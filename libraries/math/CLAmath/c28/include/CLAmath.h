//#############################################################################
//
// FILE: CLAmath.h
//
// DESCRIPTION: CLA Math Library Prototypes
//
//#############################################################################
//!
//! Copyright: Copyright (C) 2023 Texas Instruments Incorporated -
//!	All rights reserved not granted herein.
//!	Limited License.
//!
//! Texas Instruments Incorporated grants a world-wide, royalty-free,
//! non-exclusive license under copyrights and patents it now or hereafter
//! owns or controls to make, have made, use, import, offer to sell and sell
//! ("Utilize") this software subject to the terms herein. With respect to the
//! foregoing patent license, such license is granted solely to the extent that
//! any such patent is necessary to Utilize the software alone. The patent
//! license shall not apply to any combinations which include this software,
//! other than combinations with devices manufactured by or for TI 
//! ("TI Devices").
//! No hardware patent is licensed hereunder.
//!
//! Redistributions must preserve existing copyright notices and reproduce this
//! license (including the above copyright notice and the disclaimer and
//! (if applicable) source code license limitations below) in the documentation
//!  and/or other materials provided with the distribution.
//!
//! Redistribution and use in binary form, without modification, are permitted
//! provided that the following conditions are met:
//!
//! * No reverse engineering, decompilation, or disassembly of this software is 
//! permitted with respect to any software provided in binary form.
//! * Any redistribution and use are licensed by TI for use only 
//!   with TI Devices.
//! * Nothing shall obligate TI to provide you with source code for the 
//!   software licensed and provided to you in object code.
//!
//! If software source code is provided to you, modification and redistribution
//! of the source code are permitted provided that the following conditions 
//! are met:
//!
//! * any redistribution and use of the source code, including any resulting
//!   derivative works, are licensed by TI for use only with TI Devices.
//! * any redistribution and use of any object code compiled from the source
//!   code and any resulting derivative works, are licensed by TI for use 
//!   only with TI Devices.
//!
//! Neither the name of Texas Instruments Incorporated nor the names of its
//! suppliers may be used to endorse or promote products derived from this 
//! software without specific prior written permission.
//#############################################################################

#ifndef __CLAMATH_H__
#define __CLAMATH_H__

