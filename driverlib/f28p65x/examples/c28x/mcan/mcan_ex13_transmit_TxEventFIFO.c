//#############################################################################
//
// FILE:   mcan_ex9_transmit_TxEventFIFO.c
//
// TITLE:  MCAN External Transmit using Tx Buffer demonstrating use of 
//          Tx Event FIFO
//
//! \addtogroup driver_example_c28x_list
//! <h1> MCAN External Transmit using Tx Buffer </h1>
//!
//! This example demonstrates the usage of Tx Event FIFO. External
//! communication is done between two CAN nodes. The receiving node could be
//! another MCU or a CAN bus analysis tool capable of Receiving/ACKnowledging
//! transmitted frames. The transmit and receive pins of the MCAN module
//! should be connected to a CAN Transceiver. Nominal Bit Rate of 500 kbps and
//! Data bit rate of 1 Mbps is used.
//! Standard Identifier (STD ID) 0x4 is transmitted with 64 data bytes.
//! Tx Event FIFOs store transmit status information from the Tx Buffer
//! allowing the Tx Buffer to be overwritten based on the needs of the application
//! Message Marker Bits are used to link Tx Event FIFO elements to the Tx Messages, 
//! while the Tx Timestamp denotes the counter value for when the message was transmitted. 
//!
//! If another C2000 MCU is used as the receiver, mcan_ex4_receive.c can be
//! run on it for the receive function.
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
//!  - txMsg
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
#include "inc/stw_types.h"
#include "inc/stw_dataTypes.h"
#include "inc/hw_types_mcan.h"

//
// Defines.
//
#define NUM_OF_MSG                      (3U)
#define MCAN_STD_ID_FILTER_NUM          (0U)
#define MCAN_EXT_ID_FILTER_NUM          (0U)
#define MCAN_FIFO_0_NUM                 (0U)
#define MCAN_FIFO_0_ELEM_SIZE           (MCAN_ELEM_SIZE_64BYTES)
#define MCAN_FIFO_1_NUM                 (0U)
#define MCAN_FIFO_1_ELEM_SIZE           (MCAN_ELEM_SIZE_64BYTES)
#define MCAN_RX_BUFF_NUM                (0U)
#define MCAN_RX_BUFF_ELEM_SIZE          (MCAN_ELEM_SIZE_64BYTES)
#define MCAN_TX_BUFF_SIZE               (NUM_OF_MSG)
#define MCAN_TX_BUFF_ELEM_SIZE          (MCAN_ELEM_SIZE_64BYTES)
#define MCAN_TX_EVENT_SIZE              (5U)

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
MCAN_TxBufElement txMsg[NUM_OF_MSG];
int32_t loopCnt = 0U, j = 0U;
MCAN_TxEventFIFOStatus TxEFS;
MCAN_TxEventFIFOElement TxEvent, TxEventArray[NUM_OF_MSG];
uint32_t a_MM[NUM_OF_MSG] = { 0xAA, 0xBB, 0xCC};

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
    SysCtl_setMCANClk(SYSCTL_MCANA, SYSCTL_MCANCLK_DIV_5);

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
    // Initialize message to transmit.
    //
    txMsg[loopCnt].id       = ((uint32_t)(0x4)) << 18U; // STDID[28:18]
    txMsg[loopCnt].rtr      = 0U;   // RTR = 0 (Data frame)
    txMsg[loopCnt].xtd      = 0U;   // XTD = 0 (11-bit standard identifier)
    txMsg[loopCnt].esi      = 0U;
    txMsg[loopCnt].dlc      = 15U;  // 64 bytes
    txMsg[loopCnt].brs      = 1U;   // Bit-rate switching enabled
    txMsg[loopCnt].fdf      = 1U;   // Frame transmitted in CAN FD format
    txMsg[loopCnt].efc      = 1U;   // Store TX events
    txMsg[loopCnt].mm       = 0xAAU;
    txMsg[loopCnt].data[i]  = 0x1;
    for(i = 1; i < dataBytes; i++)
    {
        txMsg[loopCnt].data[i]  = txMsg[loopCnt].data[i-1] + 1;
    }
    i = 0;

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

    for(i=0;i<NUM_OF_MSG;i++)
    {
        //
        //  Setting Message Marker to Correlate each Tx Message
        //  with Corresponding Tx Event FIFO Element
        //
        txMsg[loopCnt].mm = a_MM[i];

        //
        // Write message to Message RAM.
        //
        MCAN_writeMsgRam(MCANA_DRIVER_BASE, MCAN_MEM_TYPE_BUF, loopCnt,
                        &txMsg[loopCnt]);

        //
        // Add transmission request for Tx buffer 0
        //
        MCAN_txBufAddReq(MCANA_DRIVER_BASE, 0U);

        //
        // Wait till the frame is successfully transmitted (and ACKnowledged)
        // "Tx Buffer Transmission Occurred" register is polled.
        //
        while(MCAN_getTxBufReqPend(MCANA_DRIVER_BASE))
        {
        }

        //
        // Add delay between consecutive transmit operations
        //
        DEVICE_DELAY_US(50000);
    }

    //
    // Stop Application.
    //
    asm("   ESTOP0");
}

