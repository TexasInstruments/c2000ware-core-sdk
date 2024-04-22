//###########################################################################
//
// FILE:   Example_2806xHRPWM_PrdUp_SFO_V6.c
//
// TITLE:  High Resolution PWM SFO V6 High-Resolution Period (Up Count) Example
//
//!  \addtogroup f2806x_example_list
//!  <h1>High Resolution PWM SFO V6 High-Resolution Period 
//!  (Up Count)(hrpwm_prdup_sfo_v6)</h1>
//!
//!  This example modifies the MEP control registers to show edge displacement
//!  for high-resolution period with ePWM in Up count mode
//!  due to the HRPWM control extension of the respective ePWM module.
//!  This example calls the following TI's MEP Scale Factor Optimizer (SFO)
//!  software library V6 functions:
//!
//!  \b int \b SFO();
//!  - updates MEP_ScaleFactor dynamically when HRPWM is in use
//!  - updates HRMSTEP register (exists only in EPwm1Regs register space but 
//!  valid for all channels) with MEP_ScaleFactor value
//!  - \b Returns 
//!    - 2 if error: MEP_ScaleFactor is greater than maximum value of 255
//!      (Auto-conversion may not function properly under this condition)
//!    - 1 when complete for the specified channel
//!    - 0 if not complete for the specified channel
//!
//!  This example is intended to explain the HRPWM capabilities. The code can 
//!  be optimized for code efficiency. Refer to TI's Digital power application
//!  examples and TI Digital Power Supply software libraries for details.
//!  All ePWM1A-7A channels will have fine edge movement due to the HRPWM logic
//!
//!  \note
//!  - This program requires the F2806x header files, which include
//!  the following files required for this example:
//!  SFO_V6.h and SFO_TI_Build_V6.lib
//!  - For more information on using the SFO software library, see the
//!  High-Resolution Pulse Width Modulator (HRPWM) section of the Technical 
//!  Reference Manual
//!
//!  \b External \b Connections \n
//!  Monitor ePWM1A-ePWM4A (GPIO0-GPIO7) pins on an oscilloscope.
//!
//!  \b Running \b the \b Application
//!  -# \b **!!IMPORTANT!!** : in SFO_V6.h, set PWM_CH to the max number of
//!  HRPWM channels plus one. For example, for the F2803x, the
//!  maximum number of HRPWM channels is 7. 7+1=8, so set
//!  \#define PWM_CH 8 in SFO_V6.h. (Default is 8)
//!  -# Run this example at maximum SYSCLKOUT (80 MHz)
//!  -# Add "UpdateFine" variable to the watch window
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
//!       Observe the period/frequency of the waveform changes in coarse
//!       SYSCLKOUT cycle steps.
//
//###########################################################################
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
//###########################################################################

//
// Included Files
//
#include "DSP28x_Project.h"         // DSP280xx Headerfile
#include "SFO_V6.h"

//
//                         *!!IMPORTANT!!*
// UPDATE NUMBER OF HRPWM CHANNELS + 1  USED IN SFO_V6.H
//
// Configured for 4 HRPWM's, but FF2806x has a maximum of 7 HRPWM channels 
// (8=7+1)
//
// i.e.: #define PWM_CH 5

//
// Function Prototypes
//
void HRPWM_Config(Uint16);
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


