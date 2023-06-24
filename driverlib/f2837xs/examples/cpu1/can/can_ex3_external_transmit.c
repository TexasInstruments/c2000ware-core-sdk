//#############################################################################
//
// FILE:   can_ex3_external_transmit.c
//
// TITLE:   CAN External Transmit Example
//
//! \addtogroup driver_example_list
//! <h1> CAN-A to CAN-B External Transmit </h1>
//!
//! This example initializes CAN module A and CAN module B for external
//! communication. CAN-A module is setup to transmit incrementing data for "n"
//! number of times to the CAN-B module, where "n" is the value of TXCOUNT.
//! CAN-B module is setup to trigger an interrupt service routine (ISR) when
//! data is received. An error flag will be set if the transmitted data doesn't
//! match the received data.
//!
//! \note Both CAN modules on the device need to be
//!       connected to each other via CAN transceivers. GPIOs will be different
//!       on Launchpad.
//!
//! \b Hardware \b Required \n
//!  - A C2000 board with two CAN transceivers
//!
//! \b External \b Connections \n
//!  - ControlCARD CANA is on GPIO31 (CANTXA) and GPIO30 (CANRXA)
//!  - ControlCARD CANB is on GPIO8 (CANTXB) and GPIO10 (CANRXB)
//!
//!
//! \b Watch \b Variables \n
//!  - TXCOUNT - Adjust to set the number of messages to be transmitted
//!  - txMsgCount - A counter for the number of messages sent
//!  - rxMsgCount - A counter for the number of messages received
//!  - txMsgData - An array with the data being sent
//!  - rxMsgData - An array with the data that was received
//!  - errorFlag - A flag that indicates an error has occurred
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
#define TXCOUNT  100
#define MSG_DATA_LENGTH    4
#define TX_MSG_OBJ_ID      1
#define RX_MSG_OBJ_ID      1

//
// Globals
//
volatile unsigned long i;
volatile uint32_t txMsgCount = 0;
volatile uint32_t rxMsgCount = 0;
volatile uint32_t errorFlag = 0;
uint16_t txMsgData[4];
uint16_t rxMsgData[4];

//
// Function Prototypes
//
__interrupt void canbISR(void);     // Receive interrupt for CAN-B.
                                    // No Transmit interrupt for CAN-A
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
    // on module A and B. The device.h file may need to be modified to
    // reflect the chosen GPIO pins in your board.
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
    CAN_setBitRate(CANA_BASE, DEVICE_SYSCLK_FREQ, 500000, 20);
    CAN_setBitRate(CANB_BASE, DEVICE_SYSCLK_FREQ, 500000, 20);

    //
    // Enable interrupts on the CAN B peripheral.
    // Enables Int.line0, Error & Status Change interrupts
    //
    CAN_enableInterrupt(CANB_BASE, CAN_INT_IE0 | CAN_INT_ERROR |
                        CAN_INT_STATUS);

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
    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    // This registers the interrupt handler in PIE vector table.
    //
    Interrupt_register(INT_CANB0, &canbISR);

    //
    // Enable the CAN-B interrupt signal
    //
    Interrupt_enable(INT_CANB0);

	//
    // Set GLBINT0_EN bit in CAN_GLB_INT_EN register
	//
    CAN_enableGlobalInterrupt(CANB_BASE, CAN_GLOBAL_INT_CANINT0);

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
    //      No interrupts are enabled for the Transmit side
    //
    CAN_setupMessageObject(CANA_BASE, TX_MSG_OBJ_ID, 0x95555555,
                           CAN_MSG_FRAME_EXT, CAN_MSG_OBJ_TYPE_TX, 0,
                           CAN_MSG_OBJ_NO_FLAGS, MSG_DATA_LENGTH);

    //
    // Initialize the receive message object used for receiving CAN messages.
    // Message Object Parameters:
    //      CAN Module: B
    //      Message Object ID Number: 1
    //      Message Identifier: 0x95555555
    //      Message Frame: Extended
    //      Message Type: Receive
    //      Message ID Mask: 0x0
    //      Message Object Flags: Receive Interrupt
    //      Message Data Length: 4 Bytes (Note that DLC field is a "don't care"
    //      for a Receive mailbox)
    //
    CAN_setupMessageObject(CANB_BASE, RX_MSG_OBJ_ID, 0x95555555,
                           CAN_MSG_FRAME_EXT, CAN_MSG_OBJ_TYPE_RX, 0,
                           CAN_MSG_OBJ_RX_INT_ENABLE, MSG_DATA_LENGTH);

    //
    // Initialize the transmit message object data buffer to be sent
    //
    txMsgData[0] = 0x12;
    txMsgData[1] = 0x34;
    txMsgData[2] = 0x56;
    txMsgData[3] = 0x78;

    //
    // Start CAN module A and B operations
    //
    CAN_startModule(CANA_BASE);
    CAN_startModule(CANB_BASE);

    //
    // Transmit messages from CAN-A to CAN-B
    //
    for(i = 0; i < TXCOUNT; i++)
    {
        //
        // Check the error flag to see if errors occurred
        //
        if(errorFlag)
        {
            asm("   ESTOP0");
        }

        //
        // Verify that the number of transmitted messages equal the number of
        // messages received before sending a new message
        //
        if(txMsgCount == rxMsgCount)
        {
            CAN_sendMessage(CANA_BASE, TX_MSG_OBJ_ID, MSG_DATA_LENGTH,
                            txMsgData);
            txMsgCount++;
        }
        else
        {
            errorFlag = 1;
        }

        //
        // Delay 0.25 second before continuing
        //
        DEVICE_DELAY_US(250000);

        //
        // Increment the value in the transmitted message data.
        //
        txMsgData[0] += 0x01;
        txMsgData[1] += 0x01;
        txMsgData[2] += 0x01;
        txMsgData[3] += 0x01;

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
        if(txMsgData[2] > 0xFF)
        {
            txMsgData[2] = 0;
        }
        if(txMsgData[3] > 0xFF)
        {
            txMsgData[3] = 0;
        }
    }

    //
    // Stop application
    //
    asm("   ESTOP0");
}

