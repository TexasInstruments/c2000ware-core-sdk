//###########################################################################
//
// FILE:    F2806x_McBSP.c
//
// TITLE:   F2806x Device McBSP Initialization & Support Functions.
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
// MCBSP_INIT_DELAY determines the amount of CPU cycles in the 2 sample rate
// generator (SRG) cycles required for the Mcbsp initialization routine.
// MCBSP_CLKG_DELAY determines the amount of CPU cycles in the 2 clock
// generator (CLKG) cycles required for the Mcbsp initialization routine.
//
#define CPU_SPD              80E6

//
// SRG input is LSPCLK (SYSCLKOUT/2) for examples
//
#define MCBSP_SRG_FREQ       CPU_SPD/2

#define CLKGDV_VAL           1

//
// # of CPU cycles in 2 SRG cycles-init delay
//
#define MCBSP_INIT_DELAY     2*(CPU_SPD/MCBSP_SRG_FREQ)

//
// # of CPU cycles in 2 CLKG cycles-init delay
//
#define MCBSP_CLKG_DELAY     2*(CPU_SPD/(MCBSP_SRG_FREQ/(1+CLKGDV_VAL)))


//
// InitMcbsp - This function initializes the McBSP to a known state.
//
#if DSP28_MCBSPA
void delay_loop(void);      // Delay function used for SRG initialization
void clkg_delay_loop(void); // Delay function used for CLKG initialization
#endif // endif DSP28_MCBSPA

#if DSP28_MCBSPA
void
InitMcbsp(void)
{
    InitMcbspa();
}
#endif // endif DSP28_MCBSPA

#if DSP28_MCBSPA
//
// InitMcbspa - McBSP-A register settings
//
void
InitMcbspa(void)
{
    //
    // Reset FS generator, sample rate generator & transmitter
    //    
    McbspaRegs.SPCR2.all=0x0000;
    McbspaRegs.SPCR1.all=0x0000;        // Reset Receiver, Right justify word
    
    //
    // Enable loopback mode for test. Comment out for normal McBSP transfer
    // mode
    //
    McbspaRegs.SPCR1.bit.DLB = 1;

    McbspaRegs.MFFINT.all=0x0;          // Disable all interrupts

    //
    // Single-phase frame, 1 word/frame, No companding  (Receive)
    //
    McbspaRegs.RCR2.all=0x0;
    
    McbspaRegs.RCR1.all=0x0;

    //
    // Single-phase frame, 1 word/frame, No companding  (Transmit)
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
    
    McbspaRegs.SRGR2.bit.FPER = 31;     // FPER = 32 CLKG periods

    McbspaRegs.SRGR1.bit.FWID = 0;      // Frame Width = 1 CLKG period
    
    //
    // CLKG frequency = LSPCLK/(CLKGDV+1)
    //
    McbspaRegs.SRGR1.bit.CLKGDV = CLKGDV_VAL;

    delay_loop();                // Wait at least 2 SRG clock cycles

    McbspaRegs.SPCR2.bit.GRST=1; // Enable the sample rate generator
    clkg_delay_loop();           // Wait at least 2 CLKG cycles
    McbspaRegs.SPCR2.bit.XRST=1; // Release TX from Reset
    McbspaRegs.SPCR1.bit.RRST=1; // Release RX from Reset
    McbspaRegs.SPCR2.bit.FRST=1; // Frame Sync Generator reset
}

//
// InitMcbspa8bit - McBSP-A Data Lengths
//
void
InitMcbspa8bit(void)
{
    McbspaRegs.RCR1.bit.RWDLEN1=0;     // 8-bit word
    McbspaRegs.XCR1.bit.XWDLEN1=0;     // 8-bit word
}

//
// InitMcbspa12bit - 
//
void
InitMcbspa12bit(void)
{
    McbspaRegs.RCR1.bit.RWDLEN1=1;     // 12-bit word
    McbspaRegs.XCR1.bit.XWDLEN1=1;     // 12-bit word
}

//
// InitMcbspa16bit - 
//
void
InitMcbspa16bit(void)
{
    McbspaRegs.RCR1.bit.RWDLEN1=2;      // 16-bit word
    McbspaRegs.XCR1.bit.XWDLEN1=2;      // 16-bit word
}

//
// InitMcbspa20bit - 
//
void
InitMcbspa20bit(void)
{
    McbspaRegs.RCR1.bit.RWDLEN1=3;     // 20-bit word
    McbspaRegs.XCR1.bit.XWDLEN1=3;     // 20-bit word
}

//
// InitMcbspa24bit -
//
void
InitMcbspa24bit(void)
{
    McbspaRegs.RCR1.bit.RWDLEN1=4;     // 24-bit word
    McbspaRegs.XCR1.bit.XWDLEN1=4;     // 24-bit word
}

//
// InitMcbspa32bit - 
//
void
InitMcbspa32bit(void)
{
    McbspaRegs.RCR1.bit.RWDLEN1=5;     // 32-bit word
    McbspaRegs.XCR1.bit.XWDLEN1=5;     // 32-bit word
}

