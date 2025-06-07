let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");
let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_mcpwm.js");

function onChangeDeadbandMode(inst, ui, mode)
{
    if (mode == "AH")
    {
        inst.mcpwmDeadband_inputRED = "MCPWM_DB_INPUT_MCPWMA";
        inst.mcpwmDeadband_inputFED = "MCPWM_DB_INPUT_MCPWMA";

        inst.mcpwmDeadband_polarityRED = "MCPWM_DB_POLARITY_ACTIVE_HIGH";
        inst.mcpwmDeadband_polarityFED = "MCPWM_DB_POLARITY_ACTIVE_HIGH";

        inst.mcpwmDeadband_enableRED = true;
        inst.mcpwmDeadband_enableFED = true;

        inst.mcpwmDeadband_outputSwapOutA = false;
        inst.mcpwmDeadband_outputSwapOutB = false;
    }
    else if (mode == "AL")
    {        
        inst.mcpwmDeadband_inputRED = "MCPWM_DB_INPUT_MCPWMA";
        inst.mcpwmDeadband_inputFED = "MCPWM_DB_INPUT_MCPWMA";

        inst.mcpwmDeadband_polarityRED = "MCPWM_DB_POLARITY_ACTIVE_LOW";
        inst.mcpwmDeadband_polarityFED = "MCPWM_DB_POLARITY_ACTIVE_LOW";

        inst.mcpwmDeadband_enableRED = true;
        inst.mcpwmDeadband_enableFED = true;

        inst.mcpwmDeadband_outputSwapOutA = false;
        inst.mcpwmDeadband_outputSwapOutB = false;

    }
    else if (mode == "AHC")
    {
        inst.mcpwmDeadband_inputRED = "MCPWM_DB_INPUT_MCPWMA";
        inst.mcpwmDeadband_inputFED = "MCPWM_DB_INPUT_MCPWMA";

        inst.mcpwmDeadband_polarityRED = "MCPWM_DB_POLARITY_ACTIVE_HIGH";
        inst.mcpwmDeadband_polarityFED = "MCPWM_DB_POLARITY_ACTIVE_LOW";

        inst.mcpwmDeadband_enableRED = true;
        inst.mcpwmDeadband_enableFED = true;

        inst.mcpwmDeadband_outputSwapOutA = false;
        inst.mcpwmDeadband_outputSwapOutB = false;
    }
    else if (mode == "ALC")
    {
        inst.mcpwmDeadband_inputRED = "MCPWM_DB_INPUT_MCPWMA";
        inst.mcpwmDeadband_inputFED = "MCPWM_DB_INPUT_MCPWMA";

        inst.mcpwmDeadband_polarityRED = "MCPWM_DB_POLARITY_ACTIVE_LOW";
        inst.mcpwmDeadband_polarityFED = "MCPWM_DB_POLARITY_ACTIVE_HIGH";

        inst.mcpwmDeadband_enableRED = true;
        inst.mcpwmDeadband_enableFED = true;

        inst.mcpwmDeadband_outputSwapOutA = false;
        inst.mcpwmDeadband_outputSwapOutB = false;
    }
    else if (mode == "DUAL")
    {
        inst.mcpwmDeadband_inputRED = "MCPWM_DB_INPUT_MCPWMB";
        inst.mcpwmDeadband_inputFED = "MCPWM_DB_INPUT_DB_RED";

        inst.mcpwmDeadband_polarityRED = "MCPWM_DB_POLARITY_ACTIVE_HIGH";
        inst.mcpwmDeadband_polarityFED = "MCPWM_DB_POLARITY_ACTIVE_HIGH";

        inst.mcpwmDeadband_enableRED = false;
        inst.mcpwmDeadband_enableFED = true;

        inst.mcpwmDeadband_outputSwapOutA = false;
        inst.mcpwmDeadband_outputSwapOutB = false;
    }
}

function onChangeEnableDelays(inst, ui)
{
    // if (inst.mcpwmDeadband_enableRED == true)
    // {
    //    ui.mcpwmDeadband_delayRED.hidden = false;
    // }
    // else if (inst.mcpwmDeadband_enableRED == false)
    // {
    //    ui.mcpwmDeadband_delayRED.hidden = true;
    //    inst.mcpwmDeadband_delayRED = 0;// Set to default
    // }
    // if (inst.mcpwmDeadband_enableFED == true)
    // {
    //    ui.mcpwmDeadband_delayFED.hidden = false;
    // }
    // else if (inst.mcpwmDeadband_enableFED == false)
    // {
    //    ui.mcpwmDeadband_delayFED.hidden = true;
    //    inst.mcpwmDeadband_delayFED = 0; // Set to default
    // }
}

