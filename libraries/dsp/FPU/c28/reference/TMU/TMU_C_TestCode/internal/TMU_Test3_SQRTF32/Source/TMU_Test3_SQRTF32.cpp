//*****************************************************************************
//
// FILE:     TMU_Test3_SQRTF32.cpp
//
// TITLE:    Utility To Test TMU SQRTF32 Algorithms, Table Size = 128
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
//  3.0  | 30-Apr-2011 | Alex T. | Original Release.
//  -----|-------------|---------|--------------------------------------------
//
//*****************************************************************************
// COMPILER:  This utility was compiled using Microsft Visual C++ Express
//            in Win32 console mode. 
//=============================================================================
// SQRTF32 TMU Algorithm Description:
//=============================================================================
//
// Y = 1/sqrt(X)
// Y = Y0 + dy
// X = X0 + dx
//
// Y1 = 1.5*Y0 - 0.5*Y0^3*X
// Y  = 1.5*Y1 - 0.5*Y1^3*X
//
// Y  = 1.5*(1.5*Y0 - 0.5*Y0^3*X) - 0.5*(1.5*Y0 - 0.5*Y0^3*X)^3*X
// (1.5*Y0 - 0.5*Y0^3*X)^3 = (1.5*Y0 - 0.5*Y0^3*X)*(1.5*Y0 - 0.5*Y0^3*X)*(1.5*Y0 - 0.5*Y0^3*X)
//                         = (2.25*Y0^2 - 1.5*Y0^4*X + 0.25*Y0^6*X^2)*(1.5*Y0 - 0.5*Y0^3*X)
//                         = 3.375*Y0^3 - 2.25*Y0^5*X + 0.375*Y0^7*X^2 - 1.125*Y0^5*X + 0.75*Y0^7*X^2 - 0.125*Y0^9*X^3
//                         = 3.375*Y0^3 - 3.375*Y0^5*X + 1.125*Y0^7*X^2 - 0.125*Y0^9*X^3
// Y  = 2.25*Y0 - 0.75*Y0^3*X - 0.5*(3.375*Y0^3 - 3.375*Y0^5*X + 1.125*Y0^7*X^2 - 0.125*Y0^9*X^3)*X
// Y  = 2.25*Y0 - 0.75*Y0^3*X - 1.6875*Y0^3*X + 1.6875*Y0^5*X^2 - 0.5625*Y0^7*X^3 + 0.0625*Y0^9*X^4
// Y  = 2.25*Y0 - 2.4375*Y0^3*X + 1.6875*Y0^5*X^2 - 0.5625*Y0^7*X^3 + 0.0625*Y0^9*X^4                   (1)
// Y  = 2.25*Y0 - 2.4375*Y0^3*(X0+dx) + 1.6875*Y0^5*(X0+dx)^2 - 0.5625*Y0^7*(X0+dx)^3 + 0.0625*Y0^9*(X0+dx)^4
//
// (X0 + dx)^2 = X0^2 + 2*X0*dx + dx^2
// (X0 + dx)^3 = (X0^2 + 2*X0*dx + dx^2)*(X0 + dx)
//             = X0^3 + 2*X0^2*dx + X0*dx^2 + X0^2*dx + 2*X0*dx^2 + dx^3
//             = X0^3 + 3*X0^2*dx + 3*X0*dx^2 + dx^3
// (X0 + dx)^4 = (X0^3 + 3*X0^2*dx + 3*X0*dx^2 + dx^3)*(X0 + dx)
//             = X0^4 + 3*X0^3*dx + 3*X0^2*dx^2 + X0*dx^3 + X0^3*dx + 3*X0^2*dx^2 + 3*X0*dx^3 + dx^4
//             = X0^4 + 4*X0^3*dx + 6*X0^2*dx^2 + 4*X0*dx^3 + dx^4
//
// Y  = 2.25*Y0 - 2.4375*Y0^3*X0 + 1.6875*Y0^5*X0^2 - 0.5625*Y0^7*X0^3 + 0.0625*Y0^9*X0^4
//      - 2.4375*Y0^3*dx + 1.6875*Y0^5*(2*X0*dx + dx^2) 
//      - 0.5625*Y0^7*(3*X0^2*dx + 3*X0*dx^2 + dx^3)
//      + 0.0625*Y0^9*(4*X0^3*dx + 6*X0^2*dx^2 + 4*X0*dx^3 + dx^4)
// Y = Y0 - 2.4375*Y0^3*dx 
//        + 3.375*Y0^5*X0*dx + 1.6875*Y0^5*dx^2 
//        - 1.6875*Y0^7*X0^2*dx - 1.6875*Y0^7*X0*dx^2 - 0.5625*Y0^7*dx^3
//        + 0.25*Y0^9*X0^3*dx + 0.375*Y0^9*X0^2*dx^2 + 0.25*Y0^9*X0*dx^3 + 0.0625*Y0^9*dx^4
// Y = Y0 + C1*dx + C2*dx^2 + C3*dx^3 + C4*dx^4
//
// C1 = -(2.4375*Y0^3 - 3.375*Y0^5*X0 + 1.6875*Y0^7*X0^2 - 0.25*Y0^9*X0^3)
// C2 = 1.6875*Y0^5 - 1.6875*Y0^7*X0 + 0.375*Y0^9*X0^2
// C3 = -(0.5625*Y0^7 - 0.25*Y0^9*X0)
// C4 = 0.0625*Y0^9
//
// Range X0: 1.0     to  2.0
// Range Y0: 1.0     to  0.707106781    
// Range C1: -0.5    to  -0.176776695    
// Range C2: 0.375   to  0.066291261    
// Range C3: -0.3125 to  -0.027621359
//
//  To improve accuracy, we modify equation as follows:
//
//  X = x0 + dx0 +/- dx
//
//  Y = Y0 + S1*dx + S2*dx^2 + S3*dx^3
//
//  Where:   Y0 = 1/sqrt(x0 + dx0)
//           S1 = C1 + 2*dx0*C2 + 3*dx0*dx0*C3
//           S2 = C2 + 3*dx0*C3
//           S3 = C3
//
//  Term S3*dx^3 is too small to worry about and can be ignored. So equation
//  simplifies to:
//
//  Y = Y0 + S1*dx + S2*dx*dx		; Y0, S1, S2 values are stored in table
//
//  Above equatiosn are for ISQRTF32. Convert to SQRTF32:
//
//    S2 = S2*X0 + S1 
//    S1 = S1*X0 + Y1
//    Y0 = Y0*X0
//
//===========================================================================

