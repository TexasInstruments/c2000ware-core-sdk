//#############################################################################
//! \file /2837x_vcu0_rifft_128/main.c
//!
//! \brief  Demo code for the 128 sample Real Inverse FFT routine(VCU)
//!
//! \date   July 23, 2013
//! 
//! This example shows how to use the vcu0 supported CFFT routines from the
//! library to perform an Real Inverse FFT
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
//! \addtogroup VCU0_RIFFT_EXAMPLES Real Fast Fourier Transform (N = 128) Example

// @{

//*****************************************************************************
// defines
//*****************************************************************************
#define  DATA_LENGTH    (128<<1)
#define	 EPSILON		 2
//*****************************************************************************
// globals
//*****************************************************************************
cfft16_t fft = rifft16_128P_DEFAULTS;

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
void rifft16(cfft16_t *fft_hnd);
//*****************************************************************************
// function definitions
//*****************************************************************************

//!
//! \brief main routine for the 128-sample RFFT example
//! \return returns a 1
//!
//! This example shows how to use the vcu0 supported CFFT routines from the
//! library to perform a Real Inverse FFT. The input is placed in the .econst section
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
	  fft.ipcbptr = (int *)RIFFT16_128p_in_data + 0;
	  fft.workptr = (int *)fft_work_buffer + 0;
	  fft.init(&fft);

	// Step 2: Pack the input; bit reverse it then run the FFT. Finally, 
    // flip the real and imaginary parts of the output to obtain the 
	// real inverse FFT
	  rifft16(&fft);

    //*************************************************************************
    //!
    //! \endcode
    //!
    //*************************************************************************
	// Step 3: Verify the result
	  for (k=0; k<DATA_LENGTH; k++)	  {
		  if (abs(RIFFT16_128p_out_data[k] - RIFFT16_128p_in_data[k]) > EPSILON){
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

//! \brief Real IFFT routine
//!
//! \param Handle to the structure, cfft16_t
//!
//! Calculates the Real Inverse FFT
//!
//! \return none
//
void rifft16(cfft16_t *fft_hnd)
{
  // pack complex IFFT input
  cifft16_pack_asm(fft_hnd);

  // complex FFT
  cfft16_brev(fft_hnd);
  fft_hnd->calc(fft_hnd);
  
  //flip the real and imaginary and conjugate
  cfft16_flip_re_img_conj(fft_hnd);
}

// @} //addtogroup

// End of file
