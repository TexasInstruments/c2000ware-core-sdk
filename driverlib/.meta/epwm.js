let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_epwm.js");

let device_driverlib_peripheral_funcs = 
    system.getScript("/driverlib/device_driverlib_peripherals/functions/" + 
        Common.getDeviceName().toLowerCase() + "/epwm.js");
let driverlib_funcs = device_driverlib_peripheral_funcs["epwm" + "_driverlib"];
//console.log(system)

// console.log(driverlib_funcs)

let epwm_validation = 
    system.getScript("/driverlib/epwm/" + 
        "epwm_validation.js");

let sync_module = system.getScript("/driverlib/sync.js")

var pinmuxOnlyRelease = false;

var DO_NOT_COPY_configNames = [
    "epwmMemoryFileBrowse",
    "epwmLoadConfig", 
    "copyUse",
    "copyFrom",
    "copyPerform",
    "generateCodeTemplate",
    "codeTemplateName",
    "AH",
    "AL",
    "AHC",
    "ALC",
    "DUAL",
    "hrpwm_tbclk",
    "hrpwm_mepSteps",
    "hrpwm_coarseSteps",
    "hrpwm_periodCoarseSteps",
    "hrpwm_calculatedCMPX",
    "hrpwm_calculatedCMPXHR",
    "hrpwm_calculatedTBPRD",
    "hrpwm_calculatedTBPRDHR",
    "hrpwm_calculatedRED",
    "hrpwm_calculatedREDHR",
    "hrpwm_calculatedFED",
    "hrpwm_calculatedFEDHR",
    "epwmActionQualifier_" + "EPWM_AQ_OUTPUT_A" + "_usedEvents", //DEPRECATED
    "epwmActionQualifier_" + "EPWM_AQ_OUTPUT_A" + "_t1Source", //DEPRECATED
    "epwmActionQualifier_" + "EPWM_AQ_OUTPUT_A" + "_t2Source", //DEPRECATED
    "epwmActionQualifier_" + "EPWM_AQ_OUTPUT_B" + "_usedEvents", //DEPRECATED
    "epwmActionQualifier_" + "EPWM_AQ_OUTPUT_B" + "_t1Source", //DEPRECATED
    "epwmActionQualifier_" + "EPWM_AQ_OUTPUT_B" + "_t2Source", //DEPRECATED
];

var mindb_icl_xbar_map = {
 "EPWM_MINDB_SEL_OUTXBAR_OUT1" : "XBAR_INPUT1",
 "EPWM_MINDB_SEL_OUTXBAR_OUT2" : "XBAR_INPUT2",
 "EPWM_MINDB_SEL_OUTXBAR_OUT3" : "XBAR_INPUT3",
 "EPWM_MINDB_SEL_OUTXBAR_OUT4" : "XBAR_INPUT4",
 "EPWM_MINDB_SEL_OUTXBAR_OUT5" : "XBAR_INPUT5",
 "EPWM_MINDB_SEL_OUTXBAR_OUT6" : "XBAR_INPUT6",
 "EPWM_MINDB_SEL_OUTXBAR_OUT7" : "XBAR_INPUT7",
 "EPWM_MINDB_SEL_OUTXBAR_OUT8" : "XBAR_INPUT8",
 "EPWM_MINDB_SEL_OUTXBAR_OUT9" : "XBAR_INPUT9",
 "EPWM_MINDB_SEL_OUTXBAR_OUT10" : "XBAR_INPUT10",
 "EPWM_MINDB_SEL_OUTXBAR_OUT11" : "XBAR_INPUT11",
 "EPWM_MINDB_SEL_OUTXBAR_OUT12" : "XBAR_INPUT12",
 "EPWM_MINDB_SEL_OUTXBAR_OUT13" : "XBAR_INPUT13",
 "EPWM_MINDB_SEL_OUTXBAR_OUT14" : "XBAR_INPUT14",
 "EPWM_MINDB_SEL_OUTXBAR_OUT15" : "XBAR_INPUT15",
 "EPWM_MINDB_ICL_XBAR_OUT1" : "XBAR_INPUT1",
 "EPWM_MINDB_ICL_XBAR_OUT2" : "XBAR_INPUT2",
 "EPWM_MINDB_ICL_XBAR_OUT3" : "XBAR_INPUT3",
 "EPWM_MINDB_ICL_XBAR_OUT4" : "XBAR_INPUT4",
 "EPWM_MINDB_ICL_XBAR_OUT5" : "XBAR_INPUT5",
 "EPWM_MINDB_ICL_XBAR_OUT6" : "XBAR_INPUT6",
 "EPWM_MINDB_ICL_XBAR_OUT7" : "XBAR_INPUT7",
 "EPWM_MINDB_ICL_XBAR_OUT8" : "XBAR_INPUT8",
 "EPWM_MINDB_ICL_XBAR_OUT9" : "XBAR_INPUT9",
 "EPWM_MINDB_ICL_XBAR_OUT10" : "XBAR_INPUT10",
 "EPWM_MINDB_ICL_XBAR_OUT11" : "XBAR_INPUT11",
 "EPWM_MINDB_ICL_XBAR_OUT12" : "XBAR_INPUT12",
 "EPWM_MINDB_ICL_XBAR_OUT13" : "XBAR_INPUT13",
 "EPWM_MINDB_ICL_XBAR_OUT14" : "XBAR_INPUT14",
 "EPWM_MINDB_ICL_XBAR_OUT15" : "XBAR_INPUT15",
 "EPWM_MINDB_ICL_XBAR_OUT16" : "XBAR_INPUT16"
};

