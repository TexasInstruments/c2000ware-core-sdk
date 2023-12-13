//#############################################################################
// \file     SINF32_Test.cpp
// \breif    Test the TMU instructions
// \author   original: Alex Tessarolo 
// \history	
//
// \note 
// -# This is built using g++ and make files
// -# Target is an x86 system
//
// Copyright (C) 2019 Texas Instruments Incorporated - http://www.ti.com/ 
// ALL RIGHTS RESERVED
//#############################################################################
//
//
//#############################################################################
#include "TMU.h"
//===========================================================================
// SINF32 Test Program:
//===========================================================================

void SINF32_Test(void)
{
	fprintf(OutPtr,"\nSummary Of Errors With Respect To Precise Reference Value:");
	fprintf(OutPtr,"\n\nTesting: SINF32, Table Size = %4d, Q Scaling = Q%2d", SINCOS_TABLE_SIZE, Q_RESULT);
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
	SINCOSF32_PrintResult();

	printf("\n Test 0.00048828125 <= X <  0.0009765625");
	fprintf(OutPtr,"\n\n Test 0.00048828125 <= X <  0.0009765625");
	X.f32 = 0.00048828125;
	while(X.f32 < 0.0009765625)
		{
		SINF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	SINCOSF32_PrintResult();

	printf("\n Test 0.0009765625  <= X <  0.001953125");
	fprintf(OutPtr,"\n\n Test 0.0009765625  <= X <  0.001953125");
	X.f32 = 0.0009765625;
	while(X.f32 < 0.001953125)
		{
		SINF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	SINCOSF32_PrintResult();

	printf("\n Test 0.001953125   <= X <  0.00390625");
	fprintf(OutPtr,"\n\n Test 0.001953125   <= X <  0.00390625");
	X.f32 = 0.001953125;
	while(X.f32 < 0.00390625)
		{
		SINF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	SINCOSF32_PrintResult();

	printf("\n Test 0.00390625    <= X <  0.0078125");
	fprintf(OutPtr,"\n\n Test 0.00390625    <= X <  0.0078125");
	X.f32 = 0.00390625;
	while(X.f32 < 0.0078125)
		{
		SINF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	SINCOSF32_PrintResult();

	printf("\n Test 0.0078125     <= X <  0.015625");
	fprintf(OutPtr,"\n\n Test 0.0078125     <= X <  0.015625");
	X.f32 = 0.0078125;
	while(X.f32 < 0.015625)
		{
		SINF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	SINCOSF32_PrintResult();

	printf("\n Test 0.015625      <= X <  0.03125");
	fprintf(OutPtr,"\n\n Test 0.015625      <= X <  0.03125");
	X.f32 = 0.015625;
	while(X.f32 < 0.03125)
		{
		SINF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	SINCOSF32_PrintResult();

	printf("\n Test 0.03125       <= X <  0.0625");
	fprintf(OutPtr,"\n\n Test 0.03125       <= X <  0.0625");
	X.f32 = 0.03125;
	while(X.f32 < 0.0625)
		{
		SINF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	SINCOSF32_PrintResult();

	printf("\n Test 0.0625        <= X <  0.125");
	fprintf(OutPtr,"\n\n Test 0.0625        <= X <  0.125");
	X.f32 = 0.0625;
	while(X.f32 < 0.125)
		{
		SINF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	SINCOSF32_PrintResult();

	printf("\n Test 0.125         <= X <  0.25");
	fprintf(OutPtr,"\n\n Test 0.125         <= X <  0.25");
	X.f32 = 0.125;
	while(X.f32 < 0.25)
		{
		SINF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	SINCOSF32_PrintResult();

	printf("\n Test 0.25          <= X <  0.5");
	fprintf(OutPtr,"\n\n Test 0.25          <= X <  0.5");
	X.f32 = 0.25;
	while(X.f32 < 0.5)
		{
		SINF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	SINCOSF32_PrintResult();

	printf("\n Test 0.5           <= X <  0.75");
	fprintf(OutPtr,"\n\n Test 0.5           <= X <  0.75");
	X.f32 = 0.5;
    while(X.f32 < 0.75)
		{
		SINF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	SINCOSF32_PrintResult();

	printf("\n Test 0.75          <= X <  1.0");
	fprintf(OutPtr,"\n\n Test 0.75          <= X <  1.0");
	X.f32 = 0.75;
    while(X.f32 < 1.0)
		{
		SINF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	SINCOSF32_PrintResult();

	printf("\n Test 1.0           <= X <  2.0");
	fprintf(OutPtr,"\n\n Test 1.0           <= X <  2.0");
	X.f32 = 1.0;
    while(X.f32 < 2.0)
		{
		SINF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	SINCOSF32_PrintResult();

	printf("\n Test 2.0           <= X <  4.0");
	fprintf(OutPtr,"\n\n Test 2.0           <= X <  4.0");
	X.f32 = 2.0;
    while(X.f32 < 4.0)
		{
		SINF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	SINCOSF32_PrintResult();

	printf("\n Test 4.0           <= X <  8.0");
	fprintf(OutPtr,"\n\n Test 4.0           <= X <  8.0");
	X.f32 = 4.0;
    while(X.f32 < 8.0)
		{
		SINF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	SINCOSF32_PrintResult();

	printf("\n Test Values: -3.0 <= X <= 3.0 in 0.125 increments");
	fprintf(OutPtr,"\n\n Test Values: -3.0 <= X <= 3.0 in 0.125 increments");
	X.f32 = -3.0;
	do	{
		SINF32_CheckError(X);
		X.f32 = X.f32 + 0.125;
	} while( X.f32 <= 3.0 );
	SINCOSF32_PrintResult();
}


// End of file
