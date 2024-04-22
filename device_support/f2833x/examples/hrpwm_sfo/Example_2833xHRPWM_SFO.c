//###########################################################################
//
// FILE:	Example_2833xHRPWM_SFO.c
//
// TITLE:	High Resolution PWM SFO Example
//
//! \addtogroup f2833x_example_list
//! <h1>High Resolution PWM SFO</h1>
//!
//! This example modifies the MEP control registers to show edge displacement
//! due to the HRPWM control extension of the respective ePWM module.
//!
//! \note By default, this example project is configured for floating-point 
//! math. All included libraries must be pre-compiled for floating-point math.
//! Therefore, SFO_TI_Build_fpu.lib (compiled for floating-point) is included
//! in the project instead of the SFO_TI_Build.lib (compiled for fixed-point).
//! To convert the example for fixed-point math, follow the instructions in 
//! sfo_readme.txt in the /doc directory of the header files and peripheral 
//! examples package.
//!
//! This example calls the following TI's MEP Scale Factor Optimizer (SFO)
//! software library functions:
//!
//! - \b void \b SFO_MepEn(int i);  initialize MEP_Scalefactor[i] dynamically
//!    when HRPWM is in use.  
//!
//! - \b void \b SFO_MepDis(int i);  initialize MEP_Scalefactor[i] when HRPWM 
//!   is not used
//!
//! Where MEP_ScaleFactor[5] is a global array variable used by 
//! the SFO library.
//!
//! This example is intended to explain the HRPWM capabilities. The code can be
//! optimized for code efficiency. Refer to TI's Digital power application
//! examples and TI Digital Power Supply software libraries for details.
//!
//! All ePWM1A,2A,3A,4A channels (GPIO0, GPIO2, GPIO4, GPIO6) will have fine
//! edge movement due to the HRPWM logic
//!
//! -# 5MHz PWM (SYSCLK=150MHz) or 3.33MHz PWM (SYSCLK=100MHz), ePWM1A toggle 
//!    low/high with MEP control on falling edge
//! -# 5MHz PWM (SYSCLK=150MHz) or 3.33MHz PWM (SYSCLK=100MHz) ePWM2A toggle
//!    low/high with MEP control on falling edge
//! -# 5MHz PWM (SYSCLK=150MHz) or 3.33MHz PWM (SYSCLK=100MHz) ePWM3A toggle
//!    high/low with MEP control on falling edge
//! -# 5MHz PWM (SYSCLK=150MHz) or 3.33MHz PWM (SYSCLK=100MHz) ePWM4A toggle
//!    high/low with MEP control on falling edge
//!
//!	\b Running \b the \b Application
//! -# Run this example at 150MHz SYSCLKOUT (or 100 MHz SYSCLKOUT for
//!    100 MHz devices)
//! -# Load the Example_2833xHRPWM_SFO.gel and observe variables in the
//!    watch window
//! -# Activate Real time mode
//! -# Run the code
//! -# Watch ePWM1A-4A waveforms on a Oscilloscope
//! -# In the watch window:
//! Set the variable UpdateFine = 1  to observe the ePWMxA output
//! with HRPWM capabilities (default).
//! Observe the duty cycle of the waveform changes in fine MEP steps
//! -# In the watch window:
//! Change the variable UpdateFine to 0, to observe the
//! ePWMxA output without HRPWM capabilities.
//! Observe the duty cycle of the waveform changes in coarse steps of 10nsec.
//!
//! \b External \b Connections \n
//! Monitor ePWM1-ePWM4 pins on an oscilloscope as described
//! below.
//! - EPWM1A is on GPIO0
//! - EPWM2A is on GPIO2
//! - EPWM3A is on GPIO4
//! - EPWM4A is on GPIO6
//!
//! \b Watch \b Variables \n
//! - UpdateFine
//! - MEP_ScaleFactor
//! - EPwm1Regs.CMPA.all
//! - EPwm2Regs.CMPA.all
//! - EPwm3Regs.CMPA.all
//! - EPwm4Regs.CMPA.all
//!
//! \note THE SFO.H FUNCTIONS INCLUDED WITH THIS EXAMPLE ONLY SUPPORTS 
//! EPWM1-EPWM4. FOR SUPPORT FOR MORE THAN 4 EPWMS, USE SFO_V5.H WITH THE
//! SFO_TI_BUILD_V5.LIB LIBRARY. SEE THE HRPWM REFERENCE GUIDE (SPRU924)
//! FOR USAGE INFORMATION AND DIFFERENCES BETWEEN VERSIONS.
//
//###########################################################################
// $TI Release: $
// $Release Date: $
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
//###########################################################################

