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
#define DELAY_BUFFER_SIZE 30

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
void configureEPWM(uint32_t epwmBase, uint16_t period);
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
    // initialize program variables
    //
    conversion_count = 0;
    for(delay_index = 0; delay_index < DELAY_BUFFER_SIZE; delay_index++)
    {
        delay[delay_index] = 0;
        conversion[delay_index] = 0;
    }

    //
    // Set up ADCs:
    // Signal Mode           : single-ended
    // Conversion Resolution : 12-bit;
    // Configure ADC SOCs and PPB for delay capture
    // Register and enable the interrupts
    //
    Board_init();

    //
    // Configure the ePWMs to have async. periods
    //
    configureEPWM(EPWM1_BASE, 2048);
    configureEPWM(EPWM2_BASE, 9999);

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
    ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER2);

    //
    // Check if overflow has occurred
    //
    if(true == ADC_getInterruptOverflowStatus(ADCA_BASE, ADC_INT_NUMBER2))
    {
        ADC_clearInterruptOverflowStatus(ADCA_BASE, ADC_INT_NUMBER2);
        ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER2);
    }

    //
    // Acknowledge the interrupt
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP10);
}

//
// End of file
//
