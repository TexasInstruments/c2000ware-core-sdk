//#############################################################################
//
//! \file   fastrts_div.c
//!
//! \brief  Runs the FD$$DIV routine
//! \author Vishal Coelho
//! \date   Jan 5, 2016
//
//  Group:          C2000
//  Target Device:  TMS320F28004x
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
#include "fastrts_examples_setup.h"
#include "fastrts.h"
#include "fpu.h"

//*****************************************************************************
// the defines
//*****************************************************************************
#define TEST_SIZE   (512U)
//*****************************************************************************
// the globals
//*****************************************************************************
// The global pass, fail values
uint16_t pass = 0U, fail = 0U;
// The absolute error between the result and expected values
float64_t tolerance = 1.0e-6;
// There should be at most 10 bits of error in the mantissa
uint64_t toleranceLSBMantissa = (1 << 9);

float64_t test_output[TEST_SIZE];
float64_t test_error[TEST_SIZE];
//*****************************************************************************
// the function definitions
//*****************************************************************************
void FastRTS_runTest(void)
{
    // Locals
    uint16_t i, j;
    float64u_t in1, in2, out, gold, errld, errulp;
    
    for(i = 0U, j = 0U; i < TEST_SIZE; i++, j = j + 2U)
    {
        out.f64  = DBL_MAX;
        in1.f64  = test_input[j];
        in2.f64  = test_input[j + 1U];
#if COMPILER_FPU64_SUPPORT == 1
        out.f64  = FD$$DIV(in1.f64, in2.f64);
#else
       run_div(&out, &in1, &in2);
#endif //
       test_output[i] = out.f64;
       gold.f64 = test_golden[i];

       if((FastRTS_Example_calcError((float64_t *)&out,
                (float64_t *)&gold,
                (float64_t *)&errld,
                (uint64_t *)&errulp,
                &tolerance,
                toleranceLSBMantissa)) != -1)
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
