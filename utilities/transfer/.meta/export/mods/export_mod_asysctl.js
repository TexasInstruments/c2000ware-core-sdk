//=============================================================================
// export_mod_asysctl.js - Analog System Control Export Module for CDT
//=============================================================================
// Purpose: Expose Analog System Control diagnostic information for CDT
// Location: C2000Ware/.../utilities/transfer/.meta/export/mods/
//
// Reference Documents:
//   - Device TRM: ASYSCTL chapter
//   - driverlib/<device>/driverlib/asysctl.h
//   - driverlib/<device>/driverlib/inc/hw_asysctl.h
//=============================================================================

const exportCommon = system.getScript("/utilities/transfer/export/export_mods_common.js");
const { DEVICES_WITH_CDT_SUPPORT, DEVICES_WITH_VMON, DEVICES_WITH_LOOPBACK, getDeviceName } = exportCommon;
const deviceName = getDeviceName();

// Devices with temperature sensor (all Gen3 devices)
const DEVICES_WITH_TSNS = DEVICES_WITH_CDT_SUPPORT;

// Devices with ANAREFCTL register (all Gen3 devices)
const DEVICES_WITH_ANAREF = DEVICES_WITH_CDT_SUPPORT;

// Note: DEVICES_WITH_VMON and DEVICES_WITH_LOOPBACK imported from export_mods_common.js

