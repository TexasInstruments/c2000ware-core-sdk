//###########################################################################
//
// FILE:   dma_ex1_shared_peripheral_cpu2.c
//
// TITLE:  DMA Transfer for Shared Peripheral Example for F2838x.
//
// This example shows how to initiate a DMA transfer on CPU1 from a shared
// peripheral which is owned by CPU2.  In this specific example, a timer ISR
// is used on CPU2 to initiate a SPI transfer which will trigger the CPU1 DMA.
// CPU1's DMA will then in turn update the EPWM1 CMPA value for the PWM which
// it owns.  The PWM output can be observed on the GPIO pins configured in
// the InitEPwm1Gpio() function.
//
//###########################################################################
// $Copyright:
// Copyright (C) 2022 Texas Instruments Incorporated - http://www.ti.com
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
// Pragma - Put the ePWM CMP value into shared RAM
//
#pragma DATA_SECTION(new_cmp_value, "ramgs1");

//
// Function Prototypes
//
void ExampleInitSysCtrl(void);
void InitSpi(void);
void InitCpuTimer(void);
__interrupt void cpu_timer1_isr(void);
void load_buffer(void);

//
// Global variable used in this example
//
Uint16 new_cmp_value;
Uint16 direction = 1;

//
// Main
//
void main(void)
{
//
// Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the f2838x_sysctrl.c file.
//
    ExampleInitSysCtrl();

    new_cmp_value = 3000;  // Set CMP value

//
// Clear all interrupts and initialize PIE vector table:
// Disable CPU interrupts
//
    DINT;

//
// Initialize the PIE control registers to their default state.
// The default state is all PIE interrupts disabled and flags
// are cleared.
// This function is found in the f2838x_piectrl.c file.
//
    InitPieCtrl();

//
// Disable CPU interrupts and clear all CPU interrupt flags.
//
    IER = 0x0000;
    IFR = 0x0000;

//
// Initialize the PIE vector table with pointers to the default
// Interrupt Service Routines (ISR).
// The default ISR routines are found in f2838x_defaultisr.c.
// This function is found in f2838x_pievect.c.
//
    InitPieVectTable();

//
// Wait for IPC from CPU1 confirming DMA is configured before
// initializing SPI. Note that because of the way the TXFIFO interrupt
// is configured a DMA transfer will be triggered immediately after the
// SPI is released from reset
//
    while(IPCRtoLFlagBusy(IPC_FLAG0) == 0);

//
// Setup SPI for FIFO mode
//
    InitSpi();

//
// Setup CPU Timer 1 to interrupt every 10 ms
//
    InitCpuTimers();
    ConfigCpuTimer(&CpuTimer1, 200, 10000);
    CpuTimer1Regs.TCR.all = 0x4000;

//
// Configure CPU Timer 1 ISR
//
    EALLOW;
    PieVectTable.TIMER1_INT = &cpu_timer1_isr;
    IER |= M_INT13;
    EDIS;

//
// Enable global Interrupts and higher priority real-time debug
// events:
//
    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global realtime interrupt DBGM

//
// IDLE loop. Just sit and loop forever (optional):
//
    for(;;)
    {
        asm ("  NOP");
    }
}

//
// ExampleInitSysCtrl function
// This example uses custom InitSysCtrl function since CPU2 owns some of the
// peripherals
//
void ExampleInitSysCtrl(void)
{
    //
    // Disable the watchdog
    //
    DisableDog();

#ifdef _FLASH
    //
    // Copy time critical code and Flash setup code to RAM. This includes the
    // following functions: InitFlash()
    //
    // The  RamfuncsLoadStart, RamfuncsLoadSize, and RamfuncsRunStart
    // symbols are created by the linker. Refer to the device .cmd file.
    //
    memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (size_t)&RamfuncsLoadSize);

    //
    // Call Flash Initialization to setup flash waitstates. This function must
    // reside in RAM.
    //
    InitFlash();
#endif

    //
    // Wait for IPC flag from CPU1
    //
    while(IPCRtoLFlagBusy(IPC_FLAG31) == 0);
    IPCRtoLFlagAcknowledge(IPC_FLAG31);


    //
    // Turn on required peripherals
    //
    EALLOW;
    CpuSysRegs.PCLKCR8.bit.SPI_A = 1;
    EDIS;
}


