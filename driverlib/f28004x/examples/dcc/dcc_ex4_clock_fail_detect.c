//#############################################################################
//
// FILE:  dcc_ex4_clock_fail_detect.c
//
// TITLE:  DCC Clock Fail Detection
//
//! \addtogroup driver_example_list
//! <h1>DCC Detection of clock failure</h1>
//!
//! This program demonstrates clock failure detection on continuous
//! monitoring of the PLL Clock in the system using XTAL as the osc
//! clock source. Once the oscillator clock fails, it would trigger
//! a DCC error interrupt, causing the decrement/ reload of counters
//! to stop. In this examples, the clock failure is simulated by
//! turning off the XTAL oscillator. Once the ISR is serviced, the
//! osc source is changed to INTOSC1 and the PLL is turned off.
//!
//! The Dual-Clock Comparator Module 0 is used for the clock monitoring.
//! The clocksource0 is the reference clock (Fclk0 = 20Mhz) and the
//! clocksource1 is the clock that needs to be monitored (Fclk1 = 200Mhz).
//! Seed is the value that gets loaded into the Counter.
//!
//! \note In the current example, the XTAL is expected to be a Resonator
//! running in Crystal mode which is later switched off to simulate the clock
//! failure. If an SE Crystal is used, you will need to physically disconnect
//! the clock on the board.
//!
//! Please refer to the TRM for details on counter seed values to be set.
//! Note : When running in flash configuration it is good to do a reset
//! & restart after loading the example to remove any stale flags/states.
//!
//! \b External \b Connections \n
//!  - None
//!
//! \b Watch \b Variables \n
//!  - \b status/result - Status of the clock failure detection
//!
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

//
// Defines
//
#define PASS 0
#define FAIL 1

//
// Globals
//
uint32_t result = FAIL, isr_enter = 0;
uint16_t pass= 0;

//
// Function Prototypes
//
__interrupt void DCC_ISR();

void main(void)
{
    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    //Initialize PIE and clear PIE registers. Disables CPU interrupts
    //
    Interrupt_initModule();

    //
    //Initialize the PIE vector table with pointers to the shell Interrupt
    //Service Routines (ISR)
    //
    Interrupt_initVectorTable();

    //
    // Clear Error & Done Flag
    //
    DCC_clearErrorFlag(DCC0_BASE);
    DCC_clearDoneFlag(DCC0_BASE);

    //
    // Interrupts that are used in this example are re-mapped to ISR functions
    // found within this file.
    //
    Interrupt_register(INT_DCC, &DCC_ISR);

    //
    // Enable interrupts required for this example
    //
    Interrupt_enable(INT_DCC);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Continuous monitor of PLL clock using XTAL as reference clock
    // CLk1 = PLLRAW (Frequency = 200MHz)
    // CLk0 = XTAL   (Frequency = 20MHz)
    // Tolerance = 1%
    // Allowable Frequency Tolerance = 0% (update as per the error in the XTAL frequency)
    // SysClk Freq = 100MHz
    //
    // Note: Update the parameters in case you re using different PLL or XTAL
    // frequencies,
    //
    DCC_continuousMonitor(DCC0_BASE,
                          DCC_COUNT1SRC_PLL, 200.0F,
                          DCC_COUNT0SRC_XTAL, 20.0F,
                          1.0F, 0.0F, 100.0F);

    //
    // Disable MCD to prevent NMI generation due to missing clock
    // MCD to be handled by the DCC
    //
    SysCtl_disableMCD();

    //
    // Turn off XTAL to simulate a missing clock
    //
    EALLOW;
    HWREGH(CLKCFG_BASE + SYSCTL_O_XTALCR) |= SYSCTL_XTALCR_OSCOFF;
    EDIS;

    //
    // Wait till the ISR is hit on clock failure
    //
    while(isr_enter != 0x1U);

    //
    // Configure oscillator source to INTOSC1
    //
    SysCtl_selectOscSource(SYSCTL_OSCSRC_OSC1);

    //
    // Delay of at least 60 OSCCLK cycles
    //
    SysCtl_delay(11U);

    //
    // Turn off PLL
    //
    EALLOW;
    HWREGH(CLKCFG_BASE + SYSCTL_O_SYSPLLCTL1) &=
        ~SYSCTL_SYSPLLCTL1_PLLEN;
    EDIS;

    //
    // Delay of at least 66 OSCCLK cycles required post
    // powerdown of PLL
    //
    SysCtl_delay(12U);

    //
    // Status of the clock failure detection
    //
    if (pass == 0)
    {
        result = FAIL;
    }
    else
    {
        result = PASS;
    }

    ESTOP0;
}

//
// DCC ISR triggered on an error
//
__interrupt void DCC_ISR()
{
    //
    // Shows that the ISR was called
    //
    isr_enter = 1;

    //
    // A clock failure was detected
    //
    pass++;

    if (DCC_getErrorStatus(DCC0_BASE) == 1U)
    {
        //
        // Clear the Error flag
        //
        DCC_clearErrorFlag(DCC0_BASE);
    }

    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP7);
}

