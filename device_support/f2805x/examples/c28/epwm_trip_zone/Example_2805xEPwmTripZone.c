//###########################################################################
//
// FILE:    Example_2805xEPwmTimeZone.c
//
// TITLE:   ePWM Trip Zone (epwm_trip_zone) example
//
//! \addtogroup f2805x_example_list
//! <h1>ePWM Trip Zone </h1>
//!
//! This example configures ePWM1 and ePWM2 as follows
//!  - ePWM1 has TZ1 and TZ2 as one shot trip sources
//!  - ePWM2 has TZ1 and TZ2 as cycle by cycle trip sources
//!
//! Initially tie TZ1 and TZ2 high. During the test, monitor ePWM1 or ePWM2
//! outputs on a scope. Pull TZ1 or TZ2 low to see the effect.
//!
//!  \b External \b Connections \n
//!  - EPWM1A is on GPIO0
//!  - EPWM1B is on GPIO1
//!  - EPWM2A is on GPIO2
//!  - EPWM2B is on GPIO3
//!  - TZ1 is on GPIO12
//!  - TZ2 is on GPIO13
//
//###########################################################################
// $TI Release: $
// $Release Date: $
// $Copyright:
// Copyright (C) 2012-2024 Texas Instruments Incorporated - http://www.ti.com/
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
// Prototype statements
//
void InitEPwm1Example(void);
void InitEPwm2Example(void);
__interrupt void epwm1_tzint_isr(void);
__interrupt void epwm2_tzint_isr(void);

//
// Globals
//
Uint32  EPwm1TZIntCount;
Uint32  EPwm2TZIntCount;

void main(void)
{
    //
    // Step 1. Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    // This example function is found in the F2805x_SysCtrl.c file.
    //
    InitSysCtrl();

    //
    // Step 2. Initialize GPIO:
    // This example function is found in the F2805x_Gpio.c file and
    // illustrates how to set the GPIO to it's default state.
    //
    // InitGpio();  // Skipped for this example

    //
    // For this case just init GPIO pins for ePWM1, ePWM2, and TZ pins
    //
    InitEPwm1Gpio();
    InitEPwm2Gpio();
    InitTzGpio();

    //
    // Step 3. Clear all __interrupts and initialize PIE vector table:
    // Disable CPU __interrupts
    //
    DINT;

    //
    // Initialize the PIE control registers to their default state.
    // The default state is all PIE __interrupts disabled and flags
    // are cleared.
    // This function is found in the F2805x_PieCtrl.c file.
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
    // The shell ISR routines are found in F2805x_DefaultIsr.c.
    // This function is found in F2805x_PieVect.c.
    //
    InitPieVectTable();

    //
    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    //
    EALLOW;  // This is needed to write to EALLOW protected registers
    PieVectTable.EPWM1_TZINT = &epwm1_tzint_isr;
    PieVectTable.EPWM2_TZINT = &epwm2_tzint_isr;
    EDIS;    // This is needed to disable write to EALLOW protected registers

    //
    // Step 4. Initialize all the Device Peripherals:
    // Not required for this example
    //
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;
    EDIS;

    InitEPwm1Example();
    InitEPwm2Example();

    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;

    //
    // Step 5. User specific code, enable __interrupts
    // Initialize counters:
    //
    EPwm1TZIntCount = 0;
    EPwm2TZIntCount = 0;

    //
    // Enable CPU INT3 which is connected to EPWM1-3 INT:
    //
    IER |= M_INT2;

    //
    // Enable EPWM INTn in the PIE: Group 2 __interrupt 1-3
    //
    PieCtrlRegs.PIEIER2.bit.INTx1 = 1;
    PieCtrlRegs.PIEIER2.bit.INTx2 = 1;

    //
    // Enable global Interrupts and higher priority real-time debug events:
    //
    EINT;   // Enable Global __interrupt INTM
    ERTM;   // Enable Global realtime __interrupt DBGM

    //
    // Step 6. IDLE loop. Just sit and loop forever (optional):
    //
    for(;;)
    {
        asm("          NOP");
    }
}

