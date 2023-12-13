//#############################################################################
//
//  File:   Example_2802xHRPWM_slider.c
//
//  Title:  F2802x Device HRPWM with Slider example
//
//! \addtogroup example_list
//!  <h1>High Resolution PWM Slider</h1>
//!
//!  This example modifies the MEP control registers to show edge displacement
//!  due to HRPWM control blocks of the respective EPwm module, EPwm1A, 2A, 3A,
//!  and 4A channels (GPIO0, GPIO2, GPIO4, and GPIO6) will have fine edge 
//!  movement due to HRPWM logic. Load the Example_2802xHRPWM_slider.gel file.
//!  Select the HRPWM_eval from the GEL menu. A FineDuty slider graphics will 
//!  show up in CCS. Load the program and run. Use the Slider to and observe 
//!  the EPwm edge displacement for each slider step change. This explains 
//!  the MEP control on the EPwmxA channels
//!
//!  -# PWM Freq = SYSCLK/(period=10),
//!     ePWM1A toggle low/high with MEP control on rising edge
//!     PWM Freq = SYSCLK/(period=10),
//!     ePWM1B toggle low/high with NO HRPWM control
//!
//!  -# PWM Freq = SYSCLK/(period=20),
//!     ePWM2A toggle low/high with MEP control on rising edge
//!     PWM Freq = SYSCLK/(period=20),
//!     ePWM2B toggle low/high with NO HRPWM control
//!
//!  -# PWM Freq = SYSCLK/(period=10),
//!     ePWM3A toggle as high/low with MEP control on falling edge
//!     PWM Freq = SYSCLK/(period=10),
//!     ePWM3B toggle low/high with NO HRPWM control
//!
//!  -# PWM Freq = SYSCLK/(period=20),
//!     ePWM4A toggle as high/low with MEP control on falling edge
//!     PWM Freq = SYSCLK/(period=20),
//!     ePWM4B toggle low/high with NO HRPWM control
//!
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
#include "DSP28x_Project.h"         // DSP280xx Headerfile

#include "common/include/clk.h"
#include "common/include/flash.h"
#include "common/include/gpio.h"
#include "common/include/pie.h"
#include "common/include/pll.h"
#include "common/include/pwm.h"
#include "common/include/wdog.h"

//
// Function prototypes
//
void HRPWM1_Config(int);
void HRPWM2_Config(int);
void HRPWM3_Config(int);
void HRPWM4_Config(int);

//
// General System nets - Useful for debug
//
Uint16 i, j, duty, DutyFine, n, update;
Uint32 temp;

