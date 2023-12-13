//##############################################################################
//
// FILE:   usb_ex1_dev_serial.c
//
// TITLE:   USB CDC serial example.
//
//! \addtogroup driver_example_list
//! <h1> USB CDC serial example </h1>
//!
//! This example application turns the evaluation kit into a virtual serial
//! port when connected to the USB host system.  The application supports the
//! USB Communication Device Class, Abstract Control Model to redirect SCIA
//! traffic to and from the USB host system.
//!
//! Connect USB cables from your PC to both the mini and microUSB connectors on
//! the controlCARD.Figure out what COM ports your controlCARD is enumerating
//! (typically done using Device Manager in Windows) and open a serial terminal
//! to each of with the settings 115200 Baud 8-N-1.  Characters typed in one
//! terminal should be echoed in the other and vice versa.
//!
//! A driver information (INF) file for use with Windows XP, Windows 7 and
//! Windows 10 can be found in the windows_drivers directory.
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
#include "board.h"
#include "c2000ware_libraries.h"
#include "usb_structs.h"
#include "usblib.h"
#include "usbcdc.h"
#include "usb_ids.h"
#include "device/usbdevice.h"
#include "device/usbdcdc.h"
#include "ustdlib.h"
#include "usb_hal.h"

void INT_myUSB0_ISR(void);
//******************************************************************************
//
// Configuration and tuning parameters.
//
//******************************************************************************

//******************************************************************************
//
// Variables tracking transmit and receive counts.
//
//******************************************************************************
volatile uint32_t g_ui32SCITxCount = 0;
volatile uint32_t g_ui32SCIRxCount = 0;
#ifdef DEBUG
uint32_t g_ui32SCIRxErrors = 0;
#endif

//******************************************************************************
//
// Default line coding settings for the redirected SCI.
//
//******************************************************************************
#define DEFAULT_BIT_RATE        115200
#define DEFAULT_SCI_CONFIG     (SCI_CONFIG_WLEN_8 | SCI_CONFIG_PAR_NONE | \
                                SCI_CONFIG_STOP_ONE)

//******************************************************************************
//
// Flag indicating whether or not we are currently sending a Break condition.
//
//******************************************************************************
static bool g_bSendingBreak = false;

//******************************************************************************
//
// Flags used to pass commands from interrupt context to the main loop.
//
//******************************************************************************
#define COMMAND_PACKET_RECEIVED 0x00000001
#define COMMAND_STATUS_UPDATE   0x00000002

volatile uint32_t g_ui32Flags = 0;
char *g_pcStatus;

//******************************************************************************
//
// Global flag indicating that a USB configuration has been set.
//
//******************************************************************************
static volatile bool g_bUSBConfigured = false;

//******************************************************************************
//
// Internal function prototypes.
//
//******************************************************************************
static void USBSCIPrimeTransmit(uint32_t ui32Base);
static void CheckForSerialStateChange(const tUSBDCDCDevice *psDevice,
                                      int32_t i32Errors);
static void SetControlLineState(uint16_t ui16State);
static bool SetLineCoding(tLineCoding *psLineCoding);
static void GetLineCoding(tLineCoding *psLineCoding);
static void SendBreak(bool bSend);

