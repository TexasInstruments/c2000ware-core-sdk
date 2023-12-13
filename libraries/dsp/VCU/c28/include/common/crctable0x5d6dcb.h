#ifndef _CRCTABLE0X5D6DCB_H_
#define _CRCTABLE0X5D6DCB_H_
//#############################################################################
//! \file include/common/CrcTable0x5D6DCB.h
//!
//! \brief  CRC Lookup Table for polynomial 0x5D6DCB
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
#define POLYNOMIAL24		0x5D6DCB

const unsigned long crc24Table[] = {
0x000000, 0x5D6DCB, 0xBADB96, 0xE7B65D, 0x28DAE7, 0x75B72C, 0x920171, 0xCF6CBA,
0x51B5CE, 0x0CD805, 0xEB6E58, 0xB60393, 0x796F29, 0x2402E2, 0xC3B4BF, 0x9ED974,
0xA36B9C, 0xFE0657, 0x19B00A, 0x44DDC1, 0x8BB17B, 0xD6DCB0, 0x316AED, 0x6C0726,
0xF2DE52, 0xAFB399, 0x4805C4, 0x15680F, 0xDA04B5, 0x87697E, 0x60DF23, 0x3DB2E8,
0x1BBAF3, 0x46D738, 0xA16165, 0xFC0CAE, 0x336014, 0x6E0DDF, 0x89BB82, 0xD4D649,
0x4A0F3D, 0x1762F6, 0xF0D4AB, 0xADB960, 0x62D5DA, 0x3FB811, 0xD80E4C, 0x856387,
0xB8D16F, 0xE5BCA4, 0x020AF9, 0x5F6732, 0x900B88, 0xCD6643, 0x2AD01E, 0x77BDD5,
0xE964A1, 0xB4096A, 0x53BF37, 0x0ED2FC, 0xC1BE46, 0x9CD38D, 0x7B65D0, 0x26081B,
0x3775E6, 0x6A182D, 0x8DAE70, 0xD0C3BB, 0x1FAF01, 0x42C2CA, 0xA57497, 0xF8195C,
0x66C028, 0x3BADE3, 0xDC1BBE, 0x817675, 0x4E1ACF, 0x137704, 0xF4C159, 0xA9AC92,
0x941E7A, 0xC973B1, 0x2EC5EC, 0x73A827, 0xBCC49D, 0xE1A956, 0x061F0B, 0x5B72C0,
0xC5ABB4, 0x98C67F, 0x7F7022, 0x221DE9, 0xED7153, 0xB01C98, 0x57AAC5, 0x0AC70E,
0x2CCF15, 0x71A2DE, 0x961483, 0xCB7948, 0x0415F2, 0x597839, 0xBECE64, 0xE3A3AF,
0x7D7ADB, 0x201710, 0xC7A14D, 0x9ACC86, 0x55A03C, 0x08CDF7, 0xEF7BAA, 0xB21661,
0x8FA489, 0xD2C942, 0x357F1F, 0x6812D4, 0xA77E6E, 0xFA13A5, 0x1DA5F8, 0x40C833,
0xDE1147, 0x837C8C, 0x64CAD1, 0x39A71A, 0xF6CBA0, 0xABA66B, 0x4C1036, 0x117DFD,
0x6EEBCC, 0x338607, 0xD4305A, 0x895D91, 0x46312B, 0x1B5CE0, 0xFCEABD, 0xA18776,
0x3F5E02, 0x6233C9, 0x858594, 0xD8E85F, 0x1784E5, 0x4AE92E, 0xAD5F73, 0xF032B8,
0xCD8050, 0x90ED9B, 0x775BC6, 0x2A360D, 0xE55AB7, 0xB8377C, 0x5F8121, 0x02ECEA,
0x9C359E, 0xC15855, 0x26EE08, 0x7B83C3, 0xB4EF79, 0xE982B2, 0x0E34EF, 0x535924,
0x75513F, 0x283CF4, 0xCF8AA9, 0x92E762, 0x5D8BD8, 0x00E613, 0xE7504E, 0xBA3D85,
0x24E4F1, 0x79893A, 0x9E3F67, 0xC352AC, 0x0C3E16, 0x5153DD, 0xB6E580, 0xEB884B,
0xD63AA3, 0x8B5768, 0x6CE135, 0x318CFE, 0xFEE044, 0xA38D8F, 0x443BD2, 0x195619,
0x878F6D, 0xDAE2A6, 0x3D54FB, 0x603930, 0xAF558A, 0xF23841, 0x158E1C, 0x48E3D7,
0x599E2A, 0x04F3E1, 0xE345BC, 0xBE2877, 0x7144CD, 0x2C2906, 0xCB9F5B, 0x96F290,
0x082BE4, 0x55462F, 0xB2F072, 0xEF9DB9, 0x20F103, 0x7D9CC8, 0x9A2A95, 0xC7475E,
0xFAF5B6, 0xA7987D, 0x402E20, 0x1D43EB, 0xD22F51, 0x8F429A, 0x68F4C7, 0x35990C,
0xAB4078, 0xF62DB3, 0x119BEE, 0x4CF625, 0x839A9F, 0xDEF754, 0x394109, 0x642CC2,
0x4224D9, 0x1F4912, 0xF8FF4F, 0xA59284, 0x6AFE3E, 0x3793F5, 0xD025A8, 0x8D4863,
0x139117, 0x4EFCDC, 0xA94A81, 0xF4274A, 0x3B4BF0, 0x66263B, 0x819066, 0xDCFDAD,
0xE14F45, 0xBC228E, 0x5B94D3, 0x06F918, 0xC995A2, 0x94F869, 0x734E34, 0x2E23FF,
0xB0FA8B, 0xED9740, 0x0A211D, 0x574CD6, 0x98206C, 0xC54DA7, 0x22FBFA, 0x7F9631,
};
 #endif // _CRCTABLE0X5D6DCB_H_

// End of File
