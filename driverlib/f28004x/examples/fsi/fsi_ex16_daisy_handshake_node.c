//#############################################################################
//
// FILE:   fsi_ex16_daisy_handshake_node.c
//
// TITLE:  FSI daisy chain topology, node device example
//! \addtogroup driver_example_list
//! <h1> FSI daisy chain topology, node device example </h1>
//! fsi_ex16_daisy_handshake_lead is for the lead device in the daisy-chain
//! loop, fsi_ex16_daisy_handshake_node for the other N-1 devices(N>=2).
//!
//! In the code, there are different settings provided:
//! [#define FSI_DMA_ENABLE 0] represents FSI communication using CPU control.
//! [#define FSI_DMA_ENABLE 1] represents FSI communication using DMA control,
//!     enabling FSIRX to trigger a DMA event and move the RX FSI data to the
//!     TX FSI buffer
//!
//! In a real scenario two separate devices may power up in arbitrary order and
//! there is a need to establish a clean communication link which ensures that
//! receiver side is flushed to properly interpret the start of a new valid
//! frame.
//!
//! The node devices in the daisy chain topology respond to the handshake
//! sequence and forwards the information  to the next device in the chain.
//!
//! After above synchronization steps, FSI Rx can be configured as per use case
//! i.e. nWords, lane width, enabling events, etc and start the infinite
//! transfers. More details on establishing the communication link can be found
//! in the device TRM.
//!
//! User can edit some of configuration parameters as per use case, similar to
//! other examples.
//!
//! \b nWords - Number of words per transfer may be from 1 -16
//! \b nLanes - Choice to select single or double lane for frame transfers
//! \b txUserData - User data to be sent with Data frame
//! \b txDataFrameTag - Frame tag used for Data transfers
//! \b txPingFrameTag - Frame tag used for Ping transfers
//! \b txPingTimeRefCntr - Tx Ping timer reference counter
//! \b rxWdTimeoutRefCntr - Rx Watchdog timeout reference counter
//!
//!\b External \b Connections \n
//!  For the FSI daisy-chain topology external connections are required to
//!  be made between the devices in the chain. Each devices FSI TX pins need to
//!  be connected to the FSI RX pins of the next device in the chain (or ring).
//!  See below for external connections to include and GPIOs used:
//!
//!  External Connections Required:
//!     - FSIRX_CLK  to  FSITX_CLK
//!     - FSIRX_RX0  to  FSITX_TX0
//!     - FSIRX_RX1  to  FSITX_TX1
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
//!  - \b dataFrameCntr  Number of Data frames received back
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

#define FSI_DMA_ENABLE  1

#define FSI_DELAY_LINE_CALIBRATION_ENABLE   0

#define PRESCALER_VAL    FSI_PRESCALE_50MHZ

#define DMA_TRANSFER_SIZE_IN_BURSTS 1U
#define DMA_WRAP_SIZE_IN_BURSTS     1U
#define TOTAL_WORDS_IN_TRANSFER (DMA_TRANSFER_SIZE_IN_BURSTS * nWords)

#define DATA_FRAME_TEST_IO           16
#define DATA_FRAME_TEST_IO_CONF      GPIO_16_GPIO16

#define TX_TIME_OUT_CNTR    0x1000000
#define RX_TIME_OUT_CNTR    0x1000000

// GS0 RAM to store Tx frame data which DMA will read
#define GS0_START_ADDR  0xC100
// GS1 RAM to store Tx frame tag and Userdata
#define GS1_START_ADDR  0xE000
// GS2 RAM to save received Rx frame data
#define GS2_START_ADDR  0x10000
// GS3 RAM to save received Rx frame tag and Userdata
#define GS3_START_ADDR  0x12000

//
// FSI Tx/Rx Frame tag User Data register address, used by DMA channel to
// write(and trigger transfer) read userdata respectively
//
#define FSI_TX_FRAME_TAG_UDATA_REGADDR (FSITXA_BASE + FSI_O_TX_FRAME_TAG_UDATA)
#define FSI_RX_FRAME_TAG_UDATA_REGADDR (FSIRXA_BASE + FSI_O_RX_FRAME_TAG_UDATA)

//
// Globals, User can modify these parameters as per usecase
//
// Number of words per transfer may be from 1 -16
uint16_t nWords = 8;

