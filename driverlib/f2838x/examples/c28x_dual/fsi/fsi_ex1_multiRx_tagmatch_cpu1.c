//#############################################################################
//
// FILE:   fsi_ex1_multiRx_tagmatch_cpu1.c
//
// TITLE:  CPU controlled data frame transfers to multiple receivers with
// tag-match feature enabled in internal loopback mode.
//
//! \addtogroup driver_dual_example_list
//! <h1>FSI Multi-Rx Tag-Match</h1>
//!
//! Example sets up infinite data frame transfers where trigger happens
//! through \b CPU. Multiple receivers receive data as per the received
//! frame tag.
//!
//! This is a dual core example where FSITxA & FSIRxA instances are owned
//! by CPU1 while FSIRxB, FSIRxC & FSIRxD are owned by CPU2. Internal
//! loopback mode is enabled for FSIRxA, FSIRxB, FSIRxC & FSIRxD which
//! connects data & clock lines of these receivers to FSITxA internally.
//!
//! FSITxA infinitely sends data frames with alternating tag values.
//! Receivers are configured to receive data frame with different tag
//! values with tag-match feature enabled. Tx doesn't send next frame of data
//! until it all receivers receive the data. Synchronization among all the
//! receivers is maintained through IPC flags.
//!
//!
//! User can edit some of configuration parameters as per usecase. These are
//! as below. Default values can be referred in code where these globals
//! are defined:-
//! - \b nWords - Number of words per transfer may be from 1 -16
//! - \b nLanes - Choice to select single or double lane for frame transfers
//! - \b fsiClock - FSI Clock used for transfers
//! - \b txUserData - User data to be sent with Data frame
//! - \b txDataFrameTag - Frame tag used for Data transfers
//!
//! For any errors during transfers i.e. \b error events such as Frame Overrun,
//! Underrun, Watchdog timeout and CRC/EOF/TYPE errors, execution will stop
//! immediately and status variables can be looked into for more details.
//! Execution will also stop for any mismatch between received data and sent
//! ones and also if transfers takes unusually long time(detected through
//! software counters - txTimeOutCntr and rxTimeOutCntr)
//!
//!\b External \b Connections \n
//!   For FSI internal loopback, no external connections needed
//!
//! \b Watch \b Variables \n
//!  - \b dataFrameCntrA  Number of Data frame transfered
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

#define PRESCALER_VAL    2U
//
// Globals, User can modify these parameters as per usecase
//
// Number of words per transfer may be from 1 -16
uint16_t nWords = 6;

// Transfer can be happen over single or double lane
FSI_DataWidth nLanes = FSI_DATA_WIDTH_1_LANE;

// FSI Clock used for transfer
uint32_t fsiClock = 50000000;

// User data to be sent with Data frame
uint16_t txUserData = 0x47;

// Global variable to hold tag value to be sent with Data frame.
FSI_FrameTag txDataFrameTag;

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
// Globals to capture Tx/Rx Event status.
uint16_t txEventSts = 0, rxEventSts = 0;

// Global to capture Tx buffer adress.
uint16_t *txBufAddr = 0;

// Tx Data Buffer
uint16_t txBufData[16] = {0};
#pragma DATA_SECTION(txBufData,"SHARERAMGS1");

volatile uint32_t fsiTxAInt1Received = 0,fsiTxAInt2Received = 0;
volatile uint32_t fsiRxAInt1Received = 0,fsiRxAInt2Received = 0;

// Timeout counters for Tx/Rx interrupts & ipc flag
uint32_t txTimeOutCntr = 0x100000, rxTimeOutCntr = 0x100000,
         ipcFlagTimeOutCntr = 0x100000;

// data frame & error counter
uint32_t dataFrameCntrA = 0, error = 0;
uint32_t tagIndex = 0;

//
// Function Prototypes
//
void initFSI(void);
void disableAllFSIInterrupts(void);
void prepareTxBufData(void);
static inline void compare16(uint16_t val1, uint16_t val2);
void compareBufData(uint32_t base, uint16_t txBufIndex, uint16_t rxBufIndex,
                    uint16_t nWords);
void checkReceivedFrameTypeTag(uint32_t base, FSI_FrameType type,
                               FSI_FrameTag tag);

// ISRs
__interrupt void fsiTxAInt1ISR(void);
__interrupt void fsiTxAInt2ISR(void);
__interrupt void fsiRxAInt1ISR(void);
__interrupt void fsiRxAInt2ISR(void);

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
    // Boot CPU2 core
    //
