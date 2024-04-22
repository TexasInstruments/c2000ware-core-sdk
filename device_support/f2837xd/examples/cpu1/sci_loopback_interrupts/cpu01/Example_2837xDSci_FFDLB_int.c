//###########################################################################
//
// FILE:   Example_2837xDSci_FFDLB_int.c
//
// TITLE:  SCI Digital Loop Back with Interrupts.
//
//! \addtogroup cpu01_example_list
//! <h1>SCI Digital Loop Back with Interrupts (sci_loopback_interrupts)</h1>
//!
//!  This program uses the internal loop back test mode of the peripheral.
//!  Other then boot mode pin configuration, no other hardware configuration
//!  is required. Both interrupts and the SCI FIFOs are used.
//!
//!  A stream of data is sent and then compared to the received stream.
//!  The SCI-A sent data looks like this: \n
//!  00 01 \n
//!  01 02 \n
//!  02 03 \n
//!  .... \n
//!  FE FF \n
//!  FF 00 \n
//!  etc.. \n
//!  The pattern is repeated forever.
//!
//!  \b Watch \b Variables \n
//!  - \b sdataA - Data being sent
//!  - \b rdataA - Data received
//!  - \b rdata_pointA - Keep track of where we are in the data stream.
//!    This is used to check the incoming data
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
#define CPU_FREQ        60E6
#define LSPCLK_FREQ     CPU_FREQ/4
#define SCI_FREQ        100E3
#define SCI_PRD         ((LSPCLK_FREQ/(SCI_FREQ*8))-1)

//
// Globals
//
Uint16 sdataA[2];    // Send data for SCI-A
Uint16 rdataA[2];    // Received data for SCI-A
Uint16 rdata_pointA; // Used for checking the received data

//
// Function Prototypes
//
interrupt void sciaTxFifoIsr(void);
interrupt void sciaRxFifoIsr(void);
void scia_fifo_init(void);
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
//
   InitGpio();

//
// For this example, only init the pins for the SCI-A port.
//  GPIO_SetupPinMux() - Sets the GPxMUX1/2 and GPyMUX1/2 register bits
//  GPIO_SetupPinOptions() - Sets the direction and configuration of the GPIOS
// These functions are found in the F2837xD_Gpio.c file.
//
#ifdef _LAUNCHXL_F2837xD
   GPIO_SetupPinMux(85, GPIO_MUX_CPU1, 5);
   GPIO_SetupPinOptions(85, GPIO_INPUT, GPIO_PUSHPULL);
   GPIO_SetupPinMux(84, GPIO_MUX_CPU1, 5);
   GPIO_SetupPinOptions(84, GPIO_OUTPUT, GPIO_ASYNC);
#else
   GPIO_SetupPinMux(28, GPIO_MUX_CPU1, 1);
   GPIO_SetupPinOptions(28, GPIO_INPUT, GPIO_PUSHPULL);
   GPIO_SetupPinMux(29, GPIO_MUX_CPU1, 1);
   GPIO_SetupPinOptions(29, GPIO_OUTPUT, GPIO_ASYNC);
#endif

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
   EALLOW;  // This is needed to write to EALLOW protected registers
   PieVectTable.SCIA_RX_INT = &sciaRxFifoIsr;
   PieVectTable.SCIA_TX_INT = &sciaTxFifoIsr;
   EDIS;    // This is needed to disable write to EALLOW protected registers

//
// Step 4. Initialize the Device Peripherals:
//
   scia_fifo_init();  // Init SCI-A

//
// Step 5. User specific code, enable interrupts:
//
// Init send data.  After each transmission this data
// will be updated for the next transmission
//
   for(i = 0; i<2; i++)
   {
      sdataA[i] = i;
   }

   rdata_pointA = sdataA[0];

//
// Enable interrupts required for this example
//
   PieCtrlRegs.PIECTRL.bit.ENPIE = 1;   // Enable the PIE block
   PieCtrlRegs.PIEIER9.bit.INTx1 = 1;   // PIE Group 9, INT1
   PieCtrlRegs.PIEIER9.bit.INTx2 = 1;   // PIE Group 9, INT2
   IER = 0x100;                         // Enable CPU INT
   EINT;

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
    asm("     ESTOP0"); // Test failed!! Stop!
    for (;;);
}

//
// sciaTxFifoIsr - SCIA Transmit FIFO ISR
//
interrupt void sciaTxFifoIsr(void)
{
    Uint16 i;

    for(i=0; i< 2; i++)
    {
       SciaRegs.SCITXBUF.all=sdataA[i];  // Send data
    }

    for(i=0; i< 2; i++)                  // Increment send data for next cycle
    {
       sdataA[i] = (sdataA[i]+1) & 0x00FF;
    }

    SciaRegs.SCIFFTX.bit.TXFFINTCLR=1;   // Clear SCI Interrupt flag
    PieCtrlRegs.PIEACK.all|=0x100;       // Issue PIE ACK
}

//
// sciaRxFifoIsr - SCIA Receive FIFO ISR
//
interrupt void sciaRxFifoIsr(void)
{
    Uint16 i;

    for(i=0;i<2;i++)
    {
       rdataA[i]=SciaRegs.SCIRXBUF.all;  // Read data
    }

    for(i=0;i<2;i++)                     // Check received data
    {
       if(rdataA[i] != ( (rdata_pointA+i) & 0x00FF) )
       {
           error();
       }
    }

    rdata_pointA = (rdata_pointA+1) & 0x00FF;

    SciaRegs.SCIFFRX.bit.RXFFOVRCLR=1;   // Clear Overflow flag
    SciaRegs.SCIFFRX.bit.RXFFINTCLR=1;   // Clear Interrupt flag

    PieCtrlRegs.PIEACK.all|=0x100;       // Issue PIE ack
}

//
// scia_fifo_init - Configure SCIA FIFO
//
void scia_fifo_init()
{
   SciaRegs.SCICCR.all = 0x0007;      // 1 stop bit,  No loopback
                                      // No parity,8 char bits,
                                      // async mode, idle-line protocol
   SciaRegs.SCICTL1.all = 0x0003;     // enable TX, RX, internal SCICLK,
                                      // Disable RX ERR, SLEEP, TXWAKE
   SciaRegs.SCICTL2.bit.TXINTENA = 1;
   SciaRegs.SCICTL2.bit.RXBKINTENA = 1;
   SciaRegs.SCIHBAUD.all = ((uint16_t)SCI_PRD  & 0xFF00U) >> 8U;
   SciaRegs.SCILBAUD.all = (uint16_t)SCI_PRD  & 0x00FFU;
   SciaRegs.SCICCR.bit.LOOPBKENA = 1; // Enable loop back
   SciaRegs.SCIFFTX.all = 0xC022;
   SciaRegs.SCIFFRX.all = 0x0022;
   SciaRegs.SCIFFCT.all = 0x00;

   SciaRegs.SCICTL1.all = 0x0023;     // Relinquish SCI from Reset
   SciaRegs.SCIFFTX.bit.TXFIFORESET = 1;
   SciaRegs.SCIFFRX.bit.RXFIFORESET = 1;
}

//
// End of file
//
