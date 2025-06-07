//#############################################################################
//
//! \file   f2802x/common/source/spi.c
//!
//! \brief  Contains the various functions related to the 
//!         serial peripheral interface (SPI) object
//
//  Group:          C2000
//  Target Device:  TMS320F2802x
//
//#############################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:
// Copyright (C) 2009-2025 Texas Instruments Incorporated - http://www.ti.com/
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
#include "DSP28x_Project.h"
#include "spi.h"

//
// SPI_clearRxFifoOvf -
//
void
SPI_clearRxFifoOvf(SPI_Handle spiHandle)
{
    SPI_Obj *spi = (SPI_Obj *)spiHandle;

    //
    // set the bits
    //
    spi->SPIFFRX |= SPI_SPIFFRX_FIFO_OVFCLR_BITS;

    return;
}

//
// SPI_clearRxFifoInt - 
// 
void
SPI_clearRxFifoInt(SPI_Handle spiHandle)
{
    SPI_Obj *spi = (SPI_Obj *)spiHandle;

    //
    // set the bits
    //
    spi->SPIFFRX |= SPI_SPIFFRX_INTCLR_BITS;

    return;
}

//
// SPI_clearTxFifoInt -
//
void
SPI_clearTxFifoInt(SPI_Handle spiHandle)
{
    SPI_Obj *spi = (SPI_Obj *)spiHandle;

    //
    // set the bits
    //
    spi->SPIFFTX |= SPI_SPIFFTX_INTCLR_BITS;

    return;
}

//
// SPI_disable -
//
void
SPI_disable(SPI_Handle spiHandle)
{
    SPI_Obj *spi = (SPI_Obj *)spiHandle;

    //
    // clear the bits
    //
    spi->SPICCR &= (~SPI_SPICCR_RESET_BITS);
    
    return;
}

//
// SPI_disableChannels - 
//
void
SPI_disableChannels(SPI_Handle spiHandle)
{
    SPI_Obj *spi = (SPI_Obj *)spiHandle;

    //
    // set the bits
    //
    spi->SPIFFTX &= (~SPI_SPIFFTX_CHAN_RESET_BITS);
    
    return;
}

//
// SPI_disableInt - 
//
void
SPI_disableInt(SPI_Handle spiHandle)
{
    SPI_Obj *spi = (SPI_Obj *)spiHandle;

    //
    // clear the bits
    //
    spi->SPICTL &= (~SPI_SPICTL_INT_ENA_BITS);

    return;
}

//
// SPI_disableLoopBack - 
//
void
SPI_disableLoopBack(SPI_Handle spiHandle)
{
    SPI_Obj *spi = (SPI_Obj *)spiHandle;

    //
    // clear the bits
    //
    spi->SPICCR &= (~SPI_SPICCR_SPILBK_BITS);

    return;
}

//
// SPI_disableOverRunInt - 
//
void
SPI_disableOverRunInt(SPI_Handle spiHandle)
{
    SPI_Obj *spi = (SPI_Obj *)spiHandle;

    //
    // clear the bits
    //
    spi->SPICTL &= (~SPI_SPICTL_OVRRUN_INT_ENA_BITS);

    return;
}

//
// SPI_disableRxFifo - 
//
void
SPI_disableRxFifo(SPI_Handle spiHandle)
{
    SPI_Obj *spi = (SPI_Obj *)spiHandle;

    //
    // clear the bits
    //
    spi->SPIFFRX &= (~SPI_SPIFFRX_FIFO_RESET_BITS);

    return;
}

//
// SPI_disableRxFifoInt - 
//
void
SPI_disableRxFifoInt(SPI_Handle spiHandle)
{
    SPI_Obj *spi = (SPI_Obj *)spiHandle;

    //
    // clear the bits
    //
    spi->SPIFFRX &= (~SPI_SPIFFRX_IENA_BITS);

    return;
}

