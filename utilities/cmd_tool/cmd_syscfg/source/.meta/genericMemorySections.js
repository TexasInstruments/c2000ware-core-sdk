// If you are using EABI instead of COFF, change the following sections as needed:
// - .ebss to .bss
// - .esysmem to .sysmem
// - .econst to .const
// - .pinit to .init_array


var CompilerMemorySections = [
    {
        name       : "codestart",
        displayName: "codestart",
        sectionName: "codestart",
        description: "For standalone boot, make sure the boot mode is configured to boot from the selected address",
    },
    {
        name       : "text",
        displayName: "text",
        sectionName: ".text",
        description: "Executable code and constants. Must be in Flash for standalone execution.",
        loadRun    : true
    },
    {
        name       : "ramfunc",
        displayName: "ramfunc",
        sectionName: ".TI.ramfunc",
        description: "Functions that needs be run from RAM. Load address should be in Flash and RUN address should be in RAM",
        loadRun    : true
    },
    {
        name       : "binit",
        displayName: "binit",
        sectionName: ".binit",
        description: "Boot time copy tables",
        loadRun    : false
    },
    {
        name       : "ovly",
        displayName: "ovly",
        sectionName: ".ovly",
        description: "Copy tables other than boot time (.binit) copy tables. Must be in Flash for standalone execution",
        loadRun    : false
    },
    {
        name       : "cinit",
        displayName: "cinit",
        sectionName: ".cinit",
        description: "Tables for explicitly initialized global and static variables. Must be in Flash for standalone execution.",
        loadRun    : false
    },
    // {
    //     name       : "reset",
    //     displayName: "reset",
    //     sectionName: ".reset",
    //     type       : "DSECT"
    // },
    {
        name       : "stack",
        displayName: "stack",
        sectionName: ".stack",
        description: "Should be in lower 64K. Must be in RAM",
        loadRun    : false
    },
    {
        name       : "init_array",
        displayName: "init_array",
        sectionName: ".init_array",
        description: "Table of constructors to be called at startup. (EABI only). Must be in Flash for standalone execution",
        loadRun    : false
    },
    {
        name       : "bss",
        displayName: "bss",
        sectionName: ".bss",
        description: "Global and static variables (EABI only). Must be in RAM",
        loadRun    : false
    },
    {
        name       : "const",
        displayName: "const",
        sectionName: ".const",
        description: "Global and static const variables that are explicitly initialized and contain string literals.(EABI only). Must be in Flash for standalone execution",
        loadRun    : true
    },
    {
        name       : "data",
        displayName: "data",
        sectionName: ".data",
        description: "Global and static non-const variables that are explicitly initialized. Must be in RAM",
        loadRun    : false
    },
    {
        name       : "switch",
        displayName: "switch",
        sectionName: ".switch",
        description: "Jump tables for large switch statements. Must be in Flash for standalone execution.",
        loadRun    : false
    },
    {
        name       : "sysmem",
        displayName: "sysmem",
        sectionName: ".sysmem",
        description: "Memory for malloc functions (heap) (EABI only). Must be in RAM",
        loadRun    : false
    },
]

var CLACompilerMemorySections = [
    {
        name        : "cla1Prog",
        displayName : "Cla1Prog",
        sectionName : "Cla1Prog",
        description : "",
        loadRun : true,
    },
    {
        name        : "claConst",
        displayName : ".const_cla",
        sectionName : ".const_cla",
        description : "",
        loadRun : true,
    },
    {
        name          : "claScratchpad",
        displayName   : ".scratchpad",
        sectionName   : ".scratchpad",
        description   : "",
        loadRun   : false,
        memoryGroup   : "RAMLS"
    },
    {
        name          : "bssCla",
        displayName   : ".bss_cla",
        sectionName   : ".bss_cla",
        description   : "",
        loadRun   : false,
        memoryGroup   : "RAMLS"
    },
    {
        name          : "cla1ToCpuMsgRAM",
        displayName   : "cla1ToCpuMsgRAM",
        sectionName   : "cla1ToCpuMsgRAM",
        description   : "",
        loadRun   : false,
        memoryGroup   : "CLATOCPUMSGRAM"
    },
    {
        name          : "cpuToCla1MsgRAM",
        displayName   : "cpuToCla1MsgRAM",
        sectionName   : "cpuToCla1MsgRAM",
        description   : "",
        loadRun   : false,
        memoryGroup   : "CPUTOCLAMSGRAM"
    },
]

exports = {
    CompilerMemorySections: CompilerMemorySections,
    CLACompilerMemorySections : CLACompilerMemorySections
}