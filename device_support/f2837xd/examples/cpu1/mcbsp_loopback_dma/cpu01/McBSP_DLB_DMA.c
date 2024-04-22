//###########################################################################
//
// FILE:   McBSP_DLB.c
//
// TITLE:  McBSP Loopback
//
//! \addtogroup cpu01_example_list
//! <h1>McBSP Loopback with DMA (mcbsp_loopback_dma)</h1>
//!
//! This program is a McBSP example that uses the internal loopback of
//! the peripheral and utilizes the DMA to transfer data from one buffer
//! to the McBSP, and then from the McBSP to another buffer.
//!
//! Initially, sdata[] is filled with values from 0x0000- 0x007F.
//! The DMA moves the values in sdata[] one by one to the DXRx
//! registers of the McBSP. These values are transmitted and
//! subsequently received by the McBSP. Then, the DMA moves each
//! data value to rdata[] as it is received by the McBSP.
//!
//! The sent data buffer will alternate between: \n
//!    0000 0001 0002 0003 0004 0005 .... 007F   \n
//! and\n
//!    FFFF FFFE FFFD FFFC FFFB FFFA ....        \n
//!
//! Three different McBSP serial word sizes can be tested.
//! Before compiling this project, select the serial word
//! size of 8, 16 or 32 by using the \#define statements at the
//! beginning of the code.
//!
//! This example uses DMA channel 1 and 2 interrupts.
//! The incoming data is checked for accuracy.  If an error is
//! found the error() function is called and execution stops.
//!
//! By default for the McBSP examples, the McBSP sample rate generator
//! (SRG) input clock frequency is LSPCLK (80E6/4)
//! assuming SYSCLKOUT = 80 MHz.
//!
//! This example will execute until terminated by the user.
//!
//! \b Watch \b Variables: \n
//! - sdata  - Sent data buffer
//! - rdata  - Received data buffer
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
#define WORD_SIZE  8      // Run a loopback test in 8-bit mode
//#define WORD_SIZE 16      // Run a loopback test in 16-bit mode
//#define WORD_SIZE 32      // Run a loopback test in 32-bit mode

//
// Globals
//
#pragma DATA_SECTION(sdata, "ramgs0") // Place sdata and rdata buffers in
#pragma DATA_SECTION(rdata, "ramgs1") // DMA-accessible RAM
Uint16 sdata[128];                    // Sent Data
Uint16 rdata[128];                    // Received Data
Uint16 data_size;                     // Word Length variable

//
// Function Prototypes
//
__interrupt void local_D_INTCH1_ISR(void);
__interrupt void local_D_INTCH2_ISR(void);
void mcbsp_init_dlb(void);
void init_dma(void);
void init_dma_32(void);
void start_dma(void);
void error(void);

//
// Main
//
void main(void)
{
   Uint16 i;
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
   PieVectTable.DMA_CH1_INT= &local_D_INTCH1_ISR;
   PieVectTable.DMA_CH2_INT= &local_D_INTCH2_ISR;
   EDIS;      // Disable access to EALLOW protected registers

//
// Ensure DMA is connected to PF2SEL bridge (EALLOW protected)
//
   EALLOW;
   CpuSysRegs.SECMSEL.bit.PF2SEL = 1;
   EDIS;

//
// Step 4. User specific code, enable interrupts:
//
   data_size = WORD_SIZE;
   for (i=0; i<128; i++)
   {
       sdata[i] = i;      // Fill sdata with values between 0 and 0x007F
       rdata[i] = 0;      // Initialize rdata to all 0x0000.
   }
   if (data_size == 32)
   {
       init_dma_32();     // DMA Initialization for 32-bit transfers
   }
   else
   {
       init_dma();        // 1. When using DMA, initialize DMA with
                          //    peripheral interrupts first.
   }
   start_dma();
   mcbsp_init_dlb();      // 2. Then initialize and release peripheral
                          //   (McBSP) from Reset.

//
// Enable interrupts required for this example
//
   PieCtrlRegs.PIECTRL.bit.ENPIE = 1;   // Enable the PIE block
   PieCtrlRegs.PIEIER7.bit.INTx1 = 1;   // Enable PIE Group 7, INT 1 (DMA CH1)
   PieCtrlRegs.PIEIER7.bit.INTx2 = 1;   // Enable PIE Group 7, INT 2 (DMA CH2)

   IER=0x40;                            // Enable CPU INT groups 6 and 7
   EINT;                                // Enable Global Interrupts

//
// Step 5. IDLE loop. Just sit and loop forever (optional):
//
   for(;;);
}


