//=============================================================================
// export_mod_dac.js - DAC Export Module for CDT
//=============================================================================
// Purpose: Expose DAC diagnostic information for Clinic Diagnostic Tool
// Location: C2000Ware/.../utilities/transfer/.meta/export/mods/
//
// Reference Documents:
//   - Device TRM: DAC chapter
//   - driverlib/<device>/driverlib/dac.h
//   - driverlib/<device>/driverlib/dac.c
//=============================================================================

const exportCommon = system.getScript("/utilities/transfer/export/export_mods_common.js");
const { DEVICES_WITH_DAC, DEVICES_WITH_DACA, DEVICES_WITH_DACB, DEVICES_WITH_DACC, getDeviceName } = exportCommon;
const deviceName = getDeviceName();

// Note: DAC constants imported from export_mods_common.js (centralized in device_constants.js)
// DACA/B: F28003x, F28004x, F2807x, F2837xD/S, F2838x, F28P55x, F28P65x
// DACC: F2837xD, F2837xS, F2838x only
// F280013x, F280015x, F28002x do NOT have DAC

// Alias for backward compatibility
const ALL_DAC_DEVICES = DEVICES_WITH_DAC;

//-----------------------------------------------------------------------------
// Export Information - Diagnostic Indicators
//-----------------------------------------------------------------------------
let exportsInfo = [
    //-------------------------------------------------------------------------
    // DAC Output Enable Status
    //-------------------------------------------------------------------------
    {
        name: "dacOutputEn",
        displayName: "DAC Output Enabled",
        type: 'led',
        register: "DACCTL.DACOUTEN",
        updateFunc: (instBase) => `((HWREGH(${instBase} + DAC_O_CTL) & DAC_CTL_DACOUTEN) == DAC_CTL_DACOUTEN)`,
        applicable: (inst) => {
            return ALL_DAC_DEVICES.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // DAC Reference Selection
    //-------------------------------------------------------------------------
    {
        name: "dacRefSel",
        displayName: "DAC Reference Selection",
        type: 'value',
        register: "DACCTL.DACREFSEL",
        // 0 = VDAC/VREF, 1 = ADC VREFHI/VSSA
        updateFunc: (instBase) => `((HWREGH(${instBase} + DAC_O_CTL) & DAC_CTL_DACREFSEL) >> 0)`,
        applicable: (inst) => {
            return ALL_DAC_DEVICES.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // DAC Load Mode
    //-------------------------------------------------------------------------
    {
        name: "dacLoadMode",
        displayName: "DAC Load Mode",
        type: 'value',
        register: "DACCTL.LOADMODE",
        // 0 = Load on next SYSCLK, 1 = Load on EPWMSYNCPER
        updateFunc: (instBase) => `((HWREGH(${instBase} + DAC_O_CTL) & DAC_CTL_LOADMODE) >> 2)`,
        applicable: (inst) => {
            return ALL_DAC_DEVICES.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Current DAC Output Value
    //-------------------------------------------------------------------------
    {
        name: "dacValActive",
        displayName: "DAC Active Value",
        type: 'value',
        register: "DACVALA",
        updateFunc: (instBase) => `HWREGH(${instBase} + DAC_O_VALA)`,
        applicable: (inst) => {
            return ALL_DAC_DEVICES.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Shadow Value (next value to be loaded)
    //-------------------------------------------------------------------------
    {
        name: "dacValShadow",
        displayName: "DAC Shadow Value",
        type: 'value',
        register: "DACVALS",
        updateFunc: (instBase) => `HWREGH(${instBase} + DAC_O_VALS)`,
        applicable: (inst) => {
            return ALL_DAC_DEVICES.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Lock Status
    // DACLOCK register controls write protection for DAC registers
    //-------------------------------------------------------------------------
    {
        name: "dacLocked",
        displayName: "DAC Registers Locked",
        type: 'led',
        register: "DACLOCK.DACCTL",
        updateFunc: (instBase) => `((HWREGH(${instBase} + DAC_O_LOCK) & DAC_LOCK_DACCTL) == DAC_LOCK_DACCTL)`,
        applicable: (inst) => {
            return ALL_DAC_DEVICES.includes(deviceName);
        }
    },
];

//-----------------------------------------------------------------------------
// Bitfield Instance Name Mapping
//-----------------------------------------------------------------------------
let bitfieldInstanceNames = {
    "default": (instName) => { return "Dac" + instName + "Regs" },
    "a": (instName) => { return "DacaRegs" },
    "b": (instName) => { return "DacbRegs" },
    "c": (instName) => { return "DaccRegs" },
};

//-----------------------------------------------------------------------------
// Registers to Skip
//-----------------------------------------------------------------------------
let exportsRegisterSkips = [
    // No volatile registers to skip
];

//-----------------------------------------------------------------------------
// Module Exports
//-----------------------------------------------------------------------------
exports = {
    exportsInfo: exportsInfo,
    bitfieldInstanceNames: bitfieldInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
}
