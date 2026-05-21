//=============================================================================
// export_mod_memory.js - Memory Diagnostics Export Module for CDT
//=============================================================================
// Purpose: Expose Memory diagnostic information for CDT
// Devices: All Gen3 devices
// Reference: driverlib/<device>/driverlib/inc/hw_memcfg.h, hw_nmi.h
//=============================================================================

const exportCommon = system.getScript("/utilities/transfer/export/export_mods_common.js");
const { DEVICES_WITH_CDT_SUPPORT, DEVICES_WITH_CLA, getDeviceName } = exportCommon;

// Devices with DMA correctable error support
const DEVICES_WITH_DMA_CERR = [
    "F28003x", "F28004x", "F2807x", "F2837xD", "F2837xS", "F2838x", "F28P55x", "F28P65x"
];

// DEVICES_WITH_CLA imported from exportCommon

// Devices with TestErrorRegs (CPU_RAM_TEST_ERROR_STS register)
// Note: F28004x, F2807x, F2837xD, F2837xS do NOT have this register
const DEVICES_WITH_TEST_ERROR_REGS = [
    "F280013x", "F280015x", "F28002x", "F28003x", "F2838x", "F28P55x", "F28P65x"
];

// Devices with separate RAM/Flash NMI flags (vs combined UNCERR)
// Note: F28P65x uses combined UNCERR flag, not separate RAMUNCERR/FLUNCERR
const DEVICES_WITH_SEPARATE_MEM_NMI = [
    "F28002x", "F28003x", "F28004x", "F2807x", "F2837xD", "F2837xS", "F2838x", "F28P55x"
];

//-----------------------------------------------------------------------------
// Memory Size by Device (in KB) - Maximum variant flash, representative RAM
// Source: Device datasheets
//
// Flash = largest orderable flash variant for the family
// RAM   = total on-chip SRAM (M0+M1+Lx+GSx blocks combined)
//
// F280013x flash variants: 32KB (F2800131), 128KB (F2800133), 256KB (F2800137)
// F280015x flash variants: 64KB (F2800152/155/156), 128KB (F2800157/158) — max is 128KB
// F28002x  flash variants: 128KB (F280023), 256KB (F280025)
// F28003x  flash variants: 128KB (F2800331), 256KB (F2800333), 384KB (F2800337) — 384 is real
// F28004x  flash variants: 128KB, 256KB (F2800433/35/37/39/59)
// F2807x   flash variants: 512KB (F28075), 1MB (F28076), 1.5MB — max is 1.5MB
// F2837xD  flash variants: 512KB, 1MB, 1.5MB
// F2837xS  flash variants: 512KB, 1MB, 1.5MB
// F2838x   flash variants: 1MB, 1.5MB, 2MB
// F28P55x  flash variants: 512KB, 768KB, 1MB + 64KB OTP (1088KB total addressable)
// F28P65x  flash variants: 1MB, 2MB (1280KB = 5×256KB bank configuration)
//-----------------------------------------------------------------------------
const DEVICE_MEMORY = {
    "F280013x": { flash: 256, ram: 12 },     // TMS320F280013x: max variant F2800137=256KB flash
    "F280015x": { flash: 128, ram: 28 },     // TMS320F280015x: max variant F2800157=128KB flash (not 256KB)
    "F28002x":  { flash: 256, ram: 24 },     // TMS320F28002x: max variant F280025=256KB flash
    "F28003x":  { flash: 384, ram: 69 },     // TMS320F28003x: max variant F2800337=384KB flash (confirmed)
    "F28004x":  { flash: 256, ram: 100 },    // TMS320F28004x datasheet
    "F2807x":   { flash: 1536, ram: 174 },   // TMS320F2807x: max 1.5MB flash, 174KB RAM
    "F2837xD":  { flash: 1536, ram: 204 },   // TMS320F2837xD: max 1.5MB flash
    "F2837xS":  { flash: 1536, ram: 164 },   // TMS320F2837xS: max 1.5MB flash
    "F2838x":   { flash: 2048, ram: 512 },   // TMS320F2838x: max 2MB flash, 512KB RAM
    "F28P55x":  { flash: 1088, ram: 256 },   // TMS320F28P55x: 1MB + 64KB OTP = 1088KB, 256KB RAM
    "F28P65x":  { flash: 2048, ram: 1024 }   // TMS320F28P65x: max 2MB flash, 1024KB RAM
};