//
// Globals
//
CLK_Handle myClk;
FLASH_Handle myFlash;
GPIO_Handle myGpio;
PIE_Handle myPie;
PWM_Handle myPwm1, myPwm2, myPwm3, myPwm4;

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
    myPwm4 = PWM_init((void *)PWM_ePWM4_BASE_ADDR, sizeof(PWM_Obj));
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
    // Setup the PLL for x12 /2 which will yield 60Mhz = 10Mhz * 12 / 2
    //
    PLL_setup(myPll, PLL_Multiplier_12, PLL_DivideSelect_ClkIn_by_2);

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
    // Step 1. Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    // This example function is found in the f2802x_SysCtrl.c file.
    //
    //InitSysCtrl();

    //
    // Step 2. Initialize GPIO:
    // This example function is found in the f2802x_Gpio.c file and
    // illustrates how to set the GPIO to it's default state.
    //
    //InitGpio();  // Skipped for this example

    //
    // For this case, just init GPIO for EPwm1-EPwm4
    //

    //
    // For this case just init GPIO pins for EPwm1, EPwm2, EPwm3, EPwm4
    // These functions are in the f2802x_EPwm.c file
    //
    //InitEPwm1Gpio();
    //InitEPwm2Gpio();
    //InitEPwm3Gpio();
    //InitEPwm4Gpio();

    //
    // Step 3. Clear all interrupts and initialize PIE vector table:
    // Disable CPU interrupts
    //
    //DINT;

    //
    // Initialize the PIE control registers to their default state.
    // The default state is all PIE interrupts disabled and flags
    // are cleared.
    // This function is found in the f2802x_PieCtrl.c file.
    //
    //InitPieCtrl();

    //
    // Disable CPU interrupts and clear all CPU interrupt flags:
    //
    //IER = 0x0000;
    //IFR = 0x0000;

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    // This will populate the entire table, even if the interrupt
    // is not used in this example.  This is useful for debug purposes.
    // The shell ISR routines are found in f2802x_DefaultIsr.c.
    // This function is found in f2802x_PieVect.c.
    //
    //InitPieVectTable();

    //
    // For this case just init GPIO pins for EPwm1, EPwm2, EPwm3, EPwm4
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

    GPIO_setPullUp(myGpio, GPIO_Number_6, GPIO_PullUp_Disable);
    GPIO_setPullUp(myGpio, GPIO_Number_7, GPIO_PullUp_Disable);
    GPIO_setMode(myGpio, GPIO_Number_6, GPIO_6_Mode_EPWM4A);
    GPIO_setMode(myGpio, GPIO_Number_7, GPIO_7_Mode_EPWM4B);

    //
    // Setup a debug vector table and enable the PIE
    //
    PIE_setDebugIntVectorTable(myPie);
    PIE_enable(myPie);

    CLK_enablePwmClock(myClk, PWM_Number_1);
    CLK_enablePwmClock(myClk, PWM_Number_2);
    CLK_enablePwmClock(myClk, PWM_Number_3);
    CLK_enablePwmClock(myClk, PWM_Number_4);

    //
    // For this example, only initialize the EPwm
    // Step 4. User specific code, enable interrupts:
    //
    update =1;
    DutyFine =0;

    CLK_disableTbClockSync(myClk);

    //
    // Some useful Period vs Frequency values
    //  SYSCLKOUT =     60 MHz       40 MHz
    //  
    //    Period            Frequency    Frequency
    //    1000               60 kHz       40 kHz
    //    800                75 kHz       50 kHz
    //    600                100 kHz      67 kHz
    //    500                120 kHz      80 kHz
    //    250                240 kHz      160 kHz
    //    200                300 kHz      200 kHz
    //    100                600 kHz      400 kHz
    //    50                 1.2 Mhz      800 kHz
    //    25                 2.4 Mhz      1.6 MHz
    //    20                 3.0 Mhz      2.0 MHz
    //    12                 5.0 MHz      3.3 MHz
    //    10                 6.0 MHz      4.0 MHz
    //    9                  6.7 MHz      4.4 MHz
    //    8                  7.5 MHz      5.0 MHz
    //    7                  8.6 MHz      5.7 MHz
    //    6                  10.0 MHz     6.6 MHz
    //    5                  12.0 MHz     8.0 MHz
    //

    //
    // EPwm and HRPWM register initialization
    //
    HRPWM1_Config(10);         // EPwm1 target, Period = 10
    HRPWM2_Config(20);         // EPwm2 target, Period = 20
    HRPWM3_Config(10);         // EPwm3 target, Period = 10
    HRPWM4_Config(20);         // EPwm4 target, Period = 20

    CLK_enableTbClockSync(myClk);

    while (update ==1)
    {
        PWM_setCmpAHr(myPwm1, DutyFine << 8);
        PWM_setCmpAHr(myPwm2, DutyFine << 8);
        PWM_setCmpAHr(myPwm3, DutyFine << 8);
        PWM_setCmpAHr(myPwm4, DutyFine << 8);
    }
}

