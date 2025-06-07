//#############################################################################
//
//  File:   Example_F2802xFlash.c
//
//  Title:  F2802x EPwm Timer Interrupt From Flash Example.
//
//  Group:          C2000
//  Target Device:  TMS320F2802x
//
//! \addtogroup example_list
//!  <h1>EPwm interrupt from Flash</h1>
//! This example runs the EPwm interrupt example from flash.
//!
//!    -# Build the project
//!    -# Flash the .out file into the device.
//!    -# Set the hardware jumpers to boot to Flash
//!    -# Use the included GEL file to load the project, symbols
//!       defined within the project and the variables into the watch
//!       window.
//!
//!    Steps that were taken to convert the EPwm example from RAM
//!    to Flash execution:
//!
//!    -# Change the linker cmd file to reflect the flash memory map.
//!    -# Make sure any initialized sections are mapped to Flash.
//!       In SDFlash utility this can be checked by the View->Coff/Hex
//!       status utility. Any section marked as "load" should be
//!       allocated to Flash.
//!    -# Make sure there is a branch instruction from the entry to Flash
//!       at 0x3F7FF6 to the beginning of code execution. This example
//!       uses the F2802x_CodeStartBranch.asm file to accomplish this.
//!    -# Set boot mode Jumpers to "boot to Flash"
//!    -# For best performance from the flash, modify the waitstates
//!       and enable the flash pipeline as shown in this example.
//!       Note: any code that manipulates the flash waitstate and pipeline
//!       control must be run from RAM. Thus these functions are located
//!       in their own memory section called ramfuncs.
//!
//!
//!    EPwm1 Interrupt will run from RAM and puts the flash into sleep mode.
//!    EPwm2 Interrupt will run from RAM and puts the flash into standby mode.
//!    EPwm3 Interrupt will run from FLASH.
//!
//!    As supplied:
//!
//!    All timers have the same period.
//!    The timers are started sync'ed.
//!    An interrupt is taken on a zero event for each EPwm timer.
//!
//!       EPwm1: takes an interrupt every event.
//!       EPwm2: takes an interrupt every 2nd event.
//!       EPwm3: takes an interrupt every 3rd event.
//!
//!    Thus the Interrupt count for EPwm1, EPwm4-EPwm6 should be equal
//!    The interrupt count for EPwm2 should be about half that of EPwm1
//!    and the interrupt count for EPwm3 should be about 1/3 that of EPwm1
//!
//!    Watch Variables:
//!    - EPwm1TimerIntCount
//!    - EPwm2TimerIntCount
//!    - EPwm3TimerIntCount
//!
//!    Toggle GPIO34 while in the background loop.
//
//#############################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:
// Copyright (C) 2009-2025 Texas Instruments Incorporated - http://www.ti.com/
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
// Defines
//

//
// Configure which EPwm timer interrupts are enabled at the PIE level:
// 1 = enabled,  0 = disabled
//
#define PWM1_INT_ENABLE  1
#define PWM2_INT_ENABLE  1
#define PWM3_INT_ENABLE  1

//
// Defines that configure the period for each timer
//
#define PWM1_TIMER_TBPRD   0x1FFF
#define PWM2_TIMER_TBPRD   0x1FFF
#define PWM3_TIMER_TBPRD   0x1FFF

//
// Make this long enough so that we can see an LED toggle
//
#define DELAY 1000000L

//
// Functions that will be run from RAM need to be assigned to
// a different section.  This section will then be mapped using
// the linker cmd file.
//
#pragma CODE_SECTION(EPwm1_timer_isr, "ramfuncs");
#pragma CODE_SECTION(EPwm2_timer_isr, "ramfuncs");

//
// Function Prototypes
//
__interrupt void EPwm1_timer_isr(void);
__interrupt void EPwm2_timer_isr(void);
__interrupt void EPwm3_timer_isr(void);
void InitEPwmTimer(void);

