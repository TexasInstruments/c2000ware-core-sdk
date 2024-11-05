/*
 * application.h
 *
 *  Created on: Aug 27, 2024
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "user_input_config.h"
#include "nn_utils.h"


/*****************************************************************************/
/* Application specific data Structures                                                           */
/*****************************************************************************/


//*****************************************************************************
// Derived Defines
//*****************************************************************************
//#define fft_size        (1 << fft_stages)
//#define fft_offset 10*logf(FRAME_SIZE)         //Commented without check
#if !defined(FE_RAW)
#define FE_FFT_SIZE      (1 << FE_FFT_STAGES)
#else
#define FE_FFT_SIZE        128
//#define FE_FEATURE_SIZE_PER_FRAME         (FE_FFT_SIZE)
#endif

#define NN_WL                          (1)

#if (FE_STACKING_CHANNELS==1)
#define NN_HL                          (FE_STACKING_FRAME_WIDTH)
#elif (FE_STACKING_CHANNELS==3)
#define NN_HL                          (FE_NUM_FRAME_CONCAT*FE_FEATURE_SIZE_PER_FRAME)
#endif

typedef struct
{
    float32_t frame[FE_NUM_FRAME_CONCAT][FE_FEATURE_SIZE_PER_FRAME];
} NN_frameFormat_float_t;

typedef union
{
    float32_t data[FE_STACKING_CHANNELS][NN_WL][NN_HL];
    float32_t data_flatten[FE_STACKING_CHANNELS*NN_WL*NN_HL];
#if defined(FRAME_CONCAT)
    NN_frameFormat_float_t inputCh[FE_STACKING_CHANNELS];
#endif
} NN_input_float_t;

typedef struct
{
    int8_t frame[FE_NUM_FRAME_CONCAT][FE_FEATURE_SIZE_PER_FRAME];
} NN_frameFormat_int8_t;

typedef union
{
    int8_t data[FE_STACKING_CHANNELS][NN_WL][NN_HL];
    int8_t data_flatten[FE_STACKING_CHANNELS*NN_WL*NN_HL];
#if defined(FRAME_CONCAT)
    NN_frameFormat_int8_t inputCh[FE_STACKING_CHANNELS];
#endif
} NN_input_int8_t;

typedef struct
{
    int8_t buf0[FE_NN_OUT_SIZE];

#if defined(NN_DUAL_OUTPUT)
    int8_t buf1[FE_NN_OUT_SIZE];
#endif
} NN_output_int8_t;


typedef struct
{
    NN_class_e class_detected;
    NN_input_int8_t nn_input_int;
    NN_output_int8_t nn_output_int;
    float softmax[FE_NN_OUT_SIZE];
} NN_data_t;

/*****************************************************************************/
/* External variables                                                        */
/*****************************************************************************/

extern NN_data_t nnData;
//NN_data_t nnData;

//extern NN_input_int8_t nn_input_test_int;
extern float model_test_input[];
extern NN_input_float_t nn_input_test;


#endif /* APPLICATION_H_ */
