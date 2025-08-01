//#############################################################################
//
// FILE:   mcpwm_ex3_deadband.c
//
// TITLE:  MCPWM Basic PWM generation With DeadBand
//
//! \addtogroup driver_example_list
//! <h1>MCPWM Basic PWM generation With DeadBand</h1>
//!
//! This example configures myMCPWM0 and myMCPWM1 as follows
//!     myMCPWM0 (MCPWM1)
//!         Time Base Configurations 
//!             In Up Down Count Mode for 4000 TBCLKs or 20KHz Frequency for TBCLK of 160MHz
//!         Action Qualifier is configurations
//!             Output A1 : Set High on Counter matches CMPA counting up, set low on CMPA match counting down
//!             Output A2 : Set High on Counter matches CMPA counting up, set low on CMPA match counting down
//!             Output A3 : Set High on Counter matches CMPA counting up, set low on CMPA match counting down
//!         DeadBand
//!             Active High Configuration is selected with 100 TBCLK deadband
//!     
//!     myMCPWM1 (MCPWM3)
//!         Time Base Configurations 
//!             In Up Down Count Mode for 4000 TBCLKs or 20KHz Frequency for TBCLK of 160MHz
//!         Action Qualifier is configurations
//!             Output A1 : Set High on Counter matches CMPA counting up, set low on CMPA match counting down
//!         DeadBand
//!             Disabled Configurations
//!
//!
//!  \b External \b Connections \n
//!     Monitor the MCPWM pins for the waveforms.
//!         Observe J4 40 - GPIO0  - myMCPWM0 Output A1 - Active High Configuration
//!         Observe J4 39 - GPIO1  - myMCPWM0 Output B1 - Active High Configuration
//!         Observe J4 38 - GPIO2  - myMCPWM0 Output A2 - Active High Configuration
//!         Observe J4 37 - GPIO3  - myMCPWM0 Output B2 - Active High Configuration
//!         Observe J4 36 - GPIO4  - myMCPWM0 Output A3 - Active High Configuration
//!         Observe J4 35 - GPIO5  - myMCPWM0 Output B3 - Active High Configuration
//!         Observe J4 7  - GPIO12 - myMCPWM1 Output A1 - Can be used for reference
//
//
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2025 Texas Instruments Incorporated - http://www.ti.com/
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
//#############################################################################

//
// Included Files
//
#include "f28x_project.h"

//
// Function Prototypes
//
void initMyMCPWM0(void);
void initMyMCPWM1(void);

void main(void)
{
    //
    // Step 1. Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    // This example function is found in the f2838x_sysctrl.c file.
    //
    InitSysCtrl();

    //
    // For this case just init GPIO pins for mcpwm1, mcpwm3
    // These functions are in the f2838x_mcpwm.c file
    //
    InitGpio();
    InitMcpwm1Gpio();
    InitMcpwm3Gpio();

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
    //
    InitPieVectTable();

    //
    // Disable sync(Freeze clock to PWM as well)
    //
    CpuSysRegs.PERCLKCR.bit.TBCLKSYNC = 0;

    //
    // Initialize MCPWM modules
    //
    initMyMCPWM0();
    initMyMCPWM1();

    //
    // Enable global interrupts and real-time debug
    //
    EINT;
    ERTM;

    //
    // Enable sync clock
    //
    CpuSysRegs.PERCLKCR.bit.TBCLKSYNC = 1;

    //
    // IDLE loop
    //
    while(1)
    {
        asm ("  NOP");
    }
}

//
// initMyMCPWM0 - Initialize MCPWM1 module for deadband example
//
void initMyMCPWM0(void)
{
    //
    // Time Base Control
    //
    Pwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;   // Up-down count mode
    Pwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;           // TBCLK = SYSCLKOUT / 1
    Pwm1Regs.TBCTL.bit.FREE_SOFT = EMULATION_FREE_RUN; // Free run in emulation

    //
    // Set Period for 20kHz switching frequency (TBCLK = 160MHz)
    // Period = 160MHz/(2*20kHz) = 4000 counts for Up-Down count mode
    //
    Pwm1Regs.TBPRDS.bit.TBPRDS = 4000;             // Set timer period

    //
    // Set Compare values for all channels (50% duty cycle)
    //
    Pwm1Regs.PWM1_CMPAS.bit.PWM1_CMPAS = 2000;    // Set compare A value
    Pwm1Regs.PWM2_CMPAS.bit.PWM2_CMPAS = 2000;    // Set compare A value
    Pwm1Regs.PWM3_CMPAS.bit.PWM3_CMPAS = 2000;    // Set compare A value

    //
    // Setup Action Qualifier for all channels
    //
    Pwm1Regs.PWM1_AQCTLAS.bit.CAU = AQ_SET;       // Set high on CMPA up
    Pwm1Regs.PWM1_AQCTLAS.bit.CAD = AQ_CLEAR;     // Set low on CMPA down

    Pwm1Regs.PWM2_AQCTLAS.bit.CAU = AQ_SET;       // Set high on CMPA up
    Pwm1Regs.PWM2_AQCTLAS.bit.CAD = AQ_CLEAR;     // Set low on CMPA down

    Pwm1Regs.PWM3_AQCTLAS.bit.CAU = AQ_SET;       // Set high on CMPA up
    Pwm1Regs.PWM3_AQCTLAS.bit.CAD = AQ_CLEAR;     // Set low on CMPA down

    //
    // Dead-Band Configuration
    //
    Pwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;   // Enable Dead-band module
    Pwm1Regs.DBCTL.bit.POLSEL = DB_ACTV_HI;         // Active high
    Pwm1Regs.DBCTL.bit.IN_MODE = DBA_ALL;           // Use PWMxA as source

    //
    // Set Dead-Band Delays
    //
    Pwm1Regs.DBREDS.bit.DBREDS = 100;              // Rising edge delay
    Pwm1Regs.DBFEDS.bit.DBFEDS = 100;              // Falling edge delay
}

//
// initMyMCPWM1 - Initialize MCPWM3 module for deadband example
//
void initMyMCPWM1(void)
{
    //
    // Time Base Control
    //
    Pwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;   // Up-down count mode
    Pwm3Regs.TBCTL.bit.CLKDIV = TB_DIV1;           // TBCLK = SYSCLKOUT / 1
    Pwm3Regs.TBCTL.bit.FREE_SOFT = EMULATION_FREE_RUN; // Free run in emulation

    //
    // Set Period for 20kHz switching frequency
    // Period = 160MHz/(2*20kHz) = 4000 counts for Up-Down count mode
    //
    Pwm3Regs.TBPRDS.bit.TBPRDS = 4000;             // Set timer period

    //
    // Set Compare values for PWM1 (50% duty cycle)
    //
    Pwm3Regs.PWM1_CMPAS.bit.PWM1_CMPAS = 2000;    // Set compare A value

    //
    // Setup Action Qualifier for PWM1
    //
    Pwm3Regs.PWM1_AQCTLAS.bit.CAU = AQ_SET;       // Set high on CMPA up
    Pwm3Regs.PWM1_AQCTLAS.bit.CAD = AQ_CLEAR;     // Set low on CMPA down

    //
    // Disable Dead-Band for MCPWM1
    //
    Pwm3Regs.DBCTL.bit.OUT_MODE = DB_DISABLE;      // Disable Dead-band module
}
