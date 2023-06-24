//###########################################################################
//
// FILE:   udma.h
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

#ifndef UDMA_H
#define UDMA_H

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
//! \addtogroup udma_api UDMA
//! \brief This module is used for configuring the microDMA
//! @{
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "debug.h"
#include "interrupt.h"
#include "cpu.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_udma.h"

//*****************************************************************************
//
// Defines for the API.
//
//*****************************************************************************

//*****************************************************************************
//
// Values that can be passed as channelInt param to UDMA_registerInterrupt() &
// UDMA_registerInterrupt().
//
//*****************************************************************************
#define UDMA_SW_INT                41U
#define UDMA_ERR_INT               42U

//*****************************************************************************
//
// Values that can be passed as channelNum parameter to UDMA_enableChannel(),
// UDMA_disableChannel(), UDMA_isChannelEnabled(), UDMA_changeChannelMapping(),
// UDMA_requestSoftwareTransfer(),  UDMA_enableChannelAttribute(),
// UDMA_disableChannelAttribute(), UDMA_getChannelAttribute() and
// UDMA_setChannelScatterGatherMode().
//
//*****************************************************************************
#define UDMA_CHANNEL_0             0U
#define UDMA_CHANNEL_1             1U
#define UDMA_CHANNEL_2             2U
#define UDMA_CHANNEL_3             3U
#define UDMA_CHANNEL_4             4U
#define UDMA_CHANNEL_5             5U
#define UDMA_CHANNEL_6             6U
#define UDMA_CHANNEL_7             7U
#define UDMA_CHANNEL_8             8U
#define UDMA_CHANNEL_9             9U
#define UDMA_CHANNEL_10            10U
#define UDMA_CHANNEL_11            11U
#define UDMA_CHANNEL_12            12U
#define UDMA_CHANNEL_13            13U
#define UDMA_CHANNEL_14            14U
#define UDMA_CHANNEL_15            15U
#define UDMA_CHANNEL_16            16U
#define UDMA_CHANNEL_17            17U
#define UDMA_CHANNEL_18            18U
#define UDMA_CHANNEL_19            19U
#define UDMA_CHANNEL_20            20U
#define UDMA_CHANNEL_21            21U
#define UDMA_CHANNEL_22            22U
#define UDMA_CHANNEL_23            23U
#define UDMA_CHANNEL_24            24U
#define UDMA_CHANNEL_25            25U
#define UDMA_CHANNEL_26            26U
#define UDMA_CHANNEL_27            27U
#define UDMA_CHANNEL_28            28U
#define UDMA_CHANNEL_29            29U
#define UDMA_CHANNEL_30            30U
#define UDMA_CHANNEL_31            31U

//*****************************************************************************
//
// Values that can be passed as channelNum parameter to UDMA_enableChannel(),
// UDMA_disableChannel(), UDMA_isChannelEnabled(), UDMA_changeChannelMapping(),
// UDMA_requestSoftwareTransfer(),  UDMA_enableChannelAttribute(),
// UDMA_disableChannelAttribute(), UDMA_getChannelAttribute() and
// UDMA_setChannelScatterGatherMode(). These channel numbers are defined as
// per the primary peripheral assignment for the channel to enhance
// readability.
//
//****************************************************************************
#define UDMA_CHANNEL_USBEP1_RX     UDMA_CHANNEL_0
#define UDMA_CHANNEL_USBEP1_TX     UDMA_CHANNEL_1
#define UDMA_CHANNEL_USBEP2_RX     UDMA_CHANNEL_2
#define UDMA_CHANNEL_USBEP2_TX     UDMA_CHANNEL_3
#define UDMA_CHANNEL_USBEP3_RX     UDMA_CHANNEL_4
#define UDMA_CHANNEL_USBEP3_TX     UDMA_CHANNEL_5
#define UDMA_CHANNEL_UART0_RX      UDMA_CHANNEL_8
#define UDMA_CHANNEL_UART0_TX      UDMA_CHANNEL_9
#define UDMA_CHANNEL_SSI0_RX       UDMA_CHANNEL_10
#define UDMA_CHANNEL_SSI0_TX       UDMA_CHANNEL_11
#define UDMA_CHANNEL_SW_CH12       UDMA_CHANNEL_12
#define UDMA_CHANNEL_SW_CH13       UDMA_CHANNEL_13
#define UDMA_CHANNEL_AES_CTXIN     UDMA_CHANNEL_21
#define UDMA_CHANNEL_AES_DIN       UDMA_CHANNEL_22
#define UDMA_CHANNEL_AES_CTXOUT    UDMA_CHANNEL_23
#define UDMA_CHANNEL_AES_DOUT      UDMA_CHANNEL_24
#define UDMA_CHANNEL_SW_CH26       UDMA_CHANNEL_26
#define UDMA_CHANNEL_SW_CH27       UDMA_CHANNEL_27
#define UDMA_CHANNEL_I2C0_RX       UDMA_CHANNEL_28
#define UDMA_CHANNEL_I2C0_TX       UDMA_CHANNEL_29
#define UDMA_CHANNEL_SW_CH30       UDMA_CHANNEL_30

