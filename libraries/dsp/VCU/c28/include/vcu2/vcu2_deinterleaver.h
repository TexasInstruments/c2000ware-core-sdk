#ifndef _VCU2_DEINTERLEAVER_H_
#define _VCU2_DEINTERLEAVER_H_
//#############################################################################
//! \file include/vcu2/vcu2_deinterleaver.h
//!
//! \brief  De-interleaver header file
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
#include "vcu2_types.h"

//!
//! \defgroup VCU2_DEINTERLEAVER De-Interleaver (VCU2)

//!
//! \ingroup VCU2_DEINTERLEAVER
// @{

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
// defines
//*****************************************************************************
#define _DOXYGEN_	1	// Temporary Definition for documentation purposes

//*****************************************************************************
// typedefs
//*****************************************************************************
//
//    | Sub-carrier number i = 0..m -1
//  --|------------------------------------------------------>
//  O | +----------------------------------------------------+
//  F | |   0   |   1  |                              | m-1  |
//  D | +-------+------+------------------------------+------+
//  M | |   m   |  m+1 |                              |2m-1  |
//    | +-------+------+------------------------------+------+
//  s | |       |      |                              |      |
//  y | |       |      |                              |      |
//  m | |       |      |                              |      |
//  b | |       |      |                              |      |
//  o | |       |      |                              |      |
//  l | |       |      |                              |      |
//    | |       |      |                              |      |
//  n | |       |      |                              |      |
//  u | |       |      |                              |      |
//  m | |       |      |                              |      |
//  b | |       |      |                              |      |
//  e | |       |      |                              |      |
//  r | |       |      |                              |      |
//    | |       |      |                              |      |
//  j | |       |      |                              |      |
//  = | |       |      |                              |      |
//  0 | |       |      |                              |      |
//  . | +-------+------+------------------------------+------+
//  . | |(n-1)*m|      |                              | n*m-1|
// n-1| +----------------------------------------------------+
//    v
//
// J = (j*n_j + i*n_i)%n
// I = (i*m_i + J*M_j)%m
// (i,j) - original bit position  (I,J) - interleaved position

//! \brief De-interleaver structure
//!
typedef struct _DEINTERLEAVER_Obj_{
	uint16_t  	*pInBuffer;			//!< Pointer to the input buffer
	uint16_t	*pOutBuffer;		//!< Pointer to the input buffer
	uint16_t	*pSymbol;			//!< Pointer to symbol storage
	uint16_t	n;					//!< number of OFDM symbols in each interleaving block
	uint16_t 	m;					//!< number of sub-carriers in each OFDM symbol
	uint16_t 	b;                  //!< beta
	uint16_t 	v;                  //!< mu
	uint16_t 	a;                  //!< alpha
	uint16_t 	u;                  //!< upsilon
	uint16_t 	n_i;				//!< Circular shift of the rows
	uint16_t 	n_j;				//!< Circular shift of the rows
	uint16_t 	m_i;				//!< Circular shift of the columns
	uint16_t 	m_j;				//!< Circular shift of the columns
	void (*init)(void *);			//!< Function pointer to DEINTERLEAVER initialization routine (NULL as of current release)
	void (*run)(void *);			//!< Function pointer to DEINTERLEAVER computation routine
}DEINTERLEAVER_Obj;

//! \brief Handle to the DEINTERLEAVER structure
//!
typedef DEINTERLEAVER_Obj *DEINTERLEAVER_Handle;

//*****************************************************************************
// globals
//*****************************************************************************

//*****************************************************************************
// function prototypes
//*****************************************************************************

//! \brief Runs the DEINTERLEAVER routine
//!
//! The de-interleaver equations are:
//! \f[J &=& (j{\times}n_{j} + i{\times}n_{i}) \% n \\ \f]
//! \f[I &=& (i{\times}m_{i} + J{\times}m_{j}) \% m \\ \f]
//! 
//! The interleaver equations are:
//! \f[ i &=& (a \times I - u \times J) \% m         \\ \f]
//! \f[ j &=& (b \times J - v \times i) \% n         \\ \f]
//! \f[ b &=& \beta_{j}                              \\ \f]
//! \f[ v &=& \mu_{ij} = \beta_{j} \times n_{i}      \\ \f]
//! \f[ a &=& \alpha_{i}                             \\ \f]
//! \f[ u &=& \upsilon_{ij} = alpha_{i} \times m_{j} \\ \f]
//! (i,j) - original bit position  (I,J) - interleaved position
//!
//! \param[in] hndDEINTERLEAVER handle to the DEINTERLEAVER object
//
void DEINTERLEAVER_run(DEINTERLEAVER_Handle hndDEINTERLEAVER);

#ifdef __cplusplus
}
#endif // extern "C"

// @} //ingroup

#endif //end of _VCU2_DEINTERLEAVER_H_ definition

// End of File
