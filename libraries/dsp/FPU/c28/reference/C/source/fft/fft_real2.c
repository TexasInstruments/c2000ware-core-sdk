//#############################################################################
//! \file   reference/C/source/$FILENAME$
//! \brief  Real Fast Fourier Transform (Radix 2)
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
#include <string.h>

//*****************************************************************************
// defines
//*****************************************************************************
DSP_FILENUM(37)

//*****************************************************************************
// FFT_runRFFT2()
//*****************************************************************************
void FFT_runRFFT2(FFTHandle hnd)
{
    // Locals
    uint16_t i, k, p, r, l, X1X3offset, X2X4offset;
    uint16_t p_top, p_bot, p_sin, p_cos, p_temp, grp_sep;
    uint16_t p_X1, p_X2, p_X3, p_X4;
    
    uint16_t curr_stage, n_groups, n_bflys, bfly, grp, n_calcs;
    fsize_t D0, D1, D2, D3, D4, D5, D6, D7, S, C;
    fsize_t I0, I1, I2, I3, I4, I5, I6, I7;
    fsize_t X1, X2, X3, X4, Y1, Y2, Y3, Y4;
    fsize_t D0_hh, D1_hh, D2_hh, D3_hh, D4_hh, I1_hh, I2_hh, I3_hh;
    
    fsize_t *tf          = FFT_getTwiddlePtr(hnd);
    fsize_t *temp        = FFT_getIOBufferPtr(hnd);
    fsize_t *io          = FFT_getIOBuffer2Ptr(hnd);
    uint16_t N           = FFT_getSize(hnd);
    memcpy(io, temp, N*sizeof(fsize_t)); // copy input to the output array
    uint16_t n_stages    = log2(N);
    uint16_t tblsize     = FFT_getTfTblSize(hnd);
    FFT_setNStages(hnd, n_stages);
    FFT_setSkipFactor(hnd, 0U);
    
    //-------------------------------------------------------------------------
    // Stage 1, 2 and 3
    //-------------------------------------------------------------------------
    //
    // NOTE: Instead of referring to the real part as Rn we choose Dn to avoid 
    // confusing them with the Rn FPU registers
    //
    //                 Stage 1    Stage 2
    // ---D0+jI0-o----*--D0`+jI0`--o--------*--D0^+jI0^--------o---------------*---D0^^+jI0^^--->
    //            \  /              \      /                    \             /    
    //             \/                \    /                      \           /     
    //             /\                 \  /                        \         /      
    //            /  \                 \/                          \       /       
    // ---D1+jI1-o----*--D1`+jI1`--o---/\---*--D1^+jI1^--------o----\-----/----*---D1^^+jI1^^--->
    //                              \ /  \ /                    \    \   /    /    
    //                               \    \                      \    \ /    /     
    //                              / \  / \                      \    /    /      
    // ---D2+jI2-o----*--D2`+jI2`--o---\/---*--D2^+jI2^--------o---\--/-\--/---*---D2^^+jI2^^--->
    //            \  /                 /\                       \   \/   \/   /    
    //             \/                 /  \                       \  /\   /\  /     
    //             /\                /    \                       \/  \ /  \/      
    //            /  \              /      \                      /\   \   /\      
    // ---D3+jI3-o----*--D3`+jI3`--o--------*--D3^+jI3^--------o-/--\-/-\-/--\-*---D3^^+jI3^^--->
    //                                                          /    \   \    \    
    // ---D4+jI4-o----*--D4`+jI4`--o--------*--D4^+jI4^--W8,0--o-\--/-(-1)\--/-*---D4^^+jI4^^--->
    //            \  /              \      /                      \/   \   \/      
    //             \/                \    /                       /\  / \  /\      
    //             /\                 \  /                       /  \/   \/  \     
    //            /  \                 \/                       /   /\   /\   \    
    // ---D5+jI5-o----*--D5`+jI5`--o---/\---*--D5^+jI5^--W8,1--o---/--(-1)-\---*---D5^^+jI5^^--->
    //                              \ /  \ /                      /    \    \      
    //                               \    \                      /    / \    \     
    //                              / \  / \                    /    /   \    \    
    // ---D6+jI6-o----*--D6`+jI6`--o---\/---*--D6^+jI6^--W8,2--o----/-(-1)\----*---D6^^+jI6^^--->
    //            \  /                 /\                          /       \       
    //             \/                 /  \                        /         \      
    //             /\                /    \                      /           \     
    //            /  \              /      \                    /             \    
    // ---D7+jI7-o----*--D7`+jI7`--o--------*--D7^+jI7^--W8,3--o------(-1)-----*---D7^^+jI7^^--->
    //
    // Each twiddle WN,k is of the form (e^-j2*pi*k/N) or (C-jS)
    //
    //   +-----+---------+-----+-----------------+-----+----------------+
    //   |   Stage 1     |   Stage 2             |   Stage 3            |
    //   +-----+---------+-----+-----------------+-----+----------------+
    //   | D0` |  D0+D1  | D0^ | (D0+D1)+(D2+D3) | D0^^| D0^+C*D4^+S*I1^|
    //   | I0` |  I0+I1  | I0^ | (I0+I1)+(I2+I3) | I0^^| I0^+C*I4^-S*D1^|
    //   | D1` |  D0-D1  | D1^ | (D0-D1)+(I2-I3) | D1^^| D1^+C*D5^+S*I5^|
    //   | I1` |  I0-I1  | I1^ | (I0-I1)-(D2-D3) | I1^^| I1^+C*I5^-S*D5^|
    //   | D2` |  D2+D3  | D2^ | (D0+D1)-(D2+D3) | D2^^| D2^+C*D6^+S*I6^|
    //   | I2` |  I2+I3  | I2^ | (I0+I1)-(I2+I3) | I2^^| I2^+C*I6^-S*D6^|
    //   | D3` |  D2-D3  | D3^ | (D0-D1)-(I2-I3) | D3^^| D3^+C*D7^+S*I7^|
    //   | I3` |  I2-I3  | I3^ | (I0-I1)+(D2-D3) | I3^^| I3^+C*I7^-S*D7^|
    //   | D4` |  D4+D5  | D4^ | (D4+D5)+(D6+D7) | D4^^| D0^-C*D4^-S*I1^|
    //   | I4` |  I4+I5  | I4^ | (I4+I5)+(I6+I7) | I4^^| I0^-C*I4^+S*D1^|
    //   | D5` |  D4-D5  | D5^ | (D4-D5)+(I6-I7) | D5^^| D1^-C*D5^-S*I5^|
    //   | I5` |  I4-I5  | I5^ | (I4-I5)-(D6-D7) | I5^^| I1^-C*I5^+S*D5^|
    //   | D6` |  D6+D7  | D6^ | (D4+D5)-(D6+D7) | D6^^| D2^-C*D6^-S*I6^|
    //   | I6` |  I6+I7  | I6^ | (I4+I5)-(I6+I7) | I6^^| I2^-C*I6^+S*D6^|
    //   | D7` |  D6-D7  | D7^ | (D4-D5)-(I6-I7) | D7^^| D3^-C*D7^-S*I7^|
    //   | I7` |  I6-I7  | I7^ | (I4-I5)+(D6-D7) | I7^^| I3^-C*I7^+S*D7^|
    //   +-----+---------+-----+-----------------+-----+----------------+
    //
    // Since the input is real only, we set all the 'In' to 0
    //
    //   +-----+------------------------------------------------------------------------+
    //   |   Stage 3  Simplifications                                                   |
    //   +-----+----------------+----------------+--------------------------------+-----+
    //   | D0^^| D0^+C*D4^+S*I1^|C=1,S=0         |(D0+D1)+(D2+D3)+(D4+D5)+(D6+D7) | (A) |
    //   | I0^^| I0^+C*I4^-S*D1^|C=1,S=0         |0                               |  -  |
    //   | D1^^| D1^+C*D5^+S*I5^|C=S=0.707       |(D0-D1)+|C|*((D4-D5)+(D7-D6))   | (B) |
    //   | I1^^| I1^+C*I5^-S*D5^|C=S=0.707       ||C|*((D7-D6)-(D4-D5))+(D3-D2)   | (H) |
    //   | D2^^| D2^+C*D6^+S*I6^|C=0,S=1         |(D0+D1)-(D2+D3)                 | (C) |
    //   | I2^^| I2^+C*I6^-S*D6^|C=0,S=1         |(D6+D7)-(D4+D5)                 | (G) |
    //   | D3^^| D3^+C*D7^+S*I7^|C=-0.707,S=0.707|(D0-D1)-|C|*((D4-D5)+(D7-D6))   | (D) |
    //   | I3^^| I3^+C*I7^-S*D7^|C=-0.707,S=0.707||C|*((D7-D6)-(D4-D5))-(D3-D2)   | (F) |
    //   | D4^^| D0^-C*D4^-S*I1^|C=1,S=0         |(D0+D1)+(D2+D3)-(D4+D5)-(D6+D7) | (E) |
    //   | I4^^| I0^-C*I4^+S*D1^|C=1,S=0         |0                               |  -  |
    //   | D5^^| D1^-C*D5^-S*I5^|C=S=0.707       |(D0-D1)-|C|*((D4-D5)+(D7-D6))   | (D) |
    //   | I5^^| I1^-C*I5^+S*D5^|C=S=0.707       |-(|C|*((D7-D6)-(D4-D5))-(D3-D2))|-(F) |
    //   | D6^^| D2^-C*D6^-S*I6^|C=0,S=1         |(D0+D1)-(D2+D3)                 | (C) |
    //   | I6^^| I2^-C*I6^+S*D6^|C=0,S=1         |-((D6+D7)-(D4+D5))              |-(G) |
    //   | D7^^| D3^-C*D7^-S*I7^|C=-0.707,S=0.707|(D0-D1)+|C|*((D4-D5)+(D7-D6))   | (B) |
    //   | I7^^| I3^-C*I7^+S*D7^|C=-0.707,S=0.707|-(|C|*((D7-D6)-(D4-D5))+(D3-D2))|-(H) |
    //   +-----+----------------+----------------+--------------------------------+-----+
    //
    // - We only store the unique non-zero entries A, B, C, D, E, F, G, H in 
    //   that  order
    // - Notice the output is complex conjugate about the midpoint, i.e.
    //   F(k) = F(N-k)*
    //   For example, F(1) = (B)+j(H) F(8-1)=F(7)=(B)+j(-(H))
    //                F(2) = (C)+j(G) F(8-2)=F(6)=(C)+j(-(G))
    //   This is true for all subsequent stages of the FFT. Thus, for any given
    //   FFT stage n <= log2(N), there are 
    //      - N/(2^(n-1)) butterflies
    //      - 2^n outputs per butterfly
    //   We save only the first half (2^(n-1)+1)of the outputs per butterfly 
    //   since the latter half is conjugate symmetric and not required in the 
    //   computation of the next stage
    //-------------------------------------------------------------------------
    curr_stage  = 3U;
    n_groups    = N >> curr_stage;
    n_bflys     = (N >> 1U)/n_groups;
    grp_sep      = (1U << (curr_stage - 1U)) * 2U;
    p_top       = 0U;
    // p_bot       = p_top + grp_sep;
    bfly        = 0U;
#ifdef _DEBUG
    printf("**************Stage #1, 2, 3**************\n");
#endif    
    C   = tf[0U];             S = tf[1U];
    // Iterate through the groups
    for (i = 0U; i < n_groups; i++, bfly=bfly+4U)
    {
        D0  = io[p_top + 0U];    D1 = io[p_top + 1U];
        D2  = io[p_top + 2U];    D3 = io[p_top + 3U];
        D4  = io[p_top + 4U];    D5 = io[p_top + 5U];
        D6  = io[p_top + 6U];    D7 = io[p_top + 7U];

        D0_hh = (D0+D1)+(D2+D3)+(D4+D5)+(D6+D7); // (A)
        D1_hh = (D0-D1)+(C*((D4-D5)+(D7-D6)));   // (B)
        I1_hh = (C*((D7-D6)-(D4-D5)))+(D3-D2);   // (H)
        D2_hh = (D0+D1)-(D2+D3);                 // (C)
        I2_hh = (D6+D7)-(D4+D5);                 // (G)
        D3_hh = (D0-D1)-(C*((D4-D5)+(D7-D6)));   // (D)
        I3_hh = (C*((D7-D6)-(D4-D5)))-(D3-D2);   // (F)
        D4_hh = (D0+D1)+(D2+D3)-(D4+D5)-(D6+D7); // (E)

        io[p_top + 0U]  = D0_hh;    io[p_top + 1U]   = D1_hh;
        io[p_top + 2U]  = D2_hh;    io[p_top + 3U]   = D3_hh;
        io[p_top + 4U]  = D4_hh;    io[p_top + 5U]   = I3_hh;
        io[p_top + 6U]  = I2_hh;    io[p_top + 7U]   = I1_hh;
        
        // setup p_top and p_bot for next group
        p_top = p_top + grp_sep;
        //p_bot = p_top + grp_sep;
#ifdef _DEBUG
        printf("Group #%4d, \n"
               "D0=%10.7f, D1=%10.7f,\n"
               "D2=%10.7f, D3=%10.7f,\n"
               "D4=%10.7f, I3=%10.7f,\n"
               "I2=%10.7f, I1=%10.7f \n",
                i, D0_hh, D1_hh, D2_hh, D3_hh, D4_hh, I3_hh, I2_hh, I1_hh);
#endif
    }
    
    //-------------------------------------------------------------------------
    // Stage 4 to n_stages
    //
    // NOTE: Instead of referring to the real part as Rn we choose Dn to avoid 
    // confusing them with the Rn FPU registers
    //
    // Shown below is the butterfly group from stage 4. The calculations here
    // are identical for future stages.
    //
    // D0-----------------o---------------o----(D0+D5)-------------------------------->
    //                     \             /                                        
    // D1+jI1-------------o-\-----------/-o----(D1+(D6*C1+I6*S1))+j((I6*C1-D6*S1)+I1)->
    //                     \ \         / /  
    // D2+jI2-------------o-\-\-------/-/-o----(D2+(D7*C2+I7*S2))+j((I7*C2-D7*S2)+I2)->
    //                     \ \ \     / / /  
    // D3+jI3-------------o-\-\-\---/-/-/-o----(D3+(D8*C3+I8*S3))+j((I8*C3-D8*S3)+I3)->
    //                     \ \ \ \ / / / /  
    // D4-----------------o-\-\-\-X-/-/-/-o----(D4-jD9)------------------------------->
    //                     \ \ \ X X / / /  
    // D3-jI3-------------o-\-\-X-X-X-/-/-o----(D3-(D8*C3+I8*S3))+j((I8*C3-D8*S3)-I3)->
    //                     \ \ X X X X / /  
    // D2-jI2-------------o-\-X-X-X-X-X-/-o----(D2-(D7*C2+I7*S2))+j((I7*C2-D7*S2)-I2)->
    //                     \ X X X X X X /  
    // D1-jI1-------------o-X-X-X-X-X-X-X-o----(D1-(D6*C1+I6*S1))+j((I6*C1-D6*S1)-I1)->
    //                     X X X X X X X X  
    // D5------(  1-j0 )--o-X-X-X-X-X-X-X-o----(D0-D5)-------------------------------->
    //                     / X X X X X X \  
    // D6+jI6--( C1-jS1)--o-/-X-X-X-X-X-\-o----(D1-(D6*C1+I6*S1))-j((I6*C1-D6*S1)-I1)->
    //                     / / X X X X \ \  
    // D7+jI7--( C2-jS2)--o-/-/-X-X-X-\-\-o----(D2-(D7*C2+I7*S2))-j((I7*C2-D7*S2)-I2)->
    //                     / / / X X \ \ \  
    // D8+jI8--( C3-jS3)--o-/-/-/-X-\-\-\-o----(D3-(D8*C3+I8*S3))-j((I8*C3-D8*S3)-I3)->
    //                     / / / / \ \ \ \  
    // D9------(  0-1j )--o-/-/-/---\-\-\-o----(D4+jD9)------------------------------->
    //                     / / /     \ \ \  
    // D8-jI8--(-C3-jS3)--o-/-/-------\-\-o----(D3+(D8*C3+I8*S3))-j((I8*C3-D8*S3)+I3)->
    //                     / /         \ \  
    // D7-jI7--(-C2-jS2)--o-/-----------\-o----(D2+(D7*C2+I7*S2))-j((I7*C2-D7*S2)+I2)->
    //                     /             \  
    // D6-jI6--(-C1-jS1)--o---------------o----(D1+(D6*C1+I6*S1))-j((I6*C1-D6*S1)+I1)->
    //
    // Notice we need only save the first 9 complex outputs, the rest are 
    // complex conjugates about the 8th entry. 
    //
    // The inputs from stage 3 were stored in this order
    // +--+-----------+--------------------+--+------------+
    // |IN| Ptr (Xn)  |OUT                 |Yn|Pointer dir |
    // +--+-----------+--------------------+--+------------+
    // |D0|<- X1ptr ->| D0+D5              |Y1|      *     |
    // |D1|<- X1ptr ->| D1+(D6*COS+I6*SIN) |Y1|      |     |
    // |D2|<- X1ptr ->| D2+(D7*COS+I7*SIN) |Y1|      |     |
    // |D3|<- X1ptr ->| D3+(D8*COS+I8*SIN) |Y1|      v     |
    // |D4|           | D4 (pass through)  |- |            |
    // |I3|<- X2ptr ->| D3-(D8*COS+I8*SIN) |Y2|      ^     |
    // |I2|<- X2ptr ->| D2-(D7*COS+I7*SIN) |Y2|      |     |
    // |I1|<- X2ptr ->| D1-(D6*COS+I6*SIN) |Y2|      *     |
    // +--+-----------+--------------------+--+------------+
    // |D5|<- X3ptr ->| D0-D5              |Y3|      *     |
    // |D6|<- X3ptr ->| (I6*COS-D6*SIN)-I1 |Y3|      |     |
    // |D7|<- X3ptr ->| (I7*COS-D7*SIN)-I2 |Y3|      |     |
    // |D8|<- X3ptr ->| (I8*COS-D8*SIN)-I3 |Y3|      v     |
    // |D9|<- X4ptr ->|  -D9 (negate, save)|Y4|      ^     |
    // |I8|<- X4ptr ->| (I8*COS-D8*SIN)+I3 |Y4|      |     |
    // |I7|<- X4ptr ->| (I7*COS-D7*SIN)+I2 |Y4|      |     |
    // |I6|<- X4ptr ->| (I6*COS-D6*SIN)+I1 |Y4|      *     |
    // +--+-----------+--------------------+--+------------+
    // Outer Loop: IDX_M
    //      Stage 4: M = 1 to FFTSize/16
    //      Stage 5: M = 1 to FFTSize/32
    //      Stage 6: M = 1 to FFTSize/64  etc..
    // 
    // Calculate the following M times (Xn the input, Yn the output):
    // 
    //      X1 = *X1ptr;
    //      X3 = *X3ptr;
    //      *X1ptr++ = Y1 = (X1 + X3)
    //      *X3ptr++ = Y3 = (X1 - X3)
    //      for(j=1; j <= r; j ++)
    //      {
    //         X1       = *X1ptr;
    //         X2       = *X2ptr;
    //         X3       = *X3ptr;
    //         X4       = *X4ptr;
    //         COS      = *COSptr++;
    //         SIN      = *COSptr++;
    //         *X1ptr++ = Y1 = X1 + (X3*COS + X4*SIN);        (A)
    //         *X2ptr-- = Y2 = X1 - (X3*COS + X4*SIN);        (B)
    //         *X3ptr++ = Y3 = (X4*COS - X3*SIN) - X2;        (C)
    //         *X4ptr-- = Y4 = (X4*COS - X3*SIN) + X2;        (D)
    //      }
    //      *X4ptr = Y4 = -X4 (*X4ptr)
    //-------------------------------------------------------------------------
    // Setup data and twiddle pointers
    p_top       = 0U;
    //p_bot       = p_top + grp_sep;
    // Initialize the pointers
    p_X1  = 0U;  p_X2 = 0U;
    p_X3  = 0U;  p_X4 = 0U;
    p_cos = 0U;
    X1X3offset = 8U;
    X2X4offset = 8U;
    for (k = 4U; k <= n_stages; k++)
    {
        curr_stage  = curr_stage + 1U;
        n_groups    = N >> curr_stage;
        n_bflys     = (N >> 1U)/n_groups;
        n_calcs     = (n_bflys >> 1U) - 1U;
        grp_sep     = (1U << (curr_stage - 1U)) * 2U;
        //skipfactor  = tblsize/(1U << curr_stage);
        bfly        = 0U;
        // Initialize the pointers
        p_X1  = 0U;       p_X3  = p_X1 + X1X3offset;
        p_X2 = p_X3 - 1;  p_X4  = p_X2 + X2X4offset;
        p_cos       = p_cos + (1U << (curr_stage-2));
        p_sin       = p_cos + 1U;
        p_temp      = p_cos;
#ifdef _DEBUG
        printf("******************Stage #%4d******************\n", curr_stage);   
        printf("n_groups=%4d, n_bflys=%4d, grp_sep=%4d \n", n_groups, n_bflys,
               grp_sep);
        printf("***********************************************\n");
#endif 
        
        // Iterate through the groups
        for (p = 0U; p < n_groups; p++)
        {
            X1 = io[p_top + p_X1];  X3 = io[p_top + p_X3];
            Y1 = X1 + X3; 
            Y3 = X1 - X3; 
            io[p_top + p_X1] = Y1; p_X1++;
            io[p_top + p_X3] = Y3; p_X3++;
            
//#ifdef _DEBUG // this debug block shows output in calculation order
//            printf("Group #%4d, \n"
//                   "\tY1=%10.7f, Y3=%10.7f,\n", p, Y1, Y3);
//#endif  
            for(r = 1; r <= n_calcs; r++)
            {
               X1   = io[p_top + p_X1];
               X2   = io[p_top + p_X2];
               X3   = io[p_top + p_X3];
               X4   = io[p_top + p_X4];
               C    = tf[p_cos]; p_cos = p_cos + 2U;
               S    = tf[p_sin]; p_sin = p_sin + 2U;
               
               Y1   = X1 + (X3*C + X4*S);
               Y2   = X1 - (X3*C + X4*S);
               Y3   = (X4*C - X3*S) - X2;
               Y4   = (X4*C - X3*S) + X2;
//#ifdef _DEBUG // this debug block shows output in calculation order
//            printf("\tInner Calculation %d\n"
//                   "\tY1=%10.7f, Y2=%10.7f,\n"
//                   "\tY3=%10.7f, Y4=%10.7f,\n", r, Y1, Y2, Y3, Y4);
//#endif                 
               io[p_top + p_X1] = Y1;  p_X1++;
               io[p_top + p_X2] = Y2;  p_X2--;
               io[p_top + p_X3] = Y3;  p_X3++;
               io[p_top + p_X4] = Y4;  p_X4--;
               
            }
            Y4 = -io[p_top + p_X4];
            io[p_top + p_X4] = Y4;
//#ifdef _DEBUG // this debug block shows output in calculation order
//            printf("\tY4=%10.7f\n", Y4);
//#endif  
#ifdef _DEBUG // this debug block shows output in save order
            printf("Group #%4d output, \n", p);
            for(i = 0U; i < (n_bflys * 2U); i++)
            {
                printf("\t%10.7f\n", io[p_top + i]);
            }
            
#endif  
            // setup pointers for the next group
            p_top = p_top + grp_sep;
            //p_bot = p_top + grp_sep;
            p_X1  = 0U;       p_X3  = p_X1 + X1X3offset;
            p_X2 = p_X3 - 1;  p_X4  = p_X2 + X2X4offset;
            // reset twiddle pointers for next group
            p_cos = p_temp;
            p_sin = p_cos + 1U;
        }
        // update the pointers
        p_top = 0U;

        // update the offsets
        X1X3offset = X1X3offset*2U;
        X2X4offset = X2X4offset*2U;
    }
}

// End of File