//
// Globals
//
uint32_t  EPwm1TimerIntCount;
uint32_t  EPwm2TimerIntCount;
uint32_t  EPwm3TimerIntCount;
uint32_t  LoopCount;

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

    // Setup a debug vector table and enable the PIE
    PIE_setDebugIntVectorTable(myPie);
    PIE_enable(myPie);

    //
    // Register interrupt handlers in the PIE vector table
    //
    PIE_registerPieIntHandler(myPie, PIE_GroupNumber_3, PIE_SubGroupNumber_1,
                              (intVec_t)&EPwm1_timer_isr);
    PIE_registerPieIntHandler(myPie, PIE_GroupNumber_3, PIE_SubGroupNumber_2,
                              (intVec_t)&EPwm2_timer_isr);
    PIE_registerPieIntHandler(myPie, PIE_GroupNumber_3, PIE_SubGroupNumber_3,
                              (intVec_t)&EPwm3_timer_isr);

    //
    // Initialize the EPwm Timers used in this example
    //
    InitEPwmTimer();

#ifdef _FLASH
    //
    // Copy time critical code and Flash setup code to RAM
    // This includes the following ISR functions: EPwm1_timer_isr(), 
    // EPwm2_timer_isr() and FLASH_setup();
    // The  RamfuncsLoadStart, RamfuncsLoadSize, and RamfuncsRunStart
    // symbols are created by the linker. Refer to the F228027.cmd file.
    //
    memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (size_t)&RamfuncsLoadSize);

    //
    // Call Flash Initialization to setup flash waitstates
    // This function must reside in RAM
    //
    FLASH_setup(myFlash);
#endif

    //
    // Initialize counters
    //
    EPwm1TimerIntCount = 0;
    EPwm2TimerIntCount = 0;
    EPwm3TimerIntCount = 0;
    LoopCount = 0;

    //
    // Enable CPU INT3 which is connected to EPwm1-3 INT
    //
    CPU_enableInt(myCpu, CPU_IntNumber_3);

    //
    // Enable EPwm INTn in the PIE: Group 3 interrupt 1-3.
    //
    PIE_enablePwmInt(myPie, PWM_Number_1);
    PIE_enablePwmInt(myPie, PWM_Number_2);
    PIE_enablePwmInt(myPie, PWM_Number_3);

    //
    // Enable global Interrupts and higher priority real-time debug events
    //
    CPU_enableGlobalInts(myCpu);
    CPU_enableDebugInt(myCpu);

    //
    // Configure GPIO so it can toggle in the idle loop
    //
    GPIO_setMode(myGpio, GPIO_Number_34, GPIO_34_Mode_GeneralPurpose);
    GPIO_setDirection(myGpio, GPIO_Number_34, GPIO_Direction_Output);

    for(;;)
    {
        //
        // This loop will be interrupted, so the overall
        // delay between pin toggles will be longer.
        //
        DELAY_US(DELAY);
        LoopCount++;

        //
        // Toggle GPIO
        //
        GPIO_toggle(myGpio, GPIO_Number_34);
    }
}