#ifdef _FLASH
    Device_bootCPU2(BOOTMODE_BOOT_TO_FLASH_SECTOR0);
#else
    Device_bootCPU2(BOOTMODE_BOOT_TO_M0RAM);
#endif

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
    // found within this file. Total 4; FSITxA/RxA :: INT1/INT2
    //
    Interrupt_register(INT_FSITXA1, &fsiTxAInt1ISR);
    Interrupt_register(INT_FSITXA2, &fsiTxAInt2ISR);
    Interrupt_register(INT_FSIRXA1, &fsiRxAInt1ISR);
    Interrupt_register(INT_FSIRXA2, &fsiRxAInt2ISR);

    //
    // Initialize basic settings for FSI.
    //
    initFSI();

    //
    // Enable FSI Tx/Rx interrupts.
    //
    Interrupt_enable(INT_FSITXA1);
    Interrupt_enable(INT_FSITXA2);

    Interrupt_enable(INT_FSIRXA1);
    Interrupt_enable(INT_FSIRXA2);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM).
    //
    EINT;
    ERTM;


    //
    // Configure for data transfers.
    //

    //
    // Setting for requested nWords and nLanes with transfers
    //
    FSI_setTxSoftwareFrameSize(FSITXA_BASE, nWords);

    FSI_setRxSoftwareFrameSize(FSIRXA_BASE, nWords);
    FSI_setRxSoftwareFrameSize(FSIRXB_BASE, nWords);
    FSI_setRxSoftwareFrameSize(FSIRXC_BASE, nWords);
    FSI_setRxSoftwareFrameSize(FSIRXD_BASE, nWords);

    FSI_setTxDataWidth(FSITXA_BASE, nLanes);

    FSI_setRxDataWidth(FSIRXA_BASE, nLanes);
    FSI_setRxDataWidth(FSIRXB_BASE, nLanes);
    FSI_setRxDataWidth(FSIRXC_BASE, nLanes);
    FSI_setRxDataWidth(FSIRXD_BASE, nLanes);

    //
    // Enable normal data transfer events to be sent over INT1 line for FSITxA
    //
    FSI_enableTxInterrupt(FSITXA_BASE, FSI_INT1, FSI_TX_EVT_FRAME_DONE);

    //
    // Enable normal data frame tag match events to be sent over INT1 line
    // for FSIRxA, FSIRxB, FSIRxC & FSIRxD.
    //
    FSI_enableRxInterrupt(FSIRXA_BASE, FSI_INT1,
                          FSI_RX_EVT_DATA_FRAME_TAG_MATCH);
    FSI_enableRxInterrupt(FSIRXB_BASE, FSI_INT1,
                          FSI_RX_EVT_DATA_FRAME_TAG_MATCH);
    FSI_enableRxInterrupt(FSIRXC_BASE, FSI_INT1,
                          FSI_RX_EVT_DATA_FRAME_TAG_MATCH);
    FSI_enableRxInterrupt(FSIRXD_BASE, FSI_INT1,
                          FSI_RX_EVT_DATA_FRAME_TAG_MATCH);

    //
    // Enable transmit/receive error events to be sent over INT2 line
    // Overrun and Underrun conditions in Rx are not enabled as buffer pointers
    // are always overwritten to first location for sending data frames.
    //
    FSI_enableRxInterrupt(FSIRXA_BASE, FSI_INT2, FSI_RX_EVT_CRC_ERR  |
                                                 FSI_RX_EVT_EOF_ERR  |
                                                 FSI_RX_EVT_TYPE_ERR |
                                                 FSI_RX_EVT_DATA_FRAME);

    FSI_enableRxInterrupt(FSIRXB_BASE, FSI_INT2, FSI_RX_EVT_CRC_ERR  |
                                                 FSI_RX_EVT_EOF_ERR  |
                                                 FSI_RX_EVT_TYPE_ERR |
                                                 FSI_RX_EVT_DATA_FRAME);

    FSI_enableRxInterrupt(FSIRXC_BASE, FSI_INT2, FSI_RX_EVT_CRC_ERR  |
                                                 FSI_RX_EVT_EOF_ERR  |
                                                 FSI_RX_EVT_TYPE_ERR |
                                                 FSI_RX_EVT_DATA_FRAME);

    FSI_enableRxInterrupt(FSIRXD_BASE, FSI_INT2, FSI_RX_EVT_CRC_ERR  |
                                                 FSI_RX_EVT_EOF_ERR  |
                                                 FSI_RX_EVT_TYPE_ERR |
                                                 FSI_RX_EVT_DATA_FRAME);

    FSI_setTxUserDefinedData(FSITXA_BASE, txUserData);
    FSI_setTxFrameType(FSITXA_BASE, FSI_FRAME_TYPE_NWORD_DATA);

    if(isRxFrameWdEnable)
    {
        //
        // Performing a reset on frame WD before its usage is recommended
        //

        // For FSIRxA
        FSI_resetRxModule(FSIRXA_BASE, FSI_RX_FRAME_WD_CNT_RESET);
        DEVICE_DELAY_US(1);
        FSI_clearRxModuleReset(FSIRXA_BASE, FSI_RX_FRAME_WD_CNT_RESET);

        FSI_enableRxInterrupt(FSIRXA_BASE, FSI_INT2,
                              FSI_RX_EVT_FRAME_WD_TIMEOUT);
        FSI_enableRxFrameWatchdog(FSIRXA_BASE, rxFrameWdRefCntr);

        // For FSIRxB
        FSI_resetRxModule(FSIRXB_BASE, FSI_RX_FRAME_WD_CNT_RESET);
        DEVICE_DELAY_US(1);
        FSI_clearRxModuleReset(FSIRXB_BASE, FSI_RX_FRAME_WD_CNT_RESET);

        FSI_enableRxInterrupt(FSIRXB_BASE, FSI_INT2,
                              FSI_RX_EVT_FRAME_WD_TIMEOUT);
        FSI_enableRxFrameWatchdog(FSIRXB_BASE, rxFrameWdRefCntr);

        // For FSIRxC
        FSI_resetRxModule(FSIRXC_BASE, FSI_RX_FRAME_WD_CNT_RESET);
        DEVICE_DELAY_US(1);
        FSI_clearRxModuleReset(FSIRXC_BASE, FSI_RX_FRAME_WD_CNT_RESET);

        FSI_enableRxInterrupt(FSIRXC_BASE, FSI_INT2,
                              FSI_RX_EVT_FRAME_WD_TIMEOUT);
        FSI_enableRxFrameWatchdog(FSIRXC_BASE, rxFrameWdRefCntr);

        // For FSIRxD
        FSI_resetRxModule(FSIRXD_BASE, FSI_RX_FRAME_WD_CNT_RESET);
        DEVICE_DELAY_US(1);
        FSI_clearRxModuleReset(FSIRXD_BASE, FSI_RX_FRAME_WD_CNT_RESET);

        FSI_enableRxInterrupt(FSIRXD_BASE, FSI_INT2,
                              FSI_RX_EVT_FRAME_WD_TIMEOUT);
        FSI_enableRxFrameWatchdog(FSIRXD_BASE, rxFrameWdRefCntr);
    }

    //
    // Configure Tag Match feature for Receivers
    //
    FSI_setRxFrameTagRef(FSIRXA_BASE, FSI_FRAME_TAG4);
    FSI_setRxFrameTagMask(FSIRXA_BASE, 0x0U);
    FSI_enableRxFrameTagCompare(FSIRXA_BASE);

    FSI_setRxFrameTagRef(FSIRXB_BASE, FSI_FRAME_TAG5);
    FSI_setRxFrameTagMask(FSIRXB_BASE, 0x0U);
    FSI_enableRxFrameTagCompare(FSIRXB_BASE);

    FSI_setRxFrameTagRef(FSIRXC_BASE, FSI_FRAME_TAG6);
    FSI_setRxFrameTagMask(FSIRXB_BASE, 0x0U);
    FSI_enableRxFrameTagCompare(FSIRXC_BASE);

    FSI_setRxFrameTagRef(FSIRXD_BASE, FSI_FRAME_TAG7);
    FSI_setRxFrameTagMask(FSIRXB_BASE, 0x0U);
    FSI_enableRxFrameTagCompare(FSIRXD_BASE);

    //
    // Assign ownership of FSIRxB, FSIRxC, FSIRxD modules to CPU2.
    // FSIRxB - instance 18; FSIRxC - instance 19; FSIRxD - instance 20
    //
    SysCtl_selectCPUForPeripheral(SYSCTL_CPUSEL16_FSI, 18, SYSCTL_CPUSEL_CPU2);
    SysCtl_selectCPUForPeripheral(SYSCTL_CPUSEL16_FSI, 19, SYSCTL_CPUSEL_CPU2);
    SysCtl_selectCPUForPeripheral(SYSCTL_CPUSEL16_FSI, 20, SYSCTL_CPUSEL_CPU2);

    IPC_sync(IPC_CPU1_L_CPU2_R, IPC_FLAG11);

    prepareTxBufData();
    tagIndex = 0;
    txDataFrameTag = FSI_FRAME_TAG4;
    FSI_setTxFrameTag(FSITXA_BASE, txDataFrameTag);
    tagIndex++;

    FSI_writeTxBuffer(FSITXA_BASE, txBufData, nWords, 0U);
    IPC_setFlagLtoR(IPC_CPU1_L_CPU2_R, IPC_FLAG10);

    //
    // Start Transfer
    //
    FSI_startTxTransmit(FSITXA_BASE);

    //
    // Now, start transmitting data frames
    //
    while(1)
    {
        //
        // Wait till frame done event is received by both Tx/Rx modules
        //
        while((fsiTxAInt1Received != 1U) && (txTimeOutCntr != 0U))
        {
            txTimeOutCntr--;
        }

        while((fsiRxAInt2Received != 1U) && (rxTimeOutCntr != 0U))
        {
            rxTimeOutCntr--;
        }

        while(IPC_isFlagBusyLtoR(IPC_CPU1_L_CPU2_R, IPC_FLAG10) != 0)
        {
            ipcFlagTimeOutCntr--;
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
            fsiTxAInt1Received = 0U;
            // fsiRxAInt1Received = 0U;
            fsiRxAInt2Received = 0U;
            txTimeOutCntr = 0x100000U;
            rxTimeOutCntr = 0x100000U;
            ipcFlagTimeOutCntr = 0x100000U;
            FSI_setTxBufferPtr(FSITXA_BASE, 0U);
            FSI_setRxBufferPtr(FSIRXA_BASE, 0U);
     }

        //
        // Write data into Tx buffer and set other Frame specific fields
        //
        prepareTxBufData();
        if(tagIndex % 4 == 0)
        {
            txDataFrameTag = FSI_FRAME_TAG4;
        }
        else if(tagIndex % 4 == 1 )
        {
            txDataFrameTag = FSI_FRAME_TAG5;
        }
        else if(tagIndex % 4 == 2 )
        {
            txDataFrameTag = FSI_FRAME_TAG6;
        }
        else
        {
            txDataFrameTag = FSI_FRAME_TAG7;
        }

        FSI_setTxFrameTag(FSITXA_BASE, txDataFrameTag);
        tagIndex++;
        FSI_writeTxBuffer(FSITXA_BASE, txBufData, nWords, 0U);
        IPC_setFlagLtoR(IPC_CPU1_L_CPU2_R, IPC_FLAG10);

        //
        // Start Transfer
        //
        FSI_startTxTransmit(FSITXA_BASE);

    }

    //
    // Coming out of infinite while loop means timeout occurred for one of Tx
    // or Rx transmit/receive events. Debug further to root-cause
    //
    ESTOP0;
}

