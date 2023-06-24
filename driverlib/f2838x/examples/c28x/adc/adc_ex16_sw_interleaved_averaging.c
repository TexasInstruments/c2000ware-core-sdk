//#############################################################################
//
// FILE:   adc_ex16_sw_interleaved_averaging.c
//
// TITLE:  ADC Interleaved Averaging in Software
//
//! \addtogroup driver_example_list
//! <h1>ADC Interleaved Averaging in Software</h1>
//!
//! This example demonstrates software interleaved averaging of ADC input
//! channels. ADCA/B channel 0 and 1 are sampled one after another in order
//! to achieve interleaved averaging. SOC0-15 of ADCA and ADCB are configured
//! to sample channel 0 and 1 alternatively with channel 0 being sampled by
//! even SOCs namely SOC0, 2, 4, 6, 8, 10, 12 & 14 and channel 1 being sampled
//! by odd SOCs namely SOC1, 3, 5, 7, 9, 11, 13 & 15.
//!
//! Sampling is initially triggered through external GPIO signal through
//! enabling ADCEXTSOC signal via input XBAR and thereafter through ADCINT1.
//! GPIO33 is configured to trigger ADCA and B SOCs for the first time in order
//! to ensure synchronous operation. GPIO33 needs to be connected to GPIO32
//! which in turn is driven by software to trigger the respective ADC SOCs.
//!
//! ADCA Interrupt ISRs are used to read results of both ADCA and ADCB to
//! demonstrate parallel operation of multiple ADCs. ADCINT2 is configured
//! to be triggered after completion of SOC7 while ADCINT1 is configured to be
//! triggered after completion of SOC15 conversion and respective SOC results
//! of ADCA and ADCB are read in ADCAINT2 and ADCAINT1 ISRs. Read SOC0-SOC15
//! ADC results are then averaged in ADCINT1 ISR to get the filtered ADC output.
//!
//! Early interrupt mode is configured to trigger the ADC interrupt just at the
//! end of acquisition window in order to save cycles(~42 cycles) since ADCA
//! result of SOC7 in ADCINT2 and SOC15 in ADCINT1 are read post around 60 and
//! 65 cycles respectively. Also, Fast ISRs are configured in the example to
//! save some cycles during compiler specific context save and restore.
//!
//! Optimization level: This example is expected to be run with opt level = 2
//!
//! Sampling rate related calculations:
//!  - ADC acquisition cycles programmed( S + H) = 15 SYSCLKS
//!  - Conversion time for 12-bit data = 10.5 ADCCLKS =  N = 42 SYSCLKs
//!  - Time from 1st SOC trigger to interrupt trigger: 15 * 57 + 15 = 870 SYSCLKs
//!  - Next ADC trigger will come after 870 SYSCLKs
//!  - Approximate ISR trigger frequency = 1/(870 * 5ns) = 1/4350ns = 229 KSPS
//!  - Time taken in ADCINT1 ISR : 132 SYSCLKs (Fast ISR)(O2)
//!  - Time taken in ADCINT2 ISR : 76 SYSCLKs  (Fast ISR)(O2)
//!
//! To view results in graph window, add breakpoint inside while(1) loop in
//! main() where bufferFull flag is cleared and plot the watch variables.
//!
//! \b External \b Connections \n
//!  - A0, A1, B0 and B1 pins should be connected to signals to be converted
//!  - Connect GPIO32 to GPIO33 to trigger ADC channels for the first time
//!
//! \b Watch \b Variables \n
//! - \b adcA0Results - A sequence of analog-to-digital conversion samples from
//!   pin A0.
//! - \b adcA1Results - A sequence of analog-to-digital conversion samples from
//!   pin A1.
//! - \b adcB0Results - A sequence of analog-to-digital conversion samples from
//!   pin B0.
//! - \b adcB1Results - A sequence of analog-to-digital conversion samples from
//!   pin B1.
//!
//
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2022 Texas Instruments Incorporated - http://www.ti.com
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
#include "driverlib.h"
#include "device.h"

//
// Defines
//
#define RESULTS_BUFFER_SIZE     256U

//
// Macros to define ADC resolution and input signal mode. Valid values of
// resolution are 12 for 12-bit conversion resolution, which support input
// modes ADC_MODE_SINGLE_ENDED & 16 for 16-bit conversion resolution, which
// support ADC_MODE_SINGLE_ENDED & ADC_MODE_DIFFERENTIAL input signal modes.
//
#define EX_ADC_RESOLUTION     (ADC_RESOLUTION_12BIT)
#define EX_ADC_INPUT_MODE     (ADC_MODE_SINGLE_ENDED)

