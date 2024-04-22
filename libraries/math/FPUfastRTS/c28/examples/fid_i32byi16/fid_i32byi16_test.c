//#############################################################################
//
//! \file   fid_i32byi16_test.c
//!
//! \brief  Runs the FID_i32byi16 routine
//! \author Vishal Coelho
//! \date   Apr 15, 2016
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
int32_t tolerance = 0;

int32_t test_output_quo[TEST_SIZE], test_error_quo[TEST_SIZE];
int16_t test_output_rem[TEST_SIZE], test_error_rem[TEST_SIZE];
int32_t num_rem, den_quo;
//*****************************************************************************
// the function definitions
//*****************************************************************************
void FastRTS_runTest(void)
{
    // Locals
    uint16_t i;

    for(i = 0U; i < TEST_SIZE; i++)
    {

    	num_rem = test_dividend[i];
    	den_quo = (int32_t)test_divisor[i];

    	FID_i32byi16(&num_rem, &den_quo);

    	test_output_quo[i]   = den_quo;
    	test_output_rem[i]   = (int16_t)num_rem;

    	if(FID_Example_calcError((int32_t *)&den_quo,
    	                (int32_t *)&test_quotient[i],
						(int32_t *)&test_error_quo[i],
    	                &tolerance,
						ERRORTYPE_I32) != -1)
        {
    		pass++;
        }
        else
        {
            fail++;
        }

        if(FID_Example_calcError((int16_t *)&num_rem,
            	                (int16_t *)&test_remainder[i],
        						(int16_t *)&test_error_rem[i],
            	                &tolerance,
        						ERRORTYPE_I16) != -1)
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
