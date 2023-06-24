//#############################################################################
//
// FILE:   eqep_ex2_calculation.h
//
// TITLE:  Position and Speed Measurement Using eQEP (Calculations)
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

#ifndef EQEP_EX2_CALCULATION_H
#define EQEP_EX2_CALCULATION_H

//
// Included Files
//
#include "IQmathLib.h"
#include "driverlib.h"

//
// Typedefs
//
typedef struct {
    int16_t thetaElec;      // Output: Motor electrical angle (Q15)
    int16_t thetaMech;      // Output: Motor mechanical angle (Q15)
    int16_t directionQEP;   // Output: Motor rotation direction (Q0)
    int16_t thetaRaw;       // Variable: Raw angle from timer 2 (Q0)
    int16_t mechScaler;     // Parameter: 0.9999 / total count,
                            //            total count = 4000 (Q26)
    int16_t polePairs;      // Parameter: Number of pole pairs (Q0)
    int16_t calAngle;       // Parameter: Raw angular offset between encoder
                            //            and Phase A (Q0)

    uint32_t speedScaler;   // Parameter: Scaler converting 1/N cycles to a
                            //            GLOBAL_Q speed (Q0) - independently
                            //            with global Q
    _iq speedPR;            // Output: Speed in per-unit
    uint32_t baseRPM;       // Parameter: Scaler converting GLOBAL_Q speed to
                            //            rpm (Q0) speed - independently with
                            //            global Q
    int16_t speedRPMPR;     // Output: Speed in rpm (Q0) - independently with
                            //         global Q

    _iq oldPos;
    _iq speedFR;            // Output: Speed in per-unit
    int16_t speedRPMFR;     // Output: Speed in rpm (Q0) - independently with
                            //         global Q
} PosSpeed_Object;

typedef PosSpeed_Object *PosSpeed_Handle;

//
// Function Prototypes
//
void PosSpeed_calculate(PosSpeed_Handle);

#endif  // EQEP_EX2_CALCULATION_H

