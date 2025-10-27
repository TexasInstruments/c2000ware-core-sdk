//############################################################################
//
// FILE:    clb_ex17_one_shot_pwm.c
//
// TITLE:   CLB based One-shot PWM
//
//! \addtogroup driver_example_list
//! <h1>CLB based One-shot PWM</h1>
//!
//! For the detailed description of this example, please refer to :
//!  `C2000Ware_PATH\utilities\clb_tool\clb_syscfg\doc\CLB Tool Users Guide.pdf`
//
//
//#############################################################################
// $TI Release: F28003x Support Library v6.00.01.00 $
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


#include "driverlib.h"
#include "device.h"
#include "clb_config.h"
#include "clb.h"
#include "board.h"

//
// Defines
//
#define EXAMPLE_MODE 0U               // '0' for software trigger mode and
                                     // '1' for external trigger mode
#define TB_CLK  DEVICE_SYSCLK_FREQ    // Time base clock is SYSCLK
#define PWM_CLK   1000000U             // PWM frequency as 1 Mhz
#define PRD_VAL   (TB_CLK / (PWM_CLK))  // Calculate value period value
                                        // for up count mode

//
// Function Prototypes
//
void initEPWM(void);
__interrupt void clb1ISR(void);

//
// Globals
//
uint16_t SOFT_TRIGGER  =    0; // Set this from '0' to '1' (rising edge)
                                 // to provide software trigger for one-shot
                                 // PWM when "EXAMPLE_MODE = 0"
volatile uint16_t dutyValue= 20; // Variable output pulse width

void main(void)
{
    Device_init();
    Device_initGPIO();

    Interrupt_initModule();
    Interrupt_initVectorTable();

    Interrupt_register(INT_CLB1, &clb1ISR);
    Interrupt_enable(INT_CLB1);

    //
    // Enabling CLB1
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CLB1);

    Board_init();

    initTILE1(myTILE1_BASE);

    //
    // Select Global input instead of local input for all CLB IN
    //
    CLB_configLocalInputMux(myTILE1_BASE, CLB_IN0, CLB_LOCAL_IN_MUX_GLOBAL_IN);

#if EXAMPLE_MODE == 1
    //
    // Select AUXSIG0 for CLB1, IN0
    //
    CLB_configGlobalInputMux(myTILE1_BASE, CLB_IN0, CLB_GLOBAL_IN_MUX_CLB_AUXSIG0);
#else
    CLB_configGlobalInputMux(myTILE1_BASE, CLB_IN0, CLB_GLOBAL_IN_MUX_EPWM1A);
#endif

#if EXAMPLE_MODE == 1
    //
    // Inputs set for external trigger
    //
    CLB_configGPInputMux(myTILE1_BASE, CLB_IN0, CLB_GP_IN_MUX_EXTERNAL);
#else
    //
    // Inputs set to GP register for software based trigger
    //
    CLB_configGPInputMux(myTILE1_BASE, CLB_IN0, CLB_GP_IN_MUX_GP_REG);
#endif


#if EXAMPLE_MODE == 1
    //
    // Enable external trigger simulating signal using EPWM module
    //
   initEPWM();
#endif

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    CLB_clearInterruptTag(myTILE1_BASE);


    while(1)
    {

#if EXAMPLE_MODE == 0
    //
    //  In case of software trigger mode, make sure to set
    //  SOFT_TRIGGER first as '0' and then to '1' to simulate
    //  the rising edge software trigger
    //
    CLB_setGPREG(myTILE1_BASE, SOFT_TRIGGER);
#else
        asm(" NOP");
#endif

    }
}


//
// initEPWM - Function to configure ePWM1 to generate a 1 MHz Trigger signal
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
    EPWM_setPhaseShift(EPWM1_BASE, 0);
    EPWM_setTimeBaseCounter(EPWM1_BASE, 0);

    //
    // Disable the shadow load; the load will be immediate instead
    //
    EPWM_disableCounterCompareShadowLoadMode(EPWM1_BASE,
                                             EPWM_COUNTER_COMPARE_A);

    //
    // Set the compare A value for 10% duty to generate a short trigger pulse
    // as the CLB based system is designed such as to respond to a rising edge
    //
    EPWM_setCounterCompareValue(EPWM1_BASE, EPWM_COUNTER_COMPARE_A, PRD_VAL / 10);

    //
    // Set action qualifier behavior on compare A events
    // - EPWM1A --> 1 when CTR = ZERO
    // - EPWM1A --> 0 when CTR = CMPA and increasing
    //
    EPWM_setActionQualifierAction(EPWM1_BASE, EPWM_AQ_OUTPUT_A,
                                  EPWM_AQ_OUTPUT_LOW,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    EPWM_setActionQualifierAction(EPWM1_BASE, EPWM_AQ_OUTPUT_A,
                                  EPWM_AQ_OUTPUT_HIGH,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);

    //
    // Set the time base clock prescaler to /1
    //
    EPWM_setClockPrescaler(EPWM1_BASE, EPWM_CLOCK_DIVIDER_1,
                           EPWM_HSCLOCK_DIVIDER_1);

    //
    // Set the period value; don't shadow the register
    //
    EPWM_setPeriodLoadMode(EPWM1_BASE, EPWM_PERIOD_DIRECT_LOAD);
    EPWM_setTimeBasePeriod(EPWM1_BASE, PRD_VAL - 1);

    //
    // Put the time base counter into up count mode
    //
    EPWM_setTimeBaseCounterMode(EPWM1_BASE, EPWM_COUNTER_MODE_UP);

    //
    // Sync the ePWM time base clock
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);
}

//
// CLB ISR generated after every 3rd input trigger event
//
__interrupt void clb1ISR(void)
{
    //
    // Increase pulse width by 50 ns till it reaches max
    // Range of pulse output : 0.2us - 0.8us
    //
    dutyValue += 5;
    if(dutyValue > 80)
    {
      dutyValue = 20;
    }

    //
    // Load new duty cycle value in HLC Registers
    //
    CLB_writeInterface(myTILE1_BASE, CLB_ADDR_HLC_R0, dutyValue);

    //
    // Clear the interrupt flag and acknowledge
    //
    CLB_clearInterruptTag(myTILE1_BASE);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP5);
}

