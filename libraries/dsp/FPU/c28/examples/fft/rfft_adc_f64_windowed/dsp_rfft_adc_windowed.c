//#############################################################################
//
//! \file   dsp_rfft_adc_windowed.c
//!
//! \brief  Runs the double precision Real FFT (ADC input) with windowing
//! \author Vishal Coelho
//! \date   Apr 21, 2017
//
//  Group:          C2000
//  Target Device:  TMS320f2838x
//
// This example can be configured to use and check against the pre-computed 
// signal, or sample an EPWM signal over an ADC channel and run the RFFT.
//
// REAL ADC INPUT:
// - set USE_REAL_ADC_INPUT to 1U in dsp_examples_setup.h and build
// - External Connections (for Real EPWM sampling):
// Connect A0 to EPWM2A on the target board. Refer to the board schematic
// for pin positioning.
// - The ADC will sample a 50% duty cycle 1KHz wave (EPWM2A) at 10KHz
// and run the FFT on it. Since the input is a square wave, you will
// see the fundamental frequency, 1KHz, at the 51st bin
// (51*fs/N = 51*10K/512 = 996.09375) and all its odd harmonics. Since the
// sampled waveform is not an integer multiple of the FFT_SIZE, you will see
// some spectral leakage, a portion of the fundamental will leak into the 52nd
// bin. One way to overcome this is to window the input before running the FFT
// on it.
// - exclude input.c from the build
// If the maximum component (max_idx) after RFFT magnitude computation
// (other than DC component) is found at index 51 for i.e. around 1Khz the pass is
// set to 1 else fail is set to 1. So observe watch variables : "pass", "fail"
// and "max_idx". Also you can experiment by changing EPWM2 frequency and observing
// variation of max_idx correspondingly
//
// SIMULATED ADC INPUT:
// - set USE_REAL_ADC_INPUT to 0U in dsp_examples_setup.h and build
// - include input.c from the build
// - The input and golden files were obtained by running the MATLAB script,
// FPU_DSP_runFFT.m (under reference/MATLAB), at the MATLAB command 
// line as follows
// "
//   OUT = FPU_DSP_runWindowedFFT('real_adc', 2,  'hann', 512, 'TYPE_DOUBLE', 
//                                'FTYPE_C');
//   Sampling Rate (Hz) : 100e3
//   Number of Sines : 3
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
//
// GENERAL NOTES:
// - the window needs to be in Q16 format
// - define ADC_INPUT in the project properties (predefined symbols)
// - TEST_SIZE in this file and dsp_examples_setup.c must be the same
// - Define FFT_ALIGN=N (replace N with the actual number) in the linker
// settings, C2000 Linker -> Advanced Options -> Command File Preprocessing
// -> --define. For example, for a 128 point real FFT, set FFT_ALIGN=128
// - This project has a build configuration "RAM_ROMTABLES" where the FFT 
//   tables are already in the ROM of the device. For this configuration the
//   user must define USE_TABLES to 1 as described in the foregoing bullet 
//   point
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
#define TEST_SIZE       (512U) //must be same as dsp_examples_setup.c
#define FFT_STAGES      (9U)
#define FFT_SIZE        (1 << FFT_STAGES)

//*****************************************************************************
// the globals
//*****************************************************************************
// The global pass, fail values
uint16_t pass = 0U, fail = 0U;
// The absolute error between the result and expected values
float64_t tolerance = 6.8e-6;
// CFFT_f64_Struct object
CFFT_f64_Struct cfft;
// Handle to the CFFT_f64_Struct object
CFFT_f64_Handle hnd_cfft = &cfft;

// Object of the structure CFFT_ADC_f64_Struct
CFFT_ADC_f64_Struct cfft_adc;
// Handle to the CFFT_ADC_f64_Struct object
CFFT_ADC_f64_Handle hnd_cfft_adc = &cfft_adc;


#if defined(ADC_INPUT)
// Flag to signal the ADC has finished sampling, and storing, 
// N points in the FFT input buffer
volatile uint16_t flagInputReady = 0;

// Index into the FFT input buffer
volatile uint16_t sampleIndex = 0;

// Maximum Frequency component index
uint32_t max_idx = 1;

#endif // ADC_INPUT


