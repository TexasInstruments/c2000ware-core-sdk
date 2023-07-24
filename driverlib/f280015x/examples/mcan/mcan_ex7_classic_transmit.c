//#############################################################################
//
// FILE:   mcan_ex7_classic_transmit.c
//
// TITLE:  MCAN Classic frames transmission using Tx Buffer
//
//! \addtogroup driver_example_c28x_list
//! <h1> MCAN Classic frames transmission using Tx Buffer </h1>
//!
//! This simple example shows external communication between the MCAN module
//! and another CAN node. It shows how to transmit classic CAN frames.
//! The GPIOs of MCAN should be connected to a CAN Transceiver.
//! Bit Rate is 500 kbps. Extended Identifier 0x15A5A5A5 is transmitted with
//! 8 data bytes.
//!
//! \b Hardware \b Required \n
//!  - A C2000 board with CAN transceiver
//!
//! \b External \b Connections \n
//!  Both nodes should communicate through CAN transceivers.
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
#define MCAN_TX_BUFF_ELEM_SIZE          (MCAN_ELEM_SIZE_8BYTES)
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
    uint32_t dataBytes = 8;

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Initialize GPIO and configure GPIO pins for CANTX/CANRX
    //
    Device_initGPIO();

    //
    // Configure the divisor for the MCAN bit-clock
    //
    SysCtl_setMCANClk(SYSCTL_MCANCLK_DIV_3);

    //
    // Configuring the GPIOs for MCAN.
    //
    GPIO_setPinConfig(DEVICE_GPIO_CFG_MCANRXA);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_MCANTXA);

    //
    // Initialize message to transmit.
    //
    txMsg[loopCnt].id       = ((uint32_t)(0x15A5A5A5)) ;
    txMsg[loopCnt].rtr      = 0U;
    txMsg[loopCnt].xtd      = 1U;
    txMsg[loopCnt].esi      = 0U;
    txMsg[loopCnt].dlc      = 8U;
    txMsg[loopCnt].brs      = 0U;
    txMsg[loopCnt].fdf      = 0U;
    txMsg[loopCnt].efc      = 1U;
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

    while(1)
    {
        //
        // Add request for all transmission.
        //
        HWREG(MCANA_DRIVER_BASE + MCAN_TXBAR) = 0x00000001;

        //
        // Wait till all the messages are transmitted.
        //
        while(MCAN_getTxBufReqPend(MCANA_DRIVER_BASE))
        {
        }
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
    initParams.fdMode            = 0x0U; // FD operation disabled.
    initParams.brsEnable         = 0x0U; // Bit rate switching for
                                         // transmissions disabled.

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

    //
    // Initialize bit timings.
    //
    bitTimes.nomRatePrescalar   = 0x3U; // Nominal Baud Rate Pre-scaler.
    bitTimes.nomTimeSeg1        = 0x9U; // Nominal Time segment before SP.
    bitTimes.nomTimeSeg2        = 0x8U; // Nominal Time segment after SP.
    bitTimes.nomSynchJumpWidth  = 0x8U; // Nominal SJW Range.

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
