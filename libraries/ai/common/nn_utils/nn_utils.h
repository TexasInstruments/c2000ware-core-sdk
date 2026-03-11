/*
 *  Created on: Nov 20, 2025
 */
// #############################################################################
//
//  FILE:   nn_utils.h
//
//!
//! This contains prototyping of neural network utils API functions
//!
//
// #############################################################################
//
// Copyright (C) 2025 Texas Instruments Incorporated - http://www.ti.com
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

/**
 * \addtogroup ai_nn_group AI - Neural Network Utility APIs
 * 
 * @{
 */

/**
 * \file nn_utils.h
  * 
  * \brief
  * Header file contains enumerations, structure definitions and functions
  * declarations for Edge AI Neural Network Utils Module interface
  */

#ifndef NN_UTILS_H_
#define NN_UTILS_H_

#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief Calculate softmax probabilities from logits
 *
 * \param softmax_cal_inptr Input logits (int8_t quantized)
 * \param inLen Length of input array (number of classes)
 * \param softmax_cal_outptr Output probabilities (float)
 * 
 * Converts quantized logits to probabilities using softmax function:
 * - Handles negative values with reciprocal of exp
 * - Uses scaling factor 0.1 for numerical stability
 * - Output sums to 1.0 across all classes
 * 
 * \return None
 */
void NN_softmaxCal(int8_t *softmax_cal_inptr, uint16_t inLen, float *softmax_cal_outptr);

/**
 * \brief Determine class from probability distribution
 *
 * \param classification_cal_inptr Input probability array
 * \param inLen Number of classes
 * \param threshold Minimum probability threshold for classification
 * 
 * Returns the index of highest probability if it exceeds threshold,
 * otherwise returns inLen to indicate unknown class
 * 
 * \return Class index or inLen for unknown class
 */
int NN_classificationCal(float *classification_cal_inptr, uint16_t inLen, float threshold);
/** @} */
#ifdef __cplusplus
}
#endif  /* extern "C" */

#endif /* NN_UTILS_H_ */
