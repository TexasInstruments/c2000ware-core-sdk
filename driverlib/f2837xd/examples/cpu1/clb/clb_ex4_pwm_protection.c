//#############################################################################
//
// FILE:   clb_ex4_pwm_protection.c
//
// TITLE:  CLB PWM Protection.
//
//! \addtogroup driver_example_list
//! <h1>CLB PWM Protection</h1>
//!
//! For the detailed description of this example, please refer to: 
//!  C2000Ware_PATH\utilities\clb_tool\clb_syscfg\doc\CLB Tool Users Guide.pdf
//!
//
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


#include "driverlib.h"
#include "device.h"
#include "clb_config.h"
#include "clb.h"

#define EPWM1_TIMER_TBPRD   2000U
#define EPWM1_CMPA           933U
#define EPWM1_CMPB           933U

#define EPWM2_TIMER_TBPRD   2000U
#define EPWM2_CMPA           933U
#define EPWM2_CMPB           933U

#define EPWM3_TIMER_TBPRD   2000U
#define EPWM3_CMPA           933U
#define EPWM3_CMPB           933U

#define EPWM4_TIMER_TBPRD   2000U
#define EPWM4_CMPA           933U
#define EPWM4_CMPB           933U


void initEPWM1(void);
void initEPWM2(void);
void initEPWM3(void);
void initEPWM4(void);
__interrupt void epwm1ISR(void);

uint32_t mode = 0;


