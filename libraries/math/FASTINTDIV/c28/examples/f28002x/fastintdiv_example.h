//#############################################################################
//
//! \file   fastintdiv_example.h
//!
//! \brief  Header file for fast integer division example
//! \date   Feb 14, 2019
//
//  Group:          C2000
//  Target Device:  TMS320f28002x
//
// The header file defines various types of user-defined data types used for
// storing input data passed to various forms of division tests
//
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2022 Texas Instruments Incorporated - http://www.ti.com
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


#ifndef FASTINTDIV_EXAMPLE_H_
#define FASTINTDIV_EXAMPLE_H_

#include <stdint.h>


typedef struct {
int16_t dividend; int16_t divisor; int32_t quotient; int32_t remainder;
} parameters_div_i16byi16;

typedef struct {
uint16_t dividend; uint16_t divisor; uint32_t quotient; uint32_t remainder;
} parameters_div_u16byu16;

typedef struct {
int32_t dividend; int32_t divisor; int32_t quotient; int32_t remainder;
} parameters_div_i32byi32;

typedef struct {
int32_t dividend; uint32_t divisor; int32_t quotient; int32_t remainder;
} parameters_div_i32byu32;

typedef struct {
uint32_t dividend; uint32_t divisor; uint32_t quotient; uint32_t remainder;
} parameters_div_u32byu32;

typedef struct {
int32_t dividend; int16_t divisor; int32_t quotient; int32_t remainder;
} parameters_div_i32byi16;

typedef struct {
uint32_t dividend; uint16_t divisor; uint32_t quotient; uint32_t remainder;
} parameters_div_u32byu16;

typedef struct {
int64_t dividend; int64_t divisor; int64_t quotient; int64_t remainder;
} parameters_div_i64byi64;

typedef struct {
int64_t dividend; uint64_t divisor; int64_t quotient; int64_t remainder;
} parameters_div_i64byu64;

typedef struct {
uint64_t dividend; uint64_t divisor; uint64_t quotient; uint64_t remainder;
} parameters_div_u64byu64;

#endif /* FASTINTDIV_EXAMPLE_H_ */
