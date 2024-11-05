//#############################################################################
//
// FILE:    ecap_ex1_apwm.c
//
// TITLE:   eCAP APWM Example.
//
//! \addtogroup bitfield_example_list
//! <h1>eCAP APWM Example</h1>
//!
//! This program sets up the eCAP module in APWM mode. The PWM waveform will
//! come out on GPIO5. The frequency of PWM is configured to vary between 5Hz
//! and 10Hz using the shadow registers to load the next period/compare values.
//
//#############################################################################
//
//
// 
// C2000Ware v5.04.00.00
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
#include "f28x_project.h"

//
// Function Prototypes
//
void InitAPwm1Gpio(void);

//
// Globals
//
uint16_t direction = 0;

void main(void)
{
    //
    // Step 1. Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    //
    InitSysCtrl();

    //
    // Step 2. Initialize GPIO:
    // This example function illustrates how to set the GPIO to 
    // its default state
    //
    // InitGpio();  // Skipped for this example

    //
    // Select eCAP1OUT on OUTPUTXBAR3's MUX 0.
    // Make GPIO5 eCAP1OUT for PWM output.
    //
    InitAPwm1Gpio();

    //
    // Step 3. Clear all __interrupts and initialize PIE vector table:
    // Disable CPU __interrupts
    //
    DINT;

    //
    // Initialize the PIE control registers to their default state.
    // The default state is all PIE __interrupts disabled and flags
    // are cleared.
    //
    InitPieCtrl();

    //
    // Disable CPU __interrupts and clear all CPU __interrupt flags:
    //
    IER = 0x0000;
    IFR = 0x0000;

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    // This will populate the entire table, even if the __interrupt
    // is not used in this example.  This is useful for debug purposes.
    //
    InitPieVectTable();

    //
    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    // No __interrupts used for this example.
    //

    //
    // Step 4. User specific code
    //
    //
    // Setup APWM mode on CAP1, set period and compare registers
    //
    EALLOW;
    ECap1Regs.ECCTL2.bit.CAP_APWM = 1;    // Enable APWM mode
    ECap1Regs.CAP1 = 20000000;            // Set Period value
    ECap1Regs.CAP2 = 10000000;            // Set Compare value
    ECap1Regs.ECCLR.all = 0x0FF;          // Clear pending __interrupts
    ECap1Regs.ECEINT.bit.CTR_EQ_CMP = 1;  // enable Compare Equal Int

    //
    // Start counters
    //
    ECap1Regs.ECCTL2.bit.TSCTRSTOP = 1;

    EDIS;
    for(;;)
    {
        //
        // set next duty cycle to 50%
        //
        ECap1Regs.CAP4 = ECap1Regs.CAP1 >> 1;
        //
        // vary freq
        //
        if(ECap1Regs.CAP1 >= 20000000)
        {
            direction = 0;
        }
        else if (ECap1Regs.CAP1 <= 10000000)
        {
            direction = 1;
        }

        if(direction == 0)
        {
            ECap1Regs.CAP3 = ECap1Regs.CAP1 - 500000;
        }
        else
        {
            ECap1Regs.CAP3 = ECap1Regs.CAP1 + 500000;
        }
    }
}

//
// InitAPwm1Gpio
// Select eCAP1OUT on OUTPUTXBAR3's MUX 0. Make GPIO5 eCAP1OUT for PWM output
//
void InitAPwm1Gpio()
{
    EALLOW;
    OutputXbarRegs.OUTPUT3MUX0TO15CFG.bit.MUX0 = 3; // Select ECAP1.OUT on Mux0
    OutputXbarRegs.OUTPUT3MUXENABLE.bit.MUX0 = 1;  // Enable MUX0 for ECAP1.OUT
    GpioCtrlRegs.GPAGMUX1.bit.GPIO5 = 0; // Select OUTPUTXBAR3 on GPIO5
    GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 3;
    EDIS;
}
//
// End of File
//
