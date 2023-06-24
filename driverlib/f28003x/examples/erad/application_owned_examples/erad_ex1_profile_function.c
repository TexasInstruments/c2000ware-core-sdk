//#############################################################################
//
// FILE:   erad_ex1_profile_function.c
//
// TITLE:  ERAD Profile Function.
//
//! \addtogroup driver_example_list
//! <h1>ERAD Profile Function</h1>
//!
//!  This example uses BUSCOMP1, BUSCOMP2 and COUNTER1 of the ERAD module to
//!  profile a function (delayFunction). It calculates the CPU cycles taken
//!  between the the start address of the function to the end address of the
//!  function
//!
//!  Two dummy variable are written to inside the function - startCount and
//!  endCount. BUSCOMP3, BUSCOMP4 and COUNTER2 are used to profile the time
//!  taken between the access to startCount variable till the access to
//!  endCount variable.
//!
//!  Both the counters are setup to operate in START-STOP mode and count the
//!  number of CPU cycles spend between the respective bus comparator events.
//!
//!  \b Watch \b Variables \n
//!   - cycles_Functio - the maximum number of cycles between the start of
//!                      function to the end of function
//!   - cycles_Data    - the maximum number of cycles taken between
//!                      accessing startCount variable to endCount variable
//!
//! \b External \b Connections \n
//!  None
//
//#############################################################################

//
// Included Files
//
#include "driverlib.h"
#include "device.h"

//
// Global Variables
//

//
// Start and end address of the function delayFunction.
// This value comes from the linker command file.
//
extern uint32_t delayFuncStart, delayFuncEnd;

//
// The variables used in the function which are monitored by bus comparators
// 3 and 4.
//
volatile uint32_t startCount = 0;
volatile uint32_t endCount = 0;

//
// Watch variables with the number of CPU cycles elapsed.
//
volatile uint32_t cycles_Function = 0;
volatile uint32_t cycles_Function_Max = 0;
volatile uint32_t cycles_Data = 0;
volatile uint32_t cycles_Data_Max = 0;

//
// Function Prototypes
//
void delayFunction(uint16_t);

//
// Main
//
void main(void)
{
    uint16_t i;
    ERAD_Profile_Params params;

    //
    // Initializes device clock and peripherals
    //
    Device_init();

    //
    // Configures the GPIO pin as a push-pull output
    //
    Device_initGPIO();

    //
    // Initializes the ERAD module with the owner set as
    // the APPLICATION
    //
    ERAD_initModule(ERAD_OWNER_APPLICATION);

    //
    // Parameters for profiling function.
    // The PC value is being monitored here.
    //
    params.start_address = (uint32_t)&delayFuncStart;
    params.end_address   = (uint32_t)&delayFuncEnd - 1U;
    params.bus_sel       = ERAD_BUSCOMP_BUS_VPC;
    params.busComp_base1 = ERAD_HWBP1_BASE;
    params.busComp_base2 = ERAD_HWBP2_BASE;
    params.counter_base  = ERAD_COUNTER1_BASE;

    //
    // Configuring the required ERAD submodules
    //
    ERAD_profile(params);

    //
    // Parameters for profiling the time between the accesses
    // to startCount and endCount variables.
    // The address in the Data Write Address Bus is monitored here.
    //
    params.start_address = (uint32_t)&startCount;
    params.end_address   = (uint32_t)&endCount;
    params.bus_sel       = ERAD_BUSCOMP_BUS_DWAB;
    params.busComp_base1 = ERAD_HWBP3_BASE;
    params.busComp_base2 = ERAD_HWBP4_BASE;
    params.counter_base  = ERAD_COUNTER2_BASE;

    //
    // Configuring the required ERAD submodules
    //
    ERAD_profile(params);

    //
    // Loop to call the delay function repeatedly with different delays
    //
    for(i=0; i<10; i++)
    {
        delayFunction(i % 5);

        //
        // View these two variables in CCS view
        // Note that calling the function ERAD_getCurrentValue here will
        // return 0 since the stop events have already been occurred.
        //
        cycles_Function = ERAD_getMaxCount(ERAD_COUNTER1_BASE);
        cycles_Data     = ERAD_getMaxCount(ERAD_COUNTER2_BASE);

        ESTOP0;

        //
        // Uncomment the code below to clear the maximum count
        //
        // ERAD_setMaxCount(ERAD_COUNTER1_BASE, 0);
        // ERAD_setMaxCount(ERAD_COUNTER2_BASE, 0);
    }

    ESTOP0;
    while(1);
}

//
// delay function
//
#pragma CODE_SECTION(delayFunction, ".delayFunc")
void delayFunction(uint16_t delay)
{
    startCount++;

    uint16_t i=0;
    for (; i<delay; i++)
    {
        NOP;
        NOP;
        NOP;
        NOP;
    }

    endCount++;
}

//
// End of File
//
