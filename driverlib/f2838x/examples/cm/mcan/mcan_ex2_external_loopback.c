//#############################################################################
//
// FILE:   mcan_ex2_external_loopback.c
//
// TITLE:  MCAN External Loopback with Interrupt
//
//! \addtogroup driver_example_cm_list
//! <h1> MCAN External Loopback with Interrupt </h1>
//!
//! This example shows the MCAN External Loopback functionality. The external
//! loopback is done between two MCAN Controllers. As there is only one MCAN
//! that exist this example can be changed to make MCAN Transmit or Receive
//! based on define selected. The GPIOs of MCAN should be connected to a CAN
//! Transceiver
//! 
//! Before running this example, please run the mcan_config_c28x example
//! It will initialize the clock, configure the GPIOs.
//!
//! Selection of Mode : A define has to be selected to make the MCAN to
//! transmit or receive.
//!  - TRANSMIT - MCAN to Transmit messages.
//!  - RECEIVE  - MCAN to Receive Messages.
//!
//! Run the example as with RECEIVE Define on one MCAN Controller before
//! running it as Transmit.  
//!
//! \b Hardware \b Required \n
//!  - A C2000 board with CAN transceiver
//!
//! \b External \b Connections \n
//!  - MCAN is on GPIO30 (MCANRXA) and GPIO31 (MCANTXA)
//!
//! \b Watch \b Variables \n
//!  - isrIntr0Flag - The flag has initial value as no. of messages to be
//!                   transmitted and its value decrements after a message is
//!                   transmitted. 
//!  - isrIntr1Flag - The flag has initial value as no. of messages that are
//!                   received and its value decrements after a message is
//!                   successfully received.
//!  - error - Checks if there is an error that occurred when the data was
//!            sent using internal loopback
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
// Include Files
//
#include "cm.h"
#include "inc/stw_types.h"
#include "inc/stw_dataTypes.h"

//
// Select one of the Modes.
//
#define TRANSMIT
//#define RECEIVE

//
// Defines.
//
#define NUM_OF_MSG                    (10U)
#define MCAN_STD_ID_FILT_START_ADDR   (0U)
#define MCAN_STD_ID_FILTER_NUM        (1U)
#define MCAN_EXT_ID_FILT_START_ADDR   (48U)
#define MCAN_EXT_ID_FILTER_NUM        (1U)
#define MCAN_TX_EVENT_START_ADDR      (100U)
#define MCAN_TX_EVENT_SIZE            (NUM_OF_MSG)
#define MCAN_TX_EVENT_WATERMARK       (NUM_OF_MSG/2)
#define MCAN_TX_BUFF_START_ADDR       (148U)
#define MCAN_TX_BUFF_SIZE             (NUM_OF_MSG)
#define MCAN_TX_FIFO_SIZE             (NUM_OF_MSG)
#define MCAN_FIFO_0_START_ADDR        (548U)
#define MCAN_FIFO_0_NUM               (NUM_OF_MSG)
#define MCAN_FIFO_0_WATERMARK         (NUM_OF_MSG)
#define MCAN_FIFO_1_START_ADDR        (748U)
#define MCAN_FIFO_1_NUM               (NUM_OF_MSG)
#define MCAN_FIFO_1_WATERMARK         (NUM_OF_MSG)
#define MCAN_RX_BUFF_START_ADDR       (948U)
#define MCAN_EXT_ID_AND_MASK          (0x1FFFFFFFU)
#define MCAN_TS_PRESCALAR             (0xB0)

#define MCAN_TX_BUFF_ELEM_SIZE       (MCAN_ELEM_SIZE_64Bytes)
#define MCAN_RX_BUFF_ELEM_SIZE       (MCAN_ELEM_SIZE_64Bytes)
#define MCAN_RX_FIFO0_ELEM_SIZE      (MCAN_ELEM_SIZE_64Bytes)
#define MCAN_RX_FIFO1_ELEM_SIZE      (MCAN_ELEM_SIZE_64Bytes)

