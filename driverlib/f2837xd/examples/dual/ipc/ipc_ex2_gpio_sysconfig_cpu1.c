//###########################################################################
//
// FILE:   ipc_ex2_sysconfig_cpu1.c
//
// TITLE: SysConfig GPIO Toggle for F2837xD CPU1.
//
//! \addtogroup dual_example_list
//! <h1> IPC GPIO toggle </h1>
//!
//! This example shows GPIO input on the local CPU triggering an output on the
//! remote CPU. A GPIO input change on CPU01 causes an output change on CPU02
//! and vice versa. \n
//! CPU1 has control of GPIO31 , GPIO15 and GPIO14.\n
//! CPU2 has control of GPIO34 , GPIO10 and GPIO11.\n
//!
//! The IPC is used to signal a change on the CPU's input pin.\n
//!
//! \b Hardware \b Connections
//!   - connect GPIO15 to GPIO11
//!   - connect GPIO14 to GPIO10
//!
//! \b Watch \b Pins
//!   - GPIO34 - output on CPU2
//!   - GPIO11 - input on CPU2
//!   - GPIO31 - output on CPU1
//!   - GPIO14 - input on CPU1
//!   - GPIO10 - square wave output on CPU02
//!   - GPIO15 - square wave output on CPU01
//
//#############################################################################
// $TI Release: $
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
#include "board.h"


//
// Main
//
void main(void)
{
    uint16_t state;
    uint32_t count;

    //
    // Initialize device clock and peripherals
    //
    Device_init();


    //
    // Initialize GPIO and configure the GPIO pin as a push-pull output
    //
    Device_initGPIO();

    //
    // Initialize settings from SysConfig
    //
    Board_init();

    //
    // Clear all interrupts and initialize PIE vector table:
    // Disable CPU interrupts
    //
    DINT;

    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts
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

    //
    // Sync the CPUs
    //
    IPC_sync(IPC_CPU1_L_CPU2_R, IPC_FLAG31);

    //
    // Set the state to the DAT value of GPIO14
    //
    state = GPIO_readPin(myGPIO14);

    while(1)
    {
        //
        // Generate a Square Wave on GPIO15. This signal will be used to drive
        // GPIO11 input on CPU2
        //
        if(count++ > 1000000)
        {
            count = 0;

            //
            // Toggle GPIO15
            //
            GPIO_togglePin(myGPIO15);
        }

        //
        // Set Flag 10 when GPIO14 input changes
        //
        if(GPIO_readPin(myGPIO14) != state)
        {
            state = GPIO_readPin(myGPIO14);
            //
            // This checks to see if flag 10 for CPU1_to_CPU2 is already set, then sets the Flag if it wasn't busy
            //
            IPC_sendCommand(IPC_CPU1_L_CPU2_R, IPC_FLAG10, IPC_ADDR_CORRECTION_ENABLE,
                                0, 0, 0);
        }

        //
        // Toggle GPIO31 output if Flag 11 is set by CPU2
        //
        if (IPC_isFlagBusyRtoL(IPC_CPU1_L_CPU2_R, IPC_FLAG11))
        {
            //
            // Toggle GPIO31 (LED1)
            //
            GPIO_togglePin(CPU1_LED);

            //
            // Acknowledge and clear the flag
            //
            IPC_ackFlagRtoL(IPC_CPU1_L_CPU2_R, IPC_FLAG11);
        }
    }
}

//
// End of file
//
