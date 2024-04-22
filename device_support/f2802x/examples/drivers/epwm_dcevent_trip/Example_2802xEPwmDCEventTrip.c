//#############################################################################
//
//  File:   Example_F2802xEpwmDCEventTrip.c
//
//  Title:  Check PWM Digital Compare Event Trip Zone Test
//
//! \addtogroup example_list
//!  <h1>PWM Digital Compare Event Trip Zone</h1>
//!
//!   This example configures ePWM1 and ePWM2
//!
//!   2 Examples are included:
//!   - ePWM1 has DCAEVT1 as a one shot trip source
//!   - ePWM2 has DCAEVT2 as a cycle by cycle trip source
//!   - ePWM3 reacts to DCAEVT2 and DCBEVT1 events
//!
//!   During the test, monitor ePWM1, ePWM2, or ePWM3 outputs
//!   on a scope pull TZ1 low and leave TZ2 high to create
//!   a DCAEVT1, DCAEVT2, DCBEVT1 and DCBEVT2.
//!     - EPWM1A is on GPIO0
//!     - EPWM1B is on GPIO1
//!     - EPWM2A is on GPIO2
//!     - EPWM2B is on GPIO3
//!     - EPWM3A is on GPIO4
//!     - EPWM3B is on GPIO5
//!
//!  DCAEVT1, DCAEVT2, DCBEVT1 and DCBEVT2 are all defined as
//!  true when TZ1 is low and TZ2 is high
//!   - ePWM1 will react to DCAEVT1 as a 1-shot trip. \n
//!           The trip event will pull EPWM1A high. \n
//!           The trip event will pull EPWM1B low. \n
//!   - ePWM2 will react to DCAEVT2 as a cycle-by-cycle trip. \n
//!           The trip event will pull EPWM2A high. \n
//!           The trip event will pull EPWM2B low. \n
//!   - ePWM3 will react to DCAEVT2 and DCBEVT1 events. \n
//!           The DCAEVT2 event will pull EPWM3A high. \n
//!           The DCBEVT1 event will pull EPWM3B low. \n
//
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
#include "common/include/pwm.h"
#include "common/include/wdog.h"

//
// Function Prototypes
//
void InitEPwm1Example(void);
void InitEPwm2Example(void);
void InitEPwm3Example(void);
__interrupt void epwm1_tzint_isr(void);
__interrupt void epwm2_tzint_isr(void);
__interrupt void epwm3_tzint_isr(void);

//
// Globals
//
uint32_t  EPwm1TZIntCount;
uint32_t  EPwm2TZIntCount;
uint32_t  EPwm3TZIntCount;

