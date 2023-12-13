//#############################################################################
// \file     TMU_ATANF32_GenTable.c
// \breif    ATAN Lookup table generator
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

//===========================================================================
// ATANF32 Coefficient Table Generator:
//===========================================================================

void ATANF32_Generate_Coefficients(void)
{
	int	i;
// <<VC161025: had to change long double to double for the entire file>>
	double  dx0_f64;
	double  X0_f64;
	double  X1_f64;
	double  X2_f64;
	double  Y0_f64;
	double  S1_f64;
	double  S2_f64;
	double  temp;
	        
    double  c12, c13, b1;
	double  c22, c23, b2;
	double  c32, c33, b3;
	double  a0, a1, a2;

	X0_f64  =  0.0;
	dx0_f64 =  0.00390625;				// 1/(TABLE_SIZE * 2), TABLE_SIZE == 128
	X1_f64  = X0_f64 + dx0_f64;		
	X2_f64  = X1_f64 + dx0_f64;

	for(i=0; i < ATAN_TABLE_SIZE; i++)
		{
		if( i == 0 )
			{
			// Table location 0 is special case:
			Y0_f64 = 0.0;
			S1_f64 = 0.159151705194863 * 2.0;		// = 2 * (128 * atan(1/128) / 2PI)
			S2_f64 = 0.0;
			}
		else
			{
			c12 = X0_f64;
			c13 = X0_f64 * X0_f64;
			b1  = atan(X0_f64);
			c22 = X1_f64;
			c23 = X1_f64 * X1_f64;
			b2  = atan(X1_f64);
			c32 = X2_f64;
			c33 = X2_f64 * X2_f64;
			b3  = atan(X2_f64);

			a2 = ((b2-b1)*(c32-c12) - (b3-b1)*(c22-c12))/((c13-c33)*(c22-c12) - (c13-c23)*(c32-c12));
			a1 = ((b3-b1) + a2*(c13-c33))/(c32-c12);
			a0 = b1 - a1*c12 - a2*c13;

			//  Y0 = (1/2PI) * (a0 + a1*(X0 + dx0) + a2*(X0 + dx0)^2)
			//  S1 = (1/2PI) * (a1 + 2*a2*(X0+dx0))
			//  S2 = (1/2PI) * (a2)
			Y0_f64 = a0 + a1*X1_f64 + a2*X1_f64*X1_f64;
			Y0_f64 = Y0_f64 * INV2PI;
			S1_f64 = a1 + 2.0*a2*X1_f64;
			S1_f64 = S1_f64 * INV2PI;
			S2_f64 = a2;
			S2_f64 = S2_f64 * INV2PI;

			// Best values for both ATANF32:
			Y0_f64 = Y0_f64 * 1.0;
			S1_f64 = S1_f64 * 1.0;
			S2_f64 = S2_f64 * 1.0;
			}

		ATANF32_X0[i].f32 = (float) X0_f64;
		ATANF32_X2[i].f32 = (float) X2_f64;
		ATANF32_Y0[i].f32 = (float) Y0_f64;
		ATANF32_S1[i].f32 = (float) S1_f64;
		ATANF32_S2[i].f32 = (float) S2_f64;

		// Store Y0 as +ve Q30 value:
		temp = Y0_f64 * 1073741824.0;
		if( temp >= 0.0)
			temp = temp + 0.5;
		else
			temp = temp - 0.5;
		ATANF32_Y0i[i] = (unsigned long) temp;
			
		// Store S1 as +ve Q22 value:
		temp = S1_f64 * 4194304.0;
		if( temp >= 0.0)
			temp = temp + 0.5;
		else
			temp = temp - 0.5;
		ATANF32_S1i[i] = (unsigned long) temp;

		// Store S2 as +ve Q16 value:
		temp = S2_f64 * 65536.0;
		if( temp >= 0.0)
			temp = temp + 0.5;
		else
			temp = temp - 0.5;
		ATANF32_S2i[i] = (unsigned long) -temp;

		X0_f64 = X2_f64;
		X1_f64 = X0_f64 + dx0_f64;		
		X2_f64 = X1_f64 + dx0_f64;
		}

	if(PRINT_ATAN_TABLE == 1)
		{
		fprintf(OutPtr,"\n\nStart Of Coefficients Table:\n");
		for(i=0; i < ATAN_TABLE_SIZE; i++)
			{
			fprintf(OutPtr,"\n%4d | x1 = %16.12f  x2 = %16.12f | Y0 = %16.12f   S1 = %16.12f   S2 = %16.12f | Y0i = %16lu   S1i = %16lu   S2i = %16lu", i, ATANF32_X0[i].f32, ATANF32_X2[i].f32, ATANF32_Y0[i].f32, ATANF32_S1[i].f32, ATANF32_S2[i].f32, ATANF32_Y0i[i], ATANF32_S1i[i], ATANF32_S2i[i]);
			}
		fprintf(OutPtr,"\n\nEnd of data.\n");
		}
}

// End of file
