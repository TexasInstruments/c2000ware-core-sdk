//#############################################################################
//
// FILE:   mcpwm_ex1_basic_pwm.c
//
// TITLE:  MCPWM Basic PWM generation and updates Example
//
//! \addtogroup driver_example_list
//! <h1>MCPWM Basic PWM Generation and Updates</h1>
//!
//! This example configures myMCPWM0 and myMCPWM1 as follows
//!     myMCPWM0 
//!         Time Base Configurations 
//!             In Up Count Mode for 10KHz Frequency PWM
//!         Action Qualifier is configurations
//!             Output A1 : Set High on Counter matches zero, set low on CMPA match
//!             Output B1 : Set High on Counter matches zero, set low on CMPB match
//!             Output A2 : Set High on Counter matches CMPA, set low on Period match
//!             Output B2 : Set High on Counter matches CMPB, set low on Period match
//!             Output A3 : Set High on Counter matches CMPA, set low on CMPB match
//!             Output B3 : Set Low on Counter  matches CMPA, set high on CMPB match
//!         Interrupt
//!             For Updating the CMPx Values runtime, Interrupt is configured in synchronous 
//!             with the PWM Counter. 
//!             ET1 is configured to fire at every 5 events of Counter = Period.
//!             ET1 is selected as source for the interrupt generation
//!     
//!     myMCPWM1
//!         Time Base Configurations 
//!             In Up Down Count Mode for 10KHz Frequency PWM
//!         Action Qualifier is configurations
//!             Output A1 : 
//!                 Set High on Counter matches CMPA while counting up, 
//!                 Set low on CMPA match while Counting down
//!             Output B1 : 
//!                 Set High on Counter matches CMPB while counting up, 
//!                 Set low on CMPB match while Counting down
//!         Interrupt
//!             For Updating the CMPx Values runtime, Interrupt is configured in synchronous 
//!             with the PWM Counter. 
//!             ET1 is configured to fire at every 5 events of Counter = Period.
//!             ET1 is selected as source for the interrupt generation
//!
//!
//!  \b External \b Connections \n
//!     Monitor the MCPWM pins for the waveforms.
//!         Observe J4 40 - GPIO0  - myMCPWM0 Output A1
//!         Observe J4 39 - GPIO1  - myMCPWM0 Output B1
//!         Observe J4 38 - GPIO2  - myMCPWM0 Output A2
//!         Observe J4 37 - GPIO3  - myMCPWM0 Output B2
//!         Observe J4 36 - GPIO4  - myMCPWM0 Output A3
//!         Observe J4 35 - GPIO5  - myMCPWM0 Output B3
//!         Observe J4 7  - GPIO12 - myMCPWM1 Output A1
//!         Observe J2 19 - GPIO29 - myMCPWM1 Output B1
//
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
// Globals
//
uint16_t gMcpwm0Period;
uint16_t gMcpwm1Period;

uint16_t gMcpwm0CmpA;
uint16_t gMcpwm0CmpB;
uint16_t gMcpwm1CmpA;
uint16_t gMcpwm1CmpB;

//
// Macros
//
#define APP_CMPA_MIN_PERCENT_PERIOD (10.0f)
#define APP_CMPA_MAX_PERCENT_PERIOD (50.0f)
#define APP_CMPB_MIN_PERCENT_PERIOD (50.0f)
#define APP_CMPB_MAX_PERCENT_PERIOD (90.0f)
#define APP_CMP_UPDATE_STEP_PERCENT_PERIOD (5.0f)

//
// Function Prototypes
//
__interrupt void INT_myMCPWM0_ISR(void);
__interrupt void INT_myMCPWM1_ISR(void);

