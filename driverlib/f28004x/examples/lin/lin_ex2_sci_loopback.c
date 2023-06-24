//#############################################################################
//
// FILE:   lin_ex2_sci_loopback.c
//
// TITLE:   LIN SCI Mode Internal Loopback with Interrupts
//
//! \addtogroup driver_example_list
//! <h1> LIN SCI Mode Internal Loopback with Interrupts </h1>
//!
//!  This example configures the LIN module in SCI mode for internal loopback
//!  with interrupts. The LIN module performs as a SCI with a set character
//!  and frame length in a non-multi-buffer mode. The module is setup to 
//!  continuously transmit a character, wait to receive that character, and 
//!  repeat.
//!
//! \b External \b Connections \n
//!  - None.
//!
//! \b Watch \b Variables \n
//!  - rxCount - The number of RX interrupts
//!  - transmitChar - The character being transmitted
//!  - receivedChar - The character received
//!
//
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2023 Texas Instruments Incorporated - http://www.ti.com/
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
// Defines
//
#define CHAR_LENGTH     8
#define FRAME_LENGTH    1

//
// Globals
//
volatile uint32_t rxCount = 0;
volatile uint32_t vectorOffset = 0;
volatile uint16_t error = 0;
uint16_t transmitChar = 0x0;
uint16_t receivedChar = 0x0;

//
// Function Prototypes
//
__interrupt void dataRxISR(void);
void configureSCIMode(void);

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
    // Initialize GPIO
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
    EINT;
    ERTM;

    //
    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    // This registers the interrupt handler in PIE vector table.
    //
    Interrupt_register(INT_LINA_0, &dataRxISR);

    //
    // Enable the LIN interrupt signal
    //
    Interrupt_enable(INT_LINA_0);

    //
    // Initialize the LIN module
    //
    LIN_initModule(LINA_BASE);

    //
    // Configure the LIN module to operate in SCI mode
    //
    configureSCIMode();

    //
    // Enable global interrupt lines and clear status to known value
    //
    LIN_enableGlobalInterrupt(LINA_BASE, LIN_INTERRUPT_LINE0);
    LIN_clearGlobalInterruptStatus(LINA_BASE, LIN_INTERRUPT_LINE0);

    //
    // Continuously transmit an 8-bit character, wait for ISR to run, and 
    // verify everything was received correctly
    //
    for(;;)
    {
        vectorOffset = 0;

        //
        // Increment transmit character to new value
        //
        transmitChar++;

        //
        // Reset transmit character when larger than a byte
        //
        if(transmitChar > 0xFF)
        {
            transmitChar = 0;
        }

        //
        // Wait for the SCI receiver to be idle
        //
        while(!LIN_isSCIReceiverIdle(LINA_BASE));

        //
        // Transmit the byte of data
        //
        LIN_writeSCICharBlocking(LINA_BASE, transmitChar);

        //
        // Wait for ISR to trigger and read the transmitted character
        //
        while(vectorOffset != LIN_VECT_RX);

        //
        // Halt the example if any errors occurred
        //
        if(error != 0)
        {
            asm("   ESTOP0");
        }
    }
}

//
// Configure SCI Mode - This function configures the LIN module to operate as 
// an SCI with the specified settings.
//
void
configureSCIMode(void)
{
    //
    // Enter LIN reset state to perform configurations
    //
    LIN_enterSoftwareReset(LINA_BASE);

    //
    // Switch LIN into SCI mode
    //
    LIN_enableSCIMode(LINA_BASE);

    //
    // Set the SCI communication mode to idle line
    //
    LIN_setSCICommMode(LINA_BASE, LIN_COMM_SCI_IDLELINE);

    //
    // Set SCI to transmit one stop bit
    //
    LIN_setSCIStopBits(LINA_BASE,LIN_SCI_STOP_ONE);

    //
    // Disable parity check
    //
    LIN_disableSCIParity(LINA_BASE);

    //
    // Disable multi-buffer mode
    //
    LIN_disableMultibufferMode(LINA_BASE);

    //
    // Module set to complete operations when halted by debugger
    //
    LIN_setDebugSuspendMode(LINA_BASE, LIN_DEBUG_COMPLETE);

    //
    // Set character length as 8-bits
    //
    LIN_setSCICharLength(LINA_BASE, CHAR_LENGTH);

    //
    // Set to 1 character in response field
    //
    LIN_setSCIFrameLength(LINA_BASE, FRAME_LENGTH);

    //
    // Enable Internal Loopback mode
    //
    LIN_enableIntLoopback(LINA_BASE);

    //
    // Enable interrupt for when a frame has been completely received
    //
    LIN_enableSCIInterrupt(LINA_BASE, LIN_SCI_INT_RX);

    //
    // Set the interrupt priority to line 0 (high)
    //
    LIN_setSCIInterruptLevel0(LINA_BASE, LIN_SCI_INT_RX);

    //
    // Exit LIN reset state
    //
    LIN_exitSoftwareReset(LINA_BASE);
}

//
// Received Data ISR - An interrupt service routine (ISR) to handle when new
// data is received. Once received, the data is read and interrupt status 
// cleared.
//
__interrupt void
dataRxISR(void)
{
    //
    // Increment the interrupt count
    //
    rxCount++;

    //
    // Read the highest priority interrupt vector
    //
    vectorOffset = LIN_getInterruptLine0Offset(LINA_BASE);

    //
    // Read the transmitted character
    //
    receivedChar = LIN_readSCICharBlocking(LINA_BASE, false);

    //
    // Check that the received character matches the transmitted character
    //
    if(receivedChar != transmitChar)
    {
        error++;
    }

    //
    // Clear module interrupt flag and global interrupt flag for line 0
    //
    LIN_clearInterruptStatus(LINA_BASE, LIN_INT_RX);
    LIN_clearGlobalInterruptStatus(LINA_BASE, LIN_INTERRUPT_LINE0);

    //
    // Acknowledge this interrupt located in group 8
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP8);
}

//
// End of File
//
