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
//
// C2000Ware v5.04.00.00
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

#include "scistdio.h"
#include "usb_structs.h"
#include "usblib.h"
#include "usbcdc.h"
#include "usb_ids.h"
#include "device/usbdevice.h"
#include "device/usbdcdc.h"
#include "usb_hal.h"
//#include "usb_hid_touch.h"
#include "usb_cdc.h"
#include "usb_hid_custom.h"
//#include "usb_key.h"


// Interrupt Settings for INT_myUSB0
// ISR need to be defined for the registered interrupts
#define INT_myUSB0 INT_USBA
#define INT_myUSB0_INTERRUPT_ACK_GROUP INTERRUPT_ACK_GROUP9

//*****************************************************************************
//
// USB Configurations
//
//*****************************************************************************
//
// Define to pass to SysCtl_setAuxClock(). Will configure the clock as follows:
// AUXPLLCLK =
//       20MHz (XTAL_OSC) * 12 (IMULT) / (4 (SYSDIV) )
//
#define DEVICE_AUXSETCLOCK_CFG_USB   (SYSCTL_OSCSRC_XTAL | SYSCTL_PLL_ENABLE |\
                                      SYSCTL_IMULT(12) | SYSCTL_SYSDIV(4))
#define myUSB0_BASE USB0_BASE
void myUSB0_init();

//*****************************************************************************
//
// Board Configurations
//
//*****************************************************************************
void    Board_init();
void    INTERRUPT_init();
void    USB_init();
void    PinMux_init();
void USBLib_init();




void INT_myUSB0_ISR(void);
//******************************************************************************
//
// Configuration and tuning parameters.
//
//******************************************************************************

//******************************************************************************
//
// This is the main application entry function.
//
//******************************************************************************
int
main(void)
{
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
   // Board_init();
    EALLOW;
    PinMux_init();
    USB_init();
    INTERRUPT_init();
    EDIS;

    USBLib_init();

    USBDCDCCompositeInit(0, &g_sCDCDevice, &g_psCompDevices[0]);
    USBDHIDCustomCompositeInit(0, &g_sCustomDevice, &g_psCompDevices[1]);

    USBDCompositeInit(0, &g_sCompDevice, DESCRIPTOR_DATA_SIZE,
                      g_pui8DescriptorData);

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

    usb_hid_custom_sim_init();

    //
    // Clear our local byte counters.
    //

    usb_hid_custom_sim_start();
    //
    // Enable interrupts now that the application is ready to start.
    //
    Interrupt_enable(INT_SCIA_RX);
    Interrupt_enableGlobal();

    //
    // Main application loop.
    //
    SCIprintf("\nC2000 F2838x Series USB Composite device example\n");
    SCIprintf("---------------------------------\n\n");

    while(1)
    {
        //
        // If it is time to move the mouse then do so.
        //
        usb_hid_custom_sim_handler();

        //usb_cdc_sim_handler();
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


//*****************************************************************************
//
// PINMUX Configurations
//
//*****************************************************************************
void PinMux_init()
{
    //
    // PinMux for modules assigned to CPU1
    //

    // USB pinmux
    GPIO_setAnalogMode(23, GPIO_ANALOG_ENABLED);
    GPIO_setAnalogMode(41, GPIO_ANALOG_ENABLED);

}

//*****************************************************************************
//
// INTERRUPT Configurations
//
//*****************************************************************************
void INTERRUPT_init(){

    // Interrupt Settings for INT_myUSB0
    // ISR need to be defined for the registered interrupts
    Interrupt_register(INT_myUSB0, &INT_myUSB0_ISR);
    Interrupt_enable(INT_myUSB0);
}
//*****************************************************************************
//
// USB Configurations
//
//*****************************************************************************
void USB_init(){
    //
    // Set the clocking to run from the PLL at 60MHz
    //
    SysCtl_setUSBClockDivider(SYSCTL_USBCLK_DIV_5);
}

void USBLib_init(){
    //
    // Set the USB stack mode to Device mode with VBUS monitoring.
    //
    USBStackModeSet(0, eUSBModeForceDevice, 0);
}

//
// End of file
//
