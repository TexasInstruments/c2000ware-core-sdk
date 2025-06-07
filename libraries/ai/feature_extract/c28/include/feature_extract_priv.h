/*
 *  Created on: July 16, 2024
 */

//#############################################################################
//
// FILE:   feature_extract_priv.h
//
//!
//! This contains prototyping of core API functions required to feature
//! extraction operations
//
//#############################################################################
//
//
// 
// C2000Ware v5.05.00.00
//
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//#############################################################################

#ifndef FEATURE_EXTRACT_IMPLEMENT_H_
#define FEATURE_EXTRACT_IMPLEMENT_H_

//*****************************************************************************
// Includes
//*****************************************************************************
#include <string.h>
#include "dsp.h"
#include "fpu32/fpu_cfft.h"
#include "fpu32/fpu_rfft.h"
#include "driverlib.h"
#include "fpu32/C28x_FPU_FastRTS.h"
#include "fpu32/fpu_fft_hann.h"
#include "math.h"
#include "feature_extract.h"
#include "nn_utils.h"

#include "user_input_config.h"


//! \brief Pre_processing structure
//!
typedef struct {
    Feature_Extract_Init_Params init_params;
    float *prerecorded_dataPtr;         //!< Pointer to the prerecorded_data buffer
    float *Window_outputPtr;                //!< Pointer to the Windowing output result buffer
    float *FFT_inputPtr;                   //!< Pointer to the FFT_input buffer
    float *FFT_outputPtr;                  //!< Pointer to the FFT_output buffer
    float *MagbuffPtr;                     //!< Pointer to the magnitude buffer
    float *data_reframe_inputPtr;          //!< Pointer to the data_reframe input buffer
    int8_t *data_reframe_outputPtr;          //!< Pointer to the data_reframe input buffer
    float *binInPtr;                       //!< Pointer to the bin_input buffer
    float *binOutPtr;                      //!< Pointer to the bin_output buffer
    float32_t *batchnormInPtr;             //!< Pointer to the batchnorm_input buffer
    int8_t *batchnormOutPtr;               //!< Pointer to the batchnorm_output buffer
    float *rearrangedataPtr;               //!< Pointer to the rearrangedata buffer
    int8_t *concatframeInPtr;              //!< Pointer to the concatframe_input buffer
    int8_t *concatframeOutPtr;             //!< Pointer to the concatframe_output buffer
    int8_t *softmaxcalinPtr;               //!< Pointer to the input buffer of softmax_cal
    float  *softmaxcaloutPtr;              //!< Pointer to the output buffer of softmax_cal
    // CFFT_F32_STRUCT object
    CFFT_F32_STRUCT cfft;

    // Handle to the CFFT_F32_STRUCT object
    CFFT_F32_STRUCT_Handle hnd_cfft;

    // RFFT_F32_STRUCT object
    RFFT_F32_STRUCT rfft;

    // Handle to the RFFT_F32_STRUCT object
    RFFT_F32_STRUCT_Handle hnd_rfft;
} Feature_Extract_State_Params;


/*****************************************************************************/
/* External variables                                                        */
/*****************************************************************************/
extern struct tvmgen_default_outputs outputs;

extern const int32_t tvmgen_default_bias_data[] __attribute__((weak));
extern const int32_t tvmgen_default_scale_data[] __attribute__((weak));
extern const int32_t tvmgen_default_shift_data[] __attribute__((weak));


//*****************************************************************************
// Leaf level function APIs
//*****************************************************************************
static inline void feature_extract_setrecorded_dataPtr(Feature_Extract_State_Params *fh,
        const float *pi)
{
    fh->prerecorded_dataPtr = (float *)pi;
}

static inline float * feature_extract_getrecorded_dataPtr(Feature_Extract_State_Params *fh)
{
    return(fh->prerecorded_dataPtr);
}

static inline void feature_extract_setWindow_outputPtr(Feature_Extract_State_Params *fh,
        const float *pi)
{
    fh->Window_outputPtr = (float *)pi;
}

static inline float * feature_extract_getWindow_outputPtr(Feature_Extract_State_Params *fh)
{
    return(fh->Window_outputPtr);
}

static inline void feature_extract_setFFT_inputPtr(Feature_Extract_State_Params *fh,
        const float *pi)
{
    fh->FFT_inputPtr = (float *)pi;
}