device_driverlib_peripheral.EPWM_CurrentLink.unshift(
    { name: "EPWM_LINK_WITH_DISABLE", displayName: "Disable Linking" }
);

//console.log(system.getCurrentScriptPath())

var boardCTemplate = "/driverlib/epwm/epwm.board.c.xdt";
var boardHTemplate = "/driverlib/epwm/epwm.board.h.xdt";

/* Intro splash on GUI */
let longDescription = "";

function CommentOutCode (inst, ui)
{
    if (inst.enableAllCode == true)
    {
        ui.commentOutDefaultCode.hidden = false;
    }
    else 
    {
        inst.commentOutDefaultCode = false;
        ui.commentOutDefaultCode.hidden = true;
    }
}

function performCopy(inst, ui)
{
    for (var instance_index in inst.$module.$instances)
    {
        var instance_obj = inst.$module.$instances[instance_index];
        if (instance_obj != inst) {
            //console.log(instance_obj)
            if (instance_obj.$name == inst.copyFrom)
            {
                copyAllSettings(inst, instance_obj);
            }
        }
    }
}

function getConfigNameRecursive(arrayConfigs)
{
    var configNames = [];
    for (var modConfig of arrayConfigs)
    {        
        if (modConfig.config)
        {
            configNames = configNames.concat(getConfigNameRecursive(modConfig.config))
        }
        else
        {
            var modConfigName = modConfig.name;
            configNames.push(modConfigName);
        }
    }
    return configNames;
}

function copyAllSettings(inst_copy_to, inst_copy_from)
{
    var configNames = getConfigNameRecursive(inst_copy_from.$module.config);
    for (var configOptionIndex = 0; configOptionIndex<configNames.length; configOptionIndex++)
    {
        var configName = configNames[configOptionIndex];
        if (DO_NOT_COPY_configNames.includes(configName))
        {
            continue;
        }
        //console.log(configName);
        //console.log(inst_copy_from[configName]);
        inst_copy_to[configName] = inst_copy_from[configName];
    }
}

var longDescriptionMemoryLoad = `
**Note: Currently, this tool is unable to map any of the Link settings for the EPWM. As such, they must be input MANUALLY.**

This tool functions by taking the register memory you're inputting (.dat) and setting the associated settings in Sysconfig for you.
To ensure that your .dat file is correctly exported, please follow these steps (information shown is for EPWM1 but works for all EPWMs):
*   1) Load your codebase onto your MCU in debug mode

![an offline image](${Common.getC2000WareRelativePath()}/driverlib/.meta/memory_mapping/docs/stage_1_mm_debug_view.png "Memory File Export")

*   2) Run until your peripheral setup is complete and the sync clock is enabled

![an offline image](${Common.getC2000WareRelativePath()}/driverlib/.meta/memory_mapping/docs/stage_2_mm_debug_view.png "Memory File Export")

*   3) Save the register memory (using 'Memory Browser' or via 'Tools') for your peripheral in 16-bit TI Style format.

![an offline image](${Common.getC2000WareRelativePath()}/driverlib/.meta/memory_mapping/docs/stage_4_mm_debug_view.png "Save Memory View")

![an offline image](${Common.getC2000WareRelativePath()}/driverlib/.meta/memory_mapping/docs/stage_3_mm_debug_view.png "Memory File Export")

*   4) Once these steps have been completed and your .dat file has been generated, load your .dat via 'EPWM Memory File'

*   5) Determine if you want to overwrite all existing settings with those within the memory file OR if you only want 'non-default' settings to be imported via 'Overwrite All Values From Memory File'

*   6) Click the 'Load Configuration' button and all of your settings for this EPWM will be imported and set

`

