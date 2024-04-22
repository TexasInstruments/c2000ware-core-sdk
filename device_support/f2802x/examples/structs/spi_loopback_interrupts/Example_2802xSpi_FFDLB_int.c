//###########################################################################
//
// FILE:   Example_2802xSpi_FFDLB_int.c
//
// TITLE:  f2802x Device Spi Digital Loop Back with Interrupts Example.
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
// DESCRIPTION:
//
//    This program is a SPI-A example that uses the internal loopback of
//    the peripheral.  Both interrupts and the SPI FIFOs are used.
//
//    A stream of data is sent and then compared to the received stream.
//
//    The sent data looks like this:
//    0000 0001
//    0001 0002
//    0002 0003
//    ....
//    FFFE FFFF
//    FFFF 0000
//     etc..
//
//    This pattern is repeated forever.
//
//
// Watch Variables:
//     sdata[2]    - Data to send
//     rdata[2]    - Received data
//     rdata_point - Used to keep track of the last position in
//                   the receive stream for error checking
//###########################################################################
// $TI Release:  $
// $Release Date:  $
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
// Length of the word being sent. Note that InitSpi() actually configures
// SPICCR.SPICHAR and must be updated as well.
//
#define CHAR_LENGTH     16
#define CHAR_MAX        (0xFFFF >> (16 - CHAR_LENGTH))

//
// Function Prototypes
//
__interrupt void spiTxFifoIsr(void);
__interrupt void spiRxFifoIsr(void);
void delay_loop(void);
void spi_fifo_init(void);
void error();

//
// Globals
//
uint16_t sdata[2];     // Send data buffer
uint16_t rdata[2];     // Receive data buffer
uint16_t rdata_point;  // Keep track of where we are
                       // in the data stream to check received data

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
    //InitGpio();  // Skipped for this example

    //
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
    // This function is found in the f2802x_PieCtrl.c file.
    //
    InitPieCtrl();

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
    PieVectTable.SPIRXINTA = &spiRxFifoIsr;
    PieVectTable.SPITXINTA = &spiTxFifoIsr;
    EDIS;      // This is needed to disable write to EALLOW protected registers

    //
    // Step 4. Initialize all the Device Peripherals
    //
    spi_fifo_init();	            // Initialize the SPI only

    //
    // Step 5. User specific code, enable interrupts
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
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;          // Enable the PIE block
    PieCtrlRegs.PIEIER6.bit.INTx1=1;            // Enable PIE Group 6, INT 1
    PieCtrlRegs.PIEIER6.bit.INTx2=1;            // Enable PIE Group 6, INT 2
    IER=0x20;                                   // Enable CPU INT6
    EINT;                                       // Enable Global Interrupts

    //
    // Step 6. IDLE loop. Just sit and loop forever (optional)
    //
    for(;;);
}

//
// Some Useful local functions
//

//
// delay_loop -
//
void
delay_loop()
{
    long      i;
    for (i = 0; i < 1000000; i++)
    {

    }
}

//
// error -
//
void
error(void)
{
    __asm("     ESTOP0");	 //Test failed!! Stop!
    for (;;);
}

//
// spi_fifo_init -
//
void
spi_fifo_init()
{
    //
    // Initialize SPI FIFO registers
    //
    SpiaRegs.SPIFFTX.all=0xC022;      // Enable FIFO's, set TX FIFO level to 2
    SpiaRegs.SPIFFRX.all=0x0022;      // Set RX FIFO level to 2
    SpiaRegs.SPIFFCT.all=0x00;

    SpiaRegs.SPIFFTX.bit.TXFIFO=1;
    SpiaRegs.SPIFFRX.bit.RXFIFORESET=1;

    //
    // Initialize core SPI registers
    //
    InitSpi();
}

//
// spiTxFifoIsr -
//
__interrupt void
spiTxFifoIsr(void)
{
 	uint16_t i;
    for(i=0;i<2;i++)
    {
        //
        // Send data. Note that when character length is less than 16, the
        // data must be left shifted.
        //
        SpiaRegs.SPITXBUF=sdata[i] << (16 - CHAR_LENGTH);
    }

    for(i=0;i<2;i++)                    // Increment data for next cycle
    {
        //
        // Increment data for next cycle and make sure it is never out of range
        // for the given character length.
        //
        if(sdata[i] != CHAR_MAX)
        {
            sdata[i]++;
        }
        else
        {
            sdata[i] = 0;
        }
    }

    SpiaRegs.SPIFFTX.bit.TXFFINTCLR=1;  // Clear Interrupt flag
	PieCtrlRegs.PIEACK.all|=0x20;  		// Issue PIE ACK
}

//
// spiRxFifoIsr -
//
__interrupt void
spiRxFifoIsr(void)
{
    uint16_t i;
    for(i=0;i<2;i++)
    {
	    rdata[i]=SpiaRegs.SPIRXBUF;		// Read data
	}

	for(i=0;i<2;i++)                    // Check received data
	{
	    if(rdata[i] != ((rdata_point + i) & CHAR_MAX))
        {
	        error();
        }
	}

	rdata_point++;

	SpiaRegs.SPIFFRX.bit.RXFFOVFCLR=1;  // Clear Overflow flag
	SpiaRegs.SPIFFRX.bit.RXFFINTCLR=1; 	// Clear Interrupt flag
	PieCtrlRegs.PIEACK.all|=0x20;       // Issue PIE ack
}

//
// End of File
//