__interrupt void epwm1_tzint_isr(void)
{
    EPwm1TZIntCount++;

    //
    // Leave these flags set so we only take this
    // __interrupt once
    //
    // EALLOW;
    // EPwm1Regs.TZCLR.bit.OST = 1;
    // EPwm1Regs.TZCLR.bit.INT = 1;
    // EDIS;

    //
    // Acknowledge this __interrupt to receive more __interrupts from group 2
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;
}

__interrupt void epwm2_tzint_isr(void)
{
    EPwm2TZIntCount++;

    //
    // Clear the flags - we will continue to take
    // this __interrupt until the TZ pin goes high
    //
    EALLOW;
    EPwm2Regs.TZCLR.bit.CBC = 1;
    EPwm2Regs.TZCLR.bit.INT = 1;
    EDIS;

    //
    // Acknowledge this __interrupt to receive more __interrupts from group 2
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;
}

void InitEPwm1Example()
{
    //
    // Enable TZ1 and TZ2 as one shot trip sources
    //
    EALLOW;
    EPwm1Regs.TZSEL.bit.OSHT1 = 1;
    EPwm1Regs.TZSEL.bit.OSHT2 = 1;

    //
    // What do we want the TZ1 and TZ2 to do?
    //
    EPwm1Regs.TZCTL.bit.TZA = TZ_FORCE_HI;
    EPwm1Regs.TZCTL.bit.TZB = TZ_FORCE_LO;

    //
    // Enable TZ __interrupt
    //
    EPwm1Regs.TZEINT.bit.OST = 1;
    EDIS;

    EPwm1Regs.TBPRD = 6000;                         // Set timer period
    EPwm1Regs.TBPHS.half.TBPHS = 0x0000;            // Phase is 0
    EPwm1Regs.TBCTR = 0x0000;                       // Clear counter

    //
    // Setup TBCLK
    //
    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
    EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV4;       // Clock ratio to SYSCLKOUT
    EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV4;

    EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO
    EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

    //
    // Setup compare
    //
    EPwm1Regs.CMPA.half.CMPA = 3000;

    //
    // Set actions
    //
    EPwm1Regs.AQCTLA.bit.CAU = AQ_SET;             // Set PWM1A on Zero
    EPwm1Regs.AQCTLA.bit.CAD = AQ_CLEAR;


    EPwm1Regs.AQCTLB.bit.CAU = AQ_CLEAR;          // Set PWM1A on Zero
    EPwm1Regs.AQCTLB.bit.CAD = AQ_SET;
}

void InitEPwm2Example()
{
    //
    // Enable TZ1 and TZ2 as one cycle-by-cycle trip sources
    //
    EALLOW;
    EPwm2Regs.TZSEL.bit.CBC1 = 1;
    EPwm2Regs.TZSEL.bit.CBC2 = 1;

    //
    // What do we want the TZ1 and TZ2 to do?
    //
    EPwm2Regs.TZCTL.bit.TZA = TZ_FORCE_HI;
    EPwm2Regs.TZCTL.bit.TZB = TZ_FORCE_LO;

    //
    // Enable TZ __interrupt
    //
    EPwm2Regs.TZEINT.bit.CBC = 1;
    EDIS;

    EPwm2Regs.TBPRD = 6000;                        // Set timer period
    EPwm2Regs.TBPHS.half.TBPHS = 0x0000;           // Phase is 0
    EPwm2Regs.TBCTR = 0x0000;                      // Clear counter

    //
    // Setup TBCLK
    //
    EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
    EPwm2Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
    EPwm2Regs.TBCTL.bit.HSPCLKDIV = TB_DIV4;       // Clock ratio to SYSCLKOUT
    EPwm2Regs.TBCTL.bit.CLKDIV = TB_DIV4;          // Slow just to observe on the scope

    //
    // Setup compare
    //
    EPwm2Regs.CMPA.half.CMPA = 3000;

    //
    // Set actions
    //
    EPwm2Regs.AQCTLA.bit.CAU = AQ_SET;             // Set PWM2A on Zero
    EPwm2Regs.AQCTLA.bit.CAD = AQ_CLEAR;


    EPwm2Regs.AQCTLB.bit.CAU = AQ_CLEAR;           // Set PWM2A on Zero
    EPwm2Regs.AQCTLB.bit.CAD = AQ_SET;
}

//
// End of file.
//