/* Array of CAN configurables that are common across device families */
let config = [
    /*{
        name : "regenerateConfigs",
        default: false,
        onChange : (inst, ui) =>
        {
            console.log(inst.$module.$configByName)
        }
    },
    */
    {
        name: "GROUP_LOAD_FROM_MEMORY",
        displayName: "Load EPWM Settings From Device Memory Export",
        longDescription: longDescriptionMemoryLoad,
        config: [
            {
                name: "epwmMemoryFileBrowse",
                displayName: "EPWM Memory File",
                default: "",
                hidden: false,
                fileFilter: ".dat",
            },
            {
                name: "epwmLoadAllValues",
                displayName: "Overwrite All Values From Memory File",
                longDescription: "Loads in all values from memory, overwriting current settings.",
                default: false,
                hidden: false,
            },
            {
                name: "epwmLoadConfig",
                displayName: "Load Configuration",
                buttonText: "Load the memory configuration",
                longDescription: "Load the configuration from the selected .dat file into Sysconfig.",
                hidden: false,
                onLaunch: (inst) => {
                    //console.log(inst.epwmMemoryFileBrowse)
                    return ({
                        command: Common.getC2000WareRelativePath() + "/driverlib/.meta/epwm/epwmMemory.bat",
                        args: [inst.epwmMemoryFileBrowse, "$comFile"],
                        initialData: ""
                    });
                },
                onComplete: (inst, ui, result) => {
                    // console.log(inst);
                    // console.log("inside onComplete");
                    let deviceName = Common.getDeviceName();
                    //NEED TO SET IP_NAME FOR EACH IP
                    let IP_NAME = 'epwm';
                    // console.log(deviceName);
                    let memoryData = result['data'].toString().split('\n');
                    const conversionFunctions = require("./mapping_input");
                    let sysOptions = conversionFunctions.callParser(memoryData, 0, deviceName, IP_NAME, inst.epwmLoadAllValues);
                    //algorithm run
                    // console.log(sysOptions);
                    for(let mapVals of sysOptions){
                        if((/^[0-9]+$/).test(mapVals["value"])){
                            mapVals["value"] = parseInt(mapVals["value"]);
                        }
                        try{
                            inst[mapVals["name"]] = mapVals["value"];
                        }
                        catch (e) {
                            // console.log(e);
                            if(typeof(mapVals["value"]) == "number"){
                                mapVals["value"] = mapVals["value"].toString();
                            }
                            else if(typeof(mapVals["value"]) == "string"){
                                let holder = [];
                                holder.push(mapVals["value"]);
                                mapVals["value"] = Object.assign([], holder);
                            }
                            try{
                                inst[mapVals["name"]] = mapVals["value"];
                            }
                            catch(err){
                                if(typeof(mapVals["value"]) == "object"){
                                    mapVals["value"] = mapVals["value"][0];
                                }
                            }
                        }
                        // if(ui[mapVals["name"]]["hidden"] == true){
                        //     ui[mapVals["name"]]["hidden"] = false;
                        // }
                        if(inst.$module.$configByName[mapVals["name"]].default  != mapVals["value"] && "onChange" in inst.$module.$configByName[mapVals["name"]]){
                            inst.$module.$configByName[mapVals["name"]].onChange(inst, ui);
                        }
                    }
                },
            },
        ]
    },    
    {
        name: "GROUP_COPY",
        displayName: "Copy Settings",
        description: "",
        longDescription: "",
        config: [
            {
                name: "copyUse",
                displayName : "Use Copy Feature",
                description : '',
                hidden      : false,
                default     : false,
                onChange    : (inst, ui) => {                    
                    ui.copyFrom.hidden = !inst.copyUse;
                    ui.copyPerform.hidden = !inst.copyUse;
                }
            },
            {
                name: "copyFrom",
                displayName : "Copy From",
                description : 'The SysConfig name for the EPWM to copy from',
                hidden      : true,
                default     : ""
            },
            {
                name: "copyPerform",
                displayName : "One-shot Copy",
                description : '',
                hidden      : true,
                buttonText: "Copy EPWM Configuration",
                onLaunch: (inst) => {
                    return ({
                        command: "../driverlib/.meta/epwm/epwmMemory.bat",
                        args: [inst.epwmMemoryFileBrowse, "$comFile"],
                        initialData: "",
                    });
                },
                onComplete: (inst, ui, result) => {
                    performCopy(inst, ui)
                },
            },
        ]
    },
    {
        name: "GROUP_TEMPLATECODE",
        displayName: "Template Code Generation",
        description: "",
        longDescription: "Generate template code for EPWM configuration",
        config: [
            {
                name: "generateCodeTemplate",
                displayName : "Generate Code Template",
                description : 'Enable the template code generation',
                hidden      : false,
                default     : false
            },
            {
                name: "codeTemplateName",
                displayName : "Code Template Name",
                description : 'The name of the code template generated for this EPWM configuration',
                hidden      : false,
                default     : "ePWMConfigurationTemplate"
            },
        ]
    },
];

