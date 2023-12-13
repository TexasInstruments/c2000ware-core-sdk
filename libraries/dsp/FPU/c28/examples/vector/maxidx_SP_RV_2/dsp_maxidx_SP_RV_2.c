//#############################################################################
//
//! \file   dsp_maxidx_SP_RV_2.c
//!
//! \brief  Index of Maximum Value of an Even Length Real Array 
//!         (Single Precision).
//! \author Vishal Coelho
//! \date   Sep 16, 2016
//
//  Group:          C2000
//  Target Device:  TMS320f28002x
//
// The input and golden files were obtained by running the MATLAB script, 
// FPU_DSP_runVectorRoutines.m (under reference/MATLAB), at the MATLAB command 
// line as follows
// "
//   FPU_DSP_runVectorRoutines('maxidxRV', 64, 'TYPE_FLOAT', 'FTYPE_C');
// "
// Please note that this script generates the input data using random values 
// ranging from -pi to pi so it may not be possible to generate the exact 
// same set of inputs and outputs given in this example.
//
//#############################################################################
//
//
// $Copyright: Copyright (C) 2023 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################


//*****************************************************************************
// the includes
//*****************************************************************************
#include "fpu.h"
#include "dsp.h"
#include "dsp_examples_setup.h"
#include "fpu32/fpu_vector.h"

//*****************************************************************************
// the defines
//*****************************************************************************
#define TEST_SIZE       (64U)

//*****************************************************************************
// the globals
//*****************************************************************************
// The global pass, fail values
uint16_t pass = 0U, fail = 0U;
// The absolute error between the result and expected values
float tolerance = 1.0e-9;


extern uint16_t test_golden_ui16[];

uint16_t test_output_ui16[1U];
uint16_t test_error_ui16[1U];
//*****************************************************************************
// the function definitions
//*****************************************************************************
void DSP_runTest(void)
{
    // Locals
    uint16_t result = 0U;

    // Call the calculation routine
    result = maxidx_SP_RV_2((const float *)test_input, TEST_SIZE);

    test_output_ui16[0U] = result;

    if(result == test_golden_ui16[0U])
    {
    	pass++;
    }
    else
    {
    	fail++;
    }
}

// End of File
