//#############################################################################
//
// FILE:   erad_ex4_profileinterrupts_cla.c
//
// TITLE:  ERAD Profile Interrupts CLA Example
//
//! \addtogroup driver_example_list
//! <h1> ERAD Profile Interrupts CLA </h1>
//!
//! This example configures EPWM1A to run at 1 KHz (period = 1 ms) to
//! trigger a start-of-conversion on ADC channel A0. This channel will,
//! in turn, sample EPWM4A which is set to run at 100Hz.
//! At the end-of-conversion the ADC interrupt is fired. The interrupt signal
//! will be used to trigger a CLA task that runs an FIR filter. The filter
//! is designed to be low pass with a cutoff frequency of 100Hz; it will remove
//! the odd harmonics in the input signal smoothing the square wave to a
//! sinusoidal shape.
//! The CLA background task will continuously buffer the filtered output in a
//! circular buffer.
//!
//! This example also utilizes the ERAD peripheral to profile the Interrupt
//! Service Routine (ISR) cla1ISR1 (on the C28x core). The ISR contains a loop
//! that simulates storing a random amount of data to a location in order to
//! introduce variability into the cycle measurements. The ERAD peripheral is
//! also configured to count the number of times the system event CLA_INTERRUPT1
//! occurs.
//!
//! To properly use the provided ERAD script, the following variables must be
//! set in the scripting environment prior to launching the ERAD script:
//!
//! - var PROJ_NAME = "erad_debugger_ex4_profileinterrupts_cla"
//! - var PROJ_WKSPC_LOC = "<proj_workspace_path>"
//! - var PROJ_CONFIG = "<name of active configuration [CPU1_FLASH|CPU1_RAM]>"
//!
//! To run the ERAD script, use the following command in the scripting console:
//!
//! - loadJSFile("<proj_workspace_path>\\erad_debugger_ex4_profileinterrupts_cla\\erad_ex4_profile_interrupts_cla.js", 0);
//!
//! Note that the script must be run after loading and running the .out on the
//! C28x core.
//!
//! The included JavaScript file, erad_ex4_profile_interrupts_cla.js, uses Debug Server
//! Scripting (DSS) features. For information on using the DSS, please visit:
//! http://software-dl.ti.com/ccs/esd/documents/users_guide/sdto_dss_handbook.html
//!
//! This example uses 4 HW breakpoints and 2 counters:
//!  - HWBP_1 : PC = start address of cla1Isr1
//!  - HWBP_2 : PC = end address of cla1Isr1
//!  - CTM_1  : Used to count the cla1Isr1 execution cycles.
//!             Configured in start-stop mode with start event as HWBP_1 and
//!             stop event as HWBP_2
//!  - CTM_2  : Used to count the number of times the system event
//!             CLA_INTERRUPT1 event has occurred.
//!             Configured in rising-edge count mode with counting input as
//!             system event CLA_INTERRUPT1 (INP_SEL[26])
//!
//! \b External \b Connections \n
//!  - connect A0 to EPWM4A
//!
//! \b Watch \b Variables \n
//!  - ISR_count - A counter that signifies how many times cla1ISR1 executes
//!
//! \b Profiling \b Script \b Output
//!  - Current ISR cycle count (CTM_1)
//!  - Max ISR cycle count (maximum value of CTM_1)
//!  - Interrupt occurrence count (CTM_2)
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
#include "erad_ex4_background_task.h"

//
// Defines
//
#define EPWM_CLKDIV         64UL

#define EPWM1_FREQ          1000UL
#define EPWM4_FREQ          100UL
#define EPWM1_PERIOD        (uint16_t)(DEVICE_SYSCLK_FREQ /                    \
                                       (EPWM_CLKDIV * EPWM1_FREQ))
#define EPWM4_PERIOD        (uint16_t)(DEVICE_SYSCLK_FREQ /                    \
                                       (EPWM_CLKDIV * 2U * EPWM4_FREQ))
#define EPWM4_DUTY_CYCLE    (EPWM4_PERIOD / 2)

//
// Globals
//

