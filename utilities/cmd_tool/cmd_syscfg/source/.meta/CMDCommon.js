let meminfo   = system.getScript("/utilities/cmd_tool/cmd_syscfg/source/" + system.deviceData.device.toLowerCase() + "_memoryInfo.js");
let Common   = system.getScript("/driverlib/Common.js");
var memoryInfo = meminfo.memoryInfo;


var LinkerSymbols = [
    {name : "loadStart", displayName : "LOAD_START"},
    {name : "loadEnd",   displayName : "LOAD_END"},
    {name : "loadSize",  displayName : "LOAD_SIZE"},
    {name : "runStart",  displayName : "RUN_START"},
    {name : "runEnd",    displayName : "RUN_END"},
    {name : "runSize",   displayName : "RUN_SIZE"}
]

let memoryNotCPU2Gattino = ["RAMD0", "RAMD1", "RAMLS0", "RAMLS1", "RAMLS2", "RAMLS3", "RAMLS4", "RAMLS5",
     "RAMLS6", "RAMLS7", "RAMLS8", "RAMLS9", "RAMLS8_CLA", "RAMLS9_CLA"]

exports = {
    getDeviceName : getDeviceName,
    numberToHex32 : numberToHex32,
    numberToHex24 : numberToHex24,
    isPowerOf2 : isPowerOf2,
    getCPU2MemoryDiff : getCPU2MemoryDiff,
    getDeviceMemoryInfo: getDeviceMemoryInfo,
    getDeviceMemoryRanges : getDeviceMemoryRanges,
    getDeviceUniqueMemoryRangeGroups: getDeviceUniqueMemoryRangeGroups,
    getDeviceCombinableMemoryRangeGroups: getDeviceCombinableMemoryRangeGroups,
    getDeviceMemorySections : getDeviceMemorySections,
    printDebugObject : printDebugObject,
    isMemoryRangeUsedInCombination : isMemoryRangeUsedInCombination,
    getMemoryRanges: getMemoryRanges,
    getDeviceMemoryRangeInGroup : getDeviceMemoryRangeInGroup,
    getMemoryRangesByGroup: getMemoryRangesByGroup,
    getMemoryRangesInDetail: getMemoryRangesInDetail,
    getSectionsInDetail: getSectionsInDetail,
    getSectionFormat: getSectionFormat,
    getMemoryDescription : getMemoryDescription,
    LinkerSymbols: LinkerSymbols,
    getLSConfig: getLSConfig,
    getGSConfig: getGSConfig
}

function numberToHex32(val)
{
    return "0x" + val.toString(16).padStart(8, '0').toUpperCase()
}

function numberToHex24(val)
{
    return "0x" + val.toString(16).padStart(6, '0').toUpperCase()
}

function isPowerOf2(val)
{
    return (((val & (val-1)) == 0) && val >= 2)
}

function getCPU2MemoryDiff(){
    if (memoryInfo.memoryRanges_cpu2){
    return memoryInfo.memoryRanges_cpu2;
    }
    else{
        return [{name : "null"}]
    }
}

function getDeviceName(){
    return system.deviceData.deviceId;
}

function getDeviceMemoryInfo(){
    return memoryInfo
}

function getDeviceMemoryRanges(){
    return memoryInfo.memoryRanges;
}

function getDeviceMemorySections(){
    return memoryInfo.memorySections;
}

function getDeviceUniqueMemoryRangeGroups(){
    return Array.from(new Set(memoryInfo.memoryRanges.map(item => item.group)));
}

function getDeviceMemoryRangeInGroup(group)
{
    var memInfos = [];
    for (var memInfo of getDeviceMemoryRanges())
    {
        if (memInfo.group == group)
        {
            memInfos.push(memInfo)
        }
    }
    return memInfos;
}

function getDeviceCombinableMemoryRangeGroups(){
    return memoryInfo.combinableMemories;
}

function printDebugObject(obj)
{
    if (obj == null)
    {
        console.log("Object is null");
        return;
    }
    var keys = Object.keys(obj);
    for (var key in keys)
    {
        console.log(keys[key] + " : " + obj[keys[key]]);
    }
}

//
// returns true if not in any combination range
// returns false else
//
function isMemoryRangeUsedInCombination(inst, memRangeName)
{
    for (var memGroup of getDeviceCombinableMemoryRangeGroups())
    {
        if (inst[memGroup + "memoryCombination"] && ((memGroup + "memoryCombination") in inst))
        {
            for (var memCombo of inst[memGroup + "memoryCombination"])
            {
                if (memCombo.combination.includes(memRangeName))
                {
                    return true;
                }
            }
        }
    }
    return false;
}

