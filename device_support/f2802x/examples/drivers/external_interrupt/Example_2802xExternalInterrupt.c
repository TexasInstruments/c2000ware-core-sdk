//#############################################################################
//
//  File:   Example_F2802xExternalInterrupt.c
//
//  Title:  F2802x External Interrupt test program.
//
//! \addtogroup example_list
//!  <h1>External Interrupts</h1>
//!
//!   This program sets up GPIO0 as XINT1 and GPIO1 as XINT2.  Two other
//!   GPIO signals are used to trigger the interrupt (GPIO28 triggers
//!   XINT1 and GPIO29 triggers XINT2).  The user is required to
//!   externally connect these signals for the program to work
//!   properly.
//!
//!   XINT1 input is synched to SYSCLKOUT.
//!   XINT2 has a long qualification - 6 samples at 510*SYSCLKOUT each.
//!
//!   GPIO34 will go high outside of the interrupts and low within the
//!   interrupts. This signal can be monitored on a scope.
//!
//!   Each interrupt is fired in sequence - XINT1 first and then XINT2
//!
//!   Watch Variables:
//!   - Xint1Count for the number of times through XINT1 interrupt
//!   - Xint2Count for the number of times through XINT2 interrupt
//!   - LoopCount for the number of times through the idle loop
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
#include "common/include/gpio.h"
#include "common/include/pie.h"
#include "common/include/pll.h"
#include "common/include/pwr.h"
#include "common/include/wdog.h"

//
// Function Prototypes
//
__interrupt void xint1_isr(void);
__interrupt void xint2_isr(void);

CLK_Handle myClk;
FLASH_Handle myFlash;
GPIO_Handle myGpio;
PIE_Handle myPie;

//
// Globals
//
volatile uint32_t Xint1Count;
volatile uint32_t Xint2Count;
uint32_t LoopCount;

//
// Defines
//
#define DELAY (CPU_RATE/1000*6*510)  //Qual period at 6 samples

