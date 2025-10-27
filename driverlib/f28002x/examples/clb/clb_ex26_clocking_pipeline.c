//#############################################################################
//
// FILE:   clb_ex26_clocking_pipeline.c
//
// TITLE:  CLB Clocking and PIPELINE Mode
//
//! \addtogroup driver_example_list
//! <h1>CLB Clocking and PIPELINE Mode</h1>
//!
//! For the detailed description of this example, please refer to:
//!  `C2000Ware_PATH\utilities\clb_tool\clb_syscfg\doc\CLB Tool Users Guide.pdf`
//!
//! In this example the CLB pipeline mode is enable and affects the behavior 
//! of the CLB COUNTERs and HLC. This module is only available for CLB types 
//! 3 and up.
//!
//
//#############################################################################
// $TI Release: F28004x Support Library v6.00.01.00 $
// 
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
#include "clb_config.h"

//
// Main
//
void main(void)
{
    //
    // The counter value for a CLB without PIPELINE Mode Enabled
    //
    uint32_t counterValueWithoutPipelineMode = 0;

    //
    // The counter value for a CLB with PIPELINE Mode Enabled
    //
    uint32_t counterValueWitPipelineMode = 0;

    Device_init();
    Device_initGPIO();

    Interrupt_initModule();
    Interrupt_initVectorTable();


    Board_init();

    //
    // The tile configuration is:
    // TILE1:
    // PIPELINE MODE
    // COUNTER 0 configured to match at 62,500,000 counts
    // FSM to toggle at COUNTER0 match
    // CLB OUTPUT XBAR will show the output on GPIO
    //
    // COUNTER 2 will count to 64 then trigger an ADD-5
    // With PIPELINE enabled, counter will use previous counter value
    //
    initTILE1(myCLBForTILE1_BASE);

    //
    // The tile configuration is:
    // TILE2:
    // NO PIPELINE
    // COUNTER 2 will count to 64 then trigger an ADD-5
    // With PIPELINE enabled, counter will use current counter value
    //
    initTILE2(myCLBForTILE2_BASE);

    CLB_enableCLB(myCLBForTILE1_BASE);
    CLB_enableCLB(myCLBForTILE2_BASE);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    DEVICE_DELAY_US(1000000);

    counterValueWithoutPipelineMode = CLB_getRegister(myCLBForTILE2_BASE, CLB_REG_CTR_C2);
    counterValueWitPipelineMode = CLB_getRegister(myCLBForTILE1_BASE, CLB_REG_CTR_C2);

    if (counterValueWithoutPipelineMode != counterValueWitPipelineMode + 1)
    {
        ESTOP0;

        //
        // Error with pipeline, the value should be 1 less
        //
        while(1);
    }

    //
    // Success
    //
    ESTOP0;

    //
    // Keep running and view CLB OUTPUT XBAR GPIO
    //
    while(1)
    {

    }
}


//
// End of File
//
