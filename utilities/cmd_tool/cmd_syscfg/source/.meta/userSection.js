"use strict";
/*global exports, system*/
let meminfo   = system.getScript("/utilities/cmd_tool/cmd_syscfg/source/" + system.deviceData.device.toLowerCase() + "_memoryInfo.js");
let CMDCommon = system.getScript("/utilities/cmd_tool/cmd_syscfg/source/CMDCommon.js");


var memoryInfo = meminfo.memoryInfo;

var ownerOptions = [
    { name: "CPU_ONLY", displayName: "CPU is the owner of the section" },
]

var sections = CMDCommon.getDeviceMemorySections()
for (var section of sections)
{
    if (section.name.includes("cla"))
    {
        ownerOptions = [
            { name: "CPU_ONLY", displayName: "CPU is the owner of the section" },
            { name: "CPU_CLA1", displayName: "CPU and CLA1 share this section" },
        ]
        break;
    }
}

var config = [
    {
        name: "$name",
        hidden: false,
    },
    {
        name: "sectionName",
        displayName: "Section Name",
        default: "",
        longDescription: "If Section Name is not specified, all the sections specified in the library and obj is used."
    },
    {
        name: "libraryName",
        displayName: "Library Name",
        longDescription : "If Library name is specified, only the section present in the selected library is used. Can be left blank if not applicable",
        default: ""
    },
    {
        name: "objectName",
        displayName: "Obj Name",
        longDescription : "If Obj name is specified, only the section present in the selected .obj file is used. Can be left blank if not applicable",
        default: ""
    },
    {
        name: "sectionMemory",
        displayName: "Load Memory",
        default: [],
        options: (inst) => {
            var ownerInst = inst.$ownedBy;
            const currentOptions = CMDCommon.getMemoryRanges(ownerInst);
            return currentOptions;
        },
    },
    {
        name: "sectionRunFromDifferentAddr",
        displayName: "Run From Different Address",
        default: false,
        onChange: (inst, ui) => {
            ui["sectionRun"].hidden = !inst["sectionRunFromDifferentAddr"]
            ui["sectionBinit"].hidden = !inst["sectionRunFromDifferentAddr"]
        }
    },
    {
        name: "sectionRun",
        displayName: "Run From",
        default: [],
        hidden: true,
        options: (inst) => {
            const currentOptions = CMDCommon.getMemoryRanges(inst);
            return currentOptions;
        },
    },
    {
        name: "sectionBinit",
        displayName: "Place copy table in BINIT section",
        longDescription: " - If this option is enabled, the copy tables are placed in .binit (boot-time initialization) section. Target will automatically perform the copying at auto-initialization time. \n - If this option is disabled, the copy table is placed in .ovly section and application need to perform the copy. Sysconfig generates the function CMD_init which performs the copy for all copy tables other that boot time copy tables ",
        default: true,
        hidden: true,
    },
    {
        name: "sectionAlignEnable",
        displayName: "Enable Alignment",
        default: false,
        onChange: (inst, ui) => {
            ui["sectionAlign"].hidden = !inst["sectionAlignEnable"]
        }
    },
    {
        name: "sectionAlign",
        displayName: "Alignment in bytes (must be power of 2)",
        longDescription: "In C28x, byte is 16 bits. ALIGN(8) = aligned to 8 * 16-bit boundary",
        default: 8,
        hidden: true
    },
    {
        name: "sectionFillEnable",
        displayName: "Fill section with constant",
        default: false,
        onChange: (inst, ui) => {
            ui["sectionFill"].hidden = !inst["sectionFillEnable"]
        }
    },
    {
        name: "sectionFill",
        displayName: "Fill value",
        default: 0x0,
        hidden: true
    },
    {
        name: "sectionSymbols",
        displayName: "Add linker symbols",
        default: [],
        minSelections: 0,
        options: CMDCommon.LinkerSymbols
    },
    {
        name: "sectionType",
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
    {
        name: "sectionOwner",
        displayName: "Owner of the section",
        default: "CPU_ONLY",
        options: ownerOptions,
        hidden: true
    },

];



// Define the common/portable base Watchdog
exports = {
    displayName         : "User Defined Section",
    defaultInstanceName : "userSection",
    config              : config
};