//
// CAN B ISR - The interrupt service routine is called when an interrupt is
//             triggered on CAN module B. It will be executed twice for every
//             frame received.
//             First time for status-change; second time for Mailbox receive.
//
__interrupt void
canbISR(void)
{
    uint32_t status;

    //
    // Read the CAN-B interrupt status (in the CAN_INT register) to find the
    // cause of the interrupt
    //
    status = CAN_getInterruptCause(CANB_BASE);

    //
    // If the cause is a controller status interrupt, then get the status.
    // During first iteration of every ISR execution, status = 0x8000,
    // which simply means CAN_ES != 0x07.
    //
    if(status == CAN_INT_INT0ID_STATUS)
    {
        //
        // Read the controller status.  This will return a field of status
        // error bits that can indicate various errors.  Error processing
        // is not done in this example for simplicity.  Refer to the
        // API documentation for details about the error status bits.
        // The act of reading this status will clear the interrupt.
        //
        status = CAN_getStatus(CANB_BASE);  // Return CAN_ES value.
        //
		// Now status = 0x00000010, indicating RxOK.
        //

        //
        // Check to see if an error occurred.
        //
        if(((status  & ~(CAN_STATUS_RXOK)) != CAN_STATUS_LEC_MSK) &&
           ((status  & ~(CAN_STATUS_RXOK)) != CAN_STATUS_LEC_NONE))
        {
            //
            // Set a flag to indicate some errors may have occurred.
            //
            errorFlag = 1;
        }
    }
    //
    // Check if the cause is the CAN-B receive message object 1. Will be skipped
    // in the first iteration of every ISR execution
	//
    else if(status == RX_MSG_OBJ_ID)
    {
        //
        // Get the received message
        //
        CAN_readMessage(CANB_BASE, RX_MSG_OBJ_ID, rxMsgData);

        //
        // Getting to this point means that the RX interrupt occurred on
        // message object 1, and the message RX is complete.  Clear the
        // message object interrupt.
        //
        CAN_clearInterruptStatus(CANB_BASE, RX_MSG_OBJ_ID);

        //
        // Increment a counter to keep track of how many messages have been
        // received. In a real application this could be used to set flags to
        // indicate when a message is received.
        //
        rxMsgCount++;

        //
        // Since the message was received, clear any error flags.
        //
        errorFlag = 0;
    }
    //
    // If something unexpected caused the interrupt, this would handle it.
    //
    else
    {
        //
        // Spurious interrupt handling can go here.
        //
    }

    //
    // Clear the global interrupt flag for the CAN interrupt line
    //
    CAN_clearGlobalInterruptStatus(CANB_BASE, CAN_GLOBAL_INT_CANINT0);

    //
    // Acknowledge this interrupt located in group 9
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP9);
}

//
// End of File
//