function onChangeShadowModes(inst, ui)
{
    if (!inst["mcpwmDeadband_redShadowMode"])
    {
        ui["mcpwmDeadband_redShadowLoadEvent"].hidden = true;
        inst.mcpwmDeadband_redShadowLoadEvent = device_driverlib_peripheral.MCPWM_RisingEdgeDelayLoadMode[0].name
    }
    else
    {
        ui["mcpwmDeadband_redShadowLoadEvent"].hidden = false;
    }
    if (!inst["mcpwmDeadband_fedShadowMode"])
    {
        ui["mcpwmDeadband_fedShadowLoadEvent"].hidden = true;
        inst.mcpwmDeadband_fedShadowLoadEvent = device_driverlib_peripheral.MCPWM_FallingEdgeDelayLoadMode[0].name
    }
    else
    {
         ui["mcpwmDeadband_fedShadowLoadEvent"].hidden = false;
    }
}

/* Array of configurables that are common across device families */
var config = [
    {
        name: "GROUP_DEADBAND_MODE",
        displayName : "Common Dead-Band Modes",
        description : 'Mode for the Dead-Band Submodule',
        config     : [
            {
                name: "AH", 
                displayName: "Active High",
                description : '',
                buttonText: "Setup the Dead-Band Module",
                onComplete: (inst, ui, result) => {
                    onChangeDeadbandMode(inst, ui, "AH")
                },
            },
            {
                name: "AL", 
                displayName: "Active Low",
                description : '',
                buttonText: "Setup the Dead-Band Module",
                onComplete: (inst, ui, result) => {
                    onChangeDeadbandMode(inst, ui, "AL")
                },
            },
            {
                name: "AHC", 
                displayName: "Active High Complementary",
                description : '',
                buttonText: "Setup the Dead-Band Module",
                onComplete: (inst, ui, result) => {
                    onChangeDeadbandMode(inst, ui, "AHC")
                },
            },
            {
                name: "ALC", 
                displayName: "Active Low Complementary",
                description : '',
                buttonText: "Setup the Dead-Band Module",
                onComplete: (inst, ui, result) => {
                    onChangeDeadbandMode(inst, ui, "ALC")
                },
            },
            {
                name: "DUAL", 
                displayName: "Dual Edge Delay Mode",
                description : '',
                buttonText: "Setup the Dead-Band Module",
                onComplete: (inst, ui, result) => {
                    onChangeDeadbandMode(inst, ui, "DUAL")
                },
            },
        ],
    },
    {
        name: "mcpwmDeadband_inputRED",
        displayName : "Rising Edge Delay Input",
        description : 'Select the source for DBRED (Rising Edge Delay)',
        hidden      : false,
        default     : device_driverlib_peripheral.MCPWM_DB_INPUT[0].name,
        options     : device_driverlib_peripheral.MCPWM_DB_INPUT.slice(0,2) 
    },
    {
        name: "mcpwmDeadband_inputFED",
        displayName : "Falling Edge Delay Input",
        description : 'Select the source for DBFED (Falling Edge Delay)',
        hidden      : false,
        default     : device_driverlib_peripheral.MCPWM_DB_INPUT[0].name,
        options     : device_driverlib_peripheral.MCPWM_DB_INPUT
    },

    {
        name: "mcpwmDeadband_polarityRED",
        displayName : "Rising Edge Delay Polarity",
        description : 'Whether or not to invert RED (Rising Edge Delay)',
        hidden      : false,
        default     : device_driverlib_peripheral.MCPWM_DeadBandPolarity[0].name,
        options     : device_driverlib_peripheral.MCPWM_DeadBandPolarity
    },

    {
        name: "mcpwmDeadband_polarityFED",
        displayName : "Falling Edge Delay Polarity",
        description : 'Whether or not to invert FED (Falling Edge Delay)',
        hidden      : false,
        default     : device_driverlib_peripheral.MCPWM_DeadBandPolarity[0].name,
        options     : device_driverlib_peripheral.MCPWM_DeadBandPolarity
    },

    {
        name: "mcpwmDeadband_enableRED",
        displayName : "Enable Rising Edge Delay",
        description : 'Enable DBRED (Rising Edge Delay) by choosing it as the source for the A path',
        hidden      : false,
        default     : false,
        onChange    : onChangeEnableDelays
    },
    {
        name: "mcpwmDeadband_redShadowLoadEvent",
        displayName : "RED Shadow Load Event",
        description : 'Shadow to active load event for the RED (Rising Edge Delay) register.',
        hidden      : true,
        default     : device_driverlib_peripheral.MCPWM_RisingEdgeDelayLoadMode[0].name,
        options     : device_driverlib_peripheral.MCPWM_RisingEdgeDelayLoadMode
    },
    {
        name: "mcpwmDeadband_redShadowMode",
        displayName : "Enable RED Shadow Mode",
        description : 'Enable shadowing of the RED (Rising Edge Delay) register.',
        hidden      : false,
        default     : true,
        onChange    : onChangeShadowModes,
    },

    {
        name: "mcpwmDeadband_delayRED",
        displayName : "Rising Edge Delay Value",
        description : 'DBRED (Rising Edge Delay) delay value',
        hidden      : false,
        default     : 0,
    },
    {
        name: "mcpwmDeadband_enableFED",
        displayName : "Enable Falling Edge Delay",
        description : 'Enable DBFED (Falling Edge Delay) by choosing it as the source for the B path',
        hidden      : false,
        default     : false,
        onChange    : onChangeEnableDelays
    },    
    {
        name: "mcpwmDeadband_fedShadowLoadEvent",
        displayName : "FED Shadow Load Event",
        description : 'Shadow to active load event for the FED (Falling Edge Delay) register.',
        hidden      : true,
        default     : device_driverlib_peripheral.MCPWM_FallingEdgeDelayLoadMode[0].name,
        options     : device_driverlib_peripheral.MCPWM_FallingEdgeDelayLoadMode
    },
    {
        name: "mcpwmDeadband_fedShadowMode",
        displayName : "Enable FED Shadow Mode",
        description : 'Enable shadowing of the FED (Falling Edge Delay) register.',
        hidden      : false,
        default     : true,
        onChange    : onChangeShadowModes,
    },

    {
        name: "mcpwmDeadband_delayFED",
        displayName : "Falling Edge Delay Value",
        description : 'DBFED (Falling Edge Delay) delay value',
        hidden      : false,
        default     : 0,
    },

    {
        name: "mcpwmDeadband_outputSwapOutA",
        displayName : "Swap Output for MCPWMxA",
        description : 'Check to enable output swap. Channel A path to Out B.',
        hidden      : false,
        default     : false,
    },
    {
        name: "mcpwmDeadband_outputSwapOutB",
        displayName : "Swap Output for MCPWMxB",
        description : 'Check to enable output swap. Channel B path to Out A.',
        hidden      : false,
        default     : false,
    },
    // {
    //     name: "mcpwmDeadband_dbControlGld",
    //     displayName : "Enable Deadband Control Global Load",
    //     description : 'Use global load configuration for deadband control',
    //     hidden      : false,
    //     default     : false,
    // },
    // {
    //     name: "mcpwmDeadband_controlShadowLoadEvent",
    //     displayName : "Deadband Control Shadow Load Event",
    //     description : 'Shadow to active load event for the DBCTL (Deadband Control) register.',
    //     hidden      : false,
    //     default     : device_driverlib_peripheral.MCPWM_DeadBandControlLoadMode[0].name,
    //     options     : device_driverlib_peripheral.MCPWM_DeadBandControlLoadMode
    // },
    // {
    //     name: "mcpwmDeadband_controlShadowMode",
    //     displayName : "Enable Deadband Control Shadow Mode",
    //     description : 'Enable shadowing of the DBCTL (Deadband Control) register.',
    //     hidden      : true,
    //     default     : false,
    //     //onChange    : onChangeShadowModes,
    // },
    // {
    //     name: "mcpwmDeadband_redGld",
    //     displayName : "Enable RED Global Load",
    //     description : 'Use global load configuration for RED',
    //     hidden      : false,
    //     default     : false,
    // },
    // {
    //     name: "mcpwmDeadband_fedGld",
    //     displayName : "Enable FED Global Load",
    //     description : 'Use global load configuration for FED',
    //     hidden      : false,
    //     default     : false,
    // },
    // {
    //     name: "mcpwmDeadband_deadbandCounterClockRate",
    //     displayName : "Dead Band Counter Clock Rate",
    //     description : 'Dead band counter clock rate.',
    //     hidden      : false,
    //     default     : device_driverlib_peripheral.MCPWM_DeadBandClockMode[0].name,
    //     options     : device_driverlib_peripheral.MCPWM_DeadBandClockMode,
    //     readOnly    : true,
    // },

];