#if USE_REAL_ADC_INPUT == 1U
#ifdef __cplusplus
#pragma DATA_SECTION("FFT_buffer_1")
#else
#pragma DATA_SECTION(test_input, "FFT_buffer_1")
#endif
// Matrix is four times its required size as it will be used to store
// TEST_SIZE float64_ts at a later point
uint16_t test_input[4U*TEST_SIZE];
#endif //USE_REAL_ADC_INPUT == 1U

#ifdef __cplusplus
#pragma DATA_SECTION("FFT_buffer_2")
#else
#pragma DATA_SECTION(test_output, "FFT_buffer_2")
#endif
float64_t test_output[TEST_SIZE];

float64_t test_error[TEST_SIZE];
float64_t test_magnitude_phase[(TEST_SIZE >> 1) + 1];
float64_t twiddleFactors[TEST_SIZE];

// You can get these values (Q16) by taking the original HANN512 in 
// fpu_fft_hann.h and running the following operations in MATLAB
// A = [..copy the floating point HANN512 matrix here..];
// B = reshape(A', ...size of the window..., 1)
// C = uint16(floor(B.*(2^16))); % convert to Q16
//S = sprintf('%7d, %7d, %7d, %7d, %7d, %7d, %7d, %7d,\n', C)
//
const uint16_t fftWindow[TEST_SIZE >> 1] = {
      0,       2,       9,      22,      39,      61,      89,     121,
    158,     200,     247,     299,     356,     417,     484,     555,
    632,     713,     799,     890,     985,    1086,    1191,    1301,
   1416,    1536,    1660,    1789,    1922,    2061,    2204,    2351,
   2503,    2660,    2822,    2987,    3158,    3333,    3512,    3695,
   3884,    4076,    4273,    4474,    4679,    4889,    5103,    5321,
   5543,    5769,    6000,    6234,    6472,    6715,    6961,    7211,
   7465,    7723,    7985,    8251,    8520,    8793,    9069,    9349,
   9633,    9920,   10210,   10504,   10802,   11102,   11406,   11713,
  12024,   12337,   12654,   12973,   13296,   13621,   13950,   14281,
  14615,   14952,   15291,   15633,   15978,   16325,   16675,   17027,
  17382,   17739,   18098,   18459,   18823,   19189,   19556,   19926,
  20298,   20671,   21046,   21424,   21802,   22183,   22565,   22949,
  23334,   23720,   24108,   24498,   24888,   25280,   25672,   26066,
  26461,   26857,   27254,   27651,   28050,   28449,   28849,   29249,
  29650,   30051,   30453,   30855,   31257,   31660,   32062,   32465,
  32868,   33271,   33674,   34077,   34479,   34881,   35283,   35685,
  36086,   36486,   36886,   37286,   37685,   38082,   38480,   38876,
  39271,   39666,   40059,   40451,   40842,   41232,   41621,   42008,
  42394,   42778,   43161,   43543,   43922,   44300,   44676,   45051,
  45424,   45794,   46163,   46530,   46894,   47257,   47617,   47975,
  48331,   48684,   49035,   49384,   49730,   50073,   50414,   50752,
  51087,   51420,   51750,   52077,   52401,   52722,   53040,   53355,
  53667,   53976,   54281,   54584,   54883,   55178,   55470,   55759,
  56045,   56326,   56605,   56879,   57150,   57418,   57681,   57941,
  58197,   58449,   58698,   58942,   59182,   59419,   59651,   59879,
  60104,   60324,   60540,   60751,   60959,   61162,   61361,   61556,
  61746,   61932,   62113,   62290,   62463,   62631,   62795,   62954,
  63108,   63258,   63403,   63544,   63680,   63811,   63938,   64060,
  64177,   64289,   64397,   64500,   64598,   64691,   64780,   64863,
  64942,   65016,   65085,   65149,   65208,   65263,   65312,   65357,
  65396,   65431,   65461,   65485,   65505,   65520,   65530,   65535,
};

