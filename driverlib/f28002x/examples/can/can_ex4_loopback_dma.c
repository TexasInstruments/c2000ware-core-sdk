//#############################################################################
//
// FILE:   can_ex4_loopback_dma.c
//
// TITLE:   CAN External Loopback with DMA Example
//
//! \addtogroup driver_example_list
//! <h1> CAN External Loopback with DMA </h1>
//!
//! This example sets up the CAN module to transmit and receive
//! messages on the CAN bus. The CAN module is set to transmit a 4 byte
//! message internally. An interrupt is used to assert the DMA request line
//! which then triggers the DMA to transfer the received data from the CAN
//! interface register to the receive buffer array. A data check is performed
//! once the transfer is complete.
//!
//! This example sets up the CAN controller in External Loopback test mode.
//! Data transmitted is visible on the CANTXA pin and is received internally
//! back to the CAN Core. Please refer to details of the External Loopback
//! Test Mode in the CAN Chapter in the Technical Reference Manual. Please
//! refer to the appnote Programming Examples and Debug Strategies for
//! the DCAN Module (www.ti.com/lit/SPRACE5) for useful information about
//! this example
//!
//! \b External \b Connections \n
//!  - None.
//!
//! \b Watch \b Variables \n
//!  - txMsgCount - A counter for the number of messages sent
//!  - rxMsgCount - A counter for the number of messages received
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

//
// Defines
//
#define MSG_DATA_LENGTH    4
#define TX_MSG_OBJ_ID    1
#define RX_MSG_OBJ_ID    2
#define DMA_BURST       2
#define DMA_TRANSFER    1
#define CAN_IF2    2

//
// Globals
//
volatile uint32_t txMsgCount = 0;
volatile uint32_t rxMsgCount = 0;
uint16_t txMsgData[4] = {0x12, 0x34, 0x56, 0x78};
uint16_t rxMsgData[2] = {0xFFFF, 0xFFFF};
volatile uint16_t done = 0;

// Place buffers in GSRAM
#pragma DATA_SECTION(txMsgData, "ramgs0");
#pragma DATA_SECTION(rxMsgData, "ramgs0");

//
// Function Prototypes
//
void initDMA(void);
__interrupt void dmaCh5ISR(void);
__interrupt void canISR(void);

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
    CAN_setBitRate(CANA_BASE, DEVICE_SYSCLK_FREQ, 500000, 20);

    //
    // Enable interrupts on the CAN peripheral.
    //
    CAN_enableInterrupt(CANA_BASE, CAN_INT_IE0 | CAN_INT_ERROR |
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
    Interrupt_register(INT_CANA0, &canISR);
    Interrupt_register(INT_DMA_CH5, &dmaCh5ISR);

    //
    // Setup the DMA for CAN use
    //
    initDMA();

    //
    // Enable the CAN DMA request lines for IF1, IF2, and IF3
    //
    CAN_enableDMARequests(CANA_BASE);

    //
    // Enable the CAN and DMA interrupt signal
    //
    Interrupt_enable(INT_DMA_CH5);
    Interrupt_enable(INT_CANA0);
    CAN_enableGlobalInterrupt(CANA_BASE, CAN_GLOBAL_INT_CANINT0);

    //
    // Enable CAN test mode with external loopback
    //
    CAN_enableTestMode(CANA_BASE, CAN_TEST_EXL);

    //
    // Initialize the transmit message object used for sending CAN messages.
    // Message Object Parameters:
    //      Message Object ID Number: 1
    //      Message Identifier: 0x1
    //      Message Frame: Standard
    //      Message Type: Transmit
    //      Message ID Mask: 0x0
    //      Message Object Flags: Transmit Interrupt
    //      Message Data Length: 4 Bytes
    //
    CAN_setupMessageObject(CANA_BASE, TX_MSG_OBJ_ID, 0x1, CAN_MSG_FRAME_STD,
                           CAN_MSG_OBJ_TYPE_TX, 0, CAN_MSG_OBJ_TX_INT_ENABLE,
                           MSG_DATA_LENGTH);

    //
    // Initialize the receive message object used for receiving CAN messages.
    // Message Object Parameters:
    //      Message Object ID Number: 2
    //      Message Identifier: 0x1
    //      Message Frame: Standard
    //      Message Type: Receive
    //      Message ID Mask: 0x0
    //      Message Object Flags: Receive Interrupt
    //      Message Data Length: 4 Bytes (Note that DLC field is a "don't care"
    //      for a Receive mailbox
    //
    CAN_setupMessageObject(CANA_BASE, RX_MSG_OBJ_ID, 0x1, CAN_MSG_FRAME_STD,
                           CAN_MSG_OBJ_TYPE_RX, 0, CAN_MSG_OBJ_RX_INT_ENABLE,
                           MSG_DATA_LENGTH);

    //
    // Start CAN module operations
    //
    CAN_startModule(CANA_BASE);

    //
    // Start the DMA channel
    //
    DMA_startChannel(DMA_CH5_BASE);

    //
    // Transmit the CAN message
    //
    CAN_sendMessage(CANA_BASE, TX_MSG_OBJ_ID, MSG_DATA_LENGTH,
                    txMsgData);

    //
    // Wait until the CAN message is received and the DMA transfer is complete
    //
    while(!done);

    //
    // When the DMA transfer is complete, the program will stop here
    //
    ESTOP0;
}

