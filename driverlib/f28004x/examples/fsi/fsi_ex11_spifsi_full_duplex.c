//#############################################################################
//
// FILE:   fsi_ex11_spifsi_full_duplex.c
//
// TITLE:  FSI and SPI communication full-duplex.
//
//! \addtogroup spifsi_communication
//! <h1>FSI and SPI communication full-duplex</h1>
//!
//! FSI supports SPI compatibility mode to talk to the devices not having FSI
//! but SPI module.
//! API to decode FSI frame received at SPI end is implemented and checks are
//! made to ensure received details(frame tag/type, userdata, data) match with
//! transfered frame.
//!
//! This program is the FSI part of SPI-to-FSI communication. It enables
//! both TX and RX module in SPI-mode for full functionality of SPI-master. Then
//! it sends Ping frame with tag 0 to request a flush sequence from SPI. After
//! getting flush sequence, it sends Ping frame with tag 1, 1_WORD frame, 2_WORD
//! frame, N_WORD frame with 3 words, 4_WORD frame, N_WORD frame with 5 words,
//! 6_WORD frame, N_WORD frame with 7 words and so on in duplicate manner. To
//! enable echo-functionality with FSI and SPI RX/TX FIFO, we need to prime SPI-
//! side's TX FIFO to stage the frame by sending two identical frames in succession,
//! so FSI gets the previously staged frame when FSI transmits the same frame for
//! the second time. It is because SPI-slave is driven by SPI-master, FSI-master
//! in this case; SPI-slave will only talk back to FSI when FSI is talking to SPI.
//!
//! To enable full functional duplex of SPI-to-FSI, you must load
//! fsi_ex11_spifsi_full_duplex to f28004x device and spi_ex4_spifsi_full_duplex
//! to any device that has SPI module. You must run SPI-side before FSI-side.
//!
//! If there are any comparison failures during transfers or any of error
//! event occurs, execution will stop.
//!
//! \b External \b Connections \n
//!   Number in parenthesis indicates a pin number on docking station.
//!   GPIOs on controlCARD.
//!    f28004x_FSITX               f2837x_SPIA                f28004x_FSIRX
//!   -TXCLK, GPIO7(56)         -> SPICLK, GPIO18(71)
//!   -TXD0, GPIO6(54)          -> SPISIMO, GPIO16(67)
//!   -TXD1, GPIO5(52)          -> ~SPISTE, GPIO19(73)
//!                                -SPISOMI, GPIO17(69)    -> RXD0, GPIO12(57)
//!
//! \b Watch \b Variables \n
//!  - \b fsiRxCntr  Number of Data frames received
//!  - \b fsiTxCntr  Number of Data frames transmitted
//!  - \b error      Non zero for transmit/receive data mismatch
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
#include "device.h"
#include "driverlib.h"

//
// Defines.
//
#define PRESCALER_VAL    0x25U
#define ON               0x0000U
#define TOGGLE           0x0001U

//
// Globals, these are not config parameters, user are not required to edit them
//
uint16_t txEventSts = 0, rxEventSts = 0;
uint16_t *txBufAddr = 0, *rxBufAddr = 0;

//
// Interrupt flags.
//
volatile uint32_t fsiTxInt1Received = 0,fsiTxInt2Received = 0;
volatile uint32_t fsiRxInt1Received = 0,fsiRxInt2Received = 0;

//
// error - Number of errors.
// fsiRxCntr - Number of frames received by FSI.
// fsiTxCntr - Number of frames transmitted by FSI.
// txBufData - Buffer that holds current data words.
// txDataFrameTag - Frame tag used for Data frames.
// txPingFrameTag - Frame tag used for Ping frames.
// txErrorFrameTag - Frame tag used for Error frames.
// txUserData - User data for every frames, except Ping frames.
//
uint32_t error = 0;
uint32_t fsiRxCntr = 0;
uint32_t fsiTxCntr = 0;
uint16_t txBufData[16] = { 0 };
FSI_FrameTag txDataFrameTag = FSI_FRAME_TAG10;
FSI_FrameTag txPingFrameTag = FSI_FRAME_TAG0;
FSI_FrameTag txErrorFrameTag = FSI_FRAME_TAG15;
uint16_t txUserData = 0x47U;

