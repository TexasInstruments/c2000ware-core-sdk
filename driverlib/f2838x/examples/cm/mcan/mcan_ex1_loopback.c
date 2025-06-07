//#############################################################################
//
// FILE:   mcan_ex1_loopback.c
//
// TITLE:   MCAN Loopback with Interrupts Example
//
//! \addtogroup driver_example_cm_list
//! <h1> MCAN Internal Loopback with Interrupt </h1>
//!
//! This example demonstrates Loopback functionality of the MCAN (CAN FD) module.
//! The internal loopback mode is chosen. The transmitted message will be received
//! by the node. All action is internal to the device, hence transmission will not be
//! visible on the MCAN_TX pin. Uses the last address of memory for Rx buffer.
//!
//! Before running this example, please run the mcan_config_c28x example
//! It will initialize the clock, configure the GPIOs.
//!
//! \b External \b Connections \n
//!  - None.
//!
//! \b Watch \b Variables \n
//!  - error - Checks if there is an error that occurred when the data was
//!            sent using internal loopback.
//!
//
//#############################################################################
//
//
// 
// C2000Ware v5.05.00.00
//
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
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
#include "inc/stw_dataTypes.h"
#include "inc/stw_types.h"

//
// Defines
//
#define MCAN_STD_ID_FILT_START_ADDR     (0x0U)
#define MCAN_STD_ID_FILTER_NUM          (1U)
#define MCAN_EXT_ID_FILT_START_ADDR     (0x14U)
#define MCAN_EXT_ID_FILTER_NUM          (1U)
#define MCAN_TX_BUFF_START_ADDR         (0x80U)
#define MCAN_TX_BUFF_SIZE               (10U)
#define MCAN_FIFO_1_START_ADDR          (0xc0U)
#define MCAN_FIFO_1_NUM                 (10U)
#define MCAN_TX_EVENT_START_ADDR        (0x100U)
#define MCAN_TX_EVENT_SIZE              (10U)
#define MCAN_EXT_ID_AND_MASK            (0x1FFFFFFFU)
#define MCAN_RX_BUFF_START_ADDR         (948U)
#define MCAN_FIFO_0_START_ADDR          (548U)
#define MCAN_FIFO_0_NUM                 (5U)
#define MCAN_MSG_INT                    (0x81200)

//
// Global Variables.
//
volatile uint32_t isrIntr0Flag = 1U;
volatile uint32_t isrIntr1Flag = 1U;
volatile uint16_t monEn = 0x0;
volatile unsigned long msgCount = 0;
volatile unsigned long error = 0;

//
// Function Prototype.
//
static void MCANConfig(void);
static void MCANIntrConfig(void);
static void MCANIntr0ISR(void);
static void MCANIntr1ISR(void);

