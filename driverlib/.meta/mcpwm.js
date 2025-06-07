let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_mcpwm.js");

// let device_driverlib_peripheral_funcs = 
//     system.getScript("/driverlib/device_driverlib_peripherals/functions/" + 
//         Common.getDeviceName().toLowerCase() + "/mcpwm.js");
// let driverlib_funcs = device_driverlib_peripheral_funcs["mcpwm" + "_driverlib"];
//console.log(system)

// console.log(driverlib_funcs)

let mcpwm_validation = 
    system.getScript("/driverlib/mcpwm/" + 
        "mcpwm_validation.js");

let sync_module = system.getScript("/driverlib/sync.js")

var pinmuxOnlyRelease = false;

var DO_NOT_COPY_configNames = [
    "mcpwmMemoryFileBrowse",
    "mcpwmLoadConfig", 
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
];

var boardCTemplate = "/driverlib/mcpwm/mcpwm.board.c.xdt";
var boardHTemplate = "/driverlib/mcpwm/mcpwm.board.h.xdt";

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
        if (DO_NOT_COPY_configNames.includes(configName) || (configName.deprecated))
        {
            continue;
        }
        inst_copy_to[configName] = inst_copy_from[configName];
    }
}

/* Array of CAN configurables that are common across device families */
let config = [
    // new to MCPWM. use Shadow registers for code gen
    {
        name : "mcpwm_useShdwRegForCodeGen",
        displayName : "Generated Code Uses Shadow Registers",
        description : "Generated Code Uses Shadow Registers for updating", 
        default     : true,
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
                description : 'The SysConfig name for the MCPWM to copy from',
                hidden      : true,
                default     : ""
            },
            {
                name: "copyPerform",
                displayName : "One-shot Copy",
                description : '',
                hidden      : true,
                buttonText: "Copy MCPWM Configuration",
                // onLaunch: (inst) => {
                //     return(
                //         {
                //         command: "../driverlib/.meta/mcpwm/mcpwmMemory.bat",
                //         args: [inst.mcpwmMemoryFileBrowse, "$comFile"],
                //         initialData: "",
                //     }
                //     );
                // },
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
        longDescription: "Generate template code for MCPWM configuration",
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
                description : 'The name of the code template generated for this MCPWM configuration',
                hidden      : false,
                default     : "mcpwmConfigurationTemplate"
            },
        ]
    },
];

function filterHardware(component)
{
    return (Common.typeMatches(component.type, ["MCPWM"]));
}


function modules(inst)
{
    if (inst) {
        return [
            // {
            //     name: "mcpwmPullInTemplateDot",
            //     moduleName: "/driverlib/mcpwm/templates/mcpwm.dot.dynamic.js",
            // }
        ];  
    }
    return [];
}

let submodulesComponents = [
    {
        moduleName: "/driverlib/mcpwm/modules/mcpwm_globalLoad.js",
        name: "mcpwmGlobalLoad",
        displayName:"MCPWM Global Load",
        description:"Global Loading",
    },
    {
        moduleName: "/driverlib/mcpwm/modules/mcpwm_timebase.js",
        name: "mcpwmTimebase",
        displayName:"MCPWM Time Base",
        description:"Time Base Submodule",
    },
    {
        moduleName: "/driverlib/mcpwm/modules/mcpwm_counterCompare.js",
        name: "mcpwmCounterCompare",
        displayName:"MCPWM Counter Compare",
        description:"Counter Compare Submodule",
    },
    {
        moduleName: "/driverlib/mcpwm/modules/mcpwm_actionQualifier.js",
        name: "mcpwmActionQualifier",
        displayName:"MCPWM Action Qualifier",
        description:"Action Qualifier Submodule",
    },
    {
        moduleName: "/driverlib/mcpwm/modules/mcpwm_deadband.js",
        name: "mcpwmDeadband",
        displayName:"MCPWM Dead-Band",
        description:"Dead-Band Submodule",
    },
    {
        moduleName: "/driverlib/mcpwm/modules/mcpwm_tripZone.js",
        name: "mcpwmTripZone",
        displayName:"MCPWM Trip Zone",
        description:"Trip Zone Submodule",
    },
    {
        moduleName: "/driverlib/mcpwm/modules/mcpwm_eventTrigger.js",
        name: "mcpwmEventTrigger",
        displayName:"MCPWM Event-Trigger",
        description:"Event-Trigger Submodule",
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
        options     : Pinmux.getPeripheralUseCaseNames("MCPWM"),
        onChange    : Pinmux.useCaseChanged,
    }
)

