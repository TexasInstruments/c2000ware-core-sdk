//#############################################################################
//
// FILE:   can_ex8_remote_tx.c
//
// TITLE:   CAN Remote-Frame Transmit  Example
//
//! \addtogroup driver_example_list
//! <h1> CAN-A Remote-Frame Transmit </h1>
//!
//! This example initializes CAN module A for external communication.
//! It demonstrates the ability of the module to transmit a Remote-frame
//! and receive a response in the same mailbox. CAN-B node is configured
//! to respond to the Remote frame. No interrupts are used.
//!
//! \b Hardware \b Required \n
//!  - A C2000 board with CAN transceiver and another CAN node configured
//!    for the same bit-rate to provide the response to the Remote frame.
//!    In this example, CAN-B is the "other node".
//!
//! \b Watch \b Variables \n
//!  - TXCOUNT - Adjust to set the number of Remote frames to be transmitted
//!  - txMsgCount - A counter for the number of messages sent
//!  - rxMsgData - An array with the data being received
//!
//
//#############################################################################
//
// $Release Date:  $
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

//
// Defines
//
#define TXCOUNT            1
#define MSG_DATA_LENGTH    8
#define TX_MSG_OBJ_ID      1

//
// Globals
//
volatile unsigned long i;
volatile uint32_t txMsgCount = 0;

//
// Buffer to store the message Received by node A
//
uint16_t rxMsgData[8];

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
    // Initialize GPIO and configure GPIO pins for CANTX/CANRX
    // on modules A & B
    //
    Device_initGPIO();
    GPIO_setPinConfig(DEVICE_GPIO_CFG_CANRXA);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_CANTXA);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_CANRXB);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_CANTXB);

    //
    // Initialize the CAN controllers
    //
    CAN_initModule(CANA_BASE);
    CAN_initModule(CANB_BASE);

    //
    // Set up the CAN bus bit rate to 500kHz for each module
    // Refer to the Driver Library User Guide for information on how to set
    // tighter timing control. Additionally, consult the device data sheet
    // for more information about the CAN module clocking.
    //
    CAN_setBitRate(CANA_BASE, DEVICE_SYSCLK_FREQ, 500000, 16);
    CAN_setBitRate(CANB_BASE, DEVICE_SYSCLK_FREQ, 500000, 16);

    //
    // Initialize the mailbox used for sending the remote frame
    // - and receiving the corresponding data frame
    // Message Object Parameters:
    //      CAN Module: A
    //      Message Object ID Number: 1
    //      Message Identifier: 0x111
    //      Message Frame: Standard
    //      Message Type: Receive (but transmits a Remote frame first)
    //      Message ID Mask: 0x0
    //      Message Object Flags: None
    //      Message Data Length: 8 Bytes
    //
    CAN_setupMessageObject(CANA_BASE, TX_MSG_OBJ_ID, 0x111,
                           CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_RX, 0,
                           CAN_MSG_OBJ_NO_FLAGS, MSG_DATA_LENGTH);

    //
    // Initialize the mailbox used for responding to the remote frame
    // Message Object Parameters:
    //      CAN Module: B
    //      Message Object ID Number: 1
    //      Message Identifier: 0x111
    //      Message Frame: Standard
    //      Message Type: Transmit (Auto respond to a remote frame)
    //      Message ID Mask: 0x0
    //      Message Object Flags: None
    //      Message Data Length: 8 Bytes ("Don't care" for this MBX)
    //
    CAN_setupMessageObject(CANB_BASE, TX_MSG_OBJ_ID, 0x111,
                           CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_RXTX_REMOTE, 0,
                           CAN_MSG_OBJ_NO_FLAGS, MSG_DATA_LENGTH);

    //
    // Initialize the receive buffer to a known value
    //
    rxMsgData[0] = 0;
    rxMsgData[1] = 0;
    rxMsgData[2] = 0;
    rxMsgData[3] = 0;
    rxMsgData[4] = 0;
    rxMsgData[5] = 0;
    rxMsgData[6] = 0;
    rxMsgData[7] = 0;

    //
    // Start CAN module operations
    //
    CAN_startModule(CANA_BASE);
    CAN_startModule(CANB_BASE);

    //
    // Copy data into the mailbox1 RAM of CAN-B. This is the data that will be
    // automatically transmitted in response to  a remote frame.
    //
    // Wait for busy bit to clear
    //
    while((HWREGH(CANB_BASE + CAN_O_IF1CMD) & CAN_IF1CMD_BUSY) ==
	      CAN_IF1CMD_BUSY)
    {
    }

	//
	// Write to IF1DATA & IF1DATB registers
	//
    HWREG_BP(CANB_BASE + CAN_O_IF1DATA)  =  0x67452301UL;
    HWREG_BP(CANB_BASE + CAN_O_IF1DATB)  =  0xEFCDAB89UL;

	//
    // Transfer to MBX RAM
	//
	HWREG_BP(CANB_BASE + CAN_O_IF1CMD)  =  0x00830001UL;

    //
    // Wait for busy bit to clear
    //
    while((HWREGH(CANB_BASE + CAN_O_IF1CMD) & CAN_IF1CMD_BUSY) ==
           CAN_IF1CMD_BUSY)
    {
    }

    //
    // Transmit Remote frame(s) from CAN-A and await data frame(s) from node B
    //
    //while(1)  // Uncomment for infinite transmissions
    for(i = 0; i < TXCOUNT; i++)
    {
        //
        // Initiate transmission of remote frame. "rxMsgData" is "dummy"
        // No data will go out on a Remote Frame
        //
        CAN_sendMessage(CANA_BASE, TX_MSG_OBJ_ID, MSG_DATA_LENGTH, rxMsgData);

        //
        // Poll TxOk bit in CAN_ES register to check completion of transmission
        //
        while(((HWREG_BP(CANA_BASE + CAN_O_ES) & CAN_ES_TXOK)) !=
		        CAN_ES_TXOK){}

        txMsgCount++; // Increment TX counter

        //
        // Poll RxOk bit in CAN_ES register to check completion of reception
        //
        while(((HWREG_BP(CANA_BASE + CAN_O_ES) & CAN_ES_RXOK)) !=
        		CAN_ES_RXOK){}

        CAN_readMessage(CANA_BASE, 1, rxMsgData);
    }

    //
    // Stop application
    //
    asm("   ESTOP0");
}

//
// End of File
//
