//#############################################################################
//
// FILE:   can_ex4_transmit_receive.c
//
// TITLE:  CAN Configuration for Transmit and Receive.
//
//! \addtogroup driver_example_cm_list
//! <h1> CAN Transmit and Receive Configurations </h1>
//!
//! This example shows the basic setup of CAN in order to transmit or receive
//! messages on the CAN bus with a specific Message ID. The CAN Controller is
//! configured according to the selection of the define.
//!
//! When the TRANSMIT define is selected, the CAN Controller acts as a
//! Transmitter and sends data to the second CAN Controller connected
//! externally.If TRANMSIT is not defined the CAN Controller acts as a Receiver
//! and waits for message to be transmitted by the External CAN Controller.
//!
//! Before running this example, please run the can_config_c28x example
//! from the c28x folder. It will initialize the clock, configure the GPIOs
//! and allocate CAN A to CM.
//!
//! \note CAN modules on the device need to be connected to via CAN
//!       transceivers. 
//!
//! \b Hardware \b Required \n
//!  - A C2000 board with CAN transceiver.
//!
//! \b External \b Connections \n
//!  - ControlCARD CANA is on GPIO37 (CANTXA) and GPIO36 (CANRXA)
//!
//! \b Watch \b Variables \b Transmit \Configuration \n
//!  - MSGCOUNT   - Adjust to set the number of messages
//!  - txMsgCount - A counter for the number of messages sent
//!  - txMsgData  - An array with the data being sent
//!  - errorFlag  - A flag that indicates an error has occurred
//!  - rxMsgCount - Has the initial value as No. of Messages to be received
//!                 and decrements with each message.
//!
//
//#############################################################################

//
// Included Files
//
#include "driverlib_cm.h"
#include "cm.h"

//
// Comment to Make the CAN Controller work as a Receiver.
//
#define TRANSMIT

//
// Defines
//
#ifdef TRANSMIT
#define TX_MSG_OBJ_ID    1
#else
#define RX_MSG_OBJ_ID    1
#endif
#define MSG_DATA_LENGTH  4
#define MSGCOUNT        10

//
// Globals
//
#ifdef TRANSMIT
volatile uint32_t txMsgCount = 0;
uint32_t txMsgSuccessful  = 1;
uint8_t txMsgData[4];
#else
volatile uint32_t rxMsgCount = MSGCOUNT;
uint8_t rxMsgData[4];
#endif

volatile unsigned long i;
volatile uint32_t errorFlag = 0;

//
// Function Prototypes
//
__interrupt void canaISR(void);

//
// Main
//
void main(void)
{
    volatile uint32_t delay;

    //
    // Initialize device clock and peripherals
    //
    CM_init();

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
    CAN_setBitRate(CANA_BASE, CM_CLK_FREQ, 500000, 16);

    //
    // Enable interrupts on the CAN A peripheral.
    //
    CAN_enableInterrupt(CANA_BASE, CAN_INT_IE0 | CAN_INT_ERROR |
                        CAN_INT_STATUS);

    //
    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    // This registers the interrupt handler in PIE vector table.
    //
    Interrupt_registerHandler(INT_CANA0, &canaISR);

    //
    // Enable the CAN-A interrupt signal
    //
    Interrupt_enable(INT_CANA0);

    CAN_enableGlobalInterrupt(CANA_BASE, CAN_GLOBAL_INT_CANINT0);

#ifdef TRANSMIT
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
                           CAN_MSG_OBJ_TX_INT_ENABLE, MSG_DATA_LENGTH);
    //
    // Initialize the transmit message object data buffer to be sent
    //
    txMsgData[0] = 0x12;
    txMsgData[1] = 0x34;
    txMsgData[2] = 0x56;
    txMsgData[3] = 0x78;
