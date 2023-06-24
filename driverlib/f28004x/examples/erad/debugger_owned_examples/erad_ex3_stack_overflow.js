//#############################################################################
//
// stack_overflow.js
//
// This JavaScript file is used to configure ERAD registers for use with the CCS
// example "erad_ex3_stackoverflow".
//
// To properly use this script, the following variables must be set in the
// scripting environment prior to launching the ERAD script:
//
// - var PROJ_NAME = "erad_ex3_stackoverflow"
// - var PROJ_WKSPC_LOC = <proj_workspace_path>
//
// To run this ERAD script, use the following command in the scripting console:
//
// - loadJSFile("<proj_workspace_path>\\erad_ex3_stackoverflow\\stack_overflow.js", 0);
//
// This JavaScript file uses Debug Server Scripting (DSS) features. For
// information on using the DSS, please visit:
// http://software-dl.ti.com/ccs/esd/documents/users_guide/sdto_dss_handbook.html
//
//#############################################################################

//
// Import the DSS packages
//
importPackage(Packages.com.ti.debug.engine.scripting)
importPackage(Packages.com.ti.ccstudio.scripting.environment)
importPackage(Packages.java.lang)

//
// Load pre-defined macros for register addresses
//
load(PROJ_WKSPC_LOC + "\\" + PROJ_NAME + "\\erad.js")

//
// Create our scripting environment object. This is the main entry point into
// any script and the factory for creating other scriptable servers and sessions
//
var script = ScriptingEnvironment.instance();

script.traceSetConsoleLevel(TraceLevel.ALL)

//
// Create a debug server
//
var ds = script.getServer( "DebugServer.1" );

//
// Open a debug session
//
debugSession = ds.openSession( "*", "C28xx_CPU1" );

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
debugSession.memory.writeData(Memory.Page.DATA,
                              EradGlobalRegs + GLBL_OWNER,
                              OWNER_DEBUGGER,
                              DATA_SIZE_16);

//
// Ensure that HWBP_1 is in idle mode (bits 15:12 are set to 0)
//
var hwbp1Status =
    debugSession.memory.readData(Memory.Page.DATA,
                                 EradHWBP1Regs + HWBP_STATUS,
                                 DATA_SIZE_16);

if(0 == (hwbp1Status &  0xF000))
{
    print("\nProfile Setup\n");

    //
    // Reset HWBP_1
    //
    debugSession.memory.writeData(Memory.Page.DATA,
                                  EradHWBP1Regs + HWBP_CLEAR,
                                  0x1,
                                  DATA_SIZE_16);

    debugSession.memory.writeData(Memory.Page.DATA,
                                  EradHWBP1Regs + HWBP_CNTL,
                                  0x0,
                                  DATA_SIZE_16);

    debugSession.memory.writeData(Memory.Page.DATA,
                                  EradHWBP1Regs + HWBP_REF,
                                  0x0,
                                  DATA_SIZE_32);

    //
    // Grab maximum value for stack
    //
    if (debugSession.symbol.exists("__STACK_END"))
    {
    	var stackEnd = debugSession.expression.evaluate("__STACK_END");
    }
    else
    {
    	var stackEnd = debugSession.expression.evaluate("__TI_STACK_END");
    }
    print("\nSP END: " + stackEnd.toString(16) + "\n");

    //
    // Set HWBP_REF to be stackEnd + 1 for HWBP_1
    //
    debugSession.memory.writeData(Memory.Page.DATA,
                                  EradHWBP1Regs + HWBP_REF,
                                  stackEnd + 1,
                                  DATA_SIZE_32);

    //
    // Clear mask value
    //
    debugSession.memory.writeData(Memory.Page.DATA,
                                  EradHWBP1Regs + HWBP_MASK,
                                  0x0,
                                  DATA_SIZE_32);

    //
    // Set CPU to halt when write to address greater than value in HWBP_REF
    // occurs
    // RESERVED  = (0   <<  0) | -> RESERVED
    // BUS_SEL   = (10  <<  2) | -> DWAB for write data accesses
    // STOP      = (1   <<  5) | -> Halt CPU on match
    // ROTSINT   = (0   <<  6) | -> Do not generate RTOSINT
    // COMP_MODE = (0   <<  7) | -> Generate match when address matches HWBP_REF
    // RESERVED  = (0   << 10)   -> RESERVED
    //
    // HWBP_CNTL = 0x28
    //
    debugSession.memory.writeData(Memory.Page.DATA,
                                  EradHWBP1Regs + HWBP_CNTL,
                                  0x28,
                                  DATA_SIZE_16);

    //
    // Enable HWBP_1. Update GLBL_ENABLE register with value 0x1
    //
    var enableHWBP =
        debugSession.memory.readData(Memory.Page.DATA,
                                     EradGlobalRegs + GLBL_ENABLE,
                                     DATA_SIZE_16);
    var enableBits = 0x0001;
    enableHWBP = enableHWBP | enableBits;
    debugSession.memory.writeData(Memory.Page.DATA,
                                  EradGlobalRegs + GLBL_ENABLE,
                                  enableHWBP,
                                  DATA_SIZE_16);

    //
    // Loop until Stack Overflow occurs
    //
    print("\nProfile Started. CPU will halt on stack overflow.\n");

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
            debugSession.memory.readData(Memory.Page.DATA,
                                         EradHWBP1Regs + HWBP_STATUS,
                                         DATA_SIZE_16);

        if(bp_status & 0x1 == 1)
        {
            print("\nSTACK OVERFLOW detected. Halting CPU.\n");
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
    enableHWBP = debugSession.memory.readData(Memory.Page.DATA,
                                              EradGlobalRegs +
                                              GLBL_ENABLE,
                                              DATA_SIZE_16);

    enableHWBP = enableHWBP & (~enableBits);

    debugSession.memory.writeData(Memory.Page.DATA,
                                  EradGlobalRegs + GLBL_ENABLE,
                                  enableHWBP,
                                  DATA_SIZE_16);

    print("\nProfile stopped\n");
}
else
{
    print("\nFAILED. HWBP_1 is not in idle state\n");
}

//
// End of File
//