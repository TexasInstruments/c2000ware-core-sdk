//#############################################################################
//
// FILE:   cla_ex5_adc_just_in_time.c
//
// TITLE:  Just-in-time ADC sampling with CLA
//
//! \addtogroup driver_example_list
//! <h1> Just-in-time ADC sampling with CLA </h1>
//!
//! This example showcases how to utilize early-interrupt feature of ADC
//! in combination with the low interrupt response of CLA to enable faster
//! system response and achieve high frequency control loops. EPWM1 is
//! configured to generate a PWM output signal of frequency 1 MHz and this
//! is also used to trigger the ADC sampling at each cycle. ADCA is
//! configured to sample the input on Channel 0 and to generate the early
//! interrupt at the end of S/H + offset cycles. This interrupt is used to
//! trigger the CLA control task. The CLA task implements the control logic
//! to update the duty of the PWM output based on reading the ADC sample data
//! just-in-time i.e. as soon as the ADC results gets latched.The early
//! interrupt feature and low interrupt latency of CLA allows to do some
//! pre-processing as well before reading the ADC data and still completes
//! updating the PWM output before the next interrupts comes in i.e. data read
//! and PWM update is done within a 1 MHz cycle. For illustration purposes,
//! 3-point moving average filter is used to simulate some processing and few
//! steps of the filtering code are done before reading the ADC result which
//! we consider as pre-processing code. The ADC interrupt offset is programmed
//! based on the cycles consumed by the pre-processing code.
//!
//! The calculation for interrupt offset value is as follows :-
//!   -ADC acquisition cycles programmed = 10 SYSCLKS
//!   -Conversion time for 12-bit data = 10.5 ADCCLKS =  N = 42 SYSCLKS
//!   -CLA task trigger to first instruction in Fetch delay = 4
//!   -Let the interrupt offset value be 'x'
//!   -The code inside CLA control task before ADC read takes below cycles :
//!                     Setting up profiling gpio : 3 cycles
//!                     Pre-processing : 13 cycles
//!                      Total = 3 + 13 = 16 cycles
//!
//! As described in device TRM, in order to read just-in-time the total delay
//! before reading ADC should be (N-2) cycles = 40 i.e.
//!                    : x + 4 + 16 = 40
//!                    : x = 20
//!
//! NOTE :- The optimization is off for this project and the cycles quoted above
//!         corresponds to that case.
//!
//! GPIO2 is used for profiling purposes. GPIO2 is set at the beginning of
//! CLA task 1 and is reset at the end of the task. Thus ON time of GPIO2
//! indicates the CLA activity. In order to validate the example functionality
//! , observe the GPIO0 (PWM output) and GPIO2 (profiling GPIO) on CRO.
//! The cycles difference between the rising edge of the GPIO0 and GPIO2
//! indicate the total delay from the time of ADC trigger to setting up of
//! profiling GPIO inside CLA task which should be around 44 cycles (440 ns)
//! based on the above calculation.
//!
//! \b External \b Connections \n
//!  - Provide constant DC input on ADCA0 for quick validation.
//!       GND -> Should observe PWM output duty = 0.1
//!       3.3V -> Should observe PWM output duty = 0.9
//!    Can also provide analog input in range 0 - 3.3V upto fs / 10 = 100 KHz for
//!    observing continuous duty variations
//!
//!  - Observe GPIO0 on oscilloscope
//!  - Observe GPIO2 on oscilloscope
//!
//! \b Watch \b Variables \n
//!  - None
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
#include "cla_ex5_adc_just_in_time_shared.h"
#include "board.h"

//
// Function Prototypes
//
void initEPWM(void);
void initCLA(void);
void initADC(void);
void initADCSOC(void);
void setupProfileGpio(void);
__attribute__((interrupt))  void cla1Isr1(void);

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
    // GPIO0 is set to EPWM1A
    //
    GPIO_setControllerCore(0, GPIO_CORE_CPU1);
    GPIO_setPadConfig(0,GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_0_EPWM1_A);

    //
    // GPIO2 is configured as output and CLA is assigned its controller
    //
    setupProfileGpio();

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
    // Initialize EPWM1 module
    //
    initEPWM();

    //
    // Initialize ADC
    //
    initADC();
    initADCSOC();

    //
    // Initialize resources
    //
    Board_init();
    initCLA();

    //
    // Enable global interrupts.
    //
    EINT;

    //
    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    for(;;)
    {

    }
}

