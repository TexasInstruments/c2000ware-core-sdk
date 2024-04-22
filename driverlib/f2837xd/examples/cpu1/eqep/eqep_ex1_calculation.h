//#############################################################################
//
// FILE:   eqep_ex1_calculation.h
//
// TITLE:  Frequency Measurement Using eQEP (Calculations)
//
//#############################################################################
//
// 
// $Copyright:
// Copyright (C) 2013-2024 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef EQEP_EX1_CALCULATION_H
#define EQEP_EX1_CALCULATION_H

//
// Included Files
//
#include "IQmathLib.h"
#include "driverlib.h"

//
// Typedefs
//
typedef struct
{
    uint32_t freqScalerPR;  // Parameter: Scaler converting 1/N cycles to a
                            // GLOBAL_Q freq (Q0) - independently with global Q
    uint32_t freqScalerFR;  // Parameter: Scaler converting 1/N cycles to a
                            // GLOBAL_Q freq (Q0) - independently with global Q
    uint32_t baseFreq;      // Parameter: Maximum freq

    _iq freqPR;             // Output: Freq in per-unit using capture unit
    int32_t freqHzPR;       // Output: Freq in Hz, measured using Capture unit
    uint32_t oldPos;

    _iq freqFR;             // Output: Freq in per-unit using position counter
    int32_t freqHzFR;       // Output: Freq in Hz, measured using Capture unit
    bool task_complete_FR,task_complete_PR; // Output : calculation is done.
    int16_t FR_calc_count,PR_calc_count; // Output : calculation is done.
} FreqCal_Object;

typedef FreqCal_Object *FreqCal_Handle;

//
// Function Prototypes
//
void FreqCal_calculate(FreqCal_Handle);

#endif  // EQEP_EX1_CALCULATION_H

//
// End of File
//