//
// Function Prototypes
//
void configISR(FSI_FrameType frameType);
void requestFlushSeq(void);
void sendPingFrame(FSI_FrameTag frameTag);
void sendDataFrame(void);
void syncWithSPI(void);
void checkReceivedFrameTypeTag(FSI_FrameType type, FSI_FrameTag tag);
void initialize(void);
void configureGPIOs(void);
void toggleOrOnLED(uint16_t ledType, uint16_t toggle);
void turnOffLEDs(void);
void turnOnLEDs(void);
static inline void compare16(uint16_t val1, uint16_t val2);
void compareBufData(uint16_t txBufIndex, uint16_t rxBufIndex, uint16_t nWords);
void disableAllFSIInterrupts(void);
void prepareTxBufData(int nLength);
__interrupt void fsiTxInt1ISR(void);
__interrupt void fsiTxInt2ISR(void);
__interrupt void fsiRxInt1ISR(void);
__interrupt void fsiRxInt2ISR(void);

//*****************************************************************************
//
// Main
//
//*****************************************************************************
void main(void)
{
    // device init.
    initialize();

    //
    // Assigning base addresses of Tx/Rx data buffer to globals
    //
    txBufAddr = (uint16_t *)FSI_getTxBufferAddress(FSITXA_BASE);
    rxBufAddr = (uint16_t *)FSI_getRxBufferAddress(FSIRXA_BASE);

    //
    // Turn off both LEDs that were turned on in init phase.
    //
    turnOffLEDs();

    //
    // Send Ping frame with tag 1 twice to make SPI echo back
    // the same frame.
    //
    syncWithSPI();

    //
    // Send data frames.
    //
    sendDataFrame();

    //
    // Infinite Loop.
    //
    while(1U) 
    {
        ;
    }
}

//*****************************************************************************
//
// syncWithSPI - send Ping frame with tag of 1 twice, making SPI to echo back
//               same Ping frame with tag of 1. Update fsiTxCntr as needed.
//
//*****************************************************************************
void syncWithSPI(void)
{
    uint16_t repeat;

    //
    // Prime then Get the echoed frame.
    //
    for(repeat = 1U; repeat <= 2U; repeat++){

        //
        // Set up proper ISR according to fsiTxCntr.
        //
        configISR(FSI_FRAME_TYPE_PING);
        sendPingFrame(FSI_FRAME_TAG1);
        DEVICE_DELAY_US(50U);

        //
        // Verify frame.
        //
        if ((fsiTxCntr % 2U) == 0U)
        {
            //
            // Wait till FSI Rx completely receives a frame.
            //
            while(fsiRxInt1Received != 1U);
            fsiRxInt1Received = 0;

            checkReceivedFrameTypeTag(FSI_FRAME_TYPE_PING, FSI_FRAME_TAG1);
        }
        fsiTxCntr++;
    }
}

//*****************************************************************************
//
// configISR - enables FSI RX Interrupts when it is second time sending the
//              same frame.
//
//*****************************************************************************
void configISR(FSI_FrameType frameType)
{
    //
    // Even number = second duplicate frame.
    //
    if((fsiTxCntr % 2U) == 0U)
    {
        if(frameType == FSI_FRAME_TYPE_PING)
        {
            //
            // Only enable Ping interrupt for Ping frame.
            //
            FSI_enableRxInterrupt(FSIRXA_BASE,
                                  FSI_INT1,
                                  FSI_RX_EVT_PING_FRAME |
                                  FSI_RX_EVT_FRAME_DONE);
        }
        else
        {
            //
            // data frame.
            //
            FSI_enableRxInterrupt(FSIRXA_BASE,
                                  FSI_INT1,
                                  FSI_RX_EVT_DATA_FRAME |
                                  FSI_RX_EVT_FRAME_DONE);
        }

        //
        // Error line.
        //
        FSI_enableRxInterrupt(FSIRXA_BASE, FSI_INT2, FSI_RX_EVT_CRC_ERR |
        FSI_RX_EVT_EOF_ERR |
        FSI_RX_EVT_FRAME_OVERRUN |
        FSI_RX_EVT_TYPE_ERR);
    }
    else
    {
        //
        // Prime frame will receive garbage value. Ignore it.
        //
        FSI_disableRxInterrupt(FSIRXA_BASE, FSI_INT1, FSI_RX_EVTMASK);
        FSI_disableRxInterrupt(FSIRXA_BASE, FSI_INT2, FSI_RX_EVTMASK);
    }
}

