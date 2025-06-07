//###########################################################################
//
//  FILE:  Example_2803xHRPWM_MultiCh_PrdUpDown_SFO_V6.c
//
//  TITLE: High Resolution PWM SFO V6 High-Resolution Period (Up-Down Count)
//         Multi-channel example
//
//!  \addtogroup f2803x_example_list
//!  <h1>High Resolution PWM SFO V6 High-Resolution Period
//!  (Up-Down Count) Multi-channel (hrpwm_mult_ch_prdupdown_sfo_v6)</h1>
//!
//!  This example modifies the MEP control registers to show edge displacement
//!  for high-resolution period/frequency on multiple synchronized ePWM 
//!  channels in Up-Down count mode due to the HRPWM control extension of the 
//!  respective ePWM module.
//!
//!  All period and compare register updates occur in an ISR which interrupts 
//!  at ePWM1 TBCTR = 0. This ensures that period and compare register updates 
//!  across all ePWM modules occur within the same period.
//!  This example calls the following TI's MEP Scale Factor Optimizer (SFO)
//!  software library V6 functions:
//!
//!  \b int \b SFO();
//!  - updates MEP_ScaleFactor dynamically when HRPWM is in use
//!  - updates HRMSTEP register (exists only in EPwm1Regs register space but 
//!    valid for all channels)
//!  with MEP_ScaleFactor value
//!  - \b Returns
//!    - 2 if error: MEP_ScaleFactor is greater than maximum value of 255
//!      (Auto-conversion may not function properly under this condition)
//!    - 1 when complete for the specified channel
//!    - 0 if not complete for the specified channel
//!
//!  All ePWM1A-4A channels will be synchronized to each other (with ePWM1 
//!  sync'd to the SWFSYNC) and have fine edge period movement due to the HRPWM
//!  logic.
//!  This example can be used as a primitive building block for applications 
//!  which require high resolution frequency control with synchronized ePWM 
//!  modules (i.e. resonant converter applications)
//!
//!  \note
//!  - This program requires the DSP2803x header files, which include
//!  the following files required for this example:
//!  SFO_V6.h and SFO_TI_Build_V6.lib
//!  - For more information on using the SFO software library, see the
//!  2803x High-Resolution Pulse Width Modulator (HRPWM) Reference Guide
//!
//!  \b External \b Connections \n
//!  Monitor ePWM1A-ePWM4A (GPIO0-GPIO7) pins on an oscilloscope.
//!
//!  \b Running \b the \b Application
//!  -# \b **!!IMPORTANT!!** : in SFO_V6.h, set PWM_CH to the max number of
//!  HRPWM channels used plus one. For this example, the
//!  maximum number of HRPWM channels used is 4. 4+1=5, so set
//!  \#define PWM_CH 5 in SFO_V6.h. (Default is 5)
//!  -# Run this example at maximum SYSCLKOUT (60 MHz)
//!  -# Add "UpdateFine" and "UpdateCoarse" variables to the watch window
//!     either manually or using the supplied javascript.
//!  -# Activate Real time mode
//!  -# Run the code
//!  -# Watch ePWM A channel waveforms on a Oscilloscope
//!
//!  \b Watch \b Variables \n
//!  - UpdateFine
//!    - Set the variable UpdateFine = 1  to observe the ePWMxA output
//!      with HRPWM capabilities (default)
//!      Observe the period/frequency of the waveform changes in fine MEP steps
//!    - Change the variable UpdateFine to 0, to observe the
//!       ePWMxA output without HRPWM capabilities
//!  - UpdateCoarse
//!    - To change the period/frequency in coarse steps, uncomment the
//!      relevant code, re-build and re-run with UpdateCoarse = 1.
//!      Observe the period/frequency of the waveform changes in coarse
//!      SYSCLKOUT cycle steps.
//
//###########################################################################
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
//###########################################################################

//
// Included Files
//
#include "DSP28x_Project.h"         // DSP280xx Headerfile
#include "DSP2803x_EPwm_defines.h"
#include "SFO_V6.h"

//
//                      IMPORTANT
// UPDATE NUMBER OF HRPWM CHANNELS + 1  USED IN SFO_V6.H
// Configured for 4 HRPWM channels, but F2803x has a maximum 
// of 7 HRPWM channels (8=7+1)
// i.e.: #define PWM_CH 5   

//
// Function Prototypes
//
void HRPWM_Config(Uint16);
void error(void);
__interrupt void MainISR(void);

//
// Globals - useful for debug
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

Uint16	IsrTicker;

//
// Array of pointers to EPwm register structures:
// *ePWM[0] is defined as dummy value not used in the example
//
volatile struct EPWM_REGS *ePWM[PWM_CH] =
             {  &EPwm1Regs, &EPwm1Regs, &EPwm2Regs, &EPwm3Regs, &EPwm4Regs};

