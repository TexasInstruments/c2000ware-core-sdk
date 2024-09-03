//##############################################################################
//
// FILE:   usb_ex6_host_keyboard_cm.c
//
// TITLE:  Main application code for the host keyboard example.
//
//! \addtogroup driver_example_cm_list
//! <h1>USB HID Keyboard Host (usb_host_keyboard)</h1>
//!
//! This example application demonstrates how to support a USB keyboard
//! attached to the evaluation kit board.  The display will show if a keyboard
//! is currently connected and the current state of the Caps Lock key on the
//! keyboard that is connected on the bottom status area of the screen.
//! Pressing any keys on the keyboard will cause them to be  sent out the UART0
//! at 115200 baud with no parity, 8 bits and 1 stop bit.  Any keyboard that
//! supports the USB HID BIOS protocol should work with this demo application.
//!
//! To run the example you should connect a HID compliant keyboard to the
//! microUSB port on the top of the controlCARD and open up a serial terminal
//! with the above settings to view the characters typed on the keyboard.
//!
//
//##############################################################################
//
//
// 
// C2000Ware v5.03.00.00
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
#include "host/usbhhidkeyboard.h"
#include "uartstdio.h"
#include "usb_hal.h"

//******************************************************************************
//
// The ASCII code for a backspace character.
//
//******************************************************************************
#define ASCII_BACKSPACE 0x08

//******************************************************************************
//
// The size of the host controller's memory pool in bytes.
//
//******************************************************************************
#define HCD_MEMORY_SIZE         128

//******************************************************************************
//
// The memory pool to provide to the Host controller driver.
//
//******************************************************************************
uint8_t g_pui8HCDPool[HCD_MEMORY_SIZE];

//******************************************************************************
//
// The size of the keyboard device interface's memory pool in bytes.
//
//******************************************************************************
#define KEYBOARD_MEMORY_SIZE    128

//******************************************************************************
//
// The memory pool to provide to the keyboard device.
//
//******************************************************************************
uint8_t g_pui8Buffer[KEYBOARD_MEMORY_SIZE];

//******************************************************************************
//
// Declare the USB Events driver interface.
//
//******************************************************************************
DECLARE_EVENT_DRIVER(g_sUSBEventDriver, 0, 0, USBHCDEvents);

//******************************************************************************
//
// The global that holds all of the host drivers in use in the application.
// In this case, only the Keyboard class is loaded.
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
// The global value used to store the keyboard instance value.
//
//******************************************************************************
static tUSBHKeyboard *g_psKeyboardInstance;

//******************************************************************************
//
// This enumerated type is used to hold the states of the keyboard.
//
//******************************************************************************
enum
{
    //
    // No device is present.
    //
    STATE_NO_DEVICE,

    //
    // Keyboard has been detected and needs to be initialized in the main
    // loop.
    //
    STATE_KEYBOARD_INIT,

    //
    // Keyboard is connected and waiting for events.
    //
    STATE_KEYBOARD_CONNECTED,

