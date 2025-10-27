//##############################################################################
//
// FILE:   usb_ex2_device_mouse_cm.c
//
// TITLE:   Main routines for the USB HID mouse example.
//
//! \addtogroup driver_example_cm_list
//! <h1> USB HID Mouse Device </h1>
//!
//! This example application turns the evaluation board into a USB mouse
//! supporting the Human Interface Device class.  After loading and running the
//! example simply connect the PC to the controlCARDs microUSB port using a USB
//! cable, and the mouse pointer will move in a square pattern for the duration
//! of the time it is plugged in.
//!
//! UART0, connected to the FTDI virtual COM port and running at 115200,
//! 8-N-1, is used to display messages from this application.
//!
//
//##############################################################################
//
//
// 
// C2000Ware v6.00.01.00
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

#include "cm.h"
#include "usblib.h"
#include "usbhid.h"
#include "device/usbdevice.h"
#include "device/usbdhid.h"
#include "device/usbdhidmouse.h"
#include "usb_hal.h"
#include "uartstdio.h"
#include "usb_ex2_device_mouse_structs.h"
#include <string.h>

#ifdef DEBUG // Debug output is available via UART0 if DEBUG is defined.
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

//******************************************************************************
//
// The incremental update for the mouse.
//
//******************************************************************************
#define MOUSE_MOVE_INC          1
#define MOUSE_MOVE_DEC          -1

//******************************************************************************
//
// Default line coding settings for the redirected UART.
//
//******************************************************************************
#define DEFAULT_BIT_RATE        115200
#define DEFAULT_UART_CONFIG     (UART_CONFIG_WLEN_8 | UART_CONFIG_PAR_NONE |   \
                                 UART_CONFIG_STOP_ONE)
#define UART_CLK_FREQ_CM        30000000

//******************************************************************************
//
// The system tick timer rate.
//
//******************************************************************************
#define SYSTICKS_PER_SECOND     100
#define MS_PER_SYSTICK          (1000 / SYSTICKS_PER_SECOND)

//******************************************************************************
//
// Holds command bits used to signal the main loop to perform various tasks.
//
//******************************************************************************
volatile uint32_t g_ui32Commands;
#define TICK_EVENT              0

//******************************************************************************
//
// A flag used to indicate whether or not we are currently connected to the USB
// host.
//
//******************************************************************************
volatile bool g_bConnected;

//******************************************************************************
//
// Global system tick counter holds elapsed time since the application started
// expressed in 100ths of a second.
//
//******************************************************************************
volatile uint32_t g_ui32SysTickCount;

//******************************************************************************
//
// The number of system ticks to wait for each USB packet to be sent before
// we assume the host has disconnected.  The value 50 equates to half a second.
//
//******************************************************************************
#define MAX_SEND_DELAY         50

//******************************************************************************
//
// This enumeration holds the various states that the mouse can be in during
// normal operation.
//
//******************************************************************************
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

//******************************************************************************
//
// This function handles notification messages from the mouse device driver.
//
//******************************************************************************
uint32_t
MouseHandler(void *pvCBData, uint32_t ui32Event, uint32_t ui32MsgData,
             void *pvMsgData)
{
    switch(ui32Event)
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

        //
        // Ignore the other events.
        //
        default:
            break;
    }

    return(0);
}

//******************************************************************************
//
// Wait for a period of time for the state to become idle.
// \param ui32TimeoutTicks is the number of system ticks to wait before
//         declaring a timeout and returning \b false.
//
// This function polls the current keyboard state for ui32TimeoutTicks system
// ticks waiting for it to become idle.  If the state becomes idle, the
// function returns true.  If it ui32TimeoutTicks occur prior to the state
// becoming idle, false is returned to indicate a timeout.
//
// \return Returns \b true on success or \b false on timeout.
//
//******************************************************************************
bool
WaitForSendIdle(uint32_t ui32TimeoutTicks)
{
    uint32_t ui32Start;
    uint32_t ui32Now;
    uint32_t ui32Elapsed;

    ui32Start = g_ui32SysTickCount;
    ui32Elapsed = 0;

    while(ui32Elapsed < ui32TimeoutTicks)
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
        // should be safe across a wrap of g_ui32SysTickCount.
        //
        ui32Now = g_ui32SysTickCount;
        ui32Elapsed = ((ui32Start < ui32Now) ? (ui32Now - ui32Start) :
                       (((uint32_t)0xFFFFFFFF - ui32Start) + ui32Now + 1));
    }

    //
    // If we get here, we timed out so return a bad return code to let the
    // caller know.
    //
    return(false);
}

//******************************************************************************
//
// This function provides simulated movements of the mouse.
//
//******************************************************************************
void
MoveHandler(void)
{
    uint32_t ui32Retcode;
    char cDeltaX, cDeltaY;

    //
    // Determine the direction to move the mouse.
    //
    ui32Retcode = g_ui32SysTickCount % (4 * SYSTICKS_PER_SECOND);

    if(ui32Retcode < SYSTICKS_PER_SECOND)
    {
        cDeltaX = MOUSE_MOVE_INC;
        cDeltaY = 0;
    }
    else if(ui32Retcode < (2 * SYSTICKS_PER_SECOND))
    {
        cDeltaX = 0;
        cDeltaY = MOUSE_MOVE_INC;
    }
    else if(ui32Retcode < (3 * SYSTICKS_PER_SECOND))
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

    ui32Retcode = USBDHIDMouseStateChange((void *)&g_sMouseDevice, cDeltaX,
                                        cDeltaY, 0);

    //
    // Did we schedule the report for transmission?
    //
    if(ui32Retcode == MOUSE_SUCCESS)
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

//******************************************************************************
//
// This is the interrupt handler for the SysTick interrupt.  It is called
// periodically and updates a global tick counter then sets a flag to tell the
// main loop to move the mouse.
//
//******************************************************************************
__interrupt void
SysTickHandler(void)
{
    g_ui32SysTickCount++;
    HWREGBITW(&g_ui32Commands, TICK_EVENT) = 1;
}


//******************************************************************************
//
// This is the main loop that runs the application.
//
//******************************************************************************
int
main(void)
{
    g_bConnected = false;

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
    Interrupt_registerHandler(INT_USB0, &CM_USB0DeviceIntHandler);

    //
    // Set the system tick to fire 100 times per second.
    //
    SYSTICK_disableCounter();
    SYSTICK_setClockSource(SYSTICK_CLOCK_SOURCE_INTERNAL);
    SYSTICK_setPeriod(120000000 / SYSTICKS_PER_SECOND);
    SYSTICK_enableInterrupt();
    SYSTICK_enableCounter();

    //
    // Register interrupt handlers in the RAM vector table
    //
    Interrupt_registerHandler(FAULT_SYSTICK, SysTickHandler);

    //
    // Set the USB stack mode to Device mode with VBUS monitoring.
    //
    USBStackModeSet(0, eUSBModeForceDevice, 0);

    //
    // Show the application name on the display and UART output.
    //
    DEBUG_PRINT("\nC2000 F2838x Series USB HID Mouse device example\n");
    DEBUG_PRINT("---------------------------------\n\n");

    //
    // Pass the USB library our device information, initialize the USB
    // controller and connect the device to the bus.
    //
    USBDHIDMouseInit(0, (tUSBDHIDMouseDevice *)&g_sMouseDevice);

    //
    // Enable interrupts now that the application is ready to start.
    //
    Interrupt_enableInProcessor();

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
            if(HWREG(&g_ui32Commands) & 1)
            {
                HWREG(&g_ui32Commands) &= ~1;
                MoveHandler();
            }
        }
    }
}
