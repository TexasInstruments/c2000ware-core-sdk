//#############################################################################
//
// FILE:   fsi_ex7_spi_remote_rx.c
//
// TITLE:  FSI(Remote Rx) and SPI(Main Tx) communication
//
//! \addtogroup driver_example_list
//! <h1>FSI and SPI communication(fsi_ex7_spi_remote_rx) </h1>
//!
//! FSI supports SPI compatibility mode to talk to the devices not having FSI
//! but SPI module. Example sets up infinite data frame transfers where FSI acts
//! like remote Rx and SPI as main Rx.
//! API to build the FSI frame at SPI end before transfer is implemented in SW
//! and checks are made to ensure received details(frame tag/type, userdata,
//! data) on FSI Rx match with transferred data.
//!
//! If there are any comparison failures during transfers or any of error
//! event occurs, execution will stop.
//!
//!\b External \b Connections \n
//!   For FSI(Rx) <-> SPI(Tx) communication, make connections in GPIO settings
//!
//! There is no requirement for a chip select signal to be used when connected
//! to the FSIRX. This is because the FSIRX will respond to any incoming clock
//! edge.
//!
//!  - GPIO_13 -> GPIO_9        :: To connect FSIRX_CLK with SPICLKA
//!  - GPIO_12 -> GPIO_8        :: To connect FSIRX_RX0 with SPIPICOA
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

//
// Defines
//

// Period(in us) with which CPU Timer-0 will send events
#define TIMER_PERIOD_US  1000U

#define PRESCALER_VAL    25U

//
// Globals, User can modify these parameters as per usecase
//
// Number of words per transfer may be from 1 -16
uint16_t nWords = 13;

// FSI Clock used for transfer
uint32_t fsiClock = 50000000;

// Frame tag used with Data/Ping transfers
FSI_FrameTag txDataFrameTag = FSI_FRAME_TAG10, txPingFrameTag = FSI_FRAME_TAG15;

// User data to be sent with Data frame
uint16_t txUserData = 0x47;

//
// Globals, these are not config parameters, user are not required to edit them
//
uint16_t txEventSts = 0, rxEventSts = 0;
uint16_t *txBufAddr = 0, *rxBufAddr = 0;

uint16_t txBufData[16] = {0};
volatile uint32_t fsiTxInt1Received = 0,fsiTxInt2Received = 0;
volatile uint32_t fsiRxInt1Received = 0,fsiRxInt2Received = 0;

uint32_t dataFrameCntr = 0;
uint32_t error = 0, idx = 0;

typedef struct
{
    FSI_FrameType type;
    uint16_t      userdata;
    uint16_t     *data;
    uint16_t      data_len;
    uint16_t      crcbyte;
    FSI_FrameTag  tag;
} SPI_FSIFrameInfo;

typedef struct
{
    uint16_t frameLen;
    uint16_t spiDataBuf[18];
} SPI_FSIBuiltFrame;

uint16_t spiTempBuf[18];
SPI_FSIFrameInfo  spiFrameInfo;
SPI_FSIBuiltFrame spiBuiltFrame;

unsigned long resultcrccalculated = 0;
int inpdata[50];

//
// Function Prototypes
//
static inline void compare16(uint16_t val1, uint16_t val2);
void compareBufData(uint16_t txBufIndex, uint16_t rxBufIndex, uint16_t nWords);
void disableAllFSIInterrupts(void);
void checkReceivedFrameTypeTag(FSI_FrameType type, FSI_FrameTag tag);
void configTimer0(void);

void prepareTxBufData(void);
__interrupt void fsiTxInt1ISR(void);
__interrupt void fsiTxInt2ISR(void);
__interrupt void fsiRxInt1ISR(void);
__interrupt void fsiRxInt2ISR(void);

void configureSPI(void);
void sendFlushSeqFromSPI(void);
void buildFSIFrameForSPI(SPI_FSIFrameInfo *frameInfo,
                         SPI_FSIBuiltFrame *txFrame);

