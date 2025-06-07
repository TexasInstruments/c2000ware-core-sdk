"use strict";
/*global exports, system*/
let meminfo   = system.getScript("/utilities/cmd_tool/cmd_syscfg/source/" + system.deviceData.device.toLowerCase() + "_memoryInfo.js");
let CMDCommon = system.getScript("/utilities/cmd_tool/cmd_syscfg/source/CMDCommon.js");
let cmdValidation = 
    system.getScript("/utilities/cmd_tool/cmd_syscfg/source/cmdValidation.js");
let Common   = system.getScript("/driverlib/Common.js");


/* Intro splash on GUI */
let longDescription = `Linker CMD Tool Configuration

For more information on the tool visit: https://www.ti.com/lit/an/sprad49/sprad49.pdf

!!Note!!
You may add multiple instances of linker cmd file configurations. To activate one, you should either :
- Select the active configuration under Global parameters
- Or add a pre-defined symbol with the same name as the instance name

For example: You may have one instance for RAM config (named CMD_RAM) and another for Flash config (named CMD_FLASH).
In the application project, you may have different build configurations 1 for RAM with a predefined symbol "CMD_RAM" and 1 for Flash with a predefined symbol "CMD_FLASH".
If active configuration is selected under Global Parameters, that config remains active for all the project build configurations.
`;

var availableMemoryConfig = []

function addMemoryInfoDisplay(memInfo)
{
    availableMemoryConfig.push(
        {
            name: memInfo.name,
            displayName: memInfo.name,
            collapsed: false,
            config : [
                {
                    name: memInfo.name + "_origin",
                    displayName: "Origin",
                    getValue : function (inst){
                        return memInfo.origin;
                    },
                    default: memInfo.origin,
                    displayFormat: {
                        radix: "hex",
                        bitSize: 32,
                    },
                },
                {
                    name: memInfo.name + "_length",
                    displayName: "Length",
                    getValue : function (inst){
                        return memInfo.length;
                    },
                    default: memInfo.length,
                    displayFormat: {
                        radix: "hex",
                        bitSize: 32,
                    },
                }
            ]
        }
    )    
}

// for (var memInfo of CMDCommon.getDeviceMemoryRanges())
// {
//     addMemoryInfoDisplay(memInfo)    
// }

var groupMemoryConfig = []
const uniqueGroups = CMDCommon.getDeviceUniqueMemoryRangeGroups();
for (var memoryGroup of uniqueGroups){

    var memInfoInGroup = CMDCommon.getDeviceMemoryRanges().filter(
        function(element, index) {
            if (element.group == memoryGroup)
            {
                return element
            }
        }
    );

    var memConfigs = []
    for (var memInfo of memInfoInGroup)
    {
        // memConfigs.push(
        //     {
        //         name : memInfo.name,
        //         description: "If this is checked, this memory cannot be used in a combined memory region.",
        //         default: true
        //     }
        // )
    }

    // groupMemoryConfig.push(
    //     {
    //         displayName: memoryGroup + " Memory",
    //         name: "GROUP_MEMORY_" + memoryGroup,
    //         longDescription: "Select the memory region to include in the linker CMD file, or create new combined" +
    //         " region. You have to deselect the individual memory if you plan to use it in a combined" +
    //         " region.",
    //         config: memConfigs,
    //     },
    // )
}

var groupSectionConfig = []
var groupSectionConfig_C28x = []
var groupSectionConfig_CLA = []
var sections = CMDCommon.getDeviceMemorySections()


groupSectionConfig = [
    {
        name: "GROUP_C28x",
        displayName: "C28x Compiler Sections",
        collapsed: true,
        config: groupSectionConfig_C28x
    }
];
if (!["F28E12x"].includes(Common.getDeviceName()))
{
    groupSectionConfig.push({                
            name: "GROUP_CLA",
            displayName: "CLA Compiler Sections",
            collapsed: true,
            config: groupSectionConfig_CLA       
    })
}

