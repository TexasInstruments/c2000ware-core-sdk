//#############################################################################
//
// FILE:   pga_ex1_dac_adc_ext_loopback.c
//
// TITLE:   PGA CMPSSDAC-ADC External Loopback Example.
//
//! \addtogroup driver_example_list
//! <h1>PGA CMPSSDAC-ADC External Loopback Example</h1>
//!
//! This example generates 800 mV using the CMPSSDAC output. CMPSSLITE is used
//! route the low DAC output to an external pin to be used as an external DAC.
//! The output of the CMPSS LITE DACL is externally connected to PGA for 2x gain
//! amplification. It uses two ADC channels to sample the CMPSSDAC output and
//! the amplified voltage output from PGA. The ADC is connected internally to
//! these signals.
//!
//! \b External \b Connections \n
//!  - Connect CMPSSLITE_DACL_OUT (Analog Pin A0) to PGA1_INP1 (Analog Pin A11)
//!  - Connect PGA1_INM1 (Analog Pin A4) to GND
//!
//! \b Watch \b Variables \n
//!  - \b dacResult - The DAC output voltage.
//!  - \b pgaResult - The amplified DAC voltage.
//!  - \b pgaGain   - The ratio of the amplified DAC voltage to the original
//!                   DAC output. This should always read a value of ~2.0.
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

//
// Globals
//
volatile uint16_t dacResult;
volatile uint16_t pgaResult;
float pgaGain;

//
// Main
//
void main(void)
{
    //
    // Initialize device clock and peripherals
    //
    Device_init();

    Board_init();

    PGA_enableOutput(myPGA0_BASE);
    PGA_enableInternalGainOutput(myPGA0_BASE);

    //
    // Enable Global Interrupt (INTM) and real time interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Force ADC conversion
    //
    ADC_forceSOC(myADC0_BASE, ADC_SOC_NUMBER0);
    ADC_forceSOC(myADC0_BASE, ADC_SOC_NUMBER1);

    //
    // Loop indefinitely
    //
    while(1)
    {
        //
        // Check if conversion is complete
        //
        if(ADC_getInterruptStatus(myADC0_BASE, ADC_INT_NUMBER1))
        {
            //
            // Acknowledge flag
            //
            ADC_clearInterruptStatus(myADC0_BASE, ADC_INT_NUMBER1);

            dacResult = ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER0);
            pgaResult = ADC_readResult(myADC0_RESULT_BASE, ADC_SOC_NUMBER1);
            pgaGain   = (float)pgaResult / (float)dacResult;

            //
            // Force ADC conversion
            //
            ADC_forceSOC(myADC0_BASE, ADC_SOC_NUMBER0);
            ADC_forceSOC(myADC0_BASE, ADC_SOC_NUMBER1);
        }
    }
}

//
// End of File
//
