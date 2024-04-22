//###########################################################################
//
// FILE:    ECap_Capture_Pwm_Xbar_cpu01.c
//
// TITLE:   Capture EPWM3.
//
//! \addtogroup cpu01_example_list
//! <h1>ECAP Capture PWM XBAR Example</h1>
//!
//! This example configures ePWM3A for:
//! - Up count
//! - Set on CMPA, Clear on CMPB
//! - CMP and PRD values are cycled throughout the example
//!
//! eCAP1 is configured to monitor the pulse width and effective
//! period of ePWM3A through internal routing via the Input X-Bar
//!
//! \b External \b Connections \n
//! - No external connections are required
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
Uint32  epwm_prd, epwm_cmpa, epwm_cmpb;
Uint32  expected_cap_prd, expected_cap_pulse;
Uint16  first_time, epwm_change_prd;

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
   InitECap1Gpio(4);
   GPIO_SetupPinOptions(19, GPIO_OUTPUT, GPIO_ASYNC);

//
// Initialize example variables
//
   first_time = 1;
   epwm_change_prd = 0;
   expected_cap_pulse = 0;
   expected_cap_prd = 0;

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
   EPwm3Regs.TBPRD = 999;
   EPwm3Regs.TBPHS.all = 0x00000000;
   EPwm3Regs.CMPA.bit.CMPA = 249;
   EPwm3Regs.CMPB.bit.CMPB = 749;
   EPwm3Regs.AQCTLA.bit.CAU = AQ_SET;         // Set on CMPA
   EPwm3Regs.AQCTLA.bit.CBU = AQ_CLEAR;       // Clear on CMPB

   //
   // TBCLK = SYSCLKOUT
   //
   EPwm3Regs.TBCTL.bit.HSPCLKDIV = 0;
   EPwm3Regs.TBCTL.bit.CLKDIV = 0;

   //
   // Set example variables
   //
   expected_cap_pulse = EPwm3Regs.CMPB.bit.CMPB - EPwm3Regs.CMPA.bit.CMPA;
   epwm_prd = EPwm3Regs.TBPRD;
   epwm_cmpa = EPwm3Regs.CMPA.bit.CMPA;
   epwm_cmpb = EPwm3Regs.CMPB.bit.CMPB;

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
   ECap1Regs.ECCTL2.bit.STOP_WRAP = 1;     // Stop at 2 events
   ECap1Regs.ECCTL1.bit.CAP1POL = 0;       // Rising edge
   ECap1Regs.ECCTL1.bit.CAP2POL = 1;       // Falling edge
   ECap1Regs.ECCTL1.bit.CTRRST1 = 1;       // Reset counter after latch
   ECap1Regs.ECCTL1.bit.CTRRST2 = 0;       // Do not reset counter after
   ECap1Regs.ECCTL2.bit.SYNCI_EN = 0;      // Disable sync in
   ECap1Regs.ECCTL2.bit.SYNCO_SEL = 0;     // Pass through
   ECap1Regs.ECCTL1.bit.CAPLDEN = 1;       // Enable capture units

   ECap1Regs.ECCTL2.bit.TSCTRSTOP = 1;     // Start Counter
   ECap1Regs.ECCTL2.bit.REARM = 1;         // arm one-shot
   ECap1Regs.ECCTL1.bit.CAPLDEN = 1;       // Enable CAP1-CAP4 register loads
   ECap1Regs.ECEINT.bit.CEVT2 = 1;         // 4 events = __interrupt
}

//
// ecap1_isr - ECAP1 ISR
//             ECAP runs on SYSCLK and EPWMCLK=SYSCLK/w
//             so multiply TBPRD by 2
//             ECAP accuracy is +/- 1 SYSCLK cycle
//             Due to compounded error, difference between two
//             events may be +/- 2 SYSCLK cycles
//
//             *NOTE* The accuracy of the ECAP is +/- 2 SYSCLK cycles
//             between events. However, we have increased the margin
//             to +/- 4 SYSCLK cycles because an emulator halt behaves
//             slightly differently between the EPWM and ECAP due to the
//             different operating frequencies. This may introduce a couple
//             cycle of deviation in the counter value captured the first
//             time after resuming from a breakpoint.
//
__interrupt void ecap1_isr(void)
{
    //
    // We are resetting the counter every CAP1. If the counter overflows,
    // our PWM likely has an issue
    //
    if(ECap1Regs.ECEINT.bit.CTROVF)
    {
        Fail();
    }

    //
    // Counter is reset after CAP1, so CAP2 will be our pulse width measurement
    //
    if((ECap1Regs.CAP2 - 4) > expected_cap_pulse*2 ||
            ECap1Regs.CAP2 + 4 < expected_cap_pulse*2)
    {
        Fail();
    }

    //
    // Period information is not available on first interrupt
    //
    if(first_time != 1)
    {

        //
        // Since the counter is reset after latching on CAP1
        // subsequent CAP1 values will be our PWM period
        //
        if((ECap1Regs.CAP1 - 4) > expected_cap_prd*2 ||
                    ECap1Regs.CAP1 + 4 < expected_cap_prd*2)
        {
            Fail();
        }
        ECap1PassCount++;
    }
    else
    {
        first_time = 0;
    }

   ECap1IntCount++;

   //
   // Arbitrary values to show changing both CMP and PRD values
   //
   if(epwm_change_prd == 0)
   {
       EPwm3Regs.TBPRD = 999;
       if(EPwm3Regs.CMPA.bit.CMPA == 249)
       {
           EPwm3Regs.CMPA.bit.CMPA = 499;
       }
       else if(EPwm3Regs.CMPA.bit.CMPA == 499)
       {
           EPwm3Regs.CMPA.bit.CMPA = 699;
           epwm_change_prd = 1;
       }
   }
   else
   {
       EPwm3Regs.CMPA.bit.CMPA = 249;
       if(EPwm3Regs.TBPRD == 999)
       {
           EPwm3Regs.TBPRD = 1499;
       }
       else if(EPwm3Regs.TBPRD == 1499)
       {
           EPwm3Regs.TBPRD = 1999;
           epwm_change_prd = 0;
       }
   }

   //
   // Calculate expected measurement values for ECAP
   //
   expected_cap_pulse = EPwm3Regs.CMPB.bit.CMPB - EPwm3Regs.CMPA.bit.CMPA;
   expected_cap_prd = epwm_prd - epwm_cmpa +  EPwm3Regs.CMPA.bit.CMPA;

   //
   // Store updated PWM values
   //
   epwm_cmpa = EPwm3Regs.CMPA.bit.CMPA;
   epwm_cmpb = EPwm3Regs.CMPB.bit.CMPB;
   epwm_prd = EPwm3Regs.TBPRD;

   //
   // Clear interrupts and arm ECAP
   //
   ECap1Regs.ECCLR.bit.CEVT2 = 1;
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
   for(;;);
}

//
// End of file
//
