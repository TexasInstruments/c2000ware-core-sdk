//###########################################################################
//
// FILE:   adc_soc_continuous_cpu01.c
//
// TITLE:  ADC continuous self-triggering for F2837xD.
//
//! \addtogroup cpu01_example_list
//! <h1> ADC Continuous Triggering (adc_soc_continuous)</h1>
//!
//! This example sets up the ADC to convert continuously, achieving maximum
//! sampling rate.\n
//!
//! After the program runs, the memory will contain:
//!
//! - \b AdcaResults \b: A sequence of analog-to-digital conversion samples
//! from pin A0. The time between samples is the minimum possible based on the
//! ADC speed.
//
//###########################################################################
//
// $Release Date:  $
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
void SetupADCContinuous(Uint16 channel);

//
// Defines
//
#define RESULTS_BUFFER_SIZE 256 //buffer for storing conversion results
                                //(size must be multiple of 16)

//
// Globals
//
Uint16 AdcaResults[RESULTS_BUFFER_SIZE];
Uint16 resultsIndex;

void main(void)
{
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
// Configure the ADC and power it up
//
    ConfigureADC();

//
// Setup the ADC for continuous conversions on channel 0
//
    SetupADCContinuous(0);

//
// Enable global Interrupts and higher priority real-time debug events:
//
    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global realtime interrupt DBGM

//
// Initialize results buffer
//
    for(resultsIndex = 0; resultsIndex < RESULTS_BUFFER_SIZE; resultsIndex++)
    {
        AdcaResults[resultsIndex] = 0;
    }
    resultsIndex = 0;

//
// take conversions indefinitely in loop
//
    do
    {
        //
        //enable ADCINT flags
        //
		EALLOW;
        AdcaRegs.ADCINTSEL1N2.bit.INT1E = 1;
        AdcaRegs.ADCINTSEL1N2.bit.INT2E = 1;
        AdcaRegs.ADCINTSEL3N4.bit.INT3E = 1;
        AdcaRegs.ADCINTSEL3N4.bit.INT4E = 1;
        AdcaRegs.ADCINTFLGCLR.all = 0x000F;
		EDIS;

        //
        //initialize results index
        //
        resultsIndex = 0;

        //
        //software force start SOC0 to SOC7
        //
        AdcaRegs.ADCSOCFRC1.all = 0x00FF;

        //
        //keep taking samples until the results buffer is full
        //
        while(resultsIndex < RESULTS_BUFFER_SIZE)
        {
            //
            //wait for first set of 8 conversions to complete
            //
            while(0 == AdcaRegs.ADCINTFLG.bit.ADCINT3);

            //
            //clear both INT flags generated by first 8 conversions
            //
            AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;
            AdcaRegs.ADCINTFLGCLR.bit.ADCINT3 = 1;

            //
            //save results for first 8 conversions
            //
            //note that during this time, the second 8 conversions have
            //already been triggered by EOC6->ADCIN1 and will be actively
            //converting while first 8 results are being saved
            //
            AdcaResults[resultsIndex++] = AdcaResultRegs.ADCRESULT0;
            AdcaResults[resultsIndex++] = AdcaResultRegs.ADCRESULT1;
            AdcaResults[resultsIndex++] = AdcaResultRegs.ADCRESULT2;
            AdcaResults[resultsIndex++] = AdcaResultRegs.ADCRESULT3;
            AdcaResults[resultsIndex++] = AdcaResultRegs.ADCRESULT4;
            AdcaResults[resultsIndex++] = AdcaResultRegs.ADCRESULT5;
            AdcaResults[resultsIndex++] = AdcaResultRegs.ADCRESULT6;
            AdcaResults[resultsIndex++] = AdcaResultRegs.ADCRESULT7;

            //
            //wait for the second set of 8 conversions to complete
            //
            while(0 == AdcaRegs.ADCINTFLG.bit.ADCINT4);

            //
            //clear both INT flags generated by second 8 conversions
            //
            AdcaRegs.ADCINTFLGCLR.bit.ADCINT2 = 1;
            AdcaRegs.ADCINTFLGCLR.bit.ADCINT4 = 1;

            //
            //save results for second 8 conversions
            //
            //note that during this time, the first 8 conversions have
            //already been triggered by EOC14->ADCIN2 and will be actively
            //converting while second 8 results are being saved
            //
            AdcaResults[resultsIndex++] = AdcaResultRegs.ADCRESULT8;
            AdcaResults[resultsIndex++] = AdcaResultRegs.ADCRESULT9;
            AdcaResults[resultsIndex++] = AdcaResultRegs.ADCRESULT10;
            AdcaResults[resultsIndex++] = AdcaResultRegs.ADCRESULT11;
            AdcaResults[resultsIndex++] = AdcaResultRegs.ADCRESULT12;
            AdcaResults[resultsIndex++] = AdcaResultRegs.ADCRESULT13;
            AdcaResults[resultsIndex++] = AdcaResultRegs.ADCRESULT14;
            AdcaResults[resultsIndex++] = AdcaResultRegs.ADCRESULT15;
        }

        //
        //disable all ADCINT flags to stop sampling
        //
		EALLOW;
        AdcaRegs.ADCINTSEL1N2.bit.INT1E = 0;
        AdcaRegs.ADCINTSEL1N2.bit.INT2E = 0;
        AdcaRegs.ADCINTSEL3N4.bit.INT3E = 0;
        AdcaRegs.ADCINTSEL3N4.bit.INT4E = 0;
		EDIS;

        //
        //at this point, AdcaResults[] contains a sequence of conversions
        //from the selected channel
        //

        //
        //software breakpoint, hit run again to get updated conversions
        //
        asm("   ESTOP0");
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
// SetupADCContinuous - setup the ADC to continuously convert on one channel
//
void SetupADCContinuous(Uint16 channel)
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

    EALLOW;
    AdcaRegs.ADCSOC0CTL.bit.CHSEL  = channel;  //SOC will convert on channel
    AdcaRegs.ADCSOC1CTL.bit.CHSEL  = channel;  //SOC will convert on channel
    AdcaRegs.ADCSOC2CTL.bit.CHSEL  = channel;  //SOC will convert on channel
    AdcaRegs.ADCSOC3CTL.bit.CHSEL  = channel;  //SOC will convert on channel
    AdcaRegs.ADCSOC4CTL.bit.CHSEL  = channel;  //SOC will convert on channel
    AdcaRegs.ADCSOC5CTL.bit.CHSEL  = channel;  //SOC will convert on channel
    AdcaRegs.ADCSOC6CTL.bit.CHSEL  = channel;  //SOC will convert on channel
    AdcaRegs.ADCSOC7CTL.bit.CHSEL  = channel;  //SOC will convert on channel
    AdcaRegs.ADCSOC8CTL.bit.CHSEL  = channel;  //SOC will convert on channel
    AdcaRegs.ADCSOC9CTL.bit.CHSEL  = channel;  //SOC will convert on channel
    AdcaRegs.ADCSOC10CTL.bit.CHSEL = channel;  //SOC will convert on channel
    AdcaRegs.ADCSOC11CTL.bit.CHSEL = channel;  //SOC will convert on channel
    AdcaRegs.ADCSOC12CTL.bit.CHSEL = channel;  //SOC will convert on channel
    AdcaRegs.ADCSOC13CTL.bit.CHSEL = channel;  //SOC will convert on channel
    AdcaRegs.ADCSOC14CTL.bit.CHSEL = channel;  //SOC will convert on channel
    AdcaRegs.ADCSOC15CTL.bit.CHSEL = channel;  //SOC will convert on channel

    AdcaRegs.ADCSOC0CTL.bit.ACQPS  = acqps;    //sample window is acqps +
                                               //1 SYSCLK cycles
    AdcaRegs.ADCSOC1CTL.bit.ACQPS  = acqps;    //sample window is acqps +
                                               //1 SYSCLK cycles
    AdcaRegs.ADCSOC2CTL.bit.ACQPS  = acqps;    //sample window is acqps +
                                               //1 SYSCLK cycles
    AdcaRegs.ADCSOC3CTL.bit.ACQPS  = acqps;    //sample window is acqps +
                                               //1 SYSCLK cycles
    AdcaRegs.ADCSOC4CTL.bit.ACQPS  = acqps;    //sample window is acqps +
                                               //1 SYSCLK cycles
    AdcaRegs.ADCSOC5CTL.bit.ACQPS  = acqps;    //sample window is acqps +
                                               //1 SYSCLK cycles
    AdcaRegs.ADCSOC6CTL.bit.ACQPS  = acqps;    //sample window is acqps +
                                               //1 SYSCLK cycles
    AdcaRegs.ADCSOC7CTL.bit.ACQPS  = acqps;    //sample window is acqps +
                                               //1 SYSCLK cycles
    AdcaRegs.ADCSOC8CTL.bit.ACQPS  = acqps;    //sample window is acqps +
                                               //1 SYSCLK cycles                                               
    AdcaRegs.ADCSOC9CTL.bit.ACQPS  = acqps;    //sample window is acqps +
                                               //1 SYSCLK cycles
    AdcaRegs.ADCSOC10CTL.bit.ACQPS = acqps;    //sample window is acqps +
                                               //1 SYSCLK cycles
    AdcaRegs.ADCSOC11CTL.bit.ACQPS = acqps;    //sample window is acqps +
                                               //1 SYSCLK cycles
    AdcaRegs.ADCSOC12CTL.bit.ACQPS = acqps;    //sample window is acqps +
                                               //1 SYSCLK cycles
    AdcaRegs.ADCSOC13CTL.bit.ACQPS = acqps;    //sample window is acqps +
                                               //1 SYSCLK cycles
    AdcaRegs.ADCSOC14CTL.bit.ACQPS = acqps;    //sample window is acqps +
                                               //1 SYSCLK cycles
    AdcaRegs.ADCSOC15CTL.bit.ACQPS = acqps;    //sample window is acqps +
                                               //1 SYSCLK cycles

    AdcaRegs.ADCINTSEL1N2.bit.INT1E = 0; //disable INT1 flag
    AdcaRegs.ADCINTSEL1N2.bit.INT2E = 0; //disable INT2 flag
    AdcaRegs.ADCINTSEL3N4.bit.INT3E = 0; //disable INT3 flag
    AdcaRegs.ADCINTSEL3N4.bit.INT4E = 0; //disable INT4 flag

    AdcaRegs.ADCINTSEL1N2.bit.INT1CONT = 0;
    AdcaRegs.ADCINTSEL1N2.bit.INT2CONT = 0;
    AdcaRegs.ADCINTSEL3N4.bit.INT3CONT = 0;
    AdcaRegs.ADCINTSEL3N4.bit.INT4CONT = 0;

    AdcaRegs.ADCINTSEL1N2.bit.INT1SEL = 6;  //end of SOC6 will set INT1 flag
    AdcaRegs.ADCINTSEL1N2.bit.INT2SEL = 14; //end of SOC14 will set INT2 flag
    AdcaRegs.ADCINTSEL3N4.bit.INT3SEL = 7;  //end of SOC7 will set INT3 flag
    AdcaRegs.ADCINTSEL3N4.bit.INT4SEL = 15; //end of SOC15 will set INT4 flag

    //
    //ADCINT2 will trigger first 8 SOCs
    //
    AdcaRegs.ADCINTSOCSEL1.bit.SOC0 = 2;
    AdcaRegs.ADCINTSOCSEL1.bit.SOC1 = 2;
    AdcaRegs.ADCINTSOCSEL1.bit.SOC2 = 2;
    AdcaRegs.ADCINTSOCSEL1.bit.SOC3 = 2;
    AdcaRegs.ADCINTSOCSEL1.bit.SOC4 = 2;
    AdcaRegs.ADCINTSOCSEL1.bit.SOC5 = 2;
    AdcaRegs.ADCINTSOCSEL1.bit.SOC6 = 2;
    AdcaRegs.ADCINTSOCSEL1.bit.SOC7 = 2;

    //
    //ADCINT1 will trigger second 8 SOCs
    //
    AdcaRegs.ADCINTSOCSEL2.bit.SOC8 = 1;
    AdcaRegs.ADCINTSOCSEL2.bit.SOC9 = 1;
    AdcaRegs.ADCINTSOCSEL2.bit.SOC10 = 1;
    AdcaRegs.ADCINTSOCSEL2.bit.SOC11 = 1;
    AdcaRegs.ADCINTSOCSEL2.bit.SOC12 = 1;
    AdcaRegs.ADCINTSOCSEL2.bit.SOC13 = 1;
    AdcaRegs.ADCINTSOCSEL2.bit.SOC14 = 1;
    AdcaRegs.ADCINTSOCSEL2.bit.SOC15 = 1;
    EDIS;
}

//
// End of file
//
