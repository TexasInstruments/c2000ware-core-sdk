//#############################################################################
//! \file /2837x_vcu2_reedsolomon_n255k239/main.c
//!
//! \brief  Demo code for Reed-Solomon decoding(VCU)
//!
//! \date   November 21, 2013
//! 
//! This example shows how to use the vcu2 supported Reed-Solomon routines from the
//! library
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
#include "vcu2_types.h"
#include "reedsolomon_encoder.h"
#include "vcu2_reedsolomon_decoder.h"
#include "examples_setup.h"
#include "rs_tablesn255k239.h"

//!
//! \defgroup REEDSOLOMON_EXAMPLES Reed-Solomon Decoder n=255, k=239 Example

//!
//! \ingroup REEDSOLOMON_EXAMPLES
// @{

//*****************************************************************************
// defines
//*****************************************************************************
#define  DATA_LEN		256
#define  SYNDROME_SIZE	(((2*RS_BLOCK_T+3) >> 2) << 1)
#define  LAMBDA_SIZE	(((RS_BLOCK_T+1+3) >> 2) << 1)
#define  OMEGA_SIZE		((RS_BLOCK_T+1+1) >> 1)
#define  ERROR_SIZE		(RS_BLOCK_T)
//*****************************************************************************
// globals
//*****************************************************************************
#ifdef __cplusplus
#pragma DATA_SECTION("testInput")
#pragma DATA_ALIGN(2)
#else
#pragma DATA_SECTION(encoderIn,"testInput")
#pragma DATA_ALIGN(encoderIn, 2)
#endif //__cplusplus
//! \brief Encoder input data
//!
int16_t encoderIn[DATA_LEN] = {
	#include "encoder_input.h"
};

#ifdef __cplusplus
#pragma DATA_SECTION("testOutput")
#pragma DATA_ALIGN(2)
#else
#pragma DATA_SECTION(encoderOut,"testOutput")
#pragma DATA_ALIGN(encoderOut, 2)
#endif //__cplusplus

//! \brief Encoder Output data
//!
int16_t encoderOut[DATA_LEN];

#ifdef __cplusplus
#pragma DATA_SECTION("testOutput")
#pragma DATA_ALIGN(2)
#else
#pragma DATA_SECTION(decoderIO,"testOutput")
#pragma DATA_ALIGN(decoderIO, 2)
#endif //__cplusplus
//! \brief Decoder input and output buffer
//!
int16_t decoderIO[DATA_LEN];

#ifdef __cplusplus
#pragma DATA_SECTION("testInput")
#else
#pragma DATA_SECTION(refData,"testInput")
#endif //__cplusplus

//! \brief Expected output from the encoder
//!
int16_t refData[DATA_LEN] = {
	#include "encoder_output.h"
};

//! \brief Reed Solomon Encoder Object
//!
REEDSOLOMON_ENCODER_Obj REEDSOLOMON_ENCODER;

REEDSOLOMON_ENCODER_Handle hndREEDSOLOMONEncoder = &REEDSOLOMON_ENCODER;

//! \brief Reed Solomon Decoder Object
//!
REEDSOLOMON_DECODER_Obj REEDSOLOMON_DECODER;

REEDSOLOMON_DECODER_Handle hndREEDSOLOMONDecoder = &REEDSOLOMON_DECODER;
#ifdef __cplusplus
#pragma DATA_ALIGN(2)
#else
#pragma DATA_ALIGN(syndrome, 2)
#endif //__cplusplus
//! \brief Syndromes (8-bit packed)
//!
int16_t syndrome[SYNDROME_SIZE];
#ifdef __cplusplus
#pragma DATA_ALIGN(2)
#else
#pragma DATA_ALIGN(lambda, 2)
#endif //__cplusplus
//! \brief Error Locator polynomial coefficients
//!
int16_t lambda[LAMBDA_SIZE];
#ifdef __cplusplus
#pragma DATA_ALIGN(2)
#else
#pragma DATA_ALIGN(omega, 2)
#endif //__cplusplus
//! \brief Error magnitude polynomial coefficients
//!
int16_t omega[OMEGA_SIZE];
#ifdef __cplusplus
#pragma DATA_ALIGN(2)
#else
#pragma DATA_ALIGN(errorLoc, 2)
#endif //__cplusplus
//! \brief error (location, value) pairs
//!
ERROR_LOCVAL_Obj errorLoc[ERROR_SIZE];

int16_t nInBytes  = 235;
int16_t nOutBytes = 251;
uint16_t pass = 0;
uint16_t fail = 0;
//*****************************************************************************
// Function Prototypes
//*****************************************************************************
static inline int16_t GF_add(int16_t op1, int16_t op2);
//*****************************************************************************
// function definitions
//*****************************************************************************

