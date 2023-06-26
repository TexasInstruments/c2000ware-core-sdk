//###########################################################################
//
//! \addtogroup f2806x_example_list
//! <h1>USB Boot Loader Example (boot_demo_usb)</h1>
//!
//! \note This example is using older versions of the F2806x USB and Driver
//! Libraries (v141), which are now deprecated. The source and headers used
//! are located within the "~/bl_app/deprecated" directory.
//!
//! This example application is used in conjunction with the USB boot loader
//! (boot_usb) and turns the evaluation board into a composite device
//! supporting a mouse via the Human Interface Device class and also publishing
//! runtime Device Firmware Upgrade (DFU) capability.  Dragging a finger or
//! stylus over the touchscreen translates into mouse movement and presses on
//! marked areas at the bottom of the screen indicate mouse button press.  This
//! input is used to generate messages in HID reports sent to the USB host
//! allowing the evaluation board to control the mouse pointer on the host
//! system.
//!
//! Since the device also publishes a DFU interface, host software such as the
//! dfuprog tool can determine that the device is capable of receiving software
//! updates over USB.  The runtime DFU protocol allows such tools to signal the
//! device to switch into DFU mode and prepare to receive a new software image.
//!
//! Runtime DFU functionality requires only that the device listen for a
//! particular request (DETACH) from the host and, when this is received,
//! transfer control to the USB boot loader via the normal means to reenumerate
//! as a pure DFU device capable of uploading and downloading firmware images.
//!
//! Windows device drivers for both the runtime and DFU mode of operation can
//! be found in <tt>C:/StellarisWare/windows_drivers</tt> assuming you
//! installed StellarisWare in the default directory.
//!
//! To illustrate runtime DFU capability, use the <tt>dfuprog</tt> tool which
//! is part of the Stellaris Windows USB Examples package (SW-USB-win-xxxx.msi)
//! Assuming this package is installed in the default location, the
//! <tt>dfuprog</tt> executable can be found in the
//! <tt>C:/Program Files/Texas Instruments/Stellaris/usb_examples</tt>
//! directory.
//!
//! With the device connected to your PC and the device driver installed, enter
//! the following command to enumerate DFU devices:
//!
//! <tt>dfuprog -e</tt>
//!
//! This will list all DFU-capable devices found and you should see that you
//! have one device available which is in ``Runtime'' mode.  Entering the
//! following command will switch this device into DFU mode and leave it ready
//! to receive a new firmware image:
//!
//! <tt>dfuprog -m</tt>
//!
//! After entering this command, you should notice that the device disconnects
//! from the USB bus and reconnects again. Running ``<tt>dfuprog -e</tt>'' a
//! second time will show that the device is now in DFU mode and ready to
//! receive downloads.  At this point, either LM Flash Programmer or dfuprog
//! may be used to send a new application binary to the device.
//
//###########################################################################
// $TI Release: f2806x Support Library v1.15 $
// $Release Date: December 12, 2011 $
// $Copyright:
// Copyright (C) 2009-2023 Texas Instruments Incorporated - http://www.ti.com/
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
//###########################################################################

//
// Included Files
//
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "usblib/usblib.h"
#include "usblib/usbhid.h"
#include "usblib/usb_ids.h"
#include "usblib/device/usbdevice.h"
#include "usblib/device/usbdhid.h"
#include "usblib/device/usbdhidmouse.h"
#include "usblib/device/usbddfu_rt.h"
#include "usblib/device/usbdcomp.h"
#include "usb_hiddfu_structs.h"
#include "usblib/f2806x_usbWrapper.h"

//*****************************************************************************
//
// The incremental update for the mouse.
//
//*****************************************************************************
#define MOUSE_MOVE_INC          1
#define MOUSE_MOVE_DEC          -1

//*****************************************************************************
//
// The number of system ticks to wait for each USB packet to be sent before
// we assume the host has disconnected.  The value 50 equates to half a second.
//
//*****************************************************************************
#define MAX_SEND_DELAY          50

