#include "usb_structs.h"

//******************************************************************************
//
// The HID keyboard device initialization and customization structures.
//
//******************************************************************************
tUSBDHIDKeyboardDevice g_sKeyboardDevice =
{
    USB_VID_TI_1CBE,
    USB_PID_KEYBOARD,
    500,
    USB_CONF_ATTR_SELF_PWR | USB_CONF_ATTR_RWAKE,
    KeyboardHandler,
    (void *)&g_sKeyboardDevice,
    g_pui8StringDescriptors,
    0,
    0//&g_KeyboardInstance
};
