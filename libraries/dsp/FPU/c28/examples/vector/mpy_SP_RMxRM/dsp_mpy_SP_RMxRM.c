//#############################################################################
//
//! \file   dsp_mpy_SP_RMxRM.c
//!
//! \brief  Multiplication of Two Real Matrices
//! \author Vishal Coelho
//! \date   Mar 30, 2017
//
//  Group:          C2000
//  Target Device:  TMS320f28002x
//
// The input and golden files were obtained by running the MATLAB script, 
// FPU_DSP_runVectorRoutines.m (under reference/MATLAB), at the MATLAB command 
// line as follows
// "
//   FPU_DSP_runVectorRoutines('mpyRMbyRM', 64, 'TYPE_FLOAT', 'FTYPE_C');
// "
// Please note that this script generates the input data using random values 
// ranging from -pi to pi so it may not be possible to generate the exact 
// same set of inputs and outputs given in this example.
// Also note the second complex vector is tacked on to the end of the 
// first vector in the input file
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
#define MAT1_NUM_ROWS   (16U)
#define MAT1_NUM_COLS   (4U)
#define MAT2_NUM_COLS   (16U)

//*****************************************************************************
// the globals
//*****************************************************************************
// The global pass, fail values
uint16_t pass = 0U, fail = 0U;
// The absolute error between the result and expected values
float tolerance = 2.0e-6;


// The second set of complex vectors is tacked on to the end of the 
// first set
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
float test_output[MAT1_NUM_ROWS*MAT2_NUM_COLS];
float test_error[MAT1_NUM_ROWS*MAT2_NUM_COLS];
//*****************************************************************************
// the function definitions
//*****************************************************************************
void DSP_runTest(void)
{
    // Locals
    uint16_t i;
    float32u_t out, gold, err;

    
    //Clear out the output and error arrays
    memset(test_output, 0U, (MAT1_NUM_ROWS*MAT2_NUM_COLS)*sizeof(float));
    memset(test_error, 0U, (MAT1_NUM_ROWS*MAT2_NUM_COLS)*sizeof(float));


    // Call the calculation routine
    mpy_SP_RMxRM((float *)test_output,
                 (const float *)test_input,
                 (const float *)test_input2,
                 MAT1_NUM_ROWS, MAT1_NUM_COLS, MAT2_NUM_COLS);
    
    // Compute the error
    for(i = 0U; i < MAT1_NUM_ROWS*MAT2_NUM_COLS; i++)
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
    memset(test_output, 0U, (MAT1_NUM_ROWS*MAT2_NUM_COLS)*sizeof(float));
    memset(test_error, 0U, (MAT1_NUM_ROWS*MAT2_NUM_COLS)*sizeof(float));


    // Call the calculation routine
    mpy_SP_RMxRM_2((float *)test_output,
                   (const float *)test_input,
                   (const float *)test_input2,
                   MAT1_NUM_ROWS, MAT1_NUM_COLS, MAT2_NUM_COLS);

    // Compute the error
    for(i = 0U; i < MAT1_NUM_ROWS*MAT2_NUM_COLS; i++)
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
