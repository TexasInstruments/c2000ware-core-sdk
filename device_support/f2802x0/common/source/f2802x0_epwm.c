//###########################################################################
//
// FILE:   F2802x0_EPwm.c
//
// TITLE:  F2802x0 EPwm Initialization & Support Functions.
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
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
#include "F2802x0_Device.h"     // Headerfile Include File
#include "f2802x0_examples.h"   // Examples Include File

//
// InitEPwm - This function initializes the EPwm(s) to a known state.
//
void
InitEPwm(void)
{
    //
    // Initialize EPwm1/2/3/4
    //
}

//
// InitEPwmGpio - This function initializes GPIO pins to function as EPwm pins
//
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.
//
void
InitEPwmGpio(void)
{
    InitEPwm1Gpio();
    InitEPwm2Gpio();
    InitEPwm3Gpio();
#if DSP28_EPWM4
    InitEPwm4Gpio();
#endif // endif DSP28_EPWM4
}

//
// InitEPwm1Gpio - 
//
void
InitEPwm1Gpio(void)
{
    EALLOW;

    //
    // Disable internal pull-up for the selected output pins
    // for reduced power consumption
    // Pull-ups can be enabled or disabled by the user.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO0 = 1;    // Disable pull-up on GPIO0 (EPWM1A)
    GpioCtrlRegs.GPAPUD.bit.GPIO1 = 1;    // Disable pull-up on GPIO1 (EPWM1B)

    //
    // Configure EPwm-1 pins using GPIO regs
    // This specifies which of the possible GPIO pins will be EPWM1 functional
    // pins. Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;   // Configure GPIO0 as EPWM1A
    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;   // Configure GPIO1 as EPWM1B

    EDIS;
}

//
// InitEPwm2Gpio - 
//
void
InitEPwm2Gpio(void)
{
    EALLOW;

    //
    // Disable internal pull-up for the selected output pins for reduced power 
    // consumption. Pull-ups can be enabled or disabled by the user.
    // This will enable the pullups for the specified pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO2 = 1;    // Disable pull-up on GPIO2 (EPWM2A)
    GpioCtrlRegs.GPAPUD.bit.GPIO3 = 1;    // Disable pull-up on GPIO3 (EPWM2B)

    //
    // Configure EPwm-2 pins using GPIO regs
    // This specifies which of the possible GPIO pins will be EPWM2 functional
    // pins. Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;   // Configure GPIO2 as EPWM2A
    GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;   // Configure GPIO3 as EPWM2B

    EDIS;
}

//
// InitEPwm3Gpio - 
//
void
InitEPwm3Gpio(void)
{
    EALLOW;

    //
    // Disable internal pull-up for the selected output pins
    // for reduced power consumption. Pull-ups can be enabled or disabled by 
    // the user. This will enable the pullups for the specified pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO4 = 1;    // Disable pull-up on GPIO4 (EPWM3A)
    GpioCtrlRegs.GPAPUD.bit.GPIO5 = 1;    // Disable pull-up on GPIO5 (EPWM3B)

    //
    // Configure EPwm-3 pins using GPIO regs.
    // This specifies which of the possible GPIO pins will be EPWM3 functional 
    // pins. Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;   // Configure GPIO4 as EPWM3A
    GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 1;   // Configure GPIO5 as EPWM3B

    EDIS;
}

#if DSP28_EPWM4
//
// InitEPwm4Gpio - 
//
void
InitEPwm4Gpio(void)
{
    EALLOW;
    //
    // Disable internal pull-up for the selected output pins for reduced power 
    // consumption. Pull-ups can be enabled or disabled by the user.
    // This will enable the pullups for the specified pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO6 = 1;    // Disable pull-up on GPIO6 (EPWM4A)
    GpioCtrlRegs.GPAPUD.bit.GPIO7 = 1;    // Disable pull-up on GPIO7 (EPWM4B)

    //
    // Configure EPWM-4 pins using GPIO regs
    // This specifies which of the possible GPIO pins will be EPWM4 functional 
    // pins. Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 1;   // Configure GPIO6 as EPWM4A
    GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 1;   // Configure GPIO7 as EPWM4B

    EDIS;
}
#endif // endif DSP28_EPWM4

