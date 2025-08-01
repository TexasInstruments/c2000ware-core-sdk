//#############################################################################
//
// FILE:   mcpwm_ex2_synchronization.c
//
// TITLE:  MCPWM Synchronization Example
//
//! \addtogroup driver_example_list
//! <h1>MCPWM Basic PWM Generation and Updates</h1>
//!
//! This example configures myMCPWM0 and myMCPWM1 as follows
//!     myMCPWM0 
//!         Time Base Configurations 
//!             In Up Count Mode for 10KHz Frequency PWM or 15999 TBCLKs for TBCLK of 160MHz
//!             Enabled Sync in for the InputXbar 5, with phase shift load enabled
//!             Sync Out is configured for every Counter equals Period event
//!         Action Qualifier is configurations
//!             Output A1 : Set High on Counter matches zero, set low on CMPA match
//!             Output B1 : Set High on Counter matches zero, set low on CMPB match
//!         Interrupt
//!             For Updating the Phase Shift Values runtime, Interrupt is configured in synchronous 
//!             with the PWM Counter. 
//!             ET2 is configured to fire at every 5 events of Counter = Period.
//!             ET2 is selected as source for the interrupt generation
//!     
//!     myMCPWM1
//!         Time Base Configurations 
//!             In Up Down Count Mode for 10KHz Frequency PWM or 8000 TBCLKs for TBCLK of 160MHz
//!             Enabled Sync in from myMCPWM0, with phase shift load enabled.
//!             Default Counter Mode after sync is set to counting up. But can be changed.
//!         Action Qualifier is configurations
//!             Output A1 : Set High on Counter matches zero, set low on CMPA match
//!             Output B1 : Set High on Counter matches zero, set low on CMPB match
//!
//!
//!  \b External \b Connections \n
//!     Monitor the MCPWM pins for the waveforms.
//!         Observe J4 40 - GPIO0  - myMCPWM0 Output A1
//!         Observe J4 39 - GPIO1  - myMCPWM0 Output B1
//!         Observe J4 7  - GPIO12 - myMCPWM1 Output A1
//!         Observe J2 19 - GPIO29 - myMCPWM1 Output B1
//! 
//! \b Watch \b Variables \n
//!     - gUsePhaseValueUpdate - set to true to runtime update value for the phase shift value.
//!     - gPhaseShiftValue     - value to be used for the phase shift value.
//!     - gPhaseDirUp          - true to use up phase shift value, false for down phase shift value.
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
#include "driverlib.h"
#include "device.h"
#include "board.h"

// 
// a runtime update value for the phase shift value and observations
// default this value is set to false, and hence the phase shift value 
// is initially taken from the sysconfig configuartions
//
volatile bool gUsePhaseValueUpdate = false;
volatile uint16_t gPhaseShiftValue = 0;
volatile bool gPhaseDirUp = true;

//
// Function Prototypes
//
__interrupt void INT_myMCPWM0_ISR(void);

void main(void)
{
    //
    // Initialize global variables
    //

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Disable pin locks and enable internal pull-ups.
    //
    Device_initGPIO();

    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // Disable sync(Freeze clock to PWM as well)
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Configure mcpwm1, mcpwm2
    //
    Board_init();

    //
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Enable Global Interrupt (INTM) and real time interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // IDLE loop. Just sit and loop forever (optional):
    //
    for(;;)
    {
        NOP;
    }
}

//
// INT_myMCPWM0_ISR - mcpwm0 ISR
//
__interrupt void INT_myMCPWM0_ISR(void)
{   

    //
    // In the Expressions, set gUsePhaseValueUpdate variable to true
    // and use gPhaseShiftValue to update the phase shift value and 
    // observe the waveform. 
    //
    
    if(true == gUsePhaseValueUpdate)
    {
        MCPWM_setPhaseShift(myMCPWM1_BASE, gPhaseShiftValue);

        //
        // Optionally update the Counter direction after the syncin event occurs
        //

        if(true == gPhaseDirUp)
        {
            MCPWM_setCountModeAfterSync(myMCPWM1_BASE, MCPWM_COUNT_MODE_UP_AFTER_SYNC);
        }
        else
        {
            MCPWM_setCountModeAfterSync(myMCPWM1_BASE, MCPWM_COUNT_MODE_DOWN_AFTER_SYNC);
        }
    }
    else
    {
        // 
        // do nothing
        //
    }
   
    //
    // Clear the interrupt flags. 
    // to clear all flags, MCPWM_INT_SOURCE_ALL may be used as arg.
    //
    MCPWM_clearInterrupt(myMCPWM0_BASE, MCPWM_INT_ET_1);

    //
    // Clear the global interrupt flag
    //
    MCPWM_clearGlobalInterrupt(myMCPWM0_BASE);


    //
    // Acknowledge this interrupt to receive more interrupts from group
    //
    Interrupt_clearACKGroup(INT_myMCPWM0_INTERRUPT_ACK_GROUP);
}
