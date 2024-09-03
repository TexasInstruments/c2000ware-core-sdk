//#############################################################################
//
// FILE:   ssi_ex2_loopback_udma.c
//
// TITLE:  SSI loopback example
//
//! \addtogroup driver_example_cm_list
//! <h1>SSI Loopback example with UDMA</h1>
//!
//! This example showcases how to use UDMA with SSI to transfer and receive data
//!
//! This configures the SSI in loopback mode and sends and receives data for
//! infinite time.
//! cm_common_config_c28x example needs to be run on C28x1 before running this
//! example on the CM core
//!
//! \b Configuration:
//!  - Frame format : TI mode
//!  - Baud rate    : 625000
//!  - Data width   : 16 bits
//!
//! \b External \b Connections \n
//!  - None
//!
//! \b Watch \b Variables \n
//!  - \b TxData   - Data transmitted
//!  - \b RxData   - Data received
//!  - \b errCount - Error count
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

#include "cm.h"

#pragma DATA_ALIGN(ucControlTable, 1024)
UDMA_ControlTable ucControlTable[64];

//
// Initialize the data arrays
//
uint16_t TxData[] = {0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF};
uint16_t RxData[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};

void ConfigureSSI(void)
{
    uint32_t data;

    //
    // Configure SSI in master mode, baud rate = 62500, dataWidth = 16
    //
    SSI_setConfig(SSI0_BASE, CM_CLK_FREQ, SSI_FRF_TI, SSI_MODE_MASTER, 625000, 16);

    //
    // Enable the SSI0 module.
    //
    SSI_enableModule(SSI0_BASE);

    //
    // Enable loopback mode
    //
    SSI_enableLoopback(SSI0_BASE);

        //
    // Read any residual data from the SSI port.  This makes sure the receive
    // FIFOs are empty, so we don't read any unwanted junk.  This is done here
    // because the TI SSI mode is full-duplex, which allows you to send and
    // receive at the same time.  The SSI_readDataNonBlocking function returns
    // "true" when data was returned, and "false" when no data was returned.
    // The "non-blocking" function checks if there is any data in the receive
    // FIFO and does not "hang" if there isn't.
    //
    while(SSI_readDataNonBlocking(SSI0_BASE, &data))
    {
    }
}

void ConfigureDMA(uint16_t* TxDma, uint16_t* RxDma, uint8_t size)
{
//
    // Enable DMA for Tx snd Rx events
    //
    SSI_enableDMA(SSI0_BASE, SSI_DMA_TX | SSI_DMA_RX);

    //
    // Enable UDMA
    //
    UDMA_enable(UDMA_BASE);

    //
    // Point at the control table to use for channel control structures.
    //
    UDMA_setControlBase(UDMA_BASE, ucControlTable);

    //
    // Put the attributes in a known state for the uDMA software channel.
    // These should already be disabled by default.
    //
    UDMA_disableChannelAttribute(UDMA_BASE, UDMA_CHANNEL_SSI0_TX, UDMA_CH_ATTR_ALL);
    UDMA_disableChannelAttribute(UDMA_BASE, UDMA_CHANNEL_SSI0_RX, UDMA_CH_ATTR_ALL);

    //
    // Configure the control parameters for the SSI TX channels
    // Tx channel will be used to transfer data from the buffer to the SSI Data
    // register.
    // Data size = 16
    // Source address increment = 16      (data to be read from 16-bit buffer)
    // Destination address increment = 0  (data to be copied to a single address location)
    //
    // The arbitration size will be set to 4, which causes the uDMA controller
    // to rearbitrate after 8 items are transferred.  This keeps this channel
    // from hogging the uDMA controller once the transfer is started, and allows
    // other channels cycles if they are higher priority.
    //
    UDMA_setChannelControlParams(UDMA_BASE, (UDMA_CHANNEL_SSI0_TX | UDMA_PRI_SELECT),
                                 (UDMA_SIZE_16 | UDMA_SRC_INC_16 | UDMA_DST_INC_NONE
                                  | UDMA_ARB_1));

    UDMA_setChannelTransferParams(UDMA_BASE, (UDMA_CHANNEL_SSI0_TX | UDMA_PRI_SELECT),
                                  TxDma, (void *)(SSI0_BASE + SSI_O_DR), UDMA_MODE_BASIC,
                                  size);

    //
    // Configure the control parameters for the SSI RX channel.
    // Rx channel will be used to transfer data from the SSI Data register to
    // the buffer.
    //
    // Data size = 16
    // Source address increment = 0       (data to be read from a single address location)
    // Destination address increment = 0  (data to be copied to a 16-bit buffer)
    //
    // The arbitration size will be set to 4, which causes the uDMA controller
    // to rearbitrate after 8 items are transferred.  This keeps this channel
    // from hogging the uDMA controller once the transfer is started, and allows
    // other channels cycles if they are higher priority.
    //
    UDMA_setChannelControlParams(UDMA_BASE, (UDMA_CHANNEL_SSI0_RX | UDMA_PRI_SELECT),
                                 (UDMA_SIZE_16 | UDMA_SRC_INC_NONE | UDMA_DST_INC_16
                                  | UDMA_ARB_1));

    UDMA_setChannelTransferParams(UDMA_BASE, (UDMA_CHANNEL_SSI0_RX | UDMA_PRI_SELECT),
                                  (void *)(SSI0_BASE + SSI_O_DR), RxDma, UDMA_MODE_BASIC,
                                  size);
}

//
// Main
//
void main(void)
{
    uint8_t i;
    uint8_t  errCount = 0;

    //
    // Enable clocks
    //
    CM_init();

    ConfigureSSI();
    ConfigureDMA(TxData, RxData, 16);

    //
    // Enable the UDMA channels
    //
    UDMA_enableChannel(UDMA_BASE, UDMA_CHANNEL_SSI0_RX);
    UDMA_enableChannel(UDMA_BASE, UDMA_CHANNEL_SSI0_TX);

    //
    // Wait until the complete transfer is done
    //
    while(UDMA_isChannelEnabled(UDMA_BASE, UDMA_CHANNEL_SSI0_TX));
    while(UDMA_isChannelEnabled(UDMA_BASE, UDMA_CHANNEL_SSI0_RX));

    //
    // Check the receicved data
    //
    for(i = 0; i < 16; i++)
    {
        if(TxData[i] != RxData[i])
        {
            errCount++;
        }
    }

    //
    // Loop forever. Optional
    //
    while(1);
}
