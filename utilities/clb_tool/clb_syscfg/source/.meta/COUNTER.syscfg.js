"use strict";
/*global exports, system*/

let Common   = system.getScript('/utilities/clb_tool/clb_syscfg/source/Common.js');
let logError = Common.logError;

/* Intro splash on GUI */
let longDescription = `The Counter submodule can be configured either as an adder, a counter, or a shifter. 
It has a dedicated EVENT input, which can trigger an addition, subtraction or shift operation, or load 
data into the counter register. Match values can be used as inputs into other submodules.

![Image Missing](../../utilities/clb_tool/clb_syscfg/source/.meta/references/Counter.png)
`;

/* Array of Watchdog configurables that are common across device families */
var config = [
    {
        name        : 'counterDescription',
        longDescription : "This field is for the user to provide a description of this block's logic",
        displayName : 'User Description',
        default     : '',
        multiline   : true
    },
    {
        name       : 'reset',
        displayName: "Reset",
        description: 'Reset the counter to 0 on next clock cycle (triggers low to high)',
        default    : '0',
        options    : Common.allInputsAry
    },
    {
        name       : 'event',
        displayName: "Event Trigger",
        description: 'Trigger actions in the counter.',
        default    : '0',
        options    : Common.allInputsAry
    },
    {
        name       : 'mode0',
        displayName: "Counter Enable",
        description: 'Enables Counting when set to 1',
        default    : '0',
        options    : Common.allInputsAry
    },
    {
        name       : 'mode1',
        displayName: "Direction",
        description: 'Controls counting direction. Counts up when set to 1 and counts down when set to 0.',
        default    : '0',
        options    : Common.allInputsAry
    },
    {
        name       : 'match1_val',
        displayName: "Match Reference 1",
        description: 'Sets the value of the Match reference 1 register.',
        default    : '0'
    },
    {
        name       : 'match2_val',
        displayName: "Match Reference 2",
        description: 'Sets the value of the Match reference 2 register.',
        default    : '0'
    },
    {
        name       : 'event_load_val',
        displayName: "Event Load Value",
        description: 'Sets the value of the event load value register.',
        default    : '0'
    },
    {
        name       : 'action',
        displayName: "Counter Event Action",
        description: 'What action should be taken on an event trigger?',
        default    : 'None',
        options    :
        [
            { name: "None"},
            { name: "Load"},
            { name: "Add"},
            { name: "Subtract"},
            { name: "Shift Left"},
            { name: "Shift Right"}
        ]
    },
    {
        name        : "setReadOnlyCounter",
        default     : false,
        hidden      : true,
        onChange    : onChangeLock
    }
];

if (Common.isType1_Type2())
{
    config = config.concat([
        {
            name       : 'serializer_en',
            displayName : 'Enable serializer mode',
            description: 'Enable serializer mode.',
            default    : false
        },
        {
            name: "GROUP_SERIALIZER",
            displayName: "Serializer Mode",
            longDescription: "When the counter is in serializer mode, it no longer operates as a counter. The " +
                         "counter will operate as a shift register",
            config: [
                {
                    name       : 'lfsr_en',
                    displayName : 'Enable LFSR mode',
                    description: 'Enable linear feedback shift register mode.',
                    default    : false
                },
                {
                    name       : 'match1_tap_en',
                    displayName : 'Enable Match Reference 1 tap output',
                    description: `Enables tapping of a specific bit in the counter value and outputing the result as the Match Reference 1 signal.`,
                    default    : false
                },
                {
                    name       : 'match1_tap_sel',
                    displayName : 'Counter bit position for Match Reference 1 tap',
                    description: 'Select the bit position in the counter register to be taped and used as Match Reference 1 signal',
                    default    : 0,
                    options    : Common.zero_to_31
                },
                {
                    name       : 'match2_tap_en',
                    displayName : 'Enable Match Reference 2 tap output',
                    description: `Enables tapping of a specific bit in the counter value and outputing the result as the Match Reference 2 signal.`,
                    default    : false
                },
                {
                    name       : 'match2_tap_sel',
                    displayName : 'Counter bit position for Match Reference 2 tap',
                    description: 'Select the bit position in the counter register to be taped and used as Match Reference 2 signal',
                    default    : 0,
                    options    : Common.zero_to_31
                },
                
            ]
        },
        

    ]);
}

function onChangeLock (inst, ui)
{
    ui["counterDescription"].readOnly = inst.setReadOnlyCounter;
    ui["reset"].readOnly = inst.setReadOnlyCounter;
    ui["event"].readOnly = inst.setReadOnlyCounter;
    ui["mode0"].readOnly = inst.setReadOnlyCounter;
    ui["mode1"].readOnly = inst.setReadOnlyCounter;
    ui["match1_val"].readOnly = inst.setReadOnlyCounter;
    ui["match2_val"].readOnly = inst.setReadOnlyCounter;
    ui["event_load_val"].readOnly = inst.setReadOnlyCounter;
    ui["action"].readOnly = inst.setReadOnlyCounter;

    if(Common.isType1_Type2())
    {
        ui["serializer_en"].readOnly = inst.setReadOnlyCounter;
        ui["lfsr_en"].readOnly = inst.setReadOnlyCounter;
        ui["match1_tap_en"].readOnly = inst.setReadOnlyCounter;
        ui["match1_tap_sel"].readOnly = inst.setReadOnlyCounter;
        ui["match2_tap_en"].readOnly = inst.setReadOnlyCounter;
        ui["match2_tap_sel"].readOnly = inst.setReadOnlyCounter;
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
    if (inst.action == 'None' && inst.event != '0')
       Common.logError(vo, inst, ['action', 'event'],
                  'The event input must be constant 0 for action to be None');

    if ((inst.match1_val > 0xFFFFFFFF) || (inst.match1_val < -2147483648))
       Common.logError(vo, inst, ['match1_val'],
                  'Match1 Value should be a 32 bit number');
    
	if ((inst.match2_val > 0xFFFFFFFF) || (inst.match2_val < -2147483648))
       Common.logError(vo, inst, ['match2_val'],
                  'Match2 Value should be a 32 bit number');	
    
	if ((inst.event_load_val > 0xFFFFFFFF) || (inst.event_load_val < -2147483648))
       Common.logError(vo, inst, ['event_load_val'],
                  'Event Load Value should be a 32 bit number');					  
    
	Common.validateNames(inst, vo);
}

// Define the common/portable base Watchdog
exports = {
    displayName         : 'COUNTER',
    description         : 'COUNTER',
    defaultInstanceName : 'COUNTER',
    longDescription     : longDescription,
    config              : config,
    validate            : validate,
    defaultInstanceName : 'COUNTER_',
};
