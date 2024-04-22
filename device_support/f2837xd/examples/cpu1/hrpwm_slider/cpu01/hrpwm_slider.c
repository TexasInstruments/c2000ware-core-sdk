//###########################################################################
//
// FILE:    hrpwm_slider.c
//
// TITLE:   F2837xD Device HRPWM MEP Slider example
//
//
//! \addtogroup cpu01_example_list
//! <h1> HRPWM Slider Test (hrpwm_slider)</h1>
//!
//! This example modifies the MEP control registers to show edge displacement
//! due to HRPWM control blocks of the respective EPwm module channel A and B
//! will have fine edge movement due to HRPWM logic. Load the
//! F2837xD_HRPWM_slider.gel file. Select the HRPWM_eval from the GEL menu.
//! A FineDuty slider graphics will show up in CCS. Load the program and run.
//! Use the Slider to and observe the EPwm edge displacement for each slider
//! step change. This explains the MEP control on the EPwmxA channels.
//!
//! Monitor ePWM1-ePWM8 A/B pins on an oscilloscope.
//!
//
//###########################################################################
//
// $Release Date:  $
// $Copyright:
// Copyright (C) 2013-2024 Texas Instruments Incorporated - http://www.ti.com/
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
// Defines
//
#define PWM_CH          9             // # of PWM channels

//
// Globals
//
Uint16 i,j,duty,DutyFine,n,update;
Uint32 temp;
volatile Uint16 EPwmTZIntCount[9],Test_flag1,ph_dly;   // 0,18 are extra
volatile struct EPWM_REGS *ePWM[10];                   // vars for flags

//
// Function Prototypes
//
void HRPWM1_Config(int);
void HRPWM2_Config(int);
void HRPWM3_Config(int);
void HRPWM4_Config(int);
void HRPWM5_Config(int);
void HRPWM6_Config(int);
void HRPWM7_Config(int);
void HRPWM8_Config(int);

