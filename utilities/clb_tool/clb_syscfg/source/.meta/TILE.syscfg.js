"use strict";
/*global exports, system*/

let Common   = system.getScript("/utilities/clb_tool/clb_syscfg/source/Common.js");
let logError = Common.logError;

/* Intro splash on GUI */
let longDescription = `
Tile Design for Configurable Logic Block (CLB)

For more information on the CLB:
*   User Guide: [CLB Tool User Guide](http://www.ti.com/lit/SPRUIR8 )
*   Video Training: [CLB Introduction](https://www.ti.com/video/6101195238001 )
*   Video Training: [CLB Architecture](https://www.ti.com/video/6101209618001 )
*   Video Training: [CLB Programming Tool](https://www.ti.com/video/6101205618001 )
*   Video Training: [How the C2000 CLB Tool Integrates Custom Logic In My Design](https://www.ti.com/video/6090995137001 )
*   Video Training: [Automotive Tech Day 2020](https://www.ti.com/video/6195168576001 )
*   Application Report: [Enable Differentiation and Win with CLB in Various Applications](https://www.ti.com/lit/ml/slyp681/slyp681.pdf )
*   Application Report: [C2000 Position Manager PTO API Reference Guide](https://www.ti.com/lit/ug/sprac77e/sprac77e.pdf )
*   Application Report: [Designing With The C2000 Configurable Logic Block](https://www.ti.com/lit/SPRACL3 )
*   Application Report: [How to Migrate Custom Logic From an FPGA/CPLD to C2000 Real-Time MCU](https://ti.com/lit/SPRACO2 )
*   Application Report: [How to Implement Custom Serial Interfaces Using the Configurable Logic Block (CLB)](https://ti.com/lit/an/sprad62/sprad62.pdf )
*   Application Report: [Achieve Delayed Protection for Three-Level Inverter With CLB](https://www.ti.com/lit/an/spracy3/spracy3.pdf )
*   Application Report: [Tamagawa T-Format Absolute-Encoder Master Interface Reference Design for C2000 MCUs](https://www.ti.com/lit/ug/tidue74d/tidue74d.pdf )
`;
/*
Broken Link (once a playlist link works, replace relevant video links with this line):
*   Video Training: [C2000 Configurable Logic Block (CLB) Series](https://training.ti.com/clb-training-c2000-mcus?context=1137766-1138740 )
*/
let longDescriptionSimulation = `
Updates the appropriate application file (clb_simulation.bat or clb_simulation) to generate the CLB.vcd simulation file.

To generate the CLB.vcd file for GTKWave, run the clb_simulation file. The clb_simulation 
program file can be found where the SysConfig output files are generated (i.e. /syscfg). 
Please refer to the CLB Tool User Guide for more information on how to set up GTKWave.
`

let LUT_BLOCKS = [
    {name: "LUT_0", displayName: "Look-Up Table 0"},
    {name: "LUT_1", displayName: "Look-Up Table 1"},
    {name: "LUT_2", displayName: "Look-Up Table 2"},
];

let FSM_BLOCKS = [
    {name: "FSM_0", displayName: "Finite State Machine 0"},
    {name: "FSM_1", displayName: "Finite State Machine 1"},
    {name: "FSM_2", displayName: "Finite State Machine 2"},
];

let COUNTER_BLOCKS = [
    {name: "COUNTER_0", displayName: "Counter 0"},
    {name: "COUNTER_1", displayName: "Counter 1"},
    {name: "COUNTER_2", displayName: "Counter 2"},
];

let OUTLUT_BLOCKS = [
    {name: "OUTLUT_0", displayName: "Output Look-Up Table 0"},
    {name: "OUTLUT_1", displayName: "Output Look-Up Table 1"},
    {name: "OUTLUT_2", displayName: "Output Look-Up Table 2"},
    {name: "OUTLUT_3", displayName: "Output Look-Up Table 3"},
    {name: "OUTLUT_4", displayName: "Output Look-Up Table 4"},
    {name: "OUTLUT_5", displayName: "Output Look-Up Table 5"},
    {name: "OUTLUT_6", displayName: "Output Look-Up Table 6"},
    {name: "OUTLUT_7", displayName: "Output Look-Up Table 7"},
];

