//#############################################################################
//
// FILE:   lpm_ex5_haltwake_gpio.c
//
// TITLE:  Halt entry and Exit example.
//
//! \addtogroup driver_example_list
//! <h1>Low Power Modes: Halt Mode and Wakeup using GPIO</h1>
//!
//!  This example puts the device into HALT mode. If the lowest possible
//!  current consumption in HALT mode is desired, the JTAG connector must be
//!  removed from the device board while the device is in HALT mode.
//!
//!  For applications that require minimal power consumption during HALT mode,
//!  application software should power off the XTAL prior to entering HALT by
//!  setting the XTALCR.OSCOFF bit or by using the driverlib function
//!  SysCtl_turnOffOsc(SYSCTL_OSCSRC_XTAL);. If the OSCCLK source is configured
//!  to be XTAL, the application should first switch the OSSCLK source to
//!  INTOSC1 or INTOSC2 prior to setting XTALCR.OSCOFF.
//!
//!  This example puts the device into HALT mode and then wakes up the device
//!  from HALT using an LPM wakeup pin.
//!
//!  The pin GPIO0 is configured as the LPM wakeup pin to trigger a WAKEINT
//!  interrupt upon detection of a low pulse.The GPIO0 pin must be pulled from
//!  high to low by an external agent for wakeup.
//!
//!  GPIO1 is pulled high before entering the STANDBY mode and is pulled low
//!  when in the wakeup ISR.
//!
//! \b External \b Connections \n
//!  - On device wakeup, the GPIO1 will be low and LED1 will start blinking
//
//#############################################################################
//
//
// 
// C2000Ware v6.00.00.00
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
//#############################################################################

//
// Included Files
//
#include "driverlib.h"
#include "device.h"

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
    GPIO_setPinConfig(GPIO_0_GPIO0);
    GPIO_setDirectionMode(0, GPIO_DIR_MODE_IN);
    GPIO_setPadConfig(0, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(0, GPIO_QUAL_ASYNC);

    //
    // GPIO1 is an output
    //
    GPIO_setPinConfig(GPIO_1_GPIO1);
    GPIO_setDirectionMode(1, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(1, GPIO_PIN_TYPE_STD);

    //
    // LED pin configuration
    //
    GPIO_setPinConfig(DEVICE_GPIO_CFG_LED1);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_LED1, GPIO_PIN_TYPE_STD);
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_LED1, GPIO_DIR_MODE_OUT);

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
    // Set GPIO1 high.
    //
    GPIO_writePin(1, 1);

    //
    // Disable watchdog in halt.
    //
    SysCtl_disableWatchdogInHalt();

    //
    // Enter halt mode.
    //
    SysCtl_enterHaltMode();

    while(1)
    {
        //
        // Toggle LED1
        //
        GPIO_togglePin(DEVICE_GPIO_PIN_LED1);

        //
        // 500ms delay
        //
        DEVICE_DELAY_US(500000);
    }
}

//
// wakeISR() - this will be triggered from a watchdog timeout
//             or when GPIO1 is set low.
//
__interrupt void
wakeISR(void)
{

    //
    // Reconfigure PLL after waking from halt.
    //
    SysCtl_setClock(DEVICE_SETCLOCK_CFG);

    //
    // Set GPIO1 low.
    //
    GPIO_writePin(1, 0);

    //
    // Acknowledge the interrupt
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
}


//
// End of File
//

