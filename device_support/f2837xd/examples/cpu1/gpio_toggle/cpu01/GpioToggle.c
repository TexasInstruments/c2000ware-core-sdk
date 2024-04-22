//###########################################################################
//
// FILE:    GpioToggle.c
//
// TITLE:   GPIO toggle test program.
//
//! \addtogroup cpu01_example_list
//! <h1>GPIO toggle test program (GpioToggle)</h1>
//!
//! Three different examples are included. Select the example
//! (data, set/clear or toggle) to execute before compiling using
//! the #define statements found at the top of the code.
//!
//! Toggle all of the GPIO PORT pins
//!
//! The pins can be observed using Oscilloscope.
//!
//
//###########################################################################
//
// 
// $Copyright:
// Copyright (C) 2013-2024 Texas Instruments Incorporated - http://www.ti.com/
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
// Select the example to compile in.  Only one example should be set as 1
// the rest should be set as 0.
//
#define EXAMPLE1 1  // Use DATA registers to toggle I/O's
#define EXAMPLE2 0  // Use SET/CLEAR registers to toggle I/O's
#define EXAMPLE3 0  // Use TOGGLE registers to toggle I/O's

//
// Function Prototypes
//
void delay_loop(void);
void Gpio_select(void);
void Gpio_example1(void);
void Gpio_example2(void);
void Gpio_example3(void);

//
// Main
//
void main(void)
{
//
// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the F2837xD_SysCtrl.c file.
//
   InitSysCtrl();

//
// Step 2. Initialize GPIO:
// This example function is found in the F2837xD_Gpio.c file and
// illustrates how to set the GPIO to it's default state.
   Gpio_select();

//
// Step 3. Clear all __interrupts and initialize PIE vector table:
// Disable CPU __interrupts
//
   DINT;

//
// Initialize PIE control registers to their default state.
// The default state is all PIE __interrupts disabled and flags
// are cleared.
// This function is found in the F2837xD_PieCtrl.c file.
//
   InitPieCtrl();

//
// Disable CPU __interrupts and clear all CPU __interrupt flags:
//
   IER = 0x0000;
   IFR = 0x0000;

//
// Initialize the PIE vector table with pointers to the shell Interrupt
// Service Routines (ISR).
// This will populate the entire table, even if the __interrupt
// is not used in this example.  This is useful for debug purposes.
// The shell ISR routines are found in F2837xD_DefaultIsr.c.
// This function is found in F2837xD_PieVect.c.
//
   InitPieVectTable();

//
// Step 4. User specific code:
//
#if EXAMPLE1

    //
    // This example uses DATA registers to toggle I/O's
    //
    Gpio_example1();

#endif  // - EXAMPLE1

#if EXAMPLE2

    //
    // This example uses SET/CLEAR registers to toggle I/O's
    //
    Gpio_example2();

#endif

#if EXAMPLE3

    //
    // This example uses TOGGLE registers to toggle I/O's
    //
    Gpio_example3();

#endif
}

//
// delay_loop - Delay function
//
void delay_loop()
{
    short i;
    for (i = 0; i < 1000; i++) {}
}

//
// Gpio_example1 - Example 1: Toggle I/Os using DATA registers
//
void Gpio_example1(void)
{
   for(;;)
   {
      GpioDataRegs.GPADAT.all = 0xAAAAAAAA;
      GpioDataRegs.GPBDAT.all = 0x00000AAA;
      delay_loop();

      GpioDataRegs.GPADAT.all = 0x55555555;
      GpioDataRegs.GPBDAT.all = 0x00001555;
      delay_loop();
    }
}

//
// Gpio_example2 - Example 2: Toggle I/Os using SET/CLEAR registers
//
void Gpio_example2(void)
{
   for(;;)
   {
       GpioDataRegs.GPASET.all = 0xAAAAAAAA;
       GpioDataRegs.GPACLEAR.all = 0x55555555;

       GpioDataRegs.GPBSET.all = 0x00000AAA;
       GpioDataRegs.GPBCLEAR.all = 0x00001555;

       delay_loop();

       GpioDataRegs.GPACLEAR.all = 0xAAAAAAAA;
       GpioDataRegs.GPASET.all = 0x55555555;

       GpioDataRegs.GPBCLEAR.all = 0x00000AAA;
       GpioDataRegs.GPBSET.all = 0x00001555;

       delay_loop();
    }
}

//
// Gpio_example3 - Example 3: Toggle I/Os using TOGGLE registers
//
void Gpio_example3(void)
{
   //
   // Set pins to a known state
   //
   GpioDataRegs.GPASET.all = 0xAAAAAAAA;
   GpioDataRegs.GPACLEAR.all = 0x55555555;

   GpioDataRegs.GPBSET.all = 0x00000AAA;
   GpioDataRegs.GPBCLEAR.all = 0x00001555;

   //
   // Use TOGGLE registers to flip the state of
   // the pins.
   // Any bit set to a 1 will flip state (toggle)
   // Any bit set to a 0 will not toggle.
   //
   for(;;)
   {
      GpioDataRegs.GPATOGGLE.all =0xFFFFFFFF;
      GpioDataRegs.GPBTOGGLE.all =0x00001FFF;

      delay_loop();
   }
}

//
// Gpio_select - Configure GPIO muxing and pin outputs
//
void Gpio_select(void)
{
    EALLOW;
    GpioCtrlRegs.GPAMUX1.all = 0x00000000;  // All GPIO
    GpioCtrlRegs.GPAMUX2.all = 0x00000000;  // All GPIO
    GpioCtrlRegs.GPBMUX1.all = 0x00000000;  // All GPIO
    GpioCtrlRegs.GPADIR.all = 0xFFFFFFFF;   // All outputs
    GpioCtrlRegs.GPBDIR.all = 0x00001FFF;   // All outputs
    EDIS;
}

//
// End of file
//
