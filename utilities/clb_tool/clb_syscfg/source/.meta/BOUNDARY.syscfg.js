"use strict";
/*global exports, system*/

let Common   = system.getScript("/utilities/clb_tool/clb_syscfg/source/Common.js");
let customWaveform   = system.getScript("/utilities/clb_tool/clb_syscfg/source/CustomWaveform.js");
let logError = Common.logError;

/* Intro splash on GUI */
let longDescription = "Provide simulation input functions for the 8 inputs to a CLB Tile";

let longDescriptionCustomSource = `
Note: 'N' can be a hex number (in the format: 0xN) or an integer (in the format: N)

Instruction | Description
--- | ---
**#define** | Pattern replacer; used to define macros
**high(N)** | Sets waveform high for 'N' CLB cycles
**low(N)**  | Sets waveform low for 'N' CLB cycles
**rpt(N)**  | Starts a repeat block; code encapsulated by **rpt_end** will be repeated a total of 'N' times
**rpt_end** | Denotes the end of a repeat block
`

function inputCfg(idx) {
    let config = 
    [
        {
            name    : 'in' + idx,
            default : 'None',
            displayName : '(Legacy) Boundary Input ' + idx,
            deprecated : true,

            onChange: function(inst,ui) {
                ui['input_pipeline'+idx].hidden   = (Common.isType0_Type1() || (inst['in'+idx] == 'None') || (inst['in'+idx] == '0') || (inst['in'+idx] == '1'));
                ui['in_sync_2_cycle_delay_'+idx].hidden   = ((inst['in'+idx] != 'squareWave') && (inst['in'+idx] != 'customWave'));
                ui['in_sync'+idx].hidden   = ((inst['in'+idx] != 'squareWave') && (inst['in'+idx] != 'customWave'));
                ui['in_edge'+idx].hidden   = (inst['in'+idx] != 'squareWave');
                ui['in_period'+idx].hidden = (inst['in'+idx] != 'squareWave');
                ui['in_duty'+idx  ].hidden = (inst['in'+idx] != 'squareWave');
				ui['in_repeat_count'+idx  ].hidden = (inst['in'+idx] != 'squareWave');
				ui['in_delay'+idx  ].hidden = (inst['in'+idx] != 'squareWave');
				ui['in_initial_value'+idx  ].hidden = (inst['in'+idx] != 'squareWave');

                ui['in_custom_source'+idx].hidden = (inst['in'+idx] != 'customWave');
        },

        options : 
            [
                { name: 'None',                displayName: "No Input"},
                { name: 'squareWave',          displayName: "Square Wave"},
                { name: 'customWave',          displayName: "Custom Wave Input"},
				{ name: '0',                   displayName: "Low (0)"},
				{ name: '1',                   displayName: "High (1)"},
                { name: 'TILE1_BOUNDARY.out0', displayName: "Tile 1 Output 0" },
                { name: 'TILE1_BOUNDARY.out1', displayName: "Tile 1 Output 1" },
                { name: 'TILE1_BOUNDARY.out2', displayName: "Tile 1 Output 2" },
                { name: 'TILE1_BOUNDARY.out3', displayName: "Tile 1 Output 3" },
                { name: 'TILE1_BOUNDARY.out4', displayName: "Tile 1 Output 4" },
                { name: 'TILE1_BOUNDARY.out5', displayName: "Tile 1 Output 5" },
                { name: 'TILE1_BOUNDARY.out6', displayName: "Tile 1 Output 6" },
                { name: 'TILE1_BOUNDARY.out7', displayName: "Tile 1 Output 7" },
                { name: 'TILE2_BOUNDARY.out0', displayName: "Tile 2 Output 0" },
                { name: 'TILE2_BOUNDARY.out1', displayName: "Tile 2 Output 1" },
                { name: 'TILE2_BOUNDARY.out2', displayName: "Tile 2 Output 2" },
                { name: 'TILE2_BOUNDARY.out3', displayName: "Tile 2 Output 3" },
                { name: 'TILE2_BOUNDARY.out4', displayName: "Tile 2 Output 4" },
                { name: 'TILE2_BOUNDARY.out5', displayName: "Tile 2 Output 5" },
                { name: 'TILE2_BOUNDARY.out6', displayName: "Tile 2 Output 6" },
                { name: 'TILE2_BOUNDARY.out7', displayName: "Tile 2 Output 7" },
                { name: 'TILE3_BOUNDARY.out0', displayName: "Tile 3 Output 0" },
                { name: 'TILE3_BOUNDARY.out1', displayName: "Tile 3 Output 1" },
                { name: 'TILE3_BOUNDARY.out2', displayName: "Tile 3 Output 2" },
                { name: 'TILE3_BOUNDARY.out3', displayName: "Tile 3 Output 3" },
                { name: 'TILE3_BOUNDARY.out4', displayName: "Tile 3 Output 4" },
                { name: 'TILE3_BOUNDARY.out5', displayName: "Tile 3 Output 5" },
                { name: 'TILE3_BOUNDARY.out6', displayName: "Tile 3 Output 6" },
                { name: 'TILE3_BOUNDARY.out7', displayName: "Tile 3 Output 7" },
                { name: 'TILE4_BOUNDARY.out0', displayName: "Tile 4 Output 0" },
                { name: 'TILE4_BOUNDARY.out1', displayName: "Tile 4 Output 1" },
                { name: 'TILE4_BOUNDARY.out2', displayName: "Tile 4 Output 2" },
                { name: 'TILE4_BOUNDARY.out3', displayName: "Tile 4 Output 3" },
                { name: 'TILE4_BOUNDARY.out4', displayName: "Tile 4 Output 4" },
                { name: 'TILE4_BOUNDARY.out5', displayName: "Tile 4 Output 5" },
                { name: 'TILE4_BOUNDARY.out6', displayName: "Tile 4 Output 6" },
                { name: 'TILE4_BOUNDARY.out7', displayName: "Tile 4 Output 7" },

                { name: 'TILE5_BOUNDARY.out0', displayName: "Tile 5 Output 0" },
                { name: 'TILE5_BOUNDARY.out1', displayName: "Tile 5 Output 1" },
                { name: 'TILE5_BOUNDARY.out2', displayName: "Tile 5 Output 2" },
                { name: 'TILE5_BOUNDARY.out3', displayName: "Tile 5 Output 3" },
                { name: 'TILE5_BOUNDARY.out4', displayName: "Tile 5 Output 4" },
                { name: 'TILE5_BOUNDARY.out5', displayName: "Tile 5 Output 5" },
                { name: 'TILE5_BOUNDARY.out6', displayName: "Tile 5 Output 6" },
                { name: 'TILE5_BOUNDARY.out7', displayName: "Tile 5 Output 7" },
                { name: 'TILE6_BOUNDARY.out0', displayName: "Tile 6 Output 0" },
                { name: 'TILE6_BOUNDARY.out1', displayName: "Tile 6 Output 1" },
                { name: 'TILE6_BOUNDARY.out2', displayName: "Tile 6 Output 2" },
                { name: 'TILE6_BOUNDARY.out3', displayName: "Tile 6 Output 3" },
                { name: 'TILE6_BOUNDARY.out4', displayName: "Tile 6 Output 4" },
                { name: 'TILE6_BOUNDARY.out5', displayName: "Tile 6 Output 5" },
                { name: 'TILE6_BOUNDARY.out6', displayName: "Tile 6 Output 6" },
                { name: 'TILE6_BOUNDARY.out7', displayName: "Tile 6 Output 7" },
                { name: 'TILE7_BOUNDARY.out0', displayName: "Tile 7 Output 0" },
                { name: 'TILE7_BOUNDARY.out1', displayName: "Tile 7 Output 1" },
                { name: 'TILE7_BOUNDARY.out2', displayName: "Tile 7 Output 2" },
                { name: 'TILE7_BOUNDARY.out3', displayName: "Tile 7 Output 3" },
                { name: 'TILE7_BOUNDARY.out4', displayName: "Tile 7 Output 4" },
                { name: 'TILE7_BOUNDARY.out5', displayName: "Tile 7 Output 5" },
                { name: 'TILE7_BOUNDARY.out6', displayName: "Tile 7 Output 6" },
                { name: 'TILE7_BOUNDARY.out7', displayName: "Tile 7 Output 7" },
                { name: 'TILE8_BOUNDARY.out0', displayName: "Tile 8 Output 0" },
                { name: 'TILE8_BOUNDARY.out1', displayName: "Tile 8 Output 1" },
                { name: 'TILE8_BOUNDARY.out2', displayName: "Tile 8 Output 2" },
                { name: 'TILE8_BOUNDARY.out3', displayName: "Tile 8 Output 3" },
                { name: 'TILE8_BOUNDARY.out4', displayName: "Tile 8 Output 4" },
                { name: 'TILE8_BOUNDARY.out5', displayName: "Tile 8 Output 5" },
                { name: 'TILE8_BOUNDARY.out6', displayName: "Tile 8 Output 6" },
                { name: 'TILE8_BOUNDARY.out7', displayName: "Tile 8 Output 7" },
            ]
        },
        {
            name    : 'boundaryInput' + idx,
            default : 'None',
            displayName : 'Input ' + idx,

            onChange: function(inst,ui) {
                ui['input_pipeline'+idx].hidden   = (Common.isType0_Type1() || (inst['boundaryInput'+idx] == 'None') || (inst['boundaryInput'+idx] == '0') || (inst['boundaryInput'+idx] == '1'));
                ui['in_sync_2_cycle_delay_'+idx].hidden   = ((inst['boundaryInput'+idx] != 'squareWave') && (inst['boundaryInput'+idx] != 'customWave') && (inst['boundaryInput'+idx] != 'tileOutput'));
                ui['in_sync'+idx].hidden   = ((inst['boundaryInput'+idx] != 'squareWave') && (inst['boundaryInput'+idx] != 'customWave') && (inst['boundaryInput'+idx] != 'tileOutput'));
                ui['in_edge'+idx].hidden   = ((inst['boundaryInput'+idx] != 'squareWave') && (inst['boundaryInput'+idx] != 'customWave') && (inst['boundaryInput'+idx] != 'tileOutput'));
                ui['in_period'+idx].hidden = (inst['boundaryInput'+idx] != 'squareWave');
                ui['in_duty'+idx  ].hidden = (inst['boundaryInput'+idx] != 'squareWave');
				ui['in_repeat_count'+idx  ].hidden = (inst['boundaryInput'+idx] != 'squareWave');
				ui['in_delay'+idx  ].hidden = (inst['boundaryInput'+idx] != 'squareWave');
				ui['in_initial_value'+idx  ].hidden = (inst['boundaryInput'+idx] != 'squareWave');

                ui['in_custom_source'+idx].hidden = (inst['boundaryInput'+idx] != 'customWave');
                ui['in_custom_source_output'+idx].hidden = (inst['boundaryInput'+idx] != 'customWave');

                ui['tileSelect'+idx].hidden = (inst['boundaryInput'+idx] != 'tileOutput');
                ui['tileOutputSelect'+idx].hidden = (inst['boundaryInput'+idx] != 'tileOutput');
        },

        options : 
            [
                { name: 'None',                displayName: "No Input"},
                { name: 'squareWave',          displayName: "Square Wave"},
                { name: 'customWave',          displayName: "Custom Wave Input"},
				{ name: '0',                   displayName: "Low (0)"},
				{ name: '1',                   displayName: "High (1)"},
                { name: 'tileOutput',          displayName: "Tile Output"}
            ]
        },

        {
            collapsed      : false,
            config :
            [
                {            
                    name    : 'in_edge'+idx,
                    displayName : "Input Edge Detection Pulse",
                    default : 'none',
                    description: 'Edge detection on the inputs, generates 1 cycle pulse on chosen edges - for simulation purposes only',
                    hidden  : true,
                    options : [
                        { name: 'none' },
                        { name: 'rising edge'  },
                        { name: 'falling edge' },
                        { name: 'both edges'   }
                    ]
                },

                {
                    name    : 'input_pipeline'+idx,
                    displayName : "Input Pipeline Enable (1 Cycle Delay)",
                    default : false,
                    description: 'Turns on input pipelining (adds 1 cycle delay to input) - for simulation purposes only',
                    hidden  : true,
                },
                {
                    name    : 'in_sync_2_cycle_delay_'+idx,
                    displayName : "Input Clock Synchronization (2 Cycle Delay)",
                    default : false,
                    description: "Turns the Clock synchronization on the inputs (adds 2 cycle delay to input); the delay is either 2 or 3 cycles, and cannot be predicted to be either - for simulation purposes only",
                    hidden  : true,
                },
                {
                    name    : 'in_sync'+idx,
                    displayName : "Input Clock Synchronization (3 Cycle Delay)",
                    default : false,
                    description: "Turns the Clock synchronization on the inputs (adds 3 cycle delay to input); the delay is either 2 or 3 cycles, and cannot be predicted to be either - for simulation purposes only",
                    hidden  : true,
                },
                {
                    name    : 'in_initial_value'+idx,
                    displayName : "Initial Signal Position",
                    default : 0,
                    description: 'Initial signal position for the square wave',
                    hidden  : true
                },
                {
                    name    : 'in_delay'+idx,
                    displayName : "Initial Delay Amount",
                    default : 0,
                    description: 'Initial delay for the square wave',
                    hidden  : true
                },
                {
                    name    : 'in_period'+idx,
                    displayName : "Square Wave Period",
                    default : 10,
                    description: 'Period of the square wave',
                    hidden  : true
                },
                {
                    name    : 'in_duty'+idx,
                    displayName : "Square Wave Duty",
                    default : 5,
                    description: 'Duty or ON time of the square wave',
                    hidden  : true
                },
                {
                    name    : 'in_repeat_count'+idx,
                    displayName : "Period Repeat Amount",
                    default : 100,
                    description: 'Number of periods the waveform is repeated',
                    hidden  : true
                },

                {
                    name    : 'in_custom_source'+idx,
                    displayName : "Custom Waveform Code",
                    longDescription : longDescriptionCustomSource,
                    default : 'low(100)',
                    multiline : true,
                    hidden  : true
                },
                {
                    name    : 'in_custom_source_output'+idx,
                    displayName : "Custom Waveform Output",
                    default : '',
                    getValue: (inst) => customWaveform.genWaveData(inst['in_custom_source' + idx]),
                    hidden  : true
                },

                {
                    name    : 'tileSelect'+idx,
                    displayName: "Tile Name",
                    longDescription: "Please enter a valid tile name to read the output of",
                    default : '',
                    hidden  : true
                },
                {
                    name    : 'tileOutputSelect'+idx,
                    displayName: "Tile Output",
                    longDescription: "Please select a valid tile output to use",
                    default : 0,
                    hidden  : true
                },
            ]
        },
    ];

    return config;
}

