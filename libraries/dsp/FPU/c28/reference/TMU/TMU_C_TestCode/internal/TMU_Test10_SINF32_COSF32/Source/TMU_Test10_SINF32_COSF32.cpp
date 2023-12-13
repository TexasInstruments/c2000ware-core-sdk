//*****************************************************************************
//
// FILE:     TMU_Test10_SINF32_COSF32.cpp
//
// TITLE:    Utility To Test TMU SINF32 & COSF32 Algorithms, Table Size = 128
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
//*****************************************************************************
// COMPILER:  This utility was compiled using Microsft Visual C++ Express
//            in Win32 console mode. 
//=============================================================================
// SINF32/COSF32 TMU Algorithm Description:
//=============================================================================
//
//  Y = SIN_PU(X)  
//  Y = COS_PU(X)
//
//  Where:   -1.0 < X < 1.0
//
//  Using Eulers formula:
//
//  X = x0(n) + dz
//  
//  SIN_PU(X) = Y0 + dz*S1 + dz*dz*S2
//
//  Where:   Y0 =  SIN(x0(n)*2pi)
//           S1 =  COS(x0(n)*2pi)*2pi
//           S2 = -SIN(x0(n)*2pi)*2pi*2pi*/2
//
//  With above equation, require table size 256 to achieve required accuracy.
//
//  To improve accuracy and reduce required table size to 128, the above equation 
//  is re-arranged by using following:
//
//  X = x1(n) +/- dx            (x1(n) = mid-point between x0(n) samples)
//
//  Where:   x1(n) = x0 + dx0
//           dx0 = 1/1024 = 0.0009765625
//
//  SIN_PU(X) = Y0 + dx*S1 + dx*dx*S2
//
//  Where:   Y0 =  SIN(x1*2pi)
//           S1 =  COS(x0*2pi)*2pi - dx0*SIN(x0*2pi)*2pi*2pi - dx0*dx0*COS(x0*2pi)*2pi*2pi*2pi/2
//           S2 = -SIN(x0*2pi)*2pi*2pi*/2 - dx0*COS(x0*2pi)*2pi*2pi*2pi/2
//
//  Only need first quarter of SIN table is necessary (because of symmentry):
//
//  x0=0.0     x0=0.001953125   x0=0.00390625   x0=0.0078125          x0=0.248046875   x0=0.25
//   |               |               |               |                     |               |
//   |-------dz----->|-------dz----->|------dz------>|.....................|------dz------>|
//  K=0           K=1/512         K=2/512         K=3/512             K=127/512
//   |<--dx--|--dx-->|<--dx--|--dx-->|<--dx--|--dx-->|.....................|<--dx--|--dx-->|
//           |               |               |                                     |
//      x1=0.0009765625 x1=0.0029296875 x1=0.0048828125                       0.2490234375
//   
//  x0 = n/512    for n = 0 to 127
//  (0.0) <= dz < (1/512 = 0.001953125)
//  x1 = n/512 + 1/1024   for n = 0 to 127
//  (-1/1024 = -0.0009765625) <= dx < (+1/1024 = 0.0009765625)
//
//  SIN Table:
// -----+-----------------------+--------------------------------------------------------------------------+
//    0 | x1 =   0.000976562500 | Y0  =   0.006135885138   S1  =   6.283054351807   S2  =  -0.121118269861 |
//      |                       | Y0i =          6588356   S1i =       1686594589   S2i =         -8128109 |
// -----+-----------------------+--------------------------------------------------------------------------+
//    1 | x1 =   0.002929687500 | Y0  =   0.018406730145   S1  =   6.282108306885   S2  =  -0.363339602947 |
//      |                       | Y0i =         19764077   S1i =       1686340594   S2i =        -24383308 |
// -----+-----------------------+--------------------------------------------------------------------------+
//    2 | x1 =   0.004882812500 | Y0  =   0.030674804002   S1  =   6.280216217041   S2  =  -0.605506241322 |
//      |                       | Y0i =         32936821   S1i =       1685832641   S2i =        -40634835 |
// -----+-----------------------+--------------------------------------------------------------------------+
//    3 | x1 =   0.006835937500 | Y0  =   0.042938258499   S1  =   6.277378082275   S2  =  -0.847581684589 |
//      |                       | Y0i =         46104605   S1i =       1685070809   S2i =        -56880242 |
// -----+-----------------------+--------------------------------------------------------------------------+
//    .
//    .
// -----+-----------------------+--------------------------------------------------------------------------+
//  125 | x1 =   0.245117187500 | Y0  =   0.999529480934   S1  =   0.192734852433   S2  = -19.730291366577 |
//      |                       | Y0i =       1073236594   S1i =         51736866   S2i =      -1324077431 |
// -----+-----------------------+--------------------------------------------------------------------------+
//  126 | x1 =   0.247070312500 | Y0  =   0.999830603600   S1  =   0.115652419627   S2  = -19.736236572266 |
//      |                       | Y0i =       1073559966   S1i =         31045211   S2i =      -1324476385 |
// -----+-----------------------+--------------------------------------------------------------------------+
//  127 | x1 =   0.249023437500 | Y0  =   0.999981224537   S1  =   0.038552582264   S2  = -19.739208221436 |
//      |                       | Y0i =       1073721665   S1i =         10348880   S2i =      -1324675878 |
// -----+-----------------------+--------------------------------------------------------------------------+
//  Note:     Y0i stored as Q30 number in table  ( -2.0 <= range <  2.0)
//            S1i stored as Q28 number in table  ( -8.0 <= range <  8.0)
//            S2i stored as Q26 number in table  (-32.0 <= range < 32.0)
//
//  Using the above table, the SIN_PU value for any X can be calculated as follows:
//
//  For SIN_PU:
//      table_index = integer(X*1024)
//      dx          = fraction(X*1024)/1024
//
//      if(0 <= |X| < 0.25)
//          SIN_PU(X) = Y0[table_index] + dx*S1[table_index] + dx*dx*S2[table_index];
//      if(0.25 <= |X| < 0.5)
//          dx = 1.0 - dx;
//          SIN_PU(X) = Y0[255 - table_index] + dx*S1[255 - table_index] + dx*dx*S2[255 - table_index];
//      if(0.5 <= |X| < 0.75)
//          SIN_PU(X) = -(Y0[table_index] + dx*S1[table_index] + dx*dx*S2[table_index]);
//      if(0.75 <= |X| < 1.0)
//          dx = 1.0 - dx;
//          SIN_PU(X) = -(Y0[255 - table_index] + dx*S1[255 - table_index] + dx*dx*S2[255 - table_index]);
//
//  Because of symmetry between SIN and COS, we can re-use SIN table to calculate COS_PU as follows:
//
//  For COS_PU:
//      table_index = integer(X*1024)
//      dx          = fraction(X*1024)/1024
//
//      if(0 <= |X| < 0.25)
//          dx = 1.0 - dx;
//          COS_PU(X) = Y0[255 - table_index] + dx*S1[255 - table_index] + dx*dx*S2[255 - table_index];
//      if(0.25 <= |X| < 0.5)
//          dx = 1.0 - dx;
//          COS_PU(X) = -(Y0[table_index] + dx*S1[table_index] + dx*dx*S2[table_index]);
//      if(0.5 <= |X| < 0.75)
//          dx = 1.0 - dx;
//          COS_PU(X) = -(Y0[255 - table_index] + dx*S1[255 - table_index] + dx*dx*S2[255 - table_index]);
//      if(0.75 <= |X| < 1.0)
//          COS_PU(X) = Y0[table_index] + dx*S1[table_index] + dx*dx*S2[table_index];
//
//===========================================================================

