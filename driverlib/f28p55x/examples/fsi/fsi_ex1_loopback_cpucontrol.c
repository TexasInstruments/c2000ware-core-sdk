//#############################################################################
//
// FILE:   fsi_ex1_loopback_cpucontrol.c
//
// TITLE:  CPU controlled data frame transfers with internal or external
//          loopback
//
//! \addtogroup driver_example_list
//! <h1>FSI Loopback:CPU Control</h1>
//!
//! Example sets up infinite data frame transfers where trigger happens through
//! \b CPU. Automatic(Hw triggered) Ping frame transmission is also setup along
//! with data.
//!
//! User can edit some of configuration parameters as per usecase. These are as
//! below. Default values can be referred in code where these globals are defined
//!
//! - \b nWords - Number of words per transfer may be from 1 -16
//! - \b nLanes - Choice to select single or double lane for frame transfers
//! - \b fsiClock - FSI Clock used for transfers
//! - \b txUserData - User data to be sent with Data frame
//! - \b txDataFrameTag - Frame tag used for Data transfers
//! - \b txPingFrameTag - Frame tag used for Ping transfers
//! - \b txPingTimeRefCntr - Tx Ping timer reference counter
//! - \b rxWdTimeoutRefCntr - Rx Watchdog timeout reference counter
//!
//! For any errors during transfers i.e. \b error events such as Frame Overrun,
//! Underrun, Watchdog timeout and CRC/EOF/TYPE errors, execution will stop
//! immediately and status variables can be looked into for more details.
//! Execution will also stop for any mismatch between received data and sent
//! ones and also if transfers takes unusually long time(detected through
//! software counters - txTimeOutCntr and rxTimeOutCntr)
//!
//!\b External \b Connections \n
//!   For FSI internal loopback (EXTERNAL_FSI_ENABLE == 0), no external
//!     connections needed
//!
//!   For FSI external loopback (EXTERNAL_FSI_ENABLE == 1), external
//!     connections are required. The FSI TX pins should be connected to the
//!     FSI RX pins of the same device. See below for external connections to
//!     include and GPIOs used:
//!
//!  External Connections Required between FSI TX and RX of the same device:
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
//!
//! \b Watch \b Variables \n
//!  - \b dataFrameCntr  Number of Data frame transfered
//!  - \b error          Non zero for transmit/receive data mismatch
//!
//
//#############################################################################
//
//
// 
// C2000Ware v5.05.00.00
//
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
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

#define PRESCALER_VAL    FSI_PRESCALE_75MHZ

//
// Define to enable external FSI configuration
//
// 0 = internal loopback enabled
// 1 = internal loopback disabled, FSI GPIOs configured,
//      external connections required
//
#define EXTERNAL_FSI_ENABLE     0

