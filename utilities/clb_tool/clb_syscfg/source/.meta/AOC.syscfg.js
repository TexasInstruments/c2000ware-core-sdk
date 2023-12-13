"use strict";
/*global exports, system*/

let Common   = system.getScript('/utilities/clb_tool/clb_syscfg/source/Common.js');
let customWaveform   = system.getScript("/utilities/clb_tool/clb_syscfg/source/CustomWaveform.js");
let logError = Common.logError;

/* Intro splash on GUI */
let longDescription = `
The **Asynchronous Output Conditioning (AOC) Block** submodule enables the filtering and modification of signals going into or coming out of the CLB. 
When configuring inputs into the AOC Block, either the respective BOUNDARY input or the respective BOUNDARY output can be selected. 
The signals pass through three different stages which are each responsible for performing a specific type of logic modification. 
The output of this AOC block is the modified version of the input which has undergone inverting, gating, release control, or some combination of the three.

* **Stage 1 (Inverting)**: This stage allows for the input signal to be inverted.
* **Stage 2 (Gating)**: This stage allows for the input signal to be gated (AND, OR, or XOR) with a gating control signal. 
This control signal can come from any of the CLB tile's BOUNDARY outputs or from a software register.
* **Stage 3 (Release Control)**: This stage allows for the input signal to be set or cleared with a gating control signal. 
Similarly to the gating stage, this control signal can be one of the CLB tile's outputs or a software register.

For each of the stages, there is a bypass option which passes the signal unmodified to the next stage.

_**AOC Block**_

![Image Missing](../../utilities/clb_tool/clb_syscfg/source/.meta/references/AOC.png)

_**AOC Block and the CLB Tile**_

![Image Missing](../../utilities/clb_tool/clb_syscfg/source/.meta/references/AOC_and_CLB.png)
`;

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

/* Array of Watchdog configurables that are common across device families */
let config = [
    {
        name        : 'aocDescription',
        longDescription : "This field is for the user to provide a description of this block's logic",
        displayName : 'User Description',
        default     : '',
        multiline   : true
    },
    {
        name        : 'bypass_mux',
        displayName : "Bypass AOC",
        longDescription : 'Bypass the AOC block using this mux (enabling this routes the corresponding output LUT to the CLB boundary output)',
        default     : true
    },
    {
        name        : 'input_mode',
        displayName : "AOC Input Mode",
        longDescription :   'Choose between using CLB boundary input or CLB output as the input source ' +
                            'for the output conidtioning block',
        default     : "OUTPUT",
        options     : [
            {name:"OUTPUT", displayName:"CLB OUTPUT delayed by 1 cycle"},
            {name:"INPUT", displayName:"CLB INPUT"}
        ]
    },
    {
        name: "GROUP_STAGE1",
        displayName: "Stage 1",
        description: "Stage 1 (Inverting)",
        config: [
            {
                name        : 'stage1_mux',
                displayName : "Invert Signal",
                longDescription : 'Choose to invert the signal or bypass this stage',
                default     : false
            }
        ]
    },
    {
        name: "GROUP_STAGE2",
        displayName: "Stage 2",
        description: "Stage 2 (Gating)",
        config: [
            {
                name        : 'stage2_mux',
                displayName : "Gate Type",
                longDescription : 'Choose the type of logic gate, or bypass this stage',
                default     : "BYPASS",
                options     : [
                    {name:"BYPASS"},
                    {name:"AND", displayName: "AND Gate"},
                    {name:"OR", displayName: "OR Gate"},
                    {name:"XOR", displayName: "XOR Gate"}
                ]
            },
            {
                name        : 'stage2_gate_mux',
                displayName : "Gate Signal",
                longDescription : 'Choose the signal which will be gated with the output from stage 1',
                default     : "SW",
                options     : [
                    {name:"SW", displayName:"Software Control (CLB_GP_REG.SW_GATING_CTRL_n)"},
                    {name:"OUTPUT0", displayName: "CLB OUTPUT0"},
                    {name:"OUTPUT1", displayName: "CLB OUTPUT1"},
                    {name:"OUTPUT2", displayName: "CLB OUTPUT2"},
                    {name:"OUTPUT3", displayName: "CLB OUTPUT3"},
                    {name:"OUTPUT4", displayName: "CLB OUTPUT4"},
                    {name:"OUTPUT5", displayName: "CLB OUTPUT5"},
                    {name:"OUTPUT6", displayName: "CLB OUTPUT6"},
                    {name:"OUTPUT7", displayName: "CLB OUTPUT7"},
                ],
                onChange    : onUseCustomStage2
            },
            {
                name    : 'custom_sw_gate_source',
                displayName : "Software Custom Waveform Code",
                longDescription : longDescriptionCustomSource,
                default : 'low(100)',
                multiline : true,
                hidden  : false
            },
            {
                name    : 'custom_sw_gate_source_output',
                displayName : "Software Custom Waveform Output",
                default : '',
                getValue: (inst) => customWaveform.genWaveData(inst.custom_sw_gate_source),
                hidden  : false
            },
        ]
    },
    {
        name: "GROUP_STAGE3",
        displayName: "Stage 3",
        description: "Stage 3 (Release Control)",
        config: [
            {
                name        : 'stage3_mux',
                displayName : "Release Type",
                longDescription : 'Choose the type to set/clear the output of stage 2 based on a release signal, delay the output, or bypass this stage',
                default     : "BYPASS",
                options     : [
                    {name:"BYPASS"},
                    {name:"CLEAR", displayName: "Clear signal"},
                    {name:"SET", displayName: "SET signal"},
                    {name:"DELAY", displayName: "Delay signal"}
                ]
            },
            {
                name        : 'stage3_release_mux',
                displayName : "Release Signal",
                longDescription : 'Choose the release signal which will be used on the output from stage 2',
                default     : "SW",
                options     : [
                    {name:"SW", displayName:"Software Control (CLB_GP_REG.SW_RLS_CTRL_n)"},
                    {name:"OUTPUT0", displayName: "CLB OUTPUT0"},
                    {name:"OUTPUT1", displayName: "CLB OUTPUT1"},
                    {name:"OUTPUT2", displayName: "CLB OUTPUT2"},
                    {name:"OUTPUT3", displayName: "CLB OUTPUT3"},
                    {name:"OUTPUT4", displayName: "CLB OUTPUT4"},
                    {name:"OUTPUT5", displayName: "CLB OUTPUT5"},
                    {name:"OUTPUT6", displayName: "CLB OUTPUT6"},
                    {name:"OUTPUT7", displayName: "CLB OUTPUT7"},
                ],
                onChange    : onUseCustomStage3
            },
            {
                name    : 'custom_sw_release_source',
                displayName : "Software Custom Waveform Code",
                longDescription : longDescriptionCustomSource,
                default : 'low(100)',
                multiline : true,
                hidden  : false
            },
            {
                name    : 'custom_sw_release_source_output',
                displayName : "Software Custom Waveform Output",
                default : '',
                getValue: (inst) => customWaveform.genWaveData(inst.custom_sw_release_source),
                hidden  : false
            },
        ]
    },
    {
        name        : "setReadOnlyAOC",
        default     : false,
        hidden      : true,
        onChange    : onChangeLock
    }
];