//*****************************************************************************
//
// Values that can be passed to UDMA_changeChannelMapping() as chMapping
// parameter.
//
//*****************************************************************************
#define UDMA_CH_MAPPING_0          0x0U
#define UDMA_CH_MAPPING_1          0x1U

//*****************************************************************************
//
// Flags that can be passed to UDMA_enableChannelAttribute(),
// UDMA_disableChannelAttribute() and returned from UDMA_getChannelAttribute().
//
//*****************************************************************************
#define UDMA_CH_ATTR_USEBURST      0x00000001U //!< uDMA channel responds to
                                               //!< burst requests only
#define UDMA_CH_ATTR_ALTSELECT     0x00000002U //!< uDMA channel is using
                                               //!< alternate control structure
#define UDMA_CH_ATTR_HIGH_PRIORITY 0x00000004U //!< uDMA channel uses high
                                               //!< priority level
#define UDMA_CH_ATTR_REQMASK       0x00000008U //!< uDMA channel is masked
                                               //!< for associated peripheral
#define UDMA_CH_ATTR_ALL           0x0000000FU //!< OR of all the above
                                               //!< attributes

//*****************************************************************************
//
// DMA control modes that can be passed to UDMA_setChannelTransferParams() and
// returned by UDMA_getChannelTransferMode().
//
//*****************************************************************************
#define UDMA_MODE_STOP                 0x00000000U //!< Stop Mode
#define UDMA_MODE_BASIC                0x00000001U //!< Basic Mode
#define UDMA_MODE_AUTO                 0x00000002U //!< Auto-Request Mode
#define UDMA_MODE_PINGPONG             0x00000003U //!< Ping-Pong Mode
#define UDMA_MODE_MEM_SCATTER_GATHER   0x00000004U //!< Mem Scatter-Gather Mode
#define UDMA_MODE_PER_SCATTER_GATHER   0x00000006U //!< Per Scatter-Gather Mode
#define UDMA_MODE_ALT_SELECT           0x00000001U //!< Specifies Alternate
                                                   //!< Scatter-Gather Mode
                                                   //!< when OR'd with either
                                                   //!< of above two attributes

//*****************************************************************************
//
// Channel configuration values that can be passed to
// UDMA_setChannelControlParams().
//
//*****************************************************************************
#define UDMA_DST_INC_8          0x00000000U //!< Dest addr increment of 8-bit
#define UDMA_DST_INC_16         0x40000000U //!< Dest addr increment of 16-bit
#define UDMA_DST_INC_32         0x80000000U //!< Dest addr increment of 32-bit
#define UDMA_DST_INC_NONE       0xc0000000U //!< Dest addr increment of 0-bit
#define UDMA_SRC_INC_8          0x00000000U //!< Src add increment of 8-bit
#define UDMA_SRC_INC_16         0x04000000U //!< Src add increment of 16-bit
#define UDMA_SRC_INC_32         0x08000000U //!< Src add increment of 32-bit
#define UDMA_SRC_INC_NONE       0x0C000000U //!< Src add increment of 0-bit
#define UDMA_SIZE_8             0x00000000U //!< Src & dest Data size is 8-bit
#define UDMA_SIZE_16            0x11000000U //!< Src & dest data size is 16-bit
#define UDMA_SIZE_32            0x22000000U //!< Src & dest data size is 32-bit
#define UDMA_DST_PROT_PRIV      0x00200000U //!< Dest addr access is privileged
#define UDMA_SRC_PROT_PRIV      0x00040000U //!< Src addr access is privileged
#define UDMA_ARB_1              0x00000000U //!< Arbitrate after 1 transfer
#define UDMA_ARB_2              0x00004000U //!< Arbitrate after 2 transfers
#define UDMA_ARB_4              0x00008000U //!< Arbitrate after 4 transfers
#define UDMA_ARB_8              0x0000c000U //!< Arbitrate after 8 transfers
#define UDMA_ARB_16             0x00010000U //!< Arbitrate after 16 transfers
#define UDMA_ARB_32             0x00014000U //!< Arbitrate after 32 transfers
#define UDMA_ARB_64             0x00018000U //!< Arbitrate after 64 transfers
#define UDMA_ARB_128            0x0001c000U //!< Arbitrate after 128 transfers
#define UDMA_ARB_256            0x00020000U //!< Arbitrate after 256 transfers
#define UDMA_ARB_512            0x00024000U //!< Arbitrate after 512 transfers
#define UDMA_ARB_1024           0x00028000U //!< Arbitrate after 1024 transfers
#define UDMA_NEXT_USEBURST      0x00000008U //!< Use burst transfer to complete
                                            //!< last transfer.

//*****************************************************************************
//
// Flags to be OR'd with the channel number to indicate if the primary or
// alternate control structure should be used.
//
//*****************************************************************************
#define UDMA_PRI_SELECT        0x00000000U //!< Use primary control structure
#define UDMA_ALT_SELECT        0x00000020U //!< Use alternate control structure