//
// Globals, User can modify these parameters as per usecase
//
// Number of words per transfer may be from 1 -16
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
    Interrupt_register(INT_FSITXA1, &fsiTxInt1ISR);
    Interrupt_register(INT_FSITXA2, &fsiTxInt2ISR);
    Interrupt_register(INT_FSIRXA1, &fsiRxInt1ISR);
    Interrupt_register(INT_FSIRXA2, &fsiRxInt2ISR);

    //
    // Initialize basic settings for FSI
    //
    initFSI();

    //
    // Enable FSI Tx/Rx interrupts
    //
    Interrupt_enable(INT_FSITXA1);
    Interrupt_enable(INT_FSITXA2);
    Interrupt_enable(INT_FSIRXA1);
    Interrupt_enable(INT_FSIRXA2);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // First setup Ping transfer and then Data
    //

    //
    // Performing a reset on PING WD counter before its usage is recommended
    // Done on both FSI Tx/Rx sides
    //
    FSI_resetTxModule(FSITXA_BASE, FSI_TX_PING_TIMEOUT_CNT_RESET);
    DEVICE_DELAY_US(1);
    FSI_clearTxModuleReset(FSITXA_BASE, FSI_TX_PING_TIMEOUT_CNT_RESET);

    FSI_resetRxModule(FSIRXA_BASE, FSI_RX_PING_WD_CNT_RESET);
    DEVICE_DELAY_US(1);
    FSI_clearRxModuleReset(FSIRXA_BASE, FSI_RX_PING_WD_CNT_RESET);

    //
    // Enable Rx Ping Watchdog timeout event on INT2 line
    //
    FSI_enableRxInterrupt(FSIRXA_BASE, FSI_INT2, FSI_RX_EVT_PING_WD_TIMEOUT);

    //
    // Now enable PING WD timer in both FSI Tx/Rx sides
    // Keeping reference counter for Rx little wide to ensure its not too sharp
    // to generate a WD timeout
    //
    FSI_enableTxPingTimer(FSITXA_BASE, txPingTimeRefCntr, txPingFrameTag);
    FSI_enableRxPingWatchdog(FSIRXA_BASE, rxWdTimeoutRefCntr);

    //
    // Automatic Ping transmission is setup, now configure for data transfers
    //

    //
    // Setting for requested nWords and nLanes with transfers
    //
    FSI_setTxSoftwareFrameSize(FSITXA_BASE, nWords);
    FSI_setRxSoftwareFrameSize(FSIRXA_BASE, nWords);
    FSI_setTxDataWidth(FSITXA_BASE, nLanes);
    FSI_setRxDataWidth(FSIRXA_BASE, nLanes);

    //
    // Enable normal data transfer events to be sent over INT1 line
    //
    FSI_enableTxInterrupt(FSITXA_BASE, FSI_INT1, FSI_TX_EVT_FRAME_DONE);
    FSI_enableRxInterrupt(FSIRXA_BASE, FSI_INT1, FSI_RX_EVT_DATA_FRAME );

    //
    // Enable transmit/receive error events to be sent over INT2 line
    // Overrun and Underrun conditions in Rx are not enabled as buffer pointers
    // are always overwritten to first location for sending data frames.
    //
    FSI_enableRxInterrupt(FSIRXA_BASE, FSI_INT2, FSI_RX_EVT_CRC_ERR  |
                                                 FSI_RX_EVT_EOF_ERR  |
                                                 FSI_RX_EVT_TYPE_ERR);

    FSI_setTxUserDefinedData(FSITXA_BASE, txUserData);
    FSI_setTxFrameTag(FSITXA_BASE, txDataFrameTag);
    FSI_setTxFrameType(FSITXA_BASE, FSI_FRAME_TYPE_NWORD_DATA);

    if(isRxFrameWdEnable)
    {
        //
        // Performing a reset on frame WD before its usage is recommended
        //
        FSI_resetRxModule(FSIRXA_BASE, FSI_RX_FRAME_WD_CNT_RESET);
        DEVICE_DELAY_US(1);
        FSI_clearRxModuleReset(FSIRXA_BASE, FSI_RX_FRAME_WD_CNT_RESET);

        FSI_enableRxInterrupt(FSIRXA_BASE, FSI_INT2,
                              FSI_RX_EVT_FRAME_WD_TIMEOUT);
        FSI_enableRxFrameWatchdog(FSIRXA_BASE, rxFrameWdRefCntr);
    }

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

        //
        // Start Transfer
        //
        FSI_startTxTransmit(FSITXA_BASE);

        //
        // Wait till frame done event is received by both Tx/Rx modules
        //
        while((fsiTxInt1Received != 1U) && (txTimeOutCntr != 0U))
        {
            txTimeOutCntr--;
        }

        while((fsiRxInt1Received != 1U) && (rxTimeOutCntr != 0U))
        {
            rxTimeOutCntr--;
        }

        if((txTimeOutCntr == 0) || (rxTimeOutCntr == 0))
        {
            //
            // Timeout for one of expected Tx/Rx evetns, so break execution here
            //
            break;
        }

        else
        {
            //
            // Re-initialize flags and buffer pointer before next transmission
            //
            fsiTxInt1Received = 0U;
            fsiRxInt1Received = 0U;
            txTimeOutCntr = 0x100000U;
            rxTimeOutCntr = 0x100000U;
            FSI_setTxBufferPtr(FSITXA_BASE, 0U);
            FSI_setRxBufferPtr(FSIRXA_BASE, 0U);
        }
    }

    //
    // Coming out of infinite while loop means timeout occurred for one of Tx
    // or Rx transmit/receive events. Debug further to root-cause
    //
    ESTOP0;
}

//
// initFSI - Initializes FSI Tx/Rx for loopback and also sends FLUSH
//           sequence.
//
void initFSI(void)
{
#if EXTERNAL_FSI_ENABLE == 0

    //
    // Set internalLoopback mode
    //
    FSI_enableRxInternalLoopback(FSIRXA_BASE);

#else

    //
    // Configure for External Loopback
    //
    FSI_disableRxInternalLoopback(FSIRXA_BASE);

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

#endif

    //
    // Initialize Tx/Rx, reset sequence, clear events
    //

    // TODO- Add logic to calculate PRESCALER_VAL based on user input FSI CLK
    FSI_performTxInitialization(FSITXA_BASE, PRESCALER_VAL);
    FSI_performRxInitialization(FSIRXA_BASE);

    //
    // Flush Sequence before and after releasing Rx core reset, ensures flushing
    // of Rx data/clock lines and prepares it for reception
    //
    FSI_resetRxModule(FSIRXA_BASE, FSI_RX_MAIN_CORE_RESET);
    FSI_executeTxFlushSequence(FSITXA_BASE, PRESCALER_VAL);
    DEVICE_DELAY_US(1);
    FSI_clearRxModuleReset(FSIRXA_BASE, FSI_RX_MAIN_CORE_RESET);
    FSI_executeTxFlushSequence(FSITXA_BASE, PRESCALER_VAL);

    //
    // Assigning base addresses of Tx/Rx data buffer to globals
    //
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
    dataFrameCntr++;

    //
    // Verify Frame attributes and data
    //
    checkReceivedFrameTypeTag(FSI_FRAME_TYPE_NWORD_DATA, txDataFrameTag);
    compare16(FSI_getRxUserDefinedData(FSIRXA_BASE), txUserData);
    compareBufData(0, 0, nWords);

    //
    // Clear the interrupt flag and issue ACK
    //
    FSI_clearRxEvents(FSIRXA_BASE,rxEventSts);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP7);

    //
    // Stop execution if errors encountered in frame verification
    //
    if(error != 0)
    {
        disableAllFSIInterrupts();

        //
        // INT2 line is set to fire for error events, stop immediately. Error
        // is captured in rxEventSts for debug
        //
        ESTOP0;
    }
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
