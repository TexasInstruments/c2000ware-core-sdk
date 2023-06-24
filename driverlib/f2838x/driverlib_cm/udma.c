//###########################################################################
//
// FILE:   udma.c
//
// TITLE:  Driver for the micro-DMA controller.
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

#include "udma.h"

//*****************************************************************************
//
// UDMA_enableChannelAttribute()
//
//*****************************************************************************
void
UDMA_enableChannelAttribute(uint32_t base, uint32_t channelNum,
                            uint32_t channelAttr)
{
    //
    // Check the arguments.
    //
    ASSERT(UDMA_isBaseValid(base));
    ASSERT((channelNum & 0xFFFFU) < 32U);
    ASSERT((channelAttr & ~(UDMA_CH_ATTR_USEBURST | UDMA_CH_ATTR_ALTSELECT |
            UDMA_CH_ATTR_HIGH_PRIORITY | UDMA_CH_ATTR_REQMASK)) == 0U);


    //
    // Set the useburst bit for this channel if set in channelAttr.
    //
    if((channelAttr & UDMA_CH_ATTR_USEBURST) == UDMA_CH_ATTR_USEBURST)
    {
        HWREG(base + UDMA_O_DMAUSEBURSTSET) = 1U << channelNum;
    }

    //
    // Set the alternate control select bit for this channel,
    // if set in channelAttr.
    //
    if((channelAttr & UDMA_CH_ATTR_ALTSELECT) == UDMA_CH_ATTR_ALTSELECT)
    {
        HWREG(base + UDMA_O_DMAALTSET) = 1U << channelNum;
    }

    //
    // Set the high priority bit for this channel, if set in channelAttr.
    //
    if((channelAttr & UDMA_CH_ATTR_HIGH_PRIORITY) == UDMA_CH_ATTR_HIGH_PRIORITY)
    {
        HWREG(base + UDMA_O_DMAPRIOSET) = 1U << channelNum;
    }

    //
    // Set the request mask bit for this channel, if set in channelAttr.
    //
    if((channelAttr & UDMA_CH_ATTR_REQMASK) == UDMA_CH_ATTR_REQMASK)
    {
        HWREG(base + UDMA_O_DMAREQMASKSET) = 1U << channelNum;
    }
}

//*****************************************************************************
//
// UDMA_disableChannelAttribute()
//
//*****************************************************************************
void
UDMA_disableChannelAttribute(uint32_t base, uint32_t channelNum,
                             uint32_t channelAttr)
{
    //
    // Check the arguments.
    //
    ASSERT(UDMA_isBaseValid(base));
    ASSERT((channelNum & 0xFFFFU) < 32U);
    ASSERT((channelAttr & ~(UDMA_CH_ATTR_USEBURST | UDMA_CH_ATTR_ALTSELECT |
            UDMA_CH_ATTR_HIGH_PRIORITY | UDMA_CH_ATTR_REQMASK)) == 0U);

    //
    // Clear the useburst bit for this channel if set in channelAttr.
    //
    if((channelAttr & UDMA_CH_ATTR_USEBURST) == UDMA_CH_ATTR_USEBURST)
    {
        HWREG(base + UDMA_O_DMAUSEBURSTCLR) = 1U << channelNum;
    }

    //
    // Clear the alternate control select bit for this channel, if set in
    // channelAttr.
    //
    if((channelAttr & UDMA_CH_ATTR_ALTSELECT) == UDMA_CH_ATTR_ALTSELECT)
    {
        HWREG(base + UDMA_O_DMAALTCLR) = 1U << channelNum;
    }

    //
    // Clear the high priority bit for this channel, if set in channelAttr.
    //
    if((channelAttr & UDMA_CH_ATTR_HIGH_PRIORITY) == UDMA_CH_ATTR_HIGH_PRIORITY)
    {
        HWREG(base + UDMA_O_DMAPRIOCLR) = 1U << channelNum;
    }

    //
    // Clear the request mask bit for this channel, if set in channelAttr.
    //
    if((channelAttr & UDMA_CH_ATTR_REQMASK) == UDMA_CH_ATTR_REQMASK)
    {
        HWREG(base + UDMA_O_DMAREQMASKCLR) = 1U << channelNum;
    }
}