CLK_Handle myClk;
FLASH_Handle myFlash;
GPIO_Handle myGpio;
PIE_Handle myPie;
PWM_Handle myPwm1, myPwm2, myPwm3;

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
    myGpio = GPIO_init((void *)GPIO_BASE_ADDR, sizeof(GPIO_Obj));
    myPie = PIE_init((void *)PIE_BASE_ADDR, sizeof(PIE_Obj));
    myPll = PLL_init((void *)PLL_BASE_ADDR, sizeof(PLL_Obj));
    myPwm1 = PWM_init((void *)PWM_ePWM1_BASE_ADDR, sizeof(PWM_Obj));
    myPwm2 = PWM_init((void *)PWM_ePWM2_BASE_ADDR, sizeof(PWM_Obj));
    myPwm3 = PWM_init((void *)PWM_ePWM3_BASE_ADDR, sizeof(PWM_Obj));
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

    // Setup the PLL for x10 /2 which will yield 50Mhz = 10Mhz * 10 / 2
    PLL_setup(myPll, PLL_Multiplier_10, PLL_DivideSelect_ClkIn_by_2);

    // Disable the PIE and all interrupts
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
    // For this case just init GPIO pins for ePWM1, ePWM2, and TZ pins
    //
    GPIO_setPullUp(myGpio, GPIO_Number_0, GPIO_PullUp_Disable);
    GPIO_setPullUp(myGpio, GPIO_Number_1, GPIO_PullUp_Disable);
    GPIO_setMode(myGpio, GPIO_Number_0, GPIO_0_Mode_EPWM1A);
    GPIO_setMode(myGpio, GPIO_Number_1, GPIO_1_Mode_EPWM1B);

    GPIO_setPullUp(myGpio, GPIO_Number_2, GPIO_PullUp_Disable);
    GPIO_setPullUp(myGpio, GPIO_Number_3, GPIO_PullUp_Disable);
    GPIO_setMode(myGpio, GPIO_Number_2, GPIO_2_Mode_EPWM2A);
    GPIO_setMode(myGpio, GPIO_Number_3, GPIO_3_Mode_EPWM2B);

    GPIO_setPullUp(myGpio, GPIO_Number_4, GPIO_PullUp_Disable);
    GPIO_setPullUp(myGpio, GPIO_Number_5, GPIO_PullUp_Disable);
    GPIO_setMode(myGpio, GPIO_Number_4, GPIO_4_Mode_EPWM3A);
    GPIO_setMode(myGpio, GPIO_Number_5, GPIO_5_Mode_EPWM3B);

    GPIO_setPullUp(myGpio, GPIO_Number_12, GPIO_PullUp_Enable);
    GPIO_setQualification(myGpio, GPIO_Number_12, GPIO_Qual_ASync);
    GPIO_setMode(myGpio, GPIO_Number_12, GPIO_12_Mode_TZ1_NOT);

    GPIO_setPullUp(myGpio, GPIO_Number_16, GPIO_PullUp_Enable);
    GPIO_setQualification(myGpio, GPIO_Number_16, GPIO_Qual_ASync);
    GPIO_setMode(myGpio, GPIO_Number_16, GPIO_16_Mode_TZ2_NOT);

    GPIO_setPullUp(myGpio, GPIO_Number_17, GPIO_PullUp_Enable);
    GPIO_setQualification(myGpio, GPIO_Number_17, GPIO_Qual_ASync);
    GPIO_setMode(myGpio, GPIO_Number_17, GPIO_17_Mode_TZ3_NOT);

    //
    // Setup a debug vector table and enable the PIE
    //
    PIE_setDebugIntVectorTable(myPie);
    PIE_enable(myPie);

    //
    // Register interrupt handlers in the PIE vector table
    //
    PIE_registerPieIntHandler(myPie, PIE_GroupNumber_2, PIE_SubGroupNumber_1,
                              (intVec_t)&epwm1_tzint_isr);
    PIE_registerPieIntHandler(myPie, PIE_GroupNumber_2, PIE_SubGroupNumber_2,
                              (intVec_t)&epwm2_tzint_isr);
    PIE_registerPieIntHandler(myPie, PIE_GroupNumber_2, PIE_SubGroupNumber_3,
                              (intVec_t)&epwm3_tzint_isr);

    CLK_disableTbClockSync(myClk);

    InitEPwm1Example();
    InitEPwm2Example();
    InitEPwm3Example();

    CLK_enableTbClockSync(myClk);

    //
    // Initialize counters
    //
    EPwm1TZIntCount = 0;
    EPwm2TZIntCount = 0;
    EPwm3TZIntCount = 0;

    //
    // Enable CPU INT3 which is connected to EPWM1-3 INT
    //
    CPU_enableInt(myCpu, CPU_IntNumber_2);

    //
    // Enable EPWM INTn in the PIE: Group 2 interrupt 1-3
    //
    PIE_enablePwmTzInt(myPie, PWM_Number_1);
    PIE_enablePwmTzInt(myPie, PWM_Number_2);
    PIE_enablePwmTzInt(myPie, PWM_Number_3);

    //
    // Enable global Interrupts and higher priority real-time debug events
    //
    CPU_enableGlobalInts(myCpu);
    CPU_enableDebugInt(myCpu);

    for(;;)
    {
        __asm(" NOP");
    }
}

//
// epwm1_tzint_isr - 
//
__interrupt void
epwm1_tzint_isr(void)
{
    EPwm1TZIntCount++;

    //
    // Do not clear any EPWM flags so we only take this
    // interrupt once
    //

    //
    // Acknowledge this interrupt to receive more interrupts from group 2
    //
    PIE_clearInt(myPie, PIE_GroupNumber_2);
}

