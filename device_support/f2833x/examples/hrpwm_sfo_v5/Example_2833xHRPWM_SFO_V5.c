//###########################################################################
//
// FILE:	Example_2833xHRPWM_SFO_V5.c
//
// TITLE:	High Resolution PWM SFO V5 Example
//
//! \addtogroup f2833x_example_list
//! <h1>High Resolution PWM SFO V5</h1>
//!
//! This example modifies the MEP control registers to show edge displacement
//! due to the HRPWM control extension of the respective ePWM module.
//!
//! \note By default, this example project is configured for floating-point 
//! math. All included libraries must be pre-compiled for floating-point math.
//! Therefore, SFO_TI_Build_V5B_fpu.lib (compiled for floating-point) is 
//! included in the project instead of the SFO_TI_Build_V5B.lib 
//! (compiled for fixed-point). To convert the example for fixed-point math, 
//! follow the instructions in sfo_readme.txt in the /doc directory of the 
//! header files and peripheral examples package.
//!
//! \note This program requires the DSP2833x header files, which include
//! the following files required for this example:
//! SFO_V5.h and SFO_TI_Build_V5B_fpu.lib (or SFO_TI_Build_V5B.lib for 
//! fixed point)
//!
//! This example calls the following TI's MEP Scale Factor Optimizer (SFO)
//! software library V5 functions:
//!
//! - \b int \b SFO_MepEn_V5(int i);   updates MEP_ScaleFactor[i] dynamically 
//!                                    when HRPWM is in use.
//! - \b Returns
//! 	- 1 when complete for the specified channel
//! 	- 0 if not complete for the specified channel
//! 	- 2 if there is a scale factor out-of-range error (MEP_ScaleFactor[n] 
//!         differs from seed MEP_ScaleFactor[0] by more than +/-15)
//!
//! - \b int \b SFO_MepDis_V5(int i);   updates MEP_ScaleFactor[i] when HRPWM 
//!                                     is not used
//! - \b Returns
//! 	- 1 when complete for the specified channel
//! 	- 0 if not complete for the specified channel
//!
//! This example is intended to explain the HRPWM capabilities. The code can be
//! optimized for code efficiency. Refer to TI's Digital power application
//! examples and TI Digital Power Supply software libraries for details.
//! All ePWM1A-6A channels will have fine
//! edge movement due to the HRPWM logic
//!
//! - 5MHz PWM (for 150 MHz SYSCLKOUT), ePWMxA toggle high/low with MEP control
//!   on rising edge
//! - 3.33MHz PWM (for 100 MHz SYSCLKOUT), ePWMxA toggle high/low with MEP
//!   control on rising edge
//!
//! \b Running \b the \b Application \n
//! -# \b **!!IMPORTANT!!** - in SFO_V5.h, set PWM_CH to the max number of
//! HRPWM channels plus one. For example, for the F28335, the
//! maximum number of HRPWM channels is 6. 6+1=7, so set
//! \#define PWM_CH 7 in SFO_V5.h. (Default is 7)
//! -# Run this example at 150/100MHz SYSCLKOUT
//! -# Load the Example_2833xHRPWM_SFO.gel and observe variables in the watch 
//!    window
//! -# Activate Real time mode
//! -# Run the code
//! -# Watch ePWM1-6 waveforms on a Oscilloscope
//! -# In the watch window:
//! Set the variable UpdateFine = 1  to observe the ePWMxA output
//! with HRPWM capabilities (default). Observe the duty cycle of the waveform
//! changes in fine MEP steps
//! -# In the watch window:
//! Change the variable UpdateFine to 0, to observe the
//! ePWMxA output without HRPWM capabilities. Observe the duty cycle of the
//! waveform changes in coarse steps of 10nsec.
//!
//! \b External \b Connections \n
//! Monitor the following pins on an oscilloscope:
//! - ePWM1A is on GPIO0
//! - ePWM2A is on GPIO2
//! - ePWM3A is on GPIO4
//! - ePWM4A is on GPIO6
//! - ePWM5A is on GPIO8
//! - ePWM6A is onGPIO10
//!
//! \b Watch \b Variables \n
//! - UpdateFine
//! - MEP_ScaleFactor
//! - EPwm1Regs.CMPA.all
//! - EPwm2Regs.CMPA.all
//! - EPwm3Regs.CMPA.all
//! - EPwm4Regs.CMPA.all
//! - EPwm5Regs.CMPA.all
//! - EPwm6Regs.CMPA.all
//
//###########################################################################
// $TI Release: $
// $Release Date: $
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
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "DSP2833x_EPwm_defines.h" 	// useful defines for initialization

