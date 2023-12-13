//###########################################################################
//
// FILE:   Example_2803xAdc_Periodic_Offset_Calibration.c
//
// TITLE:  ADC Periodic Calibration of Offset Error Example
//
//! \addtogroup f2803x_example_list
//! <h1> ADC Periodic Calibration of Offset Error </h1>
//!
//! This ADC example uses ePWM1 to generate a periodic ADC SOC - ADCINT1.
//! Three channels are converted, ADCINA4, ADCINA2, and ADCINB5.
//! Channel ADCINB5 is connected to VREFLO and used for periodic
//! calibration of offset error after every 10 conversions.
//!
//! Periodic Offset error calibration is done by first adding a positive
//! offset value (OFFTRIM_VALUE) to the OFFTRIM Register value in order to
//! later be able to adjust for negative offset error, if any. After 10
//! conversions of VREFLO, those are averaged together. The average is
//! subtracted from the value currently in the OFFTRIM register and the
//! positive offset value is added. This continuation of adjustment for
//! the offset error will help reduce it, especially is there are
//! variations in temperature.
//!
//! \b Watch \b Variables \n
//! - Voltage1[10]    - Last 10 ADCRESULT0 values
//! - Voltage2[10]    - Last 10 ADCRESULT1 values
//! - Voltage3[10]    - Last 10 ADCRESULT3 values
//! - ConversionCount - Current result number 0-9
//! - LoopCount       - Idle loop counter
//
//###########################################################################
// $TI Release: $
// $Release Date: $
// $Copyright:
// Copyright (C) 2009-2023 Texas Instruments Incorporated - http://www.ti.com/
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
#define OFFTRIM_VALUE 1         // Offset added to the OFFTRIM value

//
// Function Prototypes
//
__interrupt void adc_isr(void);
void Adc_Config(void);

