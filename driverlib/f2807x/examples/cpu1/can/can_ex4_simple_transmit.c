//#############################################################################
//
// FILE:   can_ex4_simple_transmit.c
//
// TITLE:   CAN simple External Transmit Example
//
//! \addtogroup driver_example_list
//! <h1> CAN-A External Transmit </h1>
//!
//! This example initializes CAN module A for external communication.
//! CAN-A module is setup to transmit data for "n" number of times,
//! where "n" is the value of TXCOUNT. Another CAN node configured for the
//! same bit-rate is needed to provide the ACK. No interrupts are used.
//!
//! \b Hardware \b Required \n
//!  - A C2000 board with CAN transceiver and another CAN node configured
//!    for the same bit-rate to provide the ACK.
//!
//! \b Watch \b Variables \n
//!  - TXCOUNT - Adjust to set the number of messages to be transmitted
//!  - txMsgCount - A counter for the number of messages sent
//!  - txMsgData - An array with the data being sent
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
#define TXCOUNT  100000
#define MSG_DATA_LENGTH    8
#define TX_MSG_OBJ_ID      1

//
// Globals
//
volatile unsigned long i;
volatile uint32_t txMsgCount = 0;
uint16_t txMsgData[8];

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
    // on module A
    //
    Device_initGPIO();
    GPIO_setPinConfig(DEVICE_GPIO_CFG_CANRXA);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_CANTXA);

    //
    // Initialize the CAN controllers
    //
    CAN_initModule(CANA_BASE);

    //
    // Set up the CAN bus bit rate to 500kHz for each module
    // Refer to the Driver Library User Guide for information on how to set
    // tighter timing control. Additionally, consult the device data sheet
    // for more information about the CAN module clocking.
    //
    CAN_setBitRate(CANA_BASE, DEVICE_SYSCLK_FREQ, 500000, 16);

    //
    // Initialize the transmit message object used for sending CAN messages.
    // Message Object Parameters:
    //      CAN Module: A
    //      Message Object ID Number: 1
    //      Message Identifier: 0x95555555
    //      Message Frame: Extended
    //      Message Type: Transmit
    //      Message ID Mask: 0x0
    //      Message Object Flags: None
    //      Message Data Length: 4 Bytes
    //
    CAN_setupMessageObject(CANA_BASE, TX_MSG_OBJ_ID, 0x95555555,
                           CAN_MSG_FRAME_EXT, CAN_MSG_OBJ_TYPE_TX, 0,
                           CAN_MSG_OBJ_NO_FLAGS, MSG_DATA_LENGTH);

    //
    // Initialize the transmit message object data buffer to be sent
    //
    txMsgData[0] = 0x01;
    txMsgData[1] = 0x23;
    txMsgData[2] = 0x45;
    txMsgData[3] = 0x67;
    txMsgData[4] = 0x89;
    txMsgData[5] = 0xAB;
    txMsgData[6] = 0xCD;
    txMsgData[7] = 0xEF;

    //
    // Start CAN module A operations
    //
    CAN_startModule(CANA_BASE);

    //
    // Transmit messages from CAN-A
    //
    while(1)
    //
    // Comment for infinite transmissions
    //
    //for(i = 0; i < TXCOUNT; i++)
    //
	{
        CAN_sendMessage(CANA_BASE, TX_MSG_OBJ_ID, MSG_DATA_LENGTH, txMsgData);

        //
        // Poll TxOk bit in CAN_ES register to check completion of transmission
        //
        while(((HWREGH(CANA_BASE + CAN_O_ES) & CAN_ES_TXOK)) !=  CAN_ES_TXOK)
		{
		}
    }
    //
    // Stop application
    //
    asm("   ESTOP0");
}

//
// End of File
//
