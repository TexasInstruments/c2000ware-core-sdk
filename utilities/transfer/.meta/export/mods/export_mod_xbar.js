//=============================================================================
// export_mod_xbar.js - XBAR Export Module for CDT
//=============================================================================
// Purpose: Expose Crossbar diagnostic information for CDT
// Devices: All Gen3 devices
//=============================================================================

const exportCommon = system.getScript("/utilities/transfer/export/export_mods_common.js");
const { getDeviceName } = exportCommon;
const deviceName = getDeviceName();

const DEVICES_WITH_XBAR = [
    "F280013x", "F280015x", "F28002x", "F28003x", "F28004x",
    "F2807x", "F2837xD", "F2837xS", "F2838x", "F28P55x", "F28P65x"
];

let exportsInfo = [
    //-------------------------------------------------------------------------
    // XBAR Flag Registers (read-only status for diagnostics)
    //-------------------------------------------------------------------------
    {
        name: "FLG1",
        displayName: "XBAR Flag 1 (CMPSS Trips)",
        type: 'value',
        register: "XBARFLG1",
        updateFunc: (instBase) => `HWREG(XBAR_BASE + XBAR_O_FLG1)`,
        applicable: (inst) => {
            return DEVICES_WITH_XBAR.includes(deviceName);
        }
    },
    {
        name: "FLG2",
        displayName: "XBAR Flag 2 (Inputs/ADC)",
        type: 'value',
        register: "XBARFLG2",
        updateFunc: (instBase) => `HWREG(XBAR_BASE + XBAR_O_FLG2)`,
        applicable: (inst) => {
            return DEVICES_WITH_XBAR.includes(deviceName);
        }
    },
    {
        name: "FLG3",
        displayName: "XBAR Flag 3 (ADC/SDFM)",
        type: 'value',
        register: "XBARFLG3",
        updateFunc: (instBase) => `HWREG(XBAR_BASE + XBAR_O_FLG3)`,
        applicable: (inst) => {
            return DEVICES_WITH_XBAR.includes(deviceName);
        }
    },
    {
        name: "FLG4",
        displayName: "XBAR Flag 4 (CLB/Error)",
        type: 'value',
        register: "XBARFLG4",
        updateFunc: (instBase) => `HWREG(XBAR_BASE + XBAR_O_FLG4)`,
        applicable: (inst) => {
            return DEVICES_WITH_XBAR.includes(deviceName);
        }
    },
    //-------------------------------------------------------------------------
    // XBAR Configuration (for verification)
    //-------------------------------------------------------------------------
    {
        name: "INPUTXBAR1",
        displayName: "Input XBAR 1 Select",
        type: 'value',
        register: "INPUT1SELECT",
        updateFunc: (instBase) => `HWREG(INPUTXBAR_BASE + XBAR_O_INPUT1SELECT)`,
        applicable: (inst) => {
            return DEVICES_WITH_XBAR.includes(deviceName);
        }
    },
];

let bitfieldInstanceNames = {
    "default": (instName) => { return "XbarRegs" },
};

//-----------------------------------------------------------------------------
// Registers to Skip (Write-1-to-Clear flag clear registers)
//-----------------------------------------------------------------------------
let exportsRegisterSkips = [
    { name: "CLR1", register: "XBARCLR1" },
    { name: "CLR2", register: "XBARCLR2" },
    { name: "CLR3", register: "XBARCLR3" },
    { name: "CLR4", register: "XBARCLR4" },
];

exports = {
    exportsInfo: exportsInfo,
    bitfieldInstanceNames: bitfieldInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
}