//
// error - Function to handle errors and halt debugger
//
void error(void)
{
   __asm("     ESTOP0"); // Test failed!! Stop!
    for (;;);
}

//
// mcbsp_init_dlb - Configure McBSP with DLB mode enabled and initialize
//                  requested loopback bit mode based on data size
//
void mcbsp_init_dlb()
{
    McbspaRegs.SPCR2.all=0x0000;        // Reset FS generator, sample rate
                                        // generator & transmitter
    McbspaRegs.SPCR1.all=0x0000;        // Reset Receiver, Right justify word
    McbspaRegs.SPCR1.bit.DLB = 1;       // Enable DLB mode.

    McbspaRegs.MFFINT.all=0x0;          // Disable all interrupts

    McbspaRegs.RCR2.all=0x0;            // Single-phase frame, 1 word/frame,
                                        // No companding (Receive)
    McbspaRegs.RCR1.all=0x0;

    McbspaRegs.XCR2.all=0x0;            // Single-phase frame, 1 word/frame,
                                        // No companding (Transmit)
    McbspaRegs.XCR1.all=0x0;

    McbspaRegs.SRGR2.bit.CLKSM = 1;     // CLKSM=1 (If SCLKME=0, i/p clock to
                                        //          SRG is LSPCLK)
    McbspaRegs.SRGR2.bit.FPER = 31;     // FPER = 32 CLKG periods

    McbspaRegs.SRGR1.bit.FWID = 0;      // Frame Width = 1 CLKG period
    McbspaRegs.SRGR1.bit.CLKGDV = 0;    // CLKG frequency = LSPCLK/(CLKGDV+1)

    McbspaRegs.PCR.bit.FSXM = 1;        // FSX generated internally, FSR
                                        // derived from an external source
    McbspaRegs.PCR.bit.CLKXM = 1;       // CLKX generated internally, CLKR
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
    // Enable Sample rate generator
    //
    McbspaRegs.SPCR2.bit.GRST=1;        // Enable the sample rate generator
    delay_loop();                       // Wait at least 2 SRG clock cycles
    McbspaRegs.SPCR2.bit.XRST=1;        // Release TX from Reset
    McbspaRegs.SPCR1.bit.RRST=1;        // Release RX from Reset
    McbspaRegs.SPCR2.bit.FRST=1;        // Frame Sync Generator reset
}

