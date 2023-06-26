//###########################################################################
//
// FILE:   f2806x_usbWrapper.c
//
// TITLE:  Wrapper for interrupt functions and USB support pins.
//
//###########################################################################
// $TI Release: F2806x C/C++ Header Files and Peripheral Examples V141 $
// $Release Date: January 19, 2015 $
// $Copyright: Copyright (C) 2011-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#include "f2806x_usbWrapper.h"
#include "device/usbdevice.h"
#include "driverlib/interrupt.h"
#include "driverlib/usb.h"
#include "inc/hw_ints.h"
#include "inc/hw_usb.h"

//*****************************************************************************
//
//! @{
//
//*****************************************************************************

// Comment the following three lines as needed
// to select between polling and interrupt driven
// service
#define VBUS_DETECT_INTERRUPT
#define ID_DETECT_INTERRUPT
#define PFLT_DETECT_INTERRUPT

static tDeviceInfo * tDevPtr;
static tUSBCallback * ExtPowerCallback;
static unsigned short g_usUSBFlags;

extern unsigned short g_usUSBFlags;
extern void USBHostPwrDisable(unsigned long ulBase);
extern void USBHostPwrEnable(unsigned long ulBase);
extern void USBHostPwrConfig(unsigned long ulBase, unsigned long ulFlags);
extern void USBHostPwrFaultDisable(unsigned long ulBase);
extern void USBHostPwrFaultEnable(unsigned long ulBase);

//*****************************************************************************
//
//! Device interrupt service routine wrapper to make ISR compatable with
//! C2000 PIE controller.
//
//*****************************************************************************

volatile unsigned long intCount = 0;
__interrupt void
f2806x_USB0DeviceIntHandler(void)
{
	intCount++;
    USB0DeviceIntHandler();
    PieCtrlRegs.PIEACK.all |= 0x10;
}
//*****************************************************************************
//
//! Host interrupt service routine wrapper to make ISR compatable with
//! C2000 PIE controller.
//
//*****************************************************************************
__interrupt void
f2806x_USB0HostIntHandler(void)
{
    USB0HostIntHandler();
    PieCtrlRegs.PIEACK.all |= 0x10;
}

//*****************************************************************************
//
//! Dual mode interrupt service routine wrapper to make ISR compatable with
//! C2000 PIE controller.
//
//*****************************************************************************
__interrupt void
f2806x_USB0DualModeIntHandler(void)
{
    USB0DualModeIntHandler();
    PieCtrlRegs.PIEACK.all |= 0x10;
}


//XINT3
//*****************************************************************************
//
//! Interrupt handler for VBus triggered interrupts.  Enables USB controller
//! if VBus is detected, otherwise removed the controller from the bus.
//
//*****************************************************************************
__interrupt void
f2806x_USBVBusIntHandler(void)
{
    //Check current state of VBUS
    switch(GpioDataRegs.GPADAT.bit.GPIO7)
    {
        //Rising Edge - VBus Applied
    case 1:
        //Restart USB service
        g_usUSBFlags |= USB_VBUS_VALID;
        USBDCDInit(0, tDevPtr);
        break;
        //Falling Edge - VBus Removed
    case 0:
        //Clear VBus Valid flag
        g_usUSBFlags &= ~USB_VBUS_VALID;

        //Vbus Removed so turn off usb
        USBDCDTerm(0);
        break;
    }
    PieCtrlRegs.PIEACK.all |= 0x800;
}

