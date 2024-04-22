//###########################################################################
//
// FILE:    usb_dev_bulk.c
//
// TITLE:   F2806x USB Bulk Device Example.
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
//! <h1>USB Generic Bulk Device (usb_dev_bulk)</h1>
//!
//! This example provides a generic USB device offering simple bulk data
//! transfer to and from the host.  The device uses a vendor-specific class ID
//! and supports a single bulk IN endpoint and a single bulk OUT endpoint.
//! Data received from the host is assumed to be ASCII text and it is
//! echoed back with the case of all alphabetic characters swapped.
//!
//! UART0, connected to the FTDI virtual COM port and running at 115,200,
//! 8-N-1, is used to display messages from this application.
//!
//! A Windows INF file for the device is provided on the installation CD.  This
//! INF contains information required to install the WinUSB subsystem on
//! WindowsXP and Vista PCs.  WinUSB is a Windows subsystem allowing user mode
//! applications to access the USB device without the need for a
//! vendor-specific kernel mode driver.
//!
//! A sample Windows command-line application, usb_bulk_example, illustrating
//! how to connect to and communicate with the bulk device is also provided.
//! Project files are included to allow the examples to be built using Microsoft
//! VisualStudio.  Source code for this application can be found in directory
//! MWare/tools/usb_bulk_example.
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
//###########################################################################

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
#include "driverlib/rom.h"
#include "include/usblib.h"
#include "driverlib/usb.h"
#include "driverlib/usb_hal.h"
#include "inc/hw_usb.h"
#include "include/usb_ids.h"
#include "include/device/usbdevice.h"
#include "include/device/usbdbulk.h"
#include "utils/uartstdio.h"
#include "usb_bulk_structs.h"

//
// The system tick rate expressed both as ticks per second and a millisecond
// period.
//
#define SYSTICKS_PER_SECOND     100
#define SYSTICK_PERIOD_MS       (1000 / SYSTICKS_PER_SECOND)

//
// The global system tick counter.
//
volatile uint32_t g_ulSysTickCount = 0;

//
// Variables tracking transmit and receive counts.
//
volatile uint32_t g_ulTxCount = 0;
volatile uint32_t g_ulRxCount = 0;

//
// Global flag indicating that a USB configuration has been set.
//
static volatile tBoolean g_bUSBConfigured = false;

//
// __error__ - The error routine that is called if the driver library 
// encounters an error.
//
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ulLine)
{
    
}
#endif

//
// SysTickIntHandler - Interrupt handler for the system tick counter.
//
__interrupt void
SysTickIntHandler(void)
{
    //
    // Update our system tick counter.
    //
    g_ulSysTickCount++;
    PieCtrlRegs.PIEACK.all |= 1;
}

