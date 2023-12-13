#ifndef _RS_TABLESN255K239_H_
#define _RS_TABLESN255K239_H_
//#############################################################################
//! \file include/common/RS_TablesN255K239.h
//!
//! \brief  Galois Field Lookup Table for polynomial 0x0000011D 
//!         Field Generator Polynomial: x^{8}+x^{4}+x^{3}+x^{2}+1
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
#include <stdint.h>

#define FIELDGENPOLY		0x0000011D 
#define TABLE_SIZE			256
#define NUM_ROOTS			16
#define CODEGENPOLY_SIZE    17

extern const int16_t RS_expTable[TABLE_SIZE];
extern const int16_t RS_logTable[TABLE_SIZE];
extern const int16_t RS_expInvTable[TABLE_SIZE];
extern const int16_t RS_logInvTable[TABLE_SIZE];
extern const int16_t RS_codeGenPoly[CODEGENPOLY_SIZE];
extern const int16_t  RS_packedAlpha[NUM_ROOTS];
extern const int16_t RS_packedBeta[NUM_ROOTS>>1];

#endif // _RS_TABLESN255K239_H_

// End of File
