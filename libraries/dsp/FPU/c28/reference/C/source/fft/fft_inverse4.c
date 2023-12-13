//#############################################################################
//! \file   reference/C/source/$FILENAME$
//! \brief  Inverse Complex Fast Fourier Transform (Radix 4)
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
DSP_FILENUM(36)

#define ONE_O_TWO   ((fsize_t)0.5)
//*****************************************************************************
// FFT_runICFFT4()
//*****************************************************************************
void FFT_runICFFT4(FFTHandle hnd)
{
    // Locals
    uint16_t i, j, k;
    uint16_t p_top, p_bot, p_top_n1, p_bot_n1, p_top_n2, p_bot_n2;
    uint16_t p_sin, p_cos, p_sin_n1, p_sin_n2, p_cos_n1, p_cos_n2;
    uint16_t in_sep, in_sep_n1, in_sep_n2;
    uint16_t grp_sep;
    
    uint16_t curr_stage, n_groups, n_bflys, bfly;
    fsize_t Ar, Ai, Br, Bi, Cr, Ci, Dr, Di;
    fsize_t Er, Ei, Fr, Fi, Gr, Gi, Hr, Hi;
    fsize_t Ir, Ii, Jr, Ji, Kr, Ki, Lr, Li;
    fsize_t S1, C1, S2, C2, S, C;
    fsize_t *tf             = FFT_getTwiddlePtr(hnd);
    fsize_t *io             = FFT_getIOBufferPtr(hnd);
    uint16_t N              = FFT_getSize(hnd);
    uint16_t n_stages       = log2(N);
    uint16_t n_combo_stages = (n_stages >> 1) << 1;
    uint16_t tblsize        = FFT_getTfTblSize(hnd);
    uint16_t tf_sep         = tblsize >> 2;
    uint16_t skipfactor     = tblsize/N;//The max skipfactor for the last stage
    uint16_t skipfactor_n1, skipfactor_n2;
    FFT_setNStages(hnd, n_stages);
    FFT_setSkipFactor(hnd, skipfactor);
    
    //*************************************************************************
    // Stages 1 & 2
    //*************************************************************************
    //- The twiddle factors have the following relationship with each other
    //  +---------------------------------+----------------------------------+
    //  | Stage N | P |  cos(1) - j sin(1)| W(N,0)..W(N,N/4 -1)              |
    //  |         | Q | -cos(1) + j sin(1)| W(N,N/2)..W(N,N/2 + N/4 -1)      |
    //  | Stage N1| R |  cos(2) - j sin(2)| W(N1,0)..W(N1,N1/4-1)            |
    //  |         | S | -sin(2) - j cos(2)| W(N1,N1/4)..W(N1,N1/2-1)         |
    //  |         | T | -cos(2) + j sin(2)| W(N1,N1/2)..W(N1/N1/2+N1/4-1)    |
    //  |         | U |  sin(2) + j cos(2)| W(N1,3N1/4)..W(N1,N1-1)          |
    //  +---------------------------------+----------------------------------+
    //         
    //
    //                           Stage N                  Stage N+1
    //p_top_n1 --Ar+jAi---------o----*---Er+jEi----------o--------*--Ir+jIi--->
    //                    |      \ (P)               |    \      /       
    //                 in_sep_n1  \/                 |     \   (R)        
    //                    |       /\             in_sep_n2  \  /         
    //                    V      /  \                |       \/          
    //p_bot_n1 --Br+jBi---------o-(Q)*---Fr+jFi------|---o---/\---*--Jr+jJi--->
    //                                               |    \ /  \(S)          
    //                                               |     \    \        
    //                                               V    / \  / \      
    //p_top_n2 --Cr+jCi---------o----*---Gr+jGi----------o---\(T)-*--Kr+jKi--->
    //                     |     \ (P)                       /\              
    //                     |      \/                        /  \         
    //                     |      /\                       /    \        
    //                     |     /  \                     /      \      
    //p_bot_n2 --Dr+jDi----|----o-(Q)*---Hr+jHi----------o----(U)-*--Lr+jLi--->
    //                     |
    //                  grp_sep
    //                     |
    //                     |
    //                     |
    //                     V
    //*************************************************************************
    curr_stage = 2;
    n_groups     = N>>curr_stage;     //# of groups of butteflys
    n_bflys      = 1<<(curr_stage-2U);//# of radix 4 butterflies in a group
    //Set the input datum seperation for a given stage, the +1 accounts for 
    // the size of complex being 2^1
    in_sep_n1    = 1<<(curr_stage - 2 + 1);
    in_sep_n2    = 1<<(curr_stage - 1 + 1);
    grp_sep      = in_sep_n1<<1;
    // Setup data pointers
    p_top_n1 = 0U;
    p_bot_n1 = p_top_n1 + in_sep_n1;
    p_top_n2 = p_top_n1 + in_sep_n2;
    p_bot_n2 = p_top_n2 + in_sep_n1;
#ifdef _DEBUG
        printf("\n**********Stages #%4d and %4d*****************\n", 
               curr_stage - 1U, curr_stage);   
        printf("n_groups=%4d, n_bflys=%4d\n", n_groups, n_bflys);
        printf("***********************************************\n");
#endif 
    //Iterate through the groups
    for (i = 0U; i < n_groups; i++)
    {
        Ar              = io[p_top_n1];
        Ai              = io[p_top_n1+1];
        Br              = io[p_bot_n1];
        Bi              = io[p_bot_n1+1];
        Cr              = io[p_top_n2];
        Ci              = io[p_top_n2+1];
        Dr              = io[p_bot_n2];
        Di              = io[p_bot_n2+1];
        Er              = ONE_O_TWO*( Ar+Br);
        Ei              = ONE_O_TWO*(-Ai-Bi);
        Fr              = ONE_O_TWO*( Ar-Br);
        Fi              = ONE_O_TWO*(-Ai+Bi);
        Gr              = ONE_O_TWO*( Cr+Dr);
        Gi              = ONE_O_TWO*(-Ci-Di);
        Hr              = ONE_O_TWO*( Cr-Dr);
        Hi              = ONE_O_TWO*(-Ci+Di);
        Ir              = ONE_O_TWO*( Er+Gr);
        Ii              = ONE_O_TWO*( Ei+Gi);
        Jr              = ONE_O_TWO*( Fr+Hi);
        Ji              = ONE_O_TWO*( Fi-Hr);
        Kr              = ONE_O_TWO*( Er-Gr);
        Ki              = ONE_O_TWO*( Ei-Gi);
        Lr              = ONE_O_TWO*( Fr-Hi);
        Li              = ONE_O_TWO*( Fi+Hr);
#ifdef _DEBUG
        printf("Butterfly #%4d\n"
               "Ar+jAi=%10.7f+j%10.7f, Br+jBi=%10.7f+j%10.7f,\n"
               "Cr+jCi=%10.7f+j%10.7f, Dr+jDi=%10.7f+j%10.7f,\n"
               "Er+jEi=%10.7f+j%10.7f, Fr+jFi=%10.7f+j%10.7f,\n"
               "Gr+jGi=%10.7f+j%10.7f, Hr+jHi=%10.7f+j%10.7f,\n"
               "Ir+jIi=%10.7f+j%10.7f, Jr+jJi=%10.7f+j%10.7f,\n"
               "Kr+jKi=%10.7f+j%10.7f, Lr+jLi=%10.7f+j%10.7f,\n",
               i, Ar, Ai, Br, Bi, Cr, Ci, Dr, Di, Er, Ei, Fr, Fi, Gr, Gi,
               Hr, Hi, Ir, Ii, Jr, Ji, Kr, Ki, Lr, Li
               );
#endif // _DEBUG
        io[p_top_n1]    = Ir;
        io[p_top_n1+1]  = Ii;
        io[p_bot_n1]    = Jr;
        io[p_bot_n1+1]  = Ji;
        io[p_top_n2]    = Kr;
        io[p_top_n2+1]  = Ki;
        io[p_bot_n2]    = Lr;
        io[p_bot_n2+1]  = Li;
        // setup p_top and p_bot for next group
        p_top_n1        = p_top_n2 + grp_sep;
        p_bot_n1        = p_top_n1 + in_sep_n1;
        p_top_n2        = p_top_n1 + in_sep_n2;
        p_bot_n2        = p_top_n2 + in_sep_n1;
    }

    //*************************************************************************
    // Combined Stages (n1, n2) to floor(log2(N)/2)*2                          
    //*************************************************************************
    //- The twiddle factors have the following relationship with each other
    //  +---------------------------------+----------------------------------+
    //  | Stage N | P |  cos(1) - j sin(1)| W(N,0)..W(N,N/4 -1)              |
    //  |         | Q | -cos(1) + j sin(1)| W(N,N/2)..W(N,N/2 + N/4 -1)      |
    //  | Stage N1| R |  cos(2) - j sin(2)| W(N1,0)..W(N1,N1/4-1)            |
    //  |         | S | -sin(2) - j cos(2)| W(N1,N1/4)..W(N1,N1/2-1)         |
    //  |         | T | -cos(2) + j sin(2)| W(N1,N1/2)..W(N1/N1/2+N1/4-1)    |
    //  |         | U |  sin(2) + j cos(2)| W(N1,3N1/4)..W(N1,N1-1)          |
    //  +---------------------------------+----------------------------------+
    //         
    //
    //                          Stage N                  Stage N+1
    //p_top_n1 --Ar+jAi---------o----*---Er+jEi----------o--------*--Ir+jIi--->
    //                    |      \ (P)               |    \      /       
    //                 in_sep_n1  \/                 |     \   (R)        
    //                    |       /\             in_sep_n2  \  /         
    //                    V      /  \                |       \/          
    //p_bot_n1 --Br+jBi---------o-(Q)*---Fr+jFi------|---o---/\---*--Jr+jJi--->
    //                                               |    \ /  \(S)          
    //                                               |     \    \        
    //                                               V    / \  / \      
    //p_top_n2 --Cr+jCi---------o----*---Gr+jGi----------o---\(T)-*--Kr+jKi--->
    //                     |     \ (P)                       /\              
    //                     |      \/                        /  \         
    //                     |      /\                       /    \        
    //                     |     /  \                     /      \      
    //p_bot_n2 --Dr+jDi----|----o-(Q)*---Hr+jHi----------o----(U)-*--Lr+jLi--->
    //                     |
    //                  grp_sep
    //                     |
    //                     |
    //                     |
    //                     V
    //*************************************************************************
    // The non-trivial stages 3 till log2(N)
    for (i = 3U; i <= n_combo_stages; i = i + 2U)
    {
        curr_stage = i + 1U;
        n_groups   = N>>curr_stage;     //# of groups of butteflys
        n_bflys    = 1<<(curr_stage-2U);//# of radix 4 butterflies in a group
        //Set the input datum and twiddle factor seperation for a
        //given stage; the skip factor determines the gap between the
        //twiddle factors for a lookup table of size tblsize
        //Set the input datum and group seperation for a given stage
        in_sep_n1       = 1<<(curr_stage - 2 + 1);
        in_sep_n2       = 1<<(curr_stage - 1 + 1);
        grp_sep         = in_sep_n1<<1;
        skipfactor_n1   = tblsize >> (curr_stage-1);
        skipfactor_n2   = tblsize >> curr_stage;
        tf_sep          = tblsize >> 2;
        // Setup data and twiddle pointers
        p_top_n1 = 0U;
        p_bot_n1 = p_top_n1 + in_sep_n1;
        p_top_n2 = p_top_n1 + in_sep_n2;
        p_bot_n2 = p_top_n2 + in_sep_n1;
        
        p_sin_n1 = 0U;
        p_cos_n1 = p_sin_n1 + tf_sep;
        p_sin_n2 = 0U;
        p_cos_n2 = p_sin_n2 + tf_sep;
        
#ifdef _DEBUG
        printf("\n**********Stages #%4d and %4d*****************\n", 
               curr_stage - 1U, curr_stage);   
        printf("n_groups=%4d, n_bflys=%4d\n", n_groups, n_bflys);
        printf("***********************************************\n");
#endif 
        //Iterate through the groups
        for (j = 0U; j < n_groups; j++)
        {
            // iterate through the butterflies
            for(k = 0U; k < n_bflys; k++)
            {
                Ar              = io[p_top_n1];
                Ai              = io[p_top_n1+1];
                Br              = io[p_bot_n1];
                Bi              = io[p_bot_n1+1];
                Cr              = io[p_top_n2];
                Ci              = io[p_top_n2+1];
                Dr              = io[p_bot_n2];
                Di              = io[p_bot_n2+1];
                S1              = tf[p_sin_n1];
                C1              = tf[p_cos_n1];
                S2              = tf[p_sin_n2];
                C2              = tf[p_cos_n2];
                DSP_ASSERT(((C1*C1+S1*S1)-1.0) < 1e-14 && 
                           ((C2*C2+S2*S2)-1.0) < 1e-14);
                Er              =  ONE_O_TWO*(Ar+(Br*C1+Bi*S1));
                Ei              =  ONE_O_TWO*(Ai+(Bi*C1-Br*S1));
                Fr              =  ONE_O_TWO*(Ar-(Br*C1+Bi*S1));
                Fi              =  ONE_O_TWO*(Ai-(Bi*C1-Br*S1));
                Gr              =  ONE_O_TWO*(Cr+(Dr*C1+Di*S1));
                Gi              =  ONE_O_TWO*(Ci+(Di*C1-Dr*S1));
                Hr              =  ONE_O_TWO*(Cr-(Dr*C1+Di*S1));
                Hi              =  ONE_O_TWO*(Ci-(Di*C1-Dr*S1));
                Ir              =  ONE_O_TWO*(Er+(Gr*C2+Gi*S2));
                Ii              =  ONE_O_TWO*(Ei+(Gi*C2-Gr*S2));
                Jr              =  ONE_O_TWO*(Fr-(Hr*S2-Hi*C2));
                Ji              =  ONE_O_TWO*(Fi-(Hi*S2+Hr*C2));
                Kr              =  ONE_O_TWO*(Er-(Gr*C2+Gi*S2));
                Ki              =  ONE_O_TWO*(Ei-(Gi*C2-Gr*S2));
                Lr              =  ONE_O_TWO*(Fr+(Hr*S2-Hi*C2));
                Li              =  ONE_O_TWO*(Fi+(Hr*C2+Hi*S2));
                if(curr_stage == n_stages)
                {
                    Ii          = -Ii;
                    Ji          = -Ji;
                    Ki          = -Ki;
                    Li          = -Li;
                }
#ifdef _DEBUG
                printf("Group=%4d, Ingroup Bfly=%4d, Cumulative Bfly=%4d\n"
                  "Ar+jAi=%10.7f+j%10.7f, Br+jBi=%10.7f+j%10.7f,\n"
                  "Cr+jCi=%10.7f+j%10.7f, Dr+jDi=%10.7f+j%10.7f,\n"
                  "Er+jEi=%10.7f+j%10.7f, Fr+jFi=%10.7f+j%10.7f,\n"
                  "Gr+jGi=%10.7f+j%10.7f, Hr+jHi=%10.7f+j%10.7f,\n"
                  "Ir+jIi=%10.7f+j%10.7f, Jr+jJi=%10.7f+j%10.7f,\n"
                  "Kr+jKi=%10.7f+j%10.7f, Lr+jLi=%10.7f+j%10.7f,\n",
                  j, k, (j*n_bflys)+k, Ar, Ai, Br, Bi, Cr, Ci, Dr, Di, Er, Ei, 
                  Fr, Fi, Gr, Gi, Hr, Hi, Ir, Ii, Jr, Ji, Kr, Ki, Lr, Li
                  );
#endif // _DEBUG
                io[p_top_n1]    = Ir;
                io[p_top_n1+1]  = Ii;
                io[p_bot_n1]    = Jr;
                io[p_bot_n1+1]  = Ji;
                io[p_top_n2]    = Kr;
                io[p_top_n2+1]  = Ki;
                io[p_bot_n2]    = Lr;
                io[p_bot_n2+1]  = Li;
                // setup p_top and p_bot for next butterfly
                p_top_n1        = p_top_n1 + 2U;
                p_bot_n1        = p_top_n1 + in_sep_n1;
                p_top_n2        = p_top_n1 + in_sep_n2;
                p_bot_n2        = p_top_n2 + in_sep_n1;
                // setup twiddle pointer for next butterfly
                p_sin_n1        = p_sin_n1 + skipfactor_n1;
                p_cos_n1        = p_sin_n1 + tf_sep;
                p_sin_n2        = p_sin_n2 + skipfactor_n2;
                p_cos_n2        = p_sin_n2 + tf_sep;
            }
            // setup p_top and p_bot for next group
            p_top_n1    = p_bot_n2;
            p_bot_n1    = p_top_n1 + in_sep_n1;
            p_top_n2    = p_top_n1 + in_sep_n2;
            p_bot_n2    = p_top_n2 + in_sep_n1;
            // reset twiddle pointers for next group
            p_sin_n1    = 0U;
            p_cos_n1    = p_sin_n1 + tf_sep;
            p_sin_n2    = 0U;
            p_cos_n2    = p_sin_n2 + tf_sep;
        }
    }

    if((n_stages - n_combo_stages) == 1U)
    {
    //*************************************************************************
    // Possible last single stage log2(N)                                      
    //*************************************************************************
        curr_stage = curr_stage + 1U;
        n_groups   = N>>curr_stage;     //# of groups of butteflys
        n_bflys    = 1<<(curr_stage-1U);//# of radix 2 butterflies in a group
        
        // Set the input datum and twiddle factor seperation for a
        // given stage; the skip factor determines the gap between the
        // twiddle factors for a lookup table of size tblsize
        // Set the input datum and group seperation for a given stage
        in_sep      = (1<<(curr_stage - 1U)) * 2U;
        skipfactor  = tblsize >> curr_stage;
        // Setup data and twiddle pointers
        p_top       = 0U;
        p_bot       = p_top + in_sep;
        p_sin       = 0U;
        p_cos       = p_sin + tf_sep;
#ifdef _DEBUG
        printf("******************Stage #%4d******************\n", curr_stage);   
        printf("n_groups=%4d, n_bflys=%4d\n", n_groups, n_bflys);
        printf("***********************************************\n");
#endif 
        // Iterate through the groups
        for (i = 0U; i < n_groups; i++)
        {
            // iterate through the butterflies
            for (j = 0U; j < n_bflys; j++)
            {
                Ar    = io[p_top];
                Ai    = io[p_top+1];
                Br    = io[p_bot];
                Bi    = io[p_bot+1];
                S     = -tf[p_sin];
                C     =  tf[p_cos];
                DSP_ASSERT(((C*C+S*S)-1.0) < 1e-14);
                Cr    = ONE_O_TWO*( Ar+C*Br-S*Bi);
                Ci    = ONE_O_TWO*(-Ai-C*Bi-S*Br);
                Dr    = ONE_O_TWO*( Ar-C*Br+S*Bi);
                Di    = ONE_O_TWO*(-Ai+C*Bi+S*Br);
                io[p_top]   = Cr;
                io[p_top+1] = Ci;
                io[p_bot]   = Dr;
                io[p_bot+1] = Di;
                // setup p_top and p_bot for next butterfly
                p_top = p_top + 2U;
                p_bot = p_top + in_sep;
                // setup twiddle pointer for next butterfly
                p_sin = p_sin + skipfactor;
                p_cos = p_sin + tf_sep;
#ifdef _DEBUG
                printf("Bfly #%4d, \nAr+jAi=%10.7f+j%10.7f, "
                       "Br+jBi=%10.7f+j%10.7f, "
                       "C+jS=%10.7f+j%10.7f, \n"
                       "Cr+jCi=%10.7f+j%10.7f, "
                       "Dr+jDi=%10.7f+j%10.7f\n",         
                        (i*n_bflys)+j, Ar, Ai, Br, Bi, C, S, Cr, Ci, Dr, Di);
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
}

// End of File
