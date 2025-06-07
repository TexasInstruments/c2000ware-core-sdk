//###########################################################################
//
// FILE:  crc8_shared_data.c
//
// TITLE: CRC8 Shared Data
//
// Description: Declare shared memory variables and assign them to specific 
// CLA-accessible memory locations
//
//! \addtogroup f2803x_example_cla_list
//! \b Memory \b Allocation \n
//!  - CLA1 Data RAM 1(RAML2)
//!    - table - CRC Lookup table
//!  - CLA1 to CPU Message RAM
//!    - crc8_msg1 - CRC of message 1
//!    - crc8_msg2 - CRC of message 2
//!    - crc8_msg3 - CRC of message 3
//!    - crc8_msg4 - CRC of message 4
//!  - CPU to CLA1 Message RAM
//!    - msg1 - Test message 1
//!    - msg2 - Test message 2
//!    - msg3 - Test message 3
//!    - msg4 - Test message 4
//
//###########################################################################
// $TI Release:  $
// $Release Date: $
// $Copyright:
// Copyright (C) 2009-2025 Texas Instruments Incorporated - http://www.ti.com/
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

//
// Included Files
//
#include "DSP28x_Project.h"

//
// Include the test header file whose name is based on the test name
// which is defined by the macro TEST on the command line
//
#include XSTRINGIZE(XCONCAT(TEST_NAME,_shared.h))

//
// Globals (Ensure that all data is placed in the data rams)
//

//
// Task 1 (C) Variables
// CLA Input Data
//
#pragma DATA_SECTION(msg1,"CpuToCla1MsgRAM");
#pragma DATA_SECTION(msg2,"CpuToCla1MsgRAM");
#pragma DATA_SECTION(msg3,"CpuToCla1MsgRAM");
#pragma DATA_SECTION(msg4,"CpuToCla1MsgRAM");
Uint16 msg1[5] =  {0x5543, 0x3669, 0x3318, 0x5f57, 0x2ba2};
Uint16 msg2[12] =
{
    0x1e18, 0x1842, 0x13e7, 0x77be, 0x4859, 0x20d7, 0x3c5d, 0x2efd, 
    0x2af7, 0x112c, 0x0f13, 0x06fa
};  
Uint16 msg3[5] =  {0x6bd9, 0x335f, 0x1dfc, 0x4d84, 0x17fd};
Uint16 msg4[12] = 
{
    0x00e4, 0x0af8, 0x6f37, 0x3d39, 0x1c63, 0x3702, 0x43c1, 0x38e3,
    0x33cb, 0x6ed8, 0x4a56, 0x221a
};

//
// CLA Output Data
//
#pragma DATA_SECTION(crc8_msg1,"Cla1ToCpuMsgRAM");
#pragma DATA_SECTION(crc8_msg2,"Cla1ToCpuMsgRAM");
#pragma DATA_SECTION(crc8_msg3,"Cla1ToCpuMsgRAM");
#pragma DATA_SECTION(crc8_msg4,"Cla1ToCpuMsgRAM");
Uint16 crc8_msg1;
Uint16 crc8_msg2;
Uint16 crc8_msg3;
Uint16 crc8_msg4;

//
// Task 2 (C) Variables
//

//
// Task 3 (C) Variables
//

//
// Task 4 (C) Variables
//

//
// Task 5 (C) Variables
//

//
// Task 6 (C) Variables
//

//
// Task 7 (C) Variables
//

//
// Task 8 (C) Variables
//

