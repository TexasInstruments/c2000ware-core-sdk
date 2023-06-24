let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");
let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_epwm.js");
function onChangeEnableDisable(inst, ui)
{
    if (inst.epwmDiodeEmulation_enableDE)
    {
        ui.epwmDiodeEmulation_selExitMode.hidden = false;
        ui.epwmDiodeEmulation_TripLSelect.hidden = false;
        ui.epwmDiodeEmulation_TripHSelect.hidden = false;
        ui.epwmDiodeEmulation_enableDiodeEmulationModeCounter.hidden = false;
        ui.epwmDiodeEmulation_enablePWMTrip.hidden = false;
        if(inst.epwmDiodeEmulation_selExitMode === device_driverlib_peripheral.EPWM_DiodeEmulationMode[0].name)
        {
            ui.epwmDiodeEmulation_Reentrycnt.hidden = false;
        }else if(inst.epwmDiodeEmulation_selExitMode === device_driverlib_peripheral.EPWM_DiodeEmulationMode[1].name)
        {
            ui.epwmDiodeEmulation_Reentrycnt.hidden = true;
        }
        if(inst.epwmDiodeEmulation_enableDiodeEmulationModeCounter)
        {
            ui.epwmDiodeEmulation_stepIncr.hidden = false;
            ui.epwmDiodeEmulation_stepDecr.hidden = false;
            ui.epwmDiodeEmulation_stepThreshold.hidden = false;
        }else
        {
            ui.epwmDiodeEmulation_stepIncr.hidden = true;
            ui.epwmDiodeEmulation_stepDecr.hidden = true;
            ui.epwmDiodeEmulation_stepThreshold.hidden = true;
        }
        for (var dePwmChannel in device_driverlib_peripheral.EPWM_DE_CHANNEL)
        {
            var deOutput = device_driverlib_peripheral.EPWM_DE_CHANNEL[dePwmChannel];
            ui["epwmDiodeEmulation_" + deOutput.name + "_selTrip"].hidden = false;  
            ui["epwmDiodeEmulation_" + deOutput.name + "_configOutput"].hidden = false;

        }

    }
    else
    {
        ui.epwmDiodeEmulation_selExitMode.hidden = true;
        ui.epwmDiodeEmulation_TripLSelect.hidden = true;
        ui.epwmDiodeEmulation_TripHSelect.hidden = true;
        ui.epwmDiodeEmulation_enableDiodeEmulationModeCounter.hidden = true;
        ui.epwmDiodeEmulation_stepIncr.hidden = true;
        ui.epwmDiodeEmulation_stepDecr.hidden = true;
        ui.epwmDiodeEmulation_stepThreshold.hidden = true;
        ui.epwmDiodeEmulation_Reentrycnt.hidden = true;
        ui.epwmDiodeEmulation_enablePWMTrip.hidden = true;

        inst.epwmDiodeEmulation_selExitMode = "EPWM_DIODE_EMULATION_CBC";
        inst.epwmDiodeEmulation_TripLSelect = "EPWM_DE_TRIP_SRC_INPUTXBAR_OUT1";
        inst.epwmDiodeEmulation_TripHSelect = "EPWM_DE_TRIP_SRC_INPUTXBAR_OUT1";
        inst.epwmDiodeEmulation_enableDiodeEmulationModeCounter = false;
        inst.epwmDiodeEmulation_stepIncr = 0;
        inst.epwmDiodeEmulation_stepDecr = 0;
        inst.epwmDiodeEmulation_stepThreshold = 0;
        inst.epwmDiodeEmulation_Reentrycnt = 0;
        inst.epwmDiodeEmulation_enablePWMTrip = false;
        for (var dePwmChannel in device_driverlib_peripheral.EPWM_DE_CHANNEL)
        {
            var deOutput = device_driverlib_peripheral.EPWM_DE_CHANNEL[dePwmChannel];
            ui["epwmDiodeEmulation_" + deOutput.name + "_selTrip"].hidden = true;  
            ui["epwmDiodeEmulation_" + deOutput.name + "_configOutput"].hidden = true;
            inst["epwmDiodeEmulation_" + deOutput.name + "_selTrip"] = "EPWM_DE_SRC_TRIPL";  
            inst["epwmDiodeEmulation_" + deOutput.name + "_configOutput"] = "EPWM_DE_SYNC_TRIPHorL";
        }
    }
}

