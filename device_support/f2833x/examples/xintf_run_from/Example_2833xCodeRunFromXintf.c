//###########################################################################
//
// FILE:	Example_2833xCodeRunFromXintf.c
//
// TITLE:	Code Run from XINTF Example
//
//! \addtogroup f2833x_example_list
//! <h1>Code Run from XINTF (xintf_run_from)</h1>
//!
//! This example configures CPU Timer0 and increments
//! a counter each time the timer asserts an interrupt.
//!
//! The code is loaded into SARAM.  The XINTF Zone 7 is
//! configured for x16-bit data bus.  A portion of the code
//! is copied to XINTF for execution there.
//!
//! \b Watch \b Variables \n
//! - CpuTimer0.InterruptCount
//! - CpuTimer1.InterruptCount
//! - CpuTimer2.InterruptCount
//
//###########################################################################
// $TI Release: $
// $Release Date: $
// $Copyright:
// Copyright (C) 2009-2023 Texas Instruments Incorporated - http://www.ti.com/
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
#include <string.h>

//
// These two functions will be loaded into SARAM and copied to XINTF zone 7 for
// execution
//
#pragma CODE_SECTION(cpu_timer0_isr,"xintffuncs");
#pragma CODE_SECTION(cpu_timer1_isr,"xintffuncs");

//
// Function Prototypes
//
void init_zone7(void);
__interrupt void cpu_timer0_isr(void);
__interrupt void cpu_timer1_isr(void);
__interrupt void cpu_timer2_isr(void);

//
// Main
//
void main(void)
{
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
    EALLOW;         // This is needed to write to EALLOW protected registers
    PieVectTable.TINT0 = &cpu_timer0_isr;
    PieVectTable.XINT13 = &cpu_timer1_isr;
    PieVectTable.TINT2 = &cpu_timer2_isr;
    EDIS;    // This is needed to disable write to EALLOW protected registers

    //
    // Step 4. Initialize the Device Peripheral. This function can be
    //         found in DSP2833x_CpuTimers.c
    //
    InitCpuTimers();   // For this example, only initialize the Cpu Timers

#if (CPU_FRQ_150MHZ)
    //
    // Configure CPU-Timer 0, 1, and 2 to interrupt every second:
    // 150MHz CPU Freq, 1 second Period (in uSeconds)
    //
    ConfigCpuTimer(&CpuTimer0, 150, 1000000);
    ConfigCpuTimer(&CpuTimer1, 150, 1000000);
    ConfigCpuTimer(&CpuTimer2, 150, 1000000);
#endif

#if (CPU_FRQ_100MHZ)
    //
    // Configure CPU-Timer 0, 1, and 2 to interrupt every second:
    // 100MHz CPU Freq, 1 second Period (in uSeconds)
    //
    ConfigCpuTimer(&CpuTimer0, 100, 1000000);
    ConfigCpuTimer(&CpuTimer1, 100, 1000000);
    ConfigCpuTimer(&CpuTimer2, 100, 1000000);
#endif

    //
    // To ensure precise timing, use write-only instructions to write to the 
    // entire register. Therefore, if any of the configuration bits are changed
    // in ConfigCpuTimer and InitCpuTimers (in DSP2833x_CpuTimers.h), the
    // below settings must also be updated.
    //
    
    //
    // Use write-only instruction to set TSS bit = 0
    //
    CpuTimer0Regs.TCR.all = 0x4000;
    
    //
    // Use write-only instruction to set TSS bit = 0
    //
    CpuTimer1Regs.TCR.all = 0x4000;
    
    //
    // Use write-only instruction to set TSS bit = 0
    //
    CpuTimer2Regs.TCR.all = 0x4000;

    //
    // Step 5. User specific code, enable interrupts:
    //

    //
    // Initialize XINTF Zone 7
    //
    init_zone7();

    //
    // Copy non-time critical code to XINTF
    // This includes the following ISR functions: cpu_timer0_isr(), 
    // cpu_timer1_isr(). The  XintffuncsLoadStart, XintffuncsLoadEnd, 
    // and XintffuncsRunStart symbols are created by the linker. Refer to the
    // F28335_ram_xintf.cmd file.
    //
    memcpy(&XintffuncsRunStart, &XintffuncsLoadStart,
           (Uint32)&XintffuncsLoadSize);

    //
    // Enable CPU int1 which is connected to CPU-Timer 0, CPU int13
    // which is connected to CPU-Timer 1, and CPU int 14, which is connected
    // to CPU-Timer 2:
    //
    IER |= M_INT1;
    IER |= M_INT13;
    IER |= M_INT14;

    //
    // Enable TINT0 in the PIE: Group 1 interrupt 7
    //
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;

    //
    // Enable global Interrupts and higher priority real-time debug events
    //
    EINT;       // Enable Global interrupt INTM
    ERTM;       // Enable Global realtime interrupt DBGM

    //
    // Step 6. IDLE loop. Just sit and loop forever (optional)
    //
    for(;;);
}

//
// cpu_timer0_isr -
//
__interrupt void
cpu_timer0_isr(void)
{
    CpuTimer0.InterruptCount++;

    //
    // Acknowledge this interrupt to receive more interrupts from group 1
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

//
// cpu_timer1_isr -
//
__interrupt void
cpu_timer1_isr(void)
{
    CpuTimer1.InterruptCount++;
    
    //
    // The CPU acknowledges the interrupt.
    //
    EDIS;
}

//
// cpu_timer2_isr - 
//
__interrupt void
cpu_timer2_isr(void)
{ 
    EALLOW;
    CpuTimer2.InterruptCount++;
    
    //
    // The CPU acknowledges the interrupt.
    //
    EDIS;
}

//
// init_zone7 - Configure the timing parameters for Zone 7.
// Notes: This function should not be executed from XINTF. Adjust the timing
//        based on the data manual and external device requirements.
//
void 
init_zone7(void)
{
    //
    // Make sure the XINTF clock is enabled
    //
    EALLOW;
    SysCtrlRegs.PCLKCR3.bit.XINTFENCLK = 1;
    EDIS;

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
    // When using ready, ACTIVE must be 1 or greater. Lead must always be 1 or 
    // greater. Zone write timing
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

