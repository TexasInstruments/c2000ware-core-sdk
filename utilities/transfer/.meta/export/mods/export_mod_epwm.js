//=============================================================================
// export_mod_epwm.js - EPWM Export Module for CDT
//=============================================================================
// Purpose: Expose EPWM diagnostic information for Clinic Diagnostic Tool
// Location: C2000Ware/.../utilities/transfer/.meta/export/mods/
//
// Reference Documents:
//   - Device TRM: EPWM chapter
//   - driverlib/<device>/driverlib/epwm.h
//   - driverlib/<device>/driverlib/epwm.c
//=============================================================================

const exportCommon = system.getScript("/utilities/transfer/export/export_mods_common.js");
const { DEVICES_WITH_CDT_SUPPORT, DEVICES_WITH_SOC_OVF, DEVICES_WITH_HRPWM, getDeviceName } = exportCommon;
const deviceName = getDeviceName();

// Devices with Digital Compare (DC) submodule
const DEVICES_WITH_DC = DEVICES_WITH_CDT_SUPPORT;

//-----------------------------------------------------------------------------
// Export Information - Diagnostic Indicators
//-----------------------------------------------------------------------------
let exportsInfo = [
    //-------------------------------------------------------------------------
    // Trip Zone Status Flags
    //-------------------------------------------------------------------------
    {
        name: "tzInt",
        displayName: "Trip Zone Global Interrupt",
        description: "Trip zone interrupt occurred. RED indicates any trip event triggered. Check individual TZ flags (OST, CBC, DCxEVT) for specific cause.",
        type: 'led',
        register: "TZFLG.INT",
        updateFunc: (instBase) => `((HWREGH(${instBase} + EPWM_O_TZFLG) & EPWM_TZFLG_INT) == EPWM_TZFLG_INT)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },
    {
        name: "tzOst",
        displayName: "Trip Zone One-Shot Event",
        description: "One-shot trip event occurred. RED indicates a latched fault requiring software clear. PWM outputs forced to safe state until cleared.",
        type: 'led',
        register: "TZFLG.OST",
        updateFunc: (instBase) => `((HWREGH(${instBase} + EPWM_O_TZFLG) & EPWM_TZFLG_OST) == EPWM_TZFLG_OST)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },
    {
        name: "tzCbc",
        displayName: "Trip Zone Cycle-by-Cycle Event",
        description: "Cycle-by-cycle trip event occurred. RED indicates recoverable fault. PWM auto-restarts next period if fault clears.",
        type: 'led',
        register: "TZFLG.CBC",
        updateFunc: (instBase) => `((HWREGH(${instBase} + EPWM_O_TZFLG) & EPWM_TZFLG_CBC) == EPWM_TZFLG_CBC)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },
    {
        name: "tzDcaevt1",
        displayName: "Digital Compare A Event 1",
        description: "Digital Compare A Event 1 triggered trip. RED indicates DCAH/DCAL comparator condition met. Often used for overcurrent protection.",
        type: 'led',
        register: "TZFLG.DCAEVT1",
        updateFunc: (instBase) => `((HWREGH(${instBase} + EPWM_O_TZFLG) & EPWM_TZFLG_DCAEVT1) == EPWM_TZFLG_DCAEVT1)`,
        applicable: (inst) => {
            return DEVICES_WITH_DC.includes(deviceName);
        }
    },
    {
        name: "tzDcaevt2",
        displayName: "Digital Compare A Event 2",
        description: "Digital Compare A Event 2 triggered trip. RED indicates secondary DCAH/DCAL condition met. Often used for second-level protection.",
        type: 'led',
        register: "TZFLG.DCAEVT2",
        updateFunc: (instBase) => `((HWREGH(${instBase} + EPWM_O_TZFLG) & EPWM_TZFLG_DCAEVT2) == EPWM_TZFLG_DCAEVT2)`,
        applicable: (inst) => {
            return DEVICES_WITH_DC.includes(deviceName);
        }
    },
    {
        name: "tzDcbevt1",
        displayName: "Digital Compare B Event 1",
        description: "Digital Compare B Event 1 triggered trip. RED indicates DCBH/DCBL comparator condition met. Often used for channel B overcurrent.",
        type: 'led',
        register: "TZFLG.DCBEVT1",
        updateFunc: (instBase) => `((HWREGH(${instBase} + EPWM_O_TZFLG) & EPWM_TZFLG_DCBEVT1) == EPWM_TZFLG_DCBEVT1)`,
        applicable: (inst) => {
            return DEVICES_WITH_DC.includes(deviceName);
        }
    },
    {
        name: "tzDcbevt2",
        displayName: "Digital Compare B Event 2",
        description: "Digital Compare B Event 2 triggered trip. RED indicates secondary DCBH/DCBL condition met. Often used for second-level protection.",
        type: 'led',
        register: "TZFLG.DCBEVT2",
        updateFunc: (instBase) => `((HWREGH(${instBase} + EPWM_O_TZFLG) & EPWM_TZFLG_DCBEVT2) == EPWM_TZFLG_DCBEVT2)`,
        applicable: (inst) => {
            return DEVICES_WITH_DC.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Event Trigger Status
    //-------------------------------------------------------------------------
    {
        name: "etInt",
        displayName: "EPWM Interrupt Flag",
        description: "EPWM interrupt pending. GREEN indicates configured interrupt event occurred (CTR=0, CTR=PRD, etc.). Should toggle each PWM period.",
        type: 'led',
        register: "ETFLG.INT",
        updateFunc: (instBase) => `((HWREGH(${instBase} + EPWM_O_ETFLG) & EPWM_ETFLG_INT) == EPWM_ETFLG_INT)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },
    {
        name: "etSocA",
        displayName: "SOCA Flag",
        description: "ADC Start-of-Conversion A pulse generated. GREEN indicates SOCA trigger sent to ADC. Should toggle if SOCA enabled.",
        type: 'led',
        register: "ETFLG.SOCA",
        updateFunc: (instBase) => `((HWREGH(${instBase} + EPWM_O_ETFLG) & EPWM_ETFLG_SOCA) == EPWM_ETFLG_SOCA)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },
    {
        name: "etSocB",
        displayName: "SOCB Flag",
        description: "ADC Start-of-Conversion B pulse generated. GREEN indicates SOCB trigger sent to ADC. Should toggle if SOCB enabled.",
        type: 'led',
        register: "ETFLG.SOCB",
        updateFunc: (instBase) => `((HWREGH(${instBase} + EPWM_O_ETFLG) & EPWM_ETFLG_SOCB) == EPWM_ETFLG_SOCB)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },
    {
        name: "etSocAOvf",
        displayName: "SOCA Overflow",
        description: "SOCA trigger overrun. RED indicates new SOCA generated before ADC acknowledged previous. ADC may be missing conversions.",
        type: 'led',
        register: "ETFLG.SOCAOVF",
        updateFunc: (instBase) => `((HWREGH(${instBase} + EPWM_O_ETFLG) & EPWM_ETFLG_SOCAOVF) == EPWM_ETFLG_SOCAOVF)`,
        applicable: (inst) => {
            // SOCAOVF only exists on F2837xD/S, F2838x, F28P65x
            return DEVICES_WITH_SOC_OVF.includes(deviceName);
        }
    },
    {
        name: "etSocBOvf",
        displayName: "SOCB Overflow",
        description: "SOCB trigger overrun. RED indicates new SOCB generated before ADC acknowledged previous. ADC may be missing conversions.",
        type: 'led',
        register: "ETFLG.SOCBOVF",
        updateFunc: (instBase) => `((HWREGH(${instBase} + EPWM_O_ETFLG) & EPWM_ETFLG_SOCBOVF) == EPWM_ETFLG_SOCBOVF)`,
        applicable: (inst) => {
            // SOCBOVF only exists on F2837xD/S, F2838x, F28P65x
            return DEVICES_WITH_SOC_OVF.includes(deviceName);
        }
    },
    {
        name: "etIntOvf",
        displayName: "EPWM Interrupt Overflow",
        description: "EPWM interrupt overrun. RED indicates new interrupt generated before previous was serviced. ISR may be too slow for PWM frequency.",
        type: 'led',
        register: "ETFLG.INTOVF",
        updateFunc: (instBase) => `((HWREGH(${instBase} + EPWM_O_ETFLG) & EPWM_ETFLG_INTOVF) == EPWM_ETFLG_INTOVF)`,
        applicable: (inst) => {
            // INTOVF only exists on F2837xD/S, F2838x, F28P65x (same as SOCAOVF/SOCBOVF)
            return DEVICES_WITH_SOC_OVF.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Time Base Status (counter direction, sync, max)
    //-------------------------------------------------------------------------
    {
        name: "tbCtrDir",
        displayName: "Counter Direction (1=Up)",
        description: "Time-base counter direction. GREEN = counting up, OFF = counting down. Should toggle in up-down mode, stay constant in up or down mode.",
        type: 'led',
        register: "TBSTS.CTRDIR",
        updateFunc: (instBase) => `((HWREGH(${instBase} + EPWM_O_TBSTS) & EPWM_TBSTS_CTRDIR) == EPWM_TBSTS_CTRDIR)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },
    {
        name: "tbSynci",
        displayName: "External Sync Input Status",
        description: "External sync input received. GREEN indicates SYNCI pulse arrived from another EPWM or external source. Used for multi-EPWM synchronization.",
        type: 'led',
        register: "TBSTS.SYNCI",
        updateFunc: (instBase) => `((HWREGH(${instBase} + EPWM_O_TBSTS) & EPWM_TBSTS_SYNCI) == EPWM_TBSTS_SYNCI)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },
    {
        name: "tbCtrMax",
        displayName: "Counter Max Latched Status",
        description: "Counter reached maximum value. GREEN indicates counter hit 0xFFFF. Unexpected in normal operation - check TBPRD and counter mode settings.",
        type: 'led',
        register: "TBSTS.CTRMAX",
        updateFunc: (instBase) => `((HWREGH(${instBase} + EPWM_O_TBSTS) & EPWM_TBSTS_CTRMAX) == EPWM_TBSTS_CTRMAX)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Digital Compare Status
    //-------------------------------------------------------------------------
    {
        name: "dcHighStatus",
        displayName: "DC Event A1 Latched",
        description: "Digital Compare A Event 1 latched. GREEN indicates DCAEVT1 condition was met and captured. Use for debugging comparator trip conditions.",
        type: 'led',
        register: "DCACTL.EVT1LAT",
        updateFunc: (instBase) => `((HWREGH(${instBase} + EPWM_O_DCACTL) & EPWM_DCACTL_EVT1LAT) == EPWM_DCACTL_EVT1LAT)`,
        applicable: (inst) => {
            return DEVICES_WITH_DC.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // HRPWM Status (if enabled)
    //-------------------------------------------------------------------------
    {
        name: "hrpwmCalError",
        displayName: "HRPWM MEP Step Invalid",
        description: "HRPWM calibration invalid. RED indicates SFO calibration not run or failed (MEP step = 0). Run SFO() in background task for valid HRPWM operation.",
        type: 'led',
        register: "HRMSTEP.HRMSTEP",
        // MEP step of 0 indicates calibration not run or error
        updateFunc: (instBase) => `((HWREGH(${instBase} + HRPWM_O_HRMSTEP) & HRPWM_HRMSTEP_HRMSTEP_M) == 0)`,
        applicable: (inst) => {
            return DEVICES_WITH_HRPWM.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Value Exports - Current EPWM Configuration
    //-------------------------------------------------------------------------
    {
        name: "tbPeriod",
        displayName: "Time Base Period",
        description: "PWM period register value (TBPRD). PWM frequency = TBCLK / (TBPRD + 1) for up-count mode, or TBCLK / (2 * TBPRD) for up-down mode.",
        type: 'value',
        register: "TBPRD",
        updateFunc: (instBase) => `HWREGH(${instBase} + EPWM_O_TBPRD)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },
    {
        name: "tbCounter",
        displayName: "Time Base Counter",
        description: "Current time-base counter value (0 to TBPRD). Shows real-time PWM position within the period. Should be continuously changing.",
        type: 'value',
        register: "TBCTR",
        updateFunc: (instBase) => `HWREGH(${instBase} + EPWM_O_TBCTR)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },
    {
        name: "cmpaValue",
        displayName: "Compare A Value",
        description: "Compare A register value (CMPA). Controls duty cycle of EPWMxA output. Duty = CMPA/TBPRD for up-count, or (TBPRD-CMPA)/TBPRD for complementary.",
        type: 'value',
        register: "CMPA",
        updateFunc: (instBase) => `HWREGH(${instBase} + EPWM_O_CMPA)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },
    {
        name: "cmpbValue",
        displayName: "Compare B Value",
        description: "Compare B register value (CMPB). Controls duty cycle of EPWMxB output. Often used for dead-band generation or separate duty control.",
        type: 'value',
        register: "CMPB",
        updateFunc: (instBase) => `HWREGH(${instBase} + EPWM_O_CMPB)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },
];

//-----------------------------------------------------------------------------
// Bitfield Instance Name Mapping
//-----------------------------------------------------------------------------
let bitfieldInstanceNames = {
    "default": (instName) => { return "EPwm" + instName + "Regs" },
};

//-----------------------------------------------------------------------------
// Registers to Skip (Read-to-Clear and Force registers)
//-----------------------------------------------------------------------------
let exportsRegisterSkips = [
    // Time base counter is volatile - may not want to export continuously
    // { name: "TBCTR", register: "TBCTR" },

    // Trip Zone Read-to-Clear registers (R/W1C - Write 1 to Clear)
    { name: "TZCLR", register: "EPWMTZCLR" },
    { name: "TZCBCCLR", register: "EPWMTZCBCCLR" },
    { name: "TZOSTCLR", register: "EPWMTZOSTCLR" },
    // Trip Zone Force registers (Write-Only - Force trigger)
    { name: "TZFRC", register: "EPWMTZFRC" },
    // Event Trigger Read-to-Clear registers (R/W1C - Write 1 to Clear)
    { name: "ETCLR", register: "EPWMETCLR" },
    // Event Trigger Force registers (Write-Only - Force trigger)
    { name: "ETFRC", register: "EPWMETFRC" },
];

//-----------------------------------------------------------------------------
// Module Exports
//-----------------------------------------------------------------------------
exports = {
    exportsInfo: exportsInfo,
    bitfieldInstanceNames: bitfieldInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
}
