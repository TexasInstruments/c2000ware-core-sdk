//###########################################################################
//
// FILE:	Example_2823xSci_Autobaud.c
//
// TITLE:	SCI Autobaud Example
//
//! \addtogroup f2823x_example_list
//! <h1>SCI Autobaud (sci_autobaud)</h1>
//!
//! This test will perform autobaud lock at a variety of baud rates, including
//! very high baud rates.
//!
//! For this test to properly run, connect the SCI-A pins to the
//! SCI-B pins without going through a transceiver.
//! At higher baud rates, the slew rate of the incoming data bits can be
//! affected by transceiver and connector performance. This slew rate may
//! limit reliable autobaud detection at higher baud rates.
//!
//! SCIA: Slave, autobaud locks, receives characters and
//! echos them back to the host.  Uses the RX interrupt
//! to receive characters.
//!
//! SCIB: Host, known baud rate, sends characters to the slave
//! and checks that they are echoed back.
//!
//! \b External \b Connections \n
//! - SCITXDA is on GPIO29
//! - SCIRXDB is on GPIO19
//! - SCIRXDA is on GPIO28
//! - SCITXDB is on GPIO18
//! - Connect GPIO29 to GPIO19
//! - Connect GPIO28 to GPIO18
//!
//! \b Watch \b Variables \n
//! - BRRVal            - current BRR value used for SCIB
//! - ReceivedAChar     - character received by SCIA
//! - ReceivedBChar     - character received by SCIB
//! - SendChar          - character being sent by SCIB
//! - SciaRegs.SCILBAUD - SCIA baud register set by autobaud lock
//! - SciaRegs.SCIHBAUD - SCIA baud register set by autobaud lock
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
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File

//
// Defines
//

//
// Amount BRR will be incremented between each autobaud lock
//
#define BAUDSTEP 100

//
// Function Prototypes
//
void scia_init(void);
void scib_init(void);
void scia_xmit(int a);
void scib_xmit(int a);
void scia_AutobaudLock(void);
void error();
__interrupt void rxaint_isr(void);

//
// Globals
//
Uint16 LoopCount;
//Uint16 xmitCount;
Uint16 ReceivedCount;
Uint16 ErrorCount;
Uint16 SendChar;
Uint16 ReceivedAChar;   // scia received character
Uint16 ReceivedBChar;   // scib received character
Uint16 BRRVal;
Uint16 Buff[10] = {0x55, 0xAA, 0xF0, 0x0F, 0x00, 0xFF, 0xF5, 0x5F, 0xA5, 0x5A};

//
// Main
//
void main(void)
{
    Uint16 i;

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

    InitSciGpio();

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
    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    //
    EALLOW;	          // This is needed to write to EALLOW protected registers
    PieVectTable.SCIRXINTA = &rxaint_isr;
    EDIS;       // This is needed to disable write to EALLOW protected register

    //
    // Step 4. Initialize all the Device Peripherals:
    // This function is found in DSP2823x_InitPeripherals.c
    //
    // InitPeripherals(); // Not required for this example
    
    scia_init();       // Initialize SCIA
    scib_init();       // Initialize SCIB

    //
    // Step 5. User specific code, enable interrupts
    //
    LoopCount = 0;
    ErrorCount = 0;

    //
    // Enable interrupts
    //
    PieCtrlRegs.PIEIER9.all = 0x0001;   // Enable all SCIA RXINT interrupt
    IER |= 0x0100;			            // enable PIEIER9, and INT9
    EINT;

    //
    // Start with BRR = 1, work through each baud rate setting
    // incrementing BRR by BAUDSTEP
    //
    for (BRRVal = 0x0000; BRRVal < (Uint32)0xFFFF; BRRVal+=BAUDSTEP)
    {
        //
        // SCIB has a known baud rate.  SCIA will autobaud to match
        //
        ScibRegs.SCIHBAUD = (BRRVal >> 8);
        ScibRegs.SCILBAUD = (BRRVal);

        //
        // Initiate an autobaud lock with scia.  Check
        // returned character against baud lock character 'A'
        //
        scia_AutobaudLock();
        while(ScibRegs.SCIRXST.bit.RXRDY != 1)
        {

        }
        ReceivedBChar = 0;
        ReceivedBChar =  ScibRegs.SCIRXBUF.bit.RXDT;
        if(ReceivedBChar != 'A')
        {
            error(0);
        }

        //
        // Send/echoback characters
        // 55 AA F0 0F 00 FF F5 5F A5 5A
        //
        for(i= 0; i<=9; i++)
        {
            SendChar = Buff[i];
            scib_xmit(SendChar);	// Initiate interrupts and xmit data in isr
            
            //
            // Wait to get the character back and check against the 
            // sent character.
            //
            while(ScibRegs.SCIRXST.bit.RXRDY != 1)
            {
                __asm("   NOP");
            }
            ReceivedBChar = 0;
            ReceivedBChar =  ScibRegs.SCIRXBUF.bit.RXDT;
            
            if(ReceivedBChar != SendChar)
            {
                error(1);
            }
        }
    }

    //
    // Stop here, no more
    //
    for(;;)
    {
        __asm("    NOP");
    }
}

