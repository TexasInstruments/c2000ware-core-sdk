//###########################################################################
//
// FILE:   adc_ex5_soc_continuous.c
//
// TITLE:  ADC continuous self-triggering.
//
//! \addtogroup driver_example_list
//! <h1> ADC Continuous Triggering (adc_soc_continuous)</h1>
//!
//! This example sets up the ADC to convert continuously, achieving maximum
//! sampling rate.\n
//!
//! \b External \b Connections \n
//!  - A0 pin should be connected to signal to convert
//!
//! \b Watch \b Variables \n
//! - \b adcAResults - A sequence of analog-to-digital conversion samples
//! from pin A0. The time between samples is the minimum possible based on the
//! ADC speed.
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
// Function Prototypes
//
void configureADC(uint32_t adcBase);
void setupADCContinuous(uint32_t adcBase, uint32_t channel);

//
// Defines
//
#define RESULTS_BUFFER_SIZE     256 //buffer for storing conversion results
                                //(size must be multiple of 16)
#define EX_ADC_RESOLUTION       12
// 12 for 12-bit conversion resolution, which supports (ADC_MODE_SINGLE_ENDED)
// Sample on single pin (VREFLO is the low reference)
// Or 16 for 16-bit conversion resolution, which supports (ADC_MODE_DIFFERENTIAL)
// Sample on pair of pins (difference between pins is converted, subject to
// common mode voltage requirements; see the device data manual)

//
// Globals
//
uint16_t adcAResults[RESULTS_BUFFER_SIZE];
uint16_t resultsIndex;

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
    // Configure the ADC and power it up
    //
    configureADC(ADCA_BASE);

    //
    // Setup the ADC for continuous conversions on channel 0
    //
    setupADCContinuous(ADCA_BASE, 0U);

    //
    // Initialize results buffer
    //
    for(resultsIndex = 0; resultsIndex < RESULTS_BUFFER_SIZE; resultsIndex++)
    {
        adcAResults[resultsIndex] = 0;
    }
    resultsIndex = 0;

    //
    // Enable global Interrupts and higher priority real-time debug events:
    //
    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global realtime interrupt DBGM

    //
    // Take conversions indefinitely in loop
    //
    do
    {
        //
        // Enable ADC interrupts
        //
        ADC_enableInterrupt(ADCA_BASE, ADC_INT_NUMBER1);
        ADC_enableInterrupt(ADCA_BASE, ADC_INT_NUMBER2);
        ADC_enableInterrupt(ADCA_BASE, ADC_INT_NUMBER3);
        ADC_enableInterrupt(ADCA_BASE, ADC_INT_NUMBER4);

        //
        // Clear all interrupts flags(INT1-4)
        //
        HWREGH(ADCA_BASE + ADC_O_INTFLGCLR) = 0x000F;

        //
        // Initialize results index
        //
        resultsIndex = 0;

        //
        // Software force start SOC0 to SOC7
        //
        HWREGH(ADCA_BASE + ADC_O_SOCFRC1) = 0x00FF;

        //
        // Keep taking samples until the results buffer is full
        //
        while(resultsIndex < RESULTS_BUFFER_SIZE)
        {
            //
            // Wait for first set of 8 conversions to complete
            //
            while(false == ADC_getInterruptStatus(ADCA_BASE, ADC_INT_NUMBER3));

            //
            // Clear the interrupt flag
            //
            ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER3);

            //
            // Save results for first 8 conversions
            //
            // Note that during this time, the second 8 conversions have
            // already been triggered by EOC6->ADCIN1 and will be actively
            // converting while first 8 results are being saved
            //
            adcAResults[resultsIndex++] = ADC_readResult(ADCARESULT_BASE,
                                                         ADC_SOC_NUMBER0);
            adcAResults[resultsIndex++] = ADC_readResult(ADCARESULT_BASE,
                                                         ADC_SOC_NUMBER1);
            adcAResults[resultsIndex++] = ADC_readResult(ADCARESULT_BASE,
                                                         ADC_SOC_NUMBER2);
            adcAResults[resultsIndex++] = ADC_readResult(ADCARESULT_BASE,
                                                         ADC_SOC_NUMBER3);
            adcAResults[resultsIndex++] = ADC_readResult(ADCARESULT_BASE,
                                                         ADC_SOC_NUMBER4);
            adcAResults[resultsIndex++] = ADC_readResult(ADCARESULT_BASE,
                                                         ADC_SOC_NUMBER5);
            adcAResults[resultsIndex++] = ADC_readResult(ADCARESULT_BASE,
                                                         ADC_SOC_NUMBER6);
            adcAResults[resultsIndex++] = ADC_readResult(ADCARESULT_BASE,
                                                         ADC_SOC_NUMBER7);

            //
            // Wait for the second set of 8 conversions to complete
            //
            while(false == ADC_getInterruptStatus(ADCA_BASE, ADC_INT_NUMBER4));

            //
            // Clear the interrupt flag
            //
            ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER4);

            //
            // Save results for second 8 conversions
            //
            // Note that during this time, the first 8 conversions have
            // already been triggered by EOC14->ADCIN2 and will be actively
            // converting while second 8 results are being saved
            //
            adcAResults[resultsIndex++] = ADC_readResult(ADCARESULT_BASE,
                                                         ADC_SOC_NUMBER8);
            adcAResults[resultsIndex++] = ADC_readResult(ADCARESULT_BASE,
                                                         ADC_SOC_NUMBER9);
            adcAResults[resultsIndex++] = ADC_readResult(ADCARESULT_BASE,
                                                         ADC_SOC_NUMBER10);
            adcAResults[resultsIndex++] = ADC_readResult(ADCARESULT_BASE,
                                                         ADC_SOC_NUMBER11);
            adcAResults[resultsIndex++] = ADC_readResult(ADCARESULT_BASE,
                                                         ADC_SOC_NUMBER12);
            adcAResults[resultsIndex++] = ADC_readResult(ADCARESULT_BASE,
                                                         ADC_SOC_NUMBER13);
            adcAResults[resultsIndex++] = ADC_readResult(ADCARESULT_BASE,
                                                         ADC_SOC_NUMBER14);
            adcAResults[resultsIndex++] = ADC_readResult(ADCARESULT_BASE,
                                                         ADC_SOC_NUMBER15);
        }

        //
        // Disable all ADCINT flags to stop sampling
        //
        ADC_disableInterrupt(ADCA_BASE, ADC_INT_NUMBER1);
        ADC_disableInterrupt(ADCA_BASE, ADC_INT_NUMBER2);
        ADC_disableInterrupt(ADCA_BASE, ADC_INT_NUMBER3);
        ADC_disableInterrupt(ADCA_BASE, ADC_INT_NUMBER4);

        //
        // At this point, adcAResults[] contains a sequence of conversions
        // from the selected channel
        //

        //
        // Software breakpoint, hit run again to get updated conversions
        //
        asm("   ESTOP0");
    }
    while(1); // Loop forever
}

