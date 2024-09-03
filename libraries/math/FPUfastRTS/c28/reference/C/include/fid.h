#ifndef _FID_H_
#define _FID_H_
//#############################################################################
//! \file   reference/C/include/$FILENAME$
//! \brief  Fast RTS Header File
//! \author Vishal Coelho (Static Inline Code adapted from original by 
//!         Prasanth V)
//! \date   19-Aug-2015
//! 
//
//  Group:            C2000
//  Txet Family:    $DEVICE$
//
//#############################################################################
//
//
// 
// C2000Ware v5.03.00.00
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

#define CONCAT(x,y)          x##y
#define XCONCAT(x,y)         CONCAT(x,y)
#define STRINGIZE(s)         #s
#define XSTRINGIZE(s)        STRINGIZE(s)

//*****************************************************************************
// the includes
//*****************************************************************************
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <float.h>

//!
//! \defgroup C_REF_MOD C Reference Module

//! 
//! \ingroup C_REF_MOD
//@{
    
#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
// defines
//*****************************************************************************
// If using FID pick ONE of the divisions you are testing
#if USE_FID == 1 
#define UI32BYUI32  0
#define I32BYI32    0
#define I32BYUI32   0
#define UI64BYUI32  0
#define I64BYI32    0
#define I64BYUI32   0
#define UI64BYUI64  0
#define I64BYI64    0
#define I64BYUI64   0
#define UI16BYUI16  0
#define I16BYI16    0
#define UI32BYUI16  0
#define I32BYI16    0
#define F64BYF64    1
#endif // USE_FID

// If using FID pick ONE of the signed division types
#define SIGNED_DIV_TRUNCATED    (1)
#define SIGNED_DIV_MODULO       (0)
#define SIGNED_DIV_EUCLIDEAN    (0)

#if SIGNED_DIV_TRUNCATED == 1
#define FID_i32byi32    FID_i32byi32_t
#define FID_i64byi32    FID_i64byi32_t
#define FID_i64byi64    FID_i64byi64_t
#define FID_i16byi16    FID_i16byi16_t
#define FID_i32byi16    FID_i32byi16_t
#elif SIGNED_DIV_MODULO == 1
#define FID_i32byi32    FID_i32byi32_m
#define FID_i64byi32    FID_i64byi32_m
#define FID_i64byi64    FID_i64byi64_m
#define FID_i16byi16    FID_i16byi16_m
#define FID_i32byi16    FID_i32byi16_m
#elif SIGNED_DIV_EUCLIDEAN == 1
#define FID_i32byi32    FID_i32byi32_e
#define FID_i64byi32    FID_i64byi32_e
#define FID_i64byi64    FID_i64byi64_e
#define FID_i16byi16    FID_i16byi16_e
#define FID_i32byi16    FID_i32byi16_e
#else
#error "Pick one of the signed division methods: truncated, modulo or \
euclidean"
#endif //SIGNED_DIV_TRUNCATED

#define max(a,b) \
({ __typeof__(a) _a = (a); \
   __typeof__(b) _b = (b); \
   _a > _b ? _a : _b;})

//*****************************************************************************
// typedefs
//*****************************************************************************
//! Flags used by the integer division operations
//!
typedef struct _FID_flags_t_{
    uint16_t TF     : 1;    // Bit 0 : Test Flag
    uint16_t NI     : 1;    // Bit 1 : Negative Integer
    uint16_t ZI     : 1;    // Bit 2 : Zero Integer
    uint16_t RNDF64 : 1;    // Bit 3 : Round to Nearest(to even on ties)
    uint16_t rsvd   : 12;   // Bits 4 - 15: Reserved
}FID_flags_t;

//! Register type (32-bit)
//! 
typedef union _reg32_t_{
    int32_t     i32;
    uint32_t    ui32;
    float       f32;
}reg32_t;
        
//! Register type (64-bit)
//! 
typedef union _reg64_t_{
    int64_t     i64;
    uint64_t    ui64;
    double      f64;
    struct{
        reg32_t L;
        reg32_t H;
    };
}reg64_t;

//*****************************************************************************
//globals
//*****************************************************************************
FID_flags_t status_flag;

reg64_t R0, R1, R2, R3, R4, R5, R6, R7;

//*****************************************************************************
// 'inline' functions
//*****************************************************************************
//! \brief Emulate the ABSI64DIV64 instruction in the FID
//! \param R3_p pointer to register R3 (holds the denominator)
//! \param R1_p pointer to register R1 (holds the numerator)
//! \param R2_p pointer to register R2 (used in a future operation)
//! \param p_status_flag , pointer to FID status flags
//!
static inline void ABSI64DIV64 (reg64_t *R3_p, reg64_t *R1_p, reg64_t *R2_p, 
                            FID_flags_t *p_status_flag)
{
    // TF = sign(num) ^ sign(den)
    p_status_flag->TF = (((R3_p->ui64 & (1UL << 63)) ^ 
                          (R1_p->ui64 & (1UL << 63))) >> 63);
    // NI = sign(num)
    p_status_flag->NI = (R1_p->ui64 & (1UL << 63)) >> 63;
    
    // num = |num| and den = |den|
    // NOTE: treat the registers as unsigned int 64 before right shifiting
    // so that it does not sign extend from the left
    if(((R3_p->ui64 >> 63) & 1UL) == 1UL)
    {
        R3_p->i64 = -(R3_p->i64);
    }
    if(((R1_p->ui64 >> 63) & 1UL) == 1UL)
    {
        R1_p->i64 = -(R1_p->i64);
    }
    // zero out R2
    R2_p->i64 = 0L;
}

//! \brief Emulate the ABSI64DIV64U instruction in the FID
//! \param R3_p pointer to register R3 (holds the denominator)
//! \param R1_p pointer to register R1 (holds the numerator)
//! \param R2_p pointer to register R2 (used in a future operation)
//! \param p_status_flag , pointer to FID status flags
//!
static inline void ABSI64DIV64U (reg64_t *R3_p, reg64_t *R1_p, reg64_t *R2_p, 
                            FID_flags_t *p_status_flag)
{
    // TF = sign(num)
    p_status_flag->TF = (R1_p->ui64 & (1UL << 63)) >> 63;
    // NI = sign(num)
    p_status_flag->NI = (R1_p->ui64 & (1UL << 63)) >> 63;
    
    // num = |num|
    // NOTE: treat the registers as unsigned int 64 before right shifiting
    // so that it does not sign extend from the left
    if(((R1_p->ui64 >> 63) & 1UL) == 1UL)
    {
        R1_p->i64 = -(R1_p->i64);
    }
    // zero out R2
    R2_p->i64 = 0L;
}

