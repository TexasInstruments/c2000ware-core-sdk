//=============================================================================
// export_mod_memoryerror.js - Memory Error Export Module for CDT
//=============================================================================
// Purpose: Expose Memory ECC Error diagnostic information for CDT
// Devices: All Gen3 devices
// Reference: driverlib/<device>/driverlib/inc/hw_memcfg.h
//
// CRITICAL: These registers provide runtime detection of memory faults
// - Uncorrectable errors (UCERRFLG) indicate data corruption
// - Correctable errors (CERRFLG) indicate ECC corrections occurred
// - Error addresses help identify faulty memory locations
//=============================================================================

const exportCommon = system.getScript("/utilities/transfer/export/export_mods_common.js");
const { DEVICES_WITH_CDT_SUPPORT, DEVICES_WITH_DMA, DEVICES_WITH_CLA, getDeviceName } = exportCommon;
const deviceName = getDeviceName();

// Note: DEVICES_WITH_DMA and DEVICES_WITH_CLA imported from centralized device_constants.js
// DMA: F28002x, F28003x, F28004x, F2807x, F2837xD, F2837xS, F2838x, F28P55x, F28P65x
// CLA: F28003x, F28004x, F2807x, F2837xD, F2837xS, F2838x, F28P55x, F28P65x (F28002x does NOT have CLA)

// Devices with HICA/HIC error support (specific to memory error module)
const DEVICES_WITH_HIC = [
    "F28003x", "F2838x"
];

