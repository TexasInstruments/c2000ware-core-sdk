//###########################################################################
//
// FILE:   Example_2803xAdc_Offset_Look_Up_Table.c
//
// TITLE:  ADC Offset Error Adjustment through Look Up Table Example
//
//! \addtogroup f2803x_example_list
//! <h1> ADC Offset Error Adjustment through Look Up Table </h1>
//!
//! This ADC example uses ePWM1 to generate a periodic ADC SOC - ADCINT1.
//! The same channel is converted, ADCINA4, with different ACQPS values
//! for each of the SOCs.
//!
//! This example uses a look up table of individual offset error
//! corrections for each of the ACQPS values to adjust the
//! readings accordingly. A modified version of AdcSelfCal()
//! function is used which sets the initial value of the
//! OFFTRIM value to 80 and calculates an average amount of
//! conversions when sampling the VREFLO. These conversion
//! results are stored in the Offset_Regs array. The
//! OFFTRIM register's value is then changed to reflect the
//! value for the first SOC (using the 1st ACQPS value).
//! This value will be used as a reference point for the other
//! values contained in the Offset_Regs array.The results read
//! for the other SOCs are then adjusted to correct for the
//! reference point and the actual offset error seen for the
//! ACQPS set for the corresponding SOC.
//!
//! \b Watch \b Variables \n
//! - Voltage1[10]    - Last 10 ADCRESULT1 values
//! - Voltage2[10]    - Last 10 ADCRESULT2 values
//! - Voltage3[10]    - Last 10 ADCRESULT3 values
//! - ConversionCount - Current result number 0-9
//! - LoopCount       - Idle loop counter
//
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
#define ADC_usDELAY  1000L
//
// Function Prototypes
//
Uint16 ADC_Offset_Calibration(Uint16 ACQPS_Value);
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
Uint16 Offset_Reg[4];
Uint16 ACQPS[4]= {6, 10, 23, 36};

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

    //
    // Step 5. User specific code
    //

    //
    //Create an array of offset values corresponding to each ACQPS value
    //
    Uint16 i=0;
    for(i=0; i<sizeof(ACQPS);i++){
        Offset_Reg[i]=ADC_Offset_Calibration(ACQPS[i]);
    }

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
    AdcRegs.ADCSOC1CTL.bit.CHSEL    = 4;  //set SOC1 channel select to ADCINA4
    AdcRegs.ADCSOC2CTL.bit.CHSEL    = 4;  //set SOC2 channel select to ADCINA4
    AdcRegs.ADCSOC3CTL.bit.CHSEL    = 4;  //set SOC3 channel select to ADCINA4
    
    //
    // set SOC0 start trigger on EPWM1A, due to round-robin SOC0 converts
    // first then SOC1, then SOC2, and lastly SOC3
    //
    AdcRegs.ADCSOC0CTL.bit.TRIGSEL  = 5;  
    AdcRegs.ADCSOC1CTL.bit.TRIGSEL  = 5;  
    AdcRegs.ADCSOC2CTL.bit.TRIGSEL  = 5;  
    AdcRegs.ADCSOC3CTL.bit.TRIGSEL  = 5;

    //
    // set SOC0 S/H Window to the first value defined in ACQPS[]
    //
    AdcRegs.ADCSOC0CTL.bit.ACQPS    = ACQPS[0];
    
    //
    // set SOC1 S/H Window to the second value defined in ACQPS[]
    //
    AdcRegs.ADCSOC1CTL.bit.ACQPS    = ACQPS[1];
    
    //
    // set SOC2 S/H Window to the third value defined in ACQPS[]
    //
    AdcRegs.ADCSOC2CTL.bit.ACQPS    = ACQPS[2];

    //
    // set SOC3 S/H Window to the fourth value defined in ACQPS[]
    //
    AdcRegs.ADCSOC3CTL.bit.ACQPS    = ACQPS[3];


    //
    // Setting the corresponding ADCOFFTRIM value for SOC1
    // All other offset adjustments will be scaled to this
    //
    AdcRegs.ADCOFFTRIM.bit.OFFTRIM=80-Offset_Reg[1];

    //
    // Correcting the Offset values based on the reference
    // value (in this case, SOC1)
    //
    Offset_Reg[2] -= Offset_Reg[1];
    Offset_Reg[3] -= Offset_Reg[1];

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

    EALLOW;

    //
    // Store the results for each conversion while adjusting each
    // conversion to the corresponding offset.
    //
    Voltage1[ConversionCount] = AdcResult.ADCRESULT1;
    Voltage2[ConversionCount] = AdcResult.ADCRESULT2 - Offset_Reg[2];
    Voltage3[ConversionCount] = AdcResult.ADCRESULT3 - Offset_Reg[3];
    
    //
    // Once the Voltage1, Voltage2, and Voltage3 arrays are full
    // re-initialize the ConversionCount and Index values.
    //

    if (ConversionCount==9)
       {
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

    EDIS;

    return;
}

