//#############################################################################
//
// FILE:   clb_ex15_tile_to_tile_delay.c
//
// TITLE:  CLB Tile to Tile Delay.
//
//! \addtogroup driver_example_list
//! <h1>CLB Tile to Tile Delay</h1>
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

uint32_t clb1delay = 0;
uint32_t clb2delay = 0;
uint32_t clb3delay = 0;
uint32_t clb4delay = 0;

__interrupt void clb1ISR(void);
__interrupt void clb2ISR(void);
__interrupt void clb3ISR(void);
__interrupt void clb4ISR(void);

void main(void)
{
    Device_init();
    Device_initGPIO();

    //
    // Configure GPIO0 for INPUTXBAR1
    //
    GPIO_setPinConfig(GPIO_0_GPIO0);
    GPIO_setDirectionMode(0, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(0, GPIO_PIN_TYPE_STD);
    XBAR_setInputPin(XBAR_INPUT1, 0);
    GPIO_writePin(0, 0);

    Interrupt_initModule();
    Interrupt_initVectorTable();


    Interrupt_register(INT_CLB1, &clb1ISR);
    Interrupt_enable(INT_CLB1);

    Interrupt_register(INT_CLB2, &clb2ISR);
    Interrupt_enable(INT_CLB2);

    Interrupt_register(INT_CLB3, &clb3ISR);
    Interrupt_enable(INT_CLB3);

    Interrupt_register(INT_CLB4, &clb4ISR);
    Interrupt_enable(INT_CLB4);

    //
    // Enabling EPWM1/2/3/4 to enable CLB1/2/3/4
    //
	SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM1);
	SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM2);
	SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM3);
	SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_EPWM4);

    CLB_enableCLB(CLB1_BASE);
    CLB_enableCLB(CLB2_BASE);
    CLB_enableCLB(CLB3_BASE);
    CLB_enableCLB(CLB4_BASE);

    initTILE1(CLB1_BASE);
    initTILE2(CLB2_BASE);
    initTILE3(CLB3_BASE);
    initTILE4(CLB4_BASE);

    //
    // Configure CLB1 BOUNDARY IN
    //

    //
    // Select Global input instead of local input for CLB IN
    //
    CLB_configLocalInputMux(CLB1_BASE, CLB_IN0, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configLocalInputMux(CLB1_BASE, CLB_IN1, CLB_LOCAL_IN_MUX_GLOBAL_IN);

    //
    // Select AUXSIG0 for CLB1, IN0
    // Select AUXSIG1 for CLB1, IN1
    //
    CLB_configGlobalInputMux(CLB1_BASE, CLB_IN0, CLB_GLOBAL_IN_MUX_CLB_AUXSIG0);
    CLB_configGlobalInputMux(CLB1_BASE, CLB_IN1, CLB_GLOBAL_IN_MUX_CLB_AUXSIG1);

    //
    // Select External for CLB1, IN0
    // Select External for CLB1, IN1
    //
    CLB_configGPInputMux(CLB1_BASE, CLB_IN0, CLB_GP_IN_MUX_EXTERNAL);
    CLB_configGPInputMux(CLB1_BASE, CLB_IN1, CLB_GP_IN_MUX_EXTERNAL);

    //
    // Configure CLB2 BOUNDARY IN
    //

    //
    // Select Global input instead of local input for CLB IN
    //
    CLB_configLocalInputMux(CLB2_BASE, CLB_IN0, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configLocalInputMux(CLB2_BASE, CLB_IN1, CLB_LOCAL_IN_MUX_GLOBAL_IN);

    //
    // Select AUXSIG0 for CLB2, IN0
    // Select AUXSIG2 for CLB2, IN1
    //
    CLB_configGlobalInputMux(CLB2_BASE, CLB_IN0, CLB_GLOBAL_IN_MUX_CLB_AUXSIG0);
    CLB_configGlobalInputMux(CLB2_BASE, CLB_IN1, CLB_GLOBAL_IN_MUX_CLB_AUXSIG2);

    //
    // Select External for CLB2, IN0
    // Select External for CLB2, IN1
    //
    CLB_configGPInputMux(CLB2_BASE, CLB_IN0, CLB_GP_IN_MUX_EXTERNAL);
    CLB_configGPInputMux(CLB2_BASE, CLB_IN1, CLB_GP_IN_MUX_EXTERNAL);


    //
    // Configure CLB3 BOUNDARY IN
    //

    //
    // Select Global input instead of local input for CLB IN
    //
    CLB_configLocalInputMux(CLB3_BASE, CLB_IN0, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configLocalInputMux(CLB3_BASE, CLB_IN1, CLB_LOCAL_IN_MUX_GLOBAL_IN);

    //
    // Select AUXSIG0 for CLB3, IN0
    // Select AUXSIG3 for CLB3, IN1
    //
    CLB_configGlobalInputMux(CLB3_BASE, CLB_IN0, CLB_GLOBAL_IN_MUX_CLB_AUXSIG0);
    CLB_configGlobalInputMux(CLB3_BASE, CLB_IN1, CLB_GLOBAL_IN_MUX_CLB_AUXSIG3);

    //
    // Select External for CLB3, IN0
    // Select External for CLB3, IN1
    //
    CLB_configGPInputMux(CLB3_BASE, CLB_IN0, CLB_GP_IN_MUX_EXTERNAL);
    CLB_configGPInputMux(CLB3_BASE, CLB_IN1, CLB_GP_IN_MUX_EXTERNAL);

    //
    // Configure CLB4 BOUNDARY IN
    //

    //
    // Select Global input instead of local input for CLB IN
    //
    CLB_configLocalInputMux(CLB4_BASE, CLB_IN0, CLB_LOCAL_IN_MUX_GLOBAL_IN);
    CLB_configLocalInputMux(CLB4_BASE, CLB_IN1, CLB_LOCAL_IN_MUX_GLOBAL_IN);

    //
    // Select AUXSIG0 for CLB4, IN0
    // Select AUXSIG4 for CLB4, IN1
    //
    CLB_configGlobalInputMux(CLB4_BASE, CLB_IN0, CLB_GLOBAL_IN_MUX_CLB_AUXSIG0);
    CLB_configGlobalInputMux(CLB4_BASE, CLB_IN1, CLB_GLOBAL_IN_MUX_CLB_AUXSIG4);

    //
    // Select External for CLB4, IN0
    // Select External for CLB4, IN1
    //
    CLB_configGPInputMux(CLB4_BASE, CLB_IN0, CLB_GP_IN_MUX_EXTERNAL);
    CLB_configGPInputMux(CLB4_BASE, CLB_IN1, CLB_GP_IN_MUX_EXTERNAL);


    //
    // Configure CLB-XBAR AUXSIG0 as INPUT1
    //
    XBAR_setCLBMuxConfig(XBAR_AUXSIG0, XBAR_CLB_MUX01_INPUTXBAR1);
    XBAR_enableCLBMux(XBAR_AUXSIG0, XBAR_MUX01);

    //
    // Configure CLB-XBAR AUXSIG1 as CLB2 OUT4
    //
    XBAR_setCLBMuxConfig(XBAR_AUXSIG1, XBAR_CLB_MUX05_CLB2_OUT4);
    XBAR_enableCLBMux(XBAR_AUXSIG1, XBAR_MUX05);

    //
    // Configure CLB-XBAR AUXSIG2 as CLB1 OUT4
    //
    XBAR_setCLBMuxConfig(XBAR_AUXSIG2, XBAR_CLB_MUX01_CLB1_OUT4);
    XBAR_enableCLBMux(XBAR_AUXSIG2, XBAR_MUX01);

    //
    // Configure CLB-XBAR AUXSIG3 as Input XBAR2 = CLB4 OUT4
    //
    XBAR_setCLBMuxConfig(XBAR_AUXSIG3, XBAR_CLB_MUX03_INPUTXBAR2);
    XBAR_enableCLBMux(XBAR_AUXSIG3, XBAR_MUX03);

    //
    // Configure CLB-XBAR AUXSIG4 as Input XBAR3 = CLB3 OUT4
    //
    XBAR_setCLBMuxConfig(XBAR_AUXSIG4, XBAR_CLB_MUX05_INPUTXBAR3);
    XBAR_enableCLBMux(XBAR_AUXSIG4, XBAR_MUX05);

    //
    // Configure GPIO24 for OUTPUTXBAR1
    //
    GPIO_setPinConfig(GPIO_24_OUTPUTXBAR1);
    GPIO_setDirectionMode(24, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(24, GPIO_PIN_TYPE_STD);

    XBAR_setOutputMuxConfig(XBAR_OUTPUT1, XBAR_OUT_MUX01_CLB1_OUT4);
    XBAR_enableOutputMux(XBAR_OUTPUT1, XBAR_MUX01);

    //
    // Configure GPIO16 for OUTPUTXBAR7
    //
    GPIO_setPinConfig(GPIO_16_OUTPUTXBAR7);
    GPIO_setDirectionMode(16, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(16, GPIO_PIN_TYPE_STD);

    XBAR_setOutputMuxConfig(XBAR_OUTPUT7, XBAR_OUT_MUX05_CLB2_OUT4);
    XBAR_enableOutputMux(XBAR_OUTPUT7, XBAR_MUX05);


    //
    // Configure GPIO14 for OUTPUTXBAR3
    //
    GPIO_setPinConfig(GPIO_14_OUTPUTXBAR3);
    GPIO_setDirectionMode(14, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(14, GPIO_PIN_TYPE_STD);

    XBAR_setOutputMuxConfig(XBAR_OUTPUT3, XBAR_OUT_MUX09_CLB3_OUT4);
    XBAR_enableOutputMux(XBAR_OUTPUT3, XBAR_MUX09);

    //
    // Input XBAR3 = CLB3 OUT4 = GPIO14
    //
    XBAR_setInputPin(XBAR_INPUT3, 14);

    //
    // Configure GPIO15 for OUTPUTXBAR4
    //
    GPIO_setPinConfig(GPIO_15_OUTPUTXBAR4);
    GPIO_setDirectionMode(15, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(15, GPIO_PIN_TYPE_STD);

    XBAR_setOutputMuxConfig(XBAR_OUTPUT4, XBAR_OUT_MUX13_CLB4_OUT4);
    XBAR_enableOutputMux(XBAR_OUTPUT4, XBAR_MUX13);

    //
    // Input XBAR2 = CLB4 OUT4 = GPIO15
    //
    XBAR_setInputPin(XBAR_INPUT2, 15);

    //
    // Configure GPIO1 for EPWM1B = CLB1 OUT2
    //
    GPIO_setPinConfig(GPIO_1_EPWM1B);
    GPIO_setDirectionMode(1, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(1, GPIO_PIN_TYPE_STD);

    //
    // Configure GPIO5 for EPWM3B = CLB3 OUT2
    //
    GPIO_setPinConfig(GPIO_5_EPWM3B);
    GPIO_setDirectionMode(5, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(5, GPIO_PIN_TYPE_STD);


    CLB_enableSynchronization(CLB1_BASE, CLB_IN0);
    CLB_enableSynchronization(CLB1_BASE, CLB_IN1);
    CLB_enableSynchronization(CLB2_BASE, CLB_IN0);
    CLB_enableSynchronization(CLB2_BASE, CLB_IN1);
    CLB_enableSynchronization(CLB3_BASE, CLB_IN0);
    CLB_enableSynchronization(CLB3_BASE, CLB_IN1);
    CLB_enableSynchronization(CLB4_BASE, CLB_IN0);
    CLB_enableSynchronization(CLB4_BASE, CLB_IN1);

    //
    // Uncomment to enable asynchronous GPIO inputs
    //
    //GPIO_setQualificationMode(0, GPIO_QUAL_ASYNC);
    //GPIO_setQualificationMode(24, GPIO_QUAL_ASYNC);
    //GPIO_setQualificationMode(16, GPIO_QUAL_ASYNC);
    //GPIO_setQualificationMode(14, GPIO_QUAL_ASYNC);
    //GPIO_setQualificationMode(15, GPIO_QUAL_ASYNC);
    //GPIO_setQualificationMode(1, GPIO_QUAL_ASYNC);
    //GPIO_setQualificationMode(5, GPIO_QUAL_ASYNC);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Enable CLB1 OUT2
    //
    CLB_setOutputMask(CLB1_BASE, 1 << 2, true);

    //
    // Enable CLB3 OUT2
    //
    CLB_setOutputMask(CLB3_BASE, 1 << 2, true);

    CLB_clearInterruptTag(CLB1_BASE);
    CLB_clearInterruptTag(CLB2_BASE);
    CLB_clearInterruptTag(CLB3_BASE);
    CLB_clearInterruptTag(CLB4_BASE);

    SysCtl_delay(1000);
    GPIO_writePin(0, 1);

    SysCtl_delay(10000);
    ESTOP0;

    //
    // Read the clbxdelay values to see how many cycles of delay
    // was detected.
    //

    while(1)
    {

        asm(" NOP");
    }
}

__interrupt void clb1ISR(void)
{
    uint16_t tag = CLB_getInterruptTag(CLB1_BASE);
    if (tag == 1)
    {
        clb1delay = CLB_getRegister(CLB1_BASE, CLB_REG_CTR_C0);
        //ESTOP0;
    }

    CLB_clearInterruptTag(CLB1_BASE);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP5);
}

__interrupt void clb2ISR(void)
{
    uint16_t tag = CLB_getInterruptTag(CLB2_BASE);
    if (tag == 1)
    {
        clb2delay = CLB_getRegister(CLB2_BASE, CLB_REG_CTR_C0);
        //ESTOP0;
    }

    CLB_clearInterruptTag(CLB2_BASE);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP5);
}

__interrupt void clb3ISR(void)
{
    uint16_t tag = CLB_getInterruptTag(CLB3_BASE);
    if (tag == 1)
    {
        clb3delay = CLB_getRegister(CLB3_BASE, CLB_REG_CTR_C0);
        //ESTOP0;
    }

    CLB_clearInterruptTag(CLB3_BASE);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP5);
}

__interrupt void clb4ISR(void)
{
    uint16_t tag = CLB_getInterruptTag(CLB4_BASE);
    if (tag == 1)
    {
        clb4delay = CLB_getRegister(CLB4_BASE, CLB_REG_CTR_C0);
        //ESTOP0;
    }

    CLB_clearInterruptTag(CLB4_BASE);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP5);
}
