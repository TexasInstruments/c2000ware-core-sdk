/*
 *  Created on: Nov 20, 2025
 */
// #############################################################################
//
//  FILE:   nn_utils.c
//
//!
//! This contains definition of neural network utils API functions
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

#include "math.h"
#ifdef __TMS320C2000__
#include "driverlib.h"
#else
#include "stdint.h"
#endif

void NN_softmaxCal(int8_t *softmax_cal_inptr, uint16_t inLen, float *softmax_cal_outptr)
{
    uint16_t i;
    float softmax_sum = 0;

    for (i = 0; i < inLen; i++)
    {
        if (softmax_cal_inptr[i] < 0)
        {
            softmax_cal_outptr[i] = (1 / expf((softmax_cal_inptr[i] * -0.1)));
        }
        else
        {
            softmax_cal_outptr[i] = expf((softmax_cal_inptr[i] * 0.1));
        }

        softmax_sum += softmax_cal_outptr[i];
    }

    for (i = 0; i < inLen; i++)
    {
        softmax_cal_outptr[i] = (float)(softmax_cal_outptr[i] / softmax_sum);
    }

    return;
}


int NN_classificationCal(float *classification_cal_inptr, uint16_t inLen, float threshold)
{
    int class = 0, idx = 0;
    // Find index with the max probability
    for (idx = 1; idx < inLen; idx++)
    {
        if (classification_cal_inptr[class] < classification_cal_inptr[idx])
        {
            class = idx;
        }
    }

    // Set threshold
    class = (classification_cal_inptr[class] >= threshold) ? class : inLen; // inLen is considered as unknown class

    return class;
}

