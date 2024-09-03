//#############################################################################
//
// FILE:   mcan_ex9_transmit.c
//
// TITLE:  MCAN External Transmit using Tx Buffer
//
//! \addtogroup driver_example_c28x_list
//! <h1> MCAN External Transmit using Tx Buffer </h1>
//!
//! This example demonstrates the MCAN External Transmit function. External
//! communication is done between two CAN nodes. The receiving node could be
//! another MCU or a CAN bus analysis tool capable of Receiving/ACKnowledging
//! transmitted frames. The transmit and receive pins of the MCAN module
//! should be connected to a CAN Transceiver. Nominal Bit Rate of 500 kbps and
//! Data bit rate of 1 Mbps is used.
//! Standard Identifier (STD ID) 0x4 is transmitted with 64 data bytes.
//! #defines that are not required for this test case have been commented out.
//! However, they have been left in the code should the scope of this code
//! be expanded to include Receive and FIFO functions.
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
// 
// C2000Ware v5.03.00.00
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
#include "driverlib.h"
#include "device.h"
#include "inc/stw_types.h"
#include "inc/stw_dataTypes.h"
#include <string.h>

//
// Defines.
//
#define NUM_OF_MSG                      (1U)
#define MCAN_STD_ID_FILTER_NUM          (0U)
#define MCAN_EXT_ID_FILTER_NUM          (0U)
#define MCAN_FIFO_0_NUM                 (0U)
#define MCAN_FIFO_0_ELEM_SIZE           (MCAN_ELEM_SIZE_64BYTES)
#define MCAN_FIFO_1_NUM                 (0U)
#define MCAN_FIFO_1_ELEM_SIZE           (MCAN_ELEM_SIZE_64BYTES)
#define MCAN_RX_BUFF_NUM                (0U)
#define MCAN_RX_BUFF_ELEM_SIZE          (MCAN_ELEM_SIZE_64BYTES)
#define MCAN_TX_BUFF_SIZE               (NUM_OF_MSG)
#define MCAN_TX_FQ_SIZE                 (0U)
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
#define MCAN_TX_EVENT_START_ADDR        (MCAN_TX_BUFF_START_ADDR + (MCAN_getMsgObjSize(MCAN_TX_BUFF_ELEM_SIZE) * 4U * (MCAN_TX_BUFF_SIZE + MCAN_TX_FQ_SIZE)))


//
// Global Variables.
//
int32_t     error = 0;
MCAN_TxBufElement txMsg[NUM_OF_MSG];
int32_t loopCnt = 0U;

//
// Function Prototype.
//
static void MCANConfig(void);

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
    // Stop Application.
    //
    asm("   ESTOP0");
}

static void MCANConfig(void)
{
    MCAN_InitParams initParams;
    MCAN_MsgRAMConfigParams    msgRAMConfigParams;
    MCAN_BitTimingParams       bitTimes;

    //
    //  Initializing all structs to zero to prevent stray values
    //
    memset(&initParams, 0, sizeof(initParams));
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
    // Initialize Message RAM Sections Configuration Parameters
    //
    msgRAMConfigParams.txStartAddr          = MCAN_TX_BUFF_START_ADDR;
    // Tx Buffers Start Address.

    msgRAMConfigParams.txBufNum             = MCAN_TX_BUFF_SIZE;
    // Number of Dedicated Transmit Buffers.

    msgRAMConfigParams.txBufMode            = 0U;

    msgRAMConfigParams.txFIFOSize           = MCAN_TX_FQ_SIZE; 
    // Number of Tx FIFO or Tx Queue Elements

    msgRAMConfigParams.txBufElemSize        = MCAN_TX_BUFF_ELEM_SIZE;
    // Tx Buffer Element Size.

    //
    // Initialize bit timings.
    //
    bitTimes.nomRatePrescalar   = 0xBU; // Nominal Baud Rate Pre-scaler
    bitTimes.nomTimeSeg1        = 0x2U; // Nominal Time segment before SP
    bitTimes.nomTimeSeg2        = 0x0U; // Nominal Time segment after SP
    bitTimes.nomSynchJumpWidth  = 0x0U; // Nominal SJW
    bitTimes.dataRatePrescalar  = 0x1U; // Data Baud Rate Pre-scaler
    bitTimes.dataTimeSeg1       = 0xAU; // Data Time segment before SP
    bitTimes.dataTimeSeg2       = 0x2U; // Data Time segment after SP
    bitTimes.dataSynchJumpWidth = 0x2U; // Data SJW
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
    // Take MCAN out of the SW initialization mode
    //
    MCAN_setOpMode(MCANA_DRIVER_BASE, MCAN_OPERATION_MODE_NORMAL);

    while (MCAN_OPERATION_MODE_NORMAL != MCAN_getOpMode(MCANA_DRIVER_BASE))
    {

    }
}
