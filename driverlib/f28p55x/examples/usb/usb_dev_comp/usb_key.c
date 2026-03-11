#include "usb_hal.h"
#include "usblib.h"
#include "usbhid.h"
#include "device/usbdevice.h"
#include "device/usbdhid.h"
#include "device/usbdhidkeyb.h"
#include "usb_key.h"


key_state_t g_eKeyboardState = STATE_UNCONFIGURED;

volatile bool g_bKeyConnected = false; // This global indicates whether or not we
                                    // are connected to a USB host.
volatile bool g_bSuspended = false; // This global indicates whether or not the
                                    //USB bus is currently in the suspend state
volatile bool g_bDisplayUpdateRequired; // This global is set to true if the
                                        // host sends a request to set or clear

uint32_t
KeyboardHandler(void *pvCBData, uint32_t ui32Event, uint32_t ui32MsgData,
                void *pvMsgData)
{
    switch (ui32Event)
    {
        //
        // The host has connected to us and configured the device.
        //
        case USB_EVENT_CONNECTED:
        {
            g_bKeyConnected = true;
            g_bSuspended = false;
            break;
        }

        //
        // The host has disconnected from us.
        //
        case USB_EVENT_DISCONNECTED:
        {
            g_bKeyConnected = false;
            break;
        }

        //
        // We receive this event every time the host acknowledges transmission
        // of a report. It is used here purely as a way of determining whether
        // the host is still talking to us or not.
        //
        case USB_EVENT_TX_COMPLETE:
        {
            //
            // Enter the idle state since we finished sending something.
            //
            g_eKeyboardState = STATE_IDLE;
            break;
        }

        //
        // This event indicates that the host has suspended the USB bus.
        //
        case USB_EVENT_SUSPEND:
        {
            g_bSuspended = true;
            break;
        }

        //
        // This event signals that the host has resumed signalling on the bus.
        //
        case USB_EVENT_RESUME:
        {
            g_bSuspended = false;
            break;
        }

        //
        // This event indicates that the host has sent us an Output or
        // Feature report and that the report is now in the buffer we provided
        // on the previous USBD_HID_EVENT_GET_REPORT_BUFFER callback.
        //
        case USBD_HID_KEYB_EVENT_SET_LEDS:
        {
            //
            // Set the LED to match the current state of the caps lock LED.
            //
            //GPIO_writePin(31,((ui32MsgData & HID_KEYB_CAPS_LOCK) ? 1 : 0));

            break;
        }

        //
        // We ignore all other events.
        //
        default:
        {
            break;
        }
    }

    return(0);
}
