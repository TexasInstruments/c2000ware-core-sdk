//#############################################################################
//
// FILE:  dcc_ex3_continuous_monitoring_of_clock.c
//
// TITLE:  DCC Continuous clock monitoring
//
//! \addtogroup driver_example_list
//! <h1>DCC Continuous clock monitoring</h1>
//!
//! This program demonstrates continuous monitoring of PLL Clock in the
//! system using INTOSC2 as the reference clock. This would trigger an
//! interrupt on any error, causing the decrement/ reload of counters to
//! stop.
//!
//! The Dual-Clock Comparator Module 0 is used for the clock monitoring.
//! The clocksource0 is the reference clock (Fclk0 = 10Mhz) and the
//! clocksource1 is the clock that needs to be monitored (Fclk1 = 200Mhz).
//! The clock0 and clock1 seed are set to achieve a window of 300us.
//! Seed is the value that gets loaded into the Counter.
//! For the sake of demo a slight variance is given to clock1 seed value
//! to generate an error on continuous monitoring.
//!
//! Please refer to the TRM for details on counter seed values to be set.
//! Note : When running in flash configuration it is good to do a reset
//! & restart after loading the example to remove any stale flags/states.
//!
//! \b External \b Connections \n
//!  - None
//!
//! \b Watch \b Variables \n
//!  - \b status/result - Status of the PLLRAW clock monitoring
//!  - \b cnt0 - Counter0 Value measure when error is generated
//!  - \b cnt1 - Counter1 Value measure when error is generated
//!  - \b valid - Valid0 Value measure when error is generated
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
// Calculating Counter0 & Valid Seed Value with +/-1% tolerance.
// INTOSC2 has  frequency variance of +/-3%
//

// If Fclk1>Fclk0, Async. Error (In Clock0 cycles) = 2 + 2*(Fsysclk/Fclk0) = 22
// Digitization error (In Clock0 cycles) = 8
// DCC Error = Async. Error + Digitization error = 30
//
// Window (in Cycles) = (DCC Error) / (0.01 * Tolerance)
// Window = 30 / (0.01 * 1) = 3000
//
// Frequency Error Allowed (In Clock0 Cycles)
//                       = Window * (Allowable Frequency Tolerance (in %) / 100)
//                       = 3000 * (3/100) = 90
//
// Total Error = DCC Error + Frequency Error Allowed = 30 + 90 = 120
//
// Counter0 = Window - Total Error   = 3000 - 120      = 2880
// Valid0   = 2 * Total Error        = 2 * 120         = 240
// Counter1 = Window x (Fclk1/Fclk0) = 3000 * (200/10) = 60000
//
// To simulate an error, we are configuring count1 seed value as 65000.
//
// Note : Update the values if you are using a different PLL frequency
//
#define VALID   240
#define COUNT0  2880
#define COUNT1  65000 // Set with a variance of 5000 counts over 60000



//
// Globals
//
uint32_t result = FAIL, pass_base = 0 , isr_enter = 0;
uint32_t cnt0 = 0,cnt1 = 0,valid = 0;

//
// Function Prototypes
//
bool DCC_Continuous_StopOnError(uint32_t base,
                                DCC_Count0ClockSource clk0src,
                                DCC_Count1ClockSource clk1src,
                                uint32_t dccCounterSeed0,
                                uint32_t dccCounterSeed1,
                                uint32_t dccValidSeed0);

__interrupt void DCC_ISR();

void main(void)
{
    bool status;

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
    // Pass calculated counter seed values to monitor the clock
    //
    status = DCC_Continuous_StopOnError(DCC0_BASE,
                                        DCC_COUNT0SRC_INTOSC2,
                                        DCC_COUNT1SRC_PLL,
                                        COUNT0, COUNT1, VALID);

    //
    // Status of the PLL clock measurement
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

//
// Function to continuously monitor a clock
//
bool DCC_Continuous_StopOnError(uint32_t base,
                                DCC_Count0ClockSource clk0src,
                                DCC_Count1ClockSource clk1src,
                                uint32_t dccCounterSeed0,
                                uint32_t dccCounterSeed1,
                                uint32_t dccValidSeed0)
{

    pass_base = base;

    //
    // Clear Error & Done Flag
    //
    DCC_clearErrorFlag(base);
    DCC_clearDoneFlag(base);

    //
    // Disable DCC
    //
    DCC_disableModule(base);

    //
    // Disable Error Signal
    //
    DCC_disableErrorSignal(base);

    //
    // Disable Done Signal
    //
    DCC_disableDoneSignal(base);

    //
    // Configure Clock Source0 to the reference clock
    // source for PLL
    //
    DCC_setCounter0ClkSource(base, clk0src);

    //
    // Configure Clock Source1 to PLL
    //
    DCC_setCounter1ClkSource(base, clk1src);

    //
    // Configure COUNTER-0, COUNTER-1 & Valid Window
    //
    DCC_setCounterSeeds(base, dccCounterSeed0, dccValidSeed0,
                        dccCounterSeed1);

    //
    // Enable Continuous mode
    //
    DCC_disableSingleShotMode(base);

    //
    // Enable Error Signal
    //
    DCC_enableErrorSignal(base);

    //
    // Enable DCC to start counting
    //
    DCC_enableModule(base);

    //
    // Wait for a window of about 1000uS to detect if an error
    // is generated and ISR is triggered
    //
    DEVICE_DELAY_US(1000);

    //
    // Check if ISR was triggered due to error
    //
    if (isr_enter != 1)
        return false;
    else
        return true;

}

//
// DCC ISR triggered on an error
//
__interrupt void DCC_ISR()
{
    uint32_t base;

    //
    // Pass the DCC base address to the ISR
    //
    base = pass_base;

    //
    // Shows that the ISR was called
    //
    isr_enter = 1;

    if (DCC_getErrorStatus(base) == 1U)
    {
        //
        // Dump the DCC counters into RAM
        //
        cnt0 = DCC_getCounter0Value(base);
        cnt1 = DCC_getCounter1Value(base);
        valid = DCC_getValidCounter0Value(base);

        //
        // Clear the Error flag
        //
        DCC_clearErrorFlag(base);
    }

    //
    // Clear the interrupt at PIE level
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP7);
}