//
// Common (C) Variables
//
#pragma DATA_SECTION(table,"Cla1DataRam1");
const Uint16 table[256] = 
{
    0x0000, 0x0007, 0x000E, 0x0009, 0x001C, 0x001B, 0x0012, 0x0015,
    0x0038, 0x003F, 0x0036, 0x0031, 0x0024, 0x0023, 0x002A, 0x002D,
    0x0070, 0x0077, 0x007E, 0x0079, 0x006C, 0x006B, 0x0062, 0x0065,
    0x0048, 0x004F, 0x0046, 0x0041, 0x0054, 0x0053, 0x005A, 0x005D,
    0x00E0, 0x00E7, 0x00EE, 0x00E9, 0x00FC, 0x00FB, 0x00F2, 0x00F5,
    0x00D8, 0x00DF, 0x00D6, 0x00D1, 0x00C4, 0x00C3, 0x00CA, 0x00CD,
    0x0090, 0x0097, 0x009E, 0x0099, 0x008C, 0x008B, 0x0082, 0x0085,
    0x00A8, 0x00AF, 0x00A6, 0x00A1, 0x00B4, 0x00B3, 0x00BA, 0x00BD,
    0x00C7, 0x00C0, 0x00C9, 0x00CE, 0x00DB, 0x00DC, 0x00D5, 0x00D2,
    0x00FF, 0x00F8, 0x00F1, 0x00F6, 0x00E3, 0x00E4, 0x00ED, 0x00EA,
    0x00B7, 0x00B0, 0x00B9, 0x00BE, 0x00AB, 0x00AC, 0x00A5, 0x00A2,
    0x008F, 0x0088, 0x0081, 0x0086, 0x0093, 0x0094, 0x009D, 0x009A,
    0x0027, 0x0020, 0x0029, 0x002E, 0x003B, 0x003C, 0x0035, 0x0032,
    0x001F, 0x0018, 0x0011, 0x0016, 0x0003, 0x0004, 0x000D, 0x000A,
    0x0057, 0x0050, 0x0059, 0x005E, 0x004B, 0x004C, 0x0045, 0x0042,
    0x006F, 0x0068, 0x0061, 0x0066, 0x0073, 0x0074, 0x007D, 0x007A,
    0x0089, 0x008E, 0x0087, 0x0080, 0x0095, 0x0092, 0x009B, 0x009C,
    0x00B1, 0x00B6, 0x00BF, 0x00B8, 0x00AD, 0x00AA, 0x00A3, 0x00A4,
    0x00F9, 0x00FE, 0x00F7, 0x00F0, 0x00E5, 0x00E2, 0x00EB, 0x00EC,
    0x00C1, 0x00C6, 0x00CF, 0x00C8, 0x00DD, 0x00DA, 0x00D3, 0x00D4,
    0x0069, 0x006E, 0x0067, 0x0060, 0x0075, 0x0072, 0x007B, 0x007C,
    0x0051, 0x0056, 0x005F, 0x0058, 0x004D, 0x004A, 0x0043, 0x0044,
    0x0019, 0x001E, 0x0017, 0x0010, 0x0005, 0x0002, 0x000B, 0x000C,
    0x0021, 0x0026, 0x002F, 0x0028, 0x003D, 0x003A, 0x0033, 0x0034,
    0x004E, 0x0049, 0x0040, 0x0047, 0x0052, 0x0055, 0x005C, 0x005B,
    0x0076, 0x0071, 0x0078, 0x007F, 0x006A, 0x006D, 0x0064, 0x0063,
    0x003E, 0x0039, 0x0030, 0x0037, 0x0022, 0x0025, 0x002C, 0x002B,
    0x0006, 0x0001, 0x0008, 0x000F, 0x001A, 0x001D, 0x0014, 0x0013,
    0x00AE, 0x00A9, 0x00A0, 0x00A7, 0x00B2, 0x00B5, 0x00BC, 0x00BB,
    0x0096, 0x0091, 0x0098, 0x009F, 0x008A, 0x008D, 0x0084, 0x0083,
    0x00DE, 0x00D9, 0x00D0, 0x00D7, 0x00C2, 0x00C5, 0x00CC, 0x00CB,
    0x00E6, 0x00E1, 0x00E8, 0x00EF, 0x00FA, 0x00FD, 0x00F4, 0x00F3,
};

//
// End of File
//

