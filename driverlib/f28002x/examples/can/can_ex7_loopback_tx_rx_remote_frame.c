//#############################################################################
//
// FILE:   can_ex7_loopback_tx_rx_remote_frame.c
//
// TITLE:   CAN Remote Request Loopback Example
//
//! \addtogroup driver_example_list
//! <h1> CAN Remote Request Loopback </h1>
//!
//! This example shows the basic setup of CAN in order to transmit a remote frame
//! and get a response for the remote frame and store it in a receive Object.
//! The CAN peripheral is configured to transmit remote request frame and a
//! remote answer frame messages with a specific CAN ID. Message object 3 is
//! configured to transmit a remote request. Message object 2 is configured as
//! a remote answer object with filter mask such that it accepts remote frame
//! with any message ID and transmit's remote answer with message ID 7 and data
//! length 8. Message object 1 is configured as a received object with filter
//! message ID 7 so as to store the remote answer data transmitted by message
//! object 2.
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
//!  - txMsgData - An array with the data being sent
//!  - rxMsgData - An array with the data that was received
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
    uint16_t rxMsgData[8];

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
    // Setup receive buffers
    //
    *(uint16_t *)rxMsgData = 0;

    while((HWREGH(myCAN0_BASE + CAN_O_IF1CMD) & CAN_IF1CMD_BUSY) ==
          CAN_IF1CMD_BUSY)
    {
    }

    //
    // Write to IF1DATA & IF1DATB registers send buffer
    //
    HWREG_BP(myCAN0_BASE + CAN_O_IF1DATA)  =  0x76543210UL;
    HWREG_BP(myCAN0_BASE + CAN_O_IF1DATB)  =  0xFEDCBA98UL;

    //
    // Transfer to MBX RAM (refer to IFxCMD bit field for explanation).
    // Configuring message object 2 to respond to a remote frame with
    // a data length 8 bytes.
    //
    HWREG_BP(myCAN0_BASE + CAN_O_IF1CMD)  =  0x00830002UL;

    //
    // Wait for busy bit to clear
    //
    while((HWREGH(myCAN0_BASE + CAN_O_IF1CMD) & CAN_IF1CMD_BUSY) ==
           CAN_IF1CMD_BUSY)
    {
    }
    //
    // Loop Forever - Send and Receive data continuously
    //
    for(;;)
    {
        //
        // Send CAN remote request frame from message object 3
        //
        CAN_sendRemoteRequestMessage(myCAN0_BASE, 3);

        //
        // Delay before receiving the data
        //
        DEVICE_DELAY_US(1000000);

        //
        // Read CAN message object 1 and check for new data
        // received by the response to the remote request from
        // message object 2
        //
        if (CAN_readMessage(myCAN0_BASE, 1, rxMsgData))
        {
            //
            // Check that received data matches sent data.
            // Device will halt here during debug .
            //
            asm(" ESTOP0");
        }
        else
        {
            //
            // Device will halt here during debug if no new data was received.
            //
            asm(" ESTOP0");
        }
    }
}

//
// End of File
//