#include "stdafx.h"

#define	VERSION	"3.0"

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
F32_UI32	Y1;
F32_UI32	Y3;
F32_UI32	Y4;

long double	TestCount;

long double	ErrorMaxY3posF64;
long double	ErrorMaxY3negF64;
long double	ErrorAvgY3posF64;
long double	ErrorAvgY3negF64;
long double ErrorCountY3posF64;
long double ErrorCountY3negF64;
long double ErrorCountY3posF64_half;
long double ErrorCountY3negF64_half;

long double	ErrorMaxY4posF64;
long double	ErrorMaxY4negF64;
long double	ErrorAvgY4posF64;
long double	ErrorAvgY4negF64;
long double ErrorCountY4posF64;
long double ErrorCountY4negF64;

typedef _int64	i64;

#define	TABLE_SIZE		128

#define PRINT_TABLE		1								// 1 = Print Table, 0 = Don't Print

#define PI				3.14159265359L

#define	SQRT2_24Q23		0x0000000000B504F3L				// = sqrt(2) * 2^23 = 11863283.20303

#define	Q_RESULT		24								// Q24, Q25, Q26,..
#define	Q_SCALE			(long double) (1 << Q_RESULT)

F32_UI32		SQRTF32_X0[TABLE_SIZE];
F32_UI32		SQRTF32_Y0[TABLE_SIZE];
F32_UI32		SQRTF32_S1[TABLE_SIZE];
F32_UI32		SQRTF32_S2[TABLE_SIZE];
unsigned long	SQRTF32_Y0i[TABLE_SIZE];
unsigned long	SQRTF32_S1i[TABLE_SIZE];
unsigned long	SQRTF32_S2i[TABLE_SIZE];

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

