//#############################################################################
// FILE: usbdma.c
// TITLE: USB Library DMA handling functions.
//#############################################################################
//!
//! Copyright: Copyright (C) 2023 Texas Instruments Incorporated -
//!	All rights reserved not granted herein.
//!	Limited License.
//!
//! Texas Instruments Incorporated grants a world-wide, royalty-free,
//! non-exclusive license under copyrights and patents it now or hereafter
//! owns or controls to make, have made, use, import, offer to sell and sell
//! ("Utilize") this software subject to the terms herein. With respect to the
//! foregoing patent license, such license is granted solely to the extent that
//! any such patent is necessary to Utilize the software alone. The patent
//! license shall not apply to any combinations which include this software,
//! other than combinations with devices manufactured by or for TI 
//! ("TI Devices").
//! No hardware patent is licensed hereunder.
//!
//! Redistributions must preserve existing copyright notices and reproduce this
//! license (including the above copyright notice and the disclaimer and
//! (if applicable) source code license limitations below) in the documentation
//!  and/or other materials provided with the distribution.
//!
//! Redistribution and use in binary form, without modification, are permitted
//! provided that the following conditions are met:
//!
//! * No reverse engineering, decompilation, or disassembly of this software is 
//! permitted with respect to any software provided in binary form.
//! * Any redistribution and use are licensed by TI for use only 
//!   with TI Devices.
//! * Nothing shall obligate TI to provide you with source code for the 
//!   software licensed and provided to you in object code.
//!
//! If software source code is provided to you, modification and redistribution
//! of the source code are permitted provided that the following conditions 
//! are met:
//!
//! * any redistribution and use of the source code, including any resulting
//!   derivative works, are licensed by TI for use only with TI Devices.
//! * any redistribution and use of any object code compiled from the source
//!   code and any resulting derivative works, are licensed by TI for use 
//!   only with TI Devices.
//!
//! Neither the name of Texas Instruments Incorporated nor the names of its
//! suppliers may be used to endorse or promote products derived from this 
//! software without specific prior written permission.
//#############################################################################


#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "debug.h"
#include "interrupt.h"
#include "usb.h"
#include "include/usblib.h"
#include "include/usblibpriv.h"

//*****************************************************************************
//
//! \addtogroup usblib_dma_api Internal USB DMA functions
//! @{
//
//*****************************************************************************

static tUSBDMAInstance g_psUSBDMAInst[1];

//*****************************************************************************
//
// Macros used to determine if a uDMA endpoint configuration is used for
// receive or transmit.
//
//*****************************************************************************
#define UDMAConfigIsRx(ui32Config)                                            \
        ((ui32Config & UDMA_SRC_INC_NONE) == UDMA_SRC_INC_NONE)
#define UDMAConfigIsTx(ui32Config)                                            \
        ((ui32Config & UDMA_DEST_INC_NONE) == UDMA_DEST_INC_NONE)

//*****************************************************************************
//
// USBLibDMAChannelStatus() for USB controllers that use the uDMA for DMA.
//
//*****************************************************************************
static uint32_t
uDMAUSBChannelStatus(tUSBDMAInstance *psUSBDMAInst, uint32_t ui32Channel)
{
    uint32_t ui32Status;

    //
    // Initialize the current status to no events.
    //
    ui32Status = USBLIBSTATUS_DMA_IDLE;


    return(ui32Status);
}

//*****************************************************************************
//
// USBLibDMAIntStatus() for USB controllers that use uDMA.
//
//*****************************************************************************
static uint32_t
uDMAUSBIntStatus(tUSBDMAInstance *psUSBDMAInst)
{

	return(0);
}

//*****************************************************************************
//
// USBLibDMAIntStatusClear() for USB controllers that use uDMA for DMA.
//
//*****************************************************************************
static void
DMAUSBIntStatusClear(tUSBDMAInstance *psUSBDMAInst, uint32_t ui32Status)
{
    //
    // Clear out the requested interrupts.  Since the USB interface does not
    // have a true interrupt clear, this clears the current completed
    // status for the requested channels.
    //
    psUSBDMAInst->ui32Complete &= ~ui32Status;

    return;
}

//*****************************************************************************
//
// USBLibDMAIntHandler() for USB controllers that use uDMA for DMA.
//
//*****************************************************************************
static void
DMAUSBIntHandler(tUSBDMAInstance *psUSBDMAInst, uint32_t ui32DMAIntStatus)
{
    uint32_t ui32Channel;

    if(ui32DMAIntStatus == 0)
    {
        return;
    }

    //
    // Determine if the uDMA is used or the USB DMA controller.
    //
    for(ui32Channel = 0; ui32Channel < USB_MAX_DMA_CHANNELS; ui32Channel++)
    {
        //
        // Mark any pending interrupts as completed.
        //
        if(ui32DMAIntStatus & 1)
        {
            psUSBDMAInst->ui32Pending &= ~((uint32_t)1 << ui32Channel);
            psUSBDMAInst->ui32Complete |= ((uint32_t)1 << ui32Channel);
        }

        //
        // Check the next channel.
        //
        ui32DMAIntStatus >>= 1;

        //
        // Break if there are no more pending DMA interrupts.
        //
        if(ui32DMAIntStatus == 0)
        {
            break;
        }
    }
}

//*****************************************************************************
//
// USBLibDMAChannelEnable() for USB controllers that use uDMA.
//
//*****************************************************************************
static void
uDMAUSBChannelEnable(tUSBDMAInstance *psUSBDMAInst, uint32_t ui32Channel)
{

}

//*****************************************************************************
//
// USBLibDMAChannelDisable() for USB controllers that use uDMA.
//
//*****************************************************************************
static void
uDMAUSBChannelDisable(tUSBDMAInstance *psUSBDMAInst, uint32_t ui32Channel)
{

}

