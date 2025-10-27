// TI File $Revision: /main/3 $
// Checkin $Date: November 10, 2009   14:05:03 $
//###########################################################################
//
// FILE:   mem_wrapper_defines.h
//
//
//###########################################################################
// 
// C2000Ware v6.00.01.00
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
//###########################################################################
#ifndef F2838x_MEMCTRL_DEFINES_H
#define F2838x_MEMCTRL_DEFINES_H
#define FPGA

//#define PASS      0xABCDABCD
//#define FAIL      0xDEADDEAD
#define TEST_DONE 0x13579BDF

#define M0_START_ADDR 0x00000
#define M1_START_ADDR 0x00400

#define D0_START_ADDR 0x0C000
#define D1_START_ADDR 0x0C800

#define LS0_START_ADDR 0x08000
#define LS1_START_ADDR 0x08800
#define LS2_START_ADDR 0x09000
#define LS3_START_ADDR 0x09800
#define LS4_START_ADDR 0x0A000
#define LS5_START_ADDR 0x0A800
#define LS6_START_ADDR 0x0B000
#define LS7_START_ADDR 0x0B800

#define GS0_START_ADDR  0x0D000
#define GS1_START_ADDR  0x0E000
#define GS2_START_ADDR  0x0F000
#define GS3_START_ADDR  0x10000
#define GS4_START_ADDR  0x11000
#define GS5_START_ADDR  0x12000
#define GS6_START_ADDR  0x13000
#define GS7_START_ADDR  0x14000
#define GS8_START_ADDR  0x15000
#define GS9_START_ADDR  0x16000
#define GS10_START_ADDR 0x17000
#define GS11_START_ADDR 0x18000
#define GS12_START_ADDR 0x19000
#define GS13_START_ADDR 0x1A000
#define GS14_START_ADDR 0x1B000
#define GS15_START_ADDR 0x1C000

#define CPU1TOCPU2MSGRAM_START_ADDR 0x3A000
#define CPU1TOCPU2MSGRAM_END_ADDR 0x3A7FF
#define CPU2TOCPU1MSGRAM_START_ADDR 0x3B000
#define CPU2TOCPU1MSGRAM_END_ADDR 0x3B7FF

#define CMTOCPU1MSGRAM_START_ADDR 0x38000
#define CMTOCPU1MSGRAM_END_ADDR 0x383FF
#define CPU1TOCMMSGRAM_START_ADDR 0x38400
#define CPU1TOCMMSGRAM_END_ADDR 0x387FF

#define CPUTOCLA1MSGRAM_START_ADDR 0x1500
#define CPUTOCLA1MSGRAM_END_ADDR 0x157F
#define CLA1TOCPUMSGRAM_START_ADDR 0x1480
#define CLA1TOCPUMSGRAM_END_ADDR 0x14FF

#endif
//===========================================================================
// End of file.
//===========================================================================
