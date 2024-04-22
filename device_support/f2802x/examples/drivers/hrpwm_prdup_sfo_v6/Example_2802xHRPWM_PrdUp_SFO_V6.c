//#############################################################################
//
//  File:   Example_2802xHRPWM_PrdUp_sfo_v6.c
//
//  Title:  F2802x Device HRPWM SFO V6 High-Resolution Period (Up Count) 
//          example
//
//! \addtogroup example_list
//!  <h1>High Resolution PWM SFO Period (Up Count) Control</h1>
//!
//!  This example modifies the MEP control registers to show edge displacement
//!  for high-resolution period with ePWM in Up count mode
//!  due to the HRPWM control extension of the respective ePWM module.
//!
//!  This example calls the following TI's MEP Scale Factor Optimizer (SFO)
//!  software library V6 functions:
//!
//!  int SFO(); \n
//!    - updates MEP_ScaleFactor dynamically when HRPWM is in use
//!    - updates HRMSTEP register (exists only in EPwm1Regs register space)
//!      with MEP_ScaleFactor value
//!    - returns 2 if error: MEP_ScaleFactor is greater than maximum value of 
//!      255 (Auto-conversion may not function properly under this condition)
//!    - returns 1 when complete for the specified channel
//!    - returns 0 if not complete for the specified channel
//!
//!
//!  This example is intended to explain the HRPWM capabilities. The code can 
//!  be optimized for code efficiency. Refer to TI's Digital power application
//!  examples and TI Digital Power Supply software libraries for details.
//!
//!  All ePWM1A-4A channels (GPIO0 through GPI07) will have fine
//!  edge movement due to the HRPWM logic.
//!
//!  =======================================================================
//!   NOTE: For more information on using the SFO software library, see the
//!   2802x High-Resolution Pulse Width Modulator (HRPWM) Reference Guide
//!  =======================================================================
//!
//!  To load and run this example:
//!  -# **!!IMPORTANT!!** - in sfo_v6.h, set PWM_CH to the max number of
//!       HRPWM channels plus one. For example, for the F2802x, the
//!       maximum number of HRPWM channels is 4. 4+1=5, so set
//!       #define PWM_CH 5 in sfo_v6.h. (Default is 5)
//!  -# Run this example at maximum SYSCLKOUT (60 or 40 MHz)
//!  -# Load the Example_2802xHRPWM_PrdUpDown_sfo_v6.gel and observe variables
//!     in the watch window
//!  -# Activate Real time mode
//!  -# Run the code
//!  -# Watch ePWM1-4 waveforms on a Oscilloscope
//!  -# In the watch window:
//!     Set the variable UpdateFine = 1  to observe the ePWMxA output
//!     with HRPWM capabilities (default)
//!     Observe the period/frequency of the waveform changes in fine MEP steps
//!  -# In the watch window:
//!     Change the variable UpdateFine to 0, to observe the
//!     ePWMxA output without HRPWM capabilities
//!     Observe the period/frequency of the waveform changes in coarse 
//!     SYSCLKOUT cycle steps.
//!
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
//                      IMPORTANT
// UPDATE NUMBER OF HRPWM CHANNELS + 1  USED IN sfo_v6.H
// i.e.: #define PWM_CH 5   // F2802x has a maximum of 4 HRPWM channels (5=4+1)
//

//
// Function prototypes
//
void HRPWM_Config(PWM_Handle myPwm, uint16_t period);
void error(void);

//
// Globals
//
Uint16 UpdateFine, PeriodFine, status;

//
// The following declarations are required in order to use the SFO
// library functions:
//

