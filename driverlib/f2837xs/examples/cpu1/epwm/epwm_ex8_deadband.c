//#############################################################################
//
// FILE:   epwm_ex8_deadband.c
//
// TITLE:  ePWM Using Deadband Submodule.
//
//! \addtogroup driver_example_list
//! <h1>ePWM Deadband</h1>
//!
//! This example configures ePWM1 through ePWM6 as follows
//!  - ePWM1 with Deadband disabled (Reference)
//!  - ePWM2 with Deadband Active High
//!  - ePWM3 with Deadband Active Low
//!  - ePWM4 with Deadband Active High Complimentary
//!  - ePWM5 with Deadband Active Low Complimentary
//!  - ePWM6 with Deadband Output Swap (switch A and B outputs)
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
//! - GPIO8 EPWM5A
//! - GPIO9 EPWM5B
//! - GPIO10 EPWM6A
//! - GPIO11 EPWM6B
//!
//! \b Watch \b Variables \n
//! - None.
//
//
//#############################################################################
//
// $Release Date:  $
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

#define EPWM_TIMER_TBPRD    2000UL

//
// Function Prototypes
//
void initEPWMWithoutDB(uint32_t base);
void setupEPWMActiveHigh(uint32_t base);
void setupEPWMActiveLow(uint32_t base);
void setupEPWMActiveHighComplementary(uint32_t base);
void setupEPWMActiveLowComplementary(uint32_t base);
void setupEPWMOutputSwap(uint32_t base);

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
    // Configure ePWMs
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
    // Initialize ePWM1
    //
    initEPWMWithoutDB(myEPWM1_BASE);

    //
    // Initialize ePWM2 Active High
    //
    initEPWMWithoutDB(myEPWM2_BASE);
    setupEPWMActiveHigh(myEPWM2_BASE);

    //
    // Initialize ePWM3 Active Low
    //
    initEPWMWithoutDB(myEPWM3_BASE);
    setupEPWMActiveLow(myEPWM3_BASE);

    //
    // Initialize ePWM4 Active High Complimentary
    //
    initEPWMWithoutDB(myEPWM4_BASE);
    setupEPWMActiveHighComplementary(myEPWM4_BASE);

    //
    // Initialize ePWM5 Active Low Complimentary
    //
    initEPWMWithoutDB(myEPWM5_BASE);
    setupEPWMActiveLowComplementary(myEPWM5_BASE);

    //
    // Initialize ePWM6 Output Swap (switch A and B outputs)
    //
    initEPWMWithoutDB(myEPWM6_BASE);
    setupEPWMOutputSwap(myEPWM6_BASE);

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


void setupEPWMOutputSwap(uint32_t base)
{

    //
    // Disable RED
    //
    EPWM_setDeadBandDelayMode(base, EPWM_DB_RED, false);

    //
    // Disable FED
    //
    EPWM_setDeadBandDelayMode(base, EPWM_DB_FED, false);

    //
    // Switch Output A with Output B
    //
    EPWM_setDeadBandOutputSwapMode(base, EPWM_DB_OUTPUT_A, true);
    EPWM_setDeadBandOutputSwapMode(base, EPWM_DB_OUTPUT_B, true);

}

void setupEPWMActiveHigh(uint32_t base)
{
    //
    // Use EPWMA as the input for both RED and FED
    //
    EPWM_setRisingEdgeDeadBandDelayInput(base, EPWM_DB_INPUT_EPWMA);
    EPWM_setFallingEdgeDeadBandDelayInput(base, EPWM_DB_INPUT_EPWMA);

    //
    // Set the RED and FED values
    //
    EPWM_setFallingEdgeDelayCount(base, 200);
    EPWM_setRisingEdgeDelayCount(base, 400);

    //
    // Do not invert the delayed outputs (AH)
    //
    EPWM_setDeadBandDelayPolarity(base, EPWM_DB_RED, EPWM_DB_POLARITY_ACTIVE_HIGH);
    EPWM_setDeadBandDelayPolarity(base, EPWM_DB_FED, EPWM_DB_POLARITY_ACTIVE_HIGH);

    //
    // Use the delayed signals instead of the original signals
    //
    EPWM_setDeadBandDelayMode(base, EPWM_DB_RED, true);
    EPWM_setDeadBandDelayMode(base, EPWM_DB_FED, true);

    //
    // DO NOT Switch Output A with Output B
    //
    EPWM_setDeadBandOutputSwapMode(base, EPWM_DB_OUTPUT_A, false);
    EPWM_setDeadBandOutputSwapMode(base, EPWM_DB_OUTPUT_B, false);

}

