//###########################################################################
//
// FILE:    hrpwm_ex2_prdupdown_sfo_v8.c
//
// TITLE:   HRPWM SFO V8 High-Resolution Period (Up-Down Count)
//          example
//
//! \addtogroup cpu01_example_list
//! <h1> HRPWM SFO Test (hrpwm_prdupdown_sfo_v8)</h1>
//!
//! This program requires the header files, which include
//! the following files required for this example:
//! sfo_v8.h and SFO_v8_fpu_lib_build_c28_eabi.lib
//!
//! Monitor ePWM1-ePWM7 A/B pins on an oscilloscope.
//! DESCRIPTION:
//!
//! This example modifies the MEP control registers to show edge displacement
//! for high-resolution period with ePWM in Up-Down count mode
//! due to the HRPWM control extension of the respective ePWM module.
//!
//! This example calls the following TI's MEP Scale Factor Optimizer (SFO)
//! software library V8 functions:
//!
//! \b int \b SFO(); \n
//! - updates MEP_ScaleFactor dynamically when HRPWM is in use
//! - updates HRMSTEP register (exists only in EPwm1Regs register space)
//!   with MEP_ScaleFactor value
//! - returns 2 if error: MEP_ScaleFactor is greater than maximum value of 255
//!   (Auto-conversion may not function properly under this condition)
//! - returns 1 when complete for the specified channel
//! - returns 0 if not complete for the specified channel
//!
//! This example is intended to explain the HRPWM capabilities. The code can be
//! optimized for code efficiency. Refer to TI's Digital power application
//! examples and TI Digital Power Supply software libraries for details.
//!
//!
//! =======================================================================
//! NOTE: For more information on using the SFO software library, see the
//! High-Resolution Pulse Width Modulator (HRPWM) Reference Guide
//! =======================================================================
//!
//! To load and run this example:
//! -# **!!IMPORTANT!!**
//! -# Run this example at maximum SYSCLKOUT
//! -# Activate Real time mode
//! -# Run the code
//! -# Watch ePWM A / B channel waveforms on an Oscilloscope
//! -# In the watch window:
//!    Set the variable UpdateFine = 1  to observe the ePWMxA & ePWMxB output
//!    with HRPWM capabilities (default)
//!    Observe the period/frequency of the waveform changes in fine MEP steps
//! -# In the watch window:
//!    Change the variable UpdateFine to 0, to observe the
//!    ePWMxA & ePWMxB output without HRPWM capabilities
//!    Observe the period/frequency of the waveform changes in coarse SYSCLKOUT
//!    cycle steps.
//
//###########################################################################
//
//
// 
// C2000Ware v5.04.00.00
//
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
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
#include "f28x_project.h"
#include "sfo_v8.h"

//
// Defines
//
#define PWM_CH            9       // # of PWM channels + 1
#define STATUS_SUCCESS    1
#define STATUS_FAIL       0

//
// Globals
//
Uint16 UpdateFine, PeriodFine, status;

int MEP_ScaleFactor; // Global variable used by the SFO library
                     // Result can be used for all HRPWM channels
                     // This variable is also copied to HRMSTEP
                     // register by SFO(0) function.

//
// Array of pointers to EPwm register structures:
// *ePWM[0] is defined as dummy value not used in the example
//
volatile struct EPWM_REGS *ePWM[PWM_CH] = {0, &EPwm1Regs, &EPwm2Regs,
                                           &EPwm3Regs, &EPwm4Regs,
                                           &EPwm5Regs, &EPwm6Regs,
                                           &EPwm7Regs, &EPwm8Regs};

//
// Function Prototypes
//
void HRPWM_Config(int);
void error(void);
void InitEPwmGpio(void);
//
// Main
//
void main(void)
{
    int i;

    EALLOW; // This is needed to write to EALLOW protected registers

    //
    // Initialize System Control for Control and Analog Subsystems
    // Enable Peripheral Clocks
    //
    InitSysCtrl();

    EDIS;

    //
    // EPWM1A and EPWM1B through all PWMS
    //
    InitEPwmGpio();

    DINT; // Disable CPU interrupts

    //
    // Initialize PIE control registers to their default state.
    // The default state is all PIE interrupts disabled and flags
    // are cleared.
    //
    InitPieCtrl();

    //
    // Disable CPU interrupts and clear all CPU interrupt flags:
    //
    EALLOW;
    IER = 0x0000;
    IFR = 0x0000;

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    // This will populate the entire table, even if the interrupt
    // is not used in this example.  This is useful for debug purposes.
    //
    InitPieVectTable();

    //
    // Initialize system variables, enable HRPWM
    //
    UpdateFine = 1;
    PeriodFine = 0;
    status = SFO_INCOMPLETE;

    //
    // Enable global Interrupts and higher priority real-time debug events:
    //
    EINT;   // Enable Global interrupt INTM
    ERTM;   // Enable Global realtime interrupt DBGM

    //
    // Calling SFO() updates the HRMSTEP register with calibrated
    // MEP_ScaleFactor. HRMSTEP must be populated with a scale factor
    // value prior to enabling high resolution period control.
    //
    while(status == SFO_INCOMPLETE) // Call until complete
    {
        status = SFO();
        if(status == SFO_ERROR)
        {
            error();    // SFO function returns 2 if an error occurs & # of MEP
        }               // steps/coarse step exceeds maximum of 255.
    }

    //
    // ePWM and HRPWM register initialization
    //
    HRPWM_Config(20);   // ePWMx target
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
                // EPwm1Regs.TBPRDHR = PeriodFine;
                //
                // The hardware will automatically scale
                // the fractional period by the MEP_ScaleFactor
                // in the HRMSTEP register (which is updated
                // by the SFO calibration software).
                //
                // Hardware conversion:
                // MEP delay movement = ((TBPRDHR(15:0) >> 8) *  HRMSTEP(7:0) +
                //                       0x80) >> 8
                //
                for(i = 1;i < PWM_CH; i++)
                {
                    (*ePWM[i]).TBPRDHR = PeriodFine; //In Q16 format
                }
            }
            else
            {
                //
                // No high-resolution movement on TBPRDHR.
                //
                for(i = 1;i < PWM_CH; i++)
                {
                    (*ePWM[i]).TBPRDHR = 0;
                }
            }

            //
            // Call the scale factor optimizer lib function SFO(0)
            // periodically to track for any change due to temp/voltage.
            // This function generates MEP_ScaleFactor by running the
            // MEP calibration module in the HRPWM logic. This scale
            // factor can be used for all HRPWM channels. HRMSTEP
            // register is automatically updated by the SFO function.
            //
            status = SFO(); // in background, MEP calibration module
                            // continuously updates MEP_ScaleFactor

            if(status == SFO_ERROR)
            {
                error();   // SFO function returns 2 if an error occurs & # of
            }              // MEP steps/coarse step exceeds maximum of 255.
        } // end PeriodFine for loop
    } // end infinite for loop
}