//*****************************************************************************
//
// The system tick timer rate.
//
//*****************************************************************************
#define SYSTICKS_PER_SECOND     100
#define MS_PER_SYSTICK          (1000 / SYSTICKS_PER_SECOND)

//*****************************************************************************
//
// Holds command bits used to signal the main loop to perform various tasks.
//
//*****************************************************************************
volatile unsigned long g_ulCommands;

//*****************************************************************************
//
// A flag used to indicate whether or not we are currently connected to the USB
// host.
//
//*****************************************************************************
volatile tBoolean g_bConnected;

//*****************************************************************************
//
// Global system tick counter holds elapsed time since the application started
// expressed in 100ths of a second.
//
//*****************************************************************************
volatile unsigned long g_ulSysTickCount;

//*****************************************************************************
//
// This enumeration holds the various states that the mouse can be in during
// normal operation.
//
//*****************************************************************************
volatile enum
{
    //
    // Unconfigured.
    //
    MOUSE_STATE_UNCONFIGURED,

    //
    // No keys to send and not waiting on data.
    //
    MOUSE_STATE_IDLE,

    //
    // Waiting on data to be sent out.
    //
    MOUSE_STATE_SENDING
}
g_eMouseState = MOUSE_STATE_UNCONFIGURED;

//*****************************************************************************
//
// Flag used to tell the main loop that it's time to pass control back to the
// boot loader for an update.
//
//*****************************************************************************
volatile tBoolean g_bUpdateSignalled;


// Prototype statements for functions found within this file.
void delay_loop(void);
void Gpio_select(void);
void Gpio_example(void);

extern volatile unsigned long ulBootEntry;

//*****************************************************************************
//
// This is the callback from the USB DFU runtime interface driver.
//
// \param pvCBData is ignored by this function.
// \param ulEvent is one of the valid events for a DFU device.
// \param ulMsgParam is defined by the event that occurs.
// \param pvMsgData is a pointer to data that is defined by the event that
// occurs.
//
// This function will be called to inform the application when a change occurs
// during operation as a DFU device.  Currently, the only event passed to this
// callback is USBD_DFU_EVENT_DETACH which tells the recipient that they should
// pass control to the boot loader at the earliest, non-interrupt context
// point.
//
// \return This function will return 0.
//
//*****************************************************************************
unsigned long
DFUDetachCallback(void *pvCBData, unsigned long ulEvent,
                  unsigned long ulMsgData, void *pvMsgData)
{
    if(ulEvent == USBD_DFU_EVENT_DETACH)
    {
        //
        // Set the flag that the main loop uses to determine when it is time
        // to transfer control back to the boot loader.  Note that we
        // absolutely DO NOT call USBDDFUUpdateBegin() here since we are
        // currently in interrupt context and this would cause bad things to
        // happen (and the boot loader to not work).
        //
        g_bUpdateSignalled = true;
    }

    return(0);
}

//*****************************************************************************
//
// This is the callback from the USB composite device class driver.
//
// \param pvCBData is ignored by this function.
// \param ulEvent is one of the valid events for a mouse device.
// \param ulMsgParam is defined by the event that occurs.
// \param pvMsgData is a pointer to data that is defined by the event that
// occurs.
//
// This function will be called to inform the application when a change occurs
// during operation as a HID class USB mouse device.
//
// \return This function will return 0.
//
//*****************************************************************************
unsigned long
MouseHandler(void *pvCBData, unsigned long ulEvent,
             unsigned long ulMsgData, void *pvMsgData)
{
    switch(ulEvent)
    {
        //
        // The USB host has connected to and configured the device.
        //
        case USB_EVENT_CONNECTED:
        {
            g_eMouseState = MOUSE_STATE_IDLE;
            g_bConnected = true;
            break;
        }

        //
        // The USB host has disconnected from the device.
        //
        case USB_EVENT_DISCONNECTED:
        {
            g_bConnected = false;
            g_eMouseState = MOUSE_STATE_UNCONFIGURED;
            break;
        }

        //
        // A report was sent to the host. We are not free to send another.
        //
        case USB_EVENT_TX_COMPLETE:
        {
            g_eMouseState = MOUSE_STATE_IDLE;
            break;
        }

    }
    return(0);
}

