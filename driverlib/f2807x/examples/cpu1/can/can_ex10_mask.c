//#############################################################################
//
// FILE:   can_ex10_mask.c
//
// TITLE:   CAN Acceptance Mask Example
//
//! \addtogroup driver_example_list
//! <h1> CAN example that illustrates the usage of Mask registers </h1>
//!
//! This example initializes CAN module A for Reception. When a frame with a
//! matching filter criterion is received, the data will be copied in mailbox 1
//! and GPIO65 will be toggled a few times and the code gets ready for the next
//! frame. If a message of any other MSGID is received, an ACK will be provided
//! Completion of reception is determined by polling CAN_NDAT_21 register.
//! No interrupts are used.
//!
//! \b Hardware \b Required \n
//!  - An external CAN node that transmits to CAN-A on the C2000 MCU
//!
//!
//! \b Watch \b Variables \n
//!  - rxMsgCount - A counter for the number of messages received
//!  - rxMsgData - An array with the data that was received
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
#define MSG_DATA_LENGTH    0    // "Don't care" for a Receive mailbox
#define RX_MSG_OBJ_ID      1    // Use mailbox 1

//
// Globals
//
uint16_t rxMsgData[8];          // Buffer for received data
uint16_t Toggle_ctr;            // GPIO toggle counter
volatile uint32_t rxMsgCount = 0;

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
	// Configure GPIO pins for CANTX/CANRX
	//
    GPIO_setPinConfig(DEVICE_GPIO_CFG_CANRXA);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_CANTXA);

    //
	// Configure GPIO pin which is toggled upon message reception
	//
    GPIO_setPadConfig(65U, GPIO_PIN_TYPE_STD);
    GPIO_setDirectionMode(65U, GPIO_DIR_MODE_OUT);

    //
    // Initialize the receive buffer to a known value
    //
    rxMsgData[0] = 0xDEAD;
    rxMsgData[1] = 0xDEAD;
    rxMsgData[2] = 0xDEAD;
    rxMsgData[3] = 0xDEAD;
    rxMsgData[4] = 0xDEAD;
    rxMsgData[5] = 0xDEAD;
    rxMsgData[6] = 0xDEAD;
    rxMsgData[7] = 0xDEAD;

    //
    // Initialize the CAN controller
    //
    CAN_initModule(CANA_BASE);

    //
    // Set up the CAN bus bit rate to 500kbps for each module
    // Refer to the Driver Library User Guide for information on how to set
    // tighter timing control. Additionally, consult the device data sheet
    // for more information about the CAN module clocking.
    //
    CAN_setBitRate(CANA_BASE, DEVICE_SYSCLK_FREQ, 500000, 16);

    //
    // Initialize the receive message object used for receiving CAN messages.
	// Possible flags: CAN_MSG_OBJ_NO_FLAGS, CAN_MSG_OBJ_USE_EXT_FILTER,
	//                 CAN_MSG_OBJ_USE_DIR_FILTER
    // Message Object Parameters:
    //      CAN Module: A
    //      Message Object ID Number: 1
    //      Message Identifier: 0x1F9FFFFA
    //      Message Frame: Extended
    //      Message Type: Receive
    //      Message ID Mask: 0x1F000000
    //      Message Object Flags: UMask, MXtd, MDir
    //      Message Object flag CAN_MSG_OBJ_USE_ID_FILTER enables usage 
    //       of msgIDMask parameter for Message Identifier based filtering
    //      Message Data Length: "Don't care" for a Receive mailbox
    CAN_setupMessageObject(CANA_BASE, RX_MSG_OBJ_ID, 0x1F9FFFFA,
                           CAN_MSG_FRAME_EXT, CAN_MSG_OBJ_TYPE_RX, 0x1F000000,
                           (CAN_MSG_OBJ_USE_ID_FILTER | CAN_MSG_OBJ_NO_FLAGS),
   						   MSG_DATA_LENGTH);

    //
    // Start CAN module A operations
    //
    CAN_startModule(CANA_BASE);

    //
	// Start reception - Just wait for data from another node
    //
    while(1)
    {
        //
        // Poll bit0 in CAN_NDAT_21 register to check completion of Reception
        //
        if((HWREG_BP(CANA_BASE + CAN_O_NDAT_21))  == 0x00000001)
        {
            //
            // Get the received message
            //
            asm("  NOP");
            CAN_readMessage(CANA_BASE, RX_MSG_OBJ_ID, rxMsgData);   // Will this clear NewDat?

            rxMsgCount++;
            for(Toggle_ctr=0; Toggle_ctr<100; Toggle_ctr++)
            {
                GPIO_togglePin(65U);
                DEVICE_DELAY_US(100000);
            }
        }
    }
}

//
// End of File
//