//******************************************************************************
//
// This function is called whenever serial data is received from the SCI.
// It is passed the accumulated error flags from each character received in
// this interrupt and determines from them whether or not an interrupt
// notification to the host is required.
//
// If a notification is required and the control interrupt endpoint is idle,
// we send the notification immediately.  If the endpoint is not idle, we
// accumulate the errors in a global variable which will be checked on
// completion of the previous notification and used to send a second one
// if necessary.
//
//******************************************************************************
static void
CheckForSerialStateChange(const tUSBDCDCDevice *psDevice, int32_t i32Errors)
{
    uint16_t ui16SerialState;

    //
    // Clear our USB serial state.  Since we are faking the handshakes, always
    // set the TXCARRIER (DSR) and RXCARRIER (DCD) bits.
    //
    ui16SerialState = USB_CDC_SERIAL_STATE_TXCARRIER |
                      USB_CDC_SERIAL_STATE_RXCARRIER;

    //
    // Are any error bits set?
    //
    if(i32Errors)
    {
        //
        // At least one error is being notified so translate from our hardware
        // error bits into the correct state markers for the USB notification.
        //
        if(i32Errors & SCI_RXST_OE)
        {
            ui16SerialState |= USB_CDC_SERIAL_STATE_OVERRUN;
        }

        if(i32Errors & SCI_RXST_PE)
        {
            ui16SerialState |= USB_CDC_SERIAL_STATE_PARITY;
        }

        if(i32Errors & SCI_RXST_FE)
        {
            ui16SerialState |= USB_CDC_SERIAL_STATE_FRAMING;
        }

        if(i32Errors & SCI_RXST_BRKDT)
        {
            ui16SerialState |= USB_CDC_SERIAL_STATE_BREAK;
        }

        //
        // Call the CDC driver to notify the state change.
        //
        USBDCDCSerialStateChange((void *)psDevice, ui16SerialState);
    }
}

//******************************************************************************
//
// Read as many characters from the SCI FIFO as we can and move them into
// the CDC transmit buffer.
//
// \return Returns SCI error flags read during data reception.
//
//******************************************************************************
static int32_t
ReadSCIData(void)
{
    int32_t i32Char, i32Errors;
    uint8_t ui8Char;
    uint32_t ui32Space;

    //
    // Clear our error indicator.
    //
    i32Errors = 0;

    //
    // Check the space in the buffer.
    //
    ui32Space = USBBufferSpaceAvailable((tUSBBuffer *)&g_sTxBuffer);

    //
    // Read data from the SCI FIFO until there is none left or we run
    // out of space in our receive buffer.
    //
    while(ui32Space && SCI_isDataAvailableNonFIFO(SCIA_BASE))
    {
        //
        // Read a character from the SCI FIFO into the ring buffer if no
        // errors are reported.
        //
        i32Char = SCI_readCharNonBlocking(SCIA_BASE);

        //
        // If the character did not contain any error notifications,
        // copy it to the output buffer.
        //
        if(!(i32Char & ~0xFF))
        {
            ui8Char = (uint8_t)(i32Char & 0xFF);
            USBBufferWrite((tUSBBuffer *)&g_sTxBuffer, (uint8_t *)&ui8Char, 1);

            //
            // Decrement the number of bytes we know the buffer can accept.
            //
            ui32Space--;
        }
        else
        {
#ifdef DEBUG
            //
            // Increment our receive error counter.
            //
            g_ui32SCIRxErrors++;
#endif
            //
            // Update our error accumulator.
            //
            i32Errors |= i32Char;
        }

        //
        // Update our count of bytes received via the SCI.
        //
        g_ui32SCIRxCount++;
    }

    //
    // Pass back the accumulated error indicators.
    //
    return(i32Errors);
}

//******************************************************************************
//
// Take as many bytes from the transmit buffer as we have space for and move
// them into the USB SCI's transmit FIFO.
//
//******************************************************************************
static void
USBSCIPrimeTransmit(uint32_t ui32Base)
{
    uint32_t ui32Read;
    uint8_t ui8Char;

    //
    // If we are currently sending a break condition, don't receive any
    // more data. We will resume transmission once the break is turned off.
    //
    if(g_bSendingBreak)
    {
        return;
    }

    //
    // If there is space in the SCI FIFO, try to read some characters
    // from the receive buffer to fill it again.
    //
    while(SCI_isSpaceAvailableNonFIFO(ui32Base))
    {
        //
        // Get a character from the buffer.
        //
        ui32Read = USBBufferRead((tUSBBuffer *)&g_sRxBuffer, &ui8Char, 1);

        //
        // Did we get a character?
        //
        if(ui32Read)
        {
            //
            // Place the character in the SCI transmit FIFO.
            //
            SCI_writeCharBlockingNonFIFO(ui32Base, ui8Char);

            //
            // Update our count of bytes transmitted via the SCI.
            //
            g_ui32SCITxCount++;
        }
        else
        {
            //
            // We ran out of characters so exit the function.
            //
            return;
        }
    }
}