//*****************************************************************************
//
//! A helper macro for building scatter-gather task table entries.
//!
//! \param transferCount is the count of items to transfer for this task.
//! \param itemSize is the bit size of the items to transfer for this task.
//! \param srcIncrement is the bit size increment for source data.
//! \param srcAddr is the starting address of the data to transfer.
//! \param dstIncrement is the bit size increment for destination data.
//! \param dstAddr is the starting address of the destination data.
//! \param arbSize is the arbitration size to use for the transfer task.
//! \param mode is the transfer mode for this task.
//!
//! This macro is intended to be used to help populate a table of uDMA tasks
//! for a scatter-gather transfer.  This macro will calculate the values for
//! the fields of a task structure entry based on the input parameters.
//!
//! There are specific requirements for the values of each parameter.  No
//! checking is done so it is up to the caller to ensure that correct values
//! are used for the parameters.
//!
//! The \e transferCount parameter is the number of items that will be
//! transferred by this task.  It must be in the range 1-1024.
//!
//! The \e itemSize parameter is the bit size of the transfer data.  It
//! must be one of \b UDMA_SIZE_8, \b UDMA_SIZE_16, or \b UDMA_SIZE_32.
//!
//! The \e srcIncrement parameter is the increment size for the source
//! data.  It must be one of \b UDMA_SRC_INC_8, \b UDMA_SRC_INC_16,
//! \b UDMA_SRC_INC_32, or \b UDMA_SRC_INC_NONE.
//!
//! The \e srcAddr parameter is a void pointer to the beginning of the source
//! data.
//!
//! The \e dstIncrement parameter is the increment size for the destination
//! data.  It must be one of \b UDMA_DST_INC_8, \b UDMA_DST_INC_16,
//! \b UDMA_DST_INC_32, or \b UDMA_DST_INC_NONE.
//!
//! The \e dstAddr parameter is a void pointer to the beginning of the
//! location where the data will be transferred.
//!
//! The \e arbSize parameter is the arbitration size for the transfer, and
//! must be one of \b UDMA_ARB_1, \b UDMA_ARB_2, \b UDMA_ARB_4, and so on
//! up to \b UDMA_ARB_1024.  This is used to select the arbitration size in
//! powers of 2, from 1 to 1024.
//!
//! The \e mode parameter is the mode to use for this transfer task.  It
//! must be one of \b UDMA_MODE_BASIC, \b UDMA_MODE_AUTO,
//! \b UDMA_MODE_MEM_SCATTER_GATHER, or \b UDMA_MODE_PER_SCATTER_GATHER.  Note
//! that normally all tasks will be one of the scatter-gather modes while the
//! last task is a task list will be AUTO or BASIC.
//!
//! This macro is intended to be used to initialize individual entries of
//! a structure of UDMA_ControlTable type, like this:
//!
//! \verbatim
//!     UDMA_ControlTable MyTaskList[] =
//!     {
//!         UDMA_TASK_STRUCT_ENTRY(Task1Count, UDMA_SIZE_8,
//!                             UDMA_SRC_INC_8, MySourceBuf,
//!                             UDMA_DST_INC_8, MyDestBuf,
//!                             UDMA_ARB_8, UDMA_MODE_MEM_SCATTER_GATHER),
//!         UDMA_TASK_STRUCT_ENTRY(Task2Count, ...),
//!     }
//! \endverbatim
//!
//! \return Nothing; this is not a function.
//
//*****************************************************************************
#define UDMA_TASK_STRUCT_ENTRY(transferCount,                                  \
                               itemSize,                                       \
                               srcIncrement,                                   \
                               srcAddr,                                        \
                               dstIncrement,                                   \
                               dstAddr,                                        \
                               arbSize,                                        \
                               mode)                                           \
    {                                                                          \
        (((srcIncrement) == UDMA_SRC_INC_NONE) ? (void *)(srcAddr) :           \
            ((void *)(&((uint8_t *)(srcAddr))[((transferCount) <<              \
             ((srcIncrement) >> UDMA_DMACHCTL_SRCINC_S)) - 1]))),              \
        (((dstIncrement) == UDMA_DST_INC_NONE) ? (void *)(dstAddr) :           \
            ((void *)(&((uint8_t *)(dstAddr))[((transferCount) <<              \
             ((dstIncrement) >> UDMA_DMACHCTL_DSTINC_S)) - 1]))),              \
        (srcIncrement) | (dstIncrement) | (itemSize) | (arbSize) |             \
        (((transferCount) - 1) << 4) |                                         \
        ((((mode) == UDMA_MODE_MEM_SCATTER_GATHER) ||                          \
          ((mode) == UDMA_MODE_PER_SCATTER_GATHER)) ?                          \
          (mode) | UDMA_MODE_ALT_SELECT : (mode)), 0                           \
    }

//*****************************************************************************
//
//! A structure that defines an entry in the channel control table.  These
//! fields are used by the uDMA controller and normally it is not necessary for
//! software to directly read or write fields in the table.
//
//*****************************************************************************
typedef struct
{
    volatile void *srcEndAddr; //!< Ending source address of the data transfer.
    volatile void *dstEndAddr; //!< Ending dest address of the data transfer.
    volatile uint32_t chControlAttr; //!< Channel control Attributes.
    volatile uint32_t spare;   //!< Spare space.
} UDMA_ControlTable;

