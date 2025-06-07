//#############################################################################
//! \file /dsp_InvComplexAbsVec_f28p55x.c
//!
//! \brief  Inverse Absolute value of a complex vector test
//!
//! This example shows how to use the vector routines in the library to
//! calculate the inverse absolute of a complex vector
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

#include "string.h"
#include "stdio.h"


//!
//! \addtogroup VECTOR_EXAMPLES Inverse Absolute Value of a Complex Vector

// @{

//*****************************************************************************
// defines
//*****************************************************************************
#define TEST_SIZE   99U
#define N1          98U     // even size
#define N2          99U     // odd size
#define EPSILON     0.001f

//*****************************************************************************
// globals
//*****************************************************************************
//! \brief input to the complex vector absolute (and inverse abs) function
//!
complex_float x[TEST_SIZE] = {
    #include "data_input_invcmplxvec.h"
};

//! \brief output  of the complex vector inverse absolute function
//!
float32_t z[TEST_SIZE];

float32_t z_exp[TEST_SIZE] = {
    #include "data_output_invcmplxvec.h"
};

uint16_t pass =0, fail = 0;

//*****************************************************************************
// function definitions
//*****************************************************************************
//!
//! \brief main routine for the Inverse Absolute Value of a Complex Vector
//!  example
//! \return 1
//!
//!  Watch Variables:
//!
//! -# z Output for the vector inverse absolute function
//! -# x Input for the vector absolute (and inverse) function
//!
int inv_cmplx_vec_test(void)
{
    int i;

    //=========================================================================
    // Inverse Absolute value of a complex vector test
    //=========================================================================
    // Run the test on a vector with even number of elements
    memset(z, 0, TEST_SIZE*sizeof(float32_t));

    //TMU version (iabs_SP_CV_TMU0()) would be called when --tmu_support= is enabled in the project properties
    //Otherwise the regular FPU32 version would be called instead
    iabs_SP_CV(z, x, N1);        // complex absolute value

    // Check the output
    for(i = 0; i < N1; i++){
        if(fabsf(z[i] - z_exp[i]) < EPSILON){
            pass++;
        }else{
            fail++;
        }
    }

    // Run the same test on a vector with odd number of elements
    memset(z, 0, TEST_SIZE*sizeof(float32_t));

    iabs_SP_CV(z, x, N2);        // complex absolute value

    // Check the output
    for(i = 0; i < N2; i++){
        if(fabsf(z[i] - z_exp[i]) < EPSILON){
            pass++;
        }else{
            fail++;
        }
    }

    // If the input has an even number of entries, it would be faster to
    // run the iabs_SP_CV_2() instead. With the TMU support turned on, use
    // the iabs_SP_CV_TMU0() instead - note that the TMU equivalent has one
    // function for both even and odd numbered vectors
    memset(z, 0, TEST_SIZE*sizeof(float32_t));
#ifdef __TMS320C28XX_TMU__
    iabs_SP_CV_TMU0(z, x, N1); // complex absolute value
#else
    iabs_SP_CV_2(z, x, N1);  // complex absolute value
#endif //__TMS320C28XX_TMU__

    // Check the output
    for(i = 0; i < N1; i++){
        if(fabsf(z[i] - z_exp[i]) < EPSILON){
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

    inv_cmplx_vec_test();

    while(1)
    {

    }
}

// End of main

// @} //addtogroup

// End of file