function onChangeLock (inst, ui)
{
    ui["aocDescription"].readOnly = inst.setReadOnlyAOC;
    ui["bypass_mux"].readOnly = inst.setReadOnlyAOC;
    ui["input_mode"].readOnly = inst.setReadOnlyAOC;
    ui["stage1_mux"].readOnly = inst.setReadOnlyAOC;
    ui["stage2_mux"].readOnly = inst.setReadOnlyAOC;
    ui["stage2_gate_mux"].readOnly = inst.setReadOnlyAOC;
    ui["stage3_mux"].readOnly = inst.setReadOnlyAOC;
    ui["stage3_release_mux"].readOnly = inst.setReadOnlyAOC;
    ui["custom_sw_gate_source"].readOnly = inst.setReadOnlyAOC;
    ui["custom_sw_release_source"].readOnly = inst.setReadOnlyAOC;
}

function onUseCustomStage2 (inst, ui)
{
    if(inst.stage2_gate_mux == "SW")
    {
        ui["custom_sw_gate_source"].hidden = false;
        ui["custom_sw_gate_source_output"].hidden = false;
    }
    else
    {
        ui["custom_sw_gate_source"].hidden = true;
        ui["custom_sw_gate_source_output"].hidden = true;
    }
}

function onUseCustomStage3 (inst, ui)
{
    if(inst.stage3_release_mux == "SW")
    {
        ui["custom_sw_release_source"].hidden = false;
        ui["custom_sw_release_source_output"].hidden = false;
    }
    else
    {
        ui["custom_sw_release_source"].hidden = true;
        ui["custom_sw_release_source_output"].hidden = true;
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
    if((inst.stage2_gate_mux.toLowerCase().includes("sw")) && (inst.custom_sw_gate_source_output.toLowerCase().includes("error")))
    {
        Common.logError(vo, inst, "custom_sw_gate_source_output", 'There is an error in the custom waveform code.');
    }
    if((inst.stage3_release_mux.toLowerCase().includes("sw")) && (inst.custom_sw_release_source_output.toLowerCase().includes("error")))
    {
        Common.logError(vo, inst, "custom_sw_release_source_output", 'There is an error in the custom waveform code.');
    }
}

// Define the common/portable base Watchdog
exports = {
    displayName         : 'AOC',
    description         : 'AOC',
    defaultInstanceName : 'AOC_',
    longDescription     : longDescription,
    config              : config,
    validate            : validate,
};