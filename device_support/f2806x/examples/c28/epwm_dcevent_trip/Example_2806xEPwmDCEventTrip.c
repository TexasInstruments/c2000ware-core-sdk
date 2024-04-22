//###########################################################################
//
// FILE:   Example_2806xEPwmDCEventTrip.c
//
// TITLE:  ePWM DC Event Trip Example
//
//! \addtogroup f2806x_example_list
//! <h1>ePWM DC Event Trip (epwm_dcevent_trip)</h1>
//!
//! In this example ePWM1, ePWM2, and ePWM3 are configured for PWM Digital 
//! Compare Event Trip using Trip zone pin inputs.
//! DCAEVT1, DCAEVT2, DCBEVT1 and DCBEVT2 events are all defined as true 
//! when TZ1 is low and TZ2 is high.
//! 3 Examples are included:
//!  - ePWM1 has DCAEVT1 as a one shot trip source
//!          The trip event will pull ePWM1A high
//!          The trip event will pull ePWM1B low
//!  - ePWM2 has DCAEVT2 as a cycle by cycle trip source
//!          The trip event will pull ePWM2A high
//!          The trip event will pull ePWM2B low
//!  - ePWM3 reacts to DCAEVT2 and DCBEVT1 events
//!          The DCAEVT2 event will pull ePWM3A high
//!          The DCBEVT1 event will pull ePWM3B low
//!
//! Initially tie TZ1 (GPIO12) and TZ2 (GPIO13) high. During the test, monitor
//! ePWM1 or ePWM2 outputs on a scope pull TZ1 low and leave TZ2 high to create
//! a DCAEVT1, DCAEVT2, DCBEVT1 and DCBEVT2. View the EPWM1A/B, EPWM2A/B, 
//! EPWM3A/B waveforms on an oscilloscope to see the effect of the events.
//! 
//!  \b External \b Connections \n
//!  - EPWM1A is on GPIO0
//!  - EPWM1B is on GPIO1
//!  - EPWM2A is on GPIO2
//!  - EPWM2B is on GPIO3
//!  - EPWM3A is on GPIO4
//!  - EPWM3B is on GPIO5
//!  - TZ1 is on GPIO12
//!  - TZ2 is on GPIO13
//!  - pull TZ1 low and leave TZ2 high to create
//!    a DCAEVT1, DCAEVT2, DCBEVT1 and DCBEVT2.
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
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
// Function Prototypes
//
void InitEPwm1Example(void);
void InitEPwm2Example(void);
void InitEPwm3Example(void);
__interrupt void epwm1_tzint_isr(void);
__interrupt void epwm2_tzint_isr(void);
__interrupt void epwm3_tzint_isr(void);

//
// Globals
//
Uint32  EPwm1TZIntCount;
Uint32  EPwm2TZIntCount;
Uint32  EPwm3TZIntCount;

