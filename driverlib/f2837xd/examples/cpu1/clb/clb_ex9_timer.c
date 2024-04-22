//#############################################################################
//
// FILE:   clb_ex9_timer.c
//
// TITLE:  CLB Timer.
//
//! \addtogroup driver_example_list
//! <h1>CLB Timer</h1>
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
#include "board.h"

__interrupt void clb1ISR(void);

#define RESET_TIMER     1
#define ENABLE_TIMER    2
#define COUNTUP_MODE    4


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

    initTILE1(myTILE1_BASE);
    Board_init();

    CLB_setGPREG(myTILE1_BASE, ENABLE_TIMER | COUNTUP_MODE);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;


    CLB_clearInterruptTag(myTILE1_BASE);


    while(1)
    {
        SysCtl_delay(20000000);
        // Change Timer Value to 2000
        CLB_configCounterLoadMatch(myTILE1_BASE, CLB_CTR0, 0, 2000, 0);
        SysCtl_delay(20000000);
        // Change Timer Value to 1000
        CLB_configCounterLoadMatch(myTILE1_BASE, CLB_CTR0, 0, 1000, 0);
        asm(" NOP");
    }
}


__interrupt void clb1ISR(void)
{
    GPIO_togglePin(myGPIO0);
    CLB_clearInterruptTag(myTILE1_BASE);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP5);
}

