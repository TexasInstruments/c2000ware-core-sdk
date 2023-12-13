//#############################################################################
//! \file   reference/C/source/$FILENAME$
//! \brief  Inverse Real Fast Fourier Transform
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
// the includes
//*****************************************************************************
#include "fft.h"
#include <math.h>

//*****************************************************************************
// defines
//*****************************************************************************
DSP_FILENUM(34)

//*****************************************************************************
// FFT_runIRFFT()
//*****************************************************************************
void FFT_runIRFFT(FFTHandle hnd)
{    
    // Locals
    uint16_t  N;
    fsize_t *temp;
    
    // Run the pack function
    FFT_pack(hnd);
    
    // The output of the pack is in the io2 buffer, the inverse complex FFTHandle
    // expects its input in the io buffer, we exchange the pointers
    temp = FFT_getIOBufferPtr(hnd);
    FFT_setIOBufferPtr(hnd, FFT_getIOBuffer2Ptr(hnd));
    FFT_setIOBuffer2Ptr(hnd, temp);

    // bit reverse the input - you do not need to set the size to N/2 
    // for the bitreverse operation, it will query the FFT type and do
    // the right thing
    hnd->bitrev(hnd);
    // run an N/2 point inverse complex FFT on the packed 
    // data
    N = FFT_getSize(hnd);
    FFT_setSize(hnd, N/2);
    if(FFT_getType(hnd) == REAL_RADIX_2)
    {
        FFT_runICFFT2(hnd);
    }
    else if (FFT_getType(hnd) == REAL_RADIX_4)
    {
        FFT_runICFFT4(hnd);
    }
    else
    {
        DSP_ASSERT(0U); // FFT Type is undefined
    }

    // Set the size back to its original
    FFT_setSize(hnd, N);

}

// End of File
