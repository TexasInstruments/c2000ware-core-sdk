//#############################################################################
//
// FILE:  dcc_ex1_single_shot_verification.c
//
// TITLE:  DCC Single shot Clock verification
//
//! \addtogroup driver_example_list
//! <h1>DCC Single shot Clock verification</h1>
//!
//! This program uses the XTAL clock as a reference clock to verify
//! the frequency of the PLLRAW clock.
//!
//! The Dual-Clock Comparator Module 0 is used for the clock verification.
//! The clocksource0 is the reference clock (Fclk0 = 20Mhz) and the
//! clocksource1 is the clock that needs to be verified (Fclk1 = 200Mhz).
//! Seed is the value that gets loaded into the Counter.
//!
//! Please refer to the TRM for details on counter seed values to be set.
//!
//! \b External \b Connections \n
//!   - None
//!
//! \b Watch \b Variables \n
//!  - \b status/result - Status of the PLLRAW clock verification
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
uint32_t result = FAIL;

//
// Main
//
void main(void)
{
    bool status=0;

    //
    // Initialize device clock and peripherals
    //
    Device_init();

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
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Verify the frequency of PLL clock using the XTAL as reference clock
    // FClk1 = PLLRAW frequency = 200MHz
    // FClk0 = XTAL frequency   = 20MHz
    // Tolerance = 1%
    // Allowable Frequency Tolerance = 0% (update as per the error in the XTAL frequency)
    // SysClk Freq = 100MHz
    //
    // Note: Update the parameters in case you are using different PLL or XTAL
    // frequencies,
    //
    status = DCC_verifyClockFrequency(DCC0_BASE,
                                      DCC_COUNT1SRC_PLL, 200.0F,
                                      DCC_COUNT0SRC_XTAL, 20.0F,
                                      1.0F, 0.0F, 100.0F);

    //
    // Status of the PLLRAW clock verification
    //
    if (!status)
    {
        result = FAIL;
    }
    else
    {
        result = PASS;
    }

    ESTOP0;
}

