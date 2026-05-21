//=============================================================================
// export_mod_cputimer.js - CPU Timer Export Module for CDT
//=============================================================================
// Purpose: Expose CPU Timer diagnostic information for Clinic Diagnostic Tool
// Location: C2000Ware/.../utilities/transfer/.meta/export/mods/
//
// Reference Documents:
//   - Device TRM: CPU Timer chapter
//   - driverlib/<device>/driverlib/cputimer.h
//   - driverlib/<device>/driverlib/cputimer.c
//
// CPU Timer Architecture:
//   - All Gen3 C2000 devices have 3 CPU timers (TIMER0, TIMER1, TIMER2)
//   - 32-bit down counter with 16-bit prescaler
//   - Timer counts down from PRD to 0, then reloads (auto-reload mode)
//   - Prescale: Timer decrements every (TDDRH:TDDR + 1) SYSCLK cycles
//   - Timer Frequency = SYSCLK / ((PRD + 1) * (Prescale + 1))
//=============================================================================

const exportCommon = system.getScript("/utilities/transfer/export/export_mods_common.js");
const { DEVICES_WITH_CDT_SUPPORT, getDeviceName } = exportCommon;
const deviceName = getDeviceName();

// All Gen3 devices have 3 CPU timers (TIMER0, TIMER1, TIMER2)

