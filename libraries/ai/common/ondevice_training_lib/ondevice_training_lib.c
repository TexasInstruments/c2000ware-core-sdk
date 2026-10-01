// #############################################################################
//
//  FILE:   ondevice_training_lib.c
//
//! Implements functions for on-device neural network training including
//! forward/backward passes, weight updates, and layer operations.
//
// #############################################################################
//
// Copyright (C) 2026 Texas Instruments Incorporated - http://www.ti.com
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


#include "ondevice_training_lib.h"
#include <device.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>

// ============================================================================
// INITIALIZATION
// ============================================================================

int ODT_Init(ModelContext_t* ctx, float learning_rate) {

    if (ctx == NULL || learning_rate <= 0.0f) {
        ODT_LOG("ERROR: ODT_Init - invalid parameters\n");
        return -1;
    }

    uint16_t i;
    
    ODT_LOG("\n========================================\n");
    ODT_LOG("ODT INITIALIZATION\n");
    ODT_LOG("========================================\n");
    
    // Copy from weights to best weights
    memcpy(ALL_BEST_WEIGHTS, ALL_WEIGHTS, TOTAL_PARAMS * sizeof(float));
    
    ctx->learning_rate = learning_rate;

    // Zero gradient accumulators if using batch training
    #if USE_GRADIENT_ACCUMULATION
    memset(ALL_WEIGHT_GRADS, 0, TOTAL_PARAMS * sizeof(float));
    #endif
    
    //Setup weight pointers
    ctx->current_weights = ALL_WEIGHTS;
    ctx->best_weights = ALL_BEST_WEIGHTS;
    #if USE_GRADIENT_ACCUMULATION
    ctx->weight_gradients = ALL_WEIGHT_GRADS;
    #endif
    
    // Setup layers
    ctx->num_layers = NUM_TRAINABLE_LAYERS;
    for (i = 0; i < NUM_TRAINABLE_LAYERS; i++) {
        // Copy layer config from flash
        ctx->layers[i] = LAYER_PARAMS_INIT[i];

         // Validate layer dimensions
        if (ctx->layers[i].input_size == 0 || ctx->layers[i].output_size == 0) {
            ODT_LOG("ERROR: ODT_Init - layer %" PRIu16 " has zero input/output size\n", i);
            return -1;
        }

        // Validate weight/bias offsets are within bounds
        if (ctx->layers[i].weight_count > 0) {
            if ((uint32_t)ctx->layers[i].weight_offset + ctx->layers[i].weight_count > TOTAL_PARAMS) {
                ODT_LOG("ERROR: ODT_Init - layer %" PRIu16 " weight offset out of bounds\n", i);
                return -1;
            }
        }
        if (ctx->layers[i].bias_count > 0) {
            if ((uint32_t)ctx->layers[i].bias_offset + ctx->layers[i].bias_count > TOTAL_PARAMS) {
                ODT_LOG("ERROR: ODT_Init - layer %" PRIu16 " bias offset out of bounds\n", i);
                return -1;
            }
        }

        // Validate adjacent layer sizes match
        if (i > 0 && ctx->layers[i].input_size != ctx->layers[i - 1].output_size) {
            ODT_LOG("ERROR: ODT_Init - layer %" PRIu16 " input size mismatch with previous layer\n", i);
            return -1;
        }
        
        // Set weight pointers into flat arrays
        if (ctx->layers[i].weight_count > 0) {
            ctx->layers[i].weights = &ALL_WEIGHTS[ctx->layers[i].weight_offset];
            #if USE_GRADIENT_ACCUMULATION
            ctx->layers[i].weight_grad = &ALL_WEIGHT_GRADS[ctx->layers[i].weight_offset];
            #endif
        } else {
            ctx->layers[i].weights = NULL;
            #if USE_GRADIENT_ACCUMULATION
            ctx->layers[i].weight_grad = NULL;
            #endif
        }
        
        // Set bias pointers
        if (ctx->layers[i].bias_count > 0) {
            ctx->layers[i].bias = &ALL_WEIGHTS[ctx->layers[i].bias_offset];
            #if USE_GRADIENT_ACCUMULATION
            ctx->layers[i].bias_grad = &ALL_WEIGHT_GRADS[ctx->layers[i].bias_offset];
            #endif
        } else {
            ctx->layers[i].bias = NULL;
            #if USE_GRADIENT_ACCUMULATION
            ctx->layers[i].bias_grad = NULL;
            #endif
        }
        
        // Log layer info
        ODT_LOG("  Layer %" PRIu16 ": ", i);
        switch (ctx->layers[i].type) {
            case LAYER_TYPE_LINEAR:
                ODT_LOG("Linear(%" PRIu16 "→%" PRIu16 ")\n", ctx->layers[i].input_size, ctx->layers[i].output_size);
                break;
            case LAYER_TYPE_RELU:
                ODT_LOG("ReLU(%" PRIu16 ")\n", ctx->layers[i].input_size);
                break;
            default:
                return -1;
        }
    }

    // Validate first layer matches frozen model output
    if (ctx->layers[0].input_size != FROZEN_OUTPUT_SIZE) {
        ODT_LOG("ERROR: ODT_Init - first layer input size (%" PRIu16 ") != FROZEN_OUTPUT_SIZE (%d)\n", ctx->layers[0].input_size, FROZEN_OUTPUT_SIZE);
        return -1;
    }

    // Validate last layer matches expected final output
    if (ctx->layers[NUM_TRAINABLE_LAYERS - 1].output_size != FINAL_OUTPUT_SIZE) {
        ODT_LOG("ERROR: ODT_Init - last layer output size (%" PRIu16 ") != FINAL_OUTPUT_SIZE (%d)\n", ctx->layers[NUM_TRAINABLE_LAYERS - 1].output_size, FINAL_OUTPUT_SIZE);
        return -1;
    }
    
    // Setup intermediate and gradient buffers
    for (i = 0; i <= NUM_TRAINABLE_LAYERS; i++) {
        // Assign pointers into static buffer arrays using offsets
        ctx->intermediate_buffers[i] = &INTERMEDIATE_BUFFERS[BUFFER_OFFSETS[i]];
        ctx->gradient_buffers[i] = &GRADIENT_BUFFERS[BUFFER_OFFSETS[i]];
    }
    
    
    ctx->batch_sample_count = 0;
    // Start in inference mode
    ctx->is_training_mode = PHASE_INFERENCE;  
    return 0;
}

