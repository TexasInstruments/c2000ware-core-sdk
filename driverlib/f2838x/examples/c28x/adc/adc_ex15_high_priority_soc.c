//###########################################################################
//
// FILE:   adc_ex15_high_priority_soc.c
//
// TITLE:  ADC High Priority SOC Example.
//
//! \addtogroup driver_example_list
//! <h1> ADC High Priority SOC (adc_high_priority_soc)</h1>
//!
//! This example demonstrates configuration of ADC high priority SOCs in
//! order to sample fastest control loop signals with high priority while
//! low priority signals are sampled with default round robin priority.
//!
//! ADC PPB block is configured to capture delay between SOC trigger
//! and actual start of the SOC sampling in order to quantify the jitters
//! in sampling high priority signals due to low priority signals. The
//! delay in processing an SOC is captured in ADCPPBxSTAMP.DLYSTAMP
//! register field and the total delay in sampling an SOC is equal to
//! (DLYSTAMP - 2) cycles. In an optimal design the high priority SOC
//! is expected to have less delay between SOC trigger and actual start
//! of the sample.
//!
//! In this example ADCA, ADCB and ADCD are configured to sample both
//! high and low priority signals. SOC0-3 are configured as high priority
//! SOCs while rest are configured with default round-robin priority. ADCA
//! SOC0-3 are configured as high priority SOCs sampling channels A0-A3,
//! ADCB SOC0-1 are configured as high priority SOCs sampling channels
//! B0-B1 and ADCD SOC0-1 are configured as high priority SOCs sampling
//! channels D0-D1. For sampling low priority signals SOC4-SOC5 are
//! configured sampling channel 4 and channel 13 respectively for ADCA
//! and channel 4 and 5 for ADCB and ADCD. For ADCA, channel 13 is
//! connected to internal temperature sensor output and hence no signal
//! needs to be connected to channel A13. High priority SOC results are
//! read in ADCINT1 ISR while low priority SOC results are read in idle
//! loop.
//!
//! This example has two modes of operation as follows. Desired mode
//! can be selected by configuring the EX_ADC_LP_SOC_TRIGGER macro
//! accordingly.
//! Mode 0: ADCINT as round robin SOC trigger
//! Mode 1: EPWM2 as round robin SOC trigger
//!
//! In mode 0, EPWM1 is configured as trigger for high priority SOCs while
//! ADCINT1 is configured as low priority SOC trigger. ADCINT1 is configured
//! to be triggered on completion of SOC1 conversion which in turn trigger
//! low priority SOCs 4 and 5 and ADCINT2 is configured to be triggered on
//! completion of SOC5. ADC result for high priority SOCs are read in ADCINT
//! ISR while low priority SOC results are read in idle loop. ADCINT3 is
//! configured to be triggered on completion of SOC3 and hence SOC2-SOC3
//! results for ADCA are read post checking if the conversion is complete
//! in ADCINT1 ISR.
//!
//! In mode 0, SOC0-SOC1 for all ADCs will experience minimal delay(0 and 1
//! conversions) in processing due to the high priority configuration. For
//! ADCA, SOC4-SOC5 are triggered when SOC2-SOC3 conversion is ongoing, hence
//! SOC4-SOC5 will see some delay(2 and 3 conversions) in processing as
//! expected. For ADCB and ADCD, SOC4-SOC5 will see minimal delay (0 and 1
//! conversions) in processing as expected.
//!
//! In mode 1, EPWM1 is configured as trigger for high priority SOCs while
//! EPWM2 is configured as low priority SOC trigger. ADCINT1 is configured
//! to be triggered on completion of SOC3 conversion and ADC result for high
//! priority SOCs are read in the ADCINT ISR. Low priority SOCs 4 and 5 are
//! triggered through EPWM2 and ADCINT2 is configured to be triggered on
//! completion of SOC5. The result for low priority SOCs are read in background
//! loop. Since, SOC4-5 are triggered post SOC2-3 conversion(due to configured
//! EPWM1 and EPWM2 trigger frequency and duty), SOC4-SOC5 will have minimal
//! delay(0 and 1 conversions respectively) in SOC processing as expected.
//!
//! Optimization Level: Example is expected to run with opt level = O2.
//!
//! To view ADC results, put breakpoint at the statement where indexB  is
//! reset to zero in idle loop.
//!
//! \b External \b Connections \n
//!  - A0-A4, B0-B1, B4-B5, D0-D1 and D4-D5 pins should be connected to signals
//!    to be converted.
//!
//!  - Observe ePWM1, ePWM2 signals on oscilloscope
//!
//! \b Watch \b Variables \n
//!  ADC Results:
//!  - adcA0Results - adcA4Results - ADC result of channels A0-A4
//!  - adcA13Results - ADC result of channels A13(Temp Sensor output)
//!  - adcB0Results - adcB1Results - ADC result of channels B0-B1
//!  - adcB4Results - ADC result of channel B4
//!  - adcB5Results - ADC result of channel B5
//!  - adcD0Results - adcD1Results - ADC result of channels D0-D1
//!  - adcD4Results - ADC result of channel D4
//!  - adcD5Results - ADC result of channel D5
//!
//!  SOC conversion delays:
//!  - delaySocA0 - Delay in sampling ADCA SOC0
//!  - delaySocA3 - Delay in sampling ADCA SOC3
//!  - delaySocA4-delaySocA5 - Delay in sampling ADCA SOC4-SOC5
//!  - delaySocB0-delaySocB1 - Delay in sampling ADCB SOC0-SOC1
//!  - delaySocB4-delaySocB5 - Delay in sampling ADCB SOC4-SOC5
//!  - delaySocD0-delaySocD1 - Delay in sampling ADCD SOC0-SOC1
//!  - delaySocD4-delaySocD5 - Delay in sampling ADCD SOC4-SOC5
//!
//
//###########################################################################
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
//###########################################################################

