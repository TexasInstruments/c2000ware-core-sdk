//=============================================================================
// export_mod_clb.js - CLB Export Module for CDT
//=============================================================================
// Purpose: Expose Configurable Logic Block diagnostic information for CDT
// Reference: driverlib/<device>/driverlib/inc/hw_clb.h
//
// Register Offsets (from hw_clb.h):
//   CLB_O_LOAD_EN    = 0x0  - Global enable & indirect load enable
//   CLB_O_DBG_OUT_2  = 0x2E - Inputs (bits 8-15) and async outputs (bits 0-7)
//   CLB_O_DBG_R0-R3  = 0x30-0x36 - HLC registers R0-R3
//   CLB_O_DBG_OUT    = 0x3E - Cell outputs and internal unit outputs
//=============================================================================

const exportCommon = system.getScript("/utilities/transfer/export/export_mods_common.js");
const { DEVICES_WITH_CLB, getDeviceName } = exportCommon;
const deviceName = getDeviceName();

// Note: CLB available on F28002x, F28003x, F28004x, F2838x, F28P55x, F28P65x
// F280013x, F280015x, F2807x, F2837xD/S do NOT have CLB

//-----------------------------------------------------------------------------
// Export Information - Diagnostic Indicators
//-----------------------------------------------------------------------------
let exportsInfo = [
    //-------------------------------------------------------------------------
    // CLB Enable Status (CLB_O_LOAD_EN at offset 0x0)
    // Bit 0: LOAD_EN, Bit 1: GLOBAL_EN, Bit 2: STOP, Bit 3: NMI_EN
    //-------------------------------------------------------------------------
    {
        name: "clbGlobalEn",
        displayName: "CLB Global Enable",
        description: "CLB tile globally enabled. GREEN indicates CLB logic is active and processing. Must be set for any CLB functionality.",
        type: 'led',
        register: "CLB_LOAD_EN.GLOBAL_EN",
        updateFunc: (instBase) => `((HWREGH(${instBase} + CLB_O_LOAD_EN) & CLB_LOAD_EN_GLOBAL_EN) == CLB_LOAD_EN_GLOBAL_EN)`,
        applicable: (inst) => {
            return DEVICES_WITH_CLB.includes(deviceName);
        }
    },
    {
        name: "clbLoadEn",
        displayName: "CLB Load Enable",
        description: "CLB indirect register load enabled. GREEN allows HLC to load counter/FSM values. Required for dynamic CLB configuration updates.",
        type: 'led',
        register: "CLB_LOAD_EN.LOAD_EN",
        updateFunc: (instBase) => `((HWREGH(${instBase} + CLB_O_LOAD_EN) & CLB_LOAD_EN_LOAD_EN) == CLB_LOAD_EN_LOAD_EN)`,
        applicable: (inst) => {
            return DEVICES_WITH_CLB.includes(deviceName);
        }
    },
    {
        name: "clbNmiEn",
        displayName: "CLB NMI Output Enable",
        description: "CLB can trigger NMI. GREEN enables CLB output to generate non-maskable interrupt. Use for critical safety-related CLB functions.",
        type: 'led',
        register: "CLB_LOAD_EN.NMI_EN",
        updateFunc: (instBase) => `((HWREGH(${instBase} + CLB_O_LOAD_EN) & CLB_LOAD_EN_NMI_EN) == CLB_LOAD_EN_NMI_EN)`,
        applicable: (inst) => {
            return DEVICES_WITH_CLB.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // CLB Debug Output 2 (CLB_O_DBG_OUT_2 at offset 0x2E)
    // Bits 0-7: Async outputs, Bits 8-15: Cell inputs
    //-------------------------------------------------------------------------
    {
        name: "clbAsyncOut",
        displayName: "CLB Async Outputs",
        description: "CLB asynchronous output states (8-bit). Shows raw output values before output LUT processing. Useful for debugging CLB logic.",
        type: 'value',
        register: "CLB_DBG_OUT_2.OUT",
        updateFunc: (instBase) => `((HWREGH(${instBase} + CLB_O_DBG_OUT_2) & CLB_DBG_OUT_2_OUT_M) >> CLB_DBG_OUT_2_OUT_S)`,
        applicable: (inst) => {
            return DEVICES_WITH_CLB.includes(deviceName);
        }
    },
    {
        name: "clbInputs",
        displayName: "CLB Cell Inputs",
        description: "CLB input signal states (8-bit). Shows current values at CLB input mux outputs. Verify external signals are reaching CLB correctly.",
        type: 'value',
        register: "CLB_DBG_OUT_2.IN",
        updateFunc: (instBase) => `((HWREGH(${instBase} + CLB_O_DBG_OUT_2) & CLB_DBG_OUT_2_IN_M) >> CLB_DBG_OUT_2_IN_S)`,
        applicable: (inst) => {
            return DEVICES_WITH_CLB.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // HLC Registers (CLB_O_DBG_R0-R3 at offsets 0x30-0x36)
    //-------------------------------------------------------------------------
    {
        name: "clbHlcR0",
        displayName: "CLB HLC Register R0",
        description: "High-Level Controller register R0 value. 32-bit general purpose register for HLC program use. Monitor for debugging HLC state machines.",
        type: 'value',
        register: "CLB_DBG_R0",
        updateFunc: (instBase) => `HWREGH(${instBase} + CLB_O_DBG_R0)`,
        applicable: (inst) => {
            return DEVICES_WITH_CLB.includes(deviceName);
        }
    },
    {
        name: "clbHlcR1",
        displayName: "CLB HLC Register R1",
        description: "High-Level Controller register R1 value. 32-bit general purpose register for HLC program use. Monitor for debugging HLC state machines.",
        type: 'value',
        register: "CLB_DBG_R1",
        updateFunc: (instBase) => `HWREGH(${instBase} + CLB_O_DBG_R1)`,
        applicable: (inst) => {
            return DEVICES_WITH_CLB.includes(deviceName);
        }
    },
    {
        name: "clbHlcR2",
        displayName: "CLB HLC Register R2",
        description: "High-Level Controller register R2 value. 32-bit general purpose register for HLC program use. Monitor for debugging HLC state machines.",
        type: 'value',
        register: "CLB_DBG_R2",
        updateFunc: (instBase) => `HWREGH(${instBase} + CLB_O_DBG_R2)`,
        applicable: (inst) => {
            return DEVICES_WITH_CLB.includes(deviceName);
        }
    },
    {
        name: "clbHlcR3",
        displayName: "CLB HLC Register R3",
        description: "High-Level Controller register R3 value. 32-bit general purpose register for HLC program use. Monitor for debugging HLC state machines.",
        type: 'value',
        register: "CLB_DBG_R3",
        updateFunc: (instBase) => `HWREGH(${instBase} + CLB_O_DBG_R3)`,
        applicable: (inst) => {
            return DEVICES_WITH_CLB.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // CLB Debug Output (CLB_O_DBG_OUT at offset 0x3E)
    // Cell outputs and internal unit outputs (32-bit register)
    //-------------------------------------------------------------------------
    {
        name: "clbOut0",
        displayName: "CLB Output 0 State",
        description: "CLB output 0 current state. GREEN indicates output is high. Shows real-time state of CLB output signal to peripherals/GPIOs.",
        type: 'led',
        register: "CLB_DBG_OUT.OUT0",
        updateFunc: (instBase) => `((HWREG(${instBase} + CLB_O_DBG_OUT) & CLB_DBG_OUT_OUT0) == CLB_DBG_OUT_OUT0)`,
        applicable: (inst) => {
            return DEVICES_WITH_CLB.includes(deviceName);
        }
    },
    {
        name: "clbOut1",
        displayName: "CLB Output 1 State",
        description: "CLB output 1 current state. GREEN indicates output is high. Shows real-time state of CLB output signal to peripherals/GPIOs.",
        type: 'led',
        register: "CLB_DBG_OUT.OUT1",
        updateFunc: (instBase) => `((HWREG(${instBase} + CLB_O_DBG_OUT) & CLB_DBG_OUT_OUT1) == CLB_DBG_OUT_OUT1)`,
        applicable: (inst) => {
            return DEVICES_WITH_CLB.includes(deviceName);
        }
    },
    {
        name: "clbOut2",
        displayName: "CLB Output 2 State",
        description: "CLB output 2 current state. GREEN indicates output is high. Shows real-time state of CLB output signal to peripherals/GPIOs.",
        type: 'led',
        register: "CLB_DBG_OUT.OUT2",
        updateFunc: (instBase) => `((HWREG(${instBase} + CLB_O_DBG_OUT) & CLB_DBG_OUT_OUT2) == CLB_DBG_OUT_OUT2)`,
        applicable: (inst) => {
            return DEVICES_WITH_CLB.includes(deviceName);
        }
    },
    {
        name: "clbOut3",
        displayName: "CLB Output 3 State",
        description: "CLB output 3 current state. GREEN indicates output is high. Shows real-time state of CLB output signal to peripherals/GPIOs.",
        type: 'led',
        register: "CLB_DBG_OUT.OUT3",
        updateFunc: (instBase) => `((HWREG(${instBase} + CLB_O_DBG_OUT) & CLB_DBG_OUT_OUT3) == CLB_DBG_OUT_OUT3)`,
        applicable: (inst) => {
            return DEVICES_WITH_CLB.includes(deviceName);
        }
    },
    {
        name: "clbOut4",
        displayName: "CLB Output 4 State",
        description: "CLB output 4 current state. GREEN indicates output is high. Shows real-time state of CLB output signal to peripherals/GPIOs.",
        type: 'led',
        register: "CLB_DBG_OUT.OUT4",
        updateFunc: (instBase) => `((HWREG(${instBase} + CLB_O_DBG_OUT) & CLB_DBG_OUT_OUT4) == CLB_DBG_OUT_OUT4)`,
        applicable: (inst) => {
            return DEVICES_WITH_CLB.includes(deviceName);
        }
    },
    {
        name: "clbOut5",
        displayName: "CLB Output 5 State",
        description: "CLB output 5 current state. GREEN indicates output is high. Shows real-time state of CLB output signal to peripherals/GPIOs.",
        type: 'led',
        register: "CLB_DBG_OUT.OUT5",
        updateFunc: (instBase) => `((HWREG(${instBase} + CLB_O_DBG_OUT) & CLB_DBG_OUT_OUT5) == CLB_DBG_OUT_OUT5)`,
        applicable: (inst) => {
            return DEVICES_WITH_CLB.includes(deviceName);
        }
    },
    {
        name: "clbOut6",
        displayName: "CLB Output 6 State",
        description: "CLB output 6 current state. GREEN indicates output is high. Shows real-time state of CLB output signal to peripherals/GPIOs.",
        type: 'led',
        register: "CLB_DBG_OUT.OUT6",
        updateFunc: (instBase) => `((HWREG(${instBase} + CLB_O_DBG_OUT) & CLB_DBG_OUT_OUT6) == CLB_DBG_OUT_OUT6)`,
        applicable: (inst) => {
            return DEVICES_WITH_CLB.includes(deviceName);
        }
    },
    {
        name: "clbOut7",
        displayName: "CLB Output 7 State",
        description: "CLB output 7 current state. GREEN indicates output is high. Shows real-time state of CLB output signal to peripherals/GPIOs.",
        type: 'led',
        register: "CLB_DBG_OUT.OUT7",
        updateFunc: (instBase) => `((HWREG(${instBase} + CLB_O_DBG_OUT) & CLB_DBG_OUT_OUT7) == CLB_DBG_OUT_OUT7)`,
        applicable: (inst) => {
            return DEVICES_WITH_CLB.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // CLB Counter Debug Values (CLB_O_DBG_C0-C2 at offsets 0x38-0x3C)
    //-------------------------------------------------------------------------
    {
        name: "clbCnt0",
        displayName: "CLB Counter 0 Value",
        description: "CLB Counter 0 current count value. 32-bit counter used by CLB logic. Monitor for timing, PWM generation, or event counting applications.",
        type: 'value',
        register: "CLB_DBG_C0",
        updateFunc: (instBase) => `HWREG(${instBase} + CLB_O_DBG_C0)`,
        applicable: (inst) => {
            return DEVICES_WITH_CLB.includes(deviceName);
        }
    },
    {
        name: "clbCnt1",
        displayName: "CLB Counter 1 Value",
        description: "CLB Counter 1 current count value. 32-bit counter used by CLB logic. Monitor for timing, PWM generation, or event counting applications.",
        type: 'value',
        register: "CLB_DBG_C1",
        updateFunc: (instBase) => `HWREG(${instBase} + CLB_O_DBG_C1)`,
        applicable: (inst) => {
            return DEVICES_WITH_CLB.includes(deviceName);
        }
    },
    {
        name: "clbCnt2",
        displayName: "CLB Counter 2 Value",
        description: "CLB Counter 2 current count value. 32-bit counter used by CLB logic. Monitor for timing, PWM generation, or event counting applications.",
        type: 'value',
        register: "CLB_DBG_C2",
        updateFunc: (instBase) => `HWREG(${instBase} + CLB_O_DBG_C2)`,
        applicable: (inst) => {
            return DEVICES_WITH_CLB.includes(deviceName);
        }
    },
];

//-----------------------------------------------------------------------------
// Bitfield Instance Name Mapping
//-----------------------------------------------------------------------------
let bitfieldInstanceNames = {
    // CLB registers are split into LogicCfgRegs, LogicCtrlRegs, DataExchRegs
    // Debug/status registers are in LogicCtrlRegs
    "default": (instName) => { return "Clb" + instName + "LogicCtrlRegs" },
};

//-----------------------------------------------------------------------------
// Registers to Skip
//-----------------------------------------------------------------------------
let exportsRegisterSkips = [
    // Debug registers change rapidly
];

//-----------------------------------------------------------------------------
// Module Exports
//-----------------------------------------------------------------------------
exports = {
    exportsInfo: exportsInfo,
    bitfieldInstanceNames: bitfieldInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
}
