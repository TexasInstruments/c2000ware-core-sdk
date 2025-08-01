//#############################################################################
//
// FILE:   mcpwm_ex3_deadband.c
//
// TITLE:  MCPWM Basic PWM generation With DeadBand
//
//! \addtogroup driver_example_list
//! <h1>MCPWM Basic PWM generation With DeadBand</h1>
//!
//! This example configures myMCPWM0 and myMCPWM1 as follows
//!     myMCPWM0 
//!         Time Base Configurations 
//!             In Up Down Count Mode for 4000 TBCLKs or 20KHz Frequency for TBCLK of 160MHz
//!         Action Qualifier is configurations
//!             Output A1 : Set High on Counter matches CMPA counting up, set low on CMPA match counting down
//!             Output A2 : Set High on Counter matches CMPA counting up, set low on CMPA match counting down
//!             Output A3 : Set High on Counter matches CMPA counting up, set low on CMPA match counting down
//!         DeadBand
//!             Active High Configuration is selected with 100 TBCLK deadband
//!     
//!     myMCPWM1
//!         Time Base Configurations 
//!             In Up Down Count Mode for 4000 TBCLKs or 20KHz Frequency for TBCLK of 160MHz
//!         Action Qualifier is configurations
//!             Output A1 : Set High on Counter matches CMPA counting up, set low on CMPA match counting down
//!         DeadBand
//!             Disabled Configurations
//!
//!
//!  \b External \b Connections \n
//!     Monitor the MCPWM pins for the waveforms.
//!         Observe J4 40 - GPIO0  - myMCPWM0 Output A1 - Active High Configuration
//!         Observe J4 39 - GPIO1  - myMCPWM0 Output B1 - Active High Configuration
//!         Observe J4 38 - GPIO2  - myMCPWM0 Output A2 - Active High Configuration
//!         Observe J4 37 - GPIO3  - myMCPWM0 Output B2 - Active High Configuration
//!         Observe J4 36 - GPIO4  - myMCPWM0 Output A3 - Active High Configuration
//!         Observe J4 35 - GPIO5  - myMCPWM0 Output B3 - Active High Configuration
//!         Observe J4 7  - GPIO12 - myMCPWM1 Output A1 - Can be used for reference
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
        NOP;
    }
}
