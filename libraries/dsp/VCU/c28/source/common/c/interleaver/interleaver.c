//#############################################################################
//! /file source/reference/C/interleaver/interleaver.c
//!
//! \brief  Interleaver
//  \author Smart Grid Group
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
// includes
//*****************************************************************************
#include "interleaver.h"
//*****************************************************************************
// defines
//*****************************************************************************
#define MAX_NUM_TONES_IN_SYMBOL     72
#define MAX_NUM_ILV_SYMBS			511 // G3 PLC -> FCC band
#define BITS_PER_SYMBOL             3
//*****************************************************************************
// globals
//*****************************************************************************
const uint16_t INTERLEAVER_subCarrierParams[MAX_NUM_TONES_IN_SYMBOL][4] = {
    #include "interleaverSubCarrierParams.h"
};

const uint16_t INTERLEAVER_symbolParams[MAX_NUM_ILV_SYMBS * BITS_PER_SYMBOL][2] = {
    #include "interleaverSymbolParams.h"
};
//*****************************************************************************
// function definitions
//*****************************************************************************

// \brief Finds the interleaver parameters
// 
// \param     hndInterleaver pointer to the interleaver object
// \param[in] n    number of symbols
// \param[in] m    number of sub-carriers
//
void INTERLEAVER_findParams(INTERLEAVER_Handle hndInterleaver, 
                uint16_t n,
                uint16_t m)
{
    // Locals
    int16_t tbl_offset;
    
    hndInterleaver->m_i = INTERLEAVER_subCarrierParams[m - 1][0];
    hndInterleaver->m_j = INTERLEAVER_subCarrierParams[m - 1][1];
    hndInterleaver->a   = INTERLEAVER_subCarrierParams[m - 1][2];
    hndInterleaver->u   = INTERLEAVER_subCarrierParams[m - 1][3];
    hndInterleaver->m   = m;
    hndInterleaver->n   = n;
    // LUT starts from symbol 4 
    tbl_offset = hndInterleaver->n - 4;
    if (tbl_offset < 0){
      tbl_offset = 0;
    }

    hndInterleaver->n_i = INTERLEAVER_symbolParams[tbl_offset][0] >> 8;
    hndInterleaver->n_j = INTERLEAVER_symbolParams[tbl_offset][0] &  0xFF;
    hndInterleaver->b   = INTERLEAVER_symbolParams[tbl_offset][1];
    hndInterleaver->v   = hndInterleaver->b * hndInterleaver->n_i;

    hndInterleaver->offset = 0;
}

// \brief Runs the Interleaver
//
// Generates interleaved bits for data
//
// \param     hndInterleaver pointer to the interleaver object
// \param[in] in_p  pointer to the input buffer
// \param[in] out_p pointer to the output buffer
// \param[in] symb  number of sub-carriers
//
void INTERLEAVER_run(INTERLEAVER_Handle hndInterleaver,
                     uint16_t *in_p, uint16_t *out_p,
                     uint16_t  symb)
{
  uint16_t ii, wordLoc, bitLoc, wordVal;
  uint16_t n, m, i, j, vii, b, v, a, u, muJ, inLoc, offset;
  uint16_t bJmodn;
  uint16_t yy;

  n   = hndInterleaver->n;
  b   = hndInterleaver->b;
  v   = hndInterleaver->v;
  m   = hndInterleaver->m;
  a   = (hndInterleaver->a) << 4;
  u   = hndInterleaver->u;
  offset = hndInterleaver->offset;

  muJ    = (m - ((long)__rpt_subcu((long)u * symb, m, 15) >> 16))<<4;
  bJmodn = n + ((long)__rpt_subcu((long)b * symb, n, 15) >> 16);
  yy     = muJ;
  
  for (ii = 0; ii < m; ii++){//ii is I
    // I=ii, J=symb
    // i = (a*I-u*J)%m = (a*I+m-uJ)%m
    // j = (b*J-v*ii)%n
    // 
    // a*ii+m-uJ < 4096 or 12 bits
    i = ((long)__rpt_subcu((long)yy, m, 11) >> 16);
    yy += a;
    vii = ((long)__rpt_subcu(((long)v * i), n, 15) >> 16);
    // bJmodn+n-vii < 1024 or 10 bits
    j = ((long)__rpt_subcu((bJmodn - vii)<<6, n, 9) >> 16);
    inLoc = i + j * m + offset;   // QPSK and 8PSK could roll over 
    
    // compute the bit location
    wordLoc = inLoc >> 4;
    bitLoc =  inLoc - (wordLoc << 4);
    wordVal = *(in_p+wordLoc);
    // save the bit to the interleaver output buffer
    *out_p++ = (wordVal >> bitLoc) & 0x1;
  }
}

// End of file
