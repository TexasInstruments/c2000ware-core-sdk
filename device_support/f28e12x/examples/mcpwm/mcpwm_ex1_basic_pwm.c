//#############################################################################
//
// FILE:   mcpwm_ex1_basic_pwm.c
//
// TITLE:  MCPWM Basic PWM generation and updates Example
//
//! \addtogroup driver_example_list
//! <h1>MCPWM Basic PWM Generation and Updates</h1>
//!
//! This example configures myMCPWM0 and myMCPWM1 as follows
//!     myMCPWM0 (MCPWM1)
//!         Time Base Configurations 
//!             In Up Count Mode for 10KHz Frequency PWM
//!         Action Qualifier is configurations
//!             Output A1 : Set High on Counter matches zero, set low on CMPA match
//!             Output B1 : Set High on Counter matches zero, set low on CMPB match
//!             Output A2 : Set High on Counter matches CMPA, set low on Period match
//!             Output B2 : Set High on Counter matches CMPB, set low on Period match
//!             Output A3 : Set High on Counter matches CMPA, set low on CMPB match
//!             Output B3 : Set Low on Counter  matches CMPA, set high on CMPB match
//!         Interrupt
//!             For Updating the CMPx Values runtime, Interrupt is configured in synchronous 
//!             with the PWM Counter. 
//!             ET1 is configured to fire at every 5 events of Counter = Period.
//!             ET1 is selected as source for the interrupt generation
//!     
//!     myMCPWM1 (MCPWM3)
//!         Time Base Configurations 
//!             In Up Down Count Mode for 10KHz Frequency PWM
//!         Action Qualifier is configurations
//!             Output A1 : 
//!                 Set High on Counter matches CMPA while counting up, 
//!                 Set low on CMPA match while Counting down
//!             Output B1 : 
//!                 Set High on Counter matches CMPB while counting up, 
//!                 Set low on CMPB match while Counting down
//!         Interrupt
//!             For Updating the CMPx Values runtime, Interrupt is configured in synchronous 
//!             with the PWM Counter. 
//!             ET1 is configured to fire at every 5 events of Counter = Period.
//!             ET1 is selected as source for the interrupt generation
//!
//!
//!  \b External \b Connections \n
//!     monitor the mcpwm pins for the waveforms TODO.
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

#include "f28x_project.h"

//
// Globals
//
uint16_t gMcpwm0Period;
uint16_t gMcpwm1Period;

uint16_t gMcpwm0CmpA;
uint16_t gMcpwm0CmpB;
uint16_t gMcpwm1CmpA;
uint16_t gMcpwm1CmpB;

//
// Macros
//
#define APP_CMPA_MIN_PERCENT_PERIOD (10.0f)
#define APP_CMPA_MAX_PERCENT_PERIOD (50.0f)
#define APP_CMPB_MIN_PERCENT_PERIOD (50.0f)
#define APP_CMPB_MAX_PERCENT_PERIOD (90.0f)
#define APP_CMP_UPDATE_STEP_PERCENT_PERIOD (5.0f)

//
// Function Prototypes
//
__interrupt void INT_myMCPWM0_ISR(void);
__interrupt void INT_myMCPWM1_ISR(void);
void initMyMCPWM0(void);
void initMyMCPWM1(void);
void registerMcpwmInterrupts(void);


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
    // This will populate the entire table, even if the interrupt
    // is not used in this example.  This is useful for debug purposes.
    // The shell ISR routines are found in f2838x_defaultisr.c.
    // This function is found in f2838x_pievect.c.
    //
    InitPieVectTable();


    // Disable sync while configuring PWMs
    CpuSysRegs.PERCLKCR.bit.TBCLKSYNC = 0;

    registerMcpwmInterrupts();
    
    // Initialize MCPWM modules
    initMyMCPWM0();
    initMyMCPWM1();

    // Clear any pending interrupts
    EALLOW;
    Pwm1Regs.INTCLR.bit.ET1 = 1;
    Pwm1Regs.INTCLR.bit.INT = 1;

    Pwm3Regs.INTCLR.bit.ET1 = 1;
    Pwm3Regs.INTCLR.bit.INT = 1;
    EDIS;

    IER |= M_INT2;
    IER |= M_INT3;

    // Enable MCPWM interrupts
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;          // Enable the PIE block
    PieCtrlRegs.PIEIER2.bit.INTx4 = 1;          // mcpwm1 group 2, int 4
    PieCtrlRegs.PIEIER3.bit.INTx2 = 1;          // mcpwm3 group 3, int 2

    // Enable global interrupts and real-time debug
    EINT;
    ERTM;

    // Enable sync clock
    CpuSysRegs.PERCLKCR.bit.TBCLKSYNC = 1;

    // IDLE loop
    while(1)
    {
        asm ("  NOP");
    }
}

