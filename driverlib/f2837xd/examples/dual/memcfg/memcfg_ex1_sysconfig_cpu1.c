//#############################################################################
//
// FILE:   memcfg_ex1_sysconfig_cpu1.c
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
uint16_t cpu1RArray[256];       // Mapped to GS0 of shared RAM owned by CPU2
uint16_t cpu1RWArray[256];      // Mapped to GS1 of shared RAM owned by CPU1
#pragma DATA_SECTION(cpu1RArray,"SHARERAMGS0");
#pragma DATA_SECTION(cpu1RWArray,"SHARERAMGS1");

uint16_t error;
uint16_t multiplier;

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

void readDataCPU1(void);
void writeDataCPU1(void);

//
// Main
//
void main(void)
{
    uint16_t ipcFlag10 = 10U;
    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Initialize GPIO
    //
    Device_initGPIO();

    //
    // Initialize SysConfig Settings
    //
    Board_init();

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
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    error = 0;
    multiplier = 0;

    writeDataCPU1();
    HWREG(IPC_BASE + IPC_O_SET) = 1UL << ipcFlag10;

    uint32_t counter = 0;

    //
    // Loop indefinitely
    //
    for(;;)
    {
        //
        // If there is no pending flag
        //
        if( (HWREG(IPC_BASE + IPC_O_FLG) & (1UL << ipcFlag10)) == 0)
        {
            readDataCPU1();

            if(multiplier++ > 255)
            {
                multiplier = 0;
            }

            //
            // Write an array to a memory location owned by CPU01
            //
            writeDataCPU1();

            //
            // Set a flag to notify CPU02 that data is available
            //
            HWREG(IPC_BASE + IPC_O_SET) = 1UL << ipcFlag10;
        }
        if (counter++ > 2000000)
        {
            //
            // Toggle CPU1_LED, defined in sysconfig
            //
            GPIO_togglePin(CPU1_LED);
            counter = 0;

        }
    }
}

//
// writeDataCPU1 - Write a pattern to an array in shared RAM
//
void writeDataCPU1(void)
{
    uint16_t index;

    //
    // Use first location to write a multiplier.
    //
    cpu1RWArray[0] = multiplier;

    for(index = 1; index < 256; index++)
    {
        cpu1RWArray[index] = index;

        //
        // The following code will attempt to write to a shared RAM assigned
        // to CPU2 and as a result will cause an access violation.
        //
        // cpu1RArray[index] = 1000 + index;
    }
}

//
// readDataCPU1 - Read and compare an array from shared RAM
//
void readDataCPU1(void)
{
    uint16_t index;

    if(cpu1RArray[0] == multiplier)
    {
        for(index = 1; index < 256; index++)
        {
            if(cpu1RArray[index] != multiplier * cpu1RWArray[index])
            {
                error = 1;
            }
        }
    }
    else
    {
        error = 1;
    }
}

//
// End of File
//
