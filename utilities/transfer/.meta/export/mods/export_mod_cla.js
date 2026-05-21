//=============================================================================
// export_mod_cla.js - CLA Export Module for CDT
//=============================================================================
// Purpose: Expose Control Law Accelerator diagnostic information for CDT
// Devices: F28003x, F28004x, F2807x, F2837xD/S, F2838x, F28P55x, F28P65x
//=============================================================================

const exportCommon = system.getScript("/utilities/transfer/export/export_mods_common.js");
const { DEVICES_WITH_CLA, getDeviceName } = exportCommon;
const deviceName = getDeviceName();

let exportsInfo = [
    {
        name: "MIER",
        displayName: "CLA Interrupt Enable",
        type: 'value',
        register: "MIER",
        updateFunc: (instBase) => `HWREGH(${instBase} + CLA_O_MIER)`,
        applicable: (inst) => {
            return DEVICES_WITH_CLA.includes(deviceName);
        }
    },
    {
        name: "MIRUN",
        displayName: "CLA Task Running",
        type: 'value',
        register: "MIRUN",
        updateFunc: (instBase) => `HWREGH(${instBase} + CLA_O_MIRUN)`,
        applicable: (inst) => {
            return DEVICES_WITH_CLA.includes(deviceName);
        }
    },
    {
        name: "SOFTINTEN",
        displayName: "Software Interrupt Enable",
        type: 'value',
        register: "SOFTINTEN",
        updateFunc: (instBase) => `HWREGH(${instBase} + CLA_O_SOFTINTEN)`,
        applicable: (inst) => {
            return DEVICES_WITH_CLA.includes(deviceName);
        }
    },
];

let bitfieldInstanceNames = {
    "default": (instName) => { return "Cla" + instName + "Regs" },
};

let exportsRegisterSkips = [];

exports = {
    exportsInfo: exportsInfo,
    bitfieldInstanceNames: bitfieldInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
}