// ============================================================================
// MAIN FUNCTIONS
// ============================================================================
int ODT_Forward(ModelContext_t* ctx, float* input, float* output) {
    uint16_t i;

    if (ctx == NULL || input == NULL || output == NULL) {
        ODT_LOG("ERROR: ODT_Forward - invalid parameters\n");
        return -1;
    }
    
    // Copy input to first buffer
    memcpy(ctx->intermediate_buffers[0], input, FROZEN_OUTPUT_SIZE * sizeof(float));
    
    //Execute each layer in sequence
    for (i = 0; i < ctx->num_layers; i++) {
        LayerParams_t* layer = &ctx->layers[i];
        float* layer_input = ctx->intermediate_buffers[i];      // Input to this layer
        float* layer_output = ctx->intermediate_buffers[i + 1]; // Output of this layer
        
        // Call appropriate function based on layer type
        switch (layer->type) {
            case LAYER_TYPE_LINEAR:
                ODT_LinearForward(layer_input, layer_output, layer);
                break;
            case LAYER_TYPE_RELU:
                ODT_ReLUForward(layer_input, layer_output, layer->input_size);
                break;
            default:
                ODT_LOG("ERROR: ODT_Forward - unknown layer type at layer %" PRIu16 "\n", i);
                return -1;
        }
    }
    
    // Copy final result to output
    memcpy(output, ctx->intermediate_buffers[ctx->num_layers], FINAL_OUTPUT_SIZE * sizeof(float));
    return 0;
}


