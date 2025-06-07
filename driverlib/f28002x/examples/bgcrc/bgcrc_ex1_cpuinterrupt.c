//#############################################################################
//
// FILE:   bgcrc_ex1_cpuinterrupt.c
//
// TITLE:  Background CRC computation with interrupt.
//
//! \addtogroup driver_example_list
//! <h1> BGCRC CPU Interrupt Example </h1>
//!
//! This example demonstrates how to configure and trigger BGCRC from the CPU.
//! BGCRC module is configured for 1 KB of GS0 RAM which is programmed with a
//! known data. The pre-computed CRC value is used as the golden CRC value.
//! Interrupt is generated once the computation is done and checks if no error
//! flags are raised
//! Calculation uses the 32-bit polynomial 0x04C11DB7 and seed value 0x00000000.
//!
//! \b External \b Connections \n
//!  - None.
//!
//! \b Watch \b Variables \n
//!  - pass - This should be 1.
//!  - runStatus - BGCRC running status. This will be BGCRC_ACTIVE if the module
//!                is running, BGCRC_IDLE if the module is idle
//!
//
//#############################################################################
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
//###########################################################################

//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "board.h"

//
// Globals
//
bool pass = false;

volatile uint32_t currentAddress = 0x0000;
volatile bool runStatus = false;

#pragma DATA_SECTION(test_data_gs0, "ramgs0")
#pragma DATA_ALIGN(test_data_gs0, 0x80)
uint32_t test_data_gs0[myBGCRC0_BLOCKSIZE/4];
const void *td_gs0 = test_data_gs0;
//
// Function Prototypes
//
__interrupt void bgcrcISR(void);

//
// Main
//
void main(void)
{
    int i;

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Initialize GPIO and configure the GPIO pin as a push-pull output
    //
    Device_initGPIO();

    //
    // Disable global interrupts.
    //
    DINT;

    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts. 
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();
    IER = 0x0000;
    IFR = 0x0000;
    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Fill RAMGS0 with known data
    //
    for(i = 0; i < (myBGCRC0_BLOCKSIZE/4); i++)
    {
        test_data_gs0[i] = 0x1000 + i;
    }
    //
    // Set runStatus to true
    //
    runStatus = true;

    //initialize sysconfig options
    //
    Board_init();

    //
    // Loop Forever
    //
    while(1)
    {
    	//
    	// Check the run status and current address of the CRC calculation.
    	//
    	runStatus = BGCRC_getRunStatus(myBGCRC0_BASE);
    	currentAddress = BGCRC_getCurrentAddress(myBGCRC0_BASE);
    }
}

//
// bgcrcISR - DONE interrupt from BGCRC.
//
__interrupt void
bgcrcISR(void)
{
    //
    // Check the status of the CRC calculation and set the global pass
    // variable. Check if no error flags are set.
    //
    if(BGCRC_getInterruptStatus(myBGCRC0_BASE) == (BGCRC_GLOBAL_INT | BGCRC_TEST_DONE))
    {
    	pass = true;
    }

    //
    // Clear the BGCRC interrupt flags.
    //
    BGCRC_clearInterruptStatus(myBGCRC0_BASE, (BGCRC_GLOBAL_INT | BGCRC_TEST_DONE | BGCRC_ALL_ERROR_FLAGS));

    //
    // Acknowledge the PIE interrupt.
    //

    Interrupt_clearACKGroup(INT_myBGCRC0_INTERRUPT_ACK_GROUP);

}

//
// End of File
//