//
// Main
//
void main(void)
{
    //
    // Step 1. Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    // This example function is found in the F2806x_SysCtrl.c file.
    //
    InitSysCtrl();

    //
    // Step 2. Initalize GPIO:
    // This example function is found in the F2806x_Gpio.c file and
    // illustrates how to set the GPIO to it's default state.
    //
    // InitGpio();  // Skipped for this example

    //
    // For this case just init GPIO pins for ePWM1, ePWM2, and TZ pins
    //
    InitEPwm1Gpio();
    InitEPwm2Gpio();
    InitEPwm3Gpio();
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
    // This function is found in the F2806x_PieCtrl.c file.
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
    // The shell ISR routines are found in F2806x_DefaultIsr.c.
    // This function is found in F2806x_PieVect.c.
    //
    InitPieVectTable();

    //
    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    //
    EALLOW;  // This is needed to write to EALLOW protected registers
    PieVectTable.EPWM1_TZINT = &epwm1_tzint_isr;
    PieVectTable.EPWM2_TZINT = &epwm2_tzint_isr;
    PieVectTable.EPWM3_TZINT = &epwm3_tzint_isr;
    EDIS;    // This is needed to disable write to EALLOW protected registers

    //
    // Step 4. Initialize all the Device Peripherals:
    // This function is found in F2806x_InitPeripherals.c
    //
    // InitPeripherals();  // Not required for this example

    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;
    EDIS;

    InitEPwm1Example();
    InitEPwm2Example();
    InitEPwm3Example();

    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;

    //
    // Step 5. User specific code, enable interrupts
    // Initalize counters:
    //
    EPwm1TZIntCount = 0;
    EPwm2TZIntCount = 0;
    EPwm3TZIntCount = 0;

    //
    // Enable CPU INT3 which is connected to EPWM1-3 INT
    //
    IER |= M_INT2;

    //
    // Enable EPWM INTn in the PIE: Group 2 interrupt 1-3
    //
    PieCtrlRegs.PIEIER2.bit.INTx1 = 1;
    PieCtrlRegs.PIEIER2.bit.INTx2 = 1;
    PieCtrlRegs.PIEIER2.bit.INTx3 = 1;

    //
    // Enable global Interrupts and higher priority real-time debug events
    //
    EINT;   // Enable Global interrupt INTM
    ERTM;   // Enable Global realtime interrupt DBGM

    //
    // Step 6. IDLE loop. Just sit and loop forever (optional)
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

    //
    // Leave these flags set so we only take this interrupt once
    //
    // EALLOW;
    // EPwm1Regs.TZCLR.bit.OST = 1;
    // EPwm1Regs.TZCLR.bit.INT = 1;
    // EDIS;

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
    // Clear the flags - we will continue to take this interrupt until 
    // the TZ pin goes high
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
// epwm3_tzint_isr - 
//
__interrupt void
epwm3_tzint_isr(void)
{
    EPwm3TZIntCount++;

    EALLOW;
    EPwm3Regs.TZCLR.bit.DCAEVT2 = 1;
    EPwm3Regs.TZCLR.bit.DCBEVT1 = 1;
    EPwm3Regs.TZCLR.bit.INT = 1;
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
    EALLOW;
    EPwm1Regs.TBPRD = 6000;                         // Set timer period
    EPwm1Regs.TBPHS.half.TBPHS = 0x0000;            // Phase is 0
    EPwm1Regs.TBCTR = 0x0000;                       // Clear counter

    //
    // Setup TBCLK
    //
    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up/down
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
    EPwm1Regs.AQCTLA.bit.CAU = AQ_SET;            // Set PWM1A on CAU
    EPwm1Regs.AQCTLA.bit.CAD = AQ_CLEAR;          // Clear PWM1A on CAD

    EPwm1Regs.AQCTLB.bit.CAU = AQ_CLEAR;          // Clear PWM1B on CAU
    EPwm1Regs.AQCTLB.bit.CAD = AQ_SET;            // Set PWM1B on CAD

    //
    // Define an event (DCAEVT1) based on TZ1 and TZ2
    //
    EPwm1Regs.DCTRIPSEL.bit.DCAHCOMPSEL = DC_TZ1;        // DCAH = TZ1
    EPwm1Regs.DCTRIPSEL.bit.DCALCOMPSEL = DC_TZ2;        // DCAL = TZ2
    
    //
    // DCAEVT1 =  DCAH low, DCAL high;
    //
    EPwm1Regs.TZDCSEL.bit.DCAEVT1 = TZ_DCAL_HI_DCAH_LOW; 
    
    //
    // DCAEVT1 = DCAEVT1 (not filtered)
    //
    EPwm1Regs.DCACTL.bit.EVT1SRCSEL = DC_EVT1;
    
    EPwm1Regs.DCACTL.bit.EVT1FRCSYNCSEL = DC_EVT_ASYNC;  // Take async path

    //
    // Enable DCAEVT1 as a one-shot trip source
    // Note: DCxEVT1 events can be defined as one-shot.
    //       DCxEVT2 events can be defined as cycle-by-cycle.
    //
    EPwm1Regs.TZSEL.bit.DCAEVT1 = 1;

    //
    // Because DCAEVT1 causes a trip event
    // (in this case one-shot) we need to use the TZA
    // the and TZB actions to force EPWM1A and EPWM1B
    // Note: TZA and TZB have higher priority over the
    //       DCAEVT2 action.
    //
    EPwm1Regs.TZCTL.bit.TZA = TZ_FORCE_HI;           // EPWM1A will go high
    EPwm1Regs.TZCTL.bit.TZB = TZ_FORCE_LO;           // EPWM1B will go low

    // Enable TZ interrupt
    EPwm1Regs.TZEINT.bit.OST = 1;
    EDIS;
}

//
// InitEPwm2Example - 
//
void
InitEPwm2Example()
{
    EPwm2Regs.TBPRD = 6000;                        // Set timer period
    EPwm2Regs.TBPHS.half.TBPHS = 0x0000;           // Phase is 0
    EPwm2Regs.TBCTR = 0x0000;                      // Clear counter

    //
    // Setup TBCLK
    //
    EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
    EPwm2Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
    EPwm2Regs.TBCTL.bit.HSPCLKDIV = TB_DIV4;       // Clock ratio to SYSCLKOUT
    
    //
    // Slow just to observe on the scope
    //
    EPwm2Regs.TBCTL.bit.CLKDIV = TB_DIV4;

    //
    // Setup compare
    //
    EPwm2Regs.CMPA.half.CMPA = 3000;

    //
    // Set actions
    //
    EPwm2Regs.AQCTLA.bit.CAU = AQ_SET;             // Set PWM2A on CAU
    EPwm2Regs.AQCTLA.bit.CAD = AQ_CLEAR;           // Clear PWM2A on CAD

    EPwm2Regs.AQCTLB.bit.CAU = AQ_CLEAR;           // Clear PWM2B on CAU
    EPwm2Regs.AQCTLB.bit.CAD = AQ_SET;             // Set PWM1B on CAD

    EALLOW;
    //
    // Define an event (DCAEVT2) based on TZ1 and TZ2
    //
    EPwm2Regs.DCTRIPSEL.bit.DCAHCOMPSEL = DC_TZ1;        // DCAH = TZ1
    EPwm2Regs.DCTRIPSEL.bit.DCALCOMPSEL = DC_TZ2;        // DCAL = TZ2
    
    //
    // DCAEVT2 =  DCAH low, DCAL high;
    //
    EPwm2Regs.TZDCSEL.bit.DCAEVT2 = TZ_DCAL_HI_DCAH_LOW;
    
    //
    // DCAEVT2 = DCAEVT2 (not filtered)
    //
    EPwm2Regs.DCACTL.bit.EVT2SRCSEL = DC_EVT1;
    
    EPwm2Regs.DCACTL.bit.EVT2FRCSYNCSEL = DC_EVT_ASYNC;  // Take async path

    //
    // Enable DCAEVT2 as a cycle-by-cycle trip source
    // Note: DCxEVT1 events can be defined as one-shot.
    //       DCxEVT2 events can be defined as cycle-by-cycle.
    EPwm2Regs.TZSEL.bit.DCAEVT2 = 1;

    //
    // Because DCAEVT2 is causes a trip event
    // (in this case cycle-by-cycle) we need to use the TZA
    // the and TZB actions to force EPWM2A and EPWM2B
    // NOTE: TZA and TZB have higher priority over the
    //       DCAEVT1 action.
    //
    EPwm2Regs.TZCTL.bit.TZA = TZ_FORCE_HI;           // EPWM2A will go high
    EPwm2Regs.TZCTL.bit.TZB = TZ_FORCE_LO;           // EPWM2B will go low

    //
    // Enable TZ interrupt
    //
    EPwm2Regs.TZEINT.bit.CBC = 1;

    EDIS;
}

//
// InitEPwm3Example - 
//
void
InitEPwm3Example()
{
    EPwm3Regs.TBPRD = 6000;                        // Set timer period
    EPwm3Regs.TBPHS.half.TBPHS = 0x0000;           // Phase is 0
    EPwm3Regs.TBCTR = 0x0000;                      // Clear counter

    //
    // Setup TBCLK
    //
    EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
    EPwm3Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
    EPwm3Regs.TBCTL.bit.HSPCLKDIV = TB_DIV4;       // Clock ratio to SYSCLKOUT
    
    //
    // Slow just to observe on the scope
    //
    EPwm3Regs.TBCTL.bit.CLKDIV = TB_DIV4;

    //
    // Setup compare
    //
    EPwm3Regs.CMPA.half.CMPA = 3000;

    //
    // Set actions
    //
    EPwm3Regs.AQCTLA.bit.CAU = AQ_SET;             // Set PWM3A on CAU
    EPwm3Regs.AQCTLA.bit.CAD = AQ_CLEAR;           // Clear PWM3A on CAD

    EPwm3Regs.AQCTLB.bit.CAU = AQ_CLEAR;           // Clear PWM3B on CAU
    EPwm3Regs.AQCTLB.bit.CAD = AQ_SET;             // Set PWM3B on CAD

    EALLOW;
    
    //
    // Define an event (DCAEVT2) based on TZ1 and TZ2
    //
    EPwm3Regs.DCTRIPSEL.bit.DCAHCOMPSEL = DC_TZ1;        // DCAH = TZ1
    EPwm3Regs.DCTRIPSEL.bit.DCALCOMPSEL = DC_TZ2;        // DCAL = TZ2
    
    //
    // DCAEVT2 =  DCAH low, DCAL high;
    //
    EPwm3Regs.TZDCSEL.bit.DCAEVT2 = TZ_DCAL_HI_DCAH_LOW;
    
    //
    // DCAEVT2 = DCAEVT2 (not filtered)
    //
    EPwm3Regs.DCACTL.bit.EVT2SRCSEL = DC_EVT1;
    
    EPwm3Regs.DCACTL.bit.EVT2FRCSYNCSEL = DC_EVT_ASYNC;  // Take async path

    //
    // Define an event (DCBEVT1) based on TZ1 and TZ2
    //
    EPwm3Regs.DCTRIPSEL.bit.DCBHCOMPSEL = DC_TZ1;        // DCBH = TZ1
    EPwm3Regs.DCTRIPSEL.bit.DCBLCOMPSEL = DC_TZ2;        // DCBL = TZ2
    
    //
    // DCBEVT1 =  DCBH low, DCBL high;
    //
    EPwm3Regs.TZDCSEL.bit.DCBEVT1 = TZ_DCAL_HI_DCAH_LOW;
    
    //
    // DCBEVT1 =  DCBEVT1 (not filtered)
    //
    EPwm3Regs.DCBCTL.bit.EVT1SRCSEL = DC_EVT1;
    
    EPwm3Regs.DCBCTL.bit.EVT1FRCSYNCSEL = DC_EVT_ASYNC;  // Take async path

    //
    // What do we want the event to do?
    // NOTE: The event is *not* defined as a one-shot or
    //       as a cycle-by-cycle trip.  Thus we use the
    //       DCAEVT2 and DCBEVT1 actions.
    //
    EPwm3Regs.TZCTL.bit.DCAEVT2 = TZ_FORCE_HI;           // EPWM3A will go high
    EPwm3Regs.TZCTL.bit.DCBEVT1 = TZ_FORCE_LO;           // EPWM3B will go low

    //
    // Enable TZ interrupt
    //
    EPwm3Regs.TZEINT.bit.DCAEVT2 = 1;
    EDIS;
}

//
// End of File
//