//
// SPI_disableTx - 
//
void
SPI_disableTx(SPI_Handle spiHandle)
{
    SPI_Obj *spi = (SPI_Obj *)spiHandle;

    //
    // clear the bits
    //
    spi->SPICTL &= (~SPI_SPICTL_TALK_BITS);

    return;
}

//
// SPI_disableTxFifo - 
//
void
SPI_disableTxFifo(SPI_Handle spiHandle)
{
    SPI_Obj *spi = (SPI_Obj *)spiHandle;

    //
    // clear the bits
    //
    spi->SPIFFTX &= (~SPI_SPIFFTX_FIFO_RESET_BITS);

    return;
}

//
// SPI_disableTxFifoEnh - 
// 
void
SPI_disableTxFifoEnh(SPI_Handle spiHandle)
{
    SPI_Obj *spi = (SPI_Obj *)spiHandle;

    //
    // clear the bits
    //
    spi->SPIFFTX &= (~SPI_SPIFFTX_FIFO_ENA_BITS);

    return;
}

//
// SPI_disableTxFifoInt - 
//
void
SPI_disableTxFifoInt(SPI_Handle spiHandle)
{
    SPI_Obj *spi = (SPI_Obj *)spiHandle;

    //
    // clear the bits
    //
    spi->SPIFFTX &= (~SPI_SPIFFTX_IENA_BITS);

    return;
}

//
// SPI_enable - 
//
void
SPI_enable(SPI_Handle spiHandle)
{
    SPI_Obj *spi = (SPI_Obj *)spiHandle;

    //
    // set the bits
    //
    spi->SPICCR |= SPI_SPICCR_RESET_BITS;

    return;
}

//
// SPI_enableChannels -
//
void
SPI_enableChannels(SPI_Handle spiHandle)
{
    SPI_Obj *spi = (SPI_Obj *)spiHandle;

    //
    // set the bits
    //
    spi->SPIFFTX |= (uint16_t)SPI_SPIFFTX_CHAN_RESET_BITS;
    
    return;
}

//
// SPI_enableInt - 
//
void
SPI_enableInt(SPI_Handle spiHandle)
{
    SPI_Obj *spi = (SPI_Obj *)spiHandle;

    //
    // set the bits
    //
    spi->SPICTL |= SPI_SPICTL_INT_ENA_BITS;

    return;
}

// 
// SPI_enableLoopBack - 
//
void
SPI_enableLoopBack(SPI_Handle spiHandle)
{
    SPI_Obj *spi = (SPI_Obj *)spiHandle;

    //
    // set the bits
    //
    spi->SPICCR |= SPI_SPICCR_SPILBK_BITS;

    return;
}

//
// SPI_enableOverRunInt - 
//
void
SPI_enableOverRunInt(SPI_Handle spiHandle)
{
    SPI_Obj *spi = (SPI_Obj *)spiHandle;

    //
    // set the bits
    //
    spi->SPICTL |= SPI_SPICTL_OVRRUN_INT_ENA_BITS;

    return;
}

//
// SPI_enableRxFifo - 
//
void
SPI_enableRxFifo(SPI_Handle spiHandle)
{
    SPI_Obj *spi = (SPI_Obj *)spiHandle;

    //
    // set the bits
    //
    spi->SPIFFRX |= SPI_SPIFFRX_FIFO_RESET_BITS;

    return;
}

//
// SPI_enableRxFifoInt - 
//
void
SPI_enableRxFifoInt(SPI_Handle spiHandle)
{
    SPI_Obj *spi = (SPI_Obj *)spiHandle;

    //
    // set the bits
    //
    spi->SPIFFRX |= SPI_SPIFFRX_IENA_BITS;

    return;
}

//
// SPI_enableTx - 
//
void
SPI_enableTx(SPI_Handle spiHandle)
{
    SPI_Obj *spi = (SPI_Obj *)spiHandle;

    //
    // set the bits
    //
    spi->SPICTL |= SPI_SPICTL_TALK_BITS;

    return;
}

