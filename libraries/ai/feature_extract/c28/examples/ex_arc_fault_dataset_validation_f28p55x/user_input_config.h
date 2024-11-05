/*
 * user_input.h
 *
 *  Created on: July 16, 2024
 *      Author: a0488208
 */

#ifndef INPUT_CONFIG_H_
#define INPUT_CONFIG_H_

#define WIN
#define FFT
#define BIN


//*****************************************************************************
// for FFT
//*****************************************************************************
#define FE_FRAME_SIZE       1024
#define FE_FFT_STAGES      10

//#define WINDOW

//#define CFFT

//#define REFRAME
// Parameters related to pre-processing feature extraction. Please refer to application note for more information.
// These parameters need to match parameters set in the training section of Edge AI Model Composer.

// Feature size per frame
#define FE_FEATURE_SIZE_PER_FRAME 256
// Frames to concatenate
#define FE_NUM_FRAME_CONCAT 1
//uint16_t num_frame_concat = 1;
// Minimum FFT bin number
#define FE_MIN_FFT_BIN 1
// FFT bin used per feature
#define FE_FFT_BIN_SIZE 2


//#define Log_Base10

//***********dummy def, to be used/merged later***********//

//#define FE_STACKING_CHANNELS              (3)                                            //dummy def, to be used/merged later
//uint16_t num_input_channel = 3;
#define FE_NN_OUT_SIZE                    2


//****************************//


#endif /* INPUT_CONFIG_H_ */
