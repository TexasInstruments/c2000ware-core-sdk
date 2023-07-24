//###########################################################################
//
// FILE:   adc_ex4_soc_software_sync.c
//
// TITLE:  ADC synchronous software triggering
//
//! \addtogroup driver_example_list
//! <h1> ADC Synchronous SOC Software Force (adc_soc_software_sync)</h1>
//!
//! This example converts some voltages on ADCA and ADCC using input 5 of the
//! input X-BAR as a software force. Input 5 is triggered by toggling GPIO0,
//! but any spare GPIO could be used. This method will ensure that both ADCs
//! start converting at exactly the same time.
//!
//! \b External \b Connections \n
//!  - A2, A3, C2, C3 pins should be connected to signals to convert
//!
//! \b Watch \b Variables \n
//! - \b myADC0Result0 \b: a digital representation of the voltage on pin A2\n
//! - \b myADC0Result1 \b: a digital representation of the voltage on pin A3\n
//! - \b myADC1Result0 \b: a digital representation of the voltage on pin C2\n
//! - \b myADC1Result1 \b: a digital representation of the voltage on pin C3\n
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
    // - Write ADC configurations and power up the ADC for both ADC A and ADC C
    // - Setup GPIO 0 to trigger input XBAR line 5.  GPIO0 is used
    //   as an example, but any spare GPIO could be used. The
    //   physical GPIO pin should be allowed to float, since the
    //   code configures it as an output and changes the value.
    // - Setup ADC acquisition window and compare values
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
        // Convert, wait for completion, and store results
        //

        //
        // Toggle GPIO0 in software.  This will cause a trigger to
        // both ADCs via input XBAR, line 5.
        //
        GPIO_writePin(0U, 1U); // Set pin
        GPIO_writePin(0U, 0U); // Clear pin

        //
        // Wait for ADCA to complete, then acknowledge the flag.
        // Since both ADCs are running synchronously, it isn't necessary
        // to wait for completion notification from both ADCs
        //
        while(ADC_getInterruptStatus(myADC0_BASE, ADC_INT_NUMBER1) == 0U);
        ADC_clearInterruptStatus(myADC0_BASE, ADC_INT_NUMBER1);

        //
        // Store results
        //
        myADC0Result0 = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER0);
        myADC0Result1 = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER1);
        myADC1Result0 = ADC_readResult(ADCCRESULT_BASE, ADC_SOC_NUMBER0);
        myADC1Result1 = ADC_readResult(ADCCRESULT_BASE, ADC_SOC_NUMBER1);

        //
        // At this point, conversion results are stored in
        // myADC0Result0, myADC0Result1, myADC1Result0, and myADC1Result1
        //

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