//*****************************************************************************
//
// UDMA_getChannelAttribute()
//
//*****************************************************************************
uint32_t
UDMA_getChannelAttribute(uint32_t base, uint32_t channelNum)
{
    uint32_t channelAttr = 0U;
    uint32_t offset = 1U << channelNum;

    //
    // Check the arguments.
    //
    ASSERT(UDMA_isBaseValid(base));
    ASSERT((channelNum & 0xFFFFU) < 32U);

    //
    // Check to see if useburst bit is set for this channel.
    //
    if((HWREG(base + UDMA_O_DMAUSEBURSTSET) & offset) == offset)
    {
        channelAttr |= UDMA_CH_ATTR_USEBURST;
    }

    //
    // Check to see if the alternate control bit is set for this channel.
    //
    if((HWREG(base + UDMA_O_DMAALTSET) & offset) == offset)
    {
        channelAttr |= UDMA_CH_ATTR_ALTSELECT;
    }

    //
    // Check to see if the high priority bit is set for this channel.
    //
    if((HWREG(base + UDMA_O_DMAPRIOSET) & offset) == offset)
    {
        channelAttr |= UDMA_CH_ATTR_HIGH_PRIORITY;
    }

    //
    // Check to see if the request mask bit is set for this channel.
    //
    if((HWREG(base + UDMA_O_DMAREQMASKSET) & offset) == offset)
    {
        channelAttr |= UDMA_CH_ATTR_REQMASK;
    }

    //
    // Return the configuration flags.
    //
    return(channelAttr);
}

//*****************************************************************************
//
// UDMA_setChannelTransferParams()
//
//*****************************************************************************
extern void
UDMA_setChannelTransferParams(uint32_t base, uint32_t index, void *srcAddr,
                              void *dstAddr, uint32_t transferMode,
                              uint32_t transferSize)
{
    UDMA_ControlTable *controlTable;
    uint32_t chControlAttr;
    uint32_t addrInc;
    uint32_t bufferBytes;
    uint32_t txModeTemp, srcAddrTemp, dstAddrTemp;

    //
    // Check the arguments.
    //
    ASSERT(UDMA_isBaseValid(base));
    ASSERT(index < 64U);
    ASSERT(HWREG(base + UDMA_O_DMACTLBASE) != 0U);
    ASSERT(transferMode <= UDMA_MODE_PER_SCATTER_GATHER);
    ASSERT((uint32_t)srcAddr >= 0x20000000U);
    ASSERT((uint32_t)dstAddr >= 0x20000000U);
    ASSERT((transferSize != 0U) && (transferSize <= 1024U));

    //
    // Get the base address of the control table.
    //
    controlTable = (UDMA_ControlTable *)HWREG(base + UDMA_O_DMACTLBASE);
    ASSERT(controlTable != 0U);

    //
    // Get the current control word value and mask off the mode and size
    // fields.
    //
    chControlAttr = (controlTable[index].chControlAttr &
                   ~(UDMA_DMACHCTL_XFERSIZE_M | UDMA_DMACHCTL_XFERMODE_M));

    //
    // Adjust the mode if the alt control structure is selected.
    //
    if((index & UDMA_ALT_SELECT) == UDMA_ALT_SELECT)
    {
        if((transferMode == UDMA_MODE_MEM_SCATTER_GATHER) ||
           (transferMode == UDMA_MODE_PER_SCATTER_GATHER))
        {
            txModeTemp = transferMode | UDMA_MODE_ALT_SELECT;
        }
        else
        {
            txModeTemp = transferMode;
        }
    }
    else
    {
        txModeTemp = transferMode;
    }

    //
    // Set the transfer size and mode in the control word (but don't write the
    // control word yet as it could kick off a transfer).
    //
    chControlAttr |= txModeTemp |
                     ((transferSize - 1U) << UDMA_DMACHCTL_XFERSIZE_S);

    //
    // Get the address increment value for the source, from the control word.
    //
    addrInc = (chControlAttr & UDMA_DMACHCTL_SRCINC_M);

    //
    // Compute the ending source address of the transfer.  If the source
    // increment is set to none, then the ending address is the same as the
    // beginning.
    //
    if(addrInc != UDMA_SRC_INC_NONE)
    {
        addrInc = addrInc >> UDMA_DMACHCTL_SRCINC_S;
        bufferBytes = transferSize << addrInc;
        srcAddrTemp = ((uint32_t)srcAddr + bufferBytes - 1U);
    }
    else
    {
        srcAddrTemp = (uint32_t)srcAddr;
    }

    //
    // Load the source ending address into the control block.
    //
    controlTable[index].srcEndAddr = (void *)srcAddrTemp;

    //
    // Get the address increment value for the destination, from the control
    // word.
    //
    addrInc = chControlAttr & UDMA_DMACHCTL_DSTINC_M;

    //
    // Compute the ending destination address of the transfer.  If the
    // destination increment is set to none, then the ending address is the
    // same as the beginning.
    //
    if(addrInc != UDMA_DST_INC_NONE)
    {
        //
        // There is a special case if this is setting up a scatter-gather
        // transfer.  The destination pointer must point to the end of
        // the alternate structure for this channel instead of calculating
        // the end of the buffer in the normal way.
        //
        if((transferMode == UDMA_MODE_MEM_SCATTER_GATHER) ||
           (transferMode == UDMA_MODE_PER_SCATTER_GATHER))
        {
            dstAddrTemp = (uint32_t)&controlTable[index |
                                                  UDMA_ALT_SELECT].spare;
        }

        //
        // Not a scatter-gather transfer, calculate end pointer normally.
        //
        else
        {
            addrInc = addrInc >> UDMA_DMACHCTL_DSTINC_S;
            bufferBytes = transferSize << addrInc;
            dstAddrTemp = ((uint32_t)dstAddr + bufferBytes - 1U);
        }
    }
    else
    {
        dstAddrTemp = (uint32_t)dstAddr;
    }

    //
    // Load the destination ending address into the control block.
    //
    controlTable[index].dstEndAddr = (void *)dstAddrTemp;

    //
    // Write the new control word value.
    //
    controlTable[index].chControlAttr = chControlAttr;
}

