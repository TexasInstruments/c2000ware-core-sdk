//#############################################################################
//
//! \file   fid_f64byf64_test.c
//!
//! \brief  Runs the FID_f64byf64 routine
//! \author Vishal Coelho
//! \date   Apr 18 2016
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
#include "fpu64/fid.h"
#include "fpu.h"

//*****************************************************************************
// the defines
//*****************************************************************************
#define TEST_SIZE   (256U)
//*****************************************************************************
// the globals
//*****************************************************************************
// The global pass, fail values
uint16_t pass = 0U, fail = 0U;
// The absolute error between the result and expected values
float64_t tolerance = 1.0e-4;
// There should be at most 10 bits of error in the mantissa
uint64_t toleranceLSBMantissa = (1 << 9);

float64_t test_output_quo[TEST_SIZE], test_error_quo[TEST_SIZE];
float64_t num;
float64_t den;
//*****************************************************************************
// the function definitions
//*****************************************************************************
void FastRTS_runTest(void)
{
    // Locals
    uint16_t i;
    uint64_t    errulp;

    for(i = 0U; i < TEST_SIZE; i++)
    {
    	num = test_dividend[i];
    	den = test_divisor[i];

    	FID_f64byf64(&num, &den, &test_output_quo[i]);

        if((FastRTS_Example_calcError((float64_t *)&test_output_quo[i],
                (float64_t *)&test_quotient[i],
                (float64_t *)&test_error_quo[i],
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
    }
}

// End of File
