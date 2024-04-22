let memorySections = system.getScript("genericMemorySections.js")

var memoryInfo = {
    combinableMemories : [
        "RAMM",
        "RAMLS",
        "RAMGS",
        "FLASH"
    ],
    codeStartLocations : [
        {displayName : "Boot from RAMM0",           name : "0x000000"},
        {displayName : "Boot from Flash Bank 0 Sector 0",  name : "0x080000"},
        {displayName : "Boot from Flash Bank 1 Sector 0",  name : "0x0A0000"},
        {displayName : "Boot from Flash Bank 2 Sector 0",  name : "0x0C0000"},
        {displayName : "Boot from Flash Bank 3 Sector 0",  name : "0x0E0000"},
        {displayName : "Boot from Flash Bank 4 Sector 0",  name : "0x100000"},
    ],
    memorySections:  memorySections.CompilerMemorySections.concat(memorySections.CLACompilerMemorySections),
    memoryRanges : [
        {name : "RAMM0",   group : "RAMM", origin  : 0x000128, length : 0x0002D8, description : "The initial bytes of RAMM0 is reserved for BootROM"},
        {name : "RAMM1",   group : "RAMM", origin  : 0x000400, length : 0x000400, description : "Last 8 words of RAMM1 is reserved as per the errata advisory 'Memory: Prefetching Beyond Valid Memory'"},

        {name : "RAMLS8_CLA",  group : "RAMLS", origin : 0x004000, length : 0x002000},
        {name : "RAMLS9_CLA",  group : "RAMLS", origin : 0x006000, length : 0x002000},

        {name : "RAMLS0",  group : "RAMLS", origin : 0x008000, length : 0x000800},
        {name : "RAMLS1",  group : "RAMLS", origin : 0x008800, length : 0x000800},
        {name : "RAMLS2",  group : "RAMLS", origin : 0x009000, length : 0x000800},
        {name : "RAMLS3",  group : "RAMLS", origin : 0x009800, length : 0x000800},
        {name : "RAMLS4",  group : "RAMLS", origin : 0x00A000, length : 0x000800},
        {name : "RAMLS5",  group : "RAMLS", origin : 0x00A800, length : 0x000800},
        {name : "RAMLS6",  group : "RAMLS", origin : 0x00B000, length : 0x000800},
        {name : "RAMLS7",  group : "RAMLS", origin : 0x00B800, length : 0x000800},
        {name : "RAMLS8",  group : "RAMLS", origin : 0x014000, length : 0x002000},
        {name : "RAMLS9",  group : "RAMLS", origin : 0x016000, length : 0x002000},

        {name : "RAMGS0",  group : "RAMGS", origin : 0x00C000, length : 0x002000},
        {name : "RAMGS1",  group : "RAMGS", origin : 0x00E000, length : 0x002000},
        {name : "RAMGS2",  group : "RAMGS", origin : 0x010000, length : 0x002000},
        {name : "RAMGS3",  group : "RAMGS", origin : 0x012000, length : 0x002000},

        {name : "FLASH_BANK0",  group : "FLASH", origin : 0x080000, length : 0x20000}, // slightly different address for flash and ram linker.cmd files
        {name : "FLASH_BANK1",  group : "FLASH", origin : 0x0A0000, length : 0x20000},
        {name : "FLASH_BANK2",  group : "FLASH", origin : 0x0C0000, length : 0x20000},
        {name : "FLASH_BANK3",  group : "FLASH", origin : 0x0E0000, length : 0x20000},
        {name : "FLASH_BANK4",  group : "FLASH", origin : 0x100000, length : 0x20000, description : "Last 16 words of Flash is reserved as per the errata advisory 'Memory: Prefetching Beyond Valid Memory'"},

        {name : "CLATOCPURAM", group : "CLATOCPUMSGRAM", origin : 0x001480, length : 0x000080}, // Following names from template linker.cmd files? 
        {name : "CPUTOCLARAM", group : "CPUTOCLAMSGRAM", origin : 0x001500, length : 0x000080},
        {name : "CLATODMARAM", origin : 0x001680, length : 0x000080},
        {name : "DMATOCLARAM", origin : 0x001700, length : 0x000080},

        {name : "RESET", origin : 0x3FFFC0, length : 0x000002}
    ],
    ramDefault :{
        "ramfunc"    : ["RAMM0"],
        "text"       : ["RAMLS0", "RAMLS1", "RAMLS2", "RAMLS3"],
        "cinit"      : ["RAMM0"],
        "switch"     : ["RAMM0"],
        "stack"      : ["RAMM1"],
        "bss"        : ["RAMLS5"],
        "init_array" : ["RAMM0"],
        "const"      : ["RAMLS5", "RAMLS6"],
        "data"       : ["RAMLS5"],
        "sysmem"     : ["RAMLS4"],
        "ovly"       : [],
        "codestart"  : "0x000000"
    },
    flashDefault :{
        "ramfunc"    : ["FLASH_BANK0"],
        "ramfuncRun" : ["RAMLS0"],
        "text"       : ["FLASH_BANK0", "FLASH_BANK1"],
        "binit"      : ["FLASH_BANK0"],
        "cinit"      : ["FLASH_BANK0"],
        "switch"     : ["FLASH_BANK0"],
        "stack"      : ["RAMM1"],
        "bss"        : ["RAMLS5"],
        "init_array" : ["FLASH_BANK0"],
        "const"      : ["FLASH_BANK0"],
        "data"       : ["RAMLS5"],
        "sysmem"     : ["RAMLS4"],
        "ovly"       : ["FLASH_BANK0"],
        "codestart"  : "0x080000"
    }
}

exports = {
    memoryInfo: memoryInfo,
}