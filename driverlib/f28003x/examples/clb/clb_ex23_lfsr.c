//#############################################################################
//
// FILE:   clb_ex23_lfsr.c
//
// TITLE:  CLB LFSR
//
//! \addtogroup driver_example_list
//! <h1>CLB LFSR</h1>
//!
//! For the detailed description of this example, please refer to:
//!  `C2000Ware_PATH\utilities\clb_tool\clb_syscfg\doc\CLB Tool Users Guide.pdf`
//!
//! In this example the CLB COUNTER module is used in Linear Feedback Shift 
//! Register (LFSR) mode. This module is only available for CLB types 2 and up.
//!
//
//#############################################################################
// $TI Release: F28003x Support Library v5.03.00.00 $
// 
// $Copyright:
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com/
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


//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "board.h"
#include "clb_config.h"

//
// Shift register GP REG bits
//
#define GPREG_0_EVENT_DATA_SHIFT  0U
#define GPREG_1_MODE0_EN_SHIFT    1U

//
// Main
//
void main(void)
{
    uint32_t counterValue = 0;

    Device_init();
    Device_initGPIO();

    Interrupt_initModule();
    Interrupt_initVectorTable();

    Board_init();

    //
    // LFSR Mode
    // Poly = MATCH2 = 0x0000FFFF
    // MODE1 = 0
    //
    initTILE1(myCLBForTILE1_BASE);

    CLB_enableCLB(myCLBForTILE1_BASE);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    counterValue = CLB_getRegister(myCLBForTILE1_BASE, CLB_REG_CTR_C0);
    if (counterValue != 0)
    {
        //
        // Error
        //
        ESTOP0;
    }

    //
    // Match2 (Polynomial will toggle the first 16 bits. Value should be 0x0000FFFF
    //

    //
    // Write 1 to DATA
    //
    CLB_setGPREG(myCLBForTILE1_BASE, (1U << GPREG_0_EVENT_DATA_SHIFT) | (0U << GPREG_1_MODE0_EN_SHIFT));
    //
    // Write 1 to EN
    //
    CLB_setGPREG(myCLBForTILE1_BASE, (1U << GPREG_0_EVENT_DATA_SHIFT) | (1U << GPREG_1_MODE0_EN_SHIFT));


    counterValue = CLB_getRegister(myCLBForTILE1_BASE, CLB_REG_CTR_C0);
    if (counterValue != 0x0000FFFF)
    {
        //
        // Error
        //
        ESTOP0;
    }

    //
    // The next value should be 0x10001 if DATA is 0
    //

    //
    // Write 0 to DATA
    //
    CLB_setGPREG(myCLBForTILE1_BASE, (0U << GPREG_0_EVENT_DATA_SHIFT) | (0U << GPREG_1_MODE0_EN_SHIFT));
    //
    // Write 1 to EN
    //
    CLB_setGPREG(myCLBForTILE1_BASE, (0U << GPREG_0_EVENT_DATA_SHIFT) | (1U << GPREG_1_MODE0_EN_SHIFT));

    counterValue = CLB_getRegister(myCLBForTILE1_BASE, CLB_REG_CTR_C0);
    if (counterValue != 0x00010001)
    {
        //
        // Error
        //
        ESTOP0;
    }

    //
    // The next value should be 0x20002 if DATA is 1
    //

    //
    // Write 1 to DATA
    //
    CLB_setGPREG(myCLBForTILE1_BASE, (1U << GPREG_0_EVENT_DATA_SHIFT) | (0U << GPREG_1_MODE0_EN_SHIFT));
    //
    // Write 1 to EN
    //
    CLB_setGPREG(myCLBForTILE1_BASE, (1U << GPREG_0_EVENT_DATA_SHIFT) | (1U << GPREG_1_MODE0_EN_SHIFT));

    counterValue = CLB_getRegister(myCLBForTILE1_BASE, CLB_REG_CTR_C0);
    if (counterValue != 0x00020002)
    {
        //
        // Error
        //
        ESTOP0;
    }


    //
    // Shift successful!
    //
    ESTOP0;


    while(1)
    {

    }
}

//
// End of File
//
