// #############################################################################
//
//  FILE:   ondevice_training_lib.h
//
//!
//! Provides implementation for on-device neural network training
//! with support for linear layers, ReLU activation, and MSE loss.
//! Designed for resource-constrained systems like TI microcontrollers.
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


#ifndef ONDEVICE_TRAINING_LIB_H
#define ONDEVICE_TRAINING_LIB_H

#ifdef DEBUG
    #include <stdio.h>
    #ifdef USE_INTERRUPT_SAFE_LOGGING
        // For systems with interrupts - disable during print
        #define ODT_LOG(...) do { \
            DINT; \
            printf(__VA_ARGS__); \
            EINT; \
        } while(0)
    #else
        // Normal logging
        #define ODT_LOG(...) printf(__VA_ARGS__)
    #endif
#else
    // No logging in release
    #define ODT_LOG(...) ((void)0)
#endif

#include <stdint.h>
#include "trainable_model_config.h"

/**
 * @brief Training phase enumeration
 */
typedef enum{
    PHASE_TRAINING,  /**< Model is in training mode */
    PHASE_INFERENCE  /**< Model is in inference mode */
} TrainingPhase_t;


/**
 * @brief Model context structure containing all training state
 */
typedef struct {
    LayerParams_t layers[NUM_TRAINABLE_LAYERS];             /**< Layer descriptors */
    uint16_t num_layers;                                    /**< Number of layers in model */
    
    /**
    * Intermediate activation buffers (for forward pass)
    * - intermediate_buffers[0] = input from frozen model
    * - intermediate_buffers[i] = output of layer[i-1]
    */
    float* intermediate_buffers[NUM_TRAINABLE_LAYERS + 1];  /**< Activation buffers for forward pass */

    /**< Gradient buffers for backward pass */
    /**< gradient_buffers[i+1] = gradient from layer i */
    /**< gradient_buffers[0] = gradient to input */
    float* gradient_buffers[NUM_TRAINABLE_LAYERS + 1];      /**< Gradient buffers for backward pass */
      
    float* current_weights;                                 /**< Points to ALL_WEIGHTS - active model parameters */
    float* best_weights;                                    /**< Points to ALL_BEST_WEIGHTS - saved best parameters */
    
    #if USE_GRADIENT_ACCUMULATION
    float* weight_gradients;                                /**< Points to ALL_WEIGHT_GRADS - accumulated gradients for batch training */
    #endif
    
    uint16_t batch_sample_count;                            /**< Samples accumulated in current batch */
    TrainingPhase_t is_training_mode;                       /**< Current phase (training or inference) */

    float learning_rate;                                    /**< Learning rate to update the parameters */
} ModelContext_t;


/**
 * @brief Initialize model context
 * @details Sets up layer pointers into flat arrays, assigns intermediate and gradient buffers, 
 *          initializes weights and training state, and stores the learning rate
 * 
 * @param ctx Model context to initialize
 * @param learning_rate Learning rate for training (e.g., 0.0001)
 * @return 0 on success, -1 on error
 */
int ODT_Init(ModelContext_t* ctx, float learning_rate);



/**
 * @brief Forward pass through all trainable layers
 * @details Processes input through each layer in sequence and stores intermediate results
 * 
 * @param ctx Model context
 * @param input Input from frozen model [FROZEN_OUTPUT_SIZE]
 * @param output Output buffer [FINAL_OUTPUT_SIZE]
 * @return 0 on success, -1 on error
 */
int ODT_Forward(ModelContext_t* ctx, float* input, float* output);



/**
 * @brief Backward pass - compute gradients for all layers. Call individual layers backward method. 
 * @details Propagates gradients backwards through the network and orchestrates the update of the gradients with respects to input, weights and biases 
 *
 * @param ctx: Model context
 * @param loss_gradient: Gradient from loss function [FINAL_OUTPUT_SIZE]
 * @return 0 on success, -1 on error
 */
int ODT_Backward(ModelContext_t* ctx, float* loss_gradient);



/**
 * @brief Update weights from accumulated gradients
 * @details Applies accumulated gradients to weights using the specified learning rate and batch size for averaging. Only updates the accumulated gradients. Does nothing when batch size is 1. 
 * 
 * @param ctx Model context
 * @param batch_size Number of samples accumulated (for averaging)
 * @return 0 on success, -1 on error
 */
int ODT_UpdateWeights(ModelContext_t* ctx, uint16_t batch_size);



/**
 * @brief Zero all gradient accumulators
 * @details Resets all weight and bias gradients to zero for a new batch
 * 
 * @param ctx Model context
 * @return 0 on success, -1 on error
 */
int ODT_ZeroGradients(ModelContext_t* ctx);


/**
 * @brief Save current weights as best weights
 * @details Copies current model weights to the best weights storage
 * 
 * @param ctx Model context
 * @return 0 on success, -1 on error
 */
int ODT_SaveBestWeights(ModelContext_t* ctx);



/**
 * @brief Load best weights to current weights
 * @details Restores the best performing weights to the current model
 * 
 * @param ctx Model context
 * @return 0 on success, -1 on error
 */
int ODT_LoadBestWeights(ModelContext_t* ctx);


/**
 * @brief Compute MSE loss
 * 
 * @param prediction: Model output [size]
 * @param target: Ground truth [size]
 * @param size: Number of elements
 * @param loss: Pointer to store computed MSE loss value
 * @return 0 on success, -1 on error
 */
int ODT_MSELoss(float* prediction, float* target, uint16_t size, float* loss);



/**
 * @brief Compute gradient of MSE loss
 * @details Calculates gradient as 2/N * (prediction - target)
 * 
 * @param prediction Model output [size]
 * @param target Ground truth [size]
 * @param grad_output Output gradient buffer [size]
 * @param size Number of elements
 * @return 0 on success, -1 on error
 */
int ODT_MSEGradient(float* prediction, float* target, float* grad_output, uint16_t size);


/**
 * @brief Linear layer forward pass
 * @details Computes output = weights @ input + bias
 * 
 * @param input Input tensor
 * @param output Output tensor
 * @param layer Layer parameters containing weights and biases
 */
void ODT_LinearForward(float* input, float* output, LayerParams_t* layer);



/**
 * @brief Linear layer backward pass
 * @details Computes gradients with respect to input, weights, and bias.
 *          For batch_size=1, updates weights immediately 
 *          For batch_size>1, accumulates gradients for later update.
 *
 * @param ctx Model context 
 * @param grad_output Gradient from next layer
 * @param grad_input Gradient to previous layer (output)
 * @param input Forward pass input 
 * @param layer Layer parameters
 * 
 */
void ODT_LinearBackward(ModelContext_t* ctx, float* grad_output, float* grad_input, float* input,
                        LayerParams_t* layer);

/**
 * @brief ReLU forward pass
 * @details Applies element-wise ReLU: output = max(0, input)
 * 
 * @param input Input tensor
 * @param output Output tensor
 * @param size Number of elements
 */
void ODT_ReLUForward(float* input, float* output, uint16_t size);



/**
 * @brief ReLU backward pass
 * @details Computes gradient: if input > 0 then 1, else 0
 * 
 * @param grad_output Gradient from next layer
 * @param grad_input Gradient to previous layer (output)
 * @param forward_output Saved output from forward pass
 * @param size Number of elements
 */
void ODT_ReLUBackward(float* grad_output, float* grad_input, 
                      float* forward_output, uint16_t size);

#endif // ONDEVICE_TRAINING_LIB_H
