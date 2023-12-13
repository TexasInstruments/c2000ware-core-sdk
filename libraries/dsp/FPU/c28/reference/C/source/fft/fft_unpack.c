//#############################################################################
//! \file   reference/C/source/$FILENAME$
//! \brief  Unpack
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
DSP_FILENUM(25)

#define ONE_O_TWO   ((fsize_t)0.5)
//*****************************************************************************
// FFT_unpack()
//*****************************************************************************
void FFT_unpack(FFTHandle hnd)
{
    // Locals
    uint16_t i, k, N_o_two_m_k, N_m_k;
    
    uint16_t in_sep, p_sin, p_cos;
    uint16_t curr_stage, n_groups, n_bflys, bfly;
    fsize_t Zr, Zi, Zcr, Zci, IA, RS, RA, IS, S, C;
    fsize_t *tf          = FFT_getTwiddlePtr(hnd);
    fsize_t *Z           = FFT_getIOBufferPtr(hnd);
    fsize_t *F           = FFT_getIOBuffer2Ptr(hnd);
    uint16_t N           = FFT_getSize(hnd);
    uint16_t tblsize     = FFT_getTfTblSize(hnd);
    uint16_t tf_sep      = tblsize/4U;
    uint16_t skipfactor  = tblsize/N;

    FFT_setSkipFactor(hnd, skipfactor);
    // p_cos, p_sin are not used in the calculation 
    // for F(0) and F(N/2) since its a trivial calculation 
    // but it is necessary to update these pointers before 
    // running the F(1) calculation
    p_sin = 0U;
    p_cos = p_sin + tf_sep;
#ifdef _DEBUG
    printf("******************Unpack******************\n");   
    printf("N =%4d, tf_sep=%4d, skip factor=%4d \n",N, tf_sep, skipfactor);
    printf("******************************************\n");
#endif  

    // F(0)
    F[0]   = Z[0] + Z[1]; // Re(Z(0)) + Im(Z(0))
    F[1]   = (fsize_t)0.0;
#ifdef _DEBUG
        printf("k=   0, F(k)=%10.7f+j%10.7f\n", F[0], F[1]);
#endif
    // F(N/2)
    i     = N/2;
    k     = i*2U; 
    F[k]  = Z[0] - Z[1]; // F(N/2) = Re(Z(0))-Im(Z(0))
    F[k+1]= (fsize_t)0.0;
#ifdef _DEBUG
    printf("k=%4d, F(k)=%10.7f+j%10.7f\n", N/2, F[k], F[k+1]);
#endif
    // setup twiddle pointer for next butterfly
    p_sin = p_sin + skipfactor;
    p_cos = p_sin + tf_sep;
    
    // F(k) for k = 1 to N/2 - 1 and k = N/2+1 to N-1
    for (i = 1U; i <= (N/2 - 1U); i++)
    {
        // Convert index to account for size of complex data
        k           = i*2U;
        N_o_two_m_k = (N/2 - i)*2U; 
        N_m_k       = (N - i)*2U;
        Zr     = Z[k];
        Zi     = Z[k+1];
        Zcr    = Z[N_o_two_m_k];
        Zci    = Z[N_o_two_m_k + 1];
        S      = -tf[p_sin];
        C      =  tf[p_cos];
        DSP_ASSERT(((C*C+S*S)-1.0) < 1e-14);
        IA     = Zi + Zci; // Imaginarys add
        RS     = Zr - Zcr; // Reals subtract
        RA     = Zr + Zcr; // Reals add
        IS     = Zi - Zci; // Imaginarys subtract
        F[k]   = ONE_O_TWO*(RA + C*IA + S*RS);
        F[k+1] = ONE_O_TWO*(IS - C*RS + S*IA);
        // F(N-k) = F*(k)
        F[N_m_k]     =  F[k];
        F[N_m_k + 1] = -F[k+1];
#ifdef _DEBUG
        printf("k=%4d, Zr+jZi=%10.7f+j%10.7f, "
               "Zcr+jZci=%10.7f+j%10.7f, "
               "F(k)=%10.7f+j%10.7f, "
               "F(N-k)=%10.7f+j%10.7f\n",         
                i, Zr, Zi, Zcr, Zci, F[k], F[k+1], F[N_m_k], F[N_m_k+1]);
#endif
        // setup twiddle pointer for next butterfly
        p_sin = p_sin + skipfactor;
        p_cos = p_sin + tf_sep;
    }

}

// End of File