function addSectionToGroup(section)
{
    //
    //
    // ********* NOTE *********
    //
    // If you edit this, you need to edit the userSection.js as well!
    //
    //
    var config =
        {
            name: "GROUP_" + section.name,
            displayName: section.name,
            collapsed: false,
            longDescription : section.description,
            config: [
                {
                    name: "sectionMemory_" + section.name,
                    displayName: "Load Memory",
                    default: [],
                    options: (inst) => {
                        if (section.memoryGroup != undefined)
                        {
                            const currentOptions = CMDCommon.getMemoryRangesByGroup(inst, section.memoryGroup);
                            return currentOptions;
                        }
                        else
                        {
                            const currentOptions = CMDCommon.getMemoryRanges(inst);
                            return currentOptions;
                        }
                    },
                },
                {
                    name: "sectionRunFromDifferentAddr_" + section.name,
                    displayName: "Run From Different Address",
                    default: false,
                    hidden : !section.loadRun,
                    onChange: (inst, ui) => {
                        ui["sectionRun_" + section.name].hidden = !inst["sectionRunFromDifferentAddr_" + section.name]
                        ui["sectionBinit_" + section.name].hidden = !inst["sectionRunFromDifferentAddr_" + section.name]
                    }
                },
                {
                    name: "sectionRun_" + section.name,
                    displayName: "Run From",
                    default: [],
                    hidden: true,
                    options: (inst) => {
                        const currentOptions = CMDCommon.getMemoryRanges(inst);
                        return currentOptions;
                    },
                },
                {
                    name: "sectionBinit_" + section.name,
                    displayName: "Place copy table in BINIT section",
                    longDescription: "- If this option is enabled, the copy tables are placed in .binit (boot-time initialization) section. Target will automatically perform the copying at auto-initialization time. \n - If this option is disabled, the copy table is placed in .ovly section and application need to perform the copy. Sysconfig generates the function CMD_init which performs the copy for all copy tables other that boot time copy tables ",
                    default: true,
                    hidden: true,
                },
                {
                    name: "sectionAlignEnable_" + section.name,
                    displayName: "Enable Alignment",
                    default: false,
                    onChange: (inst, ui) => {
                        ui["sectionAlign_" + section.name].hidden = !inst["sectionAlignEnable_" + section.name]
                    }
                },
                {
                    name: "sectionAlign_" + section.name,
                    displayName: "Alignment in bytes (must be power of 2)",
                    longDescription: "In C28x, byte is 16 bits. ALIGN(8) = aligned to 8 * 16-bit boundary",
                    default: 8,
                    hidden: true
                },
                {
                    name: "sectionFillEnable_" + section.name,
                    displayName: "Fill section with constant",
                    default: false,
                    onChange: (inst, ui) => {
                        ui["sectionFill_" + section.name].hidden = !inst["sectionFillEnable_" + section.name]
                    }
                },
                {
                    name: "sectionFill_" + section.name,
                    displayName: "Fill value",
                    default: 0x0,
                    hidden: true
                },
                {
                    name: "sectionSymbols_" + section.name,
                    displayName: "Add linker symbols",
                    default: [],
                    minSelections: 0,
                    options: CMDCommon.LinkerSymbols
                },
                {
                    name: "sectionType_" + section.name,
                    displayName: "Type",
                    default: "None",
                    options: [
                        { name: "None", displayName: "None"},
                        { name: "DSECT", displayName: "DSECT"},
                        { name: "COPY", displayName: "COPY"},
                        { name: "NOLOAD", displayName: "NOLOAD"},
                        { name: "NOINIT", displayName: "NOINIT"},
                    ]
                },
            ]
        }
    if(section.name.toLowerCase().includes("cla") && !["F28E12x"].includes(Common.getDeviceName()))
        groupSectionConfig_CLA.push(config)
    else
        groupSectionConfig_C28x.push(config)

}

for (var section of sections)
{
    // Different view for codestart section
    if(section.name == "codestart")
    {
        groupSectionConfig_C28x.push(
            {
                name: "GROUP_" + section.name,
                displayName: section.name,
                collapsed: false,
                config: [
                    {
                        name: "sectionMemory_" + section.name,
                        displayName: "Selected Memory",
                        options: CMDCommon.getDeviceMemoryInfo().codeStartLocations,
                        default : CMDCommon.getDeviceMemoryInfo().codeStartLocations[0].name
                    }
                ],
                longDescription : section.description
            }
        )
    }
    else
    {
        addSectionToGroup(section)
    }
}

