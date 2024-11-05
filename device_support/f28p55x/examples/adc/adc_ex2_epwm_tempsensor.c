//###########################################################################
//
// FILE:   adc_ex2_epwm_tempsensor.c
//
// TITLE:  Sample temperature sensor and convert to temperature
//
//! \addtogroup bitfield_example_list
//! <h1> ADC temperature sensor conversion</h1>
//!
//! This example sets up the ePWM to periodically trigger the ADC. The
//! ADC converts the internal connection to the temperature sensor,
//! which is then interpreted as a temperature by calling the
//! GetTemperatureC function.
//!
//! After the program runs, the memory will contain:\n
//! - \b sensorSample \b : The raw reading from the temperature sensor. \n
//! - \b sensorTemp \b : The interpretation of the sensor sample as a
//! temperature in degrees Celsius.
//!
//
//#############################################################################
//
//
// 
// C2000Ware v5.04.00.00
//
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
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
//#############################################################################

//
// Included Files
//
#include "f28x_project.h"

//
// Defines
//
#define RESULTS_BUFFER_SIZE     256

//
// Globals
//
uint16_t sensorSample = 0;
uint16_t isrCount = 0;
int16_t sensorTemp = 0;

//
// Function Prototypes
//
void initADC(void);
void initEPWM(void);
void initADCSOC(void);
__interrupt void adcC1ISR(void);

//
// Main
//
void main(void)
{
    //
    // Initialize device clock and peripherals
    //
    InitSysCtrl();

    //
    // Initialize GPIO
    //
    InitGpio();

    //
    // Disable CPU interrupts
    //
    DINT;

    //
    // Initialize the PIE control registers to their default state.
    // The default state is all PIE interrupts disabled and flags
    // are cleared.
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
    //
    InitPieVectTable();

    //
    // Map ISR functions
    //
    EALLOW;
    PieVectTable.ADCC1_INT = &adcC1ISR;     // Function for ADCC interrupt 1
    EDIS;

    //
    // Configure the ADC and power it up
    //
    initADC();

    //
    // Configure the ePWM
    //
    initEPWM();

    //
    // Setup the ADC for ePWM triggered conversions on channel 1
    //
    initADCSOC();


    EALLOW;

    //
    // Enable PIE interrupt
    //
    PieCtrlRegs.PIEIER1.bit.INTx3 = 1;

    //
    // Sync ePWM
    //
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;

    //
    // Enable global Interrupts and higher priority real-time debug events:
    //
    IER |= M_INT1;  // Enable group 1 interrupts

    EINT;           // Enable Global interrupt INTM
    ERTM;           // Enable Global realtime interrupt DBGM

    InitTempSensor(3.3f);

    //
    // Start ePWM
    //
    EPwm1Regs.ETSEL.bit.SOCAEN = 1;    // Enable SOCA
    EPwm1Regs.TBCTL.bit.CTRMODE = 0;   // Unfreeze, and enter up count mode

    //
    // Wait while ePWM causes ADC conversions, which then cause interrupts,
    // which fill the results buffer, eventually setting the bufferFull
    // flag
    //
    while(1)
    {
    }
}

//
// initADC - Function to configure and power up ADCC.
//
void initADC(void)
{
    //
    // Setup VREF as internal
    //
    SetVREF(ADC_ADCC, ADC_INTERNAL, ADC_VREF3P3);

    EALLOW;

    //
    // Set ADCCLK divider to /4
    //
    AdccRegs.ADCCTL2.bit.PRESCALE = 6;

    //
    // Set pulse positions to late EOC
    //
    AdccRegs.ADCCTL1.bit.INTPULSEPOS = 1;

    //
    // Power up the ADC and then delay for 1 ms
    //
    AdccRegs.ADCCTL1.bit.ADCPWDNZ = 1;
    EDIS;

    DELAY_US(1000);
}

//
// initEPWM - Function to configure ePWM1 to generate the SOC.
//
void initEPWM(void)
{
    EALLOW;

    EPwm1Regs.ETSEL.bit.SOCAEN = 0;     // Disable SOC on A group
    EPwm1Regs.ETSEL.bit.SOCASEL = 4;    // Select SOC on up-count
    EPwm1Regs.ETPS.bit.SOCAPRD = 1;     // Generate pulse on 1st event

    EPwm1Regs.CMPA.bit.CMPA = 0x0800;   // Set compare A value to 2048 counts
    EPwm1Regs.TBPRD = 0x1000;           // Set period to 4096 counts

    EPwm1Regs.TBCTL.bit.CTRMODE = 3;    // Freeze counter

    EDIS;
}

//
// initADCSOC - Function to configure ADCA's SOC0 to be triggered by ePWM1.
//
void initADCSOC(void)
{
    //
    // Select the channels to convert and the end of conversion flag
    //
    EALLOW;

    AdccRegs.ADCSOC0CTL.bit.CHSEL = 0xC;     // SOC0 will convert pin C12

    AdccRegs.ADCSOC0CTL.bit.ACQPS = 45;     // Sample window is 10 SYSCLK cycles
    AdccRegs.ADCSOC0CTL.bit.TRIGSEL = 5;   // Trigger on ePWM1 SOCA

    AdccRegs.ADCINTSEL1N2.bit.INT1SEL = 0; // End of SOC0 will set INT1 flag
    AdccRegs.ADCINTSEL1N2.bit.INT1E = 1;   // Enable INT1 flag
    AdccRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; // Make sure INT1 flag is cleared

    EDIS;
}

//
// adcC1ISR - ADC C Interrupt 1 ISR
//
__interrupt void adcC1ISR(void)
{

    isrCount++;
    //
    // Add the latest result to the buffer
    // ADCRESULT0 is the result register of SOC0
    sensorSample  = AdccResultRegs.ADCRESULT0;
    sensorTemp = GetTemperatureC(sensorSample);

    //
    // Clear the interrupt flag
    //
    AdccRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;

    //
    // Check if overflow has occurred
    //
    if(1 == AdccRegs.ADCINTOVF.bit.ADCINT1)
    {
        AdccRegs.ADCINTOVFCLR.bit.ADCINT1 = 1; //clear INT1 overflow flag
        AdccRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //clear INT1 flag
    }

    //
    // Acknowledge the interrupt
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}


//
// End of file
//
