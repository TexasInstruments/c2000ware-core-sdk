//#############################################################################
// \file     SQRTF32_Test.cpp
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
// SQRTF32 Test Program:
//===========================================================================

void SQRTF32_Test(void)
{
	int		i;
	float	temp;

	fprintf(OutPtr,"\nSummary Of Errors With Respect To Precise Reference Value:");
	fprintf(OutPtr,"\n\nTesting: SQRTF32, Table Size = %4d, Q Scaling = Q%2d",
                   SQRT_TABLE_SIZE, Q_RESULT);
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
		SQRTF32_PrintResult();
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

	SQRTF32_PrintResult();
*/
}

// End of file
