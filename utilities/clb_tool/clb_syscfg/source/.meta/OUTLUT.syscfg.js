"use strict";
/*global exports, system*/

let Common   = system.getScript('/utilities/clb_tool/clb_syscfg/source/Common.js');
let logError = Common.logError;

/* Intro splash on GUI */
let longDescription = `
The output LUT is a 3-input lookup table submodule capable of realizing any combinatorial Boolean 
equation of up to three inputs. Each of the eight OUTLUT blocks corresponds with one of the tile's 
eight outputs.

![Image Missing](../../utilities/clb_tool/clb_syscfg/source/.meta/references/OUTLUT.png)
`;

/* Array of Watchdog configurables that are common across device families */
let config = [
    {
        name        : 'outlutDescription',
        longDescription : "This field is for the user to provide a description of this block's logic",
        displayName : 'User Description',
        default     : '',
        multiline   : true
    },
    {
        name        : 'eqn',
        displayName : "Output Logic Equation",
        description : 'Boolean equation using the variables i2, i1, and i0 for the OUTLUT output.',
        default     : ''
    },
    {
        name        : 'i0',
        displayName : 'Input 0',
        default     : '0',
        options     : Common.allInputsAry
    },
    {
        name        : 'i1',
        displayName : 'Input 1',
        default     : '0',
        options     : Common.allInputsAry
    },
    {
        name        : 'i2',
        displayName : 'Input 2',
        default     : '0',
        options     : Common.allInputsAry
    },
    {
        name        : "setReadOnlyOutLut",
        default     : false,
        hidden      : true,
        onChange    : onChangeLock
    }
];

function onChangeLock (inst, ui)
{
    ui["outlutDescription"].readOnly = inst.setReadOnlyOutLut;
    ui["eqn"].readOnly = inst.setReadOnlyOutLut;
    ui["i0"].readOnly = inst.setReadOnlyOutLut;
    ui["i1"].readOnly = inst.setReadOnlyOutLut;
    ui["i2"].readOnly = inst.setReadOnlyOutLut;
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
    var expr = inst.eqn.replace(/i0/g, '').replace(/i1/g, '').replace(/i2/g, '')

    if ((!validate_equation(inst.eqn)) || ((expr != "") && (hasNum.test(expr))))
    {
        Common.logError(vo, inst, 'eqn', 'Invalid equation');
    }*/
    if (!validate_equation(inst.eqn))
    {
        Common.logError(vo, inst, 'eqn', 'Invalid equation');
    }

    let inputs = Common.inputs['OUTLUT'];
    for (let i = 0; i < inputs.length; i++) {
        let input = inputs[i];
        if (inst.eqn.match(new RegExp(input)) &&
            (inst[input] == '0' || inst[input] == '1')) {
            Common.logWarning(vo, inst, ['eqn', input],
                            'Equation uses a constant value input');
        }
    }
    Common.validateNames(inst, vo);
}

// Determine if the OUTLUT equation is a valid function of i0-i3
function validate_equation(expr)
{
    let i0,i1,i2;
    try        { eval(expr);   }
    catch(err) { return false; }

    return true;
}

// Define the common/portable base Watchdog
exports = {
    displayName         : 'OUTLUT',
    description         : 'OUTLUT',
    defaultInstanceName : 'OUTLUT_',
    longDescription     : longDescription,
    config              : config,
    validate            : validate,
};