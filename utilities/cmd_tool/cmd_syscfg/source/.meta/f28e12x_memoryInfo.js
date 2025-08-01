let memorySections = system.getScript("genericMemorySections.js")

var memoryInfo = {
    combinableMemories : [
        "RAMM",
        "RAMGS",
        "FLASH"
    ],
    codeStartLocations : [
        {displayName : "Boot from RAMM0",           name : "0x000000"},
        {displayName : "Boot from Flash Bank 0 Sector 0_63",  name : "0x080000"},
    ],
    memorySections:  memorySections.CompilerMemorySections.concat(memorySections.CLACompilerMemorySections),
    memoryRanges : [
        {name : "RAMM0",   group : "RAMM", origin  : 0x000128, length : 0x0002D8, description : "The initial bytes of RAMM0 is reserved for BootROM"},
        {name : "RAMM1",   group : "RAMM", origin  : 0x000400, length : 0x000400, description : "Last 8 words of RAMM1 is reserved as per the errata advisory 'Memory: Prefetching Beyond Valid Memory'"},

        {name : "RAMGS0",  group : "RAMGS", origin : 0x00C000, length : 0x001800},

        {name : "FLASH_BANK0_SEC_0_63",  group : "FLASH", origin : 0x080000, length : 0x10000}, 

        {name : "RESET", origin : 0x3FFFC0, length : 0x000002}
    ],
    ramDefault :{
        "ramfunc"    : ["RAMM0"],
        "text"       : ["RAMGS0"],
        "cinit"      : ["RAMM0"],
        "switch"     : ["RAMM0"],
        "stack"      : ["RAMM1"],
        "bss"        : ["RAMGS0"],
        "init_array" : ["RAMM0"],
        "const"      : ["RAMGS0"],
        "data"       : ["RAMGS0"],
        "sysmem"     : ["RAMGS0"],
        "ovly"       : [],
        "codestart"  : "0x000000"
    },
    flashDefault :{
        "ramfunc"    : ["FLASH_BANK0_SEC_0_63"],
        "ramfuncRun" : ["RAMGS0"],
        "text"       : ["FLASH_BANK0_SEC_0_63"],
        "binit"      : ["FLASH_BANK0_SEC_0_63"],
        "cinit"      : ["FLASH_BANK0_SEC_0_63"],
        "switch"     : ["FLASH_BANK0_SEC_0_63"],
        "stack"      : ["RAMM1"],
        "bss"        : ["RAMGS0"],
        "init_array" : ["FLASH_BANK0_SEC_0_63"],
        "const"      : ["FLASH_BANK0_SEC_0_63"],
        "data"       : ["RAMGS0"],
        "sysmem"     : ["RAMGS0"],
        "ovly"       : ["FLASH_BANK0_SEC_0_63"],
        "codestart"  : "0x080000"
    }
}

exports = {
    memoryInfo: memoryInfo,
}