void main(void)
{
    Device_init();
    Device_initGPIO();

    Interrupt_initModule();
    Interrupt_initVectorTable();
    Interrupt_register(INT_EPWM1, &epwm1ISR);

    GPIO_setPadConfig(0, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_0_EPWM1A);
    GPIO_setPadConfig(1, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_1_EPWM1B);

    GPIO_setPadConfig(2, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_2_EPWM2A);
    GPIO_setPadConfig(3, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_3_EPWM2B);

    GPIO_setPadConfig(4, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_4_EPWM3A);
    GPIO_setPadConfig(5, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_5_EPWM3B);

    GPIO_setPadConfig(6, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_6_EPWM4A);
    GPIO_setPadConfig(7, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_7_EPWM4B);

    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);
    initEPWM1();
    initEPWM2();
    initEPWM3();
    initEPWM4();
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);
    //SysCtl_enablePeripheral((SysCtl_PeripheralPCLOCKCR)0x0011);
    SysCtl_enablePeripheral((SysCtl_PeripheralPCLOCKCR)0x0111);
    SysCtl_enablePeripheral((SysCtl_PeripheralPCLOCKCR)0x0211);
    SysCtl_enablePeripheral((SysCtl_PeripheralPCLOCKCR)0x0311);

    // initialize all CLB tiles
    CLB_enableCLB(CLB1_BASE);
    CLB_enableCLB(CLB2_BASE);
    CLB_enableCLB(CLB3_BASE);
    CLB_enableCLB(CLB4_BASE);

    initTILE1(CLB1_BASE);
    initTILE2(CLB2_BASE);
    initTILE3(CLB3_BASE);
    initTILE4(CLB4_BASE);

    // CLB tile 1 configuration
    CLB_configLocalInputMux(CLB1_BASE, CLB_IN0, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configLocalInputMux(CLB1_BASE, CLB_IN1, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configLocalInputMux(CLB1_BASE, CLB_IN2, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configLocalInputMux(CLB1_BASE, CLB_IN3, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configLocalInputMux(CLB1_BASE, CLB_IN4, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configLocalInputMux(CLB1_BASE, CLB_IN5, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configLocalInputMux(CLB1_BASE, CLB_IN6, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configLocalInputMux(CLB1_BASE, CLB_IN7, CLB_LOCAL_IN_MUX_GLOBAL_IN);

    CLB_configGlobalInputMux(CLB1_BASE, CLB_IN0, CLB_GLOBAL_IN_MUX_EPWM1A);
    CLB_configGlobalInputMux(CLB1_BASE, CLB_IN1, CLB_GLOBAL_IN_MUX_EPWM1A);
    CLB_configGlobalInputMux(CLB1_BASE, CLB_IN2, CLB_GLOBAL_IN_MUX_EPWM1B);
    CLB_configGlobalInputMux(CLB1_BASE, CLB_IN3, CLB_GLOBAL_IN_MUX_EPWM1B);
    CLB_configGlobalInputMux(CLB1_BASE, CLB_IN4, CLB_GLOBAL_IN_MUX_EPWM1_CTRDIR);
    CLB_configGlobalInputMux(CLB1_BASE, CLB_IN5, CLB_GLOBAL_IN_MUX_EPWM1_CTRDIR);
    CLB_configGlobalInputMux(CLB1_BASE, CLB_IN6, CLB_GLOBAL_IN_MUX_EPWM1_CTRDIR);
    CLB_configGlobalInputMux(CLB1_BASE, CLB_IN7, CLB_GLOBAL_IN_MUX_EPWM1_CTRDIR);

    CLB_configGPInputMux(CLB1_BASE, CLB_IN0, CLB_GP_IN_MUX_EXTERNAL);
    CLB_configGPInputMux(CLB1_BASE, CLB_IN1, CLB_GP_IN_MUX_EXTERNAL);
    CLB_configGPInputMux(CLB1_BASE, CLB_IN2, CLB_GP_IN_MUX_EXTERNAL);
    CLB_configGPInputMux(CLB1_BASE, CLB_IN3, CLB_GP_IN_MUX_EXTERNAL);
    CLB_configGPInputMux(CLB1_BASE, CLB_IN4, CLB_GP_IN_MUX_GP_REG);
    CLB_configGPInputMux(CLB1_BASE, CLB_IN5, CLB_GP_IN_MUX_GP_REG);
    CLB_configGPInputMux(CLB1_BASE, CLB_IN6, CLB_GP_IN_MUX_GP_REG);
    CLB_configGPInputMux(CLB1_BASE, CLB_IN7, CLB_GP_IN_MUX_GP_REG);

    CLB_selectInputFilter(CLB1_BASE, CLB_IN0, CLB_FILTER_FALLING_EDGE);
    CLB_selectInputFilter(CLB1_BASE, CLB_IN2, CLB_FILTER_FALLING_EDGE);

    // CLB tile 2 configuration
    CLB_configLocalInputMux(CLB2_BASE, CLB_IN0, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configLocalInputMux(CLB2_BASE, CLB_IN1, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configLocalInputMux(CLB2_BASE, CLB_IN2, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configLocalInputMux(CLB2_BASE, CLB_IN3, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configLocalInputMux(CLB2_BASE, CLB_IN4, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configLocalInputMux(CLB2_BASE, CLB_IN5, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configLocalInputMux(CLB2_BASE, CLB_IN6, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configLocalInputMux(CLB2_BASE, CLB_IN7, CLB_LOCAL_IN_MUX_GLOBAL_IN);

    CLB_configGlobalInputMux(CLB2_BASE, CLB_IN0, CLB_GLOBAL_IN_MUX_EPWM2A);
    CLB_configGlobalInputMux(CLB2_BASE, CLB_IN1, CLB_GLOBAL_IN_MUX_EPWM2A);
    CLB_configGlobalInputMux(CLB2_BASE, CLB_IN2, CLB_GLOBAL_IN_MUX_EPWM2B);
    CLB_configGlobalInputMux(CLB2_BASE, CLB_IN3, CLB_GLOBAL_IN_MUX_EPWM2B);
    CLB_configGlobalInputMux(CLB2_BASE, CLB_IN4, CLB_GLOBAL_IN_MUX_EPWM2_CTRDIR);
    CLB_configGlobalInputMux(CLB2_BASE, CLB_IN5, CLB_GLOBAL_IN_MUX_EPWM2_CTRDIR);
    CLB_configGlobalInputMux(CLB2_BASE, CLB_IN6, CLB_GLOBAL_IN_MUX_EPWM2_CTRDIR);
    CLB_configGlobalInputMux(CLB2_BASE, CLB_IN7, CLB_GLOBAL_IN_MUX_EPWM2_CTRDIR);

    CLB_configGPInputMux(CLB2_BASE, CLB_IN0, CLB_GP_IN_MUX_EXTERNAL);
    CLB_configGPInputMux(CLB2_BASE, CLB_IN1, CLB_GP_IN_MUX_EXTERNAL);
    CLB_configGPInputMux(CLB2_BASE, CLB_IN2, CLB_GP_IN_MUX_EXTERNAL);
    CLB_configGPInputMux(CLB2_BASE, CLB_IN3, CLB_GP_IN_MUX_EXTERNAL);
    CLB_configGPInputMux(CLB2_BASE, CLB_IN4, CLB_GP_IN_MUX_GP_REG);
    CLB_configGPInputMux(CLB2_BASE, CLB_IN5, CLB_GP_IN_MUX_GP_REG);
    CLB_configGPInputMux(CLB2_BASE, CLB_IN6, CLB_GP_IN_MUX_GP_REG);
    CLB_configGPInputMux(CLB2_BASE, CLB_IN7, CLB_GP_IN_MUX_GP_REG);

    CLB_selectInputFilter(CLB2_BASE, CLB_IN0, CLB_FILTER_FALLING_EDGE);
    CLB_selectInputFilter(CLB2_BASE, CLB_IN2, CLB_FILTER_FALLING_EDGE);

    // CLB tile 3 configuration
    CLB_configLocalInputMux(CLB3_BASE, CLB_IN0, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configLocalInputMux(CLB3_BASE, CLB_IN1, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configLocalInputMux(CLB3_BASE, CLB_IN2, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configLocalInputMux(CLB3_BASE, CLB_IN3, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configLocalInputMux(CLB3_BASE, CLB_IN4, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configLocalInputMux(CLB3_BASE, CLB_IN5, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configLocalInputMux(CLB3_BASE, CLB_IN6, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configLocalInputMux(CLB3_BASE, CLB_IN7, CLB_LOCAL_IN_MUX_GLOBAL_IN);

    CLB_configGlobalInputMux(CLB3_BASE, CLB_IN0, CLB_GLOBAL_IN_MUX_EPWM3A);
    CLB_configGlobalInputMux(CLB3_BASE, CLB_IN1, CLB_GLOBAL_IN_MUX_EPWM3A);
    CLB_configGlobalInputMux(CLB3_BASE, CLB_IN2, CLB_GLOBAL_IN_MUX_EPWM3B);
    CLB_configGlobalInputMux(CLB3_BASE, CLB_IN3, CLB_GLOBAL_IN_MUX_EPWM3B);
    CLB_configGlobalInputMux(CLB3_BASE, CLB_IN4, CLB_GLOBAL_IN_MUX_EPWM3_CTRDIR);
    CLB_configGlobalInputMux(CLB3_BASE, CLB_IN5, CLB_GLOBAL_IN_MUX_EPWM3_CTRDIR);
    CLB_configGlobalInputMux(CLB3_BASE, CLB_IN6, CLB_GLOBAL_IN_MUX_EPWM3_CTRDIR);
    CLB_configGlobalInputMux(CLB3_BASE, CLB_IN7, CLB_GLOBAL_IN_MUX_EPWM3_CTRDIR);

    CLB_configGPInputMux(CLB3_BASE, CLB_IN0, CLB_GP_IN_MUX_EXTERNAL);
    CLB_configGPInputMux(CLB3_BASE, CLB_IN1, CLB_GP_IN_MUX_EXTERNAL);
    CLB_configGPInputMux(CLB3_BASE, CLB_IN2, CLB_GP_IN_MUX_EXTERNAL);
    CLB_configGPInputMux(CLB3_BASE, CLB_IN3, CLB_GP_IN_MUX_EXTERNAL);
    CLB_configGPInputMux(CLB3_BASE, CLB_IN4, CLB_GP_IN_MUX_GP_REG);
    CLB_configGPInputMux(CLB3_BASE, CLB_IN5, CLB_GP_IN_MUX_GP_REG);
    CLB_configGPInputMux(CLB3_BASE, CLB_IN6, CLB_GP_IN_MUX_GP_REG);
    CLB_configGPInputMux(CLB3_BASE, CLB_IN7, CLB_GP_IN_MUX_GP_REG);

    CLB_selectInputFilter(CLB3_BASE, CLB_IN0, CLB_FILTER_FALLING_EDGE);
    CLB_selectInputFilter(CLB3_BASE, CLB_IN2, CLB_FILTER_FALLING_EDGE);

    // CLB tile 4 configuration
    CLB_configLocalInputMux(CLB4_BASE, CLB_IN0, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configLocalInputMux(CLB4_BASE, CLB_IN1, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configLocalInputMux(CLB4_BASE, CLB_IN2, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configLocalInputMux(CLB4_BASE, CLB_IN3, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configLocalInputMux(CLB4_BASE, CLB_IN4, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configLocalInputMux(CLB4_BASE, CLB_IN5, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configLocalInputMux(CLB4_BASE, CLB_IN6, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configLocalInputMux(CLB4_BASE, CLB_IN7, CLB_LOCAL_IN_MUX_GLOBAL_IN);

    CLB_configGlobalInputMux(CLB4_BASE, CLB_IN0, CLB_GLOBAL_IN_MUX_EPWM4A);
    CLB_configGlobalInputMux(CLB4_BASE, CLB_IN1, CLB_GLOBAL_IN_MUX_EPWM4A);
    CLB_configGlobalInputMux(CLB4_BASE, CLB_IN2, CLB_GLOBAL_IN_MUX_EPWM4B);
    CLB_configGlobalInputMux(CLB4_BASE, CLB_IN3, CLB_GLOBAL_IN_MUX_EPWM4B);
    CLB_configGlobalInputMux(CLB4_BASE, CLB_IN4, CLB_GLOBAL_IN_MUX_EPWM4_CTRDIR);
    CLB_configGlobalInputMux(CLB4_BASE, CLB_IN5, CLB_GLOBAL_IN_MUX_EPWM4_CTRDIR);
    CLB_configGlobalInputMux(CLB4_BASE, CLB_IN6, CLB_GLOBAL_IN_MUX_EPWM4_CTRDIR);
    CLB_configGlobalInputMux(CLB4_BASE, CLB_IN7, CLB_GLOBAL_IN_MUX_EPWM4_CTRDIR);

    CLB_configGPInputMux(CLB4_BASE, CLB_IN0, CLB_GP_IN_MUX_EXTERNAL);
    CLB_configGPInputMux(CLB4_BASE, CLB_IN1, CLB_GP_IN_MUX_EXTERNAL);
    CLB_configGPInputMux(CLB4_BASE, CLB_IN2, CLB_GP_IN_MUX_EXTERNAL);
    CLB_configGPInputMux(CLB4_BASE, CLB_IN3, CLB_GP_IN_MUX_EXTERNAL);
    CLB_configGPInputMux(CLB4_BASE, CLB_IN4, CLB_GP_IN_MUX_GP_REG);
    CLB_configGPInputMux(CLB4_BASE, CLB_IN5, CLB_GP_IN_MUX_GP_REG);
    CLB_configGPInputMux(CLB4_BASE, CLB_IN6, CLB_GP_IN_MUX_GP_REG);
    CLB_configGPInputMux(CLB4_BASE, CLB_IN7, CLB_GP_IN_MUX_GP_REG);

    CLB_selectInputFilter(CLB4_BASE, CLB_IN0, CLB_FILTER_FALLING_EDGE);
    CLB_selectInputFilter(CLB4_BASE, CLB_IN2, CLB_FILTER_FALLING_EDGE);

    // start PWMs
    EPWM_setTimeBaseCounterMode(EPWM1_BASE, EPWM_COUNTER_MODE_UP);
    EPWM_setTimeBaseCounterMode(EPWM2_BASE, EPWM_COUNTER_MODE_UP);
    EPWM_setTimeBaseCounterMode(EPWM3_BASE, EPWM_COUNTER_MODE_UP);
    EPWM_setTimeBaseCounterMode(EPWM4_BASE, EPWM_COUNTER_MODE_UP);

    Interrupt_enable(INT_EPWM1);
    EINT;

    while(1)
    {
        asm(" NOP");
    }
}


void initEPWM1()
{
    EPWM_setTimeBasePeriod(EPWM1_BASE, EPWM1_TIMER_TBPRD);
    EPWM_setPhaseShift(EPWM1_BASE, 0U);
    EPWM_setTimeBaseCounter(EPWM1_BASE, 0U);

    EPWM_setSyncOutPulseMode(EPWM1_BASE, EPWM_SYNC_OUT_PULSE_ON_COUNTER_ZERO);

    EPWM_setCounterCompareValue(EPWM1_BASE, EPWM_COUNTER_COMPARE_A, EPWM1_CMPA);
    EPWM_setCounterCompareValue(EPWM1_BASE, EPWM_COUNTER_COMPARE_B, EPWM1_CMPB);

    EPWM_disablePhaseShiftLoad(EPWM1_BASE);
    EPWM_setClockPrescaler(EPWM1_BASE, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_1);

    EPWM_setCounterCompareShadowLoadMode(EPWM1_BASE, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_CNTR_ZERO);
    EPWM_setCounterCompareShadowLoadMode(EPWM1_BASE, EPWM_COUNTER_COMPARE_B, EPWM_COMP_LOAD_ON_CNTR_ZERO);

    EPWM_setActionQualifierAction(EPWM1_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    EPWM_setActionQualifierAction(EPWM1_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);

    EPWM_setActionQualifierAction(EPWM1_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    EPWM_setActionQualifierAction(EPWM1_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);

    EPWM_setInterruptSource(EPWM1_BASE, EPWM_INT_TBCTR_ZERO);
    EPWM_enableInterrupt(EPWM1_BASE);
    EPWM_setInterruptEventCount(EPWM1_BASE, 3U);
}


void initEPWM2()
{
    EPWM_setTimeBasePeriod(EPWM2_BASE, EPWM2_TIMER_TBPRD);
    EPWM_setPhaseShift(EPWM2_BASE, 0U);
    EPWM_setTimeBaseCounter(EPWM2_BASE, 0U);

    EPWM_enablePhaseShiftLoad(EPWM2_BASE);
    EPWM_setPhaseShift(EPWM2_BASE, 0U);

    EPWM_setCounterCompareValue(EPWM2_BASE, EPWM_COUNTER_COMPARE_A, EPWM2_CMPA);
    EPWM_setCounterCompareValue(EPWM2_BASE, EPWM_COUNTER_COMPARE_B, EPWM2_CMPB);

    EPWM_setClockPrescaler(EPWM2_BASE, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_1);

    EPWM_setCounterCompareShadowLoadMode(EPWM2_BASE, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_CNTR_ZERO);
    EPWM_setCounterCompareShadowLoadMode(EPWM2_BASE, EPWM_COUNTER_COMPARE_B, EPWM_COMP_LOAD_ON_CNTR_ZERO);

    EPWM_setActionQualifierAction(EPWM2_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    EPWM_setActionQualifierAction(EPWM2_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);

    EPWM_setActionQualifierAction(EPWM2_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    EPWM_setActionQualifierAction(EPWM2_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
}


void initEPWM3()
{
    EPWM_setTimeBasePeriod(EPWM3_BASE, EPWM3_TIMER_TBPRD);
    EPWM_setPhaseShift(EPWM3_BASE, 0U);
    EPWM_setTimeBaseCounter(EPWM3_BASE, 0U);

    EPWM_enablePhaseShiftLoad(EPWM3_BASE);
    EPWM_setPhaseShift(EPWM3_BASE, 0U);

    EPWM_setCounterCompareValue(EPWM3_BASE, EPWM_COUNTER_COMPARE_A, EPWM3_CMPA);
    EPWM_setCounterCompareValue(EPWM3_BASE, EPWM_COUNTER_COMPARE_B, EPWM3_CMPB);

    EPWM_setClockPrescaler(EPWM3_BASE, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_1);

    EPWM_setCounterCompareShadowLoadMode(EPWM3_BASE, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_CNTR_ZERO);
    EPWM_setCounterCompareShadowLoadMode(EPWM3_BASE, EPWM_COUNTER_COMPARE_B, EPWM_COMP_LOAD_ON_CNTR_ZERO);

    EPWM_setActionQualifierAction(EPWM3_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    EPWM_setActionQualifierAction(EPWM3_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);

    EPWM_setActionQualifierAction(EPWM3_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    EPWM_setActionQualifierAction(EPWM3_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
}


void initEPWM4()
{
    EPWM_setTimeBasePeriod(EPWM4_BASE, EPWM4_TIMER_TBPRD);
    EPWM_setPhaseShift(EPWM4_BASE, 0U);
    EPWM_setTimeBaseCounter(EPWM4_BASE, 0U);

    EPWM_enablePhaseShiftLoad(EPWM4_BASE);
    EPWM_setPhaseShift(EPWM4_BASE, 0U);

    EPWM_setCounterCompareValue(EPWM4_BASE, EPWM_COUNTER_COMPARE_A, EPWM4_CMPA);
    EPWM_setCounterCompareValue(EPWM4_BASE, EPWM_COUNTER_COMPARE_B, EPWM4_CMPB);

    EPWM_setClockPrescaler(EPWM4_BASE, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_1);

    EPWM_setCounterCompareShadowLoadMode(EPWM4_BASE, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_CNTR_ZERO);
    EPWM_setCounterCompareShadowLoadMode(EPWM4_BASE, EPWM_COUNTER_COMPARE_B, EPWM_COMP_LOAD_ON_CNTR_ZERO);

    EPWM_setActionQualifierAction(EPWM4_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    EPWM_setActionQualifierAction(EPWM4_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);

    EPWM_setActionQualifierAction(EPWM4_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    EPWM_setActionQualifierAction(EPWM4_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);
}


__interrupt void epwm1ISR(void)
{
    EPWM_clearEventTriggerInterruptFlag(EPWM1_BASE);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP3);

    if (mode == 0)
    {
        CLB_setOutputMask(CLB1_BASE, 0x5, false);
        CLB_setOutputMask(CLB2_BASE, 0x5, false);
        CLB_setOutputMask(CLB3_BASE, 0x5, false);
        CLB_setOutputMask(CLB4_BASE, 0x5, false);
    }
    else
    {
        CLB_setOutputMask(CLB1_BASE, 0x5, true);
        CLB_setOutputMask(CLB2_BASE, 0x5, true);
        CLB_setOutputMask(CLB3_BASE, 0x5, true);
        CLB_setOutputMask(CLB4_BASE, 0x5, true);
    }
    asm(" NOP");
}

/* end of file */
