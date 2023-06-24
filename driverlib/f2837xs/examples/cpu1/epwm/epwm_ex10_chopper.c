//#############################################################################
//
// FILE:   epwm_ex10_chopper.c
//
// TITLE:  ePWM Using Chopper Submodule.
//
//! \addtogroup driver_example_list
//! <h1>ePWM Chopper</h1>
//!
//! This example configures ePWM1, ePWM2, ePWM3 and ePWM4 as follows
//!  - ePWM1 with Chopper disabled (Reference)
//!  - ePWM2 with chopper enabled at 1/8 duty cycle
//!  - ePWM3 with chopper enabled at 6/8 duty cycle
//!  - ePWM4 with chopper enabled at 1/2 duty cycle with
//!    One-Shot Pulse enabled
//!
//!
//! \b External \b Connections \n
//! - GPIO0 EPWM1A
//! - GPIO1 EPWM1B
//! - GPIO2 EPWM2A
//! - GPIO3 EPWM2B
//! - GPIO4 EPWM3A
//! - GPIO5 EPWM3B
//! - GPIO6 EPWM4A
//! - GPIO7 EPWM4B
//!
//! \b Watch \b Variables \n
//! - None.
//
//
//
//#############################################################################
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
//#############################################################################

//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "board.h"

#define EPWM_TIMER_TBPRD    500UL

//
// Function Prototypes
//
void initEPWM(uint32_t base);

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
    // Configure ePWMs GPIOs
    //
    Board_init();

    //
    // Disable sync(Freeze clock to PWM as well). GTBCLKSYNC is applicable
    // only for multiple core devices. Uncomment the below statement if
    // applicable.
    //
    // SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_GTBCLKSYNC);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Initialize ePWM1 no chopper
    //
    initEPWM(myEPWM1_BASE);

    //
    // Initialize ePWM2 with chopper enabled at 1/8 duty cycle
    //
    initEPWM(myEPWM2_BASE);
    EPWM_setChopperDutyCycle(myEPWM2_BASE, 0);
    EPWM_setChopperFreq(myEPWM2_BASE, 3);
    EPWM_enableChopper(myEPWM2_BASE);

    //
    // Initialize ePWM3 with chopper enabled at 6/8 duty cycle
    //
    initEPWM(myEPWM3_BASE);
    EPWM_setChopperDutyCycle(myEPWM3_BASE, 5);
    EPWM_setChopperFreq(myEPWM3_BASE, 3);
    EPWM_enableChopper(myEPWM3_BASE);

    //
    // Initialize ePWM4 with chopper enabled at 1/2 duty cycle with
    // One-Shot Pulse enabled
    //
    initEPWM(myEPWM4_BASE);
    EPWM_setChopperDutyCycle(myEPWM4_BASE, 3);
    EPWM_setChopperFreq(myEPWM4_BASE, 3);
    EPWM_setChopperFirstPulseWidth(myEPWM4_BASE, 10);
    EPWM_enableChopper(myEPWM4_BASE);

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
// initEPWM - Configure ePWM1
//
void initEPWM(uint32_t base)
{
    //
    // Set-up TBCLK
    //
    EPWM_setTimeBasePeriod(base, EPWM_TIMER_TBPRD);
    EPWM_setPhaseShift(base, 0U);
    EPWM_setTimeBaseCounter(base, 0U);
    EPWM_setTimeBaseCounterMode(base, EPWM_COUNTER_MODE_UP_DOWN);
    EPWM_disablePhaseShiftLoad(base);

    //
    // Set ePWM clock pre-scaler
    //
    EPWM_setClockPrescaler(base,
                           EPWM_CLOCK_DIVIDER_4,
                           EPWM_HSCLOCK_DIVIDER_4);

    //
    // Set up shadowing
    //
    EPWM_setCounterCompareShadowLoadMode(base,
                                         EPWM_COUNTER_COMPARE_A,
                                         EPWM_COMP_LOAD_ON_CNTR_ZERO);

    //
    // Set-up compare
    //
    EPWM_setCounterCompareValue(base, EPWM_COUNTER_COMPARE_A, EPWM_TIMER_TBPRD/4);
    EPWM_setCounterCompareValue(base, EPWM_COUNTER_COMPARE_B, 3*EPWM_TIMER_TBPRD/4);

    //
    // Set actions
    //
    EPWM_setActionQualifierAction(base,
                                      EPWM_AQ_OUTPUT_A,
                                      EPWM_AQ_OUTPUT_LOW,
                                      EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    EPWM_setActionQualifierAction(base,
                                      EPWM_AQ_OUTPUT_A,
                                      EPWM_AQ_OUTPUT_HIGH,
                                      EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    EPWM_setActionQualifierAction(base,
                                      EPWM_AQ_OUTPUT_A,
                                      EPWM_AQ_OUTPUT_NO_CHANGE,
                                      EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);
    EPWM_setActionQualifierAction(base,
                                      EPWM_AQ_OUTPUT_A,
                                      EPWM_AQ_OUTPUT_LOW,
                                      EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);
    EPWM_setActionQualifierAction(base,
                                      EPWM_AQ_OUTPUT_B,
                                      EPWM_AQ_OUTPUT_LOW,
                                      EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    EPWM_setActionQualifierAction(base,
                                      EPWM_AQ_OUTPUT_B,
                                      EPWM_AQ_OUTPUT_HIGH,
                                      EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
    EPWM_setActionQualifierAction(base,
                                      EPWM_AQ_OUTPUT_B,
                                      EPWM_AQ_OUTPUT_NO_CHANGE,
                                      EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);
    EPWM_setActionQualifierAction(base,
                                      EPWM_AQ_OUTPUT_B,
                                      EPWM_AQ_OUTPUT_LOW,
                                      EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);

}