#include "stdafx.h"

#define	VERSION	"10.0"

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

#define	Q_RESULT		24								// Q24, Q25, Q26,..
#define	RETURN_FLOAT	1								// 1 = return float value, 0 = return long value
#define	SIN_COS_MODE	0								// 0 = calculate SINF32, 1 = calculate COSF32

#define	Q_SCALE			(long double) (1 << Q_RESULT)

F32_UI32	SINF32_X0[TABLE_SIZE];
F32_UI32	SINF32_X2[TABLE_SIZE];
F32_UI32	SINF32_Y0[TABLE_SIZE];
F32_UI32	SINF32_S1[TABLE_SIZE];
F32_UI32	SINF32_S2[TABLE_SIZE];
long		SINF32_Y0i[TABLE_SIZE];
long		SINF32_S1i[TABLE_SIZE];
long		SINF32_S2i[TABLE_SIZE];

long		dx_max;
long		dx_min;
i64			dx_dx_max;
i64			dx_dx_min;

void		PrintResult(void);

void		Generate_Coefficients(void);

void		SINF32_CheckError(F32_UI32 X);
void		SINF32_Test(void);

void		COS32_CheckError(F32_UI32 X);
void		COSF32_Test(void);

#if (RETURN_FLOAT == 1)
float		SINF32_Hardware_Emulation(float X);
float		COSF32_Hardware_Emulation(float X);
#else
long		SINF32_Hardware_Emulation(float X);
long		COSF32_Hardware_Emulation(float X);
#endif

float		SINF32_FPUFastRTS_Emulation(float X);
float		COSF32_FPUFastRTS_Emulation(float X);

//===========================================================================
// Start Of Program: main
//===========================================================================

