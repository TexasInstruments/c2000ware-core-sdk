#ifndef _CRCTABLE0X5D6DCBREFLECTED_H_
#define _CRCTABLE0X5D6DCBREFLECTED_H_
//#############################################################################
//! \file include/common/CrcTable0x5D6DCBReflected.h
//!
//! \brief  CRC Lookup Table for the polynomial 0x5D6DCB for a reflected algorithm
//!   i.e. the bits shifted out of the accumulator from the right instead of the
//!   left
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

const unsigned long crc24TableReflected[] = {
0x000000, 0x33D776, 0x67AEEC, 0x54799A, 0xCF5DD8, 0xFC8AAE, 0xA8F334, 0x9B2442,
0x39D6C5, 0x0A01B3, 0x5E7829, 0x6DAF5F, 0xF68B1D, 0xC55C6B, 0x9125F1, 0xA2F287,
0x73AD8A, 0x407AFC, 0x140366, 0x27D410, 0xBCF052, 0x8F2724, 0xDB5EBE, 0xE889C8,
0x4A7B4F, 0x79AC39, 0x2DD5A3, 0x1E02D5, 0x852697, 0xB6F1E1, 0xE2887B, 0xD15F0D,
0xE75B14, 0xD48C62, 0x80F5F8, 0xB3228E, 0x2806CC, 0x1BD1BA, 0x4FA820, 0x7C7F56,
0xDE8DD1, 0xED5AA7, 0xB9233D, 0x8AF44B, 0x11D009, 0x22077F, 0x767EE5, 0x45A993,
0x94F69E, 0xA721E8, 0xF35872, 0xC08F04, 0x5BAB46, 0x687C30, 0x3C05AA, 0x0FD2DC,
0xAD205B, 0x9EF72D, 0xCA8EB7, 0xF959C1, 0x627D83, 0x51AAF5, 0x05D36F, 0x360419,
0x69DB5D, 0x5A0C2B, 0x0E75B1, 0x3DA2C7, 0xA68685, 0x9551F3, 0xC12869, 0xF2FF1F,
0x500D98, 0x63DAEE, 0x37A374, 0x047402, 0x9F5040, 0xAC8736, 0xF8FEAC, 0xCB29DA,
0x1A76D7, 0x29A1A1, 0x7DD83B, 0x4E0F4D, 0xD52B0F, 0xE6FC79, 0xB285E3, 0x815295,
0x23A012, 0x107764, 0x440EFE, 0x77D988, 0xECFDCA, 0xDF2ABC, 0x8B5326, 0xB88450,
0x8E8049, 0xBD573F, 0xE92EA5, 0xDAF9D3, 0x41DD91, 0x720AE7, 0x26737D, 0x15A40B,
0xB7568C, 0x8481FA, 0xD0F860, 0xE32F16, 0x780B54, 0x4BDC22, 0x1FA5B8, 0x2C72CE,
0xFD2DC3, 0xCEFAB5, 0x9A832F, 0xA95459, 0x32701B, 0x01A76D, 0x55DEF7, 0x660981,
0xC4FB06, 0xF72C70, 0xA355EA, 0x90829C, 0x0BA6DE, 0x3871A8, 0x6C0832, 0x5FDF44,
0xD3B6BA, 0xE061CC, 0xB41856, 0x87CF20, 0x1CEB62, 0x2F3C14, 0x7B458E, 0x4892F8,
0xEA607F, 0xD9B709, 0x8DCE93, 0xBE19E5, 0x253DA7, 0x16EAD1, 0x42934B, 0x71443D,
0xA01B30, 0x93CC46, 0xC7B5DC, 0xF462AA, 0x6F46E8, 0x5C919E, 0x08E804, 0x3B3F72,
0x99CDF5, 0xAA1A83, 0xFE6319, 0xCDB46F, 0x56902D, 0x65475B, 0x313EC1, 0x02E9B7,
0x34EDAE, 0x073AD8, 0x534342, 0x609434, 0xFBB076, 0xC86700, 0x9C1E9A, 0xAFC9EC,
0x0D3B6B, 0x3EEC1D, 0x6A9587, 0x5942F1, 0xC266B3, 0xF1B1C5, 0xA5C85F, 0x961F29,
0x474024, 0x749752, 0x20EEC8, 0x1339BE, 0x881DFC, 0xBBCA8A, 0xEFB310, 0xDC6466,
0x7E96E1, 0x4D4197, 0x19380D, 0x2AEF7B, 0xB1CB39, 0x821C4F, 0xD665D5, 0xE5B2A3,
0xBA6DE7, 0x89BA91, 0xDDC30B, 0xEE147D, 0x75303F, 0x46E749, 0x129ED3, 0x2149A5,
0x83BB22, 0xB06C54, 0xE415CE, 0xD7C2B8, 0x4CE6FA, 0x7F318C, 0x2B4816, 0x189F60,
0xC9C06D, 0xFA171B, 0xAE6E81, 0x9DB9F7, 0x069DB5, 0x354AC3, 0x613359, 0x52E42F,
0xF016A8, 0xC3C1DE, 0x97B844, 0xA46F32, 0x3F4B70, 0x0C9C06, 0x58E59C, 0x6B32EA,
0x5D36F3, 0x6EE185, 0x3A981F, 0x094F69, 0x926B2B, 0xA1BC5D, 0xF5C5C7, 0xC612B1,
0x64E036, 0x573740, 0x034EDA, 0x3099AC, 0xABBDEE, 0x986A98, 0xCC1302, 0xFFC474,
0x2E9B79, 0x1D4C0F, 0x493595, 0x7AE2E3, 0xE1C6A1, 0xD211D7, 0x86684D, 0xB5BF3B,
0x174DBC, 0x249ACA, 0x70E350, 0x433426, 0xD81064, 0xEBC712, 0xBFBE88, 0x8C69FE,
};
 #endif // _CRCTABLE0X5D6DCBREFLECTED_H_

// End of File
