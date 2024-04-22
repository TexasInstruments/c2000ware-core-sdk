//#############################################################################
//
// FILE:   memcfg_ex1_sysconfig_cpu2.c
//
// TITLE: SysConfig RAM Management Example
//
//! \addtogroup driver_dual_example_list
//! <h1> LED Blinky Example</h1>
//!
//! This example demonstrates how to blink a LED using CPU1 and blink another
//! LED using CPU2 (led_ex1_blinky_cpu2.c).
//!
//! \b External \b Connections \n
//!  - None.
//!
//! \b Watch \b Variables \n
//!  - None.
//!
//
//#############################################################################
//
// 
// $Copyright:
// Copyright (C) 2013-2024 Texas Instruments Incorporated - http://www.ti.com/
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
#include "inc/hw_ipc.h"
#include "board.h"

//
// Globals
//
uint16_t cpu2RWArray[256];      // Mapped to GS1 of shared RAM owned by CPU02
uint16_t cpu2RArray[256];       // Mapped to GS0 of shared RAM owned by CPU01
#pragma DATA_SECTION(cpu2RArray,"SHARERAMGS1");
#pragma DATA_SECTION(cpu2RWArray,"SHARERAMGS0");

uint16_t isrfuncLoadStart;
extern uint16_t isrfuncLoadEnd;
uint16_t isrfuncRunStart;
uint16_t isrfuncLoadSize;

//
// Function Prototypes
//
void initCPUTimer(uint32_t);
void configCPUTimer(uint32_t, float, float);
__interrupt void cpuTimer0ISR(void);
#pragma CODE_SECTION(cpuTimer0ISR, "isrfunc")

void writeDataCPU2(void);

//
// Main
//
void main(void)
{
    uint16_t ipcFlag10 = 10U;
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
    // Initialize SysConfig Settings
    //
    Board_init();

    //
    // Wait until shared RAM is available.
    //
    while((HWREGH(MEMCFG_BASE + MEMCFG_O_GSXMSEL) &
           (MEMCFG_GSXMSEL_MSEL_GS14 | MEMCFG_GSXMSEL_MSEL_GS15)) == 0U)
    {
    }

    //
    // Interrupts that are used in this example are re-mapped to ISR functions
    // found within this file.
    //
    Interrupt_register(INT_TIMER0, &cpuTimer0ISR);

    //
    // Configure CPU Timer 0 to a 1 second period
    //
    initCPUTimer(CPUTIMER0_BASE);
    configCPUTimer(CPUTIMER0_BASE, DEVICE_SYSCLK_FREQ, 1000000);

    //
    // Start CPU Timer 0
    //
    CPUTimer_startTimer(CPUTIMER0_BASE);

    //
    // Enable CPU Timer 0 interrupt
    //
    Interrupt_enable(INT_TIMER0);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Loop indefinitely
    //
    while(1)
    {
        if((HWREG(IPC_BASE + IPC_O_STS) & (1UL << ipcFlag10)) == 1)
        {
            //
            // Read cpu2RArray and modify cpu2RWArray
            //
            writeDataCPU2();
            HWREG(IPC_BASE + IPC_O_ACK) = 1UL << ipcFlag10;
        }
    }
}


//
// initCPUTimer - This function initializes a CPU Timer to a known state.
//
void initCPUTimer(uint32_t cpuTimer)
{
    //
    // Initialize timer period to maximum
    //
    CPUTimer_setPeriod(cpuTimer, 0xFFFFFFFF);

    //
    // Initialize pre-scale counter to divide by 1 (SYSCLKOUT)
    //
    CPUTimer_setPreScaler(cpuTimer, 0);

    //
    // Make sure timer is stopped
    //
    CPUTimer_stopTimer(cpuTimer);

    //
    // Reload all counter registers with period value
    //
    CPUTimer_reloadTimerCounter(cpuTimer);
}

//
// configCPUTimer - This function initializes the selected timer to the
// period specified by the "freq" and "period" parameters. The "freq" is
// entered as Hz and the period in microseconds. The timer is held in the
// stopped state after configuration.
//
void configCPUTimer(uint32_t cpuTimer, float freq, float period)
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
    //
    CPUTimer_stopTimer(cpuTimer);
    CPUTimer_reloadTimerCounter(cpuTimer);
    CPUTimer_setEmulationMode(cpuTimer,
                              CPUTIMER_EMULATIONMODE_STOPAFTERNEXTDECREMENT);
    CPUTimer_enableInterrupt(cpuTimer);
}

//
// cpuTimer0ISR - CPU Timer0 ISR
//
__interrupt void cpuTimer0ISR(void)
{
   GPIO_togglePin(CPU2_LED);   // CPU2_LED Defined in Sysconfig

   Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
}

//
// writeDataCPU2 - Read data from cpu2RArray written by CPU01 and modify and
//                 write into cpu2RWArray. cpu2RArray[0] is used to hold the
//                 multiplier value.
//
void writeDataCPU2(void)
{
    uint16_t index;
    uint16_t multiplier;

    multiplier = cpu2RArray[0];
    cpu2RWArray[0] = multiplier;

    for(index = 1; index < 256; index ++)
    {
        cpu2RWArray[index] = multiplier * cpu2RArray[index];
    }
}

//
// End of File
//