//*****************************************************************************
//
// requestFlushSeq - request flush sequence of 0xFFFF by sending Ping frame with
//                   tag 0 to SPI.
//
//*****************************************************************************
void requestFlushSeq(void)
{
    //
    // Ping with tag 0.
    //
    FSI_setTxFrameType(FSITXA_BASE, FSI_FRAME_TYPE_PING);
    FSI_setTxFrameTag(FSITXA_BASE, FSI_FRAME_TAG0);
    FSI_startTxTransmit(FSITXA_BASE);

    toggleOrOnLED(DEVICE_GPIO_PIN_LED1, TOGGLE);
}

//*****************************************************************************
//
// sendPingFrame - wrapper function for sending Ping frame with any frameTag.
//
//*****************************************************************************
void sendPingFrame(FSI_FrameTag frameTag)
{
    //
    // Ping with frameTag.
    //
    FSI_setTxFrameType(FSITXA_BASE, FSI_FRAME_TYPE_PING);
    FSI_setTxFrameTag(FSITXA_BASE, frameTag);

    FSI_startTxTransmit(FSITXA_BASE);

    //
    // Wait for FSI Tx to finish transmit operation
    //
    while(fsiTxInt1Received != 1U);
    fsiTxInt1Received = 0U;
    compare16(txEventSts, FSI_TX_EVT_FRAME_DONE);

    toggleOrOnLED(DEVICE_GPIO_PIN_LED1, TOGGLE);
}

//*****************************************************************************
//
// sendDataFrame - as mentioned in the header, it sends Data frames, twice
// each, then verifies echoed-back frames.
//
//*****************************************************************************
void sendDataFrame(void)
{
    uint16_t nLength, repeat;
    FSI_FrameType frameType;

    //
    // 1 to 14 Data frame.
    //
    for (nLength = 1; nLength <= 14; nLength++)
    {
        switch(nLength)
        {
            //
            // If 1, 2, 4, or 6 Data frame, use pre-defined frame types.
            //
            case 1U:
                frameType = FSI_FRAME_TYPE_1WORD_DATA;
                break;
            case 2U:
                frameType = FSI_FRAME_TYPE_2WORD_DATA;
                break;
            case 4U:
                frameType = FSI_FRAME_TYPE_4WORD_DATA;
                break;
            case 6U:
                frameType = FSI_FRAME_TYPE_6WORD_DATA;
                break;
            default:
                frameType = FSI_FRAME_TYPE_NWORD_DATA;

                //
                // Let FSI know how many words are going out and coming in.
                //
                FSI_setTxSoftwareFrameSize(FSITXA_BASE, nLength);
                FSI_setRxSoftwareFrameSize(FSIRXA_BASE, nLength);
                break;
        }

        //
        // Prime then Get/Verify the echoed frame.
        //
        for (repeat = 1U; repeat <= 2U; repeat++)
        {
            //
            // Set up proper ISR according to fsiTxCntr.
            //
            configISR(frameType);

            //
            // set frameTag, userData, and frameType.
            //
            FSI_setTxFrameTag(FSITXA_BASE, (FSI_FrameTag) txDataFrameTag);
            FSI_setTxUserDefinedData(FSITXA_BASE, txUserData);
            FSI_setTxFrameType(FSITXA_BASE, (FSI_FrameType) frameType);

            //
            // Prepare data, then transmit.
            //
            if ((fsiTxCntr % 2U) == 1U)
            {
                //
                // Only prepare once because of duplicate transmit.
                //
                prepareTxBufData(nLength);
            }

            //
            // Start Transmit.
            //
            FSI_writeTxBuffer(FSITXA_BASE, txBufData, nLength, 0U);
            FSI_startTxTransmit(FSITXA_BASE);

            //
            // Wait for FSI Tx to finish transmit operation.
            // Also, check that the Transmit frame done interrupt was the source.
            //
            while(fsiTxInt1Received != 1U);
            fsiTxInt1Received = 0U;
            compare16(txEventSts, FSI_TX_EVT_FRAME_DONE);

            DEVICE_DELAY_US(50U);
            toggleOrOnLED(DEVICE_GPIO_PIN_LED1, TOGGLE);

            //
            // SPI echoes back here.
            //

            //
            // Verify received frame only if it is second duplicate frame.
            //
            if ((fsiTxCntr % 2U) == 0U)
            {
                //
                // Wait till FSI Rx completely receives a frame.
                //
                while(fsiRxInt1Received != 1U);
                fsiRxInt1Received = 0;

                //
                // Verify frameType, userData, data, CRC8, and frameTag.
                //
                compare16(FSI_getRxFrameType(FSIRXA_BASE), frameType);
                compare16(FSI_getRxUserDefinedData(FSIRXA_BASE), txUserData);
                compareBufData(0U, 0U, nLength);
                compare16(FSI_getRxReceivedCRC(FSIRXA_BASE),
                          FSI_getRxComputedCRC(FSIRXA_BASE));
                compare16(FSI_getRxFrameTag(FSIRXA_BASE), txDataFrameTag);

                //
                // Reset FSI_Tx/RxBuffer
                //
                FSI_setTxBufferPtr(FSITXA_BASE, 0U);
                FSI_setRxBufferPtr(FSIRXA_BASE, 0U);
            }
            fsiTxCntr++;

            //
            // Reset RX buffer.
            //
            FSI_setRxBufferPtr(FSIRXA_BASE, 0U);
        }
    }
}

