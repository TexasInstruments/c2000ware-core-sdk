//###########################################################################
//
// FILE:   adc_soc_software_cpu01.c
//
// TITLE:  ADC software triggering for F2837xD.
//
//! \addtogroup cpu01_example_list
//! <h1> ADC SOC Software Force (adc_soc_software)</h1>
//!
//! This example converts some voltages on ADCA and ADCB  based on a software
//! trigger.
//!
//! After the program runs, the memory will contain:
//!
//! - \b AdcaResult0 \b: a digital representation of the voltage on pin A2\n
//! - \b AdcaResult1 \b: a digital representation of the voltage on pin A3\n
//! - \b AdcbResult0 \b: a digital representation of the voltage on pin B2\n
//! - \b AdcbResult1 \b: a digital representation of the voltage on pin B3\n
//!
//! Note: The software triggers for the two ADCs happen sequentially, so the
//! two ADCs will run asynchronously.
//!
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
void SetupADCSoftware(void);

//
// Globals
//
Uint16 AdcaResult0;
Uint16 AdcaResult1;
Uint16 AdcbResult0;
Uint16 AdcbResult1;

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
    InitGpio();

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
// Enable global Interrupts and higher priority real-time debug events:
//
    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global realtime interrupt DBGM

//
//Configure the ADCs and power them up
//
    ConfigureADC();

//
//Setup the ADCs for software conversions
//
    SetupADCSoftware();

//
//take conversions indefinitely in loop
//
    do
    {
        //
        //convert, wait for completion, and store results
        //start conversions immediately via software, ADCA
        //
        AdcaRegs.ADCSOCFRC1.all = 0x0003; //SOC0 and SOC1

        //
        //start conversions immediately via software, ADCB
        //
        AdcbRegs.ADCSOCFRC1.all = 0x0003; //SOC0 and SOC1

        //
        //wait for ADCA to complete, then acknowledge flag
        //
        while(AdcaRegs.ADCINTFLG.bit.ADCINT1 == 0);
        AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;

        //
        //wait for ADCB to complete, then acknowledge flag
        //
        while(AdcbRegs.ADCINTFLG.bit.ADCINT1 == 0);
        AdcbRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;

        //
        //store results
        //
        AdcaResult0 = AdcaResultRegs.ADCRESULT0;
        AdcaResult1 = AdcaResultRegs.ADCRESULT1;
        AdcbResult0 = AdcbResultRegs.ADCRESULT0;
        AdcbResult1 = AdcbResultRegs.ADCRESULT1;

        //
        //at this point, conversion results are stored in
        //AdcaResult0, AdcaResult1, AdcbResult0, and AdcbResult1
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
    AdcbRegs.ADCCTL2.bit.PRESCALE = 6; //set ADCCLK divider to /4
    AdcSetMode(ADC_ADCA, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);
    AdcSetMode(ADC_ADCB, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);

    //
    //Set pulse positions to late
    //
    AdcaRegs.ADCCTL1.bit.INTPULSEPOS = 1;
    AdcbRegs.ADCCTL1.bit.INTPULSEPOS = 1;

    //
    //power up the ADCs
    //
    AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1;
    AdcbRegs.ADCCTL1.bit.ADCPWDNZ = 1;

    //
    //delay for 1ms to allow ADC time to power up
    //
    DELAY_US(1000);

    EDIS;
}

//
// SetupADCSoftware - Setup ADC channels and acquisition window
//
void SetupADCSoftware(void)
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
    //Select the channels to convert and end of conversion flag
    //ADCA
    //
    EALLOW;
    AdcaRegs.ADCSOC0CTL.bit.CHSEL = 2;  //SOC0 will convert pin A2
    AdcaRegs.ADCSOC0CTL.bit.ACQPS = acqps; //sample window is acqps +
                                           //1 SYSCLK cycles
    AdcaRegs.ADCSOC1CTL.bit.CHSEL = 3;  //SOC1 will convert pin A3
    AdcaRegs.ADCSOC1CTL.bit.ACQPS = acqps; //sample window is acqps +
                                           //1 SYSCLK cycles
    AdcaRegs.ADCINTSEL1N2.bit.INT1SEL = 1; //end of SOC1 will set INT1 flag
    AdcaRegs.ADCINTSEL1N2.bit.INT1E = 1;   //enable INT1 flag
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //make sure INT1 flag is cleared
    //ADCB
    AdcbRegs.ADCSOC0CTL.bit.CHSEL = 2;  //SOC0 will convert pin B2
    AdcbRegs.ADCSOC0CTL.bit.ACQPS = acqps; //sample window is acqps +
                                           //1 SYSCLK cycles
    AdcbRegs.ADCSOC1CTL.bit.CHSEL = 3;  //SOC1 will convert pin B3
    AdcbRegs.ADCSOC1CTL.bit.ACQPS = acqps; //sample window is acqps +
                                           //1 SYSCLK cycles
    AdcbRegs.ADCINTSEL1N2.bit.INT1SEL = 1; //end of SOC1 will set INT1 flag
    AdcbRegs.ADCINTSEL1N2.bit.INT1E = 1;   //enable INT1 flag
    AdcbRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //make sure INT1 flag is cleared
    EDIS;
}

//
// End of file
//
