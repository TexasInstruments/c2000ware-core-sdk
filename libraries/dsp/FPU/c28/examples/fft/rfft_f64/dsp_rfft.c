//#############################################################################
//
//! \file   dsp_rfft.c
//!
//! \brief  Runs the double precision Real FFT routine
//! \author Vishal Coelho
//! \date   Feb 03, 2016
//
//  Group:          C2000
//  Target Device:  TMS320F2828x
//
// The input and golden files were obtained by running the MATLAB script, 
// FPU_DSP_runFFT.m (under reference/MATLAB), at the MATLAB command 
// line as follows
// "
//   OUT = FPU_DSP_runFFT('real', 2, 512, 'TYPE_DOUBLE', 'FTYPE_C');
//   Sampling Rate (Hz) : 100e3
//   Number of Sines : 2
// "
// - Please note that this script generates the input wave using random values
// for the frequency, amplitude and phase so it may not be possible to 
// generate the exact same set of inputs and outputs given in 
// this example.
// - Also note the script will generate the magnitude and phase which it then
// tacks on to the end of the golden CFFT outputs
// - The input must be assigned to the section "FFT_buffer_1".
// Modify the input file genereated by MATLAB by adding the following
// line above the array declaration
//   #pragma DATA_SECTION(test_input, "FFT_buffer_1")
// - Define FFT_ALIGN=4N (replace 4N with the actual number) in the linker
// settings, C2000 Linker -> Advanced Options -> Command File Preprocessing
// -> --define. For example, for a 128 point real FFT, set FFT_ALIGN=512
//
//#############################################################################
//
//
// $Copyright: Copyright (C) 2025 Texas Instruments Incorporated -
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
float64_t test_output[TEST_SIZE + 2U];

float64_t test_error[TEST_SIZE  + 2U];
//*****************************************************************************
// the function definitions
//*****************************************************************************
void DSP_runTest(void)
{
    // Locals
    int16_t i, j;
    float64u_t out, gold, errld;
    float64_t *p_temp;

    // Configure the object
    CFFT_f64_setInputPtr(hnd_cfft, test_input);
    CFFT_f64_setOutputPtr(hnd_cfft, test_output);
    CFFT_f64_setTwiddlesPtr(hnd_cfft, FPU64CFFTtwiddleFactors);
    CFFT_f64_setStages(hnd_cfft, (FFT_STAGES - 1U));
    CFFT_f64_setFFTSize(hnd_cfft, (FFT_SIZE >> 1));
    CFFT_f64_setInitFunction(hnd_cfft, NULL);
    CFFT_f64_setCalcFunction(hnd_cfft, (v_pfn_v)CFFT_f64);
    CFFT_f64_setMagFunction(hnd_cfft, (v_pfn_v)CFFT_f64_mag);

    // Run the N/2 point complex FFT
    hnd_cfft->calc(hnd_cfft);

    // Run the unpack function on the N/2 point complex spectrum
    // to get the N/2+1 point complex spectrum of the N point real
    // data. The unpack function will generate the complex
    // spectrum from F(0) to F(N/2).
    // The pointer, p_currOutput points to the complex spectrum
    // of the real N-point input data.
    CFFT_f64_unpack(hnd_cfft);

    //
    // NOTE: Error Checking
    //
    // The golden vector has the full spectrum of the real data, i.e. F(0)
    // to F(N-1) but the unpack routine however only calculates the
    // spectrum from F(0) to F(N/2)
    //
    // The real spectrum is conjugate symmetric about the nyquist point i.e.
    // F(k) = F(N-k)*, k = 1 to N/2 - 1
    // F(0) and F(N/2) are real only
    // So test_golden[0] to test_golden[2*(N/2)] contain the points F(0),
    // F(k) for k = 1 to N/2-1 and F(N/2)
    // test_golden[2*(N/2+1)] to test_golden[2*(N-1)] contain the points
    // F(N-k)* for k = 1 to N/2-1
    // test_golden[2*N] to test_golden[3*(N-1)] contain the magnitude
    // corresponding to points F(0) to F(N-1). Since we only calculate half
    // the spectrum we are only concerned about points test_golden[2*N] to
    // test_golden[2*N + N/2]
    //
    // The same can be said about the phase, we are only concered with points
    // test_golden[3*N] to test_golden[3*N + N/2]. The user may use the
    // conjugate symmetry property of the real spectrum to calculate the
    // points F(N/2+1) to F(N-1) and then compare those with the golden
    // values left out of the error checks
    //
    for(i = 0U; i < TEST_SIZE + 2U; i++)
    {
        // NOTE: Final output of the unpack is stored in the buffer
        // pointed to by obj.p_currOutput
        out.f64 = hnd_cfft->p_currOutput[i];
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

    // Zero out the error array
    memset(test_error, 0U, sizeof(float64_t)*(TEST_SIZE + 2U));

    // Switch the p_currInput and p_currOutput pointers prior to
    // running the magnitude function
    p_temp = CFFT_f64_getCurrInputPtr(hnd_cfft);
    CFFT_f64_setCurrInputPtr(hnd_cfft, CFFT_f64_getCurrOutputPtr(hnd_cfft));
    CFFT_f64_setCurrOutputPtr(hnd_cfft, p_temp);

    // Run the magnitude function
    hnd_cfft->mag(hnd_cfft);


    for(i = (TEST_SIZE << 1), j=0U; i < (2U*TEST_SIZE+(TEST_SIZE >> 1)+1U);
    		i++, j++)
    {
        // NOTE: Final output of the FFT magnitude is stored in the
        // buffer pointed to by obj.p_currOutput
        out.f64 = hnd_cfft->p_currOutput[j];
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
                test_error[j] = errld.f64;
     }

}

// End of File
