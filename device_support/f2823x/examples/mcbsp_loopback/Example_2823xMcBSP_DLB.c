//###########################################################################
//
// FILE:	Example_2823xMcBSP_DLB.c
//
// TITLE:	McBSP Digital Loop Back Example
//
//! \addtogroup f2823x_example_list
//! <h1>McBSP Digital Loop Back (mcbsp_loopback)</h1>
//!
//! This example performs digital loopback tests for the McBSP peripheral.
//! This example does not use interrupts.  Instead, a polling
//! method is used to check the receive data.  The incoming
//! data is checked for accuracy.  If an error is found the error()
//! function is called and execution stops.
//!
//! \b Watch \b Variables \n
//! - sdata1
//! - sdata2
//! - rdata1
//! - rdata2
//! - rdata1_point
//! - rdata2_point
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
//##########################################################################

//
// Included Files
//
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File

//
// Defines
//

//
// Choose a word size.  Uncomment one of the following lines
//
#define WORD_SIZE    8        // Run a loopback test in 8-bit mode
//#define WORD_SIZE 16        // Run a loopback test in 16-bit mode
//#define WORD_SIZE 32        // Run a loopback test in 32-bit mode

//
// Function Prototypes
//
void mcbsp_init_dlb(void);
void mcbsp_xmit(int a, int b);
void error(void);

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
// Main
//
void main(void)
{
    //
    // Step 1. Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    // This example function is found in the DSP2823x_SysCtrl.c file.
    //
    InitSysCtrl();

    //
    // Step 2. Initialize GPIO:
    // This example function is found in the DSP2823x_Gpio.c file and
    // illustrates how to set the GPIO to it's default state.
    //
    // InitGpio();  // Skipped for this example
    // For this example, only enable the GPIO for McBSP-A
    InitMcbspaGpio();

    //
    // Step 3. Clear all interrupts and initialize PIE vector table
    //
    
    //
    // Disable CPU interrupts
    //
    DINT;

    //
    // Initialize PIE control registers to their default state.
    // The default state is all PIE interrupts disabled and flags
    // are cleared.
    // This function is found in the DSP2823x_PieCtrl.c file.
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
    // The shell ISR routines are found in DSP2823x_DefaultIsr.c.
    // This function is found in DSP2823x_PieVect.c.
    //
    InitPieVectTable();

    //
    // Step 4. Initialize all the Device Peripherals:
    // This function is found in DSP2823x_InitPeripherals.c
    //
    // InitPeripherals();     // Not required for this example
    data_size = WORD_SIZE;

    //
    // Initialize and release peripheral (McBSP) from Reset.
    //
    mcbsp_init_dlb();

    //
    // Step 5. User specific code, enable interrupts
    //
    
    //
    // Run a loopback test in 8-bit mode
    //
    if(data_size == 8)
    {
        sdata2 = 0x0000;           // value is a don't care for 8-bit mode
        sdata1 = 0x0000;           // 8-bit value to send
        rdata2_point = 0x0000;     // value is a don't care for 8-bit mode
        rdata1_point = sdata1;
        for(;;)
        {
            mcbsp_xmit(sdata1,sdata2);
            sdata1++;
            sdata1 = sdata1 & 0x00FF;            // Keep it to 8-bits

            //
            // Check for receive
            //
            while(McbspaRegs.SPCR1.bit.RRDY == 0 )
            { 
            
            }
            
            rdata1 = McbspaRegs.DRR1.all;         // read DRR1
            if(rdata1 != rdata1_point) 
            {
                error();
            }
            rdata1_point++;
            rdata1_point = rdata1_point & 0x00FF;  // Keep it to 8-bits

            //
            // Good place for a breakpoint
            // Check: rdatax_point = sdatax
            //        rdata1 = sdata1 - 1
            //
            __asm("    nop");
        }
    }
    
    //
    // Run a loopback test in 16-bit mode
    //
    else if(data_size == 16)
    {
        sdata2 = 0x0000;          // value is a don't care for 16-bit mode
        sdata1 = 0x0000;          // 16-bit value to send
        rdata2_point = 0x0000;    // value is a don't care for 16-bit mode
        rdata1_point = sdata1;
        for(;;)
        {
            mcbsp_xmit(sdata1,sdata2);
            sdata1++;

            //
            // Check for receive
            //
            while(McbspaRegs.SPCR1.bit.RRDY == 0 )
            {
                
            }
            
            rdata1 = McbspaRegs.DRR1.all;     // read DRR1
            
            if(rdata1 != rdata1_point) 
            {
                error();
            }
            rdata1_point++;

            //
            // Good place for a breakpoint
            // Check: rdatax_point = sdatax
            //        rdata1 = sdata1 - 1
            //
            __asm("    nop");                             
        }
    }
    
    //
    // Run a loopback test in 16-bit mode
    //
    else if(data_size == 32)
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

            //
            // Check for receive
            //
            while(McbspaRegs.SPCR1.bit.RRDY == 0 )
            {
                
            } 
            
            rdata2 = McbspaRegs.DRR2.all;
            rdata1 = McbspaRegs.DRR1.all;
            if(rdata1 != rdata1_point)
            {
                error();
            }
            if(rdata2 != rdata2_point)
            {
                error();
            }
            rdata1_point++;
            rdata2_point--;

            //
            // Good place for a breakpoint
            // Check: rdatax_point = sdatax
            //        rdata1 = sdata1 - 1
            //        rdata2 = sdata2 + 1
            //
            __asm("    nop");
        }
    }
}

