//#############################################################################
// FILE: usbdesc.c
// TITLE: USB descriptor parsing functions
//#############################################################################
// $TI Release: $
// $Release Date: $
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

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_types.h"
#include "include/usblib.h"

//*****************************************************************************
//
// Assumptions:
// ------------
//
// The following assumptions are made in this module.  From reading chapter 9
// of the USB 2.0 specification, these appear to be perfectly valid.
//
// 1.  The interface number, bInterfaceNumber in the interface descriptor, is
//     a zero based index and takes values between 0 and
//     (pConfigDescriptor->bNumInterfaces - 1) inclusive.
// 2.  Similarly, the alternate setting number, bAlternateSetting in the
//     interface descriptor, is a zero based index.
// 3.  Interface descriptors are ordered by interface number in the
//     configuration descriptor.
// 4.  If alternate settings are available for an interface, the interface
//     descriptors are ordered by alternate setting value bAlternateSetting.
// 5.  Although the endpoints associated with a given interface must follow
//     their associated interface descriptor, it is possible for other,
//     device specific descriptors to be found between an interface descriptor
//     and its endpoints or between endpoint descriptors for the same
//     interface.
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup general_usblib_api
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! Determines the number of individual descriptors of a particular type within
//! a supplied buffer.
//!
//! \param psDesc points to the first byte of a block of standard USB
//! descriptors.
//! \param ui32Size is the number of bytes of descriptor data found at pointer
//! \e psDesc.
//! \param ui32Type identifies the type of descriptor that is to be counted.
//! If the value is \b USB_DESC_ANY, the function returns the total number of
//! descriptors regardless of type.
//!
//! This function can be used to count the number of descriptors of a
//! particular type within a block of descriptors.  The caller can provide a
//! specific type value which the function matches against the second byte of
//! each descriptor or, alternatively, can specify \b USB_DESC_ANY to have the
//! function count all descriptors regardless of their type.
//!
//! \return Returns the number of descriptors found in the supplied block of
//! data.
//
//*****************************************************************************
uint32_t
USBDescGetNum(tDescriptorHeader *psDesc,  uint32_t ui32Size,
              uint32_t ui32Type)
{
    tDescriptorHeader *psDescCheck;
    uint32_t ui32TotLength;
    uint32_t ui32Count;

    //
    // Set up for our descriptor counting loop.
    //
    psDescCheck = psDesc;
    ui32TotLength = 0;
    ui32Count = 0;

    //
    // Keep looking through the supplied data until we reach the end.
    //
    while(ui32TotLength < ui32Size)
    {
        //
        // Does this descriptor match the type passed (if a specific type
        // has been specified)?
        //
        if((ui32Type == USB_DESC_ANY) ||
           (psDescCheck->bDescriptorType == (uint8_t)(ui32Type & 0xFF)))
        {
            ui32Count++;
        }

        //
        // Move on to the next descriptor.
        //
        ui32TotLength += (uint32_t)psDescCheck->bLength;
        psDescCheck = NEXT_USB_DESCRIPTOR(psDescCheck);
    }

    //
    // Return the descriptor count to the caller.
    //
    return(ui32Count);
}

//*****************************************************************************
//
//! Determines the number of individual descriptors of a particular type within
//! a supplied buffer.
//!
//! \param psDesc points to the first byte of a block of standard USB
//! descriptors.
//! \param ui32Size is the number of bytes of descriptor data found at pointer
//! \e psDesc.
//! \param ui32Type identifies the type of descriptor that is to be found.  If
//! the value is \b USB_DESC_ANY, the function returns a pointer to the n-th
//! descriptor regardless of type.
//! \param ui32Index is the zero based index of the descriptor whose pointer is
//! to be returned.  For example, passing value 1 in \e ui32Index returns the
//! second matching descriptor.
//!
//! Return a pointer to the n-th descriptor of a particular type found in the
//! block of \e ui32Size bytes starting at \e psDesc.
//!
//! \return Returns a pointer to the header of the required descriptor if
//! found or NULL otherwise.
//
//*****************************************************************************
tDescriptorHeader *
USBDescGet(tDescriptorHeader *psDesc,  uint32_t ui32Size,
           uint32_t ui32Type, uint32_t ui32Index)
{
    tDescriptorHeader *psDescCheck;
    uint32_t ui32TotLength;
    uint32_t ui32Count;

    //
    // Set up for our descriptor counting loop.
    //
    psDescCheck = psDesc;
    ui32TotLength = 0;
    ui32Count = 0;

    //
    // Keep looking through the supplied data until we reach the end.
    //
    while(ui32TotLength < ui32Size)
    {
        //
        // Does this descriptor match the type passed (if a specific type
        // has been specified)?
        //
        if((ui32Type == USB_DESC_ANY) ||
           (psDescCheck->bDescriptorType == (uint8_t)(ui32Type & 0xFF)))
        {
            //
            // We found a matching descriptor.  If our count matches the
            // supplied index, we are done so return the pointer.
            //
            if(ui32Count == ui32Index)
            {
                return(psDescCheck);
            }

            //
            // We have not found enough descriptors yet to satisfy the supplied
            // index so increment our count and continue.
            //
            ui32Count++;
        }

        //
        // Move on to the next descriptor.
        //
        ui32TotLength += (uint32_t)psDescCheck->bLength;
        psDescCheck = NEXT_USB_DESCRIPTOR(psDescCheck);
    }

    //
    // If we get here, we reached the end of the data without finding the
    // required descriptor.  Return NULL.
    //
    return((tDescriptorHeader *)0);
}

