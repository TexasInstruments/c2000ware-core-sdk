//*****************************************************************************
//
// FILE:     TMU_Test1_QUADF32.cpp
//
// TITLE:    Utility To Test TMU QUADF32 Algorithms, Table Size = 128
//
//*****************************************************************************
//
// DESIGNED:  Alex Tessarolo
// LOCATION:  Texas Instruments
//
// HISTORY:		
//
//  ver  | dd-mmm-yyyy | Who     | Changes.
//  =====|=============|=========|============================================
//  1.0  | 02-May-2012 | Alex T. | Original Release.
//  -----|-------------|---------|--------------------------------------------
//
//*****************************************************************************
// COMPILER:  This utility was compiled using Microsft Visual C++ Express
//            in Win32 console mode. 
//=============================================================================
// QUADF32 TMU Algorithm Description:
//=============================================================================
//
//===========================================================================

#include "stdafx.h"

#define	VERSION	"1.0"

#include <math.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include <conio.h>
#include <dos.h>                  
#include <time.h> 
                            
FILE	*OutPtr;
char	OutputFileName[40];

typedef	union {
	float			f32;	
	unsigned long	ui32;
	long			i32;
} F32_UI32;

F32_UI32	X;
F32_UI32	Z;
F32_UI32	Y1;
F32_UI32	Y3;
F32_UI32	Y4;
F32_UI32	Q1;
F32_UI32	Q3;

long double	Y1QuadrantF64;
long double	Y1RatioF64;
long double	Y3QuadrantF64;
long double Y3RatioF64;
long double Y3ErrorPosF64;
long double Y3ErrorNegF64;

typedef _int64	i64;

#define	TABLE_SIZE		256								// 128 or 256 are only valid values

#define PRINT_TABLE		1								// 1 = Print Table, 0 = Don't Print

#define PI				3.14159265359L

#define	Q_RESULT		24								// Q24, Q25, Q26,..
#define	Q_SCALE			(long double) (1 << Q_RESULT)

F32_UI32		DIVF32_X0[TABLE_SIZE];
F32_UI32		DIVF32_X2[TABLE_SIZE];
F32_UI32		DIVF32_Y0[TABLE_SIZE];
F32_UI32		DIVF32_S1[TABLE_SIZE];
F32_UI32		DIVF32_S2[TABLE_SIZE];
unsigned long	DIVF32_Y0i[TABLE_SIZE];
unsigned long	DIVF32_S1i[TABLE_SIZE];
unsigned long	DIVF32_S2i[TABLE_SIZE];

void		PrintResult(void);
void		DIVF32_Generate_Coefficients(void);
void		QUADF32_CheckError(F32_UI32 Z, F32_UI32 X);
void		QUADF32_Test(void);
float		QUADF32_Hardware_Emulation(float Z, float X, float *Q);

//===========================================================================
// Start Of Program: main
//===========================================================================

int _tmain(int argc, _TCHAR* argv[])
{        
 	printf("\nTest TMU DIVF32 Algorithms, Version %s, Table Size %3d", VERSION, TABLE_SIZE);
	printf("\nCopyright (c) Texas Instruments Inc. 2010-2011");

	sprintf(OutputFileName, "QUADF32_Results_float_Q%2d_TableSize%3d.txt", Q_RESULT, TABLE_SIZE);
 
 	if( (OutPtr = fopen(OutputFileName, "w+")) == NULL )
		{  
		printf("\n");
		printf("\nERROR: Could Not Open %s File For Output.", _strupr(OutputFileName));
		printf("\n");
		exit(0);
 		}           

  	fprintf(OutPtr,  ";;##########################################################################");
	fprintf(OutPtr,"\n;;");
	fprintf(OutPtr,"\n;;Title:     TMU QUADF32 Algorithm Test Results");
	fprintf(OutPtr,"\n;;");
	fprintf(OutPtr,"\n;;Version:   %s", VERSION );
	fprintf(OutPtr,"\n;;");
	fprintf(OutPtr,"\n;;TableSize: %3d", TABLE_SIZE );
	fprintf(OutPtr,"\n;;");
	fprintf(OutPtr,"\n;;##########################################################################");
	fprintf(OutPtr,"\n");
	fprintf(OutPtr,"\n");

	// Run algorithm:
	DIVF32_Generate_Coefficients();
	QUADF32_Test();

	fprintf(OutPtr,"\n");
	fprintf(OutPtr,"\n;;");
	fprintf(OutPtr,"\n;; End Of File.");
	fprintf(OutPtr,"\n;;");
	fprintf(OutPtr,"\n");

	printf("\n");
 	printf("\nDone! Generated %s File.", _strupr(OutputFileName) );
 	printf("\n");
  		
 	fcloseall();
	exit(0); 		
} 		                                                           

//===========================================================================
// DIVF32 Test Programs:
//===========================================================================