//
// Included Files
//
#include "driverlib.h"
#include "device.h"

//
// Defines
//

// Uncomment to enable profiling
//#define ENABLE_PROFILING

//
// Macro for defining ADC resolution
//
#define EX_ADC_RESOLUTION       12U

//
// Macro to define acquisition window duration based on resolution.
// This can vary as per application hardware. In this example, a
// sampling window of 15 (75 ns at a 200MHz SYSCLK rate) will be used
// for 12-bit resolution while a sampling window of 64 (320 ns at a
// 200MHz SYSCLK rate) will be used for 16-bit resolution.
//
#define EX_ACQ_WIN_12_BIT       15U
#define EX_ACQ_WIN_16_BIT       65U

//
// Macro to define ADC result buffer size
//
#define RESULTS_BUFFER_SIZE     50U

//
// Macro to define ADC Low Priority SOC trigger
// if EX_ADC_LP_SOC_TRIGGER == 0U, low priority SOC trigger = ADCINT1
// if EX_ADC_LP_SOC_TRIGGER == 1U, low priority SOC trigger = EPWM2
//
#define EX_ADC_LP_SOC_TRIGGER    0U

//
// Globals
//
volatile uint16_t indexA = 0, indexB = 0;   // Index into result buffer
volatile uint16_t bufferFull;               // Flag to indicate buffer is full

//
// Globals for capturing SOC delay
//
volatile uint16_t delaySocA0 = 0, delaySocA3 = 0, delaySocA4 = 0, delaySocA5 = 0;
volatile uint16_t delaySocB0 = 0, delaySocB1 = 0, delaySocB4 = 0, delaySocB5 = 0;
volatile uint16_t delaySocD0 = 0, delaySocD1 = 0, delaySocD4 = 0, delaySocD5 = 0;