//*****************************************************************************
//
// USBLibDMAChannelIntEnable() for USB controllers that use uDMA.
//
//*****************************************************************************
static void
uDMAUSBChannelIntEnable(tUSBDMAInstance *psUSBDMAInst, uint32_t ui32Channel)
{
    //
    // There is no way to Enable channel interrupts when using uDMA.
    //
}

//*****************************************************************************
//
// USBLibDMAChannelIntDisable() for USB controllers that use uDMA.
//
//*****************************************************************************
static void
uDMAUSBChannelIntDisable(tUSBDMAInstance *psUSBDMAInst, uint32_t ui32Channel)
{
    //
    // There is no way to Disable channel interrupts when using uDMA.
    //
}

//*****************************************************************************
//
// USBLibDMATransfer() for USB controllers that use the uDMA controller.
//
//*****************************************************************************
static uint32_t
uDMAUSBTransfer(tUSBDMAInstance *psUSBDMAInst, uint32_t ui32Channel,
                void *pvBuffer, uint32_t ui32Size)
{

        return(0);

}

//*****************************************************************************
//
// USBLibDMAChannelAllocate() for USB controllers that use uDMA for DMA.
//
//*****************************************************************************
static uint32_t
uDMAUSBChannelAllocate(tUSBDMAInstance *psUSBDMAInst, uint8_t ui8Endpoint,
                       uint32_t ui32MaxPacketSize, uint32_t ui32Config)
{

    return(0);
}

//*****************************************************************************
//
// USBLibDMAChannelRelease() for USB controllers that use uDMA for DMA.
//
//*****************************************************************************
static void
uDMAUSBChannelRelease(tUSBDMAInstance *psUSBDMAInst, uint8_t ui32Channel)
{

}

//*****************************************************************************
//
// USBLibDMAUnitSizeSet() for USB controllers that use uDMA for DMA.
//
//*****************************************************************************
static void
uDMAUSBUnitSizeSet(tUSBDMAInstance *psUSBDMAInst, uint32_t ui32Channel,
                   uint32_t ui32BitSize)
{

}

//*****************************************************************************
//
// USBLibDMAArbSizeSet() for USB controllers that use uDMA for DMA.
//
//*****************************************************************************
static void
uDMAUSBArbSizeSet(tUSBDMAInstance *psUSBDMAInst, uint32_t ui32Channel,
                  uint32_t ui32ArbSize)
{

}

//*****************************************************************************
//
// USBLibDMAStatus() for USB controllers that use uDMA for DMA.
//
//*****************************************************************************
static uint32_t
DMAUSBStatus(tUSBDMAInstance *psUSBDMAInst)
{
    return(0);
}

//*****************************************************************************
//
//! This function is used to initialize the DMA interface for a USB instance.
//!
//! \param ui32Index is the index of the USB controller for this instance.
//!
//! This function performs any initialization and configuration of the DMA
//! portions of the USB controller.  This function returns a pointer that
//! is used with the remaining USBLibDMA APIs or the function returns zero
//! if the requested controller cannot support DMA.  If this function is called
//! when already initialized it will not reinitialize the DMA controller and
//! will instead return the previously initialized DMA instance.
//!
//! \return A pointer to use with USBLibDMA APIs.
//
//*****************************************************************************
tUSBDMAInstance *
USBLibDMAInit(uint32_t ui32Index)
{
    uint32_t ui32Channel;

    ASSERT(ui32Index == USB_BASE);

    //
    // Save the base address of the USB controller.
    //
    g_psUSBDMAInst[0].ui32Base = ui32Index;

    //
    // Save the interrupt number for the USB controller.
    //
    g_psUSBDMAInst[0].ui32IntNum = INT_USB;

    //
    // Initialize the function pointers.
    //
    g_psUSBDMAInst[0].pfnArbSizeSet = uDMAUSBArbSizeSet;
    g_psUSBDMAInst[0].pfnChannelAllocate = uDMAUSBChannelAllocate;
    g_psUSBDMAInst[0].pfnChannelDisable = uDMAUSBChannelDisable;
    g_psUSBDMAInst[0].pfnChannelEnable = uDMAUSBChannelEnable;
    g_psUSBDMAInst[0].pfnChannelIntEnable = uDMAUSBChannelIntEnable;
    g_psUSBDMAInst[0].pfnChannelIntDisable = uDMAUSBChannelIntDisable;
    g_psUSBDMAInst[0].pfnChannelRelease = uDMAUSBChannelRelease;
    g_psUSBDMAInst[0].pfnChannelStatus = uDMAUSBChannelStatus;
    g_psUSBDMAInst[0].pfnIntHandler = DMAUSBIntHandler;
    g_psUSBDMAInst[0].pfnIntStatus = uDMAUSBIntStatus;
    g_psUSBDMAInst[0].pfnIntStatusClear = DMAUSBIntStatusClear;
    g_psUSBDMAInst[0].pfnStatus = DMAUSBStatus;
    g_psUSBDMAInst[0].pfnTransfer = uDMAUSBTransfer;
    g_psUSBDMAInst[0].pfnUnitSizeSet = uDMAUSBUnitSizeSet;

    //
    // Clear out the endpoint and the current configuration.
    //
    for(ui32Channel = 0; ui32Channel < USB_MAX_DMA_CHANNELS; ui32Channel++)
    {
        g_psUSBDMAInst[0].pui8Endpoint[ui32Channel] = 0;
        g_psUSBDMAInst[0].pui32Config[ui32Channel] = 0;
        g_psUSBDMAInst[0].ui32Pending = 0;
        g_psUSBDMAInst[0].ui32Complete = 0;
    }
    return(&g_psUSBDMAInst[0]);
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
