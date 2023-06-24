//#############################################################################
//
// FILE:   eqep_ex5_speed_dir_motor.c
//
// TITLE:  Motor encoder speed and direction measurement using eQEP
//         via unit timeout interrupt
//
//! \addtogroup driver_example_list
//! <h1>Motor speed and direction measurement using eQEP
//! via unit timeout interrupt</h1>
//!
//! This example can be used to sense the speed and direction of motor
//! using eQEP in quadrature encoder mode. ePWM1A is configured to simulate
//! motor encoder signals with frequency of 5 kHz on both A and B pins with 90
//! degree phase shift (so as to run this example without motor).
//! EQEP unit timeout is set which will generate an interrupt every
//!  \b UNIT_PERIOD microseconds and speed calculation occurs continuously
//!  based on the direction of motor
//!
//! The configuration for this example is as follows
//! - PWM frequency is specified as 5000Hz
//! - UNIT_PERIOD is specified as 10000 us
//! - Simulated quadrature signal frequency is 20000Hz (4 * 5000)
//! - Encoder holes assumed as 1000
//! - Thus Simulated motor speed is 300rpm (5000 * (60 / 1000))
//!
//! \b freq : Simulated quadrature signal frequency measured by counting
//! the external input pulses for UNIT_PERIOD (unit timer set to 10 ms).
//! \b speed : Measure motor speed in rpm
//! \b dir : Indicates clockwise (1) or anticlockwise (-1)
//!
//! \b External \b Connections (if motor encoder signals are simulated
//! by ePWM) \n
//! With motor \n
//! - Comment in "MOTOR" in includes
//! For External connections, Control Card settings are used by default. To use
//! launchpad pins for output select them in SysConfig.
//!
//! - On controlCARD, Connect GPIO6/eQEP1A to GPIO0/ePWM1A 
//!   (simulates eQEP Phase A signal)
//! - On controlCARD, Connect GPIO7/eQEP1B to GPIO1/ePWM1B 
//!   (simulates eQEP Phase B signal)
//! - On LaunchPad, Connect GPIO35/eQEP1A to GPIO10/ePWM6A 
//!   (simulates eQEP Phase A signal)
//! - On LaunchPad, Connect GPIO37/eQEP1B to GPIO11/ePWM6B 
//!   (simulates eQEP Phase B signal)
//!
//! \b Watch \b Variables \n
//! - \b freq : Simulated motor frequency measurement is obtained by counting
//! the external input pulses for UNIT_PERIOD (unit timer set to 10 ms).
//! - \b speed : Measure motor speed in rpm
//! - \b dir : Indicates clockwise (1) or anticlockwise (-1)
//! - \b pass - If measured qudrature frequency matches with i.e. input
//!             quadrature frequency (4 * PWM frequency) then pass = 1
//!             else fail = 1 (** only when "MOTOR" is commented out)
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
#define TB_CLK    DEVICE_SYSCLK_FREQ         // Time base clock is SYSCLK / 2
#define PWM_CLK   5000U                      // We want to output at 5 kHz
#define PRD_VAL   (TB_CLK / (PWM_CLK * 2))  // Calculate value period value
                                           // for up-down count mode
#define UNIT_PERIOD  10000U // Specify the period in microseconds
//Uncomment if motor is available for interfacing
//#define MOTOR

//
// Function Prototypes
//
void initEPWM(void);

//
// Globals
//
uint32_t oldcount = 0;  // stores the previous position counter value
int32_t freq = 0;   // measured quadrature signal frequency of motor using eQEP
float32_t speed = 0.0f;       // measured speed of motor in rpm
int32_t dir = 0;       // direction of rotation of motor
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
    // - Interrupts that are used in this example are re-mapped to ISR functions
    //   found within this file.
    // - Enable interrupts required for this example
    //
    Board_init();

    //
    // Initialize GPIOs for use as EPWM1A,EPWM1B and EQEP1A,
    // EQEPB
    //
    //
    // On controlCARD, Initialize GPIO0 to ePWM1A, GPIO1 to ePWM1B, and GPIO4 
    // as an output. (On LaunchPad, use GPIO10 on ePWM6A, GPIO11 on ePWM6B, and 
    // GPIO8 as an output.)
    // They will be used to simulate incoming eQEP Phase A, Phase B, and Index
    // signals respectively.
    //
    GPIO_setPinConfig(DEVICE_GPIO_CFG_EPWMxA);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_EPWMxA, GPIO_PIN_TYPE_STD);

    GPIO_setPinConfig(DEVICE_GPIO_CFG_EPWMxB);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_EPWMxB, GPIO_PIN_TYPE_STD);

