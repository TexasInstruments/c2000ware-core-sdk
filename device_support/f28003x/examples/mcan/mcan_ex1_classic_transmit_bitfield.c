//#############################################################################
//
// FILE:   mcan_ex1_classic_transmit_bitfield.c
//
// TITLE:  MCAN Classic frames transmission using Tx Buffer using bit field structures
//
//! \addtogroup bitfield_example_list
//! <h1> MCAN Classic frames transmission using Tx Buffer </h1>
//!
//! This simple example shows external communication between the MCAN module
//! and another MCAN node. It shows how to transmit classic CAN frames.
//! The GPIOs of MCAN should be connected to a CAN Transceiver.
//! Standard Identifier (STD ID) 0x4 is transmitted with
//! 8 data bytes. Run on LaunchPad with CAN Transceiver.
//! Run with example:mcan_ex2_classic_receive_bitfield for RX
//!
//! \b Hardware \b Required \n
//!  - A C2000 board with CAN transceiver
//!
//! \b External \b Connections \n
//!  Both nodes should communicate through CAN transceivers.
//!
//!  - MCANTX is on GPIO4, MCANRX is on GPIO5
//!
//! \b Watch \b Variables \n
//!  - txMsg
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
// Include Files
//
#include "f28x_project.h"

//
// Defines.
//
//
//  Write HW register
//
#define HW_WR_REG32(reg, val)               (*((volatile uint32_t *)(reg)) = val)

//
// MCAN config defines
//
#define BF_MCAN_WAKEUPREQEN                 (0U)
#define BF_MCAN_AUTOWAKEUP                  (0U)
#define BF_MCAN_DBGSUSP_FREE                (0U)
#define BF_MCAN_FDOE                        (0U)
#define BF_MCAN_BRSE                        (0U)
#define BF_MCAN_TXP                         (0U)
#define BF_MCAN_EFBI                        (0U)
#define BF_MCAN_PXHD                        (0U)
#define BF_MCAN_DAR                         (0U)
#define BF_MCAN_TDCF                        (0U)
#define BF_MCAN_TDCO                        (0U)
#define BF_MCAN_WDC                         (0U)
#define BF_MCAN_TDC                         (0U)
#define BF_MCAN_NBTP_NSJW                   (0x8U)
#define BF_MCAN_NBTP_NTSEG2                 (0x8U)
#define BF_MCAN_NBTP_NTSEG1                 (0x9U)
#define BF_MCAN_NBTP_NBRP                   (0x3U)
#define BF_MCAN_DBTP_DBRP                   (0x1U)
#define BF_MCAN_DBTP_DSJW                   (0x8U)
#define BF_MCAN_DBTP_DTSEG1                 (0x9U)
#define BF_MCAN_DBTP_DTSEG2                 (0x8U)
#define BF_MCAN_TXBUF_START_ADDR            (0x0U)
#define BF_MCAN_TXBUF_SIZE                  (1U)
#define BF_MCAN_TXBUF_ELEM_SIZE             (0U) // 8 Bytes max payload
#define BF_MCAN_MSG_ID                      (((uint32_t)(0x4)) << 18U)
#define BF_MCAN_MSG_RTR                     (0U)
#define BF_MCAN_MSG_XTD                     (0U)
#define BF_MCAN_MSG_ESI                     (0U)
#define BF_MCAN_MSG_DLC                     (8U) // 8 Bytes max payload
#define BF_MCAN_MSG_BRS                     (0U)
#define BF_MCAN_MSG_FDF                     (0U)
#define BF_MCAN_MSG_EFC                     (0U)
#define BF_MCAN_MSG_MM                      (0xAAU)
#define BF_MCANSS_TX_BUFFER_ELEM_ID_SHIFT   (0U)
#define BF_MCANSS_TX_BUFFER_ELEM_RTR_SHIFT  (29U)
#define BF_MCANSS_TX_BUFFER_ELEM_XTD_SHIFT  (30U)
#define BF_MCANSS_TX_BUFFER_ELEM_ESI_SHIFT  (31U)
#define BF_MCANSS_TX_BUFFER_ELEM_DLC_SHIFT  (16U)
#define BF_MCANSS_TX_BUFFER_ELEM_BRS_SHIFT  (20U)
#define BF_MCANSS_TX_BUFFER_ELEM_FDF_SHIFT  (21U)
#define BF_MCANSS_TX_BUFFER_ELEM_EFC_SHIFT  (23U)
#define BF_MCANSS_TX_BUFFER_ELEM_MM_SHIFT   (24U)
#define BF_MCAN_PAYLOAD                     (8U) // 8 Bytes max payload

//
//  MCAN RAM base address
//
#define MCANA_MSG_RAM_BASE                  (0x00058000U)

//
// Global Variables.
//
//
//  Transmit message - Classical CAN frames are limited to a maximum data payload of 8 bytes
//
uint16_t txMsg[BF_MCAN_PAYLOAD];
static uint32_t objSize[8]      = {4, 5, 6, 7, 8, 10, 14, 18};
static uint32_t dataSize[16]    = {0,  1,  2,  3,  4,  5,  6,  7, 8, 8, 8, 8, 8, 8, 8, 8};