let exportsInfo = [
    //-------------------------------------------------------------------------
    // Uncorrectable Error Flags (CRITICAL - Data Corruption)
    //-------------------------------------------------------------------------
    {
        name: "ucCpuReadErr",
        displayName: "CPU Uncorrectable Read Error",
        type: 'led',
        register: "UCERRFLG.CPURDERR",
        bitfieldInstance: "memoryerror",
        updateFunc: (instBase) => `((HWREG(MEMORYERROR_BASE + MEMCFG_O_UCERRFLG) & MEMCFG_UCERRFLG_CPURDERR) == MEMCFG_UCERRFLG_CPURDERR)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },
    {
        name: "ucDmaReadErr",
        displayName: "DMA Uncorrectable Read Error",
        type: 'led',
        register: "UCERRFLG.DMARDERR",
        bitfieldInstance: "memoryerror",
        updateFunc: (instBase) => `((HWREG(MEMORYERROR_BASE + MEMCFG_O_UCERRFLG) & MEMCFG_UCERRFLG_DMARDERR) == MEMCFG_UCERRFLG_DMARDERR)`,
        applicable: (inst) => {
            return DEVICES_WITH_DMA.includes(deviceName);
        }
    },
    {
        name: "ucCla1ReadErr",
        displayName: "CLA1 Uncorrectable Read Error",
        type: 'led',
        register: "UCERRFLG.CLA1RDERR",
        bitfieldInstance: "memoryerror",
        updateFunc: (instBase) => `((HWREG(MEMORYERROR_BASE + MEMCFG_O_UCERRFLG) & MEMCFG_UCERRFLG_CLA1RDERR) == MEMCFG_UCERRFLG_CLA1RDERR)`,
        applicable: (inst) => {
            return DEVICES_WITH_CLA.includes(deviceName);
        }
    },
    {
        name: "ucHicaReadErr",
        displayName: "HICA Uncorrectable Read Error",
        type: 'led',
        register: "UCERRFLG.HICARDERR",
        bitfieldInstance: "memoryerror",
        updateFunc: (instBase) => `((HWREG(MEMORYERROR_BASE + MEMCFG_O_UCERRFLG) & MEMCFG_UCERRFLG_HICARDERR) == MEMCFG_UCERRFLG_HICARDERR)`,
        applicable: (inst) => {
            return DEVICES_WITH_HIC.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Uncorrectable Error Addresses (Fault Location)
    //-------------------------------------------------------------------------
    {
        name: "ucCpuErrAddr",
        displayName: "CPU Uncorrectable Error Address",
        type: 'value',
        register: "UCCPUREADDR",
        bitfieldInstance: "memoryerror",
        updateFunc: (instBase) => `HWREG(MEMORYERROR_BASE + MEMCFG_O_UCCPUREADDR)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },
    {
        name: "ucDmaErrAddr",
        displayName: "DMA Uncorrectable Error Address",
        type: 'value',
        register: "UCDMAREADDR",
        bitfieldInstance: "memoryerror",
        updateFunc: (instBase) => `HWREG(MEMORYERROR_BASE + MEMCFG_O_UCDMAREADDR)`,
        applicable: (inst) => {
            return DEVICES_WITH_DMA.includes(deviceName);
        }
    },
    {
        name: "ucCla1ErrAddr",
        displayName: "CLA1 Uncorrectable Error Address",
        type: 'value',
        register: "UCCLA1READDR",
        bitfieldInstance: "memoryerror",
        updateFunc: (instBase) => `HWREG(MEMORYERROR_BASE + MEMCFG_O_UCCLA1READDR)`,
        applicable: (inst) => {
            return DEVICES_WITH_CLA.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Correctable Error Flags (ECC Correction Occurred)
    //-------------------------------------------------------------------------
    {
        name: "cCpuReadErr",
        displayName: "CPU Correctable Read Error",
        type: 'led',
        register: "CERRFLG.CPURDERR",
        bitfieldInstance: "memoryerror",
        updateFunc: (instBase) => `((HWREG(MEMORYERROR_BASE + MEMCFG_O_CERRFLG) & MEMCFG_CERRFLG_CPURDERR) == MEMCFG_CERRFLG_CPURDERR)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },
    {
        name: "cDmaReadErr",
        displayName: "DMA Correctable Read Error",
        type: 'led',
        register: "CERRFLG.DMARDERR",
        bitfieldInstance: "memoryerror",
        updateFunc: (instBase) => `((HWREG(MEMORYERROR_BASE + MEMCFG_O_CERRFLG) & MEMCFG_CERRFLG_DMARDERR) == MEMCFG_CERRFLG_DMARDERR)`,
        applicable: (inst) => {
            return DEVICES_WITH_DMA.includes(deviceName);
        }
    },
    {
        name: "cCla1ReadErr",
        displayName: "CLA1 Correctable Read Error",
        type: 'led',
        register: "CERRFLG.CLA1RDERR",
        bitfieldInstance: "memoryerror",
        updateFunc: (instBase) => `((HWREG(MEMORYERROR_BASE + MEMCFG_O_CERRFLG) & MEMCFG_CERRFLG_CLA1RDERR) == MEMCFG_CERRFLG_CLA1RDERR)`,
        applicable: (inst) => {
            return DEVICES_WITH_CLA.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Correctable Error Count and Threshold
    //-------------------------------------------------------------------------
    {
        name: "corrErrCount",
        displayName: "Correctable Error Count",
        type: 'value',
        register: "CERRCNT",
        bitfieldInstance: "memoryerror",
        updateFunc: (instBase) => `HWREG(MEMORYERROR_BASE + MEMCFG_O_CERRCNT)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },
    {
        name: "corrErrThreshold",
        displayName: "Correctable Error Threshold",
        type: 'value',
        register: "CERRTHRES",
        bitfieldInstance: "memoryerror",
        updateFunc: (instBase) => `(HWREG(MEMORYERROR_BASE + MEMCFG_O_CERRTHRES) & 0xFFFF)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },
    {
        name: "corrErrThreshExceeded",
        displayName: "Correctable Error Threshold Exceeded",
        type: 'led',
        register: "CEINTFLG.CEINTFLAG",
        bitfieldInstance: "memoryerror",
        updateFunc: (instBase) => `((HWREG(MEMORYERROR_BASE + MEMCFG_O_CEINTFLG) & MEMCFG_CEINTFLG_CEINTFLAG) == MEMCFG_CEINTFLG_CEINTFLAG)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Correctable Error Addresses
    //-------------------------------------------------------------------------
    {
        name: "cCpuErrAddr",
        displayName: "CPU Correctable Error Address",
        type: 'value',
        register: "CCPUREADDR",
        bitfieldInstance: "memoryerror",
        updateFunc: (instBase) => `HWREG(MEMORYERROR_BASE + MEMCFG_O_CCPUREADDR)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },
    {
        name: "cDmaErrAddr",
        displayName: "DMA Correctable Error Address",
        type: 'value',
        register: "CDMAREADDR",
        bitfieldInstance: "memoryerror",
        updateFunc: (instBase) => `HWREG(MEMORYERROR_BASE + MEMCFG_O_CDMAREADDR)`,
        applicable: (inst) => {
            return DEVICES_WITH_DMA.includes(deviceName);
        }
    },
];

//-----------------------------------------------------------------------------
// Bitfield Instance Name Mapping
//-----------------------------------------------------------------------------
let bitfieldInstanceNames = {
    "default": (instName) => { return "MemoryErrorRegs" },
};

//-----------------------------------------------------------------------------
// Registers to Skip (R/W1C Set/Clear registers)
//-----------------------------------------------------------------------------
let exportsRegisterSkips = [
    // Uncorrectable Error Set/Clear (R/W1C)
    { name: "UCERRSET", register: "MEMCFG_UCERRSET" },
    { name: "UCERRCLR", register: "MEMCFG_UCERRCLR" },
    // Correctable Error Set/Clear (R/W1C)
    { name: "CERRSET", register: "MEMCFG_CERRSET" },
    { name: "CERRCLR", register: "MEMCFG_CERRCLR" },
    // Correctable Error Interrupt Set/Clear (R/W1C)
    { name: "CEINTCLR", register: "MEMCFG_CEINTCLR" },
    { name: "CEINTSET", register: "MEMCFG_CEINTSET" },
];

//-----------------------------------------------------------------------------
// Module Exports
//-----------------------------------------------------------------------------
exports = {
    exportsInfo: exportsInfo,
    bitfieldInstanceNames: bitfieldInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
}
