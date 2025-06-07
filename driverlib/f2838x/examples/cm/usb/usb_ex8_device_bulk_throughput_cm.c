//##############################################################################
//
// FILE:   usb_ex8_dev_bulk_throughput.c
//
// TITLE:  Main routines for the generic bulk device example.
//
//! \addtogroup driver_example_cm_list
//! <h1>USB Throughput Bulk Device Example (usb_ex9_throughput_dev_bulk)</h1>
//!
//! This example provides a generic USB device offering simple bulk data
//! transfer to and from the host. The device uses a vendor-specific class ID
//! and supports a single bulk IN Endpoint and a single bulk OUT Endpoint.
//! Data received from the host is assumed to be ASCII text and it is
//! echoed back with the case of all alphabetic characters swapped.
//!
//! UART0, connected to the FTDI virtual COM port and running at 115200,
//! 8-N-1, is used to display messages from this application.
//!
//! A Windows INF file for the device is provided under the windows drivers
//! directory.  This INF contains information required to install the WinUSB
//! subsystem on WindowsXP, Windows 7 and Windows 10. WinUSB is a Windows
//! subsystem allowing user mode applications to access the USB device without
//! the need for a vendor-specific kernel mode driver.
//!
//! A sample Windows command-line application, usb_throughput_bulk_example,
//! illustrating how to connect to and communicate with the bulk device is
//! also provided. Project files are included to allow the examples to be
//! built using Microsoft VisualStudio.  Source code for this application can
//! be found in directory ~/utilities/tools/usb_throughput_bulk_example/Release.
//!
//
//##############################################################################
//
//
// 
// C2000Ware v5.05.00.00
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

//
// Included Files
//
#include <string.h>
#include "cm.h"
#include "usblib.h"
#include "device/usbdevice.h"
#include "device/usbdbulk.h"
#include "uartstdio.h"
#include "usb_hal.h"
#include "usb_ex8_device_bulk_structs.h"

//******************************************************************************
//
// The system tick rate expressed both as ticks per second and a millisecond
// period.
//
//******************************************************************************
#define SYSTICKS_PER_SECOND     1000

//******************************************************************************
//
// The global system tick counter.
//
//******************************************************************************
volatile uint32_t g_ui32SysTickCount = 0;

//******************************************************************************
//
// Variables tracking transmit and receive counts.
//
//******************************************************************************
volatile uint32_t g_ui32TxCount = 0;
volatile uint32_t g_ui32RxCount = 0;
uint8_t buffer[256];
uint8_t g_bConnected = 0;
volatile uint32_t globalCounter = 0UL;
volatile uint32_t idleCycles = 0UL;

tUSBMode g_eCurrentUSBMode;   // The current USB operating mode - Host, Device
                              // or unknown.

//******************************************************************************
//
// Global flag indicating that a USB configuration has been set.
//
//******************************************************************************
static volatile bool g_bUSBConfigured = false;

//******************************************************************************
//
// Interrupt handler for the system tick counter.
//
//******************************************************************************
__interrupt void
SysTickIntHandler(void)
{

    idleCycles = globalCounter * 100U;
    globalCounter = 0UL;

    //
    // Update our system tick counter.
    //
    g_ui32SysTickCount++;
}

