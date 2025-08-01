//#############################################################################
//
// FILE:   eqep_ex1_freq_cal.c
//
// TITLE:  Frequency Measurement Using eQEP
//
//! \addtogroup driver_example_list
//! <h1>Frequency Measurement Using eQEP</h1>
//!
//! This example will calculate the frequency of an input signal using the eQEP
//! module.  MCPWM1A is configured to generate this input signal with a
//! frequency of 5 kHz. It will interrupt once every period and call the
//! frequency calculation function. This example uses the IQMath library to
//! simplify high-precision calculations.
//!
//! In addition to the main example file, the following files must be included
//! in this project:
//! - \b eqep_ex1_calculation.c - contains frequency calculation function
//! - \b eqep_ex1_calculation.h - includes initialization values for frequency
//!                               structure
//!
//! The configuration for this example is as follows
//! - Maximum frequency is configured to 10KHz (baseFreq)
//! - Minimum frequency is assumed at 50Hz for capture pre-scalar selection
//!
//! \b SPEED_FR: High Frequency Measurement is obtained by counting the
//! external input pulses for 10ms (unit timer set to 100Hz).
//! \f[ SPEED\_FR = \frac{Count\ Delta}{10ms} \f]
//!
//! \b SPEED_PR: Low Frequency Measurement is obtained by measuring time
//! period of input edges. Time measurement is averaged over 64 edges for
//! better results and the capture unit performs the time measurement using
//! pre-scaled SYSCLK.
//!
//! Note that the pre-scaler for capture unit clock is selected such that the
//! capture timer does not overflow at the required minimum frequency. This
//! example runs indefinitely until the user stops it.
//!
//! For more information about the frequency calculation see the comments at
//! the beginning of eqep_ex1_calculation.c and the XLS file provided with the
//! project, eqep_ex1_calculation.xls.
//!
//! \b External \b Connections \n
//! - Connect GPIO6/eQEP1A to GPIO0/MCPWM1A
//!
//! \b Watch \b Variables \n
//! - \b freq.freqHzFR - Frequency measurement using position counter/unit
//!   time out
//! - \b freq.freqHzPR - Frequency measurement using capture unit
//!
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
#include "IQmathLib.h"
#include "eqep_ex1_calculation.h"
#include "board.h"


//
// Defines
//
#define TB_CLK    DEVICE_SYSCLK_FREQ        // Time base clock is SYSCLK
#define PWM_CLK   5000                      // We want to output at 5 kHz
#define PRD_VAL   (TB_CLK / (PWM_CLK * 2))  // Calculate value period value
                                            // for up-down count mode

// Base/max frequency is 10 kHz
#define BASE_FREQ       10000
// See Equation 5 in eqep_ex1_calculation.c
#define FREQ_SCALER_PR  (((DEVICE_SYSCLK_FREQ / 128) * 8) / (2 * BASE_FREQ))
// See Equation 2 in eqep_ex1_calculation.c
#define FREQ_SCALER_FR  ((BASE_FREQ * 2) / 100)

//
// Function Prototypes
//
void initMCPWM(void);
__interrupt void mcpwmISR(void);

//
// Globals
//
FreqCal_Object freq =
{
    FREQ_SCALER_PR,  // freqScalerPR
    FREQ_SCALER_FR,  // freqScalerFR
    BASE_FREQ,       // baseFreq
    0, 0, 0, 0, 0    // Initialize outputs to zero
};
uint32_t count =0;  // counter to check measurement gets saturated
uint32_t pass=0, fail =0; // Pass or fail indicator

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
    // Disable pin locks and enable internal pullups.
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
    // Board Initialization
    // Setup eQEP1, configuring the unit timer and quadrature capture units
    //
    Board_init();

    //
    // Initialize GPIOs for use as MCPWM1A and EQEP1A
    //
    GPIO_setPinConfig(GPIO_0_MCPWM1_1A);
    GPIO_setPadConfig(0, GPIO_PIN_TYPE_STD);

    //
    // Interrupts that are used in this example are re-mapped to ISR functions
    // found within this file.
    //
    Interrupt_register(INT_MCPWM1, &mcpwmISR);

    //
    // Setup MCPWM1 to generate a 5 kHz signal to be an input to the eQEP
    //
    initMCPWM();

    //
    // Enable interrupts required for this example
    //
    Interrupt_enable(INT_MCPWM1);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Setup eQEP1, configuring the unit timer and quadrature capture units
    //
   // initEQEP();  -- >change with Board_init(); soon

    //
    // Loop indefinitely
    //
    while(1)
    {
        ;
    }
}


