//###########################################################################
//
// FILE:   epwm_ex1_trip_zone.c
//
// TITLE:  ePWM module using Trip-Zone submodule.
//
//! \addtogroup cpu01_example_list
//! <h1> EPWM Trip Zone Module (epwm_trip_zone)</h1>
//!
//! This example configures ePWM1 and ePWM2 as follows
//!  - ePWM1 has TZ1 as one shot trip source
//!  - ePWM2 has TZ1 as cycle by cycle trip source
//!
//! Initially tie TZ1 high. During the test, monitor ePWM1 or ePWM2
//! outputs on a scope. Pull TZ1 low to see the effect.
//!
//!  \b External \b Connections \n
//!  - EPWM1A is on GPIO0
//!  - EPWM2A is on GPIO2
//!  - TZ1 is on GPIO12
//!
//! This example also makes use of the Input X-BAR. GPIO12 (the external
//! trigger) is routed to the input X_BAR, from which it is routed to TZ1.
//!
//! The TZ-Event is defined such that EPWM1A will undergo a One-Shot Trip
//! and EPWM2A will undergo a Cycle-By-Cycle Trip.
//!
//              _____________             __________________
//              |           |             |                |
//  GPIO12 -----| I/P X-BAR |-----TZ1-----| ePWM TZ Module |-----TZ-Event
//              |___________|             |________________|
//
//
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
// Defines
//
#define EXTTrig     // Leave Uncommented for Testing with External Trigger.
                    // Comment for Testing with ePWM Trigger.

//
// Globals
//
Uint32  EPwm1TZIntCount;
Uint32  EPwm2TZIntCount;

//
// Function Prototypes
//
void InitEPwm1Example(void);
void InitEPwm2Example(void);
void InitTzGpio(void);
__interrupt void epwm1_tzint_isr(void);
__interrupt void epwm2_tzint_isr(void);
void InitEPwmGpio_TZ(void);

//
// Main
//
void main(void)
{
//
// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the f2838x_sysctrl.c file.
//
    InitSysCtrl();

//
// Step 2. Initialize GPIO:
// This example function is found in the <device>_gpio.c file and
// illustrates how to set the GPIO to it's default state.
//
    InitGpio();

//
// enable PWM1, and PWM2
//
    EALLOW;
    CpuSysRegs.PCLKCR2.bit.EPWM1=1;
    CpuSysRegs.PCLKCR2.bit.EPWM2=1;
    EDIS;

//
// For this case just init GPIO pins for ePWM1, ePWM2, ePWM3
//
    InitEPwmGpio_TZ();
    InitTzGpio();

//
// Step 3. Clear all interrupts and initialize PIE vector table:
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
// Disable CPU interrupts and clear all CPU interrupt flags:
//
    IER = 0x0000;
    IFR = 0x0000;

//
// Initialize the PIE vector table with pointers to the shell Interrupt
// Service Routines (ISR).
// This will populate the entire table, even if the interrupt
// is not used in this example.  This is useful for debug purposes.
// The shell ISR routines are found in f2838x_defaultisr.c.
// This function is found in f2838x_pievect.c.
//
    InitPieVectTable();

//
// Interrupts that are used in this example are re-mapped to
// ISR functions found within this file.
//
    EALLOW; // This is needed to write to EALLOW protected registers
    PieVectTable.EPWM1_TZ_INT = &epwm1_tzint_isr;
    PieVectTable.EPWM2_TZ_INT = &epwm2_tzint_isr;
    EDIS;   // This is needed to disable write to EALLOW protected registers

//
// Step 4. Initialize the Device Peripherals:
//
    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC =0;
    EDIS;

    InitEPwm1Example();
    InitEPwm2Example();

    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC =1;
    EDIS;

//
// Step 5. User specific code, enable interrupts:
//
    EPwm1TZIntCount = 0;
    EPwm2TZIntCount = 0;

//
// Enable CPU INT2 which is connected to EPWM1-3 INT:
//
    IER |= M_INT2;

//
// Enable EPWM INTn in the PIE: Group 3 interrupt 1-3
//
    PieCtrlRegs.PIEIER2.bit.INTx1 = 1;
    PieCtrlRegs.PIEIER2.bit.INTx2 = 1;

//
// Enable global Interrupts and higher priority real-time debug events:
//
    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global realtime interrupt DBGM

//
// Step 6. IDLE loop. Just sit and loop forever (optional):
//
    for(;;)
    {
        asm ("  NOP");
    }
}

//
// epwm1_tzint_isr - EPWM1 TZ ISR
//
__interrupt void epwm1_tzint_isr(void)
{
    EPwm1TZIntCount++;

    //
    // To Re-enable the OST Interrupt, do the following:
    // EALLOW;
    // EPwm1Regs.TZCLR.bit.OST = 1;
    // EPwm1Regs.TZCLR.bit.INT = 1;
    // EDIS;
    //

    //
    // Acknowledge this interrupt to receive more interrupts from group 2
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;
}

