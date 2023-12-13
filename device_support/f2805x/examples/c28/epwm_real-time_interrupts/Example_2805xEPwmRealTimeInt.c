//###########################################################################
//
// FILE:    Example_2805xEPwmRealTimeInt.c
//
// TITLE:   ePWM Real-Time Interrupt (epwm_real-time_interrupts) example
//
//! \addtogroup f2805x_example_list
//! <h1>ePWM Real-Time Interrupt</h1>
//!
//! This example configures the ePWM1 Timer and increments
//! a counter each time an interrupt is taken. ePWM interrupt can
//! be configured as time critical to demonstrate real-time mode
//! functionality and real-time interrupt capability.
//!
//! ControlCard LED2 (GPIO31) is toggled in main loop. \n
//! ControlCard LED3 (GPIO34) is toggled in ePWM1 Timer Interrupt. \n
//!
//! FREE_SOFT bits and DBBIER.INT3 bit must be set to enable ePWM1
//! interrupt to be time critical and operational in real time mode
//! after halt command. \n
//! In this example:
//!  - ePWM1 is initialized
//!  - ePWM1 is cleared at period match and set at Compare-A match
//!  - Compare A match occurs at half period
//!  - GPIOs for LED2 and LED3 are initialized
//!  - Free_Soft bits and DBGIER are cleared
//!  - An interrupt is taken on a zero event for the ePWM1 timer
//!
//! \b Watch \b Variables \n
//! - EPwm1TimerIntCount
//! - EPwm1Regs.TBCTL.bit.FREE_SOFT
//! - EPwm1Regs.TBCTR
//! - DBGIER.INT3
//
//###########################################################################
// $TI Release: $
// $Release Date: $
// $Copyright:
// Copyright (C) 2012-2023 Texas Instruments Incorporated - http://www.ti.com/
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
// Configure if ePWM timer interrupt is enabled at the PIE level:
// 1 = enabled,  0 = disabled
//
#define PWM1_INT_ENABLE  1

//
// Configure the period for the timer
//
#define PWM1_TIMER_TBPRD   0x1FFF

//
// Prototype statements for functions found within this file.
//
interrupt void epwm1_timer_isr(void);
void InitEPwmTimer(void);

//
// Global variables used in this example
//
Uint32  EPwm1TimerIntCount;        //counts entries into PWM1 Interrupt
Uint16    LEDcount;        //creates delay for LED3 toggling

void main(void)
{
    int i;

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
    // InitGpio();  // Skipped for this example - LEDs set up in main code
    EALLOW;

    //
    // GPIO-31 - PIN FUNCTION = LED2 on controlCARD
    //
    GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 0;  // 0=GPIO, 1=CANTX-A, 2=Resv, 3=Resv
    GpioCtrlRegs.GPADIR.bit.GPIO31 = 1;      // 1=OUTput,  0=INput
    GpioDataRegs.GPACLEAR.bit.GPIO31 = 1;  // uncomment if set low initially
    //    GpioDataRegs.GPASET.bit.GPIO31 = 1;    // uncomment if set high initially

    //
    // GPIO-34 - PIN FUNCTION = LED3 on controlCARD
    //
    GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;    // 0=GPIO, 1=Resv, 2=Resv, 3=Resv
    GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1;        // 1=OUTput,  0=INput

    //
    //    GpioDataRegs.GPBCLEAR.bit.GPIO34 = 1; // uncomment if set low initially
    //
    GpioDataRegs.GPBSET.bit.GPIO34 = 1;        // uncomment if set High initially

    EDIS;

    //
    // Step 3. Clear all interrupts and initialize PIE vector table:
    // Disable CPU interrupts
    //
    DINT;

    //
    // Initialize the PIE control registers to their default state.
    // The default state is all PIE interrupts disabled and flags
    // are cleared.
    // This function is found in the F2805x_PieCtrl.c file.
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
    // The shell ISR routines are found in F2805x_DefaultIsr.c.
    // This function is found in F2805x_PieVect.c.
    //
    InitPieVectTable();

    //
    // Interrupt that is used in this example is re-mapped to
    // ISR function found within this file.
    //
    EALLOW;  // This is needed to write to EALLOW protected registers
    PieVectTable.EPWM1_INT = &epwm1_timer_isr;
    EDIS;    // This is needed to disable write to EALLOW protected registers

    //
    // Step 4. Initialize all the Device Peripherals:
    //
    InitEPwmTimer();    // For this example, only initialize the ePWM Timer

    //
    // Step 5. User specific code, enable interrupts:
    //

    //
    // Initialize counters:
    //
    EPwm1TimerIntCount = 0;

    LEDcount=0;

    //
    // Enable CPU INT3 which is connected to EPWM1-6 INT:
    //
    IER |= M_INT3;

    //
    // Enable EPWM INTn in the PIE: Group 3 interrupt 1-6
    //
    PieCtrlRegs.PIEIER3.bit.INTx1 = PWM1_INT_ENABLE;

    //
    // Initially disable time-critical interrupts
    //
    SetDBGIER(0x0000);   //PIE groups time-critical designation

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
       asm("          NOP");
       for(i = 1; i <= 100; i++)
       {
            GpioDataRegs.GPATOGGLE.bit.GPIO31 = 1;    //toggle LED2 on the controlCARD
       }
    }
}

void InitEPwmTimer()
{
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;      // Stop all the TB clocks
    EDIS;

    //
    // Disable Sync
    //
    EPwm1Regs.TBCTL.bit.SYNCOSEL = 11;  // Pass through

    //
    // Initially disable Free/Soft Bits
    //
    EPwm1Regs.TBCTL.bit.FREE_SOFT = 0;

    EPwm1Regs.TBPRD = PWM1_TIMER_TBPRD;             // Set up PWM1 Period
    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;    // Count up mode
    EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     // Select INT on Zero event
    EPwm1Regs.ETSEL.bit.INTEN = PWM1_INT_ENABLE;  // Enable INT
    EPwm1Regs.ETPS.bit.INTPRD = ET_1ST;           // Generate INT on 1st event
    EPwm1Regs.TBCTR = 0x0000;                     // Clear timer counter
    EPwm1Regs.CMPA.half.CMPA = PWM1_TIMER_TBPRD/2;    //CompareA event at half of period
    EPwm1Regs.AQCTLA.all = 0x0024;                 // Action-qualifiers, Set on CMPA, Clear on PRD

    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;         // Start all the timers synced
    EDIS;
}

//
// Interrupt routines uses in this example:
//
interrupt void epwm1_timer_isr(void)
{
    EPwm1TimerIntCount++;
    LEDcount++;

    //
    // Clear INT flag for this timer
    //
    EPwm1Regs.ETCLR.bit.INT = 1;

    if (LEDcount==500)
    {
        GpioDataRegs.GPBTOGGLE.bit.GPIO34 = 1;    //turn on/off LED3 on the controlCARD
        LEDcount=0;
    }

    //
    // Acknowledge this interrupt to receive more interrupts from group 3
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}

//
// End of file.
//