//*****************************************************************************
//
// API Function prototypes
//
//*****************************************************************************
//*****************************************************************************
//
//! \internal
//! Checks uDMA base address.
//!
//! \param base is the base address of the uDMA instance used.
//!
//! This function determines if uDMA module base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool
UDMA_isBaseValid(uint32_t base)
{
    return(base == UDMA_BASE);
}
#endif

//*****************************************************************************
//
//! Enables the uDMA controller for use.
//!
//! \param base is the base address of the uDMA instance used.
//!
//! This function enables the uDMA controller.  The uDMA controller must be
//! enabled before it can be configured and used.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UDMA_enable(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UDMA_isBaseValid(base));

    //
    // Set the master enable bit in the config register.
    //
    HWREG(base + UDMA_O_DMACFG) |= UDMA_DMACFG_MASTEN;
}

//*****************************************************************************
//
//! Disables the uDMA controller for use.
//!
//! \param base is the base address of the uDMA instance used.
//!
//! This function disables the uDMA controller.  Once disabled, the uDMA
//! controller cannot operate until re-enabled with UDMA_enable().
//!
//! \return None.
//
//*****************************************************************************
static inline void
UDMA_disable(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UDMA_isBaseValid(base));

    //
    // Clear the master enable bit in the config register.
    //
    HWREG(base + UDMA_O_DMACFG) &= ~UDMA_DMACFG_MASTEN;
}

//*****************************************************************************
//
//! Gets the uDMA error status.
//!
//! \param base is the base address of the uDMA instance used.
//!
//! This function returns the uDMA error status.  It should be called from
//! within the uDMA error interrupt handler to determine if a uDMA error
//! occurred.
//!
//! \return Returns non-zero if a uDMA error is pending.
//
//*****************************************************************************
static inline uint32_t
UDMA_getErrorStatus(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UDMA_isBaseValid(base));

    //
    // Return the uDMA error status.
    //
    return(HWREG(base + UDMA_O_DMAERRCLR));
}

//*****************************************************************************
//
//! Clears the uDMA error interrupt.
//!
//! \param base is the base address of the uDMA instance used.
//!
//! This function clears a pending uDMA error interrupt.  This function should
//! be called from within the uDMA error interrupt handler to clear the
//! interrupt.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UDMA_clearErrorStatus(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UDMA_isBaseValid(base));

    //
    // Clear the uDMA error interrupt.
    //
    HWREG(base + UDMA_O_DMAERRCLR) |= UDMA_DMAERRCLR_ERRCLR;
}

//*****************************************************************************
//
//! Enables a uDMA channel for operation.
//!
//! \param base is the base address of the uDMA instance used.
//! \param channelNum is the channel number to enable.
//!
//! This function enables a specific uDMA channel for use.  This function must
//! be used to enable a channel before it can be used to perform a uDMA
//! transfer.
//!
//! When a uDMA transfer is completed, the channel is automatically disabled by
//! the uDMA controller.  Therefore, this function should be called prior to
//! starting up any new transfer.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UDMA_enableChannel(uint32_t base, uint32_t channelNum)
{
    //
    // Check the arguments.
    //
    ASSERT(UDMA_isBaseValid(base));
    ASSERT(channelNum < 32U);

    //
    // Set the bit for this channel in the enable set register.
    //
    HWREG(base + UDMA_O_DMAENASET) = 1U << (channelNum & 0x1FU);
}

//*****************************************************************************
//
//! Disables a uDMA channel for operation.
//!
//! \param base is the base address of the uDMA instance used.
//! \param channelNum is the channel number to disable.
//!
//! This function disables a specific uDMA channel.  Once disabled, a channel
//! cannot respond to uDMA transfer requests until re-enabled via
//! UDMA_enableChannel().
//!
//! \return None.
//
//*****************************************************************************
static inline void
UDMA_disableChannel(uint32_t base, uint32_t channelNum)
{
    //
    // Check the arguments.
    //
    ASSERT(UDMA_isBaseValid(base));
    ASSERT(channelNum < 32U);

    //
    // Set the bit for this channel in the enable clear register.
    //
    HWREG(base + UDMA_O_DMAENACLR) = 1U << (channelNum & 0x1FU);
}

//*****************************************************************************
//
//! Checks if a uDMA channel is enabled for operation.
//!
//! \param base is the base address of the uDMA instance used.
//! \param channelNum is the channel number to check.
//!
//! This function checks to see if a specific uDMA channel is enabled.  This
//! function can be used to check the status of a transfer, as the channel is
//! automatically disabled at the end of a transfer.
//!
//! \return Returns \b true if the channel is enabled, \b false if disabled.
//
//*****************************************************************************
static inline bool
UDMA_isChannelEnabled(uint32_t base, uint32_t channelNum)
{
    //
    // Check the arguments.
    //
    ASSERT(UDMA_isBaseValid(base));
    ASSERT(channelNum < 32U);

    //
    // AND the specified channel bit with the enable register and return the
    // result.
    //
    return((HWREG(base + UDMA_O_DMAENASET) &
            (1U << (channelNum & 0x1FU))) != 0U);
}

