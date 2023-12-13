//#############################################################################
//
//  File:   Example_F2802xHaltWake.c
//
//  Title:  Device Halt Mode and Wakeup Program.
//
//! \addtogroup example_list
//!  <h1>Device Halt Mode and Wakeup</h1>
//!
//!   This example puts the device into HALT mode. If the lowest
//!   possible current consumption in HALT mode is desired, the
//!   JTAG connector must be removed from the device board while
//!   the device is in HALT mode.
//!
//!   The example then wakes up the device from HALT using GPIO0.
//!   GPIO0 wakes the device from HALT mode when a high-to-low
//!   signal is detected on the pin. This pin must be pulsed by
//!   an external agent for wakeup.
//!
//!   The wakeup process begins as soon as GPIO0 is held low for the
//!   time indicated in the device datasheet. After the
//!   device wakes up, GPIO1 can be observed to go high.
//!
//!   GPIO0 is configured as the LPM wakeup pin to trigger a
//!   WAKEINT interrupt upon detection of a low pulse.
//!   Initially, pull GPIO0 high externally. To wake device
//!   from halt mode, pull GPIO0 low for at least the crystal
//!   startup time + 2 OSCLKS, then pull it high again.
//!
//!   To observe when device wakes from HALT mode, monitor
//!   GPIO1 with an oscilloscope (toggled in WAKEINT ISR)
//
//#############################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:
// Copyright (C) 2009-2023 Texas Instruments Incorporated - http://www.ti.com/
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
#include "common/include/gpio.h"
#include "common/include/pie.h"
#include "common/include/pll.h"
#include "common/include/pwr.h"
#include "common/include/wdog.h"

//
// Function Prototypes
//
__interrupt void wakeint_isr(void);      // ISR for WAKEINT

//
// Globals
//
CLK_Handle myClk;
FLASH_Handle myFlash;
GPIO_Handle myGpio;
PIE_Handle myPie;

//
// Main
//
void main(void)
{
    CPU_Handle myCpu;
    PLL_Handle myPll;
    PWR_Handle myPwr;
    WDOG_Handle myWDog;

    //
    // Initialize all the handles needed for this application
    //
    myClk = CLK_init((void *)CLK_BASE_ADDR, sizeof(CLK_Obj));
    myCpu = CPU_init((void *)NULL, sizeof(CPU_Obj));
    myFlash = FLASH_init((void *)FLASH_BASE_ADDR, sizeof(FLASH_Obj));
    myGpio = GPIO_init((void *)GPIO_BASE_ADDR, sizeof(GPIO_Obj));
    myPie = PIE_init((void *)PIE_BASE_ADDR, sizeof(PIE_Obj));
    myPll = PLL_init((void *)PLL_BASE_ADDR, sizeof(PLL_Obj));
    myPwr = PWR_init((void *)PWR_BASE_ADDR, sizeof(PWR_Obj));
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
    // Initialize GPIO
    // Enable Pull-ups
    //
    GPIO_setPullUp(myGpio, GPIO_Number_0, GPIO_PullUp_Enable);
    GPIO_setPullUp(myGpio, GPIO_Number_1, GPIO_PullUp_Enable);

    //
    // GPIO1 set in the ISR to indicate device woken up.
    //
    GPIO_setDirection(myGpio, GPIO_Number_1, GPIO_Direction_Output);

    //
    // Choose GPIO0 pin for lpm wakeup
    //
    GPIO_lpmSelect(myGpio,GPIO_Number_0);

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
    // Enable CPU INT1 which is connected to WakeInt
    //
    CPU_enableInt(myCpu, CPU_IntNumber_1);

    //
    // Enable WAKEINT in the PIE: Group 1 interrupt 8
    //
    PIE_enableInt(myPie, PIE_GroupNumber_1, PIE_InterruptSource_WAKE);

    PIE_clearInt(myPie, PIE_GroupNumber_1);

    //
    // Enable global Interrupts
    //
    CPU_enableGlobalInts(myCpu);

    //
    // Only enter Standby mode when PLL is not in limp mode.
    //
    if ( PLL_getClkStatus(myPll) != PLL_PLLSTS_MCLKSTS_BITS)
    {
        //
        // LPM mode = Standby
        //
        PWR_setLowPowerMode(myPwr, PWR_LowPowerMode_Halt);
    }

    //
    // Force device into STANDBY
    //
    
    //
    // Device waits in IDLE until falling edge on GPIO0/XNMI pin wakes device
    // from Standby mode.
    //
    IDLE;
    
    for(;;)
    {
        // Loop here after wake-up.
    }
}

//
// wakeint_isr - ISR for WAKEINT - Will be executed when low pulse triggered on
// GPIO0 pin
//
__interrupt void
wakeint_isr(void)
{
    //
    // TOGGLE GPIO1 in the ISR - monitored with oscilloscope
    //
    GPIO_toggle(myGpio, GPIO_Number_1);

    PIE_clearInt(myPie, PIE_GroupNumber_1);
}

//
// End of File
//