//******************************************************************************
//
// Interrupt handler for the SCI TX which is being redirected via USB.
//
//******************************************************************************
__interrupt void
USBSCITXIntHandler(void)
{
    uint32_t ui32Ints;

    ui32Ints = SCI_getInterruptStatus(SCIA_BASE);

    //
    // Handle transmit interrupts.
    //
    if(ui32Ints & SCI_INT_TXRDY)
    {
        //
        // Move as many bytes as possible into the transmit FIFO.
        //
        USBSCIPrimeTransmit(SCIA_BASE);

        //
        // If the output buffer is empty, turn off the transmit interrupt.
        //
        if(!USBBufferDataAvailable(&g_sRxBuffer))
        {
            SCI_disableInterrupt(SCIA_BASE, SCI_INT_TXRDY);
        }
    }

    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP9);
}

//******************************************************************************
//
// ConfigureSCI - Configure the SCI and its pins.
//
//******************************************************************************
void
ConfigureSCI(void)
{
    //
    // Configure GPIO Pins for SCI mode.
    //

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
}

//******************************************************************************
//
// Interrupt handler for the SCI RX which is being redirected via USB.
//
//******************************************************************************
__interrupt void
USBSCIRXIntHandler(void)
{
    uint32_t u3i2Ints;

    u3i2Ints = SCI_getInterruptStatus(SCIA_BASE);

    //
    // Handle receive interrupts.
    //
    if(u3i2Ints & SCI_INT_RXRDY_BRKDT)
    {
        //
        // Read SCI's characters into the buffer.
        //
        ReadSCIData();

    }
    else if(u3i2Ints & SCI_INT_RXERR)
    {
        //
        // Notify Host of our error
        //
        CheckForSerialStateChange(&g_sCDCDevice, SCI_getRxStatus(SCIA_BASE));

        //
        // Clear the error and continue
        //
        SCI_performSoftwareReset(SCIA_BASE);
    }

    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP9);
}

//******************************************************************************
//
// Set the state of the RS232 RTS and DTR signals.
//
//******************************************************************************
static void
SetControlLineState(uint16_t ui16State)
{
    //
    // If configured with GPIOs controlling the handshake lines,
    // set them appropriately depending upon the flags passed in the wValue
    // field of the request structure passed.
    //
}

