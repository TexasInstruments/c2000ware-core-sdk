//#############################################################################
//
// FILE:   Std_Types.h
//
// TITLE:  Standard type definitions for C28x
//
//#############################################################################
//
// C2000Ware
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
//   documentation and/or other materials provided with the distribution.
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

#ifndef STD_TYPES_H
#define STD_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/* ========================================================================== */
/*                 Integer Types                                               */
/* ========================================================================== */

typedef unsigned char   uint8; 
typedef unsigned short  uint16;
typedef unsigned long   uint32;
typedef signed char     sint8; 
typedef signed short    sint16;
typedef signed long     sint32;

/* ========================================================================== */
/*                 Boolean Type                                                */
/* ========================================================================== */

typedef unsigned char   boolean;

#ifndef TRUE
#define TRUE  ((boolean)1U)
#endif

#ifndef FALSE
#define FALSE ((boolean)0U)
#endif

/* ========================================================================== */
/*                 Standard Macros                                             */
/* ========================================================================== */

#ifndef NULL_PTR
#define NULL_PTR ((void*)0)
#endif

#define STD_ON  0x01U
#define STD_OFF 0x00U

#ifdef __cplusplus
}
#endif

#endif /* STD_TYPES_H */