if (["F28004x", "F28002x", "F2838x", "F28003x", "F280013x", "F280015x"].includes(Common.getDeviceName())){

    config.splice.apply(config, [config.length - 1, 0].concat([      
            {
                name: "epwmLock",
                displayName : "EPWM Lock Register",
                description : 'Lock EPWM registers',
                hidden      : false,
                minSelections: 0,
                default     : [],
                options     : device_driverlib_peripheral.EPWM_LockRegisterGroup
            },
        ]));
}


function filterHardware(component)
{
    return (Common.typeMatches(component.type, ["EPWM"]));
}


function modules(inst)
{
    if (inst) {
        return [
            {
                name: "epwmPullInTemplateDot",
                moduleName: "/driverlib/epwm/templates/epwm.dot.dynamic.js",
            }
        ];  
    }
    return [];
}

let submodulesComponents = [
    {
        moduleName: "/driverlib/epwm/modules/epwm_globalLoad.js",
        name: "epwmGlobalLoad",
        displayName:"EPWM Global Load",
        description:"Global Loading",
    },
    {
        moduleName: "/driverlib/epwm/modules/epwm_timebase.js",
        name: "epwmTimebase",
        displayName:"EPWM Time Base",
        description:"Time Base Submodule",
    },
    {
        moduleName: "/driverlib/epwm/modules/epwm_counterCompare.js",
        name: "epwmCounterCompare",
        displayName:"EPWM Counter Compare",
        description:"Counter Compare Submodule",
    },
    {
        moduleName: "/driverlib/epwm/modules/epwm_actionQualifier.js",
        name: "epwmActionQualifier",
        displayName:"EPWM Action Qualifier",
        description:"Action Qualifier Submodule",
    },
    {
        moduleName: "/driverlib/epwm/modules/epwm_deadband.js",
        name: "epwmDeadband",
        displayName:"EPWM Dead-Band",
        description:"Dead-Band Submodule",
    },
    {
        moduleName: "/driverlib/epwm/modules/epwm_chopper.js",
        name: "epwmChopper",
        displayName:"EPWM Chopper",
        description:"Chopper Submodule",
    },
    {
        moduleName: "/driverlib/epwm/modules/epwm_tripZone.js",
        name: "epwmTripZone",
        displayName:"EPWM Trip Zone",
        description:"Trip Zone Submodule",
    },
    {
        moduleName: "/driverlib/epwm/modules/epwm_digitalCompare.js",
        name: "epwmDigitalCompare",
        displayName:"EPWM Digital Compare",
        description:"Digital Compare Submodule",
    },
    {
        moduleName: "/driverlib/epwm/modules/epwm_eventTrigger.js",
        name: "epwmEventTrigger",
        displayName:"EPWM Event-Trigger",
        description:"Event-Trigger Submodule",
    },
    {
        moduleName: "/driverlib/epwm/modules/hrpwm_extension.js",
        name: "hrpwm",
        displayName:"HRPWM",
        description:"High Resolution Pulse Width Modulation",
    },
];

