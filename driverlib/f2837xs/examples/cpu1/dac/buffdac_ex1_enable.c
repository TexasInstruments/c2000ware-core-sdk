//#############################################################################
//
// FILE:   buffdac_ex1_enable.c
//
// TITLE:   Buffered DAC Enable Output Example
//
//! \addtogroup driver_example_list
//! <h1> Buffered DAC Enable </h1>
//!
//! This example generates a voltage on the buffered DAC output,
//! DACOUTA/ADCINA0 and uses the default DAC reference setting of
//! VDAC.
//!
//! \b External \b Connections \n
//!  - When the DAC reference is set to VDAC, an external reference voltage
//!    must be applied to the VDAC pin. This can be accomplished by connecting a
//!    jumper wire from 3.3V to ADCINB0.
//!
//! \b Watch \b Variables \n
//!  - None.
//!
//
//#############################################################################
//
// $Release Date: $
// $Copyright:
// Copyright (C) 2014-2023 Texas Instruments Incorporated - http://www.ti.com/
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
// Globals
//
uint16_t dacVal = 2048;

//
// Function Prototypes
//
void configureDAC(void);

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
    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // Configure the DAC module
    //
    configureDAC();

    //
    // Continuously set the DAC output value
    //
    while(1)
    {
        DAC_setShadowValue(DACA_BASE, dacVal);
        DEVICE_DELAY_US(2);
    }
}

//
// Configure DAC - Setup the reference voltage and output value for the DAC
//
void
configureDAC(void)
{
    //
    // Set VDAC as the DAC reference voltage.
    // Edit here to use ADC VREF as the reference voltage.
    //
    DAC_setReferenceVoltage(DACA_BASE, DAC_REF_VDAC);

    //
    // Enable the DAC output
    //
    DAC_enableOutput(DACA_BASE);

    //
    // Set the DAC shadow output to 0
    //
    DAC_setShadowValue(DACA_BASE, 0);

    //
    // Delay for buffered DAC to power up
    //
    DEVICE_DELAY_US(10);
}

//
// End of File
//
