//#############################################################################
//
// FILE:   can_ex1_loopback.c
//
// TITLE:   CAN Loopback Example
//
//! \addtogroup driver_example_cm_list
//! <h1> CAN Loopback </h1>
//!
//! This example shows the basic setup of CAN in order to transmit and receive
//! messages on the CAN bus.  The CAN peripheral is configured to transmit
//! messages with a specific CAN ID. The message that is sent is
//! a 2 byte message that contains an incrementing pattern.
//!
//! This example sets up the CAN controller in External Loopback test mode.
//! Data transmitted is visible on the CANTXA pin and is received internally
//! back to the CAN Core. Please refer to details of the External Loopback
//! Test Mode in the CAN Chapter in the Technical Reference Manual.
//!
//! Before running this example, please run the can_config_c28x example
//! from the c28x folder. It will initialize the clock, configure the GPIOs
//! and allocate CAN A to CM.
//!
//! \b External \b Connections \n
//!  - None.
//!
//! \b Watch \b Variables \n
//!  - msgCount - A counter for the number of successful messages received.
//!  - rxMsgData - An array with the data that was received.
//!  - txMsgData - An array with the data being sent.
//!
//
//#############################################################################

//
// Included Files
//
#include "cm.h"

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
    volatile uint32_t delay;
    uint8_t txMsgData[2], rxMsgData[2];

    //
    // Initialize device clock and peripherals
    //
    CM_init();

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
    CAN_setBitRate(CANA_BASE, CM_CLK_FREQ, 500000, 16);

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
        for(delay = 0U; delay < 50000; delay++);

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
                //
                // Device will halt here if transmitted and received data are
                // not same.
                //
                __asm("   bkpt #0");
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
            __asm("   bkpt #0");
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
