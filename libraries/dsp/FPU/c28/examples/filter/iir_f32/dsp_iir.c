//#############################################################################
//
//! \file   dsp_iir.c
//!
//! \brief  Runs the single precision IIR routine
//! \author Vishal Coelho
//! \date   Aug 02, 2016
//
//  Group:          C2000
//  Target Device:  TMS320f28002x
//
// The input and golden files were obtained by running the MATLAB script, 
// FPU_DSP_runIIRFilter.m (under reference/MATLAB), at the MATLAB command 
// line as follows
// "
//  R = FPU_DSP_runIIRFilter('lowpass', 1024, 'TYPE_FLOAT', 'FTYPE_C')
//  Sampling Rate (Hz) : 100e3
//  Lowpass Filter Design
//  Fp(Hz) Fst(Hz) Ap(dB) Ast(dB):5e3 10e3 0.1 60
//   
//  ans =
//   
//  Sample Rate      : N/A (normalized frequency)
//  Passband Edge    : 0.1                       
//  3-dB Point       : 0.11117                   
//  6-dB Point       : 0.11641                   
//  Stopband Edge    : 0.2                       
//  Passband Ripple  : 0.1 dB                    
//  Stopband Atten.  : 60 dB                     
//  Transition Width : 0.1                       
//   
//  Num of SOS = 3
// "
// Please note that this script generates the input wave using random values 
// for the frequency, amplitude and phase so it may not be possible to 
// generate the exact same set of inputs, outputs and coefficients given in 
// this example.
// Also note the filter coefficients are tacked on to the end of the test 
// input, and the scale factors after that, in the input file.
//
// The difference equation for the IIR is given as
//
// a y(n) = b x(n) + b x(n-1) + b x(n-2) - a y(n-1) - a y(n-2)
//  0        0        1          2          1          2
//        ^        ^          ^          ^          ^
// y(n) = b x(n) + b x(n-1) + b x(n-2) - a y(n-1) - a y(n-2)
//         0        1          2          1          2
//           ^  ^
// where the a, b coefficients are normalized to a
//                                                0
// MATLAB will generate the coefficients as per the above equation (a  = 1)
//                                                                   0
// and store it to the formatted file. The assembly routine, however,
// implements the following difference equation
//        ^        ^          ^           `          `
// y(n) = b x(n) + b x(n-1) + b x(n-2) + a y(n-1) + a y(n-2)
//         0        1          2          1          2
//            `     ^
// where the a  = -a .
// THE USER MUST MANUALLY NEGATE THE COEFFICIENTS A[1], A[2] OF EACH BIQAUD
// IN TEST_INPUT (OR WHATEVER ARRAY THEY USE). THE MATLAB SCRIPT WILL NOT
// DO THIS
// For this example MATLAB generates the following B's and A's
//   Biquad 1, B = 1.00000000000F, -1.58911634842F,  1.00000000000F,
//             A = 1.00000000000F, -1.80768968822F,  0.91729359227F,
//   Biquad 2, B = 1.00000000000F, -1.12938486120F,  1.00000000000F,
//             A = 1.00000000000F, -1.70313897897F,  0.76411432132F,
//   Biquad 3, B = 1.00000000000F,  1.00000000000F,  0.00000000000F,
//             A = 1.00000000000F, -0.82953774579F,  0.00000000000F
// The A's must be stored as follows,
//   Biquad 1, B = 1.00000000000F, -1.58911634842F,  1.00000000000F,
//             A = 1.00000000000F,  1.80768968822F, -0.91729359227F,
//   Biquad 2, B = 1.00000000000F, -1.12938486120F,  1.00000000000F,
//             A = 1.00000000000F,  1.70313897897F, -0.76411432132F,
//   Biquad 3, B = 1.00000000000F,  1.00000000000F,  0.00000000000F,
//             A = 1.00000000000F,  0.82953774579F,  0.00000000000F
//
//#############################################################################
//
//
// $Copyright: Copyright (C) 2020 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################


//*****************************************************************************
// the includes
//*****************************************************************************
#include "fpu.h"
#include "dsp.h"
#include "dsp_examples_setup.h"
#include "fpu32/fpu_filter.h"

//*****************************************************************************
// the defines
//*****************************************************************************
#define TEST_SIZE       (512U)
#define NUM_SOS			(3U)	// Number of Second Order Stages (biquad)
#define FILTER_ORDER    (NUM_SOS<<1)

//*****************************************************************************
// the globals
//*****************************************************************************
// The global pass, fail values
uint16_t pass = 0U, fail = 0U;
// The absolute error between the result and expected values
float tolerance = 2.0e-5;


// IIR_f32 object
IIR_f32 iir;
// Handle to the IIR_f32 object
IIR_f32_Handle hnd_iir = &iir;

// The filter coefficients and scale factors are tacked on to the end of the 
// MATLAB generated input
float coeffs_B[NUM_SOS*3U];
float coeffs_A[NUM_SOS*3U];
float scaleFactors[NUM_SOS];

// The delay line buffer
float delayLine[NUM_SOS*4U];

float test_output[TEST_SIZE];
float test_error[TEST_SIZE];
//*****************************************************************************
// the function definitions
//*****************************************************************************
void DSP_runTest(void)
{
    // Locals
    uint16_t i;
    float32u_t in, out, gold, err;
    float *p_cb, *p_ca;

    // Copy the A and B coefficients from test input into their respective 
    // arrays. The coefficients start at test_input[TEST_SIZE] first with the
    // Bs of the first biquad then the As alternating in that fashion for each
    // biquad
    p_cb = &test_input[TEST_SIZE];
    p_ca = p_cb + 3UL;
    
    for(i = 0U; i < NUM_SOS; i++)
    {
        memcpy(&coeffs_B[3U*i], p_cb, 3U*sizeof(float));
        memcpy(&coeffs_A[3U*i], p_ca, 3U*sizeof(float));
        p_cb += 6UL;
        p_ca += 6UL;
    }
    memcpy(scaleFactors, &test_input[TEST_SIZE+(6U*NUM_SOS)],
    		NUM_SOS*sizeof(float));
    
    // Configure the object
    IIR_f32_setCoefficientsBPtr(hnd_iir, coeffs_B);
    IIR_f32_setCoefficientsAPtr(hnd_iir, coeffs_A);
    IIR_f32_setDelayLinePtr(hnd_iir, delayLine);
    IIR_f32_setInputPtr(hnd_iir, (float *)&in);
    IIR_f32_setOutputPtr(hnd_iir, (float *)&out);
    IIR_f32_setScalePtr(hnd_iir, scaleFactors);
    IIR_f32_setOrder(hnd_iir, FILTER_ORDER);
    IIR_f32_setInitFunction(hnd_iir, (v_pfn_v)IIR_f32_init);
    IIR_f32_setCalcFunction(hnd_iir, (v_pfn_v)IIR_f32_calc);
    
    // Run the initialization function
    hnd_iir->init(hnd_iir);

    for(i = 0U; i < TEST_SIZE; i++)
    {
        out.f32  = FLT_MAX;
        in.f32   = test_input[i];

        // Call the calculation routine
        hnd_iir->calc(hnd_iir);

        test_output[i] = out.f32;
        gold.f32 = test_golden[i];
        err.f32 = fabsf(out.f32 - gold.f32);

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
