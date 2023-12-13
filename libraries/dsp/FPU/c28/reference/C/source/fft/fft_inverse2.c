//#############################################################################
//! \file   reference/C/source/$FILENAME$
//! \brief  Inverse Complex Fast Fourier Transform (Radix 2)
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
DSP_FILENUM(32)

#define ONE_O_TWO   ((fsize_t)0.5)
//*****************************************************************************
// FFT_runICFFT2()
//*****************************************************************************
void FFT_runICFFT2(FFTHandle hnd)
{
    // Locals
    uint16_t i, k, p, r;
    uint16_t p_top, p_bot, p_sin, p_cos, in_sep;
    
    uint16_t curr_stage, n_groups, n_bflys, bfly;
    fsize_t Ar, Ai, Br, Bi, Cr, Ci, Dr, Di, S, C;
    fsize_t *tf          = FFT_getTwiddlePtr(hnd);
    fsize_t *io          = FFT_getIOBufferPtr(hnd);
    uint16_t N           = FFT_getSize(hnd);
    uint16_t n_stages    = log2(N);
    uint16_t tblsize     = FFT_getTfTblSize(hnd);
    uint16_t tf_sep      = tblsize/4U;
    uint16_t skipfactor  = tblsize/N; //The max skipfactor for the last stage
    FFT_setNStages(hnd, n_stages);
    FFT_setSkipFactor(hnd, skipfactor);
    
    //-------------------------------------------------------------------------
    // Stage 1
    //-------------------------------------------------------------------------
    curr_stage  = 1U;
    n_groups    = N >> curr_stage;
    n_bflys     = (N >> 1U)/n_groups;
    in_sep      = (1U << (curr_stage - 1U)) * 2U;
    p_top       = 0U;
    p_bot       = p_top + in_sep;
    bfly        = 0U;
#ifdef _DEBUG
    printf("******************Stage #%4d******************\n", curr_stage);   
    printf("n_groups=%4d, n_bflys=%4d, in_sep=%4d \n", n_groups, n_bflys,
           in_sep);
    printf("***********************************************\n");
#endif    
    // Iterate through the groups
    for (i = 0U; i < n_groups; i++)
    {
        Ar          = io[p_top];
        Ai          = io[p_top+1];
        Br          = io[p_bot];
        Bi          = io[p_bot+1];
        Cr          = ONE_O_TWO * ( Ar+Br);
        Ci          = ONE_O_TWO * (-Ai-Bi);
        Dr          = ONE_O_TWO * ( Ar-Br);
        Di          = ONE_O_TWO * (-Ai+Bi);
        io[p_top]   = Cr;
        io[p_top+1] = Ci;
        io[p_bot]   = Dr;
        io[p_bot+1] = Di;
        bfly++;
        // setup p_top and p_bot for next group
        p_top = p_top + in_sep + 2U;
        p_bot = p_top + in_sep;
#ifdef _DEBUG
        printf("Bfly #%4d, Ar+jAi=%10.7f+j%10.7f, "
               "Br+jBi=%10.7f+j%10.7f, "
               "Cr+jCi=%10.7f+j%10.7f, "
               "Dr+jDi=%10.7f+j%10.7f\n",         
                bfly, Ar, Ai, Br, Bi, Cr, Ci, Dr, Di);
#endif
    }
    
    //-------------------------------------------------------------------------
    // Stage 2
    //-------------------------------------------------------------------------
    curr_stage  = 2U;
    n_groups    = N >> curr_stage;
    n_bflys     = (N >> 1U)/n_groups;
    in_sep      = (1U << (curr_stage - 1U)) * 2U;
    p_top       = 0U;
    p_bot       = p_top + in_sep;
    bfly        = 0U;
#ifdef _DEBUG
    printf("******************Stage #%4d******************\n", curr_stage);   
    printf("n_groups=%4d, n_bflys=%4d, in_sep=%4d \n", n_groups, n_bflys,
           in_sep);
    printf("***********************************************\n");
#endif 
    // Iterate through the groups
    for (i = 0U; i < n_groups; i++)
    {
        //first bfly
        Ar          = io[p_top];
        Ai          = io[p_top+1];
        Br          = io[p_bot];
        Bi          = io[p_bot+1];
        Cr          = ONE_O_TWO * (Ar+Br);
        Ci          = ONE_O_TWO * (Ai+Bi);
        Dr          = ONE_O_TWO * (Ar-Br);
        Di          = ONE_O_TWO * (Ai-Bi);
        io[p_top]   = Cr;
        io[p_top+1] = Ci;
        io[p_bot]   = Dr;
        io[p_bot+1] = Di;
        bfly++;
#ifdef _DEBUG
        printf("Bfly #%4d, Ar+jAi=%10.7f+j%10.7f, "
               "Br+jBi=%10.7f+j%10.7f, "
               "Cr+jCi=%10.7f+j%10.7f, "
               "Dr+jDi=%10.7f+j%10.7f\n",         
                bfly, Ar, Ai, Br, Bi, Cr, Ci, Dr, Di);
#endif
        // second bfly
        p_top       = p_top + 2U;
        p_bot       = p_top + in_sep;
        Ar          = io[p_top];
        Ai          = io[p_top+1];
        Br          = io[p_bot];
        Bi          = io[p_bot+1];
        Cr          = ONE_O_TWO * (Ar+Bi);
        Ci          = ONE_O_TWO * (Ai-Br);
        Dr          = ONE_O_TWO * (Ar-Bi);
        Di          = ONE_O_TWO * (Ai+Br);
        io[p_top]   = Cr;
        io[p_top+1] = Ci;
        io[p_bot]   = Dr;
        io[p_bot+1] = Di;
        bfly++;
        // setup p_top and p_bot for next group
        p_top = p_top + in_sep + 2U;
        p_bot = p_top + in_sep;
#ifdef _DEBUG
        printf("Bfly #%4d, Ar+jAi=%10.7f+j%10.7f, "
               "Br+jBi=%10.7f+j%10.7f, "
               "Cr+jCi=%10.7f+j%10.7f, "
               "Dr+jDi=%10.7f+j%10.7f\n",         
                bfly, Ar, Ai, Br, Bi, Cr, Ci, Dr, Di);
#endif
    }
    //-------------------------------------------------------------------------
    // Stage 3 to n_stages - 1
    //-------------------------------------------------------------------------
    for (k = 3U; k <= (n_stages - 1U); k++)
    {
        curr_stage  = curr_stage + 1U;
        n_groups    = N >> curr_stage;
        n_bflys     = (N >> 1U)/n_groups;
        in_sep      = (1U << (curr_stage - 1U)) * 2U;
        skipfactor  = tblsize/(1U << curr_stage);
        // Setup data and twiddle pointers
        p_top       = 0U;
        p_bot       = p_top + in_sep;
        p_sin       = 0U;
        p_cos       = p_sin + tf_sep;
        bfly        = 0U;
#ifdef _DEBUG
        printf("******************Stage #%4d******************\n", curr_stage);   
        printf("n_groups=%4d, n_bflys=%4d, in_sep=%4d \n", n_groups, n_bflys,
               in_sep);
        printf("***********************************************\n");
#endif 
        // Iterate through the groups
        for (p = 0U; p < n_groups; p++)
        {
            // iterate through the butterflies
            for (r = 0U; r < n_bflys; r++)
            {
                Ar    = io[p_top];
                Ai    = io[p_top+1];
                Br    = io[p_bot];
                Bi    = io[p_bot+1];
                S     = -tf[p_sin];
                C     =  tf[p_cos];
                DSP_ASSERT(((C*C+S*S)-1.0) < 1e-14);
                Cr    = ONE_O_TWO * (Ar+C*Br-S*Bi);
                Ci    = ONE_O_TWO * (Ai+C*Bi+S*Br);
                Dr    = ONE_O_TWO * (Ar-C*Br+S*Bi);
                Di    = ONE_O_TWO * (Ai-C*Bi-S*Br);
                io[p_top]   = Cr;
                io[p_top+1] = Ci;
                io[p_bot]   = Dr;
                io[p_bot+1] = Di;
                bfly++;
                // setup p_top and p_bot for next butterfly
                p_top = p_top + 2U;
                p_bot = p_top + in_sep;
                // setup twiddle pointer for next butterfly
                p_sin = p_sin + skipfactor;
                p_cos = p_sin + tf_sep;
#ifdef _DEBUG
                printf("Bfly #%4d, Ar+jAi=%10.7f+j%10.7f, "
                       "Br+jBi=%10.7f+j%10.7f, "
                       "C+jS=%10.7f+j%10.7f, "
                       "Cr+jCi=%10.7f+j%10.7f, "
                       "Dr+jDi=%10.7f+j%10.7f\n",         
                        bfly, Ar, Ai, Br, Bi, C, S, Cr, Ci, Dr, Di);
#endif
            }
            // setup p_top and p_bot for next group
            p_top = p_top + in_sep;
            p_bot = p_top + in_sep;
            // reset twiddle pointers for next group
            p_sin = 0U;
            p_cos = p_sin + tf_sep;
        }
    }
    //-------------------------------------------------------------------------
    // Stage n_stages
    //-------------------------------------------------------------------------
    curr_stage  = curr_stage + 1U;
    n_groups    = N >> curr_stage;
    n_bflys     = (N >> 1U)/n_groups;
    in_sep      = (1U << (curr_stage - 1U)) * 2U;
    skipfactor  = tblsize/(1U << curr_stage);
    // Setup data and twiddle pointers
    p_top       = 0U;
    p_bot       = p_top + in_sep;
    p_sin       = 0U;
    p_cos       = p_sin + tf_sep;
    bfly        = 0U;
#ifdef _DEBUG
    printf("******************Stage #%4d******************\n", curr_stage);   
    printf("n_groups=%4d, n_bflys=%4d, in_sep=%4d \n", n_groups, n_bflys,
           in_sep);
    printf("***********************************************\n");
#endif 
    // Iterate through the groups
    for (p = 0U; p < n_groups; p++)
    {
        // iterate through the butterflies
        for (r = 0U; r < n_bflys; r++)
        {
            Ar    = io[p_top];
            Ai    = io[p_top+1];
            Br    = io[p_bot];
            Bi    = io[p_bot+1];
            S     = -tf[p_sin];
            C     =  tf[p_cos];
            DSP_ASSERT(((C*C+S*S)-1.0) < 1e-14);
            Cr    = ONE_O_TWO * ( Ar+C*Br-S*Bi);
            Ci    = ONE_O_TWO * (-Ai-C*Bi-S*Br);
            Dr    = ONE_O_TWO * ( Ar-C*Br+S*Bi);
            Di    = ONE_O_TWO * (-Ai+C*Bi+S*Br);
            io[p_top]   = Cr;
            io[p_top+1] = Ci;
            io[p_bot]   = Dr;
            io[p_bot+1] = Di;
            bfly++;
            // setup p_top and p_bot for next butterfly
            p_top = p_top + 2U;
            p_bot = p_top + in_sep;
            // setup twiddle pointer for next butterfly
            p_sin = p_sin + skipfactor;
            p_cos = p_sin + tf_sep;
#ifdef _DEBUG
            printf("Bfly #%4d, Ar+jAi=%10.7f+j%10.7f, "
                   "Br+jBi=%10.7f+j%10.7f, "
                   "C+jS=%10.7f+j%10.7f, "
                   "Cr+jCi=%10.7f+j%10.7f, "
                   "Dr+jDi=%10.7f+j%10.7f\n",         
                    bfly, Ar, Ai, Br, Bi, C, S, Cr, Ci, Dr, Di);
#endif
        }
        // setup p_top and p_bot for next group
        p_top = p_top + in_sep;
        p_bot = p_top + in_sep;
        // reset twiddle pointers for next group
        p_sin = 0U;
        p_cos = p_sin + tf_sep;
    }
    
}

// End of File
