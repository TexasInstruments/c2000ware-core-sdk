//###########################################################################
//
//  FILE:  Example_2803xHRCap_Cature_Pwm.c
//
//  TITLE: Non-High Resolution Capture PWM Pulses example
//
//!  \addtogroup f2803x_example_list
//!  <h1>HRCAP Non-High Resolution Capture PWM Pulses (hrcap_capture_pwm)</h1>
//!
//!  HRCAP1 is configured for non high-resolution capture mode to
//!  capture the time between rising and falling edges of the PWM1A output.
//!
//!  This example configures ePWM1A for:
//!  - Up count
//!  - Period starts at 80 and goes up to 4000 then back down again.
//!  - Toggle output on PRD
//!
//!  \note
//! - On Piccolo-B, the HCCAPCLK frequency is 2 * SYSCLK.EPWM period in 
//!  up-count mode is TBPRD + 1 SYSCLK counts. Therefore,\n
//!  \f$ePWM\ period(up\ count\ mode) =   2* (TBPRD+1) HCCAPCLK\ counts \f$ \n
//! - Because there is no EMU FREE/STOP support in the HRCAP peripheral,
//!  the HRCAP results cannot easily be seen in "Real-time continuous refresh"
//!  debug mode.  The only way to see accurate results of the capture is to
//!  set a breakpoint in the HRCAP ISR immediately after data has been 
//!  captured. Otherwise the results read at any other time in the program 
//!  via the debugger could be mid-capture between one period and the next, 
//!  and therefore bogus.
//!
//!  \b External \b Connections \n
//!  - HRCAP1 is on GPIO26
//!  - ePWM1A is on GPIO0
//!  - Connect output of ePWM1A to input of HRCAP1 (GPIO0->GPIO26)
//!
//!  \b Watch  \b Variables \n
//!  - PULSELOW
//!    - Pulse Width of Low Pulses (# of HCCAPCLK cycles - integer)
//!  - PULSEHIGH
//!    - Pulse Width of High Pulses (# of HCCAPCLK cycles - integer)
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
#include "DSP2803x_Device.h"         // DSP2803x Headerfile
#include "DSP2803x_Examples.h"       // DSP2803x Examples Headerfile
#include "DSP2803x_EPwm_defines.h" 	 // useful defines for initialization

//
// Defines
//
#define HCCAPCLK_FREQ               120    // HCCAPCLK Freq in MHz

//
// Frequency of SYSCLK sourced from same PLL as HRCAP
//
#define HRCAP_SYSCLK_FREQ           60  

//
// # HCCAPCLK's in 1 SYSCLK (sourced from same PLL as HRCAP)
//
#define NUM_HCCAPCLKS_PER_HCSYSCLK  HCCAPCLK_FREQ/HRCAP_SYSCLK_FREQ
#define SYSCLK_FREQ                 60    // System SYSCLK Freq in MHz

//
// Pwm Defines
//
#define PWM1_TIMER_MIN 200
#define PWM1_TIMER_MAX 4000

//
// Function Prototypes
//
void HRCAP1_Config(void);
void ePWM1_Config(Uint16 period);
void Fail(void);
__interrupt void HRCAP1_Isr (void);

//
// Globals
//

//
// Count and Dly captured by 1st RISE/FALL event after cal, soft reset, or 
// clock enable is invalid and therefore ignored. 
// (equals # cycles from reset, cal, clock enable to edge instead of valid 
// pulse width)
//
Uint16 first;
Uint16 PULSELOW;
Uint16 PULSEHIGH;
Uint16 EPwm1TimerDirection;

//
// Defines that keep track of which way the timer value is moving
//
#define EPWM_TIMER_UP   1
#define EPWM_TIMER_DOWN 0

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
    // These functions are in the DSP2803x_HRCap.c and DSP2803x_EPwm.c files
    // respectively
    //
    InitHRCapGpio();
    InitEPwm1Gpio();

    //
    // Step 3. Clear all interrupts and initialize PIE vector table:
    // Disable and clear all CPU interrupts
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
    EALLOW;	// This is needed to write to EALLOW protected registers
    PieVectTable.HRCAP1_INT = &HRCAP1_Isr;
    EDIS;   // This is needed to disable write to EALLOW protected registers

    //
    // Step 4. Initialize all the Device Peripherals:
    //
    HRCAP1_Config();         // Configure HRCAP1 Module
    ePWM1_Config(1000);	     // EPWM1 output waveform, Period = 500

    //
    // For this example, only initialize the EPwm
    // Step 5. User specific code, enable interrupts:
    //

    //
    // Initialize variables
    //
    first = 0;

    //
    // Enable interrupts required for this example
    //
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;   // Enable the PIE block
    PieCtrlRegs.PIEIER4.bit.INTx7=1;     // Enable PIE Group 4, INT 7
    IER|=M_INT4;                         // Enable CPU INT4
    ERTM;
    EINT;                                // Enable Global Interrupts

    //
    // Step 6. IDLE loop. Just sit and loop forever (optional):
    //
    for(;;)
    {
        __asm("          NOP");  // Set breakpoint here to debug
    }
}