function onChangeLock (inst, ui)
{
    ui["boundaryInput0"].readOnly = inst.setReadOnlyBoundary;
    ui["boundaryInput1"].readOnly = inst.setReadOnlyBoundary;
    ui["boundaryInput2"].readOnly = inst.setReadOnlyBoundary;
    ui["boundaryInput3"].readOnly = inst.setReadOnlyBoundary;
    ui["boundaryInput4"].readOnly = inst.setReadOnlyBoundary;
    ui["boundaryInput5"].readOnly = inst.setReadOnlyBoundary;
    ui["boundaryInput6"].readOnly = inst.setReadOnlyBoundary;
    ui["boundaryInput7"].readOnly = inst.setReadOnlyBoundary;

    for(var i = 0; i < 8; i++)
    {
        ui['input_pipeline'+i].readOnly = inst.setReadOnlyBoundary;
        ui['in_sync_2_cycle_delay_'+i].readOnly = inst.setReadOnlyBoundary;
        ui['in_sync'+i].readOnly = inst.setReadOnlyBoundary;
        ui['in_edge'+i].readOnly = inst.setReadOnlyBoundary;
        ui['in_period'+i].readOnly = inst.setReadOnlyBoundary;
        ui['in_duty'+i  ].readOnly = inst.setReadOnlyBoundary;
        ui['in_repeat_count'+i  ].readOnly = inst.setReadOnlyBoundary;
        ui['in_delay'+i  ].readOnly = inst.setReadOnlyBoundary;
        ui['in_initial_value'+i  ].readOnly = inst.setReadOnlyBoundary;

        ui['in_custom_source'+i].readOnly = inst.setReadOnlyBoundary;

        ui['tileSelect'+i].readOnly = inst.setReadOnlyBoundary;
        ui['tileOutputSelect'+i].readOnly = inst.setReadOnlyBoundary;
    }
}

