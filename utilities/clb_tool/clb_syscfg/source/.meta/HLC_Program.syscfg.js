"use strict";
/*global exports, system*/

let Common   = system.getScript('/utilities/clb_tool/clb_syscfg/source/Common.js');
let logError = Common.logError;

/* Intro splash on GUI */
let longDescription = `The HLC will execute these instructions upon on an event trigger (up to 8 instructions). Possible instructions are included below:

Instruction | Description
--- |---
ADD {Src} {Dest}        |   This instruction performs a 32-bit unsigned addition, where {Dest} = {Dest} + {Src}. The {Src} can be R0, R1, R2, R3, C0, C1, or C2. The {Dest} can only be R0, R1, R2, or R3.
INTR [6-bit constant]   |   This instruction will flag an interrupt through the CPU interface. The 6-bit constant is stored in the interrupt flag register CLB_INTR_TAG_REG.
MOV {Src} {Dest}        |   This instruction moves {Src} to {Dest}. Both {Src} and {Dest} can be any of R0, R1, R2, R3, C0, C1, or C2.
MOV_T1 {Src} {Dest}     |   This instruction moves {Src} to the Match1 register of the {Dest} counter. {Src} can be any of the registers R0, R1, R2, R3, or the counter values associated with C0, C1, or C2. {Dest} is the Match1 register of any of the counters C0, C1, or C2.
MOV_T2 {Src} {Dest}     |   This instruction moves {Src} to the Match2 register of the {Dest} counter. {Src} can be any of the registers R0, R1, R2, R3, or the counter values associated with C0, C1, or C2. {Dest} is the Match2 register of any of the counters C0, C1, or C2.
PULL {Dest}             |   This instruction transfers data from the data exchange pull memory buffer in the CPU interface to the {Dest} register. {Dest} can be any of R0, R1, R2, R3, C0, C1, or C2.
PUSH {Src}              |   This instruction transfers data from {Src} to the data exchange push memory buffer in the CPU interface. {Src} can be any of R0, R1, R2, R3, C0, C1, or C2.
SUB {Src} {Dest}        |   This instruction performs a 32-bit unsigned subtraction, where {Dest} = {Dest} - {Src}. The {Src} can be R0, R1, R2, R3, C0, C1, or C2. The {Dest} can only be R0, R1, R2, or R3.
`;

/* The up to 8 instructions that can be configured for an event program */
let config = [
    { name: 'instruct0', displayName: "Instruction 0", default: '', hidden: false, onChange: onChange },
    { name: 'instruct1', displayName: "Instruction 1", default: '', hidden: true,  onChange: onChange },
    { name: 'instruct2', displayName: "Instruction 2", default: '', hidden: true,  onChange: onChange },
    { name: 'instruct3', displayName: "Instruction 3", default: '', hidden: true,  onChange: onChange },
    { name: 'instruct4', displayName: "Instruction 4", default: '', hidden: true,  onChange: onChange },
    { name: 'instruct5', displayName: "Instruction 5", default: '', hidden: true,  onChange: onChange },
    { name: 'instruct6', displayName: "Instruction 6", default: '', hidden: true,  onChange: onChange },
    { name: 'instruct7', displayName: "Instruction 7", default: '', hidden: true,  onChange: onChange },
    {
        name        : "setReadOnlyHLCProg",
        default     : false,
        hidden      : true,
        onChange    : onChangeLock
    },
    {
        name        : "numEvents",
        default     : 0,
        hidden      : true,
    }
];

function onChangeLock (inst, ui)
{
    ui["instruct0"].readOnly = inst.setReadOnlyHLCProg;
    ui["instruct1"].readOnly = inst.setReadOnlyHLCProg;
    ui["instruct2"].readOnly = inst.setReadOnlyHLCProg;
    ui["instruct3"].readOnly = inst.setReadOnlyHLCProg;
    ui["instruct4"].readOnly = inst.setReadOnlyHLCProg;
    ui["instruct5"].readOnly = inst.setReadOnlyHLCProg;
    ui["instruct6"].readOnly = inst.setReadOnlyHLCProg;
    ui["instruct7"].readOnly = inst.setReadOnlyHLCProg;
}

