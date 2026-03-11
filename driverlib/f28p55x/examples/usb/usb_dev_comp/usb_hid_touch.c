#include "usb_hal.h"
#include "usblib.h"
#include "usbhid.h"
#include "device/usbdevice.h"
#include "device/usbdhid.h"

#include "usb_hid_touch.h"

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
volatile bool g_bMouseConnected;
volatile uint32_t g_ui32Commands;
volatile uint32_t g_ui32SysTickCount;

__interrupt void
CPUTimerIntHandler(void)
{
    g_ui32SysTickCount++;

    HWREG(&g_ui32Commands) |= 1;

    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
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


void
MoveHandler(void)
{
    uint32_t ui32Retcode;
    char cDeltaX, cDeltaY;

    //
    // Determine the direction to move the mouse.
    //
    ui32Retcode = g_ui32SysTickCount % (4 * TICKS_PER_SECOND);
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
            g_bMouseConnected = false;
        }
    }
}


void usb_hid_touch_sim_init()
{
    Interrupt_register(INT_TIMER0, &CPUTimerIntHandler);

    CPUTimerInit();

    CPUTimer_setPeriod(CPUTIMER0_BASE,
                      (SysCtl_getClock(DEVICE_OSCSRC_FREQ) / TICKS_PER_SECOND));
}

void usb_hid_touch_sim_start()
{
    CPUTimer_enableInterrupt(CPUTIMER0_BASE);
    Interrupt_enable(INT_TIMER0);

    CPUTimer_startTimer(CPUTIMER0_BASE);
}


void usb_hid_touch_sim_handler()
{
    if (g_bMouseConnected) {
        //
        if(HWREG(&g_ui32Commands) & 1)
        {
            HWREG(&g_ui32Commands) &= ~1;
            MoveHandler();
        }
    }
}

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
            g_bMouseConnected = true;
            break;
        }

        //
        // The USB host has disconnected from the device.
        //
        case USB_EVENT_DISCONNECTED:
        {
            g_bMouseConnected = false;
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