//
// HRPWM_Config - Configures all ePWM channels and sets up HRPWM
//                on ePWMxA channels &  ePWMxB channels
//
void HRPWM_Config(period)
{
    Uint16 j;

    //
    // ePWM channel register configuration with HRPWM
    // ePWMxA toggle low/high with MEP control on Rising edge
    //
    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;   // Disable TBCLK within the EPWM
    EDIS;

    for(j = 1;j < PWM_CH;j++)
    {
        (*ePWM[j]).TBCTL.bit.PRDLD = TB_SHADOW;  // set Shadow load
        (*ePWM[j]).TBPRD = period;               // PWM frequency = 1/(2*TBPRD)
        (*ePWM[j]).CMPA.bit.CMPA = period / 2;   // set duty 50% initially
        (*ePWM[j]).CMPA.bit.CMPAHR = (1 << 8);   // initialize HRPWM extension
        (*ePWM[j]).CMPB.bit.CMPB = period / 2;   // set duty 50% initially
        (*ePWM[j]).CMPB.all |= 1;
        (*ePWM[j]).TBPHS.all = 0;
        (*ePWM[j]).TBCTR = 0;

        (*ePWM[j]).TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Select up-down
                                                        // count mode
        (*ePWM[j]).EPWMSYNCINSEL.all = SYNC_IN_SRC_DISABLE_ALL;
        (*ePWM[j]).EPWMSYNCOUTEN.all = SYNC_OUT_SRC_DISABLE_ALL;
        (*ePWM[j]).TBCTL.bit.HSPCLKDIV = TB_DIV1;
        (*ePWM[j]).TBCTL.bit.CLKDIV = TB_DIV1;          // TBCLK = SYSCLKOUT
        (*ePWM[j]).TBCTL.bit.FREE_SOFT = 11;

        (*ePWM[j]).CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;  // LOAD CMPA on CTR = 0
        (*ePWM[j]).CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
        (*ePWM[j]).CMPCTL.bit.SHDWAMODE = CC_SHADOW;
        (*ePWM[j]).CMPCTL.bit.SHDWBMODE = CC_SHADOW;

        (*ePWM[j]).AQCTLA.bit.CAU = AQ_SET;             // PWM toggle high/low
        (*ePWM[j]).AQCTLA.bit.CAD = AQ_CLEAR;
        (*ePWM[j]).AQCTLB.bit.CBU = AQ_SET;             // PWM toggle high/low
        (*ePWM[j]).AQCTLB.bit.CBD = AQ_CLEAR;

        EALLOW;
        (*ePWM[j]).HRCNFG.all = 0x0;
        (*ePWM[j]).HRCNFG.bit.EDGMODE = HR_BEP;          // MEP control on
                                                         // both edges.
        (*ePWM[j]).HRCNFG.bit.CTLMODE = HR_CMP;          // CMPAHR and TBPRDHR
                                                         // HR control.
        (*ePWM[j]).HRCNFG.bit.HRLOAD = HR_CTR_ZERO_PRD;  // load on CTR = 0
                                                         // and CTR = TBPRD
        (*ePWM[j]).HRCNFG.bit.EDGMODEB = HR_BEP;         // MEP control on
                                                         // both edges
        (*ePWM[j]).HRCNFG.bit.CTLMODEB = HR_CMP;         // CMPBHR and TBPRDHR
                                                         // HR control
        (*ePWM[j]).HRCNFG.bit.HRLOADB = HR_CTR_ZERO_PRD; // load on CTR = 0
                                                         // and CTR = TBPRD
        (*ePWM[j]).HRCNFG.bit.AUTOCONV = 1;        // Enable autoconversion for
                                                   // HR period

        (*ePWM[j]).HRPCTL.bit.TBPHSHRLOADE = 1;    // Enable TBPHSHR sync
                                                   // (required for updwn
                                                   //  count HR control)
        (*ePWM[j]).HRPCTL.bit.HRPE = 1;            // Turn on high-resolution
                                                   // period control.

        CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;      // Enable TBCLK within
                                                   // the EPWM
        (*ePWM[j]).TBCTL.bit.SWFSYNC = 1;          // Synchronize high
                                                   // resolution phase to
                                                   // start HR period
        EDIS;
    }
}

//
// error - Halt debugger when error occurs
//
void error (void)
{
    ESTOP0;         // Stop here and handle error
}

//
// End of file
//
