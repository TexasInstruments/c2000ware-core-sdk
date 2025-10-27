//#############################################################################
//
// FILE:   UART_ex2_loopback.c
//
// TITLE:  UART loopback example.
//
//! \addtogroup driver_example_list
//! <h1>UART Loopback</h1>
//!
//!  This test receives and loop-backs data through the UARTA port.
//!
//!  \b Watch \b Variables \n
//!  - \b sData - Data being sent
//!  - \b rData - Data received
//!  - \b loopCount - Number of characters sent
//!  - \b errorCount - Number of errors detected
//!
//! Note: Avoid keeping the memory browser open while the execution
//! is in progress.
//!
//! \b External \b Connections \n
//!  Connect the UARTA Rx port to Tx port for external loopback.
//!  - GPIO2 is UARTARX to be connected to GPIO3 is UARTATX
//!
//
//#############################################################################
//
//
// 
// C2000Ware v6.00.01.00
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
#include "board.h"
#include "c2000ware_libraries.h"

//
// Define to enable external UART loopback configuration
//
// 0 = internal loopback enabled
// 1 = internal loopback disabled, UART GPIOs configured,
//      external connections required
//
#define EXTERNAL_LOOPBACK_ENABLE    0

//
// Defines
//
uint16_t sData, rData;
uint16_t errorCount, loopCount;

//
// Main
//
void main(void)
{

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Disable pin locks and enable internal pull-ups.
    //
    Device_initGPIO();

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
    // PinMux and Peripheral Initialization
    //
    Board_init();

    #if EXTERNAL_LOOPBACK_ENABLE == 1
        //
        // External loopback configuration
        //
        UART_disableLoopback(myUART0_BASE);
    #else
        //
        // Internal loopback configuration
        //
        UART_enableLoopback(myUART0_BASE);
    #endif

    //
    // C2000Ware Library initialization
    //
    C2000Ware_libraries_init();

    //
    // Enable Global Interrupt (INTM) and real time interrupt (DBGM)
    //
    EINT;
    ERTM;

    while(1)
    {
        //
        // Send the character
        //
        UART_writeChar(myUART0_BASE, sData);

        //
        // Block until data is received and then return it.
        //
        // If the code is stuck here, check hardware connection
        // in case of external loopback.
        //
        rData = UART_readChar(myUART0_BASE);

        //
        // Check received data against sent data
        //
        if(rData != sData)
        {
            errorCount++;
            //
            // Something went wrong.
            // rData doesn't contain expected data.
            // Uncomment to stop the execution here.
            // ESTOP0;
            for (;;);
        }

        //
        // Move to the next character and repeat the test
        //
        sData++;

        //
        // Limit the character to 8-bits
        //
        sData &= 0x00FF;
        loopCount++;
    }
}

//
// End of File
//
