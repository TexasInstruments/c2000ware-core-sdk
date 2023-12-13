#ifndef _REEDSOLOMON_ENCODER_H_
#define _REEDSOLOMON_ENCODER_H_
//#############################################################################
//! \file include/common/reedsolomon_encoder.h
//!
//! \brief  Reed Solomon Encoder header file
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
//! \defgroup REEDSOLOMON_ENCODER Reed Solomon Encoder

//!
//! \ingroup REEDSOLOMON_ENCODER
// @{

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
// defines
//*****************************************************************************
#define RS_BLOCK_N      255     //!< Encoded block size
#define RS_BLOCK_K      239     //!< Message size
#define RS_BLOCK_T      ((RS_BLOCK_N - RS_BLOCK_K)/2) //!< number of correctable errors
#define WORD_2BYTES   	1       //!< Encoder can either operate on 2 bytes/word or 1 byte/word
//*****************************************************************************
// typedefs
//*****************************************************************************

//! \brief Reed-Solomon Encoder structure
//!
typedef struct _REEDSOLOMON_ENCODER_Obj_{
    uint16_t    n;                  //!< number of codeword symbols (bytes) in a block
    uint16_t    k;                  //!< number of message symbols (bytes) in a block
    uint16_t    t;                  //!< number of correctable errors in the block
    int16_t     *pGenPolyIdx;       //!< Pointer to the Code Generator Polynomial with coefficients in index form
    int16_t     *pRS_expTable;      //!< Pointer to the lookup table (roots of the extension Galois Field)
                                    //!  that converts index to decimal form
    int16_t     *pRS_logTable;      //!< Pointer to the lookup table (roots of the extension Galois Field)
                                    //!  that converts decimal to index form
	void (*init)(void *, 
                int16_t *,
                int16_t *,
                int16_t *);         //!< Function pointer to Reed Solomon Encoder initialization routine
	void (*run)(void *, 
                int16_t *,
                int16_t  );         //!< Function pointer to Reed Solomon Encoder computation routine
}REEDSOLOMON_ENCODER_Obj;

//! \brief Handle to the Reed-Solomon Encoder structure
//!
typedef REEDSOLOMON_ENCODER_Obj *REEDSOLOMON_ENCODER_Handle;

//*****************************************************************************
// globals
//*****************************************************************************

//*****************************************************************************
// function prototypes
//*****************************************************************************
//! \brief Initializes the Reed Solomon Encoder object
//!
//! \param[in] hndRSEncoder handle to the Reed Solomon Encoder object
//! \param[in] pGenPolyIdx pointer to the code generator polynomial (Index Form)
//! \param[in] pRS_expTable pointer to the lookup table that converts index to decimal form
//! \param[in] pRS_logTable pointer to the lookup table that converts decimal to index form
//
void REEDSOLOMON_ENCODER_init(REEDSOLOMON_ENCODER_Handle hndRSEncoder, 
                int16_t *pGenPolyIdx,
                int16_t *pRS_expTable,
                int16_t *pRS_logTable);

//! \brief Runs the Reed Solomon Encoder
//! 
//! \param[in] hndRSEncoder handle to the Reed Solomon Encoder object
//! \param     pData pointer to the original message or data
//! \param[in] nBytes number of bytes in the input message
//
void REEDSOLOMON_ENCODER_run(REEDSOLOMON_ENCODER_Handle hndRSEncoder,
                             int16_t *pData, int16_t nBytes);

#ifdef __cplusplus
}
#endif // extern "C"

// @} //ingroup

#endif //end of _REEDSOLOMON_ENCODER_H_ definition

// End of File