//! \brief Emulate the ABSI64DIV32 instruction in the FID
//! \param R3_p pointer to register R3 (holds the denominator)
//! \param R1_p pointer to register R1 (holds the numerator)
//! \param R2_p pointer to register R2 (used in a future operation)
//! \param p_status_flag , pointer to FID status flags
//!
static inline void ABSI64DIV32 (reg32_t *R3_p, reg64_t *R1_p, reg32_t *R2_p, 
                            FID_flags_t *p_status_flag)
{
    // TF = sign(num) ^ sign(den)
    p_status_flag->TF = (((R3_p->ui32 & (1UL << 31)) >> 31) ^ 
                         ((R1_p->ui64 & (1UL << 63)) >> 63));
    // NI = sign(num)
    p_status_flag->NI = (R1_p->ui64 & (1UL << 63)) >> 63;
    
    // num = |num| and den = |den|
    // NOTE: treat the registers as unsigned int 64/32 before right shifiting
    // so that it does not sign extend from the left
    if(((R3_p->ui32 >> 31) & 1U) == 1U)
    {
        R3_p->i32 = -(R3_p->i32);
    }
    if(((R1_p->ui64 >> 63) & 1UL) == 1UL)
    {
        R1_p->i64 = -(R1_p->i64);
    }
    // zero out R2
    R2_p->i32 = 0;
}

//! \brief Emulate the ABSI64DIV32U instruction in the FID
//! \param R3_p pointer to register R3 (holds the denominator)
//! \param R1_p pointer to register R1 (holds the numerator)
//! \param R2_p pointer to register R2 (used in a future operation)
//! \param p_status_flag , pointer to FID status flags
//!
static inline void ABSI64DIV32U (reg32_t *R3_p, reg64_t *R1_p, reg32_t *R2_p, 
                            FID_flags_t *p_status_flag)
{
    // TF = sign(num)
    p_status_flag->TF = (R1_p->ui64 & (1UL << 63)) >> 63;
    // NI = sign(num)
    p_status_flag->NI = (R1_p->ui64 & (1UL << 63)) >> 63;
    
    // num = |num|
    // NOTE: treat the registers as unsigned int 64/32 before right shifiting
    // so that it does not sign extend from the left
    if(((R1_p->ui64 >> 63) & 1UL) == 1UL)
    {
        R1_p->i64 = -(R1_p->i64);
    }
    // zero out R2
    R2_p->i32 = 0;
}

//! \brief Emulate the ABSI32DIV32 instruction in the FID
//! \param R3_p pointer to register R3 (holds the denominator)
//! \param R1_p pointer to register R1 (holds the numerator)
//! \param R2_p pointer to register R2 (used in a future operation)
//! \param p_status_flag , pointer to FID status flags
//!
static inline void ABSI32DIV32 (reg32_t *R3_p, reg32_t *R1_p, reg32_t *R2_p, 
                            FID_flags_t *p_status_flag)
{
    // TF = sign(num) ^ sign(den)
    p_status_flag->TF = (((R3_p->ui32 & (1UL << 31)) ^ 
                          (R1_p->ui32 & (1UL << 31))) >> 31);
    // NI = sign(num)
    p_status_flag->NI = (R1_p->ui32 & (1UL << 31)) >> 31;
    
    // num = |num| and den = |den|
    // NOTE: treat the registers as unsigned int 64/32 before right shifiting
    // so that it does not sign extend from the left
    if(((R3_p->ui32 >> 31) & 1U) == 1U)
    {
        R3_p->i32 = -(R3_p->i32);
    }
    if(((R1_p->ui32 >> 31) & 1U) == 1U)
    {
        R1_p->i32 = -(R1_p->i32);
    }
    // zero out R2
    R2_p->i32 = 0;
}

//! \brief Emulate the ABSI32DIV32U instruction in the FID
//! \param R3_p pointer to register R3 (holds the denominator)
//! \param R1_p pointer to register R1 (holds the numerator)
//! \param R2_p pointer to register R2 (used in a future operation)
//! \param p_status_flag , pointer to FID status flags
//!
static inline void ABSI32DIV32U (reg32_t *R3_p, reg32_t *R1_p, reg32_t *R2_p, 
                            FID_flags_t *p_status_flag)
{
    // TF = sign(num)
    p_status_flag->TF = (R1_p->ui32 & (1UL << 31)) >> 31;
    // NI = sign(num)
    p_status_flag->NI = (R1_p->ui32 & (1UL << 31)) >> 31;
    
    // num = |num|
    // NOTE: treat the registers as unsigned int 64/32 before right shifiting
    // so that it does not sign extend from the left
    if(((R1_p->ui32 >> 31) & 1U) == 1U)
    {
        R1_p->i32 = -(R1_p->i32);
    }
    // zero out R2
    R2_p->i32 = 0;
}


