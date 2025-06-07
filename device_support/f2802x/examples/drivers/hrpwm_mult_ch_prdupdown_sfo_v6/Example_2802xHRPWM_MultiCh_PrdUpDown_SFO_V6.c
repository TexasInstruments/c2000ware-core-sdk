//#############################################################################
//
//  File:   Example_2802xHRPWM_MultiCh_PrdUpDown_sfo_v6.c
//
//  Title:  F2802x Device HRPWM SFO V6 High-Resolution Period (Up-Down Count) 
//          Multi-channel example
//
//! \addtogroup example_list
//!  <h1>High Resolution PWM SFO Period Control</h1>
//!
//!  This example modifies the MEP control registers to show edge displacement
//!  for high-resolution period/frequency on multiple synchronized ePWM 
//!  channels in Up-Down count mode due to the HRPWM control extension of the  
//!  respective ePWM module.
//!
//!  Notice that all period and compare register updates occur in an ISR which 
//!  interrupts at ePWM1 TBCTR = 0. This ensures that period and compare 
//!  register updates across all ePWM modules occur within the same period.
//!
//!  This example calls the following TI's MEP Scale Factor Optimizer (SFO)
//!  software library V6 functions:
//!
//!  int SFO(); \n
//!      - updates MEP_ScaleFactor dynamically when HRPWM is in use
//!      - updates HRMSTEP register (exists only in EPwm1Regs register space)
//!        with MEP_ScaleFactor value
//!      - returns 2 if error: MEP_ScaleFactor is greater than maximum value of
//!        255 (Auto-conversion may not function properly under this condition)
//!      - returns 1 when complete for the specified channel
//!      - returns 0 if not complete for the specified channel
//!
//!
//!  All ePWM1A-4A channels will be synchronized to each other 
//!  (with ePWM1 sync'd to the SWFSYNC) and have fine edge period movement due 
//!  to the HRPWM logic.
//!
//!  This example can be used as a primitive building block for applications 
//!  which require high resolution frequency control with synchronized ePWM 
//!  modules (i.e. resonant converter applications)
//!
//!  =======================================================================
//!   NOTE: For more information on using the SFO software library, see the
//!   2802x High-Resolution Pulse Width Modulator (HRPWM) Reference Guide
//!  =======================================================================
//!  
//!  To load and run this example:
//!  -# **!!IMPORTANT!!** - in sfo_v6.h, set PWM_CH to the max number of
//!              HRPWM channels plus one. For example, for the F2802x, the
//!              maximum number of HRPWM channels is 4. 4+1=5, so set
//!              #define PWM_CH 5 in sfo_v6.h. (Default is 5)
//!  -# Run this example at maximum SYSCLKOUT (60 MHz or 40 MHz)
//!  -# Add "UpdateFine" and "UpdateCourse" variables to the watch window.
//!  -# Activate Real time mode
//!  -# Run the code
//!  -# Watch ePWM A channel waveforms on a Oscilloscope
//!  -# In the watch window:
//!     Set the variable UpdateFine = 1  to observe the ePWMxA output
//!     with HRPWM capabilities (default)
//!     Observe the period/frequency of the waveform changes in fine MEP steps
//!  -# In the watch window:
//!     Change the variable UpdateFine to 0, to observe the
//!     ePWMxA output without HRPWM capabilities
//!     To change the period/frequency in coarse steps, uncomment the relevant 
//!     code, re-build and re-run with UpdateCoarse = 1.
//!     Observe the period/frequency of the waveform changes in coarse 
//!     SYSCLKOUT cycle steps.
//!
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
#include "DSP28x_Project.h"         // DSP280xx Headerfile

#include "sfo_v6.h"
#include "common/include/f2802x_epwm_defines.h"

#include "common/include/clk.h"
#include "common/include/flash.h"
#include "common/include/gpio.h"
#include "common/include/pie.h"
#include "common/include/pll.h"
#include "common/include/pwm.h"
#include "common/include/wdog.h"

