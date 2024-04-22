//#############################################################################
//
//  File:   Example_F2802x0Watchdog.c
//
//  Title:  F2802x0 Watchdog interrupt test program.
//
//! \addtogroup example_list
//!  <h1>Watchdog Interrupt</h1>
//!
//!  This program exercises the watchdog.
//!
//!  First the watchdog is connected to the WAKEINT interrupt of the
//!  PIE block.  The code is then put into an infinite loop.
//!
//!  The user can select to feed the watchdog key register or not
//!  by commenting one line of code in the infinite loop.
//!
//!  If the watchdog key register is fed by the WDOG_clearCounter function
//!  then the WAKEINT interrupt is not taken.  If the key register
//!  is not fed by the  WDOG_clearCounter function then WAKEINT will be taken.
//!
//!  Watch Variables:
//!  - LoopCount for the number of times through the infinite loop
//!  - WakeCount for the number of times through WAKEINT
//
//#############################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:
// Copyright (C) 2009-2024 Texas Instruments Incorporated - http://www.ti.com/
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
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File

#include "common/include/clk.h"
#include "common/include/flash.h"
#include "common/include/pie.h"
#include "common/include/pll.h"
#include "common/include/wdog.h"

//
// Function Prototypes
//
__interrupt void wakeint_isr(void);

//
// Globals
//
uint32_t WakeCount;
uint32_t LoopCount;

CLK_Handle myClk;
FLASH_Handle myFlash;
PIE_Handle myPie;

//
// Main
//
void main(void)
{
    CPU_Handle myCpu;
    PLL_Handle myPll;
    WDOG_Handle myWDog;

    //
    // Initialize all the handles needed for this application 
    //
    myClk = CLK_init((void *)CLK_BASE_ADDR, sizeof(CLK_Obj)); 
    myCpu = CPU_init((void *)NULL, sizeof(CPU_Obj));
    myFlash = FLASH_init((void *)FLASH_BASE_ADDR, sizeof(FLASH_Obj));
    myPie = PIE_init((void *)PIE_BASE_ADDR, sizeof(PIE_Obj));
    myPll = PLL_init((void *)PLL_BASE_ADDR, sizeof(PLL_Obj));
    myWDog = WDOG_init((void *)WDOG_BASE_ADDR, sizeof(WDOG_Obj));

    //
    // Perform basic system initialization
    //
    WDOG_disable(myWDog);
    CLK_enableAdcClock(myClk);
    (*Device_cal)();

    //
    // Select the internal oscillator 1 as the clock source
    //
    CLK_setOscSrc(myClk, CLK_OscSrc_Internal);

    //
    // Setup the PLL for x10 /2 which will yield 50Mhz = 10Mhz * 10 / 2
    //
    PLL_setup(myPll, PLL_Multiplier_10, PLL_DivideSelect_ClkIn_by_2);

    //
    // Disable the PIE and all interrupts
    //
    PIE_disable(myPie);
    PIE_disableAllInts(myPie);
    CPU_disableGlobalInts(myCpu);
    CPU_clearIntFlags(myCpu);

    //
    // If running from flash copy RAM only functions to RAM   
    //
#ifdef _FLASH
    memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (size_t)&RamfuncsLoadSize);
#endif   

    //
    // Setup a debug vector table and enable the PIE
    //
    PIE_setDebugIntVectorTable(myPie);
    PIE_enable(myPie);

    //
    // Register interrupt handlers in the PIE vector table
    //
    PIE_registerPieIntHandler(myPie, PIE_GroupNumber_1, PIE_SubGroupNumber_8, 
                              (intVec_t)&wakeint_isr);

    //
    // Clear the counters
    //
    WakeCount = 0; // Count interrupts
    LoopCount = 0; // Count times through idle loop

    WDOG_enableInt(myWDog); 

    //
    // Enable WAKEINT in the PIE: Group 1 interrupt 8
    // Enable INT1 which is connected to WAKEINT
    //
    PIE_enableInt(myPie, PIE_GroupNumber_1, PIE_InterruptSource_WAKE);
    CPU_enableInt(myCpu, CPU_IntNumber_1);
    CPU_enableGlobalInts(myCpu);

    //
    // Reset the watchdog counter
    //
    WDOG_clearCounter(myWDog);

    //
    // Enable the watchdog
    //
    WDOG_enable(myWDog);

    for(;;) 
    {
        LoopCount++;

        //
        // Uncomment WDOG_clearCounter to just loop here
        // Comment WDOG_clearCounter to take the WAKEINT instead
        //
        WDOG_clearCounter(myWDog);
    }
}

//
// wakeint_isr - 
//
__interrupt void 
wakeint_isr(void)
{
    WakeCount++;

    //
    // Acknowledge this interrupt to get more from group 1
    //
    PIE_clearInt(myPie, PIE_GroupNumber_1);
}

//
// End of File
//

