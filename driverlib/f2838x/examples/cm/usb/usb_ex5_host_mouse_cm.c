//##############################################################################
//
// FILE:   usb_ex5_host_mouse_cm.c
//
// TITLE:  Main application code for the host mouse example.
//
//! \addtogroup driver_example_cm_list
//! <h1>USB HID Mouse Host (usb_host_mouse)</h1>
//!
//! This application demonstrates the handling of a USB mouse attached to the
//! evaluation kit.  Once attached, the position of the mouse pointer and the
//! state of the mouse buttons are output to the display.
//!
//! UART0, which is connected to the FTDI virtual serial port on the
//! controlCARD board, is configured for 115200 bits per second, and 8-N-1
//! mode.  When a HID compliant mouse is connected to the microUSB port on the
//! top of the controlCARD, position and button information will be displayed
//! to the console.
//!
//
//##############################################################################
//
//
// 
// C2000Ware v6.00.00.00
//
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
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

#include <string.h>
#include "cm.h"
#include "usblib.h"
#include "usbhid.h"
#include "host/usbhost.h"
#include "host/usbhhid.h"
#include "host/usbhhub.h"
#include "host/usbhhidmouse.h"
#include "uartstdio.h"
#include "usb_hal.h"

//*****************************************************************************
//
// The size of the host controller's memory pool in bytes.
//
//*****************************************************************************
#define HCD_MEMORY_SIZE         128

//*****************************************************************************
//
// The memory pool to provide to the Host controller driver.
//
//*****************************************************************************
uint8_t g_pui8HCDPool[HCD_MEMORY_SIZE];

//*****************************************************************************
//
// The size of the mouse device interface's memory pool in bytes.
//
//*****************************************************************************
#define MOUSE_MEMORY_SIZE       128

//*****************************************************************************
//
// The memory pool to provide to the mouse device.
//
//*****************************************************************************
uint8_t g_pui8Buffer[MOUSE_MEMORY_SIZE];

//*****************************************************************************
//
// Declare the USB Events driver interface.
//
//*****************************************************************************
DECLARE_EVENT_DRIVER(g_sUSBEventDriver, 0, 0, USBHCDEvents);

//*****************************************************************************
//
// The global that holds all of the host drivers in use in the application.
// In this case, only the Mouse class is loaded.
//
//*****************************************************************************
static tUSBHostClassDriver const * const g_ppHostClassDrivers[] =
{
    &g_sUSBHIDClassDriver,
    &g_sUSBEventDriver
};

//*****************************************************************************
//
// This global holds the number of class drivers in the g_ppHostClassDrivers
// list.
//
//*****************************************************************************
static const uint32_t g_ui32NumHostClassDrivers =
    sizeof(g_ppHostClassDrivers) / sizeof(tUSBHostClassDriver *);

//*****************************************************************************
//
// The global value used to store the mouse instance value.
//
//*****************************************************************************
static tUSBHMouse *g_psMouseInstance;

//*****************************************************************************
//
// The global values used to store the mouse state.
//
//*****************************************************************************
static uint32_t g_ui32Buttons;
static int32_t g_i32CursorX;
static int32_t g_i32CursorY;

//*****************************************************************************
//
// The current USB operating mode - Host, Device or unknown.
//
//*****************************************************************************
tUSBMode g_eCurrentUSBMode;

//*****************************************************************************
//
// This enumerated type is used to hold the states of the mouse.
//
//*****************************************************************************
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
g_eUSBState;

//*****************************************************************************
//
// This is the generic callback from host stack.
//
// pvData is actually a pointer to a tEventInfo structure.
//
// This function will be called to inform the application when a USB event has
// occurred that is outside those related to the mouse device.  At this
// point this is used to detect unsupported devices being inserted and removed.
// It is also used to inform the application when a power fault has occurred.
// This function is required when the g_USBGenericEventDriver is included in
// the host controller driver array that is passed in to the
// USBHCDRegisterDrivers() function.
//
//*****************************************************************************
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
                UARTprintf("\nMouse Connected\n");

                //
                // Proceed to the STATE_MOUSE_INIT state so that the main loop
                // can finish initialized the mouse since USBHMouseInit()
                // cannot be called from within a callback.
                //
                g_eUSBState = STATE_MOUSE_INIT;
            }

            break;
        }

        //
        // Unsupported device detected.
        //
        case USB_EVENT_UNKNOWN_CONNECTED:
        {
            UARTprintf("Unsupported Device Class (0x%02x) Connected.\n",
                       pEventInfo->ui32Instance);
            //
            // An unknown device was detected.
            //
            g_eUSBState = STATE_UNKNOWN_DEVICE;

            break;
        }

        //
        // Device has been unplugged.
        //
        case USB_EVENT_DISCONNECTED:
        {
            //
            // Indicate that the device has been disconnected.
            //
            UARTprintf("Device Disconnected\n");

            //
            // Change the state so that the main loop knows that the device is
            // no longer present.
            //
            g_eUSBState = STATE_NO_DEVICE;

            //
            // Reset the button state.
            //
            g_ui32Buttons = 0;

            break;
        }
        //
        // Power Fault has occurred.
        //
        case USB_EVENT_POWER_FAULT:
        {
            UARTprintf("Power Fault\n");

            //
            // No power means no device is present.
            //
            g_eUSBState = STATE_POWER_FAULT;

            break;
        }

        default:
        {
            break;
        }
    }
}

