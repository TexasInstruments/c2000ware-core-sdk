//###########################################################################
//
// FILE:    hw_gcrc.h
//
// TITLE:   Definitions for the GCRC registers.
//
//###########################################################################
// $Copyright:
// Copyright (C) 2022 Texas Instruments Incorporated - http://www.ti.com
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//###########################################################################

#ifndef HW_GCRC_H
#define HW_GCRC_H

//*************************************************************************************************
//
// The following are defines for the GCRC register offsets
//
//*************************************************************************************************
#define GCRC_O_CRCCTRL        0x0U    // CRC Control Register
#define GCRC_O_CRCPOLY        0x4U    // CRC Polynomial Register
#define GCRC_O_CRCDATAMASK    0x8U    // CRC Data Mask Register
#define GCRC_O_CRCDATAIN      0xCU    // CRC Data Input Register
#define GCRC_O_CRCDATAOUT     0x10U   // CRC Data Output Register
#define GCRC_O_CRCDATATRANS   0x14U   // CRC Transformed Data Register


//*************************************************************************************************
//
// The following are defines for the bit fields in the CRCCTRL register
//
//*************************************************************************************************
#define GCRC_CRCCTRL_POLYSIZE_S   0U
#define GCRC_CRCCTRL_POLYSIZE_M   0x3FU    // CRC polynomial order
#define GCRC_CRCCTRL_ENDIANNESS   0x40U    // Defines the endianness of the data stream.
#define GCRC_CRCCTRL_BITREVERSE   0x80U    // Enables the DATAIN bus to the CRC engine to be bit
                                           // reversed.
#define GCRC_CRCCTRL_DATATYPE_S   8U
#define GCRC_CRCCTRL_DATATYPE_M   0x300U   // Defines the DATATYPE of the element of the data
                                           // array.

//*************************************************************************************************
//
// The following are defines for the bit fields in the CRCDATAMASK register
//
//*************************************************************************************************
#define GCRC_CRCDATAMASK_DATAMASK_S   0U
#define GCRC_CRCDATAMASK_DATAMASK_M   0x1FU   // Number of bits to be masked



#endif
