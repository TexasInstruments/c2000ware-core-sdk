//###########################################################################
//
// FILE:   Example_2837xDSpi_FFDLB_int.c
//
// TITLE:  SPI Digital Loop Back with Interrupts Example.
//
//! \addtogroup cpu01_example_list
//! <h1>SPI Digital Loop Back with Interrupts (spi_loopback_interrupts)</h1>
//!
//!  This program uses the internal loop back test mode of the peripheral.
//!  Other then boot mode pin configuration, no other hardware configuration
//!  is required. Both interrupts and the SPI FIFOs are used.
//!
//!  A stream of data is sent and then compared to the received stream.
//!  The sent data looks like this: \n
//!  0000 0001 \n
//!  0001 0002 \n
//!  0002 0003 \n
//!  .... \n
//!  FFFE FFFF \n
//!  FFFF 0000 \n
//!  etc.. \n
//!  This pattern is repeated forever.
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
// Globals
//
Uint16 sdata[2];     // Send data buffer
Uint16 rdata[2];     // Receive data buffer
Uint16 rdata_point;  // Keep track of where we are
                     // in the data stream to check received data

//
// Function Prototypes
//
interrupt void spiTxFifoIsr(void);
interrupt void spiRxFifoIsr(void);
void delay_loop(void);
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
   InitSpiaGpio();

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
   PieVectTable.SPIA_RX_INT = &spiRxFifoIsr;
   PieVectTable.SPIA_TX_INT = &spiTxFifoIsr;
   EDIS;    // This is needed to disable write to EALLOW protected registers

//
// Step 4. Initialize the Device Peripherals:
//
   spi_fifo_init();   // Initialize the SPI only

//
// Step 5. User specific code, enable interrupts:
//

//
// Initialize the send data buffer
//
   for(i=0; i<2; i++)
   {
      sdata[i] = i;
   }
   rdata_point = 0;

//
// Enable interrupts required for this example
//
   PieCtrlRegs.PIECTRL.bit.ENPIE = 1;     // Enable the PIE block
   PieCtrlRegs.PIEIER6.bit.INTx1 = 1;     // Enable PIE Group 6, INT 1
   PieCtrlRegs.PIEIER6.bit.INTx2 = 1;     // Enable PIE Group 6, INT 2
   IER=0x20;                              // Enable CPU INT6
   EINT;                                  // Enable Global Interrupts

//
// Step 6. IDLE loop. Just sit and loop forever (optional):
//
    for(;;);
}

//
// delay_loop - Function to provide delay
//
void delay_loop()
{
    long i;
    for (i = 0; i < 1000000; i++) {}
}

//
// error - Function to halt debugger on error
//
void error(void)
{
    asm("     ESTOP0");  //Test failed!! Stop!
    for (;;);
}

//
// spi_fifo_init - Initialize SPI FIFO
//
void spi_fifo_init()
{
    //
    // Initialize SPI FIFO registers
    //
    SpiaRegs.SPIFFTX.all = 0xC022;    // Enable FIFOs, set TX FIFO level to 2
    SpiaRegs.SPIFFRX.all = 0x0022;    // Set RX FIFO level to 2
    SpiaRegs.SPIFFCT.all = 0x00;

    SpiaRegs.SPIFFTX.bit.TXFIFO=1;
    SpiaRegs.SPIFFRX.bit.RXFIFORESET=1;

    //
    // Initialize core SPI registers
    //
    InitSpi();
}

//
// spiTxFifoIsr - ISR for SPI transmit FIFO
//
interrupt void spiTxFifoIsr(void)
{
    Uint16 i;
    for(i=0;i<2;i++)
    {
       SpiaRegs.SPITXBUF=sdata[i];      // Send data
    }

    for(i=0;i<2;i++)                    // Increment data for next cycle
    {
       sdata[i] = sdata[i] + 1;
    }

    SpiaRegs.SPIFFTX.bit.TXFFINTCLR=1;  // Clear Interrupt flag
    PieCtrlRegs.PIEACK.all|=0x20;       // Issue PIE ACK
}

//
// spiRxFifoIsr - ISR for SPI receive FIFO
//
interrupt void spiRxFifoIsr(void)
{
    Uint16 i;

    for(i=0; i<2; i++)
    {
        rdata[i]=SpiaRegs.SPIRXBUF;     // Read data
    }

    for(i=0; i<2; i++)                  // Check received data
    {
        if(rdata[i] != rdata_point+i)
        {
            error();
        }
    }

    rdata_point++;
    SpiaRegs.SPIFFRX.bit.RXFFOVFCLR=1;  // Clear Overflow flag
    SpiaRegs.SPIFFRX.bit.RXFFINTCLR=1;  // Clear Interrupt flag
    PieCtrlRegs.PIEACK.all|=0x20;       // Issue PIE ack
}

//
// End of file
//
