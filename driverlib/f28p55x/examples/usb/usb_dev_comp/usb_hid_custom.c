#include "usb_hal.h"
#include "usblib.h"
#include "usbhid.h"
#include "device/usbdevice.h"
#include "device/usbdhid.h"
#include "usb_hid_custom.h"
#include "scistdio.h"
#include "usb_comp_structs.h"
#include "usb_dev_comp/usb_hid_custom_structs.h"

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
g_eCustomState = MOUSE_STATE_UNCONFIGURED;

static volatile bool g_bCustomConnected;
static volatile uint32_t g_ui32CustomCommands;
static volatile uint32_t g_ui32SysTickCount;
static volatile int8_t g_i8report_feature = 1;

static __interrupt void
CPUTimerIntHandler(void)
{
    g_ui32SysTickCount++;

    HWREG(&g_ui32CustomCommands) |= 1;

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
static bool
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
        // Is the Custom is idle, return immediately.
        //
        if(g_eCustomState == MOUSE_STATE_IDLE)
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

static int32_t ReportFeature(void)
{
    uint32_t ui32Retcode;
    g_eCustomState = MOUSE_STATE_SENDING;
    ui32Retcode = USBDHIDCustomReportFeature((void *)&g_sCustomDevice);

   //
   // Did we schedule the report for transmission?
   //
   if(ui32Retcode == 0)
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
           g_bCustomConnected = false;
           ui32Retcode = 1;
       }
   }

   return ui32Retcode;
}

static void
MoveHandler(void)
{
    uint32_t ui32Retcode;
    uint16_t ui16DeltaX, ui16DeltaY;

    //
    // Determine the direction to move the Custom.
    //
#if 0
    ui32Retcode = g_ui32SysTickCount % (4 * TICKS_PER_SECOND);
    if(ui32Retcode < TICKS_PER_SECOND)
    {
        ui16DeltaX = 1000;
        ui16DeltaY = 1500;
    }
    else if(ui32Retcode < (2 * TICKS_PER_SECOND))
    {
        ui16DeltaX = 1000;
        ui16DeltaY = 2000;
    }
    else if(ui32Retcode < (3 * TICKS_PER_SECOND))
    {
        ui16DeltaX = 1000;
        ui16DeltaY = 2500;
    }
    else
    {
        ui16DeltaX = 1000;
        ui16DeltaY = 3000;
    }
#endif
    ui16DeltaX = 1000;
    ui16DeltaY = 1000;

    //
    // Tell the HID driver to send this new report.
    //
    g_eCustomState = MOUSE_STATE_SENDING;
    ui32Retcode = USBDHIDCustomPointStateChange((void *)&g_sCustomDevice, ui16DeltaX,
                                                ui16DeltaY);
}

static void
DummySimHandler(void)
{
    uint32_t ui32Retcode;
    tUSBHIDCustomTouchEvent sEvent;

    int8_t iter = 0;

    sEvent.press_count = 10;
    for (iter = 0; iter < sEvent.press_count; iter++) {
        sEvent.fingers[iter].press = 0;
        sEvent.fingers[iter].x = 0xFFFF;
        sEvent.fingers[iter].y = 0xFFFF;
    }

    //
    // Tell the HID driver to send this new report.
    //
    g_eCustomState = MOUSE_STATE_SENDING;

    ui32Retcode = USBDHIDCustomTouchEvent((void *)&g_sCustomDevice, &sEvent);
}

static void
MultTouchSimHandler(void)
{
    uint32_t ui32Retcode;
    tUSBHIDCustomTouchEvent sEvent;
    int8_t iter = 0;
    uint16_t x_iter = 1000;

    while(x_iter < 1900) {
        sEvent.press_count = 10;
        for (iter = 0; iter < 10; iter++) {
            sEvent.fingers[iter].press = 1;
            sEvent.fingers[iter].x = x_iter;
            sEvent.fingers[iter].y = 1000 + iter * 200;
        }

        //
        // Tell the HID driver to send this new report.
        //
        g_eCustomState = MOUSE_STATE_SENDING;

        ui32Retcode = USBDHIDCustomTouchEvent((void *)&g_sCustomDevice, &sEvent);
        if(ui32Retcode == 0)
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
                g_bCustomConnected = false;
                break;
            }
            x_iter+=10;
        }
    }
}

static void
KeySimHandler(void)
{
    uint32_t ui32Retcode;
    uint8_t ui8KeyIter;
    uint8_t ui8Key;

    for (ui8KeyIter = 0; ui8KeyIter < 8; ui8KeyIter++) {

        ui8Key = (1 << ui8KeyIter);

        //
        // Tell the HID driver to send this new report.
        //
        g_eCustomState = MOUSE_STATE_SENDING;

        ui32Retcode = USBDHIDCustomReportKey((void *)&g_sCustomDevice, ui8Key);
        if(ui32Retcode == 0)
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
                g_bCustomConnected = false;
                break;
            }
        }

        ui8Key = 0;

        //
        // Tell the HID driver to send this new report.
        //
        g_eCustomState = MOUSE_STATE_SENDING;

        ui32Retcode = USBDHIDCustomReportKey((void *)&g_sCustomDevice, ui8Key);
        if(ui32Retcode == 0)
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
                g_bCustomConnected = false;
                break;
            }
        }

        USBDelay(500);
    }
}

void usb_hid_custom_sim_init()
{
    Interrupt_register(INT_TIMER0, &CPUTimerIntHandler);

    CPUTimerInit();

    CPUTimer_setPeriod(CPUTIMER0_BASE,
                      (SysCtl_getClock(DEVICE_OSCSRC_FREQ) / TICKS_PER_SECOND));
}

void usb_hid_custom_sim_start()
{
    CPUTimer_enableInterrupt(CPUTIMER0_BASE);
    Interrupt_enable(INT_TIMER0);

    CPUTimer_startTimer(CPUTIMER0_BASE);
}


void usb_hid_custom_sim_handler()
{
    if (g_bCustomConnected) {
        //
        if (g_i8report_feature) {
            if (ReportFeature() == 0) {
                log_info("Report feature success");
                g_i8report_feature--;
            }
        } else {
            if(HWREG(&g_ui32CustomCommands) & 1)
            {
                HWREG(&g_ui32CustomCommands) &= ~1;

                if(g_eCustomState != MOUSE_STATE_IDLE) {
                    return;
                }
#if 1
                //MoveHandler();
#endif

#if 1
                //TouchSimHandler();
                MultTouchSimHandler();
                KeySimHandler();
                //MultTouchSimHandler();
#endif

                //DummySimHandler();
            }
        }
    } else {
        g_i8report_feature = 10;
    }
}

uint32_t
CustomHandler(void *pvCBData, uint32_t ui32Event, uint32_t ui32MsgData,
             void *pvMsgData)
{
    switch(ui32Event)
    {
        //
        // The USB host has connected to and configured the device.
        //
        case USB_EVENT_CONNECTED:
        {
            g_eCustomState = MOUSE_STATE_IDLE;
            g_bCustomConnected = true;
            break;
        }

        //
        // The USB host has disconnected from the device.
        //
        case USB_EVENT_DISCONNECTED:
        {
            g_bCustomConnected = false;
            g_eCustomState = MOUSE_STATE_UNCONFIGURED;
            break;
        }

        //
        // A report was sent to the host.  We are not free to send another.
        //
        case USB_EVENT_TX_COMPLETE:
        {
            g_eCustomState = MOUSE_STATE_IDLE;
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
