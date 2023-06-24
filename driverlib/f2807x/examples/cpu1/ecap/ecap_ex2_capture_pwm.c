//#############################################################################
//
// FILE:    ecap_capture_pwm.c
//
// TITLE:   Capture ePWM3.
//
//! \addtogroup driver_example_list
//! <h1>eCAP Capture PWM Example</h1>
//!
//! This example configures ePWM3A for:
//! - Up count mode
//! - Period starts at 500 and goes up to 8000
//! - Toggle output on PRD
//!
//! eCAP1 is configured to capture the time between rising
//! and falling edge of the ePWM3A output.
//!
//! \b External \b Connections \n
//! - eCAP1 is on GPIO16
//! - ePWM3A is on GPIO4
//! - Connect GPIO4 to GPIO16.
//!
//! \b Watch \b Variables \n
//! - \b ecap1PassCount - Successful captures.
//! - \b ecap1IntCount - Interrupt counts.
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
// Included Files
//
#include "driverlib.h"
#include "device.h"

//
// Defines
//
#define PWM3_TIMER_MIN     500U
#define PWM3_TIMER_MAX     8000U
#define EPWM_TIMER_UP      1U
#define EPWM_TIMER_DOWN    0U

//
// Globals
//
uint32_t ecap1IntCount;
uint32_t ecap1PassCount;
uint32_t epwm3TimerDirection;
volatile uint16_t cap2Count;
volatile uint16_t cap3Count;
volatile uint16_t cap4Count;
volatile uint16_t epwm3PeriodCount;

//
// Function Prototypes
//
void error(void);
void initECAP(void);
void initEPWM(void);
__interrupt void ecap1ISR(void);

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
    // Configure GPIO4/5 as ePWM3A/3B
    //
    GPIO_setPadConfig(4, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_4_EPWM3A);
    GPIO_setPadConfig(5, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_5_EPWM3B);

    //
    // Configure GPIO 16 as eCAP input
    //
    XBAR_setInputPin(XBAR_INPUT7, 16);
    GPIO_setPinConfig(GPIO_16_GPIO16);
    GPIO_setDirectionMode(16, GPIO_DIR_MODE_IN);
    GPIO_setQualificationMode(16, GPIO_QUAL_ASYNC);

    //
    // Interrupts that are used in this example are re-mapped to ISR functions
    // found within this file.
    //
    Interrupt_register(INT_ECAP1, &ecap1ISR);

    //
    // Configure ePWM and eCAP
    //
    initEPWM();
    initECAP();

    //
    // Initialize counters:
    //
    cap2Count = 0U;
    cap3Count = 0U;
    cap4Count = 0U;
    ecap1IntCount = 0U;
    ecap1PassCount = 0U;
    epwm3PeriodCount = 0U;

    //
    // Enable interrupts required for this example
    //
    Interrupt_enable(INT_ECAP1);

    //
    // Enable Global Interrupt (INTM) and Real time interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Loop forever. Suspend or place breakpoints to observe the buffers.
    //
    for(;;)
    {
       NOP;
    }
}

//
// initEPWM - Configure ePWM
//
void initEPWM()
{
    //
    // Disable sync(Freeze clock to PWM as well)
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Configure ePWM
    //       Counter runs in up-count mode.
    //       Action qualifier will toggle output on period match
    //
    EPWM_setTimeBaseCounterMode(EPWM3_BASE, EPWM_COUNTER_MODE_UP);
    EPWM_setTimeBasePeriod(EPWM3_BASE, PWM3_TIMER_MIN);
    EPWM_setPhaseShift(EPWM3_BASE, 0U);
    EPWM_setActionQualifierAction(EPWM3_BASE,
                                  EPWM_AQ_OUTPUT_A,
                                  EPWM_AQ_OUTPUT_TOGGLE,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);
    EPWM_setClockPrescaler(EPWM3_BASE,
                           EPWM_CLOCK_DIVIDER_1,
                           EPWM_HSCLOCK_DIVIDER_2);

    epwm3TimerDirection = EPWM_TIMER_UP;

    //
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);
}

