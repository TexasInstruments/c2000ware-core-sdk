//###########################################################################
//
// FILE:    Example_2803xEPwmBlanking.c
//
// TITLE:   ePWM Blanking Window example
//
//! \addtogroup f2803x_example_list
//! <h1> ePWM Blanking Window (epwm_blanking_window) </h1>
//!
//! This example configures ePWM1 and ePWM2
//! - ePWM1: DCAEVT1 forces EPWM1A high, a blanking window is used
//!          EPWM1B toggles on zero as a reference.
//! - ePWM2: DCAEVT1 forces EPWM2A high, no blanking window is used
//!          EPWM2B toggles on zero as a reference.
//! ePWM1A is set to normally stay low. DCAEVT1 is true when TZ1 is
//! low and TZ2 is high.  When an event is true (DCAEVT1) EPWM1A is
//! configured to be forced high. A blanking window is applied to
//! keep the event from taking effect around the zero point. In
//! other words, when the event is taken, EPWM1A will be forced high
//! if there is no event, EPWM1A will remain low.
//! Notice the blanking window keeps the event from forcing EPWM1A
//! high around the zero point.
//! ePWM2 is configured the same way as ePWM1 except no blanking
//! window is applied.
//!
//! Initially tie TZ1 (GPIO12) and TZ2 (GPIO13) high. During the
//! test, monitor ePWM1 or ePWM2 outputs on a scope. Create DCAEVT1
//! by pulling TZ1 low and TZ2 high to see the effect.
//!
//!  \b External \b Connections \n
//!  - ePWM1A is on GPIO0
//!  - ePWM1B is on GPIO1
//!  - ePWM2A is on GPIO2
//!  - ePWM2B is on GPIO3
//!  - TZ1 is on GPIO12
//!  - TZ2 is on GPIO13
//!
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

//
// Main
//
void main(void)
{
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
    // For this case just init GPIO pins for ePWM1, ePWM2, and TZ pins
    //
    InitEPwm1Gpio();
    InitEPwm2Gpio();
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
    // Step 5. User specific code, enable interrupts
    // Initialize counters:
    //
    EPwm1TZIntCount = 0;
    EPwm2TZIntCount = 0;

    //
    // Enable CPU INT3 which is connected to EPWM1-3 INT:
    //
    IER |= M_INT2;

    //
    // Enable EPWM INTn in the PIE: Group 2 interrupt 1-3
    //
    PieCtrlRegs.PIEIER2.bit.INTx1 = 1;
    PieCtrlRegs.PIEIER2.bit.INTx2 = 1;

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
    }
}

//
// epwm1_tzint_isr -
//
__interrupt void 
epwm1_tzint_isr(void)
{
    EPwm1TZIntCount++;

    EALLOW;
    EPwm1Regs.TZCLR.bit.DCAEVT1 = 1;
    EPwm1Regs.TZCLR.bit.INT = 1;
    EDIS;

    //
    // Acknowledge this interrupt to receive more interrupts from group 2
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;
}

