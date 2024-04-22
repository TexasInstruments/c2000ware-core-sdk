//###########################################################################
//
// FILE:    Example_2805xEPwmTimeZone.c
//
// TITLE:   ePWM Trip Zone Safety example
//
//! \addtogroup f2805x_example_list
//! <h1>ePWM Safety Trip Zone</h1>
//!
//! This example shows how to use ePWM trip zones 4 (EQEP1ERR), 5 (CLOCKFAIL),
//! and 6 (EMUSTOP) to trip the ePWM outputs under certain safety-critical
//! conditions. An emulator stop causes TZ6 to trip ePWM3A low and
//! ePWM3B high. An EQEP phase error (PHE) causes TZ4 to trip ePWM1A and
//! ePWM1B low. A CLOCKFAIL will cause TZ5 to trip ePWM2A and ePWM2B high.
//!
//! The EMUSTOP will be the first trip to occur when the coded breakpoint
//! is reached. You will need to press RUN to continue the simulation.
//! TZ4 will occur next followed by TZ5. The delay between trips may be
//! increased or decreased to make viewing the ePWM outputs easier by
//! modifying the delay function.
//!
//! During the example, monitor ePWM1 ePWM2, and ePWM3 outputs on a scope
//!
//!  \b External \b Connections \n
//!    - EPWM1A is on GPIO0 (One shot)
//!    - EPWM1B is on GPIO1 (One shot)
//!    - EPWM2A is on GPIO2 (One shot)
//!    - EPWM2B is on GPIO3 (One shot)
//!    - EPWM3A is on GPIO4 (Cycle by cycle)
//!    - EPWM3B is on GPIO5 (Cycle by cycle)
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
// Prototype statements for functions found within this file.
//
void InitEPwm1Example(void);
void InitEPwm2Example(void);
void InitEPwm3Example(void);
void InitEPwmExamples(void);
void delay(void);

__interrupt void epwm1_tzint_isr(void);
__interrupt void epwm2_tzint_isr(void);
__interrupt void epwm3_tzint_isr(void);
__interrupt void nmi_isr(void);
__interrupt void eqep1_isr(void);

//
// Global variables used in this example
//
Uint16  EPwm1TZIntCount = 0;
Uint16  EPwm2TZIntCount = 0;
Uint16  EPwm3TZIntCount = 0;
Uint16  NmiIntCount = 0;

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
    // For this case just init GPIO pins for ePWM1, ePWM2, ePWM3
    //
    InitEPwm1Gpio();
    InitEPwm2Gpio();
    InitEPwm3Gpio();

    //
    // Step 3. Clear all __interrupts and initialize PIE vector table:
    // Disable CPU __interrupts
    //
    DINT;

    //
    // Enable CLOCKFAIL and Phase Error __interrupts
    //
    EALLOW;
    SysCtrlRegs.PLLSTS.bit.MCLKOFF = 1;
    NmiIntruptRegs.NMICFG.bit.CLOCKFAIL = 1;
    EQep1Regs.QEINT.bit.QPE = 1;
    EDIS;

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
    PieVectTable.EPWM1_TZINT = &epwm1_tzint_isr;        // TZ1 -- One shot
    PieVectTable.EPWM2_TZINT = &epwm2_tzint_isr;        // TZ2 -- One shot
    PieVectTable.EPWM3_TZINT = &epwm3_tzint_isr;        // TZ3 -- Cycle by cycle
    PieVectTable.NMI = &nmi_isr; // CLOCKFAIL will also force an NMI __interrupt
                                // if CLOCKFAIL __interrupt enabled.
    PieVectTable.EQEP1_INT = &eqep1_isr;
    EDIS;    // This is needed to disable write to EALLOW protected registers

    //
    // Step 4. Initialize all the Device Peripherals:
    // Not required for this example
    //
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;
    EDIS;

    InitEPwmExamples();

    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;

    //
    // Step 5. User specific code, enable __interrupts
    // Initialize counters:
    //
    // Enable CPU INT2 and INT5 which is connected to
    // EPWM1-3 INT and EQEP
    //
    IER |= M_INT2;
    IER |= M_INT5;

    //
    // Enable EPWM INTn in the PIE: Group 2 __interrupt 1-3
    //
    PieCtrlRegs.PIEIER2.bit.INTx1 = 1;
    PieCtrlRegs.PIEIER2.bit.INTx2 = 1;
    PieCtrlRegs.PIEIER2.bit.INTx3 = 1;

    //
    // Enable EQEP INT1 in the PIE:    Group 5 __interrupt
    //
    PieCtrlRegs.PIEIER5.bit.INTx1 = 1;

    //
    // Enable global Interrupts and higher priority real-time debug events:
    //
    EINT;   // Enable Global __interrupt INTM
    ERTM;   // Enable Global realtime __interrupt DBGM

    delay();    // Delay loop - Observe EPWMs!

    asm("    ESTOP0");            // TRIP TZ6 (EPWM3) - EMULATION PAUSED!
                                // Observe ePWM3 outputs and
                                // continue run to generate more trips.
                                // EPWM3A should be held low and EPWM3B
                                // should be held high.  The waveform
                                // should resume operation once the
                                // program is continued.
    EALLOW;

    delay(); // Delay loop - Observe EPWMs!

    EQep1Regs.QFRC.bit.PHE = 1;    // TRIP TZ4 (EPWM1)
                                // Both EPWM1A and EPWM1B should be held low.
                                // These waveforms should hold these values
                                // from this point on.

    delay(); // Delay loop - Observe EPWMs!

    NmiIntruptRegs.NMIFLGFRC.bit.CLOCKFAIL = 1;    // TRIP TZ5 (EPWM2)
                                // Both EPWM2A and EPWB2B should be held high.
                                // These waveforms should hold these values
                                // from this point on.
    EDIS;

    delay(); // Delay loop - Observe EPWMs!

    asm("    ESTOP0");    // Example Complete! (TZ6 also tripped again)
                        // Continue run to view PWM outputs on oscilloscope

    for(;;);

    //
    // PWMs configured as cycle by cycle trips will be running at this point
    //
}