//
// initDMA - Initialize the DMA controller and configure DMA channel 5 to
//           transfer the received CAN data into the specified RX buffer
//
void initDMA()
{
    //
    // Initialize DMA
    //
    DMA_initController();

    //
    // Configure DMA Ch5 for RX. When the CAN asserts the DMA line, the DMA
    // will transfer the contents of the IF2 data register into the RX buffer
    //
    DMA_configAddresses(DMA_CH5_BASE, rxMsgData,
                        (uint16_t *)(CANA_BASE + CAN_O_IF2DATA));
    DMA_configBurst(DMA_CH5_BASE, DMA_BURST, 2, 1);
    DMA_configTransfer(DMA_CH5_BASE, DMA_TRANSFER, 0, 0);
    DMA_configMode(DMA_CH5_BASE, DMA_TRIGGER_CANAIF2, DMA_CFG_ONESHOT_DISABLE |
                   DMA_CFG_CONTINUOUS_DISABLE | DMA_CFG_SIZE_16BIT);

    //
    // Configure DMA Ch5 interrupts
    //
    DMA_setInterruptMode(DMA_CH5_BASE, DMA_INT_AT_END);
    DMA_enableInterrupt(DMA_CH5_BASE);
    DMA_enableTrigger(DMA_CH5_BASE);
}

//
// CAN ISR - The interrupt service routine called when a CAN interrupt is
//           triggered.  It checks for the cause of the interrupt, and
//           maintains a count of all messages that have been transmitted.
//
__interrupt void
canISR(void)
{
    uint32_t status;

    //
    // Read the CAN interrupt status to find the cause of the interrupt
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
        if(((status  & ~(CAN_STATUS_TXOK | CAN_STATUS_RXOK)) != 7) &&
           ((status  & ~(CAN_STATUS_TXOK | CAN_STATUS_RXOK)) != 0))
        {
            // Something went wrong. rData doesn't contain expected data.
            ESTOP0;
        }
    }

    //
    // Check if the cause is the transmit message object 1
    //
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
        // sent.  In a real application this could be used to set flags to
        // indicate when a message is sent.
        //
        txMsgCount++;
    }

    //
    // Check if the cause is the receive message object 2
    //
    else if(status == RX_MSG_OBJ_ID)
    {
        //
        // Assert the DMA request line for IF2 register for the message object
        //
        CAN_transferMessage(CANA_BASE, CAN_IF2, RX_MSG_OBJ_ID, false, true);

        //
        // Getting to this point means that the RX interrupt occurred on
        // message object 2, and the message RX is complete.  Clear the
        // message object interrupt.
        //
        CAN_clearInterruptStatus(CANA_BASE, RX_MSG_OBJ_ID);

        //
        // Increment a counter to keep track of how many messages have been
        // received. In a real application this could be used to set flags to
        // indicate when a message is received.
        //
        rxMsgCount++;
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
    CAN_clearGlobalInterruptStatus(CANA_BASE, CAN_GLOBAL_INT_CANINT0);

    //
    // Acknowledge this interrupt located in group 9
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP9);
}

//
// DMA Channel 5 ISR - The interrupt service routine called when the DMA
//                     channel completes the transfer of data into the buffer.
//
__interrupt void dmaCh5ISR(void)
{
    uint16_t i, txWordData, txIndex = 0;

    //
    // Stop the DMA channel operations and acknowledge interrupt
    //
    DMA_stopChannel(DMA_CH5_BASE);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP7);

    //
    // Check for data integrity
    //
    for(i = 0; i < 2; i++)
    {
        //
        // Combine two bytes of CAN TX data into a single word for error
        // checking since the DMA transfers data as words into the RX buffer.
        //
        txWordData = txMsgData[txIndex] + (txMsgData[txIndex + 1] << 8U);

        if(rxMsgData[i] != txWordData)
        {
            // Something went wrong. rxMsgData doesn't contain expected data.
            ESTOP0;
        }

        txIndex+=2;
    }

    done = 1;
    return;
}

//
// End of File
//