//*****************************************************************************
//
//! Sets the base address for the channel control table.
//!
//! \param base is the base address of the uDMA instance used.
//! \param controlTable is a pointer to the 1024-byte-aligned base address
//! of the uDMA channel control table.
//!
//! This function configures the base address of the channel control table.
//! This table resides in system memory and holds control information for each
//! uDMA channel.  The table must be aligned on a 1024-byte boundary.  The base
//! address must be configured before any of the channel functions can be used.
//!
//! The size of the channel control table depends on the number of uDMA
//! channels and the transfer modes that are used.  Refer to the introductory
//! text and the microcontroller datasheet for more information about the
//! channel control table.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UDMA_setControlBase(uint32_t base, const void *controlTable)
{
    //
    // Check the arguments.
    //
    ASSERT(UDMA_isBaseValid(base));
    ASSERT(((uint32_t)controlTable & ~0x3FFU) == (uint32_t)controlTable);
    ASSERT((uint32_t)controlTable >= 0x20000000U);

    //
    // Program the base address into the register.
    //
    HWREG(base + UDMA_O_DMACTLBASE) = (uint32_t)controlTable;
}

//*****************************************************************************
//
//! Gets the base address for the channel control table.
//!
//! \param base is the base address of the uDMA instance used.
//!
//! This function gets the base address of the channel control table.  This
//! table resides in system memory and holds control information for each uDMA
//! channel.
//!
//! \return Returns a pointer to the base address of the channel control table.
//
//*****************************************************************************
static inline void *
UDMA_getControlBase(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UDMA_isBaseValid(base));

    //
    // Read the current value of the control base register and return it to
    // the caller.
    //
    return((void *)HWREG(base + UDMA_O_DMACTLBASE));
}

//*****************************************************************************
//
//! Gets the base address for the channel control table alternate structures.
//!
//! \param base is the base address of the uDMA instance used.
//!
//! This function gets the base address of the second half of the channel
//! control table that holds the alternate control structures for each channel.
//!
//! \return Returns a pointer to the base address of the second half of the
//! channel control table.
//
//*****************************************************************************
static inline void *
UDMA_getAlternateControlBase(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(UDMA_isBaseValid(base));

    //
    // Read the current value of the control base register and return it to
    // the caller.
    //
    return((void *)HWREG(base + UDMA_O_DMAALTBASE));
}

//*****************************************************************************
//
//! Requests a uDMA channel to start a transfer.
//!
//! \param base is the base address of the uDMA instance used.
//! \param channelNum is the channel number on which to request a uDMA
//! transfer.
//!
//! This function allows software to request a uDMA channel to begin a
//! transfer.  This function could be used for performing a memory-to-memory
//! transfer, or if for some reason a transfer needs to be initiated by
//! software instead of the peripheral associated with that channel.
//!
//! \note If the software channel and interrupts are used, then
//! the completion is signaled on the uDMA dedicated interrupt.  If a
//! peripheral channel is used, then the completion is signaled on the
//! peripheral's interrupt.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UDMA_requestSoftwareTransfer(uint32_t base, uint32_t channelNum)
{
    //
    // Check the arguments.
    //
    ASSERT(UDMA_isBaseValid(base));
    ASSERT((channelNum & 0xFFFFU) < 32U);

    //
    // Set the bit for this channel in the software uDMA request register.
    //
    HWREG(base + UDMA_O_DMASWREQ) = 1U << (channelNum & 0x1FU);
}

//*****************************************************************************
//
//! Sets the control parameters for a uDMA channel control structure.
//!
//! \param base is the base address of the uDMA instance used.
//! \param index is the control table structure index.
//! \param chControlAttr specifies the channel control parameters.
//!
//! This function is used to set control parameters for a uDMA transfer. These
//! parameters are typically not changed often.
//!
//! The \e index parameter should be the logical OR of the channel number
//! with one of \b UDMA_PRI_SELECT or \b UDMA_ALT_SELECT to choose whether
//! the primary or alternate data structure is used.
//!
//! The \e chControlAttr parameter is the logical OR of five values: the data
//! size, the source address increment, the destination address increment, the
//! arbitration size, and the use burst flag.  The choices available for each
//! of these values is described below.
//!
//! Choose the data size from one of \b UDMA_SIZE_8, \b UDMA_SIZE_16, or
//! \b UDMA_SIZE_32 to select a data size of 8, 16, or 32 bits.
//!
//! Choose the source address increment from one of \b UDMA_SRC_INC_8,
//! \b UDMA_SRC_INC_16, \b UDMA_SRC_INC_32, or \b UDMA_SRC_INC_NONE to select
//! an address increment of 8-bit bytes, 16-bit half-words, 32-bit words, or
//! to select non-incrementing.
//!
//! Choose the destination address increment from one of \b UDMA_DST_INC_8,
//! \b UDMA_DST_INC_16, \b UDMA_DST_INC_32, or \b UDMA_DST_INC_NONE to select
//! an address increment of 8-bit bytes, 16-bit half-words, 32-bit words, or
//! to select non-incrementing.
//!
//! The arbitration size determines how many items are transferred before
//! the uDMA controller re-arbitrates for the bus.  Choose the arbitration size
//! from one of \b UDMA_ARB_1, \b UDMA_ARB_2, \b UDMA_ARB_4, \b UDMA_ARB_8,
//! through \b UDMA_ARB_1024 to select the arbitration size from 1 to 1024
//! items, in powers of 2.
//!
//! The value \b UDMA_NEXT_USEBURST is used to force the channel to only
//! respond to burst requests at the tail end of a scatter-gather transfer.
//!
//! \note The address increment cannot be smaller than the data size.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UDMA_setChannelControlParams(uint32_t base, uint32_t index,
                             uint32_t chControlAttr)
{
    UDMA_ControlTable *controlTable;

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

    //
    // Get the current control word value and mask off the fields to be
    // changed, then OR in the new settings.
    //
    controlTable[index].chControlAttr =
         ((controlTable[index].chControlAttr &
           ~(UDMA_DMACHCTL_DSTINC_M  | UDMA_DMACHCTL_DSTSIZE_M     |
             UDMA_DMACHCTL_SRCINC_M  | UDMA_DMACHCTL_SRCSIZE_M     |
             UDMA_DMACHCTL_ARBSIZE_M | UDMA_DMACHCTL_NXTUSEBURST)) |
             chControlAttr);
}

