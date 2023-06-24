//###########################################################################
//
// FILE:   adc_ex7_ppb_offset.c
//
// TITLE:  ADC offset adjust using post-processing block
//
//! \addtogroup driver_example_list
//! <h1> ADC PPB Offset (adc_ppb_offset)</h1>
//!
//! This example software triggers the ADC.  Some SOCs have automatic offset
//! adjustment applied by the post-processing block. After the program runs,
//! the memory will contain ADC & post-processing block(PPB) results.
//!
//! \b External \b Connections \n
//!  - A2, C2 pins should be connected to signals to convert
//!
//! \b Watch \b Variables \n
//!  - \b myADC0Result \b: a digital representation of the voltage on pin A2
//!  - \b myADC0PPBResult \b : a digital representation of the voltage
//!      on pin A2, minus 100 LSBs of automatically added offset
//!  - \b myADC1Result \b: a digital representation of the voltage on pin C2
//!  - \b myADC1PPBResult \b : a digital representation of the voltage
//!      on pin C2 plus 100 LSBs of automatically added offset
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

//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "board.h"

//
// Globals
//
uint16_t myADC0Result;
uint16_t myADC0PPBResult;
uint16_t myADC1Result;
uint16_t myADC1PPBResult;

void main(void)
{
    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Disable pin locks and enable internal pullups.
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
    // Board Initialization
    // - Configure the ADCs and power them up
    // - Setup the ADCs for software conversions
    // - Setup PPB offset correction.
    //      conversion on channel A will subtract 100.
    //      conversion on channel C will add 100.
    //
    Board_init();

    //
    // Enable global Interrupts and higher priority real-time debug events:
    //
    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global realtime interrupt DBGM

    //
    // Take conversions indefinitely in loop
    //
    do
    {
        //
        // Convert, wait for completion, and store results.
        // Start conversions immediately via software, ADCA
        //
        ADC_forceSOC(myADC0_BASE, ADC_SOC_NUMBER0);
        ADC_forceSOC(myADC0_BASE, ADC_SOC_NUMBER1);

        //
        // Wait for ADCA to complete, then acknowledge flag
        //
        while(ADC_getInterruptStatus(myADC0_BASE, ADC_INT_NUMBER1) == false);
        ADC_clearInterruptStatus(myADC0_BASE, ADC_INT_NUMBER1);

        //
        // Start conversions immediately via software, ADCC
        //
        ADC_forceSOC(myADC1_BASE, ADC_SOC_NUMBER0);
        ADC_forceSOC(myADC1_BASE, ADC_SOC_NUMBER1);

        //
        // Wait for ADCC to complete, then acknowledge flag
        //
        while(ADC_getInterruptStatus(myADC1_BASE, ADC_INT_NUMBER1) == false);
        ADC_clearInterruptStatus(myADC1_BASE, ADC_INT_NUMBER1);

        //
        // Store results
        //
        myADC0Result = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER0);
        myADC0PPBResult = ADC_readPPBResult(ADCARESULT_BASE, ADC_PPB_NUMBER1);
        myADC1Result = ADC_readResult(ADCCRESULT_BASE, ADC_SOC_NUMBER0);
        myADC1PPBResult = ADC_readPPBResult(ADCCRESULT_BASE, ADC_PPB_NUMBER1);

        //
        // Software breakpoint, hit run again to get updated conversions
        //
        asm("   ESTOP0");
    }
    while(1);
}

//
// End of file
//
