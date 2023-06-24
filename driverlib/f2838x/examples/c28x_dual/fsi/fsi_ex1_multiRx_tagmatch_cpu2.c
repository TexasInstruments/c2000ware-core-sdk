//#############################################################################
//
// FILE:   fsi_ex1_multiRx_tagmatch_cpu2.c
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
//!  - \b dataFrameCntrB  Number of Data frame received by FSIRxB
//!  - \b dataFrameCntrC  Number of Data frame received by FSIRxC
//!  - \b dataFrameCntrD  Number of Data frame received by FSIRxD
//!  - \b error          Non zero for transmit/receive data mismatch
//!
//
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2022 Texas Instruments Incorporated - http://www.ti.com
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
// Globals
//

// Number of words per transfer may be from 1 -16
uint16_t nWords = 6;

//
// Globals, these are not config parameters, user are not required to edit them
//
uint16_t rxBEventSts = 0, rxCEventSts = 0, rxDEventSts = 0;

// Reference user data to check with received Data frame user data
uint16_t txUserData = 0x47;

// Buffer used by Tx to send data. This is used to check whether correct
// data is received at the receiver. This buffer is placed in GSRAM1 and
// hence can be accessed by both CPU1 and CPU2.
uint16_t txBufDataRead[16] = {0};
#pragma DATA_SECTION(txBufDataRead,"SHARERAMGS1");

volatile uint32_t fsiRxBInt1Received = 0,fsiRxBInt2Received = 0;
volatile uint32_t fsiRxCInt1Received = 0,fsiRxCInt2Received = 0;
volatile uint32_t fsiRxDInt1Received = 0,fsiRxDInt2Received = 0;

uint32_t rxTimeOutCntr = 0x100000;

// Globals to capture the number of frames received by FSIRxB, FSIRxC &
// FSIRxD respectively.
uint32_t dataFrameCntrB = 0;
uint32_t dataFrameCntrC = 0;
uint32_t dataFrameCntrD = 0;

uint32_t error = 0;

//
// Function Prototypes
//
static inline void compare16(uint16_t val1, uint16_t val2);
void compareBufData(uint32_t base, uint16_t txBufIndex, uint16_t rxBufIndex,
                    uint16_t nWords);
void disableAllFSIRxInterrupts(void);
void checkReceivedFrameTypeTag(uint32_t base, FSI_FrameType type,
                               FSI_FrameTag tag);
void prepareTxBufData(void);

// ISRs
__interrupt void fsiRxBInt1ISR(void);
__interrupt void fsiRxBInt2ISR(void);

__interrupt void fsiRxCInt1ISR(void);
__interrupt void fsiRxCInt2ISR(void);