var moduleStatic = {
    name: "mcpwmGlobal",
    displayName: "MCPWM Global Settings",
    config: [
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
                validation.logError("The SYNC module needs to be added on CPU1 when an MCPWM instance is added on CPU2", 
                inst, "mcpwmTimebase_forceSyncPulse");
            }
        } 
    }else
	{
		if (Common.isContextCPU2())
        {
				validation.logWarning("The SYNC module needs to be added on CPU1 when an MCPWM instance is added on CPU2", 
                inst, "mcpwmTimebase_forceSyncPulse");
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
                "The copy from name is not a valid MCPWM name", 
                inst, "copyFrom");
        }
    }

    //
    // Copy Check End
    //

    var usedMCPWMTemplateNamesInsts = [];
    for (var instance_index in inst.$module.$instances)
    {
        var instance_obj = inst.$module.$instances[instance_index];
        if (instance_obj.generateCodeTemplate)
        {
            usedMCPWMTemplateNamesInsts.push(instance_obj.codeTemplateName);
        }
    }

    var duplicatesResult = Common.findDuplicates(usedMCPWMTemplateNamesInsts)

    if (duplicatesResult.duplicates.length != 0)
    {
        var allDuplicates = "";
        for (var duplicateNamesIndex in duplicatesResult.duplicates)
        {
            allDuplicates = allDuplicates + Common.stringOrEmpty(allDuplicates, ", ") 
                            + duplicatesResult.duplicates[duplicateNamesIndex];
        }
        validation.logError(
            "The MCPWM template name is already used. Duplicates: " + allDuplicates, 
            inst, "codeTemplateName");
    }

    for (var valIndex = 0; valIndex < mcpwm_validation.mcpwm_validation.length; valIndex++)
    {
        var valObject = mcpwm_validation.mcpwm_validation[valIndex];
        if (!valObject.devices.includes(Common.getDeviceName()))
        {
            continue;
        }
        if (valObject.type == mcpwm_validation.validation_info && !useInfos)
        {
            continue;
        }
        if (valObject.type == mcpwm_validation.validation_warning && !useWarnings)
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
    boardCTemplate = "/driverlib/mcpwm/mcpwm_empty.board.c.xdt";
    boardHTemplate = "/driverlib/mcpwm/mcpwm_empty.board.h.xdt";
    onValidate = undefined;
    moduleStatic = undefined;
}

var sharedModuleInstances = undefined;

var mcpwmModule = {
    peripheralName: "MCPWM",
    displayName: "MCPWM",
    maxInstances: Common.peripheralCount("MCPWM"),
    defaultInstanceName: "myMCPWM",
    description: "Multi Channel Pulse Width Modulator Peripheral",
    // longDescription: (Common.getCollateralFindabilityList("MCPWM")),
    filterHardware : filterHardware,
    config: config,
    templates: {
        boardc : boardCTemplate,
        boardh : boardHTemplate
    },
    modules: modules,
    moduleInstances : (inst) => {
        var regInterrupts = []
        
        var pinmuxQualMods = Pinmux.getGpioQualificationModInstDefinitions("MCPWM", inst)
        regInterrupts = regInterrupts.concat(pinmuxQualMods)

        if (inst.mcpwmEventTrigger_registerInterrupts)
        {
            regInterrupts.push({
                name: "mcpwmInt",      
                displayName: "MCPWM Interrupt ",
                moduleName: "/driverlib/interrupt.js",
                collapsed: true,
                args: {
                    $name : inst.$name + "_ET_INT",
                    int : "INT_" + inst.$name,
                    pinmuxPeripheralModule : "mcpwm",
                    driverlibInt: "INT_#"
                }
            })
        }
        
        return regInterrupts;
    },
	sharedModuleInstances: sharedModuleInstances,
    moduleStatic: moduleStatic,
    pinmuxRequirements    : Pinmux.mcpwmPinmuxRequirements,
    validate : onValidate,
    
};

if (mcpwmModule.maxInstances <= 0)
{
    delete mcpwmModule.pinmuxRequirements;
}
else
{
    Pinmux.addCustomPinmuxEnumToConfig(mcpwmModule)
    Pinmux.addPinMuxQualGroupToConfig(mcpwmModule)
}

exports = mcpwmModule;
