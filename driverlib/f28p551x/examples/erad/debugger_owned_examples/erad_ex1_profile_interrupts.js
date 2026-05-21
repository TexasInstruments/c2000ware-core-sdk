//#############################################################################
//
// erad_ex1_profile_interrupts.js
//
// This JavaScript file is used to configure ERAD registers for use with the
// -CCS example "erad_ex1_profile_interrupts".
//
// To run the ERAD script, use the following command in the scripting console:
// - require("<proj_workspace_path>\\erad_debugger_ex1_profileinterrupts\\erad_ex1_profile_interrupts.js")
//
// Note that the script must be run after loading the .out on the C28x core.
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
// Example: Profile Interrupts
//*****************************************************************************

//
// Set owner as debugger
//
debugSession.memory.write(ERAD_GLOBAL_BASE + ERAD_Global_Regs_Offset.GLBL_OWNER,
                          ERAD_Owner.ERAD_OWNER_DEBUGGER,
                          DATA_SIZE_16);

//
// Ensure that counters 1-4 are in idle mode (bits 15:12 are set to 0)
//
var counter1Status =
    Number(debugSession.memory.readOne(ERAD_COUNTER_BASE[0] + ERAD_CTM_Regs_Offset.CTM_STATUS,
                                 DATA_SIZE_16));

var counter2Status =
    Number(debugSession.memory.readOne(ERAD_COUNTER_BASE[1] + ERAD_CTM_Regs_Offset.CTM_STATUS,
                                 DATA_SIZE_16));

var counter3Status =
    Number(debugSession.memory.readOne(ERAD_COUNTER_BASE[2] + ERAD_CTM_Regs_Offset.CTM_STATUS,
                                 DATA_SIZE_16));

var counter4Status =
    Number(debugSession.memory.readOne(ERAD_COUNTER_BASE[3] + ERAD_CTM_Regs_Offset.CTM_STATUS,
                                 DATA_SIZE_16));

var CTM_STATUS_M = 0xF000;

