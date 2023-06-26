// TI File $Revision: /main/1 $
// Checkin $Date: August 18, 2006   13:46:44 $
//###########################################################################
//
// FILE:   DSP2833x_Spi.c
//
// TITLE:  DSP2833x SPI Initialization & Support Functions.
//
//###########################################################################
// $TI Release: 2833x/2823x Header Files V1.32 $
// $Release Date: June 28, 2010 $
// $Copyright:
// Copyright (C) 2009-2023 Texas Instruments Incorporated - http://www.ti.com/
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
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

//
// InitSPI - This function initializes the SPI(s) to a known state.
//
void 
InitSpi(void)
{
    //
    // Initialize SPI-A/B/C/D
    //
}

//
// InitSpiGpio - This function initializes GPIO pins to function as SPI pins
//
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.  
// 
// Caution: 
// For each SPI peripheral
// Only one GPIO pin should be enabled for SPISOMO operation.
// Only one GPIO pin should be enabled for SPISOMI operation. 
// Only one GPIO pin should be enabled for SPICLKA operation. 
// Only one GPIO pin should be enabled for SPISTEA operation. 
// Comment out other unwanted lines.
//
void 
InitSpiGpio()
{
    InitSpiaGpio();
}

//
// InitSpiaGpio - This function initializes GPIO poins to function as SPI pins
//
void 
InitSpiaGpio()
{
    EALLOW;
    
    //
    // Enable internal pull-up for the selected pins
    // Pull-ups can be enabled or disabled by the user.  
    // This will enable the pullups for the specified pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO16 = 0;   //Enable pull-up on GPIO16 (SPISIMOA)
    GpioCtrlRegs.GPAPUD.bit.GPIO17 = 0;   //Enable pull-up on GPIO17 (SPISOMIA)
    GpioCtrlRegs.GPAPUD.bit.GPIO18 = 0;   //Enable pull-up on GPIO18 (SPICLKA)
    GpioCtrlRegs.GPAPUD.bit.GPIO19 = 0;   //Enable pull-up on GPIO19 (SPISTEA)

    //GpioCtrlRegs.GPBPUD.bit.GPIO54 = 0; //Enable pull-up on GPIO54 (SPISIMOA)
    //GpioCtrlRegs.GPBPUD.bit.GPIO55 = 0; //Enable pull-up on GPIO55 (SPISOMIA)
    //GpioCtrlRegs.GPBPUD.bit.GPIO56 = 0; //Enable pull-up on GPIO56 (SPICLKA)
    //GpioCtrlRegs.GPBPUD.bit.GPIO57 = 0; //Enable pull-up on GPIO57 (SPISTEA)

    //
    // Set qualification for selected pins to asynch only
    // This will select asynch (no qualification) for the selected pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAQSEL2.bit.GPIO16 = 3; // Asynch input GPIO16 (SPISIMOA)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO17 = 3; // Asynch input GPIO17 (SPISOMIA)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO18 = 3; // Asynch input GPIO18 (SPICLKA)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = 3; // Asynch input GPIO19 (SPISTEA)

    //GpioCtrlRegs.GPBQSEL2.bit.GPIO54 = 3; // Asynch input GPIO16 (SPISIMOA)
    //GpioCtrlRegs.GPBQSEL2.bit.GPIO55 = 3; // Asynch input GPIO17 (SPISOMIA)
    //GpioCtrlRegs.GPBQSEL2.bit.GPIO56 = 3; // Asynch input GPIO18 (SPICLKA)
    //GpioCtrlRegs.GPBQSEL2.bit.GPIO57 = 3; // Asynch input GPIO19 (SPISTEA)

    //
    // Configure SPI-A pins using GPIO regs
    // This specifies which of the possible GPIO pins will be SPI 
    // functional pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 1; // Configure GPIO16 as SPISIMOA
    GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 1; // Configure GPIO17 as SPISOMIA
    GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 1; // Configure GPIO18 as SPICLKA
    GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 1; // Configure GPIO19 as SPISTEA

    //GpioCtrlRegs.GPBMUX2.bit.GPIO54 = 1; // Configure GPIO54 as SPISIMOA
    //GpioCtrlRegs.GPBMUX2.bit.GPIO55 = 1; // Configure GPIO55 as SPISOMIA
    //GpioCtrlRegs.GPBMUX2.bit.GPIO56 = 1; // Configure GPIO56 as SPICLKA
    //GpioCtrlRegs.GPBMUX2.bit.GPIO57 = 1; // Configure GPIO57 as SPISTEA

    EDIS;
}

//
// End of file
//