//
// Main
//
void main(void)
{
    //
    // Step 1. Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    // This example function is found in the DSP2803x_SysCtrl.c file.
    //
    InitSysCtrl();

    //
    // Step 2. Initialize GPIO:
    // This example function is found in the DSP2803x_Gpio.c file and
    // illustrates how to set the GPIO to it's default state.
    //
    // InitGpio();  // Skipped for this example
    InitEPwmGpio();

    //
    // Step 3. Clear all interrupts and initialize PIE vector table:
    // Disable CPU interrupts
    //
    DINT;

    //
    // Initialize the PIE control registers to their default state.
    // The default state is all PIE interrupts disabled and flags
    // are cleared.
    // This function is found in the DSP2803x_PieCtrl.c file.
    //
    InitPieCtrl();

    //
    // Disable CPU interrupts and clear all CPU interrupt flags:
    //
    IER = 0x0000;
    IFR = 0x0000;

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    // This will populate the entire table, even if the interrupt
    // is not used in this example.  This is useful for debug purposes.
    // The shell ISR routines are found in DSP2803x_DefaultIsr.c.
    // This function is found in DSP2803x_PieVect.c.
    //
    InitPieVectTable();

    //
    // Step 4. Initialize all the Device Peripherals:
    // Not required for this example
    //

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
    
    while  (status== SFO_INCOMPLETE) 
    {
        status = SFO();
        if (status == SFO_ERROR)
        {
            //
            // SFO function returns 2 if an error occurs & # of 
            // MEP steps/coarse step
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
    HRPWM_Config(Period);

    //
    // Software Control variables
    //
    Increment_Freq = 1;
    Increment_Freq_Fine = 1;
    IsrTicker = 0;
    UpdatePeriod = 0;
    UpdatePeriodFine = 0;

    //
    // User control variables:
    //
    UpdateCoarse = 0;
    UpdateFine = 1;

    //
    // Reassign ISRs.
    //
    EALLOW;	        // This is needed to write to EALLOW protected registers
    PieVectTable.EPWM1_INT = &MainISR;
    EDIS;

    //
    // Enable PIE group 3 interrupt 1 for EPWM1_INT
    //
    PieCtrlRegs.PIEIER3.bit.INTx1 = 1;

    //
    // Enable CNT_zero interrupt using EPWM1 Time-base
    //
    EPwm1Regs.ETSEL.bit.INTEN = 1;              // Enable EPWM1INT generation
    EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO; //Enable interrupt CNT_zero event
    EPwm1Regs.ETPS.bit.INTPRD = 1;       // Generate interrupt on the 1st event
    EPwm1Regs.ETCLR.bit.INT = 1;         // Enable more interrupts

    //
    // Enable CPU INT3 for EPWM1_INT:
    //
    IER |= M_INT3;

    //
    // Enable global Interrupts and higher priority real-time debug events:
    //
    EINT;                   // Enable Global interrupt INTM
    ERTM;	                // Enable Global realtime interrupt DBGM

    EALLOW;
    //
    // Synchronize high resolution phase to start HR period
    //
    EPwm1Regs.TBCTL.bit.SWFSYNC = 1; 
    EDIS;

    for(;;)
    {
        //
        // The below code controls coarse edge movement
        //
        if(UpdateCoarse==1)
        {
            if(Increment_Freq==1)       // Increase frequency to 600 kHz
            {
                Period= Period - 1;
            }
            
            else
            {
                Period= Period + 1;      // Decrease frequency to 300 kHz
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
            {
                PeriodFine=PeriodFine-1;
            }
            else
            {
                PeriodFine=PeriodFine+1; // Decrement high-resolution frequency
            }
            if(PeriodFine<=0x3333 && Increment_Freq_Fine==1)
            {
                Increment_Freq_Fine=0;
            }
            else if(PeriodFine>= 0xFFBF && Increment_Freq_Fine==0)
            {
                Increment_Freq_Fine=1;
            }

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
        // MEP calibration module continuously updates MEP_ScaleFactor in
        // background
        //
        status = SFO(); 
        
        if (status == SFO_ERROR)
        {
            //
            // SFO function returns 2 if an error occurs & # of 
            // MEP steps/coarse step
            //
            error();   
        }
    }
}

//
// MainISR - interrupts at ePWM1 TBCTR = 0. This ISR updates the compare and 
// period registers for all ePWM modules within the same period. User must 
// ensure that the PWM period is large enough to execute all of the code in the
// ISR before TBCTR = Period for all ePWM's.
//
__interrupt void 
MainISR(void)
{
    //
    // Sweep frequency coarsely between 300 kHz and 600 kHz.
    //
    if(UpdatePeriod==1)
    {
        EPwm1Regs.TBPRD = Period;
        EPwm1Regs.CMPA.half.CMPA = (Period >> 1);   // set duty 50%

        EPwm2Regs.TBPRD = Period;
        EPwm2Regs.CMPA.half.CMPA = (Period >> 1);   // set duty 50%

        EPwm3Regs.TBPRD = Period;
        EPwm3Regs.CMPA.half.CMPA = (Period >> 1);   // set duty 50%

        EPwm4Regs.TBPRD = Period;
        EPwm4Regs.CMPA.half.CMPA = (Period >> 1);   // set duty 50%
        UpdatePeriod=0;
    }

    //
    // The below is for fine edge movement
    //
    if(UpdatePeriodFine==1)
    {
        EPwm1Regs.TBPRDHR = PeriodFine;
        EPwm2Regs.TBPRDHR = PeriodFine;
        EPwm3Regs.TBPRDHR = PeriodFine;
        EPwm4Regs.TBPRDHR = PeriodFine;
        UpdatePeriodFine=0;
    }

   	IsrTicker++;

    //
	// Enable more interrupts from this EPWM
    //
	EPwm1Regs.ETCLR.bit.INT = 1;

    //
	// Acknowledge interrupt to receive more interrupts from PIE group 3
    //
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}

//
// HRPWM_Config - Configures all ePWM channels and sets up HRPWM on 
// ePWMxA channels. Parameters are the period which is the desired PWM period 
// in TBCLK counts
//
void 
HRPWM_Config(Uint16 period)
{
    Uint16 j;

    //
    // ePWM channel register configuration with HRPWM
    // ePWMxA toggle low/high with MEP control on Rising edge
    //
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;     // Disable TBCLK within the EPWM
    EDIS;

    for (j=1;j<PWM_CH;j++)
    {
        (*ePWM[j]).TBCTL.bit.PRDLD = TB_SHADOW;  // set Shadow load
        (*ePWM[j]).TBPRD = period;               // PWM frequency = 1/(2*TBPRD)
        (*ePWM[j]).TBPRDHR =0x54FF;
        (*ePWM[j]).CMPA.half.CMPA = period / 2;  // set duty 50% initially
        (*ePWM[j]).CMPA.half.CMPAHR = (1 << 8);  // initialize HRPWM extension
        (*ePWM[j]).CMPB = period / 2;            // set duty 50% initially

        if (j == 1)
        {
            //
            // Accounts for 1 cycle delay between ePWMj and ePWM1
            //
            (*ePWM[j]).TBPHS.half.TBPHS = 1;         
        }
        else
        {
            (*ePWM[j]).TBPHS.half.TBPHS = 0;
        }
        
        (*ePWM[j]).TBCTR = 0;

        //
        // Select up-down count mode
        //
        (*ePWM[j]).TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;     
        
        //
        // TBCTR phase load on SYNC (required for updown count HR control
        //
        (*ePWM[j]).TBCTL.bit.PHSEN = TB_ENABLE;             
        
        //
        // Synchronized with SYNC IN signal 
        // (either previous ePWM or SWFSYNC for ePWM1)
        //
        (*ePWM[j]).TBCTL.bit.SYNCOSEL = TB_SYNC_IN;
        (*ePWM[j]).TBCTL.bit.HSPCLKDIV = TB_DIV1;
        (*ePWM[j]).TBCTL.bit.CLKDIV = TB_DIV1;          // TBCLK = SYSCLKOUT
        (*ePWM[j]).TBCTL.bit.FREE_SOFT = 11;

        (*ePWM[j]).CMPCTL.bit.LOADAMODE = CC_CTR_ZERO; // LOAD CMPA on CTR = 0
        (*ePWM[j]).CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
        (*ePWM[j]).CMPCTL.bit.SHDWAMODE = CC_SHADOW;
        (*ePWM[j]).CMPCTL.bit.SHDWBMODE = CC_SHADOW;

        (*ePWM[j]).AQCTLA.bit.CAU = AQ_SET;       // PWM toggle high/low
        (*ePWM[j]).AQCTLA.bit.CAD = AQ_CLEAR;
        (*ePWM[j]).AQCTLB.bit.CAU = AQ_SET;       // PWM toggle high/low
        (*ePWM[j]).AQCTLB.bit.CAD = AQ_CLEAR;

        EALLOW;
        (*ePWM[j]).HRCNFG.all = 0x0;
        
        //
        // MEP control on both edges
        //
        (*ePWM[j]).HRCNFG.bit.EDGMODE = HR_BEP;          
        
        //
        // CMPAHR and TBPRDHR HR control
        //
        (*ePWM[j]).HRCNFG.bit.CTLMODE = HR_CMP;
        
        //
        // load on CTR = 0 and CTR = TBPRD
        //
        (*ePWM[j]).HRCNFG.bit.HRLOAD  = HR_CTR_ZERO_PRD; 
        
        //
        // Enable autoconversion for HR period
        //
        (*ePWM[j]).HRCNFG.bit.AUTOCONV = 1;  

        //
        // Enable TBPHSHR sync (required for updwn count HR control)
        //
        (*ePWM[j]).HRPCTL.bit.TBPHSHRLOADE = 1;          
        
        //
        // Turn on high-resolution period control.
        //
        (*ePWM[j]).HRPCTL.bit.HRPE = 1;                  

        SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;  // Enable TBCLK within the EPWM
        
        //
        // Synchronize high resolution phase to start HR period 
        // (Last step in HR initialization)
        //
        (*ePWM[j]).TBCTL.bit.SWFSYNC = 1;
        EDIS;
    }
}

void error (void)
{
    ESTOP0;         // Stop here and handle error
}

//
// End of File
//

