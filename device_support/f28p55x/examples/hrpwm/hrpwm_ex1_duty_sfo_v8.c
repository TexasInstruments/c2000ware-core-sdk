//###########################################################################
//
// FILE:    hrpwm_ex1_duty_sfo_v8.c
//
// TITLE:   HRPWM SFO V8 High-Resolution Period
//          (Up-Down Count) example
//
//! \addtogroup cpu01_example_list
//! <h1> HRPWM Duty SFO (hrpwm_duty_sfo_v8)</h1>
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
//! -# Watch ePWM A / B channel waveforms on a Oscilloscope
//! -# In the watch window:
//!    Set the variable UpdateFine = 1  to observe the ePWMxA & ePWMxB output
//!    with HRPWM capabilities (default)
//!    Observe the period/frequency of the waveform changes in fine MEP steps
//! -# In the watch window:
//!    Change the variable UpdateFine to 0, to observe the
//!    ePWMxA & ePWMxB output without HRPWM capabilities
//!    Observe the period/frequency of the waveform changes in coarse
//!    SYSCLKOUT cycle steps.
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

#define AUTOCONVERT       0       // 1 = Turn auto-conversion ON
                                  // 0 = Turn auto-conversion OFF

//
// Globals
//
Uint16 UpdateFine;
Uint16 DutyFine;
Uint16 status;
Uint16 CMPA_reg_val;
Uint16 CMPAHR_reg_val;
Uint16 CMPB_reg_val;
Uint16 CMPBHR_reg_val;

int MEP_ScaleFactor; // Global variable used by the SFO library
                     // Result can be used for all HRPWM channels
                     // This variable is also copied to HRMSTEP
                     // register by SFO() function.

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
void InitEPwm1Gpio(void);
void InitEPwm2Gpio(void);
void InitEPwm3Gpio(void);
void InitEPwm4Gpio(void);
void InitEPwm5Gpio(void);
void InitEPwm6Gpio(void);
void InitEPwm7Gpio(void);
void InitEPwm8Gpio(void);
void InitEPwm9Gpio(void);
void InitEPwm10Gpio(void);
void InitEPwm11Gpio(void);
void InitEPwm12Gpio(void);

