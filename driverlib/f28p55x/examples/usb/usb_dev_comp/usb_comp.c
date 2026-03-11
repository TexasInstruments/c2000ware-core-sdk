#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_ints.h"
#include "inc/hw_types.h"
#include "usb.h"
#include "usblib.h"
#include "usb_ids.h"

#include "device/usbdevice.h"

uint32_t
USBEventHandler(void *pvCBData, uint32_t ui32Event, uint32_t ui32MsgParam,
                void *pvMsgData)
{
    //
    // Infor the UI code of the state change.
    //
    if(ui32Event == USB_EVENT_CONNECTED)
    {

    }
    else if(ui32Event == USB_EVENT_DISCONNECTED)
    {

    }
    else if(ui32Event == USB_EVENT_SUSPEND)
    {

    }
    else if(ui32Event == USB_EVENT_RESUME)
    {

    }

    return(0);
}