//
// SFO V5 library headerfile - required to use SFO library functions
//
#include "SFO_V5.h"

//
//                          !!IMPORTANT!!
// UPDATE NUMBER OF HRPWM CHANNELS + 1  USED IN SFO_V5.H
// i.e. #define PWM_CH	   // F28335 has a maximum of 6 HRPWM channels (7=6+1)
//

//
// Declare your function prototypes here
//
void HRPWM_Config(int);
void error (void);

//
// General System nets - Useful for debug
//
Uint16 UpdateFine, DutyFine, status, nMepChannel;

//
// The following declarations are required in order to use the SFO
// library functions:
//

//
// Global array used by the SFO library. For n HRPWM channels + 1 for 
// MEP_ScaleFactor[0]
//
int MEP_ScaleFactor[PWM_CH];

//
// Array of pointers to EPwm register structures:
// *ePWM[0] is defined as dummy value not used in the example
//
volatile struct EPWM_REGS *ePWM[PWM_CH] =
 			 {  &EPwm1Regs, &EPwm1Regs, &EPwm2Regs,	&EPwm3Regs,
 			    &EPwm4Regs,	&EPwm5Regs,	&EPwm6Regs};

//
// Main 
//
void main(void)
{
    //
    // Local variables
    //
    int i;
    Uint32 temp;
    int16 CMPA_reg_val, CMPAHR_reg_val;

    //
    // Step 1. Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    // This example function is found in the DSP2833x_SysCtrl.c file.
    //
    InitSysCtrl();

    //
    // Step 2. Initialize GPIO:
    // This example function is found in the DSP2833x_Gpio.c file and
    // illustrates how to set the GPIO to it's default state.
    //
    // InitGpio();  // Skipped for this example

    //
    // For this case just init GPIO pins for ePWM1-ePWM6
    // This function is in the DSP2833x_EPwm.c file
    //
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
    // This function is found in the DSP2833x_PieCtrl.c file.
    //
    InitPieCtrl();

    //
    // Disable CPU interrupts and clear all CPU interrupt flags
    //
    IER = 0x0000;
    IFR = 0x0000;

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    // This will populate the entire table, even if the interrupt
    // is not used in this example.  This is useful for debug purposes.
    // The shell ISR routines are found in DSP2833x_DefaultIsr.c.
    // This function is found in DSP2833x_PieVect.c.
    //
    InitPieVectTable();

    //
    // Step 4. Initialize all the Device Peripherals:
    // This function is found in DSP2833x_InitPeripherals.c
    //
    // InitPeripherals();  // Not required for this example

    //
    // For this example, only initialize the ePWM
    // Step 5. User specific code, enable interrupts
    //

    UpdateFine = 1;
    DutyFine   = 0;
    nMepChannel=1;          // HRPWM diagnostics start on ePWM channel 1

    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;
    EDIS;

    //
    // MEP_ScaleFactor variables initialization for SFO library functions
    //
    for(i=0;i<PWM_CH;i++)
    {
        MEP_ScaleFactor[i] =0;
    }

    //
    // MEP_ScaleFactor variables initialization using SFO_MepDis_V5 library
    // function.
    //
    EALLOW;
    for(i=1;i<PWM_CH;i++)
    {
        //
        // Enable HRPWM logic for channel prior to calibration
        //
        (*ePWM[i]).HRCNFG.bit.EDGMODE = 1;
        
        while ( SFO_MepDis_V5(i) == SFO_INCOMPLETE );
        {
            //
            // returns "0" when cal. incomplete for channel
            //
        }
    }
    EDIS;

    //
    // Initialize a common seed variable MEP_ScaleFactor[0] required for all 
    // SFO functions
    //
    MEP_ScaleFactor[0] = MEP_ScaleFactor[1];

    //
    //  Some useful Period vs Frequency values
    //  SYSCLKOUT =     150MHz         100 MHz
    //  -----------------------------------------
    //	Period	        Frequency      Frequency
    //	1000			150 kHz		   100 KHz
    //	800				187 kHz		   125 KHz
    //	600				250 kHz		   167 KHz
    //	500				300 kHz		   200 KHz
    //	250				600 kHz		   400 KHz
    //	200				750 kHz		   500 KHz
    //	100				1.5 MHz		   1.0 MHz
    //	50				3.0 MHz		   2.0 MHz
    //	25				6.0 MHz		   4.0 MHz
    //	20				7.5 MHz		   5.0 MHz
    //	12				12.5 MHz	   8.33 MHz
    //	10				15.0 MHz	   10.0 MHz
    //	9				16.7 MHz	   11.1 MHz
    //	8				18.8 MHz	   12.5 MHz
    //	7				21.4 MHz	   14.3 MHz
    //	6				25.0 MHz	   16.7 MHz
    //	5				30.0 MHz	   20.0 MHz
    //
    
    //
    // ePWM and HRPWM register initialization
    //
    
    //
    // ePWMx target, 5 MHz PWM(150MHz SYSCLKOUT)/3.33 MHz PWM(100MHz SYSCLKOUT)
    //
    HRPWM_Config(30);

    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;

    for(;;)
    {
        //
        // Sweep DutyFine as a Q15 number from 0.2 - 0.999
        //
        for(DutyFine = 0x2300; DutyFine < 0x7000; DutyFine++)
        {
            if(UpdateFine)
            {
                /*
                //
                // CMPA_reg_val is calculated as a Q0.
                // Since DutyFine is a Q15 number, and the period is Q0
                // the product is Q15. So to store as a Q0, we shift right
                // 15 bits.
                //
                CMPA_reg_val = ((long)DutyFine * EPwm1Regs.TBPRD)>>15;

                //
                // This next step is to obtain the remainder which was
                // truncated during our 15 bit shift above.
                // compute the whole value, and then subtract CMPA_reg_val
                // shifted LEFT 15 bits:
                //
                temp = ((long)DutyFine * EPwm1Regs.TBPRD) ;
                temp = temp - ((long)CMPA_reg_val<<15);

                //
                // This obtains the MEP count in digits, from
                // 0,1, .... MEP_Scalefactor. Once again since this is Q15
                // convert to Q0 by shifting:
                //
                CMPAHR_reg_val = (temp*MEP_ScaleFactor[1])>>15;

                //
                // Now the lower 8 bits contain the MEP count.
                // Since the MEP count needs to be in the upper 8 bits of
                // the 16 bit CMPAHR register, shift left by 8.
                //
                CMPAHR_reg_val = CMPAHR_reg_val << 8;

                //
                // Add the offset and rounding
                //
                CMPAHR_reg_val += 0x0180;

                //
                // Write the values to the registers as one 32-bit or 
                // two 16-bits
                //
                EPwm1Regs.CMPA.half.CMPA = CMPA_reg_val;
                EPwm1Regs.CMPA.half.CMPAHR = CMPAHR_reg_val;

                //
                // All the above operations may be condensed into
                // the following form for each channel:
                //
                */

                //
                // EPWM calculations where EPwm1Regs are accessed
                // by (*ePWM[1]), EPwm2Regs are accessed by (*ePWM[2]),
                // etc.:
                //
                for(i=1;i<PWM_CH;i++)
                {
                    CMPA_reg_val = ((long)DutyFine * (*ePWM[i]).TBPRD)>>15;
                    temp = ((long)DutyFine * (*ePWM[i]).TBPRD) ;
                    temp = temp - ((long)CMPA_reg_val<<15);
                    CMPAHR_reg_val = (temp*MEP_ScaleFactor[i])>>15;
                    CMPAHR_reg_val = CMPAHR_reg_val << 8;
                    CMPAHR_reg_val += 0x0180;

                    //
                    // Example for a 32 bit write to CMPA:CMPAHR
                    //
                    (*ePWM[i]).CMPA.all = ((long)CMPA_reg_val)<<16 | 
                                            CMPAHR_reg_val;
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
                for(i=1;i<PWM_CH;i++)
                {
                    (*ePWM[i]).CMPA.half.CMPA = ((long)DutyFine * 
                                                (*ePWM[i]).TBPRD>>15);
                }
            }

            //
            // Call the scale factor optimizer lib function SFO_MepEn_V5()
            // periodically to track for any changes due to temp/voltage.
            // SFO_MepEn_V5 Calibration must be finished on one channel
            // (return 1) before moving on to the next channel.
            //
            // *NOTE*: In this example, SFO_MepEn_V5 is called 700 times in a 
            //         loop. For example purposes, this allows the CMPAHR and 
            //         CMPA registers to change in such a way that when 
            //         watching in "Continuous Refresh" mode, the user
            //         can see the CMPAHR register increment in fine steps to a
            //         certain point before the CMPA register increments in a 
            //         coarse step. Normally, SFO_MepEn_V5 can be called once 
            //         every so often in the background for a slow update with 
            //         no for-loop.
            //
            
            //
            // Call SFO_MepEn_V5 700 times.
            //
            for (i=0; i<700; i++)
            {
                status = SFO_MepEn_V5(nMepChannel);
                
                //
                // Once SFO_MepEn_V5 complete (returns 1)-
                //
                if (status == SFO_COMPLETE)
                {
                    nMepChannel++;  // move on to next channel
                }
                                
                //
                // If MEP_ScaleFactor[nMepChannel] differs from seed 
                // Mep_ScaleFactor[0] by more than +/-15, status = 2 
                // (out of range error)
                //
                else if (status == SFO_OUTRANGE_ERROR)
                {
                    error();
                }
                
                if(nMepChannel==PWM_CH)
                {
                    //
                    // Once max channels reached, loop back to channel 1
                    //
                    nMepChannel =1;
                }
            }
        }
    }
}

//
// HRPWM_Config - Configures all ePWM channels and sets up HRPWM on 
// PWMxA channels
//
void
HRPWM_Config(period)
{
    Uint16 j;
    
    //
    // ePWM channel register configuration with HRPWM
    // ePWMxA toggle low/high with MEP control on Rising edge
    //
    for (j=1;j<PWM_CH;j++)
    {
        (*ePWM[j]).TBCTL.bit.PRDLD = TB_IMMEDIATE;	// set Immediate load
        (*ePWM[j]).TBPRD = period-1;		      // PWM frequency = 1 / period
        (*ePWM[j]).CMPA.half.CMPA = period / 2;   // set duty 50% initially
        (*ePWM[j]).CMPA.half.CMPAHR = (1 << 8);   // initialize HRPWM extension
        (*ePWM[j]).CMPB = period / 2;	          // set duty 50% initially
        (*ePWM[j]).TBPHS.all = 0;
        (*ePWM[j]).TBCTR = 0;

        (*ePWM[j]).TBCTL.bit.CTRMODE = TB_COUNT_UP;
        (*ePWM[j]).TBCTL.bit.PHSEN = TB_DISABLE;
        (*ePWM[j]).TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
        (*ePWM[j]).TBCTL.bit.HSPCLKDIV = TB_DIV1;
        (*ePWM[j]).TBCTL.bit.CLKDIV = TB_DIV1;
        (*ePWM[j]).TBCTL.bit.FREE_SOFT = 11;

        (*ePWM[j]).CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
        (*ePWM[j]).CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
        (*ePWM[j]).CMPCTL.bit.SHDWAMODE = CC_SHADOW;
        (*ePWM[j]).CMPCTL.bit.SHDWBMODE = CC_SHADOW;


        (*ePWM[j]).AQCTLA.bit.ZRO = AQ_SET;    // PWM toggle high/low
        (*ePWM[j]).AQCTLA.bit.CAU = AQ_CLEAR;
        (*ePWM[j]).AQCTLB.bit.ZRO = AQ_SET;
        (*ePWM[j]).AQCTLB.bit.CBU = AQ_CLEAR;

        EALLOW;
        (*ePWM[j]).HRCNFG.all = 0x0;
        (*ePWM[j]).HRCNFG.bit.EDGMODE = HR_FEP; // MEP control on falling edge
        (*ePWM[j]).HRCNFG.bit.CTLMODE = HR_CMP;
        (*ePWM[j]).HRCNFG.bit.HRLOAD  = HR_CTR_ZERO;
        EDIS;
    }
}

//
// error - An error occurs when the MEP_ScaleFactor [n] calculated from
// SFO_MEPEn_V5 differs by > +/- 15 from the Seed Value in MEP_ScaleFactor[0].
// SFO_MepEn_V5 returned a "2" (SFO_OUTRANGE_ERROR). The user should:
// (1) Re-run SFO_MepDis_V5 to re-calibrate an appropriate seed value.
// (2) Ensure the code is not calling Mep_En_V5 on a different channel when it 
//     is currently still running on a channel. (Repetitively call Mep_En_V5 
//     on current channel until an SFO_COMPLETE ( i.e. 1) is returned.
// (3) If the out-of-range condition is acceptable for the application, ignore 
//     the "2" and treat it as a "1" or SFO_COMPLETE.
//
void
error (void)
{
    //
    // Error - MEP_ScaleFactor out of range of Seed - rerun MepDis calibration.
    //
    ESTOP0;
}

//
// End of File
//

