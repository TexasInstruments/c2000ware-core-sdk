//*****************************************************************************
//
// FILE:     TMU_Test3_DIVF32.cpp
//
// TITLE:    Utility To Test TMU DIVF32 Algorithms
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
//  2.0  | 24-Apr-2012 | Alex T. | Original Release.
//  -----|-------------|---------|--------------------------------------------
//  3.0  | 31-May-2012 | Alex T. | Added LVF/LUF flags, corrected boundary checks, corrected phase 5 calculations.
//  -----|-------------|---------|--------------------------------------------
//
//*****************************************************************************
// COMPILER:  This utility was compiled using Microsft Visual C++ Express
//            in Win32 console mode. 
//=============================================================================
// DIVF32 TMU Algorithm Description:
//=============================================================================
//
// First calculate Y = 1/X:, then at end calculate Y = Z * (1/X)
//  Y = 1/X
//  Y = Y0 + dy
//  X = X0 + dx
//  
//  Y1 = 2*Y0 - Y0^2*X
//  Y  = 2*Y1 - Y1^2*X
//  
//  Y = 2*(2*Y0 - Y0^2*X) - (2*Y0 - Y0^2*X)^2*X
//  Y = 4*Y0 - 2*Y0^2*X - [(4*Y0^2 - 2*Y0^3*X - 2*Y0^3*X + Y0^4*X^2)*X]
//  Y = 4*Y0 - 2*Y0^2*X - [4*Y0^2*X - 4*Y0^3*X^2 + Y0^4*X^3]
//  Y = 4*Y0 - 2*Y0^2*X - 4*Y0^2*X + 4*Y0^3*X^2 - Y0^4*X^3
//  Y = 4*Y0 - 6*Y0^2*X + 4*Y0^3*X^2 - Y0^4*X^3							(1)
//  
//  Y = 4*Y0 - 6*Y0^2*(X0 + dx) + 4*Y0^3*(X0 + dx)^2 - Y0^4*(X0 + dx)^3
//  Y = 4*Y0 - 6*Y0^2*(X0 + dx) + 4*Y0^3*(X0^2 + 2*X0*dx + dx^2) - Y0^4*[(X0^2 + 2*X0*dx + dx^2)*(X0 + dx)]
//  Y = 4*Y0 - 6*Y0^2*X0 - 6*Y0^2*dx + 4*Y0^3*X0^2 + 8*Y0^3*X0*dx + 4*Y0^3*dx^2
//      - Y0^4*[X0^3 + X0^2*dx + 2*X0^2*dx + 2*X0*dx^2 + X0*dx^2 + dx^3]
//  Y = 4*Y0 - 6*Y0^2*X0 - 6*Y0^2*dx + 4*Y0^3*X0^2 + 8*Y0^3*X0*dx + 4*Y0^3*dx^2
//      - Y0^4*[X0^3 + 3*X0^2*dx + 3*X0*dx^2 + dx^3]
//  Y = 4*Y0 - 6*Y0^2*X0 - 6*Y0^2*dx + 4*Y0^3*X0^2 + 8*Y0^3*X0*dx + 4*Y0^3*dx^2
//      - Y0^4*X0^3 - 3*Y0^4*X0^2*dx - 3*Y0^4*X0*dx^2 - Y0^4*dx^3
//  Y = 4*Y0 - 6*Y0^2*X0 + 4*Y0^3*X0^2 - Y0^4*X0^3 - 6*Y0^2*dx + 8*Y0^3*X0*dx - 3*Y0^4*X0^2*dx 
//      + 4*Y0^3*dx^2 - 3*Y0^4*X0*dx^2 - Y0^4*dx^3
//  Y = (4*Y0 - 6*Y0^2*X0 + 4*Y0^3*X0^2 - Y0^4*X0^3) - (6*Y0^2 - 8*Y0^3*X0 + 3*Y0^4*X0^2)*dx 
//      + (4*Y0^3 - 3*Y0^4*X0)*dx^2 - Y0^4*dx^3
//  
//  C0 = 4*Y0 - 6*Y0^2*X0 + 4*Y0^3*X0^2 - Y0^4*X0^3 = Y0
//  C1 = -(6*Y0^2 - 8*Y0^3*X0 + 3*Y0^4*X0^2)
//  C2 = 4*Y0^3 - 3*Y0^4*X0
//  C3 = -(Y0^4)
//  
//  Y = Y0 + C1*dx + C2*dx^2 + C3*dx^3
//  
//  Range X0:  1.0 to 2.0
//  Range Y0:  1.0 to 0.5      
//  Range C1: -1.0 to -0.25    
//  Range C2:  1.0 to 0.125    
//  Range C3: -1.0 to 0.0625
//
//  To improve accuracy, we modify equation as follows:
//
//  X = x0 + dx0 +/- dx
//
//  Y = Y0 + S1*dx + S2*dx^2 + S3*dx^3
//
//  Where:   Y0 = 1/(x0 + dx0)
//           S1 = C1 + 2*dx0*C2 + 3*dx0*dx0*C3
//           S2 = C2 + 3*dx0*C3
//           S3 = C3
//
//  Term S3*dx^3 is too small to worry about and can be ignored. So equation
//  simplifies to:
//
//  Y = Y0 + S1*dx + S2*dx*dx		; Y0, S1, S2 values are stored in table
//
// The following conversion happens on the Input number by default before it gets to the TMU functions:
//    -ve zero inputs are treated as +ve zero
//    +/- DNorm inputs are treated as +ve zero
//    +/- NaN is treated as +/-Infinity
//    +/- Inf is NOT CONVERTED to MAX rather they are taken care in TMU functions
//
//    Division      Result  Overflow  Underflow
//    0/Normal        0        -        -
//    0/0             0        1        -
//    0/Inf           0        -        1
//    Inf/Normal      Inf      1        -
//    Inf/0           Inf      1        -
//    Inf/Inf         Inf      -        1
//    Normal/0        Inf      1        -
//    Normal/Inf      0        -        1
//    Normal/Normal   Note 1  Note 1   Note 1
//                
//    Note:    1) For normal calculations, the result is calculated as follows:  
//                      Eo = (Ez – Ei) + 127;
//                      Mo = Mz / Mi;                // 0.5 < Mo < 2.0
//                      if( Mo < 1.0 )               // Normalize mantissa:
//                          {
//                          Eo = Eo – 1;
//                          Mo = Mo * 2.0;
//                          }
//                      if( Eo >= 255)               // If value too big:
//                          {
//                          Eo  = 255;               // Return Inf
//                          Mo  = 0;
//                          LVF = 1;
//                          }
//                      if(Eo < 0)                   // If value too small:                                                                
//                          {
//                          So = 0;
//                          Eo = 0;                  // Return zero
//                          Mo = 0;
//                          LUF = 1;      
//                          }    
//
//               Note: Denorm value could be returned by above if Eo = 0 & Mo != 0
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
F32_UI32	Z;
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

