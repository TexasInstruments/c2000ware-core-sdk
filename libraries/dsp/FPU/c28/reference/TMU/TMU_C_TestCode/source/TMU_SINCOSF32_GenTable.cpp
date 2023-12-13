//#############################################################################
// \file     TMU_SINCOSF32_GenTable.c
// \breif    SIN & COS Lookup table generator
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

//===========================================================================
// SINF32 and COSF32 Coefficient Table Generator:
//===========================================================================

void SINCOSF32_Generate_Coefficients(void)
{
	int	i;

	F32_UI32 X0;
	F32_UI32 X2;
// <<VC161025: had to change long double to double for the entire file>>
	double  X0_f64;
	double  Y0_f64;
	double  S1_f64;
	double  S2_f64;
	double  temp;
	double  x0;
	double  x1;
            
	double  dx0 = 0.0009765625;	   // 1/1024
	double  C1 =   6.28318530718;  // = 2pi
	double  C2 = -19.73920880217;  // = -(2pi)^2/2!
	double  C3 = -41.34170224047;  // = -(2pi)^3/3!

	// Initialize table for: 	0.0009765625 <= |X| <= (0.25 - 0.0009765625)
	X0.f32 = 0.0;
	for(i=0; i < SINCOS_TABLE_SIZE; i++)
		{

		X2.f32 = X0.f32 + 0.001953125;		// Step size = 2/1024

		X0_f64	= (double) X0.f32;

		x0 = X0_f64 * C1;					// Convert X0 to radians
		x1 = (X0_f64 + dx0) * C1;

		Y0_f64 = sin(x1);					// Y value at mid-point between X0 and X2
		S1_f64 = (cos(x0) * C1) + (2 * dx0 * sin(x0) * C2) + (3 * dx0 * dx0 * cos(x0) * C3);
		S2_f64 = (sin(x0) * C2) + (3 * dx0 * cos(x0) * C3);

		// Best values for SINF32:
//		Y0_f64 = Y0_f64 * 1.00000004;
//		S1_f64 = S1_f64 * 1.000001;

		// Best values for COSF32:
//		Y0_f64 = Y0_f64 * 1.00000005;
//		S1_f64 = S1_f64 * 0.999995;

		// Best values for both SINF32 and COSF32:
		Y0_f64 = Y0_f64 * 1.00000005;
		S1_f64 = S1_f64 * 0.999996;

		SINF32_X0[i].f32 = (float) (X0.f32 + 0.0009765625);
		SINF32_Y0[i].f32 = (float) Y0_f64;
		SINF32_S1[i].f32 = (float) S1_f64;
		SINF32_S2[i].f32 = (float) S2_f64;

		// Store Y0 as +ve Q30 value:
		temp = Y0_f64 * 1073741824.0;
		if( temp >= 0.0)
			temp = temp + 0.5;
		else
			temp = temp - 0.5;
		SINF32_Y0i[i] = (long) temp;
			
		// Store S1 as +ve Q21 value:
		temp = S1_f64 * 2097152.0;
		if( temp >= 0.0)
			temp = temp + 0.5;
		else
			temp = temp - 0.5;
		SINF32_S1i[i] = (long) temp;

		// Store S2 as +ve Q14 value:
		temp = S2_f64 * 16384.0;
		if( temp >= 0.0)
			temp = temp + 0.5;
		else
			temp = temp - 0.5;
		SINF32_S2i[i] = (long) -temp;

		X0.ui32 = X2.ui32;
		}

	if(PRINT_SINCOS_TABLE == 1)
		{
		fprintf(OutPtr,"\n\nStart Of Coefficients Table:\n");
		for(i=0; i < SINCOS_TABLE_SIZE; i++)
			{
			fprintf(OutPtr,"\n%4d | x1 = %16.12f | Y0 = %16.12f   S1 = %16.12f   S2 = %16.12f | Y0i = %16ld   S1i = %16ld   S2i = %16ld", i, SINF32_X0[i].f32, SINF32_Y0[i].f32, SINF32_S1[i].f32, SINF32_S2[i].f32, SINF32_Y0i[i], SINF32_S1i[i], SINF32_S2i[i]);
			}
		fprintf(OutPtr,"\n\nEnd of data.\n");
		}
}

// End of file