//*****************************************************************************
//
// Initialization module.
//
//*****************************************************************************
void initialize(void)
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
    // found within this file. Total 5; FSI Tx/Rx :: INT1/INT2 + SPI Rx
    //
    Interrupt_register(INT_FSITXA_INT1, &fsiTxInt1ISR);
    Interrupt_register(INT_FSITXA_INT2, &fsiTxInt2ISR);
    Interrupt_register(INT_FSIRXA_INT1, &fsiRxInt1ISR);
    Interrupt_register(INT_FSIRXA_INT2, &fsiRxInt2ISR);

    //
    // TX initialization.
    //
    FSI_performTxInitialization(FSITXA_BASE, PRESCALER_VAL);

    //
    // Connect FSI_TXCLK to RXCLK internally.
    //
    FSI_enableRxSPIPairing(FSIRXA_BASE);

    //
    // Disable Internal Loopback in FSI Rx and keep it under master Core reset
    // till all GPIO settings are made, also clear any Rx events.
    //
    FSI_resetRxModule(FSIRXA_BASE, FSI_RX_MASTER_CORE_RESET);
    FSI_clearRxEvents(FSIRXA_BASE, FSI_RX_EVTMASK);
    FSI_disableRxInternalLoopback(FSIRXA_BASE);

    //
    // GPIO setting.
    //
    configureGPIOs();

    //
    // enable SPI mode on the FSIRX
    //
    FSI_enableTxSPIMode(FSITXA_BASE);
    FSI_enableRxSPIMode(FSIRXA_BASE);
    FSI_clearRxModuleReset(FSIRXA_BASE, FSI_RX_MASTER_CORE_RESET);
    FSI_clearTxModuleReset(FSITXA_BASE, FSI_TX_MASTER_CORE_RESET);


    DEVICE_DELAY_US(50);

    //
    // Request flush sequence by sending PING frame with tag 0.
    //
    requestFlushSeq();
    fsiTxCntr++;
    DEVICE_DELAY_US(50);

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
    // Configure for data transfers.
    // Enable normal data transfer events to be sent over INT1 line
    //
    FSI_enableTxInterrupt(FSITXA_BASE, FSI_INT1, FSI_TX_EVT_FRAME_DONE);

    //
    // Turn on LEDs.
    //
    turnOnLEDs();
}

//*****************************************************************************
//
// GPIO configuration.
//
//*****************************************************************************
void configureGPIOs(void)
{
    //
    // Configure GPIOs for FSI TX and RX.
    //
    GPIO_setPinConfig(GPIO_7_FSITXA_CLK);
    GPIO_setPinConfig(GPIO_6_FSITXA_D0);
    GPIO_setPinConfig(GPIO_5_FSITXA_D1);
    GPIO_setPinConfig(GPIO_12_FSIRXA_D0);

    //
    // Set GPIO12 to be asynchronous(pass through without delay)
    // Default setting is to have 2 SYS_CLK cycles delay
    //
    GPIO_setQualificationMode(12, GPIO_QUAL_ASYNC);

    //
    // LED GPIO.
    //
    GPIO_setPadConfig(DEVICE_GPIO_PIN_LED1, GPIO_PIN_TYPE_STD);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_LED1, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_LED2, GPIO_PIN_TYPE_STD);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_LED2, GPIO_DIR_MODE_OUT);
}

//*****************************************************************************
//
// toggleOrOnLED - toggles or turns on one of two LEDs.
//
//*****************************************************************************
void toggleOrOnLED(uint16_t ledType, uint16_t toggle)
{
    //
    // Turn on LED
    //
    GPIO_writePin(ledType, 0);

    //
    // Delay for a bit.
    //
    DEVICE_DELAY_US(500000);

    if(toggle)
    {
        //
        // Turn off LED
        //
        GPIO_writePin(ledType, 1);

        //
        // Delay for a bit.
        //
        DEVICE_DELAY_US(500000);
    }
}

