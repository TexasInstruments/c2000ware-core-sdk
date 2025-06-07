//###########################################################################
//
//  FILE:  Example_2803xHRPWM_slider.c
//
//  TITLE: High Resolution PWM with slider example
//
//!  \addtogroup f2803x_example_list
//!  <h1>High Resolution PWM with slider(hrpwm_slider)</h1>
//!
//!  This example modifies the MEP control registers to show edge displacement
//!  due to HRPWM control blocks of the respective EPwm module, EPwm1A, 2A, 3A,
//!  and 4A channels (GPIO0, GPIO2, GPIO4, and GPIO6) will have fine edge 
//!  movement due to HRPWM logic.
//!
//! \b External \b Connections \n
//!  Monitor EPwm1-EPwm4 pins on an oscilloscope as described
//!  below.
//!  - ePWM1A is on GPIO0
//!  - ePWM1B is on GPIO1
//!  - ePWM2A is on GPIO2
//!  - ePWM2B is on GPIO3
//!  - ePWM3A is on GPIO4
//!  - ePWM3B is on GPIO5
//!
//!  \b Running \b the \b Application
//!  -# Launch the target configuration and connect to the target first
//!  -# Load the program and set it up to run in real time mode. Do not 
//!     run yet!
//!  -# Load the Example_2803xHRPWM_slider.gel file (provided in the folder)
//!  -# Select the DSP2803x HRPWM FineDutySlider from the Scripts menu 
//!     (debug perspective).
//!     A FineDuty slider graphics will show up in CCS. (See Below)
//!  -# Add "DutyFine" variable to the watch window
//!     either manually or using the supplied javascript. This variable is
//!     controlled by the slider
//!  -# Run the example
//!  -# Use the Slider to and observe the EPwm edge displacement
//!     for each slider step change. This explains the MEP control on the 
//!     EPwmxA channels,
//!    -# \f$ PWM Freq = \frac{SYSCLK}{period=10} \f$ \n
//!       ePWM1A toggle low/high with MEP control on rising edge \n
//!       \f$ PWM Freq = \frac{SYSCLK}{period=10} \f$ \n
//!       ePWM1B toggle low/high with NO HRPWM control
//!    -# \f$ PWM Freq = \frac{SYSCLK}{period=20} \f$ \n
//!       ePWM2A toggle low/high with MEP control on rising edge \n
//!       \f$ PWM Freq = \frac{SYSCLK}{period=20} \f$ \n
//!       ePWM2B toggle low/high with NO HRPWM control
//!    -# \f$ PWM Freq = \frac{SYSCLK}{period=10} \f$ \n
//!       ePWM3A toggle as high/low with MEP control on falling edge \n
//!       \f$ PWM Freq = \frac{SYSCLK}{period=10} \f$ \n
//!       ePWM3B toggle low/high with NO HRPWM control
//!    -# \f$ PWM Freq = \frac{SYSCLK}{period=20} \f$ \n
//!       ePWM4A toggle as high/low with MEP control on falling edge \n
//!       \f$ PWM Freq = \frac{SYSCLK}{period=20} \f$ \n
//!       ePWM4B toggle low/high with NO HRPWM control
//!
//!  \b Watch \b Variables \n
//!  - DutyFine
//!
//!  \latexonly \begin{figure}[H] \begin{center} \includegraphics[width=1.0in]
//!  {piccolo_fine_duty_slider.jpg} \caption{Fine Duty Slider} \end{center} 
//!  \end{figure} \endlatexonly
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
#include "DSP2803x_Device.h"            // DSP2803x Headerfile
#include "DSP2803x_Examples.h"          // DSP2803x Examples Headerfile
#include "DSP2803x_EPwm_defines.h" 	    // useful defines for initialization

//
// Function prototypes
//
void HRPWM1_Config(Uint16);
void HRPWM2_Config(Uint16);
void HRPWM3_Config(Uint16);
void HRPWM4_Config(Uint16);