int				LVF_flag;			// Latched overflow flag.
int				LUF_flag;			// Latched underflow flag.

unsigned long	EINVF32_TABLE[128] = {
0x7F, 0x7E, 0x7C, 0x7A, 0x78, 0x76, 0x75, 0x73, 0x71, 0x6F, 0x6D, 0x6C, 0x6A, 0x68, 0x67, 0x65,
0x64, 0x62, 0x60, 0x5F, 0x5D, 0x5C, 0x5A, 0x59, 0x58, 0x56, 0x55, 0x53, 0x52, 0x51, 0x4F, 0x4E, 
0x4D, 0x4C, 0x4A, 0x49, 0x48, 0x47, 0x45, 0x44, 0x43, 0x42, 0x41, 0x40, 0x3F, 0x3D, 0x3C, 0x3B,
0x3A, 0x39, 0x38, 0x37, 0x36, 0x35, 0x34, 0x33, 0x32, 0x31, 0x30, 0x2F, 0x2E, 0x2D, 0x2C, 0x2C,
0x2B, 0x2A, 0x29, 0x28, 0x27, 0x26, 0x25, 0x25, 0x24, 0x23, 0x22, 0x21, 0x21, 0x20, 0x1F, 0x1E,
0x1E, 0x1D, 0x1C, 0x1B, 0x1B, 0x1A, 0x19, 0x18, 0x18, 0x17, 0x16, 0x16, 0x15, 0x14, 0x14, 0x13,
0x12, 0x12, 0x11, 0x10, 0x10, 0x0F, 0x0E, 0x0E, 0x0D, 0x0D, 0x0C, 0x0B, 0x0B, 0x0A, 0x0A, 0x09,
0x09, 0x08, 0x07, 0x07, 0x06, 0x06, 0x05, 0x05, 0x04, 0x04, 0x03, 0x03, 0x02, 0x02, 0x01, 0x01 };