//! \brief Emulate the SUBC2UI64 instruction in the FID
//! \param R3_p pointer to register R3 (holds the denominator)
//! \param R1_p pointer to register R1 (holds the numerator/quotient)
//! \param R2_p pointer to register R2 (holds the remainder)
//! \param p_status_flag , pointer to FID status flags
//!
//! \note target must support 128-bit wide integer mode for gcc __uint128_t
//! and __int128_t extensions to work
//! 
static inline void SUBC2UI64 (reg64_t *R3_p, reg64_t *R1_p, reg64_t *R2_p,
                    FID_flags_t *p_status_flag)
{
    int16_t i;
    __int128_t temp;
    
    status_flag.ZI = 0;
    
    for(i = 1; i <= 2; i++)
    {
        // temp = (rem << 1) + MSb(num) - den
        temp = ((__uint128_t)((R2_p->ui64) << 1) + 
                (__uint128_t)((R1_p->ui64 & (1UL << 63)) >> 63)) -
                (__uint128_t)R3_p->ui64;
    #ifdef _DEBUG
        printf("R3 (den) = %#llx, R1 (num/quo) = %#llx, R2 (rem) = %#llx,"
               " temp = %#llx\n", 
               R3_p->ui64, R1_p->ui64, R2_p->ui64, temp); 
    #endif //_DEBUG
        // if((rem << 1) + MSb(num)) >= den 
        //     rem = temp.ui64;
        //     num = (num << 1) + 1 -- the 1 is increment of the quotient
        // else
        //     rem = (rem << 1) + MSb(num)
        //     num = num << 1
        if(temp >= 0LL)
        {
            R2_p->ui64 = (temp & 0xFFFFFFFFFFFFFFFFUL);
            R1_p->ui64 = (R1_p->ui64 << 1) + 1;
            
        }
        else
        {
            R2_p->ui64 = ((R2_p->ui64 << 1) + 
                          ((R1_p->ui64 & (1UL << 63)) >> 63));
            R1_p->ui64 = (R1_p->ui64 << 1);
        }
              
    }
    // if(rem == 0), flag.ZI = 1
    if(R2_p->ui64 == 0UL)
    {
        p_status_flag->ZI = 1;
    }
    #ifdef _DEBUG
        printf("AFTER 2: R3 (den) = %#llx, R1 (num/quo) = %#llx, "
               "R2 (rem) = %#llx, temp = %#llx\n", 
               R3_p->ui64, R1_p->ui64, R2_p->ui64, temp); 
    #endif //_DEBUG
}


//! \brief Emulate the SUBC4UI32 instruction in the FID
//! \param R3_p pointer to register R3 (holds the denominator)
//! \param R1_p pointer to register R1 (holds the numerator/quotient)
//! \param R2_p pointer to register R2 (holds the remainder)
//! \param p_status_flag , pointer to FID status flags
//!
static inline void SUBC4UI32 (reg32_t *R3_p, reg32_t *R1_p, reg32_t *R2_p,
                    FID_flags_t *p_status_flag)
{
    int16_t i;
    int64_t temp;
    
    status_flag.ZI = 0;
    
    for(i = 1; i <= 4; i++)
    {
        // temp = (rem << 1) + MSb(num) - den
        //<<VC160407: need 33 bits when you left shift the remainder especially
        // if the divisor occupies the full unsigend 32-bit range
        // temp = ((R2_p->ui32) << 1) + ((R1_p->ui32 & 0x80000000UL) >> 31) -
        //          R3_p->ui32;
        temp = ((uint64_t)R2_p->ui32 << 1) + 
               (((uint64_t)R1_p->ui32 & 0x80000000UL) >> 31) -
               (uint64_t)R3_p->ui32;
        //  VC160407>>
    #ifdef _DEBUG
        printf("R3(den) = %#llx, R1(num/quo) = %#llx, R2(rem) = %#llx,"
               " temp = %#llx\n", 
               R3_p->ui32, R1_p->ui32, R2_p->ui32, temp); 
    #endif //_DEBUG
    
        // if((rem << 1) + MSb(num)) >= den 
        //     rem = temp.ui32;
        //     num = (num << 1) + 1 -- the 1 is increment of the quotient
        // else
        //     rem = (rem << 1) + MSb(num)
        //     num = num << 1
        if(temp >= 0L)
        {
            R2_p->ui32 = (temp & 0xFFFFFFFFUL);
            R1_p->ui32 = (R1_p->ui32 << 1) + 1;
            
        }
        else
        {
            R2_p->ui32 = ((R2_p->ui32 << 1) + 
                          ((R1_p->ui32 & 0x80000000UL) >> 31));
            R1_p->ui32 = (R1_p->ui32 << 1);
        }
              
    }
    
    // if(rem == 0), flag.ZI = 1
    if(R2_p->ui32 == 0U)
    {
        p_status_flag->ZI = 1;
    }
    #ifdef _DEBUG
        printf("AFTER 4: R3(den) = %#llx, R1(num/quo) = %#llx, "
               "R2(rem) = %#llx, temp = %#llx\n", 
               R3_p->ui32, R1_p->ui32, R2_p->ui32, temp); 
    #endif //_DEBUG
}

//! \brief Swaps the high and low double words (32-bit) - emulate SWAPI64
//! \param R_p pointer to register Rn (n = 0 to 7)
//!
static inline void SWAPI64 (reg64_t *R_p)
{
   uint64_t temp = R_p->ui64;
   R_p->ui64 = (((temp & 0x00000000FFFFFFFFUL) << 32) + 
                ((temp & 0xFFFFFFFF00000000UL) >> 32)); 
    #ifdef _DEBUG
        printf("Swap, before: %#20lx, after = %#20lx\n", 
               temp, R_p->ui64); 
    #endif //_DEBUG
}

//! \brief Emulate the NEGI32DIV32 instruction
//! \param R1_p pointer to register R1 (holds the quotient)
//! \param R2_p pointer to register R2 (holds the remainder)
//! \param p_status_flag , pointer to FID status flags
//!
static inline void NEGI32DIV32 (reg32_t *R1_p, reg32_t *R2_p, 
                   FID_flags_t *p_status_flag)
{
   if(p_status_flag->TF == 0x1)
   {
       R1_p->i32 = -(R1_p->i32);
   }
   if(p_status_flag->NI == 0x1)
   {
       R2_p->i32 = -(R2_p->i32);
   }
}

