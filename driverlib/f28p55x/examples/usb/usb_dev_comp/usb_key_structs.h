#ifndef _USB_KEY_STRUCTS_H
#define _USB_KEY_STRUCTS_H

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_types.h"
#include "usb.h"
#include "usblib.h"
#include "usb_ids.h"

#include "device/usbdevice.h"

#include "usbhid.h"
#include "device/usbdhid.h"
#include "device/usbdhidkeyb.h"


extern tUSBDHIDKeyboardDevice g_sKeyboardDevice;


//
// Function Prototypes
//
extern uint32_t KeyboardHandler(void *pvCBData, uint32_t ui32Event,
                                uint32_t ui32MsgData, void *pvMsgData);

#endif
