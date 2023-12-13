//#############################################################################
// \file     TMU_SQRTF32.c
// \breif    Emulate the Trigononmetric and Math Unit (TMU) SQRTF32 instruction 
// \author   original: Alex Tessarolo 
// \history	
//
//  ver  | dd-mmm-yyyy | Who     | Changes.
//  =====|=============|=========|============================================
//  3.0  | 30-Apr-2011 | Alex T. | Original Release.
//  -----|-------------|---------|--------------------------------------------
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
#include "TMU.h"

//*****************************************************************************
// globals
//*****************************************************************************
F32_UI32		SQRTF32_X0[SQRT_TABLE_SIZE];
F32_UI32		SQRTF32_Y0[SQRT_TABLE_SIZE];
F32_UI32		SQRTF32_S1[SQRT_TABLE_SIZE];
F32_UI32		SQRTF32_S2[SQRT_TABLE_SIZE];
unsigned long	SQRTF32_Y0i[SQRT_TABLE_SIZE];
unsigned long	SQRTF32_S1i[SQRT_TABLE_SIZE];
unsigned long	SQRTF32_S2i[SQRT_TABLE_SIZE];
//=============================================================================
// SQRTF32 Algorithms:
//=============================================================================
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

		// Extract table index and dx value for SQRT_TABLE_SIZE == 128:
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
	dx_dx_S2  = (((dx_dx & 0x000000000003FFFFLL) * (S2i & 0x00000000000FFFFFLL)) & 0x0000003FFFFC0000LL) >> 18; 

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
	dx_S1     =  (((((i64) temp) & 0x0000000001FFFFFFLL) * (S1i & 0x0000000000FFFFFFLL)) & 0x0001FFFFFF800000LL) >> 23;

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
			sum  =  (((sum & 0x00000000FFFFFF80LL) * (SQRT2_24Q23)) & 0x00FFFFFF80000000LL) >> 31;
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

//=============================================================================
// SQRTF32 Error Checking:
//=============================================================================

void SQRTF32_CheckError(F32_UI32 X)
{
    // <<VC161025: had to change long double to double for the entire file>>
	double X_f64;
	double	Y1_f64;
	double Y1_temp_f64;
	double Y1_error_f64;

	// Increment total test count:
	TestCount = TestCount + 1.0;

	// Generate Precise Reefernce Value Y1:
	X_f64 = (double) X.f32;
	Y1_f64 = sqrt(X_f64);

	Y1_temp_f64 = Y1_f64;

		// Calculate Hardware Emulation Value Y3:
	Y3.f32 = SQRTF32_Hardware_Emulation(X.f32);

	if(Y1_temp_f64 > ((double) Y3.f32))
		{
		Y1_error_f64 = Y1_temp_f64 - ((double) Y3.f32);
		if(Y1_error_f64 > ErrorMaxY3posF64)
			ErrorMaxY3posF64 = Y1_error_f64;
		ErrorCountY3posF64 = ErrorCountY3posF64 + 1.0;
		ErrorAvgY3posF64 = ErrorAvgY3posF64 + Y1_error_f64;
		if((Y1_error_f64 * Q_SCALE) >= 0.5)
			ErrorCountY3posF64_half = ErrorCountY3posF64_half + 1.0;
		}
	if(Y1_temp_f64 < ((double) Y3.f32))
		{
		Y1_error_f64 = ((double) Y3.f32) - Y1_temp_f64;
		if(Y1_error_f64 > ErrorMaxY3negF64)
			ErrorMaxY3negF64 = Y1_error_f64;
		ErrorCountY3negF64 = ErrorCountY3negF64 + 1.0;
		ErrorAvgY3negF64 = ErrorAvgY3negF64 + Y1_error_f64;
		if((Y1_error_f64 * Q_SCALE) >= 0.5)
			ErrorCountY3negF64_half = ErrorCountY3negF64_half + 1.0;
		}

	// Calculate FastRTS Emulation Value Y4:
	Y4.f32  = SQRTF32_FPUFastRTS_Emulation(X.f32);

	if(Y1_temp_f64 > ((double) Y4.f32))
		{
		Y1_error_f64 = Y1_temp_f64 - ((double) Y4.f32);
		if(Y1_error_f64 > ErrorMaxY4posF64)
			ErrorMaxY4posF64 = Y1_error_f64;
		ErrorCountY4posF64 = ErrorCountY4posF64 + 1.0;
		ErrorAvgY4posF64 = ErrorAvgY4posF64 + Y1_error_f64;
		}
	if(Y1_temp_f64 < ((double) Y4.f32))
		{
		Y1_error_f64 = ((double) Y4.f32) - Y1_temp_f64;
		if(Y1_error_f64 > ErrorMaxY4negF64)
			ErrorMaxY4negF64 = Y1_error_f64;
		ErrorCountY4negF64 = ErrorCountY4negF64 + 1.0;
		ErrorAvgY4negF64 = ErrorAvgY4negF64 + Y1_error_f64;
		}
}



// End of file
