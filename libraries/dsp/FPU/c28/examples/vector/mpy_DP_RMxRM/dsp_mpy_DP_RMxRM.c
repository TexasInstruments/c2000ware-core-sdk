//#############################################################################
//
//! \file   dsp_mpy_DP_RMxRM.c
//!
//! \brief  Multiplication of Two Real Double Precision Matrices
//! \author Vishal Coelho
//! \date   Jul 12, 2017
//
//  Group:          C2000
//  Target Device:  TMS320f2838x
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
// $Copyright: Copyright (C) 2023 Texas Instruments Incorporated -
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
#define MAT1_NUM_ROWS   (16U)
#define MAT1_NUM_COLS   (4U)
#define MAT2_NUM_COLS   (16U)

//*****************************************************************************
// the globals
//*****************************************************************************
// The global pass, fail values
uint16_t pass = 0U, fail = 0U;
// The absolute error between the result and expected values
float64_t tolerance = 5.0e-12;
// The second set of complex vectors is tacked on to the end of the 
// first set
float64_t *test_input2 = &test_input[TEST_SIZE];

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
float64_t test_output[MAT1_NUM_ROWS*MAT2_NUM_COLS];
float64_t test_error[MAT1_NUM_ROWS*MAT2_NUM_COLS];
//*****************************************************************************
// the function definitions
//*****************************************************************************
void DSP_runTest(void)
{
    // Locals
    uint16_t i;
    float64u_t out, gold, errld;

    
    //Clear out the output and error arrays
    memset(test_output, 0U, (MAT1_NUM_ROWS*MAT2_NUM_COLS)*sizeof(float64_t));
    memset(test_error, 0U, (MAT1_NUM_ROWS*MAT2_NUM_COLS)*sizeof(float64_t));


    // Call the calculation routine
    mpy_DP_RMxRM((float64_t *)test_output,
                 (float64_t *)test_input,
                 (float64_t *)test_input2,
                 MAT1_NUM_ROWS, MAT1_NUM_COLS, MAT2_NUM_COLS);
    
    // Compute the error
    for(i = 0U; i < MAT1_NUM_ROWS*MAT2_NUM_COLS; i++)
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

    
    //Clear out the output and error arrays
    memset(test_output, 0U, (MAT1_NUM_ROWS*MAT2_NUM_COLS)*sizeof(float64_t));
    memset(test_error, 0U, (MAT1_NUM_ROWS*MAT2_NUM_COLS)*sizeof(float64_t));


    // Call the calculation routine
    mpy_DP_RMxRM_2((float64_t *)test_output,
                   (float64_t *)test_input,
                   (float64_t *)test_input2,
                   MAT1_NUM_ROWS, MAT1_NUM_COLS, MAT2_NUM_COLS);

    // Compute the error
    for(i = 0U; i < MAT1_NUM_ROWS*MAT2_NUM_COLS; i++)
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