//
// Globals for capturing ADC results
//
uint16_t adcA0Results[RESULTS_BUFFER_SIZE]  = {0}; // ADC result buffer for Ch A0
uint16_t adcB0Results[RESULTS_BUFFER_SIZE]  = {0}; // ADC result buffer for Ch B0
uint16_t adcD0Results[RESULTS_BUFFER_SIZE]  = {0}; // ADC result buffer for Ch D0
uint16_t adcA1Results[RESULTS_BUFFER_SIZE]  = {0}; // ADC result buffer for Ch A1
uint16_t adcB1Results[RESULTS_BUFFER_SIZE]  = {0}; // ADC result buffer for Ch B1
uint16_t adcD1Results[RESULTS_BUFFER_SIZE]  = {0}; // ADC result buffer for Ch D1
uint16_t adcA2Results[RESULTS_BUFFER_SIZE]  = {0}; // ADC result buffer for Ch A2
uint16_t adcA3Results[RESULTS_BUFFER_SIZE]  = {0}; // ADC result buffer for Ch A3
uint16_t adcA4Results[RESULTS_BUFFER_SIZE]  = {0}; // ADC result buffer for Ch A4
uint16_t adcB4Results[RESULTS_BUFFER_SIZE]  = {0}; // ADC result buffer for Ch B4
uint16_t adcD4Results[RESULTS_BUFFER_SIZE]  = {0}; // ADC result buffer for Ch D4
uint16_t adcA13Results[RESULTS_BUFFER_SIZE] = {0}; // ADC result buffer for Ch A13
uint16_t adcB5Results[RESULTS_BUFFER_SIZE]  = {0}; // ADC result buffer for Ch B5
uint16_t adcD5Results[RESULTS_BUFFER_SIZE]  = {0}; // ADC result buffer for Ch D5

//
// Characteristics of PWM triggers
// EPWM1 - frequency -> 400kHz, dutyA -> 50%, dutyB -> 50%, ePWM1B - inverted
//
EPWM_SignalParams pwmSignal1 =
            {400000, 0.5f, 0.5f, true, DEVICE_SYSCLK_FREQ, SYSCTL_EPWMCLK_DIV_2,
            EPWM_COUNTER_MODE_UP, EPWM_CLOCK_DIVIDER_1,
            EPWM_HSCLOCK_DIVIDER_1};

#if(EX_ADC_LP_SOC_TRIGGER == 1)
//
// EPWM2 - frequency -> 100kHz, dutyA -> 50%, dutyB -> 50%, ePWM2B - inverted
//
EPWM_SignalParams pwmSignal2 =
            {100000, 0.5f, 0.5f, true, DEVICE_SYSCLK_FREQ, SYSCTL_EPWMCLK_DIV_2,
            EPWM_COUNTER_MODE_UP, EPWM_CLOCK_DIVIDER_1,
            EPWM_HSCLOCK_DIVIDER_1};
#endif

//
// Functional Prototypes
//

//
// ADC configuration related APIs
//
void configureADC(uint32_t adcBase);
void initADCSOC(uint32_t adcBase);
void initADCPPB(void);

//
// EPWM configuration related APIs
//
void initEPWMGPIO(void);

#ifdef ENABLE_PROFILING
void setupProfileGpio(void);
#endif

//
// ADC ISR defined as high priority interrupt
//
__interrupt void adcA1ISR(void);
#pragma CODE_SECTION(adcA1ISR, ".TI.ramfunc")
#pragma INTERRUPT (adcA1ISR, HPI)

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

#ifdef ENABLE_PROFILING
    //
    // Setup profiling GPIO
    //
    setupProfileGpio();
#endif

    //
    // For this case just init GPIO pins for ePWM1, ePWM2, ePWM3
    //
    initEPWMGPIO();

    //
    // Configure the ADC and power it up
    //
    configureADC(ADCA_BASE);
    configureADC(ADCB_BASE);
    configureADC(ADCD_BASE);

    //
    // Disable sync(Freeze clock to PWM as well)
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Configuring ePWM modules for desired frequency and duty
    //
    EPWM_configureSignal(EPWM1_BASE, &pwmSignal1);
    EPWM_setTimeBaseCounterMode(EPWM1_BASE, EPWM_COUNTER_MODE_STOP_FREEZE);
    EPWM_disableADCTrigger(EPWM1_BASE, EPWM_SOC_A);

