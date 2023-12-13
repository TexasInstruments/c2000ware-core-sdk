#ifndef _VCU0_FFT_H_
#define _VCU0_FFT_H_
//#############################################################################
//! \file include/vcu0/vcu0_fft.h
//!
//! \brief  Fast-Fourier Transform header file
//#############################################################################
//!
//! Copyright: Copyright (C) 2023 Texas Instruments Incorporated -
//!	All rights reserved not granted herein.
//!	Limited License.
//!
//! Texas Instruments Incorporated grants a world-wide, royalty-free,
//! non-exclusive license under copyrights and patents it now or hereafter
//! owns or controls to make, have made, use, import, offer to sell and sell
//! ("Utilize") this software subject to the terms herein. With respect to the
//! foregoing patent license, such license is granted solely to the extent that
//! any such patent is necessary to Utilize the software alone. The patent
//! license shall not apply to any combinations which include this software,
//! other than combinations with devices manufactured by or for TI 
//! ("TI Devices").
//! No hardware patent is licensed hereunder.
//!
//! Redistributions must preserve existing copyright notices and reproduce this
//! license (including the above copyright notice and the disclaimer and
//! (if applicable) source code license limitations below) in the documentation
//!  and/or other materials provided with the distribution.
//!
//! Redistribution and use in binary form, without modification, are permitted
//! provided that the following conditions are met:
//!
//! * No reverse engineering, decompilation, or disassembly of this software is 
//! permitted with respect to any software provided in binary form.
//! * Any redistribution and use are licensed by TI for use only 
//!   with TI Devices.
//! * Nothing shall obligate TI to provide you with source code for the 
//!   software licensed and provided to you in object code.
//!
//! If software source code is provided to you, modification and redistribution
//! of the source code are permitted provided that the following conditions 
//! are met:
//!
//! * any redistribution and use of the source code, including any resulting
//!   derivative works, are licensed by TI for use only with TI Devices.
//! * any redistribution and use of any object code compiled from the source
//!   code and any resulting derivative works, are licensed by TI for use 
//!   only with TI Devices.
//!
//! Neither the name of Texas Instruments Incorporated nor the names of its
//! suppliers may be used to endorse or promote products derived from this 
//! software without specific prior written permission.
//#############################################################################

//*****************************************************************************
// includes
//*****************************************************************************
#include "vcu0_types.h"

//!
//! \defgroup VCU0_FFT Fast Fourier Transform (VCU0)

//!
//! \ingroup VCU0_FFT
// @{
//
#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
// defines
//*****************************************************************************
#define NULL    0
#define  rfft16_unpack (fft_hnd)  rfft16_unpack_asm (fft_hnd)

//! Default values for the complex FFT structure for 64 sample points
#define cfft16_64P_DEFAULTS    { (int *)NULL,\
        (int *)NULL,\
        (int *)NULL,\
        64,\
        6,\
		8,\
		(int *)NULL,\
        (void (*)(void *))cfft16_init,\
        (void (*)(void *))cfft16_64p_calc}

//! Default values for the complex FFT structure for 64 sample points
//! if using bit reversal lookup table (Deprecated)        
#define cfft16_64P_BREV_DEFAULTS    { (int *)NULL,\
        (int *)NULL,\
        (int *)NULL,\
        64,\
        6,\
		8,\
		BIT_REV_64_TBL,\
        (void (*)(void *))cfft16_init,\
        (void (*)(void *))cfft16_64p_calc}

//! Default values for the complex FFT structure for 128 sample points
#define cfft16_128P_DEFAULTS    { (int *)NULL,\
        (int *)NULL,\
        (int *)NULL,\
        128,\
        7,\
		4,\
		(int *)NULL,\
        (void (*)(void *))cfft16_init,\
        (void (*)(void *))cfft16_128p_calc}

//! Default values for the complex FFT structure for 256 sample points
#define cfft16_256P_DEFAULTS    { (int *)NULL,\
        (int *)NULL,\
        (int *)NULL,\
        256,\
        8,\
		2,\
		(int *)NULL,\
        (void (*)(void *))cfft16_init,\
        (void (*)(void *))cfft16_256p_calc}

//! Default values for the complex FFT structure for 128 real sample points        
#define rfft16_128P_DEFAULTS    { (int *)NULL,\
        (int *)NULL,\
        (int *)NULL,\
		64,\
		6,\
		4,\
		(int *)NULL,\
        (void (*)(void *))cfft16_init,\
        (void (*)(void *))cfft16_64p_calc}