//
// InitEPwmTimer - 
//
void
InitEPwmTimer()
{
    CLK_disableTbClockSync(myClk);
    CLK_enablePwmClock(myClk, PWM_Number_1);
    CLK_enablePwmClock(myClk, PWM_Number_2);
    CLK_enablePwmClock(myClk, PWM_Number_3);

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

    //
    // Setup Sync
    //
    PWM_setSyncMode(myPwm1, PWM_SyncMode_EPWMxSYNC);
    PWM_setSyncMode(myPwm2, PWM_SyncMode_EPWMxSYNC);
    PWM_setSyncMode(myPwm3, PWM_SyncMode_EPWMxSYNC);

    //
    // Allow each timer to be sync'ed
    //
    PWM_enableCounterLoad(myPwm1);
    PWM_enableCounterLoad(myPwm2);
    PWM_enableCounterLoad(myPwm3);

    //
    // Set the phase
    //
    PWM_setPhase(myPwm1, 100);
    PWM_setPhase(myPwm1, 200);
    PWM_setPhase(myPwm1, 300);

    PWM_setPeriod(myPwm1, PWM1_TIMER_TBPRD);
    PWM_setCounterMode(myPwm1, PWM_CounterMode_Up);         // Count up
    
    //
    // Select INT on Zero event
    //
    PWM_setIntMode(myPwm1, PWM_IntMode_CounterEqualZero);
    
    PWM_enableInt(myPwm1);                        // Enable INT
    
    //
    // Generate INT on 1st event
    //
    PWM_setIntPeriod(myPwm1, PWM_IntPeriod_FirstEvent);

    PWM_setPeriod(myPwm2, PWM2_TIMER_TBPRD);
    PWM_setCounterMode(myPwm2, PWM_CounterMode_Up);         // Count up
    
    //
    // Enable INT on Zero event
    //
    PWM_setIntMode(myPwm2, PWM_IntMode_CounterEqualZero);
    
    PWM_enableInt(myPwm2);                                  // Enable INT
    
    //
    // Generate INT on 2nd events
    //
    PWM_setIntPeriod(myPwm2, PWM_IntPeriod_SecondEvent);

    PWM_setPeriod(myPwm3, PWM3_TIMER_TBPRD);
    PWM_setCounterMode(myPwm3, PWM_CounterMode_Up);         // Count up
    
    //
    // Enable INT on Zero event
    //
    PWM_setIntMode(myPwm3, PWM_IntMode_CounterEqualZero);
    
    PWM_enableInt(myPwm3);                                  // Enable INT
    
    //
    // Generate INT on 3rd event
    //
    PWM_setIntPeriod(myPwm3, PWM_IntPeriod_ThirdEvent);

    PWM_setCmpA(myPwm1, PWM1_TIMER_TBPRD / 2);
    PWM_setActionQual_Period_PwmA(myPwm1, PWM_ActionQual_Set);
    PWM_setActionQual_CntUp_CmpA_PwmA(myPwm1, PWM_ActionQual_Clear);
    PWM_setActionQual_Period_PwmB(myPwm1, PWM_ActionQual_Set);
    PWM_setActionQual_CntUp_CmpA_PwmB(myPwm1, PWM_ActionQual_Clear);

    PWM_setCmpA(myPwm2, PWM2_TIMER_TBPRD / 2);
    PWM_setActionQual_Period_PwmA(myPwm2, PWM_ActionQual_Set);
    PWM_setActionQual_CntUp_CmpA_PwmA(myPwm2, PWM_ActionQual_Clear);
    PWM_setActionQual_Period_PwmB(myPwm2, PWM_ActionQual_Set);
    PWM_setActionQual_CntUp_CmpA_PwmB(myPwm2, PWM_ActionQual_Clear);

    PWM_setCmpA(myPwm3, PWM3_TIMER_TBPRD / 2);
    PWM_setActionQual_Period_PwmA(myPwm3, PWM_ActionQual_Set);
    PWM_setActionQual_CntUp_CmpA_PwmA(myPwm3, PWM_ActionQual_Clear);
    PWM_setActionQual_Period_PwmB(myPwm3, PWM_ActionQual_Set);
    PWM_setActionQual_CntUp_CmpA_PwmB(myPwm3, PWM_ActionQual_Clear);

    CLK_enableTbClockSync(myClk);
}

//
// EPwm1_timer_isr - This ISR MUST be executed from RAM as it will put the 
// Flash into Sleep Interrupt routines uses in this example:
//
__interrupt void
EPwm1_timer_isr(void)
{
    //
    // Put the Flash to sleep
    //
    FLASH_setPowerMode(myFlash, FLASH_PowerMode_PumpAndBankSleep);

    EPwm1TimerIntCount++;

    //
    // Clear INT flag for this timer
    //
    PWM_clearIntFlag(myPwm1);

    //
    // Clear this interrupt to receive more interrupts from group 3
    //
    PIE_clearInt(myPie, PIE_GroupNumber_3);
}

//
// EPwm2_timer_isr - This ISR MUST be executed from RAM as it will put the 
// Flash into Standby
//
__interrupt void
EPwm2_timer_isr(void)
{
    EPwm2TimerIntCount++;

    //
    // Put the Flash into standby
    //
    FLASH_setPowerMode(myFlash, FLASH_PowerMode_PumpAndBankStandby);

    //
    // Clear INT flag for this timer
    //
    PWM_clearIntFlag(myPwm2);

    //
    // Clear this interrupt to receive more interrupts from group 3
    //
    PIE_clearInt(myPie, PIE_GroupNumber_3);
}

//
// EPwm3_timer_isr - 
//
__interrupt void
EPwm3_timer_isr(void)
{
    uint16_t i;

    EPwm3TimerIntCount++;

    //
    // Short Delay to simulate some ISR Code
    //
    for(i = 1; i < 0x01FF; i++)
    {
        
    }

    //
    // Clear INT flag for this timer
    //
    PWM_clearIntFlag(myPwm3);

    //
    // Clear this interrupt to receive more interrupts from group 3
    //
    PIE_clearInt(myPie, PIE_GroupNumber_3);
}

//
// End of File
//