//
//                          IMPORTANT
// UPDATE NUMBER OF HRPWM CHANNELS + 1  USED IN sfo_v6.H
//
// Configured for 4 HRPWM channels; F2803x has a maximum of 
// 4 HRPWM channels (5=4+1)
//
// i.e.: #define PWM_CH 5

//
// Function prototypes
//
void HRPWM_Config(PWM_Handle myPwm, uint16_t period, uint16_t phase);
void error(void);
__interrupt void MainISR(void);

//
// Globals
//
Uint16 UpdateFine,  status, UpdateCoarse, Increment_Freq, Increment_Freq_Fine;

volatile Uint16 UpdatePeriod;
volatile Uint16 UpdatePeriodFine;
volatile Uint16 PeriodFine;
volatile Uint16 Period;

//
// The following declarations are required in order to use the SFO
// library functions:
//

//
// Global variable used by the SFO library. Result can be used for all HRPWM 
// channels. This variable is also copied to HRMSTEP register by SFO(0) 
// function.
//
int MEP_ScaleFactor; 

Uint16    IsrTicker;

//
// Array of pointers to EPwm register structures:
// *ePWM[0] is defined as dummy value not used in the example
//
volatile struct EPWM_REGS *ePWM[PWM_CH] =
             {  &EPwm1Regs, &EPwm1Regs, &EPwm2Regs, &EPwm3Regs, &EPwm4Regs};

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
    //InitEPwmGpio();

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

    //
    // Step 4. Initialize the Device Peripherals:
    //
    CLK_enablePwmClock(myClk, PWM_Number_1);
    CLK_enablePwmClock(myClk, PWM_Number_2);
    CLK_enablePwmClock(myClk, PWM_Number_3);
    CLK_enablePwmClock(myClk, PWM_Number_4);
    CLK_enableHrPwmClock(myClk);

    //
    // For this example, only initialize the ePWM
    // Step 5. User specific code, enable interrupts:
    //

    //
    // Calling SFO() updates the HRMSTEP register with calibrated 
    // MEP_ScaleFactor. HRMSTEP must be populated with a scale factor value 
    // prior to enabling high resolution period control.
    //
    status = SFO_INCOMPLETE;
    
    while(status== SFO_INCOMPLETE) // Call until complete
    {
        status = SFO();
        if (status == SFO_ERROR)
        {
            //
            // SFO function returns 2 if an error occurs & # of MEP 
            // steps/coarse step exceeds maximum of 255.
            //
            error();   
        }
    }

    //
    // Some useful PWM period vs Frequency values
    //  TBCLK = 60 MHz
    //
    //  Period   Freq
    //  1000     30 KHz
    //  800    37.5 KHz
    //  600      50 KHz
    //  500      60 KHz
    //  250     120 KHz
    //  200     150 KHz
    //  100     300 KHz
    //  50      600 KHz
    //  30        1 MHz
    //  25      1.2 MHz
    //  20      1.5 MHz
    //  12      2.5 MHz
    //  10        3 MHz
    //  9       3.3 MHz
    //  8       3.8 MHz
    //  7       4.3 MHz
    //  6       5.0 MHz
    //  5       6.0 MHz
    //
    
    //
    // ePWM and HRPWM register initialization
    //
    Period = 500;
    PeriodFine=0xFFBF;

    CLK_disableTbClockSync(myClk);

    HRPWM_Config(myPwm1, Period, 1);
    HRPWM_Config(myPwm2, Period, 0);
    HRPWM_Config(myPwm3, Period, 0);
    HRPWM_Config(myPwm4, Period, 0);

    CLK_enableTbClockSync(myClk);

    //
    // Software Control variables
    //
    Increment_Freq = 1;
    Increment_Freq_Fine = 1;
    IsrTicker = 0;
    UpdatePeriod = 0;
    UpdatePeriodFine = 0;

    //
    // User control variables
    //
    UpdateCoarse = 0;
    UpdateFine = 1;

    //
    // Reassign ISRs
    //
    PIE_registerPieIntHandler(myPie, PIE_GroupNumber_3, PIE_SubGroupNumber_1,
                              (intVec_t)&MainISR);

    //
    // Enable PIE group 3 interrupt 1 for EPWM1_INT
    //
    PIE_enableInt(myPie, PIE_GroupNumber_3, PIE_InterruptSource_EPWM1);

    //
    // Enable CNT_zero interrupt using EPWM1 Time-base
    //
    
    //
    // Select INT on Zero event
    //
    PWM_setIntMode(myPwm1, PWM_IntMode_CounterEqualZero);
    
    PWM_enableInt(myPwm1);                                  // Enable INT
    
    //
    // Generate INT on 3rd event
    //
    PWM_setIntPeriod(myPwm1, PWM_IntPeriod_FirstEvent);
    
    PWM_clearIntFlag(myPwm1);

    //
    // Enable CPU INT3 for EPWM1_INT
    //
    CPU_enableInt(myCpu, CPU_IntNumber_3);

    //
    // Enable global Interrupts and higher priority real-time debug events
    //
    CPU_enableGlobalInts(myCpu);
    CPU_enableDebugInt(myCpu);

    //
    // Synchronize high resolution phase to start HR period
    //
    PWM_forceSync(myPwm1);

    for(;;)
    {
        //
        // The below code controls coarse edge movement
        //
        if(UpdateCoarse==1)
        {
            
            if(Increment_Freq==1)           //Increase frequency to 600 kHz
            {
                Period= Period - 1;
            }
            
            else
            {
                Period= Period + 1;         //Decrease frequency to 300 kHz
            }

            if(Period<100 && Increment_Freq==1)
            {
                Increment_Freq=0;
            }
        
            else if(Period>500 && Increment_Freq==0)
            {
                Increment_Freq=1;
            }

            UpdatePeriod=1;
        }

        //
        // The below code controls high-resolution fine edge movement
        //
        if(UpdateFine==1)
        {
            if(Increment_Freq_Fine==1)    // Increase high-resolution frequency
            PeriodFine=PeriodFine-1;
            else
            PeriodFine=PeriodFine+1; // Decrement high-resolution frequency

            if(PeriodFine<=0x3333 && Increment_Freq_Fine==1)
            Increment_Freq_Fine=0;
            else if(PeriodFine>= 0xFFBF && Increment_Freq_Fine==0)
            Increment_Freq_Fine=1;

            UpdatePeriodFine=1;
        }

        //
        // Call the scale factor optimizer lib function SFO()
        // periodically to track for any change due to temp/voltage.
        // This function generates MEP_ScaleFactor by running the
        // MEP calibration module in the HRPWM logic. This scale
        // factor can be used for all HRPWM channels. HRMSTEP
        // register is automatically updated by the SFO function.
        //
        
        //
        // in background, MEP calibration module continuously updates 
        // MEP_ScaleFactor
        //
        status = SFO(); 
        if (status == SFO_ERROR)
        {
            //
            // SFO function returns 2 if an error occurs & # of MEP 
            // steps/coarse step exceeds maximum of 255.
            //
            error();   
        }
    }
}

