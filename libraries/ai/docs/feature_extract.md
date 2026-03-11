
**Feature Extract**
- **Files:**: `feature_extract.h`, `feature_extract.c`, `feature_extract_c29.c`

- **Purpose:**: Implements the embedded feature-extraction pipeline used before inference. The pipeline supports preprocessing (mean removal), windowing (Hann), FFT, FFT normalization, DC removal, frequency binning, log scaling, frame concatenation (sliding window), and optional batch normalization / quantization support.

**Types & Configuration**
- **`model_input_t`**: Input sample type — `int8_t` when `SKIP_NORMALIZE` is defined, otherwise `float`.
- **`model_output_t`**: Output sample type — `int8_t` when `OUTPUT_INT` is defined, otherwise `float`.
- **Important compile-time macros**: `FE_FRAME_SIZE`, `FE_FFT_STAGES`, `FE_FEATURE_SIZE_PER_FRAME`, `FE_MIN_FFT_BIN`, `FE_FFT_BIN_SIZE`, `FE_BIN_NORMALIZE`, `FE_STACKING_CHANNELS`, `FE_STACKING_FRAME_WIDTH`, `FE_VARIABLES`, `FE_NUM_FRAME_CONCAT`, `FE_NN_OUT_SIZE`, and feature toggles such as `FE_RAW`, `FE_WIN`, `FE_FFT`, `FE_NORMALIZE`, `FE_DC_REM`, `FE_BIN`, `FE_LOG`, `FE_CONCAT`, `SKIP_NORMALIZE`, `OUTPUT_INT`.

**Data structure**
- **`feature_extraction`**: Context structure that holds pointers to input, output, history and scratch buffers plus a few runtime flags and a size field.
	- `input_buffer`: pointer to samples to process.
	- `output_buffer`: pointer where extracted features will be written.
	- `history_buffer`: optional pointer used for initialization/history handling.
	- `scratch_buffer`: workspace used during processing (size requested by `FE_allocFeatureExtract`).
	- `test_feature_extraction`: boolean to toggle test-mode output handling.
	- `size_required_by_library`: returned by `FE_allocFeatureExtract` to indicate scratch size requirements.

**Public API (high level)**
- **`void FE_allocFeatureExtract(feature_extraction_handle fe);`**: Calculates and sets `fe->size_required_by_library` (the implementation uses approximately `FE_FRAME_SIZE * 4 * sizeof(float)`). Call this first to know scratch-buffer requirements.
- **`void FE_initFeatureExtract(feature_extraction_handle fe);`**: Initializes history and output buffers. When `SKIP_NORMALIZE` is defined it applies batch-normalization using parameters from `tvmgen_default.h`; otherwise copies floats directly.
- **`void FE_runFeatureExtract(feature_extraction_handle fe);`**: Perform full feature extraction pipeline for each channel configured by the build flags. The function performs safety checks (NULL pointers) before processing.
- **`int FE_compareModelInput(model_input_t* expected_array, model_input_t* obtained_array);`**: Compares model input arrays and returns the number of mismatches.
- **`int FE_compareModelOutput(model_output_t* expected_array, model_output_t* obtained_array);`**: Compares model output arrays and returns the number of mismatches.

**Supporting helpers (exposed)**
- **`void FE_getHanningWindow(float *hanning_window, uint16_t frame_size);`**: Fills `hanning_window` using the compiled-in `HANN*` table for `FE_FRAME_SIZE`.
- **`void FE_windowing(float *input_buffer, float *hanning_window, uint16_t frame_size);`**: Applies symmetric Hann window in-place on `input_buffer` using `hanning_window`.
- **`void FE_fft(float *fft_input_buffer, float *fft_output_buffer, uint16_t frame_size, uint16_t fft_stages);`**: Thin wrapper that calls the platform FFT implementation (`FE_cfft` implemented in `feature_extract_c29.c` for C29 targets).
- **`void FE_fftNormalize(float *input_buffer, uint16_t frame_size);`**: Scales FFT magnitudes by `1/frame_size`.
- **`void FE_bin(float *input_buffer, uint16_t feature_size_per_frame, uint16_t minimum_bin_size, uint16_t bin_size, uint16_t normalize_bin, uint16_t array_len);`**: Accumulates or averages bins from FFT magnitudes into lower-dimensional features.
- **`void FE_log(float *input_buffer, uint16_t feature_size_per_frame, float log_mul, float log_threshold, float log_base);`**: Applies log-scaling to features. If `log_base` > 0 a scaling by `1/log(log_base)` is applied; inputs below zero are converted to absolute for numeric stability in the implementation.

