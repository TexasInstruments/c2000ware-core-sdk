//###########################################################################
//
// FILE:   Example_2837xD_Spi_dma.c
//
// TITLE:  SPI Digital Loop Back with DMA Example.
//
//! \addtogroup cpu01_example_list
//! <h1>SPI Digital Loop Back with DMA (spi_loopback_dma)</h1>
//!
//!  This program uses the internal loop back test mode of the peripheral.
//!  Other then boot mode pin configuration, no other hardware configuration
//!  is required. Both DMA Interrupts and the SPI FIFOs are used.
//!
//!  A stream of data is sent and then compared to the received stream.
//!  The sent data looks like this: \n
//!  0000 0001 \n
//!  0001 0002 \n
//!  0002 0003 \n
//!  .... \n
//!  007E 007F \n
//!
//!  \b Watch \b Variables \n
//!  - \b sdata - Data to send
//!  - \b rdata - Received data
//!  - \b rdata_point - Used to keep track of the last position in
//!    the receive stream for error checking
//!
//
//###########################################################################
//
// $Release Date:  $
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
#define BURST         (FIFO_LVL-1)    // burst size should be less than 8
#define TRANSFER      15              // [(MEM_BUFFER_SIZE/FIFO_LVL)-1]
#define FIFO_LVL      8               // FIFO Interrupt Level

//
// Globals
//
#pragma DATA_SECTION(sdata, "ramgs0");    // map the TX data to memory
#pragma DATA_SECTION(rdata, "ramgs1");    // map the RX data to memory
Uint16 sdata[128];     // Send data buffer
Uint16 rdata[128];     // Receive data buffer
Uint16 rdata_point;    // Keep track of where we are
                       // in the data stream to check received data
volatile Uint16 *DMADest;
volatile Uint16 *DMASource;
volatile Uint16 done;

//
// Function Prototypes
//
__interrupt void local_D_INTCH5_ISR(void);
__interrupt void local_D_INTCH6_ISR(void);
void delay_loop(void);
void dma_init(void);
void spi_fifo_init(void);
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
// This example function is found in the F2837xD_SysCtrl.c file.
//
   InitSysCtrl();

//
// Step 2. Initialize GPIO:
// This example function is found in the F2837xD_Gpio.c file and
// illustrates how to set the GPIO to it's default state.
// Setup only the GP I/O only for SPI-A functionality
//
//   InitSpiaGpio();

//
// Step 3. Initialize PIE vector table:
// Disable and clear all CPU interrupts
//
   DINT;
   IER = 0x0000;
   IFR = 0x0000;

//
// Initialize PIE control registers to their default state:
// This function is found in the F2837xD_PieCtrl.c file.
//
   InitPieCtrl();

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
   EALLOW;  // This is needed to write to EALLOW protected registers
   PieVectTable.DMA_CH5_INT= &local_D_INTCH5_ISR;
   PieVectTable.DMA_CH6_INT= &local_D_INTCH6_ISR;
   EDIS;   // This is needed to disable write to EALLOW protected registers

//
// Step 4. Initialize the Device Peripherals:
//
   dma_init();            // Set up DMA for SPI configuration
   spi_fifo_init();       // Initialize the SPI only

//
// Ensure DMA is connected to Peripheral Frame 2 bridge (EALLOW protected)
//
    EALLOW;
    CpuSysRegs.SECMSEL.bit.PF2SEL = 1;
    EDIS;

//
// Step 5. User specific code, enable interrupts:
//

//
// Initialize the data buffers
//
    for(i=0; i<128; i++)
    {
        sdata[i] = i;
        rdata[i]= 0;
    }
    rdata_point = 0;

