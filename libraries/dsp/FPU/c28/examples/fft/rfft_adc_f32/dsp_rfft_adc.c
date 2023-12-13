//#############################################################################
//
//! \file   dsp_rfft_adc.c
//!
//! \brief  Runs the single precision Real FFT (ADC input) routine
//! \author Vishal Coelho
//! \date   Apr 05, 2017
//
//  Group:          C2000
//  Target Device:  TMS320f28002x
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
// see the fundamental frequency (maximum magnitude), 1KHz, at the 51st bin
// (51*fs/N = 51*10K/512 = 996.09375Hz) and all its odd harmonics. Since the
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
//
// SIMULATED ADC INPUT:
// - set USE_REAL_ADC_INPUT to 0U in dsp_examples_setup.h and build
// - include input.c from the build
// - The input and golden files were obtained by running the MATLAB script,
// FPU_DSP_runFFT.m (under reference/MATLAB), at the MATLAB command 
// line as follows
// "
//   OUT = FPU_DSP_runFFT('real_adc', 2, 512, 'TYPE_FLOAT', 'FTYPE_C');
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
#include "fpu32/fpu_rfft.h"

//*****************************************************************************
// the defines
//*****************************************************************************
#define TEST_SIZE       (256U) //must be same as dsp_examples_setup.c
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

// Object of the structure RFFT_ADC_F32_STRUCT
RFFT_ADC_F32_STRUCT rfft_adc;
// Handle to the RFFT_ADC_F32_STRUCT object
RFFT_ADC_F32_STRUCT_Handle hnd_rfft_adc = &rfft_adc;

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
// Matrix is twice its required size as it will be used to store
// TEST_SIZE floats at a later point
uint16_t test_input[2U*TEST_SIZE];
#endif //USE_REAL_ADC_INPUT == 1U

#ifdef __cplusplus
#pragma DATA_SECTION("FFT_buffer_2")
#else
#pragma DATA_SECTION(test_output, "FFT_buffer_2")
#endif
float test_output[TEST_SIZE];

float test_error[TEST_SIZE];
float test_magnitude_phase[(TEST_SIZE >> 1) + 1];
float twiddleFactors[TEST_SIZE];

//*****************************************************************************
// the function definitions
//*****************************************************************************
void DSP_runTest(void)
{
    // Locals
    int16_t i;
#if USE_REAL_ADC_INPUT == 0U
    int16_t j;
    float32u_t out, gold, err;
#endif // USE_REAL_ADC_INPUT == 0U

#if USE_REAL_ADC_INPUT == 1U
     float max;
#endif // USE_REAL_ADC_INPUT == 1U

    float *p_temp;

    // Configure the object
    RFFT_f32_setInputPtr(hnd_rfft, (float *)test_input);
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

    //Link the RFFT_ADC_F32_STRUCT to RFFT_F32_STRUCT. Tail pointer
    //of RFFT_ADC_F32_STRUCT must point to the OutBuf pointer of
    //RFFT_F32_STRUCT
    RFFT_ADC_f32_setTailPtr(hnd_rfft_adc, &(hnd_rfft->OutBuf));
    RFFT_ADC_f32_setInBufPtr(hnd_rfft_adc, test_input);

#if USE_REAL_ADC_INPUT == 1U
    while(1){
        while(flagInputReady == 0){};  // Wait on ADC ISR to set the flag
                                       // before proceeding
#endif //USE_REAL_ADC_INPUT == 1U
        RFFT_adc_f32(hnd_rfft_adc);    // Calculate real FFT with 12-bit

#if USE_REAL_ADC_INPUT == 0U
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
        // So test_golden[0] to test_golden[N-1] contain the points Re(0), Re(1),
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
#endif // USE_REAL_ADC_INPUT == 0U

        // Reset the flag
        flagInputReady = 0;
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

// Checking whether the maximum component in frequency domain is at index 51 i.e around 1Khz
// If yes then set pass = 1 else fail = 1
#if USE_REAL_ADC_INPUT == 1U
        max = 0.0f;
        max_idx = 1;
        for(i = 1U; i < TEST_SIZE / 2; i++)
        {
            if(p_temp[i] > max)
            {
                max = p_temp[i];
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
#endif // USE_REAL_ADC_INPUT == 0U

        // Zero out the error array and magnitude array
        memset(test_error, 0U, sizeof(float)*(TEST_SIZE));
        memset(test_magnitude_phase, 0U, sizeof(float)*((TEST_SIZE >> 1) + 1U));
#ifdef __TMS320C28XX_TMU__ //defined when --tmu_support=tmu0 in the project 
        // properties
        RFFT_f32_phase_TMU0(hnd_rfft);           //Calculate phase
#else
        RFFT_f32_phase(hnd_rfft);                //Calculate phase
#endif

        p_temp      = test_magnitude_phase;
#if USE_REAL_ADC_INPUT == 0U
        // Check the output
        // For a N-pt real FFT, the index values for the mag and phase are 0, 1,
        // 2, ....N/2-1, N/2, N/2+1, ....,N-1. Because the FFT is real, there is
        // a conjugate symmetry around the N/2 values i.e. index value 0 is
        // conjugate symmetric to N-1, index 1 to N-2, etc. The middle value N/2
        // doesn't have a corresponding counterpart. Hence, you need N/2+1 values
        // for Mag and Phase. Phase index 0 is 0 because the signal is real, so
        // you need one less value for Phase.
        for(i  = (TEST_SIZE+(TEST_SIZE >> 1)+1U), j=0U;
                i <= ((TEST_SIZE << 1)); i++, j++)
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
#endif //USE_REAL_ADC_INPUT == 0U
#if USE_REAL_ADC_INPUT == 1U
    }
#endif //USE_REAL_ADC_INPUT == 1U
}

// End of File
