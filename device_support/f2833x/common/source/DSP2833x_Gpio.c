// TI File $Revision: /main/1 $
// Checkin $Date: August 18, 2006   13:46:25 $
//###########################################################################
//
// FILE:	DSP2833x_Gpio.c
//
// TITLE:	DSP2833x General Purpose I/O Initialization & Support Functions.
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
// InitGpio - This function initializes the Gpio to a known (default) state.
//
// For more details on configuring GPIO's as peripheral functions,
// refer to the individual peripheral examples and/or GPIO setup example. 
//
void 
InitGpio(void)
{
    EALLOW;

    //
    // Each GPIO pin can be: 
    // a) a GPIO input/output
    // b) peripheral function 1
    // c) peripheral function 2
    // d) peripheral function 3
    // By default, all are GPIO Inputs 
    //
    GpioCtrlRegs.GPAMUX1.all = 0x0000;     // GPIO functionality GPIO0-GPIO15
    GpioCtrlRegs.GPAMUX2.all = 0x0000;     // GPIO functionality GPIO16-GPIO31
    GpioCtrlRegs.GPBMUX1.all = 0x0000;     // GPIO functionality GPIO32-GPIO39
    GpioCtrlRegs.GPBMUX2.all = 0x0000;     // GPIO functionality GPIO48-GPIO63
    GpioCtrlRegs.GPCMUX1.all = 0x0000;     // GPIO functionality GPIO64-GPIO79
    GpioCtrlRegs.GPCMUX2.all = 0x0000;     // GPIO functionality GPIO80-GPIO95

    GpioCtrlRegs.GPADIR.all = 0x0000;      // GPIO0-GPIO31 are inputs
    GpioCtrlRegs.GPBDIR.all = 0x0000;      // GPIO32-GPIO63 are inputs   
    GpioCtrlRegs.GPCDIR.all = 0x0000;      // GPI064-GPIO95 are inputs

    //
    // Each input can have different qualification
    // a) input synchronized to SYSCLKOUT
    // b) input qualified by a sampling window
    // c) input sent asynchronously (valid for peripheral inputs only)
    //
    GpioCtrlRegs.GPAQSEL1.all = 0x0000;    // GPIO0-GPIO15 Synch to SYSCLKOUT 
    GpioCtrlRegs.GPAQSEL2.all = 0x0000;    // GPIO16-GPIO31 Synch to SYSCLKOUT
    GpioCtrlRegs.GPBQSEL1.all = 0x0000;    // GPIO32-GPIO39 Synch to SYSCLKOUT 
    GpioCtrlRegs.GPBQSEL2.all = 0x0000;    // GPIO48-GPIO63 Synch to SYSCLKOUT 

    //
    // Pull-ups can be enabled or disabled
    //
    GpioCtrlRegs.GPAPUD.all = 0x0000;      // Pullup's enabled GPIO0-GPIO31
    GpioCtrlRegs.GPBPUD.all = 0x0000;      // Pullup's enabled GPIO32-GPIO63
    GpioCtrlRegs.GPCPUD.all = 0x0000;      // Pullup's enabled GPIO64-GPIO79
    //GpioCtrlRegs.GPAPUD.all = 0xFFFF;    // Pullup's disabled GPIO0-GPIO31
    //GpioCtrlRegs.GPBPUD.all = 0xFFFF;    // Pullup's disabled GPIO32-GPIO34
    //GpioCtrlRegs.GPCPUD.all = 0xFFFF;    // Pullup's disabled GPIO64-GPIO79

    EDIS;
}	
	
//
// End of file
//

