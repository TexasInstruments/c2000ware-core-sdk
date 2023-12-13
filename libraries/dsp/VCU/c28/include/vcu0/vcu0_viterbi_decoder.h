#ifndef _VCU0_VITERBI_DECODER_H_
#define _VCU0_VITERBI_DECODER_H_
//#############################################################################
//! \file include/vcu0/vcu0_viterbi_decoder.h
//!
//! \brief  Viterbi Decoder header file
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
#include "vcu0_types.h"

//!
//! \defgroup VCU0_VITERBI_DECODER Viterbi Decoding (VCU0)

//!
//! \ingroup VCU0_VITERBI_DECODER
// @{

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
// defines
//*****************************************************************************
#define FRAME_LEN 					128
#define CODED_LEN 					(FRAME_LEN << 1)
#define ENCODER_LEN 				7
#define STATES  					64
#define LARGE_NEG_NUMBER 			-8192

#define CNV_DEC_NUM_STATES          (1<<(G3_PHY_CNV_K -1))

/* When no overlap method is used */
/* Viterbi decodes maximum of 256 coded bits in 1 shot */
#define CNV_DEC_MAX_UBITS           128                                                      
#define CNV_DEC_MAX_CBITS           (CNV_DEC_MAX_UBITS << 1)  // CR=1/2

/* When overlap method is used */ 
/* Viterbi decodes in blocks of 128 coded bits */
#define CNV_DEC_BLK_UBITS           64           
#define CNV_DEC_BLK_CBITS           (CNV_DEC_BLK_UBITS << 1)  // CR=1/2
#define CNV_DEC_BLK_CBITS_LOG2      7

#define CNV_DEC_BLK_UWORDS          4                         // 16-bits words
#define CNV_DEC_METRIC_INIT         -16384
#define G3_PHY_CNV_K                7

#define cnvDec(nBits, in_p, out_p, flag) \
        cnvDec_asm(nBits, in_p, out_p, flag)

#define cnvDecInit(nBits) \
        cnvDecInit_asm(nBits)

#define cnvDecMetricRescale() \
        cnvDecMetricRescale_asm()

//*****************************************************************************
// typedefs
//*****************************************************************************

//! Viterbi decode mode enumeration
typedef enum
{
  CNV_DEC_MODE_DEC_ALL   = 0,  //!< Decodes all output bits
  CNV_DEC_MODE_OVLP_INIT = 1,  //!< Use window overlap method, 
                               //!< only metrics and transitions update
  CNV_DEC_MODE_OVLP_DEC  = 2,  //!< Use window overlap method,  
                               //!< update transitions/metrics/trace through current &
                               //!< previous blocks, decode previous block only
  CNV_DEC_MODE_OVLP_LAST = 3   //!< last block in overlap

}vitMode_t;

//*****************************************************************************
// globals
//*****************************************************************************
extern int16 VIT_in_data[];			//!< Input fed into the C-model encoder
extern int16 VIT_quant_data[];		//!< Output from the C-model encoder
extern int32 VIT_gold_vt_data[];	//!< Golden trace history (VT0/VT1); can be used to verify functionality
extern Uint16 VIT_frame_len;

extern UINT16 trn_tmp[CNV_DEC_MAX_UBITS];

//*****************************************************************************
// function prototypes
//*****************************************************************************
//! \brief Initialize Viterbi Decoder
//! 
//! Initialize state metric table to a large negative value given by
//! CNV_DEC_METRIC_INIT and initialize the transition and wrap pointers
//! 
//! \param nTranBits Number of Coded bits
//
extern void cnvDecInit_asm(int nTranBits);

//!  Viterbi Decoder
//! 
//! This routine performs the trellis decoding. It has four modes of
//! operation
//! - 0: Update metrics and transition history, trace and decodes all (for header packets) 
//! - 1: Update metrics and transition history for only 1st block in payload
//! - 2: Update metrics and transition history, trace back through the current 
//!      and previous blocks, decodes previos block giving nBits/2 bits
//! - 3: Update metrics and transition history, trace back through the current 
//!      and previous blocks, decodes current and previos block giving nBits/2 bits 
//! 
//! \param nBits Number of Coded bits for this block
//! \param in_p Address of input buffer
//! \param out_p Address of output buffer
//! \param flag Mode of operation
//
extern void cnvDec_asm(int nBits, int *in_p, int *out_p, int flag);

//! \brief State Metrics Rescale
//! 
//! Rescale the state metrics by finding the lowest metric and dividing the
//! rest by it. This prevents overflow between successive decoder stages
//! 
//
extern void cnvDecMetricRescale_asm();

#ifdef __cplusplus
}
#endif // extern "C"

// @} //ingroup

#endif //end of _VCU0_VITERBI_DECODER_H_ definition

// End of File