//
// Main
//
void main(void)
{
    int i;
    Uint32 temp, temp1;

    //
    // Initialize System Control for Control and Analog Subsystems
    // Enable Peripheral Clocks
    //
    EALLOW;
    InitSysCtrl();
    EDIS;

    //
    // Initialize GPIO
    //
    InitEPwm1Gpio();
    InitEPwm2Gpio();
    InitEPwm3Gpio();
    InitEPwm4Gpio();
    InitEPwm5Gpio();
    InitEPwm6Gpio();
    InitEPwm7Gpio();
    InitEPwm8Gpio();
    InitEPwm9Gpio();
    InitEPwm10Gpio();
    InitEPwm11Gpio();
    InitEPwm12Gpio();


    DINT; // Disable CPU interrupts

    //
    // Initialize PIE control registers to their default state.
    // The default state is all PIE interrupts disabled and flags
    // are cleared.
    //
    InitPieCtrl();

    //
    // Disable CPU interrupts and clear all CPU interrupt flags
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
    // For this example, only initialize the ePWM
    // User specific code, enable interrupts:
    //
    UpdateFine = 1;
    DutyFine = 0;
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
    while(status == SFO_INCOMPLETE)
    {
        status = SFO();
        if(status == SFO_ERROR)
        {
            error();   // SFO function returns 2 if an error occurs & # of MEP
        }              // steps/coarse step exceeds maximum of 255.
    }

    //
    // ePWM and HRPWM register initialization
    //
    HRPWM_Config(10);   // ePWMx target
    EALLOW;

    for(;;)
    {
        //
        // Sweep DutyFine as a Q15 number from 0.2 - 0.999
        //
        for(DutyFine = 0x199A; DutyFine < 0x7FDF; DutyFine++)
        {
            if(UpdateFine)
            {

                /* All below calculations apply for CMPB as well.
                // CMPA_reg_val , CMPAHR_reg_val is calculated as a Q0.
                // Since DutyFine is a Q15 number, and the period is Q0
                // the product is Q15. So to store as a Q0, we shift right
                // 15 bits.

                CMPA_reg_val = ((long)DutyFine * (EPwm1Regs.TBPRD + 1)) >> 15;

                // This next step is to obtain the remainder which was
                // truncated during our 15 bit shift above.
                // compute the whole value, and then subtract CMPA_reg_val
                // shifted LEFT 15 bits:
                temp = ((long)DutyFine * (EPwm1Regs.TBPRD + 1)) ;
                temp = temp - ((long)CMPA_reg_val << 15);

                ** If auto-conversion is disabled, the following step can be
                // skipped. If autoconversion is enabled, the SFO function will
                // write the MEP_ScaleFactor to the HRMSTEP register and the
                // hardware will automatically scale the remainder in the CMPAHR
                // register by the MEP_ScaleFactor.
                // Because the remainder calculated above (temp) is in Q15
                // format, it must be shifted left by 1 to convert to Q16 format
                // for the hardware to properly convert.
                CMPAHR_reg_val = temp << 1;

                ** If auto-conversion is enabled, the following step is
                   performed automatically in hardware and can be skipped
                // This obtains the MEP count in digits, from
                // 0,1, .... MEP_Scalefactor.
                // 0x0080 (0.5 in Q8) is converted to 0.5 in Q15 by shifting
                // left 7. This is added to fractional duty * MEP_SF product in
                // order to round the decimal portion of the product up to the
                // next integer if the decimal portion is >= 0.5.
                //
                // Once again since this is Q15 convert to Q0 by shifting:
                //
                CMPAHR_reg_val = (temp * MEP_ScaleFactor + (0x0080 << 7)) >> 15;

                ** If auto-conversion is enabled, the following step is
                   performed automatically in hardware and can be skipped
                // Now the lower 8 bits contain the MEP count.
                // Since the MEP count needs to be in the upper 8 bits of
                // the 16 bit CMPAHR register, shift left by 8.
                CMPAHR_reg_val = CMPAHR_reg_val << 8;

                // Write the values to the registers as one 32-bit or two
                // 16-bits
                EPwm1Regs.CMPA.bit.CMPA = CMPA_reg_val;
                EPwm1Regs.CMPA.bit.CMPAHR = CMPAHR_reg_val;
                */

                //
                // All the above operations may be condensed into the following
                // form:
                //
                for(i = 1;i < PWM_CH;i++)
                {
                    CMPA_reg_val = ((long)DutyFine * ((*ePWM[i]).TBPRD + 1)) >> 15;
                    CMPB_reg_val = ((long)DutyFine * ((*ePWM[i]).TBPRD + 1)) >> 15;
                    temp = ((long)DutyFine * ((*ePWM[i]).TBPRD + 1)) ;
                    temp1 = ((long)DutyFine * ((*ePWM[i]).TBPRD + 1)) ;
                    temp = temp - ((long)CMPA_reg_val << 15);
                    temp1 = temp1 - ((long)CMPB_reg_val << 15);

                   #if(AUTOCONVERT)
                    CMPAHR_reg_val = temp << 1; // convert to Q16
                    CMPBHR_reg_val = temp << 1; // convert to Q16
                   #else
                    CMPAHR_reg_val = ((temp * MEP_ScaleFactor) +
                                      (0x0080 << 7)) >> 15;
                    CMPAHR_reg_val = CMPAHR_reg_val << 8;
                    CMPBHR_reg_val = ((temp1 * MEP_ScaleFactor) +
                                      (0x0080 << 7)) >> 15;
                    CMPBHR_reg_val = CMPBHR_reg_val << 8;
                   #endif

                   //
                   // Example for a 32 bit write to CMPA:CMPAHR
                   //
                    (*ePWM[i]).CMPA.all = ((long)CMPA_reg_val) << 16 |
                                          CMPAHR_reg_val; // loses lower 8-bits
                   //
                   // Example for a 32 bit write to CMPB:CMPBHR
                   //
                    (*ePWM[i]).CMPB.all = ((long)CMPB_reg_val) << 16 |
                                          CMPBHR_reg_val; // loses lower 8-bits
                }
            }
            else
            {
                //
                // CMPA_reg_val is calculated as a Q0.
                // Since DutyFine is a Q15 number, and the period is Q0
                // the product is Q15. So to store as a Q0, we shift right
                // 15 bits.
                //
                for(i = 1;i < PWM_CH;i++)
                {
                    (*ePWM[i]).CMPA.bit.CMPA = (((long)DutyFine *
                                                ((*ePWM[i]).TBPRD + 1)) >> 15);
                    (*ePWM[i]).CMPB.bit.CMPB = (((long)DutyFine *
                                                ((*ePWM[i]).TBPRD + 1)) >> 15);
                }
            }

            //
            // Call the scale factor optimizer lib function SFO()
            // periodically to track for any change due to temp/voltage.
            // This function generates MEP_ScaleFactor by running the
            // MEP calibration module in the HRPWM logic. This scale
            // factor can be used for all HRPWM channels. The SFO()
            // function also updates the HRMSTEP register with the
            // scale factor value.
            //
            status = SFO(); // in background, MEP calibration module
                            // continuously updates MEP_ScaleFactor

            if(status == SFO_ERROR)
            {
                error();   // SFO function returns 2 if an error occurs & #
                           // of MEP steps/coarse step
            }              // exceeds maximum of 255.
        } // end DutyFine for loop
    } // end infinite for loop
}

