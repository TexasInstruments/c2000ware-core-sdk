//###########################################################################
//
// FILE:    Example_2803xEPwmTimeInt.c
//
// TITLE:   ePWM Timer Interrupt (epwm_timer_interrupts) example
//
//! \addtogroup f2803x_example_list
//! <h1>ePWM Timer Interrupt (epwm_timer_interrupts)</h1>
//!
//! This example configures the ePWM Timers and increments a counter each
//! time an interrupt is taken.
//! In this example:
//!  - All ePWM's are initialized.
//!  - All timers have the same period.
//!  - The timers are started sync'ed.
//!  - An interrupt is taken on a zero event for each ePWM timer.
//!  - ePWM1: takes an interrupt every event.
//!  - ePWM2: takes an interrupt every 2nd event.
//!  - ePWM3: takes an interrupt every 3rd event.
//!  - ePWM4: takes an interrupt every event.
//! Thus the Interrupt count for ePWM1 and ePWM4 should be equal.The
//! interrupt count for ePWM2 should be about half that of ePWM1 and
//! the interrupt count for ePWM3 should be about 1/3 that of ePWM1.
//!
//! \b Watch \b Variables \n
//! - EPwm1TimerIntCount
//! - EPwm2TimerIntCount
//! - EPwm3TimerIntCount
//! - EPwm4TimerIntCount
//
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
// Defines for ePWM timer interrupts (1 = enabled,  0 = disabled)
//
#define PWM1_INT_ENABLE  1
#define PWM2_INT_ENABLE  1
#define PWM3_INT_ENABLE  1
#define PWM4_INT_ENABLE  1

//
// Defines for the period for each timer
//
#define PWM1_TIMER_TBPRD   0x1FFF
#define PWM2_TIMER_TBPRD   0x1FFF
#define PWM3_TIMER_TBPRD   0x1FFF
#define PWM4_TIMER_TBPRD   0x1FFF

//
// Prototype statements
//
__interrupt void epwm1_timer_isr(void);
__interrupt void epwm2_timer_isr(void);
__interrupt void epwm3_timer_isr(void);
__interrupt void epwm4_timer_isr(void);

void InitEPwmTimer(void);

//
// Globals
//
Uint32  EPwm1TimerIntCount;
Uint32  EPwm2TimerIntCount;
Uint32  EPwm3TimerIntCount;
Uint32  EPwm4TimerIntCount;

//
// Main
//
void main(void)
{
    int i;

    //
    // Step 1. Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    // This example function is found in the DSP2803x_SysCtrl.c file.
    //
    InitSysCtrl();

    //
    // Step 2. Initialize GPIO:
    // This example function is found in the DSP2803x_Gpio.c file and
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
    // This function is found in the DSP2803x_PieCtrl.c file.
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
    // The shell ISR routines are found in DSP2803x_DefaultIsr.c.
    // This function is found in DSP2803x_PieVect.c.
    //
    InitPieVectTable();

    //
    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    //
    EALLOW;  // This is needed to write to EALLOW protected registers
    PieVectTable.EPWM1_INT = &epwm1_timer_isr;
    PieVectTable.EPWM2_INT = &epwm2_timer_isr;
    PieVectTable.EPWM3_INT = &epwm3_timer_isr;
    PieVectTable.EPWM4_INT = &epwm4_timer_isr;
    EDIS;    // This is needed to disable write to EALLOW protected registers

    //
    // Step 4. Initialize all the Device Peripherals:
    //
    InitEPwmTimer();    // For this example, only initialize the ePWM Timers

    //
    // Step 5. User specific code, enable interrupts:
    //

    //
    // Initialize counters:
    //
    EPwm1TimerIntCount = 0;
    EPwm2TimerIntCount = 0;
    EPwm3TimerIntCount = 0;
    EPwm4TimerIntCount = 0;

    //
    // Enable CPU INT3 which is connected to EPWM1-6 INT:
    //
    IER |= M_INT3;

    //
    // Enable EPWM INTn in the PIE: Group 3 interrupt 1-6
    //
    PieCtrlRegs.PIEIER3.bit.INTx1 = PWM1_INT_ENABLE;
    PieCtrlRegs.PIEIER3.bit.INTx2 = PWM2_INT_ENABLE;
    PieCtrlRegs.PIEIER3.bit.INTx3 = PWM3_INT_ENABLE;
    PieCtrlRegs.PIEIER3.bit.INTx4 = PWM4_INT_ENABLE;

    //
    // Enable global Interrupts and higher priority real-time debug events:
    //
    EINT;   // Enable Global interrupt INTM
    ERTM;   // Enable Global realtime interrupt DBGM

    //
    // Step 6. IDLE loop. Just sit and loop forever (optional):
    //
    for(;;)
    {
        __asm("          NOP");
        for(i=1;i<=10;i++)
        {
            
        }
    }
}