//*****************************************************************************
//
// USB Mode callback
//
// \param ui32Index is the zero-based index of the USB controller making the
//        callback.
// \param eMode indicates the new operating mode.
//
// This function is called by the USB library whenever an OTG mode change
// occurs and, if a connection has been made, informs us of whether we are to
// operate as a host or device.
//
// \return None.
//
//*****************************************************************************
void
ModeCallback(uint32_t ui32Index, tUSBMode eMode)
{
    //
    // Save the new mode.
    //
    g_eCurrentUSBMode = eMode;
}

//*****************************************************************************
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
//*****************************************************************************
void
MouseCallback(tUSBHMouse *pvCBData, uint32_t ui32Event, uint32_t ui32MsgParam,
              void *pvMsgData)
{
    int32_t i32DoUpdate;

    //
    // Do an update unless there is no reason to.
    //
    i32DoUpdate = 1;

    switch(ui32Event)
    {
        //
        // Mouse button press detected.
        //
        case USBH_EVENT_HID_MS_PRESS:
        {
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
            //
            // The mouse returns a 8 bit signed value...check to see if we
            // need to sign extend
            //
            if(ui32MsgParam & 0x80)
            {
                ui32MsgParam |= 0xFF00;
            }

            //
            // Update the cursor X position.
            //
            g_i32CursorX += (int16_t)ui32MsgParam ;

            //
            // Cap the value to not cause an overflow.
            //
            if(g_i32CursorX > 9999)
            {
                g_i32CursorX = 9999;
            }

            if(g_i32CursorX < -9999)
            {
                g_i32CursorX = -9999;
            }

            break;
        }

        //
        // Mouse Y movement detected.
        //
        case USBH_EVENT_HID_MS_Y:
        {
            //
            // The mouse returns a 8 bit signed value...check to see if we
            // need to sign extend
            //
            if(ui32MsgParam & 0x80)
                ui32MsgParam |= 0xFF00;

            //
            // Update the cursor Y position.
            //
            g_i32CursorY += (int16_t)ui32MsgParam;

            //
            // Cap the value to not cause an overflow.
            //
            if(g_i32CursorY > 9999)
            {
                g_i32CursorY = 9999;
            }

            if(g_i32CursorY < -9999)
            {
                g_i32CursorY = -9999;
            }

            break;
        }
        default:
        {
            //
            // No reason to update.
            //
            i32DoUpdate = 0;

            break;
        }
    }

    //
    // Display the current mouse position and button state if there was an
    // update.
    //
    if(i32DoUpdate)
    {
    UARTprintf("\rPos: %d, %d  Buttons: %d%d%d    ", g_i32CursorX, g_i32CursorY,
               g_ui32Buttons & 1, (g_ui32Buttons & 2) >> 1,
               (g_ui32Buttons & 4) >> 2);
    }
}

//*****************************************************************************
//
// This is the main loop that runs the application.
//
//*****************************************************************************
int
main(void)
{

    //
    // Initialize device clock and peripherals
    //
    CM_init();

    //
    // Initialize the UART for console I/O.
    //
    UARTStdioConfig(UART0_BASE, 115200, UART_CLK_FREQ_USB);

    //
    // Register the interrupt handler, for USB.
    //
    Interrupt_registerHandler(INT_USB0, &CM_USB0HostIntHandler);

    //
    // Enable interrupts now that the application is ready to start.
    //
    Interrupt_enableInProcessor();

    //
    // Initially wait for device connection.
    //
    g_eUSBState = STATE_NO_DEVICE;

    //
    // Initialize the USB stack mode and pass in a mode callback.
    //
    USBStackModeSet(0, eUSBModeForceHost, ModeCallback);

    //
    // Register the host class drivers.
    //
    USBHCDRegisterDrivers(0, g_ppHostClassDrivers, g_ui32NumHostClassDrivers);

    //
    // Initialized the cursor.
    //
    g_ui32Buttons = 0;
    g_i32CursorX = 0;
    g_i32CursorY = 0;

    //
    // Open an instance of the mouse driver.  The mouse does not need
    // to be present at this time, this just saves a place for it and allows
    // the applications to be notified when a mouse is present.
    //
    g_psMouseInstance =
        USBHMouseOpen(MouseCallback, g_pui8Buffer, MOUSE_MEMORY_SIZE);

    //
    // Initialize the power configuration. This sets the power enable signal
    // to be active high and does not enable the power fault.
    //
    USBHCDPowerConfigInit(0, USBHCD_VBUS_AUTO_HIGH | USBHCD_VBUS_FILTER);

    //
    // Initialize the USB controller for Host operation.
    //
    USBHCDInit(0, g_pui8HCDPool, HCD_MEMORY_SIZE);

    //
    // The main loop for the application.
    //
    while(1)
    {
        //
        // Run the host state machine.
        //
        USBHCDMain();

        switch(g_eUSBState)
        {
            //
            // This state is entered when the mouse is first detected.
            //
            case STATE_MOUSE_INIT:
            {
                //
                // Initialize the newly connected mouse.
                //
                USBHMouseInit(g_psMouseInstance);

                //
                // Proceed to the mouse connected state.
                //
                g_eUSBState = STATE_MOUSE_CONNECTED;

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
    }
}

//
// End of file
//
