//#############################################################################
//
// FILE:   fsi_ex3_loopback_dmacontrol.c
//
// TITLE:  DMA controlled data frame transfers with internal loopback
//
//! \addtogroup driver_example_list
//! <h1>FSI DMA frame transfers:DMA Control</h1>
//!
//! Example sets up infinite data frame transfers where DMA trigger happens
//! once through CPU and then DMA takes control to transfer data iteratively.
//! This example demonstrates the FSI feature about triggering DMA events which
//! in turn can copy data and trigger next transfer.
//!
//! Two DMA channels are setup for FSI Tx operation and two for Rx.
//! Four areas in GSx memories are also setup as source and sink for data and
//! tag values of frame under transmission.
//!
//! Automatic(Hw triggered) Ping frame transmission is also setup along
//! with data.
//!
//! If there are any comparison failures during transfers or any error
//! event occurs, execution will stop.
//!
//! User Configurations:
//! If "Software Frame Size" is modified in FSI TX or FSI RX Sysconfig, change:
//! DMA CH0 "Destination Wrap Size"
//! DMA CH0 "Burst Size"
//! DMA CH2 "Source Wrap Size"
//! DMA CH2 "Burst Size"
//! FSI TX/RX "Software Frame Size"
//!
//!  \note: This example project has support for migration across our C2000 
//!  device families. If you are wanting to build this project from launchpad
//!  or controlCARD, please specify in the .syscfg file the board you're using.
//!  At any time you can select another device to migrate this example.
//!
//! \b External \b Connections \n
//!  For FSI internal loopback (default setting), no external
//!  connections needed
//!
//!  For FSI external loopback (disable "Loopback Mode" in FSI RX Sysconfig),
//!  external connections are required. Refer to SysConfig for external
//!  connections (GPIO pin numbers) specific to each device.
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
// Copyright (C) 2025 Texas Instruments Incorporated - http://www.ti.com/
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
#include "board.h"

//
// Defines
//
#define TOTAL_WORDS_IN_TRANSFER (myDMA0_TRANSFERSIZE * myFSIRX0_nWords)

//
// GSRAM data buffers
//
uint16_t gs0Data[0x800];
uint16_t gs1Data[0x800];
uint16_t gs2Data[0x800];
uint16_t gs3Data[0x800];

//
// FSI Tx/Rx Frame tag User Data register address, used by DMA channels to
// write (and trigger transfer) and read User data respectively
//
const void *txFrameTagAddr = (const void *)(myFSITX0_BASE +
                                            FSI_O_TX_FRAME_TAG_UDATA);
const void *rxFrameTagAddr = (const void *)(myFSIRX0_BASE +
                                            FSI_O_RX_FRAME_TAG_UDATA);

//
// Map the TX frame data buffer to DMA accessible global shared memory.
//
#pragma DATA_SECTION(gs0Data, "ramgs0");

//
// Map the TX data frame tag and User data buffer to DMA accessible global
// shared memory.
//
#pragma DATA_SECTION(gs1Data, "ramgs1");
//
// Map the RX frame data buffer to DMA accessible global shared memory.
//
#pragma DATA_SECTION(gs2Data, "ramgs2");
//
// Map the RX frame tag and User data buffer to DMA accessible global
// shared memory.
//
#pragma DATA_SECTION(gs3Data, "ramgs3");
//
// Set up pointers to GSRAM buffers
//
const void *gs0Addr = (const void *)gs0Data;
const void *gs1Addr = (const void *)gs1Data;
const void *gs2Addr = (const void *)gs2Data;
const void *gs3Addr = (const void *)gs3Data;

//
// Globals, User can modify these parameters as per use case
//

// Boolean flag to enable/disable Rx Frame Watchdog
// If changed to false: take out FSI_RX_EVT_FRAME_WD_TIMEOUT interrupt setting
// in FSIRX Sysconfig
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
const void *txBufAddr = 0, *rxBufAddr = 0;
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
__interrupt void fsitxdma_isr(void);
__interrupt void fsirxdma_isr(void);

//
// InitFrameTagAndData - Initializes GS0/GS1 memories to populate tag and data
//                       for frame transfers
//
void InitFrameTagAndData(void)
{
    unsigned int i;
    uint16_t *temp;

    temp = (uint16_t *)gs0Addr;
    for(i = 0; i < TOTAL_WORDS_IN_TRANSFER; i++)
    {
        *temp = i;
        temp++;
    }

    temp = (uint16_t *)gs1Addr;
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
    // Assigning base addresses of Tx/Rx data buffer to globals
    //
    txBufAddr = (const void *)(myFSITX0_BASE + FSI_O_TX_BUF_BASE(0));
    rxBufAddr = (const void *)(myFSIRX0_BASE + FSI_O_RX_BUF_BASE(0));

    //
    // Call Sysconfig configured code.
    //
    Board_init();

    //
    // Flush Sequence before and after releasing Rx core reset, ensures flushing
    // of Rx data/clock lines and prepares it for reception.
    //
    FSI_resetRxModule(myFSIRX0_BASE, FSI_RX_MAIN_CORE_RESET);
    FSI_executeTxFlushSequence(myFSITX0_BASE, myFSITX0_PRESCALER_VAL);
    DEVICE_DELAY_US(1);
    FSI_clearRxModuleReset(myFSIRX0_BASE, FSI_RX_MAIN_CORE_RESET);
    FSI_executeTxFlushSequence(myFSITX0_BASE, myFSITX0_PRESCALER_VAL);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM).
    //
    EINT;
    ERTM;

    if(isRxFrameWdEnable)
    {
        //
        // Performing a reset on frame WD before its usage is recommended.
        //
        FSI_resetRxModule(myFSIRX0_BASE, FSI_RX_FRAME_WD_CNT_RESET);
        DEVICE_DELAY_US(1);
        FSI_clearRxModuleReset(myFSIRX0_BASE, FSI_RX_FRAME_WD_CNT_RESET);
        FSI_enableRxFrameWatchdog(myFSIRX0_BASE, rxFrameWdRefCntr);
    }

    FSI_enableTxDMAEvent(myFSITX0_BASE);
    FSI_enableRxDMAEvent(myFSIRX0_BASE);

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
        // Starting location is after one word as extra write to marker
        // location will lead to 1st comparison fail.
        //
        txTempData16 = ((uint16_t *)gs0Addr) + 1;
        rxTempData16 = ((uint16_t *)gs2Addr) + 1;

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
        *((uint16_t *)gs0Addr) = (uint16_t )countDMAtransfers;
    }
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
