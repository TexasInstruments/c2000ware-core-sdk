//###########################################################################
//
// FILE:    epwm_ex4_deadband_c28.c
//
// TITLE:   Check PWM Dead-Band
//
//! \addtogroup cpu01_example_list
//! <h1> EPWM dead band control (epwm_deadband)</h1>
//!
//! During the test, monitor ePWM1, ePWM2, and/or ePWM3 outputs
//! on a scope.
//!
//! - ePWM1A is on GPIO0
//! - ePWM1B is on GPIO1
//! - ePWM2A is on GPIO2
//! - ePWM2B is on GPIO3
//! - ePWM3A is on GPIO4
//! - ePWM3B is on GPIO5
//!
//! This example configures ePWM1, ePWM2 and ePWM3 for:
//! - Count up/down
//! - Deadband
//!
//! 3 Examples are included:
//! - ePWM1: Active low PWMs
//! - ePWM2: Active low complementary PWMs
//! - ePWM3: Active high complementary PWMs
//!
//! Each ePWM is configured to interrupt on the 3rd zero event.
//! When this happens the deadband is modified such that
//! 0 <= DB <= DB_MAX.  That is, the deadband will move up and
//! down between 0 and the maximum value.
//!
//! View the EPWM1A/B, EPWM2A/B and EPWM3A/B waveforms
//! via an oscilloscope
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
#define EPWM1_MAX_DB   0x03FF
#define EPWM2_MAX_DB   0x03FF
#define EPWM3_MAX_DB   0x03FF
#define EPWM1_MIN_DB   0
#define EPWM2_MIN_DB   0
#define EPWM3_MIN_DB   0
#define DB_UP          1
#define DB_DOWN        0

//
// Globals
//
Uint32 EPwm1TimerIntCount;
Uint32 EPwm2TimerIntCount;
Uint32 EPwm3TimerIntCount;
Uint16 EPwm1_DB_Direction;
Uint16 EPwm2_DB_Direction;
Uint16 EPwm3_DB_Direction;

//
// Function Prototypes
//
void InitEPwm1Example(void);
void InitEPwm2Example(void);
void InitEPwm3Example(void);
__interrupt void epwm1_isr(void);
__interrupt void epwm2_isr(void);
__interrupt void epwm3_isr(void);

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
// This example function is found in the f2838x_gpio.c file and
// illustrates how to set the GPIO to its default state.
//
//    InitGpio();

//
// enable PWM1, PWM2 and PWM3
//
    CpuSysRegs.PCLKCR2.bit.EPWM1=1;
    CpuSysRegs.PCLKCR2.bit.EPWM2=1;
    CpuSysRegs.PCLKCR2.bit.EPWM3=1;

//
// For this case just init GPIO pins for ePWM1, ePWM2, ePWM3
// These functions are in the f2838x_epwm.c file
//
    InitEPwm1Gpio();
    InitEPwm2Gpio();
    InitEPwm3Gpio();

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
    PieVectTable.EPWM1_INT = &epwm1_isr;
    PieVectTable.EPWM2_INT = &epwm2_isr;
    PieVectTable.EPWM3_INT = &epwm3_isr;
    EDIS;   // This is needed to disable write to EALLOW protected registers

//
// Step 4. Initialize the Device Peripherals:
//
    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC =0;
    EDIS;

    InitEPwm1Example();
    InitEPwm2Example();
    InitEPwm3Example();

    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC =1;
    EDIS;

//
// Step 5. User specific code, enable interrupts:
// Initialize counters:
//
    EPwm1TimerIntCount = 0;
    EPwm2TimerIntCount = 0;
    EPwm3TimerIntCount = 0;

//
// Enable CPU INT3 which is connected to EPWM1-3 INT:
//
    IER |= M_INT3;

//
// Enable EPWM INTn in the PIE: Group 3 interrupt 1-3
//
    PieCtrlRegs.PIEIER3.bit.INTx1 = 1;
    PieCtrlRegs.PIEIER3.bit.INTx2 = 1;
    PieCtrlRegs.PIEIER3.bit.INTx3 = 1;

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
        asm ("          NOP");
    }
}

