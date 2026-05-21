//=============================================================================
// export_mod_sent.js - SENT Export Module for CDT
//=============================================================================
// Purpose: Expose Single Edge Nibble Transmission diagnostic information for CDT
// Devices: F28003x, F28004x, F28P55x, F28P65x
//=============================================================================

const exportCommon = system.getScript("/utilities/transfer/export/export_mods_common.js");
const { getDeviceName } = exportCommon;
const deviceName = getDeviceName();

const DEVICES_WITH_SENT = [
    "F28003x", "F28004x", "F28P55x", "F28P65x"
];

let exportsInfo = [
    {
        name: "DNRDY",
        displayName: "Data Not Ready",
        type: 'led',
        register: "SENTSTS.DNRDY",
        updateFunc: (instBase) => `((HWREGH(${instBase} + SENT_O_STS) & SENT_STS_DNRDY) == SENT_STS_DNRDY)`,
        applicable: (inst) => {
            return DEVICES_WITH_SENT.includes(deviceName);
        }
    },
    {
        name: "CRCERR",
        displayName: "CRC Error",
        type: 'led',
        register: "SENTSTS.CRCERR",
        updateFunc: (instBase) => `((HWREGH(${instBase} + SENT_O_STS) & SENT_STS_CRCERR) == SENT_STS_CRCERR)`,
        applicable: (inst) => {
            return DEVICES_WITH_SENT.includes(deviceName);
        }
    },
    {
        name: "FRMERR",
        displayName: "Frame Error",
        type: 'led',
        register: "SENTSTS.FRMERR",
        updateFunc: (instBase) => `((HWREGH(${instBase} + SENT_O_STS) & SENT_STS_FRMERR) == SENT_STS_FRMERR)`,
        applicable: (inst) => {
            return DEVICES_WITH_SENT.includes(deviceName);
        }
    },
    {
        name: "SYNCERR",
        displayName: "Sync Error",
        type: 'led',
        register: "SENTSTS.SYNCERR",
        updateFunc: (instBase) => `((HWREGH(${instBase} + SENT_O_STS) & SENT_STS_SYNCERR) == SENT_STS_SYNCERR)`,
        applicable: (inst) => {
            return DEVICES_WITH_SENT.includes(deviceName);
        }
    },
];

let bitfieldInstanceNames = {
    "default": (instName) => { return "Sent" + instName + "Regs" },
};

let exportsRegisterSkips = [];

exports = {
    exportsInfo: exportsInfo,
    bitfieldInstanceNames: bitfieldInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
}
