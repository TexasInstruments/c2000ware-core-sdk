//###########################################################################
//
// FILE:   usb_host_mouse.c
//
// TITLE:  USB Mouse Host example. 
//
// ASSUMPTIONS:
//
//    This program requires:
//        - the F2806x header files 
//        - Driverlib (/ControlSUITE/device_support/f2806x/version/MWare/
//                                      driverlib/Debug/driverlib.lib)
//        - Usblib (/ControlSUITE/device_support/f2806x/version/MWare/
//                                      lib/usblib.lib)
//        - USB Capable F2806x
//
// Description:
//
//! \addtogroup f2806x_example_list
//! <h1>USB HID Mouse Host (usb_host_mouse)</h1>
//!
//! This application demonstrates the handling of a USB mouse attached to the
//! evaluation kit.  Once attached, the position of the mouse pointer and the
//! state of the mouse buttons are output to the UART.
//!
//! UART0, connected to the FTDI virtual COM port and running at 115,200,
//! 8-N-1, is used to display messages from this application.
//
//  Section .ebss was initialized to 0x0000 in
//  F2806x_CodeStartBranch_ebss_init.asm. This was to ensure that all global
//  variables of the usblib are initialized to 0x0000 on the F2806x.
//
//###########################################################################	
// $TI Release: $ 
// $Release Date: $ 
// $Copyright:
// Copyright (C) 2009-2024 Texas Instruments Incorporated - http://www.ti.com/
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
//#############################################################################

//
// Included Files
//
#include "DSP28x_Project.h"
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/rom.h"
#include "driverlib/usb.h"
#include "inc/hw_usb.h"
#include "include/usblib.h"
#include "include/usbhid.h"
#include "driverlib/usb_hal.h"
#include "include/host/usbhost.h"
#include "include/host/usbhhid.h"
#include "include/host/usbhhidmouse.h"
#include "utils/uartstdio.h"

//
// The number of SysTick ticks per second.
//
#define TICKS_PER_SECOND 100
#define MS_PER_SYSTICK (1000 / TICKS_PER_SECOND)

//
// Our running system tick counter and a global used to determine the time
// elapsed since last call to GetTickms().
//
uint32_t g_ui32SysTickCount;
uint32_t g_ui32LastTick;

//
// The size of the host controller's memory pool in bytes.
//
#define HCD_MEMORY_SIZE         128

//
// The memory pool to provide to the Host controller driver.
//
unsigned char g_pHCDPool[HCD_MEMORY_SIZE];

//
// The size of the mouse device interface's memory pool in bytes.
//
#define MOUSE_MEMORY_SIZE       128

//
// The memory pool to provide to the mouse device.
//
uint8_t g_pucBuffer[MOUSE_MEMORY_SIZE];

//
// Declare the USB Events driver interface.
//
DECLARE_EVENT_DRIVER(g_sUSBEventDriver, 0, 0, USBHCDEvents);

//
// The global that holds all of the host drivers in use in the application.
// In this case, only the Mouse class is loaded.
//
static tUSBHostClassDriver const * const g_ppHostClassDrivers[] =
{
    &g_sUSBHIDClassDriver,
    &g_sUSBEventDriver
};

//
// This global holds the number of class drivers in the g_ppHostClassDrivers
// list.
//
static const unsigned long g_ulNumHostClassDrivers =
    sizeof(g_ppHostClassDrivers) / sizeof(tUSBHostClassDriver *);

//
// The global value used to store the mouse instance value.
//
static tUSBHMouse *g_psMouseInstance;

//
// The global values used to store the mouse state.
//
static unsigned long g_ui32Buttons;
static long g_i32CursorX;
static long g_i32CursorY;

//
// The current USB operating mode - Host, Device or unknown.
//
tUSBMode g_eCurrentUSBMode;

//
// This enumerated type is used to hold the states of the mouse.
//
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
    // A power fault has occured.
    //
    STATE_POWER_FAULT
}
g_eUSBState;

//
// The error routine that is called if the driver library encounters an error.
//
#ifdef DEBUG
void
__error__(char *pcFilename, unsigned long ulLine)
{
    
}
#endif