//
// Main
//
void main(void)
{
    //
    // Local variables
    //
    int i;

    //
    // Step 1. Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    // This example function is found in the F2806x_SysCtrl.c file.
    //
    InitSysCtrl();

    //
    // Step 2. Initalize GPIO:
    // This example function is found in the F2806x_Gpio.c file and
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
    // This function is found in the F2806x_PieCtrl.c file.
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
    // The shell ISR routines are found in F2806x_DefaultIsr.c.
    // This function is found in F2806x_PieVect.c.
    //
    InitPieVectTable();

    //
    // Step 4. Initialize all the Device Peripherals:
    // This function is found in F2806x_InitPeripherals.c
    //
    // InitPeripherals();  // Not required for this example

    //
    // For this example, only initialize the ePWM
    // Step 5. User specific code, enable interrupts:
    //
    UpdateFine = 1;
    PeriodFine = 0;
    status = SFO_INCOMPLETE;

    //
    // Calling SFO() updates the HRMSTEP register with calibrated 
    // MEP_ScaleFactor. HRMSTEP must be populated with a scale factor value 
    // prior to enabling high resolution period control.
    //
    
    //
    // Call until complete
    //
    while  (status== SFO_INCOMPLETE)
    {  
        status = SFO();
        if (status == SFO_ERROR)
        {
            //
            // SFO function returns 2 if an error occurs & # of MEP
            // steps/coarse step
            //
            error();
        }
    }

    //
    // Some useful Period vs Frequency values
    //  SYSCLKOUT =     80 MHz
    //  ---------------------------
    //	Period	        Frequency
    //	1000	        80 kHz
    //	800		        100 kHz
    //	600		        133 kHz
    //	500		        160 kHz
    //	250		        320 kHz
    //	200		        400 kHz
    //	100		        800 kHz
    //	50		        1.6 Mhz
    //	25		        3.2 Mhz
    //	20		        4.0 Mhz
    //	12		        6.7 MHz
    //	10		        8.0 MHz
    //	9		        8.9 MHz
    //	8		        10.0 MHz
    //	7		        11.4 MHz
    //	6		        13.3 MHz
    //	5		        16.0 MHz
    //

    //
    // ePWM and HRPWM register initialization
    //
    HRPWM_Config(30);        // ePWMx target
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
                // Hardware conversion:
                // MEP delay movement = ((TBPRDHR(15:0) >> 8) *  HRMSTEP(7:0) 
                //                       + 0x80) >> 8
                for(i=1;i<PWM_CH;i++)
                {
                    (*ePWM[i]).TBPRDHR = PeriodFine; //In Q16 format
                }

                }
            else
            {
                //
                // No high-resolution movement on TBPRDHR.
                //
                for(i=1;i<PWM_CH;i++)
                {
                    (*ePWM[i]).TBPRDHR = 0;
                }
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
// channels
//
// PARAMETERS:  period - desired PWM period in TBCLK counts
// RETURN:      N/A
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
        (*ePWM[j]).TBCTL.bit.PRDLD = TB_SHADOW;   // set Shadow load
        (*ePWM[j]).TBPRD = period-1;              // PWM frequency = 1 / period
        (*ePWM[j]).CMPA.half.CMPA = period / 2;   // set duty 50% initially
        (*ePWM[j]).CMPA.half.CMPAHR = (1 << 8);   // initialize HRPWM extension
        
        //
        // set duty 50% initially (edge 3 cycles after CTR=0)
        //
        (*ePWM[j]).CMPB = period / 2;
        
        (*ePWM[j]).TBPHS.all = 0;
        (*ePWM[j]).TBCTR = 0;

        (*ePWM[j]).TBCTL.bit.CTRMODE = TB_COUNT_UP;   // Select up-count mode
        (*ePWM[j]).TBCTL.bit.PHSEN = TB_DISABLE;
        (*ePWM[j]).TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
        (*ePWM[j]).TBCTL.bit.HSPCLKDIV = TB_DIV1;
        (*ePWM[j]).TBCTL.bit.CLKDIV = TB_DIV1;        // TBCLK = SYSCLKOUT
        (*ePWM[j]).TBCTL.bit.FREE_SOFT = 11;

        (*ePWM[j]).CMPCTL.bit.LOADAMODE = CC_CTR_PRD; // Load CMPA on CTR = PRD
        (*ePWM[j]).CMPCTL.bit.LOADBMODE = CC_CTR_PRD;
        (*ePWM[j]).CMPCTL.bit.SHDWAMODE = CC_SHADOW;
        (*ePWM[j]).CMPCTL.bit.SHDWBMODE = CC_SHADOW;


        (*ePWM[j]).AQCTLA.bit.PRD = AQ_SET;          // PWM toggle high/low
        (*ePWM[j]).AQCTLA.bit.CAU = AQ_CLEAR;
        (*ePWM[j]).AQCTLB.bit.PRD = AQ_SET;
        (*ePWM[j]).AQCTLB.bit.CAU = AQ_CLEAR;

        EALLOW;
        (*ePWM[j]).HRCNFG.all = 0x0;
        (*ePWM[j]).HRCNFG.bit.EDGMODE = HR_BEP;    // MEP control on both edges
        (*ePWM[j]).HRCNFG.bit.CTLMODE = HR_CMP;
        (*ePWM[j]).HRCNFG.bit.HRLOAD  = HR_CTR_ZERO_PRD;

        (*ePWM[j]).HRCNFG.bit.AUTOCONV = 1;          // Enable autoconversion

        //
        // Turn on high-resolution period control.
        //
        (*ePWM[j]).HRPCTL.bit.HRPE = 1;
        EDIS;

        EALLOW;
        SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;  // Enable TBCLK within the EPWM
        EDIS;
        (*ePWM[j]).TBCTL.bit.SWFSYNC = 1;    // Sync for high resolution period
    }
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