//
// epwm2_tzint_isr - 
//
__interrupt void
epwm2_tzint_isr(void)
{
    EPwm2TZIntCount++;

    //
    // Clear the flags - we will continue to take this interrupt until the 
    // TZ pin goes high
    //
    PWM_clearTripZone(myPwm2, PWM_TripZoneFlag_CBC);
    PWM_clearTripZone(myPwm2, PWM_TripZoneFlag_Global);

    //
    // Acknowledge this interrupt to receive more interrupts from group 2
    //
    PIE_clearInt(myPie, PIE_GroupNumber_2);
}

//
// epwm3_tzint_isr -
//
__interrupt void
epwm3_tzint_isr(void)
{
    EPwm3TZIntCount++;

    PWM_clearTripZone(myPwm3, PWM_TripZoneFlag_DCAEVT2);
    PWM_clearTripZone(myPwm3, PWM_TripZoneFlag_DCAEVT1);
    PWM_clearTripZone(myPwm3, PWM_TripZoneFlag_Global);

    //
    // Acknowledge this interrupt to receive more interrupts from group 2
    //
    PIE_clearInt(myPie, PIE_GroupNumber_2);
}

//
// InitEPwm1Example - 
//
void
InitEPwm1Example()
{
    CLK_enablePwmClock(myClk, PWM_Number_1);

    PWM_setPeriod(myPwm1, 6000);    // Set timer period
    PWM_setPhase(myPwm1, 0x0000);   // Phase is 0
    PWM_setCount(myPwm1, 0x0000);   // Clear counter

    //
    // Setup TBCLK
    //
    PWM_setCounterMode(myPwm1, PWM_CounterMode_UpDown); // Count up/down
    PWM_disableCounterLoad(myPwm1);                   // Disable phase loading
    
    //
    // Clock ratio to SYSCLKOUT
    //
    PWM_setHighSpeedClkDiv(myPwm1, PWM_HspClkDiv_by_4); 
    
    PWM_setClkDiv(myPwm1, PWM_ClkDiv_by_4);

    //
    // Load registers every ZERO
    //
    PWM_setShadowMode_CmpA(myPwm1, PWM_ShadowMode_Shadow);
    PWM_setShadowMode_CmpB(myPwm1, PWM_ShadowMode_Shadow);
    PWM_setLoadMode_CmpA(myPwm1, PWM_LoadMode_Zero);
    PWM_setLoadMode_CmpB(myPwm1, PWM_LoadMode_Zero);

    //
    // Setup compare
    //
    PWM_setCmpA(myPwm1, 3000);

    //
    // Set actions
    //
    
    //
    // Set PWM1A on CAU
    //
    PWM_setActionQual_CntUp_CmpA_PwmA(myPwm1, PWM_ActionQual_Set);
    
    //
    // Clear PWM1B on CAD
    
    PWM_setActionQual_CntDown_CmpA_PwmA(myPwm1, PWM_ActionQual_Clear);

    PWM_setActionQual_CntUp_CmpA_PwmB(myPwm1, PWM_ActionQual_Clear);
    
    //
    // Clear PWM1B on CAD
    //
    PWM_setActionQual_CntDown_CmpA_PwmB(myPwm1, PWM_ActionQual_Set);

    //
    // Define an event (DCAEVT1) based on TZ1 and TZ2
    //
    PWM_setDigitalCompareInput(myPwm1, PWM_DigitalCompare_A_High, 
                               PWM_DigitalCompare_InputSel_TZ1);  // DCAH = TZ1
    PWM_setDigitalCompareInput(myPwm1, PWM_DigitalCompare_A_Low, 
                               PWM_DigitalCompare_InputSel_TZ2);  // DCAL = TZ2
    //
    // DCAEVT1 =  DCAH low, DCAL high;
    //
    PWM_setTripZoneDCEventSelect_DCAEVT1(myPwm1, 
                                         PWM_TripZoneDCEventSel_DCxHL_DCxLH);
    //
    // DCAEVT1 = DCAEVT1 (not filtered), Take async path
    //
    PWM_setDigitalCompareAEvent1(myPwm1, false, true, false, false);

    //
    // Enable DCAEVT1 as a one-shot trip source
    // Note: DCxEVT1 events can be defined as one-shot.
    //       DCxEVT2 events can be defined as cycle-by-cycle.
    //
    PWM_enableTripZoneSrc(myPwm1, PWM_TripZoneSrc_OneShot_CmpA);

    //
    // Because DCAEVT1 is causes a trip event (in this case one-shot) we need 
    // to use the TZAthe and TZB actions to force EPWM1A and EPWM1B
    // Note: TZA and TZB have higher priority over the DCAEVT2 action.
    //
    
    //
    // EPWM1A will go high
    //
    PWM_setTripZoneState_TZA(myPwm1, PWM_TripZoneState_EPWM_High);
    
    //
    // EPWM1B will go low
    //
    PWM_setTripZoneState_TZB(myPwm1, PWM_TripZoneState_EPWM_Low);

    //
    // Enable TZ interrupt
    //
    PWM_enableTripZoneInt(myPwm1, PWM_TripZoneFlag_OST);
}

