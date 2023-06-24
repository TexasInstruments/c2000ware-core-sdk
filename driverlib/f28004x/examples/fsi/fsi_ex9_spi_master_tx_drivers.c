//#############################################################################
//
// FILE:  fsi_ex9_spi_master_tx_drivers.c
//
// TITLE:  FSI(Master Tx) and SPI(Slave Rx) communication
//
//! \addtogroup driver_example_list
//! <h1>FSI and SPI communication (fsi_ex9_spi_master_tx_drivers) </h1>
//!
//! Port of fsi_ex6_spi_mater_tx example using spifsi drivers.
//! FSI supports SPI compatibility mode to talk to the devices not having FSI
//! but SPI module. Example sets up infinite data frame transfers where FSI acts
//! like master Tx and SPI as slave Rx.
//! API to decode FSI frame received at SPI end is implemented and checks are
//! made to ensure received details (frame tag/type, userdata, data) match with
//! transfered frame.
//!
//! If there are any comparison failures during transfers or any of error
//! event occurs, execution will stop.
//!
//!\b External \b Connections \n
//!   For FSI <-> SPI communication, make below connections on controlCard
//!   in GPIO settings
//!
//!  - GPIO_7 -> GPIO_9        :: To connect FSITX_CLK with SPICLKA
//!         (56 -> 71 on docking station)
//!  - GPIO_6 -> GPIO_8        :: To connect FSITX_TX0 with SPISIMOA
//!         (54 -> 87 on docking station)
//!  - GPIO_5 -> GPIO_11       :: To connect FSITX_TX1 with SPISTEA
//!         (52 -> 73 on docking station)
//!
//! \b Watch \b Variables \n
//!  - \b dataFrameCntr  Number of Data frame transfered from FSI.
//!  - \b spiRxCntr      Number of Data frame received at SPI.
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
#include "device.h"
#include "driverlib.h"
#include "spifsi.h"

// Period (in us) with which CPU Timer-0 will send events
#define TIMER_PERIOD_US 1000U
#define PRESCALER_VAL   25U
#define SPI_CLK_SPEED   500000U

//
// Globals, User can modify these parameters as per usecase
//

//
// Number of words per transfer may be from 1 - 16
//
uint16_t nLength;

//
// FrameTag and userData used with Data/Ping/Error transfers
//
SPIFSI_FrameTag txDataFrameTag = SPIFSI_FRAME_TAG10;
SPIFSI_FrameTag txPingFrameTag = SPIFSI_FRAME_TAG0;
SPIFSI_FrameTag txErrorFrameTag = SPIFSI_FRAME_TAG15;
uint16_t txUserData = 0x47U;

//
// SPI-side error flag.
//
SPIFSI_Error spifsiErrorStatus = SPIFSI_NO_ERROR;

//
// Globals, these are not config parameters, user are not required to edit them
//
uint16_t txEventSts = 0U, rxEventSts = 0U;
uint16_t *txBufAddr = 0U, *rxBufAddr = 0U;

//
// Interrupt Line flag.
//
volatile uint32_t fsiTxInt1Received = 0U,fsiTxInt2Received = 0U;
volatile uint32_t fsiRxInt1Received = 0U,fsiRxInt2Received = 0U;
volatile uint32_t spiRxIntReceived = 0U;

//
// dataFrameCntr - number of frames transmitted from FSI.
// spiRxCntr - number of frames received by SPI.
// error - number of errors.
// spiFrameInfo - software-defined decoded frame by SPI.
// data[16] - decoded data array by SPI.
// txBufData[18] - data to be transmitted from FSI.
//
uint32_t dataFrameCntr = 0U;
uint32_t spiRxCntr = 0U;
uint32_t error = 0U;
SPIFSI_FrameInfo  spiFrameInfo;
uint16_t data[16];
uint16_t txBufData[18] = { 0 };

//
// Function Prototypes
//
void init(void);
void configureSPI(void);
void pingOrErrorFrame(SPIFSI_FrameType frameType);
void dataFrame(void);
void prepareTxBufData(uint16_t nLength);
void compareBufData(uint16_t txBufIndex, uint16_t rxBufIndex, uint16_t nLength);
static inline void compare16(uint16_t val1, uint16_t val2);
__interrupt void fsiTxInt1ISR(void);
__interrupt void fsiTxInt2ISR(void);
__interrupt void fsiRxInt1ISR(void);
__interrupt void fsiRxInt2ISR(void);
__interrupt void spiRxFIFOISR(void);
void disableAllFSIInterrupts(void);


