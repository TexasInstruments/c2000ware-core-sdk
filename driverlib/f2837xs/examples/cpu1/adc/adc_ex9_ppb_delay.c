//###########################################################################
//
// FILE:   adc_ex9_ppb_delay.c
//
// TITLE:  ADC delay capture using Post-Processing block.
//
//! \addtogroup driver_example_list
//! <h1> ADC PPB Delay Capture (adc_ppb_delay)</h1>
//!
//! This example demonstrates delay capture using the post-processing block.
//!
//! Two asynchronous ADC triggers are setup:\n
//!  - ePWM1, with period 2048, triggering SOC0 to convert on pin A0\n
//!  - ePWM2, with period 9999, triggering SOC1 to convert on pin A2\n
//!
//! Each conversion generates an ISR at the end of the conversion.  In the
//! ISR for SOC0, a conversion counter is incremented and the PPB is checked
//! to determine if the sample was delayed.\n
//!
//! After the program runs, the memory will contain:\n
//! - \b conversion \b: the sequence of conversions using SOC0 that were delayed
//! - \b delay \b: the corresponding delay of each of the delayed conversions
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
#define DELAY_BUFFER_SIZE 30
//Number of delayed conversions to record
#define EX_ADC_RESOLUTION       12
// 12 for 12-bit conversion resolution, which supports (ADC_MODE_SINGLE_ENDED)
// Sample on single pin (VREFLO is the low reference)
// Or 16 for 16-bit conversion resolution, which supports (ADC_MODE_DIFFERENTIAL)
// Sample on pair of pins (difference between pins is converted, subject to
// common mode voltage requirements; see the device data manual)

//
// Globals
//
uint32_t conversion_count;
uint32_t conversion[DELAY_BUFFER_SIZE];
uint16_t delay[DELAY_BUFFER_SIZE];
volatile uint16_t delay_index;

//
// Functional Prototypes
//
void initADC(void);
void initADCSOC(void);
void configureEPWM(uint32_t epwmBase, uint16_t period);
void configureADCSOC(uint32_t adcBase, uint16_t channel);
__interrupt void adcA1ISR(void);
__interrupt void adcA2ISR(void);

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
    initADC();

    //
    // Configure the ePWMs to have async. periods
    //
    configureEPWM(EPWM1_BASE, 2048);
    configureEPWM(EPWM2_BASE, 9999);

    //
    // Setup the ADC SOCs on ADCA
    //
    initADCSOC();

    //
    // Map ISR functions
    //
    Interrupt_register(INT_ADCA1, &adcA1ISR);
    Interrupt_register(INT_ADCA2, &adcA2ISR);

    //
    // initialize program variables
    //
    conversion_count = 0;
    for(delay_index = 0; delay_index < DELAY_BUFFER_SIZE; delay_index++)
    {
        delay[delay_index] = 0;
        conversion[delay_index] = 0;
    }

    //
    // Enable specific PIE & CPU interrupts:
    //
    Interrupt_enable(INT_ADCA1);
    Interrupt_enable(INT_ADCA2);

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
    // Enable SOCA triggers
    //
    EPWM_enableADCTrigger(EPWM1_BASE, EPWM_SOC_A);
    EPWM_enableADCTrigger(EPWM2_BASE, EPWM_SOC_A);

    //
    // Unfreeze epwm counters to count-up
    //
    EPWM_setTimeBaseCounterMode(EPWM1_BASE, EPWM_COUNTER_MODE_UP);
    EPWM_setTimeBaseCounterMode(EPWM2_BASE, EPWM_COUNTER_MODE_UP);

    //
    // Take conversions indefinitely in loop
    //
    do
    {
        delay_index = 0;
        //
        // Enable SOCA triggers
        //
        EPWM_enableADCTrigger(EPWM1_BASE, EPWM_SOC_A);
        EPWM_enableADCTrigger(EPWM2_BASE, EPWM_SOC_A);

        //
        // Unfreeze epwm counters to count-up
        //
        EPWM_setTimeBaseCounterMode(EPWM1_BASE, EPWM_COUNTER_MODE_UP);
        EPWM_setTimeBaseCounterMode(EPWM2_BASE, EPWM_COUNTER_MODE_UP);

        //
        //wait for list of delayed conversions to fill via interrupts
        //
        while(DELAY_BUFFER_SIZE > delay_index){}

        //
        // Stop ePWMs, disabling SOCAs and freezing the counters
        //
        EPWM_disableADCTrigger(EPWM1_BASE, EPWM_SOC_A);
        EPWM_disableADCTrigger(EPWM2_BASE, EPWM_SOC_A);
        EPWM_setTimeBaseCounterMode(EPWM1_BASE, EPWM_COUNTER_MODE_STOP_FREEZE);
        EPWM_setTimeBaseCounterMode(EPWM2_BASE, EPWM_COUNTER_MODE_STOP_FREEZE);

        //
        //software breakpoint
        //
        ESTOP0;

        //
        //conversion[] will show which conversions were delayed
        //delay[] will show how long each conversion was delayed
        //conversion_count will show total number of conversions
        //conversion_count - DELAY_BUFFER_SIZE is the number of samples
        //    that started immediately without any delay
        //
    }
    while(1);
}

