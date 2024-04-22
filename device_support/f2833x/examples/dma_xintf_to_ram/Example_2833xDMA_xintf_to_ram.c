//###########################################################################
//
// FILE:   Example_2833xDMA_xintf_to_ram.c
//
// TITLE:  DMA XINTF to RAM Example
//
//! \addtogroup f2833x_example_list
//! <h1> DMA XINTF to RAM (dma_xintf_to_ram)</h1>
//!
//! This example will perform a block copy of 1024 words from Zone 7 XINTF 
//! (DMABuf2) to L4 SARAM (DMABuf1).
//! Transfer will be started by Timer0.
//! We will use 32-bit DMA datasize.  Note this is independent from the XINTF
//! data width which is x16.
//!
//! \b Watch \b Variables \n
//! - DMABuf1
//! - DMABuf2
//
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
#define BUF_SIZE   1024  // Sample buffer size

#pragma DATA_SECTION(DMABuf1,"DMARAML4");
#pragma DATA_SECTION(DMABuf2,"ZONE7DATA");

volatile Uint16 DMABuf1[BUF_SIZE];
volatile Uint16 DMABuf2[BUF_SIZE];

volatile Uint16 *DMADest;
volatile Uint16 *DMASource;

//
// Functions Prototypes
//
__interrupt void local_DINTCH1_ISR(void);
void init_zone7(void);

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
    // Disable CPU interrupts and clear all CPU interrupt flags:
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

    IER = M_INT7 ;	                             //Enable INT7 (7.1 DMA Ch1)
    EnableInterrupts();
    CpuTimer0Regs.TCR.bit.TSS  = 1;               //Stop Timer0 for now

    //
    // Step 5. User specific code, enable interrupts:
    //
    
    //
    // Initialize DMA
    //
    DMAInitialize();
    init_zone7();

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
    for(;;);
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
// init_zone7 - Configure the timing parameters for Zone 7.
// Notes:
//    This function should not be executed from XINTF
//    Adjust the timing based on the data manual and
//    external device requirements.
//
void 
init_zone7(void)
{
    //
    // Make sure the XINTF clock is enabled
    //
    SysCtrlRegs.PCLKCR3.bit.XINTFENCLK = 1;

    //
    // Configure the GPIO for XINTF with a 16-bit data bus
    // This function is in DSP2833x_Xintf.c
    //
    InitXintf16Gpio();
    
    EALLOW;
    
    //
    // All Zones
    // Timing for all zones based on XTIMCLK = SYSCLKOUT
    //
    XintfRegs.XINTCNF2.bit.XTIMCLK = 0;
    
    //
    // Buffer up to 3 writes
    //
    XintfRegs.XINTCNF2.bit.WRBUFF = 3;
    
    //
    // XCLKOUT is enabled
    //
    XintfRegs.XINTCNF2.bit.CLKOFF = 0;
    
    //
    // XCLKOUT = XTIMCLK
    //
    XintfRegs.XINTCNF2.bit.CLKMODE = 0;
    
    //
    // Disable XHOLD to prevent XINTF bus from going into high impedance state
    // whenever TZ3 signal goes low. This occurs because TZ3 on GPIO14 is
    // shared with HOLD of XINTF
    //
    XintfRegs.XINTCNF2.bit.HOLD = 1;

    //
    // Zone 7
    // When using ready, ACTIVE must be 1 or greater
    // Lead must always be 1 or greater
    // Zone write timing
    //
    XintfRegs.XTIMING7.bit.XWRLEAD = 1;
    XintfRegs.XTIMING7.bit.XWRACTIVE = 2;
    XintfRegs.XTIMING7.bit.XWRTRAIL = 1;
    
    //
    // Zone read timing
    //
    XintfRegs.XTIMING7.bit.XRDLEAD = 1;
    XintfRegs.XTIMING7.bit.XRDACTIVE = 3;
    XintfRegs.XTIMING7.bit.XRDTRAIL = 0;

    //
    // don't double all Zone read/write lead/active/trail timing
    //
    XintfRegs.XTIMING7.bit.X2TIMING = 0;

    //
    // Zone will not sample XREADY signal
    //
    XintfRegs.XTIMING7.bit.USEREADY = 0;
    XintfRegs.XTIMING7.bit.READYMODE = 0;

    //
    // 1,1 = x16 data bus
    // 0,1 = x32 data bus
    // other values are reserved
    //
    XintfRegs.XTIMING7.bit.XSIZE = 3;
    EDIS;

    //
    // Force a pipeline flush to ensure that the write to
    // the last register configured occurs before returning.
    //
    __asm(" RPT #7 || NOP");
}

//
// End of File
//