//! \brief Emulate the ENEGI32DIV32 instruction
//! \param R3_p pointer to register R3 (holds the denominator)
//! \param R1_p pointer to register R1 (holds the quotient)
//! \param R2_p pointer to register R2 (holds the remainder)
//! \param p_status_flag , pointer to FID status flags
//!
static inline void ENEGI32DIV32 (reg32_t *R3_p, reg32_t *R1_p, reg32_t *R2_p, 
                   FID_flags_t *p_status_flag)
{
   // For Euclidean Division we always keep a positive remainder
   //  -N/D   =  D x (-Q1) + R1
   //   N/-D  = -D x (-Q2) + R2
   // where |Q1|<|Q2|, R1<R2, Q1,Q2 < 0 for the same N and D
   // e.g. -3/4 will set NI=1 and TF=1 and do 3/4 to give Q=0, R=3
   // which must be adjusted to Q=1, R=4-3=1
   // then Q=-Q because TF==1 so we end up with Q=-1, R=1 for -3/4
   // 3/-4 will set NI=0 but TF=0 and do 3/4 to give Q=0, R=3
   // which is then adjusted to Q=1, R=4-3=1 
   //  
   // TF and NI follow the sign of the numerator
   // if((num < 0) &&  (rem != 0)) quo += 1, rem = den - rem   
   if((p_status_flag->NI == 1) && (p_status_flag->ZI == 0))
   {
       R1_p->i32 = R1_p->i32 + 1;
       R2_p->i32 = R3_p->i32 - R2_p->i32;
   }
   // if (num < 0) , quo = -quo
   if(p_status_flag->TF == 0x1)
   {
       R1_p->i32 = -(R1_p->i32);
   }
}

//! \brief Emulate the MNEGI32DIV32 instruction
//! \param R3_p pointer to register R3 (holds the denominator)
//! \param R1_p pointer to register R1 (holds the quotient)
//! \param R2_p pointer to register R2 (holds the remainder)
//! \param p_status_flag , pointer to FID status flags
//!
static inline void MNEGI32DIV32 (reg32_t *R3_p, reg32_t *R1_p, reg32_t *R2_p, 
                   FID_flags_t *p_status_flag)
{
   
   // For Floored Division remainder follows the sign of the denominator
   //  -N/D   =  D x (-Q1) +  R1
   //   N/-D  = -D x (-Q2) + -R2
   // where |Q1|<|Q2|, R1<R2, Q1,Q2 < 0 for the same N and D
   // e.g. -3/4 will set NI=1 and TF=1 and do 3/4 to give Q=0, R=3
   // which must be adjusted to Q=1, R=4-3=1
   // then Q=-Q because TF==1 so we end up with Q=-1, R=1 for -3/4
   // 3/-4 will set NI=0 and TF=1 and do 3/4 to give Q=0, R=3
   // which is then adjusted to Q=1, R=4-3=1 
   // Since TF==1, Q=-Q and since (NI=0 ^ TF=1 == 1) R=-R
   // we get Q=-1, R=-1
   // NI = sign(num)
   // TF = sign(num) ^ sign(den)
   
   // if((sign(num)^sign(den)) && (rem != 0)) quo += 1, rem = den - rem   
   if((p_status_flag->TF == 1) && (p_status_flag->ZI == 0))
   {
       R1_p->i32 = R1_p->i32 + 1;
       R2_p->i32 = R3_p->i32 - R2_p->i32;
   }
   // if(sign(num)^sign(den)) quo = -quo
   if(p_status_flag->TF == 0x1)
   {
       R1_p->i32 = -(R1_p->i32);
   }
   
   // if(sig(num) ^ (sign(num)^sign(den))) rem = -rem
   // -- if num < 0, den < 0 (-3/-4) or num > 0 den <0 (3/-4)
   if((p_status_flag->NI ^ p_status_flag->TF) == 1)
   {
       R2_p->i32 = -(R2_p->i32);
   }
}

//! \brief Emulate the NEGI64DIV32 instruction
//! \param R1_p pointer to register R1 (holds the quotient)
//! \param R2_p pointer to register R2 (holds the remainder)
//! \param p_status_flag , pointer to FID status flags
//!
static inline void NEGI64DIV32 (reg64_t *R1_p, reg32_t *R2_p, 
                   FID_flags_t *p_status_flag)
{
   if(p_status_flag->TF == 0x1)
   {
       R1_p->i64 = -(R1_p->i64);
   }
   if(p_status_flag->NI == 0x1)
   {
       R2_p->i32 = -(R2_p->i32);
   }
}

//! \brief Emulate the ENEGI64DIV32 instruction
//! \param R3_p pointer to register R3 (holds the denominator)
//! \param R1_p pointer to register R1 (holds the quotient)
//! \param R2_p pointer to register R2 (holds the remainder)
//! \param p_status_flag , pointer to FID status flags
//!
static inline void ENEGI64DIV32 (reg32_t *R3_p, reg64_t *R1_p, reg32_t *R2_p, 
                   FID_flags_t *p_status_flag)
{
   // For Euclidean Division we always keep a positive remainder
   //  -N/D   =  D x (-Q1) + R1
   //   N/-D  = -D x (-Q2) + R2
   // where |Q1|<|Q2|, R1<R2, Q1,Q2 < 0 for the same N and D
   // e.g. -3/4 will set NI=1 and TF=1 and do 3/4 to give Q=0, R=3
   // which must be adjusted to Q=1, R=4-3=1
   // then Q=-Q because TF==1 so we end up with Q=-1, R=1 for -3/4
   // 3/-4 will set NI=0 but TF=0 and do 3/4 to give Q=0, R=3
   // which is then adjusted to Q=1, R=4-3=1 
   //  
   // TF and NI follow the sign of the numerator
   // if((num < 0) &&  (rem != 0)) quo += 1, rem = den - rem   
   if((p_status_flag->NI == 1) && (p_status_flag->ZI == 0))
   {
       R1_p->i64 = R1_p->i64 + 1L;
       R2_p->i32 = R3_p->i32 - R2_p->i32;
   }
   // if (num < 0) , quo = -quo
   if(p_status_flag->TF == 0x1)
   {
       R1_p->i64 = -(R1_p->i64);
   }
}