let AOC_BLOCKS = [
    {name: "AOC_0", displayName: "Asynchronous Output Conditioning Block 0"},
    {name: "AOC_1", displayName: "Asynchronous Output Conditioning Block 1"},
    {name: "AOC_2", displayName: "Asynchronous Output Conditioning Block 2"},
    {name: "AOC_3", displayName: "Asynchronous Output Conditioning Block 3"},
    {name: "AOC_4", displayName: "Asynchronous Output Conditioning Block 4"},
    {name: "AOC_5", displayName: "Asynchronous Output Conditioning Block 5"},
    {name: "AOC_6", displayName: "Asynchronous Output Conditioning Block 6"},
    {name: "AOC_7", displayName: "Asynchronous Output Conditioning Block 7"},
];

function moduleInstances(inst)
{
    let components  = [
        {
            moduleName: "/utilities/clb_tool/clb_syscfg/source/BOUNDARY",
            displayName: "Boundary Inputs (Simulation Only)",
            description: inst.$name,
            name: "BOUNDARY",
            collapsed: true,
            args: {
                setReadOnlyBoundary: inst.tileLock ?? false                         //If inst.tileLock is undefined, use false instead; nullish coalescing
            }
        },
        {
            moduleName: "/utilities/clb_tool/clb_syscfg/source/LUT",
            displayName: "Look-Up Table 0",
            description: inst.$name,
            name: "LUT_0",
            collapsed: true,
            hidden: (inst.streamlineMode && !inst.lutBlocks.includes("LUT_0")),
            args: {
                setReadOnlyLut: inst.tileLock ?? false
            }
        },
        {
            moduleName: "/utilities/clb_tool/clb_syscfg/source/LUT",
            displayName: "Look-Up Table 1",
            description: inst.$name,
            name: "LUT_1",
            collapsed: true,
            hidden: (inst.streamlineMode && !inst.lutBlocks.includes("LUT_1")),
            args: {
                setReadOnlyLut: inst.tileLock ?? false
            }
        },
        {
            moduleName: "/utilities/clb_tool/clb_syscfg/source/LUT",
            displayName: "Look-Up Table 2",
            description: inst.$name,
            name: "LUT_2",
            collapsed: true,
            hidden: (inst.streamlineMode && !inst.lutBlocks.includes("LUT_2")),
            args: {
                setReadOnlyLut: inst.tileLock ?? false
            }
        },
        {
            moduleName: "/utilities/clb_tool/clb_syscfg/source/FSM",
            displayName: "Finite State Machine 0",
            description: inst.$name,
            name: "FSM_0",
            collapsed: true,
            hidden: (inst.streamlineMode && !inst.fsmBlocks.includes("FSM_0")),
            args: {
                setReadOnlyFSM: inst.tileLock ?? false
            }
        },
        {
            moduleName: "/utilities/clb_tool/clb_syscfg/source/FSM",
            displayName: "Finite State Machine 1",
            description: inst.$name,
            name: "FSM_1",
            collapsed: true,
            hidden: (inst.streamlineMode && !inst.fsmBlocks.includes("FSM_1")),
            args: {
                setReadOnlyFSM: inst.tileLock ?? false
            }
        },
        {
            moduleName: "/utilities/clb_tool/clb_syscfg/source/FSM",
            displayName: "Finite State Machine 2",
            description: inst.$name,
            name: "FSM_2",
            collapsed: true,
            hidden: (inst.streamlineMode && !inst.fsmBlocks.includes("FSM_2")),
            args: {
                setReadOnlyFSM: inst.tileLock ?? false
            }
        },
        {
            moduleName: "/utilities/clb_tool/clb_syscfg/source/COUNTER",
            displayName: " Counter 0",
            description: inst.$name,
            name: "COUNTER_0",
            collapsed: true,
            hidden: (inst.streamlineMode && !inst.counterBlocks.includes("COUNTER_0")),
            args: {
                setReadOnlyCounter: inst.tileLock ?? false
            }
        },
        {
            moduleName: "/utilities/clb_tool/clb_syscfg/source/COUNTER",
            displayName: "Counter 1",
            description: inst.$name,
            name: "COUNTER_1",
            collapsed: true,
            hidden: (inst.streamlineMode && !inst.counterBlocks.includes("COUNTER_1")),
            args: {
                setReadOnlyCounter: inst.tileLock ?? false
            }
        },
        {
            moduleName: "/utilities/clb_tool/clb_syscfg/source/COUNTER",
            displayName: "Counter 2",
            description: inst.$name,
            name: "COUNTER_2",
            collapsed: true,
            hidden: (inst.streamlineMode && !inst.counterBlocks.includes("COUNTER_2")),
            args: {
                setReadOnlyCounter: inst.tileLock ?? false
            }
        },
        {
            moduleName: "/utilities/clb_tool/clb_syscfg/source/OUTLUT",
            displayName: "Output Look-Up Table 0",
            description: inst.$name,
            name: "OUTLUT_0",
            collapsed: true,
            hidden: (inst.streamlineMode && !inst.outlutBlocks.includes("OUTLUT_0")),
            args: {
                setReadOnlyOutLut: inst.tileLock ?? false
            }
        },
        {
            moduleName: "/utilities/clb_tool/clb_syscfg/source/OUTLUT",
            displayName: "Output Look-Up Table 1",
            description: inst.$name,
            name: "OUTLUT_1",
            collapsed: true,
            hidden: (inst.streamlineMode && !inst.outlutBlocks.includes("OUTLUT_1")),
            args: {
                setReadOnlyOutLut: inst.tileLock ?? false
            }
        },
        {
            moduleName: "/utilities/clb_tool/clb_syscfg/source/OUTLUT",
            displayName: "Output Look-Up Table 2",
            description: inst.$name,
            name: "OUTLUT_2",
            collapsed: true,
            hidden: (inst.streamlineMode && !inst.outlutBlocks.includes("OUTLUT_2")),
            args: {
                setReadOnlyOutLut: inst.tileLock ?? false
            }
        },
        {
            moduleName: "/utilities/clb_tool/clb_syscfg/source/OUTLUT",
            displayName: "Output Look-Up Table 3",
            description: inst.$name,
            name: "OUTLUT_3",
            collapsed: true,
            hidden: (inst.streamlineMode && !inst.outlutBlocks.includes("OUTLUT_3")),
            args: {
                setReadOnlyOutLut: inst.tileLock ?? false
            }
        },
        {
            moduleName: "/utilities/clb_tool/clb_syscfg/source/OUTLUT",
            displayName: "Output Look-Up Table 4",
            description: inst.$name,
            name: "OUTLUT_4",
            collapsed: true,
            hidden: (inst.streamlineMode && !inst.outlutBlocks.includes("OUTLUT_4")),
            args: {
                setReadOnlyOutLut: inst.tileLock ?? false
            }
        },
        {
            moduleName: "/utilities/clb_tool/clb_syscfg/source/OUTLUT",
            displayName: "Output Look-Up Table 5",
            description: inst.$name,
            name: "OUTLUT_5",
            collapsed: true,
            hidden: (inst.streamlineMode && !inst.outlutBlocks.includes("OUTLUT_5")),
            args: {
                setReadOnlyOutLut: inst.tileLock ?? false
            }
        },
        {
            moduleName: "/utilities/clb_tool/clb_syscfg/source/OUTLUT",
            displayName: "Output Look-Up Table 6",
            description: inst.$name,
            name: "OUTLUT_6",
            collapsed: true,
            hidden: (inst.streamlineMode && !inst.outlutBlocks.includes("OUTLUT_6")),
            args: {
                setReadOnlyOutLut: inst.tileLock ?? false
            }
        },
        {
            moduleName: "/utilities/clb_tool/clb_syscfg/source/OUTLUT",
            displayName: "Output Look-Up Table 7",
            description: inst.$name,
            name: "OUTLUT_7",
            collapsed: true,
            hidden: (inst.streamlineMode && !inst.outlutBlocks.includes("OUTLUT_7")),
            args: {
                setReadOnlyOutLut: inst.tileLock ?? false
            }
        },
        {
            moduleName: "/utilities/clb_tool/clb_syscfg/source/HLC",
            displayName: "High Level Controller",
            description: inst.$name,
            name: "HLC",
            collapsed: true,
            args: {
                setReadOnlyHLC: inst.tileLock ?? false
            }
        }
    ];

    if (Common.isType1_Type2())
    {
        components = components.concat([
            {
                moduleName: "/utilities/clb_tool/clb_syscfg/source/AOC",
                displayName: "Asynchronous Output Conditioning Block 0",
                description: inst.$name,
                name: "AOC_0",
                collapsed: true,
                hidden: (inst.streamlineMode && !inst.aocBlocks.includes("AOC_0")),
                args: {
                    setReadOnlyAOC: inst.tileLock ?? false
                }
            },
            {
                moduleName: "/utilities/clb_tool/clb_syscfg/source/AOC",
                displayName: "Asynchronous Output Conditioning Block 1",
                description: inst.$name,
                name: "AOC_1",
                collapsed: true,
                hidden: (inst.streamlineMode && !inst.aocBlocks.includes("AOC_1")),
                args: {
                    setReadOnlyAOC: inst.tileLock ?? false
                }
            },
            {
                moduleName: "/utilities/clb_tool/clb_syscfg/source/AOC",
                displayName: "Asynchronous Output Conditioning Block 2",
                description: inst.$name,
                name: "AOC_2",
                collapsed: true,
                hidden: (inst.streamlineMode && !inst.aocBlocks.includes("AOC_2")),
                args: {
                    setReadOnlyAOC: inst.tileLock ?? false
                }
            },
            {
                moduleName: "/utilities/clb_tool/clb_syscfg/source/AOC",
                displayName: "Asynchronous Output Conditioning Block 3",
                description: inst.$name,
                name: "AOC_3",
                collapsed: true,
                hidden: (inst.streamlineMode && !inst.aocBlocks.includes("AOC_3")),
                args: {
                    setReadOnlyAOC: inst.tileLock ?? false
                }
            },
            {
                moduleName: "/utilities/clb_tool/clb_syscfg/source/AOC",
                displayName: "Asynchronous Output Conditioning Block 4",
                description: inst.$name,
                name: "AOC_4",
                collapsed: true,
                hidden: (inst.streamlineMode && !inst.aocBlocks.includes("AOC_4")),
                args: {
                    setReadOnlyAOC: inst.tileLock ?? false
                }
            },
            {
                moduleName: "/utilities/clb_tool/clb_syscfg/source/AOC",
                displayName: "Asynchronous Output Conditioning Block 5",
                description: inst.$name,
                name: "AOC_5",
                collapsed: true,
                hidden: (inst.streamlineMode && !inst.aocBlocks.includes("AOC_5")),
                args: {
                    setReadOnlyAOC: inst.tileLock ?? false
                }
            },
            {
                moduleName: "/utilities/clb_tool/clb_syscfg/source/AOC",
                displayName: "Asynchronous Output Conditioning Block 6",
                description: inst.$name,
                name: "AOC_6",
                collapsed: true,
                hidden: (inst.streamlineMode && !inst.aocBlocks.includes("AOC_6")),
                args: {
                    setReadOnlyAOC: inst.tileLock ?? false
                }
            },
            {
                moduleName: "/utilities/clb_tool/clb_syscfg/source/AOC",
                displayName: "Asynchronous Output Conditioning Block 7",
                description: inst.$name,
                name: "AOC_7",
                collapsed: true,
                hidden: (inst.streamlineMode && !inst.aocBlocks.includes("AOC_7")),
                args: {
                    setReadOnlyAOC: inst.tileLock ?? false
                }
            }
        ]);
    }
    return components;
}

