//###########################################################################
//
// FILE:	Example_2833xFPU_software.c
//
// TITLE:	Floating Point Unit Software Example
//
//! \addtogroup f2833x_example_list
//! <h1>Floating Point Unit (fpu_software)</h1>
//!
//! The code calculates two y=mx+b equations.  The variables are all
//! 32-bit floating-point.
//!
//! The compiler will only used fixed point instructions.  This means the 
//! runtime support library will be used to emulate floating point.
//! This will also run on C28x devices without the floating point unit.
//! To compile the project for fixed point, the following Build Options were 
//! used:
//! -# Project->Properties-> C/C++ Build window-> Basic Settings->
//! C2000 Compiler Vx.x \n
//! In All Options textbox: "--float_support=fpu32" is removed. \n
//! OR in Runtime Model Options, under "Specify floating point support
//! (--float_support) pull-down menu: Select "None".
//! -# Project->Properties-> C/C++ Build window-> Basic Settings->
//! C2000 Linker Vx.x-> File Search Path \n
//! In "Include linker file or command file as input (--library, -l)"
//! box, click green plus sign and add  rts2800.lib or rts2800_ml.lib
//! (run-time support library).
//! -# Not included in this example: If the project includes any other
//! libraries, they must also be compiled with fixed point instructions.
//!
//! \b Watch \b Variables \n
//! - y1
//! - y2
//! - FPU registers (optional)
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
float y1, y2;
float m1, m2;
float x1, x2;
float b1, b2;

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
    //

    //
    // Step 5. User specific code, enable interrupts
    //

    //
    // Calculate two y=mx+b equations.
    //
    y1 = 0;
    y2 = 0;
    m1 = .5;
    m2 = .6;
    x1 = 3.4;
    x2 = 7.3;
    b1 = 4.2;
    b2 = 8.9;

    y1 = m1*x1 + b1;
    y2 = m2*x2 + b2;

    ESTOP0;  // This is a software breakpoint
}

//
// End of File
//

