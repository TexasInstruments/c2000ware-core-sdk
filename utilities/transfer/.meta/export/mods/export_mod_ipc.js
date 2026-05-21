//=============================================================================
// export_mod_ipc.js - IPC Export Module for CDT
//=============================================================================
// Purpose: Expose Inter-Processor Communication diagnostic information for CDT
// Devices: F2837xD, F2838x, F28P65x (dual-core devices)
//=============================================================================

const exportCommon = system.getScript("/utilities/transfer/export/export_mods_common.js");
const { getDeviceName } = exportCommon;
const deviceName = getDeviceName();

const DEVICES_WITH_IPC = [
    "F2837xD", "F2838x", "F28P65x"
];

let exportsInfo = [
    {
        name: "IPCFLG",
        displayName: "IPC Flag Status",
        type: 'value',
        register: "IPCSTS.FLG",
        updateFunc: (instBase) => `HWREG(${instBase} + IPC_O_STS)`,
        applicable: (inst) => {
            return DEVICES_WITH_IPC.includes(deviceName);
        }
    },
    {
        name: "IPCACK",
        displayName: "IPC Acknowledge Status",
        type: 'value',
        register: "IPCACK",
        updateFunc: (instBase) => `HWREG(${instBase} + IPC_O_ACK)`,
        applicable: (inst) => {
            return DEVICES_WITH_IPC.includes(deviceName);
        }
    },
    {
        name: "IPCBOOTSTS",
        displayName: "IPC Boot Status",
        type: 'value',
        register: "IPCBOOTSTS",
        updateFunc: (instBase) => `HWREG(${instBase} + IPC_O_BOOTSTS)`,
        applicable: (inst) => {
            return DEVICES_WITH_IPC.includes(deviceName);
        }
    },
    {
        name: "IPCBOOTMODE",
        displayName: "IPC Boot Mode",
        type: 'value',
        register: "IPCBOOTMODE",
        updateFunc: (instBase) => `HWREG(${instBase} + IPC_O_BOOTMODE)`,
        applicable: (inst) => {
            return DEVICES_WITH_IPC.includes(deviceName);
        }
    },
];

let bitfieldInstanceNames = {
    "default": (instName) => { return "IpcRegs" },
};

let exportsRegisterSkips = [];

exports = {
    exportsInfo: exportsInfo,
    bitfieldInstanceNames: bitfieldInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
}