#if(EX_ADC_LP_SOC_TRIGGER == 1)
    EPWM_configureSignal(EPWM2_BASE, &pwmSignal2);
    EPWM_setTimeBaseCounterMode(EPWM2_BASE, EPWM_COUNTER_MODE_STOP_FREEZE);
    EPWM_disableADCTrigger(EPWM2_BASE, EPWM_SOC_A);
#endif

    //
    // Setup the ADC SOCs
    //
    initADCSOC(ADCA_BASE);
    initADCSOC(ADCB_BASE);
    initADCSOC(ADCD_BASE);

    //
    // Configure ADC PPB for delay capture
    //
    initADCPPB();

    //
    // Enable the temperature sensor and give it 500 us to power up
    //
    ASysCtl_enableTemperatureSensor();
    DEVICE_DELAY_US(500);

    //
    // Configure the SOC to occur on the first up-count event
    //
    EPWM_setADCTriggerSource(EPWM1_BASE, EPWM_SOC_A, EPWM_SOC_TBCTR_U_CMPA);
    EPWM_setADCTriggerEventPrescale(EPWM1_BASE, EPWM_SOC_A, 1);
    EPWM_enableADCTrigger(EPWM1_BASE, EPWM_SOC_A);
    EPWM_setTimeBaseCounterMode(EPWM1_BASE, EPWM_COUNTER_MODE_UP);

#if(EX_ADC_LP_SOC_TRIGGER == 1)
    //
    // Configure the SOC to occur on the first up-count event
    //
    EPWM_setADCTriggerSource(EPWM2_BASE, EPWM_SOC_A, EPWM_SOC_TBCTR_U_CMPA);
    EPWM_setADCTriggerEventPrescale(EPWM2_BASE, EPWM_SOC_A, 1);
    EPWM_enableADCTrigger(EPWM2_BASE, EPWM_SOC_A);
    EPWM_setTimeBaseCounterMode(EPWM2_BASE, EPWM_COUNTER_MODE_UP);
#endif

    //
    // Enable ADC interrupt
    //
    Interrupt_enable(INT_ADCA1);

    //
    // Enable global Interrupts and higher priority real-time debug events:
    //
    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global realtime interrupt DBGM

    //
    // Start ePWM:
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Loop indefinitely:
    //
    while(1)
    {
        //
        // Wait for ADCA to complete conversion of low priority SOCs,
        // then acknowledge flag
        //
        while(ADC_getInterruptStatus(ADCA_BASE, ADC_INT_NUMBER2) == false)
        {
        }

        ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER2);
        ADC_clearInterruptStatus(ADCB_BASE, ADC_INT_NUMBER2);
        ADC_clearInterruptStatus(ADCD_BASE, ADC_INT_NUMBER2);

        //
        // Capture delays for low priority SOCs
        //
        delaySocA4 = ADC_getPPBDelayTimeStamp(ADCA_BASE, ADC_PPB_NUMBER3);
        delaySocA5 = ADC_getPPBDelayTimeStamp(ADCA_BASE, ADC_PPB_NUMBER4);

        delaySocB4 = ADC_getPPBDelayTimeStamp(ADCB_BASE, ADC_PPB_NUMBER3);
        delaySocB5 = ADC_getPPBDelayTimeStamp(ADCB_BASE, ADC_PPB_NUMBER4);

        delaySocD4 = ADC_getPPBDelayTimeStamp(ADCD_BASE, ADC_PPB_NUMBER3);
        delaySocD5 = ADC_getPPBDelayTimeStamp(ADCD_BASE, ADC_PPB_NUMBER4);

        //
        // Read low priority ADC signals in background loop
        //
        adcA4Results[indexB]   = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER4);
        adcB4Results[indexB]   = ADC_readResult(ADCBRESULT_BASE, ADC_SOC_NUMBER4);
        adcD4Results[indexB]   = ADC_readResult(ADCDRESULT_BASE, ADC_SOC_NUMBER4);

        adcA13Results[indexB]  = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER5);
        adcB5Results[indexB]   = ADC_readResult(ADCBRESULT_BASE, ADC_SOC_NUMBER5);
        adcD5Results[indexB++] = ADC_readResult(ADCDRESULT_BASE, ADC_SOC_NUMBER5);

        if(indexB == RESULTS_BUFFER_SIZE)
        {
            //
            // Reset the index on buffer full condition. Put breakpoint on below
            // statement to view ADC results on graph window.
            //
            indexB = 0U;
        }
    }
}