//******************************************************************************
//
// Set the communication parameters to use on the SCI.
//
//******************************************************************************
static bool
SetLineCoding(tLineCoding *psLineCoding)
{
    uint32_t ui32Config;
    bool bRetcode;

    //
    // Assume everything is OK until we detect any problem.
    //
    bRetcode = true;

    //
    // Word length.  For invalid values, the default is to set 8 bits per
    // character and return an error.
    //
    switch(psLineCoding->ui8Databits)
    {
        case 5:
        {
            ui32Config = SCI_CONFIG_WLEN_5;
            break;
        }

        case 6:
        {
            ui32Config = SCI_CONFIG_WLEN_6;
            break;
        }

        case 7:
        {
            ui32Config = SCI_CONFIG_WLEN_7;
            break;
        }

        case 8:
        {
            ui32Config = SCI_CONFIG_WLEN_8;
            break;
        }

        default:
        {
            ui32Config = SCI_CONFIG_WLEN_8;
            bRetcode = false;
            break;
        }
    }

    //
    // Parity. For any invalid values, we set no parity and return an error.
    //
    switch(psLineCoding->ui8Parity)
    {
        case USB_CDC_PARITY_NONE:
        {
            ui32Config |= SCI_CONFIG_PAR_NONE;
            break;
        }

        case USB_CDC_PARITY_ODD:
        {
            ui32Config |= SCI_CONFIG_PAR_ODD;
            break;
        }

        case USB_CDC_PARITY_EVEN:
        {
            ui32Config |= SCI_CONFIG_PAR_EVEN;
            break;
        }

        case USB_CDC_PARITY_MARK:
        {
            ui32Config |= SCI_CONFIG_PAR_ODD;
            break;
        }

        case USB_CDC_PARITY_SPACE:
        {
            ui32Config |= SCI_CONFIG_PAR_EVEN;
            break;
        }

        default:
        {
            ui32Config |= SCI_CONFIG_PAR_NONE;
            bRetcode = false;
            break;
        }
    }

    //
    // Stop bits.  Our hardware only supports 1 or 2 stop bits whereas CDC
    // allows the host to select 1.5 stop bits.  If passed 1.5 (or any other
    // invalid or unsupported value of ui8Stop, we set up for 1 stop bit but
    // return an error in case the caller needs to Stall or otherwise report
    // this back to the host.
    //
    switch(psLineCoding->ui8Stop)
    {
        //
        // One stop bit requested.
        //
        case USB_CDC_STOP_BITS_1:
        {
            ui32Config |= SCI_CONFIG_STOP_ONE;
            break;
        }

        //
        // Two stop bits requested.
        //
        case USB_CDC_STOP_BITS_2:
        {
            ui32Config |= SCI_CONFIG_STOP_TWO;
            break;
        }

        //
        // Other cases are either invalid values of ui8Stop or values that we
        // cannot support so set 1 stop bit but return an error.
        //
        default:
        {
            ui32Config = SCI_CONFIG_STOP_ONE;
            bRetcode |= false;
            break;
        }
    }

    //
    // Set the SCI mode appropriately.
    //
    SCI_setConfig(SCIA_BASE, SysCtl_getLowSpeedClock(DEVICE_OSCSRC_FREQ),
                  readusb32_t(&(psLineCoding->ui32Rate)), ui32Config);

    //
    // Let the caller know if we had a problem or not.
    //
    return(bRetcode);
}

//******************************************************************************
//
// Get the communication parameters in use on the SCI.
//
//******************************************************************************
static void
GetLineCoding(tLineCoding *psLineCoding)
{
    uint32_t ui32Config;
    uint32_t ui32Rate;

    //
    // Get the current line coding set in the SCI.
    //
    SCI_getConfig(SCIA_BASE, SysCtl_getLowSpeedClock(DEVICE_OSCSRC_FREQ),
                  &ui32Rate, &ui32Config);
    writeusb32_t(&(psLineCoding->ui32Rate), ui32Rate);

    //
    // Translate the configuration word length field into the format expected
    // by the host.
    //
    switch(ui32Config & SCI_CONFIG_WLEN_MASK)
    {
        case SCI_CONFIG_WLEN_8:
        {
            psLineCoding->ui8Databits = 8;
            break;
        }

        case SCI_CONFIG_WLEN_7:
        {
            psLineCoding->ui8Databits = 7;
            break;
        }

        case SCI_CONFIG_WLEN_6:
        {
            psLineCoding->ui8Databits = 6;
            break;
        }

        case SCI_CONFIG_WLEN_5:
        {
            psLineCoding->ui8Databits = 5;
            break;
        }

        //
        // We don't expect to receive any other events.  Ignore any that show
        // up in a release build or hang in a debug build.
        //
        default:
#ifdef DEBUG
            while(1);
#else
            break;
#endif
    }

    //
    // Translate the configuration parity field into the format expected
    // by the host.
    //
    switch(ui32Config & SCI_CONFIG_PAR_MASK)
    {
        case SCI_CONFIG_PAR_NONE:
        {
            psLineCoding->ui8Parity = USB_CDC_PARITY_NONE;
            break;
        }

        case SCI_CONFIG_PAR_ODD:
        {
            psLineCoding->ui8Parity = USB_CDC_PARITY_ODD;
            break;
        }

        case SCI_CONFIG_PAR_EVEN:
        {
            psLineCoding->ui8Parity = USB_CDC_PARITY_EVEN;
            break;
        }
        //
        // We don't expect to receive any other events.  Ignore any that show
        // up in a release build or hang in a debug build.
        //
        default:
#ifdef DEBUG
            while(1);
#else
            break;
#endif
    }

    //
    // Translate the configuration stop bits field into the format expected
    // by the host.
    //
    switch(ui32Config & SCI_CONFIG_STOP_MASK)
    {
        case SCI_CONFIG_STOP_ONE:
        {
            psLineCoding->ui8Stop = USB_CDC_STOP_BITS_1;
            break;
        }

        case SCI_CONFIG_STOP_TWO:
        {
            psLineCoding->ui8Stop = USB_CDC_STOP_BITS_2;
            break;
        }

        //
        // We don't expect to receive any other events.  Ignore any that show
        // up in a release build or hang in a debug build.
        //
        default:
#ifdef DEBUG
            while(1);
#else
            break;
#endif
    }
}

