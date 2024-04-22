//###########################################################################
//
// FILE:   ipc_ex2_sysconfig_cpu2.c
//
// TITLE: SysConfig IPC GPIO Toggle for F2837xD CPU2.
//
// This example shows GPIO input on the local CPU triggering an output on the
// remote CPU. A GPIO input change on CPU01 causes an output change on CPU02
// and vice versa.
// CPU1 has control of GPIO31 , GPIO15 and GPIO14.
// CPU2 has control of GPIO34 , GPIO10 and GPIO11.
//
// The IPC is used to signal a change on the CPU's input pin.
//
// \b Hardware \b Connections
//   - connect GPIO15 to GPIO11
//   - connect GPIO14 to GPIO10
//
// \b Watch \b Pins
//   - GPIO34 - output on CPU2
//   - GPIO11 - input on CPU2
//   - GPIO31 - output on CPU1
//   - GPIO14 - input on CPU1
//   - GPIO10 - square wave output on CPU02
//   - GPIO15 - square wave output on CPU01
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
    uint32_t count;
    uint16_t state;

    //
    // Initialize device clock and peripherals
    //
    Device_init();

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

    //
    // Sync the CPUs
    //
    IPC_sync(IPC_CPU2_L_CPU1_R, IPC_FLAG31);

    //
    // Set the state to the DAT value of GPIO11
    //
    state = GPIO_readPin(myGPIO11);

    //
    // Toggle GPIO10
    //
    GPIO_togglePin(myGPIO10);

    while(1)
    {
        //
        // Produce a Square Wave on GPIO10. This signal will be used to drive
        // GPIO14 input on CPU1
        //
        if(count++ > 2000000)
        {
            count = 0;

            //
            // Toggle GPIO10
            //
            GPIO_togglePin(myGPIO10);
        }

        //
        // Set Flag 11 for CPU2_to_CPU1 flags when GPIO11 input changes
        //
        if(GPIO_readPin(myGPIO11) != state)
        {
            state = GPIO_readPin(myGPIO11);

            //
            // This checks to see if flag 11 for CPU2_to_CPU1 is already set, then sets the Flag if it wasn't busy
            //
            IPC_sendCommand(IPC_CPU2_L_CPU1_R, IPC_FLAG11, IPC_ADDR_CORRECTION_ENABLE,
                                0, 0, 0);
        }

        //
        // Toggle GPIO34 output if Flag 10 is set by CPU1
        //
        if (IPC_isFlagBusyRtoL(IPC_CPU2_L_CPU1_R, IPC_FLAG10))
        {
            //
            // Toggle GPIO34 (LED2)
            //
            GPIO_togglePin(CPU2_LED);

            //
            // Acknowledge and clear the flag
            //
            IPC_ackFlagRtoL(IPC_CPU2_L_CPU1_R, IPC_FLAG10);
        }
    }
}

//
// End of file
//
