//#############################################################################
//
// FILE:   cla_ex4_pwm_control.c
//
// TITLE:  Controlling PWM output using CLA
//
//! \addtogroup driver_example_list
//! <h1> Controlling PWM output using CLA </h1>
//!
//! This example showcases how to update PWM signal output using CLA.
//! EPWM1 is configured to generate complementary signals on both of its
//! channels of fixed frequency 100 KHz. EPWM4 is configured to trigger
//! a periodic CLA control task of frequency 10 KHz. The CLA task implements
//! a very simple logic to vary the duty of the EPWM1 outputs by increasing it
//! by 0.1 in every iteration and maintaining it in the range of 0.1-0.9. For
//! actual use-cases, the control logic could be modified to much more complex
//! depending upon the application. The other CLA task (CLA task 8) is
//! triggered by software at beginning to initialize the CLA global variables
//!
//! \b External \b Connections \n
//!  - Observe GPIO0 (EPWM1A) on oscilloscope
//!  - Observe GPIO1 (EPWM1B) on oscilloscope
//!
//! \b Watch \b Variables \n
//!  - duty
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
// Included Files
//
#include <cla_ex4_pwm_control_shared.h>
#include "driverlib.h"
#include "device.h"
#include "board.h"

//
// Function Prototypes
//
void initEPWM(void);
void initCLA(void);

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
    // GPIO0 is set to EPWM1A
    // GPIO1 is set to EPWM1B
    //
    GPIO_setControllerCore(0, GPIO_CORE_CPU1);
    GPIO_setPadConfig(0,GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_0_EPWM1_A);
    GPIO_setControllerCore(1, GPIO_CORE_CPU1);
    GPIO_setPadConfig(1,GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_1_EPWM1_B);

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
    // Initialize EPWM module
    //
    initEPWM();

    //
    // Initialize resources
    //
    Board_init();
    initCLA();

    //
    // Enable global interrupts.
    //
    EINT;

    //
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    for(;;)
    {

    }
}


//
// EPWM Initialization
// EPWM1 : generates output of frequency EPWM1_FREQ (100 KHz)
// EPWM4 : Triggers CLA task at frequency EPWM4_FREQ (10 KHz)
//
void initEPWM(void)
{
    //
    // Set up EPWM1 to
    // - run on a base clock of SYSCLK
    // - have a period of EPWM1_PERIOD
    // - run in count up-down mode
    //
    EPWM_setClockPrescaler(EPWM1_BASE, EPWM_CLOCK_DIVIDER_1,
                           EPWM_HSCLOCK_DIVIDER_1);
    EPWM_setTimeBasePeriod(EPWM1_BASE, EPWM1_PERIOD);
    EPWM_setCounterCompareValue(EPWM1_BASE, EPWM_COUNTER_COMPARE_A, EPWM1_PERIOD/10U);
    EPWM_setTimeBaseCounterMode(EPWM1_BASE, EPWM_COUNTER_MODE_UP_DOWN);
    EPWM_setTimeBaseCounter(EPWM1_BASE, 0U);

    //
    // Configuring action-qualifiers for EPWM1 to generate symmetric
    // and complementary outputs on channel A and B
    //
    EPWM_setActionQualifierAction(EPWM1_BASE, EPWM_AQ_OUTPUT_A,
                         EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    EPWM_setActionQualifierAction(EPWM1_BASE, EPWM_AQ_OUTPUT_A,
                             EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    EPWM_setActionQualifierAction(EPWM1_BASE, EPWM_AQ_OUTPUT_B,
                             EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    EPWM_setActionQualifierAction(EPWM1_BASE, EPWM_AQ_OUTPUT_B,
                             EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);

    //
    // Enabling Counter Compare shadow mode
    //
    EPWM_setCounterCompareShadowLoadMode(EPWM1_BASE, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_SYNC_CNTR_ZERO);

    //
    // Set up EPWM4 to
    // - run on a base clock of SYSCLK
    // - have a period of EPWM4_PERIOD
    // - run in count up mode
    EPWM_setClockPrescaler(EPWM4_BASE, EPWM_CLOCK_DIVIDER_1,
                           EPWM_HSCLOCK_DIVIDER_1);
    EPWM_setTimeBasePeriod(EPWM4_BASE, EPWM4_PERIOD);
    EPWM_setTimeBaseCounterMode(EPWM4_BASE, EPWM_COUNTER_MODE_UP);
    EPWM_setTimeBaseCounter(EPWM4_BASE, 0U);

    //
    // Enabling EPWM4 interrupt at TBCTR = 0 to trigger
    // CLA task
    //
    EPWM_setInterruptSource(EPWM4_BASE, EPWM_INT_TBCTR_ZERO);
    EPWM_enableInterrupt(EPWM4_BASE);
    EPWM_setInterruptEventCount(EPWM4_BASE, 1U);

    //
    // EPWM 1 and 4 should run freely in emulation mode
    //
    EPWM_setEmulationMode(EPWM1_BASE, EPWM_EMULATION_FREE_RUN);
    EPWM_setEmulationMode(EPWM4_BASE, EPWM_EMULATION_FREE_RUN);
}

//
// CLA Initialization
//
void initCLA(void)
{
    //
    // Force task 8, the one time initialization task
    //
    CLA_forceTasks(CLA1_BASE, CLA_TASKFLAG_8);
}