//
// HRPWM1_Config - 
//
void
HRPWM1_Config(period)
{
    PWM_setPeriodLoad(myPwm1, PWM_PeriodLoad_Immediate);
    PWM_setPeriod(myPwm1, period-1);        // Set timer period
    PWM_setCmpA(myPwm1, period / 2);
    PWM_setCmpAHr(myPwm1, (1 << 8));
    PWM_setCmpB(myPwm1, period / 2);
    PWM_setPhase(myPwm1, 0x0000);           // Phase is 0
    PWM_setCount(myPwm1, 0x0000);           // Clear counter

    PWM_setCounterMode(myPwm1, PWM_CounterMode_Up);   // Count up
    PWM_disableCounterLoad(myPwm1);                   // Disable phase loading
    PWM_setSyncMode(myPwm1, PWM_SyncMode_Disable);
    
    //
    // Clock ratio to SYSCLKOUT
    //
    PWM_setHighSpeedClkDiv(myPwm1, PWM_HspClkDiv_by_1);
    
    PWM_setClkDiv(myPwm1, PWM_ClkDiv_by_1);

    //
    // Load registers every ZERO
    //
    PWM_setShadowMode_CmpA(myPwm1, PWM_ShadowMode_Shadow);
    
    PWM_setShadowMode_CmpB(myPwm1, PWM_ShadowMode_Shadow);
    PWM_setLoadMode_CmpA(myPwm1, PWM_LoadMode_Zero);
    PWM_setLoadMode_CmpB(myPwm1, PWM_LoadMode_Zero);

    PWM_setActionQual_Zero_PwmA(myPwm1, PWM_ActionQual_Clear);
    PWM_setActionQual_CntUp_CmpA_PwmA(myPwm1, PWM_ActionQual_Set);
    PWM_setActionQual_Zero_PwmB(myPwm1, PWM_ActionQual_Clear);
    PWM_setActionQual_CntUp_CmpB_PwmB(myPwm1, PWM_ActionQual_Set);

    PWM_setHrEdgeMode(myPwm1, PWM_HrEdgeMode_Rising);
    PWM_setHrControlMode(myPwm1, PWM_HrControlMode_Duty);
    PWM_setHrShadowMode(myPwm1, PWM_HrShadowMode_CTR_EQ_0);
}

//
// HRPWM2_Config - 
//
void
HRPWM2_Config(period)
{
    //
    // ePWM2 register configuration with HRPWM
    // ePWM2A toggle low/high with MEP control on Rising edge
    //
    PWM_setPeriodLoad(myPwm2, PWM_PeriodLoad_Immediate);
    PWM_setPeriod(myPwm2, period-1);        // Set timer period
    PWM_setCmpA(myPwm2, period / 2);
    PWM_setCmpAHr(myPwm2, (1 << 8));
    PWM_setCmpB(myPwm2, period / 2);
    PWM_setPhase(myPwm2, 0x0000);           // Phase is 0
    PWM_setCount(myPwm2, 0x0000);           // Clear counter

    PWM_setCounterMode(myPwm2, PWM_CounterMode_Up);  // Count up
    PWM_disableCounterLoad(myPwm2);                  // Disable phase loading
    PWM_setSyncMode(myPwm2, PWM_SyncMode_Disable);
    
    //
    // Clock ratio to SYSCLKOUT
    //
    PWM_setHighSpeedClkDiv(myPwm2, PWM_HspClkDiv_by_1);
    PWM_setClkDiv(myPwm2, PWM_ClkDiv_by_1);

    //
    // Load registers every ZERO
    //
    PWM_setShadowMode_CmpA(myPwm2, PWM_ShadowMode_Shadow);
    PWM_setShadowMode_CmpB(myPwm2, PWM_ShadowMode_Shadow);
    PWM_setLoadMode_CmpA(myPwm2, PWM_LoadMode_Zero);
    PWM_setLoadMode_CmpB(myPwm2, PWM_LoadMode_Zero);

    PWM_setActionQual_Zero_PwmA(myPwm2, PWM_ActionQual_Clear);
    PWM_setActionQual_CntUp_CmpA_PwmA(myPwm2, PWM_ActionQual_Set);
    PWM_setActionQual_Zero_PwmB(myPwm2, PWM_ActionQual_Clear);
    PWM_setActionQual_CntUp_CmpB_PwmB(myPwm2, PWM_ActionQual_Set);

    PWM_setHrEdgeMode(myPwm2, PWM_HrEdgeMode_Rising);
    PWM_setHrControlMode(myPwm2, PWM_HrControlMode_Duty);
    PWM_setHrShadowMode(myPwm2, PWM_HrShadowMode_CTR_EQ_0);
}

