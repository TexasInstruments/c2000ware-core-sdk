//###########################################################################
//
// FILE:   Example_2802xSci_FFDLB_int.c
//
// TITLE:  f2802x Device SCI Digital Loop Back program.
//
//
// ASSUMPTIONS:
//
//    This program requires the f2802x header files.
//
//    This program uses the internal loop back test mode of the peripheral.
//    Other then boot mode pin configuration, no other hardware configuration
//    is required.
//
//    As supplied, this project is configured for "boot to SARAM"
//    operation.  The 2802x Boot Mode table is shown below.
//    For information on configuring the boot mode of an eZdsp,
//    please refer to the documentation included with the eZdsp,
//
//    $Boot_Table
//    While an emulator is connected to your device, the TRSTn pin = 1,
//    which sets the device into EMU_BOOT boot mode. In this mode, the
//    peripheral boot modes are as follows:
//
//      Boot Mode:   EMU_KEY        EMU_BMODE
//                   (0xD00)	     (0xD01)
//      ---------------------------------------
//      Wait		 !=0x55AA        X
//      I/O		     0x55AA	         0x0000
//      SCI		     0x55AA	         0x0001
//      Wait 	     0x55AA	         0x0002
//      Get_Mode	 0x55AA	         0x0003
//      SPI		     0x55AA	         0x0004
//      I2C		     0x55AA	         0x0005
//      OTP		     0x55AA	         0x0006
//      Wait		 0x55AA	         0x0007
//      Wait		 0x55AA	         0x0008
//      SARAM		 0x55AA	         0x000A	  <-- "Boot to SARAM"
//      Flash		 0x55AA	         0x000B
//	    Wait		 0x55AA          Other
//
//   Write EMU_KEY to 0xD00 and EMU_BMODE to 0xD01 via the debugger
//   according to the Boot Mode Table above. Build/Load project,
//   Reset the device, and Run example
//
//   $End_Boot_Table
//
//   Assumes the device has both SCI-A and SCI-B peripherals.
//
// DESCRIPTION:
//
//    This program is a SCI example that uses the internal loopback of
//    the peripheral.  Both interrupts and the SCI FIFOs are used.
//
//    A stream of data is sent and then compared to the received stream.
//
//    The SCI-A sent data looks like this:
//    00 01
//    01 02
//    02 03
//    ....
//    FE FF
//    FF 00
//    etc..
//
//    The pattern is repeated forever.
//
//    Watch Variables:
//       sdataA             Data being sent
//       rdataA             Data received
//       rdata_pointA       Keep track of where we are in the datastream
//                          This is used to check the incoming data
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:
// Copyright (C) 2009-2025 Texas Instruments Incorporated - http://www.ti.com/
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
// Default = 40 MHz. Change to 60E6 for 60 MHz devices
//
#define CPU_FREQ 	40E6

#define LSPCLK_FREQ (CPU_FREQ/4)
#define SCI_FREQ 	100E3
#define SCI_PRD 	((LSPCLK_FREQ/(SCI_FREQ*8))-1)

//
// Function Prototypes
//
__interrupt void sciaTxFifoIsr(void);
__interrupt void sciaRxFifoIsr(void);
__interrupt void scibTxFifoIsr(void);
__interrupt void scibRxFifoIsr(void);
void scia_fifo_init(void);
void scib_fifo_init(void);
void error(void);

//
// Globals
//
uint16_t sdataA[2];         // Send data for SCI-A
uint16_t rdataA[2];         // Received data for SCI-A
uint16_t rdata_pointA;      // Used for checking the received data

//
// Main
//
void main(void)
{
    uint16_t i;

    //
    // WARNING: Always ensure you call memcpy before running any functions from
    // RAM InitSysCtrl includes a call to a RAM based function and without a
    // call to memcpy first, the processor will go "into the weeds"
    //
#ifdef _FLASH
    memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (size_t)&RamfuncsLoadSize);
