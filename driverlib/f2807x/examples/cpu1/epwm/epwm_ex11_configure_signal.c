//###########################################################################
//
// FILE:   epwm_ex11_configure_signal.c
//
// TITLE:  Configure desired EPWM frequency & duty
//
//! \addtogroup driver_example_list
//! <h1> EPWM Configure Signal </h1>
//!
//! This example configures ePWM1, ePWM2, ePWM3 to produce signal of desired
//! frequency and duty. It also configures phase between the configured
//! modules.
//!
//! Signal of 10kHz with duty of 0.5 is configured on ePWMxA & ePWMxB
//! with ePWMxB inverted. Also, phase of 120 degree is configured between
//! ePWM1 to ePWM3 signals.
//!
//! During the test, monitor ePWM1, ePWM2, and/or ePWM3 outputs
//! on an oscilloscope.
//!
//! - ePWM1A is on GPIO0
//! - ePWM1B is on GPIO1
//! - ePWM2A is on GPIO2
//! - ePWM2B is on GPIO3
//! - ePWM3A is on GPIO4
//! - ePWM3B is on GPIO5
//!
//
//###########################################################################
//
// $Release Date: $
// $Copyright:
// Copyright (C) 2014-2023 Texas Instruments Incorporated - http://www.ti.com/
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
#include "driverlib.h"
#include "device.h"
#include "board.h"

//
// Globals
//
EPWM_SignalParams pwmSignal =
            {10000, 0.5f, 0.5f, true, DEVICE_SYSCLK_FREQ, SYSCTL_EPWMCLK_DIV_2,
            EPWM_COUNTER_MODE_UP_DOWN, EPWM_CLOCK_DIVIDER_1,
            EPWM_HSCLOCK_DIVIDER_1};
//
//  Function Prototypes
//
void configurePhase(uint32_t base, uint32_t masterBase, uint16_t phaseVal);

//
// Main
//
void main(void)
{
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
    // For this case just init GPIO pins for ePWM1, ePWM2, ePWM3
    //
    Board_init();

    //
    // Disable sync(Freeze clock to PWM as well)
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Configuring ePWM module for desired frequency and duty
    //
    EPWM_configureSignal(myEPWM1_BASE, &pwmSignal);
    EPWM_configureSignal(myEPWM2_BASE, &pwmSignal);
    EPWM_configureSignal(myEPWM3_BASE, &pwmSignal);

    //
    // Configure phase between PWM1, PWM2 & PWM3.
    // PWM1 is configured as master and ePWM2 & 3
    // are configured as slaves.
    //
    EPWM_disablePhaseShiftLoad(myEPWM1_BASE);
    EPWM_setPhaseShift(myEPWM1_BASE, 0U);

    //
    // ePWM1 SYNCO is generated on CTR=0
    //
    EPWM_setSyncOutPulseMode(myEPWM1_BASE, EPWM_SYNC_OUT_PULSE_ON_COUNTER_ZERO);

    //
    // Configure phase shift for EPWM2 & 3
    //
    configurePhase(myEPWM2_BASE, myEPWM1_BASE, 120);
    configurePhase(myEPWM3_BASE, myEPWM1_BASE, 240);


    EPWM_enablePhaseShiftLoad(myEPWM2_BASE);
    EPWM_enablePhaseShiftLoad(myEPWM3_BASE);

    //
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Enable interrupts required for this example
    //
    Interrupt_enable(INT_EPWM1);

    //
    // Enable global Interrupts and higher priority real-time debug events:
    //
    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global realtime interrupt DBGM

    //
    // IDLE loop. Just sit and loop forever (optional):
    //
    for(;;)
    {
        asm ("  NOP");
    }
}

//
// configurePhase - Configure ePWMx Phase
//
void configurePhase(uint32_t base, uint32_t masterBase, uint16_t phaseVal)
{
    uint32_t readPrdVal, phaseRegVal;

    //
    // Read Period value to calculate value for Phase Register
    //
    readPrdVal = EPWM_getTimeBasePeriod(masterBase);

    //
    // Caluclate phase register values based on Time Base counter mode
    //
    if((HWREGH(base + EPWM_O_TBCTL) & 0x3U) == EPWM_COUNTER_MODE_UP_DOWN)
    {
        phaseRegVal = (2U * readPrdVal * phaseVal) / 360U;
    }
    else if((HWREGH(base + EPWM_O_TBCTL) & 0x3U) < EPWM_COUNTER_MODE_UP_DOWN)
    {
        phaseRegVal = (readPrdVal * phaseVal) / 360U;
    }

    EPWM_selectPeriodLoadEvent(base, EPWM_SHADOW_LOAD_MODE_SYNC);
    EPWM_setPhaseShift(base, phaseRegVal);
    EPWM_setTimeBaseCounter(base, phaseRegVal);
}

//
// End of file
//