//
// Main
//
void main(void)
{
   EALLOW;
//
// Step 1. Initialize System Control for Control and Analog Subsystems
// Enable Peripheral Clocks
// This example function is found in the F2837xD_SysCtrl.c file.
//
    InitSysCtrl();
    EDIS;

    InitEPwmGpio();                   // EPWM1A and EPWM1B through all PWMS

    ePWM[1] = &EPwm1Regs;             // PWM Address Map
    ePWM[2] = &EPwm2Regs;             // PWM Address Map
    ePWM[3] = &EPwm3Regs;             // PWM Address Map
    ePWM[4] = &EPwm4Regs;             // PWM Address Map
    ePWM[5] = &EPwm5Regs;             // PWM Address Map
    ePWM[6] = &EPwm6Regs;             // PWM Address Map
    ePWM[7] = &EPwm7Regs;             // PWM Address Map
    ePWM[8] = &EPwm8Regs;             // PWM Address Map
    ePWM[9] = &EPwm9Regs;             // PWM Address Map

    InitEPwmGpio();                   // EPWM1A and EPWM1B -

    DINT; // Disable CPU interrupts

//
// Initialize PIE control registers to their default state.
// The default state is all PIE interrupts disabled and flags
// are cleared.
//

//
// This function is found in the F2837xD_PieCtrl.c file.
//
    InitPieCtrl();

//
// Disable CPU interrupts and clear all CPU interrupt flags:
//
    EALLOW;
    IER = 0x0000;
    IFR = 0x0000;

//
// Initialize the PIE vector table with pointers to the shell Interrupt
// Service Routines (ISR).
// This will populate the entire table, even if the interrupt
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
 // EDIS;   // This is needed to disable write to EALLOW protected registers

//
// Enable interrupts required for this example
//
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;   // Enable the PIE block
    IER = 0x400;                         // Enable CPU INT

//
// Interrupts that are used in this example are re-mapped to
// ISR functions found within this file.
// Interrupts that are used in this example are re-mapped to
// ISR functions found within this file.
//

//
// Step 5. User specific code, enable interrupts:
//
    update =1;
    DutyFine =0;

    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;
    EDIS;

//
// EPwm and HRPWM register initialization
//
    HRPWM1_Config(30);         // EPwm1 target, Period = 10
    HRPWM2_Config(20);         // EPwm2 target, Period = 20
    HRPWM3_Config(20);         // EPwm3 target, Period = 10
    HRPWM4_Config(20);         // EPwm4 target, Period = 20
    HRPWM5_Config(20);         // EPwm1 target, Period = 10
    HRPWM6_Config(20);         // EPwm2 target, Period = 20
    HRPWM7_Config(20);         // EPwm3 target, Period = 10
    HRPWM8_Config(20);         // EPwm4 target, Period = 20

    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;

    while(update == 1)
    {
        //
        // Example, write to the HRPWM extension of CMPA / CMPB
        //
        EPwm1Regs.CMPA.bit.CMPAHR = DutyFine << 8;
        EPwm1Regs.CMPB.all = DutyFine << 8;
        EPwm2Regs.CMPA.bit.CMPAHR = DutyFine << 8;
        EPwm2Regs.CMPB.all = DutyFine << 8;

        //
        // Example, 32-bit write to CMPA:CMPAHR
        //
        EPwm3Regs.CMPA.all = ((Uint32)EPwm3Regs.CMPA.bit.CMPA << 16) +
                             (DutyFine << 8);
        EPwm3Regs.CMPB.all = DutyFine << 8;
        EPwm4Regs.CMPB.all = (DutyFine << 8);
        EPwm4Regs.CMPA.bit.CMPAHR = (DutyFine << 8);

        //
        // Example, write to the HRPWM extension of CMPA / CMPB
        //
        EPwm5Regs.CMPA.bit.CMPAHR = DutyFine << 8;
        EPwm5Regs.CMPB.all = DutyFine << 8;
        EPwm6Regs.CMPA.bit.CMPAHR = DutyFine << 8;
        EPwm6Regs.CMPB.all = DutyFine << 8;

        //
        // Example, write to the HRPWM extension of CMPA / CMPB
        //
        EPwm7Regs.CMPA.bit.CMPAHR = DutyFine << 8;
        EPwm7Regs.CMPB.all = DutyFine << 8;
        EPwm8Regs.CMPA.bit.CMPAHR = DutyFine << 8;
        EPwm8Regs.CMPB.all = DutyFine << 8;
    }

//
// Enable global Interrupts and higher priority real-time debug events:
//
    EINT;   // Enable Global interrupt INTM
    ERTM;   // Enable Global realtime interrupt DBGM

    for(;;); // Step 6. IDLE loop. Just sit and loop forever (optional):
}

//
// HRPWM1_Config - Configure HRPWM1 settings
//
void HRPWM1_Config(period)
{
    //
    // ePWM1 register configuration with HRPWM
    // ePWM  toggle high/low with MEP control on 1A AND 1B
    //
    EPwm1Regs.TBCTL.bit.PRDLD = TB_IMMEDIATE;    // set Immediate load
    EPwm1Regs.TBPRD = period - 1;                // PWM frequency = 1 / period
    EPwm1Regs.CMPB.bit.CMPB = period/2;          // set duty 50% initial
    EPwm1Regs.CMPB.all |= (1 << 8);              // initialize HRPWM extension
    EPwm1Regs.CMPA.bit.CMPA = period / 2;        // set duty 50% initially
    EPwm1Regs.CMPA.bit.CMPAHR = (1 << 8);
    EPwm1Regs.TBPHS.all = 0;
    EPwm1Regs.TBCTR = 0;

    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;
    EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;
    EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
    EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
    EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;

    EPwm1Regs.AQCTLA.bit.ZRO = AQ_SET;
    EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR;
    EPwm1Regs.AQCTLB.bit.ZRO = AQ_SET;
    EPwm1Regs.AQCTLB.bit.CBU = AQ_CLEAR;

    EALLOW;
    EPwm1Regs.HRCNFG.all = 0x0;
    EPwm1Regs.HRCNFG.bit.EDGMODE = HR_FEP;
    EPwm1Regs.HRCNFG.bit.CTLMODE = HR_CMP;
    EPwm1Regs.HRCNFG.bit.HRLOAD  = HR_CTR_ZERO;

    EPwm1Regs.HRCNFG.bit.EDGMODEB = HR_FEP;
    EPwm1Regs.HRCNFG.bit.CTLMODEB = HR_CMP;
    EPwm1Regs.HRCNFG.bit.HRLOADB  = HR_CTR_ZERO;
    EDIS;
}

