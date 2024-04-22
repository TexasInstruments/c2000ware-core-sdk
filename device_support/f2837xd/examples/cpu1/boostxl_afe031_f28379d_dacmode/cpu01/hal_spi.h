//#############################################################################
//
// FILE:   hal_spi.h
//
// TITLE:  HAL SPI Functions
//
//###########################################################################
//
// 
// $Copyright:
// Copyright (C) 2013-2024 Texas Instruments Incorporated - http://www.ti.com/
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
//###########################################################################

#ifndef _HAL_SPI_H
#define _HAL_SPI_H

//
// Defines
//

/* LSPCLK = SYSCLK/2/LSPCLK */
/* SPICLK = LSPCLK/(BRR+1) */
/* SYSCLK=100MHz, SPICLK=100/4/5=5MHz */

#define HAL_SPI_LSPCLK    1  //LSPCLK=SYSCLK

#define HAL_SPI_CCR_RST0  0x0F
#define HAL_SPI_CCR_RST1  0x8F
#define HAL_SPI_CTL_MSTR  0x06
#define HAL_SPI_FFTX      0xE040
#define HAL_SPI_FFRX      0x204F

/* PGA112 */
#define HAL_SPI_PGA_READ      0x6A
#define HAL_SPI_PGA_WRITE     0x2A
#define HAL_SPI_PGA_RWSHIFT   8
#define HAL_SPI_PGA_GAINSHIFT 4
#define HAL_SPI_PGA_CH0       0x0
#define HAL_SPI_PGA_CH1       0x1

//
// Function Prototypes
//
void HAL_spi_cfg();
void HAL_spi_init();
void HAL_spi_xmt(Uint16 a);
void HAL_spi_fifoInit();
void HAL_spi_writeGain(Uint16 val);
void InitAFESpiGpio();
void HAL_spi_cfgWdLen(Uint16 val);
Uint16 HAL_spi_read(Uint16 a);


#endif

//
// End of file
//