//
// ePWM1_Config - 
//
void 
ePWM1_Config(Uint16 period)
{
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;
    EDIS;

    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP; // Count up
    EPwm1Regs.TBPRD = PWM1_TIMER_MIN;
    EPwm1Regs.TBPHS.all = 0x00000000;
    EPwm1Regs.AQCTLA.bit.PRD = AQ_TOGGLE;      // Toggle on PRD

    //
    // TBCLK = SYSCLKOUT
    //
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
    EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    EPwm1TimerDirection = EPWM_TIMER_UP;

    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;
}

//
// HRCAP1_Config -
//
void 
HRCAP1_Config(void)
{
    EALLOW;
    HRCap1Regs.HCCTL.bit.SOFTRESET = 1;
    HRCap1Regs.HCCTL.bit.HCCAPCLKSEL = 1;  // HCCAPCLK = PLLCLK = SYSCLK x 2
    
    //
    // Enable Rising Edge Capture Event Interrupt
    //
    HRCap1Regs.HCCTL.bit.RISEINTE = 1;     
    
    //
    // Disable Falling Edge Capture Event Interrupt
    //
    HRCap1Regs.HCCTL.bit.FALLINTE = 0;
    
    //
    // Disable Interrupt on 16-bit Counter Overflow Event
    //
    HRCap1Regs.HCCTL.bit.OVFINTE = 0;
}

//
// HRCAP1_Isr -
//
__interrupt void 
HRCAP1_Isr (void)
{
    EALLOW;
    if (HRCap1Regs.HCIFR.bit.RISEOVF == 1)
    {
        ESTOP0;      // Another rising edge detected before ISR serviced.
    }

    if (first==0)
    {
        //
        // Discard first data (because first interrupt after reset/clk enable
        // measures time from clock start to edge instead of valid pulse width)
        //
        first = 1; 
    }
    else
    {
        HRCap1Regs.HCCTL.bit.RISEINTE = 0; // Disable rising edge interrupts

        //
        // Current Low and High Pulse
        // In up-count mode: 
        // ePWM pulse width = TBPRD + 1 SYSCLK cycles
        //          = (TBPRD + 1) * (HCCAPCLK_FREQ/SYSCLK_FREQ) HCCAPCLK cycles
        // Variance = +/- 1 SYSCLK cycles (or +/- #HCCAPCLK's/SYSCLK).
        //
        // The extra +/- 1 HCCAPCLK cycle check in this example is to account 
        // for EPWM_TIMER_MAX and EPWM_TIMER_MIN limits when switching between 
        // UP_COUNT/DOWN_COUNT, and pulse captured is still the last period 
        // instead of current period.
        //

        //
        // Capture current high pulse width in HCCAPCLK cycles
        //
        PULSEHIGH = HRCap1Regs.HCCAPCNTFALL1 + 1;

        if ((PULSEHIGH > ((Uint32)(EPwm1Regs.TBPRD + 1)* 
            HCCAPCLK_FREQ/SYSCLK_FREQ + NUM_HCCAPCLKS_PER_HCSYSCLK + 1))||
            (PULSEHIGH < ((Uint32)(EPwm1Regs.TBPRD + 1)* 
            HCCAPCLK_FREQ/SYSCLK_FREQ - NUM_HCCAPCLKS_PER_HCSYSCLK - 1)))
        {
            ESTOP0;
        }

        //
        // Capture low pulse width immediately preceding high pulse width 
        // in HCCAPCLK cycles
        //
        PULSELOW = HRCap1Regs.HCCAPCNTRISE0 + 1;
        if ((PULSELOW > ((Uint32)(EPwm1Regs.TBPRD + 1) * 
            HCCAPCLK_FREQ/SYSCLK_FREQ + NUM_HCCAPCLKS_PER_HCSYSCLK + 1))||
            (PULSELOW < ((Uint32)(EPwm1Regs.TBPRD + 1) * 
            HCCAPCLK_FREQ/SYSCLK_FREQ - NUM_HCCAPCLKS_PER_HCSYSCLK - 1))) 
        {
            ESTOP0;
        }

        //
        // Modulate EPWM1 TBPRD register between TIMER_MAX and TIMER_MIN
        //
        if (EPwm1TimerDirection == EPWM_TIMER_UP)
        {
            if(EPwm1Regs.TBPRD < PWM1_TIMER_MAX)
            {
                EPwm1Regs.TBPRD++;
            }
            else
            {
                EPwm1TimerDirection = EPWM_TIMER_DOWN;
                EPwm1Regs.TBPRD--;
            }
        }
        else
        {
            if(EPwm1Regs.TBPRD > PWM1_TIMER_MIN)
            {
                EPwm1Regs.TBPRD--;
            }
            else
            {
                EPwm1TimerDirection = EPWM_TIMER_UP;
                EPwm1Regs.TBPRD++;
            }
        }
    }

    HRCap1Regs.HCICLR.all = 0x001F;    // Clear all HRCAP interrupts
    HRCap1Regs.HCCTL.bit.RISEINTE = 1; // Re-enable rising edge interrupts

    HRCap1Regs.HCICLR.bit.INT=1;   // Clear HRCAP interrupt flag
    PieCtrlRegs.PIEACK.bit.ACK4=1; // Acknowledge PIE Group 4 interrupts.
    
    EDIS;
}

//
// End of File
//