//
// returns true if not in any combination range
// returns false else
//
function getMemoryRangeOwnerInCombination(inst, memRangeName)
{
    for (var memGroup of getDeviceCombinableMemoryRangeGroups())
    {
        if (inst[memGroup + "memoryCombination"] && ((memGroup + "memoryCombination") in inst))
        {
            for (var memCombo of inst[memGroup + "memoryCombination"])
            {
                if (memCombo.combination.includes(memRangeName))
                {
                    return memCombo.$name;
                }
            }
        }
    }
    return null;
}


function getMemoryRanges(inst)
{
    const currentOptions = [];
    for (var memRange of getDeviceMemoryRanges())
    {
        if (!isMemoryRangeUsedInCombination(inst, memRange.name))
        {
            if (!["f28p65x"].includes(Common.getDeviceName().toLowerCase()) || Common.isContextCPU1() || !memoryNotCPU2Gattino.includes(memRange.name)){
                currentOptions.push({
                    name: memRange.name
                });
            }
        }
    }

    for (var memGroup of getDeviceCombinableMemoryRangeGroups())
    {
        if (inst[memGroup + "memoryCombination"] && ((memGroup + "memoryCombination") in inst))
        {
            for (var memCombo of inst[memGroup + "memoryCombination"])
            {
                    currentOptions.push({
                        name: memCombo.$name
                    });
            }
        }
    }

    return currentOptions
}



function getMemoryRangesByGroup(inst, group)
{
    const currentOptions = [];
    for (var memRange of getDeviceMemoryRanges())
    {
        if (!isMemoryRangeUsedInCombination(inst, memRange.name))
        {
            if (memRange.group == group)
            {
                if (!["f28p65x"].includes(Common.getDeviceName().toLowerCase()) || Common.isContextCPU1() || !memoryNotCPU2Gattino.includes(memRange.name)){
                    currentOptions.push({
                        name: memRange.name
                    });
                }
            }
        }
    }

    for (var memGroup of getDeviceCombinableMemoryRangeGroups())
    {
        if (inst[memGroup + "memoryCombination"] && ((memGroup + "memoryCombination") in inst))
        {
            for (var memCombo of inst[memGroup + "memoryCombination"])
            {
                if (memCombo.group == group)
                {
                        currentOptions.push({
                            name: memCombo.$name
                        });
                }
            }
        }
    }

    return currentOptions
}


// Returns a list of all memory regions including the combined ones
// The list includes the region name, origin and length
// The list is sorted by address
function getMemoryRangesInDetail(inst)
{
    var MemRanges = [];
    var CPU2mems = getCPU2MemoryDiff();
    var CPU2memNames = [];
    CPU2mems.forEach((element, index) => 
    {
        CPU2memNames.push(element.name)
    });
    for (var memRange of getDeviceMemoryRanges())
    {
        if (!isMemoryRangeUsedInCombination(inst, memRange.name))
        {
            var memDiff = {};
            CPU2mems.forEach((element, index) => 
            {
                if (element.name == memRange.name){
                    memDiff = element
                } 
            });
            if (Common.isContextCPU2() && CPU2memNames.includes(memRange.name)){
                if (memDiff.group != "DELETE"){
                    MemRanges.push({
                        name   : memDiff.name,
                        origin : numberToHex24(memDiff.origin),
                        length : numberToHex24(memDiff.length),
                        group  : memDiff.group,
                        config : memDiff.name.startsWith("RAMLS") ? getLSConfig(memDiff.name) :
                                memDiff.name.startsWith("RAMGS") ? getGSConfig(memDiff.name) : 
                                memDiff.name.includes("CLATOCPU","CPUTOCLA") ? getCLAMessageRAMConfig(memDiff.name) :
                                memDiff.name.includes("FLASH") ? getFlashMuxConfig(memDiff.name) : undefined
                    });
                }
            }
            else{
            MemRanges.push({
                name   : memRange.name,
                origin : numberToHex24(memRange.origin),
                length : numberToHex24(memRange.length),
                group  : memRange.group,
                config : memRange.name.startsWith("RAMLS") ? getLSConfig(memRange.name) :
                         memRange.name.startsWith("RAMGS") ? getGSConfig(memRange.name) : 
                         memRange.name.includes("CLATOCPU","CPUTOCLA") ? getCLAMessageRAMConfig(memRange.name) :
                         memRange.name.includes("FLASH") ? getFlashMuxConfig(memRange.name) : undefined
            });
            }
        }
    }

    for (var memGroup of getDeviceCombinableMemoryRangeGroups())
    {
        if (inst[memGroup + "memoryCombination"] && ((memGroup + "memoryCombination") in inst))
        {
            for (var memCombo of inst[memGroup + "memoryCombination"])
            {
                var totalLen = 0
                var origin = 0xFFFFFFFF
                var memConfig = undefined

                for (var m of getDeviceMemoryRangeInGroup(memGroup))
                {
                    if(memCombo.combination.includes(m.name))
                    {
                        origin = Math.min(origin, m.origin)
                        totalLen += m.length
                        memConfig = m.name.startsWith("RAMLS") ? getLSConfig(m.name) :
                                    m.name.startsWith("RAMGS") ? getGSConfig(m.name) : undefined
                    }
                }

                MemRanges.push({
                    name   : memCombo.$name,
                    origin : numberToHex24(origin),
                    length : numberToHex24(totalLen),
                    group  : memGroup,
                    config : memConfig
                });
            }
        }
    }

    return MemRanges.sort((a,b) => (a.origin - b.origin))
}


