/*
 * usb_hid_touch_structs.h
 *
 */


#ifndef USB_HID_TOUCH_STRUCTS_H
#define USB_HID_TOUCH_STRUCTS_H
//
// Included Files
//
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_types.h"
#include "usb.h"
#include "usblib.h"
#include "usb_ids.h"

#include "device/usbdevice.h"

#include "usbhid.h"
#include "device/usbdhid.h"
#include "device/usbdhidmouse.h"
extern uint32_t MouseHandler(void *pvCBData, uint32_t ui32Event,
                             uint32_t ui32MsgData, void *pvMsgData);

extern tUSBDHIDMouseDevice g_sMouseDevice;


#endif // USB_HID_TOUCH_STRUCTS_H
