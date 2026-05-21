//=============================================================================
// export_mod_wwdt.js - WWDT Export Module for CDT
//=============================================================================
// Purpose: Expose Windowed Watchdog Timer diagnostic information for CDT
// Devices: F28003x, F2838x, F28P55x, F28P65x (validated against hw_wwd.h presence)
// Reference: driverlib/<device>/driverlib/inc/hw_wwd.h
//=============================================================================

const exportCommon = system.getScript("/utilities/transfer/export/export_mods_common.js");
const { getDeviceName } = exportCommon;
const deviceName = getDeviceName();

const DEVICES_WITH_WWDT = [
    "F28003x", "F2838x", "F28P55x", "F28P65x"
];

let exportsInfo = [
    {
        name: "WDEN",
        displayName: "Watchdog Enabled",
        type: 'led',
        register: "WWDCNF.WDEN",
        updateFunc: (instBase) => `((HWREG(${instBase} + WWD_O_WWDCNF) & WWD_WWDCNF_WDEN) == WWD_WWDCNF_WDEN)`,
        applicable: (inst) => {
            return DEVICES_WITH_WWDT.includes(deviceName);
        }
    },
    {
        name: "WINMIN_ACTIVE",
        displayName: "Window Min Active",
        type: 'led',
        register: "WWDSTS.WINMIN",
        updateFunc: (instBase) => `((HWREG(${instBase} + WWD_O_WWDSTS) & WWD_WWDSTS_WINMIN) == WWD_WWDSTS_WINMIN)`,
        applicable: (inst) => {
            return DEVICES_WITH_WWDT.includes(deviceName);
        }
    },
    {
        name: "EVENT_FIRED",
        displayName: "Event Fired",
        type: 'led',
        register: "WWDSTS.EVTFIRED",
        updateFunc: (instBase) => `((HWREG(${instBase} + WWD_O_WWDSTS) & WWD_WWDSTS_EVTFIRED) == WWD_WWDSTS_EVTFIRED)`,
        applicable: (inst) => {
            return DEVICES_WITH_WWDT.includes(deviceName);
        }
    },
    {
        name: "WWDCNT",
        displayName: "Watchdog Counter",
        type: 'value',
        register: "WWDCNT",
        updateFunc: (instBase) => `HWREG(${instBase} + WWD_O_WWDCNT)`,
        applicable: (inst) => {
            return DEVICES_WITH_WWDT.includes(deviceName);
        }
    },
];

let bitfieldInstanceNames = {
    "default": (instName) => { return "EradWwdt" + instName + "Regs" },
};

let exportsRegisterSkips = [];

exports = {
    exportsInfo: exportsInfo,
    bitfieldInstanceNames: bitfieldInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
}
