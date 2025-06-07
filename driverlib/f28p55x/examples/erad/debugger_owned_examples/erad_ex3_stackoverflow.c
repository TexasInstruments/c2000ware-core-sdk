//#############################################################################
//
// FILE:   erad_ex3_stackoverflow.c
//
// TITLE:  ERAD Stack Overflow Example
//
//! \addtogroup driver_example_list
//! <h1> ERAD Stack Overflow </h1>
//!
//! This example shows the basic setup of CAN in order to transmit and receive
//! messages on the CAN bus.  The CAN peripheral is configured to transmit
//! messages with a specific CAN ID.  A message is then transmitted once per
//! second, using a simple delay loop for timing.  The message that is sent is
//! a 2 byte message that contains an incrementing pattern.
//!
//! This example sets up the CAN controller in External Loopback test mode.
//! Data transmitted is visible on the CANTXA pin and is received internally
//! back to the CAN Core.
//!
//! A buffer is created to store message history up to 50 messages for the
//! duration of the program. A logic error is intentionally made to allow the
//! buffer to overflow, eventually causing a stack overflow. The included
//! JavaScript file, stack_overflow.js, programs ERAD registers in order to
//! detect the stack overflow and halt the CPU once the illegal write is made.
//! The illegal write is made after 507 messages are received.
//!
//! To properly use the provided ERAD script, the following variables must be
//! set in the scripting environment prior to launching the ERAD script:
//!
//! - var PROJ_NAME = "erad_debugger_ex3_stackoverflow"
//! - var PROJ_WKSPC_LOC = <proj_workspace_path>
//!
//! To run the ERAD script, use the following command in the scripting console:
//!
//! - loadJSFile("<proj_workspace_path>\\erad_debugger_ex3_stackoverflow\\erad_ex3_stack_overflow.js", 0);
//!
//! Note that the script must be run after loading and running the .out on the
//! C28x core. 
//!
//! The included JavaScript file, erad_ex3_stack_overflow.js, uses Debug Server
//! Scripting (DSS) features. For information on using the DSS, please visit:
//! http://software-dl.ti.com/ccs/esd/documents/users_guide/sdto_dss_handbook.html
//!
//! This example uses 1 HW watchpoint :
//!  - HWBP_1 : Data Write Address Bus = Stack end address + 1
//!
//! \b External \b Connections \n
//!  - None.
//!
//! \b Watch \b Variables \n
//!  - msgCount - A counter for the number of successful messages received
//!  - txMsgData - An array with the data being sent
//!  - rxMsgData - An array with the data that was received
//!  - msgHistoryBuff - An array meant to store the last 50 messages received
//!
//! \b Profiling \b Script \b Output
//!  - "STACK OVERFLOW detected. Halting CPU." will be printed in the scripting
//!    console when a stack overflow occurs (that is, when the watchpoint is hit)
//
//#############################################################################
//
//
// 
// C2000Ware v5.05.00.00
//
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
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


//
// Globals
//
extern uint32_t __TI_STACK_END;
volatile uint32_t functionCallCount = 0;

//
// Function Prototypes
//
void recursiveFunction(uint32_t delay);

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
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    recursiveFunction(1);

    //
    // IDLE loop. Just sit and loop forever (optional)
    //
    while(1)
    {

    }
}

//
// recursive function to fill the stack
//
void recursiveFunction(uint32_t delay)
{
    functionCallCount++;

    //
    // Recursive function
    //
    recursiveFunction(delay + 1UL);
}


//
// End of File
//
