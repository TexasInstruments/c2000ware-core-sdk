//#############################################################################
//
// FILE:   epwm_ex18_minimum_deadband_icl.c
//
// TITLE:  ePWM Using Minimum Deadband and ICL 
//
//! \addtogroup driver_example_list
//! <h1>ePWM Minimum Deadband and ICL</h1> 
//!
//! This example configures ePWM2, ePWM3, ePWM4 and ePWM5 as follows
//! (Note: ePWM2 and ePWM3 are configured for demonstration purpose -
//!  i.e they are original ePWM4 and ePWM5 signals respectively)
//!
//! Minimum Deadband:
//!  - ePWM2 is 50 KHz signal Type-4 signal with 55% duty cycle. TBPRD = 2000
//!      - There is an overlap of active high states in A and B between
//!        TBCNT = 900 and 1100
//!  - ePWM4 applies a minimum deadband with 200 SYSCLK cycles delay (1 us).
//!      - The new duty cycle changes to 40%.
//!
//! Illegal Combo Logic:
//!  - ePWM3 is 100 KHz signal Type-4 signal with 50% duty cycle. TBPRD = 1000.
//!  - ePWM5 applies ICL look up table (LUT) logic to perform AND operation
//!    between 5A & 4A and 5B & 4B.
//!
//!  \b External \b Connections \n
//!  - ePWM2A is on GPIO2 and ePWM2B is on GPIO3
//!  - ePWM3A is on GPIO4 and ePWM3B is on GPIO5
//!  - ePWM4A is on GPIO6 and ePWM4B is on GPIO7
//!  - ePWM5A is on GPIO8 and ePWM5B is on GPIO9
//!
//! For LUT1, ePWM4A is input from ICL X-BAR
//! For LUT2, ePWM4B is input from ICL X-BAR
//! ICL LUT and associated decision qualifiers
//! can be visualized in the following truth table:
//!
//! LUT1:
//!     _____________________________________
//!     | ePWM4A | ePWM5A | ePWM5B | ePWM5A | <-- 5A output
//!     |--------|--------|--------|--------|
//!     |    0   |    0   |    X   |    0   |
//!     |    0   |    1   |    X   |    0   |
//!     |    1   |    0   |    X   |    0   |
//!     |    1   |    1   |    X   |    1   |
//!     |________|________|________|________|
//!
//!
//! LUT2:
//!     _____________________________________
//!     | ePWM4B | ePWM5B | ePWM5A | ePWM5B | <-- 5B output
//!     |--------|--------|--------|--------|
//!     |    0   |    0   |    X   |    0   |
//!     |    0   |    1   |    X   |    0   |
//!     |    1   |    0   |    X   |    0   |
//!     |    1   |    1   |    X   |    1   |
//!     |________|________|________|________|
//!
//
//#############################################################################
//
//
// 
// C2000Ware v6.00.01.00
//
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
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
#include "c2000ware_libraries.h"

//
// Main
//
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
    // Set EPWM Clock Divider to 1 to feed 200 MHz SysClock. 
    // Note: Default value is 2.
    //
    SysCtl_setEPWMClockDivider(SYSCTL_EPWMCLK_DIV_1);

    //
    // PinMux and Peripheral Initialization
    //
    Board_init();

    //
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);
    //
    // C2000Ware Library initialization
    //
    C2000Ware_libraries_init();

    //
    // Enable Global Interrupt (INTM) and real time interrupt (DBGM)
    //
    EINT;
    ERTM;

    while(1)
    {
        
    }
}

//
// End of File
//
