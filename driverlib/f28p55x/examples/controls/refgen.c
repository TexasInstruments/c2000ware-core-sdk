//#############################################################################
//! \file /refgen.c
//!
//!
//! This example shows how to use SysConfig to setup and run DCL's reference 
//! generator
//
//  Group:             C2000
//  Target Family:     F28P55X
//
//#############################################################################
// $Copyright:
// Copyright (C) 2022 Texas Instruments Incorporated - http://www.ti.com
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


//*****************************************************************************
// includes
//*****************************************************************************
#include "driverlib.h"
#include "device.h"
#include "board.h"
#include "c2000ware_libraries.h"
#include "stdio.h"

//!
//! \addtogroup DCL_EXAMPLES Ref Gen example

// @{

//
// declared & initialized by sysconfig
//
extern DCL_REFGEN myREFGEN0;
extern FDLOG LoggerSineA;
extern FDLOG LoggerSineB;
extern FDLOG LoggerSineC;

uint16_t isrCnt = 0;
uint16_t isrStopCnt = 400;

uint16_t currIdxA = 0;
uint16_t currIdxB = 0;
uint16_t currIdxC = 0;


int Run_RefGen_Logger()
{

    float32_t sineA, sineB, sineC;

    //
    // Runs reference generator based on pre-configured settings denoted in sysconfig
    //
    DCL_runRefgen(&myREFGEN0);

    //
    // Save generated phase output to the data logger
    //
    sineA = DCL_getRefgenPhaseA(&myREFGEN0);
    sineB = DCL_getRefgenPhaseB(&myREFGEN0);
    sineC = DCL_getRefgenPhaseC(&myREFGEN0);
    DCL_writeLog(&LoggerSineA, sineA);
    DCL_writeLog(&LoggerSineB, sineB);
    DCL_writeLog(&LoggerSineC, sineC);

    //
    // Record the latest index for each data logger for debugging purposes
    //
    currIdxA = FDLOG_ELEMENT(&LoggerSineA);
    currIdxB = FDLOG_ELEMENT(&LoggerSineB);
    currIdxC = FDLOG_ELEMENT(&LoggerSineC);

    return 1;
}

//
// Main
//
void main(void)
{
    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Disable pin locks and enable internal pull-ups.
    //
    Device_initGPIO();

    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // PinMux and Peripheral Initialization
    //
    Board_init();

    //
    // C2000Ware Library initialization
    //
    C2000Ware_libraries_init();

    //
    // Enable Global Interrupt (INTM) and real time interrupt (DBGM)
    //
    EINT;
    ERTM;

    while(1)
    {

    }
}

// initialize CPU timer0 in sysconfig
interrupt void timer_Isr(void)
{
    if (isrCnt < isrStopCnt)
    {
        Run_RefGen_Logger();
        isrCnt++;
    }
    else
    {
        Interrupt_disable(INT_myCPUTIMER0);
        DCL_BREAK_POINT;
    }

    Interrupt_clearACKGroup(INT_myCPUTIMER0_INTERRUPT_ACK_GROUP);
}

// End of main

// @} //addtogroup

// End of file
