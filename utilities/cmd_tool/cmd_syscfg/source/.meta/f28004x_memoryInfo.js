let memorySections = system.getScript("genericMemorySections.js")


//TODO: placement of BEGIN should be optional in RAM/Flash (4 flash entry points). Add a warning on case non-default options are chosen
// Flash Bank1 not present in 280041/280040
// CLA not present in 280045/42/40

var memoryInfo = {
    combinableMemories : [
        "RAMM",
        "RAMLS",
        "RAMGS",
        "FLASH"
    ],
    codeStartLocations : [
        {displayName : "Boot from RAMM0",                         name : "0x000000"},
        {displayName : "Boot from Flash Bank 0 Sector 0",         name : "0x080000"},
        {displayName : "Boot from Flash Bank 0 End of Sector 14", name : "0x08EFF0"},
        {displayName : "Boot from Flash Bank 1 Sector 0",         name : "0x090000"},
        {displayName : "Boot from Flash Bank 1 End of Sector 14", name : "0x09EFF0"},
    ],
    memorySections:  memorySections.CompilerMemorySections.concat(memorySections.CLACompilerMemorySections),
    memoryRanges : [
        {name : "RAMM0",  group : "RAMM",  origin : 0x0000F6, length : 0x00030A, description : "The initial bytes of RAMM0 is reserved for BootROM"},
        {name : "RAMM1",  group : "RAMM",  origin : 0x000400, length : 0x0003F8, description : "Last 8 words of RAMM1 is reserved as per the errata advisory 'Memory: Prefetching Beyond Valid Memory'"},

        {name : "RAMLS0", group : "RAMLS", origin : 0x008000, length : 0x000800},
        {name : "RAMLS1", group : "RAMLS", origin : 0x008800, length : 0x000800},
        {name : "RAMLS2", group : "RAMLS", origin : 0x009000, length : 0x000800},
        {name : "RAMLS3", group : "RAMLS", origin : 0x009800, length : 0x000800},
        {name : "RAMLS4", group : "RAMLS", origin : 0x00A000, length : 0x000800},
        {name : "RAMLS5", group : "RAMLS", origin : 0x00A800, length : 0x000800},
        {name : "RAMLS6", group : "RAMLS", origin : 0x00B000, length : 0x000800},
        {name : "RAMLS7", group : "RAMLS", origin : 0x00B800, length : 0x000800},

        {name : "RAMGS0", group : "RAMGS", origin : 0x00C000, length : 0x002000},
        {name : "RAMGS1", group : "RAMGS", origin : 0x00E000, length : 0x002000},
        {name : "RAMGS2", group : "RAMGS", origin : 0x010000, length : 0x002000},
        {name : "RAMGS3", group : "RAMGS", origin : 0x012000, length : 0x001FF8,  description : "Last 8 words of RAMGS3 is reserved as per the errata advisory 'Memory: Prefetching Beyond Valid Memory'"},

        {name : "FLASH_BANK0_SEC0",  group : "FLASH",  origin:  0x080000, length : 0x001000},
        {name : "FLASH_BANK0_SEC1",  group : "FLASH",  origin:  0x081000, length : 0x001000},
        {name : "FLASH_BANK0_SEC2",  group : "FLASH",  origin:  0x082000, length : 0x001000},
        {name : "FLASH_BANK0_SEC3",  group : "FLASH",  origin:  0x083000, length : 0x001000},
        {name : "FLASH_BANK0_SEC4",  group : "FLASH",  origin:  0x084000, length : 0x001000},
        {name : "FLASH_BANK0_SEC5",  group : "FLASH",  origin:  0x085000, length : 0x001000},
        {name : "FLASH_BANK0_SEC6",  group : "FLASH",  origin:  0x086000, length : 0x001000},
        {name : "FLASH_BANK0_SEC7",  group : "FLASH",  origin:  0x087000, length : 0x001000},
        {name : "FLASH_BANK0_SEC8",  group : "FLASH",  origin:  0x088000, length : 0x001000},
        {name : "FLASH_BANK0_SEC9",  group : "FLASH",  origin:  0x089000, length : 0x001000},
        {name : "FLASH_BANK0_SEC10", group : "FLASH",  origin:  0x08A000, length : 0x001000},
        {name : "FLASH_BANK0_SEC11", group : "FLASH",  origin:  0x08B000, length : 0x001000},
        {name : "FLASH_BANK0_SEC12", group : "FLASH",  origin:  0x08C000, length : 0x001000},
        {name : "FLASH_BANK0_SEC13", group : "FLASH",  origin:  0x08D000, length : 0x001000},
        {name : "FLASH_BANK0_SEC14", group : "FLASH",  origin:  0x08E000, length : 0x001000},
        {name : "FLASH_BANK0_SEC15", group : "FLASH",  origin:  0x08F000, length : 0x001000},
        {name : "FLASH_BANK1_SEC0 ", group : "FLASH",  origin:  0x090000, length : 0x001000},
        {name : "FLASH_BANK1_SEC1 ", group : "FLASH",  origin:  0x091000, length : 0x001000},
        {name : "FLASH_BANK1_SEC2 ", group : "FLASH",  origin:  0x092000, length : 0x001000},
        {name : "FLASH_BANK1_SEC3 ", group : "FLASH",  origin:  0x093000, length : 0x001000},
        {name : "FLASH_BANK1_SEC4 ", group : "FLASH",  origin:  0x094000, length : 0x001000},
        {name : "FLASH_BANK1_SEC5 ", group : "FLASH",  origin:  0x095000, length : 0x001000},
        {name : "FLASH_BANK1_SEC6 ", group : "FLASH",  origin:  0x096000, length : 0x001000},
        {name : "FLASH_BANK1_SEC7 ", group : "FLASH",  origin:  0x097000, length : 0x001000},
        {name : "FLASH_BANK1_SEC8 ", group : "FLASH",  origin:  0x098000, length : 0x001000},
        {name : "FLASH_BANK1_SEC9 ", group : "FLASH",  origin:  0x099000, length : 0x001000},
        {name : "FLASH_BANK1_SEC10", group : "FLASH",  origin:  0x09A000, length : 0x001000},
        {name : "FLASH_BANK1_SEC11", group : "FLASH",  origin:  0x09B000, length : 0x001000},
        {name : "FLASH_BANK1_SEC12", group : "FLASH",  origin:  0x09C000, length : 0x001000},
        {name : "FLASH_BANK1_SEC13", group : "FLASH",  origin:  0x09D000, length : 0x001000},
        {name : "FLASH_BANK1_SEC14", group : "FLASH",  origin:  0x09E000, length : 0x001000},
        {name : "FLASH_BANK1_SEC15", group : "FLASH",  origin:  0x09F000, length : 0x000FF0,  description : "Last 16 words of Flash is reserved as per the errata advisory 'Memory: Prefetching Beyond Valid Memory'"},

        {name : "CLATOCPU_MSGRAM",   group : "CLATOCPUMSGRAM",  origin : 0x001480, length  : 0x000080},
        {name : "CPUTOCLA_MSGRAM",   group : "CPUTOCLAMSGRAM",  origin : 0x001500, length  : 0x000080},

        {name : "RESET", origin : 0x3FFFC0, length  : 0x000002}
    ],

    ramDefault :{
        "ramfunc"    : ["RAMM0"],
        "text"       : ["RAMLS0", "RAMLS1", "RAMLS2", "RAMLS3", "RAMLS4"],
        "cinit"      : ["RAMM0"],
        "switch"     : ["RAMM0"],
        "stack"      : ["RAMM1"],
        "bss"        : ["RAMLS5"],
        "init_array" : ["RAMM0"],
        "const"      : ["RAMLS5"],
        "data"       : ["RAMLS5"],
        "sysmem"     : ["RAMLS5"],
        "ovly"       : [],
        "codestart"  : "0x000000"
    },
    flashDefault :{
        "ramfunc"    : ["FLASH_BANK0_SEC1"],
        "ramfuncRun" : ["RAMLS0"],
        "text"       : ["FLASH_BANK0_SEC2", "FLASH_BANK0_SEC3", "FLASH_BANK0_SEC5"],
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