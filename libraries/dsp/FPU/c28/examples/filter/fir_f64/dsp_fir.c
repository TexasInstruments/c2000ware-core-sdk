//#############################################################################
//
//! \file   dsp_fir.c
//!
//! \brief  Runs the double precision FIR routine
//! \author Vishal Coelho
//! \date   Jan 11, 2016
//
//  Group:          C2000
//  Target Device:  TMS320f2838x
//
// The input and golden files were obtained by running the MATLAB script, 
// FPU_DSP_runFIRFilter.m (under reference/MATLAB), at the MATLAB command 
// line as follows
// "
//   R = FPU_DSP_runFIRFilter('lowpass', 512, 'TYPE_DOUBLE', 'FTYPE_C');
//   Sampling Rate (Hz) : 100e3
//   Lowpass Filter Design
//   Fp(Hz) Fst(Hz) Ap(dB) Ast(dB):5e3 10e3 0.1 60
//   
//   ans =
//   
//   Sample Rate      : N/A (normalized frequency)
//   Passband Edge    : 0.1
//   3-dB Point       : 0.13185
//   6-dB Point       : 0.14438
//   Stopband Edge    : 0.2
//   Passband Ripple  : 0.097242 dB
//   Stopband Atten.  : 60.0806 dB
//   Transition Width : 0.1
//   
//   Filter Order = 58
// "
// Please note that this script generates the input wave using random values 
// for the frequency, amplitude and phase so it may not be possible to 
// generate the exact same set of inputs, outputs and coefficients given in 
// this example.
// Also note the filter coefficients are tacked on to the end of the test 
// input in the input file
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
#include "fpu.h"
#include "dsp.h"
#include "dsp_examples_setup.h"
#include "fpu64/filter.h"

//*****************************************************************************
// the defines
//*****************************************************************************
#define TEST_SIZE       (512U)
#define FILTER_ORDER    (58U)
//*****************************************************************************
// the globals
//*****************************************************************************
// The global pass, fail values
uint16_t pass = 0U, fail = 0U;
// The absolute error between the result and expected values
float64_t tolerance = 1.0e-6;
// FIR_f64 object
FIR_f64 fir;
// Handle to the FIR_f64 object
FIR_f64_Handle hnd_fir = &fir;

// The filter coefficients are tacked on to the end of the MATLAB generated
// input
const float64_t *coefficients = &test_input[TEST_SIZE];

// The delay line buffer
float64_t delayLine[FILTER_ORDER + 1U];

float64_t test_output[TEST_SIZE];
float64_t test_error[TEST_SIZE];
//*****************************************************************************
// the function definitions
//*****************************************************************************
void DSP_runTest(void)
{
    // Locals
    uint16_t i;
    float64u_t in, out, gold, errld;

    // Configure the object
    FIR_f64_setCoefficientsPtr(hnd_fir, coefficients);
    FIR_f64_setDelayLinePtr(hnd_fir, delayLine);
    FIR_f64_setInputPtr(hnd_fir, (float64_t *)&in);
    FIR_f64_setOutputPtr(hnd_fir, (float64_t *)&out);
    FIR_f64_setOrder(hnd_fir, FILTER_ORDER);
    FIR_f64_setInitFunction(hnd_fir, (v_pfn_v)FIR_f64_init);
    FIR_f64_setCalcFunction(hnd_fir, (v_pfn_v)FIR_f64_calc);
    
    // Run the initialization function
    hnd_fir->init(hnd_fir);

    for(i = 0U; i < TEST_SIZE; i++)
    {
        out.f64  = DBL_MAX;
        in.f64   = test_input[i];

        // Call the calculation routine
        hnd_fir->calc(hnd_fir);

        test_output[i] = out.f64;
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
