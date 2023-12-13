//#############################################################################
//! \file source/common/C/crc/crc_util.c
//!
//! \brief  Utility routines for CRC calculations
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
uint32_t CRC_bitReflect(uint32_t valToReverse,int16_t bitWidth)
{
	int16_t i,j,p,t;
	uint32_t pattern, skip;
	//unsigned int a, b;
	uint32_t value = valToReverse;

	//Determine what power of 2 bitWidth is
	t = bitWidth; p = 0;
	while(t > 1){
		t = t >> 1;
		p++;
	}

	//Start the reversing process
	for(i = 0; i < p; i++){
		//Increment skip
		skip = CRC_pow2(i);

		//Initialize pattern
		pattern = 0xFFFFFFFF;
		//First generate the pattern for the switch
		for(j = 0; j < (bitWidth/skip)-1; j++){
			pattern ^= (pattern << skip);
		}

		//Make the switch
		//a = ((value & pattern) << skip);
		//b = ((value >> skip) & pattern);
		//value = a | b;
		value = (((value & pattern) << skip) | ((value >> skip) & pattern));
	}

	return value;

}


uint16_t CRC_pow2(uint16_t power)
{
	if (power == 0){
		return 1;
	}else{
		return(2 * CRC_pow2(--power));
	}
}
// End of file
