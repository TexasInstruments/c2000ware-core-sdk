"use strict";
/*global exports, system*/

let Common   = system.getScript('/utilities/clb_tool/clb_syscfg/source/Common.js');
let logError = Common.logError;

/* Intro splash on GUI */
let longDescription = `The High Level Controller submodule is event-driven and performs a set of actions. It 
provides a data exchange and interrupt mechanism to the CPU. There are 4 registers which can be used for 
basic operations and to modify or set up values for the three Counter blocks.

![Image Missing](../../utilities/clb_tool/clb_syscfg/source/.meta/references/HLC.png)
`;

let longDescriptionSPI = `
This is for simulation only; to configure the SPI buffer for CLB, 
refer to the "Data Exporting Through SPI Buffer" drop-down in the 
CLB module.

Export CLB data through SPI buffer. Data is HLC R0 regiter

![Image Missing](../../utilities/clb_tool/clb_syscfg/source/.meta/references/SPI_Buffer.png)
`

var hlcInputs = Common.allInputsAry;
if (Common.isType1_Type2())
{
    hlcInputs = hlcInputs.concat(Common.altInputsAry);
}

/* Array of Watchdog configurables that are common across device families */
let config = [
    {
        name        : 'hlcDescription',
        longDescription : "This field is for the user to provide a description of this block's logic",
        displayName : 'User Description',
        default     : '',
        multiline   : true
    },
    {
        name        : 'e0',
        description : 'Event 0',
        displayName : 'Event 0 (e0)',
        default     : '0',
        onChange    : onChange,
        options     : hlcInputs
    },
    {
        name        : 'e1',
        description : 'Event 1',
        displayName : 'Event 1 (e1)',
        default     : '0',
        onChange    : onChange,
        options     : hlcInputs
    },
    {
        name        : 'e2',
        description : 'Event 2',
        displayName : 'Event 2 (e2)',
        default     : '0',
        onChange    : onChange,
        options     : hlcInputs
    },
    {
        name        : 'e3',
        description : 'Event 3',
        displayName : 'Event 3 (e3)',
        default     : '0',
        onChange    : onChange,
        options     : hlcInputs
    },
    {
        name        : "setReadOnlyHLC",
        default     : false,
        hidden      : true,
        onChange    : onChangeLock
    }
];

config = config.concat([{
    name: "GROUP_REGINIT",
    displayName: "Register 0-3 Initialization",
    longDescription: `R0-R3 are loaded with initial values during device initialization and simulation initialization.`,
    config: [
        {
            name       : 'R0_init',
            displayName: "R0 Initial Value",
            description: 'Initial value for register R0',
            default    : '0'
        },
        {
            name       : 'R1_init',
            displayName: "R1 Initial Value",
            description: 'Initial value for register R1',
            default    : '0'
        },
        {
            name       : 'R2_init',
            displayName: "R2 Initial Value",
            description: 'Initial value for register R2',
            default    : '0'
        },
        {
            name       : 'R3_init',
            displayName: "R3 Initial Value",
            description: 'Initial value for register R3',
            default    : '0'
        },
    ]
}]);

config = config.concat([{
    name: "GROUP_FIFOINIT",
    displayName: "FIFO Initialization and Refill Values",
    longDescription: `FIFO[0..3] are initial values loaded into the CLB's 4-level pull FIFO during device initialization and simulation 
    initialization. FIFO[A..D] are only used by simulation to represent when the FIFO is refilled (which treats 
    the FIFO as an 8-level pull FIFO)`,
    config: [
        {
            name       : 'FIFO_init_enable',
            displayName: "Pull FIFO Initialization Enable",
            description: `Initializes the CLB pull FIFO with 4 elements; this is also used in the simulation 
            (note that the simulation will always initialize the pull FIFO with the values listed below)`,
            default    : false
        },
        {
            name       : 'FIFO0_init',
            displayName: "Pull FIFO[0] Initial Value",
            description: 'Initial value for index 0 of the HLC FIFO',
            default    : '0'
        },
        {
            name       : 'FIFO1_init',
            displayName: "Pull FIFO[1] Initial Value",
            description: 'Initial value for index 1 of the HLC FIFO',
            default    : '0'
        },
        {
            name       : 'FIFO2_init',
            displayName: "Pull FIFO[2] Initial Value",
            description: 'Initial value for index 2 of the HLC FIFO',
            default    : '0'
        },
        {
            name       : 'FIFO3_init',
            displayName: "Pull FIFO[3] Initial Value",
            description: 'Initial value for index 3 of the HLC FIFO',
            default    : '0'
        },
        {
            name       : 'FIFO_refill_enable',
            displayName: "Pull FIFO Refill Enable (Simulation Only)",
            description: 'Enables the simulation to use the FIFO refill values during the simulation itself',
            default    : false
        },
        {
            name       : 'FIFO0_refill',
            displayName: "(Simulation Only) FIFO[A]",
            description: 'Refill value for index 0 of the HLC FIFO',
            default    : '0'
        },
        {
            name       : 'FIFO1_refill',
            displayName: "(Simulation Only) FIFO[B]",
            description: 'Refill value for index 1 of the HLC FIFO',
            default    : '0'
        },
        {
            name       : 'FIFO2_refill',
            displayName: "(Simulation Only) FIFO[C]",
            description: 'Refill value for index 2 of the HLC FIFO',
            default    : '0'
        },
        {
            name       : 'FIFO3_refill',
            displayName: "(Simulation Only) FIFO[D]",
            description: 'Refill value for index 3 of the HLC FIFO',
            default    : '0'
        },
    ]
}]);

