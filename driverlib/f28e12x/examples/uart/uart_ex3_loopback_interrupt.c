//#############################################################################
//
// FILE:   UART_ex3_loopback_interrupt.c
//
// TITLE:  UART loopback with interrupt example.
//
//! \addtogroup driver_example_list
//! <h1>UART Loopback with interrupt</h1>
//!
//!  This test uses the internal loop back test mode of the peripheral.
//!  Receive interrupt with FIFO is used in the example.
//!
//!  A stream of data is sent and then compared to the received stream.
//!  The UART-A sent data looks like this: \n
//!  00 01 \n
//!  01 02 \n
//!  02 03 \n
//!  .... \n
//!  FE FF \n
//!  FF 00 \n
//!  etc.. \n
//!  The pattern is repeated forever.
//!
//!  \b Watch \b Variables \n
//!  - \b sData - Data being sent
//!  - \b rData - Data received
//!  - \b loopCount - Number of times ISR is executed
//!  - \b errorCount - Number of errors detected
//!
//! Note: Avoid keeping the memory browser open while the execution
//! is in progress.
//!
//! \b External \b Connections \n
//!  Connect the UARTA Rx port to Tx port for external loopback.
//!  - GPIO32 is UARTARX to be connected to GPIO43 is UARTATX
//!
//
//#############################################################################
//
//
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
uint16_t sData[2], rData[2];
uint16_t errorCount, loopCount;

void error(void);

//
// Main
//
void main(void)
{
    uint16_t i;

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

    //
    // Init the send data.  After each transmission this data
    // will be updated for the next transmission.
    // Put a character to show start of example.
    //
    for(i = 0; i < 2; i++)
    {
        sData[i] = i;
        UART_writeChar(myUART0_BASE, sData[i]);
    }

    while(1)
    {
        //
        // Check the hardware connections if
        // the code execution is halted here
        // and interrupt is never executed!
        //
    }
}

__interrupt void UART_RX_IntHandler(void)
{
    uint32_t ui32Status;
    uint16_t i = 0;

    //
    // Get the interrupt status.
    //
    ui32Status = UART_getInterruptStatus(myUART0_BASE, UART_RAW_INT);

    //
    // Clear the asserted interrupts.
    //
    UART_clearInterruptStatus(myUART0_BASE, ui32Status);

    //
    // Loop while there are characters in the receive FIFO.
    //
    while(UART_isDataAvailable(myUART0_BASE))
    {
        //
        // Read the next character from the UART and write it back to the UART.
        //
        rData[i++] = UART_readCharNonBlocking(myUART0_BASE);
    }

    //
    // Check received data
    //
    for(i = 0; i < 2; i++)
    {
        if(rData[i] != sData[i])
        {
            errorCount++;
            // Uncomment to halt the code in error function.
            //error();
        }
    }

    //
    // Increment & send data for next cycle
    //
    for(i = 0; i < 2; i++)
    {
        sData[i] = (sData[i] + 1) & 0x00FF;
        UART_writeCharNonBlocking(myUART0_BASE, sData[i]);
    }

    loopCount++;

    // Clear UART and PIPE interrupts
    UART_clearGlobalInterruptFlag(myUART0_BASE);
    Interrupt_clearACKGroup(INT_myUART0_INTERRUPT_ACK_GROUP);
}

//
// error - Function to halt debugger on error
//
void error(void)
{
    asm("     ESTOP0"); // Test failed!! Stop!
    for (;;);
}

//
// End of File
//
