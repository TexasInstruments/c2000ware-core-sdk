//###########################################################################
//
// FILE:   DSP2803x_HRCap.c
//
// TITLE:  DSP2803x HRCAP Initialization & Support Functions.
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
// InitHRCap - This function initializes the HRCAP(s) to a known state.
//
void 
InitHRCap(void)
{
    //
    // Initialize HRCAP1, HRCAP2
    //
}

//
// InitHRCapGpio - This function initializes GPIO pins to function as ECAP pins
//
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.
//
// Caution:
// For each HRCAP peripheral
// Only one GPIO pin should be enabled for ECAP operation.
// Comment out other unwanted lines.
//
void 
InitHRCapGpio()
{
#if DSP28_HRCAP1
    InitHRCap1Gpio();
#endif
#if DSP28_HRCAP2
    InitHRCap2Gpio();
#endif
}

//
// InitHRCap1Gpio - This function initializes GPIO pins to function as ECAP1
//
void 
InitHRCap1Gpio(void)
{
    EALLOW;
    
    //
    // Enable internal pull-up for the selected pins 
    // Pull-ups can be enabled or disabled by the user.
    // This will enable the pullups for the specified pins.
    // Comment out other unwanted lines.
    //
    //GpioCtrlRegs.GPAPUD.bit.GPIO9 = 0;   // Enable pull-up on GPIO9  (HRCAP1)
    GpioCtrlRegs.GPAPUD.bit.GPIO26 = 0;    // Enable pull-up on GPIO26 (HRCAP1)

    //
    // Set qualification for selected pins to asynch only
    // This will select asynch (no qualification) for the selected pins.
    // Comment out other unwanted lines.
    //
    //GpioCtrlRegs.GPAQSEL1.bit.GPIO9 = 3; //Asynch to SYSCLKOUT GPIO9(HRCAP1)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO26 = 3;  //Asynch to SYSCLKOUT GPIO26(HRCAP1)

    //
    // Configure HRCAP-1 pins using GPIO regs*/
    // This specifies which of the possible GPIO pins will be 
    // HRCAP1 functional pins.
    // Comment out other unwanted lines.
    //
    //GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 3;    // Configure GPIO9 as HRCAP1
    GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 1;    // Configure GPIO26 as GRCAP1

    EDIS;
}

//
// InitHRCap2Gpio -This function initializes GPIO pins to function as ECAP2
//
void
InitHRCap2Gpio(void)
{
    EALLOW;
    
    //
    // Enable internal pull-up for the selected pins 
    // Pull-ups can be enabled or disabled by the user.
    // This will enable the pullups for the specified pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO11 = 0;   // Enable pull-up on GPIO11 (HRCAP2)
    //GpioCtrlRegs.GPAPUD.bit.GPIO27 = 0; // Enable pull-up on GPIO27 (HRCAP2)

    //
    // Set qualification for selected pins to asynch only
    // This will select asynch (no qualification) for the selected pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAQSEL1.bit.GPIO11 = 3;  //Asynch to SYSCLKOUT GPIO11(HRCAP2)
    //GpioCtrlRegs.GPAQSEL2.bit.GPIO27 = 3;//Asynch to SYSCLKOUT GPIO27(HRCAP2)

    //
    // Configure HRCAP-1 pins using GPIO regs
    // This specifies which of the possible GPIO pins will be HRCAP1 functional
    // pins. Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 3;    // Configure GPIO11 as HRCAP2
    //GpioCtrlRegs.GPAMUX2.bit.GPIO27 = 1;    // Configure GPIO27 as HRCAP2

    EDIS;
}

//
// End of file
//