#else
    //
    // Initialize the receive message object used for receiving CAN messages.
    // Message Object Parameters:
    //      CAN Module: A
    //      Message Object ID Number: 1
    //      Message Identifier: 0x95555555
    //      Message Frame: Extended
    //      Message Type: Receive
    //      Message ID Mask: 0x0
    //      Message Object Flags: Receive Interrupt
    //      Message Data Length: 4 Bytes
    //
    CAN_setupMessageObject(CANA_BASE, RX_MSG_OBJ_ID, 0x95555555,
                           CAN_MSG_FRAME_EXT, CAN_MSG_OBJ_TYPE_RX, 0,
                           CAN_MSG_OBJ_RX_INT_ENABLE, MSG_DATA_LENGTH);
#endif

    //
    // Start CAN module A operations
    //
    CAN_startModule(CANA_BASE);

#ifdef TRANSMIT
    //
    // Transmit messages from CAN-A.
    //
    for(i = 0; i < MSGCOUNT; i++)
    {
        //
        // Check the error flag to see if errors occurred
        //
        if(errorFlag)
        {
            __asm("   bkpt #0");
        }

        //
        // Transmit the message.
        //
        CAN_sendMessage(CANA_BASE, TX_MSG_OBJ_ID, MSG_DATA_LENGTH,
                        txMsgData);

        //
        // Delay before continuing
        //
        for(delay = 0U; delay < 50000; delay++);

        while(txMsgSuccessful);
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

        //
        // Update the flag for next message.
        //
        txMsgSuccessful  = 1;
    }
#else
    //
    // Loop to keep receiving data from another CAN Controller.
    //
    while(rxMsgCount)
    {
    }
#endif

    //
    // Stop the application.
    //
    __asm("   bkpt #0");

}

//
// CAN A ISR - The interrupt service routine called when a CAN interrupt is
//             triggered on CAN module A.
//
__interrupt void
canaISR(void)
{
    uint32_t status;

    //
    // Read the CAN-B interrupt status to find the cause of the interrupt
    //
    status = CAN_getInterruptCause(CANA_BASE);

    //
    // If the cause is a controller status interrupt, then get the status
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
        status = CAN_getStatus(CANA_BASE);

        //
        // Check to see if an error occurred.
        //
#ifdef TRANSMIT
        if(((status  & ~(CAN_STATUS_TXOK)) != CAN_STATUS_LEC_MSK) &&
           ((status  & ~(CAN_STATUS_TXOK)) != CAN_STATUS_LEC_NONE))
#else
        if(((status  & ~(CAN_STATUS_RXOK)) != CAN_STATUS_LEC_MSK) &&
           ((status  & ~(CAN_STATUS_RXOK)) != CAN_STATUS_LEC_NONE))
#endif
        {
            //
            // Set a flag to indicate some errors may have occurred.
            //
            errorFlag = 1;
        }
    }
#ifdef TRANSMIT
    else if(status == TX_MSG_OBJ_ID)
    {
        //
        // Getting to this point means that the TX interrupt occurred on
        // message object 1, and the message TX is complete.  Clear the
        // message object interrupt.
        //
        CAN_clearInterruptStatus(CANA_BASE, TX_MSG_OBJ_ID);

        //
        // Increment a counter to keep track of how many messages have been
        // transmitted. In a real application this could be used to set flags to
        // indicate when a message is transmitted.
        //
        txMsgCount++;

        //
        // Since the message was transmitted, clear any error flags.
        //
        errorFlag = 0;

        //
        // Clear the message transmitted successful Flag.
        //
        txMsgSuccessful  = 0;
    }
#else
    else if(status == RX_MSG_OBJ_ID)
    {
        //
        // Get the received message
        //
        CAN_readMessage(CANA_BASE, RX_MSG_OBJ_ID, rxMsgData);

        //
        // Getting to this point means that the RX interrupt occurred on
        // message object 1, and the message RX is complete.  Clear the
        // message object interrupt.
        //
        CAN_clearInterruptStatus(CANA_BASE, RX_MSG_OBJ_ID);

        //
        // Decrement the counter after a message has been received.
        //
        rxMsgCount--;

        //
        // Since the message was received, clear any error flags.
        //
        errorFlag = 0;
    }
#endif
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
    CAN_clearGlobalInterruptStatus(CANA_BASE, CAN_GLOBAL_INT_CANINT0);
}

//
// End of File
//
