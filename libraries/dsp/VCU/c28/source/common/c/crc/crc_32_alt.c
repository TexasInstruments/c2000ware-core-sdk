//#############################################################################
//! \file source/common/C/crc/crc_32_alt.c
//!
//! \brief  32-bit CRC
//
// o CRC implementation is based on tables. If the tables
//   are calculated on the fly, the macro GEN_CRC_TABLES shall be defined
//   and genCRC32Tables() shall be called during 
//   initialization. If the macro is not defined, pre-calculated tables will
//   will be used. Using the latter option can put the tables to flash.
//
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
#include "VCU0_CRC.h"

//  Generate the CRC lookup table using the polynomial 0x04c11db7
// 
// \param none
//  
// This function is to generate the CRC32 table for every possible byte
// i.e. 2^8 = 256 table values, using the CRC32_PRIME polynomial 0x04c11db7. 
// It expects a global array, crc32_table, to be defined in the application
// code
// 
// \return none
// 
 void genCRC32Table()
/* generate the table of CRC remainders for all possible bytes */
{ 
  register uint16 i, j;  
  register uint32 crc32_accum;
  for ( i = 0;  i < 256;  i++ )
  { 
    // myindex = i;
    crc32_accum = ( (uint32) i << 24 );
    for ( j = 0;  j < 8;  j++ )
    { 
      if ( crc32_accum & 0x80000000L )
        crc32_accum = ( crc32_accum << 1 ) ^ POLYNOMIAL32;
      else
        crc32_accum = ( crc32_accum << 1 ); 
    }
    crc32_table[i] = crc32_accum;
  }
}

//  C- function to get the 32-bit CRC
// 
// \param The initial value of crc, in case the message has been
//  chopped into several parts, you can use the crc32 of the previous
//  segment as the init value for the current segment crc32 calculation
//  until the final crc is derived.
// \param Address of the message buffer
// \param Parity of the first message byte, i.e. whether its on an even
//  or odd address
// \param Length of the message in bytes
//  
// Calculate the 32-bit CRC of a message buffer by using the lookup table,
// crc32_table based on the polynomial 0x04c11db7
// 
// \return CRC result
// 
uint32 getCRC32_cpu (uint32 input_crc32_accum, uint16 * msg, CRC_parity_e parity,
    uint16 rxLen)
{
  register uint16 i;
  register uint16 j;
  uint32 crc32_accum;
  
  SINT16 *pdata;

  crc32_accum = input_crc32_accum;
  pdata = (SINT16 *) msg;

  for (j = 0; j < rxLen; j++, parity++)
  {
    i = ( crc32_accum >> 24 ) ^ (__byte(pdata, parity));
    crc32_accum = ( crc32_accum << 8 ) ^ crc32_table[i];
  }
  return crc32_accum; 
}

// End of file