unsigned long crc8(unsigned long address, unsigned int no_locations);

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
    // Disable Internal Loopback in FSI Rx and keep it under main Core reset
    // till all GPIO settings are made, also clear any Rx events.
    //
    FSI_disableRxInternalLoopback(FSIRXA_BASE);

    FSI_resetRxModule(FSIRXA_BASE, FSI_RX_MAIN_CORE_RESET);
    FSI_clearRxEvents(FSIRXA_BASE, FSI_RX_EVTMASK);

    //
    // NOTE: External loopback, Modify GPIO settings as per setup
    //
    GPIO_setPinConfig(GPIO_13_FSIRXA_CLK);
    GPIO_setPinConfig(GPIO_12_FSIRXA_D0);

    GPIO_setPinConfig(GPIO_9_SPIA_CLK);
    GPIO_setPinConfig(GPIO_8_SPIA_SIMO);

    //
    // Set GP11, 12,13 to be asynchronous(pass through without delay)
    // Default setting is to have 2 SYS_CLK cycles delay
    //
    GPIO_setQualificationMode(12, GPIO_QUAL_ASYNC);
    GPIO_setQualificationMode(13, GPIO_QUAL_ASYNC);

    //
    // Configure SPI module for main Tx operation
    //
    configureSPI();

    //
    // Enable SPI mode on the FSI Rx and take it out of reset. Also, send Flush
    // sequence from SPI to synchronize with FSI Rx
    //
    FSI_enableRxSPIMode(FSIRXA_BASE);
    FSI_clearRxModuleReset(FSIRXA_BASE, FSI_RX_MAIN_CORE_RESET);
    DEVICE_DELAY_US(10);
    sendFlushSeqFromSPI();

    //
    // Assigning base addresses of Tx/Rx data buffer to globals
    //
    rxBufAddr = (uint16_t *)FSI_getRxBufferAddress(FSIRXA_BASE);
    txBufAddr = (uint16_t *)txBufData;

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
    // Setting for requested nWords with transfers
    //
    FSI_setRxSoftwareFrameSize(FSIRXA_BASE, nWords);

    //
    // Fill the Frame Info fields for SPI main
    //
    spiFrameInfo.tag = txDataFrameTag;
    spiFrameInfo.data = &txBufData[0];
    spiFrameInfo.data_len = nWords;
    spiFrameInfo.type = FSI_FRAME_TYPE_NWORD_DATA;
    spiFrameInfo.userdata = txUserData;

    //
    // Now, start transfers from SPI end after building a data frame.
    //
    while(1)
    {
        //
        // Update Tx data and build frame for transfer
        //
        prepareTxBufData();
        buildFSIFrameForSPI(&spiFrameInfo, &spiBuiltFrame);

        //
        // Now sending word(16 bit) by word from SPI for full frame
        //
        for(idx = 0; idx < spiBuiltFrame.frameLen; idx++)
        {
            SPI_writeDataBlockingFIFO(SPIA_BASE, spiBuiltFrame.spiDataBuf[idx]);
        }

        //
        // Wait till FSI Rx completely receives a frame.
        //
        while (fsiRxInt1Received != 1U);
        fsiRxInt1Received = 0;

        //
        // Verify Frame attributes and data
        //
        compare16(rxEventSts, (FSI_RX_EVT_DATA_FRAME | FSI_RX_EVT_FRAME_DONE));

        compare16(FSI_getRxFrameType(FSIRXA_BASE), FSI_FRAME_TYPE_NWORD_DATA);
        compare16(FSI_getRxFrameTag(FSIRXA_BASE), txDataFrameTag);
        compare16(FSI_getRxUserDefinedData(FSIRXA_BASE), txUserData);
        compareBufData(0U, 0U, nWords);

        //
        // In case of comparison failures, break execution
        // Else, increment received data frame counter and reset FSI Rx buffer
        // for next transfer
        //
        if(error)
        {
            break;
        }

        dataFrameCntr++;
        FSI_setRxBufferPtr(FSIRXA_BASE, 0U);
    }

    //
    // Coming out of infinite while loop means data comparison test failed.
    // Debug further to root-cause
    //
    ESTOP0;
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

    for(i = 0; i < nWords; i++)
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
// buildFSIFrameForSPI - builds the data frame for SPI which FSI Rx can
//                       understand
//
void buildFSIFrameForSPI(SPI_FSIFrameInfo *frameInfo,
                         SPI_FSIBuiltFrame *txFrame)
{
    uint16_t i = 0;
    uint16_t j = 0;
    // maximum 16 + udata
    uint16_t crc_tempArray[17];
    uint16_t crc_val = 0;

    //
    // First put the SOF (1001'b) in the upper 4 bits
    // Frame Type field in the next 4 bits
    // User data in the lower 8 bits
    //
    i = 0;

    txFrame->spiDataBuf[i] = 0x9000 | ((frameInfo->type <<8)& 0x0F00);

    switch (frameInfo->type)
    {
        case FSI_FRAME_TYPE_NWORD_DATA:
        case FSI_FRAME_TYPE_1WORD_DATA:
        case FSI_FRAME_TYPE_2WORD_DATA:
        case FSI_FRAME_TYPE_4WORD_DATA:
        case FSI_FRAME_TYPE_6WORD_DATA:
            //
            // Data frame has been chosen. So add user data, set the frame
            // length and fill the data to be transmitted. Also, create the CRC
            // value on data + userdata to be sent across
            //
            txFrame->spiDataBuf[i] |=(frameInfo->userdata & 0x00FF);
            txFrame->frameLen= frameInfo->data_len + 2;

            for(i = 1; i <= frameInfo->data_len; i++)
            {
                txFrame->spiDataBuf[i] = frameInfo->data[i-1];
            }

            crc_tempArray[0] = (frameInfo->userdata <<8) & 0xFF00;
            for(j = 1; j <= frameInfo->data_len;j++)
            {
                crc_tempArray[j] = frameInfo->data[j-1];
            }

            crc_val = crc8((uint32_t)(&crc_tempArray[0]), frameInfo->data_len +1);
            frameInfo->crcbyte = crc_val & 0x00FF;

            //
            // Add the CRC (lower 8), Frame Tag (next 4), and EOF (upper4)
            //
            txFrame->spiDataBuf[i] = (crc_val <<8)&0xFF00;
            break;
        case FSI_FRAME_TYPE_ERROR:
        case FSI_FRAME_TYPE_PING:
            //
            // There is nothing else to add
            // set the data length of the SPI array to be 1 word.
            //
            txFrame->frameLen = 1;
            break;
        default:
            break;
    }

    //
    // Complete the frame by adding the tag and EOF fields
    //
    txFrame->spiDataBuf[i] |= ((frameInfo->tag <<4) & 0x00F0) | 0x0006;
}

