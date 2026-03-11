// #############################################################################
//
//  FILE:   application_main.c
//
//! This example shows the use of feature_extract library files in to process
//! hello world dataset and perform AI inference using a pre-trained
//! model. The feature extraction library extracts relevant features
//! from raw input data and prepares the input for the model.
//
// #############################################################################
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
// #############################################################################

//
// Included Files
//
#include "board.h"
#include "c2000ware_libraries.h"
#include "device.h"
#include "driverlib.h"
#include "math.h"
#include "tvmgen_default.h"
#include <stdint.h>
#include <stdio.h>

#include "feature_extract.h"
#include "user_input_config.h"

#pragma DATA_SECTION(scratch_buffer, "FFT_buffer_1")
float scratch_buffer[FE_FRAME_SIZE * 4];

// test case from test vector
extern float raw_input_test[];
extern float model_test_input[];
extern model_output_t golden_output[];

// NN model output
#define FAIL 0
#define PASS 1
int test_result = FAIL;
#define TEST_FEATURE_EXTRACT

model_input_t model_input[1 * FE_STACKING_CHANNELS * FE_STACKING_FRAME_WIDTH * 1];
#if defined(TEST_FEATURE_EXTRACT)
model_input_t test_feature_extraction[1 * FE_STACKING_CHANNELS * FE_STACKING_FRAME_WIDTH * 1];
#endif

model_output_t model_output[FE_NN_OUT_SIZE];

void boards_init()
{
    // Initialize device clock and peripherals
    Device_init();

    // Disable pin locks and enable internal pull-ups.
    Device_initGPIO();

    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    Interrupt_initModule();

    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    Interrupt_initVectorTable();

    // PinMux and Peripheral Initialization
    Board_init();
    
    // C2000Ware Library initialization
    C2000Ware_libraries_init();
    
    // Enable Global Interrupt (INTM) and real time interrupt (DBGM)
    EINT;
    ERTM;
    
    Flash_enablePrefetch(FLASH0CTRL_BASE);
    return;
}

void main(void)
{
    
    boards_init();
    
    int error = 0;

    feature_extraction fe;
    feature_extraction_handle fe_handle = &fe;

    fe_handle->scratch_buffer = &scratch_buffer[0];
    FE_allocFeatureExtract(fe_handle);
    ASSERT(FE_FRAME_SIZE * 4 * sizeof(float) >= fe.size_required_by_library);

    fe_handle->input_buffer = &raw_input_test[0];
    fe_handle->history_buffer = &model_test_input[0];

#if defined(TEST_FEATURE_EXTRACT)
    fe_handle->output_buffer = &test_feature_extraction[0];
    fe_handle->test_feature_extraction = true;
    FE_initFeatureExtract(fe_handle);
#endif
    fe_handle->output_buffer = &model_input[0];
    fe_handle->test_feature_extraction = false;
    FE_initFeatureExtract(fe_handle);

    FE_runFeatureExtract(fe_handle);

#if defined(TEST_FEATURE_EXTRACT)
    error = FE_compareModelInput(test_feature_extraction, model_input);
    printf("Feature extraction mismatches %d\n", error);
#endif

    struct tvmgen_default_inputs inputs = {(void *)&model_input};
    struct tvmgen_default_outputs outputs = {(void *)&model_output};

    // if NPU hardware accelerator exists in current device and it is enabled
    tvmgen_default_run(&inputs, &outputs);
#ifdef TVMGEN_DEFAULT_TI_NPU
    extern volatile int32_t tvmgen_default_finished;
    while (!tvmgen_default_finished);
#endif

    error = FE_compareModelOutput(golden_output, model_output);

    if (error == 0)
    {
        test_result = PASS;
        printf("All tests have passed.\r\n");
    }
    printf("Golden vectors matched: %d not matched: %d\n", FE_NN_OUT_SIZE - error, error);

    while (1)
    {
    }
}

//
// End of File
//
