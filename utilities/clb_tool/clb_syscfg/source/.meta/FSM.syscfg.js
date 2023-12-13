"use strict";
/*global exports, system*/

let Common   = system.getScript("/utilities/clb_tool/clb_syscfg/source/Common.js");
let logError = Common.logError;

/* Intro splash on GUI */
let longDescription = `The Finite State Machine submodule can be used as a single four-state FSM 
or two independent two-state FSMs. It generates two state outputs and one combinational output. 
When not used as a state machine, the FSM submodule can function as a 4-input LUT.

_**FSM Block**_

![Image Missing](../../utilities/clb_tool/clb_syscfg/source/.meta/references/FSM.png)

_**FSM LUT Block**_

![Image Missing](../../utilities/clb_tool/clb_syscfg/source/.meta/references/FSM_LUT.png)
`;

/* Array of Watchdog configurables that are common across device families */
let config = [
    {
        name        : 'fsmDescription',
        longDescription : "This field is for the user to provide a description of this block's logic",
        displayName : 'User Description',
        default     : '',
        multiline   : true
    },
    {
        name        : "eqn_out",
        displayName : 'LUT Output Equation',
        description : 'Boolean equation using the variables e1, e0, s1, s0, xe0, and xe1 for the LUT output.',
        default     : ''
    },
    {
        name        : "eqn_s0",
        displayName : 'State 0 Output Equation (s0)',
        description : 'Boolean equation using the variables e1, e0, s1, and s0 for the S0 output.',
        default     : ''
    },
    {
        name        : "eqn_s1",
        displayName : 'State 1 Output Equation (s1)',
        description : 'Boolean equation using the variables e1, e0, s1, and s0 for the S1 output.',
        default     : ''
    },
    {
        name        : "e0",
        displayName : 'External Input 0 (e0)',
        default     : '0',
        options     : Common.allInputsAry
    },
    {
        name        : "e1",
        displayName : 'External Input 1 (e1)',
        default     : '0',
        options     : Common.allInputsAry
    },
    {
        name        : "xe0",
        displayName : 'Extra External Input 0',
        default     : '0',
        options     : Common.allInputsAry
    },
    {
        name        : "xe1",
        displayName : 'Extra External Input 1',
        default     : '0',
        options     : Common.allInputsAry
    },
    {
        name        : "setReadOnlyFSM",
        default     : false,
        hidden      : true,
        onChange    : onChangeLock
    }
];

