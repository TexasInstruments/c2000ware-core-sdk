#ifndef _VCU2_FFT_H_
#define _VCU2_FFT_H_
//#############################################################################
//! \file include/vcu2/vcu2_fft.h
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
#include "vcu2_types.h"

//!
//! \defgroup VCU2_FFT Fast Fourier Transform (VCU2)

//!
//! \ingroup VCU2_FFT
// @{

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
// defines
//*****************************************************************************
#define _DOXYGEN_	1	// Temporary Definition for documentation purposes

//*****************************************************************************
// typedefs
//*****************************************************************************

//! \brief CFFT structure
//!
typedef struct _CFFT_Obj_{
	int16_t		  *pInBuffer;		//!< Input buffer pointer
	int16_t		  *pOutBuffer;		//!< Output buffer pointer
	const int16_t *pTwiddleFactors;	//!< Twiddle Factor pointer
	int16_t		  nSamples;			//!< Number of samples
	int16_t		  nStages;			//!< Number of stages in the FFT, \f$n\ =\ log_{2}(N)\f$
	int16_t		  twiddleSkipStep;	//!< Twiddle factor table search(skip) step
	void (*init)(void *);           //!< Function pointer to CFFT initialization routine
	void (*run)(void *);			//!< Function pointer to CFFT computation routine
}CFFT_Obj;

//! \brief Handle to the CFFT structure
//!
typedef CFFT_Obj *CFFT_Handle;

//*****************************************************************************
// globals
//*****************************************************************************
//! \brief VCU2 twiddle factors
//!
extern const int16_t *vcu2_twiddleFactors;

//! \brief VCU0 twiddle factors
//!
extern const int16_t *vcu0_twiddleFactors;

//*****************************************************************************
// function prototypes
//*****************************************************************************
//! \brief Initializes the CFFT object
//! 
//! This routine is used to initialize the CFFT object and must be called atleast
//! once before using either the CFFT or ICFFT routines
//!
//! \param[in] hndCFFT handle to the CFFT object
//
void CFFT_init32Pt(CFFT_Handle hndCFFT);

//! \brief Runs the Complex FFT routine
//! 
//! \param[in] hndCFFT handle to the CFFT object
//! \attention For bit reverse addressing to work, the input buffer must be aligned
//! to size of the buffer in words (16-bit). For example, the 32 point complex FFT requires
//! an input buffer of size 64 words (16-bit), therefore it must be aligned to a boundary
//! of 64. This can be done by assigning the array to a named section 
//! (buffer1) using compiler pragmas 
//! \code #pragma DATA_SECTION(buffer1Q15,"buffer1") \endcode
//! and then either assigning this memory to the start of a RAM block in the 
//! linker command file or aligning it to a boundary using the align directive
//! \code buffer1 : > RAMLS3, ALIGN = 64, PAGE = 1 \endcode
//! \note The algorithm ping-pongs between the two buffers, i.e. the buffers 
//! pointed to by \b pInBuffer and \b pOutBuffer, at every stage. Depending
//! on the number of stages the output may be in either of the two buffers; the
//! algorithm will switch the pointers \b pOutBuffer and \b pInBuffer in the 
//! event that the output ends up in the original input buffer, with the end result
//! that \b pOutBuffer always points to the output.
//
void CFFT_run32Pt(CFFT_Handle hndCFFT);

//! \brief Runs the Complex Inverse FFT routine
//! 
//! Run the forward FFT on the input and rearrange the output as follows:
//! \f[x(0) =  x'(0)\f]
//! \f[x(n) = x'(N-n), n \in \{1,N-1\} \f], where N is the sample size
//!
//! \param[in] hndCFFT handle to the CFFT object
//! \attention For bit reverse addressing to work, the input buffer must be aligned
//! to size of the buffer in words (16-bit). For example, the 32 point complex FFT requires
//! an input buffer of size 64 words (16-bit), therefore it must be aligned to a boundary
//! of 64. This can be done by assigning the array to a named section 
//! (buffer1) using compiler pragmas 
//! \code #pragma DATA_SECTION(buffer1Q15,"buffer1") \endcode
//! and then either assigning this memory to the start of a RAM block in the 
//! linker command file or aligning it to a boundary using the align directive
//! \code buffer1 : > RAMLS3, ALIGN = 64, PAGE = 1 \endcode
//! If the output buffer of the forward FFT becomes the input to the IFFT, then it
//! must be aligned to the same word (16-bit) boundary as well.
//! \note The algorithm ping-pongs between the two buffers, i.e. the buffers 
//! pointed to by \b pInBuffer and \b pOutBuffer, at every stage. Depending
//! on the number of stages the output may be in either of the two buffers; the
//! algorithm will switch the pointers \b pOutBuffer and \b pInBuffer in the 
//! event that the output ends up in the original input buffer, with the end result
//! that \b pOutBuffer always points to the output.
//
void ICFFT_run32Pt(CFFT_Handle hndCFFT);

