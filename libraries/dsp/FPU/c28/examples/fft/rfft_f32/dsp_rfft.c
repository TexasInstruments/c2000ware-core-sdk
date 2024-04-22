
//#############################################################################
//
//! \file   dsp_rfft.c
//!
//! \brief  Runs the single precision Real FFT routine
//! \author Vishal Coelho
//! \date   Aug 08, 2016
//
//  Group:          C2000
//  Target Device:  TMS320f28002x
//
// The input and golden files were obtained by running the MATLAB script, 
// FPU_DSP_runFFT.m (under reference/MATLAB), at the MATLAB command 
// line as follows
// "
//   OUT = FPU_DSP_runFFT('real', 2, 1024, 'TYPE_FLOAT', 'FTYPE_C');
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
// - Define FFT_ALIGN=2N (replace 2N with the actual number) in the linker
// settings, C2000 Linker -> Advanced Options -> Command File Preprocessing
// -> --define. For example, for a 128 point real FFT, set FFT_ALIGN=256
// - This version of the real FFT requires the use of CFFT_f32t variant 
// - This project has a build configuration "RAM_ROMTABLES" where the FFT 
//   tables are already in the ROM of the device. For this configuration the
//   user must define USE_TABLES to 1 as described in the foregoing bullet 
//   point
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




// CFFT_F32_STRUCT object
CFFT_F32_STRUCT cfft;
// Handle to the CFFT_F32_STRUCT object
CFFT_F32_STRUCT_Handle hnd_cfft = &cfft;
#ifdef __cplusplus
#pragma DATA_SECTION("FFT_buffer_2")
#else
#pragma DATA_SECTION(test_output, "FFT_buffer_2")
#endif
float test_output[TEST_SIZE + 2U];

float test_error[TEST_SIZE  + 2U];
float test_phase[TEST_SIZE];

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
    CFFT_f32_setInputPtr(hnd_cfft, test_input);
    CFFT_f32_setOutputPtr(hnd_cfft, test_output);
    CFFT_f32_setTwiddlesPtr(hnd_cfft, CFFT_f32_twiddleFactors);
    CFFT_f32_setStages(hnd_cfft, (FFT_STAGES - 1U));
    CFFT_f32_setFFTSize(hnd_cfft, (FFT_SIZE >> 1));

    // Run the N/2 point complex FFT
    // NOTE: Can only use the 't' version of the CFFT with the
    // pack and unpack functions
    CFFT_f32t(hnd_cfft);                   // Calculate FFT



    // Run the unpack function on the N/2 point complex spectrum
    // to get the N/2+1 point complex spectrum of the N point real
    // data. The unpack function will generate the complex
    // spectrum from F(0) to F(N/2).
    // The pointer, p_currOutput points to the complex spectrum
    // of the real N-point input data.
    CFFT_f32_unpack(hnd_cfft);

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
    // test_golden[2*N] to test_golden[3*N-1] contain the magnitude
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
    // NOTE: Final output of the unpack is stored in the buffer
    // pointed to by obj.p_currOutput
    p_temp      = CFFT_f32_getCurrOutputPtr(hnd_cfft);
    for(i = 0U; i < TEST_SIZE + 2U; i++)
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
    memset(test_error, 0U, sizeof(float)*(TEST_SIZE  + 2U));

    //
    // switch the CurrentInPtr and CurrentOutPtr pointers
    //
    p_temp = CFFT_f32_getCurrInputPtr(hnd_cfft);
    CFFT_f32_setCurrInputPtr(hnd_cfft, CFFT_f32_getCurrOutputPtr(hnd_cfft));
    CFFT_f32_setCurrOutputPtr(hnd_cfft, p_temp);

    // Run the magnitude function
#ifdef __TMS320C28XX_TMU__ //defined when --tmu_support=tmu0 in the project 
                           // properties
    // Calculate magnitude, result stored in CurrentOutPtr
    CFFT_f32_mag_TMU0(hnd_cfft);     
#else
    // Calculate magnitude, result stored in CurrentOutPtr    
    CFFT_f32_mag(hnd_cfft);          
#endif
    //
    // NOTE: the N/2 point is not calculated by the mag functions;
    // we dont need to calculate |F(N/2)| as its real, so we just copy
    // it over
    //
    test_input[TEST_SIZE/2] = test_output[TEST_SIZE];

    // NOTE: Final output of the FFT magnitude is stored in the
    // buffer pointed to by obj.p_currOutput
    p_temp      = CFFT_f32_getCurrOutputPtr(hnd_cfft);
    // Check the output
    for(i = (TEST_SIZE << 1), j=0U; i < (2U*TEST_SIZE+(TEST_SIZE >> 1)+1U);
    		i++, j++)
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
    
    // Zero out the error array
    memset(test_error, 0U, sizeof(float)*(TEST_SIZE + 2U));
    
    //
    // To avoid overwriting the magnitude, change the output buffer for
    // the phase()
    //
    CFFT_f32_setCurrOutputPtr(hnd_cfft, test_phase);
#ifdef __TMS320C28XX_TMU__ //defined when --tmu_support=tmu0 in the project 
                           //properties
    // Calculate phase, result stored in CurrentOutPtr
    CFFT_f32_phase_TMU0(hnd_cfft);        
#else
    // Calculate phase, result stored in CurrentOutPtr    
    CFFT_f32_phase(hnd_cfft);              
#endif
    // NOTE: Final output of the FFT magnitude is stored in the
    // buffer pointed to by obj.p_currOutput
    p_temp      = CFFT_f32_getCurrOutputPtr(hnd_cfft);
    // Check the output
    for(i = 3U*TEST_SIZE, j=0U; i < (3U*TEST_SIZE + (TEST_SIZE >> 1)); 
        i++, j++)
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
}



// End of File
