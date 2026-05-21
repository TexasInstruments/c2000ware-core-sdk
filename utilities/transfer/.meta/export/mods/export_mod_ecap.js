//=============================================================================
// export_mod_ecap.js - ECAP Export Module for CDT
//=============================================================================
// Purpose: Expose Enhanced Capture diagnostic information for CDT
// Location: C2000Ware/.../utilities/transfer/.meta/export/mods/
//
// Reference Documents:
//   - Device TRM: ECAP chapter
//   - driverlib/<device>/driverlib/ecap.h
//   - driverlib/<device>/driverlib/ecap.c
//=============================================================================

const exportCommon = system.getScript("/utilities/transfer/export/export_mods_common.js");
const { DEVICES_WITH_CDT_SUPPORT, DEVICES_WITH_HRCAP, getDeviceName } = exportCommon;
const deviceName = getDeviceName();

// DEVICES_WITH_HRCAP imported from export_mods_common (sourced from device_constants.js)

//-----------------------------------------------------------------------------
// Export Information - Diagnostic Indicators
//-----------------------------------------------------------------------------
let exportsInfo = [
    //-------------------------------------------------------------------------
    // Capture Status Flags
    //-------------------------------------------------------------------------
    {
        name: "capEvt1",
        displayName: "Capture Event 1 Flag",
        type: 'led',
        register: "ECFLG.CEVT1",
        updateFunc: (instBase) => `((HWREGH(${instBase} + ECAP_O_ECFLG) & ECAP_ECFLG_CEVT1) == ECAP_ECFLG_CEVT1)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },
    {
        name: "capEvt2",
        displayName: "Capture Event 2 Flag",
        type: 'led',
        register: "ECFLG.CEVT2",
        updateFunc: (instBase) => `((HWREGH(${instBase} + ECAP_O_ECFLG) & ECAP_ECFLG_CEVT2) == ECAP_ECFLG_CEVT2)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },
    {
        name: "capEvt3",
        displayName: "Capture Event 3 Flag",
        type: 'led',
        register: "ECFLG.CEVT3",
        updateFunc: (instBase) => `((HWREGH(${instBase} + ECAP_O_ECFLG) & ECAP_ECFLG_CEVT3) == ECAP_ECFLG_CEVT3)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },
    {
        name: "capEvt4",
        displayName: "Capture Event 4 Flag",
        type: 'led',
        register: "ECFLG.CEVT4",
        updateFunc: (instBase) => `((HWREGH(${instBase} + ECAP_O_ECFLG) & ECAP_ECFLG_CEVT4) == ECAP_ECFLG_CEVT4)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Counter Overflow
    //-------------------------------------------------------------------------
    {
        name: "capOvf",
        displayName: "Counter Overflow Flag",
        type: 'led',
        register: "ECFLG.CTROVF",
        updateFunc: (instBase) => `((HWREGH(${instBase} + ECAP_O_ECFLG) & ECAP_ECFLG_CTROVF) == ECAP_ECFLG_CTROVF)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Compare Match (APWM mode)
    //-------------------------------------------------------------------------
    {
        name: "capCmpMatch",
        displayName: "Compare Match Flag",
        type: 'led',
        register: "ECFLG.CTR_CMP",
        updateFunc: (instBase) => `((HWREGH(${instBase} + ECAP_O_ECFLG) & ECAP_ECFLG_CTR_CMP) == ECAP_ECFLG_CTR_CMP)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Capture Values
    //-------------------------------------------------------------------------
    {
        name: "cap1Value",
        displayName: "Capture 1 Value",
        type: 'value',
        register: "CAP1",
        updateFunc: (instBase) => `HWREG(${instBase} + ECAP_O_CAP1)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },
    {
        name: "cap2Value",
        displayName: "Capture 2 Value",
        type: 'value',
        register: "CAP2",
        updateFunc: (instBase) => `HWREG(${instBase} + ECAP_O_CAP2)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },
    {
        name: "cap3Value",
        displayName: "Capture 3 Value",
        type: 'value',
        register: "CAP3",
        updateFunc: (instBase) => `HWREG(${instBase} + ECAP_O_CAP3)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },
    {
        name: "cap4Value",
        displayName: "Capture 4 Value",
        type: 'value',
        register: "CAP4",
        updateFunc: (instBase) => `HWREG(${instBase} + ECAP_O_CAP4)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Time Stamp Counter
    //-------------------------------------------------------------------------
    {
        name: "tsctr",
        displayName: "Time Stamp Counter",
        type: 'value',
        register: "TSCTR",
        updateFunc: (instBase) => `HWREG(${instBase} + ECAP_O_TSCTR)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // HRCAP Status (devices with high-resolution capture)
    //-------------------------------------------------------------------------
    {
        name: "hrcapCalDone",
        displayName: "HRCAP Calibration Done",
        type: 'led',
        register: "HRFLG.CALIBDONE",
        updateFunc: (instBase) => `((HWREGH(${instBase} + HRCAP_O_HRFLG) & HRCAP_HRFLG_CALIBDONE) == HRCAP_HRFLG_CALIBDONE)`,
        applicable: (inst) => {
            return DEVICES_WITH_HRCAP.includes(deviceName);
        }
    },
];

//-----------------------------------------------------------------------------
// Bitfield Instance Name Mapping
//-----------------------------------------------------------------------------
let bitfieldInstanceNames = {
    "default": (instName) => { return "ECap" + instName + "Regs" },
};

//-----------------------------------------------------------------------------
// Registers to Skip (Read-to-Clear and Force registers)
//-----------------------------------------------------------------------------
let exportsRegisterSkips = [
    // Time stamp counter changes rapidly
    // { name: "TSCTR", register: "TSCTR" },

    // Read-to-Clear registers (R/W1C - Write 1 to Clear)
    { name: "ECCLR", register: "ECAPECCLR" },
    // Force registers (Write-Only - Force trigger)
    { name: "ECFRC", register: "ECAPECFRC" },
];

//-----------------------------------------------------------------------------
// Module Exports
//-----------------------------------------------------------------------------
exports = {
    exportsInfo: exportsInfo,
    bitfieldInstanceNames: bitfieldInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
}