//
// InitMcbspGpio -
//
void
InitMcbspGpio(void)
{
    InitMcbspaGpio();
}

//
// InitMcbspaGpio - 
//
void
InitMcbspaGpio(void)
{
    EALLOW;

    //
    // Configure McBSP-A pins using GPIO regs
    // This specifies which of the possible GPIO pins will be McBSP functional 
    // pins. Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAMUX2.bit.GPIO20 = 2;    // GPIO20 is MDXA pin
    GpioCtrlRegs.GPAMUX2.bit.GPIO21 = 2;    // GPIO21 is MDRA pin
    GpioCtrlRegs.GPAMUX2.bit.GPIO22 = 2;    // GPIO22 is MCLKXA pin
    GpioCtrlRegs.GPBMUX2.bit.GPIO58 = 1;    // GPIO58 is MCLKRA pin
    GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 2;    // GPIO23 is MFSXA pin
    GpioCtrlRegs.GPBMUX1.bit.GPIO44 = 1;    // GPIO44 is MFSRA pin

    GpioCtrlRegs.GPBMUX2.bit.GPIO50 = 2;    // GPIO50 is MDXA pin
    GpioCtrlRegs.GPBMUX2.bit.GPIO51 = 2;    // GPIO51 is MDRA pin
    GpioCtrlRegs.GPBMUX2.bit.GPIO52 = 2;    // GPIO52 is MCLKXA pin
    GpioCtrlRegs.GPBMUX2.bit.GPIO53 = 2;    // GPIO53 is MFSXA pin

    //
    // Enable internal pull-up for the selected pins
    // Pull-ups can be enabled or disabled by the user.
    // This will enable the pullups for the specified pins.
    // Comment out other unwanted lines.
    //
    //GpioCtrlRegs.GPAPUD.bit.GPIO20 = 0;   // Enable pull-up on GPIO20 (MDXA)
    //GpioCtrlRegs.GPAPUD.bit.GPIO21 = 0;   // Enable pull-up on GPIO21 (MDRA)
    //GpioCtrlRegs.GPAPUD.bit.GPIO22 = 0;   // Enable pull-up on GPIO22 (MCLKXA)
    //GpioCtrlRegs.GPBPUD.bit.GPIO58 = 0;   // Enable pull-up on GPIO58 (MCLKRA)
    //GpioCtrlRegs.GPAPUD.bit.GPIO23 = 0;   // Enable pull-up on GPIO23 (MFSXA)
    //GpioCtrlRegs.GPBPUD.bit.GPIO44 = 0;   // Enable pull-up on GPIO44 (MFSRA)

    //GpioCtrlRegs.GPBPUD.bit.GPIO50 = 0;   // Enable pull-up on GPIO50 (MDXA)
    //GpioCtrlRegs.GPBPUD.bit.GPIO51 = 0;   // Enable pull-up on GPIO51 (MDRA)
    //GpioCtrlRegs.GPBPUD.bit.GPIO52 = 0;   // Enable pull-up on GPIO52 (MCLKXA)
    //GpioCtrlRegs.GPBPUD.bit.GPIO53 = 0;   // Enable pull-up on GPIO53 (MFSXA)

    //
    // Set qualification for selected input pins to asynch only
    // This will select asynch (no qualification) for the selected pins.
    // Comment out other unwanted lines.
    //
    GpioCtrlRegs.GPAQSEL2.bit.GPIO21 = 3;   // Asynch input GPIO21 (MDRA)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO22 = 3;   // Asynch input GPIO22 (MCLKXA)
    GpioCtrlRegs.GPBQSEL2.bit.GPIO58 = 3; 	// Asynch input GPIO58 (MCLKRA)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO23 = 3;   // Asynch input GPIO23 (MFSXA)
    GpioCtrlRegs.GPBQSEL1.bit.GPIO44 = 3; 	// Asynch input GPIO44 (MFSRA)

    GpioCtrlRegs.GPBQSEL2.bit.GPIO51 = 3; 	// Asynch input GPIO51 (MDRA)
    GpioCtrlRegs.GPBQSEL2.bit.GPIO52 = 3; 	// Asynch input GPIO52 (MCLKXA)
    GpioCtrlRegs.GPBQSEL2.bit.GPIO53 = 3; 	// Asynch input GPIO53 (MFSXA)

    EDIS;
}

//
// delay_loop - 
//
void
delay_loop(void)
{
    long      i;
    
    //
    // delay in McBsp init. must be at least 2 SRG cycles
    //
    for (i = 0; i < MCBSP_INIT_DELAY; i++)
    {
        
    }
}

//
// clkg_delay_loop - 
//
void
clkg_delay_loop(void)
{
    long      i;
    
    //
    // delay in McBsp init. must be at least 2 SRG cycles
    //
    for (i = 0; i < MCBSP_CLKG_DELAY; i++)
    {
        
    }
}
#endif // endif DSP28_MCBSPA

//
// End of File
//