var config = [
    // {
    //     name: "configuration",
    //     displayName: "Configuration",
    //     options : [
    //         { name: "RAM", displayName: "RAM - fast debug configuration"},
    //         { name: "FLASH", displayName: "FLASH - retain after device reset"}
    //     ],
    //     default: "RAM",
    // },
    {
        name: "GROUP_DEFAULTS",
        displayName : "Default configuration",
        config     : [
            {
                name: "RAM_Default",
                displayName: "RAM default Configuration",
                description : '',
                buttonText: "Setup RAM default",
                onComplete: (inst, ui, result) => {
                    var memoryInfo = CMDCommon.getDeviceMemoryInfo()
                    if (Common.isContextCPU2() && memoryInfo.ramDefault_cpu2){
                        for(var i in memoryInfo.ramDefault_cpu2)
                        {
                            if (i!="codestart"){
                                inst["sectionMemory_"+i] = memoryInfo.ramDefault_cpu2[i]
                                inst["sectionAlignEnable_"+i] = false
                            } else {
                                inst["sectionMemory_"+i] = memoryInfo.ramDefault_cpu2[i]
                            }
                        }
                    }
                    else{
                        for(var i in memoryInfo.ramDefault)
                        {
                            if (i!="codestart"){
                                inst["sectionMemory_"+i] = memoryInfo.ramDefault[i]
                                inst["sectionAlignEnable_"+i] = false
                            } else {
                                inst["sectionMemory_"+i] = memoryInfo.ramDefault[i]
                            }
                        }
                    }
                    inst["sectionRun_ramfunc"] = []
                    inst["sectionRunFromDifferentAddr_ramfunc"] = false
                },
            },
            {
                name: "Flash_default", 
                displayName: "Flash default Configuration",
                description : '',
                buttonText: "Setup Flash default",
                onComplete: (inst, ui, result) => {
                    var memoryInfo = CMDCommon.getDeviceMemoryInfo()
                    if (Common.isContextCPU2() && memoryInfo.flashDefault_cpu2){
                        for(var i in memoryInfo.flashDefault_cpu2)
                        {
                            if(i!="ramfuncRun" && i!="codestart"){
                                inst["sectionMemory_"+i] = memoryInfo.flashDefault_cpu2[i]
                            }
                            else if (i=="codestart"){
                                inst["sectionMemory_"+i] = memoryInfo.flashDefault_cpu2[i]
                            }
                            else
                            {
                                ui["sectionRun_ramfunc"].hidden = false
                                ui["sectionBinit_ramfunc"].hidden = false
                                inst["sectionRun_ramfunc"] = memoryInfo.flashDefault_cpu2[i]
                                inst["sectionRunFromDifferentAddr_ramfunc"] = true
                                inst["sectionBinit_ramfunc"] = false
                            }
                            if(memoryInfo.flashDefault_cpu2[i][0].startsWith("FLASH")){
                                inst["sectionAlignEnable_"+i] = true
                                if (ui["sectionAlign_"+i].hidden){
                                ui["sectionAlign_"+i].hidden = false
                                }
                            }
                        }
                    }
                    else {
                        for(var i in memoryInfo.flashDefault)
                        {
                            if(i!="ramfuncRun" && i!="codestart")
                            {
                                inst["sectionMemory_"+i] = memoryInfo.flashDefault[i]
                            }
                            else if (i=="codestart"){
                                inst["sectionMemory_"+i] = memoryInfo.flashDefault[i]
                            } else{
                                ui["sectionRun_ramfunc"].hidden = false
                                ui["sectionBinit_ramfunc"].hidden = false
                                inst["sectionRun_ramfunc"] = memoryInfo.flashDefault[i]
                                inst["sectionRunFromDifferentAddr_ramfunc"] = true
                            }
                            if(memoryInfo.flashDefault[i][0].startsWith("FLASH"))
                            {
                                inst["sectionAlignEnable_"+i] = true
                                ui["sectionAlign_"+i].hidden = false
                            }
                        }
                    }
                },
            },

        ],
    },
    {
        name: "GROUP_AVAILABLE_MEMORY",
        displayName: "Available Memory Ranges",
        config : availableMemoryConfig,
        collapsed: false,
    },
    {
        displayName: "Memory",
        name: "GROUP_MEMORY",
        config: groupMemoryConfig,
        collapsed: false,
    },
    {
        displayName: "Section",
        name: "GROUP_SECTION",
        config: groupSectionConfig,
        collapsed: false,
    },
    {
        displayName: "CRC/Checksum Generation",
        name: "GROUP_CRC",
        config: [
            {
                name : "crcEnable",
                displayName : "Enable CRC/Checksum for entire flash",
                default : false,
                onChange: (inst, ui) => {
                    ui["crcType"].hidden = !inst["crcEnable"]
                }
            },
            {
                name : "crcType",
                displayName : "CRC/Checksum Algorithm",
                default : "C28_CHECKSUM_16",
                options : [
                    { name : "C28_CHECKSUM_16", displayName : "C28_CHECKSUM_16"},
                    { name : "CRC32_PRIME",     displayName : "CRC32_PRIME      (Poly = 0x04c11db7)"},
                    { name : "CRC16_802_15_4",  displayName : "CRC16_802_15_4   (Poly = 0x00001021)"},
                    { name : "CRC16_ALT",       displayName : "CRC16_ALT        (Poly = 0x00008005)"},
                    { name : "CRC8_PRIME",      displayName : "CRC8_PRIME       (Poly = 0x00000007)"},
                    { name : "CRC32_C",         displayName : "CRC32_C          (Poly = 0x1edc6f41)"},
                    { name : "CRC24_FLEXRAY",   displayName : "CRC24_FLEXRAY    (Poly = 0x005d6dcb)"}
                ],
                hidden : true
            },
        ],
        collapsed: false,
    }
];