//
// Background Task (C) Variables
// Circular buffer to store filtered output
//
#pragma DATA_SECTION(buffer, "Cla1DataRam");
volatile float buffer[BUFFER_SIZE];

//
// Linker Defined variables
//
extern uint32_t Cla1ProgRunStart, Cla1ProgLoadStart, Cla1ProgLoadSize;
extern uint32_t Cla1ConstRunStart, Cla1ConstLoadStart, Cla1ConstLoadSize;

//
// Pre-chosen Pseudo Random Generator constants
//
const uint16_t PseudoRand_multiplier = 31821;
const uint16_t PseudoRand_increment = 13849;
uint16_t PseudoRand_seed = 21845;

//
// ISR Counter
//
uint32_t ISR_count = 0;

//
// Function Prototypes
//
void initADC(void);
void initADCSOC(void);
void initEPWM(void);
void initCLA(void);
__attribute__((interrupt))  void cla1Isr1(void);
uint16_t generatePseudoRand16(uint16_t *);

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
    GPIO_setMasterCore(0, GPIO_CORE_CPU1);
    GPIO_setPadConfig(0,GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_0_EPWM1_A);

    //
    // GPIO6 is set to EPWM4A
    //
    GPIO_setMasterCore(6, GPIO_CORE_CPU1);
    GPIO_setPadConfig(6,GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_6_EPWM4_A);

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
    // Map the ISR to the CLA end-of-task interrupt.
    //
    Interrupt_register(INT_CLA1_1, cla1Isr1);

    //
    // Setup the CLA and ADC
    //
    initCLA();
    initADC();
    initADCSOC();

    //
    // Disable sync(Freeze clock to PWM as well)
    //
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);
    initEPWM();

    //
    // Enable the interrupts in the PIE: Group 11 interrupt 1.
    //
    Interrupt_enable(INT_CLA1_1);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP11);

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
    ADC_setInterruptPulseMode(ADCA_BASE, ADC_PULSE_END_OF_CONV);

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
// is then used to trigger task 1 of the CLA (the filter)
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
// Description: EPWM1A will run at EPWM1_FREQ Hz and serves as the sampling
// clock for ADC channel A0 which will be sampling the slower running EPWM4A
// (at EPWM4_FREQ Hz). The default time base for the EPWM module is half the
// system clock i.e.
//       TBCLK = SYSCLKOUT
// EPWM1A will be setup in count-up mode and an event generated every period
// this event will trigger the ADC to start sampling on channel A0
// EPWM4A is setup for updown count mode with CMPA level at the half period
// point giving a 50% duty cycle square wave at EPWM4_FREQ Hz
// For a desired PWM frequency F_pwm (1/T_pwm), we have
//       T_pwm = 2 x TBPRD / TBCLK
//       TBPRD = TBCLK/(2*F_pwm)
// For e.g. F_pwm = 10KHz, TBCLK = 50e6
//       TBPRD = 50e6/(2*10e3)
//             = 2500
// For e.g. F_pwm = 1KHz, TBCLK = 50e6
//       TBPRD = 50e6/(2*1e3)
//             = 25000
// For e.g. F_pwm = 100Hz, TBCLK = 50e6
//       TBPRD = 50e6/(2*1e2)
//             = 250000
//
void initEPWM(void)
{
    //
    // Set up EPWM1 to
    // - run on a base clock of SYSCLK/64
    // - have a period of EPWM1_PERIOD
    // - run in count up mode
    //
    EPWM_setClockPrescaler(EPWM1_BASE, EPWM_CLOCK_DIVIDER_8,
                           EPWM_HSCLOCK_DIVIDER_8);
    EPWM_setTimeBasePeriod(EPWM1_BASE, EPWM1_PERIOD);
    EPWM_setTimeBaseCounterMode(EPWM1_BASE, EPWM_COUNTER_MODE_UP);
    EPWM_setTimeBaseCounter(EPWM1_BASE, 0U);

    //
    // Enable SOC-A and set it to assert when the counter hits
    // zero. It asserts on every event
    //
    EPWM_enableADCTrigger(EPWM1_BASE, EPWM_SOC_A);
    EPWM_setADCTriggerSource(EPWM1_BASE, EPWM_SOC_A, EPWM_SOC_TBCTR_ZERO);
    EPWM_setADCTriggerEventPrescale(EPWM1_BASE, EPWM_SOC_A, 1U);

    //
    // EPWM1 should toggle each time its counter hits zero
    //
    EPWM_setActionQualifierAction(EPWM1_BASE, EPWM_AQ_OUTPUT_A,
            EPWM_AQ_OUTPUT_TOGGLE, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);

    //
    // Set up EPWM4 to
    // - run on a base clock of SYSCLK/64
    // - have a period of EPWM4_PERIOD
    // - run in count up/down mode
    // - have its CMPA value set for a 50% duty cycle
    //
    EPWM_setClockPrescaler(EPWM4_BASE, EPWM_CLOCK_DIVIDER_8,
                           EPWM_HSCLOCK_DIVIDER_8);
    EPWM_setTimeBasePeriod(EPWM4_BASE, EPWM4_PERIOD);
    EPWM_setTimeBaseCounterMode(EPWM4_BASE, EPWM_COUNTER_MODE_UP_DOWN);
    EPWM_setTimeBaseCounter(EPWM4_BASE, 0U);
    EPWM_setCounterCompareValue(EPWM4_BASE, EPWM_COUNTER_COMPARE_A,
            EPWM4_DUTY_CYCLE);

    //
    // On compare A, when counting up, pull the EPWM A output high
    // On compare A, when counting down, pull the EPWM A output low
    //
    EPWM_setActionQualifierAction(EPWM4_BASE, EPWM_AQ_OUTPUT_A,
            EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    EPWM_setActionQualifierAction(EPWM4_BASE, EPWM_AQ_OUTPUT_A,
                EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);

    //
    // EPWM 1 and 4 should run freely in emulation mode
    //
    EPWM_setEmulationMode(EPWM1_BASE, EPWM_EMULATION_FREE_RUN);
    EPWM_setEmulationMode(EPWM4_BASE, EPWM_EMULATION_FREE_RUN);
}

//
// generatePseudoRand16 - Generate a pseudo random 16-bit number by passing a
// start value or "seed". This generator is a linear congruential pseudo random
// generator, which is very fast. The basic calculation is:
//
// randNum(n) = ((randNum(n-1) * multiplier) + increment) modulo M
//
uint16_t
generatePseudoRand16(uint16_t *seed)
{
    //
    // Perform calculation. Mask off bottom bits in lieu of modulus operation
    //
    *seed = ((uint32_t)*seed * PseudoRand_multiplier + PseudoRand_increment)
            & 0xFFFF;
    return(*seed);
}

//
// CLA Initialization
//
// Description: This function will
// - copy over code and const from flash to CLA program and data ram
//   respectively
// - Initialize the task vectors (MVECTx)
// - setup each task's trigger
// - enable each individual task
// - map program and data spaces to the CLA
// - run any one-time initialization task
// Please note that the CLA can only run code and access data that is in RAM.
// the user must assign constants (tables) to FLASH, and copy them over to
// RAM at run-time. They must be copied to a RAM that lies in the address space
// of the CLA, and prior to giving the CLA control over that space
//
void initCLA(void)
{
    //
    // Copy the program and constants from FLASH to RAM before configuring
    // the CLA
    //
#if defined(_FLASH)
    memcpy((uint32_t *)&Cla1ProgRunStart, (uint32_t *)&Cla1ProgLoadStart,
           (uint32_t)&Cla1ProgLoadSize);
    memcpy((uint32_t *)&Cla1ConstRunStart, (uint32_t *)&Cla1ConstLoadStart,
        (uint32_t)&Cla1ConstLoadSize );
#endif //defined(_FLASH)

    //
    // CLA Program will reside in RAMLS0 and data in RAMLS1, RAMLS2
    //
    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS0, MEMCFG_LSRAMMASTER_CPU_CLA1);
    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS1, MEMCFG_LSRAMMASTER_CPU_CLA1);
    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS2, MEMCFG_LSRAMMASTER_CPU_CLA1);
    MemCfg_setCLAMemType(MEMCFG_SECT_LS0, MEMCFG_CLA_MEM_PROGRAM);
    MemCfg_setCLAMemType(MEMCFG_SECT_LS1, MEMCFG_CLA_MEM_DATA);
    MemCfg_setCLAMemType(MEMCFG_SECT_LS2, MEMCFG_CLA_MEM_DATA);