int _tmain(int argc, _TCHAR* argv[])
{        
 	printf("\nTest TMU SINF32 and COSF32 Algorithms, Version %s, Table Size %3d", VERSION, TABLE_SIZE);
	printf("\nCopyright (c) Texas Instruments Inc. 2010-2011");

	#if	(RETURN_FLOAT == 1)
		sprintf(OutputFileName, "SINF32_COSF32_Results_float_Q%2d_TableSize%3d.txt", Q_RESULT, TABLE_SIZE);
 	#else
		sprintf(OutputFileName, "SINF32_COSF32_Results_long_Q%2d_TableSize%3d.txt", Q_RESULT, TABLE_SIZE);
	#endif

 	if( (OutPtr = fopen(OutputFileName, "w+")) == NULL )
		{  
		printf("\n");
		printf("\nERROR: Could Not Open %s File For Output.", _strupr(OutputFileName));
		printf("\n");
		exit(0);
 		}           

  	fprintf(OutPtr,  ";;##########################################################################");
	fprintf(OutPtr,"\n;;");
	fprintf(OutPtr,"\n;;Title:     TMU SINF32 and COSF32 Algorithm Test Results");
	fprintf(OutPtr,"\n;;");
	fprintf(OutPtr,"\n;;Version:   %s", VERSION );
	fprintf(OutPtr,"\n;;");
	fprintf(OutPtr,"\n;;TableSize: %3d", TABLE_SIZE );
	fprintf(OutPtr,"\n;;");
	fprintf(OutPtr,"\n;;##########################################################################");
	fprintf(OutPtr,"\n");
	fprintf(OutPtr,"\n");

	// Run algorithm:
	Generate_Coefficients();
	SINF32_Test();
	COSF32_Test();

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
// SINF32 and COSF32 Test Programs:
//===========================================================================

void SINF32_CheckError(F32_UI32 X)
{
	long double X_f64;
	long double	Y1_f64;
	long double Y1_temp_f64;
	long double Y1_error_f64;

	// Increment total test count:
	TestCount = TestCount + 1.0;

	// Generate Precise Reefernce Value Y1:
	X_f64 = (long double) X.f32;
	Y1_f64 = sin(X_f64 * 2.0L * PI);

	Y1_temp_f64 = Y1_f64;

	// Calculate Hardware Emulation Value Y3:
	#if (RETURN_FLOAT == 1)
		Y3.f32 = SINF32_Hardware_Emulation(X.f32);

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
	#else
		Y3.i32 = SINF32_Hardware_Emulation(X.f32);	// Value returned as Q30

		Y3.i32 = Y3.i32 >> (30 - Q_RESULT);	
	#endif

	// Calculate FastRTS Emulation Value Y4:
	Y4.f32  = SINF32_FPUFastRTS_Emulation(X.f32);

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

void COSF32_CheckError(F32_UI32 X)
{
	long double X_f64;
	long double	Y1_f64;
	long double Y1_temp_f64;
	long double Y1_error_f64;

	// Generate Precise Reefernce Value Y1:
	X_f64 = (long double) X.f32;
	Y1_f64 = cos(X_f64 * 2.0L * PI);

	Y1_temp_f64 = Y1_f64;

	// Calculate Hardware Emulation Value Y3:
	#if (RETURN_FLOAT == 1)
		Y3.f32 = COSF32_Hardware_Emulation(X.f32);

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
	#else
		Y3.i32 = COSF32_Hardware_Emulation(X.f32);	// Value returned as Q30

		Y3.i32 = Y3.i32 >> (30 - Q_RESULT);	
	#endif

	// Calculate FastRTS Emulation Value Y4:
	Y4.f32  = COSF32_FPUFastRTS_Emulation(X.f32);

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

void SINF32_Test(void)
{
	fprintf(OutPtr,"\nSummary Of Errors With Respect To Precise Reference Value:");
	fprintf(OutPtr,"\n\nTesting: SINF32, Table Size = %4d, Q Scaling = Q%2d", TABLE_SIZE, Q_RESULT);
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

	ErrorMaxY4posF64 = 0.0;
	ErrorMaxY4negF64 = 0.0;
	ErrorAvgY4posF64 = 0.0;
	ErrorAvgY4negF64 = 0.0;
	ErrorCountY4posF64 = 0.0;
	ErrorCountY4negF64 = 0.0;

	dx_min = 1;
	dx_max = -1;
	dx_dx_min = 1;
	dx_dx_max = -1;

	#if (RETURN_FLOAT == 1)
		printf("\n Test SINF32 Using Q%2d Scaling, Return (float)", Q_RESULT);
	#else
		printf("\n Test SINF32 Using Q%2d Scaling, Return (long)", Q_RESULT);
	#endif

	printf("\n Test 0.0           <= X <  0.00048828125");
	fprintf(OutPtr,"\n\n Test 0.0           <= X <  0.00048828125");
	X.f32 = 0.0;
	while(X.f32 < 0.00048828125)
		{
		SINF32_CheckError(X);
		// Increment Input Value:
		X.f32 = X.f32 + 2.910381556e-11;
		};
	PrintResult();

	printf("\n Test 0.00048828125 <= X <  0.0009765625");
	fprintf(OutPtr,"\n\n Test 0.00048828125 <= X <  0.0009765625");
	X.f32 = 0.00048828125;
	while(X.f32 < 0.0009765625)
		{
		SINF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	PrintResult();

	printf("\n Test 0.0009765625  <= X <  0.001953125");
	fprintf(OutPtr,"\n\n Test 0.0009765625  <= X <  0.001953125");
	X.f32 = 0.0009765625;
	while(X.f32 < 0.001953125)
		{
		SINF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	PrintResult();

	printf("\n Test 0.001953125   <= X <  0.00390625");
	fprintf(OutPtr,"\n\n Test 0.001953125   <= X <  0.00390625");
	X.f32 = 0.001953125;
	while(X.f32 < 0.00390625)
		{
		SINF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	PrintResult();

	printf("\n Test 0.00390625    <= X <  0.0078125");
	fprintf(OutPtr,"\n\n Test 0.00390625    <= X <  0.0078125");
	X.f32 = 0.00390625;
	while(X.f32 < 0.0078125)
		{
		SINF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	PrintResult();

	printf("\n Test 0.0078125     <= X <  0.015625");
	fprintf(OutPtr,"\n\n Test 0.0078125     <= X <  0.015625");
	X.f32 = 0.0078125;
	while(X.f32 < 0.015625)
		{
		SINF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	PrintResult();

	printf("\n Test 0.015625      <= X <  0.03125");
	fprintf(OutPtr,"\n\n Test 0.015625      <= X <  0.03125");
	X.f32 = 0.015625;
	while(X.f32 < 0.03125)
		{
		SINF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	PrintResult();

	printf("\n Test 0.03125       <= X <  0.0625");
	fprintf(OutPtr,"\n\n Test 0.03125       <= X <  0.0625");
	X.f32 = 0.03125;
	while(X.f32 < 0.0625)
		{
		SINF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	PrintResult();

	printf("\n Test 0.0625        <= X <  0.125");
	fprintf(OutPtr,"\n\n Test 0.0625        <= X <  0.125");
	X.f32 = 0.0625;
	while(X.f32 < 0.125)
		{
		SINF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	PrintResult();

	printf("\n Test 0.125         <= X <  0.25");
	fprintf(OutPtr,"\n\n Test 0.125         <= X <  0.25");
	X.f32 = 0.125;
	while(X.f32 < 0.25)
		{
		SINF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	PrintResult();

	printf("\n Test 0.25          <= X <  0.5");
	fprintf(OutPtr,"\n\n Test 0.25          <= X <  0.5");
	X.f32 = 0.25;
	while(X.f32 < 0.5)
		{
		SINF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	PrintResult();

	printf("\n Test 0.5           <= X <  0.75");
	fprintf(OutPtr,"\n\n Test 0.5           <= X <  0.75");
	X.f32 = 0.5;
    while(X.f32 < 0.75)
		{
		SINF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	PrintResult();

	printf("\n Test 0.75          <= X <  1.0");
	fprintf(OutPtr,"\n\n Test 0.75          <= X <  1.0");
	X.f32 = 0.75;
    while(X.f32 < 1.0)
		{
		SINF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	PrintResult();

	printf("\n Test 1.0           <= X <  2.0");
	fprintf(OutPtr,"\n\n Test 1.0           <= X <  2.0");
	X.f32 = 1.0;
    while(X.f32 < 2.0)
		{
		SINF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	PrintResult();

	printf("\n Test 2.0           <= X <  4.0");
	fprintf(OutPtr,"\n\n Test 2.0           <= X <  4.0");
	X.f32 = 2.0;
    while(X.f32 < 4.0)
		{
		SINF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	PrintResult();

	printf("\n Test 4.0           <= X <  8.0");
	fprintf(OutPtr,"\n\n Test 4.0           <= X <  8.0");
	X.f32 = 4.0;
    while(X.f32 < 8.0)
		{
		SINF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	PrintResult();

	printf("\n Test Values: -3.0 <= X <= 3.0 in 0.125 increments");
	fprintf(OutPtr,"\n\n Test Values: -3.0 <= X <= 3.0 in 0.125 increments");
	X.f32 = -3.0;
	do	{
		SINF32_CheckError(X);
		X.f32 = X.f32 + 0.125;
	} while( X.f32 <= 3.0 );
	PrintResult();
}

void COSF32_Test(void)
{
	fprintf(OutPtr,"\nSummary Of Errors With Respect To Precise Reference Value:");
	fprintf(OutPtr,"\n\nTesting: COSF32, Table Size = %4d, Q Scaling = Q%2d", TABLE_SIZE, Q_RESULT);
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

	ErrorMaxY4posF64 = 0.0;
	ErrorMaxY4negF64 = 0.0;
	ErrorAvgY4posF64 = 0.0;
	ErrorAvgY4negF64 = 0.0;
	ErrorCountY4posF64 = 0.0;
	ErrorCountY4negF64 = 0.0;

	#if (RETURN_FLOAT == 1)
		printf("\n Test COSF32 Using Q%2d Scaling, Return (float)", Q_RESULT);
	#else
		printf("\n Test COSF32 Using Q%2d Scaling, Return (long)", Q_RESULT);
	#endif

	printf("\n Test 0.0           <= X <  0.00048828125");
	fprintf(OutPtr,"\n\n Test 0.0           <= X <  0.00048828125");
	X.f32 = 0.0;
	while(X.f32 < 0.00048828125)
		{
		COSF32_CheckError(X);
		// Increment Input Value:
		X.f32 = X.f32 + 2.910381556e-11;
		};
	PrintResult();

	printf("\n Test 0.00048828125 <= X <  0.0009765625");
	fprintf(OutPtr,"\n\n Test 0.00048828125 <= X <  0.0009765625");
	X.f32 = 0.00048828125;
	while(X.f32 < 0.0009765625)
		{
		COSF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	PrintResult();

	printf("\n Test 0.0009765625  <= X <  0.001953125");
	fprintf(OutPtr,"\n\n Test 0.0009765625  <= X <  0.001953125");
	X.f32 = 0.0009765625;
	while(X.f32 < 0.001953125)
		{
		COSF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	PrintResult();

	printf("\n Test 0.001953125   <= X <  0.00390625");
	fprintf(OutPtr,"\n\n Test 0.001953125   <= X <  0.00390625");
	X.f32 = 0.001953125;
	while(X.f32 < 0.00390625)
		{
		COSF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	PrintResult();

	printf("\n Test 0.00390625    <= X <  0.0078125");
	fprintf(OutPtr,"\n\n Test 0.00390625    <= X <  0.0078125");
	X.f32 = 0.00390625;
	while(X.f32 < 0.0078125)
		{
		COSF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	PrintResult();

	printf("\n Test 0.0078125     <= X <  0.015625");
	fprintf(OutPtr,"\n\n Test 0.0078125     <= X <  0.015625");
	X.f32 = 0.0078125;
	while(X.f32 < 0.015625)
		{
		COSF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	PrintResult();

	printf("\n Test 0.015625      <= X <  0.03125");
	fprintf(OutPtr,"\n\n Test 0.015625      <= X <  0.03125");
	X.f32 = 0.015625;
	while(X.f32 < 0.03125)
		{
		COSF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	PrintResult();

	printf("\n Test 0.03125       <= X <  0.0625");
	fprintf(OutPtr,"\n\n Test 0.03125       <= X <  0.0625");
	X.f32 = 0.03125;
	while(X.f32 < 0.0625)
		{
		COSF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	PrintResult();

	printf("\n Test 0.0625        <= X <  0.125");
	fprintf(OutPtr,"\n\n Test 0.0625        <= X <  0.125");
	X.f32 = 0.0625;
	while(X.f32 < 0.125)
		{
		COSF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	PrintResult();

	printf("\n Test 0.125         <= X <  0.25");
	fprintf(OutPtr,"\n\n Test 0.125         <= X <  0.25");
	X.f32 = 0.125;
	while(X.f32 < 0.25)
		{
		COSF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	PrintResult();

	printf("\n Test 0.25          <= X <  0.5");
	fprintf(OutPtr,"\n\n Test 0.25          <= X <  0.5");
	X.f32 = 0.25;
	while(X.f32 < 0.5)
		{
		COSF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	PrintResult();

	printf("\n Test 0.5           <= X <  0.75");
	fprintf(OutPtr,"\n\n Test 0.5           <= X <  0.75");
	X.f32 = 0.5;
    while(X.f32 < 0.75)
		{
		COSF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	PrintResult();

	printf("\n Test 0.75          <= X <  1.0");
	fprintf(OutPtr,"\n\n Test 0.75          <= X <  1.0");
	X.f32 = 0.75;
    while(X.f32 < 1.0)
		{
		COSF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	PrintResult();

	printf("\n Test 1.0           <= X <  2.0");
	fprintf(OutPtr,"\n\n Test 1.0           <= X <  2.0");
	X.f32 = 1.0;
    while(X.f32 < 2.0)
		{
		COSF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	PrintResult();

	printf("\n Test 2.0           <= X <  4.0");
	fprintf(OutPtr,"\n\n Test 2.0           <= X <  4.0");
	X.f32 = 2.0;
    while(X.f32 < 4.0)
		{
		COSF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	PrintResult();

	printf("\n Test 4.0           <= X <  8.0");
	fprintf(OutPtr,"\n\n Test 4.0           <= X <  8.0");
	X.f32 = 4.0;
    while(X.f32 < 8.0)
		{
		COSF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	PrintResult();

	printf("\n Test Values: -3.0 <= X <= 3.0 in 0.125 increments");
	fprintf(OutPtr,"\n\n Test Values: -3.0 <= X <= 3.0 in 0.125 increments");
	X.f32 = -3.0;
	do	{
		COSF32_CheckError(X);
		X.f32 = X.f32 + 0.125;
	} while( X.f32 <= 3.0 );
	PrintResult();
}

//===========================================================================
// SINF32 and COSF32 Coefficient Table Generator:
//===========================================================================

void Generate_Coefficients(void)
{
	int	i;

	F32_UI32 X0;
	F32_UI32 X2;

	long double		X0_f64;
	long double		Y0_f64;
	long double		S1_f64;
	long double		S2_f64;
	long double		temp;
	long double		x0;
	long double		x1;

	long double		dx0 = 0.0009765625L;		// 1/1024
	long double		C1 =   6.28318530718L;		// = 2pi
	long double		C2 = -19.73920880217L;		// = -(2pi)^2/2!
	long double		C3 = -41.34170224047L;		// = -(2pi)^3/3!

	// Initialize table for: 	0.0009765625 <= |X| <= (0.25 - 0.0009765625)
	X0.f32 = 0.0;
	for(i=0; i < TABLE_SIZE; i++)
		{

		X2.f32 = X0.f32 + 0.001953125;		// Step size = 2/1024

		X0_f64	= (long double) X0.f32;

		x0 = X0_f64 * C1;					// Convert X0 to radians
		x1 = (X0_f64 + dx0) * C1;

		Y0_f64 = sin(x1);					// Y value at mid-point between X0 and X2
		S1_f64 = (cos(x0) * C1) + (2 * dx0 * sin(x0) * C2) + (3 * dx0 * dx0 * cos(x0) * C3);
		S2_f64 = (sin(x0) * C2) + (3 * dx0 * cos(x0) * C3);

		// Best values for SINF32:
//		Y0_f64 = Y0_f64 * 1.00000004L;
//		S1_f64 = S1_f64 * 1.000001L;

		// Best values for COSF32:
//		Y0_f64 = Y0_f64 * 1.00000005L;
//		S1_f64 = S1_f64 * 0.999995L;

		// Best values for both SINF32 and COSF32:
		Y0_f64 = Y0_f64 * 1.00000005L;
		S1_f64 = S1_f64 * 0.999996L;

		SINF32_X0[i].f32 = (float) (X0.f32 + 0.0009765625);
		SINF32_Y0[i].f32 = (float) Y0_f64;
		SINF32_S1[i].f32 = (float) S1_f64;
		SINF32_S2[i].f32 = (float) S2_f64;

		// Store Y0 as +ve Q30 value:
		temp = Y0_f64 * 1073741824.0L;
		if( temp >= 0.0)
			temp = temp + 0.5L;
		else
			temp = temp - 0.5L;
		SINF32_Y0i[i] = (long) temp;
			
		// Store S1 as +ve Q21 value:
		temp = S1_f64 * 2097152.0L;
		if( temp >= 0.0)
			temp = temp + 0.5L;
		else
			temp = temp - 0.5L;
		SINF32_S1i[i] = (long) temp;

		// Store S2 as +ve Q14 value:
		temp = S2_f64 * 16384.0L;
		if( temp >= 0.0)
			temp = temp + 0.5L;
		else
			temp = temp - 0.5L;
		SINF32_S2i[i] = (long) -temp;

		X0.ui32 = X2.ui32;
		}

	if(PRINT_TABLE == 1)
		{
		fprintf(OutPtr,"\n\nStart Of Coefficients Table:\n");
		for(i=0; i < TABLE_SIZE; i++)
			{
			fprintf(OutPtr,"\n%4d | x1 = %16.12f | Y0 = %16.12f   S1 = %16.12f   S2 = %16.12f | Y0i = %16d   S1i = %16d   S2i = %16d", i, SINF32_X0[i].f32, SINF32_Y0[i].f32, SINF32_S1[i].f32, SINF32_S2[i].f32, SINF32_Y0i[i], SINF32_S1i[i], SINF32_S2i[i]);
			}
		fprintf(OutPtr,"\n\nEnd of data.\n");
		}
}

//===========================================================================
// SINF32 and COSF32 Algorithms:
//===========================================================================

#if (RETURN_FLOAT == 1)
float	SINF32_Hardware_Emulation(float X)
#else
long	SINF32_Hardware_Emulation(float X)
#endif
{
	unsigned int	table_index;
	long			dx;
	long			index;
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
								// 1 =  0.0
								// 2 =  1.0

	//----------------------------------------------------------------------------------------------------------------------------
	// Pipeline Phase 1: Format input and extract table index and dx value:

	// Extract sign, exp and mantissa 0f input:
	tempX.f32 = X;
	Si = (tempX.ui32 & 0x80000000);
	Ei = (tempX.ui32 & 0x7F800000);
	Mi = (tempX.ui32 & 0x007FFFFF);

	// Set default values of data:
	So = 0x00000000L;												// Set default sign of result (+ve)
	dx = 0;
	Boundary = 0;
	table_index = 0;

	// Check limits:
	if( Ei <= 0x2F000000L )											// If X <= 2^[(0x2F0/8 =  94) - (0x3E8/8 = 127) = -33], input value very small:
		Boundary = 1;												// Return  0.0 value for SINF32,  1.0 value for COSF32
	else if( Ei >= 0x4A800000L )									// If X >= 2^[(0x4A8/8 = 149) - (0x3E8/8 = 127) =  22], input value too big:
		Boundary = 1;												// Return  0.0 value for SINF32,  1.0 value for COSF32
	else 
		{
		// Extract table_index and dx value:
		if( Ei <= 0x3A800000L )										// If X < {0.001953125 = 2^[(0x3B0/8 = 118) - 127 = -9]}
			{
			table_index = 0;
			dx = ((Mi | 0x00800000L) >> (117 - (Ei >> 23))) - 0x00800000L;
			}
		else
			{
			index = ((Mi | 0x00800000L) << 7) >> (148 - (Ei >> 23));
			temp = (Mi << ((Ei >> 23) - 117)) & 0x00FFFFFFL;

			if( (index & 0x00000100L) != 0 )						// If Quadrant 2 or 3:
				So = 0x80000000L;									// Set sign of result (-ve)	
	
			if( (index & 0x00000080L) == 0 )						// If:  Quadrant 0 (0.0  <= |X| < 0.25) or Quadrant 2 (0.5  <= |X| < 0.75):	
				{
				table_index = index & 0x0000007FL;
				dx = temp - 0x00800000L;
				if( ((index & 0x0000007FL) == 0) && (temp == 0) )	// If frac(X) == 0.0 or 0.5 exactly:
					Boundary = 1;									// Return exact 0.0
				}
			else													// Else: Quadrant 1 (0.25 <= |X| < 0.5 ) or Quadrant 3 (0.75 <= |X| < 1.0 ):
				{
				table_index = 127 - (index & 0x0000007FL);
				dx = 0x00800000L - temp;
				if( ((index & 0x0000007FL) == 0) && (temp == 0) )	// If frac(X) == 0.25 or 0.75 exactly:
					Boundary = 2;									// Return exact 1.0
				}
			}
		}

	// If SINF32 and input was negative (X < 0), invert result:
	if(Si != 0)
		So = So ^ 0x80000000L;

	//----------------------------------------------------------------------------------------------------------------------------
	// Pipeline Phase 2: Get ROM table values and calcualte dx*dx

	S2i	= (i64) SINF32_S2i[table_index];	// 20.Q14, +ve number with only bits 0 to 19 are valid (S2i[19:0])
	S1i = (i64) SINF32_S1i[table_index];	// 24.Q21, +ve number with only bits 0 to 23 are valid (S1i[23:0])
	Y0i = (i64) SINF32_Y0i[table_index];	// 30.Q30, +ve number with only bits 0 to 29 are valid (Y0i[29:0])

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

	// For SINF32 & COSF32 calculate:
	//     sum = Y0i + ((dx_S1 - dx_dx_S2) >> 1)
	//
	//     Note: if( dx >= 0 )
	//              sum = Y0i + (round(dx_S1 - dx_dx_S2) >> 1)
	//           else
	//              sum = Y0i - (round(dx_S1 + dx_dx_S2) >> 1)
	//
	// For INVF32 & ISQRTF32 calculate:
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
	#if (RETURN_FLOAT == 1)
		if( Boundary == 1 )
			Y.ui32 = 0x00000000L;			// Return 0.0
		else if( Boundary == 2 )
			Y.ui32 = So | 0x3F800000L;		// Return 1.0 with proper sign
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
	#else
		// Invert sum if output negative:
		if(So == 0x80000000L)
			sum = -sum;

		return (long) sum;
	#endif
}


#if (RETURN_FLOAT == 1)
float	COSF32_Hardware_Emulation(float X)
#else
long	COSF32_Hardware_Emulation(float X)
#endif
{
	unsigned int	table_index;
	long			dx;
	long			index;
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
								// 1 =  0.0
								// 2 =  1.0

	//----------------------------------------------------------------------------------------------------------------------------
	// Pipeline Phase 1: Format input and extract table index and dx value:

	// Extract sign, exp and mantissa 0f input:
	tempX.f32 = X;
	Si = (tempX.ui32 & 0x80000000);
	Ei = (tempX.ui32 & 0x7F800000);
	Mi = (tempX.ui32 & 0x007FFFFF);

	// Set default values of data:
	So = 0x00000000L;												// Set default sign of result (+ve)
	dx = 0;
	Boundary = 0;
	table_index = 0;

	// Check limits:
	if( Ei <= 0x2F000000L )											// If X <= 2^[(0x2F0/8 =  94) - (0x3E8/8 = 127) = -33], input value very small:
		Boundary = 2;												// Return  0.0 value for SINF32,  1.0 value for COSF32
	else if( Ei >= 0x4A800000L )									// If X >= 2^[(0x4A8/8 = 149) - (0x3E8/8 = 127) =  22], input value too big:
		Boundary = 2;												// Return  0.0 value for SINF32,  1.0 value for COSF32
	else 
		{
		// Extract table_index and dx value:
		if( Ei <= 0x3A800000L )										// If X < {0.001953125 = 2^[(0x3B0/8 = 118) - 127 = -9]}
			{
			table_index = 127;
			dx = 0x00800000L - ((Mi | 0x00800000L) >> (117 - (Ei >> 23)));
			}
		else
			{
			index = ((Mi | 0x00800000L) << 7) >> (148 - (Ei >> 23));
			temp = (Mi << ((Ei >> 23) - 117)) & 0x00FFFFFFL;

			if(    ((index & 0x00000180L) == 0x00000080L) 
				|| ((index & 0x00000180L) == 0x00000100L)  )		// If Quadrant 1 or 2:
				So = 0x80000000L;									// Set sign of result (-ve)	
	
			if( (index & 0x00000080L) != 0 )						// If: Quadrant 1 (0.25 <= |X| < 0.5 ) or Quadrant 3 (0.75 <= |X| < 1.0 ):
				{
				table_index = index & 0x0000007FL;
				dx = temp - 0x00800000L;
				if( ((index & 0x0000007FL) == 0) && (temp == 0) )	// If frac(X) == 0.25 or 0.75 exactly:
					Boundary = 1;									// Return exact 0.0
				}
			else													// Else:  Quadrant 0 (0.0  <= |X| < 0.25) or Quadrant 2 (0.5  <= |X| < 0.75):	
				{
				table_index = 127 - (index & 0x0000007FL);
				dx = 0x00800000L - temp;
				if( ((index & 0x0000007FL) == 0) && (temp == 0) )	// If frac(X) == 0.0 or 0.5 exactly:
					Boundary = 2;									// Return exact  1.0 if frac(X) == 0.0
				                                                    // Return exact -1.0 if frac(X) == 0.5
				}
			}
		}

	//----------------------------------------------------------------------------------------------------------------------------
	// Pipeline Phase 2: Get ROM table values and calcualte dx*dx

	S2i	= (i64) SINF32_S2i[table_index];	// 21.Q14, +ve number with only bits 0 to 20 are valid (S2i[20:0])
	S1i = (i64) SINF32_S1i[table_index];	// 25.Q21, +ve number with only bits 0 to 24 are valid (S1i[24:0])
	Y0i = (i64) SINF32_Y0i[table_index];	// 30.Q30, +ve number with only bits 0 to 29 are valid (Y0i[29:0])

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
		// if dx positive: perform 32-bit add
		sum = Y0i + dx_S1_SUB_dx_dx_S2;		
	else
		// if dx negative: perform 32-bit sub
		sum = Y0i - dx_S1_ADD_dx_dx_S2; 

	//----------------------------------------------------------------------------------------------------------------------------
	// Pipeline Phase 5: Format output
	#if (RETURN_FLOAT == 1)
		if( Boundary == 1 )
			Y.ui32 = 0x00000000L;			// Return 0.0
		else if( Boundary == 2 )
			Y.ui32 = So | 0x3F800000L;		// Return 1.0 with proper sign
		else
			{
			// If sum is zero, return zero:
			if(sum <= 0)
				return 0.0;

			// Normalize result and adjust exponent and mantissa:
			Eo = 0x3F800000L;				// Start with Exp = 2^0
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
	#else
		// Invert sum if output negative:
		if(So == 0x80000000L)
			sum = -sum;

		return (long) sum;
	#endif
}

//===========================================================================
// FastRTS SINF32: As supported in FPU and Fast RTS library.
//===========================================================================
//
// Using Eulers formula:
//
//   Sin(X) = Sin(X0) + Cos(X0)*dx - Sin(X0)*dx*dx/2! - Cos(X0)*dx*dx*dx/3! 
//
//   Where: X = X0 + dx
//  
//---------------------------------------------------------------------------

float	SINF32_FPUFastRTS_Emulation(float X)
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

	Y = SIN_X0 + dx * (COS_X0 +  dx * (C0 * SIN_X0 + dx * C1 * COS_X0));

	return	Y;
}

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

//===========================================================================
// No more.
//===========================================================================