// make sure to add conditionals to not have the same trip signal for triph / tripl ?
var config = [
    {
        name        : "epwmDiodeEmulation_enableDE",
        displayName : "Enable Diode Emulation Mode",
        description : 'Enables Diode Emulation Mode, by default Diode Emulation is cleared',
        hidden      : false,
        default     : false,
        onChange    : onChangeEnableDisable
    },
    {
        name: "epwmDiodeEmulation_enablePWMTrip",
        displayName : "Enable PWM Trip Output",
        description : 'If enabled, PWM Trip will not bypass diode emulation logic',
        hidden      : true,
        default     : false,
    },
    {
        name: "epwmDiodeEmulation_selExitMode",
        displayName : "Diode Emulation Mode Select",
        description : 'The event for which the diode emulation mode exits',
        hidden      : true,
        default     : device_driverlib_peripheral.EPWM_DiodeEmulationMode[0].name,
        options     : device_driverlib_peripheral.EPWM_DiodeEmulationMode,
        onChange    : onChangeEnableDisable

    },
    {
        name: "epwmDiodeEmulation_Reentrycnt",
        displayName : "Reentry Delay",
        description : 'Delay value until diode emulation can exit in terms of PWMSYNCOUT (0-255)',
        hidden      : true,
        default     : 0,
    },
    {
        name: "epwmDiodeEmulation_TripLSelect", 
        displayName : "Input TripL Select",
        description : 'Input trip low select from Xbar or CMPSS',
        hidden      : true,
        default     : device_driverlib_peripheral.EPWM_DiodeEmulationTripSource[0].name,
        options     : device_driverlib_peripheral.EPWM_DiodeEmulationTripSource
    },
    {
        name: "epwmDiodeEmulation_TripHSelect",
        displayName : "Input TripH Select",
        description : 'Input trip high select from Xbar or CMPSS',
        hidden      : true,
        default     : device_driverlib_peripheral.EPWM_DiodeEmulationTripSource[0].name,
        options     : device_driverlib_peripheral.EPWM_DiodeEmulationTripSource
    },
    {
        name:  "GROUP_DEMON",
        displayName: "Diode Emulation Monitor Configuration",
        description: "",
        longDescription: "",
        config: [
            {
                name: "epwmDiodeEmulation_enableDiodeEmulationModeCounter",
                displayName : "Enable Monitor Counter",
                description : 'Enabling this ',
                hidden      : true,
                default     : false,
                onChange    : onChangeEnableDisable

            },
            {
                name: "epwmDiodeEmulation_stepIncr",
                displayName : "Increment Stepsize of Counter when TripH or TripL Occurs",
                description : 'Increments count by defined step size when TripH or TripL occurs(256 is max step size)',
                hidden      : true,
                default     : 0
            },
            {
                name: "epwmDiodeEmulation_stepDecr",
                displayName : "Decrement Stepsize of Counter when TripH or TripL Occurs",
                description : 'Decrements count by defined step size when TripH or TripL occurs(256 is max step size)',
                hidden      : true,
                default     : 0
            },
            {
                name: "epwmDiodeEmulation_stepThreshold",
                displayName : "Threshold for Number of TripH or TripL Signal Occurrences",
                description : 'When threshold is reached, a trip pulse is generated and counter is cleared',
                hidden      : true,
                default     : 0
            },
        ]
    }
];

for (var dePwmChannel in device_driverlib_peripheral.EPWM_DE_CHANNEL)
{
    var deOutput = device_driverlib_peripheral.EPWM_DE_CHANNEL[dePwmChannel];
    var deOutputconfigs = []
    var deOutput_Configs = [
        {
            name: "epwmDiodeEmulation_" + deOutput.name + "_selTrip",
            displayName : deOutput.displayName.replace("emulation", "Emulation").replace("channel", "Channel") + " Trip Select",
            description : 'Trip select for diode emulation output',
            hidden      : true,
            default     : device_driverlib_peripheral.EPWM_DE_SRC[0].name,
            options     : device_driverlib_peripheral.EPWM_DE_SRC,
        },
        {
            name: "epwmDiodeEmulation_" + deOutput.name + "_configOutput",
            displayName : deOutput.displayName.replace("emulation", "Emulation").replace("channel", "Channel") + " Output Select",
            description : 'Set diode emulation output channel A to tripHortripL, inverted tripHortripL, constant low or high',
            hidden      : true,
            default     : device_driverlib_peripheral.EPWM_DiodeEmulationSignal[0].name,
            options     : device_driverlib_peripheral.EPWM_DiodeEmulationSignal,
        }

        
    ]

    config = config.concat([{
            name:  "GROUP_DE_Output_" + deOutput.name,
            displayName: deOutput.displayName.replace("emulation", "Emulation").replace("channel", "Channel") + " Output Configuration",
            description: "",
            longDescription: "",
            config: deOutput_Configs
    }]);

}

var epwmDiodeEmulationSubmodule = {
    displayName: "EPWM Diode Emulation",
    maxInstances: Common.peripheralCount("EPWM"),
    defaultInstanceName: "EPWM_DE",
    description: "Enhanced Pulse Width Modulator Diode Emulation Configuration",
    config: config,
    templates: {
        boardc : "", //"/gpio/gpio.board.c.xdt",
        boardh : ""//"/gpio/gpio.board.h.xdt"
    },
};


exports = epwmDiodeEmulationSubmodule;