//#############################################################################
//
// FILE:   eqep_ex2_pos_speed.c
//
// TITLE:  Position and Speed Measurement Using eQEP
//
//! \addtogroup driver_example_list
//! <h1> Position and Speed Measurement Using eQEP</h1>
//!
//! This example provides position and speed measurement using the
//! capture unit and speed measurement using unit time out of the eQEP module.
//! ePWM1 and a GPIO are configured to generate simulated eQEP signals. The
//! ePWM module will interrupt once every period and call the position/speed
//! calculation function. This example uses the IQMath library to simplify
//! high-precision calculations.
//!
//! In addition to the main example file, the following files must be included
//! in this project:
//! - \b eqep_ex2_calculation.c - contains position/speed calculation function
//! - \b eqep_ex2_calculation.h - includes initialization values for
//!                               position/speed structure
//!
//! The configuration for this example is as follows
//! - Maximum speed is configured to 6000rpm (baseRPM)
//! - Minimum speed is assumed at 10rpm for capture pre-scalar selection
//! - Pole pair is configured to 2 (polePairs)
//! - Encoder resolution is configured to 4000 counts/revolution (mechScaler)
//! - Which means: 4000 / 4 = 1000 line/revolution quadrature encoder
//!   (simulated by ePWM1)
//! - ePWM1 (simulating QEP encoder signals) is configured for a 5kHz frequency
//!   or 300 rpm (= 4 * 5000 cnts/sec * 60 sec/min) / 4000 cnts/rev)
//!
//! \b SPEEDRPM_FR: High Speed Measurement is obtained by counting the QEP
//! input pulses for 10ms (unit timer set to 100Hz).
//!
//! \b SPEEDRPM_FR = (Position Delta / 10ms) * 60 rpm
//!
//! \b SPEEDRPM_PR: Low Speed Measurement is obtained by measuring time period
//! of QEP edges. Time measurement is averaged over 64 edges for better results
//! and the capture unit performs the time measurement using pre-scaled SYSCLK.
//!
//! Note that the pre-scaler for capture unit clock is selected such that the
//! capture timer does not overflow at the required minimum frequency. This
//! example runs indefinitely until the user stops it.
//!
//! For more information about the position/speed calculation see the comments
//! at the beginning of eqep_ex2_calculation.c and the XLS file provided with
//! the project, eqep_ex2_calculation.xls.
//!
//! \b External \b Connections \n
//! - Connect GPIO20/eQEP1A to GPIO0/ePWM1A (simulates eQEP Phase A signal)
//! - Connect GPIO21/eQEP1B to GPIO1/ePWM1B (simulates eQEP Phase B signal)
//! - Connect GPIO23/eQEP1I to GPIO2 (simulates eQEP Index Signal)
//!
//! \b Watch \b Variables \n
//!  - \b posSpeed.speedRPMFR - Speed meas. in rpm using QEP position counter
//!  - \b posSpeed.speedRPMPR - Speed meas. in rpm using capture unit
//!  - \b posSpeed.thetaMech  - Motor mechanical angle (Q15)
//!  - \b posSpeed.thetaElec  - Motor electrical angle (Q15)
//!
//
//#############################################################################
//
// 
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
//#############################################################################

//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "IQmathLib.h"
#include "eqep_ex2_calculation.h"

//
// Defines
//
#define TB_CLK    DEVICE_SYSCLK_FREQ / 2    // Time base clock is SYSCLK / 2
#define PWM_CLK   5000                      // We want to output at 5 kHz
                                            // (300 rpm)
#define PRD_VAL   (TB_CLK / (PWM_CLK * 2))  // Calculate value period value
                                            // for up-down count mode

// .9999 / 4000 converted to IQ26 fixed point format
#define MECH_SCALER     16776
// 2 pole pairs in this example
#define POLE_PAIRS      2
// Angular offset between encoder and Phase A
#define CAL_ANGLE       0
// See Equation 5 in eqep_ex2_calculation.c
#define SPEED_SCALER    ((((uint64_t)32 * DEVICE_SYSCLK_FREQ / 64) * 60) / (24000000))
// Base/max rpm is 6000rpm
#define BASE_RPM        6000

