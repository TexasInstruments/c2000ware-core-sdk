//#############################################################################
//
//! \file   dsp_mac_SP_CVxCV.c
//!
//! \brief  Runs the single precision complex vector MAC routine
//! \author Vishal Coelho
//! \date   Jul 18, 2016
//
//  Group:          C2000
//  Target Device:  TMS320f28002x
//
// The input and golden files were obtained by running the MATLAB script, 
// FPU_DSP_runVectorRoutines.m (under reference/MATLAB), at the MATLAB command 
// line as follows
// "
//   FPU_DSP_runVectorRoutines('macCVbyCV', 64, 'TYPE_FLOAT', 'FTYPE_C');
// "
// Please note that this script generates the input data using random values 
// ranging from -pi to pi so it may not be possible to generate the exact 
// same set of inputs and outputs given in this example.
// Also note the second complex vector is tacked on to the end of the first 
// vector in the input file
//
//#############################################################################
//
//
// 
// C2000Ware v5.03.00.00
//
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
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
float tolerance = 1.0e-5;

//<<VC160916: cant check ulp error as this only applies to
// fixed point representation of the same set of numbers
//
// a tolerance of 1.0e-5 represented in IEEE754 format is
// 1.31072*2^-17, so the mantissa is roughly accurate to 17 bits
// Therefore, there may be error in the 32-17 = 15 LSbs
// uint32_t toleranceLSBMantissa = (1UL << 15);
//
// VC160916>>

// The second complex vector is tacked on to the end of the first complex 
// vector 
const float *test_input2 = &test_input[2U*TEST_SIZE];

#ifdef __TI_EABI__
#ifdef __cplusplus
#pragma DATA_SECTION(".bss:output")
#else
#pragma DATA_SECTION(test_output, ".bss:output")
#endif // __cplusplus
#else
#ifdef __cplusplus
#pragma DATA_SECTION(".ebss:output")
#else
#pragma DATA_SECTION(test_output, ".ebss:output")
#endif // __cplusplus
#endif //__TI_EABI__
float test_output[2U];
float test_error[2U];
//*****************************************************************************
// the function definitions
//*****************************************************************************
void DSP_runTest(void)
{
    // Locals
    complex_float result;
    float32u_t out, gold, err;

    //<<VC160916: cant check ulp error as this only applies to
    // fixed point representation of the same set of numbers
    //
    //float32u_t errulp;
    //
    // VC160916>>

    result.dat[0] = FLT_MAX;
    result.dat[1] = FLT_MAX;

    // Call the calculation routine
    result = mac_SP_CVxCV((complex_float *)&test_input[0U], 
                 (complex_float *)&test_input2[0U], TEST_SIZE);

    test_output[0U] = result.dat[0];
    test_output[1U] = result.dat[1];

    out.f32    = test_output[0U];
    gold.f32   = test_golden[0U];
    err.f32    = fabsf(out.f32 - gold.f32);
//<<VC160916: cant check ulp error as this only applies to
// fixed point representation of the same set of numbers
//
//        if(out.ui32 >= gold.ui32)
//        {
//            errulp.ui32 = out.ui32 - gold.ui32;
//        }
//        else
//        {
//            errulp.ui32 = gold.ui32 - out.ui32;
//        }
//
//        if((err.f32 < tolerance) &&
//           (errulp.ui32 < toleranceLSBMantissa))
//
// VC160916>>

    if(err.f32 < tolerance)
    {
        pass++;
    }
    else
    {
        fail++;
    }
    test_error[0U] = err.f32;

    out.f32    = test_output[1U];
    gold.f32   = test_golden[1U];
    err.f32    = fabsf(out.f32 - gold.f32);
//<<VC160916: cant check ulp error as this only applies to
// fixed point representation of the same set of numbers
//
//        if(out.ui32 >= gold.ui32)
//        {
//            errulp.ui32 = out.ui32 - gold.ui32;
//        }
//        else
//        {
//            errulp.ui32 = gold.ui32 - out.ui32;
//        }
//
//        if((err.f32 < tolerance) &&
//           (errulp.ui32 < toleranceLSBMantissa))
//
// VC160916>>

    if(err.f32 < tolerance)
    {
        pass++;
    }
    else
    {
        fail++;
    }
    test_error[1U] = err.f32;
}

// End of File
