//#############################################################################
//
//! \file   fastrts_cosine.c
//!
//! \brief  Runs the CORDIC cosine routine
//! \author Vishal Coelho
//! \date   Dec 16, 2016
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
#include "fpu64/cordic.h"

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
float64_t tolerance = 1.0e-9;

uint64_t toleranceLSBMantissa = 0;

float64_t test_output[TEST_SIZE];
float64_t test_error[TEST_SIZE];

int64_t   x_i = 0, y_i = 0, z_i = 0;

CORDIC_F64 cordic;
CORDIC_F64_Handle hnd_cordic = &cordic;

//*****************************************************************************
// the function definitions
//*****************************************************************************
void FastRTS_runTest(void)
{
    // Locals
    uint16_t i;
    float64u_t in, out, gold, errld, errulp;
    

    // Initialize the object
    CORDIC_F64_setx_i(hnd_cordic, &x_i);
    CORDIC_F64_sety_i(hnd_cordic, &y_i);
	CORDIC_F64_setz_i(hnd_cordic, &z_i);
	CORDIC_F64_setN(hnd_cordic, 64);
	CORDIC_F64_setAtanTblPtr(hnd_cordic, CORDIC_F64_atanTable);
	CORDIC_F64_setRunKernelPtr(hnd_cordic, (v_pfn_v)CORDIC_F64_rotationKernel);

    for(i = 0U; i < TEST_SIZE; i++)
    {
        out.f64  = DBL_MAX;
        in.f64   = test_input[i];
#if COMPILER_FPU64_SUPPORT == 1
        out.f64  = cos(in.f64);
#else
        out = CORDIC_F64_cos(hnd_cordic, in);
#endif //
        test_output[i] = out.f64;
        gold.f64 = test_golden[i];

        if((FastRTS_Example_calcError((float64_t *)&out,
                (float64_t *)&gold,
                (float64_t *)&errld,
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
        test_error[i] = errld.f64;
    }
}

// End of File
