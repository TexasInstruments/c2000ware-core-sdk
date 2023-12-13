//#############################################################################
// FILE: usbdcomp.h
// TITLE: USB composite device class driver
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

#ifndef __USBDCOMP_H__
#define __USBDCOMP_H__

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
// Return to default packing when using the IAR Embedded Workbench compiler.
//
//*****************************************************************************
#ifdef __ICCARM__
#pragma pack()
#endif

//*****************************************************************************
//
//! \addtogroup composite_device_class_api
//! @{
//
//*****************************************************************************

//
// Defines a single entry in a table of device types supported by the composite
// device.
//
typedef struct
{
    //
    // This is set internally by the composite class so it can be left
    // uninitialized by the application.
    //
    const tDeviceInfo *psDeviceInfo;

    //
    // This should be the header to the configuration header for a class.
    //
    const tConfigHeader *psConfigHeader;

    //
    // The offset to this devices interface, filled in by the composite class.
    //
    uint8_t ui8IfaceOffset;
}
tUSBDCompositeEntry;

//*****************************************************************************
//
// PRIVATE
//
// This structure defines the private instance data and state variables for the
// composite device class.  The memory for this structure is included in
// the sPrivateData field in the tUSBDCompositeDevice structure passed on
// USBDCompositeInit() and should not be modified by any code outside of the
// composite device code.
//
//*****************************************************************************
typedef struct
{
    //
    // Saves which USB controller is in use.
    //
    uint32_t ui32USBBase;

    //
    // The device information pointer.
    //
    tDeviceInfo sDevInfo;

    //
    // This is the configuration descriptor for this instance.
    //
    tConfigDescriptor sConfigDescriptor;

    //
    // This is the device descriptor for this instance.
    //
    tDeviceDescriptor sDeviceDescriptor;

    //
    // The configuration header for this instance.
    //
    tConfigHeader sCompConfigHeader;

    //
    // These are the configuration sections that will be built from the
    // Configuration Descriptor header and the descriptors from the devices
    // that are part of this composite device.
    //
    tConfigSection psCompSections[2];
    tConfigSection *ppsCompSections[2];

    //
    // The size and pointer to the data used by the instance.
    //
    uint32_t ui32DataSize;
    uint8_t *pui8Data;

    //
    // The current "owner" of endpoint 0.  This is used to track the device
    // class which is currently transferring data on EP0.
    //
    uint32_t ui32EP0Owner;
}
tCompositeInstance;

//*****************************************************************************
//
//! The structure used by the application to define operating parameters for
//! the composite device class.
//
//*****************************************************************************
typedef struct
{
    //
    //! The vendor ID that this device is to present in the device descriptor.
    //
    const uint16_t ui16VID;

    //
    //! The product ID that this device is to present in the device descriptor.
    //
    const uint16_t ui16PID;

    //
    //! The maximum power consumption of the device, expressed in mA.
    //
    const uint16_t ui16MaxPowermA;

    //
    //! Indicates whether the device is self or bus-powered and whether or not
    //! it supports remote wake up.  Valid values are USB_CONF_ATTR_SELF_PWR or
    //! USB_CONF_ATTR_BUS_PWR, optionally ORed with USB_CONF_ATTR_RWAKE.
    //
    const uint8_t ui8PwrAttributes;

    //
    //! A pointer to the callback function which will be called to notify
    //! the application of events relating to the operation of the composite
    //! device.
    //
    const tUSBCallback pfnCallback;

    //
    //! A pointer to the string descriptor array for this device.  This array
    //! must contain the following string descriptor pointers in this order.
    //! Language descriptor, Manufacturer name string (language 1), Product
    //! name string (language 1), Serial number string (language 1), Composite
    //! device interface description string (language 1), Configuration
    //! description string (language 1).
    //!
    //! If supporting more than 1 language, the descriptor block (except for
    //! string descriptor 0) must be repeated for each language defined in the
    //! language descriptor.
    //!
    //
    const uint8_t * const *ppui8StringDescriptors;

    //
    //! The number of descriptors provided in the ppStringDescriptors
    //! array.  This must be 1 + ((5 + (number of strings)) *
    //!                           (number of languages)).
    //
    const uint32_t ui32NumStringDescriptors;

    //
    //! The number of devices in the psDevices array.
    //
   const  uint32_t ui32NumDevices;

    //
    //! This application supplied array holds the the top level device class
    //! information as well as the Instance data for that class.
    //
    tCompositeEntry * const psDevices;

    //
    //! The private data for this device instance.  This memory must remain
    //! accessible for as long as the composite device is in use and must
    //! not be modified by any code outside the composite class driver.
    //
    tCompositeInstance sPrivateData;
}
tUSBDCompositeDevice;

//*****************************************************************************
//
// Return to default packing when using the IAR Embedded Workbench compiler.
//
//*****************************************************************************
#ifdef __ICCARM__
#pragma pack()
#endif

//*****************************************************************************
//
// Composite specific device class driver events
//
//*****************************************************************************

//*****************************************************************************
//
// API Function Prototypes
//
//*****************************************************************************
extern void *USBDCompositeInit(uint32_t ui32Index,
                               tUSBDCompositeDevice *psCompDevice,
                               uint32_t ui32Size, uint8_t *pui8Data);
extern void USBDCompositeTerm(void *pvInstance);

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

#endif

