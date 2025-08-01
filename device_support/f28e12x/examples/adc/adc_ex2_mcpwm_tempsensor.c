//###########################################################################
//
// FILE:   adc_ex2_mcpwm_tempsensor.c
//
// TITLE:  Sample temperature sensor and convert to temperature
//
//! \addtogroup bitfield_example_list
//! <h1> ADC temperature sensor conversion</h1>
//!
//! This example sets up the MCPWM to periodically trigger the ADC. The
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
// $Copyright:
// Copyright (C) 2025 Texas Instruments Incorporated - http://www.ti.com/
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
void initMCPWM(void);
void initADCSOC(void);
__interrupt void adcA1ISR(void);

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
    PieVectTable.ADCA1_INT = &adcA1ISR;     // Function for ADCA interrupt 1
    EDIS;

    //
    // Configure the ADC and power it up
    //
    initADC();

    //
    // Configure the MCPWM
    //
    initMCPWM();

    //
    // Setup the ADC for MCPWM triggered conversions on channel 1
    //
    initADCSOC();

    //
    // Enable global Interrupts and higher priority real-time debug events:
    //
    IER |= M_INT1;  // Enable group 1 interrupts

    EINT;           // Enable Global interrupt INTM
    ERTM;           // Enable Global realtime interrupt DBGM


    EALLOW;

    //
    // Enable PIE interrupt
    //
    PieCtrlRegs.PIEIER1.bit.INTx1 = 1;

    //
    // Sync MCPWM
    //
    CpuSysRegs.PERCLKCR.bit.TBCLKSYNC = 1;

    InitTempSensor(3.3f);

    //
    // Start MCPWM
    //
    Pwm1Regs.SOCEN.bit.SOCA_ENABLE = 1;    // Enable SOCA
    Pwm1Regs.TBCTL.bit.CTRMODE = 0;   // Unfreeze, and enter up count mode

    //
    // Wait while MCPWM causes ADC conversions, which then cause interrupts,
    // which fill the results buffer, eventually setting the bufferFull
    // flag
    //
    while(1)
    {
    }
}

//
// initADC - Function to configure and power up ADCA.
//
void initADC(void)
{
    //
    // Setup VREF as internal
    //
    SetVREF(ADC_ADCA, ADC_INTERNAL, ADC_VREF3P3);

    EALLOW;

    //
    // Set ADCCLK divider to /4
    //
    AdcaRegs.ADCCTL2.bit.PRESCALE = 6;

    //
    // Set pulse positions to late EOC
    //
    AdcaRegs.ADCCTL1.bit.INTPULSEPOS = 1;

    //
    // Power up the ADC and then delay for 1 ms
    //
    AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1;
    EDIS;

    DELAY_US(1000);
}

//
// initMCPWM - Function to configure MCPWM1 to generate the SOC.
//
void initMCPWM(void)
{
    EALLOW;
    Pwm1Regs.TBCTL.bit.PRDLD = 1;
    Pwm1Regs.CMPCTL.bit.PWM1_LOADAMODE = 3;

    Pwm1Regs.SOCEN.bit.SOCA_ENABLE = 0;    // Disable SOCA
    Pwm1Regs.SOCSEL.bit.SOCA_SEL = 10;    // Select SOC on up-count
    Pwm1Regs.SOCPERIOD.bit.SOCA_PERIOD = 1;     // Generate pulse on 1st event

    Pwm1Regs.PWM1_CMPA.bit.PWM1_CMPA = 0x0800;   // Set compare A value to 2048 counts
    Pwm1Regs.TBPRD.bit.TBPRD = 0x1000;           // Set period to 4096 counts

    Pwm1Regs.TBCTL.bit.CTRMODE = 3;    // Freeze counter

    EDIS;
}

//
// initADCSOC - Function to configure ADCA's SOC0 to be triggered by MCPWM1.
//
void initADCSOC(void)
{
    //
    // Select the channels to convert and the end of conversion flag
    //
    EALLOW;

    AdcaRegs.ADCSOC0CTL.bit.CHSEL = 22;     // SOC0 will convert pin A22

    AdcaRegs.ADCSOC0CTL.bit.ACQPS = 112;     // Sample window is 10 SYSCLK cycles
    AdcaRegs.ADCSOC0CTL.bit.TRIGSEL = 5;   // Trigger on MCPWM1 SOCA

    AdcaRegs.ADCINTSEL.bit.INT1SEL = 0; // End of SOC0 will set INT1 flag
    AdcaRegs.ADCINTSEL.bit.INT1E = 1;   // Enable INT1 flag
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; // Make sure INT1 flag is cleared

    EDIS;
}

//
// adcA1ISR - ADC A Interrupt 1 ISR
//
__interrupt void adcA1ISR(void)
{

    isrCount++;
    //
    // Add the latest result to the buffer
    // ADCRESULT0 is the result register of SOC0
    sensorSample  = AdcaResultRegs.ADCRESULT0.bit.RESULT;
    sensorTemp = GetTemperatureC(sensorSample);

    //
    // Clear the interrupt flag
    //
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;

    //
    // Check if overflow has occurred
    //
    if(1 == AdcaRegs.ADCINTOVF.bit.ADCINT1OVF)
    {
        AdcaRegs.ADCINTOVFCLR.bit.ADCINT1OVF = 1; //clear INT1 overflow flag
        AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //clear INT1 flag
    }

    //
    // Acknowledge the interrupt
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}


//
// End of file
//
