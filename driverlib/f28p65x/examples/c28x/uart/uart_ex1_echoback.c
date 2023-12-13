//#############################################################################
//
// FILE:   UART_ex1_echoback.c
//
// TITLE:  UART echoback example.
//
//! \addtogroup driver_example_list
//! <h1>UART Echoback</h1>
//!
//!  This test receives and echo-backs data through the UARTA port.
//!
//!  A terminal such as 'putty' can be used to view the data from
//!  the UART and to send information to the UART. Characters
//!  received by the UART port are sent back to the host.
//!
//!  \b Running \b the \b Application
//!  Open a COM port with the following settings using a terminal:
//!  -  Find correct COM port
//!  -  Bits per second = 115200
//!  -  Data Bits = 8
//!  -  Parity = None
//!  -  Stop Bits = 1
//!  -  Hardware Control = None
//!
//!  The program will print out a greeting and then ask you to
//!  enter a character which it will echo back to the terminal.
//!
//!  \b Watch \b Variables \n
//!  - None
//!
//! \b External \b Connections \n
//!  Connect the UARTA port to a PC via a transceiver and cable.
//!  - GPIO85 is UARTARX (Connect to Pin3, PC-TX, of serial DB9 cable)
//!  - GPIO84 is UARTATX (Connect to Pin2, PC-RX, of serial DB9 cable)
//! 
//!  \note The pin muxing for the UARTA port needs to be done by the master 
//!  CPU1. The common configuration example provided in the C28x folder can be 
//!  used for making GPIO85 as the UART Rx pin and GPIO84 as the UART Tx pin.
//
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2022 Texas Instruments Incorporated - http://www.ti.com
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
#include <stdint.h>
#include <stdbool.h>

#include "driverlib.h"
#include "device.h"
#include "board.h"

//
// Function Prototypes
//
__interrupt void UART_RX_IntHandler(void);

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

    //
    // Enable Global Interrupt (INTM) and real time interrupt (DBGM)
    //
    EINT;
    ERTM;

    // 
    // Put a character to show start of example.  This will display on the
    // terminal.
    //
    UART_writeChar(UARTA_BASE, '!');
    UART_writeChar(UARTA_BASE, '!');

    //
    // FIFO interrupt levels are set to generate an interrupt
    // when the TX FIFO is less than or equal to 7/8 empty and the
    // RX FIFO is greater than or equal to 1/8 full.
    //
    UART_setFIFOLevel(UARTA_BASE, UART_FIFO_TX1_8, UART_FIFO_RX1_8);

    //
    // FIFO receive interrupt configuration
    //
    UART_clearInterruptStatus(UARTA_BASE,UART_INT_RX | UART_INT_RT);   
    UART_enableInterrupt(UARTA_BASE,UART_INT_RX);

    //
    // Loop forever echoing data through the UART.
    //
    while(1)
    {
    }
}


__interrupt void UART_RX_IntHandler(void)
{
    uint32_t ui32Status;

    //
    // Get the interrupt status.
    //
    ui32Status = UART_getInterruptStatus(UARTA_BASE, UART_RAW_INT);

    //
    // Clear the asserted interrupts.
    //
    UART_clearInterruptStatus(UARTA_BASE, ui32Status);

    //
    // Loop while there are characters in the receive FIFO.
    //
    while(UART_isDataAvailable(UARTA_BASE))
    {
        //
        // Read the next character from the UART and write it back to the UART.
        //
        UART_writeCharNonBlocking(UARTA_BASE,
                                  UART_readCharNonBlocking(UARTA_BASE));
    }

    // TODO: Add a function to clear the global flag
    HWREG(myUART0_BASE + 0x0044U) = 1;
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP8);

}

//
// End of File
//