//
// SPI_enableTxFifo - 
//
void
SPI_enableTxFifo(SPI_Handle spiHandle)
{
    SPI_Obj *spi = (SPI_Obj *)spiHandle;

    //
    // set the bits
    //
    spi->SPIFFTX |= SPI_SPIFFTX_FIFO_RESET_BITS;

    return;
}

//
// SPI_enableFifoEnh - 
//
void
SPI_enableFifoEnh(SPI_Handle spiHandle)
{
    SPI_Obj *spi = (SPI_Obj *)spiHandle;

    //
    // set the bits
    //
    spi->SPIFFTX |= SPI_SPIFFTX_FIFO_ENA_BITS;

    return;
}

//
// SPI_enableTxFifoInt - 
//
void
SPI_enableTxFifoInt(SPI_Handle spiHandle)
{
    SPI_Obj *spi = (SPI_Obj *)spiHandle;

    //
    // set the bits
    //
    spi->SPIFFTX |= SPI_SPIFFTX_IENA_BITS;

    return;
}

//
// SPI_getRxFifoStatus - 
//
SPI_FifoStatus_e
SPI_getRxFifoStatus(SPI_Handle spiHandle)
{
    SPI_Obj *spi = (SPI_Obj *)spiHandle;

    //
    // get the status
    //
    SPI_FifoStatus_e status = (SPI_FifoStatus_e)
                              (spi->SPIFFRX & SPI_SPIFFRX_FIFO_ST_BITS);

    return(status);
}

//
// SPI_getTxFifoStatus - 
//
SPI_FifoStatus_e
SPI_getTxFifoStatus(SPI_Handle spiHandle)
{
    SPI_Obj *spi = (SPI_Obj *)spiHandle;

    //
    // get the status
    //
    SPI_FifoStatus_e status = (SPI_FifoStatus_e)
                              (spi->SPIFFTX & SPI_SPIFFTX_FIFO_ST_BITS);

    return(status);
}

//
// SPI_init - 
//
SPI_Handle
SPI_init(void *pMemory, const size_t numBytes)
{
    SPI_Handle spiHandle;

    if(numBytes < sizeof(SPI_Obj))
    {
        return((SPI_Handle)NULL);
    }

    //
    // assign the handle
    //
    spiHandle = (SPI_Handle)pMemory;
    
    return(spiHandle);
}

//
// SPI_reset - 
//
void
SPI_reset(SPI_Handle spiHandle)
{
    SPI_Obj *spi = (SPI_Obj *)spiHandle;

    //
    // clear the bits
    //
    spi->SPICCR &= (~SPI_SPICCR_RESET_BITS);

    return;
}

//
// SPI_resetChannels - 
//
void
SPI_resetChannels(SPI_Handle spiHandle)
{
    SPI_Obj *spi = (SPI_Obj *)spiHandle;

    //
    // clear the bits
    //
    spi->SPIFFTX &= (~SPI_SPIFFTX_CHAN_RESET_BITS);
    
    return;
}

//
// SPI_resetRxFifo - 
//
void
SPI_resetRxFifo(SPI_Handle spiHandle)
{
    SPI_Obj *spi = (SPI_Obj *)spiHandle;

    //
    // clear the bits
    //
    spi->SPIFFRX &= (~SPI_SPIFFRX_FIFO_RESET_BITS);

    return;
}

//
// SPI_resetTxFifo - 
//
void
SPI_resetTxFifo(SPI_Handle spiHandle)
{
    SPI_Obj *spi = (SPI_Obj *)spiHandle;

    //
    // clear the bits
    //
    spi->SPIFFTX &= (~SPI_SPIFFTX_FIFO_RESET_BITS);

    return;
}

//
// SPI_setBaudRate - 
//
void
SPI_setBaudRate(SPI_Handle spiHandle, const SPI_BaudRate_e baudRate)
{
    SPI_Obj *spi = (SPI_Obj *)spiHandle;

    //
    // set the bits
    //
    spi->SPIBRR = baudRate;
    return;
}

