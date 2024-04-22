//#############################################################################
//! \file /2837x_vcu2_viterbi_k7cr12/main.c
//!
//! \brief  Demo code for Viterbi K=7 CR=1/2 routine(VCU)
//!
//! \date   August 1, 2013
//! 
//! This example shows how to use the vcu2 supported VITERBI routines from the
//! library
//!
//
//  Group:             C2000
//  Target Family:     F2837x
//
//#############################################################################
//
//
// $Copyright: Copyright (C) 2024 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################

//*****************************************************************************
// includes
//*****************************************************************************
#include "vcu2_types.h"
#include "viterbi_encoder.h"
#include "vcu2_viterbi_decoder.h"
#include "examples_setup.h"

//!
//! \defgroup VITERBI_EXAMPLES Viterbi Decoder K=7, CR=1/2 Example

//!
//! \ingroup VITERBI_EXAMPLES
// @{

//*****************************************************************************
// defines
//*****************************************************************************
#define DATA_PACK_LEN        	64
#define DATA_BITS_LEN        	(DATA_PACK_LEN << 4)
#define FRAME_LENGTH			DATA_PACK_LEN
#define CODE_RATE               2
#define CODED_LENGTH			FRAME_LENGTH * CODE_RATE
#define CONSTRAINT_LENGTH		4
#define NSTATES					(1 << (CONSTRAINT_LENGTH - 1))
#define NEG_STATEMETRIC_INIT 	-8192
#define ERR_EPSILON				0
#define CNV_DEC_BLK_UBITS       64
#define CNV_DEC_BLK_CBITS       (CNV_DEC_BLK_UBITS << 1)  // CR=1/2
//*****************************************************************************
// globals
//*****************************************************************************
#ifdef __cplusplus
#pragma DATA_SECTION("testInput")
#else
#pragma DATA_SECTION(dataPack,"testInput")
#endif //__cplusplus

// \brief Test Input Data. This is also the expected
// output after decoding
//
uint16_t dataPack[DATA_PACK_LEN] = {
	  0x0100, 0x0302, 0x0504, 0x0706,
	  0x0908, 0x0B0A, 0x0D0C, 0x0F0E,
	  0x1110, 0x1312, 0x1514, 0x1716,
	  0x1918, 0x1B1A, 0x1D1C, 0x1F1E,
	  0x2120, 0x2322, 0x2524, 0x2726,
	  0x2928, 0x2B2A, 0x2D2C, 0x2F2E,
	  0x3130, 0x3332, 0x3534, 0x3736,
	  0x3938, 0x3B3A, 0x3D3C, 0x3F3E,
	  0x4140, 0x4342, 0x4544, 0x4746,
	  0x4948, 0x4B4A, 0x4D4C, 0x4F4E,
	  0x5150, 0x5352, 0x5554, 0x5756,
	  0x5958, 0x5B5A, 0x5D5C, 0x5F5E,
	  0x6160, 0x6362, 0x6564, 0x6766,
	  0x6968, 0x6B6A, 0x6D6C, 0x6F6E,
	  0x7170, 0x7372, 0x7574, 0x7776,
	  0x7978, 0x7B7A, 0x7D7C, 0x7F7E,
};

uint16_t dataBits[DATA_BITS_LEN];

#ifdef __cplusplus
#pragma DATA_SECTION("receivedBits")
int16_t dataReceived[DATA_BITS_LEN<<1];

#pragma DATA_SECTION("decodedBits")
uint16_t dataOut[DATA_BITS_LEN];

#pragma DATA_SECTION("decodedBits")
uint16_t oneShotDataOut[256];

#pragma DATA_SECTION("transitionBits")
uint16_t transitionBits[560];
#else
#pragma DATA_SECTION(dataReceived,"receivedBits")
int16_t dataReceived[DATA_BITS_LEN<<1];

#pragma DATA_SECTION(dataOut,"decodedBits")
uint16_t dataOut[DATA_BITS_LEN];

