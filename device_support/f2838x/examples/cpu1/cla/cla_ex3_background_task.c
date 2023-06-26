//#############################################################################
//
// FILE:   cla_ex3_background_task.c
//
// TITLE:  CLA ADC Sampling and Filtering with Buffering in a Background Task
//
//! \addtogroup bitfield_example_list
//! <h1> CLA ADC Sampling and Filtering with Buffering in a Background
//! Task </h1>
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
//! \b External \b Connections \n
//!  - connect A0 to EPWM4A
//!
//! \b Watch \b Variables \n
//!  - None
//!
//
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2022 Texas Instruments Incorporated - http://www.ti.com
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
#include "f28x_project.h"
#include "cla_ex3_background_task_shared.h"

//
// Defines
//
#define SYS_FREQ            100000000UL
#define EPWM_CLKDIV         64UL

#define EPWM1_FREQ          1000UL
#define EPWM4_FREQ          100UL
#define EPWM1_PERIOD        (uint16_t)(SYS_FREQ/(EPWM_CLKDIV*EPWM1_FREQ))
#define EPWM4_PERIOD        (uint16_t)(SYS_FREQ/(EPWM_CLKDIV*EPWM4_FREQ))
#define EPWM4_DUTY_CYCLE    (EPWM4_PERIOD/2)

//
// Globals
//

// Background Task (C) Variables
// Circular buffer to store filtered output
#pragma DATA_SECTION(buffer, "CLADataLS0");
volatile float buffer[BUFFER_SIZE];

// Linker Defined variables
extern uint32_t Cla1funcsRunStart, Cla1funcsLoadStart, Cla1funcsLoadSize;
extern uint32_t Cla1ConstRunStart, Cla1ConstLoadStart, Cla1ConstLoadSize;

//
// Function Prototypes
//
void initADC( void );
void initADCSOC( void );
void initEPWM( void );
void initCLA( void );
__attribute__((interrupt))  void cla1Isr1( void );

//
// Main
//
void main(void)
{
    //
    // Initialize device clock and peripherals
    //
    InitSysCtrl();

    //
    // GPIO0 is set to EPWM1A
    //
    InitGpio();
    GPIO_SetupPinMux(0U, GPIO_MUX_CPU1, 1);
    GPIO_SetupPinOptions(0U, GPIO_OUTPUT, GPIO_PUSHPULL);

    //
    // GPIO6 is set to EPWM4A
    //
    GPIO_SetupPinMux(6U, GPIO_MUX_CPU1, 1);
    GPIO_SetupPinOptions(6U, GPIO_OUTPUT, GPIO_PUSHPULL);

    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts. 
    //
    InitPieCtrl();
    IER = 0x0000;
    IFR = 0x0000;

    //
    // Initialize the PIE vector table with pointers to the default Interrupt
    // Service Routines (ISR).
    //
    InitPieVectTable();

    //
    // Map the ISR to the CLA end-of-task interrupt.
    //
    EALLOW;
    PieVectTable.CLA1_1_INT = &cla1Isr1;
    EDIS;

    //
    // Setup the CLA and ADC
    //
    initCLA();
    initADC();
    initADCSOC();

    //
    // Disable sync(Freeze clock to PWM as well)
    //
    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0U;
    EDIS;
    initEPWM();

    //
    // Enable the interrupts in the PIE: Group 11 interrupt 1.
    //
    PieCtrlRegs.PIEIER11.bit.INTx1 = 1U;
    IER |= 0x0400U;
    PieCtrlRegs.PIEACK.bit.ACK11 = 1U;

    //
    // Enable global interrupts.
    //
    EINT;
    ERTM;

    //
    // Enable sync and clock to PWM
    //
    EALLOW;
    CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1U;
    EDIS;

    for(;;)
    {
    }
}

//-----------------------------------------------------------------------------
// ADC Initialization
//
// Function to configure and power up ADC A
//
//-----------------------------------------------------------------------------
void initADC(void)
{
    EALLOW;

    //
    // Set ADCCLK divider to /4
    //
    AdcaRegs.ADCCTL2.bit.PRESCALE = 6;

    //
    // Set pulse positions to late
    //
    AdcaRegs.ADCCTL1.bit.INTPULSEPOS = 1;

    //
    // Power up the ADCs and then delay for 1 ms
    //
    AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1;

    EDIS;

    DELAY_US(1000);
}

