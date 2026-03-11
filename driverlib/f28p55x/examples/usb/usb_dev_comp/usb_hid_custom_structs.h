#ifndef _USB_HID_CUSTOM_H
#define _USB_HID_CUSTOM_H

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_types.h"
#include "usb.h"
#include "usblib.h"
#include "usb_ids.h"

#include "device/usbdevice.h"

#include "usbhid.h"
#include "device/usbdhid.h"
#include "device/usbdhidcustom.h"


extern uint32_t CustomHandler(void *pvCBData, uint32_t ui32Event,
                             uint32_t ui32MsgData, void *pvMsgData);

extern tUSBDHIDCustomDevice g_sCustomDevice;


#endif