// Transfer can be happen over single or double lane
FSI_DataWidth nLanes = FSI_DATA_WIDTH_1_LANE;

// Frame tag used with Data/Ping transfers
FSI_FrameTag txPingFrameTag = FSI_FRAME_TAG15;

// Frame tag used with Data/Ping transfers
FSI_FrameTag txDataFrameTag = FSI_FRAME_TAG10;

// User data to be sent with Data frame(for CPU control)
uint16_t txUserData = 0x47;

// Tx Ping timer and Rx Watchdog reference counter values
uint32_t txPingTimeRefCntr = TX_TIME_OUT_CNTR, rxWdTimeoutRefCntr = 0x1400000;

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
uint16_t rxBufData[16] = {0};
volatile uint32_t fsiTxInt1Received = 0,fsiTxInt2Received = 0;
volatile uint32_t fsiRxInt1Received = 0,fsiRxInt2Received = 0;
uint32_t txTimeOutCntr = TX_TIME_OUT_CNTR, rxTimeOutCntr = RX_TIME_OUT_CNTR;
uint32_t dataFrameCntr = 0, dataFrameCntr_ui32 = 0;

uint32_t dmaIntr1 = 0, dmaIntr2 = 0;
volatile uint16_t i = 0, *txTempData16 = 0, *rxTempData16 = 0;

uint32_t error = 0;

//
// Function Prototypes
//
static inline void compare16(uint16_t val1, uint16_t val2);
void compareBufData(uint16_t txBufIndex, uint16_t rxBufIndex, uint16_t nWords);
void disableAllFSIInterrupts(void);
void checkReceivedFrameTypeTag(FSI_FrameType type, FSI_FrameTag tag);
void initFSI(void);
void testGPIO(void);
__interrupt void fsiTxInt1ISR(void);
__interrupt void fsiTxInt2ISR(void);
__interrupt void fsiRxInt1ISR(void);
__interrupt void fsiRxInt2ISR(void);
__interrupt void fsirxdma_isr(void);
void fsirx_dma_config();
void InitFrameTagAndData();
void handshake_node(void);

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
    testGPIO();

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
    // Initialize basic settings for FSI
    //
    initFSI();

    //
    // Interrupts that are used in this example are re-mapped to ISR functions
    // found within this file. Total 4; FSI Tx/Rx :: INT1/INT2
    //
    Interrupt_register(INT_FSITXA_INT1, &fsiTxInt1ISR);
    Interrupt_register(INT_FSITXA_INT2, &fsiTxInt2ISR);
    Interrupt_register(INT_FSIRXA_INT1, &fsiRxInt1ISR);
    Interrupt_register(INT_FSIRXA_INT2, &fsiRxInt2ISR);

    //
    // Enable FSI Tx/Rx interrupts
    //
    Interrupt_enable(INT_FSITXA_INT1);
    Interrupt_enable(INT_FSITXA_INT2);
    Interrupt_enable(INT_FSIRXA_INT1);
    Interrupt_enable(INT_FSIRXA_INT2);

#if FSI_DMA_ENABLE ==1

    //
    // DMA Interrupts that are used in this example are re-mapped to ISR functions
    // found within this file.
    //
    Interrupt_register(INT_DMA_CH4, &fsirxdma_isr);

    //
    // Enable DMA interrupts
    //
    Interrupt_enable(INT_DMA_CH4);

#endif

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Enable normal data transfer events to be sent over INT1 line
    //
    FSI_enableRxInterrupt(FSIRXA_BASE, FSI_INT1, FSI_RX_EVT_PING_FRAME);

    // Wait till interrupt is received on FSIRX INT1 line, verify it's for FRAME
    // DONE event for PING Frame reception
    //
    handshake_node();
	
#if FSI_DELAY_LINE_CALIBRATION_ENABLE

    // TODO - Implement FSI RX delay line calibration here
    //          to compensate for channel-to-channel skew.
    //          See Application Report SPRACJ9 and respective
    //          software examples within C2000ware.