//
// InitSpi - Function to Setup SPI for FIFO mode
//
void InitSpi(void)
{
   //
   // Initialize SPI FIFO registers
   //
   SpiaRegs.SPICCR.bit.SPISWRESET = 0; // Reset SPI
   SpiaRegs.SPICCR.all = 0x001F;       //16-bit character, Loopback mode
   SpiaRegs.SPICTL.all = 0x0017;       //Interrupt enabled, Master/Slave XMIT
                                       //enabled
   SpiaRegs.SPISTS.all = 0x0000;
   SpiaRegs.SPIBRR.bit.SPI_BIT_RATE = 0x0063;   // Baud rate
   SpiaRegs.SPIFFTX.all = 0xC022;               // Enable FIFO's, set TX FIFO
                                                // level to 4
   SpiaRegs.SPIFFRX.all = 0x0022;               // Set RX FIFO level to 4
   SpiaRegs.SPIFFCT.all = 0x00;
   SpiaRegs.SPIPRI.all = 0x0000;
   SpiaRegs.SPICCR.bit.SPISWRESET = 1;          // Enable SPI
   SpiaRegs.SPIFFTX.bit.TXFIFO = 1;
   SpiaRegs.SPIFFRX.bit.RXFIFORESET = 1;

   //
   // A DMA transfer will be triggered here!
   //

   //
   // Load the SPI FIFO Tx Buffer
   //
   load_buffer();

   //
   // Disable the clock to prevent continuous transfer / DMA triggers
   // Note this method of disabling the clock should not be used if
   // actual data is being transmitted
   //
   EALLOW;
   CpuSysRegs.PCLKCR8.bit.SPI_A = 0;
   EDIS;
}

//
// cpu_timer1_isr - Function for CPU Timer1 Interrupt Service Routine
//
__interrupt void cpu_timer1_isr(void)
{
    //
    // Re-enable SPI clock to allow DMA trigger
    //
    EALLOW;
    CpuSysRegs.PCLKCR8.bit.SPI_A = 1;
    EDIS;

    //
    // Wait for interrupt flag
    // This is when the DMA trigger will occur
    //
    while(!SpiaRegs.SPIFFTX.bit.TXFFINT);

    //
    // Reload the SPI TX buffer and clear interrupt flag
    //
    load_buffer();

    SpiaRegs.SPIFFTX.bit.TXFFINTCLR = 1;

    //
    // Disable the clock to prevent continuous transfer / DMA triggers
    // Note this method of disabling the clock should not be used if
    // actual data is being transmitted
    //
    EALLOW;
    CpuSysRegs.PCLKCR8.bit.SPI_A = 0;
    EDIS;

    //
    // Update next value to be transferred to the EPWM
    //
    if(new_cmp_value >= 4500)
    {
        direction = 0;
    }
    else if(new_cmp_value <= 1500)
    {
        direction = 1;
    }

    if(!direction)
    {
        new_cmp_value -= 50;
    }
    else
    {
        new_cmp_value += 50;
    }
}

//
// load_buffer - Function to load SPI Tx FIFO Buffer
//
void load_buffer(void)
{
    //
    // Fill up the FIFO buffer
    //
    SpiaRegs.SPITXBUF = 0xAAAA;
    SpiaRegs.SPITXBUF = 0xAAAA;
    SpiaRegs.SPITXBUF = 0xAAAA;
    SpiaRegs.SPITXBUF = 0xAAAA;
    SpiaRegs.SPITXBUF = 0xAAAA;
    SpiaRegs.SPITXBUF = 0xAAAA;
    SpiaRegs.SPITXBUF = 0xAAAA;
    SpiaRegs.SPITXBUF = 0xAAAA;
    SpiaRegs.SPITXBUF = 0xAAAA;
    SpiaRegs.SPITXBUF = 0xAAAA;
    SpiaRegs.SPITXBUF = 0xAAAA;
    SpiaRegs.SPITXBUF = 0xAAAA;
    SpiaRegs.SPITXBUF = 0xAAAA;
    SpiaRegs.SPITXBUF = 0xAAAA;
    SpiaRegs.SPITXBUF = 0xAAAA;
    SpiaRegs.SPITXBUF = 0xAAAA;
}

//
// End of file
//
