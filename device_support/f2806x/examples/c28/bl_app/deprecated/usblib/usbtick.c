//###########################################################################
//
// FILE:   usbtick.c
//
// TITLE:  Functions related to USB stack tick timer handling.
//
//###########################################################################
// $TI Release: F2806x C/C++ Header Files and Peripheral Examples V141 $
// $Release Date: January 19, 2015 $
// $Copyright: Copyright (C) 2011-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "usblib/usblib.h"
#include "usblib/usblibpriv.h"

//*****************************************************************************
//
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
// These are the internal timer tick handlers used by the USB stack.  Handlers
// in g_pfTickHandlers are called in the context of the USB SOF interrupt
// every USB_SOF_TICK_DIVIDE milliseconds.
//
//*****************************************************************************
tUSBTickHandler g_pfTickHandlers[MAX_USB_TICK_HANDLERS];
void *g_pvTickInstance[MAX_USB_TICK_HANDLERS];

//*****************************************************************************
//
// Flag to indicate whether or not we have been initialized.
//
//*****************************************************************************
tBoolean g_bUSBTimerInitialized = false;

//*****************************************************************************
//
// This is the current tick value in ms for the system.  This is used for all
// instances of USB controllers and for all timer tick handlers.
//
//*****************************************************************************
unsigned long g_ulCurrentUSBTick = 0;

//*****************************************************************************
//
// This is the total number of SOF interrupts received since the system
// booted.  The value is incremented by the low level device- or host-interrupt
// handler functions.
//
//*****************************************************************************
unsigned long g_ulUSBSOFCount = 0;

//*****************************************************************************
//
// This internal function initializes the variables used in processing timer
// ticks.
//
// This function should only be called from within the USB library.  It is set
// up to ensure that it can be called multiple times if necessary without
// the previous configuration being erased (to cater for OTG mode switching).
//
// \return None.
//
//*****************************************************************************
void
InternalUSBTickInit(void)
{
    unsigned long ulLoop;

    if(!g_bUSBTimerInitialized)
    {
        for(ulLoop = 0; ulLoop < MAX_USB_TICK_HANDLERS; ulLoop++)
        {
            g_pfTickHandlers[ulLoop] = (tUSBTickHandler)0;
            g_pvTickInstance[ulLoop] = 0;
        }

        g_bUSBTimerInitialized = true;
    }
}

//*****************************************************************************
//
// This internal function resets the USB tick handler.
//
// This function should only be called from within the USB library.  It will
// clear out the tick handler state and should be called to allow the tick
// handlers to be initialized once USBDCDInit() function is called.
//
// \return None.
//
//*****************************************************************************
void
InternalUSBTickReset(void)
{
    //
    // Reset the initialized flag so that the next time InternalUSBTickInit()
    // is called.
    //
    g_bUSBTimerInitialized = 0;
}

//*****************************************************************************
//
// This internal function handles registering OTG, Host, or Device SOF timer
// handler functions.
//
// \param pfHandler specifies the handler to call for the given type of
// handler.
// \param pvInstance is the instance pointer that will be returned to the
// function provided in the \e pfHandler function.
//
// This function should only be called inside the USB library and only as a
// result to a call to reinitialize the stack in a new mode.  Currently the
// following 3 types of timer tick handlers can be registered:
// TICK_HANDLER_OTG, TICK_HANDLER_HOST, or TICK_HANDLER_DEVICE.  Handlers
// registered via this function are called in the context of the SOF interrupt.
//
// \return A value of zero means that the tick handler was registered and any
// other value indicates an error.
//
//*****************************************************************************
long
InternalUSBRegisterTickHandler(tUSBTickHandler pfHandler,
                               void *pvInstance)
{
    long lIdx;

    for(lIdx = 0; lIdx < MAX_USB_TICK_HANDLERS; lIdx++)
    {
        if(g_pfTickHandlers[lIdx] == 0)
        {
    //
    // Save the handler.
    //
            g_pfTickHandlers[lIdx] = pfHandler;

    //
    // Save the instance data.
    //
            g_pvTickInstance[lIdx] = pvInstance;
        }
    }

    if(lIdx == MAX_USB_TICK_HANDLERS)
    {
        return(-1);
    }
    return(0);
}

//*****************************************************************************
//
//! \internal
//!
//! Calls internal handlers in response to a tick based on the start of frame
//! interrupt.
//!
//! \param ulTicksmS specifies how many milliseconds have passed since the last
//! call to this function.
//!
//! This function is called every 5mS in the context of the Start of Frame
//! (SOF) interrupt.  It is used to call any registered internal tick
//! functions.
//!
//! This function should only be called from within the USB library.
//!
//! \return None.
//
//*****************************************************************************
void
InternalUSBStartOfFrameTick(unsigned long ulTicksmS)
{
    long lIdx;

    //
    // Advance time.
    //
    g_ulCurrentUSBTick += ulTicksmS;

    //
    // Call any registered SOF tick handlers.
    //
    for(lIdx = 0; lIdx < MAX_USB_TICK_HANDLERS; lIdx++)
    {
        if(g_pfTickHandlers[lIdx])
        {
            g_pfTickHandlers[lIdx](g_pvTickInstance[lIdx], ulTicksmS);
        }
    }
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************


