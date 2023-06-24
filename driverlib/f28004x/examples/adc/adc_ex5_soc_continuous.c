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
//
// $Copyright:
// Copyright (C) 2023 Texas Instruments Incorporated - http://www.ti.com/
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
#include "board.h"

//
// Defines
//
#define RESULTS_BUFFER_SIZE     256 //buffer for storing conversion results
                                //(size must be multiple of 16)

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
    // Board Initialization
    // - Configure the ADC and power it up
    // - Setup the ADC for continuous conversions on channel 0
    // 
    Board_init();

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
        ADC_enableInterrupt(myADC0_BASE, ADC_INT_NUMBER1);
        ADC_enableInterrupt(myADC0_BASE, ADC_INT_NUMBER2);
        ADC_enableInterrupt(myADC0_BASE, ADC_INT_NUMBER3);
        ADC_enableInterrupt(myADC0_BASE, ADC_INT_NUMBER4);

        //
        // Clear all interrupts flags(INT1-4)
        //
        HWREGH(myADC0_BASE + ADC_O_INTFLGCLR) = 0x000F;

        //
        // Initialize results index
        //
        resultsIndex = 0;

        //
        // Software force start SOC0 to SOC7
        //
        HWREGH(myADC0_BASE + ADC_O_SOCFRC1) = 0x00FF;

        //
        // Keep taking samples until the results buffer is full
        //
        while(resultsIndex < RESULTS_BUFFER_SIZE)
        {
            //
            // Wait for first set of 8 conversions to complete
            //
            while(false == ADC_getInterruptStatus(myADC0_BASE, ADC_INT_NUMBER3));

            //
            // Clear the interrupt flag
            //
            ADC_clearInterruptStatus(myADC0_BASE, ADC_INT_NUMBER3);

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
            while(false == ADC_getInterruptStatus(myADC0_BASE, ADC_INT_NUMBER4));

            //
            // Clear the interrupt flag
            //
            ADC_clearInterruptStatus(myADC0_BASE, ADC_INT_NUMBER4);

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
        ADC_disableInterrupt(myADC0_BASE, ADC_INT_NUMBER1);
        ADC_disableInterrupt(myADC0_BASE, ADC_INT_NUMBER2);
        ADC_disableInterrupt(myADC0_BASE, ADC_INT_NUMBER3);
        ADC_disableInterrupt(myADC0_BASE, ADC_INT_NUMBER4);

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
// End of file
//