if(["F28E12x"].includes(Common.getDeviceName()))
{
    // config = config.concat(
    //     {
    //         name: "mcpwmDeadband_deadbandFallingEdgeDelayLink",
    //         displayName : "Dead Band Rising Edge Delay Link",
    //         description : 'Simultaneous write to the current MCPWM module DBRED register',
    //         hidden      : false,
    //         default     : device_driverlib_peripheral.MCPWM_CurrentLink[0].name,
    //         options     : device_driverlib_peripheral.MCPWM_CurrentLink
    //     },
    //     {
    //         name: "mcpwmDeadband_deadbandRisingEdgeDelayLink",
    //         displayName : "Dead Band Falling Edge Delay Link",
    //         description : 'Simultaneous write to the current MCPWM module DBFED register',
    //         hidden      : false,
    //         default     : device_driverlib_peripheral.MCPWM_CurrentLink[0].name,
    //         options     : device_driverlib_peripheral.MCPWM_CurrentLink
    //     }
    //     )
}

var MCPWMDeadbandSubmodule = {
    displayName: "MCPWM Dead-Band",
    maxInstances: Common.peripheralCount("mcpwm"),
    defaultInstanceName: "MCPWM_DB",
    description: "Enhanced Pulse Width Modulator Dead-Band",
    config: config,
    templates: {
        boardc : "", //"/gpio/gpio.board.c.xdt",
        boardh : ""//"/gpio/gpio.board.h.xdt"
    },
};


exports = MCPWMDeadbandSubmodule;