//
// init_dma - DMA Initialization for data size <= 16-bit
//
void init_dma()
{
  EALLOW;
  DmaRegs.DMACTRL.bit.HARDRESET = 1;
  __asm(" NOP");                        // Only 1 NOP needed per Design

  DmaRegs.CH1.MODE.bit.CHINTE = 0;
  // Channel 1, McBSPA transmit
  DmaRegs.CH1.BURST_SIZE.all = 0;       // 1 word/burst
  DmaRegs.CH1.SRC_BURST_STEP = 0;       // no effect when using 1 word/burst
  DmaRegs.CH1.DST_BURST_STEP = 0;       // no effect when using 1 word/burst
  DmaRegs.CH1.TRANSFER_SIZE = 127;      // Interrupt every frame
                                        // (127 bursts/transfer)
  DmaRegs.CH1.SRC_TRANSFER_STEP = 1;    // Move to next word in buffer after
                                        // each word in a burst
  DmaRegs.CH1.DST_TRANSFER_STEP = 0;    // Don't move destination address
  DmaRegs.CH1.SRC_ADDR_SHADOW = (Uint32) &sdata[0];   // Start address = buffer
  DmaRegs.CH1.SRC_BEG_ADDR_SHADOW = (Uint32) &sdata[0];  // Not needed unless
                                                         // using wrap function
  DmaRegs.CH1.DST_ADDR_SHADOW = (Uint32) &McbspaRegs.DXR1.all; // Start address
                                                               // = McBSPA DXR
  //
  // Not needed unless using wrap function
  //
  DmaRegs.CH1.DST_BEG_ADDR_SHADOW = (Uint32) &McbspaRegs.DXR1.all;
  DmaRegs.CH1.CONTROL.bit.PERINTCLR = 1;   // Clear peripheral interrupt event
                                           // flag.
  DmaRegs.CH1.CONTROL.bit.ERRCLR = 1;      // Clear sync error flag
  DmaRegs.CH1.DST_WRAP_SIZE = 0xFFFF;      // Put to maximum - don't want
                                           // destination wrap.
  DmaRegs.CH1.SRC_WRAP_SIZE = 0xFFFF;      // Put to maximum - don't want
                                           // source wrap.
  DmaRegs.CH1.MODE.bit.CHINTE = 1;         // Enable channel interrupt
  DmaRegs.CH1.MODE.bit.CHINTMODE = 1;      // Interrupt at end of transfer
  DmaRegs.CH1.MODE.bit.PERINTE = 1;        // Enable peripheral interrupt event
  DmaRegs.CH1.MODE.bit.PERINTSEL = 1;      // Peripheral interrupt select =
                                           // McBSP MXSYNCA
  DmaClaSrcSelRegs.DMACHSRCSEL1.bit.CH1 = DMA_MXEVTA;
  DmaRegs.CH1.CONTROL.bit.PERINTCLR = 1;   // Clear any spurious interrupt flags

  //
  // Channel 2, McBSPA Receive
  //
  DmaRegs.CH2.MODE.bit.CHINTE = 0;
  DmaRegs.CH2.BURST_SIZE.all = 0;        // 1 word/burst
  DmaRegs.CH2.SRC_BURST_STEP = 0;        // no effect when using 1 word/burst
  DmaRegs.CH2.DST_BURST_STEP = 0;        // no effect when using 1 word/burst
  DmaRegs.CH2.TRANSFER_SIZE = 127;       // Interrupt every 127 bursts/transfer
  DmaRegs.CH2.SRC_TRANSFER_STEP = 0;     // Don't move source address
  DmaRegs.CH2.DST_TRANSFER_STEP = 1;     // Move to next word in buffer after
                                         // each word in a burst
  DmaRegs.CH2.SRC_ADDR_SHADOW = (Uint32) &McbspaRegs.DRR1.all; // Start address
                                                               // = McBSPA DRR
  //
  // Not needed unless using wrap function
  //
  DmaRegs.CH2.SRC_BEG_ADDR_SHADOW = (Uint32) &McbspaRegs.DRR1.all;
  DmaRegs.CH2.DST_ADDR_SHADOW = (Uint32) &rdata[0];      // Start address =
                                                         // Receive buffer
                                                         // (for McBSP-A)
  DmaRegs.CH2.DST_BEG_ADDR_SHADOW = (Uint32) &rdata[0];  // Not needed unless
                                                         // using wrap function
  DmaRegs.CH2.CONTROL.bit.PERINTCLR = 1; // Clear peripheral interrupt event
                                         // flag.
  DmaRegs.CH2.CONTROL.bit.ERRCLR = 1;    // Clear sync error flag
  DmaRegs.CH2.DST_WRAP_SIZE = 0xFFFF;    // Put to maximum - don't want
                                         // destination wrap.
  DmaRegs.CH2.SRC_WRAP_SIZE = 0xFFFF;    // Put to maximum - don't want
                                         // source wrap.
  DmaRegs.CH2.MODE.bit.CHINTE = 1;       // Enable channel interrupt
  DmaRegs.CH2.MODE.bit.CHINTMODE = 1;    // Interrupt at end of transfer
  DmaRegs.CH2.MODE.bit.PERINTE = 1;      // Enable peripheral interrupt event
  DmaRegs.CH2.MODE.bit.PERINTSEL = 2;    // Peripheral interrupt select =
                                         // McBSP MRSYNCA
  DmaClaSrcSelRegs.DMACHSRCSEL1.bit.CH2 = DMA_MREVTA;
  DmaRegs.CH2.CONTROL.bit.PERINTCLR = 1; // Clear any spurious interrupt flags
  EDIS;
}

