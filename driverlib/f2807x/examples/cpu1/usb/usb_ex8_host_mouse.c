//##############################################################################
//
// FILE:   usb_ex8_host_mouse.c
//
// TITLE:  Main application code for the host mouse example.
//
//##############################################################################
//
//
// $Copyright:
// Copyright (C) 2014-2023 Texas Instruments Incorporated - http://www.ti.com/
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//##############################################################################

//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "usblib.h"
#include "usbhid.h"
#include "host/usbhost.h"
#include "host/usbhhid.h"
#include "host/usbhhidmouse.h"
#ifdef DEBUG
#include "scistdio.h"
#endif
#include "usb_ex8_dual_detect.h"

//******************************************************************************
//
// The size of the mouse device interface's memory pool in bytes.
//
//******************************************************************************
#define MOUSE_MEMORY_SIZE       128

//******************************************************************************
//
// The memory pool to provide to the mouse device.
//
//******************************************************************************
uint8_t g_pui8Buffer[MOUSE_MEMORY_SIZE];

//******************************************************************************
//
// Declare the USB Events driver interface.
//
//******************************************************************************
DECLARE_EVENT_DRIVER(g_sUSBEventDriver, 0, 0, USBHCDEvents);

//******************************************************************************
//
// The global that holds all of the host drivers in use in the application.
// In this case, only the Mouse class is loaded.
//
//******************************************************************************
static tUSBHostClassDriver const * const g_ppHostClassDrivers[] =
{
    &g_sUSBHIDClassDriver,
    &g_sUSBEventDriver
};

//******************************************************************************
//
// This global holds the number of class drivers in the g_ppHostClassDrivers
// list.
//
//******************************************************************************
static const uint32_t g_ui32NumHostClassDrivers =
                   sizeof(g_ppHostClassDrivers) / sizeof(tUSBHostClassDriver *);

//******************************************************************************
//
// The global value used to store the mouse instance value.
//
//******************************************************************************
static uint32_t g_ui32MouseInstance;

//******************************************************************************
//
// The global values used to store the mouse state.
//
//******************************************************************************
static uint32_t g_ui32Buttons;

//******************************************************************************
//
// This enumerated type is used to hold the states of the mouse.
//
//******************************************************************************
enum
{
    //
    // No device is present.
    //
    STATE_NO_DEVICE,

    //
    // Mouse has been detected and needs to be initialized in the main
    // loop.
    //
    STATE_MOUSE_INIT,

    //
    // Mouse is connected and waiting for events.
    //
    STATE_MOUSE_CONNECTED,

    //
    // An unsupported device has been attached.
    //
    STATE_UNKNOWN_DEVICE,

    //
    // A power fault has occurred.
    //
    STATE_POWER_FAULT
}
eUSBState;

//******************************************************************************
//
// This is the generic callback from host stack.
//
// \param pvData is actually a pointer to a tEventInfo structure.
//
// This function will be called to inform the application when a USB event has
// occurred that is outside those related to the mouse device.  At this
// point this is used to detect unsupported devices being inserted and removed.
// It is also used to inform the application when a power fault has occurred.
// This function is required when the g_USBGenericEventDriver is included in
// the host controller driver array that is passed in to the
// USBHCDRegisterDrivers() function.
//
// \return None.
//
//******************************************************************************
void
USBHCDEvents(void *pvData)
{
    tEventInfo *pEventInfo;

    //
    // Cast this pointer to its actual type.
    //
    pEventInfo = (tEventInfo *)pvData;

    switch(pEventInfo->ui32Event)
    {
        //
        // New mouse detected.
        //
        case USB_EVENT_CONNECTED:
        {
            //
            // See if this is a HID Mouse.
            //
            if((USBHCDDevClass(pEventInfo->ui32Instance, 0) == USB_CLASS_HID) &&
               (USBHCDDevProtocol(pEventInfo->ui32Instance, 0) ==
                USB_HID_PROTOCOL_MOUSE))
            {
                //
                // Indicate that the mouse has been detected.
                //
                DEBUG_PRINT("Mouse Connected\n");

                //
                // Proceed to the STATE_MOUSE_INIT state so that the main loop
                // can finish initialized the mouse since USBHMouseInit()
                // cannot be called from within a callback.
                //
                eUSBState = STATE_MOUSE_INIT;
            }

            break;
        }
        //
        // Unsupported detected.
        //
        case USB_EVENT_UNKNOWN_CONNECTED:
        {
            DEBUG_PRINT("Unsupported Device Connected\n");

            //
            // An unknown device was detected.
            //
            eUSBState = STATE_UNKNOWN_DEVICE;


            break;
        }
        //
        // Device has been unplugged.
        //
        case USB_EVENT_DISCONNECTED:
        {
            //
            // Indicate that the mouse has been disconnected.
            //
            DEBUG_PRINT("Device Disconnected\n");

            //
            // Change the state so that the main loop knows that the mouse is
            // no longer present.
            //
            eUSBState = STATE_NO_DEVICE;

            //
            // Reset the button state.
            //
            g_ui32Buttons = 0;


            break;
        }
        //
        // Power Fault occurred.
        //
        case USB_EVENT_POWER_FAULT:
        {
            DEBUG_PRINT("Power Fault\n");

            //
            // No power means no device is present.
            //
            eUSBState = STATE_POWER_FAULT;

            break;
        }
        default:
        {
            break;
        }
    }
}

