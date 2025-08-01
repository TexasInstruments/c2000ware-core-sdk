//#############################################################################
//
// FILE:    ecap_capture_pwm.c
//
// TITLE:   Capture MCPWM1.
//
//! \addtogroup driver_example_list
//! <h1>eCAP Capture PWM Example</h1>
//!
//! This example configures MCPWM1A for:
//! - Up count mode
//! - Period starts at 500 and goes up to 8000
//! - Toggle output on PRD
//!
//! eCAP1 is configured to capture the time between rising
//! and falling edge of the MCPWM1A output.
//!
//! \b External \b Connections \n
//! - eCAP1 is on GPIO2
//! - MCPWM1A is on GPIO0
//! - Connect GPIO0 to GPIO2.
//!
//! \b Watch \b Variables \n
//! - \b ecap1PassCount - Successful captures.
//! - \b ecap1IntCount - Interrupt counts.
//
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2025 Texas Instruments Incorporated - http://www.ti.com/
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
#include "board.h"

//
// Defines
//
#define PWM1_TIMER_MIN     500U
#define PWM1_TIMER_MAX     8000U
#define MCPWM_TIMER_UP      1U
#define MCPWM_TIMER_DOWN    0U

//
// Globals
//
uint32_t ecap1IntCount;
uint32_t ecap1PassCount;
uint32_t MCPWM1TimerDirection;
volatile uint32_t cap2Count;
volatile uint32_t cap3Count;
volatile uint32_t cap4Count;
volatile uint16_t MCPWM1PeriodCount;

//
// Function Prototypes
//
void error(void);
void initECAP(void);
void initMCPWM(void);

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
    // Configure GPIO0/1 as MCPWM1A/1B
    //
    GPIO_setPadConfig(0,GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_0_MCPWM1_1A);
    GPIO_setPadConfig(1,GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_1_MCPWM1_1B);

    //
    // Board initialization
    // Configure GPIO 16 as eCAP input
    // Enable interrupts required for this example
    //
    Board_init();
    
    //
    // Configure MCPWM
    //
    initMCPWM();

    //
    // Initialize counters:
    //
    cap2Count = 0U;
    cap3Count = 0U;
    cap4Count = 0U;
    ecap1IntCount = 0U;
    ecap1PassCount = 0U;
    MCPWM1PeriodCount = 0U;

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
// initMCPWM - Configure MCPWM
//
void initMCPWM()
{
    //
    // Disable sync(Freeze clock to PWM as well)
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Configure MCPWM
    //       Counter runs in up-count mode.
    //       Action qualifier will toggle output on period match
    //
    MCPWM_setTimeBaseCounterMode(PWM1_BASE, MCPWM_COUNTER_MODE_UP);
    MCPWM_setTimeBasePeriodShadow(PWM1_BASE, PWM1_TIMER_MIN);

    MCPWM_setActionQualifierActionCompleteShadow(PWM1_BASE, MCPWM_AQ_OUTPUT_1A,
    MCPWM_AQ_OUTPUT_NO_CHANGE_ZERO | MCPWM_AQ_OUTPUT_TOGGLE_PERIOD 
    | MCPWM_AQ_OUTPUT_NO_CHANGE_UP_CMPA | MCPWM_AQ_OUTPUT_NO_CHANGE_DOWN_CMPA 
    | MCPWM_AQ_OUTPUT_NO_CHANGE_UP_CMPB | MCPWM_AQ_OUTPUT_NO_CHANGE_DOWN_CMPB);

    MCPWM_setClockPrescaler(PWM1_BASE,
                            MCPWM_CLOCK_DIVIDER_2);

    MCPWM1TimerDirection = MCPWM_TIMER_UP;

    //
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);
}

//
// myECAP0 ISR
//
__interrupt void INT_myECAP0_ISR(void)
{
    //
    // Get the capture counts. Each capture should be 2x the MCPWM count
    // because of the MCPWM clock divider.
    //
    cap2Count = ECAP_getEventTimeStamp(myECAP0_BASE, ECAP_EVENT_2);
    cap3Count = ECAP_getEventTimeStamp(myECAP0_BASE, ECAP_EVENT_3);
    cap4Count = ECAP_getEventTimeStamp(myECAP0_BASE, ECAP_EVENT_4);

    //
    // Compare the period value with the captured count
    //
    MCPWM1PeriodCount = MCPWM_getTimeBasePeriodShadow(PWM1_BASE);

    if(cap2Count > ((MCPWM1PeriodCount *2) + 2U) ||
       cap2Count < ((MCPWM1PeriodCount *2) - 2U))
    {
        error();
    }

    if(cap3Count > ((MCPWM1PeriodCount *2) + 2U) ||
       cap3Count < ((MCPWM1PeriodCount *2) - 2U))
    {
        error();
    }

    if(cap4Count > ((MCPWM1PeriodCount *2) + 2U) ||
       cap4Count < ((MCPWM1PeriodCount *2) - 2U))
    {
        error();
    }

    ecap1IntCount++;

    //
    // Keep track of the MCPWM direction and adjust period accordingly to
    // generate a variable frequency PWM.
    //
    if(MCPWM1TimerDirection == MCPWM_TIMER_UP)
    {
        if(MCPWM1PeriodCount < PWM1_TIMER_MAX)
        {
           MCPWM_setTimeBasePeriodShadow(PWM1_BASE, ++MCPWM1PeriodCount);
        }
        else
        {
           MCPWM1TimerDirection = MCPWM_TIMER_DOWN;
           MCPWM_setTimeBasePeriodShadow(PWM1_BASE, ++MCPWM1PeriodCount);
        }
    }
    else
    {
        if(MCPWM1PeriodCount > PWM1_TIMER_MIN)
        {
            MCPWM_setTimeBasePeriodShadow(PWM1_BASE, --MCPWM1PeriodCount);
        }
        else
        {
           MCPWM1TimerDirection = MCPWM_TIMER_UP;
           MCPWM_setTimeBasePeriodShadow(PWM1_BASE, ++MCPWM1PeriodCount);
        }
    }

    //
    // Count correct captures
    //
    ecap1PassCount++;

    //
    // Clear interrupt flags for more interrupts.
    //
    ECAP_clearInterrupt(myECAP0_BASE,ECAP_ISR_SOURCE_CAPTURE_EVENT_4);
    ECAP_clearGlobalInterrupt(myECAP0_BASE);

    //
    // Start eCAP
    //
    ECAP_reArm(myECAP0_BASE);

    //
    // Acknowledge the group interrupt for more interrupts.
    //
    Interrupt_clearACKGroup(INT_myECAP0_INTERRUPT_ACK_GROUP);
}

//
// error - Error function
//
void error()
{
    ESTOP0;
}