void		PrintResult(void);
void		SQRTF32_Generate_Coefficients(void);
void		SQRTF32_CheckError(F32_UI32 X);
void		SQRTF32_Test(void);
float		SQRTF32_Hardware_Emulation(float X);
float		SQRTF32_FPUFastRTS_Emulation(float X);

//===========================================================================
// Start Of Program: main
//===========================================================================

int _tmain(int argc, _TCHAR* argv[])
{        
 	printf("\nTest TMU SQRTF32 Algorithms, Version %s, Table Size %3d", VERSION, TABLE_SIZE);
	printf("\nCopyright (c) Texas Instruments Inc. 2010-2011");

	sprintf(OutputFileName, "SQRTF32_Results_float_Q%2d_TableSize%3d.txt", Q_RESULT, TABLE_SIZE);
 
 	if( (OutPtr = fopen(OutputFileName, "w+")) == NULL )
		{  
		printf("\n");
		printf("\nERROR: Could Not Open %s File For Output.", _strupr(OutputFileName));
		printf("\n");
		exit(0);
 		}           

  	fprintf(OutPtr,  ";;##########################################################################");
	fprintf(OutPtr,"\n;;");
	fprintf(OutPtr,"\n;;Title:     TMU SQRTF32 Algorithm Test Results");
	fprintf(OutPtr,"\n;;");
	fprintf(OutPtr,"\n;;Version:   %s", VERSION );
	fprintf(OutPtr,"\n;;");
	fprintf(OutPtr,"\n;;TableSize: %3d", TABLE_SIZE );
	fprintf(OutPtr,"\n;;");
	fprintf(OutPtr,"\n;;##########################################################################");
	fprintf(OutPtr,"\n");
	fprintf(OutPtr,"\n");

	// Run algorithm:
	SQRTF32_Generate_Coefficients();
	SQRTF32_Test();

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
// SQRTF32 Test Program:
//===========================================================================

void SQRTF32_CheckError(F32_UI32 X)
{
	long double X_f64;
	long double	Y1_f64;
	long double Y1_temp_f64;
	long double Y1_error_f64;

	// Increment total test count:
	TestCount = TestCount + 1.0;

	// Generate Precise Reefernce Value Y1:
	X_f64 = (long double) X.f32;
	Y1_f64 = sqrt(X_f64);

	Y1_temp_f64 = Y1_f64;

		// Calculate Hardware Emulation Value Y3:
	Y3.f32 = SQRTF32_Hardware_Emulation(X.f32);

	if(Y1_temp_f64 > ((long double) Y3.f32))
		{
		Y1_error_f64 = Y1_temp_f64 - ((long double) Y3.f32);
		if(Y1_error_f64 > ErrorMaxY3posF64)
			ErrorMaxY3posF64 = Y1_error_f64;
		ErrorCountY3posF64 = ErrorCountY3posF64 + 1.0;
		ErrorAvgY3posF64 = ErrorAvgY3posF64 + Y1_error_f64;
		if((Y1_error_f64 * Q_SCALE) >= 0.5L)
			ErrorCountY3posF64_half = ErrorCountY3posF64_half + 1.0;
		}
	if(Y1_temp_f64 < ((long double) Y3.f32))
		{
		Y1_error_f64 = ((long double) Y3.f32) - Y1_temp_f64;
		if(Y1_error_f64 > ErrorMaxY3negF64)
			ErrorMaxY3negF64 = Y1_error_f64;
		ErrorCountY3negF64 = ErrorCountY3negF64 + 1.0;
		ErrorAvgY3negF64 = ErrorAvgY3negF64 + Y1_error_f64;
		if((Y1_error_f64 * Q_SCALE) >= 0.5L)
			ErrorCountY3negF64_half = ErrorCountY3negF64_half + 1.0;
		}

	// Calculate FastRTS Emulation Value Y4:
	Y4.f32  = SQRTF32_FPUFastRTS_Emulation(X.f32);

	if(Y1_temp_f64 > ((long double) Y4.f32))
		{
		Y1_error_f64 = Y1_temp_f64 - ((long double) Y4.f32);
		if(Y1_error_f64 > ErrorMaxY4posF64)
			ErrorMaxY4posF64 = Y1_error_f64;
		ErrorCountY4posF64 = ErrorCountY4posF64 + 1.0;
		ErrorAvgY4posF64 = ErrorAvgY4posF64 + Y1_error_f64;
		}
	if(Y1_temp_f64 < ((long double) Y4.f32))
		{
		Y1_error_f64 = ((long double) Y4.f32) - Y1_temp_f64;
		if(Y1_error_f64 > ErrorMaxY4negF64)
			ErrorMaxY4negF64 = Y1_error_f64;
		ErrorCountY4negF64 = ErrorCountY4negF64 + 1.0;
		ErrorAvgY4negF64 = ErrorAvgY4negF64 + Y1_error_f64;
		}
}

void PrintResult(void)
{
	fprintf(OutPtr,"\nTest Count = %16.1f", TestCount);
	fprintf(OutPtr,"\nError For Hardware Emulation : pos (Max, Avg, Count, Half) > %16.14f, %16.14f, %16.1f, %16.1f", (ErrorMaxY3posF64 * Q_SCALE), ((ErrorAvgY3posF64/ErrorCountY3posF64) * Q_SCALE), ErrorCountY3posF64, ErrorCountY3posF64_half);
	fprintf(OutPtr,"\n                             : neg (Max, Avg, Count, Half) > %16.14f, %16.14f, %16.1f, %16.1f", (ErrorMaxY3negF64 * Q_SCALE), ((ErrorAvgY3negF64/ErrorCountY3negF64) * Q_SCALE), ErrorCountY3negF64, ErrorCountY3negF64_half);
	fprintf(OutPtr,"\nError For FastRTS  Emulation : pos (Max, Avg, Count      ) > %16.14f, %16.14f, %16.1f",         (ErrorMaxY4posF64 * Q_SCALE), ((ErrorAvgY4posF64/ErrorCountY4posF64) * Q_SCALE), ErrorCountY4posF64);
	fprintf(OutPtr,"\n                             : neg (Max, Avg, Count      ) > %16.14f, %16.14f, %16.1f",         (ErrorMaxY4negF64 * Q_SCALE), ((ErrorAvgY4negF64/ErrorCountY4negF64) * Q_SCALE), ErrorCountY4negF64);
}


void SQRTF32_Test(void)
{
	int		i;
	float	temp;

	fprintf(OutPtr,"\nSummary Of Errors With Respect To Precise Reference Value:");
	fprintf(OutPtr,"\n\nTesting: SQRTF32, Table Size = %4d, Q Scaling = Q%2d", TABLE_SIZE, Q_RESULT);
	fprintf(OutPtr,"\n===========================================================================\n");

  	// Clear test count:
	TestCount = 0.0;

  	// Clear error logs:

	ErrorMaxY3posF64 = 0.0;
	ErrorMaxY3negF64 = 0.0;
	ErrorAvgY3posF64 = 0.0;
	ErrorAvgY3negF64 = 0.0;
	ErrorCountY3posF64 = 0.0;
	ErrorCountY3negF64 = 0.0;
	ErrorCountY3posF64_half = 0.0;
	ErrorCountY3negF64_half = 0.0;

	ErrorMaxY4posF64 = 0.0;
	ErrorMaxY4negF64 = 0.0;
	ErrorAvgY4posF64 = 0.0;
	ErrorAvgY4negF64 = 0.0;
	ErrorCountY4posF64 = 0.0;
	ErrorCountY4negF64 = 0.0;

	printf("\nTest SQRTF32 Using Q%2d Scaling, Return (float)", Q_RESULT);
	printf("\nCheck All Values Between X = 0.25 to X = 3.99999999 (all mantissa bits):");
	fprintf(OutPtr,"\n\n\nCheck All Values Between X = 0.25 to X = 3.99999999 (all mantissa bits):");

	X.f32 = 0.25;
	temp = 0.25;
	for(i=0; i < 240; i++)
		{
		fprintf(OutPtr,"\n\nCheck Values Between: %16.14f <= X < %16.14f", temp, (temp + 0.015625));
		temp = temp + 0.015625;
		while(X.f32 < temp)
			{
			SQRTF32_CheckError(X);
			X.ui32 = X.ui32 + 1;
			};
		PrintResult();
		}
/*
	printf("\nCheck Some Random Values:");
	fprintf(OutPtr,"\n\n\nCheck Some Random Values:");

	// Test a few random values:
	X.f32 = 3.33333;
	SQRTF32_CheckError(X);

	X.f32 = 12345.6789;
	SQRTF32_CheckError(X);

	X.f32 = 0.7654321;
	SQRTF32_CheckError(X);

	X.f32 = 3.0;
	SQRTF32_CheckError(X);

	X.f32 = 4.0;
	SQRTF32_CheckError(X);

	X.f32 = 5.0;
	SQRTF32_CheckError(X);

	X.f32 = 6.0;
	SQRTF32_CheckError(X);

	X.f32 = 7.0;
	SQRTF32_CheckError(X);

	X.f32 = 16.0;
	SQRTF32_CheckError(X);

	X.f32 = 0.5;
	SQRTF32_CheckError(X);

	X.f32 = 0.26;
	SQRTF32_CheckError(X);

	X.f32 = 0.25;
	SQRTF32_CheckError(X);

	X.f32 = 0.241;
	SQRTF32_CheckError(X);

	X.f32 = 0.0625;
	SQRTF32_CheckError(X);

	PrintResult();
*/
}

//===========================================================================
// SQRTF32 Coefficient Table Generator:
//===========================================================================

void SQRTF32_Generate_Coefficients(void)
{
	unsigned int	i;
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
	long double		Y0_9_f64;

	long double		X0_2_f64;
	long double		X0_3_f64;

	// Initialize first value:
	X0_f64  =  1.0L;					// 1.0
	dx0_f64 =  0.00390625L;				// 1/(TABLE_SIZE * 2)
	X1_f64  = X0_f64 + dx0_f64;		

	for(i=0; i < TABLE_SIZE; i++)
		{
		// Initialize 64-bit float values for intermediate calculations:
		Y0_f64 = 1.0L / sqrt(X0_f64);
		Y1_f64 = 1.0L / sqrt(X1_f64);

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
		C1_f64 = -2.4375L*Y0_3_f64 +  3.375L*Y0_5_f64*X0_f64 - 1.6875L*Y0_7_f64*X0_2_f64 + 0.25L*Y0_9_f64*X0_3_f64;
		C2_f64 = 1.6875L*Y0_5_f64 - 1.6875L*Y0_7_f64*X0_f64 +  0.375L*Y0_9_f64*X0_2_f64;
		C3_f64 = -0.5625L*Y0_7_f64 +   0.25L*Y0_9_f64*X0_f64;

		// S1 = C1 + 2*dx0*C2 + 3*dx0*dx0*C3
		S1_f64 = C1_f64 + 2.0L*dx0_f64*C2_f64 + 3.0L*dx0_f64*dx0_f64*C3_f64;
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
		Y1_f64 = Y1_f64 * 1.00000005L;
		S1_f64 = S1_f64 * 1.000001L;
		S2_f64 = S2_f64 * 1.0L;

		// Store Y0 as +ve Q31 value:
		temp = Y1_f64 * 2147483648.0L;
		if( temp >= 0.0)
			temp = temp + 0.5L;
		else
			temp = temp - 0.5L;
		SQRTF32_Y0i[i] = (unsigned long) (temp + (1 << 6));
			
		// Store S1 as +ve Q23 value:
		temp = S1_f64 * 8388608.0L;
		if( temp >= 0.0)
			temp = temp + 0.5L;
		else
			temp = temp - 0.5L;
		SQRTF32_S1i[i] = (unsigned long) temp;

		// Store S2 as +ve Q17 value:
		temp = S2_f64 * 131072.0L;
		if( temp >= 0.0)
			temp = temp + 0.5L;
		else
			temp = temp - 0.5L;
		SQRTF32_S2i[i] = (unsigned long) -temp;

		// Increment X for next table entry:
		X0_f64 = X0_f64 + 0.0078125L;		// X0 = X0 + 1.0/(TABLE_SIZE = 128)
		X1_f64 = X1_f64 + 0.0078125L;		// X1 = X1 + 1.0/(TABLE_SIZE = 128)
		}

	if(PRINT_TABLE == 1)
		{
		fprintf(OutPtr,"\nStart Of Coefficient Table:\n");
		for(i=0; i < TABLE_SIZE; i++)
			{
			fprintf(OutPtr,"\n%4d | X0 = %16.12f | Y0 = %16.12f   S1 = %16.12f   S2 = %16.12f | Y0i = %16u   S1i = %16u   S2i = %16u", (i), SQRTF32_X0[i].f32, SQRTF32_Y0[i].f32,  SQRTF32_S1[i].f32, SQRTF32_S2[i].f32, SQRTF32_Y0i[i], SQRTF32_S1i[i],  SQRTF32_S2i[i]);
			}
		fprintf(OutPtr,"\n\nEnd of data.\n");
		}
}

//===========================================================================
// SQRTF32 Algorithms:
//===========================================================================

float SQRTF32_Hardware_Emulation(float X)
{
	F32_UI32		tempX;	
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

	unsigned long	Si;		// Bit  31    Sign     Of Input Value
	unsigned long	Ei;		// Bits 30:23 Exponent Of Input Value
	unsigned long	Mi;		// Bits 22:0  Mantissa Of Input Value
	unsigned long	So;		// Bit  31    Sign     Of Output Value
	unsigned long	Eo;		// Bits 30:23 Exponent Of Output Value
	unsigned long	Mo;		// Bits 22:0  Mantissa Of Output Value

	unsigned int	Boundary;	// 0 = none;
								// 1 = return boundary condition value

	//----------------------------------------------------------------------------------------------------------------------------
	// Pipeline Phase 1: Format input and extract table_index and dx value:

	// Extract sign, exp and mantissa of input:
	tempX.f32 = X;
	Si = (tempX.ui32 & 0x80000000);
	Ei = (tempX.ui32 & 0x7F800000);
	Mi = (tempX.ui32 & 0x007FFFFF);

	// Set default values of data:
	dx = 0;
	Boundary = 0;
	table_index = 0;

	// Check if input is zero or Denorm. If so, generate zero and return:
	if( Ei == 0x00000000 )	
		{
		So = 0x00000000;
		Eo = 0x00000000;
		Mo = 0x00000000;
		Y.ui32 = So + Eo + Mo;
		Boundary = 1;
		}
	// Check if Nan or infinity input. If so, generate infinity and return:
	else if( Ei == 0x7F800000 )
		{
		So = 0x00000000;
		Eo = 0x7F800000;
		Mo = 0x00000000;
		Y.ui32 = So + Eo + Mo;
		Boundary = 1;
		}
	// Check if input is negative. If so, generate zero and return:
	else if( Si == 0x80000000 )
		{
		So = 0x00000000;
		Eo = 0x00000000;
		Mo = 0x00000000;
		Y.ui32 = So + Eo + Mo;
		Boundary = 1;
		}
	// Check if input is modulo of 2. If so, adjust exponent and return with value:
	else if( Mi == 0x00000000L )
		{
		So = 0x00000000;
		Eo = (((Ei >> 1) + 0x1FC00000L) & 0x7F800000L);		// (Ei - 127) /2 + 127 = Ei/2 + 63.5 = (Ei + 0x3F800000L) >> 1
		// If exponent is odd (ei = Ei - 127 = odd value), then return SQRT(2) in mantissa:
		if( (Ei & 0x00800000) != 0x00800000 )
			Mo = (SQRT2_24Q23 & 0x007FFFFFL);
		else
			Mo = 0x00000000;
		Y.ui32 = So + Eo + Mo;
		Boundary = 1;
		}
	else
		{
		// Clear sign bit and adjust exponent:
		So = 0x00000000;
		Eo = (((Ei >> 1) + 0x1FC00000L) & 0x7F800000L);		// (Ei - 127) /2 + 127 = Ei/2 + 63.5 = (Ei + 0x3F800000L) >> 1

		// Extract table index and dx value for TABLE_SIZE == 128:
		table_index = ((Mi & 0x007F0000L) >> 16);			
		if( (Mi & 0x00008000L) == 0 )
			dx = (0xFFFF8000L ^ (Mi & 0x0000FFFFL)) << 9;			// Q33
		else
			dx = (0x00008000L ^ (Mi & 0x0000FFFFL)) << 9;			// Q33
		}

	//----------------------------------------------------------------------------------------------------------------------------
	// Pipeline Phase 2: Get ROM table values and calcualte dx*dx

	S2i	= (i64) SQRTF32_S2i[table_index];	// 20.Q15, +ve number with only bits 0 to 19 are valid (S2i[19:0])
	S1i = (i64) SQRTF32_S1i[table_index];	// 24.Q21, +ve number with only bits 0 to 23 are valid (S1i[23:0])
	Y0i = (i64) SQRTF32_Y0i[table_index];	// 30.Q29, +ve number with only bits 0 to 29 are valid (Y0i[29:0])

	// Calculate: dx_dx = ((dx >> 10) * (dx >> 10)) >> 11;
	//
	// The input range of dx for INVF32 is:
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
	// max = 0x00002000L
	//       0x00001FFFL
	//       ...
	//       0x00000001L
	// min = 0x00000000L
	if((temp & 0x00004000L) != 0)
		temp = ((temp ^ 0x00007FFFL) + 1) & 0x00007FFFL;

	// The multiplication performs a 15-bit * 15-bit multiply with 29-bit result (mpy_result[28:0] = temp[14:0] * temp[14:0]):
	// But we only keep 18-bits, from bits 11 to 28, of the result (dx_dx[17:0] =  mpy_result[28:11]):
	// The result range of dx_dx is:
	// max = 0x00002000L
	//       0x00001FFFL
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
		sum = Y0i + dx_S1_SUB_dx_dx_S2;		
	else
		// if dx negative: perform 32-bit add
		sum = Y0i - dx_S1_ADD_dx_dx_S2; 

	//----------------------------------------------------------------------------------------------------------------------------
	// Pipeline Phase 5: Format output
	if( Boundary != 0 )
		return	Y.f32;			// Return boundary condition value detected in Pipeline Phase 1
	else
		{
		// If exponent is odd (ei = Ei - 127 = odd value), then multiply result by SQRT(2):
		if( (Ei & 0x00800000) != 0x00800000 )
			{
			// Perform 25-bit by 24-bit multiply with 25-bit result (sum[24:0] = sum[30:6] * SQRT2[23:0]):
			sum  =  (((sum & 0x00000000FFFFFF80L) * (SQRT2_24Q23)) & 0x00FFFFFF80000000L) >> 31;
			}
		else
			{
			// else, if exponent is even, scale back to 24-bit mantissa:
			sum = sum >> 8;	
			}

		// Make sure sum value is not negative:
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

//===========================================================================
// No more.
//===========================================================================
