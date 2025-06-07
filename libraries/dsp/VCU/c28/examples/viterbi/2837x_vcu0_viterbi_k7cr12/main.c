//#############################################################################
//! \file /2837x_vcu0_viterbi_k7cr12/main.c
//!
//! \brief  Demo code for Viterbi K=7 CR=1/2 routine(VCU)
//!
//! \date   August 1, 2013
//! 
//! This example shows how to use the vcu0 supported VITERBI routines from the
//! library
//!
//
//  Group:             C2000
//  Target Family:     F2837x
//
//#############################################################################
//
//
// $Copyright: Copyright (C) 2025 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################

//*****************************************************************************
// includes
//*****************************************************************************
#include "vcu0_types.h"
#include "vcu0_viterbi_decoder.h"
#include "examples_setup.h"

//!
//! \defgroup VCU0_VITERBI_EXAMPLES Viterbi Decoder K=7, CR=1/2 Example

//!
//! \ingroup VCU0_VITERBI_EXAMPLES
// @{

//*****************************************************************************
// defines
//*****************************************************************************
#define DATA_PACK_LEN        	128
#define DATA_BITS_LEN        	(DATA_PACK_LEN << 4)
//*****************************************************************************
// globals
//*****************************************************************************
#ifdef __cplusplus
#pragma DATA_SECTION("buffer_out")
#else
#pragma DATA_SECTION(data_out,"buffer_out")
#endif //__cplusplus
UINT16 data_out[255];
extern int16 VIT_quant_data[];

// \brief Test Input Data. This is also the expected
// output after decoding
//
UINT16 data_pack[DATA_PACK_LEN] = 
{
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
  0x7978, 0x7B7A, 0x7D7C, 0x407E,

};

UINT32 err=0;

SINT16 *dataIn_p, *dataOut_p;
int vblk = 0;
int nBits = 0;

uint16_t pass = 0;
uint16_t fail = 0;
//*****************************************************************************
// Function Prototypes
//*****************************************************************************
void Error(void);
//*****************************************************************************
// function definitions
//*****************************************************************************

//!
//! \brief main routine for the Viterbi decoder K=7 CR=1/2
//! \return returns a 1
//!
//! This example shows how to use the vcu0 supported VITERBI routines from the
//! library. The raw data, placed in a section "testInput", will be convolutionally
//! encoded based on a set of encoder polynomial predetermined for this particular
//! coding scheme. The encoded bits are quantized and stored in the "receivedBits"
//! section. The vcu0 decoder will then decode this bit stream and store the output
//! in the "decodedBits" section
//!
int main( void )
{
    // Locals
	SINT16 k;

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
	// Step 1: Run the decoder initialization
    cnvDecInit((int)CNV_DEC_BLK_CBITS);
    dataIn_p  = VIT_quant_data;
    dataOut_p = (SINT16 *)data_out;
    
	//Step 2: Run for first block
    nBits     = DATA_BITS_LEN << 1;
    cnvDec(CNV_DEC_BLK_CBITS,
           dataIn_p,
           dataOut_p,
           CNV_DEC_MODE_OVLP_INIT);
    vblk      = 1;
    dataIn_p += CNV_DEC_BLK_CBITS;
    nBits    -= CNV_DEC_BLK_CBITS;

	//Step 3-N-1: Run viterbi for the middle blocks
    while (nBits >= CNV_DEC_BLK_CBITS)
    {
      cnvDec(CNV_DEC_BLK_CBITS,
             dataIn_p,
             dataOut_p,
             CNV_DEC_MODE_OVLP_DEC);
      dataIn_p    += CNV_DEC_BLK_CBITS;
      dataOut_p   += (CNV_DEC_BLK_UBITS >> 4);
      nBits       -= CNV_DEC_BLK_CBITS;
      vblk++;


      /* rescale every 4 blks  */
      if ((vblk & 0x3) == 0)
        cnvDecMetricRescale();

    }

	//Step N: Run Viterbi for the last block
    cnvDec(nBits,
           dataIn_p,
           dataOut_p+((CNV_DEC_BLK_UBITS+nBits) >> 4),
           CNV_DEC_MODE_OVLP_LAST);

    //*************************************************************************
    //!
    //! \endcode
    //!
    //*************************************************************************

	// Verify the results
	for (k=0; k<((DATA_BITS_LEN>>4) - 1); k++)
	{
		if (data_pack[k] != data_out[k]){
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
