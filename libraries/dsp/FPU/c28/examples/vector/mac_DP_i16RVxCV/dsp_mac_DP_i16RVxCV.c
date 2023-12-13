//#############################################################################
//
//! \file   dsp_mac_DP_i16RVxCV.c
//!
//! \brief  Runs the double precision Multiply-and-Accumulate rotuine, of a 
//!         Real Vector (integer) and a Complex Vector
//! \author Vishal Coelho
//! \date   Jul 20, 2016
//
//  Group:          C2000
//  Target Device:  TMS320f2838x
//
// The input and golden files were obtained by running the following commands
// at the MATLAB command prompt
//      N = 64;
//      A = int16(randi([intmin('int16'), intmax('int16')],1,N));
//      S_A = sprintf('%6d, %6d, %6d, %6d, \n', A);
//      B = rand(1,N)+1i.*rand(1,N);
//      C = sum(double(A).*B);
//      D = [real(B); imag(B)];
//      S_D = sprintf('%13.10fL, %13.10fL, %13.10fL, %13.10fL, \n', D);
//      E = reshape(D, 1, 128);
//      F = [real(C), imag(C)];
//      S_F = sprintf('%13.10fL, %13.10fL, \n', F);
// Write the contents of "S_A" followed by "S_E" (in separate vectors)to 
// input.c and "S_F" to golden.c
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
float64_t tolerance = 1.0e-5;

extern int16_t test_input2[];

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
    result = mac_DP_i16RVxCV((complexf64_t *)&test_input[0U], 
                 (int16_t *)&test_input2[0U], TEST_SIZE);

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
