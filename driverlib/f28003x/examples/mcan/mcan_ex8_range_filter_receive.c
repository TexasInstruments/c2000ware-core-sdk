//#############################################################################
//
// FILE:   mcan_ex8_range_filter_receive.c
//
// TITLE:  MCAN Reception of EXTID frames (with RANGE filter) into RX-FIFO1
//
//! \addtogroup driver_example_c28x_list
//! <h1> MCAN External Reception (with RANGE filter) into RX-FIFO1 </h1>
//!
//! This example demonstrates Receiving, with RANGE filter configuration.
//! The transmitting node could be a CAN FD capable controller or a
//! CAN bus analysis tool capable of transmitting CAN FD frames.
//! Only Extended IDs from 0x1FFFFF23 to 0x1FFFFF46 are received.
//! Other IDs are not received. RXFIFO1 starts at an offset of 748 (2EC).
//! MCAN Message RAM starts at 0x58000, so received messages will be copied
//! starting at address 0x582EC. Note that as long as the ID matches,
//! "classic" CAN frames will also be received.
//!
//! The transmit and receive pins of the MCAN module should be connected to a
//! CAN Transceiver. Nominal Bit Rate of 500 kbps and Data bit rate of 1 Mbps
//! is used.
//!
//!
//! \b Hardware \b Required \n
//!  - A C2000 board with CAN transceiver
//!
//! \b External \b Connections \n
//!  Both nodes should communicate through CAN FD capable transceivers.
//!
//!  - MCAN is on DEVICE_GPIO_PIN_CANRXA (MCANRXA)
//!  - and DEVICE_GPIO_PIN_CANTXA (MCANTXA)
//!
//! \b Watch \b Variables \n
//!  - rxMsg
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
#include "inc/stw_types.h"
#include "inc/stw_dataTypes.h"
#include "inc/hw_types_mcan.h"

//
// Defines.
//
#define NUM_OF_MSG                      (1U)
#define MCAN_STD_ID_FILTER_NUM          (0U)
#define MCAN_EXT_ID_FILTER_NUM          (1U)
#define MCAN_FIFO_0_NUM                 (0U)
#define MCAN_FIFO_0_ELEM_SIZE           (MCAN_ELEM_SIZE_64BYTES)
#define MCAN_FIFO_1_NUM                 (NUM_OF_MSG)
#define MCAN_FIFO_1_WATERMARK           (NUM_OF_MSG)
#define MCAN_FIFO_1_ELEM_SIZE           (MCAN_ELEM_SIZE_64BYTES)
#define MCAN_RX_BUFF_NUM                (0U)
#define MCAN_RX_BUFF_ELEM_SIZE          (MCAN_ELEM_SIZE_64BYTES)
#define MCAN_TX_BUFF_SIZE               (0U)
#define MCAN_TX_BUFF_ELEM_SIZE          (MCAN_ELEM_SIZE_64BYTES)
#define MCAN_TX_EVENT_SIZE              (0U)
#define MCAN_EXT_ID_AND_MASK            (0x1FFFFFFFU)

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
int32_t     error = 0;
MCAN_RxBufElement rxMsg[NUM_OF_MSG], rxMsg1;
MCAN_RxFIFOStatus RxFS;
int32_t loopCnt = 0U;

//
// Function Prototype.
//
static void MCANConfig(void);
static void MCANIntrConfig(void);
__interrupt void MCANIntr1ISR(void);

void main()
 {
    int i = 0;
    volatile uint32_t mode = 0U;
    uint32_t dataBytes = 64;

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Initialize GPIO and unlock the GPIO configuration registers
    //
    Device_initGPIO();

    //
    // Configure the divisor for the MCAN bit-clock
    //
    SysCtl_setMCANClk(SYSCTL_MCANCLK_DIV_3);

    //
    // ISR Configuration.
    //
    MCANIntrConfig();

    //
    // Configure GPIO pins for MCANTX/MCANRX operation
    //
    GPIO_setPinConfig(DEVICE_GPIO_CFG_MCANRXA);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_MCANTXA);

    //
    // Initialize receive data structure
    // (not to be confused with RX Buffer inside the MCAN module)
    //
    rxMsg[loopCnt].id = 0U;
    rxMsg[loopCnt].rtr = 0U;
    rxMsg[loopCnt].xtd = 1U;
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

    //
    // Configure the MCAN Module.
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
    asm("   ESTOP0");
}

