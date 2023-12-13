//#############################################################################
//
//! \file   dsp_fir.c
//!
//! \brief  Runs the single precision FIR routine
//! \author Vishal Coelho
//! \date   Sep 16, 2016
//
//  Group:          C2000
//  Target Device:  TMS320f28002x
//
// The input and golden files were obtained by running the MATLAB script, 
// FPU_DSP_runFIRFilter.m (under reference/MATLAB), at the MATLAB command 
// line as follows
// "
//  R = FPU_DSP_runFIRFilter('lowpass', 1024, 'TYPE_FLOAT', 'FTYPE_C')
//  Sampling Rate (Hz) : 100e3
//  Lowpass Filter Design
//  Fp(Hz) Fst(Hz) Ap(dB) Ast(dB):5e3 10e3 0.1 60
//   
//  ans =
//   
// Sample Rate      : N/A (normalized frequency)
// Passband Edge    : 0.1                       
// 3-dB Point       : 0.13185                   
// 6-dB Point       : 0.14438                   
// Stopband Edge    : 0.2                       
// Passband Ripple  : 0.097242 dB               
// Stopband Atten.  : 60.0806 dB                
// Transition Width : 0.1                       
//  
// Filter Order = 58
// "
// Please note that this script generates the input wave using random values 
// for the frequency, amplitude and phase so it may not be possible to 
// generate the exact same set of inputs, outputs and coefficients given in 
// this example.
// Also note the filter coefficients are tacked on to the end of the test 
// input, and the scale factors after that, in the input file.
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
#include "fpu.h"
#include "dsp.h"
#include "dsp_examples_setup.h"
#include "fpu32/fpu_filter.h"

//*****************************************************************************
// the defines
//*****************************************************************************

#define TEST_SIZE       (512U)

#define FIR_ORDER       (58U)             // ORDER = NUM_TAPS - 1    

//*****************************************************************************
// the globals
//*****************************************************************************
// The global pass, fail values
uint16_t pass = 0U, fail = 0U;
// The absolute error between the result and expected values
float tolerance = 1.0e-6;


// FIR_f32 object
FIR_f32 fir;
// Handle to the FIR_f32 object
FIR_f32_Handle hnd_fir = &fir;

// The filter coefficients are tacked on to the end of the 
// MATLAB generated input
float coeffs[FIR_ORDER+1];

// The delay line buffer
float delayLine[FIR_ORDER+1];

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
        
    // Configure the object
    FIR_f32_setCoefficientsPtr(hnd_fir, coeffs);
    FIR_f32_setDelayLinePtr(hnd_fir, delayLine);
    FIR_f32_setOrder(hnd_fir, FIR_ORDER);
    FIR_f32_setInitFunction(hnd_fir, (v_pfn_v)FIR_f32_init);
    FIR_f32_setCalcFunction(hnd_fir, (v_pfn_v)FIR_f32_calc);
    
    // Copy the coefficients from test input into the "coeffs" array
    memcpy(&coeffs, &test_input[TEST_SIZE], (FIR_ORDER + 1U)*sizeof(float));
    // Run the initialization function
    hnd_fir->init(hnd_fir);

    for(i = 0U; i < TEST_SIZE; i++)
    {
    	in.f32   = test_input[i];
    	out.f32  = FLT_MAX;
        FIR_f32_setInput(hnd_fir, in.f32);
        FIR_f32_setOutput(hnd_fir, out.f32);

        // Call the calculation routine
        hnd_fir->calc(hnd_fir);

        out.f32 = FIR_f32_getOutput(hnd_fir);
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