int ODT_Backward(ModelContext_t* ctx, float* loss_gradient) {
    int16_t i;  

    if (ctx == NULL || loss_gradient == NULL) {
        ODT_LOG("ERROR: ODT_Backward - invalid parameters\n");
        return -1;
    }

    // Copy loss gradient to last gradient buffer
    memcpy(ctx->gradient_buffers[ctx->num_layers], loss_gradient, FINAL_OUTPUT_SIZE * sizeof(float));
    
    // Execute layers in REVERSE order
    for (i = ctx->num_layers - 1; i >= 0; i--) {
        LayerParams_t* layer = &ctx->layers[i];
        
        float* grad_output = ctx->gradient_buffers[i + 1];  // Gradient from next layer
        float* grad_input = ctx->gradient_buffers[i];       // Gradient to previous layer
        float* layer_input = ctx->intermediate_buffers[i];  // Saved from forward pass
        float* layer_output = ctx->intermediate_buffers[i + 1];  // Saved from forward pass
        
        switch (layer->type) {
            case LAYER_TYPE_LINEAR:
                ODT_LinearBackward(ctx, grad_output, grad_input, layer_input, layer);
                break;
            case LAYER_TYPE_RELU:
                ODT_ReLUBackward(grad_output, grad_input, layer_output, layer->output_size);
                break;
             default:
                ODT_LOG("ERROR: ODT_Backward - unknown layer type at layer %d\n", i);
                return -1;
        }
    }
    return 0;
}

int ODT_UpdateWeights(ModelContext_t* ctx, uint16_t batch_size) {
    if (ctx == NULL || batch_size == 0) {
        ODT_LOG("ERROR: ODT_UpdateWeights - invalid parameters\n");
        return -1;
    }

    //When the batch size is 1, gradients are applied to the parameters in the backward function itself. If batch size is more than 1, we need to accumulate and update here. 
    #if USE_GRADIENT_ACCUMULATION
        // Batch Mode: Apply accumulated gradients
        uint32_t i;
        float scale = ctx->learning_rate / batch_size;  // Average gradients
        
        // Update all weights in one pass
        for (i = 0; i < TOTAL_PARAMS; i++) {
            ctx->current_weights[i] -= scale * ctx->weight_gradients[i];
        }
    #endif
    return 0;
}

int ODT_ZeroGradients(ModelContext_t* ctx) {
    if (ctx == NULL) {
        ODT_LOG("ERROR: ODT_ZeroGradients - ctx is NULL\n");
        return -1;
    }
    
    // No need to zero gradient when batch size is 1 as we are not accumulating gradient at all. 
    #if USE_GRADIENT_ACCUMULATION
        // Batch Mode: Clear gradient accumulators
        memset(ctx->weight_gradients, 0, TOTAL_PARAMS * sizeof(float));
    #endif
    return 0;
}

int ODT_SaveBestWeights(ModelContext_t* ctx) {
    if (ctx == NULL) {
        ODT_LOG("ERROR: ODT_SaveBestWeights - ctx is NULL\n");
        return -1;
    }

    // Copy current weights to best weights
    memcpy(ctx->best_weights, ctx->current_weights, TOTAL_PARAMS * sizeof(float));
    return 0;
}


int ODT_LoadBestWeights(ModelContext_t* ctx) {
    if (ctx == NULL) {
        ODT_LOG("ERROR: ODT_LoadBestWeights - ctx is NULL\n");
        return -1;
    }

    // Copy best weights to current weights
    memcpy(ctx->current_weights, ctx->best_weights, TOTAL_PARAMS * sizeof(float));
    return 0;
}

// ============================================================================
// LAYER OPERATIONS - Linear
// ============================================================================
void ODT_LinearForward(float* input, float* output, LayerParams_t* layer) {
    uint16_t i, j;
    uint16_t rows = layer->shape.linear.rows;  // output_size 
    uint16_t cols = layer->shape.linear.cols;  // input_size 
    
    float* weights = layer->weights;  // Pointer to weight matrix
    float* bias = layer->bias;        // Pointer to bias vector
    
    // For each output neuron i
    for (i = 0; i < rows; i++) {
        float sum = 0.0f;
        
        // Compute dot product: row i of W with input vector
        for (j = 0; j < cols; j++) {
            // Calculate index in 1D weight array
            uint32_t w_idx = (uint32_t)i * cols + j;  // W[i][j]
            
            // Accumulate: sum += W[i][j] × input[j]
            sum += weights[w_idx] * input[j];
        }
        
        // Add bias: output[i] = sum + b[i]
        output[i] = sum + bias[i];
    }
}