//
// The following function will perform an offset calculation based on the AdcOffsetSelfCal()
// function, and return the value needed to perform a write to the ADCOFFTRIM register. This
// function was used instead of the AdcOffsetSelfCal() function to pass in an ACQPS value
// and have the offset trim be adjusted for each ACQPS value passed in.
//
Uint16 ADC_Offset_Calibration(Uint16 ACQPS_Value)
{
    Uint16 index= 0;           //Initialize index to 0
    Uint32 Sum= 0;             //Set sum to 0
    Uint32 Mean= 999;          //Initialize mean to known value
    Uint16 SampleSize= 256;    //(**NOTE: Sample size must be multiples of 2^x where is an integer >= 4)

    EALLOW;
    AdcRegs.ADCCTL1.bit.ADCREFSEL = 0;     //Select internal reference mode
    AdcRegs.ADCCTL1.bit.VREFLOCONV = 1;    //Select VREFLO connection on B5
    AdcChanSelect(13);                     //Select channel B5 for all SOC

    // Apply artificial offset (+80) to account for a negative offset that may
    // reside in the ADC core
    AdcRegs.ADCOFFTRIM.bit.OFFTRIM = 80;

    //Capture ADC conversion on VREFLO

    // Set the ADC sample window to the desired value
    // (Sample window = ACQPS + 1)
    AdcRegs.ADCSOC0CTL.bit.ACQPS  = ACQPS_Value;
    AdcRegs.ADCSOC1CTL.bit.ACQPS  = ACQPS_Value;
    AdcRegs.ADCSOC2CTL.bit.ACQPS  = ACQPS_Value;
    AdcRegs.ADCSOC3CTL.bit.ACQPS  = ACQPS_Value;
    AdcRegs.ADCSOC4CTL.bit.ACQPS  = ACQPS_Value;
    AdcRegs.ADCSOC5CTL.bit.ACQPS  = ACQPS_Value;
    AdcRegs.ADCSOC6CTL.bit.ACQPS  = ACQPS_Value;
    AdcRegs.ADCSOC7CTL.bit.ACQPS  = ACQPS_Value;
    AdcRegs.ADCSOC8CTL.bit.ACQPS  = ACQPS_Value;
    AdcRegs.ADCSOC9CTL.bit.ACQPS  = ACQPS_Value;
    AdcRegs.ADCSOC10CTL.bit.ACQPS = ACQPS_Value;
    AdcRegs.ADCSOC11CTL.bit.ACQPS = ACQPS_Value;
    AdcRegs.ADCSOC12CTL.bit.ACQPS = ACQPS_Value;
    AdcRegs.ADCSOC13CTL.bit.ACQPS = ACQPS_Value;
    AdcRegs.ADCSOC14CTL.bit.ACQPS = ACQPS_Value;
    AdcRegs.ADCSOC15CTL.bit.ACQPS = ACQPS_Value;

    // Enable ping-pong sampling

    // Enabled ADCINT1 and ADCINT2
    AdcRegs.INTSEL1N2.bit.INT1E = 1;
    AdcRegs.INTSEL1N2.bit.INT2E = 1;

    // Disable continuous sampling for ADCINT1 and ADCINT2
    AdcRegs.INTSEL1N2.bit.INT1CONT = 0;
    AdcRegs.INTSEL1N2.bit.INT2CONT = 0;

    // ADCINTs trigger at end of conversion
    AdcRegs.ADCCTL1.bit.INTPULSEPOS = 1;

    // Setup ADCINT1 and ADCINT2 trigger source
    AdcRegs.INTSEL1N2.bit.INT1SEL = 6;      //EOC6 triggers ADCINT1
    AdcRegs.INTSEL1N2.bit.INT2SEL = 14;     //EOC14 triggers ADCINT2

    // Setup each SOC's ADCINT trigger source
    //
    AdcRegs.ADCINTSOCSEL1.bit.SOC0  = 2;    //ADCINT2 starts SOC0-7
    AdcRegs.ADCINTSOCSEL1.bit.SOC1  = 2;
    AdcRegs.ADCINTSOCSEL1.bit.SOC2  = 2;
    AdcRegs.ADCINTSOCSEL1.bit.SOC3  = 2;
    AdcRegs.ADCINTSOCSEL1.bit.SOC4  = 2;
    AdcRegs.ADCINTSOCSEL1.bit.SOC5  = 2;
    AdcRegs.ADCINTSOCSEL1.bit.SOC6  = 2;
    AdcRegs.ADCINTSOCSEL1.bit.SOC7  = 2;
    AdcRegs.ADCINTSOCSEL2.bit.SOC8  = 1;    //ADCINT1 starts SOC8-15
    AdcRegs.ADCINTSOCSEL2.bit.SOC9  = 1;
    AdcRegs.ADCINTSOCSEL2.bit.SOC10 = 1;
    AdcRegs.ADCINTSOCSEL2.bit.SOC11 = 1;
    AdcRegs.ADCINTSOCSEL2.bit.SOC12 = 1;
    AdcRegs.ADCINTSOCSEL2.bit.SOC13 = 1;
    AdcRegs.ADCINTSOCSEL2.bit.SOC14 = 1;
    AdcRegs.ADCINTSOCSEL2.bit.SOC15 = 1;

    DELAY_US(ADC_usDELAY);           // Delay before converting ADC channels

    // Force Start SOC0-7 to begin ping-pong sampling
    AdcRegs.ADCSOCFRC1.all = 0x00FF;

    while( index < SampleSize )
    {
        // Wait for ADCINT1 to trigger, then add ADCRESULT0-7 registers to sum
        while (AdcRegs.ADCINTFLG.bit.ADCINT1 == 0) {}

        AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //clear ADCINT1 (INT1CONT = 0)
        Sum += AdcResult.ADCRESULT0;
        Sum += AdcResult.ADCRESULT1;
        Sum += AdcResult.ADCRESULT2;
        Sum += AdcResult.ADCRESULT3;
        Sum += AdcResult.ADCRESULT4;
        Sum += AdcResult.ADCRESULT5;
        Sum += AdcResult.ADCRESULT6;

        // Wait for SOC9 conversion to start, which gives time for SOC7
        // conversion result
        while( AdcRegs.ADCSOCFLG1.bit.SOC9 == 1 ) {}

        Sum += AdcResult.ADCRESULT7;

        // Wait for ADCINT2 to trigger, then add ADCRESULT8-15 registers to sum
        while (AdcRegs.ADCINTFLG.bit.ADCINT2 == 0) {}

        AdcRegs.ADCINTFLGCLR.bit.ADCINT2 = 1;   //clear ADCINT2 (INT2CONT = 0)
        Sum += AdcResult.ADCRESULT8;
        Sum += AdcResult.ADCRESULT9;
        Sum += AdcResult.ADCRESULT10;
        Sum += AdcResult.ADCRESULT11;
        Sum += AdcResult.ADCRESULT12;
        Sum += AdcResult.ADCRESULT13;
        Sum += AdcResult.ADCRESULT14;

        // Wait for SOC1 conversion to start, which gives time for SOC15
        // conversion result
        while( AdcRegs.ADCSOCFLG1.bit.SOC1 == 1 ) {}

        Sum += AdcResult.ADCRESULT15;

        index+=16;
     }

    // Disable ADCINT1 and ADCINT2 to STOP the ping-pong sampling
    AdcRegs.INTSEL1N2.bit.INT1E = 0;
    AdcRegs.INTSEL1N2.bit.INT2E = 0;

    // Wait for any pending SOCs to complete
    while(AdcRegs.ADCSOCFLG1.all != 0) {}

    // Clear any pending interrupts
    AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;
    AdcRegs.ADCINTFLGCLR.bit.ADCINT2 = 1;
    AdcRegs.ADCINTOVFCLR.bit.ADCINT1 = 1;
    AdcRegs.ADCINTOVFCLR.bit.ADCINT2 = 1;

    // reset RR pointer to 32, so that next SOC is SOC0
    AdcRegs.SOCPRICTL.bit.SOCPRIORITY = 1;

    while( AdcRegs.SOCPRICTL.bit.SOCPRIORITY != 1 );
     {
         AdcRegs.SOCPRICTL.bit.SOCPRIORITY = 0;
     }
     while( AdcRegs.SOCPRICTL.bit.SOCPRIORITY != 0 );

     Mean = Sum / SampleSize;    // Calculate average ADC sample value

    EDIS;

    return Mean;
}


//
// End of File
//
