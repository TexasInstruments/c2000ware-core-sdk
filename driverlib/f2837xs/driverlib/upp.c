//###########################################################################
//
// FILE:   upp.c
//
// TITLE:  C28x uPP driver.
//
//###########################################################################
// $Copyright:
// Copyright (C) 2022 Texas Instruments Incorporated - http://www.ti.com
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

#include <stdbool.h>
#include <stdint.h>
#include "upp.h"

//*****************************************************************************
//
// UPP_setDMAReadThreshold
//
//*****************************************************************************
void
UPP_setDMAReadThreshold(uint32_t base, UPP_DMAChannel channel,
                        UPP_ThresholdSize size)
{
    //
    // Check the arguments.
    //
    ASSERT(UPP_isBaseValid(base));
    if(channel == UPP_DMA_CHANNEL_I)
    {
        //
        // Set DMA read threshold for channel I.
        //
        HWREGH(base + UPP_O_THCFG) = (HWREGH(base + UPP_O_THCFG)       &
                                      ~(uint16_t)UPP_THCFG_RDSIZEI_M)  |
                                     (uint16_t)size;
    }
    else
    {
        //
        // Set DMA read threshold for channel Q.
        //
        HWREGH(base + UPP_O_THCFG) = (HWREGH(base + UPP_O_THCFG)        &
                                      ~(uint16_t)UPP_THCFG_RDSIZEQ_M)   |
                                     ((uint16_t)size << UPP_THCFG_RDSIZEQ_S);
    }
}

//*****************************************************************************
//
// UPP_setDMADescriptor
//
//*****************************************************************************
void
UPP_setDMADescriptor(uint32_t base, UPP_DMAChannel channel,
                     const UPP_DMADescriptor * const desc)
{
    //
    // Check the arguments.
    //
    ASSERT(UPP_isBaseValid(base));
    if(channel == UPP_DMA_CHANNEL_I)
    {
        //
        // Sets DMA descriptors for channel I.
        //
        HWREG(base + UPP_O_CHIDESC0)  = desc->addr;
        HWREG(base + UPP_O_CHIDESC1)  = ((uint32_t)desc->byteCount   |
                                        (((uint32_t)desc->lineCount) <<
                                         UPP_CHIDESC1_LCNT_S));
        HWREGH(base + UPP_O_CHIDESC2) = desc->lineOffset;
    }
    else
    {
        //
        // Sets DMA descriptors for channel Q.
        //
        HWREG(base + UPP_O_CHQDESC0)  = desc->addr;
        HWREG(base + UPP_O_CHQDESC1)  = ((uint32_t)desc->byteCount   |
                                        (((uint32_t)desc->lineCount) <<
                                         UPP_CHQDESC1_LCNT_S));
        HWREGH(base + UPP_O_CHQDESC2) = desc->lineOffset;
    }
}

//*****************************************************************************
//
// UPP_getDMAChannelStatus
//
//*****************************************************************************
void
UPP_getDMAChannelStatus(uint32_t base, UPP_DMAChannel channel,
                        UPP_DMAChannelStatus * const status)
{
    uint32_t cntStatus;

    //
    // Check the arguments.
    //
    ASSERT(UPP_isBaseValid(base));
    if(channel == UPP_DMA_CHANNEL_I)
    {
        //
        // Return the current status for channel I.
        //
        cntStatus            = HWREG(base + UPP_O_CHIST1);
        status->curAddr      = HWREG(base + UPP_O_CHIST0);
        status->curByteCount = (uint16_t)(cntStatus & UPP_CHIDESC1_BCNT_M);
        status->curLineCount = (uint16_t)(cntStatus >> UPP_CHIDESC1_LCNT_S);
    }
    else
    {
        //
        // Return the current status for channel Q.
        //
        cntStatus            = HWREG(base + UPP_O_CHQST1);
        status->curAddr      = HWREG(base + UPP_O_CHQST0);
        status->curByteCount = (uint16_t)(cntStatus & UPP_CHQDESC1_BCNT_M);
        status->curLineCount = (uint16_t)(cntStatus >> UPP_CHQDESC1_LCNT_S);
    }
}