__interrupt void epwm1_tzint_isr(void)    // EQEP1ERR
{
    //
    // This ISR is reached when an inverted EQEP1ERR
    // occurs.  The inverted EQEP1ERR signal is generated
    // by a phase error (PHE) in the EQEP module.  No
    // other EQEP error signals will cause a trip.
    //
    // Increment counter
    //
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

__interrupt void epwm2_tzint_isr(void)    // CLOCKFAIL
{
    //
    // This ISR is reached when a CLOCKFAIL signal
    // is generated.  The NMI ISR will execute
    // prior to this ISR if the CLOCKFAIL __interrupt
    // is enabled.  However, the trip will occur immediately.
    //
    // Increment counter
    //
    EPwm2TZIntCount++;

    //
    // Leave these flags set so we only take this
    // __interrupt once
    //
    // EALLOW;
    // EPwm2Regs.TZCLR.bit.OST = 1;
    // EPwm2Regs.TZCLR.bit.INT = 1;
    // EDIS;

    //
    // Acknowledge this __interrupt to receive more __interrupts from group 2
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;
}

__interrupt void epwm3_tzint_isr(void)    // EMUSTOP
{
    //
    // This ISR will be reached whenever the
    // emulation is halted.  The trip will occur
    // immediately upon the software reaching a
    // breakpoint or being paused, and this ISR
    // will execute when the software is resumed.
    //
    // Increment counter
    //
    EPwm3TZIntCount++;

    //
    // Clear these flags so we can receive the __interrupt again
    //
    EALLOW;
    EPwm3Regs.TZCLR.bit.CBC = 1;
    EPwm3Regs.TZCLR.bit.INT = 1;
    EDIS;

    //
    // Acknowledge this __interrupt to receive more __interrupts from group 2
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;
}

void nmi_isr()
{
    //
    // Increment counter
    //
    NmiIntCount++;

    //
    // For this example we will just clear the flags.
    // Ordinarily, an alternative clocking source should
    // be selected or other corrective action should be taken.
    //
    EALLOW;
    NmiIntruptRegs.NMIFLGCLR.bit.CLOCKFAIL = 1;  // Clear CLOCKFAIL __interrupt flag
                                                // must be cleared before NMI __interrupt flag
    NmiIntruptRegs.NMIFLGCLR.bit.NMIINT = 1;        // Clear NMI __interrupt flag
    EDIS;
}

void eqep1_isr()
{
    //
    // This ISR will execute after the trip zone
    // ISR associated with the inverted EQEP1ERR
    // has completed.
    //
    // Handle EQEP error here.  For this example
    // we will just clear error flags.
    //
    EQep1Regs.QCLR.bit.PHE = 1;
    EQep1Regs.QCLR.bit.INT = 1;

    //
    // Acknowledge this __interrupt to receive more __interrupts from group 5
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;
}

void delay()
{
    Uint32 i = 0;
    for(i = 0; i < 30000000; i++)
    {
        asm("    NOP");
    }
}

void InitEPwm1Example()
{
    //
    // Enable TZ4 as a one shot trip source
    //
    EALLOW;
    EPwm1Regs.TZSEL.bit.OSHT4 = 1;

    //
    // What do we want the TZ4 (EQEP1ERR) to do?
    //
    EPwm1Regs.TZCTL.bit.TZA = TZ_FORCE_LO;
    EPwm1Regs.TZCTL.bit.TZB = TZ_FORCE_LO;

    //
    // Enable TZ __interrupt
    //
    EPwm1Regs.TZEINT.bit.OST = 1;
    EDIS;

    EPwm1Regs.TBPRD = 12000;                        // Set timer period
    EPwm1Regs.TBPHS.half.TBPHS = 0x0000;            // Phase is 0
    EPwm1Regs.TBCTR = 0x0000;                       // Clear counter

    //
    // Setup TBCLK
    //
    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;      // Count up
    EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;             // Disable phase loading
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV4;            // Clock ratio to SYSCLKOUT
    EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV4;

    EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;         // Load registers every ZERO
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
    EPwm1Regs.AQCTLA.bit.CAU = AQ_SET;                 // Set PWM1A on Zero
    EPwm1Regs.AQCTLA.bit.CAD = AQ_CLEAR;


    EPwm1Regs.AQCTLB.bit.CAU = AQ_CLEAR;              // Set PWM1A on Zero
    EPwm1Regs.AQCTLB.bit.CAD = AQ_SET;
}

void InitEPwm2Example()
{
    //
    // Enable TZ5 as a one shot trip source
    //
    EALLOW;
    EPwm2Regs.TZSEL.bit.OSHT5 = 1;

    //
    // What do we want TZ5 (CLOCKFAIL) to do
    //
    EPwm2Regs.TZCTL.bit.TZA = TZ_FORCE_HI;
    EPwm2Regs.TZCTL.bit.TZB = TZ_FORCE_HI;

    //
    // Enable TZ __interrupt
    //
    EPwm2Regs.TZEINT.bit.OST = 1;
    EDIS;

    EPwm2Regs.TBPRD = 6000;                             // Set timer period
    EPwm2Regs.TBPHS.half.TBPHS = 0x0000;               // Phase is 0
    EPwm2Regs.TBCTR = 0x0000;                          // Clear counter

    //
    // Setup TBCLK
    //
    EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;     // Count up
    EPwm2Regs.TBCTL.bit.PHSEN = TB_DISABLE;            // Disable phase loading
    EPwm2Regs.TBCTL.bit.HSPCLKDIV = TB_DIV4;           // Clock ratio to SYSCLKOUT
    EPwm2Regs.TBCTL.bit.CLKDIV = TB_DIV4;

    EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;        // Load registers every ZERO
    EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

    //
    // Setup compare
    //
    EPwm2Regs.CMPA.half.CMPA = 3000;

    //
    // Set actions
    //
    EPwm2Regs.AQCTLA.bit.CAU = AQ_SET;                 // Set PWM1A on Zero
    EPwm2Regs.AQCTLA.bit.CAD = AQ_CLEAR;

    EPwm2Regs.AQCTLB.bit.CAU = AQ_CLEAR;              // Set PWM1A on Zero
    EPwm2Regs.AQCTLB.bit.CAD = AQ_SET;
}

void InitEPwm3Example()
{
    //
    // Enable TZ6 (EMUSTOP) as cycle by cycle trip source
    //
    EALLOW;
    EPwm3Regs.TZSEL.bit.CBC6 = 1;

    //
    // What do we want TZ6 to do?
    //
    EPwm3Regs.TZCTL.bit.TZA = TZ_FORCE_LO;
    EPwm3Regs.TZCTL.bit.TZB = TZ_FORCE_HI;

    //
    // Enable TZ __interrupt
    //
    EPwm3Regs.TZEINT.bit.CBC = 1;
    EDIS;

    EPwm3Regs.TBPRD = 9000;                             // Set timer period
    EPwm3Regs.TBPHS.half.TBPHS = 0x0000;                // Phase is 0
    EPwm3Regs.TBCTR = 0x0000;                           // Clear counter

    //
    // Setup TBCLK
    //
    EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;     // Count up
    EPwm3Regs.TBCTL.bit.PHSEN = TB_DISABLE;            // Disable phase loading
    EPwm3Regs.TBCTL.bit.HSPCLKDIV = TB_DIV4;           // Clock ratio to SYSCLKOUT
    EPwm3Regs.TBCTL.bit.CLKDIV = TB_DIV4;

    EPwm3Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;        // Load registers every ZERO
    EPwm3Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm3Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm3Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

    //
    // Setup compare
    //
    EPwm3Regs.CMPA.half.CMPA = 3000;

    //
    // Set actions
    //
    EPwm3Regs.AQCTLA.bit.CAU = AQ_SET;                 // Set PWM1A on Zero
    EPwm3Regs.AQCTLA.bit.CAD = AQ_CLEAR;

    EPwm3Regs.AQCTLB.bit.CAU = AQ_CLEAR;              // Set PWM1A on Zero
    EPwm3Regs.AQCTLB.bit.CAD = AQ_SET;
}

void InitEPwmExamples()
{
    InitEPwm1Example();
    InitEPwm2Example();
    InitEPwm3Example();
}


//
// End of file.
//
