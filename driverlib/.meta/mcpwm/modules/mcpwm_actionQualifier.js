let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");
let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_mcpwm.js");

/* Array of configurables that are common across device families */
var UsedAQEventConfigs = [];
var UsedAQOutput_Configs = [];
var UsedAqOutput_aqEvent_Configs = [];

function onChangeUsedOutputs(inst, ui)
{
    for (var aqOutputIndex in device_driverlib_peripheral.MCPWM_ActionQualifierOutputModule)
    {
        var aqOutput = device_driverlib_peripheral.MCPWM_ActionQualifierOutputModule[aqOutputIndex];
        if (inst["mcpwmActionQualifier_" + aqOutput.name + "_shadowMode"])
        {
            ui["mcpwmActionQualifier_" + aqOutput.name + "_shadowEvent"].hidden = false;
        }
        else
        {
            ui["mcpwmActionQualifier_" + aqOutput.name + "_shadowEvent"].hidden = true;
            inst["mcpwmActionQualifier_" + aqOutput.name + "_shadowEvent"] = device_driverlib_peripheral.MCPWM_ActionQualifierLoadMode[0].name;
        }
        /*
        // Filter out the output events to only show the ones being used.
        for (var aqEventIndex in device_driverlib_peripheral.MCPWM_ActionQualifierOutputEvent)
        {
            var aqEvent = device_driverlib_peripheral.MCPWM_ActionQualifierOutputEvent[aqEventIndex];
            if  (inst["mcpwmActionQualifier_" + aqOutput.name + "_usedEvents"].includes(aqEvent.name))
            {
                ui["mcpwmActionQualifier_" + aqOutput.name + "_" + aqEvent.name.replace("MCPWM_AQ_OUTPUT_", "")].hidden = false;
            }
            else
            {
                ui["mcpwmActionQualifier_" + aqOutput.name + "_" + aqEvent.name.replace("MCPWM_AQ_OUTPUT_", "")].hidden = true;
            }
        }
        */
    }
}

var config = [
    
    // {
    //     name: "mcpwmActionQualifier_continousSwForceReloadModeGld",
    //     displayName : "Enable Continuous SW Force Global Load",
    //     description : 'Use global load configuration for AQCSFRC',
    //     hidden      : false,
    //     default     : false,
    // },
    // {
    //     name: "mcpwmActionQualifier_continousSwForceReloadMode",
    //     displayName : "Continuous SW Force Shadow Mode",
    //     description : '',
    //     hidden      : false,
    //     default     : device_driverlib_peripheral.MCPWM_ActionQualifierContForce[0].name,
    //     options     : device_driverlib_peripheral.MCPWM_ActionQualifierContForce,
    // },
    // {
    //     name: "mcpwmActionQualifier_t1Source",
    //     displayName : "T1 Trigger Source",
    //     description : '',
    //     hidden      : false,
    //     default     : device_driverlib_peripheral.MCPWM_ActionQualifierTriggerSource[0].name,
    //     options     : device_driverlib_peripheral.MCPWM_ActionQualifierTriggerSource,
    // },
    // {
    //     name: "mcpwmActionQualifier_t2Source", 
    //     displayName : "T2 Trigger Source",
    //     description : '',
    //     hidden      : false,
    //     default     : device_driverlib_peripheral.MCPWM_ActionQualifierTriggerSource[0].name,
    //     options     : device_driverlib_peripheral.MCPWM_ActionQualifierTriggerSource,
    // },
];

for (var aqOutputIndex in device_driverlib_peripheral.MCPWM_ActionQualifierOutputModule)
{
    var aqOutput = device_driverlib_peripheral.MCPWM_ActionQualifierOutputModule[aqOutputIndex];
    var aqOutputconfigs = []

    var aqOutput_Configs = [
        {
            name: "mcpwmActionQualifier_" + aqOutput.name + "_shadowMode",
            displayName : aqOutput.displayName.replace("output", "") + "Shadow Mode Enable",
            description : '',
            hidden      : false,
            default     : true,
            onChange    : onChangeUsedOutputs,
        },
        {
            name: "mcpwmActionQualifier_" + aqOutput.name + "_shadowEvent",
            displayName : aqOutput.displayName.replace("output", "") + "Shadow Load Event",
            description : '',
            hidden      : false,
            default     : device_driverlib_peripheral.MCPWM_ActionQualifierLoadMode[0].name,
            options     : device_driverlib_peripheral.MCPWM_ActionQualifierLoadMode,
        },
        {
            name : "mcpwmActionQualifier_"+ aqOutput.name +"_SWAForcection",
            displayName : "Software Force Action",
            options : device_driverlib_peripheral.MCPWM_ActionQualifierSWForceOutput,
            default : device_driverlib_peripheral.MCPWM_ActionQualifierSWForceOutput[0].name,
            
        }
    ]

    for (var aqEventIndex in device_driverlib_peripheral.MCPWM_ActionQualifierOutputEvent)
    {
        var aqEvent = device_driverlib_peripheral.MCPWM_ActionQualifierOutputEvent[aqEventIndex];
        var aqOutput_aqEvent_config = {
            name: "mcpwmActionQualifier_" + aqOutput.name + "_" + aqEvent.name.replace("MCPWM_AQ_OUTPUT_", ""),
            displayName : aqOutput.displayName.replace("output", "") + " " + aqEvent.displayName.replace("AQ OUTPUT ", ""),
            description : '',
            hidden      : false,
            default     : device_driverlib_peripheral.MCPWM_ActionQualifierOutput[0].name,
            options     : device_driverlib_peripheral.MCPWM_ActionQualifierOutput,
        };
        aqOutputconfigs.push(aqOutput_aqEvent_config);
    }

    aqOutput_Configs = aqOutput_Configs.concat([{
        name: "GROUP_AQ_" + aqOutput.name,
        displayName: aqOutput.displayName.replace("output", "") + "Event Output Configuration",
        description: "",
        longDescription: "",
        config: aqOutputconfigs
    }]);
    config = config.concat([{
            name:  "GROUP_AQ_Output_" + aqOutput.name,
            displayName: aqOutput.displayName.replace("output", "") + "Output Configuration",
            description: "",
            longDescription: "",
            config: aqOutput_Configs
    }]);

    UsedAQOutput_Configs.push(aqOutput_Configs);
}



var epwmAQSubmodule = {
    displayName: "MCPWM Action Qualifier",
    maxInstances: Common.peripheralCount("mcpwm"),
    defaultInstanceName: "MCPWM_AQ",
    description: "Enhanced Pulse Width Modulator Action Qualifier",
    config: config,
    templates: {
        boardc : "", //"/gpio/gpio.board.c.xdt",
        boardh : ""//"/gpio/gpio.board.h.xdt"
    },
};

exports = epwmAQSubmodule;