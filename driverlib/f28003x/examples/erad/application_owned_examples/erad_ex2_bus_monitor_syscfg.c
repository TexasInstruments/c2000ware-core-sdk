//#############################################################################
//
// FILE:   erad_ex2_bus_monitor.c
//
// TITLE:  ERAD Monotoring instruction and data address buses.
//
//! \addtogroup driver_example_list
//! <h1>ERAD HWBP Monitor Program Counter</h1>
//!
//!  In this example, the function delayFunction is called multiple times.
//!  The function does read and writes to the global variables startCount and
//!  endCount.
//!
//!  The BUSCOMP1 and COUNTER1 is used to count the number of times the function
//!  delayFunction was invoked. BUSCOMP2 is used to generate an interrupt when
//!  there is read access to the startCount variable and BUSCOMP3 is used to
//!  generate an interrupt when there is a write access to the endCount variable
//!
//!  \b Watch \b Variables \n
//!  - funcCount - number of times the function delayFunction was invoked
//!  - isrCount  - number of times the ISR was invoked
//!
//! \b External \b Connections \n
//!  - None
//
//#############################################################################

//
//Included Files
//
#include "driverlib.h"
#include "device.h"
#include "board.h"

//
// Globals
//
uint32_t isrCount = 0;
uint32_t funcCount = 0;
volatile uint32_t startCount, endCount;

//
// Function prototypes
//
interrupt void RTOSISR(void);
void delayFunction();

//
// Addresses of the function and variables to be monitored
//
void *addr_startCount    = (void *)&startCount;
void *addr_endCount      = (void *)&endCount;
void *addr_delayFunction = (void *)&delayFunction;


//
// Main
//
void main(void)
{
    int i;

    //
    // Initializes device clock and peripherals
    //
    Device_init();

    //
    // Board initialization
    //
    Board_init();

    //
    // Configures the GPIO pin as a push-pull output
    //
    Device_initGPIO();

    //
    // Initializes PIE and clears PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initializes the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // ISRs for each RTOS interrupt
    //
    Interrupt_register(INT_RTOS, &RTOSISR);
    Interrupt_enableInCPU(INTERRUPT_CPU_RTOSINT);

    //
    // Enable RTOS Interrupt
    //
    Interrupt_enable(INT_RTOS);

    EINT;
    ERTM;

    //
    // Loop to call the delay function multiple times
    //
    for(i = 0; i < 10; i++)
    {
        //
        // Call the delay function
        //
        delayFunction();

        //
        // Get the current count of COUNTER1 to get the number of times
        // function delayFunction was invoked
        //
        funcCount = ERAD_getCurrentCount(ERAD_COUNTER1_BASE);
    }

    ESTOP0;
    while(1);
}

//
// delay function
//
void delayFunction()
{
    uint32_t temp = startCount;
    startCount = temp + 1;

    uint16_t i=0;
    for (; i<100; i++)
    {
        NOP;
    }

    endCount = temp + 1;
}


//
// ISR to be executed on RTOS generation
// Program will halt at this ESTOP0
//
interrupt void RTOSISR(void)
{
    //
    // Indicate that the ISR was executed
    //
    isrCount++;

    if(ERAD_getBusCompStatus(ERAD_HWBP2_BASE) == ERAD_STATE_COMPLETED)
    {
        //
        // ISR was raised because of BUSCOMP2 - Read to startCount variable
        //
        ESTOP0;
       	ERAD_clearBusCompEvent(ERAD_HWBP2_BASE);
    }
    if(ERAD_getBusCompStatus(ERAD_HWBP3_BASE) == ERAD_STATE_COMPLETED)
    {
        //
        // ISR was raised because of BUSCOMP3 - Write to endCount variable
        //
        ESTOP0;
       	ERAD_clearBusCompEvent(ERAD_HWBP3_BASE);
    }
}


