//###########################################################################
//
//  FILE:  Example_2805xPgaComp.c
//
//  TITLE: PGA Error Compensation example
//
//! \addtogroup f2805x_example_list
//! <h1> PGA Error Compensation </h1>
//!
//! This ADC/PGA example uses ePWM1 to generate a periodic ADC SOC - ADCINT1.
//! The PGAs are configured for a GAIN of 3 and are converted on channels
//! ADCINA3 and ADCINA1. The ADC conversions are post-processed for error
//! compensation.
//!
//! \b Watch \b Variables \n
//! - Voltage1[10]    - Last 10 ADCRESULT0 values
//! - Voltage2[10]    - Last 10 ADCRESULT1 values
//! - ConversionCount - Current result number 0-9
//! - LoopCount       - Idle loop counter
//
//###########################################################################
// $TI Release: $
// $Release Date: $
// $Copyright:
// Copyright (C) 2012-2024 Texas Instruments Incorporated - http://www.ti.com/
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

//
// Prototype statements for functions found within this file.
//
__interrupt void adc_isr(void);

//
// Global variables used in this example:
//
Uint16 LoopCount;
Uint16 ConversionCount;
Uint16 Voltage1[10];
Uint16 Voltage2[10];

main()
{
    //
    // Step 1. Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    // This example function is found in the F2805x_SysCtrl.c file.
    //
    InitSysCtrl();

    //
    // Step 2. Initialize GPIO:
    // This example function is found in the F2805x_Gpio.c file and
    // illustrates how to set the GPIO to it's default state.
    //
    // InitGpio();  // Skipped for this example

    //
    // Step 3. Clear all __interrupts and initialize PIE vector table:
    // Disable CPU __interrupts
    //
    DINT;

    //
    // Initialize the PIE control registers to their default state.
    // The default state is all PIE __interrupts disabled and flags
    // are cleared.
    // This function is found in the F2805x_PieCtrl.c file.
    //
    InitPieCtrl();

    //
    // Disable CPU __interrupts and clear all CPU __interrupt flags:
    //
    IER = 0x0000;
    IFR = 0x0000;

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    // This will populate the entire table, even if the __interrupt
    // is not used in this example.  This is useful for debug purposes.
    // The shell ISR routines are found in F2805x_DefaultIsr.c.
    // This function is found in F2805x_PieVect.c.
    //
    InitPieVectTable();

    //
    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    //
    EALLOW;  // This is needed to write to EALLOW protected register
    PieVectTable.ADCINT1 = &adc_isr;
    EDIS;    // This is needed to disable write to EALLOW protected registers

    //
    // Step 4. Initialize all the Device Peripherals:
    //
    InitAdc();  // For this example, init the ADC
    AdcOffsetSelfCal();

    //
    // Step 5. User specific code, enable __interrupts:
    //

    //
    // Enable ADCINT1 in PIE
    //
    PieCtrlRegs.PIEIER1.bit.INTx1 = 1;   // Enable INT 1.1 in the PIE
    IER |= M_INT1;                       // Enable CPU Interrupt 1
    EINT;                                // Enable Global __interrupt INTM
    ERTM;                           // Enable Global realtime __interrupt DBGM

    LoopCount = 0;
    ConversionCount = 0;

    //
    // Configure ADC
    // Note: Channel ADCINA3  will be double sampled to workaround the ADC
    // 1st sample issue for rev0 silicon errata
    //
    EALLOW;
    AnalogSubsysRegs.PGAEN.bit.AMPA1EN        = 1;
    AnalogSubsysRegs.PGAEN.bit.AMPA3EN        = 1;
    AnalogSubsysRegs.AMPM1_GAIN.bit.AMPA1GAIN = PGA_GAIN_3;
    AnalogSubsysRegs.AMPM1_GAIN.bit.AMPA3GAIN = PGA_GAIN_3;

    AdcRegs.ADCCTL1.bit.INTPULSEPOS = 1;  //ADCINT1 trips after AdcResults latch
    AdcRegs.INTSEL1N2.bit.INT1E     = 1;  //Enabled ADCINT1
    AdcRegs.INTSEL1N2.bit.INT1CONT  = 0;  //Disable ADCINT1 Continuous mode
    AdcRegs.INTSEL1N2.bit.INT1SEL   = 2;  //setup EOC2 to trigger ADCINT1
    AdcRegs.ADCSOC0CTL.bit.CHSEL    = 3;  //set SOC0 channel select to ADCINA3
    AdcRegs.ADCSOC1CTL.bit.CHSEL    = 3;  //set SOC1 channel select to ADCINA3
    AdcRegs.ADCSOC2CTL.bit.CHSEL    = 1;  //set SOC2 channel select to ADCINA1
    AdcRegs.ADCSOC0CTL.bit.TRIGSEL  = 5;  //set SOC0 start trigger on EPWM1A
    AdcRegs.ADCSOC1CTL.bit.TRIGSEL  = 5;  //set SOC1 start trigger on EPWM1A
    AdcRegs.ADCSOC2CTL.bit.TRIGSEL  = 5;  //set SOC2 start trigger on EPWM1A
    AdcRegs.ADCSOC0CTL.bit.ACQPS    = 23; //SOC0 S/H Window = 24 (23+1) Cycles
    AdcRegs.ADCSOC1CTL.bit.ACQPS    = 23; //SOC0 S/H Window = 24 (23+1) Cycles
    AdcRegs.ADCSOC2CTL.bit.ACQPS    = 23; //SOC0 S/H Window = 24 (23+1) Cycles
    EDIS;

    //
    // Assumes ePWM1 clock is already enabled in InitSysCtrl();
    //
    EPwm1Regs.ETSEL.bit.SOCAEN   = 1;        // Enable SOC on A group

    //
    // Select SOC from from CPMA on upcount
    //
    EPwm1Regs.ETSEL.bit.SOCASEL  = 4;
    EPwm1Regs.ETPS.bit.SOCAPRD   = 1;        // Generate pulse on 1st event
    EPwm1Regs.CMPA.half.CMPA     = 0x0080;   // Set compare A value
    EPwm1Regs.TBPRD              = 0xFFFF;   // Set period for ePWM1
    EPwm1Regs.TBCTL.bit.CTRMODE  = 0;        // count up and start

    //
    // Wait for ADC __interrupt
    //
    for(;;)
    {
        LoopCount++;
    }
}

__interrupt void  adc_isr(void)
{
    //
    // Discard ADCRESULT0 as part of the workaround to the 1st sample errata
    // for rev0
    //
    Voltage1[ConversionCount] = PgaComp(PGA_CHAN_A3, PGA_GAIN_3,
                                            AdcResult.ADCRESULT1);
    Voltage2[ConversionCount] = PgaComp(PGA_CHAN_A1, PGA_GAIN_3,
                                            AdcResult.ADCRESULT2);

    //
    // If 10 conversions have been logged, start over
    //
    if(ConversionCount == 9)
    {
        ConversionCount = 0;
    }
    else
    {
        ConversionCount++;
    }

    //
    // Clear ADCINT1 flag reinitialize for next SOC
    //
    AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;  // Acknowledge __interrupt to PIE

    return;
}


