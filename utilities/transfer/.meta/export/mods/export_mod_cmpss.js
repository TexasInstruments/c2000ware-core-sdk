//=============================================================================
// export_mod_cmpss.js - CMPSS Export Module for CDT
//=============================================================================
// Purpose: Expose Comparator Subsystem diagnostic information for CDT
// Location: C2000Ware/.../utilities/transfer/.meta/export/mods/
//
// Reference Documents:
//   - Device TRM: CMPSS chapter
//   - driverlib/<device>/driverlib/cmpss.h
//   - driverlib/<device>/driverlib/cmpss.c
//=============================================================================

const exportCommon = system.getScript("/utilities/transfer/export/export_mods_common.js");
const { DEVICES_WITH_CDT_SUPPORT, DEVICES_WITH_CMPSS, getDeviceName } = exportCommon;
const deviceName = getDeviceName();

// CMPSS Instance Counts by Device (from hw_memmap.h)
// F28003x: CMPSS1-4 (4 instances)
// F28004x: CMPSS1-7 (7 instances)
// F2807x: CMPSS1-8 (8 instances)
// F2837xD/S: CMPSS1-8 (8 instances)
// F2838x: CMPSS1-8 (8 instances)
// F28P55x: CMPSS1-4 (4 instances)
// F28P65x: CMPSS1-11 (11 instances)

