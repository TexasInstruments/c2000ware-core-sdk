//###########################################################################
//
// FILE:   gcrc.c
//
// TITLE:  Driver for the GCRC module.
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

#include "gcrc.h"


//*****************************************************************************
//
// GCRC_setFixedPolynomialDataPath()
//
//*****************************************************************************
void
GCRC_setFixedPolynomialDataPath(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(GCRC_isBaseValid(base));

    //
    // Set the polynomial size, Endianness, dataType and Bitreverse fields
    //
    HWREG(base + GCRC_O_CRCCTRL) = ((uint32_t)GCRC_FIXEDPATH_POLYSIZE <<
                                    GCRC_CRCCTRL_POLYSIZE_S) |
                                   GCRC_FIXEDPATH_ENDIANNESS |
                                   GCRC_FIXEDPATH_DATATYPE   |
                                   GCRC_FIXEDPATH_BITREVERSE;

    //
    // Set the 32-bit polynomial
    //
    HWREG(base + GCRC_O_CRCPOLY) = GCRC_FIXEDPATH_POLY;

    //
    // Disable data masking
    //
    HWREG(base + GCRC_O_CRCDATAMASK) = GCRC_FIXEDPATH_DATAMASK;
}

//*****************************************************************************
//
// GCRC_writeData()
//
//*****************************************************************************
void
GCRC_writeData(uint32_t base, uint32_t data, uint32_t dataSize)
{
    //
    // Check the arguments
    //
    ASSERT(GCRC_isBaseValid(base));
    ASSERT((dataSize == GCRC_DATATYPE_8BIT)  ||
           (dataSize == GCRC_DATATYPE_16BIT) ||
           (dataSize == GCRC_DATATYPE_32BIT));

    if(dataSize == GCRC_DATATYPE_8BIT)
    {
        //
        // Perform a 8-bit write
        //
        HWREGB(base + GCRC_O_CRCDATAIN) = (uint8_t)data;
    }
    else if(dataSize == GCRC_DATATYPE_16BIT)
    {
        //
        // Perform a 16-bit write
        //
        HWREGH(base + GCRC_O_CRCDATAIN) = (uint16_t)data;
    }
    else
    {
        //
        // Perform a 32-bit write
        //
        HWREG(base + GCRC_O_CRCDATAIN) = data;
    }
}



