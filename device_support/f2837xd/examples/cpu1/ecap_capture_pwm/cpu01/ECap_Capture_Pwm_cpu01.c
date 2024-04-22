//###########################################################################
//
// FILE:    ECap_Capture_Pwm_cpu01.c
//
// TITLE:   Capture EPWM3.
//
//! \addtogroup cpu01_example_list
//! <h1>ECAP Capture PWM Example</h1>
//!
//! This example configures ePWM3A for:
//! - Up count
//! - Period starts at 2 and goes up to 1000
//! - Toggle output on PRD
//!
//! eCAP1 is configured to capture the time between rising
//! and falling edge of the ePWM3A output.
//!
//! \b External \b Connections \n
//! - eCAP1 is on GPIO19
//! - ePWM3A is on GPIO4
//! - Connect GPIO4 to GPIO19.
//!
//! \b Watch \b Variables \n
//! - \b ECap1PassCount - Successful captures
//! - \b ECap1IntCount - Interrupt counts
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
// Configure the start/end period for the timer
#define PWM3_TIMER_MIN     10
#define PWM3_TIMER_MAX     8000
// To keep track of which way the timer value is moving
#define EPWM_TIMER_UP   1
#define EPWM_TIMER_DOWN 0

//
// Globals
//
Uint32  ECap1IntCount;
Uint32  ECap1PassCount;
Uint32  EPwm3TimerDirection;

//
// Function Prototypes
//
__interrupt void ecap1_isr(void);
void InitECapture(void);
void InitEPwmTimer(void);
void Fail(void);

//
// Main
//
void main(void)
{
//
// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the F2837xD_SysCtrl.c file.
//
   InitSysCtrl();

//
// Step 2. Initialize GPIO:
// This example function is found in the F2837xD_Gpio.c file and
// illustrates how to set the GPIO to its default state.
//
   InitEPwm3Gpio();
   InitECap1Gpio(19);
   GPIO_SetupPinOptions(19, GPIO_INPUT, GPIO_ASYNC);

//
// Step 3. Clear all __interrupts and initialize PIE vector table:
// Disable CPU __interrupts
//
   DINT;

//
// Initialize the PIE control registers to their default state.
// The default state is all PIE __interrupts disabled and flags
// are cleared.
// This function is found in the F2837xD_PieCtrl.c file.
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
// The shell ISR routines are found in F2837xD_DefaultIsr.c.
// This function is found in F2837xD_PieVect.c.
//
   InitPieVectTable();

//
// Interrupts that are used in this example are re-mapped to
// ISR functions found within this file.
//
   EALLOW;  // This is needed to write to EALLOW protected registers
   PieVectTable.ECAP1_INT = &ecap1_isr;
   EDIS;    // This is needed to disable write to EALLOW protected registers

//
// Step 4. Initialize the Device Peripherals:
//
   InitEPwmTimer();    // For this example, only initialize the ePWM Timers
   InitECapture();

//
// Initialize counters:
//
   ECap1IntCount = 0;
   ECap1PassCount = 0;

//
// Enable CPU INT4 which is connected to ECAP1-4 INT:
//
   IER |= M_INT4;

//
// Enable eCAP INTn in the PIE: Group 3 __interrupt 1-6
//
   PieCtrlRegs.PIEIER4.bit.INTx1 = 1;

//
// Enable global Interrupts and higher priority real-time debug events:
//
   EINT;   // Enable Global __interrupt INTM
   ERTM;   // Enable Global realtime __interrupt DBGM

//
// Step 5. IDLE loop. Just sit and loop forever (optional):
//
   for(;;)
   {
      asm("          NOP");
   }
}

//
// InitEPwmTimer - Initialize ePWM3 timer configuration
//
void InitEPwmTimer()
{
   EALLOW;
   CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;
   EDIS;

   EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP; // Count up
   EPwm3Regs.TBPRD = PWM3_TIMER_MIN;
   EPwm3Regs.TBPHS.all = 0x00000000;
   EPwm3Regs.AQCTLA.bit.PRD = AQ_TOGGLE;      // Toggle on PRD

   //
   // TBCLK = SYSCLKOUT
   //
   EPwm3Regs.TBCTL.bit.HSPCLKDIV = 1;
   EPwm3Regs.TBCTL.bit.CLKDIV = 0;

   EPwm3TimerDirection = EPWM_TIMER_UP;

   EALLOW;
   CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
   EDIS;
}

