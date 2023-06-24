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
//! For External connections, Control Card settings are used by default. To use
//! launchpad pins for eQEP1A select them in SysConfig.
//!
//! \b External \b Connections for Control Card\n
//! - Connect GPIO6/eQEP1A to GPIO0/ePWM1A
//!
//! \b External \b Connections for LaunchPad\n
//! - Connect GPIO35/eQEP1A to GPIO10/ePWM6A
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
// Copyright (C) 2023 Texas Instruments Incorporated - http://www.ti.com/
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
void initEPWM(void);

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
    //
    // On controlCARD, Initialize GPIO0 to EPWM1A, GPIO6 to EQEP1A
    // On LaunchPad, Initialize GPIO10 to EPWM1A, GPIO10 on EQEP1A

    GPIO_setPinConfig(DEVICE_GPIO_CFG_EPWMxA);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_EPWMxA, GPIO_PIN_TYPE_STD);

    //
    // Setup ePWM1 to generate a 5 kHz signal to be an input to the eQEP
    //
    initEPWM();

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
// initEPWM - Function to configure ePWM1 to generate a 5 kHz signal.
//
void
initEPWM(void)
{
    //
    // Disable the ePWM time base clock before configuring the module
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Set phase shift to 0 and clear the time base counter
    //
    EPWM_setPhaseShift(DEVICE_PERIPHERAL_BASE_EPWM, 0);
    EPWM_setTimeBaseCounter(DEVICE_PERIPHERAL_BASE_EPWM, 0);

    //
    // Disable the shadow load; the load will be immediate instead
    //
    EPWM_disableCounterCompareShadowLoadMode(DEVICE_PERIPHERAL_BASE_EPWM,
                                             EPWM_COUNTER_COMPARE_A);
    EPWM_disableCounterCompareShadowLoadMode(DEVICE_PERIPHERAL_BASE_EPWM,
                                             EPWM_COUNTER_COMPARE_B);

    //
    // Set the compare A value to half the period value, compare B to 0
    //
    EPWM_setCounterCompareValue(DEVICE_PERIPHERAL_BASE_EPWM, EPWM_COUNTER_COMPARE_A, PRD_VAL/2);
    EPWM_setCounterCompareValue(DEVICE_PERIPHERAL_BASE_EPWM, EPWM_COUNTER_COMPARE_B, 0);

    //
    // Set action qualifier behavior on compare A events
    // - EPWM1A --> 1 when CTR = CMPA and increasing
    // - EPWM1A --> 0 when CTR = CMPA and decreasing
    //
    EPWM_setActionQualifierAction(DEVICE_PERIPHERAL_BASE_EPWM, EPWM_AQ_OUTPUT_A,
                                  EPWM_AQ_OUTPUT_HIGH,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    EPWM_setActionQualifierAction(DEVICE_PERIPHERAL_BASE_EPWM, EPWM_AQ_OUTPUT_A,
                                  EPWM_AQ_OUTPUT_LOW,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);

    //
    // Configure EPWM1B to be complementary to EPWM1A
    //
    EPWM_setDeadBandDelayPolarity(DEVICE_PERIPHERAL_BASE_EPWM, EPWM_DB_FED,
                                  EPWM_DB_POLARITY_ACTIVE_LOW);
    EPWM_setDeadBandDelayMode(DEVICE_PERIPHERAL_BASE_EPWM, EPWM_DB_FED, true);
    EPWM_setDeadBandDelayMode(DEVICE_PERIPHERAL_BASE_EPWM, EPWM_DB_RED, true);

    //
    // Set the time base clock prescaler to /1
    //
    EPWM_setClockPrescaler(DEVICE_PERIPHERAL_BASE_EPWM, EPWM_CLOCK_DIVIDER_1,
                           EPWM_HSCLOCK_DIVIDER_1);

    //
    // Set the period value; don't shadow the register
    //
    EPWM_setPeriodLoadMode(DEVICE_PERIPHERAL_BASE_EPWM, EPWM_PERIOD_DIRECT_LOAD);
    EPWM_setTimeBasePeriod(DEVICE_PERIPHERAL_BASE_EPWM, PRD_VAL);

    //
    // Put the time base counter into up-down count mode
    //
    EPWM_setTimeBaseCounterMode(DEVICE_PERIPHERAL_BASE_EPWM, EPWM_COUNTER_MODE_UP_DOWN);

    //
    // Sync the ePWM time base clock
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