//
// SPI_setCharLength - 
//
void
SPI_setCharLength(SPI_Handle spiHandle, const SPI_CharLength_e length)
{
    SPI_Obj *spi = (SPI_Obj *)spiHandle;

    //
    // clear the bits
    //
    spi->SPICCR &= (~SPI_SPICCR_CHAR_LENGTH_BITS);

    //
    // set the bits
    //
    spi->SPICCR |= length;

    return;
}

//
// SPI_setClkPhase - 
//
void
SPI_setClkPhase(SPI_Handle spiHandle, const SPI_ClkPhase_e clkPhase)
{
    SPI_Obj *spi = (SPI_Obj *)spiHandle;

    //
    // set the value
    //
    spi->SPICTL |= clkPhase;

    return;
}

//
// SPI_setClkPolarity - 
//
void
SPI_setClkPolarity(SPI_Handle spiHandle, const SPI_ClkPolarity_e polarity)
{
    SPI_Obj *spi = (SPI_Obj *)spiHandle;

    //
    // clear the bits
    //
    spi->SPICCR &= (~SPI_SPICCR_CLKPOL_BITS);

    //
    // set the bits
    //
    spi->SPICCR |= polarity;

    return;
}

//
// SPI_setMode - 
//
void
SPI_setMode(SPI_Handle spiHandle, const SPI_Mode_e mode)
{
    SPI_Obj *spi = (SPI_Obj *)spiHandle;

    //
    // set the bits
    //
    spi->SPICTL |= mode;

    return;
}

//
// SPI_setPriority - 
//
void
SPI_setPriority(SPI_Handle spiHandle, const SPI_Priority_e priority)
{
    SPI_Obj *spi = (SPI_Obj *)spiHandle;

    //
    // clear the field
    //
    spi->SPIPRI &= (~SPI_SPIPRI_SUSP_BITS);
    
    //
    // set the bits
    //
    spi->SPIPRI |= priority;

    return;
}

//
// SPI_setRxFifoIntLevel - 
//
void
SPI_setRxFifoIntLevel(SPI_Handle spiHandle, const SPI_FifoLevel_e fifoLevel)
{
    SPI_Obj *spi = (SPI_Obj *)spiHandle;

    //
    // clear the value
    //
    spi->SPIFFRX &= (~SPI_SPIFFRX_IL_BITS);

    //
    // set the bits
    //
    spi->SPIFFRX |= fifoLevel;

    return;
}

//
// SPI_setSteInv - 
//
void
SPI_setSteInv(SPI_Handle spiHandle, const SPI_SteInv_e steinv)
{
    SPI_Obj *spi = (SPI_Obj *)spiHandle;

    //
    // clear the field
    //
    spi->SPIPRI &= (~SPI_SPIPRI_STE_INV_BITS);
    
    //
    // set the bits
    //
    spi->SPIPRI |= steinv;

    return;
}

//
// SPI_setTriWire - 
//
void
SPI_setTriWire(SPI_Handle spiHandle, const SPI_TriWire_e triwire)
{
    SPI_Obj *spi = (SPI_Obj *)spiHandle;
    
    //
    // clear the field
    //
    spi->SPIPRI &= (~SPI_SPIPRI_TRIWIRE);
    
    //
    // set the bits
    //
    spi->SPIPRI |= triwire;

    return;
}

//
// SPI_setTxDelay - 
//
void
SPI_setTxDelay(SPI_Handle spiHandle, const uint8_t delay)
{
    SPI_Obj *spi = (SPI_Obj *)spiHandle;

    //
    // set the bits
    //
    spi->SPIFFCT = delay;

    return;
}

//
// SPI_setTxFifoIntLevel - 
//
void
SPI_setTxFifoIntLevel(SPI_Handle spiHandle, const SPI_FifoLevel_e fifoLevel)
{
    SPI_Obj *spi = (SPI_Obj *)spiHandle;

    //
    // clear the value
    //
    spi->SPIFFTX &= (~SPI_SPIFFTX_IL_BITS);

    //
    // set the bits
    //
    spi->SPIFFTX |= fifoLevel;

    return;
}

//
// End of file
//

