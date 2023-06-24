//#############################################################################
//
// FILE:   fsi_ex10_spi_slave_rx_driver.c
//
// TITLE:  FSI(Slave Rx) and SPI(Master Tx) communication
//
//! \addtogroup driver_example_list
//! <h1>FSI and SPI communication (fsi_ex10_spi_slave_rx_driver) </h1>
//!
//! Port of fsi_ex7_spi_slave_rx example using spifsi driver.
//! FSI supports SPI compatibility mode to talk to the devices not having FSI
//! but SPI module. Example sets up infinite data frame transfers where FSI acts
//! like slave Rx and SPI as master Rx.
//! API to build the FSI frame at SPI end before transfer is implemented in SW
//! and checks are made to ensure received details (frame tag/type, userdata,
//! data) on FSI Rx match with transferred data.
//!
//! If there are any comparison failures during transfers or any of error
//! event occurs, execution will stop.
//!
//!\b External \b Connections \n
//!   For FSI(Rx) <-> SPI(Tx) communication on controlCARD, make connections 
//!   in GPIO settings
//!
//! There is no requirement for a chip select signal to be used when connected
//! to the FSIRX. This is because the FSIRX will respond to any incoming clock
//! edge.
//!
//!  - GPIO_13 -> GPIO_9        :: To connect FSIRX_CLK with SPICLKA
//!         (59 -> 71 on docking station)
//!  - GPIO_12 -> GPIO_8        :: To connect FSIRX_RX0 with SPISIMOA
//!         (57 -> 87 on docking station)
//!
//! \b Watch \b Variables \n
//!  - \b dataFrameCntr  Number of Data frame transfered
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
#include "spifsi.h"

// Period (in us) with which CPU Timer-0 will send events
#define TIMER_PERIOD_US  1000U
#define PRESCALER_VAL    25U
#define SPI_CLK_SPEED    500000U

//
// Globals, User can modify these parameters as per usecase
//

//
// FrameTag and userData used with Data/Ping/Error transfers
//
SPIFSI_FrameTag txDataFrameTag = SPIFSI_FRAME_TAG10;
SPIFSI_FrameTag txPingFrameTag = SPIFSI_FRAME_TAG0;
SPIFSI_FrameTag txErrorFrameTag = SPIFSI_FRAME_TAG15;
uint16_t txUserData = 0x47U;

//
// Globals, these are not config parameters, user are not required to edit them
//

//
// tx/rxEventSts - describes status of FSI_TX/RX.
// *tx/rxBufAddr - address of FSI_TX/RX buffers.
//
uint16_t txEventSts = 0U, rxEventSts = 0U;
uint16_t *txBufAddr = 0U, *rxBufAddr = 0U;

//
// Interrupt Line flag.
//
volatile uint32_t fsiTxInt1Received = 0U, fsiTxInt2Received = 0U;
volatile uint32_t fsiRxInt1Received = 0U, fsiRxInt2Received = 0U;

//
// dataFrameCntr - number of frames received by FSI.
// spiTxCntr - number of frames transmitted from SPI.
// error - number of errors.
// spifsiErrorStatus - error status returned from SPIFSI api calls.
// spiFrameInfo - software-defined encoded frame by SPI.
// nLength - number of 16-bit words data.
// txBufData[16] - data to be transmitted from SPI.
//
uint32_t dataFrameCntr = 0U;
uint32_t spiTxCntr = 0U;
uint32_t error = 0U;
SPIFSI_Error spifsiErrorStatus = SPIFSI_NO_ERROR;
SPIFSI_FrameInfo  spiFrameInfo;
uint16_t nLength;
uint16_t txBufData[16] = {0};

//
// Function Prototypes
//
void init(void);
static inline void compare16(uint16_t val1, uint16_t val2);
void compareBufData(uint16_t txBufIndex, uint16_t rxBufIndex, uint16_t nLength);
void prepareTxBufData(uint16_t nLength);
void pingOrErrorFrame(SPIFSI_FrameType frameType);
void dataFrame(void);
void configureSPI(void);
void sendFlushSeqFromSPI(void);
void buildSpiFrameInfo(SPIFSI_FrameType frameType, uint16_t userData,
                      uint16_t nLength, SPIFSI_FrameTag frameTag);
