//=============================================================================
// export_mod_syserror.js - System Error Export Module for CDT
//=============================================================================
// Purpose: Expose System Error Interrupt diagnostic information for CDT
// Devices: F280013x, F280015x, F28003x, F2838x, F28P55x, F28P65x
// Reference: driverlib/<device>/driverlib/inc/hw_sysctl.h
//
// System Error registers provide:
// - Global interrupt status
// - AES bus error flags (security module errors)
// - EPGA (Embedded Pattern Generator/Analyzer) interrupt flags
//=============================================================================

const exportCommon = system.getScript("/utilities/transfer/export/export_mods_common.js");
const { getDeviceName } = exportCommon;
const deviceName = getDeviceName();

//-----------------------------------------------------------------------------
// Device Support Constants
//-----------------------------------------------------------------------------
const DEVICES_WITH_SYS_ERROR = [
    "F280013x", "F280015x", "F28003x", "F2838x", "F28P55x", "F28P65x"
];

// Devices with AES module
// Note: F2838x does not have AES hardware - removed to match export_mod_aes.js
const DEVICES_WITH_AES = [
    "F28003x", "F28P55x", "F28P65x"
];

// Devices with EPGA
const DEVICES_WITH_EPGA = [
    "F28003x"
];

let exportsInfo = [
    //-------------------------------------------------------------------------
    // System Error Interrupt Flag Register
    //-------------------------------------------------------------------------
    {
        name: "sysErrIntFlg",
        displayName: "System Error Interrupt Flag",
        type: 'value',
        register: "SYS_ERR_INT_FLG",
        bitfieldInstance: "sysstatus",
        updateFunc: (instBase) => `HWREG(SYSSTATUS_BASE + SYSCTL_O_SYS_ERR_INT_FLG)`,
        applicable: (inst) => {
            return DEVICES_WITH_SYS_ERROR.includes(deviceName);
        }
    },
    {
        name: "sysErrGlobalInt",
        displayName: "Global System Error Interrupt",
        type: 'led',
        register: "SYS_ERR_INT_FLG.GINT",
        bitfieldInstance: "sysstatus",
        updateFunc: (instBase) => `((HWREG(SYSSTATUS_BASE + SYSCTL_O_SYS_ERR_INT_FLG) & SYSCTL_SYS_ERR_INT_FLG_GINT) == SYSCTL_SYS_ERR_INT_FLG_GINT)`,
        applicable: (inst) => {
            return DEVICES_WITH_SYS_ERROR.includes(deviceName);
        }
    },
    {
        name: "aesBusError",
        displayName: "AES Bus Error",
        type: 'led',
        register: "SYS_ERR_INT_FLG.AES_BUS_ERROR",
        bitfieldInstance: "sysstatus",
        updateFunc: (instBase) => `((HWREG(SYSSTATUS_BASE + SYSCTL_O_SYS_ERR_INT_FLG) & SYSCTL_SYS_ERR_INT_FLG_AES_BUS_ERROR) == SYSCTL_SYS_ERR_INT_FLG_AES_BUS_ERROR)`,
        applicable: (inst) => {
            return DEVICES_WITH_AES.includes(deviceName);
        }
    },
    {
        name: "epgaInt",
        displayName: "EPGA Interrupt",
        type: 'led',
        register: "SYS_ERR_INT_FLG.EPGA_INT",
        bitfieldInstance: "sysstatus",
        updateFunc: (instBase) => `((HWREG(SYSSTATUS_BASE + SYSCTL_O_SYS_ERR_INT_FLG) & SYSCTL_SYS_ERR_INT_FLG_EPGA_INT) == SYSCTL_SYS_ERR_INT_FLG_EPGA_INT)`,
        applicable: (inst) => {
            return DEVICES_WITH_EPGA.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // System Error Mask Register (shows which errors are enabled)
    //-------------------------------------------------------------------------
    {
        name: "sysErrMask",
        displayName: "System Error Mask",
        type: 'value',
        register: "SYS_ERR_MASK",
        bitfieldInstance: "sysstatus",
        updateFunc: (instBase) => `HWREG(SYSSTATUS_BASE + SYSCTL_O_SYS_ERR_MASK)`,
        applicable: (inst) => {
            return DEVICES_WITH_SYS_ERROR.includes(deviceName);
        }
    },
];

//-----------------------------------------------------------------------------
// Bitfield Instance Name Mapping
//-----------------------------------------------------------------------------
let bitfieldInstanceNames = {
    "default": (instName) => { return "SysStatusRegs" },
};

//-----------------------------------------------------------------------------
// Registers to Skip (R/W1C Set/Clear registers)
//-----------------------------------------------------------------------------
let exportsRegisterSkips = [
    // System Error Interrupt Clear (R/W1C - Write 1 to Clear)
    { name: "SYS_ERR_INT_CLR", register: "SYSCTL_SYS_ERR_INT_CLR" },
    // System Error Interrupt Set (Write 1 to Set - Force)
    { name: "SYS_ERR_INT_SET", register: "SYSCTL_SYS_ERR_INT_SET" },
];

//-----------------------------------------------------------------------------
// Module Exports
//-----------------------------------------------------------------------------
exports = {
    exportsInfo: exportsInfo,
    bitfieldInstanceNames: bitfieldInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
}
