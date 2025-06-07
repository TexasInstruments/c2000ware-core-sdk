//###########################################################################
//
// FILE:    Example_2803xEPwmDCEventTripComp.c
//
// TITLE:   ePWM DC Event Trip Comparator example
//
//! \addtogroup f2803x_example_list
//! <h1>ePWM DC Event Trip Comparator (epwm_dcevent_trip_comp)</h1>
//!
//! In this example ePWM1 is configured for PWM Digital Compare Event
//! Trip using Comparator1A and comparator1B pin inputs.
//! DCAEVT1, DCBEVT1 events are triggered by increasing the voltage on
//! COMP1B pin to be higher than that of COMP1A pin.
//! In this example:
//!    - ePWM1 has DCAEVT1 and DCBEVT1 as one shot trip sources.
//!            DCAEVT1 will pull EPWM1A high.
//!            DCBEVT1 will pull EPWM1B low.
//!
//! Initially make the voltage level at COMP1A to be higher than that of 
//! COMP1B. Increase voltage on inverting side of comparator(COMP1B pin) to 
//! trigger a DCAEVT1, and DCBEVT1. ePWM1 will react to DCAEVT1 and DCBEVT1 as 
//! a 1 shot trip. View the EPWM1A/B waveforms on an oscilloscope to see the
//! effect of the events.
//!
//! \b External \b Connections \n
//!  - EPWM1A is on GPIO0
//!  - EPWM1B is on GPIO1
//!  - COMP1A is on ADCA2
//!  - COMP1B is on ADCB2
//!  - pull COMP1B to a higher voltage level than COMP1A.
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
__interrupt void epwm1_tzint_isr(void);

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
    EDIS;    // This is needed to disable write to EALLOW protected registers

    //
    // Step 4. Initialize all the Device Peripherals:
    // Not required for this example
    //
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1;        // Enable Clock to the ADC
    
    //
    // Comparator shares the internal BG reference of the ADC, 
    // must be powered even if ADC is unused
    //
    AdcRegs.ADCCTL1.bit.ADCBGPWD = 1;            
    
    DELAY_US(1000L);             // Delay to allow BG reference to settle.

    //
    // Enable clock to the Comparator 1 block
    //
    SysCtrlRegs.PCLKCR3.bit.COMP1ENCLK = 1;
    
    Comp1Regs.COMPCTL.bit.COMPDACEN = 1;     // Power up Comparator 1 locally
    
    //
    // Connect the inverting input to pin COMP1B
    //
    Comp1Regs.COMPCTL.bit.COMPSOURCE = 1; 
    
    //
    // Uncomment following 2 lines to use DAC instead of pin COMP1B
    //
    // Connect the inverting input to the internal DAC
    //
    //Comp1Regs.COMPCTL.bit.COMPSOURCE = 0;   
    //Comp1Regs.DACVAL.bit.DACVAL = 512;		// Set DAC output to midpoint
    //
        
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;
    EDIS;

    InitEPwm1Example();

    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;

    //
    // Step 5. User specific code, enable interrupts
    // Initialize counters:
    //
    EPwm1TZIntCount = 0;

    //
    // Enable CPU INT3 which is connected to EPWM1-3 INT:
    //
    IER |= M_INT2;

    //
    // Enable EPWM INTn in the PIE: Group 2 interrupt 1-3
    //
    PieCtrlRegs.PIEIER2.bit.INTx1 = 1;

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
// epwm1_tzint_isr - EPwm1 TZ Interrupt
//
__interrupt void 
epwm1_tzint_isr(void)
{
    EPwm1TZIntCount++;

    //
    // Leave these flags set so we only take this
    // interrupt once
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

void InitEPwm1Example()
{
    EALLOW;
    EPwm1Regs.TBPRD = 6000;                         // Set timer period
    EPwm1Regs.TBPHS.half.TBPHS = 0x0000;            // Phase is 0
    EPwm1Regs.TBCTR = 0x0000;

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
    
    //
    // DCAH = Comparator 1 output
    //
    EPwm1Regs.DCTRIPSEL.bit.DCAHCOMPSEL = DC_COMP1OUT;
    
    EPwm1Regs.DCTRIPSEL.bit.DCALCOMPSEL = DC_TZ2;         // DCAL = TZ2
    
    //
    // DCAEVT1 =  DCAH low (will become active as Comparator output goes low)
    //
    EPwm1Regs.TZDCSEL.bit.DCAEVT1 = TZ_DCAH_LOW;
    
    //
    // DCAEVT1 = DCAEVT1 (not filtered)
    //
    EPwm1Regs.DCACTL.bit.EVT1SRCSEL = DC_EVT1;
    
    EPwm1Regs.DCACTL.bit.EVT1FRCSYNCSEL = DC_EVT_ASYNC;   // Take async path

    //
    // Define an event (DCBEVT1) based on TZ1 and TZ2
    //
    
    //
    // DCBH = Comparator 1 output
    //
    EPwm1Regs.DCTRIPSEL.bit.DCBHCOMPSEL = DC_COMP1OUT;
    
    EPwm1Regs.DCTRIPSEL.bit.DCBLCOMPSEL = DC_TZ2;         // DCAL = TZ2
    
    //
    // DCBEVT1 =  (will become active as Comparator output goes low)
    //
    EPwm1Regs.TZDCSEL.bit.DCBEVT1 = TZ_DCBH_LOW;
    
    //
    // DCBEVT1 = DCBEVT1 (not filtered)
    //    
    EPwm1Regs.DCBCTL.bit.EVT1SRCSEL = DC_EVT1;
    
    EPwm1Regs.DCBCTL.bit.EVT1FRCSYNCSEL = DC_EVT_ASYNC;   // Take async path

    //
    // Enable DCAEVT1 and DCBEVT1 are one shot trip sources
    // Note: DCxEVT1 events can be defined as one-shot.
    //       DCxEVT2 events can be defined as cycle-by-cycle.
    //
    EPwm1Regs.TZSEL.bit.DCAEVT1 = 1;
    EPwm1Regs.TZSEL.bit.DCBEVT1 = 1;

    //
    // What do we want the DCAEVT1 and DCBEVT1 events to do?
    // DCAEVTx events can force EPWMxA
    // DCBEVTx events can force EPWMxB
    //
    EPwm1Regs.TZCTL.bit.TZA = TZ_FORCE_HI;           // EPWM1A will go high
    EPwm1Regs.TZCTL.bit.TZB = TZ_FORCE_LO;           // EPWM1B will go low

    //
    // Enable TZ interrupt
    //
    EPwm1Regs.TZEINT.bit.OST = 1;
    EDIS;
}

//
// End of File
//

