//#############################################################################
//
// FILE:   mcpwm_ex4_basic_pwm_no_syscfg.c
//
// TITLE:  MCPWM Basic PWM generation and updates Example without Sysconfig
//
//! \addtogroup driver_example_list
//! <h1>MCPWM Basic PWM Generation and Updates without Sysconfig</h1>
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
void configureMcpwmPinmux(void);
void initMyMCPWM0(void);
void initMyMCPWM1(void);
void registerMcpwmInterrupts(void);

// Interrupt Settings for INT_myMCPWM0
// ISR need to be defined for the registered interrupts
#define INT_myMCPWM0                        INT_MCPWM1
#define INT_myMCPWM0_INTERRUPT_ACK_GROUP    INTERRUPT_ACK_GROUP2

// Interrupt Settings for INT_myMCPWM1
// ISR need to be defined for the registered interrupts
#define INT_myMCPWM1                        INT_MCPWM3
#define INT_myMCPWM1_INTERRUPT_ACK_GROUP    INTERRUPT_ACK_GROUP3

#define myMCPWM0_BASE                       PWM1_BASE
#define myMCPWM1_BASE                       PWM3_BASE

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
    // Confiugure the pin mux for the MCPWM pins
    //
    configureMcpwmPinmux();


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

    Board_init();
    registerMcpwmInterrupts();
    
    //
    // initialize MCPWMs
    //
    initMyMCPWM0();
    initMyMCPWM1();

    MCPWM_clearInterrupt(myMCPWM0_BASE, MCPWM_INT_ET_1);
    MCPWM_clearGlobalInterrupt(myMCPWM0_BASE);

    MCPWM_clearInterrupt(myMCPWM1_BASE, MCPWM_INT_ET_1);
    MCPWM_clearGlobalInterrupt(myMCPWM1_BASE);

    Interrupt_enable(INT_myMCPWM0);
    Interrupt_enable(INT_myMCPWM1);

    //
    // get the Configuration info for updates
    // Note if the shadow registers were used in the init configuration, 
    // the corresponding MCPWM_getTimeBasePeriodShadow() and 
    // MCPWM_getCounterCompareValueShadow() may be used.
    //
    gMcpwm0Period = MCPWM_getTimeBasePeriodActive(myMCPWM0_BASE);
    gMcpwm1Period = MCPWM_getTimeBasePeriodActive(myMCPWM1_BASE);
    gMcpwm0CmpA   = MCPWM_getCounterCompareActiveValue(myMCPWM0_BASE, MCPWM_COUNTER_COMPARE_1A);
    gMcpwm0CmpB   = MCPWM_getCounterCompareActiveValue(myMCPWM0_BASE, MCPWM_COUNTER_COMPARE_1B);
    gMcpwm1CmpA   = MCPWM_getCounterCompareActiveValue(myMCPWM1_BASE, MCPWM_COUNTER_COMPARE_1A);
    gMcpwm1CmpB   = MCPWM_getCounterCompareActiveValue(myMCPWM1_BASE, MCPWM_COUNTER_COMPARE_1B);

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
    MCPWM_setCounterCompareActiveValue(myMCPWM0_BASE, MCPWM_COUNTER_COMPARE_1A, gMcpwm0CmpA);
    MCPWM_setCounterCompareActiveValue(myMCPWM0_BASE, MCPWM_COUNTER_COMPARE_1B, gMcpwm0CmpB);
    MCPWM_setCounterCompareActiveValue(myMCPWM0_BASE, MCPWM_COUNTER_COMPARE_2A, gMcpwm0CmpA);
    MCPWM_setCounterCompareActiveValue(myMCPWM0_BASE, MCPWM_COUNTER_COMPARE_2B, gMcpwm0CmpB);
    MCPWM_setCounterCompareActiveValue(myMCPWM0_BASE, MCPWM_COUNTER_COMPARE_3A, gMcpwm0CmpA);
    MCPWM_setCounterCompareActiveValue(myMCPWM0_BASE, MCPWM_COUNTER_COMPARE_3B, gMcpwm0CmpB);

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
    MCPWM_setCounterCompareActiveValue(myMCPWM1_BASE, MCPWM_COUNTER_COMPARE_1A, gMcpwm1CmpA);
    MCPWM_setCounterCompareActiveValue(myMCPWM1_BASE, MCPWM_COUNTER_COMPARE_1B, gMcpwm1CmpB);

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

