//#############################################################################
//! \file   reference/C/source/$FILENAME$
//! \brief  Fast Fourier Transform Magnitude
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
DSP_FILENUM(27)

//*****************************************************************************
// FFT_getMagnitude()
//*****************************************************************************
void FFT_getMagnitude(FFTHandle hnd)
{    
    // Locals
    uint16_t i,j,k;
    uint16_t N = FFT_getSize(hnd);
    fsize_t *mag = FFT_getMagBufferPtr(hnd);
    fsize_t *io = FFT_getIOBuffer2Ptr(hnd);

    if(FFT_getType(hnd) == ALT_REAL_RADIX_2)
    {
        i = 0U, j = i;
        mag[0] = fabs_t(io[0]);
#ifdef _DEBUG
        printf("i=%4d, io[i]=%10.7f, mag[i]=%10.7f\n",
            i, io[i], mag[i]);
#endif
      
        for(i = 1U, j = N - 1U; i < (N >> 1U); i++, j--)
        {
            mag[i] = sqrt(io[i]*io[i] + io[j]*io[j]);
#ifdef _DEBUG
            printf("i=%4d, io[i]=%10.7f+j%10.7f, mag[i]=%10.7f\n",
                i, io[i], io[j], mag[i]);
#endif
        }
        i = N >> 1U, j = i;
        mag[(N >> 1U)] = fabs_t(io[(N >> 1U)]);
#ifdef _DEBUG
        printf("i=%4d, io[i]=%10.7f, mag[i]=%10.7f\n",
            i, io[i], mag[i]);
#endif
    }
    else
    {
        for(i = 0U, j = 0U, k = 1U; i < N; i++, j += 2, k += 2)
        {
            mag[i] = sqrt(io[j]*io[j] + io[k]*io[k]);
#ifdef _DEBUG
            printf("i=%4d, io[i]=%10.7f+j%10.7f, mag[i]=%10.7f\n",
                i, io[j], io[k], mag[i]);
#endif
        }
    }
}

// End of File
