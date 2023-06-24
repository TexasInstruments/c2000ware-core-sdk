//#############################################################################
//
// FILE:    ecap_sw_sync.c
//
// TITLE:   Software Sync.
//
//! \addtogroup driver_example_list
//! <h1>eCAP Software Sync Example</h1>
//!
//! This example configures ePWM3A for:
//! - Up count mode
//! - Period starts at 500 and goes up to 8000
//! - Toggle output on PRD
//!
//! eCAP1, eCAP2 and eCAP3 are configured to capture the time between rising
//! and falling edge of the ePWM3A output.
//!
//! \b External \b Connections \n
//! - eCAP1, eCAP2, eCAP3 are on GPIO16
//! - ePWM3A is on GPIO4
//! - Connect GPIO4 to GPIO16.
//!
//! \b Watch \b Variables \n
//! - \b ecapPassCount - Successful captures.
//! - \b ecap3IntCount - Interrupt counts.
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
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "board.h"

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
bool firstInterrupt;
uint32_t ecap3IntCount;
uint32_t ecapPassCount;
uint32_t epwm3TimerDirection;
volatile uint16_t epwm3PeriodCount;
volatile uint16_t ecap1Cap1Count;
volatile uint16_t ecap1Cap2Count;
volatile uint16_t ecap1Cap3Count;
volatile uint16_t ecap1Cap4Count;
volatile uint16_t ecap2Cap1Count;
volatile uint16_t ecap2Cap2Count;
volatile uint16_t ecap2Cap3Count;
volatile uint16_t ecap2Cap4Count;
volatile uint16_t ecap3Cap1Count;
volatile uint16_t ecap3Cap2Count;
volatile uint16_t ecap3Cap3Count;
volatile uint16_t ecap3Cap4Count;

//
// Function Prototypes
//
void error(void);
void initECAP(void);
void initEPWM(void);

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
    GPIO_setPadConfig(4,GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_4_EPWM3_A);
    GPIO_setPadConfig(5,GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_5_EPWM3_B);

    //
    // Board initialization
    // Configure GPIO 16 as eCAP input
    // Enable interrupts required for this example
    //
    Board_init();

    //
    // Configure ePWM
    //
    initEPWM();
    
    //
    // Initialize counters: and values
    //
    firstInterrupt = true;
    ecap3IntCount = 0U;
    ecapPassCount = 0U;
    epwm3PeriodCount = 0U;
    ecap1Cap1Count = 0U;
    ecap1Cap2Count = 0U;
    ecap1Cap3Count = 0U;
    ecap1Cap4Count = 0U;
    ecap2Cap1Count = 0U;
    ecap2Cap2Count = 0U;
    ecap2Cap3Count = 0U;
    ecap2Cap4Count = 0U;
    ecap3Cap1Count = 0U;
    ecap3Cap2Count = 0U;
    ecap3Cap3Count = 0U;
    ecap3Cap4Count = 0U;

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
// myECAP3 ISR
//
__interrupt void INT_myECAP3_ISR(void)
{
    //
    // Get the capture counts. Each capture should match for all the eCAPs. 
    //
    ecap1Cap1Count = ECAP_getEventTimeStamp(myECAP1_BASE, ECAP_EVENT_1);
    ecap1Cap2Count = ECAP_getEventTimeStamp(myECAP1_BASE, ECAP_EVENT_2);
    ecap1Cap3Count = ECAP_getEventTimeStamp(myECAP1_BASE, ECAP_EVENT_3);
    ecap1Cap4Count = ECAP_getEventTimeStamp(myECAP1_BASE, ECAP_EVENT_4);
    ecap2Cap1Count = ECAP_getEventTimeStamp(myECAP2_BASE, ECAP_EVENT_1);
    ecap2Cap2Count = ECAP_getEventTimeStamp(myECAP2_BASE, ECAP_EVENT_2);
    ecap2Cap3Count = ECAP_getEventTimeStamp(myECAP2_BASE, ECAP_EVENT_3);
    ecap2Cap4Count = ECAP_getEventTimeStamp(myECAP2_BASE, ECAP_EVENT_4);
    ecap3Cap1Count = ECAP_getEventTimeStamp(myECAP3_BASE, ECAP_EVENT_1);
    ecap3Cap2Count = ECAP_getEventTimeStamp(myECAP3_BASE, ECAP_EVENT_2);
    ecap3Cap3Count = ECAP_getEventTimeStamp(myECAP3_BASE, ECAP_EVENT_3);
    ecap3Cap4Count = ECAP_getEventTimeStamp(myECAP3_BASE, ECAP_EVENT_4);

    //
    // Compare the period value with the captured count
    //
    epwm3PeriodCount = EPWM_getTimeBasePeriod(EPWM3_BASE);
    
    //
    // Validate synchronization. 
    //
    if(firstInterrupt){
        firstInterrupt = false;
    }
    else{
        if (!((ecap1Cap1Count == ecap2Cap1Count)&&(ecap2Cap1Count == ecap3Cap1Count)))
        {
            error();
        }
    }
    if (!((ecap1Cap2Count == ecap2Cap2Count)&&(ecap2Cap2Count == ecap3Cap2Count)))
    {
        error();
    }
    if (!((ecap1Cap3Count == ecap2Cap3Count)&&(ecap2Cap3Count == ecap3Cap3Count)))
    {
        error();
    }
    if (!((ecap1Cap4Count == ecap2Cap4Count)&&(ecap2Cap4Count == ecap3Cap4Count)))
    {
        error();
    }

    ecap3IntCount++;

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
    ecapPassCount++;

    //
    // Clear interrupt flags for more interrupts.
    //
    ECAP_clearInterrupt(myECAP3_BASE,ECAP_ISR_SOURCE_CAPTURE_EVENT_4);
    ECAP_clearGlobalInterrupt(myECAP3_BASE);

    //
    // Start eCAP
    //
    ECAP_reArm(myECAP1_BASE);
    ECAP_reArm(myECAP2_BASE);
    ECAP_reArm(myECAP3_BASE);

    //
    // Acknowledge the group interrupt for more interrupts.
    //
    Interrupt_clearACKGroup(INT_myECAP3_INTERRUPT_ACK_GROUP);
}

//
// error - Error function
//
void error()
{
    ESTOP0;
}
