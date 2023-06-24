//*****************************************************************************
//
// hw_types.h - Common types and macros.
//
// Copyright (c) 2005-2016 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
//   Redistribution and use in source and binary forms, with or without
//   modification, are permitted provided that the following conditions
//   are met:
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
// 
// This is part of revision 2.1.3.156 of the Tiva Firmware Development Package.
//
//*****************************************************************************

#ifndef __HW_TYPES_H__
#define __HW_TYPES_H__

//*****************************************************************************
//
// Macros for hardware access, both direct and via the bit-band region.
//
//*****************************************************************************
#define HWREG(x)                                                              \
        (*((volatile uint32_t *)(x)))
#define HWREGH(x)                                                             \
        (*((volatile uint16_t *)(x)))
#define HWREGB(x)                                                             \
        (*((volatile uint8_t *)(x)))
#define HWREGBITW(x, b)                                                       \
        HWREG(((uint32_t)(x) & 0xF0000000) | 0x02000000 |                     \
              (((uint32_t)(x) & 0x000FFFFF) << 5) | ((b) << 2))
#define HWREGBITH(x, b)                                                       \
        HWREGH(((uint32_t)(x) & 0xF0000000) | 0x02000000 |                    \
               (((uint32_t)(x) & 0x000FFFFF) << 5) | ((b) << 2))
#define HWREGBITB(x, b)                                                       \
        HWREGB(((uint32_t)(x) & 0xF0000000) | 0x02000000 |                    \
               (((uint32_t)(x) & 0x000FFFFF) << 5) | ((b) << 2))

//
// The HWREG_BP Define uses __byte_peripheral_32 intrinsic which can be
// used to access a 32-bit byte peripherals data address, preventing the
// accesses from being broken up. The intrinsic returns a reference to an 
// unsigned long and can be used both to read and write data. This is 
// applicable for the C28x Driver and is not applicable for CM Driver. Thus
// the define HWREG_BP has been mapped to HWREG.
//
#define HWREG_BP(x)                                                           \
        HWREG(x)

//****************************************************************************
//
// For checking NULL pointers
//
//****************************************************************************
#ifndef NULL
#define NULL ((void *)0x0)
#endif

#endif // __HW_TYPES_H__
