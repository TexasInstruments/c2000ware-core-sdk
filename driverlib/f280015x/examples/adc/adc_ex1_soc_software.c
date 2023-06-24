//#############################################################################
//
// FILE:   adc_ex1_soc_software.c
//
// TITLE:  ADC Software Triggering
//
//! \addtogroup driver_example_list
//! <h1>ADC Software Triggering</h1>
//!
//! This example converts some voltages on ADCA and ADCC based on a software
//! trigger.
//!
//! The ADCC will not convert until ADCA is complete, so the ADCs will not run
//! asynchronously. However, this is much less efficient than allowing the ADCs
//! to convert synchronously in parallel (for example, by using an ePWM 
//! trigger).
//!
//! \b External \b Connections \n
//!  - A0, A1, C2, and C3 should be connected to signals to convert
//!
//! \b Watch \b Variables \n
//! - \b myADC0Result0 - Digital representation of the voltage on pin A0
//! - \b myADC0Result1 - Digital representation of the voltage on pin A1
//! - \b myADC1Result0 - Digital representation of the voltage on pin C2
//! - \b myADC1Result1 - Digital representation of the voltage on pin C3
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

//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "board.h"

//
// Globals
//
uint16_t myADC0Result0;
uint16_t myADC0Result1;
uint16_t myADC1Result0;
uint16_t myADC1Result1;

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
    // Set up ADCs, initializing the SOCs to be triggered by software
    //
    Board_init();

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Loop indefinitely
    //
    while(1)
    {
        //
        // Convert, wait for completion, and store results
        //
        ADC_forceMultipleSOC(myADC0_BASE, (ADC_FORCE_SOC0 | ADC_FORCE_SOC1));

        //
        // Wait for ADCA to complete, then acknowledge flag
        //
        while(ADC_getInterruptStatus(myADC0_BASE, ADC_INT_NUMBER1) == false)
        {
        }
        ADC_clearInterruptStatus(myADC0_BASE, ADC_INT_NUMBER1);

        ADC_forceMultipleSOC(myADC1_BASE, (ADC_FORCE_SOC0 | ADC_FORCE_SOC1));
        //
        // Wait for ADCC to complete, then acknowledge flag
        //
        while(ADC_getInterruptStatus(myADC1_BASE, ADC_INT_NUMBER1) == false)
        {
        }
        ADC_clearInterruptStatus(myADC1_BASE, ADC_INT_NUMBER1);

        //
        // Store results
        //
        myADC0Result0 = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER0);
        myADC0Result1 = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER1);
        myADC1Result0 = ADC_readResult(ADCCRESULT_BASE, ADC_SOC_NUMBER0);
        myADC1Result1 = ADC_readResult(ADCCRESULT_BASE, ADC_SOC_NUMBER1);

        //
        // Software breakpoint. At this point, conversion results are stored in
        // myADC0Result0, myADC0Result1, myADC1Result0, and myADC1Result1.
        //
        // Hit run again to get updated conversions.
        //
        ESTOP0;
    }
}
