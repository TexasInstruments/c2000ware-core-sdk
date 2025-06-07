//#############################################################################
//
//! \file   dsp_rfft_windowed.c
//!
//! \brief  Runs the single precision Real FFT routine by first windowing
//!         the input
//! \author Vishal Coelho
//! \date   Sep 16, 2016
//
//  Group:          C2000
//  Target Device:  TMS320f28002x
//
// The input and golden files were obtained by running the MATLAB script, 
// FPU_DSP_runWindowedFFT.m (under reference/MATLAB), at the MATLAB command 
// line as follows
// "
//   OUT = FPU_DSP_runWindowedFFT('real_alt', 2, 'hann', 512, ...
//             'TYPE_FLOAT','FTYPE_C');
//   Sampling Rate (Hz) : 100e3
//   Number of Sines : 3
// "
// - For this example we use a 512 point Hann window. While MATLAB does 
//   generate the window in a .c file, we will not include it; we will, 
//   instead include the header file "fpu_fft_hann.h"
// - Please note that this script generates the input wave using random values
//   for the frequency, amplitude and phase so it may not be possible to 
//   generate the exact same set of inputs and outputs given in 
//   this example.
// - Also note the script will generate the magnitude and phase which it then
//   tacks on to the end of the golden CFFT outputs
// - The input must be assigned to the section "FFT_buffer_1".
// Modify the input file genereated by MATLAB by adding the following
// line above the array declaration
//   #pragma DATA_SECTION(test_input, "FFT_buffer_1")
// - Define FFT_ALIGN=2N (replace 2N with the actual number) in the linker
// settings, C2000 Linker -> Advanced Options -> Command File Preprocessing
// -> --define. For example, for a 128 point real FFT, set FFT_ALIGN=256
// - This project has a build configuration "RAM_ROMTABLES" where the FFT 
//   tables are already in the ROM of the device. For this configuration the
//   user must define USE_TABLES to 1 as described in the foregoing bullet 
//   point
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
#include "fpu32/fpu_rfft.h"
#include "fpu32/fpu_fft_hann.h"

//*****************************************************************************
// the defines
//*****************************************************************************
#define TEST_SIZE       (256U)
#define FFT_STAGES      (8U)
#define FFT_SIZE        (1 << FFT_STAGES)

//*****************************************************************************
// the globals
//*****************************************************************************
// The global pass, fail values
uint16_t pass = 0U, fail = 0U;
// The absolute error between the result and expected values
float tolerance = 1.0e-3;


// Object of the structure RFFT_F32_STRUCT
RFFT_F32_STRUCT rfft;
// Handle to the RFFT_F32_STRUCT object
RFFT_F32_STRUCT_Handle hnd_rfft = &rfft;

#ifdef __cplusplus
#pragma DATA_SECTION("FFT_buffer_2")
#else
#pragma DATA_SECTION(test_output, "FFT_buffer_2")
#endif
float test_output[TEST_SIZE];

float test_error[TEST_SIZE];
float test_magnitude_phase[(TEST_SIZE >> 1) + 1];
float twiddleFactors[TEST_SIZE];

const float fftWindow[TEST_SIZE >> 1] = HANN256;
//*****************************************************************************
// the function definitions
//*****************************************************************************
void DSP_runTest(void)
{
    // Locals
    int16_t i, j;
    float32u_t out, gold, err;
    float *p_temp;

    // Configure the object
    RFFT_f32_setInputPtr(hnd_rfft, test_input);
    RFFT_f32_setOutputPtr(hnd_rfft, test_output);
    RFFT_f32_setMagnitudePtr(hnd_rfft, test_magnitude_phase);
    RFFT_f32_setPhasePtr(hnd_rfft, test_magnitude_phase);
    RFFT_f32_setStages(hnd_rfft,  FFT_STAGES);
    RFFT_f32_setFFTSize(hnd_rfft, FFT_SIZE);

    // Twiddle factor pointer
#ifdef USE_TABLES
    RFFT_f32_setTwiddlesPtr(hnd_rfft, RFFT_f32_twiddleFactors);
#else
    //Calculate twiddle factor
    RFFT_f32_setTwiddlesPtr(hnd_rfft, twiddleFactors);
    RFFT_f32_sincostable(hnd_rfft);         
#endif //USE_TABLES

    // Apply the window
    RFFT_f32_win(&test_input[0], (float *)&fftWindow, FFT_SIZE);

    // Run the real FFT (alternate version)
    RFFT_f32(hnd_rfft);

    //
    // NOTE: Error Checking
    //
    // The golden vector has the full spectrum of the real data, i.e. F(0)
    // to F(N-1) but the rfft routine however only calculates the
    // spectrum from F(0) to F(N/2) arranged in the following manner
    // re[0], re[1]....re[N/2-1], re[N/2], im[N/2-1], im[N/2-2].....im[1]
    // The bins 0 and N/2 are real only 
    // 
    // The real spectrum is conjugate symmetric about the nyquist point i.e.
    // F(k) = F(N-k)*, k = 1 to N/2 - 1
    // F(0) and F(N/2) are real only
    // So test_golden[0] to test_golden[N/2-1] contain the points Re(0), Re(1),
    // ...Re(N/2-1), Re(N/2), Im(N/2-1)...Im(1)
    //
    // test_golden[N] to test_golden[3*N/2] contain the magnitude 
    // corresponding to points F(0) to F(N/2).
    //
    // test_golden[3*N/2+1] to test_golden[2*N+1] contain the phase
    // corresponding to points F(0) to F(N/2).
    //
    p_temp      = test_output;
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

    // Zero out the error array
    memset(test_error, 0U, sizeof(float)*(TEST_SIZE));

    // Run the magnitude function
#ifdef __TMS320C28XX_TMU__ //defined when --tmu_support=tmu0 in the project 
                           // properties
    RFFT_f32_mag_TMU0(hnd_rfft);            //Calculate magnitude
#else
    RFFT_f32_mag(hnd_rfft);                 //Calculate magnitude
#endif

    p_temp      = test_magnitude_phase;
    // Check the output
    for(i = (TEST_SIZE), j=0U; i <= (TEST_SIZE+(TEST_SIZE >> 1)); i++, j++)
    {
    	out.f32     = p_temp[j];
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
        test_error[j] = err.f32;
    }
    
    // Zero out the error array and magnitude array
    memset(test_error, 0U, sizeof(float)*(TEST_SIZE));
    memset(test_magnitude_phase, 0U, sizeof(float)*((TEST_SIZE >> 1) + 1U));
#ifdef __TMS320C28XX_TMU__ //defined when --tmu_support=tmu0 in the project 
                           // properties
    RFFT_f32_phase_TMU0(hnd_rfft);           //Calculate phase
#else
    RFFT_f32_phase(hnd_rfft);                //Calculate phase
#endif
//
//        if(err.f32 < tolerance)
//        {
//            pass++;
//        }
//        else
//        {
//            fail++;
//        }
//        test_error[j] = err.f32;
//    }
// VC160920>>
}

// End of File
