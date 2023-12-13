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
        {displayName : "Boot from Flash Bank 0 Sector 0",  name : "0x080000"},
        {displayName : "Boot from Flash Bank 1 Sector 0",  name : "0x0A0000"},
        {displayName : "Boot from Flash Bank 2 Sector 0",  name : "0x0C0000"},
        {displayName : "Boot from Flash Bank 3 Sector 0",  name : "0x0E0000"},
        {displayName : "Boot from Flash Bank 4 Sector 0",  name : "0x100000"},
    ],
    memorySections:  memorySections.CompilerMemorySections.concat(memorySections.CLACompilerMemorySections),
    memoryRanges_cpu2 :[
        {name : "RAMD2",   group : "RAMD", origin  : 0x008000, length : 0x002000}, // Are these correct?? From ram linker_cpu2 for gattino 
        {name : "RAMD3",   group : "RAMD", origin  : 0x00A000, length : 0x002000}, // Conflicts with LSRAM locations
        {name : "RAMD4",   group : "RAMD", origin  : 0x00C000, length : 0x002000},
        {name : "RAMD5",   group : "RAMD", origin  : 0x00E000, length : 0x002000}, 
        {name : "RAMD0",  group : "DELETE"}, // Should not be included in CPU2 linker file due to memory location conflicts
        {name : "RAMD1",  group : "DELETE"},
        {name : "RAMLS0",  group : "DELETE"},
        {name : "RAMLS1",  group : "DELETE"},
        {name : "RAMLS2",  group : "DELETE"},
        {name : "RAMLS3",  group : "DELETE"},
        {name : "RAMLS4",  group : "DELETE"},
        {name : "RAMLS5",  group : "DELETE"},
        {name : "RAMLS6",  group : "DELETE"},
        {name : "RAMLS7",  group : "DELETE"},
        {name : "RAMLS8",  group : "DELETE"},
        {name : "RAMLS9",  group : "DELETE"},
        {name : "RAMLS8_CLA",  group : "DELETE"},
        {name : "RAMLS9_CLA",  group : "DELETE"},
    ],
    memoryRanges : [
        {name : "RAMM0",   group : "RAMM", origin  : 0x0001B1, length : 0x00024F, description : "The initial bytes of RAMM0 is reserved for BootROM"},
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
        {name : "RAMLS8",  group : "RAMLS", origin : 0x022000, length : 0x002000},
        {name : "RAMLS9",  group : "RAMLS", origin : 0x024000, length : 0x002000},

        {name : "RAMD0",   group : "RAMD", origin  : 0x00C000, length : 0x002000},
        {name : "RAMD1",   group : "RAMD", origin  : 0x00E000, length : 0x002000},
        {name : "RAMD2",   group : "RAMD", origin  : 0x01A000, length : 0x002000},
        {name : "RAMD3",   group : "RAMD", origin  : 0x01C000, length : 0x002000},
        {name : "RAMD4",   group : "RAMD", origin  : 0x01E000, length : 0x002000},
        {name : "RAMD5",   group : "RAMD", origin  : 0x020000, length : 0x002000},

        {name : "RAMGS0",  group : "RAMGS", origin : 0x010000, length : 0x002000},
        {name : "RAMGS1",  group : "RAMGS", origin : 0x012000, length : 0x002000},
        {name : "RAMGS2",  group : "RAMGS", origin : 0x014000, length : 0x002000},
        {name : "RAMGS3",  group : "RAMGS", origin : 0x016000, length : 0x002000},
        {name : "RAMGS4",  group : "RAMGS", origin : 0x018000, length : 0x002000, description : "Last 8 words of RAMGS15 is reserved as per the errata advisory 'Memory: Prefetching Beyond Valid Memory'"},

        {name : "FLASH_BANK0",  group : "FLASH", origin : 0x080000, length : 0x20000}, // slightly different address for flash and ram linker.cmd files
        {name : "FLASH_BANK1",  group : "FLASH", origin : 0x0A0000, length : 0x20000},
        {name : "FLASH_BANK2",  group : "FLASH", origin : 0x0C0000, length : 0x20000},
        {name : "FLASH_BANK3",  group : "FLASH", origin : 0x0E0000, length : 0x20000},
        {name : "FLASH_BANK4",  group : "FLASH", origin : 0x100000, length : 0x20000, description : "Last 16 words of Flash is reserved as per the errata advisory 'Memory: Prefetching Beyond Valid Memory'"},

        {name : "CLATOCPURAM", group : "CLATOCPUMSGRAM", origin : 0x001480, length : 0x000080}, // Following names from template linker.cmd files? 
        {name : "CPUTOCLARAM", group : "CPUTOCLAMSGRAM", origin : 0x001500, length : 0x000080},
        {name : "CLATODMARAM", origin : 0x001680, length : 0x000080},
        {name : "DMATOCLARAM", origin : 0x001700, length : 0x000080},
        {name : "CPU1TOCPU2RAM",   origin : 0x03A000, length : 0x000800},
        {name : "CPU2TOCPU1RAM",   origin : 0x03B000, length : 0x000800},
        
        {name : "CANA_MSG_RAM",   origin : 0x049000, length : 0x000800},  // included or no? Not included in Tenor
        {name : "CANB_MSG_RAM",   origin : 0x04B000, length : 0x000800},

        {name : "RESET", origin : 0x3FFFC0, length : 0x000002}
    ],
    ramDefault_cpu2 :{
        "ramfunc"    : ["RAMM0"],
        "text"       : ["RAMGS4"],
        "cinit"      : ["RAMM0"],
        "switch"     : ["RAMM0"],
        "stack"      : ["RAMM1"],
        "bss"        : ["RAMGS4"],
        "init_array" : ["RAMM0"],
        "const"      : ["RAMGS4"],
        "data"       : ["RAMGS4"],
        "sysmem"     : ["RAMGS4"],
        "ovly"       : [],
        "codestart"  : "0x000000"
    },
    ramDefault :{
        "ramfunc"    : ["RAMM0"],
        "text"       : ["RAMD0", "RAMD1", "RAMLS0", "RAMLS1", "RAMLS2", "RAMLS3"],
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
    flashDefault_cpu2 :{
        "ramfunc"    : ["FLASH_BANK3"],
        "ramfuncRun" : ["RAMGS4"],
        "text"       : ["FLASH_BANK3", "FLASH_BANK4"],
        "binit"      : ["FLASH_BANK3"],
        "cinit"      : ["FLASH_BANK3"],
        "switch"     : ["FLASH_BANK3"],
        "stack"      : ["RAMM1"],
        "bss"        : ["RAMGS4"],
        "init_array" : ["FLASH_BANK3"],
        "const"      : ["FLASH_BANK3"],
        "data"       : ["RAMGS4"],
        "sysmem"     : ["RAMGS4"],
        "ovly"       : ["FLASH_BANK3"],
        "codestart"  : "0x0E0000"
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