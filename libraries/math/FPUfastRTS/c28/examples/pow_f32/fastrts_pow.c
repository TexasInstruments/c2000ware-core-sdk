//#############################################################################
//
//! \file   fastrts_pow.c
//!
//! \brief  Runs the powf routine
//! \author Vishal Coelho
//! \date   Feb 7, 2017
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

#define TEST_SIZE   (128U)

//*****************************************************************************
// the globals
//*****************************************************************************
// The global pass, fail values
uint16_t pass = 0U, fail = 0U;
// The absolute error between the result and logected values
float32_t tolerance = 4.0e-4;


float32_t test_output[TEST_SIZE];
float32_t test_error[TEST_SIZE];
//*****************************************************************************
// the function definitions
//*****************************************************************************
void FastRTS_runTest(void)
{
    // Locals
    uint16_t i, j;
    float32u_t in_y, in_x, out, gold, err;

    //<<VC170207: cant check ulp error as this only applies to
    // fixed point representation of the same set of numbers
    //
    //float32u_t errulp;
    //
    // VC170207>>

    for(i = 0U, j = 0U; i < TEST_SIZE; i++, j = j + 2)
    {
        out.f32  = FLT_MAX;
        in_x.f32   = test_input[j];
        in_y.f32   = test_input[j+1];
        
        // Run the calculation function
        out.f32  = powf(in_x.f32, in_y.f32);

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
