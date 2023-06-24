//#############################################################################
//
// FILE:  dcc_ex2_single_shot measurement.c
//
// TITLE:  DCC Single shot Clock measurement
//
//! \addtogroup driver_example_list
//! <h1>DCC Single shot Clock measurement</h1>
//!
//! This program demonstrates Single Shot measurement of the INTOSC2
//! clock post trim using XTAL as the reference clock.
//!
//! The Dual-Clock Comparator Module 0 is used for the clock measurement.
//! The clocksource0 is the reference clock (Fclk0 = 20Mhz) and the
//! clocksource1 is the clock that needs to be measured (Fclk1 = 10Mhz).
//! Since the frequency of the clock1 needs to be measured an initial seed is
//! set to the max value of the counter.
//!
//! Please refer to the TRM for details on counter seed values to be set.
//!
//! \note In this device, by default, the XTAL is disabled and INTOSC2 is
//! configured as the PLL source.
//! To use XTAL (of frequency 20MHz) as the PLL source, update the device.h file
//!  with following changes :
//! - Comment the line #define USE_PLL_SRC_INTOSC
//! - Uncomment the line #define USE_PLL_SRC_XTAL
//! If you are using a XTAL with different frequency, update the macros
//! DEVICE_OSCSRC_FREQ, DEVICE_SETCLOCK_CFG, DEVICE_SYSCLK_FREQ accordingly.
//!
//! To run this example, XTAL needs to be enabled. XTAL is enabled if you use
//! it as the PLL source. You can also enable it by using the function
//! \e SysCtl_turnOnOsc(SYSCTL_OSCSRC_XTAL)
//!
//! \b External \b Connections \n
//!   - None
//!
//! \b Watch \b Variables \n
//!  - \b result - Status if the INTOSC2 clock measurement
//!       completed successfully.
//!  - \b meas_freq1 - measured clock frequency, in this case for INTOSC2.
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
uint32_t  result     = FAIL;
float32_t meas_freq1 = 0.0F;

void main(void)
{
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
    // Check if XTAL is enabled
    //
    if((HWREGH(CLKCFG_BASE + SYSCTL_O_XTALCR) & SYSCTL_XTALCR_OSCOFF) != 0)
    {
        //
        // XTAL is not enabled!!
        //
        ESTOP0;
    }

    //
    // Measure the frequency of INTOSC2 using XTAL as reference clock
    // Clk1 = INTOSC2
    // CLk2 = XTAL (Frequency = 20MHz)
    // Tolerance = 1%
    // Allowable Frequency Tolerance = 0% (update as per the error in the XTAL frequency)
    // SysClk Freq = 120MHz
    //
    meas_freq1 = DCC_measureClockFrequency(DCC0_BASE,
                                          DCC_COUNT1SRC_INTOSC2,
                                          DCC_COUNT0SRC_XTAL, 20.0F,
                                          1.0F, 0.0F, 120.0F);

    //
    // Measured clock frequency of INTOSC2.
    // Value of INTOSC2 freq can be checked in the device datasheet
    //
    if ((meas_freq1 >= 9.7F) && (meas_freq1 <= 10.3F))
    {
        result = PASS;
    }
    else
    {
        result = FAIL;
    }

    ESTOP0;
}