//
// MainISR - interrupts at ePWM1 TBCTR = 0.
// This ISR updates the compare and period registers for all ePWM modules 
// within the same period. User must ensure that the PWM period is large enough
// to execute all of the code in the ISR before TBCTR = Period for all ePWM's.
//
__interrupt void
MainISR(void)
{
    //
    // Sweep frequency coarsely between 300 kHz and 600 kHz.
    //
    if(UpdatePeriod==1)
    {
        PWM_setPeriod(myPwm1, Period);    // Set timer period
        PWM_setCmpA(myPwm1, Period >> 1);

        PWM_setPeriod(myPwm2, Period);    // Set timer period
        PWM_setCmpA(myPwm2, Period >> 1);

        PWM_setPeriod(myPwm2, Period);    // Set timer period
        PWM_setCmpA(myPwm2, Period >> 1);

        PWM_setPeriod(myPwm2, Period);    // Set timer period
        PWM_setCmpA(myPwm2, Period >> 1);

        UpdatePeriod=0;
    }

    //
    // The below is for fine edge movement
    //
    if(UpdatePeriodFine==1)
    {
       PWM_setPeriodHr(myPwm1, PeriodFine);
       PWM_setPeriodHr(myPwm2, PeriodFine);
       PWM_setPeriodHr(myPwm3, PeriodFine);
       PWM_setPeriodHr(myPwm4, PeriodFine);

       UpdatePeriodFine=0;
    }

    IsrTicker++;

    //
    // Enable more interrupts from this EPWM
    //
    PWM_clearIntFlag(myPwm1);

    //
    // Acknowledge interrupt to receive more interrupts from PIE group 3
    //
    PIE_clearInt(myPie, PIE_GroupNumber_3);
}