//
// Globals
//
uint16_t adcA0Results[RESULTS_BUFFER_SIZE];  // Buffer for ADCA channel 0
uint16_t adcA1Results[RESULTS_BUFFER_SIZE];  // Buffer for ADCA channel 1
uint16_t adcB0Results[RESULTS_BUFFER_SIZE];  // Buffer for ADCB channel 0
uint16_t adcB1Results[RESULTS_BUFFER_SIZE];  // Buffer for ADCB channel 1
volatile uint32_t sumACh0 = 0, sumACh1 = 0, averageACh0 = 0, averageACh1 = 0;
volatile uint32_t sumBCh0 = 0, sumBCh1 = 0, averageBCh0 = 0, averageBCh1 = 0;
volatile uint16_t indexA = 0, indexB = 0;    // Index into result buffer
volatile uint16_t bufferFull = 0;            // Flag to indicate buffer is full
volatile uint32_t countIdle = 0;             // Idle counter

//
// Function Prototypes
//
void configureADC(uint32_t adcBase);
void initEPWM(uint32_t pwmBase);
void initADCSOC(uint32_t adcBase);
void initADCGPIOTrigger(void);

//
// ISRs
//
__interrupt void adcA1ISR(void);
#pragma CODE_SECTION(adcA1ISR, ".TI.ramfunc")
#pragma INTERRUPT (adcA1ISR, HPI)
__interrupt void adcA2ISR(void);
#pragma CODE_SECTION(adcA2ISR, ".TI.ramfunc")
#pragma INTERRUPT (adcA2ISR, HPI)

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
    Interrupt_register(INT_ADCA2, &adcA2ISR);

    //
    // Set up the ADC and the ePWM and initialize the SOC
    //
    configureADC(ADCA_BASE);
    configureADC(ADCB_BASE);
    initADCSOC(ADCA_BASE);
    initADCSOC(ADCB_BASE);

    //
    // Configure GPIO trigger for ADC
    //
    initADCGPIOTrigger();

    //
    // Initialize results buffer
    //
    for(indexA = 0; indexA < RESULTS_BUFFER_SIZE; indexA++)
    {
        adcA0Results[indexA] = 0;
        adcA1Results[indexA] = 0;
        adcB0Results[indexA] = 0;
        adcB1Results[indexA] = 0;
    }

    indexA = 0;
    indexB = 0;
    bufferFull = 0;

    //
    // Enable ADC interrupt
    //
    Interrupt_enable(INT_ADCA1);
    Interrupt_enable(INT_ADCA2);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Trigger ADC once through setting GPIO32 connected to ADCEXTSOC
    // pin(GPIO33)
    //
    GPIO_setPortPins(GPIO_PORT_B, GPIO_GPBDIR_GPIO32);

    //
    // Loop indefinitely
    //
    while(1)
    {
        countIdle = 0;
        indexA = 0;
        indexB = 0;

        //
        // Wait while ADCINT1 causes ADC conversions which then cause interrupts.
        // When the results buffer is filled, the bufferFull flag will be set.
        //
        while(bufferFull == 0)
        {
            //
            // Incrementing idle counter to get the CPU bandwidth
            //
            countIdle++;
        }

        //
        // Clear the buffer full flag. Add breakpoint at this statement to
        // view ADC results in graph view.
        //
        bufferFull = 0;

//        //
//        // Software breakpoint to view results.
//        // Hit run again to get updated conversions.
//        // Uncomment to halt the execution once buffer is full.
//        //
//        ESTOP0;
    }
}

//
// initADCGPIOTrigger - Configure ADCEXTSOC as ADC GPIO trigger
//
void initADCGPIOTrigger(void)
{
    //
    // Load the output latch
    //
    GPIO_clearPortPins(GPIO_PORT_B, GPIO_GPBDIR_GPIO32);
    GPIO_setDirectionMode(32, GPIO_DIR_MODE_OUT);           // output

    GPIO_setDirectionMode(33, GPIO_DIR_MODE_IN);            // input
    XBAR_setInputPin(INPUTXBAR_BASE, XBAR_INPUT5, 33);
}

