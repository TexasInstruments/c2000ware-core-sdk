//#############################################################################
//
// erad.js
//
// This file contains addresses and offsets for all ERAD registers
//
//#############################################################################

console.log("Including erad.js \n");

//
// ERAD Global Registers Base Address
//
var ERAD_GLOBAL_BASE  =  0x5E800;

//
// ERAD Global Register Offsets
//
let ERAD_Global_Regs_Offset = {
    "GLBL_EVENT_STAT"  : 0x0,    //  Global Event Status Register
    "GLBL_HALT_STAT"   : 0x2,    //  Global Halt Status Register
    "GLBL_ENABLE"      : 0x4,    //  Global Enable Register
    "GLBL_CTM_RESET"   : 0x6,    //  Global Counter Reset
    "GLBL_OWNER"       : 0xA,    //  Global Ownership
};

//
// ERAD Hardware Breakpoint Register Base Addresses
//
let ERAD_HWBP_BASE = [
    0x5E900,
    0x5E908,
    0x5E910,
    0x5E918,
    0x5E920,
    0x5E928,
    0x5E930,
    0x5E938,
];

//
// ERAD Hardware Breakpoint Register Offsets
//
let ERAD_HWBP_Regs_Offset = {
    "HWBP_MASK"     : 0x0,     //  HWBP Mask Register
    "HWBP_REF"      : 0x2,     //  HWBP Reference Register
    "HWBP_CLEAR"    : 0x4,     //  HWBP Clear Register
    "HWBP_CNTL"     : 0x6,     //  HWBP Control Register
    "HWBP_STATUS"   : 0x7,     //  HWBP Status Register
};

//
// ERAD Counter Register Base Addresses
//
let ERAD_COUNTER_BASE = [
    0x5E980,
    0x5E990,
    0x5E9A0,
    0x5E9B0,
];

//
// ERAD Counter Register Offsets
//
let ERAD_CTM_Regs_Offset = {
    "CTM_CNTL"           : 0x0,     //  Counter Control Register
    "CTM_STATUS"         : 0x1,     //  Counter Status Register
    "CTM_REF"            : 0x2,     //  Counter Reference Register
    "CTM_COUNT"          : 0x4,     //  Counter Current Value Register
    "CTM_MAX_COUNT"      : 0x6,     //  Counter Max Count Value Register
    "CTM_INPUT_SEL"      : 0x8,     //  Counter Input Select Register
    "CTM_CLEAR"          : 0x9,     //  Counter Clear Register
    "CTM_INPUT_SEL_2"    : 0xA,     //  Counter Input Select Extension Register
};

//
// ERAD Owner
//
let ERAD_Owner = {
    "ERAD_OWNER_NOOWNER"     : 0,     //! No owner
    "ERAD_OWNER_APPLICATION" : 1,     //! Application owned
    "ERAD_OWNER_DEBUGGER"    : 2,     //! Debugger owned
}

module.exports = {
    ERAD_GLOBAL_BASE,
    ERAD_Global_Regs_Offset,
    ERAD_HWBP_BASE,
    ERAD_HWBP_Regs_Offset,
    ERAD_COUNTER_BASE,
    ERAD_CTM_Regs_Offset,
    ERAD_Owner
};

//
// End of File
//