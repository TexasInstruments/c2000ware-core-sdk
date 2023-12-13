//##############################################################################
//
// usb_ex10_host_mouse.c - The USB Mouse handling routines.
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
#include "usb_hal.h"
#include "usblib.h"
#include "usbhid.h"
#include "scistdio.h"
#include "host/usbhost.h"
#include "host/usbhhid.h"
#include "host/usbhhub.h"
#include "host/usbhhidmouse.h"
#include "scistdio.h"
#include "usb_ex10_host_hub.h"

//******************************************************************************
//
// The global values used to store the mouse state.
//
//******************************************************************************
static uint32_t g_ui32Buttons;
static int32_t g_i32CursorX;
static int32_t g_i32CursorY;

//******************************************************************************
//
// The global value used to store the mouse instance value.
//
//******************************************************************************
static tUSBHMouse *g_psMouseInstance;

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
uint8_t g_pui8BufferMouse[MOUSE_MEMORY_SIZE];

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
g_eUSBState;

//******************************************************************************
//
// This is the callback from the USB HID mouse handler.
//
// \param psMsInstance is ignored by this function.
// \param ui32Event is one of the valid events for a mouse device.
// \param ui32MsgParam is defined by the event that occurs.
// \param pvMsgData is a pointer to data that is defined by the event that
// occurs.
//
// This function will be called to inform the application when a mouse has
// been plugged in or removed and any time mouse movement or button pressed
// is detected.
//
// \return None.
//
//******************************************************************************
void
MouseCallback(tUSBHMouse *psMsInstance, uint32_t ui32Event,
              uint32_t ui32MsgParam, void *pvMsgData)
{
    int32_t i32DoUpdate;
    volatile char pcBuffer[20];

    //
    // Do an update unless there is no reason to.
    //
    i32DoUpdate = 0;

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
            i32DoUpdate = 1;

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
            i32DoUpdate = 1;

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
                ui32MsgParam |= 0xFF00;
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
            i32DoUpdate = 1;

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
            i32DoUpdate = 1;

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
        //
        // Display the current mouse position and button state.
        //
        SCIprintf("\rPos: %l, %l  Buttons: %l%l%l    ", g_i32CursorX,
                  g_i32CursorY, g_ui32Buttons & 1, (g_ui32Buttons & 2) >> 1,
                  (g_ui32Buttons & 4) >> 2);


    }
}

//*****************************************************************************
//
// The main routine for handling the USB Mouse.
//
//*****************************************************************************
void
MouseMain(void)
{
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
            g_eUSBState = STATE_MOUSE_INIT;
            MouseOpen();
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

//*****************************************************************************
//
// Open the instance of the mouse driver.
//
//*****************************************************************************
void
MouseOpen(void)
{
    //
    // Open an instance of the mouse driver. The mouse does not need
    // to be present at this time, this just saves a place for it and allows
    // the applications to be notified when a mouse is present.
    //
    g_psMouseInstance = USBHMouseOpen(MouseCallback, g_pui8BufferMouse,
                                      MOUSE_MEMORY_SIZE);

    //
    // Initialized the cursor.
    //
    g_ui32Buttons = 0;
    g_i32CursorX = 0;
    g_i32CursorY = 0;
}
