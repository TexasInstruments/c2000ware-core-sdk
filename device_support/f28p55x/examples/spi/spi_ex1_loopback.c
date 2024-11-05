//###########################################################################
//
// FILE:   spi_ex1_loopback.c
//
// TITLE:  SPI Digital Loop Back Example.
//
//! \addtogroup bitfield_example_list
//! <h1>SPI Digital Loop Back </h1>
//!
//!  This program uses the internal loop back test mode of the peripheral.
//!  Other than boot mode pin configuration, no other hardware configuration
//!  is required. Interrupts are not used.
//!
//!  A stream of data is sent and then compared to the received stream.
//!  The sent data looks like this: \n
//!  0000 0001 0002 0003 0004 0005 0006 0007 .... FFFE FFFF \n
//!  This pattern is repeated forever.
//!
//!  \b Watch \b Variables \n
//!  - \b sdata - sent data
//!  - \b rdata - received data
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
// Function Prototypes
//
void transmitData(uint16_t a);
void initSPIFIFO(void);
void error(void);
void InitSpi(void);
void InitSpiaGpio(void);

void main(void)
{
    uint16_t sdata;  // sent data
    uint16_t rdata;  // received data

    //
    // Initialize device clock and peripherals
    //
    InitSysCtrl();

    //
    // Initialize GPIO
    //
    InitGpio();
    InitSpiaGpio();

    //
    // Disable CPU interrupts
    //
    DINT;

    //
    // Initialize the PIE control registers to their default state.
    // The default state is all PIE interrupts disabled and flags
    // are cleared.
    //
    InitPieCtrl();

    //
    // Disable CPU interrupts and clear all CPU interrupt flags
    //
    IER = 0x0000;
    IFR = 0x0000;

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR)
    //
    InitPieVectTable();

    //
    // Set up SPI, initializing it for FIFO mode
    //
    initSPIFIFO();

    //
    // Loop forever. Suspend or place breakpoints to observe the buffers.
    //
    sdata = 0x0000;
    for(;;)
    {
        //
        // Transmit data
        //
        transmitData(sdata);

        //
        // Wait until data is received
        //
        while(SpiaRegs.SPIFFRX.bit.RXFFST != 1)
        {

        }

        //
        // Check against sent data
        //
        rdata = SpiaRegs.SPIRXBUF;
        if(rdata != sdata)
        {
            error();
        }
        sdata++;
    }
}

//
// error - Error function that halts the debugger
//
void error(void)
{
    asm("     ESTOP0");     // Test failed!! Stop!
    for(;;);
}

//
// transmitData - Transmit value via SPI
//
void transmitData(uint16_t a)
{
    SpiaRegs.SPITXBUF = a;
}

//
// initSPIFIFO - Initialize SPIA FIFO
//
void initSPIFIFO(void)
{
    //
    // Initialize SPI FIFO registers
    //
    SpiaRegs.SPIFFTX.all = 0xE040;
    SpiaRegs.SPIFFRX.all = 0x2044;
    SpiaRegs.SPIFFCT.all = 0x0;

    //
    // Initialize core SPI registers
    //
    InitSpi();
}

//
// InitSPI - This function initializes the SPI to a known state
//
void InitSpi(void)
{
    //
    // Initialize SPI-A
    //

    //
    // Set reset low before configuration changes
    // Clock polarity (0 == rising, 1 == falling)
    // 16-bit character
    // Enable loop-back
    //
    SpiaRegs.SPICCR.bit.SPISWRESET = 0;
    SpiaRegs.SPICCR.bit.CLKPOLARITY = 0;
    SpiaRegs.SPICCR.bit.SPICHAR = (16 - 1);
    SpiaRegs.SPICCR.bit.SPILBK = 1;

    //
    // Enable controller (0 == peripheral, 1 == controller)
    // Enable transmission (Talk)
    // Clock phase (0 == normal, 1 == delayed)
    // SPI interrupts are disabled
    //
    SpiaRegs.SPICTL.bit.CONTROLLER_PERIPHERAL = 1;
    SpiaRegs.SPICTL.bit.TALK = 1;
    SpiaRegs.SPICTL.bit.CLK_PHASE = 0;
    SpiaRegs.SPICTL.bit.SPIINTENA = 0;

    //
    // Set the baud rate using a 1 MHz SPICLK
    // BRR = (LSPCLK / SPICLK) - 1
    //
    SpiaRegs.SPIBRR.bit.SPI_BIT_RATE = ((37500000 / 1000000) - 1);

    // Set FREE bit
    // Halting on a breakpoint will not halt the SPI
    //
    SpiaRegs.SPIPRI.bit.FREE = 1;

    //
    // Release the SPI from reset
    //
    SpiaRegs.SPICCR.bit.SPISWRESET = 1;
}

void InitSpiaGpio(void)
{
       EALLOW;

    //
    // Enable internal pull-up for the selected pins
    //
    // Pull-ups can be enabled or disabled by the user.
    // This will enable the pullups for the specified pins.
    //
    GpioCtrlRegs.GPAPUD.bit.GPIO16 = 0;  // Enable pull-up on GPIO16 (SPIPICOA)
    GpioCtrlRegs.GPAPUD.bit.GPIO17 = 0;  // Enable pull-up on GPIO17 (SPIPOCIA)
    GpioCtrlRegs.GPAPUD.bit.GPIO18 = 0;  // Enable pull-up on GPIO18 (SPICLKA)
    GpioCtrlRegs.GPAPUD.bit.GPIO19 = 0;  // Enable pull-up on GPIO19 (SPIPTEA)

    //
    // Set qualification for selected pins to asynch only
    //
    // This will select asynch (no qualification) for the selected pins.
    //
    GpioCtrlRegs.GPAQSEL2.bit.GPIO16 = 3; // Asynch input GPIO16 (SPIPICOA)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO17 = 3; // Asynch input GPIO17 (SPIPOCIA)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO18 = 3; // Asynch input GPIO18 (SPICLKA)
    GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = 3; // Asynch input GPIO19 (SPIPTEA)

    //
    // Configure SPI-A pins
    //
    // This specifies which of the possible GPIO pins will be SPI functional
    // pins.
    //
    GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 1; // Configure GPIO16 as SPIPICOA
    GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 1; // Configure GPIO17 as SPIPOCIA
    GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 1; // Configure GPIO18 as SPICLKA
    GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 1; // Configure GPIO19 as SPIPTEA

    EDIS;
}


//
// End of file
//