let exportsInfo = [
    //-------------------------------------------------------------------------
    // Memory Capacity (bar visualization entries)
    // These provide device memory totals for visual bar display
    //-------------------------------------------------------------------------
    {
        name: "flashBar",
        displayName: "Flash",
        description: "Total Flash memory capacity on this device.",
        type: 'bar',
        category: 'memory_capacity',
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(getDeviceName());
        }
    },
    {
        name: "ramBar",
        displayName: "RAM",
        description: "Total RAM memory capacity on this device.",
        type: 'bar',
        category: 'memory_capacity',
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(getDeviceName());
        }
    },

    //-------------------------------------------------------------------------
    // Memory Access Violations
    // MAVFLG register bits: CPUFETCH=0, CPUWRITE=1, DMAWRITE=2
    //-------------------------------------------------------------------------
    {
        name: "cpuwriteviolation",
        displayName: "CPU Write Violation",
        description: "CPU attempted to write to protected memory. Check MEMCFG_MSGxACCPROT settings.",
        type: 'led',
        category: 'access_violation',
        register: "MAVFLG.CPUWRITE",
        baseRegister: "MAVFLG",
        bitMask: 0x2,  // Bit 1
        bitfieldInstance: "accessprotection",
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(getDeviceName());
        }
    },
    {
        name: "cpufetchviolation",
        displayName: "CPU Fetch Violation",
        description: "CPU attempted to fetch from protected memory. Check MEMCFG_MSGxACCPROT settings.",
        type: 'led',
        category: 'access_violation',
        register: "MAVFLG.CPUFETCH",
        baseRegister: "MAVFLG",
        bitMask: 0x1,  // Bit 0
        bitfieldInstance: "accessprotection",
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(getDeviceName());
        }
    },

    //-------------------------------------------------------------------------
    // Correctable Error Flags (ECC errors that were corrected)
    // CERRFLG register bits: CPURDERR=0, DMARDERR=1, CLA1RDERR=2
    //-------------------------------------------------------------------------
    {
        name: "cpurderr",
        displayName: "CPU Correctable Error",
        description: "Single-bit ECC error corrected during CPU read. Address in CERRTHRES.",
        type: 'led',
        category: 'correctable_error',
        register: "CERRFLG.CPURDERR",
        baseRegister: "CERRFLG",
        bitMask: 0x1,  // Bit 0
        bitfieldInstance: "memerr",
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(getDeviceName());
        }
    },
    {
        name: "dmarderr",
        displayName: "DMA Correctable Error",
        description: "Single-bit ECC error corrected during DMA read. Check DMA transactions.",
        type: 'led',
        category: 'correctable_error',
        register: "CERRFLG.DMARDERR",
        baseRegister: "CERRFLG",
        bitMask: 0x2,  // Bit 1
        bitfieldInstance: "memerr",
        applicable: (inst) => {
            return DEVICES_WITH_DMA_CERR.includes(getDeviceName());
        }
    },
    {
        name: "cla1rderr",
        displayName: "CLA Correctable Error",
        description: "Single-bit ECC error corrected during CLA read. Check CLA memory access.",
        type: 'led',
        category: 'correctable_error',
        register: "CERRFLG.CLA1RDERR",
        baseRegister: "CERRFLG",
        bitMask: 0x4,  // Bit 2
        bitfieldInstance: "memerr",
        applicable: (inst) => {
            return DEVICES_WITH_CLA.includes(getDeviceName());
        }
    },

    //-------------------------------------------------------------------------
    // RAM Test Error Status (BIST/Memory Test)
    // CPU_RAM_TEST_ERROR_STS register bits: COR_ERROR=0, UNC_ERROR=1
    //-------------------------------------------------------------------------
    {
        name: "ramtestunc",
        displayName: "RAM Test Uncorrectable",
        description: "BIST/Memory test found uncorrectable 2-bit error. Memory may be damaged.",
        type: 'led',
        category: 'test_error',
        register: "CPU_RAM_TEST_ERROR_STS.UNC_ERROR",
        baseRegister: "CPU_RAM_TEST_ERROR_STS",
        bitMask: 0x2,  // Bit 1
        bitfieldInstance: "testerr",
        applicable: (inst) => {
            return DEVICES_WITH_TEST_ERROR_REGS.includes(getDeviceName());
        }
    },
    {
        name: "ramtestcor",
        displayName: "RAM Test Correctable",
        description: "BIST/Memory test found correctable 1-bit error. ECC corrected it.",
        type: 'led',
        category: 'test_error',
        register: "CPU_RAM_TEST_ERROR_STS.COR_ERROR",
        baseRegister: "CPU_RAM_TEST_ERROR_STS",
        bitMask: 0x1,  // Bit 0
        bitfieldInstance: "testerr",
        applicable: (inst) => {
            return DEVICES_WITH_TEST_ERROR_REGS.includes(getDeviceName());
        }
    },

    //-------------------------------------------------------------------------
    // NMI Flags - Memory Errors (Uncorrectable - triggered NMI)
    //-------------------------------------------------------------------------
    {
        name: "ramuncerr",
        displayName: "RAM Uncorrectable (NMI)",
        description: "NMI triggered by uncorrectable 2-bit RAM ECC error. Data corruption likely.",
        type: 'led',
        category: 'nmi_error',
        register: "NMIFLG.RAMUNCERR",
        baseRegister: "NMIFLG",
        bitMask: 0x4,  // Bit 2
        bitfieldInstance: "nmi",
        applicable: (inst) => {
            return DEVICES_WITH_SEPARATE_MEM_NMI.includes(getDeviceName());
        }
    },
    {
        name: "fluncerr",
        displayName: "Flash Uncorrectable (NMI)",
        description: "NMI triggered by uncorrectable 2-bit Flash ECC error. Flash may need reprogramming.",
        type: 'led',
        category: 'nmi_error',
        register: "NMIFLG.FLUNCERR",
        baseRegister: "NMIFLG",
        bitMask: 0x8,  // Bit 3
        bitfieldInstance: "nmi",
        applicable: (inst) => {
            return DEVICES_WITH_SEPARATE_MEM_NMI.includes(getDeviceName());
        }
    },
    {
        name: "uncerr",
        displayName: "Memory Uncorrectable (NMI)",
        description: "NMI triggered by uncorrectable 2-bit ECC error (RAM or Flash).",
        type: 'led',
        category: 'nmi_error',
        register: "NMIFLG.UNCERR",
        baseRegister: "NMIFLG",
        bitMask: 0x4,  // Bit 2 (combined flag)
        bitfieldInstance: "nmi",
        applicable: (inst) => {
            // F280013x, F280015x, and F28P65x use combined UNCERR flag
            return ["F280013x", "F280015x", "F28P65x"].includes(getDeviceName());
        }
    },
];

let bitfieldInstanceNames = {
    "default": (instName) => { return "NmiIntruptRegs" },
    "nmi": (instName) => { return "NmiIntruptRegs" },
    "accessprotection": (instName) => { return "AccessProtectionRegs" },
    "testerr": (instName) => { return "TestErrorRegs" },
    "memerr": (instName) => { return "MemoryErrorRegs" },
};

let exportsRegisterSkips = [
    // Memory error clear registers
    { name: "CERRCLR", register: "MEMCFG_CERRCLR" },
    { name: "UCERRCLR", register: "MEMCFG_UCERRCLR" },
    // Access violation clear
    { name: "MAVCLR", register: "MEMCFG_MAVCLR" },
];

exports = {
    exportsInfo: exportsInfo,
    bitfieldInstanceNames: bitfieldInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
    DEVICE_MEMORY: DEVICE_MEMORY,
};