//
// Globals Useful for debug
//
Uint16 i,j,	duty, DutyFine, n,update;
Uint32 temp;

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
    // For this case, just init GPIO for EPwm1-EPwm4

    //
    // For this case just init GPIO pins for EPwm1, EPwm2, EPwm3, EPwm4
    // These functions are in the DSP2803x_EPwm.c file
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
    // For this example, only initialize the EPwm
    // Step 5. User specific code, enable interrupts:
    //
    update =1;
    DutyFine =0;

    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;
    EDIS;

    //
    // Some useful Period vs Frequency values
    //  SYSCLKOUT =     60 MHz
    //  -------------------------
    //	Period          Frequency
    //	1000            60 kHz
    //	800             75 kHz
    //	600             100 kHz
    //	500             120 kHz
    //	250             240 kHz
    //	200             300 kHz
    //	100             600 kHz
    //	50              1.2 Mhz
    //	25              2.4 Mhz
    //	20              3.0 Mhz
    //	12              5.0 MHz
    //	10              6.0 MHz
    //	9               6.7 MHz
    //	8               7.5 MHz
    //	7               8.6 MHz
    //	6               10.0 MHz
    //	5               12.0 MHz
    //

    //
    // EPwm and HRPWM register initialization
    //
    HRPWM1_Config(10);	     // EPwm1 target, Period = 10
    HRPWM2_Config(20);	     // EPwm2 target, Period = 20
    HRPWM3_Config(10);	     // EPwm3 target, Period = 10
    HRPWM4_Config(20);	     // EPwm4 target, Period = 20

    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;

    while (update ==1)
    {
        //
        //for(DutyFine =1; DutyFine <255 ;DutyFine ++)
        //
        {
            //
            // Example, write to the HRPWM extension of CMPA
            // Left shift by 8 to write into MSB bits
            //
            EPwm1Regs.CMPA.half.CMPAHR = DutyFine << 8; 
            EPwm2Regs.CMPA.half.CMPAHR = DutyFine << 8;

            //
            // Example, 32-bit write to CMPA:CMPAHR
            //
            EPwm3Regs.CMPA.all = ((Uint32)EPwm3Regs.CMPA.half.CMPA << 16) + 
                                    (DutyFine << 8);
            EPwm4Regs.CMPA.all = ((Uint32)EPwm4Regs.CMPA.half.CMPA << 16) + 
                                    (DutyFine << 8);
        }
    }
}

//
// HRPWM1_Config - ePWM1 register configuration with HRPWM
//
void 
HRPWM1_Config(Uint16 period)
{
    //
    // ePWM1A toggle low/high with MEP control on Rising edge
    //
    EPwm1Regs.TBCTL.bit.PRDLD = TB_IMMEDIATE;// set Immediate load
    EPwm1Regs.TBPRD = period-1;              // PWM frequency = 1 / period
    EPwm1Regs.CMPA.half.CMPA = period / 2;   // set duty 50% initially
    EPwm1Regs.CMPA.half.CMPAHR = (1 << 8);   // initialize HRPWM extension
    EPwm1Regs.CMPB = period / 2;             // set duty 50% initially
    EPwm1Regs.TBPHS.all = 0;
    EPwm1Regs.TBCTR = 0;

    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;
    EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;         // ePWM1 is the Master
    EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
    EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
    EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;

    EPwm1Regs.AQCTLA.bit.ZRO = AQ_CLEAR;          // PWM toggle low/high
    EPwm1Regs.AQCTLA.bit.CAU = AQ_SET;
    EPwm1Regs.AQCTLB.bit.ZRO = AQ_CLEAR;
    EPwm1Regs.AQCTLB.bit.CBU = AQ_SET;

    EALLOW;
    EPwm1Regs.HRCNFG.all = 0x0;
    EPwm1Regs.HRCNFG.bit.EDGMODE = HR_REP;        // MEP control on Rising edge
    EPwm1Regs.HRCNFG.bit.CTLMODE = HR_CMP;
    EPwm1Regs.HRCNFG.bit.HRLOAD  = HR_CTR_ZERO;
    EDIS;
}

