//=============================================================================
// export_mod_mcbsp.js - McBSP Export Module for CDT
//=============================================================================
// Purpose: Expose Multichannel Buffered Serial Port diagnostic info for CDT
// Devices: F2837xD, F2837xS
//=============================================================================

const exportCommon = system.getScript("/utilities/transfer/export/export_mods_common.js");
const { getDeviceName } = exportCommon;
const deviceName = getDeviceName();

const DEVICES_WITH_MCBSP = [
    "F2837xD", "F2837xS"
];

let exportsInfo = [
    {
        name: "XRDY",
        displayName: "Transmitter Ready",
        type: 'led',
        register: "SPCR2.XRDY",
        updateFunc: (instBase) => `((HWREGH(${instBase} + MCBSP_O_SPCR2) & MCBSP_SPCR2_XRDY) == MCBSP_SPCR2_XRDY)`,
        applicable: (inst) => {
            return DEVICES_WITH_MCBSP.includes(deviceName);
        }
    },
    {
        name: "RRDY",
        displayName: "Receiver Ready",
        type: 'led',
        register: "SPCR1.RRDY",
        updateFunc: (instBase) => `((HWREGH(${instBase} + MCBSP_O_SPCR1) & MCBSP_SPCR1_RRDY) == MCBSP_SPCR1_RRDY)`,
        applicable: (inst) => {
            return DEVICES_WITH_MCBSP.includes(deviceName);
        }
    },
    {
        name: "XSYNCERR",
        displayName: "Transmit Sync Error",
        type: 'led',
        register: "SPCR2.XSYNCERR",
        updateFunc: (instBase) => `((HWREGH(${instBase} + MCBSP_O_SPCR2) & MCBSP_SPCR2_XSYNCERR) == MCBSP_SPCR2_XSYNCERR)`,
        applicable: (inst) => {
            return DEVICES_WITH_MCBSP.includes(deviceName);
        }
    },
    {
        name: "RSYNCERR",
        displayName: "Receive Sync Error",
        type: 'led',
        register: "SPCR1.RSYNCERR",
        updateFunc: (instBase) => `((HWREGH(${instBase} + MCBSP_O_SPCR1) & MCBSP_SPCR1_RSYNCERR) == MCBSP_SPCR1_RSYNCERR)`,
        applicable: (inst) => {
            return DEVICES_WITH_MCBSP.includes(deviceName);
        }
    },
];

let bitfieldInstanceNames = {
    "default": (instName) => { return "McBsp" + instName + "Regs" },
};

let exportsRegisterSkips = [];

exports = {
    exportsInfo: exportsInfo,
    bitfieldInstanceNames: bitfieldInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
}