//XINT2
//*****************************************************************************
//
//! Interrupt handler for Power Fault interrupts.  Turns off power if fault is
//! detected, and turns power back on after fault is cleared.
//
//*****************************************************************************
__interrupt void
f2806x_USBPFLTIntHandler(void)
{
    //TODO: Change to match GPIOs used for PFLT and EPEN
    //Check current state of PFLT
    switch(GpioDataRegs.GPADAT.bit.GPIO0)
    {
        //Rising Edge - Power Fault Active
    case 1:
        //Turn off external power
        //Call callback
        if(ExtPowerCallback)
            (*ExtPowerCallback)(0, USB_EVENT_POWER_FAULT, 0, 0);
        break;
        //Falling Edge - Power Fault Inactive
    case 0:
        //Turn on external power
        //Call callback
        if(ExtPowerCallback)
            (*ExtPowerCallback)(0, USB_EVENT_POWER_FAULT, 1, 0);
        break;
    }
    PieCtrlRegs.PIEACK.all |= 0x01;
}

//XINT1
//*****************************************************************************
//
//! Interrupt handler for ID state change events.  Configures USB controller
//! appropriately when the USB ID signal changes.
//
//*****************************************************************************
__interrupt void
f2806x_USBIDIntHandler(void)
{
    //Check current state of ID
    switch(GpioDataRegs.GPADAT.bit.GPIO2)
    {
        //Rising Edge - Device Mode
    case 1:
        g_usUSBFlags &= ~USB_ID_HOST;
        break;
        //Falling Edge - Host Mode
    case 0:
        g_usUSBFlags |= USB_ID_HOST;
        break;
    }
    PieCtrlRegs.PIEACK.all |= 0x800;
}

//*****************************************************************************
//
//! Sets up a GPIO for use for VBus detection
//!
//! \param psDeviceInfo USB device to be initialized when VBus is detected.
//!
//! When using a GPIO for VBus detection don't forget to put a resistance in
//! series with the intended GPIO.  GPIOs are not 5V tolerant, so neglecting
//! the series resistance will potentially damage the device
//!
//! \return Returns void.
//
//*****************************************************************************
void
f2806x_VBusIntInit(tDeviceInfo *psDevice)
{
    //Setup VBus Pin - change to suite your application
    //BE SURE TO PLACE 100k resistor in series; I/Os are NOT 5V TOLERANT
    //GPIO7 = GPIO7
    GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 0;
    //GPIO7 = Input
    GpioCtrlRegs.GPADIR.bit.GPIO7 = 0;

//Only setup interrupts if requested
#ifdef VBUS_DETECT_INTERRUPT
    //XINT3 = GPIO39
    GpioIntRegs.GPIOXINT3SEL.all = 7;
    //Enable XINT3 Interrupt
    XIntruptRegs.XINT3CR.bit.ENABLE = 1;
    //Set XINT3 Polarity 0-falling, 1-rising, 3-both
    XIntruptRegs.XINT3CR.bit.POLARITY = 1;

    //Copy pointer to device info
    tDevPtr = psDevice;

    //Setup Interrupt
    EALLOW;
    //Disable XINT3
    IntDisable(INT_XINT3);
    //Copy VBus handler to Pie Vector Table
    IntRegister(INT_XINT3, f2806x_USBVBusIntHandler);
    //Enable XINT3
    IntEnable(INT_XINT3);
    EDIS;
#endif
}




//*****************************************************************************
//
//! Sets up GPIOs for use for External Power Enable and Power Fault
//!
//! \param Callback USB Points to callback for Power Fault events.
//!
//! \return Returns void.
//
//*****************************************************************************
void
f2806x_ExtPowerInit(tUSBCallback *Callback)
{
    //Setup GPIO0 for EPEN
    //GPIO0 = GPIO0
    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 0;
    //GPIO0 = Output
    GpioCtrlRegs.GPADIR.bit.GPIO0 = 1;
    //Default EPEN State
    GpioDataRegs.GPADAT.bit.GPIO0 = 1;


    //Setup GPIO for PFLT
    //GPIO1 = GPIO1
    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 0;
    //GPIO1 = Input
    GpioCtrlRegs.GPADIR.bit.GPIO1 = 0;

#ifdef PFLT_DETECT_INTERRUPT
    //Enable interrupt, set polarity, etc.
    GpioIntRegs.GPIOXINT2SEL.all = 1;
    //Enable XINT2
    XIntruptRegs.XINT2CR.bit.ENABLE = 1;
    //Interrupt on Rising and Falling edge
    XIntruptRegs.XINT2CR.bit.POLARITY = 3;
    //Register Interrupt Handler

    //Copy callback if it exists
    if(Callback)
        ExtPowerCallback = Callback;

    //Setup Interrupt
    EALLOW;
    //Disable XINT2
    IntDisable(INT_XINT2);
    //Copy PFLT handler to Pie Vector Table
    IntRegister(INT_XINT2, f2806x_USBPFLTIntHandler);
    //Enable XINT2
    IntEnable(INT_XINT2);
    EDIS;
#endif
}

