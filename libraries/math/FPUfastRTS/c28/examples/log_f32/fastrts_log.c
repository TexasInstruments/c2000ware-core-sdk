//#############################################################################
//
//! \file   fastrts_log.c
//!
//! \brief  Runs the log routine
//! \author Vishal Coelho
//! \date   Jan 27, 2017
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
// The absolute error between the result and logected values
float32_t tolerance = 1e-5;


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

    //<<VC170127: cant check ulp error as this only applies to
    // fixed point representation of the same set of numbers
    //
    //float32u_t errulp;
    //
    // VC170127>>

    for(i = 0U; i < TEST_SIZE; i++)
    {
        out.f32  = FLT_MAX;
        in.f32   = test_input[i];
        
        // Run the calculation function
        out.f32  = logf(in.f32);

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
