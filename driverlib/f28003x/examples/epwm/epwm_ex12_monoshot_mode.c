//#############################################################################
//
// FILE:   epwm_ex12_monoshot_mode.c
//
// TITLE:  Realization of Monoshot mode
//
//! \addtogroup driver_example_list
//! <h1>Realization of Monoshot mode</h1>
//!
//! This example showcases how to generate monoshot PWM output based on external
//! trigger i.e. generating just a single pulse output on receipt of an external
//! trigger. And the next pulse will be generated only when the next trigger
//! comes. The example utilizes external synchronization and T1 action qualifier
//! event features to achieve the desired output.
//!
//! ePWM1 is used to generate the monoshot output and ePWM2 is used an external
//! trigger for that. No external connections are required as ePWM2A is fed
//! as the trigger using Input X-BAR automatically.
//!
//! ePWM1 is configured to generated a single pulse of 0.5us when received
//! an external trigger. This is achieved by enabling the phase synchronization
//! feature and configuring EPWMxSYNCI as EXTSYNCIN1. And this EPWMxSYNCI
//! is also configured as T1 event of action qualifier to set output HIGH while
//! "CTR = PRD" action is used to set output LOW.
//!
//! ePWM2 is configured to generate a 100 KHz signal with a duty of 1% (to
//! simulate a rising edge trigger) which is routed to EXTSYNCIN1 using Input XBAR.
//!
//! Observe GPIO0 (EPWM1A : Monoshot Output) and GPIO2(EPWM2 : External Trigger)
//! on oscilloscope.
//!
//!
//! \b NOTE : In the following example, the ePWM timer is still running in a
//!        continuous mode rather than a one-shot mode thus for more reliable
//!        implementation, refer to CLB based one shot PWM implementation
//!        demonstrated in "clb_ex17_one_shot_pwm" example
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
    // Disable sync(Freeze clock to PWM as well)
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Configure ePWM1, ePWM2 GPIOs and Modules
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