//******************************************************************************
//
// This function sets or clears a break condition on the redirected SCI RX
// line.  A break is started when the function is called with \e bSend set to
// \b true and persists until the function is called again with \e bSend set
// to \b false.
//
//******************************************************************************
static void
SendBreak(bool bSend)
{
    //
    // C28x SCI cannot send break conditions
    //
    return;
}

//******************************************************************************
//
// Handles CDC driver notifications related to control and setup of the device.
//
// \param pvCBData is the client-supplied callback pointer for this channel.
// \param ui32Event identifies the event we are being notified about.
// \param ui32MsgValue is an event-specific value.
// \param pvMsgData is an event-specific pointer.
//
// This function is called by the CDC driver to perform control-related
// operations on behalf of the USB host.  These functions include setting
// and querying the serial communication parameters, setting handshake line
// states and sending break conditions.
//
// \return The return value is event-specific.
//
//******************************************************************************
uint32_t
ControlHandler(void *pvCBData, uint32_t ui32Event,
               uint32_t ui32MsgValue, void *pvMsgData)
{
    uint32_t ui32IntsOff;

    //
    // Which event are we being asked to process?
    //
    switch(ui32Event)
    {
        //
        // We are connected to a host and communication is now possible.
        //
        case USB_EVENT_CONNECTED:
            g_bUSBConfigured = true;

            //
            // Flush our buffers.
            //
            USBBufferFlush(&g_sTxBuffer);
            USBBufferFlush(&g_sRxBuffer);

            //
            // Tell the main loop to update the display.
            //
            ui32IntsOff = Interrupt_disableMaster();
            g_pcStatus = "Connected";
            g_ui32Flags |= COMMAND_STATUS_UPDATE;
            if(!ui32IntsOff)
            {
                Interrupt_enableMaster();
            }
            break;

        //
        // The host has disconnected.
        //
        case USB_EVENT_DISCONNECTED:
            g_bUSBConfigured = false;
            ui32IntsOff = Interrupt_disableMaster();
            g_pcStatus = "Disconnected";
            g_ui32Flags |= COMMAND_STATUS_UPDATE;
            if(!ui32IntsOff)
            {
                Interrupt_enableMaster();
            }
            break;

        //
        // Return the current serial communication parameters.
        //
        case USBD_CDC_EVENT_GET_LINE_CODING:
            GetLineCoding(pvMsgData);
            break;

        //
        // Set the current serial communication parameters.
        //
        case USBD_CDC_EVENT_SET_LINE_CODING:
            SetLineCoding(pvMsgData);
            break;

        //
        // Set the current serial communication parameters.
        //
        case USBD_CDC_EVENT_SET_CONTROL_LINE_STATE:
            SetControlLineState((uint16_t)ui32MsgValue);
            break;

        //
        // Send a break condition on the serial line.
        //
        case USBD_CDC_EVENT_SEND_BREAK:
            SendBreak(true);
            break;

        //
        // Clear the break condition on the serial line.
        //
        case USBD_CDC_EVENT_CLEAR_BREAK:
            SendBreak(false);
            break;

        //
        // Ignore SUSPEND and RESUME for now.
        //
        case USB_EVENT_SUSPEND:
        case USB_EVENT_RESUME:
            break;

        //
        // We don't expect to receive any other events.  Ignore any that show
        // up in a release build or hang in a debug build.
        //
        default:
#ifdef DEBUG
            while(1);
#else
            break;
#endif

    }

    return(0);
}