//
// epwm2_tzint_isr - 
//
__interrupt void 
epwm2_tzint_isr(void)
{
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
// InitEPwm1Example -
//
void 
InitEPwm1Example()
{
    EPwm1Regs.TBPRD = 1000;                         // Set timer period
    EPwm1Regs.TBPHS.half.TBPHS = 0x0000;            // Phase is 0
    EPwm1Regs.TBCTR = 0x0000;                       // Clear counter

    //
    // Setup TBCLK
    //
    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;     // Count up
    EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
    EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO
    EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

    //
    // Setup compare
    //
    EPwm1Regs.CMPA.half.CMPA = 500;

    //
    // Set actions
    //
    EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR;             // Clear PWM1A on CAU

    //
    // Use EPWM1B as a reference
    //
    EPwm1Regs.AQCTLB.bit.ZRO = AQ_TOGGLE;           // TOGGLE PWM1B on Zero

    //
    // Define an event (DCAEVT1) based on TZ1 and TZ2
    // For blanking we must use the filtered event
    // Use the async path to avoid sync to TBCLK
    //
    EALLOW;
    EPwm1Regs.DCTRIPSEL.bit.DCAHCOMPSEL = DC_TZ1;        // DCAH = TZ1
    EPwm1Regs.DCTRIPSEL.bit.DCALCOMPSEL = DC_TZ2;        // DCAL = TZ2
    
    //
    // DCAEVT1 =  DCAH low, DCAL high;
    //
    EPwm1Regs.TZDCSEL.bit.DCAEVT1 = TZ_DCAL_HI_DCAH_LOW; 
    
    
    EPwm1Regs.DCFCTL.bit.SRCSEL = DC_SRC_DCAEVT1;        
    EPwm1Regs.DCACTL.bit.EVT1SRCSEL = DC_EVT_FLT;        // DCAEVT1 = DCEVTFLT
    EPwm1Regs.DCACTL.bit.EVT1FRCSYNCSEL = DC_EVT_ASYNC;  // Take asynch path

    EPwm1Regs.TZCTL.bit.DCAEVT1 = TZ_FORCE_HI;       // Force DCAEVT1 to high

    //
    // Blank (block) the event during this window
    // The window starts at TBCLK = 875 and is 250 TBCLK wide
    //
    EPwm1Regs.DCFCTL.bit.PULSESEL = DC_PULSESEL_ZERO;
    EPwm1Regs.DCFOFFSET = 875;
    EPwm1Regs.DCFWINDOW = 250;
    EPwm1Regs.DCFCTL.bit.BLANKE = DC_BLANK_ENABLE;
    EPwm1Regs.DCFCTL.bit.BLANKINV = DC_BLANK_NOTINV;

    //
    // Enable interrupt on the DCAEVT1
    //
    EPwm1Regs.TZEINT.bit.DCAEVT1 = 1;
    EDIS;
}

//
// InitEPwm2Example - 
//
void 
InitEPwm2Example()
{
    //
    // The setup for ePWM2 is identical to ePWM1 except
    // there is no blanking window applied.
    //
    EPwm2Regs.TBPRD = 1000;                        // Set timer period
    EPwm2Regs.TBPHS.half.TBPHS = 0x0000;           // Phase is 0
    EPwm2Regs.TBCTR = 0x0000;                      // Clear counter

    //
    // Setup TBCLK
    //
    EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;     // Count up
    EPwm2Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
    EPwm2Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
    EPwm2Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO
    EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

    //
    // Setup compare
    //
    EPwm2Regs.CMPA.half.CMPA = 500;

    //
    // Set actions
    //
    EPwm2Regs.AQCTLA.bit.CAU = AQ_CLEAR;             // Clear PWM2A on CAU
    EPwm2Regs.AQCTLA.bit.ZRO = AQ_SET;               // Set PWM2A on Zero

    //
    // Use EPWM1B as a reference
    //
    EPwm2Regs.AQCTLB.bit.ZRO = AQ_TOGGLE;            // TOGGLE PWM2B on Zero

    //
    // Define an event (DCAEVT1) based on TZ1 and TZ2
    // For blanking we must use the filtered event
    // Use the async path to avoid sync to TBCLK
    //
    EALLOW;
    EPwm2Regs.DCTRIPSEL.bit.DCAHCOMPSEL = DC_TZ1;        // DCAH = TZ1
    EPwm2Regs.DCTRIPSEL.bit.DCALCOMPSEL = DC_TZ2;        // DCAL = TZ2
    
    //
    // DCAEVT1 =  DCAH low, DCAL high;
    //
    EPwm2Regs.TZDCSEL.bit.DCAEVT1 = TZ_DCAL_HI_DCAH_LOW; 
    
    //
    // DCEVTFLT Filter Source = DCAEVT1
    //
    EPwm2Regs.DCFCTL.bit.SRCSEL = DC_SRC_DCAEVT1;        
    
    EPwm2Regs.DCACTL.bit.EVT1SRCSEL = DC_EVT_FLT;        // DCAEVT1 = DCEVTFLT
    EPwm2Regs.DCACTL.bit.EVT1FRCSYNCSEL = DC_EVT_ASYNC;  // Take asynch path


    EPwm2Regs.TZCTL.bit.DCAEVT1 = TZ_FORCE_HI;         // force high on DCAEVT1

    //
    // Blank (block) the event during this window
    // The window starts at TBCLK = 875 and is 250 TBCLK wide
    //
    EPwm2Regs.DCFCTL.bit.PULSESEL = DC_PULSESEL_ZERO;
    EPwm2Regs.DCFOFFSET = 875;
    EPwm2Regs.DCFWINDOW = 250;
    
    //
    // Blanking window is disabled
    //
    EPwm2Regs.DCFCTL.bit.BLANKE = DC_BLANK_DISABLE;
    
    EPwm2Regs.DCFCTL.bit.BLANKINV = 0;

    //
    // Enable interrupt on the DCAEVT1
    //
    EPwm2Regs.TZEINT.bit.DCAEVT1 = 1;
    EDIS;
}

//
// End of File
//