void main(void)
{
    //
    // Initialize global variables
    //

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Disable pin locks and enable internal pull-ups.
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
    // Disable sync(Freeze clock to PWM as well)
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Configure mcpwm1, mcpwm2
    //
    Board_init();

    //
    // get the Configuration info for updates
    // Note if the shadow registers were used in the init configuration, 
    // the corresponding MCPWM_getTimeBasePeriodShadow() and 
    // MCPWM_getCounterCompareValueShadow() may be used.
    //
    // Note: the Shadow registers are being used in this example as the 
    //       loadMode is not set to LOAD_FREEZE
    //
    //
    gMcpwm0Period = MCPWM_getTimeBasePeriodShadow(myMCPWM0_BASE);
    gMcpwm1Period = MCPWM_getTimeBasePeriodShadow(myMCPWM1_BASE);
    gMcpwm0CmpA   = MCPWM_getCounterCompareShadowValue(myMCPWM0_BASE, MCPWM_COUNTER_COMPARE_1A);
    gMcpwm0CmpB   = MCPWM_getCounterCompareShadowValue(myMCPWM0_BASE, MCPWM_COUNTER_COMPARE_1B);
    gMcpwm1CmpA   = MCPWM_getCounterCompareShadowValue(myMCPWM1_BASE, MCPWM_COUNTER_COMPARE_1A);
    gMcpwm1CmpB   = MCPWM_getCounterCompareShadowValue(myMCPWM1_BASE, MCPWM_COUNTER_COMPARE_1B);

    //
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Enable Global Interrupt (INTM) and real time interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // IDLE loop. Just sit and loop forever (optional):
    //
    for(;;)
    {
        NOP;
    }
}

//
// INT_myMCPWM0_ISR - mcpwm0 ISR
//
__interrupt void INT_myMCPWM0_ISR(void)
{
    
    //
    // Alternatively, we can get the current Active and Shadow values of the CMPx registers using
    // MCPWM_getCounterCompareActiveValue() and MCPWM_getCounterCompareShadowValue() respectively and
    // use for the calculation. 
    // 
    // For this example we are using a common CMPA and CMPB values for all PWM1,2,3 of myMCPWM0
    // hence, using a common variable instead of get API everytime.
    // 
    
    uint16_t minCmpAValue = (uint16_t) ((APP_CMPA_MIN_PERCENT_PERIOD * ((float)gMcpwm0Period))/100.0);
    uint16_t maxCmpAValue = (uint16_t) ((APP_CMPA_MAX_PERCENT_PERIOD * ((float)gMcpwm0Period))/100.0);
    uint16_t minCmpBValue = (uint16_t) ((APP_CMPB_MIN_PERCENT_PERIOD * ((float)gMcpwm0Period))/100.0);
    uint16_t maxCmpBValue = (uint16_t) ((APP_CMPB_MAX_PERCENT_PERIOD * ((float)gMcpwm0Period))/100.0);

    gMcpwm0CmpA += (uint16_t) ((APP_CMP_UPDATE_STEP_PERCENT_PERIOD * ((float)gMcpwm0Period))/100.0);
    gMcpwm0CmpB += (uint16_t) ((APP_CMP_UPDATE_STEP_PERCENT_PERIOD * ((float)gMcpwm0Period))/100.0);

    if(gMcpwm0CmpA > maxCmpAValue){
        gMcpwm0CmpA = minCmpAValue;
    }
    if(gMcpwm0CmpB > maxCmpBValue){
        gMcpwm0CmpB = minCmpBValue;
    }

    //
    // Note that these updates may be interrupted by a higher priority interrupt or,
    // the updates may happen across a period event (or action events selected). Such 
    // scenarios result in the unexpected period/duty behaviour in the outputs. 
    // suggested approach is to use the shadow load mode or the global load mode, and
    // use the corresponding MCPWM_setCounterCompareShadowValue() API for updates.
    //
    // For global load usage, please refer to the global load use case exmaple.
    //
    MCPWM_setCounterCompareShadowValue(myMCPWM0_BASE, MCPWM_COUNTER_COMPARE_1A, gMcpwm0CmpA);
    MCPWM_setCounterCompareShadowValue(myMCPWM0_BASE, MCPWM_COUNTER_COMPARE_1B, gMcpwm0CmpB);
    MCPWM_setCounterCompareShadowValue(myMCPWM0_BASE, MCPWM_COUNTER_COMPARE_2A, gMcpwm0CmpA);
    MCPWM_setCounterCompareShadowValue(myMCPWM0_BASE, MCPWM_COUNTER_COMPARE_2B, gMcpwm0CmpB);
    MCPWM_setCounterCompareShadowValue(myMCPWM0_BASE, MCPWM_COUNTER_COMPARE_3A, gMcpwm0CmpA);
    MCPWM_setCounterCompareShadowValue(myMCPWM0_BASE, MCPWM_COUNTER_COMPARE_3B, gMcpwm0CmpB);

    //
    // Clear the interrupt flags. 
    // to clear all flags, MCPWM_INT_SOURCE_ALL may be used as arg.
    //
    MCPWM_clearInterrupt(myMCPWM0_BASE, MCPWM_INT_ET_1);

    //
    // Clear the global interrupt flag. Only with this flag clear, 
    // will the next interrupt be received.
    //
    MCPWM_clearGlobalInterrupt(myMCPWM0_BASE);


    //
    // Acknowledge this interrupt to receive more interrupts from group
    //
    Interrupt_clearACKGroup(INT_myMCPWM0_INTERRUPT_ACK_GROUP);
}

