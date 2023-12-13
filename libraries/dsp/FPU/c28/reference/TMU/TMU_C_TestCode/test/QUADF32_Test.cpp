//#############################################################################
// \file     QUADF32_Test.cpp
// \breif    Test the TMU instructions
// \author   original: Alex Tessarolo 
// \history	
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
// QUADF32 Test Program:
//===========================================================================

void QUADF32_Test(void)
{
	int		i;
	float	temp;

	fprintf(OutPtr,"\nSummary Of Errors With Respect To Precise Reference Value:");
	fprintf(OutPtr,"\n\nTesting: QUADF32, Table Size = %4d, Q Scaling = Q%2d", DIV_TABLE_SIZE, Q_RESULT);
	fprintf(OutPtr,"\n===========================================================================\n");


	printf("\nTest QUADF32 Using Q%2d Scaling, Return (float)", Q_RESULT);

	printf("\nCheck Values Around Full Circle:");
	fprintf(OutPtr,"\n\n\nCheck Values Around Full Circle:");

	// 0 Deg, radius = 0.0
	Z.f32 = 0.0;
	X.f32 = 0.0;
	QUADF32_CheckError(Z, X);
	QUADF32_PrintResult();

	// 0 Deg, radius = 0.0
	Z.f32 = 0.0;
	X.ui32 = 0x80000000L;		// X = -0.0
	QUADF32_CheckError(Z, X);
	QUADF32_PrintResult();

	// 0 Deg, radius = 0.0
	Z.ui32 = 0x80000000L;		// Z = -0.0
	X.f32 = 0.0;
	QUADF32_CheckError(Z, X);
	QUADF32_PrintResult();

	// 0 Deg, radius = 0.0
	Z.ui32 = 0x80000000L;		// Z = -0.0
	X.ui32 = 0x80000000L;		// X = -0.0
	QUADF32_CheckError(Z, X);
	QUADF32_PrintResult();

	// 0 Deg, radius = 0.7776
	Z.f32 = 0.0;
	X.f32 = 0.7776;
	QUADF32_CheckError(Z, X);
	QUADF32_PrintResult();

	// 0 Deg, radius = 0.7776
	Z.ui32 = 0x80000000;		// Z = -0.0
	X.f32 = 0.7776;
	QUADF32_CheckError(Z, X);
	QUADF32_PrintResult();

	// 15 Deg, radius = 0.7776
	Z.f32 = 0.2012576894718;
	X.f32 = 0.7511039225224;
	QUADF32_CheckError(Z, X);
	QUADF32_PrintResult();

	// 30 Deg, radius = 0.7776
	Z.f32 = 0.388;
	X.f32 = 0.6734213539827;
	QUADF32_CheckError(Z, X);
	QUADF32_PrintResult();

	// 45 Deg, radius = 0.7776
	Z.f32 = 0.5498462330507;
	X.f32 = 0.5498462330507;
	QUADF32_CheckError(Z, X);
	QUADF32_PrintResult();

	// 60 Deg, radius = 0.7776
	Z.f32 = 0.6734213539827;
	X.f32 = 0.388;
	QUADF32_CheckError(Z, X);
	QUADF32_PrintResult();

	// 75 Deg, radius = 0.7776
	Z.f32 = 0.7511039225224;
	X.f32 = 0.2012576894718;
	QUADF32_CheckError(Z, X);
	QUADF32_PrintResult();

	// 90 Deg, radius = 0.7776
	Z.f32 = 0.7776;
	X.f32 = 0.0;
	QUADF32_CheckError(Z, X);
	QUADF32_PrintResult();

	// 90 Deg, radius = 0.7776
	Z.f32 = 0.7776;
	X.ui32 = 0x80000000L;		// X = -0.0
	QUADF32_CheckError(Z, X);
	QUADF32_PrintResult();

	// 105 Deg, radius = 0.7776
	Z.f32 = 0.7511039225224;
	X.f32 = -0.2012576894718;
	QUADF32_CheckError(Z, X);
	QUADF32_PrintResult();

	// 120 deg, radius = 0.7776
	Z.f32 = 0.6734213539827;
	X.f32 = -0.388;
	QUADF32_CheckError(Z, X);
	QUADF32_PrintResult();

	// 135 Deg, radius = 0.7776
	Z.f32 = 0.5498462330507;
	X.f32 = -0.5498462330507;
	QUADF32_CheckError(Z, X);
	QUADF32_PrintResult();

	// 150 Deg, radius = 0.7776
	Z.f32 = 0.388;
	X.f32 = -0.6734213539827;
	QUADF32_CheckError(Z, X);
	QUADF32_PrintResult();

	// 165 Deg, radius = 0.7776
	Z.f32 = 0.2012576894718;
	X.f32 = -0.7511039225224;
	QUADF32_CheckError(Z, X);
	QUADF32_PrintResult();

	// 180 Deg, radius = 0.7776
	Z.f32 = 0.0;
	X.f32 = -0.7776;
	QUADF32_CheckError(Z, X);
	QUADF32_PrintResult();

	// 180 Deg, radius = 0.7776
	Z.ui32 = 0x80000000L;		// Z = -0.0
	X.f32 = -0.7776;
	QUADF32_CheckError(Z, X);
	QUADF32_PrintResult();

	// 195 Deg, radius = 0.7776
	Z.f32 = -0.2012576894718;
	X.f32 = -0.7511039225224;
	QUADF32_CheckError(Z, X);
	QUADF32_PrintResult();

	// 210 Deg, radius = 0.7776
	Z.f32 = -0.388;
	X.f32 = -0.6734213539827;
	QUADF32_CheckError(Z, X);
	QUADF32_PrintResult();

	// 225 Deg, radius = 0.7776
	Z.f32 = -0.5498462330507;
	X.f32 = -0.5498462330507;
	QUADF32_CheckError(Z, X);
	QUADF32_PrintResult();

	// 240 deg, radius = 0.7776
	Z.f32 = -0.6734213539827;
	X.f32 = -0.388;
	QUADF32_CheckError(Z, X);
	QUADF32_PrintResult();

	// 255 Deg, radius = 0.7776
	Z.f32 = -0.7511039225224;
	X.f32 = -0.2012576894718;
	QUADF32_CheckError(Z, X);
	QUADF32_PrintResult();

	// 270 Deg, radius = 0.7776
	Z.f32 = -0.7776;
	X.f32 =  0.0;
	QUADF32_CheckError(Z, X);
	QUADF32_PrintResult();

	// 270 Deg, radius = 0.7776
	Z.f32 = -0.7776;
	X.ui32 = 0x80000000L;		// X = -0.0
	QUADF32_CheckError(Z, X);
	QUADF32_PrintResult();

	// 285 Deg, radius = 0.7776
	Z.f32 = -0.7511039225224;
	X.f32 = 0.2012576894718;
	QUADF32_CheckError(Z, X);
	QUADF32_PrintResult();

	// 300 Deg, radius = 0.7776
	Z.f32 = -0.6734213539827;
	X.f32 = 0.388;
	QUADF32_CheckError(Z, X);
	QUADF32_PrintResult();

	// 315 Deg, radius = 0.7776
	Z.f32 = -0.5498462330507;
	X.f32 = 0.5498462330507;
	QUADF32_CheckError(Z, X);
	QUADF32_PrintResult();

	// 330 Deg, radius = 0.7776
	Z.f32 = -0.388;
	X.f32 = 0.6734213539827;
	QUADF32_CheckError(Z, X);
	QUADF32_PrintResult();

	// 345 Deg, radius = 0.7776
	Z.f32 = -0.2012576894718;
	X.f32 = 0.7511039225224;
	QUADF32_CheckError(Z, X);
	QUADF32_PrintResult();
}

//End of file
