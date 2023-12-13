//##############################################################################
//
// FILE:   usb_ex8_dual_detect.c
//
// TITLE:  Example to show how to switch USB operating modes on the fly.
//
//! \addtogroup driver_example_list
//! <h1> USB Dual Detect </h1>
//!
//! This program uses a GPIO to do ID detection.  If a host is connected to
//! the device's USB port, the stack will switch to device mode and enumerate
//! as mouse.  If a mouse device is connected to the device's USB port, the
//! stack will switch to host mode and display the mouses movement and button
//! press information in a serial terminal.
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
//#include "driverlib.h"
//#include "device.h"
#include "usb_hal.h"
#include "board.h"
#include "c2000ware_libraries.h"
#include "usb_structs.h"
#include "usblib.h"
#include "usbhid.h"
#include "device/usbdevice.h"
#include "device/usbdhid.h"
#include "device/usbdhidmouse.h"
#include "host/usbhost.h"
#ifdef DEBUG
#include "scistdio.h"
#endif
#include "usb_ex8_descriptors.h"
#include "usb_ex8_dual_detect.h"

//******************************************************************************
//
// The current state of the USB in the system based on the detected mode.
//
//******************************************************************************
volatile tUSBMode g_eCurrentUSBMode = eUSBModeNone;

//******************************************************************************
//
// The saved number of clock ticks per millisecond.
//
//******************************************************************************
uint32_t g_ui32ClockMS;

//******************************************************************************
//
// The size of the host controller's memory pool in bytes.
//
//******************************************************************************
//#define HCD_MEMORY_SIZE         128

//******************************************************************************
//
// The memory pool to provide to the Host controller driver.
//
//******************************************************************************
//unsigned char g_pHCDPool[HCD_MEMORY_SIZE];
extern uint8_t g_pui8HCDPool[myUSB0_LIB_HCD_MEMORY_SIZE];
//******************************************************************************
//
// This global is used to indicate to the main loop that a mode change has
// occurred.
//
//******************************************************************************
uint32_t g_ui32NewState;

extern tUSBDHIDMouseDevice g_sMouseDevice;

//******************************************************************************
//
// Callback function for mode changes.
//
//******************************************************************************
void
ModeCallback(uint32_t ui32Index, tUSBMode eMode)
{
    //
    // Save the new mode.
    //

    g_eCurrentUSBMode = eMode;

    switch(eMode)
    {
        case eUSBModeHost:
        {
            DEBUG_PRINT("\nHost Mode.\n");
            break;
        }
        case eUSBModeDevice:
        {
            DEBUG_PRINT("\nDevice Mode.\n");
            break;
        }
        case eUSBModeNone:
        {
            DEBUG_PRINT("\nIdle Mode.\n");
            break;
        }
        default:
        {
            DEBUG_PRINT("ERROR: Bad Mode!\n");
            break;
        }
    }
    g_ui32NewState = 1;
}

//******************************************************************************
//
// Configure the UART and its pins.  This must be called before UARTprintf().
//
//******************************************************************************
void
ConfigureSCI(void)
{
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

    //
    // Initialize the SCI for console I/O.
    //
    SCIStdioConfig(SCIA_BASE, 115200, SysCtl_getLowSpeedClock(DEVICE_OSCSRC_FREQ));
}

//******************************************************************************
//
// Capture one sequence of DEVCTL register values during a session request.
//
//******************************************************************************
int
main(void)
{
    uint8_t oldID = 2;

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
    // Set the clocking to run from the PLL at 60MHz
    //
    //SysCtl_setAuxClock(DEVICE_AUXSETCLOCK_CFG_USB);
    Board_init();

    C2000Ware_libraries_init();

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Configure the required pins for USB operation.
    //
    USBGPIOEnable();
    Interrupt_register(INT_USBA, f28x_USB0DualModeIntHandler);

#ifdef DEBUG
    //
    // Configure SCIA for debug output.
    //
    ConfigureSCI();
    SCIprintf("\033[2JDual Mode Detection Application\n");

#endif

    //
    // Determine the number of SysCtlDelay loops required to delay 1mS.
    //
    g_ui32ClockMS = SysCtl_getClock(DEVICE_OSCSRC_FREQ) / (3 * 1000);

    //
    // Initialize the host stack.
    //
    HostStackInit();

    //
    // Initialize the device stack.
    //
    DeviceStackInit();

    Interrupt_enableMaster();

    //
    // Set the new state so that the screen updates on the first
    // pass.
    //
    g_ui32NewState = 1;

    //
    // Loop forever.
    //
    while(1)
    {
        if(GPIO_readPin(47) != oldID)
        {
            oldID = GPIO_readPin(47);
            if(GPIO_readPin(47))
            {
                //
                // Device Mode
                // Kill the host mode
                //
                USBHCDTerm(0);

                //
                // Force device and re-initialize the stack
                //
                USBStackModeSet(0, eUSBModeForceDevice, ModeCallback);

                DeviceStackInit();
                g_eCurrentUSBMode = eUSBModeForceDevice;
            }
            else
            {
                //
                // Host Mode
                // Kill the Device mode
                //
                USBDHIDMouseTerm((tUSBDHIDMouseDevice *)&g_sMouseDevice);
                USBStackModeSet(0, eUSBModeForceHost, ModeCallback);
                HostStackInit();
                USBHCDInit(0, g_pui8HCDPool, myUSB0_LIB_HCD_MEMORY_SIZE);
                g_eCurrentUSBMode = eUSBModeForceHost;
            }
        }

        if(g_eCurrentUSBMode == eUSBModeForceHost)
        {
            HostMain();
        }
    }
}

//
// End of file
//
