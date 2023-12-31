//#############################################################################
// \file     FASTRTS_SQRTF32.c
// \breif    Emulate the Fast RTS SQRTF32 instruction 
// \author   original: Alex Tessarolo 
// \history	
//
//  ver  | dd-mmm-yyyy | Who     | Changes.
//  =====|=============|=========|============================================
//  3.0  | 30-Apr-2011 | Alex T. | Original Release.
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
unsigned long	EISQRTF32_EVEN_TABLE[128] = {
0x35, 0x34, 0x34, 0x33, 0x32, 0x32, 0x31, 0x30, 0x30, 0x2F, 0x2E, 0x2E, 0x2D, 0x2C, 0x2C, 0x2B,
0x2B, 0x2A, 0x29, 0x29, 0x28, 0x28, 0x27, 0x27, 0x26, 0x26, 0x25, 0x24, 0x24, 0x23, 0x23, 0x22,
0x22, 0x21, 0x21, 0x20, 0x20, 0x1F, 0x1F, 0x1E, 0x1E, 0x1E, 0x1D, 0x1D, 0x1C, 0x1C, 0x1B, 0x1B,
0x1A, 0x1A, 0x1A, 0x19, 0x19, 0x18, 0x18, 0x17, 0x17, 0x17, 0x16, 0x16, 0x15, 0x15, 0x15, 0x14,
0x14, 0x13, 0x13, 0x13, 0x12, 0x12, 0x12, 0x11, 0x11, 0x10, 0x10, 0x10, 0x0F, 0x0F, 0x0F, 0x0E,
0x0E, 0x0E, 0x0D, 0x0D, 0x0D, 0x0C, 0x0C, 0x0C, 0x0B, 0x0B, 0x0B, 0x0A, 0x0A, 0x0A, 0x09, 0x09,
0x09, 0x09, 0x08, 0x08, 0x08, 0x07, 0x07, 0x07, 0x06, 0x06, 0x06, 0x06, 0x05, 0x05, 0x05, 0x04,
0x04, 0x04, 0x04, 0x03, 0x03, 0x03, 0x03, 0x02, 0x02, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01, 0x00 };

unsigned long	EISQRTF32_ODD_TABLE[128] = {
0x7F, 0x7F, 0x7E, 0x7D, 0x7C, 0x7B, 0x7A, 0x79, 0x78, 0x77, 0x77, 0x76, 0x75, 0x74, 0x73, 0x72,
0x71, 0x71, 0x70, 0x6F, 0x6E, 0x6D, 0x6C, 0x6C, 0x6B, 0x6A, 0x69, 0x69, 0x68, 0x67, 0x66, 0x66,
0x65, 0x64, 0x64, 0x63, 0x62, 0x61, 0x61, 0x60, 0x5F, 0x5F, 0x5E, 0x5D, 0x5D, 0x5C, 0x5C, 0x5B,
0x5A, 0x5A, 0x59, 0x58, 0x58, 0x57, 0x57, 0x56, 0x56, 0x55, 0x54, 0x54, 0x53, 0x53, 0x52, 0x52,
0x51, 0x50, 0x50, 0x4F, 0x4F, 0x4E, 0x4E, 0x4D, 0x4D, 0x4C, 0x4C, 0x4B, 0x4B, 0x4A, 0x4A, 0x49,
0x49, 0x48, 0x48, 0x47, 0x47, 0x46, 0x46, 0x46, 0x45, 0x45, 0x44, 0x44, 0x43, 0x43, 0x42, 0x42,
0x42, 0x41, 0x41, 0x40, 0x40, 0x3F, 0x3F, 0x3F, 0x3E, 0x3E, 0x3D, 0x3D, 0x3D, 0x3C, 0x3C, 0x3B,
0x3B, 0x3B, 0x3A, 0x3A, 0x39, 0x39, 0x39, 0x38, 0x38, 0x38, 0x37, 0x37, 0x36, 0x36, 0x36, 0x35 };


//===========================================================================
// FastRTS SQRTF32: As supported in FPU and Fast RTS library.
//===========================================================================

float	SQRTF32_FPUFastRTS_Emulation(float X)
{
	F32_UI32		tempX;
	F32_UI32		Y;

	unsigned int	index;

	unsigned long	Si;		// Bit  31    Sign     Of Input Value
	unsigned long	Ei;		// Bits 30:23 Exponent Of Input Value
	unsigned long	Mi;		// Bits 22:0  Mantissa Of Input Value
	unsigned long	So;		// Bit  31    Sign     Of Estimate Value
	unsigned long	Eo;		// Bits 30:23 Exponent Of Estimate Value
	unsigned long	Mo;		// Bits 22:0  Mantissa Of Estimate Value

	tempX.f32 = X;

	Si = (tempX.ui32 & 0x80000000);
	Ei = (tempX.ui32 & 0x7F800000);
	Mi = (tempX.ui32 & 0x007FFFFF);

	// Check if input is zero or Denorm. If so, generate zero and return:
	if( Ei == 0x00000000 )	
		{
		So = 0x00000000;
		Eo = 0x00000000;
		Mo = 0x00000000;
		Y.ui32 = So + Eo + Mo;
		return 	Y.f32;
		}

	// Check if Nan or infinity input. If so, generate Infinity and return:
	if( Ei == 0x7F800000 )
		{
		So = 0x00000000;
		Eo = 0x7F800000;
		Mo = 0x00000000;
		Y.ui32 = So + Eo + Mo;
		return 	Y.f32;
		}

	// Check if input is negative. If so, generate zero and return:
	if( Si == 0x80000000 )
		{
		So = 0x00000000;
		Eo = 0x00000000;
		Mo = 0x00000000;
		Y.ui32 = So + Eo + Mo;
		return 	Y.f32;
		}

	// Adjust exponent and initialize mantissa with initial estimate value:
	// Clear sign bit and adjust exponent:
	So = 0x00000000;
	index = (unsigned int) (Mi >> 16);
	if( (Ei & 0x00800000) == 0x00800000 )
		{
		Mo = EISQRTF32_ODD_TABLE[index] << 16;
		}
	else
		{
		Mo = EISQRTF32_EVEN_TABLE[index] << 16;
		}

	// Check if exponet value is even:
	if( (Ei & 0x00800000) == 0x00800000 )
		{
		Eo = 0x5EC00000 - (Ei >> 1);
		// If mantissa is zero, then add one to exponent
		if( Mi == 0x00000000 )
			{
			Eo = Eo + 0x00800000;
			Mo = 0x00000000;
			}
		}
	else
	// else Exponent is odd:
		{
		Eo = 0x5F000000 - (Ei >> 1);
		}

	// This value is the estimate of Y = 1/sqrt(X):
	Y.ui32 = So + Eo + Mo;

	// Execute Newton Raphson Algorithm to improve precision:
	Y.f32 = (float) Y.f32 * (1.5 - Y.f32 * Y.f32 * X * 0.5);
	Y.f32 = (float) Y.f32 * (1.5 - Y.f32 * Y.f32 * X * 0.5);

	return	(Y.f32 * X);
}


// End of file
