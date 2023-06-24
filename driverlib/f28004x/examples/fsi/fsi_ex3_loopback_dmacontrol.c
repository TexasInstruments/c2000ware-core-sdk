//#############################################################################
//
// FILE:   fsi_ex3_loopback_dmacontrol.c
//
// TITLE:  DMA controlled data frame transfers with internal loopback
//
//! \addtogroup driver_example_list
//! <h1>FSI DMA frame transfers:DMA Control</h1>
//!
//! Example sets up infinite data frame transfers where DMA trigger happens once
//! through CPU and then DMA takes control to transfer data iteratively. This
//! example demonstrates the FSI feature about triggering DMA events which in
//! turn can copy data and trigger next transfer.
//!
//! Two DMA channels are setup for FSI Tx operation and two for Rx.
//! Four areas in GSx memories are also setup as source and sink for data and
//! tag values of frame under transmission.
//!
//! Automatic(Hw triggered) Ping frame transmission is also setup along
//! with data.
//!
//! If there are any comparison failures during transfers or any of error
//! event occurs, execution will stop.
//!
//! \b External \b Connections \n
//!   For FSI internal loopback (EXTERNAL_FSI_ENABLE == 0), no external
//!     connections needed
//!
//!   For FSI external loopback (EXTERNAL_FSI_ENABLE == 1), external
//!   connections are required. The FSI TX pins should be connected to the
//!   respective FSI RX pins of the same device. See below for external
//!   connections to include and GPIOs used:
//!
//!  External Connections Required between FSI TX and RX of the same device:
//!  - FSIRX_CLK to FSITX_CLK
//!  - FSIRX_RX0 to FSITX_TX0
//!  - FSIRX_RX1 to FSITX_TX1
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
//!  - \b countDMAtransfers  Number of Data frame transfered
//!  - \b error              Non zero for transmit/receive data mismatch
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
// Defines: User can modify these values as desired
//
#define PRESCALER_VAL    FSI_PRESCALE_50MHZ

//
// Define to enable external FSI configuration
//
// 0 = internal loopback enabled
// 1 = internal loopback disabled, FSI GPIOs configured,
//      external connections required
//
#define EXTERNAL_FSI_ENABLE     0

#define DMA_TRANSFER_SIZE_IN_BURSTS 512U
#define TOTAL_WORDS_IN_TRANSFER (DMA_TRANSFER_SIZE_IN_BURSTS * nWords)

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
uint16_t nWords = 4;

// Transfer can be happen over single or double lane
FSI_DataWidth nLanes = FSI_DATA_WIDTH_1_LANE;

// FSI Clock used for transfer
uint32_t fsiClock = 50000000;

// Frame tag used with Data/Ping transfers
FSI_FrameTag txPingFrameTag = FSI_FRAME_TAG15;

// Tx Ping timer and Rx Watchdog reference counter values
uint32_t txPingTimeRefCntr = 0x1000000, rxWdTimeoutRefCntr = 0x1400000;

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
uint32_t error = 0;
uint32_t dmaIntr1 = 0, dmaIntr2 = 0;
uint32_t countDMAtransfers = 0U;
volatile uint16_t i = 0, *txTempData16 = 0, *rxTempData16 = 0;
uint32_t dmaTxIntCnt = 0, dmaRxIntCnt = 0; //TODO, may remove it, just for DEBUG

//
// Function Prototypes
//
static inline void compare16(uint16_t val1, uint16_t val2);
void initFSI(void);
__interrupt void fsitxdma_isr(void);
__interrupt void fsirxdma_isr(void);
void fsitx_dma_config();
void fsirx_dma_config();

