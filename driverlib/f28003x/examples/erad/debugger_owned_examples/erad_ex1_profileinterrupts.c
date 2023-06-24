//#############################################################################
//
// FILE:    erad_ex1_profileinterrupts.c
//
// TITLE:   ERAD Profiling Interrupts Example
//
//! \addtogroup driver_example_list
//! <h1> ERAD Profiling Interrupts </h1>
//!
//! This example configures CPU Timer0, 1, and 2 to be profiled using the ERAD
//! module. Included is a JavaScript file, profile_interrupts.js, which is used
//! with the scripting console to program ERAD registers and view profiling
//! data.
//!
//! To properly use the provided ERAD script, the following variables must be
//! set in the scripting environment prior to launching the ERAD script:
//!
//! - var PROJ_NAME = "erad_debugger_ex1_profileinterrupts"
//! - var PROJ_WKSPC_LOC = "<proj_workspace_path>"
//! - var PROJ_CONFIG = "<name of active configuration [CPU1_FLASH|CPU1_RAM]>"
//!
//! To run the ERAD script, use the following command in the scripting console:
//!
//! - loadJSFile("<proj_workspace_path>\\erad_debugger_ex1_profileinterrupts\\erad_ex1_profile_interrupts.js", 0);
//!
//! The included JavaScript file, erad_ex1_profile_interrupts.js, uses Debug Server
//! Scripting (DSS) features. For information on using the DSS, please visit:
//! http://software-dl.ti.com/ccs/esd/documents/users_guide/sdto_dss_handbook.html
//!
//! Note that the script must be run after loading and running the .out on the
//! C28x core. Only CPU timer 2 ISR is profiled in this example.
//!
//! This example uses 2 HW breakpoints and 4 counters:
//!  - HWBP_1 : PC = start address of cpuTimer2ISR
//!  - HWBP_2 : PC = end address of cpuTimer2ISR
//!  - CTM_1  : Used to count the cpuTimer2ISR execution cycles.
//!             Configured in start-stop mode with start event as HWBP_1 and
//!             stop event as HWBP_2
//!  - CTM_2  : Used to count the number of times the system event TIMER2_TINT2
//!             has occurred.
//!             Configured in rising-edge count mode with counting input as
//!             system event TIMER2_TINT2 (INP_SEL[25])
//!  - CTM_3  : Used to count the number of times cputTimer2ISR executes.
//!             Configured in rising-edge count mode with counting input as
//!             HWBP_1 (INP_SEL[0])
//!  - CTM_4  : Used to count the latency from the system event TIMER2_TINT2 to
//!             cpuTimer2ISR entry.
//!             Configured in start-stop mode with start event as TIMER2_TINT2
//!             and stop event as HWBP_1
//!
//! \b External \b Connections \n
//!  - None
//!
//! \b Watch \b Variables \n
//!  - cpuTimer0IntCount
//!  - cpuTimer1IntCount
//!  - cpuTimer2IntCount
//!
//! \b Profiling \b Script \b Output
//!  - Current ISR cycle count (CTM_1)
//!  - Max ISR cycle count (maximum value of CTM_1)
//!  - Interrupt occurrence count (CTM_2)
//!  - ISR execution count (CTM_3)
//!  - ISR entry delay cycle count (maximum value of CTM_4)
//!
//! Note that the large difference between Interrupt occurrence count (CTM_2)
//! and ISR execution count (CTM_3) is because the ISR takes more number of
//! cycles than the actual interrupt period. ISR entry delay cycle count will
//! also be higher due to the same reason.
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
#include <stdint.h>
#include <float.h>
#include <math.h>
#include "driverlib.h"
#include "device.h"

//
// Globals
//
uint64_t cpuTimer0IntCount;
uint64_t cpuTimer1IntCount;
uint64_t cpuTimer2IntCount;

//
// Pre-chosen Pseudo Random Generator constants
//
const uint16_t PseudoRand_multiplier = 31821;
const uint16_t PseudoRand_increment = 13849;
uint16_t PseudoRand_seed = 21845;

