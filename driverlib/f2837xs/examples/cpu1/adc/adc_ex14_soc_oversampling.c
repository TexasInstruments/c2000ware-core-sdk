//#############################################################################
//
// FILE:   adc_ex14_soc_oversampling.c
//
// TITLE:  ADC Oversampling Using Multiple SOCs
//
//! \addtogroup driver_example_list
//! <h1>ADC SOC Oversampling </h1>
//!
//! This example sets up ePWM1 to periodically trigger a set of conversions on
//! ADCA including multiple SOCs that all convert A2 to achieve oversampling on
//! A2. 
//!
//! ADCA Interrupt ISRs are used to read results of ADCA.
//!
//! \b External \b Connections \n
//!  - A0, A1, A2 should be connected to signals to be converted.
//!
//! \b Watch \b Variables \n
//! - \b adcAResult0 - Digital representation of the voltage on pin A0
//! - \b adcAResult1 - Digital representation of the voltage on pin A1
//! - \b adcAResult2 - Digital representation of the voltage on pin A2
//!
//
//#############################################################################
//
// $Release Date: $
// $Copyright:
// Copyright (C) 2014-2023 Texas Instruments Incorporated - http://www.ti.com/
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

//
// Included Files
//
#include "driverlib.h"
#include "device.h"

//
// Defines
//
#define EX_ADC_RESOLUTION       12
// 12 for 12-bit conversion resolution, which supports (ADC_MODE_SINGLE_ENDED)
// Sample on single pin (VREFLO is the low reference)
// Or 16 for 16-bit conversion resolution, which supports (ADC_MODE_DIFFERENTIAL)
// Sample on pair of pins (difference between pins is converted, subject to
// common mode voltage requirements; see the device data manual)

//
// Globals
//
uint16_t adcAResult0; 
uint16_t adcAResult1;
uint16_t adcAResult2;

//
// Function Prototypes
//
void configureADC(uint32_t adcBase);
void initEPWM();
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
    Device_init();

    //
    // Disable pin locks and enable internal pullups.
    //
    Device_initGPIO();

    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // Interrupts that are used in this example are re-mapped to ISR functions
    // found within this file.
    //
    Interrupt_register(INT_ADCA1, &adcA1ISR);

    //
    // Set up the ADC and the ePWM and initialize the SOC
    //
    configureADC(ADCA_BASE);
    initEPWM();
    initADCSOC();

    //
    // Enable ADC interrupt
    //
    Interrupt_enable(INT_ADCA1);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Start ePWM1, enabling SOCA and putting the counter in up-count mode
    //
    EPWM_enableADCTrigger(EPWM1_BASE, EPWM_SOC_A);
    EPWM_setTimeBaseCounterMode(EPWM1_BASE, EPWM_COUNTER_MODE_UP);

    //
    // Take conversions indefinitely in loop
    //
    do
    {
        //
        // Wait while ePWM causes ADC conversions.
        // ADCA1 ISR processes each new set of conversions. 
        //
    }
    while(1);
}

//
// configureADC - Write ADC configurations and power up the ADC for the
// selected ADC
//
void configureADC(uint32_t adcBase)
{
    //
    // Set ADCDLK divider to /4
    //
    ADC_setPrescaler(adcBase, ADC_CLK_DIV_4_0);

    //
    // Set resolution and signal mode (see #defines above) and load
    // corresponding trims.
    //
#if(EX_ADC_RESOLUTION == 12)
    ADC_setMode(adcBase, ADC_RESOLUTION_12BIT, ADC_MODE_SINGLE_ENDED);
#elif(EX_ADC_RESOLUTION == 16)
    ADC_setMode(adcBase, ADC_RESOLUTION_16BIT, ADC_MODE_DIFFERENTIAL);
#endif

    //
    // Set pulse positions to late
    //
    ADC_setInterruptPulseMode(adcBase, ADC_PULSE_END_OF_CONV);

    //
    // Power up the ADCs and then delay for 1 ms
    //
    ADC_enableConverter(adcBase);

    //
    // Delay for 1ms to allow ADC time to power up
    //
    DEVICE_DELAY_US(1000);
}