//! \brief Emulate the MNEGI64DIV32 instruction
//! \param R3_p pointer to register R3 (holds the denominator)
//! \param R1_p pointer to register R1 (holds the quotient)
//! \param R2_p pointer to register R2 (holds the remainder)
//! \param p_status_flag , pointer to FID status flags
//!
static inline void MNEGI64DIV32 (reg32_t *R3_p, reg64_t *R1_p, reg32_t *R2_p, 
                   FID_flags_t *p_status_flag)
{
   
   // For Floored Division remainder follows the sign of the denominator
   //  -N/D   =  D x (-Q1) +  R1
   //   N/-D  = -D x (-Q2) + -R2
   // where |Q1|<|Q2|, R1<R2, Q1,Q2 < 0 for the same N and D
   // e.g. -3/4 will set NI=1 and TF=1 and do 3/4 to give Q=0, R=3
   // which must be adjusted to Q=1, R=4-3=1
   // then Q=-Q because TF==1 so we end up with Q=-1, R=1 for -3/4
   // 3/-4 will set NI=0 and TF=1 and do 3/4 to give Q=0, R=3
   // which is then adjusted to Q=1, R=4-3=1 
   // Since TF==1, Q=-Q and since (NI=0 ^ TF=1 == 1) R=-R
   // we get Q=-1, R=-1
   // NI = sign(num)
   // TF = sign(num) ^ sign(den)
   
   // if((sign(num)^sign(den)) && (rem != 0)) quo += 1, rem = den - rem   
   if((p_status_flag->TF == 1) && (p_status_flag->ZI == 0))
   {
       R1_p->i64 = R1_p->i64 + 1L;
       R2_p->i32 = R3_p->i32 - R2_p->i32;
   }
   // if(sign(num)^sign(den)) quo = -quo
   if(p_status_flag->TF == 0x1)
   {
       R1_p->i64 = -(R1_p->i64);
   }
   
   // if(sig(num) ^ (sign(num)^sign(den))) rem = -rem
   // -- if num < 0, den < 0 (-3/-4) or num > 0 den <0 (3/-4)
   if((p_status_flag->NI ^ p_status_flag->TF) == 1)
   {
       R2_p->i32 = -(R2_p->i32);
   }
}

//! \brief Emulate the NEGI64DIV64 instruction
//! \param R1_p pointer to register R1 (holds the quotient)
//! \param R2_p pointer to register R2 (holds the remainder)
//! \param p_status_flag , pointer to FID status flags
//!
static inline void NEGI64DIV64 (reg64_t *R1_p, reg64_t *R2_p, 
                   FID_flags_t *p_status_flag)
{
   if(p_status_flag->TF == 0x1)
   {
       R1_p->i64 = -(R1_p->i64);
   }
   if(p_status_flag->NI == 0x1)
   {
       R2_p->i64 = -(R2_p->i64);
   }
}

//! \brief Emulate the ENEGI64DIV64 instruction
//! \param R3_p pointer to register R3 (holds the denominator)
//! \param R1_p pointer to register R1 (holds the quotient)
//! \param R2_p pointer to register R2 (holds the remainder)
//! \param p_status_flag , pointer to FID status flags
//!
static inline void ENEGI64DIV64 (reg64_t *R3_p, reg64_t *R1_p, reg64_t *R2_p, 
                   FID_flags_t *p_status_flag)
{
   // For Euclidean Division we always keep a positive remainder
   //  -N/D   =  D x (-Q1) + R1
   //   N/-D  = -D x (-Q2) + R2
   // where |Q1|<|Q2|, R1<R2, Q1,Q2 < 0 for the same N and D
   // e.g. -3/4 will set NI=1 and TF=1 and do 3/4 to give Q=0, R=3
   // which must be adjusted to Q=1, R=4-3=1
   // then Q=-Q because TF==1 so we end up with Q=-1, R=1 for -3/4
   // 3/-4 will set NI=0 but TF=0 and do 3/4 to give Q=0, R=3
   // which is then adjusted to Q=1, R=4-3=1 
   //  
   // TF and NI follow the sign of the numerator
   // if((num < 0) &&  (rem != 0)) quo += 1, rem = den - rem   
   if((p_status_flag->NI == 1) && (p_status_flag->ZI == 0))
   {
       R1_p->i64 = R1_p->i64 + 1L;
       R2_p->i64 = R3_p->i64 - R2_p->i64;
   }
   // if (num < 0) , quo = -quo
   if(p_status_flag->TF == 0x1)
   {
       R1_p->i64 = -(R1_p->i64);
   }
}


//! \brief Emulate the MNEGI64DIV64 instruction
//! \param R3_p pointer to register R3 (holds the denominator)
//! \param R1_p pointer to register R1 (holds the quotient)
//! \param R2_p pointer to register R2 (holds the remainder)
//! \param p_status_flag , pointer to FID status flags
//!
static inline void MNEGI64DIV64 (reg64_t *R3_p, reg64_t *R1_p, reg64_t *R2_p, 
                   FID_flags_t *p_status_flag)
{
   
   // For Floored Division remainder follows the sign of the denominator
   //  -N/D   =  D x (-Q1) +  R1
   //   N/-D  = -D x (-Q2) + -R2
   // where |Q1|<|Q2|, R1<R2, Q1,Q2 < 0 for the same N and D
   // e.g. -3/4 will set NI=1 and TF=1 and do 3/4 to give Q=0, R=3
   // which must be adjusted to Q=1, R=4-3=1
   // then Q=-Q because TF==1 so we end up with Q=-1, R=1 for -3/4
   // 3/-4 will set NI=0 and TF=1 and do 3/4 to give Q=0, R=3
   // which is then adjusted to Q=1, R=4-3=1 
   // Since TF==1, Q=-Q and since (NI=0 ^ TF=1 == 1) R=-R
   // we get Q=-1, R=-1
   // NI = sign(num)
   // TF = sign(num) ^ sign(den)
   
   // if((sign(num)^sign(den)) && (rem != 0)) quo += 1, rem = den - rem   
   if((p_status_flag->TF == 1) && (p_status_flag->ZI == 0))
   {
       R1_p->i64 = R1_p->i64 + 1L;
       R2_p->i64 = R3_p->i64 - R2_p->i64;
   }
   // if(sign(num)^sign(den)) quo = -quo
   if(p_status_flag->TF == 0x1)
   {
       R1_p->i64 = -(R1_p->i64);
   }
   
   // if(sig(num) ^ (sign(num)^sign(den))) rem = -rem
   // -- if num < 0, den < 0 (-3/-4) or num > 0 den <0 (3/-4)
   if((p_status_flag->NI ^ p_status_flag->TF) == 1)
   {
       R2_p->i64 = -(R2_p->i64);
   }
}

