let memorySections = system.getScript("genericMemorySections.js")


//TODO: placement of BEGIN should be optional in RAM/Flash (4 flash entry points). Add a warning in case non-default options are chosen
// In case of CPU2, additional entry points are available. CPU1 application should invoke Device_bootCPU2 with the configured boot mode.

var memoryInfo = {
    combinableMemories : [
        "RAMM",
        "RAMD",
        "RAMLS",
        "RAMGS",
        "FLASH"
    ],
    codeStartLocations : [
        {displayName : "Boot from RAMM0",           name : "0x000000"},
        {displayName : "Boot from Flash Sector 0",  name : "0x080000"},
        {displayName : "Boot from Flash Sector 4",  name : "0x088000"},
        {displayName : "Boot from Flash Sector 8",  name : "0x0A8000"},
        {displayName : "Boot from Flash Sector 13", name : "0x0BE000"},
    ],
    memorySections:  memorySections.CompilerMemorySections.concat(memorySections.CLACompilerMemorySections),
    memoryRanges_cpu2 :[
        {name : "RAMM0",   group : "RAMM", origin  : 0x0001A9, length : 0x000257, description : "The initial bytes of RAMM0 is reserved for BootROM"},
    ],
    memoryRanges : [
        {name : "RAMM0",   group : "RAMM", origin  : 0x0001B1, length : 0x00024F, description : "The initial bytes of RAMM0 is reserved for BootROM"},
        {name : "RAMM1",   group : "RAMM", origin  : 0x000400, length : 0x0003F8, description : "Last 8 words of RAMM1 is reserved as per the errata advisory 'Memory: Prefetching Beyond Valid Memory'"},

        {name : "RAMLS0",  group : "RAMLS", origin : 0x008000, length : 0x000800},
        {name : "RAMLS1",  group : "RAMLS", origin : 0x008800, length : 0x000800},
        {name : "RAMLS2",  group : "RAMLS", origin : 0x009000, length : 0x000800},
        {name : "RAMLS3",  group : "RAMLS", origin : 0x009800, length : 0x000800},
        {name : "RAMLS4",  group : "RAMLS", origin : 0x00A000, length : 0x000800},
        {name : "RAMLS5",  group : "RAMLS", origin : 0x00A800, length : 0x000800},
        {name : "RAMLS6",  group : "RAMLS", origin : 0x00B000, length : 0x000800},
        {name : "RAMLS7",  group : "RAMLS", origin : 0x00B800, length : 0x000800},

        {name : "RAMD0",   group : "RAMD", origin  : 0x00C000, length : 0x000800},
        {name : "RAMD1",   group : "RAMD", origin  : 0x00C800, length : 0x000800},

        {name : "RAMGS0",  group : "RAMGS", origin : 0x00D000, length : 0x001000},
        {name : "RAMGS1",  group : "RAMGS", origin : 0x00E000, length : 0x001000},
        {name : "RAMGS2",  group : "RAMGS", origin : 0x00F000, length : 0x001000},
        {name : "RAMGS3",  group : "RAMGS", origin : 0x010000, length : 0x001000},
        {name : "RAMGS4",  group : "RAMGS", origin : 0x011000, length : 0x001000},
        {name : "RAMGS5",  group : "RAMGS", origin : 0x012000, length : 0x001000},
        {name : "RAMGS6",  group : "RAMGS", origin : 0x013000, length : 0x001000},
        {name : "RAMGS7",  group : "RAMGS", origin : 0x014000, length : 0x001000},
        {name : "RAMGS8",  group : "RAMGS", origin : 0x015000, length : 0x001000},
        {name : "RAMGS9",  group : "RAMGS", origin : 0x016000, length : 0x001000},
        {name : "RAMGS10", group : "RAMGS", origin : 0x017000, length : 0x001000},
        {name : "RAMGS11", group : "RAMGS", origin : 0x018000, length : 0x001000},
        {name : "RAMGS12", group : "RAMGS", origin : 0x019000, length : 0x001000},
        {name : "RAMGS13", group : "RAMGS", origin : 0x01A000, length : 0x001000},
        {name : "RAMGS14", group : "RAMGS", origin : 0x01B000, length : 0x001000},
        {name : "RAMGS15", group : "RAMGS", origin : 0x01C000, length : 0x000FF8,  description : "Last 8 words of RAMGS15 is reserved as per the errata advisory 'Memory: Prefetching Beyond Valid Memory'"},

        {name : "FLASH0",  group : "FLASH", origin : 0x080000, length : 0x002000},
        {name : "FLASH1",  group : "FLASH", origin : 0x082000, length : 0x002000},
        {name : "FLASH2",  group : "FLASH", origin : 0x084000, length : 0x002000},
        {name : "FLASH3",  group : "FLASH", origin : 0x086000, length : 0x002000},
        {name : "FLASH4",  group : "FLASH", origin : 0x088000, length : 0x008000},
        {name : "FLASH5",  group : "FLASH", origin : 0x090000, length : 0x008000},
        {name : "FLASH6",  group : "FLASH", origin : 0x098000, length : 0x008000},
        {name : "FLASH7",  group : "FLASH", origin : 0x0A0000, length : 0x008000},
        {name : "FLASH8",  group : "FLASH", origin : 0x0A8000, length : 0x008000},
        {name : "FLASH9",  group : "FLASH", origin : 0x0B0000, length : 0x008000},
        {name : "FLASH10", group : "FLASH", origin : 0x0B8000, length : 0x002000},
        {name : "FLASH11", group : "FLASH", origin : 0x0BA000, length : 0x002000},
        {name : "FLASH12", group : "FLASH", origin : 0x0BC000, length : 0x002000},
        {name : "FLASH13", group : "FLASH", origin : 0x0BE000, length : 0x002000,  description : "Last 16 words of Flash is reserved as per the errata advisory 'Memory: Prefetching Beyond Valid Memory'"},

        {name : "CLATOCPU_MSGRAM", group : "CLATOCPUMSGRAM", origin : 0x001480, length : 0x000080},
        {name : "CPUTOCLA_MSGRAM", group : "CPUTOCLAMSGRAM", origin : 0x001500, length : 0x000080},
        {name : "CLATODMA_MSGRAM", origin : 0x001680, length : 0x000080},
        {name : "DMATOCLA_MSGRAM", origin : 0x001700, length : 0x000080},
        {name : "CMTOCPURAM",      origin : 0x038000, length : 0x000800},
        {name : "CPUTOCMRAM",      origin : 0x039000, length : 0x000800},
        {name : "CPU1TOCPU2RAM",   origin : 0x03A000, length : 0x000800},
        {name : "CPU2TOCPU1RAM",   origin : 0x03B000, length : 0x000800},

        {name : "RESET", origin : 0x3FFFC0, length : 0x000002}
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
        "ramfunc"    : ["FLASH3"],
        "ramfuncRun" : ["RAMLS0"],
        "text"       : ["FLASH1", "FLASH2", "FLASH3", "FLASH4"],
        "binit"      : ["FLASH4"],
        "cinit"      : ["FLASH4"],
        "switch"     : ["FLASH1"],
        "stack"      : ["RAMM1"],
        "bss"        : ["RAMLS5"],
        "init_array" : ["FLASH1"],
        "const"      : ["FLASH5"],
        "data"       : ["RAMLS5"],
        "sysmem"     : ["RAMLS5"],
        "ovly"       : ["FLASH1"],
        "codestart"  : "0x080000"
    }
}

exports = {
    memoryInfo: memoryInfo,
}