//###########################################################################
//
// FILE:   Example_2833xECap_apwm.c
//
// TITLE:  eCAP APWM Example
//
//! \addtogroup f2833x_example_list
//! <h1>eCAP APWM (ecap_epwm)</h1>
//!
//! This program sets up eCAP pins in the APWM mode.
//! This program runs at 150 MHz SYSCLKOUT assuming a 30 MHz
//! XCLKIN or 100 MHz SYSCLKOUT assuming a 20 MHz XCLKIN. \n
//! For 150 MHz devices: \n
//! 	- eCAP1 will come out on the GPIO24 pin.
//! 	This pin is configured to vary between 7.5 Hz and 15 Hz using
//! the shadow registers to load the next period/compare values. \n
//! 	- eCAP2 will come out on the GPIO7 pin.
//! This pin is configured as a 7.5 Hz output. \n
//! 	- eCAP3 will come out on the GPIO9 pin.
//! This pin is configured as a 1.5 Hz output. \n
//! 	- eCAP4 will come out on the GPIO11 pin.
//! This pin is configured as a 30 kHz output. \n
//! 	- All frequencies assume a 30 Mhz input clock. The XCLKOUT pin
//! should show 150Mhz. \n
//!
//! For 100 MHz devices: \n
//! 	- eCAP1 will come out on the GPIO24 pin.
//! 	This pin is configured to vary between 5 Hz and 10 Hz using
//! the shadow registers to load the next period/compare values. \n
//! 	- eCAP2 will come out on the GPIO7 pin.
//! 	This pin is configured as a 5 Hz output. \n
//! 	- eCAP3 will come out on the GPIO9 pin.
//! 	This pin is configured as a 1 Hz output. \n
//! 	- eCAP4 will come out on the GPIO11 pin.
//! 	This pin is configured as a 20kHz output. \n
//! 	- All frequencies assume a 20 Mhz input clock. The XCLKOUT pin
//! should show 100Mhz.
//
//
//###########################################################################
// $TI Release: $
// $Release Date: $
// $Copyright:
// Copyright (C) 2009-2025 Texas Instruments Incorporated - http://www.ti.com/
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
//###########################################################################

//
// Included Files
//
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File

//
// Globals
//
Uint16 direction = 0;

//
// Main
//
void main(void)
{
    //
    // Step 1. Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    // This example function is found in the DSP2833x_SysCtrl.c file.
    //
    InitSysCtrl();

    //
    // Step 2. Initialize GPIO:
    // This example function is found in the DSP2833x_Gpio.c file and
    // illustrates how to set the GPIO to it's default state.
    //
    // InitGpio();  // Skipped for this example

    //
    // Initialize the GPIO pins for eCAP.
    // This function is found in the DSP2833x_ECap.c file
    //
    InitECapGpio();

    //
    // Step 3. Clear all interrupts and initialize PIE vector table:
    // Disable CPU interrupts
    //
    DINT;

    //
    // Initialize the PIE control registers to their default state.
    // The default state is all PIE interrupts disabled and flags
    // are cleared.
    // This function is found in the DSP2833x_PieCtrl.c file.
    //
    InitPieCtrl();

    //
    // Disable CPU interrupts and clear all CPU interrupt flags
    //
    IER = 0x0000;
    IFR = 0x0000;

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    // This will populate the entire table, even if the interrupt
    // is not used in this example.  This is useful for debug purposes.
    // The shell ISR routines are found in DSP2833x_DefaultIsr.c.
    // This function is found in DSP2833x_PieVect.c.
    //
    InitPieVectTable();

    //
    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file. 
    // No interrupts used for this example.
    //

    //
    // Step 4. Initialize all the Device Peripherals:
    // This function is found in DSP2833x_InitPeripherals.c
    //
    // InitPeripherals(); // Not required for this example

    //
    // Step 5. User specific code
    // Setup APWM mode on CAP1, set period and compare registers
    //
    ECap1Regs.ECCTL2.bit.CAP_APWM = 1;	    // Enable APWM mode
    ECap1Regs.CAP1 = 0x01312D00;			// Set Period value
    ECap1Regs.CAP2 = 0x00989680;			// Set Compare value
    ECap1Regs.ECCLR.all = 0x0FF;			// Clear pending interrupts
    ECap1Regs.ECEINT.bit.CTR_EQ_CMP = 1;    // enable Compare Equal Int

    //
    // Setup APWM mode on CAP2, set period and compare registers
    //
    ECap2Regs.ECCTL2.bit.CAP_APWM = 1;	    // Enable APWM mode
    ECap2Regs.CAP1 = 0x01312D00;			// Set Period value
    ECap2Regs.CAP2 = 0x00989680;			// Set Compare value
    ECap2Regs.ECCLR.all = 0x0FF;			// Clear pending interrupts
    ECap1Regs.ECEINT.bit.CTR_EQ_CMP = 1;    // enable Compare Equal Int

    //
    // Setup APWM mode on CAP3, set period and compare registers
    //
    ECap3Regs.ECCTL2.bit.CAP_APWM = 1;	    // Enable APWM mode
    ECap3Regs.CAP1 = 0x05F5E100;			// Set Period value
    ECap3Regs.CAP2 = 0x02FAF080;			// Set Compare value
    ECap3Regs.ECCLR.all = 0x0FF;			// Clear pending interrupts
    ECap1Regs.ECEINT.bit.CTR_EQ_CMP = 1;    // enable Compare Equal Int

    //
    // Setup APWM mode on CAP4, set period and compare registers
    //
    ECap4Regs.ECCTL2.bit.CAP_APWM = 1;	    // Enable APWM mode
    ECap4Regs.CAP1 = 0x00001388;			// Set Period value
    ECap4Regs.CAP2 = 0x000009C4;			// Set Compare value
    ECap4Regs.ECCLR.all = 0x0FF;			// Clear pending interrupts
    ECap1Regs.ECEINT.bit.CTR_EQ_CMP = 1;    // enable Compare Equal Int

    //
    // Start counters
    //
    ECap1Regs.ECCTL2.bit.TSCTRSTOP = 1;
    ECap2Regs.ECCTL2.bit.TSCTRSTOP = 1;
    ECap3Regs.ECCTL2.bit.TSCTRSTOP = 1;
    ECap4Regs.ECCTL2.bit.TSCTRSTOP = 1;

    for(;;)
    {
        //
        // set next duty cycle to 50%
        //
        ECap1Regs.CAP4 = ECap1Regs.CAP1 >> 1;

        //
        // vary freq between 7.5 Hz and 15 Hz (for 150MHz SYSCLKOUT) 
        // 5 Hz and 10 Hz (for 100 MHz SYSCLKOUT)
        //
        if(ECap1Regs.CAP1 >= 0x01312D00)
        {
            direction = 0;
        } 
        else if (ECap1Regs.CAP1 <= 0x00989680)
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
// End of File
//