//-----------------------------------------------------------------------------
//
// ADC SOC Initialization
//
// Description: This function will configure the ADC, channel A0 to start
// its conversion on a trigger from EPWM1 (EPMW1SOCA). The ADC will sample this
// channel continuously. After each conversion it will assert ADCINT1, which
// is then used to trigger task 1 of the CLA (the filter)
//
//-----------------------------------------------------------------------------
void initADCSOC( void )
{
	EALLOW;

    //
    // Configure SOC0 of ADCA
    // - SOC0 will be triggered by EPWM1SOCA
    // - SOC0 will convert pin A0 with a sample window of 100 SYSCLK cycles.
    // - EOC0 will be generated at the end of conversion
    // - SOC0 will sample on each trigger regardless of the interrupt flag
    //
    AdcaRegs.ADCSOC0CTL.bit.CHSEL = 0;
    AdcaRegs.ADCSOC0CTL.bit.ACQPS = 100U - 1U;
    AdcaRegs.ADCSOC0CTL.bit.TRIGSEL = 5;
    AdcaRegs.ADCINTSEL1N2.bit.INT1CONT = 1;

    //
    // Set SOC0 to set the interrupt 1 flag. Enable the interrupt and make
    // sure its flag is cleared.
    //
    AdcaRegs.ADCINTSEL1N2.bit.INT1SEL = 0;
    AdcaRegs.ADCINTSEL1N2.bit.INT1E = 1;
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;

    EDIS;
}

//-----------------------------------------------------------------------------
//
// EPWM Initialization
//
// Description: EPWM1A will run at EPWM1_FREQ Hz and serves as the sampling
// clock for ADC channel A1 which will be sampling the slower running EPWM4A
// (at EPWM4_FREQ Hz). The default time base for the EPWM module is half the
// system clock i.e.
//       TBCLK = SYSCLKOUT/2
// EPWM1A will be setup in count-up mode and an event generated every period
// this event will trigger the ADC to start sampling on channel A1
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
//-----------------------------------------------------------------------------
void initEPWM( void )
{
	EALLOW;

    //
    // Set up EPWM1 to
    // - run on a base clock of SYSCLK/128
    // - have a period of EPWM1_PERIOD
    // - run in count up mode
    //
    EPwm1Regs.TBCTL.bit.CLKDIV = 2U;    // EPWM_CLOCK_DIVIDER_4
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = 4U; // EPWM_HSCLOCK_DIVIDER_8
    EPwm1Regs.TBPRD = EPWM1_PERIOD;
    EPwm1Regs.TBCTL.bit.CTRMODE = 0U;
    EPwm1Regs.TBCTR = 0U;

    //
    // Enable SOC-A and set it to assert when the counter hits
    // zero. It asserts on every event
    //
    EPwm1Regs.ETSEL.bit.SOCAEN = 1U;
    EPwm1Regs.ETSEL.bit.SOCASEL = 1U;
    EPwm1Regs.ETPS.bit.SOCPSSEL = 1U;
    EPwm1Regs.ETSOCPS.bit.SOCAPRD2 = 1U;

    //
    // EPWM1 should toggle each time its counter hits zero
    //
    EPwm1Regs.AQCTLA.bit.ZRO = 3U;

    //
    // Set up EPWM4 to
    // - run on a base clock of SYSCLK/32
    // - have a period of EPWM4_PERIOD
    // - run in count up/down mode
    // - have its CMPA value set for a 50% duty cycle
    //
    EPwm4Regs.TBCTL.bit.CLKDIV = 2U;    // EPWM_CLOCK_DIVIDER_4
    EPwm4Regs.TBCTL.bit.HSPCLKDIV = 4U; // EPWM_HSCLOCK_DIVIDER_8


    EPwm4Regs.TBPRD = EPWM4_PERIOD;
    EPwm4Regs.TBCTL.bit.CTRMODE = 2U;
    EPwm4Regs.TBCTR = 0U;
    EPwm4Regs.CMPA. all = EPWM4_DUTY_CYCLE;

    //
    // On compare A, when counting up, pull the EPWM A output high
    // On compare A, when counting down, pull the EPWM A output low
    //
    EPwm4Regs.AQCTLA.bit.CAU = 2U;
    EPwm4Regs.AQCTLA.bit.CAD = 1U;

    //
    // EPWM 1 and 4 should run freely in emulation mode
    //
    EPwm1Regs.TBCTL.bit.FREE_SOFT = 2U;
    EPwm4Regs.TBCTL.bit.FREE_SOFT = 2U;

    EDIS;
}