#endif

    //
    // Step 1. Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    // This example function is found in the f2802x_SysCtrl.c file.
    //
    InitSysCtrl();

    //
    // Step 2. Initialize GPIO:
    // This example function is found in the f2802x_Gpio.c file and
    // illustrates how to set the GPIO to it's default state.
    //
    //InitGpio();
    
    //
    // Setup only the GP I/O only for SCI-A and SCI-B functionality
    // This function is found in f2802x_Sci.c
    //
    InitSciGpio();

    //
    // Step 3. Clear all interrupts and initialize PIE vector table:
    // Disable CPU interrupts
    //
    DINT;

    //
    // Initialize PIE control registers to their default state.
    // The default state is all PIE interrupts disabled and flags
    // are cleared.
    // This function is found in the f2802x_PieCtrl.c file.
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
    // The shell ISR routines are found in f2802x_DefaultIsr.c.
    // This function is found in f2802x_PieVect.c.
    //
    InitPieVectTable();

    //
    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    //
    EALLOW;	           // This is needed to write to EALLOW protected registers
    PieVectTable.SCIRXINTA = &sciaRxFifoIsr;
    PieVectTable.SCITXINTA = &sciaTxFifoIsr;
    EDIS;      // This is needed to disable write to EALLOW protected registers

    //
    // Step 4. Initialize all the Device Peripherals
    //
    scia_fifo_init();               // Init SCI-A FIFO

    //
    // Step 5. User specific code, enable interrupts
    //

    //
    // Init send data.  After each transmission this data will be updated for 
    // the next transmission
    //
    for(i = 0; i<2; i++)
    {
        sdataA[i] = i;
    }

    rdata_pointA = sdataA[0];

    //
    // Enable interrupts required for this example
    //
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;          // Enable the PIE block
    PieCtrlRegs.PIEIER9.bit.INTx1=1;            // PIE Group 9, INT1
    PieCtrlRegs.PIEIER9.bit.INTx2=1;            // PIE Group 9, INT2
    IER = 0x100;	                            // Enable CPU INT
    EINT;

    //
    // Step 6. IDLE loop. Just sit and loop forever (optional)
    //
    for(;;);
}

//
// error -
//
void
error(void)
{
    __asm("     ESTOP0");           // Test failed!! Stop!
    for (;;);
}

//
// sciaTxFifoIsr -
//
__interrupt void
sciaTxFifoIsr(void)
{
    uint16_t i;
    for(i=0; i< 2; i++)
    {
        SciaRegs.SCITXBUF=sdataA[i];     // Send data
    }

    for(i=0; i< 2; i++)                 //Increment send data for next cycle
    {
        sdataA[i] = (sdataA[i]+1) & 0x00FF;
    }

    SciaRegs.SCIFFTX.bit.TXFFINTCLR=1;	// Clear SCI Interrupt flag
    PieCtrlRegs.PIEACK.all|=0x100;      // Issue PIE ACK
}

//
// sciaRxFifoIsr -
//
__interrupt void
sciaRxFifoIsr(void)
{
    uint16_t i;
    for(i=0;i<2;i++)
    {
        rdataA[i]=SciaRegs.SCIRXBUF.all;	   // Read data
    }
    
    for(i=0;i<2;i++)                           // Check received data
    {
        if(rdataA[i] != ( (rdata_pointA+i) & 0x00FF) )
        {
            error();
        }
    }
    rdata_pointA = (rdata_pointA+1) & 0x00FF;

    SciaRegs.SCIFFRX.bit.RXFFOVRCLR=1;          // Clear Overflow flag
    SciaRegs.SCIFFRX.bit.RXFFINTCLR=1;          // Clear Interrupt flag

    PieCtrlRegs.PIEACK.all|=0x100;              // Issue PIE ack
}

//
// scia_fifo_init - 
//
void
scia_fifo_init()
{
    //
    // 1 stop bit,  No loopback, No parity, 8 char bits, async mode, idle-line 
    // protocol
    //
    SciaRegs.SCICCR.all =0x0007;   
    
    //
    // enable TX, RX, internal SCICLK, Disable RX ERR, SLEEP, TXWAKE
    //
    SciaRegs.SCICTL1.all =0x0003;
    SciaRegs.SCICTL2.bit.TXINTENA =1;
    SciaRegs.SCICTL2.bit.RXBKINTENA =1;
    SciaRegs.SCIHBAUD = SCI_PRD >> 8;
    SciaRegs.SCILBAUD = SCI_PRD;
    SciaRegs.SCICCR.bit.LOOPBKENA =1;       // Enable loop back
    SciaRegs.SCIFFTX.all=0xC022;
    SciaRegs.SCIFFRX.all=0x0022;
    SciaRegs.SCIFFCT.all=0x00;

    SciaRegs.SCICTL1.all =0x0023;           // Relinquish SCI from Reset
    SciaRegs.SCIFFTX.bit.TXFIFOXRESET=1;
    SciaRegs.SCIFFRX.bit.RXFIFORESET=1;
}

//
// End of File
//