    //
    // Keyboard has received a key press that requires updating the keyboard
    // in the main loop.
    //
    STATE_KEYBOARD_UPDATE,

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

extern const tHIDKeyboardUsageTable g_sUSKeyboardMap;

//*****************************************************************************
//
// These defines are used to define the screen constraints to the application.
//
//*****************************************************************************
#define DISPLAY_BANNER_HEIGHT   10
#define DISPLAY_BANNER_BG       ClrDarkBlue
#define DISPLAY_TEXT_BORDER     2
#define DISPLAY_TEXT_FG         ClrWhite
#define DISPLAY_TEXT_BG         ClrBlack

//*****************************************************************************
//
// The current USB operating mode - Host, Device or unknown.
//
//*****************************************************************************
tUSBMode g_eCurrentUSBMode;

//*****************************************************************************
//
// This variable holds the current status of the modifiers keys.
//
//*****************************************************************************
uint32_t g_ui32Modifiers = 0;

//*****************************************************************************
//
// This is the number of characters that will fit on a line in the text area.
//
//*****************************************************************************
uint32_t g_ui32CharsPerLine;

//*****************************************************************************
//
// This is the number of lines that will fit in the text area.
//
//*****************************************************************************
uint32_t g_ui32LinesPerScreen;

//*****************************************************************************
//
// This is the current line for printing in the text area.
//
//*****************************************************************************
uint32_t g_ui32Line = 0;

//*****************************************************************************
//
// This is the current column for printing in the text area.
//
//*****************************************************************************
uint32_t g_ui32Column = 0;

//*****************************************************************************
//
// This function prints the character out the UART and into the text area of
// the screen.
//
// \param ui8Char is the character to print out.
//
// This function handles all of the detail of printing a character to both the
// UART and to the text area of the screen on the evaluation board.  The text
// area of the screen will be cleared any time the text goes beyond the end
// of the text area.
//
// \return None.
//
//*****************************************************************************
void
PrintChar(const char ui8Char)
{
    //
    // Send the character to the UART.
    //
    UARTprintf("%c", ui8Char);
}

//*****************************************************************************
//
// This is the generic callback from host stack.
//
// pvData is actually a pointer to a tEventInfo structure.
//
// This function will be called to inform the application when a USB event has
// occurred that is outside those related to the keyboard device.  At this
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
    //
    // Cast this pointer to its actual type.
    //
    tEventInfo *pEventInfo;

    //
    // Cast this pointer to its actual type.
    //
    pEventInfo = (tEventInfo *)pvData;