//*****************************************************************************
//
// UPP_isDescriptorPending
//
//*****************************************************************************
bool
UPP_isDescriptorPending(uint32_t base, UPP_DMAChannel channel)
{
    bool status;
    //
    // Check the arguments.
    //
    ASSERT(UPP_isBaseValid(base));
    if(channel == UPP_DMA_CHANNEL_I)
    {
        //
        // Return the pend status for channel I descriptor.
        //
        status = ((HWREGH(base + UPP_O_CHIST2) &
                  (uint16_t)UPP_CHIST2_PEND)  == UPP_CHIST2_PEND);
    }
    else
    {
        //
        // Return the pend status for channel Q descriptor.
        //
        status = ((HWREGH(base + UPP_O_CHQST2) &
                  (uint16_t)UPP_CHQST2_PEND)  == UPP_CHQST2_PEND);
    }
    return(status);
}

//*****************************************************************************
//
// UPP_isDescriptorActive
//
//*****************************************************************************
bool
UPP_isDescriptorActive(uint32_t base, UPP_DMAChannel channel)
{
    bool status;
    //
    // Check the arguments.
    //
    ASSERT(UPP_isBaseValid(base));
    if(channel == UPP_DMA_CHANNEL_I)
    {
        //
        // Returns active status for channel I descriptor.
        //
        status = ((HWREGH(base + UPP_O_CHIST2) &
                  (uint16_t)UPP_CHIST2_ACT)   == UPP_CHIST2_ACT);
    }
    else
    {
        //
        // Returns active status for channel Q descriptor.
        //
        status = ((HWREGH(base + UPP_O_CHQST2) &
                  (uint16_t)UPP_CHQST2_ACT)   == UPP_CHQST2_ACT);
    }
    return(status);
}

//*****************************************************************************
//
// UPP_getDMAFIFOWatermark
//
//*****************************************************************************
uint16_t
UPP_getDMAFIFOWatermark(uint32_t base, UPP_DMAChannel channel)
{
    uint16_t status;
    //
    // Check the arguments.
    //
    ASSERT(UPP_isBaseValid(base));
    if(channel == UPP_DMA_CHANNEL_I)
    {
        //
        // Return the watermark for FIFO block count for DMA Channel I.
        //
        status = ((HWREGH(base + UPP_O_CHIST2) &
                  (uint16_t)UPP_CHIST2_WM_M)  >> UPP_CHIST2_WM_S);
    }
    else
    {
        //
        // Return the watermark for FIFO block count for DMA Channel I.
        //
        status = ((HWREGH(base + UPP_O_CHQST2) &
                  (uint16_t)UPP_CHQST2_WM_M)  >> UPP_CHQST2_WM_S);
    }
    return(status);
}

//*****************************************************************************
//
// UPP_readRxMsgRAM
//
//*****************************************************************************
void
UPP_readRxMsgRAM(uint32_t rxBase, uint16_t array[], uint16_t length,
                 uint16_t offset)
{
    uint16_t i;
    //
    // Check the arguments.
    //
    ASSERT(UPP_isRxBaseValid(rxBase));
    ASSERT((length + offset) < UPP_RX_MSGRAM_MAX_SIZE);

    for(i = 0U; i < length; i++)
    {
        //
        // Read one 16-bit word.
        //
        array[i] = HWREGH(rxBase + offset + i);
    }
}

//*****************************************************************************
//
// UPP_writeTxMsgRAM
//
//*****************************************************************************
void
UPP_writeTxMsgRAM(uint32_t txBase, const uint16_t array[], uint16_t length,
                  uint16_t offset)
{
    uint16_t i;
    //
    // Check the arguments.
    //
    ASSERT(UPP_isTxBaseValid(txBase));
    ASSERT((length + offset) < UPP_TX_MSGRAM_MAX_SIZE);

    for(i = 0U; i < length; i++)
    {
        //
        // Write one 16-bit word.
        //
        HWREGH(txBase + offset + i) = array[i];
    }
}
