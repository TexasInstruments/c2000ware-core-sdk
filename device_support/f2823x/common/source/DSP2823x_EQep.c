// TI File $Revision: /main/3 $
// Checkin $Date: July 27, 2007   11:55:20 $
//###########################################################################
//
// FILE:   DSP2823x_EQep.c
//
// TITLE:  DSP2823x eQEP Initialization & Support Functions.
//
//###########################################################################
// $TI Release: 2823x/2823x Header Files V1.32 $
// $Release Date: June 28, 2010 $
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
#include "DSP2823x_Device.h"     // DSP2823x Headerfile Include File
#include "DSP2823x_Examples.h"   // DSP2823x Examples Include File

//
// InitEQep - This function initializes the eQEP(s) to a known state.
//
void 
InitEQep(void)
{
    //
    // Initialize eQEP1/2
    //
}

//
// InitEQepGpio - This function initializes GPIO pins to function as eQEP pins
//
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.
//
// Caution:
// For each eQEP peripheral
// Only one GPIO pin should be enabled for EQEPxA operation.
// Only one GPIO pin should be enabled for EQEPxB operation.
// Only one GPIO pin should be enabled for EQEPxS operation.
// Only one GPIO pin should be enabled for EQEPxI operation.
// Comment out other unwanted lines.
//
void 
InitEQepGpio()
{
#if DSP28_EQEP1
    InitEQep1Gpio();
#endif  // endif DSP28_EQEP1
#if DSP28_EQEP2
    InitEQep2Gpio();
#endif // endif DSP28_EQEP2
}

//
// InitEQep1Gpio - This function initializes GPIO pins to function as eQEP1
//
#if DSP28_EQEP1
void 
InitEQep1Gpio(void)
{
    EALLOW;

    //
    // Enable internal pull-up for the selected pins
    // Pull-ups can be enabled or disabled by the user.
    // This will enable the pullups for the specified pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO20 = 0;   // Enable pull-up on GPIO20 (EQEP1A)
    GpioCtrlRegs.GPAPUD.bit.GPIO21 = 0;   // Enable pull-up on GPIO21 (EQEP1B)
    GpioCtrlRegs.GPAPUD.bit.GPIO22 = 0;   // Enable pull-up on GPIO22 (EQEP1S)
    GpioCtrlRegs.GPAPUD.bit.GPIO23 = 0;   // Enable pull-up on GPIO23 (EQEP1I)
    //GpioCtrlRegs.GPBPUD.bit.GPIO50 = 0;  // Enable pull-up on GPIO50 (EQEP1A)
    //GpioCtrlRegs.GPBPUD.bit.GPIO51 = 0;  // Enable pull-up on GPIO51 (EQEP1B)
    //GpioCtrlRegs.GPBPUD.bit.GPIO52 = 0;  // Enable pull-up on GPIO52 (EQEP1S)
    //GpioCtrlRegs.GPBPUD.bit.GPIO53 = 0;  // Enable pull-up on GPIO53 (EQEP1I)

    //
    // Inputs are synchronized to SYSCLKOUT by default.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAQSEL2.bit.GPIO20 = 0;  // Sync to SYSCLKOUT GPIO20 (EQEP1A)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO21 = 0;  // Sync to SYSCLKOUT GPIO21 (EQEP1B)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO22 = 0;  // Sync to SYSCLKOUT GPIO22 (EQEP1S)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO23 = 0;  // Sync to SYSCLKOUT GPIO23 (EQEP1I)

    //GpioCtrlRegs.GPBQSEL2.bit.GPIO50 = 0;  //Sync to SYSCLKOUT GPIO50(EQEP1A)
    //GpioCtrlRegs.GPBQSEL2.bit.GPIO51 = 0;  //Sync to SYSCLKOUT GPIO51(EQEP1B)
    //GpioCtrlRegs.GPBQSEL2.bit.GPIO52 = 0;  //Sync to SYSCLKOUT GPIO52(EQEP1S)
    //GpioCtrlRegs.GPBQSEL2.bit.GPIO53 = 0;  //Sync to SYSCLKOUT GPIO53(EQEP1I)

    //
    // Configure eQEP-1 pins using GPIO regs
    // This specifies which of the possible GPIO pins will be eQEP1 functional 
    // pins. Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAMUX2.bit.GPIO20 = 1;   // Configure GPIO20 as EQEP1A
    GpioCtrlRegs.GPAMUX2.bit.GPIO21 = 1;   // Configure GPIO21 as EQEP1B
    GpioCtrlRegs.GPAMUX2.bit.GPIO22 = 1;   // Configure GPIO22 as EQEP1S
    GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 1;   // Configure GPIO23 as EQEP1I

    //GpioCtrlRegs.GPBMUX2.bit.GPIO50 = 1;   // Configure GPIO50 as EQEP1A
    //GpioCtrlRegs.GPBMUX2.bit.GPIO51 = 1;   // Configure GPIO51 as EQEP1B
    //GpioCtrlRegs.GPBMUX2.bit.GPIO52 = 1;   // Configure GPIO52 as EQEP1S
    //GpioCtrlRegs.GPBMUX2.bit.GPIO53 = 1;   // Configure GPIO53 as EQEP1I

    EDIS;
}
#endif // if DSP28_EQEP1

//
// InitEQep2Gpio - This function initializes GPIO pins to function as eQEP2
//
#if DSP28_EQEP2
void 
InitEQep2Gpio(void)
{
    EALLOW;

    //
    // Enable internal pull-up for the selected pins
    // Pull-ups can be enabled or disabled by the user.
    // This will enable the pullups for the specified pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO24 = 0;    // Enable pull-up on GPIO24 (EQEP2A)
    GpioCtrlRegs.GPAPUD.bit.GPIO25 = 0;    // Enable pull-up on GPIO25 (EQEP2B)
    GpioCtrlRegs.GPAPUD.bit.GPIO26 = 0;    // Enable pull-up on GPIO26 (EQEP2I)
    GpioCtrlRegs.GPAPUD.bit.GPIO27 = 0;    // Enable pull-up on GPIO27 (EQEP2S)

    //
    // Inputs are synchronized to SYSCLKOUT by default.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAQSEL2.bit.GPIO24 = 0;  // Sync to SYSCLKOUT GPIO24 (EQEP2A)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO25 = 0;  // Sync to SYSCLKOUT GPIO25 (EQEP2B)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO26 = 0;  // Sync to SYSCLKOUT GPIO26 (EQEP2I)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO27 = 0;  // Sync to SYSCLKOUT GPIO27 (EQEP2S)

    //
    // Configure eQEP-2 pins using GPIO regs
    // This specifies which of the possible GPIO pins will be eQEP2 functional 
    // pins. Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 2;   // Configure GPIO24 as EQEP2A
    GpioCtrlRegs.GPAMUX2.bit.GPIO25 = 2;   // Configure GPIO25 as EQEP2B
    GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 2;   // Configure GPIO26 as EQEP2I
    GpioCtrlRegs.GPAMUX2.bit.GPIO27 = 2;   // Configure GPIO27 as EQEP2S

    EDIS;
}
#endif // endif DSP28_EQEP2

//
// End of file
//

