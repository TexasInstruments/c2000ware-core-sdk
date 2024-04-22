//#############################################################################
//
//! \file   fastrts_sincos.c
//!
//! \brief  Runs the sincos routine
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
#define TEST_SIZE   (128U)
//*****************************************************************************
// the globals
//*****************************************************************************
// The global pass, fail values
uint16_t pass = 0U, fail = 0U;
// The absolute error between the result and expected values
float32_t tolerance = 2.5e-7;


float32_t test_output[TEST_SIZE << 1];
float32_t test_error[TEST_SIZE << 1];
//*****************************************************************************
// the function definitions
//*****************************************************************************
void FastRTS_runTest(void)
{
    // Locals
    uint16_t i, j;
    float32u_t in, out_s, out_c, gold_s, gold_c;
    float32u_t err_s, err_c;
    
    //<<VC160921: cant check ulp error as this only applies to
    // fixed point representation of the same set of numbers
    //
    //float32u_t errulp_s, errulp_c;
    //
    // VC160921>>
    

    for(i = 0U, j = 0U; i < TEST_SIZE; i++, j=j+2)
    {
        out_s.f32  = FLT_MAX;
        out_c.f32  = FLT_MAX;
        in.f32     = test_input[i];
        
        // Run the calculation function
         sincosf(in.f32, (float32_t *)&out_s, (float32_t *)&out_c);

        test_output[j]   = out_s.f32;
        test_output[j+1] = out_c.f32;
        
        gold_s.f32 = test_golden[j];
        gold_c.f32 = test_golden[j+1];

        err_s.f32  = fabsf(out_s.f32 - gold_s.f32);
        err_c.f32  = fabsf(out_c.f32 - gold_c.f32);
        
        if(err_s.f32 < tolerance)
        {
            pass++;
        }
        else
        {
            fail++;
        }
        test_error[j]   = err_s.f32;
        if(err_c.f32 < tolerance)
        {
            pass++;
        }
        else
        {
            fail++;
        }
        test_error[j+1] = err_c.f32;
    }
}

// End of File
