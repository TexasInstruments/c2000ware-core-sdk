//###########################################################################
//
// FILE:    DSP2803x_Comp.c
//
// TITLE:   DSP2803x Comparator Initialization & Support Functions.
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
// InitComp - This function initializes the Comp to a known state.
//
void
InitComp(void)
{
    //
    // Initialize Comp
    //
}

//
// InitCompGpio - This function initializes GPIO pins to function as Comp pins
//
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.
//
// Caution:
//      Only one GPIO pin should be enabled for each operation.
//      Only one GPIO pin shoudl be enabled for each operation.
//      Comment out other unwanted lines.
//
void 
InitCompGpio()
{
    InitComp1Gpio();
    
#if DSP28_COMP2
    InitComp2Gpio();
#endif
    
#if DSP28_COMP3
    InitComp3Gpio();
#endif
}

//
// InitComp1Gpio - This function initializes GPIO pins to function as Comp pins
//
void 
InitComp1Gpio()
{
    EALLOW;

    //
    // Disable internal pull-up for the selected output pins
    // to reduce power consumption 
    // Pull-ups can be enabled or disabled disabled by the user.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO1 = 1;    //Disable pull-up on GPIO1(CMP1OUT)
    //GpioCtrlRegs.GPAPUD.bit.GPIO20 = 1;  //Disable pull-up on GPIO20(CMP1OUT)
    //GpioCtrlRegs.GPBPUD.bit.GPIO42 = 1;  //Disable pull-up on GPIO42(CMP1OUT)

    //
    // Configure Comp pins using GPIO regs
    //
    // This specifies which of the possible GPIO pins will be Comp 
    // functional pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 3;   // GPIO1 for CMP1OUT operation
    //GpioCtrlRegs.GPAMUX2.bit.GPIO20 = 3;  // GPIO20 for CMP1OUT operation
    //GpioCtrlRegs.GPBMUX1.bit.GPIO42 = 3;  // GPIO42 for CMP1OUT operation

    GpioCtrlRegs.AIOMUX1.bit.AIO2 = 2;    // AIO2 for CMP1A operation
    GpioCtrlRegs.AIOMUX1.bit.AIO10 = 2;   // AIO10 for CMP1B operation

    EDIS;
}

#if DSP28_COMP2
//
// InitComp2Gpio - This function initializes GPIO pins to function as Comp pins
//
void 
InitComp2Gpio()
{
    EALLOW;

    //
    // Disable internal pull-up for the selected output pins
    // to reduce power consumption
    // Pull-ups can be enabled or disabled disabled by the user.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO3 = 1;   //Disable pull-up on GPIO3 (CMP2OUT)
    GpioCtrlRegs.GPAPUD.bit.GPIO21 = 1;  //Disable pull-up on GPIO21 (CMP2OUT)
    //GpioCtrlRegs.GPBPUD.bit.GPIO34 = 1; //Disable pull-up on GPIO34 (CMP2OUT)
    //GpioCtrlRegs.GPBPUD.bit.GPIO43 = 1; //Disable pull-up on GPIO43 (CMP2OUT)

    //
    // Configure Comp pins using GPIO regs
    // This specifies which of the possible GPIO pins will be
    // Comp functional pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 3;   //GPIO3 on CMP2OUT operation
    GpioCtrlRegs.GPAMUX2.bit.GPIO21 = 3;  //GPIO21 on CMP2OUT operation
    //GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 1; //GPIO34 on CMP2OUT operation
    //GpioCtrlRegs.GPBMUX1.bit.GPIO43 = 3; //GPIO43 on CMP2OUT operation

    GpioCtrlRegs.AIOMUX1.bit.AIO4 = 2;    //Configure AIO4 for CMP2A operation
    GpioCtrlRegs.AIOMUX1.bit.AIO12 = 2;   //Configure AIO12 for CMP2B operation

    EDIS;
}

#endif

#if DSP28_COMP3
//
// InitComp3Gpio - This function initializes GPIO pins to function as Comp pins
//
void 
InitComp3Gpio()
{
    EALLOW;
    
    //
    // Disable internal pull-up for the selected output pins
    // to reduce power consumption
    // Pull-ups can be enabled or disabled disabled by the user.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPBPUD.bit.GPIO34 = 1;  //Disable pull-up for GPIO34 (CMP3OUT)

    //
    // Configure Comp pins using GPIO regs
    // This specifies which of the possible GPIO pins will be 
    // Comp functional pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 3;  //GPIO34 for CMP3OUT operation
    GpioCtrlRegs.AIOMUX1.bit.AIO6 = 2;    //AIO6 for CMP3A operation
    GpioCtrlRegs.AIOMUX1.bit.AIO14 = 2;   //AIO14 for CMP3B operation

    EDIS;
}

#endif

//
// End of file
//

