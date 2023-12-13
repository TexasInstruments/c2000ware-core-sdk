//#############################################################################
// \file     TMU_SQRTF32_GenTable.c
// \breif    SQRTF32 Lookup table generator
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
//===========================================================================
// SQRTF32 Coefficient Table Generator:
//===========================================================================

void SQRTF32_Generate_Coefficients(void)
{
	unsigned int	i;
    // <<VC161025: had to change long double to double for the following vars>>
	double		X0_f64;
	double		X1_f64;
	double		Y0_f64;
	double		Y1_f64;
	double		S1_f64;
	double		S2_f64;
	double		C1_f64;
	double		C2_f64;
	double		C3_f64;
	double		dx0_f64;
	double		temp;
    
	double		Y0_2_f64;
	double		Y0_3_f64;
	double		Y0_4_f64;
	double		Y0_5_f64;
	double		Y0_6_f64;
	double		Y0_7_f64;
	double		Y0_8_f64;
	double		Y0_9_f64;
    
	double		X0_2_f64;
	double		X0_3_f64;

	// Initialize first value:
	X0_f64  =  1.0;					// 1.0
	dx0_f64 =  0.00390625;			// 1/(SQRT_TABLE_SIZE * 2)
	X1_f64  = X0_f64 + dx0_f64;		

	for(i=0; i < SQRT_TABLE_SIZE; i++)
		{
		// Initialize 64-bit float values for intermediate calculations:
		Y0_f64 = 1.0 / sqrt(X0_f64);
		Y1_f64 = 1.0 / sqrt(X1_f64);

		Y0_2_f64 = Y0_f64 * Y0_f64;
		Y0_3_f64 = Y0_2_f64 * Y0_f64;
		Y0_4_f64 = Y0_3_f64 * Y0_f64;
		Y0_5_f64 = Y0_4_f64 * Y0_f64;
		Y0_6_f64 = Y0_5_f64 * Y0_f64;
		Y0_7_f64 = Y0_6_f64 * Y0_f64;
		Y0_8_f64 = Y0_7_f64 * Y0_f64;
		Y0_9_f64 = Y0_8_f64 * Y0_f64;

		X0_2_f64 = X0_f64 * X0_f64;
		X0_3_f64 = X0_2_f64 * X0_f64;

		// Calculate C1, C2, C3:
		// C1 = 2.4375*Y0^3 - 3.375*Y0^5*X0 + 1.6875*Y0^7*X0^2 - 0.25*Y0^9*X0^3
		// C2 = 1.6875*Y0^5 - 1.6875*Y0^7*X0 + 0.375*Y0^9*X0^2
		// C3 = 0.5625*Y0^7 - 0.25*Y0^9*X0
		C1_f64 = -2.4375*Y0_3_f64 +  3.375*Y0_5_f64*X0_f64 - 1.6875*Y0_7_f64*X0_2_f64 + 0.25*Y0_9_f64*X0_3_f64;
		C2_f64 = 1.6875*Y0_5_f64 - 1.6875*Y0_7_f64*X0_f64 +  0.375*Y0_9_f64*X0_2_f64;
		C3_f64 = -0.5625*Y0_7_f64 +   0.25*Y0_9_f64*X0_f64;

		// S1 = C1 + 2*dx0*C2 + 3*dx0*dx0*C3
		S1_f64 = C1_f64 + 2.0*dx0_f64*C2_f64 + 3.0*dx0_f64*dx0_f64*C3_f64;
		// S2 = C2 + 3*dx0*C3
		S2_f64 = C2_f64 + 3*dx0_f64*C3_f64;

		// Above equatiosn are for ISQRTF32. Convert to SQRTF32:
		//
		// S2 = S2*X1 + S1 
		// S1 = S1*X1 + Y1
		// Y0 = Y1*X1
		S2_f64 = S2_f64 * X1_f64 + S1_f64;
		S1_f64 = S1_f64 * X1_f64 + Y1_f64;
		Y1_f64 = Y1_f64 * X1_f64;

		// Store values in tables:
		SQRTF32_X0[i].f32 = (float) X1_f64;			
		SQRTF32_Y0[i].f32 = (float) Y1_f64;
		SQRTF32_S1[i].f32 = (float) S1_f64;
		SQRTF32_S2[i].f32 = (float) S2_f64;

		// Fudge factors to improve accuracy:
		Y1_f64 = Y1_f64 * 1.00000005;
		S1_f64 = S1_f64 * 1.000001;
		S2_f64 = S2_f64 * 1.0;

		// Store Y0 as +ve Q31 value:
		temp = Y1_f64 * 2147483648.0;
		if( temp >= 0.0)
			temp = temp + 0.5;
		else
			temp = temp - 0.5;
		SQRTF32_Y0i[i] = (unsigned long) (temp + (1 << 6));
			
		// Store S1 as +ve Q23 value:
		temp = S1_f64 * 8388608.0;
		if( temp >= 0.0)
			temp = temp + 0.5;
		else
			temp = temp - 0.5;
		SQRTF32_S1i[i] = (unsigned long) temp;

		// Store S2 as +ve Q17 value:
		temp = S2_f64 * 131072.0;
		if( temp >= 0.0)
			temp = temp + 0.5;
		else
			temp = temp - 0.5;
		SQRTF32_S2i[i] = (unsigned long) -temp;

		// Increment X for next table entry:
		X0_f64 = X0_f64 + 0.0078125;		// X0 = X0 + 1.0/(SQRT_TABLE_SIZE = 128)
		X1_f64 = X1_f64 + 0.0078125;		// X1 = X1 + 1.0/(SQRT_TABLE_SIZE = 128)
		}

	if(PRINT_SQRT_TABLE == 1)
		{
		fprintf(OutPtr,"\nStart Of Coefficient Table:\n");
		for(i=0; i < SQRT_TABLE_SIZE; i++)
			{
			fprintf(OutPtr,"\n%4d | X0 = %16.12f | Y0 = %16.12f"
                           "   S1 = %16.12f   S2 = %16.12f | Y0i = %16lu"
                           "   S1i = %16lu   S2i = %16lu", (i), 
                           SQRTF32_X0[i].f32, SQRTF32_Y0[i].f32,  
                           SQRTF32_S1[i].f32, SQRTF32_S2[i].f32, 
                           SQRTF32_Y0i[i], SQRTF32_S1i[i],  SQRTF32_S2i[i]);
			}
		fprintf(OutPtr,"\n\nEnd of data.\n");
		}
}


// End of file
