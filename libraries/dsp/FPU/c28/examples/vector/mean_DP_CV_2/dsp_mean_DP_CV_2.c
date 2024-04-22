//#############################################################################
//
//! \file   dsp_mean_DP_CV_2.c
//!
//! \brief  Double Precision Mean of Real and Imaginary Parts of a Complex 
//!         Vector
//! \author Vishal Coelho
//! \date   Jul 21, 2016
//
//  Group:          C2000
//  Target Device:  TMS320f2838x
//
// The input and golden files were obtained by running the MATLAB script, 
// FPU_DSP_runVectorRoutines.m (under reference/MATLAB), at the MATLAB command 
// line as follows
// "
//   FPU_DSP_runVectorRoutines('meanCV', 64, 'TYPE_DOUBLE', 'FTYPE_C');
// "
// Please note that this script generates the input data using random values 
// ranging from -pi to pi so it may not be possible to generate the exact 
// same set of inputs and outputs given in this example.
//
//#############################################################################
//
//
// $Copyright: Copyright (C) 2024 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################


//*****************************************************************************
// the includes
//*****************************************************************************
#include "fpu.h"
#include "dsp.h"
#include "dsp_examples_setup.h"
#include "fpu64/vector.h"

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
float64_t tolerance = 1.0e-10;
float64_t test_output[2U];
float64_t test_error[2U];
//*****************************************************************************
// the function definitions
//*****************************************************************************
void DSP_runTest(void)
{
    // Locals
	uint16_t i;
    complexf64_t result;
    float64u_t out, gold, errld;

    result.real = DBL_MAX;
    result.imag = DBL_MAX;

    // Call the calculation routine
    result = mean_DP_CV_2((const complexf64_t *)test_input, TEST_SIZE);

    test_output[0U] = result.real;
    test_output[1U] = result.imag;

    for(i = 0U; i < 2U; i++)
    {
        out.f64  = test_output[i];
        gold.f64 = test_golden[i];

        // Calculation of error and comparison with tolerance
                errld.f64 = fabsf(out.f64 - gold.f64);
                       if(errld.f64 < tolerance)
                               {
                                   pass++;
                               }
                               else
                               {
                                   fail++;
                               }
                test_error[i] = errld.f64;
      }

    
}

// End of File