if((0 == (counter1Status & CTM_STATUS_M)) &&
   (0 == (counter2Status & CTM_STATUS_M)) &&
   (0 == (counter3Status & CTM_STATUS_M)) &&
   (0 == (counter4Status & CTM_STATUS_M)))
{
    //
    // Reset HWBP_1 and HWBP_2
    //
    debugSession.memory.write(ERAD_HWBP_BASE[0] + ERAD_HWBP_Regs_Offset.HWBP_CLEAR,
                                  0x1,
                                  DATA_SIZE_16);

    debugSession.memory.write(ERAD_HWBP_BASE[1] + ERAD_HWBP_Regs_Offset.HWBP_CLEAR,
                                  0x1,
                                  DATA_SIZE_16);

    //
    // Get the start and end addresses of the Timer 2 ISR
    //
    var startTimer2ISR = Number(debugSession.expressions.evaluate("funcStart"));
    var endTimer2ISR = Number(debugSession.expressions.evaluate("funcEnd")) - 1;

    //
    // Set two hardware breakpoints at the start and end of cpuTimer2ISR
    //
    debugSession.memory.write(ERAD_HWBP_BASE[0] + ERAD_HWBP_Regs_Offset.HWBP_REF,
                                  startTimer2ISR,
                                  DATA_SIZE_32);

    debugSession.memory.write(ERAD_HWBP_BASE[1] + ERAD_HWBP_Regs_Offset.HWBP_REF,
                                  endTimer2ISR,
                                  DATA_SIZE_32);

    //
    // Set HWBP_1 and HWBP_2 to generate an event on PC match
    // RESERVED  = (0 <<  0) | -> RESERVED
    // BUS_SEL   = (1 <<  1) | -> VPC for program counter match
    // STOP      = (0 <<  5) | -> Do not stop CPU on match
    // RTOSINT   = (0 <<  6) | -> Do not generate RTOSINT
    // COMP_MODE = (0 <<  7) | -> Regular masked compare.
    //                           (address | mask) == (reference | mask)
    // RESERVED  = (0 << 12)   -> RESERVED
    //
    // HWBP_CNTL = 0x0002
    //
    debugSession.memory.write(ERAD_HWBP_BASE[0] + ERAD_HWBP_Regs_Offset.HWBP_CNTL,
                                  0x0002,
                                  DATA_SIZE_16);

    debugSession.memory.write(ERAD_HWBP_BASE[1] + ERAD_HWBP_Regs_Offset.HWBP_CNTL,
                                  0x0002,
                                  DATA_SIZE_16);

    //
    // Reset Counters 1-4 globally
    //
    debugSession.memory.write(ERAD_GLOBAL_BASE + ERAD_Global_Regs_Offset.GLBL_CTM_RESET,
                                  0xF,
                                  DATA_SIZE_16);

    //
    // Clear CTM_COUNT
    //
    debugSession.memory.write(ERAD_COUNTER_BASE[0] + ERAD_CTM_Regs_Offset.CTM_COUNT,
                                  0x0,
                                  DATA_SIZE_32);

    //
    // Clear CTM_MAX_COUNT
    //
    debugSession.memory.write(ERAD_COUNTER_BASE[0] + ERAD_CTM_Regs_Offset.CTM_MAX_COUNT,
                                  0x0,
                                  DATA_SIZE_32);

    //
    // Clear EVENT_FIRED and OVERFLOW sticky bits
    // EVENT_CLEAR    = (1 << 0) | -> Clear EVENT_FIRED sticky bit in CTM_STATUS
    // OVERFLOW_CLEAR = (1 << 1) | -> Clear OVERFLOW sticky bit in CTM_STATUS
    // RESERVED       = (0 << 2)   -> RESERVED
    //
    debugSession.memory.write(ERAD_COUNTER_BASE[0] + ERAD_CTM_Regs_Offset.CTM_CLEAR,
                                  0x3,
                                  DATA_SIZE_16);

    //
    // Clear CTM_REF
    //
    debugSession.memory.write(ERAD_COUNTER_BASE[0] + ERAD_CTM_Regs_Offset.CTM_REF,
                                  0x0,
                                  DATA_SIZE_32);

    //
    // Configure CTM_1 to count cpuTimer2ISR execution cycles
    // Configure CTM_1 to be in start-stop mode
    //
    // CTM_INPUT_SEL = 0x0000
    //   CTM_INP_SEL    = (0 <<  0) | -> Disabled by CTM_INP_SEL_EN
    //   STA_INP_SEL    = (0 <<  8) | -> Use HWBP_1 as start event for CTM_1
    //
    // CTM_INPUT_SEL_2 = 0x0001
    //   STO_INP_SEL    = (1 << 0)   -> Use HWBP_2 as stop event for CTM_1
    //   RST_INP_SEL    = (0 << 8)   -> Disabled by RST_EN
    //
    // CTM_CNTL = 0x0004
    //   RESERVED        = (0 <<  0) | -> RESERVED
    //   START_STOP_MODE = (1 <<  2) | -> Enable start-stop mode
    //   EVENT_MODE      = (0 <<  3) | -> Count as long as input is active (high)
    //   RST_ON_MATCH    = (0 <<  4) | -> Stop counting once reference value is
    //                                    reached
    //   RESERVED        = (0 <<  5) | -> RESERVED
    //   STOP            = (0 <<  6) | -> Do not stop CPU when counter reaches
    //                                    reference value
    //   RTOSINT         = (0 <<  7) | -> Do not generate RTOSINT
    //   START_STOP_CUM  = (0 <<  8) | -> Counter gets cleared on stop event
    //   RESERVED        = (0 <<  9) | -> RESERVED
    //   RST_EN          = (0 << 10) | -> Disable RST_INP_SEL
    //   CTM_INP_SEL_EN  = (0 << 11)   -> Disable CTM_IN_SEL register and count
    //                                    CPU cycles
    //
    debugSession.memory.write(ERAD_COUNTER_BASE[0] + ERAD_CTM_Regs_Offset.CTM_INPUT_SEL,
                                  (0x0),
                                  DATA_SIZE_16);
    debugSession.memory.write(ERAD_COUNTER_BASE[0] + ERAD_CTM_Regs_Offset.CTM_INPUT_SEL_2,
                                  (0x1),
                                  DATA_SIZE_16);

    debugSession.memory.write(ERAD_COUNTER_BASE[0] + ERAD_CTM_Regs_Offset.CTM_CNTL,
                                  0x004,
                                  DATA_SIZE_16);

    //
    // Clear CTM_COUNT, CTM_MAX_COUNT, CTM_STATUS sticky bits
    //
    debugSession.memory.write(ERAD_COUNTER_BASE[1] + ERAD_CTM_Regs_Offset.CTM_COUNT,
                                  0x0,
                                  DATA_SIZE_32);

    debugSession.memory.write(ERAD_COUNTER_BASE[1] + ERAD_CTM_Regs_Offset.CTM_MAX_COUNT,
                                  0x0,
                                  DATA_SIZE_32);

    debugSession.memory.write(ERAD_COUNTER_BASE[1] + ERAD_CTM_Regs_Offset.CTM_CLEAR,
                                  0x3,
                                  DATA_SIZE_16);

    //
    // Configure CTM_2 to count number of times system event TIMER2_TINT2 occurs
    // Configure CTM_2 to be in rising-edge count mode
    //
    // CTM_INPUT_SEL   = 34 ( Count system event TIMER2_TINT2 )
    // CTM_INPUT_SEL_2 = 0
    //
    debugSession.memory.write(ERAD_COUNTER_BASE[1] + ERAD_CTM_Regs_Offset.CTM_INPUT_SEL,
                                  34,
                                  DATA_SIZE_16);
    debugSession.memory.write(ERAD_COUNTER_BASE[1] + ERAD_CTM_Regs_Offset.CTM_INPUT_SEL_2,
                                  0x0000,
                                  DATA_SIZE_16);

    //
    // Configure CTM_2 to be in rising-edge count mode
    //
    // CTM_CNTL = 0x0808
    //   EVENT_MODE     = (1 <<  3) | -> Count only on rising-edge of count input
    //   CNT_INP_SEL_EN = (1 << 11)   -> Enable CTM_INP_SEL
    //
    debugSession.memory.write(ERAD_COUNTER_BASE[1] + ERAD_CTM_Regs_Offset.CTM_CNTL,
                                  0x0808,
                                  DATA_SIZE_16);
    //
    // Clear CTM_COUNT, CTM_MAX_COUNT, CTM_STATUS sticky bits
    //
    debugSession.memory.write(ERAD_COUNTER_BASE[2] + ERAD_CTM_Regs_Offset.CTM_COUNT,
                                  0x0,
                                  DATA_SIZE_32);

    debugSession.memory.write(ERAD_COUNTER_BASE[2] + ERAD_CTM_Regs_Offset.CTM_MAX_COUNT,
                                  0x0,
                                  DATA_SIZE_32);

    debugSession.memory.write(ERAD_COUNTER_BASE[2] + ERAD_CTM_Regs_Offset.CTM_CLEAR,
                                  0x3,
                                  DATA_SIZE_16);

    //
    // Configure CTM_3 to count number of times cputTimer2ISR executes
    // CNT_INP_SEL = 0 ( Use HWBP_1 as count event )
    //
    debugSession.memory.write(ERAD_COUNTER_BASE[2] + ERAD_CTM_Regs_Offset.CTM_INPUT_SEL,
                                  0x0000,
                                  DATA_SIZE_16);

    //
    // Configure CTM_3 to be in rising-edge count mode
    //
    // CTM_CNTL = 0x0808
    //   EVENT_MODE     = (1 <<  3) | -> Count only on rising-edge of count input
    //   CNT_INP_SEL_EN = (1 << 11)   -> Enable CTM_INP_SEL
    //
    debugSession.memory.write(ERAD_COUNTER_BASE[2] + ERAD_CTM_Regs_Offset.CTM_CNTL,
                                  0x0808,
                                  DATA_SIZE_16);

    //
    // Clear CTM_COUNT, CTM_MAX_COUNT, CTM_STATUS sticky bits
    //
    debugSession.memory.write(ERAD_COUNTER_BASE[3] + ERAD_CTM_Regs_Offset.CTM_COUNT,
                                  0x0,
                                  DATA_SIZE_32);

    debugSession.memory.write(ERAD_COUNTER_BASE[3] + ERAD_CTM_Regs_Offset.CTM_MAX_COUNT,
                                  0x0,
                                  DATA_SIZE_32);

    debugSession.memory.write(ERAD_COUNTER_BASE[3] + ERAD_CTM_Regs_Offset.CTM_CLEAR,
                                  0x3,
                                  DATA_SIZE_16);

    //
    // Configure CTM_4 to grab latency from TIMER2_TINT2 to cpuTimer2ISR
    // execution
    //
    // CTM_INPUT_SEL = 0x2200
    //   STA_INP_SEL = (34 << 8) -> Use TIMER2_TINT2 as start event for CTM_4
    //
    // CTM_INPUT_SEL_2 = 0x0000
    //   STO_INP_SEL = (0 << 0)  -> Use cpuTimer2ISR as stop event for CTM_4
    //
    debugSession.memory.write(ERAD_COUNTER_BASE[3] + ERAD_CTM_Regs_Offset.CTM_INPUT_SEL,
                                  0x2200,
                                  DATA_SIZE_16);
    debugSession.memory.write(ERAD_COUNTER_BASE[3] + ERAD_CTM_Regs_Offset.CTM_INPUT_SEL_2,
                                  0x0,
                                  DATA_SIZE_16);

    //
    // Configure CTM_4 to be in start-stop mode
    //
    // CTM_CNTL  = 0x0004
    //   START_STOP_MODE = (1 <<  2)  -> Enable start-stop mode
    //
    debugSession.memory.write(ERAD_COUNTER_BASE[3] + ERAD_CTM_Regs_Offset.CTM_CNTL,
                                  0x0004,
                                  DATA_SIZE_16);
    //
    // Enable HWBP_1-2 and CTM_1-4
    // HWBP_GLOBAL_ENABLE    = (1 << 0) | (1 << 1)
    // COUNTER_GLOBAL_ENABLE = (1 << 8) | (1 << 9) | (1 << 10) | (1 << 11)
    //
    var enableCounter =
        Number(debugSession.memory.readOne(ERAD_GLOBAL_BASE + ERAD_Global_Regs_Offset.GLBL_ENABLE,
                                     DATA_SIZE_16));
    var enableBits = 0x0100 | 0x0200 | 0x0400 | 0x0800 | 0x0001 | 0x0002;
    enableCounter = enableCounter | enableBits;
    debugSession.memory.write(ERAD_GLOBAL_BASE + ERAD_Global_Regs_Offset.GLBL_ENABLE,
                                  enableCounter,
                                  DATA_SIZE_16);

    console.log("\nCounter Started\n");

    var coreRan = 0;

    while(1)
    {
        var cycleCount =
            debugSession.memory.readOne (ERAD_COUNTER_BASE[0] + ERAD_CTM_Regs_Offset.CTM_COUNT,
                                         DATA_SIZE_32);

        var cycleMax =
            debugSession.memory.readOne (ERAD_COUNTER_BASE[0] +
                                         ERAD_CTM_Regs_Offset.CTM_MAX_COUNT,
                                         DATA_SIZE_32);

        var intEventCount =
            debugSession.memory.readOne (ERAD_COUNTER_BASE[1] + ERAD_CTM_Regs_Offset.CTM_COUNT,
                                         DATA_SIZE_32);

        var isrExecCount =
            debugSession.memory.readOne (ERAD_COUNTER_BASE[2] + ERAD_CTM_Regs_Offset.CTM_COUNT,
                                         DATA_SIZE_32);

        var isrDelayCycleMax =
            debugSession.memory.readOne (ERAD_COUNTER_BASE[3] +
                                         ERAD_CTM_Regs_Offset.CTM_MAX_COUNT,
                                         DATA_SIZE_32);

        console.log("Current ISR Cycle Count = " + cycleCount.toString() +
              "\t Max ISR Cycle Count = " + cycleMax.toString() +
              "\t Int Occurence Count = " + intEventCount.toString() +
              "\t ISR Execution Count = " + isrExecCount.toString() +
              "\t ISR Delay Cycle Count = " + isrDelayCycleMax.toString());

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
    // Disable  HWBP_1-2 and CTM_1-4
    //
    enableCounter =
        Number(debugSession.memory.readOne(ERAD_GLOBAL_BASE + ERAD_Global_Regs_Offset.GLBL_ENABLE,
                                     DATA_SIZE_16));
    enableCounter = enableCounter & (~enableBits);
    debugSession.memory.write(ERAD_GLOBAL_BASE + ERAD_Global_Regs_Offset.GLBL_ENABLE,
                                  enableCounter,
                                  DATA_SIZE_16);

    //
    // Reset CTM_1-4 values
    //
    debugSession.memory.write(ERAD_COUNTER_BASE[0] + ERAD_CTM_Regs_Offset.CTM_COUNT,
                                  0x0,
                                  DATA_SIZE_32);

    debugSession.memory.write(ERAD_COUNTER_BASE[0] + ERAD_CTM_Regs_Offset.CTM_MAX_COUNT,
                                  0x0,
                                  DATA_SIZE_32);

    debugSession.memory.write(ERAD_COUNTER_BASE[0] + ERAD_CTM_Regs_Offset.CTM_CLEAR,
                                  0x3,
                                  DATA_SIZE_32);

    debugSession.memory.write(ERAD_COUNTER_BASE[1] + ERAD_CTM_Regs_Offset.CTM_COUNT,
                                  0x0,
                                  DATA_SIZE_32);

    debugSession.memory.write(ERAD_COUNTER_BASE[1] + ERAD_CTM_Regs_Offset.CTM_MAX_COUNT,
                                  0x0,
                                  DATA_SIZE_32);

    debugSession.memory.write(ERAD_COUNTER_BASE[1] + ERAD_CTM_Regs_Offset.CTM_CLEAR,
                                  0x3,
                                  DATA_SIZE_32);

    debugSession.memory.write(ERAD_COUNTER_BASE[2] + ERAD_CTM_Regs_Offset.CTM_COUNT,
                                  0x0,
                                  DATA_SIZE_32);

    debugSession.memory.write(ERAD_COUNTER_BASE[2] + ERAD_CTM_Regs_Offset.CTM_MAX_COUNT,
                                  0x0,
                                  DATA_SIZE_32);

    debugSession.memory.write(ERAD_COUNTER_BASE[2] + ERAD_CTM_Regs_Offset.CTM_CLEAR,
                                  0x3,
                                  DATA_SIZE_32);

    debugSession.memory.write(ERAD_COUNTER_BASE[3] + ERAD_CTM_Regs_Offset.CTM_COUNT,
                                  0x0,
                                  DATA_SIZE_32);

    debugSession.memory.write(ERAD_COUNTER_BASE[3] + ERAD_CTM_Regs_Offset.CTM_MAX_COUNT,
                                  0x0,
                                  DATA_SIZE_32);

    debugSession.memory.write(ERAD_COUNTER_BASE[3] + ERAD_CTM_Regs_Offset.CTM_CLEAR,
                                  0x3,
                                  DATA_SIZE_32);

    //
    // Reset HWBP_1-2
    //
    debugSession.memory.write(ERAD_HWBP_BASE[0] + ERAD_HWBP_Regs_Offset.HWBP_CLEAR,
                                  0x1,
                                  DATA_SIZE_16);

    debugSession.memory.write(ERAD_HWBP_BASE[1] + ERAD_HWBP_Regs_Offset.HWBP_CLEAR,
                                  0x1,
                                  DATA_SIZE_16);

    console.log("\nCounter Stopped\n");
}
else
{
    console.log("Failed\n");
}

//
// End of File
//