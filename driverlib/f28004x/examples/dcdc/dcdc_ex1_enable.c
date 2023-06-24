//#############################################################################
//
// FILE:   dcdc_ex1_enable.c
//
// TITLE:   DCDC Enable Example
//
//! \addtogroup driver_example_list
//! <h1> DCDC Enable </h1>
//!
//! This example enables the DC-DC regulator. The procedure to enable the 
//! internal DC-DC regulator must be completed prior to all other 
//! initialization functions and application code.
//!
//! This example later disables the DC-DC and asks the user to measure the I/O 
//! current before and after. Breakpoints are provided for this purpose to test
//! the functionality, this is an optional feature and can be removed.
//!
//! \b External \b Connections \n
//!  - Refer to the device Datasheet for the External Connections for the DC-DC module.
//!
//!
//
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2023 Texas Instruments Incorporated - http://www.ti.com/
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
#include "board.h"

//
// Main
//
void main(void)
{
    //
    // Disable the watchdog timer
    //
    SysCtl_disableWatchdog();

    //
    // DC-DC initialization
    //
    DC_DC_init(); 

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Initialize GPIO and configure GPIO pins for CANTX/CANRX
    //
    Device_initGPIO();

    //
    // Board initialization
    //
    Board_init();

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
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;


    //
    // Loop Forever 
    //
     while(1)
    {
        // DC-DC is enabled by sysconfig
        /* First Breakpoint is provided for the user to measure I/O current while DC-DC is enabled. */ 
        ESTOP0; 
        ASysCtl_disableDCDC();
        /* Second breakpoint is provided for the user to measure I/o current while DC-DC is disabled. */
        ESTOP0;
    }
}

//
// End of File
//