//
// Global Variables.
//
volatile uint32_t isrIntr0Flag = NUM_OF_MSG;
volatile uint32_t isrIntr1Flag = NUM_OF_MSG;
volatile uint32_t isrIntrTSFlag = 1U;
int32_t     error = 0;
MCAN_TxBufElement txMsg[NUM_OF_MSG];
MCAN_RxBufElement rxMsg[NUM_OF_MSG], rxMsg1;
int32_t loopCnt = 0U;


//
// Function Prototype.
//
static void MCANConfig(void);
static void MCANIntrConfig(void);
static void MCANIntr0ISR(void);
static void MCANIntr1ISR(void);

void main()
{
#ifdef RECEIVE
    int32_t dataCnt;
#endif
    int i = 0;
    uint32_t numOfMsg = NUM_OF_MSG;
    volatile uint32_t mode = 0U;
    uint32_t dataBytes = 8;
    
    //
    // Switching on the peripheral.
    //
    CM_init();

    //
    // Reset the peripheral.
    //
    SysCtl_resetPeripheral(SYSCTL_PERIPH_RES_MCAN_A);

    //
    // CrossBar and ISR Configuration.
    //
    MCANIntrConfig();
    
    //
    // Initialize message to transmit.
    //
    for(loopCnt = 0U ; loopCnt < numOfMsg ; loopCnt++)
    {
        txMsg[loopCnt].id       = (0x0);
        txMsg[loopCnt].id       = (loopCnt) << 16U;
        txMsg[loopCnt].id       |= (0xFF);
        txMsg[loopCnt].rtr      = 0U;
        txMsg[loopCnt].xtd      = 1U;
        txMsg[loopCnt].esi      = 0U;
        txMsg[loopCnt].dlc      = 15U;
        txMsg[loopCnt].brs      = 0U;
        txMsg[loopCnt].fdf      = 1U;
        txMsg[loopCnt].efc      = 1U;
        txMsg[loopCnt].mm       = 0xAAU;
        txMsg[loopCnt].data[i]  = 0x1;
        for(i = 1; i < dataBytes; i++)
        {
            txMsg[loopCnt].data[i]  = txMsg[loopCnt].data[i-1] + 1;
        }
        i = 0;
    }
    for(loopCnt = 0U ; loopCnt < numOfMsg ; loopCnt++)
    {
        rxMsg[loopCnt].id = 0U;
        rxMsg[loopCnt].rtr = 0U;
        rxMsg[loopCnt].xtd = 0U;
        rxMsg[loopCnt].esi = 0U;
        rxMsg[loopCnt].rxts = 0U;
        rxMsg[loopCnt].dlc = 0U;
        rxMsg[loopCnt].brs = 0U;
        rxMsg[loopCnt].fdf = 0U;
        rxMsg[loopCnt].fidx = 0U;
        rxMsg[loopCnt].anmf = 0U;
        for(i = 0; i < dataBytes; i++)
        {
            rxMsg[loopCnt].data[i]  = 0;
        }
    }

    //
    // Configure the MCAN Module.
    //
    MCANConfig();
    
#ifdef TRANSMIT
    //
    // This is transmitter side application.
    //
     
    // 
    // Enable Interrupts.
    //
    MCAN_enableIntr(MCAN0_BASE, MCAN_INTR_MASK_ALL,1);
    MCAN_enableIntr(MCAN0_BASE, MCAN_INTR_SRC_RES_ADDR_ACCESS|
                    MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND,0);
    
    //
    // Select Interrupt Line.
    //
    MCAN_selectIntrLine(MCAN0_BASE, MCAN_INTR_MASK_ALL,
                        MCAN_INTR_LINE_NUM_0);
    
    //
    // Enable Interrupt Line.
    //
    MCAN_enableIntrLine(MCAN0_BASE, MCAN_INTR_LINE_NUM_0, 1U);
    
    //
    // Enable Transmission interrupt.
    //
    for(loopCnt = 0U ; loopCnt < numOfMsg ; loopCnt++)
    {
        MCAN_txBufTransIntrEnable(MCAN0_BASE, loopCnt,1);
    
        //
        // Write message to Message RAM.
        //
        MCAN_writeMsgRam(MCAN0_BASE, MCAN_MEM_TYPE_BUF, loopCnt,
                         &txMsg[loopCnt]);
    }
    
    //
    // Add request for all transmission.
    //
    HWREG(MCAN0_BASE + MCAN_TXBAR) = 0x000003FF;
                
    //
    // Wait till the flag becomes zero and all the messages are transmitted.
    //
    while(isrIntr0Flag)
    {
    }
#endif
#ifdef RECEIVE
    //
    // This is receiver side application.
    // 

    //
    // Enable Interrupts.
    //
    MCAN_enableIntr(MCAN0_BASE, MCAN_INTR_MASK_ALL,1);
    MCAN_enableIntr(MCAN0_BASE, MCAN_INTR_SRC_RES_ADDR_ACCESS|
                    MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND,0);
    
    //
    // Select Interrupt Line.
    //
    MCAN_selectIntrLine(MCAN0_BASE, MCAN_INTR_MASK_ALL,
                        MCAN_INTR_LINE_NUM_1);
    //
    // Enable Interrupt Line.
    //
    MCAN_enableIntrLine(MCAN0_BASE, MCAN_INTR_LINE_NUM_1, 1U);
    
    //
    // Wait till the interrupt flag becomes zero.
    //
    while(isrIntr1Flag)
    {
    }

    for(loopCnt = 0U ; loopCnt < numOfMsg;loopCnt++)
    {
        MCAN_readMsgRam(MCAN0_BASE, MCAN_MEM_TYPE_FIFO, 0U,
                        MCAN_RX_FIFO_NUM_1, &rxMsg1);
        MCAN_writeRxFIFOAck(MCAN0_BASE, MCAN_RX_FIFO_NUM_1,
                            loopCnt);
        rxMsg[loopCnt] = rxMsg1;
    }
                
    for(loopCnt = 0U ; loopCnt < numOfMsg ; loopCnt++)
    {

        if (rxMsg[loopCnt].id  != txMsg[loopCnt].id)
        {
            error++;
        }
        if (rxMsg[loopCnt].rtr != txMsg[loopCnt].rtr)
        {
            error++;
        }
        if (rxMsg[loopCnt].xtd != txMsg[loopCnt].xtd)
        {
            error++;
        }
        if (rxMsg[loopCnt].esi != txMsg[loopCnt].esi)
        {
            error++;
        }
        if (rxMsg[loopCnt].dlc != txMsg[loopCnt].dlc)
        {
            error++;
        }
        if (rxMsg[loopCnt].brs != txMsg[loopCnt].brs)
        {
            error++;
        }
        if (rxMsg[loopCnt].fdf != txMsg[loopCnt].fdf)
        {
            error++;
        }
        
        if (loopCnt > 0)
        {
            if (rxMsg[loopCnt].rxts > rxMsg[loopCnt-1].rxts)
            {
            }
            else
            {
                error++;
            }
        }

        for (dataCnt = 0U ; dataCnt < dataBytes ; dataCnt++)
        {
            if (rxMsg[loopCnt].data[dataCnt]!=
                txMsg[loopCnt].data[dataCnt])
            {
                error++;
            }
        }
    }
#endif
    if (error != 0)
    {
        //
        // Stop if there is an error.
        //
        __asm("   bkpt #0");
    }
    
    //
    // Stop Application.
    //
    __asm("   bkpt #0");
}

