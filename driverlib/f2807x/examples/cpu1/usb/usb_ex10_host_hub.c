//##############################################################################
//
// FILE:   usb_ex10_host_hub.c
//
// TITLE:  An example using that supports a USB Hub, USB keyboard, and
// a USB mass storage device.
//
//! \addtogroup driver_example_list
//! <h1>USB HUB Host example </h1>
//!
//! This example application demonstrates how to support a USB keyboard and USB
//! Mouse with a USB Hub. The display will show the connected devices on the
//! USB hub.
//!
//! To run the example you should connect a USB Hub to the microUSB port on the
//! top of the controlCARD and open up a serial terminal with the above settings
//! to view the characters typed on the keyboard. Allow the example to run with
//! the hub connected and then connect the USB Host Mouse or Keyboard.
//!
//! When a USB Mouse is connected on the Hub the position of the mouse pointer
//! and the state of the mouse buttons are output to the display. Similarly
//! when a USB Keyboard is connected, any key press on the keyboard will cause
//! them to be  sent out the SCI at 115200 baud with no parity, 8 bits and 1
//! stop bit.
//!
//! This example is for depicting the usage of Hub.
//!
//! There are some limitations in this example :
//! 1. The Example fails to recognize the USB Hub and the device if the
//!    Mouse/Keyboard is already connected to the USB Hub and the Hub is
//!    connected to the Micro USB of the Control Card.
//! 2. The same port should not be used to connect a Keyboard and mouse.  
//!
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
#include "host/usbhost.h"
#include "host/usbhhid.h"
#include "host/usbhhub.h"
#include "host/usbhhidkeyboard.h"
#include "scistdio.h"
#include "ustdlib.h"
#include "usb_ex10_host_hub.h"

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
uint8_t g_pui8HCDPool[HCD_MEMORY_SIZE * MAX_USB_DEVICES];

//*****************************************************************************
//
// Declare the USB Events driver interface.
//
//*****************************************************************************
DECLARE_EVENT_DRIVER(g_sUSBEventDriver, 0, 0, USBHCDEvents);

//*****************************************************************************
//
// The global that holds all of the host drivers in use in the application.
// In this case, only the Keyboard class is loaded.
//
//*****************************************************************************
static tUSBHostClassDriver const * const g_ppHostClassDrivers[] =
{
    &g_sUSBHostMSCClassDriver,
    &g_sUSBHIDClassDriver,
    &g_sUSBHubClassDriver,
    &g_sUSBEventDriver
};

//*****************************************************************************
//
// The current USB operating mode - Host, Device or unknown.
//
//*****************************************************************************
tUSBMode g_eCurrentUSBMode;

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
// Status bar boxes for hub ports.
//
//*****************************************************************************
#define NUM_HUB_STATUS          4

//*****************************************************************************
//
// Structure for Hub Status.
//
//*****************************************************************************
struct
{
    //
    // Holds if there is a device connected to this port.
    //
    bool bConnected;

    //
    // The instance data for the device if bConnected is true.
    //
    uint32_t ui32Instance;
}
g_psHubStatus[NUM_HUB_STATUS];

