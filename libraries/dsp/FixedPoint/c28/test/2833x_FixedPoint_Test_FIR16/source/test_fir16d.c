//#############################################################################
//! \file $FOLDER_TEST$/$DEVICE$_FixedPoint_FIR16/test_fir16d.c
//!
//! \brief  16-bit FIR Filter Example
//!
//! \date   Aug 12, 2014
//! 
//! This examples shows how to implement a 16-bit FIR filter using the optimized
//! FIR library routines. This version of the FIR filter has a limitation of 256 
//! taps (filter order max 255). If a higher order filter is required, refer to the
//! FIR16_Alt example.
//! 
//! typedef struct { 
//!     int32_t *coeff_ptr;        
//!     int32_t * dbuffer_ptr;
//!     int    cbindex;
//!     int order; 
//!     int input;   
//!     int output; 
//!     void (*init)(void *);
//!     void (*calc)(void *);
//!     }FIR16; 
//! 
//! Users can also use default templates defined within fir.h to initialize 
//! the FIR16 header structure.
//!                 
//! FIR16  fir= FIR16_DEFAULTS;
//! 
//! The MATLAB Filter Design and Analysis Tool (FDATool) is a useful tool 
//! for designing filters and generating fixed point coefficients. Refer
//! to the appendix of the Fixed Point DSP Libray User's Guide for more
//! information.
//! 
//! \b Watch \b Variables
//! - fir   FIR16 object
//! 
//! In CCS, you can invoke the "SetupDebugEnv.js" script from the 
//! Scripting console to have these variables set up in the Watch window
//! and create graphs to show the input/output vectors
//
//  Group:            C2000
//  Target Family:    C28x
//
//#############################################################################
//
//
//$Copyright: Copyright (C) 2014-2024 Texas Instruments Incorporated -
//            http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################
#define XXSTRINGIZE(s)	XSTRINGIZE(s)  // calls xstringize(s), if s is a macro it
                                       // will expand s first
#define XSTRINGIZE(s)	STRINGIZE(s)  // calls stringize(s), if s is a macro it
                                      // will expand s first
#define STRINGIZE(s)	#s			  // TREAT s as a literal, if s is a macro
                                      // it wont be expanded
#define XCONCAT(x,y,z) CONCAT(x,y,z)  // expand x and y then call concat on the
                                      // expanded macros x and y
#define CONCAT(x,y,z)	x ## y ## z   // concats x and y but doesnt expand
                                      // x and y if they are macros
//*****************************************************************************
// includes
//*****************************************************************************
#include "test_fir16d.h"
#include "filter.h"
//*****************************************************************************
// defines
//*****************************************************************************

//*****************************************************************************
// globals
//*****************************************************************************                                        
// Create an Instance of FIR16 module and place the object in "firfilt" section 
#ifndef __cplusplus
#pragma DATA_SECTION(fir, "firfilt");
#else
#pragma DATA_SECTION("firfilt");
#endif
FIR16 fir= FIR16_DEFAULTS;

#if ((RUN_TEST == TEST_1) || (RUN_TEST == TEST_2)  || (RUN_TEST == TEST_8))
int16_t temp[SIGNAL_LENGTH];
int32_t *dbuffer;

#elif ((RUN_TEST == TEST_3) || (RUN_TEST == TEST_4) || (RUN_TEST == TEST_5) || \
	   (RUN_TEST == TEST_6) || (RUN_TEST == TEST_7))
// Define the Delay buffer for the "FIR_ORDER"th order filter
// and place it in "firldb" section. Since we define it as int32_t,
// The size of the buffer is:
// FIR_ORDER even -> (FIR_ORDER+1)/2+1 e.g. FIR_ORDER = 32, size = 17 dwords
//           odd  -> (FIR_ORDER+1)/2   e.g. FIR_ORDER = 31, size = 16 dwords
// The delay line buffer must be aligned to a 256 word boundary
#ifndef __cplusplus
#pragma DATA_SECTION(dbuffer,"firldb");
#else
#pragma DATA_SECTION("firfilt");
#endif
#if(FIR_ORDER & 0x01)   // odd
int32_t dbuffer[(FIR_ORDER+1)/2];
#else
int32_t dbuffer[(FIR_ORDER+3)/2];
#endif
// Input/output buffer 
#ifndef __cplusplus
#pragma DATA_SECTION(sigIn, "sigIn");
#else
#pragma DATA_SECTION("sigIn");
#endif
int16_t sigIn[SIGNAL_LENGTH]= {
	#include XSTRINGIZE(XCONCAT(test,RUN_TEST,_data_input.txt))
};