//
// error -
//
void error(void)
{
    __asm("     ESTOP0");               // test failed!! Stop!
    for (;;);
}

//
// mcbsp_init_dlb -
//
void 
mcbsp_init_dlb()
{
    //
    // Reset FS generator, sample rate generator & transmitter
    //
    McbspaRegs.SPCR2.all=0x0000;
    
    McbspaRegs.SPCR1.all=0x0000;		// Reset Receiver, Right justify word
    
    //
    // Enable loopback mode for test. Comment out for normal McBSP
    // transfer mode.
    //
    McbspaRegs.SPCR1.bit.DLB = 1;      

    McbspaRegs.MFFINT.all=0x0;			// Disable all interrupts

    //
    // Single-phase frame, 1 word/frame, No companding	(Receive)
    //
    McbspaRegs.RCR2.all=0x0;
    McbspaRegs.RCR1.all=0x0;

    //
    // Single-phase frame, 1 word/frame, No companding	(Transmit)
    //
    McbspaRegs.XCR2.all=0x0;			
    McbspaRegs.XCR1.all=0x0;

    //
    // FSX generated internally, FSR derived from an external source
    //
    McbspaRegs.PCR.bit.FSXM = 1;	

    //
    // CLKX generated internally, CLKR derived from an external source
    //
    McbspaRegs.PCR.bit.CLKXM = 1;		

    //
    // CLKSM=1 (If SCLKME=0, i/p clock to SRG is LSPCLK)
    //    
    McbspaRegs.SRGR2.bit.CLKSM = 1;
    
    McbspaRegs.SRGR2.bit.FPER = 31;		// FPER = 32 CLKG periods

    McbspaRegs.SRGR1.bit.FWID = 0;      // Frame Width = 1 CLKG period
    McbspaRegs.SRGR1.bit.CLKGDV = 1;	// CLKG frequency = LSPCLK/(CLKGDV+1)

    delay_loop();                		// Wait at least 2 SRG clock cycles

    //
    // Initialize McBSP Data Length
    //
    if(data_size == 8)             	// Run a loopback test in 8-bit mode
    {
        InitMcbspa8bit();
    }
    if(data_size == 16)            	// Run a loopback test in 16-bit mode
    {
        InitMcbspa16bit();
    }
    if(data_size == 32)            	// Run a loopback test in 32-bit mode
    {
        InitMcbspa32bit();
    }

    McbspaRegs.SPCR2.bit.GRST=1;    // Enable the sample rate generator
    delay_loop();
    McbspaRegs.SPCR2.bit.XRST=1;    // Release TX from Reset
    McbspaRegs.SPCR1.bit.RRST=1;    // Release RX from Reset
    McbspaRegs.SPCR2.bit.FRST=1;    // Frame Sync Generator reset
}

//
// mcbsp_xmit - 
//
void 
mcbsp_xmit(int a, int b)
{
    McbspaRegs.DXR2.all=b;
    McbspaRegs.DXR1.all=a;
}

//
// End of File
//