//
// Main
//
void main(void)
{
    CPU_Handle myCpu;
    PLL_Handle myPll;
    WDOG_Handle myWDog;

    uint32_t TempX1Count;
    uint32_t TempX2Count;

    //
    // Initialize all the handles needed for this application
    //
    myClk = CLK_init((void *)CLK_BASE_ADDR, sizeof(CLK_Obj));
    myCpu = CPU_init((void *)NULL, sizeof(CPU_Obj));
    myFlash = FLASH_init((void *)FLASH_BASE_ADDR, sizeof(FLASH_Obj));
    myGpio = GPIO_init((void *)GPIO_BASE_ADDR, sizeof(GPIO_Obj));
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
    PIE_registerPieIntHandler(myPie, PIE_GroupNumber_1, PIE_SubGroupNumber_4,
                              (intVec_t)&xint1_isr);
    PIE_registerPieIntHandler(myPie, PIE_GroupNumber_1, PIE_SubGroupNumber_5,
                              (intVec_t)&xint2_isr);

    //
    // Clear the counters
    //
    Xint1Count = 0;                 // Count XINT1 interrupts
    Xint2Count = 0;                 // Count XINT2 interrupts
    LoopCount = 0;                  // Count times through idle loop

    //
    // Enable XINT1 and XINT2 in the PIE: Group 1 interrupt 4 & 5
    // Enable INT1 which is connected to WAKEINT
    //
    PIE_enableInt(myPie, PIE_GroupNumber_1, PIE_InterruptSource_XINT_1);
    PIE_enableInt(myPie, PIE_GroupNumber_1, PIE_InterruptSource_XINT_2);
    CPU_enableInt(myCpu, CPU_IntNumber_1);

    //
    // Enable Global Interrupts
    //
    CPU_enableGlobalInts(myCpu);

    //
    // GPIO28 & GPIO29 are outputs, start GPIO28 high and GPIO29 low
    //
    GPIO_setHigh(myGpio, GPIO_Number_28);
    GPIO_setMode(myGpio, GPIO_Number_28, GPIO_28_Mode_GeneralPurpose);
    GPIO_setDirection(myGpio, GPIO_Number_28, GPIO_Direction_Output);

    GPIO_setLow(myGpio, GPIO_Number_29);
    GPIO_setMode(myGpio, GPIO_Number_29, GPIO_29_Mode_GeneralPurpose);
    GPIO_setDirection(myGpio, GPIO_Number_29, GPIO_Direction_Output);

    //
    // GPIO0 and GPIO1 are inputs
    //
    GPIO_setMode(myGpio, GPIO_Number_0, GPIO_0_Mode_GeneralPurpose);
    GPIO_setDirection(myGpio, GPIO_Number_0, GPIO_Direction_Input);
    GPIO_setQualification(myGpio, GPIO_Number_0, GPIO_Qual_Sync);

    GPIO_setMode(myGpio, GPIO_Number_1, GPIO_1_Mode_GeneralPurpose);
    GPIO_setDirection(myGpio, GPIO_Number_1, GPIO_Direction_Input);
    GPIO_setQualification(myGpio, GPIO_Number_1, GPIO_Qual_Sample_6);
    GPIO_setQualificationPeriod(myGpio, GPIO_Number_1, 0xFF);

    //
    // GPIO0 is XINT1, GPIO1 is XINT2
    //
    GPIO_setExtInt(myGpio, GPIO_Number_0, CPU_ExtIntNumber_1);
    GPIO_setExtInt(myGpio, GPIO_Number_1, CPU_ExtIntNumber_2);

    //
    // Configure XINT1
    //
    PIE_setExtIntPolarity(myPie, CPU_ExtIntNumber_1,
                          PIE_ExtIntPolarity_FallingEdge);
    PIE_setExtIntPolarity(myPie, CPU_ExtIntNumber_2,
                          PIE_ExtIntPolarity_RisingEdge);

    //
    // Enable XINT1 and XINT2
    //
    PIE_enableExtInt(myPie, CPU_ExtIntNumber_1);
    PIE_enableExtInt(myPie, CPU_ExtIntNumber_2);

    //
    // GPIO34 will go low inside each interrupt.  Monitor this on a scope
    //
    GPIO_setMode(myGpio, GPIO_Number_34, GPIO_34_Mode_GeneralPurpose);
    GPIO_setDirection(myGpio, GPIO_Number_34, GPIO_Direction_Output);

    for(;;)
    {
        TempX1Count = Xint1Count;
        TempX2Count = Xint2Count;

        //
        // Trigger both XINT1
        //
        GPIO_setHigh(myGpio, GPIO_Number_34);
        GPIO_setLow(myGpio, GPIO_Number_28);

        while(Xint1Count == TempX1Count)
        {
            
        }

        //
        // Trigger both XINT2
        //
        GPIO_setHigh(myGpio, GPIO_Number_34);

        DELAY_US(DELAY);                      // Wait for Qual period

        GPIO_setHigh(myGpio, GPIO_Number_29); // Raise GPIO29, trigger XINT2

        while(Xint2Count == TempX2Count)
        {
            
        }

        //
        // Check that the counts were incremented properly and get ready
        // to start over.
        //
        if(Xint1Count == TempX1Count+1 && Xint2Count == TempX2Count+1)
        {
            LoopCount++;
            GPIO_setHigh(myGpio, GPIO_Number_28);
            GPIO_setLow(myGpio, GPIO_Number_29);
        }
        
        else
        {
            ESTOP0;                 // stop here
        }
    }
}

//
// xint1_isr - 
//
__interrupt void
xint1_isr(void)
{
    GPIO_setLow(myGpio, GPIO_Number_34);

    Xint1Count++;

    //
    // Acknowledge this interrupt to get more from group 1
    //
    PIE_clearInt(myPie, PIE_GroupNumber_1);
}

//
// xint2_isr -
//
__interrupt void
xint2_isr(void)
{
    GPIO_setLow(myGpio, GPIO_Number_34);

    Xint2Count++;

    //
    // Acknowledge this interrupt to get more from group 1
    //
    PIE_clearInt(myPie, PIE_GroupNumber_1);
}

//
// End of File
//