#endif

    //
    // Setting for requested nWords and nLanes with transfers
    //
    FSI_setTxFrameType(FSITXA_BASE, FSI_FRAME_TYPE_NWORD_DATA);
    FSI_setTxSoftwareFrameSize(FSITXA_BASE, nWords);
    FSI_setTxDataWidth(FSITXA_BASE, nLanes);
    // RX setting part
    FSI_setRxSoftwareFrameSize(FSIRXA_BASE, nWords);
    FSI_setRxDataWidth(FSIRXA_BASE, nLanes);

    //
    // Enable transmit/receive error events to be sent over INT2 line
    // Overrun and Underrun conditions in Rx are not enabled as buffer pointers
    // are always overwritten to first location for sending data frames.
    //
    FSI_enableRxInterrupt(FSIRXA_BASE, FSI_INT2, FSI_RX_EVT_CRC_ERR  |
                                                 FSI_RX_EVT_EOF_ERR  |
                                                 FSI_RX_EVT_TYPE_ERR);

    FSI_disableRxInterrupt(FSIRXA_BASE, FSI_INT1, FSI_RX_EVT_PING_FRAME);
    DEVICE_DELAY_US(10);

    FSI_enableTxInterrupt(FSITXA_BASE, FSI_INT1, FSI_TX_EVT_FRAME_DONE);

    #if FSI_DMA_ENABLE==0

    FSI_enableRxInterrupt(FSIRXA_BASE, FSI_INT1, FSI_RX_EVT_DATA_FRAME);

    #else

    //
    // Initialize the dma channels for both tx and rx buffers
    //
    DMA_initController();

    InitFrameTagAndData();

    fsirx_dma_config();

    FSI_setTxStartMode(FSITXA_BASE, FSI_TX_START_FRAME_CTRL_OR_UDATA_TAG);

    // Enable DMA event on FSI Rx
    FSI_enableRxDMAEvent(FSIRXA_BASE);

    // Start RX channels
    DMA_startChannel(DMA_CH3_BASE);
    DMA_startChannel(DMA_CH4_BASE);

    #endif

    //
    // Now, start transmitting data frames
    //
    while(1)
    {

    #if FSI_DMA_ENABLE==0

         //
        // Wait for RX data frame received event
        //
        while(fsiRxInt1Received != 1U);

        while(fsiTxInt1Received != 1U);

        fsiRxInt1Received = 0U;
        fsiTxInt1Received = 0U;

    #else

        //
        // Wait for RX channels to complete a transfer
        //
        while(dmaIntr2 == 0U); // RX Int flag
        dmaIntr2 = 0;

    #endif

    }
}

