//=============================================================================
// export_mod_dcsm.js - DCSM Export Module for CDT
//=============================================================================
// Purpose: Expose Dual Code Security Module diagnostic information for CDT
// Location: C2000Ware/.../utilities/transfer/.meta/export/mods/
//
// Reference Documents:
//   - Device TRM: DCSM chapter
//   - driverlib/<device>/driverlib/dcsm.h
//   - driverlib/<device>/driverlib/inc/hw_dcsm.h
//=============================================================================

const exportCommon = system.getScript("/utilities/transfer/export/export_mods_common.js");
const { DEVICES_WITH_CDT_SUPPORT, getDeviceName } = exportCommon;
const deviceName = getDeviceName();

// Devices with Zone 2
const DEVICES_WITH_ZONE2 = [
    "F28003x", "F28004x", "F2807x", "F2837xD", "F2837xS", "F2838x", "F28P55x", "F28P65x"
];

// Devices with JTAG lock feature
const DEVICES_WITH_JTAGLOCK = [
    "F28003x", "F28P55x", "F28P65x"
];

//-----------------------------------------------------------------------------
// Export Information - Diagnostic Indicators
//-----------------------------------------------------------------------------
let exportsInfo = [
    //-------------------------------------------------------------------------
    // Zone 1 Security Status
    //-------------------------------------------------------------------------
    {
        name: "z1Armed",
        displayName: "Zone 1 Armed",
        type: 'led',
        register: "Z1_CR.ARMED",
        // ARMED bit indicates passwords have been read
        updateFunc: (instBase) => `((HWREG(DCSM_Z1_BASE + DCSM_O_Z1_CR) & DCSM_Z1_CR_ARMED) == DCSM_Z1_CR_ARMED)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },
    {
        name: "z1Unsecure",
        displayName: "Zone 1 Unsecured",
        type: 'led',
        register: "Z1_CR.UNSECURE",
        // UNSECURE bit indicates zone is unlocked
        updateFunc: (instBase) => `((HWREG(DCSM_Z1_BASE + DCSM_O_Z1_CR) & DCSM_Z1_CR_UNSECURE) == DCSM_Z1_CR_UNSECURE)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },
    {
        name: "z1AllZero",
        displayName: "Zone 1 All Zero (Locked)",
        type: 'led',
        register: "Z1_CR.ALLZERO",
        // ALLZERO bit indicates zone is permanently locked
        updateFunc: (instBase) => `((HWREG(DCSM_Z1_BASE + DCSM_O_Z1_CR) & DCSM_Z1_CR_ALLZERO) == DCSM_Z1_CR_ALLZERO)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Zone 2 Security Status
    //-------------------------------------------------------------------------
    {
        name: "z2Armed",
        displayName: "Zone 2 Armed",
        type: 'led',
        register: "Z2_CR.ARMED",
        updateFunc: (instBase) => `((HWREG(DCSM_Z2_BASE + DCSM_O_Z2_CR) & DCSM_Z2_CR_ARMED) == DCSM_Z2_CR_ARMED)`,
        applicable: (inst) => {
            return DEVICES_WITH_ZONE2.includes(deviceName);
        }
    },
    {
        name: "z2Unsecure",
        displayName: "Zone 2 Unsecured",
        type: 'led',
        register: "Z2_CR.UNSECURE",
        updateFunc: (instBase) => `((HWREG(DCSM_Z2_BASE + DCSM_O_Z2_CR) & DCSM_Z2_CR_UNSECURE) == DCSM_Z2_CR_UNSECURE)`,
        applicable: (inst) => {
            return DEVICES_WITH_ZONE2.includes(deviceName);
        }
    },
    {
        name: "z2AllZero",
        displayName: "Zone 2 All Zero (Locked)",
        type: 'led',
        register: "Z2_CR.ALLZERO",
        updateFunc: (instBase) => `((HWREG(DCSM_Z2_BASE + DCSM_O_Z2_CR) & DCSM_Z2_CR_ALLZERO) == DCSM_Z2_CR_ALLZERO)`,
        applicable: (inst) => {
            return DEVICES_WITH_ZONE2.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // JTAG Lock Status
    //-------------------------------------------------------------------------
    {
        name: "jtagLocked",
        displayName: "JTAG Locked",
        type: 'led',
        register: "Z1_JLM_ENABLE",
        // JLM_ENABLE != 0xF indicates JTAG is locked
        updateFunc: (instBase) => `((HWREG(DCSM_Z1_BASE + DCSM_O_Z1_JLM_ENABLE) & 0xF) != 0xF)`,
        applicable: (inst) => {
            return DEVICES_WITH_JTAGLOCK.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Link Pointer Status
    //-------------------------------------------------------------------------
    {
        name: "z1LinkPointer",
        displayName: "Zone 1 Link Pointer",
        type: 'value',
        register: "Z1_LINKPOINTER",
        updateFunc: (instBase) => `(HWREG(DCSM_Z1_BASE + DCSM_O_Z1_LINKPOINTER) & DCSM_Z1_LINKPOINTER_LINKPOINTER_M)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },
    {
        name: "z1LinkPointerErr",
        displayName: "Zone 1 Link Pointer Error",
        type: 'led',
        register: "Z1_LINKPOINTERERR",
        updateFunc: (instBase) => `((HWREG(DCSM_Z1_BASE + DCSM_O_Z1_LINKPOINTERERR) & DCSM_Z1_LINKPOINTERERR_Z1_LINKPOINTERERR_M) != 0)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Security Error Status
    //-------------------------------------------------------------------------
    {
        name: "secError",
        displayName: "Security Error Occurred",
        type: 'led',
        register: "SECERRSTAT",
        updateFunc: (instBase) => `(HWREG(DCSM_COMMON_BASE + DCSM_O_SECERRSTAT) != 0)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },
    {
        name: "secErrorStat",
        displayName: "Security Error Status",
        type: 'value',
        register: "SECERRSTAT",
        updateFunc: (instBase) => `HWREG(DCSM_COMMON_BASE + DCSM_O_SECERRSTAT)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Flash Semaphore Status
    //-------------------------------------------------------------------------
    {
        name: "flashSemaphore",
        displayName: "Flash Semaphore Owner",
        type: 'value',
        register: "FLSEM",
        // 0=Free, 1=Zone1, 2=Zone2
        updateFunc: (instBase) => `(HWREG(DCSM_COMMON_BASE + DCSM_O_FLSEM) & 0x3)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Sector Status (which zone owns which sectors)
    //-------------------------------------------------------------------------
    {
        name: "sectStat1",
        displayName: "Sector Status 1",
        type: 'value',
        register: "SECTSTAT1",
        updateFunc: (instBase) => `HWREG(DCSM_COMMON_BASE + DCSM_O_SECTSTAT1)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },
    {
        name: "ramStat1",
        displayName: "RAM Status 1",
        type: 'value',
        register: "RAMSTAT1",
        updateFunc: (instBase) => `HWREG(DCSM_COMMON_BASE + DCSM_O_RAMSTAT1)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },
];

//-----------------------------------------------------------------------------
// Bitfield Instance Name Mapping
//-----------------------------------------------------------------------------
let bitfieldInstanceNames = {
    "default": (instName) => { return "DcsmZ1Regs" },
    "z1": (instName) => { return "DcsmZ1Regs" },
    "z2": (instName) => { return "DcsmZ2Regs" },
    "common": (instName) => { return "DcsmCommonRegs" },
};

//-----------------------------------------------------------------------------
// Registers to Skip (Security sensitive and Clear/Force registers)
//-----------------------------------------------------------------------------
let exportsRegisterSkips = [
    // CSM Keys - DO NOT READ (security sensitive)
    { name: "Z1_CSMKEY0", register: "DCSM_Z1_CSMKEY0" },
    { name: "Z1_CSMKEY1", register: "DCSM_Z1_CSMKEY1" },
    { name: "Z1_CSMKEY2", register: "DCSM_Z1_CSMKEY2" },
    { name: "Z1_CSMKEY3", register: "DCSM_Z1_CSMKEY3" },
    { name: "Z2_CSMKEY0", register: "DCSM_Z2_CSMKEY0" },
    { name: "Z2_CSMKEY1", register: "DCSM_Z2_CSMKEY1" },
    { name: "Z2_CSMKEY2", register: "DCSM_Z2_CSMKEY2" },
    { name: "Z2_CSMKEY3", register: "DCSM_Z2_CSMKEY3" },
    // JTAG Keys - DO NOT READ (security sensitive)
    { name: "Z1_JTAGKEY0", register: "DCSM_Z1_JTAGKEY0" },
    { name: "Z1_JTAGKEY1", register: "DCSM_Z1_JTAGKEY1" },
    { name: "Z1_JTAGKEY2", register: "DCSM_Z1_JTAGKEY2" },
    { name: "Z1_JTAGKEY3", register: "DCSM_Z1_JTAGKEY3" },
    // CMAC Keys - DO NOT READ (security sensitive)
    { name: "Z1_CMACKEY0", register: "DCSM_Z1_CMACKEY0" },
    { name: "Z1_CMACKEY1", register: "DCSM_Z1_CMACKEY1" },
    { name: "Z1_CMACKEY2", register: "DCSM_Z1_CMACKEY2" },
    { name: "Z1_CMACKEY3", register: "DCSM_Z1_CMACKEY3" },
    // Security Error Clear/Force
    { name: "SECERRCLR", register: "DCSM_SECERRCLR" },
    { name: "SECERRFRC", register: "DCSM_SECERRFRC" },
];

//-----------------------------------------------------------------------------
// Module Exports
//-----------------------------------------------------------------------------
exports = {
    exportsInfo: exportsInfo,
    bitfieldInstanceNames: bitfieldInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
}