#pragma DATA_SECTION(oneShotDataOut,"decodedBits")
uint16_t oneShotDataOut[256];

#pragma DATA_SECTION(transitionBits,"transitionBits")
uint16_t transitionBits[560];
#endif // __cplusplus

#pragma DATA_ALIGN(dataOut, 2)
#pragma DATA_ALIGN(oneShotDataOut, 2)

uint16_t tempTransitionBits[290];

const int32_t BMSELInit[] = {0x54541010 ,0x10105454, 0x01014545, 0x45450101};

VITERBI_DECODER_Obj VITERBI_DECODER;
VITERBI_DECODER_Handle handleVITERBIDecoder = &VITERBI_DECODER;

VITERBI_ENCODER_Obj VITERBI_ENCODER;
VITERBI_ENCODER_Handle handleVITERBIEncoder = &VITERBI_ENCODER;

uint16_t pass = 0;
uint16_t fail = 0;
//*****************************************************************************
// Function Prototypes
//*****************************************************************************

//*****************************************************************************
// function definitions
//*****************************************************************************

//!
//! \brief main routine for the Viterbi decoder K=7 CR=1/2
//! \return returns a 1
//!
//! This example shows how to use the vcu2 supported VITERBI routines from the
//! library. The raw data, placed in a section "testInput", will be convolutionally
//! encoded based on a set of encoder polynomial predetermined for this particular
//! coding scheme. The encoded bits are quantized and stored in the "receivedBits"
//! section. The vcu2 decoder will then decode this bit stream and store the output
//! in the "decodedBits" section which needs to be aligned to an even address as 
//! the traceback step writes out 32 bits at a time, if first word is not aligned to
//! an even address, the trace will overwrite the previous address and may corrupt
//! other data
//!
int main( void )
{
    // Locals
    int16_t i, k;
    uint16_t nBits, nBlks;

#ifdef FLASH
	EALLOW;
	Flash0EccRegs.ECC_ENABLE.bit.ENABLE = 0;
	EDIS;
	memcpy((uint32_t *)&RamfuncsRunStart, (uint32_t *)&RamfuncsLoadStart,
			(uint32_t)&RamfuncsLoadSize );
	VCU2_initFlash();
#endif //FLASH
	
	VCU2_initSystemClocks();
	
	VCU2_initEpie();

    //*************************************************************************
    //! \b Running \b the \b Viterbi \b Encoder
    //! The raw data stream is first unpacked and then fed to the convolutional
    //! encoder which uses the following polynomials to generate the LLRs
	//! \f$ G_{0} = 1 + D_{0} + D_{2} + D_{3} + D_{6} \f$                                            
    //! \f$ G_{1} = 1 + D_{2} + D_{3} + D_{5} + D_{6} \f$  
    //! The encoded bits are quantized before feeding them to the decoder
    //! \code
    //*************************************************************************
	// Step 1: Unpack the raw data stream, clear out the last CONSTRAINT_LENGTH-1
	// bits
	VITERBI_ENCODER_blockUnpack2Bits(DATA_PACK_LEN, (uint16_t *)dataPack, (uint16_t *)dataBits);
	for (i=1; i<=(CONSTRAINT_LENGTH-1); i++){
		dataBits[DATA_BITS_LEN - i] = 0;
	}

	// Step 2: Initialize the Encoder structure and encode the bit stream followed by
	// quantization of the encoded LLRs. This is the typical process at the transmission end
	VITERBI_ENCODER.u_p      = (uint16_t *)dataBits;
	VITERBI_ENCODER.c_p      = (uint16_t *)dataReceived;
	VITERBI_ENCODER.cr       = CODE_RATE;
	VITERBI_ENCODER.nBits    = DATA_BITS_LEN;
	VITERBI_ENCODER.init     = (void (*)(void *))VITERBI_ENCODER_init;
	VITERBI_ENCODER.run      = (void (*)(void *))VITERBI_ENCODER_runK7CR12;
	VITERBI_ENCODER.quantize = (void (*)(void *, int16_t ))VITERBI_ENCODER_quantizeBits;

	VITERBI_ENCODER.init(handleVITERBIEncoder);
	VITERBI_ENCODER.run(handleVITERBIEncoder);
	VITERBI_ENCODER.quantize(handleVITERBIEncoder, 5);
    //*************************************************************************
    //! \endcode
    //! \b Running \b the \b Viterbi \b Decoder
    //! The encoded LLRs are run through the Viterbi Decoder in batches of 128
    //! bits. For a code rate of 1/2 each block should yield 64 bits after traceback
    //! There are three modes of operation shown in this example:
    //! - VITERBIMODE_OVERLAPINIT The first block of 128 bits are fed through the
    //!     decoding trellis; state metrics and transition bits are updated (and stored
    //!     to memory if necessary) but no traceback is performed in this block
    //! - VITERBIMODE_OVERLAPDECODE  The next N-2 blocks are fed through the trellis.
    //!     The state metrics and transition bits are updated for the i^{th}block and the
    //!     transition history of both the i^{th} and i-1^{st} blocks i.e. 128 transition bits
    //!     are used to trace back the i-1^{st} block of 64 bits.
    //! - VITERBIMODE_OVERLAPLAST This mode is used for the final (N^{th}) block of 128
    //!     The state metric and transition bits are updated and the block is decoded
    //!     using the final transition bits
    //! \code
    //*************************************************************************
	// Step 1: Initialize VITERBI object
	VITERBI_DECODER.codeRate	 	  = CODE_RATE; //Actually 1/CODE_RATE
	VITERBI_DECODER.constraintLength  = CONSTRAINT_LENGTH;
	VITERBI_DECODER.mode              = VITERBIMODE_OVERLAPINIT;
	VITERBI_DECODER.stateMetricInit   = NEG_STATEMETRIC_INIT;
	VITERBI_DECODER.nBits             = CNV_DEC_BLK_CBITS;
	VITERBI_DECODER.nStates           = NSTATES;
	VITERBI_DECODER.pInBuffer         = dataReceived;
	VITERBI_DECODER.pOutBuffer        = dataOut;
	VITERBI_DECODER.pTransitionHistory= transitionBits;
	VITERBI_DECODER.pBMSELInit        = BMSELInit;
	VITERBI_DECODER.pTransitionStart1 = transitionBits;
	VITERBI_DECODER.pTransitionStart2 = transitionBits + 4 * CNV_DEC_BLK_UBITS;
	VITERBI_DECODER.pTransitionWrap1  = transitionBits + 4 * CNV_DEC_BLK_UBITS;
	VITERBI_DECODER.pTransitionWrap2  = transitionBits + 8 * CNV_DEC_BLK_UBITS;
	VITERBI_DECODER.pTransitionTemp	  = tempTransitionBits;
	VITERBI_DECODER.run               =(void(*)(void *))VITERBI_DECODER_runK7CR12;
	VITERBI_DECODER.init			  =(void(*)(void *))VITERBI_DECODER_initK7CR12;
	VITERBI_DECODER.rescale		      =(void(*)(void *))VITERBI_DECODER_rescaleK7CR12;
	VITERBI_DECODER.init(handleVITERBIDecoder);

	//Step 2: Run for first block
	nBits = DATA_BITS_LEN << 1;
	VITERBI_DECODER.run(handleVITERBIDecoder);
	nBits -= CNV_DEC_BLK_CBITS;
	nBlks = 1;
	VITERBI_DECODER.pInBuffer += CNV_DEC_BLK_CBITS;

	//Step 3-N-1: Run viterbi for the middle blocks
	VITERBI_DECODER.mode  = VITERBIMODE_OVERLAPDECODE;
	while (nBits >= CNV_DEC_BLK_CBITS)
	{
		/* run viterbi decode */
		VITERBI_DECODER.run(handleVITERBIDecoder);
		VITERBI_DECODER.pInBuffer += CNV_DEC_BLK_CBITS;
		VITERBI_DECODER.pOutBuffer += (CNV_DEC_BLK_UBITS >> 4);
		nBits -= CNV_DEC_BLK_CBITS;
		nBlks++;

		/* rescale every 8 blks */
		if ((nBlks & 0x3) == 0)
			VITERBI_DECODER.rescale(handleVITERBIDecoder);
	}

	//Step N: Run Viterbi for the last block
	VITERBI_DECODER.nBits = nBits;
	VITERBI_DECODER.pOutBuffer += ((((CNV_DEC_BLK_UBITS+(nBits>>1)-6+31) >> 5)<<1));
	VITERBI_DECODER.mode = VITERBIMODE_OVERLAPLAST;
	VITERBI_DECODER.run(handleVITERBIDecoder);

    //*************************************************************************
    //! \endcode
    //! \b Running \b the \b Viterbi \b Decoder \b One-Shot \b Mode
    //! The example shows how to use the one-shot mode to decode upto 256
    //! bits in one go.
    //! \code
    //*************************************************************************
	// Step 1: Initialize VITERBI object
	VITERBI_DECODER.codeRate	 	  = CODE_RATE; //Actually 1/CODE_RATE
	VITERBI_DECODER.constraintLength  = CONSTRAINT_LENGTH;
	VITERBI_DECODER.mode              = VITERBIMODE_DECODEALL;
	VITERBI_DECODER.stateMetricInit   = NEG_STATEMETRIC_INIT;
	VITERBI_DECODER.nBits             = CNV_DEC_BLK_CBITS;
	VITERBI_DECODER.nStates           = NSTATES;
	VITERBI_DECODER.pInBuffer         = dataReceived;
	VITERBI_DECODER.pOutBuffer        = oneShotDataOut;
	VITERBI_DECODER.pTransitionHistory= transitionBits;
	VITERBI_DECODER.pBMSELInit        = BMSELInit;
	VITERBI_DECODER.pTransitionStart1 = transitionBits;
	VITERBI_DECODER.pTransitionStart2 = transitionBits + 4 * CNV_DEC_BLK_UBITS;
	VITERBI_DECODER.pTransitionWrap1  = transitionBits + 4 * CNV_DEC_BLK_UBITS;
	VITERBI_DECODER.pTransitionWrap2  = transitionBits + 8 * CNV_DEC_BLK_UBITS;
	VITERBI_DECODER.pTransitionTemp	  = tempTransitionBits;
	VITERBI_DECODER.run               =(void(*)(void *))VITERBI_DECODER_runK7CR12;
	VITERBI_DECODER.init			  =(void(*)(void *))VITERBI_DECODER_initK7CR12;
	VITERBI_DECODER.rescale		      =(void(*)(void *))VITERBI_DECODER_rescaleK7CR12;
	VITERBI_DECODER.init(handleVITERBIDecoder);

	// Step 2: Run for first 256 bit block
	VITERBI_DECODER.run(handleVITERBIDecoder);

    //*************************************************************************
    //!
    //! \endcode
    //!
    //*************************************************************************

	// Verify the results
	for (k=0; k<((DATA_BITS_LEN>>4) - 1); k++)
	{
		if (dataPack[k] != dataOut[k]){
			fail++;
			//          asm(" ESTOP0");
		}else{
			pass++;
		}
	}

	for (k=0; k< (64 - (CONSTRAINT_LENGTH-1)); k++)
	{
		oneShotDataOut[k] = tempTransitionBits[2*k];
		if (dataBits[k] != oneShotDataOut[k]){
			fail++;
			//          asm(" ESTOP0");
		}else{
			pass++;
		}
	}
    // End of test
    done();
    // Execution never reaches this point
    return 1;
}
// End of main

// @} //addtogroup

// End of file