    switch(pEventInfo->ui32Event)
    {
        //
        // New keyboard detected.
        //
        case USB_EVENT_CONNECTED:
        {
            //
            // See if this is a HID Keyboard.
            //
            if((USBHCDDevClass(pEventInfo->ui32Instance, 0) == USB_CLASS_HID) &&
               (USBHCDDevProtocol(pEventInfo->ui32Instance, 0) ==
                USB_HID_PROTOCOL_KEYB))
            {
                //
                // Indicate that the keyboard has been detected.
                //
                UARTprintf("Keyboard Connected\n");

                //
                // Proceed to the STATE_KEYBOARD_INIT state so that the main
                // loop can finish initialized the mouse since
                // USBHKeyboardInit() cannot be called from within a callback.
                //
                g_eUSBState = STATE_KEYBOARD_INIT;
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
            // Change the state so that the main loop knows that the device
            // is no longer present.
            //
            g_eUSBState = STATE_NO_DEVICE;

            break;
        }
        //
        // Power Fault occurred.
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
        //
        // Ignore the other events.
        //
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
ModeCallback(uint32_t ulIndex, tUSBMode eMode)
{
    //
    // Save the new mode.
    //
    g_eCurrentUSBMode = eMode;

    switch(eMode)
    {
        case eUSBModeHost:
        {
            UARTprintf("\nHost Mode.\n");
            break;
        }
        case eUSBModeDevice:
        {
            UARTprintf("\nDevice Mode.\n");
            break;
        }
        case eUSBModeNone:
        {
            UARTprintf("\nIdle Mode.\n");
            break;
        }

        //
        // Ignore the other events.
        //
        default:
        {
            UARTprintf("ERROR: Bad Mode!\n");
            break;
        }
    }
}

//*****************************************************************************
//
// This is the callback from the USB HID keyboard handler.
//
// \param psKbInstance is ignored by this function.
// \param ui32Event is one of the valid events for a keyboard device.
// \param ui32MsgParam is defined by the event that occurs.
// \param pvMsgData is a pointer to data that is defined by the event that
// occurs.
//
// This function will be called to inform the application when a keyboard has
// been plugged in or removed and any time a key is pressed or released.
//
// \return None.
//
//*****************************************************************************
void
KeyboardCallback(tUSBHKeyboard *psKbInstance, uint32_t ui32Event,
                 uint32_t ui32MsgParam, void *pvMsgData)
{
    char ui8Char;

    switch(ui32Event)
    {
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
                g_eUSBState = STATE_KEYBOARD_UPDATE;

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
                g_eUSBState = STATE_KEYBOARD_UPDATE;

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
                g_eUSBState = STATE_KEYBOARD_UPDATE;

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
                    ui8Char = ASCII_BACKSPACE;
                }
                else
                {
                    //
                    // This is not backspace so try to map the usage code to a
                    // printable ASCII character.
                    //
                    ui8Char = (char)
                        USBHKeyboardUsageToChar(g_psKeyboardInstance,
                                                &g_sUSKeyboardMap,
                                                (uint8_t)ui32MsgParam);
                }

                //
                // A zero value indicates there was no textual mapping of this
                // usage code.
                //
                if(ui8Char != 0)
                {
                    PrintChar(ui8Char);
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
// This is the main loop that runs the application.
//
//*****************************************************************************
int
main(void)
{

    tUSBMode eLastMode;
    char *pcString;

    //
    // Initialize device clock and peripherals
    //
    CM_init();

    //
    // Initialize the UART for console I/O.
    //
    UARTStdioConfig(UART0_BASE, 115200, UART_CLK_FREQ_USB);

    //
    // Initially wait for device connection.
    //
    g_eUSBState = STATE_NO_DEVICE;
    eLastMode = eUSBModeHost;
    g_eCurrentUSBMode = eUSBModeHost;

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
    // Open an instance of the keyboard driver.  The keyboard does not need
    // to be present at this time, this just save a place for it and allows
    // the applications to be notified when a keyboard is present.
    //
    g_psKeyboardInstance = USBHKeyboardOpen(KeyboardCallback, g_pui8Buffer,
                                            KEYBOARD_MEMORY_SIZE);

    //
    // Initialize the power configuration. This sets the power enable signal
    // to be active high and does not enable the power fault.
    //
    USBHCDPowerConfigInit(0, USBHCD_VBUS_AUTO_HIGH | USBHCD_VBUS_FILTER);

    //
    // Initialize the USB controller for OTG operation with a 2ms polling
    // rate.
    //
    USBHCDInit(0, g_pui8HCDPool, HCD_MEMORY_SIZE);

    //
    // Open and instance of the keyboard class driver.
    //
    UARTprintf("Host Keyboard Application\n");

    //
    // The main loop for the application.
    //
    while(1)
    {
        //
        // Run the host state machine.
        //
        USBHCDMain();

        //
        // Has the USB mode changed since last time we checked?
        //
        if(g_eCurrentUSBMode != eLastMode)
        {
            //
            // Remember the new mode.
            //
            eLastMode = g_eCurrentUSBMode;

            switch(eLastMode)
            {
                case eUSBModeHost:
                    pcString = "HOST";
                    break;

                case eUSBModeDevice:
                    pcString = "DEVICE";
                    break;

                case eUSBModeNone:
                    pcString = "NONE";
                    break;

                default:
                    pcString = "UNKNOWN";
                    break;
            }

            UARTprintf("USB mode changed to %s\n", pcString);
        }

        switch(g_eUSBState)
        {

            //
            // This state is entered when they keyboard is first detected.
            //
            case STATE_KEYBOARD_INIT:
            {
                //
                // Initialized the newly connected keyboard.
                //
                USBHKeyboardInit(g_psKeyboardInstance);

                //
                // Proceed to the keyboard connected state.
                //
                g_eUSBState = STATE_KEYBOARD_CONNECTED;

                USBHKeyboardModifierSet(g_psKeyboardInstance, g_ui32Modifiers);

                break;
            }

            case STATE_KEYBOARD_UPDATE:
            {
                //
                // If the application detected a change that required an
                // update to be sent to the keyboard to change the modifier
                // state then call it and return to the connected state.
                //
                g_eUSBState = STATE_KEYBOARD_CONNECTED;

                USBHKeyboardModifierSet(g_psKeyboardInstance, g_ui32Modifiers);

                break;
            }

            case STATE_KEYBOARD_CONNECTED:
            {
                //
                // Nothing is currently done in the main loop when the keyboard
                // is connected.
                //
                break;
            }

            case STATE_UNKNOWN_DEVICE:
            {
                //
                // Nothing to do as the device is unknown.
                //
                break;
            }

            case STATE_NO_DEVICE:
            {
                //
                // Nothing is currently done in the main loop when the keyboard
                // is not connected.
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
