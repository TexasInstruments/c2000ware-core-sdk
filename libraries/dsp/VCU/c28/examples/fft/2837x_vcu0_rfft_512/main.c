//#############################################################################
//! \file /2837x_vcu0_rfft_512/main.c
//!
//! \brief  Demo code for the 512 sample RFFT routine(VCU)
//!
//! \date   July 23, 2013
//! 
//! This example shows how to use the vcu0 supported CFFT routines from the
//! library to perform a Real FFT
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
#include "vcu0_fft.h"
#include "examples_setup.h"

//!
//! \addtogroup VCU0_RFFT_EXAMPLES Real Fast Fourier Transform (N = 512) Example

// @{

//*****************************************************************************
// defines
//*****************************************************************************
#define  DATA_LENGTH    (256<<1)
#define  EPSILON		 1
//*****************************************************************************
// globals
//*****************************************************************************
cfft16_t fft = rfft16_512P_DEFAULTS;

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
void rfft16(cfft16_t *fft_hnd);
//*****************************************************************************
// function definitions
//*****************************************************************************

//!
//! \brief main routine for the 512-sample RFFT example
//! \return returns a 1
//!
//! This example shows how to use the vcu0 supported CFFT routines from the
//! library to perform a Real FFT. The input is placed in the .econst section
//! and needs to be aligned to the size of the input in words to allow the bit reverse
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
	  fft.ipcbptr = (int *)RFFT16_512p_in_data + 0;
	  fft.workptr = (int *)fft_work_buffer + 0;
	  fft.init(&fft);

	// Step 2: Flip real and imaginary part of the complex input; bit reverse
	// it then run the FFT. Finally, unpack the complex output to get the
	// real FFT
	  rfft16(&fft);

    //*************************************************************************
    //!
    //! \endcode
    //!
    //*************************************************************************
	// Step 3: Verify the result
	  for (k=0; k<DATA_LENGTH; k++)	  {
		  if (abs(RFFT16_512p_out_data[k] - RFFT16_512p_in_data[k]) > EPSILON){
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

//! \brief Real FFT routine
//!
//! \param Handle to the structure, cfft16_t
//!
//! This function reinterprets the N pt data as N/2 pt complex data
//! and flips the real and imaginary parts before calling the bit
//! reversal function. An N/2 pt complex FFT is used on the data and
//! the result is unpacked to get the real FFT
//!
//! \return none
//
void rfft16(cfft16_t *fft_hnd)
{
	// flip real and imaginary, VCU-0 real part is at high word
	cfft16_flip_re_img(fft_hnd);

	// bit reversal
	cfft16_brev(fft_hnd);

	// FFT core calculation
	fft_hnd->calc(fft_hnd);

	// unpack the complex FFT output
	cfft16_unpack(fft_hnd);
}

// @} //addtogroup

// End of file