//***************************************************************************
//
// Wait for a period of time for the state to become idle.
//
// \param ulTimeoutTick is the number of system ticks to wait before
// declaring a timeout and returning \b false.
//
// This function polls the current keyboard state for ulTimeoutTicks system
// ticks waiting for it to become idle.  If the state becomes idle, the
// function returns true.  If it ulTimeoutTicks occur prior to the state
// becoming idle, false is returned to indicate a timeout.
//
// \return Returns \b true on success or \b false on timeout.
//
//***************************************************************************
tBoolean
WaitForSendIdle(unsigned long ulTimeoutTicks)
{
    unsigned long ulStart;
    unsigned long ulNow;
    unsigned long ulElapsed;

    ulStart = g_ulSysTickCount;
    ulElapsed = 0;

    while(ulElapsed < ulTimeoutTicks)
    {
        //
        // Is the mouse is idle, return immediately.
        //
        if(g_eMouseState == MOUSE_STATE_IDLE)
        {
            return(true);
        }

        //
        // Determine how much time has elapsed since we started waiting.  This
        // should be safe across a wrap of g_ulSysTickCount.
        //
        ulNow = g_ulSysTickCount;
        ulElapsed = ((ulStart < ulNow) ? (ulNow - ulStart) :
                     (((unsigned long)0xFFFFFFFF - ulStart) + ulNow + 1));
    }

    //
    // If we get here, we timed out so return a bad return code to let the
    // caller know.
    //
    return(false);
}

//*****************************************************************************
//
// This function provides simulated movements of the mouse.
//
//*****************************************************************************
void
MoveHandler(void)
{
    unsigned long ulRetcode;
    char cDeltaX, cDeltaY;

    //
    // Determine the direction to move the mouse.
    //
    ulRetcode = g_ulSysTickCount % (4 * SYSTICKS_PER_SECOND);
    if(ulRetcode < SYSTICKS_PER_SECOND)
    {
        cDeltaX = MOUSE_MOVE_INC;
        cDeltaY = 0;
    }
    else if(ulRetcode < (2 * SYSTICKS_PER_SECOND))
    {
        cDeltaX = 0;
        cDeltaY = MOUSE_MOVE_INC;
    }
    else if(ulRetcode < (3 * SYSTICKS_PER_SECOND))
    {
        cDeltaX = (char)MOUSE_MOVE_DEC;
        cDeltaY = 0;
    }
    else
    {
        cDeltaX = 0;
        cDeltaY = (char)MOUSE_MOVE_DEC;
    }

    //
    // Tell the HID driver to send this new report.
    //
    g_eMouseState = MOUSE_STATE_SENDING;
    ulRetcode = USBDHIDMouseStateChange((void *)&g_sMouseDevice, cDeltaX,
                                        cDeltaY, 0);

    //
    // Did we schedule the report for transmission?
    //
    if(ulRetcode == MOUSE_SUCCESS)
    {
        //
        // Wait for the host to acknowledge the transmission if all went well.
        //
        if(!WaitForSendIdle(MAX_SEND_DELAY))
        {
            //
            // The transmission failed, so assume the host disconnected and go
            // back to waiting for a new connection.
            //
            g_bConnected = false;
        }
    }
}


//*****************************************************************************
//
// This is the interrupt handler for the SysTick interrupt.  It is called
// periodically and updates a global tick counter then sets a flag to tell the
// main loop to check the button state.
//
//*****************************************************************************
__interrupt void
SysTickHandler(void)
{
    g_ulSysTickCount++;
    
    HWREG(&g_ulCommands) |= 1;
    
    PieCtrlRegs.PIEACK.all |= 1;
}

