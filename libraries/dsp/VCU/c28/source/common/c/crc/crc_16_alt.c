//#############################################################################
//! \file source/common/C/crc/crc_16_alt.c
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
#include "VCU0_CRC.h"

// Generate the CRC lookup table using the polynomial 0x8005
// 
// \param none
//  
// This function is to generate the CRC16 table for every possible byte
// i.e. 2^8 = 256 table values, using the CRC16_802_15_4 polynomial 0x8005. It
// expects a global array, crc16p1_table, to be defined in the application
// code
// 
// \return none
// 
void genCRC16P1Table(void)
{
  int i, j;
  unsigned long poly, c;
  /* terms of polynomial defining this crc (except x^16): */
  //static const byte p[] = {0,2,15};
  static const int p[] = {0,2,15};

  /* make exclusive-or pattern from polynomial (0x1021) */
  poly = 0L;
  for ( i = 0; i < sizeof( p ) / sizeof( int ); i++ )
  {
    poly |= 1L << p[i];
  }

  for ( i = 0; i < 256; i++ )
  {
    c = i << 8;
    for ( j = 0; j < 8; j++ )
    {
      c = ( c & 0x8000 ) ? poly ^ ( c << 1 ) : ( c << 1 );
    }
    crc16p1_table[i] = (unsigned int) c;
  }
}

//  Generate the CRC lookup table using the polynomial 0x1021
// 
// \param none
//  
// This function is to generate the CRC16 table for every possible byte
// i.e. 2^8 = 256 table values, using the CRC16_ALT polynomial 0x1021. It
// expects a global array, crc16p2_table, to be defined in the application
// code
// 
// \return none
// 
void genCRC16P2Table(void)
{
  int i, j;
  unsigned long poly, c;
  /* terms of polynomial defining this crc (except x^16): */
  //static const byte p[] = {0,5,12};
  static const int p[] = {0,5,12};

  /* make exclusive-or pattern from polynomial (0x1021) */
  poly = 0L;
  for ( i = 0; i < sizeof( p ) / sizeof( int ); i++ )
  {
    poly |= 1L << p[i];
  }

  for ( i = 0; i < 256; i++ )
  {
    c = i << 8;
    for ( j = 0; j < 8; j++ )
    {
      c = ( c & 0x8000 ) ? poly ^ ( c << 1 ) : ( c << 1 );
    }
    crc16p2_table[i] = (unsigned int) c;
  }
}

//  C- function to get the 16-bit CRC
// 
// \param The initial value of crc, in case the message has been
//  chopped into several parts, you can use the crc16 of the previous
//  segment as the init value for the current segment crc16 calculation
//  until the final crc is derived.
// \param Address of the message buffer
// \param Parity of the first message byte, i.e. whether its on an even
//  or odd address
// \param Length of the message in bytes
//  
// Calculate the 16-bit CRC of a message buffer by using the lookup table,
// crc16p1_table based on the polynomial 0x8005
// 
// \return CRC result
// 
uint16 getCRC16P1_cpu (uint16 input_crc16_accum, uint16 * msg, CRC_parity_e parity,
    uint16 rxLen)
{
  uint16 crc16_accum = input_crc16_accum;
  SINT16 *pdata = (SINT16 *)msg;
  uint16 i, j = 0;

  for (j=0; j<rxLen; j++, parity++)
  {
    i = (crc16_accum >> 8) ^ __byte(pdata, parity);
    crc16_accum = (crc16_accum << 8) ^ crc16p1_table[i];
  }
  
  return (uint16)crc16_accum; 
}

//  C- function to get the 16-bit CRC
// 
// \param The initial value of crc, in case the message has been
//  chopped into several parts, you can use the crc16 of the previous
//  segment as the init value for the current segment crc16 calculation
//  until the final crc is derived.
// \param Address of the message buffer
// \param Parity of the first message byte, i.e. whether its on an even
//  or odd address
// \param Length of the message in bytes
//  
// Calculate the 16-bit CRC of a message buffer by using the lookup table,
// crc16p2_table based on the polynomial 0x1021
// 
// \return CRC result
// 
uint16 getCRC16P2_cpu (uint16 input_crc16_accum, uint16 * msg, CRC_parity_e parity,
    uint16 rxLen)
{
  uint16 crc16_accum = input_crc16_accum;
  SINT16 *pdata = (SINT16 *)msg;
  uint16 i, j = 0;

  for (j=0; j<rxLen; j++, parity++)
  {
    i = (crc16_accum >> 8) ^ __byte(pdata, parity);
    crc16_accum = (crc16_accum << 8) ^ crc16p2_table[i];
  }
  
  return (uint16)crc16_accum; 
}

// End of file