//*****************************************************************************
//
// Main.
//
//*****************************************************************************
void main(void)
{
    init();

    //
    // Now, start sending data frames from FSI Tx and receive + verify at SPI end
    // Come out of loop if there is any mismatch btw transmit and receive data.
    //
    while(1U)
    {
        //
        // Send Ping frame with ping tag, then decode/verify on SPI side.
        //
        pingOrErrorFrame(SPIFSI_FRAME_TYPE_PING);

        //
        // Send Error frame with error tag, then decode/verify on SPI side.
        //
        pingOrErrorFrame(SPIFSI_FRAME_TYPE_ERROR);

        //
        // Send 1 - 16 words data frame with data tag,
        // then decode/verify on SPI side.
        //
        dataFrame();

        //
        // In case of comparison failures, break execution
        // Else, increment received data frame counter and reset FSI Tx buffer
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
// Sending PING or ERROR frame, then verifying. (FSI -> SPI)
//
//*****************************************************************************
void pingOrErrorFrame(SPIFSI_FrameType frameType)
{
    //
    // set frameType.
    //
    FSI_setTxFrameType(FSITXA_BASE, (FSI_FrameType) frameType);

    //
    // Set frameTag then transmit.
    //
    if(frameType == SPIFSI_FRAME_TYPE_PING)
    {
        FSI_setTxFrameTag(FSITXA_BASE, (FSI_FrameTag) txPingFrameTag);
    }
    else
    {
        FSI_setTxFrameTag(FSITXA_BASE, (FSI_FrameTag) txErrorFrameTag);
    }
    FSI_startTxTransmit(FSITXA_BASE);

    //
    // Wait for FSI Tx to finish transmit operation
    // Also, check that the Transmit frame done interrupt was the source
    //
    while(fsiTxInt1Received != 1U);
    fsiTxInt1Received = 0U;
    compare16(txEventSts, FSI_TX_EVT_FRAME_DONE);

    //
    // Increment dataFrameCntr.
    //
    dataFrameCntr++;

    //
    // Wait till SPI completely receives a frame.
    //
    while(spiRxIntReceived != 1U);
    spiRxIntReceived = 0U;

    //
    // Compare frameType/Tag
    //
    compare16(spiFrameInfo.frameType, frameType);
    if(frameType == SPIFSI_FRAME_TYPE_PING)
    {
        compare16(spiFrameInfo.frameTag, txPingFrameTag);
    }
    else
    {
        compare16(spiFrameInfo.frameTag, txErrorFrameTag);
    }

    //
    // Reset FSI_TxBuffer and SPI_RXFIFO
    //
    FSI_setTxBufferPtr(FSITXA_BASE, 0U);
    SPI_resetRxFIFO(SPIA_BASE);
}

//*****************************************************************************
//
// Sending 1 to 16 word frames, then verifying. (FSI -> SPI)
//
//*****************************************************************************
void dataFrame(void)
{
    SPIFSI_FrameType frameType;

    for (nLength = 1; nLength <= 16; nLength++)
    {
        //
        // set nLength for NWORD_DATA_FRAME.
        //
        spiFrameInfo.nLength = nLength;

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
                FSI_setTxSoftwareFrameSize(FSITXA_BASE, nLength);
                break;
        }

        //
        // set tag, userData, and frameType.
        //
        FSI_setTxFrameTag(FSITXA_BASE, (FSI_FrameTag) txDataFrameTag);
        FSI_setTxUserDefinedData(FSITXA_BASE, txUserData);
        FSI_setTxFrameType(FSITXA_BASE, (FSI_FrameType) frameType);

        //
        // Setting for requested nLength with transfers
        // Write data into Tx buffer and set other Frame specific fields
        //
        prepareTxBufData(nLength);
        FSI_writeTxBuffer(FSITXA_BASE, txBufData, nLength, 0U);
        FSI_startTxTransmit(FSITXA_BASE);

        //
        // Wait for FSI Tx to finish transmit operation
        // Also, check that the Transmit frame done interrupt was the source
        //
        while(fsiTxInt1Received != 1U);
        fsiTxInt1Received = 0U;
        compare16(txEventSts, FSI_TX_EVT_FRAME_DONE);

        //
        // Increment dataFrameCntr.
        //
        dataFrameCntr++;

        //
        // Wait till SPI completely receives a frame.
        //
        while(spiRxIntReceived != 1U);
        spiRxIntReceived = 0U;

        //
        // Compare frameType, frameTag, userData, and data,
        //
        compare16(spiFrameInfo.frameType, frameType);
        compare16(spiFrameInfo.frameTag, txDataFrameTag);
        compare16(spiFrameInfo.userData, txUserData);
        compareBufData(0U, 0U, spiFrameInfo.nLength);

        //
        // Reset FSI_TxBuffer and SPI_RXFIFO
        //
        FSI_setTxBufferPtr(FSITXA_BASE, 0U);
        SPI_resetRxFIFO(SPIA_BASE);
    }
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
    Interrupt_register(INT_SPIA_RX, &spiRxFIFOISR);

    // TODO- Add logic to calculate PRESCALER_VAL based on user input FSI CLK
    FSI_performTxInitialization(FSITXA_BASE, PRESCALER_VAL);
    //FSI_disableRxInternalLoopback(FSIRXA_BASE);

    //
    // Configure GPIOs for FSI Tx and SPIA
    //
    GPIO_setPinConfig(GPIO_7_FSITXA_CLK);
    GPIO_setPinConfig(GPIO_6_FSITXA_D0);
    GPIO_setPinConfig(GPIO_5_FSITXA_D1);

    GPIO_setPinConfig(DEVICE_GPIO_CFG_SPICLKA);
    GPIO_setPinConfig(GPIO_11_SPIA_STE);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_SPISOMIA);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_SPISIMOA);

    //
    // Set GP8, 9, 10, 11 (56, 16, 17, 11 on LaunchPad) to be 
    // asynchronous(pass through without delay)
    // Default setting is to have 2 SYS_CLK cycles delay
    //
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_SPISOMIA, GPIO_QUAL_ASYNC);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_SPICLKA, GPIO_QUAL_ASYNC);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_SPISIMOA, GPIO_QUAL_ASYNC);
    GPIO_setQualificationMode(11, GPIO_QUAL_ASYNC);

    //
    // Configure SPI module for Rx operation
    //
    configureSPI();

    //
    // enable SPI mode on the FSIRX
    //
    FSI_enableTxSPIMode(FSITXA_BASE);

    //
    // Enable FSI Tx/Rx interrupts
    //
    Interrupt_enable(INT_FSITXA_INT1);
    Interrupt_enable(INT_FSITXA_INT2);
    Interrupt_enable(INT_FSIRXA_INT1);
    Interrupt_enable(INT_FSIRXA_INT2);
    Interrupt_enable(INT_SPIA_RX);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Enable normal data transfer events to be sent over INT1 line
    //
    FSI_enableTxInterrupt(FSITXA_BASE, FSI_INT1, FSI_TX_EVT_FRAME_DONE);

    //
    // initialize spiFrameInfo.data.
    //
    spiFrameInfo.data = data;

    //
    // Assigning base addresses of Tx/Rx data buffer to globals
    //
    txBufAddr = (uint16_t *) FSI_getTxBufferAddress(FSITXA_BASE);
    rxBufAddr = (uint16_t *) spiFrameInfo.data;
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
// SPI A Receive FIFO ISR at RX level 1.
// Preventing FIFO overrun.
//
//*****************************************************************************
__interrupt void spiRxFIFOISR(void)
{
    //
    // Read and check for error.
    //
    spifsiErrorStatus = SPIFSI_readFrame(SPIA_BASE, &spiFrameInfo);
    if(spifsiErrorStatus)
    {
        error++;
        ESTOP0;
    }

    //
    // Set the global interrupt.
    //
    spiRxIntReceived = 1U;

    //
    // Number of frames received on SPI side.
    //
    spiRxCntr++;

    //
    // Clear interrupt flag and issue ACK
    //
    SPI_clearInterruptStatus(SPIA_BASE, SPI_INT_RXFF);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP6);
}