//
// Main
//
void main(void)
{
    volatile uint32_t mode = 0U;
    MCAN_TxBufElement    txMsg;
    MCAN_RxBufElement    rxMsg;
    MCAN_RxNewDataStatus newData;

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
    txMsg.id       = ((uint32_t)(0x4)) << 18U; // Identifier Value.
    txMsg.rtr      = 0U; // Transmit data frame.
    txMsg.xtd      = 0U; // 11-bit standard identifier.
    txMsg.esi      = 0U; // ESI bit in CAN FD format depends only on error
                         // passive flag.
    txMsg.dlc      = 4U; // CAN + CAN FD: transmit frame has 0-8 data bytes.
    txMsg.brs      = 1U; // CAN FD frames transmitted with bit rate
                         // switching.
    txMsg.fdf      = 1U; // Frame transmitted in CAN FD format.
    txMsg.efc      = 1U; // Store Tx events.
    txMsg.mm       = 0xAAU; // Message Marker.

    //
    // Data bytes.
    //
    txMsg.data[0]  = 0x12;
    txMsg.data[1]  = 0x34;
    txMsg.data[2]  = 0x56;
    txMsg.data[3]  = 0x78;

    //
    // Configure MCAN.
    //
    MCANConfig();

    //
    // Enable Interrupts.
    //
    MCAN_enableIntr(MCAN0_BASE, MCAN_INTR_MASK_ALL, 1U);

    //
    // Select Interrupt Line.
    //
    MCAN_selectIntrLine(MCAN0_BASE, MCAN_INTR_MASK_ALL, MCAN_INTR_LINE_NUM_1);

    //
    // Enable Interrupt Line.
    //
    MCAN_enableIntrLine(MCAN0_BASE, MCAN_INTR_LINE_NUM_1, 1U);

    //
    // Write Tx Message to the Message RAM.
    //
    MCAN_writeMsgRam(MCAN0_BASE, MCAN_MEM_TYPE_BUF, 1U, &txMsg);

    //
    // Enable Transmission interrupt.
    //
    MCAN_txBufTransIntrEnable(MCAN0_BASE, 1U,1U);

    //
    // Add request for transmission.
    //
    MCAN_txBufAddReq(MCAN0_BASE, 1U);

    //
    // Wait for the isrIntr1Flag to be reset.
    //
    while(isrIntr1Flag)
    {
    }

    //
    // Read Message RAM.
    //
    MCAN_readMsgRam(MCAN0_BASE, MCAN_MEM_TYPE_BUF, 0U, MCAN_RX_FIFO_NUM_1,
                    &rxMsg);

    //
    // Get the New Data Status.
    //
    MCAN_getNewDataStatus(MCAN0_BASE, &newData);

    //
    // Check that received data matches sent data.
    // Device will halt here during debug if data doesn't match.
    //
    if((txMsg.data[0] != rxMsg.data[0]) ||
       (txMsg.data[1] != rxMsg.data[1]) ||
       (txMsg.data[2] != rxMsg.data[2]) ||
       (txMsg.data[3] != rxMsg.data[3]))
    {
        //
        // Device will halt here if transmitted and received data are
        // not same.
        //
        __asm("   bkpt #0");
    }
    else
    {
        //
        // Increment message count if message is received.
        //
        msgCount++;
    }

    //
    // Stop Application.
    //
    __asm("   bkpt #0");
}