void QUADF32_CheckError(F32_UI32 Z, F32_UI32 X)
{
	long double X_f64;
	long double Z_f64;

	// Generate Precise Reefernce Value Y1:
	X_f64 = (long double) X.f32;
	Z_f64 = (long double) Z.f32;

	if( (fabs(X_f64) == 0.0L) & (fabs(Z_f64) == 0) )
		{
		Y1QuadrantF64 = 0.0L;
		Y1RatioF64 = 0.0L;
		}
	else if( fabs(Z_f64) <= fabs(X_f64) )
		{
		Y1RatioF64 = Z_f64 / X_f64;
		if( X_f64 >= 0.0L )
			Y1QuadrantF64 = 0.0L;
		else
			{
			if( Z_f64 >= 0.0L )
				Y1QuadrantF64 = 0.5L;
			else
				Y1QuadrantF64 = -0.5L;
			}
		}
	else
		{
		if( Z_f64 >= 0.0L )
			Y1QuadrantF64 = 0.25L;
		else
			Y1QuadrantF64 = -0.25L;
		Y1RatioF64 = - (X_f64 / Z_f64);
		}

	// Calculate Hardware Emulation Value Y3:
	Y3.f32 = QUADF32_Hardware_Emulation(Z.f32, X.f32, &Q3.f32);

	Y3ErrorPosF64 = 0.0L;
	if(Y1RatioF64 > ((long double) Y3.f32))
		{
		Y3ErrorPosF64 = Y1RatioF64 - ((long double) Y3.f32);
		}
	if(Y1RatioF64 < ((long double) Y3.f32))
		{
		Y3ErrorNegF64 = ((long double) Y3.f32) - Y1RatioF64;
		}
}

void PrintResult(void)
{
	fprintf(OutPtr,"\n\nZ input                      :     > %16.14f", Z.f32 );
	fprintf(OutPtr,"\nX input                      :     > %16.14f", X.f32 );
	fprintf(OutPtr,"\nReference Ratio              :     > %16.14f", Y1RatioF64 );
	fprintf(OutPtr,"\nHardware  Ratio              :     > %16.14f", Y3.f32 );
	fprintf(OutPtr,"\nError For Hardware Emulation : pos > %16.14f", (Y3ErrorPosF64 * Q_SCALE) );
	fprintf(OutPtr,"\n                             : neg > %16.14f", (Y3ErrorNegF64 * Q_SCALE) );
	fprintf(OutPtr,"\nReference Quadrant           :     > %16.14f", Y1QuadrantF64 );
	fprintf(OutPtr,"\nHardware  Quadrant           :     > %16.14f", Q3.f32 );
}

