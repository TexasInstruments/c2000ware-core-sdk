//#############################################################################
//
//! \file   dsp_irfft.c
//!
//! \brief  Compute the double precision Inverse Real FFT
//! \author Vishal Coelho
//! \date   Feb 16, 2016
//
//  Group:          C2000
//  Target Device:  TMS320f2838x
//
// The input and golden files were obtained by running the MATLAB script, 
// FPU_DSP_runIFFT.m (under reference/MATLAB), at the MATLAB command
// line as follows
// "
//   OUT = FPU_DSP_runIFFT('real', 2, 512, 'TYPE_DOUBLE', 'FTYPE_C');
//   Sampling Rate (Hz) : 100e3
//   Number of Sines : 4
// "
// - Please note that this script generates the input wave using random values
// for the frequency, amplitude and phase so it may not be possible to 
// generate the exact same set of inputs and outputs given in 
// this example.
// - The input must be assigned to the section "FFT_buffer_1".
// Modify the input file genereated by MATLAB by adding the following
// line above the array declaration
//   #pragma DATA_SECTION(test_input, "FFT_buffer_1")
// - Define FFT_ALIGN=4N (replace 4N with the actual number) in the linker
// settings, C2000 Linker -> Advanced Options -> Command File Preprocessing
// -> --define. For example, for a 128 point real IFFT, set FFT_ALIGN=512
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
#include "fpu64/fpu64_fft.h"

//*****************************************************************************
// the defines
//*****************************************************************************
#define TEST_SIZE       (512U)  //512 is the size of the real data, but the
                                //size of the IFFT is 256 complex
#define FFT_STAGES      (8U)	// #stages and size of the ICFFT (N/2)
#define FFT_SIZE        (1 << FFT_STAGES)

//*****************************************************************************
// the globals
//*****************************************************************************
// The global pass, fail values
uint16_t pass = 0U, fail = 0U;
// The absolute error between the result and expected values
float64_t tolerance = 1.0e-9;
// CFFT_f64_Struct object
CFFT_f64_Struct cfft;
// Handle to the CFFT_f64_Struct object
CFFT_f64_Handle hnd_cfft = &cfft;

#ifdef __cplusplus
#pragma DATA_SECTION("FFT_buffer_2")
#else
#pragma DATA_SECTION(test_output, "FFT_buffer_2")
#endif
float64_t test_output[TEST_SIZE];

float64_t test_error[TEST_SIZE];
//*****************************************************************************
// the function definitions
//*****************************************************************************
void DSP_runTest(void)
{
    // Locals
    int16_t i;
    float64u_t out, gold, errld;
    float64_t *p_temp;

    // Configure the object
    CFFT_f64_setInputPtr(hnd_cfft, test_input);
    CFFT_f64_setOutputPtr(hnd_cfft, test_output);
    CFFT_f64_setTwiddlesPtr(hnd_cfft, FPU64CFFTtwiddleFactors);
    CFFT_f64_setStages(hnd_cfft, (FFT_STAGES));
    CFFT_f64_setFFTSize(hnd_cfft, (FFT_SIZE));
    CFFT_f64_setInitFunction(hnd_cfft, NULL);
    CFFT_f64_setCalcFunction(hnd_cfft, (v_pfn_v)ICFFT_f64);
    CFFT_f64_setMagFunction(hnd_cfft, NULL);

    // Run the pack function on the N/2 point complex spectrum
    // to get the N/2 packed spectrum of the N point real
    // data. The pack function will generate the complex
    // spectrum from Z(0) to Z(N/2).
    // The pointer, p_currOutput points to the complex spectrum
    // of the real N-point input data. The pointers must be exchanged
    // prior to calling the inverse FFT
    // The currOutput and currInput pointer must be assigned before
    // calling the pack function
    CFFT_f64_setCurrInputPtr(hnd_cfft, &test_input[0]);
    CFFT_f64_setCurrOutputPtr(hnd_cfft, &test_output[0]);
    CFFT_f64_pack(hnd_cfft);

    // After the pack operation the output is in the buffer pointed
    // to by currOutput; this should be set as the object input pointer.
    // The object output pointer should be set to the buffer pointer to
    // by currInput
    // The inverse FFT function will overwrite the currInput and currOutput
    // pointers.
    p_temp = CFFT_f64_getCurrOutputPtr(hnd_cfft);
    CFFT_f64_setInputPtr(hnd_cfft, p_temp);
    p_temp = CFFT_f64_getCurrInputPtr(hnd_cfft);
    CFFT_f64_setOutputPtr(hnd_cfft, p_temp);

    // Run the N/2 point inverse complex FFT
    hnd_cfft->calc(hnd_cfft);


    // Error check
    for(i = 0U; i < TEST_SIZE; i++)
    {
        // NOTE: Final output of the IFFT is stored in the buffer
        // pointed to by obj.p_currInput
        out.f64 = hnd_cfft->p_currInput[i];
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
