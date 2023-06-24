//#############################################################################
//
// FILE:   sysctl_ex2_xclkout_config.c
//
// TITLE:  XCLKOUT Configuration
//
//! \addtogroup driver_example_list
//! <h1> XCLKOUT (External Clock Output) Configuration </h1>
//!
//! This example demonstrates how to configure the XCLKOUT pin for observing
//! internal clocks through an external pin, for debugging and testing purposes.
//!
//! In this example, we are using INTOSC1 as the XCLKOUT clock source and
//! configuring the divider as 8.
//! Expected frequency of XCLKOUT = (INTOSC1 freq)/8 = 10/8 = 1.25MHz
//!
//! View the XCLKOUT on GPIO16 using an oscilloscope.
//
//#############################################################################
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
    // Disable pin locks and enable internal pullups.
    //
    Device_initGPIO();

    //
    // Select the clock source for XCLKOUT. Refer to the enum SysCtl_ClockOut
    // for other clock sources.
    //
    SysCtl_selectClockOutSource(SYSCTL_CLOCKOUT_INTOSC1);

    //
    // Configure the XCLOUT clock divider. The divider can be /1, /2, /4 or /8.
    //
    SysCtl_setXClk(SYSCTL_XCLKOUT_DIV_8);

    //
    // Configure GPIO16 as XCLKOUT pin. Note that GPIO18 also can be used as
    // XCLKOUT pin
    //
    GPIO_setPinConfig(GPIO_16_XCLKOUT);
    // GPIO_setPinConfig(GPIO_18_XCLKOUT);

    //
    // Loop Forever. The Clock can be viewed on the configured GPIO pin.
    //
    while(1);
}

//
// End of File
//