// ADC Initialization
//
// Function to configure and power up ADC A
//
void initADC(void)
{
    //
    // Setup VREF as internal
    //
    ADC_setVREF(ADCA_BASE, ADC_REFERENCE_INTERNAL, ADC_REFERENCE_3_3V);

    //
    // Set ADCCLK divider to /4
    //
    ADC_setPrescaler(ADCA_BASE, ADC_CLK_DIV_4_0);

    //
    // Set pulse positions to late
    //
    ADC_setInterruptPulseMode(ADCA_BASE, ADC_PULSE_END_OF_ACQ_WIN);

    //
    // Set interrupt offset delay as 20 cycles based on the calculation
    // shown in example header
    //
    ADC_setInterruptCycleOffset(ADCA_BASE, 20);

    //
    // Power up the ADCs and then delay for 1 ms
    //
    ADC_enableConverter(ADCA_BASE);

    DEVICE_DELAY_US(1000);
}

//
// ADC SOC Initialization
//
// Description: This function will configure the ADC, channel A0 to start
// its conversion on a trigger from EPWM1 (EPMW1SOCA). The ADC will sample this
// channel continuously. After each conversion it will assert ADCINT1, which
// is then used to trigger task 1 of the CLA
//
void initADCSOC(void)
{
    //
    // Configure SOC0 of ADCA
    // - SOC0 will be triggered by EPWM1SOCA
    // - SOC0 will convert pin A0 with a sample window of 10 SYSCLK cycles.
    // - EOC0 will be generated at the end of conversion
    // - SOC0 will sample on each trigger regardless of the interrupt flag
    //
    ADC_setupSOC(ADCA_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_EPWM1_SOCA,
                 ADC_CH_ADCIN0, 10);
    ADC_enableContinuousMode(ADCA_BASE, ADC_INT_NUMBER1);

    //
    // Set SOC0 to set the interrupt 1 flag. Enable the interrupt and make
    // sure its flag is cleared.
    //
    ADC_setInterruptSource(ADCA_BASE, ADC_INT_NUMBER1, ADC_SOC_NUMBER0);
    ADC_enableInterrupt(ADCA_BASE, ADC_INT_NUMBER1);
    ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1);
}

//
// EPWM Initialization
//
// Description: EPWM1A will run at EPWM1_FREQ (1 MHz) and is used to generate
// the PWM output. It also serves as the sampling clock for ADC channel A0
// The default time base for the EPWM module is half the system clock
//
void initEPWM(void)
{
    //
    // Set up EPWM1 to
    // - run on a base clock of SYSCLK
    // - have a period of EPWM1_PERIOD
    // - run in count up mode
    // - initialize the COMPA register to realize 0.1 duty
    //
    EPWM_setClockPrescaler(EPWM1_BASE, EPWM_CLOCK_DIVIDER_1,
                           EPWM_HSCLOCK_DIVIDER_1);
    EPWM_setTimeBasePeriod(EPWM1_BASE, EPWM1_PERIOD - 1U);
    EPWM_setCounterCompareValue(EPWM1_BASE, EPWM_COUNTER_COMPARE_A, (0.1f * EPWM1_PERIOD));
    EPWM_setTimeBaseCounterMode(EPWM1_BASE, EPWM_COUNTER_MODE_UP);
    EPWM_setTimeBaseCounter(EPWM1_BASE, 0U);

    //
    // Configuring action-qualifiers for EPWM1
    //
    EPWM_setActionQualifierAction(EPWM1_BASE, EPWM_AQ_OUTPUT_A,
                         EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    EPWM_setActionQualifierAction(EPWM1_BASE, EPWM_AQ_OUTPUT_A,
                             EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);

    //
    // Enabling Shadow mode
    //
    EPWM_setCounterCompareShadowLoadMode(EPWM1_BASE, EPWM_COUNTER_COMPARE_A,
                                         EPWM_COMP_LOAD_ON_SYNC_CNTR_ZERO);

    //
    // Enable SOC-A and set it to assert when the counter hits
    // zero. It asserts on every event
    //
    EPWM_enableADCTrigger(EPWM1_BASE, EPWM_SOC_A);
    EPWM_setADCTriggerSource(EPWM1_BASE, EPWM_SOC_A, EPWM_SOC_TBCTR_ZERO);
    EPWM_setADCTriggerEventPrescale(EPWM1_BASE, EPWM_SOC_A, 1U);

    //
    // EPWM 1 should run freely in emulation mode
    //
    EPWM_setEmulationMode(EPWM1_BASE, EPWM_EMULATION_FREE_RUN);

}

//
// CLA Initialization
//
//
void initCLA(void)
{
    //
    // Force task 8, the one time initialization task to initialize
    // the CLA global variables
    //
    CLA_forceTasks(CLA1_BASE, CLA_TASKFLAG_8);
}

//
// Setting up GPIO2 for profiling and set CLA as its controller
//
void setupProfileGpio(void)
{
        GPIO_setDirectionMode(2,GPIO_DIR_MODE_OUT);
        GPIO_setQualificationMode(2,GPIO_QUAL_SYNC);
        GPIO_setPinConfig(GPIO_2_GPIO2);
        GPIO_writePin(2,0);
        GPIO_setControllerCore(2, GPIO_CORE_CPU1_CLA1);
}