//
// Included Files
//
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "DSP2833x_EPwm_defines.h" 	// useful defines for initialization
#include "SFO.h"					// SFO library headerfile

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
Uint16 j,duty, DutyFine, n, UpdateFine;
volatile int i;
Uint32 temp;

//
// Global array used by the SFO library
//
int16 MEP_ScaleFactor[5];

volatile struct 
EPWM_REGS *ePWM[] ={ &EPwm1Regs, &EPwm1Regs,	&EPwm2Regs,	&EPwm3Regs,	
                     &EPwm4Regs, &EPwm5Regs,	&EPwm6Regs};

//
// Main
//
void main(void)
{
    //
    // Step 1. Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    // This example function is found in the DSP2833x_SysCtrl.c file.
    //
    InitSysCtrl();

    //
    // Step 2. Initialize GPIO:
    //
    // This example function is found in the DSP2833x_Gpio.c file and
    // illustrates how to set the GPIO to it's default state.
    //
    // InitGpio();  // Skipped for this example
    // For this case, just init GPIO for ePWM1-ePWM4

    //
    // For this case just init GPIO pins for ePWM1, ePWM2, ePWM3, ePWM4
    // These functions are in the DSP2833x_EPwm.c file
    //
    InitEPwm1Gpio();
    InitEPwm2Gpio();
    InitEPwm3Gpio();
    InitEPwm4Gpio();

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

    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;
    EDIS;

    //
    //  MEP_ScaleFactor variables initialization for SFO library functions
    //
    MEP_ScaleFactor[0] = 0; 	// Common Variables for SFO functions
    MEP_ScaleFactor[1] = 0;	    // SFO for HRPWM1
    MEP_ScaleFactor[2] = 0;		// SFO for HRPWM2
    MEP_ScaleFactor[3] = 0;		// SFO for HRPWM3
    MEP_ScaleFactor[4] = 0;	    // SFO for HRPWM4

    //
    // 	MEP_ScaleFactor variables initialized using function SFO_MepDis
    //
    while ( MEP_ScaleFactor[1] == 0 )
    {
        SFO_MepDis(1);		// SFO for HRPWM1
    }
    while ( MEP_ScaleFactor[2] == 0 ) 
    {
        SFO_MepDis(2);		// SFO for HRPWM2
    }
    while ( MEP_ScaleFactor[3] == 0 ) 
    {
        SFO_MepDis(3);		// SFO for HRPWM3
    }
    while ( MEP_ScaleFactor[4] == 0 ) 
    {
        SFO_MepDis(4);		// SFO for HRPWM4
    }

    //
    // Initialize a common seed variable MEP_ScaleFactor[0] required for all
    // SFO functions
    //
    
    //
    //Common Variable for SFO library function
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
    //  30              5.0 MHz        3.33 MHz
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
    // ePWM1 target, 5 MHz PWM (SYSCLK=150MHz) or 3.33 MHz PWM (SYSCLK=100MHz)
    //
    HRPWM1_Config(30);
    
    //
    // ePWM2 target, 5 MHz PWM (SYSCLK=150MHz) or 3.33 MHz PWM (SYSCLK=100MHz)
    HRPWM2_Config(30);
    
    //
    // ePWM3 target, 5 MHz PWM (SYSCLK=150MHz) or 3.33 MHz PWM (SYSCLK=100MHz)
    //
    HRPWM3_Config(30);
    
    //
    // ePWM4 target, 5 MHz PWM (SYSCLK=150MHz) or 3.33 MHz PWM (SYSCLK=100MHz)
    //
    HRPWM4_Config(30);

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
            //
            // Variables
            //
            int16 CMPA_reg_val, CMPAHR_reg_val;
            int32 temp;

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
                // Write the values to the registers as one 32-bit or two 16-bits
                //
                EPwm1Regs.CMPA.half.CMPA = CMPA_reg_val;
                EPwm1Regs.CMPA.half.CMPAHR = CMPAHR_reg_val;
                */
                
                //
                // All the above operations may be condensed into
                // the following form: EPWM1 calculations
                //
                CMPA_reg_val = ((long)DutyFine * EPwm1Regs.TBPRD)>>15;
                temp = ((long)DutyFine * EPwm1Regs.TBPRD) ;
                temp = temp - ((long)CMPA_reg_val<<15);
                CMPAHR_reg_val = (temp*MEP_ScaleFactor[1])>>15;
                CMPAHR_reg_val = CMPAHR_reg_val << 8;
                CMPAHR_reg_val += 0x0180;

                //
                // Example for a 32 bit write to CMPA:CMPAHR
                //
                EPwm1Regs.CMPA.all = ((long)CMPA_reg_val)<<16 | CMPAHR_reg_val;

                //
                // EPWM2 calculations
                //
                CMPA_reg_val = ((long)DutyFine * EPwm2Regs.TBPRD)>>15;
                temp = ((long)DutyFine * EPwm2Regs.TBPRD) ;
                temp = temp - ((long)CMPA_reg_val<<15);
                CMPAHR_reg_val = (temp*MEP_ScaleFactor[2])>>15;
                CMPAHR_reg_val = CMPAHR_reg_val << 8;
                CMPAHR_reg_val += 0x0180;
                
                //
                // Example as a 16 bit write to CMPA and then a 16-bit write to
                // CMPAHR
                //
                EPwm2Regs.CMPA.half.CMPA = CMPA_reg_val;
                EPwm2Regs.CMPA.half.CMPAHR = CMPAHR_reg_val;

                //
                // EPWM3 calculations
                //
                CMPA_reg_val = ((long)DutyFine * EPwm3Regs.TBPRD)>>15;
                temp = ((long)DutyFine * EPwm3Regs.TBPRD) ;
                temp = temp - ((long)CMPA_reg_val<<15);
                CMPAHR_reg_val = (temp*MEP_ScaleFactor[3])>>15;
                CMPAHR_reg_val = CMPAHR_reg_val << 8;
                CMPAHR_reg_val += 0x0180;
                EPwm3Regs.CMPA.half.CMPA = CMPA_reg_val;
                EPwm3Regs.CMPA.half.CMPAHR = CMPAHR_reg_val;

                //
                // EPWM4 calculations
                //
                CMPA_reg_val = ((long)DutyFine * EPwm4Regs.TBPRD)>>15;
                temp = ((long)DutyFine * EPwm4Regs.TBPRD) ;
                temp = temp - ((long)CMPA_reg_val<<15);
                CMPAHR_reg_val = (temp*MEP_ScaleFactor[4])>>15;
                CMPAHR_reg_val = CMPAHR_reg_val << 8;
                CMPAHR_reg_val += 0x0180;
                EPwm4Regs.CMPA.half.CMPA = CMPA_reg_val;
                EPwm4Regs.CMPA.half.CMPAHR = CMPAHR_reg_val;
            }
            
            else
            {
                //
                // CMPA_reg_val is calculated as a Q0.
                // Since DutyFine is a Q15 number, and the period is Q0
                // the product is Q15. So to store as a Q0, we shift right
                // 15 bits.
                //
                EPwm1Regs.CMPA.half.CMPA = ((long)DutyFine * EPwm1Regs.TBPRD>>15);
                EPwm2Regs.CMPA.half.CMPA = ((long)DutyFine * EPwm2Regs.TBPRD)>>15;
                EPwm3Regs.CMPA.half.CMPA = ((long)DutyFine * EPwm3Regs.TBPRD)>>15;
                EPwm4Regs.CMPA.half.CMPA = ((long)DutyFine * EPwm4Regs.TBPRD)>>15;
            }

            for (i=0;i<300;i++)
            {
                //
                // Call the scale factor optimizer lib
                //
                SFO_MepEn(1);
                SFO_MepEn(2);
                SFO_MepEn(3);
                SFO_MepEn(4);
            }
        }
    }
}

