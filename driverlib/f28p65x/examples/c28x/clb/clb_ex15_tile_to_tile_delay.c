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
//!  `C2000Ware_PATH\utilities\clb_tool\clb_syscfg\doc\CLB Tool Users Guide.pdf`
//!
//! In this example the output of a GPIO is taken into the CLB TILE through 
//! INPUT XBAR and the CLB XBAR. The signal is forwarded by the TILE to the 
//! next TILE. This time the signal only goes through the CLB XBAR and NOT 
//! the Input XBAR. This is done to show that delays are added when the signals 
//! are passed from TILE to TILE and the delay is NOT characterized. The user 
//! should always avoid passing signals with timing requirements between tiles. 
//! The COUNTER modules inside the CLBs will count the amount of delay in cycles.
//!
//
//
//#############################################################################
// $TI Release: $
// 
// 
// C2000Ware v6.00.00.00
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

    //
    // Enabling CLB1/2/3/4
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CLB1);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CLB2);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CLB3);
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CLB4);

    Board_init();

    initTILE1(myTILE1_BASE);
    initTILE2(myTILE2_BASE);
    initTILE3(myTILE3_BASE);
    initTILE4(myTILE4_BASE);

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

    CLB_clearInterruptTag(myTILE1_BASE);
    CLB_clearInterruptTag(myTILE2_BASE);
    CLB_clearInterruptTag(myTILE3_BASE);
    CLB_clearInterruptTag(myTILE4_BASE);

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
    uint16_t tag = CLB_getInterruptTag(myTILE1_BASE);
    if (tag == 1)
    {
        clb1delay = CLB_getRegister(myTILE1_BASE, CLB_REG_CTR_C0);
        //ESTOP0;
    }

    CLB_clearInterruptTag(myTILE1_BASE);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP5);
}

__interrupt void clb2ISR(void)
{
    uint16_t tag = CLB_getInterruptTag(myTILE2_BASE);
    if (tag == 1)
    {
        clb2delay = CLB_getRegister(myTILE2_BASE, CLB_REG_CTR_C0);
        //ESTOP0;
    }

    CLB_clearInterruptTag(myTILE2_BASE);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP5);
}

__interrupt void clb3ISR(void)
{
    uint16_t tag = CLB_getInterruptTag(myTILE3_BASE);
    if (tag == 1)
    {
        clb3delay = CLB_getRegister(myTILE3_BASE, CLB_REG_CTR_C0);
        //ESTOP0;
    }

    CLB_clearInterruptTag(myTILE3_BASE);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP5);
}

__interrupt void clb4ISR(void)
{
    uint16_t tag = CLB_getInterruptTag(myTILE4_BASE);
    if (tag == 1)
    {
        clb4delay = CLB_getRegister(myTILE4_BASE, CLB_REG_CTR_C0);
        //ESTOP0;
    }

    CLB_clearInterruptTag(myTILE4_BASE);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP5);
}