void initFSI(void)
{
    //
    // Initialize Tx/Rx, reset sequence, clear events.
    //

    // TODO- Add logic to calculate PRESCALER_VAL based on user input FSI CLK.
    FSI_performTxInitialization(FSITXA_BASE, PRESCALER_VAL);
    FSI_performRxInitialization(FSIRXA_BASE);
    FSI_performRxInitialization(FSIRXB_BASE);
    FSI_performRxInitialization(FSIRXC_BASE);
    FSI_performRxInitialization(FSIRXD_BASE);

    //
    // Set internalLoopback mode for FSIRxA
    //
    FSI_enableRxInternalLoopback(FSIRXA_BASE);

    //
    // Enable Internal loopback for FSIRxB, FSIRxC, FSIRxD.
    //
    FSI_enableRxInternalLoopback(FSIRXB_BASE);
    FSI_enableRxInternalLoopback(FSIRXC_BASE);
    FSI_enableRxInternalLoopback(FSIRXD_BASE);

    //
    // Flush Sequence before and after releasing Rx core reset, ensures
    // flushing of Rx data/clock lines and prepares it for reception.
    //
    FSI_resetRxModule(FSIRXA_BASE, FSI_RX_MASTER_CORE_RESET);
    FSI_resetRxModule(FSIRXB_BASE, FSI_RX_MASTER_CORE_RESET);
    FSI_resetRxModule(FSIRXC_BASE, FSI_RX_MASTER_CORE_RESET);
    FSI_resetRxModule(FSIRXD_BASE, FSI_RX_MASTER_CORE_RESET);
    FSI_executeTxFlushSequence(FSITXA_BASE, PRESCALER_VAL);
    DEVICE_DELAY_US(1);
    FSI_clearRxModuleReset(FSIRXA_BASE, FSI_RX_MASTER_CORE_RESET);
    FSI_clearRxModuleReset(FSIRXB_BASE, FSI_RX_MASTER_CORE_RESET);
    FSI_clearRxModuleReset(FSIRXC_BASE, FSI_RX_MASTER_CORE_RESET);
    FSI_clearRxModuleReset(FSIRXD_BASE, FSI_RX_MASTER_CORE_RESET);
    FSI_executeTxFlushSequence(FSITXA_BASE, PRESCALER_VAL);

    //
    // Assigning base addresses of Tx/Rx data buffer to globals.
    //
    txBufAddr = (uint16_t *)FSI_getTxBufferAddress(FSITXA_BASE);
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
// fsiTxAInt1ISR - FSI Tx Interrupt on INsT1 line
//
__interrupt void fsiTxAInt1ISR(void)
{
    fsiTxAInt1Received = 1U;

    txEventSts = FSI_getTxEventStatus(FSITXA_BASE);

    //
    // Clear the interrupt flag and issue ACK
    //
    FSI_clearTxEvents(FSITXA_BASE, FSI_TX_EVTMASK);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP4);
}