//
// epwm2_tzint_isr - EPWM2 TZ ISR
//
__interrupt void epwm2_tzint_isr(void)
{
    GpioDataRegs.GPATOGGLE.bit.GPIO11 = 1;

    EPwm2TZIntCount++;

    //
    // Clear the flags - we will continue to take
    // this interrupt until the TZ pin goes high
    //
    EALLOW;
    EPwm2Regs.TZCLR.bit.CBC = 1;
    EPwm2Regs.TZCLR.bit.INT = 1;
    EDIS;

    //
    // Acknowledge this interrupt to receive more interrupts from group 2
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;
}

//
// InitEPwm1Example - Initialize EPWM1 configuration
//
void InitEPwm1Example()
{
    //
    // Enable TZ1 as one shot trip sources
    //
    EALLOW;
    EPwm1Regs.TZSEL.bit.OSHT1 = 1;

    //
    // Set TZA
    //
    EPwm1Regs.TZCTL.bit.TZA = TZ_FORCE_HI;

    //
    // Enable TZ interrupt
    //
    EPwm1Regs.TZEINT.bit.OST = 1;
    EDIS;

    EPwm1Regs.TBPRD = 12000;                        // Set timer period
    EPwm1Regs.TBPHS.bit.TBPHS = 0x0000;             // Phase is 0
    EPwm1Regs.TBCTR = 0x0000;                       // Clear counter

    //
    // Setup TBCLK
    //
    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
    EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV4;       // Clock ratio to SYSCLKOUT
    EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV4;

    EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO
    EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;

    //
    // Setup compare
    //
    EPwm1Regs.CMPA.bit.CMPA = 6000;

    //
    // Set actions
    //
    EPwm1Regs.AQCTLA.bit.CAU = AQ_SET;             // Set PWM1A on CAU
    EPwm1Regs.AQCTLA.bit.CAD = AQ_CLEAR;           // Clear PWM1A on CAD
}

//
// InitEPwm2Example - Initialize EPWM2 configuration
//
void InitEPwm2Example()
{
    //
    // Enable TZ1 as one cycle-by-cycle trip sources
    //
    EALLOW;
    EPwm2Regs.TZSEL.bit.CBC1 = 1;

    //
    // Set TZA
    //
    EPwm2Regs.TZCTL.bit.TZA = TZ_FORCE_HI;

    //
    // Enable TZ interrupt
    //
    EPwm2Regs.TZEINT.bit.CBC = 1;
    EDIS;

    EPwm2Regs.TBPRD = 6000;                       // Set timer period
    EPwm2Regs.TBPHS.bit.TBPHS = 0x0000;           // Phase is 0
    EPwm2Regs.TBCTR = 0x0000;                     // Clear counter

    //
    // Setup TBCLK
    //
    EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
    EPwm2Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
    EPwm2Regs.TBCTL.bit.HSPCLKDIV = TB_DIV4;       // Clock ratio to SYSCLKOUT
    EPwm2Regs.TBCTL.bit.CLKDIV = TB_DIV4;          // Slow just to observe on
                                                   // the scope.

    //
    // Setup compare
    //
    EPwm2Regs.CMPA.bit.CMPA = 3000;

    //
    // Set actions
    //
    EPwm2Regs.AQCTLA.bit.CAU = AQ_SET;             // Set PWM2A on CAU
    EPwm2Regs.AQCTLA.bit.CAD = AQ_CLEAR;           // Clear PWM2A on CAD
}

//
// InitTzGpio - Initialize TZ GPIOs
//
void InitTzGpio(void)
{
    //
    // For External Trigger, GPIO12 as the trigger for TripZone
    //
    EALLOW;
    GpioCtrlRegs.GPAPUD.bit.GPIO12 = 0;    // Enable pull-up on GPIO12 (TZ1)

    GpioCtrlRegs.GPAQSEL1.bit.GPIO12 = 3;  // Asynch input GPIO12 (TZ1)
    EDIS;

    EALLOW;
    InputXbarRegs.INPUT1SELECT = 12;
    EDIS;

    //
    // For monitoring when the TZ Interrupt has been entered
    //
    EALLOW;
    GpioCtrlRegs.GPAPUD.bit.GPIO11 = 1;    // Disable pull-up on GPIO0 (EPWM1A)
    GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 0;   // Configure GPIO0 as EPWM1A
    GpioCtrlRegs.GPADIR.bit.GPIO11 = 1;
    EDIS;
}

//
// InitEPwmGpio_TZ - Initialize EPWM1A and EPWM2A GPIOs
//
void InitEPwmGpio_TZ(void)
{
    EALLOW;
    GpioCtrlRegs.GPAPUD.bit.GPIO0 = 1;    // Disable pull-up on GPIO0 (EPWM1A)
    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;   // Configure GPIO0 as EPWM1A
    GpioCtrlRegs.GPAPUD.bit.GPIO2 = 1;    // Disable pull-up on GPIO2 (EPWM2A)
    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;   // Configure GPIO2 as EPWM2A
    EDIS;
}

//
// End of file
//
