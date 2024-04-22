//#############################################################################
//
// FILE:  clb_ex12_output_intersect.c
//
// TITLE:  CLB Output Intersect.
//
//! \addtogroup driver_example_list
//! <h1>CLB Output Intersect</h1>
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

__interrupt void clb1ISR(void);


#define EPWM_TIMER_TBPRD    2000

//
// Function Prototypes
//
void initEPWM(uint32_t epwm_base);
void initOff180EPWM(uint32_t epwm_base);
uint16_t dutyValue = 0;

void main(void)
{
    Device_init();
    Device_initGPIO();

    Interrupt_initModule();
    Interrupt_initVectorTable();

    //
    // Disable sync(Freeze clock to PWM as well). GTBCLKSYNC is applicable
    // only for multiple core devices. Uncomment the below statement if
    // applicable.
    //
    // SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_GTBCLKSYNC);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);
    initEPWM(EPWM2_BASE);
    initOff180EPWM(EPWM3_BASE);
    EPWM_setupEPWMLinks(EPWM3_BASE, EPWM_LINK_WITH_EPWM_2, EPWM_LINK_COMP_A);
    EPWM_setSyncOutPulseMode(EPWM2_BASE, EPWM_SYNC_OUT_PULSE_ON_COUNTER_ZERO);
    EPWM_enablePhaseShiftLoad(EPWM3_BASE);
    //
    // Enable sync and clock to PWM
    //

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    Interrupt_register(INT_CLB1, &clb1ISR);
    Interrupt_enable(INT_CLB1);

    //
    // Enabling EPWM1 to enable CLB1
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1);

    CLB_enableCLB(CLB1_BASE);
    initTILE1(CLB1_BASE);

    //
    // Select Global input instead of local input for all CLB IN
    //
    CLB_configLocalInputMux(CLB1_BASE, CLB_IN0, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configLocalInputMux(CLB1_BASE, CLB_IN1, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configLocalInputMux(CLB1_BASE, CLB_IN2, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configLocalInputMux(CLB1_BASE, CLB_IN3, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configLocalInputMux(CLB1_BASE, CLB_IN4, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configLocalInputMux(CLB1_BASE, CLB_IN5, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configLocalInputMux(CLB1_BASE, CLB_IN6, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configLocalInputMux(CLB1_BASE, CLB_IN7, CLB_LOCAL_IN_MUX_GLOBAL_IN);

    //
    // Select EPWM2A and EPWM3A
    //
    CLB_configGlobalInputMux(CLB1_BASE, CLB_IN0, CLB_GLOBAL_IN_MUX_EPWM2A);
    CLB_configGlobalInputMux(CLB1_BASE, CLB_IN1, CLB_GLOBAL_IN_MUX_EPWM3A);

    //
    // Unused Inputs below
    //
    CLB_configGlobalInputMux(CLB1_BASE, CLB_IN2, CLB_GLOBAL_IN_MUX_EPWM1A);
    CLB_configGlobalInputMux(CLB1_BASE, CLB_IN3, CLB_GLOBAL_IN_MUX_EPWM1A);
    CLB_configGlobalInputMux(CLB1_BASE, CLB_IN4, CLB_GLOBAL_IN_MUX_EPWM1A);
    CLB_configGlobalInputMux(CLB1_BASE, CLB_IN5, CLB_GLOBAL_IN_MUX_EPWM1A);
    CLB_configGlobalInputMux(CLB1_BASE, CLB_IN6, CLB_GLOBAL_IN_MUX_EPWM1A);
    CLB_configGlobalInputMux(CLB1_BASE, CLB_IN7, CLB_GLOBAL_IN_MUX_EPWM1A);


    //
    // Inputs set to External
    //
    CLB_configGPInputMux(CLB1_BASE, CLB_IN0, CLB_GP_IN_MUX_EXTERNAL);
    CLB_configGPInputMux(CLB1_BASE, CLB_IN1, CLB_GP_IN_MUX_EXTERNAL);

    //
    // Unused inputs to GP register
    //
    CLB_configGPInputMux(CLB1_BASE, CLB_IN2, CLB_GP_IN_MUX_GP_REG);
    CLB_configGPInputMux(CLB1_BASE, CLB_IN3, CLB_GP_IN_MUX_GP_REG);
    CLB_configGPInputMux(CLB1_BASE, CLB_IN4, CLB_GP_IN_MUX_GP_REG);
    CLB_configGPInputMux(CLB1_BASE, CLB_IN5, CLB_GP_IN_MUX_GP_REG);
    CLB_configGPInputMux(CLB1_BASE, CLB_IN6, CLB_GP_IN_MUX_GP_REG);
    CLB_configGPInputMux(CLB1_BASE, CLB_IN7, CLB_GP_IN_MUX_GP_REG);

    //
    // Configure GPIO0 for EPWM1A
    //
    GPIO_setPinConfig(GPIO_0_EPWM1A);
    GPIO_setDirectionMode(0, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(0, GPIO_PIN_TYPE_STD);

    //
    // Configure GPIO2 for EPWM2A
    //
    GPIO_setPinConfig(GPIO_2_EPWM2A);
    GPIO_setDirectionMode(2, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(2, GPIO_PIN_TYPE_STD);

    //
    // Configure GPIO2 for EPWM3A
    //
    GPIO_setPinConfig(GPIO_4_EPWM3A);
    GPIO_setDirectionMode(4, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(4, GPIO_PIN_TYPE_STD);


    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;


    CLB_clearInterruptTag(CLB1_BASE);

    //
    // Enable OUT1 to replace EPWM1A
    //
    CLB_setOutputMask(CLB1_BASE, 1 << 0, true);

    //EPWM1A is EPWM2A ANDED with EPWM3A

    for(;;)
    {
        SysCtl_delay(100000);
        dutyValue ++;
        if (dutyValue >= EPWM_TIMER_TBPRD)
            dutyValue = 0;
        EPWM_setCounterCompareValue(EPWM2_BASE, EPWM_COUNTER_COMPARE_A, dutyValue);
    }
}


__interrupt void clb1ISR(void)
{

    CLB_clearInterruptTag(CLB1_BASE);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP5);
}


void initEPWM(uint32_t epwm_base)
{
    //
    // Set-up TBCLK
    //
    EPWM_setTimeBasePeriod(epwm_base, EPWM_TIMER_TBPRD);
    EPWM_setPhaseShift(epwm_base, 0U);
    EPWM_setTimeBaseCounter(epwm_base, 0U);

    //
    // Set Compare values
    //
    EPWM_setCounterCompareValue(epwm_base,
                                EPWM_COUNTER_COMPARE_A,
                                2*EPWM_TIMER_TBPRD/3);
    EPWM_setCounterCompareValue(epwm_base,
                                EPWM_COUNTER_COMPARE_B,
                                2*EPWM_TIMER_TBPRD/3);

    //
    // Set up counter mode
    //
    EPWM_setTimeBaseCounterMode(epwm_base, EPWM_COUNTER_MODE_UP);
    EPWM_disablePhaseShiftLoad(epwm_base);
    EPWM_setClockPrescaler(epwm_base,
                           EPWM_CLOCK_DIVIDER_8,
                           EPWM_HSCLOCK_DIVIDER_1);

    //
    // Set up shadowing
    //
    EPWM_setCounterCompareShadowLoadMode(epwm_base,
                                         EPWM_COUNTER_COMPARE_A,
                                         EPWM_COMP_LOAD_ON_CNTR_ZERO);
    EPWM_setCounterCompareShadowLoadMode(epwm_base,
                                         EPWM_COUNTER_COMPARE_B,
                                         EPWM_COMP_LOAD_ON_CNTR_ZERO);

    //
    // Set actions
    //

    EPWM_setActionQualifierAction(epwm_base,
                                  EPWM_AQ_OUTPUT_A,
                                  EPWM_AQ_OUTPUT_HIGH,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);


    EPWM_setActionQualifierAction(epwm_base,
                                  EPWM_AQ_OUTPUT_B,
                                  EPWM_AQ_OUTPUT_HIGH,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);

    EPWM_setActionQualifierAction(epwm_base,
                                  EPWM_AQ_OUTPUT_A,
                                  EPWM_AQ_OUTPUT_LOW,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    EPWM_setActionQualifierAction(epwm_base,
                                  EPWM_AQ_OUTPUT_B,
                                  EPWM_AQ_OUTPUT_LOW,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);

}


void initOff180EPWM(uint32_t epwm_base)
{
    //
    // Set-up TBCLK
    //
    EPWM_selectPeriodLoadEvent(epwm_base, EPWM_SHADOW_LOAD_MODE_SYNC);
    EPWM_setTimeBasePeriod(epwm_base, EPWM_TIMER_TBPRD);
    EPWM_setPhaseShift(epwm_base, EPWM_TIMER_TBPRD/2);
    EPWM_setTimeBaseCounter(epwm_base, EPWM_TIMER_TBPRD/2);

    //
    // Set Compare values
    //
    EPWM_setCounterCompareValue(epwm_base,
                                EPWM_COUNTER_COMPARE_A,
                                2*EPWM_TIMER_TBPRD/3);
    EPWM_setCounterCompareValue(epwm_base,
                                EPWM_COUNTER_COMPARE_B,
                                2*EPWM_TIMER_TBPRD/3);

    //
    // Set up counter mode
    //
    EPWM_setTimeBaseCounterMode(epwm_base, EPWM_COUNTER_MODE_UP);
    EPWM_disablePhaseShiftLoad(epwm_base);
    EPWM_setClockPrescaler(epwm_base,
                           EPWM_CLOCK_DIVIDER_8,
                           EPWM_HSCLOCK_DIVIDER_1);

    //
    // Set up shadowing
    //
    EPWM_setCounterCompareShadowLoadMode(epwm_base,
                                         EPWM_COUNTER_COMPARE_A,
                                         EPWM_COMP_LOAD_ON_CNTR_ZERO);
    EPWM_setCounterCompareShadowLoadMode(epwm_base,
                                         EPWM_COUNTER_COMPARE_B,
                                         EPWM_COMP_LOAD_ON_CNTR_ZERO);

    //
    // Set actions
    //
    EPWM_setActionQualifierAction(epwm_base,
                                  EPWM_AQ_OUTPUT_A,
                                  EPWM_AQ_OUTPUT_HIGH,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    EPWM_setActionQualifierAction(epwm_base,
                                  EPWM_AQ_OUTPUT_B,
                                  EPWM_AQ_OUTPUT_HIGH,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    EPWM_setActionQualifierAction(epwm_base,
                                  EPWM_AQ_OUTPUT_A,
                                  EPWM_AQ_OUTPUT_LOW,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    EPWM_setActionQualifierAction(epwm_base,
                                  EPWM_AQ_OUTPUT_B,
                                  EPWM_AQ_OUTPUT_LOW,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);

}