//! \brief Zero out a register - emulate ZERO
//! \param R_p pointer to register Rn (n = 0 to 7)
//!
static inline void ZERO (reg64_t *R_p)
{
   R_p->ui64 = 0UL;
}

//! \brief Pre division (double precision) operation
//! \param R0_p pointer to register R0 (holds the unbiased exponent)
//! \param R2_p pointer to register R2 (holds the numerator)
//! \param R1_p pointer to register R1 (holds the quotient)
//! \param R3_p pointer to register R3 (holds the denominator)
//! \param p_status_flag , pointer to FID status
//!
static inline void PREDIVF64(reg32_t *R0_p, reg64_t *R2_p, reg64_t *R1_p, 
             reg64_t *R3_p, FID_flags_t *p_status_flag)
{
    // Set the quotient to zero
    ZERO(&R1);
    
    // flag.TF = sign(num)^sign(den)
    p_status_flag->TF = ((R2_p->ui64 & (1UL << 63)) ^ 
                         (R3_p->ui64 & (1UL << 63)) >> 63);
    
    // R0.H = exp(num) - exp(den) - bias
    R0_p->i32 = (((R2_p->ui64 & (0x7FF0000000000000UL)) >> 52) - 
                 ((R3_p->ui64 & (0x7FF0000000000000UL)) >> 52) + 
                   1023);
                     
    // Set the exponent field to 1 and interpret the resultant value 
    // as 1.M * 2^52 before proceeding with the recursive conditional 
    // subtraction
    R2_p->ui64 = ((R2_p->ui64 & 0x000FFFFFFFFFFFFFUL) | (1UL << 52));
    R3_p->ui64 = ((R3_p->ui64 & 0x000FFFFFFFFFFFFFUL) | (1UL << 52));
    
    // den = 1.M * 2^53
    R3_p->ui64 <<= 1;
    
    #ifdef _DEBUG
    printf("PREDIV: EXP: %d, NUM = %#20lx, DEN = %#20lx \n",
       R0_p->i32, R2_p->ui64, R3_p->ui64);
    #endif // _DEBUG
}

//! \brief Post division (double precision) operation
//! \param R1_p pointer to register R1 (holds the quotient)
//! \param R0_p pointer to register R0 (holds the unbiased exponent)
//! \param p_status_flag , pointer to FID status
//!
static inline void POSTDIVF64(reg64_t *R1_p, reg32_t *R0_p, 
                     FID_flags_t *p_status_flag)
{
    // Since we perform the SUBC operation (part of SUBC3F64) 19*3 = 57 times
    // instead of the requisite 55 times, we end up with two extra shifts in 
    // the quotient which we undo here to give 55 significant bits
    R1_p->ui64 = R1_p->ui64 >> 2;
    #ifdef _DEBUG
    printf("POSTDIV: First adjustment: QUO = %#20lx (%f)\n", 
                   R1_p->ui64, R1_p->f64);
    #endif // _DEBUG
    // Perform blind rounding if the rounding flag is set
    if(p_status_flag->RNDF64 == 1)
    {
        // The quotient is as follows
        //   55   53  .............  3   2    1   0   
        // +----+----+-------------+---+---+----+----+
        // |Q.52|Q.51|             |Q.1|Q.0|Q.-1|Q.-2|
        // +----+----+-------------+---+---+----+----+
        //  MSb                         LSb  G    S
        //                                   |    |
        //                                   v    v  
        //                                 guard  sticky
        //
        // G - guard bit is the bit exactly to the right of the LSb, its 
        //     value is exactly 1/2 LSb. Its the midpoint between representable
        //     numbers
        // S - sticky bit is the OR'ing of all bits to the right of the guard
        //     bit. In the example, there is only one bit but there could be 
        //     many. There reason we OR these bits to give S is we just want to
        //     know if the value is above the midpoint (S=1) or at the 
        //     mid-point (S=0) - we dont care about the bits that make up the 
        //     sticky bit just whether it pushes the G+S over the midpoint or 
        //     not. If S = 0 an G = 1 we are half way between representable
        //     numbers and a decision to round up/down is made based on whether
        //     the LSb is 0 (even) or 1 (odd)
        // 
        // Bit 2 is the least significant bit in the mantissa of the 
        // quotient, we basically add a half LSB (1/2 * 4 = 2) to this value 
        // and drop the last two bits -- this is a blind rounding
        //
        // Normally we would check to see if the value [Q.-1:Q.-2] was > 2 
        // then [Q.51:Q.0] would round up (i.e. add 1), if [Q.-1:Q.-2] < 2
        // we round down (i.e. just drop the last two bits). But if [Q.-1:Q.-2]
        // was 2, i.e. exactly 1/2 LSB we have a tie, and we must round to the 
        // nearest even number - we would have to check Q.0: 
        //    if Q.0 is 0 (even) we round down, i.e. just truncate
        //    if Q.0 is 1 (odd) we round up and add 1 to [Q.51:Q.0]
        // Blind rounding matches the hardware implementation
        //
        R1_p->ui64 = R1_p->ui64 + 2UL;
    }
    
    // Drop the last two bits to give 53 significant bits
    R1_p->ui64 = R1_p->ui64 >> 2;
    #ifdef _DEBUG
    printf("POSTDIV: Drop G,S: QUO = %#20lx (%f)\n", R1_p->ui64, R1_p->f64);
    #endif // _DEBUG
    
    // Insert the sign bit
    R1_p->ui64 = R1_p->ui64 | ((uint64_t)p_status_flag->TF << 63);
    
    // Insert the exponent by first  checking if the bit in the 53rd position 
    // is 1 (the implicit 1); if it isnt we need to subtract 1 from the 
    // exponent, shift up the mantissa 1 before masking off the bit in the 
    // 53rd position (bit 52)and re-inserting the exponent
    if(((R1_p->ui64 & (1UL << 52)) >> 52) == 0)
    {
        R0_p->ui32 = R0_p->ui32 - 1;
        R1_p->ui64 = R1_p->ui64 << 1;
        
    }
    R1_p->ui64 = R1_p->ui64 & ~(0x7FFUL << 52);
    R1_p->ui64 = R1_p->ui64 | ((uint64_t)(R0_p->ui32 & 0x7FF) << 52);
    
    #ifdef _DEBUG
    printf("POSTDIV: QUO = %#20lx (%f)\n", R1_p->ui64, R1_p->f64);
    #endif // _DEBUG
}   

