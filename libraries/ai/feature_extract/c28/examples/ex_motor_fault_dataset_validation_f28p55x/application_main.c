//#############################################################################
//
// FILE:   application_main.c
//
//!
//! This example shows the use of feature_extract library files in to process
//! motor_fault_classification data set. The example is developed on f28p55
//! launchpad. Please set the "TMS320F28P550SJ9_LaunchPad.ccxml" in
//! "targetConfigs" as the active configuration.
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

//
// Included Files
//
#include <stdio.h>

#include "driverlib.h"
#include "device.h"
#include "board.h"
#include "c2000ware_libraries.h"
//#include "user_input_config.h"
#include "application.h"
#include "tvmgen_default.h"
//#include "math.h"
//#include <string.h>
//#include "feature_extract.h"


/*****************************************************************************/
/* Definitions                                                               */
/*****************************************************************************/
//


// #defines
//
#define PASS 1
#define FAIL 0

/*****************************************************************************/
/* External variables                                                        */
/*****************************************************************************/
#pragma DATA_SECTION(scratch_buffer, "FFT_buffer_1")
#define SCRATCH_BUFFER_LEN (FE_FFT_SIZE*8)
#define SCRATCH_BUFFER_SIZE (SCRATCH_BUFFER_LEN*sizeof(float))
float scratch_buffer[SCRATCH_BUFFER_LEN];

//
// Function prototyping
//

#ifdef TVMGEN_DEFAULT_TI_NPU
extern void TI_NPU_init();
extern volatile int32_t tvmgen_default_finished;
#endif

#pragma DATA_SECTION(nnData, "nnData_sec");
NN_data_t nnData;

NN_input_float_t nn_input_test;

int test_result;
int error = 0;

#define TEST_FEATURE_EXTRACT


//raw_data input
extern float raw_input_test[];

// NN model output
extern int8_t golden_output[FE_NN_OUT_SIZE];


// Main
void main(void)
{
    // Initialize device clock and peripherals
    Device_init();

    // Disable pin locks and enable internal pull-ups.
    Device_initGPIO();

    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    Interrupt_initModule();

    // Initialize the PIE vector table with pointers to the shell Interrupt Service Routines (ISR).
    Interrupt_initVectorTable();

    // PinMux and Peripheral Initialization
    Board_init();

    // C2000Ware Library initialization
    C2000Ware_libraries_init();

#ifdef TVMGEN_DEFAULT_TI_NPU
    TI_NPU_init();
#endif

    Interrupt_enableGlobal(); // Enable CPU interrupt

    // Enable Global Interrupt (INTM) and real time interrupt (DBGM)
    EINT;
    ERTM;

    // initialize feature extract
    Feature_Extract_Init_Params init_params;

    //Essential initial parameter declaration for the example code to run
    init_params.version = 1;
    #if defined(FE_RAW)
    init_params.type = FEATURE_EXTRACT_RAW;
    #elif defined(FE_FFT) && !defined(FE_BIN) && !defined(FE_WIN)
    init_params.type = FEATURE_EXTRACT_FFT;
    #elif defined(FE_FFT) && defined(FE_BIN) && !defined(FE_WIN)
    init_params.type = FEATURE_EXTRACT_FFT_BIN;
    #elif defined(FE_FFT) && defined(FE_BIN) && defined(FE_WIN)
    init_params.type = FEATURE_EXTRACT_WIN_FFT_BIN;
    #endif
    init_params.num_frame_concat = FE_NUM_FRAME_CONCAT;
    init_params.feature_size_per_frame = FE_FEATURE_SIZE_PER_FRAME;
    init_params.output_feature_width = NN_WL;
    init_params.output_feature_height = NN_HL;
    init_params.num_input_channels = FE_STACKING_CHANNELS;
    init_params.total_feature_size_per_frame = (init_params.feature_size_per_frame)*(init_params.num_input_channels);
    #if !defined(FE_RAW)
    {
        init_params.fft_stage_num = FE_FFT_STAGES;
        init_params.log_multiply = FE_LOG_MUL;
        init_params.log_base = FE_LOG_BASE;
    }
    #else
    {
        init_params.fft_stage_num = 0;
        init_params.log_multiply = 1;
        init_params.log_base = 1;
    }
    #endif
    init_params.fft_size = FE_FFT_SIZE;
    init_params.nn_output_size = FE_NN_OUT_SIZE;
    init_params.size_of_frame = FE_FRAME_SIZE;
    init_params.output_convert_bias = tvmgen_default_bias_data;
    init_params.output_convert_scale = tvmgen_default_scale_data;
    init_params.output_convert_shift = tvmgen_default_shift_data;
    init_params.output_convert_shift_len = sizeof(tvmgen_default_shift_data) / sizeof(tvmgen_default_shift_data[0]);
    init_params.output_feature_size_per_channel = (init_params.num_frame_concat)*(init_params.feature_size_per_frame);
    init_params.output_feature_size = init_params.output_feature_size_per_channel*init_params.num_input_channels;


    //Remaining initial parameter declaration initialized with meaningful value. These only for user's reference
    init_params.fft_bin_size = 0;
    init_params.min_fft_bin_size = 1;

    Feature_Extract_Alloc_Params alloc_params;
    alloc_feature_extract(&init_params, &alloc_params);
    ASSERT(SCRATCH_BUFFER_SIZE >= alloc_params.scratch_size);
    ASSERT(sizeof(Feature_Extract_Handle_Params) >= alloc_params.handle_size);

    Feature_Extract_Handle_Params handle_params;

    init_feature_extract(&init_params, &handle_params);

#ifdef TEST_FEATURE_EXTRACT

    init_nn_input_with_test_data(&handle_params, model_test_input, nn_input_test.data_flatten, nnData.nn_input_int.data_flatten);
#else //TEST_FEATURE_EXTRACT
    int feature_extract_size_in_bytes = sizeof(nnData.nn_input_int.data_flatten)*sizeof(int8_t);
    memset(&nnData.nn_input_int.data_flatten, 0, feature_extract_size_in_bytes);
#endif //TEST_FEATURE_EXTRACT


    void *input_buffer = raw_input_test;
    void *output_buffer = &nnData.nn_input_int.data[0][0][0];
    void *scratch_buffer1 = scratch_buffer;
    run_feature_extract(&handle_params, input_buffer, output_buffer, scratch_buffer1);

    // Run NN model
    struct tvmgen_default_inputs inputs = { (void*) &nnData.nn_input_int.data[0][0][0] };
    struct tvmgen_default_outputs outputs = { &nnData.nn_output_int.buf0[0] };
    tvmgen_default_run(&inputs, &outputs);

    #if defined(TVMGEN_DEFAULT_TI_NPU)
         while (!tvmgen_default_finished);
    #endif

#ifdef TEST_FEATURE_EXTRACT
    int n = 0;
    for(n=0;n<FE_NN_OUT_SIZE;n++)
    {
       if(abs(golden_output[n] - nnData.nn_output_int.buf0[n])>5)
       {
          error++;
       }
    }
    if(error==0)
    {
        test_result = PASS;
    }
    else
    {
        test_result = FAIL;
    }
#endif //TEST_FEATURE_EXTRACT

    softmax_cal(nnData.nn_output_int.buf0, FE_NN_OUT_SIZE, nnData.softmax); // Compute softmax
    nnData.class_detected = classification_cal(nnData.softmax, FE_NN_OUT_SIZE, 0.5); // Compute classification

    printf("Golden vectors matched: %d not matched: %d\n", FE_NN_OUT_SIZE - error, error);

    while(1)
    {
    }
}

//
// End of File
//