//
// rxaint_isr - ISR for PIE INT9.1 Connected to RXAINT  SCI-A
//
__interrupt void
rxaint_isr(void)
{
    //
    // Insert ISR Code here
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

    //
    // If autobaud detected, we must clear CDC
    //
    if(SciaRegs.SCIFFCT.bit.ABD == 1)
    {
        SciaRegs.SCIFFCT.bit.ABDCLR = 1;
        SciaRegs.SCIFFCT.bit.CDC = 0;
        
        //
        // Check received character - should be 'A'
        //
        ReceivedAChar = 0;
        ReceivedAChar = SciaRegs.SCIRXBUF.all;
        
        if(ReceivedAChar != 'A')
        {
            error(2);
        }
        else
        {
            scia_xmit(ReceivedAChar);
        }
    }

    //
    // This was not autobaud detect
    //
    else
    {
        //
        // Check received character against sendchar
        //
        ReceivedAChar = 0;
        ReceivedAChar = SciaRegs.SCIRXBUF.all;
        
        if(ReceivedAChar != SendChar)
        {
            error(3);
        }
        else
        {
            scia_xmit(ReceivedAChar);
        }
    }

    SciaRegs.SCIFFRX.bit.RXFFINTCLR = 1;	// clear Receive interrupt flag
    ReceivedCount++;
}

//
// error -
//
void 
error()
{
    ErrorCount++;
    __asm("     ESTOP0");  	       // Uncomment to stop the test here
    for (;;);
}

//
// scia_init - SCIA  8-bit word, baud rate 0x000F, default, 1 STOP bit,
// no parity
//
void 
scia_init()
{
    //
    // Note: Clocks were turned on to the SCIA peripheral
    // in the InitSysCtrl() function
    //
    
    //
    // Reset FIFO's
    //
    SciaRegs.SCIFFTX.all=0x8000;

    //
    // 1 stop bit,  No loopback, No parity,8 char bits, async mode,
    // idle-line protocol
    //
    SciaRegs.SCICCR.all =0x0007;
    
    //
    // enable TX, RX, internal SCICLK, Disable RX ERR, SLEEP, TXWAKE
    //
    SciaRegs.SCICTL1.all =0x0003;
    SciaRegs.SCICTL2.all =0x0003;
    SciaRegs.SCICTL2.bit.RXBKINTENA =1;
    SciaRegs.SCICTL1.all =0x0023;     // Relinquish SCI from Reset
}

//
// scib_init - SCIB  8-bit word, baud rate 0x000F, default, 
// 1 STOP bit, no parity
//
void 
scib_init()
{
    //
    // Reset FIFO's
    //
    ScibRegs.SCIFFTX.all=0x8000;

    //
    // 1 stop bit, No parity, 8-bit character, No loopback
    //
    ScibRegs.SCICCR.all = 0x0007;

    //
    // Enable TX, RX, Use internal SCICLK
    //
    ScibRegs.SCICTL1.all = 0x0003;

    //
    // Disable RxErr, Sleep, TX Wake, Disable Rx Interrupt, Tx Interrupt
    //
    ScibRegs.SCICTL2.all = 0x0000;

    //
    // Relinquish SCI-A from reset
    //
    ScibRegs.SCICTL1.all = 0x0023;

    return;
}

//
// scia_xmit - Transmit a character from the SCI-A'
//
void 
scia_xmit(int a)
{
    SciaRegs.SCITXBUF=a;
}

//
// scib_xmit - Transmit a character from the SCI-B'
//
void 
scib_xmit(int a)
{
    ScibRegs.SCITXBUF=a;
}

//
// scia_AutobaudLock - Perform autobaud lock with the host. Note that if 
// autobaud never occurs the program will hang in this routine as there is 
// no timeout mechanism included.
//
void 
scia_AutobaudLock()
{
    SciaRegs.SCICTL1.bit.SWRESET = 0;
    SciaRegs.SCICTL1.bit.SWRESET = 1;

    //
    // Must prime baud register with >= 1
    //
    SciaRegs.SCIHBAUD = 0;
    SciaRegs.SCILBAUD = 1;

    //
    // Prepare for autobaud detection
    // Make sure the ABD bit is clear by writing a 1 to ABDCLR
    // Set the CDC bit to enable autobaud detection
    //
    SciaRegs.SCIFFCT.bit.ABDCLR = 1;
    SciaRegs.SCIFFCT.bit.CDC = 1;

    //
    // Wait until we correctly read an
    // 'A' or 'a' and lock
    //
    // As long as Autobaud calibration is enabled (CDC = 1),
    // SCI-B (host) will continue transmitting 'A'. This will
    // continue until interrupted by the SCI-A RX ISR, where
    // SCI-A RXBUF receives 'A', autobaud-locks (ABDCLR=1
    // CDC=0),and returns an 'A' back to the host. Then control
    // is returned to this loop and the loop is exited.
    //
    // NOTE: ABD will become set sometime between
    //       scib_xmit and the DELAY_US loop, and
    //       the SCI-A RX ISR will be triggered.
    //       Upon returning and reaching the if-statement,
    //       ABD will have been cleared again by the ISR.
    //

    while(SciaRegs.SCIFFCT.bit.CDC== 1)
    {
        //
        // Note the lower the baud rate the longer
        // this delay has to be to allow the other end
        // to echo back a character (about 4 characters long)
        // Make this really long since we are going through all
        // the baud rates.
        //
        DELAY_US(280000L);

        if(SciaRegs.SCIFFCT.bit.CDC == 1)
        {
            
        }
        scib_xmit('A');  // host transmits 'A'
    }
    return;
}

//
// End of File
//

