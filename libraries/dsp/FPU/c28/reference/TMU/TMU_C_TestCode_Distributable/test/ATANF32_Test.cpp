//#############################################################################
// \file     ATANF32_Test.cpp
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
// ATANF32 Test Program:
//===========================================================================

void ATANF32_Test(void)
{

	fprintf(OutPtr,"\nSummary Of Errors With Respect To Precise Reference Value:");
	fprintf(OutPtr,"\n\nTesting: ATANF32, Table Size = %4d, Q Scaling = Q%2d", ATAN_TABLE_SIZE, Q_RESULT);
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
	ATANF32_PrintResult();

	printf("\n Test 0.00048828125 <= X <  0.0009765625");
	fprintf(OutPtr,"\n\n Test 0.00048828125 <= X <  0.0009765625");
	X.f32 = 0.00048828125;
	while(X.f32 < 0.0009765625)
		{
		ATANF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	ATANF32_PrintResult();

	printf("\n Test 0.0009765625  <= X <  0.001953125");
	fprintf(OutPtr,"\n\n Test 0.0009765625  <= X <  0.001953125");
	X.f32 = 0.0009765625;
	while(X.f32 < 0.001953125)
		{
		ATANF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	ATANF32_PrintResult();

	printf("\n Test 0.001953125   <= X <  0.00390625");
	fprintf(OutPtr,"\n\n Test 0.001953125   <= X <  0.00390625");
	X.f32 = 0.001953125;
	while(X.f32 < 0.00390625)
		{
		ATANF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	ATANF32_PrintResult();

	printf("\n Test 0.00390625    <= X <  0.0078125");
	fprintf(OutPtr,"\n\n Test 0.00390625    <= X <  0.0078125");
	X.f32 = 0.00390625;
	while(X.f32 < 0.0078125)
		{
		ATANF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	ATANF32_PrintResult();

	printf("\n Test 0.0078125     <= X <  0.015625");
	fprintf(OutPtr,"\n\n Test 0.0078125     <= X <  0.015625");
	X.f32 = 0.0078125;
	while(X.f32 < 0.015625)
		{
		ATANF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	ATANF32_PrintResult();

	printf("\n Test 0.015625      <= X <  0.03125");
	fprintf(OutPtr,"\n\n Test 0.015625      <= X <  0.03125");
	X.f32 = 0.015625;
	while(X.f32 < 0.03125)
		{
		ATANF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	ATANF32_PrintResult();

	printf("\n Test 0.03125       <= X <  0.0625");
	fprintf(OutPtr,"\n\n Test 0.03125       <= X <  0.0625");
	X.f32 = 0.03125;
	while(X.f32 < 0.0625)
		{
		ATANF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	ATANF32_PrintResult();

	printf("\n Test 0.0625        <= X <  0.125");
	fprintf(OutPtr,"\n\n Test 0.0625        <= X <  0.125");
	X.f32 = 0.0625;
	while(X.f32 < 0.125)
		{
		ATANF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	ATANF32_PrintResult();

	printf("\n Test 0.125         <= X <  0.25");
	fprintf(OutPtr,"\n\n Test 0.125         <= X <  0.25");
	X.f32 = 0.125;
	while(X.f32 < 0.25)
		{
		ATANF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	ATANF32_PrintResult();

	printf("\n Test 0.25          <= X <  0.5");
	fprintf(OutPtr,"\n\n Test 0.25          <= X <  0.5");
	X.f32 = 0.25;
	while(X.f32 < 0.5)
		{
		ATANF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	ATANF32_PrintResult();

	printf("\n Test 0.5           <= X <  1.0");
	fprintf(OutPtr,"\n\n Test 0.5           <= X <  1.0");
	X.f32 = 0.5;
    while(X.f32 < 1.0)
		{
		ATANF32_CheckError(X);
		// Increment Input Value:
		X.ui32 = X.ui32 + 1;
		};
	ATANF32_PrintResult();

	printf("\n Test 1.0");
	fprintf(OutPtr,"\n\n Test 1.0");
	X.f32 = 1.0;
 	ATANF32_CheckError(X);

	ATANF32_PrintResult();
}

//End of file