//
// HRPWM2_Config - Configure HRPWM2 settings
//
void HRPWM2_Config(period)
{
    //
    // ePWM2 register configuration with HRPWM
    // ePWM  toggle high/low with MEP control on 2A AND 2B
    //
    EPwm2Regs.TBCTL.bit.PRDLD = TB_IMMEDIATE;     // set Immediate load
    EPwm2Regs.TBPRD = period - 1;                 // PWM frequency = 1 / period
    EPwm2Regs.CMPB.bit.CMPB = period/2;           // set duty 50% initial
    EPwm2Regs.CMPB.all |= (1 << 8);               // initialize HRPWM extension
    EPwm2Regs.CMPA.bit.CMPA = period / 2;         // set duty 50% initially
    EPwm2Regs.CMPA.bit.CMPAHR = (1 << 8);
    EPwm2Regs.TBPHS.all = 0;
    EPwm2Regs.TBCTR = 0;

    EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;
    EPwm2Regs.TBCTL.bit.PHSEN = TB_DISABLE;
    EPwm2Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
    EPwm2Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
    EPwm2Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
    EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;

    EPwm2Regs.AQCTLA.bit.ZRO = AQ_SET;
    EPwm2Regs.AQCTLA.bit.CAU = AQ_CLEAR;
    EPwm2Regs.AQCTLB.bit.ZRO = AQ_SET;
    EPwm2Regs.AQCTLB.bit.CBU = AQ_CLEAR;

    EALLOW;
    EPwm2Regs.HRCNFG.all = 0x0;
    EPwm2Regs.HRCNFG.bit.EDGMODE = HR_FEP;
    EPwm2Regs.HRCNFG.bit.CTLMODE = HR_CMP;
    EPwm2Regs.HRCNFG.bit.HRLOAD  = HR_CTR_ZERO;

    EPwm2Regs.HRCNFG.bit.EDGMODEB = HR_FEP;
    EPwm2Regs.HRCNFG.bit.CTLMODEB = HR_CMP;
    EPwm2Regs.HRCNFG.bit.HRLOADB  = HR_CTR_ZERO;
    EDIS;
}

//
// HRPWM3_Config - Configure HRPWM3 settings
//
void HRPWM3_Config(period)
{
    //
    // ePWM3 register configuration with HRPWM
    // ePWM3A / 3B  toggle high/low with MEP control on falling edge
    //
    EPwm3Regs.TBCTL.bit.PRDLD = TB_IMMEDIATE;     // set Immediate load
    EPwm3Regs.TBPRD = period - 1;                 // PWM frequency = 1 / period
    EPwm3Regs.CMPB.bit.CMPB = period/2;           // set duty 50% initial
    EPwm3Regs.CMPB.all |= (1 << 8);               // initialize HRPWM extension
    EPwm3Regs.CMPA.bit.CMPA = period / 2;         // set duty 50% initially
    EPwm3Regs.CMPA.bit.CMPAHR = (1 << 8);
    EPwm3Regs.TBPHS.all = 0;
    EPwm3Regs.TBCTR = 0;

    EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;
    EPwm3Regs.TBCTL.bit.PHSEN = TB_DISABLE;
    EPwm3Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
    EPwm3Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
    EPwm3Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    EPwm3Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm3Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
    EPwm3Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm3Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;

    EPwm3Regs.AQCTLA.bit.ZRO = AQ_SET;
    EPwm3Regs.AQCTLA.bit.CAU = AQ_CLEAR;
    EPwm3Regs.AQCTLB.bit.ZRO = AQ_SET;
    EPwm3Regs.AQCTLB.bit.CBU = AQ_CLEAR;

    EALLOW;
    EPwm3Regs.HRCNFG.all = 0x0;
    EPwm3Regs.HRCNFG.bit.EDGMODE = HR_FEP;
    EPwm3Regs.HRCNFG.bit.CTLMODE = HR_CMP;
    EPwm3Regs.HRCNFG.bit.HRLOAD  = HR_CTR_ZERO;

    EPwm3Regs.HRCNFG.bit.EDGMODEB = HR_FEP;
    EPwm3Regs.HRCNFG.bit.CTLMODEB = HR_CMP;
    EPwm3Regs.HRCNFG.bit.HRLOADB  = HR_CTR_ZERO;
    EDIS;
}