//-----------------------------------------------------------------------------
// Export Information - Diagnostic Indicators
//-----------------------------------------------------------------------------
let exportsInfo = [
    //-------------------------------------------------------------------------
    // Temperature Sensor Status
    //-------------------------------------------------------------------------
    {
        name: "tempSensorEnabled",
        displayName: "Temperature Sensor Enabled",
        type: 'led',
        register: "TSNSCTL.ENABLE",
        updateFunc: (instBase) => `((HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_TSNSCTL) & ASYSCTL_TSNSCTL_ENABLE) == ASYSCTL_TSNSCTL_ENABLE)`,
        applicable: (inst) => {
            return DEVICES_WITH_TSNS.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Analog Reference Configuration
    //-------------------------------------------------------------------------
    {
        name: "anaRefInternal",
        displayName: "Internal Analog Reference",
        type: 'led',
        register: "ANAREFCTL.ANAREFSEL",
        // 0 = External, 1 = Internal
        updateFunc: (instBase) => `((HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_ANAREFCTL) & ASYSCTL_ANAREFCTL_ANAREFSEL) == ASYSCTL_ANAREFCTL_ANAREFSEL)`,
        applicable: (inst) => {
            return DEVICES_WITH_ANAREF.includes(deviceName);
        }
    },
    {
        name: "anaRef2p5Sel",
        displayName: "2.5V Analog Reference",
        type: 'led',
        register: "ANAREFCTL.ANAREF2P5SEL",
        // 0 = VDDA, 1 = 2.5V internal reference
        updateFunc: (instBase) => `((HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_ANAREFCTL) & ASYSCTL_ANAREFCTL_ANAREF2P5SEL) == ASYSCTL_ANAREFCTL_ANAREF2P5SEL)`,
        applicable: (inst) => {
            return DEVICES_WITH_ANAREF.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Voltage Monitor Status
    //-------------------------------------------------------------------------
    {
        name: "borlvmonDisabled",
        displayName: "BORL Monitor Disabled",
        type: 'led',
        register: "VMONCTL.BORLVMONDIS",
        updateFunc: (instBase) => `((HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_VMONCTL) & ASYSCTL_VMONCTL_BORLVMONDIS) == ASYSCTL_VMONCTL_BORLVMONDIS)`,
        applicable: (inst) => {
            return DEVICES_WITH_VMON.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // ADC-DAC Loopback Status
    //-------------------------------------------------------------------------
    {
        name: "loopbackAdcA",
        displayName: "DAC Loopback to ADCA",
        type: 'led',
        register: "ADCDACLOOPBACK.ENLB2ADCA",
        updateFunc: (instBase) => `((HWREG(ANALOGSUBSYS_BASE + ASYSCTL_O_ADCDACLOOPBACK) & ASYSCTL_ADCDACLOOPBACK_ENLB2ADCA) == ASYSCTL_ADCDACLOOPBACK_ENLB2ADCA)`,
        applicable: (inst) => {
            return DEVICES_WITH_LOOPBACK.includes(deviceName);
        }
    },
    {
        name: "loopbackAdcC",
        displayName: "DAC Loopback to ADCC",
        type: 'led',
        register: "ADCDACLOOPBACK.ENLB2ADCC",
        updateFunc: (instBase) => `((HWREG(ANALOGSUBSYS_BASE + ASYSCTL_O_ADCDACLOOPBACK) & ASYSCTL_ADCDACLOOPBACK_ENLB2ADCC) == ASYSCTL_ADCDACLOOPBACK_ENLB2ADCC)`,
        applicable: (inst) => {
            return DEVICES_WITH_LOOPBACK.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Lock Status
    //-------------------------------------------------------------------------
    {
        name: "tsnsLocked",
        displayName: "TSNSCTL Locked",
        type: 'led',
        register: "LOCK.TSNSCTL",
        updateFunc: (instBase) => `((HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_LOCK) & ASYSCTL_LOCK_TSNSCTL) == ASYSCTL_LOCK_TSNSCTL)`,
        applicable: (inst) => {
            return DEVICES_WITH_TSNS.includes(deviceName);
        }
    },
    {
        name: "anarefLocked",
        displayName: "ANAREFCTL Locked",
        type: 'led',
        register: "LOCK.ANAREFCTL",
        updateFunc: (instBase) => `((HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_LOCK) & ASYSCTL_LOCK_ANAREFCTL) == ASYSCTL_LOCK_ANAREFCTL)`,
        applicable: (inst) => {
            return DEVICES_WITH_ANAREF.includes(deviceName);
        }
    },
    {
        name: "vmonLocked",
        displayName: "VMONCTL Locked",
        type: 'led',
        register: "LOCK.VMONCTL",
        updateFunc: (instBase) => `((HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_LOCK) & ASYSCTL_LOCK_VMONCTL) == ASYSCTL_LOCK_VMONCTL)`,
        applicable: (inst) => {
            return DEVICES_WITH_VMON.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // CMPSS Mux Selections (values for debugging)
    //-------------------------------------------------------------------------
    {
        name: "cmp1hpMuxSel",
        displayName: "CMP1 HP Mux Selection",
        type: 'value',
        register: "CMPHPMXSEL.CMP1HPMXSEL",
        updateFunc: (instBase) => `((HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_CMPHPMXSEL) & ASYSCTL_CMPHPMXSEL_CMP1HPMXSEL_M) >> ASYSCTL_CMPHPMXSEL_CMP1HPMXSEL_S)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },
    {
        name: "cmp1lpMuxSel",
        displayName: "CMP1 LP Mux Selection",
        type: 'value',
        register: "CMPLPMXSEL.CMP1LPMXSEL",
        updateFunc: (instBase) => `((HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_CMPLPMXSEL) & ASYSCTL_CMPLPMXSEL_CMP1LPMXSEL_M) >> ASYSCTL_CMPLPMXSEL_CMP1LPMXSEL_S)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },
];

//-----------------------------------------------------------------------------
// Bitfield Instance Name Mapping
//-----------------------------------------------------------------------------
let bitfieldInstanceNames = {
    "default": (instName) => { return "AnalogSubsysRegs" },
};

//-----------------------------------------------------------------------------
// Registers to Skip
//-----------------------------------------------------------------------------
let exportsRegisterSkips = [
    // Internal test registers (should not read in production)
    { name: "INTERNALTESTCTL", register: "ASYSCTL_INTERNALTESTCTL" },
];

//-----------------------------------------------------------------------------
// Module Exports
//-----------------------------------------------------------------------------
exports = {
    exportsInfo: exportsInfo,
    bitfieldInstanceNames: bitfieldInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
}
