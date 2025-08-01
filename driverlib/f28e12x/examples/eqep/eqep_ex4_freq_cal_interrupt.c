//#############################################################################
//
// FILE:   eqep_ex4_freq_cal_interrupt.c
//
// TITLE:  Frequency Measurement Using eQEP via unit timeout interrupt
//
//! \addtogroup driver_example_list
//! <h1>Frequency Measurement Using eQEP via unit timeout interrupt</h1>
//!
//! This example will calculate the frequency of an input signal using the
//! eQEP module.  ePWM1A is configured to generate this input signal with a
//! frequency of 5 kHz. EQEP unit timeout is set which will generate
//! an interrupt every \b UNIT_PERIOD microseconds and frequency calculation
//! occurs continuously
//!
//! The configuration for this example is as follows
//! - PWM frequency is specified as 5000Hz
//! - UNIT_PERIOD is specified as 10000 us
//! - Min frequency is (1/(2*10ms)) i.e 50Hz
//! - Highest frequency can be (2^32)/ ((2*10ms))
//! - Resolution of frequency measurement is 50hz
//!
//! \b freq : Frequency Measurement is obtained by counting the
//! external input pulses for UNIT_PERIOD (unit timer set to 10 ms).
//!
//! \b External \b Connections for Control Card\n
//! - Connect GPIO6/eQEP1A to GPIO0/MCPWM1A
//!
//! \b Watch \b Variables \n
//! - \b freq - Frequency measurement using position counter/unit
//!   time out
//! - \b pass - If measured frequency matches with PWM frequency
//!             then pass = 1 else 0
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
#include "board.h"


//
// Defines
//
#define TB_CLK    DEVICE_SYSCLK_FREQ         // ePWM Time base clock is SYSCLK/2
#define PWM_CLK   5000U                      // PWM frequency as 5 kHz
#define PRD_VAL   (TB_CLK / (PWM_CLK * 2))  // Calculate value period value
                                            // for up-down count mode
#define UNIT_PERIOD  10000U // Specify the unit timeout period in
                            // microseconds
                            
//
// Function Prototypes
//

void initMCPWM(void);

//
// Globals
//
uint32_t oldcount = 0;  // stores the previous position counter value
int32_t freq = 0;      // measured frequency using eQEP
uint32_t count = 0;     // just to make sure measured frequency gets saturated
uint32_t pass = 0, fail = 0; // test pass or fail indicator

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
    // - Setup eQEP1, configuring the unit timer and quadrature capture units
    // - Initialize GPIOs for EQEP1A
    // - Interrupts that are used in this example are re-mapped to ISR functions
    //   found within this file.
    // - Enable interrupts required for this example
    //
    Board_init();

    //
    // Initialize GPIOs for EPWM1A
    //

    GPIO_setPinConfig(GPIO_0_MCPWM1_1A);
    GPIO_setPadConfig(0, GPIO_PIN_TYPE_STD);

    //
    // Setup ePWM1 to generate a 5 kHz signal to be an input to the eQEP
    //
    initMCPWM();
    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

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

    MCPWM_setPeriodLoadMode(PWM1_BASE, MCPWM_PERIOD_SHADOW_LOAD_DISABLE);
    MCPWM_setCounterCompareShadowLoadMode(PWM1_BASE, MCPWM_COUNTER_COMPARE_1A, MCPWM_COMP_LOAD_FREEZE);
    MCPWM_setCounterCompareShadowLoadMode(PWM1_BASE, MCPWM_COUNTER_COMPARE_1B, MCPWM_COMP_LOAD_FREEZE);
    MCPWM_setActionQualifierShadowLoadMode(PWM1_BASE, MCPWM_ACTION_QUALIFIER_1A, MCPWM_AQ_LOAD_FREEZE);
    MCPWM_setActionQualifierShadowLoadMode(PWM1_BASE, MCPWM_ACTION_QUALIFIER_1B, MCPWM_AQ_LOAD_FREEZE);
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
    MCPWM_setCounterCompareActiveValue(PWM1_BASE, MCPWM_COUNTER_COMPARE_1B, 0);

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
    // Set the time base clock prescaler to /1
    //
    MCPWM_setClockPrescaler(PWM1_BASE, MCPWM_CLOCK_DIVIDER_1);

    //
    // Set the period value; don't shadow the register
    //
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
// eqep11 ISR- interrupts once per ePWM period
//
__interrupt void
INT_myEQEP0_ISR(void)
{

    uint32_t temp =0, newcount = 0 ;
    
    count++;  // increment count value so to wait for frequency saturation

    newcount = EQEP_getPositionLatch(myEQEP0_BASE); // new position counter value
    temp = newcount;

    //
    // Calculates the number of position counts in unit time
    //
    if (newcount >= oldcount)
        newcount = newcount - oldcount;
    else
        newcount = (0xFFFFFFFF - oldcount) + newcount;

    //
    // Stores the current position count value to oldcount variable
    //
    oldcount = temp;

    //
    // Frequency calculation equation i.e
    // freq = ((position counts) * 1000000 )/ (2 * Unit_time (in microseconds))
    //
    freq = (newcount * (uint32_t)1000000U)/(2 * (uint32_t)UNIT_PERIOD);

    //
    // Compares the measured frequency with input frequency
    //
    if (count >= 2){
        if (((freq - PWM_CLK) < 50) && ((freq - PWM_CLK) > -50)){
            pass = 1; fail = 0;
        }
        else {
            fail = 1; pass = 0;
        }
    }

    //
    // Clears the interrupt flag
    //
    EQEP_clearInterruptStatus(myEQEP0_BASE,EQEP_INT_UNIT_TIME_OUT|EQEP_INT_GLOBAL);
    Interrupt_clearACKGroup(INT_myEQEP0_INTERRUPT_ACK_GROUP);
}

//
// End of File
//