//
// EchoNewDataToHost - Receive new data and echo it back to the host.
//
// \param psDevice points to the instance data for the device whose data is to
// be processed.
// \param pcData points to the newly received data in the USB receive buffer.
// \param ulNumBytes is the number of bytes of data available to be processed.
//
// This function is called whenever there is data available from the host.  The
// data is read byte-by-byte, the case of any alphabetical characters is
// swapped, and then it is written back out to be transmitted back to the host.
//
// \return Returns the number of bytes of data processed.
//
static uint32_t
EchoNewDataToHost(tUSBDBulkDevice *psDevice, uint8_t *pcData,
                  uint32_t ulNumBytes)
{
    uint32_t ulLoop, ulSpace, ulCount;
    uint32_t ulReadIndex;
    uint32_t ulWriteIndex;
    tUSBRingBufObject sTxRing;

    //
    // Get the current buffer information to allow us to write directly to the
    // transmit buffer (there is already have enough information from the
    // parameters to access the receive buffer directly).
    //
    USBBufferInfoGet(&g_sTxBuffer, &sTxRing);

    //
    // How much space is there in the transmit buffer?
    //
    ulSpace = USBBufferSpaceAvailable(&g_sTxBuffer);

    //
    // How many characters can be processed this time round?
    //
    ulLoop = (ulSpace < ulNumBytes) ? ulSpace : ulNumBytes;
    ulCount = ulLoop;

    //
    // Update our receive counter.
    //
    g_ulRxCount += ulNumBytes;

    //
    // Set up to process the characters by directly accessing the USB buffers.
    //
    ulReadIndex = (uint32_t)(pcData - g_pui8USBRxBuffer);
    ulWriteIndex = sTxRing.ui32WriteIndex;

    //
    // Copy from the receive buffer to the transmit buffer converting character
    // case on the way.
    //
    while(ulLoop--)
    {
        //
        // Is this a lower case character?
        //
        if((g_pui8USBRxBuffer[ulReadIndex] >= 'a') &&
                (g_pui8USBRxBuffer[ulReadIndex] <= 'z'))
        {
            //
            // Convert to upper case and write to the transmit buffer.
            //
            g_pui8USBTxBuffer[ulWriteIndex] =
                (g_pui8USBRxBuffer[ulReadIndex] - 'a') + 'A';
        }
        else
        {
            //
            // Is this an upper case character?
            //
            if((g_pui8USBRxBuffer[ulReadIndex] >= 'A') &&
                    (g_pui8USBRxBuffer[ulReadIndex] <= 'Z'))
            {
                //
                // Convert to lower case and write to the transmit buffer.
                //
                g_pui8USBTxBuffer[ulWriteIndex] =
                    (g_pui8USBRxBuffer[ulReadIndex] - 'Z') + 'z';
            }
            else
            {
                //
                // Copy the received character to the transmit buffer.
                //
                g_pui8USBTxBuffer[ulWriteIndex] = g_pui8USBRxBuffer[ulReadIndex];
            }
        }

        //
        // Move to the next character taking care to adjust the pointer for
        // the buffer wrap if necessary.
        //
        ulWriteIndex++;
        ulWriteIndex = (ulWriteIndex == BULK_BUFFER_SIZE) ? 0 : ulWriteIndex;
        ulReadIndex++;
        ulReadIndex = (ulReadIndex == BULK_BUFFER_SIZE) ? 0 : ulReadIndex;
    }

    //
    // The data has been processed in place so now send the processed data back
    // to the host.
    //
    USBBufferDataWritten(&g_sTxBuffer, ulCount);

    //
    // Return the number of bytes processed to allow the bulk device driver to
    // update its read pointer appropriately.
    //
    return(ulCount);
}

//
// TxHandler - Handles bulk driver notifications related to the transmit 
// channel (data to the USB host).
//
// \param pvCBData is the client-supplied callback pointer for this channel.
// \param ulEvent identifies the event that has been sent.
// \param ulMsgValue is an event-specific value.
// \param pvMsgData is an event-specific pointer.
//
// This function is called by the bulk driver to notify us of any events
// related to operation of the transmit data channel (the IN channel carrying
// data to the USB host).
//
// \return The return value is event-specific.
//
uint32_t
TxHandler(void *pvCBData, uint32_t ulEvent, uint32_t ulMsgValue,
          void *pvMsgData)
{
    //
    // No action is required in response to any transmit event in this example.
    // All that is done is to update the transmit counter.
    //
    if(ulEvent == USB_EVENT_TX_COMPLETE)
    {
        g_ulTxCount += ulMsgValue;
    }

    return(0);
}