var config = [
	{ 
		name : 'unused', 
		default : '', 
		hidden: true
	}
]

if (Common.isType2()){
	config = [
		{ 
			name : 'pipeline_mode',
			displayName : 'Pipeline Mode',
			description : 'Pipeline Mode for COUNTER and HLC submodules', 
			default : false,
		}
	]
}

config = config.concat([
    {
        name: "GROUP_UI_CONFIG",
        displayName: "UI Configuration Options",
        longDescription: "Options for streamlining the CLB Tool user interface or locking the tile settings",
        config: [
            {
                name: "tileLock",
                displayName: "Lock Tile Editing",
                longDescription: "Locks the Tile Design from being edited",
                default: false
            },
            {
                name : 'streamlineMode',
                displayName : 'Streamline Code Generation',
                longDescription : 'Enabling this setting will generate code only for the specified CLB blocks',
                default : false,
                onChange : onChangeCodeGen
            },
            {
                name : 'lutBlocks',
                displayName : 'Enabled LUT Blocks',
                longDescription : 'Configures which LUT blocks will have their corresponding code generated',
                hidden  : true,
                minSelections : 0,
                default : [],
                options : LUT_BLOCKS
            },
            {
                name : 'fsmBlocks',
                displayName : 'Enabled FSM Blocks',
                longDescription : 'Configures which FSM blocks will have their corresponding code generated',
                hidden  : true,
                minSelections : 0,
                default : [],
                options : FSM_BLOCKS
            },
            {
                name : 'counterBlocks',
                displayName : 'Enabled Counter Blocks',
                longDescription : 'Configures which counter blocks will have their corresponding code generated',
                hidden  : true,
                minSelections : 0,
                default : [],
                options : COUNTER_BLOCKS
            },
            {
                name : 'outlutBlocks',
                displayName : 'Enabled Output LUT Blocks',
                longDescription : 'Configures which output LUT blocks will have their corresponding code generated',
                hidden  : true,
                minSelections : 0,
                default : [],
                options : OUTLUT_BLOCKS
            },
            {
                name : 'aocBlocks',
                displayName : 'Enabled AOC Blocks',
                longDescription : 'Configures which AOC blocks will have their corresponding code generated',
                hidden  : true,
                minSelections : 0,
                default : [],
                options : AOC_BLOCKS
            }
        ]
    }
]);