//******************************************************************************
//
// Configure the SCI and its pins. This must be called before SCIprintf().
//
//******************************************************************************
void
ConfigureSCI(void)
{
    //
    // GPIO28 is the SCI Rx pin.
    //
    GPIO_setMasterCore(28, GPIO_CORE_CPU1);
    GPIO_setPinConfig(GPIO_28_SCIRXDA);
    GPIO_setDirectionMode(28, GPIO_DIR_MODE_IN);
    GPIO_setPadConfig(28, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(28, GPIO_QUAL_ASYNC);

    //
    // GPIO29 is the SCI Tx pin.
    //
    GPIO_setMasterCore(29, GPIO_CORE_CPU1);
    GPIO_setPinConfig(GPIO_29_SCITXDA);
    GPIO_setDirectionMode(29, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(29, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(29, GPIO_QUAL_ASYNC);

    //
    // Initialize the SCI for console I/O.
    //
    SCIStdioConfig(SCIA_BASE, 115200,
                   SysCtl_getLowSpeedClock(DEVICE_OSCSRC_FREQ));

}

//*****************************************************************************
//
// This function updates the status area of the screen.  It uses the current
// state of the application to print the status bar.
//
//*****************************************************************************
void
UpdateStatus(uint32_t ui32Port)
{

    uint8_t ui8DevClass, ui8DevProtocol;

    if(g_psHubStatus[ui32Port].bConnected)
    {
        ui8DevClass = USBHCDDevClass(g_psHubStatus[ui32Port].ui32Instance, 0);
        ui8DevProtocol = USBHCDDevProtocol(
                                    g_psHubStatus[ui32Port].ui32Instance, 0);

        if(ui8DevClass == USB_CLASS_HID)
        {
            if(ui8DevProtocol == USB_HID_PROTOCOL_MOUSE)
            {
                //
                // Mouse is currently connected.
                //
                SCIprintf("\nHost Mouse is connected on Hub Port %d\n",
                          ui32Port);
            }
            else if(ui8DevProtocol == USB_HID_PROTOCOL_KEYB)
            {
                //
                // Keyboard is currently connected.
                //
                SCIprintf("\nHost Keyboard is connected on Hub Port %d\n",
                          ui32Port);
            }
            else
            {
                //
                // Unknown device is currently connected.
                //
                SCIprintf("\nUnkown Device is connected on Hub Port %d\n",
                          ui32Port);
            }
        }
        else if(ui8DevClass == USB_CLASS_MASS_STORAGE)
        {
            //
            // MSC device is currently connected.
            //
            SCIprintf("\nMass Storage Device is connected on Hub Port %d\n",
                      ui32Port);
        }
        else if(ui8DevClass == USB_CLASS_HUB)
        {
            //
            // USB Hub device is currently connected.
            //
            SCIprintf("\nUSB Hub is connected\n");
        }
        else
        {
            //
            // Unknown device is currently connected.
            //
            SCIprintf("\nUnkown Device is connected\n");
        }
    }
    else
    {
        ui8DevClass = USBHCDDevClass(g_psHubStatus[ui32Port].ui32Instance, 0);
        ui8DevProtocol = USBHCDDevProtocol(
                                     g_psHubStatus[ui32Port].ui32Instance, 0);

        if(ui8DevClass == USB_CLASS_HID)
        {
            if(ui8DevProtocol == USB_HID_PROTOCOL_MOUSE)
            {
                //
                // Mouse is currently disconnected.
                //
                SCIprintf("\nHost Mouse is Disconnected on Hub Port %d\n",
                          ui32Port);
            }
            else if(ui8DevProtocol == USB_HID_PROTOCOL_KEYB)
            {
                //
                // Keyboard is currently disconnected.
                //
                SCIprintf("\nHost Keyboard is Disconnected on Hub Port %d\n",
                          ui32Port);
            }
            else
            {
                //
                // Unknown device is currently disconnected.
                //
                SCIprintf("\nUnkown Device is Disconnected on Hub Port %d\n",
                          ui32Port);
            }
        }
        else if(ui8DevClass == USB_CLASS_MASS_STORAGE)
        {
            //
            // MSC device is currently disconnected.
            //
            SCIprintf("\nMass Storage Device is Disconnected on Hub Port %d\n",
                      ui32Port);
        }
        else if(ui8DevClass == USB_CLASS_HUB)
        {
            //
            // USB Hub device is currently disconnected.
            //
            SCIprintf("\nUSB Hub is Disconnected\n");
        }
        else
        {
            //
            // Unknown device is currently disconnected.
            //
            SCIprintf("\nUnkown Device is Disconnected\n");
        }
    }
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
    tEventInfo *pEventInfo;
    uint8_t ui8Port;

    //
    // Cast this pointer to its actual type.
    //
    pEventInfo = (tEventInfo *)pvData;

    //
    // Get the hub port number that the device is connected to.
    //
    ui8Port = USBHCDDevHubPort(pEventInfo->ui32Instance);

    switch(pEventInfo->ui32Event)
    {
        case USB_EVENT_UNKNOWN_CONNECTED:
        case USB_EVENT_CONNECTED:
        {

            //
            // If this is the hub then ignore this connection.
            //
            if((USBHCDDevClass(pEventInfo->ui32Instance, 0) == USB_CLASS_HUB))
            {
                //
                // USB Hub device is currently connected.
                //
                SCIprintf("\nUSB Hub is connected\n");
                break;
            }

            //
            // If this is not a direct connection, then the hub is on
            // port 0 so the index should be moved down from 1-4 to 0-3.
            //
            if(ui8Port > 0)
            {
                ui8Port--;
            }

            //
            // Save the device instance data.
            //
            g_psHubStatus[ui8Port].ui32Instance = pEventInfo->ui32Instance;
            g_psHubStatus[ui8Port].bConnected = true;

            //
            // Update the port status for the new device.
            //
            UpdateStatus(ui8Port);

            break;
        }

        //
        // A device has been unplugged.
        //
        case USB_EVENT_DISCONNECTED:
        {
            //
            // If this is the hub then ignore this.
            //
            if((USBHCDDevClass(pEventInfo->ui32Instance, 0) == USB_CLASS_HUB))
            {
                //
                // USB Hub device has been disconnected.
                //
                SCIprintf("\nUSB Hub is Disconnected\n");
                break;
            }

            //
            // If this is not a direct connection, then the hub is on
            // port 0 so the index should be moved down from 1-4 to 0-3.
            //
            if(ui8Port > 0)
            {
                ui8Port--;
            }

            //
            // Device is no longer connected.
            //
            g_psHubStatus[ui8Port].ui32Instance = 0;
            g_psHubStatus[ui8Port].bConnected = false;

            //
            // Update the port status for the new device.
            //
            UpdateStatus(ui8Port);

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
// This is the callback from the USB HUB mouse handler.
//
// pvCBData is ignored by this function.
// ui32Event is one of the valid events for a mouse device.
// ui32MsgParam is defined by the event that occurs.
// pvMsgData is a pointer to data that is defined by the event that occurs.
//
// This function will be called to inform the application when a mouse has
// been plugged in or removed and any time mouse movement or button pressed
// is detected.
//
// This function will return 0.
//
//*****************************************************************************
void
HubCallback(tHubInstance *psHubInstance, uint32_t ui32Event,
            uint32_t ui32MsgParam, void *pvMsgData)
{
}

//*****************************************************************************
//
// The main application loop.
//
//*****************************************************************************
int
main(void)
{
    uint32_t i32Idx;

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Initialize GPIO and configure GPIO pins for USB.
    //
    Device_initGPIO();

    //
    // Set the clocking to run from the PLL at 60MHz
    //
    SysCtl_setAuxClock(DEVICE_AUXSETCLOCK_CFG_USB);

    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Configure the required pins for USB operation.
    //
    USBGPIOEnable();

    //
    // Register the interrupt handler for USB Interrupts.
    //
    Interrupt_register(INT_USBA, &f28x_USB0OTGModeIntHandler);

    //
    // Enable Interrupts
    //
    Interrupt_enableMaster();

    //
    // Configure SCIA for debug output.
    //
    ConfigureSCI();

    //
    // Initialize the hub port status.
    //
    for(i32Idx = 0; i32Idx < NUM_HUB_STATUS; i32Idx++)
    {
        g_psHubStatus[i32Idx].bConnected = false;
        g_psHubStatus[i32Idx].ui32Instance = 0;
    }

    //
    // Open the Mouse and Keyboard Interface.
    //
    MouseOpen();
    KeyboardOpen();

    //
    // Initialize the USB stack mode and pass in a mode callback.
    //
    USBStackModeSet(0, eUSBModeForceHost, 0);

    //
    // Register the host class drivers.
    //
    USBHCDRegisterDrivers(0, g_ppHostClassDrivers, g_ui32NumHostClassDrivers);

    //
    // Open a hub instance and provide it with the memory required to hold
    // configuration descriptors for each attached device.
    //
    USBHHubOpen(HubCallback);

    //
    // Initialize the power configuration. This sets the power enable signal
    // to be active high and does not enable the power fault.
    //
    USBHCDPowerConfigInit(0, USBHCD_VBUS_AUTO_HIGH | USBHCD_VBUS_FILTER);

    //
    // Initialize the USB controller for Host mode.
    //
    USBHCDInit(0, g_pui8HCDPool, sizeof(g_pui8HCDPool));

    SCIprintf("USB Host Hub Example\n");

    //
    // The main loop for the application.
    //
    while(1)
    {
            //
            // Call the USB library to let non-interrupt code run.
            //
            USBHCDMain();

            //
            // Call the keyboard main routine.
            //
            KeyboardMain();

            //
            // Call the Mouse main routine.
            //
            MouseMain();
    }
}
