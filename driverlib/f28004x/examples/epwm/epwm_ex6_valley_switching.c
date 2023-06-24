//#############################################################################
//
// FILE:   epwm_ex6_valley_switching.c
//
// TITLE:  ePWM Using Valley Switching
//
//! \addtogroup driver_example_list
//! <h1>ePWM Valley Switching</h1>
//!
//! This example configures ePWM1 as follows
//!  - ePWM1 with DCAEVT1 forcing the ePWM output LOW
//!  - GPIO25 is used as the input to the INPUT XBAR INPUT1
//!  - INPUT1 (from INPUT XBAR) is used as the source for DCAEVT1
//!  - GPIO25 is set to output and toggled in the main loop to trip the PWM
//!
//!  - ePWM1 with DCBEVT1 forcing the ePWM output LOW
//!  - GPIO25 is used as the input to the INPUT XBAR INPUT1
//!  - INPUT1 (from INPUT XBAR) is used as the source for DCAEVT1
//!  - GPIO25 is set to output and toggled in the main loop to trip the PWM
//!  - DCBEVT1 uses the filtered version of DCBEVT1
//!  - The DCFILT signal uses the valley switching module to delay the
//!  - DCFILT signal by a software defined DELAY value.
//!
//! \b External \b Connections \n
//! - GPIO0 EPWM1A
//! - GPIO1 EPWM1B
//! - GPIO25 TRIPIN1 (Output Pin, toggled through software)
//!
//! \b Watch \b Variables \n
//! - None.
//
//
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2023 Texas Instruments Incorporated - http://www.ti.com/
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

//
// Function Prototypes
//
__interrupt void epwm1ISR(void);

void main(void)
{

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
    // Interrupts that are used in this example are re-mapped to ISR functions
    // found within this file.
    //
    Interrupt_register(INT_EPWM1, &epwm1ISR);

    //
    // Disable sync(Freeze clock to PWM as well). GTBCLKSYNC is applicable
    // only for multiple core devices. Uncomment the below statement if
    // applicable.
    //
    // SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_GTBCLKSYNC);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Configure ePWM1, and TZ GPIOs
    //
    Board_init();
    GPIO_writePin(myGPIO25, 1);

    //
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Enable interrupts required for this example
    //
    Interrupt_enable(INT_EPWM1);

    //
    // Enable Global Interrupt (INTM) and real time interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Delay so the PWM runs for a some time to see the Waveform on
    // scope
    //

    SysCtl_delay(600000U);
    //
    // IDLE loop. Just sit and loop forever (optional):
    //
    for(;;)
    {
        //
        // PULL Trip GPIO LOW from CTR=4000 to 11000
        // PULL Trip GPIO HIGH at CTR=11000
        //
        while(HWREGH(myEPWM1_BASE + EPWM_O_TBCTR) < 4000);
        GPIO_writePin(myGPIO25, 0);
        while(HWREGH(myEPWM1_BASE + EPWM_O_TBCTR) < 11000);
        GPIO_writePin(myGPIO25, 1);
        while(HWREGH(myEPWM1_BASE + EPWM_O_TBCTR) > 3000);
        GPIO_writePin(myGPIO25, 1);
        NOP;
    }
}

interrupt void epwm1ISR(void){

    EPWM_clearTripZoneFlag(myEPWM1_BASE, EPWM_TZ_FLAG_OST | EPWM_TZ_FLAG_DCAEVT1 | EPWM_TZ_FLAG_DCBEVT1 | EPWM_TZ_INTERRUPT);
    EPWM_clearOneShotTripZoneFlag(myEPWM1_BASE, EPWM_TZ_OST_FLAG_DCBEVT1);

    //
    // Clear INT flag for this timer
    //
    EPWM_clearEventTriggerInterruptFlag(myEPWM1_BASE);

    //
    // Acknowledge interrupt group
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP3);

}