//
// HRPWM_Config - Configures all ePWM channels and sets up HRPWM on ePWMxA 
// channels. Parameters: period - desired PWM period in TBCLK counts
//
void
HRPWM_Config(PWM_Handle myPwm, uint16_t period, uint16_t phase)
{
    PWM_setPeriodLoad(myPwm, PWM_PeriodLoad_Shadow);
    PWM_setPeriod(myPwm, period);           // Set timer period
    PWM_setPeriodHr(myPwm, 0x54FF);
    PWM_setCmpA(myPwm, period / 2);
    PWM_setCmpAHr(myPwm, (1 << 8));
    PWM_setCmpB(myPwm, period / 2);
    PWM_setPhase(myPwm, phase);             // Phase is 0
    PWM_setCount(myPwm, 0x0000);            // Clear counter

    PWM_setCounterMode(myPwm, PWM_CounterMode_UpDown);   // Count up
    PWM_enableCounterLoad(myPwm);               // Disable phase loading
    PWM_setSyncMode(myPwm, PWM_SyncMode_Disable);
    
    //
    // Clock ratio to SYSCLKOUT
    //
    PWM_setHighSpeedClkDiv(myPwm, PWM_HspClkDiv_by_1);
    
    PWM_setClkDiv(myPwm, PWM_ClkDiv_by_1);
    PWM_setRunMode(myPwm, PWM_RunMode_FreeRun);

    //
    // Load registers every ZERO
    //
    PWM_setShadowMode_CmpA(myPwm, PWM_ShadowMode_Shadow);
    
    PWM_setShadowMode_CmpB(myPwm, PWM_ShadowMode_Shadow);
    PWM_setLoadMode_CmpA(myPwm, PWM_LoadMode_Zero);
    PWM_setLoadMode_CmpB(myPwm, PWM_LoadMode_Zero);

    PWM_setActionQual_CntDown_CmpA_PwmA(myPwm, PWM_ActionQual_Clear);
    PWM_setActionQual_CntUp_CmpA_PwmA(myPwm, PWM_ActionQual_Set);
    PWM_setActionQual_CntDown_CmpB_PwmB(myPwm, PWM_ActionQual_Clear);
    PWM_setActionQual_CntUp_CmpB_PwmB(myPwm, PWM_ActionQual_Set);

    PWM_setHrEdgeMode(myPwm, PWM_HrEdgeMode_Both);
    PWM_setHrControlMode(myPwm, PWM_HrControlMode_Duty);
    
    //
    // Enable auto-conversion logic
    //
    PWM_setHrShadowMode(myPwm, PWM_HrShadowMode_CTR_EQ_0);
    PWM_enableAutoConvert(myPwm);

    PWM_enableHrPhaseSync(myPwm);
    PWM_enableHrPeriod(myPwm);

    PWM_forceSync(myPwm);
}

//
// error - 
//
void error (void)
{
    ESTOP0;         // Stop here and handle error
}

//
// End of File
//

