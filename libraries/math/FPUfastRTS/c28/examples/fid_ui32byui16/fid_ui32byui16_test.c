//#############################################################################
//
//! \file   fid_ui32byui16_test.c
//!
//! \brief  Runs the FID_ui32byui16 routine
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
uint32_t tolerance = 0;

uint32_t test_output_quo[TEST_SIZE], test_error_quo[TEST_SIZE];
uint16_t test_output_rem[TEST_SIZE], test_error_rem[TEST_SIZE];
uint32_t num_rem, den_quo;
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
    	den_quo = (uint32_t)test_divisor[i];

    	FID_ui32byui16(&num_rem, &den_quo);

    	test_output_quo[i]   = den_quo;
    	test_output_rem[i]   = (uint16_t)num_rem;

    	if(FID_Example_calcError((uint32_t *)&den_quo,
    	                (uint32_t *)&test_quotient[i],
						(uint32_t *)&test_error_quo[i],
    	                &tolerance,
						ERRORTYPE_UI32) != -1)
        {
    		pass++;
        }
        else
        {
            fail++;
        }

        if(FID_Example_calcError((uint16_t *)&num_rem,
            	                (uint16_t *)&test_remainder[i],
        						(uint16_t *)&test_error_rem[i],
            	                &tolerance,
        						ERRORTYPE_UI16) != -1)
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