void handshake_node(void)
{

    while(1)
    {
        while(fsiRxInt1Received != 1);
        compare16(rxEventSts, (FSI_RX_EVT_PING_FRAME | FSI_RX_EVT_FRAME_DONE));
        checkReceivedFrameTypeTag(FSI_FRAME_TYPE_PING, FSI_FRAME_TAG0);
        //
        // If received frame type and tag matches, exit this loop and proceed to
        // next step by sending flush sequence, otherwise clear error and
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
            rxTimeOutCntr = RX_TIME_OUT_CNTR;
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
    DEVICE_DELAY_US(10);
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

    FSI_performTxInitialization(FSITXA_BASE, PRESCALER_VAL);
    FSI_performRxInitialization(FSIRXA_BASE);
    txBufAddr = (uint16_t *)FSI_getTxBufferAddress(FSITXA_BASE);
    rxBufAddr = (uint16_t *)FSI_getRxBufferAddress(FSIRXA_BASE);
}

//
// fsiTxInt1ISR - FSI Tx Interrupt on INsT1 line
//
__interrupt void fsiTxInt1ISR(void)
{
    fsiTxInt1Received = 1U;
    txEventSts = FSI_getTxEventStatus(FSITXA_BASE);

    // Set FSI TX buffer pointer to beginning
    FSI_setTxBufferPtr(FSITXA_BASE, 0U);

    // Clear the interrupt flag and issue ACK
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
    if((rxEventSts & FSI_RX_EVT_DATA_FRAME) != 0)
   {
        dataFrameCntr++;

        if(dataFrameCntr >= 0xFFFFFFFF)
        {
            dataFrameCntr_ui32++;
            dataFrameCntr = 0;
        }

        //
        // Move received User Data, Frame Tag, and Data to TX buffer/registers
        //
        FSI_setTxUserDefinedData(FSITXA_BASE, FSI_getRxUserDefinedData(FSIRXA_BASE));
        FSI_setTxFrameTag(FSITXA_BASE, (FSI_FrameTag)FSI_getRxFrameTag(FSIRXA_BASE));

        FSI_writeTxBuffer(FSITXA_BASE, rxBufAddr, nWords, 0U); // Put read data into TX buffer
        FSI_startTxTransmit(FSITXA_BASE);
   }
    fsiRxInt1Received = 1U;

    // Set FSI RX buffer pointer to beginning
    FSI_setRxBufferPtr(FSIRXA_BASE, 0U);

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

void testGPIO(void)
{
    GPIO_setDirectionMode(DATA_FRAME_TEST_IO,GPIO_DIR_MODE_OUT);
    GPIO_setQualificationMode(DATA_FRAME_TEST_IO,GPIO_QUAL_ASYNC);
    GPIO_setPinConfig(DATA_FRAME_TEST_IO_CONF);

    GPIO_writePin(DATA_FRAME_TEST_IO,1);
}

//
// InitFrameTagAndData - Initializes GS0/GS1 memories to populate tag and data
//                       for frame transfers
//
void InitFrameTagAndData(void)
{
    unsigned int i;
    uint16_t *temp;

    temp = (uint16_t *)GS1_START_ADDR;
    for(i = FSI_FRAME_TAG0; i < FSI_FRAME_TAG15; i++)
    {
        //
        //tag and user data
        //
        *temp = ((0x0 + i) | ((unsigned long)(0x0 + i) << 8));
        temp++;
    }
}

//
// fsirx_dma_config - Sets up DMA channels(Ch3 and Ch4) for FSI Rx operation
//
void fsirx_dma_config()
{
    //
    // Move RX FSI data into TX buffer
    //
    DMA_configAddresses(DMA_CH3_BASE, txBufAddr, rxBufAddr);
    DMA_configBurst(DMA_CH3_BASE, nWords, 1, 1);
    DMA_configTransfer(DMA_CH3_BASE, DMA_TRANSFER_SIZE_IN_BURSTS, 0, 0);
    DMA_configWrap(DMA_CH3_BASE, DMA_WRAP_SIZE_IN_BURSTS, 0,
                   DMA_WRAP_SIZE_IN_BURSTS, 0);

    DMA_configMode(DMA_CH3_BASE, DMA_TRIGGER_FSIRXA, DMA_CFG_ONESHOT_DISABLE|
                   DMA_CFG_CONTINUOUS_ENABLE|DMA_CFG_SIZE_16BIT);

    DMA_disableInterrupt(DMA_CH3_BASE);
    DMA_enableTrigger(DMA_CH3_BASE);

    //
    // Move Tag and User Data into TX Registers
    //
    DMA_configAddresses(DMA_CH4_BASE,(uint16_t *)FSI_TX_FRAME_TAG_UDATA_REGADDR,
                        (uint16_t *)GS1_START_ADDR);
    DMA_configBurst(DMA_CH4_BASE, 1, 0, 0);
    DMA_configTransfer(DMA_CH4_BASE, DMA_TRANSFER_SIZE_IN_BURSTS, 0, 0);
    DMA_configWrap(DMA_CH4_BASE, DMA_WRAP_SIZE_IN_BURSTS, 0,
                   DMA_WRAP_SIZE_IN_BURSTS, 0);
    DMA_configMode(DMA_CH4_BASE, DMA_TRIGGER_FSIRXA, DMA_CFG_ONESHOT_DISABLE |
                   DMA_CFG_CONTINUOUS_ENABLE | DMA_CFG_SIZE_16BIT);

    DMA_setInterruptMode(DMA_CH4_BASE, DMA_INT_AT_END);
    DMA_enableInterrupt(DMA_CH4_BASE);

    DMA_enableTrigger(DMA_CH4_BASE);
}

//
// fsirxdma_isr - FSI RX DMA ISR
//
interrupt void fsirxdma_isr(void)
{
    // Set FSI TX/RX circular buffer pointers back to beginning
    FSI_setRxBufferPtr(FSIRXA_BASE, 0U);

    GPIO_togglePin(DATA_FRAME_TEST_IO);

    dataFrameCntr++;

    if(dataFrameCntr >= 0xFFFFFFFF)
    {
        dataFrameCntr_ui32++;
        dataFrameCntr = 0;
    }

    dmaIntr2 = 1;
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP7);
}

//
// End of File
//

