//=============================================================================
// export_mod_nmi.js - NMI Export Module for CDT
//=============================================================================
// Purpose: Expose Non-Maskable Interrupt diagnostic information for CDT
// Location: C2000Ware/.../utilities/transfer/.meta/export/mods/
//
// Reference Documents:
//   - Device TRM: NMI chapter
//   - driverlib/<device>/driverlib/sysctl.h (NMI functions)
//   - driverlib/<device>/driverlib/inc/hw_nmi.h
//=============================================================================

const exportCommon = system.getScript("/utilities/transfer/export/export_mods_common.js");
const { DEVICES_WITH_CDT_SUPPORT, getDeviceName } = exportCommon;
const deviceName = getDeviceName();

// Devices with CLB NMI flag (validated against hw_nmi.h NMI_FLG_CLBNMI)
const DEVICES_WITH_CLB_NMI = [
    "F28002x", "F28003x", "F28004x", "F2807x", "F2837xD", "F2837xS", "F2838x", "F28P55x", "F28P65x"
];

// Devices with BGCRC NMI flag
// Note: F2807x, F2837xD, F2837xS do not have BGCRC hardware - removed from list
const DEVICES_WITH_CRC_NMI = [
    "F28002x", "F28003x", "F2838x", "F28P55x", "F28P65x"
];

// Devices with separate RAM/Flash NMI flags
const DEVICES_WITH_SEPARATE_MEM_NMI = [
    "F28002x", "F28003x", "F28004x", "F2807x", "F2837xD", "F2837xS", "F2838x", "F28P55x"
];