void		PrintResult(void);
void		DIVF32_Generate_Coefficients(void);
void		DIVF32_CheckError(F32_UI32 Z, F32_UI32 X);
void		CheckValues(F32_UI32 Z, F32_UI32 X);
void		DIVF32_Test(void);
float		DIVF32_Hardware_Emulation(float Z, float X);
float		DIVF32_FPUFastRTS_Emulation(float Z, float X);

//===========================================================================
// Start Of Program: main
//===========================================================================

int _tmain(int argc, _TCHAR* argv[])
{        
 	printf("\nTest TMU DIVF32 Algorithms, Version %s, Table Size %3d", VERSION, TABLE_SIZE);
	printf("\nCopyright (c) Texas Instruments Inc. 2010-2011");

	sprintf(OutputFileName, "DIVF32_Results_float_Q%2d_TableSize%3d.txt", Q_RESULT, TABLE_SIZE);
 
 	if( (OutPtr = fopen(OutputFileName, "w+")) == NULL )
		{  
		printf("\n");
		printf("\nERROR: Could Not Open %s File For Output.", _strupr(OutputFileName));
		printf("\n");
		exit(0);
 		}           

  	fprintf(OutPtr,  ";;##########################################################################");
	fprintf(OutPtr,"\n;;");
	fprintf(OutPtr,"\n;;Title:     TMU DIVF32 Algorithm Test Results");
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
	DIVF32_Test();

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

void DIVF32_CheckError(F32_UI32 Z, F32_UI32 X)
{
	long double X_f64;
	long double Z_f64;
	long double	Y1_f64;
	long double Y1_temp_f64;
	long double Y1_error_f64;

	// Increment total test count:
	TestCount = TestCount + 1.0;

	// Generate Precise Reefernce Value Y1:
	X_f64 = (long double) X.f32;
	Z_f64 = (long double) Z.f32;
	Y1_f64 = Z_f64 / X_f64;

	Y1_temp_f64 = Y1_f64;

	// Calculate Hardware Emulation Value Y3:
	Y3.f32 = DIVF32_Hardware_Emulation(Z.f32, X.f32);

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
	Y4.f32  = DIVF32_FPUFastRTS_Emulation(Z.f32, X.f32);

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


void CheckValues(F32_UI32 Z, F32_UI32 X)
{
	long double X_f64;
	long double Z_f64;
	long double	Y1_f64;
	long double Y1_temp_f64;
	long double Y1_error_f64;

	// Generate Precise Reefernce Value Y1:
	X_f64 = (long double) X.f32;
	Z_f64 = (long double) Z.f32;
	Y1_f64 = Z_f64 / X_f64;

	Y1_temp_f64 = Y1_f64;

	// Calculate Hardware Emulation Value Y3:
	LVF_flag = 0;
	LUF_flag = 0;
	Y3.f32 = DIVF32_Hardware_Emulation(Z.f32, X.f32);

	Y1_error_f64 = 0.0;
	if(Y1_temp_f64 > ((long double) Y3.f32))
		{
		Y1_error_f64 = Y1_temp_f64 - ((long double) Y3.f32);
		}
	if(Y1_temp_f64 < ((long double) Y3.f32))
		{
		Y1_error_f64 = ((long double) Y3.f32) - Y1_temp_f64;
		}

	fprintf(OutPtr,"\n\nHardware Emulation Y = %24.12f / %24.12f = %24.12f (LVF = %1d) (LUF = %1d) (Absolute Error = %20.12f) ", Z.f32, X.f32, Y3.f32, LVF_flag, LUF_flag, (Y1_error_f64 * Q_SCALE));

	// Calculate FastRTS Emulation Value Y4:
	LVF_flag = 0;
	LUF_flag = 0;
	Y4.f32  = DIVF32_FPUFastRTS_Emulation(Z.f32, X.f32);

	Y1_error_f64 = 0.0;
	if(Y1_temp_f64 > ((long double) Y4.f32))
		{
		Y1_error_f64 = Y1_temp_f64 - ((long double) Y4.f32);
		}
	if(Y1_temp_f64 < ((long double) Y4.f32))
		{
		Y1_error_f64 = ((long double) Y4.f32) - Y1_temp_f64;
		}
	fprintf(OutPtr,"\nFastRTS  Emulation Y = %24.12f / %24.12f = %24.12f (LVF = %1d) (LUF = %1d) (Absolute Error = %20.12f)", Z.f32, X.f32, Y4.f32, LVF_flag, LUF_flag, (Y1_error_f64 * Q_SCALE));
}

void DIVF32_Test(void)
{
	int		i;
	float	temp;

	fprintf(OutPtr,"\nSummary Of Errors With Respect To Precise Reference Value:");
	fprintf(OutPtr,"\n\nTesting: INVF32, Table Size = %4d, Q Scaling = Q%2d", TABLE_SIZE, Q_RESULT);
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

	printf("\nTest DIVF32 Using Q%2d Scaling, Return (float)", Q_RESULT);

	printf("\nCheck All Values Between Z = 1.0 / (X = 1.00000 to X = 1.99999999) (all mantissa bits):");
	fprintf(OutPtr,"\n\n\nCheck All Values Between Z = 1.0 / (X = 1.00000 to X = 1.99999999) (all mantissa bits):");

	Z.f32 = 1.0;
	X.f32 = 1.0;
	temp = 1.0;
	do	{
		#if TABLE_SIZE == 128
		temp = temp + 0.0078125;
		#endif

		#if TABLE_SIZE == 256
		temp = temp + 0.00390625;
		#endif

		fprintf(OutPtr,"\n\nCheck Values Between: %16.14f <= X < %16.14f", X.f32, temp);

	  	// Clear error logs:
		TestCount = 0.0;

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

		do  {
			DIVF32_CheckError(Z, X);
			X.ui32 = X.ui32 + 1;
			} 
		while( X.f32 < temp );

		PrintResult();
		}
	while( temp < 2.0 );


	printf("\nCheck All Values Between Z = 1.0 / (X = 0.0625 to X = 0.12499999) (all mantissa bits):");
	fprintf(OutPtr,"\n\n\nCheck All Values Between Z = 1.0 / (X = 0.0625 to X = 0.12499999) (all mantissa bits):");

	Z.f32 = 1.0;
	X.f32 = 0.0625;
	temp = 0.0625;
	do	{
		#if TABLE_SIZE == 128
		temp = temp + 0.00048828125;
		#endif

		#if TABLE_SIZE == 256
		temp = temp + 0.000244140625;
		#endif

		fprintf(OutPtr,"\n\nCheck Values Between: %16.14f <= X < %16.14f", X.f32, temp);

	  	// Clear error logs:
		TestCount = 0.0;

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

		do  {
			DIVF32_CheckError(Z, X);
			X.ui32 = X.ui32 + 1;
			} 
		while( X.f32 < temp );

		PrintResult();
		}
	while( temp < 0.125 );


	printf("\nCheck Some Random Values:");
	fprintf(OutPtr,"\n\n\nCheck Some Random Values:");

	Z.f32 = 1.0;

	X.f32 = 3.33333;
	CheckValues(Z, X);
	X.f32 = -3.33333;
	CheckValues(Z, X);

	X.f32 = 0.7654321;
	CheckValues(Z, X);
	X.f32 = -0.7654321;
	CheckValues(Z, X);

	X.f32 = 3.0;
	CheckValues(Z, X);
	X.f32 = -3.0;
	CheckValues(Z, X);

	X.f32 = 4.0;
	CheckValues(Z, X);
	X.f32 = -4.0;
	CheckValues(Z, X);

	X.f32 = 5.0;
	CheckValues(Z, X);
	X.f32 = -5.0;
	CheckValues(Z, X);

	X.f32 = 6.0;
	CheckValues(Z, X);
	X.f32 = -6.0;
	CheckValues(Z, X);

	X.f32 = 7.0;
	CheckValues(Z, X);
	X.f32 = -7.0;
	CheckValues(Z, X);

	X.f32 = 16.0;
	CheckValues(Z, X);
	X.f32 = -16.0;
	CheckValues(Z, X);

	X.f32 = 0.5;
	CheckValues(Z, X);
	X.f32 = -0.5;
	CheckValues(Z, X);

	X.f32 = 0.26;
	CheckValues(Z, X);
	X.f32 = -0.26;
	CheckValues(Z, X);

	X.f32 = 0.25;
	CheckValues(Z, X);
	X.f32 = -0.25;
	CheckValues(Z, X);

	X.f32 = 0.241;
	CheckValues(Z, X);
	X.f32 = -0.241;
	CheckValues(Z, X);

	X.f32 = 0.0625;
	CheckValues(Z, X);
	X.f32 = -0.0625;
	CheckValues(Z, X);

	Z.f32 = 1.5;
	X.f32 = 1.0;
	CheckValues(Z, X);

	Z.f32 = -1.5;
	X.f32 = 1.0;
	CheckValues(Z, X);

	Z.f32 = -1.5;
	X.f32 = -1.0;
	CheckValues(Z, X);

	Z.f32 = 1.5;
	X.f32 = -1.0;
	CheckValues(Z, X);

	Z.f32 = 1.5;
	X.f32 = 1.333;
	CheckValues(Z, X);

	Z.f32 = -1.5;
	X.f32 = 1.333;
	CheckValues(Z, X);

	Z.f32 = -1.5;
	X.f32 = -1.333;
	CheckValues(Z, X);

	Z.f32 = 1.5;
	X.f32 = -1.333;
	CheckValues(Z, X);

	Z.f32 = 1.01;
	X.f32 = 1.01;
	CheckValues(Z, X);

	Z.f32 = 1.01;
	X.f32 = 1.99;
	CheckValues(Z, X);

	Z.f32 = 1.99;
	X.f32 = 1.01;
	CheckValues(Z, X);

	Z.f32 = 1.99;
	X.f32 = 1.99;
	CheckValues(Z, X);

	printf("\nCheck Some Boundary Condition Values:");
	fprintf(OutPtr,"\n\n\nCheck Some Boundary Condition Values:");

	Z.ui32 = 0x3FFFFFFFL;	// Z = 1.99999999
	X.ui32 = 0x3F800001L;	// X = 1.0000001
	CheckValues(Z, X);
	Z.ui32 = 0x3F800001L;	// Z = 1.0000001
	X.ui32 = 0x3F800001L;	// X = 1.0000001
	CheckValues(Z, X);
	Z.ui32 = 0x3FFFFFFFL;	// Z = 1.99999999
	X.ui32 = 0x3FFFFFFFL;	// X = 1.99999999
	CheckValues(Z, X);
	Z.ui32 = 0x3F800001L;	// Z = 1.0000001
	X.ui32 = 0x3FFFFFFFL;	// X = 1.99999999
	CheckValues(Z, X);


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
			fprintf(OutPtr,"\n%4d | X0 = %16.12f,  X2 = %16.12f | Y0 = %16.12f   S1 = %16.12f   S2 = %16.12f | Y0i = %16u   S1i = %16d   S2i = %16d", i, DIVF32_X0[i].f32, DIVF32_X2[i].f32, DIVF32_Y0[i].f32, DIVF32_S1[i].f32, DIVF32_S2[i].f32, DIVF32_Y0i[i], DIVF32_S1i[i], DIVF32_S2i[i]);
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
// DIVF32 Algorithms:
//===========================================================================

float DIVF32_Hardware_Emulation(float Z, float X)
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

	unsigned long	Si;		// Bit  31    Sign     Of Input Value
	unsigned long	Ei;		// Bits 30:23 Exponent Of Input Value
	unsigned long	Mi;		// Bits 22:0  Mantissa Of Input Value
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
	Si = (tempX.ui32 & 0x80000000);
	Ei = (tempX.ui32 & 0x7F800000);
	Mi = (tempX.ui32 & 0x007FFFFF);

	// Extract sign, exp and mantissa of Numerator:
	tempZ.f32 = Z;
	Sz = (tempZ.ui32 & 0x80000000);
	Ez = (tempZ.ui32 & 0x7F800000);
	Mz = (tempZ.ui32 & 0x007FFFFF);

	// Set default values of data:
	dx = 0;
	Boundary = 0;
	table_index = 0;

	// Check for following boundary conditions:
	//
    //    Division      Result  Overflow  Underflow
    //    0/Normal        0        -        -
    //    0/0             0        1        -
    //    0/Inf           0        -        1
    //    Inf/Normal      Inf      1        -
    //    Inf/0           Inf      1        -
    //    Inf/Inf         Inf      -        1
    //    Normal/0        Inf      1        -
    //    Normal/Inf      0        -        1

	// Check if numerator is zero or Denorm. If so, generate zero and return:
	if( Ez == 0x00000000 )	
		{
		So = 0x00000000;
		Eo = 0x00000000;
		Mo = 0x00000000;
		if( Ei == 0x00000000 )		// If denominator is zero or Denorm, set overflow flag
			LVF_flag = 1;		
		if( Ei == 0x7F800000 )		// If denominator is Inf or NaN, set underflow flag
			LUF_flag = 1;
		Y.ui32 = So + Eo + Mo;
		Boundary = 1;
		}
	// Check if numerator is infinity or NaN. If so, generate Inf and return:
	else if( Ez == 0x7F800000 )
		{
		if( Ei == 0x00000000 )
			So = Sz;				// If denominator is zero, sign follows numerator
		else
			So = Si ^ Sz;			// Else sign follows num XOR den
		Eo = 0x7F800000;
		Mo = 0x00000000;
		if( Ei == 0x7F800000 )		// If denominator is Inf or NaN, set underflow flag
			LUF_flag = 1;
		else
			LVF_flag = 1;			// else, set overflow flag.
		Y.ui32 = So + Eo + Mo;
		Boundary = 1;
		}
	// If denominator is zero or Denorm and numerator is Normal, return Inf and set overflow flag:
	else if( Ei == 0x00000000 )
		{
		So = Sz;
		Eo = 0x7F800000;
		Mo = 0x00000000;
		LVF_flag = 1;		
		Y.ui32 = So + Eo + Mo;
		Boundary = 1;
		}
	// If denominator is Inf or NaN and numerator is Normal, return Inf and set underflow flag:
	else if( Ei == 0x7F800000 )
		{
		So = 0x00000000;
		Eo = 0x00000000;
		Mo = 0x00000000;
		LUF_flag = 1;	
		Y.ui32 = So + Eo + Mo;
		Boundary = 1;
		}
	// At this point, inputs are Normal. Check if denominator is modulo of 2. If so, adjust exponent and return with value:
	else if( Mi == 0x00000000 )
		{
		So = Si ^ Sz;	
		Eo = (0x3F800000L + Ez) - Ei;
		Mo = Mz;
		if( Eo >= 0x7F800000 )			// Check if value too big. Return Inf and set overflow flag.
			{
			So = 0x00000000;
			Eo = 0x7F800000;
			Mo = 0x00000000;
			LVF_flag = 1;	
			}
		if( Eo >= 0x80000000 )			// Check if value too small. Return zero and set underflow flag.
			{
			So = 0x00000000;
			Eo = 0x00000000;
			Mo = 0x00000000;
			LUF_flag = 1;	
			}
		Y.ui32 = So + Eo + Mo;
		Boundary = 1;
		}
		
	// Note: The following section can be done in parallel with above boundary checks. It will be ignored on the last stage.
	//
	// Extract table index and dx value:
	#if TABLE_SIZE == 128
	table_index = ((Mi & 0x007F0000L) >> 16);
	if( (Mi & 0x00008000L) == 0 )
		dx = (0xFFFF8000L ^ (Mi & 0x0000FFFFL)) << 9;			// Q33
	else
		dx = (0x00008000L ^ (Mi & 0x0000FFFFL)) << 9;			// Q33
	#endif
	#if TABLE_SIZE == 256
	table_index = ((Mi & 0x007F8000L) >> 15);
	if( (Mi & 0x00004000L) == 0 )
		dx = (0xFFFFC000L ^ (Mi & 0x00007FFFL)) << 10;			// Q33
	else
		dx = (0x00004000L ^ (Mi & 0x00007FFFL)) << 10;			// Q33
	#endif

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
		// Generate sign bit and adjust exponent:
		//    Note:    1) For normal calculations, the result is calculated as follows:  
		//                      Eo = (Ez – Ei) + 127;
		//                      Mo = Mz / Mi;                // 0.5 < Mo < 2.0
		//                      if( Mo < 1.0 )               // Normalize mantissa:
		//                          {
		//                          Eo = Eo – 1;
		//                          Mo = Mo * 2.0;
		//                          }
		//                      if( Eo >= 255)               // If value too big:
		//                          {
		//                          Eo  = 255;               // Return Inf
		//                          Mo  = 0;
		//                          LVF = 1;
		//                          }
		//                      if(Eo < 0)                   // If value too small:                                                                
		//                          {
		//                          So = 0;
		//                          Eo = 0;                  // Return zero
		//                          Mo = 0;
		//                          LUF = 1;      
		//                          }    
		//
		//               Note: Denorm value could be returned by above if Eo = 0 & Mo != 0
		//

		sum  =  (((sum & 0x00000000FFFFFF80L) * (Mz | 0x00800000L)) & 0x00FFFFFF80000000L) >> 31;
		So = Si ^ Sz;	
		Eo = (0x3F800000L + Ez) - Ei;
		if( (sum & 0x01000000L) != 0 )
			sum = sum >> 1;
		else
			Eo = Eo - 0x00800000L;

		Mo = (unsigned long) (sum & 0x007FFFFFL);
	
		if( Eo >= 0x7F800000 )			// Check if value too big. Return Inf and set overflow flag.
			{
			So = 0x00000000;
			Eo = 0x7F800000;
			Mo = 0x00000000;
			LVF_flag = 1;	
			}
		if( Eo >= 0x80000000 )			// Check if value too small. Return zero and set underflow flag.
			{
			So = 0x00000000;
			Eo = 0x00000000;
			Mo = 0x00000000;
			LUF_flag = 1;	
			}
		Y.ui32 = So + Eo + Mo;
		return 	Y.f32;
		}
}

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

//===========================================================================
// No more.
//===========================================================================