//
// Function Prototypes
//
void initEPWM(void);
void initEQEP(void);
__interrupt void epwmISR(void);

//
// Globals
//
PosSpeed_Object posSpeed =
{
    0, 0, 0, 0,     // Initialize outputs to zero
    MECH_SCALER,    // mechScaler
    POLE_PAIRS,     // polePairs
    CAL_ANGLE,      // calAngle
    SPEED_SCALER,   // speedScaler
    0,              // Initialize output to zero
    BASE_RPM,       // baseRPM
    0, 0, 0, 0      // Initialize outputs to zero
};

uint16_t interruptCount = 0;

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
    // Initialize GPIO0 to ePWM1A, GPIO1 to ePWM1B, and GPIO4 as an output.
    // They will be used to simulate incoming eQEP Phase A, Phase B, and Index
    // signals respectively.
    //
    GPIO_setPinConfig(GPIO_0_EPWM1A);
    GPIO_setPadConfig(0, GPIO_PIN_TYPE_STD);

    GPIO_setPinConfig(GPIO_1_EPWM1B);
    GPIO_setPadConfig(1, GPIO_PIN_TYPE_STD);

    GPIO_setPinConfig(GPIO_2_GPIO2);
    GPIO_setDirectionMode(2, GPIO_DIR_MODE_OUT);
    GPIO_writePin(2, 0);

    //
    // Initialize GPIOs for use as EQEP1A, EQEP1B, and EQEP1I
    //
    GPIO_setPinConfig(GPIO_20_EQEP1A);
    GPIO_setPadConfig(20, GPIO_PIN_TYPE_STD);

    GPIO_setPinConfig(GPIO_21_EQEP1B);
    GPIO_setPadConfig(21, GPIO_PIN_TYPE_STD);

    GPIO_setPinConfig(GPIO_23_EQEP1I);
    GPIO_setPadConfig(23, GPIO_PIN_TYPE_STD);

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
    // Interrupts that are used in this example are re-mapped to ISR functions
    // found within this file.
    //
    Interrupt_register(INT_EPWM1, &epwmISR);

    //
    // Setup ePWM1 to generate a 5 kHz signal to be an input to the eQEP
    //
    initEPWM();

    //
    // Enable interrupts required for this example
    //
    Interrupt_enable(INT_EPWM1);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Setup eQEP1, configuring the unit timer and quadrature capture units
    //
    initEQEP();

    //
    // Loop indefinitely
    //
    while(1)
    {
        ;
    }
}

//
// Function to configure eQEP1.
//
void initEQEP(void)
{
    //
    // Configure the decoder for quadrature count mode
    //
    EQEP_setDecoderConfig(EQEP1_BASE, (EQEP_CONFIG_1X_RESOLUTION |
                                       EQEP_CONFIG_QUADRATURE |
                                       EQEP_CONFIG_NO_SWAP));
    EQEP_setEmulationMode(EQEP1_BASE, EQEP_EMULATIONMODE_RUNFREE);

    //
    // Configure the position counter to reset on an index event
    //
    EQEP_setPositionCounterConfig(EQEP1_BASE, EQEP_POSITION_RESET_IDX,
                                  0xFFFFFFFF);

    //
    // Enable the unit timer, setting the frequency to 100 Hz
    //
    EQEP_enableUnitTimer(EQEP1_BASE, (DEVICE_SYSCLK_FREQ / 100));

    //
    // Configure the position counter to be latched on a unit time out
    //
    EQEP_setLatchMode(EQEP1_BASE, EQEP_LATCH_UNIT_TIME_OUT);

    //
    // Enable the eQEP1 module
    //
    EQEP_enableModule(EQEP1_BASE);

    //
    // Configure and enable the edge-capture unit. The capture clock divider is
    // SYSCLKOUT/64. The unit-position event divider is QCLK/32.
    //
    EQEP_setCaptureConfig(EQEP1_BASE, EQEP_CAPTURE_CLK_DIV_64,
                          EQEP_UNIT_POS_EVNT_DIV_32);
    EQEP_enableCapture(EQEP1_BASE);
}