// Initialize interrupts for MCPWM modules
// - Registers ISR handlers for MCPWM0 and MCPWM1
// - Initially disables both interrupts
void registerMcpwmInterrupts(void)
{
    // Get the PIE Vector Table
    EALLOW;
    
    // Register MCPWM0 interrupt handler
    PieVectTable.MCPWM1_INT = &INT_myMCPWM0_ISR;
    
    // Register MCPWM1 interrupt handler
    PieVectTable.MCPWM3_INT = &INT_myMCPWM1_ISR;
    
    EDIS;

    // Ensure interrupts are initially disabled
    IER &= ~(1 << M_INT2);  // Disable MCPWM0 interrupt group
    IER &= ~(1 << M_INT3);  // Disable MCPWM1 interrupt group
}


void initMyMCPWM0(void)
{
    // Time Base Control configuration
    Pwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;          
    Pwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;              
    Pwm1Regs.TBCTL.bit.PRDLD = TB_SHADOW_LOAD_DISABLE; 
    Pwm1Regs.TBCTL.bit.SYNCOSEL = SYNC_OUT_DISABLED;  
    Pwm1Regs.TBCTL.bit.FREE_SOFT = EMULATION_FREE_RUN; 

    // Counter Compare Control
    Pwm1Regs.CMPCTL.bit.PWM1_LOADAMODE = CC_LD_DISABLE;
    Pwm1Regs.CMPCTL.bit.PWM1_LOADBMODE = CC_LD_DISABLE;
    Pwm1Regs.CMPCTL.bit.PWM2_LOADAMODE = CC_LD_DISABLE;
    Pwm1Regs.CMPCTL.bit.PWM2_LOADBMODE = CC_LD_DISABLE;
    Pwm1Regs.CMPCTL.bit.PWM3_LOADAMODE = CC_LD_DISABLE;
    Pwm1Regs.CMPCTL.bit.PWM3_LOADBMODE = CC_LD_DISABLE;
    Pwm1Regs.CMPCTL.bit.LOADCMODE = CC_LD_DISABLE;
    Pwm1Regs.CMPCTL.bit.LOADDMODE = CC_LD_DISABLE;

    // Action Qualifier Control
    Pwm1Regs.AQCTL.bit.PWM1_LDAQAMODE = AQ_LD_DISABLE;         
    Pwm1Regs.AQCTL.bit.PWM1_LDAQBMODE = AQ_LD_DISABLE;
    Pwm1Regs.AQCTL.bit.PWM2_LDAQAMODE = AQ_LD_DISABLE;         
    Pwm1Regs.AQCTL.bit.PWM2_LDAQBMODE = AQ_LD_DISABLE;
    Pwm1Regs.AQCTL.bit.PWM3_LDAQAMODE = AQ_LD_DISABLE;         
    Pwm1Regs.AQCTL.bit.PWM3_LDAQBMODE = AQ_LD_DISABLE;         


    // Set period for 10kHz
    Pwm1Regs.TBPRD.bit.TBPRD = 15999;

    // Configure PWM1 Action Qualifier outputs
    Pwm1Regs.PWM1_AQCTLA.bit.ZRO = AQ_SET;         
    Pwm1Regs.PWM1_AQCTLA.bit.CAU = AQ_CLEAR;       

    Pwm1Regs.PWM1_AQCTLB.bit.ZRO = AQ_SET;         
    Pwm1Regs.PWM1_AQCTLB.bit.CBU = AQ_CLEAR;       

    // Configure PWM2 Action Qualifier outputs
    Pwm1Regs.PWM2_AQCTLA.bit.PRD = AQ_CLEAR;       
    Pwm1Regs.PWM2_AQCTLA.bit.CAU = AQ_SET;         

    Pwm1Regs.PWM2_AQCTLB.bit.PRD = AQ_CLEAR;       
    Pwm1Regs.PWM2_AQCTLB.bit.CBU = AQ_SET;         

    // Configure PWM3 Action Qualifier outputs
    Pwm1Regs.PWM3_AQCTLA.bit.CAU = AQ_SET;         
    Pwm1Regs.PWM3_AQCTLA.bit.CBU = AQ_CLEAR;       

    Pwm1Regs.PWM3_AQCTLB.bit.CAU = AQ_CLEAR;       
    Pwm1Regs.PWM3_AQCTLB.bit.CBU = AQ_SET;         

    // Configure Event Trigger
    Pwm1Regs.ETSEL.bit.ET1_SEL = EVT_TBCTR_PERIOD; 
    Pwm1Regs.ETPERIOD.bit.ET1_PERIOD = 5;          

    // Enable ET1 interrupt
    EALLOW;
    Pwm1Regs.INTEN.bit.ET1 = INT_ENABLE;
    EDIS;

    //
    // Acknowledge this interrupt to receive more interrupts from group 2
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;

}

