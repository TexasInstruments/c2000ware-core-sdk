//#############################################################################
//
//! \file   dsp_rnd_DP_RS.c
//!
//! \brief  Rounding (Unbiased) of a Floating Point Scalar (Double Precision).
//! \author Vishal Coelho
//! \date   Jul 25, 2016
//
//  Group:          C2000
//  Target Device:  TMS320f2838x
//
// The input and golden files were obtained by running the MATLAB script, 
// FPU_DSP_runVectorRoutines.m (under reference/MATLAB), at the MATLAB command 
// line as follows
// "
//   FPU_DSP_runVectorRoutines('roundRS', 64, 'TYPE_DOUBLE', 'FTYPE_C');
// "
// Please note that this script generates the input data using random values 
// so it may not be possible to generate the exact same set of inputs and 
// outputs given in this example.
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
float64_t tolerance = 1.0e-10;
float64_t test_output[TEST_SIZE];
float64_t test_error[TEST_SIZE];
//*****************************************************************************
// the function definitions
//*****************************************************************************
void DSP_runTest(void)
{
    // Locals
	uint16_t i;
    float64u_t out, gold, errld;


    //Clear out the output and error arrays
    memset(test_output, 0U, TEST_SIZE*sizeof(float64_t));
    memset(test_error, 0U, TEST_SIZE*sizeof(float64_t));

    for(i = 0U; i < TEST_SIZE; i++)
    {
        // Call the calculation routine
        test_output[i] = rnd_DP_RS(test_input[i]);

    }
    
    for(i = 0U; i < TEST_SIZE; i++)
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
