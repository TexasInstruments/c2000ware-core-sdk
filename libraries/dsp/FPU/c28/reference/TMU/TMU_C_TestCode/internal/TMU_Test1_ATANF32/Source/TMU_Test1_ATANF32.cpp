//*****************************************************************************
//
// FILE:     TMU_Test1_ATANF32.cpp
//
// TITLE:    Utility To Test TMU ATANF32 Algorithms, Table Size = 128
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
//  1.0  | 30-Apr-2012 | Alex T. | Original Release.
//
//*****************************************************************************
// COMPILER:  This utility was compiled using Microsft Visual C++ Express
//            in Win32 console mode. 
//=============================================================================
// ATANF32 TMU Algorithm Description:
//=============================================================================
//
//
//  Y = ATAN(X)  
//
//  Where:   -1.0 <= X <= 1.0
//          -PI/4 <= Y <= PI/4 
//
//  Output Y given in PU value rather then radians:
//
//  Ypu = ATAN(X) * (1/2PI)
//
//  Where:   -1.0   <= X   <= 1.0
//           -0.125 <= Ypu <= 0.125 
//
// Use quadractic approximation:
//
//  x0 = X(n)
//  x2 = X(n+1)
//  x1 = (x0 + x1)/2
//
//	c12 = x0
//	c13 = x0 * x0
//	b1  = ATAN(x0)
//	c22 = x1
//	c23 = x1 * x1
//	b2  = ATAN(x1)
//	c32 = x2
//	c33 = x2 * x2
//	b3  = ATAN(x2) 
//
//	a2 = ((b2-b1)*(c32-c12) - (b3-b1)*(c22-c12))/((c13-c33)*(c22-c12) - (c13-c23)*(c32-c12))
//	a1 = ((b3-b1) + a2*(c13-c33))/(c32-c12)
//	a0 = b1 - a1*c12 - a2*c13
//
//	Ypu = (1/2PI) * (a0 + a1*X + a2*X*X)
//
//  To improve accuracy, we modify equation as follows:
//
//  X  = X0 + dx0 + dx
// 
//  Ypu = (1/2PI) * (a0 + a1*(X0 + dx0 + dx) + a2*(X0 + dx0 + dx)*(X0 + dx0 + dx))
//  Ypu = (1/2PI) * (a0 + a1*(X0 + dx0) + a1*dx + a2*(X0*X0 + 2*X0*dx0 + dx0^2 + 2*X0*dx + 2*dx0*dx + dx*dx))
//  Ypu = Y0 + S1*dx + S2*dx*dx
//
//  Y0 = (1/2PI) * (a0 + a1*(X0 + dx0) + a2*(X0 + dx0)^2)
//  S1 = (1/2PI) * (a1 + 2*a2*(X0+dx0))
//  S2 = (1/2PI) * (a2)
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
#define INV2PI			0.159154943091895

#define	Q_RESULT		24								// Q24, Q25, Q26,..
#define	RETURN_FLOAT	1								// 1 = return float value, 0 = return long value
#define	SIN_COS_MODE	0								// 0 = calculate SINF32, 1 = calculate COSF32

#define	Q_SCALE			(long double) (1 << Q_RESULT)

F32_UI32		ATANF32_X0[TABLE_SIZE];
F32_UI32		ATANF32_X2[TABLE_SIZE];
F32_UI32		ATANF32_Y0[TABLE_SIZE];
F32_UI32		ATANF32_S1[TABLE_SIZE];
F32_UI32		ATANF32_S2[TABLE_SIZE];
unsigned long	ATANF32_Y0i[TABLE_SIZE];
unsigned long	ATANF32_S1i[TABLE_SIZE];
unsigned long	ATANF32_S2i[TABLE_SIZE];

void		PrintResult(void);
void		ATANF32_Generate_Coefficients(void);
void		ATANF32_CheckError(F32_UI32 X);
void		ATANF32_Test(void);
float		ATANF32_Hardware_Emulation(float X);
float		ATANF32_FPUFastRTS_Emulation(float X);

//===========================================================================
// Start Of Program: main
//===========================================================================