//
// InitEPwmSyncGpio - This function initializes GPIO pins to function as 
// EPwm Synch pins
//
void
InitEPwmSyncGpio(void)
{
    //
    //EALLOW;
    //

    //
    // Configure EPWMSYNCI
    //

    //
    // Enable internal pull-up for the selected pins
    // Pull-ups can be enabled or disabled by the user.
    // This will enable the pullups for the specified pins.
    // Comment out other unwanted lines.
    //
    
    //
    // Enable pull-up on GPIO6 (EPWMSYNCI)
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0;
    
    //
    // Enable pull-up on GPIO32 (EPWMSYNCI)
    //
    //GpioCtrlRegs.GPBPUD.bit.GPIO32 = 0;

    //
    // Set qualification for selected pins to asynch only
    // This will select synch to SYSCLKOUT for the selected pins.
    // Comment out other unwanted lines.
    //
    
    //
    // Synch to SYSCLKOUT GPIO6 (EPWMSYNCI)
    //
    GpioCtrlRegs.GPAQSEL1.bit.GPIO6 = 0;
    
    //
    // Synch to SYSCLKOUT GPIO32 (EPWMSYNCI)
    //
    //GpioCtrlRegs.GPBQSEL1.bit.GPIO32 = 0;

    //
    // Configure EPwmSync pins using GPIO regs
    // This specifies which of the possible GPIO pins will be EPwmSync 
    // unctional pins. Comment out other unwanted lines.
    //
    
    //
    // Configures GPIO6 for EPWMSYNCI operation
    //
    GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 2;
    
    //
    // Configures GPIO32 for EPWMSYNCI operation
    //
    //GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 2;   

    //
    // Configure EPWMSYNC0
    //

    //
    // Disable internal pull-up for the selected output pins for reduced 
    // power consumption. Pull-ups can be enabled or disabled by the user.
    // Comment out other unwanted lines.
    //
    
    //
    // Disable pull-up on GPIO6 (EPWMSYNCO)
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO6 = 1;
    
    //
    // Disable pull-up on GPIO33 (EPWMSYNCO)
    //
    //GpioCtrlRegs.GPBPUD.bit.GPIO33 = 1;

    GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 3;    // Configures GPIO6 for EPWMSYNCO
    //GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 2;   // Configures GPIO33 for EPWMSYNCO
}

//
// InitTzGpio - This function initializes GPIO pins to function as 
// Trip Zone (TZ) pins
//
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.
//
void
InitTzGpio(void)
{
    EALLOW;

    //
    // Enable internal pull-up for the selected pins
    // Pull-ups can be enabled or disabled by the user.
    // This will enable the pullups for the specified pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO12 = 0;    // Enable pull-up on GPIO12 (TZ1)
    GpioCtrlRegs.GPAPUD.bit.GPIO16 = 0;    // Enable pull-up on GPIO16 (TZ2)
    //GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0;    // Enable pull-up on GPIO28 (TZ2)
    GpioCtrlRegs.GPAPUD.bit.GPIO17 = 0;    // Enable pull-up on GPIO17 (TZ3)
    //GpioCtrlRegs.GPAPUD.bit.GPIO29 = 0;    // Enable pull-up on GPIO29 (TZ3)

    //
    /// Set qualification for selected pins to asynch only
    // Inputs are synchronized to SYSCLKOUT by default.
    // This will select asynch (no qualification) for the selected pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAQSEL1.bit.GPIO12 = 3;  // Asynch input GPIO12 (TZ1)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO16 = 3;  // Asynch input GPIO16 (TZ2)
    //GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3;  // Asynch input GPIO28 (TZ2)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO17 = 3;  // Asynch input GPIO17 (TZ3)
    //GpioCtrlRegs.GPAQSEL2.bit.GPIO29 = 3;  // Asynch input GPIO29 (TZ3)

    //
    // Configure TZ pins using GPIO regs
    // This specifies which of the possible GPIO pins will be TZ 
    // functional pins. Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 1;  // Configure GPIO12 as TZ1
    GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 3;  // Configure GPIO16 as TZ2
    //GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 3;  // Configure GPIO28 as TZ2
    GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 3;  // Configure GPIO17 as TZ3
    //GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 3;  // Configure GPIO29 as TZ3

    EDIS;
}

//
// End of file
//