//
// USBHCDEvents - This is the generic callback from host stack.
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
                // Proceed to the STATE_MOUSE_INIT state so that the main 
                // loop can finish initialized the mouse since 
                // USBHMouseInit() cannot be called from within a callback.
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
            //
            // An unknown device was detected.
            //
            g_eUSBState = STATE_UNKNOWN_DEVICE;
            UARTprintf("Unknown Device Connected\n");

            break;
        }
        //
        // Device has been unplugged.
        //
        case USB_EVENT_DISCONNECTED:
        {

            //
            // Change the state so that the main loop knows that the device is
            // no longer present.
            //
            g_eUSBState = STATE_NO_DEVICE;
            UARTprintf("Device Disconnected\n");

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

            //
            // No power means no device is present.
            //
            g_eUSBState = STATE_POWER_FAULT;
            UARTprintf("Power Fault\n");

            break;
        }

        default:
        {
            break;
        }
    }
}

//
// SysTickIntHandler - This is the handler for this SysTick interrupt.
//
__interrupt void
SysTickIntHandler(void)
{
    //
    // Update our tick counter.
    //
    g_ui32SysTickCount++;
    PieCtrlRegs.PIEACK.all |= 1;
}

//
// GetTickms - This function returns the number of ticks since the last time 
// this function was called.
//
uint32_t
GetTickms(void)
{
    uint32_t ui32RetVal;
    uint32_t ui32Saved;

    ui32RetVal = g_ui32SysTickCount;
    ui32Saved = ui32RetVal;

    if(ui32Saved > g_ui32LastTick)
    {
        ui32RetVal = ui32Saved - g_ui32LastTick;
    }
    else
    {
        ui32RetVal = g_ui32LastTick - ui32Saved;
    }

    //
    // This could miss a few milliseconds but the timings here are on a
    // much larger scale.
    //
    g_ui32LastTick = ui32Saved;

    //
    // Return the number of milliseconds since the last time this was called.
    //
    return(ui32RetVal * MS_PER_SYSTICK);
}

//
// ModeCallback - USB Mode callback
//
// \param ulIndex is the zero-based index of the USB controller making the
//        callback.
// \param eMode indicates the new operating mode.
//
// This function is called by the USB library whenever an OTG mode change
// occurs and, if a connection has been made, informs us of whether we are to
// operate as a host or device.
//
// \return None.
//
void
ModeCallback(unsigned long ulIndex, tUSBMode eMode)
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
    	default:
    	{
    		UARTprintf("ERROR: Bad Mode!\n");
    		break;
    	}
    }
}

//
// MouseCallback - This is the callback from the USB HID mouse handler.
//
// \param pvCBData is ignored by this function.
// \param ulEvent is one of the valid events for a mouse device.
// \param ulMsgParam is defined by the event that occurs.
// \param pvMsgData is a pointer to data that is defined by the event that
// occurs.
//
// This function will be called to inform the application when a mouse has
// been plugged in or removed and any time mouse movement or button pressed
// is detected.
//
// \return This function will return 0.
//
void
MouseCallback(tUSBHMouse *pvCBData, uint32_t ui32Event, uint32_t ui32MsgParam,
              void *pvMsgData)
{
    int32_t i32DoUpdate;
    volatile char pcBuffer[20];

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
        	// The mouse returns a 8 bit signed value...check to see if we need
            // to sign extend
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

            break;
        }

        //
        // Mouse Y movement detected.
        //
        case USBH_EVENT_HID_MS_Y:
        {
        	//
        	// The mouse returns a 8 bit signed value...check to see if we need
            // to sign extend
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
    	//
		// Display the current mouse position and button state.
		//
		UARTprintf("\rPos: %l, %l  Buttons: %l%l%l    ", g_i32CursorX, 
                   g_i32CursorY, g_ui32Buttons & 1, (g_ui32Buttons & 2) >> 1,
				   (g_ui32Buttons & 4) >> 2);
    }
}

