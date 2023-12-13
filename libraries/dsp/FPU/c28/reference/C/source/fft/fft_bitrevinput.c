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
DSP_FILENUM(31)

//*****************************************************************************
// FFT_bitReverseInput()
//*****************************************************************************
void FFT_bitReverseInput(FFTHandle hnd)
{    
   // Locals
    uint16_t i, bri, j, brj, k, brk;
    uint16_t N     = FFT_getSize(hnd);
    uint16_t nbits;
    fsize_t t_r, t_i;
    fsize_t *io    = FFT_getIOBufferPtr(hnd);
    
#ifdef _DEBUG
    printf("Bit Reversal of array of %d values\n", N);
#endif    
    if((FFT_getType(hnd) == COMPLEX_RADIX_2) ||
       (FFT_getType(hnd) == COMPLEX_RADIX_4) ||
       (FFT_getType(hnd) == ALT_REAL_RADIX_2))
    {
        // Do nothing
    }
    else if ((FFT_getType(hnd) == REAL_RADIX_2) ||
             (FFT_getType(hnd) == REAL_RADIX_4))
    {
        N = N >> 1; // must treat real input as N/2 complex and then bit-rev
    }
    else 
    {
        DSP_ASSERT(0U); //Type is invalid
    }   
    nbits = log2(N);
#ifdef _DEBUG
    printf("Each %d-bit index is reversed \n", nbits);
#endif  

    if(FFT_getType(hnd) == ALT_REAL_RADIX_2)
    {
        for(i = 0U; i < N; i++)
        {
            bri = FFT_bitReverseIndex(i, nbits);
            
            if(i < bri)
            {
                // Exhcange
                t_i       = io[i];
                io[i]     = io[bri];
                io[bri]   = t_i;
#ifdef _DEBUG
            printf("    Reversing i=%4d, br_i=%4d\n", i, bri);
#endif
            }
            else
            {
#ifdef _DEBUG
            printf("Not Reversing i=%4d, br_i=%4d\n", i, bri);
#endif            
            }
        }
    }
    else
    {
        for(i = 0U, j = i, k =j+1; i < N; i++, j += 2U, k += 2U)
        {
            bri = FFT_bitReverseIndex(i, nbits);
            brj = bri << 1; // accounts for the complex size
            brk = brj + 1;        
            
            if(i < bri)
            {
                // Exhcange
                t_r       = io[j];
                t_i       = io[k];
                io[j]     = io[brj];
                io[k]     = io[brk];
                io[brj]   = t_r;
                io[brk]   = t_i;
#ifdef _DEBUG
            printf("    Reversing i=%4d, br_i=%4d\n", j, brj);
#endif
            }
            else
            {
#ifdef _DEBUG
            printf("Not Reversing i=%4d, br_i=%4d\n", j, brj);
#endif            
            }
        }
    }
}

// End of File