//
// HRPWM2_Config - ePWM2 register configuration with HRPWM
//
void 
HRPWM2_Config(Uint16 period)
{
    //
    // ePWM2A toggle low/high with MEP control on Rising edge
    //
    EPwm2Regs.TBCTL.bit.PRDLD = TB_IMMEDIATE;     // set Immediate load
    EPwm2Regs.TBPRD = period - 1;                 // PWM frequency = 1 / period
    EPwm2Regs.CMPA.half.CMPA = period / 2;        // set duty 50% initially
    EPwm2Regs.CMPA.half.CMPAHR = (1 << 8);        // initialize HRPWM extension
    EPwm2Regs.CMPB = period / 2;                  // set duty 50% initially
    EPwm2Regs.TBPHS.all = 0;
    EPwm2Regs.TBCTR = 0;

    EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;
    EPwm2Regs.TBCTL.bit.PHSEN = TB_DISABLE;       // ePWM2 is the Master
    EPwm2Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
    EPwm2Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
    EPwm2Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
    EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;

    EPwm2Regs.AQCTLA.bit.ZRO = AQ_CLEAR;          // PWM toggle low/high
    EPwm2Regs.AQCTLA.bit.CAU = AQ_SET;
    EPwm2Regs.AQCTLB.bit.ZRO = AQ_CLEAR;
    EPwm2Regs.AQCTLB.bit.CBU = AQ_SET;

    EALLOW;
    EPwm2Regs.HRCNFG.all = 0x0;
    EPwm2Regs.HRCNFG.bit.EDGMODE = HR_REP;        // MEP control on Rising edge
    EPwm2Regs.HRCNFG.bit.CTLMODE = HR_CMP;
    EPwm2Regs.HRCNFG.bit.HRLOAD  = HR_CTR_ZERO;
    EDIS;
}

//
// HRPWM3_Config - ePWM3 register configuration with HRPWM
//
void 
HRPWM3_Config(Uint16 period)
{
    //
    // ePWM3A toggle high/low with MEP control on falling edge
    //
    EPwm3Regs.TBCTL.bit.PRDLD = TB_IMMEDIATE;     // set Immediate load
    EPwm3Regs.TBPRD = period - 1;                 // PWM frequency = 1 / period
    EPwm3Regs.CMPA.half.CMPA = period / 2;        // set duty 50% initially
    EPwm3Regs.CMPA.half.CMPAHR = (1 << 8);        // initialize HRPWM extension
    EPwm3Regs.CMPB = period / 2;                  // set duty 50% initially
    EPwm3Regs.TBPHS.all = 0;
    EPwm3Regs.TBCTR = 0;

    EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;
    EPwm3Regs.TBCTL.bit.PHSEN = TB_DISABLE;       // ePWM3 is the Master
    EPwm3Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
    EPwm3Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
    EPwm3Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    EPwm3Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm3Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
    EPwm3Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm3Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;

    EPwm3Regs.AQCTLA.bit.ZRO = AQ_SET;            // PWM toggle high/low
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
// HRPWM4_Config - ePWM4 register configuration with HRPWM
//
void 
HRPWM4_Config(Uint16 period)
{
    // 
    // ePWM4A toggle high/low with MEP control on falling edge
    //
    EPwm4Regs.TBCTL.bit.PRDLD = TB_IMMEDIATE;   // set Immediate load
    EPwm4Regs.TBPRD = period - 1;               // PWM frequency = 1 / period
    EPwm4Regs.CMPA.half.CMPA = period / 2;      // set duty 50% initially
    EPwm4Regs.CMPA.half.CMPAHR = (1 << 8);      // initialize HRPWM extension
    EPwm4Regs.CMPB = period / 2;                // set duty 50% initially
    EPwm4Regs.TBPHS.all = 0;
    EPwm4Regs.TBCTR = 0;

    EPwm4Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;
    EPwm4Regs.TBCTL.bit.PHSEN = TB_DISABLE;     // ePWM4 is the Master
    EPwm4Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
    EPwm4Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
    EPwm4Regs.TBCTL.bit.CLKDIV = TB_DIV1;

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
    EPwm4Regs.HRCNFG.bit.EDGMODE = HR_FEP;       //MEP control on falling edge
    EPwm4Regs.HRCNFG.bit.CTLMODE = HR_CMP;
    EPwm4Regs.HRCNFG.bit.HRLOAD  = HR_CTR_ZERO;
    EDIS;
}

//
// End of Files
//

