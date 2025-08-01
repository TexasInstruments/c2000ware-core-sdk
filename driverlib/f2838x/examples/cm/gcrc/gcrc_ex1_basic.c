//#############################################################################
//
// FILE:   gcrc_ex1_basic.c
//
// TITLE:  CRC computation using GCRC module
//
//! \addtogroup driver_example_cm_list
//! <h1>GCRC example</h1>
//!
//! This example showcases how to use GCRC to compute CRC for a 8-bit array.
//! This demonstrates 2 methods for computing the CRC
//! cm_common_config_c28x example needs to be run on C28x1 before running this
//! example on the CM core
//!
//! \b External \b Connections \n
//!  - None
//!
//! \b Watch \b Variables \n
//!  - \b crcResult1   - CRC value computed using Method 1
//!  - \b crcResult2   - CRC value computed using Method 2
//!  - \b crcGolden    - Golden CRC value
//!
//
//#############################################################################
// 
// C2000Ware v6.00.00.00
//
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
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
//#############################################################################

#include "cm.h"

#pragma DATA_ALIGN(gData, 32)
uint8_t gData[] = {0x8a, 0xf6, 0x1e, 0x6d, 0x8d};

//
// Main
//
void main(void)
{
	int i;
    uint8_t     data[]      = {0x8a, 0xf6, 0x1e, 0x6d, 0x8d};
	uint32_t    crcResult1  = 0;
	uint32_t    crcResult2  = 0;
    uint32_t    crcGolden   = 0x52d24341;
	
    //
    // disable WD, enable peripheral clocks.
    //
    CM_init();
	
	
	//
	// GCRC configurations
	//
    uint32_t    poly        = 0x4C11DB7;
    uint32_t    polysize    = 32;
    uint32_t    seed        = 0x654cfd7a;
    uint32_t    endianness  = GCRC_ENDIANNESS_BIG;
    uint32_t    dataType    = GCRC_DATATYPE_8BIT;
    bool        bitRev      = false;
    uint32_t    dataMask    = 0;
	
	//
	// Configure the GCRC module
	//
    GCRC_setPolynomial(GCRC_BASE, poly, polysize);
    GCRC_setDataType(GCRC_BASE, dataType);
    GCRC_setDataEndianness(GCRC_BASE, endianness);
    GCRC_setDataMask(GCRC_BASE, dataMask);
    GCRC_enableBitReverse(GCRC_BASE, bitRev);
	
	
	/////////////////////////////////////////////////////////////////
	// Method 1 - Providing data to the CRC engine as 8-bit writes //
	/////////////////////////////////////////////////////////////////
	
	//
	// Set Seed value
	//
    GCRC_setSeedValue(GCRC_BASE, seed);

	//
	// Write data to the CRC engine
	//
	for(i = 0; i < 5; i++)
    {
        GCRC_writeData(GCRC_BASE, data[i], dataType);
    }
	
	//
	// Read the CRC result
	//
	crcResult1 = GCRC_readResult(GCRC_BASE);
	

	
	//////////////////////////////////////////////////////////////////////////////////////
	// Method 2 (optimal) - Providing data to the CRC engine as 32-bit and 8-bit writes //
	//////////////////////////////////////////////////////////////////////////////////////
	
	//
	// The 4 bytes aligned to a 32-bit address can be combined and provided
	// to the engine as a single 32-bit data
	//
	
	//
	// Set Seed value
	//
    GCRC_setSeedValue(GCRC_BASE, seed);

	//
	// Write data to the CRC engine. 
	// gData is aligned to a 32-bit address
	//
    GCRC_writeData(GCRC_BASE, *(uint32_t *)gData, GCRC_DATATYPE_32BIT);
    GCRC_writeData(GCRC_BASE, gData[4], GCRC_DATATYPE_8BIT);
    
	//
	// Read the CRC result
	//
	crcResult2 = GCRC_readResult(GCRC_BASE);

	
	//
	// Check for computed crc values
	//
	if((crcResult1 != crcGolden) || (crcResult2 != crcGolden))
	{
	    //
	    // Error. The computed crc does not match the golden value
	    //
	    __asm(" bkpt #0");
	}
	
    //
    // Loop indefinitely (optional)
    //
	while(1);
}
