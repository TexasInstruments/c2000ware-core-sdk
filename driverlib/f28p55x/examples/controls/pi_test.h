//#############################################################################
//
// FILE:   pi_test.h
//
// TITLE:  DCL PI controller with sysconfig demonstration
//
// This header file contains defines, variables and prototypes that used in this example
//
//#############################################################################
// 
// C2000Ware v5.05.00.00
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
 
#ifndef PI_TEST_H
#define PI_TEST_H

#ifdef __cplusplus
extern "C" {
#endif

#include "c2000ware_libraries.h"
#include "stdint.h"
#include "math.h"
#include "stdio.h"

int PI_test(void);

//
//  User configurable values
//
#define DATA_LENGTH     800  //!< Size of total data inputs
#define NUM_ELEMENTS    400   //!< The number of samples ran, cannot exceed DATA_LENGTH
#define EPSILON         0.00001f

//
// declared & initialized by sysconfig
//
extern DCL_PI myController0;
extern float32_t outLogArr[DATA_LENGTH];

//
// Allocate data sections and initialize data
//
#pragma DATA_SECTION(rkLogArr, "LoggerDataSection")
float32_t rkLogArr[DATA_LENGTH] =
{
#include "data/PI_rk-1.dat"
};

#pragma DATA_SECTION(ykLogArr, "LoggerDataSection")
float32_t ykLogArr[DATA_LENGTH] =
{
#include "data/PI_yk-1.dat"
};

#pragma DATA_SECTION(ctlLogArr, "LoggerDataSection")
float32_t ctlLogArr[DATA_LENGTH] =
{
#include "data/PI_ctl-1.dat"
};



#ifdef __cplusplus
}
#endif // extern "C"

#endif