//
// Global variables
//
Uint16 LoopCount;
Uint16 ConversionCount;
Uint16 Voltage1[10];
Uint16 Voltage2[10];
Uint16 Voltage3[10];

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
    // Disable CPU interrupts and clear all CPU interrupt flags
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
    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    //
    EALLOW;             // This is needed to write to EALLOW protected register
    PieVectTable.ADCINT1 = &adc_isr;
    EDIS;    // This is needed to disable write to EALLOW protected registers

    //
    // Step 4. Initialize all the Device Peripherals:
    //
    InitAdc();  // For this example, init the ADC
    AdcOffsetSelfCal();
    AdcRegs.ADCOFFTRIM.bit.OFFTRIM += OFFTRIM_VALUE;

    //
    // Step 5. User specific code, enable interrupts:
    //

    //
    // Enable VREFLO for Channel B5
    //
    AdcRegs.ADCCTL1.bit.VREFLOCONV = 1;

    //
    // Enable ADCINT1 in PIE
    //
    PieCtrlRegs.PIEIER1.bit.INTx1 = 1; // Enable INT 1.1 in the PIE
    IER |= M_INT1;                     // Enable CPU Interrupt 1
    EINT;                              // Enable Global interrupt INTM
    ERTM;                              // Enable Global realtime interrupt DBGM
    
    LoopCount = 0;
    ConversionCount = 0;

    //
    // Configure ADC
    // Note: Channel ADCINA4  will be double sampled to workaround the 
    // ADC 1st sample issue for rev0 silicon errata
    //
    EALLOW;
    AdcRegs.ADCCTL1.bit.INTPULSEPOS = 1; // ADCINT1 trips after AdcResults latch
    AdcRegs.INTSEL1N2.bit.INT1E     = 1; // Enabled ADCINT1
    AdcRegs.INTSEL1N2.bit.INT1CONT  = 0; // Disable ADCINT1 Continuous mode
    AdcRegs.INTSEL1N2.bit.INT1SEL   = 3; // setup EOC3 to trigger
                                         // ADCINT1 to fire

    //
    // set SOC0 channel select to ADCINA4
    // (dummy sample for rev0 errata workaround)
    //
    AdcRegs.ADCSOC0CTL.bit.CHSEL    = 4; 
    AdcRegs.ADCSOC1CTL.bit.CHSEL    = 4;   //set SOC1 channel select to ADCINA4
    AdcRegs.ADCSOC2CTL.bit.CHSEL    = 2;   //set SOC2 channel select to ADCINA2
    AdcRegs.ADCSOC3CTL.bit.CHSEL    = 13;  //set SOC3 channel select to ADCINB5
    
    //
    // set SOC0 start trigger on EPWM1A, due to round-robin SOC0 converts
    // first then SOC1, then SOC2
    //
    AdcRegs.ADCSOC0CTL.bit.TRIGSEL  = 5;  
    
    //
    // set SOC1 start trigger on EPWM1A, due to round-robin SOC0 converts 
    // first then SOC1, then SOC2
    //
    AdcRegs.ADCSOC1CTL.bit.TRIGSEL  = 5;  
    
    //
    // set SOC2 start trigger on EPWM1A, due to round-robin SOC0 converts 
    // first then SOC1, then SOC2
    //
    AdcRegs.ADCSOC2CTL.bit.TRIGSEL  = 5;  
    
    //
    // set SOC3 start trigger on EPWM1A, due to round-robin SOC0 converts
    // first then SOC1, then SOC2
    //
    AdcRegs.ADCSOC3CTL.bit.TRIGSEL  = 5;

    //
    // set SOC0 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)
    //
    AdcRegs.ADCSOC0CTL.bit.ACQPS    = 6;
    
    //
    // set SOC1 S/H Window to 11 ADC Clock Cycles, (10 ACQPS plus 1)
    //
    AdcRegs.ADCSOC1CTL.bit.ACQPS    = 10;
    
    //
    // set SOC2 S/H Window to 11 ADC Clock Cycles, (10 ACQPS plus 1)
    //
    AdcRegs.ADCSOC2CTL.bit.ACQPS    = 10;

    //
    // set SOC3 S/H Window to 11 ADC Clock Cycles, (10 ACQPS plus 1)
    //
    AdcRegs.ADCSOC3CTL.bit.ACQPS    = 10;


    EDIS;

    //
    // Assumes ePWM1 clock is already enabled in InitSysCtrl();
    //
    EPwm1Regs.ETSEL.bit.SOCAEN  = 1;        // Enable SOC on A group
    EPwm1Regs.ETSEL.bit.SOCASEL = 4;        // Select SOC from from CPMA on upcount
    EPwm1Regs.ETPS.bit.SOCAPRD  = 1;        // Generate pulse on 1st event
    EPwm1Regs.CMPA.half.CMPA    = 0x0080;   // Set compare A value
    EPwm1Regs.TBPRD             = 0xFFFF;   // Set period for ePWM1
    EPwm1Regs.TBCTL.bit.CTRMODE = 0;        // count up and start

    //
    // Wait for ADC interrupt
    //
    for(;;)
    {
        LoopCount++;
    }
}

//
// adc_isr 
//
__interrupt void
adc_isr(void)
{
    //
    // Discard ADCRESULT0 as part of the workaround to the
    // 1st sample errata for rev0
    //
    Voltage1[ConversionCount] = AdcResult.ADCRESULT1; 
    
    Voltage2[ConversionCount] = AdcResult.ADCRESULT2;

    Voltage3[ConversionCount] = AdcResult.ADCRESULT3;

    if (ConversionCount==9) // After 10 conversions re-calibrate the OFFTRIM value
       {
           Uint16 Avg=0;
           Uint16 sum=0;

           EALLOW;


           Uint16 i=0;

           //
           // Average the results of channel B5 (VREFLO)
           //
           for(i=0; i<=ConversionCount;i++){
               sum+=Voltage3[ConversionCount];
           }
           Avg=sum/10;

           //
           // Adjust the value of the OFFTRIM
           //
           AdcRegs.ADCOFFTRIM.bit.OFFTRIM= AdcRegs.ADCOFFTRIM.bit.OFFTRIM+OFFTRIM_VALUE-Avg;

           EDIS;

           ConversionCount=0;  //Reset the ConversionCount variable
     }
    else
       {
           ConversionCount++;
       }

    //
    // Clear ADCINT1 flag reinitialize for next SOC
    //
    AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;
    
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;   // Acknowledge interrupt to PIE

    return;
}

//
// End of File
//
