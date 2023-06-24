//#############################################################################
//
// FILE:   fsi_ex8_ext_p2pconnection_tx.c
//
// TITLE:  FSI Transmit in Point to Point Connection
//
//! \addtogroup driver_example_list
//! <h1>FSI P2Point Connection:Tx Side</h1>
//!
//! Example sets up FSI transmitting device in a point to point connection
//! to the FSI receiving device. Example code to set up FSI receiving device is
//! implemented in a separate file.
//!
//! In a real scenario two separate devices may power up in arbitrary order and
//! there is a need to establish a clean communication link which ensures that
//! receiver side is flushed to properly interpret the start of a new valid
//! frame.
//!
//! There is no true concept of a main or a remote node in the FSI protocol,
//! but to simplify the data flow and connection we can consider transmitting
//! device as main and receiving side as remote. Transmitting side will be
//! driver of initialization sequence.
//!
//! Handshake mechanism which must take place before actual data transmission
//! can be usecase specific; points described below can be taken as an example
//! on how to implement the handshake from transmitting side -
//!
//! - Setup the receiver interrupts to detect PING type frame reception
//! - Begin the PING loop
//!       + Send the Flush sequence
//!       + Send a PING frame with the frame tag \b FSI_FRAME_TAG0
//!       + Wait for some time(determined by application)
//!       + If the FSI Rx has received a PING frame with \b FSI_FRAME_TAG1, come
//!         out of loop. Otherwise iterate the loop again
//!  - Send a PING frame with the frame tag FSI_FRAME_TAG1
//!
//! After above synchronization steps, FSI Tx can be configured as per usecase
//! i.e. nWords, lane width, enabling events etc and start the infinite
//! transfers. More details on establishing the communication link can be found
//! in device TRM.
//!
//! User can edit some of configuration parameters as per usecase, similar to
//! other examples.
//!
//! \b nWords - Number of words per transfer may be from 1 -16
//! \b nLanes - Choice to select single or double lane for frame transfers
//! \b fsiClock - FSI Clock used for transfers
//! \b txUserData - User data to be sent with Data frame
//! \b txDataFrameTag - Frame tag used for Data transfers
//! \b txPingFrameTag - Frame tag used for Ping transfers
//! \b txPingTimeRefCntr - Tx Ping timer reference counter
//! \b rxWdTimeoutRefCntr - Rx Watchdog timeout reference counter
//!
//!\b External \b Connections \n
//!   For FSI external P2P connection, external connections are required
//!   to be made between two devices. Device 1's FSI TX and RX pins need to
//!   be connected to device 2's FSI RX and TX pins respectively. See below
//!   for external connections to make and GPIOs used:
//!
//!  External connections required between independent RX and TX devices:
//!  - FSIRX_CLK to FSITX_CLK
//!  - FSIRX_RX0 to FSITX_TX0
//!  - FSIRX_RX1 to FSITX_TX1
//!
//!  ControlCard FSI Header GPIOs:
//!     - GPIO_27  ->    FSITX_CLK
//!     - GPIO_26  ->    FSITX_TX0
//!     - GPIO_25  ->    FSITX_TX1
//!     - GPIO_13  ->    FSIRX_CLK
//!     - GPIO_12  ->    FSIRX_RX0
//!     - GPIO_11  ->    FSIRX_RX1
//!  LaunchPad FSI Header GPIOs:
//!     - GPIO_7   ->    FSITX_CLK
//!     - GPIO_6   ->    FSITX_TX0
//!     - GPIO_25   ->    FSITX_TX1
//!     - GPIO_33  ->    FSIRX_CLK
//!     - GPIO_12  ->    FSIRX_RX0
//!     - GPIO_2  ->    FSIRX_RX1
//!
//! \b Watch \b Variables \n
//!  - \b dataFrameCntr  Number of Data frame transmitted
//!  - \b error          Non zero for transmit/receive data mismatch
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

#define PRESCALER_VAL    FSI_PRESCALE_50MHZ

#define FSI_DELAY_LINE_CALIBRATION_ENABLE   0

//
// Globals, User can modify these parameters as per usecase
//
// Number of words per transfer may be from 1-16
uint16_t nWords = 6;

// Transfer can be happen over single or double lane
FSI_DataWidth nLanes = FSI_DATA_WIDTH_1_LANE;

// FSI Clock used for transfer
uint32_t fsiClock = 50000000;

