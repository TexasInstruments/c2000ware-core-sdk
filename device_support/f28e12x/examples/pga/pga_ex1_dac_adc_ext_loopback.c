//#############################################################################
//
// FILE:   pga_ex1_dac_adc_ext_loopback.c
//
// TITLE:   PGA DAC-ADC External Loopback Example.
//
//! \addtogroup bitfield_example_list
//! <h1>PGA DAC-ADC External Loopback Example</h1>
//!
//! This example generates 800 mV using the CMPSSLITE DAC output. CMPSSLITE is
//! used route the low DAC output to an external pin. The output of the low DAC
//! is externally connected to PGA for 2x gain amplification. It uses two ADC
//! channels to sample the CMPSSDAC output and the amplified voltage output
//! from PGA. The ADC is connected internally to these signals.
//!
//! \b External \b Connections \n
//!  - Connect CMPSSLITE_DACL_OUT (Analog Pin A0) to PGA1_INP1 (Analog Pin A11)
//!  - Connect PGA1_INM1 (Analog Pin A4) to GND
//!
//! \b Watch \b Variables \n
//!  - \b dacResult - The DAC output voltage.
//!  - \b pgaResult - The amplified DAC voltage.
//!  - \b pgaGain   - The ratio of the amplified DAC voltage to the original
//!                   DAC output. This should always read a value of ~2.0.
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
// Globals
//
volatile uint32_t dacResult;
volatile uint32_t pgaResult;
float pgaGain;

//
// Function Prototypes
//
void initPGA(void);
void initCMPSSLITE(void);
void initADC(void);
void initADCSOC(void);

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
    // Configure PGA1_INP1 as AGPIO
    //
    EALLOW;
    GpioCtrlRegs.GPHAMSEL.bit.GPIO237 = 1;
    EDIS;

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
    // Initialize PGA, CMPSSLITE, and ADC
    //
    initPGA();

    initCMPSSLITE();

    initADC();
    initADCSOC();

    DELAY_US(3000);

    //
    // Enable Global Interrupt (INTM) and real time interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Force ADC conversion
    //
    AdcaRegs.ADCSOCFRC1.bit.SOC0 = 1;
    AdcaRegs.ADCSOCFRC1.bit.SOC1 = 1;

    //
    // Loop indefinitely
    //
    while(1)
    {
        //
        // Check if conversion is complete
        //
        if(AdcaRegs.ADCINTFLG.bit.ADCINT1 == 1)
        {
            //
            // Acknowledge flag
            //
            AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;

            dacResult = AdcaResultRegs.ADCRESULT0.bit.RESULT;
            pgaResult = AdcaResultRegs.ADCRESULT1.bit.RESULT;
            pgaGain   = (float)pgaResult / (float)dacResult;

            //
            // Force ADC conversion
            //
            AdcaRegs.ADCSOCFRC1.bit.SOC0 = 1;
            AdcaRegs.ADCSOCFRC1.bit.SOC1 = 1;
        }
    }
}

//
// initADC - Function to configure and power up ADCA.
//
void initADC(void)
{
    //
    // Set the voltage reference
    //
    // NOTE:
    // VREFHI pin must not be driven by an external reference
    // voltage. Disconnect any external reference before proceeding
    //
    ESTOP0;
    SetVREF(ADC_ADCA, ADC_INTERNAL, ADC_VREF3P3);

    EALLOW;

    //
    // Set ADCCLK divider to /1
    //
    AdcaRegs.ADCCTL2.bit.PRESCALE = 1;

    //
    // Set pulse positions to late
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
// initADCSOC - Function to configure ADCA's SOC0 to be triggered by ePWM1.
//
void initADCSOC(void)
{
    //
    // Select the channels to convert and the end of conversion flag
    //
    EALLOW;

    //
    // Convert CMPSSLITE_DACL output
    //
    AdcaRegs.ADCSOC0CTL.bit.CHSEL = 0;     // SOC0 will convert A0 (CMPSSDAC_OUT)
    AdcaRegs.ADCSOC0CTL.bit.ACQPS = 4;     // Sample window is 5 SYSCLK cycles
    AdcaRegs.ADCSOC0CTL.bit.TRIGSEL = 0;   // Trigger by software

    //
    // Convert PGA1 output
    //
    AdcaRegs.ADCSOC1CTL.bit.CHSEL = 8;    // SOC1 will convert A8 (PGA1_OUT)
    AdcaRegs.ADCSOC1CTL.bit.ACQPS = 4;     // Sample window is 5 SYSCLK cycles
    AdcaRegs.ADCSOC1CTL.bit.TRIGSEL = 0;   // Trigger by software

    //
    // Configure ADC interrupt status flags
    //
    AdcaRegs.ADCINTSEL.bit.INT1SEL = 1; // End of SOC1 will set INT1 flag
    AdcaRegs.ADCINTSEL.bit.INT1E = 1;   // Enable INT1 flag
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; // Make sure INT1 flag is cleared

    EDIS;
}

//
// initCMPSSLITE - Configure CMPSSLITE
//
void initCMPSSLITE(void)
{
    EALLOW;

    //
    // Enable DAC output of the low comparator to an external pin
    //
    AnalogSubsysRegs.CMPSSCTL.bit.CMP3LDACOUTEN = 1;

    //
    // Set the value of the internal DAC of the low comparator
    //
    CmpssLite3Regs.DACLVALS.bit.DACVAL = 1000;

    //
    // Enable CMPSSLITE module
    //
    CmpssLite3Regs.COMPCTL.bit.COMPDACE = 1;

    EDIS;
}

//
// initPGA - Configure PGA1 gain
//
void initPGA(void)
{
    EALLOW;

    //
    // Set the PGA mode
    //
    Pga1Regs.MUXSEL.bit.PMUXSEL = 0;
    Pga1Regs.MUXSEL.bit.NMUXSEL = 1;
    Pga1Regs.MUXSEL.bit.MMUXSEL = 1;

    //
    // Set a gain of 2 to PGA1
    //
    Pga1Regs.PGACTL.bit.GAIN = 1;

    //
    // No filter resistor for output
    //
    Pga1Regs.PGACTL.bit.FILT_RES_SEL = 0;

    //
    // Enable PGA1
    //
    Pga1Regs.PGACTL.bit.PGAEN = 1;

    Pga1Regs.PGACTL.bit.PGA_OUTENABLE = 1;
    Pga1Regs.PGACTL.bit.PGA_OUTEN_INTGAIN = 1;

    EDIS;
}

//
// End of File
//
