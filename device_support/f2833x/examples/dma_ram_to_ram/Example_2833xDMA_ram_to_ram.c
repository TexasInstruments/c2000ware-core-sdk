//###########################################################################
//
// FILE:   Example_2833xDMA_ram_to_ram.c
//
// TITLE:  DMA Ram to Ram Example
//
//! \addtogroup f2833x_example_list
//! <h1> DMA Ram to Ram (dma_ram_to_ram)</h1>
//!
//! This example will perform a block copy from L5 SARAM to L4 SARAM of 1024
//! words. Transfer will be started by Timer0. Will use 32-bit data size to
//! decrease the transfer time.
//!
//! \b Watch \b Variables \n
//! - DMABuf1
//! - DMABuf2
//
//###########################################################################
// $TI Release: $
// $Release Date: $
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
#define BUF_SIZE   1024         // Sample buffer size

//
// DMA Defines
//
#define CH1_TOTAL               DATA_POINTS_PER_CHANNEL
#define CH1_WORDS_PER_BURST     ADC_CHANNELS_TO_CONVERT

#pragma DATA_SECTION(DMABuf1,"DMARAML4");
#pragma DATA_SECTION(DMABuf2,"DMARAML5");

volatile Uint16 DMABuf1[1024];
volatile Uint16 DMABuf2[1024];

volatile Uint16 *DMADest;
volatile Uint16 *DMASource;

//
// Function Prototypes
//
__interrupt void local_DINTCH1_ISR(void);

//
// Main
//
void main(void)
{
    Uint16 i;
    
    //
    // Step 1. Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    // This example function is found in the DSP2833x_SysCtrl.c file.
    //
    InitSysCtrl();

    //
    // Step 2. Initialize GPIO:
    // This example function is found in the DSP2833x_Gpio.c file and
    // illustrates how to set the GPIO to it's default state.
    //
    // InitGpio();  // Skipped for this example

    //
    // Step 3. Clear all interrupts and initialize PIE vector table:
    // Disable CPU interrupts
    //
    DINT;

    //
    // Initialize the PIE control registers to their default state.
    // The default state is all PIE interrupts disabled and flags
    // are cleared.
    // This function is found in the DSP2833x_PieCtrl.c file.
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
    // The shell ISR routines are found in DSP2833x_DefaultIsr.c.
    // This function is found in DSP2833x_PieVect.c.
    //
    InitPieVectTable();

    //
    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    //
    EALLOW;	// Allow access to EALLOW protected registers
    PieVectTable.DINTCH1= &local_DINTCH1_ISR;
    EDIS;   // Disable access to EALLOW protected registers

    IER = M_INT7 ;                        //Enable INT7 (7.1 DMA Ch1)
    EnableInterrupts();
    CpuTimer0Regs.TCR.bit.TSS  = 1;       //Stop Timer0 for now

    //
    // Step 5. User specific code, enable interrupts:
    //
    
    //
    // Initialize DMA
    //
    DMAInitialize();

    //
    // Initialize Tables
    //
    for (i=0; i<BUF_SIZE; i++)
    {
        DMABuf1[i] = 0;
        DMABuf2[i] = i;
    }

    //
    // Configure DMA Channel
    //
    DMADest   = &DMABuf1[0];
    DMASource = &DMABuf2[0];
    DMACH1AddrConfig(DMADest,DMASource);
    
    //
    // Will set up to use 32-bit datasize, pointers are based on 16-bit words
    //
    DMACH1BurstConfig(31,2,2);
    
    //
    // so need to increment by 2 to grab the correct location
    //
    DMACH1TransferConfig(31,2,2);
    DMACH1WrapConfig(0xFFFF,0,0xFFFF,0);
    
    //
    // Use timer0 to start the x-fer.
    // Since this is a static copy use one shot mode, so only one trigger 
    // is needed. Also using 32-bit mode to decrease x-fer time
    //
    DMACH1ModeConfig(DMA_TINT0,PERINT_ENABLE,ONESHOT_ENABLE,CONT_DISABLE,
                     SYNC_DISABLE,SYNC_SRC,OVRFLOW_DISABLE,THIRTYTWO_BIT,
                     CHINT_END,CHINT_ENABLE);

    StartDMACH1();

    //
    // Init the timer 0
    //
    
    //
    // load low value so we can start the DMA quickly
    //
    CpuTimer0Regs.TIM.half.LSW = 512;
    CpuTimer0Regs.TCR.bit.SOFT = 1;      //Allow to free run even if halted
    CpuTimer0Regs.TCR.bit.FREE = 1;
    CpuTimer0Regs.TCR.bit.TIE  = 1;      //Enable the timer0 interrupt signal
    CpuTimer0Regs.TCR.bit.TSS  = 0;      //restart the timer 0
    for(;;)
    {
        
    }
}

//
// local_DINTCH1_ISR - INT7.1(DMA Channel 1)
//
__interrupt void 
local_DINTCH1_ISR(void)
{
    //
    // To receive more interrupts from this PIE group, acknowledge this 
    // interrupt
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;

    //
    // Next two lines for debug only to halt the processor here
    // Remove after inserting ISR Code
    //
    __asm ("      ESTOP0");
    for(;;);
}

//
// End of File
//

