// TI File $Revision: /main/4 $
// Checkin $Date: July 9, 2009   10:51:59 $
//###########################################################################
//
// FILE:    DSP2833x_CpuTimers.c
//
// TITLE:   CPU 32-bit Timers Initialization & Support Functions.
//
// NOTES:   CpuTimer2 is reserved for use with DSP BIOS and
//          other realtime operating systems.
//
//          Do not use these this timer in your application if you ever plan
//          on integrating DSP-BIOS or another realtime OS.
//
//###########################################################################
// $TI Release: 2833x/2823x Header Files V1.32 $
// $Release Date: June 28, 2010 $
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
#include "DSP2833x_Device.h"     // Headerfile Include File
#include "DSP2833x_Examples.h"   // Examples Include File

//
// Defines
//
struct CPUTIMER_VARS CpuTimer0;

//
// When using DSP BIOS & other RTOS, comment out CPU Timer 2 code.
//
struct CPUTIMER_VARS CpuTimer1;
struct CPUTIMER_VARS CpuTimer2;

//
// InitCpuTimers - This function initializes all three CPU timers to a known 
// state.
//
void 
InitCpuTimers(void)
{
    //
    // CPU Timer 0 - Initialize address pointers to respective timer registers
    //
    CpuTimer0.RegsAddr = &CpuTimer0Regs;
    
    //
    // Initialize timer period to maximum
    //
    CpuTimer0Regs.PRD.all  = 0xFFFFFFFF;
    
    //
    // Initialize pre-scale counter to divide by 1 (SYSCLKOUT)
    //
    CpuTimer0Regs.TPR.all  = 0;
    CpuTimer0Regs.TPRH.all = 0;
    
    //
    // Make sure timer is stopped
    //
    CpuTimer0Regs.TCR.bit.TSS = 1;
    
    //
    // Reload all counter register with period value
    //
    CpuTimer0Regs.TCR.bit.TRB = 1;
    
    //
    // Reset interrupt counters
    //
    CpuTimer0.InterruptCount = 0;

    //
    // CpuTimer2 is reserved for DSP BIOS & other RTOS
    // Do not use this timer if you ever plan on integrating
    // DSP-BIOS or another realtime OS.
    //

    //
    // Initialize address pointers to respective timer registers
    //
    CpuTimer1.RegsAddr = &CpuTimer1Regs;
    CpuTimer2.RegsAddr = &CpuTimer2Regs;
    
    //
    // Initialize timer period to maximum
    //
    CpuTimer1Regs.PRD.all  = 0xFFFFFFFF;
    CpuTimer2Regs.PRD.all  = 0xFFFFFFFF;
    
    //
    // Make sure timers are stopped
    //
    CpuTimer1Regs.TCR.bit.TSS = 1;
    CpuTimer2Regs.TCR.bit.TSS = 1;
    
    //
    // Reload all counter register with period value
    //
    CpuTimer1Regs.TCR.bit.TRB = 1;
    CpuTimer2Regs.TCR.bit.TRB = 1;
    
    //
    // Reset interrupt counters
    //
    CpuTimer1.InterruptCount = 0;
    CpuTimer2.InterruptCount = 0;
}

//
// ConfigCpuTimer - This function initializes the selected timer to the period 
// specified by the "Freq" and "Period" parameters. The "Freq" is entered as 
// "MHz" and the period in "uSeconds". The timer is held in the stopped state
// after configuration.
//
void 
ConfigCpuTimer(struct CPUTIMER_VARS *Timer, float Freq, float Period)
{
    Uint32  temp;

    //
    // Initialize timer period
    //
    Timer->CPUFreqInMHz = Freq;
    Timer->PeriodInUSec = Period;
    temp = (long) (Freq * Period);
    
    //
    // Counter decrements PRD+1 times each period
    //
    Timer->RegsAddr->PRD.all = temp - 1;

    //
    // Set pre-scale counter to divide by 1 (SYSCLKOUT)
    //
    Timer->RegsAddr->TPR.all  = 0;
    Timer->RegsAddr->TPRH.all  = 0;

    //
    // Initialize timer control register
    //
    
    //
    // 1 = Stop timer, 0 = Start/Restart Timer
    //
    Timer->RegsAddr->TCR.bit.TSS = 1;
    
    Timer->RegsAddr->TCR.bit.TRB = 1;    // 1 = reload timer
    Timer->RegsAddr->TCR.bit.SOFT = 1;
    Timer->RegsAddr->TCR.bit.FREE = 1;   // Timer Free Run
    
    //
    // 0 = Disable/ 1 = Enable Timer Interrupt
    //
    Timer->RegsAddr->TCR.bit.TIE = 1;    

    //
    // Reset interrupt counter
    //
    Timer->InterruptCount = 0;
}

//
// End of File
//

