//#############################################################################
//! \file /dsp_ComplexAbsVec_f28p55x.c
//!
//! \brief  Absolute value of a complex vector test
//!
//! This example shows how to use the vector routines in the library to
//! calculate the absolute (and inverse absolute) of a vector
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

//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "board.h"
#include "c2000ware_libraries.h"
#include "stdio.h"
#include "string.h"

//!
//! \addtogroup VECTOR_EXAMPLES Absolute Value of a Complex Vector

// @{

//*****************************************************************************
// defines
//*****************************************************************************
#define TEST_SIZE        99U
#define N1          98U     // even size
#define N2          99U     // odd size
#define EPSILON     0.001f

//*****************************************************************************
// globals
//*****************************************************************************
//! \brief input to the complex vector absolute (and inverse abs) function
//!
const complex_float x[TEST_SIZE] = {
    #include "data_input_cmplxvec.h"
};

//! \brief output  of the complex vector absolute function
//!
float32_t y[TEST_SIZE];

const float32_t y_exp[TEST_SIZE] = {
    #include "data_output_cmplxvec1.h"
};

//! \brief output  of the complex vector inverse absolute function
//!
float32_t z[TEST_SIZE];

const float32_t z_exp[TEST_SIZE] = {
    #include "data_output_cmplxvec2.h"
};

uint16_t pass = 0, fail = 0;

int cmplx_vec_test(void)
{
    int i;
    //=========================================================================
    // Absolute value of a complex vector test
    //=========================================================================
    // Run the test on a vector with even number of elements
    memset(y, 0, TEST_SIZE*sizeof(float32_t));

    //TMU version (abs_SP_CV_TMU0()) would be called when --tmu_support= is enabled in the project properties
    //Otherwise the regular FPU32 version would be called instead
    abs_SP_CV(y, x, N1);  // complex absolute value

    // Check the output
    for(i = 0; i < N1; i++){
        if(fabsf(y[i] - y_exp[i]) < EPSILON){
            pass++;
        }else{
            fail++;
        }
    }

    // Run the same test on a vector with odd number of elements
    memset(y, 0, TEST_SIZE*sizeof(float));

    //TMU version (abs_SP_CV_TMU0()) would be called when --tmu_support= is enabled in the project properties
    //Otherwise the regular FPU32 version would be called instead
    abs_SP_CV(y, x, N2);  // complex absolute value

    // Check the output
    for(i = 0; i < N2; i++){
        if(fabsf(y[i] - y_exp[i]) < EPSILON){
            pass++;
        }else{
            fail++;
        }
    }

    // If the input has an even number of entries, it would be faster to
    // run the abs_SP_CV_2() instead. With the TMU0 support turned on, use
    // the abs_SP_CV_TMU0() instead - note that the TMU equivalent has one
    // function for both even and odd numbered vectors
    memset(y, 0, TEST_SIZE*sizeof(float));

#ifdef __TMS320C28XX_TMU__
    abs_SP_CV_TMU0(y, x, N1); // complex absolute value
#else
    abs_SP_CV_2(y, x, N1);  // complex absolute value
#endif //_TMS320C28XX_TMU0__

    // Check the output
    for(i = 0; i < N1; i++){
        if(fabsf(y[i] - y_exp[i]) < EPSILON){
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

    cmplx_vec_test();

    while(1)
    {
        
    }
}

//
// End of File
//
