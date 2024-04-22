//###########################################################################
//
// FILE:   adc_ppb_delay_cpu01.c
//
// TITLE:  Post-Processing delay capture for F2837xD.
//
//! \addtogroup cpu01_example_list
//! <h1> ADC PPB Delay Capture (adc_ppb_delay)</h1>
//!
//! This example demonstrates delay capture using the post-processing block.
//!
//! Two asynchronous ADC triggers are setup:\n
//!  - ePWM1, with period 2048, triggering SOC0 to convert on pin A0\n
//!  - ePWM1, with period 9999, triggering SOC1 to convert on pin A1\n
//!
//! Each conversion generates an ISR at the end of the conversion.  In the
//! ISR for SOC0, a conversion counter is incremented and the PPB is checked
//! to determine if the sample was delayed.\n
//!
//! After the program runs, the memory will contain:\n
//! - \b conversion \b: the sequence of conversions using SOC0 that were delayed
//! - \b delay \b: the corresponding delay of each of the delayed conversions
//!
//
//###########################################################################
// $Copyright:
// Copyright (C) 2013-2024 Texas Instruments Incorporated - http://www.ti.com/
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
#include "F28x_Project.h"

//
// Function Prototypes
//
void ConfigureADC(void);
void ConfigureEPWM(void);
void SetupADCEpwm(Uint16 channel1, Uint16 channel2);
interrupt void adca1_isr(void);
interrupt void adca2_isr(void);

//
// Defines
//
#define DELAY_BUFFER_SIZE 30

//
// Globals
//
Uint32 conversion_count;
Uint32 conversion[DELAY_BUFFER_SIZE];
Uint16 delay[DELAY_BUFFER_SIZE];
volatile Uint16 delay_index;

void main(void)
{
    Uint16  adcChannelId0;
    Uint16  adcChannelId1;
//
// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the F2837xD_SysCtrl.c file.
//
    InitSysCtrl();

//
// Step 2. Initialize GPIO:
// This example function is found in the F2837xD_Gpio.c file and
// illustrates how to set the GPIO to it's default state.
//
    InitGpio(); // Skipped for this example

//
// Step 3. Clear all interrupts and initialize PIE vector table:
// Disable CPU interrupts
//
    DINT;

//
// Initialize the PIE control registers to their default state.
// The default state is all PIE interrupts disabled and flags
// are cleared.
// This function is found in the F2837xD_PieCtrl.c file.
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
// The shell ISR routines are found in F2837xD_DefaultIsr.c.
// This function is found in F2837xD_PieVect.c.
//
    InitPieVectTable();

//
// Map ISR functions
//
    EALLOW;
    PieVectTable.ADCA1_INT = &adca1_isr; //function for ADCA interrupt 1
    PieVectTable.ADCA2_INT = &adca2_isr; //function for ADCA interrupt 2
    EDIS;

//
// Configure the ADC and power it up
//
    ConfigureADC();

//
// Configure ePWM1 and ePWM2 with asynchronous periods
//
    ConfigureEPWM();

//
// Setup the ADC for ePWM triggered conversions on ADC channels 0 and 1
//
    adcChannelId0 = ADC_CHANNEL_0;
    adcChannelId1 = ADC_CHANNEL_1;

    SetupADCEpwm(adcChannelId0, adcChannelId1);

//
// Setup the post-processing block to be associated with SOC0
//
    AdcaRegs.ADCPPB1CONFIG.bit.CONFIG = 0;

//
// Enable global Interrupts and higher priority real-time debug events:
//
    IER |= M_INT1; //Enable group 1 interrupts
    IER |= M_INT10; //Enable group 1 interrupts
    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global realtime interrupt DBGM

//
// enable PIE interrupt
//
    PieCtrlRegs.PIEIER1.bit.INTx1  = 1;
    PieCtrlRegs.PIEIER10.bit.INTx2 = 1;

//
// initialize program variables
//
    conversion_count = 0;
    for(delay_index = 0; delay_index < DELAY_BUFFER_SIZE; delay_index++)
    {
        delay[delay_index] = 0;
        conversion[delay_index] = 0;
    }

//
// Start ePWMs
//
    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EPwm1Regs.ETSEL.bit.SOCAEN = 1;  //enable SOCA
    EPwm1Regs.TBCTL.bit.CTRMODE = 0; //unfreeze, and enter up count mode
    EPwm2Regs.ETSEL.bit.SOCAEN = 1;  //enable SOCA
    EPwm2Regs.TBCTL.bit.CTRMODE = 0; //unfreeze, and enter up count mode

    do
    {
        delay_index = 0;

        //
        //wait for list of delayed conversions to fill via interrupts
        //
        while(DELAY_BUFFER_SIZE > delay_index){}

        //
        //software breakpoint
        //
        asm("   ESTOP0");

        //
        //conversion[] will show which conversions were delayed
        //delay[] will show how long each conversion was delayed
        //conversion_count will show total number of conversions
        //conversion_count - DELAY_BUFFER_SIZE is the number of samples
        //    that started immediately without any delay
        //
    }while(1);
}

//
// ConfigureADC - Write ADC configurations and power up the ADC for both
//                ADC A and ADC B
//
void ConfigureADC(void)
{
    EALLOW;

    //
    //write configurations
    //
    AdcaRegs.ADCCTL2.bit.PRESCALE = 6; //set ADCCLK divider to /4
    AdcSetMode(ADC_ADCA, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);

    //
    //Set pulse positions to late
    //
    AdcaRegs.ADCCTL1.bit.INTPULSEPOS = 1;

    //
    //power up the ADC
    //
    AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1;

    //
    //delay for 1ms to allow ADC time to power up
    //
    DELAY_US(1000);

    EDIS;
}

