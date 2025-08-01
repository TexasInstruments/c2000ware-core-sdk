var deviceName = system.deviceData.device;

let exportsInfo = [
 {
        name: "cpuwriteviolation",
        displayName: "Master CPU Write Access Violation",
        type: 'led',
        register: "MAVFLG.CPUWRITE",
        bitfieldInstance: "accessprotection",
        updateFunc: (instBase) => `((HWREGH(ACCESSPROTECTION_BASE + MEMCFG_O_MAVFLG) & MEMCFG_MAVFLG_CPUWRITE) == MEMCFG_MAVFLG_CPUWRITE)`,
        applicable: (inst) => {
            return (["F280013x", "F280015x", "F28003x"].includes(deviceName)? true: false);
        }
    },
    {
        name: "cpufetchviolation",
        displayName: "Master CPU Fetch Access Violation",
        type: 'led',
        register: "MAVFLG.CPUFETCH",
        bitfieldInstance: "accessprotection",
        updateFunc: (instBase) => `((HWREGH(ACCESSPROTECTION_BASE + MEMCFG_O_MAVFLG) & MEMCFG_MAVFLG_CPUFETCH) == MEMCFG_MAVFLG_CPUFETCH)`,
        applicable: (inst) => {
            return (["F280013x", "F280015x", "F28003x"].includes(deviceName)? true: false);
        }
    },
    {
        name: "pllreflosts",
        displayName: "SYSPLL 'Reference Lost' Event Occured",
        type: 'led',
        register: "SYSPLLSTS.REF_LOSTS",
        bitfieldInstance: "clkcfg",
        updateFunc: (instBase) => `((HWREGH(CLKCFG_BASE + SYSCTL_O_SYSPLLSTS) & SYSCTL_SYSPLLSTS_REF_LOSTS) == SYSCTL_SYSPLLSTS_REF_LOSTS)`,
        applicable: (inst) => {
            return (["F280013x", "F280015x"].includes(deviceName)? true: false);
        }
    },
    {
        name: "mclksts",
        displayName: "OSCCLK Detected Missing",
        type: 'led',
        register: "MCDCR.MCLKSTS",
        bitfieldInstance: "clkcfg",
        updateFunc: (instBase) => `((HWREGH(CLKCFG_BASE + SYSCTL_O_MCDCR) & SYSCTL_MCDCR_MCLKSTS) == SYSCTL_MCDCR_MCLKSTS)`,
        applicable: (inst) => {
            return (["F280013x", "F280015x","F28003x"].includes(deviceName)? true: false);
        }
    },
    {
        name: "cpurderr",
        displayName: "CPU Correctable Read Error",
        type: 'led',
        register: "CERRFLG.CPURDERR",
        bitfieldInstance: "memerr",
        updateFunc: (instBase) => `((HWREGH(MEMORYERROR_BASE + MEMCFG_O_CERRFLG) & MEMCFG_CERRFLG_CPURDERR) == MEMCFG_CERRFLG_CPURDERR)`,
        applicable: (inst) => {
            return (["F280013x", "F280015x", "F28003x"].includes(deviceName)? true: false);
        }
    },
    {
        name: "dmarderr",
        displayName: "DMA Correctable Read Error",
        type: 'led',
        register: "CERRFLG.DMARDERR",
        bitfieldInstance: "memerr",
        updateFunc: (instBase) => `((HWREGH(MEMORYERROR_BASE + MEMCFG_O_CERRFLG) & MEMCFG_CERRFLG_DMARDERR) == MEMCFG_CERRFLG_DMARDERR)`,
        applicable: (inst) => {
            return (["F28003x"].includes(deviceName)? true: false);
        }
    },
    {
        name: "cla1rderr",
        displayName: "CLA1 Correctable Read Error",
        type: 'led',
        register: "CERRFLG.CLA1RDERR",
        bitfieldInstance: "memerr",
        updateFunc: (instBase) => `((HWREGH(MEMORYERROR_BASE + MEMCFG_O_CERRFLG) & MEMCFG_CERRFLG_CLA1RDERR) == MEMCFG_CERRFLG_CLA1RDERR)`,
        applicable: (inst) => {
            return (["F28003x"].includes(deviceName)? true: false);
        }
    },
    {
        name: "uncerror",
        displayName: "Uncorrectable RAM Test Error",
        type: 'led',
        register: "CPU_RAM_TEST_ERROR_STS.UNC_ERROR",
        bitfieldInstance: "testerr",
        updateFunc: (instBase) => `((HWREGH(TESTERROR_BASE +  MEMCFG_O_CPU_RAM_TEST_ERROR_STS) & MEMCFG_CPU_RAM_TEST_ERROR_STS_CLR_UNC_ERROR) == MEMCFG_CPU_RAM_TEST_ERROR_STS_CLR_UNC_ERROR)`,
        applicable: (inst) => {
            return (["F280013x", "F280015x", "F28003x"].includes(deviceName)? true: false);
        }
    },
    {
        name: "corerror",
        displayName: "Correctable RAM Test Error",
        type: 'led',
        register: "CPU_RAM_TEST_ERROR_STS.COR_ERROR",
        bitfieldInstance: "testerr",
        updateFunc: (instBase) => `((HWREGH(TESTERROR_BASE +  MEMCFG_O_CPU_RAM_TEST_ERROR_STS) & MEMCFG_CPU_RAM_TEST_ERROR_STS_CLR_COR_ERROR) == MEMCFG_CPU_RAM_TEST_ERROR_STS_CLR_COR_ERROR)`,
        applicable: (inst) => {
            return (["F280013x", "F280015x", "F28003x"].includes(deviceName)? true: false);
        }
    },
    {
        name: "clkf",
        displayName: "Clock Fail",
        type: 'led',
        register: "NMIFLG.CLOCKFAIL",
        bitfieldInstance: "nmi",
        updateFunc: (instBase) => `((HWREGH(NMI_BASE + NMI_O_FLG) & NMI_FLG_CLOCKFAIL) == NMI_FLG_CLOCKFAIL)`,
        applicable: (inst) => {
            return (["F280013x"].includes(deviceName)? true: false);
        }
    },
    {
        name: "ramuncerr",
        displayName: "RAM Uncorrectable Error",
        type: 'led',
        register: "NMIFLG.RAMUNCERR",
        bitfieldInstance: "nmi",
        updateFunc: (instBase) => `((HWREGH(NMI_BASE + NMI_O_FLG) & NMI_FLG_RAMUNCERR) == NMI_FLG_RAMUNCERR)`,
        applicable: (inst) => {
            return (["F28003x"].includes(deviceName)? true: false);
        }
    },
    {
        name: "fluncerr",
        displayName: "Flash Uncorrectable Error",
        type: 'led',
        register: "NMIFLG.FLUNCERR",
        bitfieldInstance: "nmi",
        updateFunc: (instBase) => `((HWREGH(NMI_BASE + NMI_O_FLG) & NMI_FLG_FLUNCERR) == NMI_FLG_FLUNCERR)`,
        applicable: (inst) => {
            return (["F28003x"].includes(deviceName)? true: false);
        }
    },
    {
        name: "uncerr",
        displayName: "Flash/RAM/ROM Uncorrectable Error",
        type: 'led',
        register: "NMIFLG.UNCERR",
        bitfieldInstance: "nmi",
        updateFunc: (instBase) => `((HWREGH(NMI_BASE + NMI_O_FLG) & NMI_FLG_UNCERR) == NMI_FLG_UNCERR)`,
        applicable: (inst) => {
            return (["F280013x", "F280015x"].includes(deviceName)? true: false);
        }
    },
    {
        name: "regparityerr",
        displayName: "Register Parity Error",
        type: 'led',
        register: "NMIFLG.REGPARITYERR",
        bitfieldInstance: "nmi",
        updateFunc: (instBase) => `((HWREGH(NMI_BASE + NMI_O_FLG) & NMI_FLG_REGPARITYERR) == NMI_FLG_REGPARITYERR)`,
        applicable: (inst) => {
            return (["F280015x"].includes(deviceName)? true: false);
        }
    },
]

let bitfiledInstanceNames = {
    "default": (instName) => { return "NmiIntruptRegs" },
    "nmi": (instName) => { return "NmiIntruptRegs" },
    "accessprotection": (instName) => { return "AccessProtectionRegs" },
    "clkcfg": (instName) => { return "ClkCfgRegs" },
    "testerr": (instName) => { return "TestErrorRegs" },
    "memerr": (instName) => { return "MemoryErrorRegs" },
}

let exportsRegisterSkips = [
]

exports = {
    exportsInfo: exportsInfo,
    bitfiledInstanceNames : bitfiledInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
}