//******************************************************************************
//
// This is the callback from the USB HID mouse handler.
//
// \param pvCBData is ignored by this function.
// \param ui32Event is one of the valid events for a mouse device.
// \param ui32MsgParam is defined by the event that occurs.
// \param pvMsgData is a pointer to data that is defined by the event that
// occurs.
//
// This function will be called to inform the application when a mouse has
// been plugged in or removed and any time mouse movement or button pressed
// is detected.
//
// \return This function will return 0.
//
//******************************************************************************
uint32_t
MouseCallback(void *pvCBData, uint32_t ui32Event, uint32_t ui32MsgParam,
              void *pvMsgData)
{
    switch(ui32Event)
    {
        //
        // Mouse button press detected.
        //
        case USBH_EVENT_HID_MS_PRESS:
        {
            DEBUG_PRINT("Button Pressed %02x\n", ui32MsgParam);

            //
            // Save the new button that was pressed.
            //
            g_ui32Buttons |= ui32MsgParam;

            break;
        }

        //
        // Mouse button release detected.
        //
        case USBH_EVENT_HID_MS_REL:
        {
            DEBUG_PRINT("Button Released %02x\n", ui32MsgParam);

            //
            // Remove the button from the pressed state.
            //
            g_ui32Buttons &= ~ui32MsgParam;

            break;
        }

        //
        // Mouse X movement detected.
        //
        case USBH_EVENT_HID_MS_X:
        {
            DEBUG_PRINT("X:%02d.\n", (uint8_t)ui32MsgParam);

            break;
        }

        //
        // Mouse Y movement detected.
        //
        case USBH_EVENT_HID_MS_Y:
        {
            DEBUG_PRINT("Y:%02d.\n", (uint8_t)ui32MsgParam);

            break;
        }
    }

    return(0);
}

//******************************************************************************
//
// Initialize the host mode stack.
//
//******************************************************************************
void
HostStackInit(void)
{
    //
    // Register the host class drivers.
    //
    USBHCDRegisterDrivers(0, g_ppHostClassDrivers, g_ui32NumHostClassDrivers);

    //
    // Initialize the button states.
    //
    g_ui32Buttons = 0;

    //
    // Open an instance of the mouse driver.  The mouse does not need
    // to be present at this time, this just saves a place for it and allows
    // the applications to be notified when a mouse is present.
    //
    g_ui32MouseInstance =
        (uint32_t)USBHMouseOpen((tUSBHIDMouseCallback)MouseCallback,
                                (uint8_t *)g_pui8Buffer,
                                MOUSE_MEMORY_SIZE);

    //
    // Initialize the power configuration. This sets the power enable signal
    // to be active high and does not enable the power fault.
    //
    USBHCDPowerConfigInit(0, USBHCD_VBUS_AUTO_HIGH | USBHCD_VBUS_FILTER);

    //
    // Call the main loop for the Host controller driver.
    //
    eUSBState = STATE_NO_DEVICE;
}

//******************************************************************************
//
// This is the main loop that runs the application.
//
//******************************************************************************
void
HostMain(void)
{
    switch(eUSBState)
    {
        //
        // This state is entered when the mouse is first detected.
        //
        case STATE_MOUSE_INIT:
        {
            //
            // Initialize the newly connected mouse.
            //
            USBHMouseInit((tUSBHMouse *)g_ui32MouseInstance);

            //
            // Proceed to the mouse connected state.
            //
            eUSBState = STATE_MOUSE_CONNECTED;

            break;
        }
        case STATE_MOUSE_CONNECTED:
        {
            //
            // Nothing is currently done in the main loop when the mouse
            // is connected.
            //
            break;
        }
        case STATE_NO_DEVICE:
        {
            //
            // The mouse is not connected so nothing needs to be done here.
            //
            break;
        }
        default:
        {
            break;
        }
    }

    //
    // Periodically call the main loop for the Host controller driver.
    //
    USBHCDMain();
}

//
// End of file
//