//!
//! \brief main routine for the Reed-Solomon decoder n=255, k=239
//! \return returns a 1
//!
//! This example shows how to use the vcu2 supported REED_SOLOMON routines from the
//! library. The raw data, placed in a section "testInput", will be encoded
//! using the code generator polynomial and extension Galois Field for this particular
//! coding scheme. The encoded bits stored in the "encoderOut" and fed into the decoder
//! through the buffer "decoderIO" with error injected
//!
int main( void )
{
    // Locals
	int16_t i, temp, errorValue;
	uint16_t errorPosition;

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
    //! \b Running \b the \b Reed-Solomon \b Encoder
    //! The encoder uses the following polynomial to generate the coded sequence
    //! \f{eqnarray}
    //! 1.x^{ 16} +118.x^{ 15} + 52.x^{ 14} +103.x^{ 13} + 31.x^{ 12} +104.x^{ 11}
    //! + 126.x^{ 10} +187.x^{  9} +232.x^{  8} + 17.x^{  7} + 56.x^{  6} +183.x^{  5}
    //! + 49.x^{  4} +100.x^{  3} + 81.x^{  2} + 44.x^{  1} + 79
    //! \f}
    //! \code
    //*************************************************************************
	// Step 1: Intialize the encoder object
	REEDSOLOMON_ENCODER.init = (void (*)(void *, int16_t *,
            int16_t *, int16_t *))REEDSOLOMON_ENCODER_init;
	REEDSOLOMON_ENCODER.run = (void (*)(void *, int16_t *,
			int16_t))REEDSOLOMON_ENCODER_run;
	REEDSOLOMON_ENCODER.init(hndREEDSOLOMONEncoder,
			(int16_t *)RS_codeGenPoly,
			(int16_t *)RS_expTable,
			(int16_t *)RS_logTable);



	// Step 2: Prior to running the encoder, pack the input if necessary. Run the
	// encoder
#if WORD_2BYTES
	for (i = 0; i < (DATA_LEN >> 1); i++){
		encoderOut[i] = (encoderIn[2*i] & 0xFF) | (encoderIn[2*i+1]<<8);
	}
	REEDSOLOMON_ENCODER.run(hndREEDSOLOMONEncoder, encoderOut, nInBytes);
#else
	for (i = 0; i < (DATA_LEN >> 1); i++){
		encoderOut[i] = encoderIn[i];
	}
	REEDSOLOMON_ENCODER.run(hndREEDSOLOMONEncoder, encoderOut, nInBytes);
#endif //WORD_2BYTES

	// Step 3: Verify the results
	for( i = 0; i < nOutBytes ; i++){
#if WORD_2BYTES
		temp = __byte((int *)encoderOut, i);
		if(temp != refData[i]){
#else
		if(encoderOut[i] != refData[i]){
#endif //WORD_2BYTES
			fail++;
		}else{
			pass++;
		}
	}
    //*************************************************************************
    //! \endcode
    //! \b Running \b the \b Reed-Solomon \b Decoder
    //! Error is injected into the transmitted stream and then fed to the decoder
    //! \code
    //*************************************************************************

	// Copy the encoder output to the decoder input
	for( i = 0; i < nOutBytes; i++){
		decoderIO[i] = encoderOut[i];
	}

	//Inject error
#if WORD_2BYTES
	decoderIO[10] = (decoderIO[10] & 0xFF) | (111 << 8);
	decoderIO[20] = 222 | (222<<8);
	decoderIO[30] = 222 | (222<<8);
	decoderIO[40] = 222 | (222<<8);
	decoderIO[50] = (decoderIO[50] & 0xFF00) | 222;
#else
	decoderIO[3] = 111;
	decoderIO[4] = 222;
	decoderIO[5] = 222;
	decoderIO[6] = 222;
	decoderIO[7] = 222;
	decoderIO[8] = 222;
	decoderIO[9] = 222;
	decoderIO[10] = 222;
#endif
	// Step 1: Initialize Reed-Solomon Decoder object
	REEDSOLOMON_DECODER.init = (void (*)(void *,
			int16_t *, int16_t *, int16_t *, int16_t *,
			int16_t *, int16_t *, int16_t *,
			ERROR_LOCVAL_Obj *))REEDSOLOMON_DECODER_initN255K239;
	REEDSOLOMON_DECODER.run = (void (*)(void *, int16_t *,
			int16_t))REEDSOLOMON_DECODER_runN255K239;
	REEDSOLOMON_DECODER.init(hndREEDSOLOMONDecoder,
            syndrome, lambda, omega, (int16_t *)RS_packedAlpha,
            (int16_t *)RS_packedBeta, (int16_t *)RS_expTable,
            (int16_t *)RS_logTable, errorLoc);

	//Step 2: Run the decoder
	REEDSOLOMON_DECODER.run(hndREEDSOLOMONDecoder, decoderIO, nOutBytes);

	//Step 3: Correct the error
	for(i = 0; i < ERROR_SIZE; i ++){
		errorPosition  = errorLoc[i].pos;
		errorValue     = errorLoc[i].val;
		__byte((int *)decoderIO, errorPosition) = GF_add(errorValue,
				__byte((int *)decoderIO, errorPosition));
	}

    //*************************************************************************
    //!
    //! \endcode
    //!
    //*************************************************************************

	// Verify the results
	for(i = 0; i < nOutBytes; i ++){
		if(decoderIO[i] == encoderOut[i]){
			pass++;
		}else{
			fail++;
		}
	}
    // End of test
    done();
    // Execution never reaches this point
    return 1;
}
// End of main

// \brief Galois Field Addition
//
// Addition or subtraction in GF(2) binary and GF(2^m) extenstion fields
// are equivalent and can be carried out through a simple XOR operation
// \param[in] op1 First operand in decimal form
// \param[in] op2 Second operand in decimal form
// \return Sum (or difference) of the two operands using GF arithmetic in
//         decimal form
//
static inline int16_t GF_add(int16_t op1, int16_t op2)
{
	return ( op1 ^ op2);
}

// @} //addtogroup

// End of file
