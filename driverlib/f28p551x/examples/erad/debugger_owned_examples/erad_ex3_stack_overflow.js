//#############################################################################
//
// erad_ex3_stack_overflow.js
//
// This JavaScript file is used to configure ERAD registers for use with the CCS
// example "erad_ex3_stackoverflow".
//
// To run the ERAD script, use the following command in the scripting console:
// - require("<proj_workspace_path>\\erad_debugger_ex3_stackoverflow\\erad_ex3_stack_overflow.js")
//
// This JavaScript file uses CCS Scripting features. For information, please visit:
// https://software-dl.ti.com/ccs/esd/documents/users_guide_ccs_20.0.0/index_debug-scripting.html
//
//#############################################################################

const ERAD = require("./erad.js");

let {
    ERAD_GLOBAL_BASE,
    ERAD_Global_Regs_Offset,
    ERAD_HWBP_BASE,
    ERAD_HWBP_Regs_Offset,
    ERAD_COUNTER_BASE,
    ERAD_CTM_Regs_Offset,
    ERAD_Owner
} = ERAD;

//
// Launch a scripting session
//
const { initScripting } = require(require.resolve("scripting",  {paths: [process.cwd()] }));
const ds = initScripting();
const debugSession = ds.openSession("C28xx_CPU1");

//
// Variables for data read/write sizes
//
var DATA_SIZE_16 = 16;
var DATA_SIZE_32 = 32;

//*****************************************************************************
// Example: Stack Overflow
//*****************************************************************************

//
// Set owner as debugger
//
debugSession.memory.write(ERAD_GLOBAL_BASE + ERAD_Global_Regs_Offset.GLBL_OWNER,
                              ERAD_Owner.ERAD_OWNER_DEBUGGER,
                              DATA_SIZE_16);

//
// Ensure that HWBP_1 is in idle mode (bits 15:12 are set to 0)
//
var hwbp1Status =
    Number(debugSession.memory.readOne(ERAD_HWBP_BASE[0] + ERAD_HWBP_Regs_Offset.HWBP_STATUS,
                                 DATA_SIZE_16));

if(0 == (hwbp1Status &  0xF000))
{
    console.log("\nProfile Setup\n");

    //
    // Reset HWBP_1
    //
    debugSession.memory.write(ERAD_HWBP_BASE[0] + ERAD_HWBP_Regs_Offset.HWBP_CLEAR,
                                  0x1,
                                  DATA_SIZE_16);

    debugSession.memory.write(ERAD_HWBP_BASE[0] + ERAD_HWBP_Regs_Offset.HWBP_CNTL,
                                  0x0,
                                  DATA_SIZE_16);

    debugSession.memory.write(ERAD_HWBP_BASE[0] + ERAD_HWBP_Regs_Offset.HWBP_REF,
                                  0x0,
                                  DATA_SIZE_32);

    //
    // Grab maximum value for stack
    //
  	var stackEnd = Number(debugSession.expressions.evaluate("__TI_STACK_END"));
    console.log("\nSP END: " + stackEnd.toString(16) + "\n");

    //
    // Set HWBP_REF to be stackEnd + 1 for HWBP_1
    //
    debugSession.memory.write(ERAD_HWBP_BASE[0] + ERAD_HWBP_Regs_Offset.HWBP_REF,
                                  stackEnd + 1,
                                  DATA_SIZE_32);

    //
    // Clear mask value
    //
    debugSession.memory.write(ERAD_HWBP_BASE[0] + ERAD_HWBP_Regs_Offset.HWBP_MASK,
                                  0x0,
                                  DATA_SIZE_32);

    //
    // Set CPU to halt when write to address greater than value in HWBP_REF
    // occurs
    // RESERVED  = (0   <<  0) | -> RESERVED
    // BUS_SEL   = (10  <<  1) | -> DWAB for write data accesses
    // STOP      = (1   <<  5) | -> Halt CPU on match
    // ROTSINT   = (0   <<  6) | -> Do not generate RTOSINT
    // COMP_MODE = (0   <<  7) | -> Generate match when address matches HWBP_REF
    // RESERVED  = (0   << 10)   -> RESERVED
    //
    // HWBP_CNTL = 0x24
    //
    debugSession.memory.write(ERAD_HWBP_BASE[0] + ERAD_HWBP_Regs_Offset.HWBP_CNTL,
                                  0x24,
                                  DATA_SIZE_16);

    //
    // Enable HWBP_1. Update GLBL_ENABLE register with value 0x1
    //
    var enableHWBP =
        Number(debugSession.memory.readOne(ERAD_GLOBAL_BASE + ERAD_Global_Regs_Offset.GLBL_ENABLE,
                                     DATA_SIZE_16));
    var enableBits = 0x0001;
    enableHWBP = enableHWBP | enableBits;
    debugSession.memory.write(ERAD_GLOBAL_BASE + ERAD_Global_Regs_Offset.GLBL_ENABLE,
                                  enableHWBP,
                                  DATA_SIZE_16);

    //
    // Loop until Stack Overflow occurs
    //
    console.log("\nProfile Started. CPU will halt on stack overflow.\n");

    var coreRan = 0;

    while(1)
    {
        //
        // Read status and check for event fired bit to be set active. This
        // signals that a "match" has occured, as defined by the values set in
        // HWBP_CNTL and HWBP_REF for HWBP_1. In this case, the event fired bit
        // represents whether or not a write has occured to the address in
        // HWBP_REF1, which is set to one past the _STACK_END value
        //
        var bp_status =
            Number(debugSession.memory.readOne(ERAD_HWBP_BASE[0] + ERAD_HWBP_Regs_Offset.HWBP_STATUS,
                                         DATA_SIZE_16));

        if(bp_status & 0x1 == 1)
        {
            console.log("\nSTACK OVERFLOW detected. Halting CPU.\n");
            break;
        }

        //
        // Halt script if CPU is halted
        //
        var halted = debugSession.target.isHalted();

        if(!halted)
        {
            coreRan = 1;
        }

        if(coreRan && halted)
        {
            break;
        }
    }

    //
    // Disable HWBP_1
    //
    enableHWBP = Number(debugSession.memory.readOne(ERAD_GLOBAL_BASE +
                                              ERAD_Global_Regs_Offset.GLBL_ENABLE,
                                              DATA_SIZE_16));

    enableHWBP = enableHWBP & (~enableBits);

    debugSession.memory.write(ERAD_GLOBAL_BASE + ERAD_Global_Regs_Offset.GLBL_ENABLE,
                                  enableHWBP,
                                  DATA_SIZE_16);

    //
    // Reset HWBP_1
    //
    debugSession.memory.write(ERAD_HWBP_BASE[0] + ERAD_HWBP_Regs_Offset.HWBP_CLEAR,
                                  0x1,
                                  DATA_SIZE_16);


    console.log("\nProfile stopped\n");
}
else
{
    console.log("\nFAILED. HWBP_1 is not in idle state\n");
}

//
// End of File
//