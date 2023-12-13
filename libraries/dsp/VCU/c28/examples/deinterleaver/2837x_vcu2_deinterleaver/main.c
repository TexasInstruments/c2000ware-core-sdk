//#############################################################################
//! \file /2837x_vcu2_deinterleaver/main.c
//!
//! \brief  Demo code for the Deinterleaver routine(VCU)
//!
//! \date   Jan 06, 2015
//! 
//! This example shows how to use the vcu2 supported De-interleaver routine 
//! from the library
//!
//
//  Group:             C2000
//  Target Family:     F2837x
// 
//#############################################################################
//
//
// $Copyright: Copyright (C) 2023 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################

//*****************************************************************************
// includes
//*****************************************************************************
#include <string.h>
#include "vcu2_types.h"
#include "vcu2_deinterleaver.h"
#include "interleaver.h"
#include "examples_setup.h"

//!
//! \addtogroup DEINTERLEAVER_EXAMPLES DE-interleaver Example

// @{

//*****************************************************************************
// defines
//*****************************************************************************
#define  MAX_NUM_BITS        4096
#define  MAX_NUM_WORDS       (MAX_NUM_BITS/16)
#define  MIN_N               4
#define  MAX_N               250 //511
#define  MIN_M               36  //6
#define  MAX_M               72
//*****************************************************************************
// globals
//*****************************************************************************
#ifdef __cplusplus
#pragma DATA_SECTION("testInput")
#else
#pragma DATA_SECTION(testInput,"testInput")
#endif
uint16_t testInput[MAX_NUM_WORDS] = {
    #include "data_input.h"
};

#ifdef __cplusplus
#pragma DATA_SECTION("testOutput")
#else
#pragma DATA_SECTION(testOutput,"testOutput")
#endif
uint16_t testOutput[MAX_NUM_WORDS];

#ifdef __cplusplus
#pragma DATA_SECTION("interleavedOutput")
#else
#pragma DATA_SECTION(interleavedOutput,"interleavedOutput")
#endif
uint16_t interleavedOutput[MAX_NUM_BITS];

#ifdef __cplusplus
#pragma DATA_SECTION("deinterleavedOutput")
#else
#pragma DATA_SECTION(deinterleavedOutput,"deinterleavedOutput")
#endif
uint16_t deinterleavedOutput[MAX_NUM_BITS];

INTERLEAVER_Obj INTERLEAVER;
INTERLEAVER_Handle hndINTERLEAVER = &INTERLEAVER;

DEINTERLEAVER_Obj DEINTERLEAVER;
DEINTERLEAVER_Handle hndDEINTERLEAVER = &DEINTERLEAVER;

uint16_t pass = 0;
uint16_t fail = 0;
//*****************************************************************************
// Function Prototypes
//*****************************************************************************

//*****************************************************************************
// function definitions
//*****************************************************************************