//
// HRPWM4_Config - Configure HRPWM4 settings
//
void HRPWM4_Config(period)
{
    //
    // ePWM4 register configuration with HRPWM
    // ePWM4A  / 4B toggle high/low with MEP control on falling edge
    //
    EPwm4Regs.TBCTL.bit.PRDLD = TB_IMMEDIATE;    // set Immediate load
    EPwm4Regs.TBPRD = period - 1;                // PWM frequency = 1 / period
    EPwm4Regs.CMPB.bit.CMPB = period/2;          // set duty 50% initial
    EPwm4Regs.CMPB.all |= (1 << 8);              // initialize HRPWM extension
    EPwm4Regs.CMPA.bit.CMPA = period / 2;        // set duty 50% initially
    EPwm4Regs.CMPA.bit.CMPAHR = (1 << 8);
    EPwm4Regs.TBPHS.all = 0;
    EPwm4Regs.TBCTR = 0;

    EPwm4Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;
    EPwm4Regs.TBCTL.bit.PHSEN = TB_DISABLE;
    EPwm4Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
    EPwm4Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
    EPwm4Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    EPwm4Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm4Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
    EPwm4Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm4Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;

    EPwm4Regs.AQCTLA.bit.ZRO = AQ_SET;
    EPwm4Regs.AQCTLA.bit.CAU = AQ_CLEAR;
    EPwm4Regs.AQCTLB.bit.ZRO = AQ_SET;
    EPwm4Regs.AQCTLB.bit.CBU = AQ_CLEAR;

    EALLOW;
    EPwm4Regs.HRCNFG.all = 0x0;
    EPwm4Regs.HRCNFG.bit.EDGMODE = HR_FEP;
    EPwm4Regs.HRCNFG.bit.CTLMODE = HR_CMP;
    EPwm4Regs.HRCNFG.bit.HRLOAD  = HR_CTR_ZERO;

    EPwm4Regs.HRCNFG.bit.EDGMODEB = HR_FEP;
    EPwm4Regs.HRCNFG.bit.CTLMODEB = HR_CMP;
    EPwm4Regs.HRCNFG.bit.HRLOADB  = HR_CTR_ZERO;
    EDIS;
}

