//############################################################################
//
// FILE:    clb_ex16_glue_logic.c
//
// TITLE:   CLB Glue Logic
//
//! \addtogroup driver_example_list
//! <h1>CLB Glue Logic</h1>
//!
//! For the detailed description of this example, please refer to :
//!  `C2000Ware_PATH\utilities\clb_tool\clb_syscfg\doc\CLB Tool Users Guide.pdf`
//!
//! In this example the user is walked through how to migrate custom logic from 
//! an FPGA/CPLD to C2000™ microcontrollers.
//!
//
//
//#############################################################################
// $TI Release: $
// 
// 
// C2000Ware v5.05.00.00
//
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
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

#define EPWM1_TIMER_TBPRD   0x0020
#define EPWM1_CMPA          0x0010
#define EPWM1_CMPB          0x0010

#define EPWM2_TIMER_TBPRD   0x05C0
#define EPWM2_CMPA          0x02E0
#define EPWM2_CMPB          0x02E0

void initEPWM1(void);
void initEPWM2(void);
void initCLB1(void);


void main(void)
{
    Device_init();
    Device_initGPIO();

    Interrupt_initModule();
    Interrupt_initVectorTable();

    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    Board_init();

    initEPWM1();
    initEPWM2();

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

	SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CLB1);

    initCLB1();

    EPWM_setTimeBaseCounterMode(myEPWM1_BASE, EPWM_COUNTER_MODE_UP);
    EPWM_setTimeBaseCounterMode(myEPWM2_BASE, EPWM_COUNTER_MODE_UP);
}


void initEPWM1()
{
    EPWM_setTimeBasePeriod(myEPWM1_BASE, EPWM1_TIMER_TBPRD);
    EPWM_setPhaseShift(myEPWM1_BASE, 0U);
    EPWM_setTimeBaseCounter(myEPWM1_BASE, 0U);

    EPWM_enableSyncOutPulseSource(myEPWM1_BASE, EPWM_SYNC_OUT_PULSE_ON_CNTR_ZERO);

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


void initEPWM2()
{
    EPWM_setTimeBasePeriod(myEPWM2_BASE, EPWM2_TIMER_TBPRD);
    EPWM_setPhaseShift(myEPWM2_BASE, 0U);
    EPWM_setTimeBaseCounter(myEPWM2_BASE, 0U);

    EPWM_enableSyncOutPulseSource(myEPWM2_BASE, EPWM_SYNC_OUT_PULSE_ON_CNTR_ZERO);

    EPWM_setCounterCompareValue(myEPWM2_BASE, EPWM_COUNTER_COMPARE_A, EPWM2_CMPA);
    EPWM_setCounterCompareValue(myEPWM2_BASE, EPWM_COUNTER_COMPARE_B, EPWM2_CMPB);

    EPWM_disablePhaseShiftLoad(myEPWM2_BASE);
    EPWM_setClockPrescaler(myEPWM2_BASE, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_1);

    EPWM_setCounterCompareShadowLoadMode(myEPWM2_BASE, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_CNTR_ZERO);
    EPWM_setCounterCompareShadowLoadMode(myEPWM2_BASE, EPWM_COUNTER_COMPARE_B, EPWM_COMP_LOAD_ON_CNTR_ZERO);

    EPWM_setActionQualifierAction(myEPWM2_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    EPWM_setActionQualifierAction(myEPWM2_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    EPWM_setActionQualifierAction(myEPWM2_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    EPWM_setActionQualifierAction(myEPWM2_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
}


void initCLB1(void)
{
    //
    // Output LUT
    //
    CLB_configOutputLUT(myTILE1_BASE, CLB_OUT0, TILE1_CFG_OUTLUT_0);
    CLB_configOutputLUT(myTILE1_BASE, CLB_OUT1, TILE1_CFG_OUTLUT_1);
    CLB_configOutputLUT(myTILE1_BASE, CLB_OUT2, TILE1_CFG_OUTLUT_2);
    CLB_configOutputLUT(myTILE1_BASE, CLB_OUT3, TILE1_CFG_OUTLUT_3);
    CLB_configOutputLUT(myTILE1_BASE, CLB_OUT4, TILE1_CFG_OUTLUT_4);
    CLB_configOutputLUT(myTILE1_BASE, CLB_OUT5, TILE1_CFG_OUTLUT_5);
    CLB_configOutputLUT(myTILE1_BASE, CLB_OUT6, TILE1_CFG_OUTLUT_6);
    CLB_configOutputLUT(myTILE1_BASE, CLB_OUT7, TILE1_CFG_OUTLUT_7);

    //
    // LUT4
    //
    CLB_selectLUT4Inputs(myTILE1_BASE, TILE1_CFG_LUT4_IN0, TILE1_CFG_LUT4_IN1, TILE1_CFG_LUT4_IN2, TILE1_CFG_LUT4_IN3);
    CLB_configLUT4Function(myTILE1_BASE, TILE1_CFG_LUT4_FN10, TILE1_CFG_LUT4_FN2);

    //
    // FSM
    //
    CLB_selectFSMInputs(myTILE1_BASE, TILE1_CFG_FSM_EXT_IN0, TILE1_CFG_FSM_EXT_IN1, TILE1_CFG_FSM_EXTRA_IN0, TILE1_CFG_FSM_EXTRA_IN1);
    CLB_configFSMNextState(myTILE1_BASE, TILE1_CFG_FSM_NEXT_STATE_0, TILE1_CFG_FSM_NEXT_STATE_1, TILE1_CFG_FSM_NEXT_STATE_2);
    CLB_configFSMLUTFunction(myTILE1_BASE, TILE1_CFG_FSM_LUT_FN10, TILE1_CFG_FSM_LUT_FN2);

    //
    // Counters
    //
    CLB_selectCounterInputs(myTILE1_BASE, TILE1_CFG_COUNTER_RESET, TILE1_CFG_COUNTER_EVENT, TILE1_CFG_COUNTER_MODE_0, TILE1_CFG_COUNTER_MODE_1);
    CLB_configMiscCtrlModes(myTILE1_BASE, TILE1_CFG_MISC_CONTROL);
    CLB_configCounterLoadMatch(myTILE1_BASE, CLB_CTR0, TILE1_COUNTER_0_LOAD_VAL, TILE1_COUNTER_0_MATCH1_VAL, TILE1_COUNTER_0_MATCH2_VAL);
    CLB_configCounterLoadMatch(myTILE1_BASE, CLB_CTR1, TILE1_COUNTER_1_LOAD_VAL, TILE1_COUNTER_1_MATCH1_VAL, TILE1_COUNTER_1_MATCH2_VAL);
    CLB_configCounterLoadMatch(myTILE1_BASE, CLB_CTR2, TILE1_COUNTER_2_LOAD_VAL, TILE1_COUNTER_2_MATCH1_VAL, TILE1_COUNTER_2_MATCH2_VAL);
}