static void MCANConfig(void)
{
    MCAN_InitParams initParams;
    MCAN_MsgRAMConfigParams    msgRAMConfigParams;
    MCAN_ExtMsgIDFilterElement extFiltelem;
    MCAN_BitTimingParams       bitTimes;

    //
    //  Initializing all structs to zero to prevent stray values
    //
    memset(&initParams, 0, sizeof(initParams));
    memset(&msgRAMConfigParams, 0, sizeof(msgRAMConfigParams));
    memset(&extFiltelem, 0, sizeof(extFiltelem));
    memset(&bitTimes, 0, sizeof(bitTimes));

    //
    // Initialize MCAN Init parameters.
    //
    initParams.fdMode            = 0x1U; // FD operation enabled.
    initParams.brsEnable         = 0x1U; // Bit rate switching enabled.

    //
    // Initialize Message RAM Sections Configuration Parameters
    //
    msgRAMConfigParams.flesa                = MCAN_EXT_ID_FILT_START_ADDR;
    // Extended ID Filter List Start Address (0)

    msgRAMConfigParams.lse                  = MCAN_EXT_ID_FILTER_NUM;
    // Extended ID Filter List Size (1)

    msgRAMConfigParams.rxFIFO1startAddr     = MCAN_FIFO_1_START_ADDR;
    // Rx FIFO1 Start Address (748U)

    msgRAMConfigParams.rxFIFO1size          = MCAN_FIFO_1_NUM;
    // Number of Rx FIFO elements (1)

    msgRAMConfigParams.rxFIFO1waterMark     = MCAN_FIFO_1_WATERMARK;
    // Level for Rx FIFO 1 watermark interrupt (1)

    msgRAMConfigParams.rxFIFO1OpMode        = 0U;
    // FIFO blocking mode.

    msgRAMConfigParams.rxFIFO1ElemSize      = MCAN_FIFO_1_ELEM_SIZE;
    // Rx FIFO1 Element Size - RBDS field of MCAN_RXESC Register

    //
    // Initialize Rx FIFO Filter element Configuration parameters.
    //

    extFiltelem.efid2               = 0x1FFFFF46U;    // Extended ID2
    extFiltelem.efid1               = 0x1FFFFF23U;    // Extended ID1
    extFiltelem.efec                = 0x6U;           // Store into FIFO 1.
    extFiltelem.eft                 = 0x0U;           // Range filter from EFID1 to EFID2
                                                            //(EFID2 >= EFID1)
    //
    // Initialize bit timings.
    //
    bitTimes.nomRatePrescalar   = 0x3U; // Nominal Baud Rate Pre-scaler.
    bitTimes.nomTimeSeg1        = 0x9U; // Nominal Time segment before SP
    bitTimes.nomTimeSeg2        = 0x8U; // Nominal Time segment after SP
    bitTimes.nomSynchJumpWidth  = 0x8U; // Nominal (Re)Synch Jump Width Range
    bitTimes.dataRatePrescalar  = 0x1U; // Data Baud Rate Pre-scaler.
    bitTimes.dataTimeSeg1       = 0x9U; // Data Time segment before SP
    bitTimes.dataTimeSeg2       = 0x8U; // Data Time segment after SP
    bitTimes.dataSynchJumpWidth = 0x8U; // Data (Re)Synchronization Jump Width

    //
    // Wait for memory initialization to happen.
    //
    while(FALSE == MCAN_isMemInitDone(MCANA_DRIVER_BASE))
    {
    }

    //
    // Put MCAN in SW initialization mode.
    //
    MCAN_setOpMode(MCANA_DRIVER_BASE, MCAN_OPERATION_MODE_SW_INIT);

    //
    // Wait till MCAN is not initialized.
    //
    while (MCAN_OPERATION_MODE_SW_INIT != MCAN_getOpMode(MCANA_DRIVER_BASE))
    {}

    //
    // Initialize MCAN module.
    //
    MCAN_init(MCANA_DRIVER_BASE, &initParams);

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
    MCAN_addExtMsgIDFilter(MCANA_DRIVER_BASE, 0U, &extFiltelem);

    //
    // Set Extended ID Mask for acceptance filtering of received frames
    // (Mask disabled when all bits are set to 1)
    //
    MCAN_setExtIDAndMask(MCANA_DRIVER_BASE, MCAN_EXT_ID_AND_MASK);

    //
    // Take MCAN out of the SW initialization mode
    //
    MCAN_setOpMode(MCANA_DRIVER_BASE, MCAN_OPERATION_MODE_NORMAL);

    while (MCAN_OPERATION_MODE_NORMAL != MCAN_getOpMode(MCANA_DRIVER_BASE))
    {

    }
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

    //
    //  Clearing the interrupt lineNum
    //
    HW_WR_FIELD32(MCANA_DRIVER_BASE + MCAN_MCANSS_EOI, MCAN_MCANSS_EOI, 0x2);

    //
    // Clear the interrupt Status.
    //
    MCAN_clearIntrStatus(MCANA_DRIVER_BASE, intrStatus);

    //
    //  Check to see if the interrupt is caused by a new message being
    //  received in RX FIFO 1
    //
    if((MCAN_INTR_SRC_RX_FIFO1_NEW_MSG & intrStatus) == MCAN_INTR_SRC_RX_FIFO1_NEW_MSG)
    {
        MCAN_readMsgRam(MCANA_DRIVER_BASE, MCAN_MEM_TYPE_FIFO, 0U,
                            MCAN_RX_FIFO_NUM_1, &rxMsg1);

        rxMsg[loopCnt] = rxMsg1;
        RxFS.num = MCAN_RX_FIFO_NUM_1;

        MCAN_writeRxFIFOAck(MCANA_DRIVER_BASE, MCAN_RX_FIFO_NUM_1,
                            RxFS.getIdx);
    }
    else
    {
        error++;

        //
        //  Interrupt handling for other interrupt sources goes here
        //

    }

    //
    // Acknowledge this interrupt located in group 9
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP9);
}
