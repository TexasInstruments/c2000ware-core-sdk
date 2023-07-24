//#############################################################################
//
// FILE:   epg_ex1_generate_clocks.c
//
// TITLE:   EPG Generating Synchronous Clocks
//
//! \addtogroup driver_example_list
//! <h1> EPG Generating Synchronous Clocks </h1>
//!
//! This example shows how to generate 2 synchronous clocks with edges being
//! offset by 2 clock cycles. It configures Signal Generator to shift a
//! periodic data. Generated Clock has period EPG CLOCK/6.
//!
//! \b External \b Connections \n
//!  - None. Signal is generated on GPIO 24, 3. Can be visualized
//!    through oscilloscope.
//!
//! \b Watch \b Variables \n
//!  - sigGenActiveData - Active Data of signal generator transform output
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
#define CLK_GEN_PERIOD      0U
#define CLK_GEN_OFFSET      0U
#define SIG_GEN_DATA_LENGTH 12U
#define SIG_GEN_DATA0_0_12  0b000001111110U
#define SIG_GEN_DATA0_16_27 (SIG_GEN_DATA0_0_12 << 2)


//
// Globals
//
uint32_t sigGenActiveData = 0;  //Data transform output

//
// Main
//
void main(void)
{
    uint32_t sigGenData = 0;

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
    // Select Signal Generator output for EPG output of 0,1
    //
    EPG_selectEPGOutput(EPG1_BASE, EPG_OUT0, EPG_OUT_SEL_SIG);
    EPG_selectEPGOutput(EPG1_BASE, EPG_OUT1, EPG_OUT_SEL_SIG);

    //
    // Select Signal Generator output 0,2 for EPG output 0,1
    // This makes sure that bit 0, bit 16 of the transformed data
    // are sent to the output when bit bang is disabled
    //
    EPG_selectSignalOutput(EPG1_BASE, EPG_OUT0, EPG_SIGGEN0_DATATRANOUT0);
    EPG_selectSignalOutput(EPG1_BASE, EPG_OUT1, EPG_SIGGEN0_DATATRANOUT2);

    //
    // Set Clock Generator 0 period to 0 which is divide by 1
    //
    EPG_setClkGenPeriod(EPG1_BASE, EPG_CLKGEN0, CLK_GEN_PERIOD);

    //
    // Set offset of clock generator output 0 to 0
    //
    EPG_setClkGenOffset(EPG1_BASE, EPG_CLKGEN0, 0, CLK_GEN_OFFSET);

    //
    // Set the source of signal generator 0 to clk generator output 0
    //
    EPG_selectSigGenClkSource(EPG1_BASE, EPG_SIGGEN0, EPG_CLKGEN0_CLKOUT0_DCLK);

    //
    // Set signal generator bit length to 12. When it completes
    // shifting of 12 bits, it loads the data0 and data1 registers to
    // to the active data register
    //
    EPG_setDataBitLen(EPG1_BASE, EPG_SIGGEN0, SIG_GEN_DATA_LENGTH);

    //
    // Set signal generator mode to right shift and repeat for 12 bits.
    //
    EPG_setSignalGenMode(EPG1_BASE, EPG_SIGGEN0,
                         EPG_SIGGEN_MODE_ROTATE_RIGHT_REPEAT);
    //
    // Set the first 12 bits of data for signal generator output 0 to
    // generator a 50% duty cycle clock with 1 cycle offset and next
    // 12 bits with 3 cycle offset
    //
    sigGenData = (SIG_GEN_DATA0_0_12 | (uint32_t)SIG_GEN_DATA0_16_27 << 16);
    EPG_setData0Word(EPG1_BASE, EPG_SIGGEN0, sigGenData);

    //
    // Enable EPG
    //
    EPG_enableGlobal(EPG1_BASE);

    //
    // Enable signal generator
    //
    EPG_enableSignalGen(EPG1_BASE, EPG_SIGGEN0);

    while(1)
    {
        sigGenActiveData = EPG_getData0ActiveReg(EPG1_BASE, EPG_SIGGEN0);
        //
        // Delay before reading the transformed data by signal generator
        //
        DEVICE_DELAY_US(1000000);
    }

}

//
// End of File
//
