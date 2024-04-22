//###########################################################################
//
// FILE:   McBSP_DLB_int.c
//
// TITLE:  McBSP Loopback with Interrupts
//
//! \addtogroup cpu01_example_list
//! <h1>McBSP Loopback with Interrupts (mcbsp_loopback_interrupts)</h1>
//!
//!  This program is a McBSP example that uses the internal loopback of
//!  the peripheral.  Both Rx and Tx interrupts are enabled.
//!
//!  Incrementing values from 0x0000 to 0x00FF are being sent and received.
//!
//!  This pattern is repeated forever.
//!
//!  By default for the McBSP examples, the McBSP sample rate generator (SRG)
//!  input clock frequency is LSPCLK 80E6/4.
//!
//! \b Watch \b Variables: \n
//! - sdata - Sent data word
//! - rdata - Received data word
//! - rdata_point - Tracks last position in receive stream for error checking
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
// Globals
//
Uint16 sdata;       // Sent Data
Uint16 rdata;       // Received Data
Uint16 rdata_point; // Keep track of where we
                    // are in the data stream

//
// Function Prototypes
//
__interrupt void Mcbsp_TxINTA_ISR(void);
__interrupt void Mcbsp_RxINTA_ISR(void);
void mcbsp_init_dlb(void);
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
// Setup only the GP I/O only for McBSP-A functionality
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

//
// Interrupts that are used in this example are re-mapped to
// ISR functions found within this file.
//
   EALLOW;    // Allow access to EALLOW protected registers
   PieVectTable.MCBSPA_RX_INT = &Mcbsp_RxINTA_ISR;
   PieVectTable.MCBSPA_TX_INT = &Mcbsp_TxINTA_ISR;
   EDIS;      // Disable access to EALLOW protected registers

//
// Step 4. Initialize the Device Peripherals:
//
   mcbsp_init_dlb();      // For this example, only initialize the Mcbsp

//
// Step 5. User specific code, enable interrupts:
//
   sdata = 0;
   rdata_point = sdata;

//
// Enable interrupts required for this example
//
   PieCtrlRegs.PIECTRL.bit.ENPIE = 1;   // Enable the PIE block
   PieCtrlRegs.PIEIER6.bit.INTx5 = 1;   // Enable PIE Group 6, INT 5
   PieCtrlRegs.PIEIER6.bit.INTx6 = 1;   // Enable PIE Group 6, INT 6
   IER = 0x20;                          // Enable CPU INT6
   EINT;                                // Enable Global Interrupts

//
// Step 6. IDLE loop. Just sit and loop forever (optional):
//
   for(;;);
}

//
// error - Function to halt debugger on error
//
void error(void)
{
   __asm("     ESTOP0"); // Test failed!! Stop!
    for (;;);
}

//
// mcbsp_init_dlb - Initialize MCBSP with digital loopback setup
//
void mcbsp_init_dlb()
{
//
// RESET MCBSP
//
   McbspaRegs.SPCR2.bit.FRST = 0; // Frame Sync generator reset
   McbspaRegs.SPCR2.bit.GRST = 0; // Sample Rate generator Reset
   McbspaRegs.SPCR2.bit.XRST = 0; // Transmitter reset
   McbspaRegs.SPCR1.bit.RRST = 0; // Receiver reset

//
// Initialize McBSP Registers
// McBSP register settings for Digital loop back
//
   McbspaRegs.SPCR2.all = 0x0000; // XRST =0
   McbspaRegs.SPCR1.all = 0x8000; // RRST =0, DLB enabled
   McbspaRegs.RCR2.all = 0x0001;  // RDATDLY = 1
   McbspaRegs.RCR1.all = 0x0;
   McbspaRegs.XCR2.all = 0x0001;  // XDATDLY = 1
   McbspaRegs.XCR1.all = 0x0;

   McbspaRegs.SRGR2.all = 0x3140;
   McbspaRegs.SRGR1.all = 0x010f;
   McbspaRegs.MCR2.all = 0x0;
   McbspaRegs.MCR1.all = 0x0;
   McbspaRegs.PCR.all = 0x0A00;

   McbspaRegs.MFFINT.bit.XINT = 1; // Enable Transmit Interrupts
   McbspaRegs.MFFINT.bit.RINT = 1; // Enable Receive Interrupts

//
// Enable Sample rate generator
//
   McbspaRegs.SPCR2.bit.GRST = 1;
   delay_loop();                   // Wait at least 2 SRG clock cycles

//
// Enable TX/RX unit
//
   McbspaRegs.SPCR2.bit.XRST = 1;
   McbspaRegs.SPCR1.bit.RRST = 1;

//
// Frame Sync generator reset
//
   McbspaRegs.SPCR2.bit.FRST = 1;
}

//
// Mcbsp_TxINTA_ISR - Mcbsp Transmit ISR
//
__interrupt void Mcbsp_TxINTA_ISR(void)
{
    McbspaRegs.DXR1.all= sdata;
    sdata = (sdata+1)& 0x00FF ;

    //
    // To receive more interrupts from this PIE group, acknowledge
    // this interrupt
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;
}

//
// Mcbsp_RxINTA_ISR - Mcbsp Receive ISR
//
__interrupt void Mcbsp_RxINTA_ISR(void)
{
    rdata=McbspaRegs.DRR1.all;
    if (rdata != ( (rdata_point) & 0x00FF) )
    {
        error();
    }
    rdata_point = (rdata_point+1) & 0x00FF;

    //
    // To receive more interrupts from this PIE group, acknowledge this
    // interrupt
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;
}

//
// End of file
//