//
// HRPWM3_Config - 
//
void
HRPWM3_Config(period)
{
    PWM_setPeriodLoad(myPwm3, PWM_PeriodLoad_Immediate);
    PWM_setPeriod(myPwm3, period-1);    // Set timer period
    PWM_setCmpA(myPwm3, period / 2);
    PWM_setCmpAHr(myPwm3, (1 << 8));
    PWM_setCmpB(myPwm3, period / 2);
    PWM_setPhase(myPwm3, 0x0000);       // Phase is 0
    PWM_setCount(myPwm3, 0x0000);       // Clear counter

    PWM_setCounterMode(myPwm3, PWM_CounterMode_Up);    // Count up
    PWM_disableCounterLoad(myPwm3);                    // Disable phase loading
    PWM_setSyncMode(myPwm3, PWM_SyncMode_Disable);
    
    //
    // Clock ratio to SYSCLKOUT
    //
    PWM_setHighSpeedClkDiv(myPwm3, PWM_HspClkDiv_by_1);
    
    PWM_setClkDiv(myPwm3, PWM_ClkDiv_by_1);

    //
    // Load registers every ZERO
    //
    PWM_setShadowMode_CmpA(myPwm3, PWM_ShadowMode_Shadow);
    
    PWM_setShadowMode_CmpB(myPwm3, PWM_ShadowMode_Shadow);
    PWM_setLoadMode_CmpA(myPwm3, PWM_LoadMode_Zero);
    PWM_setLoadMode_CmpB(myPwm3, PWM_LoadMode_Zero);

    PWM_setActionQual_Zero_PwmA(myPwm3, PWM_ActionQual_Set);
    PWM_setActionQual_CntUp_CmpA_PwmA(myPwm3, PWM_ActionQual_Clear);
    PWM_setActionQual_Zero_PwmB(myPwm3, PWM_ActionQual_Set);
    PWM_setActionQual_CntUp_CmpB_PwmB(myPwm3, PWM_ActionQual_Clear);

    PWM_setHrEdgeMode(myPwm3, PWM_HrEdgeMode_Falling);
    PWM_setHrControlMode(myPwm3, PWM_HrControlMode_Duty);
    PWM_setHrShadowMode(myPwm3, PWM_HrShadowMode_CTR_EQ_0);
}

//
// HRPWM4_Config - 
//
void
HRPWM4_Config(period)
{
    PWM_setPeriodLoad(myPwm4, PWM_PeriodLoad_Immediate);
    PWM_setPeriod(myPwm4, period-1);    // Set timer period
    PWM_setCmpA(myPwm4, period / 2);
    PWM_setCmpAHr(myPwm4, (1 << 8));
    PWM_setCmpB(myPwm4, period / 2);
    PWM_setPhase(myPwm4, 0x0000);       // Phase is 0
    PWM_setCount(myPwm4, 0x0000);       // Clear counter

    PWM_setCounterMode(myPwm4, PWM_CounterMode_Up);   // Count up
    PWM_disableCounterLoad(myPwm4);                   // Disable phase loading
    PWM_setSyncMode(myPwm4, PWM_SyncMode_Disable);
    
    //
    // Clock ratio to SYSCLKOUT
    //
    PWM_setHighSpeedClkDiv(myPwm4, PWM_HspClkDiv_by_1);
    
    PWM_setClkDiv(myPwm4, PWM_ClkDiv_by_1);

    //
    // Load registers every ZERO
    //
    PWM_setShadowMode_CmpA(myPwm4, PWM_ShadowMode_Shadow);
    
    PWM_setShadowMode_CmpB(myPwm4, PWM_ShadowMode_Shadow);
    PWM_setLoadMode_CmpA(myPwm4, PWM_LoadMode_Zero);
    PWM_setLoadMode_CmpB(myPwm4, PWM_LoadMode_Zero);

    PWM_setActionQual_Zero_PwmA(myPwm4, PWM_ActionQual_Set);
    PWM_setActionQual_CntUp_CmpA_PwmA(myPwm4, PWM_ActionQual_Clear);
    PWM_setActionQual_Zero_PwmB(myPwm4, PWM_ActionQual_Set);
    PWM_setActionQual_CntUp_CmpB_PwmB(myPwm4, PWM_ActionQual_Clear);

    PWM_setHrEdgeMode(myPwm4, PWM_HrEdgeMode_Falling);
    PWM_setHrControlMode(myPwm4, PWM_HrControlMode_Duty);
    PWM_setHrShadowMode(myPwm4, PWM_HrShadowMode_CTR_EQ_0);
}

//
// End of File
//

