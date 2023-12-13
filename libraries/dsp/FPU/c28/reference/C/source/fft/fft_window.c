//#############################################################################
//! \file   reference/C/source/$FILENAME$
//! \brief  Fast Fourier Transform Windowing
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
DSP_FILENUM(29)

//*****************************************************************************
// FFT_applyWindow()
//*****************************************************************************
void FFT_applyWindow(FFTHandle hnd)
{    
    // Locals
    uint16_t i, j, k;
    uint16_t N   = FFT_getSize(hnd);
    fsize_t *win = FFT_getWindowTblPtr(hnd);
    fsize_t *io  = FFT_getIOBufferPtr(hnd);
    fsize_t t_r, t_i, w;
    
    if((FFT_getType(hnd) == COMPLEX_RADIX_2) ||
       (FFT_getType(hnd) == COMPLEX_RADIX_4))
    {
        for(i = 0U, j = i, k =j+1; i < (N >> 1); i++, j += 2U, k += 2U)
        {
            t_r   = io[j];
            t_i   = io[k];
            w     = *win;
            io[j] = io[j] * (*win);
            io[k] = io[k] * (*win++);
#ifdef _DEBUG
            printf("i=%4d, io[i]=%10.7f+j%10.7f," 
                   " win=%10.7f, out=(%10.7f+j%10.7f)\n",
                    i, t_r, t_i, w, io[j], io[k]);
#endif
        }
        for(i = (N >> 1), j = N, k =j+1; i < N; i++, j += 2U, k += 2U)
        {
            t_r   = io[j];
            t_i   = io[k];
            io[j] = io[j] * (*--win);
            io[k] = io[k] * (*win);
            w     = *win;
#ifdef _DEBUG
            printf("i=%4d, io[i]=%10.7f+j%10.7f,"
                   " win=%10.7f, out=(%10.7f+j%10.7f)\n",
                    i, t_r, t_i, w, io[j], io[k]);
#endif
        }
    }
    else if ((FFT_getType(hnd) == REAL_RADIX_2) ||
             (FFT_getType(hnd) == REAL_RADIX_4))
    {
        for(i = 0U; i < (N >> 1); i++)
        {
            t_r   = io[i];
            w     = *win;
            io[i] = io[i] * (*win++);
#ifdef _DEBUG
            printf("i=%4d, io[i]=%10.7f, win*io[i]=%10.7f*(%10.7f)\n",
                    i, t_r, w, io[i]);
#endif
        }
        for(i = (N >> 1); i < N; i++)
        {
            t_r   = io[i];
            w     = *win;
            io[i] = io[i] * (*--win);
#ifdef _DEBUG
            printf("i=%4d, io[i]=%10.7f, win*io[i]=%10.7f*(%10.7f)\n",
                    i, t_r, w, io[i]);
#endif
        }
    }
    else
    {
        DSP_ASSERT(0U); //Type is invalid
    }
}

// End of File