void initMyMCPWM1(void)
{
    // Time Base Control configuration
    Pwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;      // Up-down count mode
    Pwm3Regs.TBCTL.bit.CLKDIV = TB_DIV1;            // No clock division
    Pwm3Regs.TBCTL.bit.PRDLD = TB_SHADOW_LOAD_DISABLE;
    Pwm3Regs.TBCTL.bit.SYNCOSEL = SYNC_OUT_DISABLED;
    Pwm3Regs.TBCTL.bit.FREE_SOFT = EMULATION_FREE_RUN;

    // Counter Compare Control
    Pwm3Regs.CMPCTL.bit.PWM1_LOADAMODE = CC_LD_DISABLE;
    Pwm3Regs.CMPCTL.bit.PWM1_LOADBMODE = CC_LD_DISABLE;
    Pwm3Regs.CMPCTL.bit.LOADCMODE = CC_LD_DISABLE;
    Pwm3Regs.CMPCTL.bit.LOADDMODE = CC_LD_DISABLE;

    // Action Qualifier Control
    Pwm3Regs.AQCTL.bit.PWM1_LDAQAMODE = AQ_LD_DISABLE;         
    Pwm3Regs.AQCTL.bit.PWM1_LDAQBMODE = AQ_LD_DISABLE;

    // Set period for 10kHz in Up-Down mode
    Pwm3Regs.TBPRD.bit.TBPRD = 8000;

    // Configure PWM1 Action Qualifier outputs
    Pwm3Regs.PWM1_AQCTLA.bit.CAU = AQ_SET;          // Set high when counter equals CMPA up
    Pwm3Regs.PWM1_AQCTLA.bit.CAD = AQ_CLEAR;        // Set low when counter equals CMPA down

    Pwm3Regs.PWM1_AQCTLB.bit.CBU = AQ_SET;          // Set high when counter equals CMPB up
    Pwm3Regs.PWM1_AQCTLB.bit.CBD = AQ_CLEAR;        // Set low when counter equals CMPB down

    // Configure Event Trigger
    Pwm3Regs.ETSEL.bit.ET1_SEL = EVT_TBCTR_PERIOD;
    Pwm3Regs.ETPERIOD.bit.ET1_PERIOD = 5;

    // Enable ET1 interrupt
    EALLOW;
    Pwm3Regs.INTEN.bit.ET1 = INT_ENABLE;
    EDIS;
}