//
// Function Prototype.
//
static void MCANConfig(void);

void main()
{
    uint32_t cnt            = 0U;
    uint32_t startAddr      = 0U;
    uint32_t elemSize       = 0U;
    uint32_t elemAddr       = 0U;
    uint32_t txBufId        = 0U;
    uint32_t regVal         = 0U;
    uint32_t payloadSize    = 0U;
    uint32_t dataCnt        = 0U;

    //
    // Initialize device clock and peripherals
    //
    InitSysCtrl();

    //
    // Initialize GPIO and configure GPIO pins
    //
    //
    // Initialize GPIO
    //
    InitGpio();

    //
    // Configure the divisor for the MCAN bit-clock
    //
    ClkCfgRegs.AUXCLKDIVSEL.bit.MCANCLKDIV = 2U;

    //
    // Configuring the GPIOs for MCAN.
    //
    GPIO_SetupPinMux(4U, GPIO_MUX_CPU1, 0x03U);//TX
    GPIO_SetupPinMux(5U, GPIO_MUX_CPU1, 0x05U);//RX

    //
    // Configure the MCAN Module.
    //
    MCANConfig();

    //***************************************************************
    //  Write to message RAM
    //***************************************************************

    for(cnt = 0U;cnt < dataSize[BF_MCAN_MSG_DLC];cnt++)
    {
        txMsg[cnt] = cnt;
    }
    //
    //  Get element address
    //
    startAddr   = (McanaRegs.MCAN_TXBC.bit.TBSA << 2U);
    elemSize    = (objSize[McanaRegs.MCAN_TXESC.bit.TBDS] << 2U);
    elemAddr    = startAddr + (elemSize * txBufId);
    //
    //  TX buffer ID
    //
    regVal  = 0U;
    regVal |= ((((uint32_t)BF_MCAN_MSG_ID  << BF_MCANSS_TX_BUFFER_ELEM_ID_SHIFT))     |
               (((uint32_t)BF_MCAN_MSG_RTR << BF_MCANSS_TX_BUFFER_ELEM_RTR_SHIFT))    |
               (((uint32_t)BF_MCAN_MSG_XTD << BF_MCANSS_TX_BUFFER_ELEM_XTD_SHIFT))    |
               (((uint32_t)BF_MCAN_MSG_ESI << BF_MCANSS_TX_BUFFER_ELEM_ESI_SHIFT)));
    HW_WR_REG32(MCANA_MSG_RAM_BASE + elemAddr, regVal);
    elemAddr += 4U;
    //
    //  DLC
    //
    regVal  = 0U;
    regVal |= ((((uint32_t)BF_MCAN_MSG_DLC << BF_MCANSS_TX_BUFFER_ELEM_DLC_SHIFT))    |
               (((uint32_t)BF_MCAN_MSG_BRS << BF_MCANSS_TX_BUFFER_ELEM_BRS_SHIFT))    |
               (((uint32_t)BF_MCAN_MSG_FDF << BF_MCANSS_TX_BUFFER_ELEM_FDF_SHIFT))    |
               (((uint32_t)BF_MCAN_MSG_EFC << BF_MCANSS_TX_BUFFER_ELEM_EFC_SHIFT))    |
               (((uint32_t)BF_MCAN_MSG_MM  << BF_MCANSS_TX_BUFFER_ELEM_MM_SHIFT)));
    HW_WR_REG32(MCANA_MSG_RAM_BASE + elemAddr, regVal);
    elemAddr += 4U;
    //
    //  Payload
    //
    payloadSize = dataSize[BF_MCAN_MSG_DLC];
    dataCnt     = 0U;
    for(cnt = 0U;cnt < (payloadSize >> 2U);cnt++)
    {
        regVal  = 0U;
        regVal |= ((uint32_t)txMsg[dataCnt]                  |
                   ((uint32_t)txMsg[dataCnt + 1U] << 8U)     |
                   ((uint32_t)txMsg[dataCnt + 2U] << 16U)    |
                   ((uint32_t)txMsg[dataCnt + 3U] << 24U));
        HW_WR_REG32(MCANA_MSG_RAM_BASE + elemAddr, regVal);
        elemAddr    += 4U;
        dataCnt     += 4U;
    }
    //
    //  Remaining bytes
    //
    if(0U != (payloadSize % 4U))
    {
        regVal  = 0U;
        regVal |= ((uint32_t)txMsg[dataCnt]                  |
                   ((uint32_t)txMsg[dataCnt + 1U] << 8U)     |
                   ((uint32_t)txMsg[dataCnt + 2U] << 16U)    |
                   ((uint32_t)txMsg[dataCnt + 3U] << 24U));
        HW_WR_REG32(MCANA_MSG_RAM_BASE + elemAddr, regVal);
    }

    //***************************************************************
    //  Transmit TX buffer
    //***************************************************************

    while(1)
    {
        //
        //  Add TX request
        //
        regVal  = McanaRegs.MCAN_TXBAR.all;
        regVal |= (1U << txBufId);

        McanaRegs.MCAN_CCCR.bit.CCE = 0U;
        McanaRegs.MCAN_TXBAR.all    = regVal;

        //
        //  Wait for all message transmission
        //
        while(0U != McanaRegs.MCAN_TXBRP.all)
        {
            ;
        }
    }
}

