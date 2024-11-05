//#############################################################################
//
// FILE:   spi_ex2_dma_loopback.c
//
// TITLE:  SPI Digital Loop Back with DMA Example.
//
//! \addtogroup bitfield_example_list
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
//!  - \b sData - Data to send
//!  - \b rData - Received data
//!  - \b rData_point - Used to keep track of the last position in
//!    the receive stream for error checking
//!
//
//#############################################################################
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
//#############################################################################

//
// Included Files
//
#include "f28x_project.h"

//
// Defines
//
#define BURST         (FIFO_LVL-1)    // burst size should be less than 8
#define TRANSFER      15              // [(MEM_BUFFER_SIZE/FIFO_LVL)-1]
#define FIFO_LVL      8               // FIFO Interrupt Level

//
// Globals
//
#pragma DATA_SECTION(sData, "ramgs0");    // map the TX data to memory
#pragma DATA_SECTION(rData, "ramgs0");    // map the RX data to memory
uint16_t sData[128];     // Send data buffer
uint16_t rData[128];     // Receive data buffer
uint16_t rData_point;    // Keep track of where we are
                       // in the data stream to check received data
volatile uint16_t *DMADest;
volatile uint16_t *DMASource;
volatile uint16_t done;

//
// Function Prototypes
//
__interrupt void local_D_INTCH5_ISR(void);
__interrupt void local_D_INTCH6_ISR(void);
void dma_init(void);
void spi_fifo_init(void);
void error();
void InitSpi(void);
void InitSpiaGpio(void);

//
// Main
//
void main(void)
{
    uint16_t i;

    //
    // Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    // This example function is found in the <device>_sysctrl.c file.
    //
    InitSysCtrl();

    //
    // Initialize GPIO
    //
    InitGpio();
    InitSpiaGpio();

    //
    // Clear all interrupts:
    //
    DINT;

    //
    // Initialize PIE control registers to their default state.
    // The default state is all PIE __interrupts disabled and flags
    // are cleared.
    // This function is found in the <device>_piectrl.c file.
    //
    InitPieCtrl();

    //
    // Disable CPU __interrupts and clear all CPU __interrupt flags:
    //
    IER = 0x0000;
    IFR = 0x0000;

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    // This will populate the entire table, even if the __interrupt
    // is not used in this example.  This is useful for debug purposes.
    // The shell ISR routines are found in <device>_defaultisr.c.
    // This function is found in <device>_pievect.c.
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
    // Initialize the Device Peripherals:
    //
    dma_init();
    spi_fifo_init();     // Initialize the SPI FIFO


    //
    // Initialize the data buffers
    //
    for(i=0; i<128; i++)
    {
        sData[i] = i;
        rData[i]= 0;
    }
    rData_point = 0;

    //
    // Enable interrupts required for this example
    //
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1; // Enable the PIE block
    PieCtrlRegs.PIEIER7.bit.INTx5 = 1; // Enable PIE Group 7, INT 1 (DMA CH1)
    PieCtrlRegs.PIEIER7.bit.INTx6 = 1; // Enable PIE Group 7, INT 2 (DMA CH2)
    IER= M_INT7;                       // Enable CPU INT6
    EINT;                              // Enable Global Interrupts

    StartDMACH6();                   // Start SPI RX DMA channel
    StartDMACH5();                   // Start SPI TX DMA channel

    done = 0;                        // Test is not done yet

    while(!done);                    // wait until the DMA transfer is complete

    //
    // when the DMA transfer is complete the program will stop here
    //
    ESTOP0;
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

    DMASource = (volatile uint16_t *)sData;
    DMADest = (volatile uint16_t *)rData;

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
    uint16_t i;

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
        if(rData[i] != i)
        {
            error();
        }
    }

    done = 1;  // test done.
    return;
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

    //
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
// End of File
//
