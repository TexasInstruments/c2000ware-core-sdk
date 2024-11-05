//###########################################################################
//
// FILE:   dma_gsram_transfer_cpu01.c
//
// TITLE:  DMA GSRAM Transfer
//
//! \addtogroup cpu01_example_list
//! <h1>DMA GSRAM Transfer (dma_gsram_transfer)</h1>
//!
//!  This example uses one DMA channel to transfer data from a buffer in
//!  RAMGS0 to a buffer in RAMGS1. The example sets the DMA channel
//!  PERINTFRC bit repeatedly until the transfer of 16 bursts (where each
//!  burst is 8 16-bit words) has been completed. When the whole transfer is
//!  complete, it will trigger the DMA interrupt.
//!
//!  \b Watch \b Variables \n
//!  - \b sdata - Data to send
//!  - \b rdata - Received data
//!
//
//###########################################################################
//
//
// 
// C2000Ware v5.04.00.00
//
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
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
#include "f28x_project.h"

//
// DMA data sections
//
#pragma DATA_SECTION(sdata, "ramgs0");  // map the TX data to memory
#pragma DATA_SECTION(rdata, "ramgs1");  // map the RX data to memory

//
// Defines
//
#define BURST       7       // write 7 to the register for a burst size of 8
#define TRANSFER    15      // [(MEM_BUFFER_SIZE/(BURST + 1)) - 1]

//
// Globals
//
Uint16 sdata[128];   // Send data buffer
Uint16 rdata[128];   // Receive data buffer
volatile Uint16 *DMADest;
volatile Uint16 *DMASource;
volatile Uint16 done;

//
// Function Prototypes
//
__interrupt void local_D_INTCH6_ISR(void);
void dma_init(void);
void error();

//
// Main
//
void main(void)
{
   Uint16 i;

//
// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
//
   InitSysCtrl();

//
// Step 2. Initialize GPIO:
// illustrates how to set the GPIO to it's default state.
//
// InitGpio();  // Skipped for this example

//
// Step 3. Initialize PIE vector table:
// Disable and clear all CPU interrupts
//
   DINT;
   IER = 0x0000;
   IFR = 0x0000;

//
// Initialize PIE control registers to their default state:
//
   InitPieCtrl();

//
// Initialize the PIE vector table with pointers to the default Interrupt
// Service Routines (ISR).
//
   InitPieVectTable();

//
// Interrupts that are used in this example are re-mapped to
// ISR functions found within this file.
//
   EALLOW;  // This is needed to write to EALLOW protected registers
   PieVectTable.DMA_CH6_INT= &local_D_INTCH6_ISR;
   EDIS;    // This is needed to disable write to EALLOW protected registers

//
// Step 4. Initialize the Device Peripherals:
//
   dma_init();  // set up the dma

//
// Step 5. User specific code, enable interrupts:
// Initialize the data buffers
//
   for(i = 0; i < 128; i++)
   {
       sdata[i] = i;
       rdata[i] = 0;
   }

//
// Enable interrupts required for this example
//
   PieCtrlRegs.PIECTRL.bit.ENPIE = 1;   // Enable the PIE block
   PieCtrlRegs.PIEIER7.bit.INTx6 = 1;   // Enable PIE Group 7, INT 2 (DMA CH2)
   IER= M_INT7;                         // Enable CPU INT6
   EINT;                                // Enable Global Interrupts

   StartDMACH6();      // Start DMA channel

   done = 0;           // Test is not done yet

   while(!done)        // wait until the DMA transfer is complete
   {
       EALLOW;
       DmaRegs.CH6.CONTROL.bit.PERINTFRC = 1;
       EDIS;

       DELAY_US(1000);
   }

//
// When the DMA transfer is complete the program will stop here
//
   ESTOP0;
}

//
// error - Error Function which will halt the debugger
//
void error(void)
{
   asm("     ESTOP0");  //Test failed!! Stop!
    for (;;);
}

//
// dma_init - DMA setup for both TX and RX channels.
//
void dma_init()
{
    //
    // Refer to dma.c for the descriptions of the following functions.
    //

    //
    //Initialize DMA
    //
    DMAInitialize();

    DMASource = (volatile Uint16 *)sdata;
    DMADest = (volatile Uint16 *)rdata;

    //
    // configure DMA CH6
    //
    DMACH6AddrConfig(DMADest,DMASource);
    DMACH6BurstConfig(BURST,1,1);
    DMACH6TransferConfig(TRANSFER,1,1);
    DMACH6ModeConfig(0,PERINT_ENABLE,ONESHOT_DISABLE,CONT_DISABLE,
                     SYNC_DISABLE,SYNC_SRC,OVRFLOW_DISABLE,SIXTEEN_BIT,
                     CHINT_END,CHINT_ENABLE);
}

//
// local_D_INTCH6_ISR - DMA Channel6 ISR
//
__interrupt void local_D_INTCH6_ISR(void)
{
    Uint16 i;

    EALLOW;  // NEED TO EXECUTE EALLOW INSIDE ISR !!!
    DmaRegs.CH6.CONTROL.bit.HALT = 1;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP7; // ACK to receive more interrupts
                                            // from this PIE group
    EDIS;

    for( i = 0; i < 128; i++ )
    {
        //
        // check for data integrity
        //
        if (rdata[i] != i)
        {
            error();
        }
    }

    done = 1; // Test done.
    return;
}

//
// End of file
//