//
// configureADC - Write ADC configurations and power up the selected ADC
//                instance
//
void configureADC(uint32_t adcBase)
{
    //
    // Set ADCCLK divider to /4
    //
    ADC_setPrescaler(adcBase, ADC_CLK_DIV_4_0);

    //
    // Set resolution and signal mode (see #defines above) and load
    // corresponding trims.
    //
    ADC_setMode(adcBase, EX_ADC_RESOLUTION, EX_ADC_INPUT_MODE);

    //
    // Set pulse positions at the end of the acquisition window.
    //
    ADC_setInterruptPulseMode(adcBase, ADC_PULSE_END_OF_ACQ_WIN);

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
// Function to configure selected ADC's SOC0 to be triggered by ePWM1.
//
void initADCSOC(uint32_t adcBase)
{
    uint16_t i;

   //
   // Configure SOCs of selected ADC
   // - For 12-bit resolution, a sampling window of 15 (75 ns at a 200MHz
   //   SYSCLK rate) will be used.  For 16-bit resolution, a sampling window
   //   of 64 (320 ns at a 200MHz SYSCLK rate) will be used.
   //

   //
   // ADC channel for SOC0, SOC2, ...,SOC14 = ADCIN0
   // ADC channel for SOC1, SOC3, ...,SOC15 = ADCIN1
   // SOC Trigger = GPIO (for first time triggering)
   // ACQPS = 64 for 16-bit resolution & 15 for 12-bit resolution
   //
   for(i = 0; i < 16; i++)
   {
       ADC_setupSOC(adcBase, (ADC_SOCNumber)i,
                    ADC_TRIGGER_GPIO,
                    ((i % 2 == 0) ? ADC_CH_ADCIN0 : ADC_CH_ADCIN1),
                    ((EX_ADC_RESOLUTION == ADC_RESOLUTION_16BIT) ? 64U : 15U));

       //
       // Set SOC trigger
       //
       ADC_setInterruptSOCTrigger(adcBase, (ADC_SOCNumber)i,
                                  ADC_INT_SOC_TRIGGER_ADCINT1);
   }

    //
    // Set ADCA SOC7 to set the interrupt 2 flag and SOC15 to set interrupt 1
    // flag. Enable the interrupt and make sure its flag is cleared.
    //
    if(adcBase == ADCA_BASE)
    {
        ADC_setInterruptSource(adcBase, ADC_INT_NUMBER2, ADC_SOC_NUMBER7);
        ADC_enableContinuousMode(adcBase, ADC_INT_NUMBER2);
        ADC_enableInterrupt(adcBase, ADC_INT_NUMBER2);
        ADC_clearInterruptStatus(adcBase, ADC_INT_NUMBER2);
    }

    ADC_setInterruptSource(adcBase, ADC_INT_NUMBER1, ADC_SOC_NUMBER15);
    ADC_enableContinuousMode(adcBase, ADC_INT_NUMBER1);
    ADC_enableInterrupt(adcBase, ADC_INT_NUMBER1);
    ADC_clearInterruptStatus(adcBase, ADC_INT_NUMBER1);
}

//
// ADC A Interrupt 2 ISR
//
__interrupt void adcA2ISR(void)
{
    //
    // Take sum of different channels
    //
    sumACh0 = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER0) +
              ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER2) +
              ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER4) +
              ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER6);

    sumBCh0 = ADC_readResult(ADCBRESULT_BASE, ADC_SOC_NUMBER0) +
              ADC_readResult(ADCBRESULT_BASE, ADC_SOC_NUMBER2) +
              ADC_readResult(ADCBRESULT_BASE, ADC_SOC_NUMBER4) +
              ADC_readResult(ADCBRESULT_BASE, ADC_SOC_NUMBER6);

    sumACh1 = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER1) +
              ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER3) +
              ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER5) +
              ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER7);

    sumBCh1 = ADC_readResult(ADCBRESULT_BASE, ADC_SOC_NUMBER1) +
              ADC_readResult(ADCBRESULT_BASE, ADC_SOC_NUMBER3) +
              ADC_readResult(ADCBRESULT_BASE, ADC_SOC_NUMBER5) +
              ADC_readResult(ADCBRESULT_BASE, ADC_SOC_NUMBER7);

    //
    // Acknowledge the interrupt
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP10);
}

//
// ADC A Interrupt 1 ISR
//
__interrupt void adcA1ISR(void)
{
    //
    // Add the latest result to the buffer
    //
    sumACh0 += ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER8)  +
               ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER10) +
               ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER12) +
               ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER14);

    sumBCh0 += ADC_readResult(ADCBRESULT_BASE, ADC_SOC_NUMBER8)  +
               ADC_readResult(ADCBRESULT_BASE, ADC_SOC_NUMBER10) +
               ADC_readResult(ADCBRESULT_BASE, ADC_SOC_NUMBER12) +
               ADC_readResult(ADCBRESULT_BASE, ADC_SOC_NUMBER14);

    sumACh1 += ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER9)  +
               ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER11) +
               ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER13) +
               ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER15);

    sumBCh1 += ADC_readResult(ADCBRESULT_BASE, ADC_SOC_NUMBER9)  +
               ADC_readResult(ADCBRESULT_BASE, ADC_SOC_NUMBER11) +
               ADC_readResult(ADCBRESULT_BASE, ADC_SOC_NUMBER13) +
               ADC_readResult(ADCBRESULT_BASE, ADC_SOC_NUMBER15);

    //
    // Taking average of 8 channels
    //
    averageACh0 = sumACh0 >> 3;
    averageACh1 = sumACh1 >> 3;
    averageBCh0 = sumBCh0 >> 3;
    averageBCh1 = sumBCh1 >> 3;

    adcA0Results[indexA]   = averageACh0;
    adcA1Results[indexA++] = averageACh1;
    adcB0Results[indexB]   = averageBCh0;
    adcB1Results[indexB++] = averageBCh1;

    //
    // Set the bufferFull flag if the buffer is full
    //
    if(RESULTS_BUFFER_SIZE <= indexA)
    {
        bufferFull = 1;
    }

    //
    // Acknowledge the interrupt
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
}

//
// End of file
//
