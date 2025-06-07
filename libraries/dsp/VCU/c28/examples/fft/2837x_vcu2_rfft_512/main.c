//#############################################################################
//! \file /2837x_vcu2_rfft_512/main.c
//!
//! \brief  Demo code for the 512 sample RFFT(VCU) and RIFFT(VCU)
//!
//! \date   July 23, 2013
//! 
//! This example shows how to use the vcu2 supported CFFT and utility routines
//! from the library to perform an FFT of an N point real sequence
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
#include "vcu2_types.h"
#include "vcu2_fft.h"
#include "examples_setup.h"

//!
//! \addtogroup RFFT_EXAMPLES Fast Fourier Transform of a 512 point Real Sequence

// @{

//*****************************************************************************
// defines
//*****************************************************************************
#define NSTAGES		8
#define NSAMPLES 	1<<NSTAGES
#define ERR_EPSILON	3
//*****************************************************************************
// globals
//*****************************************************************************
#ifdef __cplusplus
#pragma DATA_SECTION("buffer1")
#else
#pragma DATA_SECTION(buffer1Q15,"buffer1")
#endif //__cplusplus
// \brief Test Input Data
//
int16_t buffer1Q15[2*NSAMPLES] = {
    #include "data_input.h"
};

// \brief Expected Output
//
const int16_t goldenOutputQ15[2*NSAMPLES] = {
    #include "data_output.h"
};

// \brief Error Vector
//
int16_t errorQ15[2*NSAMPLES];

#ifdef __cplusplus
#pragma DATA_SECTION("buffer2")
#else
#pragma DATA_SECTION(buffer2Q15,"buffer2")
#endif
// \brief Test Output Data
//
int16_t buffer2Q15[2*NSAMPLES];

// \brief CFFT Object
//
CFFT_Obj CFFT;

// \brief Handle to the CFFT object
//
CFFT_Handle handleCFFT;

uint16_t pass = 0;
uint16_t fail = 0;
//*****************************************************************************
// Function Prototypes
//*****************************************************************************

//*****************************************************************************
// function definitions
//*****************************************************************************

//!
//! \brief main routine for the 512-sample CFFT example
//! \return returns a 1
//!
//! This example shows how to use the vcu2 supported CFFT routines from the
//! library. The input is placed in a section buffer1 that needs to be
//! aligned to the size of the input in words to allow the bit reverse
//! addressing in stage 1 of the FFT to work properly. The output, however, need
//! not be aligned to any boundary
//!
int main( void )
{
    // Locals
    int16_t i;

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
    // Running the FFT
    //*************************************************************************
    //! \b Running \b the \b FFT
    //! The user starts by initializing the CFFT Object with the appropriate
    //! init() and run().The init() accepts pointers to the input and output
    //! buffers and will initialize the other object elements appropriately.
    //! For the F2837xD devices, the twiddle factor tables are already present
    //! in bootrom.
    //! For an N-point real sequence, we will treat the input as an N/2 point
    //! complex data set and then run an N/2 point complex FFT on it. The output
    //! must be "unpacked" to get the correct output
    //! \code
    //*************************************************************************
	// Step 1: Initialize CFFT object
    CFFT.pInBuffer  = buffer1Q15;
    CFFT.pOutBuffer = buffer2Q15;
	CFFT.init = (void (*)(void *))CFFT_init256Pt;
	CFFT.run  = (void (*)(void *))CFFT_run256Pt;

	// Step 2: Initialize the handle
	handleCFFT = &CFFT;

	// Step 3: Calling the init() will setup the twiddle factor table
    //         and run the Forward FFT followed by an unpacking routine
	CFFT.init(handleCFFT);
	CFFT.run(handleCFFT);
	CFFT_unpack(handleCFFT);
    //*************************************************************************
    //!
    //! \endcode
    //!
    //*************************************************************************

	// Step 4: Verify the result
	for(i = 0; i < CFFT.nSamples*2; i++){
		errorQ15[i] = abs(CFFT.pOutBuffer[i] - goldenOutputQ15[i]);
	  if( errorQ15[i] > ERR_EPSILON ){
          fail++;
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