//
// HRPWM_Config - Configures all ePWM channels and sets up HRPWM
//                on ePWMxA / ePWMxB  channels
//
void HRPWM_Config(period)
{
    Uint16 j;

    //
    // ePWM channel register configuration with HRPWM
    // ePWMxA / ePWMxB toggle low/high with MEP control on Rising edge
    //
    for (j = 1;j < PWM_CH;j++)
    {
        (*ePWM[j]).TBCTL.bit.PRDLD = TB_SHADOW;  // set Shadow load
        (*ePWM[j]).TBPRD = period-1;             // PWM frequency = 1 / period
        (*ePWM[j]).CMPA.bit.CMPA = period / 2;   // set duty 50% initially
        (*ePWM[j]).CMPA.bit.CMPAHR = (1 << 8);   // initialize HRPWM extension
        (*ePWM[j]).CMPB.bit.CMPB = period / 2;   // set duty 50% initially
        (*ePWM[j]).CMPB.all |= (1 << 8);         // initialize HRPWM extension
        (*ePWM[j]).TBPHS.all = 0;
        (*ePWM[j]).TBCTR = 0;

        (*ePWM[j]).TBCTL.bit.CTRMODE = TB_COUNT_UP;
        (*ePWM[j]).TBCTL.bit.PHSEN = TB_DISABLE;
        (*ePWM[j]).EPWMSYNCINSEL.all = SYNC_IN_SRC_DISABLE_ALL;
        (*ePWM[j]).EPWMSYNCOUTEN.all = SYNC_OUT_SRC_DISABLE_ALL;
        (*ePWM[j]).TBCTL.bit.HSPCLKDIV = TB_DIV1;
        (*ePWM[j]).TBCTL.bit.CLKDIV = TB_DIV1;
        (*ePWM[j]).TBCTL.bit.FREE_SOFT = 11;

        (*ePWM[j]).CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
        (*ePWM[j]).CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
        (*ePWM[j]).CMPCTL.bit.SHDWAMODE = CC_SHADOW;
        (*ePWM[j]).CMPCTL.bit.SHDWBMODE = CC_SHADOW;


        (*ePWM[j]).AQCTLA.bit.ZRO = AQ_SET;      // PWM toggle high/low
        (*ePWM[j]).AQCTLA.bit.CAU = AQ_CLEAR;
        (*ePWM[j]).AQCTLB.bit.ZRO = AQ_SET;
        (*ePWM[j]).AQCTLB.bit.CBU = AQ_CLEAR;

        EALLOW;
        (*ePWM[j]).HRCNFG.all = 0x0;
        (*ePWM[j]).HRCNFG.bit.EDGMODE = HR_FEP;  // MEP control on falling edge
        (*ePWM[j]).HRCNFG.bit.CTLMODE = HR_CMP;
        (*ePWM[j]).HRCNFG.bit.HRLOAD  = HR_CTR_ZERO;
        (*ePWM[j]).HRCNFG.bit.EDGMODEB = HR_FEP; // MEP control on falling edge
        (*ePWM[j]).HRCNFG.bit.CTLMODEB = HR_CMP;
        (*ePWM[j]).HRCNFG.bit.HRLOADB  = HR_CTR_ZERO;
        #if(AUTOCONVERT)
        (*ePWM[j]).HRCNFG.bit.AUTOCONV = 1;      // Enable auto-conversion
                                                 // logic
        #endif
        (*ePWM[j]).HRPCTL.bit.HRPE = 0; // Turn off high-resolution period
                                        // control.
        EDIS;
    }
}

//
// error - Halt debugger when called
//
void error (void)
{
    ESTOP0;         // Stop here and handle error
}

//
// End of file
//