//*****************************************************************************
//
// UDMA_getChannelTransferSize()
//
//*****************************************************************************
uint32_t
UDMA_getChannelTransferSize(uint32_t base, uint32_t index)
{
    UDMA_ControlTable *controlTable;
    uint32_t chControlAttr, txSize;

    //
    // Check the arguments.
    //
    ASSERT(UDMA_isBaseValid(base));
    ASSERT((index & 0xFFFFU) < 64U);
    ASSERT(HWREG(base + UDMA_O_DMACTLBASE) != 0U);

    //
    // Get the base address of the control table.
    //
    controlTable = (UDMA_ControlTable *)HWREG(base + UDMA_O_DMACTLBASE);
    ASSERT(controlTable != 0U);

    //
    // Get the current control word value and mask off all but the size field
    // and the mode field.
    //
    chControlAttr = (controlTable[index].chControlAttr &
                   (UDMA_DMACHCTL_XFERSIZE_M | UDMA_DMACHCTL_XFERMODE_M));

    //
    // If the size field and mode field are 0 then the transfer is finished
    // and there are no more items to transfer
    //
    if(chControlAttr == 0U)
    {
        txSize = 0U;
    }

    //
    // Otherwise, if either the size field or more field is non-zero, then
    // not all the items have been transferred.
    //
    else
    {
        //
        // Shift the size field and add one, then return to user.
        //
        txSize = (chControlAttr >> UDMA_DMACHCTL_XFERSIZE_S) + 1U;
    }
    return(txSize);
}
//*****************************************************************************
//
// UDMA_setChannelScatterGatherMode()
//
//*****************************************************************************
void
UDMA_setChannelScatterGatherMode(uint32_t base, uint32_t channelNum,
                                uint32_t taskCount, UDMA_ControlTable *taskList,
                                bool isPeriphScatterGather)
{
    volatile UDMA_ControlTable *controlTable;
    UDMA_ControlTable *taskTable;

    //
    // Check the parameters
    //
    ASSERT(UDMA_isBaseValid(base));
    ASSERT(channelNum < 32U);
    ASSERT(HWREG(base + UDMA_O_DMACTLBASE) != 0U);
    ASSERT(taskList != 0U);
    ASSERT((taskCount != 0U) && (taskCount <= 1024U));

    //
    // Get the base address of the control table.
    //
    controlTable = (UDMA_ControlTable *)HWREG(base + UDMA_O_DMACTLBASE);

    //
    // Get a handy pointer to the task list.
    //
    taskTable = taskList;
    ASSERT(taskTable);

    //
    // Compute the ending address for the source pointer.  This address is the
    // last element of the last task in the task table.
    //
    controlTable[channelNum].srcEndAddr = &taskTable[taskCount - 1U].spare;

    //
    // Compute the ending address for the destination pointer.  This address
    // is the end of the alternate structure for this channel.
    //
    controlTable[channelNum].dstEndAddr = &controlTable[channelNum |
                                          UDMA_ALT_SELECT].spare;

    //
    // Compute the control word.  Most configurable items are fixed for
    // scatter-gather.  Item and increment sizes are all 32-bit and arb
    // size must be 4.  The count is the number of items in the task list
    // times 4 (4 words per task).
    //
    controlTable[channelNum].chControlAttr =
              (UDMA_DST_INC_32 | UDMA_SIZE_32 | UDMA_SRC_INC_32 | UDMA_ARB_4   |
               ((uint32_t)((taskCount * 4U) - 1U) << UDMA_DMACHCTL_XFERSIZE_S) |
               ((isPeriphScatterGather == true) ? UDMA_MODE_PER_SCATTER_GATHER :
                UDMA_MODE_MEM_SCATTER_GATHER));

    //
    // Scatter-gather operations can leave the alt bit set.  So if doing
    // back to back scatter-gather transfers, the second attempt may not
    // work correctly because the alt bit is set.  Therefore, clear the
    // alt bit here to ensure that it is always cleared before a new SG
    // transfer is started.
    //
    HWREG(base + UDMA_O_DMAALTCLR) = 1U << channelNum;
}
