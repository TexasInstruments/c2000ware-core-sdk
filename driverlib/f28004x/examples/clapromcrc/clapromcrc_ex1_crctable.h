//#############################################################################
//
// FILE:   clapromcrc_ex1_crctable.h
//
// TITLE:  CRC Table for CLA Program ROM
//
// This file contains the global variable 'uint32_t clapromcrcTable' which 
// contains the 97 CRC-32 values for the CLA Program ROM. The first 96 CRC
// values contain the CRCs for the 96 1KB blocks of memory. The last CRC value
// is the CRC for the entire 96KB of CLA Program ROM. For all of these 
// calculated values, a seed value of 0x00000000 was used.
//
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2023 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef _CLAPROMCRC_EX1_CRCTABLE_H_
#define _CLAPROMCRC_EX1_CRCTABLE_H_

//
// Included Files
//
#include "driverlib.h"
#include "device.h"

//
// Globals
//
uint32_t clapromcrcTable[97] = 
{
    0x1DB09369,
    0xA734865F,
    0xA9A6BDFB,
    0xD2924FE0,
    0x41110A6F,
    0x9BFD31E2,
    0xED9EE91A,
    0xC7C3F72E,
    0x665D575D,
    0xCCD32823,
    0x2D6BC95B,
    0x0D6EFE66,
    0x38AD2DE6,
    0x6F8C500C,
    0x15F0F865,
    0x4E4524E9,
    0x2BF5C642,
    0x88E91A4A,
    0xD2243A92,
    0xCA461C57,
    0x982F4C9E,
    0xB1773F86,
    0x194BBE5D,
    0x19CA9321,
    0x422DA4AC,
    0x8D4CF9DD,
    0xDFC6AAD4,
    0xC22C5BD8,
    0xE00E941D,
    0xCB463281,
    0xA5D77527,
    0xBB01B1CA,
    0x2BE125AD,
    0x6C8508C1,
    0x81C0BE4D,
    0xF3FBFE01,
    0x91B27E24,
    0xCEF60B29,
    0x8D070402,
    0xE651592D,
    0xA1356CF1,
    0x3D4D0472,
    0xA59BD599,
    0x63E40B93,
    0x90B69556,
    0x36DA6C3D,
    0xDCAE7A7E,
    0x9241C28E,
    0x17D56B61,
    0x7610F523,
    0x38FE4662,
    0x3C596CC3,
    0xB16601C4,
    0xC3A93BF2,
    0xC5D03A3F,
    0x50EE75A0,
    0xDD02E505,
    0x6154DEDC,
    0xABA4C153,
    0x9F68F3A1,
    0x9B2D0048,
    0xD890845E,
    0x5E188218,
    0xE1BC7621,
    0x528CF739,
    0xA53A5738,
    0xAD6AD5A2,
    0xC2859B45,
    0x81A98E84,
    0x24144359,
    0x3DB82BEF,
    0x8DCD442E,
    0xB26B98C2,
    0x672F4B50,
    0xFC0A3112,
    0xADDEAF4D,
    0x2B9BFFC6,
    0xC4D08F68,
    0x534A27D5,
    0x5DA3A860,
    0x5B0AF1EA,
    0x5B0AF1EA,
    0x5B0AF1EA,
    0x5B0AF1EA,
    0x5B0AF1EA,
    0x5B0AF1EA,
    0xAA8FF25E,
    0xF2D08A15,
    0x1F10415D,
    0x4034B8BD,
    0xB866A22C,
    0xBC4D802B,
    0xF886C660,
    0x06471E84,
    0x315EA800,
    0x5B0AF1EA,
    0x84BFA10C
};

#endif //_CLAPROMCRC_EX1_CRCTABLE_H_

//
// End of File
//
