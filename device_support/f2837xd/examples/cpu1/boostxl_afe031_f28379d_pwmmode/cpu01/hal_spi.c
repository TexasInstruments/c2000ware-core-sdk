//#############################################################################
//
// FILE:   hal_spi.c
//
// TITLE:  HAL SPI Functions
//
//#############################################################################
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
//#############################################################################

//
// Included Files
//
#include "F28x_Project.h"
#include "hal_spi.h"
#include "afe031_config.h"
#include "hal_afe031.h"

//
// FUNCTION NAME: HAL_spi_cfg
//
// DESCRIPTION:   Configure SPI.
//
// Return Value:  None
//
// Input Parameters:
//
// Output Parameters:
// Functions Called:
//                InitSpiaGpio (TI header lib)
//                HAL_spi_fifo_init
//                HAL_spi_init
//
void HAL_spi_cfg()
{
    InitAFESpiGpio();
    HAL_spi_fifoInit();
    HAL_spi_init();
}

void InitAFESpiGpio()
{
    EALLOW;

    GPIO_SetupPinOptions(58, GPIO_INPUT, GPIO_ASYNC | GPIO_PULLUP);
    GPIO_SetupPinOptions(59, GPIO_INPUT, GPIO_ASYNC | GPIO_PULLUP);
    GPIO_SetupPinOptions(61, GPIO_INPUT, GPIO_ASYNC | GPIO_PULLUP);
    GPIO_SetupPinOptions(60, GPIO_INPUT, GPIO_ASYNC | GPIO_PULLUP);

    GPIO_SetupPinMux(58, GPIO_MUX_CPU1, 15);
    GPIO_SetupPinMux(59, GPIO_MUX_CPU1, 15);
    GPIO_SetupPinMux(60, GPIO_MUX_CPU1, 15);
    GPIO_SetupPinMux(61, GPIO_MUX_CPU1, 15);

    EDIS;
}

//
// FUNCTION NAME: HAL_spi_init
//
// DESCRIPTION:   Initialize SPI.
//
// Return Value:  None
//
// Input Parameters:
//
// Output Parameters:
// Functions Called:
//
//
void HAL_spi_init()
{
    EALLOW;
    ClkCfgRegs.LOSPCP.all = HAL_SPI_LSPCLK;
    EDIS;

    SpiaRegs.SPICCR.bit.SPISWRESET = 0;
    SpiaRegs.SPICCR.bit.CLKPOLARITY = 1;
    SpiaRegs.SPICCR.bit.SPILBK = 0;
    SpiaRegs.SPICCR.bit.SPICHAR = 15; //16-bit character
    SpiaRegs.SPICCR.bit.HS_MODE = 0x1;
    SpiaRegs.SPICTL.bit.SPIINTENA = 0; // Interrupt disable
    SpiaRegs.SPICTL.bit.TALK = 1; // Transmit enable
    SpiaRegs.SPICTL.bit.MASTER_SLAVE = 1; //Master
    SpiaRegs.SPICTL.bit.CLK_PHASE = 0; //Normal phase, depending on SPICCR.6 (CLOCK_POLARITY)
    SpiaRegs.SPICTL.bit.OVERRUNINTENA = 0; //Overrun interrupt disable

    SpiaRegs.SPIBRR.bit.SPI_BIT_RATE = HAL_SPI_BRR;

    SpiaRegs.SPIPRI.bit.FREE = 1;  // Set so breakpoints don't disturb xmission

    SpiaRegs.SPICCR.bit.SPISWRESET = 1; // Ready to transmit
}

//
// FUNCTION NAME: HAL_spi_xmt
//
// DESCRIPTION:   SPI transmit.
//
// Return Value:  None
//
// Input Parameters: val to be transmitted
//
// Output Parameters:
// Functions Called:
//
//
UINT16 spiXmtErrState = 0;
void HAL_spi_xmt(Uint16 a)
{
    SpiaRegs.SPITXBUF = a;
    DELAY_US(1);
}

//
// FUNCTION NAME: PHY_spiFifoInit
//
// DESCRIPTION:   Initialize SPI FIFO.
//
// Return Value:  None
//
// Input Parameters:
//
// Output Parameters:
// Functions Called:
//
//
void HAL_spi_fifoInit()
{
    //
    // Initialize SPI FIFO registers
    //
    SpiaRegs.SPIFFTX.all = HAL_SPI_FFTX;
    SpiaRegs.SPIFFRX.all = HAL_SPI_FFRX;
    SpiaRegs.SPIFFCT.all = 0x0;
}

//
// FUNCTION NAME: HAL_spi_writeGain
//
// DESCRIPTION:   AFE start. Start DMA, adc SOC.
//
// Return Value:  None
//
// Input Parameters: val - gain to be written to PGA
//
// Output Parameters:
// Functions Called:
//
//
void HAL_spi_writeGain(Uint16 val)
{
    Uint16 regVal;

    regVal = (HAL_SPI_PGA_WRITE << HAL_SPI_PGA_RWSHIFT)
            | ((val & 0xF) << HAL_SPI_PGA_GAINSHIFT) |
            HAL_SPI_PGA_CH1;
    HAL_spi_xmt(regVal);
}

//
// FUNCTION NAME: HAL_spi_cfgWdLen
//
// DESCRIPTION:   Configure word length.
//
// Return Value:  None
//
// Input Parameters: val - length
//
// Output Parameters:
// Functions Called:
//
//
void HAL_spi_cfgWdLen(Uint16 val)
{
    SpiaRegs.SPICCR.bit.SPICHAR = val - 1;
}

//
// FUNCTION NAME: HAL_spi_read
//
// DESCRIPTION:   SPI read.
//
// Return Value:  None
//
// Input Parameters:
//
// Output Parameters:
// Functions Called:
//
//
Uint16 HAL_spi_read(Uint16 a)
{
    SpiaRegs.SPITXBUF = a;
    /* Need to check out */
    DELAY_US(2);
    /* Write a dummy */
    SpiaRegs.SPITXBUF = 0xFFFF;
    DELAY_US(2);

    return SpiaRegs.SPIDAT;
}

//
// End of file
//