//-----------------------------------------------------------------------------
// Export Information - Diagnostic Indicators
//-----------------------------------------------------------------------------
let exportsInfo = [
    //-------------------------------------------------------------------------
    // NMI Enable Status
    //-------------------------------------------------------------------------
    {
        name: "nmiEnabled",
        displayName: "NMI Globally Enabled",
        type: 'led',
        register: "CFG.NMIE",
        updateFunc: (instBase) => `((HWREGH(NMI_BASE + NMI_O_CFG) & NMI_CFG_NMIE) == NMI_CFG_NMIE)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Global NMI Flag
    //-------------------------------------------------------------------------
    {
        name: "nmiFlag",
        displayName: "NMI Interrupt Occurred",
        type: 'led',
        register: "FLG.NMIINT",
        updateFunc: (instBase) => `((HWREGH(NMI_BASE + NMI_O_FLG) & NMI_FLG_NMIINT) == NMI_FLG_NMIINT)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Clock Fail NMI
    //-------------------------------------------------------------------------
    {
        name: "nmiClockFail",
        displayName: "Clock Fail (NMI)",
        type: 'led',
        register: "FLG.CLOCKFAIL",
        updateFunc: (instBase) => `((HWREGH(NMI_BASE + NMI_O_FLG) & NMI_FLG_CLOCKFAIL) == NMI_FLG_CLOCKFAIL)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Memory Error NMIs (device-specific)
    //-------------------------------------------------------------------------
    {
        name: "nmiRamUncErr",
        displayName: "RAM Uncorrectable Error (NMI)",
        type: 'led',
        register: "FLG.RAMUNCERR",
        updateFunc: (instBase) => `((HWREGH(NMI_BASE + NMI_O_FLG) & NMI_FLG_RAMUNCERR) == NMI_FLG_RAMUNCERR)`,
        applicable: (inst) => {
            return DEVICES_WITH_SEPARATE_MEM_NMI.includes(deviceName);
        }
    },
    {
        name: "nmiFlashUncErr",
        displayName: "Flash Uncorrectable Error (NMI)",
        type: 'led',
        register: "FLG.FLUNCERR",
        updateFunc: (instBase) => `((HWREGH(NMI_BASE + NMI_O_FLG) & NMI_FLG_FLUNCERR) == NMI_FLG_FLUNCERR)`,
        applicable: (inst) => {
            return DEVICES_WITH_SEPARATE_MEM_NMI.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // HWBIST Error NMI
    //-------------------------------------------------------------------------
    {
        name: "nmiHwBistErr",
        displayName: "HW BIST Error (NMI)",
        type: 'led',
        register: "FLG.CPU1HWBISTERR",
        updateFunc: (instBase) => `((HWREGH(NMI_BASE + NMI_O_FLG) & NMI_FLG_CPU1HWBISTERR) == NMI_FLG_CPU1HWBISTERR)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // System Debug NMI
    //-------------------------------------------------------------------------
    {
        name: "nmiSysDbg",
        displayName: "System Debug (NMI)",
        type: 'led',
        register: "FLG.SYSDBGNMI",
        updateFunc: (instBase) => `((HWREGH(NMI_BASE + NMI_O_FLG) & NMI_FLG_SYSDBGNMI) == NMI_FLG_SYSDBGNMI)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // CLB NMI (Reconfigurable Logic)
    //-------------------------------------------------------------------------
    {
        name: "nmiClb",
        displayName: "CLB/RL (NMI)",
        type: 'led',
        register: "FLG.CLBNMI",
        updateFunc: (instBase) => `((HWREGH(NMI_BASE + NMI_O_FLG) & NMI_FLG_CLBNMI) == NMI_FLG_CLBNMI)`,
        applicable: (inst) => {
            return DEVICES_WITH_CLB_NMI.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Software Error NMI
    //-------------------------------------------------------------------------
    {
        name: "nmiSwErr",
        displayName: "Software Error (NMI)",
        type: 'led',
        register: "FLG.SWERR",
        updateFunc: (instBase) => `((HWREGH(NMI_BASE + NMI_O_FLG) & NMI_FLG_SWERR) == NMI_FLG_SWERR)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // CRC Fail NMI (BGCRC)
    //-------------------------------------------------------------------------
    {
        name: "nmiCrcFail",
        displayName: "CRC Fail (NMI)",
        type: 'led',
        register: "FLG.CRC_FAIL",
        updateFunc: (instBase) => `((HWREGH(NMI_BASE + NMI_O_FLG) & NMI_FLG_CRC_FAIL) == NMI_FLG_CRC_FAIL)`,
        applicable: (inst) => {
            return DEVICES_WITH_CRC_NMI.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // NMI Flag Register (raw value)
    //-------------------------------------------------------------------------
    {
        name: "nmiFlagRaw",
        displayName: "NMI Flag Register",
        type: 'value',
        register: "FLG",
        updateFunc: (instBase) => `HWREGH(NMI_BASE + NMI_O_FLG)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // NMI Shadow Flag Register
    //-------------------------------------------------------------------------
    {
        name: "nmiShadowFlag",
        displayName: "NMI Shadow Flags",
        type: 'value',
        register: "SHDFLG",
        updateFunc: (instBase) => `HWREGH(NMI_BASE + NMI_O_SHDFLG)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // NMI Watchdog Counter
    //-------------------------------------------------------------------------
    {
        name: "nmiWdCnt",
        displayName: "NMI Watchdog Counter",
        type: 'value',
        register: "WDCNT",
        updateFunc: (instBase) => `HWREGH(NMI_BASE + NMI_O_WDCNT)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Error Pin Status
    //-------------------------------------------------------------------------
    {
        name: "errorPinAsserted",
        displayName: "Error Pin Asserted",
        type: 'led',
        register: "ERRORSTS.ERROR",
        updateFunc: (instBase) => `((HWREGH(NMI_BASE + NMI_O_ERRORSTS) & NMI_ERRORSTS_ERROR) == NMI_ERRORSTS_ERROR)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },
    {
        name: "errorPinState",
        displayName: "Error Pin Current State",
        type: 'led',
        register: "ERRORSTS.PINSTS",
        updateFunc: (instBase) => `((HWREGH(NMI_BASE + NMI_O_ERRORSTS) & NMI_ERRORSTS_PINSTS) == NMI_ERRORSTS_PINSTS)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },
];

//-----------------------------------------------------------------------------
// Bitfield Instance Name Mapping
//-----------------------------------------------------------------------------
let bitfieldInstanceNames = {
    "default": (instName) => { return "NmiIntruptRegs" },
};

//-----------------------------------------------------------------------------
// Registers to Skip (Clear and Force registers)
//-----------------------------------------------------------------------------
let exportsRegisterSkips = [
    // NMI Flag Clear (Write-1-to-Clear)
    { name: "FLGCLR", register: "NMI_FLGCLR" },
    // NMI Flag Force (Write-Only)
    { name: "FLGFRC", register: "NMI_FLGFRC" },
    // Error Status Clear (Write-1-to-Clear)
    { name: "ERRORSTSCLR", register: "NMI_ERRORSTSCLR" },
    // Error Status Force (Write-Only)
    { name: "ERRORSTSFRC", register: "NMI_ERRORSTSFRC" },
];

//-----------------------------------------------------------------------------
// Module Exports
//-----------------------------------------------------------------------------
exports = {
    exportsInfo: exportsInfo,
    bitfieldInstanceNames: bitfieldInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
}
