//#############################################################################
//
// FILE:   hrpwm_ex2_slider.c
//
// TITLE:  HRPWM Slider.
//
//! \addtogroup driver_example_list
//! <h1>HRPWM Slider</h1>
//!
//! This example modifies the MEP control registers to show edge displacement
//! due to HRPWM. Control blocks of the respective ePWM module channel A and B
//! will have fine edge movement due to HRPWM logic.
//!
//! Monitor ePWM1 A/B pins on an oscilloscope.
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

#define EPWM_TIMER_TBPRD            100UL

//
// Globals
//

uint16_t dutyFine = 1;
uint16_t previousDutyFine = 1;
uint16_t status;

//
// Function Prototypes
//
void initHRPWM(uint32_t period);
void error(void);

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
    // Disable pin locks and enable internal pull ups.
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
    // Initialize the EPWM GPIOs and CHANGE XBAR inputs from using GPIO0
    //
    Board_init();

    //
    // Disable sync(Freeze clock to PWM as well)
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    initHRPWM(EPWM_TIMER_TBPRD);

    //
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);


    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;


    for(;;)
    {
        if (dutyFine != previousDutyFine)
        {
            HRPWM_setCounterCompareValue(myEPWM1_BASE, HRPWM_COUNTER_COMPARE_A,
                                         (EPWM_TIMER_TBPRD/2 << 8) | dutyFine);
            HRPWM_setCounterCompareValue(myEPWM1_BASE, HRPWM_COUNTER_COMPARE_B,
                                         (EPWM_TIMER_TBPRD/2 << 8) | dutyFine);

            previousDutyFine = dutyFine;
        }
     }
}



void initHRPWM(uint32_t period)
{
    EPWM_setEmulationMode(myEPWM1_BASE, EPWM_EMULATION_FREE_RUN);

    //
    // Set-up TBCLK
    //
    EPWM_setTimeBasePeriod(myEPWM1_BASE, period-1);
    EPWM_setPhaseShift(myEPWM1_BASE, 0U);
    EPWM_setTimeBaseCounter(myEPWM1_BASE, 0U);

    //
    // set duty 50% initially
    //
    HRPWM_setCounterCompareValue(myEPWM1_BASE, HRPWM_COUNTER_COMPARE_A, (period/2 << 8));
    HRPWM_setCounterCompareValue(myEPWM1_BASE, HRPWM_COUNTER_COMPARE_B, (period/2 << 8));


    //
    // Set up counter mode
    //
    EPWM_setTimeBaseCounterMode(myEPWM1_BASE, EPWM_COUNTER_MODE_UP);
    EPWM_disablePhaseShiftLoad(myEPWM1_BASE);
    EPWM_setClockPrescaler(myEPWM1_BASE,
                           EPWM_CLOCK_DIVIDER_1,
                           EPWM_HSCLOCK_DIVIDER_1);
    EPWM_setSyncOutPulseMode(myEPWM1_BASE, EPWM_SYNC_OUT_PULSE_DISABLED);


    //
    // Set up shadowing
    //
    EPWM_setCounterCompareShadowLoadMode(myEPWM1_BASE,
                                         EPWM_COUNTER_COMPARE_A,
                                         EPWM_COMP_LOAD_ON_CNTR_ZERO);
    EPWM_setCounterCompareShadowLoadMode(myEPWM1_BASE,
                                         EPWM_COUNTER_COMPARE_B,
                                         EPWM_COMP_LOAD_ON_CNTR_ZERO);

    //
    // Set actions
    //

    EPWM_setActionQualifierAction(myEPWM1_BASE,
                                  EPWM_AQ_OUTPUT_A,
                                  EPWM_AQ_OUTPUT_LOW,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);


    EPWM_setActionQualifierAction(myEPWM1_BASE,
                                  EPWM_AQ_OUTPUT_B,
                                  EPWM_AQ_OUTPUT_LOW,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);

    EPWM_setActionQualifierAction(myEPWM1_BASE,
                                  EPWM_AQ_OUTPUT_A,
                                  EPWM_AQ_OUTPUT_HIGH,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    EPWM_setActionQualifierAction(myEPWM1_BASE,
                                  EPWM_AQ_OUTPUT_B,
                                  EPWM_AQ_OUTPUT_HIGH,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);


    HRPWM_setMEPEdgeSelect(myEPWM1_BASE, HRPWM_CHANNEL_A, HRPWM_MEP_CTRL_RISING_EDGE);
    HRPWM_setMEPControlMode(myEPWM1_BASE, HRPWM_CHANNEL_A, HRPWM_MEP_DUTY_PERIOD_CTRL);
    HRPWM_setCounterCompareShadowLoadEvent(myEPWM1_BASE, HRPWM_CHANNEL_A, HRPWM_LOAD_ON_CNTR_ZERO);

    HRPWM_setMEPEdgeSelect(myEPWM1_BASE, HRPWM_CHANNEL_B, HRPWM_MEP_CTRL_RISING_EDGE);
    HRPWM_setMEPControlMode(myEPWM1_BASE, HRPWM_CHANNEL_B, HRPWM_MEP_DUTY_PERIOD_CTRL);
    HRPWM_setCounterCompareShadowLoadEvent(myEPWM1_BASE, HRPWM_CHANNEL_B, HRPWM_LOAD_ON_CNTR_ZERO);

    //
    // Since we are not using the SFO the Auto Conversion
    // ***MUST*** be DISABLED .
    //
    HRPWM_disableAutoConversion(myEPWM1_BASE);

    //
    // Turn off high-resolution period control.
    //

    HRPWM_disablePeriodControl(myEPWM1_BASE);
    HRPWM_disablePhaseShiftLoad(myEPWM1_BASE);

}

//
// error - Halt debugger when called
//
void error (void)
{
    ESTOP0;         // Stop here and handle error
}

