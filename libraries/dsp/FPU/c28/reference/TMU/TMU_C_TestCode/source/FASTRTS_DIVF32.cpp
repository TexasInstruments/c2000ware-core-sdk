//#############################################################################
// \file     FASTRTS_DIVF32.c
// \breif    Emulate the Fast RTS DIVF32 instruction 
// \author   original: Alex Tessarolo 
// \history	
//
//  ver  | dd-mmm-yyyy | Who     | Changes.
//  =====|=============|=========|============================================
//  2.0  | 24-Apr-2012 | Alex T. | Original Release.
//  -----|-------------|---------|--------------------------------------------
//  3.0  | 31-May-2012 | Alex T. | Added LVF/LUF flags, corrected boundary checks, corrected phase 5 calculations.
//  -----|-------------|---------|--------------------------------------------
//
// \note 
// -# This is built using g++ and make files
// -# Target is an x86 system
//
// Copyright (C) $YEAR$ Texas Instruments Incorporated - http://www.ti.com/
// ALL RIGHTS RESERVED
//#############################################################################
//
//
//#############################################################################
#include "TMU.h"

//*****************************************************************************
// globals
//*****************************************************************************
unsigned long	EINVF32_TABLE[128] = {
0x7F, 0x7E, 0x7C, 0x7A, 0x78, 0x76, 0x75, 0x73, 0x71, 0x6F, 0x6D, 0x6C, 0x6A, 0x68, 0x67, 0x65,
0x64, 0x62, 0x60, 0x5F, 0x5D, 0x5C, 0x5A, 0x59, 0x58, 0x56, 0x55, 0x53, 0x52, 0x51, 0x4F, 0x4E, 
0x4D, 0x4C, 0x4A, 0x49, 0x48, 0x47, 0x45, 0x44, 0x43, 0x42, 0x41, 0x40, 0x3F, 0x3D, 0x3C, 0x3B,
0x3A, 0x39, 0x38, 0x37, 0x36, 0x35, 0x34, 0x33, 0x32, 0x31, 0x30, 0x2F, 0x2E, 0x2D, 0x2C, 0x2C,
0x2B, 0x2A, 0x29, 0x28, 0x27, 0x26, 0x25, 0x25, 0x24, 0x23, 0x22, 0x21, 0x21, 0x20, 0x1F, 0x1E,
0x1E, 0x1D, 0x1C, 0x1B, 0x1B, 0x1A, 0x19, 0x18, 0x18, 0x17, 0x16, 0x16, 0x15, 0x14, 0x14, 0x13,
0x12, 0x12, 0x11, 0x10, 0x10, 0x0F, 0x0E, 0x0E, 0x0D, 0x0D, 0x0C, 0x0B, 0x0B, 0x0A, 0x0A, 0x09,
0x09, 0x08, 0x07, 0x07, 0x06, 0x06, 0x05, 0x05, 0x04, 0x04, 0x03, 0x03, 0x02, 0x02, 0x01, 0x01 };


//===========================================================================
// FastRTS DIVF32: As supported in FPU and Fast RTS library.
//===========================================================================
float	DIVF32_FPUFastRTS_Emulation(float Z, float X)
{
	F32_UI32		tempX;
	F32_UI32		tempZ;
	F32_UI32		Y;

	unsigned int	index;

	unsigned long	Si;		// Bit  31    Sign     Of Input Value
	unsigned long	Ei;		// Bits 30:23 Exponent Of Input Value
	unsigned long	Mi;		// Bits 22:0  Mantissa Of Input Value
	unsigned long	So;		// Bit  31    Sign     Of Estimate Value
	unsigned long	Eo;		// Bits 30:23 Exponent Of Estimate Value
	unsigned long	Mo;		// Bits 22:0  Mantissa Of Estimate Value
	unsigned long	Sz;		// Bit  31    Sign     Of Numerator Value
	unsigned long	Ez;		// Bits 30:23 Exponent Of Numerator Value
	unsigned long	Mz;		// Bits 22:0  Mantissa Of Numerator Value

	tempX.f32 = X;

	Si = (tempX.ui32 & 0x80000000);
	Ei = (tempX.ui32 & 0x7F800000);
	Mi = (tempX.ui32 & 0x007FFFFF);

	tempZ.f32 = Z;

	Sz = (tempZ.ui32 & 0x80000000);
	Ez = (tempZ.ui32 & 0x7F800000);
	Mz = (tempZ.ui32 & 0x007FFFFF);

	// Check if input is zero or Denorm. If so, generate infinity and return:
	if( Ei == 0x00000000 )	
		{
		So = 0x00000000;
		Eo = 0x7F800000;
		Mo = 0x00000000;
		Y.ui32 = So + Eo + Mo;
		return 	Y.f32;
		}
	// Check if Nan or infinity input. If so, generate zero adn return:
	if( Ei == 0x7F800000 )
		{
		So = 0x00000000;
		Eo = 0x00000000;
		Mo = 0x00000000;
		Y.ui32 = So + Eo + Mo;
		return 	Y.f32;
		}

	// Check if input is modulo of 2. If so, adjust exponent and return with value:
	if( Mi == 0x00000000 )
		{
		So = Si ^ Sz;	
		Eo = (0x3F800000L + Ez) - Ei;
		Mo = Mz;
		Y.ui32 = So + Eo + Mo;
		return 	Y.f32;
		}

	// If input too big, return zero:
	if( Ei == 0x7F000000 )
		{
		So = 0x00000000;
		Eo = 0x00000000;
		Mo = 0x00000000;
		Y.ui32 = So + Eo + Mo;
		return 	Y.f32;
		}

	// Copy sign bit and adjust exponent:
	So = Si;	
	Eo = 0x7E800000 - Ei;
	index = (unsigned int) (Mi >> 16);
	// Get initial estimate value of mantissa from table:
	Mo = EINVF32_TABLE[index] << 16;

	// This value is the estimate of Y = 1/X:
	Y.ui32 = So + Eo + Mo;

	// Execute Newton Raphson Algorithm to improve precision:
	Y.f32 = (float) Y.f32 * (2.0 - Y.f32 * X);
	Y.f32 = (float) Y.f32 * (2.0 - Y.f32 * X);

	return	(Y.f32 * Z);
}

// End of file
