//###########################################################################
//
// usb_mouse_structs.c - Data structures defining the USB mouse device.
//
//###########################################################################
// $TI Release:  $
// $Release Date: $
// $Copyright:
// Copyright (C) 2009-2024 Texas Instruments Incorporated - http://www.ti.com/
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


#include "inc/hw_types.h"
#include "driverlib/usb.h"
#include "usblib/usblib.h"
#include "usblib/usbhid.h"
#include "usblib/usb_ids.h"
#include "usblib/device/usbdevice.h"
#include "usblib/device/usbdhid.h"
#include "usblib/device/usbdhidmouse.h"
#include "usblib/device/usbddfu_rt.h"
#include "usblib/device/usbdcomp.h"
#include "usb_hiddfu_structs.h"

//*****************************************************************************
//
// The languages supported by this device.
//
//*****************************************************************************
const unsigned char g_pLangDescriptor[] =
{
    4,
    USB_DTYPE_STRING,
    USBShort(USB_LANG_EN_US)
};

//*****************************************************************************
//
// The manufacturer string.
//
//*****************************************************************************
const unsigned char g_pManufacturerString[] =
{
    (17 + 1) * 2,
    USB_DTYPE_STRING,
    'T', 0, 'e', 0, 'x', 0, 'a', 0, 's', 0, ' ', 0, 'I', 0, 'n', 0, 's', 0,
    't', 0, 'r', 0, 'u', 0, 'm', 0, 'e', 0, 'n', 0, 't', 0, 's', 0,
};

//*****************************************************************************
//
// The product string.
//
//*****************************************************************************
const unsigned char g_pProductString[] =
{
    (34 + 1) * 2,
    USB_DTYPE_STRING,
    'M', 0, 'o', 0, 'u', 0, 's', 0, 'e', 0, ' ', 0, 'w', 0, 'i', 0, 't', 0,
    'h', 0, ' ', 0, 'D', 0, 'e', 0, 'v', 0, 'i', 0, 'c', 0, 'e', 0, ' ', 0,
    'F', 0, 'i', 0, 'r', 0, 'm', 0, 'w', 0, 'a', 0, 'r', 0, 'e', 0, ' ', 0,
    'U', 0, 'p', 0, 'g', 0, 'r', 0, 'a', 0, 'd', 0, 'e', 0
};

//*****************************************************************************
//
// The serial number string.
//
//*****************************************************************************
const unsigned char g_pSerialNumberString[] =
{
    (8 + 1) * 2,
    USB_DTYPE_STRING,
    '1', 0, '2', 0, '3', 0, '4', 0, '5', 0, '6', 0, '7', 0, '8', 0
};

//*****************************************************************************
//
// The interface description string.
//
//*****************************************************************************
const unsigned char g_pHIDInterfaceString[] =
{
    (19 + 1) * 2,
    USB_DTYPE_STRING,
    'H', 0, 'I', 0, 'D', 0, ' ', 0, 'M', 0, 'o', 0, 'u', 0, 's', 0,
    'e', 0, ' ', 0, 'I', 0, 'n', 0, 't', 0, 'e', 0, 'r', 0, 'f', 0,
    'a', 0, 'c', 0, 'e', 0
};

//*****************************************************************************
//
// The configuration description string.
//
//*****************************************************************************
const unsigned char g_pConfigString[] =
{
    (23 + 1) * 2,
    USB_DTYPE_STRING,
    'H', 0, 'I', 0, 'D', 0, ' ', 0, 'M', 0, 'o', 0, 'u', 0, 's', 0,
    'e', 0, ' ', 0, 'C', 0, 'o', 0, 'n', 0, 'f', 0, 'i', 0, 'g', 0,
    'u', 0, 'r', 0, 'a', 0, 't', 0, 'i', 0, 'o', 0, 'n', 0
};

//*****************************************************************************
//
// The descriptor string table.
//
//*****************************************************************************
const unsigned char * const g_pStringDescriptors[] =
{
    g_pLangDescriptor,
    g_pManufacturerString,
    g_pProductString,
    g_pSerialNumberString,
    g_pHIDInterfaceString,
    g_pConfigString
};

#define NUM_STRING_DESCRIPTORS (sizeof(g_pStringDescriptors) /                \
                                sizeof(unsigned char *))

//*****************************************************************************
//
// The HID mouse device initialization and customization structures.
//
//*****************************************************************************
tHIDMouseInstance g_sMouseInstance;

const tUSBDHIDMouseDevice g_sMouseDevice =
{
    USB_VID_TI,
    USB_PID_COMP_HID_DFU,
    500,
    USB_CONF_ATTR_SELF_PWR,
    MouseHandler,
    (void *)&g_sMouseDevice,
    g_pStringDescriptors,
    NUM_STRING_DESCRIPTORS,
    &g_sMouseInstance
};

//*****************************************************************************
//
// The DFU runtime interface initialization and customization structures
//
//*****************************************************************************
tDFUInstance g_sDFUInstance;

const tUSBDDFUDevice g_sDFUDevice =
{
    DFUDetachCallback,
    (void *)&g_sDFUDevice,
    &g_sDFUInstance
};

//****************************************************************************
//
// The number of device class instances that this composite device will
// use.
//
//****************************************************************************
#define NUM_DEVICES         2

//****************************************************************************
//
// The array of devices supported by this composite device.
//
//****************************************************************************
tCompositeEntry g_psCompDevices[NUM_DEVICES]=
{
    //
    // HID Mouse Information.
    //
    {
        &g_sHIDDeviceInfo,
        0
    },

    //
    // Device Firmware Upgrade Runtime Interface.
    //
    {
        &g_sDFUDeviceInfo,
        0
    }
};

//****************************************************************************
//
// Additional workspace required by the composite driver to hold a lookup
// table allowing mapping of composite interface and endpoint numbers to
// individual device class instances.
//
//****************************************************************************
unsigned long g_pulCompWorkspace[NUM_DEVICES];

//****************************************************************************
//
// The instance data for this composite device.
//
//****************************************************************************
tCompositeInstance g_CompInstance;

//****************************************************************************
//
// Allocate the Device Data for the top level composite device class.
//
//****************************************************************************
tUSBDCompositeDevice g_sCompDevice =
{
    //
    // TI VID.
    //
    USB_VID_TI,

    //
    // Stellaris PID for composite HID/DFU device.
    //
    USB_PID_COMP_HID_DFU,

    //
    // This is in milliamps.
    //
    500,

    //
    // Bus powered device.
    //
    USB_CONF_ATTR_BUS_PWR,

    //
    // Device event handler function pointer (receives connect, disconnect
    // and other device-level notifications).
    //
    MouseHandler,

    //
    // The string table.
    //
    g_pStringDescriptors,
    NUM_STRING_DESCRIPTORS,

    //
    // The Composite device array.
    //
    NUM_DEVICES,
    g_psCompDevices,

    //
    // Additional workspace.
    //
    g_pulCompWorkspace,

    //
    // Composite device instance data.
    //
    &g_CompInstance
};

//****************************************************************************
//
// A buffer into which the composite device can write the combined config
// descriptor.
//
//****************************************************************************
unsigned char g_pcDescriptorBuffer[DESCRIPTOR_BUFFER_SIZE];

