//#############################################################################
//
// FILE:   application_main.c
//
//! This example shows the use of feature_extract library files in to process
//! arc_fault_detection dataset. The example is developed on f28p55
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
#include <stdint.h>
#include <stdio.h>
#include "driverlib.h"
#include "device.h"
#include "board.h"
#include "c2000ware_libraries.h"
#include "tvmgen_default.h"
#include "math.h"

#include "feature_extract.h"
#include "user_input_config.h"

// feat_extract_STRUCT object
//feat_extract_STRUCT pre_process1;

// Handle to the feat_extract_STRUCT object
//feat_extract_STRUCT_Handle hnd_pre_process1 = &pre_process1;

//
// #defines
//

//*****************************************************************************
// Derived Defines
//*****************************************************************************

//#define FE_FRAME_SIZE      (1 << FE_FFT_STAGES)

#define PASS 1
#define FAIL 0

#define e 2.71828183F

#pragma DATA_SECTION(scratch_buffer, "FFT_buffer_1")
//float scratch_buffer[FFT_SIZE*4];
#define SCRATCH_BUFFER_LEN (FE_FRAME_SIZE*4)
#define SCRATCH_BUFFER_SIZE (SCRATCH_BUFFER_LEN*sizeof(float))
float scratch_buffer[SCRATCH_BUFFER_LEN];

//
// Global variable declarations
//

//Raw input
extern float raw_input_test[];


#ifdef NPU_VERIFICATION
extern float model_input_top_float[FE_FEATURE_SIZE_PER_FRAME];
#endif

// NN model output
extern int8_t golden_output[FE_NN_OUT_SIZE];

int test_result;
int status = 0;
int error = 0;
typedef int8_t output_t;
typedef struct
{
  output_t buf0[FE_NN_OUT_SIZE];
} NN_result_t;
NN_result_t result;

//
// Main
//
void main(void)
{

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Disable pin locks and enable internal pull-ups.
    //
    Device_initGPIO();

    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    //
    // PinMux and Peripheral Initialization
    //
    Board_init();

    //
    // C2000Ware Library initialization
    //
    C2000Ware_libraries_init();

    //
    // Enable Global Interrupt (INTM) and real time interrupt (DBGM)
    //
    EINT;
    ERTM;

    Flash_enablePrefetch(FLASH0CTRL_BASE);

    //Pre_processing_variable_init();

    //if NPU hardware accelerator exists in current device and it is enabled
    #ifdef TVMGEN_DEFAULT_TI_NPU
    extern void TI_NPU_init();
    TI_NPU_init();
    #endif

    //int status = 0;

    int8_t model_input_test[FE_FEATURE_SIZE_PER_FRAME] = {0};
    int8_t *model_inputPtr;
    result.buf0[0] = 0;
    result.buf0[1] = 0;

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
    init_params.min_fft_bin_size = FE_MIN_FFT_BIN;
    init_params.num_frame_concat = FE_NUM_FRAME_CONCAT;
    init_params.feature_size_per_frame = FE_FEATURE_SIZE_PER_FRAME;
    init_params.total_feature_size_per_frame = (init_params.feature_size_per_frame)*(init_params.num_input_channels);
    init_params.fft_stage_num = FE_FFT_STAGES;
    init_params.nn_output_size = FE_NN_OUT_SIZE;
    init_params.fft_bin_size = FE_FFT_BIN_SIZE;
    init_params.fft_size = FE_FRAME_SIZE;
    init_params.size_of_frame = FE_FRAME_SIZE;
    init_params.output_convert_bias = tvmgen_default_bias_data;
    init_params.output_convert_scale = tvmgen_default_scale_data;
    init_params.output_convert_shift = tvmgen_default_shift_data;
    init_params.log_multiply = FE_LOG_MUL;
    init_params.log_base = FE_LOG_BASE;

    //Remaining initial parameter declaration initialized with null value. These only for user's reference
    init_params.output_feature_height = 0;
    init_params.num_input_channels = 0;
    init_params.output_feature_width = 0;
    init_params.output_convert_shift_len = sizeof(tvmgen_default_shift_data) / sizeof(tvmgen_default_shift_data[0]);

    //Feature_Extract_State_Params state_params;

    Feature_Extract_Alloc_Params alloc_params;
    alloc_feature_extract(&init_params, &alloc_params);
    ASSERT(SCRATCH_BUFFER_SIZE >= alloc_params.scratch_size);
    ASSERT(sizeof(Feature_Extract_Handle_Params) >= alloc_params.handle_size);

    Feature_Extract_Handle_Params handle_params;

    init_feature_extract(&init_params, &handle_params);

    void *input_buffer = raw_input_test;
    void *output_buffer = &model_input_test[0];
    void *scratch_buffer1 = scratch_buffer;
    run_feature_extract(&handle_params, input_buffer, output_buffer, scratch_buffer1);

    model_inputPtr = &model_input_test[0];

    struct tvmgen_default_inputs inputs = { (void*) model_inputPtr};
    struct tvmgen_default_outputs outputs = { &result.buf0[0] };

    status = tvmgen_default_run(&inputs, &outputs);

    //if NPU hardware accelerator exists in current device and it is enabled
    #ifdef TVMGEN_DEFAULT_TI_NPU
    extern volatile int32_t tvmgen_default_finished;
    while (!tvmgen_default_finished) ;
    #endif

    int i = 0;
    for(i=0;i<FE_NN_OUT_SIZE;i++)
    {
        if(abs(golden_output[i] - result.buf0[i])>2)
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
    
    printf("Golden vectors matched: %d not matched: %d\n", FE_NN_OUT_SIZE - error, error);

    while(1)
    {
        
    }
}

//
// End of File
//