//
// HRPWM1_Config - 
//
void 
HRPWM1_Config(period)
{
    //
    // ePWM1 register configuration with HRPWM
    // ePWM1A toggle low/high with MEP control on Rising edge
    //
    EPwm1Regs.TBCTL.bit.PRDLD = TB_IMMEDIATE;  // set Immediate load
    EPwm1Regs.TBPRD = period-1;		           // PWM frequency = 1 / period
    EPwm1Regs.CMPA.half.CMPA = period / 2;     // set duty 50% initially
    EPwm1Regs.CMPA.half.CMPAHR = (1 << 8);     // initialize HRPWM extension
    EPwm1Regs.CMPB = period / 2;	           // set duty 50% initially
    EPwm1Regs.TBPHS.all = 0;
    EPwm1Regs.TBCTR = 0;

    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;
    EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;	    // EPWM1 is the Master
    EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
    EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;
    EPwm1Regs.TBCTL.bit.FREE_SOFT = 11;

    EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
    EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;

    EPwm1Regs.AQCTLA.bit.ZRO = AQ_SET;         // PWM toggle high/low
    EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR;
    EPwm1Regs.AQCTLB.bit.ZRO = AQ_SET;
    EPwm1Regs.AQCTLB.bit.CBU = AQ_CLEAR;

    EALLOW;
    EPwm1Regs.HRCNFG.all = 0x0;
    EPwm1Regs.HRCNFG.bit.EDGMODE = HR_FEP;	    // MEP control on falling edge
    EPwm1Regs.HRCNFG.bit.CTLMODE = HR_CMP;
    EPwm1Regs.HRCNFG.bit.HRLOAD  = HR_CTR_ZERO;
    EDIS;
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
    EPwm2Regs.TBCTL.bit.PRDLD = TB_IMMEDIATE;	// set Immediate load
    EPwm2Regs.TBPRD = period-1;		            // PWM frequency = 1 / period
    EPwm2Regs.CMPA.half.CMPA = period / 2;      // set duty 50% initially
    EPwm1Regs.CMPA.half.CMPAHR = (1 << 8);      // initialize HRPWM extension
    EPwm2Regs.CMPB = period / 2;	            // set duty 50% initially
    EPwm2Regs.TBPHS.all = 0;
    EPwm2Regs.TBCTR = 0;

    EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;
    EPwm2Regs.TBCTL.bit.PHSEN = TB_DISABLE;		// ePWM2 is the Master
    EPwm2Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
    EPwm2Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
    EPwm2Regs.TBCTL.bit.CLKDIV = TB_DIV1;
    EPwm2Regs.TBCTL.bit.FREE_SOFT = 11;

    EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
    EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;

    EPwm2Regs.AQCTLA.bit.ZRO = AQ_SET;          // PWM toggle high/low
    EPwm2Regs.AQCTLA.bit.CAU = AQ_CLEAR;
    EPwm2Regs.AQCTLB.bit.ZRO = AQ_SET;
    EPwm2Regs.AQCTLB.bit.CBU = AQ_CLEAR;

    EALLOW;
    EPwm2Regs.HRCNFG.all = 0x0;
    EPwm2Regs.HRCNFG.bit.EDGMODE = HR_FEP;      // MEP control on falling edge
    EPwm2Regs.HRCNFG.bit.CTLMODE = HR_CMP;
    EPwm2Regs.HRCNFG.bit.HRLOAD  = HR_CTR_ZERO;

    EDIS;
}

