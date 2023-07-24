//#############################################################################
//
// FILE:   mcan_ex1_loopback.c
//
// TITLE:   MCAN Loopback with Interrupts Example
//
//! \addtogroup driver_example_c28x_list
//! <h1> MCAN Internal Loopback with Interrupt </h1>
//!
//! This example shows the MCAN Loopback functionality. The internal loopback
//! mode is entered. The sent message should be received by the node.
//! Use the last address of memory for Rx buffer.
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
// Include Files
//
#include "driverlib.h"
#include "device.h"
#include "inc/stw_dataTypes.h"
#include "inc/stw_types.h"

//
// Defines
//
#define MCAN_STD_ID_FILTER_NUM          (1U)
#define MCAN_EXT_ID_FILTER_NUM          (0U)
#define MCAN_FIFO_0_NUM                 (5U)
#define MCAN_FIFO_0_ELEM_SIZE           (MCAN_ELEM_SIZE_64BYTES)
#define MCAN_FIFO_1_NUM                 (10U)
#define MCAN_FIFO_1_ELEM_SIZE           (MCAN_ELEM_SIZE_64BYTES)
#define MCAN_RX_BUFF_NUM                (10U)
#define MCAN_RX_BUFF_ELEM_SIZE          (MCAN_ELEM_SIZE_64BYTES)
#define MCAN_TX_BUFF_SIZE               (10U)
#define MCAN_TX_BUFF_ELEM_SIZE          (MCAN_ELEM_SIZE_64BYTES)
#define MCAN_TX_EVENT_SIZE              (10U)
#define MCAN_EXT_ID_AND_MASK            (0x1FFFFFFFU)
#define MCAN_MSG_INT                    (0x81200)

