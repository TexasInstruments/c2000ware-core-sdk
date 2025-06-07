//#############################################################################
//
// FILE:   clb_ex1_combinatorial_logic.c
//
// TITLE:  CLB Combinational Logic.
//
//! \addtogroup driver_example_list
//! <h1>CLB Combinational Logic</h1>
//!
//! For the detailed description of this example, please refer to:
//!  `C2000Ware_PATH\utilities\clb_tool\clb_syscfg\doc\CLB Tool Users Guide.pdf`
//!
//! The objective of this example is to prevent simultaneous high or low outputs 
//! on a PWM pair. PWM modules 1 and 2 are configured to generate identical 
//! waveforms based on a fixed frequency up-count mode.
//!
//
//
//#############################################################################
// $TI Release: F28004x Support Library v5.05.00.00 $
// 
// $Copyright:
// Copyright (C) 2025 Texas Instruments Incorporated - http://www.ti.com/
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

void initCLB1(void);


uint32_t mode = 0;


void main(void)
{
    Device_init();
    Device_initGPIO();

    Interrupt_initModule();
    Interrupt_initVectorTable();

	SysCtl_enablePeripheral((SysCtl_PeripheralPCLOCKCR)0x0011);

    Board_init();

    initTILE1(myTILE1_BASE);

    CLB_setGPREG(myTILE1_BASE, mode);

    CLB_setOutputMask(myTILE1_BASE, 0x5, true);

    Interrupt_enable(INT_EPWM1);
    EINT;

    while(1)
    {
        asm(" NOP");
    }
}


__interrupt void INT_myEPWM1_ISR(void)
{
    EPWM_clearEventTriggerInterruptFlag(myEPWM1_BASE);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP3);
    CLB_setGPREG(myTILE1_BASE, mode & 3UL);
    asm(" NOP");
}