//*****************************************************************************
//
//! Determines the number of different alternate configurations for a given
//! interface within a configuration descriptor.
//!
//! \param psConfig points to the first byte of a standard USB configuration
//! descriptor.
//! \param ui8InterfaceNumber is the interface number for which the number of
//! alternate configurations is to be counted.
//!
//! This function can be used to count the number of alternate settings for a
//! specific interface within a configuration.
//!
//! \return Returns the number of alternate versions of the specified interface
//! or 0 if the interface number supplied cannot be found in the config
//! descriptor.
//
//*****************************************************************************
uint32_t
USBDescGetNumAlternateInterfaces(tConfigDescriptor *psConfig,
                                 uint8_t ui8InterfaceNumber)
{
    tDescriptorHeader *psDescCheck;
    uint32_t ui32TotLength;
    uint32_t ui32Count;

    //
    // Set up for our descriptor counting loop.
    //
    psDescCheck = (tDescriptorHeader *)psConfig;
    ui32TotLength = 0;
    ui32Count = 0;

    //
    // Keep looking through the supplied data until we reach the end.
    //
    while(ui32TotLength < (uint32_t)readusb16_t(&(psConfig->wTotalLength)))
    {
        //
        // Is this an interface descriptor with the required interface number?
        //
        if((psDescCheck->bDescriptorType == USB_DTYPE_INTERFACE) &&
            (((tInterfaceDescriptor *)psDescCheck)->bInterfaceNumber ==
             ui8InterfaceNumber))
        {
            //
            // Yes - increment our count.
            //
            ui32Count++;
        }

        //
        // Move on to the next descriptor.
        //
        ui32TotLength += (uint32_t)psDescCheck->bLength;
        psDescCheck = NEXT_USB_DESCRIPTOR(psDescCheck);
    }

    //
    // Return the descriptor count to the caller.
    //
    return(ui32Count);
}

//*****************************************************************************
//
//! Returns a pointer to the n-th interface descriptor in a config descriptor
//! with the supplied interface number.
//!
//! \param psConfig points to the first byte of a standard USB configuration
//! descriptor.
//! \param ui8InterfaceNumber is the interface number of the descriptor that is
//! being queried.
//! \param ui32Index is the zero based index of the descriptor to return.
//!
//! This function returns a pointer to the n-th interface descriptor in the
//! supplied configuration which has the requested interface number.  It may be
//! used by a client to retrieve the descriptors for each alternate setting
//! of a given interface within the configuration passed.
//!
//! \return Returns a pointer to the n-th interface descriptor with interface
//! number as specified or NULL of this descriptor does not exist.
//
//*****************************************************************************
static tInterfaceDescriptor *
USBDescGetAlternateInterface(tConfigDescriptor *psConfig,
                             uint8_t ui8InterfaceNumber,
                             uint32_t ui32Index)
{
    tDescriptorHeader *psDescCheck;
    uint32_t ui32TotLength;
    uint32_t ui32Count;

    //
    // Set up for our descriptor counting loop.
    //
    psDescCheck = (tDescriptorHeader *)psConfig;
    ui32TotLength = 0;
    ui32Count = 0;

    //
    // Keep looking through the supplied data until we reach the end.
    //
    while(ui32TotLength < (uint32_t)readusb16_t(&(psConfig->wTotalLength)))
    {
        //
        // Does this descriptor match the type passed (if a specific type
        // has been specified)?
        //
        if((psDescCheck->bDescriptorType == USB_DTYPE_INTERFACE) &&
            (((tInterfaceDescriptor *)psDescCheck)->bInterfaceNumber ==
             ui8InterfaceNumber))
        {
            //
            // This is an interface descriptor for interface
            // ui8InterfaceNumber.  Determine if this is the n-th one we have
            // found and, if so, return its pointer.
            //
            if(ui32Count == ui32Index)
            {
                //
                // Found it - return the pointer.
                //
                return((tInterfaceDescriptor *)psDescCheck);
            }

            //
            // Increment our count of matching descriptors found and go back
            // to look for another since we have not yet reached the n-th
            // match.
            //
            ui32Count++;
        }

        //
        // Move on to the next descriptor.
        //
        ui32TotLength += (uint32_t)psDescCheck->bLength;
        psDescCheck = NEXT_USB_DESCRIPTOR(psDescCheck);
    }

    //
    // If we drop out the end of the loop, we did not find the requested
    // descriptor so return NULL.
    //
    return((tInterfaceDescriptor *)0);
}