//
// MCPWM1 -> myMCPWM0 Pinmux
//
//
// MCPWM1_1A - GPIO Settings
//
#define GPIO_PIN_MCPWM1_1A 0
#define myMCPWM0_MCPWM1A_GPIO 0
#define myMCPWM0_MCPWM1A_PIN_CONFIG GPIO_0_MCPWM1_1A
//
// MCPWM1_1B - GPIO Settings
//
#define GPIO_PIN_MCPWM1_1B 1
#define myMCPWM0_MCPWM1B_GPIO 1
#define myMCPWM0_MCPWM1B_PIN_CONFIG GPIO_1_MCPWM1_1B
//
// MCPWM1_2A - GPIO Settings
//
#define GPIO_PIN_MCPWM1_2A 2
#define myMCPWM0_MCPWM2A_GPIO 2
#define myMCPWM0_MCPWM2A_PIN_CONFIG GPIO_2_MCPWM1_2A
//
// MCPWM1_2B - GPIO Settings
//
#define GPIO_PIN_MCPWM1_2B 3
#define myMCPWM0_MCPWM2B_GPIO 3
#define myMCPWM0_MCPWM2B_PIN_CONFIG GPIO_3_MCPWM1_2B
//
// MCPWM1_3A - GPIO Settings
//
#define GPIO_PIN_MCPWM1_3A 4
#define myMCPWM0_MCPWM3A_GPIO 4
#define myMCPWM0_MCPWM3A_PIN_CONFIG GPIO_4_MCPWM1_3A
//
// MCPWM1_3B - GPIO Settings
//
#define GPIO_PIN_MCPWM1_3B 5
#define myMCPWM0_MCPWM3B_GPIO 5
#define myMCPWM0_MCPWM3B_PIN_CONFIG GPIO_5_MCPWM1_3B

//
// MCPWM3 -> myMCPWM1 Pinmux
//
//
// MCPWM3_1A - GPIO Settings
//
#define GPIO_PIN_MCPWM3_1A 12
#define myMCPWM1_MCPWM1A_GPIO 12
#define myMCPWM1_MCPWM1A_PIN_CONFIG GPIO_12_MCPWM3_1A
//
// MCPWM3_1B - GPIO Settings
//
#define GPIO_PIN_MCPWM3_1B 29
#define myMCPWM1_MCPWM1B_GPIO 29
#define myMCPWM1_MCPWM1B_PIN_CONFIG GPIO_29_MCPWM3_1B

//
// Interrupt Confiugrations
//
void registerMcpwmInterrupts(){
    
    // Interrupt Settings for INT_myMCPWM0
    // ISR need to be defined for the registered interrupts
    Interrupt_register(INT_myMCPWM0, &INT_myMCPWM0_ISR);
    Interrupt_disable(INT_myMCPWM0);

    // Interrupt Settings for INT_myMCPWM1
    // ISR need to be defined for the registered interrupts
    Interrupt_register(INT_myMCPWM1, &INT_myMCPWM1_ISR);
    Interrupt_disable(INT_myMCPWM1);
}