function onChangeCodeGen(inst, ui)
{
    if(inst.streamlineMode == true)
    {
        ui["lutBlocks"].hidden = false;
        ui["fsmBlocks"].hidden = false;
        ui["counterBlocks"].hidden = false;
        ui["outlutBlocks"].hidden = false;
        if(Common.isType1_Type2())
        {
            ui["aocBlocks"].hidden = false;
        }
    }
    else
    {
        ui["lutBlocks"].hidden = true;
        ui["fsmBlocks"].hidden = true;
        ui["counterBlocks"].hidden = true;
        ui["outlutBlocks"].hidden = true;
        if(Common.isType1_Type2())
        {
            ui["aocBlocks"].hidden = true;
        }
    }
}

function onValidate(inst, validation)
{
    Common.logInfo(validation, inst, "$name", "To utilize the CLB simulation, please see the \"Generate CLB Simulation File\" description within the Global Parameters in the Tile Design module.")
}
function onValidateStatic(inst, validation)
{
    if(inst.clock_period < 1000)
    {
        Common.logWarning(validation, inst, "clock_period", "The value for Clock Period is in picoseconds; a value less than 1000 is less than 1 nanosecond");
    }
    if(inst.sim_duration < 1000)
    {
        Common.logWarning(validation, inst, "sim_duration", "The value for Simulation Duration is in picoseconds; a value less than 1000 is less than 1 nanosecond");
    }
    if(inst.reset_duration < 1000)
    {
        Common.logWarning(validation, inst, "reset_duration", "The value for Reset Duration is in picoseconds; a value less than 1000 is less than 1 nanosecond");
    }
}