//
// Function to configure ePWM1 to generate the SOC.
//
void initEPWM(void)
{
    //
    // Disable SOCA
    //
    EPWM_disableADCTrigger(EPWM1_BASE, EPWM_SOC_A);

    //
    // Configure the SOC to occur on the first up-count event
    //
    EPWM_setADCTriggerSource(EPWM1_BASE, EPWM_SOC_A, EPWM_SOC_TBCTR_U_CMPA);
    EPWM_setADCTriggerEventPrescale(EPWM1_BASE, EPWM_SOC_A, 1);

    //
    // Set the compare A value to 1000 and the period to 1999
    // Assuming ePWM clock is 100MHz, this would give 50kHz sampling
    // 50MHz ePWM clock would give 25kHz sampling, etc. 
    // The sample rate can also be modulated by changing the ePWM period
    // directly (ensure that the compare A value is less than the period). 
    //
    EPWM_setCounterCompareValue(EPWM1_BASE, EPWM_COUNTER_COMPARE_A, 1000);
    EPWM_setTimeBasePeriod(EPWM1_BASE, 1999);

    //
    // Set the local ePWM module clock divider to /1
    //
    EPWM_setClockPrescaler(EPWM1_BASE,
                           EPWM_CLOCK_DIVIDER_1,
                           EPWM_HSCLOCK_DIVIDER_1);

    //
    // Freeze the counter
    //
    EPWM_setTimeBaseCounterMode(EPWM1_BASE, EPWM_COUNTER_MODE_STOP_FREEZE);
}

//
// Function to configure SOCs on ADCA and ADCD to be triggered by ePWM1.
//
void initADCSOC(void)
{
        uint16_t acqps;

    //
    // Determine minimum acquisition window (in SYSCLKS) based on resolution
    //
    if(EX_ADC_RESOLUTION == 12)
    {
        acqps = 14; // 75ns
    }
    else //resolution is 16-bit
    {
        acqps = 63; // 320ns
    }
    //
    // - NOTE: A longer sampling window will be required if the ADC driving
    //   source is less than ideal (an ideal source would be a high bandwidth
    //   op-amp with a small series resistance). See TI application report
    //   SPRACT6 for guidance on ADC driver design.

    //
    // Select the channels to convert and the configure the ePWM trigger 
    //
    ADC_setupSOC(ADCA_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_EPWM1_SOCA,
                 ADC_CH_ADCIN0, acqps);
    ADC_setupSOC(ADCA_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_EPWM1_SOCA,
                 ADC_CH_ADCIN1, acqps);

    //
    // Setup multiple SOCs to oversample A2
    //
    ADC_setupSOC(ADCA_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_EPWM1_SOCA,
                 ADC_CH_ADCIN2, acqps);
    ADC_setupSOC(ADCA_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_EPWM1_SOCA,
                 ADC_CH_ADCIN2, acqps);
    ADC_setupSOC(ADCA_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_EPWM1_SOCA,
                 ADC_CH_ADCIN2, acqps);
    ADC_setupSOC(ADCA_BASE, ADC_SOC_NUMBER5, ADC_TRIGGER_EPWM1_SOCA,
                 ADC_CH_ADCIN2, acqps);

    //
    // Selec SOC5 on ADCA as the interrupt source.  
    //
    ADC_setInterruptSource(ADCA_BASE, ADC_INT_NUMBER1, ADC_SOC_NUMBER5);
    ADC_enableInterrupt(ADCA_BASE, ADC_INT_NUMBER1);
    ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1);
}

//
// ADC A Interrupt 1 ISR
//
__interrupt void adcA1ISR(void)
{
    //
    // Store results for A0 and A1
    //
    adcAResult0 = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER0);
    adcAResult1 = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER1);

    //
    // Average the 4 oversampled A2 results together
    //
    adcAResult2 = 
        (ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER2) +
        ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER3) +
        ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER4) +
        ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER5)) >> 2;

    //
    // Clear the interrupt flag
    //
    ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1);

    //
    // Check if overflow has occurred
    //
    if(true == ADC_getInterruptOverflowStatus(ADCA_BASE, ADC_INT_NUMBER1))
    {
        ADC_clearInterruptOverflowStatus(ADCA_BASE, ADC_INT_NUMBER1);
        ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1);
    }

    //
    // Acknowledge the interrupt
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
}

//
// End of file
//
