#ifndef TVMGEN_DEFAULT_H_
#define TVMGEN_DEFAULT_H_
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Symbol defined when running model on TI NPU hardware accelerator */
#define TVMGEN_DEFAULT_TI_NPU
#ifdef TVMGEN_DEFAULT_TI_NPU_SOFT
	#error Conflicting definition for where model should run.
#endif

/* The generated model library expects the following inputs/outputs:
 * Inputs:
 *    Tensor[(1, 3, 128, 1), int8]
 * Outputs:
 *    Tensor[(1, 6), int8]
 */

/* Input feature normalization parameters:
 *   input_int = clip(((int32_t)((input_float + bias) * scale)) >> shift, min, max)
 *   where (min, max) = (-128, 127) if int8 type, (0, 255) if uint8 type
 */
#define TVMGEN_DEFAULT_BIAS_LEN 3
#define TVMGEN_DEFAULT_SCALE_LEN 3
#define TVMGEN_DEFAULT_SHIFT_LEN 1
extern const int32_t tvmgen_default_bias_data[] __attribute__((weak)) = {-83, -80, -79};
extern const int32_t tvmgen_default_scale_data[] __attribute__((weak)) = {163, 165, 160};
extern const int32_t tvmgen_default_shift_data[] __attribute__((weak)) = {7};


/* TI NPU hardware accelerator initialization */
extern void TI_NPU_init();

/* Flag for model execution completion on TI NPU hardware accelerator */
extern volatile int32_t tvmgen_default_finished;


/*!
 * \brief Input tensor pointers for TVM module "default" 
 */
struct tvmgen_default_inputs {
  void* onnx__Add_0;
};

/*!
 * \brief Output tensor pointers for TVM module "default" 
 */
struct tvmgen_default_outputs {
  void* output;
};

/*!
 * \brief entrypoint function for TVM module "default"
 * \param inputs Input tensors for the module 
 * \param outputs Output tensors for the module 
 */
int32_t tvmgen_default_run(
  struct tvmgen_default_inputs* inputs,
  struct tvmgen_default_outputs* outputs
);

#ifdef __cplusplus
}
#endif

#endif // TVMGEN_DEFAULT_H_