//
// configureADC - Write ADC configurations and power up the desired ADC instance
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
// initADCSOC - Function to configure ADC SOCs as per application requirement
//
void initADCSOC(uint32_t adcBase)
{
    uint16_t i;

    //
    // Set SOC priority- SOC0-SOC3 are high priority SOCs and SOC4-SOC15
    // would have round-robin priority
    //
    ADC_setSOCPriority(adcBase, ADC_PRI_THRU_SOC3_HIPRI);

    //
    // Configure EPWM1 as SOC0-SOC1 trigger
    //
    for(i = 0; i < 2; i++)
    {
       ADC_setupSOC(adcBase, (ADC_SOCNumber)i,
                    ADC_TRIGGER_EPWM1_SOCA,
                    (ADC_Channel)i,
                    ((EX_ADC_RESOLUTION == ADC_RESOLUTION_16BIT) ?
                     EX_ACQ_WIN_16_BIT : EX_ACQ_WIN_12_BIT));
    }

    if(adcBase == ADCA_BASE)
    {
        //
        // Configure EPWM1 as SOC2-SOC3 trigger
        //
        for(i = 2; i < 4; i++)
        {
           ADC_setupSOC(adcBase, (ADC_SOCNumber)i,
                        ADC_TRIGGER_EPWM1_SOCA,
                        (ADC_Channel)i,
                        ((EX_ADC_RESOLUTION == ADC_RESOLUTION_16BIT) ?
                         EX_ACQ_WIN_16_BIT : EX_ACQ_WIN_12_BIT));
        }
    }

#if(EX_ADC_LP_SOC_TRIGGER == 1)
    //
    // Configuration for EPWM trigger for low priority SOCs
    //

    //
    // Configure EPWM2 as SOC4-SOC5 trigger. Configure SOC5 to sample
    // channel 13. For ADCA it is temperature sensor output
    //
    ADC_setupSOC(adcBase, ADC_SOC_NUMBER4, ADC_TRIGGER_EPWM2_SOCA,
                 ADC_CH_ADCIN4, ((EX_ADC_RESOLUTION == ADC_RESOLUTION_16BIT) ?
                                 EX_ACQ_WIN_16_BIT : EX_ACQ_WIN_12_BIT));

    if(adcBase == ADCA_BASE)
    {
        ADC_setupSOC(adcBase, ADC_SOC_NUMBER5, ADC_TRIGGER_EPWM2_SOCA,
                        ADC_CH_ADCIN13, 140);
    }
    else
    {
        ADC_setupSOC(adcBase, ADC_SOC_NUMBER5, ADC_TRIGGER_EPWM2_SOCA,
                     ADC_CH_ADCIN5, 140);

    }

    //
    // Set ADCA SOC3 to set the interrupt 1 flag.
    //
    ADC_setInterruptSource(adcBase, ADC_INT_NUMBER1, ADC_SOC_NUMBER3);

#elif(EX_ADC_LP_SOC_TRIGGER == 0)
    //
    // Configuration for ADCINT1 Trigger for low priority SOCs
    //

    //
    // Configure SOC4-SOC5. Configure SOC5 to sample channel 13. For ADCA it
    // is temperature sensor output
    //
    ADC_setupSOC(adcBase, ADC_SOC_NUMBER4, ADC_TRIGGER_SW_ONLY,
                 ADC_CH_ADCIN4, ((EX_ADC_RESOLUTION == ADC_RESOLUTION_16BIT) ?
                                 EX_ACQ_WIN_16_BIT : EX_ACQ_WIN_12_BIT));

    if(adcBase == ADCA_BASE)
    {
        ADC_setupSOC(adcBase, ADC_SOC_NUMBER5, ADC_TRIGGER_SW_ONLY,
                     ADC_CH_ADCIN13, 140);
    }
    else
    {
        ADC_setupSOC(adcBase, ADC_SOC_NUMBER5, ADC_TRIGGER_SW_ONLY,
                     ADC_CH_ADCIN5, 140);
    }

    //
    // Configure ADCINT1 as SOC4-SOC5 trigger
    //
    for(i = 4; i < 6; i++)
    {
        //
        // Set interrupt SOC trigger
        //
        ADC_setInterruptSOCTrigger(adcBase, (ADC_SOCNumber)i,
                                   ADC_INT_SOC_TRIGGER_ADCINT1);
    }


    if(adcBase == ADCA_BASE)
    {
        //
        // Set ADCA SOC3 to set the interrupt 3 flag. Enable the interrupt,
        // and make sure its flag is cleared.
        //
        ADC_setInterruptSource(adcBase, ADC_INT_NUMBER3, ADC_SOC_NUMBER3);
        ADC_enableInterrupt(adcBase, ADC_INT_NUMBER3);
        ADC_clearInterruptStatus(adcBase, ADC_INT_NUMBER3);
    }

    //
    // Set ADCA SOC1 to set the interrupt 1 flag. Enable the interrupt,
    // continuous interrupt mode and make sure its flag is cleared.
    //
    ADC_setInterruptSource(adcBase, ADC_INT_NUMBER1, ADC_SOC_NUMBER1);

#endif

    //
    // Enable the ADCINT1 interrupt, continuous interrupt mode
    // and make sure its flag is cleared.
    //
    ADC_enableContinuousMode(adcBase, ADC_INT_NUMBER1);
    ADC_enableInterrupt(adcBase, ADC_INT_NUMBER1);
    ADC_clearInterruptStatus(adcBase, ADC_INT_NUMBER1);

    //
    // Set ADC SOC5 to set the interrupt 2 flag. Enable the interrupt
    // and make sure its flag is cleared.
    //
    ADC_setInterruptSource(adcBase, ADC_INT_NUMBER2, ADC_SOC_NUMBER5);
    ADC_enableInterrupt(adcBase, ADC_INT_NUMBER2);
    ADC_clearInterruptStatus(adcBase, ADC_INT_NUMBER2);
}