//
// init_dma_32 - DMA Initialization for data size > 16-bit and <= 32-bit.
//
void init_dma_32()
{
  EALLOW;
  DmaRegs.DMACTRL.bit.HARDRESET = 1;
  __asm(" NOP");                        // Only 1 NOP needed per Design

  // Channel 1, McBSPA transmit
  DmaRegs.CH1.MODE.bit.PERINTSEL = DMA_MXEVTA;
  DmaRegs.CH1.BURST_SIZE.all = 1;       // 2 word/burst
  DmaRegs.CH1.SRC_BURST_STEP = 1;       // increment 1 16-bit addr. btwn words
  DmaRegs.CH1.DST_BURST_STEP = 1;       // increment 1 16-bit addr. btwn words
  DmaRegs.CH1.TRANSFER_SIZE = 63;       // Interrupt every 63 bursts/transfer
  DmaRegs.CH1.SRC_TRANSFER_STEP = 1;    // Move to next word in buffer after
                                        // each word in a burst.
  DmaRegs.CH1.DST_TRANSFER_STEP = 0xFFFF;    // Go back to DXR2
  DmaRegs.CH1.SRC_ADDR_SHADOW = (Uint32) &sdata[0];  // Start address = buffer
  DmaRegs.CH1.SRC_BEG_ADDR_SHADOW = (Uint32) &sdata[0]; // Not needed unless
                                                        // using wrap function.
  DmaRegs.CH1.DST_ADDR_SHADOW = (Uint32) &McbspaRegs.DXR2.all; // Start address
                                                               // = McBSPA DXR2

  //
  // Not needed unless using wrap function
  //
  DmaRegs.CH1.DST_BEG_ADDR_SHADOW = (Uint32) &McbspaRegs.DXR2.all;
  DmaRegs.CH1.CONTROL.bit.ERRCLR = 1;   // Clear sync error flag
  DmaRegs.CH1.DST_WRAP_SIZE = 0xFFFF;   // Put to maximum - don't want
                                        // destination wrap
  DmaRegs.CH1.SRC_WRAP_SIZE = 0xFFFF;   // Put to maximum - don't want
                                        // source wrap
  DmaRegs.CH1.MODE.bit.CHINTE = 1;      // Enable channel interrupt
  DmaRegs.CH1.MODE.bit.CHINTMODE = 1;   // Interrupt at end of transfer
  DmaRegs.CH1.MODE.bit.PERINTE = 1;     // Enable peripheral interrupt event
  DmaRegs.CH1.MODE.bit.PERINTSEL = 1;   // Peripheral interrupt select = McBSP
                                        // MXSYNCA
  DmaClaSrcSelRegs.DMACHSRCSEL1.bit.CH1 = DMA_MXEVTA;
  DmaRegs.CH1.CONTROL.bit.PERINTCLR = 1;  // Clear any spurious interrupt flags

  //
  // Channel 2, McBSPA Receive
  //
  DmaRegs.CH2.BURST_SIZE.all = 1;       // 2 words/burst
  DmaRegs.CH2.SRC_BURST_STEP = 1;       // Increment 1 16-bit addr. btwn words
  DmaRegs.CH2.DST_BURST_STEP = 1;       // Increment 1 16-bit addr. btwn words
  DmaRegs.CH2.TRANSFER_SIZE = 63;       // Interrupt every 63 bursts/transfer
  DmaRegs.CH2.SRC_TRANSFER_STEP = 0xFFFF;  // Decrement  back to DRR2
  DmaRegs.CH2.DST_TRANSFER_STEP = 1;       // Move to next word in buffer after
                                           // each word in a burst
  DmaRegs.CH2.SRC_ADDR_SHADOW = (Uint32) &McbspaRegs.DRR2.all; // Start address
                                                               // = McBSPA DRR
  //
  // Not needed unless using wrap function
  //
  DmaRegs.CH2.SRC_BEG_ADDR_SHADOW = (Uint32) &McbspaRegs.DRR2.all;
  DmaRegs.CH2.DST_ADDR_SHADOW = (Uint32) &rdata[0];  // Start address =
                                                     // Receive buffer(McBSP-A)
  //
  // Not needed unless using wrap function
  //
  DmaRegs.CH2.DST_BEG_ADDR_SHADOW = (Uint32) &rdata[0];
  DmaRegs.CH2.CONTROL.bit.ERRCLR = 1;    // Clear sync error flag
  DmaRegs.CH2.DST_WRAP_SIZE = 0xFFFF;    // Put to maximum - don't want
                                         // destination wrap
  DmaRegs.CH2.SRC_WRAP_SIZE = 0xFFFF;    // Put to maximum - don't want
                                         // source wrap
  DmaRegs.CH2.MODE.bit.CHINTE = 1;       // Enable channel interrupt
  DmaRegs.CH2.MODE.bit.CHINTMODE = 1;    // Interrupt at end of transfer
  DmaRegs.CH2.MODE.bit.PERINTE = 1;      // Enable peripheral interrupt event
  DmaRegs.CH2.MODE.bit.PERINTSEL = 2;    // Peripheral interrupt select =
                                         // McBSP MRSYNCA
  DmaClaSrcSelRegs.DMACHSRCSEL1.bit.CH2 = DMA_MREVTA;
  DmaRegs.CH2.CONTROL.bit.PERINTCLR = 1;  // Clear any spurious interrupt flags
  EDIS;
}

