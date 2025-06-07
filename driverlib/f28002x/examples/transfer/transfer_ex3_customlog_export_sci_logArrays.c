//#############################################################################
//
// FILE:   transfer_ex3_customlog_export_sci_logArrays.c
//
// TITLE:  Transfer: Custom Logger Solution
//
//! \addtogroup driver_example_list
//! <h1> GUI based solution for data logging (one direction) </h1>
//!
//! This example demonstrates how to use SysConfig to enable datalogging
//! on our C28x devices. To enable this example, make sure to go to
//! Build -> Variables and set GUI_SUPPORT to value of 1.
//! This will create the GUI in CCS which can be opened under 
//! View -> GUI Composer -> Applications -> 
//!                                    transfer_ex3_customlog_export_sci_logArrays
//!
//! In this example, we are using SCI to export data out of the device. We
//! export a few arrays to show case this example.
//! If you're using a launchpad, you can enable board components to select
//! the correct SCI base to visualize the data through the COM port.
//!
//
//#############################################################################
// $Copyright:
// Copyright (C) 2025 Texas Instruments Incorporated - http://www.ti.com/
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
#include "export/export_log.h"

uint32_t  u32Arr [3] = {15689, 99, 98623156};
int32_t   i32Arr [3] = {-25555, 98952, -45632};
float     f32Arr [3] = {60233.36, 0.99, -3156.005};
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
    EXPORTLOG_init();

    //
    // Enable Global Interrupt (INTM) and real time interrupt (DBGM)
    //
    EINT;
    ERTM;

    while(1)
    {
        DEVICE_DELAY_US(1000000);

        EXPORTLOG_log("Logging UInt32 array");
        EXPORTLOG_logUint32Array(u32Arr, 3);
        EXPORTLOG_log("Logging Int32 array");
        EXPORTLOG_logInt32Array(i32Arr, 3);
        EXPORTLOG_log("Logging float32 array (4 decimal points)");
        EXPORTLOG_logFloat32Array(f32Arr, 3, 4);
    }
}


//
// End of File
//

