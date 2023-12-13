//##############################################################################
//
// usb_ex10_host_keyboard.c - The USB keyboard handling routines.
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
#include "host/usbhhidkeyboard.h"
#include "usb_ex10_host_hub.h"

//*****************************************************************************
//
// The size of the keyboard device interface's memory pool in bytes.
//
//*****************************************************************************
#define KEYBOARD_MEMORY_SIZE    128

//*****************************************************************************
//
// The memory pool to provide to the keyboard device.
//
//*****************************************************************************
uint8_t g_pui8Buffer[KEYBOARD_MEMORY_SIZE];

//*****************************************************************************
//
// The global value used to store the keyboard instance value.
//
//*****************************************************************************
static tUSBHKeyboard * g_psKeyboardInstance;

extern const tHIDKeyboardUsageTable g_sUSKeyboardMap;

//*****************************************************************************
//
// This enumerated type is used to hold the states of the keyboard.
//
//*****************************************************************************
enum
{
    //
    // No device is present.
    //
    eStateNoDevice,

    //
    // Keyboard has been detected and needs to be initialized in the main
    // loop.
    //
    eStateKeyboardInit,

    //
    // Keyboard is connected and waiting for events.
    //
    eStateKeyboardConnected,

    //
    // Keyboard has received a key press that requires updating the keyboard
    // in the main loop.
    //
    eStateKeyboardUpdate,
}
g_iKeyboardState;

//*****************************************************************************
//
// This variable holds the current status of the modifiers keys.
//
//*****************************************************************************
uint32_t g_ui32Modifiers;

//*****************************************************************************
//
// This function prints the character out the SCI and into the text area of
// the screen.
//
// \param cChar is the character to print out.
//
// This function handles all of the detail of printing a character to both the
// SCI and to the text area of the screen on the evaluation board.  The text
// area of the screen will be cleared any time the text goes beyond the end
// of the text area.
//
// \return None.
//
//*****************************************************************************
void
PrintChar(const char cChar)
{

    //
    // Send the character to the SCI.
    //
    SCIprintf("%c", cChar);

}

//*****************************************************************************
//
// This is the callback from the USB HID keyboard handler.
//
// pvCBData is ignored by this function.
// ui32Event is one of the valid events for a keyboard device.
// ui32MsgParam is defined by the event that occurs.
// pvMsgData is a pointer to data that is defined by the event that
// occurs.
//
// This function will be called to inform the application when a keyboard has
// been plugged in or removed and any time a key is pressed or released.
//
// This function will return 0.
//
//*****************************************************************************
void
KeyboardCallback(tUSBHKeyboard *psKbInstance, uint32_t ui32Event,
                 uint32_t ui32MsgParam, void *pvMsgData)
{
    char cChar;

    switch(ui32Event)
    {
        //
        // New keyboard detected.
        //
        case USB_EVENT_CONNECTED:
        {
            //
            // Proceed to the STATE_KEYBOARD_INIT state so that the main loop
            // can finish initialized the mouse since USBHKeyboardInit() cannot
            // be called from within a callback.
            //
            g_iKeyboardState = eStateKeyboardInit;
            break;
        }

        //
        // Keyboard has been unplugged.
        //
        case USB_EVENT_DISCONNECTED:
        {
            //
            // Change the state so that the main loop knows that the keyboard
            // is no longer present.
            //
            g_iKeyboardState = eStateNoDevice;
            break;
        }

        //
        // New Key press detected.
        //
        case USBH_EVENT_HID_KB_PRESS:
        {
            //
            // If this was a Caps Lock key then update the Caps Lock state.
            //
            if(ui32MsgParam == HID_KEYB_USAGE_CAPSLOCK)
            {
                //
                // The main loop needs to update the keyboard's Caps Lock
                // state.
                //
                g_iKeyboardState = eStateKeyboardUpdate;

                //
                // Toggle the current Caps Lock state.
                //
                g_ui32Modifiers ^= HID_KEYB_CAPS_LOCK;
            }
            else if(ui32MsgParam == HID_KEYB_USAGE_SCROLLOCK)
            {
                //
                // The main loop needs to update the keyboard's Scroll Lock
                // state.
                //
                g_iKeyboardState = eStateKeyboardUpdate;

                //
                // Toggle the current Scroll Lock state.
                //
                g_ui32Modifiers ^= HID_KEYB_SCROLL_LOCK;
            }
            else if(ui32MsgParam == HID_KEYB_USAGE_NUMLOCK)
            {
                //
                // The main loop needs to update the keyboard's Scroll Lock
                // state.
                //
                g_iKeyboardState = eStateKeyboardUpdate;

                //
                // Toggle the current Num Lock state.
                //
                g_ui32Modifiers ^= HID_KEYB_NUM_LOCK;
            }
            else
            {
                //
                // Was this the backspace key?
                //
                if((uint8_t)ui32MsgParam == HID_KEYB_USAGE_BACKSPACE)
                {
                    //
                    // Yes - set the ASCII code for a backspace key.  This is
                    // not returned by USBHKeyboardUsageToChar since this only
                    // returns printable characters.
                    //
                    cChar = ASCII_BACKSPACE;
                }
                else
                {
                    //
                    // This is not backspace so try to map the usage code to a
                    // printable ASCII character.
                    //
                    cChar = (char)
                        USBHKeyboardUsageToChar(g_psKeyboardInstance,
                                                &g_sUSKeyboardMap,
                                                (uint8_t)ui32MsgParam);
                }

                //
                // A zero value indicates there was no textual mapping of this
                // usage code.
                //
                if(cChar != 0)
                {
                    PrintChar(cChar);
                }
            }
            break;
        }
        case USBH_EVENT_HID_KB_MOD:
        {
            //
            // This application ignores the state of the shift or control
            // and other special keys.
            //
            break;
        }
        case USBH_EVENT_HID_KB_REL:
        {
            //
            // This applications ignores the release of keys as well.
            //
            break;
        }
    }
}

//*****************************************************************************
//
// The main routine for handling the USB keyboard.
//
//*****************************************************************************
void
KeyboardMain(void)
{
    switch(g_iKeyboardState)
    {
        //
        // This state is entered when they keyboard is first detected.
        //
        case eStateKeyboardInit:
        {
            //
            // Initialized the newly connected keyboard.
            //
            USBHKeyboardInit(g_psKeyboardInstance);

            //
            // Proceed to the keyboard connected state.
            //
            g_iKeyboardState = eStateKeyboardConnected;

            //
            // Set the current state of the modifiers.
            //
            USBHKeyboardModifierSet(g_psKeyboardInstance, g_ui32Modifiers);

            break;
        }
        case eStateKeyboardUpdate:
        {
            //
            // If the application detected a change that required an
            // update to be sent to the keyboard to change the modifier
            // state then call it and return to the connected state.
            //
            g_iKeyboardState = eStateKeyboardConnected;

            USBHKeyboardModifierSet(g_psKeyboardInstance, g_ui32Modifiers);

            break;
        }
        case eStateKeyboardConnected:
        default:
        {
            break;
        }
    }
}

//*****************************************************************************
//
// Open the Keyboard Interface.
//
//*****************************************************************************
void
KeyboardOpen(void)
{
    //
    // Open an instance of the keyboard driver.
    //
    g_psKeyboardInstance = USBHKeyboardOpen(KeyboardCallback, g_pui8Buffer,
                                            KEYBOARD_MEMORY_SIZE);
    g_iKeyboardState = eStateNoDevice;
}
