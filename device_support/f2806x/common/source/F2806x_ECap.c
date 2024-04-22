//###########################################################################
//
// FILE:   F2806x_ECap.c
//
// TITLE:  F2806x eCAP Initialization & Support Functions.
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
#include "F2806x_Device.h"     // F2806x Headerfile Include File
#include "F2806x_Examples.h"   // F2806x Examples Include File

//
// InitECap - This function initializes the eCAP(s) to a known state.
//
void
InitECap(void)
{
    //
    // Initialize eCAP1/2/3
    //
}

//
// InitECapGpio - This function initializes GPIO pins to function as ECAP pins
//
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.
//
// Caution: For each eCAP peripheral
// Only one GPIO pin should be enabled for ECAP operation.
// Comment out other unwanted lines.
//
void
InitECapGpio()
{
    #if DSP28_ECAP1
        InitECap1Gpio();
    #endif // endif DSP28_ECAP1
    #if DSP28_ECAP2
        InitECap2Gpio();
    #endif // endif DSP28_ECAP2
    #if DSP28_ECAP3
        InitECap3Gpio();
    #endif // endif DSP28_ECAP3
}

#if DSP28_ECAP1
//
// InitECap1Gpio - 
//
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
    GpioCtrlRegs.GPAPUD.bit.GPIO5 = 0;		// Enable pull-up on GPIO5 (CAP1)
    //GpioCtrlRegs.GPAPUD.bit.GPIO11 = 0;   // Enable pull-up on GPIO11 (CAP1)
    //GpioCtrlRegs.GPAPUD.bit.GPIO19 = 0;	// Enable pull-up on GPIO19 (CAP1)
    //GpioCtrlRegs.GPAPUD.bit.GPIO24 = 0;   // Enable pull-up on GPIO24 (CAP1)

    //
    // Inputs are synchronized to SYSCLKOUT by default.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAQSEL1.bit.GPIO5 = 0;	// Synch to SYSCLKOUT GPIO5 (CAP1)
    //GpioCtrlRegs.GPAQSEL1.bit.GPIO11 = 0; // Synch to SYSCLKOUT GPIO11 (CAP1)
    //GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = 0;	// Synch to SYSCLKOUT GPIO19 (CAP1)
    //GpioCtrlRegs.GPAQSEL2.bit.GPIO24 = 0; // Synch to SYSCLKOUT GPIO24 (CAP1)

    //
    // Configure eCAP-1 pins using GPIO regs
    // This specifies which of the possible GPIO pins will be eCAP1 functional 
    // pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 3;		// Configure GPIO5 as CAP1
    //GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 3;  // Configure GPIO11 as CAP1
    //GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 3;	// Configure GPIO19 as CAP1
    //GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 1;  // Configure GPIO24 as CAP1

    EDIS;
}
#endif // endif DSP28_ECAP1

#if DSP28_ECAP2
//
// InitECap2Gpio -
// 
void
InitECap2Gpio(void)
{
    EALLOW;
    
    //
    // Enable internal pull-up for the selected pins
    // Pull-ups can be enabled or disabled by the user.
    // This will enable the pullups for the specified pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO7 = 0;      // Enable pull-up on GPIO7 (CAP2)
    //GpioCtrlRegs.GPAPUD.bit.GPIO15 = 0;   // Enable pull-up on GPIO15 (CAP2)
    //GpioCtrlRegs.GPAPUD.bit.GPIO25 = 0;	// Enable pull-up on GPIO25 (CAP2)

    //
    // Inputs are synchronized to SYSCLKOUT by default.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAQSEL1.bit.GPIO7 = 0;  // Synch to SYSCLKOUT GPIO7 (CAP2)
    //GpioCtrlRegs.GPAQSEL1.bit.GPIO15 = 0; // Synch to SYSCLKOUT GPIO15 (CAP2)
    //GpioCtrlRegs.GPAQSEL2.bit.GPIO25 = 0; // Synch to SYSCLKOUT GPIO25 (CAP2)

    //
    // Configure eCAP-2 pins using GPIO regs
    // This specifies which of the possible GPIO pins will be eCAP2 functional 
    // pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 3;     // Configure GPIO7 as CAP2
    //GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 1;    // Configure GPIO15 as CAP2
    //GpioCtrlRegs.GPAMUX2.bit.GPIO25 = 1;	   // Configure GPIO25 as CAP2

    EDIS;
}
#endif // endif DSP28_ECAP2

#if DSP28_ECAP3
//
// InitECap3Gpio - 
//
void
InitECap3Gpio(void)
{
    EALLOW;
    
    //
    // Enable internal pull-up for the selected pins
    // Pull-ups can be enabled or disabled by the user.
    // This will enable the pullups for the specified pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO9 = 0;     // Enable pull-up on GPIO9 (CAP3)
    //GpioCtrlRegs.GPAPUD.bit.GPIO26 = 0;    // Enable pull-up on GPIO26 (CAP3)

    //
    // Inputs are synchronized to SYSCLKOUT by default.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAQSEL1.bit.GPIO9 = 0;  // Synch to SYSCLKOUT GPIO9 (CAP3)
    //GpioCtrlRegs.GPAQSEL2.bit.GPIO26 = 0; // Synch to SYSCLKOUT GPIO26 (CAP3)

    //
    // Configure eCAP-3 pins using GPIO regs
    // This specifies which of the possible GPIO pins will be eCAP3 functional 
    // pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 3;     // Configure GPIO9 as CAP3
    //GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 1;    // Configure GPIO26 as CAP3

    EDIS;
}
#endif // endif DSP28_ECAP3

//
// End of file
//