//-----------------------------------------------------------------------------
// Export Information - Diagnostic Indicators
//-----------------------------------------------------------------------------
let exportsInfo = [
    //-------------------------------------------------------------------------
    // Comparator Output Status - High Side
    // LED Color: RED = comparator output HIGH (input > threshold)
    //            GREEN = comparator output LOW (input < threshold)
    //-------------------------------------------------------------------------
    {
        name: "compHigh",
        displayName: "High Comparator Output",
        description: "Current state of high-side comparator output.\nRED = Input signal exceeds high threshold (comparator output HIGH)\nGREEN = Input signal below high threshold (comparator output LOW)",
        type: 'led',
        register: "COMPSTS.COMPHSTS",
        updateFunc: (instBase) => `((HWREGH(${instBase} + CMPSS_O_COMPSTS) & CMPSS_COMPSTS_COMPHSTS) == CMPSS_COMPSTS_COMPHSTS)`,
        applicable: (inst) => {
            return DEVICES_WITH_CMPSS.includes(deviceName);
        }
    },
    {
        name: "compHighLatch",
        displayName: "High Comparator Latched",
        description: "Latched status of high-side comparator. Stays set until cleared.\nRED = High threshold was exceeded at some point (latched trip)\nGREEN = No trip event since last clear",
        type: 'led',
        register: "COMPSTS.COMPHLATCH",
        updateFunc: (instBase) => `((HWREGH(${instBase} + CMPSS_O_COMPSTS) & CMPSS_COMPSTS_COMPHLATCH) == CMPSS_COMPSTS_COMPHLATCH)`,
        applicable: (inst) => {
            return DEVICES_WITH_CMPSS.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Comparator Output Status - Low Side
    // LED Color: RED = comparator output HIGH (input < threshold)
    //            GREEN = comparator output LOW (input > threshold)
    //-------------------------------------------------------------------------
    {
        name: "compLow",
        displayName: "Low Comparator Output",
        description: "Current state of low-side comparator output.\nRED = Input signal below low threshold (comparator output HIGH)\nGREEN = Input signal above low threshold (comparator output LOW)",
        type: 'led',
        register: "COMPSTS.COMPLSTS",
        updateFunc: (instBase) => `((HWREGH(${instBase} + CMPSS_O_COMPSTS) & CMPSS_COMPSTS_COMPLSTS) == CMPSS_COMPSTS_COMPLSTS)`,
        applicable: (inst) => {
            return DEVICES_WITH_CMPSS.includes(deviceName);
        }
    },
    {
        name: "compLowLatch",
        displayName: "Low Comparator Latched",
        description: "Latched status of low-side comparator. Stays set until cleared.\nRED = Low threshold was crossed at some point (latched trip)\nGREEN = No trip event since last clear",
        type: 'led',
        register: "COMPSTS.COMPLLATCH",
        updateFunc: (instBase) => `((HWREGH(${instBase} + CMPSS_O_COMPSTS) & CMPSS_COMPSTS_COMPLLATCH) == CMPSS_COMPSTS_COMPLLATCH)`,
        applicable: (inst) => {
            return DEVICES_WITH_CMPSS.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // DAC Reference Values (for monitoring threshold settings)
    //-------------------------------------------------------------------------
    {
        name: "dacValHigh",
        displayName: "DAC High Value",
        type: 'value',
        register: "DACHVALS.DACVAL",
        updateFunc: (instBase) => `((HWREGH(${instBase} + CMPSS_O_DACHVALS) & CMPSS_DACHVALS_DACVAL_M))`,
        applicable: (inst) => {
            return DEVICES_WITH_CMPSS.includes(deviceName);
        }
    },
    {
        name: "dacValLow",
        displayName: "DAC Low Value",
        type: 'value',
        register: "DACLVALS.DACVAL",
        updateFunc: (instBase) => `((HWREGH(${instBase} + CMPSS_O_DACLVALS) & CMPSS_DACLVALS_DACVAL_M))`,
        applicable: (inst) => {
            return DEVICES_WITH_CMPSS.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Ramp Generator Status
    // RAMPSTS register (offset 0x10) contains current ramp value
    // Non-zero value indicates ramp generator is active
    //-------------------------------------------------------------------------
    {
        name: "rampValue",
        displayName: "Ramp Generator Value",
        description: "Current ramp generator counter value. Non-zero indicates ramp is active.",
        type: 'value',
        register: "RAMPSTS.RAMPVALUE",
        updateFunc: (instBase) => `(HWREGH(${instBase} + CMPSS_O_RAMPSTS))`,
        applicable: (inst) => {
            return DEVICES_WITH_CMPSS.includes(deviceName);
        }
    },
    {
        name: "rampMaxRef",
        displayName: "Ramp Max Reference",
        description: "Maximum reference value for ramp generator (active register).",
        type: 'value',
        register: "RAMPMAXREFA",
        updateFunc: (instBase) => `(HWREGH(${instBase} + CMPSS_O_RAMPMAXREFA))`,
        applicable: (inst) => {
            return DEVICES_WITH_CMPSS.includes(deviceName);
        }
    },
    {
        name: "rampDecVal",
        displayName: "Ramp Decrement Value",
        description: "Decrement value per SYSCLK cycle for ramp generator.",
        type: 'value',
        register: "RAMPDECVALA",
        updateFunc: (instBase) => `(HWREGH(${instBase} + CMPSS_O_RAMPDECVALA))`,
        applicable: (inst) => {
            return DEVICES_WITH_CMPSS.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Digital Filter Configuration
    // CTRIPHFILCTL and CTRIPLFILLCTL contain filter sample/threshold settings
    //-------------------------------------------------------------------------
    {
        name: "digFilterHSamplePrescale",
        displayName: "High Digital Filter Sample Prescale",
        description: "Sample clock prescale for high-side digital filter.",
        type: 'value',
        register: "CTRIPHFILCTL.SAMPPRESC",
        // CMPSS_CTRIPHFILCTL_SAMPPRESC_M = bits [9:0] = 0x03FF (Ref: hw_cmpss.h)
        updateFunc: (instBase) => `((HWREGH(${instBase} + CMPSS_O_CTRIPHFILCTL) & CMPSS_CTRIPHFILCTL_SAMPPRESC_M))`,
        applicable: (inst) => {
            return DEVICES_WITH_CMPSS.includes(deviceName);
        }
    },
    {
        name: "digFilterLSamplePrescale",
        displayName: "Low Digital Filter Sample Prescale",
        description: "Sample clock prescale for low-side digital filter.",
        type: 'value',
        register: "CTRIPLFILCTL.SAMPPRESC",
        // CMPSS_CTRIPLFILCTL_SAMPPRESC_M = bits [9:0] = 0x03FF (Ref: hw_cmpss.h)
        updateFunc: (instBase) => `((HWREGH(${instBase} + CMPSS_O_CTRIPLFILCTL) & CMPSS_CTRIPLFILCTL_SAMPPRESC_M))`,
        applicable: (inst) => {
            return DEVICES_WITH_CMPSS.includes(deviceName);
        }
    },
];

//-----------------------------------------------------------------------------
// Bitfield Instance Name Mapping
//-----------------------------------------------------------------------------
let bitfieldInstanceNames = {
    "default": (instName) => { return "Cmpss" + instName + "Regs" },
};

//-----------------------------------------------------------------------------
// Registers to Skip (Read-to-Clear registers)
//-----------------------------------------------------------------------------
let exportsRegisterSkips = [
    // Read-to-Clear registers (R/W1C - Write 1 to Clear)
    { name: "COMPSTSCLR", register: "CMPSSCOMPSTSCLR" },
];

//-----------------------------------------------------------------------------
// Module Exports
//-----------------------------------------------------------------------------
exports = {
    exportsInfo: exportsInfo,
    bitfieldInstanceNames: bitfieldInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
}