//
// Function to configure and power up ADCA.
//
void initADC(void)
{
    
    //
    // Set ADCDLK divider to /4
    //
    ADC_setPrescaler(ADCA_BASE, ADC_CLK_DIV_4_0);

    //
    // Set resolution and signal mode (see #defines above) and load
    // corresponding trims.
    //
#if(EX_ADC_RESOLUTION == 12)
    ADC_setMode(ADCA_BASE, ADC_RESOLUTION_12BIT, ADC_MODE_SINGLE_ENDED);
#elif(EX_ADC_RESOLUTION == 16)
    ADC_setMode(ADCA_BASE, ADC_RESOLUTION_16BIT, ADC_MODE_DIFFERENTIAL);
#endif

    //
    // Set pulse positions to late
    //
    ADC_setInterruptPulseMode(ADCA_BASE, ADC_PULSE_END_OF_CONV);

    //
    // Power up the ADC and then delay for 1 ms
    //
    ADC_enableConverter(ADCA_BASE);
    DEVICE_DELAY_US(1000);
}

//
// Function to configure ADCA's SOC0 to be triggered by ePWM1 and SOC1 to be
// triggered by ePWM2.
//
void initADCSOC(void)
{
    //
    // Configure SOC0 of ADCA to convert pin A0 and SOC1 to convert A2. The
    // EPWM1SOCA signal will be the trigger for SOC0 and EPWM2SOCA will trigger
    // SOC1.
    // - For 12-bit resolution, a sampling window of 15 (75 ns at a 200MHz
    //   SYSCLK rate) will be used.  For 16-bit resolution, a sampling window
    //   of 64 (320 ns at a 200MHz SYSCLK rate) will be used.
    // - NOTE: A longer sampling window will be required if the ADC driving
    //   source is less than ideal (an ideal source would be a high bandwidth
    //   op-amp with a small series resistance). See TI application report
    //   SPRACT6 for guidance on ADC driver design.
    //

#if(EX_ADC_RESOLUTION == 12)
    ADC_setupSOC(ADCA_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_EPWM1_SOCA,
                 ADC_CH_ADCIN0, 15);
    ADC_setupSOC(ADCA_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_EPWM2_SOCA,
                 ADC_CH_ADCIN0, 15);
#elif(EX_ADC_RESOLUTION == 16)
    ADC_setupSOC(ADCA_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_EPWM1_SOCA,
                 ADC_CH_ADCIN0, 64);
    ADC_setupSOC(ADCA_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_EPWM2_SOCA,
                 ADC_CH_ADCIN0, 64);
#endif

    //
    // Set SOC0 to set the interrupt 1 flag and SOC1 to set interrupt
    // 2 flag. Enable the interrupts and make sure the flags are cleared.
    //
    ADC_setInterruptSource(ADCA_BASE, ADC_INT_NUMBER1, ADC_SOC_NUMBER0);
    ADC_setInterruptSource(ADCA_BASE, ADC_INT_NUMBER2, ADC_SOC_NUMBER1);
    ADC_enableInterrupt(ADCA_BASE, ADC_INT_NUMBER1);
    ADC_enableInterrupt(ADCA_BASE, ADC_INT_NUMBER1);
    ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1);
    ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER2);

    //
    // Asscociate PPB1 with SOC0.  This will allow delay detection for
    // this SOC.
    //
    ADC_setupPPB(ADCA_BASE, ADC_PPB_NUMBER1, ADC_SOC_NUMBER0);
}

