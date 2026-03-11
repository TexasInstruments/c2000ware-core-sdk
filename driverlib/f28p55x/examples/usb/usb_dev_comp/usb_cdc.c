#include "usb_structs.h"
#include "usblib.h"
#include "usbcdc.h"
#include "usb_ids.h"
#include "device/usbdevice.h"
#include "device/usbdcdc.h"
#include "ustdlib.h"
#include "usb_hal.h"
//#include "usb_hid_touch.h"
#include "scistdio.h"

#include "usb_cdc.h"

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
// Flag indicating whether or not we are currently sending a Break condition.
//
//******************************************************************************
bool g_bSendingBreak = false;

//******************************************************************************
//
// Flags used to pass commands from interrupt context to the main loop.
//
//******************************************************************************
volatile uint32_t g_ui32Flags = 0;
char *g_pcStatus;

//******************************************************************************
//
// Global flag indicating that a USB configuration has been set.
//
//******************************************************************************
volatile bool g_bUSBConfigured = false;

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
    // GPIO9 is the SCI Rx pin.
    //
    GPIO_setControllerCore(9, GPIO_CORE_CPU1);
    GPIO_setPinConfig(GPIO_9_SCIA_RX);
    GPIO_setDirectionMode(9, GPIO_DIR_MODE_IN);
    GPIO_setPadConfig(9, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(9, GPIO_QUAL_ASYNC);

    //
    // GPIO8 is the SCI Tx pin.
    //
    GPIO_setControllerCore(8, GPIO_CORE_CPU1);
    GPIO_setPinConfig(GPIO_8_SCIA_TX);
    GPIO_setDirectionMode(8, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(8, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(8, GPIO_QUAL_ASYNC);


    //
    // GPIO15 is the SCI Rx pin.
    //
    GPIO_setControllerCore(15, GPIO_CORE_CPU1);
    GPIO_setPinConfig(GPIO_15_SCIB_RX);
    GPIO_setDirectionMode(15, GPIO_DIR_MODE_IN);
    GPIO_setPadConfig(15, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(15, GPIO_QUAL_ASYNC);

    //
    // GPIO14 is the SCI Tx pin.
    //
    GPIO_setControllerCore(14, GPIO_CORE_CPU1);
    GPIO_setPinConfig(GPIO_14_SCIB_TX);
    GPIO_setDirectionMode(14, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(14, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(14, GPIO_QUAL_ASYNC);

    //
    // Initialize the SCI for console I/O.
    //
    SCIStdioConfig(SCIB_BASE, 115200,
                   SysCtl_getLowSpeedClock(DEVICE_OSCSRC_FREQ));

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
USBDCDCControlHandler(void *pvCBData, uint32_t ui32Event,
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
            ui32IntsOff = Interrupt_disableGlobal();
            g_pcStatus = "Connected";
            g_ui32Flags |= COMMAND_STATUS_UPDATE;
            if(!ui32IntsOff)
            {
                Interrupt_enableGlobal();
            }
            break;

        //
        // The host has disconnected.
        //
        case USB_EVENT_DISCONNECTED:
            g_bUSBConfigured = false;
            ui32IntsOff = Interrupt_disableGlobal();
            g_pcStatus = "Disconnected";
            g_ui32Flags |= COMMAND_STATUS_UPDATE;
            if(!ui32IntsOff)
            {
                Interrupt_enableGlobal();
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
USBDCDCTxHandler(void *pvCBData, uint32_t ui32Event, uint32_t ui32MsgValue,
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
USBDCDCRxHandler(void *pvCBData, uint32_t ui32Event, uint32_t ui32MsgValue,
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

static uint32_t ui32TxCount = 0;
static uint32_t ui32RxCount = 0;
static char pcBuffer[16] = {0};
static volatile uint32_t ui32Fullness = 0;

void usb_cdc_sim_handler()
{
    //
    // Have we been asked to update the status display?
    //
    if(g_ui32Flags & COMMAND_STATUS_UPDATE)
    {
        //
        // Clear the command flag
        //
        Interrupt_disableGlobal();
        g_ui32Flags &= ~COMMAND_STATUS_UPDATE;
        Interrupt_enableGlobal();
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
