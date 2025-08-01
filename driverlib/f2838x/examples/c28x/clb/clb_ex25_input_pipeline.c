//#############################################################################
//
// FILE:   clb_ex25_input_pipeline.c
//
// TITLE:  CLB INPUT Pipeline Mode
//
//! \addtogroup driver_example_list
//! <h1>CLB INPUT Pipeline Mode</h1>
//!
//! For the detailed description of this example, please refer to:
//!  `C2000Ware_PATH\utilities\clb_tool\clb_syscfg\doc\CLB Tool Users Guide.pdf`
//!
//! In this example the CLB Input Pipeline mode is enable to delay the input 
//! signal by a clock cycle. This module is only available for CLB types 3 and up.
//!
//
//#############################################################################
// $TI Release: $
// 
// 
// C2000Ware v6.00.00.00
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
#include "clb_config.h"

#define INPUT_WITHOUT_PIPELINE_MODE CLB_IN1
#define INPUT_WITH_PIPELINE_MODE    CLB_IN2

//
// Main
//
void main(void)
{
    uint32_t delayBetweenInputs = 0;

    Device_init();
    Device_initGPIO();

    Interrupt_initModule();
    Interrupt_initVectorTable();


    Board_init();

    //
    // The tile configuration is:
    // LUT0 is only high when -> IN1 is high and IN0 is LOW
    // LUT0 output (when high) enables the COUNTER0 to count up
    //
    initTILE1(myCLBForTILE1_BASE);

    CLB_enableCLB(myCLBForTILE1_BASE);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Set both inputs to capture the delay between them in the counter value
    //
    CLB_setGPREG(myCLBForTILE1_BASE,
                 (1 << INPUT_WITH_PIPELINE_MODE) |
                 (1 << INPUT_WITHOUT_PIPELINE_MODE));

    //
    // Read C0 to get the counter value reflecting the delay between the INPUTs
    //
    delayBetweenInputs = CLB_getRegister(myCLBForTILE1_BASE, CLB_REG_CTR_C0);

    //
    // The input WITH pipeline mode enabled with capture the counter
    // one cycle later than the input WITHOUT pipeline mode enabled
    //
    if (delayBetweenInputs != 1)
    {
        //
        // Error, the captured counter value is not 1 cycle
        //
        ESTOP0;
        while(1);
    }

    //
    // Success the counter value captured delay between pipeline mode enabled input
    // and without pipeline mode enabled input
    //
    ESTOP0;

    while(1)
    {

    }
}


//
// End of File
//
