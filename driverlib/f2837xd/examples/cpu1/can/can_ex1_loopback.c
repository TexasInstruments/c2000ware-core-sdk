//#############################################################################
//
// FILE:   can_ex1_loopback.c
//
// TITLE:   CAN External Loopback Example
//
//! \addtogroup driver_example_list
//! <h1> CAN External Loopback </h1>
//!
//! This example shows the basic setup of CAN in order to transmit and receive
//! messages on the CAN bus.  The CAN peripheral is configured to transmit
//! messages with a specific CAN ID.  A message is then transmitted once per
//! second, using a simple delay loop for timing.  The message that is sent is
//! a 2 byte message that contains an incrementing pattern.
//!
//! This example sets up the CAN controller in External Loopback test mode.
//! Data transmitted is visible on the CANTXA pin and is received internally
//! back to the CAN Core. Please refer to details of the External Loopback
//! Test Mode in the CAN Chapter in the Technical Reference Manual.
//!
//! \b External \b Connections \n
//!  - None.
//!
//! \b Watch \b Variables \n
//!  - msgCount - A counter for the number of successful messages received
//!  - txMsgData - An array with the data being sent
//!  - rxMsgData - An array with the data that was received
//!
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
#include "board.h"

//
// Defines
//
#define MSG_DATA_LENGTH    2

//
// Globals
//
volatile unsigned long msgCount = 0;

//
// Main
//
void main(void)
{
    uint16_t txMsgData[2], rxMsgData[2];

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Initialize GPIO and configure GPIO pins for CANTX/CANRX
    //
    Device_initGPIO();

    //
    // Board initialization
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
    // Start CAN module operations
    //
    CAN_startModule(myCAN0_BASE);

    //
    // Setup send and receive buffers
    //
    txMsgData[0] = 0x01;
    txMsgData[1] = 0x02;
    *(uint16_t *)rxMsgData = 0;

    //
    // Loop Forever - Send and Receive data continuously
    //
    for(;;)
    {
        //
        // Send CAN message data from message object 1
        //
        CAN_sendMessage(myCAN0_BASE, 1, MSG_DATA_LENGTH, txMsgData);

        //
        // Delay before receiving the data
        //
        DEVICE_DELAY_US(500000);

        //
        // Read CAN message object 2 and check for new data
        //
        if (CAN_readMessage(myCAN0_BASE, 2, rxMsgData))
        {
            //
            // Check that received data matches sent data.
            // Device will halt here during debug if data doesn't match.
            //
            if((txMsgData[0] != rxMsgData[0]) ||
               (txMsgData[1] != rxMsgData[1]))
            {
                asm(" ESTOP0");
            }
            else
            {
                //
                // Increment message received counter
                //
                msgCount++;
            }
        }
        else
        {
            //
            // Device will halt here during debug if no new data was received.
            //
            asm(" ESTOP0");
        }

        //
        // Increment the value in the transmitted message data.
        //
        txMsgData[0] += 0x01;
        txMsgData[1] += 0x01;

        //
        // Reset data if exceeds a byte
        //
        if(txMsgData[0] > 0xFF)
        {
            txMsgData[0] = 0;
        }
        if(txMsgData[1] > 0xFF)
        {
            txMsgData[1] = 0;
        }
    }
}

//
// End of File
//