//*****************************************************************************
//
//! Returns a pointer to the n-th interface descriptor in a configuration
//! descriptor that applies to the supplied alternate setting number.
//!
//! \param psConfig points to the first byte of a standard USB configuration
//! descriptor.
//! \param ui32Index is the zero based index of the interface that is to be
//! found.  If \e ui32Alt is set to a value other than \b USB_DESC_ANY, this
//! will be equivalent to the interface number being searched for.
//! \param ui32Alt is the alternate setting number which is to be
//! searched for.  If this value is \b USB_DESC_ANY, the alternate setting
//! is ignored and all interface descriptors are considered in the search.
//!
//! Return a pointer to the n-th interface descriptor found in the supplied
//! configuration descriptor.  If \e ui32Alt is not \b USB_DESC_ANY, only
//! interface descriptors which are part of the supplied alternate setting are
//! considered in the search otherwise all interface descriptors are
//! considered.
//!
//! Note that, although alternate settings can be applied on an interface-by-
//! interface basis, the number of interfaces offered is fixed for a given
//! config descriptor.  Hence, this function will correctly find the unique
//! interface descriptor for that interface's alternate setting number
//! \e ui32Alt if \e ui32Index is set to the required interface number and
//! \e ui32Alt is set to a valid alternate setting number for that interface.
//!
//! \return Returns a pointer to the required interface descriptor if
//! found or NULL otherwise.
//
//*****************************************************************************
tInterfaceDescriptor *
USBDescGetInterface(tConfigDescriptor *psConfig, uint32_t ui32Index,
                    uint32_t ui32Alt)
{
    //
    // If we are being told to ignore the alternate configuration, this boils
    // down to a very simple query.
    //
    if(ui32Alt == USB_DESC_ANY)
    {
        //
        // Return the ui32Index-th interface descriptor we find in the
        // configuration descriptor.
        //
        return((tInterfaceDescriptor *)USBDescGet(
                          (tDescriptorHeader *)psConfig,
                          (uint32_t)readusb16_t(&(psConfig->wTotalLength)),
                          USB_DTYPE_INTERFACE, ui32Index));
    }
    else
    {
        //
        // In this case, a specific alternate setting number is required.
        // Given that interface numbers are zero based indices, we can
        // pass the supplied ui32Index parameter directly as the interface
        // number to USBDescGetAlternateInterface to retrieve the requested
        // interface descriptor pointer.
        //
        return(USBDescGetAlternateInterface(psConfig, ui32Index, ui32Alt));
    }
}

//*****************************************************************************
//
//! Return a pointer to the n-th endpoint descriptor in the supplied
//! interface descriptor.
//!
//! \param psInterface points to the first byte of a standard USB interface
//! descriptor.
//! \param ui32Index is the zero based index of the endpoint that is to be
//! found.
//! \param ui32Size contains the maximum number of bytes that the function may
//! search beyond \e psInterface while looking for the requested endpoint
//! descriptor.
//!
//! Return a pointer to the n-th endpoint descriptor found in the supplied
//! interface descriptor.  If the \e ui32Index parameter is invalid (greater
//! than or equal to the bNumEndpoints field of the interface descriptor) or
//! the endpoint cannot be found within \e ui32Size bytes of the interface
//! descriptor pointer, the function will return NULL.
//!
//! Note that, although the USB 2.0 specification states that endpoint
//! descriptors must follow the interface descriptor that they relate to, it
//! also states that device specific descriptors should follow any standard
//! descriptor that they relate to.  As a result, we cannot assume that each
//! interface descriptor will be followed by nothing but an ordered list of
//! its own endpoints and, hence, the function needs to be provided \e ui32Size
//! to limit the search range.
//!
//! \return Returns a pointer to the requested endpoint descriptor if
//! found or NULL otherwise.
//
//*****************************************************************************
tEndpointDescriptor *
USBDescGetInterfaceEndpoint(tInterfaceDescriptor *psInterface,
                            uint32_t ui32Index, uint32_t ui32Size)
{
    //
    // Is the index passed valid?
    //
    if(ui32Index >= psInterface->bNumEndpoints)
    {
        //
        // It's out of bounds so return a NULL.
        //
        return((tEndpointDescriptor *)0);
    }
    else
    {
        //
        // Endpoint index is valid so find the descriptor.
        //
        return((tEndpointDescriptor *)USBDescGet(
                         (tDescriptorHeader *)psInterface,
                          ui32Size, USB_DTYPE_ENDPOINT, ui32Index));
    }
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
