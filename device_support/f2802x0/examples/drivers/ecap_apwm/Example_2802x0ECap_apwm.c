//#############################################################################
//
//  File:   Example_F2802x0ECap_apwm.c
//
//  Title:  F2802x0 ECAP APWM Example
//
//! \addtogroup example_list
//!  <h1>ECAP Asymmetric PWM</h1>
//!
//!   This program sets up the eCAP pins in the APWM mode.
//!   This program runs at 50 MHz or 40 MHz SYSCLKOUT assuming
//!   a 10 MHz OSCCLK depending on the max frequency allowed
//!   by a particular device.
//!
//!   eCAP1 will come out on the GPIO5 pin.
//!   This pin is configured to vary between 3 Hz and 6 Hz (at 50 MHz
//!   SYSCLKOUT) or 2 Hz and 4 Hz (at 40 MHz SYSCLKOUT) using the
//!   shadow registers to load the next period/compare values.
//!
//!   Monitor eCAP1 pin on GPIO5 for PWM frequency
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
#include "common/include/cap.h"
#include "common/include/wdog.h"

//
// Globals
//
uint16_t direction = 0;

CLK_Handle myClk;
FLASH_Handle myFlash;
GPIO_Handle myGpio;
PIE_Handle myPie;

//
// Main
//
void main(void)
{
    CAP_Handle myCap;
    CPU_Handle myCpu;
    PLL_Handle myPll;
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
    myCap = CAP_init((void *)CAPA_BASE_ADDR, sizeof(CAP_Obj));
    myWDog = WDOG_init((void *)WDOG_BASE_ADDR, sizeof(WDOG_Obj));

    //
    // Perform basic system initialization
    //
    WDOG_disable(myWDog);
    CLK_enableAdcClock(myClk);
    (*Device_cal)();
    CLK_disableAdcClock(myClk);

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
    //
    GPIO_setPullUp(myGpio, GPIO_Number_5, GPIO_PullUp_Enable);
    GPIO_setQualification(myGpio, GPIO_Number_5, GPIO_Qual_Sync);
    GPIO_setMode(myGpio, GPIO_Number_5, GPIO_5_Mode_ECAP1);

    //
    // Setup a debug vector table and enable the PIE
    //
    PIE_setDebugIntVectorTable(myPie);
    PIE_enable(myPie);

    //
    // Setup APWM mode on CAP1, set period and compare registers
    //
    CLK_enableEcap1Clock(myClk);
    CAP_setModeApwm(myCap);                     // Enable APWM mode
    CAP_setApwmPeriod(myCap, 0x01312D00);       // Set Period value
    CAP_setApwmCompare(myCap, 0x00989680);      // Set Compare value
    CAP_clearInt(myCap, CAP_Int_Type_All);      // Clear pending interrupts
    CAP_enableInt(myCap, CAP_Int_Type_CTR_CMP); // enable Compare Equal Int

    //
    // Start counters
    //
    CAP_enableTimestampCounter(myCap);
    for(;;)
    {
        //
        // vary freq
        //
        if(CAP_getCap1(myCap) >= 0x01312D00)
        {
            direction = 0;
        }
        else if(CAP_getCap1(myCap) <= 0x00989680)
        {
            direction = 1;
        }

        //
        // update the period using CAP3 (APRD) shadow register
        //
        if(direction == 0)
        {
            CAP_setApwmShadowPeriod(myCap, CAP_getCap1(myCap) - 500000);
        } 
        else
        {
            CAP_setApwmShadowPeriod(myCap, CAP_getCap1(myCap) + 500000);
        }
    }
}

//
// End of File
//

