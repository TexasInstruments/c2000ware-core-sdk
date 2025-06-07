//###########################################################################
//
// FILE:   usb_dev_keyboard.c
//
// TITLE:  USB Keyboard Device example. 
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
//! <h1>USB HID Keyboard Device (usb_dev_keyboard)</h1>
//!
//! This example application turns the evaluation board into a USB keyboard
//! supporting the Human Interface Device class.  When the push button is
//! pressed, a sequence of key presses is simulated to type a string.  Care
//! should be taken to ensure that the active window can safely receive the
//! text; enter is not pressed at any point so no actions are attempted by the
//! host if a terminal window is used (for example).  The status LED is used to
//! indicate the current Caps Lock state and is updated in response to any
//! other keyboard attached to the same USB host system.
//!
//! Because no USB evaluation kits currently exist the GPIOs for the push
//! button and LED are NOT implemented.  The application can be tested
//! as is by manually modifying the ulButton variable with a debugger or
//! the software can easily be modified by filling in appropriate code
//! snippets in this file where you find //TODO: comments.
//!
//! The device implemented by this application also supports USB remote wakeup
//! allowing it to request the host to reactivate a suspended bus.  If the bus
//! is suspended (as indicated on the application display), pressing the
//! push button will request a remote wakeup assuming the host has not
//! specifically disabled such requests.
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
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/interrupt.h"
#include "driverlib/rom.h"
#include "driverlib/usb.h"
#include "inc/hw_usb.h"
#include "include/usblib.h"
#include "driverlib/usb_hal.h"
#include "include/usbhid.h"
#include "include/device/usbdevice.h"
#include "include/device/usbdhid.h"
#include "include/device/usbdhidkeyb.h"
#include "utils/uartstdio.h"
#include "usb_keyb_structs.h"

//
// The system tick timer period.
//
#define SYSTICKS_PER_SECOND     100

