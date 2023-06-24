//#############################################################################
//
// FILE:   erad_ex3_stackoverflow.c
//
// TITLE:  ERAD Stack Overflow Example
//
//! \addtogroup driver_example_list
//! <h1> ERAD Stack Overflow </h1>
//!
//! This example shows the basic setup of CAN in order to transmit and receive
//! messages on the CAN bus.  The CAN peripheral is configured to transmit
//! messages with a specific CAN ID.  A message is then transmitted once per
//! second, using a simple delay loop for timing.  The message that is sent is
//! a 2 byte message that contains an incrementing pattern.
//!
//! This example sets up the CAN controller in External Loopback test mode.
//! Data transmitted is visible on the CANTXA pin and is received internally
//! back to the CAN Core.
//!
//! A buffer is created to store message history up to 50 messages for the
//! duration of the program. A logic error is intentionally made to allow the
//! buffer to overflow, eventually causing a stack overflow. The included
//! JavaScript file, stack_overflow.js, programs ERAD registers in order to
//! detect the stack overflow and halt the CPU once the illegal write is made.
//! The illegal write is made after 507 messages are received.
//!
//! To properly use the provided ERAD script, the following variables must be
//! set in the scripting environment prior to launching the ERAD script:
//!
//! - var PROJ_NAME = "erad_debugger_ex3_stackoverflow"
//! - var PROJ_WKSPC_LOC = <proj_workspace_path>
//!
//! To run the ERAD script, use the following command in the scripting console:
//!
//! - loadJSFile("<proj_workspace_path>\\erad_debugger_ex3_stackoverflow\\erad_ex3_stack_overflow.js", 0);
//!
//! Note that the script must be run after loading and running the .out on the
//! C28x core. 
//!
//! The included JavaScript file, erad_ex3_stack_overflow.js, uses Debug Server
//! Scripting (DSS) features. For information on using the DSS, please visit:
//! http://software-dl.ti.com/ccs/esd/documents/users_guide/sdto_dss_handbook.html
//!
//! This example uses 1 HW watchpoint :
//!  - HWBP_1 : Data Write Address Bus = Stack end address + 1
//!
//! \b External \b Connections \n
//!  - None.
//!
//! \b Watch \b Variables \n
//!  - msgCount - A counter for the number of successful messages received
//!  - txMsgData - An array with the data being sent
//!  - rxMsgData - An array with the data that was received
//!  - msgHistoryBuff - An array meant to store the last 50 messages received
//!
//! \b Profiling \b Script \b Output
//!  - "STACK OVERFLOW detected. Halting CPU." will be printed in the scripting
//!    console when a stack overflow occurs (that is, when the watchpoint is hit)
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
#define MSG_DATA_LENGTH    2

//
// Globals
//
volatile unsigned long msgCount = 0;

//
// Stack start and end addresses
//
extern uint16_t _stack;
extern uint16_t _STACK_END;

//
// Main
//
void main(void)
{
    //
    // Setup transfer and receive buffers
    //
    uint16_t txMsgData[2], rxMsgData[2];

    //
    // Create buffer to hold message history up to 50 messages
    //
    volatile uint32_t msgHistoryBuff[50];

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Initialize GPIO and configure GPIO pins for CANTX/CANRX
    //
    Device_initGPIO();
    GPIO_setPinConfig(DEVICE_GPIO_CFG_CANRXA);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_CANTXA);

    //
    // Initialize the CAN controller
    //
    CAN_initModule(CANA_BASE);

    //
    // Set up the CAN bus bit rate to 500kHz
    // Refer to the Driver Library User Guide for information on how to set
    // tighter timing control. Additionally, consult the device data sheet
    // for more information about the CAN module clocking.
    //
    CAN_setBitRate(CANA_BASE, DEVICE_SYSCLK_FREQ, 500000, 16);

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
    // Enable CAN test mode with external loopback
    //
    CAN_enableTestMode(CANA_BASE, CAN_TEST_EXL);

    //
    // Initialize the transmit message object used for sending CAN messages.
    // Message Object Parameters:
    //      Message Object ID Number: 1
    //      Message Identifier: 0x1234
    //      Message Frame: Standard
    //      Message Type: Transmit
    //      Message ID Mask: 0x0
    //      Message Object Flags: None
    //      Message Data Length: 2 Bytes
    //
    CAN_setupMessageObject(CANA_BASE, 1, 0x1234, CAN_MSG_FRAME_STD,
                           CAN_MSG_OBJ_TYPE_TX, 0, CAN_MSG_OBJ_NO_FLAGS, 
                           MSG_DATA_LENGTH);

    //
    // Initialize the receive message object used for receiving CAN messages.
    // Message Object Parameters:
    //      Message Object ID Number: 2
    //      Message Identifier: 0x1234
    //      Message Frame: Standard
    //      Message Type: Receive
    //      Message ID Mask: 0x0
    //      Message Object Flags: None
    //      Message Data Length: 2 Bytes
    //
    CAN_setupMessageObject(CANA_BASE, 2, 0x1234, CAN_MSG_FRAME_STD,
                           CAN_MSG_OBJ_TYPE_RX, 0, CAN_MSG_OBJ_NO_FLAGS, 
                           MSG_DATA_LENGTH);

    //
    // Start CAN module operations
    //
    CAN_startModule(CANA_BASE);    

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
        CAN_sendMessage(CANA_BASE, 1, MSG_DATA_LENGTH, txMsgData);

        //
        // Delay before receiving the data
        //
        DEVICE_DELAY_US(50000);

        //
        // Read CAN message object 2 and check for new data
        //
        if (CAN_readMessage(CANA_BASE, 2, rxMsgData))
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
                // Store message in message history buffer and increment message
                // received counter. Purposely leave out logic to reset counter
                // when buffer is full, eventually causing a stack overflow
                //
                uint32_t message =
                    (uint32_t)rxMsgData[0] | ((uint32_t)rxMsgData[1] << 16);
                msgHistoryBuff[msgCount++] = message;
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