if (Common.isType2())
{
    config = config.concat([{
        name: "GROUP_SPIDATAEXPORT",
        displayName: "Data Exporting Through SPI Buffer (Simulation Only)",
        description: "",
        longDescription: longDescriptionSPI,
        config: [
            {
                name: "spiBufferAccess",
                displayName : "Enable SPI Buffer Access for Simulation",
                description : 'Enable CLB data exporting through SPI buffer.',
                hidden      : false,
                default     : false
            },
            {
                name: "spiBufferLoadTriggerSignal",
                displayName : "SPI Buffer Load Trigger Signal",
                hidden      : false,
                default     : Common.staticSwitchOptions[0].name,
                options     : Common.staticSwitchOptions
            },
            {
                name: "spiBufferR0Shift",
                displayName : "HLC R0 Register Shift Value",
                longDescription: `This value determines which 16 bits of the 32-bit R0 register are 
                exported to the SPI RX buffer (i.e. a value of 1 selects bits 16:1 of the R0 register)`,
                hidden      : false,
                default     : Common.zero_to_16[0].name,
                options     : Common.zero_to_16
            }
        ]
    }]);
}

function onChangeLock (inst, ui)
{
    ui["hlcDescription"].readOnly = inst.setReadOnlyHLC;
    ui["e0"].readOnly = inst.setReadOnlyHLC;
    ui["e1"].readOnly = inst.setReadOnlyHLC;
    ui["e2"].readOnly = inst.setReadOnlyHLC;
    ui["e3"].readOnly = inst.setReadOnlyHLC;
    ui["R0_init"].readOnly = inst.setReadOnlyHLC;
    ui["R1_init"].readOnly = inst.setReadOnlyHLC;
    ui["R2_init"].readOnly = inst.setReadOnlyHLC;
    ui["R3_init"].readOnly = inst.setReadOnlyHLC;
    
    ui["FIFO0_init"].readOnly = inst.setReadOnlyHLC;
    ui["FIFO1_init"].readOnly = inst.setReadOnlyHLC;
    ui["FIFO2_init"].readOnly = inst.setReadOnlyHLC;
    ui["FIFO3_init"].readOnly = inst.setReadOnlyHLC;
    
    ui["spiBufferAccess"].readOnly = inst.setReadOnlyHLC;
    ui["spiBufferLoadTriggerSignal"].readOnly = inst.setReadOnlyHLC;
    ui["spiBufferR0Shift"].readOnly = inst.setReadOnlyHLC;
}

/**
 * Change notification function
 *
 * @param inst - Watchdog instance to be validated
 * @param ui   - The user interface object
 */
function onChange(inst, ui)
{
    ui.program0.hidden = (inst.e0 == '0');
    ui.program1.hidden = (inst.e1 == '0');
    ui.program2.hidden = (inst.e2 == '0');
    ui.program3.hidden = (inst.e3 == '0');
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
}

function moduleInstances(inst)
{
    var numEvents = 0;
    if(inst.e0 != '0')
    {
        numEvents++;
    }
    if(inst.e1 != '0')
    {
        numEvents++;
    }
    if(inst.e2 != '0')
    {
        numEvents++;
    }
    if(inst.e3 != '0')
    {
        numEvents++;
    }

    let instrs = [
        {
            moduleName: "/utilities/clb_tool/clb_syscfg/source/HLC_Program",
            name      : "program0",
            displayName: "HLC Program 0",
            collapsed : false,
            hidden    : true,
            args: {
                setReadOnlyHLCProg: inst.setReadOnlyHLC,
                numEvents: numEvents
            }
        },
        {
            moduleName: "/utilities/clb_tool/clb_syscfg/source/HLC_Program",
            name      : "program1",
            displayName: "HLC Program 1",
            collapsed : false,
            hidden    : true,
            args: {
                setReadOnlyHLCProg: inst.setReadOnlyHLC,
                numEvents: numEvents
            }
        },
        {
            moduleName: "/utilities/clb_tool/clb_syscfg/source/HLC_Program",
            name      : "program2",
            displayName: "HLC Program 2",
            collapsed : false,
            hidden    : true,
            args: {
                setReadOnlyHLCProg: inst.setReadOnlyHLC,
                numEvents: numEvents
            }
        },
        {
            moduleName: "/utilities/clb_tool/clb_syscfg/source/HLC_Program",
            name      : "program3",
            displayName: "HLC Program 3",
            collapsed : false,
            hidden    : true,
            args: {
                setReadOnlyHLCProg: inst.setReadOnlyHLC,
                numEvents: numEvents
            }
        },
    ];

    return instrs;
}

// Define the common/portable base Watchdog
exports = {
    displayName         : 'HLC',
    description         : 'High Level Controller and Sequencer',
    defaultInstanceName : 'HLC_',
    longDescription     : longDescription,
    config              : config,
    validate            : validate,
    moduleInstances     : moduleInstances,
};