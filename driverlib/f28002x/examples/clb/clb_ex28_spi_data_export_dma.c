//#############################################################################
//
// FILE:   clb_ex28_spi_data_export_dma.c
//
// TITLE:  CLB SPI Data Export DMA
//
//! \addtogroup driver_example_list
//! <h1>CLB SPI Data Export DMA</h1>
//!
//! For the detailed description of this example, please refer to:
//!  `C2000Ware_PATH\utilities\clb_tool\clb_syscfg\doc\CLB Tool Users Guide.pdf`
//!
//! In this example the high speed data export feature of the CLB is used and 
//! one of the HLC registers is exported out of the CLB module using the SPI RX 
//! buffer. The data received in the SPI RX buffer is transferred to memory 
//! using DMA. This module is only available for CLB types 3 and up.
//!
//
//#############################################################################
// $TI Release: F28004x Support Library v5.02.00.00 $
// $Release Date: 04-07-2024 $
// $Copyright:
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com/
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
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "board.h"
#include "clb_config.h"

//
// RX FIFO interrupt level
//
uint16_t rxFIFOLevel = 0;

//
// Count for the number of DMA completion interrupts
//
uint16_t dmaIntCount = 0;

//
// The destination array for the CLB exported data
//
uint16_t clbExportedData[16] = {0};

//
// The variable used to validate the exported data
//
uint16_t validationData = 0;

//
// Place buffers in GSRAM
//
#pragma DATA_SECTION(clbExportedData, "ramgs0");

__interrupt void dmaCh6ISR(void)
{
    uint16_t dataIndex = 0;

    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP7);

    //
    // Validate the received/transfered data
    //
    for (dataIndex = 0; dataIndex < rxFIFOLevel; dataIndex++)
    {
        if (clbExportedData[dataIndex] != validationData)
        {
            //
            // Error the data does not match the expected pattern
            //
            ESTOP0;
        }
        validationData += 5;
    }

    //
    // Increment number of interrupt counts.
    //
    dmaIntCount++;
}

void initDMA()
{
    uint16_t txFIFOLevelNotUsed = 0;

    //
    // Read the current FIFO level to know how much data to read
    // from the buffer
    //
    SPI_getFIFOInterruptLevel(mySPIForTILE1_BASE, &txFIFOLevelNotUsed, &rxFIFOLevel);

    //
    // Initialize DMA
    //
    DMA_initController();

    //
    // Configure DMA Ch6 for RX. When the FIFO contains at least rxFIFOLevel words to
    // read, data will be transferred from the SPI module's receive buffer
    // register to the clbExportedData buffer.
    //
    DMA_configAddresses(DMA_CH6_BASE, clbExportedData,
                        (uint16_t *)(mySPIForTILE1_BASE + SPI_O_RXBUF));

    //
    // Each burst is rxFIFOLevel elements of size 16-bit, and the destination address
    // is incremented by one while the source address is kept the same (SPI_O_RXBUF).
    //
    DMA_configBurst(DMA_CH6_BASE, rxFIFOLevel, 0, 1);

    //
    // Do 1 Transfer, keeping the source address unchanged, and rewinding the destination
    // address back to the beginning of the clbExportedData buffer.
    // Continuous mode enabled to redo the configuration when the transfer is done.
    //
    DMA_configTransfer(DMA_CH6_BASE, 1, 0, 1-rxFIFOLevel);
    DMA_configMode(DMA_CH6_BASE, DMA_TRIGGER_SPIARX, DMA_CFG_ONESHOT_DISABLE |
                   DMA_CFG_CONTINUOUS_ENABLE | DMA_CFG_SIZE_16BIT);

    //
    // Configure DMA Ch6 interrupts
    //
    DMA_setInterruptMode(DMA_CH6_BASE, DMA_INT_AT_END);
    DMA_enableInterrupt(DMA_CH6_BASE);
    DMA_enableTrigger(DMA_CH6_BASE);
}

//
// Main
//
void main(void)
{
    Device_init();
    Device_initGPIO();

    Interrupt_initModule();
    Interrupt_initVectorTable();

    Interrupt_register(INT_DMA_CH6, &dmaCh6ISR);
    Interrupt_enable(INT_DMA_CH6);

    //
    // Configures SPI to enable RX FIFO and RX FIFO interrupts
    // for CLB data export
    //
    Board_init();

    //
    // The tile configuration is:
    // TILE1:
    // Non PIPELINE MODE
    // COUNTER0 set to generate a match event every 125000 clocks then reset
    // COUNTER0 match1 event will:
    // 1. Trigger HLC to increment R0 by 5
    // 2. Trigger SPI Export event to push R0 to the SPIRX buffer
    //
    initTILE1(myCLBForTILE1_BASE);

    //
    // Set up DMA for SPI use, initialize the SPI for FIFO mode
    //
    initDMA();

    //
    // Start the DMA channels
    //
    DMA_startChannel(DMA_CH6_BASE);

    CLB_enableCLB(myCLBForTILE1_BASE);


    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;


    while(1)
    {

    }
}


//
// End of File
//