//
// fsiTxAInt2ISR - FSI Tx Interrupt on INT2 line
//
__interrupt void fsiTxAInt2ISR(void)
{
    fsiTxAInt2Received = 1U;

    txEventSts = FSI_getTxEventStatus(FSITXA_BASE);

    //
    // Clear the interrupt flag and issue ACK
    //
    FSI_clearTxEvents(FSITXA_BASE, FSI_TX_EVTMASK);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP4);

    disableAllFSIInterrupts();

    //
    // INT2 line is set to fire for error events, stop immediately. Actual
    // Error is captured in txEventSts for debug.
    //
    ESTOP0;
}

//
// fsiRxAInt1ISR - FSI Rx Interrupt on INT1 line
//
__interrupt void fsiRxAInt1ISR(void)
{
    rxEventSts = FSI_getRxEventStatus(FSIRXA_BASE);

//    fsiRxAInt1Received = 1U;
    dataFrameCntrA++;

    //
    // Verify Frame attributes and data
    //
    checkReceivedFrameTypeTag(FSIRXA_BASE, FSI_FRAME_TYPE_NWORD_DATA,
                              FSI_FRAME_TAG4);
    compare16(FSI_getRxUserDefinedData(FSIRXA_BASE), txUserData);
    compareBufData(FSIRXA_BASE, 0, 0, nWords);

    //
    // Clear the interrupt flag and issue ACK
    //
    FSI_clearRxEvents(FSIRXA_BASE,rxEventSts);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP4);

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
// fsiRxAInt2ISR - FSI Rx Interrupt on INT2 line
//
__interrupt void fsiRxAInt2ISR(void)
{
    rxEventSts = FSI_getRxEventStatus(FSIRXA_BASE);

    fsiRxAInt2Received = 1U;

    //
    // Clear the interrupt flag and issue ACK
    //
    FSI_clearRxEvents(FSIRXA_BASE,rxEventSts);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP4);

    if(rxEventSts & FSI_RX_EVT_DATA_FRAME == 0x0U)
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
void compareBufData(uint32_t base, uint16_t txBufIndex, uint16_t rxBufIndex,
                    uint16_t nWords)
{
    uint16_t i;
    uint16_t rxDataArray[16];

    FSI_readRxBuffer(base, rxDataArray, nWords, rxBufIndex);

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
void checkReceivedFrameTypeTag(uint32_t base, FSI_FrameType type,
                               FSI_FrameTag tag)
{
    compare16((uint16_t)FSI_getRxFrameType(base), (uint16_t)type);

    if(type == FSI_FRAME_TYPE_PING)
    {
        compare16(FSI_getRxPingTag(base), (uint16_t)tag);
    }
    else
    {
        compare16(FSI_getRxFrameTag(base), (uint16_t)tag);
    }
}

//
// End of File
//
