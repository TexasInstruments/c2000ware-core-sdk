//#############################################################################
// \file     TMU_DIVF32.c
// \breif    Emulate the Trigononmetric and Math Unit (TMU) DIVF32 instruction 
// \author   original: Alex Tessarolo 
// \history	
//
//  ver  | dd-mmm-yyyy | Who     | Changes.
//  =====|=============|=========|============================================
//  2.0  | 24-Apr-2012 | Alex T. | Original Release.
//  -----|-------------|---------|--------------------------------------------
//  3.0  | 31-May-2012 | Alex T. | Added LVF/LUF flags, corrected boundary checks, corrected phase 5 calculations.
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
// DIVF32 TMU Algorithm Description:
//=============================================================================
//
// First calculate Y = 1/X:, then at end calculate Y = Z * (1/X)
//  Y = 1/X
//  Y = Y0 + dy
//  X = X0 + dx
//  
//  Y1 = 2*Y0 - Y0^2*X
//  Y  = 2*Y1 - Y1^2*X
//  
//  Y = 2*(2*Y0 - Y0^2*X) - (2*Y0 - Y0^2*X)^2*X
//  Y = 4*Y0 - 2*Y0^2*X - [(4*Y0^2 - 2*Y0^3*X - 2*Y0^3*X + Y0^4*X^2)*X]
//  Y = 4*Y0 - 2*Y0^2*X - [4*Y0^2*X - 4*Y0^3*X^2 + Y0^4*X^3]
//  Y = 4*Y0 - 2*Y0^2*X - 4*Y0^2*X + 4*Y0^3*X^2 - Y0^4*X^3
//  Y = 4*Y0 - 6*Y0^2*X + 4*Y0^3*X^2 - Y0^4*X^3							(1)
//  
//  Y = 4*Y0 - 6*Y0^2*(X0 + dx) + 4*Y0^3*(X0 + dx)^2 - Y0^4*(X0 + dx)^3
//  Y = 4*Y0 - 6*Y0^2*(X0 + dx) + 4*Y0^3*(X0^2 + 2*X0*dx + dx^2) - Y0^4*[(X0^2 + 2*X0*dx + dx^2)*(X0 + dx)]
//  Y = 4*Y0 - 6*Y0^2*X0 - 6*Y0^2*dx + 4*Y0^3*X0^2 + 8*Y0^3*X0*dx + 4*Y0^3*dx^2
//      - Y0^4*[X0^3 + X0^2*dx + 2*X0^2*dx + 2*X0*dx^2 + X0*dx^2 + dx^3]
//  Y = 4*Y0 - 6*Y0^2*X0 - 6*Y0^2*dx + 4*Y0^3*X0^2 + 8*Y0^3*X0*dx + 4*Y0^3*dx^2
//      - Y0^4*[X0^3 + 3*X0^2*dx + 3*X0*dx^2 + dx^3]
//  Y = 4*Y0 - 6*Y0^2*X0 - 6*Y0^2*dx + 4*Y0^3*X0^2 + 8*Y0^3*X0*dx + 4*Y0^3*dx^2
//      - Y0^4*X0^3 - 3*Y0^4*X0^2*dx - 3*Y0^4*X0*dx^2 - Y0^4*dx^3
//  Y = 4*Y0 - 6*Y0^2*X0 + 4*Y0^3*X0^2 - Y0^4*X0^3 - 6*Y0^2*dx + 8*Y0^3*X0*dx - 3*Y0^4*X0^2*dx 
//      + 4*Y0^3*dx^2 - 3*Y0^4*X0*dx^2 - Y0^4*dx^3
//  Y = (4*Y0 - 6*Y0^2*X0 + 4*Y0^3*X0^2 - Y0^4*X0^3) - (6*Y0^2 - 8*Y0^3*X0 + 3*Y0^4*X0^2)*dx 
//      + (4*Y0^3 - 3*Y0^4*X0)*dx^2 - Y0^4*dx^3
//  
//  C0 = 4*Y0 - 6*Y0^2*X0 + 4*Y0^3*X0^2 - Y0^4*X0^3 = Y0
//  C1 = -(6*Y0^2 - 8*Y0^3*X0 + 3*Y0^4*X0^2)
//  C2 = 4*Y0^3 - 3*Y0^4*X0
//  C3 = -(Y0^4)
//  
//  Y = Y0 + C1*dx + C2*dx^2 + C3*dx^3
//  
//  Range X0:  1.0 to 2.0
//  Range Y0:  1.0 to 0.5      
//  Range C1: -1.0 to -0.25    
//  Range C2:  1.0 to 0.125    
//  Range C3: -1.0 to 0.0625
//
//  To improve accuracy, we modify equation as follows:
//
//  X = x0 + dx0 +/- dx
//
//  Y = Y0 + S1*dx + S2*dx^2 + S3*dx^3
//
//  Where:   Y0 = 1/(x0 + dx0)
//           S1 = C1 + 2*dx0*C2 + 3*dx0*dx0*C3
//           S2 = C2 + 3*dx0*C3
//           S3 = C3
//
//  Term S3*dx^3 is too small to worry about and can be ignored. So equation
//  simplifies to:
//
//  Y = Y0 + S1*dx + S2*dx*dx		; Y0, S1, S2 values are stored in table
//
// The following conversion happens on the Input number by default before it gets to the TMU functions:
//    -ve zero inputs are treated as +ve zero
//    +/- DNorm inputs are treated as +ve zero
//    +/- NaN is treated as +/-Infinity
//    +/- Inf is NOT CONVERTED to MAX rather they are taken care in TMU functions
//
//    Division      Result  Overflow  Underflow
//    0/Normal        0        -        -
//    0/0             0        1        -
//    0/Inf           0        -        1
//    Inf/Normal      Inf      1        -
//    Inf/0           Inf      1        -
//    Inf/Inf         Inf      -        1
//    Normal/0        Inf      1        -
//    Normal/Inf      0        -        1
//    Normal/Normal   Note 1  Note 1   Note 1
//                
//    Note:    1) For normal calculations, the result is calculated as follows:  
//                      Eo = (Ez – Ei) + 127;
//                      Mo = Mz / Mi;                // 0.5 < Mo < 2.0
//                      if( Mo < 1.0 )               // Normalize mantissa:
//                          {
//                          Eo = Eo – 1;
//                          Mo = Mo * 2.0;
//                          }
//                      if( Eo >= 255)               // If value too big:
//                          {
//                          Eo  = 255;               // Return Inf
//                          Mo  = 0;
//                          LVF = 1;
//                          }
//                      if(Eo < 0)                   // If value too small:                                                                
//                          {
//                          So = 0;
//                          Eo = 0;                  // Return zero
//                          Mo = 0;
//                          LUF = 1;      
//                          }    
//
//               Note: Denorm value could be returned by above if Eo = 0 & Mo != 0
//
//===========================================================================
#include "TMU.h"

