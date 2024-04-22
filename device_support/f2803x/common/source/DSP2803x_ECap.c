//###########################################################################
//
// FILE:   DSP2803x_ECap.c
//
// TITLE:  DSP2803x eCAP Initialization & Support Functions.
//
//###########################################################################
// $TI Release: $
// $Release Date: $
// $Copyright:
// Copyright (C) 2009-2024 Texas Instruments Incorporated - http://www.ti.com/
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
#include "DSP2803x_Device.h"     // DSP2803x Headerfile Include File
#include "DSP2803x_Examples.h"   // DSP2803x Examples Include File

//
// InitECap - This function initializes the eCAP(s) to a known state.
//
void 
InitECap(void)
{
    //
    // Initialize eCAP1
    //
}

//
// InitECapGpio - This function initializes GPIO pins to function as ECAP pins
//
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.
//
// Caution:
// For each eCAP peripheral
// Only one GPIO pin should be enabled for ECAP operation.
// Comment out other unwanted lines.
//
void 
InitECapGpio()
{
    InitECap1Gpio();
}

void 
InitECap1Gpio(void)
{
    EALLOW;
    //
    // Enable internal pull-up for the selected pins
    // Pull-ups can be enabled or disabled by the user.
    // This will enable the pullups for the specified pins.
    // Comment out other unwanted lines.
    //
    //GpioCtrlRegs.GPAPUD.bit.GPIO5 = 0;    // Enable pull-up on GPIO5 (CAP1)
    GpioCtrlRegs.GPAPUD.bit.GPIO19 = 0;     // Enable pull-up on GPIO19 (CAP1)
    //GpioCtrlRegs.GPAPUD.bit.GPIO24 = 0;   // Enable pull-up on GPIO24 (CAP1)

    //
    // Inputs are synchronized to SYSCLKOUT by default.
    // Comment out other unwanted lines.
    //
    //GpioCtrlRegs.GPAQSEL1.bit.GPIO5 = 0;  // Synch to SYSCLKOUT GPIO5 (CAP1)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = 0;   // Synch to SYSCLKOUT GPIO19 (CAP1)
    //GpioCtrlRegs.GPAQSEL2.bit.GPIO24 = 0; // Synch to SYSCLKOUT GPIO24 (CAP1)
    
    // Configure eCAP-1 pins using GPIO regs
    // This specifies which of the possible GPIO pins will be eCAP1 
    // functional pins.
    // Comment out other unwanted lines.
    //
    //GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 3;   // Configure GPIO5 as CAP1
    GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 3;    // Configure GPIO19 as CAP1
    //GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 1;  // Configure GPIO24 as CAP1

    EDIS;
}

//
// End of file
//