//******************************************************************************
//
// Handles CDC driver notifications related to the transmit channel (data to
// the USB host).
//
// \param pvCBData is the client-supplied callback pointer for this channel.
// \param ui32Event identifies the event we are being notified about.
// \param ui32MsgValue is an event-specific value.
// \param pvMsgData is an event-specific pointer.
//
// This function is called by the CDC driver to notify us of any events
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
    // Which event have we been sent?
    //
    switch(ui32Event)
    {
        case USB_EVENT_TX_COMPLETE:
            //
            // Since we are using the USBBuffer, we don't need to do anything
            // here.
            //
            break;

        //
        // We don't expect to receive any other events.  Ignore any that show
        // up in a release build or hang in a debug build.
        //
        default:
#ifdef DEBUG
            while(1);
#else
            break;
#endif

    }
    return(0);
}

//******************************************************************************
//
// Handles CDC driver notifications related to the receive channel (data from
// the USB host).
//
// \param pvCBData is the client-supplied callback data value for this channel.
// \param ui32Event identifies the event we are being notified about.
// \param ui32MsgValue is an event-specific value.
// \param pvMsgData is an event-specific pointer.
//
// This function is called by the CDC driver to notify us of any events
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
    uint32_t ui32Count;

    //
    // Which event are we being sent?
    //
    switch(ui32Event)
    {
        //
        // A new packet has been received.
        //
        case USB_EVENT_RX_AVAILABLE:
        {
            //
            // Feed some characters into the SCI TX FIFO and enable the
            // interrupt so we are told when there is more space.
            //
            USBSCIPrimeTransmit(SCIA_BASE);
            SCI_enableInterrupt(SCIA_BASE, SCI_INT_TXRDY);
            break;
        }

        //
        // We are being asked how much unprocessed data we have still to
        // process. We return 0 if the SCI is currently idle or 1 if it is
        // in the process of transmitting something. The actual number of
        // bytes in the SCI FIFO is not important here, merely whether or
        // not everything previously sent to us has been transmitted.
        //
        case USB_EVENT_DATA_REMAINING:
        {
            //
            // Get the number of bytes in the buffer and add 1 if some data
            // still has to clear the transmitter.
            //
            ui32Count = SCI_isTransmitterBusy(SCIA_BASE) ? 1 : 0;
            return(ui32Count);
        }

        //
        // We are being asked to provide a buffer into which the next packet
        // can be read. We do not support this mode of receiving data so let
        // the driver know by returning 0. The CDC driver should not be sending
        // this message but this is included just for illustration and
        // completeness.
        //
        case USB_EVENT_REQUEST_BUFFER:
        {
            return(0);
        }

        //
        // We don't expect to receive any other events.  Ignore any that show
        // up in a release build or hang in a debug build.
        //
        default:
#ifdef DEBUG
            while(1);
#else
            break;
#endif
    }

    return(0);
}