#if defined(_FLASH)
    //
    // In Flash config, constants are loaded in Flash and then copied to LS3.
    // CLA reads the constants from LS3.
    //
    MemCfg_setCLAMemType(MEMCFG_SECT_LS3, MEMCFG_CLA_MEM_DATA);
    MemCfg_setLSRAMMasterSel(MEMCFG_SECT_LS3, MEMCFG_LSRAMMASTER_CPU_CLA1);
#endif //defined(_FLASH)

//
// Suppressing #770-D conversion from pointer to smaller integer
// The CLA address range is 16 bits so the addresses passed to the MVECT
// registers will be in the lower 64KW address space. Turn the warning
// back on after the MVECTs are assigned addresses
//
#pragma diag_suppress=770

    //
    // Assign the task vectors and set the triggers for task 1 and 7
    //
    CLA_mapTaskVector(CLA1_BASE, CLA_MVECT_1, (uint16_t)&Cla1Task1);
    CLA_mapTaskVector(CLA1_BASE, CLA_MVECT_7, (uint16_t)&Cla1Task7);
    CLA_setTriggerSource(CLA_TASK_1, CLA_TRIGGER_ADCA1);
    CLA_setTriggerSource(CLA_TASK_7, CLA_TRIGGER_SOFTWARE);

    //
    // Enable Tasks 1 and 7. Since task 7 is forced in software, we must
    // enable software forcing (IACKE)
    //
    CLA_enableTasks(CLA1_BASE, (CLA_TASKFLAG_1 | CLA_TASKFLAG_7));
    CLA_enableIACK(CLA1_BASE);

    //
    // The background task will be triggered by software; it shares
    // the same trigger source as task 8. Disable the hardware triggering
    // mechanism for the background task (if it is enabled) and then
    // set the trigger source for task 8 to 0 indicating a software
    // trigger.
    //
    // Enable the background task and start it. Enabling the background
    // task disables task 8.
    //
    CLA_mapBackgroundTaskVector(CLA1_BASE, (uint16_t)&Cla1BackgroundTask);