var globalConfigs = [
    {
        name: "activateCMD",
        displayName: "Active a Linker CMD Configuration",
        default: false,
        onChange: (inst, ui) => {
            ui["activeCMD"].hidden = !inst["activateCMD"]
        }
    },
    {
        name: "activeCMD",
        displayName: "Current Active Linker CMD Configuration",
        hidden: true,
        default: "CMD0",
        options: (modStatic) => {
            var availableCMDs = []
            var mod = system.modules["/utilities/cmd_tool/cmd_syscfg/source/CMD"];
            for (var inst of mod.$instances)
            {
                availableCMDs.push({
                    name: inst.$name
                })
            }
            return availableCMDs
        }
    }
]

var moduleInstances = (inst) => {
    var mods = []
    for (var memGroup of CMDCommon.getDeviceCombinableMemoryRangeGroups()) {
        mods.push({
            name: memGroup + "memoryCombination",
            displayName: memGroup + " Memory Combination",
            moduleName: "/utilities/cmd_tool/cmd_syscfg/source/memoryCombination.js",
            group: "GROUP_MEMORY",
            requiredArgs : {
                group: memGroup
            },
            useArray: true,
            collapsed: true,
        })
    }

    mods.push({
        name: "userSection",
        displayName: "User Defined Sections",
        moduleName: "/utilities/cmd_tool/cmd_syscfg/source/userSection.js",
        group: "GROUP_SECTION",
        useArray: true,
        collapsed: true,
    })
    return mods
}



function onValidate(inst, validation) {

    for (var valIndex = 0; valIndex < cmdValidation.cmdValidation.length; valIndex++)
    {
        var valObject = cmdValidation.cmdValidation[valIndex];
        if (!valObject.devices.includes(system.deviceData.device))
        {
            continue;
        }
        valObject.func(inst, validation, valObject.name);
    }
}

// Define the common/portable base Watchdog
exports = {
    displayName         : "CMD",
    description         : "CMD",
    defaultInstanceName : "CMD",
    longDescription     : longDescription,
    //maxInstances        : 1,
    moduleInstances     : moduleInstances,
    moduleStatic        : {
        name: "cmdGlobal",
        displayName: "Linker Command Tool Global Settings",
        config: globalConfigs
    },
    modules: (inst) => {
        if (inst) {
            return [
                {
                    name: "pullInTemplateCMD",
                    moduleName: "/utilities/cmd_tool/cmd_syscfg/source/templates/device_cmd.cmd.dynamic.js",
                }
            ];  
        }
        return [];
    },
    templates: {
        "/utilities/cmd_tool/cmd_syscfg/source/templates/device_cmd.c.xdt": "",
        "/utilities/cmd_tool/cmd_syscfg/source/templates/device_cmd.h.xdt": "",
        "/utilities/cmd_tool/cmd_syscfg/source/templates/device_cmd.opt.xdt": "",
        "/utilities/cmd_tool/cmd_syscfg/source/templates/device_cmd.cmd.genlibs.xdt": ""
    },
    config              : config,
    validate            : onValidate
};
