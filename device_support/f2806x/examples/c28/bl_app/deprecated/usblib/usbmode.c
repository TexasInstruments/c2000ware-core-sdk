//###########################################################################
//
// FILE:   usbmode.c
//
// TITLE:  Functions related to dual mode USB device/host operation.
//
//###########################################################################
// $TI Release: F2806x C/C++ Header Files and Peripheral Examples V141 $
// $Release Date: January 19, 2015 $
// $Copyright: Copyright (C) 2011-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_usb.h"
#include "driverlib/debug.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/usb.h"
#include "usblib/usblib.h"
#include "usblib/device/usbdevice.h"
#include "usblib/host/usbhost.h"
#include "usblib/usblibpriv.h"

//*****************************************************************************
//
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
// The following label defines interrupts that we will always pass to the host
// interrupt handler even if we are in dual mode and not yet sure of which
// mode we are operating in.
//
//*****************************************************************************
#define USB_HOST_INTS           (USB_INTCTRL_VBUS_ERR)

//*****************************************************************************
//
// Global variable indicating which mode of operation the application has
// requested.
//
//*****************************************************************************
volatile tUSBMode g_eUSBMode = USB_MODE_NONE;

//*****************************************************************************
//
// The default and the current polling rate for the USB OTG library.
//
//*****************************************************************************
volatile unsigned long g_ulPollRate;

//*****************************************************************************
//
// The current time remaining in milliseconds before checking the cable
// connection.
//
//*****************************************************************************
volatile unsigned long g_ulWaitTicks = 0;

//*****************************************************************************
//
// Global variable indicating whether we are currently operating in host or
// device mode if the user has requested Dual mode operation.
//
//*****************************************************************************
static volatile tUSBMode g_eDualMode = USB_MODE_NONE;

//*****************************************************************************
//
// Global variable holding a pointer to the callback function which will be
// called when the USB mode changes between device and host.
//
//*****************************************************************************
static tUSBModeCallback g_pfnUSBModeCallback;

//*****************************************************************************
//
//! Allows a dual-mode application to switch between USB device and host modes.
//!
//! \param ulIndex specifies the USB controller whose mode of operation is to
//! be set.  This parameter must be set to 0.
//! \param eUSBMode indicates the mode that the application wishes to operate
//! in.  Valid values are \b USB_MODE_DEVICE to operate as a USB device and
//! \b USB_MODE_HOST to operate as a USB host.
//! \param pfnCallback is a pointer to a function which the USB library will
//! call each time the mode is changed to indicate the new operating mode.  In
//! cases where \e eUSBMode is set to either \b USB_MODE_DEVICE or
//! \b USB_MODE_HOST, the callback will be made immediately to allow the
//! application to perform any host or device specific initialization.
//!
//! This function allows a USB application, which can operate in host
//! or device mode, to indicate to the USB stack the mode that it wishes to
//! use.  The caller is responsible for cleaning up the interface and removing
//! itself from the bus prior to making this call and reconfiguring afterwards.
//!
//! For successful dual mode mode operation, an application must register
//! USB0DualModeIntHandler() as the interrupt handler for the USB0 interrupt.
//! This handler is responsible for steering interrupts to the device or host
//! stack depending upon the chosen mode.  Devices which do not require dual
//! mode capability should register either \e USB0DeviceIntHandler() or
//! \e USB0HostIntHandler() instead.  Registering \e USB0DualModeIntHandler()
//! for a single mode application will result in an application binary larger
//! than required since library functions for both USB operating modes will be
//! included even though only one mode is required.
//!
//! Single mode applications (those offering exclusively USB device or USB
//! host functionality) need not call this function since no interrupt
//! steering is required if the appropriate single mode interrupt handler is
//! installed.
//!
//! \return None.
//
//*****************************************************************************
void
USBStackModeSet(unsigned long ulIndex, tUSBMode eUSBMode,
                tUSBModeCallback pfnCallback)
{
    //
    // Check the arguments.
    //
    ASSERT(ulIndex == 0);

    //
    // Remember the mode so that we can steer the interrupts appropriately.
    //
    g_eUSBMode = eUSBMode;

    //
    // Remember the callback pointer.
    //
    g_pfnUSBModeCallback = pfnCallback;

    //
    // If we are being asked to be either a host or device, we will not be
    // trying to auto-detect the mode so make the callback immediately.
    //
    if((eUSBMode == USB_MODE_DEVICE) || (eUSBMode == USB_MODE_HOST))
    {
        //
        // Make sure that a callback was provided.
        //
        if(g_pfnUSBModeCallback)
        {
        g_pfnUSBModeCallback(0, eUSBMode);
    }
}
}

