let memorySections = system.getScript("genericMemorySections.js")

var memoryInfo = {
    combinableMemories : [
        "RAMM",
        "RAMLS",
        "FLASH"
    ],
    codeStartLocations : [
        {displayName : "Boot from RAMM0",                          name : "0x000000"},
        {displayName : "Boot from Flash Bank 0 Sector 0",          name : "0x080000"},
        {displayName : "Boot from Flash Bank 0 Sector 32",         name : "0x088000"},
        {displayName : "Boot from Flash Bank 0 End of Sector 63",  name : "0x08FFF0"},
        {displayName : "Boot from Flash Bank 0 Sector 64",         name : "0x090000"},
        {displayName : "Boot from Flash Bank 1 Sector 96 ",        name : "0x098000"},
        {displayName : "Boot from Flash Bank 1 End of Sector 127", name : "0x09FFF0"},

    ],
    memorySections:  memorySections.CompilerMemorySections,

    memoryRanges : [
        {name : "RAMM0",  group : "RAMM", origin : 0x000128, length : 0x0002D8, description : "The initial bytes of RAMM0 is reserved for BootROM"},
        {name : "RAMM1",  group : "RAMM", origin : 0x000400, length : 0x0003F8, description : "Last 8 words of RAMM1 is reserved as per the errata advisory 'Memory: Prefetching Beyond Valid Memory'"},

        {name : "RAMLS0", group : "RAMLS", origin : 0x008000, length : 0x002000},
        {name : "RAMLS1", group : "RAMLS", origin : 0x00A000, length : 0x001FF8, description : "Last 8 words of RAMLS1 is reserved as per the errata advisory 'Memory: Prefetching Beyond Valid Memory'"},


        {name : "FLASH_BANK0_SEC_0_7",     group : "FLASH", origin : 0x080000, length : 0x2000},
        {name : "FLASH_BANK0_SEC_8_15",    group : "FLASH", origin : 0x082000, length : 0x2000},
        {name : "FLASH_BANK0_SEC_16_23",   group : "FLASH", origin : 0x084000, length : 0x2000},
        {name : "FLASH_BANK0_SEC_24_31",   group : "FLASH", origin : 0x086000, length : 0x2000},
        {name : "FLASH_BANK0_SEC_32_29",   group : "FLASH", origin : 0x088000, length : 0x2000},
        {name : "FLASH_BANK0_SEC_40_47",   group : "FLASH", origin : 0x08A000, length : 0x2000},
        {name : "FLASH_BANK0_SEC_48_55",   group : "FLASH", origin : 0x08C000, length : 0x2000},
        {name : "FLASH_BANK0_SEC_56_63",   group : "FLASH", origin : 0x08E000, length : 0x2000},
        {name : "FLASH_BANK0_SEC_64_71",   group : "FLASH", origin : 0x090000, length : 0x2000},
        {name : "FLASH_BANK0_SEC_72_79",   group : "FLASH", origin : 0x092000, length : 0x2000},
        {name : "FLASH_BANK0_SEC_80_87",   group : "FLASH", origin : 0x094000, length : 0x2000},
        {name : "FLASH_BANK0_SEC_88_95",   group : "FLASH", origin : 0x096000, length : 0x2000},
        {name : "FLASH_BANK0_SEC_96_103",  group : "FLASH", origin : 0x098000, length : 0x2000},
        {name : "FLASH_BANK0_SEC_104_111", group : "FLASH", origin : 0x09A000, length : 0x2000},
        {name : "FLASH_BANK0_SEC_112_119", group : "FLASH", origin : 0x09C000, length : 0x2000},
        {name : "FLASH_BANK0_SEC_120_127", group : "FLASH", origin : 0x09E000, length : 0x1FF0, description : "Last 16 words of Flash is reserved as per the errata advisory 'Memory: Prefetching Beyond Valid Memory'"},

        {name : "RESET", origin : 0x3FFFC0, length  : 0x000002}
    ],

    ramDefault :{
        "ramfunc"    : ["RAMM0"],
        "text"       : ["RAMLS0", "RAMLS1"],
        "cinit"      : ["RAMM0"],
        "switch"     : ["RAMM0"],
        "stack"      : ["RAMM1"],
        "bss"        : ["RAMLS0"],
        "init_array" : ["RAMM0"],
        "const"      : ["RAMLS0"],
        "data"       : ["RAMLS0"],
        "sysmem"     : ["RAMLS0"],
        "ovly"       : [],
        "codestart"  : "0x000000"
    },
    flashDefault :{
        "ramfunc"    : ["FLASH_BANK0_SEC_0_7"],
        "ramfuncRun" : ["RAMLS0"],
        "text"       : ["FLASH_BANK0_SEC_8_15", "FLASH_BANK0_SEC_16_23", "FLASH_BANK0_SEC_24_31"],
        "binit"      : ["FLASH_BANK0_SEC_0_7"],
        "cinit"      : ["FLASH_BANK0_SEC_0_7"],
        "switch"     : ["FLASH_BANK0_SEC_0_7"],
        "stack"      : ["RAMM1"],
        "bss"        : ["RAMLS0"],
        "init_array" : ["FLASH_BANK0_SEC_0_7"],
        "const"      : ["FLASH_BANK0_SEC_32_29"],
        "data"       : ["RAMLS0"],
        "sysmem"     : ["RAMLS0"],
        "ovly"       : ["FLASH_BANK0_SEC_0_7"],
        "codestart"  : "0x080000"
    }
}

exports = {
    memoryInfo: memoryInfo,
}