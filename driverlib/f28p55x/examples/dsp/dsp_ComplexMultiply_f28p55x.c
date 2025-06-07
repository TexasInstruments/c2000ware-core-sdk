//#############################################################################
//! \file /dsp_ComplexMultiply_f28p55x.c
//!
//! \brief  Complex Multiplication
//!
//! This example shows how to use the vector routines in the library to
//! calculate the complex product of two complex vectors
//!
//
//  Group:             C2000
//  Target Family:     F28P55X
//
//#############################################################################
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

//*****************************************************************************
// includes
//*****************************************************************************
#include "driverlib.h"
#include "device.h"
#include "board.h"
#include "c2000ware_libraries.h"
#include "stdio.h"
#include "string.h"


//!
//! \addtogroup VECTOR_EXAMPLES Complex Multiplication

// @{

//*****************************************************************************
// defines
//*****************************************************************************
#define SIZE        99U
#define EPSILON     0.001f

//*****************************************************************************
// globals
//*****************************************************************************
//! \brief input to the complex multiply function
//!
const complex_float x[SIZE] = {
    #include "data_input_cmplxmul1.h"
};

//! \brief input to the complex multiply function
//!
const complex_float y[SIZE] = {
    #include "data_input_cmplxmul2.h"
};

//! \brief output  of the complex vector inverse absolute function
//!
complex_float z[SIZE];

complex_float z_exp[SIZE] = {
    #include "data_output_cmplxmul.h"
};

uint16_t pass = 0, fail = 0;

//*****************************************************************************
// function definitions
//*****************************************************************************
//!
//! \brief main routine for the Complex Multiply example
//! \return returns a 1
//!
//!  Watch Variables:
//!
//! -# y Input
//! -# x Input
//! -# z Output
//!
int cmplx_mul_test(void)
{
    int i;

    //=========================================================================
    // Complex multiplication test
    //=========================================================================
    memset(z, 0, SIZE*sizeof(complex_float));

    for(i = 0; i < SIZE; i++){
        z[i] = mpy_SP_CSxCS(x[i], y[i]); // complex multiply


        if((fabsf(z[i].dat[0]- z_exp[i].dat[0]) < EPSILON) &&
                (fabsf(z[i].dat[1]- z_exp[i].dat[1]) < EPSILON)){
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

    cmplx_mul_test();

    while(1)
    {

    }
}

// End of main

// @} //addtogroup

// End of file
