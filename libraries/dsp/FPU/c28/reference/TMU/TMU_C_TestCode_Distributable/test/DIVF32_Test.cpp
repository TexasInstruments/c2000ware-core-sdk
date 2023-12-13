//#############################################################################
// \file     DIVF32_Test.cpp
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
// DIVF32 Test Program:
//===========================================================================

void DIVF32_Test(void)
{
	int		i;
	float	temp;

	fprintf(OutPtr,"\nSummary Of Errors With Respect To Precise Reference Value:");
	fprintf(OutPtr,"\n\nTesting: INVF32, Table Size = %4d, Q Scaling = Q%2d", DIV_TABLE_SIZE, Q_RESULT);
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
		#if DIV_TABLE_SIZE == 128
		temp = temp + 0.0078125;
		#endif

		#if DIV_TABLE_SIZE == 256
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

		DIVF32_PrintResult();
		}
	while( temp < 2.0 );


	printf("\nCheck All Values Between Z = 1.0 / (X = 0.0625 to X = 0.12499999) (all mantissa bits):");
	fprintf(OutPtr,"\n\n\nCheck All Values Between Z = 1.0 / (X = 0.0625 to X = 0.12499999) (all mantissa bits):");

	Z.f32 = 1.0;
	X.f32 = 0.0625;
	temp = 0.0625;
	do	{
		#if DIV_TABLE_SIZE == 128
		temp = temp + 0.00048828125;
		#endif

		#if DIV_TABLE_SIZE == 256
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

		DIVF32_PrintResult();
		}
	while( temp < 0.125 );


	printf("\nCheck Some Random Values:");
	fprintf(OutPtr,"\n\n\nCheck Some Random Values:");

	Z.f32 = 1.0;

	X.f32 = 3.33333;
	DIVF32_CheckValues(Z, X);
	X.f32 = -3.33333;
	DIVF32_CheckValues(Z, X);

	X.f32 = 0.7654321;
	DIVF32_CheckValues(Z, X);
	X.f32 = -0.7654321;
	DIVF32_CheckValues(Z, X);

	X.f32 = 3.0;
	DIVF32_CheckValues(Z, X);
	X.f32 = -3.0;
	DIVF32_CheckValues(Z, X);

	X.f32 = 4.0;
	DIVF32_CheckValues(Z, X);
	X.f32 = -4.0;
	DIVF32_CheckValues(Z, X);

	X.f32 = 5.0;
	DIVF32_CheckValues(Z, X);
	X.f32 = -5.0;
	DIVF32_CheckValues(Z, X);

	X.f32 = 6.0;
	DIVF32_CheckValues(Z, X);
	X.f32 = -6.0;
	DIVF32_CheckValues(Z, X);

	X.f32 = 7.0;
	DIVF32_CheckValues(Z, X);
	X.f32 = -7.0;
	DIVF32_CheckValues(Z, X);

	X.f32 = 16.0;
	DIVF32_CheckValues(Z, X);
	X.f32 = -16.0;
	DIVF32_CheckValues(Z, X);

	X.f32 = 0.5;
	DIVF32_CheckValues(Z, X);
	X.f32 = -0.5;
	DIVF32_CheckValues(Z, X);

	X.f32 = 0.26;
	DIVF32_CheckValues(Z, X);
	X.f32 = -0.26;
	DIVF32_CheckValues(Z, X);

	X.f32 = 0.25;
	DIVF32_CheckValues(Z, X);
	X.f32 = -0.25;
	DIVF32_CheckValues(Z, X);

	X.f32 = 0.241;
	DIVF32_CheckValues(Z, X);
	X.f32 = -0.241;
	DIVF32_CheckValues(Z, X);

	X.f32 = 0.0625;
	DIVF32_CheckValues(Z, X);
	X.f32 = -0.0625;
	DIVF32_CheckValues(Z, X);

	Z.f32 = 1.5;
	X.f32 = 1.0;
	DIVF32_CheckValues(Z, X);

	Z.f32 = -1.5;
	X.f32 = 1.0;
	DIVF32_CheckValues(Z, X);

	Z.f32 = -1.5;
	X.f32 = -1.0;
	DIVF32_CheckValues(Z, X);

	Z.f32 = 1.5;
	X.f32 = -1.0;
	DIVF32_CheckValues(Z, X);

	Z.f32 = 1.5;
	X.f32 = 1.333;
	DIVF32_CheckValues(Z, X);

	Z.f32 = -1.5;
	X.f32 = 1.333;
	DIVF32_CheckValues(Z, X);

	Z.f32 = -1.5;
	X.f32 = -1.333;
	DIVF32_CheckValues(Z, X);

	Z.f32 = 1.5;
	X.f32 = -1.333;
	DIVF32_CheckValues(Z, X);

	Z.f32 = 1.01;
	X.f32 = 1.01;
	DIVF32_CheckValues(Z, X);

	Z.f32 = 1.01;
	X.f32 = 1.99;
	DIVF32_CheckValues(Z, X);

	Z.f32 = 1.99;
	X.f32 = 1.01;
	DIVF32_CheckValues(Z, X);

	Z.f32 = 1.99;
	X.f32 = 1.99;
	DIVF32_CheckValues(Z, X);

	printf("\nCheck Some Boundary Condition Values:");
	fprintf(OutPtr,"\n\n\nCheck Some Boundary Condition Values:");

	Z.ui32 = 0x3FFFFFFFL;	// Z = 1.99999999
	X.ui32 = 0x3F800001L;	// X = 1.0000001
	DIVF32_CheckValues(Z, X);
	Z.ui32 = 0x3F800001L;	// Z = 1.0000001
	X.ui32 = 0x3F800001L;	// X = 1.0000001
	DIVF32_CheckValues(Z, X);
	Z.ui32 = 0x3FFFFFFFL;	// Z = 1.99999999
	X.ui32 = 0x3FFFFFFFL;	// X = 1.99999999
	DIVF32_CheckValues(Z, X);
	Z.ui32 = 0x3F800001L;	// Z = 1.0000001
	X.ui32 = 0x3FFFFFFFL;	// X = 1.99999999
	DIVF32_CheckValues(Z, X);


}

// End of file