//! \brief Initializes the CFFT object
//! \param[in] hndCFFT handle to the CFFT object
//
void CFFT_init64Pt(CFFT_Handle hndCFFT);

//! \brief Runs the Complex FFT routine
//! 
//! \param[in] hndCFFT handle to the CFFT object
//! \attention For bit reverse addressing to work, the input buffer must be aligned
//! to size of the buffer in words (16-bit). For example, the 64 point complex FFT requires
//! an input buffer of size 128 words (16-bit), therefore it must be aligned to a boundary
//! of 128. This can be done by assigning the array to a named section 
//! (buffer1) using compiler pragmas 
//! \code #pragma DATA_SECTION(buffer1Q15,"buffer1") \endcode
//! and then either assigning this memory to the start of a RAM block in the 
//! linker command file or aligning it to a boundary using the align directive
//! \code buffer1 : > RAMLS3, ALIGN = 128, PAGE = 1 \endcode
//! \note The algorithm ping-pongs between the two buffers, i.e. the buffers 
//! pointed to by \b pInBuffer and \b pOutBuffer, at every stage. Depending
//! on the number of stages the output may be in either of the two buffers; the
//! algorithm will switch the pointers \b pOutBuffer and \b pInBuffer in the 
//! event that the output ends up in the original input buffer, with the end result
//! that \b pOutBuffer always points to the output.
//
void CFFT_run64Pt(CFFT_Handle hndCFFT);

//! \brief Runs the Complex Inverse FFT routine
//!
//! Run the forward FFT on the input and rearrange the output as follows:
//! \f[x(0) =  x'(0)\f]
//! \f[x(n) = x'(N-n), n \in \{1,N-1\} \f], where N is the sample size
//!
//! \param[in] hndCFFT handle to the CFFT object
//! \attention For bit reverse addressing to work, the input buffer must be aligned
//! to size of the buffer in words (16-bit). For example, the 64 point complex FFT requires
//! an input buffer of size 128 words (16-bit), therefore it must be aligned to a boundary
//! of 128. This can be done by assigning the array to a named section
//! (buffer1) using compiler pragmas
//! \code #pragma DATA_SECTION(buffer1Q15,"buffer1") \endcode
//! and then either assigning this memory to the start of a RAM block in the
//! linker command file or aligning it to a boundary using the align directive
//! \code buffer1 : > RAMLS3, ALIGN = 128, PAGE = 1 \endcode
//! If the output buffer of the forward FFT becomes the input to the IFFT, then it
//! must be aligned to the same word (16-bit) boundary as well.
//! \note The algorithm ping-pongs between the two buffers, i.e. the buffers 
//! pointed to by \b pInBuffer and \b pOutBuffer, at every stage. Depending
//! on the number of stages the output may be in either of the two buffers; the
//! algorithm will switch the pointers \b pOutBuffer and \b pInBuffer in the 
//! event that the output ends up in the original input buffer, with the end result
//! that \b pOutBuffer always points to the output.
//
void ICFFT_run64Pt(CFFT_Handle hndCFFT);

//! \brief Initializes the CFFT object
//! \param[in] hndCFFT handle to the CFFT object
//
void CFFT_init128Pt(CFFT_Handle hndCFFT);

//! \brief Runs the Complex FFT routine
//! 
//! \param[in] hndCFFT handle to the CFFT object
//! \attention For bit reverse addressing to work, the input buffer must be aligned
//! to size of the buffer in words (16-bit). For example, the 128 point complex FFT requires
//! an input buffer of size 256 words (16-bit), therefore it must be aligned to a boundary
//! of 256. This can be done by assigning the array to a named section 
//! (buffer1) using compiler pragmas 
//! \code #pragma DATA_SECTION(buffer1Q15,"buffer1") \endcode
//! and then either assigning this memory to the start of a RAM block in the 
//! linker command file or aligning it to a boundary using the align directive
//! \code buffer1 : > RAMLS3, ALIGN = 256, PAGE = 1 \endcode
//
void CFFT_run128Pt(CFFT_Handle hndCFFT);

