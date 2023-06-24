//#############################################################################
//
// profile_function.js
//
// This JavaScript file is used to configure ERAD registers for use with the CCS
// example "erad_ex2_profilefunction".
//
// To properly use this script, the following variables must be set in the
// scripting environment prior to launching the ERAD script:
//
// - var PROJ_NAME = "erad_ex2_profilefunction"
// - var PROJ_WKSPC_LOC = "<proj_workspace_path>"
// - var PROJ_CONFIG = "<name of active configuration [CPU1_FLASH|CPU1_RAM]>"
//
// To run this ERAD script, use the following command in the scripting console:
//
// - loadJSFile("<proj_workspace_path>\\erad_ex2_profilefunction\\profile_function.js", 0);
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
// Load pre-defined macros for register addresses and useful functions
//
load(PROJ_WKSPC_LOC + "\\" + PROJ_NAME + "\\erad.js");
load(PROJ_WKSPC_LOC + "\\" + PROJ_NAME + "\\erad_util.js");

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
// Example: Profile Function
//*****************************************************************************

//
// Set owner as debugger
//
debugSession.memory.writeData(Memory.Page.DATA,
                              EradGlobalRegs + GLBL_OWNER,
                              OWNER_DEBUGGER,
                              DATA_SIZE_16);

//
// Ensure that counters 1-2 are in idle mode (bits 15:12 are set to 0)
//
var counter1Status =
    debugSession.memory.readData(Memory.Page.DATA,
                                 EradCounter1Regs + CTM_STATUS,
                                 DATA_SIZE_16);

var counter2Status =
    debugSession.memory.readData(Memory.Page.DATA,
                                 EradCounter2Regs + CTM_STATUS,
                                 DATA_SIZE_16);

var CTM_STATUS_M = 0x3000