//******************************************************************************
// Receive new data and echo it back to the host.
//
// \param psDevice points to the instance data for the device whose data is to
// be processed.
// \param pcData points to the newly received data in the USB receive buffer.
// \param ui32NumBytes is the number of bytes of data available to be processed.
//
// This function is called whenever there is data available from the host.  The
// data is read byte-by-byte, the case of any alphabetical characters is
// swapped, and then it is written back out to be transmitted back to the host.
//
// \return Returns the number of bytes of data processed.
//******************************************************************************
static uint32_t
EchoNewDataToHost(tUSBDBulkDevice *psDevice, uint8_t *pcData,
                  uint32_t ui32NumBytes)
{
    uint32_t ui32Loop, ui32Space, ui32Count;
    uint32_t ui32ReadIndex;
    uint32_t ui32WriteIndex;
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
    ui32Space = USBBufferSpaceAvailable(&g_sTxBuffer);

    //
    // How many characters can be processed this time round?
    //
    ui32Loop = (ui32Space < ui32NumBytes) ? ui32Space : ui32NumBytes;
    ui32Count = ui32Loop;

    //
    // Update our receive counter.
    //
    g_ui32RxCount += ui32NumBytes;

    //
    // Dump a debug message.
    //
    UARTprintf("Received %d bytes\n", ui32NumBytes);

    //
    // Set up to process the characters by directly accessing the USB buffers.
    //
    ui32ReadIndex = (uint32_t)(pcData - g_pui8USBRxBuffer);
    ui32WriteIndex = sTxRing.ui32WriteIndex;

    //
    // Copy from the receive buffer to the transmit buffer converting character
    // case on the way.
    //
    while(ui32Loop--)
    {
        //
        // Is this a lower case character?
        //
        if((g_pui8USBRxBuffer[ui32ReadIndex] >= 'a') &&
           (g_pui8USBRxBuffer[ui32ReadIndex] <= 'z'))
        {
            //
            // Convert to upper case and write to the transmit buffer.
            //
            g_pui8USBTxBuffer[ui32WriteIndex] =
                                 (g_pui8USBRxBuffer[ui32ReadIndex] - 'a') + 'A';
        }
        else
        {
            //
            // Is this an upper case character?
            //
            if((g_pui8USBRxBuffer[ui32ReadIndex] >= 'A') &&
               (g_pui8USBRxBuffer[ui32ReadIndex] <= 'Z'))
            {
                //
                // Convert to lower case and write to the transmit buffer.
                //
                g_pui8USBTxBuffer[ui32WriteIndex] =
                                 (g_pui8USBRxBuffer[ui32ReadIndex] - 'Z') + 'z';
            }
            else
            {
                //
                // Copy the received character to the transmit buffer.
                //
                g_pui8USBTxBuffer[ui32WriteIndex] =
                                               g_pui8USBRxBuffer[ui32ReadIndex];
            }
        }

        //
        // Move to the next character taking care to adjust the pointer for
        // the buffer wrap if necessary.
        //
        ui32WriteIndex++;
        ui32WriteIndex = ((ui32WriteIndex == BULK_BUFFER_SIZE) ? 0 :
                          ui32WriteIndex);
        ui32ReadIndex++;
        ui32ReadIndex = (ui32ReadIndex == BULK_BUFFER_SIZE) ? 0 : ui32ReadIndex;
    }

    //
    // The data has been processed in place so now send the processed data back
    // to the host.
    //
    USBBufferDataWritten(&g_sTxBuffer, ui32Count);

    //
    // Return the number of bytes processed to allow the bulk device driver to
    // update its read pointer appropriately.
    //
    return(ui32Count);
}

//*****************************************************************************
//
// Handles bulk driver notifications related to the transmit channel (data to
// the USB host).
//
// \param pvCBData is the client-supplied callback pointer for this channel.
// \param ui32Event identifies the event that has been sent.
// \param ui32MsgValue is an event-specific value.
// \param pvMsgData is an event-specific pointer.
//
// This function is called by the bulk driver to notify us of any events
// related to operation of the transmit data channel (the IN channel carrying
// data to the USB host).
//
// \return The return value is event-specific.
//
//******************************************************************************
uint32_t
TxHandler(void *pvCBData, uint32_t ui32Event, uint32_t ui32MsgValue,
          void *pvMsgData)
{
    //
    // Update the transmit counter.
    // Write the USB Bulk Data.
    //
    if(ui32Event == USB_EVENT_TX_COMPLETE)
    {
        g_ui32TxCount += ui32MsgValue;

        uint32_t ui32Space = USBDBulkTxPacketAvailable(&g_sBulkDevice);
        if(ui32Space)
        {
            USBDBulkPacketWrite(&g_sBulkDevice, buffer, ui32Space, true);
        }
    }

    return(0);
}