//*****************************************************************************
//
//! Gets the transfer mode for a uDMA channel control structure.
//!
//! \param base is the base address of the uDMA instance used.
//! \param index is the index for channel control structure.
//!
//! This function is used to get the transfer mode for the uDMA channel and
//! to query the status of a transfer on a channel.  When the transfer is
//! complete the mode is \b UDMA_MODE_STOP.
//!
//! \return Returns the transfer mode of the specified channel and control
//! structure, which is one of the following values:
//! \b UDMA_MODE_STOP,
//! \b UDMA_MODE_BASIC,
//! \b UDMA_MODE_AUTO,
//! \b UDMA_MODE_PINGPONG,
//! \b UDMA_MODE_MEM_SCATTER_GATHER,
//! \b UDMA_MODE_PER_SCATTER_GATHER.
//
//*****************************************************************************
static inline uint32_t
UDMA_getChannelTransferMode(uint32_t base, uint32_t index)
{
    UDMA_ControlTable *controlTable;
    uint32_t chControlAttr;

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
    // Get the current control word value and mask off all but the mode field.
    //
    chControlAttr = (controlTable[index].chControlAttr &
                     UDMA_DMACHCTL_XFERMODE_M);

    //
    // Check if scatter/gather mode, and if so, mask off the alt bit.
    //
    if(((chControlAttr & ~UDMA_MODE_ALT_SELECT) ==
        UDMA_MODE_MEM_SCATTER_GATHER) ||
       ((chControlAttr & ~UDMA_MODE_ALT_SELECT) ==
        UDMA_MODE_PER_SCATTER_GATHER))
    {
        chControlAttr &= ~UDMA_MODE_ALT_SELECT;
    }

    //
    // Return the mode to the caller.
    //
    return(chControlAttr);
}

//*****************************************************************************
//
//! Configures peripheral mapping for any uDMA channel.
//!
//! \param base is the base address of the uDMA instance used.
//! \param channelNum is the uDMA channel to be assigned.
//! \param chMapping specifies the peripheral assignment for the channel.
//!
//! This function configures peripheral mapping for any uDMA channel. Each uDMA
//! channel can be mapped to a fixed set of peripherals. Refer device datasheet
//! for all the possible configurations for a channel. The param \e channelNum
//! can take values 0U-31U specifying uDMA channels. The param \e chMapping
//! specifies possible peripheral assignmentes for a channel. For selecting
//! primary or secondary channel assignment UDMA_CH_MAPPING_0 or
//! UDMA_CH_MAPPING_1 macros can be used.
//!
//! \note This function is only available on devices that have the DMA Channel
//! Map Select registers (DMACHMAP0-3).  Please consult the data sheet for
//! your part.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UDMA_changeChannelMapping(uint32_t base, uint32_t channelNum,
                          uint32_t chMapping)
{
    uint32_t shift, mapReg;

    //
    // Check the parameters.
    //
    ASSERT(UDMA_isBaseValid(base));
    ASSERT(channelNum <= 31U);
    ASSERT((chMapping == UDMA_CH_MAPPING_0) ||
           (chMapping == UDMA_CH_MAPPING_1));

    //
    // Find the uDMA channel chMapping register and shift value to use for
    // this channel.
    //
    mapReg = base + UDMA_O_DMACHMAP0 + ((channelNum / 8U) * 4U);
    shift = (channelNum & 0x7U) * 4U;

    //
    // Set the channel map encoding for this channel.
    //
    HWREG(mapReg) = (HWREG(mapReg) & ~((uint32_t)0xFU << shift)) |
                    (chMapping << shift);
}

