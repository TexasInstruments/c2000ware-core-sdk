//###########################################################################
//
// FILE:   Example_2803xClaAdc.c
//
// TITLE:  CLA ADC example
//
//!  \addtogroup f2803x_example_list
//!  <h1>CLA ADC (cla_adc)</h1>
//!
//! In this example ePWM1 is setup to generate a periodic ADC SOC.
//! Channel ADCINA2 is converted. When the ADC begins conversion,
//! it will assert ADCINT2 which will start CLA task 2.
//!
//! Cla Task2 logs 20 ADCRESULT1 values in a circular buffer.
//! When Task2 completes an interrupt to the CPU clears the ADCINT2 flag.
//!
//! \b Watch \b Variables \n
//! - VoltageCLA       - Last 20 ADCRESULT1 values
//! - ConversionCount  - Current result number
//! - LoopCount        - Idle loop counter
//
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
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
#include "CLAShared.h"
#include <string.h>
#include <stdint.h>

//
// Prototype statements
//
__interrupt void cla1_isr2(void);

//
// Globals
//
#pragma DATA_SECTION(ConversionCount, "Cla1ToCpuMsgRAM");
#pragma DATA_SECTION(VoltageCLA,      "Cla1ToCpuMsgRAM");

Uint16 ConversionCount;
Uint16 LoopCount;
Uint16 VoltageCLA[NUM_DATA_POINTS];

//
// These are defined by the linker file
//
extern Uint16 Cla1funcsLoadStart;
extern Uint16 Cla1funcsLoadSize;
extern Uint16 Cla1funcsRunStart;

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
    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    //
    EALLOW;             // This is needed to write to EALLOW protected register
    PieVectTable.CLA1_INT2 = &cla1_isr2;
    EDIS;      // This is needed to disable write to EALLOW protected registers

    //
    // Step 4. Initialize all the Device Peripherals:
    //
    InitAdc();         // For this example, init the ADC
    AdcOffsetSelfCal();

    //
    // Step 5. User specific code, enable interrupts:
    //

    //
    // Enable ADCINT1 in PIE
    //
    PieCtrlRegs.PIEIER11.bit.INTx2 = 1; // Enable INT 11.2 in PIE (CLA Task2)
    IER |= M_INT11;                     // Enable CPU Interrupt 11
    EINT;                               // Enable Global interrupt INTM
    ERTM;                              // Enable Global realtime interrupt DBGM

    //
    // Copy CLA code from its load address to CLA program RAM
    //
    // Note: during debug the load and run addresses can be
    // the same as Code Composer Studio can load the CLA program
    // RAM directly.
    //
    // The ClafuncsLoadStart, ClafuncsLoadEnd, and ClafuncsRunStart
    // symbols are created by the linker.
    //
    memcpy((uint16_t *)&Cla1funcsRunStart,(uint16_t *)&Cla1funcsLoadStart,
            (unsigned long)&Cla1funcsLoadSize);

    //
    // Initialize the CLA registers
    //
    EALLOW;
    Cla1Regs.MVECT2 = (Uint16)((Uint32)&Cla1Task2 - (Uint32)&Cla1Prog_Start);
    Cla1Regs.MVECT8 = (Uint16)((Uint32)&Cla1Task8 - (Uint32)&Cla1Prog_Start);
    
    //
    // ADCINT2 starts Task 2
    //
    Cla1Regs.MPISRCSEL1.bit.PERINT2SEL = CLA_INT2_ADCINT2; 
    
    Cla1Regs.MMEMCFG.bit.PROGE = 1;  // Map CLA program memory to the CLA
    Cla1Regs.MCTL.bit.IACKE = 1;     // Enable IACK to start tasks via software
    Cla1Regs.MIER.all = (M_INT8 | M_INT2);   // Enable Task 8 and Task 2
    Cla1ForceTask8andWait();    // Force CLA task 8.
                                // This will initialize ConversionCount to zero

    //
    // ADCINT trips when ADC begins conversion
    //
    AdcRegs.ADCCTL1.bit.INTPULSEPOS = 0;
    
    AdcRegs.INTSEL1N2.bit.INT2E = 1;    //Enable ADCINT2
    AdcRegs.INTSEL1N2.bit.INT2CONT = 0; //Disable ADCINT2 Continuous mode
    AdcRegs.INTSEL1N2.bit.INT2SEL = 1;  //setup EOC1 to trigger ADCINT2 to fire
    AdcRegs.ADCSOC1CTL.bit.CHSEL = 2;   //set SOC1 channel select to ADCINA2
    AdcRegs.ADCSOC1CTL.bit.TRIGSEL = 5;  //set SOC1 start trigger on EPWM1A
    
    //
    // set SOC1 S/H Window to 7 ADC Clock Cycles, (6 ACQPS plus 1)
    //
    AdcRegs.ADCSOC1CTL.bit.ACQPS    = 6;    
    EDIS;

    //
    // Assumes ePWM1 clock is already enabled in InitSysCtrl();
    //
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;
    EDIS;
    EPwm1Regs.ETSEL.bit.SOCAEN  = 1;    // Enable SOC on A group
    EPwm1Regs.ETSEL.bit.SOCASEL = 4;    // Select SOC from from CPMA on upcount
    EPwm1Regs.ETPS.bit.SOCAPRD  = 1;    // Generate pulse on 1st event
    EPwm1Regs.CMPA.half.CMPA = 0x2EE;   // Set compare A value
    
    //
    // Set period for ePWM1 - this will determine the sampling frequency(20KHz)
    //
    EPwm1Regs.TBPRD = 0x5DC;

    EPwm1Regs.TBCTL.bit.CTRMODE     = 0;        // count up and start
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;

    //
    // Wait for ADC interrupt
    //
    for(;;)
    {
        LoopCount++;
    }
}

//
// cla1_isr2 - This interrupt occurs when CLA Task 2 completes
//
__interrupt void 
cla1_isr2()
{
    //
    // Clear ADCINT2 flag reinitialize for next SOC
    //
    AdcRegs.ADCINTFLGCLR.bit.ADCINT2 = 1;    
    PieCtrlRegs.PIEACK.all = 0xFFFF;
}

//
// End of File
//

