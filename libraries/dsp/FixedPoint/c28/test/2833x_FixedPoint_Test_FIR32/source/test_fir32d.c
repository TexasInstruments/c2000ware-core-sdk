//#############################################################################
//! \file $FOLDER_TEST$/$DEVICE$_FixedPoint_FIR32/test_fir32d.c
//!
//! \brief  32-bit FIR Filter Example
//! \author Vishal Coelho 
//!
//! \date   Aug 12, 2014
//! 
//! This examples shows how to implement a 32-bit FIR filter using the optimized
//! FIR library routines. This version of the FIR filter has a limitation of 128 
//! taps (filter order max 127). If a higher order filter is required, refer to the
//! FIR32_Alt example.
//! The structure of 32 bit filter is shown as follows:
//! 
//! typedef struct { 
//!   long *coeff_ptr;        
//!   long * dbuffer_ptr;        
//!   int    cbindex;            
//!   int order;              
//!   long input;               
//!   long output;             
//!   void (*init)(void *);   
//!   void (*calc)(void *);    
//! }FIR32; 
//! 
//! Users can also use default templates defined within fir.h to initialize 
//! the FIR32 header structure.
//!                 
//! FIR32  fir= FIR32_DEFAULTS;
//! 
//! The MATLAB Filter Design and Analysis Tool (FDATool) is a useful tool 
//! for designing filters and generating fixed point coefficients. Refer
//! to the appendix of the Fixed Point DSP Libray User's Guide for more
//! information.
//! 
//! \b Watch \b Variables
//! - fir   FIR32 object
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
//$Copyright: Copyright (C) 2014-2025 Texas Instruments Incorporated -
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
#include "test_fir32d.h"
#include "filter.h"

//*****************************************************************************
// defines
//*****************************************************************************


//*****************************************************************************
// globals
//*****************************************************************************                                        
// Create an Instance of FIR32 module and place the object in "firfilt" section 
#ifndef __cplusplus
#pragma DATA_SECTION(fir, "firfilt");
#else
#pragma DATA_SECTION("firfilt");
#endif
FIR32 fir= FIR32_DEFAULTS;

#if ((RUN_TEST == TEST_1) || (RUN_TEST == TEST_2) || (RUN_TEST == TEST_8))
int16_t temp[SIGNAL_LENGTH*2];
int32_t *dbuffer;
#elif ((RUN_TEST == TEST_3) || (RUN_TEST == TEST_4) || (RUN_TEST == TEST_5) || \
	   (RUN_TEST == TEST_6) || (RUN_TEST == TEST_7))
// Define the Delay buffer for the "FIR_ORDER"th order filter
// and place it in "firldb" section. 
// Its size should be FIR_ORDER+1
// The delay line buffer must be aligned to a 256 word boundary
#ifndef __cplusplus
#pragma DATA_SECTION(dbuffer,"firldb");
#else
#pragma DATA_SECTION("firfilt");
#endif
int32_t dbuffer[FIR_ORDER+1];

// Input/output buffer 
#ifndef __cplusplus
#pragma DATA_SECTION(sigIn, "sigIn");
#else
#pragma DATA_SECTION("sigIn");
#endif
int32_t sigIn[SIGNAL_LENGTH]= {
#include XSTRINGIZE(XCONCAT(test,RUN_TEST,_data_input.txt))
};

#ifndef __cplusplus
#pragma DATA_SECTION(sigOut, "sigOut");
#else
#pragma DATA_SECTION("sigOut");
#endif
int32_t sigOut[SIGNAL_LENGTH];                                

// Define Constant Coefficient Array  and place it in the "coefffilt"
// section. The size of the array is FIR_ORDER+1
#ifndef __cplusplus
#pragma DATA_SECTION(coeff, "coefffilt");
#else
#pragma DATA_SECTION("coefffilt");
#endif
int32_t coeff[FIR_ORDER+1] = {
	#include XSTRINGIZE(XCONCAT(test,RUN_TEST,_coeffs.txt))
};

const int32_t goldOut[SIGNAL_LENGTH] = {
	#include XSTRINGIZE(XCONCAT(test,RUN_TEST,_data_output.txt))
};

// Error between computed output and MATLAB output
int32_t err[SIGNAL_LENGTH];
#endif

extern uint16_t pass, fail;
//*****************************************************************************
// function definitions
//*****************************************************************************
uint16_t FIXPT_DSP_runTest()
{
	//Locals
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
    fir.init(&fir);
    fir.calc(&fir);
#elif ((RUN_TEST == TEST_3) || (RUN_TEST == TEST_4) || (RUN_TEST == TEST_5) || \
	   (RUN_TEST == TEST_6) || (RUN_TEST == TEST_7))

	// zero out sigOut
	memset(sigOut, 0, sizeof(sigOut));
	// Initialize FIR32 object
	fir.order       = FIR_ORDER;
	fir.dbuffer_ptr = dbuffer;
	fir.coeff_ptr   =(int32_t *)coeff;
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
	goldPass = 2*(FIR_ORDER + 1);
	if(fir.cbindex == 2*FIR_ORDER + 2){
		pass++;
	}else{
		fail++;
	}
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
	for(i = FIR_ORDER+goldPass; i < 2*SIGNAL_LENGTH; i++) {
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