//! \brief Runs the Complex Inverse FFT routine
//!
//! Run the forward FFT on the input and rearrange the output as follows:
//! \f[x(0) =  x'(0)\f]
//! \f[x(n) = x'(N-n), n \in \{1,N-1\} \f], where N is the sample size
//!
//! \param[in] hndCFFT handle to the CFFT object
//! \attention For bit reverse addressing to work, the input buffer must be aligned
//! to size of the buffer in words (16-bit). For example, the 128 point complex FFT requires
//! an input buffer of size 256 words (16-bit), therefore it must be aligned to a boundary
//! of 256. This can be done by assigning the array to a named section
//! (buffer1) using compiler pragmas
//! \code #pragma DATA_SECTION(buffer1Q15,"buffer1") \endcode
//! and then either assigning this memory to the start of a RAM block in the
//! linker command file or aligning it to a boundary using the align directive
//! \code buffer1 : > RAMLS3, ALIGN = 256, PAGE = 1 \endcode
//! If the output buffer of the forward FFT becomes the input to the IFFT, then it
//! must be aligned to the same word (16-bit) boundary as well.
//! \note The algorithm ping-pongs between the two buffers, i.e. the buffers 
//! pointed to by \b pInBuffer and \b pOutBuffer, at every stage. Depending
//! on the number of stages the output may be in either of the two buffers; the
//! algorithm will switch the pointers \b pOutBuffer and \b pInBuffer in the 
//! event that the output ends up in the original input buffer, with the end result
//! that \b pOutBuffer always points to the output.
//
void ICFFT_run128Pt(CFFT_Handle hndCFFT);

//! \brief Initializes the CFFT object
//! \param[in] hndCFFT handle to the CFFT object
//
void CFFT_init256Pt(CFFT_Handle hndCFFT);

//! \brief Runs the Complex FFT routine
//! 
//! \param[in] hndCFFT handle to the CFFT object
//! \attention For bit reverse addressing to work, the input buffer must be aligned
//! to size of the buffer in words (16-bit). For example, the 256 point complex FFT requires
//! an input buffer of size 512 words (16-bit), therefore it must be aligned to a boundary
//! of 512. This can be done by assigning the array to a named section 
//! (buffer1) using compiler pragmas 
//! \code #pragma DATA_SECTION(buffer1Q15,"buffer1") \endcode
//! and then either assigning this memory to the start of a RAM block in the 
//! linker command file or aligning it to a boundary using the align directive
//! \code buffer1 : > RAMLS3, ALIGN = 512, PAGE = 1 \endcode
//! \note The algorithm ping-pongs between the two buffers, i.e. the buffers 
//! pointed to by \b pInBuffer and \b pOutBuffer, at every stage. Depending
//! on the number of stages the output may be in either of the two buffers; the
//! algorithm will switch the pointers \b pOutBuffer and \b pInBuffer in the 
//! event that the output ends up in the original input buffer, with the end result
//! that \b pOutBuffer always points to the output.
//
void CFFT_run256Pt(CFFT_Handle hndCFFT);

//! \brief Runs the Complex Inverse FFT routine
//!
//! Run the forward FFT on the input and rearrange the output as follows:
//! \f[x(0) =  x'(0)\f]
//! \f[x(n) = x'(N-n), n \in \{1,N-1\} \f], where N is the sample size
//!
//! \param[in] hndCFFT handle to the CFFT object
//! \attention For bit reverse addressing to work, the input buffer must be aligned
//! to size of the buffer in words (16-bit). For example, the 256 point complex FFT requires
//! an input buffer of size 512 words (16-bit), therefore it must be aligned to a boundary
//! of 512. This can be done by assigning the array to a named section
//! (buffer1) using compiler pragmas
//! \code #pragma DATA_SECTION(buffer1Q15,"buffer1") \endcode
//! and then either assigning this memory to the start of a RAM block in the
//! linker command file or aligning it to a boundary using the align directive
//! \code buffer1 : > RAMLS3, ALIGN = 512, PAGE = 1 \endcode
//! If the output buffer of the forward FFT becomes the input to the IFFT, then it
//! must be aligned to the same word (16-bit) boundary as well.
//
void ICFFT_run256Pt(CFFT_Handle hndCFFT);

//! \brief Initializes the CFFT object
//! \param[in] hndCFFT handle to the CFFT object
//
void CFFT_init512Pt(CFFT_Handle hndCFFT);

