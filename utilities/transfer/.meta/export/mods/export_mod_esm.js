//=============================================================================
// export_mod_esm.js - ESM Export Module for CDT
//=============================================================================
// Purpose: Expose Error Signaling Module diagnostic information for CDT
// Devices: F28P55x, F28P65x
//=============================================================================

const exportCommon = system.getScript("/utilities/transfer/export/export_mods_common.js");
const { getDeviceName } = exportCommon;
const deviceName = getDeviceName();

const DEVICES_WITH_ESM = [
    "F28P55x", "F28P65x"
];

let exportsInfo = [
    {
        name: "GBLSTS",
        displayName: "Global Error Status",
        type: 'led',
        register: "ESMSTS.GBLSTS",
        updateFunc: (instBase) => `((HWREG(${instBase} + ESM_CPU_O_ESMSTS) & ESM_CPU_ESMSTS_GBLSTS) == ESM_CPU_ESMSTS_GBLSTS)`,
        applicable: (inst) => {
            return DEVICES_WITH_ESM.includes(deviceName);
        }
    },
    {
        name: "CFGERR",
        displayName: "Configuration Error",
        type: 'led',
        register: "ESMSTS.CFGERR",
        updateFunc: (instBase) => `((HWREG(${instBase} + ESM_CPU_O_ESMSTS) & ESM_CPU_ESMSTS_CFGERR) == ESM_CPU_ESMSTS_CFGERR)`,
        applicable: (inst) => {
            return DEVICES_WITH_ESM.includes(deviceName);
        }
    },
    {
        name: "LOW_RAW",
        displayName: "Low Priority Raw Status",
        type: 'value',
        register: "ESMLPR",
        updateFunc: (instBase) => `HWREG(${instBase} + ESM_CPU_O_LOW_PRI_RAW)`,
        applicable: (inst) => {
            return DEVICES_WITH_ESM.includes(deviceName);
        }
    },
    {
        name: "HIGH_RAW",
        displayName: "High Priority Raw Status",
        type: 'value',
        register: "ESMHPR",
        updateFunc: (instBase) => `HWREG(${instBase} + ESM_CPU_O_HI_PRI_RAW)`,
        applicable: (inst) => {
            return DEVICES_WITH_ESM.includes(deviceName);
        }
    },
];

let bitfieldInstanceNames = {
    "default": (instName) => { return "EsmCpuRegs" },
};

let exportsRegisterSkips = [];

exports = {
    exportsInfo: exportsInfo,
    bitfieldInstanceNames: bitfieldInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
}
