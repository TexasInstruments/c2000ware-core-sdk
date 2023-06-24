//#############################################################################
//
// FILE:   erad_ex3_stack_overflow_detect.c
//
// TITLE:  ERAD HWBP Stack Overflow Detection.
//
//! \addtogroup driver_example_list
//! <h1>ERAD HWBP Stack Overflow Detection</h1>
//!
//!  This example uses BUSCOMP1 to monitor the stack. The Bus comparator
//!  is set to monitor the data write access bus and generate an RTOS interrupt
//!  CPU when a write is detected to end of the STACK within a threshold.
//!
//!  \b Watch \b Variables \n
//!  - functionCallCount - the number of times the recursive function
//!    overflowing the STACK is called.
//!  - x indicates that the ISR has been entered
//!
//! \b External \b Connections \n
//!  None
//
//#############################################################################

//
//Included Files
//
#include "driverlib.h"
#include "device.h"


//
// Global Variables
//

//
// The stack end address
//
extern uint32_t __TI_STACK_END;

//
// A threshold value. An interrupt is generated when there is an access to
// StackEnd - threshold
//
uint32_t threshold = 10;

volatile uint32_t functionCallCount = 0;
uint32_t x = 0;

//
// Function Prototypes
//
interrupt void RTOSISR(void);
void recursiveFunction(uint32_t delay);

//
// Main
//
void main(void)
{
    //
    // Initializes device clock and peripherals
    //
    Device_init();

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

    //
    // Initializes the ERAD module with the owner set as APPLICATION
    //
    ERAD_initModule(ERAD_OWNER_APPLICATION);

    //
    // Parameters for generating interrupt on a write access to the
    // threshold address
    //
    ERAD_AddressHit_Params addr_params;
    addr_params.address = (uint32_t)&__TI_STACK_END - threshold;
    addr_params.mask = 0x0;
    addr_params.bus_sel = ERAD_BUSCOMP_BUS_DWAB;

    //
    // Sets a watchpoint at the end address of the STACK
    //
    ERAD_enableInterruptOnAddressHit(addr_params, ERAD_HWBP1_BASE);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    recursiveFunction(1);

    //
    // IDLE loop. Just sit and loop forever (optional)
    //
    while(1)
    {

    }
}

//
// recursive function to fill the stack
//
void recursiveFunction(uint32_t delay)
{
    functionCallCount++;

    //
    // Recursive function
    //
    recursiveFunction(delay + 1UL);
}

//
// ISR to be executed on RTOS generation
// Program will halt at this ESTOP0
//
interrupt void
RTOSISR(void)
{
    //
    // Indicate that the ISR was executed
    //
    x++;
    ESTOP0;
}

//
// End of File
//
