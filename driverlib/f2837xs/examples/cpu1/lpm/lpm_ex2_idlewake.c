//#############################################################################
//
// FILE:   lpm_ex2_idlewake.c
//
// TITLE:  Idle entry and Exit example.
//
//! \addtogroup driver_example_list
//! <h1>Low Power Modes: Device Idle Mode and Wakeup</h1>
//!
//!  This example puts the device into IDLE mode then
//!  wakes up the device from IDLE using watchdog timer or using XINT1
//!  which triggers on a falling edge of GPIO0.
//!
//!  In the case of watchdog, the device wakes up from the IDLE mode when
//!  the watch dog timer overflows, triggering an interrupt. In the ISR, the LED
//!  is toggled to indicate the device is out of IDLE mode.
//!  A pre scalar is set for the watch dog timer to change the counter overflow
//!  time.
//!
//!  In the case of XINT1, this GPIO0 pin must be pulled from high to low
//!  by an external agent for wakeup. GPIO0 is configured as an XINT1 pin
//!  to trigger an XINT1 interrupt upon detection of a falling edge.
//!
//!  Initially, pull GPIO0 high externally. To wake device
//!  from IDLE mode by triggering an XINT1 interrupt,
//!  pull GPIO0 low (falling edge). The wakeup process begins as soon
//!  as GPIO0 is held low for the time indicated in the device datasheet.
//!  After the device wakes up, GPIO1 can be observed to go low.
//!
//! \b External \b Connections \n
//!  - In the case of XINT1, To observe the device wakeup from IDLE mode,
//!    monitor GPIO1 with an oscilloscope, which goes high in the XINT_1_ISR.
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
__interrupt void xint1ISR(void);
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
    // Configure GPIO0 as external wake source. The input XBAR is configured
    // to map the GPIO0 to the XINT1 using XBAR input 4
    //
    XBAR_setInputPin(XBAR_INPUT4, 0);
    GPIO_setInterruptType(GPIO_INT_XINT1, GPIO_INT_TYPE_FALLING_EDGE);
    GPIO_enableInterrupt(GPIO_INT_XINT1);
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
    // Map the ISR to the XINT1 interrupt.
    //
    Interrupt_register(INT_XINT1, xint1ISR);
#else
    //
    // Re-map watchdog wake interrupt signal to call the ISR function in this
    // example
    //
    Interrupt_register(INT_WAKE, &wakeupISR);
#endif
#ifndef WD_WAKE
    //
    // Enable the wake interrupt in the PIE: Group 1 interrupt 4.
    //
    Interrupt_enable(INT_XINT1);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
#else
    //
    // Set the watchdog to generate an interrupt signal instead of a
    // reset signal
    //
    SysCtl_setWatchdogMode(SYSCTL_WD_MODE_INTERRUPT);
    SysCtl_setWatchdogPrescaler(SYSCTL_WD_PRESCALE_64);

    //
    // Enable the watchdog wake interrupt signal in the
    // PIE: Group 1 interrupt 8.
    //
    Interrupt_enable(INT_WAKE);
#endif
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
    // Enter idle mode.
    //
    SysCtl_enterIdleMode();

    //
    // Loop forever.
    //
    while(1)
    {
    }
}
#ifndef WD_WAKE
//
// xint1ISR - External interrupt when GPIO0 is pulled from high to low.
//
__interrupt void
xint1ISR(void)
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
    for(i=0;i<6;i++)
    {
        GPIO_writePin(DEVICE_GPIO_PIN_LED1, toggle);
        DEVICE_DELAY_US(50000);
        toggle= !toggle;
    }
    toggle=!toggle;
    //
    // Acknowledge this interrupt located in group 1
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
}
#endif
//
// End of File
//