// Define the common/portable base Watchdog
exports = {
    displayName         : "Tile Design",
    description         : "Tile Design",
    defaultInstanceName : "TILE",
    longDescription     : longDescription,
    moduleInstances     : moduleInstances,
    documentation       : "/utilities/clb_tool/clb_syscfg/source/CLB Tool Users Guide (beta1).pdf",
    moduleStatic        : {
        config : [
                    {
                        name: "generateSimulation",
                        displayName: "Generate CLB Simulation File",
                        longDescription: longDescriptionSimulation,
                        default: false
                    },
                    {
                        name: "GROUP_SIMULATION",
                        displayName: "Simulation Options",
                        longDescription: "Options for CLB simulation files",
                        config: [
                            {
                                name        : 'clock_period',
                                displayName : 'Clock Period (ps)',
                                longDescription : 'Period of the clock specified in Pico Seconds used for simulation in System C',
                                default     : 20000
                            },
                            {
                                name        : 'sim_duration',
                                displayName : 'Simulation Duration (ps)',
                                longDescription : 'Duration of the simulation, specified in Pico Seconds)',
                                default     : 50000000
                            },
                            {
                                name        : 'reset_duration',
                                displayName : 'Reset Duration (ps)',
                                longDescription : 'Time at which reset signal is deassrted, specified in Pico Seconds',
                                default     : 40000
                            }
                        ]
                    },
                ],
        validate: onValidateStatic
    },
    modules: (inst) => {
        if (inst && (system.getOS().includes("win"))) {
            return [
                {
                    name: "pullInTemplateH",
                    moduleName: "/utilities/clb_tool/clb_syscfg/source/clb_run_dynamic_template_clb_h.js"
                },
                {
                    name: "pullInTemplateC",
                    moduleName: "/utilities/clb_tool/clb_syscfg/source/clb_run_dynamic_template_clb_c.js"
                },
                {
                    name: "pullInTemplateSIM",
                    moduleName: "/utilities/clb_tool/clb_syscfg/source/clb_run_dynamic_template_clb_sim.js"
                },
                {
                    name: "pullInTemplateDOT",
                    moduleName: "/utilities/clb_tool/clb_syscfg/source/clb_run_dynamic_template_clb_dot.js"
                },
                {
                    name: "pullInTemplateBAT",
                    moduleName: "/utilities/clb_tool/clb_syscfg/source/clb_run_dynamic_template_simulation_bat.js"
                },
            ];
        }
        else if (inst) {
            return [
                {
                    name: "pullInTemplateH",
                    moduleName: "/utilities/clb_tool/clb_syscfg/source/clb_run_dynamic_template_clb_h.js"
                },
                {
                    name: "pullInTemplateC",
                    moduleName: "/utilities/clb_tool/clb_syscfg/source/clb_run_dynamic_template_clb_c.js"
                },
                {
                    name: "pullInTemplateSIM",
                    moduleName: "/utilities/clb_tool/clb_syscfg/source/clb_run_dynamic_template_clb_sim.js"
                },
                {
                    name: "pullInTemplateDOT",
                    moduleName: "/utilities/clb_tool/clb_syscfg/source/clb_run_dynamic_template_clb_dot.js"
                },
                {
                    name: "pullInTemplateSH",
                    moduleName: "/utilities/clb_tool/clb_syscfg/source/clb_run_dynamic_template_simulation_sh.js"
                },
            ];
        }
        return [];
    },
    validate            : onValidate,
    // The following line should not be needed, but is here to workaround a bug
    config              : config,
};