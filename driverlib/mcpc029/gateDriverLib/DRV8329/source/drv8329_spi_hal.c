//#############################################################################
//
// FILE:   drv8329_spi_hal.c
//
// TITLE:  SPI HAL Interface for DRV8329
//
//#############################################################################
// $Copyright:
// Copyright (C) 2026 Texas Instruments Incorporated - http://www.ti.com/
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

#include "drv8329_spi_hal.h"
#include "spi.h"
#include "gpio.h"

//*****************************************************************************
//
//! findParity
//
//*****************************************************************************
bool
findParity(int32_t x)
{
    uint32_t y = x ^ (x >> 1);
    y = y ^ (y >> 2);
    y = y ^ (y >> 4);
    y = y ^ (y >> 8);
    y = y ^ (y >> 16);

    //
    // if (y & 1) then ODD PARITY else EVEN PARITY
    //
    if (y & 1)
        return 1;
    return 0;
}

//*****************************************************************************
//
//! DRV_SPI_HAL_Transfer16
//
//*****************************************************************************
uint16_t
DRV_SPI_HAL_Transfer16(uint16_t txData16Bit)
{

    SPI_writeDataBlockingNonFIFO(DRV_SPI_BASE, txData16Bit);
    
    //
    // Rx frame format
    //
    // Status -> Position 15:8
    // Data-> Position 7:0
    //
    return SPI_readDataBlockingNonFIFO(DRV_SPI_BASE);
}

//*****************************************************************************
//
// DRV8329_SPI_HAL_ReadRegister
//
//*****************************************************************************
uint16_t
DRV8329_SPI_HAL_ReadRegister(uint16_t regAddr)
{
    uint16_t parityVal = 0x00;
    uint16_t txData;
    uint16_t rxData;

    ///
    // Construct frame for DRV8329 Register Read
    //
    // R/W Bit -> Position 15; Set to 1 for READ
    // Register Address -> Position 14:9
    // Parity -> Position 8; Compute for Even parity of (Address + R/W bit)
    //
    txData = ((regAddr << DRV8329_SPI_HAL_ADDR_SHIFT) & DRV8329_SPI_HAL_ADDR_MASK) | DRV8329_SPI_HAL_ADDR_READ_FLAG;
    parityVal =  findParity(txData << DRV8329_SPI_HAL_ADDR_JUSTIFY_SHIFT);
    txData = txData | (parityVal & (0x1));
    txData = txData << DRV8329_SPI_HAL_ADDR_JUSTIFY_SHIFT;

    rxData = DRV_SPI_HAL_Transfer16(txData);

    //
    // Return 8-bit Register Data received in position 7:0
    //
    return (rxData & DRV8329_SPI_HAL_DATA_MASK);
}

//*****************************************************************************
//
// DRV8329_SPI_HAL_WriteRegister
//
//*****************************************************************************
void
DRV8329_SPI_HAL_WriteRegister(uint16_t regAddr, uint16_t data)
{
    uint16_t parityVal = 0x00;
    uint16_t txData;
    uint16_t rxData;

    //
    // Construct frame for DRV8329 Register Write
    //
    // R/W Bit -> Position 15; Set to 0 for WRITE
    // Register Address -> Position 14:9
    // Parity -> Position 8; Compute for Even parity of (Address + R/W bit)
    // New Register Value -> Position 7:0
    //
    txData = ((regAddr << DRV8329_SPI_HAL_ADDR_SHIFT) & DRV8329_SPI_HAL_ADDR_MASK);
    parityVal =  findParity(txData << DRV8329_SPI_HAL_ADDR_JUSTIFY_SHIFT);
    txData = txData | (parityVal & (0x1));
    txData = ((txData << DRV8329_SPI_HAL_ADDR_JUSTIFY_SHIFT) | (data & DRV8329_SPI_HAL_DATA_MASK));

    rxData = DRV_SPI_HAL_Transfer16(txData);
}