__interrupt void fsiRxDInt1ISR(void);
__interrupt void fsiRxDInt2ISR(void);

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
    // found within this file. Total 6; FSIRxB/C/D :: INT1/INT2
    //
    Interrupt_register(INT_FSIRXB1, &fsiRxBInt1ISR);
    Interrupt_register(INT_FSIRXB2, &fsiRxBInt2ISR);

    Interrupt_register(INT_FSIRXC1, &fsiRxCInt1ISR);
    Interrupt_register(INT_FSIRXC2, &fsiRxCInt2ISR);

    Interrupt_register(INT_FSIRXD1, &fsiRxDInt1ISR);
    Interrupt_register(INT_FSIRXD2, &fsiRxDInt2ISR);

    //
    // Enable FSI Tx/Rx interrupts.
    //
    Interrupt_enable(INT_FSIRXB1);
    Interrupt_enable(INT_FSIRXB2);

    Interrupt_enable(INT_FSIRXC1);
    Interrupt_enable(INT_FSIRXC2);

    Interrupt_enable(INT_FSIRXD1);
    Interrupt_enable(INT_FSIRXD2);

    IPC_sync(IPC_CPU1_L_CPU2_R, IPC_FLAG11);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM).
    //
    EINT;
    ERTM;

    //
    // Now, start transmitting data frames
    //
    while(1)
    {
        //
        // Wait till frame done event is received by both Tx/Rx modules
        //
        while((fsiRxBInt2Received != 1U) && (fsiRxCInt2Received != 1U) &&
              (fsiRxDInt2Received != 1U) && (rxTimeOutCntr != 0U))
        {
            rxTimeOutCntr--;
        }

        if(rxTimeOutCntr == 0)
        {
            //
            // Timeout for one of expected Tx/Rx evetns, so break execution here
            //
            break;
        }
        else
        {
            if(IPC_isFlagBusyRtoL(IPC_CPU1_L_CPU2_R, IPC_FLAG10) == 1)
            {
                //
                // Re-initialize flags and buffer pointer before next transmission
                //
                fsiRxBInt2Received = 0U;
                fsiRxCInt2Received = 0U;
                fsiRxDInt2Received = 0U;
                rxTimeOutCntr = 0x100000U;
                FSI_setRxBufferPtr(FSIRXB_BASE, 0U);
                FSI_setRxBufferPtr(FSIRXC_BASE, 0U);
                FSI_setRxBufferPtr(FSIRXD_BASE, 0U);

                // IPCRtoLFlagAcknowledge(IPC_FLAG10);
                IPC_ackFlagRtoL(IPC_CPU1_L_CPU2_R, IPC_FLAG10);
            }
        }
    }

    //
    // Coming out of infinite while loop means timeout occurred for one of Tx
    // or Rx transmit/receive events. Debug further to root-cause
    //
    ESTOP0;
}

//
// fsiRxBInt1ISR - FSI Rx Interrupt on INT1 line
//
__interrupt void fsiRxBInt1ISR(void)
{
    rxBEventSts = FSI_getRxEventStatus(FSIRXB_BASE);

    fsiRxBInt1Received = 1U;
    dataFrameCntrB++;

    //
    // Verify Frame attributes and data
    //
    checkReceivedFrameTypeTag(FSIRXB_BASE, FSI_FRAME_TYPE_NWORD_DATA,
                              FSI_FRAME_TAG5);
    compare16(FSI_getRxUserDefinedData(FSIRXB_BASE), txUserData);
    compareBufData(FSIRXB_BASE, 0, 0, nWords);

    //
    // Clear the interrupt flag and issue ACK
    //
    FSI_clearRxEvents(FSIRXB_BASE,rxBEventSts);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP4);

    //
    // Stop execution if errors encountered in frame verification
    //
    if(error != 0)
    {
        disableAllFSIRxInterrupts();

        //
        // INT2 line is set to fire for error events, stop immediately. Error
        // is captured in rxEventSts for debug
        //
        ESTOP0;
    }
}

//
// fsiRxBInt2ISR - FSI Rx Interrupt on INT2 line
//
__interrupt void fsiRxBInt2ISR(void)
{
    rxBEventSts = FSI_getRxEventStatus(FSIRXB_BASE);

    fsiRxBInt2Received = 1U;

    //
    // Clear the interrupt flag and issue ACK
    //
    FSI_clearRxEvents(FSIRXB_BASE,rxBEventSts);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP4);

    if(rxBEventSts & FSI_RX_EVT_DATA_FRAME == 0x0U)
    {
        disableAllFSIRxInterrupts();

        //
        // INT2 line is set to fire for error events, stop immediately. Error
        // is captured in rxEventSts for debug
        //
        ESTOP0;
    }
}

//
// fsiRxBInt1ISR - FSI Rx Interrupt on INT1 line
//
__interrupt void fsiRxCInt1ISR(void)
{
    rxCEventSts = FSI_getRxEventStatus(FSIRXC_BASE);

    fsiRxCInt1Received = 1U;
    dataFrameCntrC++;

    //
    // Verify Frame attributes and data
    //
    checkReceivedFrameTypeTag(FSIRXC_BASE, FSI_FRAME_TYPE_NWORD_DATA,
                              FSI_FRAME_TAG6);
    compare16(FSI_getRxUserDefinedData(FSIRXC_BASE), txUserData);
    compareBufData(FSIRXC_BASE, 0, 0, nWords);

    //
    // Clear the interrupt flag and issue ACK
    //
    FSI_clearRxEvents(FSIRXC_BASE,rxCEventSts);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP7);

    //
    // Stop execution if errors encountered in frame verification
    //
    if(error != 0)
    {
        disableAllFSIRxInterrupts();

        //
        // INT2 line is set to fire for error events, stop immediately. Error
        // is captured in rxEventSts for debug
        //
        ESTOP0;
    }
}

