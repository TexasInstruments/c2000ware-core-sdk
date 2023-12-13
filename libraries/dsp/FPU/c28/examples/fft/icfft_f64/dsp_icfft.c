//#############################################################################
//
//! \file   dsp_icfft.c
//!
//! \brief  Runs the double precision Inverse Complex FFT routine
//! \author Vishal Coelho
//! \date   Feb 09, 2016
//
//  Group:          C2000
//  Target Device:  TMS320f2838x
//
// The input and golden files were obtained by running the MATLAB script, 
// FPU_DSP_runIFFT.m (under reference/MATLAB), at the MATLAB command 
// line as follows
// "
//   OUT = FPU_DSP_runIFFT('complex', 2, 512, 'TYPE_DOUBLE', 'FTYPE_C');
//   Sampling Rate (Hz) : 100e3
//   Number of Sines : 10
// "
// - Please note that this script generates the input wave using random values
// for the frequency, amplitude and phase so it may not be possible to 
// generate the exact same set of inputs and outputs given in 
// this example.
// - The input must be assigned to the section "FFT_buffer_1".
// Modify the input file genereated by MATLAB by adding the following
// line above the array declaration
//   #pragma DATA_SECTION(test_input, "FFT_buffer_1")
// - Define FFT_ALIGN=8N (replace 8N with the actual number) in the linker
// settings, C2000 Linker -> Advanced Options -> Command File Preprocessing
// -> --define. For example, for a 128 point FFT, set FFT_ALIGN=1024
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
#include <string.h>

#include "fpu.h"
#include "dsp.h"
#include "dsp_examples_setup.h"
#include "fpu64/fpu64_fft.h"

//*****************************************************************************
// the defines
//*****************************************************************************
#define TEST_SIZE       (512U)
#define FFT_STAGES      (9U)
#define FFT_SIZE        (1 << FFT_STAGES)

//*****************************************************************************
// the globals
//*****************************************************************************
// The global pass, fail values
uint16_t pass = 0U, fail = 0U;
// The absolute error between the result and expected values
float64_t tolerance = 1.2e-5;
// CFFT_f64_Struct object
CFFT_f64_Struct icfft;
// Handle to the CFFT_f64_Struct object
CFFT_f64_Handle hnd_icfft = &icfft;

#ifdef __cplusplus
#pragma DATA_SECTION("FFT_buffer_2")
#else
#pragma DATA_SECTION(test_output, "FFT_buffer_2")
#endif
float64_t test_output[TEST_SIZE << 1];

float64_t test_error[TEST_SIZE << 1];
//*****************************************************************************
// the function definitions
//*****************************************************************************
void DSP_runTest(void)
{
    // Locals
    int16_t i;
    float64u_t out, gold, errld;

    // Configure the object
    CFFT_f64_setInputPtr(hnd_icfft, test_input);
    CFFT_f64_setOutputPtr(hnd_icfft, test_output);
    CFFT_f64_setTwiddlesPtr(hnd_icfft, FPU64CFFTtwiddleFactors);
    CFFT_f64_setStages(hnd_icfft, FFT_STAGES);
    CFFT_f64_setFFTSize(hnd_icfft, FFT_SIZE);
    CFFT_f64_setInitFunction(hnd_icfft, NULL);
    CFFT_f64_setCalcFunction(hnd_icfft, (v_pfn_v)ICFFT_f64);
    CFFT_f64_setMagFunction(hnd_icfft, NULL);
    CFFT_f64_setPhaseFunction(hnd_icfft, NULL);

    // Run the calculation function
    hnd_icfft->calc(hnd_icfft);


    for(i = 0U; i < (TEST_SIZE << 1); i++)
    {
        // NOTE: Final output of the FFT is stored in the buffer
        // pointed to by obj.p_currInput
        out.f64 = hnd_icfft->p_currInput[i];
        gold.f64 = test_golden[i];

        // Calculation of error and comparison with tolerance
                errld.f64 = fabsf(out.f64 - gold.f64);
                       if(errld.f64 < tolerance)
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
