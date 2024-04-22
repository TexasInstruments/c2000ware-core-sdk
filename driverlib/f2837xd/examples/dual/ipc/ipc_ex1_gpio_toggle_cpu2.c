//###########################################################################
//
// FILE:   ipc_gpio_toggle_cpu02.c
//
// TITLE:  IPC GPIO Toggle for F2837xD CPU2.
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

//
// Main
//
void main(void)
{
    uint32_t count;
    uint16_t state;
    uint16_t ipcFlag17 = 17U;
    uint16_t ipcFlag10 = 10U;
    uint16_t ipcFlag11 = 11U;

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Initialize GPIO and configure the GPIO pin as a push-pull output
    //
    // This is configured by CPU1

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
    // Send IPC flag 5 to CPU2
    //
    HWREG(IPC_BASE + IPC_O_SET) = 1UL << ipcFlag17;

    //
    // Set the state to the DAT value of GPIO11
    //
    state = GPIO_readPin(11UL);

    //
    // Toggle GPIO10
    //
    GPIO_togglePin(10UL);

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
            GPIO_togglePin(10UL);
        }

        //
        // Set Flag 11 when GPIO11 input changes
        //
        if(GPIO_readPin(11UL) != state)
        {
            state = GPIO_readPin(11UL);

            if(!(HWREG(IPC_BASE + IPC_O_STS) & (1UL << ipcFlag11)))
            {
                //
                // Send IPC flag 11 to CPU2
                //
            	HWREG(IPC_BASE + IPC_O_SET) = 1UL << ipcFlag11;
            }
        }

        //
        // Toggle GPIO34 output if Flag 10 is set by CPU1
        //
        if((HWREG(IPC_BASE + IPC_O_STS) & (1UL << ipcFlag10)))
        {
        	//
        	// Toggle GPIO34 (LED2)
        	//
        	GPIO_togglePin(DEVICE_GPIO_PIN_LED2);

            //
            // ACK IPC flag 11 for CPU2
            //
            HWREG(IPC_BASE + IPC_O_ACK) = 1UL << ipcFlag10;

            //
            // Clear IPC flag 11 for CPU2
            //
            HWREG(IPC_BASE + IPC_O_CLR) = 1UL << ipcFlag10;
        }
    }
}

//
// End of file
//