// Interrupt handler for MCPWM0 ET1 events
// Updates compare values for all PWM channels:
// - CMPA: Cycles between 10% to 50% of period
// - CMPB: Cycles between 50% to 90% of period
// - Update step size of 5% of period
// Note: Called every 5 period events (via ET1 prescaler)
__interrupt void INT_myMCPWM0_ISR(void)
{
    static uint16_t gMcpwm0CmpA = 7999;  // 50% initial duty
    static uint16_t gMcpwm0CmpB = 7999;  // 50% initial duty
    
    uint16_t minCmpA = (uint16_t)((APP_CMPA_MIN_PERCENT_PERIOD * 15999)/100.0f);
    uint16_t maxCmpA = (uint16_t)((APP_CMPA_MAX_PERCENT_PERIOD * 15999)/100.0f);
    uint16_t minCmpB = (uint16_t)((APP_CMPB_MIN_PERCENT_PERIOD * 15999)/100.0f);
    uint16_t maxCmpB = (uint16_t)((APP_CMPB_MAX_PERCENT_PERIOD * 15999)/100.0f);
    uint16_t stepSize = (uint16_t)((APP_CMP_UPDATE_STEP_PERCENT_PERIOD * 15999)/100.0f);

    // Update compare values
    gMcpwm0CmpA += stepSize;
    gMcpwm0CmpB += stepSize;

    // Check limits and wrap around
    if(gMcpwm0CmpA > maxCmpA) {
        gMcpwm0CmpA = minCmpA;
    }
    if(gMcpwm0CmpB > maxCmpB) {
        gMcpwm0CmpB = minCmpB;
    }

    // Update PWM1 compare values
    Pwm1Regs.PWM1_CMPA.bit.PWM1_CMPA = gMcpwm0CmpA;
    Pwm1Regs.PWM1_CMPB.bit.PWM1_CMPB = gMcpwm0CmpB;

    // Update PWM2 compare values
    Pwm1Regs.PWM2_CMPA.bit.PWM2_CMPA = gMcpwm0CmpA;
    Pwm1Regs.PWM2_CMPB.bit.PWM2_CMPB = gMcpwm0CmpB;

    // Update PWM3 compare values
    Pwm1Regs.PWM3_CMPA.bit.PWM3_CMPA = gMcpwm0CmpA;
    Pwm1Regs.PWM3_CMPB.bit.PWM3_CMPB = gMcpwm0CmpB;

    // Clear interrupt flags
    EALLOW;
    Pwm1Regs.INTCLR.bit.ET1 = 1;
    Pwm1Regs.INTCLR.bit.INT = 1;
    EDIS;
    //
    // Acknowledge this interrupt to receive more interrupts from group 2
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;
    // IER &= ~(1 << M_INT2);
}

// Interrupt handler for MCPWM1 ET1 events
// Updates compare values for complementary PWM outputs:
// - CMPA: Cycles between 10% to 50% of period
// - CMPB: Cycles between 50% to 90% of period
// - Update step size of 5% of period
// Note: Called every 5 period events (via ET1 prescaler)
__interrupt void INT_myMCPWM1_ISR(void)
{
    static uint16_t gMcpwm1CmpA = 0;     // 0% initial duty
    static uint16_t gMcpwm1CmpB = 0;     // 0% initial duty

    uint16_t minCmpA = (uint16_t)((APP_CMPA_MIN_PERCENT_PERIOD * 8000)/100.0f);
    uint16_t maxCmpA = (uint16_t)((APP_CMPA_MAX_PERCENT_PERIOD * 8000)/100.0f);
    uint16_t minCmpB = (uint16_t)((APP_CMPB_MIN_PERCENT_PERIOD * 8000)/100.0f);
    uint16_t maxCmpB = (uint16_t)((APP_CMPB_MAX_PERCENT_PERIOD * 8000)/100.0f);
    uint16_t stepSize = (uint16_t)((APP_CMP_UPDATE_STEP_PERCENT_PERIOD * 8000)/100.0f);

    // Update compare values
    gMcpwm1CmpA += stepSize;
    gMcpwm1CmpB += stepSize;

    // Check limits and wrap around
    if(gMcpwm1CmpA > maxCmpA) {
        gMcpwm1CmpA = minCmpA;
    }
    if(gMcpwm1CmpB > maxCmpB) {
        gMcpwm1CmpB = minCmpB;
    }

    // Update PWM1 compare values
    Pwm3Regs.PWM1_CMPA.bit.PWM1_CMPA = gMcpwm1CmpA;
    Pwm3Regs.PWM1_CMPB.bit.PWM1_CMPB = gMcpwm1CmpB;

    // Clear interrupt flags
    EALLOW;
    Pwm3Regs.INTCLR.bit.ET1 = 1;
    Pwm3Regs.INTCLR.bit.INT = 1;
    EDIS;

    // Acknowledge interrupt group
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
    // IER &= ~(1 << M_INT3);
}