//
// initADCPPB - Function to configure ADC PPBs as per application requirement
//
void initADCPPB(void)
{
    //
    // PPB configuration for ADCA
    //
    ADC_setupPPB(ADCA_BASE, ADC_PPB_NUMBER1, ADC_SOC_NUMBER0);
    ADC_setupPPB(ADCA_BASE, ADC_PPB_NUMBER2, ADC_SOC_NUMBER3);
    ADC_setupPPB(ADCA_BASE, ADC_PPB_NUMBER3, ADC_SOC_NUMBER4);
    ADC_setupPPB(ADCA_BASE, ADC_PPB_NUMBER4, ADC_SOC_NUMBER5);

    //
    // PPB configuration for ADCB
    //
    ADC_setupPPB(ADCB_BASE, ADC_PPB_NUMBER1, ADC_SOC_NUMBER0);
    ADC_setupPPB(ADCB_BASE, ADC_PPB_NUMBER2, ADC_SOC_NUMBER1);
    ADC_setupPPB(ADCB_BASE, ADC_PPB_NUMBER3, ADC_SOC_NUMBER4);
    ADC_setupPPB(ADCB_BASE, ADC_PPB_NUMBER4, ADC_SOC_NUMBER5);

    //
    // PPB configuration for ADCD
    //
    ADC_setupPPB(ADCD_BASE, ADC_PPB_NUMBER1, ADC_SOC_NUMBER0);
    ADC_setupPPB(ADCD_BASE, ADC_PPB_NUMBER2, ADC_SOC_NUMBER1);
    ADC_setupPPB(ADCD_BASE, ADC_PPB_NUMBER3, ADC_SOC_NUMBER4);
    ADC_setupPPB(ADCD_BASE, ADC_PPB_NUMBER4, ADC_SOC_NUMBER5);
}