// Frame tag used with Data/Ping transfers
FSI_FrameTag txDataFrameTag = FSI_FRAME_TAG10, txPingFrameTag = FSI_FRAME_TAG15;

// User data to be sent with Data frame
uint16_t txUserData = 0x47;

// Tx Ping timer and Rx Watchdog reference counter values
uint32_t txPingTimeRefCntr = 0x10000, rxWdTimeoutRefCntr = 0x14000;

// Boolean flag to enable/disable Rx Frame Watchdog
bool isRxFrameWdEnable = true;

//
// This value can be anything suitable to generate a single interrupt event,
// lower values may lead WD to trigger another event even before handler of 1st
// one is not completed
//
uint32_t rxFrameWdRefCntr = 0x1000000;

//
// Globals, these are not config parameters, user are not required to edit them
//
uint16_t txEventSts = 0, rxEventSts = 0;
uint16_t *txBufAddr = 0, *rxBufAddr = 0;

uint16_t txBufData[16] = {0};
volatile uint32_t fsiTxInt1Received = 0,fsiTxInt2Received = 0;
volatile uint32_t fsiRxInt1Received = 0,fsiRxInt2Received = 0;
uint32_t txTimeOutCntr = 0x100000, rxTimeOutCntr = 0x100000;
uint32_t dataFrameCntr = 0;

uint32_t error = 0;

//
// Function Prototypes
//
static inline void compare16(uint16_t val1, uint16_t val2);
void compareBufData(uint16_t txBufIndex, uint16_t rxBufIndex, uint16_t nWords);
void disableAllFSIInterrupts(void);
void checkReceivedFrameTypeTag(FSI_FrameType type, FSI_FrameTag tag);
void initFSI(void);
void prepareTxBufData(void);
__interrupt void fsiTxInt1ISR(void);
__interrupt void fsiTxInt2ISR(void);
__interrupt void fsiRxInt1ISR(void);
__interrupt void fsiRxInt2ISR(void);

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
    // Disable pin locks and enable internal pullups.
    //
    Device_initGPIO();

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
    // Interrupts that are used in this example are re-mapped to ISR functions
    // found within this file. Total 4; FSI Tx/Rx :: INT1/INT2
    //
    Interrupt_register(INT_FSITXA_INT1, &fsiTxInt1ISR);
    Interrupt_register(INT_FSITXA_INT2, &fsiTxInt2ISR);
    Interrupt_register(INT_FSIRXA_INT1, &fsiRxInt1ISR);
    Interrupt_register(INT_FSIRXA_INT2, &fsiRxInt2ISR);

    //
    // Initialize basic settings for FSI
    //
    initFSI();

    //
    // Enable FSI Tx/Rx interrupts
    //
    Interrupt_enable(INT_FSITXA_INT1);
    Interrupt_enable(INT_FSITXA_INT2);
    Interrupt_enable(INT_FSIRXA_INT1);
    Interrupt_enable(INT_FSIRXA_INT2);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Enable normal data transfer events to be sent over INT1 line
    //
    FSI_enableTxInterrupt(FSITXA_BASE, FSI_INT1, FSI_TX_EVT_FRAME_DONE);
    FSI_enableRxInterrupt(FSIRXA_BASE, FSI_INT1, FSI_RX_EVT_PING_FRAME);

    //
    // Wait till interrupt is received on FSIRX INT1 line, verify it's for FRAME
    // DONE event for PING Frame reception
    //
    while(1)
    {
        //
        // Send the flush sequence
        //
        FSI_executeTxFlushSequence(FSITXA_BASE, PRESCALER_VAL);

        //
        // Send a ping frame with frame tag 0000b
        //
        FSI_setTxFrameTag(FSITXA_BASE, FSI_FRAME_TAG0);
        FSI_setTxFrameType(FSITXA_BASE, FSI_FRAME_TYPE_PING);
        FSI_startTxTransmit(FSITXA_BASE);

        while(fsiRxInt1Received != 1U && rxTimeOutCntr != 0U)
        {
            DEVICE_DELAY_US(1);
            rxTimeOutCntr--;
        }

        if(rxTimeOutCntr == 0)
        {
            rxTimeOutCntr = 0x100000;
            continue;
        }
        else
        {
            compare16(rxEventSts, (FSI_RX_EVT_PING_FRAME | FSI_RX_EVT_FRAME_DONE));
            checkReceivedFrameTypeTag(FSI_FRAME_TYPE_PING, FSI_FRAME_TAG1);
            //
            // If received frame type and tag matches, exit this loop and proceed
            // to next step by sending flush sequence, otherwise clear error and
            // interrupt flag and continue looping.
            //
            if(error == 0)
            {
                fsiRxInt1Received = 0;
                break;
            }

            fsiRxInt1Received = 0;
            error = 0;
        }
    }

    //
    // Send a ping frame with frame tag 0001b
    //
    FSI_setTxFrameTag(FSITXA_BASE, FSI_FRAME_TAG1);
    FSI_setTxFrameType(FSITXA_BASE, FSI_FRAME_TYPE_PING);
    FSI_startTxTransmit(FSITXA_BASE);
    DEVICE_DELAY_US(100);