//
// ConfigureEPWM - setup PWM1 and PWM2 with asynchronous periods
//
void ConfigureEPWM(void)
{
    EALLOW;
    //
    // Assumes ePWM clock is already enabled
    //
    EPwm1Regs.ETSEL.bit.SOCAEN    = 0;    // Disable SOC on A group
    EPwm1Regs.ETSEL.bit.SOCASEL    = 4;   // Select SOC on up-count
    EPwm1Regs.ETPS.bit.SOCAPRD = 1;       // Generate pulse on 1st event
    EPwm1Regs.CMPA.bit.CMPA = 0x0400;     // Set compare A value to 1024 counts
    EPwm1Regs.TBPRD = 0x0800;             // Set period to 2048 counts
    EPwm1Regs.TBCTL.bit.CTRMODE = 3;      // freeze counter

    //
    // Assumes ePWM clock is already enabled
    //
    EPwm2Regs.ETSEL.bit.SOCAEN    = 0;     // Disable SOC on A group
    EPwm2Regs.ETSEL.bit.SOCASEL    = 4;    // Select SOC on up-count
    EPwm2Regs.ETPS.bit.SOCAPRD = 1;        // Generate pulse on 1st event
    EPwm2Regs.CMPA.bit.CMPA = 0x0400;      // Set compare A value to 1024 counts
    EPwm2Regs.TBPRD = 9999;                // Set period to 9999 counts
    EPwm2Regs.TBCTL.bit.CTRMODE = 3;       // freeze counter
    EDIS;
}

//
// SetupADCEpwm - Setup ADC SOC for EPWM
//
void SetupADCEpwm(Uint16 channel1, Uint16 channel2)
{
    Uint16 acqps;

    //
    // Determine minimum acquisition window (in SYSCLKS) based on resolution
    //
    if(ADC_RESOLUTION_12BIT == AdcaRegs.ADCCTL2.bit.RESOLUTION)
    {
        acqps = 14; //75ns
    }
    else //resolution is 16-bit
    {
        acqps = 63; //320ns
    }

    //
    //Select the channels to convert and setup the end of conversion flag
    //ADCA
    //
    EALLOW;
    AdcaRegs.ADCSOC0CTL.bit.CHSEL     = channel1;               // ADC Channel to be converted on SOC0 trigger
    AdcaRegs.ADCSOC1CTL.bit.CHSEL     = channel2;               // ADC Channel to be converted on SOC1 trigger
    AdcaRegs.ADCSOC0CTL.bit.ACQPS     = acqps;                  // sample window is 100 SYSCLK cycles
    AdcaRegs.ADCSOC1CTL.bit.ACQPS     = acqps;                  // sample window is 100 SYSCLK cycles
    AdcaRegs.ADCSOC0CTL.bit.TRIGSEL   = 5;                      // trigger on ePWM1 SOCA/C
    AdcaRegs.ADCSOC1CTL.bit.TRIGSEL   = 7;                      // trigger on ePWM2 SOCA/C
    AdcaRegs.ADCINTSEL1N2.bit.INT1SEL = 0;                      // end of SOC0 will set INT1 flag
    AdcaRegs.ADCINTSEL1N2.bit.INT2SEL = 1;                      // end of SOC1 will set INT1 flag
    AdcaRegs.ADCINTSEL1N2.bit.INT1E   = 1;                      // enable INT1 flag
    AdcaRegs.ADCINTSEL1N2.bit.INT2E   = 1;                      // enable INT2 flag
    EDIS;
}

//
// adca1_isr - ADCA1 Interrupt Service Routine
//
interrupt void adca1_isr(void)
{
    //
    //DLYSTAMP will read 2 if the sample was not delayed
    //
    if(2 < AdcaRegs.ADCPPB1STAMP.bit.DLYSTAMP)
    {
        //
        //if DLYSTAMP > 2, then the sample was delayed by (DLYSTAMP - 2)
        //cycles (SYSCLK)
        //
        conversion[delay_index] = conversion_count;
        delay[delay_index] = AdcaRegs.ADCPPB1STAMP.bit.DLYSTAMP - 2;
        delay_index++;

        //
        //corrective action(s) for delayed sample can occur here
        //...
        //
    }

    //
    //read ADC sample here
    //...
    //

    conversion_count++;

    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //clear INT1 flag

    //
    // Check if overflow has occurred
    //
    if(1 == AdcaRegs.ADCINTOVF.bit.ADCINT1)
    {
        AdcaRegs.ADCINTOVFCLR.bit.ADCINT1 = 1; //clear INT1 overflow flag
        AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //clear INT1 flag
    }

    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

//
// adca2_isr - ADCA2 Interrupt Service Routine
//
interrupt void adca2_isr(void)
{
    //
    //read ADC sample
    //...
    //

    AdcaRegs.ADCINTFLGCLR.bit.ADCINT2 = 1; //clear INT2 flag

    //
    // Check if overflow has occurred
    //
    if(1 == AdcaRegs.ADCINTOVF.bit.ADCINT2)
    {
        AdcaRegs.ADCINTOVFCLR.bit.ADCINT2 = 1; //clear INT2 overflow flag
        AdcaRegs.ADCINTFLGCLR.bit.ADCINT2 = 1; //clear INT2 flag
    }

    PieCtrlRegs.PIEACK.all = PIEACK_GROUP10;
}

//
// End of file
//