void QUADF32_Test(void)
{
	int		i;
	float	temp;

	fprintf(OutPtr,"\nSummary Of Errors With Respect To Precise Reference Value:");
	fprintf(OutPtr,"\n\nTesting: QUADF32, Table Size = %4d, Q Scaling = Q%2d", TABLE_SIZE, Q_RESULT);
	fprintf(OutPtr,"\n===========================================================================\n");


	printf("\nTest QUADF32 Using Q%2d Scaling, Return (float)", Q_RESULT);

	printf("\nCheck Values Around Full Circle:");
	fprintf(OutPtr,"\n\n\nCheck Values Around Full Circle:");

	// 0 Deg, radius = 0.0
	Z.f32 = 0.0L;
	X.f32 = 0.0L;
	QUADF32_CheckError(Z, X);
	PrintResult();

	// 0 Deg, radius = 0.0
	Z.f32 = 0.0L;
	X.ui32 = 0x80000000L;		// X = -0.0
	QUADF32_CheckError(Z, X);
	PrintResult();

	// 0 Deg, radius = 0.0
	Z.ui32 = 0x80000000L;		// Z = -0.0
	X.f32 = 0.0L;
	QUADF32_CheckError(Z, X);
	PrintResult();

	// 0 Deg, radius = 0.0
	Z.ui32 = 0x80000000L;		// Z = -0.0
	X.ui32 = 0x80000000L;		// X = -0.0
	QUADF32_CheckError(Z, X);
	PrintResult();

	// 0 Deg, radius = 0.7776
	Z.f32 = 0.0L;
	X.f32 = 0.7776L;
	QUADF32_CheckError(Z, X);
	PrintResult();

	// 0 Deg, radius = 0.7776
	Z.ui32 = 0x80000000L;		// Z = -0.0
	X.f32 = 0.7776L;
	QUADF32_CheckError(Z, X);
	PrintResult();

	// 15 Deg, radius = 0.7776
	Z.f32 = 0.2012576894718L;
	X.f32 = 0.7511039225224L;
	QUADF32_CheckError(Z, X);
	PrintResult();

	// 30 Deg, radius = 0.7776
	Z.f32 = 0.388L;
	X.f32 = 0.6734213539827L;
	QUADF32_CheckError(Z, X);
	PrintResult();

	// 45 Deg, radius = 0.7776
	Z.f32 = 0.5498462330507L;
	X.f32 = 0.5498462330507L;
	QUADF32_CheckError(Z, X);
	PrintResult();

	// 60 Deg, radius = 0.7776
	Z.f32 = 0.6734213539827L;
	X.f32 = 0.388L;
	QUADF32_CheckError(Z, X);
	PrintResult();

	// 75 Deg, radius = 0.7776
	Z.f32 = 0.7511039225224L;
	X.f32 = 0.2012576894718L;
	QUADF32_CheckError(Z, X);
	PrintResult();

	// 90 Deg, radius = 0.7776
	Z.f32 = 0.7776L;
	X.f32 = 0.0;
	QUADF32_CheckError(Z, X);
	PrintResult();

	// 90 Deg, radius = 0.7776
	Z.f32 = 0.7776L;
	X.ui32 = 0x80000000L;		// X = -0.0
	QUADF32_CheckError(Z, X);
	PrintResult();

	// 105 Deg, radius = 0.7776
	Z.f32 = 0.7511039225224L;
	X.f32 = -0.2012576894718L;
	QUADF32_CheckError(Z, X);
	PrintResult();

	// 120 deg, radius = 0.7776
	Z.f32 = 0.6734213539827L;
	X.f32 = -0.388L;
	QUADF32_CheckError(Z, X);
	PrintResult();

	// 135 Deg, radius = 0.7776
	Z.f32 = 0.5498462330507L;
	X.f32 = -0.5498462330507L;
	QUADF32_CheckError(Z, X);
	PrintResult();

	// 150 Deg, radius = 0.7776
	Z.f32 = 0.388L;
	X.f32 = -0.6734213539827L;
	QUADF32_CheckError(Z, X);
	PrintResult();

	// 165 Deg, radius = 0.7776
	Z.f32 = 0.2012576894718L;
	X.f32 = -0.7511039225224L;
	QUADF32_CheckError(Z, X);
	PrintResult();

	// 180 Deg, radius = 0.7776
	Z.f32 = 0.0;
	X.f32 = -0.7776L;
	QUADF32_CheckError(Z, X);
	PrintResult();

	// 180 Deg, radius = 0.7776
	Z.ui32 = 0x80000000L;		// Z = -0.0
	X.f32 = -0.7776L;
	QUADF32_CheckError(Z, X);
	PrintResult();

	// 195 Deg, radius = 0.7776
	Z.f32 = -0.2012576894718L;
	X.f32 = -0.7511039225224L;
	QUADF32_CheckError(Z, X);
	PrintResult();

	// 210 Deg, radius = 0.7776
	Z.f32 = -0.388L;
	X.f32 = -0.6734213539827L;
	QUADF32_CheckError(Z, X);
	PrintResult();

	// 225 Deg, radius = 0.7776
	Z.f32 = -0.5498462330507L;
	X.f32 = -0.5498462330507L;
	QUADF32_CheckError(Z, X);
	PrintResult();

	// 240 deg, radius = 0.7776
	Z.f32 = -0.6734213539827L;
	X.f32 = -0.388L;
	QUADF32_CheckError(Z, X);
	PrintResult();

	// 255 Deg, radius = 0.7776
	Z.f32 = -0.7511039225224L;
	X.f32 = -0.2012576894718L;
	QUADF32_CheckError(Z, X);
	PrintResult();

	// 270 Deg, radius = 0.7776
	Z.f32 = -0.7776L;
	X.f32 =  0.0;
	QUADF32_CheckError(Z, X);
	PrintResult();

	// 270 Deg, radius = 0.7776
	Z.f32 = -0.7776L;
	X.ui32 = 0x80000000L;		// X = -0.0
	QUADF32_CheckError(Z, X);
	PrintResult();

	// 285 Deg, radius = 0.7776
	Z.f32 = -0.7511039225224L;
	X.f32 = 0.2012576894718L;
	QUADF32_CheckError(Z, X);
	PrintResult();

	// 300 Deg, radius = 0.7776
	Z.f32 = -0.6734213539827L;
	X.f32 = 0.388L;
	QUADF32_CheckError(Z, X);
	PrintResult();

	// 315 Deg, radius = 0.7776
	Z.f32 = -0.5498462330507L;
	X.f32 = 0.5498462330507L;
	QUADF32_CheckError(Z, X);
	PrintResult();

	// 330 Deg, radius = 0.7776
	Z.f32 = -0.388L;
	X.f32 = 0.6734213539827L;
	QUADF32_CheckError(Z, X);
	PrintResult();

	// 345 Deg, radius = 0.7776
	Z.f32 = -0.2012576894718L;
	X.f32 = 0.7511039225224L;
	QUADF32_CheckError(Z, X);
	PrintResult();
}

//===========================================================================
// DIVF32 Coefficient Table Generator:
//===========================================================================