//
// fsiRxBInt2ISR - FSI Rx Interrupt on INT2 line
//
__interrupt void fsiRxCInt2ISR(void)
{
    rxCEventSts = FSI_getRxEventStatus(FSIRXC_BASE);

    fsiRxCInt2Received = 1U;

    //
    // Clear the interrupt flag and issue ACK
    //
    FSI_clearRxEvents(FSIRXC_BASE,rxCEventSts);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP7);

    if(rxCEventSts & FSI_RX_EVT_DATA_FRAME == 0x0U)
    {
        disableAllFSIRxInterrupts();

        //
        // INT2 line is set to fire for error events, stop immediately. Error
        // is captured in rxEventSts for debug
        //
        ESTOP0;
    }
}

//
// fsiRxBInt1ISR - FSI Rx Interrupt on INT1 line
//
__interrupt void fsiRxDInt1ISR(void)
{
    rxDEventSts = FSI_getRxEventStatus(FSIRXD_BASE);

    fsiRxDInt1Received = 1U;
    dataFrameCntrD++;

    //
    // Verify Frame attributes and data
    //
    checkReceivedFrameTypeTag(FSIRXD_BASE, FSI_FRAME_TYPE_NWORD_DATA,
                              FSI_FRAME_TAG7);
    compare16(FSI_getRxUserDefinedData(FSIRXD_BASE), txUserData);
    compareBufData(FSIRXD_BASE, 0, 0, nWords);

    //
    // Clear the interrupt flag and issue ACK
    //
    FSI_clearRxEvents(FSIRXD_BASE,rxDEventSts);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP7);

    //
    // Stop execution if errors encountered in frame verification
    //
    if(error != 0)
    {
        disableAllFSIRxInterrupts();

        //
        // INT2 line is set to fire for error events, stop immediately. Error
        // is captured in rxEventSts for debug
        //
        ESTOP0;
    }
}

//
// fsiRxBInt2ISR - FSI Rx Interrupt on INT2 line
//
__interrupt void fsiRxDInt2ISR(void)
{
    rxDEventSts = FSI_getRxEventStatus(FSIRXD_BASE);

    fsiRxDInt2Received = 1U;

    //
    // Clear the interrupt flag and issue ACK
    //
    FSI_clearRxEvents(FSIRXD_BASE,rxDEventSts);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP7);

    if(rxDEventSts & FSI_RX_EVT_DATA_FRAME == 0x0U)
    {
        disableAllFSIRxInterrupts();

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
void disableAllFSIRxInterrupts(void)
{
    FSI_disableRxInterrupt(FSIRXB_BASE, FSI_INT1, FSI_RX_EVTMASK);
    FSI_disableRxInterrupt(FSIRXB_BASE, FSI_INT2, FSI_RX_EVTMASK);

    FSI_disableRxInterrupt(FSIRXC_BASE, FSI_INT1, FSI_RX_EVTMASK);
    FSI_disableRxInterrupt(FSIRXC_BASE, FSI_INT2, FSI_RX_EVTMASK);

    FSI_disableRxInterrupt(FSIRXD_BASE, FSI_INT1, FSI_RX_EVTMASK);
    FSI_disableRxInterrupt(FSIRXD_BASE, FSI_INT2, FSI_RX_EVTMASK);


    FSI_clearRxEvents(FSIRXB_BASE, FSI_RX_EVTMASK);
    FSI_clearRxEvents(FSIRXC_BASE, FSI_RX_EVTMASK);
    FSI_clearRxEvents(FSIRXD_BASE, FSI_RX_EVTMASK);
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
        if(rxDataArray[i] != txBufDataRead[txBufIndex])
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
