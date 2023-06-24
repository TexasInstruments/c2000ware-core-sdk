//#############################################################################
//
// FILE:   cla_ex7_shared_resource_handling.c
//
// TITLE:  Handling shared resources across C28x and CLA
//
//! \addtogroup driver_example_list
//! <h1>  Handling shared resources across C28x and CLA </h1>
//!
//! This example showcases how to handle shared resource challenges across
//! C28x and CLA. As the peripherals are shared between CLA and the CPU,
//! overlapping read-modify-write to the registers by them can lead to data
//! race conditions ultimately leading to data violation or incorrect
//! functionality. In this example, CPU ISR and CLA tasks runs independently.
//! CPU ISR gets triggered by EPWM4 @10KHz and toggles the EPWM1B output via
//! software by controlling CSFB bits of AQCSFRC. CLA task gets triggered by
//! EPWM5 @100Khz and toggles the EPWM1A output via software by controlling
//! CSFA bits of AQCSFRC. Thus in this process both CPU and CLA do read-modify
//! -write to AQCSFRC register independently at different frequencies so there
//! is chance of race condition and updates due to one of them can get lost/.
//! overwritten. This can be clearly observed by updating "phase_shift_ON" to 
//! 0U and probing the EPWM1A and 1B outputs on a scope.
//!
//! This is a standard critical section problem and can be handled by software
//! handshaking mechanism like mutex etc. But most of the real-time control
//! applications are time-sensitive and cannot afford addition software overhead
//! hence this example suggests an alternative hardware based technique to avoid
//! shared resource conflicts between CPU and CLA. The phase shifting mechanism
//! of the EPWM modules is utilized to schedule the CLA task and CPU ISR as
//! desired. EPWM4 generates a synchronous pulse every ZERO event and provides
//! a phase shift of 20 cycles to EPWM5. This way both CLA task and C28x ISR
//! runs at original frequencies i.e. 100KHz and 10KHz but CLA task leads with
//! a phase offset of 20 cycles wrt CPU ISR. Hence concurrent read-modify-writes
//! to AQCSFRC never happens and the EPWM1A and EPWM1B outputs behave as desired
//! i.e. consistent 50 KHz PWM output on EPWM1A and 5 KHz PWM output on EPWM1B
//! with a duty ~50% on both should be generated. In order to utilize this phase
//! shifting mechanism in this example, please make sure "phase_shift_ON" is
//! set to 1.
//!
//!
//! \b External \b Connections \n
//!  - Observe GPIO0 (EPWM1A Output) on oscilloscope
//!  - Observe GPIO1 (EPWM1B Output) on oscilloscope
//!  - Observe GPIO2 (CLA Task Profiling) on oscilloscope
//!  - Observe GPIO3 (CPU ISR Profiling) on oscilloscope
//!
//!
//! Note :- The phase offset value can easily be configured by updating TBPHS
//!         register to schedule the CLA task and C28x ISR as desired depending
//!         upon the application need so as to avoid overlapping register writes
//!         by CPU and CLA
//!
//! Note :- The optimization is on and set to O2 for the project and all the results
//!         quoted correspond to this case.
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
#include <cla_ex7_shared_resource_handling.h>
#include "board.h"
//
// Defines
//
#define phase_shift_ON 1U

//
// Global variables
//
volatile uint16_t cpu_flag = 0; // Flag used in ISR to implement toggle of
                                // EPWM1B output

//
// Function Prototypes
//
void initEPWM(void);
void setupADCSOC_trigger(void);
void setuploop1ProfileGpio(void);
void setuploop2ProfileGpio(void);
void initCLA(void);
__interrupt void cpuISR(void);


#if defined(_FLASH)
#pragma CODE_SECTION(cpuISR,".TI.ramfunc");
#endif


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
    // GPIO0 is set to EPWM1A and GPIO1 is set to EPWM1B
    //
    GPIO_setControllerCore(0, GPIO_CORE_CPU1);
    GPIO_setPadConfig(0,GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_0_EPWM1_A);
    GPIO_setControllerCore(1, GPIO_CORE_CPU1);
    GPIO_setPadConfig(1,GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_1_EPWM1_B);

    //
    // Setup Profiling GPIOs for loop1 and loop2
    //
    setuploop1ProfileGpio();
    setuploop2ProfileGpio();

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
    // Initialize EPWM1, EPWM4 and EPWM5 modules
    //
    initEPWM();

    //
    // Initialize resources
    //
    Board_init();
    initCLA();

    //
    // Register the EPWM4 interrupt
    //
    Interrupt_register(INT_EPWM4, &cpuISR);

    //
    // Enable EPWM4 CPU interrupt
    //
    Interrupt_enable(INT_EPWM4);

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

