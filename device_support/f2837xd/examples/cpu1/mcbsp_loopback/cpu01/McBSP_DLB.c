//###########################################################################
//
// FILE:   McBSP_DLB.c
//
// TITLE:  McBSP Loopback
//
//! \addtogroup cpu01_example_list
//! <h1>McBSP Loopback (mcbsp_loopback)</h1>
//!
//!  Three different serial word sizes can be tested.  Before compiling
//!  this project, select the serial word size of 8, 16 or 32 by using
//!  the \#define statements at the beginning of the code.
//!
//!  This example does not use interrupts.  Instead, a polling
//!  method is used to check the receive data.  The incoming
//!  data is checked for accuracy.  If an error is found the error()
//!  function is called and execution stops.
//!
//!  This program will execute until terminated by the user.
//!
//! \b 8-bit \b word \b example: \n
//!      The sent data looks like this:\n
//!      00 01 02 03 04 05 06 07 .... FE FF\n
//!
//! \b 16-bit \b word \b example: \n
//!      The sent data looks like this:\n
//!      0000 0001 0002 0003 0004 0005 0006 0007 .... FFFE FFFF\n
//!
//! \b 32-bit \b word \b example: \n
//!      The sent data looks like this: \n
//!      FFFF0000 FFFE0001 FFFD0002 .... 0000FFFF \n
//!
//! \b Watch \b Variables: \n
//! - sdata1 - Sent data word:     8 or 16-bit or low half of 32-bit
//! - sdata2 - Sent data word:     upper half of 32-bit
//! - rdata1 - Received data word: 8 or 16-bit or low half of 32-bit
//! - rdata2 - Received data word: upper half of 32-bit
//! - rdata1_point - Tracks last position in receive stream 1 for error
//!                  checking
//! - rdata2_point - Tracks last position in receive stream 2 for error
//!                  checking
//!
//! \note sdata2 and rdata2 are not used for 8-bit or 16-bit word size
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
// Defines
//
// Choose a word size.  Uncomment one of the following lines
//
#define WORD_SIZE    8    // Run a loopback test in 8-bit mode
//#define WORD_SIZE 16      // Run a loopback test in 16-bit mode
//#define WORD_SIZE 32      // Run a loopback test in 32-bit mode

//
// Globals
//
Uint16 sdata1 = 0x000;    // Sent Data
Uint16 rdata1 = 0x000;    // Received Data
Uint16 sdata2 = 0x000;    // Sent Data
Uint16 rdata2 = 0x000;    // Received Data
Uint16 rdata1_point;
Uint16 rdata2_point;
Uint16 data_size;

//
// Function Prototypes
//
void mcbsp_init_dlb(void);
void mcbsp_xmit(int a, int b);
void error(void);

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
// For this example, only enable the GPIO for McBSP-A
//
   InitMcbspaGpio();

//
// Step 3. Clear all interrupts and initialize PIE vector table:
// Disable CPU interrupts
//
   DINT;

//
// Initialize PIE control registers to their default state.
// The default state is all PIE interrupts disabled and flags
// are cleared.
// This function is found in the F2837xD_PieCtrl.c file.
//
   InitPieCtrl();

//
// Disable CPU interrupts and clear all CPU interrupt flags:
//
   IER = 0x0000;
   IFR = 0x0000;

//
// Initialize the PIE vector table with pointers to the shell Interrupt
// Service Routines (ISR).
// This will populate the entire table, even if the interrupt
// is not used in this example.  This is useful for debug purposes.
// The shell ISR routines are found in F2837xD_DefaultIsr.c.
// This function is found in F2837xD_PieVect.c.
//
   InitPieVectTable();

   data_size = WORD_SIZE;

//
// Initialize and release peripheral (McBSP) from Reset.
//
   mcbsp_init_dlb();

