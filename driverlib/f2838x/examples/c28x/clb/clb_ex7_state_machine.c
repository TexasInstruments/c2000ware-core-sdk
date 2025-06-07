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
//!  C2000Ware_PATH\utilities\clb_tool\clb_syscfg\doc\Designing With the C2000 CLB.pdf
//! This application report describes the process of creating this CLB example
//! and can be used as guidance on desiging custom logic with the CLB. This example 
//! uses all submodules inside a CLB TILE in order to implement a complete system.
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
    // Enabling CLB1
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_CLB1);

    Board_init();

    initTILE1(myTILE1_BASE);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    CLB_clearInterruptTag(myTILE1_BASE);

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
    uint16_t tag = CLB_getInterruptTag(myTILE1_BASE);
    if (tag == UPDATE_PWM_COMPLETED_TAG)
    {
        canUpdate = 1;
        CLB_setGPREG(myTILE1_BASE, 0);
    }

    CLB_clearInterruptTag(myTILE1_BASE);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP5);
}

void updateClbPwm(uint32_t period, uint32_t duty)
{
    if (canUpdate)
    {
        canUpdate = 0;
        CLB_writeInterface(myTILE1_BASE, CLB_ADDR_COUNTER_1_LOAD, period);
        HWREG(myTILE1_BASE + CLB_LOGICCTL + CLB_O_BUF_PTR) = 0U;
        HWREG(myTILE1_BASE + CLB_DATAEXCH + CLB_O_PULL(0)) = period;
        HWREG(myTILE1_BASE + CLB_DATAEXCH + CLB_O_PULL(1)) = duty;
        CLB_setGPREG(myTILE1_BASE, 1 << TRIGGER_PWM_UPDATE_SHIFT);
    }
}