//! Default values for the complex FFT structure for 256 real sample points               
#define rfft16_256P_DEFAULTS    { (int *)NULL,\
        (int *)NULL,\
        (int *)NULL,\
        128,\
        7,\
		4,\
		(int *)NULL,\
        (void (*)(void *))cfft16_init,\
        (void (*)(void *))cfft16_128p_calc}

//! Default values for the complex FFT structure for 512 real sample points            
#define rfft16_512P_DEFAULTS    { (int *)NULL,\
        (int *)NULL,\
        (int *)NULL,\
        256,\
        8,\
		1,\
		(int *)NULL,\
        (void (*)(void *))cfft16_init,\
        (void (*)(void *))cfft16_256p_calc}
        
//! Default values for the Real Inverse FFT structure for 64 points
#define rifft16_64P_DEFAULTS   \
        cfft16_64P_DEFAULTS

//! Default values for the Real Inverse FFT structure for 128 points
#define rifft16_128P_DEFAULTS   \
        cfft16_128P_DEFAULTS

//! Default values for the Real Inverse FFT structure for 256 points        
#define rifft16_256P_DEFAULTS   \
        cfft16_256P_DEFAULTS        
        
#define cfft16_pack(fft_hnd)	\
		cfft16_pack_asm(fft_hnd)
		
#define cfft16_unpack(fft_hnd)	\
		cfft16_unpack_asm(fft_hnd)

//*****************************************************************************
// typedefs
//*****************************************************************************

//! Complex FFT data structure
typedef struct {
        int *ipcbptr;                       //!< input buffer pointer
        int *workptr;                       //!< work buffer pointer
        int *tfptr;                         //!< twiddle factor table pointer
        int size;							//!< Number of data points
        int nrstage;						//!< Number of FFT stages
        int step;							//!< Twiddle factor table search step
        int *brevptr;						//!< Bit reversal table pointer
        void (*init)(void *);				//!< Function pointer to initialization routine
        void (*calc)(void *);				//!< Function pointer to calculation routine
        }cfft16_t;

typedef cfft16_t  *cfft16_handle_s;			//!< Handle to structure

//*****************************************************************************
// globals
//*****************************************************************************
extern SINT16 CFFT16_64p_in_data[];				// Input fed into the simulator
extern SINT16 CFFT16_64p_out_data[];			// Output from the simulator
extern SINT16 CFFT16_64p_brev_in_data[];		// Input fed into the simulator
extern SINT16 CFFT16_64p_brev_out_data[];		// Output from the simulator
extern SINT16 CFFT16_128p_in_data[];			// Input fed into the simulator
extern SINT16 CFFT16_128p_out_data[];			// Output from the simulator
extern SINT16 CFFT16_256p_in_data[];			// Input fed into the simulator
extern SINT16 CFFT16_256p_out_data[];			// Output from the simulator
extern SINT16 RFFT16_128p_in_data[];			// Input fed into the simulator
extern SINT16 RFFT16_128p_out_data[];			// Output from the simulator
extern SINT16 RFFT16_256p_in_data[];			// Input fed into the simulator
extern SINT16 RFFT16_256p_out_data[];			// Output from the simulator
extern SINT16 RFFT16_512p_in_data[];			// Input fed into the simulator
extern SINT16 RFFT16_512p_out_data[];			// Output from the simulator
extern SINT16 RIFFT16_64p_in_data[];            // Input fed into the simulator
extern SINT16 RIFFT16_64p_out_data[];           // Output from the simulator
extern SINT16 RIFFT16_128p_in_data[];           // Input fed into the simulator
extern SINT16 RIFFT16_128p_out_data[];          // Output from the simulator
extern SINT16 RIFFT16_256p_in_data[];           // Input fed into the simulator
extern SINT16 RIFFT16_256p_out_data[];          // Output from the simulator

extern SINT16 BIT_REV_64_TBL[64];
extern SINT16 CFFT16_TF[];

//*****************************************************************************
// function prototypes
//*****************************************************************************
//! \brief Twiddle Factor Table Initialization
//!
//! Initializes the tfptr (twiddle factor pointer)to the start of the twiddle factor
//! table in memory
//!
//! \param cfft16_handle_s Handle to the FFT structure
//  
extern void cfft16_init(cfft16_t  *cfft16_handle_s);

