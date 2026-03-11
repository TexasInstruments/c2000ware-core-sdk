/*
 * usb_hid_touch.c
 *
 */
#include "usb_structs.h"

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
    g_pui8StringDescriptors,
    0,
};
