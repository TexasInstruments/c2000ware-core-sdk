#include "usb_structs.h"

//******************************************************************************
//
// The HID mouse device initialization and customization structures.
//
//******************************************************************************
tHIDCustomInstance g_sCustomInstance;

tUSBDHIDCustomDevice g_sCustomDevice =
{
    USB_VID_TI_1CBE,
    USB_PID_MOUSE,
    500,
    USB_CONF_ATTR_SELF_PWR,
    CustomHandler,
    (void *)&g_sCustomDevice,
    g_pui8StringDescriptors,
    0,
};