//
// SysCtrlInit - 
//
void
SysCtrlInit(void)
{
    EALLOW;
    
    //
    // Disable Watchdog
    //
    SysCtrlRegs.WDCR = 0x68;

    //
    // Setup Clock
    // 20MHz ->PLL->80MHz->C28
    //      ->PLL2->120MHz->USB
    //
    SysCtrlRegs.CLKCTL.bit.XCLKINOFF = 1;
    SysCtrlRegs.CLKCTL.bit.XTALOSCOFF = 0;
    SysCtrlRegs.CLKCTL.bit.OSCCLKSRC2SEL = 0;
    SysCtrlRegs.CLKCTL.bit.OSCCLKSRCSEL = 1;

    while(SysCtrlRegs.PLLSTS.bit.MCLKSTS);
    SysCtrlRegs.PLLSTS.bit.DIVSEL = 0;
    SysCtrlRegs.PLLSTS.bit.MCLKOFF = 1;
    SysCtrlRegs.PLLCR.bit.DIV = 4;
    while(!SysCtrlRegs.PLLSTS.bit.PLLLOCKS);
    SysCtrlRegs.PLLSTS.bit.MCLKOFF = 1;
    SysCtrlRegs.PLLSTS.bit.DIVSEL = 3;

    SysCtrlRegs.PLL2CTL.bit.PLL2CLKSRCSEL = 2;
    SysCtrlRegs.PLL2CTL.bit.PLL2EN = 1;
    SysCtrlRegs.PLL2MULT.bit.PLL2MULT = 6;
    while(!SysCtrlRegs.PLL2STS.bit.PLL2LOCKS);

    //
    // Enable USB Clock
    //
    SysCtrlRegs.PCLKCR3.bit.USB0ENCLK = 1;
    
    // 
    // Enable PHY
    //
    GpioCtrlRegs.GPACTRL2.bit.USB0IOEN = 1;

    EDIS;
}

//
// main - This is the main loop that runs the application.
//
int
main(void)
{
	//
    // Section .ebss was initialized to 0x0000 in
	// F2806x_CodeStartBranch_ebss_init.asm. This was to ensure that all global
	// variables of the usblib are initialized to 0x0000 on the F2806x.
	//

    //
    // Set the clocking to run from the PLL
    //
    SysCtrlInit();

    //
    // Initialize interrupt controller and vector table
    InitPieCtrl();
    InitPieVectTable();

    //
    // Enable Host Mode
    //
    EALLOW;
    HWREG(USBMODESEL) = USBMODESEL_HOST;
    HWREG(USB0_BASE + USB_O_GPCS) = USBGPCS_HOST;
    EDIS;

    //
    // Enable the peripherals used by this example.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    //
    // Enable the UART.
    //
    EALLOW;
    GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 1;
    GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0;
    GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3;
    GpioCtrlRegs.GPADIR.bit.GPIO28 = 0;

    GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 1;
    GpioCtrlRegs.GPAPUD.bit.GPIO29 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO29 = 1;
    EDIS;

    UARTStdioInit(0);

    //
    // Enable Clocking to the USB controller.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_USB0);

    //
    // Register interrupt handler and enable interrupts
    //
    USBGPIOEnable();
    USBIntRegister(USB0_BASE, f28x_USB0HostIntHandler);
    IntMasterEnable();

    UARTprintf("\033[2JHost Mouse Application\n");

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
    USBHCDRegisterDrivers(0, g_ppHostClassDrivers, g_ulNumHostClassDrivers);

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
        USBHMouseOpen(MouseCallback, g_pucBuffer, MOUSE_MEMORY_SIZE);

    //
    // Initialize the power configuration. This sets the power enable signal
    // to be active high and does not enable the power fault.
    //
    USBHCDPowerConfigInit(0, USBHCD_VBUS_AUTO_HIGH | USBHCD_VBUS_FILTER);

    //
    // Initialize the USB controller for Host operation
    //
    USBHCDInit(0, g_pHCDPool, HCD_MEMORY_SIZE);

    //
    // The main loop for the application.
    //
    while(1)
    {
        //
        // Periodidcally call the host mode stack to 
        // process pending actions
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
// End of File
//

