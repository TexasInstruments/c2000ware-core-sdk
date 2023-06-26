//###########################################################################
//
// FILE:    LedBlink.c
//
// TITLE:   LED Blink Getting Started Program.
//
//! \addtogroup cpu01_example_list
//! <h1>LED Blink Getting Started Program (timed_led_blink)</h1>
//!
//!  This example configures CPU Timer0 for a 500 msec period, and toggles the
//!  GPIO34 LED once per interrupt. For testing purposes, this example
//!  also increments a counter each time the timer asserts an interrupt.
//!
//!  \b Watch \b Variables \n
//!  - CpuTimer0.InterruptCount
//!
//!  Monitor the GPIO34 LED blink on (for 500 msec) and off (for 500 msec) on
//!  the F2837xD control card.
//!
//
//###########################################################################
//
// $Release Date:  $
// $Copyright:
// Copyright (C) 2013-2023 Texas Instruments Incorporated - http://www.ti.com/
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
// Function Prototypes
//
__interrupt void cpu_timer0_isr(void);

void main(void)
{
//
// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the F2837xD_SysCtrl.c file.
//
   InitSysCtrl();

//
// Step 2. Initialize GPIO:
// This example function is found in the F2837xD_Gpio.c file and
// illustrates how to set the GPIO to it's default state.
//
// InitGpio();  // Skipped for this example

//
// Step 3. Clear all __interrupts and initialize PIE vector table:
//
   DINT;

//
// Initialize the PIE control registers to their default state.
// The default state is all PIE __interrupts disabled and flags
// are cleared.
// This function is found in the F2837xD_PieCtrl.c file.
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
// The shell ISR routines are found in F2837xD_DefaultIsr.c.
// This function is found in F2837xD_PieVect.c.
//
   InitPieVectTable();

//
// Interrupts that are used in this example are re-mapped to
// ISR functions found within this file.
//
   EALLOW;  // This is needed to write to EALLOW protected registers
   PieVectTable.TIMER0_INT = &cpu_timer0_isr;
   EDIS;    // This is needed to disable write to EALLOW protected registers

//
// Step 4. Initialize the Device Peripheral. This function can be
//         found in F2837xD_CpuTimers.c
//
   InitCpuTimers();   // For this example, only initialize the Cpu Timers

//
// Configure CPU-Timer 0 to __interrupt every 500 milliseconds:
// 60MHz CPU Freq, 50 millisecond Period (in uSeconds)
//
   ConfigCpuTimer(&CpuTimer0, 60, 500000);

//
// To ensure precise timing, use write-only instructions to write to the entire
// register. Therefore, if any of the configuration bits are changed in
// ConfigCpuTimer and InitCpuTimers (in F2837xD_cputimervars.h), the below
// settings must also be updated.
//
   CpuTimer0Regs.TCR.all = 0x4001;

//
// Step 5. User specific code, enable __interrupts:
// Configure GPIO34 as a GPIO output pin
//
   EALLOW;
   GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;
   GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1;
   EDIS;

//
// Enable CPU INT1 which is connected to CPU-Timer 0:
//
   IER |= M_INT1;

//
// Enable TINT0 in the PIE: Group 1 __interrupt 7
//
   PieCtrlRegs.PIEIER1.bit.INTx7 = 1;

//
// Enable global Interrupts and higher priority real-time debug events:
//
   EINT;   // Enable Global __interrupt INTM
   ERTM;   // Enable Global realtime __interrupt DBGM

//
// Step 6. IDLE loop. Just sit and loop forever (optional):
//
   for(;;);
}

//
// cpu_timer0_isr - CPU Timer0 ISR that toggles GPIO32 once per 500ms
//
__interrupt void cpu_timer0_isr(void)
{
   CpuTimer0.InterruptCount++;
   GpioDataRegs.GPBTOGGLE.bit.GPIO34 = 1;

   //
   // Acknowledge this __interrupt to receive more __interrupts from group 1
   //
   PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

//
// End of file
//