//*****************************************************************************
//
// turnOffLEDs - turns off both LEDs.
//
//*****************************************************************************
void turnOffLEDs(void)
{
    //
    // Turn off both LEDs.
    //
    GPIO_writePin(DEVICE_GPIO_PIN_LED1, 1);
    GPIO_writePin(DEVICE_GPIO_PIN_LED2, 1);
}

//*****************************************************************************
//
// turnOnLEDs - turns on both LEDs.
//
//*****************************************************************************
void turnOnLEDs(void)
{
    //
    // Turn on both LEDs.
    //
    GPIO_writePin(DEVICE_GPIO_PIN_LED1, 0);
    GPIO_writePin(DEVICE_GPIO_PIN_LED2, 0);
}

//*****************************************************************************
//
// prepareTxBufData - update array which is used as source to Tx data buffer.
//
//*****************************************************************************
void prepareTxBufData(int nLength)
{
    uint16_t i;

    for(i = 0; i < nLength; i++)
    {
        txBufData[i] = txBufData[i] + 1;
    }
}

//*****************************************************************************
//
// fsiTxInt1ISR - FSI TX Interrupt on INT1 line.
//
//*****************************************************************************
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

//*****************************************************************************
//
// fsiTxInt2ISR - FSI TX Interrupt on INT2 line.
//
//*****************************************************************************
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

//*****************************************************************************
//
// fsiRxInt1ISR - FSI RX Interrupt on INT1 line.
//
//*****************************************************************************
__interrupt void fsiRxInt1ISR(void)
{
    rxEventSts = FSI_getRxEventStatus(FSIRXA_BASE);

    fsiRxInt1Received = 1U;
    fsiRxCntr++;

    //
    // Clear the interrupt flag and issue ACK
    //
    FSI_clearRxEvents(FSIRXA_BASE, rxEventSts);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP7);
}

//*****************************************************************************
//
// fsiRxInt2ISR - FSI RX Interrupt on INT2 line.
//
//*****************************************************************************
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

//*****************************************************************************
//
// disableAllFSIInterrupts - disables all event interrupts in both FSI Tx/Rx,
//                           also clear them.
//
//*****************************************************************************
void disableAllFSIInterrupts(void)
{
    FSI_disableTxInterrupt(FSITXA_BASE, FSI_INT1, FSI_TX_EVTMASK);
    FSI_disableTxInterrupt(FSITXA_BASE, FSI_INT2, FSI_TX_EVTMASK);
    FSI_disableRxInterrupt(FSIRXA_BASE, FSI_INT1, FSI_RX_EVTMASK);
    FSI_disableRxInterrupt(FSIRXA_BASE, FSI_INT2, FSI_RX_EVTMASK);

    FSI_clearTxEvents(FSITXA_BASE, FSI_TX_EVTMASK);
    FSI_clearRxEvents(FSIRXA_BASE, FSI_RX_EVTMASK);
}

//*****************************************************************************
//
// compare16 - compares two 16 bit values and increments global error flag by 1
//             for mismatch.
//
//*****************************************************************************
static inline void compare16(uint16_t val1, uint16_t val2)
{
    if(val1 != val2)
    {
        error++;

        //
        // LED2 goes high if error.
        //
        toggleOrOnLED(DEVICE_GPIO_PIN_LED2, ON);

        ESTOP0;
    }
}

//*****************************************************************************
//
// compareBufData - compares if received data is same as transmitted ones
//                  It doesn't consider wrap-up cases, but, can be enhanced.
//
//*****************************************************************************
void compareBufData(uint16_t txBufIndex, uint16_t rxBufIndex, uint16_t nWords)
{
    uint16_t i;

    for(i = 0; i < nWords; i++)
    {
        if(rxBufAddr[rxBufIndex] != txBufAddr[txBufIndex])
        {
            error++;

            //
            // LED2 goes high if error.
            //
            toggleOrOnLED(DEVICE_GPIO_PIN_LED2, ON);

            ESTOP0;
            return;
        }

        txBufIndex++;
        rxBufIndex++;
    }
}

//*****************************************************************************
//
// checkReceivedFrameTypeTag - checks received frame type/tag and updates global
//                             error flag.
//
//*****************************************************************************
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
