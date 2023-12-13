//#############################################################################
//! FILE: cla_cfft.h
//!
//! TITLE: Prototypes and definitions for Complex FFT on CLA
//
//
///#############################################################################
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

#ifndef _CLA_CFFT_H_
#define _CLA_CFFT_H_

//
// Includes
//

//!
//! \defgroup CLA_DSP_FFT Fast Fourier Transform (CLA)

//!
//! \ingroup CLA_DSP_FFT
// @{

#ifdef __cplusplus
extern "C" {
#endif

//
// Defines
//

//
// Typedefs
//


//
// Globals
//

//! \brief CLA twiddle factors
//!
extern const float *cla_twiddleFactors;

//! \brief CLA bit reversal tables
//!
extern const float *cla_bitReversalTable;

//
// Function prototypes
//

//! \brief Runs the Complex FFT routine (1024 points)
//! 
//! \attention 
//! -# This is an in-place algorithm
//! -# The input/output buffer must be aligned to a 12-bit address, usually the
//!   starting address of one of the CLA data RAMs
//! -# The complex data has real-first ordering i.e. the real part occupies the lower 
//!   double word
//! -# This function is not re-entrant as it uses global variable to store temporary
//!   values. It also expects the FFT buffer to be global (to both the C28 and CLA)
//!   and to be named \b "IOBuffer". If the user desires to change the name, the macro
//!   IOBUFFER must be altered in the source assembly to reflect the new name and the
//!   code rebuilt
//!
//! \return FFT of the input in the I/O buffer
//
extern void CLA_CFFT_run1024Pt();

//! \brief Runs the Complex FFT routine (512 points)
//!
//! \attention
//! -# This is an in-place algorithm
//! -# The input/output buffer must be aligned to a 12-bit address, usually the
//!   starting address of one of the CLA data RAMs
//! -# The complex data has real-first ordering i.e. the real part occupies the lower
//!   double word
//! -# This function is not re-entrant as it uses global variable to store temporary
//!   values. It also expects the FFT buffer to be global (to both the C28 and CLA)
//!   and to be named \b "IOBuffer". If the user desires to change the name, the macro
//!   IOBUFFER must be altered in the source assembly to reflect the new name and the
//!   code rebuilt
//!
//! \return FFT of the input in the I/O buffer
//
extern void CLA_CFFT_run512Pt();
extern void CLA_CFFT_run256Pt();

//!
//! \brief Unpack the 512-point complex FFT output to get the FFT of a 1024 point
//!         real sequence
//!
//! In order to get the FFT of a real N-point sequence, we treat the input as
//! an N/2-point complex sequence, take its complex FFT, use the following
//! properties to get the N-pt Fourier transform of the real sequence
//!
//! \f[
//! FFT_{n}(k,f) = FFT_{N/2}(k,f_{e})+e^{\frac{-j2{\pi}k}{N}}FFT_{N/2}(k,f_{o})
//! \f]
//!
//! where \f$f_{e}\f$ is the even elements, \f$f_{o}\f$ the odd elements,
//! k = 0 to \f$\frac{N}{2}-1\f$ and
//!
//! \f[ F_{e}(k) = \frac{Z(k) + Z(\frac{N}{2}-k)^{\ast}}{2} \f]
//! \f[ F_{o}(k) = -j\frac{Z(k) - Z(\frac{N}{2}-k)^{\ast}}{2} \f]
//!
//! We get the first N/2 points of the FFT by combining the above two equations
//! \f[ F(k) = F_{e}(k) + e^{\frac{-j2{\pi}k}{N}}F_{o}(k) \f]
//!
//! \attention
//! -# This is an off-place algorithm
//! -# Since this function follows an FFT the input buffer must have been 
//!   aligned to a 12-bit address, usually the starting address of one of the 
//!   CLA data RAMs
//! -# The complex data has real-first ordering i.e. the real part occupies
//!    the lower double word
//! -# This function expects the FFT buffers to be global (to both 
//!    the C28 and CLA) and to be named "IOBuffer" and "IOBuffer2" respectively.
//!    If the user desires to  change the name, the macros I_BUFFER and O_BUFFER
//!    must be altered in the source assembly to reflect the new name and the 
//!    code rebuilt
//! -# In the loops the code does two extra reads beyond the end of the
//!    twiddle factor table. Ensure that atleast 4 words after the twiddle
//!    factor table are within CLA accessible data RAM. If using the tables in
//!    Data ROM this is not an issue as the bit reversal tables follow the
//!    twiddle table and you end up reading the first two entries of that
//!    table instead
//! \sa http://www.engineeringproductivitytools.com/stuff/T0001/PT10.HTM for
//! the entire derivation
//
extern void CLA_CFFT_unpack512Pt();
extern void CLA_CFFT_unpack256Pt();

#ifdef __cplusplus
}
#endif // extern "C"

// @} //ingroup

#endif //end of _CLA_CFFT_H_ definition
