//#############################################################################
//
// FILE:   can_ex9_remote_answer.c
//
// TITLE:   CAN Remote-Frame Auto-answer Example
//
//! \addtogroup driver_example_list
//! <h1> CAN-A Remote-Frame Auto-answer </h1>
//!
//! This example initializes CAN module A for external communication.
//! It demonstrates the ability of the module to respond to a Remote-frame.
//!
//! \b Hardware \b Required \n
//!  - A C2000 board with CAN transceiver and another CAN node configured
//! for the same bit-rate to transmit the Remote frame.
//!
//!
//! \b Watch \b Variables \n
//!
//!  - txMsgCount - A counter for the number of data frames sent
//!
//
//#############################################################################
//
// $Release  $
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
#define MSG_DATA_LENGTH    8
#define TX_MSG_OBJ_ID    1

//
// Globals
//
volatile uint32_t txMsgCount = 0;

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
    // Initialize the mailbox used for sending the data frame
    // Message Object Parameters:
    //      CAN Module: A
    //      Message Object ID Number: 1
    //      Message Identifier: 0x111
    //      Message Frame: Standard
    //      Message Type: Transmit (with auto-answer)
    //      Message ID Mask: 0x0
    //      Message Object Flags: None
    //      Message Data Length: 8 Bytes
    //
    CAN_setupMessageObject(CANA_BASE, TX_MSG_OBJ_ID, 0x111,
                           CAN_MSG_FRAME_STD, CAN_MSG_OBJ_TYPE_RXTX_REMOTE, 0,
                           CAN_MSG_OBJ_NO_FLAGS, MSG_DATA_LENGTH);

    //
    // Start CAN module operations
    //
    CAN_startModule(CANA_BASE);

    //
    // Copy data into the mailbox1 RAM of CAN-A. This is the data that will be
    // automatically transmitted in response to  a remote frame.

    //
    // Wait for busy bit to clear
    //
    while((HWREGH(CANA_BASE +CAN_O_IF1CMD) & CAN_IF1CMD_BUSY)==CAN_IF1CMD_BUSY)
    {
    }

	//
	// Write to IF1DATA & IF1DATB registers
	//
    HWREG_BP(CANA_BASE + CAN_O_IF1DATA)  =  0x44332211UL;
    HWREG_BP(CANA_BASE + CAN_O_IF1DATB)  =  0x88776655UL;

	//
    // Transfer to MBX RAM
	//
	HWREG_BP(CANA_BASE + CAN_O_IF1CMD)  =  0x00830001UL;

    //
    // Wait for busy bit to clear
    //
    while((HWREGH(CANA_BASE + CAN_O_IF1CMD) & CAN_IF1CMD_BUSY) ==
           CAN_IF1CMD_BUSY)
    {
    }

    //
    // Wait and Transmit data frame(s)in response to Remote frame(s)
    //
    while(1)
    {
        //
        // Poll TxOk bit in CAN_ES register to check completion of transmission
        //
        while(((HWREGH(CANA_BASE + CAN_O_ES) & CAN_ES_TXOK)) !=  CAN_ES_TXOK)
		{
		}

        txMsgCount++; // Increment TX counter
    }
}

//
// End of File
//
