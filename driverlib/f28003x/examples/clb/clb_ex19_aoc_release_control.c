//#############################################################################
//
// FILE:   clb_ex19_aoc_release_control.c
//
// TITLE:  CLB AOC Release Control Example
//
//! \addtogroup driver_example_list
//! <h1>CLB AOC Release Control</h1>
//!
//! For the detailed description of this example, please refer to:
//!  `C2000Ware_PATH\utilities\clb_tool\clb_syscfg\doc\CLB Tool Users Guide.pdf`
//!
//! In this example the Asynchronous Output Conditioning block is used to 
//! asynchronously set/release the input signals to the CLB. This module is 
//! only available for CLB types 2 and up.
//!
//
//#############################################################################
// $TI Release: F28003x Support Library v5.00.00.00 $
// $Release Date: 11-17-2023 $
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
#include "clb_config.h"

//
// Main
//
void main(void)
{
    Device_init();
    Device_initGPIO();

    Interrupt_initModule();
    Interrupt_initVectorTable();

    Board_init();

    //
    // Implement Pass through GPIO0
    // Implement AOC does not invert
    // Implement AOC Gate Control is in bypass
    // AOC Release Control will be in CLEAR mode with SW RLS control
    //
    initTILE1(myCLBForTILE1_BASE);

    CLB_enableCLB(myCLBForTILE1_BASE);


    while(1)
    {
        DEVICE_DELAY_US(5000000);

        //
        // After this function executes, the state of the FLOP in the AOC
        // is set to HIGH.
        //
        CLB_writeSWReleaseControl(myCLBForTILE1_BASE, CLB_SW_RLS_CTRL4, true);

        //
        // Now that the output is set to HIGH, a rising edge in the CLB_OUT4
        // signal will cause a CLEAR of the output.
        //

        GPIO_writePin(myGPIO1Output, 1);

        DEVICE_DELAY_US(5000000);

        //
        // Clear the release signal, making it ready for the next write to SW
        // RLS register to cause a RISING EDGE.
        //
        CLB_writeSWReleaseControl(myCLBForTILE1_BASE, CLB_SW_RLS_CTRL4, false);
        GPIO_writePin(myGPIO1Output, 0);
    }
}

//
// End of File
//