//! \brief Emulate the SUBC4UI32 instruction in the FID
//! \param R2_p pointer to register R2 (holds the numerator)
//! \param R1_p pointer to register R1 (holds the quotient)
//! \param R3_p pointer to register R3 (holds the denominator)
//! \param p_status_flag , pointer to FID status flags
//!
static inline void SUBC3F64 (reg64_t *R2_p, reg64_t *R1_p, reg64_t *R3_p,
                    FID_flags_t *p_status_flag)
{
    int16_t i;
    int64_t temp;
    
    for(i = 1; i <= 3; i++)
    {
        // temp = (num << 1) - den
        temp = (R2_p->i64 << 1) - R3_p->i64;
    #ifdef _DEBUG
        printf("R3 (den) = %#20lx, R1 (quo) = %#20lx, R2 (num) = %#20lx,"
               " temp = %#20lx\n", 
               R3_p->ui64, R1_p->ui64, R2_p->ui64, temp); 
    #endif //_DEBUG
        // if (num << 1) >= den 
        //     num = temp(53:0);
        //     quo = (quo << 1) + 1
        // else
        //     quo = quo << 1
        //     num = num << 1 + quo(63)
        if(temp >= 0L)
        {
            R2_p->ui64 = (temp  & 0x003FFFFFFFFFFFFFUL);
            R1_p->ui64 = (R1_p->ui64 << 1) + 1;
            
        }
        else
        {
            R2_p->ui64 = ((R2_p->ui64 << 1) + 
                          ((R1_p->ui64 & (1UL << 63)) >> 63)) & 
                          0x003FFFFFFFFFFFFFUL;
            R1_p->ui64 = (R1_p->ui64 << 1);
        }
              
    }
    #ifdef _DEBUG
        printf("AFTER 3: R3 (den) = %#20lx, R1 (quo) = %#20lx, "
               "R2 (num) = %#20lx, temp = %#20lx\n", 
               R3_p->ui64, R1_p->ui64, R2_p->ui64, temp); 
    #endif //_DEBUG
}

//*****************************************************************************
// 'extern' function prototypes
//*****************************************************************************
//! \brief Division: ui32/ui32
//! \param[in] num , numerator (ui32)
//! \param[in] den , denominator (ui32)
//! \param[out] p_quo , pointer to the quotient
//! \param[out] p_rem  , pointer to the remainder
//! \return none
extern void FID_ui32byui32(const uint32_t num, const uint32_t den, 
                           uint32_t *p_quo, uint32_t *p_rem);
                           
//! \brief Division: i32/i32 (Truncated)
//! \param[in] num , numerator (i32)
//! \param[in] den , denominator (i32)
//! \param[out] p_quo , pointer to the quotient
//! \param[out] p_rem  , pointer to the remainder
//! \return none
extern void FID_i32byi32_t(const int32_t num, const int32_t den, 
                           int32_t *p_quo, int32_t *p_rem);

//! \brief Division: i32/i32 (Floored or Modulo)
//! \param[in] num , numerator (i32)
//! \param[in] den , denominator (i32)
//! \param[out] p_quo , pointer to the quotient
//! \param[out] p_rem  , pointer to the remainder
//! \return none
extern void FID_i32byi32_m(const int32_t num, const int32_t den, 
                           int32_t *p_quo, int32_t *p_rem);

//! \brief Division: i32/i32 (Euclidean)
//! \param[in] num , numerator (i32)
//! \param[in] den , denominator (i32)
//! \param[out] p_quo , pointer to the quotient
//! \param[out] p_rem  , pointer to the remainder
//! \return none
extern void FID_i32byi32_e(const int32_t num, const int32_t den, 
                           int32_t *p_quo, int32_t *p_rem);

//! \brief Division: i32/ui32 (Truncated)
//! \param[in] num , numerator (i32)
//! \param[in] den , denominator (ui32)
//! \param[out] p_quo , pointer to the quotient
//! \param[out] p_rem  , pointer to the remainder
//! \return none
extern void FID_i32byui32(const int32_t num, const uint32_t den, 
                           int32_t *p_quo, int32_t *p_rem);
                           
//! \brief Division: ui64/ui32
//! \param[in] num , numerator (ui64)
//! \param[in] den , denominator (ui32)
//! \param[out] p_quo , pointer to the quotient
//! \param[out] p_rem  , pointer to the remainder
//! \return none
extern void FID_ui64byui32(const uint64_t num, const uint32_t den, 
                           uint64_t *p_quo, uint32_t *p_rem);
                           
//! \brief Division: i64/i32 (Truncated)
//! \param[in] num , numerator (i64)
//! \param[in] den , denominator (i32)
//! \param[out] p_quo , pointer to the quotient
//! \param[out] p_rem  , pointer to the remainder
//! \return none
extern void FID_i64byi32_t(const int64_t num, const int32_t den, 
                       int64_t *p_quo, int32_t *p_rem);

//! \brief Division: i64/i32 (Floored or Modulo)
//! \param[in] num , numerator (i64)
//! \param[in] den , denominator (i32)
//! \param[out] p_quo , pointer to the quotient
//! \param[out] p_rem  , pointer to the remainder
//! \return none
extern void FID_i64byi32_m(const int64_t num, const int32_t den, 
                       int64_t *p_quo, int32_t *p_rem);

//! \brief Division: i64/i32 (Euclidean)
//! \param[in] num , numerator (i64)
//! \param[in] den , denominator (i32)
//! \param[out] p_quo , pointer to the quotient
//! \param[out] p_rem  , pointer to the remainder
//! \return none
extern void FID_i64byi32_e(const int64_t num, const int32_t den, 
                       int64_t *p_quo, int32_t *p_rem);