static inline float * feature_extract_getFFT_inputPtr(Feature_Extract_State_Params *fh)
{
    return(fh->FFT_inputPtr);
}

static inline void feature_extract_setFFT_outputPtr(Feature_Extract_State_Params *fh,
        const float *pi)
{
    fh->FFT_outputPtr = (float *)pi;
}

static inline float * feature_extract_getFFT_outputPtr(Feature_Extract_State_Params *fh)
{
    return(fh->FFT_outputPtr);
}

static inline void feature_extract_setMagbuffPtr(Feature_Extract_State_Params *fh,
        const float *pi)
{
    fh->MagbuffPtr = (float *)pi;
}

static inline float * feature_extract_getMagbuffPtr(Feature_Extract_State_Params *fh)
{
    return(fh->MagbuffPtr);
}

static inline void feature_extract_setdatareframeinputPtr(Feature_Extract_State_Params *fh,
        const float *pi)
{
    fh->data_reframe_inputPtr = (float *)pi;
}

static inline float * feature_extract_getdatareframeinputPtr(Feature_Extract_State_Params *fh)
{
    return(fh->data_reframe_inputPtr);
}

static inline void feature_extract_setdatareframeoutputPtr(Feature_Extract_State_Params *fh,
        int8_t *pi)
{
    fh->data_reframe_outputPtr = (int8_t *)pi;
}

static inline int8_t * feature_extract_getv(Feature_Extract_State_Params *fh)
{
    return(fh->data_reframe_outputPtr);
}

static inline void feature_extract_setbinInPtr(Feature_Extract_State_Params *fh,
        const float *pi)
{
    fh->binInPtr = (float *)pi;
}

static inline float * feature_extract_getbinInPtr(Feature_Extract_State_Params *fh)
{
    return(fh->binInPtr);
}

static inline void feature_extract_setbinOutPtr(Feature_Extract_State_Params *fh,
        const float *pi)
{
    fh->binOutPtr = (float *)pi;
}

static inline float * feature_extract_getbinOutPtr(Feature_Extract_State_Params *fh)
{
    return(fh->binOutPtr);
}

static inline void feature_extract_setminfftbinsize(Feature_Extract_State_Params *fh,
                      const uint16_t st)
{
    fh->init_params.min_fft_bin_size= st;
}

static inline uint16_t feature_extract_getminfftbinsize(Feature_Extract_State_Params *fh)
{
    return(fh->init_params.min_fft_bin_size);
}


static inline void feature_extract_setchannellength(Feature_Extract_State_Params *fh,
                      const uint16_t st)
{
    fh->init_params.num_input_channels= st;
}

static inline uint16_t feature_extract_getchannellength(Feature_Extract_State_Params *fh)
{
    return(fh->init_params.num_input_channels);
}

static inline void feature_extract_setchannelwidth(Feature_Extract_State_Params *fh,
                      const uint16_t st)
{
    fh->init_params.output_feature_width= st;
}

static inline uint16_t feature_extract_getchannelwidth(Feature_Extract_State_Params *fh)
{
    return(fh->init_params.output_feature_width);
}

static inline void feature_extract_setchannelheight(Feature_Extract_State_Params *fh,
                      const uint16_t st)
{
    fh->init_params.output_feature_height= st;
}

static inline uint16_t feature_extract_getchannelheight(Feature_Extract_State_Params *fh)
{
    return(fh->init_params.output_feature_height);
}

static inline void feature_extract_setfftstagessize(Feature_Extract_State_Params *fh,
                      const uint16_t st)
{
    fh->init_params.fft_stage_num= st;
}

static inline uint16_t feature_extract_getfftstagessize(Feature_Extract_State_Params *fh)
{
    return(fh->init_params.fft_stage_num);
}

static inline void feature_extract_setfftsize(Feature_Extract_State_Params *fh,
                      const uint16_t st)
{
    fh->init_params.fft_size= st;
}

static inline uint16_t feature_extract_getfftsize(Feature_Extract_State_Params *fh)
{
    return(fh->init_params.fft_size);
}

static inline void feature_extract_setfftbinsize(Feature_Extract_State_Params *fh,
                      const uint16_t st)
{
    fh->init_params.fft_bin_size= st;
}

