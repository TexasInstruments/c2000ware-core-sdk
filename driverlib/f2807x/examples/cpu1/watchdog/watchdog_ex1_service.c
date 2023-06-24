//#############################################################################
//
// FILE:   watchdog_ex1_service.c
//
// TITLE:  Servicing Watchdog Example
//
//! \addtogroup driver_example_list
//! <h1> Watchdog </h1>
//!
//! This example shows how to service the watchdog or generate a wakeup
//! interrupt using the watchdog. By default the example will generate a
//! Wake interrupt.  To service the watchdog and not generate the interrupt,
//! uncomment the SysCtl_serviceWatchdog() line in the main for loop.
//!
//! \b External \b Connections \n
//!  - None.
//!
//! \b Watch \b Variables \n
//!  - wakeCount - The number of times entered into the watchdog ISR
//!  - loopCount - The number of loops performed while not in ISR
//!
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

//
// Globals
//
uint32_t wakeCount;
uint32_t loopCount;

//
// Function Prototypes
//
__interrupt void wakeupISR(void);

//
// Main
//
void main(void)
{
    //
    // Initialize device clock and peripherals
    //
    Device_init();

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
    // Re-map watchdog wake interrupt signal to call the ISR function in this
    // example
    //
    Interrupt_register(INT_WAKE, &wakeupISR);

    //
    // Clear the counters
    //
    wakeCount = 0;
    loopCount = 0;

    //
    // Set the watchdog to generate an interrupt signal instead of a
    // reset signal
    //
    SysCtl_setWatchdogMode(SYSCTL_WD_MODE_INTERRUPT);

    //
    // Enable the watchdog wake interrupt signal
    //
    Interrupt_enable(INT_WAKE);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Reset the watchdog counter
    //
    SysCtl_serviceWatchdog();

    //
    // Enable the watchdog
    //
    SysCtl_enableWatchdog();

    //
    // Loop Forever
    //
    for(;;)
    {
        loopCount++;

        //
        // Uncomment SysCtl_serviceWatchdog to just loop here.
        // Comment SysCtl_serviceWatchdog to have watchdog timeout and trigger
        // an interrupt signal to execute the wakeupISR
        //
        // SysCtl_serviceWatchdog();
    }
}

//
// Wakeup ISR - The interrupt service routine called when the watchdog
//              triggers the wake interrupt signal
//
__interrupt void
wakeupISR(void)
{
    wakeCount++;

    //
    // Acknowledge this interrupt located in group 1
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
	
    Example_PassCount++;
}

//
// End of File
//
