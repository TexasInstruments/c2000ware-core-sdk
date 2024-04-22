//#############################################################################
//
// FILE:   clb_ex7_state_machine.c
//
// TITLE:  CLB State Machine.
//
//! \addtogroup driver_example_list
//! <h1>CLB State Machine</h1>
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


#define UPDATE_PWM_COMPLETED_TAG    1
#define TRIGGER_PWM_UPDATE_SHIFT    2
volatile uint16_t canUpdate = 1;

volatile uint32_t clbPwmPeriod = 2000;
volatile uint32_t clbPwmDuty = 1000;
volatile uint16_t clbPwmUpdateNow = 0;

__interrupt void clb1ISR(void);
void updateClbPwm(uint32_t period, uint32_t duty);

void main(void)
{
    Device_init();
    Device_initGPIO();

    Interrupt_initModule();
    Interrupt_initVectorTable();

    Interrupt_register(INT_CLB1, &clb1ISR);
    Interrupt_enable(INT_CLB1);
    
    //
    // Enabling EPWM1 to enable CLB1
    //
	SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1);

    CLB_enableCLB(CLB1_BASE);
    initTILE1(CLB1_BASE);

    CLB_configLocalInputMux(CLB1_BASE, CLB_IN0, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configLocalInputMux(CLB1_BASE, CLB_IN1, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configLocalInputMux(CLB1_BASE, CLB_IN2, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configLocalInputMux(CLB1_BASE, CLB_IN3, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configLocalInputMux(CLB1_BASE, CLB_IN4, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configLocalInputMux(CLB1_BASE, CLB_IN5, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configLocalInputMux(CLB1_BASE, CLB_IN6, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configLocalInputMux(CLB1_BASE, CLB_IN7, CLB_LOCAL_IN_MUX_GLOBAL_IN);

    CLB_configGlobalInputMux(CLB1_BASE, CLB_IN0, CLB_GLOBAL_IN_MUX_CLB_AUXSIG0);
    CLB_configGlobalInputMux(CLB1_BASE, CLB_IN1, CLB_GLOBAL_IN_MUX_CLB_AUXSIG1);

    CLB_configGlobalInputMux(CLB1_BASE, CLB_IN2, CLB_GLOBAL_IN_MUX_EPWM1_CTRDIR);
    CLB_configGlobalInputMux(CLB1_BASE, CLB_IN3, CLB_GLOBAL_IN_MUX_EPWM1_CTRDIR);
    CLB_configGlobalInputMux(CLB1_BASE, CLB_IN4, CLB_GLOBAL_IN_MUX_EPWM1_CTRDIR);
    CLB_configGlobalInputMux(CLB1_BASE, CLB_IN5, CLB_GLOBAL_IN_MUX_EPWM1_CTRDIR);
    CLB_configGlobalInputMux(CLB1_BASE, CLB_IN6, CLB_GLOBAL_IN_MUX_EPWM1_CTRDIR);
    CLB_configGlobalInputMux(CLB1_BASE, CLB_IN7, CLB_GLOBAL_IN_MUX_EPWM1_CTRDIR);

    CLB_configGPInputMux(CLB1_BASE, CLB_IN0, CLB_GP_IN_MUX_EXTERNAL);
    CLB_configGPInputMux(CLB1_BASE, CLB_IN1, CLB_GP_IN_MUX_EXTERNAL);
    CLB_configGPInputMux(CLB1_BASE, CLB_IN2, CLB_GP_IN_MUX_GP_REG);

    CLB_configGPInputMux(CLB1_BASE, CLB_IN3, CLB_GP_IN_MUX_GP_REG);
    CLB_configGPInputMux(CLB1_BASE, CLB_IN4, CLB_GP_IN_MUX_GP_REG);
    CLB_configGPInputMux(CLB1_BASE, CLB_IN5, CLB_GP_IN_MUX_GP_REG);
    CLB_configGPInputMux(CLB1_BASE, CLB_IN6, CLB_GP_IN_MUX_GP_REG);
    CLB_configGPInputMux(CLB1_BASE, CLB_IN7, CLB_GP_IN_MUX_GP_REG);


    //
    // Configure GPIO31 for OUTPUTXBAR8
    //
    GPIO_setPinConfig(GPIO_31_OUTPUTXBAR8);
    GPIO_setDirectionMode(31, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(31, GPIO_PIN_TYPE_STD);

    //
    // Configure OUTPUT-XBAR OUTPUT8 as CLB1_OUT4
    //
    XBAR_setOutputMuxConfig(XBAR_OUTPUT8, XBAR_OUT_MUX01_CLB1_OUT4);
    XBAR_enableOutputMux(XBAR_OUTPUT8, XBAR_MUX01);

    //
    // Configure GPIO34 for OUTPUTXBAR1
    //
    GPIO_setPinConfig(GPIO_34_OUTPUTXBAR1);
    GPIO_setDirectionMode(34, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(34, GPIO_PIN_TYPE_STD);

    //
    // Configure OUTPUT-XBAR OUTPUT1 as CLB1_OUT5
    //
    XBAR_setOutputMuxConfig(XBAR_OUTPUT1, XBAR_OUT_MUX03_CLB1_OUT5);
    XBAR_enableOutputMux(XBAR_OUTPUT1, XBAR_MUX03);

    //
    // Configure GPIO4 for Button
    //
    GPIO_setPinConfig(GPIO_4_GPIO4);
    GPIO_setDirectionMode(4, GPIO_DIR_MODE_IN);
    GPIO_setPadConfig(4, GPIO_PIN_TYPE_PULLUP);

    //
    // Configure Input-XBAR INPUT1 to GPIO4
    //
    XBAR_setInputPin(XBAR_INPUT1, 4);

    //
    // Configure CLB-XBAR AUXSIG0 as INPUT1
    //
    XBAR_setCLBMuxConfig(XBAR_AUXSIG0, XBAR_CLB_MUX01_INPUTXBAR1);
    XBAR_enableCLBMux(XBAR_AUXSIG0, XBAR_MUX01);

    //
    // Configure GPIO5 for Sensor
    //
    GPIO_setPinConfig(GPIO_5_GPIO5);
    GPIO_setDirectionMode(5, GPIO_DIR_MODE_IN);
    GPIO_setPadConfig(5, GPIO_PIN_TYPE_PULLUP);

    //
    // Configure Input-XBAR INPUT2 to GPIO5
    //
    XBAR_setInputPin(XBAR_INPUT2, 5);

    //
    // Configure CLB-XBAR AUXSIG1 as INPUT2
    //
    XBAR_setCLBMuxConfig(XBAR_AUXSIG1, XBAR_CLB_MUX03_INPUTXBAR2);
    XBAR_enableCLBMux(XBAR_AUXSIG1, XBAR_MUX03);


    //
    // Configure GPIO0 for EPWM1A which will be overriden by CLB0_OUT0
    //
    GPIO_setPinConfig(GPIO_0_EPWM1A);
    GPIO_setDirectionMode(0, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(0, GPIO_PIN_TYPE_STD);

    //
    // Configure GPIO1 for EPWM1B which will be overriden by CLB0_OUT1
    //
    GPIO_setPinConfig(GPIO_1_EPWM1B);
    GPIO_setDirectionMode(1, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(1, GPIO_PIN_TYPE_STD);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    CLB_setGPREG(CLB1_BASE, 0);
    CLB_clearInterruptTag(CLB1_BASE);

    CLB_setOutputMask(CLB1_BASE, 1 << 0 | 1 << 2, true);


    while(1)
    {
        if (clbPwmUpdateNow)
        {
            updateClbPwm(clbPwmPeriod, clbPwmDuty);
            clbPwmUpdateNow = 0;
        }
        asm(" NOP");
    }
}

__interrupt void clb1ISR(void)
{
    uint16_t tag = CLB_getInterruptTag(CLB1_BASE);
    if (tag == UPDATE_PWM_COMPLETED_TAG)
    {
        canUpdate = 1;
        CLB_setGPREG(CLB1_BASE, 0);
    }

    CLB_clearInterruptTag(CLB1_BASE);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP5);
}

void updateClbPwm(uint32_t period, uint32_t duty)
{
    if (canUpdate)
    {
        canUpdate = 0;
        CLB_writeInterface(CLB1_BASE, CLB_ADDR_COUNTER_1_LOAD, period);
        HWREG(CLB1_BASE + CLB_LOGICCTL + CLB_O_BUF_PTR) = 0U;
        HWREG(CLB1_BASE + CLB_DATAEXCH + CLB_O_PULL(0)) = period;
        HWREG(CLB1_BASE + CLB_DATAEXCH + CLB_O_PULL(1)) = duty;
        CLB_setGPREG(CLB1_BASE, 1 << TRIGGER_PWM_UPDATE_SHIFT);
    }
}