const insert = (arr, index, newItem) => [
// part of the array before the specified index
...arr.slice(0, index),
// inserted item
newItem,
// part of the array after the specified index
...arr.slice(index)
]

if (["F28P65x"].includes(Common.getDeviceName()))
{
    submodulesComponents = insert(submodulesComponents, 3, 
        {
            moduleName: "/driverlib/epwm/modules/epwm_xcmpmode.js",
            name: "epwmXCMP",
            displayName:"EPWM XCMP Mode",
            description:"XCMP Submodule",
        });
    submodulesComponents = insert(submodulesComponents, 8 , 
        {
            moduleName: "/driverlib/epwm/modules/epwm_diodeEmulation.js",
            name: "epwmDiodeEmulation",
            displayName:"EPWM Diode Emulation",
            description:"Diode Emulation Submodule",
        });
    submodulesComponents = insert(submodulesComponents, 10 , 
        {
            moduleName: "/driverlib/epwm/modules/epwm_minDBILC.js",
            name: "epwmMinDBILC",
            displayName:"EPWM Minimum Dead Band and Illegal Combo Logic",
            description:"Minimum Dead Band and Illegal Combo Logic Submodule",
        });
}
for (var submoduleComponent of submodulesComponents)
{
    var submodule = system.getScript(submoduleComponent.moduleName)
    config = config.concat([
        {
            name: "GROUP_" + submodule.defaultInstanceName,
            displayName: submodule.displayName,
            longDescription: submodule.description,
            description: "",
            config: submodule.config
        },
    ])
}

config.push(
    {
        name: "useCase",
        displayName : "PinMux Use Case",
        description : 'Peripheral use case',
        hidden      : false,
        default     : 'ALL',
        options     : Pinmux.getPeripheralUseCaseNames("EPWM"),
        onChange    : Pinmux.useCaseChanged,
    }
)

var moduleStatic = {
    name: "epwmGlobal",
    displayName: "EPWM Global Settings",
    config: [
        // {
        //     name: "printModuleInfo",
        //     displayName : "Print Module Info",
        //     description : '',
        //     hidden      : false,
        //     buttonText: "Print",
        //     onLaunch: (inst) => {
        //         return ({
        //             command: "../driverlib/.meta/epwm/epwmMemory.bat",
        //             args: [inst.epwmMemoryFileBrowse, "$comFile"],
        //             initialData: "",
        //         });
        //     },
        //     onComplete: (inst, ui, result) => {
        //         Common.printConfigsInfo(system.modules['/driverlib/epwm.js'].$configByName) 
        //     },
        // },
        {
            name:"enableInfo",
            displayName: "Enable Info Mode",
            default : true
        },
        {
            name:"enableWarning",
            displayName: "Enable Warnings",
            default : true
        },
        {
            name:"enableAllCode",
            displayName: "Enable All Code Generation",
            description: "Enable All Code Generation",
            default : false
        },
        {
            name:"commentOutDefaultCode",
            displayName: "Comment Out the Default Settings Code",
            description: "Comment Out the Default Settings Code",
            default : false
        },
        {
            name:"generateInitFunctions",
            displayName: "Generate Init Function for Each Instance",
            description: "Generate Init Function for Each Instance",
            default : false
        },
    ],

    modules: Common.autoForce("sync", "/driverlib/sync.js")
}   