//
// This function will configure MCAN module.
//
static void MCANConfig(void)
{
    MCAN_RevisionId revId;
    MCAN_InitParams initParams;
    MCAN_ConfigParams configParams;
    MCAN_MsgRAMConfigParams    msgRAMConfigParams;
    MCAN_StdMsgIDFilterElement stdFiltelem;
    MCAN_BitTimingParams       bitTimes;

    //
    // Initialize MCAN Init parameters.
    //
    initParams.fdMode            = 0x1U; // FD operation enabled.
    initParams.brsEnable         = 0x1U; // Bit rate switching for
                                         // transmissions enabled.
    initParams.txpEnable         = 0x0U; // Transmit pause disabled.
    initParams.efbi              = 0x0U; // Edge filtering disabled.
    initParams.pxhddisable       = 0x0U; // Protocol exception handling enabled.
    initParams.darEnable         = 0x0U; // Enable automatic retransmission of messages
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
    configParams.monEnable         = monEn; // Bus Monitoring Mode is disabled.
    configParams.asmEnable         = 0x0U;  // Normal CAN operation.
    configParams.tsPrescalar       = 0xFU;  // Prescaler Value.
    configParams.tsSelect          = 0x0U;  // Timestamp counter value.
    configParams.timeoutSelect     = MCAN_TIMEOUT_SELECT_CONT;
    // Time-out counter source select.
    configParams.timeoutPreload    = 0xFFFFU; // Start value of the Timeout
                                              // Counter.
    configParams.timeoutCntEnable  = 0x0U; // Time-out Counter is disabled.
    configParams.filterConfig.rrfs = 0x1U; // Reject all remote frames with
                                           // 29-bit extended IDs.
    configParams.filterConfig.rrfe = 0x1U; // Reject all remote frames with
                                           // 11-bit standard IDs.
    configParams.filterConfig.anfe = 0x1U; // Accept in Rx FIFO 1.
    configParams.filterConfig.anfs = 0x1U; // Accept in Rx FIFO 1.

    //
    // Initialize Message RAM Sections Configuration Parameters.
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
    msgRAMConfigParams.txFIFOSize           = 0U; // No Tx FIFO/Queue.
    msgRAMConfigParams.txBufMode            = 0U; //Tx FIFO operation
    msgRAMConfigParams.txBufElemSize        = MCAN_ELEM_SIZE_64BYTES;
    // Tx Buffer Element Size.
    msgRAMConfigParams.txEventFIFOStartAddr = MCAN_TX_EVENT_START_ADDR;
    // Tx Event FIFO Start Address.
    msgRAMConfigParams.txEventFIFOSize      = MCAN_TX_BUFF_SIZE;
    // Event FIFO Size.
    msgRAMConfigParams.txEventFIFOWaterMark = 3U;
    // Level for Tx Event FIFO watermark interrupt.
    msgRAMConfigParams.rxFIFO0startAddr     = MCAN_FIFO_0_START_ADDR;
    // Rx FIFO0 Start Address.
    msgRAMConfigParams.rxFIFO0size          = MCAN_FIFO_0_NUM;
    // Number of Rx FIFO elements.
    msgRAMConfigParams.rxFIFO0waterMark     = 3U; // Rx FIFO0 Watermark.
    msgRAMConfigParams.rxFIFO0OpMode        = 0U; // FIFO blocking mode.
    msgRAMConfigParams.rxFIFO1startAddr     = MCAN_FIFO_1_START_ADDR;
    // Rx FIFO1 Start Address.
    msgRAMConfigParams.rxFIFO1size          = MCAN_FIFO_1_NUM;
    // Number of Rx FIFO elements.
    msgRAMConfigParams.rxFIFO1waterMark     = 3U; // Level for Rx FIFO 1
                                                  // watermark interrupt.
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
    // Get MCANSS Revision ID.
    //
    MCAN_getRevisionId(MCAN0_BASE, &revId);
    
    //
    // Wait for Memory initialization to be completed.
    //
    while(FALSE == MCAN_isMemInitDone(MCAN0_BASE));

    //
    // Put MCAN in SW initialization mode.
    //
    MCAN_setOpMode(MCAN0_BASE, MCAN_OPERATION_MODE_SW_INIT);

    //
    // Wait till MCAN is not initialized.
    //
    while (MCAN_OPERATION_MODE_SW_INIT != MCAN_getOpMode(MCAN0_BASE));

    //
    // Initialize MCAN module.
    //
    MCAN_init(MCAN0_BASE, &initParams);

    //
    // Configure MCAN module.
    //
    MCAN_config(MCAN0_BASE, &configParams);

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
    // Enable internal loopback mode
    //
    MCAN_lpbkModeEnable(MCAN0_BASE, MCAN_LPBK_MODE_EXTERNAL, TRUE);

    //
    // Take MCAN out of the SW initialization mode
    //
    MCAN_setOpMode(MCAN0_BASE, MCAN_OPERATION_MODE_NORMAL);

    while (MCAN_OPERATION_MODE_NORMAL != MCAN_getOpMode(MCAN0_BASE));
}

//
// This function will configure X-BAR for MCAN interrupts.
//
static void MCANIntrConfig(void)
{
    Interrupt_registerHandler(INT_MCANSS_0,&MCANIntr0ISR);
    Interrupt_enable(INT_MCANSS_0);
    Interrupt_registerHandler(INT_MCANSS_1,&MCANIntr1ISR);
    Interrupt_enable(INT_MCANSS_1);
    Interrupt_enableInProcessor();
}

//
// This is Interrupt Service Routine for MCAN interrupt 0.
//
static void MCANIntr0ISR(void)
{
    uint32_t intrStatus;
    intrStatus = MCAN_getIntrStatus(MCAN0_BASE);

    if (MCAN_MSG_INT != intrStatus)
    {
        error++;
    }

    //
    // Clear the interrupt Status.
    //
    MCAN_clearIntrStatus(MCAN0_BASE, intrStatus);

    //
    // Update the flag value.
    //
    isrIntr0Flag = 0U;
}

//
// This is Interrupt Service Routine for MCAN interrupt 1.
//
static void MCANIntr1ISR(void)
{
    uint32_t intrStatus;

    intrStatus = MCAN_getIntrStatus(MCAN0_BASE);
    if (MCAN_MSG_INT != intrStatus)
    {
        error++;
    }

    //
    // Clear the interrupt Status.
    //
    MCAN_clearIntrStatus(MCAN0_BASE, intrStatus);

    //
    // Update the flag value.
    //
    isrIntr1Flag = 0U;
}