//*****************************************************************************
//
//! Sets up a GPIO for use for ID detection
//!
//! \return Returns void.
//
//*****************************************************************************
void
f2806x_IDInit(void)
{
    //Setup GPIO for ID
    //GPIO1 = GPIO1
    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 0;
    //GPIO1 = Input
    GpioCtrlRegs.GPADIR.bit.GPIO2 = 0;

#ifdef ID_DETECT_INTERRUPT
    //Enable interrupt, set polarity, etc.
    GpioIntRegs.GPIOXINT1SEL.all = 2;
    //Enable XINT1
    XIntruptRegs.XINT1CR.bit.ENABLE = 1;
    //Interrupt on Rising and Falling edge
    XIntruptRegs.XINT1CR.bit.POLARITY = 3;

    //Setup Interrupt
    EALLOW;
    //Disable XINT1
    IntDisable(INT_XINT1);
    //Copy ID handler to Pie Vector Table
    IntRegister(INT_XINT1, f2806x_USBIDIntHandler);
    //Enable XINT1
    IntEnable(INT_XINT1);
    EDIS;
#endif
}


//*****************************************************************************
//
//! Polling function for use when support function aren't implemented with
//! interrupts.  Call this function periodically from the main application.
//!
//! \return Returns void.
//
//*****************************************************************************
void f2806x_USBSupportMain(void)
{
#ifndef PFLT_DETECT_INTERRUPT
    //Check Powerfault
    //if power fault detected turn off power
    //otherwise turn on power
#endif
#ifndef ID_DETECT_INTERRUPT
    //Check ID
    //if host set host flag
    //if device set device flag
#endif
#ifndef VBUS_DETECT_INTERRUPT
    //Check VBus
    //if vbus is valid set vbus valid flag
    //otherwise clear  it
#endif
}






/******************************************************************************
 *
 *   Redefine the following functions to match you application
 *   typically this only requires setting up a few GPIOs
 *
 * ***************************************************************************/

