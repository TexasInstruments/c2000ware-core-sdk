//#############################################################################
//
// FILE:   epg_ex8_generate_two_offset_clocks_with_siggen.c
//
// TITLE:   EPG Generating Two Offset Clocks With SIGGEN
//
//! \addtogroup driver_example_list
//! <h1> EPG Generating Two Offset Clocks With SIGGEN </h1>
//!
//! This example generates two offset clocks using the SIGGEN module.
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

#define TEN_BIT         0
#define TWENTY_BIT      1
#define BIT_LENGTH_MODE TWENTY_BIT

//
// Defines
//
#if BIT_LENGTH_MODE == TEN_BIT

#define CLK_GEN_PERIOD      10U-1U
#define SIG_GEN_DATA_LENGTH 10U
#define SIG_GEN_DATA0_0_10  0b0000011111U
#define SIG_GEN_DATA0_16_27 (SIG_GEN_DATA0_0_10 << 2)

//
// Uncomment to offset by 3
//
// #define SIG_GEN_DATA0_16_27 (SIG_GEN_DATA0_0_10 << 3)

#else

#define CLK_GEN_PERIOD      5U-1U
#define SIG_GEN_DATA_LENGTH 20U
#define SIG_GEN_DATA0_0_20  0b00000000001111111111U
#define SIG_GEN_DATA1_0_20 (SIG_GEN_DATA0_0_20 << 5)

#endif
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
    // Select Signal Generator output for EPG output of 0,1
    //
    EPG_selectEPGOutput(EPG1_BASE, EPG_OUT0, EPG_OUT_SEL_SIG);
    EPG_selectEPGOutput(EPG1_BASE, EPG_OUT1, EPG_OUT_SEL_SIG);


    EPG_selectSignalOutput(EPG1_BASE, EPG_OUT0, EPG_SIGGEN0_DATATRANOUT0);

#if BIT_LENGTH_MODE == TEN_BIT
    EPG_selectSignalOutput(EPG1_BASE, EPG_OUT1, EPG_SIGGEN0_DATATRANOUT2);
#else
    EPG_selectSignalOutput(EPG1_BASE, EPG_OUT1, EPG_SIGGEN0_DATATRANOUT4);
#endif

    //
    // Set Clock Generator 0 period
    //
    EPG_setClkGenPeriod(EPG1_BASE, EPG_CLKGEN0, CLK_GEN_PERIOD);

    //
    // Set the source of signal generator 0 to clk generator output 0
    //
    EPG_selectSigGenClkSource(EPG1_BASE, EPG_SIGGEN0, EPG_CLKGEN0_CLKOUT0_GCLK);

    //
    // Set offset of clock generator output 0 to 0
    //
    EPG_setClkGenOffset(EPG1_BASE, EPG_CLKGEN0, 0, 0);


    //
    // Set signal generator bit length
    //
    EPG_setDataBitLen(EPG1_BASE, EPG_SIGGEN0, SIG_GEN_DATA_LENGTH);

    //
    // Set signal generator mode to right shift and repeat.
    //
    EPG_setSignalGenMode(EPG1_BASE, EPG_SIGGEN0,
                         EPG_SIGGEN_MODE_ROTATE_RIGHT_REPEAT);

#if BIT_LENGTH_MODE == TEN_BIT
    EPG_setData0Word(EPG1_BASE, EPG_SIGGEN0, (SIG_GEN_DATA0_0_10 | (uint32_t)SIG_GEN_DATA0_16_27 << 16));
#else
    EPG_setData0Word(EPG1_BASE, EPG_SIGGEN0, SIG_GEN_DATA0_0_20);
    EPG_setData1Word(EPG1_BASE, EPG_SIGGEN0, SIG_GEN_DATA1_0_20);
#endif

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
        //
        // Delay
        //
        DEVICE_DELAY_US(1000000);
    }

}

//
// End of File
//