function getSectionsInDetail(inst){
    var Sections = []
    for (var section of memoryInfo.memorySections)
    {
        Sections.push({
            name                        : section.name,
            inst                        : inst,
            type                        : "compiler",
            sectionName                 : section.sectionName,
            sectionMemory               : inst["sectionMemory_" + section.name],
            sectionRunFromDifferentAddr : inst["sectionRunFromDifferentAddr_" + section.name],
            sectionRun                  : inst["sectionRun_" + section.name],
            sectionBinit                : inst["sectionBinit_" + section.name],
            sectionAlignEnable          : inst["sectionAlignEnable_" + section.name],
            sectionAlign                : inst["sectionAlign_" + section.name],
            sectionFillEnable           : inst["sectionFillEnable_" + section.name],
            sectionFill                 : inst["sectionFill_" + section.name],
            sectionSymbols              : inst["sectionSymbols_" + section.name],
            sectionType                 : inst["sectionType_" + section.name],
        })
    }
    for (var userSection of inst["userSection"])
    {
        var sectName = userSection["sectionName"]
        var libName  = userSection["libraryName"]
        var objName  = userSection["objectName"]

        var sectionDetails = ""
        if(sectName.length != 0)
            sectionDetails = "*(" + sectName + ")"
        if((libName.length != 0) &&  (objName.length != 0))
            sectionDetails = libName + "<" + objName + ">" + sectionDetails.replace("*", "")
        if((libName.length != 0) &&  (objName.length == 0))
            sectionDetails = libName + sectionDetails.replace("*", "")
        if((libName.length == 0) &&  (objName.length != 0))
            sectionDetails = objName + sectionDetails.replace("*", "")

        sectionDetails = userSection.$name + " { " + sectionDetails + " }"

        Sections.push({
            name                        : userSection.$name,
            inst                        : userSection,
            type                        : "user",
            sectionName                 : sectionDetails,
            sectionMemory               : userSection["sectionMemory"],
            sectionRunFromDifferentAddr : userSection["sectionRunFromDifferentAddr"],
            sectionRun                  : userSection["sectionRun"],
            sectionBinit                : userSection["sectionBinit"],
            sectionAlignEnable          : userSection["sectionAlignEnable"],
            sectionAlign                : userSection["sectionAlign"],
            sectionFillEnable           : userSection["sectionFillEnable"],
            sectionFill                 : userSection["sectionFill"],
            sectionSymbols              : userSection["sectionSymbols"],
            sectionType                 : userSection["sectionType"],
        })
    }
    // TODO: Add other library sections

    return Sections;
}

