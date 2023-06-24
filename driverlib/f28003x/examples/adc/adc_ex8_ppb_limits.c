//###########################################################################
//
// FILE:   adc_ex8_ppb_limits.c
//
// TITLE:  ADC limits check using post-processing block for f2838x.
//
//! \addtogroup driver_example_list
//! <h1> ADC PPB Limits (adc_ppb_limits)</h1>
//!
//! This example sets up the ePWM to periodically trigger the ADC. If the
//! results are outside of the defined range, the post-processing block
//! will generate an interrupt.
//!
//! The default limits are 1000LSBs and 3000LSBs.  With VREFHI set to 3.3V, the
//! PPB will generate an interrupt if the input voltage goes above about
//! 2.4V or below about 0.8V.
//!
//! \b External \b Connections \n
//!  - A0 should be connected to a signal to convert
//!
//! \b Watch \b Variables \n
//!  - None
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
uint32_t intStatus;
//
// Functional Prototypes
//
void configureEPWM(uint32_t epwmBase);

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
    // - Setup the ADC for ePWM triggered conversions on channel 0
    // - Configure ADC post-processing limits
    //      SOC0 will generate an interrupt if conversion is above or below limits
    // 
    Board_init();

    //
    // Configure the ePWM
    //
    configureEPWM(EPWM1_BASE);

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
    // Enable SOCA trigger
    //
    EPWM_enableADCTrigger(EPWM1_BASE, EPWM_SOC_A);

    //
    // Unfreeze epwm counter to count-up
    //
    EPWM_setTimeBaseCounterMode(EPWM1_BASE, EPWM_COUNTER_MODE_UP);

    //
    // Take conversions indefinitely in loop
    //
    do
    {
        //
        // Wait while ePWM causes ADC conversions.
        // If the ADC conversions exceed the PPB limits, then an interrupt
        // will be generated. User can read ADC results either in idle loop
        // or ADCINT ISR as per application requirement.
        //
    }
    while(1);
}

//
// configureEPWM - Setup SOC and compare values for EPWM
//
void configureEPWM(uint32_t epwmBase)
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
    // Set compare A value to 2048 counts
    //
    EPWM_setCounterCompareValue(epwmBase, EPWM_COUNTER_COMPARE_A, 2048U);

    //
    // Set period to 4096 counts
    //
    EPWM_setTimeBasePeriod(epwmBase, 4096U);

    //
    // Freeze counter
    //
    EPWM_setTimeBaseCounterMode(epwmBase, EPWM_COUNTER_MODE_STOP_FREEZE);
}

//
// adcAEvtISR - ISR for ADCA PPB
//
interrupt void adcAEvtISR(void)
{
    //
    // Warning, you are outside of PPB limits
    //
    intStatus = ADC_getPPBEventStatus(myADC0_BASE, ADC_PPB_NUMBER1);
    if((intStatus & ADC_EVT_TRIPHI) != 0U)
    {
        //
        // Voltage exceeded high limit
        //
        asm("   ESTOP0");

        //
        // Clear the trip flag and continue
        //
        ADC_clearPPBEventStatus(myADC0_BASE, ADC_PPB_NUMBER1, ADC_EVT_TRIPHI);
    }
    if((intStatus & ADC_EVT_TRIPLO) != 0U)
    {
        //
        // Voltage exceeded low limit
        //
        asm("   ESTOP0");

        //
        // Clear the trip flag and continue
        //
        ADC_clearPPBEventStatus(myADC0_BASE, ADC_PPB_NUMBER1, ADC_EVT_TRIPLO);
    }
    Interrupt_clearACKGroup(INT_myADC0_EVT_INTERRUPT_ACK_GROUP);
}

//
// End of file
//
