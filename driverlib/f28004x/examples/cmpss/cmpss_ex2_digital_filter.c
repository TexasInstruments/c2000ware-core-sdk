//#############################################################################
//
// FILE:   cmpss_ex2_digital_filter.c
//
// TITLE:  CMPSS Digital Filter Configuration
//
//! \addtogroup driver_example_list
//! <h1> CMPSS Digital Filter Configuration </h1>
//!
//! This example enables the CMPSS1 COMPH comparator and feeds the output
//! through the digital filter to the GPIO14/OUTPUTXBAR3 pin.
//!
//! CMPIN1P is used to give positive input and internal DAC is configured 
//! to provide the negative input. Internal DAC is configured to provide a
//! signal at VDD/2.
//!
//! When a low input(VSS) is provided to CMPIN1P,
//!     - GPIO14 output is low
//!
//! When a high input(higher than VDD/2) is provided to CMPIN1P,
//!     - GPIO14 output turns high

//!
//! \b External \b Connections \n
//!  - Give input on CMPIN1P (The pin is shared with ADCINB6)
//!  - Output can be observed on GPIO14
//!
//! \b Watch \b Variables \n
//!  - None
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
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Disable pin locks and enable internal pullups.
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
    // Board initialization
    // - Configure GPIO14 to output CTRIPOUT1H (routed through XBAROUTPUT3)
    // - Setup the Output X-BAR to output CTRIPOUTH on OUTPUTXBAR3
    // - Configure the high comparator of CMPSS1
    // - Enable CMPSS and configure the negative input signal to come from
    //   the DAC
    // - Use VDDA as the reference for the DAC and set DAC value to midpoint for
    //   arbitrary reference.
    // - Configure digital filter. For this example, the maxiumum values will be
    //   used for the clock prescale, sample window size, and threshold.
    // - Initialize the filter logic and start filtering
    // - Configure the output signals. Both CTRIPH and CTRIPOUTH will be fed by
    //   the filter output.
    //
    Board_init();

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Loop indefinitely
    //
    while(1)
    {

    }
}