//*****************************************************************************
//
// disableAllFSIInterrupts - Disables all event interrupts in both FSI Tx/Rx,
//                           also clear them
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
// configureSPI - Configure SPI for Rx slave operation
//
//*****************************************************************************
void configureSPI(void)
{
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SPIA);

    SPI_disableModule(SPIA_BASE);

    //
    // SPI configuration. Use a 500kHz SPICLK and 16-bit word size.
    // SPICLK will be an input driven by FSI_TXCLK.
    //
    SPI_setConfig(SPIA_BASE, DEVICE_LSPCLK_FREQ, SPI_PROT_POL0PHA0,
                  SPI_MODE_SLAVE, SPI_CLK_SPEED, 16U);


    SPI_enableFIFO(SPIA_BASE);
    SPI_setEmulationMode(SPIA_BASE, SPI_EMULATION_FREE_RUN);

    //
    // interrupt at FIFO level 1.
    //
    SPI_clearInterruptStatus(SPIA_BASE, SPI_INT_RXFF);
    SPI_setFIFOInterruptLevel(SPIA_BASE, SPI_FIFO_TX1, SPI_FIFO_RX1);
    SPI_enableInterrupt(SPIA_BASE, SPI_INT_RXFF);
    SPI_disableInterrupt(SPIA_BASE, SPI_INT_TXFF);

    SPI_enableModule(SPIA_BASE);
}

//
// End of File
//