__interrupt void fsiTxInt1ISR(void);
__interrupt void fsiTxInt2ISR(void);
__interrupt void fsiRxInt1ISR(void);
__interrupt void fsiRxInt2ISR(void);
void disableAllFSIInterrupts(void);

//*****************************************************************************
//
// Main
//
//*****************************************************************************
void main(void)
{
    init();

    //
    // Encode and send Ping frame with ping tag from SPI.
    // Then verify on FSI side.
    //
    pingOrErrorFrame(SPIFSI_FRAME_TYPE_PING);

    //
    // Encode and send Error frame with error tag from SPI.
    // Then verify on FSI side.
    //
    pingOrErrorFrame(SPIFSI_FRAME_TYPE_ERROR);

    //
    // Encode and send 1 - 16 words data frame with data tag from SPI.
    // Then verify on FSI side.
    //
    dataFrame();

    //
    // Now, start transfers from SPI end after building a data frame.
    //
    while(1)
    {
        //
        // In case of comparison failures, break execution
        // Else, increment received data frame counter and reset FSI Rx buffer
        // for next transfer
        //
        if(error)
        {
            break;
        }
    }

    //
    // Coming out of infinite while loop means data comparison test failed.
    // Debug further to root-cause
    //
    ESTOP0;

    //
    // Infinite loop.
    //
    while(1U);
}

//*****************************************************************************
//
// Sending PING or ERROR frame, then verifying. (SPI -> FSI)
//
//*****************************************************************************
void pingOrErrorFrame(SPIFSI_FrameType frameType)
{
    //
    // Build spiFrameInfo.
    // UserData and nLength are not required for PING/ERROR frame.
    //
    if(frameType == SPIFSI_FRAME_TYPE_PING)
    {
        buildSpiFrameInfo(frameType, 0U, 0U, txPingFrameTag);
    }
    else
    {
        buildSpiFrameInfo(frameType, 0U, 0U, txErrorFrameTag);
    }

    //
    // Encode and transmit the Frame.
    //
    spifsiErrorStatus = SPIFSI_writeFrame(SPIA_BASE, &spiFrameInfo);
    if(spifsiErrorStatus)
    {
        error++;
    }

    //
    // Wait till FSI Rx completely receives a frame.
    //
    while(fsiRxInt1Received != 1U);
    fsiRxInt1Received = 0;

    //
    // Increment spiTxCntr.
    //
    spiTxCntr++;

    //
    // Compare frameType.
    //
    compare16((SPIFSI_FrameType) FSI_getRxFrameType(FSIRXA_BASE), frameType);

    //
    // Compare frameTag.
    // Seperate driverLib function for Ping Frame.
    //
    if (frameType == SPIFSI_FRAME_TYPE_PING)
    {
        compare16((SPIFSI_FrameTag) FSI_getRxPingTag(FSIRXA_BASE), txPingFrameTag);
    }
    else
    {
        compare16((SPIFSI_FrameTag) FSI_getRxFrameTag(FSIRXA_BASE), txErrorFrameTag);
    }

    //
    // Reset SPI_TXFIFO and FSI_RX
    //
    SPI_resetTxFIFO(SPIA_BASE);
    FSI_setRxBufferPtr(FSIRXA_BASE, 0U);
}

