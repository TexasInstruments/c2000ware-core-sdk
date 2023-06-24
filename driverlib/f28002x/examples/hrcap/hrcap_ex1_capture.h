//#############################################################################
//
// FILE:   hrcap_ex1_capture.h
//
// TITLE:  HRCAP Calibration Header
//
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2023 Texas Instruments Incorporated - http://www.ti.com/
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

//
// Included Files
//
#include "hrcap.h"

//
// Defines
//
#define HRCALCAL_STATUS_DONE_ISR    (HRCAP_CALIBRATION_DONE |                  \
                                     HRCAP_GLOBAL_CALIBRATION_INTERRUPT )

#define HRCALCAL_STATUS_DONE_PERIOD_OVERFLOW_ISR                               \
                                    (HRCAP_CALIBRATION_DONE |                  \
                                     HRCAP_GLOBAL_CALIBRATION_INTERRUPT |      \
                                     HRCAP_CALIBRATION_PERIOD_OVERFLOW)

#define HRCALCAL_CALIBRATION_FLAGS  (HRCAP_CALIBRATION_DONE |                  \
                                     HRCAP_CALIBRATION_PERIOD_OVERFLOW)

#define HRCAPCAL_OVERFLOW           4294967295.0f
#define HRCAPCAL_INV_OVERFLOW       (float32_t)(1.0f / HRCAPCAL_OVERFLOW)

//
// Typedefs
//
typedef struct
{
    uint32_t hrclkCount;    // High resolution clock count
    uint32_t sysclkcount;   // System clock count
    float32_t scaleFactor;  // Scale factor
    bool calDone;           // Calibration done flag
} HRCAPCAL_CalResultObj;