static void MCANConfig(void)
{
    MCAN_InitParams initParams;
    MCAN_ConfigParams configParams;
    MCAN_MsgRAMConfigParams    msgRAMConfigParams;
    MCAN_BitTimingParams       bitTimes;

    //
    //  Initializing all structs to zero to prevent stray values
    //
    memset(&initParams, 0, sizeof(initParams));
    memset(&configParams, 0, sizeof(configParams));
    memset(&msgRAMConfigParams, 0, sizeof(msgRAMConfigParams));
    memset(&bitTimes, 0, sizeof(bitTimes));

    //
    // Initialize MCAN Init parameters.
    //
    initParams.fdMode            = 0x1U; // FD operation enabled.
    initParams.brsEnable         = 0x1U; // Bit rate switching for
                                         // transmissions enabled.

    //
    // Transmitter Delay Compensation parameters.
    //
    initParams.tdcConfig.tdcf    = 0xAU;
    initParams.tdcConfig.tdco    = 0x6U;

    //
    // Initialize MCAN Config parameters.
    //
    configParams.tsSelect          = 0x2U;  // External Timestamp counter value used. (necessary for CAN-FD operation)

    //
    // Initialize Message RAM Sections Configuration Parameters
    //
    msgRAMConfigParams.txStartAddr          = MCAN_TX_BUFF_START_ADDR;
    // Tx Buffers Start Address.

    msgRAMConfigParams.txBufNum             = MCAN_TX_BUFF_SIZE;
    // Number of Dedicated Transmit Buffers.

    msgRAMConfigParams.txBufMode            = 0U;

    msgRAMConfigParams.txBufElemSize        = MCAN_TX_BUFF_ELEM_SIZE;
    // Tx Buffer Element Size.
    msgRAMConfigParams.txEventFIFOStartAddr = MCAN_TX_EVENT_START_ADDR;
    // Tx Event FIFO Start Address.
    msgRAMConfigParams.txEventFIFOSize      = MCAN_TX_EVENT_SIZE;
    // Event FIFO Size.
    msgRAMConfigParams.txEventFIFOWaterMark = 3U;

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
    // Configure MCAN module.
    //
    MCAN_config(MCANA_DRIVER_BASE, &configParams);

    //
    // Configure Message RAM Sections
    //
    MCAN_msgRAMConfig(MCANA_DRIVER_BASE, &msgRAMConfigParams);

    //
    // Set Prescalar and Enable External Timestamp Counter
    //
    MCAN_extTSCounterConfig(MCANA_DRIVER_BASE, 0xFFF);
    MCAN_extTSCounterEnable(MCANA_DRIVER_BASE, 1U);

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
    if((MCAN_INTR_SRC_TX_EVT_FIFO_WATERMARK & intrStatus) == MCAN_INTR_SRC_TX_EVT_FIFO_WATERMARK)
    {
        //
        // Read Tx Event FIFO Status
        //
        MCAN_getTxEventFIFOStatus(MCANA_DRIVER_BASE, &TxEFS);

        //
        // Read all Tx Event FIFO Elements once the
        // watermark is hit, so that the FIFO is empty again
        //
        while(TxEFS.fillLvl)
        {
            //
            // Read Tx Event FIFO Element Data from Message RAM
            //
            MCAN_readTxEventFIFO(MCANA_DRIVER_BASE, &TxEvent);

            //
            // Store Tx FIFO Element information into predefined array
            //
            TxEventArray[j] = TxEvent;
            j++;

            //
            // Write Acknowledge to increment Get Index
            // which will point to the next element in the FIFO
            //
            MCAN_writeTxEventFIFOAck(MCANA_DRIVER_BASE, TxEFS.getIdx);

            //
            // Read FIFO Status to check Fill Level
            //
            MCAN_getTxEventFIFOStatus(MCANA_DRIVER_BASE, &TxEFS);
        }
    }
    else if((MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND & intrStatus) == MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND)
    {
        //
        //  Interrupt handling when timestamp counter rolls over
        //  Counter value resets to zero automatically, in case
        //  no action is taken
        //
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
