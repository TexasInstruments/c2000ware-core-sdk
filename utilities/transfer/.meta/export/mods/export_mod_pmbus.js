//=============================================================================
// export_mod_pmbus.js - PMBus Export Module for CDT
//=============================================================================
// Purpose: Expose PMBus diagnostic information for CDT
// Devices: F280015x, F28002x, F28003x, F28004x, F2838x, F28P55x, F28P65x
// Reference: driverlib/<device>/driverlib/inc/hw_pmbus.h
//=============================================================================

const exportCommon = system.getScript("/utilities/transfer/export/export_mods_common.js");
const { getDeviceName } = exportCommon;
const deviceName = getDeviceName();

// PMBus availability (validated against hw_pmbus.h presence in driverlib)
const DEVICES_WITH_PMBUS = [
    "F280015x", "F28002x", "F28003x", "F28004x", "F2838x", "F28P55x", "F28P65x"
];

let exportsInfo = [
    {
        name: "DATAREQ",
        displayName: "Data Request",
        type: 'led',
        register: "PMBSTS.DATAREQ",
        updateFunc: (instBase) => `((HWREGH(${instBase} + PMBUS_O_PMBSTS) & PMBUS_PMBSTS_DATAREQ) == PMBUS_PMBSTS_DATAREQ)`,
        applicable: (inst) => {
            return DEVICES_WITH_PMBUS.includes(deviceName);
        }
    },
    {
        name: "NACK",
        displayName: "Not Acknowledge",
        type: 'led',
        register: "PMBSTS.NACK",
        updateFunc: (instBase) => `((HWREGH(${instBase} + PMBUS_O_PMBSTS) & PMBUS_PMBSTS_NACK) == PMBUS_PMBSTS_NACK)`,
        applicable: (inst) => {
            return DEVICES_WITH_PMBUS.includes(deviceName);
        }
    },
    {
        name: "PECDATAVALID",
        displayName: "PEC Data Valid/Invalid",
        type: 'led',
        register: "PMBSTS.PEC_VALID",
        updateFunc: (instBase) => `((HWREGH(${instBase} + PMBUS_O_PMBSTS) & PMBUS_PMBSTS_PEC_VALID) == PMBUS_PMBSTS_PEC_VALID)`,
        applicable: (inst) => {
            return DEVICES_WITH_PMBUS.includes(deviceName);
        }
    },
    {
        name: "ALERTEDGE",
        displayName: "Alert Edge Detection",
        type: 'led',
        register: "PMBSTS.ALERT_EDGE",
        updateFunc: (instBase) => `((HWREGH(${instBase} + PMBUS_O_PMBSTS) & PMBUS_PMBSTS_ALERT_EDGE) == PMBUS_PMBSTS_ALERT_EDGE)`,
        applicable: (inst) => {
            return DEVICES_WITH_PMBUS.includes(deviceName);
        }
    },
];

let bitfieldInstanceNames = {
    "default": (instName) => { return "Pmbus" + instName + "Regs" },
};

let exportsRegisterSkips = [];

exports = {
    exportsInfo: exportsInfo,
    bitfieldInstanceNames: bitfieldInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
}