/**
 * Validate this module's configuration
 *
 * @param inst - HLC Program instance that was changed
 * @param ui   - The UI object for changing ui poroperties
 */
function onChange(inst, ui) {
    let first_blank = 0;

    for (first_blank=0; first_blank < 8; ++first_blank) {
        let field = 'instruct'+first_blank;
        ui[field].hidden = false;
        if (inst[field] == '') break;
    }

    for (let i=first_blank+1; i < 8; ++i)
    {
        let field = 'instruct'+i;
        if (inst[field] == '') { ui[field].hidden = true; }
    }
}

/**
 * Validate this module's configuration
 *
 * @param inst       - Watchdog instance to be validated
 * @param vo         - Issue reporting object
 */
function validate(inst, vo)
{
    Common.validateNames(inst, vo);

    for (let i=0 ; i < 8; ++i) {
        let field = 'instruct'+i;
        instruction_validate(inst[field], inst, field, vo, i)
    }
}

function instruction_validate(instruction, inst, field, vo, i)
{
    if (instruction == '') { return true; }
    let re  = /\s*(\S+)\s*(.*)/i
    let found = instruction.match(re);

    let opcode   = found[1].toUpperCase();
    let operands = found[2].toUpperCase();

    operands = operands.split(',');
    for (let i = 0; i < operands.length; i++) {
        operands[i] = operands[i].trim();
    }

    let registers = ['R0', 'R1', 'R2', 'R3'];
    let counters  = ['C0', 'C1', 'C2'];
    let either    = registers.concat(counters);
    let itype;

    switch (opcode) {
		case 'MOV':
           itype = [ 2, either, either ];
           break;

        case 'ADD':
        case 'SUB':
           itype = [ 2, either, registers ];
           break;

        case 'MOV_T1':
        case 'MOV_T2':
           itype = [ 2, either, counters ];
           break;

        case 'PUSH':
        case 'PULL':
           itype = [ 1, either, 0 ]
           break;

        case 'INTR':
           if (operands.length != 1) {
               logError(vo, inst, field,
                   'Expected 1 operands. ' + operands.length + ' operands found.');
               return;
           }
           let opval = parseInt(operands[0]);
           if (opval < 0 || opval > 63 || isNaN(opval)) {
               logError(vo, inst, field,
                   'The operand for INTR must be a 6 bit value [0..63]');
               return;
           }
           return;

        default:
            logError(vo, inst, field, 'Invalid operation');
            return;
    }

    if (operands.length != itype[0]) {
        logError(vo, inst, field,
            'Expected ' + itype[0] +' operands. ' + operands.length + ' operands found.');
        return;
    }

    if (itype[0] >= 1 && !itype[1].includes(operands[0])) {
        logError(vo, inst, field, 'Src Operand is invalid');
        return;
    }

    if (itype[0] >= 2 && !itype[2].includes(operands[1])) {
        logError(vo, inst, field, 'Dest Operand is invalid');
        return;
    }


    let fieldPrev = 'instruct' + (i-1);
    var foundPrev;
    var opcodePrev;

    if(Common.isType0_Type1() && ((inst[fieldPrev]) && (inst.numEvents > 1)))
    {
        foundPrev = inst[fieldPrev].match(re);
        opcodePrev   = foundPrev[1].toUpperCase();

        if(((opcode == 'PUSH') && inst[fieldPrev].includes("PULL")) || ((opcode == 'PULL') && inst[fieldPrev].includes("PUSH")))
        {
            logError(vo, inst, field, "If more than one event is enabled, a " + opcodePrev + " followed by a " + opcode + " instruction will not work; a dummy instruction is required between the two instructions")
        }
    }
}

// Define the common/portable base Watchdog
exports = {
    displayName         : 'HLCProgram',
    description         : 'High Level Controller Event Program',
    defaultInstanceName : 'HLCP_',
    longDescription     : longDescription,
    config              : config,
    validate            : validate
};