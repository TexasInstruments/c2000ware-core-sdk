//=============================================================================
// export_mod_emif.js - EMIF Export Module for CDT
//=============================================================================
// Purpose: Expose External Memory Interface diagnostic information for CDT
// Devices: F2837xD, F2837xS, F2838x, F28P65x
//=============================================================================

const exportCommon = system.getScript("/utilities/transfer/export/export_mods_common.js");
const { getDeviceName } = exportCommon;
const deviceName = getDeviceName();

const DEVICES_WITH_EMIF = [
    "F2837xD", "F2837xS", "F2838x", "F28P65x"
];

let exportsInfo = [
    {
        name: "asyncCs2MaxWait",
        displayName: "Async CS2 Max External Wait (nonzero = configured)",
        description: "Async CS2 Max External Wait (nonzero = configured)",
        type: 'led',
        register: "EMIF1.ASYNC_WCCR.MAX_EXT_WAIT",
        updateFunc: (instBase) => `((HWREG(${instBase} + EMIF_O_ASYNC_WCCR) & EMIF_ASYNC_WCCR_MAX_EXT_WAIT_M) != 0)`,
        ledValues: { true: "CONFIGURED", false: "ZERO" },
        applicable: (inst) => {
            return DEVICES_WITH_EMIF.includes(deviceName);
        }
    },
    {
        name: "SDRAMSTS",
        displayName: "SDRAM Status",
        type: 'value',
        register: "SDRAM_TR",
        updateFunc: (instBase) => `HWREG(${instBase} + EMIF_O_SDRAM_TR)`,
        applicable: (inst) => {
            return DEVICES_WITH_EMIF.includes(deviceName);
        }
    },
    {
        name: "CS2CFG",
        displayName: "CS2 Config",
        type: 'value',
        register: "ASYNC_CS2_CR",
        updateFunc: (instBase) => `HWREG(${instBase} + EMIF_O_ASYNC_CS2_CR)`,
        applicable: (inst) => {
            return DEVICES_WITH_EMIF.includes(deviceName);
        }
    },
];

let bitfieldInstanceNames = {
    "default": (instName) => { return "Emif" + instName + "Regs" },
};

let exportsRegisterSkips = [];

exports = {
    exportsInfo: exportsInfo,
    bitfieldInstanceNames: bitfieldInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
}
