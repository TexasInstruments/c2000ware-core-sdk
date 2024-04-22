//#############################################################################
//
//! \file   fid_i64byi32_test.c
//!
//! \brief  Runs the FID_i64byi32 routine
//! \author Vishal Coelho
//! \date   Apr 11, 2016
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
int64_t tolerance = 0;

int64_t test_output_quo[TEST_SIZE], test_error_quo[TEST_SIZE];
int32_t test_output_rem[TEST_SIZE], test_error_rem[TEST_SIZE];
reg64_t num_rem, den_quo;
//*****************************************************************************
// the function definitions
//*****************************************************************************
void FastRTS_runTest(void)
{
    // Locals
    uint16_t i;

    for(i = 0U; i < TEST_SIZE; i++)
    {
        den_quo.i64 = 0;
    	num_rem.i64 = test_dividend[i];
    	den_quo.L.i32 = test_divisor[i];

    	FID_i64byi32(&num_rem.i64, &den_quo.i64);

    	test_output_quo[i]   = den_quo.i64;
    	test_output_rem[i]   = num_rem.L.i32;

    	if(FID_Example_calcError((int64_t *)&den_quo.i64,
    	                (int64_t *)&test_quotient[i],
						(int64_t *)&test_error_quo[i],
    	                &tolerance,
						ERRORTYPE_I64) != -1)
        {
    		pass++;
        }
        else
        {
            fail++;
        }

        if(FID_Example_calcError((int32_t *)&num_rem.L.i32,
            	                (int32_t *)&test_remainder[i],
        						(int32_t *)&test_error_rem[i],
            	                &tolerance,
        						ERRORTYPE_I32) != -1)
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
