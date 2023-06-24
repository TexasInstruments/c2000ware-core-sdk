//#############################################################################
//
// FILE:   fsi_dual_line_delay_select_tx.c
//
// TITLE:  FSI Skew Calibration in Dual Data Line Mode (TX Device)
//
//! \addtogroup driver_example_list
//! <h1>FSI Skew Calibration in Dual Data Line Mode (TX Device)</h1>
//!
//! In order to understand this example better and visualize the results
//! please refer to: [Fast Serial Interface (FSI) Skew 
//! Compensation](http://www.ti.com/lit/an/spracj9/spracj9.pdf)
//!
//! Companion: fsi_dual_line_delay_select_rx
//! This example configures the FSI module to transmit pings at dual data rate
//! (using RXD0 and RXD1). Run the C28x device with this application first then
//! run the core with the fsi_dual_line_delay_select_rx application.
//! This example must be used with fsi_dual_line_delay_select_rx
//!
//! In fsi_dual_line_delay_select_rx example, the FSI module is configured
//! to listen for a ping at dual data rate (using both RXD0 and RXD1).
//! The software tests whether the ping sent from the TX
//! device is correctly received against all combinations of delay elements activated.
//! RXD0: 0-31 delay elements activated
//! RXD1: 0-31 delay elements activated
//! RXCLK: 0-31 delay elements activated
//! The software stores the status of the ping received (fail/pass) for each of the
//! 32x32x32 combinations of the delay line elements. This result can be graphed using
//! the FSI Skew Compensation Utility.
//!
//!\b External \b Connections \n
//!   For FSI external connection, make below GPIO settings in
//!   example code.
//!
//!  ControlCard FSI Header GPIOs:
//!     - GPIO_27  ->    FSITX_CLK
//!     - GPIO_26  ->    FSITX_TX0
//!     - GPIO_25  ->    FSITX_TX1
//!     - GPIO_13  ->    FSIRX_CLK
//!     - GPIO_12  ->    FSIRX_RX0
//!     - GPIO_11  ->    FSIRX_RX1
//!
//!  LaunchPad FSI Header GPIOs:
//!     - GPIO_7   ->    FSITX_CLK
//!     - GPIO_6   ->    FSITX_TX0
//!     - GPIO_25   ->    FSITX_TX1
//!     - GPIO_33  ->    FSIRX_CLK
//!     - GPIO_12  ->    FSIRX_RX0
//!     - GPIO_2  ->    FSIRX_RX1
//!
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

#define PRESCALER_VAL       FSI_PRESCALE_50MHZ
#define COUNTER_TIMEOUT     200

#define FSI_PACKAGE_COUNT   16
#define FSI_NUM_WORDS       6

// Transfer can be happen over single or double lane
FSI_DataWidth nLanes = FSI_DATA_WIDTH_2_LANE;

// Frame tag used with Data/Ping transfers
FSI_FrameTag txDataFrameTag = FSI_FRAME_TAG10;

// User data to be sent with Data frame
uint16_t txUserData = 0x47;


uint16_t txEventSts = 0, rxEventSts = 0;
uint16_t txBufData[16] = {0};
volatile uint32_t fsiTxInt1Received = 0,fsiTxInt2Received = 0;
volatile uint32_t fsiRxInt1Received = 0,fsiRxInt2Received = 0;
uint32_t rxTimeOutCntr = COUNTER_TIMEOUT;
uint32_t error = 0;

//
// Function Prototypes
//
static inline void compare16(uint16_t val1, uint16_t val2);
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
    FSI_setRxDataWidth(FSIRXA_BASE, nLanes);
    FSI_setTxDataWidth(FSITXA_BASE, nLanes);

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
                rxTimeOutCntr = COUNTER_TIMEOUT;
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


        FSI_setTxSoftwareFrameSize(FSITXA_BASE, FSI_NUM_WORDS);
        FSI_setTxDataWidth(FSITXA_BASE, nLanes);
        FSI_setTxUserDefinedData(FSITXA_BASE, txUserData);
        FSI_setTxFrameTag(FSITXA_BASE, txDataFrameTag);
        FSI_setTxFrameType(FSITXA_BASE, FSI_FRAME_TYPE_NWORD_DATA);
        FSI_setTxBufferPtr(FSITXA_BASE, 0U);

        //
        // Now, start transmitting data frames
        //
        uint16_t packageCount = 0;
        fsiTxInt1Received = 0;
        while(packageCount < FSI_PACKAGE_COUNT)
        {
            //
            // Write data into Tx buffer and set other Frame specific fields
            //
            prepareTxBufData();
            FSI_writeTxBuffer(FSITXA_BASE, txBufData, FSI_NUM_WORDS, 0U);

            //
            // Start Transfer
            //
            FSI_startTxTransmit(FSITXA_BASE);

            while(fsiTxInt1Received != 1);

            //
            // Re-initialize flags and buffer pointer before next transmission
            //
            fsiTxInt1Received = 0U;
            FSI_setTxBufferPtr(FSITXA_BASE, 0U);
            DEVICE_DELAY_US(100);
            packageCount++;
        }

    }
}

//
// initFSI - Initializes FSI Tx/Rx with internal loopback and also sends FLUSH
//           sequence.
//
void initFSI(void)
{
    FSI_disableRxInternalLoopback(FSIRXA_BASE);

    //
    // NOTE: External loopback, Modify GPIO settings as per setup
    //
	GPIO_setPinConfig(DEVICE_GPIO_CFG_FSI_TXCLK);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_FSI_TX0);
    if(nLanes == FSI_DATA_WIDTH_2_LANE)
    {
        GPIO_setPinConfig(DEVICE_GPIO_CFG_FSI_TX1);
    }

    GPIO_setPinConfig(DEVICE_GPIO_CFG_FSI_RXCLK);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_FSI_RX0);
    if(nLanes == FSI_DATA_WIDTH_2_LANE)
    {
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
}

//
// prepareTxBufData - Update array which is used as source to Tx data buffer
//
void prepareTxBufData(void)
{
    uint16_t i;

    for(i = 0; i < FSI_NUM_WORDS; i++)
    {
        txBufData[i] = i;
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
