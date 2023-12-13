//#############################################################################
//! \file source/common/C/crc/crc_16.c
//!
//! \brief  16-bit CRC
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
#include "VCU2_CRC.h"

//*****************************************************************************
// defines
//*****************************************************************************

//*****************************************************************************
// globals
//*****************************************************************************

//*****************************************************************************
// function definitions
//*****************************************************************************

void CRC_run16BitTableLookupC(CRC_Handle hndCRC)
{
	uint16_t i;
	uint16_t tableIndex;
	uint16_t parity        = (uint16_t)hndCRC->parity;
	uint16_t accumulator   = hndCRC->seedValue;
	uint16_t *pInputVector = (uint16_t *)hndCRC->pMsgBuffer;
	uint16_t *pCrcTable    = (uint16_t *)hndCRC->pCrcTable;

	// The assumption is the message bytes are packed into 16-bit words
	// and the calculation starts from either the high or low byte
	// The memory arrangement is as follows:
	// Address|_LB__|_HB__|
	// 0x0000 |_D0L_|_D0H_|
	// 0x0001 |_D1L_|_D1H_|
	// 0x0002 |_D2L_|_D2H_|
	// 0x0003 |_D3L_|_D3H_|
	// 0x0004 |_D4L_|_D4H_|
	// ...

	for(i = 0; i < hndCRC->nMsgBytes; i++, parity++){
		// __byte selects either the low(0) or high(1) byte in a word
		// the initial selection provided by the enumeration parity
		// the table index is calculated from the high byte of the accumulator
		// XOR'd with the low and high bytes of each word in the input vector
		tableIndex  = (accumulator >> 8) ^ __byte((int *)pInputVector, parity);
		accumulator = (accumulator << 8) ^ pCrcTable[tableIndex];
	}

	// Save the CRC result
	hndCRC->crcResult = (uint32_t)accumulator;
}

void CRC_run16BitReflectedTableLookupC(CRC_Handle hndCRC)
{
	uint16_t i;
	uint16_t tableIndex;
	uint16_t parity        = (uint16_t)hndCRC->parity;
	uint16_t accumulator   = hndCRC->seedValue;
	uint16_t *pInputVector = (uint16_t *)hndCRC->pMsgBuffer;
	uint16_t *pCrcTable    = (uint16_t *)hndCRC->pCrcTable;

	// The assumption is the message bytes are packed into 16-bit words
	// and the calculation starts from either the high or low byte
	// The memory arrangement is as follows:
	// Address|_LB__|_HB__|
	// 0x0000 |_D0L_|_D0H_|
	// 0x0001 |_D1L_|_D1H_|
	// 0x0002 |_D2L_|_D2H_|
	// 0x0003 |_D3L_|_D3H_|
	// 0x0004 |_D4L_|_D4H_|
	// ...

	for(i = 0; i < hndCRC->nMsgBytes; i++, parity++){
		// __byte selects either the low(0) or high(1) byte in a word
		// the initial selection provided by the enumeration parity
		// the table index is calculated from the low byte of the accumulator
		// XOR'd with the low and high bytes of each word in the input vector
		tableIndex  = (accumulator & 0x00FF) ^ __byte((int *)pInputVector, parity);
		accumulator = (accumulator >> 8) ^ pCrcTable[tableIndex];
	}

	// Save the CRC result
	hndCRC->crcResult = (uint32_t)accumulator;
}

// End of file
