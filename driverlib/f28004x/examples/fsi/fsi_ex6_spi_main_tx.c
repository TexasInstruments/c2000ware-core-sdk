//#############################################################################
//
// FILE:   fsi_ex6_spi_main_tx.c
//
// TITLE:  FSI(Main Tx) and SPI(Remote Rx) communication
//
//! \addtogroup driver_example_list
//! <h1>FSI and SPI communication(fsi_ex6_spi_main_tx) </h1>
//!
//! FSI supports SPI compatibility mode to talk to the devices not having FSI
//! but SPI module. Example sets up infinite data frame transfers where FSI acts
//! like main Tx and SPI as remote Rx.
//! API to decode FSI frame received at SPI end is implemented and checks are
//! made to ensure received details(frame tag/type, userdata, data) match with
//! transfered frame.
//!
//! If there are any comparison failures during transfers or any of error
//! event occurs, execution will stop.
//!
//!\b External \b Connections \n
//!   For FSI <-> SPI communication, make below connections in GPIO settings
//!
//!  - GPIO_7 -> GPIO_9        :: To connect FSITX_CLK with SPICLKA
//!  - GPIO_6 -> GPIO_8        :: To connect FSITX_TX0 with SPIPICOA
//!  - GPIO_5 -> GPIO_11       :: To connect FSITX_TX1 with SPIPTEA
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
void decodeFSIFrameReceivedinSPI(SPI_FSIFrameInfo *frameInfo,
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
    // Perform FSI Tx Initialization
    //
    FSI_performTxInitialization(FSITXA_BASE, PRESCALER_VAL);

    //
    // Configure GPIOs for FSI Tx and SPIA
    //
    GPIO_setPinConfig(GPIO_7_FSITXA_CLK);
    GPIO_setPinConfig(GPIO_6_FSITXA_D0);
    GPIO_setPinConfig(GPIO_5_FSITXA_D1);

    GPIO_setPinConfig(GPIO_9_SPIA_CLK);
    GPIO_setPinConfig(GPIO_11_SPIA_STE);
    GPIO_setPinConfig(GPIO_10_SPIA_SOMI);
    GPIO_setPinConfig(GPIO_8_SPIA_SIMO);

    //
    // Set GP8, 9, 10, 11 to be asynchronous(pass through without delay)
    // Default setting is to have 2 SYS_CLK cycles delay
    //
    GPIO_setQualificationMode(8, GPIO_QUAL_ASYNC);
    GPIO_setQualificationMode(9, GPIO_QUAL_ASYNC);
    GPIO_setQualificationMode(10,GPIO_QUAL_ASYNC);
    GPIO_setQualificationMode(11,GPIO_QUAL_ASYNC);

    //
    // Configure SPI module for Rx operation
    //
    configureSPI();

    //
    // Assigning base addresses of Tx/Rx data buffer to globals
    //
    txBufAddr = (uint16_t *)FSI_getTxBufferAddress(FSITXA_BASE);
    rxBufAddr = (uint16_t *)spiFrameInfo.data;

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
    
    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Configure for data transfers
    //

    //
    // Setting for requested nWords and nLanes with transfers
    //
    FSI_setTxSoftwareFrameSize(FSITXA_BASE, nWords);

    //
    // Enable normal data transfer events to be sent over INT1 line
    //
    FSI_enableTxInterrupt(FSITXA_BASE, FSI_INT1, FSI_TX_EVT_FRAME_DONE);

    FSI_setTxFrameTag(FSITXA_BASE, txDataFrameTag);
    FSI_setTxUserDefinedData(FSITXA_BASE, txUserData);
    FSI_setTxFrameType(FSITXA_BASE, FSI_FRAME_TYPE_NWORD_DATA);

    //
    // Now, start sending data frames from FSI Tx and receive + verify at SPI
    // end. Come out of loop if there is any mismatch between transmit and
    // receive data.
    //
    while(1)
    {
        //
        // Write data into Tx buffer and set other Frame specific fields
        //
        prepareTxBufData();
        FSI_writeTxBuffer(FSITXA_BASE, txBufData, nWords, 0U);

        FSI_startTxTransmit(FSITXA_BASE);

        //
        // Wait for FSI Tx to finish transmit operation
        // Also, check that the Transmit frame done interrupt was the source
        //
        while(fsiTxInt1Received != 1U);
        fsiTxInt1Received = 0;
        compare16(txEventSts, FSI_TX_EVT_FRAME_DONE);

        idx = 0;

        //
        // Read the SPIRX buffer until empty
        // Then save the number of words received and decode the data frame
        //
        while(SPI_getRxFIFOStatus(SPIA_BASE)>0)
        {
            spiBuiltFrame.spiDataBuf[idx] = SPI_readDataBlockingFIFO(SPIA_BASE);
            idx++;
        }

        spiBuiltFrame.frameLen = idx;
        decodeFSIFrameReceivedinSPI(&spiFrameInfo,&spiBuiltFrame);

        //
        // Verify Frame attributes and data
        //
        compare16(spiFrameInfo.type, FSI_FRAME_TYPE_NWORD_DATA);
        compare16(spiFrameInfo.tag, txDataFrameTag);
        compare16(spiFrameInfo.userdata, txUserData);
        compareBufData(0U, 0U, spiFrameInfo.data_len);

        //
        // In case of comparison failures, break execution
        // Else, increment received data frame counter and reset FSI Tx buffer
        // for next transfer
        //
        if(error)
            break;

        dataFrameCntr++;
        FSI_setTxBufferPtr(FSITXA_BASE, 0U);
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
    dataFrameCntr++;

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
// checkReceivedFrameTypeTag - Decode the received FSI frame
//
void decodeFSIFrameReceivedinSPI(SPI_FSIFrameInfo *frameInfo,
                                 SPI_FSIBuiltFrame *txFrame)
{
    uint16_t temp = 0;
    uint16_t i = 0;
    uint16_t j = 0;
    uint16_t dataframe;
    uint16_t crc_val = 0;

    //
    // Maximum num of words considered - 16 + udata
    //
    uint16_t crc_tempArray[17];

    //
    // Get the frame type from first word and set the number of words in the
    // received frame, based on the frame type
    //
    temp = txFrame->spiDataBuf[i];
    frameInfo->type = (FSI_FrameType)((temp>>8) & 0x000F);

    switch (frameInfo->type)
    {
        case FSI_FRAME_TYPE_NWORD_DATA:
            frameInfo->data_len = txFrame->frameLen - 2;
            dataframe = 1;
            break;
        case FSI_FRAME_TYPE_1WORD_DATA:
            frameInfo->data_len = 1;
            dataframe = 1;
            break;
        case FSI_FRAME_TYPE_2WORD_DATA:
            frameInfo->data_len = 2;
            dataframe = 1;
            break;
        case FSI_FRAME_TYPE_4WORD_DATA:
            frameInfo->data_len = 4;
            dataframe = 1;
            break;
        case FSI_FRAME_TYPE_6WORD_DATA:
            frameInfo->data_len = 6;
            dataframe = 1;
            break;
        case FSI_FRAME_TYPE_ERROR:
        case FSI_FRAME_TYPE_PING:
            frameInfo->data_len = 0;
            frameInfo->userdata = 0;
            dataframe = 0;
            break;
        default:
            break;
    }

    //
    // For data frames, get it calculated CRC value.
    // Fetch userdata and data from frame and use SW CRC function to calculate
    // CRC value
    //
    if(dataframe)
    {
        frameInfo->userdata = ((uint16_t)txFrame->spiDataBuf[i] & 0x00FF);

        for(i = 1; i <= frameInfo->data_len; i++)
        {
            frameInfo->data[i-1] = txFrame->spiDataBuf[i];
        }

        //
        // Copy the data and userdata into another buffer for the crc calculation
        //
        crc_tempArray[0] = (frameInfo->userdata <<8) & 0xFF00;
        for(j = 1; j <= frameInfo->data_len; j++)
        {
            crc_tempArray[j] = txFrame->spiDataBuf[j-1];
        }

        crc_val = crc8((uint32_t)(&crc_tempArray[0]), frameInfo->data_len +1);
        frameInfo->crcbyte = crc_val & 0x000F;
    }

    //
    // Complete the frame decoding the tag
    // Drop the last 4 bits since its just the end of frame
    //
    frameInfo->tag = (FSI_FrameTag)((txFrame->spiDataBuf[i] >> 4) & 0x000F);
}

//
// configureSPI - Configure SPI for Rx remote operation
//
void configureSPI(void)
{
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_SPIA);

    SPI_disableModule(SPIA_BASE);

    //
    // SPI configuration. Use a 500kHz SPICLK and 16-bit word size.
    //
    SPI_setConfig(SPIA_BASE, DEVICE_LSPCLK_FREQ, SPI_PROT_POL0PHA0,
                  SPI_MODE_PERIPHERAL, 500000, 16);

    SPI_enableFIFO(SPIA_BASE);
    SPI_setEmulationMode(SPIA_BASE, SPI_EMULATION_STOP_AFTER_TRANSMIT);

    SPI_enableModule(SPIA_BASE);
}

//
// crc8 - This function calculates crc8 i.e.polynomial with highest degree 8
//        It returns 32 bit crc and assumes that, at each location data is
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
        asm(" VCRC8L_1 *XAR6 ");  //calculates crc on lower byte of 16 bit
        asm(" VCRC8H_1 *XAR6++ ");  //calculates crc on higher byte of 16 bit
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