//
// InitEPwmTimer - Initialize EPwm Timer
//
void 
InitEPwmTimer()
{
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;      // Stop all the TB clocks
    EDIS;

    //
    // Setup Sync
    //
    EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;  // Pass through
    EPwm2Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;  // Pass through
    EPwm3Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;  // Pass through
    EPwm4Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN;  // Pass through

    //
    // Allow each timer to be sync'ed
    //
    EPwm1Regs.TBCTL.bit.PHSEN = TB_ENABLE;
    EPwm2Regs.TBCTL.bit.PHSEN = TB_ENABLE;
    EPwm3Regs.TBCTL.bit.PHSEN = TB_ENABLE;
    EPwm4Regs.TBCTL.bit.PHSEN = TB_ENABLE;

    EPwm1Regs.TBPHS.half.TBPHS = 100;
    EPwm2Regs.TBPHS.half.TBPHS = 200;
    EPwm3Regs.TBPHS.half.TBPHS = 300;
    EPwm4Regs.TBPHS.half.TBPHS = 400;

    EPwm1Regs.TBPRD = PWM1_TIMER_TBPRD;
    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;    // Count up
    EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // Select INT on Zero event
    EPwm1Regs.ETSEL.bit.INTEN = PWM1_INT_ENABLE;  // Enable INT
    EPwm1Regs.ETPS.bit.INTPRD = ET_1ST;           // Generate INT on 1st event

    EPwm2Regs.TBPRD = PWM2_TIMER_TBPRD;
    EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;     // Count up
    EPwm2Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;      // Enable INT on Zero event
    EPwm2Regs.ETSEL.bit.INTEN = PWM2_INT_ENABLE;   // Enable INT
    EPwm2Regs.ETPS.bit.INTPRD = ET_2ND;            // Generate INT on 2nd event

    EPwm3Regs.TBPRD = PWM3_TIMER_TBPRD;
    EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;     // Count up
    EPwm3Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;      // Enable INT on Zero event
    EPwm3Regs.ETSEL.bit.INTEN = PWM3_INT_ENABLE;   // Enable INT
    EPwm3Regs.ETPS.bit.INTPRD = ET_3RD;            // Generate INT on 3rd event

    EPwm4Regs.TBPRD = PWM4_TIMER_TBPRD;
    EPwm4Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;     // Count up
    EPwm4Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;      // Enable INT on Zero event
    EPwm4Regs.ETSEL.bit.INTEN = PWM4_INT_ENABLE;   // Enable INT
    EPwm4Regs.ETPS.bit.INTPRD = ET_1ST;            // Generate INT on 1st event

    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;      // Start all the timers synced
    EDIS;
}

//
// epwm1_timer_isr - EPwm1 Timer Interrupt routine
//
__interrupt void 
epwm1_timer_isr(void)
{
    EPwm1TimerIntCount++;

    //
    // Clear INT flag for this timer
    //
    EPwm1Regs.ETCLR.bit.INT = 1;

    //
    // Acknowledge this interrupt to receive more interrupts from group 3
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}

//
// epwm2_timer_isr - EPwm2 Timer Interrupt routine
//
__interrupt void 
epwm2_timer_isr(void)
{
    EPwm2TimerIntCount++;

    //
    // Clear INT flag for this timer
    //
    EPwm2Regs.ETCLR.bit.INT = 1;

    //
    // Acknowledge this interrupt to receive more interrupts from group 3
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}

//
// epwm3_timer_isr - EPwm3 Timer Interrupt routine
//
__interrupt void 
epwm3_timer_isr(void)
{
    EPwm3TimerIntCount++;

    //
    // Clear INT flag for this timer
    //
    EPwm3Regs.ETCLR.bit.INT = 1;

    //
    // Acknowledge this interrupt to receive more interrupts from group 3
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}

//
// epwm4_timer_isr - EPwm4 Timer Interrupt routine
//
__interrupt void 
epwm4_timer_isr(void)
{
    EPwm4TimerIntCount++;

    //
    // Clear INT flag for this timer
    //
    EPwm4Regs.ETCLR.bit.INT = 1;

    //
    // Acknowledge this interrupt to receive more interrupts from group 3
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}

//
// End of File
//

