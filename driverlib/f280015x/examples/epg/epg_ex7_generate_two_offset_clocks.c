//#############################################################################
//
// FILE:   epg_ex7_generate_two_offset_clocks.c
//
// TITLE:   EPG Generating Two Offset Clocks
//
//! \addtogroup driver_example_list
//! <h1> EPG Generating Two Offset Clocks </h1>
//!
//! This example generates two offset clocks using the CLKGEN (CLKDIV) modules.
//! For more information on this example, visit:
//! [Designing With the C2000 Embedded Pattern Generator 
//! (EPG)](https://www.ti.com/lit/spracy7)
//!
//! \b External \b Connections \n
//!  - None. Signal is generated on GPIO 24, 3. Can be visualized
//!    through oscilloscope.
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

//
// Defines
//
#define CLK_GEN_PERIOD      100U-1U

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
    // Initialize GPIO and configure GPIO pins 24, 3 for EPG OUT
    //
    Device_initGPIO();
    
    GPIO_setPinConfig(GPIO_24_OUTPUTXBAR1);
    GPIO_setDirectionMode(24, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(24, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(24, GPIO_QUAL_SYNC);

    GPIO_setPinConfig(GPIO_3_OUTPUTXBAR2);
    GPIO_setDirectionMode(3, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(3, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(3, GPIO_QUAL_SYNC);

    //
    // Connect EPG Output to GPIO through xbar
    //
    XBAR_setOutputMuxConfig(OUTPUTXBAR_BASE, XBAR_OUTPUT1,
                            XBAR_OUT_MUX30_EPG1_OUT0);
    XBAR_setOutputMuxConfig(OUTPUTXBAR_BASE, XBAR_OUTPUT2,
                            XBAR_OUT_MUX31_EPG1_OUT1);
    XBAR_enableOutputMux(OUTPUTXBAR_BASE, XBAR_OUTPUT1, XBAR_MUX30);
    XBAR_enableOutputMux(OUTPUTXBAR_BASE, XBAR_OUTPUT2, XBAR_MUX31);

    //
    // Select Clock Generator output for EPG output of 0,1
    //
    EPG_selectEPGOutput(EPG1_BASE, EPG_OUT0, EPG_OUT_SEL_CLK);
    EPG_selectEPGOutput(EPG1_BASE, EPG_OUT1, EPG_OUT_SEL_CLK);

    //
    // Select Clock Generator Data output for EPG output of 0,1
    //
    EPG_selectClkOutput(EPG1_BASE, EPG_OUT0, EPG_CLKGEN0_CLKOUT0_DCLK);
    EPG_selectClkOutput(EPG1_BASE, EPG_OUT1, EPG_CLKGEN0_CLKOUT1_DCLK);

    //
    // Set Clock Generator 0 period to CLK_GEN_PERIOD
    //
    EPG_setClkGenPeriod(EPG1_BASE, EPG_CLKGEN0, CLK_GEN_PERIOD);

    //
    // Set offset of clock generator output 0 to 0
    //
    EPG_setClkGenOffset(EPG1_BASE, EPG_CLKGEN0, 0, 0);

    //
    // Set offset of clock generator output 1 to 25
    //
    EPG_setClkGenOffset(EPG1_BASE, EPG_CLKGEN0, 1, 25);

    //
    // Switching from BITBANG mode will disable the clock generation
    //
    //EPG_setSignalGenMode(EPG1_BASE, EPG_SIGGEN0, EPG_SIGGEN_MODE_SHIFT_RIGHT_ONCE);

    //
    // Enable EPG
    //
    EPG_enableGlobal(EPG1_BASE);

    while(1)
    {
        //
        // Delay
        //
        DEVICE_DELAY_US(1000000);
    }

}

//
// End of File
//
