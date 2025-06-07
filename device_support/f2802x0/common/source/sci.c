//#############################################################################
//
//! \file   f2802x0/common/source/sci.c
//!
//! \brief  Contains the various functions related to the serial 
//!         communications interface (SCI) object
//
//  Group:          C2000
//  Target Device:  TMS320F2802x0
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
#include "sci.h"

//
// SCI_clearAutoBaudDetect - 
//
void
SCI_clearAutoBaudDetect(SCI_Handle sciHandle)
{
    SCI_Obj *sci = (SCI_Obj *)sciHandle;
    
    //
    // set the bits
    //
    sci->SCIFFCT |= SCI_SCIFFCT_ABDCLR_BITS;

    return;
}

//
// SCI_clearRxFifoOvf -
//
void
SCI_clearRxFifoOvf(SCI_Handle sciHandle)
{
    SCI_Obj *sci = (SCI_Obj *)sciHandle;

    //
    // set the bits
    //
    sci->SCIFFRX |= SCI_SCIFFRX_FIFO_OVFCLR_BITS;

    return;
}

//
// SCI_clearRxFifoInt -
//
void
SCI_clearRxFifoInt(SCI_Handle sciHandle)
{
    SCI_Obj *sci = (SCI_Obj *)sciHandle;

    //
    // set the bits
    //
    sci->SCIFFRX |= SCI_SCIFFRX_INTCLR_BITS;

    return;
}

//
// SCI_clearTxFifoInt -
//
void
SCI_clearTxFifoInt(SCI_Handle sciHandle)
{
    SCI_Obj *sci = (SCI_Obj *)sciHandle;

    //
    // set the bits
    //
    sci->SCIFFTX |= SCI_SCIFFTX_INTCLR_BITS;

    return;
}

//
// SCI_disable -
//
void
SCI_disable(SCI_Handle sciHandle)
{
    SCI_Obj *sci = (SCI_Obj *)sciHandle;

    //
    // clear the bits
    //
    sci->SCICTL1 &= (~SCI_SCICTL1_RESET_BITS);

    return;
}

//
// SCI_disableAutoBaudAlign - 
//
void
SCI_disableAutoBaudAlign(SCI_Handle sciHandle)
{
    SCI_Obj *sci = (SCI_Obj *)sciHandle;

    //
    // clear the bits
    //
    sci->SCIFFCT &= (~SCI_SCIFFCT_CDC_BITS);

    return;
}

//
// SCI_disableLoopBack - 
//
void
SCI_disableLoopBack(SCI_Handle sciHandle)
{
    SCI_Obj *sci = (SCI_Obj *)sciHandle;

    //
    // clear the bits
    //
    sci->SCICCR &= (~SCI_SCICCR_LB_ENA_BITS);

    return;
}

//
// SCI_disableParity - 
//
void
SCI_disableParity(SCI_Handle sciHandle)
{
    SCI_Obj *sci = (SCI_Obj *)sciHandle;

    //
    // clear the bits
    //
    sci->SCICCR &= (~SCI_SCICCR_PARITY_ENA_BITS);

    return;
}

//
// SCI_disableRx - 
//
void
SCI_disableRx(SCI_Handle sciHandle)
{
    SCI_Obj *sci = (SCI_Obj *)sciHandle;

    //
    // clear the bits
    //
    sci->SCICTL1 &= (~SCI_SCICTL1_RXENA_BITS);

    return;
}

//
// SCI_disableRxErrorInt - 
//
void
SCI_disableRxErrorInt(SCI_Handle sciHandle)
{
    SCI_Obj *sci = (SCI_Obj *)sciHandle;

    //
    // clear the bits
    //
    sci->SCICTL1 &= (~SCI_SCICTL1_RX_ERR_INT_ENA_BITS);

    return;
}

