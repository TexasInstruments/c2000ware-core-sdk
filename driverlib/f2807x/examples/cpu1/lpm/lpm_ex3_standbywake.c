//#############################################################################
//
// FILE:   lpm_ex3_standbywake.c
//
// TITLE:  Standby entry and Exit example.
//
//! \addtogroup driver_example_list
//! <h1>Low Power Modes: Device Standby Mode and Wakeup</h1>
//!
//!  This example puts the device into STANDBY mode. If the lowest
//!  possible current consumption in STANDBY mode is desired, the
//!  JTAG connector must be removed from the device board while
//!  the device is in STANDBY mode.
//!
//!  This example puts the device into STANDBY mode then wakes up
//!  the device from STANDBY using watchdog timer or an LPM wakeup pin.
//!
//!  In case of watchdog , the device wakes up from the STANDBY mode
//!  when the watch dog timer overflows triggering an interrupt. In the ISR,
//!  the LED is toggled to indicate the device is out of STANDBY mode.
//!  A pre scalar is set for the watch dog timer to change the counter overflow
//!  time.
//!
//!  In case of wakeup pin , GPIO0 is configured as the LPM wakeup pin
//!  to trigger a WAKEINT interrupt upon detection of a low pulse.
//!  Initially, pull GPIO0 high externally. To wake device
//!  from STANDBY mode, pull GPIO0 low for at least (2+QUALSTDBY)
//!  OSCLKS, then pull it high again.
//!
//!  The example then wakes up the device from STANDBY using GPIO0.
//!  GPIO0 wakes the device from STANDBY mode when a low pulse
//!  (signal goes high->low->high)is detected on the pin.
//!  This pin must be pulsed by an external agent for wakeup.
//!
//!  As soon as GPIO0 goes high again after the pulse, the device
//!  should wake up, and GPIO1 can be observed to toggle low.
//!
//! \b External \b Connections \n
//!  - To observe when device wakes from STANDBY mode, monitor
//!    GPIO1 with an oscilloscope (set to 0 in WAKEINT ISR)
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
// Comment for waking through GPIO.
//
#define WD_WAKE

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

uint16_t toggle = 1, count = 0, i = 0, pass = 0;

//
// Function Prototypes
//
#ifndef WD_WAKE
__interrupt void wakeISR(void);
#else
__interrupt void wakeupISR(void);
#endif

//
// Main
//
void main(void)
{
    //
    // Configure PLL, disable WD, enable peripheral clocks.
    //
    Device_init();

    //
    // Disable pin locks and enable internal pullups.
    //
    Device_initGPIO();

#ifndef WD_WAKE
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
#else
    //
    //Led toggling is a measure of wakeup
    //
    GPIO_setPadConfig(DEVICE_GPIO_PIN_LED1, GPIO_PIN_TYPE_STD);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_LED1, GPIO_DIR_MODE_OUT);
#endif
#ifndef WD_WAKE
    //
    // Use GPIO0 to wake the CPU from standby.
    //
    SysCtl_enableLPMWakeupPin(0);

    //
    // The wakeup signal should be (2+QUALSTBY) OSCCLKs wide
    //
    SysCtl_setStandbyQualificationPeriod(2);
#else
    //
    //Watch dog is used to wake up from watch dog
    //
    SysCtl_enableWatchdogStandbyWakeup();
#endif
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

#ifndef WD_WAKE
    //
    // Map the ISR to the wake interrupt. This would be triggered
    // when the LPM wake pin, mapped to the GPIO0 is pulled low.
    //
    Interrupt_register(INT_WAKE, wakeISR);
#else
    //
    // Re-map watchdog wake interrupt signal to call the ISR function in this
    // example
    //
    Interrupt_register(INT_WAKE, &wakeupISR);
#endif
    //
    // Enable the wake interrupt in the PIE: Group 1 interrupt 8.
    //
    Interrupt_enable(INT_WAKE);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
#ifdef WD_WAKE
    //
    // Set the watchdog to generate an interrupt signal instead of a
    // reset signal
    //
    SysCtl_setWatchdogMode(SYSCTL_WD_MODE_INTERRUPT);
    SysCtl_setWatchdogPrescaler(SYSCTL_WD_PRESCALE_64);
    //
    // Enable the watchdog wake interrupt signal
#endif
    //
    // Enable global interrupts.
    //
    EINT;
#ifdef WD_WAKE
    //
    // Reset the watchdog counter
    //
    SysCtl_serviceWatchdog();

    //
    // Enable the watchdog
    //
    SysCtl_enableWatchdog();
#endif

    //
    // Power down the flash bank and pump. Ensure there are no subsequent
    // flash accesses.
    //
    Flash_powerDown(FLASH0CTRL_BASE);

#ifndef WD_WAKE
    //
    // Set GPIO1 high.
    //
    GPIO_writePin(1, 1);
#endif

    //
    // Enter standby mode.
    //
    SysCtl_enterStandbyMode();

    //
    // Loop forever.
    //
    while(1)
    {
    }
}

#ifndef WD_WAKE
//
// wakeISR - The interrupt service routine called when the watchdog
//              triggers the wake interrupt signal
//
__interrupt void
wakeISR(void)
{
    Example_PassCount++;
    //
    // Write GPIO1 low.
    //
    GPIO_writePin(1, 0);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
}
#else
//
// Wakeup ISR - The interrupt service routine called when the watchdog
//              triggers the wake interrupt signal
//
__interrupt void
wakeupISR(void)
{
    Example_PassCount++;
    for(i = 0; i < 6; i++)
    {
        GPIO_writePin(DEVICE_GPIO_PIN_LED1, toggle);
        DEVICE_DELAY_US(50000);
        toggle = !toggle;
    }
    toggle = !toggle;

    //
    // Acknowledge this interrupt located in group 1
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
}
#endif
//
// End of File
//

