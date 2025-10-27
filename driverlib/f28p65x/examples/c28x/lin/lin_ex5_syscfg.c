//#############################################################################
//
// FILE:   lin_ex5_syscfg.c
//
// TITLE:   LIN Internal Loopback with Interrupts using Sysconfig
//
//! \addtogroup driver_example_list
//! <h1> LIN Internal Loopback with Interrupts using Sysconfig </h1>
//!
//!  This example is similar to ex1 but using syscfg tool to configure the
//!  LIN Module parameters. The file lin_ex5_syscfg.syscfg can be updated 
//!  using the GUI tool to update the configuration parameters.  
//!  This example configures the LIN module in commander mode for internal
//!  loopback with interrupts. The module is setup to perform 8 data
//!  transmissions with different transmit IDs and varying transmit data.
//!  Upon reception of an ID header, an interrupt is triggered on line 0
//!  and an interrupt service routine (ISR) is called. The received data
//!  is then checked for accuracy.
//!
//!  \note This example project has support for migration across our C2000 
//!  device families. If you are wanting to build this project from launchpad
//!  or controlCARD, please specify in the .syscfg file the board you're using.
//!  At any time you can select another device to migrate this example.
//!
//! \b External \b Connections \n
//!  - None.
//!
//! \b Watch \b Variables \n
//!  - txData - An array with the data being sent
//!  - rxData - An array with the data that was received
//!  - result - The example completion status (PASS = 0xABCD, FAIL = 0xFFFF)
//!  - level0Count - The number of line 0 interrupts
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

//
// Defines
//
#define FRAME_LENGTH    0x8
#define LIN_PASS        0xABCD
#define LIN_FAIL        0xFFFF

//
// Globals
//
volatile uint32_t level0Count = 0;
volatile uint32_t vectorOffset = 0;
uint16_t result;
uint16_t txData[8] = {0x11, 0x34, 0x56, 0x78, 0x9A, 0xAB, 0xCD, 0xEF};
uint16_t rxData[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

//
// Function Prototypes
//
__interrupt void level0ISR(void);

//
// Main
//
void main(void)
{
    uint32_t i, dataIndex;
    uint16_t txID, error;

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Initialize GPIO and configure GPIO pins for LINTX/LINRX
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
    // Board initialization
    //
    Board_init();

    EINT;
    ERTM;

    //
    // Perform 8 data transmissions with different transmit IDs and varying
    // number of bytes transmitted. Received data is checked for correctness.
    //
    for(i = 1 ; i <= FRAME_LENGTH; i++)
    {
        vectorOffset = 0;

        //
        // Create a new transmit ID and update with parity bits
        //
        txID = (0x10 + i);
        txID = LIN_generateParityID(txID);

        //
        // Increment the value of the first 8-bits of the transmitted
        // message data
        //
        txData[0]++;

        //
        // Reset values in receive buffer array
        //
        for(dataIndex=0; dataIndex < 8; dataIndex++)
        {
            rxData[dataIndex] = 0xFF;
        }

        //
        // Set the frame length (number of bytes to be transmitted)
        //
        LIN_setFrameLength(myLIN0_BASE, i);

        //
        // This places data into the transmit buffer.
        // No ID or data is placed on the bus and transmitted yet.
        //
        LIN_sendData(myLIN0_BASE, txData);

        //
        // Set the message ID to initiate a header transmission.
        // This causes the ID to be written to the bus followed by the
        // data in the transmit buffers.
        //
        LIN_setIDByte(myLIN0_BASE, txID);

        //
        // Wait for ISR to trigger and run upon reception of the ID header
        //
        while(vectorOffset != LIN_VECT_ID);

        //
        // Wait until Transmit buffer is empty and has completed transmission
        //
        while(!LIN_isTxBufferEmpty(myLIN0_BASE));

        //
        // Read the received data in the receive buffers
        //
        LIN_getData(myLIN0_BASE, rxData);

        //
        // Verify the transmitted data matches the received data
        //
        for (dataIndex=0; dataIndex < i; dataIndex++)
        {
            if (rxData[dataIndex] != txData[dataIndex])
            {
                error++;
            }
        }
    }

    //
    // Check if any data errors occurred
    //
    if(error == 0)
    {
        result = LIN_PASS;
    }
    else
    {
      result = LIN_FAIL;
    }

    //
    // Example completed. Check "result" variable for completion status.
    //
    asm("   ESTOP0");
}

//
// LIN High Priority (Level 0) ISR - Interrupt service routine for interrupt
// line 0. This ISR saves the offset vector indicating the current highest
// priority pending interrupt.
//
__interrupt void
level0ISR(void)
{
    //
    // Increment the interrupt count
    //
    level0Count++;

    //
    // Read the high priority interrupt vector
    //
    vectorOffset = LIN_getInterruptLine0Offset(myLIN0_BASE);
    LIN_clearInterruptStatus(myLIN0_BASE, LIN_INT_ID);
    LIN_clearGlobalInterruptStatus(myLIN0_BASE, LIN_INTERRUPT_LINE0);

    //
    // Acknowledge this interrupt
    //
    Interrupt_clearACKGroup(INT_myLIN0_LINE0_INTERRUPT_ACK_GROUP);
}


//
// End of File
//