//*****************************************************************************
// the function definitions
//*****************************************************************************
void DSP_runTest(void)
{
    // Locals
    int16_t i;
#if USE_REAL_ADC_INPUT == 0U
    int16_t j;
    float64u_t out, gold, errld;
#endif // USE_REAL_ADC_INPUT == 0U

#if USE_REAL_ADC_INPUT == 1U
        float64_t max;
#endif // USE_REAL_ADC_INPUT == 1U

    // Configure the object
    CFFT_f64_setInputPtr(hnd_cfft, (float64_t *)test_input);
    CFFT_f64_setCurrInputPtr(hnd_cfft, (float64_t *)test_input);
    CFFT_f64_setOutputPtr(hnd_cfft, test_output);
    CFFT_f64_setCurrOutputPtr(hnd_cfft, test_output);
    CFFT_f64_setTwiddlesPtr(hnd_cfft, FPU64RFFTtwiddleFactors);
    CFFT_f64_setStages(hnd_cfft, (FFT_STAGES));
    CFFT_f64_setFFTSize(hnd_cfft, (FFT_SIZE));
    CFFT_f64_setInitFunction(hnd_cfft, NULL);
    CFFT_f64_setCalcFunction(hnd_cfft, (v_pfn_v)RFFT_adc_f64);
    CFFT_f64_setMagFunction(hnd_cfft, (v_pfn_v)RFFT_f64_mag);

    //Link the CFFT_ADC_f64 object to the CFFT_f64 object. The tail pointer
    //of CFFT_ADC_f64 must point to the OutBuf pointer of
    //CFFT_f64
    CFFT_ADC_f64_setTailPtr(hnd_cfft_adc, &(hnd_cfft->p_output));
    CFFT_ADC_f64_setInBufPtr(hnd_cfft_adc, test_input);
    
#if USE_REAL_ADC_INPUT == 1U
    while(1){
        while(flagInputReady == 0){};  // Wait on ADC ISR to set the flag
                                       // before proceeding
        // Modifying the input and output pointers to the correct input
        // and output buffer before running FFT
        CFFT_f64_setCurrInputPtr(hnd_cfft, (float64_t *)test_input);
        CFFT_f64_setCurrOutputPtr(hnd_cfft, test_output);
#endif //USE_REAL_ADC_INPUT == 1U

        // Apply the window (float) to the input (uint16_t)
        RFFT_adc_f64_win(test_input, fftWindow, FFT_SIZE );
        // Run the N point real FFT
        hnd_cfft->calc(hnd_cfft_adc);

#if USE_REAL_ADC_INPUT == 0U
    //
    // NOTE: Error Checking
    //
    // The golden vector has the full spectrum of the real data, i.e. F(0)
    // to F(N-1) but the real FFT routine however only calculates the
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
    for(i = 0U; i < TEST_SIZE; i++)
    {
        // NOTE: Final output is stored in the buffer pointed to by 
        // obj.p_currOutput
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

#endif // USE_REAL_ADC_INPUT == 0U

    // Reset the flag
    flagInputReady = 0;
    // Zero out the error array
    memset(test_error, 0U, sizeof(float64_t)*TEST_SIZE);

    // Modifying the input and output pointer before running the
    // magnitude function
    CFFT_f64_setCurrInputPtr(hnd_cfft, CFFT_f64_getCurrOutputPtr(hnd_cfft));
    CFFT_f64_setCurrOutputPtr(hnd_cfft, test_magnitude_phase);

    // Run the magnitude function
    hnd_cfft->mag(hnd_cfft);

    // Checking whether the maximum component in frequency domain is at index 51 i.e around 1Khz
    // If yes then set pass = 1 else fail = 1
#if USE_REAL_ADC_INPUT == 1U
    max = 0.0;
    max_idx = 1;
    for(i = 1U; i < TEST_SIZE >> 1; i++)
    {
         if(hnd_cfft->p_currOutput[i] > max)
         {
              max = hnd_cfft->p_currOutput[i];
              max_idx = i;
         }
    }

    if (max_idx == 51)
    {
       pass = 1;
       fail = 0;
    }
    else
    {
       pass = 0;
       fail = 1;
    }
#endif // USE_REAL_ADC_INPUT == 1U

#if USE_REAL_ADC_INPUT == 0U
    for(i = (TEST_SIZE), j=0U; i <= (TEST_SIZE+(TEST_SIZE >> 1)); i++, j++)
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

#endif //USE_REAL_ADC_INPUT == 0U
#if USE_REAL_ADC_INPUT == 1U
    }
#endif //USE_REAL_ADC_INPUT == 1U
}

// End of File
