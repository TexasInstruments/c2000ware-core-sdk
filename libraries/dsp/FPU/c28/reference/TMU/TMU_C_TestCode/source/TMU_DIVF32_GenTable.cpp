//#############################################################################
// \file     TMU_DIVF32_GenTable.c
// \breif    DIVF32 Lookup table generator
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
//===========================================================================
// DIVF32 Coefficient Table Generator:
//===========================================================================

// This version uses 2nd oder polynomial approximation:
void DIVF32_Generate_Coefficients(void)
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

	X0_f64  =  1.0;

	#if DIV_TABLE_SIZE == 128
	dx0_f64 =  0.00390625;				// 1/(DIV_TABLE_SIZE * 2)
	#endif
	#if DIV_TABLE_SIZE == 256
	dx0_f64 =  0.001953125;			// 1/(DIV_TABLE_SIZE * 2)
	#endif

	X1_f64  = X0_f64 + dx0_f64;		
	X2_f64  = X1_f64 + dx0_f64;

	for(i=0; i < DIV_TABLE_SIZE; i++)
		{
		c12 = X0_f64;
		c13 = X0_f64 * X0_f64;
		b1  = 1.0 / X0_f64;
		c22 = X1_f64;
		c23 = X1_f64 * X1_f64;
		b2  = 1.0 / X1_f64;
		c32 = X2_f64;
		c33 = X2_f64 * X2_f64;
		b3  = 1.0 / X2_f64;

		a2 = ((b2-b1)*(c32-c12) - (b3-b1)*(c22-c12))/((c13-c33)*(c22-c12) - (c13-c23)*(c32-c12));
		a1 = ((b3-b1) + a2*(c13-c33))/(c32-c12);
		a0 = b1 - a1*c12 - a2*c13;
		
		//  Y0 = (1/2PI) * (a0 + a1*(X0 + dx0) + a2*(X0 + dx0)^2)
		//  S1 = (1/2PI) * (a1 + 2*a2*(X0+dx0))
		//  S2 = (1/2PI) * (a2)
		Y0_f64 = a0 + a1*X1_f64 + a2*X1_f64*X1_f64;
		S1_f64 = a1 + 2.0*a2*X1_f64;
		S2_f64 = a2;

		// Fudge factors to improve accuracy:
		#if DIV_TABLE_SIZE == 128
		Y0_f64 = Y0_f64 * 1.0;
		S1_f64 = S1_f64 * 0.999995;
		S2_f64 = S2_f64 * 1.0;
		#endif
		#if DIV_TABLE_SIZE == 256
		Y0_f64 = Y0_f64 * 1.0;
		S1_f64 = S1_f64 * 1.0;
		S2_f64 = S2_f64 * 1.0;
		#endif

		DIVF32_X0[i].f32 = (float) X0_f64;
		DIVF32_X2[i].f32 = (float) X2_f64;
		DIVF32_Y0[i].f32 = (float) Y0_f64;
		DIVF32_S1[i].f32 = (float) S1_f64;
		DIVF32_S2[i].f32 = (float) S2_f64;

		// Store Y0 as +ve Q32 value + rounding:
		temp = Y0_f64 * 4294967296.0;
		if( temp >= 0.0)
			temp = temp + 0.5;
		else
			temp = temp - 0.5;
		DIVF32_Y0i[i] = (unsigned long) (temp + (1 << 7));
			
		#if DIV_TABLE_SIZE == 128
		// Store S1 as +ve Q24 value:
		temp = S1_f64 * 16777216.0;
		#endif
		#if DIV_TABLE_SIZE == 256
		// Store S1 as +ve Q23 value:
		temp = S1_f64 * 8388608.0;
		#endif
		if( temp >= 0.0)
			temp = temp + 0.5;
		else
			temp = temp - 0.5;
		DIVF32_S1i[i] = (unsigned long) (-temp);

		#if DIV_TABLE_SIZE == 128
		// Store S2 as +ve Q18 value:
		temp = S2_f64 * 262144.0;
		#endif
		#if DIV_TABLE_SIZE == 256
		// Store S2 as +ve Q16 value:
		temp = S2_f64 * 65536.0;
		#endif
		if( temp >= 0.0)
			temp = temp + 0.5;
		else
			temp = temp - 0.5;
		DIVF32_S2i[i] = (unsigned long) temp;

		// Increment X for next table entry:
		X0_f64 = X2_f64;
		X1_f64 = X0_f64 + dx0_f64;		
		X2_f64 = X1_f64 + dx0_f64;
		}

	if(PRINT_DIV_TABLE == 1)
		{
		fprintf(OutPtr,"\n\nStart Of Coefficients Table:\n");
		for(i=0; i < DIV_TABLE_SIZE; i++)
			{
			fprintf(OutPtr,"\n%4d | X0 = %16.12f,  X2 = %16.12f | Y0 = %16.12f   S1 = %16.12f   S2 = %16.12f | Y0i = %16lu   S1i = %16lu   S2i = %16lu", i, DIVF32_X0[i].f32, DIVF32_X2[i].f32, DIVF32_Y0[i].f32, DIVF32_S1[i].f32, DIVF32_S2[i].f32, DIVF32_Y0i[i], DIVF32_S1i[i], DIVF32_S2i[i]);
			}
		fprintf(OutPtr,"\n\nEnd of data.\n");
		}
}