//
// initMCPWM - Function to configure MCPWM1 to generate a 5 kHz signal.
//
void
initMCPWM(void)
{
    //
    // Disable the MCPWM time base clock before configuring the module
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Load Mode configurations
    //
    // - Time Base Load Mode: Disabled
    // - Counter Compare Load Mode: Freeze shadow to active load
    // - Action Qualifier Load Mode: Freeze shadow to active load
    //
    MCPWM_setPeriodLoadMode(PWM1_BASE, MCPWM_PERIOD_SHADOW_LOAD_DISABLE);
    MCPWM_setCounterCompareShadowLoadMode(PWM1_BASE, MCPWM_COUNTER_COMPARE_1A, MCPWM_COMP_LOAD_FREEZE);
    MCPWM_setActionQualifierShadowLoadMode(PWM1_BASE, MCPWM_ACTION_QUALIFIER_1A, MCPWM_AQ_LOAD_FREEZE);
    MCPWM_setRisingEdgeDelayCountShadowLoadMode(PWM1_BASE, MCPWM_RED_LOAD_FREEZE);
    MCPWM_setFallingEdgeDelayCountShadowLoadMode(PWM1_BASE, MCPWM_FED_LOAD_FREEZE);

    //
    // Set phase shift to 0 and clear the time base counter
    //
    MCPWM_setPhaseShift(PWM1_BASE, 0);
    MCPWM_setTimeBaseCounter(PWM1_BASE, 0);

    //
    // Set the compare A value to half the period value, compare B to 0
    //
    MCPWM_setCounterCompareActiveValue(PWM1_BASE, MCPWM_COUNTER_COMPARE_1A, PRD_VAL/2);

    //
    // Set action qualifier behavior on compare A events
    // - MCPWM1A --> 1 when CTR = CMPA and increasing
    // - MCPWM1A --> 0 when CTR = CMPA and decreasing
    //
    MCPWM_setActionQualifierActionCompleteActive(PWM1_BASE, MCPWM_AQ_OUTPUT_1A, MCPWM_AQ_OUTPUT_NO_CHANGE_ZERO | 
        MCPWM_AQ_OUTPUT_NO_CHANGE_PERIOD | 
        MCPWM_AQ_OUTPUT_HIGH_UP_CMPA | 
        MCPWM_AQ_OUTPUT_LOW_DOWN_CMPA | 
        MCPWM_AQ_OUTPUT_NO_CHANGE_UP_CMPB | 
        MCPWM_AQ_OUTPUT_NO_CHANGE_DOWN_CMPB);

    //
    // Configure MCPWM1B to be complementary to MCPWM1A
    //
    MCPWM_setDeadBandDelayPolarity(PWM1_BASE, MCPWM_DB_FED,
                                  MCPWM_DB_POLARITY_ACTIVE_LOW);
    MCPWM_setDeadBandDelayMode(PWM1_BASE, MCPWM_DB_FED, true);
    MCPWM_setDeadBandDelayMode(PWM1_BASE, MCPWM_DB_RED, true);

    //
    // Enable interrupt when the counter is equal to 0
    //
    MCPWM_setEventTriggerSource(PWM1_BASE, MCPWM_ET_1,
                                MCPWM_EVT_TBCTR_ZERO);
    MCPWM_enableInterrupt(PWM1_BASE, MCPWM_INT_ET_1);

    //
    // Interrupt on first event
    //
    MCPWM_setEventTriggerEventPrescale(PWM1_BASE, MCPWM_ET_1, 1);

    //
    // Set the time base clock prescaler to /1
    //
    MCPWM_setClockPrescaler(PWM1_BASE, MCPWM_CLOCK_DIVIDER_1);

    //
    // Set the period value; don't shadow the register
    //
    MCPWM_setPeriodLoadMode(PWM1_BASE, MCPWM_PERIOD_SHADOW_LOAD_DISABLE);
    MCPWM_setTimeBasePeriodActive(PWM1_BASE, PRD_VAL);

    //
    // Put the time base counter into up-down count mode
    //
    MCPWM_setTimeBaseCounterMode(PWM1_BASE, MCPWM_COUNTER_MODE_UP_DOWN);

    //
    // Sync the MCPWM time base clock
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);
}

//
// MCPWM1 ISR- interrupts once per MCPWM period
//
__interrupt void
mcpwmISR(void)
{
    //
    // Checks for events and calculates frequency.
    //
    FreqCal_calculate(&freq, &count);

    //
    // Comparing the eQEP measured frequency with the MCPWM frequency
    // After count becomes 3 , eQEP measurement gets saturated and
    // classifying pass = 1 if measured frequency is 50 more or
    // less than input
    //
    if (count >= 3){
        if (((freq.freqHzFR - PWM_CLK) < 50) && ((freq.freqHzFR - PWM_CLK) > -50)) {
               pass = 1; fail = 0;
          }
        else {
            fail = 1; pass = 0;
          }
       }
    //
    // Clear interrupt flag and issue ACK
    //
    MCPWM_clearInterrupt(PWM1_BASE, MCPWM_INT_ET_1);
    MCPWM_clearGlobalInterrupt(PWM1_BASE);

    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP2);
}

//
// End of File
//