function onChangeLock (inst, ui)
{
    ui["fsmDescription"].readOnly = inst.setReadOnlyFSM;
    ui["eqn_out"].readOnly = inst.setReadOnlyFSM;
    ui["eqn_s0"].readOnly = inst.setReadOnlyFSM;
    ui["eqn_s1"].readOnly = inst.setReadOnlyFSM;
    ui["e0"].readOnly = inst.setReadOnlyFSM;
    ui["e1"].readOnly = inst.setReadOnlyFSM;
    ui["xe0"].readOnly = inst.setReadOnlyFSM;
    ui["xe1"].readOnly = inst.setReadOnlyFSM;
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
    var expr = inst.eqn_out.replace(/e0/g, '').replace(/e1/g, '').replace(/s0/g, '').replace(/s1/g, '').replace(/xe0/g, '').replace(/xe1/g, '')
    if ((!validate_out_equation(inst.eqn_out)) || ((expr != "") && (hasNum.test(expr))))
    {
        Common.logError(vo, inst, 'eqn_out', 'Invalid equation');
    }

    expr = inst.eqn_s0.replace(/e0/g, '').replace(/e1/g, '').replace(/s0/g, '').replace(/s1/g, '')
    if ((!validate_equation(inst.eqn_s0)) || ((expr != "") && (hasNum.test(expr))))
    {
        Common.logError(vo, inst, 'eqn_s0', 'Invalid equation');
    }

    expr = inst.eqn_s1.replace(/e0/g, '').replace(/e1/g, '').replace(/s0/g, '').replace(/s1/g, '')
    if ((!validate_equation(inst.eqn_s1)) || ((expr != "") && (hasNum.test(expr))))
    {
        Common.logError(vo, inst, 'eqn_s1', 'Invalid equation');
    }*/
    if (!validate_out_equation(inst.eqn_out))
    {
        Common.logError(vo, inst, 'eqn_out', 'Invalid equation');
    }
    if (!validate_equation(inst.eqn_s0))
    {
        Common.logError(vo, inst, 'eqn_s0', 'Invalid equation');
    }
    if (!validate_equation(inst.eqn_s1))
    {
        Common.logError(vo, inst, 'eqn_s1', 'Invalid equation');
    }

	if (((inst.eqn_out.includes("xe0")) && (inst.eqn_out.includes("s0")))
		|| ((inst.eqn_out.includes("xe1")) && (inst.eqn_out.includes("s1")))){
		Common.logError(vo, inst, ['eqn_out'], 'Equation uses both (xe0 and s0) or (xe1 and s1) at the same time');
	}
	if ((inst.eqn_s0.includes("xe0")) || (inst.eqn_s0.includes("xe1"))) {
		Common.logError(vo, inst, ['eqn_s0'], 'S0 equation can not use xe0 or xe1 inputs');
	}
	if ((inst.eqn_s1.includes("xe0")) || (inst.eqn_s1.includes("xe1")))	 {
		Common.logError(vo, inst, ['eqn_s1'], 'S1 equation can not use xe0 or xe1 inputs');
	}

    let inputs = Common.inputs['FSM'];
    for (let i = 0; i < inputs.length; i++) {
        let input = inputs[i];
		let expr_val = new RegExp("\\b" + input + "\\b");
        if (inst.eqn_out.match(expr_val) && (inst[input] == '0' || inst[input] == '1')) {
            Common.logWarning(vo, inst, ['eqn_out', input], 'Equation uses a constant value input');
        }
        if (inst.eqn_s0.match(expr_val) && (inst[input] == '0' || inst[input] == '1')) {
            Common.logWarning(vo, inst, ['eqn_s0', input], 'Equation uses a constant value input');
        }
        if (inst.eqn_s1.match(expr_val) && (inst[input] == '0' || inst[input] == '1')) {
            Common.logWarning(vo, inst, ['eqn_s1', input], 'Equation uses a constant value input');
        }
		if(Common.which_instance(inst)== '0') {
			if ((inst[input] == 'LUT_1.OUT') || (inst[input] == 'LUT_2.OUT') ||
				(inst[input] == 'FSM_0.OUT') || (inst[input] == 'FSM_1.OUT') || (inst[input] == 'FSM_2.OUT'))
			{
				Common.logWarning(vo, inst, [input],
                'Invalid connection for this FSM instance');
			}
		}
		if(Common.which_instance(inst)==1) {
			if ((inst[input] == 'LUT_2.OUT') ||	(inst[input] == 'FSM_1.OUT') || (inst[input] == 'FSM_2.OUT'))
			{
				Common.logWarning(vo, inst, [input],
				'Invalid connection for this FSM instance');
			}
		}
		if(Common.which_instance(inst)==2) {
			if ((inst[input] == 'FSM_2.OUT'))
			{
				Common.logWarning(vo, inst, [input],
				'Invalid connection for this FSM instance');
			}
		}
    }

    Common.validateNames(inst, vo);
}

// Determine if the State equation is a valid function of e1,e0,s1,s0
function validate_equation(expr)
{
    let e1,e0,s1,s0;
    try        { eval(expr);   }
    catch(err) { return false; }

    return true;
}

function validate_out_equation(expr)
{
    let e1,e0,s1,s0, xe0, xe1;
    try        { eval(expr);   }
    catch(err) { return false; }

    return true;
}

// Define the common/portable base Watchdog
exports = {
    displayName         : "FSM",
    description         : "FSM",
    defaultInstanceName : "FSM_",
    longDescription     : longDescription,
    config              : config,
    validate            : validate,
};