//*****************************************************************************
//
//! Registers an interrupt handler for the uDMA controller.
//!
//! \param channelInt identifies which uDMA interrupt is to be registered.
//! \param fnHandler is a pointer to the function to be called when the
//! interrupt is activated.
//!
//! This function registers and enables the handler to be called when the uDMA
//! controller generates an interrupt. The param \e channelInt can take
//! following values: UDMA_SW_INT or UDMA_ERR_INT.
//!
//! \sa Interrupt_registerHandler() for important information about registering
//! interrupt handlers.
//!
//! \note The interrupt handler for the uDMA is for transfer completion when
//! the software channel is used and for error interrupts.  The interrupts for
//! each peripheral channel are handled through the individual peripheral
//! interrupt handlers.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UDMA_registerInterrupt(uint32_t channelInt, void (*fnHandler)(void))
{
    //
    // Check the arguments.
    //
    ASSERT(fnHandler);

    //
    // Register the interrupt handler.
    //
    Interrupt_registerHandler(channelInt, fnHandler);

    //
    // Enable the interrupt.
    //
    Interrupt_enable(channelInt);
}

//*****************************************************************************
//
//! Unregisters an interrupt handler for the uDMA controller.
//!
//! \param channelInt identifies which uDMA interrupt to unregister.
//!
//! This function disables and unregisters the handler to be called for the
//! specified uDMA interrupt. The param \e channelInt can take following
//! values: UDMA_SW_INT or UDMA_ERR_INT.
//!
//! \sa Interrupt_registerHandler() for important information about registering
//! interrupt handlers.
//!
//! \return None.
//
//*****************************************************************************
static inline void
UDMA_unregisterInterrupt(uint32_t channelInt)
{
    //
    // Disable the interrupt.
    //
    Interrupt_disable(channelInt);

    //
    // Unregister the interrupt handler.
    //
    Interrupt_unregisterHandler(channelInt);
}

//*****************************************************************************
//
//! Enables attributes of a uDMA channel.
//!
//! \param base is the base address of the uDMA instance used.
//! \param channelNum is the channel to configure.
//! \param channelAttr is a combination of attributes for the channel.
//!
//! This function is used to enable attributes of a uDMA channel.
//!
//! The \e channelAttr parameter is the logical OR of any of the following:
//!
//! - \b UDMA_CH_ATTR_USEBURST is used to restrict transfers to use only burst
//!   mode
//! - \b UDMA_CH_ATTR_ALTSELECT is used to select the alternate control
//!   structure for this channel (it is very unlikely that this flag should
//!   be used)
//! - \b UDMA_CH_ATTR_HIGH_PRIORITY is used to set this channel to high priority
//! - \b UDMA_CH_ATTR_REQMASK is used to mask the hardware request signal from
//!   the peripheral for this channel.
//!
//! \return None.
//
//*****************************************************************************
extern void
UDMA_enableChannelAttribute(uint32_t base, uint32_t channelNum,
                            uint32_t channelAttr);

//*****************************************************************************
//
//! Disables attributes of a uDMA channel.
//!
//! \param base is the base address of the uDMA instance used.
//! \param channelNum is the channel to configure.
//! \param channelAttr is a combination of attributes for the channel.
//!
//! This function is used to disable attributes of a uDMA channel.
//!
//! The \e channelAttr parameter is the logical OR of any of the following:
//!
//! - \b UDMA_CH_ATTR_USEBURST is used to restrict transfers to use only burst
//!   mode.
//! - \b UDMA_CH_ATTR_ALTSELECT is used to select the alternate control
//!   structure for this channel.
//! - \b UDMA_CH_ATTR_HIGH_PRIORITY is used to set this channel to high
//!   priority.
//! - \b UDMA_CH_ATTR_REQMASK is used to mask the hardware request signal from
//!   the peripheral for this channel.
//!
//! \return None.
//
//*****************************************************************************
extern void
UDMA_disableChannelAttribute(uint32_t base, uint32_t channelNum,
                             uint32_t channelAttr);

//*****************************************************************************
//
//! Gets the enabled attributes of a uDMA channel.
//!
//! \param base is the base address of the uDMA instance used.
//! \param channelNum is the channel to configure.
//!
//! This function returns a combination of flags representing the attributes of
//! the uDMA channel.
//!
//! \return Returns the logical OR of the attributes of the uDMA channel, which
//! can be any of the following:
//! - \b UDMA_CH_ATTR_USEBURST is used to restrict transfers to use only burst
//!   mode
//! - \b UDMA_CH_ATTR_ALTSELECT is used to select the alternate control
//!   structure for this channel
//! - \b UDMA_CH_ATTR_HIGH_PRIORITY is used to set this channel to high priority
//! - \b UDMA_CH_ATTR_REQMASK is used to mask the hardware request signal from
//!   the peripheral for this channel
//
//*****************************************************************************
extern uint32_t
UDMA_getChannelAttribute(uint32_t base, uint32_t channelNum);

