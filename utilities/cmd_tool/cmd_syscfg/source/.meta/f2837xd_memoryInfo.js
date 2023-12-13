let memorySections = system.getScript("genericMemorySections.js")


// RAMGS12-15 not present in 376D/374D
// Flash second half not present in 376D/374D.
// Flash sector names : Use numbers? C2000ware uses A-N
var memoryInfo = {
    combinableMemories : [
        "RAMM",
        "RAMD",
        "RAMLS",
        "RAMGS",
        "FLASH"
    ],
    codeStartLocations : [
        {displayName : "Boot from RAMM",   name : "0x000000"},
        {displayName : "Boot from Flash",  name : "0x080000"},
    ],
    memorySections:  memorySections.CompilerMemorySections.concat(memorySections.CLACompilerMemorySections),
    memoryRanges_cpu2 :[
        {name : "RAMM0",   group : "RAMM", origin  : 0x0000A2, length : 0x00035E, description : "The initial bytes of RAMM0 is reserved for BootROM"},
    ],    memoryRanges : [
        {name : "RAMM0",   group : "RAMM", origin  : 0x000123, length : 0x0002DD, description : "The initial bytes of RAMM0 is reserved for BootROM"},
        {name : "RAMM1",   group : "RAMM", origin  : 0x000400, length : 0x0003F8, description : "Last 8 words of RAMM1 is reserved as per the errata advisory 'Memory: Prefetching Beyond Valid Memory'"},

        {name : "RAMLS0",  group : "RAMLS", origin : 0x008000, length : 0x000800},
        {name : "RAMLS1",  group : "RAMLS", origin : 0x008800, length : 0x000800},
        {name : "RAMLS2",  group : "RAMLS", origin : 0x009000, length : 0x000800},
        {name : "RAMLS3",  group : "RAMLS", origin : 0x009800, length : 0x000800},
        {name : "RAMLS4",  group : "RAMLS", origin : 0x00A000, length : 0x000800},
        {name : "RAMLS5",  group : "RAMLS", origin : 0x00A800, length : 0x000800},

        {name : "RAMD0",   group : "RAMD", origin  : 0x00B000, length : 0x000800},
        {name : "RAMD1",   group : "RAMD", origin  : 0x00B800, length : 0x000800},

        {name : "RAMGS0",  group : "RAMGS", origin : 0x00C000, length : 0x001000},
        {name : "RAMGS1",  group : "RAMGS", origin : 0x00D000, length : 0x001000},
        {name : "RAMGS2",  group : "RAMGS", origin : 0x00E000, length : 0x001000},
        {name : "RAMGS3",  group : "RAMGS", origin : 0x00F000, length : 0x001000},
        {name : "RAMGS4",  group : "RAMGS", origin : 0x010000, length : 0x001000},
        {name : "RAMGS5",  group : "RAMGS", origin : 0x011000, length : 0x001000},
        {name : "RAMGS6",  group : "RAMGS", origin : 0x012000, length : 0x001000},
        {name : "RAMGS7",  group : "RAMGS", origin : 0x013000, length : 0x001000},
        {name : "RAMGS8",  group : "RAMGS", origin : 0x014000, length : 0x001000},
        {name : "RAMGS9",  group : "RAMGS", origin : 0x015000, length : 0x001000},
        {name : "RAMGS10", group : "RAMGS", origin : 0x016000, length : 0x001000},
        {name : "RAMGS11", group : "RAMGS", origin : 0x017000, length : 0x001000},
        {name : "RAMGS12", group : "RAMGS", origin : 0x018000, length : 0x001000},
        {name : "RAMGS13", group : "RAMGS", origin : 0x019000, length : 0x001000},
        {name : "RAMGS14", group : "RAMGS", origin : 0x01A000, length : 0x001000},
        {name : "RAMGS15", group : "RAMGS", origin : 0x01B000, length : 0x000FF8,  description : "Last 8 words of RAMGS15 is reserved as per the errata advisory 'Memory: Prefetching Beyond Valid Memory'"},


        {name : "FLASHA", group : "FLASH", origin : 0x080000, length : 0x002000, description : "Flash Bank 0"},
        {name : "FLASHB", group : "FLASH", origin : 0x082000, length : 0x002000, description : "Flash Bank 0"},
        {name : "FLASHC", group : "FLASH", origin : 0x084000, length : 0x002000, description : "Flash Bank 0"},
        {name : "FLASHD", group : "FLASH", origin : 0x086000, length : 0x002000, description : "Flash Bank 0"},
        {name : "FLASHE", group : "FLASH", origin : 0x088000, length : 0x008000, description : "Flash Bank 0"},
        {name : "FLASHF", group : "FLASH", origin : 0x090000, length : 0x008000, description : "Flash Bank 0"},
        {name : "FLASHG", group : "FLASH", origin : 0x098000, length : 0x008000, description : "Flash Bank 0"},
        {name : "FLASHH", group : "FLASH", origin : 0x0A0000, length : 0x008000, description : "Flash Bank 0"},
        {name : "FLASHI", group : "FLASH", origin : 0x0A8000, length : 0x008000, description : "Flash Bank 0"},
        {name : "FLASHJ", group : "FLASH", origin : 0x0B0000, length : 0x008000, description : "Flash Bank 0"},
        {name : "FLASHK", group : "FLASH", origin : 0x0B8000, length : 0x002000, description : "Flash Bank 0"},
        {name : "FLASHL", group : "FLASH", origin : 0x0BA000, length : 0x002000, description : "Flash Bank 0"},
        {name : "FLASHM", group : "FLASH", origin : 0x0BC000, length : 0x002000, description : "Flash Bank 0"},
        {name : "FLASHN", group : "FLASH", origin : 0x0BE000, length : 0x001FF0, description : "Flash Bank 0. Last 16 words of Flash is reserved as per the errata advisory 'Memory: Prefetching Beyond Valid Memory'"},

        {name : "CLATOCPU_MSGRAM", group : "CLATOCPUMSGRAM", origin : 0x001480, length : 0x000080},
        {name : "CPUTOCLA_MSGRAM", group : "CPUTOCLAMSGRAM", origin : 0x001500, length : 0x000080},
        {name : "CPU1TOCPU2RAM",   origin : 0x03FC00, length : 0x000400},
        {name : "CPU2TOCPU1RAM",   origin : 0x03F800, length : 0x000400},

        {name : "RESET" , origin : 0x3FFFC0, length : 0x000002}
    ],

    ramDefault :{
        "ramfunc"    : ["RAMM0"],
        "text"       : ["RAMD0", "RAMD1", "RAMLS0", "RAMLS1", "RAMLS2", "RAMLS3"],
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
        "ramfunc"    : ["FLASHD"],
        "ramfuncRun" : ["RAMLS0"],
        "text"       : ["FLASHB", "FLASHC", "FLASHD", "FLASHE"],
        "binit"      : ["FLASHA"],
        "cinit"      : ["FLASHA"],
        "switch"     : ["FLASHA"],
        "stack"      : ["RAMM1"],
        "bss"        : ["RAMLS5"],
        "init_array" : ["FLASHB"],
        "const"      : ["FLASHF"],
        "data"       : ["RAMLS5"],
        "sysmem"     : ["RAMLS5"],
        "ovly"       : ["FLASHA"],
        "codestart"  : "0x080000"
    }
}

exports = {
    memoryInfo: memoryInfo,
}