//=============================================================================
// export_mod_hrcap.js - HRCAP Export Module for CDT
//=============================================================================
// Purpose: Expose High Resolution Capture diagnostic information for CDT
// Devices: F28003x, F28004x, F2838x, F28P55x, F28P65x
//=============================================================================

const exportCommon = system.getScript("/utilities/transfer/export/export_mods_common.js");
const { getDeviceName } = exportCommon;
const deviceName = getDeviceName();

const DEVICES_WITH_HRCAP = [
    "F28003x", "F28004x", "F2838x", "F28P55x", "F28P65x"
];

let exportsInfo = [
    {
        name: "CALIBDONE",
        displayName: "HRCAP Calibration Done",
        type: 'led',
        register: "HRCAP.HRCTL",
        updateFunc: (instBase) => `((HWREGH(${instBase} + HRCAP_O_HRCTL) & HRCAP_HRCTL_CALIBDONE) == HRCAP_HRCTL_CALIBDONE)`,
        applicable: (inst) => {
            return DEVICES_WITH_HRCAP.includes(deviceName);
        }
    },
    {
        name: "CALPRDCHKSTS",
        displayName: "Calibration Period Check Status",
        type: 'led',
        register: "HRCAP.HRFLG",
        updateFunc: (instBase) => `((HWREGH(${instBase} + HRCAP_O_HRFLG) & HRCAP_HRFLG_CALPRDCHKSTS) == HRCAP_HRFLG_CALPRDCHKSTS)`,
        applicable: (inst) => {
            return DEVICES_WITH_HRCAP.includes(deviceName);
        }
    },
];

let bitfieldInstanceNames = {
    "default": (instName) => { return "HRCap" + instName + "Regs" },
};

let exportsRegisterSkips = [];

exports = {
    exportsInfo: exportsInfo,
    bitfieldInstanceNames: bitfieldInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
}
