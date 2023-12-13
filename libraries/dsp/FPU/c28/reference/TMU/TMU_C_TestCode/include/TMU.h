#ifndef _TMU_H_
#define _TMU_H_
//#############################################################################
//
// \file   TMU.h
//
// \brief  DSP Library Definitions and Types
// \author original: Alex Tessarolo, x86 C library: Vishal Coelho
// \date   Sep 14, 2016
//
// \note 
// -# This is built using g++ and make files
// -# Target is an x86 system
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

//*****************************************************************************
// the includes
//*****************************************************************************
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
//defines
//*****************************************************************************
#define VERSION         "3.0"
#define SINCOS_VERSION  "10.0"
#define ATAN_VERSION    "1.0"
#define QUAD_VERSION    "1.0"

#include <math.h>
#include <stdio.h>
#include <fcntl.h>
//#include <io.h> -- linux uses unistd.h
#include <unistd.h>

#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
//#include <conio.h> -- DOS, not supported on linux

//#include <dos.h> -- not supported on linux
#include <time.h> 
#include <stdint.h>

// Common defines
#define PI				    3.14159265359
#define INV2PI              0.159154943091895
#define	Q_RESULT		    24					  // Q24, Q25, Q26,..
// <<VC161025: had to change long double to double for the entire file>>
#define	Q_SCALE			    (double) (1 << Q_RESULT)

// Square Root defines
#define	SQRT_TABLE_SIZE		128
#define PRINT_SQRT_TABLE    1				      // 1 = Print Table, 0 = Don't Print
#define	SQRT2_24Q23		    0x0000000000B504F3LL  // = sqrt(2) * 2^23 = 11863283.20303

// Division (and quad) defines
#define	DIV_TABLE_SIZE      256					  // 128 or 256 are only valid values
#define PRINT_DIV_TABLE     1					  // 1 = Print Table, 0 = Don't Print

// Sine defines
#define SINCOS_TABLE_SIZE   128
#define PRINT_SINCOS_TABLE  1                     // 1 = Print Table, 0 = Don't Print
#define	RETURN_FLOAT	    1                     // 1 = return float value, 0 = return long value
#define	SIN_COS_MODE	    0                     // 0 = calculate SINF32, 1 = calculate COSF32

// atan defines
#define ATAN_TABLE_SIZE     128
#define PRINT_ATAN_TABLE    1                     // 1 = Print Table, 0 = Don't Print

//*****************************************************************************
// typedefs
//*****************************************************************************
typedef	union {
	float			f32;	
	unsigned long	ui32;
	long			i32;
} F32_UI32;

typedef int64_t	i64;
//*****************************************************************************
// globals
//*****************************************************************************
extern FILE *OutPtr;
extern char OutputFileName[40];

extern F32_UI32 X;
extern F32_UI32	Z;
extern F32_UI32 Y1;
extern F32_UI32 Y3;
extern F32_UI32 Y4;
extern F32_UI32 Q1;
extern F32_UI32 Q3;

extern double TestCount;
       
extern double ErrorMaxY3posF64;
extern double ErrorMaxY3negF64;
extern double ErrorAvgY3posF64;
extern double ErrorAvgY3negF64;
extern double ErrorCountY3posF64;
extern double ErrorCountY3negF64;
extern double ErrorCountY3posF64_half;
extern double ErrorCountY3negF64_half;
       
extern double ErrorMaxY4posF64;
extern double ErrorMaxY4negF64;
extern double ErrorAvgY4posF64;
extern double ErrorAvgY4negF64;
extern double ErrorCountY4posF64;
extern double ErrorCountY4negF64;

// Square Root Globals
extern F32_UI32 SQRTF32_X0[SQRT_TABLE_SIZE];
extern F32_UI32 SQRTF32_Y0[SQRT_TABLE_SIZE];
extern F32_UI32 SQRTF32_S1[SQRT_TABLE_SIZE];
extern F32_UI32 SQRTF32_S2[SQRT_TABLE_SIZE];
extern unsigned long SQRTF32_Y0i[SQRT_TABLE_SIZE];
extern unsigned long SQRTF32_S1i[SQRT_TABLE_SIZE];
extern unsigned long SQRTF32_S2i[SQRT_TABLE_SIZE];

// Division Globals
extern F32_UI32 DIVF32_X0[DIV_TABLE_SIZE];
extern F32_UI32 DIVF32_X2[DIV_TABLE_SIZE];
extern F32_UI32 DIVF32_Y0[DIV_TABLE_SIZE];
extern F32_UI32 DIVF32_S1[DIV_TABLE_SIZE];
extern F32_UI32 DIVF32_S2[DIV_TABLE_SIZE];
extern unsigned long DIVF32_Y0i[DIV_TABLE_SIZE];
extern unsigned long DIVF32_S1i[DIV_TABLE_SIZE];
extern unsigned long DIVF32_S2i[DIV_TABLE_SIZE];
extern int LVF_flag;			// Latched overflow flag.
extern int LUF_flag;			// Latched underflow flag.

