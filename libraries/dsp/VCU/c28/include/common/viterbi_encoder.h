#ifndef _VITERBI_ENCODER_H_
#define _VITERBI_ENCODER_H_
//#############################################################################
//! \file include/common/viterbi_encoder.h
//!
//! \brief  Viterbi Encoder header file
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
#include <stdint.h>

//!
//! \defgroup VITERBI_ENCODER Viterbi Encoder

//!
//! \ingroup VITERBI_ENCODER
// @{

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
// defines
//*****************************************************************************
#define MIN_K                    4
#define MAX_K					 7
#define MAX_CNV_ENC_DELAY_LEN	 (MAX_K - 1)
#define K4_CNV_ENC_DELAY_LEN	 4
#define K7_CNV_ENC_DELAY_LEN	 7
//*****************************************************************************
// typedefs
//*****************************************************************************
//! \brief VITERBI Encoder Structure
//! The encoder is implemented in C. It is used to generate the input
//! sequence for the example
//!
typedef struct _VITERBI_ENCODER_Obj_{
  uint16_t delay[MAX_CNV_ENC_DELAY_LEN];  //!< delay line
  uint16_t *u_p;                          //!< pointer to uncoded bits buffer
  uint16_t *c_p;                          //!< pointer to coded bits buffer
  uint16_t cr;                            //!  code rate
  uint16_t nBits;                         //!< Number of uncoded bits
  void (*init)(void *);			          //!< Function pointer to Encoder initialization routine
  void (*run)(void *);			          //!< Function pointer to Encoder computation routine
  void (*quantize)(void  *, int16_t );    //!< Function pointer to Encoder quantization routine
}VITERBI_ENCODER_Obj;

//! \brief Handle to the VITERBI Encoder structure
//!
typedef VITERBI_ENCODER_Obj *VITERBI_ENCODER_Handle;

//*****************************************************************************
// globals
//*****************************************************************************

//*****************************************************************************
// function prototypes
//*****************************************************************************

//! \brief Initialize the encoder structure by zeroing out the delay line
//! \param hndVITEncoder Handle to the Viterbi Encoder Structure
void VITERBI_ENCODER_init(VITERBI_ENCODER_Handle hndVITEncoder);

//!
//! \brief This function performs convolution encoding in prime. It uses
//! constraint length of K=7, and code rate 1/2.
//! 
//! The polynomials are:
//! G0 = 1 + D2 + D3
//! G1 = 1 + D  + D2 + D3
//!                                                       
//! It calculates:
//! c(2k  )=u(k)+u(k-2)+u(k-3)
//! c(2k+1)=u(k)+u(k-1)+u(k-2)+u(k-3)
//!
//! \param hndVITEncoder handle to the Viterbi encoder object whose elements are
//!        nBits - number of input bits for decode                         
//!        u_p   - pointer to input uncoded bits                                    
//!        c_p   - pointer to output coded bits 
//!                (It produces 2xnBit bits)                           
//!
void VITERBI_ENCODER_runK4CR12(VITERBI_ENCODER_Handle hndVITEncoder);

//!
//! \brief This function performs convolution encoding in prime. It uses
//! constraint length of K=7, and code rate 1/2.
//! 
//! The polynomials are:
//! G0 = 1 + D + D2 +D3 + D6                                            
//! G1 = 1 + D2 + D3 + D5 + D6  
//!                                                       
//! It calculates:
//! c(2k  )=u(k)+u(k-1)+u(k-2)+u(k-3)+u(k-6)                  
//! c(2k+1)=u(k)+u(k-2)+u(k-3)+u(k-5)+u(k-6)
//!
//! \param hndVITEncoder handle to the Viterbi encoder object whose elements are
//!        nBits - number of input bits for decode                         
//!        u_p   - pointer to input uncoded bits                                    
//!        c_p   - pointer to output coded bits 
//!                (It produces 2xnBit bits)                           
//!
void VITERBI_ENCODER_runK7CR12(VITERBI_ENCODER_Handle hndVITEncoder);

//! \brief Quantization of Encoder Bits
//! \param hndVITEncoder handle to the Viterbi encoder object whose elements are
//!        nBits - number of input bits to be quantized
//!        c_p   - pointer to output coded bits
//! \param format power of 2, the bits will be quantized to +-(2^format)
void VITERBI_ENCODER_quantizeBits(VITERBI_ENCODER_Handle hndVITEncoder, int16_t format);

//! \brief Word Unpacking to Bits
//! \param[in]  nSize number of 16-bits words 
//! \param[in]  in_p  pointer to input data in 16-bit words
//! \param[out] out_p pointer to output data in bits     
void VITERBI_ENCODER_blockUnpack2Bits(uint16_t nSize, uint16_t *in_p, uint16_t *out_p);
#ifdef __cplusplus
}
#endif // extern "C"

// @} //ingroup

#endif //end of _VITERBI_ENCODER_H_ definition

// End of File