//
// InitFrameTagAndData - Initializes GS0/GS1 memories to populate tag and data
//                       for frame transfers
//
void InitFrameTagAndData(void)
{
    unsigned int i;
    uint16_t *temp;

    temp = (uint16_t *)GS0_START_ADDR;
    for(i = 0; i < TOTAL_WORDS_IN_TRANSFER; i++)
    {
        *temp = (GS0_START_ADDR + i);
        temp++;
    }

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
    // found within this file.
    //
    Interrupt_register(INT_DMA_CH2, &fsitxdma_isr);
    Interrupt_register(INT_DMA_CH4, &fsirxdma_isr);

    //
    // Enable FSI Tx/Rx interrupts
    //
    Interrupt_enable(INT_DMA_CH2);
    Interrupt_enable(INT_DMA_CH4);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Initialize basic settings for FSI
    //
    initFSI();

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
    // Enable transmit/receive error events to be sent over INT2 line
    // Overrun and Underrun conditions in Rx are not enabled as buffer pointers
    // are always overwritten to first location for sending data frames.
    //
    FSI_enableRxInterrupt(FSIRXA_BASE, FSI_INT2, FSI_RX_EVT_CRC_ERR  |
                                                 FSI_RX_EVT_EOF_ERR  |
                                                 FSI_RX_EVT_TYPE_ERR);

    //
    // Automatic Ping transmission is setup, now configure for data transfers
    //

    //
    // Initialize the dma channels for both tx and rx buffers
    //
    DMA_initController();

    fsirx_dma_config();
    fsitx_dma_config();

    FSI_setTxFrameType(FSITXA_BASE, FSI_FRAME_TYPE_NWORD_DATA);
    //
    // Setting for requested nWords and nLanes with transfers
    //
    FSI_setTxSoftwareFrameSize(FSITXA_BASE, nWords);
    FSI_setRxSoftwareFrameSize(FSIRXA_BASE, nWords);
    FSI_setTxDataWidth(FSITXA_BASE, nLanes);
    FSI_setRxDataWidth(FSIRXA_BASE, nLanes);

    //
    // Enable DMA event on both FSI Tx/Rx and
    FSI_setTxStartMode(FSITXA_BASE, FSI_TX_START_FRAME_CTRL_OR_UDATA_TAG);
    FSI_enableTxDMAEvent(FSITXA_BASE);
    FSI_enableRxDMAEvent(FSIRXA_BASE);

    InitFrameTagAndData();

    //
    // Start RX channels
    //
    DMA_startChannel(DMA_CH3_BASE);
    DMA_startChannel(DMA_CH4_BASE);

    DMA_startChannel(DMA_CH1_BASE);
    DMA_forceTrigger(DMA_CH1_BASE);
    DMA_startChannel(DMA_CH2_BASE);
    DMA_forceTrigger(DMA_CH2_BASE);

    while(1)
    {
        //
        // Wait for both TX and RX channels to complete a transfer
        //
        while(dmaIntr1 == 0U);
        dmaIntr1 = 0;

        while(dmaIntr2 == 0U);
        dmaIntr2 = 0;

        //
        // Starting location is after one word as extra write to marker location
        // will lead to 1st comparison fail
        //
        txTempData16 = (uint16_t *)(GS0_START_ADDR + 1);
        rxTempData16 = (uint16_t *)(GS2_START_ADDR + 1);

        //
        // verify transfers
        //
        for(i = 1; i < TOTAL_WORDS_IN_TRANSFER; i++)
        {
            compare16(*txTempData16,*rxTempData16);
            txTempData16++;
            rxTempData16++;
        }

        countDMAtransfers++;
        //
        // Just changing the 1st entry in Tx buffer Source GS0 location as a
        // marker for observing change in received data in memory view of
        // debugger with each transfer
        //
        *(uint16_t *)GS0_START_ADDR = (uint16_t )countDMAtransfers;
    }
}