//*****************************************************************************
//
//! Steers USB interrupts from controller to the correct handler in the USB
//! stack.
//!
//! This interrupt handler is used in applications which require to operate
//! in both host and device mode.  It steers the USB hardware interrupt to the
//! correct handler in the USB stack depending upon the current operating mode
//! of the application, USB device or host.
//!
//! For successful dual mode operation, an application must register
//! USB0DualModeIntHandler() in the CPU vector table as the interrupt handler
//! for the USB0 interrupt.  This handler is responsible for steering
//! interrupts to the device or host stack depending upon the chosen mode.
//!
//! \note Devices which do not require dual mode capability should register
//! either USB0DeviceIntHandler() or USB0HostIntHandler() instead.  Registering
//! USB0DualModeIntHandler() for a single mode application will result in an
//! application binary larger than required since library functions for both
//! USB operating modes will be included even though only one mode is actually
//! required.
//!
//! \return None.
//
//*****************************************************************************
void
USB0DualModeIntHandler(void)
{
    unsigned long ulStatus;

    //
    // Read the USB interrupt status.
    //
    ulStatus = USBIntStatusControl(USB0_BASE);

    //
    // Pass through the subset of interrupts that we always want
    // the host stack to see regardless of whether or not we
    // are actually in host mode at this point.
    //
    if(ulStatus & USB_HOST_INTS)
    {
        //
        // Call the host's interrupt handler.
        //
        USBHostIntHandlerInternal(0, ulStatus & USB_HOST_INTS);

        //
        // We have already processed these interrupts so clear them
        // from the status.
        //
        ulStatus &= ~USB_HOST_INTS;
    }

    //
    // Steer the interrupt to the appropriate handler within the stack
    // depending upon our current operating mode.  Note that we need to pass
    // the ulStatus parameter since the USB interrupt register is
    // clear-on-read.
    //
    switch(g_eUSBMode)
    {
    case USB_MODE_NONE:
    {
        //
        // No mode is set yet so we have no idea what to do.  Just ignore
        // the interrupt.
        //
        break;
    }

    //
    // Operating in pure host mode.
    //
    case USB_MODE_HOST:
    {
        //
        // Call the host interrupt handler if there is anything still to
        // process.
        //
        USBHostIntHandlerInternal(0, ulStatus);

        break;
    }

    //
    // Operating in pure device mode.
    //
    case USB_MODE_DEVICE:
    {
        //
        // Call the device interrupt handler.
        //
        USBDeviceIntHandlerInternal(0, ulStatus);

        break;
    }

    default:
    {
            break;
    }
    }
}

//*****************************************************************************
//
//! Initializes the USB controller for dual mode operation.
//!
//! \param ulIndex specifies the USB controller that is to be initialized for
//! dual mode operation.  This parameter must be set to 0.
//!
//! This function initializes the USB controller hardware into a state
//! suitable for dual mode operation.  Applications may use this function to
//! ensure that the controller is in a neutral state and able to receive
//! appropriate interrupts before host or device mode is chosen using a call
//! to USBStackModeSet().
//!
//! \return None.
//
//*****************************************************************************
void
USBDualModeInit(unsigned long ulIndex)
{
    //
    // We only support a single USB controller.
    //
    ASSERT(ulIndex == 0);

    //
    // Configure the End point 0.
    //
    USBHostEndpointConfig(USB0_BASE, USB_EP_0, 64, 0, 0,
                          (USB_EP_MODE_CTRL | USB_EP_SPEED_FULL |
                           USB_EP_HOST_OUT));

    //
    // Enable USB Interrupts.
    //
    USBIntEnableControl(USB0_BASE, USB_INTCTRL_RESET |
                                       USB_INTCTRL_DISCONNECT |
                                       USB_INTCTRL_SESSION |
                                       USB_INTCTRL_BABBLE |
                                       USB_INTCTRL_CONNECT |
                                       USB_INTCTRL_RESUME |
                                       USB_INTCTRL_SUSPEND |
                                       USB_INTCTRL_VBUS_ERR);

    //
    // Enable all endpoint interrupts.
    //
    USBIntEnableEndpoint(USB0_BASE, USB_INTEP_ALL);

    //
    // Initialize the USB tick module.
    //
    InternalUSBTickInit();

    //
    // Enable the USB interrupt.
    //
    IntEnable(INT_USB0);

    //
    // Turn on session request to enable ID pin checking.
    //
    USBOTGSessionRequest(USB0_BASE, true);

    //
    // Initialize the power configuration.
    //
    USBHostPwrConfig(USB0_BASE, USBHCDPowerConfigGet(ulIndex));

    //
    // If power enable is automatic then then USBHostPwrEnable() has to be
    // called to allow the USB controller to control the power enable pin.
    //
    if(USBHCDPowerAutomatic(ulIndex))
    {
        //
        // This will not turn on power but instead will allow the USB
        // controller to turn on power when needed.
        //
        USBHostPwrEnable(USB0_BASE);
    }
}

//*****************************************************************************
//
//! Returns the USB controller to the default mode when in dual mode operation.
//!
//! \param ulIndex specifies the USB controller whose dual mode operation is to
//! be ended.  This parameter must be set to 0.
//!
//! Applications using both host and device modes may call this function to
//! disable interrupts in preparation for shutdown or a change of operating
//! mode.
//!
//! \return None.
//
//*****************************************************************************
void
USBDualModeTerm(unsigned long ulIndex)
{
    //
    // We only support a single USB controller.
    //
    ASSERT(ulIndex == 0);

    //
    // Disable the USB interrupt.
    //
    IntDisable(INT_USB0);

    USBIntDisableControl(USB0_BASE, USB_INTCTRL_ALL);

    USBIntDisableEndpoint(USB0_BASE, USB_INTEP_ALL);
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************


