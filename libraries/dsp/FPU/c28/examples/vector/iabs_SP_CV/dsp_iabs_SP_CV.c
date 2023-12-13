//#############################################################################
//
//! \file   dsp_iabs_SP_CV.c
//!
//! \brief  Finds the inverse of the magnitude of each entry of a complex 
//!         vector
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
//   FPU_DSP_runVectorRoutines('iabsCV', 64, 'TYPE_FLOAT', 'FTYPE_C');
// "
// Please note that this script generates the input data using random values 
// ranging from -pi to pi so it may not be possible to generate the exact 
// same set of inputs and outputs given in this example.
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


float test_output[TEST_SIZE];
float test_error[TEST_SIZE];
//*****************************************************************************
// the function definitions
//*****************************************************************************
void DSP_runTest(void)
{
    // Locals
	uint16_t i;
    float32u_t out, gold, err;


    //Clear out the output and error arrays
    memset(test_output, 0U, TEST_SIZE*sizeof(float));
    memset(test_error, 0U, TEST_SIZE*sizeof(float));

    // Call the calculation routine
    iabs_SP_CV(test_output, (const complex_float *)test_input, TEST_SIZE);

    for(i = 0U; i < TEST_SIZE; i++)
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

    //Clear out the output and error arrays
    memset(test_output, 0U, TEST_SIZE*sizeof(float));
    memset(test_error, 0U, TEST_SIZE*sizeof(float));

    // Call the more efficient calculation routine for even sized inputs
    iabs_SP_CV_2(test_output, (const complex_float *)test_input, TEST_SIZE);

    for(i = 0U; i < TEST_SIZE; i++)
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
