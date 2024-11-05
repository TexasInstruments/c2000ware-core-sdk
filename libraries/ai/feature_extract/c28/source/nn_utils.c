/*
 *  Created on: July 16, 2024
 */

//#############################################################################
//
// FILE:   nn_utils.c
//
//!
//! This contains definition of neural network utils API functions
//!
//
//#############################################################################
//
//
// 
// C2000Ware v5.04.00.00
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

#include "nn_utils.h"



void softmax_cal(int8_t *softmaxcalinptr, uint16_t inLen, float *softmaxcaloutptr)
{
    uint16_t i,j;
    float softmax_sum;

    float softmax_exp[NN_MAX_NUM_CLASSES];
    ASSERT(inLen < NN_MAX_NUM_CLASSES);

    for(i=0;i<inLen;i++)
    {
        if(softmaxcalinptr[i]<0)
        {
            softmax_exp[i] = 1/(expf(softmaxcalinptr[i]*-0.1));
        }
        else
        {
            softmax_exp[i] = expf(softmaxcalinptr[i]*0.1);
        }
    }

    for(i=0;i<inLen;i++)
    {
        softmax_sum = 0;
        for(j=0;j<inLen;j++)
        {
            softmax_sum = softmax_sum + softmax_exp[j];
        }
        softmaxcaloutptr[i] = (float)softmax_exp[i]/softmax_sum;
    }
}

NN_class_e classification_cal(float *calssification_cal_inptr, uint16_t inLen, float threshold)
{
    uint16_t i, imax;
    NN_class_e class;

    imax = 0;

    // Find index with the max probability
    for(i=1;i<inLen;i++)
    {
        if(calssification_cal_inptr[imax]<calssification_cal_inptr[i])
        {
            imax=i;
        }
    }

    // Set threshold
    class = (calssification_cal_inptr[imax]>=threshold) ? (NN_class_e)imax : (NN_class_e)inLen; // inLen is considered as unknown class

    return class;
}