//
// HRPWM5_Config - Configure HRPWM5 settings
//
void HRPWM5_Config(period)
{
    //
    // ePWM5 register configuration with HRPWM
    // ePWM5A / 5B toggle high/low with MEP control on falling edge
    //
    EPwm5Regs.TBCTL.bit.PRDLD = TB_IMMEDIATE;     // set Immediate load
    EPwm5Regs.TBPRD = period - 1;                 // PWM frequency = 1 / period
    EPwm5Regs.CMPB.bit.CMPB = period/2;           // set duty 50% initial
    EPwm5Regs.CMPB.all |= (1 << 8);               // initialize HRPWM extension
    EPwm5Regs.CMPA.bit.CMPA = period / 2;         // set duty 50% initially
    EPwm5Regs.CMPA.bit.CMPAHR = (1 << 8);
    EPwm5Regs.TBPHS.all = 0;
    EPwm5Regs.TBCTR = 0;

    EPwm5Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;
    EPwm5Regs.TBCTL.bit.PHSEN = TB_DISABLE;
    EPwm5Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
    EPwm5Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
    EPwm5Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    EPwm5Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm5Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
    EPwm5Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm5Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;

    EPwm5Regs.AQCTLA.bit.ZRO = AQ_SET;
    EPwm5Regs.AQCTLA.bit.CAU = AQ_CLEAR;
    EPwm5Regs.AQCTLB.bit.ZRO = AQ_SET;
    EPwm5Regs.AQCTLB.bit.CBU = AQ_CLEAR;

    EALLOW;
    EPwm5Regs.HRCNFG.all = 0x0;
    EPwm5Regs.HRCNFG.bit.EDGMODE = HR_FEP;
    EPwm5Regs.HRCNFG.bit.CTLMODE = HR_CMP;
    EPwm5Regs.HRCNFG.bit.HRLOAD  = HR_CTR_ZERO;

    EPwm5Regs.HRCNFG.bit.EDGMODEB = HR_FEP;
    EPwm5Regs.HRCNFG.bit.CTLMODEB = HR_CMP;
    EPwm5Regs.HRCNFG.bit.HRLOADB  = HR_CTR_ZERO;
    EDIS;
}

//
// HRPWM6_Config - Configure HRPWM6 settings
//
void HRPWM6_Config(period)
{
    //
    // ePWM6 register configuration with HRPWM
    // ePWM6A / 6B toggle high/low with MEP control on falling edge
    //
    EPwm6Regs.TBCTL.bit.PRDLD = TB_IMMEDIATE;     // set Immediate load
    EPwm6Regs.TBPRD = period - 1;                 // PWM frequency = 1 / period
    EPwm6Regs.CMPB.bit.CMPB = period/2;           // set duty 50% initial
    EPwm6Regs.CMPB.all |= (1 << 8);               // initialize HRPWM extension
    EPwm6Regs.CMPA.bit.CMPA = period / 2;         // set duty 50% initially
    EPwm6Regs.CMPA.bit.CMPAHR = (1 << 8);
    EPwm6Regs.TBPHS.all = 0;
    EPwm6Regs.TBCTR = 0;

    EPwm6Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;
    EPwm6Regs.TBCTL.bit.PHSEN = TB_DISABLE;
    EPwm6Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
    EPwm6Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
    EPwm6Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    EPwm6Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm6Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
    EPwm6Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm6Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;

    EPwm6Regs.AQCTLA.bit.ZRO = AQ_SET;
    EPwm6Regs.AQCTLA.bit.CAU = AQ_CLEAR;
    EPwm6Regs.AQCTLB.bit.ZRO = AQ_SET;
    EPwm6Regs.AQCTLB.bit.CBU = AQ_CLEAR;

    EALLOW;
    EPwm6Regs.HRCNFG.all = 0x0;
    EPwm6Regs.HRCNFG.bit.EDGMODE = HR_FEP;
    EPwm6Regs.HRCNFG.bit.CTLMODE = HR_CMP;
    EPwm6Regs.HRCNFG.bit.HRLOAD  = HR_CTR_ZERO;

    EPwm6Regs.HRCNFG.bit.EDGMODEB = HR_FEP;
    EPwm6Regs.HRCNFG.bit.CTLMODEB = HR_CMP;
    EPwm6Regs.HRCNFG.bit.HRLOADB  = HR_CTR_ZERO;
    EDIS;
}