//! \brief Runs the Complex FFT routine
//! 
//! \param[in] hndCFFT handle to the CFFT object
//! \attention For bit reverse addressing to work, the input buffer must be aligned
//! to size of the buffer in words (16-bit). For example, the 512 point complex FFT requires
//! an input buffer of size 1024 words (16-bit), therefore it must be aligned to a boundary
//! of 1024. This can be done by assigning the array to a named section 
//! (buffer1) using compiler pragmas 
//! \code #pragma DATA_SECTION(buffer1Q15,"buffer1") \endcode
//! and then either assigning this memory to the start of a RAM block in the 
//! linker command file or aligning it to a boundary using the align directive
//! \code buffer1 : > RAMGS4, ALIGN = 1024, PAGE = 1 \endcode
//! \note The algorithm ping-pongs between the two buffers, i.e. the buffers 
//! pointed to by \b pInBuffer and \b pOutBuffer, at every stage. Depending
//! on the number of stages the output may be in either of the two buffers; the
//! algorithm will switch the pointers \b pOutBuffer and \b pInBuffer in the 
//! event that the output ends up in the original input buffer, with the end result
//! that \b pOutBuffer always points to the output.
//
void CFFT_run512Pt(CFFT_Handle hndCFFT);

//! \brief Runs the Complex Inverse FFT routine
//!
//! Run the forward FFT on the input and rearrange the output as follows:
//! \f[x(0) =  x'(0)\f]
//! \f[x(n) = x'(N-n), n \in \{1,N-1\} \f], where N is the sample size
//!
//! \param[in] hndCFFT handle to the CFFT object
//! \attention For bit reverse addressing to work, the input buffer must be aligned
//! to size of the buffer in words (16-bit). For example, the 512 point complex FFT requires
//! an input buffer of size 1024 words (16-bit), therefore it must be aligned to a boundary
//! of 1024. This can be done by assigning the array to a named section
//! (buffer1) using compiler pragmas
//! \code #pragma DATA_SECTION(buffer1Q15,"buffer1") \endcode
//! and then either assigning this memory to the start of a RAM block in the
//! linker command file or aligning it to a boundary using the align directive
//! \code buffer1 : > RAMGS4, ALIGN = 1024, PAGE = 1 \endcode
//! If the output buffer of the forward FFT becomes the input to the IFFT, then it
//! must be aligned to the same word (16-bit) boundary as well.
//! \note The algorithm ping-pongs between the two buffers, i.e. the buffers 
//! pointed to by \b pInBuffer and \b pOutBuffer, at every stage. Depending
//! on the number of stages the output may be in either of the two buffers; the
//! algorithm will switch the pointers \b pOutBuffer and \b pInBuffer in the 
//! event that the output ends up in the original input buffer, with the end result
//! that \b pOutBuffer always points to the output.
//
void ICFFT_run512Pt(CFFT_Handle hndCFFT);

//! \brief Initializes the CFFT object
//! \param[in] hndCFFT handle to the CFFT object
//
void CFFT_init1024Pt(CFFT_Handle hndCFFT);

//! \brief Runs the Complex FFT routine
//! 
//! \param[in] hndCFFT handle to the CFFT object
//! \attention For bit reverse addressing to work, the input buffer must be aligned
//! to size of the buffer in words (16-bit). For example, the 1024 point complex FFT requires
//! an input buffer of size 2048 words (16-bit), therefore it must be aligned to a boundary
//! of 2048. This can be done by assigning the array to a named section 
//! (buffer1) using compiler pragmas 
//! \code #pragma DATA_SECTION(buffer1Q15,"buffer1") \endcode
//! and then either assigning this memory to the start of a RAM block in the 
//! linker command file or aligning it to a boundary using the align directive
//! \code buffer1 : > RAMGS4, ALIGN = 2048, PAGE = 1 \endcode
//! \note The algorithm ping-pongs between the two buffers, i.e. the buffers 
//! pointed to by \b pInBuffer and \b pOutBuffer, at every stage. Depending
//! on the number of stages the output may be in either of the two buffers; the
//! algorithm will switch the pointers \b pOutBuffer and \b pInBuffer in the 
//! event that the output ends up in the original input buffer, with the end result
//! that \b pOutBuffer always points to the output.
//
void CFFT_run1024Pt(CFFT_Handle hndCFFT);