//
// InitEPwm2Example - 
//
void
InitEPwm2Example()
{
    CLK_enablePwmClock(myClk, PWM_Number_2);

    PWM_setPeriod(myPwm2, 6000);            // Set timer period
    PWM_setPhase(myPwm2, 0x0000);           // Phase is 0
    PWM_setCount(myPwm2, 0x0000);           // Clear counter

    //
    // Setup TBCLK
    //
    PWM_setCounterMode(myPwm2, PWM_CounterMode_UpDown); // Count up
    
    PWM_disableCounterLoad(myPwm2);                  // Disable phase loading
    
    //
    // Clock ratio to SYSCLKOUT
    //
    PWM_setHighSpeedClkDiv(myPwm2, PWM_HspClkDiv_by_4); 
    
    PWM_setClkDiv(myPwm2, PWM_ClkDiv_by_4);// Slow just to observe on the scope

    //
    // Setup compare
    //
    PWM_setCmpA(myPwm2, 3000);

    //
    // Set actions
    //
    
    //
    // Set PWM2A on Zero
    //
    PWM_setActionQual_CntUp_CmpA_PwmA(myPwm2, PWM_ActionQual_Set);
    
    PWM_setActionQual_CntDown_CmpA_PwmA(myPwm2, PWM_ActionQual_Clear);

    //
    // Clear PWM2B on Zero
    //
    PWM_setActionQual_CntUp_CmpA_PwmB(myPwm2, PWM_ActionQual_Clear);
    
    PWM_setActionQual_CntDown_CmpA_PwmB(myPwm2, PWM_ActionQual_Set);

    //
    // Define an event (DCAEVT2) based on TZ1 and TZ2
    //
    
    //
    // DCAH = TZ1
    //
    PWM_setDigitalCompareInput(myPwm2, PWM_DigitalCompare_A_High, 
                               PWM_DigitalCompare_InputSel_TZ1); 
    
    //
    // DCAL = TZ2
    //
    PWM_setDigitalCompareInput(myPwm2, PWM_DigitalCompare_A_Low, 
                               PWM_DigitalCompare_InputSel_TZ2);

    //
    // DCAEVT2 =  DCAH low, DCAL high
    //
    PWM_setTripZoneDCEventSelect_DCAEVT1(myPwm2, 
                                         PWM_TripZoneDCEventSel_DCxHL_DCxLH);

    //
    // DCAEVT2 = DCAEVT2 (not filtered), Take async path
    //
    PWM_setDigitalCompareAEvent1(myPwm2, false, true, false, false); 

    //
    // Enable DCAEVT2 as a cycle-by-cycle trip source
    // Note: DCxEVT1 events can be defined as one-shot.
    //       DCxEVT2 events can be defined as cycle-by-cycle.
    //
    PWM_enableTripZoneSrc(myPwm2, PWM_TripZoneSrc_CycleByCycle_CmpA);

    //
    // Because DCAEVT2 is causes a trip event (in this case cycle-by-cycle) 
    // we need to use the TZA the and TZB actions to force EPWM2A and EPWM2B
    // NOTE: TZA and TZB have higher priority over the
    //       DCAEVT1 action.
    //
    
    //
    // EPWM2A will go high
    //
    PWM_setTripZoneState_TZA(myPwm2, PWM_TripZoneState_EPWM_High);
    
    //
    // EPWM2B will go low
    //
    PWM_setTripZoneState_TZB(myPwm2, PWM_TripZoneState_EPWM_Low);

    //
    // Enable TZ interrupt
    //
    PWM_enableTripZoneInt(myPwm2, PWM_TripZoneFlag_CBC);
}

