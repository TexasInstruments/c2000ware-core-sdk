
**Neural Network Utilities**
- **Files:**: `nn_utils.h`, `nn_utils.c`

- **Purpose:**: Helper utilities used by the edge inference path. Provides a softmax converter that turns quantized logits into float probabilities and a classification helper that selects the highest-probability class subject to a threshold.

**Public API**
- **`void NN_softmaxCal(int8_t *softmaxcalinptr, uint16_t inLen, float *softmaxcaloutptr);`**
	- **Inputs:** `softmaxcalinptr` points to quantized logits (`int8_t`), `inLen` is number of classes.
	- **Output:** `softmaxcaloutptr` receives probabilities (`float`) whose sum should be 1.0.

- **`int NN_classificationCal(float *calssification_cal_inptr, uint16_t inLen, float threshold);`**
	- **Inputs:** `calssification_cal_inptr` is a probability array, `inLen` is the number of classes, `threshold` is the minimum probability required to accept a prediction.
	- **Returns:** index of highest-probability class when that probability >= `threshold`; otherwise returns `inLen` to signal "unknown".

**Implementation overview**
- `NN_softmaxCal` accepts quantized logits and produces a floating-point probability vector. The function converts input scores to positive values, computes a normalization denominator and writes normalized probabilities into the provided output buffer.
- `NN_classificationCal` scans the probability array to find the maximum-probability index and applies the threshold rule to determine if a class should be returned or `inLen` (unknown).

**Example usage (pseudo-code)**
```
// Given int8 logits and an output array
int8_t logits[N_CLASSES];
float probs[N_CLASSES];

NN_softmaxCal(logits, N_CLASSES, probs);
int predicted = NN_classificationCal(probs, N_CLASSES, 0.5f);
if (predicted < N_CLASSES) {
	// accepted prediction
} else {
	// unknown class
}
```

**Notes**
- Callers provide input and output buffers; the API writes results into the output buffer passed as `softmaxcaloutptr`.
- The header `nn_utils.h` contains the function signatures and short descriptions.

**References**
- `nn_utils.h` — API declarations.
- `nn_utils.c` — implementation of the softmax and classification helpers.