//*****************************************************************************
//
// Sending 1 to 16 word frames, then verifying. (SPI -> FSI)
//
//*****************************************************************************
void dataFrame(void)
{
    SPIFSI_FrameType frameType;

    for (nLength = 1; nLength <= 16; nLength++)
    {
        //
        // If nLength is not 1,2,4, nor 6, use NWORD_DATA_FRAME.
        //
        switch (nLength)
        {
            case 1U:
                frameType = SPIFSI_FRAME_TYPE_1WORD_DATA;
                break;
            case 2U:
                frameType = SPIFSI_FRAME_TYPE_2WORD_DATA;
                break;
            case 4U:
                frameType = SPIFSI_FRAME_TYPE_4WORD_DATA;
                break;
            case 6U:
                frameType = SPIFSI_FRAME_TYPE_6WORD_DATA;
                break;
            default:
                frameType = SPIFSI_FRAME_TYPE_NWORD_DATA;

                //
                // Let FSI know the number of data words.
                //
                FSI_setRxSoftwareFrameSize(FSIRXA_BASE, nLength);
                break;
        }

        //
        // Build spiFrameInfo.
        //
        buildSpiFrameInfo(frameType, txUserData, nLength, txDataFrameTag);
        prepareTxBufData(nLength);

        //
        // Encode and transmit the Frame.
        //
        spifsiErrorStatus = SPIFSI_writeFrame(SPIA_BASE, &spiFrameInfo);
        if (spifsiErrorStatus)
        {
            error++;
        }

        //
        // Wait till FSI Rx completely receives a frame.
        //
        while(fsiRxInt1Received != 1U);
        fsiRxInt1Received = 0;
        FSI_setRxBufferPtr(FSIRXA_BASE, 0U);

        //
        // Increment spiTxCntr.
        //
        spiTxCntr++;

        //
        // Verify frameType, userData, data, CRC8, and frameTag.
        //
        compare16((SPIFSI_FrameType) FSI_getRxFrameType(FSIRXA_BASE), frameType);
        compare16(FSI_getRxUserDefinedData(FSIRXA_BASE), txUserData);
        compareBufData(0U, 0U, nLength);
        compare16(FSI_getRxReceivedCRC(FSIRXA_BASE), FSI_getRxComputedCRC(FSIRXA_BASE));
        compare16((SPIFSI_FrameTag) FSI_getRxFrameTag(FSIRXA_BASE), txDataFrameTag);

        //
        // Reset SPI_TXFIFO and FSI_RX
        //
        SPI_resetTxFIFO(SPIA_BASE);
        FSI_setRxBufferPtr(FSIRXA_BASE, 0U);
    }
}
//*****************************************************************************
//
// Populates spiInfoFrame fields.
//
//*****************************************************************************
void buildSpiFrameInfo(SPIFSI_FrameType frameType, uint16_t userData,
                      uint16_t nLength, SPIFSI_FrameTag frameTag)
{
    spiFrameInfo.frameType = frameType;
    spiFrameInfo.userData = userData;
    spiFrameInfo.nLength = nLength;
    spiFrameInfo.frameTag = frameTag;
}

//*****************************************************************************
//
// Device/variable initialization.
//
//*****************************************************************************
void init(void)
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
    // Disable Internal Loopback in FSI Rx and keep it under master Core reset
    // till all GPIO settings are made, also clear any Rx events.
    //
    FSI_disableRxInternalLoopback(FSIRXA_BASE);

    FSI_resetRxModule(FSIRXA_BASE, FSI_RX_MASTER_CORE_RESET);
    FSI_clearRxEvents(FSIRXA_BASE, FSI_RX_EVTMASK);

    //
    // NOTE: External loopback, Modify GPIO settings as per setup
    //
    GPIO_setPinConfig(DEVICE_GPIO_CFG_FSI_RXCLK);
    GPIO_setPinConfig(GPIO_12_FSIRXA_D0);

    GPIO_setPinConfig(DEVICE_GPIO_CFG_SPICLKA);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_SPISIMOA);

    //
    // Set GP12,13 (12, 33 on LaunchPad)
    // to be asynchronous(pass through without delay)
    // Default setting is to have 2 SYS_CLK cycles delay
    //
    GPIO_setQualificationMode(12, GPIO_QUAL_ASYNC);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_FSI_RXCLK, GPIO_QUAL_ASYNC);

    //
    // Configure SPI module for master Tx operation
    //
    configureSPI();

    //
    // Enable SPI mode on the FSI Rx and take it out of reset. Also, send Flush
    // sequence from SPI to synchronize with FSI Rx
    //
    FSI_enableRxSPIMode(FSIRXA_BASE);
    FSI_clearRxModuleReset(FSIRXA_BASE, FSI_RX_MASTER_CORE_RESET);
    DEVICE_DELAY_US(10);
    sendFlushSeqFromSPI();

    //
    // Assigning base addresses of Tx/Rx data buffer to globals
    //
    rxBufAddr = (uint16_t *) FSI_getRxBufferAddress(FSIRXA_BASE);
    txBufAddr = (uint16_t *) txBufData;

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
    // Configure for data transfers
    //
    //
    // Enable normal data transfer events to be sent over INT1 line and Error
    // events on INT2 from FSI Rx
    //
    FSI_enableRxInterrupt(FSIRXA_BASE, FSI_INT1, FSI_RX_EVT_DATA_FRAME |
    FSI_RX_EVT_FRAME_DONE);

    FSI_enableRxInterrupt(FSIRXA_BASE, FSI_INT2, FSI_RX_EVT_CRC_ERR |
    FSI_RX_EVT_EOF_ERR |
    FSI_RX_EVT_FRAME_OVERRUN |
    FSI_RX_EVT_TYPE_ERR);

    //
    // initialize spiFrameInfo.
    //
    spiFrameInfo.data = txBufData;

    //
    // Assigning base addresses of Tx/Rx data buffer to globals
    //
    rxBufAddr = (uint16_t *) FSI_getRxBufferAddress(FSIRXA_BASE);
    txBufAddr = (uint16_t *) txBufData;
}

