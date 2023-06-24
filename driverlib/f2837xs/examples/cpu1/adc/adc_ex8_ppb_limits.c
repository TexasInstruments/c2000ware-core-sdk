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
uint32_t intStatus;
//
// Functional Prototypes
//
void configureADC(uint32_t adcBase);
void configureEPWM(uint32_t epwmBase);
void configurePPB1Limits(uint16_t soc, uint16_t limitHigh, uint16_t limitLow);
void configureADCSOC(uint32_t adcBase, uint16_t channel);
interrupt void adcAEvtISR(void);

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
    // Map ISR functions
    //
    Interrupt_register(INT_ADCA_EVT, &adcAEvtISR);

    //
    // Enable specific PIE & CPU interrupts:
    //
    Interrupt_enable(INT_ADCA_EVT);


    //
    // Configure the ADC and power it up
    //
    configureADC(ADCA_BASE);

    //
    // Configure the ePWM
    //
    configureEPWM(EPWM1_BASE);

    //
    // Setup the ADC for ePWM triggered conversions on channel 0
    //
    configureADCSOC(ADCA_BASE, 0);

    //
    // Configure ADC post-processing limits
    // SOC0 will generate an interrupt if conversion is above or below limits
    //
    configurePPB1Limits(0,3000,1000);

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
// configureADC - Write ADC configurations and power up the ADC for both
//                ADC A and ADC C
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
// adcAEvtISR - ISR for ADCA PPB
//
interrupt void adcAEvtISR(void)
{
    //
    // Warning, you are outside of PPB limits
    //
    intStatus = ADC_getPPBEventStatus(ADCA_BASE, ADC_PPB_NUMBER1);
    if((intStatus & ADC_EVT_TRIPHI) != 0U)
    {
        //
        // Voltage exceeded high limit
        //
        asm("   ESTOP0");

        //
        // Clear the trip flag and continue
        //
        ADC_clearPPBEventStatus(ADCA_BASE, ADC_PPB_NUMBER1, ADC_EVT_TRIPHI);
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
        ADC_clearPPBEventStatus(ADCA_BASE, ADC_PPB_NUMBER1, ADC_EVT_TRIPLO);
    }
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP10);
}

//
// End of file
//
