//#############################################################################
//
//! \file   dsp_mpy_SP_CSxCS.c
//!
//! \brief  Multiplication of Two Complex Single Precision Numbers
//! \author Vishal Coelho
//! \date   Sep 16, 2016
//
//  Group:          C2000
//  Target Device:  TMS320f28002x
//
// The input and golden files were obtained by running the MATLAB script, 
// FPU_DSP_runVectorRoutines.m (under reference/MATLAB), at the MATLAB command 
// line as follows
// "
//   FPU_DSP_runVectorRoutines('mpyCSbyCS', 64, 'TYPE_FLOAT', 'FTYPE_C');
// "
// Please note that this script generates the input data using random values 
// ranging from -pi to pi so it may not be possible to generate the exact 
// same set of inputs and outputs given in this example.
// Also note the second set of complex scalars is tacked on to the end of the 
// first set in the input file
//
//#############################################################################
//
//
// $Copyright: Copyright (C) 2023 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################


//*****************************************************************************
// the includes
//*****************************************************************************
#include "fpu.h"
#include "dsp.h"
#include "dsp_examples_setup.h"
#include "fpu32/fpu_vector.h"
#include <string.h>

//*****************************************************************************
// the defines
//*****************************************************************************
#define TEST_SIZE       (64U)

//*****************************************************************************
// the globals
//*****************************************************************************
// The global pass, fail values
uint16_t pass = 0U, fail = 0U;
// The absolute error between the result and expected values
float tolerance = 1.0e-6;


// The second set of complex scalars is tacked on to the end of the 
// first set
float *test_input2 = &test_input[2U*TEST_SIZE];

float test_output[2U*TEST_SIZE];
float test_error[2U*TEST_SIZE];
//*****************************************************************************
// the function definitions
//*****************************************************************************
void DSP_runTest(void)
{
    // Locals
    uint16_t i, j;
    float32u_t out, gold,  err;
    complex_float w, x, y;



    //Clear out the output and error arrays
    memset(test_output, 0U, (2U*TEST_SIZE)*sizeof(float));
    memset(test_error, 0U, (2U*TEST_SIZE)*sizeof(float));


    for(i = 0U, j =0U; i < 2U*TEST_SIZE; i=i+2)
    {
    	w.dat[0] = test_input[i];
    	w.dat[1] = test_input[i+1];
    	x.dat[0] = test_input2[i];
    	x.dat[1] = test_input2[i+1];

        // Call the calculation routine
    	y = mpy_SP_CSxCS(w, x);

    	// Store the output
        test_output[j++] = y.dat[0];
        test_output[j++] = y.dat[1];
    }              
    
    // Compute the error
    for(i = 0U; i < 2U*TEST_SIZE; i++)
    {
        out.f32  = test_output[i];
        gold.f32 = test_golden[i];
        err.f32  = fabsf(out.f32 - gold.f32);
        if(err.f32 < tolerance)
        {
            pass++;
        }
        else
        {
            fail++;
        }
        test_error[i] = err.f32;
    }
}

// End of File