//
// HRPWM3_Config -
//
void 
HRPWM3_Config(period)
{
    //
    // ePWM3 register configuration with HRPWM
    // ePWM3A toggle high/low with MEP control on falling edge
    //
    EPwm3Regs.TBCTL.bit.PRDLD = TB_IMMEDIATE;	 // set Immediate load
    EPwm3Regs.TBPRD = period-1;		             // PWM frequency = 1 / period
    EPwm3Regs.CMPA.half.CMPA = period / 2;       // set duty 50% initially
    EPwm3Regs.CMPA.half.CMPAHR = (1 << 8);       // initialize HRPWM extension
    EPwm3Regs.TBPHS.all = 0;
    EPwm3Regs.TBCTR = 0;

    EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;
    EPwm3Regs.TBCTL.bit.PHSEN = TB_DISABLE;		  // ePWM3 is the Master
    EPwm3Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
    EPwm3Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
    EPwm3Regs.TBCTL.bit.CLKDIV = TB_DIV1;
    EPwm3Regs.TBCTL.bit.FREE_SOFT = 11;

    EPwm3Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm3Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
    EPwm3Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm3Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;

    EPwm3Regs.AQCTLA.bit.ZRO = AQ_SET;           // PWM toggle high/low
    EPwm3Regs.AQCTLA.bit.CAU = AQ_CLEAR;
    EPwm3Regs.AQCTLB.bit.ZRO = AQ_SET;
    EPwm3Regs.AQCTLB.bit.CBU = AQ_CLEAR;

    EALLOW;
    EPwm3Regs.HRCNFG.all = 0x0;
    EPwm3Regs.HRCNFG.bit.EDGMODE = HR_FEP;       // MEP control on falling edge
    EPwm3Regs.HRCNFG.bit.CTLMODE = HR_CMP;
    EPwm3Regs.HRCNFG.bit.HRLOAD  = HR_CTR_ZERO;
    EDIS;
}