//#############################################################################
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//#############################################################################
#ifdef __cplusplus
extern "C"
{
#endif
//#############################################################################
//
// Includes
//
//#############################################################################
#include <stdint.h>

//#############################################################################
//
// Macro Definitions
//
//#############################################################################
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

//
// The below redefinitions of functions, or function mappings is due to the
// fact that the CLA compiler tools do not support <math.h>. Therefore, the
// CLA math library with these below redefinitions help to cross-compile code
// for the CLA which uses standard C functions.
//
#ifdef __TMS320C28XX_CLA__

//
// The below are the redefinitions of functions, or function mappings for the
// type 2 CLA. The functions are mapped to the inline version of the CLA math
// library because the background task does not support function calls.
//
#ifdef __TMS320C28XX_CLA2__
//
// math.h Functions for CLA2
//
#define acosf              CLAacos_inline
#define asinf              CLAasin_inline
#define atanf              CLAatan_inline
#define atan2f             CLAatan2_inline
#define cosf               CLAcos_inline
#define expf               CLAexp_inline
#define logf               CLAln_inline
#define log10f             CLAlog10_inline
#define sinf               CLAsin_inline
#define sqrtf              CLAsqrt_inline
#define tanf(m)            (CLAsin_inline(m)/CLAcos_inline(m))

//
// TMU Intrinsics for CLA2
//
#define __divf32           CLAdiv_inline
#define __sqrt             CLAsqrt_inline
#define __sin              CLAsin_inline
#define __cos              CLAcos_inline
#define __atan             CLAatan_inline
#define __atan2            CLAatan2_inline
#define __sinpuf32         CLAsinPU_inline
#define __cospuf32         CLAcosPU_inline

#else
//
// math.h Functions for CLA
//
#define acosf              CLAacos
#define asinf              CLAasin
#define atanf              CLAatan
#define atan2f             CLAatan2
#define cosf               CLAcos
#define expf               CLAexp
#define logf               CLAln
#define log10f             CLAlog10
#define sinf               CLAsin
#define sqrtf              CLAsqrt
#define tanf(m)            (CLAsin(m)/CLAcos(m))

//
// TMU Intrinsics for CLA
//
#define __divf32           CLAdiv
#define __sqrt             CLAsqrt
#define __sin              CLAsin
#define __cos              CLAcos
#define __atan             CLAatan
#define __atan2            CLAatan2
#define __sinpuf32         CLAsinPU
#define __cospuf32         CLAcosPU

#endif

//
// math.h Functions
//
#define fmaxf              __mmaxf32
#define fminf              __mminf32

//
// General CPU Intrinsics
//
#define __eallow           __meallow
#define __edis             __medis

//
// FPU Intrinsics
//
#define __einvf32          __meinvf32
#define __eisqrtf32        __meisqrtf32
#define __f32toi16r        __mf32toi16r
#define __f32toui16r       __mf32toui16r
#define __fmax             __mmaxf32
#define __fmin             __mminf32
#define __fracf32          __mfracf32
#define __swapf            __mswapf
#define __swapff           __mswapf
#endif

//#############################################################################
//
// Structures, variables and typedefs.
//
//#############################################################################

//CLAsincosTable Variables
extern float32_t CLAsincosTable[];
extern float32_t CLAsinTable[];
extern float32_t *CLAsincosTable_Sin0;
extern float32_t CLAcosTable[];
extern float32_t *CLAsincosTable_Cos0;
extern float32_t *CLAsinTableEnd;
extern float32_t *CLAcosTableEnd;
extern float32_t *CLAsincosTableEnd;
extern float32_t CLAsincosTable_TABLE_SIZE;
extern float32_t CLAsincosTable_TABLE_SIZEDivTwoPi;
extern float32_t CLAsincosTable_TwoPiDivTABLE_SIZE;
extern float32_t CLAsincosTable_TABLE_MASK;
extern float32_t CLAsincosTable_Coef0;
extern float32_t CLAsincosTable_Coef1;
extern float32_t CLAsincosTable_Coef1_pos;
extern float32_t CLAsincosTable_Coef2;
extern float32_t CLAsincosTable_Coef3;
extern float32_t CLAsincosTable_Coef3_neg;

//CLAatanTable Variables
extern float32_t CLAatan2HalfPITable[];
extern float32_t CLAatan2Table[];
extern float32_t *CLAatan2TableEnd;
extern float32_t *CLAINV2PI;

//CLAacosineTable Variables
extern float32_t CLAacosinHalfPITable[];
extern float32_t CLAacosinTable[];
extern float32_t *CLAacosinTableEnd;

//CLAasineTable Variables
extern float32_t CLAasinHalfPITable[];
extern float32_t CLAasinTable[];
extern float32_t *CLAasinTableEnd;

//CLAexpTable Variables
extern float32_t CLAINV1,CLAINV2,CLAINV3,CLAINV4;
extern float32_t CLAINV5,CLAINV6,CLAINV7,CLALOG10;
extern float32_t CLAExpTable[];
extern float32_t *CLAExpTableEnd;

//CLAlnTable Variables
extern float32_t CLALNV2,CLALNVe,CLALNV10,CLABIAS;
extern long CLALN_TABLE_MASK1,CLALN_TABLE_MASK2;
extern float32_t CLALnTable[];
extern float32_t *CLALnTableEnd;

//Linker Defined variables
extern uint16_t  _cla_scratchpad_start;
extern uint16_t  _cla_scratchpad_end;

//#############################################################################
//
// Function Prototypes
//
//#############################################################################
extern float32_t CLAacos( float32_t fVal );
extern float32_t CLAacos_spc( float32_t fVal );
extern float32_t CLAasin( float32_t fVal );
extern float32_t CLAatan( float32_t fVal );
extern float32_t CLAatan2( float32_t fVal1, float32_t fVal2 );
extern float32_t CLAatan2PU( float32_t fVal1, float32_t fVal2 );
extern float32_t CLAcos( float32_t fAngleRad);
extern float32_t CLAcosPU( float32_t fAngleRadPU );
extern float32_t CLAdiv( float32_t fNum, float32_t fDen);
extern float32_t CLAexp( float32_t fVal);
extern float32_t CLAexp10( float32_t fVal);
extern float32_t CLAexp2( float32_t fNum, float32_t fDen );
extern float32_t CLAisqrt( float32_t fVal );
extern float32_t CLAln( float32_t fVal);
extern float32_t CLAlog10( float32_t fVal);
extern float32_t CLAsin( float32_t fAngleRad );
extern float32_t CLAsinPU( float32_t fAngleRadPU);
extern float32_t CLAsqrt( float32_t fVal);
extern void CLAsincos(float32_t fAngleRad, float32_t *y_sin, float32_t *y_cos);
extern float32_t CLAexpN(float32_t fVal, float32_t N);
extern float32_t CLAlogN(float32_t fVal, float32_t N);

//#############################################################################
//
// Inline Functions
//
//#############################################################################
#define CLAMATH_TWOPI_DIV_TABLE_SIZE   0.04908738521234f
#define CLAMATH_LN_2                   0.693147181f
#define CLAMATH_LN_10                  2.302585093f
#define CLAMATH_TABLE_SIZE             64f
#define CLAMATH_TABLE_SIZE_M_1         63.0f
#define CLAMATH_PI                     3.141592653589f
#define CLAMATH_PI_DIV_TWO             1.570796327f

#ifdef __TMS320C28XX_CLA__

//
// CLAdiv_inline( float32_t fNum, float32_t fDen)
//
#pragma FUNC_ALWAYS_INLINE(CLAdiv_inline)
static inline float32_t CLAdiv_inline( float32_t fNum, float32_t fDen )
{
    //Local Variables
    float32_t Ye,Yee;   //Estimated values
    float32_t result;

    Ye = __meinvf32(fDen);

    Yee = Ye*fDen;
    Yee = 2 - Yee;
    Ye = Ye * Yee;

    Yee = Ye*fDen;
    Yee = 2 - Yee;
    Ye = Ye * Yee;

    result = Ye * fNum;

    return(result);
}

//
// CLAacos_inline(float32_t fVal)
//
#pragma FUNC_ALWAYS_INLINE(CLAacos_inline)
static inline float32_t CLAacos_inline(float32_t fVal)
{
    int32_t xTblIdx;    //integer valued Table index
    float32_t A0, A1, A2; //Table coefficients
    float32_t *entry;
    float32_t result;

    xTblIdx = fabsf(fVal) * CLAMATH_TABLE_SIZE_M_1;
    xTblIdx = xTblIdx * 3;
    //Table is ordered as 3 32-bit coefficients, the
    //index points to these triplets, hence the *3*sizeof(float)

    entry = &CLAacosinTable[xTblIdx];
    A0 = *entry++;
    A1 = *entry++;
    A2 = *entry;

    result = A0 + (fabsf(fVal) * (A1 + (A2 * fabsf(fVal))));

    if(fVal < 0.0f)
    {
       result = CLAMATH_PI - result;
    }

    return(result);
}

//
// CLAasin_inline(float32_t fVal)
//
#pragma FUNC_ALWAYS_INLINE(CLAasin_inline)
static inline float32_t CLAasin_inline(float32_t fVal)
{
    int32_t xTblIdx;    //integer valued Table index
    float32_t A0, A1, A2; //Table coefficients
    float32_t *entry;
    float32_t result;
    float32_t temp;
    temp = fabsf(fVal);
    xTblIdx = temp * CLAMATH_TABLE_SIZE_M_1;
    xTblIdx = xTblIdx * 3;
    //Table is ordered as 3 32-bit coefficients, the
    //index points to these triplets, hence the *3*sizeof(float)

    entry = &CLAasinTable[xTblIdx];
    A0 = *entry++;
    A1 = *entry++;
    A2 = *entry;

    result = A0 + (fabsf(fVal) * (A1 + (A2 * fabsf(fVal))));

    if(fVal < 0.0f)
    {
       result = - result;
    }

    return(result);
}

//
// CLAatan_inline(float32_t fVal)
//
#pragma FUNC_ALWAYS_INLINE(CLAatan_inline)
static inline float32_t CLAatan_inline(float32_t fVal)
{
    uint32_t uxTblIdx;    //integer valued Table index
    float32_t ratio;
    float32_t num,den;
    float32_t A0, A1, A2; //Table coefficients
    float32_t *entry;
    float32_t result;

    num = __mminf32(fabsf(fVal), 1.0f);
    den = __mmaxf32(fabsf(fVal), 1.0f);
    ratio = (num/den); //Expected the newton raphson algo for better
                       //accuracy on the divide
    uxTblIdx = ratio * CLAMATH_TABLE_SIZE_M_1;
    uxTblIdx = uxTblIdx * 3;
    //Table is ordered as 3 32-bit coefficients, the
    //index points to these triplets, hence the *3*sizeof(float)

    entry = &CLAatan2Table[uxTblIdx];
    A0 = *entry++;
    A1 = *entry++;
    A2 = *entry;

    result = A0 + ratio * (A1 + A2 * ratio);
    if(fabsf(fVal) > 1.0f)
    {
       result = CLAMATH_PI_DIV_TWO - result;
    }
    if(fVal < 0.0f)
    {
       result = - result;
    }

    return(result);
}

//
// CLAatan2_inline( float32_t fVal1, float32_t fVal2 )
//
#pragma FUNC_ALWAYS_INLINE(CLAatan2_inline)
static inline float32_t CLAatan2_inline( float32_t fVal1, float32_t fVal2 )
{
    uint32_t uxTblIdx;    //integer valued Table index
    float32_t ratio;
    float32_t num,den;
    float32_t A0, A1, A2; //Table coefficients
    float32_t *entry;
    float32_t result;

    num = __mminf32(fabsf(fVal1), fabsf(fVal2));
    den = __mmaxf32(fabsf(fVal1), fabsf(fVal2));

    ratio = CLAdiv_inline(num, den);

    uxTblIdx = ratio * CLAMATH_TABLE_SIZE_M_1;
    uxTblIdx = uxTblIdx * 3;
    //Table is ordered as 3 32-bit coefficients, the
    //index points to these triplets, hence the *3*sizeof(float)

    entry = &CLAatan2Table[uxTblIdx];
    A0 = *entry++;
    A1 = *entry++;
    A2 = *entry;

    result = A0 + ratio * (A1 + A2 * ratio);

    if((fVal1 < 0.0f) && (fVal2 < 0.0f) && (fabsf(fVal1) < fabsf(fVal2)))
    {
        result = result - CLAMATH_PI;
    }
    else if((fVal1 < 0.0f) && (fVal2 < 0.0f) && (fabsf(fVal1) >= fabsf(fVal2)))
    {
        result = -result - CLAMATH_PI_DIV_TWO;
    }
    else if((fVal1 < 0.0f) && (fVal2 > 0.0f) && (fabsf(fVal1) >= fabsf(fVal2)))
    {
        result = result - CLAMATH_PI_DIV_TWO;
    }
    else if((fVal1 < 0.0f) && (fVal2 > 0.0f) && (fabsf(fVal1) < fabsf(fVal2)))
    {
        result = -result;
    }
    else if((fVal1 > 0.0f) && (fVal2 > 0.0f) && (fabsf(fVal1) >= fabsf(fVal2)))
    {
        result = CLAMATH_PI_DIV_TWO - result;
    }
    else if((fVal1 > 0.0f) && (fVal2 < 0.0f) && (fabsf(fVal1) >= fabsf(fVal2)))
    {
        result = result + CLAMATH_PI_DIV_TWO;
    }
    else if((fVal1 > 0.0f) && (fVal2 < 0.0f) && (fabsf(fVal1) < fabsf(fVal2)))
    {
        result = CLAMATH_PI - result;
    }

    return(result);
}

//
// CLAatan2PU_inline( float32_t fVal1, float32_t fVal2 )
//
#pragma FUNC_ALWAYS_INLINE(CLAatan2PU_inline)
static inline float32_t CLAatan2PU_inline( float32_t fVal1, float32_t fVal2)
{
    float32_t result = CLAatan2_inline(fVal1, fVal2)/(2*CLAMATH_PI);

    return(result);
}

//
// CLAcos_inline(float32_t fAngleRad)
//
#pragma FUNC_ALWAYS_INLINE(CLAcos_inline)
static inline float32_t CLAcos_inline(float32_t fAngleRad)
{
    float32_t tblIdx;
    float32_t X;          //Fractional part of tblidx
    float32_t SinK,CosK;
    int16_t index;

    tblIdx = fAngleRad * CLAsincosTable_TABLE_SIZEDivTwoPi;
    index = (((int16_t)tblIdx) & (int16_t)0x007F);

    SinK = CLAsincosTable[index];       //*pTblSin;
    CosK = CLAsincosTable[index+32];    //*pTblCos;

    X = __mfracf32(tblIdx);
    X = X * (float32_t)CLAMATH_TWOPI_DIV_TABLE_SIZE;

    //Using the Taylor series
    return(CosK + X * (-SinK                           \
                + X * (CLAsincosTable_Coef0 * CosK     \
                + X * (CLAsincosTable_Coef1_pos * SinK \
                + X * (CLAsincosTable_Coef2 * CosK     \
                + X * (CLAsincosTable_Coef3_neg * SinK))))));
}

//
// CLAcosPU_inline(float32_t fAngleRadPU)
//
#pragma FUNC_ALWAYS_INLINE(CLAcosPU_inline)
static inline float32_t CLAcosPU_inline(float32_t fAngleRadPU)
{
    float32_t tblIdx;
    float32_t X;            //Fractional part of tblidx
    float32_t SinK, CosK;
    int16_t index;

    tblIdx = fAngleRadPU * 2 * CLAMATH_PI * CLAsincosTable_TABLE_SIZEDivTwoPi;
    index=(((int16_t)tblIdx) & (int16_t)0x007F);

    SinK = CLAsincosTable[index];       //*pTblSin;
    CosK = CLAsincosTable[index+32];    //*pTblCos;

    X = __mfracf32(tblIdx);
    X = X * (float32_t)CLAMATH_TWOPI_DIV_TABLE_SIZE;

    //Using the Taylor series
    return(CosK + X * (-SinK                           \
                + X * (CLAsincosTable_Coef0 * CosK     \
                + X * (CLAsincosTable_Coef1_pos * SinK \
                + X * (CLAsincosTable_Coef2 * CosK     \
                + X * (CLAsincosTable_Coef3_neg * SinK))))));
}

//
// CLAexp_inline(float32_t fVal)
//
#pragma FUNC_ALWAYS_INLINE(CLAexp_inline)
static inline float32_t CLAexp_inline(float32_t fVal)
{
    float32_t X;        //Exponent
    float32_t Xm;       //Residue
    int16_t Idx;        //index into EXP table
    float32_t Ei,Em;    //Exponent(Integer), Exponent(Mantissa)
    float32_t result;

    //Step(1):   Calculate absolute of x
    X = fabsf(fVal);

    //Step(2):   Identify the integer and mantissa of the input
    Idx = (int16_t)X;
    Xm = __mfracf32(X);

    //Step(3):   Obtain the e^integer(x) from the table
    Ei = CLAExpTable[Idx];
    Em = CLAINV1 + Xm*(CLAINV1+Xm*CLAINV2*(CLAINV1+(Xm*CLAINV3) \
                 *(CLAINV1+(Xm*CLAINV4)*(CLAINV1+(Xm*CLAINV5) \
                 *(CLAINV1+(Xm*CLAINV6)*(CLAINV1+Xm*CLAINV7))))));

    result = Ei*Em;

    if(fVal < 0.0f)
    {
        result = 1.0f / result;
    }

    return(result);
}

//
// CLAexp10_inline(float32_t fVal)
//
#pragma FUNC_ALWAYS_INLINE(CLAexp10_inline)
static inline float32_t CLAexp10_inline(float32_t fVal)
{
    float32_t CLALOG10_E = 2.30258509f;
    float32_t X;        //Exponent
    float32_t Xm;       //Residue
    int16_t Idx;        //index into EXP table
    float32_t Ei,Em;    //Exponent(Integer), Exponent(Mantissa)
    float32_t result;

    //Step(1):    Calculate absolute of x/LOG10(e) (or x*LN(10))
    X = fabsf(fVal*CLALOG10_E);

    //Step(2):   Identify the integer and mantissa of the input
    Idx = (int16_t)X;
    Xm = __mfracf32(X);

    //Step(3):   Obtain the e^integer(x) from the table
    Ei = CLAExpTable[Idx];
    Em = CLAINV1 + Xm*(CLAINV1 + Xm*CLAINV2 *(CLAINV1+(Xm*CLAINV3) \
                 *(CLAINV1+(Xm*CLAINV4)*(CLAINV1+(Xm*CLAINV5) \
                 *(CLAINV1+(Xm*CLAINV6)*(CLAINV1+Xm*CLAINV7))))));

    result = Ei*Em;

    if(fVal < 0.0f)
    {
        result = 1.0f / result;
    }

    return(result);
}

//
// CLAexp2_inline(float32_t fNum, float32_t fDen )
//
#pragma FUNC_ALWAYS_INLINE(CLAexp2_inline)
static inline float32_t CLAexp2_inline( float32_t fNum, float32_t fDen)
{
    float32_t X;        //Exponent
    float32_t Y;
    float32_t Xm;       //Residue
    int16_t Idx;        //index into EXP table
    float32_t Ei,Em;    //Exponent(Integer), Exponent(Mantissa)
    float32_t result;

    //Step(1):   Calculate absolute of x=A/B
    Y = fNum/fDen;
    X = fabsf(Y);

    //Step(2):   Identify the integer and mantissa of the input
    Idx = (int16_t)X;
    Xm = __mfracf32(X);

    //Step(3):   Obtain the e^integer(x) from the table
    Ei = CLAExpTable[Idx];
    Em = CLAINV1 + Xm*(CLAINV1+Xm*CLAINV2*(CLAINV1+(Xm*CLAINV3) \
                 *(CLAINV1+(Xm*CLAINV4)*(CLAINV1+(Xm*CLAINV5) \
                 *(CLAINV1+(Xm*CLAINV6)*(CLAINV1+Xm*CLAINV7))))));

    result = Ei*Em;

    if(Y < 0.0f)
    {
        result = 1.0f / result;
    }

    return(result);
}

//
// CLAisqrt_inline(float32_t fVal)
//
#pragma FUNC_ALWAYS_INLINE(CLAisqrt_inline)
static inline float32_t CLAisqrt_inline(float32_t fVal)
{
    float32_t Ye, Yee, Yeee;
    float32_t result;

    Ye = __meisqrtf32(fVal); //Initial estimate of sqrt(fVal)

    if(fVal  == 0.0f)
    {
        Ye = 0.0f;
    }

    Yee = Ye * (1.5f - Ye * Ye * fVal * 0.5f);  //Newton rapshon iteration 1
    Yeee = Yee * (1.5f - Yee * Yee * fVal * 0.5f); //Newton rapshon iteration 2

    result = Yeee;

    return(result);
}

//
// CLAln_inline(float32_t fVal)
//
#pragma FUNC_ALWAYS_INLINE(CLAln_inline)
static inline float32_t CLAln_inline(float32_t fVal)
{
    float32_t Xm,E;
    float32_t A0,A1,A2;
    float32_t result;
    int32_t Idx;
    int32_t tmp;
    union{
        uint32_t mem_i;
        float32_t mem_f;
    }X;

    //Step(1)
    X.mem_f = fVal;

    //Step(2): Identify the exponent of the input, store it float.
    tmp = (X.mem_i >> 23) - 127;
    E = tmp * CLAMATH_LN_2;

    //Step(3):  Identify the mantissa{Xm}.
    X.mem_i = (X.mem_i & 0x3FFFFFFF) | 0x3F800000;
    //Mask the sign and MSB of the exponent
    //Or with  1.0*2^127. This creates a value (S)1.(M)*2^(127-127) or (S)1.M
    //We have isolated mantissa with sign bit (1 is implicit)
    //The above two operations is equivalent to X/2^127
    //or isolating the mantissa

    Xm = __mfracf32(X.mem_f);
    //NOTE:Using the mfrac returns the fractional part
    //of a value not its mantissa

    //Step(3):  Calculate the value of Ln(1+mantissa)by using the
    //           polynomial approx = a0 + Xm*(a1 + Xm*a2)
    Idx = (int32_t)(Xm * 32.0f);
    Idx *= 3; //Table is ordered as 3 32-bit coefficients, the
              //index points to these triplets, hence the *3*sizeof(float32_t)
    A0 = CLALnTable[Idx];
    A1 = CLALnTable[Idx+1];
    A2 = CLALnTable[Idx+2];

    result = A0 + Xm * (A1 + A2 * Xm) + E;

    return(result);
}

//
// CLAlog10_inline(float32_t fVal)
//
#pragma FUNC_ALWAYS_INLINE(CLAlog10_inline)
static inline float32_t CLAlog10_inline(float32_t fVal)
{
    float32_t Xm,E;
    float32_t A0,A1,A2;
    float32_t ln_fVal;
    float32_t result;
    int32_t Idx;
    int32_t tmp;
    union{
        uint32_t mem_i;
        float32_t mem_f;
    }X;

    //Step(1)
    X.mem_f = fVal;

    //Step(2): Identify the exponent of the input, store it float.
    tmp = (X.mem_i >> 23) - 127;
    E = tmp * CLAMATH_LN_2;

    //Step(3):  Identify the mantissa{Xm}.
    X.mem_i = (X.mem_i & 0x3FFFFFFF)| 0x3F800000;
    //Mask the sign and MSB of the exponent
    //Or with  1.0*2^127. This creates a value (S)1.(M)*2^(127-127) or (S)1.M
    //We have isolated mantissa with sign bit (1 is implicit)
    //The above two operations is equivalent to X/2^127
    //or isolating the mantissa

    Xm = __mfracf32(X.mem_f);
    //NOTE:Using the mfrac returns the fractional part
    //of a value not its mantissa

    //Step(3):  Calculate the value of Ln(1+mantissa)by using the
    //           polynomial approx = a0 + Xm*(a1 + Xm*a2)
    Idx = (int32_t)(Xm * 32.0f);
    Idx *= 3; //Table is ordered as 3 32-bit coefficients, the
              //index points to these triplets, hence the *3*sizeof(float32_t)
    A0 = CLALnTable[Idx];
    A1 = CLALnTable[Idx+1];
    A2 = CLALnTable[Idx+2];

    ln_fVal = A0 + Xm * (A1 + A2 * Xm) + E;
    result = ln_fVal / CLAMATH_LN_10;

    return(result);
}

//
// CLAsin_inline(float32_t fAngleRad)
//
#pragma FUNC_ALWAYS_INLINE(CLAsin_inline)
static inline float32_t CLAsin_inline(float32_t fAngleRad)
{
    float32_t tblIdx;     //The floating pt table index
    float32_t X;          //Fractional part of tblidx
    float32_t SinK,CosK;  //Table values sin and cos that are closest to the
                          //user input angle value
    int16_t index;

    tblIdx = fAngleRad * CLAsincosTable_TABLE_SIZEDivTwoPi;
    index= (((int16_t)tblIdx) & (int16_t)0x007F);
    SinK = CLAsincosTable[(int16_t)index];
    CosK = CLAsincosTable[index+32];

    X = __mfracf32(tblIdx);
    X = X * (float32_t)CLAMATH_TWOPI_DIV_TABLE_SIZE;

    //Using the Taylor series
    return(SinK + X * (CosK                        \
                + X * (CLAsincosTable_Coef0 * SinK \
                + X * (CLAsincosTable_Coef1 * CosK \
                + X * (CLAsincosTable_Coef2 * SinK \
                + X * (CLAsincosTable_Coef3 * CosK))))));
}

//
// CLAsinPU_inline(float32_t fAngleRadPU)
//
#pragma FUNC_ALWAYS_INLINE(CLAsinPU_inline)
static inline float32_t CLAsinPU_inline(float32_t fAngleRadPU)
{
    float32_t tblIdx;     //The floating pt table index
    float32_t X;          //Fractional part of tblidx
    float32_t SinK,CosK;  //Table values sin and cos that are closest to the
                          //user input angle value
    int16_t index;

    tblIdx = fAngleRadPU * 2 * CLAMATH_PI * CLAsincosTable_TABLE_SIZEDivTwoPi;
    index= (((int16_t)tblIdx)&(int16_t)0x007F);
    SinK = CLAsincosTable[(int16_t)index];
    CosK = CLAsincosTable[index+32];

    X = __mfracf32(tblIdx);
    X = X * (float32_t)CLAMATH_TWOPI_DIV_TABLE_SIZE;

    //Using the Taylor series
    return(SinK + X * (CosK                        \
                + X * (CLAsincosTable_Coef0 * SinK \
                + X * (CLAsincosTable_Coef1 * CosK \
                + X * (CLAsincosTable_Coef2 * SinK \
                + X * (CLAsincosTable_Coef3 * CosK))))));
}

//
// CLAsqrt_inline(float32_t fVal)
//
#pragma FUNC_ALWAYS_INLINE(CLAsqrt_inline)
static inline float32_t CLAsqrt_inline(float32_t fVal)
{
    float32_t y0, y1, y2;

    y0 = __meisqrtf32(fVal);   //Initial estimate of isqrt(fVal)


    if(fVal == 0.0f)
    {
        y0 = 0.0f;
    }

    y1 = y0*((float32_t)1.5f - y0*y0*fVal*(float32_t)0.5f);
    //Newton rapshon iteration 1
    y2 = y1*((float32_t)1.5f - y1*y1*fVal*(float32_t)0.5f);
    //Newton rapshon iteration 2
    y2 = y2 * fVal;
    //est(1/sqrt(fVal))*fVal = est(sqrt(fVal))

    return(y2);
}

//
// CLAsincos_inline(float32_t fAngleRad, float32_t *y_sin, float32_t *y_cos)
//
#pragma FUNC_ALWAYS_INLINE(CLAsincos_inline)
static inline void CLAsincos_inline(float32_t fAngleRad,
                                    float32_t *y_sin,
                                    float32_t *y_cos)
{
    float32_t tblIdx;     //The floating pt table index
    float32_t X;          //Fractional part of tblidx
    float32_t SinK, CosK; //Table values sin and cos that are closest to the
                          //user input angle value
    int16_t index;

    tblIdx = fAngleRad * CLAsincosTable_TABLE_SIZEDivTwoPi;
    index=(((int16_t)tblIdx)&(int16_t)0x007F);

    SinK = CLAsincosTable[index];    //*pTblSin;
    CosK = CLAsincosTable[index+32]; //*pTblCos;

    X = __mfracf32(tblIdx);
    X = X * (float32_t)CLAMATH_TWOPI_DIV_TABLE_SIZE;

    //Using the Taylor series
    *y_cos = CosK + X * (-SinK             \
            + X * (CLAsincosTable_Coef0 * CosK   \
            + X * (CLAsincosTable_Coef1_pos * SinK   \
            + X * (CLAsincosTable_Coef2 * CosK   \
            + X * (CLAsincosTable_Coef3_neg * SinK)))));

    *y_sin = SinK + X * (CosK                 \
            + X * (CLAsincosTable_Coef0 * SinK   \
            + X * (CLAsincosTable_Coef1 * CosK   \
            + X * (CLAsincosTable_Coef2 * SinK   \
            + X * (CLAsincosTable_Coef3 * CosK)))));
}

//
// CLAexpN_inline(float32_t fVal, float32_t N)
//
#pragma FUNC_ALWAYS_INLINE(CLAexpN_inline)
static inline float32_t CLAexpN_inline(float32_t fVal, float32_t N)
{
    float32_t ln_N;   //natural logarithm of N
    float32_t Exp;    //equivalent Exponent
    float32_t result;

    //Step(1):   Calculate ln(N)
    ln_N = CLAln_inline(N);

    //Step(2):   fVal*ln(N)
    Exp = fVal*ln_N;

    //Step(3):   N^x = e^(fVal*ln(N))
    result = CLAexp_inline(Exp);

    return(result);
}

//
// CLAlogN_inline(float32_t fVal, float32_t N)
//
#pragma FUNC_ALWAYS_INLINE(CLAlogN_inline)
static inline float32_t CLAlogN_inline(float32_t fVal, float32_t N)
{
    float32_t ln_fVal;
    float32_t ln_N;
    float32_t result;

    //Step 1:   Calculate natural logarithm of fVal
    ln_fVal = CLAln_inline(fVal);

    //Step 2:   Calculate natural logarithm of N
    ln_N = CLAln_inline(N);

    //Step 3:   log_N(x) = ln(fVal)/ln(N)
    result = CLAdiv_inline(ln_fVal, ln_N);

    return(result);
}

//
// CLA_floor(float32_t val)
//
static inline float32_t CLA_floor(float32_t val)
{
    volatile uint32_t temp = (uint32_t)val;

    if(val < 0.0f)
    {
        temp = temp - 1;
    }

    return((float32_t)temp);
}

//
// CLA_ceil(float32_val)
//
static inline float32_t CLA_ceil(float32_t val)
{
    volatile uint32_t temp = (uint32_t)val;

    if(val > 0.0f)
    {
        temp = temp + 1;
    }

    return((float32_t)temp);
}

#endif

//###########################################################################
//
//End of the C bindings section for C++ compilers.
//
//###########################################################################
#ifdef __cplusplus
}
#endif //__cplusplus

#endif // __CLAMATH_H__
