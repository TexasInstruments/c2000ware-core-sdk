//#############################################################################
//! \file /2837x_vcu0_cfft_128/main.c
//!
//! \brief  Demo code for the 128 sample CFFT routine(VCU)
//!
//! \date   July 23, 2013
//! 
//! This example shows how to use the vcu0 supported CFFT routines from the
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
#include "vcu0_types.h"
#include "vcu0_fft.h"
#include "examples_setup.h"

//!
//! \addtogroup VCU0_CFFT_EXAMPLES Complex Fast Fourier Transform (N = 128) Example

// @{

//*****************************************************************************
// defines
//*****************************************************************************
#define  DATA_LENGTH    (128<<1)
//*****************************************************************************
// globals
//*****************************************************************************
cfft16_t fft = cfft16_128P_DEFAULTS;

#ifdef __cplusplus
#pragma DATA_SECTION (".shadow");
#else
#pragma DATA_SECTION (fft_work_buffer, ".shadow");
#endif //__cplusplus
ComplexShort fft_work_buffer[256];

//Global Data
UINT32 err=0;
SINT16 *dataIn_p, *dataOut_p;

uint16_t pass = 0;
uint16_t fail = 0;
//*****************************************************************************
// Function Prototypes
//*****************************************************************************
void cfft16(cfft16_t *fft_hnd);
//*****************************************************************************
// function definitions
//*****************************************************************************

//!
//! \brief main routine for the 128-sample CFFT example
//! \return returns a 1
//!
//! This example shows how to use the vcu0 supported CFFT routines from the
//! library. The input is placed in the .econst section and needs to be
//! aligned to the size of the input in words to allow the bit reverse
//! addressing in stage 1 of the FFT to work properly. The output, however, need
//! not be aligned to any boundary
//!
int main( void )
{
    // Locals
	SINT16 k;

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
    //! The user declares the cfft16_t Object with the appropriate
    //! init() and run() (often specified in the DEFAULT macros provided in the
    //! header file). The init() will load the twiddle factor table pointer
    //! to the structure. For the F2837xD devices, the twiddle factor tables are
    //! present in bootrom and may be used instead of the table provided with
    //! the library source code
    //! \code
    //*************************************************************************
	// Step 1: Initialize CFFT object
	  fft.ipcbptr = (int *)CFFT16_128p_in_data + 0;
	  fft.workptr = (int *)fft_work_buffer + 0;
	  fft.init(&fft);

	// Step 2: Bit reverse the input and then run the FFT
	  cfft16(&fft);

    //*************************************************************************
    //!
    //! \endcode
    //!
    //*************************************************************************
	// Step 3: Verify the result
	  for (k=0; k<DATA_LENGTH; k++)	  {
		  if (CFFT16_128p_out_data[k] != CFFT16_128p_in_data[k]){
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

//! \brief Complex FFT routine
//!
//! \param Handle to the structure, cfft16_t
//!
//! Rearrange the input data in bit reversed format and
//! call the FFT routine to get the complex FFT
//!
//! \return none
//
void cfft16(cfft16_t *fft_hnd)
{
  // bit reversal
  cfft16_brev(fft_hnd);
  // FFT core calculation
  fft_hnd->calc(fft_hnd);
}

// @} //addtogroup

// End of file
