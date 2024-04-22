//###########################################################################
//
// FILE:    Example_2837xDScia_FFDLB.c
//
// TITLE:   SCI FIFO Digital Loop Back Test.
//
//! \addtogroup cpu01_example_list
//! <h1>SCI FIFO Digital Loop Back Test (sci_looback)</h1>
//!
//!  This program uses the internal loop back test mode of the peripheral.
//!  Other then boot mode pin configuration, no other hardware configuration
//!  is required.
//!
//!  This test uses the loopback test mode of the SCI module to send
//!  characters starting with 0x00 through 0xFF.  The test will send
//!  a character and then check the receive buffer for a correct match.
//!
//!  \b Watch \b Variables \n
//!  - \b LoopCount - Number of characters sent
//!  - \b ErrorCount - Number of errors detected
//!  - \b SendChar - Character sent
//!  - \b ReceivedChar - Character received
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
Uint16 LoopCount;
Uint16 ErrorCount;

//
// Function Prototypes
//
void scia_loopback_init(void);
void scia_fifo_init(void);
void scia_xmit(int a);
void error();

//
// Main
//
void main(void)
{
    Uint16 SendChar;
    Uint16 ReceivedChar;

//
// Step 1. Initialize System Control registers, PLL, WatchDog, Clocks to
// default state:
// This function is found in the F2837xD_SysCtrl.c file.
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
// Step 3. Initialize PIE vector table:
// The PIE vector table is initialized with pointers to shell Interrupt
// Service Routines (ISR).  The shell routines are found in F2837xD_DefaultIsr.c.
// Insert user specific ISR code in the appropriate shell ISR routine in
// the F2837xD_DefaultIsr.c file.
//

//
// Disable and clear all CPU __interrupts:
//
    DINT;
    IER = 0x0000;
    IFR = 0x0000;

//
// Initialize Pie Control Registers To Default State:
// This function is found in the F2837xD_PieCtrl.c file.
//
// InitPieCtrl();  //PIE is not used for this example

//
// Initialize the PIE Vector Table To a Known State:
// This function is found in F2837xD_PieVect.c.
// This function populates the PIE vector table with pointers
// to the shell ISR functions found in F2837xD_DefaultIsr.c.
//
    InitPieVectTable();

//
// Enable CPU and PIE __interrupts
// This example function is found in the F2837xD_PieCtrl.c file.
//
    EnableInterrupts();

//
// Step 4. User specific functions, Reassign vectors (optional),
// Enable Interrupts:
//
    LoopCount = 0;
    ErrorCount = 0;

    scia_fifo_init();       // Initialize the SCI FIFO
    scia_loopback_init();  // Initialize SCI for digital loop back

    //
    // Note: Autobaud lock is not required for this example
    //

//
// Send a character starting with 0
//
    SendChar = 0;

//
// Step 5. Send Characters forever starting with 0x00 and going through
// 0xFF.  After sending each, check the receive buffer for the correct value
//
    for(;;)
    {
       scia_xmit(SendChar);

       //
       // wait for RRDY/RXFFST =1 for 1 data available in FIFO
       //
       while(SciaRegs.SCIFFRX.bit.RXFFST == 0) { }

       //
       // Check received character
       //
       ReceivedChar = SciaRegs.SCIRXBUF.all;
       if(ReceivedChar != SendChar)
       {
           error();
       }

       //
       // Move to the next character and repeat the test
       //
       SendChar++;

       //
       // Limit the character to 8-bits
       //
       SendChar &= 0x00FF;
       LoopCount++;
    }
}

//
// error - Function to count errors
//
void error()
{
    ErrorCount++;
//   asm("     ESTOP0");  // Uncomment to stop the test here
//   for (;;);
}

//
// scia_loopback_init - Configure SCIA settings
//
void scia_loopback_init()
{
    //
    // Note: Clocks were turned on to the SCIA peripheral
    // in the InitSysCtrl() function
    //

    SciaRegs.SCICCR.all = 0x0007;  // 1 stop bit,  No loopback
                                   // No parity,8 char bits,
                                   // async mode, idle-line protocol
    SciaRegs.SCICTL1.all = 0x0003; // enable TX, RX, internal SCICLK,
                                   // Disable RX ERR, SLEEP, TXWAKE
    SciaRegs.SCICTL2.all = 0x0003;
    SciaRegs.SCICTL2.bit.TXINTENA = 1;
    SciaRegs.SCICTL2.bit.RXBKINTENA = 1;
    SciaRegs.SCIHBAUD.all = 0x0000;
    SciaRegs.SCILBAUD.all = 0x000F;
    SciaRegs.SCICCR.bit.LOOPBKENA = 1; // Enable loop back
    SciaRegs.SCICTL1.all = 0x0023;     // Relinquish SCI from Reset
}

//
// scia_xmit - Transmit a character from the SCI
//
void scia_xmit(int a)
{
    SciaRegs.SCITXBUF.all=a;
}

//
// scia_fifo_init - Initialize the SCI FIFO
//
void scia_fifo_init()
{
    SciaRegs.SCIFFTX.all = 0xE040;
    SciaRegs.SCIFFRX.all = 0x2044;
    SciaRegs.SCIFFCT.all = 0x0;
}

//
// End of file
//