//*****************************************************************************
// globals
//*****************************************************************************
F32_UI32 DIVF32_X0[DIV_TABLE_SIZE];
F32_UI32 DIVF32_X2[DIV_TABLE_SIZE];
F32_UI32 DIVF32_Y0[DIV_TABLE_SIZE];
F32_UI32 DIVF32_S1[DIV_TABLE_SIZE];
F32_UI32 DIVF32_S2[DIV_TABLE_SIZE];
unsigned long DIVF32_Y0i[DIV_TABLE_SIZE];
unsigned long DIVF32_S1i[DIV_TABLE_SIZE];
unsigned long DIVF32_S2i[DIV_TABLE_SIZE];

int	LVF_flag;			// Latched overflow flag.
int	LUF_flag;			// Latched underflow flag.
//=============================================================================
// DIVF32 Algorithms:
//=============================================================================
float DIVF32_Hardware_Emulation(float Z, float X)
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

	unsigned long	Si;		// Bit  31    Sign     Of Input Value
	unsigned long	Ei;		// Bits 30:23 Exponent Of Input Value
	unsigned long	Mi;		// Bits 22:0  Mantissa Of Input Value
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
	Si = (tempX.ui32 & 0x80000000);
	Ei = (tempX.ui32 & 0x7F800000);
	Mi = (tempX.ui32 & 0x007FFFFF);

	// Extract sign, exp and mantissa of Numerator:
	tempZ.f32 = Z;
	Sz = (tempZ.ui32 & 0x80000000);
	Ez = (tempZ.ui32 & 0x7F800000);
	Mz = (tempZ.ui32 & 0x007FFFFF);

	// Set default values of data:
	dx = 0;
	Boundary = 0;
	table_index = 0;

	// Check for following boundary conditions:
	//
    //    Division      Result  Overflow  Underflow
    //    0/Normal        0        -        -
    //    0/0             0        1        -
    //    0/Inf           0        -        1
    //    Inf/Normal      Inf      1        -
    //    Inf/0           Inf      1        -
    //    Inf/Inf         Inf      -        1
    //    Normal/0        Inf      1        -
    //    Normal/Inf      0        -        1

	// Check if numerator is zero or Denorm. If so, generate zero and return:
	if( Ez == 0x00000000 )	
		{
		So = 0x00000000;
		Eo = 0x00000000;
		Mo = 0x00000000;
		if( Ei == 0x00000000 )		// If denominator is zero or Denorm, set overflow flag
			LVF_flag = 1;		
		if( Ei == 0x7F800000 )		// If denominator is Inf or NaN, set underflow flag
			LUF_flag = 1;
		Y.ui32 = So + Eo + Mo;
		Boundary = 1;
		}
	// Check if numerator is infinity or NaN. If so, generate Inf and return:
	else if( Ez == 0x7F800000 )
		{
		if( Ei == 0x00000000 )
			So = Sz;				// If denominator is zero, sign follows numerator
		else
			So = Si ^ Sz;			// Else sign follows num XOR den
		Eo = 0x7F800000;
		Mo = 0x00000000;
		if( Ei == 0x7F800000 )		// If denominator is Inf or NaN, set underflow flag
			LUF_flag = 1;
		else
			LVF_flag = 1;			// else, set overflow flag.
		Y.ui32 = So + Eo + Mo;
		Boundary = 1;
		}
	// If denominator is zero or Denorm and numerator is Normal, return Inf and set overflow flag:
	else if( Ei == 0x00000000 )
		{
		So = Sz;
		Eo = 0x7F800000;
		Mo = 0x00000000;
		LVF_flag = 1;		
		Y.ui32 = So + Eo + Mo;
		Boundary = 1;
		}
	// If denominator is Inf or NaN and numerator is Normal, return Inf and set underflow flag:
	else if( Ei == 0x7F800000 )
		{
		So = 0x00000000;
		Eo = 0x00000000;
		Mo = 0x00000000;
		LUF_flag = 1;	
		Y.ui32 = So + Eo + Mo;
		Boundary = 1;
		}
	// At this point, inputs are Normal. Check if denominator is modulo of 2. If so, adjust exponent and return with value:
	else if( Mi == 0x00000000 )
		{
		So = Si ^ Sz;	
		Eo = (0x3F800000L + Ez) - Ei;
		Mo = Mz;
		if( Eo >= 0x7F800000 )			// Check if value too big. Return Inf and set overflow flag.
			{
			So = 0x00000000;
			Eo = 0x7F800000;
			Mo = 0x00000000;
			LVF_flag = 1;	
			}
		if( Eo >= 0x80000000 )			// Check if value too small. Return zero and set underflow flag.
			{
			So = 0x00000000;
			Eo = 0x00000000;
			Mo = 0x00000000;
			LUF_flag = 1;	
			}
		Y.ui32 = So + Eo + Mo;
		Boundary = 1;
		}
		
	// Note: The following section can be done in parallel with above boundary checks. It will be ignored on the last stage.
	//
	// Extract table index and dx value:
	#if DIV_TABLE_SIZE == 128
	table_index = ((Mi & 0x007F0000L) >> 16);
	if( (Mi & 0x00008000L) == 0 )
		dx = (0xFFFF8000L ^ (Mi & 0x0000FFFFL)) << 9;			// Q33
	else
		dx = (0x00008000L ^ (Mi & 0x0000FFFFL)) << 9;			// Q33
	#endif
	#if DIV_TABLE_SIZE == 256
	table_index = ((Mi & 0x007F8000L) >> 15);
	if( (Mi & 0x00004000L) == 0 )
		dx = (0xFFFFC000L ^ (Mi & 0x00007FFFL)) << 10;			// Q33
	else
		dx = (0x00004000L ^ (Mi & 0x00007FFFL)) << 10;			// Q33
	#endif

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
		// Generate sign bit and adjust exponent:
		//    Note:    1) For normal calculations, the result is calculated as follows:  
		//                      Eo = (Ez – Ei) + 127;
		//                      Mo = Mz / Mi;                // 0.5 < Mo < 2.0
		//                      if( Mo < 1.0 )               // Normalize mantissa:
		//                          {
		//                          Eo = Eo – 1;
		//                          Mo = Mo * 2.0;
		//                          }
		//                      if( Eo >= 255)               // If value too big:
		//                          {
		//                          Eo  = 255;               // Return Inf
		//                          Mo  = 0;
		//                          LVF = 1;
		//                          }
		//                      if(Eo < 0)                   // If value too small:                                                                
		//                          {
		//                          So = 0;
		//                          Eo = 0;                  // Return zero
		//                          Mo = 0;
		//                          LUF = 1;      
		//                          }    
		//
		//               Note: Denorm value could be returned by above if Eo = 0 & Mo != 0
		//

		sum  =  (((sum & 0x00000000FFFFFF80LL) * (Mz | 0x00800000L)) & 0x00FFFFFF80000000LL) >> 31;
		So = Si ^ Sz;	
		Eo = (0x3F800000L + Ez) - Ei;
		if( (sum & 0x01000000L) != 0 )
			sum = sum >> 1;
		else
			Eo = Eo - 0x00800000L;

		Mo = (unsigned long) (sum & 0x007FFFFFL);
	
		if( Eo >= 0x7F800000 )			// Check if value too big. Return Inf and set overflow flag.
			{
			So = 0x00000000;
			Eo = 0x7F800000;
			Mo = 0x00000000;
			LVF_flag = 1;	
			}
		if( Eo >= 0x80000000 )			// Check if value too small. Return zero and set underflow flag.
			{
			So = 0x00000000;
			Eo = 0x00000000;
			Mo = 0x00000000;
			LUF_flag = 1;	
			}
		Y.ui32 = So + Eo + Mo;
		return 	Y.f32;
		}
}