static inline uint16_t feature_extract_getfftbinsize(Feature_Extract_State_Params *fh)
{
    return(fh->init_params.fft_bin_size);
}

static inline void feature_extract_setperframefeaturesize(Feature_Extract_State_Params *fh,
                      const uint16_t st)
{
    fh->init_params.feature_size_per_frame= st;
}

static inline uint16_t feature_extract_getperframefeaturesize(Feature_Extract_State_Params *fh)
{
    return(fh->init_params.feature_size_per_frame);
}

static inline void feature_extract_settotalframesize(Feature_Extract_State_Params *fh,
                      const uint16_t st)
{
    fh->init_params.total_feature_size_per_frame= st;
}

static inline uint16_t feature_extract_gettotalframesize(Feature_Extract_State_Params *fh)
{
    return(fh->init_params.total_feature_size_per_frame);
}

static inline void feature_extract_setframesize(Feature_Extract_State_Params *fh,
                      const uint16_t st)
{
    fh->init_params.size_of_frame= st;
}

static inline uint16_t feature_extract_getframesize(Feature_Extract_State_Params *fh)
{
    return(fh->init_params.size_of_frame);
}

static inline void feature_extract_setnumframeconcat(Feature_Extract_State_Params *fh,
                      const uint16_t st)
{
    fh->init_params.num_frame_concat= st;
}

static inline uint16_t feature_extract_getnumframeconcat(Feature_Extract_State_Params *fh)
{
    return(fh->init_params.num_frame_concat);
}

static inline void feature_extract_setlogmul(Feature_Extract_State_Params *fh,
                      const uint16_t st)
{
    fh->init_params.log_multiply= st;
}

static inline uint16_t feature_extract_getlogmul(Feature_Extract_State_Params *fh)
{
    return(fh->init_params.log_multiply);
}

static inline void feature_extract_setlogbase(Feature_Extract_State_Params *fh,
                      const float st)
{
    fh->init_params.log_base= st;
}

static inline float feature_extract_getlogbase(Feature_Extract_State_Params *fh)
{
    return(fh->init_params.log_base);
}

static inline void feature_extract_setconcatframe_inPtr(Feature_Extract_State_Params *fh,
        int8_t *pi)
{
    fh->concatframeInPtr = (int8_t *)pi;
}

static inline int8_t * feature_extract_getconcatframe_inPtr(Feature_Extract_State_Params *fh)
{
    return(fh->concatframeInPtr);
}

static inline void feature_extract_setconcatframe_outPtr(Feature_Extract_State_Params *fh,
        int8_t *pi)
{
    fh->concatframeOutPtr = (int8_t *)pi;
}

static inline int8_t * feature_extract_getconcatframe_outPtr(Feature_Extract_State_Params *fh)
{
    return(fh->concatframeOutPtr);
}

//*****************************************************************************
// Function Prototyping
//*****************************************************************************


static inline void feature_extract_setbatchnorm_inPtr(Feature_Extract_State_Params *fh,
        float32_t *pi)
{
    fh->batchnormInPtr = (float32_t *)pi;
}

static inline float32_t * feature_extract_getbatchnorm_inPtr(Feature_Extract_State_Params *fh)
{
    return(fh->batchnormInPtr);
}

static inline void feature_extract_setbatchnorm_outPtr(Feature_Extract_State_Params *fh,
        int8_t *pi)
{
    fh->batchnormOutPtr = (int8_t *)pi;
}

static inline int8_t * feature_extract_getbatchnorm_outPtr(Feature_Extract_State_Params *fh)
{
    return(fh->batchnormOutPtr);
}

static inline void feature_extract_setrearrangedataPtr(Feature_Extract_State_Params *fh,
        const float *pi)
{
    fh->rearrangedataPtr = (float *)pi;
}

static inline float * feature_extract_getrearrangedataPtr(Feature_Extract_State_Params *fh)
{
    return(fh->rearrangedataPtr);
}

void run_frame_rearrange(Feature_Extract_State_Params *hnd_feature_extract);
void batch_normalization(Feature_Extract_State_Params *hnd_feature_extract);

#endif   /* FEATURE_EXTRACT_IMPLEMENT_H_ */