//
// configureEPWM - Setup SOC and compare values for EPWM and set specified 
// period.
//
void configureEPWM(uint32_t epwmBase, uint16_t period)
{
    //
    // Disable SOCA trigger
    //
    EPWM_disableADCTrigger(epwmBase, EPWM_SOC_A);

    //
    // Trigger SOCA on CMPA up-count
    //
    EPWM_setADCTriggerSource(epwmBase, EPWM_SOC_A, EPWM_SOC_TBCTR_U_CMPA);

    //
    // Generate pulse on 1st event
    //
    EPWM_setADCTriggerEventPrescale(epwmBase, EPWM_SOC_A, 1U);

    //
    // Set compare A value to approximately half the period
    //
    EPWM_setCounterCompareValue(epwmBase, EPWM_COUNTER_COMPARE_A, period/2);

    //
    // Set period as specified
    //
    EPWM_setTimeBasePeriod(epwmBase, period);

    //
    // Set the local ePWM module clock divider to /1
    //
    EPWM_setClockPrescaler(epwmBase,
                           EPWM_CLOCK_DIVIDER_1,
                           EPWM_HSCLOCK_DIVIDER_1);

    //
    // Freeze counter
    //
    EPWM_setTimeBaseCounterMode(epwmBase, EPWM_COUNTER_MODE_STOP_FREEZE);
}

//
// configurePPB1Limits - Configure high and low limits for ADCPPB
//
void configurePPB1Limits(uint16_t soc, uint16_t limitHigh, uint16_t limitLow)
{
    //
    // Asscociate PPB1 with soc
    //
    ADC_setupPPB(ADCA_BASE, ADC_PPB_NUMBER1, (ADC_SOCNumber)soc);

    //
    // Set high and low limits
    //
    ADC_setPPBTripLimits(ADCA_BASE, ADC_PPB_NUMBER1, limitHigh, limitLow);

    //
    // Enable high and low limit events to generate interrupt
    //
    ADC_enablePPBEventInterrupt(ADCA_BASE, ADC_PPB_NUMBER1,
                                (ADC_EVT_TRIPHI | ADC_EVT_TRIPLO));
}

//
// configureADCSOC - Setup ADC EPWM channel and trigger settings
//
void configureADCSOC(uint32_t adcBase, uint16_t channel)
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

    //
    // Select the channels to convert and end of conversion flag
    // ADCA
    //
    ADC_setupSOC(adcBase, ADC_SOC_NUMBER0, ADC_TRIGGER_EPWM1_SOCA,
                 (ADC_Channel)channel, acqps);

    //
    // Configure source as EOC1, clear & enable the interrupt
    //
    ADC_setInterruptSource(adcBase, ADC_INT_NUMBER1, ADC_SOC_NUMBER0);
    ADC_clearInterruptStatus(adcBase, ADC_INT_NUMBER1);
    ADC_enableInterrupt(adcBase, ADC_INT_NUMBER1);
}

//
// ADC A Interrupt 1 ISR - check for delayed conversions
//
__interrupt void adcA1ISR(void)
{
    //
    //DLYSTAMP will read 2 if the sample was not delayed
    //
    if(2 < ADC_getPPBDelayTimeStamp(ADCA_BASE, ADC_PPB_NUMBER1))
    {
        //
        //if DLYSTAMP > 2, then the sample was delayed by (DLYSTAMP - 2)
        //cycles (SYSCLK)
        //
        conversion[delay_index] = conversion_count;
        delay[delay_index] = ADC_getPPBDelayTimeStamp(ADCA_BASE, ADC_PPB_NUMBER1) - 2;
        delay_index++;

        //
        //corrective action(s) for delayed sample can occur here
        //...
        //
    }

    //
    //read ADC sample here
    //...
    //

    conversion_count++;

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
// ADC A Interrupt 2 ISR - dummy ISR.  Occurs async. to ADC A ISR 1.
//
__interrupt void adcA2ISR(void)
{
    //
    //read ADC sample here
    //...
    //

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