//
// SCI_disableRxFifoInt - 
//
void
SCI_disableRxFifoInt(SCI_Handle sciHandle)
{
    SCI_Obj *sci = (SCI_Obj *)sciHandle;

    //
    // clear the bits
    //
    sci->SCIFFRX &= (~SCI_SCIFFRX_IENA_BITS);

    return;
}

//
// SCI_disableRxInt  - 
//
void
SCI_disableRxInt(SCI_Handle sciHandle)
{
    SCI_Obj *sci = (SCI_Obj *)sciHandle;

    //
    // clear the bits
    //
    sci->SCICTL2 &= (~SCI_SCICTL2_RX_INT_ENA_BITS);

    return;
}

//
// SCI_disableSleep - 
//
void
SCI_disableSleep(SCI_Handle sciHandle)
{
    SCI_Obj *sci = (SCI_Obj *)sciHandle;

    //
    // clear the bits
    //
    sci->SCICTL1 &= (~SCI_SCICTL1_SLEEP_BITS);

    return;
}

//
// SCI_disableTx - 
//
void
SCI_disableTx(SCI_Handle sciHandle)
{
    SCI_Obj *sci = (SCI_Obj *)sciHandle;

    //
    // clear the bits
    //
    sci->SCICTL1 &= (~SCI_SCICTL1_TXENA_BITS);

    return;
}

//
// SCI_disableFifoEnh -
//
void
SCI_disableFifoEnh(SCI_Handle sciHandle)
{
    SCI_Obj *sci = (SCI_Obj *)sciHandle;

    //
    // clear the bits
    //
    sci->SCIFFTX &= (~SCI_SCIFFTX_FIFO_ENA_BITS);

    return;
}

//
// SCI_disableTxFifoInt - 
//
void
SCI_disableTxFifoInt(SCI_Handle sciHandle)
{
    SCI_Obj *sci = (SCI_Obj *)sciHandle;

    //
    // clear the bits
    //
    sci->SCIFFTX &= (~SCI_SCIFFTX_IENA_BITS);

    return;
}

//
// SCI_disableTxInt -
//
void
SCI_disableTxInt(SCI_Handle sciHandle)
{
    SCI_Obj *sci = (SCI_Obj *)sciHandle;

    //
    // clear the bits
    //
    sci->SCICTL2 &= (~SCI_SCICTL2_TX_INT_ENA_BITS);

    return;
}

//
// SCI_disableTxWake - 
//
void
SCI_disableTxWake(SCI_Handle sciHandle)
{
    SCI_Obj *sci = (SCI_Obj *)sciHandle;

    //
    // clear the bits
    //
    sci->SCICTL1 &= (~SCI_SCICTL1_TXWAKE_BITS);

    return;
}

//
// SCI_enable - 
//
void
SCI_enable(SCI_Handle sciHandle)
{
    SCI_Obj *sci = (SCI_Obj *)sciHandle;

    //
    // set the bits
    //
    sci->SCICTL1 |= SCI_SCICTL1_RESET_BITS;

    return;
}

//
// SCI_enableAutoBaudAlign -
//
void
SCI_enableAutoBaudAlign(SCI_Handle sciHandle)
{
    SCI_Obj *sci = (SCI_Obj *)sciHandle;

    //
    // set the bits
    //
    sci->SCIFFCT |= SCI_SCIFFCT_CDC_BITS;

    return;
}

//
// SCI_enableLoopBack - 
//
void
SCI_enableLoopBack(SCI_Handle sciHandle)
{
    SCI_Obj *sci = (SCI_Obj *)sciHandle;

    //
    // set the bits
    //
    sci->SCICCR |= SCI_SCICCR_LB_ENA_BITS;

    return;
}

//
// SCI_enableParity - 
//
void
SCI_enableParity(SCI_Handle sciHandle)
{
    SCI_Obj *sci = (SCI_Obj *)sciHandle;

    //
    // set the bits
    //
    sci->SCICCR |= SCI_SCICCR_PARITY_ENA_BITS;

    return;
}