void ODT_LinearBackward(ModelContext_t* ctx, float* grad_output, float* grad_input, float* input,
                        LayerParams_t* layer) {
    uint16_t i, j;
    uint16_t rows = layer->shape.linear.rows;  // output_size
    uint16_t cols = layer->shape.linear.cols;  // input_size
    
    float* weights = layer->weights;
    float* bias = layer->bias;
    
    // Compute grad_input = W^T × grad_output
    for (j = 0; j < cols; j++) {  // For each input
        float sum = 0.0f;
        
        for (i = 0; i < rows; i++) {  // Sum over outputs
            uint32_t w_idx = (uint32_t)i * cols + j;  // W[i,j]
            sum += weights[w_idx] * grad_output[i];
        }
        
        grad_input[j] = sum;
    }
    
    // Weight/Bias Gradients (CONDITIONAL based on batch size)
    #if USE_GRADIENT_ACCUMULATION
    // Batch Mode (batch_size > 1): ACCUMULATE gradients 
     // Accumulate grad_weights += grad_output ⊗ input
    for (i = 0; i < rows; i++) {  // For each output
        for (j = 0; j < cols; j++) {  // For each input
            w_idx = (uint32_t)i * cols + j;  // W[i,j]
            layer->weight_grad[w_idx] += grad_output[i] * input[j];
        }
    }
    
    // Accumulate grad_bias 
    for (i = 0; i < rows; i++) {
        layer->bias_grad[i] += grad_output[i];
    }
    #else
    // Per-Sample Mode (batch_size = 1): UPDATE weights IMMEDIATELY
    // Compute gradient and update weight in one pass
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            uint32_t w_idx = (uint32_t)i * cols + j;
            
            // Compute gradient
            float gradient = grad_output[i] * input[j];
            
            // Update weight immediately
            weights[w_idx] -= ctx->learning_rate * gradient;
        }
    }
    
    // Update bias immediately
    for (i = 0; i < rows; i++) {
        bias[i] -= ctx->learning_rate * grad_output[i];
    }
    
    #endif
}


// ============================================================================
// LAYER OPERATIONS - ReLU
// ============================================================================
void ODT_ReLUForward(float* input, float* output, uint16_t size) {
    uint16_t i;
    
    // For each element
    for (i = 0; i < size; i++) {
        // Apply: output[i] = max(0, input[i])
        output[i] = input[i] > 0 ? input[i] : 0;
    }
}

void ODT_ReLUBackward(float* grad_output, float* grad_input, 
                      float* forward_output, uint16_t size) {
    uint16_t i;
    
    for (i = 0; i < size; i++) {
        // If forward output was positive, pass gradient through
        // Otherwise, block gradient (set to 0)
        grad_input[i] = (forward_output[i] > 0) ? grad_output[i] : 0;
    }
}

// ============================================================================
// LOSS FUNCTIONS
// ============================================================================

int ODT_MSELoss(float* prediction, float* target, uint16_t size, float* loss) {
    uint16_t i;
    float sum = 0.0f;

    if (prediction == NULL || target == NULL || size == 0 || loss == NULL) {
        ODT_LOG("ERROR: ODT_MSELoss - invalid parameters\n");
        return -1;
    }
    
    // Sum of squared errors
    for (i = 0; i < size; i++) {
        float diff = prediction[i] - target[i];   // Error
        sum += diff * diff;                       // Squared error
    }
    
    // Store average
    *loss = sum / size;
    return 0;
}

int ODT_MSEGradient(float* prediction, float* target, float* grad_output, uint16_t size) {
    uint16_t i;

    if (prediction == NULL || target == NULL || grad_output == NULL || size == 0) {
        ODT_LOG("ERROR: ODT_MSEGradient - invalid parameters\n");
        return -1;
    }

    float scale = 2.0f / size;  // 2/N
    
    // Compute gradient for each element
    for (i = 0; i < size; i++) {
        grad_output[i] = scale * (prediction[i] - target[i]);
    }
    return 0;
}

