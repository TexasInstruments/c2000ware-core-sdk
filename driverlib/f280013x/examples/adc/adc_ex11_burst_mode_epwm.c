//#############################################################################
//
// FILE:   adc_ex11_burst_mode_epwm.c
//
// TITLE:  ADC burst mode example
//
//! \addtogroup driver_example_list
//! <h1>ADC Burst Mode</h1>
//!
//! This example sets up ePWM1 to periodically trigger ADCA using burst mode.
//! This allows for different channels to be sampled with each burst.
//!
//! Each burst triggers 3 conversions.  A0 and A1 are part of every burst while
//! the third conversion rotates between A2, A3, and A4.  This allows high
//! importance signals to be sampled at high speed while lower priority signals
//! can be sampled at a lower rate.
//!
//! ADCA Interrupt ISRs are used to read results for ADCA.
//!
//! \b External \b Connections \n
//!  - A0, A1, A2, A3, A4
//!
//! \b Watch \b Variables \n
//! - \b adcAResult0 - Digital representation of the voltage on pin A0
//! - \b adcAResult1 - Digital representation of the voltage on pin A1
//! - \b adcAResult2 - Digital representation of the voltage on pin A2
//! - \b adcAResult3 - Digital representation of the voltage on pin A3
//! - \b adcAResult4 - Digital representation of the voltage on pin A4
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
// Globals
//
uint16_t adcAResult0;
uint16_t adcAResult1;
uint16_t adcAResult2;
uint16_t adcAResult3;
uint16_t adcAResult4;


//
// Function Prototypes
//
void initEPWM();
__interrupt void adcABurstISR(void);

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
    // Set up ADCs:
    // Signal Mode           : single-ended
    // Conversion Resolution : 12-bit;
    //
    // Enable burst mode for SOC7-15 with burst size of 3 with
    // burst mode trigger as EPWM1 SOCA. Select the channels to be
    // converted and configure the S+H duration
    // Burst1: SOC7  (A0) + SOC8  (A1) + SOC9  (A2)
    // Burst2: SOC10 (A0) + SOC11 (A1) + SOC12 (A3)
    // Burst3: SOC13 (A0) + SOC14 (A1) + SOC15 (A4)
    //
    // Register and enable the interrupts:
    // Interrupts that are used in this example are re-mapped to ISR functions
    // found within this file. Each of the 3 interrupts will occur at the end
    // of the 3 different bursts, but all 3 will map to the same ADC result
    // handling ISR
    //
    Board_init();

    //
    // Initialize PWM
    //
    initEPWM();

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
        // ADCA Burst ISR processes each new set of conversions.
        //
    }
    while(1);
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
// ADC A Interrupt Burst Mode ISR
//
__interrupt void adcABurstISR(void)
{
    uint16_t rrPointer;
    ADC_IntNumber burstIntSource;

    //
    //Read the round-robin pointer to determine which burst just completed
    //
    rrPointer = (HWREGH(ADCA_BASE + ADC_O_SOCPRICTL) & 0x03E0) >> 5;
    switch(rrPointer){
        //
        // Burst 1
        //
        case 9:
            adcAResult0 = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER7);
            adcAResult1 = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER8);
            adcAResult2 = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER9);
            burstIntSource = ADC_INT_NUMBER1;
        break;

        //
        // Burst 2
        //
        case 12:
            adcAResult0 = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER10);
            adcAResult1 = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER11);
            adcAResult3 = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER12);
            burstIntSource = ADC_INT_NUMBER2;
        break;

        //
        // Burst 3
        //
        case 15:
            adcAResult0 = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER13);
            adcAResult1 = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER14);
            adcAResult4 = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER15);
            burstIntSource = ADC_INT_NUMBER3;
        break;

        default:
            ESTOP0; //handle error for unexpected RR pointer value
    }

    //
    // Clear the interrupt flag
    //
    ADC_clearInterruptStatus(ADCA_BASE, burstIntSource);

    //
    // Check if overflow has occurred
    //
    if(true == ADC_getInterruptOverflowStatus(ADCA_BASE, burstIntSource))
    {
        ADC_clearInterruptOverflowStatus(ADCA_BASE, burstIntSource);
        ADC_clearInterruptStatus(ADCA_BASE, burstIntSource);
    }

    //
    // Acknowledge the interrupt
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP10);
}

//
// End of file
//