//
// SCI_enableRx - 
//
void
SCI_enableRx(SCI_Handle sciHandle)
{
    SCI_Obj *sci = (SCI_Obj *)sciHandle;

    //
    // set the bits
    //
    sci->SCICTL1 |= SCI_SCICTL1_RXENA_BITS;

    return;
}

//
// SCI_enableRxErrorInt - 
//
void
SCI_enableRxErrorInt(SCI_Handle sciHandle)
{
    SCI_Obj *sci = (SCI_Obj *)sciHandle;

    //
    // set the bits
    //
    sci->SCICTL1 |= SCI_SCICTL1_RX_ERR_INT_ENA_BITS;

    return;
}

//
// SCI_enableRxInt - 
//
void
SCI_enableRxInt(SCI_Handle sciHandle)
{
    SCI_Obj *sci = (SCI_Obj *)sciHandle;

    //
    // set the bits
    //
    sci->SCICTL2 |= SCI_SCICTL2_RX_INT_ENA_BITS;

    return;
}

//
// SCI_enableSleep - 
//
void
SCI_enableSleep(SCI_Handle sciHandle)
{
    SCI_Obj *sci = (SCI_Obj *)sciHandle;

    //
    // set the bits
    //
    sci->SCICTL1 |= SCI_SCICTL1_SLEEP_BITS;

    return;
}

//
// SCI_enableRxFifoInt - 
//
void
SCI_enableRxFifoInt(SCI_Handle sciHandle)
{
    SCI_Obj *sci = (SCI_Obj *)sciHandle;

    //
    // set the bits
    //
    sci->SCIFFRX |= SCI_SCIFFRX_IENA_BITS;

    return;
}

//
// SCI_enableTx - 
//
void
SCI_enableTx(SCI_Handle sciHandle)
{
    SCI_Obj *sci = (SCI_Obj *)sciHandle;

    //
    // set the bits
    //
    sci->SCICTL1 |= SCI_SCICTL1_TXENA_BITS;

    return;
}

//
// SCI_enableFifoEnh -
//
void
SCI_enableFifoEnh(SCI_Handle sciHandle)
{
    SCI_Obj *sci = (SCI_Obj *)sciHandle;

    //
    // set the bits
    //
    sci->SCIFFTX |= SCI_SCIFFTX_FIFO_ENA_BITS;

    return;
}

//
// SCI_enableTxFifoInt - 
//
void
SCI_enableTxFifoInt(SCI_Handle sciHandle)
{
    SCI_Obj *sci = (SCI_Obj *)sciHandle;

    //
    // set the bits
    //
    sci->SCIFFTX |= SCI_SCIFFTX_IENA_BITS;

    return;
}

//
// SCI_enableTxInt - 
//
void
SCI_enableTxInt(SCI_Handle sciHandle)
{
    SCI_Obj *sci = (SCI_Obj *)sciHandle;

    //
    // set the bits
    //
    sci->SCICTL2 |= SCI_SCICTL2_TX_INT_ENA_BITS;

    return;
}

//
// SCI_enableTxWake - 
//
void
SCI_enableTxWake(SCI_Handle sciHandle)
{
    SCI_Obj *sci = (SCI_Obj *)sciHandle;

    //
    // set the bits
    //
    sci->SCICTL1 |= SCI_SCICTL1_TXWAKE_BITS;

    return;
}

//
// SCI_getDataBlocking -
//
uint16_t
SCI_getDataBlocking(SCI_Handle sciHandle)
{
    SCI_Obj *sci = (SCI_Obj *)sciHandle;

    while(SCI_isRxDataReady(sciHandle) != true)
    {
        
    }

    return (sci->SCIRXBUF);
}

//
// SCI_getDataNonBlocking -
//
uint16_t
SCI_getDataNonBlocking(SCI_Handle sciHandle, uint16_t * success)
{
    SCI_Obj *sci = (SCI_Obj *)sciHandle;

    if(SCI_isRxDataReady(sciHandle))
    {
        *success = true;
        return (sci->SCIRXBUF); 
    }
    
    *success = false;
    return (NULL);
}