/**
 * Validate this module's configuration
 *
 * @param inst       - Watchdog instance to be validated
 * @param validation - Issue reporting object
 */
function validate(inst, vo)
{
    Common.validateNames(inst, vo);

    for (let i = 0; i < 8; ++i) {
        if((inst['boundaryInput'+i] == 'customWave') && (inst['in_custom_source_output'+i].toLowerCase().includes("error")))
        {
            Common.logError(vo, inst, ['in_custom_source_output'+i], 'There is an error in the custom waveform code.');
        }
        if (inst['boundaryInput'+i] == 'squareWave') {
            if (inst['in_period'+i] < 2) {
                Common.logError(vo, inst, ['in_period'+i],
                            'The Square Wave period must be >= 2');
            }
            if (inst['in_duty'+i] < 1 || inst['in_duty'+i]>= inst['in_period'+i]) {
                Common.logError(vo, inst, ['in_duty'+i],
                            'The Square Wave duty cycle must be >= 1 and < period.');
            }
            if((inst["in_initial_value"+i] != 0) && (inst["in_initial_value"+i] != 1))
            {
                Common.logError(vo, inst, ['in_initial_value'+i],
                            'The Square Wave initial value must be 0 or 1.');
            }
            if(inst["in_delay"+i] < 0)
            {
                Common.logError(vo, inst, ['in_delay'+i],
                            'The Square Wave delay must be at least 0 cycle.');
            }
        }
        if(Common.isType2())
        {
            if(((inst['boundaryInput'+i] == 'squareWave') || (inst['boundaryInput'+i] == 'customWave')) && (inst['input_pipeline'+i] == false) && (inst['in_sync'+i] == false) && (inst['in_sync_2_cycle_delay_'+i] == false))
            {
                Common.logInfo(vo, inst, ['input_pipeline'+i],
                            'If this input is synchronous the input pipeline must be enabled. Check the device TRM for more details.');
                Common.logInfo(vo, inst, ['in_sync_2_cycle_delay_'+i],
                            'If this input is asynchronous, synchronization must be enabled. Check the device TRM for more details.');
            }
            if((inst['boundaryInput'+i] == 'tileOutput') && (inst['input_pipeline'+i] == false))
            {
                Common.logWarning(vo, inst, ['input_pipeline'+i],
                            'Synchronous signals coming from Tile outputs must have the input pipeline enabled.');
            }
            if(((inst['boundaryInput'+i] == 'squareWave') || (inst['boundaryInput'+i] == 'customWave')) && (((inst['input_pipeline'+i] == true) && (inst['in_sync_2_cycle_delay_'+i] == true)) || (((inst['input_pipeline'+i] == true) && (inst['in_sync'+i] == true)))))
            {
                Common.logInfo(vo, inst, ['input_pipeline'+i],
                            'Enabling both the input pipeline and synchronizer will concatenate the delays (enabling both is not necessary).');
            }
        }
        else if(((inst['boundaryInput'+i] == 'squareWave') || (inst['boundaryInput'+i] == 'customWave')) && (inst['in_sync'+i] == false) && (inst['in_sync_2_cycle_delay_'+i] == false))
        {
            Common.logInfo(vo, inst, ['in_sync_2_cycle_delay_'+i],
                        'If this input is asynchronous, synchronization must be enabled. Check the device TRM for more details.');
        }
        if((inst['in_sync'+i] == true) && (inst['in_sync_2_cycle_delay_'+i] == true))
        {
            Common.logError(vo, inst, ['in_sync_2_cycle_delay_'+i],
                        'There is only 1 input synchronization that can occur, which has either a 2 or 3 cycle delay.');
        }

        if(inst['boundaryInput'+i] == 'tileOutput')
        {
            if((inst['tileOutputSelect'+i] < 0) || (inst['tileOutputSelect'+i] > 7))
            {
                Common.logError(vo, inst, ['tileOutputSelect'+i],
                            'The tile output number must be between 0 and 7.');
            }
            var matches = 0;
            let tileInstances = system.modules["/utilities/clb_tool/clb_syscfg/source/TILE"].$instances;
            for(let j = 0; j < system.modules["/utilities/clb_tool/clb_syscfg/source/TILE"].$instances.length; j++)
            {
                if(inst['tileSelect' + i] === tileInstances[j].$name)
                {
                    matches = 1;
                }
            }
            if(matches == 0)
            {
                Common.logError(vo, inst, ['tileSelect'+i],
                            'The tile name must match an existing tile.');
            }
            //console.log(system.modules["/utilities/clb_tool/clb_syscfg/source/TILE"].$instances[0].$name)
            //Common.printDebugObject(system.modules["/utilities/clb_tool/clb_syscfg/source/TILE"].$instances[0].$name)
        }
    }
}

// Define the common/portable base Watchdog
exports = {
    config : inputCfg(0).concat(
             inputCfg(1),
             inputCfg(2),
             inputCfg(3),
             inputCfg(4),
             inputCfg(5),
             inputCfg(6),
             inputCfg(7),
             {
                 name        : "setReadOnlyBoundary",
                 default     : false,
                 hidden      : true,
                 onChange    : onChangeLock
             }),
    displayName         : "Inputs Conditioner",
    validate            : validate,
    description         : "Inputs Conditioner",
    defaultInstanceName : "BOUNDARY",
    longDescription     : longDescription,
};