//******************************************************************************
//
// This is the main application entry function.
//
//******************************************************************************
int
main(void)
{
    uint32_t ui32TxCount;
    uint32_t ui32RxCount;
    char pcBuffer[16];
    volatile uint32_t ui32Fullness;

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Initialize GPIO and configure GPIO pins for USB.
    //
    Device_initGPIO();

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
    // Initialize the transmit and receive buffers.
    //
    USBBufferInit(&g_sTxBuffer);
    USBBufferInit(&g_sRxBuffer);




    //
    // Register the interrupt handler, returning an error if an error occurs.
    //
    //Interrupt_register(INT_USBA, &INT_myUSB0_ISR);
    //Interrupt_register(INT_myUSB0, &INT_myUSB0_ISR);

    //
    // Set the clocking to run from the PLL at 60MHz
    //
   // SysCtl_setAuxClock(DEVICE_AUXSETCLOCK_CFG_USB);
    Board_init();

    C2000Ware_libraries_init();



    //
    // Pass our device information to the USB library and place the device
    // on the bus.
    //
    //USBDCDCInit(0, &g_sCDCDevice);
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
    // Not configured initially.
    //
    g_bUSBConfigured = false;

    //
    // Configure the SCI for debug output.
    //
    ConfigureSCI();

    //
    // Set the default SCI configuration.
    //
    SCI_setConfig(SCIA_BASE, SysCtl_getLowSpeedClock(DEVICE_OSCSRC_FREQ),
                  DEFAULT_BIT_RATE, DEFAULT_SCI_CONFIG);

    SCI_setFIFOInterruptLevel(SCIA_BASE,SCI_FIFO_TX8, SCI_FIFO_RX8);

    //
    // Configure and enable SCI interrupts.
    //
    SCI_clearInterruptStatus(SCIA_BASE, SCI_getInterruptStatus(SCIA_BASE));
    SCI_enableInterrupt(SCIA_BASE, (SCI_INT_RXERR | SCI_INT_RXRDY_BRKDT |
                                    SCI_INT_TXRDY));
    Interrupt_register(INT_SCIA_TX, &USBSCITXIntHandler);
    Interrupt_register(INT_SCIA_RX, &USBSCIRXIntHandler);


    //
    // Clear our local byte counters.
    //
    ui32RxCount = 0;
    ui32TxCount = 0;

    //
    // Enable interrupts now that the application is ready to start.
    //
    Interrupt_enable(INT_SCIA_RX);
    Interrupt_enableMaster();

    //
    // Main application loop.
    //
    while(1)
    {
        //
        // Have we been asked to update the status display?
        //
        if(g_ui32Flags & COMMAND_STATUS_UPDATE)
        {
            //
            // Clear the command flag
            //
            Interrupt_disableMaster();
            g_ui32Flags &= ~COMMAND_STATUS_UPDATE;
            Interrupt_enableMaster();
        }

        //
        // Has there been any transmit traffic since we last checked?
        //
        if(ui32TxCount != g_ui32SCITxCount)
        {
            //
            // Take a snapshot of the latest transmit count.
            //
            ui32TxCount = g_ui32SCITxCount;

            //
            // Update the display of bytes transmitted by the SCI.
            //
            usnprintf(pcBuffer, 16, "%d ", ui32TxCount);

            //
            // Update the RX buffer fullness. Remember that the buffers are
            // named relative to the USB whereas the status display is from
            // the SCI's perspective. The USB's receive buffer is the SCI's
            // transmit buffer.
            //
            ui32Fullness = ((USBBufferDataAvailable(&g_sRxBuffer) * 100) /
                    myUSB0_LIB_SCI_BUFFER_SIZE);
        }

        //
        // Has there been any receive traffic since we last checked?
        //
        if(ui32RxCount != g_ui32SCIRxCount)
        {
            //
            // Take a snapshot of the latest receive count.
            //
            ui32RxCount = g_ui32SCIRxCount;

            //
            // Update the display of bytes received by the SCI.
            //
            usnprintf(pcBuffer, 16, "%d ", ui32RxCount);

            //
            // Update the TX buffer fullness. Remember that the buffers are
            // named relative to the USB whereas the status display is from
            // the SCI's perspective. The USB's transmit buffer is the SCI's
            // receive buffer.
            //
            ui32Fullness = ((USBBufferDataAvailable(&g_sTxBuffer) * 100) /
                    myUSB0_LIB_SCI_BUFFER_SIZE);
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
