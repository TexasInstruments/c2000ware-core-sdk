/*
 * Copyright (c) 2021 Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */




//
// Included Files
//
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "usblib.h"
#include "usbhid.h"
#include "usb_ids.h"
#include "device/usbdevice.h"
#include "usb_structs.h"


// Data structures defining this CDC USB device.

//******************************************************************************
//
// The languages supported by this device.
//
//******************************************************************************
const uint8_t g_pui8LangDescriptor[] =
{
    4,
    USB_DTYPE_STRING,
    USBShort(USB_LANG_EN_US)
};

//******************************************************************************
//
// The manufacturer string.
//
//******************************************************************************
const uint8_t g_pui8ManufacturerString[] =
{
    (17 + 1) * 2,
    USB_DTYPE_STRING,
    'T',0,'e',0,'x',0,'a',0,'s',0,' ',0,'I',0,'n',0,'s',0,'t',0,'r',0,'u',0,'m',0,'e',0,'n',0,'t',0,'s',0,
};

//******************************************************************************
//
// The product string.
//
//******************************************************************************
const uint8_t g_pui8ProdectString[] =
{
    2 + (24 * 2),
    USB_DTYPE_STRING,
    'C',0,'o',0,'m',0,'p',0,'o',0,'s',0,'i',0,'t',0,'e',0,' ',0,'v',0,'i',0,'r',0,'t',0,'u',0,'a',0,'l',0,' ',0,'D',0,'e',0,'v',0,'i',0,'c',0,'e',0
};

//******************************************************************************
//
// The serial number string.
//
//******************************************************************************
const uint8_t g_pui8SerialNumberString[] =
{
    2 + (8 * 2),
    USB_DTYPE_STRING,
    '1',0,'2',0,'3',0,'4',0,'5',0,'6',0,'7',0,'8',0,
};

//******************************************************************************
//
// The control interface description string.
//
//******************************************************************************
const uint8_t g_pui8ControlInterfaceString[] =
{
    2 + (21 * 2),
    USB_DTYPE_STRING,
	'A',0,'C',0,'M',0,' ',0,'C',0,'o',0,'n',0,'t',0,'r',0,'o',0,'l',0,' ',0,'I',0,'n',0,'t',0,'e',0,'r',0,'f',0,'a',0,'c',0,'e',0,
};

//******************************************************************************
//
// The configuration description string.
//
//******************************************************************************
const uint8_t g_pui8ConfigString[] =
{
    2 + (26 * 2),
    USB_DTYPE_STRING,
	'S',0,'e',0,'l',0,'f',0,' ',0,'P',0,'o',0,'w',0,'e',0,'r',0,'e',0,'d',0,' ',0,'C',0,'o',0,'n',0,'f',0,'i',0,'g',0,'u',0,'r',0,'a',0,'t',0,'i',0,'o',0,'n',0,
};

//******************************************************************************
//
// The descriptor string table.
//
//******************************************************************************
const uint8_t * const g_pui8StringDescriptors[] =
{
    g_pui8LangDescriptor,
    g_pui8ManufacturerString,
    g_pui8ProdectString,
    g_pui8SerialNumberString,
    g_pui8ControlInterfaceString,
    g_pui8ConfigString
};

#define NUM_STRING_DESCRIPTORS (sizeof(g_pui8StringDescriptors)              /\
                                sizeof(uint8_t *))

uint8_t g_pui8DescriptorData[DESCRIPTOR_DATA_SIZE];

tCompositeEntry g_psCompDevices[NUM_DEVICES];

tUSBDCompositeDevice g_sCompDevice =
{
    //
    // Tiva VID.
    //
    USB_VID_TI_1CBE,

    //
    // Tiva PID for composite HID and HID.
    //
    USB_PID_COMP_HID_HID,

    //
    // This is in 2mA increments so 500mA.
    //
    250,

    //
    // Bus powered device.
    //
    USB_CONF_ATTR_BUS_PWR,

    //
    // There is no need for a default composite event handler.
    //
    USBEventHandler,

    //
    // The string table.
    //
    g_pui8StringDescriptors,
    NUM_STRING_DESCRIPTORS,

    //
    // The Composite device array.
    //
    NUM_DEVICES,
    g_psCompDevices,
};


