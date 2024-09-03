//#############################################################################
//
// FILE:   dmpu_ex1_secure_mem_transfer.c
//
// TITLE:  Demonstrate CM-MPU usage for uDMA transfers
//
//! \addtogroup driver_example_cm_list
//! <h1> Demonstrate DMPU usage. </h1>
//!
//! This example demonstrates how to configure CM-MPU for uDMA transfer.
//! uDMA is configured to transfer data between two memory regions and
//! DMPU is configured to demonstrate memory access protection in uDMA
//! associated memory regions
//!
//! The following memory map is set up:
//! -\b Region 0 - uDMA source buffer
//! -\b Region 1 - uDMA control table
//! -\b Region 2 - uDMA destination buffer
//!
//! \b External \b Connections \n
//!  - None
//!
//! \b Watch \b Variables \n
//! - \b faultCount     - Count for uDMA access faults. This should be non zero.
//! - \b errCountGlobal - Error Counter. This should be zero.
//! - \b memTransferCount - Count of memory uDMA transfer blocks
//!
//
//#############################################################################
//
//
// 
// C2000Ware v5.03.00.00
//
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
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
#include "driverlib_cm.h"
#include "cm.h"

//
// Defines
//
#define UDMA_SW_INT            41U //!< Interrupt Number for UDMASWINT
#define UDMA_ERR_INT           42U //!< Interrupt Number for UDMAERRINT
#define SYSTICK_INT            15U //!< Interrupt Number for SYSTICKINT

//
// The size of the memory transfer source and destination buffers (in words).
//
#define MEM_BUFFER_SIZE         256U

//
// Globals
//

//
// The source and destination buffers used for memory transfers.
//
static uint32_t srcBuffer[MEM_BUFFER_SIZE]; //!< Source Buffer
static uint32_t dstBuffer[MEM_BUFFER_SIZE]; //!< Destination Buffer

//
// The count of uDMA errors.  This value is incremented by the uDMA error
// handler.
//
static uint32_t errCountDMA = 0U, faultCount = 0U;
static volatile uint32_t memFaultAdd, busFaultAdd, val;
static volatile uint32_t faultStatus;
static volatile uint32_t intFlagStatus, accVioAdd;

//
// The count of times the uDMA interrupt occurred but the uDMA transfer was not
// complete.  This should remain 0.
//
static uint32_t badInterruptCount = 0;

//
// Error Counter. This should be zero for the successful transfers.
//
static uint32_t errCountGlobal = 0;

//
// The count of memory uDMA transfer blocks.  This value is incremented by the
// uDMA interrupt handler whenever a memory block transfer is completed.
//
static uint32_t memTransferCount = 0;

//
// The control table used by the uDMA controller.  This table must be aligned
// to a 1024 byte boundary.
//
#pragma DATA_ALIGN(ucControlTable, 64)
UDMA_ControlTable ucControlTable[64];

//
// Function prototypes
//
void uDMAErrorISR(void);
void uDMAIntISR(void);
void initSWTransfer(void);

//
// Main
//
void main(void)
{
     uint32_t index;

    //
    // Initialize device clock and peripherals
    //
    CM_init();

    //
    // Fill the source memory buffer with a simple incrementing pattern.
    //
    for(index = 0; index < MEM_BUFFER_SIZE; index++)
    {
        srcBuffer[index] = index;
    }

    //
    // Register interrupt handlers in the RAM vector table.
    //
    Interrupt_registerHandler(UDMA_SW_INT, uDMAIntISR);
    Interrupt_registerHandler(UDMA_ERR_INT, uDMAErrorISR);

    //
    // Enable the uDMA controller error interrupt.  This interrupt will occur
    // if there is a bus error during a transfer.
    //
    Interrupt_enable(UDMA_ERR_INT);

    //
    // Enable the uDMA controller.
    //
    UDMA_enable(UDMA_BASE);

    //
    // Point at the control table to use for channel control structures.
    //
    UDMA_setControlBase(UDMA_BASE, ucControlTable);

    //
    // Setting up MPU regions for source, destination buffers and controltable
    // array.
    //

    //
    // All regions are configured with required access. No violation should be
    // observed while writing to srcBuffer in ISR as CM-MPU.
    //
    CMMPU_setRegionAttributes(DMPU_BASE, CMMPU_RGN_0, (uint32_t)&srcBuffer,
                              (CMMPU_RGN_SIZE_1K| CMMPU_RGN_PERM_READ_ONLY |
                               CMMPU_RGN_ENABLE));

    CMMPU_setRegionAttributes(DMPU_BASE, CMMPU_RGN_1, (uint32_t)&ucControlTable[0],
                              (CMMPU_RGN_SIZE_1K| CMMPU_RGN_PERM_FULL_ACCESS |
                               CMMPU_RGN_ENABLE));

    CMMPU_setRegionAttributes(DMPU_BASE, CMMPU_RGN_2, (uint32_t)&dstBuffer,
                              (CMMPU_RGN_SIZE_1K| CMMPU_RGN_PERM_FULL_ACCESS |
                               CMMPU_RGN_ENABLE));

    CMMPU_enableAccessViolationInterrupt(DMPU_BASE);
    CMMPU_enable(DMPU_BASE);

    //
    // Initialize the uDMA memory to memory transfers.
    //
    initSWTransfer();

    //
    // Loop forever with the CPU not sleeping, so the debugger can connect.
    //
    while(1)
    {
    }
}