// Returns the section details to be added in the cmd file
 function getSectionFormat(section)
{
    var spaces = " ".repeat(Math.max(20 - section.sectionName.length, 1))
    var text   = "    "

    // codestart will use absolute address
    if(section.name == "codestart")
    {
        text += "codestart" + spaces + " : >  " + section.sectionMemory
        return text
    }

    // skip the line if memory is not selected
    if(section.sectionMemory.length == 0)
    {
        return ""
    }

    // : is not used in case of custom output sections (used in user sections)
    if(section.type == "user")
        var colon = "   "
    else
        var colon = " : "

    if (section.sectionRunFromDifferentAddr && (section.sectionRun.length != 0))
    {
        var arrowLoad = (section.sectionMemory.length > 1) ?  ">>" : "> "
        var arrowRun  = (section.sectionRun.length > 1)    ?  ">>" : "> "
        var copyTable = section.sectionBinit ?  "BINIT" : "copyTable_" + section.name
        text += section.sectionName + spaces + colon + "   LOAD " + arrowLoad + " " + section.sectionMemory.join(" | ") +",\n" +
                             " ".repeat(30) + "RUN  " + arrowRun  + " " + section.sectionRun.join(" | ") + ",\n" +
                             " ".repeat(30) + "TABLE(" + copyTable + ")"
    }
    else
    {
        var arrow = (section.sectionMemory.length > 1) ?  ">>" : "> "
        text += section.sectionName + spaces + colon + arrow + " " + section.sectionMemory.join(" | ")
    }

    for (var sym of LinkerSymbols)
    {
        if (section.sectionSymbols.includes(sym.name))
            text += ",\n" + " ".repeat(30) + sym.displayName + "(" + sym.name  + "_" + section.name + ")"
    }


    if(section.sectionAlignEnable)
        text += ",\n" + " ".repeat(30) + "ALIGN(" + section.sectionAlign + ")"

    if(section.sectionFillEnable)
        text += ",\n" + " ".repeat(30) + "FILL(" + section.sectionFill + ")"

    if(section.sectionType != "None")
        text += ",\n" + " ".repeat(30) +  "TYPE(" + section.sectionType + ")"

    return text
}

function getLSConfig(mem)
{
    let memcfg   = system.modules["/driverlib/memcfg.js"];
    var stat = undefined;
    if (memcfg && memcfg.$static){
        stat = memcfg.$static
    }
    if(stat)
    {
        var varName = "config_MEMCFG_SECT_" + mem.replace("RAM", "")
        return stat[varName]
    }
    else
    {
        return undefined
    }
}

function getGSConfig(mem)
{    
    let memcfg   = system.modules["/driverlib/memcfg.js"];
    var stat = undefined;
    if (memcfg && memcfg.$static){
        stat = memcfg.$static
    }
    if(stat)
    {
        var varName = "config_MEMCFG_SECT_" + mem.replace("RAM", "")
        if (stat[varName])
        {
            return stat[varName].replace("MEMCFG_GSRAMMASTER_", "")
        } else {
            return undefined
        }
    }
    else
    {
        return undefined
    }
}

function getFlashMuxConfig(mem)
{    
    let memcfg   = system.modules["/driverlib/memcfg.js"];
    var stat = undefined;
    if (memcfg && memcfg.$static){
        stat = memcfg.$static
    }
    if(stat)
    {
        var varName = "config_SYSCTL_FLASH" + mem.replace("FLASH", "")
        if (stat[varName])
        {
            return stat[varName].replace("SYSCTL_CPUSEL_", "")
        } else {
            return undefined
        }
    }
    else
    {
        return undefined
    }
}

function getCLAMessageRAMConfig(mem)
{
    let memcfg   = system.modules["/driverlib/memcfg.js"];
    var stat = undefined;
    if (memcfg && memcfg.$static){
        stat = memcfg.$static
    }
    if(stat)
    {
        var varName = "init_MEMCFG_SECT"
        if (mem.includes("CLATOCPU"))
            varName += "_MSGCLA1TOCPU"
        else if (mem.includes("CPUTOCLA"))
            varName += "_MSGCPUTOCLA1"
        return stat[varName]
    }
    else
    {
        return undefined
    }
}

// Returns the section details to be added in the cmd file
function getMemoryDescription(mem)
{

    if(mem.startsWith("RAMM") || mem.startsWith("RAMD"))
    {
        return "C28x only memory"
    }
    else if (mem.startsWith("RAMLS"))
    {
        var config = getLSConfig(mem)
        if(config)
            return config
        else
            return "Shared with C28x and CLA. Owner not configured in Memcfg"

    }
    else if (mem.startsWith("RAMGS") && ["F2838x","F2837xd"].includes(getDeviceName()))
    {
        var config = getGSConfig(mem)
        if(config)
            return config + " memory. Shared with C28x and DMA"
        else
            return "Shared with CPU1 and CPU2 subsystems. Both C28x and DMA has access. Owner subsystem not configured in Memcfg"
    }
    else
    {
        return "Shared with C28x and DMA"
    }
}