//
// App function configureMcpwmPinmux - to configure the Pinmux for the MCPWM outputs
//
void configureMcpwmPinmux(void)
{
    //
    // Configure the Pinmux for the MCPWM outputs
    //

    //
    // MCPWM1 -> myMCPWM0 Pinmux
    //
    GPIO_setPinConfig(myMCPWM0_MCPWM1A_PIN_CONFIG);
    GPIO_setPadConfig(myMCPWM0_MCPWM1A_GPIO, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(myMCPWM0_MCPWM1A_GPIO, GPIO_QUAL_SYNC);

    GPIO_setPinConfig(myMCPWM0_MCPWM1B_PIN_CONFIG);
    GPIO_setPadConfig(myMCPWM0_MCPWM1B_GPIO, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(myMCPWM0_MCPWM1B_GPIO, GPIO_QUAL_SYNC);

    GPIO_setPinConfig(myMCPWM0_MCPWM2A_PIN_CONFIG);
    GPIO_setPadConfig(myMCPWM0_MCPWM2A_GPIO, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(myMCPWM0_MCPWM2A_GPIO, GPIO_QUAL_SYNC);

    GPIO_setPinConfig(myMCPWM0_MCPWM2B_PIN_CONFIG);
    GPIO_setPadConfig(myMCPWM0_MCPWM2B_GPIO, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(myMCPWM0_MCPWM2B_GPIO, GPIO_QUAL_SYNC);

    GPIO_setPinConfig(myMCPWM0_MCPWM3A_PIN_CONFIG);
    GPIO_setPadConfig(myMCPWM0_MCPWM3A_GPIO, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(myMCPWM0_MCPWM3A_GPIO, GPIO_QUAL_SYNC);

    GPIO_setPinConfig(myMCPWM0_MCPWM3B_PIN_CONFIG);
    GPIO_setPadConfig(myMCPWM0_MCPWM3B_GPIO, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(myMCPWM0_MCPWM3B_GPIO, GPIO_QUAL_SYNC);

    //
    // MCPWM3 -> myMCPWM1 Pinmux
    //
    GPIO_setPinConfig(myMCPWM1_MCPWM1A_PIN_CONFIG);
    GPIO_setPadConfig(myMCPWM1_MCPWM1A_GPIO, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(myMCPWM1_MCPWM1A_GPIO, GPIO_QUAL_SYNC);

    GPIO_setPinConfig(myMCPWM1_MCPWM1B_PIN_CONFIG);
    GPIO_setPadConfig(myMCPWM1_MCPWM1B_GPIO, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(myMCPWM1_MCPWM1B_GPIO, GPIO_QUAL_SYNC);
}

//
// App function initMyMCPWM0 - to initialize the myMCPWM0
//
void initMyMCPWM0(){

    /* Commenting out the reset default configs */

    //
    // Load Mode configurations
    //
    // - Global Load Mode: Disabled
    // - Time Base Load Mode: Disabled
    // - Counter Compare Load Mode: Freeze shadow to active load
    // - Action Qualifier Load Mode: Freeze shadow to active load
    // - Dead Band Load Mode: Freeze shadow to active load
    //

    MCPWM_disableGlobalLoad(myMCPWM0_BASE);

    MCPWM_setPeriodLoadMode(myMCPWM0_BASE, MCPWM_PERIOD_SHADOW_LOAD_DISABLE);

    MCPWM_setCounterCompareShadowLoadMode(myMCPWM0_BASE, MCPWM_COUNTER_COMPARE_1A, MCPWM_COMP_LOAD_FREEZE);
    MCPWM_setCounterCompareShadowLoadMode(myMCPWM0_BASE, MCPWM_COUNTER_COMPARE_1B, MCPWM_COMP_LOAD_FREEZE);
    MCPWM_setCounterCompareShadowLoadMode(myMCPWM0_BASE, MCPWM_COUNTER_COMPARE_2A, MCPWM_COMP_LOAD_FREEZE);
    MCPWM_setCounterCompareShadowLoadMode(myMCPWM0_BASE, MCPWM_COUNTER_COMPARE_2B, MCPWM_COMP_LOAD_FREEZE);
    MCPWM_setCounterCompareShadowLoadMode(myMCPWM0_BASE, MCPWM_COUNTER_COMPARE_3A, MCPWM_COMP_LOAD_FREEZE);
    MCPWM_setCounterCompareShadowLoadMode(myMCPWM0_BASE, MCPWM_COUNTER_COMPARE_3B, MCPWM_COMP_LOAD_FREEZE);

    MCPWM_setActionQualifierShadowLoadMode(myMCPWM0_BASE, MCPWM_ACTION_QUALIFIER_1A, MCPWM_AQ_LOAD_FREEZE);
    MCPWM_setActionQualifierShadowLoadMode(myMCPWM0_BASE, MCPWM_ACTION_QUALIFIER_1B, MCPWM_AQ_LOAD_FREEZE);
    MCPWM_setActionQualifierShadowLoadMode(myMCPWM0_BASE, MCPWM_ACTION_QUALIFIER_2A, MCPWM_AQ_LOAD_FREEZE);
    MCPWM_setActionQualifierShadowLoadMode(myMCPWM0_BASE, MCPWM_ACTION_QUALIFIER_2B, MCPWM_AQ_LOAD_FREEZE);
    MCPWM_setActionQualifierShadowLoadMode(myMCPWM0_BASE, MCPWM_ACTION_QUALIFIER_3A, MCPWM_AQ_LOAD_FREEZE);
    MCPWM_setActionQualifierShadowLoadMode(myMCPWM0_BASE, MCPWM_ACTION_QUALIFIER_3B, MCPWM_AQ_LOAD_FREEZE);

    MCPWM_setRisingEdgeDelayCountShadowLoadMode(myMCPWM0_BASE, MCPWM_RED_LOAD_FREEZE);
    MCPWM_setFallingEdgeDelayCountShadowLoadMode(myMCPWM0_BASE, MCPWM_FED_LOAD_FREEZE);

    // Time Base Configuration
    // -----------------------
    // Frequency        : 10000 Hz
    // Period           : 15999 TB Clocks
    // Phase Shift      : Disabled
    // Counter Mode     : Up - count mode
    // Prescaler        : Input Clock Divide clock by 1
    // Sync In Source   : Disabled
    // Sync Out Source  : Generated by software
    // Emulation Mode   : Stop after next Time Base counter increment or decrement
    //

    MCPWM_setEmulationMode(myMCPWM0_BASE, MCPWM_EMULATION_FREE_RUN);

    // MCPWM_setClockPrescaler(myMCPWM0_BASE, MCPWM_CLOCK_DIVIDER_1);
    MCPWM_setTimeBaseCounterMode(myMCPWM0_BASE, MCPWM_COUNTER_MODE_UP);
    MCPWM_setTimeBasePeriodActive(myMCPWM0_BASE, 15999);
    
    // MCPWM_setSyncInPulseSource(myMCPWM0_BASE, MCPWM_SYNC_IN_PULSE_SRC_DISABLE);
    // MCPWM_setSyncOutPulseMode(myMCPWM0_BASE, MCPWM_SYNC_OUT_PULSE_ON_SOFTWARE);
    // MCPWM_setSyncPulseSource(myMCPWM0_BASE, MCPWM_SYNC_PULSE_DISABLED);


    //
    // Counter Compare Values
    // ----------------------
    // PWM CMP A,B for PWM 1,2,3 :  50 % of TB Period Value or 7999
    // PWM CMP C,D               :  0 % of TB Period Value
    //
    //

    MCPWM_setCounterCompareActiveValue(myMCPWM0_BASE, MCPWM_COUNTER_COMPARE_1A, 7999);
    MCPWM_setCounterCompareActiveValue(myMCPWM0_BASE, MCPWM_COUNTER_COMPARE_1B, 7999);
    MCPWM_setCounterCompareActiveValue(myMCPWM0_BASE, MCPWM_COUNTER_COMPARE_2A, 7999);
    MCPWM_setCounterCompareActiveValue(myMCPWM0_BASE, MCPWM_COUNTER_COMPARE_2B, 7999);
    MCPWM_setCounterCompareActiveValue(myMCPWM0_BASE, MCPWM_COUNTER_COMPARE_3A, 7999);
    MCPWM_setCounterCompareActiveValue(myMCPWM0_BASE, MCPWM_COUNTER_COMPARE_3B, 7999);
    MCPWM_setCounterCompareActiveValue(myMCPWM0_BASE, MCPWM_COUNTER_COMPARE_C, 0);
    MCPWM_setCounterCompareActiveValue(myMCPWM0_BASE, MCPWM_COUNTER_COMPARE_D, 0);

    //
    // Action Qualifier Configurations
    // -------------------------------
    // PWM 1 Output A :
    //  - TB counter equals zero    : Set output pins to High
    //  - TB counter up equals CMPA    : Set output pins to low
    // PWM 1 Output B :
    //  - TB counter equals zero    : Set output pins to High
    //  - TB counter up equals CMPB    : Set output pins to low
    // PWM 2 Output A :
    //  - TB counter equals period    : Set output pins to low
    //  - TB counter up equals CMPA    : Set output pins to High
    // PWM 2 Output B :
    //  - TB counter equals period    : Set output pins to low
    //  - TB counter up equals CMPB    : Set output pins to High
    // PWM 3 Output A :
    //  - TB counter up equals CMPA    : Set output pins to High
    //  - TB counter up equals CMPB    : Set output pins to low
    // PWM 3 Output B :
    //  - TB counter up equals CMPA    : Set output pins to low
    //  - TB counter up equals CMPB    : Set output pins to High
    // 
    
    // PWM Output 1A
    MCPWM_setActionQualifierActionCompleteActive(myMCPWM0_BASE, MCPWM_AQ_OUTPUT_1A,
                                           MCPWM_AQ_OUTPUT_HIGH_ZERO |
                                           MCPWM_AQ_OUTPUT_NO_CHANGE_PERIOD |
                                           MCPWM_AQ_OUTPUT_LOW_UP_CMPA |
                                           MCPWM_AQ_OUTPUT_NO_CHANGE_DOWN_CMPA |
                                           MCPWM_AQ_OUTPUT_NO_CHANGE_UP_CMPB |
                                           MCPWM_AQ_OUTPUT_NO_CHANGE_DOWN_CMPB);

    // PWM Output 1B
    MCPWM_setActionQualifierActionCompleteActive(myMCPWM0_BASE, MCPWM_AQ_OUTPUT_1B,
                                           MCPWM_AQ_OUTPUT_HIGH_ZERO |
                                           MCPWM_AQ_OUTPUT_NO_CHANGE_PERIOD |
                                           MCPWM_AQ_OUTPUT_NO_CHANGE_UP_CMPA |
                                           MCPWM_AQ_OUTPUT_NO_CHANGE_DOWN_CMPA |
                                           MCPWM_AQ_OUTPUT_LOW_UP_CMPB |
                                           MCPWM_AQ_OUTPUT_NO_CHANGE_DOWN_CMPB);

    // PWM Output 2A
    MCPWM_setActionQualifierActionCompleteActive(myMCPWM0_BASE, MCPWM_AQ_OUTPUT_2A,
                                           MCPWM_AQ_OUTPUT_NO_CHANGE_ZERO |
                                           MCPWM_AQ_OUTPUT_LOW_PERIOD |
                                           MCPWM_AQ_OUTPUT_HIGH_UP_CMPA |
                                           MCPWM_AQ_OUTPUT_NO_CHANGE_DOWN_CMPA |
                                           MCPWM_AQ_OUTPUT_NO_CHANGE_UP_CMPB |
                                           MCPWM_AQ_OUTPUT_NO_CHANGE_DOWN_CMPB);

    // PWM Output 2B
    MCPWM_setActionQualifierActionCompleteActive(myMCPWM0_BASE, MCPWM_AQ_OUTPUT_2B,
                                           MCPWM_AQ_OUTPUT_NO_CHANGE_ZERO |
                                           MCPWM_AQ_OUTPUT_LOW_PERIOD |
                                           MCPWM_AQ_OUTPUT_NO_CHANGE_UP_CMPA |
                                           MCPWM_AQ_OUTPUT_NO_CHANGE_DOWN_CMPA |
                                           MCPWM_AQ_OUTPUT_HIGH_UP_CMPB |
                                           MCPWM_AQ_OUTPUT_NO_CHANGE_DOWN_CMPB);

    // PWM Output 3A
    MCPWM_setActionQualifierActionCompleteActive(myMCPWM0_BASE, MCPWM_AQ_OUTPUT_3A,
                                           MCPWM_AQ_OUTPUT_NO_CHANGE_ZERO |
                                           MCPWM_AQ_OUTPUT_NO_CHANGE_PERIOD |
                                           MCPWM_AQ_OUTPUT_HIGH_UP_CMPA |
                                           MCPWM_AQ_OUTPUT_NO_CHANGE_DOWN_CMPA |
                                           MCPWM_AQ_OUTPUT_LOW_UP_CMPB |
                                           MCPWM_AQ_OUTPUT_NO_CHANGE_DOWN_CMPB);

    // PWM Output 3B
    MCPWM_setActionQualifierActionCompleteActive(myMCPWM0_BASE, MCPWM_AQ_OUTPUT_3B,
                                           MCPWM_AQ_OUTPUT_NO_CHANGE_ZERO |
                                           MCPWM_AQ_OUTPUT_NO_CHANGE_PERIOD |
                                           MCPWM_AQ_OUTPUT_LOW_UP_CMPA |
                                           MCPWM_AQ_OUTPUT_NO_CHANGE_DOWN_CMPA |
                                           MCPWM_AQ_OUTPUT_HIGH_UP_CMPB |
                                           MCPWM_AQ_OUTPUT_NO_CHANGE_DOWN_CMPB);

    // MCPWM_setActionQualifierSWAction(myMCPWM0_BASE, MCPWM_AQ_OUTPUT_1A, MCPWM_AQ_SW_FORCE_DISABLED);
    // MCPWM_setActionQualifierSWAction(myMCPWM0_BASE, MCPWM_AQ_OUTPUT_1B, MCPWM_AQ_SW_FORCE_DISABLED);
    // MCPWM_setActionQualifierSWAction(myMCPWM0_BASE, MCPWM_AQ_OUTPUT_2A, MCPWM_AQ_SW_FORCE_DISABLED);
    // MCPWM_setActionQualifierSWAction(myMCPWM0_BASE, MCPWM_AQ_OUTPUT_2B, MCPWM_AQ_SW_FORCE_DISABLED);
    // MCPWM_setActionQualifierSWAction(myMCPWM0_BASE, MCPWM_AQ_OUTPUT_3A, MCPWM_AQ_SW_FORCE_DISABLED);
    // MCPWM_setActionQualifierSWAction(myMCPWM0_BASE, MCPWM_AQ_OUTPUT_3B, MCPWM_AQ_SW_FORCE_DISABLED);

    //
    // Dead Band configurations
    // ------------------------
    // Disabled
    // 

    // MCPWM_setDeadBandDelayMode(myMCPWM0_BASE, MCPWM_DB_RED, false);
    // MCPWM_setDeadBandDelayMode(myMCPWM0_BASE, MCPWM_DB_FED, false);

    //
    // Trip Zone Configurations
    // ------------------------
    // TZ OST source      :   No Source Selected
    // TZ CBC source      :   No Source Selected
    // TZ CBC Clear Source:   Disable action
    // TZ Action on A     :   Disable action
    // TZ Action on B     :   Disable action
    // 

    // MCPWM_selectTripZoneCBCEvent(myMCPWM0_BASE, MCPWM_TZ_CBC_PULSE_CLR_NONE);
    // MCPWM_setTripZoneAction(myMCPWM0_BASE, MCPWM_TZ_ACTION_EVENT_TZA, MCPWM_TZ_ACTION_DISABLE);
    // MCPWM_setTripZoneAction(myMCPWM0_BASE, MCPWM_TZ_ACTION_EVENT_TZB, MCPWM_TZ_ACTION_DISABLE);

    //
    // Events and Interrupts
    // ---------------------
    // SOCA Source   :   Event is Disabled
    // SOCB Source   :   Event is Disabled
    // SOCC Source   :   Event is Disabled
    // SOCD Source   :   Event is Disabled
    // ET1 Source   :   Time Base Counter equals Period  
    // ET1 Prescale :   5
    // ET2 Source   :   Event is Disabled
    // 
    // Interrupt Sources   :    "Interrupt Event Trigger 1 signal"
    // 
    
    // MCPWM_setADCTriggerSource(myMCPWM0_BASE, MCPWM_SOC_A, MCPWM_SOC_DISABLED);
    // MCPWM_setADCTriggerSource(myMCPWM0_BASE, MCPWM_SOC_B, MCPWM_SOC_DISABLED);
    // MCPWM_setADCTriggerSource(myMCPWM0_BASE, MCPWM_SOC_C, MCPWM_SOC_DISABLED);
    // MCPWM_setADCTriggerSource(myMCPWM0_BASE, MCPWM_SOC_D, MCPWM_SOC_DISABLED);
    MCPWM_setEventTriggerSource(myMCPWM0_BASE, MCPWM_ET_1, MCPWM_EVT_TBCTR_PERIOD);
    MCPWM_setEventTriggerEventPrescale(myMCPWM0_BASE, MCPWM_ET_1, 5);
    // MCPWM_setEventTriggerSource(myMCPWM0_BASE, MCPWM_ET_2, MCPWM_EVT_DISABLED);

    MCPWM_disableInterrupt(myMCPWM0_BASE, MCPWM_INT_SOURCE_ALL);
    MCPWM_enableInterrupt(myMCPWM0_BASE, MCPWM_INT_ET_1);
}

//
// App fucntion initMyMCPWM1 - to initialize the myMCPWM1
//
void initMyMCPWM1(){

    //
    // Load Mode configurations
    // 
    // Code Generated Uses Active Registers to write to.
    // 
    // Global Load Mode configurations
    // -------------------------------
    // Global Load          : Disabled. Individual Local Load Modes take Effect
    // Global Load Source   : Load on global force
    // Global Load Oneshot mode : Disabled
    // 
    // 
    // Time Base Load Mode configurations
    // ----------------------------------
    // Period Load Mode : PWM Period register load from Shadow register is disabled
    //
    // Counter Compare Registers Load Mode Configurations
    // --------------------------------------------------
    // PWM 1 CMP A :  Freeze shadow to active load
    // PWM 1 CMP B :  Freeze shadow to active load
    // 
    // Action Qualifier Registers Load Mode Configurations
    // --------------------------------------------------
    // PWM 1 AQ A :  Freeze shadow to active load
    // PWM 1 AQ B :  Freeze shadow to active load
    // 
    // Dead Band Registers Load Mode Configurations
    // --------------------------------------------
    // Dead Band RED Load Mode : Freeze shadow to active load
    // Dead Band FED Load Mode : Freeze shadow to active load
    // 
    // 

    MCPWM_disableGlobalLoad(myMCPWM1_BASE);

    MCPWM_setPeriodLoadMode(myMCPWM1_BASE, MCPWM_PERIOD_SHADOW_LOAD_DISABLE);

    MCPWM_setCounterCompareShadowLoadMode(myMCPWM1_BASE, MCPWM_COUNTER_COMPARE_1A, MCPWM_COMP_LOAD_FREEZE);
    MCPWM_setCounterCompareShadowLoadMode(myMCPWM1_BASE, MCPWM_COUNTER_COMPARE_1B, MCPWM_COMP_LOAD_FREEZE);

    MCPWM_setActionQualifierShadowLoadMode(myMCPWM1_BASE, MCPWM_ACTION_QUALIFIER_1A, MCPWM_AQ_LOAD_FREEZE);
    MCPWM_setActionQualifierShadowLoadMode(myMCPWM1_BASE, MCPWM_ACTION_QUALIFIER_1B, MCPWM_AQ_LOAD_FREEZE);

    MCPWM_setRisingEdgeDelayCountShadowLoadMode(myMCPWM1_BASE, MCPWM_RED_LOAD_FREEZE);
    MCPWM_setFallingEdgeDelayCountShadowLoadMode(myMCPWM1_BASE, MCPWM_FED_LOAD_FREEZE);

    //
    // Time Base Configurations
    // ------------------------ 
    // Frequency        : 10000 Hz
    // Period           : 8000 TB Clocks
    // Phase Shift      : Disabled
    // 
    // Counter Mode     : Up - down - count mode
    // Prescaler        : Input Clock Divide clock by 1
    // Sync In Source   : TODO
    // Sync Out Source  : Sync pulse is generated by software
    // Sync Per Source  : Disabled
    // 
    // Emulation Mode   : Stop after next Time Base counter increment or decrement
    // 

    // MCPWM_setEmulationMode(myMCPWM1_BASE, MCPWM_EMULATION_STOP_AFTER_NEXT_TB);

    // MCPWM_setClockPrescaler(myMCPWM1_BASE, MCPWM_CLOCK_DIVIDER_1);
    MCPWM_setTimeBaseCounterMode(myMCPWM1_BASE, MCPWM_COUNTER_MODE_UP_DOWN);
    MCPWM_setTimeBasePeriodActive(myMCPWM1_BASE, 8000);
    
    // MCPWM_setSyncInPulseSource(myMCPWM1_BASE, MCPWM_SYNC_IN_PULSE_SRC_DISABLE);
    // MCPWM_setSyncOutPulseMode(myMCPWM1_BASE, MCPWM_SYNC_OUT_PULSE_ON_SOFTWARE);
    // MCPWM_setSyncPulseSource(myMCPWM1_BASE, MCPWM_SYNC_PULSE_DISABLED);


    //
    // Counter Compare Values
    // ----------------------
    // PWM 1 CMP A : 0 or  0 % of TB Period Value
    // PWM 1 CMP B : 0 or  0 % of TB Period Value
    // CMP C : 4000 or  50 % of TB Period Value
    // CMP D : 4000 or  50 % of TB Period Value
    // 
    // 

    MCPWM_setCounterCompareActiveValue(myMCPWM1_BASE, MCPWM_COUNTER_COMPARE_1A, 0);
    MCPWM_setCounterCompareActiveValue(myMCPWM1_BASE, MCPWM_COUNTER_COMPARE_1B, 0);
    MCPWM_setCounterCompareActiveValue(myMCPWM1_BASE, MCPWM_COUNTER_COMPARE_C, 4000);
    MCPWM_setCounterCompareActiveValue(myMCPWM1_BASE, MCPWM_COUNTER_COMPARE_D, 4000);

    //
    // Action Qualifier Configurations
    // -------------------------------
    // PWM 1 Output A :
    //  - TB counter up equals CMPA    : Set output pins to High
    //  - TB counter down equals CMPA    : Set output pins to low
    // PWM 1 Output B :
    //  - TB counter up equals CMPB    : Set output pins to High
    //  - TB counter down equals CMPB    : Set output pins to low
    // 
    // 
    // PWM Output A
    MCPWM_setActionQualifierActionCompleteActive(
        myMCPWM1_BASE,
        MCPWM_AQ_OUTPUT_1A,
        MCPWM_AQ_OUTPUT_NO_CHANGE_ZERO |
        MCPWM_AQ_OUTPUT_NO_CHANGE_PERIOD |
        MCPWM_AQ_OUTPUT_HIGH_UP_CMPA |
        MCPWM_AQ_OUTPUT_LOW_DOWN_CMPA |
        MCPWM_AQ_OUTPUT_NO_CHANGE_UP_CMPB |
        MCPWM_AQ_OUTPUT_NO_CHANGE_DOWN_CMPB
    );

    // PWM Output B
    MCPWM_setActionQualifierActionCompleteActive(
        myMCPWM1_BASE,
        MCPWM_AQ_OUTPUT_1B,
        MCPWM_AQ_OUTPUT_NO_CHANGE_ZERO |
        MCPWM_AQ_OUTPUT_NO_CHANGE_PERIOD |
        MCPWM_AQ_OUTPUT_NO_CHANGE_UP_CMPA |
        MCPWM_AQ_OUTPUT_NO_CHANGE_DOWN_CMPA |
        MCPWM_AQ_OUTPUT_HIGH_UP_CMPB |
        MCPWM_AQ_OUTPUT_LOW_DOWN_CMPB
    );
    
    // MCPWM_setActionQualifierSWAction(myMCPWM1_BASE, MCPWM_AQ_OUTPUT_1A, MCPWM_AQ_SW_FORCE_DISABLED);
    // MCPWM_setActionQualifierSWAction(myMCPWM1_BASE, MCPWM_AQ_OUTPUT_1B, MCPWM_AQ_SW_FORCE_DISABLED);

    //
    // Dead Band configurations
    // ------------------------
    // Configuration Selected  : Custom
    // Rising Edge Delay       : Disabled
    // Falling Edge Delay      : Disabled
    // Swap Output A           : Not Swapped
    // Swap Output B           : Not Swapped
    // 
    // 

    // MCPWM_setDeadBandDelayMode(myMCPWM1_BASE, MCPWM_DB_RED, false);
    // MCPWM_setDeadBandDelayMode(myMCPWM1_BASE, MCPWM_DB_FED, false);

    //
    // Trip Zone Configurations
    // ------------------------
    // TZ OST source      :   No Source Selected
    // TZ CBC source      :   No Source Selected
    // TZ CBC Clear Source:   Disable action
    // TZ Action on A     :   Disable action
    // TZ Action on B     :   Disable action
    // 

    // MCPWM_selectTripZoneCBCEvent(myMCPWM1_BASE, MCPWM_TZ_CBC_PULSE_CLR_NONE);
    // MCPWM_setTripZoneAction(myMCPWM1_BASE, MCPWM_TZ_ACTION_EVENT_TZA, MCPWM_TZ_ACTION_DISABLE);
    // MCPWM_setTripZoneAction(myMCPWM1_BASE, MCPWM_TZ_ACTION_EVENT_TZB, MCPWM_TZ_ACTION_DISABLE);

    //
    // Events and Interrupts
    // ---------------------
    // SOCA Source   :   Event is Disabled
    // SOCB Source   :   Event is Disabled
    // SOCC Source   :   Event is Disabled
    // SOCD Source   :   Event is Disabled
    // ET1 Source   :   Time Base Counter equals Period
    // ET1 Prescale :   5
    // ET2 Source   :   Event is Disabled
    // 
    // Interrupt Sources   :    "Interrupt Event Trigger 1 signal"
    // 
    
    // MCPWM_setADCTriggerSource(myMCPWM1_BASE, MCPWM_SOC_A, MCPWM_SOC_DISABLED);
    // MCPWM_setADCTriggerSource(myMCPWM1_BASE, MCPWM_SOC_B, MCPWM_SOC_DISABLED);
    // MCPWM_setADCTriggerSource(myMCPWM1_BASE, MCPWM_SOC_C, MCPWM_SOC_DISABLED);
    // MCPWM_setADCTriggerSource(myMCPWM1_BASE, MCPWM_SOC_D, MCPWM_SOC_DISABLED);
    MCPWM_setEventTriggerSource(myMCPWM1_BASE, MCPWM_ET_1, MCPWM_EVT_TBCTR_PERIOD);
    MCPWM_setEventTriggerEventPrescale(myMCPWM1_BASE, MCPWM_ET_1, 5);
    // MCPWM_setEventTriggerSource(myMCPWM1_BASE, MCPWM_ET_2, MCPWM_EVT_DISABLED);

    MCPWM_disableInterrupt(myMCPWM1_BASE, MCPWM_INT_SOURCE_ALL);
    MCPWM_enableInterrupt(myMCPWM1_BASE, MCPWM_INT_ET_1);
}

