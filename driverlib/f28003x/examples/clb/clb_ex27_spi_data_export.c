//#############################################################################
//
// FILE:   clb_ex27_spi_data_export.c
//
// TITLE:  CLB SPI Data Export
//
//! \addtogroup driver_example_list
//! <h1>CLB SPI Data Export</h1>
//!
//! For the detailed description of this example, please refer to:
//!  `C2000Ware_PATH\utilities\clb_tool\clb_syscfg\doc\CLB Tool Users Guide.pdf`
//!
//! In this example the high speed data export feature of the CLB is used and 
//! one of the HLC registers is exported out of the CLB module using the SPI 
//! RX buffer. This module is only available for CLB types 3 and up.
//!
//
//#############################################################################
// $TI Release: F28003x Support Library v5.03.00.00 $
// 
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
// Count for SPI RX FIFO INT
//
uint16_t spiFifoRxIntCount = 0;

//
// Destination buffer for exported CLB data
//
uint16_t clbExportedData[16] = {0};

__interrupt void mySPIForTILE1_RxFIFOISR(void)
{
    uint16_t dataIndex = 0;
    uint16_t rxFIFOLevel = 0;
    uint16_t txFIFOLevel = 0;

    //
    // Read the interrupt status
    //
    uint32_t spiIntStatus = SPI_getInterruptStatus(mySPIForTILE1_BASE);

    //
    // Read the current FIFO level to know how much data to read
    // from the buffer
    //
    SPI_getFIFOInterruptLevel(mySPIForTILE1_BASE, &txFIFOLevel, &rxFIFOLevel);

    if (spiIntStatus & SPI_INT_RXFF)
    {
        for (dataIndex = 0; dataIndex < rxFIFOLevel; dataIndex++)
        {
            clbExportedData [dataIndex] = SPI_readDataNonBlocking(mySPIForTILE1_BASE);
        }
    }
    if (spiIntStatus & SPI_INT_RXFF_OVERFLOW)
    {
        ESTOP0;

        //
        // Error! Data was not read in time
        //
        while(1);
    }

    //
    // Increment number of interrupt counts.
    //
    spiFifoRxIntCount++;

    //
    // Clear interrupt flag and issue ACK
    //
    SPI_clearInterruptStatus(mySPIForTILE1_BASE, SPI_INT_RXFF | SPI_INT_RXFF_OVERFLOW);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP6);
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

    Interrupt_register(INT_SPIA_RX, &mySPIForTILE1_RxFIFOISR);
    Interrupt_enable(INT_SPIA_RX);

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