//! \brief Bit-Reversed Indexing
//!
//! Rearranges the input data in bit-reveresed index format. If the number
//! of FFT stages is even, the data is bit-reversed into the work buffer and then copied
//! back to the input buffer. In this respect the bit reversal is considered to be
//! in-place. For an odd number of stages the bit-reversed output is placed 
//! in the work buffer (off-place). The FFT (not the bit reversal function) 
//! will then transfer the data back to the input buffer pointed to by ipcbptr
//!
//! \param cfft16_handle_s Handle to the FFT structure
//!
//! \attention For bit reverse addressing to work, the input buffer must be aligned
//! to size of the buffer in words (16-bit). For example, the 128 point complex FFT requires
//! an input buffer of size 256 words (16-bit), therefore it must be aligned to a boundary
//! of 256. This can be done by assigning the array to a named section 
//! (fftInput) using compiler pragmas (in the example, the input is assigned to 
//! .econst and aligned to a boundary of 256 using the .align assembler directive)
//! \code #pragma DATA_SECTION (CFFT16_128p_in_data, "fftInput") \endcode
//! and then either assigning this memory to the start of a RAM block in the 
//! linker command file, as is done in the examples, or aligning it to a boundary
//! using the align directive
//! \code fftInput  : > RAMLS4, ALIGN = 256, PAGE = 1 \endcode
// 
extern void cfft16_brev(cfft16_t  *cfft16_handle_s);

//! \brief Flip real and imaginary parts of complex number
//!
//! This functions is needed in the computation of real FFTs to ensure that
//! the real part of the complex number always ends up at the high word (16-bit) of 
//! a 32 bit address
//!
//! \param cfft16_handle_s Handle to the FFT structure
// 
extern void cfft16_flip_re_img(cfft16_t  *cfft16_handle_s);

//! \brief Flip real and imaginary parts of complex number and conjugate
//!
//! This functions is needed in the computation of real IFFTs to ensure that
//! the real part of the complex number always ends up at the high word (16-bit) of 
//! a 32 bit address
//!
//! \param cfft16_handle_s Handle to the FFT structure
//
extern void cfft16_flip_re_img_conj(cfft16_t  *cfft16_handle_s);

//! \brief Real FFT Unpack
//!
//! When using an N/2 pt complex FFT to compute the N-pt real FFT, the
//! result of the complex FFT must be unpacked to get the real value. Refer
//! to http://www.engineeringproductivitytools.com/stuff/T0001/PT10.HTM
//! for the complete derivation and explanation of the algorithm
//!
//! \param cfft16_handle_s Handle to the FFT structure
//
extern void cfft16_unpack_asm(cfft16_t  *cfft16_handle_s);

//! \brief complex IFFT pack
//!
//! When calculating the IFFT of a Real FFT, the data must be packed before 
//! using the complex IFFT to get the result. Refer to 
//! http://www.engineeringproductivitytools.com/stuff/T0001/PT10.HTM
//! for the complete derivation and explanation of the algorithm
//!
//! \param cfft16_handle_s Handle to the FFT structure
//
extern void cifft16_pack_asm(cfft16_t  *cfft16_handle_s);

//! \brief Calculate the 64 pt Complex FFT
//!
//! \param cfft16_handle_s Handle to the FFT structure
//!
//
extern void cfft16_64p_calc(cfft16_t  *cfft16_handle_s);

//! \brief Calculate the 128 pt Complex FFT
//!
//! \param cfft16_handle_s Handle to the FFT structure
//!
//! \sa cfft16_brev for memory alignment requirements
//
extern void cfft16_128p_calc(cfft16_t  *cfft16_handle_s);

//! \brief Calculate the 256 pt Complex FFT
//!
//! \param cfft16_handle_s Handle to the FFT structure
//!
//! \sa cfft16_brev for memory alignment requirements
//
extern void cfft16_256p_calc(cfft16_t  *cfft16_handle_s);

// \brief Table based Bit Reversal
//
// \param cfft16_handle_s Handle to the FFT structure
//
// Uses the table, pointed to by brevptr, to rearrange the input data
// in bit reversed index format 
//
//
extern void cfft16_tbl_brev(cfft16_t  *cfft16_handle_s) __attribute__ ((__deprecated__));

#ifdef __cplusplus
}
#endif // extern "C"

// @} //ingroup

#endif //end of _VCU0_FFT_H_ definition

// End of File