//
// Function Prototypes
//
interrupt void cpuTimer0ISR(void) __attribute__((ramfunc));
interrupt void cpuTimer1ISR(void) __attribute__((ramfunc));
interrupt void cpuTimer2ISR(void) __attribute__((ramfunc));
void initCPUTimers(void);
void configCPUTimer(uint32_t, float, float);
uint16_t generatePseudoRand16(uint16_t *);

//
// Main
//
void main(void)
{
    //
    // Initializes device clock and peripherals
    //
    Device_init();

    //
    // Configures the GPIO pin as a push-pull output
    //
    Device_initGPIO();
    GPIO_setPinConfig(DEVICE_GPIO_PIN_LED1);
    GPIO_setMasterCore(DEVICE_GPIO_PIN_LED1, GPIO_CORE_CPU1);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_LED1, GPIO_PIN_TYPE_STD);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_LED1, GPIO_DIR_MODE_OUT);

    //
    // Initializes PIE and clears PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initializes the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // ISRs for each CPU Timer interrupt
    //
    Interrupt_register(INT_TIMER0, &cpuTimer0ISR);
    Interrupt_register(INT_TIMER1, &cpuTimer1ISR);
    Interrupt_register(INT_TIMER2, &cpuTimer2ISR);

    //
    // Initializes the Device Peripheral. For this example, only initialize the
    // Cpu Timers.
    //
    initCPUTimers();

    //
    // Configure CPU-Timer 0, 1, and 2 to interrupt every 1066,
    // 1776 and 2001 cycles
    //
    configCPUTimer(CPUTIMER0_BASE, DEVICE_SYSCLK_FREQ, 10.66);
    configCPUTimer(CPUTIMER1_BASE, DEVICE_SYSCLK_FREQ, 17.76);
    configCPUTimer(CPUTIMER2_BASE, DEVICE_SYSCLK_FREQ, 20.01);

    //
    // To ensure precise timing, use write-only instructions to write to the
    // entire register. Therefore, if any of the configuration bits are changed
    // in configCPUTimer and initCPUTimers, the below settings must also
    // be updated.
    //
    CPUTimer_enableInterrupt(CPUTIMER0_BASE);
    CPUTimer_enableInterrupt(CPUTIMER1_BASE);
    CPUTimer_enableInterrupt(CPUTIMER2_BASE);

    //
    // Enables CPU int1, int13, and int14 which are connected to CPU-Timer 0,
    // CPU-Timer 1, and CPU-Timer 2 respectively.
    // Enable TINT0 in the PIE: Group 1 interrupt 7
    //
    Interrupt_enable(INT_TIMER0);
    Interrupt_enable(INT_TIMER1);
    Interrupt_enable(INT_TIMER2);

    //
    // Starts CPU-Timer 0, CPU-Timer 1, and CPU-Timer 2.
    //
    CPUTimer_startTimer(CPUTIMER0_BASE);
    CPUTimer_startTimer(CPUTIMER1_BASE);
    CPUTimer_startTimer(CPUTIMER2_BASE);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // IDLE loop. Just sit and loop forever (optional)
    //
    while(1)
    {
    }
}

//
// initCPUTimers - This function initializes all three CPU timers
// to a known state.
//
void
initCPUTimers(void)
{
    //
    // Make sure timer is stopped
    //
    CPUTimer_stopTimer(CPUTIMER0_BASE);
    CPUTimer_stopTimer(CPUTIMER1_BASE);
    CPUTimer_stopTimer(CPUTIMER2_BASE);

    //
    // Initialize timer period to maximum
    //
    CPUTimer_setPeriod(CPUTIMER0_BASE, 0xFFFFFFFF);
    CPUTimer_setPeriod(CPUTIMER1_BASE, 0xFFFFFFFF);
    CPUTimer_setPeriod(CPUTIMER2_BASE, 0xFFFFFFFF);

    //
    // Initialize pre-scale counter to divide by 1 (SYSCLKOUT)
    //
    CPUTimer_setPreScaler(CPUTIMER0_BASE, 0);
    CPUTimer_setPreScaler(CPUTIMER1_BASE, 0);
    CPUTimer_setPreScaler(CPUTIMER2_BASE, 0);

    //
    // Reload all counter register with period value
    //
    CPUTimer_reloadTimerCounter(CPUTIMER0_BASE);
    CPUTimer_reloadTimerCounter(CPUTIMER1_BASE);
    CPUTimer_reloadTimerCounter(CPUTIMER2_BASE);

    //
    // Reset interrupt counter
    //
    cpuTimer0IntCount = 0;
    cpuTimer1IntCount = 0;
    cpuTimer2IntCount = 0;
}