//
// EPWM Initialization
// EPWM1 : generates software controlled outputs at A & B
// EPWM4 : triggers CPU interrupt @ 10KHz
// EPWM5 : triggers CLA task 1 @ 100KHz
//
void initEPWM(void)
{
    //
    // Set up EPWM1 to
    // - run on a base clock of SYSCLK
    // - run in count up-down mode
    // - Max period
    // - Immediate load of SW actions
    //
    EPWM_setClockPrescaler(EPWM1_BASE, EPWM_CLOCK_DIVIDER_1,
                           EPWM_HSCLOCK_DIVIDER_1);
    EPWM_setTimeBasePeriod(EPWM1_BASE, 0xFFFF);
    EPWM_setTimeBaseCounterMode(EPWM1_BASE, EPWM_COUNTER_MODE_UP_DOWN);
    EPWM_setTimeBaseCounter(EPWM1_BASE, 0U);
    EPWM_setActionQualifierContSWForceShadowMode(EPWM1_BASE, EPWM_AQ_SW_IMMEDIATE_LOAD);

    //
    // Run freely in emulation mode
    //
    EPWM_setEmulationMode(EPWM1_BASE, EPWM_EMULATION_FREE_RUN);


    //
    // Set up EPWM4 to
    // - run on a base clock of SYSCLK
    // - have a period of EPWM4_PERIOD (10 KHz)
    // - run in count up mode
    // - Generate a SYNCOUT pulse if phase shifting is used
    // - Generate an interrupt to CPU on very TBCTR=ZERO event
    EPWM_setClockPrescaler(EPWM4_BASE, EPWM_CLOCK_DIVIDER_1,
                           EPWM_HSCLOCK_DIVIDER_1);
    EPWM_setTimeBasePeriod(EPWM4_BASE, EPWM4_PERIOD - 1U);
    EPWM_setTimeBaseCounterMode(EPWM4_BASE, EPWM_COUNTER_MODE_UP);
    EPWM_setTimeBaseCounter(EPWM4_BASE, 0U);
#if phase_shift_ON == 1U
    EPWM_setSyncOutPulseMode(EPWM4_BASE, EPWM_SYNC_OUT_PULSE_ON_COUNTER_ZERO);
#endif
    EPWM_setInterruptSource(EPWM4_BASE, EPWM_INT_TBCTR_ZERO);
    EPWM_enableInterrupt(EPWM4_BASE);
    EPWM_setInterruptEventCount(EPWM4_BASE, 1U);

    //
    // Set up EPWM5 to
    // - run on a base clock of SYSCLK
    // - have a period of EPWM4_PERIOD (100 KHz)
    // - run in count up mode
    // - Enable phase shift of 20 cycles on receiving a
    // - SYNC pulse if phase shifting is used
    // - Trigger a CLA task on every TBCTR=ZERO event
    EPWM_setClockPrescaler(EPWM5_BASE, EPWM_CLOCK_DIVIDER_1,
                           EPWM_HSCLOCK_DIVIDER_1);
    EPWM_setTimeBasePeriod(EPWM5_BASE, EPWM5_PERIOD - 1U);
    EPWM_setTimeBaseCounterMode(EPWM5_BASE, EPWM_COUNTER_MODE_UP);
    EPWM_setTimeBaseCounter(EPWM5_BASE, 0U);
#if phase_shift_ON == 1U
    EPWM_enablePhaseShiftLoad(EPWM5_BASE);
    EPWM_setPhaseShift(EPWM5_BASE, 20U);
    EPWM_enableOneShotSync(EPWM5_BASE);
#endif
    EPWM_setInterruptSource(EPWM5_BASE, EPWM_INT_TBCTR_ZERO);
    EPWM_enableInterrupt(EPWM5_BASE);
    EPWM_setInterruptEventCount(EPWM5_BASE, 1U);
}

//
// CLA Initialization
//
void initCLA(void)
{
    //
    // Force task 8, the one time initialization task
    //
    CLA_forceTasks(CLA1_BASE, CLA_TASKFLAG_8);
}

//
// Setting up GPIO2 for profiling cla Task
//
void setuploop1ProfileGpio(void)
{
        GPIO_setDirectionMode(2,GPIO_DIR_MODE_OUT);
        GPIO_setQualificationMode(2,GPIO_QUAL_SYNC);
        GPIO_setPinConfig(GPIO_2_GPIO2);
        GPIO_writePin(2,0);
        GPIO_setControllerCore(2, GPIO_CORE_CPU1_CLA1);
}

//
// Setting up GPIO3 for profiling cpuISR
//
void setuploop2ProfileGpio(void)
{
        GPIO_setDirectionMode(3,GPIO_DIR_MODE_OUT);
        GPIO_setQualificationMode(3,GPIO_QUAL_SYNC);
        GPIO_setPinConfig(GPIO_3_GPIO3);
        GPIO_writePin(3,0);
}

//
// CPU ISR
//
__interrupt void cpuISR(void)
{
    //
    // Turn ON Profiling GPIO3
    //
    GPIO_writePin(3,1);

    //
    // Toggle the EPWM1B output using SW Force Action
    //
    if (cpu_flag == 1)
    {
        EPWM_setActionQualifierContSWForceAction(EPWM1_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_SW_OUTPUT_HIGH);
        cpu_flag = 0;
    }

    else
    {
        EPWM_setActionQualifierContSWForceAction(EPWM1_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_SW_OUTPUT_LOW);
        cpu_flag = 1;
    }

    //
    // Turn OFF Profiling GPIO3
    //
    GPIO_writePin(3,0);

    //
    // Clear EPWM4 interrupt flag so that next interrupt can come in
    //
    EPWM_clearEventTriggerInterruptFlag(EPWM4_BASE);

    //
    // Acknowledge the interrupt
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP3);
}