//
// Global variable used by the SFO library. Result can be used for all HRPWM 
// channels. This variable is also copied to HRMSTEP register by SFO() function
//
int MEP_ScaleFactor; 

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

    // Disable CPU interrupts and clear all CPU interrupt flags:
    //   IER = 0x0000;
    //   IFR = 0x0000;

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
    CLK_enableHrPwmClock(myClk);

    //
    // For this example, only initialize the ePWM
    // Step 4. User specific code, enable interrupts:
    //
    UpdateFine = 1;
    PeriodFine = 0;
    status = SFO_INCOMPLETE;

    //
    // Calling SFO() updates the HRMSTEP register with calibrated 
    // MEP_ScaleFactor. HRMSTEP must be populated with a scale factor value 
    // prior to enabling high resolution period control.
    //
    while  (status== SFO_INCOMPLETE) // Call until complete
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
    // Some useful Period vs Frequency values
    //  SYSCLKOUT =     60 MHz       40 MHz
    //
    //  Period          Frequency    Frequency
    //  1000            60 kHz       40 kHz
    //  800             75 kHz       50 kHz
    //  600             100 kHz      67 kHz
    //  500             120 kHz      80 kHz
    //  250             240 kHz      160 kHz
    //  200             300 kHz      200 kHz
    //  100             600 kHz      400 kHz
    //  50              1.2 Mhz      800 kHz
    //  25              2.4 Mhz      1.6 MHz
    //  20              3.0 Mhz      2.0 MHz
    //  12              5.0 MHz      3.3 MHz
    //  10              6.0 MHz      4.0 MHz
    //  9               6.7 MHz      4.4 MHz
    //  8               7.5 MHz      5.0 MHz
    //  7               8.6 MHz      5.7 MHz
    //  6               10.0 MHz     6.6 MHz
    //  5               12.0 MHz     8.0 MHz
    //

    //
    // ePWM and HRPWM register initialization
    //
    CLK_disableTbClockSync(myClk);

    HRPWM_Config(myPwm1, 30);        // ePWMx target
    HRPWM_Config(myPwm2, 30);        // ePWMx target
    HRPWM_Config(myPwm3, 30);        // ePWMx target
    HRPWM_Config(myPwm4, 30);        // ePWMx target

    CLK_enableTbClockSync(myClk);

    PWM_forceSync(myPwm1);
    PWM_forceSync(myPwm2);
    PWM_forceSync(myPwm3);
    PWM_forceSync(myPwm4);

    for(;;)
    {
        //
        // Sweep PeriodFine as a Q16 number from 0.2 - 0.999
        //
        for(PeriodFine = 0x3333; PeriodFine < 0xFFBF; PeriodFine++)
        {
            if(UpdateFine)
            {
                //
                // Because auto-conversion is enabled, the desired
                // fractional period must be written directly to the
                // TBPRDHR (or TBPRDHRM) register in Q16 format
                // (lower 8-bits are ignored)
                //
                EPwm1Regs.TBPRDHR = PeriodFine;

                //
                // The hardware will automatically scale
                // the fractional period by the MEP_ScaleFactor
                // in the HRMSTEP register (which is updated
                // by the SFO calibration software).
                //

                //
                // Hardware conversion:
                // MEP delay movement = ((TBPRDHR(15:0) >> 8) *  HRMSTEP(7:0) 
                // + 0x80) >> 8
                //

                //for(i=1;i<PWM_CH;i++)
                //{
                //    (*ePWM[i]).TBPRDHR = PeriodFine; //In Q16 format
                //}
                PWM_setPeriodHr(myPwm1, PeriodFine);
                PWM_setPeriodHr(myPwm2, PeriodFine);
                PWM_setPeriodHr(myPwm3, PeriodFine);
                PWM_setPeriodHr(myPwm4, PeriodFine);
            }
            
            else
            {
                //
                // No high-resolution movement on TBPRDHR.
                //

                //for(i=1;i<PWM_CH;i++)
                //{
                //  (*ePWM[i]).TBPRDHR = 0;
                //}
                PWM_setPeriodHr(myPwm1, 0);
                PWM_setPeriodHr(myPwm2, 0);
                PWM_setPeriodHr(myPwm3, 0);
                PWM_setPeriodHr(myPwm4, 0);
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
}

//
// HRPWM_Config - Configures all ePWM channels and sets up HRPWM on ePWMxA 
// channels. Parameters:  period - desired PWM period in TBCLK counts
//
void
HRPWM_Config(PWM_Handle myPwm, uint16_t period)
{
    //
    //Uint16 j;
    //
    
    //
    // ePWM channel register configuration with HRPWM
    // ePWMxA toggle low/high with MEP control on Rising edge
    //
    //EALLOW;
    //SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;  // Disable TBCLK within the EPWM
    //EDIS;

    //for (j=1;j<PWM_CH;j++)
    //{
    //    (*ePWM[j]).TBCTL.bit.PRDLD = TB_SHADOW; // set Shadow load
    //    (*ePWM[j]).TBPRD = period-1;            // PWM frequency = 1 / period
    //    (*ePWM[j]).CMPA.half.CMPA = period / 2; // set duty 50% initially
    //    (*ePWM[j]).CMPA.half.CMPAHR = (1 << 8); // initialize HRPWM extension
    //
    //    //
    //    // set duty 50% initially (edge 3 cycles after CTR=0)
    //    //
    //    (*ePWM[j]).CMPB = period / 2;
    //    (*ePWM[j]).TBPHS.all = 0;
    //    (*ePWM[j]).TBCTR = 0;
    //

    PWM_setPeriodLoad(myPwm, PWM_PeriodLoad_Shadow);
    PWM_setPeriod(myPwm, period-1);     // Set timer period
    PWM_setCmpA(myPwm, period / 2);
    PWM_setCmpAHr(myPwm, (1 << 8));
    PWM_setCmpB(myPwm, period / 2);
    PWM_setPhase(myPwm, 0x0000);        // Phase is 0
    PWM_setCount(myPwm, 0x0000);        // Clear counter

    //    (*ePWM[j]).TBCTL.bit.CTRMODE = TB_COUNT_UP;   // Select up-count mode
    //    (*ePWM[j]).TBCTL.bit.PHSEN = TB_DISABLE;
    //    (*ePWM[j]).TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
    //    (*ePWM[j]).TBCTL.bit.HSPCLKDIV = TB_DIV1;
    //    (*ePWM[j]).TBCTL.bit.CLKDIV = TB_DIV1;        // TBCLK = SYSCLKOUT
    //    (*ePWM[j]).TBCTL.bit.FREE_SOFT = 11;

    PWM_setCounterMode(myPwm, PWM_CounterMode_Up);     // Count up
    PWM_disableCounterLoad(myPwm);                     // Disable phase loading
    PWM_setSyncMode(myPwm, PWM_SyncMode_Disable);
    
    //
    // Clock ratio to SYSCLKOUT
    //
    PWM_setHighSpeedClkDiv(myPwm, PWM_HspClkDiv_by_1);
    
    PWM_setClkDiv(myPwm, PWM_ClkDiv_by_1);
    PWM_setRunMode(myPwm, PWM_RunMode_FreeRun);

    //    //
    //    // Load CMPA on CTR = PRD
    //    //
    //    (*ePWM[j]).CMPCTL.bit.LOADAMODE = CC_CTR_PRD;
    //    (*ePWM[j]).CMPCTL.bit.LOADBMODE = CC_CTR_PRD;
    //    (*ePWM[j]).CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    //    (*ePWM[j]).CMPCTL.bit.SHDWBMODE = CC_SHADOW;

    //
    // Load registers every ZERO
    //
    PWM_setShadowMode_CmpA(myPwm, PWM_ShadowMode_Shadow);
    
    PWM_setShadowMode_CmpB(myPwm, PWM_ShadowMode_Shadow);
    PWM_setLoadMode_CmpA(myPwm, PWM_LoadMode_Zero);
    PWM_setLoadMode_CmpB(myPwm, PWM_LoadMode_Zero);

    //    (*ePWM[j]).AQCTLA.bit.PRD = AQ_SET;        // PWM toggle high/low
    //    (*ePWM[j]).AQCTLA.bit.CAU = AQ_CLEAR;
    //    (*ePWM[j]).AQCTLB.bit.PRD = AQ_SET;
    //    (*ePWM[j]).AQCTLB.bit.CAU = AQ_CLEAR;

    PWM_setActionQual_Period_PwmA(myPwm, PWM_ActionQual_Set);
    PWM_setActionQual_CntUp_CmpA_PwmA(myPwm, PWM_ActionQual_Clear);
    PWM_setActionQual_Period_PwmB(myPwm, PWM_ActionQual_Set);
    PWM_setActionQual_CntUp_CmpA_PwmB(myPwm, PWM_ActionQual_Clear);

    //    EALLOW;
    //    (*ePWM[j]).HRCNFG.all = 0x0;
    //    (*ePWM[j]).HRCNFG.bit.EDGMODE = HR_BEP;  // MEP control on both edges
    //    (*ePWM[j]).HRCNFG.bit.CTLMODE = HR_CMP;
    //    (*ePWM[j]).HRCNFG.bit.HRLOAD  = HR_CTR_ZERO_PRD;
    //
    //    (*ePWM[j]).HRCNFG.bit.AUTOCONV = 1;      // Enable autoconversion
    //
    //    //
    //    // Turn on high-resolution period control
    //    //
    //    (*ePWM[j]).HRPCTL.bit.HRPE = 1;
    //    EDIS;

    PWM_setHrEdgeMode(myPwm, PWM_HrEdgeMode_Both);
    PWM_setHrControlMode(myPwm, PWM_HrControlMode_Duty);
    
    //
    // Enable auto-conversion logic
    //
    PWM_setHrShadowMode(myPwm, PWM_HrShadowMode_CTR_EQ_0_OR_PRD);
    
    PWM_enableAutoConvert(myPwm);
    PWM_enableHrPeriod(myPwm);

    //    EALLOW;
    //    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1; //Enable TBCLK within the EPWM
    //    EDIS;
    //    (*ePWM[j]).TBCTL.bit.SWFSYNC = 1;  // Sync for high resolution period
    PWM_forceSync(myPwm);

    //}
}

//
// error - 
//
void
error(void)
{
    ESTOP0;         // Stop here and handle error
}

//
// End of File
//

