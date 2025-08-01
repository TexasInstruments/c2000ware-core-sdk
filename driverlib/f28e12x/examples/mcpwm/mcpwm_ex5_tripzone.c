//#############################################################################
//
// FILE:   mcpwm_ex5_tripzone.c
//
// TITLE:  MCPWM PWM Tripzone Feature Showcase
//
//! \addtogroup driver_example_list
//! <h1>MCPWM PWM Tripzone Feature Showcase</h1>
//!
//! This example configures myMCPWM0 and myMCPWM1 as follows
//!     myMCPWM0 
//!         Time Base Configurations 
//!             In Up Count Mode for 15999 TBCLKs or 10KHz Frequency for TBCLK of 160MHz
//!         Action Qualifier configurations
//!             Output A1/B1: Set High on Counter Zero, Set Low on Counter matches CMPA/CMPB counting up
//!             Output A2/B2: Set Low on Counter Period, Set High on Counter matches CMPA/CMPB counting up
//!             Output A3: Set High on Counter matches CMPA, Set Low on Counter matches CMPB counting up
//!             Output B3: Set Low on Counter matches CMPA, Set High on Counter matches CMPB counting up
//!         Trip Zone Configurations
//!             CBC1 is source of the CBC trip. CBC Clear is "counter = zero" event
//!             TZA is configured for Setting Low, TZB is configured to Setting High
//!         Interrupt Configurations
//!             Interrupt is configured for CBC trip
//!
//!     myMCPWM1
//!         Time Base Configurations 
//!             In Up Down Count Mode for 8000 TBCLKs or 10KHz Frequency for TBCLK of 160MHz
//!         Action Qualifier configurations
//!             Output A1: Set High on Counter matches CMPA counting up, Set Low on Counter matches CMPA counting down
//!             Output B1: Set High on Counter matches CMPB counting up, Set Low on Counter matches CMPB counting down
//!         Trip Zone Configurations
//!             OSHT1 is source of the OneShot trip
//!             TZA is configured for Setting Low, TZB is configured to Setting High
//!         Interrupt Configurations
//!             Interrupt is configured for OST trip
//!
//!     myGPIO0 and InputXbar and PwmXbar
//!         GPIO6 is configured in Output Mode and is connected to InputXbar13
//!         This InputXbar instance is connected to the PwmXbar instance that connects to trip
//!         This is used for triggering the Trip Input
//!
//!                                 Trip Signal Routing
//!         +--------+    +-----------------+    +-------+       +---------------+
//!         |        |    |                 |    |       |    -->| CBC1 (MCPWM0) |
//!         | GPIO6  |--->| INPUTXBAR_IN13  |--->|PWMXBAR|---|   +---------------+
//!         |        |    |                 |    |       |    -->| OSHT1(MCPWM1) |
//!         +--------+    +-----------------+    +-------+       +---------------+
//!
//!         \note 
//!             If external trip is used by the user, please configure GPIO6 as input mode and remove
//!             the GPIO6 driving code from the example
//! 
//!  \b External \b Connections \n
//!     Observe the trip input on GPIO6:
//!         Observe J4 32 - GPIO6  - Trip Input
//!     Monitor the MCPWM pins for the waveforms:
//!         Observe J4 40 - GPIO0  - myMCPWM0 Output A1
//!         Observe J4 39 - GPIO1  - myMCPWM0 Output B1
//!         Observe J4 38 - GPIO2  - myMCPWM0 Output A2
//!         Observe J4 37 - GPIO3  - myMCPWM0 Output B2
//!         Observe J4 36 - GPIO4  - myMCPWM0 Output A3
//!         Observe J4 35 - GPIO5  - myMCPWM0 Output B3
//!         Observe J1 7  - GPIO12 - myMCPWM1 Output A1
//!         Observe J2 19 - GPIO29 - myMCPWM1 Output B1
//
//
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2025 Texas Instruments Incorporated - http://www.ti.com/
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//#############################################################################

//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "board.h"

#define MAX_TRIP_ISR_COUNT 10U
//
// Global Variables
//
volatile uint32_t gTripIsrCount = 0;

__interrupt void INT_myMCPWM0_ISR(void);
__interrupt void INT_myMCPWM1_ISR(void);

void main(void)
{
    //
    // Initialize global variables
    //

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Disable pin locks and enable internal pull-ups.
    //
    Device_initGPIO();

    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // Disable sync(Freeze clock to PWM as well)
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Configure mcpwm1, mcpwm2
    //
    Board_init();

    //
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Enable Global Interrupt (INTM) and real time interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // IDLE loop. Just sit and loop forever (optional):
    //
    for(;;)
    {   

        // Toggle the GPIO with Delay
        GPIO_togglePin(myGPIO0);
        DEVICE_DELAY_US(1000000);
        
    }
}

//
// Interrupt Service Routine for myMCPWM0 CBC Trip
//
__interrupt void INT_myMCPWM0_ISR(void)
{
    // 
    // This is a status Flag set to know which Trip is triggered.
    //
    volatile uint32_t tripFalg = MCPWM_getTripZoneFlagStatus(myMCPWM0_BASE);
    
    //
    // Clear the Trip flag
    //
    MCPWM_clearTripZoneFlagStatus(myMCPWM0_BASE, tripFalg);

    /* switch case on the trip flag to perform action related to the trip */

    //
    // Clear Gloabl Interrupt Flag
    //
    MCPWM_clearInterrupt(myMCPWM0_BASE, MCPWM_INT_TZ_CBC);
    
    // 
    // Clear the Global Interrupt Flag for myMCPWM0 to let the ISR trigger again.
    //
    MCPWM_clearGlobalInterrupt(myMCPWM0_BASE);

    gTripIsrCount++;
}


//
// Interrupt Service Routine for myMCPWM1 OneShot Trip
//
__interrupt void INT_myMCPWM1_ISR(void)
{   

    //
    // This is a status Flag set to know which Trip is triggered.
    //
    volatile uint32_t tripFalg = MCPWM_getTripZoneFlagStatus(myMCPWM1_BASE);
    
    //
    // switch case on the trip flag to perform action related to the trip
    // Clear the Trip flag
    //
    MCPWM_clearTripZoneFlagStatus(myMCPWM1_BASE, tripFalg);

    //
    // wait for gTripIsrCount > MAX_TRIP_ISR_COUNT and then clear the OneShot Trip
    //
    if(gTripIsrCount > MAX_TRIP_ISR_COUNT)
    {   
        gTripIsrCount = 0;
        //
        // Clear the OneShot Trip
        // This flag needs to be cleared to clear the OneShot Trip
        //
        MCPWM_clearInterrupt(myMCPWM1_BASE, MCPWM_INT_TZ_OST);
    }
    else
    {
        //
        // Do Nothing
        //
    }

    //
    // Clear the Global Interrupt Flag for myMCPWM1 to let the ISR trigger again.
    //
    MCPWM_clearGlobalInterrupt(myMCPWM1_BASE);

    //
    // Clear Interrupt
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP2);

}
