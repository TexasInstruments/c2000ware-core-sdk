//#############################################################################
// \file     FASTRTS_DIVF32.c
// \breif    Emulate the Fast RTS DIVF32 instruction 
// \author   original: Alex Tessarolo 
// \history	
//
//  ver  | dd-mmm-yyyy | Who     | Changes.
//  =====|=============|=========|============================================
//  6.0  | 28-Nov-2011 | Alex T. | Original Release.
//  -----|-------------|---------|--------------------------------------------
//  7.0  | 31-Jan-2012 | Alex T. | Reduced complexity of Phase 1 where 
//       |             |         | table_index and dx is extracted.
//  -----|-------------|---------|--------------------------------------------
//  8.0  | 18-Feb-2012 | Alex T. | Did bit accurate version of Phase 2, 3 & 4
//       |             |         | 
//  -----|-------------|---------|--------------------------------------------
//  9.0  |  7-Apr-2012 | Alex T. | Modified Phase 3 & 4 to be common with
//       |             |         | INVF32 and ISQRTF32.
//  -----|-------------|---------|--------------------------------------------
//  10.0 | 13-Aug-2012 | Alex T. | Corrected comment on COSF32 function
//       |             |         | relating to setting of result for exact
//       |             |         | frac(X) == 0.0 and 0.5  (1.0 and -1.0 result)
//  -----|-------------|---------|--------------------------------------------
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
// FastRTS COSF32: As supported in FPU and Fast RTS library.
//===========================================================================
//
// Using Eulers formula:
//
//   Cos(X) = Cos(X0) - Sin(X0)*dx - Cos(X0)*dx*dx/2! + Sin(X0)*dx*dx*dx/3! 
//
//   Where: X = X0 + dx
//  
//---------------------------------------------------------------------------

float	COSF32_FPUFastRTS_Emulation(float X)
{
	long			index;
	float			temp;
	float			dx;
	float			X0;
	float			Y;
	float			SIN_X0;
	float			COS_X0;
	float			C0 = -0.5;
	float			C1 = -0.1666666667;
	
	// Take fraction of input:
	index = (long) X;
	temp = X - ((float) index);

	temp = (float) (temp * 512.0);
	index = (long) temp;
	X0 = (float) ((((float) index) * 2.0 * PI) / 512.0);
	dx = (float) (((temp -  ((float) index)) * 2.0 * PI) / 512.0);

	SIN_X0 = (float) sin(X0);
	COS_X0 = (float) cos(X0);

	Y = COS_X0 + dx * (-SIN_X0 +  dx * (C0 * COS_X0 - dx * C1 * SIN_X0));

	return	Y;
}

// End of file
