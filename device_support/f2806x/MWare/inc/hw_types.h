//###########################################################################
//
// FILE:   hw_types.h
//
// TITLE:  Type definitions used in ALL driverlib functions.
//
//###########################################################################
// $TI Release: $
// $Release Date: $
// $Copyright:
// Copyright (C) 2009-2024 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef __HW_TYPES_H__
#define __HW_TYPES_H__

#include <stdint.h>

//
// Define a boolean type, and values for true and false.
//
typedef unsigned char tBoolean;

#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif

typedef uint16_t uint8_t;
typedef int16_t int8_t;

//
// Macros for hardware access, both direct and via the bit-band region.
//
#define HWREG(x)                                                              \
        (*((volatile unsigned long *)(x)))
#define HWREGH(x)                                                             \
        (*((volatile unsigned short *)(x)))
#define HWREGB(x)                                                            \
        __byte((int *)(x),0)
//        
// Emulated Bitbanded write
//
#define HWREGBITW(address, mask, value)                                       \
        (*(volatile unsigned long *)(address)) =                              \
       ((*(volatile unsigned long *)(address)) & ~((unsigned long)1 << mask)) \
       | ((unsigned long)value << mask)

//
// Emulated Bitbanded read
//
#define HWREGBITR(address, mask)                                              \
        (((*(volatile unsigned long *)(address)) & ((unsigned long)1 << mask))\
           >> mask)        

//        
// Emulated Bitbanded write
//
#define HWREGBITHW(address, mask, value)                                       \
        (*(volatile unsigned short *)(address)) =                              \
       ((*(volatile unsigned short *)(address)) & ~((unsigned short)1 << mask)) \
       | ((unsigned short)value << mask)

//       
// Emulated Bitbanded read
//
#define HWREGBITHR(address, mask)                                             \
        (((*(volatile unsigned short *)(address)) &                           \
        ((unsigned short)1 << mask)) >> mask)


#endif // __HW_TYPES_H__

//
// End of File
//