// This version uses 2nd oder polynomial approximation:
void DIVF32_Generate_Coefficients(void)
{
	int	i;

	long double		dx0_f64;
	long double		X0_f64;
	long double		X1_f64;
	long double		X2_f64;
	long double		Y0_f64;
	long double		S1_f64;
	long double		S2_f64;
	long double		temp;
	
    long double		c12, c13, b1;
	long double		c22, c23, b2;
	long double		c32, c33, b3;
	long double		a0, a1, a2;

	X0_f64  =  1.0L;

	#if TABLE_SIZE == 128
	dx0_f64 =  0.00390625L;				// 1/(TABLE_SIZE * 2)
	#endif
	#if TABLE_SIZE == 256
	dx0_f64 =  0.001953125L;			// 1/(TABLE_SIZE * 2)
	#endif

	X1_f64  = X0_f64 + dx0_f64;		
	X2_f64  = X1_f64 + dx0_f64;

	for(i=0; i < TABLE_SIZE; i++)
		{
		c12 = X0_f64;
		c13 = X0_f64 * X0_f64;
		b1  = 1.0L / X0_f64;
		c22 = X1_f64;
		c23 = X1_f64 * X1_f64;
		b2  = 1.0L / X1_f64;
		c32 = X2_f64;
		c33 = X2_f64 * X2_f64;
		b3  = 1.0L / X2_f64;

		a2 = ((b2-b1)*(c32-c12) - (b3-b1)*(c22-c12))/((c13-c33)*(c22-c12) - (c13-c23)*(c32-c12));
		a1 = ((b3-b1) + a2*(c13-c33))/(c32-c12);
		a0 = b1 - a1*c12 - a2*c13;
		
		//  Y0 = (1/2PI) * (a0 + a1*(X0 + dx0) + a2*(X0 + dx0)^2)
		//  S1 = (1/2PI) * (a1 + 2*a2*(X0+dx0))
		//  S2 = (1/2PI) * (a2)
		Y0_f64 = a0 + a1*X1_f64 + a2*X1_f64*X1_f64;
		S1_f64 = a1 + 2.0L*a2*X1_f64;
		S2_f64 = a2;

		// Fudge factors to improve accuracy:
		#if TABLE_SIZE == 128
		Y0_f64 = Y0_f64 * 1.0L;
		S1_f64 = S1_f64 * 0.999995L;
		S2_f64 = S2_f64 * 1.0L;
		#endif
		#if TABLE_SIZE == 256
		Y0_f64 = Y0_f64 * 1.0L;
		S1_f64 = S1_f64 * 1.0L;
		S2_f64 = S2_f64 * 1.0L;
		#endif

		DIVF32_X0[i].f32 = (float) X0_f64;
		DIVF32_X2[i].f32 = (float) X2_f64;
		DIVF32_Y0[i].f32 = (float) Y0_f64;
		DIVF32_S1[i].f32 = (float) S1_f64;
		DIVF32_S2[i].f32 = (float) S2_f64;

		// Store Y0 as +ve Q32 value + rounding:
		temp = Y0_f64 * 4294967296.0L;
		if( temp >= 0.0)
			temp = temp + 0.5L;
		else
			temp = temp - 0.5L;
		DIVF32_Y0i[i] = (unsigned long) (temp + (1 << 7));
			
		#if TABLE_SIZE == 128
		// Store S1 as +ve Q24 value:
		temp = S1_f64 * 16777216.0L;
		#endif
		#if TABLE_SIZE == 256
		// Store S1 as +ve Q23 value:
		temp = S1_f64 * 8388608.0L;
		#endif
		if( temp >= 0.0)
			temp = temp + 0.5L;
		else
			temp = temp - 0.5L;
		DIVF32_S1i[i] = (unsigned long) (-temp);

		#if TABLE_SIZE == 128
		// Store S2 as +ve Q18 value:
		temp = S2_f64 * 262144.0L;
		#endif
		#if TABLE_SIZE == 256
		// Store S2 as +ve Q16 value:
		temp = S2_f64 * 65536.0L;
		#endif
		if( temp >= 0.0)
			temp = temp + 0.5L;
		else
			temp = temp - 0.5L;
		DIVF32_S2i[i] = (unsigned long) temp;

		// Increment X for next table entry:
		X0_f64 = X2_f64;
		X1_f64 = X0_f64 + dx0_f64;		
		X2_f64 = X1_f64 + dx0_f64;
		}

	if(PRINT_TABLE == 1)
		{
		fprintf(OutPtr,"\n\nStart Of Coefficients Table:\n");
		for(i=0; i < TABLE_SIZE; i++)
			{
			fprintf(OutPtr,"\n%4d | X0 = %16.12f,  X2 = %16.12f | Y0 = %16.12f   S1 = %16.12f   S2 = %16.12f | Y0i = %16u   S1i = %16u   S2i = %16u", i, DIVF32_X0[i].f32, DIVF32_X2[i].f32, DIVF32_Y0[i].f32, DIVF32_S1[i].f32, DIVF32_S2[i].f32, DIVF32_Y0i[i], DIVF32_S1i[i], DIVF32_S2i[i]);
			}
		fprintf(OutPtr,"\n\nEnd of data.\n");
		}
}