//
// A mapping from the ASCII value received from the UART to the corresponding
// USB HID usage code.
//
static const char g_ppcKeyUsageCodes[][2] =
{
    { 0, HID_KEYB_USAGE_SPACE },                       //   0x20
    { HID_KEYB_LEFT_SHIFT, HID_KEYB_USAGE_1 },         // ! 0x21
    { HID_KEYB_LEFT_SHIFT, HID_KEYB_USAGE_FQUOTE },    // " 0x22
    { HID_KEYB_LEFT_SHIFT, HID_KEYB_USAGE_3 },         // # 0x23
    { HID_KEYB_LEFT_SHIFT, HID_KEYB_USAGE_4 },         // $ 0x24
    { HID_KEYB_LEFT_SHIFT, HID_KEYB_USAGE_5 },         // % 0x25
    { HID_KEYB_LEFT_SHIFT, HID_KEYB_USAGE_7 },         // & 0x26
    { 0, HID_KEYB_USAGE_FQUOTE },                      // ' 0x27
    { HID_KEYB_LEFT_SHIFT, HID_KEYB_USAGE_9 },         // ( 0x28
    { HID_KEYB_LEFT_SHIFT, HID_KEYB_USAGE_0 },         // ) 0x29
    { HID_KEYB_LEFT_SHIFT, HID_KEYB_USAGE_8 },         // * 0x2a
    { HID_KEYB_LEFT_SHIFT, HID_KEYB_USAGE_EQUAL },     // + 0x2b
    { 0, HID_KEYB_USAGE_COMMA },                       // , 0x2c
    { 0, HID_KEYB_USAGE_MINUS },                       // - 0x2d
    { 0, HID_KEYB_USAGE_PERIOD },                      // . 0x2e
    { 0, HID_KEYB_USAGE_FSLASH },                      // / 0x2f
    { 0, HID_KEYB_USAGE_0 },                           // 0 0x30
    { 0, HID_KEYB_USAGE_1 },                           // 1 0x31
    { 0, HID_KEYB_USAGE_2 },                           // 2 0x32
    { 0, HID_KEYB_USAGE_3 },                           // 3 0x33
    { 0, HID_KEYB_USAGE_4 },                           // 4 0x34
    { 0, HID_KEYB_USAGE_5 },                           // 5 0x35
    { 0, HID_KEYB_USAGE_6 },                           // 6 0x36
    { 0, HID_KEYB_USAGE_7 },                           // 7 0x37
    { 0, HID_KEYB_USAGE_8 },                           // 8 0x38
    { 0, HID_KEYB_USAGE_9 },                           // 9 0x39
    { HID_KEYB_LEFT_SHIFT, HID_KEYB_USAGE_SEMICOLON }, // : 0x3a
    { 0, HID_KEYB_USAGE_SEMICOLON },                   // ; 0x3b
    { HID_KEYB_LEFT_SHIFT, HID_KEYB_USAGE_COMMA },     // < 0x3c
    { 0, HID_KEYB_USAGE_EQUAL },                       // = 0x3d
    { HID_KEYB_LEFT_SHIFT, HID_KEYB_USAGE_PERIOD },    // > 0x3e
    { HID_KEYB_LEFT_SHIFT, HID_KEYB_USAGE_FSLASH },    // ? 0x3f
    { HID_KEYB_LEFT_SHIFT, HID_KEYB_USAGE_2 },         // @ 0x40
    { HID_KEYB_LEFT_SHIFT, HID_KEYB_USAGE_A },         // A 0x41
    { HID_KEYB_LEFT_SHIFT, HID_KEYB_USAGE_B },         // B 0x42
    { HID_KEYB_LEFT_SHIFT, HID_KEYB_USAGE_C },         // C 0x43
    { HID_KEYB_LEFT_SHIFT, HID_KEYB_USAGE_D },         // D 0x44
    { HID_KEYB_LEFT_SHIFT, HID_KEYB_USAGE_E },         // E 0x45
    { HID_KEYB_LEFT_SHIFT, HID_KEYB_USAGE_F },         // F 0x46
    { HID_KEYB_LEFT_SHIFT, HID_KEYB_USAGE_G },         // G 0x47
    { HID_KEYB_LEFT_SHIFT, HID_KEYB_USAGE_H },         // H 0x48
    { HID_KEYB_LEFT_SHIFT, HID_KEYB_USAGE_I },         // I 0x49
    { HID_KEYB_LEFT_SHIFT, HID_KEYB_USAGE_J },         // J 0x4a
    { HID_KEYB_LEFT_SHIFT, HID_KEYB_USAGE_K },         // K 0x4b
    { HID_KEYB_LEFT_SHIFT, HID_KEYB_USAGE_L },         // L 0x4c
    { HID_KEYB_LEFT_SHIFT, HID_KEYB_USAGE_M },         // M 0x4d
    { HID_KEYB_LEFT_SHIFT, HID_KEYB_USAGE_N },         // N 0x4e
    { HID_KEYB_LEFT_SHIFT, HID_KEYB_USAGE_O },         // O 0x4f
    { HID_KEYB_LEFT_SHIFT, HID_KEYB_USAGE_P },         // P 0x50
    { HID_KEYB_LEFT_SHIFT, HID_KEYB_USAGE_Q },         // Q 0x51
    { HID_KEYB_LEFT_SHIFT, HID_KEYB_USAGE_R },         // R 0x52
    { HID_KEYB_LEFT_SHIFT, HID_KEYB_USAGE_S },         // S 0x53
    { HID_KEYB_LEFT_SHIFT, HID_KEYB_USAGE_T },         // T 0x54
    { HID_KEYB_LEFT_SHIFT, HID_KEYB_USAGE_U },         // U 0x55
    { HID_KEYB_LEFT_SHIFT, HID_KEYB_USAGE_V },         // V 0x56
    { HID_KEYB_LEFT_SHIFT, HID_KEYB_USAGE_W },         // W 0x57
    { HID_KEYB_LEFT_SHIFT, HID_KEYB_USAGE_X },         // X 0x58
    { HID_KEYB_LEFT_SHIFT, HID_KEYB_USAGE_Y },         // Y 0x59
    { HID_KEYB_LEFT_SHIFT, HID_KEYB_USAGE_Z },         // Z 0x5a
    { 0, HID_KEYB_USAGE_LBRACKET },                    // [ 0x5b
    { 0, HID_KEYB_USAGE_BSLASH },                      // \ 0x5c
    { 0, HID_KEYB_USAGE_RBRACKET },                    // ] 0x5d
    { HID_KEYB_LEFT_SHIFT, HID_KEYB_USAGE_6 },         // ^ 0x5e
    { HID_KEYB_LEFT_SHIFT, HID_KEYB_USAGE_MINUS },     // _ 0x5f
    { 0, HID_KEYB_USAGE_BQUOTE },                      // ` 0x60
    { 0, HID_KEYB_USAGE_A },                           // a 0x61
    { 0, HID_KEYB_USAGE_B },                           // b 0x62
    { 0, HID_KEYB_USAGE_C },                           // c 0x63
    { 0, HID_KEYB_USAGE_D },                           // d 0x64
    { 0, HID_KEYB_USAGE_E },                           // e 0x65
    { 0, HID_KEYB_USAGE_F },                           // f 0x66
    { 0, HID_KEYB_USAGE_G },                           // g 0x67
    { 0, HID_KEYB_USAGE_H },                           // h 0x68
    { 0, HID_KEYB_USAGE_I },                           // i 0x69
    { 0, HID_KEYB_USAGE_J },                           // j 0x6a
    { 0, HID_KEYB_USAGE_K },                           // k 0x6b
    { 0, HID_KEYB_USAGE_L },                           // l 0x6c
    { 0, HID_KEYB_USAGE_M },                           // m 0x6d
    { 0, HID_KEYB_USAGE_N },                           // n 0x6e
    { 0, HID_KEYB_USAGE_O },                           // o 0x6f
    { 0, HID_KEYB_USAGE_P },                           // p 0x70
    { 0, HID_KEYB_USAGE_Q },                           // q 0x71
    { 0, HID_KEYB_USAGE_R },                           // r 0x72
    { 0, HID_KEYB_USAGE_S },                           // s 0x73
    { 0, HID_KEYB_USAGE_T },                           // t 0x74
    { 0, HID_KEYB_USAGE_U },                           // u 0x75
    { 0, HID_KEYB_USAGE_V },                           // v 0x76
    { 0, HID_KEYB_USAGE_W },                           // w 0x77
    { 0, HID_KEYB_USAGE_X },                           // x 0x78
    { 0, HID_KEYB_USAGE_Y },                           // y 0x79
    { 0, HID_KEYB_USAGE_Z },                           // z 0x7a
    { HID_KEYB_LEFT_SHIFT, HID_KEYB_USAGE_LBRACKET },  // { 0x7b
    { HID_KEYB_LEFT_SHIFT, HID_KEYB_USAGE_BSLASH },    // | 0x7c
    { HID_KEYB_LEFT_SHIFT, HID_KEYB_USAGE_RBRACKET },  // } 0x7d
    { HID_KEYB_LEFT_SHIFT, HID_KEYB_USAGE_BQUOTE },    // ~ 0x7e
};