//=============================================================================
// DIVF32 Error Checking:
//=============================================================================

void DIVF32_CheckError(F32_UI32 Z, F32_UI32 X)
{
    // <<VC161025: had to change long double to double for the entire file>>
	double X_f64;
	double Z_f64;
	double	Y1_f64;
	double Y1_temp_f64;
	double Y1_error_f64;

	// Increment total test count:
	TestCount = TestCount + 1.0;

	// Generate Precise Reefernce Value Y1:
	X_f64 = (double) X.f32;
	Z_f64 = (double) Z.f32;
	Y1_f64 = Z_f64 / X_f64;

	Y1_temp_f64 = Y1_f64;

	// Calculate Hardware Emulation Value Y3:
	Y3.f32 = DIVF32_Hardware_Emulation(Z.f32, X.f32);

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
	Y4.f32  = DIVF32_FPUFastRTS_Emulation(Z.f32, X.f32);

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


void DIVF32_CheckValues(F32_UI32 Z, F32_UI32 X)
{
    // <<VC161025: had to change long double to double for the entire file>>
	double X_f64;
	double Z_f64;
	double	Y1_f64;
	double Y1_temp_f64;
	double Y1_error_f64;

	// Generate Precise Reefernce Value Y1:
	X_f64 = (double) X.f32;
	Z_f64 = (double) Z.f32;
	Y1_f64 = Z_f64 / X_f64;

	Y1_temp_f64 = Y1_f64;

	// Calculate Hardware Emulation Value Y3:
	LVF_flag = 0;
	LUF_flag = 0;
	Y3.f32 = DIVF32_Hardware_Emulation(Z.f32, X.f32);

	Y1_error_f64 = 0.0;
	if(Y1_temp_f64 > ((double) Y3.f32))
		{
		Y1_error_f64 = Y1_temp_f64 - ((double) Y3.f32);
		}
	if(Y1_temp_f64 < ((double) Y3.f32))
		{
		Y1_error_f64 = ((double) Y3.f32) - Y1_temp_f64;
		}

	fprintf(OutPtr,"\n\nHardware Emulation Y = %24.12f / %24.12f = %24.12f (LVF = %1d) (LUF = %1d) (Absolute Error = %20.12f) ", Z.f32, X.f32, Y3.f32, LVF_flag, LUF_flag, (Y1_error_f64 * Q_SCALE));

	// Calculate FastRTS Emulation Value Y4:
	LVF_flag = 0;
	LUF_flag = 0;
	Y4.f32  = DIVF32_FPUFastRTS_Emulation(Z.f32, X.f32);

	Y1_error_f64 = 0.0;
	if(Y1_temp_f64 > ((double) Y4.f32))
		{
		Y1_error_f64 = Y1_temp_f64 - ((double) Y4.f32);
		}
	if(Y1_temp_f64 < ((double) Y4.f32))
		{
		Y1_error_f64 = ((double) Y4.f32) - Y1_temp_f64;
		}
	fprintf(OutPtr,"\nFastRTS  Emulation Y = %24.12f / %24.12f = %24.12f (LVF = %1d) (LUF = %1d) (Absolute Error = %20.12f)", Z.f32, X.f32, Y4.f32, LVF_flag, LUF_flag, (Y1_error_f64 * Q_SCALE));
}


// End of file