function onValidate(inst, validation)
{
    // Check if the sync module is added on CPU1 if the current context is CPU2
    if (Common.isMultiCoreDevice() && Common.isMultiCoreSysConfig())
    {
        if (Common.isContextCPU2())
        {
            if (Common.isModuleOnOtherContext("/driverlib/sync.js") == false)
            {
                validation.logError("The SYNC module needs to be added on CPU1 when an EPWM instance is added on CPU2", 
                inst, "epwmTimebase_forceSyncPulse");
            }
        } 
    }else
	{
		if (Common.isContextCPU2())
        {
				validation.logWarning("The SYNC module needs to be added on CPU1 when an EPWM instance is added on CPU2", 
                inst, "epwmTimebase_forceSyncPulse");
		}
	}

    //
    // Static Variables
    //

    var useInfos = inst.$module.$static["enableInfo"]
    var useWarnings = inst.$module.$static["enableWarning"]

    //
    // End of static variables
    //


    //
    // Copy Check Start
    //
    var validCopyName = false;
    if (inst.copyUse)
    {
        for (var instance_index in inst.$module.$instances)
        {
            var instance_obj = inst.$module.$instances[instance_index];
            if (instance_obj != inst) {
                if (instance_obj.$name == inst.copyFrom)
                {
                    validCopyName = true;
                }
            }
        }

        if (!validCopyName)
        {
            validation.logError(
                "The copy from name is not a valid EPWM name", 
                inst, "copyFrom");
        }
    }

    //
    // Copy Check End
    //

    var usedEPWMTemplateNamesInsts = [];
    for (var instance_index in inst.$module.$instances)
    {
        var instance_obj = inst.$module.$instances[instance_index];
        if (instance_obj.generateCodeTemplate)
        {
            usedEPWMTemplateNamesInsts.push(instance_obj.codeTemplateName);
        }
    }

    var duplicatesResult = Common.findDuplicates(usedEPWMTemplateNamesInsts)

    if (duplicatesResult.duplicates.length != 0)
    {
        var allDuplicates = "";
        for (var duplicateNamesIndex in duplicatesResult.duplicates)
        {
            allDuplicates = allDuplicates + Common.stringOrEmpty(allDuplicates, ", ") 
                            + duplicatesResult.duplicates[duplicateNamesIndex];
        }
        validation.logError(
            "The EPWM template name is already used. Duplicates: " + allDuplicates, 
            inst, "codeTemplateName");
    }

    for (var valIndex = 0; valIndex < epwm_validation.epwm_validation.length; valIndex++)
    {
        var valObject = epwm_validation.epwm_validation[valIndex];
        if (!valObject.devices.includes(Common.getDeviceName()))
        {
            continue;
        }
        if (valObject.type == epwm_validation.validation_info && !useInfos)
        {
            continue;
        }
        if (valObject.type == epwm_validation.validation_warning && !useWarnings)
        {
            continue;
        }
        valObject.func(inst, validation, valObject.name);
    }

}


if (Common.onlyPinmux())
{
    config = [config[config.length - 1]];
    moduleInstances = undefined
}

if (pinmuxOnlyRelease)
{
    config = [config[config.length - 1]];
    modules = undefined;
    boardCTemplate = "/driverlib/epwm/epwm_empty.board.c.xdt";
    boardHTemplate = "/driverlib/epwm/epwm_empty.board.h.xdt";
    onValidate = undefined;
    moduleStatic = undefined;
}

var sharedModuleInstances = undefined;

sharedModuleInstances = function (inst) {
	let mindb_icl_xbar = [];
	if (Common.isContextCPU2()){
		return [];
	}
    if (inst.epwmMinDeadBand_A_inputRefSignal != "EPWM_MINDB_SEL_DEPWM" && inst.epwmMinDeadBand_EnableA)
    {
        mindb_icl_xbar = mindb_icl_xbar.concat(
            [
                {
                    name: "MINDB_XBAR_A",      
                    displayName: "MINDB X-BAR Configuration",
                    moduleName: "/driverlib/mindbxbar.js",
                    collapsed: true,
					group: "GROUP_MINDB_Output_A",
					requiredArgs: {
						mindbxbarInstance : mindb_icl_xbar_map[inst.epwmMinDeadBand_A_inputRefSignal]
					}
                },
            ]
        );
    }
    if (inst.epwmMinDeadBand_B_inputRefSignal != "EPWM_MINDB_SEL_DEPWM" && inst.epwmMinDeadBand_EnableB)
    {
        mindb_icl_xbar = mindb_icl_xbar.concat(
            [
                {
                    name: "MINDB_XBAR_B",      
                    displayName: "MINDB X-BAR Configuration",
                    moduleName: "/driverlib/mindbxbar.js",
                    collapsed: true,
					group: "GROUP_MINDB_Output_B",
					requiredArgs: {
						mindbxbarInstance : mindb_icl_xbar_map[inst.epwmMinDeadBand_B_inputRefSignal]
					}
                },
            ]
        );
    }
	if (inst.epwmICL_EnableA)
	{
		mindb_icl_xbar = mindb_icl_xbar.concat(
            [
                {
                    name: "ICL_XBAR_A",      
                    displayName: "ICL X-BAR Configuration",
                    moduleName: "/driverlib/iclxbar.js",
                    collapsed: true,
					group: "GROUP_ICL_A",
					requiredArgs: {
						iclxbarInstance : mindb_icl_xbar_map[inst.epwmICL_A_selXBAR]
					}
                },
            ]
        );
	}
	if (inst.epwmICL_EnableB)
	{
		mindb_icl_xbar = mindb_icl_xbar.concat(
            [
                {
                    name: "ICL_XBAR_B",      
                    displayName: "ICL X-BAR Configuration",
                    moduleName: "/driverlib/iclxbar.js",
                    collapsed: true,
					group: "GROUP_ICL_B",
					requiredArgs: {
						iclxbarInstance : mindb_icl_xbar_map[inst.epwmICL_B_selXBAR]
					}
                },
            ]
        );
	}
    return mindb_icl_xbar;
}