//
// delay_loop - 
//
void
delay_loop()
{
    short      i;
    for (i = 0; i < 1000; i++)
    {
        
    }
}

//
// GpioToggle - 
//
void
GpioToggle(void)
{ 
    //
    // Example 1:
    // Toggle I/Os using DATA registers
    //
    GpioDataRegs.GPATOGGLE.all =0xCFFFFFFF;
    GpioDataRegs.GPBTOGGLE.all =0x0000000F;
}

//
// Gpio_select -
//
void
Gpio_select(void)
{
    EALLOW;
	GpioCtrlRegs.GPAMUX1.all = 0x00000000;  // All GPIO
	GpioCtrlRegs.GPAMUX2.all = 0x00000000;  // All GPIO
	GpioCtrlRegs.GPAMUX1.all = 0x00000000;  // All GPIO
    GpioCtrlRegs.GPADIR.all = 0xCFFFFFFF;   // All outputs
    GpioCtrlRegs.GPBDIR.all = 0x0000000F;   // All outputs
    EDIS;

    //
    // Set pins to a known state
    //
    GpioDataRegs.GPASET.all    =0x8AAAAAAA;
    GpioDataRegs.GPACLEAR.all  =0x45555555;

    GpioDataRegs.GPBSET.all    =0x0000000A;   			  
    GpioDataRegs.GPBCLEAR.all  =0x00000005;   			     
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
    //10MHz ->PLL->60MHz->C28
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

//*****************************************************************************
//
// This is the main loop that runs the application.
//
//*****************************************************************************
int
main(void)
{
	g_bConnected = 0;
	g_bUpdateSignalled = 0;
    
    //
    // Set the clocking
    //
	SysCtrlInit();

    //
    // Initialize interrupt controller and vector table
    //
    InitPieCtrl();
    InitPieVectTable();

    //
    // Set the system tick to fire 100 times per second.
    //
    SysTickPeriodSet(SysCtlClockGet() / SYSTICKS_PER_SECOND);
    SysTickIntEnable();
    SysTickEnable();
    
    //
    // Register Interrupt Handlers
    //
    IntRegister(INT_TINT0, SysTickHandler);
    IntRegister(INT_USB0, f2806x_USB0DeviceIntHandler);
    IntMasterEnable();

    //
    // Initialize each of the device instances that will form our composite
    // USB device.
    //
    g_sCompDevice.psDevices[0].pvInstance =
        USBDHIDMouseCompositeInit(0, (tUSBDHIDMouseDevice *)&g_sMouseDevice);
    g_sCompDevice.psDevices[1].pvInstance =
        USBDDFUCompositeInit(0, (tUSBDDFUDevice *)&g_sDFUDevice);

    //
    // Pass the USB library our device information, initialize the USB
    // controller and connect the device to the bus.
    //
    USBDCompositeInit(0, &g_sCompDevice, DESCRIPTOR_BUFFER_SIZE,
                      g_pcDescriptorBuffer);

    //
    // Drop into the main loop.
    //
    while(!g_bUpdateSignalled)
    {
        //
        // Wait for USB configuration to complete.
        //
        while(!g_bConnected && !g_bUpdateSignalled)
        {
            
        }
        
        Gpio_select();

        //
        // Now keep processing the mouse as long as the host is connected and
        // we've not been told to prepare for a firmware upgrade.
        //
        while(g_bConnected && !g_bUpdateSignalled)
        {
            //
			// Do stuff while we are connected
            //
			GpioToggle();
			
            if(HWREG(&g_ulCommands) & 1)
            {
                HWREG(&g_ulCommands) &= ~1;
                MoveHandler();
            }
        }

        //
        // If we drop out of the previous loop, either the host has
        // disconnected or a firmware upgrade has been signalled.
        //
    }

    //
    // If we get here, a firmware upgrade has been signalled so we need to get
    // back into the boot loader to allow this to happen.  Call the USB DFU
    // device class to do this for us.  Note that this function never returns.
    //
    USBDDFUUpdateBegin();
}

//
// End of File
//