void setupEPWMActiveLowComplementary(uint32_t base)
{
    //
    // Use EPWMA as the input for both RED and FED
    //
    EPWM_setRisingEdgeDeadBandDelayInput(base, EPWM_DB_INPUT_EPWMA);
    EPWM_setFallingEdgeDeadBandDelayInput(base, EPWM_DB_INPUT_EPWMA);

    //
    // Set the RED and FED values
    //
    EPWM_setFallingEdgeDelayCount(base, 200);
    EPWM_setRisingEdgeDelayCount(base, 400);

    //
    // Invert only the Rising Edge delayed output (ALC)
    //
    EPWM_setDeadBandDelayPolarity(base, EPWM_DB_RED, EPWM_DB_POLARITY_ACTIVE_LOW);
    EPWM_setDeadBandDelayPolarity(base, EPWM_DB_FED, EPWM_DB_POLARITY_ACTIVE_HIGH);

    //
    // Use the delayed signals instead of the original signals
    //
    EPWM_setDeadBandDelayMode(base, EPWM_DB_RED, true);
    EPWM_setDeadBandDelayMode(base, EPWM_DB_FED, true);

    //
    // DO NOT Switch Output A with Output B
    //
    EPWM_setDeadBandOutputSwapMode(base, EPWM_DB_OUTPUT_A, false);
    EPWM_setDeadBandOutputSwapMode(base, EPWM_DB_OUTPUT_B, false);

}


void setupEPWMActiveHighComplementary(uint32_t base)
{
    //
    // Use EPWMA as the input for both RED and FED
    //
    EPWM_setRisingEdgeDeadBandDelayInput(base, EPWM_DB_INPUT_EPWMA);
    EPWM_setFallingEdgeDeadBandDelayInput(base, EPWM_DB_INPUT_EPWMA);

    //
    // Set the RED and FED values
    //
    EPWM_setFallingEdgeDelayCount(base, 200);
    EPWM_setRisingEdgeDelayCount(base, 400);

    //
    // Invert only the Falling Edge delayed output (AHC)
    //
    EPWM_setDeadBandDelayPolarity(base, EPWM_DB_RED, EPWM_DB_POLARITY_ACTIVE_HIGH);
    EPWM_setDeadBandDelayPolarity(base, EPWM_DB_FED, EPWM_DB_POLARITY_ACTIVE_LOW);

    //
    // Use the delayed signals instead of the original signals
    //
    EPWM_setDeadBandDelayMode(base, EPWM_DB_RED, true);
    EPWM_setDeadBandDelayMode(base, EPWM_DB_FED, true);

    //
    // DO NOT Switch Output A with Output B
    //
    EPWM_setDeadBandOutputSwapMode(base, EPWM_DB_OUTPUT_A, false);
    EPWM_setDeadBandOutputSwapMode(base, EPWM_DB_OUTPUT_B, false);

}



void setupEPWMActiveLow(uint32_t base)
{
    //
    // Use EPWMA as the input for both RED and FED
    //
    EPWM_setRisingEdgeDeadBandDelayInput(base, EPWM_DB_INPUT_EPWMA);
    EPWM_setFallingEdgeDeadBandDelayInput(base, EPWM_DB_INPUT_EPWMA);

    //
    // Set the RED and FED values
    //
    EPWM_setFallingEdgeDelayCount(base, 200);
    EPWM_setRisingEdgeDelayCount(base, 400);

    //
    // INVERT the delayed outputs (AL)
    //
    EPWM_setDeadBandDelayPolarity(base, EPWM_DB_RED, EPWM_DB_POLARITY_ACTIVE_LOW);
    EPWM_setDeadBandDelayPolarity(base, EPWM_DB_FED, EPWM_DB_POLARITY_ACTIVE_LOW);

    //
    // Use the delayed signals instead of the original signals
    //
    EPWM_setDeadBandDelayMode(base, EPWM_DB_RED, true);
    EPWM_setDeadBandDelayMode(base, EPWM_DB_FED, true);

    //
    // DO NOT Switch Output A with Output B
    //
    EPWM_setDeadBandOutputSwapMode(base, EPWM_DB_OUTPUT_A, false);
    EPWM_setDeadBandOutputSwapMode(base, EPWM_DB_OUTPUT_B, false);

}


//
// initEPWM - Configure ePWM1
//
void initEPWMWithoutDB(uint32_t base)
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