//-----------------------------------------------------------------------------
// Export Information - Diagnostic Indicators
//-----------------------------------------------------------------------------
let exportsInfo = [
    //=========================================================================
    // Timer Status LEDs
    //=========================================================================

    //-------------------------------------------------------------------------
    // Timer Running Status (TSS bit inverted - TSS=0 means running)
    //-------------------------------------------------------------------------
    {
        name: "timerRunning",
        displayName: "Timer Running",
        description: "Timer is actively counting down. TSS=0 means running, TSS=1 means stopped.",
        type: 'led',
        register: "TCR.TSS",
        updateFunc: (instBase) => `((HWREGH(${instBase} + CPUTIMER_O_TCR) & CPUTIMER_TCR_TSS) == 0)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Timer Interrupt Enable (TIE)
    //-------------------------------------------------------------------------
    {
        name: "timerIntEnable",
        displayName: "Interrupt Enabled",
        description: "Timer interrupt is enabled. When TIF is set, an interrupt will be generated.",
        type: 'led',
        register: "TCR.TIE",
        updateFunc: (instBase) => `((HWREGH(${instBase} + CPUTIMER_O_TCR) & CPUTIMER_TCR_TIE) == CPUTIMER_TCR_TIE)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Timer Interrupt Flag (TIF)
    //-------------------------------------------------------------------------
    {
        name: "timerIntFlag",
        displayName: "Interrupt Flag Set",
        description: "Timer reached zero and set interrupt flag. Write 1 to clear. If stuck ON, ISR may not be clearing it.",
        type: 'led',
        register: "TCR.TIF",
        updateFunc: (instBase) => `((HWREGH(${instBase} + CPUTIMER_O_TCR) & CPUTIMER_TCR_TIF) == CPUTIMER_TCR_TIF)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Timer Reload Mode (TRB - Timer Reload Bit)
    // When written with 1, timer counter TIM is loaded with PRD value
    // Reading always returns 0 (write-only action bit)
    //-------------------------------------------------------------------------
    {
        name: "timerReloadPending",
        displayName: "Reload Pending",
        description: "Timer reload was requested (TRB written). Reading always returns 0 after reload completes.",
        type: 'led',
        register: "TCR.TRB",
        updateFunc: (instBase) => `((HWREGH(${instBase} + CPUTIMER_O_TCR) & CPUTIMER_TCR_TRB) == CPUTIMER_TCR_TRB)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Emulation Mode - Free Run
    // FREE=1: Timer runs free regardless of emulation suspend
    // FREE=0, SOFT=0: Stop immediately on emulation suspend
    // FREE=0, SOFT=1: Stop after current decrement on emulation suspend
    //-------------------------------------------------------------------------
    {
        name: "timerFreeRun",
        displayName: "Free Run Mode",
        description: "Timer runs free during debug halt (FREE=1). If OFF, timer stops when debugger halts CPU.",
        type: 'led',
        register: "TCR.FREE",
        updateFunc: (instBase) => `((HWREGH(${instBase} + CPUTIMER_O_TCR) & CPUTIMER_TCR_FREE) == CPUTIMER_TCR_FREE)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Emulation Mode - Soft Stop
    // SOFT=1 with FREE=0: Timer stops after current decrement on debug halt
    //-------------------------------------------------------------------------
    {
        name: "timerSoftStop",
        displayName: "Soft Stop Mode",
        description: "Timer stops gracefully after current decrement on debug halt (SOFT=1, FREE=0).",
        type: 'led',
        register: "TCR.SOFT",
        updateFunc: (instBase) => `((HWREGH(${instBase} + CPUTIMER_O_TCR) & CPUTIMER_TCR_SOFT) == CPUTIMER_TCR_SOFT)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },

    //=========================================================================
    // Timer Value Registers
    //=========================================================================

    //-------------------------------------------------------------------------
    // Timer Period (32-bit reload value)
    // This is the value loaded into TIM when timer is started or reloads
    //-------------------------------------------------------------------------
    {
        name: "timerPeriod",
        displayName: "Period (PRD)",
        description: "Timer period/reload value. Timer counts from this value down to 0.",
        type: 'value',
        register: "PRD",
        updateFunc: (instBase) => `HWREG(${instBase} + CPUTIMER_O_PRD)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Timer Counter Value (32-bit current count)
    // Note: This is volatile and may change between reads
    //-------------------------------------------------------------------------
    {
        name: "timerCounter",
        displayName: "Counter (TIM)",
        description: "Current timer count value. Counts down from PRD to 0. Volatile - captured at halt.",
        type: 'value',
        register: "TIM",
        updateFunc: (instBase) => `HWREG(${instBase} + CPUTIMER_O_TIM)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Timer Prescale Divider Low (8-bit)
    // Timer decrements every (TDDRH:TDDR + 1) SYSCLK cycles
    //-------------------------------------------------------------------------
    {
        name: "timerPrescale",
        displayName: "Prescale Low (TDDR)",
        description: "Prescale divider low byte (0-255). Timer decrements every (Prescale+1) clock cycles.",
        type: 'value',
        register: "TPR.TDDR",
        updateFunc: (instBase) => `(HWREGH(${instBase} + CPUTIMER_O_TPR) & CPUTIMER_TPR_TDDR_M)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Timer Prescale Divider High (8-bit)
    // Combined with TDDR for 16-bit prescale: (TDDRH << 8) | TDDR
    //-------------------------------------------------------------------------
    {
        name: "timerPrescaleHigh",
        displayName: "Prescale High (TDDRH)",
        description: "Prescale divider high byte (0-255). Full prescale = (TDDRH << 8) | TDDR.",
        type: 'value',
        register: "TPRH.TDDRH",
        updateFunc: (instBase) => `((HWREGH(${instBase} + CPUTIMER_O_TPRH) & CPUTIMER_TPRH_TDDRH_M) >> CPUTIMER_TPRH_TDDRH_S)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Timer Prescale Counter Low (8-bit) - PSC
    // Current prescale count value (counts down from TDDR to 0)
    //-------------------------------------------------------------------------
    {
        name: "timerPrescaleCounter",
        displayName: "Prescale Counter (PSC)",
        description: "Current prescale counter value. Counts down from TDDR to 0, then decrements TIM.",
        type: 'value',
        register: "TPR.PSC",
        updateFunc: (instBase) => `((HWREGH(${instBase} + CPUTIMER_O_TPR) & CPUTIMER_TPR_PSC_M) >> CPUTIMER_TPR_PSC_S)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Timer Control Register (Full TCR for detailed status)
    //-------------------------------------------------------------------------
    {
        name: "timerControl",
        displayName: "Control Reg (TCR)",
        description: "Full Timer Control Register value for detailed analysis.",
        type: 'value',
        register: "TCR",
        updateFunc: (instBase) => `HWREGH(${instBase} + CPUTIMER_O_TCR)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },
];

//-----------------------------------------------------------------------------
// Bitfield Instance Name Mapping
//-----------------------------------------------------------------------------
let bitfieldInstanceNames = {
    "default": (instName) => { return "CpuTimer" + instName + "Regs" },
    "0": (instName) => { return "CpuTimer0Regs" },
    "1": (instName) => { return "CpuTimer1Regs" },
    "2": (instName) => { return "CpuTimer2Regs" },
};

//-----------------------------------------------------------------------------
// Registers to Skip
//-----------------------------------------------------------------------------
let exportsRegisterSkips = [
    // Timer counter is volatile - may skip if causing issues
    // {
    //     name: "TIM",
    //     register: "TIM"
    // },
];

//-----------------------------------------------------------------------------
// Module Exports
//-----------------------------------------------------------------------------
exports = {
    exportsInfo: exportsInfo,
    bitfieldInstanceNames: bitfieldInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
}
