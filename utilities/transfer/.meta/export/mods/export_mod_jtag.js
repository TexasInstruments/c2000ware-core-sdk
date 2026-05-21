//=============================================================================
// export_mod_jtag.js - JTAG Export Module for CDT
//=============================================================================
// Purpose: Expose JTAG debug interface diagnostic information for CDT
// Devices: All Gen3 devices
//=============================================================================

const exportCommon = system.getScript("/utilities/transfer/export/export_mods_common.js");
const { getDeviceName } = exportCommon;
const deviceName = getDeviceName();

const DEVICES_WITH_JTAG = [
    "F280013x", "F280015x", "F28002x", "F28003x", "F28004x",
    "F2807x", "F2837xD", "F2837xS", "F2838x", "F28P55x", "F28P65x"
];

let exportsInfo = [
    {
        name: "JTAGDIS",
        displayName: "JTAG Disabled",
        type: 'led',
        register: "Z1OTP.JTAGDIS",
        updateFunc: (instBase) => `((HWREG(DCSM_Z1OTP_BASE + DCSM_O_Z1OTP_JTAGPSWDL0) == 0xFFFFFFFF) ? 0 : 1)`,
        applicable: (inst) => {
            return DEVICES_WITH_JTAG.includes(deviceName);
        }
    },
    {
        name: "TRST",
        displayName: "JTAG TRST Pin Status",
        // TODO: TRST status register access is device-specific; implement per TRM
        // Returning false as safe default until properly implemented
        type: 'led',
        register: "JTAG.TRST",
        updateFunc: (instBase) => `false`,
        ledValues: { true: "ASSERTED", false: "NOT_ASSERTED" },
        applicable: (inst) => {
            return DEVICES_WITH_JTAG.includes(deviceName);
        }
    },
];

let bitfieldInstanceNames = {
    "default": (instName) => { return "JtagRegs" },
};

let exportsRegisterSkips = [];

exports = {
    exportsInfo: exportsInfo,
    bitfieldInstanceNames: bitfieldInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
}