//*****************************************************************************
//
//! Sets the configuration for USB power fault.
//!
//! \param ulBase specifies the USB module base address.
//! \param ulFlags specifies the configuration of the power fault.
//!
//! This function controls how the USB controller uses its external power
//! control pins(USBnPFTL and USBnEPEN).  The flags specify the power
//! fault level sensitivity, the power fault action, and the power enable level
//! and source.
//!
//! One of the following can be selected as the power fault level
//! sensitivity:
//!
//! - \b USB_HOST_PWRFLT_LOW - An external power fault is indicated by the pin
//!                            being driven low.
//! - \b USB_HOST_PWRFLT_HIGH - An external power fault is indicated by the pin
//!                             being driven high.
//!
//! One of the following can be selected as the power fault action:
//!
//! - \b USB_HOST_PWRFLT_EP_NONE - No automatic action when power fault
//!   detected.
//! - \b USB_HOST_PWRFLT_EP_TRI - Automatically Tri-state the USBnEPEN pin on a
//!                               power fault.
//! - \b USB_HOST_PWRFLT_EP_LOW - Automatically drive USBnEPEN pin low on a
//!                               power fault.
//! - \b USB_HOST_PWRFLT_EP_HIGH - Automatically drive USBnEPEN pin high on a
//!                                power fault.
//!
//! One of the following can be selected as the power enable level and source:
//!
//! - \b USB_HOST_PWREN_MAN_LOW - USBEPEN is driven low by the USB controller
//!                               when USBHostPwrEnable() is called.
//! - \b USB_HOST_PWREN_MAN_HIGH - USBEPEN is driven high by the USB controller
//!                                when USBHostPwrEnable() is called.
//! - \b USB_HOST_PWREN_AUTOLOW - USBEPEN is driven low by the USB controller
//!                               automatically if USBOTGSessionRequest() has
//!                               enabled a session.
//! - \b USB_HOST_PWREN_AUTOHIGH - USBEPEN is driven high by the USB controller
//!                                automatically if USBOTGSessionRequest() has
//!                                enabled a session.
//!
//! On devices that support the VBUS glitch filter, the
//! \b USB_HOST_PWREN_FILTER can be added to ignore small short drops in VBUS
//! level caused by high power consumption.  This is mainly used to avoid
//! causing VBUS errors caused by devices with high in-rush current.
//!
//! \note The following values have been deprecated and should no longer be
//!       used.
//! - \b USB_HOST_PWREN_LOW - Automatically drive USBnEPEN low when power is
//!                           enabled.
//! - \b USB_HOST_PWREN_HIGH - Automatically drive USBnEPEN high when power is
//!                            enabled.
//! - \b USB_HOST_PWREN_VBLOW - Automatically drive USBnEPEN low when power is
//!                             enabled.
//! - \b USB_HOST_PWREN_VBHIGH - Automatically drive USBnEPEN high when power is
//!                              enabled.
//!
//! \note This function should only be called on microcontrollers that support
//! host mode or OTG operation.
//!
//! \return None.
//
//*****************************************************************************
void
USBHostPwrConfig(unsigned long ulBase, unsigned long ulFlags)
{


    //
    // Set the power fault configuration as specified.  This will not change
    // whether fault detection is enabled or not.
    //

}

//*****************************************************************************
//
//! Enables power fault detection.
//!
//! \param ulBase specifies the USB module base address.
//!
//! This function enables power fault detection in the USB controller.  If the
//! USBPFLT pin is not in use this function should not be used.
//!
//! \note This function should only be called in host mode.
//!
//! \return None.
//
//*****************************************************************************
void
USBHostPwrFaultEnable(unsigned long ulBase)
{



    //
    // Enable power fault input.
    //

}

//*****************************************************************************
//
//! Disables power fault detection.
//!
//! \param ulBase specifies the USB module base address.
//!
//! This function disables power fault detection in the USB controller.
//!
//! \note This function should only be called in host mode.
//!
//! \return None.
//
//*****************************************************************************
void
USBHostPwrFaultDisable(unsigned long ulBase)
{


    //
    // Enable power fault input.
    //

}

//*****************************************************************************
//
//! Enables the external power pin.
//!
//! \param ulBase specifies the USB module base address.
//!
//! This function enables the USBEPEN signal to enable an external power supply
//! in host mode operation.
//!
//! \note This function should only be called in host mode.
//!
//! \return None.
//
//*****************************************************************************
void
USBHostPwrEnable(unsigned long ulBase)
{


    //
    // Enable the external power supply enable signal.
    //

}

//*****************************************************************************
//
//! Disables the external power pin.
//!
//! \param ulBase specifies the USB module base address.
//!
//! This function disables the USBEPEN signal to disable an external power
//! supply in host mode operation.
//!
//! \note This function should only be called in host mode.
//!
//! \return None.
//
//*****************************************************************************
void
USBHostPwrDisable(unsigned long ulBase)
{


    //
    // Disable the external power supply enable signal.
    //

}

//*****************************************************************************
//
// Close the c2000_specific Doxygen group.
//! @}
//
//*****************************************************************************