//
// InitEPwm3Example - 
//
void
InitEPwm3Example()
{
    CLK_enablePwmClock(myClk, PWM_Number_3);

    PWM_setPeriod(myPwm3, 6000);        // Set timer period
    PWM_setPhase(myPwm3, 0x0000);       // Phase is 0
    PWM_setCount(myPwm3, 0x0000);       // Clear counter

    //
    // Setup TBCLK
    //
    PWM_setCounterMode(myPwm3, PWM_CounterMode_UpDown); // Count up
    PWM_disableCounterLoad(myPwm3);             // Disable phase loading
    
    //
    // Clock ratio to SYSCLKOUT
    //
    PWM_setHighSpeedClkDiv(myPwm3, PWM_HspClkDiv_by_4);
    
    //
    // Slow just to observe on the scope
    //
    PWM_setClkDiv(myPwm3, PWM_ClkDiv_by_4);

    //
    // Setup compare
    //
    PWM_setCmpA(myPwm3, 3000);

    //
    // Set actions
    //
    
    //
    // Set PWM3A on Count Up
    //
    PWM_setActionQual_CntUp_CmpA_PwmA(myPwm3, PWM_ActionQual_Set);
    
    PWM_setActionQual_CntDown_CmpA_PwmA(myPwm3, PWM_ActionQual_Clear);

    //
    // Clear PWM3B on Count Up
    //
    PWM_setActionQual_CntUp_CmpA_PwmB(myPwm3, PWM_ActionQual_Clear);
    
    PWM_setActionQual_CntDown_CmpA_PwmB(myPwm3, PWM_ActionQual_Set);

    //
    // Define an event (DCAEVT2) based on TZ1 and TZ2
    //
    
    //
    // DCAH = TZ1
    //
    PWM_setDigitalCompareInput(myPwm3, PWM_DigitalCompare_A_High, 
                               PWM_DigitalCompare_InputSel_TZ1); 

    //
    // DCAL = TZ2
    //
    PWM_setDigitalCompareInput(myPwm3, PWM_DigitalCompare_A_Low, 
                               PWM_DigitalCompare_InputSel_TZ2);

    //
    // DCAEVT2 =  DCAH low, DCAL high
    //
    PWM_setTripZoneDCEventSelect_DCAEVT2(myPwm3, 
                                         PWM_TripZoneDCEventSel_DCxHL_DCxLH);

    //
    // DCAEVT2 = DCAEVT2 (not filtered), Take async path
    //
    PWM_setDigitalCompareAEvent2(myPwm3, false, true);

    //
    // Define an event (DCBEVT1) based on TZ1 and TZ2
    //
    
    //
    // DCBH = TZ1
    //
    PWM_setDigitalCompareInput(myPwm3, PWM_DigitalCompare_A_High, 
                               PWM_DigitalCompare_InputSel_TZ1);
    
    //
    // DCBL = TZ2
    //
    PWM_setDigitalCompareInput(myPwm3, PWM_DigitalCompare_A_Low, 
                               PWM_DigitalCompare_InputSel_TZ2);
    
    //
    // DCBEVT1 =  DCBH low, DCBL high;
    //
    PWM_setTripZoneDCEventSelect_DCAEVT1(myPwm3, 
                                         PWM_TripZoneDCEventSel_DCxHL_DCxLH);
    
    //
    // DCBEVT1 =  DCBEVT1 (not filtered), Take async path
    //
    PWM_setDigitalCompareAEvent1(myPwm3, false, true, false, false);

    //
    // NOTE: The event is *not* defined as a one-shot or as a cycle-by-cycle 
    // trip. Thus we use the DCAEVT2 and DCBEVT1 actions.
    //
    
    //
    // EPWM3A will go high
    //
    PWM_setTripZoneState_DCAEVT2(myPwm2, PWM_TripZoneState_EPWM_High);
    
    //
    // EPWM3B will go low
    //
    PWM_setTripZoneState_DCAEVT1(myPwm2, PWM_TripZoneState_EPWM_Low);

    //
    // Enable TZ interrupt
    //
    PWM_enableTripZoneInt(myPwm3, PWM_TripZoneFlag_DCAEVT2);
}

//
// End of File
//