//
// This global indicates whether or not we are connected to a USB host.
//
volatile tBoolean g_bConnected = false;

//
// This global indicates whether or not the USB bus is currently in the suspend
// state.
//
volatile tBoolean g_bSuspended = false;

//
// Global system tick counter holds elapsed time since the application started
// expressed in 100ths of a second.
//
volatile unsigned long g_ulSysTickCount;

//
// The number of system ticks to wait for each USB packet to be sent before
// we assume the host has disconnected.  The value 50 equates to half a second.
//
#define MAX_SEND_DELAY          50

//
// This global is set to true if the host sends a request to set or clear
// any keyboard LED.
//
volatile tBoolean g_bDisplayUpdateRequired;

//
// This enumeration holds the various states that the keyboard can be in during
// normal operation.
//
volatile enum
{
    //
    // Unconfigured.
    //
    STATE_UNCONFIGURED,

    //
    // No keys to send and not waiting on data.
    //
    STATE_IDLE,

    //
    // Waiting on data to be sent out.
    //
    STATE_SENDING
}
g_eKeyboardState = STATE_UNCONFIGURED;

//
// __error__ - The error routine that is called if the driver library 
// encounters an error.
//
#ifdef DEBUG
void
__error__(char *pcFilename, unsigned long ulLine)
{
    
}
#endif