//
// start_dma - Start the DMA channels' 1 and 2
//
void start_dma (void)
{
  EALLOW;
  DmaRegs.CH1.CONTROL.bit.RUN = 1;      // Start DMA Transmit from McBSP-A
  DmaRegs.CH2.CONTROL.bit.RUN = 1;      // Start DMA Receive from McBSP-A
  EDIS;
}

//
// local_D_INTCH1_ISR - DMA ISR for channel 1 (INT7.1)
//
__interrupt void local_D_INTCH1_ISR(void)
{
    EALLOW;      // NEED TO EXECUTE EALLOW INSIDE ISR !!!
    DmaRegs.CH1.CONTROL.bit.HALT = 1;

    //
    // To receive more interrupts from this PIE group, acknowledge
    // this interrupt
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;
    EDIS;
    return;
}

//
// local_D_INTCH2_ISR - DMA ISR for channel 2 (INT7.2)
//
__interrupt void local_D_INTCH2_ISR(void)
{
    Uint16 i;
    EALLOW;      // NEED TO EXECUTE EALLOW INSIDE ISR !!!
    DmaRegs.CH2.CONTROL.bit.HALT = 1;

    //
    // To receive more interrupts from this PIE group, acknowledge this
    // interrupt
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;
    for (i=0; i<128; i++)
    {
        if(data_size == 8)
        {
            if((rdata[i]&0x00FF) != (sdata[i]&0x00FF))
            {
              error();  // STOP if there is an error !!
            }
        }
        else if(data_size == 16)
        {
            if (rdata[i] != sdata[i])
            {
              error();  // STOP if there is an error !!
            }
        }
        else if(data_size == 32)
        {
            if ((rdata[i])!=(sdata[i]))
            {
              error ();
            }
        }
   }
   EDIS;

   return;
}

//
// End of file
//
