"use strict";
/*global exports, system*/

let Common   = system.getScript('/utilities/clb_tool/clb_syscfg/source/Common.js');
let logError = Common.logError;

/* Intro splash on GUI */
let longDescription = `The LUT4 submodule has 4-input look-up table functionality and is capable of 
realizing any combinatorial Boolean equation of up to four inputs.

![Image Missing](../../utilities/clb_tool/clb_syscfg/source/.meta/references/LUT.png)
`;

/* Array of Watchdog configurables that are common across device families */
let config = [
    {
        name        : 'lutDescription',
        longDescription : "This field is for the user to provide a description of this block's logic",
        displayName : 'LUT User Description',
        default     : '',
        hidden      : false,
        multiline   : true,
        readOnly    : false
    },
    {
        name        : 'eqn',
        displayName : 'Logic Equation',
        description : 'Boolean equation using the variables i3, i2, i1, and i0 for the LUT output.',
        hidden      : false,
        default     : ''
    },
    {
        name        : 'i0',
        displayName : 'Input 0',
        default     : '0',
        hidden      : false,
        options     : Common.allInputsAry
    },
    {
        name        : 'i1',
        displayName : 'Input 1',
        default     : '0',
        hidden      : false,
        options     : Common.allInputsAry
    },
    {
        name        : 'i2',
        displayName : 'Input 2',
        default     : '0',
        hidden      : false,
        options     : Common.allInputsAry
    },
    {
        name        : 'i3',
        displayName : 'Input 3',
        default     : '0',
        hidden      : false,
        options     : Common.allInputsAry
    },
    {
        name        : "setReadOnlyLut",
        default     : false,
        hidden      : true,
        onChange    : onChangeLock
    }
];

function onChangeLock (inst, ui)
{
    ui["lutDescription"].readOnly = inst.setReadOnlyLut;
    ui["eqn"].readOnly = inst.setReadOnlyLut;
    ui["i0"].readOnly = inst.setReadOnlyLut;
    ui["i1"].readOnly = inst.setReadOnlyLut;
    ui["i2"].readOnly = inst.setReadOnlyLut;
    ui["i3"].readOnly = inst.setReadOnlyLut;
}

/**
 * Validate this module's configuration
 *
 * @param inst       - Watchdog instance to be validated
 * @param validation - Issue reporting object
 */
function validate(inst, vo)
{
    //Used to check if numbers are used in expression; removing because LUT can use constants since it's just programming the outputs of the logic equation
    /*var hasNum = /\d/;
    var expr = inst.eqn.replace(/i0/g, '').replace(/i1/g, '').replace(/i2/g, '').replace(/i3/g, '')

    if ((!validate_equation(inst.eqn)) || ((expr != "") && (hasNum.test(expr))))
    {
        Common.logError(vo, inst, 'eqn', 'Invalid equation');
    }*/
    if (!validate_equation(inst.eqn))
    {
        Common.logError(vo, inst, 'eqn', 'Invalid equation');
    }

    let inputs = Common.inputs['LUT'];
    for (let i = 0; i < inputs.length; i++) {
        let input = inputs[i];
        if (inst.eqn.match(new RegExp(input)) &&
            (inst[input] == '0' || inst[input] == '1')) {
            Common.logWarning(vo, inst, ['eqn', input],
                            'Equation uses a constant value input');
        }
		if(Common.which_instance(inst)== '0') {
				if ((inst[input] == 'LUT_0.OUT') || (inst[input] == 'LUT_1.OUT') || (inst[input] == 'LUT_2.OUT') ||
					(inst[input] == 'FSM_0.OUT') || (inst[input] == 'FSM_1.OUT') || (inst[input] == 'FSM_2.OUT'))				
				{
					Common.logWarning(vo, inst, [input],
                    'Invalid connection for this LUT instance');
				}
		}
		if(Common.which_instance(inst)==1) {
				if ((inst[input] == 'LUT_1.OUT') || (inst[input] == 'LUT_2.OUT') ||
					(inst[input] == 'FSM_1.OUT') || (inst[input] == 'FSM_2.OUT'))				
				{
					Common.logWarning(vo, inst, [input],
                    'Invalid connection for this LUT instance');
				}
		}
		if(Common.which_instance(inst)==2) {
				if ((inst[input] == 'LUT_2.OUT') ||
					(inst[input] == 'FSM_2.OUT'))				
				{
					Common.logWarning(vo, inst, [input],
                    'Invalid connection for this LUT instance');
				}
		}
    }

    Common.validateNames(inst, vo);
}

// Determine if the LUT equation is a valid function of i0-i3
function validate_equation(expr)
{
    let i0,i1,i2,i3;
    try        { eval(expr);   }
    catch(err) { return false; }

    return true;
}

// Define the common/portable base Watchdog
exports = {
    displayName         : 'LUT',
    description         : 'LUT',
    defaultInstanceName : 'LUT_',
    longDescription     : longDescription,
    config              : config,
    hidden              : false,
    validate            : validate,
};