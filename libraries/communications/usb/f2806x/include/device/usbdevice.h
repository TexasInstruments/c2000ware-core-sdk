//#############################################################################
// FILE: usbdevice.h
// TITLE: types and definitions used during USB enumeration
//#############################################################################
// $TI Release: $
// $Release Date: $
// $Copyright:
// Copyright (C) 2009-2023 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef __USBDEVICE_H__
#define __USBDEVICE_H__

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
//! \addtogroup device_api
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! The maximum number of independent interfaces that any single device
//! implementation can support.  Independent interfaces means interface
//! descriptors with different bInterfaceNumber values - several interface
//! descriptors offering different alternative settings but the same interface
//! number count as a single interface.
//
//*****************************************************************************
#define USB_MAX_INTERFACES_PER_DEVICE 8

#include "usbdevicepriv.h"

//*****************************************************************************
//
//! This structure is passed to the USB library on a call to USBDCDInit and
//! provides the library with information about the device that the
//! application is implementing.  It contains functions pointers for the
//! various USB event handlers and pointers to each of the standard device
//! descriptors.
//
//*****************************************************************************
struct tDeviceInfo
{
    //
    //! A pointer to a structure containing pointers to event handler functions
    //! provided by the client to support the operation of this device.
    //
    const tCustomHandlers * psCallbacks;

    //
    //! A pointer to the device descriptor for this device.
    //
    const uint8_t *pui8DeviceDescriptor;

    //
    //! A pointer to an array of configuration descriptor pointers.  Each entry
    //! in the array corresponds to one configuration that the device may be
    //! set to use by the USB host.  The number of entries in the array must
    //! match the bNumConfigurations value in the device descriptor
    //! array, pui8DeviceDescriptor.
    //
    const tConfigHeader * const *ppsConfigDescriptors;

    //
    //! A pointer to the string descriptor array for this device.  This array
    //! must be arranged as follows:
    //!
    //!   - [0]   - Standard descriptor containing supported language codes.
    //!   - [1]   - String 1 for the first language listed in descriptor 0.
    //!   - [2]   - String 2 for the first language listed in descriptor 0.
    //!   - ...
    //!   - [n]   - String n for the first language listed in descriptor 0.
    //!   - [n+1] - String 1 for the second language listed in descriptor 0.
    //!   - ...
    //!   - [2n]  - String n for the second language listed in descriptor 0.
    //!   - [2n+1]- String 1 for the third language listed in descriptor 0.
    //!   - ...
    //!   - [3n]  - String n for the third language listed in descriptor 0.
    //!
    //! and so on.
    //
    const uint8_t * const *ppui8StringDescriptors;

    //
    //! The total number of descriptors provided in the ppStringDescriptors
    //! array.
    //
    uint32_t ui32NumStringDescriptors;
};

//*****************************************************************************
//
//! This type is used by an application to describe and instance of a device
//! and an instance data pointer for that class.  The psDevice pointer should
//! be a pointer to a valid device class to include in the composite device.
//! The pvInstance pointer should be a pointer to an instance pointer for the
//! device in the psDevice pointer.
//!
//
//*****************************************************************************
typedef struct
{
    //
    //! This is the top level device information structure.
    //
    const tDeviceInfo *psDevInfo;

    //
    //! This is the instance data for the device structure.
    //
    void *pvInstance;

    //
    //! A per-device workspace used by the composite device.
    //
    uint32_t ui32DeviceWorkspace;
}
tCompositeEntry;

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
// Public APIs offered by the USB library device control driver.
//
//*****************************************************************************
extern void USBDCDInit(uint32_t ui32Index, tDeviceInfo *psDevice,
                       void *pvDCDCBData);
extern void USBDCDTerm(uint32_t ui32Index);
extern void USBDCDStallEP0(uint32_t ui32Index);
extern void USBDCDRequestDataEP0(uint32_t ui32Index, uint8_t *pui8Data,
                                 uint32_t ui32Size);
extern void USBDCDSendDataEP0(uint32_t ui32Index, uint8_t *pui8Data,
                              uint32_t ui32Size);
extern void USBDCDSetDefaultConfiguration(uint32_t ui32Index,
                                          uint32_t ui32DefaultConfig);
extern uint32_t USBDCDConfigDescGetSize(const tConfigHeader *psConfig);
extern uint32_t USBDCDConfigDescGetNum(const tConfigHeader *psConfig,
                                       uint32_t ui32Type);
extern tDescriptorHeader *USBDCDConfigDescGet(const tConfigHeader *psConfig,
                                              uint32_t ui32Type,
                                              uint32_t ui32Index,
                                              uint32_t *pui32Section);
extern uint32_t
       USBDCDConfigGetNumAlternateInterfaces(const tConfigHeader *psConfig,
                                             uint8_t ui8InterfaceNumber);
extern tInterfaceDescriptor *
       USBDCDConfigGetInterface(const tConfigHeader *psConfig,
                                uint32_t ui32Index, uint32_t ui32AltCfg,
                                uint32_t *pui32Section);
extern tEndpointDescriptor *
       USBDCDConfigGetInterfaceEndpoint(const tConfigHeader *psConfig,
                                        uint32_t ui32InterfaceNumber,
                                        uint32_t ui32AltCfg,
                                        uint32_t ui32Index);
extern void USBDCDPowerStatusSet(uint32_t ui32Index, uint8_t ui8Power);
extern bool USBDCDRemoteWakeupRequest(uint32_t ui32Index);

//*****************************************************************************
//
// Device mode interrupt handler for controller index 0.
//
//*****************************************************************************
extern void USB0DeviceIntHandler(void);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __USBENUM_H__