//
// INT_myMCPWM1_ISR - myMCPWM1 ISR
//
__interrupt void INT_myMCPWM1_ISR(void)
{

    //
    // Alternatively, we can get the current Active and Shadow values of the CMPx registers using
    // MCPWM_getCounterCompareActiveValue() and MCPWM_getCounterCompareShadowValue() respectively and
    // use for the calculation. 
    // 
    
    uint16_t minCmpAValue = (uint16_t) ((APP_CMPA_MIN_PERCENT_PERIOD * ((float)gMcpwm1Period))/100.0);
    uint16_t maxCmpAValue = (uint16_t) ((APP_CMPA_MAX_PERCENT_PERIOD * ((float)gMcpwm1Period))/100.0);
    uint16_t minCmpBValue = (uint16_t) ((APP_CMPB_MIN_PERCENT_PERIOD * ((float)gMcpwm1Period))/100.0);
    uint16_t maxCmpBValue = (uint16_t) ((APP_CMPB_MAX_PERCENT_PERIOD * ((float)gMcpwm1Period))/100.0);

    gMcpwm1CmpA += (uint16_t) ((APP_CMP_UPDATE_STEP_PERCENT_PERIOD * ((float)gMcpwm1Period))/100.0);
    gMcpwm1CmpB += (uint16_t) ((APP_CMP_UPDATE_STEP_PERCENT_PERIOD * ((float)gMcpwm1Period))/100.0);

    if(gMcpwm1CmpA > maxCmpAValue){
        gMcpwm1CmpA = minCmpAValue;
    }
    if(gMcpwm1CmpB > maxCmpBValue){
        gMcpwm1CmpB = minCmpBValue;
    }

    //
    // Note that these updates may be interrupted by a higher priority interrupt or,
    // the updates may happen across a period event (or action events selected). Such 
    // scenarios result in the unexpected period/duty behaviour in the outputs. 
    // suggested approach is to use the shadow load mode or the global load mode, and
    // use the corresponding MCPWM_setCounterCompareValueShadow() API for updates.
    //
    // For global load usage, please refer to the global load use case exmaple.
    //
    MCPWM_setCounterCompareShadowValue(myMCPWM1_BASE, MCPWM_COUNTER_COMPARE_1A, gMcpwm1CmpA);
    MCPWM_setCounterCompareShadowValue(myMCPWM1_BASE, MCPWM_COUNTER_COMPARE_1B, gMcpwm1CmpB);

    //
    // Clear the interrupt flags. 
    // to clear all flags, MCPWM_INT_SOURCE_ALL may be used as arg.
    //
    MCPWM_clearInterrupt(myMCPWM1_BASE, MCPWM_INT_ET_1);

    //
    // Clear the global interrupt flag. Only with this flag clear, 
    // will the next interrupt be received.
    //
    MCPWM_clearGlobalInterrupt(myMCPWM1_BASE);


    //
    // Acknowledge this interrupt to receive more interrupts from group
    //
    Interrupt_clearACKGroup(INT_myMCPWM1_INTERRUPT_ACK_GROUP);
}

