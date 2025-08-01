/*
 *  Created on: July 16, 2024
 */

//#############################################################################
//
// FILE:   feature_extract.h
//
//!
//! This contains prototyping of user interactive API functions
//!
//
//#############################################################################
//
//
// 
// C2000Ware v6.00.00.00
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

#ifndef FEATURE_EXTRACT_INTERFACE_H_
#define FEATURE_EXTRACT_INTERFACE_H_


#include "driverlib.h"


/*****************************************************************************/
/* Data Structures                                                           */
/*****************************************************************************/

typedef enum {
    FEATURE_EXTRACT_NONE,
    FEATURE_EXTRACT_RAW,
    FEATURE_EXTRACT_FFT,
    FEATURE_EXTRACT_FFT_BIN,
    FEATURE_EXTRACT_WIN_FFT_BIN,
    FEATURE_EXTRACT_CUSTOM
} Feature_Extract_Type;


//! \brief Pre_processing structure
//!
typedef struct {
    int32_t version;
    uint16_t type;     //!< Feature Extraction Type
    uint16_t min_fft_bin_size;                  //!< Minimum size of FFT BIN  --> FE_MIN_FFT_BIN
    uint16_t num_input_channels;                //!< Number of input channels --> FE_
    uint16_t fft_stage_num;                     //!< Number of FFT stages --> FE_FFT_STAGES
    uint16_t fft_size;                          //!< Size of FFT
    uint16_t fft_bin_size;                      //!< FFT bin size
    uint16_t feature_size_per_frame;            //!< Size of Feature per frame
    uint16_t total_feature_size_per_frame;      //!< Size of Total frame
    uint16_t size_of_frame;                     //!< Size of frame
    uint16_t output_feature_width;              //!< Width of feature extract output data
    uint16_t output_feature_height;             //!< Height of feature extract output data
    uint16_t output_feature_size_per_channel;   //!< Size of feature output per channel
    uint16_t output_feature_size;               //!< Size of total feature
    uint16_t num_frame_concat;                  //!< Number of frames to be concatenated
    uint16_t nn_output_size;                    //!< Size of neural_network output buffer
    uint16_t log_multiply;                      //!< Multiplication factor of log operation --> FE_LOG_MUL
    float log_base;                             //!< Base of log operation --> FE_LOG_BASE

    const float *output_convert_bias;
    const int32_t *output_convert_scale;
    const int32_t *output_convert_shift;
    int32_t output_convert_shift_len;
} Feature_Extract_Init_Params;


//! \brief Pre_processing structure
//!
typedef struct {
  uint32_t handle_size;
  uint32_t scratch_size;
} Feature_Extract_Alloc_Params;


//! \brief Pre_processing structure
//!
typedef struct {
  uint8_t context[96];
} Feature_Extract_Handle_Params;

int alloc_feature_extract(Feature_Extract_Init_Params* init_params, Feature_Extract_Alloc_Params* alloc_params);

int init_feature_extract(Feature_Extract_Init_Params* init_params, Feature_Extract_Handle_Params* handle_params);

int run_feature_extract(Feature_Extract_Handle_Params *handle_params, void* input_buffer, void* output_buffer, void* scratch_buffer);

int init_nn_input_with_test_data(Feature_Extract_Handle_Params *handle_params, float *model_test_input, float32_t* nn_input_test_data_flatten, int8_t *nnData_flatten);

#endif   /* FEATURE_EXTRACT_INTERFACE_H_ */
