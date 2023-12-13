//##############################################################################
//
// FILE:   usb_ex2_device_mouse_structs.c
//
// TITLE:   Data structures defining the USB mouse device.
//! <h1> Data structures defining the USB mouse device. </h1>
//
//##############################################################################

#include "usb_ex2_device_mouse_structs.h"

//******************************************************************************
//
// The languages supported by this device.
//
//******************************************************************************
const uint8_t g_pLangDescriptor[] =
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
const uint8_t g_pManufacturerString[] =
{
    (17 + 1) * 2,
    USB_DTYPE_STRING,
    'T', 0, 'e', 0, 'x', 0, 'a', 0, 's', 0, ' ', 0, 'I', 0, 'n', 0, 's', 0,
    't', 0, 'r', 0, 'u', 0, 'm', 0, 'e', 0, 'n', 0, 't', 0, 's', 0,
};

//******************************************************************************
//
// The product string.
//
//******************************************************************************
const uint8_t g_pProductString[] =
{
    (13 + 1) * 2,
    USB_DTYPE_STRING,
    'M', 0, 'o', 0, 'u', 0, 's', 0, 'e', 0, ' ', 0, 'E', 0, 'x', 0, 'a', 0,
    'm', 0, 'p', 0, 'l', 0, 'e', 0
};

//******************************************************************************
//
// The serial number string.
//
//******************************************************************************
const uint8_t g_pSerialNumberString[] =
{
    (8 + 1) * 2,
    USB_DTYPE_STRING,
    '1', 0, '2', 0, '3', 0, '4', 0, '5', 0, '6', 0, '7', 0, '8', 0
};

//******************************************************************************
//
// The interface description string.
//
//******************************************************************************
const uint8_t g_pHIDInterfaceString[] =
{
    (19 + 1) * 2,
    USB_DTYPE_STRING,
    'H', 0, 'I', 0, 'D', 0, ' ', 0, 'M', 0, 'o', 0, 'u', 0, 's', 0,
    'e', 0, ' ', 0, 'I', 0, 'n', 0, 't', 0, 'e', 0, 'r', 0, 'f', 0,
    'a', 0, 'c', 0, 'e', 0
};

//******************************************************************************
//
// The configuration description string.
//
//******************************************************************************
const uint8_t g_pConfigString[] =
{
    (23 + 1) * 2,
    USB_DTYPE_STRING,
    'H', 0, 'I', 0, 'D', 0, ' ', 0, 'M', 0, 'o', 0, 'u', 0, 's', 0,
    'e', 0, ' ', 0, 'C', 0, 'o', 0, 'n', 0, 'f', 0, 'i', 0, 'g', 0,
    'u', 0, 'r', 0, 'a', 0, 't', 0, 'i', 0, 'o', 0, 'n', 0
};

//******************************************************************************
//
// The descriptor string table.
//
//******************************************************************************
const uint8_t * const g_pStringDescriptors[] =
{
    g_pLangDescriptor,
    g_pManufacturerString,
    g_pProductString,
    g_pSerialNumberString,
    g_pHIDInterfaceString,
    g_pConfigString
};

#define NUM_STRING_DESCRIPTORS (sizeof(g_pStringDescriptors)                  /\
                                sizeof(uint8_t *))

//******************************************************************************
//
// The HID mouse device initialization and customization structures.
//
//******************************************************************************
tHIDMouseInstance g_sMouseInstance;

tUSBDHIDMouseDevice g_sMouseDevice =
{
    USB_VID_TI_1CBE,
    USB_PID_MOUSE,
    500,
    USB_CONF_ATTR_SELF_PWR,
    MouseHandler,
    (void *)&g_sMouseDevice,
    g_pStringDescriptors,
    NUM_STRING_DESCRIPTORS,
};

//
// End of file
//