//
// SCI_getRxFifoStatus - 
//
SCI_FifoStatus_e
SCI_getRxFifoStatus(SCI_Handle sciHandle)
{
    SCI_Obj *sci = (SCI_Obj *)sciHandle;
    SCI_FifoStatus_e status;

    //
    // get the status
    //
    status = (SCI_FifoStatus_e)(sci->SCIFFRX & SCI_SCIFFRX_FIFO_ST_BITS);

    return(status);
}

//
// SCI_getTxFifoStatus - 
//
SCI_FifoStatus_e
SCI_getTxFifoStatus(SCI_Handle sciHandle)
{
    SCI_Obj *sci = (SCI_Obj *)sciHandle;
    SCI_FifoStatus_e status;

    //
    // get the status
    //
    status = (SCI_FifoStatus_e)(sci->SCIFFTX & SCI_SCIFFTX_FIFO_ST_BITS);

    return(status);
}

//
// SCI_init - 
//
SCI_Handle
SCI_init(void *pMemory, const size_t numBytes)
{
    SCI_Handle sciHandle;

    if(numBytes < sizeof(SCI_Obj))
    {
        return((SCI_Handle)NULL);
    }

    //
    // assign the handle
    //
    sciHandle = (SCI_Handle)pMemory;
    
    return(sciHandle);
}

//
// SCI_putDataBlocking - 
//
void
SCI_putDataBlocking(SCI_Handle sciHandle, uint16_t data)
{
    SCI_Obj *sci = (SCI_Obj *)sciHandle;

    while(SCI_isTxReady(sciHandle) != true)
    {
        
    }
    
    //
    // write the data
    //
    sci->SCITXBUF = data;
    
}

//
// SCI_putDataNonBlocking - 
//
uint16_t
SCI_putDataNonBlocking(SCI_Handle sciHandle, uint16_t data)
{
    SCI_Obj *sci = (SCI_Obj *)sciHandle;

    if(SCI_isTxReady(sciHandle))
    {
        //
        // write the data
        //
        sci->SCITXBUF = data;
        
        return (true);
    }

    return (false);
}

//
// SCI_reset -
//
void
SCI_reset(SCI_Handle sciHandle)
{
    SCI_Obj *sci = (SCI_Obj *)sciHandle;

    //
    // clear the bits
    //
    sci->SCICTL1 &= (~SCI_SCICTL1_RESET_BITS);

    return;
}

//
// SCI_resetChannels - 
//
void
SCI_resetChannels(SCI_Handle sciHandle)
{
    SCI_Obj *sci = (SCI_Obj *)sciHandle;

    //
    // clear the bits
    //
    sci->SCIFFTX &= (~SCI_SCIFFTX_CHAN_RESET_BITS);
    asm(" nop");
    sci->SCIFFTX |= (uint16_t)(SCI_SCIFFTX_CHAN_RESET_BITS);
    
    return;
}

//
// SCI_resetRxFifo -
//
void
SCI_resetRxFifo(SCI_Handle sciHandle)
{
    SCI_Obj *sci = (SCI_Obj *)sciHandle;

    //
    // clear the bits
    //
    sci->SCIFFRX &= (~SCI_SCIFFRX_FIFO_RESET_BITS);
    asm(" nop");
    sci->SCIFFRX |= SCI_SCIFFRX_FIFO_RESET_BITS;

    return;
}

//
// SCI_resetTxFifo -
//
void
SCI_resetTxFifo(SCI_Handle sciHandle)
{
    SCI_Obj *sci = (SCI_Obj *)sciHandle;

    //
    // clear the bits
    //
    sci->SCIFFTX &= (~SCI_SCIFFTX_FIFO_RESET_BITS);
    asm(" nop");
    sci->SCIFFTX |= SCI_SCIFFTX_FIFO_RESET_BITS;

    return;
}

