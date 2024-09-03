//#############################################################################
//
// FILE:   transfer_comslogger_export_sci.c
//
// TITLE:  Transfer: Communication Logger
//
//! \addtogroup driver_example_list
//! <h1> Solution for interpreting communication peripheral messages </h1>
//!
//! This example can be loaded for a bridge device that is taking in FSI 
//! and outputting SCI. For this example, you can use the already built-in
//! XDS UART or SCI to USB on a launchpad or controlCARD to view the output.
//! This example works in conjunction with the transfer_raw_fsi_tx example.
//! Flash the bridge device with this application code, and run the 
//! transfer_raw_fsi_tx example from another device.
//! 
//! In this example, we are using SCI to export data out of the device while
//! receiving FSI as the input. We can then visualize the FSI packets in a 
//! GUI.
//! View -> GUI Composer -> Applications -> 
//!                                     transfer_comslogger_export_sci
//! If you're using a launchpad, you can enable board components to select
//! the correct SCI base to visualize the data through the COM port.
//!
//
//#############################################################################
// 
// C2000Ware v5.03.00.00
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
#include "export/export.h"
#include "logger/coms_logger.h"


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
    EXPORT_init();
    COMSLOG_init();

    //
    // Enable Global Interrupt (INTM) and real time interrupt (DBGM)
    //
    EINT;
    ERTM;

    while(1)
    {
        COMSLOG_transferBufferData();
    }
}

void COMSLOG_transferBufferOverflow() {

    //
    // Received too much data too quickly. The transfer buffer overflowed
    // Make the buffer larger
    //
    ESTOP0;

}

void COMSLOG_comsLinkError(uint16_t status) {

    //
    // FSI receive error occurred
    // Bad frames received
    //
    ESTOP0;
}



//
// End of File
//