//
// HRPWM4_Config - 
//
void 
HRPWM4_Config(period)
{
    //
    // ePWM4 register configuration with HRPWM
    // ePWM4A toggle high/low with MEP control on falling edge
    //
    EPwm4Regs.TBCTL.bit.PRDLD = TB_IMMEDIATE;	 // set Immediate load
    EPwm4Regs.TBPRD = period-1;		             // PWM frequency = 1 / period
    EPwm4Regs.CMPA.half.CMPA = period / 2;       // set duty 50% initially
    EPwm4Regs.CMPA.half.CMPAHR = (1 << 8);       // initialize HRPWM extension
    EPwm4Regs.CMPB = period / 2;	             // set duty 50% initially
    EPwm4Regs.TBPHS.all = 0;
    EPwm4Regs.TBCTR = 0;

    EPwm4Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;
    EPwm4Regs.TBCTL.bit.PHSEN = TB_DISABLE;		 // ePWM4 is the Master
    EPwm4Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
    EPwm4Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
    EPwm4Regs.TBCTL.bit.CLKDIV = TB_DIV1;
    EPwm4Regs.TBCTL.bit.FREE_SOFT = 11;

    EPwm4Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm4Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
    EPwm4Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm4Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;

    EPwm4Regs.AQCTLA.bit.ZRO = AQ_SET;           // PWM toggle high/low
    EPwm4Regs.AQCTLA.bit.CAU = AQ_CLEAR;
    EPwm4Regs.AQCTLB.bit.ZRO = AQ_SET;
    EPwm4Regs.AQCTLB.bit.CBU = AQ_CLEAR;

    EALLOW;
    EPwm4Regs.HRCNFG.all = 0x0;
    EPwm4Regs.HRCNFG.bit.EDGMODE = HR_FEP;       // MEP control on falling edge
    EPwm4Regs.HRCNFG.bit.CTLMODE = HR_CMP;
    EPwm4Regs.HRCNFG.bit.HRLOAD  = HR_CTR_ZERO;
    EDIS;
}

//
// End of File
//