static void MCANIntrConfig(void)
{
    Interrupt_registerHandler(INT_MCANSS_0,&MCANIntr0ISR);
    Interrupt_enable(INT_MCANSS_0);
    Interrupt_registerHandler(INT_MCANSS_1,&MCANIntr1ISR);
    Interrupt_enable(INT_MCANSS_1);
    Interrupt_enableInProcessor();
}
static void MCANConfig(void)
{
    MCAN_RevisionId revId;
    MCAN_InitParams initParams;
    MCAN_ConfigParams configParams;
    MCAN_MsgRAMConfigParams    msgRAMConfigParams;
    MCAN_StdMsgIDFilterElement stdFiltelem;
    MCAN_ExtMsgIDFilterElement extFiltelem;
    MCAN_BitTimingParams       bitTimes;

    //
    // Initialize MCAN Init parameters.
    //
    initParams.fdMode            = 0x1U; // FD operation disabled.
    initParams.brsEnable         = 0x1U; // Bit rate switching for
                                         // transmissions enabled.
    initParams.txpEnable         = 0x1U; // Transmit pause enabled.
    initParams.efbi              = 0x0U; // Edge filtering disabled.
    initParams.pxhddisable       = 0x0U; // Protocol exception handling enabled.
    initParams.darEnable         = 0x1U; // Enable automatic retransmission of messages
                                         // that were not transmitted successfully.
    initParams.wkupReqEnable     = 0x1U; // Wakeup request is enabled.
    initParams.autoWkupEnable    = 0x1U; // Auto-Wakeup is enabled.
    initParams.emulationEnable   = 0x1U; // Emulation/Debug Suspend is enabled.
    initParams.tdcEnable         = 0x1U; // Transmitter Delay Compensation is
                                         // enabled.
    initParams.wdcPreload        = 0xFFU; // Start value of the Message RAM
                                          // Watchdog Counter preload.
 
    //
    // Transmitter Delay Compensation parameters.
    //
    initParams.tdcConfig.tdcf    = 0xAU;
    initParams.tdcConfig.tdco    = 0x6U;
    
    //
    // Initialize MCAN Config parameters.
    // 
    configParams.monEnable       = 0x0U; // Bus Monitoring Mode is disabled.
    configParams.asmEnable       = 0x0U; // Normal CAN operation.
    configParams.tsPrescalar       = 0x2U; // Prescaler Value.
    configParams.tsSelect          = 0x2U; // Timestamp counter value.
    configParams.timeoutSelect     = MCAN_TIMEOUT_SELECT_CONT;
    // Time-out counter source select.
    configParams.timeoutPreload    = 0xFFFFU;// Start value of the Timeout
                                             // Counter.
    configParams.timeoutCntEnable  = 0x0U; // Time-out Counter is disabled.
    configParams.filterConfig.rrfs = 0x1U; // Reject all remote frames with
                                           // 29-bit extended IDs.
    configParams.filterConfig.rrfe = 0x1U; // Reject all remote frames with
                                           // 11-bit standard IDs.
    configParams.filterConfig.anfe = 0x1U; // Accept in Rx FIFO 1.
    configParams.filterConfig.anfs = 0x1U; // Accept in Rx FIFO 1.

    //
    // Initialize Message RAM Sections Configuration Parameters
    //
    msgRAMConfigParams.flssa                = MCAN_STD_ID_FILT_START_ADDR;
    // Standard ID Filter List Start Address.
    msgRAMConfigParams.lss                  = MCAN_STD_ID_FILTER_NUM;
    // List Size: Standard ID.
    msgRAMConfigParams.flesa                = MCAN_EXT_ID_FILT_START_ADDR;
    // Extended ID Filter List Start Address.
    msgRAMConfigParams.lse                  = MCAN_EXT_ID_FILTER_NUM;
    // List Size: Extended ID.
    msgRAMConfigParams.txStartAddr          = MCAN_TX_BUFF_START_ADDR;
    // Tx Buffers Start Address.
    msgRAMConfigParams.txBufNum             = MCAN_TX_BUFF_SIZE;
    // Number of Dedicated Transmit Buffers.
    msgRAMConfigParams.txFIFOSize           = MCAN_TX_FIFO_SIZE;
    // Tx FIFO/Queue.
    msgRAMConfigParams.txBufMode            = 0U;
    msgRAMConfigParams.txBufElemSize        = MCAN_ELEM_SIZE_64BYTES;
  // Tx Buffer Element Size.
    msgRAMConfigParams.txEventFIFOStartAddr = MCAN_TX_EVENT_START_ADDR;
    // Tx Event FIFO Start Address.
    msgRAMConfigParams.txEventFIFOSize      = MCAN_TX_BUFF_SIZE;
    // Event FIFO Size.
    msgRAMConfigParams.txEventFIFOWaterMark = MCAN_TX_EVENT_WATERMARK;
    // Level for Tx Event FIFO watermark interrupt.
    msgRAMConfigParams.rxFIFO0startAddr     = MCAN_FIFO_0_START_ADDR;
    // Rx FIFO0 Start Address.
    msgRAMConfigParams.rxFIFO0size          = MCAN_FIFO_0_NUM;
    // Number of Rx FIFO elements.
    msgRAMConfigParams.rxFIFO0waterMark     = MCAN_FIFO_0_WATERMARK;
    msgRAMConfigParams.rxFIFO0OpMode        = 0U;
    msgRAMConfigParams.rxFIFO1startAddr     = MCAN_FIFO_1_START_ADDR;
    // Rx FIFO1 Start Address.
    msgRAMConfigParams.rxFIFO1size          = MCAN_FIFO_1_NUM;
    // Number of Rx FIFO elements.
    msgRAMConfigParams.rxFIFO1waterMark     = MCAN_FIFO_1_WATERMARK;
    // Level for Rx FIFO 1 watermark interrupt.
    msgRAMConfigParams.rxFIFO1OpMode        = 0U; // FIFO blocking mode.
    msgRAMConfigParams.rxBufStartAddr       = MCAN_RX_BUFF_START_ADDR;
    // Rx Buffer Start Address.
    msgRAMConfigParams.rxBufElemSize        = MCAN_ELEM_SIZE_64BYTES;
    // Rx Buffer Element Size.
    msgRAMConfigParams.rxFIFO0ElemSize      = MCAN_ELEM_SIZE_64BYTES;
    // Rx FIFO0 Element Size.
    msgRAMConfigParams.rxFIFO1ElemSize      = MCAN_ELEM_SIZE_64BYTES;
    // Rx FIFO1 Element Size.
    
    //
    // Initialize Tx Buffer Configuration parameters.
    //
    stdFiltelem.sfid2              = 0x0U; // Standard Filter ID 2.
    stdFiltelem.sfid1              = 0x4U; // Standard Filter ID 1.
    stdFiltelem.sfec               = 0x7U; // Store into Rx Buffer or as
                           // debug message, configuration of SFT[1:0] ignored.
    stdFiltelem.sft                = 0x0U; // Range filter from SFID1 to SFID2.
    
    //
    // Initialize Tx Buffer Configuration parameters.
    //
    extFiltelem.efid2  = (0x9U << 16U);
    extFiltelem.efid2 |= 0xFFU;
    extFiltelem.efid1  = (0x0U << 16U);
    extFiltelem.efid1 |= 0xFFU;
    extFiltelem.efec   = 0x6U;
    extFiltelem.eft    = 0x0U;

    //
    // Initialize bit timings.
    //
    bitTimes.nomRatePrescalar   = 0x1FU; // Nominal Baud Rate Pre-scaler.
    bitTimes.nomTimeSeg1        = 0x1U; // Nominal Time segment before sample point.
    bitTimes.nomTimeSeg2        = 0x1U; // Nominal Time segment after sample point.
    bitTimes.nomSynchJumpWidth  = 0x0U; // Nominal (Re)Synchronization Jump Width Range.
    bitTimes.dataRatePrescalar  = 0x3U; // Data Baud Rate Pre-scaler.
    bitTimes.dataTimeSeg1       = 0x1U; // Data Time segment before sample point.
    bitTimes.dataTimeSeg2       = 0x1U; // Data Time segment after sample point.
    bitTimes.dataSynchJumpWidth = 0x0U; // Data (Re)Synchronization Jump Width.

    //
    // Get MCANSS Revision ID
    //
    MCAN_getRevisionId(MCAN0_BASE, &revId);
    
    //
    // Wait for memory initialization to happen.
    //
    while(FALSE == MCAN_isMemInitDone(MCAN0_BASE))
    {
    }
    
    //
    // Put MCAN in SW initialization mode.
    //
    MCAN_setOpMode(MCAN0_BASE, MCAN_OPERATION_MODE_SW_INIT);
    
    //
    // Wait till MCAN is not initialized.
    //
    while (MCAN_OPERATION_MODE_SW_INIT != MCAN_getOpMode(MCAN0_BASE))
    {}
   
    //
    // Initialize MCAN module.
    //
    MCAN_init(MCAN0_BASE, &initParams);
    
    //
    // Configure MCAN module.
    //
    MCAN_config(MCAN0_BASE, &configParams);
 
    //
    // Disable external timeStamp overflow interrupt.
    //
    MCAN_extTSEnableIntr(MCAN0_BASE,1);

    //
    // Configure TimeStamp Counter.
    //
    MCAN_extTSCounterConfig(MCAN0_BASE, MCAN_TS_PRESCALAR);

    //
    // Configure Bit timings.
    //
    MCAN_setBitTime(MCAN0_BASE, &bitTimes);
    
    //
    // Set Extended ID Mask.
    //
    MCAN_setExtIDAndMask(MCAN0_BASE, MCAN_EXT_ID_AND_MASK);
    
    //
    // Configure Message RAM Sections
    //
    MCAN_msgRAMConfig(MCAN0_BASE, &msgRAMConfigParams);
    
    //
    // Configure Standard ID filter element
    //
    MCAN_addStdMsgIDFilter(MCAN0_BASE, 0U, &stdFiltelem);
    
    //
    // Configure Extended ID filter element
    //
    MCAN_addExtMsgIDFilter(MCAN0_BASE, 0U, &extFiltelem);

    //
    // Enable external counter.
    //
    MCAN_extTSCounterEnable(MCAN0_BASE, 1U);

    //
    // Take MCAN out of the SW initialization mode
    //
    MCAN_setOpMode(MCAN0_BASE, MCAN_OPERATION_MODE_NORMAL);
    
    while (MCAN_OPERATION_MODE_NORMAL != MCAN_getOpMode(MCAN0_BASE))
    {
        
    }
}

static void MCANIntr0ISR(void)
{
    uint32_t intrStatus;

    intrStatus = MCAN_getIntrStatus(MCAN0_BASE);
    MCAN_clearIntrStatus(MCAN0_BASE, intrStatus);
    
    if (MCAN_INTR_SRC_TRANS_COMPLETE == (intrStatus &
         MCAN_INTR_SRC_TRANS_COMPLETE))
    {
        //
        // Decrement the flag after each message is transmitted.
        //
        isrIntr0Flag--;
    }
    else
    {
        //
        // Stop the application if error occurs.
        //
        __asm("   bkpt #0");
    }

}

static void MCANIntr1ISR(void)
{
    uint32_t intrStatus;

    intrStatus = MCAN_getIntrStatus(MCAN0_BASE);
    MCAN_clearIntrStatus(MCAN0_BASE, intrStatus);
    if(MCAN_INTR_SRC_RX_FIFO1_NEW_MSG ==
            (intrStatus & MCAN_INTR_SRC_RX_FIFO1_NEW_MSG))
    {
        //
        // Decrement the flag after each message is received.
        //
        isrIntr1Flag--;
    }
    else
    {
        //
        // Stop the application if error occurs.
        //
        __asm("   bkpt #0");
    }
}
