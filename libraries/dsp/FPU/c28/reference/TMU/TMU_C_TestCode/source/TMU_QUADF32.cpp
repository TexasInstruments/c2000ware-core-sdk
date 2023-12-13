//#############################################################################
// \file     TMU_QUADF32.c
// \breif    Emulate the Trigononmetric and Math Unit (TMU) QUADF32 instruction 
// \author   original: Alex Tessarolo 
// \history	
//
//  ver  | dd-mmm-yyyy | Who     | Changes.
//  =====|=============|=========|============================================
//  1.0  | 02-May-2012 | Alex T. | Original Release.
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
#include "TMU.h"

//===========================================================================
// QUADF32 Algorithms:
//===========================================================================

float QUADF32_Hardware_Emulation(float Z, float X, float *Q)
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

	unsigned long	Sx;		// Bit  31    Sign     Of Input Value
	unsigned long	Ex;		// Bits 30:23 Exponent Of Input Value
	unsigned long	Mx;		// Bits 22:0  Mantissa Of Input Value
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
	Sx = (tempX.ui32 & 0x80000000);
	Ex = (tempX.ui32 & 0x7F800000);
	Mx = (tempX.ui32 & 0x007FFFFF);

	// Extract sign, exp and mantissa of Numerator:
	tempZ.f32 = Z;
	Sz = (tempZ.ui32 & 0x80000000);
	Ez = (tempZ.ui32 & 0x7F800000);
	Mz = (tempZ.ui32 & 0x007FFFFF);

	//	if( (fabs(X_f64) == 0.0) & (fabs(Z_f64) == 0) )
	//		{
	//		Y1QuadrantF64 = 0.0;
	//		Y1RatioF64 = 0.0;
	//		}
	//	else if( fabs(Z_f64) <= fabs(X_f64) )
	//		{
	//		Y1RatioF64 = Z_f64 / X_f64;
	//		if( X_f64 >= 0.0 )
	//			Y1QuadrantF64 = 0.0;
	//		else
	//			{
	//			if( Z_f64 >= 0.0 )
	//				Y1QuadrantF64 = 0.5;
	//			else
	//				Y1QuadrantF64 = -0.5;
	//			}
	//		}
	//	else
	//		{
	//		if( Z_f64 >= 0.0 )
	//			Y1QuadrantF64 = 0.25;
	//		else
	//			Y1QuadrantF64 = -0.25;
	//		Y1RatioF64 = X_f64 / Z_f64;
	//		}
	//

	// If input values are zero, negative zero or Denorm, force to zero:
	if( Ex == 0x00000000 )
		{
		Sx = 0x00000000;
		Mx = 0x00000000;
		}
	if( Ez == 0x00000000 )
		{
		Sz = 0x00000000;
		Mz = 0x00000000;
		}

	if( (Ez | Mz) <= (Ex | Mx) )
		{
		// Default Ratio = Z/X
		if( Sx == 0 )
			*Q = 0.0;
		else
			{
			if( Sz == 0 )
				*Q = 0.5;
			else
				*Q = -0.5;
			}
		}
	else
		{
		if( Sz == 0 )
			*Q = 0.25;
		else
			*Q = -0.25;
		// Swap Z and X, Ratio = X/Z
		So = Sz;
		Sz = Sx;
		Sx = So;
		Eo = Ez;
		Ez = Ex;
		Ex = Eo;
		Mo = Mz;
		Mz = Mx;
		Mx = Mo;

		// Invert sign of Z:
		Sz = Sz ^ 0x80000000;
		}

	// Set default values of data:
	dx = 0;
	Boundary = 0;
	table_index = 0;

	// If Z and X are zero, return zero:
	if( (Ex == 0x00000000) & (Ez == 0x00000000) )	
		{
		So = 0x00000000;
		Eo = 0x00000000;
		Mo = 0x00000000;
		Y.ui32 = So + Eo + Mo;
		*Q = 0.0;
		Boundary = 1;
		}
	// Check if Nan or infinity input. If so, generate zero and return:
	else if( Ex == 0x7F800000 )
		{
		So = 0x00000000;
		Eo = 0x00000000;
		Mo = 0x00000000;
		Y.ui32 = So + Eo + Mo;
		Boundary = 1;
		}
	// If input too big, return zero:
	else if( Ex == 0x7F000000 )
		{
		So = 0x00000000;
		Eo = 0x00000000;
		Mo = 0x00000000;
		Y.ui32 = So + Eo + Mo;
		Boundary = 1;
		}
	// Check if input is modulo of 2. If so, adjust exponent and return with value:
	else if( Mx == 0x00000000 )
		{
		So = Sx ^ Sz;	
		Eo = (0x3F800000L + Ez) - Ex;
		Mo = Mz;
		Y.ui32 = So + Eo + Mo;
		Boundary = 1;
		}
	else
		{
		// Generate sign bit and adjust exponent:
		So = Sx ^ Sz;	
		if( Mz == 0 )
			Eo = (0x3F000000L + Ez) - Ex;
		else
			Eo = (0x3F800000L + Ez) - Ex;

		// Extract table index and dx value:
		#if DIV_TABLE_SIZE == 128
		table_index = ((Mx & 0x007F0000L) >> 16);
		if( (Mx & 0x00008000L) == 0 )
			dx = (0xFFFF8000L ^ (Mx & 0x0000FFFFL)) << 9;			// Q33
		else
			dx = (0x00008000L ^ (Mx & 0x0000FFFFL)) << 9;			// Q33
		#endif
		#if DIV_TABLE_SIZE == 256
		table_index = ((Mx & 0x007F8000L) >> 15);
		if( (Mx & 0x00004000L) == 0 )
			dx = (0xFFFFC000L ^ (Mx & 0x00007FFFL)) << 10;			// Q33
		else
			dx = (0x00004000L ^ (Mx & 0x00007FFFL)) << 10;			// Q33
		#endif
		}

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
		if( Mz != 0 )
			{
			// Perform 25-bit by 24-bit multiply with 24-bit result (sum[23:0] = sum[31:7] * Mz[23:0]):
			sum  =  (((sum & 0x00000000FFFFFF80LL) * (Mz | 0x00800000L)) & 0x00FFFFFF00000000LL) >> 32;
			}
		else
			{
			// Scale back to 24-bit mantissa:
			sum = sum >> 8;				
			}

		// Should never get here, but just to make sure:
		// Mantissa should be in the range: of 1.0 to 0.5
		// 16777215 = 0x00FFFFFF = 0.9999999 in Q24 format
		// ...
		//  8388608 = 0x00800000 = 0.5000000 in Q24 format
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
// QUADF32 Error Checking:
//=============================================================================

