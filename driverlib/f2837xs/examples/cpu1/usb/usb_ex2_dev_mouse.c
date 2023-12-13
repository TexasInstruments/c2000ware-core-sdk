//##############################################################################
//
// FILE:   usb_ex2_dev_mouse.c
//
// TITLE:  Main routines for the USB HID mouse example.
//
//! \addtogroup driver_example_list
//! <h1> USB HID Mouse Device </h1>
//!
//! This example application turns the evaluation board into a USB mouse
//! supporting the Human Interface Device class.  After loading and running the
//! example simply connect the PC to the controlCARDs microUSB port using a USB
//! cable, and the mouse pointer will move in a square pattern for the duration
//! of the time it is plugged in.
//!
//! SCIA, connected to the FTDI virtual COM port and running at 115200,
//! 8-N-1, is used to display messages from this application.
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
//#include "driverlib.h"
//#include "device.h"
#include "usb_hal.h"
#include "board.h"
#include "c2000ware_libraries.h"
#include "usblib.h"
#include "usbhid.h"
#include "device/usbdevice.h"
#include "device/usbdhid.h"
//#include "device/usbdhidmouse.h"
//#include "usb_ex2_mouse_structs.h"
#include "usb_structs.h"
#include "scistdio.h"

void INT_myUSB0_ISR(void);

//******************************************************************************
//
// Defines
//
//******************************************************************************
#define MOUSE_MOVE_INC           1    // The incremental update for the mouse.
#define MOUSE_MOVE_DEC          -1
#define TICKS_PER_SECOND        100
#define MS_PER_SYSTICK          (1000 / TICKS_PER_SECOND)
#define TICK_EVENT               0

#ifdef DEBUG // Debug output is available via SCIA if DEBUG is defined.
    //
    // Map all debug print calls to SCIprintf in debug builds.
    //
    #define DEBUG_PRINT SCIprintf
#else
    //
    // Compile out all debug print calls in release builds.
    //
    #define DEBUG_PRINT while(0) ((int32_t (*)(char *, ...))0)
#endif

#define MAX_SEND_DELAY          50   // The number of system ticks to wait for
                                     // each USB packet to be sent before
                                     // we assume the host has disconnected.
                                     // The value 50 equates to half a second.

//******************************************************************************
//
// Globals
//
//******************************************************************************
volatile uint32_t g_ui32Commands;        // Holds command bits used to signal
                                         // the main loop to perform
                                         // various tasks.
volatile bool g_bConnected;              // A flag used to indicate whether or
                                         // not we are currently connected to
                                         // the USB host.
volatile uint32_t g_ui32TickCount;       // Global system tick counter holds
                                         // elapsed time since the application
                                         // started expressed in 100ths of a
                                         // second.
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
// MouseHandler - This function handles notification messages from the
//                mouse device driver.
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
// WaitForSendIdle - Wait for a period of time for the state to become idle.
//
// \param ui32TimeoutTick is the number of system ticks to wait before declaring
//  a timeout and returning \b false.
//
// This function polls the current keyboard state for ui32TimeoutTicks system
// ticks waiting for it to become idle. If the state becomes idle, the
// function returns true. If it ui32TimeoutTicks occur prior to the state
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

    ui32Start = g_ui32TickCount;
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
        // should be safe across a wrap of g_ui32TickCount.
        //
        ui32Now = g_ui32TickCount;
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
// MoveHandler - This function provides simulated movements of the mouse.
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
    ui32Retcode = g_ui32TickCount % (4 * TICKS_PER_SECOND);
    if(ui32Retcode < TICKS_PER_SECOND)
    {
        cDeltaX = MOUSE_MOVE_INC;
        cDeltaY = 0;
    }
    else if(ui32Retcode < (2 * TICKS_PER_SECOND))
    {
        cDeltaX = 0;
        cDeltaY = MOUSE_MOVE_INC;
    }
    else if(ui32Retcode < (3 * TICKS_PER_SECOND))
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
// CPUTimerIntHandler - This is the interrupt handler for the CPU Timer
// interrupt. It is called periodically and updates a global tick counter then
// sets a flag to tell the main loop to move the mouse.
//
//******************************************************************************
__interrupt void
CPUTimerIntHandler(void)
{
    GPIO_writePin(0,1);

    g_ui32TickCount++;

    HWREG(&g_ui32Commands) |= 1;

    GPIO_writePin(0,0);

    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
}

#ifdef DEBUG
//******************************************************************************
//
// ConfigureSCI - Configure the SCI and its pins. This must be called before
// DEBUG_PRINT(). It configures the SCI GPIOs and the Console I/O.
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
#endif

//******************************************************************************
//
// This is the main application entry function.
//
//******************************************************************************
int main(void)
{
    g_bConnected = false;

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
    //SysCtl_setAuxClock(DEVICE_AUXSETCLOCK_CFG_USB);
    //
     // Initialize PIE and clear PIE registers. Disables CPU interrupts.
     //
     Interrupt_initModule();

     //
     // Initialize the PIE vector table with pointers to the shell Interrupt
     // Service Routines (ISR).
     //
     Interrupt_initVectorTable();

    Board_init();

    C2000Ware_libraries_init();


    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

#ifdef DEBUG
    //
    // Configure the SCI for debug output.
    //
    ConfigureSCI();
#endif

    USBGPIOEnable();
    //Interrupt_register(INT_USBA, INT_myUSB0_ISR);

    //
    // Initialize the USB stack for device mode.
    //
    //USBStackModeSet(0, eUSBModeForceDevice, 0);
    GPIO_setDirectionMode(0, GPIO_DIR_MODE_OUT);

    //
    // Register the interrupt handler, returning an error if an error occurs.
    //
    Interrupt_register(INT_TIMER0, &CPUTimerIntHandler);

    CPUTimerInit();

    CPUTimer_setPeriod(CPUTIMER0_BASE,
                      (SysCtl_getClock(DEVICE_OSCSRC_FREQ) / TICKS_PER_SECOND));

    //
    // Enable the CPU Timer interrupt.
    //
    CPUTimer_enableInterrupt(CPUTIMER0_BASE);
    Interrupt_enable(INT_TIMER0);

    CPUTimer_startTimer(CPUTIMER0_BASE);

    //
    // Show the application name on the display and SCI output.
    //
    DEBUG_PRINT("\nC2000 F2837xS Series USB HID Mouse device example\n");
    DEBUG_PRINT("---------------------------------\n\n");

    //
    // Pass the USB library our device information, initialize the USB
    // controller and connect the device to the bus.
    //
    //USBDHIDMouseInit(0, (tUSBDHIDMouseDevice *)&g_sMouseDevice);

    Interrupt_enableMaster();

    //
    // Drop into the main loop.
    //
    while(1)
    {
        //
        // Tell the user what we are doing.
        //
        DEBUG_PRINT("Waiting for host...\n");

        //
        // Wait for USB configuration to complete.
        //
        while(!g_bConnected)
        {
        }

        //
        // Update the status.
        //
        DEBUG_PRINT("Host connected...\n");

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

//******************************************************************************
//
//! Device interrupt service routine wrapper to make ISR compatible with
//! C2000 PIE controller.
//
//******************************************************************************
__interrupt void
INT_myUSB0_ISR(void)
{
    USB0DeviceIntHandler();
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP9);
}

//
// End of file
//