#ifndef MOTOR
    //
    // Setup ePWM1 to generate a 5 kHz signal to be an input to the eQEP
    //
    initEPWM();

#endif
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
    EPWM_setCounterCompareValue(DEVICE_PERIPHERAL_BASE_EPWM, 
                                EPWM_COUNTER_COMPARE_A, PRD_VAL/2);
    EPWM_setCounterCompareValue(DEVICE_PERIPHERAL_BASE_EPWM, 
                                EPWM_COUNTER_COMPARE_B, 0);

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
    // Set action qualifier behavior on compare B events
    // - EPWM1B --> 1 when CTR = PRD and increasing
    // - EPWM1B --> 0 when CTR = 0 and decreasing
    //
    EPWM_setActionQualifierAction(DEVICE_PERIPHERAL_BASE_EPWM, EPWM_AQ_OUTPUT_B,
                                EPWM_AQ_OUTPUT_HIGH,
                                EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);
    EPWM_setActionQualifierAction(DEVICE_PERIPHERAL_BASE_EPWM, EPWM_AQ_OUTPUT_B,
                                EPWM_AQ_OUTPUT_LOW,
                                EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);

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
    EPWM_setTimeBaseCounterMode(DEVICE_PERIPHERAL_BASE_EPWM,  
                                EPWM_COUNTER_MODE_UP_DOWN);

    //
    // Sync the ePWM time base clock
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);
}

//
// eqep1 ISR- interrupts once per ePWM period
//
__interrupt void
INT_myEQEP0_ISR(void)
{
    uint32_t temp = 0, newcount = 0 ;
    
    count++; // increment count value so to wait for frequency saturation

    newcount = EQEP_getPositionLatch(myEQEP0_BASE); // new position counter value
    temp = newcount;

   //
   // Gets direction of rotation of motor
   //
   dir = EQEP_getDirection(myEQEP0_BASE);

   //
   // Calculates the number of position in unit time based on
   // motor's direction of rotation
   //
   if (dir > 0 ){
       if (newcount >= oldcount)
            newcount = newcount - oldcount;
        else
            newcount = (0xFFFFFFFF - oldcount) + newcount;
        }
   else {
        if (newcount <= oldcount)
            newcount = oldcount - newcount;
        else
            newcount = (0xFFFFFFFF - newcount) + oldcount;
        }

   //
   // Stores the current position count value to oldcount variable
   //
   oldcount = temp;

   //
   // Simulated Frequency and speed calculation
   //
   freq = (newcount * (uint32_t)1000000U)/((uint32_t)UNIT_PERIOD);
   speed = (freq * 60)/4000.0f;

   //
   // Compares the measured quadrature simulated frequency with input quadrature
   // frequency and if difference is within the measurement resolution
   // (1/10ms = 100Hz) then pass = 1 else fail = 1
   //
#ifndef MOTOR
   if (count >= 2){
        if (((freq - PWM_CLK * 4) < 100) && ((freq - PWM_CLK * 4) > -100)){
            pass = 1; fail = 0;
        }
        else {
            fail = 1; pass = 0;
        }
    }
#endif

   //
   // Clear interrupt flag and issue ACK
   //
   EQEP_clearInterruptStatus(myEQEP0_BASE,EQEP_INT_UNIT_TIME_OUT|EQEP_INT_GLOBAL);
   Interrupt_clearACKGroup(INT_myEQEP0_INTERRUPT_ACK_GROUP);
 }

//
// End of File
//