//
// configureSPI - Configures the SPI for main Tx operation
//
void configureSPI(void)
{
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SPIA);
    SPI_disableModule(SPIA_BASE);

    SPI_setConfig(SPIA_BASE, SysCtl_getLowSpeedClock(20000000),
                  SPI_PROT_POL0PHA0, SPI_MODE_CONTROLLER, 5000000, 16);

    SPI_enableFIFO(SPIA_BASE);
    SPI_setEmulationMode(SPIA_BASE, SPI_EMULATION_FREE_RUN);

    SPI_enableModule(SPIA_BASE);
}

//
// sendFlushSeqFromSPI - Send Flush sequence from SPI to FSI Rx
//
void sendFlushSeqFromSPI(void)
{
    SPI_writeDataBlockingFIFO(SPIA_BASE,0xFFFF);
}

//
// crc8 - This function calculates crc8 i.e. polynomial with highest degree 8
//        It returns 32 bit CRC and assumes that, at each location data is
//        written as "16" bit and i/p to the function is "starting address
//        location and no.of locations for which crc8 has to be calculated"
//
unsigned long crc8(unsigned long address, unsigned int no_locations)
{
    int count;
    unsigned long address1 = address;

    //
    // Clear CRC
    //
    asm(" VCRCCLR ");

    for(count = 0; count < no_locations; count++){
     inpdata[count] = HWREGH(address1);
     address1++;
    }

    //
    // Pointer to the beginning of data section - vcu_data_init - source pointer
    //
    #if defined(__TI_EABI__)
    asm(" MOVL XAR6,#inpdata ");
    #else
    asm(" MOVL XAR6,#_inpdata ");
    #endif

    //
    //pointer for destination
    //
    #if defined(__TI_EABI__)
    asm(" MOV DP,#resultcrccalculated ");
    #else
    asm(" MOV DP,#_resultcrccalculated ");
    #endif

    for(count = 1; count <= no_locations; count++)
    {
        //
        // CRC calculation : VCU instructions
        //
        asm(" VNOP ");
        asm(" VCRC8L_1 *XAR6 ");  //calculates CRC on lower byte of 16 bit
        asm(" VCRC8H_1 *XAR6++ ");  //calculates CRC on higher byte of 16 bit
        asm(" VNOP ");
        asm(" VNOP ");
    }

    #if defined(__TI_EABI__)
    asm(" VMOV32 @resultcrccalculated, VCRC ");
    #else
    asm(" VMOV32 @_resultcrccalculated, VCRC ");
    #endif
    return(resultcrccalculated);
}

//
// End of File
//