//
// epwm1_isr - EPWM1 ISR
//
__interrupt void epwm1_isr(void)
{
    if(EPwm1_DB_Direction == DB_UP)
    {
        if(EPwm1Regs.DBFED.bit.DBFED < EPWM1_MAX_DB)
        {
            EPwm1Regs.DBFED.bit.DBFED++;
            EPwm1Regs.DBRED.bit.DBRED++;
        }
        else
        {
            EPwm1_DB_Direction = DB_DOWN;
            EPwm1Regs.DBFED.bit.DBFED--;
            EPwm1Regs.DBRED.bit.DBRED--;
        }
    }
    else
    {
        if(EPwm1Regs.DBFED.bit.DBFED == EPWM1_MIN_DB)
        {
            EPwm1_DB_Direction = DB_UP;
            EPwm1Regs.DBFED.bit.DBFED++;
            EPwm1Regs.DBRED.bit.DBRED++;
        }
        else
        {
            EPwm1Regs.DBFED.bit.DBFED--;
            EPwm1Regs.DBRED.bit.DBRED--;
        }
    }
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
// epwm2_isr - EPWM2 ISR
//
__interrupt void epwm2_isr(void)
{
    if(EPwm2_DB_Direction == DB_UP)
    {
        if(EPwm2Regs.DBFED.bit.DBFED < EPWM2_MAX_DB)
        {
            EPwm2Regs.DBFED.bit.DBFED++;
            EPwm2Regs.DBRED.bit.DBRED++;
        }
        else
        {
            EPwm2_DB_Direction = DB_DOWN;
            EPwm2Regs.DBFED.bit.DBFED--;
            EPwm2Regs.DBRED.bit.DBRED--;
        }
    }
    else
    {
        if(EPwm2Regs.DBFED.bit.DBFED == EPWM2_MIN_DB)
        {
            EPwm2_DB_Direction = DB_UP;
            EPwm2Regs.DBFED.bit.DBFED++;
            EPwm2Regs.DBRED.bit.DBRED++;
        }
        else
        {
            EPwm2Regs.DBFED.bit.DBFED--;
            EPwm2Regs.DBRED.bit.DBRED--;
        }
    }

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
// epwm3_isr - EPWM3 ISR
//
__interrupt void epwm3_isr(void)
{
    if(EPwm3_DB_Direction == DB_UP)
    {
        if(EPwm3Regs.DBFED.bit.DBFED < EPWM3_MAX_DB)
        {
            EPwm3Regs.DBFED.bit.DBFED++;
            EPwm3Regs.DBRED.bit.DBRED++;
        }
        else
        {
            EPwm3_DB_Direction = DB_DOWN;
            EPwm3Regs.DBFED.bit.DBFED--;
            EPwm3Regs.DBRED.bit.DBRED--;
        }
    }
    else
    {
        if(EPwm3Regs.DBFED.bit.DBFED == EPWM3_MIN_DB)
        {
            EPwm3_DB_Direction = DB_UP;
            EPwm3Regs.DBFED.bit.DBFED++;
            EPwm3Regs.DBRED.bit.DBRED++;
        }
        else
        {
            EPwm3Regs.DBFED.bit.DBFED--;
            EPwm3Regs.DBRED.bit.DBRED--;
        }
    }

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
// InitEPwm1Example - Initialize EPWM1 configuration
//
void InitEPwm1Example()
{
    EPwm1Regs.TBPRD = 6000;                       // Set timer period
    EPwm1Regs.TBPHS.bit.TBPHS = 0x0000;           // Phase is 0
    EPwm1Regs.TBCTR = 0x0000;                     // Clear counter

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
    EPwm1Regs.CMPA.bit.CMPA = 3000;

    //
    // Set actions
    //
    EPwm1Regs.AQCTLA.bit.CAU = AQ_SET;            // Set PWM1A on Zero
    EPwm1Regs.AQCTLA.bit.CAD = AQ_CLEAR;

    EPwm1Regs.AQCTLB.bit.CAU = AQ_CLEAR;          // Set PWM1A on Zero
    EPwm1Regs.AQCTLB.bit.CAD = AQ_SET;

    //
    // Active Low PWMs - Setup Deadband
    //
    EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
    EPwm1Regs.DBCTL.bit.POLSEL = DB_ACTV_LO;
    EPwm1Regs.DBCTL.bit.IN_MODE = DBA_ALL;
    EPwm1Regs.DBRED.bit.DBRED = EPWM1_MIN_DB;
    EPwm1Regs.DBFED.bit.DBFED = EPWM1_MIN_DB;
    EPwm1_DB_Direction = DB_UP;

    //
    // Interrupt where we will change the Deadband
    //
    EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;    // Select INT on Zero event
    EPwm1Regs.ETSEL.bit.INTEN = 1;               // Enable INT
    EPwm1Regs.ETPS.bit.INTPRD = ET_3RD;          // Generate INT on 3rd event
}

//
// InitEPwm2Example - Initialize EPWM2 configuration
//
void InitEPwm2Example()
{
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
                                                   // the scope

    //
    // Setup compare
    //
    EPwm2Regs.CMPA.bit.CMPA = 3000;

    //
    // Set actions
    //
    EPwm2Regs.AQCTLA.bit.CAU = AQ_SET;            // Set PWM2A on Zero
    EPwm2Regs.AQCTLA.bit.CAD = AQ_CLEAR;

    EPwm2Regs.AQCTLB.bit.CAU = AQ_CLEAR;          // Set PWM2A on Zero
    EPwm2Regs.AQCTLB.bit.CAD = AQ_SET;

    //
    // Active Low complementary PWMs - setup the deadband
    //
    EPwm2Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
    EPwm2Regs.DBCTL.bit.POLSEL = DB_ACTV_LOC;
    EPwm2Regs.DBCTL.bit.IN_MODE = DBA_ALL;
    EPwm2Regs.DBRED.bit.DBRED = EPWM2_MIN_DB;
    EPwm2Regs.DBFED.bit.DBFED = EPWM2_MIN_DB;
    EPwm2_DB_Direction = DB_UP;

    //
    // Interrupt where we will modify the deadband
    //
    EPwm2Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // Select INT on Zero event
    EPwm2Regs.ETSEL.bit.INTEN = 1;                // Enable INT
    EPwm2Regs.ETPS.bit.INTPRD = ET_3RD;           // Generate INT on 3rd event
}

//
// InitEPwm3Example - Initialize EPWM3 configuration
//
void InitEPwm3Example()
{
    EPwm3Regs.TBPRD = 6000;                        // Set timer period
    EPwm3Regs.TBPHS.bit.TBPHS = 0x0000;            // Phase is 0
    EPwm3Regs.TBCTR = 0x0000;                      // Clear counter

    //
    // Setup TBCLK
    //
    EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up
    EPwm3Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
    EPwm3Regs.TBCTL.bit.HSPCLKDIV = TB_DIV4;       // Clock ratio to SYSCLKOUT
    EPwm3Regs.TBCTL.bit.CLKDIV = TB_DIV4;          // Slow so we can observe on
                                                   // the scope

    //
    // Setup compare
    //
    EPwm3Regs.CMPA.bit.CMPA = 3000;

    //
    // Set actions
    //
    EPwm3Regs.AQCTLA.bit.CAU = AQ_SET;             // Set PWM3A on Zero
    EPwm3Regs.AQCTLA.bit.CAD = AQ_CLEAR;

    EPwm3Regs.AQCTLB.bit.CAU = AQ_CLEAR;           // Set PWM3A on Zero
    EPwm3Regs.AQCTLB.bit.CAD = AQ_SET;

    //
    // Active high complementary PWMs - Setup the deadband
    //
    EPwm3Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
    EPwm3Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;
    EPwm3Regs.DBCTL.bit.IN_MODE = DBA_ALL;
    EPwm3Regs.DBRED.bit.DBRED = EPWM3_MIN_DB;
    EPwm3Regs.DBFED.bit.DBFED = EPWM3_MIN_DB;
    EPwm3_DB_Direction = DB_UP;

    //
    // Interrupt where we will change the deadband
    //
    EPwm3Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;      // Select INT on Zero event
    EPwm3Regs.ETSEL.bit.INTEN = 1;                 // Enable INT
    EPwm3Regs.ETPS.bit.INTPRD = ET_3RD;            // Generate INT on 3rd event
}

//
// End of file
//
