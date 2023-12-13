//#############################################################################
// \file     TMU_ATANF32.c
// \breif    Emulate the Trigononmetric and Math Unit (TMU) ATANF32 instruction 
// \author   original: Alex Tessarolo 
// \history	
//
//  ver  | dd-mmm-yyyy | Who     | Changes.
//  =====|=============|=========|============================================
//  1.0  | 30-Apr-2012 | Alex T. | Original Release.
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
#include "TMU.h"

//*****************************************************************************
// globals
//*****************************************************************************
F32_UI32 ATANF32_X0[ATAN_TABLE_SIZE];
F32_UI32 ATANF32_X2[ATAN_TABLE_SIZE];
F32_UI32 ATANF32_Y0[ATAN_TABLE_SIZE];
F32_UI32 ATANF32_S1[ATAN_TABLE_SIZE];
F32_UI32 ATANF32_S2[ATAN_TABLE_SIZE];
unsigned long ATANF32_Y0i[ATAN_TABLE_SIZE];
unsigned long ATANF32_S1i[ATAN_TABLE_SIZE];
unsigned long ATANF32_S2i[ATAN_TABLE_SIZE];

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

//=============================================================================
// ATANF32 Error Checking:
//=============================================================================

void ATANF32_CheckError(F32_UI32 X)
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
	Y1_f64 = atan(X_f64) * INV2PI;
	Y1_f64 = Y1_f64;

	Y1_temp_f64 = Y1_f64;

	// Calculate Hardware Emulation Value Y3:
	Y3.f32 = ATANF32_Hardware_Emulation(X.f32);

	if(Y1_temp_f64 > ((double) Y3.f32))
		{
		Y1_error_f64 = Y1_temp_f64 - ((double) Y3.f32);
		if(Y1_error_f64 > ErrorMaxY3posF64)
			ErrorMaxY3posF64 = Y1_error_f64;
		ErrorCountY3posF64 = ErrorCountY3posF64 + 1.0;
		ErrorAvgY3posF64 = ErrorAvgY3posF64 + Y1_error_f64;
		}
	if(Y1_temp_f64 < ((double) Y3.f32))
		{
		Y1_error_f64 = ((double) Y3.f32) - Y1_temp_f64;
		if(Y1_error_f64 > ErrorMaxY3negF64)
			ErrorMaxY3negF64 = Y1_error_f64;
		ErrorCountY3negF64 = ErrorCountY3negF64 + 1.0;
		ErrorAvgY3negF64 = ErrorAvgY3negF64 + Y1_error_f64;
		}

	// Calculate FastRTS Emulation Value Y4:
	Y4.f32  = ATANF32_FPUFastRTS_Emulation(X.f32);

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
