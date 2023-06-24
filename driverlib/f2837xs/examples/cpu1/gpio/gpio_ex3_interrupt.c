//#############################################################################
//
// FILE:    gpio_ex3_interrupt.c
//
// TITLE:   Device GPIO Interrupt
//
//! \addtogroup driver_example_list
//! <h1> Device GPIO Interrupt </h1>
//!
//! Configures the device GPIOs through the sysconfig file. One GPIO output
//! pin, and one GPIO input pin is configured. The example then configures the
//! GPIO input pin to be the source of an external interrupt which toggles
//! the GPIO output pin.
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
#include "board.h"

//
// Interrupt Handler
//
__interrupt void gpioInterruptHandler(void);

//
// Main
//
void main(void)
{
    //
    // Initializes system control, device clock, and peripherals
    //
    Device_init();

    //
    // Initializes PIE and clear PIE registers. Disables CPU interrupts.
    // and clear all CPU interrupt flags.
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // Board Initialization
    //
    Board_init();

    GPIO_setInterruptType(GPIO_INT_XINT1, GPIO_INT_TYPE_FALLING_EDGE);
    GPIO_setInterruptPin(myGPIOInputInterrupt0, GPIO_INT_XINT1);
    GPIO_enableInterrupt(GPIO_INT_XINT1);

    Interrupt_register(INT_XINT1, &gpioInterruptHandler);
    Interrupt_enable(INT_XINT1);

    //
    // Enables CPU interrupts
    //
    Interrupt_enableMaster();

    //
    // Loop.
    //
    for(;;)
    {

    }
}

__interrupt void gpioInterruptHandler(void)
{
    GPIO_togglePin(myGPIOOutput0);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
}


//
// End of File
//

