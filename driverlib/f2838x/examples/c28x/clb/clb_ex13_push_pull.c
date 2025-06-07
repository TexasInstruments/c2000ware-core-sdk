//#############################################################################
//
// FILE:   clb_ex13_push_pull.c
//
// TITLE:  CLB PUSH PULL.
//
//! \addtogroup driver_example_list
//! <h1>CLB PUSH PULL</h1>
//!
//! For the detailed description of this example, please refer to:
//!  `C2000Ware_PATH\utilities\clb_tool\clb_syscfg\doc\CLB Tool Users Guide.pdf`
//!
//! In this example, the use of the PUSH-PULL interface is shown. Multiple 
//! COUNTER submodules, HLC submodule, FSM submodules, and OUTLUT submodules 
//! are used. The PUSH-PULL interface is used alongside the GP register to 
//! update the COUNTER submodules’ event frequencies.
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

__interrupt void clb1ISR(void);

#define FRC_LOAD     0x1


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
        SysCtl_delay(20000000);
        HWREG(myTILE1_BASE + CLB_LOGICCTL + CLB_O_BUF_PTR) = 0U;
        HWREG(myTILE1_BASE + CLB_DATAEXCH + CLB_O_PULL(0)) = 500U;
        HWREG(myTILE1_BASE + CLB_DATAEXCH + CLB_O_PULL(1)) = 1000U;
        HWREG(myTILE1_BASE + CLB_DATAEXCH + CLB_O_PULL(2)) = 2000U;
        CLB_setGPREG(myTILE1_BASE, FRC_LOAD);
        CLB_setGPREG(myTILE1_BASE, 0);
        SysCtl_delay(20000000);
        HWREG(myTILE1_BASE + CLB_LOGICCTL + CLB_O_BUF_PTR) = 0U;
        HWREG(myTILE1_BASE + CLB_DATAEXCH + CLB_O_PULL(0)) = 1000U;
        HWREG(myTILE1_BASE + CLB_DATAEXCH + CLB_O_PULL(1)) = 2000U;
        HWREG(myTILE1_BASE + CLB_DATAEXCH + CLB_O_PULL(2)) = 4000U;
        CLB_setGPREG(myTILE1_BASE, FRC_LOAD);
        CLB_setGPREG(myTILE1_BASE, 0);
        asm(" NOP");
    }
}


__interrupt void clb1ISR(void)
{


    CLB_clearInterruptTag(myTILE1_BASE);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP5);
}

