//#############################################################################
//
// FILE:   lpm_ex1_haltwake.c
//
// TITLE:  Halt entry and Exit example.
//
//! \addtogroup driver_example_list
//! <h1>Low Power Modes: Halt Mode and Wakeup</h1>
//!
//!  This example puts the device into HALT mode. If the lowest
//!  possible current consumption in HALT mode is desired, the
//!  JTAG connector must be removed from the device board while
//!  the device is in HALT mode.
//!
//!  The example then wakes up the device from HALT using GPIO0.
//!  GPIO0 wakes the device from HALT mode when a high-to-low
//!  signal is detected on the pin. This pin must be pulsed by
//!  an external agent for wakeup.
//!
//!  The wakeup process begins as soon as GPIO0 is held low for the
//!  time indicated in the device datasheet. After the
//!  device wakes up, GPIO1 can be observed to go low.
//!
//!  GPIO0 is configured as the LPM wakeup pin to trigger a
//!  WAKEINT interrupt upon detection of a low pulse.
//!  Initially, pull GPIO0 high externally.
//!
//!  To observe when device wakes from HALT mode, monitor
//!  GPIO1 with an oscilloscope (Cleared to 0 in WAKEINT ISR)
//!
//! \b External \b Connections \n
//!  - GPIO0, GPIO1
//
//#############################################################################
//
// $Release Date: $
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
//#############################################################################

//
// Included Files
//
#include "driverlib.h"
#include "device.h"

#ifdef _FLASH
// These are defined by the linker (see device linker command file)
extern uint16_t RamfuncsLoadStart;
extern uint16_t RamfuncsLoadSize;
extern uint16_t RamfuncsRunStart;
#endif

//
// Defines
//
// Define if the INTOSC0/1 will be enabled during HALT
#define HALT_OSCON    1           // OSC ON
//#define HALT_OSCON  0       // OSC OFF

//
// Function Prototypes
//
__interrupt void wakeISR(void);

//
// Main
//
void main(void)
{
    //
    // When the example is used with the watchdog Timer, the watchdog
    // timer will reset the device when it is LPM. If the example is run
    // from flash and the device is in a boot to flash configuration,
    // then it will restart the application and will enter the condition
    // below and ESTOP0 if the debugger is connected.
    //
    // Check whether this was a normal startup or a watchdog reset.
    //
    if( SysCtl_getResetCause() == SYSCTL_CAUSE_WDRS)
    {
        SysCtl_clearResetCause(SYSCTL_CAUSE_WDRS);
        ESTOP0;
    }

    //
    // Configure PLL, disable WD, enable peripheral clocks.
    //
    Device_init();

    //
    // Disable pin locks and enable internal pullups.
    //
    Device_initGPIO();

    //
    // GPIO0 is the external wake-up source
    //
    GPIO_setMasterCore(0, GPIO_CORE_CPU1);
    GPIO_setPinConfig(GPIO_0_GPIO0);
    GPIO_setDirectionMode(0, GPIO_DIR_MODE_IN);
    GPIO_setPadConfig(0, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(0, GPIO_QUAL_ASYNC);

    //
    // GPIO1 is an output
    //
    GPIO_setMasterCore(1, GPIO_CORE_CPU1);
    GPIO_setPinConfig(GPIO_1_GPIO1);
    GPIO_setDirectionMode(1,GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(1, GPIO_PIN_TYPE_STD);

    //
    // Use GPIO0 to wake the CPU from halt.
    //
    SysCtl_enableLPMWakeupPin(0);

    //
    // Disable global interrupts.
    //
    DINT;

    //
    // Initialize interrupt controller and vector table.
    //
    Interrupt_initModule();
    Interrupt_initVectorTable();
    IER = 0x0000;
    IFR = 0x0000;

    //
    // Map the ISR to the wake interrupt.
    //
    Interrupt_register(INT_WAKE, wakeISR);

    //
    // Enable the wake interrupt in the PIE: Group 1 interrupt 8.
    //
    Interrupt_enable(INT_WAKE);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);

    //
    // Enable global interrupts.
    //
    EINT;

    //
    // Check if HALT_OSCON is defined.
    //
    if(HALT_OSCON)
    {
        //
        // Enable watchdog in halt.
        //
        SysCtl_enableWatchdogStandbyWakeup();
        SysCtl_setWatchdogMode(SYSCTL_WD_MODE_RESET);
        SysCtl_enableWatchdogInHalt();

        //
        // Enable the watchdog to wake the device from halt.
        // Uncomment this section if a watchdog wakeup is desired.
        //
//        SysCtl_serviceWatchdog();
//        SysCtl_enableWatchdog();
    }
    else
    {
        //
        // Disable watchdog in halt.
        //
        SysCtl_disableWatchdogStandbyWakeup();
        SysCtl_disableWatchdogInHalt();
    }

    //
    // Power down the flash bank and pump. Ensure there are no subsequent
    // flash accesses.
    //
    Flash_powerDown(FLASH0CTRL_BASE);

    //
    // Set GPIO1 high.
    //
    GPIO_writePin(1, 1);

    //
    // Enter halt mode.
    //
    SysCtl_enterHaltMode();

    //
    // Reconfigure PLL after waking from halt.
    //
    SysCtl_setClock(DEVICE_SETCLOCK_CFG);
    ESTOP0;

    //
    // Loop forever.
    //
    while(1)
    {
    }
}

//
// wakeISR() - this will be triggered from a watchdog timeout and set
//             GPIO1 low.
//
__interrupt void
wakeISR(void)
{
    //
    // Write GPIO1 low.
    //
    GPIO_writePin(1, 0);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
}

//
// End of File
//