/*
// This version uses Newton Raphson expansion:
void DIVF32_Generate_Coefficients(void)
{
	unsigned int i;
	long double		X0_f64;
	long double		X1_f64;
	long double		Y0_f64;
	long double		Y1_f64;
	long double		S1_f64;
	long double		S2_f64;
	long double		C1_f64;
	long double		C2_f64;
	long double		C3_f64;
	long double		dx0_f64;
	long double		temp;

	long double		Y0_2_f64;
	long double		Y0_3_f64;
	long double		Y0_4_f64;
	long double		Y0_5_f64;
	long double		Y0_6_f64;
	long double		Y0_7_f64;
	long double		Y0_8_f64;

	long double		X0_2_f64;
	long double		X0_3_f64;
	long double		X0_4_f64;
	long double		X0_5_f64;
	long double		X0_6_f64;

	X0_f64  =  1.0L;					// 1.0

	#if TABLE_SIZE == 128
	dx0_f64 =  0.00390625L;				// 1/(TABLE_SIZE * 2)
	#endif
	#if TABLE_SIZE == 256
	dx0_f64 =  0.001953125L;			// 1/(TABLE_SIZE * 2)
	#endif

	X1_f64  = X0_f64 + dx0_f64;		

	for(i=0; i < TABLE_SIZE; i++)
		{
		// Increment X0:
		DIVF32_X0[i].f32 = (float) X1_f64;
		
		// Initialize 64-bit float values for intermediate calculations:
		Y0_f64 = 1.0L / X0_f64;
		Y1_f64 = 1.0L / X1_f64;

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
		C1_f64 = -(6.0L*Y0_2_f64 - 8.0L*Y0_3_f64*X0_f64 + 3.0L*Y0_4_f64*X0_2_f64);
		C2_f64 = 4.0L*Y0_3_f64 - 3.0L*Y0_4_f64*X0_f64;
		C3_f64 = -(Y0_4_f64);

		// Calculate using more accurate equations:
//		C1_f64 = -28.0L*Y0_2_f64 + 112.0L*Y0_3_f64*X0_f64 - 210.0L*Y0_4_f64*X0_2_f64 + 224.0*Y0_5_f64*X0_3_f64 - 140.0L*Y0_6_f64*X0_4_f64 + 48.0L*Y0_7_f64*X0_5_f64 - 7.0L*Y0_8_f64*X0_6_f64;
//		C2_f64 =  56.0L*Y0_3_f64 - 210.0L*Y0_4_f64*X0_f64 + 336.0L*Y0_5_f64*X0_2_f64 - 280.0*Y0_6_f64*X0_3_f64 + 120.0L*Y0_7_f64*X0_4_f64 - 21.0L*Y0_8_f64*X0_5_f64;
//		C3_f64 = -70.0L*Y0_4_f64 + 224.0L*Y0_5_f64*X0_f64 - 280.0L*Y0_6_f64*X0_2_f64 + 160.0*Y0_7_f64*X0_3_f64 -  35.0L*Y0_8_f64*X0_4_f64;

		// S1 = C1 + 2*dx0*C2 + 3*dx0*dx0*C3
		S1_f64 = C1_f64 + 2.0L*dx0_f64*C2_f64 + 3.0L*dx0_f64*dx0_f64*C3_f64;
		// S2 = C2 + 3*dx0*C3
		S2_f64 = C2_f64 + 3*dx0_f64*C3_f64;

		DIVF32_Y0[i].f32 = (float) Y1_f64;
		DIVF32_S1[i].f32 = (float) S1_f64;
		DIVF32_S2[i].f32 = (float) S2_f64;

		// Fudge factors to improve accuracy:
		#if TABLE_SIZE == 128
		Y1_f64 = Y1_f64 * 1.0L;
		S1_f64 = S1_f64 * 1.0000109L;
		S2_f64 = S2_f64 * 1.0001L;
		#endif
		#if TABLE_SIZE == 256
		Y1_f64 = Y1_f64 * 1.0L;
		S1_f64 = S1_f64 * 1.0L;
		S2_f64 = S2_f64 * 1.0L;
		#endif

		// Store Y0 as +ve Q32 value + rounding:
		temp = Y1_f64 * 4294967296.0L;
		if( temp >= 0.0)
			temp = temp + 0.5L;
		else
			temp = temp - 0.5L;
		DIVF32_Y0i[i] = (unsigned long) (temp + (1 << 7));
			
		#if TABLE_SIZE == 128
		// Store S1 as +ve Q24 value:
		temp = S1_f64 * 16777216.0L;
		#endif
		#if TABLE_SIZE == 256
		// Store S1 as +ve Q23 value:
		temp = S1_f64 * 8388608.0L;
		#endif
		if( temp >= 0.0)
			temp = temp + 0.5L;
		else
			temp = temp - 0.5L;
		DIVF32_S1i[i] = (unsigned long) (-temp);

		#if TABLE_SIZE == 128
		// Store S2 as +ve Q18 value:
		temp = S2_f64 * 262144.0L;
		#endif
		#if TABLE_SIZE == 256
		// Store S1 as +ve Q16 value:
		temp = S2_f64 * 65536.0L;
		#endif
		if( temp >= 0.0)
			temp = temp + 0.5L;
		else
			temp = temp - 0.5L;
		DIVF32_S2i[i] = (unsigned long) temp;

		// Increment X for next table entry:
		#if TABLE_SIZE == 128
		X0_f64 = X0_f64 + 0.0078125L;		// X0 = X0 + 1.0/(TABLE_SIZE = 128)
		X1_f64 = X1_f64 + 0.0078125L;		// X1 = X1 + 1.0/(TABLE_SIZE = 128)
		#endif
		#if TABLE_SIZE == 256
		X0_f64 = X0_f64 + 0.00390625L;		// X0 = X0 + 1.0/(TABLE_SIZE = 256)
		X1_f64 = X1_f64 + 0.00390625L;		// X1 = X1 + 1.0/(TABLE_SIZE = 256)
		#endif
		}

	if(PRINT_TABLE == 1)
		{
		fprintf(OutPtr,"\n\nStart Of Coefficients Table:\n");
		for(i=0; i < TABLE_SIZE; i++)
			{
			fprintf(OutPtr,"\n%4d | X0 = %16.12f | Y0 = %16.12f   S1 = %16.12f   S2 = %16.12f | Y0i = %16u   S1i = %16d   S2i = %16d", i, DIVF32_X0[i].f32, DIVF32_Y0[i].f32, DIVF32_S1[i].f32, DIVF32_S2[i].f32, DIVF32_Y0i[i], DIVF32_S1i[i], DIVF32_S2i[i]);
			}
		fprintf(OutPtr,"\n\nEnd of data.\n");
		}
}
*/