//! \brief Division: i64/ui32 (Truncated)
//! \param[in] num , numerator (i64)
//! \param[in] den , denominator (ui32)
//! \param[out] p_quo , pointer to the quotient
//! \param[out] p_rem  , pointer to the remainder
//! \return none
//! \note the remainder can be at most 33-bits (signed) and is therefore
//! sign extended to fit a signed 64-bit standard integer type
//!
extern void FID_i64byui32(const int64_t num, const uint32_t den, 
                           int64_t *p_quo, int64_t *p_rem);
                           
//! \brief Division: ui64/ui64
//! \param[in] num , numerator (ui64)
//! \param[in] den , denominator (ui64)
//! \param[out] p_quo , pointer to the quotient
//! \param[out] p_rem  , pointer to the remainder
//! \return none
extern void FID_ui64byui64(const uint64_t num, const uint64_t den, 
                           uint64_t *p_quo, uint64_t *p_rem);
                           
//! \brief Division: i64/i64 (Truncated)
//! \param[in] num , numerator (i64)
//! \param[in] den , denominator (i64)
//! \param[out] p_quo , pointer to the quotient
//! \param[out] p_rem  , pointer to the remainder
//! \return none
extern void FID_i64byi64_t(const int64_t num, const int64_t den, 
                           int64_t *p_quo, int64_t *p_rem);

//! \brief Division: i64/i64 (Floored or Modulo)
//! \param[in] num , numerator (i64)
//! \param[in] den , denominator (i64)
//! \param[out] p_quo , pointer to the quotient
//! \param[out] p_rem  , pointer to the remainder
//! \return none
extern void FID_i64byi64_m(const int64_t num, const int64_t den, 
                           int64_t *p_quo, int64_t *p_rem);

//! \brief Division: i64/i64 (Euclidean)
//! \param[in] num , numerator (i64)
//! \param[in] den , denominator (i64)
//! \param[out] p_quo , pointer to the quotient
//! \param[out] p_rem  , pointer to the remainder
//! \return none
extern void FID_i64byi64_e(const int64_t num, const int64_t den, 
                           int64_t *p_quo, int64_t *p_rem);
                           
//! \brief Division: i64/ui64 (Truncated)
//! \param[in] num , numerator (i64)
//! \param[in] den , denominator (ui64)
//! \param[out] p_quo , pointer to the quotient
//! \param[out] p_rem  , pointer to the remainder
//! \return none
//!
extern void FID_i64byui64(const int64_t num, const uint64_t den, 
                           int64_t *p_quo, int64_t *p_rem);
                           
//! \brief Division: ui16/ui16
//! \param[in] num , numerator (ui16)
//! \param[in] den , denominator (ui16)
//! \param[out] p_quo , pointer to the quotient
//! \param[out] p_rem  , pointer to the remainder
//! \return none
extern void FID_ui16byui16(const uint16_t num, const uint16_t den, 
                           uint16_t *p_quo, uint16_t *p_rem);
                           
//! \brief Division: i16/i16 (Truncated)
//! \param[in] num , numerator (i16)
//! \param[in] den , denominator (i16)
//! \param[out] p_quo , pointer to the quotient
//! \param[out] p_rem  , pointer to the remainder
//! \return none
extern void FID_i16byi16_t(const int16_t num, const int16_t den, 
                           int16_t *p_quo, int16_t *p_rem);

//! \brief Division: i16/i16 (Floored or Modulo)
//! \param[in] num , numerator (i16)
//! \param[in] den , denominator (i16)
//! \param[out] p_quo , pointer to the quotient
//! \param[out] p_rem  , pointer to the remainder
//! \return none
extern void FID_i16byi16_m(const int16_t num, const int16_t den, 
                           int16_t *p_quo, int16_t *p_rem);

//! \brief Division: i16/i16 (Euclidean)
//! \param[in] num , numerator (i16)
//! \param[in] den , denominator (i16)
//! \param[out] p_quo , pointer to the quotient
//! \param[out] p_rem  , pointer to the remainder
//! \return none
extern void FID_i16byi16_e(const int16_t num, const int16_t den, 
                           int16_t *p_quo, int16_t *p_rem);
                           
//! \brief Division: ui32/ui16
//! \param[in] num , numerator (ui32)
//! \param[in] den , denominator (ui16)
//! \param[out] p_quo , pointer to the quotient
//! \param[out] p_rem  , pointer to the remainder
//! \return none
extern void FID_ui32byui16(const uint32_t num, const uint16_t den, 
                           uint32_t *p_quo, uint16_t *p_rem);
                           
//! \brief Division: i32/i16 (Truncated)
//! \param[in] num , numerator (i32)
//! \param[in] den , denominator (i16)
//! \param[out] p_quo , pointer to the quotient
//! \param[out] p_rem  , pointer to the remainder
//! \return none
extern void FID_i32byi16_t(const int32_t num, const int16_t den, 
                           int32_t *p_quo, int16_t *p_rem);

//! \brief Division: i32/i16 (Floored or Modulo)
//! \param[in] num , numerator (i32)
//! \param[in] den , denominator (i16)
//! \param[out] p_quo , pointer to the quotient
//! \param[out] p_rem  , pointer to the remainder
//! \return none
extern void FID_i32byi16_m(const int32_t num, const int16_t den, 
                           int32_t *p_quo, int16_t *p_rem);

//! \brief Division: i32/i16 (Euclidean)
//! \param[in] num , numerator (i32)
//! \param[in] den , denominator (i16)
//! \param[out] p_quo , pointer to the quotient
//! \param[out] p_rem  , pointer to the remainder
//! \return none
extern void FID_i32byi16_e(const int32_t num, const int16_t den, 
                           int32_t *p_quo, int16_t *p_rem);
                           
//! \brief Division: f64/f64
//! \param[in] num , numerator (f64)
//! \param[in] den , denominator (f64)
//! \param[out] p_quo , pointer to the quotient
//! \return none
extern void FID_f64byf64(const double num, const double den, 
                           double *p_quo);
#ifdef __cplusplus
}
#endif //extern "C"

//@} //ingroup

#endif // end of _FID_H_ definition
