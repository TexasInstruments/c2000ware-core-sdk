//#############################################################################
// \file     FASTRTS_ATANF32.c
// \breif    Emulate the Fast RTS ATANF32 instruction 
// \author   original: Alex Tessarolo 
// \history	
//
//  ver  | dd-mmm-yyyy | Who     | Changes.
//  =====|=============|=========|============================================
//  1.0  | 30-Apr-2012 | Alex T. | Original Release.
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

//===========================================================================
// FastRTS ATANF32: As supported in FPU and Fast RTS library.
//===========================================================================
//
// Using Chebyshev polynomial approximaton formula:
//
// Seventh Order Polynomial:
//
//   Y = atan(X) = 0.999133448222780*X - 0.320533292381664*X^3 
//                 + 0.144982490144465*X^5 - 0.038254464970299*X^7
//
//   Ypu = Y / 2PI
//  
//---------------------------------------------------------------------------

float	ATANF32_FPUFastRTS_Emulation(float X)
{
	float			Xpwr2;
	float			Y;
	// Seventh Order Polynomial coefficients:
	float			C0 = 0.999133448222780;
	float			C1 = -0.320533292381664;
	float			C2 = 0.144982490144465;
	float			C3 = -0.038254464970299;
	
	// Take fraction of input:
	Xpwr2 = X * X;

	// Seventh Order Polynomial:
	Y = X * (C0 + Xpwr2*(C1 + Xpwr2*(C2 + Xpwr2*C3)));

	return	(Y * (float) INV2PI);
}

// End of file