//! \brief Runs the Complex Inverse FFT routine
//!
//! Run the forward FFT on the input and rearrange the output as follows:
//! \f[x(0) =  x'(0)\f]
//! \f[x(n) = x'(N-n), n \in \{1,N-1\} \f], where N is the sample size
//!
//! \param[in] hndCFFT handle to the CFFT object
//! \attention For bit reverse addressing to work, the input buffer must be aligned
//! to size of the buffer in words (16-bit). For example, the 1024 point complex FFT requires
//! an input buffer of size 2048 words (16-bit), therefore it must be aligned to a boundary
//! of 2048. This can be done by assigning the array to a named section
//! (buffer1) using compiler pragmas
//! \code #pragma DATA_SECTION(buffer1Q15,"buffer1") \endcode
//! and then either assigning this memory to the start of a RAM block in the
//! linker command file or aligning it to a boundary using the align directive
//! \code buffer1 : > RAMGS4, ALIGN = 2048, PAGE = 1 \endcode
//! If the output buffer of the forward FFT becomes the input to the IFFT, then it
//! must be aligned to the same word (16-bit) boundary as well.
//! \note The algorithm ping-pongs between the two buffers, i.e. the buffers 
//! pointed to by \b pInBuffer and \b pOutBuffer, at every stage. Depending
//! on the number of stages the output may be in either of the two buffers; the
//! algorithm will switch the pointers \b pOutBuffer and \b pInBuffer in the 
//! event that the output ends up in the original input buffer, with the end result
//! that \b pOutBuffer always points to the output.
//
void ICFFT_run1024Pt(CFFT_Handle hndCFFT);

//!
//! \brief Unpack the complex FFT output to get the FFT of two interleaved
//!        real sequences
//!
//! In order to get the FFT of a real N-pt sequences, we treat the input as
//! an N/2 pt complex sequence, take its complex FFT, use the following properties
//! to get the N-pt Fourier transform of the real sequence
//! 
//! \f[ FFT_{n}(k,f) = FFT_{N/2}(k,f_{e}) + e^{\frac{-j2{\pi}k}{N}}FFT_{N/2}(k,f_{o}) \f]
//! 
//! where \f$f_{e}\f$ is the even elements, \f$f_{o}\f$ the odd elements and
//! 
//! \f[ F_{e}(k) = \frac{Z(k) + Z(\frac{N}{2}-k)^{\ast}}{2} \f]
//! \f[ F_{o}(k) = -j\frac{Z(k) - Z(\frac{N}{2}-k)^{\ast}}{2} \f]
//! 
//! We get the first N/2 points of the FFT by combining the above two equations
//! \f[ F(k) = F_{e}(k) + e^{\frac{-j2{\pi}k}{N}}F_{o}(k) \f]
//!
//! \param[in] hndCFFT handle to the CFFT object
//! \note This is an in-place algorithm; the routine writes the output to the input buffer itself
//! \sa http://www.engineeringproductivitytools.com/stuff/T0001/PT10.HTM for the entire
//!  derivation
//
void CFFT_unpack(CFFT_Handle hndCFFT);

//! \brief Pack the input prior to running the inverse complex FFT to get
//!        the real inverse FFT
//!
//! In order to reverse the process of the forward real FFT,
//!
//! \f[ F_{e}(k) = \frac{F(k) + F(\frac{N}{2}-k)^{\ast}}{2} \f]
//! \f[ F_{o}(k) = \frac{F(k) - F(\frac{N}{2}-k)^{\ast}}{2} e^{\frac{j2{\pi}k}{N}} \f]
//!
//! where \f$f_{e}\f$ is the even elements, \f$f_{o}\f$ the odd elements.
//! The array for the IFFT then becomes:
//! \f[ Z(k) = F_{e}(k) + jF_{o}(k), \ k = 0...\frac{N}{2}-1 \f]
//!
//! \param[in] hndCFFT handle to the CFFT object
//! \note
//! - This is an in-place algorithm; the routine writes the output to the input buffer itself
//! - The assumption is that the user will run the packed sequence through
//!   an IFFT sequence i.e. conjugate -> Forward FFT -> conjugate. The packed output
//!   is conjugated in this routine obviating the need for the first conjugate in the
//!   IFFT sequence
//! \sa http://www.engineeringproductivitytools.com/stuff/T0001/PT10.HTM for the entire
//!  derivation
//
void CFFT_pack(CFFT_Handle hndCFFT);

//!
//! \brief Take the complex conjugate of the entries in an array of complex
//! numbers
//!
//! \param pBuffer Pointer to the buffer of complex data to be conjugated
//! \param[in] size Size of the buffer (multiple of 2 32-bits locations)
//
void CFFT_conjugate(void *pBuffer, uint16_t size);

#ifdef __cplusplus
}
#endif // extern "C"

// @} //ingroup

#endif //end of _VCU2_FFT_H_ definition

// End of File
