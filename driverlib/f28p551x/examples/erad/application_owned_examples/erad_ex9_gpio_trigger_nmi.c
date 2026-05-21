//#############################################################################
//
// FILE:   erad_ex9_gpio_trigger_nmi.c
//
// TITLE:  External GPIO triggering NMI
//
//! \addtogroup driver_example_list
//! <h1>ERAD - External GPIO triggering NMI</h1>
//!
//!  In this example, a GPIO is triggered externally. The ERAD Counter module
//!  is used to count the number of rising edges on the GPIO and an NMI is
//!  is triggered on reaching the set reference count value.
//!
//!  \b Watch \b Variables \n
//!  - nmiCount - number of times the NMI is serviced.
//!
//! \b External \b Connections \n
//!  - GPIO0 - trigger source
//
//#############################################################################

//
// Included Files
//
#include "device.h"
#include "board.h"

//
// Function prototypes
//
__interrupt void NMIISR(void);

//
// Globals
//
uint32_t nmiCount = 0;

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

    Interrupt_register(INT_NMI, &NMIISR);
    Interrupt_enable(INT_NMI);
    
    EINT;
    ERTM;

    while(1)
    {
        // External trigger to GPIO
    }
}

__interrupt void NMIISR(void)
{
    nmiCount++;
    SysCtl_clearAllNMIFlags();
    ERAD_clearCounterEvent(ERAD_COUNTER1_BASE);
}
