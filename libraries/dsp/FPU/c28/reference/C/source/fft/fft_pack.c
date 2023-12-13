//#############################################################################
//! \file   reference/C/source/$FILENAME$
//! \brief  Pack
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
DSP_FILENUM(33)

#define ONE_O_TWO   ((fsize_t)0.5)
//*****************************************************************************
// FFT_pack()
//*****************************************************************************
void FFT_pack(FFTHandle hnd)
{
    // Locals
    uint16_t i, k, N_o_two_m_k, N_m_k;
    
    uint16_t in_sep, p_sin, p_cos;
    uint16_t curr_stage, n_groups, n_bflys, bfly;
    fsize_t Fr, Fi, Fcr, Fci, IA, RS, RA, IS, S, C;
    fsize_t *tf          = FFT_getTwiddlePtr(hnd);
    fsize_t *F           = FFT_getIOBufferPtr(hnd);
    fsize_t *Z           = FFT_getIOBuffer2Ptr(hnd);
    uint16_t N           = FFT_getSize(hnd);
    uint16_t tblsize     = FFT_getTfTblSize(hnd);
    uint16_t tf_sep      = tblsize/4U;
    uint16_t skipfactor  = tblsize/N;

    FFT_setSkipFactor(hnd, skipfactor);

    p_sin = 0U;
    p_cos = p_sin + tf_sep;
#ifdef _DEBUG
    printf("******************Pack********************\n");   
    printf("N =%4d, tf_sep=%4d, skip factor=%4d \n",N, tf_sep, skipfactor);
    printf("******************************************\n");
#endif  

    // F(k) for k = 0 to N/2 - 1
    for (i = 0U; i <= (N/2 - 1U); i++)
    {
        // Convert index to account for size of complex data
        k           = i*2U;
        N_o_two_m_k = (N/2 - i)*2U; 
        Fr     = F[k];
        Fi     = F[k+1];
        Fcr    = F[N_o_two_m_k];
        Fci    = F[N_o_two_m_k + 1];
        S      =  tf[p_sin];
        C      =  tf[p_cos];
        DSP_ASSERT(((C*C+S*S)-1.0) < 1e-14);
        IA     = Fi + Fci; // Imaginarys add
        RS     = Fr - Fcr; // Reals subtract
        RA     = Fr + Fcr; // Reals add
        IS     = Fi - Fci; // Imaginarys subtract
        Z[k]   = ONE_O_TWO*(RA - C*IA - S*RS);
        Z[k+1] = ONE_O_TWO*(IS + C*RS - S*IA);
#ifdef _DEBUG
        printf("k=%4d, Fr+jFi=%10.7f+j%10.7f, "
               "Fcr+jFci=%10.7f+j%10.7f, "
               "Z(k)=%10.7f+j%10.7f\n",         
                i, Fr, Fi, Fcr, Fci, Z[k], Z[k+1]);
#endif
        // setup twiddle pointer for next butterfly
        p_sin = p_sin + skipfactor;
        p_cos = p_sin + tf_sep;
    }

}

// End of File
