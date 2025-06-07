//###########################################################################
//
// FILE:   hw_types.h
//
// TITLE:  Type definitions used in driverlib functions.
//
//###########################################################################
// $Copyright:
// Copyright (C) 2025 Texas Instruments Incorporated - http://www.ti.com/
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
//###########################################################################

#ifndef HW_TYPES_H
#define HW_TYPES_H

//*****************************************************************************
//
// Macros for hardware access
//
//*****************************************************************************
#if defined(__TMS320C28XX_CLA__)
    #define HWREG(x)                                                          \
            (*((volatile uint32_t *)((uintptr_t)(x))))
    #define HWREGH(x)                                                         \
            (*((volatile uint16_t *)((uintptr_t)(x))))
#else
    #define HWREG(x)                                                          \
            (*((volatile uint32_t *)(x)))
    #define HWREGH(x)                                                         \
            (*((volatile uint16_t *)(x)))
#endif

#define HWREG_BP(x)                                                           \
        __byte_peripheral_32((uint32_t *)(x))
#define HWREGB(x)                                                             \
        __byte((int16_t *)(x),0)

//*****************************************************************************
//
// SUCCESS and FAILURE for API return value
//
//*****************************************************************************
#define STATUS_S_SUCCESS    (0)
#define STATUS_E_FAILURE    (-1)

//*****************************************************************************
//
// Definition of 8 bit types for USB Driver code to maintain portability
// between byte and word addressable cores of C2000 Devices.
//
//*****************************************************************************
typedef uint16_t uint8_t;
typedef int16_t int8_t;

//****************************************************************************
//
// For checking NULL pointers
//
//****************************************************************************
#ifndef NULL
#define NULL ((void *)0x0)
#endif

//*****************************************************************************
//
// 32-bit and 64-bit float type
//
//*****************************************************************************
#ifndef C2000_IEEE754_TYPES
#define C2000_IEEE754_TYPES
#ifdef __TI_EABI__
typedef float         float32_t;
typedef double        float64_t;
#else // TI COFF
typedef float         float32_t;
typedef long double   float64_t;
#endif // __TI_EABI__
#endif // C2000_IEEE754_TYPES

//*****************************************************************************
//
// Extern compiler intrinsic prototypes. See compiler User's Guide for details.
// These are provided to satisfy static analysis tools. The #ifndef is required
// because the '&' is for a C++-style reference, and although it is the correct
// prototype, it will not build in C code.
//
//*****************************************************************************
#if(defined(__TMS320C28XX__) || defined(__TMS320C28XX_CLA__))
#else
extern int16_t &__byte(int16_t *array, uint16_t byte_index);
extern uint32_t &__byte_peripheral_32(uint32_t *x);
#endif

//
// C++ Bool Compatibility
//
#if defined(__cplusplus)
typedef bool _Bool;
#endif

/* To fix Misra-C errors */
#ifndef TRUE
#define TRUE  1
#endif
#ifndef FALSE
#define FALSE  0
#endif

#endif // HW_TYPES_H
