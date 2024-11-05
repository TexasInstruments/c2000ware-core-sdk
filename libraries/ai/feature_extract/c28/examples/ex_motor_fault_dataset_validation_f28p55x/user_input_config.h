#ifndef INPUT_CONFIG_H_
#define INPUT_CONFIG_H_

#define FE_FFT
#define FE_BIN
//#define FE_RAW
//#define FRAME_CONCAT
#define NN_INPUT_DIM_2D1
//#define NN_INPUT_DIM_1D


#define FE_FFT_STAGES                 8

// FFT bin used per feature
#define FE_FRAME_SIZE   256
// Minimum FFT bin number
#define FE_MIN_FFT_BIN 1

#if defined(FE_FFT) && defined(FE_BIN)
//#define FE_FFT_SIZE      (1 << FE_FFT_STAGES)
#if defined(NN_INPUT_DIM_2D1)
#define FE_STACKING_CHANNELS              (3)
#endif
#if defined(NN_INPUT_DIM_1D)
#define FE_STACKING_CHANNELS    1
#define FE_STACKING_FRAME_WIDTH 384
#endif
#define FE_NUM_FRAME_CONCAT               (8)
#define FE_FEATURE_SIZE_PER_FRAME         (16)
#endif

#if defined(FE_FFT) && !defined(FE_BIN)
//#define FE_FFT_SIZE      (1 << FE_FFT_STAGES)
#define FE_STACKING_CHANNELS       3
#define FE_NUM_FRAME_CONCAT        1
#define FE_FEATURE_SIZE_PER_FRAME  128
#endif

#if defined(FE_RAW)
#define FE_STACKING_CHANNELS              (3)
#define FE_NUM_FRAME_CONCAT               (1)
//#define FE_FFT_SIZE        128
#define FE_FEATURE_SIZE_PER_FRAME         (FE_FFT_SIZE)
#endif // end of RAW

#define FE_NN_OUT_SIZE                    (4) // Number of output classes

#endif /* INPUT_CONFIG_H_ */