#if FSI_DELAY_LINE_CALIBRATION_ENABLE

    // TODO - Implement FSI RX delay line calibration here
    //          to compensate for channel-to-channel skew.
    //          See Application Report SPRACJ9 and respective
    //          software examples within C2000ware.

#endif

    FSI_setTxSoftwareFrameSize(FSITXA_BASE, nWords);
    FSI_setTxDataWidth(FSITXA_BASE, nLanes);
    FSI_setTxUserDefinedData(FSITXA_BASE, txUserData);
    FSI_setTxFrameTag(FSITXA_BASE, txDataFrameTag);
    FSI_setTxFrameType(FSITXA_BASE, FSI_FRAME_TYPE_NWORD_DATA);

    //
    // Now, start transmitting data frames
    //
    while(1)
    {
        //
        // Write data into Tx buffer and set other Frame specific fields
        //
        prepareTxBufData();
        FSI_writeTxBuffer(FSITXA_BASE, txBufData, nWords, 0U);
        while(fsiTxInt1Received != 1U);

        //
        // Start Transfer
        //
        FSI_startTxTransmit(FSITXA_BASE);

        while(fsiTxInt1Received != 1);

        //
        // Re-initialize flags and buffer pointer before next transmission
        //
        fsiTxInt1Received = 0U;
        dataFrameCntr++;
        FSI_setTxBufferPtr(FSITXA_BASE, 0U);
        DEVICE_DELAY_US(10);
    }
}

//
// initFSI - Initializes FSI Tx/Rx and also sends FLUSH sequence.
//
void initFSI(void)
{
    FSI_disableRxInternalLoopback(FSIRXA_BASE);

    //
    // NOTE: External loopback, Modify GPIO settings as per setup
    //
    GPIO_setPinConfig(DEVICE_GPIO_CFG_FSI_TXCLK);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_FSI_TX0);

    GPIO_setPinConfig(DEVICE_GPIO_CFG_FSI_RXCLK);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_FSI_RX0);
    if(nLanes == FSI_DATA_WIDTH_2_LANE)
    {
		GPIO_setPinConfig(DEVICE_GPIO_CFG_FSI_TX1);
        GPIO_setPinConfig(DEVICE_GPIO_CFG_FSI_RX1);
    }

    //
    // Set RX GPIO to be asynchronous
    // (pass through without delay)
    // Default setting is to have 2 SYS_CLK cycles delay
    //
    if(nLanes == FSI_DATA_WIDTH_2_LANE)
    {
        GPIO_setQualificationMode(DEVICE_GPIO_PIN_FSI_RX1, GPIO_QUAL_ASYNC);
    }
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_FSI_RX0, GPIO_QUAL_ASYNC);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_FSI_RXCLK, GPIO_QUAL_ASYNC);

    //
    // Perform FSI Tx and Rx initialization
    //
    FSI_performTxInitialization(FSITXA_BASE, PRESCALER_VAL);
    FSI_performRxInitialization(FSIRXA_BASE);
    txBufAddr = (uint16_t *)FSI_getTxBufferAddress(FSITXA_BASE);
    rxBufAddr = (uint16_t *)FSI_getRxBufferAddress(FSIRXA_BASE);
}

//
// prepareTxBufData - Update array which is used as source to Tx data buffer
//
void prepareTxBufData(void)
{
    uint16_t i;

    for(i = 0; i < nWords; i++)
    {
        txBufData[i] = txBufData[i] + 1;
    }
}