//
// Function to configure ePWM1 to generate a 5 kHz signal.
//
void initEPWM(void)
{
    //
    // Disable the ePWM time base clock before configuring the module
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Set phase shift to 0 and clear the time base counter
    //
    EPWM_setPhaseShift(EPWM1_BASE, 0);
    EPWM_setTimeBaseCounter(EPWM1_BASE, 0);

    //
    // Disable the shadow load; the load will be immediate instead
    //
    EPWM_disableCounterCompareShadowLoadMode(EPWM1_BASE,
                                             EPWM_COUNTER_COMPARE_A);
    EPWM_disableCounterCompareShadowLoadMode(EPWM1_BASE,
                                             EPWM_COUNTER_COMPARE_B);

    //
    // Set the compare A value to half the period value, compare B to 0
    //
    EPWM_setCounterCompareValue(EPWM1_BASE, EPWM_COUNTER_COMPARE_A, PRD_VAL/2);
    EPWM_setCounterCompareValue(EPWM1_BASE, EPWM_COUNTER_COMPARE_B, 0);

    //
    // Set action qualifier behavior on compare A events
    // - EPWM1A --> 1 when CTR = CMPA and increasing
    // - EPWM1A --> 0 when CTR = CMPA and decreasing
    //
    EPWM_setActionQualifierAction(EPWM1_BASE, EPWM_AQ_OUTPUT_A,
                                  EPWM_AQ_OUTPUT_HIGH,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    EPWM_setActionQualifierAction(EPWM1_BASE, EPWM_AQ_OUTPUT_A,
                                  EPWM_AQ_OUTPUT_LOW,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);

    //
    // Set action qualifier behavior on compare B events
    // - EPWM1B --> 1 when CTR = PRD and increasing
    // - EPWM1B --> 0 when CTR = 0 and decreasing
    //
    EPWM_setActionQualifierAction(EPWM1_BASE, EPWM_AQ_OUTPUT_B,
                                  EPWM_AQ_OUTPUT_HIGH,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);
    EPWM_setActionQualifierAction(EPWM1_BASE, EPWM_AQ_OUTPUT_B,
                                  EPWM_AQ_OUTPUT_LOW,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);

    //
    // Enable interrupt when the counter is equal to PRD
    //
    EPWM_setInterruptSource(EPWM1_BASE, EPWM_INT_TBCTR_PERIOD);
    EPWM_enableInterrupt(EPWM1_BASE);

    //
    // Interrupt on first event
    //
    EPWM_setInterruptEventCount(EPWM1_BASE, 1);

    //
    // Set the time base clock prescaler to /1
    //
    EPWM_setClockPrescaler(EPWM1_BASE, EPWM_CLOCK_DIVIDER_1,
                           EPWM_HSCLOCK_DIVIDER_1);

    //
    // Set the period value; don't shadow the register
    //
    EPWM_setPeriodLoadMode(EPWM1_BASE, EPWM_PERIOD_DIRECT_LOAD);
    EPWM_setTimeBasePeriod(EPWM1_BASE, PRD_VAL);

    //
    // Put the time base counter into up-down count mode
    //
    EPWM_setTimeBaseCounterMode(EPWM1_BASE, EPWM_COUNTER_MODE_UP_DOWN);

    //
    // Sync the ePWM time base clock
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);
}

//
// ePWM1 ISR--interrupts once every 4 QCLK counts (one period)
//
 __interrupt void epwmISR(void)
{
    uint16_t i;

    //
    // Position speed and measurement
    //
    PosSpeed_calculate(&posSpeed);

    //
    // Control loop for position control and speed control
    //
    interruptCount++;
    if(interruptCount == 1000)
    {
        //
        // Pulse index signal (1 pulse/rev)
        //
        GPIO_writePin(2, 1);
        for(i = 0; i < 700; i++)
        {
            ;
        }
        GPIO_writePin(2, 0);
    }

    //
    // Clear interrupt flag and issue ACK
    //
    EPWM_clearEventTriggerInterruptFlag(EPWM1_BASE);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP3);
}
