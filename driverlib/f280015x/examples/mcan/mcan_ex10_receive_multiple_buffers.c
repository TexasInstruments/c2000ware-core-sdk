//#############################################################################
//
// FILE:   mcan_ex10_receive_multiple_buffers.c
//
// TITLE:  MCAN receive multiple messages using Rx Buffer
//
//! \addtogroup driver_example_c28x_list
//! <h1> MCAN receive using Rx Buffer </h1>
//!
//! This example demonstrates how to receive MCAN messages in multiple buffers,
//! including the configuration and handling of the messages. Communication is done
//! between atleast two CAN nodes. The transmitting node could be another MCU or a
//! CAN bus analysis tool capable of transmitting CAN FD frames. The transmit
//! and receive pins of the MCAN module should be connected to a CAN
//! transceiver. Nominal Bit Rate of 500 kbps & Data bit rate of 1 Mbps is used
//!
//! Standard frames with message IDs 0x123, 0x124, 0x125, 0x126 are received.
//! (For Extended frames, same procedure to be followed for configuration
//!   by adding Extended Message ID Filter Element(s))
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
#define NUM_OF_MSG                      (4U)
#define MCAN_STD_ID_FILTER_NUM          (4U)
#define MCAN_EXT_ID_FILTER_NUM          (0U)
#define MCAN_FIFO_0_NUM                 (0U)
#define MCAN_FIFO_0_ELEM_SIZE           (MCAN_ELEM_SIZE_64BYTES)
#define MCAN_FIFO_1_NUM                 (0U)
#define MCAN_FIFO_1_ELEM_SIZE           (MCAN_ELEM_SIZE_64BYTES)
#define MCAN_RX_BUFF_NUM                (10U)
#define MCAN_RX_BUFF_ELEM_SIZE          (MCAN_ELEM_SIZE_64BYTES)
#define MCAN_TX_BUFF_SIZE               (0U)
#define MCAN_TX_BUFF_ELEM_SIZE          (MCAN_ELEM_SIZE_64BYTES)
#define MCAN_TX_EVENT_SIZE              (0U)

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
MCAN_RxBufElement rxMsg[NUM_OF_MSG];
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

    for(loopCnt = 0; loopCnt < NUM_OF_MSG; loopCnt++)
    {
      //
      // Initialize message to receive
      //
      rxMsg[loopCnt].id = 0U;
      rxMsg[loopCnt].rtr = 0U;
      rxMsg[loopCnt].xtd = 0U;
      rxMsg[loopCnt].esi = 0U;
      rxMsg[loopCnt].rxts = 0U;   // Rx Timestamp
      rxMsg[loopCnt].dlc = 0U;
      rxMsg[loopCnt].brs = 0U;
      rxMsg[loopCnt].fdf = 0U;
      rxMsg[loopCnt].fidx = 0U;   // Filter Index
                                  // (of matching Rx acceptance filter element)
      rxMsg[loopCnt].anmf = 0U;   // Accepted Non-matching Frame

      for(i = 0; i < dataBytes; i++)  // Initialize receive buffer to 0
      {
          rxMsg[loopCnt].data[i]  = 0;
      }
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

    for(;;)
    {
        //
        //  Adding delay of 1 second
        //
        DEVICE_DELAY_US(1000000);

        //
        //  Message handling code goes here
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
    MCAN_StdMsgIDFilterElement stdFiltelem;
    MCAN_BitTimingParams       bitTimes;

    //
    //  Initializing all structs to zero to prevent stray values
    //
    memset(&initParams, 0, sizeof(initParams));
    memset(&msgRAMConfigParams, 0, sizeof(msgRAMConfigParams));
    memset(&stdFiltelem, 0, sizeof(stdFiltelem));
    memset(&bitTimes, 0, sizeof(bitTimes));

    //
    // Configure MCAN initialization parameters
    //
    initParams.fdMode            = 0x1U; // FD operation enabled.
    initParams.brsEnable         = 0x1U; // Bit rate switching enabled

    //
    // Initialize Message RAM Sections Configuration Parameters
    //
    msgRAMConfigParams.flssa                = MCAN_STD_ID_FILT_START_ADDR;
    // Standard ID Filter List Start Address.
    msgRAMConfigParams.lss                  = MCAN_STD_ID_FILTER_NUM;
    // List Size: Standard ID.
    msgRAMConfigParams.rxBufStartAddr       = MCAN_RX_BUFF_START_ADDR;
    // Rx Buffer Start Address.
    msgRAMConfigParams.rxBufElemSize        = MCAN_RX_BUFF_ELEM_SIZE;
    // Rx Buffer Element Size.

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
    // Initialize Rx Buffer Configuration parameters.
    //
    stdFiltelem.sfec               = 0x7U; // Store into Rx Buffer
                                           // configuration of SFT[1:0] ignored

    //
    // Configuring SFID2[10:9] = 0 to store message in RX Buffer
    // SFID2[5:0] defines which RX Buffer element received message
    // will be stored into (among upto 64 buffer elements)
    // Frames matching different filter elements cannot be
    // configured to be stored in the same buffer element
    // i.e. SFID2[5:0] HAS to be distinct for every filter element
    //


    //
    // Configure Standard ID filter element 0
    //
    stdFiltelem.sfid2              = 0x0U; // Standard Filter ID 2.
    stdFiltelem.sfid1              = 0x123U; // Standard Filter ID 1.

    MCAN_addStdMsgIDFilter(MCANA_DRIVER_BASE, 0U, &stdFiltelem);

    //
    // Configure Standard ID filter element 1
    //
    stdFiltelem.sfid2              = 0x1U; // Standard Filter ID 2.
    stdFiltelem.sfid1              = 0x124U; // Standard Filter ID 1.

    MCAN_addStdMsgIDFilter(MCANA_DRIVER_BASE, 1U, &stdFiltelem);

    //
    // Configure Standard ID filter element 2
    //
    stdFiltelem.sfid2              = 0x2U; // Standard Filter ID 2.
    stdFiltelem.sfid1              = 0x125U; // Standard Filter ID 1.

    MCAN_addStdMsgIDFilter(MCANA_DRIVER_BASE, 2U, &stdFiltelem);

    //
    // Configure Standard ID filter element 3
    //
    stdFiltelem.sfid2              = 0x3U; // Standard Filter ID 2.
    stdFiltelem.sfid1              = 0x126U; // Standard Filter ID 1.

    MCAN_addStdMsgIDFilter(MCANA_DRIVER_BASE, 3U, &stdFiltelem);

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
    MCAN_RxNewDataStatus newData;

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
    //  Check to see if the interrupt is caused by a message being
    //  received in dedicated RX Buffers
    //
    if((MCAN_IR_DRX_MASK & intrStatus) == MCAN_IR_DRX_MASK)
    {
        //
        // Read the NewData registers
        //
        MCAN_getNewDataStatus(MCANA_DRIVER_BASE, &newData);

        //  If message is received in buffer element 0
        if((newData.statusLow & (1UL << 0U)) != 0)
        {
            MCAN_readMsgRam(MCANA_DRIVER_BASE, MCAN_MEM_TYPE_BUF, 0U,
                          0, &rxMsg[0]);
        }
        //  If message is received in buffer element 1
        if((newData.statusLow & (1UL << 1U)) != 0)
        {
            MCAN_readMsgRam(MCANA_DRIVER_BASE, MCAN_MEM_TYPE_BUF, 1U,
                          0, &rxMsg[1]);
        }
        if((newData.statusLow & (1UL << 2U)) != 0)
        {
            MCAN_readMsgRam(MCANA_DRIVER_BASE, MCAN_MEM_TYPE_BUF, 2U,
                          0, &rxMsg[2]);
        }
        if((newData.statusLow & (1UL << 3U)) != 0)
        {
            MCAN_readMsgRam(MCANA_DRIVER_BASE, MCAN_MEM_TYPE_BUF, 3U,
                          0, &rxMsg[3]);
        }

        //
        //  Clearing the NewData registers
        //
        MCAN_clearNewDataStatus(MCANA_DRIVER_BASE, &newData);
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
