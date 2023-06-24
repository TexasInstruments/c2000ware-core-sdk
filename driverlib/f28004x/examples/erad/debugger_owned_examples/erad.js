//#############################################################################
//
// erad.js
//
// This file contains addresses and offsets for all ERAD registers
//
//#############################################################################

print("Including erad.js \n");

//
// ERAD Global Registers Base Address
//
var EradGlobalRegs      =  0x5E800;

//
// ERAD Global Register Offsets
//
var GLBL_EVENT_STAT              =  0x0;     //  Global Event Status Register
var GLBL_HALT_STAT               =  0x2;     //  Global Halt Status Register
var GLBL_ENABLE                  =  0x4;     //  Global Enable Register
var GLBL_CTM_RESET               =  0x6;     //  Global Counter Reset
var GLBL_OWNER                   =  0xA;     //  Global Ownership

//
// ERAD Hardware Breakpoint Register Base Addresses
//
var EradHWBP1Regs       =  0x5E900;
var EradHWBP2Regs       =  0x5E908;
var EradHWBP3Regs       =  0x5E910;
var EradHWBP4Regs       =  0x5E918;
var EradHWBP5Regs       =  0x5E920;
var EradHWBP6Regs       =  0x5E928;
var EradHWBP7Regs       =  0x5E930;
var EradHWBP8Regs       =  0x5E938;

//
// ERAD Hardware Breakpoint Register Offsets
//
var HWBP_MASK                    =  0x0;     //  HWBP Mask Register
var HWBP_REF                     =  0x2;     //  HWBP Reference Register
var HWBP_CLEAR                   =  0x4;     //  HWBP Clear Register
var HWBP_CNTL                    =  0x6;     //  HWBP Control Register
var HWBP_STATUS                  =  0x7;     //  HWBP Status Register

//
// ERAD Counter Register Base Addresses
//
var EradCounter1Regs    =  0x5E980;
var EradCounter2Regs    =  0x5E990;
var EradCounter3Regs    =  0x5E9A0;
var EradCounter4Regs    =  0x5E9B0;

//
// ERAD Counter Register Offsets
//
var CTM_CNTL                     =  0x0;     //  Counter Control Register
var CTM_STATUS                   =  0x1;     //  Counter Status Register
var CTM_REF                      =  0x2;     //  Counter Reference Register
var CTM_COUNT                    =  0x4;     //  Counter Current Value Register
var CTM_MAX_COUNT                =  0x6;     //  Counter Max Count Value
                                             //  Register
var CTM_INPUT_SEL                =  0x8;     //  Counter Input Select Register
var CTM_CLEAR                    =  0x9;     //  Counter Clear Register
var CTM_INPUT_SEL_2              =  0xA;     //  Counter Input Select Extension
                                             //  Register

//
// ERAD Miscellaneous Constants
//
var OWNER_DEBUGGER               =  0x2;     //  Value to set in Global
                                             //  Ownership register in order to
                                             //  set owner as debugger

//
// End of File
//