//
//  Defining Starting Addresses for Message RAM Sections,
//  (Calculated from Macros based on User defined configuration above)
//
#define MCAN_STD_ID_FILT_START_ADDR     (0x0U)
#define MCAN_EXT_ID_FILT_START_ADDR     (MCAN_STD_ID_FILT_START_ADDR + ((MCAN_STD_ID_FILTER_NUM * MCANSS_STD_ID_FILTER_SIZE_WORDS * 4U)))
#define MCAN_FIFO_0_START_ADDR          (MCAN_EXT_ID_FILT_START_ADDR + ((MCAN_EXT_ID_FILTER_NUM * MCANSS_EXT_ID_FILTER_SIZE_WORDS * 4U)))
#define MCAN_FIFO_1_START_ADDR          (MCAN_FIFO_0_START_ADDR + (MCAN_getMsgObjSize(MCAN_FIFO_0_ELEM_SIZE) * 4U * MCAN_FIFO_0_NUM))
#define MCAN_RX_BUFF_START_ADDR         (MCAN_FIFO_1_START_ADDR + (MCAN_getMsgObjSize(MCAN_FIFO_1_ELEM_SIZE) * 4U * MCAN_FIFO_1_NUM))
#define MCAN_TX_BUFF_START_ADDR         (MCAN_RX_BUFF_START_ADDR + (MCAN_getMsgObjSize(MCAN_RX_BUFF_ELEM_SIZE) * 4U * MCAN_RX_BUFF_NUM))
#define MCAN_TX_EVENT_START_ADDR        (MCAN_TX_BUFF_START_ADDR + (MCAN_getMsgObjSize(MCAN_TX_BUFF_ELEM_SIZE) * 4U * MCAN_TX_BUFF_SIZE))

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
__interrupt void MCANIntr1ISR(void);

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
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Initialize GPIO and unlock the GPIO configuration registers
    //
    Device_initGPIO();

    //
    // Configuring the GPIOs for MCAN.
    //
    GPIO_setPinConfig(DEVICE_GPIO_CFG_MCANRXA);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_MCANTXA);

    //
    // Configure the divisor for the MCAN bit-clock
    //
    SysCtl_setMCANClk(SYSCTL_MCANCLK_DIV_3);

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
    MCAN_enableIntr(MCANA_DRIVER_BASE, MCAN_INTR_MASK_ALL, 1U);

    //
    // Select Interrupt Line.
    //
    MCAN_selectIntrLine(MCANA_DRIVER_BASE, MCAN_INTR_MASK_ALL, MCAN_INTR_LINE_NUM_1);

    //
    // Enable Interrupt Line.
    //
    MCAN_enableIntrLine(MCANA_DRIVER_BASE, MCAN_INTR_LINE_NUM_1, 1U);

    //
    // Write Tx Message to the Message RAM.
    //
    MCAN_writeMsgRam(MCANA_DRIVER_BASE, MCAN_MEM_TYPE_BUF, 1U, &txMsg);

    //
    // Enable Transmission interrupt.
    //
    MCAN_txBufTransIntrEnable(MCANA_DRIVER_BASE, 1U,1U);

    //
    // Add request for transmission.
    //
    MCAN_txBufAddReq(MCANA_DRIVER_BASE, 1U);

    //
    // Wait for the isrIntr1Flag to be reset.
    //
    while(isrIntr1Flag)
    {
    }

    //
    // Read Message RAM.
    //
    MCAN_readMsgRam(MCANA_DRIVER_BASE, MCAN_MEM_TYPE_BUF, 0U, MCAN_RX_FIFO_NUM_1,
                    &rxMsg);

    //
    // Get the New Data Status.
    //
    MCAN_getNewDataStatus(MCANA_DRIVER_BASE, &newData);

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
        asm(" ESTOP0");
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
    asm(" ESTOP0");
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
    //  Initializing all structs to zero to prevent stray values
    //
    memset(&initParams, 0, sizeof(initParams));
    memset(&configParams, 0, sizeof(configParams));
    memset(&msgRAMConfigParams, 0, sizeof(msgRAMConfigParams));
    memset(&stdFiltelem, 0, sizeof(stdFiltelem));
    memset(&bitTimes, 0, sizeof(bitTimes));

    //
    // Initialize MCAN Init parameters.
    //
    initParams.fdMode            = 0x1U; // FD operation enabled.
    initParams.brsEnable         = 0x1U; // Bit rate switching for
                                         // transmissions enabled.
    initParams.txpEnable         = 0x0U; // Transmit pause disabled.
    initParams.efbi              = 0x0U; // Edge filtering disabled.
    initParams.pxhddisable       = 0x0U; // Protocol exception handling enabled
    initParams.darEnable         = 0x0U; // Enable Automatic retransmission of
                                       // messages not transmitted successfully
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
    configParams.monEnable         = monEn; // Bus Monitoring Mode is disabled
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
    msgRAMConfigParams.txBufElemSize        = MCAN_TX_BUFF_ELEM_SIZE;
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
    msgRAMConfigParams.rxBufElemSize        = MCAN_RX_BUFF_ELEM_SIZE;
    // Rx Buffer Element Size.
    msgRAMConfigParams.rxFIFO0ElemSize      = MCAN_FIFO_0_ELEM_SIZE;
    // Rx FIFO0 Element Size.
    msgRAMConfigParams.rxFIFO1ElemSize      = MCAN_FIFO_1_ELEM_SIZE;
    // Rx FIFO1 Element Size.

    //
    // Initialize Rx Buffer Configuration parameters.
    //
    stdFiltelem.sfid2              = 0x0U; // Standard Filter ID 2.
    stdFiltelem.sfid1              = 0x4U; // Standard Filter ID 1.
    stdFiltelem.sfec               = 0x7U; // Store into Rx Buffer
    stdFiltelem.sft                = 0x0U; // Range filter from SFID1 to SFID2

    //
    // Initialize bit timings
    //
    bitTimes.nomRatePrescalar   = 0x3U; // Nominal Baud Rate Pre-scaler.
    bitTimes.nomTimeSeg1        = 0x9U; // Nominal Time segment before SP
    bitTimes.nomTimeSeg2        = 0x8U; // Nominal Time segment after SP
    bitTimes.nomSynchJumpWidth  = 0x8U; // Nominal SJW
    bitTimes.dataRatePrescalar  = 0x1U; // Data Baud Rate Pre-scaler.
    bitTimes.dataTimeSeg1       = 0x9U; // Data Time segment before SP
    bitTimes.dataTimeSeg2       = 0x8U; // Data Time segment after SP
    bitTimes.dataSynchJumpWidth = 0x8U; // Data SJW

    //
    // Get MCANSS Revision ID.
    //
    MCAN_getRevisionId(MCANA_DRIVER_BASE, &revId);

    //
    // Wait for Memory initialization to be completed.
    //
    while(FALSE == MCAN_isMemInitDone(MCANA_DRIVER_BASE));

    //
    // Put MCAN in SW initialization mode.
    //
    MCAN_setOpMode(MCANA_DRIVER_BASE, MCAN_OPERATION_MODE_SW_INIT);

    //
    // Wait till MCAN is not initialized.
    //
    while (MCAN_OPERATION_MODE_SW_INIT != MCAN_getOpMode(MCANA_DRIVER_BASE));

    //
    // Initialize MCAN module.
    //
    MCAN_init(MCANA_DRIVER_BASE, &initParams);

    //
    // Configure MCAN module.
    //
    MCAN_config(MCANA_DRIVER_BASE, &configParams);

    //
    // Configure Bit timings.
    //
    MCAN_setBitTime(MCANA_DRIVER_BASE, &bitTimes);

    //
    // Configure Message RAM Sections
    //
    MCAN_msgRAMConfig(MCANA_DRIVER_BASE, &msgRAMConfigParams);

    //
    // Configure Standard ID filter element
    //
    MCAN_addStdMsgIDFilter(MCANA_DRIVER_BASE, 0U, &stdFiltelem);

    //
    // Enable internal loopback mode
    //
    MCAN_lpbkModeEnable(MCANA_DRIVER_BASE, MCAN_LPBK_MODE_EXTERNAL, TRUE);

    //
    // Take MCAN out of the SW initialization mode
    //
    MCAN_setOpMode(MCANA_DRIVER_BASE, MCAN_OPERATION_MODE_NORMAL);

    while (MCAN_OPERATION_MODE_NORMAL != MCAN_getOpMode(MCANA_DRIVER_BASE));
}

//
// This function will configure X-BAR for MCAN interrupts.
//
static void MCANIntrConfig(void)
{

    Interrupt_initModule();
    Interrupt_initVectorTable();

    Interrupt_register(INT_MCANA_1,&MCANIntr1ISR);
    Interrupt_enable(INT_MCANA_1);

    Interrupt_enableGlobal();

}

//
// This is Interrupt Service Routine for MCAN interrupt 1.
//
__interrupt void MCANIntr1ISR(void)
{
    uint32_t intrStatus;

    intrStatus = MCAN_getIntrStatus(MCANA_DRIVER_BASE);
    if (MCAN_MSG_INT != intrStatus)
    {
        error++;
    }

    //
    // Clear the interrupt Status.
    //
    MCAN_clearIntrStatus(MCANA_DRIVER_BASE, intrStatus);

    //
    // Update the flag value.
    //
    isrIntr1Flag = 0U;

    //
    // Acknowledge this interrupt located in group 9
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP9);
}