/*
// This version uses Newton Raphson expansion:
void DIVF32_Generate_Coefficients(void)
{
	unsigned int i;
    // <<VC161025: had to change long double to double for the entire file>>
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

	double		X0_2_f64;
	double		X0_3_f64;
	double		X0_4_f64;
	double		X0_5_f64;
	double		X0_6_f64;

	X0_f64  =  1.0;					    // 1.0

	#if DIV_TABLE_SIZE == 128
	dx0_f64 =  0.00390625;				// 1/(DIV_TABLE_SIZE * 2)
	#endif
	#if DIV_TABLE_SIZE == 256
	dx0_f64 =  0.001953125;			    // 1/(DIV_TABLE_SIZE * 2)
	#endif

	X1_f64  = X0_f64 + dx0_f64;		

	for(i=0; i < DIV_TABLE_SIZE; i++)
		{
		// Increment X0:
		DIVF32_X0[i].f32 = (float) X1_f64;
		
		// Initialize 64-bit float values for intermediate calculations:
		Y0_f64 = 1.0 / X0_f64;
		Y1_f64 = 1.0 / X1_f64;

		Y0_2_f64 = Y0_f64 * Y0_f64;
		Y0_3_f64 = Y0_2_f64 * Y0_f64;
		Y0_4_f64 = Y0_3_f64 * Y0_f64;
		Y0_5_f64 = Y0_4_f64 * Y0_f64;
		Y0_6_f64 = Y0_5_f64 * Y0_f64;
		Y0_7_f64 = Y0_6_f64 * Y0_f64;
		Y0_8_f64 = Y0_7_f64 * Y0_f64;

		X0_2_f64 = X0_f64 * X0_f64;
		X0_3_f64 = X0_2_f64 * X0_f64;
		X0_4_f64 = X0_3_f64 * X0_f64;
		X0_5_f64 = X0_4_f64 * X0_f64;
		X0_6_f64 = X0_5_f64 * X0_f64;

		// Calculate using orginal equations:
		C1_f64 = -(6.0*Y0_2_f64 - 8.0*Y0_3_f64*X0_f64 + 3.0*Y0_4_f64*X0_2_f64);
		C2_f64 = 4.0*Y0_3_f64 - 3.0*Y0_4_f64*X0_f64;
		C3_f64 = -(Y0_4_f64);

		// Calculate using more accurate equations:
//		C1_f64 = -28.0*Y0_2_f64 + 112.0*Y0_3_f64*X0_f64 - 210.0*Y0_4_f64*X0_2_f64 + 224.0*Y0_5_f64*X0_3_f64 - 140.0*Y0_6_f64*X0_4_f64 + 48.0*Y0_7_f64*X0_5_f64 - 7.0*Y0_8_f64*X0_6_f64;
//		C2_f64 =  56.0*Y0_3_f64 - 210.0*Y0_4_f64*X0_f64 + 336.0*Y0_5_f64*X0_2_f64 - 280.0*Y0_6_f64*X0_3_f64 + 120.0*Y0_7_f64*X0_4_f64 - 21.0*Y0_8_f64*X0_5_f64;
//		C3_f64 = -70.0*Y0_4_f64 + 224.0*Y0_5_f64*X0_f64 - 280.0*Y0_6_f64*X0_2_f64 + 160.0*Y0_7_f64*X0_3_f64 -  35.0*Y0_8_f64*X0_4_f64;

		// S1 = C1 + 2*dx0*C2 + 3*dx0*dx0*C3
		S1_f64 = C1_f64 + 2.0*dx0_f64*C2_f64 + 3.0*dx0_f64*dx0_f64*C3_f64;
		// S2 = C2 + 3*dx0*C3
		S2_f64 = C2_f64 + 3*dx0_f64*C3_f64;

		DIVF32_Y0[i].f32 = (float) Y1_f64;
		DIVF32_S1[i].f32 = (float) S1_f64;
		DIVF32_S2[i].f32 = (float) S2_f64;

		// Fudge factors to improve accuracy:
		#if DIV_TABLE_SIZE == 128
		Y1_f64 = Y1_f64 * 1.0;
		S1_f64 = S1_f64 * 1.0000109;
		S2_f64 = S2_f64 * 1.0001;
		#endif
		#if DIV_TABLE_SIZE == 256
		Y1_f64 = Y1_f64 * 1.0;
		S1_f64 = S1_f64 * 1.0;
		S2_f64 = S2_f64 * 1.0;
		#endif

		// Store Y0 as +ve Q32 value + rounding:
		temp = Y1_f64 * 4294967296.0;
		if( temp >= 0.0)
			temp = temp + 0.5;
		else
			temp = temp - 0.5;
		DIVF32_Y0i[i] = (unsigned long) (temp + (1 << 7));
			
		#if DIV_TABLE_SIZE == 128
		// Store S1 as +ve Q24 value:
		temp = S1_f64 * 16777216.0;
		#endif
		#if DIV_TABLE_SIZE == 256
		// Store S1 as +ve Q23 value:
		temp = S1_f64 * 8388608.0;
		#endif
		if( temp >= 0.0)
			temp = temp + 0.5;
		else
			temp = temp - 0.5;
		DIVF32_S1i[i] = (unsigned long) (-temp);

		#if DIV_TABLE_SIZE == 128
		// Store S2 as +ve Q18 value:
		temp = S2_f64 * 262144.0;
		#endif
		#if DIV_TABLE_SIZE == 256
		// Store S1 as +ve Q16 value:
		temp = S2_f64 * 65536.0;
		#endif
		if( temp >= 0.0)
			temp = temp + 0.5;
		else
			temp = temp - 0.5;
		DIVF32_S2i[i] = (unsigned long) temp;

		// Increment X for next table entry:
		#if DIV_TABLE_SIZE == 128
		X0_f64 = X0_f64 + 0.0078125;		// X0 = X0 + 1.0/(DIV_TABLE_SIZE = 128)
		X1_f64 = X1_f64 + 0.0078125;		// X1 = X1 + 1.0/(DIV_TABLE_SIZE = 128)
		#endif
		#if DIV_TABLE_SIZE == 256
		X0_f64 = X0_f64 + 0.00390625;		// X0 = X0 + 1.0/(DIV_TABLE_SIZE = 256)
		X1_f64 = X1_f64 + 0.00390625;		// X1 = X1 + 1.0/(DIV_TABLE_SIZE = 256)
		#endif
		}

	if(PRINT_DIV_TABLE == 1)
		{
		fprintf(OutPtr,"\n\nStart Of Coefficients Table:\n");
		for(i=0; i < DIV_TABLE_SIZE; i++)
			{
			fprintf(OutPtr,"\n%4d | X0 = %16.12f | Y0 = %16.12f   S1 = %16.12f   S2 = %16.12f | Y0i = %16u   S1i = %16d   S2i = %16d", i, DIVF32_X0[i].f32, DIVF32_Y0[i].f32, DIVF32_S1[i].f32, DIVF32_S2[i].f32, DIVF32_Y0i[i], DIVF32_S1i[i], DIVF32_S2i[i]);
			}
		fprintf(OutPtr,"\n\nEnd of data.\n");
		}
}
*/

// End of file