//
// InitECapture - Initialize ECAP1 configurations
//
void InitECapture()
{
   ECap1Regs.ECEINT.all = 0x0000;          // Disable all capture __interrupts
   ECap1Regs.ECCLR.all = 0xFFFF;           // Clear all CAP __interrupt flags
   ECap1Regs.ECCTL1.bit.CAPLDEN = 0;       // Disable CAP1-CAP4 register loads
   ECap1Regs.ECCTL2.bit.TSCTRSTOP = 0;     // Make sure the counter is stopped

   //
   // Configure peripheral registers
   //
   ECap1Regs.ECCTL2.bit.CONT_ONESHT = 1;   // One-shot
   ECap1Regs.ECCTL2.bit.STOP_WRAP = 3;     // Stop at 4 events
   ECap1Regs.ECCTL1.bit.CAP1POL = 1;       // Falling edge
   ECap1Regs.ECCTL1.bit.CAP2POL = 0;       // Rising edge
   ECap1Regs.ECCTL1.bit.CAP3POL = 1;       // Falling edge
   ECap1Regs.ECCTL1.bit.CAP4POL = 0;       // Rising edge
   ECap1Regs.ECCTL1.bit.CTRRST1 = 1;       // Difference operation
   ECap1Regs.ECCTL1.bit.CTRRST2 = 1;       // Difference operation
   ECap1Regs.ECCTL1.bit.CTRRST3 = 1;       // Difference operation
   ECap1Regs.ECCTL1.bit.CTRRST4 = 1;       // Difference operation
   ECap1Regs.ECCTL2.bit.SYNCI_EN = 1;      // Enable sync in
   ECap1Regs.ECCTL2.bit.SYNCO_SEL = 0;     // Pass through
   ECap1Regs.ECCTL1.bit.CAPLDEN = 1;       // Enable capture units

   ECap1Regs.ECCTL2.bit.TSCTRSTOP = 1;     // Start Counter
   ECap1Regs.ECCTL2.bit.REARM = 1;         // arm one-shot
   ECap1Regs.ECCTL1.bit.CAPLDEN = 1;       // Enable CAP1-CAP4 register loads
   ECap1Regs.ECEINT.bit.CEVT4 = 1;         // 4 events = __interrupt
}

//
// ecap1_isr - ECAP1 ISR
//              Cap input is syc'ed to SYSCLKOUT so there may be
//              a +/- 1 cycle variation
//
__interrupt void ecap1_isr(void)
{
   if(ECap1Regs.CAP2 > EPwm3Regs.TBPRD*4+4 ||
      ECap1Regs.CAP2 < EPwm3Regs.TBPRD*4-4)
   {
       Fail();
   }

   if(ECap1Regs.CAP3 > EPwm3Regs.TBPRD*4+4 ||
      ECap1Regs.CAP3 < EPwm3Regs.TBPRD*4-4)
   {
       Fail();
   }

   if(ECap1Regs.CAP4 > EPwm3Regs.TBPRD*4+4 ||
      ECap1Regs.CAP4 < EPwm3Regs.TBPRD*4-4)
   {
       Fail();
   }

   ECap1IntCount++;

   if(EPwm3TimerDirection == EPWM_TIMER_UP)
   {
        if(EPwm3Regs.TBPRD < PWM3_TIMER_MAX)
        {
           EPwm3Regs.TBPRD++;
        }
        else
        {
           EPwm3TimerDirection = EPWM_TIMER_DOWN;
           EPwm3Regs.TBPRD--;
        }
   }
   else
   {
        if(EPwm3Regs.TBPRD > PWM3_TIMER_MIN)
        {
           EPwm3Regs.TBPRD--;
        }
        else
        {
           EPwm3TimerDirection = EPWM_TIMER_UP;
           EPwm3Regs.TBPRD++;
        }
   }

   ECap1PassCount++;

   ECap1Regs.ECCLR.bit.CEVT4 = 1;
   ECap1Regs.ECCLR.bit.INT = 1;
   ECap1Regs.ECCTL2.bit.REARM = 1;

   //
   // Acknowledge this __interrupt to receive more __interrupts from group 4
   //
   PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;
}

//
// Fail - Function that halts debugger
//
void Fail()
{
   asm("   ESTOP0");
}

//
// End of file
//
