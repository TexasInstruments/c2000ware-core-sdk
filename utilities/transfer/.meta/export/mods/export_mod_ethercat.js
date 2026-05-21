//=============================================================================
// export_mod_ethercat.js - EtherCAT Export Module for CDT
//=============================================================================
// Purpose: Expose EtherCAT diagnostic information for CDT
// Devices: F2838x (CM core)
//=============================================================================

const exportCommon = system.getScript("/utilities/transfer/export/export_mods_common.js");
const { getDeviceName } = exportCommon;
const deviceName = getDeviceName();

const DEVICES_WITH_ETHERCAT = [
    "F2838x"
];

let exportsInfo = [
    {
        name: "ALSTATUS",
        displayName: "AL Status",
        type: 'value',
        register: "AL_STATUS",
        updateFunc: (instBase) => `HWREGH(${instBase} + ESC_O_AL_STATUS)`,
        applicable: (inst) => {
            return DEVICES_WITH_ETHERCAT.includes(deviceName);
        }
    },
    {
        name: "ALCONTROL",
        displayName: "AL Control",
        type: 'value',
        register: "AL_CONTROL",
        updateFunc: (instBase) => `HWREGH(${instBase} + ESC_O_AL_CONTROL)`,
        applicable: (inst) => {
            return DEVICES_WITH_ETHERCAT.includes(deviceName);
        }
    },
    {
        name: "WDSTATUS",
        displayName: "Watchdog Status",
        type: 'led',
        register: "WD_STATUS",
        updateFunc: (instBase) => `((HWREGH(${instBase} + ESC_O_WD_STATUS) & 0x01) == 0x01)`,
        applicable: (inst) => {
            return DEVICES_WITH_ETHERCAT.includes(deviceName);
        }
    },
    {
        name: "PORTLINK0",
        displayName: "Port 0 Link",
        type: 'led',
        register: "PHY_STATUS",
        updateFunc: (instBase) => `((HWREGH(${instBase} + ESC_O_DL_STATUS) & 0x10) == 0x10)`,
        applicable: (inst) => {
            return DEVICES_WITH_ETHERCAT.includes(deviceName);
        }
    },
];

let bitfieldInstanceNames = {
    "default": (instName) => { return "EscRegs" },
};

let exportsRegisterSkips = [];

exports = {
    exportsInfo: exportsInfo,
    bitfieldInstanceNames: bitfieldInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
}