**Batch normalization helpers**
- **`void FE_batchNormalization_npu(float *input_buffer, int8_t *output_buffer, float bias_val, int32_t scale_val, int32_t shift_val, uint16_t feature_size);`**: Applies a quantized-style normalization pipeline used with `SKIP_NORMALIZE` builds. Result is clamped to `int8_t`.
- **`void FE_batchNormalization_cpu(float *input_buffer, uint8_t *output_buffer, float scale_val, int32_t zero_point_val, uint16_t feature_size);`**: Reference CPU-style quantization used in some flows. Clamps to `[0,255]`.

**C29-specific implementation notes**
- `feature_extract_c29.c` implements `FE_cfft` using the C29 single-precision CFFT API (`cfft_f32`). It prepares twiddle factors, configures the `CFFT_F32_STRUCT` handle and calls the C29-optimized FFT routines. The function then computes magnitudes and writes a half-spectrum (magnitude array) back to the provided buffer(s).
- The C29 FFT implementation expects platform constants like `FE_FRAME_SIZE` and `FE_FFT_STAGES` to be available at compile time and uses a twiddle-factor array sized relative to `FE_FRAME_SIZE`.

**Pipeline overview (what `FE_runFeatureExtract` does, depending on build flags)**
- Input copy: copies a frame from `fe->input_buffer` into `fe->scratch_buffer`.
- FE_RAW (optional): mean removal (subtract frame mean) to center the signal.
- FE_WIN (optional): compute and apply a Hann window (symmetric) to the frame.
- FE_FFT (optional): run complex FFT, producing an interleaved complex spectrum then magnitudes.
- FE_NORMALIZE (optional): divide FFT magnitudes by the FFT size.
- FE_DC_REM (optional): drop/shift DC bin from the spectrum.
- FE_BIN (optional): reduce spectrum length to `FE_FEATURE_SIZE_PER_FRAME` by summing or averaging frequency bins.
- FE_LOG (optional): apply log scaling to the binned/magnitude values.
- FE_CONCAT (optional): shift previous frames and concatenate features to form a temporal context (sliding window).
- Batch normalization / quantize: either `FE_batchNormalization_npu` (when `SKIP_NORMALIZE` is enabled and quantized model path is used) or copy the float outputs directly into `output_buffer`.

**Example usage (pseudo-code)**
```
// Allocate and initialize
feature_extraction fe = {0};
fe.input_buffer = input_ptr;        // float samples: size = FE_VARIABLES * FE_FRAME_SIZE
fe.output_buffer = output_ptr;      // pre-allocated output area
fe.history_buffer = history_ptr;    // optional

FE_allocFeatureExtract(&fe);        // sets fe.size_required_by_library
fe.scratch_buffer = malloc(fe.size_required_by_library);
FE_initFeatureExtract(&fe);

// Process frames (per call will iterate channels as configured)
FE_runFeatureExtract(&fe);

// compare / validate
int mismatches = FE_compareModelInput(expected, actual);
```

**Behavior & safety notes**
- The implementation does early returns on NULL pointers for public APIs (`FE_allocFeatureExtract`, `FE_initFeatureExtract`, `FE_runFeatureExtract`, etc.).
- When `SKIP_NORMALIZE` is defined, the code uses quantization parameters defined in `tvmgen_default.h` (for example: `tvmgen_default_bias_data`, `tvmgen_default_scale_data`, `tvmgen_default_shift_data`). Ensure those symbols are linked into your build.
- The Hanning window tables (`HANN32`, `HANN64`, ... `HANN2048`) are referenced at compile time; ensure `FE_FRAME_SIZE` matches one of the supported sizes or the code will default to a zero-filled `hann` table.
- The C29 FFT implementation uses the `cfft_f32` API and writes a half-spectrum magnitude array into the provided buffers. Check buffer sizing carefully: the pipeline assumes `scratch_buffer` contains multiple contiguous regions for temporary input, twiddles, and output (see `FE_allocFeatureExtract` suggestion for size).

**Troubleshooting**
- If features look all zero or NaN: verify `FE_FRAME_SIZE`, `FE_FFT_STAGES` and that input samples are not all constant. Check that `FE_getHanningWindow` returns a valid table for the configured frame size.
- If quantized results are unexpectedly clipped: confirm batch-normalization parameters from `tvmgen_default.h` and that `SKIP_NORMALIZE` and `OUTPUT_INT` build modes are consistent with your model.

**References**
- See `feature_extract.h` for API and data-structure definitions.
- See `feature_extract.c` for the pipeline and helper implementations.
- See `feature_extract_c29.c` for the C29-optimized FFT wrapper used by `FE_fft`.