//
// RxHandler - Handles bulk driver notifications related to the receive channel
// (data from the USB host).
//
// \param pvCBData is the client-supplied callback pointer for this channel.
// \param ulEvent identifies the event that has been sent.
// \param ulMsgValue is an event-specific value.
// \param pvMsgData is an event-specific pointer.
//
// This function is called by the bulk driver to notify us of any events
// related to operation of the receive data channel (the OUT channel carrying
// data from the USB host).
//
// \return The return value is event-specific.
//
uint32_t
RxHandler(void *pvCBData, uint32_t ulEvent, uint32_t ulMsgValue,
          void *pvMsgData)
{
    //
    // Which event was sent?
    //
    switch(ulEvent)
    {
        //
        // The host has connected.
        //
        case USB_EVENT_CONNECTED:
        {
            g_bUSBConfigured = true;
            UARTprintf("Host connected.\n");

            //
            // Flush our buffers.
            //
            USBBufferFlush(&g_sTxBuffer);
            USBBufferFlush(&g_sRxBuffer);

            break;
        }

        //
        // The host has disconnected.
        //
        case USB_EVENT_DISCONNECTED:
        {
            g_bUSBConfigured = false;
            UARTprintf("Host disconnected.\n");
            break;
        }

        //
        // A new packet has been received.
        //
        case USB_EVENT_RX_AVAILABLE:
        {
            tUSBDBulkDevice *psDevice;

            //
            // Get a pointer to our instance data from the callback data
            // parameter.
            //
            psDevice = (tUSBDBulkDevice *)pvCBData;

            //
            // Read the new packet and echo it back to the host.
            //
            return(EchoNewDataToHost(psDevice, pvMsgData, ulMsgValue));
        }

        //
        // Ignore SUSPEND and RESUME for now.
        //
        case USB_EVENT_SUSPEND:
        case USB_EVENT_RESUME:
        {
            break;
        }

        //
        // Ignore all other events and return 0.
        //
        default:
        {
            break;
        }
    }

    return(0);
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
// main - This is the main application entry function.
//
int
main(void)
{
	//
    // Section .ebss was initialized to 0x0000 in
	// F2806x_CodeStartBranch_ebss_init.asm. This was to ensure that all global
	// variables of the usblib are initialized to 0x0000 on the F2806x.
	//
    uint32_t ulTxCount;
    uint32_t ulRxCount;

    //
    // Set the clocking to run from the PLL
    //
    SysCtrlInit();

    //
    // Initialize interrupt controller and vector table
    //
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
    // Setup UART GPIOS and enable the UART.
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
    UARTprintf("\033[2JBulk device application\n");

    //
    // Not configured initially.
    //
    g_bUSBConfigured = false;

    //
    // Enable the system tick.
    //
    SysTickPeriodSet(SysCtlClockGet(SYSTEM_CLOCK_SPEED) /
                     SYSTICKS_PER_SECOND);
    SysTickIntEnable();
    SysTickEnable();

    //
    // Enable the GPIO peripheral used for USB, and configure the USB
    // pins.
    //
    USBGPIOEnable();

    //
    // Register Interrupt Handlers
    //
    IntRegister(INT_TINT0, SysTickIntHandler);
    USBIntRegister(USB0_BASE, f28x_USB0DeviceIntHandler);
    IntMasterEnable();

    //
    // Initialize the transmit and receive buffers.
    //
    USBBufferInit(&g_sTxBuffer);
    USBBufferInit(&g_sRxBuffer);

    //
    // Pass our device information to the USB library and place the device
    // on the bus.
    //
    USBDBulkInit(0, &g_sBulkDevice);

    //
    // Wait for initial configuration to complete.
    //
    UARTprintf("Waiting for host...\n");

    //
    // Clear our local byte counters.
    //
    ulRxCount = 0;
    ulTxCount = 0;

    //
    // Main application loop.
    //
    while(1)
    {
        //
        // See if any data has been transferred.
        //
        if((ulTxCount != g_ulTxCount) || (ulRxCount != g_ulRxCount))
        {
            //
            // Take a snapshot of the latest transmit and receive counts.
            //
            ulTxCount = g_ulTxCount;
            ulRxCount = g_ulRxCount;

            //
            // Update the display of bytes transferred.
            //
            UARTprintf("\rTx: %d  Rx: %d", ulTxCount, ulRxCount);
        }
    }
}

//
// End of File
//