//
// HRPWM7_Config - Configure HRPWM7 settings
//
void HRPWM7_Config(period)
{
    //
    // ePWM7 register configuration with HRPWM
    // ePWM7A 7B  toggle high/low with MEP control on falling edge
    //
    EPwm7Regs.TBCTL.bit.PRDLD = TB_IMMEDIATE;     // set Immediate load
    EPwm7Regs.TBPRD = period - 1;                 // PWM frequency = 1 / period
    EPwm7Regs.CMPB.bit.CMPB = period/2;           // set duty 50% initial
    EPwm7Regs.CMPB.all |= (1 << 8);               // initialize HRPWM extension
    EPwm7Regs.CMPA.bit.CMPA = period / 2;         // set duty 50% initially
    EPwm7Regs.CMPA.bit.CMPAHR = (1 << 8);
    EPwm7Regs.TBPHS.all = 0;
    EPwm7Regs.TBCTR = 0;

    EPwm7Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;
    EPwm7Regs.TBCTL.bit.PHSEN = TB_DISABLE;
    EPwm7Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
    EPwm7Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
    EPwm7Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    EPwm7Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm7Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
    EPwm7Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm7Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;

    EPwm7Regs.AQCTLA.bit.ZRO = AQ_SET;
    EPwm7Regs.AQCTLA.bit.CAU = AQ_CLEAR;
    EPwm7Regs.AQCTLB.bit.ZRO = AQ_SET;
    EPwm7Regs.AQCTLB.bit.CBU = AQ_CLEAR;

    EALLOW;
    EPwm7Regs.HRCNFG.all = 0x0;
    EPwm7Regs.HRCNFG.bit.EDGMODE = HR_FEP;
    EPwm7Regs.HRCNFG.bit.CTLMODE = HR_CMP;
    EPwm7Regs.HRCNFG.bit.HRLOAD  = HR_CTR_ZERO;

    EPwm7Regs.HRCNFG.bit.EDGMODEB = HR_FEP;
    EPwm7Regs.HRCNFG.bit.CTLMODEB = HR_CMP;
    EPwm7Regs.HRCNFG.bit.HRLOADB  = HR_CTR_ZERO;
    EDIS;
}

//
// HRPWM8_Config - Configure HRPWM8 settings
//
void HRPWM8_Config(period)
{
    //
    // ePWM8 register configuration with HRPWM
    // ePWM8A 8B toggle high/low with MEP control on falling edge
    //
    EPwm8Regs.TBCTL.bit.PRDLD = TB_IMMEDIATE;     // set Immediate load
    EPwm8Regs.TBPRD = period - 1;                 // PWM frequency = 1 / period
    EPwm8Regs.CMPB.bit.CMPB = period/2;           // set duty 50% initial
    EPwm8Regs.CMPB.all |= (1 << 8);               // initialize HRPWM extension
    EPwm8Regs.CMPA.bit.CMPA = period / 2;         // set duty 50% initially
    EPwm8Regs.CMPA.bit.CMPAHR = (1 << 8);
    EPwm8Regs.TBPHS.all = 0;
    EPwm8Regs.TBCTR = 0;

    EPwm8Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;
    EPwm8Regs.TBCTL.bit.PHSEN = TB_DISABLE;
    EPwm8Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
    EPwm8Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
    EPwm8Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    EPwm8Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    EPwm8Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
    EPwm8Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm8Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;

    EPwm8Regs.AQCTLA.bit.ZRO = AQ_SET;
    EPwm8Regs.AQCTLA.bit.CAU = AQ_CLEAR;
    EPwm8Regs.AQCTLB.bit.ZRO = AQ_SET;
    EPwm8Regs.AQCTLB.bit.CBU = AQ_CLEAR;

    EALLOW;
    EPwm8Regs.HRCNFG.all = 0x0;
    EPwm8Regs.HRCNFG.bit.EDGMODE = HR_FEP;
    EPwm8Regs.HRCNFG.bit.CTLMODE = HR_CMP;
    EPwm8Regs.HRCNFG.bit.HRLOAD  = HR_CTR_ZERO;

    EPwm8Regs.HRCNFG.bit.EDGMODEB = HR_FEP;
    EPwm8Regs.HRCNFG.bit.CTLMODEB = HR_CMP;
    EPwm8Regs.HRCNFG.bit.HRLOADB  = HR_CTR_ZERO;
    EDIS;
}

//
// End of file
//