int _tmain(int argc, _TCHAR* argv[])
{        
 	printf("\nTest TMU ATANF32 Algorithm, Version %s, Table Size %3d", VERSION, TABLE_SIZE);
	printf("\nCopyright (c) Texas Instruments Inc. 2010-2011");

	sprintf(OutputFileName, "ATANF32_Results_float_Q%2d_TableSize%3d.txt", Q_RESULT, TABLE_SIZE);

 	if( (OutPtr = fopen(OutputFileName, "w+")) == NULL )
		{  
		printf("\n");
		printf("\nERROR: Could Not Open %s File For Output.", _strupr(OutputFileName));
		printf("\n");
		exit(0);
 		}           

  	fprintf(OutPtr,  ";;##########################################################################");
	fprintf(OutPtr,"\n;;");
	fprintf(OutPtr,"\n;;Title:     TMU ATANF32 Algorithm Test Results");
	fprintf(OutPtr,"\n;;");
	fprintf(OutPtr,"\n;;Version:   %s", VERSION );
	fprintf(OutPtr,"\n;;");
	fprintf(OutPtr,"\n;;TableSize: %3d", TABLE_SIZE );
	fprintf(OutPtr,"\n;;");
	fprintf(OutPtr,"\n;;##########################################################################");
	fprintf(OutPtr,"\n");
	fprintf(OutPtr,"\n");

	// Run algorithm:
	ATANF32_Generate_Coefficients();
	ATANF32_Test();

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
// ATANF32 Test Programs:
//===========================================================================

void ATANF32_CheckError(F32_UI32 X)
{
	long double X_f64;
	long double	Y1_f64;
	long double Y1_temp_f64;
	long double Y1_error_f64;

	// Increment total test count:
	TestCount = TestCount + 1.0;

	// Generate Precise Reefernce Value Y1:
	X_f64 = (long double) X.f32;
	Y1_f64 = atan(X_f64) * INV2PI;
	Y1_f64 = Y1_f64;

	Y1_temp_f64 = Y1_f64;

	// Calculate Hardware Emulation Value Y3:
	Y3.f32 = ATANF32_Hardware_Emulation(X.f32);

	if(Y1_temp_f64 > ((long double) Y3.f32))
		{
		Y1_error_f64 = Y1_temp_f64 - ((long double) Y3.f32);
		if(Y1_error_f64 > ErrorMaxY3posF64)
			ErrorMaxY3posF64 = Y1_error_f64;
		ErrorCountY3posF64 = ErrorCountY3posF64 + 1.0;
		ErrorAvgY3posF64 = ErrorAvgY3posF64 + Y1_error_f64;
		}
	if(Y1_temp_f64 < ((long double) Y3.f32))
		{
		Y1_error_f64 = ((long double) Y3.f32) - Y1_temp_f64;
		if(Y1_error_f64 > ErrorMaxY3negF64)
			ErrorMaxY3negF64 = Y1_error_f64;
		ErrorCountY3negF64 = ErrorCountY3negF64 + 1.0;
		ErrorAvgY3negF64 = ErrorAvgY3negF64 + Y1_error_f64;
		}

	// Calculate FastRTS Emulation Value Y4:
	Y4.f32  = ATANF32_FPUFastRTS_Emulation(X.f32);

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
	fprintf(OutPtr,"\nError For Hardware Emulation : pos (Max, Avg, Count) > %16.14f, %16.14f, %16.1f", (ErrorMaxY3posF64 * Q_SCALE), ((ErrorAvgY3posF64/ErrorCountY3posF64) * Q_SCALE), ErrorCountY3posF64);
	fprintf(OutPtr,"\n                             : neg (Max, Avg, Count) > %16.14f, %16.14f, %16.1f", (ErrorMaxY3negF64 * Q_SCALE), ((ErrorAvgY3negF64/ErrorCountY3negF64) * Q_SCALE), ErrorCountY3negF64);
	fprintf(OutPtr,"\nError For FastRTS  Emulation : pos (Max, Avg, Count) > %16.14f, %16.14f, %16.1f", (ErrorMaxY4posF64 * Q_SCALE), ((ErrorAvgY4posF64/ErrorCountY4posF64) * Q_SCALE), ErrorCountY4posF64);
	fprintf(OutPtr,"\n                             : neg (Max, Avg, Count) > %16.14f, %16.14f, %16.1f", (ErrorMaxY4negF64 * Q_SCALE), ((ErrorAvgY4negF64/ErrorCountY4negF64) * Q_SCALE), ErrorCountY4negF64);
}

void ATANF32_Test(void)
{

	fprintf(OutPtr,"\nSummary Of Errors With Respect To Precise Reference Value:");
	fprintf(OutPtr,"\n\nTesting: ATANF32, Table Size = %4d, Q Scaling = Q%2d", TABLE_SIZE, Q_RESULT);
	fprintf(OutPtr,"\n===========================================================================\n");

	printf("\n Test ATANF32 Using Q%2d Scaling, Return (float)", Q_RESULT);

 	// Clear test count:
	TestCount = 0.0;

  	// Clear error logs:
	ErrorMaxY3posF64 = 0.0;
	ErrorMaxY3negF64 = 0.0;
	ErrorAvgY3posF64 = 0.0;
	ErrorAvgY3negF64 = 0.0;
	ErrorCountY3posF64 = 0.0;
	ErrorCountY3negF64 = 0.0;

	ErrorMaxY4posF64 = 0.0;
	ErrorMaxY4negF64 = 0.0;
	ErrorAvgY4posF64 = 0.0;
	ErrorAvgY4negF64 = 0.0;
	ErrorCountY4posF64 = 0.0;
	ErrorCountY4negF64 = 0.0;

	printf("\n Test 0.0           <= X <  0.00048828125");
	fprintf(OutPtr,"\n\n Test 0.0           <= X <  0.00048828125");
	X.f32 = 0.0;
	while(X.f32 < 0.00048828125)
		{
		ATANF32_CheckError(X);
		// Increment Input Value:
		X.f32 = X.f32 + 2.910381556e-11;
		};
	PrintResult();

	printf("\n Test 0.00048828125 <= X <  0.0009765625");
	fprintf(OutPtr,"\n\n Test 0.00048828125 <= X <  0.0009765625");
	X.f32 = 0.00048828125;
	while(X.f32 < 0.0009765625)
		{
		ATANF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	PrintResult();

	printf("\n Test 0.0009765625  <= X <  0.001953125");
	fprintf(OutPtr,"\n\n Test 0.0009765625  <= X <  0.001953125");
	X.f32 = 0.0009765625;
	while(X.f32 < 0.001953125)
		{
		ATANF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	PrintResult();

	printf("\n Test 0.001953125   <= X <  0.00390625");
	fprintf(OutPtr,"\n\n Test 0.001953125   <= X <  0.00390625");
	X.f32 = 0.001953125;
	while(X.f32 < 0.00390625)
		{
		ATANF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	PrintResult();

	printf("\n Test 0.00390625    <= X <  0.0078125");
	fprintf(OutPtr,"\n\n Test 0.00390625    <= X <  0.0078125");
	X.f32 = 0.00390625;
	while(X.f32 < 0.0078125)
		{
		ATANF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	PrintResult();

	printf("\n Test 0.0078125     <= X <  0.015625");
	fprintf(OutPtr,"\n\n Test 0.0078125     <= X <  0.015625");
	X.f32 = 0.0078125;
	while(X.f32 < 0.015625)
		{
		ATANF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	PrintResult();

	printf("\n Test 0.015625      <= X <  0.03125");
	fprintf(OutPtr,"\n\n Test 0.015625      <= X <  0.03125");
	X.f32 = 0.015625;
	while(X.f32 < 0.03125)
		{
		ATANF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	PrintResult();

	printf("\n Test 0.03125       <= X <  0.0625");
	fprintf(OutPtr,"\n\n Test 0.03125       <= X <  0.0625");
	X.f32 = 0.03125;
	while(X.f32 < 0.0625)
		{
		ATANF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	PrintResult();

	printf("\n Test 0.0625        <= X <  0.125");
	fprintf(OutPtr,"\n\n Test 0.0625        <= X <  0.125");
	X.f32 = 0.0625;
	while(X.f32 < 0.125)
		{
		ATANF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	PrintResult();

	printf("\n Test 0.125         <= X <  0.25");
	fprintf(OutPtr,"\n\n Test 0.125         <= X <  0.25");
	X.f32 = 0.125;
	while(X.f32 < 0.25)
		{
		ATANF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	PrintResult();

	printf("\n Test 0.25          <= X <  0.5");
	fprintf(OutPtr,"\n\n Test 0.25          <= X <  0.5");
	X.f32 = 0.25;
	while(X.f32 < 0.5)
		{
		ATANF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	PrintResult();

	printf("\n Test 0.5           <= X <  1.0");
	fprintf(OutPtr,"\n\n Test 0.5           <= X <  1.0");
	X.f32 = 0.5;
    while(X.f32 < 1.0)
		{
		ATANF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	PrintResult();

	printf("\n Test 1.0");
	fprintf(OutPtr,"\n\n Test 1.0");
	X.f32 = 1.0;
 	ATANF32_CheckError(X);

	PrintResult();
}

//===========================================================================
// ATANF32 Coefficient Table Generator:
//===========================================================================

void ATANF32_Generate_Coefficients(void)
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

	X0_f64  =  0.0L;
	dx0_f64 =  0.00390625L;				// 1/(TABLE_SIZE * 2), TABLE_SIZE == 128
	X1_f64  = X0_f64 + dx0_f64;		
	X2_f64  = X1_f64 + dx0_f64;

	for(i=0; i < TABLE_SIZE; i++)
		{
		if( i == 0 )
			{
			// Table location 0 is special case:
			Y0_f64 = 0.0L;
			S1_f64 = 0.159151705194863L * 2.0L;		// = 2 * (128 * atan(1/128) / 2PI)
			S2_f64 = 0.0L;
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
			S1_f64 = a1 + 2.0L*a2*X1_f64;
			S1_f64 = S1_f64 * INV2PI;
			S2_f64 = a2;
			S2_f64 = S2_f64 * INV2PI;

			// Best values for both ATANF32:
			Y0_f64 = Y0_f64 * 1.0L;
			S1_f64 = S1_f64 * 1.0L;
			S2_f64 = S2_f64 * 1.0L;
			}

		ATANF32_X0[i].f32 = (float) X0_f64;
		ATANF32_X2[i].f32 = (float) X2_f64;
		ATANF32_Y0[i].f32 = (float) Y0_f64;
		ATANF32_S1[i].f32 = (float) S1_f64;
		ATANF32_S2[i].f32 = (float) S2_f64;

		// Store Y0 as +ve Q30 value:
		temp = Y0_f64 * 1073741824.0L;
		if( temp >= 0.0)
			temp = temp + 0.5L;
		else
			temp = temp - 0.5L;
		ATANF32_Y0i[i] = (unsigned long) temp;
			
		// Store S1 as +ve Q22 value:
		temp = S1_f64 * 4194304.0L;
		if( temp >= 0.0)
			temp = temp + 0.5L;
		else
			temp = temp - 0.5L;
		ATANF32_S1i[i] = (unsigned long) temp;

		// Store S2 as +ve Q16 value:
		temp = S2_f64 * 65536.0L;
		if( temp >= 0.0)
			temp = temp + 0.5L;
		else
			temp = temp - 0.5L;
		ATANF32_S2i[i] = (unsigned long) -temp;

		X0_f64 = X2_f64;
		X1_f64 = X0_f64 + dx0_f64;		
		X2_f64 = X1_f64 + dx0_f64;
		}

	if(PRINT_TABLE == 1)
		{
		fprintf(OutPtr,"\n\nStart Of Coefficients Table:\n");
		for(i=0; i < TABLE_SIZE; i++)
			{
			fprintf(OutPtr,"\n%4d | x1 = %16.12f  x2 = %16.12f | Y0 = %16.12f   S1 = %16.12f   S2 = %16.12f | Y0i = %16u   S1i = %16u   S2i = %16u", i, ATANF32_X0[i].f32, ATANF32_X2[i].f32, ATANF32_Y0[i].f32, ATANF32_S1[i].f32, ATANF32_S2[i].f32, ATANF32_Y0i[i], ATANF32_S1i[i], ATANF32_S2i[i]);
			}
		fprintf(OutPtr,"\n\nEnd of data.\n");
		}
}

//===========================================================================
// ATANF32 Algorithms:
//===========================================================================

float	ATANF32_Hardware_Emulation(float X)
{
	unsigned int	table_index;
	long			dx;
	long			temp;
	i64				dx_dx;
	i64				dx_dx_S2;
	i64				dx_S1;
	i64				sum;
	i64				dx_S1_ADD_dx_dx_S2;
	i64				dx_S1_SUB_dx_dx_S2;
	i64				Y0i;
	i64				S2i;
	i64				S1i;
	
	F32_UI32 tempX;
	F32_UI32 Y;

	unsigned long	Si;			// Bit  31    Sign     Of Input Value
	unsigned long	Ei;			// Bits 30:23 Exponent Of Input Value
	unsigned long	Mi;			// Bits 22:0  Mantissa Of Input Value
	unsigned long	So;			// Bit  31    Sign     Of Output Value
	unsigned long	Eo;			// Bits 30:23 Exponent Of Output Value
	unsigned long	Mo;			// Bits 22:0  Mantissa Of Output Value

	unsigned int	Boundary;	// 0 = none;
								// 1 = return boundary condition value

	//----------------------------------------------------------------------------------------------------------------------------
	// Pipeline Phase 1: Format input and extract table index and dx value:

	// Extract sign, exp and mantissa 0f input:
	tempX.f32 = X;
	Si = (tempX.ui32 & 0x80000000);
	Ei = (tempX.ui32 & 0x7F800000);
	Mi = (tempX.ui32 & 0x007FFFFF);

	// Set default values of data:
	So = 0x00000000L;								// Set default sign of result (+ve)
	dx = 0;
	Boundary = 0;
	table_index = 0;

	// Check limits:
	if( Ei <= 0x2F800000L )							// If X <= 1/2^32, value too small, return zero
		{
		So = 0x00000000;
		Eo = 0x00000000;
		Mo = 0x00000000;
		Y.ui32 = So + Eo + Mo;
		Boundary = 1;												
		}
	else if( Ei >= 0x3F800000L )					// If X >= 1.0, saturate to and return 0.125
		{
		So = Si;
		Eo = 0x3E000000L;
		Mo = 0x00000000L;
		Y.ui32 = So + Eo + Mo;
		Boundary = 1;												
		}
	else 
		{
		So = Si;

		// If X < 0.0078125 :
		if( Ei <= 0x3B800000L )										
			{
			table_index = 0;
			dx = ((Mi | 0x00800000L)) >> (119 - (Ei >> 23));
			}
		else
		// If 0.0078125 <= X < 1.0 :
			{
			table_index = ((Mi | 0x00800000L) << 7) >> (150 - (Ei >> 23));
			dx = (Mi << ((Ei >> 23) - 118)) & 0x01FFFFFFL;
			if( (dx & 0x01000000L) == 0 )
				dx = (0xFF000000L ^ (dx & 0x01FFFFFFL));			// Q33
			else
				dx = (0x01000000L ^ (dx & 0x01FFFFFFL));			// Q33
			}

		}

	//----------------------------------------------------------------------------------------------------------------------------
	// Pipeline Phase 2: Get ROM table values and calcualte dx*dx

	S2i	= (i64) ATANF32_S2i[table_index];	// 20.Q14, +ve number with only bits 0 to 19 are valid (S2i[19:0])
	S1i = (i64) ATANF32_S1i[table_index];	// 24.Q21, +ve number with only bits 0 to 23 are valid (S1i[23:0])
	Y0i = (i64) ATANF32_Y0i[table_index];	// 30.Q30, +ve number with only bits 0 to 29 are valid (Y0i[29:0])

	// Calculate: dx_dx = ((dx >> 10) * (dx >> 10)) >> 11;
	//
	// The input range of dx for SINF32 & COSF32 is:
	//
	// max:  0x00800000
	//       0x007FFFFF
	//       ...
	//       0x00000001
	//       0x00000000
	//       0xFFFFFFFF
	//       ...
	//       0xFF800001
	//       0xFF800000
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
	// This operation performs a 18-bit * 20-bit multiply with a 38-bit result (mpy_result[38:0] = dx_dx[17:0] * S2i[19:0]):
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

	// For SINF32 & COSF32 & ATANF32 & SQRTF32 calculate:
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
		// if dx positive: perform 32-bit add
		sum = Y0i + dx_S1_SUB_dx_dx_S2;		
	else
		// if dx negative: perform 32-bit sub
		sum = Y0i - dx_S1_ADD_dx_dx_S2; 
	
	//----------------------------------------------------------------------------------------------------------------------------
	// Pipeline Phase 5: Format output
	if( Boundary == 1 )
		return	Y.f32;			// Return boundary condition value detected in Pipeline Phase 1
	else
		{
		// If sum is zero or negative, return zero:
		if(sum <= 0)
			return 0.0;

		// Normalize result and adjust exponent and mantissa:
		Eo = 0x3F800000L;			// Start with Exp = 2^0
		Mo = (long) sum;
		while((Mo & 0x40000000L) == 0)
			{
			Mo = Mo << 1;
			Eo = Eo - 0x00800000L;
			}
		Mo = (Mo >> 7) & 0x007FFFFF;
		
		Y.ui32 = So + Eo + Mo;
		}

		return	Y.f32;
}

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

//===========================================================================
// No more.
//===========================================================================
