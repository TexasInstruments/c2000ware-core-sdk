/*
 *  Created on: Oct 8, 2024
 */
//#############################################################################
//
// FILE:   nn_utils.h
//
//!
//! This contains prototyping of neural network utils API functions
//!
//
//#############################################################################
//
//
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
//#############################################################################

#ifndef NN_UTILS_H_
#define NN_UTILS_H_

#include "feature_extract.h"
#include "math.h"

typedef enum
{
    NN_CLASS_0 = 0,
    NN_CLASS_1 = 1,
    NN_CLASS_2 = 2,
    NN_CLASS_3 = 3,
    NN_CLASS_4 = 4,
    NN_CLASS_5 = 5,
    NN_CLASS_6 = 6,
    NN_CLASS_7 = 7,
    NN_CLASS_8 = 8,
    NN_CLASS_9 = 9,
    NN_CLASS_10 = 10,
    NN_CLASS_11 = 11,
    NN_CLASS_12 = 12,
    NN_CLASS_13 = 13,
    NN_CLASS_14 = 14,
    NN_CLASS_15 = 15,
    NN_MAX_NUM_CLASSES = 16
} NN_class_e;


//*****************************************************************************
// Function Prototyping
//*****************************************************************************
void softmax_cal(int8_t *softmaxcalinptr, uint16_t inLen, float *softmaxcaloutptr);

NN_class_e classification_cal(float *calssification_cal_inptr, uint16_t inLen, float threshold);

#endif /* NN_UTILS_H_ */
