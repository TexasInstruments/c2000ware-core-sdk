//###########################################################################
//
// FILE:   usb_dev_mouse.c
//
// TITLE:  USB Mouse Device example. 
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
//! <h1>USB HID Mouse Device (usb_dev_mouse)</h1>
//!
//! This example application turns the evaluation board into a USB mouse
//! supporting the Human Interface Device class.  The mouse pointer will move
//! in a square pattern for the duration of the time it is plugged in.
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
// Copyright (C) 2009-2025 Texas Instruments Incorporated - http://www.ti.com/
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
#include "driverlib/debug.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/usb.h"
#include "inc/hw_usb.h"
#include "include/usblib.h"
#include "include/usbhid.h"
#include "driverlib/usb_hal.h"
#include "include/device/usbdevice.h"
#include "include/device/usbdhid.h"
#include "include/device/usbdhidmouse.h"
#include "utils/uartstdio.h"
#include "usb_mouse_structs.h"

//
// The incremental update for the mouse.
//
#define MOUSE_MOVE_INC          1
#define MOUSE_MOVE_DEC          -1

//
// The system tick timer rate.
//
#define SYSTICKS_PER_SECOND     100
#define MS_PER_SYSTICK          (1000 / SYSTICKS_PER_SECOND)

//
// Holds command bits used to signal the main loop to perform various tasks.
//
volatile unsigned long g_ulCommands;
#define TICK_EVENT              0

//
// A flag used to indicate whether or not we are currently connected to the USB
// host.
//
volatile tBoolean g_bConnected;

//
// Global system tick counter holds elapsed time since the application started
// expressed in 100ths of a second.
//
volatile unsigned long g_ulSysTickCount;

//
// Debug-related definitions and declarations.
//
// Debug output is available via UART0 if DEBUG is defined during build.
//
#ifdef DEBUG
//
// Map all debug print calls to UARTprintf in debug builds.
//
#define DEBUG_PRINT UARTprintf

#else

//
// Compile out all debug print calls in release builds.
//
#define DEBUG_PRINT while(0) ((int32_t (*)(char *, ...))0)
#endif

//
// The number of system ticks to wait for each USB packet to be sent before
// we assume the host has disconnected.  The value 50 equates to half a second.
//
#define MAX_SEND_DELAY          50

//
// This enumeration holds the various states that the mouse can be in during
// normal operation.
//
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
// MouseHandler - This function handles notification messages from the mouse 
// device driver.
//
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
        // A report was sent to the host.  We are not free to send another.
        //
        case USB_EVENT_TX_COMPLETE:
        {
            g_eMouseState = MOUSE_STATE_IDLE;
            break;
        }

    }

    return(0);
}

//
// WaitForSendIdle - Wait for a period of time for the state to become idle.
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

//
// MoveHandler - This function provides simulated movements of the mouse.
//
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

//
// SysTickHandler - This is the interrupt handler for the SysTick interrupt.
// It is called periodically and updates a global tick counter then sets a flag
// to tell the main loop to move the mouse.
//
__interrupt void
SysTickHandler(void)
{
    g_ulSysTickCount++;
    HWREG(&g_ulCommands) |= 1;
    PieCtrlRegs.PIEACK.all |= 1;
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

    g_bConnected = false;
    //
    // Set the clocking to run from the PLL
    //
    SysCtrlInit();
    InitPieCtrl();
    InitPieVectTable();

    //
    // Enable Device Mode
    //
    EALLOW;
    HWREG(USBMODESEL) = USBMODESEL_DEV;
    HWREG(USB0_BASE + USB_O_GPCS) = USBGPCS_DEV;
    EDIS;

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
    UARTprintf("\033[2JMouse device application\n");

    //
    // Set the system tick to fire 100 times per second.
    //
    SysTickPeriodSet(SysCtlClockGet(SYSTEM_CLOCK_SPEED) / SYSTICKS_PER_SECOND);
    SysTickIntEnable();
    SysTickEnable();

    USBGPIOEnable();
    
    //
    // Register interrupt handlers
    //
    IntRegister(INT_TINT0, SysTickHandler);
    USBIntRegister(USB0_BASE, f28x_USB0DeviceIntHandler);

    //
    // Initialize the USB stack for device mode.
    //
    USBStackModeSet(0, eUSBModeForceDevice, 0);

    //
    // Pass the USB library our device information, initialize the USB
    // controller and connect the device to the bus.
    //
    USBDHIDMouseInit(0, (tUSBDHIDMouseDevice *)&g_sMouseDevice);

    IntMasterEnable();

    //
    // Drop into the main loop.
    //
    while(1)
    {
        //
        // Tell the user what we are doing.
        //
        UARTprintf("Waiting for host...\n");

        //
        // Wait for USB configuration to complete.
        //
        while(!g_bConnected)
        {
            
        }

        //
        // Update the status.
        //
        UARTprintf("Host connected...\n");

        //
        // Now keep processing the mouse as long as the host is connected.
        //
        while(g_bConnected)
        {
            //
            // If it is time to move the mouse then do so.
            //
            if(HWREG(&g_ulCommands) & 1)
            {
                HWREG(&g_ulCommands) &= ~1;
                MoveHandler();
            }
        }
    }
}

//
// End of File
//

