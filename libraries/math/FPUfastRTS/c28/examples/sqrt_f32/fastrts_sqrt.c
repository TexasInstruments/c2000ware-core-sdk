//#############################################################################
//
//! \file   fastrts_sqrt.c
//!
//! \brief  Runs the sqrt routine
//! \author Vishal Coelho
//! \date   Sep 21, 2016
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
#include "fpu32/C28x_FPU_FastRTS.h"

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
float32_t tolerance = 2.5e-7;



float32_t test_output[TEST_SIZE];
float32_t test_error[TEST_SIZE];
//*****************************************************************************
// the function definitions
//*****************************************************************************
void FastRTS_runTest(void)
{
    // Locals
    uint16_t i;
    float32u_t in, out, gold, err;

    //<<VC160921: cant check ulp error as this only applies to
    // fixed point representation of the same set of numbers
    //
    //float32u_t errulp;
    //
    // VC160921>>

    for(i = 0U; i < TEST_SIZE; i++)
    {
        out.f32  = FLT_MAX;
        in.f32   = test_input[i];
        
        // Run the calculation function
        out.f32  = sqrtf(in.f32);

        test_output[i] = out.f32;
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