var epwmModule = {
    peripheralName: "EPWM",
    displayName: "EPWM",
    maxInstances: Common.peripheralCount("EPWM"),
    defaultInstanceName: "myEPWM",
    description: "Enhanced Pulse Width Modulator Peripheral",
    longDescription: (Common.getCollateralFindabilityList("EPWM")),
    filterHardware : filterHardware,
    config: config,
    templates: {
        boardc : boardCTemplate,
        boardh : boardHTemplate
    },
    modules: modules,
    moduleInstances : (inst) => {
        var regInterrupts = []
        
        var pinmuxQualMods = Pinmux.getGpioQualificationModInstDefinitions("EPWM", inst)
        regInterrupts = regInterrupts.concat(pinmuxQualMods)

        if (inst.epwmEventTrigger_registerInterrupts)
        {
            regInterrupts.push({
                name: "epwmInt",      
                displayName: "EPWM Interrupt ",
                moduleName: "/driverlib/interrupt.js",
                collapsed: true,
                args: {
                    $name : inst.$name + "_ET_INT",
                    int : "INT_" + inst.$name,
                    pinmuxPeripheralModule : "epwm",
                    driverlibInt: "INT_#"
                }
            })
        }
        if (inst.epwmTripZone_registerInterrupts)
        {
            regInterrupts.push({
                name: "epwmTZInt",      
                displayName: "EPWM TZ Interrupt ",
                moduleName: "/driverlib/interrupt.js",
                collapsed: true,
                args: {
                    $name : inst.$name + "_TZ_INT",
                    int : "INT_" + inst.$name + "_TZ",
                    pinmuxPeripheralModule : "epwm",
                    driverlibInt: "INT_#_TZ"
                }
            })
        }
        return regInterrupts;
    },
	sharedModuleInstances: sharedModuleInstances,
    moduleStatic: moduleStatic,
    pinmuxRequirements    : Pinmux.epwmPinmuxRequirements,
    validate : onValidate,
    migrateLegacyConfiguration : (inst) =>
    {
        //
        // Migrating old method for T1 and T2
        //
        var AQLocation = 0;
        for (let i=0; i< inst.$module.config.length; i++)
        {
            if (inst.$module.config[i].name == "GROUP_EPWM_AQ")
            {
                AQLocation = i; 
            }
        }

        var A_t1Value = "";
        var A_t2Value = "";
        var B_t1Value = "";
        var B_t2Value = "";

        // Get the old values for T1 and T2

        for (let x=0; x< inst.$module.config[AQLocation].config.length; x++)
        {
            if (inst.$module.config[AQLocation].config[x].name == "GROUP_AQ_Output_EPWM_AQ_OUTPUT_A") // Check T1 and T2 for A Output
            {
               for (let y=0; y< inst.$module.config[AQLocation].config[x].config.length; y++)
               {
                  if (inst.$module.config[AQLocation].config[x].config[y].name == "epwmActionQualifier_EPWM_AQ_OUTPUT_A_t1Source")
                  {
                    A_t1Value = inst[inst.$module.config[AQLocation].config[x].config[y].name]
                  }
                  if (inst.$module.config[AQLocation].config[x].config[y].name == "epwmActionQualifier_EPWM_AQ_OUTPUT_A_t2Source")
                  {
                    A_t2Value = inst[inst.$module.config[AQLocation].config[x].config[y].name]
                  }
               }
            }
            if (inst.$module.config[AQLocation].config[x].name == "GROUP_AQ_Output_EPWM_AQ_OUTPUT_B") // Check T1 and T2 for B Output
            {
               for (let z=0; z< inst.$module.config[AQLocation].config[x].config.length; z++)
               {
                  if (inst.$module.config[AQLocation].config[x].config[z].name == "epwmActionQualifier_EPWM_AQ_OUTPUT_B_t1Source")
                  {
                    B_t1Value = inst[inst.$module.config[AQLocation].config[x].config[z].name]
                  }
                  if (inst.$module.config[AQLocation].config[x].config[z].name == "epwmActionQualifier_EPWM_AQ_OUTPUT_B_t2Source")
                  {
                    B_t2Value = inst[inst.$module.config[AQLocation].config[x].config[z].name]
                  }
               }
            }
        }

        // Setup the new T1 value
        if (A_t1Value != device_driverlib_peripheral.EPWM_ActionQualifierTriggerSource[0].name && B_t1Value == device_driverlib_peripheral.EPWM_ActionQualifierTriggerSource[0].name)
        {
            inst.epwmActionQualifier_t1Source = A_t1Value
        }
        else if (A_t1Value == device_driverlib_peripheral.EPWM_ActionQualifierTriggerSource[0].name && B_t1Value != device_driverlib_peripheral.EPWM_ActionQualifierTriggerSource[0].name)
        {
            inst.epwmActionQualifier_t1Source = B_t1Value
        }
        else if (A_t1Value == device_driverlib_peripheral.EPWM_ActionQualifierTriggerSource[0].name && B_t1Value == device_driverlib_peripheral.EPWM_ActionQualifierTriggerSource[0].name)
        {
            inst.epwmActionQualifier_t1Source = device_driverlib_peripheral.EPWM_ActionQualifierTriggerSource[0].name
        }
        else
        {
            inst.epwmActionQualifier_t1Source = B_t1Value
        }

        // Setup the new T2 value
        if (A_t2Value != device_driverlib_peripheral.EPWM_ActionQualifierTriggerSource[0].name && B_t2Value == device_driverlib_peripheral.EPWM_ActionQualifierTriggerSource[0].name)
        {
            inst.epwmActionQualifier_t2Source = A_t2Value
        }
        else if (A_t2Value == device_driverlib_peripheral.EPWM_ActionQualifierTriggerSource[0].name && B_t2Value != device_driverlib_peripheral.EPWM_ActionQualifierTriggerSource[0].name)
        {
            inst.epwmActionQualifier_t2Source = B_t2Value
        }
        else if (A_t2Value == device_driverlib_peripheral.EPWM_ActionQualifierTriggerSource[0].name && B_t2Value == device_driverlib_peripheral.EPWM_ActionQualifierTriggerSource[0].name)
        {
            inst.epwmActionQualifier_t2Source = device_driverlib_peripheral.EPWM_ActionQualifierTriggerSource[0].name
        }
        else
        {
            inst.epwmActionQualifier_t2Source = B_t2Value
        }  

        //
        // Update Digital Compare Combo Logic
        //
        /*
        for (var dcCompareTypeIndex in device_driverlib_peripheral.EPWM_DigitalCompareType)
        {
            var dcCompareType = device_driverlib_peripheral.EPWM_DigitalCompareType[dcCompareTypeIndex];
            var dcTypeName = "epwmDigitalCompare_" + dcCompareType.name
            var dcTypeNameCombo = "epwmDigitalCompare_" + dcCompareType.name + "_combinationInputConfig"
            if (inst.dcTypeNameCombo != [])
            {
                inst.dcTypeName = "EPWM_DC_TRIP_COMBINATION"
            }
        }
        */
    }
};

if (epwmModule.maxInstances <= 0)
{
    delete epwmModule.pinmuxRequirements;
}
else
{
    Pinmux.addCustomPinmuxEnumToConfig(epwmModule)
    Pinmux.addPinMuxQualGroupToConfig(epwmModule)
}

exports = epwmModule;