//
// initFSI - Initializes FSI Tx/Rx with internal loopback and also sends FLUSH
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
// fsitx_dma_config - Sets up DMA channels(Ch1 and Ch2) for FSI Tx operation
//
void fsitx_dma_config()
{
    //
    // For the data buffers
    //
    DMA_configAddresses(DMA_CH1_BASE, txBufAddr, (uint16_t *)GS0_START_ADDR);
    DMA_configBurst(DMA_CH1_BASE, nWords, 1, 1);
    DMA_configTransfer(DMA_CH1_BASE, DMA_TRANSFER_SIZE_IN_BURSTS, 1, 1);
    DMA_configWrap(DMA_CH1_BASE, DMA_TRANSFER_SIZE_IN_BURSTS, 0, nWords, 0);
    DMA_configMode(DMA_CH1_BASE, DMA_TRIGGER_FSITXA, DMA_CFG_ONESHOT_DISABLE|
                   DMA_CFG_CONTINUOUS_ENABLE | DMA_CFG_SIZE_16BIT);

    DMA_disableInterrupt(DMA_CH1_BASE);
    DMA_enableTrigger(DMA_CH1_BASE);

    //
    // For the tag and userdata fields
    //
    DMA_configAddresses(DMA_CH2_BASE, (uint16_t *)FSI_TX_FRAME_TAG_UDATA_REGADDR,
                        (uint16_t *)GS1_START_ADDR);
    DMA_configBurst(DMA_CH2_BASE, 0, 0, 0);
    DMA_configTransfer(DMA_CH2_BASE, DMA_TRANSFER_SIZE_IN_BURSTS, 1, 0);
    DMA_configWrap(DMA_CH2_BASE, 16, 0, 16, 0);
    DMA_configMode(DMA_CH2_BASE, DMA_TRIGGER_FSITXA, DMA_CFG_ONESHOT_DISABLE|
                   DMA_CFG_CONTINUOUS_ENABLE|DMA_CFG_SIZE_16BIT);

    DMA_setInterruptMode(DMA_CH2_BASE, DMA_INT_AT_END);
    DMA_enableInterrupt(DMA_CH2_BASE);
    DMA_enableTrigger(DMA_CH2_BASE);
}

//
// fsirx_dma_config - Sets up DMA channels(Ch3 and Ch4) for FSI Rx operation
//
void fsirx_dma_config()
{
    DMA_configAddresses(DMA_CH3_BASE, (uint16_t *)GS2_START_ADDR, rxBufAddr);
    DMA_configBurst(DMA_CH3_BASE, nWords, 1, 1);
    DMA_configTransfer(DMA_CH3_BASE, DMA_TRANSFER_SIZE_IN_BURSTS, 1, 1);
    DMA_configWrap(DMA_CH3_BASE, nWords, 0, DMA_TRANSFER_SIZE_IN_BURSTS, 0);
    DMA_configMode(DMA_CH3_BASE, DMA_TRIGGER_FSIRXA, DMA_CFG_ONESHOT_DISABLE|
                   DMA_CFG_CONTINUOUS_ENABLE|DMA_CFG_SIZE_16BIT);

    DMA_disableInterrupt(DMA_CH3_BASE);
    DMA_enableTrigger(DMA_CH3_BASE);

    //
    // For the tag and userdata fields
    //
    DMA_configAddresses(DMA_CH4_BASE,(uint16_t *)GS3_START_ADDR,
                        (uint16_t *)FSI_RX_FRAME_TAG_UDATA_REGADDR);
    DMA_configBurst(DMA_CH4_BASE, 0, 0, 0);
    DMA_configTransfer(DMA_CH4_BASE, DMA_TRANSFER_SIZE_IN_BURSTS, 0, 1);
    DMA_configWrap(DMA_CH4_BASE, 16, 0, 16, 0);
    DMA_configMode(DMA_CH4_BASE, DMA_TRIGGER_FSIRXA, DMA_CFG_ONESHOT_DISABLE |
                   DMA_CFG_CONTINUOUS_ENABLE | DMA_CFG_SIZE_16BIT);

    DMA_setInterruptMode(DMA_CH4_BASE, DMA_INT_AT_END);
    DMA_enableInterrupt(DMA_CH4_BASE);
    DMA_enableTrigger(DMA_CH4_BASE);
}

//
// fsitxdma_isr - FSI Tx DMA ISR
//
interrupt void fsitxdma_isr(void)
{
    dmaIntr1 = 1;
    dmaTxIntCnt++;
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP7);
}

//
// fsirxdma_isr - FSI Rx DMA ISR
//
interrupt void fsirxdma_isr(void)
{
    dmaIntr2 = 1;
    dmaRxIntCnt++;
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP7);
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
// End of File
//