//
// initSWTransfer - Initializes the uDMA software channel to perform a memory
// to memory uDMA transfer.
//
void initSWTransfer(void)
{
    //
    // Enable interrupts from the uDMA software channel.
    //
    Interrupt_enable(UDMA_SW_INT);

    //
    // Put the attributes in a known state for the uDMA software channel.
    // These should already be disabled by default.
    //
    UDMA_disableChannelAttribute(UDMA_BASE, 30U, UDMA_CH_ATTR_ALL);

    //
    // Configure the control parameters for the SW channel.  The SW channel
    // will be used to transfer between two memory buffers, 32 bits at a time.
    // Therefore the data size is 32 bits, and the address increment is 32 bits
    // for both source and destination.  The arbitration size will be set to 8,
    // which causes the uDMA controller to re-arbitrate after 8 items are
    // transferred.  This keeps this channel from hogging the uDMA controller
    // once the transfer is started, and allows other channels cycles if they
    // are higher priority.
    //
    UDMA_setChannelControlParams(UDMA_BASE, (30U  | UDMA_PRI_SELECT),
                                 (UDMA_SIZE_32    | UDMA_SRC_INC_32 |
                                  UDMA_DST_INC_32 | UDMA_ARB_8));

    //
    // Set up the transfer parameters for the software channel.  This will
    // configure the transfer buffers and the transfer size.  Auto mode must be
    // used for software transfers.
    //
    UDMA_setChannelTransferParams(UDMA_BASE, (30U | UDMA_PRI_SELECT),
                                  srcBuffer, dstBuffer, UDMA_MODE_AUTO,
                                  MEM_BUFFER_SIZE);

    //
    // Now the software channel is primed to start a transfer.  The channel
    // must be enabled.  For software based transfers, a request must be
    // issued.  After this, the uDMA memory transfer begins.
    //
    UDMA_enableChannel(UDMA_BASE, 30U);
    UDMA_requestSoftwareTransfer(UDMA_BASE, 30U);
}

//
// uDMAIntISR - The interrupt handler for uDMA interrupts from the memory
// channel.  This interrupt will increment a counter, and then restart another
// memory transfer.
//
void uDMAIntISR(void)
{
    static uint32_t ranNum = 1;
    uint32_t chMode;
    uint32_t i;

    //
    // Check for the primary control structure to indicate complete.
    //
    chMode = UDMA_getChannelTransferMode(UDMA_BASE, (30U|UDMA_PRI_SELECT));
    if(chMode == UDMA_MODE_STOP)
    {
        //
        // Increment the count of completed transfers.
        //
        memTransferCount++;

        //
        // Check the data integrity of transfer
        //
        for(i=0; i< MEM_BUFFER_SIZE; i++)
        {
            if(dstBuffer[i] != srcBuffer[i])
            {
                errCountGlobal++;
            }

        }
        if(errCountGlobal == 0)
        {
            for(i = 0; i < MEM_BUFFER_SIZE; i++)
            {
                srcBuffer[i] = i + ranNum;
            }
            ranNum++;
            ranNum = ranNum % 100;

            //
            // Configure it for another transfer.
            //
            UDMA_setChannelTransferParams(UDMA_BASE, (30U|UDMA_PRI_SELECT),
                                          srcBuffer, dstBuffer, UDMA_MODE_AUTO,
                                          MEM_BUFFER_SIZE);

            //
            // Initiate another transfer.
            //
            UDMA_enableChannel(UDMA_BASE, 30U);
            UDMA_requestSoftwareTransfer(UDMA_BASE, 30U);

        }
    }

    //
    // If the channel is not stopped, then something is wrong.
    //
    else
    {
        badInterruptCount++;
    }
}

//
// uDMAErrorISR - The interrupt handler for uDMA errors.  This interrupt will
// occur if the uDMA encounters a bus error while trying to perform a transfer.
// This handler just increments a counter if an error occurs.
//
void uDMAErrorISR(void)
{
    uint32_t errStatus;

    //
    // CM-MPU ACC-VIO register status.
    //
    intFlagStatus = CMMPU_getAccessViolationFlags(DMPU_BASE);
    accVioAdd = CMMPU_getAccessViolationAddr(DMPU_BASE);
    CMMPU_clearAccessViolationFlags(DMPU_BASE, (CMMPU_ACC_VIO_FLAGS_READ |
                                    CMMPU_ACC_VIO_FLAGS_WRITE));

    //
    // Increment a counter to indicate fault occurred in MPU.
    //
    if(intFlagStatus != 0U)
    {
        faultCount++;
    }

    //
    // Check for uDMA error bit.
    //
    errStatus = UDMA_getErrorStatus(UDMA_BASE);

    //
    // If there is a uDMA error, then clear the error and increment
    // the error counter.
    //
    if(errStatus)
    {
        UDMA_clearErrorStatus(UDMA_BASE);
        errCountDMA++;
    }
}

//
// End of File
//
