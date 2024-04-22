//#############################################################################
//
// FILE:   clb_ex2_gpio_input_filter.c
//
// TITLE:  CLB GPIO Input Filter.
//
//! \addtogroup driver_example_list
//! <h1>CLB GPIO Input Filter</h1>
//!
//! For the detailed description of this example, please refer to:
//!  `C2000Ware_PATH\utilities\clb_tool\clb_syscfg\doc\CLB Tool Users Guide.pdf`
//!
//! This example demonstrates use of finite state machines (FSMs) and counters 
//! to implement a simple âglitchâ filter which might, for example, be applied 
//! to an incoming GPIO signal to remove unwanted short duration pulses.
//!
//
//
//#############################################################################
// $TI Release: F28004x Support Library v5.02.00.00 $
// $Release Date: 04-07-2024 $
// $Copyright:
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com/
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

#define EPWM1_TIMER_TBPRD   0xFFFF
#define EPWM1_CMPA          0x0003
#define EPWM1_CMPB          0xFFFC
#define MODE_CHG_COUNT      10000U

void initEPWM1(void);
void initCLB1(void);

uint32_t ccount = 0UL;
uint16_t cglitch = 3U;


void main(void)
{
    Device_init();
    Device_initGPIO();

    Interrupt_initModule();
    Interrupt_initVectorTable();

    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);
	SysCtl_enablePeripheral((SysCtl_PeripheralPCLOCKCR)0x0011);

    Board_init();

    initTILE1(myTILE1_BASE);
    initEPWM1();
    CLB_setOutputMask(myTILE1_BASE, 0x1, true);

    EPWM_setTimeBaseCounterMode(myEPWM1_BASE, EPWM_COUNTER_MODE_UP);

    while(1)
    {
        if (ccount++ > MODE_CHG_COUNT)
        {
            EPWM_setCounterCompareValue (myEPWM1_BASE, EPWM_COUNTER_COMPARE_A, cglitch);
            EPWM_setCounterCompareValue (myEPWM1_BASE, EPWM_COUNTER_COMPARE_B, cglitch);
            ccount = 0;
        }
        asm(" NOP");
    }
}


void initEPWM1()
{
    EPWM_setTimeBasePeriod(myEPWM1_BASE, EPWM1_TIMER_TBPRD);
    EPWM_setPhaseShift(myEPWM1_BASE, 0U);
    EPWM_setTimeBaseCounter(myEPWM1_BASE, 0U);

    EPWM_setSyncOutPulseMode(myEPWM1_BASE, EPWM_SYNC_OUT_PULSE_ON_COUNTER_ZERO);

    EPWM_setCounterCompareValue(myEPWM1_BASE, EPWM_COUNTER_COMPARE_A, EPWM1_CMPA);
    EPWM_setCounterCompareValue(myEPWM1_BASE, EPWM_COUNTER_COMPARE_B, EPWM1_CMPB);

    EPWM_disablePhaseShiftLoad(myEPWM1_BASE);
    EPWM_setClockPrescaler(myEPWM1_BASE, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_1);

    EPWM_setCounterCompareShadowLoadMode(myEPWM1_BASE, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_CNTR_ZERO);
    EPWM_setCounterCompareShadowLoadMode(myEPWM1_BASE, EPWM_COUNTER_COMPARE_B, EPWM_COMP_LOAD_ON_CNTR_ZERO);

    EPWM_setActionQualifierAction(myEPWM1_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    EPWM_setActionQualifierAction(myEPWM1_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    EPWM_setActionQualifierAction(myEPWM1_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    EPWM_setActionQualifierAction(myEPWM1_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
}