if((0 == (counter1Status & CTM_STATUS_M)) &&
   (0 == (counter2Status & CTM_STATUS_M)))
{
    //
    // Reset HWBP_1, HWBP_2, HWBP_3 and HWBP_4
    //
    debugSession.memory.writeData(Memory.Page.DATA,
                                  EradHWBP1Regs + HWBP_CLEAR,
                                  0x1,
                                  DATA_SIZE_16);

    debugSession.memory.writeData(Memory.Page.DATA,
                                  EradHWBP2Regs + HWBP_CLEAR,
                                  0x1,
                                  DATA_SIZE_16);

    debugSession.memory.writeData(Memory.Page.DATA,
                                  EradHWBP3Regs + HWBP_CLEAR,
                                  0x1,
                                  DATA_SIZE_16);

    debugSession.memory.writeData(Memory.Page.DATA,
                                  EradHWBP4Regs + HWBP_CLEAR,
                                  0x1,
                                  DATA_SIZE_16);

    //
    // Get the start and end addresses of the FIR function "performFIR"
    //
    var addrFunc1 = getFuncAddressXML("performFIR");
    var startFIRFunc = addrFunc1[0];
    var endFIRFunc = addrFunc1[1];

    //
    // Get the start and end addresses of the sorting function "sortMax"
    //
    var addrFunc2 = getFuncAddressXML("sortMax");
    var startSortFunc = addrFunc2[0];
    var endSortFunc = addrFunc2[0];

    //
    // Set two hardware breakpoints at the start and end of performFIR
    //
    debugSession.memory.writeData(Memory.Page.DATA,
                                  EradHWBP1Regs + HWBP_REF,
                                  startFIRFunc,
                                  DATA_SIZE_32);

    debugSession.memory.writeData(Memory.Page.DATA,
                                  EradHWBP2Regs + HWBP_REF,
                                  endFIRFunc,
                                  DATA_SIZE_32);

    //
    // Set two hardware breakpoints at the start and end of sortMax
    //
    debugSession.memory.writeData(Memory.Page.DATA,
                                  EradHWBP3Regs + HWBP_REF,
                                  startSortFunc,
                                  DATA_SIZE_32);

    debugSession.memory.writeData(Memory.Page.DATA,
                                  EradHWBP4Regs + HWBP_REF,
                                  endSortFunc,
                                  DATA_SIZE_32);

    //
    // Set HWBP_1, HWBP_2, HWBP_3 and HWBP_4 to generate an event on PC match
    // RESERVED  = (0 <<  0) | -> RESERVED
    // BUS_SEL   = (1 <<  2) | -> VPC for program counter match
    // STOP      = (0 <<  5) | -> Do not stop CPU on match
    // RTOSINT   = (0 <<  6) | -> Do not generate RTOSINT
    // COMP_MODE = (0 <<  7) | -> Regular masked compare.
    //                           (address | mask) == (reference | mask)
    // RESERVED  = (0 << 12)   -> RESERVED
    //
    // HWBP_CNTL = 0x0004
    //
    debugSession.memory.writeData(Memory.Page.DATA,
                                  EradHWBP1Regs + HWBP_CNTL,
                                  0x0004,
                                  DATA_SIZE_16);

    debugSession.memory.writeData(Memory.Page.DATA,
                                  EradHWBP2Regs + HWBP_CNTL,
                                  0x0004,
                                  DATA_SIZE_16);

    debugSession.memory.writeData(Memory.Page.DATA,
                                  EradHWBP3Regs + HWBP_CNTL,
                                  0x0004,
                                  DATA_SIZE_16);

    debugSession.memory.writeData(Memory.Page.DATA,
                                  EradHWBP4Regs + HWBP_CNTL,
                                  0x0004,
                                  DATA_SIZE_16);

    //
    // Reset Counters 1 and 2 globally
    //
    debugSession.memory.writeData(Memory.Page.DATA,
                                  EradGlobalRegs + GLBL_CTM_RESET,
                                  0x3,
                                  DATA_SIZE_16);

    //
    // Clear CTM_COUNT
    //
    debugSession.memory.writeData(Memory.Page.DATA,
                                  EradCounter1Regs + CTM_COUNT,
                                  0x0,
                                  DATA_SIZE_32);

    //
    // Clear CTM_MAX_COUNT
    //
    debugSession.memory.writeData(Memory.Page.DATA,
                                  EradCounter1Regs + CTM_MAX_COUNT,
                                  0x0,
                                  DATA_SIZE_32);

    //
    // Clear EVENT_FIRED and OVERFLOW sticky bits
    // EVENT_CLEAR    = (1 << 0) | -> Clear EVENT_FIRED sticky bit in CTM_STATUS
    // OVERFLOW_CLEAR = (1 << 1) | -> Clear OVERFLOW sticky bit in CTM_STATUS
    // RESERVED       = (0 << 2)   -> RESERVED
    //
    debugSession.memory.writeData(Memory.Page.DATA,
                                  EradCounter1Regs + CTM_CLEAR,
                                  0x3,
                                  DATA_SIZE_16);

    //
    // Clear CTM_REF
    //
    debugSession.memory.writeData(Memory.Page.DATA,
                                  EradCounter1Regs + CTM_REF,
                                  0x0,
                                  DATA_SIZE_32);

    //
    // Configure CTM_1 to count cpuTimer2ISR execution cycles
    // CTM_INP_SEL_EN = (0 <<  0) | -> Disable CTM_IN_SEL register and count
    //                                 CPU cycles
    // CTM_INP_SEL    = (0 <<  1) | -> Disabled by CTM_INP_SEL_EN
    // STA_INP_SEL    = (0 <<  6) | -> Use HWBP_1 as start event for CTM_1
    // STO_INP_SEL    = (1 << 11)   -> Use HWBP_2 as stop event for CTM_1
    //
    // CTM_INPUT_SEL  = 0x0800
    //
    debugSession.memory.writeData(Memory.Page.DATA,
                                  EradCounter1Regs + CTM_INPUT_SEL,
                                  0x0800,
                                  DATA_SIZE_16);

    //
    // Configure CTM_1 to be in start-stop mode
    // RESERVED        = (0 <<  0) | -> RESERVED
    // START_STOP_MODE = (1 <<  2) | -> Enable start-stop mode
    // EVENT_MODE      = (0 <<  3) | -> Count as long as input is active (high)
    // RST_ON_MATCH    = (0 <<  4) | -> Stop counting once reference value is
    //                                  reached
    // RESERVED        = (0 <<  5) | -> RESERVED
    // STOP            = (0 <<  6) | -> Do not stop CPU when counter reaches
    //                                  reference value
    // RTOSINT         = (0 <<  7) | -> Do not generate RTOSINT
    // RESERVED        = (0 <<  8) | -> RESERVED
    // RST_EN          = (0 << 10) | -> Disable RST_INP_SEL
    // RST_INP_SEL     = (0 << 11)   -> Disabled by RST_EN
    //
    // CTM_CNTL        = 0x0004
    //
    debugSession.memory.writeData(Memory.Page.DATA,
                                  EradCounter1Regs + CTM_CNTL,
                                  0x004,
                                  DATA_SIZE_16);

    //
    // Clear CTM_COUNT, CTM_MAX_COUNT, CTM_STATUS sticky bits
    //
    debugSession.memory.writeData(Memory.Page.DATA,
                                  EradCounter2Regs + CTM_COUNT,
                                  0x0,
                                  DATA_SIZE_32);

    debugSession.memory.writeData(Memory.Page.DATA,
                                  EradCounter2Regs + CTM_MAX_COUNT,
                                  0x0,
                                  DATA_SIZE_32);

    debugSession.memory.writeData(Memory.Page.DATA,
                                  EradCounter2Regs + CTM_CLEAR,
                                  0x3,
                                  DATA_SIZE_16);

    //
    // Configure CTM_2 to count sortMax execution cycles
    // STA_INP_SEL    = (2 << 6)  | -> Use HWPB_3 as start event for CTM_2
    // STO_INP_SEL    = (3 <<  11)  -> Use HWBP_4 as stop event for CTM_2
    //
    // CTM_INPUT_SEL  = 0x1880
    //
    debugSession.memory.writeData(Memory.Page.DATA,
                                  EradCounter2Regs + CTM_INPUT_SEL,
                                  0x1880,
                                  DATA_SIZE_16);

    //
    // Configure CTM_2 to be in start-stop mode
    // START_STOP_MODE = (1 <<  2)  -> Enable start-stop mode
    //
    // CTM_CNTL        = 0x0004
    //
    debugSession.memory.writeData(Memory.Page.DATA,
                                  EradCounter2Regs + CTM_CNTL,
                                  0x0004,
                                  DATA_SIZE_16);

    //
    // Enable HWBP_1-4 and CTM_1-2
    // HWBP_GLOBAL_ENABLE    = (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3)
    // COUNTER_GLOBAL_ENABLE = (1 << 8) | (1 << 9)
    //
    var enableCounter =
        debugSession.memory.readData(Memory.Page.DATA,
                                     EradGlobalRegs + GLBL_ENABLE,
                                     DATA_SIZE_16);
    var enableBits = 0x0100 | 0x0200 | 0x0001 | 0x0002 | 0x0004 | 0x0008;
    enableCounter = enableCounter | enableBits;
    debugSession.memory.writeData(Memory.Page.DATA,
                                  EradGlobalRegs + GLBL_ENABLE,
                                  enableCounter,
                                  DATA_SIZE_16);

    print("\nCounter Started\n");

    var coreRan = 0;

    while(1)
    {
        var cycleCountFIR  =
            debugSession.memory.readData(Memory.Page.DATA,
                                         EradCounter1Regs + CTM_COUNT,
                                         DATA_SIZE_32);

        var cycleMaxFIR    =
            debugSession.memory.readData(Memory.Page.DATA,
                                         EradCounter1Regs +
                                         CTM_MAX_COUNT,
                                         DATA_SIZE_32);

        var cycleCountSort =
            debugSession.memory.readData(Memory.Page.DATA,
                                         EradCounter2Regs + CTM_COUNT,
                                         DATA_SIZE_32);

        var cycleMaxSort   =
            debugSession.memory.readData(Memory.Page.DATA,
                                         EradCounter2Regs +
                                         CTM_MAX_COUNT,
                                         DATA_SIZE_32);

        print("Current FIR Cycle Count = " + cycleCountFIR.toString() +
              "\t Max FIR Cycle Count = " + cycleMaxFIR.toString() +
              "\t Current Sort Cycle Count = " + cycleCountSort.toString() +
              "\t Max Sort Cycle Count = " + cycleMaxSort.toString());

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
    // Disable  HWBP_1-4 and CTM_1-2
    //
    enableCounter =
        debugSession.memory.readData(Memory.Page.DATA,
                                     EradGlobalRegs + GLBL_ENABLE,
                                     DATA_SIZE_16);
    enableCounter = enableCounter & (~enableBits);
    debugSession.memory.writeData(Memory.Page.DATA,
                                  EradGlobalRegs + GLBL_ENABLE,
                                  enableCounter,
                                  DATA_SIZE_16);

    //
    // Reset CTM_1-2 values
    //
    debugSession.memory.writeData(Memory.Page.DATA,
                                  EradCounter1Regs + CTM_COUNT,
                                  0x0,
                                  DATA_SIZE_32);

    debugSession.memory.writeData(Memory.Page.DATA,
                                  EradCounter1Regs + CTM_MAX_COUNT,
                                  0x0,
                                  DATA_SIZE_32);

    debugSession.memory.writeData(Memory.Page.DATA,
                                  EradCounter1Regs + CTM_CLEAR,
                                  0x3,
                                  DATA_SIZE_32);

    debugSession.memory.writeData(Memory.Page.DATA,
                                  EradCounter2Regs + CTM_COUNT,
                                  0x0,
                                  DATA_SIZE_32);

    debugSession.memory.writeData(Memory.Page.DATA,
                                  EradCounter2Regs + CTM_MAX_COUNT,
                                  0x0,
                                  DATA_SIZE_32);

    debugSession.memory.writeData(Memory.Page.DATA,
                                  EradCounter2Regs + CTM_CLEAR,
                                  0x3,
                                  DATA_SIZE_32);

    //
    // Reset HWBP_1-4
    //
    debugSession.memory.writeData(Memory.Page.DATA,
                                  EradHWBP1Regs + HWBP_CLEAR,
                                  0x1,
                                  DATA_SIZE_16);

    debugSession.memory.writeData(Memory.Page.DATA,
                                  EradHWBP2Regs + HWBP_CLEAR,
                                  0x1,
                                  DATA_SIZE_16);

    debugSession.memory.writeData(Memory.Page.DATA,
                                  EradHWBP3Regs + HWBP_CLEAR,
                                  0x1,
                                  DATA_SIZE_16);

    debugSession.memory.writeData(Memory.Page.DATA,
                                  EradHWBP4Regs + HWBP_CLEAR,
                                  0x1,
                                  DATA_SIZE_16);

    print("\nCounter Stopped\n");
}
else
{
    print("Failed\n");
}

//
// End of File
//