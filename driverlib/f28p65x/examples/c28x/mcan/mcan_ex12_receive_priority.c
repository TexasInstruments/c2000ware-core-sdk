//#############################################################################
//
// FILE:   mcan_ex12_receive_priority.c
//
// TITLE:   MCAN Receive High Priority Message Example
//
//! \addtogroup driver_example_c28x_list
//! <h1> MCAN Internal Loopback with Interrupt </h1>
//!
//! This example shows the MCAN Loopback functionality. The internal loopback
//! mode is entered. The sent message should be received by the node.
//! Use the last address of memory for Rx buffer.
//! This example demonstrates the MCAN receive function for High Priority Messages.
//! Messages with Message IDs from the range 0x1 to 0xB are received in Rx FIFO 1,
//! while messages with Message IDs 0x3 and 0x9 are marked as High Priority by the
//! receiving CAN node (frames in itself conform to CAN Protocol, Priority is only
//! marked from the perspective of the receiving CAN Node), following which a separate
//! interrupt is generated and the messages can be read.

//! Communication is done between two CAN nodes. The transmitting node could be another
//! MCU or a CAN bus analysis tool capable of transmitting CAN FD frames. The transmit
//! and receive pins of the MCAN module should be connected to a CAN
//! transceiver. Nominal Bit Rate of 500 kbps & Data bit rate of 1 Mbps is used
//!
//! Only Standard frames within the message ID range 0x1 to 0x9 are received.
//!
//! If another C2000 MCU is used as the transmitter, mcan_ex3_transmit.c can be
//! run on it for the transmit function.
//!
//! \b Hardware \b Required \n
//!  - A C2000 board with CAN transceiver
//!
//! \b External \b Connections \n
//!   Both nodes should communicate through CAN FD capable transceivers.
//!
//!  - MCAN is on DEVICE_GPIO_PIN_CANRXA (MCANRXA)
//!  - and DEVICE_GPIO_PIN_CANTXA (MCANTXA)
//!
//! \b Watch \b Variables \n
//!  - rxMsg, rxMsg1
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
#include "driverlib.h"
#include "device.h"
#include "inc/stw_dataTypes.h"
#include "inc/stw_types.h"
#include "inc/hw_types_mcan.h"

//
// Defines
//
#define MCAN_STD_ID_FILTER_NUM          (3U)
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
MCAN_RxBufElement rxMsg, rxMsg1;
MCAN_RxFIFOStatus RxFS;

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
    SysCtl_setMCANClk(SYSCTL_MCANA, SYSCTL_MCANCLK_DIV_5);

    //
    // CrossBar and ISR Configuration.
    //
    MCANIntrConfig();

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

    while(1)
    {
        //
        //  Adding delay of 1 second
        //
        DEVICE_DELAY_US(1000000);

        //
        //  Message Handling Code goes here
        //

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
    // Standard ID Filter List Size
    msgRAMConfigParams.rxFIFO1startAddr     = MCAN_FIFO_1_START_ADDR;
    // Rx FIFO1 Start Address.
    msgRAMConfigParams.rxFIFO1size          = MCAN_FIFO_1_NUM;
    // Number of Rx FIFO elements.
    msgRAMConfigParams.rxFIFO1waterMark     = 8U; // Level for Rx FIFO 1
                                                  // watermark interrupt.
    msgRAMConfigParams.rxFIFO1OpMode        = 0U; // FIFO blocking mode.
    msgRAMConfigParams.rxFIFO1ElemSize      = MCAN_FIFO_1_ELEM_SIZE;
    // Rx FIFO1 Element Size.

    //
    // Initialize bit timings.
    //
    bitTimes.nomRatePrescalar   = 0x3U; // Nominal Baud Rate Pre-scaler
    bitTimes.nomTimeSeg1        = 0x9U; // Nominal Time segment before SP
    bitTimes.nomTimeSeg2        = 0x8U; // Nominal Time segment after SP
    bitTimes.nomSynchJumpWidth  = 0x8U; // Nominal SJW
    bitTimes.dataRatePrescalar  = 0x1U; // Data Baud Rate Pre-scaler
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
    // Initialize Rx Buffer Configuration parameters.
    //
    stdFiltelem.sfid2              = 0x3U; // Standard Filter ID 2.
    stdFiltelem.sfid1              = 0x9U; // Standard Filter ID 1.
    stdFiltelem.sfec               = MCAN_STDFILTEC_PRI_FIFO0; //
    stdFiltelem.sft                = 0x1U; // Dual ID filter for SFID1 and SFID2

    //
    // Configure Standard ID filter element
    //
    MCAN_addStdMsgIDFilter(MCANA_DRIVER_BASE, 0U, &stdFiltelem);

    //
    // Initialize Rx Buffer Configuration parameters.
    //
    stdFiltelem.sfid2              = 0x1U; // Standard Filter ID 2.
    stdFiltelem.sfid1              = 0xBU; // Standard Filter ID 1.
    stdFiltelem.sfec               = MCAN_STDFILTEC_FIFO0; //
    stdFiltelem.sft                = 0x0U; // Range filter from SFID1 to SFID2

    //
    // Configure Standard ID filter element
    //
    MCAN_addStdMsgIDFilter(MCANA_DRIVER_BASE, 1U, &stdFiltelem);

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

    if((intrStatus & MCAN_INTR_SRC_HIGH_PRIO_MSG) == MCAN_INTR_SRC_HIGH_PRIO_MSG)
    {
        MCAN_readHighPriorityMsgRam(MCANA_DRIVER_BASE, &rxMsg);

        //
        //  High Priority Message Handling Goes Here
        //

    }
    if((intrStatus & MCAN_INTR_SRC_RX_FIFO1_WATERMARK) == MCAN_INTR_SRC_RX_FIFO1_WATERMARK)
    {
        MCAN_RxFIFOStatus RxFS;

        RxFS.num = MCAN_RX_FIFO_NUM_1;

        MCAN_getRxFIFOStatus(MCANA_DRIVER_BASE, &RxFS);

        while(RxFS.fillLvl)
        {
            MCAN_readMsgRam(MCANA_DRIVER_BASE, MCAN_MEM_TYPE_FIFO, 0U,
                                MCAN_RX_FIFO_NUM_1, &rxMsg1);

            MCAN_writeRxFIFOAck(MCANA_DRIVER_BASE, MCAN_RX_FIFO_NUM_1,
                                RxFS.getIdx);
        }
    }

    //
    // Clear the interrupt Status.
    //
    MCAN_clearIntrStatus(MCANA_DRIVER_BASE, intrStatus);

    //
    //  Clearing the interrupt lineNum
    //
    MCAN_clearInterrupt(MCANA_DRIVER_BASE, 0x2);

    //
    // Acknowledge this interrupt located in group 9
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP9);
}
