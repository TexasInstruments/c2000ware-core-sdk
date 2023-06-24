let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");
let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_epwm.js");

/* Array of configurables that are common across device families */
var UsedAQEventConfigs = [];
var UsedAQOutput_Configs = [];
var UsedAqOutput_aqEvent_Configs = [];

function onChangeUsedOutputs(inst, ui)
{
    for (var aqOutputIndex in device_driverlib_peripheral.EPWM_ActionQualifierOutputModule)
    {
        var aqOutput = device_driverlib_peripheral.EPWM_ActionQualifierOutputModule[aqOutputIndex];
        if (inst["epwmActionQualifier_" + aqOutput.name + "_shadowMode"])
        {
            ui["epwmActionQualifier_" + aqOutput.name + "_shadowEvent"].hidden = false;
        }
        else
        {
            ui["epwmActionQualifier_" + aqOutput.name + "_shadowEvent"].hidden = true;
            inst["epwmActionQualifier_" + aqOutput.name + "_shadowEvent"] = device_driverlib_peripheral.EPWM_ActionQualifierLoadMode[0].name;
        }
        /*
        // Filter out the output events to only show the ones being used.
        for (var aqEventIndex in device_driverlib_peripheral.EPWM_ActionQualifierOutputEvent)
        {
            var aqEvent = device_driverlib_peripheral.EPWM_ActionQualifierOutputEvent[aqEventIndex];
            if  (inst["epwmActionQualifier_" + aqOutput.name + "_usedEvents"].includes(aqEvent.name))
            {
                ui["epwmActionQualifier_" + aqOutput.name + "_" + aqEvent.name.replace("EPWM_AQ_OUTPUT_", "")].hidden = false;
            }
            else
            {
                ui["epwmActionQualifier_" + aqOutput.name + "_" + aqEvent.name.replace("EPWM_AQ_OUTPUT_", "")].hidden = true;
            }
        }
        */
    }
}

var config = [
    {
        name: "epwmActionQualifier_continousSwForceReloadModeGld",
        displayName : "Enable Continuous SW Force Global Load",
        description : 'Use global load configuration for AQCSFRC',
        hidden      : false,
        default     : false,
    },
    {
        name: "epwmActionQualifier_continousSwForceReloadMode",
        displayName : "Continuous SW Force Shadow Mode",
        description : '',
        hidden      : false,
        default     : device_driverlib_peripheral.EPWM_ActionQualifierContForce[0].name,
        options     : device_driverlib_peripheral.EPWM_ActionQualifierContForce,
    },
    {
        name: "epwmActionQualifier_t1Source",
        displayName : "T1 Trigger Source",
        description : '',
        hidden      : false,
        default     : device_driverlib_peripheral.EPWM_ActionQualifierTriggerSource[0].name,
        options     : device_driverlib_peripheral.EPWM_ActionQualifierTriggerSource,
    },
    {
        name: "epwmActionQualifier_t2Source", 
        displayName : "T2 Trigger Source",
        description : '',
        hidden      : false,
        default     : device_driverlib_peripheral.EPWM_ActionQualifierTriggerSource[0].name,
        options     : device_driverlib_peripheral.EPWM_ActionQualifierTriggerSource,
    },
];

