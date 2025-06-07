//#############################################################################
//
//! \file   dsp_mpy_SP_RVxRV_2.c
//!
//! \brief  Element Wise Multiplication of two Real Vectors (Single Precision)
//! \author Vishal Coelho
//! \date   Sep 16, 2016
//
//  Group:          C2000
//  Target Device:  TMS320f28002x
//
// The input and golden files were obtained by running the following commands
// at the MATLAB command line
//    N = 64;
//    A = -100 + (100 - -100).*rand(1,N);
//    S_A = sprintf('%15.10fF, %15.10fF, %15.10fF, %15.10fF, \n', A);
//    B = -100 + (100 - -100).*rand(1,N);
//    S_B = sprintf('%15.10fF, %15.10fF, %15.10fF, %15.10fF, \n', B);
//    C = A.*B;
//    S_C = sprintf('%16.10fF, %16.10fF, %16.10fF, %16.10fF, \n', C);
// Write the contents of S_A followed by S_B to the array test_input in 
// input.c, and the contents of S_C to test_golden in golden.c
//
//#############################################################################
//
//
// $Copyright: Copyright (C) 2025 Texas Instruments Incorporated -
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
float tolerance = 5.0e-4;


// The real vector tacked on to the end of the complex vector
float *test_input2 = &test_input[TEST_SIZE];

#ifdef __TI_EABI__
#ifdef __cplusplus
#pragma DATA_SECTION(".bss:output")
#else
#pragma DATA_SECTION(test_output, ".bss:output")
#endif // __cplusplus
#else
#ifdef __cplusplus
#pragma DATA_SECTION(".ebss:output")
#else
#pragma DATA_SECTION(test_output, ".ebss:output")
#endif // __cplusplus
#endif //__TI_EABI__
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
    memset(test_error, 0U,  TEST_SIZE*sizeof(float));


    // Call the calculation routine
    mpy_SP_RVxRV_2((float *)test_output, 
                   (const float *)test_input, 
                   (const float *)test_input2, TEST_SIZE);
    
    // Compute the error
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