//
// fsiTxInt1ISR - FSI Tx Interrupt on INsT1 line
//
__interrupt void fsiTxInt1ISR(void)
{
    fsiTxInt1Received = 1U;

    txEventSts = FSI_getTxEventStatus(FSITXA_BASE);

    //
    // Clear the interrupt flag and issue ACK
    //
    FSI_clearTxEvents(FSITXA_BASE, FSI_TX_EVTMASK);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP7);
}

//
// fsiTxInt2ISR - FSI Tx Interrupt on INT2 line
//
__interrupt void fsiTxInt2ISR(void)
{
    fsiTxInt2Received = 1U;

    txEventSts = FSI_getTxEventStatus(FSITXA_BASE);

    //
    // Clear the interrupt flag and issue ACK
    //
    FSI_clearTxEvents(FSITXA_BASE, FSI_TX_EVTMASK);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP7);

    disableAllFSIInterrupts();

    //
    // INT2 line is set to fire for error events, stop immediately. Actual Error
    // is captured in txEventSts for debug
    //
    ESTOP0;
}

//
// fsiRxInt1ISR - FSI Rx Interrupt on INT1 line
//
__interrupt void fsiRxInt1ISR(void)
{
    rxEventSts = FSI_getRxEventStatus(FSIRXA_BASE);

    fsiRxInt1Received = 1U;

    //
    // Clear the interrupt flag and issue ACK
    //
    FSI_clearRxEvents(FSIRXA_BASE,rxEventSts);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP7);
}

//
// fsiRxInt2ISR - FSI Rx Interrupt on INT2 line
//
__interrupt void fsiRxInt2ISR(void)
{
    rxEventSts = FSI_getRxEventStatus(FSIRXA_BASE);

    fsiRxInt2Received = fsiRxInt2Received + 1U;

    //
    // Clear the interrupt flag and issue ACK
    //
    FSI_clearRxEvents(FSIRXA_BASE,rxEventSts);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP7);

    disableAllFSIInterrupts();

    //
    // INT2 line is set to fire for error events, stop immediately. Error
    // is captured in rxEventSts for debug
    //
    ESTOP0;
}

//
// disableAllFSIInterrupts - Disables all event interrupts in both FSI Tx/Rx,
//                           also clear them
//
void disableAllFSIInterrupts(void)
{
    FSI_disableTxInterrupt(FSITXA_BASE, FSI_INT1, FSI_TX_EVTMASK);
    FSI_disableTxInterrupt(FSITXA_BASE, FSI_INT2, FSI_TX_EVTMASK);
    FSI_disableRxInterrupt(FSIRXA_BASE, FSI_INT1, FSI_RX_EVTMASK);
    FSI_disableRxInterrupt(FSIRXA_BASE, FSI_INT2, FSI_RX_EVTMASK);

    FSI_clearTxEvents(FSITXA_BASE, FSI_TX_EVTMASK);
    FSI_clearRxEvents(FSIRXA_BASE, FSI_RX_EVTMASK);
}

//
// compare16 - Compares two 16 bit values and increments global error flag by 1
//             for mismatch
//
static inline void compare16(uint16_t val1, uint16_t val2)
{
    if(val1 != val2)
    {
        error++;
    }
}

//
// compareBufData - Compares if received data is same as transmitted ones
//                  It doesn't consider wrap-up cases, but, can be enhanced
//
void compareBufData(uint16_t txBufIndex, uint16_t rxBufIndex, uint16_t nWords)
{
    uint16_t i;
    uint16_t rxDataArray[16];

    FSI_readRxBuffer(FSIRXA_BASE, rxDataArray, nWords, rxBufIndex);

    for(i = 0; i < nWords; i++)
    {
        if(rxDataArray[i] != txBufAddr[txBufIndex])
        {
            error++;
            return;
        }

        txBufIndex++;
    }
}

//
// checkReceivedFrameTypeTag - Checks received frame type/tag and updates global
//                             error flag
//
void checkReceivedFrameTypeTag(FSI_FrameType type, FSI_FrameTag tag)
{
    compare16((uint16_t)FSI_getRxFrameType(FSIRXA_BASE), (uint16_t)type);

    if(type == FSI_FRAME_TYPE_PING)
    {
        compare16(FSI_getRxPingTag(FSIRXA_BASE), (uint16_t)tag);
    }
    else
    {
        compare16(FSI_getRxFrameTag(FSIRXA_BASE), (uint16_t)tag);
    }
}

//
// End of File
//