//*****************************************************************************
//
// prepareTxBufData - Update array which is used as source to Tx data buffer
//
//*****************************************************************************
void prepareTxBufData(uint16_t nLength)
{
    uint16_t i;

    for(i = 0; i < nLength; i++)
    {
        txBufData[i] = txBufData[i] + 1;
    }
}

//*****************************************************************************
//
// fsiTxInt1ISR - FSI Tx Interrupt on INsT1 line
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
// fsiTxInt2ISR - FSI Tx Interrupt on INT2 line
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
// fsiRxInt1ISR - FSI Rx Interrupt on INT1 line
//
//*****************************************************************************
__interrupt void fsiRxInt1ISR(void)
{
    rxEventSts = FSI_getRxEventStatus(FSIRXA_BASE);

    fsiRxInt1Received = 1U;
    dataFrameCntr++;

    //
    // Clear the interrupt flag and issue ACK
    //
    FSI_clearRxEvents(FSIRXA_BASE,rxEventSts);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP7);
}

//*****************************************************************************
//
// fsiRxInt2ISR - FSI Rx Interrupt on INT2 line
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
// disableAllFSIInterrupts - Disables all event interrupts in both FSI Tx/Rx,
//                           also clear them
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
// compare16 - Compares two 16 bit values and increments global error flag by 1
//             for mismatch
//
//*****************************************************************************
static inline void compare16(uint16_t val1, uint16_t val2)
{
    if(val1 != val2)
    {
        error++;
    }
}

//*****************************************************************************
//
// compareBufData - Compares if received data is same as transmitted ones
//                  It doesn't consider wrap-up cases, but, can be enhanced
//
//*****************************************************************************
void compareBufData(uint16_t txBufIndex, uint16_t rxBufIndex, uint16_t nLength)
{
    uint16_t i;

    for(i = 0; i < nLength; i++)
    {
        if(rxBufAddr[rxBufIndex] != txBufAddr[txBufIndex])
        {
            error++;
            return;
        }

        txBufIndex++;
        rxBufIndex++;
    }
}

//*****************************************************************************
//
// configureSPI - Configures the SPI for master Tx operation
//
//*****************************************************************************
void configureSPI(void)
{
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SPIA);
    SPI_disableModule(SPIA_BASE);

    SPI_setConfig(SPIA_BASE, DEVICE_LSPCLK_FREQ, SPI_PROT_POL0PHA0,
                  SPI_MODE_MASTER, SPI_CLK_SPEED, 16U);

    SPI_enableFIFO(SPIA_BASE);
    SPI_setEmulationMode(SPIA_BASE, SPI_EMULATION_FREE_RUN);

    SPI_enableModule(SPIA_BASE);
}

//*****************************************************************************
//
// sendFlushSeqFromSPI - Send Flush sequence from SPI to FSI Rx
//
//*****************************************************************************
void sendFlushSeqFromSPI(void)
{
    uint16_t flushSeq = 0xFFFF;
    SPI_write16Bits(SPIA_BASE, &flushSeq);
}

//
// End of File
//
