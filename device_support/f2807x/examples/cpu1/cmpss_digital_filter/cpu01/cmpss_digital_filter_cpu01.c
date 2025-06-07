//###########################################################################
//
// FILE:   cmpss_digital_filter_cpu01.c
//
// TITLE:  CMPSS Digital Filter Example Configuration for F2807x.
//
//! \addtogroup cpu01_example_list
//! <h1> CMPSS Digital Filter </h1>
//!
//! This example enables the CMPSS1 COMPH comparator and feeds the output
//! through the digital filter to the GPIO14/OUTPUTXBAR3 pin.
//!
//! The COMPH inputs are:
//!   - POS signal from CMPIN1P pin
//!   - NEG signal from internal DACH
//!
//
//###########################################################################
//
// $Release Date:  $
// $Copyright:
// Copyright (C) 2014-2025 Texas Instruments Incorporated - http://www.ti.com/
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
#include "F28x_Project.h"

//
// Defines
//
//definitions for selecting DACH reference
#define REFERENCE_VDDA     0
#define REFERENCE_VDAC     1
//definitions for COMPH input selection
#define NEGIN_DAC          0
#define NEGIN_PIN          1
//definitions for CTRIPH/CTRIPOUTH output selection
#define CTRIP_ASYNCH       0
#define CTRIP_SYNCH        1
#define CTRIP_FILTER       2
#define CTRIP_LATCH        3
//definitions for selecting output pin
#define GPIO_PIN_NUM      14 //OUTPUTXBAR3 is mux'd with GPIO14
#define GPIO_PER_NUM       6 //OUTPUTXBAR3 is peripheral option 6 for GPIO14

//
// Function Prototypes
//
void InitCMPSS(void);

//
// Main
//
void main(void)
{
//
// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the F2807x_SysCtrl.c file.
//
    InitSysCtrl();

//
// Step 2. Initialize GPIO:
// This example function is found in the F2807x_Gpio.c file and
// illustrates how to set the GPIO to it's default state.
//
    InitGpio();

//
// Step 3. Clear all interrupts and initialize PIE vector table:
// Disable CPU interrupts
//
    DINT;

//
// Initialize the PIE control registers to their default state.
// The default state is all PIE interrupts disabled and flags
// are cleared.
// This function is found in the F2807x_PieCtrl.c file.
//
    InitPieCtrl();

//
// Disable CPU interrupts and clear all CPU interrupt flags:
//
    IER = 0x0000;
    IFR = 0x0000;

//
// Configure Comparator COMP1H to accept POS input from pin and NEG
// input from DAC
//
    InitCMPSS();

//
// Configure GPIO14 to output CTRIPOUT1H
//
    GPIO_SetupPinMux(GPIO_PIN_NUM, GPIO_MUX_CPU1, GPIO_PER_NUM);

//
// Observe filtered output on pin
//
    while(1);
}

//
// InitCMPSS - Initialize CMPSS1 and configure values
//
void InitCMPSS(void)
{
    EALLOW;

    //
    //Enable CMPSS
    //
    Cmpss1Regs.COMPCTL.bit.COMPDACE = 1;

    //
    //NEG signal comes from DAC
    //
    Cmpss1Regs.COMPCTL.bit.COMPHSOURCE = NEGIN_DAC;

    //
    //Use VDDA as the reference for DAC
    //
    Cmpss1Regs.COMPDACCTL.bit.SELREF = REFERENCE_VDDA;

    //
    //Set DAC to midpoint for arbitrary reference
    //
    Cmpss1Regs.DACHVALS.bit.DACVAL = 2048;

    //
    // Configure Digital Filter
    //Maximum CLKPRESCALE value provides the most time between samples
    //
    Cmpss1Regs.CTRIPHFILCLKCTL.bit.CLKPRESCALE = 0x3FF;

    //
    //Maximum SAMPWIN value provides largest number of samples
    //
    Cmpss1Regs.CTRIPHFILCTL.bit.SAMPWIN = 0x1F;

    //
    //Maximum THRESH value requires static value for entire window
    //  THRESH should be GREATER than half of SAMPWIN
    //
    Cmpss1Regs.CTRIPHFILCTL.bit.THRESH = 0x1F;

    //
    //Reset filter logic & start filtering
    //
    Cmpss1Regs.CTRIPHFILCTL.bit.FILINIT = 1;

    //
    // Configure CTRIPOUT path
    // Digital filter output feeds CTRIPH and CTRIPOUTH
    //
    Cmpss1Regs.COMPCTL.bit.CTRIPHSEL = CTRIP_FILTER;
    Cmpss1Regs.COMPCTL.bit.CTRIPOUTHSEL = CTRIP_FILTER;

    //
    // Configure CTRIPOUTH output pin
    //Configure OUTPUTXBAR3 to be CTRIPOUT1H
    //
    OutputXbarRegs.OUTPUT3MUX0TO15CFG.all &= ~((Uint32)1);

    //
    //Enable OUTPUTXBAR3 Mux for Output
    //
    OutputXbarRegs.OUTPUT3MUXENABLE.all |= (Uint32)1;
    EDIS;
}

//
// End of file
//