#ifndef __cplusplus
#pragma DATA_SECTION(sigOut, "sigOut");
#else
#pragma DATA_SECTION("sigOut");
#endif
int16_t sigOut[SIGNAL_LENGTH];

const int16_t goldOut[SIGNAL_LENGTH] = {
	#include XSTRINGIZE(XCONCAT(test,RUN_TEST,_data_output.txt))
};

// Define Constant Coefficient Array  and place it in the "coefffilt"
// section. You can either reorder the coefficients at run time (done 
// in this example) or just store them reordered.
// Index       LSW       MSW
//         +---------+---------+
//  0      | h(L-1)  | h(L/2-1)|
//  2      | h(L-2)  | h(L/2-2)|
//  4      | h(L-3)  | h(L/2-3)|
//  6      | h(L-4)  | h(L/2-4)|
//  ...    | ...     | ...     |
//  L/2-3  | h(L/2+2)| h(2)    |
//  L/2-2  | h(L/2+1)| h(1)    |
//  L/2-1  | h(L/2)  | h(0)    |
//         +---------+---------+
// The size of the array is:
// FIR_ORDER even -> (FIR_ORDER+1)+1 e.g. FIR_ORDER = 32, size = 34 words
//           odd  -> (FIR_ORDER+1)   e.g. FIR_ORDER = 31, size = 32 words
// The reason being that we use the DMAC operation which will multiply
// the coefficients in 32-bit chunks, we don't want an odd size coefficient
// buffer and risk corrupting the delay line
#ifndef __cplusplus
#pragma DATA_SECTION(coeff, "coefffilt");
#else
#pragma DATA_SECTION("coefffilt");
#endif
#if(FIR_ORDER & 0x01)   // odd
int16_t coeff[FIR_ORDER+1] = {
	#include XSTRINGIZE(XCONCAT(test,RUN_TEST,_coeffs.txt))
};
#else
int16_t coeff[FIR_ORDER+2] = {
	#include XSTRINGIZE(XCONCAT(test,RUN_TEST,_coeffs.txt))
};
#endif

#ifndef __cplusplus
#pragma DATA_SECTION(revCoeff, "coefffilt");
#else
#pragma DATA_SECTION("coefffilt");
#endif
int16_t revCoeff[FIR_ORDER+2];                                   

int16_t err[SIGNAL_LENGTH];
#endif // ((RUN_TEST == TEST_2)||(RUN_TEST == TEST_3))

extern uint16_t pass, fail;
//*****************************************************************************
// function definitions
//*****************************************************************************
uint16_t FIXPT_DSP_runTest()
{
    // Locals
    int16_t i = 0;

#if(RUN_TEST == TEST_1)
    // Write dummy codes to temp
    memset(temp, 0xBAAD, sizeof(temp));

    dbuffer         = (int32_t *)&temp[FIR_ORDER]; // Set dbuffer to an odd address
    fir.order       = FIR_ORDER;        // odd
    fir.dbuffer_ptr = &dbuffer[0];
    fir.init(&fir);

#elif(RUN_TEST == TEST_2)
    // Write dummy codes to temp
    memset(temp, 0xBAAD, sizeof(temp));

    dbuffer         = (int32_t *)&temp[FIR_ORDER]; // Set dbuffer to an even address
    fir.order       = FIR_ORDER;        // even
    fir.dbuffer_ptr = &dbuffer[0];
    fir.init(&fir);

#elif(RUN_TEST == TEST_8)
    // Write dummy codes to temp
    memset(temp, 0xBAAD, sizeof(temp));

    dbuffer         = (int32_t *)&temp[FIR_ORDER]; // Set dbuffer to an even address
    fir.order       = FIR_ORDER;        // even
    fir.dbuffer_ptr = &dbuffer[0];
    fir.coeff_ptr   = 0;
    fir.init(&fir);
    fir.calc(&fir);

#elif ((RUN_TEST == TEST_3) || (RUN_TEST == TEST_4) || (RUN_TEST == TEST_5) || \
	   (RUN_TEST == TEST_6) || (RUN_TEST == TEST_7))
    // zero out sigOut
    memset(sigOut, 0, sizeof(sigOut));

	// Load the coefficients in normal order. If
	// FIR_ORDER even -> number of taps are odd, zero out the last element of coeffs
	//           odd  -> number of taps are even, do nothing