static void MCANConfig(void)
{
    //
    // Wait for memory initialization to happen.
    //
    while(0U == McanaSsRegs.MCANSS_STAT.bit.MEM_INIT_DONE)
    {
        ;
    }

    //
    // Put MCAN in SW initialization mode.
    //
    McanaRegs.MCAN_CCCR.bit.INIT = 1U;

    //
    // Wait till MCAN is not initialized.
    //
    while(1U != McanaRegs.MCAN_CCCR.bit.INIT)
    {
        ;
    }

    //***************************************************************
    // MCAN init
    //***************************************************************

    //
    //  Configure MCAN wakeup and clock stop controls
    //
    McanaSsRegs.MCANSS_CTRL.bit.WAKEUPREQEN     = BF_MCAN_WAKEUPREQEN;
    McanaSsRegs.MCANSS_CTRL.bit.AUTOWAKEUP      = BF_MCAN_AUTOWAKEUP;
    McanaSsRegs.MCANSS_CTRL.bit.DBGSUSP_FREE    = BF_MCAN_DBGSUSP_FREE;

    //
    //  Unlock write protected registers
    //
    McanaRegs.MCAN_CCCR.bit.CCE     = 1U;

    //
    //  Configure MCAN mode(FD vs Classic CAN operation) and controls
    //
    McanaRegs.MCAN_CCCR.bit.FDOE    = BF_MCAN_FDOE;
    McanaRegs.MCAN_CCCR.bit.BRSE    = BF_MCAN_BRSE;
    McanaRegs.MCAN_CCCR.bit.TXP     = BF_MCAN_TXP;
    McanaRegs.MCAN_CCCR.bit.EFBI    = BF_MCAN_EFBI;
    McanaRegs.MCAN_CCCR.bit.PXHD    = BF_MCAN_PXHD;
    McanaRegs.MCAN_CCCR.bit.DAR     = BF_MCAN_DAR;

    //
    //  Configure Transceiver Delay Compensation
    //
    McanaRegs.MCAN_TDCR.bit.TDCF    = BF_MCAN_TDCF;
    McanaRegs.MCAN_TDCR.bit.TDCO    = BF_MCAN_TDCO;
    McanaRegs.MCAN_RWD.bit.WDC      = BF_MCAN_WDC;
    McanaRegs.MCAN_DBTP.bit.TDC     = BF_MCAN_TDC;

    //***************************************************************
    // MCAN timing configuration
    //***************************************************************

    //
    // Configure Bit timings.
    //
    //
    //  Nominal bit timing
    //
    McanaRegs.MCAN_NBTP.bit.NSJW    = BF_MCAN_NBTP_NSJW;
    McanaRegs.MCAN_NBTP.bit.NTSEG2  = BF_MCAN_NBTP_NTSEG2;
    McanaRegs.MCAN_NBTP.bit.NTSEG1  = BF_MCAN_NBTP_NTSEG1;
    McanaRegs.MCAN_NBTP.bit.NBRP    = BF_MCAN_NBTP_NBRP;

    //
    //  Data bit timing - NOT required for Classic CAN
    //

    //***************************************************************
    // Configure Message RAM Sections
    //***************************************************************

    //
    //  Configure Tx Event FIFO
    //
    McanaRegs.MCAN_TXEFC.bit.EFSA   = 0U;
    McanaRegs.MCAN_TXEFC.bit.EFS    = 0U;
    McanaRegs.MCAN_TXEFC.bit.EFWM   = 0U;

    //
    //  Configure Tx Buffer
    //
    McanaRegs.MCAN_TXBC.bit.TBSA    = (BF_MCAN_TXBUF_START_ADDR >> 2U);
    McanaRegs.MCAN_TXBC.bit.NDTB    = BF_MCAN_TXBUF_SIZE;
    McanaRegs.MCAN_TXBC.bit.TFQS    = 0U;
    McanaRegs.MCAN_TXBC.bit.TFQM    = 0U;
    McanaRegs.MCAN_TXESC.bit.TBDS   = BF_MCAN_TXBUF_ELEM_SIZE;

    //
    //  Lock write protected registers
    //
    McanaRegs.MCAN_CCCR.bit.CCE     = 0U;

    //
    // Take MCAN out of the SW initialization mode
    //
    McanaRegs.MCAN_CCCR.bit.INIT    = 0U;

    while(0U != McanaRegs.MCAN_CCCR.bit.INIT)
    {
        ;
    }

}