// sincos Globals
extern F32_UI32 SINF32_X0[SINCOS_TABLE_SIZE];
extern F32_UI32 SINF32_X2[SINCOS_TABLE_SIZE];
extern F32_UI32 SINF32_Y0[SINCOS_TABLE_SIZE];
extern F32_UI32 SINF32_S1[SINCOS_TABLE_SIZE];
extern F32_UI32 SINF32_S2[SINCOS_TABLE_SIZE];
extern long SINF32_Y0i[SINCOS_TABLE_SIZE];
extern long SINF32_S1i[SINCOS_TABLE_SIZE];
extern long SINF32_S2i[SINCOS_TABLE_SIZE];
extern long dx_max;
extern long dx_min;
extern i64 dx_dx_max;
extern i64 dx_dx_min;

// atan globals
extern F32_UI32 ATANF32_X0[ATAN_TABLE_SIZE];
extern F32_UI32 ATANF32_X2[ATAN_TABLE_SIZE];
extern F32_UI32 ATANF32_Y0[ATAN_TABLE_SIZE];
extern F32_UI32 ATANF32_S1[ATAN_TABLE_SIZE];
extern F32_UI32 ATANF32_S2[ATAN_TABLE_SIZE];
extern unsigned long ATANF32_Y0i[ATAN_TABLE_SIZE];
extern unsigned long ATANF32_S1i[ATAN_TABLE_SIZE];
extern unsigned long ATANF32_S2i[ATAN_TABLE_SIZE];

// quad globals
extern double Y1QuadrantF64;
extern double Y1RatioF64;
extern double Y3QuadrantF64;
extern double Y3RatioF64;
extern double Y3ErrorPosF64;
extern double Y3ErrorNegF64;

//*****************************************************************************
// static inlines
//*****************************************************************************

static inline char* _strlwr(char *s)
{
    char *tmp = s;
    for(;*tmp; ++tmp)
    {
        *tmp = tolower((unsigned char) *tmp);
    }
    return s;
}

static inline char* _strupr(char *s)
{
    char *tmp = s;
    for(;*tmp; ++tmp)
    {
        *tmp = toupper((unsigned char) *tmp);
    }
    return s;
}

//*****************************************************************************
// prototypes
//*****************************************************************************
extern void PrintResult(void);
#define SQRTF32_PrintResult PrintResult
#define DIVF32_PrintResult  PrintResult
extern void ATANF32_PrintResult(void);
#define SINCOSF32_PrintResult ATANF32_PrintResult
extern void QUADF32_PrintResult(void);


extern void SQRTF32_Generate_Coefficients(void);
extern void SQRTF32_CheckError(F32_UI32 X);
extern float SQRTF32_Hardware_Emulation(float X);
extern float SQRTF32_FPUFastRTS_Emulation(float X);

extern void DIVF32_Generate_Coefficients(void);
extern void DIVF32_CheckError(F32_UI32 Z, F32_UI32 X);
extern void DIVF32_CheckValues(F32_UI32 Z, F32_UI32 X);
extern float DIVF32_Hardware_Emulation(float Z, float X);
extern float DIVF32_FPUFastRTS_Emulation(float Z, float X);

extern void SINCOSF32_Generate_Coefficients(void);
extern void SINF32_CheckError(F32_UI32 X);
extern void COSF32_CheckError(F32_UI32 X);

#if (RETURN_FLOAT == 1)
extern float SINF32_Hardware_Emulation(float X);
extern float COSF32_Hardware_Emulation(float X);
#else
extern long SINF32_Hardware_Emulation(float X);
extern long COSF32_Hardware_Emulation(float X);
#endif
extern float SINF32_FPUFastRTS_Emulation(float X);
extern float COSF32_FPUFastRTS_Emulation(float X);

extern void ATANF32_Generate_Coefficients(void);
extern void ATANF32_CheckError(F32_UI32 X);
extern float ATANF32_Hardware_Emulation(float X);
extern float ATANF32_FPUFastRTS_Emulation(float X);

extern void QUADF32_CheckError(F32_UI32 Z, F32_UI32 X);
extern void QUADF32_Test(void);
extern float QUADF32_Hardware_Emulation(float Z, float X, float *Q);

#ifdef __cplusplus
}
#endif // extern "C"


#endif  // end of  _TMU_H_

// End of File
