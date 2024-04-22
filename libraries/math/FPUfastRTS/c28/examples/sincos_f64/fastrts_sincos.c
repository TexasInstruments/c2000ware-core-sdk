//#############################################################################
//
//! \file   fastrts_sincos.c
//!
//! \brief  Runs the sincos routine
//! \author Vishal Coelho
//! \date   Mar 1, 2016
//
//  Group:          C2000
//  Target Device:  TMS320F28004x
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
float64_t tolerance = 9.0e-13;

uint64_t toleranceLSBMantissa = 0;

float64_t test_output[TEST_SIZE << 1];
float64_t test_error[TEST_SIZE << 1];
//*****************************************************************************
// the function definitions
//*****************************************************************************
void FastRTS_runTest(void)
{
    // Locals
    uint16_t i, j;
    float64u_t in, out_s, out_c, gold_s, gold_c;
    float64u_t errld_s, errld_c, errulp_s, errulp_c;

    for(i = 0U, j = 0U; i < TEST_SIZE; i++, j=j+2)
    {
        out_s.f64  = DBL_MAX;
        out_c.f64  = DBL_MAX;
        in.f64   = test_input[i];
#if COMPILER_FPU64_SUPPORT == 1
        sincos(in.f64, &out_s, &out_c);
#else
       run_sincos(&in, &out_s, &out_c);
#endif //
        test_output[j]   = out_s.f64;
        test_output[j+1] = out_c.f64;
        
        gold_s.f64 = test_golden[j];
        gold_c.f64 = test_golden[j+1];

        if(((FastRTS_Example_calcError((float64_t *)&out_s,
                (float64_t *)&gold_s,
                (float64_t *)&errld_s,
                (uint64_t *)&errulp_s,
                &tolerance,
                toleranceLSBMantissa)) != -1) &&
           ((FastRTS_Example_calcError((float64_t *)&out_c,
                (float64_t *)&gold_c,
                (float64_t *)&errld_c,
                (uint64_t *)&errulp_c,
                &tolerance,
                toleranceLSBMantissa)) != -1))
        {
            pass++;
        }
        else
        {
            fail++;
        }
        test_error[j]   = errld_s.f64;
        test_error[j+1] = errld_c.f64;
    }
}

// End of File