for (var aqOutputIndex in device_driverlib_peripheral.EPWM_ActionQualifierOutputModule)
{
    var aqOutput = device_driverlib_peripheral.EPWM_ActionQualifierOutputModule[aqOutputIndex];
    var aqOutputconfigs = []

    var aqOutput_Configs = [
        {
            name: "epwmActionQualifier_" + aqOutput.name + "_gld",
            displayName : aqOutput.displayName.replace("output", "") + "Global Load Enable",
            description : 'Use global load configuration for ' + aqOutput.displayName.replace("output", ""),
            hidden      : false,
            default     : false,
        },
        {
            name: "epwmActionQualifier_" + aqOutput.name + "_shadowMode",
            displayName : aqOutput.displayName.replace("output", "") + "Shadow Mode Enable",
            description : '',
            hidden      : false,
            default     : false,
            onChange    : onChangeUsedOutputs,
        },
        {
            name: "epwmActionQualifier_" + aqOutput.name + "_shadowEvent",
            displayName : aqOutput.displayName.replace("output", "") + "Shadow Load Event",
            description : '',
            hidden      : true,
            default     : device_driverlib_peripheral.EPWM_ActionQualifierLoadMode[0].name,
            options     : device_driverlib_peripheral.EPWM_ActionQualifierLoadMode,
        },
        {
            name: "epwmActionQualifier_" + aqOutput.name + "_t1Source",
            displayName : aqOutput.displayName.replace("output", "") + "T1 Trigger Source",
            description : '',
            hidden      : true,
            default     : device_driverlib_peripheral.EPWM_ActionQualifierTriggerSource[0].name,
            options     : device_driverlib_peripheral.EPWM_ActionQualifierTriggerSource,
            deprecated  : true,
        },
        {
            name: "epwmActionQualifier_" + aqOutput.name + "_t2Source",
            displayName : aqOutput.displayName.replace("output", "") + "T2 Trigger Source",
            description : '',
            hidden      : true,
            default     : device_driverlib_peripheral.EPWM_ActionQualifierTriggerSource[0].name,
            options     : device_driverlib_peripheral.EPWM_ActionQualifierTriggerSource,
            deprecated  : true,
        },
        {
            name: "epwmActionQualifier_" + aqOutput.name + "_onetimeSwForceAction",
            displayName : aqOutput.displayName.replace("output", "") + "One-Time SW Force Action",
            description : '',
            hidden      : false,
            default     : device_driverlib_peripheral.EPWM_ActionQualifierOutput[0].name,
            options     : device_driverlib_peripheral.EPWM_ActionQualifierOutput,
        },
        {
            name: "epwmActionQualifier_" + aqOutput.name + "_continuousSwForceAction",
            displayName : aqOutput.displayName.replace("output", "") + "Continuous SW Force Action",
            description : '',
            hidden      : false,
            default     : device_driverlib_peripheral.EPWM_ActionQualifierSWOutput[0].name,
            options     : device_driverlib_peripheral.EPWM_ActionQualifierSWOutput,
        },
        {
            name: "epwmActionQualifier_" + aqOutput.name + "_usedEvents",
            displayName : "Events to Configure for " + 
                        aqOutput.displayName,
            description : '',
            hidden      : false,
            default     : [],
            minSelections: 0,
            options     : device_driverlib_peripheral.EPWM_ActionQualifierOutputEvent,
            onChange    : onChangeUsedOutputs,
            deprecated  : true,
        }
    ]

    for (var aqEventIndex in device_driverlib_peripheral.EPWM_ActionQualifierOutputEvent)
    {
        var aqEvent = device_driverlib_peripheral.EPWM_ActionQualifierOutputEvent[aqEventIndex];
        var aqOutput_aqEvent_config = {
            name: "epwmActionQualifier_" + aqOutput.name + "_" + aqEvent.name.replace("EPWM_AQ_OUTPUT_", ""),
            displayName : aqOutput.displayName.replace("output", "") + " " + aqEvent.displayName.replace("AQ OUTPUT ", ""),
            description : '',
            hidden      : false,
            default     : device_driverlib_peripheral.EPWM_ActionQualifierOutput[0].name,
            options     : device_driverlib_peripheral.EPWM_ActionQualifierOutput,
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
    displayName: "EPWM Action Qualifier",
    maxInstances: Common.peripheralCount("EPWM"),
    defaultInstanceName: "EPWM_AQ",
    description: "Enhanced Pulse Width Modulator Action Qualifier",
    config: config,
    templates: {
        boardc : "", //"/gpio/gpio.board.c.xdt",
        boardh : ""//"/gpio/gpio.board.h.xdt"
    },
};

exports = epwmAQSubmodule;