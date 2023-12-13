//#############################################################################
// \file     TMU_SINF32.c
// \breif    Emulate the Trigononmetric and Math Unit (TMU) SINF32 instruction 
// \author   original: Alex Tessarolo 
// \history	
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
#include "TMU.h"

//*****************************************************************************
// globals
//*****************************************************************************
F32_UI32 SINF32_X0[SINCOS_TABLE_SIZE];
F32_UI32 SINF32_X2[SINCOS_TABLE_SIZE];
F32_UI32 SINF32_Y0[SINCOS_TABLE_SIZE];
F32_UI32 SINF32_S1[SINCOS_TABLE_SIZE];
F32_UI32 SINF32_S2[SINCOS_TABLE_SIZE];
long SINF32_Y0i[SINCOS_TABLE_SIZE];
long SINF32_S1i[SINCOS_TABLE_SIZE];
long SINF32_S2i[SINCOS_TABLE_SIZE];
long dx_max;
long dx_min;
i64 dx_dx_max;
i64 dx_dx_min;
//=============================================================================
// SINF32 Algorithms:
//=============================================================================

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

//=============================================================================
// SINF32 Error Checking:
//=============================================================================

void SINF32_CheckError(F32_UI32 X)
{
    // <<VC161025: had to change long double to double for the entire file>>
	double X_f64;
	double Y1_f64;
	double Y1_temp_f64;
	double Y1_error_f64;

	// Increment total test count:
	TestCount = TestCount + 1.0;

	// Generate Precise Reefernce Value Y1:
	X_f64 = (double) X.f32;
	Y1_f64 = sin(X_f64 * 2.0 * PI);

	Y1_temp_f64 = Y1_f64;

	// Calculate Hardware Emulation Value Y3:
	#if (RETURN_FLOAT == 1)
		Y3.f32 = SINF32_Hardware_Emulation(X.f32);

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
	#else
		Y3.i32 = SINF32_Hardware_Emulation(X.f32);	// Value returned as Q30

		Y3.i32 = Y3.i32 >> (30 - Q_RESULT);	
	#endif

	// Calculate FastRTS Emulation Value Y4:
	Y4.f32  = SINF32_FPUFastRTS_Emulation(X.f32);

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