void QUADF32_CheckError(F32_UI32 Z, F32_UI32 X)
{
    // <<VC161025: had to change long double to double for the entire file>>
	double X_f64;
	double Z_f64;

	// Generate Precise Reefernce Value Y1:
	X_f64 = (double) X.f32;
	Z_f64 = (double) Z.f32;

	if( (fabs(X_f64) == 0.0) & (fabs(Z_f64) == 0) )
		{
		Y1QuadrantF64 = 0.0;
		Y1RatioF64 = 0.0;
		}
	else if( fabs(Z_f64) <= fabs(X_f64) )
		{
		Y1RatioF64 = Z_f64 / X_f64;
		if( X_f64 >= 0.0 )
			Y1QuadrantF64 = 0.0;
		else
			{
			if( Z_f64 >= 0.0 )
				Y1QuadrantF64 = 0.5;
			else
				Y1QuadrantF64 = -0.5;
			}
		}
	else
		{
		if( Z_f64 >= 0.0 )
			Y1QuadrantF64 = 0.25;
		else
			Y1QuadrantF64 = -0.25;
		Y1RatioF64 = - (X_f64 / Z_f64);
		}

	// Calculate Hardware Emulation Value Y3:
	Y3.f32 = QUADF32_Hardware_Emulation(Z.f32, X.f32, &Q3.f32);

	Y3ErrorPosF64 = 0.0;
	if(Y1RatioF64 > ((double) Y3.f32))
		{
		Y3ErrorPosF64 = Y1RatioF64 - ((double) Y3.f32);
		}
	if(Y1RatioF64 < ((double) Y3.f32))
		{
		Y3ErrorNegF64 = ((double) Y3.f32) - Y1RatioF64;
		}
}



// End of file