//
// configureADC - Write ADC configurations and power up the ADC for both
//                ADC A and ADC B
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
// setupADCContinuous - setup the ADC to continuously convert on one channel
//
void setupADCContinuous(uint32_t adcBase, uint32_t channel)
{
    uint16_t acqps;

    //
    // Determine acquisition window (in SYSCLKS) based on resolution
    //
    if(EX_ADC_RESOLUTION == 12)
    {
        acqps = 30; // 150ns
    }
    else //resolution is 16-bit
    {
        acqps = 64; // 320ns
    }
    //
    // - NOTE: A longer sampling window will be required if the ADC driving
    //   source is less than ideal (an ideal source would be a high bandwidth
    //   op-amp with a small series resistance). See TI application report
    //   SPRACT6 for guidance on ADC driver design.
    // - NOTE: A slightly longer S+H window is used with 12-bit resolution to
    //   ensure the data collection loop can keep up with the ADC
    //   

    //
    // Configure SOCs channel no. & acquisition window.
    //
    ADC_setupSOC(adcBase, ADC_SOC_NUMBER0, ADC_TRIGGER_SW_ONLY,
                 (ADC_Channel)channel, acqps);
    ADC_setupSOC(adcBase, ADC_SOC_NUMBER1, ADC_TRIGGER_SW_ONLY,
                 (ADC_Channel)channel, acqps);
    ADC_setupSOC(adcBase, ADC_SOC_NUMBER2, ADC_TRIGGER_SW_ONLY,
                 (ADC_Channel)channel, acqps);
    ADC_setupSOC(adcBase, ADC_SOC_NUMBER3, ADC_TRIGGER_SW_ONLY,
                 (ADC_Channel)channel, acqps);
    ADC_setupSOC(adcBase, ADC_SOC_NUMBER4, ADC_TRIGGER_SW_ONLY,
                 (ADC_Channel)channel, acqps);
    ADC_setupSOC(adcBase, ADC_SOC_NUMBER5, ADC_TRIGGER_SW_ONLY,
                 (ADC_Channel)channel, acqps);
    ADC_setupSOC(adcBase, ADC_SOC_NUMBER6, ADC_TRIGGER_SW_ONLY,
                 (ADC_Channel)channel, acqps);
    ADC_setupSOC(adcBase, ADC_SOC_NUMBER7, ADC_TRIGGER_SW_ONLY,
                 (ADC_Channel)channel, acqps);
    ADC_setupSOC(adcBase, ADC_SOC_NUMBER8, ADC_TRIGGER_SW_ONLY,
                 (ADC_Channel)channel, acqps);
    ADC_setupSOC(adcBase, ADC_SOC_NUMBER9, ADC_TRIGGER_SW_ONLY,
                 (ADC_Channel)channel, acqps);
    ADC_setupSOC(adcBase, ADC_SOC_NUMBER10, ADC_TRIGGER_SW_ONLY,
                 (ADC_Channel)channel, acqps);
    ADC_setupSOC(adcBase, ADC_SOC_NUMBER11, ADC_TRIGGER_SW_ONLY,
                 (ADC_Channel)channel, acqps);
    ADC_setupSOC(adcBase, ADC_SOC_NUMBER12, ADC_TRIGGER_SW_ONLY,
                 (ADC_Channel)channel, acqps);
    ADC_setupSOC(adcBase, ADC_SOC_NUMBER13, ADC_TRIGGER_SW_ONLY,
                 (ADC_Channel)channel, acqps);
    ADC_setupSOC(adcBase, ADC_SOC_NUMBER14, ADC_TRIGGER_SW_ONLY,
                 (ADC_Channel)channel, acqps);
    ADC_setupSOC(adcBase, ADC_SOC_NUMBER15, ADC_TRIGGER_SW_ONLY,
                 (ADC_Channel)channel, acqps);

    //
    // Setup interrupt trigger for SOCs. ADCINT2 will trigger first 8 SOCs.
    // ADCINT1 will trigger next 8 SOCs
    //

    //
    // ADCINT2 trigger for SOC0-SOC7
    //
    ADC_setInterruptSOCTrigger(adcBase, ADC_SOC_NUMBER0,
                               ADC_INT_SOC_TRIGGER_ADCINT2);
    ADC_setInterruptSOCTrigger(adcBase, ADC_SOC_NUMBER1,
                               ADC_INT_SOC_TRIGGER_ADCINT2);
    ADC_setInterruptSOCTrigger(adcBase, ADC_SOC_NUMBER2,
                               ADC_INT_SOC_TRIGGER_ADCINT2);
    ADC_setInterruptSOCTrigger(adcBase, ADC_SOC_NUMBER3,
                               ADC_INT_SOC_TRIGGER_ADCINT2);
    ADC_setInterruptSOCTrigger(adcBase, ADC_SOC_NUMBER4,
                               ADC_INT_SOC_TRIGGER_ADCINT2);
    ADC_setInterruptSOCTrigger(adcBase, ADC_SOC_NUMBER5,
                               ADC_INT_SOC_TRIGGER_ADCINT2);
    ADC_setInterruptSOCTrigger(adcBase, ADC_SOC_NUMBER6,
                               ADC_INT_SOC_TRIGGER_ADCINT2);
    ADC_setInterruptSOCTrigger(adcBase, ADC_SOC_NUMBER7,
                               ADC_INT_SOC_TRIGGER_ADCINT2);

    //
    // ADCINT1 trigger for SOC8-SOC15
    //
    ADC_setInterruptSOCTrigger(adcBase, ADC_SOC_NUMBER8,
                               ADC_INT_SOC_TRIGGER_ADCINT1);
    ADC_setInterruptSOCTrigger(adcBase, ADC_SOC_NUMBER9,
                               ADC_INT_SOC_TRIGGER_ADCINT1);
    ADC_setInterruptSOCTrigger(adcBase, ADC_SOC_NUMBER10,
                               ADC_INT_SOC_TRIGGER_ADCINT1);
    ADC_setInterruptSOCTrigger(adcBase, ADC_SOC_NUMBER11,
                               ADC_INT_SOC_TRIGGER_ADCINT1);
    ADC_setInterruptSOCTrigger(adcBase, ADC_SOC_NUMBER12,
                               ADC_INT_SOC_TRIGGER_ADCINT1);
    ADC_setInterruptSOCTrigger(adcBase, ADC_SOC_NUMBER13,
                               ADC_INT_SOC_TRIGGER_ADCINT1);
    ADC_setInterruptSOCTrigger(adcBase, ADC_SOC_NUMBER14,
                               ADC_INT_SOC_TRIGGER_ADCINT1);
    ADC_setInterruptSOCTrigger(adcBase, ADC_SOC_NUMBER15,
                               ADC_INT_SOC_TRIGGER_ADCINT1);

    //
    // Disable Interrupt flags
    //
    ADC_disableInterrupt(adcBase, ADC_INT_NUMBER1);
    ADC_disableInterrupt(adcBase, ADC_INT_NUMBER2);
    ADC_disableInterrupt(adcBase, ADC_INT_NUMBER3);
    ADC_disableInterrupt(adcBase, ADC_INT_NUMBER4);

    //
    // Enable continuous mode
    //
    ADC_enableContinuousMode(adcBase, ADC_INT_NUMBER1);
    ADC_enableContinuousMode(adcBase, ADC_INT_NUMBER2);
    ADC_enableContinuousMode(adcBase, ADC_INT_NUMBER3);
    ADC_enableContinuousMode(adcBase, ADC_INT_NUMBER4);

    //
    // Configure interrupt triggers
    //
    ADC_setInterruptSource(adcBase, ADC_INT_NUMBER1, ADC_SOC_NUMBER6);
    ADC_setInterruptSource(adcBase, ADC_INT_NUMBER2, ADC_SOC_NUMBER14);
    ADC_setInterruptSource(adcBase, ADC_INT_NUMBER3, ADC_SOC_NUMBER7);
    ADC_setInterruptSource(adcBase, ADC_INT_NUMBER4, ADC_SOC_NUMBER15);
}

//
// End of file
//