//
// Step 4. User specific code, enable interrupts:
//
    if(data_size == 8)             // Run a loopback test in 8-bit mode
    {
        sdata2 = 0x0000;           // value is a don't care for 8-bit mode
        sdata1 = 0x0000;           // 8-bit value to send
        rdata2_point = 0x0000;     // value is a don't care for 8-bit mode
        rdata1_point = sdata1;
        for(;;)
        {
            mcbsp_xmit(sdata1,sdata2);
            sdata1++;
            sdata1 = sdata1 & 0x00FF;                  // Keep it to 8-bits

            while(McbspaRegs.SPCR1.bit.RRDY == 0 ) { } // Check for receive
            rdata1 = McbspaRegs.DRR1.all;              // read DRR1
            if(rdata1 != rdata1_point) error();
            rdata1_point++;
            rdata1_point = rdata1_point & 0x00FF;      // Keep it to 8-bits

            __asm("    nop");    // Good place for a breakpoint
                                 // Check: rdatax_point = sdatax
                                 //        rdata1 = sdata1 - 1
        }
    }
    else if(data_size == 16)       // Run a loopback test in 16-bit mode
    {
        sdata2 = 0x0000;           // value is a don't care for 16-bit mode
        sdata1 = 0x0000;           // 16-bit value to send
        rdata2_point = 0x0000;     // value is a don't care for 16-bit mode
        rdata1_point = sdata1;
        for(;;)
        {
            mcbsp_xmit(sdata1,sdata2);
            sdata1++;

            while(McbspaRegs.SPCR1.bit.RRDY == 0 ) { }   // Check for receive
            rdata1 = McbspaRegs.DRR1.all;                // read DRR1
            if(rdata1 != rdata1_point) error();
            rdata1_point++;

            __asm("    nop");      // Good place for a breakpoint
                                   // Check: rdatax_point = sdatax
                                   //        rdata1 = sdata1 - 1
        }
    }
    else if(data_size == 32)       // Run a loopback test in 32-bit mode
    {
        sdata1 = 0x0000;
        sdata2 = 0xFFFF;
        rdata1_point = sdata1;
        rdata2_point = sdata2;
        for(;;)
        {
            mcbsp_xmit(sdata1,sdata2);
            sdata1++;
            sdata2--;

            while(McbspaRegs.SPCR1.bit.RRDY == 0 ) { }  // Check for receive
            rdata2 = McbspaRegs.DRR2.all;
            rdata1 = McbspaRegs.DRR1.all;
            if(rdata1 != rdata1_point) error();
            if(rdata2 != rdata2_point) error();
            rdata1_point++;
            rdata2_point--;

           __asm("    nop");       // Good place for a breakpoint
                                   // Check: rdatax_point = sdatax
                                   //        rdata1 = sdata1 - 1
                                   //        rdata2 = sdata2 + 1
        }
    }
}

//
// error - Function to indicate error and halt debugger
//
void error(void)
{
   __asm("     ESTOP0");  // test failed!! Stop!
   for (;;);
}

//
// mcbsp_init_dlb - Initialize McBSP with DLB enabled and setup for specific
//                  loopback test bit mode
//
void mcbsp_init_dlb()
{
    McbspaRegs.SPCR2.all=0x0000;        // Reset FS generator, sample rate
                                        // generator & transmitter
    McbspaRegs.SPCR1.all=0x0000;        // Reset Receiver, Right justify word
    McbspaRegs.SPCR1.bit.DLB = 1;       // Enable DLB mode. Comment out for
                                        // non-DLB mode.

    McbspaRegs.RCR2.bit.RDATDLY = 1;    // RX data delay is 1 bit
    McbspaRegs.XCR2.bit.XDATDLY = 1;    // TX data delay is 1 bit

    McbspaRegs.SRGR2.bit.GSYNC = 0;     // No clock sync for CLKG
    McbspaRegs.SRGR2.bit.FPER = 320;    // Frame-synchronization period

    McbspaRegs.SRGR2.bit.FSGM = 1;      // Frame-synchronization pulses from
                                        // the sample rate generator

    McbspaRegs.SRGR2.bit.CLKSM = 1;     // Sample rate generator input clock
                                        // is LSPCLK
    McbspaRegs.PCR.bit.SCLKME = 0;

    McbspaRegs.SRGR1.bit.CLKGDV = 1;    // Divide-down value for CLKG
    delay_loop();
    McbspaRegs.SRGR1.bit.FWID = 1;      // Frame-synchronization pulse width

    McbspaRegs.PCR.bit.CLKXM = 1;       // CLKX generated internally, CLKR
                                        // derived from an external source
    McbspaRegs.PCR.bit.FSXM = 1;        // FSX generated internally, FSR
                                        // derived from an external source

    //
    // Initialize McBSP Data Length
    //
    if(data_size == 8)                  // Run a loopback test in 8-bit mode
    {
      InitMcbspa8bit();
    }
    if(data_size == 16)                 // Run a loopback test in 16-bit mode
    {
      InitMcbspa16bit();
    }
    if(data_size == 32)                 // Run a loopback test in 32-bit mode
    {
      InitMcbspa32bit();
    }

    //
    // Enable Sample rate generator and
    // wait at least 2 CLKG clock cycles
    //
    McbspaRegs.SPCR2.bit.GRST = 1;
    delay_loop();

    //
    // Release from reset
    // RX, TX and frame sync generator
    //
    McbspaRegs.SPCR2.bit.XRST = 1;
    McbspaRegs.SPCR1.bit.RRST = 1;
    McbspaRegs.SPCR2.bit.FRST = 1;
}

//
// mcbsp_xmit - Transmit data via McBPP
//
void mcbsp_xmit(int a, int b)
{
    McbspaRegs.DXR2.all=b;
    McbspaRegs.DXR1.all=a;
}

//
// End of file
//