//
// adcA1ISR - ADC A Interrupt 1 ISR
//
__interrupt void adcA1ISR(void)
{
#ifdef ENABLE_PROFILING
    //
    // Setting Profiling GPIO12 : Takes 3 cycles
    //
    HWREG(GPIODATA_BASE  + GPIO_O_GPASET) = 0x1000;
#endif

    //
    // Read SOC delays
    //
    delaySocA0  = ADC_getPPBDelayTimeStamp(ADCA_BASE, ADC_PPB_NUMBER1);
    delaySocB0  = ADC_getPPBDelayTimeStamp(ADCB_BASE, ADC_PPB_NUMBER1);
    delaySocB1  = ADC_getPPBDelayTimeStamp(ADCB_BASE, ADC_PPB_NUMBER2);
    delaySocD0  = ADC_getPPBDelayTimeStamp(ADCD_BASE, ADC_PPB_NUMBER1);
    delaySocD1  = ADC_getPPBDelayTimeStamp(ADCD_BASE, ADC_PPB_NUMBER2);

    //
    // Add the latest ADC result of high priority signals to the buffer
    //
    adcA0Results[indexA]   = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER0);
    adcB0Results[indexA]   = ADC_readResult(ADCBRESULT_BASE, ADC_SOC_NUMBER0);
    adcD0Results[indexA]   = ADC_readResult(ADCDRESULT_BASE, ADC_SOC_NUMBER0);
    adcA1Results[indexA]   = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER1);
    adcB1Results[indexA]   = ADC_readResult(ADCBRESULT_BASE, ADC_SOC_NUMBER1);
    adcD1Results[indexA]   = ADC_readResult(ADCDRESULT_BASE, ADC_SOC_NUMBER1);

#if(EX_ADC_LP_SOC_TRIGGER == 0)
    //
    // Wait for ADCA to complete conversion of SOC2-SOC3, then acknowledge
    // flag
    //
    while(ADC_getInterruptStatus(ADCA_BASE, ADC_INT_NUMBER3) == false)
    {
    }

    ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER3);
#endif

    //
    // Read ADCA SOC2-SOC3 results post checking the ADCINT3 flag
    //
    adcA2Results[indexA]   = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER2);
    adcA3Results[indexA++] = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER3);

    //
    // Read delay for ADCA SOC3
    //
    delaySocA3  = ADC_getPPBDelayTimeStamp(ADCA_BASE, ADC_PPB_NUMBER2);

    if(RESULTS_BUFFER_SIZE <= indexA)
    {
        //
        // Reset the index when buffer is full.
        //
        indexA = 0;
    }

    //
    // Acknowledge the interrupt
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);

#ifdef ENABLE_PROFILING
    //
    // Resetting Profiling GPIO12
    //
    HWREG(GPIODATA_BASE  + GPIO_O_GPACLEAR) = 0x1000;
#endif
}

//
// initEPWMGPIO - Configure ePWM1-ePWM2 GPIO
//
void initEPWMGPIO(void)
{
    //
    // Disable pull up on GPIO0-1 and configure them as PWMs
    //
    GPIO_setPadConfig(0, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_0_EPWM1A);

    GPIO_setPadConfig(1, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_1_EPWM1B);

#if(EX_ADC_LP_SOC_TRIGGER == 1)
    //
    // Disable pull up on GPIO2-3 and configure them as PWMs
    //
    GPIO_setPadConfig(2, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_2_EPWM2A);

    GPIO_setPadConfig(3, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_3_EPWM2B);
#endif
}

#ifdef ENABLE_PROFILING
//
// setupProfileGpio - Configure profiling GPIO
//
void setupProfileGpio(void)
{
    GPIO_setDirectionMode(12,GPIO_DIR_MODE_OUT);
    GPIO_setQualificationMode(12,GPIO_QUAL_SYNC);
    GPIO_setPinConfig(GPIO_12_GPIO12);
    GPIO_writePin(12,0);
}
#endif

//
// End of file
//
