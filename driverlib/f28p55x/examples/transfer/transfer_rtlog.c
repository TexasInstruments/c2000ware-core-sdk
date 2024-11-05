//#############################################################################
//
// FILE:   transfer_rtlog.c
//
// TITLE:  Transfer: Custom Logger Solution
//
//! \addtogroup driver_example_list
//! <h1> GUI based solution for data logging (one direction) </h1>
//!
//! This example demonstrates how to use SysConfig to enable datalogging
//! on our C28x devices. 
//!
//! In this example, we are using FSI to export data out of the device.
//! If you're using a launchpad, you can enable board components to select
//! the correct FSI base then refer to transfer_comslogger_rtlog_export_sci to
//! visualize the data through a COM port. This project works in conjunction 
//! with transfer_comslogger_rtlog_export_sci.
//! This project generates a file named loggger/realtime_log.json that is 
//! used for the transfer_comslogger_rtlog_export_sci project. This file
//! provides the metadata to know how to display the incoming data coming
//! from the FSI frame to the GUI. The GUI tab named RT Logger will show
//! the data in a table format.
//!
//
//#############################################################################
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
//#############################################################################

//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "board.h"
#include "c2000ware_libraries.h"
#include "logger/realtime_log.h"
uint16_t a = 0;
float e[8] = {
                   1243.43, -4399.24, -23.392, 0.0213,
                   -2093, 238.4993, -2390.300, 329.401
            };

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
    // Disable pin locks and enable internal pull-ups.
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
    // PinMux and Peripheral Initialization
    //
    Board_init();

    //
    // C2000Ware Library initialization
    //
    C2000Ware_libraries_init();

    //
    // Logging Inits
    //
    RTLOG_init();

    //
    // Start the high priority ISR
    //
    CPUTimer_startTimer(myTimer1s_BASE);

    //
    // Enable Global Interrupt (INTM) and real time interrupt (DBGM)
    //
    EINT;
    ERTM;

    while(1)
    {

    }
}

volatile uint16_t toggle = 0;
interrupt void INT_myTimer1s_ISR(void){
    uint32_t b = 6798004;
    float c = -189.4934;
    uint16_t d[2] = {19872, 290};

    if (toggle == 0)
    {
        RTLOG_writeLog_0(a, b, c, d);
    }
    else {
        RTLOG_writeLog_1(e);
    }
    toggle ^= 1;

}

//
// End of File
//