//
// Enable interrupts required for this example
//
   PieCtrlRegs.PIECTRL.bit.ENPIE = 1;   // Enable the PIE block
   PieCtrlRegs.PIEIER7.bit.INTx5 = 1;   // Enable PIE Group 7, INT 1 (DMA CH1)
   PieCtrlRegs.PIEIER7.bit.INTx6 = 1;   // Enable PIE Group 7, INT 2 (DMA CH2)
   IER= M_INT7;                         // Enable CPU INT6
   EINT;                                // Enable Global Interrupts

   StartDMACH6();                       // Start SPI RX DMA channel
   StartDMACH5();                       // Start SPI TX DMA channel

   done = 0;                            // Test is not done yet

   while(!done);                        // wait until the DMA transfer is
                                        // complete

   //
   // when the DMA transfer is complete the program will stop here
   //
   ESTOP0;
}

//
// delay_loop - Function to add delay
//
void delay_loop()
{
    long i;
    for (i = 0; i < 1000000; i++) {}
}

//
// error - Halt debugger when error received
//
void error(void)
{
   asm("     ESTOP0");  //Test failed!! Stop!
   for (;;);
}

//
// spi_fifo_init - Initialize SPIA FIFO
//
void spi_fifo_init()
{
    //
    // Initialize SPI FIFO registers
    //
    SpiaRegs.SPIFFRX.all=0x2040;             // RX FIFO enabled, clear FIFO int
    SpiaRegs.SPIFFRX.bit.RXFFIL = FIFO_LVL;  // Set RX FIFO level

    SpiaRegs.SPIFFTX.all=0xE040;             // FIFOs enabled, TX FIFO released,
    SpiaRegs.SPIFFTX.bit.TXFFIL = FIFO_LVL;  // Set TX FIFO level

    //
    // Initialize core SPI registers
    //
    InitSpi();
}

//
// dma_init - DMA setup for both TX and RX channels.
//
void dma_init()
{
    //
    // Initialize DMA
    //
    DMAInitialize();

    DMASource = (volatile Uint16 *)sdata;
    DMADest = (volatile Uint16 *)rdata;

    //
    // configure DMACH5 for TX
    //
    DMACH5AddrConfig(&SpiaRegs.SPITXBUF,DMASource);
    DMACH5BurstConfig(BURST,1,0);         // Burst size, src step, dest step
    DMACH5TransferConfig(TRANSFER,1,0);   // transfer size, src step, dest step
    DMACH5ModeConfig(DMA_SPIATX,PERINT_ENABLE,ONESHOT_DISABLE,CONT_DISABLE,
                     SYNC_DISABLE,SYNC_SRC,OVRFLOW_DISABLE,SIXTEEN_BIT,
                     CHINT_END,CHINT_ENABLE);

    //
    // configure DMA CH2 for RX
    //
    DMACH6AddrConfig(DMADest,&SpiaRegs.SPIRXBUF);
    DMACH6BurstConfig(BURST,0,1);
    DMACH6TransferConfig(TRANSFER,0,1);
    DMACH6ModeConfig(DMA_SPIARX,PERINT_ENABLE,ONESHOT_DISABLE,CONT_DISABLE,
                     SYNC_DISABLE,SYNC_SRC,OVRFLOW_DISABLE,SIXTEEN_BIT,
                     CHINT_END,CHINT_ENABLE);
}

//
// local_D_INTCH5_ISR - DMA Channel 5 ISR
//
__interrupt void local_D_INTCH5_ISR(void)
{
    EALLOW;  // NEED TO EXECUTE EALLOW INSIDE ISR !!!
    DmaRegs.CH5.CONTROL.bit.HALT=1;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP7; // ACK to receive more interrupts
                                            // from this PIE group
    EDIS;
    return;
}

//
// local_D_INTCH6_ISR - DMA Channel 6 ISR
//
__interrupt void local_D_INTCH6_ISR(void)
{
    Uint16 i;

    EALLOW;  // NEED TO EXECUTE EALLOW INSIDE ISR !!!
    DmaRegs.CH6.CONTROL.bit.HALT = 1;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP7; // ACK to receive more interrupts
                                            // from this PIE group
    EDIS;

    for( i = 0; i<128; i++ )
    {
        //
        // check for data integrity
        //
        if(rdata[i] != i)
        {
            error();
        }
    }

    done = 1;  // test done.
    return;
}

//
// End of file
//
