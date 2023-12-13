let memorySections = system.getScript("genericMemorySections.js")


//TODO: placement of BEGIN should be optional in RAM/Flash (4 flash entry points). Add a warning on case non-default options are chosen
// Flash sectors 4-7 only available in 280025/23
// Flash sectors 8-15 only available in 280025


var memoryInfo = {
    combinableMemories : [
        "RAMM",
        "RAMLS",
        "RAMGS",
        "FLASH"
    ],
    codeStartLocations : [
        {displayName : "Boot from RAMM0",               name : "0x000000"},
        {displayName : "Boot from Flash Sector 0",      name : "0x080000"},
        {displayName : "Boot from Flash Sector 4",      name : "0x088000"},
        {displayName : "Boot from Flash Sector 8",      name : "0x0A8000"},
        {displayName : "Boot from Flash Sector 14 end", name : "0x08EFF0"},
    ],
    memorySections: memorySections.CompilerMemorySections,
    memoryRanges : [
        {name : "RAMM0",             group : "RAMM",  origin : 0x000128, length : 0x0002D8, description : "The initial bytes of RAMM0 is reserved for BootROM"},
        {name : "RAMM1",             group : "RAMM",  origin : 0x000400, length : 0x0003F8, description : "Last 8 words of RAMM1 is reserved as per the errata advisory 'Memory: Prefetching Beyond Valid Memory'"},

        {name : "RAMLS4",            group : "RAMLS", origin : 0x00A000, length:  0x000800},
        {name : "RAMLS5",            group : "RAMLS", origin : 0x00A800, length:  0x000800},
        {name : "RAMLS6",            group : "RAMLS", origin : 0x00B000, length:  0x000800},
        {name : "RAMLS7",            group : "RAMLS", origin : 0x00B800, length:  0x000800},

        {name : "RAMGS0",            group : "RAMGS", origin : 0x00C000, length:  0x0007F8, description : "Last 8 words of RAMGS0 is reserved as per the errata advisory 'Memory: Prefetching Beyond Valid Memory'"},

        {name : "FLASH_BANK0_SEC0",  group : "FLASH", origin:  0x080000, length : 0x001000},
        {name : "FLASH_BANK0_SEC1",  group : "FLASH", origin:  0x081000, length : 0x001000},
        {name : "FLASH_BANK0_SEC2",  group : "FLASH", origin:  0x082000, length : 0x001000},
        {name : "FLASH_BANK0_SEC3",  group : "FLASH", origin:  0x083000, length : 0x001000},
        {name : "FLASH_BANK0_SEC4",  group : "FLASH", origin:  0x084000, length : 0x001000},
        {name : "FLASH_BANK0_SEC5",  group : "FLASH", origin:  0x085000, length : 0x001000},
        {name : "FLASH_BANK0_SEC6",  group : "FLASH", origin:  0x086000, length : 0x001000},
        {name : "FLASH_BANK0_SEC7",  group : "FLASH", origin:  0x087000, length : 0x001000},
        {name : "FLASH_BANK0_SEC8",  group : "FLASH", origin:  0x088000, length : 0x001000},
        {name : "FLASH_BANK0_SEC9",  group : "FLASH", origin:  0x089000, length : 0x001000},
        {name : "FLASH_BANK0_SEC10", group : "FLASH", origin:  0x08A000, length : 0x001000},
        {name : "FLASH_BANK0_SEC11", group : "FLASH", origin:  0x08B000, length : 0x001000},
        {name : "FLASH_BANK0_SEC12", group : "FLASH", origin:  0x08C000, length : 0x001000},
        {name : "FLASH_BANK0_SEC13", group : "FLASH", origin:  0x08D000, length : 0x001000},
        {name : "FLASH_BANK0_SEC14", group : "FLASH", origin:  0x08E000, length : 0x001000},
        {name : "FLASH_BANK0_SEC15", group : "FLASH", origin:  0x08F000, length : 0x000FF0, description : "Last 16 words of Flash is reserved as per the errata advisory 'Memory: Prefetching Beyond Valid Memory'"},

        {name : "RESET", origin : 0x3FFFC0, length  : 0x000002}
    ],

    ramDefault :{
        "ramfunc"    : ["RAMM0"],
        "text"       : ["RAMLS4", "RAMLS5", "RAMLS6", "RAMLS7", "RAMGS0"],
        "cinit"      : ["RAMM0"],
        "switch"     : ["RAMM0"],
        "stack"      : ["RAMM1"],
        "bss"        : ["RAMLS4"],
        "init_array" : ["RAMM0"],
        "const"      : ["RAMLS4"],
        "data"       : ["RAMLS4"],
        "sysmem"     : ["RAMLS4"],
        "ovly"       : [],
        "codestart"  : "0x000000"
    },
    flashDefault :{
        "ramfunc"    : ["FLASH_BANK0_SEC1"],
        "ramfuncRun" : ["RAMLS4"],
        "text"       : ["FLASH_BANK0_SEC2", "FLASH_BANK0_SEC3", "FLASH_BANK0_SEC4"],
        "binit"      : ["FLASH_BANK0_SEC1"],
        "cinit"      : ["FLASH_BANK0_SEC1"],
        "switch"     : ["FLASH_BANK0_SEC1"],
        "stack"      : ["RAMM1"],
        "bss"        : ["RAMLS5"],
        "init_array" : ["FLASH_BANK0_SEC1"],
        "const"      : ["FLASH_BANK0_SEC4"],
        "data"       : ["RAMLS5"],
        "sysmem"     : ["RAMLS5"],
        "ovly"       : ["FLASH_BANK0_SEC1"],
        "codestart"  : "0x080000"
    }
}


exports = {
    memoryInfo: memoryInfo,
}