//!
//! \brief main routine for the deinterleaver example
//! \return returns a 1
//!
//! This example shows how to use the vcu2 supported Deinterleaver routines from the
//! library. The input is placed in a section testInput, interleaved into interleavedOutput,
//! run through the VCU2 de-interleaver, packed and placed into testOutput finally
//!
int main( void )
{
    // Locals
    int16_t i, kk, nWords, remBits;
	uint16_t n, m;
	uint16_t symb;
	uint16_t tmp, idx;
	uint16_t *testInput_p, *testOutput_p, *tmp_p;

#ifdef FLASH
	EALLOW;
	Flash0EccRegs.ECC_ENABLE.bit.ENABLE = 0;
	memcpy((uint32_t *)&RamfuncsRunStart, (uint32_t *)&RamfuncsLoadStart,
			(uint32_t)&RamfuncsLoadSize );
	VCU2_initFlash();
#endif //FLASH
	
	VCU2_initSystemClocks();
	
	VCU2_initEpie();

    //*************************************************************************
    // Running the Interleaver
    //*************************************************************************
    //! \b Running \b the \b Interleaver
    //! \code
    //*************************************************************************
    // Sweep the tones(only interested in m = 36, 72)
	for (m = MIN_M; m <= MAX_M; m+=(MAX_M-MIN_M)){
		// sweep for the number of OFDM symbols
		for (n = MIN_N; n <= MAX_N; n+=20){
			// check to see if it is out of bound
			if (n * m > MAX_NUM_BITS){
				break;
			}
           // Find the interleaver parameters for each n, m
           INTERLEAVER_findParams(hndINTERLEAVER, n, m);
           // Clear out the buffers
           memset(interleavedOutput, 0, sizeof(interleavedOutput));
           memset(deinterleavedOutput, 0, sizeof(deinterleavedOutput));
           
           // Run the interleaver
           for (symb = 0; symb < n; symb++){
               INTERLEAVER_run(hndINTERLEAVER, &testInput[0], &interleavedOutput[symb * m],
                        symb);
            }
           //*************************************************************************
           // Running the De-interleaver
           //*************************************************************************
           //Initialize the VCU deinterleaver object
           DEINTERLEAVER.pOutBuffer = &deinterleavedOutput[0];
           DEINTERLEAVER.m          = m;
           DEINTERLEAVER.n          = n;
           DEINTERLEAVER.b          = INTERLEAVER.b;
           DEINTERLEAVER.v          = INTERLEAVER.v;
           DEINTERLEAVER.a          = INTERLEAVER.a;
           DEINTERLEAVER.u          = INTERLEAVER.u;
           DEINTERLEAVER.n_i        = INTERLEAVER.n_i;
           DEINTERLEAVER.n_j        = INTERLEAVER.n_j;
           DEINTERLEAVER.m_i        = INTERLEAVER.m_i;
           DEINTERLEAVER.m_j        = INTERLEAVER.m_j;
           DEINTERLEAVER.pSymbol    = &symb;
           DEINTERLEAVER.init       = 0;
		   DEINTERLEAVER.run        = (void(*)(void *))DEINTERLEAVER_run;
           
           for (symb = 0; symb < n; symb++){
              //Run the VCU2 Deinterleaver
              DEINTERLEAVER.pInBuffer = &interleavedOutput[symb * m];
              DEINTERLEAVER.run(hndDEINTERLEAVER);
      	    }
            
           // Pack the de-interleaved bits into works
           nWords  = (n * m) >> 4; 
           remBits = (n * m) - (nWords << 4);
           tmp_p   = &deinterleavedOutput[0];
           testOutput_p = &testOutput[0];
           for (i = 0; i < nWords; i++){
             tmp = 0;
             tmp |= (*tmp_p++);
             tmp |= (*tmp_p++ << 1);
             tmp |= (*tmp_p++ << 2);
             tmp |= (*tmp_p++ << 3);
             tmp |= (*tmp_p++ << 4);
             tmp |= (*tmp_p++ << 5);
             tmp |= (*tmp_p++ << 6);
             tmp |= (*tmp_p++ << 7);
             tmp |= (*tmp_p++ << 8);
             tmp |= (*tmp_p++ << 9);
             tmp |= (*tmp_p++ << 10);
             tmp |= (*tmp_p++ << 11);
             tmp |= (*tmp_p++ << 12);
             tmp |= (*tmp_p++ << 13);
             tmp |= (*tmp_p++ << 14);
             tmp |= (*tmp_p++ << 15);
             *testOutput_p++ = tmp;
            }
           if (remBits > 0){
             // There are a few more bits <16 that are packed into
             // the last word
	         tmp = 0;
	         for (kk = 0; kk < remBits; kk++)
	           tmp |= (*tmp_p++ << kk);
               *testOutput_p = tmp;
            }
            // Step 4: Verify the result
            testInput_p = &testInput[0];
            testOutput_p = &testOutput[0];

            // check for error
            for (idx = 0; idx < (n * m >> 3); idx++){
                if (idx & 0x1){ // odd, upper byte 
                    tmp = __byte((int *)testInput_p++, 1) ^ __byte((int *)testOutput_p++, 1);
                }else{ // even, lower byte
                    tmp = __byte((int *)testInput_p, 0) ^ __byte((int *)testOutput_p, 0);
                }
                // check for error
                if (tmp){
                    fail++;
                }else{
                    pass++;
                }
            }
        }
    }

    //*************************************************************************
    //!
    //! \endcode
    //!
    //*************************************************************************
    // End of test
    done();
    // Execution never reaches this point
    return 1;
}
// End of main

// @} //addtogroup

// End of file
