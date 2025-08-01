//#############################################################################
//
// FILE:   uart_ex2_loopback_udma.c
//
// TITLE:  UART loopback example
//
//! \addtogroup driver_example_cm_list
//! <h1>UART Loopback example with UDMA</h1>
//!
//! This example showcases how to use UDMA with UART to transfer and receive data
//!
//! This configures the UART in loopback mode and sends and receives data for
//! infinite time.
//! cm_common_config_c28x example needs to be run on C28x1 before running this
//! example on the CM core
//!
//! \b Configuration:
//!  -  Find correct COM port
//!  -  Bits per second = 115200
//!  -  Data Bits = 8
//!  -  Parity = None
//!  -  Stop Bits = 1
//!  -  Hardware Control = None
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
// C2000Ware v6.00.00.00
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

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "cm.h"
#include "driverlib_cm.h"

#pragma DATA_ALIGN(ucControlTable, 1024)
UDMA_ControlTable ucControlTable[64];

//
// Initialize the data arrays
//
uint8_t TxData[] = {0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF};
uint8_t RxData[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};	

void ConfigureUART(void)
{

    //
    // Configure UART with baud rate = 115200, dataWidth = 8
    //
    UART_setConfig(UART0_BASE,UART_CLK_FREQ , 115200,
                  (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                   UART_CONFIG_PAR_NONE));

    //
    // Enable the UART0 module.
    //
    UART_enableModule(UART0_BASE);

    //
    // Enable loopback mode
    //
    UART_enableLoopback(UART0_BASE);
}

void ConfigureDMA(uint8_t* TxDma, uint8_t* RxDma, uint8_t size)
{
//
    // Enable DMA for Tx snd Rx events
    //
    UART_enableDMA(UART0_BASE,UART_DMA_TX |UART_DMA_RX);

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
    UDMA_disableChannelAttribute(UDMA_BASE, UDMA_CHANNEL_UART0_TX, UDMA_CH_ATTR_ALL);
    UDMA_disableChannelAttribute(UDMA_BASE, UDMA_CHANNEL_UART0_RX, UDMA_CH_ATTR_ALL);

    //
    // Configure the control parameters for the UART TX channels
    // Tx channel will be used to transfer data from the buffer to the UART Data
    // register.
    // Data size = 8
    // Source address increment = 8      (data to be read from 8-bit buffer)
    // Destination address increment = 0 (data to be copied to a single address location)
    //
    // The arbitration size will be set to 1, which causes the uDMA controller
    // to re-arbitrate after 1 item is transferred.
    //
    UDMA_setChannelControlParams(UDMA_BASE, (UDMA_CHANNEL_UART0_TX | UDMA_PRI_SELECT),
                                (UDMA_SIZE_8 | UDMA_SRC_INC_8 | UDMA_DST_INC_NONE
                                 | UDMA_ARB_1));

    UDMA_setChannelTransferParams(UDMA_BASE, (UDMA_CHANNEL_UART0_TX | UDMA_PRI_SELECT),
                                  TxDma, (void *)(UART0_BASE + UART_O_DR), UDMA_MODE_BASIC,
                                  size);

    //
    // Configure the control parameters for the UART RX channel.
    // Rx channel will be used to transfer data from the UART Data register to
    // the buffer.
    //
    // Data size = 8
    // Source address increment = 0       (data to be read from a single address location)
    // Destination address increment = 8  (data to be copied to a 8-bit buffer)
    //
    // The arbitration size will be set to 1, which causes the uDMA controller
    // to re arbitrate after 1 item is transferred.
    //
    UDMA_setChannelControlParams(UDMA_BASE, (UDMA_CHANNEL_UART0_RX | UDMA_PRI_SELECT),
                                (UDMA_SIZE_8 | UDMA_SRC_INC_NONE | UDMA_DST_INC_8
                                  | UDMA_ARB_1));

    UDMA_setChannelTransferParams(UDMA_BASE, (UDMA_CHANNEL_UART0_RX | UDMA_PRI_SELECT),
                                 (void *)(UART0_BASE + UART_O_DR), RxDma, UDMA_MODE_BASIC,
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
    // Disable WD, enable peripheral clocks.
    //
    CM_init();

	//
	// Configure the UART 
	//
    ConfigureUART();
	
	//
	// Configure the UDMA to read/write to the TX/RX buffers 
	//
    ConfigureDMA(TxData, RxData, 16);

    //
    // Enable the UDMA channels
    //
    UDMA_enableChannel(UDMA_BASE, UDMA_CHANNEL_UART0_RX);
    UDMA_enableChannel(UDMA_BASE, UDMA_CHANNEL_UART0_TX);

    //
    // Wait until the complete transfer is done
    //
    while(UDMA_isChannelEnabled(UDMA_BASE, UDMA_CHANNEL_UART0_TX));
    while(UDMA_isChannelEnabled(UDMA_BASE, UDMA_CHANNEL_UART0_RX));

    //
    // Check the received data
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
