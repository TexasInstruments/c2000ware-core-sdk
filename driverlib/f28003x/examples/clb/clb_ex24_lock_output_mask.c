//#############################################################################
//
// FILE:   clb_ex24_lock_output_mask.c
//
// TITLE:  CLB Lock Output Mask
//
//! \addtogroup driver_example_list
//! <h1>CLB Lock Output Mask</h1>
//!
//! For the detailed description of this example, please refer to:
//!  `C2000Ware_PATH\utilities\clb_tool\clb_syscfg\doc\CLB Tool Users Guide.pdf`
//!
//! In this example the lock outpt mask feature of the CLB is used to lock the 
//! selected output signal override settings. This module is only available for 
//! CLB types 3 and up.
//!
//
//#############################################################################
// $TI Release: F28003x Support Library v5.03.00.00 $
// 
// $Copyright:
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com/
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
    uint32_t outputMask = 0;

    Device_init();
    Device_initGPIO();

    Interrupt_initModule();
    Interrupt_initVectorTable();


    Board_init();

    //
    // The tile configuration is not important for this example
    //
    initTILE1(myCLBForTILE1_BASE);

    CLB_enableCLB(myCLBForTILE1_BASE);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    DEVICE_DELAY_US(1000);
    ESTOP0;

    outputMask = HWREG(myCLBForTILE1_BASE + CLB_LOGICCTL + CLB_O_OUT_EN);
    if (outputMask != 1U << 4U){
        //
        // Output Mask was not set for OUT4
        //
        ESTOP0;
        while(1);
    }

    //
    // Output Mask was set for OUT4
    // let's try to change it while it's locked
    //
    CLB_setOutputMask(myCLBForTILE1_BASE, CLB_OUTPUT_04, false);

    outputMask = HWREG(myCLBForTILE1_BASE + CLB_LOGICCTL + CLB_O_OUT_EN);
    if (outputMask != 1U << 4U){
        //
        // Output Mask was change even though it was locked
        //
        ESTOP0;
        while(1);
    }

    ESTOP0;

    //
    // Output Mask was set for OUT4
    // Enable the writes to OUT_EN then change the mask
    //
    CLB_enableOutputMaskUpdates(myCLBForTILE1_BASE);
    CLB_setOutputMask(myCLBForTILE1_BASE, CLB_OUTPUT_04, false);

    outputMask = HWREG(myCLBForTILE1_BASE + CLB_LOGICCTL + CLB_O_OUT_EN);
    if (outputMask == 1U << 4U){
        //
        // Output Mask was change even though it was locked
        //
        ESTOP0;
        while(1);
    }

    //
    // Success, the lock was diabled and the update took place on the
    // OUT_EN register
    //
    ESTOP0;

    while(1)
    {

    }
}


//
// End of File
//
