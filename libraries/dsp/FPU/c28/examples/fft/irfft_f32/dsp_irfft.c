//#############################################################################
//
//! \file   dsp_irfft.c
//!
//! \brief  Compute the single precision Inverse Real FFT
//! \author Vishal Coelho
//! \date   Aug 09, 2016
//
//  Group:          C2000
//  Target Device:  TMS320f28002x
//
// The input and golden files were obtained by running the MATLAB script, 
// FPU_DSP_runFFT.m (under reference/MATLAB), at the MATLAB command 
// line as follows
// "
//   OUT = FPU_DSP_runIFFT('real', 2, 1024, 'TYPE_DOUBLE', 'FTYPE_C');
//   Sampling Rate (Hz) : 100e3
//   Number of Sines : 2
// "
// - Please note that this script generates the input wave using random values
// for the frequency, amplitude and phase so it may not be possible to 
// generate the exact same set of inputs and outputs given in 
// this example.
// - The input must be assigned to the section "FFT_buffer_1".
// Modify the input file genereated by MATLAB by adding the following
// line above the array declaration
//   #pragma DATA_SECTION(test_input, "FFT_buffer_1")
// - Define FFT_ALIGN=2N (replace 2N with the actual number) in the linker
// settings, C2000 Linker -> Advanced Options -> Command File Preprocessing
// -> --define. For example, for a 128 point real IFFT, set FFT_ALIGN=256
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
#include <string.h>

#include "fpu.h"
#include "dsp.h"
#include "dsp_examples_setup.h"
#include "fpu32/fpu_cfft.h"

//*****************************************************************************
// the defines
//*****************************************************************************
#define TEST_SIZE       (256U) //1024 is the size of the real data, but the
                                //size of the IFFT is 512 complex
#define FFT_STAGES      (7U)	// #stages and size of the ICFFT (N/2)
#define FFT_SIZE        (1 << FFT_STAGES)

//*****************************************************************************
// the globals
//*****************************************************************************
// The global pass, fail values
uint16_t pass = 0U, fail = 0U;
// The absolute error between the result and expected values
float tolerance = 1.0e-6;

// CFFT_F32_STRUCT object
CFFT_F32_STRUCT cfft;
// Handle to the CFFT_F32_STRUCT object
CFFT_F32_STRUCT_Handle hnd_cfft = &cfft;

#ifdef __cplusplus
#pragma DATA_SECTION("FFT_buffer_2")
#else
#pragma DATA_SECTION(test_output, "FFT_buffer_2")
#endif
float test_output[TEST_SIZE];

float test_error[TEST_SIZE];
//*****************************************************************************
// the function definitions
//*****************************************************************************
void DSP_runTest(void)
{
    // Locals
    int16_t i;
    float32u_t out, gold, err;
    float *p_temp;

    // Configure the object
    CFFT_f32_setInputPtr(hnd_cfft, test_input);
    CFFT_f32_setOutputPtr(hnd_cfft, test_output);
    CFFT_f32_setTwiddlesPtr(hnd_cfft, CFFT_f32_twiddleFactors);
    CFFT_f32_setStages(hnd_cfft, (FFT_STAGES));
    CFFT_f32_setFFTSize(hnd_cfft, (FFT_SIZE));

    // Run the pack function on the N/2 point complex spectrum
    // to get the N/2 packed spectrum of the N point real
    // data. The pack function will generate the complex
    // spectrum from Z(0) to Z(N/2).
    // The pointer, p_currOutput points to the complex spectrum
    // of the real N-point input data. The pointers must be exchanged
    // prior to calling the inverse FFT
    // The currOutput and currInput pointer must be assigned before
    // calling the pack function
    CFFT_f32_setCurrInputPtr(hnd_cfft, &test_input[0]);
    CFFT_f32_setCurrOutputPtr(hnd_cfft, &test_output[0]);
    CFFT_f32_pack(hnd_cfft);

    // After the pack operation the output is in the buffer pointed
    // to by currOutput; this should be set as the object input pointer.
    // The object output pointer should be set to the buffer pointer to
    // by currInput
    // The inverse FFT function will overwrite the currInput and currOutput
    // pointers.
    p_temp = CFFT_f32_getCurrOutputPtr(hnd_cfft);
    CFFT_f32_setInputPtr(hnd_cfft, p_temp);
    p_temp = CFFT_f32_getCurrInputPtr(hnd_cfft);
    CFFT_f32_setOutputPtr(hnd_cfft, p_temp);

    // Run the N/2 point inverse complex FFT
    // NOTE: Can only use the 't' version of the ICFFT with the
    // pack and unpack functions
    ICFFT_f32t(hnd_cfft);


    // Error check
    p_temp      = CFFT_f32_getCurrInputPtr(hnd_cfft);
    for(i = 0U; i < TEST_SIZE; i++)
    {
    	out.f32     = p_temp[i];
        gold.f32    = test_golden[i];
        err.f32     = fabsf(out.f32 - gold.f32);
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