#pragma diag_warning=770
    CLA_disableHardwareTrigger(CLA1_BASE);
    CLA_setTriggerSource(CLA_TASK_8, CLA_TRIGGER_SOFTWARE);
    CLA_enableBackgroundTask(CLA1_BASE);
    CLA_startBackgroundTask(CLA1_BASE);

    //
    // Force task 7, the one time initialization task
    //
    CLA_forceTasks(CLA1_BASE, CLA_TASKFLAG_7);
}

//
// CLA Task 1 End-of-Task Interrupt Service Routine
//
// Description: This ISR is run every time task 1 completes. It continuously
// takes the filtered values from the CLA and stores it to a circular buffer
//
__attribute__((interrupt))  void cla1Isr1 ()
{
    //
    // Clear the ADC interrupt flag so the next SOC can occur
    //
    ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1);

    //
    // Acknowledge the end-of-task interrupt for task 1
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP11);

    //
    // Simulate storing data to a location. "volatile" keyword ensures this is
    // not optimized out by the compiler.
    //
    volatile uint32_t output;

    //
    // Generate a random number.
    //
    uint16_t count = generatePseudoRand16(&PseudoRand_seed);

    //
    // Simulate a task that can take some time to complete. Loop a "random"
    // number of times and store values to a location.
    //
    uint32_t i;
    for(i = 0; i < count; i++)
    {
        output = i;
    }

    //
    // Increment a counter signifying that ISR has executed
    //
    ISR_count++;
}

//
// End of File
//