//===========================================================================
// QUADF32 Algorithms:
//===========================================================================

float QUADF32_Hardware_Emulation(float Z, float X, float *Q)
{
	F32_UI32		tempX;	
	F32_UI32		tempZ;	
	F32_UI32		Y;
	long			dx;
	long			temp;
	i64				dx_dx;
	i64				dx_dx_S2;
	i64				dx_S1;
	i64				sum;
	i64				dx_S1_ADD_dx_dx_S2;
	i64				dx_S1_SUB_dx_dx_S2;
	unsigned int	table_index;
	i64				Y0i;
	i64				S2i;
	i64				S1i;

	unsigned long	Sx;		// Bit  31    Sign     Of Input Value
	unsigned long	Ex;		// Bits 30:23 Exponent Of Input Value
	unsigned long	Mx;		// Bits 22:0  Mantissa Of Input Value
	unsigned long	So;		// Bit  31    Sign     Of Output Value
	unsigned long	Eo;		// Bits 30:23 Exponent Of Output Value
	unsigned long	Mo;		// Bits 22:0  Mantissa Of Output Value
	unsigned long	Sz;		// Bit  31    Sign     Of Numerator Value
	unsigned long	Ez;		// Bits 30:23 Exponent Of Numerator Value
	unsigned long	Mz;		// Bits 22:0  Mantissa Of Numerator Value


	unsigned int	Boundary;	// 0 = none;
								// 1 = return boundary condition value

	//----------------------------------------------------------------------------------------------------------------------------
	// Pipeline Phase 1: Format input and extract table_index and dx value:

	// Extract sign, exp and mantissa of input:
	tempX.f32 = X;
	Sx = (tempX.ui32 & 0x80000000);
	Ex = (tempX.ui32 & 0x7F800000);
	Mx = (tempX.ui32 & 0x007FFFFF);

	// Extract sign, exp and mantissa of Numerator:
	tempZ.f32 = Z;
	Sz = (tempZ.ui32 & 0x80000000);
	Ez = (tempZ.ui32 & 0x7F800000);
	Mz = (tempZ.ui32 & 0x007FFFFF);

	//	if( (fabs(X_f64) == 0.0L) & (fabs(Z_f64) == 0) )
	//		{
	//		Y1QuadrantF64 = 0.0L;
	//		Y1RatioF64 = 0.0L;
	//		}
	//	else if( fabs(Z_f64) <= fabs(X_f64) )
	//		{
	//		Y1RatioF64 = Z_f64 / X_f64;
	//		if( X_f64 >= 0.0L )
	//			Y1QuadrantF64 = 0.0L;
	//		else
	//			{
	//			if( Z_f64 >= 0.0L )
	//				Y1QuadrantF64 = 0.5L;
	//			else
	//				Y1QuadrantF64 = -0.5L;
	//			}
	//		}
	//	else
	//		{
	//		if( Z_f64 >= 0.0L )
	//			Y1QuadrantF64 = 0.25L;
	//		else
	//			Y1QuadrantF64 = -0.25L;
	//		Y1RatioF64 = X_f64 / Z_f64;
	//		}
	//

	// If input values are zero, negative zero or Denorm, force to zero:
	if( Ex == 0x00000000 )
		{
		Sx = 0x00000000;
		Mx = 0x00000000;
		}
	if( Ez == 0x00000000 )
		{
		Sz = 0x00000000;
		Mz = 0x00000000;
		}

	if( (Ez | Mz) <= (Ex | Mx) )
		{
		// Default Ratio = Z/X
		if( Sx == 0 )
			*Q = 0.0;
		else
			{
			if( Sz == 0 )
				*Q = 0.5;
			else
				*Q = -0.5;
			}
		}
	else
		{
		if( Sz == 0 )
			*Q = 0.25;
		else
			*Q = -0.25;
		// Swap Z and X, Ratio = X/Z
		So = Sz;
		Sz = Sx;
		Sx = So;
		Eo = Ez;
		Ez = Ex;
		Ex = Eo;
		Mo = Mz;
		Mz = Mx;
		Mx = Mo;

		// Invert sign of Z:
		Sz = Sz ^ 0x80000000;
		}

	// Set default values of data:
	dx = 0;
	Boundary = 0;
	table_index = 0;

	// If Z and X are zero, return zero:
	if( (Ex == 0x00000000) & (Ez == 0x00000000) )	
		{
		So = 0x00000000;
		Eo = 0x00000000;
		Mo = 0x00000000;
		Y.ui32 = So + Eo + Mo;
		*Q = 0.0;
		Boundary = 1;
		}
	// Check if Nan or infinity input. If so, generate zero and return:
	else if( Ex == 0x7F800000 )
		{
		So = 0x00000000;
		Eo = 0x00000000;
		Mo = 0x00000000;
		Y.ui32 = So + Eo + Mo;
		Boundary = 1;
		}
	// If input too big, return zero:
	else if( Ex == 0x7F000000 )
		{
		So = 0x00000000;
		Eo = 0x00000000;
		Mo = 0x00000000;
		Y.ui32 = So + Eo + Mo;
		Boundary = 1;
		}
	// Check if input is modulo of 2. If so, adjust exponent and return with value:
	else if( Mx == 0x00000000 )
		{
		So = Sx ^ Sz;	
		Eo = (0x3F800000L + Ez) - Ex;
		Mo = Mz;
		Y.ui32 = So + Eo + Mo;
		Boundary = 1;
		}
	else
		{
		// Generate sign bit and adjust exponent:
		So = Sx ^ Sz;	
		if( Mz == 0 )
			Eo = (0x3F000000L + Ez) - Ex;
		else
			Eo = (0x3F800000L + Ez) - Ex;

		// Extract table index and dx value:
		#if TABLE_SIZE == 128
		table_index = ((Mx & 0x007F0000L) >> 16);
		if( (Mx & 0x00008000L) == 0 )
			dx = (0xFFFF8000L ^ (Mx & 0x0000FFFFL)) << 9;			// Q33
		else
			dx = (0x00008000L ^ (Mx & 0x0000FFFFL)) << 9;			// Q33
		#endif
		#if TABLE_SIZE == 256
		table_index = ((Mx & 0x007F8000L) >> 15);
		if( (Mx & 0x00004000L) == 0 )
			dx = (0xFFFFC000L ^ (Mx & 0x00007FFFL)) << 10;			// Q33
		else
			dx = (0x00004000L ^ (Mx & 0x00007FFFL)) << 10;			// Q33
		#endif
		}

	//----------------------------------------------------------------------------------------------------------------------------
	// Pipeline Phase 2: Get ROM table values and calcualte dx*dx

	S2i	= (i64) DIVF32_S2i[table_index];	// 21.Q15, +ve number with only bits 0 to 20 are valid (S2i[20:0])
	S1i = (i64) DIVF32_S1i[table_index];	// 25.Q21, +ve number with only bits 0 to 24 are valid (S1i[24:0])
	Y0i = (i64) DIVF32_Y0i[table_index];	// 30.Q29, +ve number with only bits 0 to 29 are valid (Y0i[29:0])

	// Calculate: dx_dx = ((dx >> 10) * (dx >> 10)) >> 11;
	//
	// The input range of dx for DIVF32 is:
	//
	// max:  0x00FFFFFF
	//       ...
	//       0x00000001
	//       0x00000000
	//       0xFFFFFFFF
	//       ...
	//       0xFF000001
	//       0xFF000000
	//
	// For this multiplication, we only need to use 15 bits from dx (temp[14:0] = dx[25:10]):
	temp = (dx & 0x01FFFC00L) >> 10;

	// If dx is negative, then we negate the 15-bits and only keep lower 15-bits (temp[14:0]):
	// The scaled range of dx is now:
	// max = 0x00004000L
	//       0x00003FFFL
	//       ...
	//       0x00000001L
	// min = 0x00000000L
	if((temp & 0x00004000L) != 0)
		temp = ((temp ^ 0x00007FFFL) + 1) & 0x00007FFFL;

	// The multiplication performs a 15-bit * 15-bit multiply with 29-bit result (mpy_result[28:0] = temp[14:0] * temp[14:0]):
	// But we only keep 18-bits, from bits 11 to 28, of the result (dx_dx[17:0] =  mpy_result[28:11]):
	// The result range of dx_dx is:
	// max = 0x00004000L
	//       0x00003FFFL
	//       ...
	//       0x00000001L
	// min = 0x00000000L
	dx_dx = (i64) ((((temp & 0x00007FFFL) * (temp & 0x00007FFFL)) & 0x1FFFF800L) >> 11);

	//----------------------------------------------------------------------------------------------------------------------------
	// Pipeline Phases 3 & 4: Calculate output

	// Calculate:  dx_dx_S2  = (dx_dx * S2i) >> 18
	//
	// This operation performs a 18-bit * 20-bit multiply with a 38-bit result (mpy_result[37:0] = dx_dx[17:0] * S2i[19:0]):
	// But only the upper 20-bits of the mpy result are kept from bits 18 to 37 (dx_dx_S2[19:0] = mpy_result[37:18]):
	dx_dx_S2  = (((dx_dx & 0x000000000003FFFFL) * (S2i & 0x00000000000FFFFFL)) & 0x0000003FFFFC0000L) >> 18; 

	// Calculate:  dx_S1 = (dx * S1i) >> 23
	//
	// If dx is negative, then chage to positive value:
	// 
	// Note: Only first 25-bits of dx are valid:
	temp = dx & 0x01FFFFFFL;
	if((dx & 0x01000000L) != 0)
		temp = ((temp ^ 0x01FFFFFFL) + 1) & 0x01FFFFFFL;
		
	// This operation performs a 25-bit * 24-bit multiply with a 49-bit result (mpy_result[48:0] = dx[24:0] * S1i[23:0]):
	// But only the upper 26-bits of the mpy result are kept from bits 23 to 48 (dx_S1[25:0] = mpy_result[48:23]):
	dx_S1     =  (((((i64) temp) & 0x0000000001FFFFFFL) * (S1i & 0x0000000000FFFFFFL)) & 0x0001FFFFFF800000L) >> 23;

	// For SINF32 & COSF32 & SQRTF32 & ATANF32 calculate:
	//     sum = Y0i + ((dx_S1 - dx_dx_S2) >> 1)
	//
	//     Note: if( dx >= 0 )
	//              sum = Y0i + (round(dx_S1 - dx_dx_S2) >> 1)
	//           else
	//              sum = Y0i - (round(dx_S1 + dx_dx_S2) >> 1)
	//
	// For DIVF32 calculate:
	//     sum = Y0i - ((dx_S1 - dx_dx_S2) >> 1)
	//
	//     Note: if( dx >= 0 )
	//              sum = Y0i - (round(dx_S1 - dx_dx_S2) >> 1)
	//           else
	//              sum = Y0i + (round(dx_S1 + dx_dx_S2) >> 1)
	//    
	// Calculate: dx_S1_ADD_dx_dx_S2[26:0] = (((dx_S1[25:0] + dx_dx_S2[19:0]) + 1) >> 1) 
	dx_S1_ADD_dx_dx_S2 = (((dx_S1 + dx_dx_S2) + 1) >> 1); 
	// Calculate: dx_S1_SUB_dx_dx_S2[26:0] = (((dx_S1[25:0] - dx_dx_S2[19:0]) + 1) >> 1) 
	dx_S1_SUB_dx_dx_S2 = (((dx_S1 - dx_dx_S2) + 1) >> 1);

	if((dx & 0x01000000L) == 0)
		// if dx positive: perform 32-bit sub
		sum = Y0i - dx_S1_SUB_dx_dx_S2;		
	else
		// if dx negative: perform 32-bit add
		sum = Y0i + dx_S1_ADD_dx_dx_S2; 

	//----------------------------------------------------------------------------------------------------------------------------
	// Pipeline Phase 5: Format output
	if( Boundary != 0 )
		return	Y.f32;			// Return boundary condition value detected in Pipeline Phase 1
	else
		{
		if( Mz != 0 )
			{
			// Perform 25-bit by 24-bit multiply with 24-bit result (sum[23:0] = sum[31:7] * Mz[23:0]):
			sum  =  (((sum & 0x00000000FFFFFF80L) * (Mz | 0x00800000L)) & 0x00FFFFFF00000000L) >> 32;
			}
		else
			{
			// Scale back to 24-bit mantissa:
			sum = sum >> 8;				
			}

		// Should never get here, but just to make sure:
		// Mantissa should be in the range: of 1.0 to 0.5
		// 16777215 = 0x00FFFFFF = 0.9999999 in Q24 format
		// ...
		//  8388608 = 0x00800000 = 0.5000000 in Q24 format
		if(sum > 16777215)
			sum = 16777215;
		if(sum < 0)
			sum = 0;

		Mo = (unsigned long) (sum & 0x007FFFFFL);
	
		Y.ui32 = So + Eo + Mo;

		return 	Y.f32;
		}
}

//===========================================================================
// No more.
//===========================================================================
