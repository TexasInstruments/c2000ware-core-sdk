//#############################################################################
//! \file /dsp_Round_f28p55x.c
//!
//! \brief  Demo code for the Rounding example
//!
//! This example shows how to use the rnd_SP_RS() to round a floating
//! point scalar argument
//!
//
//  Group:             C2000
//  Target Family:     F28P55x
//
//#############################################################################
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


//*****************************************************************************
// includes
//*****************************************************************************
#include "driverlib.h"
#include "device.h"
#include "board.h"
#include "c2000ware_libraries.h"
#include "stdio.h"


//!
//! \addtogroup VECTOR_EXAMPLES Rounding of a Floating Point Scalar

// @{

//*****************************************************************************
// defines
//*****************************************************************************
#define SIZE            100U

//*****************************************************************************
// globals
//*****************************************************************************
//! \brief input to the rounding function
//!
float32_t x[SIZE] = {
    #include "data_input_round.h"
};

//! \brief Output from the rounding
//!
float32_t y[SIZE];


//! \brief Expected output
//!
float32_t y_exp[SIZE] = {
    #include "data_output_round.h"
};

uint16_t pass = 0, fail = 0;

//*****************************************************************************
// function definitions
//*****************************************************************************
//!
//! \brief main routine for the Rounding example
//! \return 1
//!
//! The code will round a series of floating point scalars using
//! the FPU library's rnd_SP_RS()
//!
//!  Watch Variables:
//! -# x Input
//! -# y Output
//!
int round_test(void)
{
    int i;

    //=========================================================================
    // Rounding test
    //=========================================================================
    for(i = 0; i < SIZE; i++){
        __asm(" NOP");
        y[i] = rnd_SP_RS(x[i]);
        __asm(" NOP");
        if(y[i] == y_exp[i]){
            pass++;
        }else{
            fail++;
        }
    }

    printf("Total of %d tests pass, and %d failure",pass,fail);

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

    round_test();

    while(1)
    {

    }
}

// End of main

// @} //addtogroup

// End of file