//******************************************************************************
//
// Handles bulk driver notifications related to the receive channel (data from
// the USB host).
//
// \param pvCBData is the client-supplied callback pointer for this channel.
// \param ui32Event identifies the event that has been sent.
// \param ui32MsgValue is an event-specific value.
// \param pvMsgData is an event-specific pointer.
//
// This function is called by the bulk driver to notify us of any events
// related to operation of the receive data channel (the OUT channel carrying
// data from the USB host).
//
// \return The return value is event-specific.
//
//******************************************************************************
uint32_t
RxHandler(void *pvCBData, uint32_t ui32Event, uint32_t ui32MsgValue,
          void *pvMsgData)
{
    //
    // Which event was sent?
    //
    switch(ui32Event)
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

            g_bConnected = true;

            break;
        }

        //
        // The host has disconnected.
        //
        case USB_EVENT_DISCONNECTED:
        {
            g_bUSBConfigured = false;
            UARTprintf("Host disconnected.\n");
            g_bConnected = false;
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
            return(EchoNewDataToHost(psDevice, pvMsgData, ui32MsgValue));
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

//******************************************************************************
// ModeCallback - USB Mode callback
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
//******************************************************************************
void
ModeCallback(uint32_t ui32Index, tUSBMode eMode)
{
    //
    // Save the new mode.
    //
    g_eCurrentUSBMode = eMode;
}


//******************************************************************************
//
// This is the main application entry function.
//
//******************************************************************************
int
main(void)
{
    uint16_t index;
	uint32_t loopCount;
    volatile uint16_t firstPacket;
    unsigned long ui32Space;
    firstPacket = 1;

    for(index = 0; index < 256; index++)
    {
        buffer[index] = index;
    }

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
    // Not configured initially.
    //
    g_bUSBConfigured = false;

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
    Interrupt_registerHandler(FAULT_SYSTICK, &SysTickIntHandler);

    //
    // Show the application name on the display and UART output.
    //
    UARTprintf("\nC2000 F2838x Series USB Throughput bulk device example\n");
    UARTprintf("---------------------------------\n\n");

    //
    // Initialize the transmit and receive buffers.
    //
    USBBufferInit(&g_sTxBuffer);
    USBBufferInit(&g_sRxBuffer);

    //
    // Set the USB stack mode to Device mode with VBUS monitoring.
    //
    USBStackModeSet(0, eUSBModeForceDevice, ModeCallback);

    //
    // Pass our device information to the USB library and place the device
    // on the bus.
    //
    USBDBulkInit(0, &g_sBulkDevice);

    //
    // Enable interrupts now that the application is ready to start.
    //
    Interrupt_enableInProcessor();

    //
    // Main application loop.
    //
    while(firstPacket)
    {
        //
        // Nothing to do...everything happens in the interrupt context.
        //
        if(g_bConnected)
        {
            //
            // How much space is there in the transmit buffer?
            //
            if(firstPacket)
            {
                ui32Space = USBDBulkTxPacketAvailable(&g_sBulkDevice);

                if(ui32Space)
                {
                    USBDBulkPacketWrite(&g_sBulkDevice, buffer, ui32Space,
                                        true);
                }
                firstPacket = 0;
            }
        }
    }

    //
    // This is where USB interrupts will be taken.
    // Set up CPUTimer for 1ms with interrupt.
    // Count Number of cycles per loop iteration.
    // In CPUTimer interrupt multiply cycle count by counter to find Number
    // cycles idle in 1ms.
    //
    while(1)
    {
        
		for(loopCount = 0; loopCount < 50; loopCount++)
		{
			__asm(" NOP");
		}

        //
        // Loop iteration should be 100 cycles
        //
        globalCounter++;

		for(loopCount = 0; loopCount < 40; loopCount++)
		{
			__asm(" NOP");
		}
    }
}

//
// End of file
//