//
// initECAP - Configure eCAP
//
void initECAP()
{
    //
    // Disable ,clear all capture flags and interrupts
    //
    ECAP_disableInterrupt(ECAP1_BASE,
                          (ECAP_ISR_SOURCE_CAPTURE_EVENT_1  |
                           ECAP_ISR_SOURCE_CAPTURE_EVENT_2  |
                           ECAP_ISR_SOURCE_CAPTURE_EVENT_3  |
                           ECAP_ISR_SOURCE_CAPTURE_EVENT_4  |
                           ECAP_ISR_SOURCE_COUNTER_OVERFLOW |
                           ECAP_ISR_SOURCE_COUNTER_PERIOD   |
                           ECAP_ISR_SOURCE_COUNTER_COMPARE));
    ECAP_clearInterrupt(ECAP1_BASE,
                        (ECAP_ISR_SOURCE_CAPTURE_EVENT_1  |
                         ECAP_ISR_SOURCE_CAPTURE_EVENT_2  |
                         ECAP_ISR_SOURCE_CAPTURE_EVENT_3  |
                         ECAP_ISR_SOURCE_CAPTURE_EVENT_4  |
                         ECAP_ISR_SOURCE_COUNTER_OVERFLOW |
                         ECAP_ISR_SOURCE_COUNTER_PERIOD   |
                         ECAP_ISR_SOURCE_COUNTER_COMPARE));

    //
    // Disable CAP1-CAP4 register loads
    //
    ECAP_disableTimeStampCapture(ECAP1_BASE);

    //
    // Configure eCAP
    //    Enable capture mode.
    //    One shot mode, stop capture at event 4.
    //    Set polarity of the events to rising, falling, rising, falling edge.
    //    Set capture in time difference mode.
    //    Select input from XBAR7.
    //    Enable eCAP module.
    //    Enable interrupt.
    //
    ECAP_stopCounter(ECAP1_BASE);
    ECAP_enableCaptureMode(ECAP1_BASE);

    ECAP_setCaptureMode(ECAP1_BASE, ECAP_ONE_SHOT_CAPTURE_MODE, ECAP_EVENT_4);

    ECAP_setEventPolarity(ECAP1_BASE, ECAP_EVENT_1, ECAP_EVNT_FALLING_EDGE);
    ECAP_setEventPolarity(ECAP1_BASE, ECAP_EVENT_2, ECAP_EVNT_RISING_EDGE);
    ECAP_setEventPolarity(ECAP1_BASE, ECAP_EVENT_3, ECAP_EVNT_FALLING_EDGE);
    ECAP_setEventPolarity(ECAP1_BASE, ECAP_EVENT_4, ECAP_EVNT_RISING_EDGE);

    ECAP_enableCounterResetOnEvent(ECAP1_BASE, ECAP_EVENT_1);
    ECAP_enableCounterResetOnEvent(ECAP1_BASE, ECAP_EVENT_2);
    ECAP_enableCounterResetOnEvent(ECAP1_BASE, ECAP_EVENT_3);
    ECAP_enableCounterResetOnEvent(ECAP1_BASE, ECAP_EVENT_4);

    XBAR_setInputPin(XBAR_INPUT7, 16);

    ECAP_enableLoadCounter(ECAP1_BASE);
    ECAP_setSyncOutMode(ECAP1_BASE, ECAP_SYNC_OUT_SYNCI);
    ECAP_startCounter(ECAP1_BASE);
    ECAP_enableTimeStampCapture(ECAP1_BASE);
    ECAP_reArm(ECAP1_BASE);

    ECAP_enableInterrupt(ECAP1_BASE, ECAP_ISR_SOURCE_CAPTURE_EVENT_4);
}

//
// eCAP 1 ISR
//
__interrupt void ecap1ISR(void)
{
    //
    // Get the capture counts. Each capture should be 4x the ePWM count
    // because of the ePWM clock dividers.
    //
    cap2Count = ECAP_getEventTimeStamp(ECAP1_BASE, ECAP_EVENT_2);
    cap3Count = ECAP_getEventTimeStamp(ECAP1_BASE, ECAP_EVENT_3);
    cap4Count = ECAP_getEventTimeStamp(ECAP1_BASE, ECAP_EVENT_4);

    //
    // Compare the period value with the captured count
    //
    epwm3PeriodCount = EPWM_getTimeBasePeriod(EPWM3_BASE);

    if(cap2Count > ((epwm3PeriodCount * 4) + 4) ||
       cap2Count < ((epwm3PeriodCount * 4) - 4))
    {
        error();
    }

    if(cap3Count > ((epwm3PeriodCount * 4) + 4) ||
       cap3Count < ((epwm3PeriodCount * 4) - 4))
    {
        error();
    }

    if(cap4Count > ((epwm3PeriodCount * 4) + 4) ||
       cap4Count < ((epwm3PeriodCount * 4) - 4))
    {
        error();
    }

    ecap1IntCount++;

    //
    // Keep track of the ePWM direction and adjust period accordingly to
    // generate a variable frequency PWM.
    //
    if(epwm3TimerDirection == EPWM_TIMER_UP)
    {
        if(epwm3PeriodCount < PWM3_TIMER_MAX)
        {
           EPWM_setTimeBasePeriod(EPWM3_BASE, ++epwm3PeriodCount);
        }
        else
        {
           epwm3TimerDirection = EPWM_TIMER_DOWN;
           EPWM_setTimeBasePeriod(EPWM3_BASE, ++epwm3PeriodCount);
        }
    }
    else
    {
        if(epwm3PeriodCount > PWM3_TIMER_MIN)
        {
            EPWM_setTimeBasePeriod(EPWM3_BASE, --epwm3PeriodCount);
        }
        else
        {
           epwm3TimerDirection = EPWM_TIMER_UP;
           EPWM_setTimeBasePeriod(EPWM3_BASE, ++epwm3PeriodCount);
        }
    }

    //
    // Count correct captures
    //
    ecap1PassCount++;

    //
    // Clear interrupt flags for more interrupts.
    //
    ECAP_clearInterrupt(ECAP1_BASE,ECAP_ISR_SOURCE_CAPTURE_EVENT_4);
    ECAP_clearGlobalInterrupt(ECAP1_BASE);

    //
    // Start eCAP
    //
    ECAP_reArm(ECAP1_BASE);

    //
    // Acknowledge the group interrupt for more interrupts.
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP4);
}

//
// error - Error function
//
void error()
{
    ESTOP0;
}
