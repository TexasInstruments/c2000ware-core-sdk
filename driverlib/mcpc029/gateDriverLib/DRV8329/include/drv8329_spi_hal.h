//#############################################################################
//
// FILE:   drv8329_spi_hal.h
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

#ifndef DRV8329_SPI_HAL_H
#define DRV8329_SPI_HAL_H

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
//
//! \addtogroup drv8329_spi_hal_api DRV8329 SPI HAL APIs
//! \brief This module contains APIs to communicate with DRV8329 via SPI.
//! @{
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "hw_defines.h"
#include "gpio.h"

//*****************************************************************************
//
// Defines for DRV8329 16-bit SPI transmission word formatting
//
//*****************************************************************************
#define DRV8329_SPI_HAL_ADDR_MASK           0x7E
#define DRV8329_SPI_HAL_ADDR_SHIFT          1
#define DRV8329_SPI_HAL_ADDR_JUSTIFY_SHIFT  8
#define DRV8329_SPI_HAL_ADDR_READ_FLAG      0x80

#define DRV8329_SPI_HAL_DATA_MASK           0xFF

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
//*****************************************************************************
//
//! Read a DRV8329 register
//!
//! \param regAddr is the address of the DRV8329 register to be read
//!
//! This function sends the register address over SPI and receives the
//! register data from the DRV8329
//!
//! \return Returns the 8-bit data read from the specified register in
//! position 7:0
//
//*****************************************************************************
uint16_t
DRV8329_SPI_HAL_ReadRegister(uint16_t regAddr);

//*****************************************************************************
//
//! Write to a DRV8329 register
//!
//! \param regAddr is the address of the DRV8329 register to be written
//! \param data is the 16-bit data to be written to the register
//!
//! This function writes the specified data to the DRV8329 register at the
//! given address using SPI transmission
//!
//! \return None
//
//*****************************************************************************
void
DRV8329_SPI_HAL_WriteRegister(uint16_t regAddr, uint16_t data);

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************

#ifdef __cplusplus
}
#endif // extern "C"

#endif /* DRV8329_SPI_HAL_H */