//
// SCI_setBaudRate -
//
void
SCI_setBaudRate(SCI_Handle sciHandle, const SCI_BaudRate_e baudRate)
{
    SCI_Obj *sci = (SCI_Obj *)sciHandle;

    //
    // set the bits
    //
    sci->SCIHBAUD = ((uint16_t)baudRate >> 8);
    sci->SCILBAUD = baudRate & 0xFF;

    return;
}

//
// SCI_setCharLength -
//
void
SCI_setCharLength(SCI_Handle sciHandle, const SCI_CharLength_e charLength)
{
    SCI_Obj *sci = (SCI_Obj *)sciHandle;

    //
    // clear the bits
    //
    sci->SCICCR &= (~SCI_SCICCR_CHAR_LENGTH_BITS);

    //
    // set the bits
    //
    sci->SCICCR |= charLength;

    return;
}

//
// SCI_setMode -
//
void
SCI_setMode(SCI_Handle sciHandle, const SCI_Mode_e mode)
{
    SCI_Obj *sci = (SCI_Obj *)sciHandle;

    //
    // clear the bits
    //
    sci->SCICCR &= (~SCI_SCICCR_MODE_BITS);

    //
    // set the bits
    //
    sci->SCICCR |= mode;

    return;
}

//
// SCI_setNumStopBits -
//
void
SCI_setNumStopBits(SCI_Handle sciHandle, const SCI_NumStopBits_e numBits)
{
    SCI_Obj *sci = (SCI_Obj *)sciHandle;

    //
    // clear the bits
    //
    sci->SCICCR &= (~SCI_SCICCR_STOP_BITS);

    //
    // set the bits
    //
    sci->SCICCR |= numBits;

    return;
}

//
// SCI_setPriority -
//
void
SCI_setPriority(SCI_Handle sciHandle, const SCI_Priority_e priority)
{
    SCI_Obj *sci = (SCI_Obj *)sciHandle;

    //
    // set the bits
    //
    sci->SCIPRI = priority;

    return;
}

//
// SCI_setParity -
//
void
SCI_setParity(SCI_Handle sciHandle, const SCI_Parity_e parity)
{
    SCI_Obj *sci = (SCI_Obj *)sciHandle;

    //
    // clear the bits
    //
    sci->SCICCR &= (~SCI_SCICCR_PARITY_BITS);

    //
    // set the bits
    //
    sci->SCICCR |= parity;

    return;
}

//
// SCI_setTxDelay -
//
void
SCI_setTxDelay(SCI_Handle sciHandle, const uint8_t delay)
{
    SCI_Obj *sci = (SCI_Obj *)sciHandle;

    //
    // clear the bits
    //
    sci->SCIFFCT &= (~SCI_SCIFFCT_DELAY_BITS); 

    //
    // set the bits
    //
    sci->SCIFFCT |= delay;

    return;
}

//
// SCI_setRxFifoIntLevel -
//
void
SCI_setRxFifoIntLevel(SCI_Handle sciHandle, const SCI_FifoLevel_e fifoLevel)
{
    SCI_Obj *sci = (SCI_Obj *)sciHandle;

    //
    // clear the value
    //
    sci->SCIFFRX &= (~SCI_SCIFFRX_IL_BITS);

    //
    // set the bits
    //
    sci->SCIFFRX |= fifoLevel;

    return;
}

//
// SCI_setTxFifoIntLevel
//
void
SCI_setTxFifoIntLevel(SCI_Handle sciHandle, const SCI_FifoLevel_e fifoLevel)
{
    SCI_Obj *sci = (SCI_Obj *)sciHandle;

    //
    // clear the value
    //
    sci->SCIFFTX &= (~SCI_SCIFFTX_IL_BITS);

    //
    // set the bits
    //
    sci->SCIFFTX |= fifoLevel;

    return;
}

//
// End of file
//