#if ((FIR_ORDER & 0x01) == 0)
    	coeff[FIR_ORDER + 1] = 0;

	// if the order of the coefficients is even, you will have
	// an odd number of taps; zero out the location right after the
	// last tap
		revCoeff[FIR_ORDER_REV-1] = 0;
#endif
	// Reorder the coefficients
	// FIR_ORDER even -> (FIR_ORDER+1)+1 e.g. FIR_ORDER = 32, size = 34 words
	//           odd  -> (FIR_ORDER+1)   e.g. FIR_ORDER = 31, size = 32 words
#if (FIR_ORDER & 0x01) //odd order
	for(i = 0; i < FIR_ORDER + 1; i = i + 2){
#else // even order
	for(i = 0; i < FIR_ORDER + 2; i = i + 2){
#endif
		revCoeff[FIR_ORDER_REV-i-1] = coeff[i/2+FIR_ORDER_REV/2];
		revCoeff[FIR_ORDER_REV-i-2] = coeff[i/2];
	}

	// Initialize FIR16 object
	fir.order       = FIR_ORDER;
	fir.dbuffer_ptr = &dbuffer[0];
	fir.coeff_ptr   = (int32_t *)&revCoeff[0];
	fir.init(&fir);

	// FIR calculation
	for(i = 0; i < SIGNAL_LENGTH; i++){
		fir.input  = sigIn[i]; // Q15 format
		fir.calc(&fir);
		sigOut[i]  = fir.output;
	}
#endif

	return(1);

}
uint16_t FIXPT_DSP_genReport()
{
	//Locals
	int16_t i;
	uint16_t goldPass = 0; // Each test must define an expected pass value

#if ((RUN_TEST == TEST_1)||(RUN_TEST == TEST_2))
#if(FIR_ORDER & 0x01)   // odd
	if(fir.cbindex == FIR_ORDER - 1){
		pass++;
	}else{
		fail++;
	}
	goldPass = FIR_ORDER + 1;
#else //FIR_ORDER is even
	if(fir.cbindex == FIR_ORDER){
		pass++;
	}else{
		fail++;
	}
	goldPass = FIR_ORDER + 2;
#endif
	// Check above dbuffer
	for(i = 0; i < FIR_ORDER; i++) {
		if(temp[i] == 0xBAAD){
			pass++;
		}else{
			fail++;
		}
	}
	// check dbuffer
	for(i = FIR_ORDER; i < (FIR_ORDER + goldPass); i++) {
		if(temp[i] == 0){
			pass++;
		}else{
			fail++;
		}
	}
	// Check below dbuffer
	for(i = FIR_ORDER+goldPass; i < SIGNAL_LENGTH; i++) {
		if(temp[i] == 0xBAAD){
			pass++;
		}else{
			fail++;
		}
	}

#elif ((RUN_TEST == TEST_3) || (RUN_TEST == TEST_4) || (RUN_TEST == TEST_5) || \
	   (RUN_TEST == TEST_6) || (RUN_TEST == TEST_7))
	goldPass =  SIGNAL_LENGTH;
	// Check that bit reversal was done correctly
	for(i = 0; i < goldPass; i++ ){
		err[i] = abs(goldOut[i] - sigOut[i]);
		if(err[i] < TOLERANCE){
			pass++;
		}else{
			fail++;
		}
	}

#endif

	return(1);
}
//###########################################################################
// End of File
//###########################################################################