//*****************************************************************************
//
//! Sets the transfer parameters for a uDMA channel control structure.
//!
//! \param base is the base address of the uDMA instance used.
//! \param index is the index for channel control structure.
//! \param transferMode is the type of uDMA transfer mode.
//! \param srcAddr is the source address for the transfer.
//! \param dstAddr is the destination address for the transfer.
//! \param transferSize is the number of data items to transfer.
//!
//! This function is used to configure the parameters for a uDMA transfer.
//! These parameters are not typically changed often.  The function
//! UDMA_setChannelControlParams() MUST be called at least once for this
//! channel prior to calling this function.
//!
//! The \e index parameter should be the logical OR of the
//! channel number with one of \b UDMA_PRI_SELECT or \b UDMA_ALT_SELECT to
//! choose whether the primary or alternate data structure is used.
//!
//! The \e mode parameter should be one of the following values:
//!
//! - \b UDMA_MODE_STOP stops the uDMA transfer. The controller sets the mode
//!   to this value at the end of a transfer.
//! - \b UDMA_MODE_BASIC to perform a basic transfer based on request.
//! - \b UDMA_MODE_AUTO to perform a transfer that always completes once
//!   started even if the request is removed.
//! - \b UDMA_MODE_PINGPONG to set up a transfer that switches between the
//!   primary and alternate control structures for the channel.  This mode
//!   allows use of ping-pong buffering for uDMA transfers.
//! - \b UDMA_MODE_MEM_SCATTER_GATHER to set up a memory scatter-gather
//!   transfer.
//! - \b UDMA_MODE_PER_SCATTER_GATHER to set up a peripheral scatter-gather
//!   transfer.
//!
//! The \e srcAddr and \e dstAddr parameters are pointers to the first
//! location of the data to be transferred.  These addresses should be aligned
//! according to the item size.  The compiler takes care of this alignment if
//! the pointers are pointing to storage of the appropriate data type.
//!
//! The \e transferSize parameter is the number of data items, not the
//! number of bytes.
//!
//! The two scatter-gather modes, memory and peripheral, are actually different
//! depending on whether the primary or alternate control structure is
//! selected.  This function looks for the \b UDMA_PRI_SELECT and
//! \b UDMA_ALT_SELECT flag along with the channel number and sets the
//! scatter-gather mode as appropriate for the primary or alternate control
//! structure.
//!
//! The channel must also be enabled using UDMA_enableChannel() after calling
//! this function.  The transfer does not begin until the channel has been
//! configured and enabled.  Note that the channel is automatically disabled
//! after the transfer is completed, meaning that UDMA_enableChannel() must
//! be called again after setting up the next transfer.
//!
//! \note Great care must be taken to not modify a channel control structure
//! that is in use or else the results are unpredictable, including the
//! possibility of undesired data transfers to or from memory or peripherals.
//! For BASIC and AUTO modes, it is safe to make changes when the channel is
//! disabled, or the uDMA_getChannelMode() returns \b UDMA_MODE_STOP.  For
//! PINGPONG or one of the SCATTER_GATHER modes, it is safe to modify the
//! primary or alternate control structure only when the other is being used.
//! The uDMA_getChannelMode() function returns \b UDMA_MODE_STOP when a
//! channel control structure is inactive and safe to modify.
//!
//! \return None.
//
//*****************************************************************************
extern void
UDMA_setChannelTransferParams(uint32_t base, uint32_t index, void *srcAddr,
                              void *dstAddr, uint32_t transferMode,
                              uint32_t transferSize);

//*****************************************************************************
//
//! Gets the current transfer size for a uDMA channel control structure.
//!
//! \param base is the base address of the uDMA instance used.
//! \param index is the index for channel control structure.
//!
//! This function is used to get the uDMA transfer size for a channel.  The
//! transfer size is the number of items to transfer, where the size of an item
//! might be 8, 16, or 32 bits.  If a partial transfer has already occurred,
//! then the number of remaining items is returned.  If the transfer is
//! complete, then 0 is returned.
//!
//! \return Returns the number of items remaining to transfer.
//
//*****************************************************************************
extern uint32_t
UDMA_getChannelTransferSize(uint32_t base, uint32_t index);

//*****************************************************************************
//
//! Configures a uDMA channel for scatter-gather mode.
//!
//! \param base is the base address of the uDMA instance used.
//! \param channelNum is the uDMA channel number.
//! \param taskCount is the number of scatter-gather tasks to execute.
//! \param taskList is a pointer to the beginning of the scatter-gather
//! task list.
//! \param isPeriphScatterGather is a flag to indicate it is a peripheral
//! scatter-gather transfer (else it is memory scatter-gather transfer)
//!
//! This function is used to configure a channel for scatter-gather mode.
//! The caller must have already set up a task list and must pass a pointer to
//! the start of the task list as the \e taskList parameter.  The
//! \e taskCount parameter is the count of tasks in the task list, not the
//! size of the task list.  The flag \e isPeriphScatterGather should be used to
//! indicate if scatter-gather should be configured for peripheral or memory
//! operation.
//!
//! \sa UDMA_TASK_STRUCT_ENTRY
//!
//! \return None.
//
//*****************************************************************************
extern void
UDMA_setChannelScatterGatherMode(uint32_t base, uint32_t channelNum,
                                uint32_t taskCount, UDMA_ControlTable *taskList,
                                bool isPeriphScatterGather);

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // UDMA_H