//
// configCPUTimer - This function initializes the selected timer to the
// period specified by the "Freq" and "Period" parameters. The "Freq" is
// entered as "Hz" and the period in "uSeconds". The timer is held in the
// stopped state after configuration.
//
void
configCPUTimer(uint32_t cpuTimer, float freq, float period)
{
    uint32_t temp;

    //
    // Initialize timer period:
    //
    temp = (uint32_t) (freq / 1000000 * period);
    CPUTimer_setPeriod(cpuTimer, temp);

    //
    // Set pre-scale counter to divide by 1 (SYSCLKOUT):
    //
    CPUTimer_setPreScaler(cpuTimer, 0);

    //
    // Initializes timer control register. The timer is stopped, reloaded,
    // free run disabled, and interrupt enabled.
    // Additionally, the free and soft bits are set
    //
    CPUTimer_stopTimer(cpuTimer);
    CPUTimer_reloadTimerCounter(cpuTimer);
    CPUTimer_setEmulationMode(cpuTimer,
              CPUTIMER_EMULATIONMODE_STOPAFTERNEXTDECREMENT);
    CPUTimer_enableInterrupt(cpuTimer);

    //
    // Resets interrupt counters for the three cpuTimers
    //
    if (cpuTimer == CPUTIMER0_BASE)
    {
        cpuTimer0IntCount = 0;
    }
    else if(cpuTimer == CPUTIMER1_BASE)
    {
        cpuTimer1IntCount = 0;
    }
    else if(cpuTimer == CPUTIMER2_BASE)
    {
        cpuTimer2IntCount = 0;
    }
}

//
// cpuTimer0ISR - Counter for CpuTimer0
//
interrupt void
cpuTimer0ISR(void)
{
    cpuTimer0IntCount++;

    //
    // Acknowledge this interrupt to receive more interrupts from group 1
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
}

//
// cpuTimer1ISR - Counter for CpuTimer1
//
interrupt void
cpuTimer1ISR(void)
{
    //
    // The CPU acknowledges the interrupt.
    //
    cpuTimer1IntCount++;
}

//
// cpuTimer2ISR - Counter for CpuTimer2
//
interrupt void
cpuTimer2ISR(void)
{
    //
    // Simulate storing data to a location. "volatile" keyword ensures this is
    // not optimized out by the compiler.
    //
    volatile uint32_t output;

    //
    // Generate a random number.
    //
    uint16_t count = generatePseudoRand16(&PseudoRand_seed);

    //
    // Simulate a task that can take some time to complete. Loop a "random"
    // number of times and store values to a location.
    //
    uint32_t i;
    for(i = 0; i < count; i++)
    {
        output = i;
    }

    //
    // The CPU acknowledges the interrupt.
    //
    cpuTimer2IntCount++;
}

//
// generatePseudoRand16 - Generate a pseudo random 16-bit number by passing a
// start value or "seed". This generator is a linear congruential pseudo random
// generator, which is very fast. The basic calculation is:
//
// randNum(n) = ((randNum(n-1) * multiplier) + increment) modulo M
//
uint16_t
generatePseudoRand16(uint16_t *seed)
{
    //
    // Perform calculation. Mask off bottom bits in lieu of modulus operation
    //
    *seed = ((uint32_t)*seed * PseudoRand_multiplier + PseudoRand_increment)
            & 0xFFFF;
    return(*seed);
}

//
// End of File
//