//
// KeyboardHandler- Handles asynchronous events from the HID keyboard driver.
//
// \param pvCBData is the event callback pointer provided during
// USBDHIDKeyboardInit().  This is a pointer to our keyboard device structure
// (&g_sKeyboardDevice).
// \param ulEvent identifies the event we are being called back for.
// \param ulMsgData is an event-specific value.
// \param pvMsgData is an event-specific pointer.
//
// This function is called by the HID keyboard driver to inform the application
// of particular asynchronous events related to operation of the keyboard HID
// device.
//
// \return Returns 0 in all cases.
//
unsigned long
KeyboardHandler(void *pvCBData, unsigned long ulEvent, unsigned long ulMsgData,
                void *pvMsgData)
{
    switch (ulEvent)
    {
        //
        // The host has connected to us and configured the device.
        //
        case USB_EVENT_CONNECTED:
        {
            g_bConnected = true;
            g_bSuspended = false;
            break;
        }

        //
        // The host has disconnected from us.
        //
        case USB_EVENT_DISCONNECTED:
        {
            g_bConnected = false;
            break;
        }

        //
        // We receive this event every time the host acknowledges transmission
        // of a report. It is used here purely as a way of determining whether
        // the host is still talking to us or not.
        //
        case USB_EVENT_TX_COMPLETE:
        {
            //
            // Enter the idle state since we finished sending something.
            //
            g_eKeyboardState = STATE_IDLE;
            break;
        }

        //
        // This event indicates that the host has suspended the USB bus.
        //
        case USB_EVENT_SUSPEND:
        {
            g_bSuspended = true;
            break;
        }

        //
        // This event signals that the host has resumed signalling on the bus.
        //
        case USB_EVENT_RESUME:
        {
            g_bSuspended = false;
            break;
        }

        //
        // This event indicates that the host has sent us an Output or
        // Feature report and that the report is now in the buffer we provided
        // on the previous USBD_HID_EVENT_GET_REPORT_BUFFER callback.
        //
        case USBD_HID_KEYB_EVENT_SET_LEDS:
        {
            //
            // Set the LED to match the current state of the caps lock LED.
            //
            //TODO: Write caps lock state to LED pin	
            //      GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0,
            //      (ulMsgData & HID_KEYB_CAPS_LOCK) ? GPIO_PIN_0 : 0);
            break;
        }

        //
        // We ignore all other events.
        //
        default:
        {
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
        // Is the keyboard is idle, return immediately.
        //
        if(g_eKeyboardState == STATE_IDLE)
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
// SendString - Sends a string of characters via the USB HID keyboard interface
//
void
SendString(char *pcStr)
{
    unsigned long ulChar;

    //
    // Loop while there are more characters in the string.
    //
    while(*pcStr)
    {
        //
        // Get the next character from the string.
        //
        ulChar = *pcStr++;

        //
        // Skip this character if it is a non-printable character.
        //
        if((ulChar < ' ') || (ulChar > '~'))
        {
            continue;
        }

        //
        // Convert the character into an index into the keyboard usage code
        // table.
        //
        ulChar -= ' ';

        //
        // Send the key press message.
        //
        g_eKeyboardState = STATE_SENDING;
        if(USBDHIDKeyboardKeyStateChange((void *)&g_sKeyboardDevice,
                                         g_ppcKeyUsageCodes[ulChar][0],
                                         g_ppcKeyUsageCodes[ulChar][1],
                                         true) != KEYB_SUCCESS)
        {
            return;
        }

        //
        // Wait until the key press message has been sent.
        //
        if(!WaitForSendIdle(MAX_SEND_DELAY))
        {
            g_bConnected = 0;
            return;
        }

        //
        // Send the key release message.
        //
        g_eKeyboardState = STATE_SENDING;
        if(USBDHIDKeyboardKeyStateChange((void *)&g_sKeyboardDevice,
                                         0, g_ppcKeyUsageCodes[ulChar][1],
                                         false) != KEYB_SUCCESS)
        {
            return;
        }

        //
        // Wait until the key release message has been sent.
        //
        if(!WaitForSendIdle(MAX_SEND_DELAY))
        {
            g_bConnected = 0;
            return;
        }
    }
}

//
// SysTickIntHandler - This is the interrupt handler for the SysTick interrupt.
// It is used to update our local tick count which, in turn, is used to check 
// for transmit timeouts.
//
__interrupt void
SysTickIntHandler(void)
{
    g_ulSysTickCount++;
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
// This is the main loop that runs the application.
//
int
main(void)
{
	//
    // Section .ebss was initialized to 0x0000 in
	// F2806x_CodeStartBranch_ebss_init.asm. This was to ensure that all global
	// variables of the usblib are initialized to 0x0000 on the F2806x.
	//
    unsigned long ulButton, ulPrevious, ulLastTickCount;
    tBoolean bLastSuspend;

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
    UARTprintf("\033[2JKeyboard device application\n");

    //
    // Enable the GPIO that is used for the on-board push button.
    //
    //TODO: Configure GPIO for push button

    //
    // Enable the GPIO that is used for the on-board LED.
    //
    //TODO: Configure GPIO for LED

    //
    // Not configured initially.
    //
    g_bConnected = false;
    g_bSuspended = false;
    bLastSuspend = false;


    //
    // Pass our device information to the USB HID device class driver,
    // initialize the USB
    // controller and connect the device to the bus.
    //
    USBDHIDKeyboardInit(0, &g_sKeyboardDevice);

    //
    // Set the system tick to fire 100 times per second.
    //
    SysTickPeriodSet(SysCtlClockGet(SYSTEM_CLOCK_SPEED) / SYSTICKS_PER_SECOND);
    SysTickIntEnable();
    SysTickEnable();

    //
    // Register interrupt handlers
    //
    IntRegister(INT_TINT0, SysTickIntHandler);
    USBIntRegister(USB0_BASE, f28x_USB0DeviceIntHandler);

    IntMasterEnable();

    //
    // The main loop starts here.  We begin by waiting for a host connection
    // then drop into the main keyboard handling section.  If the host
    // disconnects, we return to the top and wait for a new connection.
    //
    ulPrevious = 1;
    while(1)
    {
        //
        // Tell the user what we are doing and provide some basic instructions.
        //
        UARTprintf("Waiting for host...\n");

        //
        // Wait for USB configuration to complete. Even in this state, we look
        // for key presses and, if any occur while the bus is suspended, we
        // issue a remote wakeup request.
        //
        while(!g_bConnected)
        {
            //
            // Remember the current time.
            //
            ulLastTickCount = g_ulSysTickCount;

            //
            // Has the suspend state changed since last time we checked?
            //
            if(bLastSuspend != g_bSuspended)
            {
                //
                // Yes - the state changed so update the display.
                //
                bLastSuspend = g_bSuspended;
                UARTprintf(bLastSuspend ? "Bus suspended...\n" :
                           "Waiting for host...\n");
            }

            //
            // See if the button was just pressed and the device is suspended.
            //
            //TODO: Read GPIO that was select for the pushbutton
            //            ulButton = GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_4);
            if((ulButton == 0) && (ulPrevious != 0) && g_bSuspended)
            {
                //
                // Request a remote wakeup.
                //
                USBDHIDKeyboardRemoteWakeupRequest((void *)&g_sKeyboardDevice);
            }
            ulPrevious = ulButton;

            //
            // Wait for at least 1 system tick to have gone by before we poll
            // the buttons again.
            //
            while(g_ulSysTickCount == ulLastTickCount)
            {
                
            }
        }

        //
        // Update the status.
        //
        UARTprintf("Host connected...\n");

        //
        // Enter the idle state.
        //
        g_eKeyboardState = STATE_IDLE;

        //
        // Assume that the bus is not currently suspended if we have just been
        // configured.
        //
        bLastSuspend = false;

        //
        // Keep transfering characters from the UART to the USB host for as
        // long as we are connected to the host.
        //
        while(g_bConnected)
        {
            //
            // Remember the current time.
            //
            ulLastTickCount = g_ulSysTickCount;

            //
            // Has the suspend state changed since last time we checked?
            //
            if(bLastSuspend != g_bSuspended)
            {
                //
                // Yes - the state changed so update the display.
                //
                bLastSuspend = g_bSuspended;
                UARTprintf(bLastSuspend ? "Bus suspended...\n" :
                           "Host connected...\n");
            }

            //
            // See if the button was just pressed.
            //
            //TODO: Read GPIO that was select for the pushbutton
            //            ulButton = GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_4);
            if((ulButton == 0) && (ulPrevious != 0))
            {
                //
                // If the bus is suspended then resume it.  Otherwise, type
                // some "random" characters.
                //
                if(g_bSuspended)
                {
                    USBDHIDKeyboardRemoteWakeupRequest(
                        (void *)&g_sKeyboardDevice);
                }
                else
                {
                    SendString("C2000...Are you in Control?");
                }
            }
            ulPrevious = ulButton;

            //
            // Wait for at least 1 system tick to have gone by before we poll
            // the buttons again.
            //
            while(g_ulSysTickCount == ulLastTickCount)
            {
                
            }
        }
    }
}

//
// End of File
//

