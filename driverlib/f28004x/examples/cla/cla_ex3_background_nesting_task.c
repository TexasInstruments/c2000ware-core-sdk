//#############################################################################
//
// FILE:   cla_ex3_background_nesting_task.c
//
// TITLE:  CLA background nesting task
//
//! \addtogroup driver_example_list
//! <h1> CLA background nesting task </h1>
//!
//! This example configures CLA task 1 to be triggered by EPWM1 running at
//! 2 Hz (period = 0.5s). A background task is configured to be triggered by CPU
//! timer running at .5 Hz (period = 2s).
//! CLA task 1 toggles LED1 at the start and end of the task and the background 
//! task toggles LED2 at the start and end of the task. Background task will be
//! preempted by Task1 and hence LED1 will be toggling even while LED2 is ON.
//!
//! Note that the compile flag cla_background_task is turned on in this project.
//! Enabling background task adds additional context save/restore cycles during
//! task switching thus increasing the overall trigger-to-task latency.
//! If the application does not use the background CLA task, it is recommended
//! to turn this flag off for better performance.
//! The option is available in Project Properties -> C2000 Build ->
//! C2000 Compiler -> Advanced Options -> Runtime Model Options.
//!
//! \b External \b Connections \n
//!  - None
//!
//! \b Watch \b Variables \n
//!  - None
//!
//###########################################################################
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
//###########################################################################

//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "cla_ex3_background_nesting_task_shared.h"
#include "board.h"

//
// Defines
//
#define EPWM_CLKDIV        1792UL
#define EPWM1_FREQ         2UL
#define EPWM1_PERIOD  (uint16_t)(DEVICE_SYSCLK_FREQ /(EPWM_CLKDIV * EPWM1_FREQ))

//
// Defines
//
#define WAITSTEP    __asm(" RPT #255||NOP")
#define EPSILON     1e-1

//
// Globals
//

//
// Function Prototypes
//
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
    // Configure the LEDs
    //
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_LED1, GPIO_DIR_MODE_OUT);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_LED2, GPIO_DIR_MODE_OUT);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_LED1, GPIO_QUAL_SYNC);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_LED2, GPIO_QUAL_SYNC);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_LED1);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_LED2);

    GPIO_setControllerCore(DEVICE_GPIO_PIN_LED1, GPIO_CORE_CPU1_CLA1);
    GPIO_setControllerCore(DEVICE_GPIO_PIN_LED2, GPIO_CORE_CPU1_CLA1);

    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    // initialize CPU timers

    // Initialize timer period : 2 seconds

    CPUTimer_setPeriod(CPUTIMER1_BASE, DEVICE_SYSCLK_FREQ * 2);

    // Initialize pre-scale counter to divide by 1 (SYSCLKOUT)
    CPUTimer_setPreScaler(CPUTIMER1_BASE, 0);
    // Make sure timer is stopped
    CPUTimer_stopTimer(CPUTIMER1_BASE);
    CPUTimer_setEmulationMode(CPUTIMER1_BASE,
                              CPUTIMER_EMULATIONMODE_RUNFREE);
    // Enables CPU timer interrupt.
    CPUTimer_enableInterrupt(CPUTIMER1_BASE);
    // Starts(restarts) CPU timer.
    CPUTimer_startTimer(CPUTIMER1_BASE);

    //
    // Initialize resources
    //
    Board_init();

    //
    // Disable sync(Freeze clock to PWM as well)
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);
    initEPWM();

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
//
// Description: EPWM1A will run at EPWM1_FREQ Hz and trigger CLA Task1
// The default time base for the EPWM module is half the system clock i.e.
// TBCLK = SYSCLKOUT
// EPWM1A will be setup in count-up mode and an event generated every period
//
void initEPWM(void)
{
    //
    // Set up EPWM1 to
    // - run on a base clock of SYSCLK/128 / 14
    // - have a period of EPWM1_PERIOD
    // - run in count up mode
    //
    EPWM_setClockPrescaler(EPWM1_BASE, EPWM_CLOCK_DIVIDER_128,
                           EPWM_HSCLOCK_DIVIDER_14);
    EPWM_setTimeBasePeriod(EPWM1_BASE, EPWM1_PERIOD);
    EPWM_setTimeBaseCounterMode(EPWM1_BASE, EPWM_COUNTER_MODE_UP);
    EPWM_setTimeBaseCounter(EPWM1_BASE, 0U);

    //
    // Enable INT, generate INT on 1st event
    //
    EPWM_setInterruptSource(EPWM1_BASE, EPWM_INT_TBCTR_ZERO);
    EPWM_enableInterrupt(EPWM1_BASE);
    EPWM_setInterruptEventCount(EPWM1_BASE, 1U);

    //
    // EPWM 1 should Stop when counter completes whole cycle in emulation mode
    //
    EPWM_setEmulationMode(EPWM1_BASE, EPWM_EMULATION_STOP_AFTER_FULL_CYCLE);
}


//
// End of File
//
