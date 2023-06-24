//#############################################################################
//
// FILE:   interrupt_ex3_sw_prioritization.c
//
// TITLE:  CPU Timer Interrupt Software Prioritization
//
//! \addtogroup driver_example_list
//! <h1> CPU Timer Interrupt Software Prioritization </h1>
//!
//! This examples demonstrates the software prioritization of interrupts
//! through CPU Timer Interrupts. Software prioritization of interrupts is
//! achieved by enabling interrupt nesting.
//!
//! In this device, hardware priorities for CPU Timer 0, 1 and 2 are set
//! as timer 0 being highest priority and timer 2 being lowest priority.
//! This example configures CPU Timer0, 1, and 2 priority in software with
//! timer 2 priority being highest and timer 0 being lowest in software and
//! prints a trace for the order of execution.
//!
//! For most applications, the hardware prioritizing of the interrupts is
//! sufficient. For applications that need custom prioritizing, this example
//! illustrates how this can be done through software.User specific priorities
//! can be configured in sw_prioritized_isr_level.h header file.
//!
//! To enable interrupt nesting, following sequence needs to followed in ISRs.
//! <b>Step 1:</b> Set the global priority:
//! Modify the IER register to allow CPU interrupts with a higher user
//! priority to be serviced.
//! Note: at this time IER has already been saved on the stack.
//! <b>Step 2:</b> Set the group priority: (optional)
//! Modify the appropriate PIEIERx register to allow group interrupts with a
//! higher user set priority to be serviced. Do NOT clear PIEIER register bits
//! from another group other than that being serviced by this ISR. Doing so
//! can cause erroneous interrupts to occur.
//! <b>Step 3:</b> Enable interrupts: There are three steps to do this:
//!         a. Clear the PIEACK bits
//!         b. Wait at least one cycle
//!         c. Clear the INTM bit.
//! <b>Step 4:</b> Run the main part of the ISR
//! <b>Step 5:</b> Set INTM to disable interrupts.
//! <b>Step 6:</b> Restore PIEIERx (optional depending on step 2)
//! <b>Step 7:</b> Return from ISR
//!
//! Refer to below link on more details on Interrupt nesting in C28x devices:
//! <C2000Ware>\docs\c28x_interrupt_nesting\html\index.html
//!
//! \b External \b Connections \n
//!  - None
//!
//! \b Watch \b Variables \n
//! - traceISR - shows the order in which ISRs are executed.
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
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "sw_prioritized_isr_levels.h"

//
// Defines
//
#define TRACE_SIZE  51U

//
// Globals
//
uint16_t cpuTimer0IntCount;
uint16_t cpuTimer1IntCount;
uint16_t cpuTimer2IntCount;

//
// This array will be used as a trace to check the
// order that the interrupts were serviced
//
uint16_t  traceISR[TRACE_SIZE];

//
// Index to update an element in the trace buffer
//
uint16_t  traceISRIndex = 0;

//
// Function Prototypes
//
__interrupt void cpuTimer0ISR(void);
__interrupt void cpuTimer1ISR(void);
__interrupt void cpuTimer2ISR(void);
void initCPUTimers(void);
void configCPUTimer(uint32_t, float, float);

//
// Main
//
void main(void)
{
    uint32_t i;

    //
    // Initializes device clock and peripherals
    //
    Device_init();

    //
    // Configures the GPIO pin as a push-pull output
    //
    Device_initGPIO();
    GPIO_setPinConfig(DEVICE_GPIO_CFG_LED1);
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
    // Reset the ISR trace
    //
    for(i = 0; i < TRACE_SIZE; i++)
    {
       traceISR[i] = 0;
    }

    //
    // Initializes the Device Peripheral. For this example, only initialize the
    // Cpu Timers.
    //
    initCPUTimers();

    //
    // Configure CPU-Timer 0, 1, and 2 to interrupt every second:
    // 1 second Period (in uSeconds)
    //
    configCPUTimer(CPUTIMER0_BASE, DEVICE_SYSCLK_FREQ, 1000000);
    configCPUTimer(CPUTIMER1_BASE, DEVICE_SYSCLK_FREQ, 1000000);
    configCPUTimer(CPUTIMER2_BASE, DEVICE_SYSCLK_FREQ, 1000000);

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
    // Make sure timer is stopped
    //
    CPUTimer_stopTimer(CPUTIMER0_BASE);
    CPUTimer_stopTimer(CPUTIMER1_BASE);
    CPUTimer_stopTimer(CPUTIMER2_BASE);

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
// period specified by the "freq" and "period" parameters. The "freq" is
// entered as Hz and the period in uSeconds. The timer is held in the stopped
// state after configuration.
//
void
configCPUTimer(uint32_t cpuTimer, float freq, float period)
{
    uint32_t temp;

    //
    // Initialize timer period:
    //
    temp = (uint32_t)(freq / 1000000 * period);
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
__interrupt void
cpuTimer0ISR(void)
{
    //
    // Save IER register on stack
    //
    volatile uint16_t tempPIEIER = HWREGH(PIECTRL_BASE + PIE_O_IER1);

    //
    // Set the global and group priority to allow CPU interrupts
    // with higher priority
    //
    IER |= M_INT1;
    IER &= MINT1;
    HWREGH(PIECTRL_BASE + PIE_O_IER1) &= MG1_7;

    //
    // Enable Interrupts
    //
    Interrupt_clearACKGroup(0xFFFFU);
    __asm("  NOP");
    EINT;

    //
    // Insert ISR code here
    //
    cpuTimer0IntCount++;

    //
    // Disable interrupts and restore registers saved:
    //
    DINT;
    HWREGH(PIECTRL_BASE + PIE_O_IER1) = tempPIEIER;

    //
    //  Add ISR to Trace
    //
    traceISR[traceISRIndex % TRACE_SIZE] = 0x0017;
    traceISRIndex++;
}

//
// cpuTimer1ISR - Counter for CpuTimer1
//
__interrupt void
cpuTimer1ISR(void)
{
    //
    // Set the global priority to allow CPU interrupts with higher priority
    //
    IER &= MINT13;
    EINT;

    //
    // Insert ISR code here
    //
    cpuTimer1IntCount++;

    //
    // Disable Interrupts
    //
    DINT;

    //
    //  Add ISR to Trace
    //
    traceISR[traceISRIndex % TRACE_SIZE] = 0x00D0;
    traceISRIndex++;
}

//
// cpuTimer2ISR - Counter for CpuTimer2
//
__interrupt void
cpuTimer2ISR(void)
{
    IER &= MINT14;                 // Set "global" priority
    EINT;

    //
    // Insert ISR code here
    //
    cpuTimer2IntCount++;

    //
    // Disable interrupts
    //
    DINT;

    //
    //  Add ISR to Trace
    //
    traceISR[traceISRIndex % TRACE_SIZE] = 0x00E0;
    traceISRIndex++;
}

//
// End of File
//