//-----------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------
void initCLA( void )
{
    //
    // Copy the program and constants from FLASH to RAM before configuring
    // the CLA
    //
#if defined(_FLASH)
    memcpy((uint32_t *)&Cla1funcsRunStart, (uint32_t *)&Cla1funcsLoadStart,
        (uint32_t)&Cla1funcsLoadSize );
    memcpy((uint32_t *)&Cla1ConstRunStart, (uint32_t *)&Cla1ConstLoadStart,
        (uint32_t)&Cla1ConstLoadSize );
#endif //defined(_FLASH)

    EALLOW;

    //
    // CLA Program will reside in RAMLS5 and data in RAMLS0, RAMLS1
    //
    MemCfgRegs.LSxCLAPGM.bit.CLAPGM_LS5 = 1U;
    MemCfgRegs.LSxCLAPGM.bit.CLAPGM_LS0 = 0U;
    MemCfgRegs.LSxCLAPGM.bit.CLAPGM_LS1 = 0U;

    //
    // Select CLA as the master of RAMLS0, RAMSL1, RAMLS5
    //
    MemCfgRegs.LSxMSEL.bit.MSEL_LS0 = 1U;
    MemCfgRegs.LSxMSEL.bit.MSEL_LS1 = 1U;
    MemCfgRegs.LSxMSEL.bit.MSEL_LS5 = 1U;

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
    Cla1Regs.MVECT1 = (uint16_t)&Cla1Task1;
    Cla1Regs.MVECT7 = (uint16_t)&Cla1Task7;

    DmaClaSrcSelRegs.CLA1TASKSRCSEL1.bit.TASK1 = 1U; //ADCA1
    DmaClaSrcSelRegs.CLA1TASKSRCSEL2.bit.TASK7 = 0U; //Software

    //
    // Enable Tasks 1 and 7. Since task 7 is forced in software, we must
    // enable software forcing (IACKE)
    //
    Cla1Regs.MIER.bit.INT1 = 1U;
    Cla1Regs.MIER.bit.INT7 = 1U;

    Cla1Regs.MCTL.bit.IACKE = 1U;

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
    Cla1Regs._MVECTBGRND = (uint16_t)&Cla1BackgroundTask;
#pragma diag_warning=770

    Cla1Regs._MCTLBGRND.bit.TRIGEN = 0U;

    DmaClaSrcSelRegs.CLA1TASKSRCSEL2.bit.TASK8 = 0U; //Software

    Cla1Regs._MCTLBGRND.bit.BGEN = 1U;

    Cla1Regs._MCTLBGRND.bit.BGSTART = 1U;

    //
    // Force task 7, the one time initialization task
    //
    Cla1Regs.MIFRC.bit.INT7 = 1U;

    EDIS;
}

//-----------------------------------------------------------------------------
//
// CLA Task 1 End-of-Task Interrupt Service Routine
//
// Description: This ISR is run every time task 1 completes. It continuously
// takes the filtered values from the CLA and stores it to a circular buffer
//
//-----------------------------------------------------------------------------
#ifdef __cplusplus
#pragma CODE_SECTION(".TI.ramfunc");
#else
#pragma CODE_SECTION(cla1Isr1, ".TI.ramfunc")
#endif
__attribute__((interrupt))  void cla1Isr1 ()
{
	EALLOW;

    //
    // Clear the ADC interrupt flag so the next SOC can occur
    //
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1U;

    //
    // Acknowledge the end-of-task interrupt for task 1
    //
    PieCtrlRegs.PIEACK.bit.ACK11 = 1U;

    EDIS;
}

//
// End of File
//
