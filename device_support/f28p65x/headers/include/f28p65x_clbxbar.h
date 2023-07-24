//###########################################################################
//
// FILE:    f28p65x_clbxbar.h
//
// TITLE:   Definitions for the CLBXBAR registers.
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

#ifndef F28P65X_CLBXBAR_H
#define F28P65X_CLBXBAR_H

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// CLBXBAR Individual Register Bit Definitions:

struct AUXSIG0MUX0TO15CFG_BITS {        // bits description
    Uint16 MUX0:2;                      // 1:0 MUX0 Configuration for AUXSIG0 of CLB-XBAR
    Uint16 MUX1:2;                      // 3:2 MUX1 Configuration for AUXSIG0 of CLB-XBAR
    Uint16 MUX2:2;                      // 5:4 MUX2 Configuration for AUXSIG0 of CLB-XBAR
    Uint16 MUX3:2;                      // 7:6 MUX3 Configuration for AUXSIG0 of CLB-XBAR
    Uint16 MUX4:2;                      // 9:8 MUX4 Configuration for AUXSIG0 of CLB-XBAR
    Uint16 MUX5:2;                      // 11:10 MUX5 Configuration for AUXSIG0 of CLB-XBAR
    Uint16 MUX6:2;                      // 13:12 MUX6 Configuration for AUXSIG0 of CLB-XBAR
    Uint16 MUX7:2;                      // 15:14 MUX7 Configuration for AUXSIG0 of CLB-XBAR
    Uint16 MUX8:2;                      // 17:16 MUX8 Configuration for AUXSIG0 of CLB-XBAR
    Uint16 MUX9:2;                      // 19:18 MUX9 Configuration for AUXSIG0 of CLB-XBAR
    Uint16 MUX10:2;                     // 21:20 MUX10 Configuration for AUXSIG0 of CLB-XBAR
    Uint16 MUX11:2;                     // 23:22 MUX11 Configuration for AUXSIG0 of CLB-XBAR
    Uint16 MUX12:2;                     // 25:24 MUX12 Configuration for AUXSIG0 of CLB-XBAR
    Uint16 MUX13:2;                     // 27:26 MUX13 Configuration for AUXSIG0 of CLB-XBAR
    Uint16 MUX14:2;                     // 29:28 MUX14 Configuration for AUXSIG0 of CLB-XBAR
    Uint16 MUX15:2;                     // 31:30 MUX15 Configuration for AUXSIG0 of CLB-XBAR
};

union AUXSIG0MUX0TO15CFG_REG {
    Uint32  all;
    struct  AUXSIG0MUX0TO15CFG_BITS  bit;
};

struct AUXSIG0MUX16TO31CFG_BITS {       // bits description
    Uint16 MUX16:2;                     // 1:0 MUX16 Configuration for AUXSIG0 of CLB-XBAR
    Uint16 MUX17:2;                     // 3:2 MUX17 Configuration for AUXSIG0 of CLB-XBAR
    Uint16 MUX18:2;                     // 5:4 MUX18 Configuration for AUXSIG0 of CLB-XBAR
    Uint16 MUX19:2;                     // 7:6 MUX19 Configuration for AUXSIG0 of CLB-XBAR
    Uint16 MUX20:2;                     // 9:8 MUX20 Configuration for AUXSIG0 of CLB-XBAR
    Uint16 MUX21:2;                     // 11:10 MUX21 Configuration for AUXSIG0 of CLB-XBAR
    Uint16 MUX22:2;                     // 13:12 MUX22 Configuration for AUXSIG0 of CLB-XBAR
    Uint16 MUX23:2;                     // 15:14 MUX23 Configuration for AUXSIG0 of CLB-XBAR
    Uint16 MUX24:2;                     // 17:16 MUX24 Configuration for AUXSIG0 of CLB-XBAR
    Uint16 MUX25:2;                     // 19:18 MUX25 Configuration for AUXSIG0 of CLB-XBAR
    Uint16 MUX26:2;                     // 21:20 MUX26 Configuration for AUXSIG0 of CLB-XBAR
    Uint16 MUX27:2;                     // 23:22 MUX27 Configuration for AUXSIG0 of CLB-XBAR
    Uint16 MUX28:2;                     // 25:24 MUX28 Configuration for AUXSIG0 of CLB-XBAR
    Uint16 MUX29:2;                     // 27:26 MUX29 Configuration for AUXSIG0 of CLB-XBAR
    Uint16 MUX30:2;                     // 29:28 MUX30 Configuration for AUXSIG0 of CLB-XBAR
    Uint16 MUX31:2;                     // 31:30 MUX31 Configuration for AUXSIG0 of CLB-XBAR
};

union AUXSIG0MUX16TO31CFG_REG {
    Uint32  all;
    struct  AUXSIG0MUX16TO31CFG_BITS  bit;
};

struct AUXSIG1MUX0TO15CFG_BITS {        // bits description
    Uint16 MUX0:2;                      // 1:0 MUX0 Configuration for AUXSIG1 of CLB-XBAR
    Uint16 MUX1:2;                      // 3:2 MUX1 Configuration for AUXSIG1 of CLB-XBAR
    Uint16 MUX2:2;                      // 5:4 MUX2 Configuration for AUXSIG1 of CLB-XBAR
    Uint16 MUX3:2;                      // 7:6 MUX3 Configuration for AUXSIG1 of CLB-XBAR
    Uint16 MUX4:2;                      // 9:8 MUX4 Configuration for AUXSIG1 of CLB-XBAR
    Uint16 MUX5:2;                      // 11:10 MUX5 Configuration for AUXSIG1 of CLB-XBAR
    Uint16 MUX6:2;                      // 13:12 MUX6 Configuration for AUXSIG1 of CLB-XBAR
    Uint16 MUX7:2;                      // 15:14 MUX7 Configuration for AUXSIG1 of CLB-XBAR
    Uint16 MUX8:2;                      // 17:16 MUX8 Configuration for AUXSIG1 of CLB-XBAR
    Uint16 MUX9:2;                      // 19:18 MUX9 Configuration for AUXSIG1 of CLB-XBAR
    Uint16 MUX10:2;                     // 21:20 MUX10 Configuration for AUXSIG1 of CLB-XBAR
    Uint16 MUX11:2;                     // 23:22 MUX11 Configuration for AUXSIG1 of CLB-XBAR
    Uint16 MUX12:2;                     // 25:24 MUX12 Configuration for AUXSIG1 of CLB-XBAR
    Uint16 MUX13:2;                     // 27:26 MUX13 Configuration for AUXSIG1 of CLB-XBAR
    Uint16 MUX14:2;                     // 29:28 MUX14 Configuration for AUXSIG1 of CLB-XBAR
    Uint16 MUX15:2;                     // 31:30 MUX15 Configuration for AUXSIG1 of CLB-XBAR
};

union AUXSIG1MUX0TO15CFG_REG {
    Uint32  all;
    struct  AUXSIG1MUX0TO15CFG_BITS  bit;
};

struct AUXSIG1MUX16TO31CFG_BITS {       // bits description
    Uint16 MUX16:2;                     // 1:0 MUX16 Configuration for AUXSIG1 of CLB-XBAR
    Uint16 MUX17:2;                     // 3:2 MUX17 Configuration for AUXSIG1 of CLB-XBAR
    Uint16 MUX18:2;                     // 5:4 MUX18 Configuration for AUXSIG1 of CLB-XBAR
    Uint16 MUX19:2;                     // 7:6 MUX19 Configuration for AUXSIG1 of CLB-XBAR
    Uint16 MUX20:2;                     // 9:8 MUX20 Configuration for AUXSIG1 of CLB-XBAR
    Uint16 MUX21:2;                     // 11:10 MUX21 Configuration for AUXSIG1 of CLB-XBAR
    Uint16 MUX22:2;                     // 13:12 MUX22 Configuration for AUXSIG1 of CLB-XBAR
    Uint16 MUX23:2;                     // 15:14 MUX23 Configuration for AUXSIG1 of CLB-XBAR
    Uint16 MUX24:2;                     // 17:16 MUX24 Configuration for AUXSIG1 of CLB-XBAR
    Uint16 MUX25:2;                     // 19:18 MUX25 Configuration for AUXSIG1 of CLB-XBAR
    Uint16 MUX26:2;                     // 21:20 MUX26 Configuration for AUXSIG1 of CLB-XBAR
    Uint16 MUX27:2;                     // 23:22 MUX27 Configuration for AUXSIG1 of CLB-XBAR
    Uint16 MUX28:2;                     // 25:24 MUX28 Configuration for AUXSIG1 of CLB-XBAR
    Uint16 MUX29:2;                     // 27:26 MUX29 Configuration for AUXSIG1 of CLB-XBAR
    Uint16 MUX30:2;                     // 29:28 MUX30 Configuration for AUXSIG1 of CLB-XBAR
    Uint16 MUX31:2;                     // 31:30 MUX31 Configuration for AUXSIG1 of CLB-XBAR
};

union AUXSIG1MUX16TO31CFG_REG {
    Uint32  all;
    struct  AUXSIG1MUX16TO31CFG_BITS  bit;
};

struct AUXSIG2MUX0TO15CFG_BITS {        // bits description
    Uint16 MUX0:2;                      // 1:0 MUX0 Configuration for AUXSIG2 of CLB-XBAR
    Uint16 MUX1:2;                      // 3:2 MUX1 Configuration for AUXSIG2 of CLB-XBAR
    Uint16 MUX2:2;                      // 5:4 MUX2 Configuration for AUXSIG2 of CLB-XBAR
    Uint16 MUX3:2;                      // 7:6 MUX3 Configuration for AUXSIG2 of CLB-XBAR
    Uint16 MUX4:2;                      // 9:8 MUX4 Configuration for AUXSIG2 of CLB-XBAR
    Uint16 MUX5:2;                      // 11:10 MUX5 Configuration for AUXSIG2 of CLB-XBAR
    Uint16 MUX6:2;                      // 13:12 MUX6 Configuration for AUXSIG2 of CLB-XBAR
    Uint16 MUX7:2;                      // 15:14 MUX7 Configuration for AUXSIG2 of CLB-XBAR
    Uint16 MUX8:2;                      // 17:16 MUX8 Configuration for AUXSIG2 of CLB-XBAR
    Uint16 MUX9:2;                      // 19:18 MUX9 Configuration for AUXSIG2 of CLB-XBAR
    Uint16 MUX10:2;                     // 21:20 MUX10 Configuration for AUXSIG2 of CLB-XBAR
    Uint16 MUX11:2;                     // 23:22 MUX11 Configuration for AUXSIG2 of CLB-XBAR
    Uint16 MUX12:2;                     // 25:24 MUX12 Configuration for AUXSIG2 of CLB-XBAR
    Uint16 MUX13:2;                     // 27:26 MUX13 Configuration for AUXSIG2 of CLB-XBAR
    Uint16 MUX14:2;                     // 29:28 MUX14 Configuration for AUXSIG2 of CLB-XBAR
    Uint16 MUX15:2;                     // 31:30 MUX15 Configuration for AUXSIG2 of CLB-XBAR
};

union AUXSIG2MUX0TO15CFG_REG {
    Uint32  all;
    struct  AUXSIG2MUX0TO15CFG_BITS  bit;
};

struct AUXSIG2MUX16TO31CFG_BITS {       // bits description
    Uint16 MUX16:2;                     // 1:0 MUX16 Configuration for AUXSIG2 of CLB-XBAR
    Uint16 MUX17:2;                     // 3:2 MUX17 Configuration for AUXSIG2 of CLB-XBAR
    Uint16 MUX18:2;                     // 5:4 MUX18 Configuration for AUXSIG2 of CLB-XBAR
    Uint16 MUX19:2;                     // 7:6 MUX19 Configuration for AUXSIG2 of CLB-XBAR
    Uint16 MUX20:2;                     // 9:8 MUX20 Configuration for AUXSIG2 of CLB-XBAR
    Uint16 MUX21:2;                     // 11:10 MUX21 Configuration for AUXSIG2 of CLB-XBAR
    Uint16 MUX22:2;                     // 13:12 MUX22 Configuration for AUXSIG2 of CLB-XBAR
    Uint16 MUX23:2;                     // 15:14 MUX23 Configuration for AUXSIG2 of CLB-XBAR
    Uint16 MUX24:2;                     // 17:16 MUX24 Configuration for AUXSIG2 of CLB-XBAR
    Uint16 MUX25:2;                     // 19:18 MUX25 Configuration for AUXSIG2 of CLB-XBAR
    Uint16 MUX26:2;                     // 21:20 MUX26 Configuration for AUXSIG2 of CLB-XBAR
    Uint16 MUX27:2;                     // 23:22 MUX27 Configuration for AUXSIG2 of CLB-XBAR
    Uint16 MUX28:2;                     // 25:24 MUX28 Configuration for AUXSIG2 of CLB-XBAR
    Uint16 MUX29:2;                     // 27:26 MUX29 Configuration for AUXSIG2 of CLB-XBAR
    Uint16 MUX30:2;                     // 29:28 MUX30 Configuration for AUXSIG2 of CLB-XBAR
    Uint16 MUX31:2;                     // 31:30 MUX31 Configuration for AUXSIG2 of CLB-XBAR
};

union AUXSIG2MUX16TO31CFG_REG {
    Uint32  all;
    struct  AUXSIG2MUX16TO31CFG_BITS  bit;
};

struct AUXSIG3MUX0TO15CFG_BITS {        // bits description
    Uint16 MUX0:2;                      // 1:0 MUX0 Configuration for AUXSIG3 of CLB-XBAR
    Uint16 MUX1:2;                      // 3:2 MUX1 Configuration for AUXSIG3 of CLB-XBAR
    Uint16 MUX2:2;                      // 5:4 MUX2 Configuration for AUXSIG3 of CLB-XBAR
    Uint16 MUX3:2;                      // 7:6 MUX3 Configuration for AUXSIG3 of CLB-XBAR
    Uint16 MUX4:2;                      // 9:8 MUX4 Configuration for AUXSIG3 of CLB-XBAR
    Uint16 MUX5:2;                      // 11:10 MUX5 Configuration for AUXSIG3 of CLB-XBAR
    Uint16 MUX6:2;                      // 13:12 MUX6 Configuration for AUXSIG3 of CLB-XBAR
    Uint16 MUX7:2;                      // 15:14 MUX7 Configuration for AUXSIG3 of CLB-XBAR
    Uint16 MUX8:2;                      // 17:16 MUX8 Configuration for AUXSIG3 of CLB-XBAR
    Uint16 MUX9:2;                      // 19:18 MUX9 Configuration for AUXSIG3 of CLB-XBAR
    Uint16 MUX10:2;                     // 21:20 MUX10 Configuration for AUXSIG3 of CLB-XBAR
    Uint16 MUX11:2;                     // 23:22 MUX11 Configuration for AUXSIG3 of CLB-XBAR
    Uint16 MUX12:2;                     // 25:24 MUX12 Configuration for AUXSIG3 of CLB-XBAR
    Uint16 MUX13:2;                     // 27:26 MUX13 Configuration for AUXSIG3 of CLB-XBAR
    Uint16 MUX14:2;                     // 29:28 MUX14 Configuration for AUXSIG3 of CLB-XBAR
    Uint16 MUX15:2;                     // 31:30 MUX15 Configuration for AUXSIG3 of CLB-XBAR
};

union AUXSIG3MUX0TO15CFG_REG {
    Uint32  all;
    struct  AUXSIG3MUX0TO15CFG_BITS  bit;
};

struct AUXSIG3MUX16TO31CFG_BITS {       // bits description
    Uint16 MUX16:2;                     // 1:0 MUX16 Configuration for AUXSIG3 of CLB-XBAR
    Uint16 MUX17:2;                     // 3:2 MUX17 Configuration for AUXSIG3 of CLB-XBAR
    Uint16 MUX18:2;                     // 5:4 MUX18 Configuration for AUXSIG3 of CLB-XBAR
    Uint16 MUX19:2;                     // 7:6 MUX19 Configuration for AUXSIG3 of CLB-XBAR
    Uint16 MUX20:2;                     // 9:8 MUX20 Configuration for AUXSIG3 of CLB-XBAR
    Uint16 MUX21:2;                     // 11:10 MUX21 Configuration for AUXSIG3 of CLB-XBAR
    Uint16 MUX22:2;                     // 13:12 MUX22 Configuration for AUXSIG3 of CLB-XBAR
    Uint16 MUX23:2;                     // 15:14 MUX23 Configuration for AUXSIG3 of CLB-XBAR
    Uint16 MUX24:2;                     // 17:16 MUX24 Configuration for AUXSIG3 of CLB-XBAR
    Uint16 MUX25:2;                     // 19:18 MUX25 Configuration for AUXSIG3 of CLB-XBAR
    Uint16 MUX26:2;                     // 21:20 MUX26 Configuration for AUXSIG3 of CLB-XBAR
    Uint16 MUX27:2;                     // 23:22 MUX27 Configuration for AUXSIG3 of CLB-XBAR
    Uint16 MUX28:2;                     // 25:24 MUX28 Configuration for AUXSIG3 of CLB-XBAR
    Uint16 MUX29:2;                     // 27:26 MUX29 Configuration for AUXSIG3 of CLB-XBAR
    Uint16 MUX30:2;                     // 29:28 MUX30 Configuration for AUXSIG3 of CLB-XBAR
    Uint16 MUX31:2;                     // 31:30 MUX31 Configuration for AUXSIG3 of CLB-XBAR
};

union AUXSIG3MUX16TO31CFG_REG {
    Uint32  all;
    struct  AUXSIG3MUX16TO31CFG_BITS  bit;
};

struct AUXSIG4MUX0TO15CFG_BITS {        // bits description
    Uint16 MUX0:2;                      // 1:0 MUX0 Configuration for AUXSIG4 of CLB-XBAR
    Uint16 MUX1:2;                      // 3:2 MUX1 Configuration for AUXSIG4 of CLB-XBAR
    Uint16 MUX2:2;                      // 5:4 MUX2 Configuration for AUXSIG4 of CLB-XBAR
    Uint16 MUX3:2;                      // 7:6 MUX3 Configuration for AUXSIG4 of CLB-XBAR
    Uint16 MUX4:2;                      // 9:8 MUX4 Configuration for AUXSIG4 of CLB-XBAR
    Uint16 MUX5:2;                      // 11:10 MUX5 Configuration for AUXSIG4 of CLB-XBAR
    Uint16 MUX6:2;                      // 13:12 MUX6 Configuration for AUXSIG4 of CLB-XBAR
    Uint16 MUX7:2;                      // 15:14 MUX7 Configuration for AUXSIG4 of CLB-XBAR
    Uint16 MUX8:2;                      // 17:16 MUX8 Configuration for AUXSIG4 of CLB-XBAR
    Uint16 MUX9:2;                      // 19:18 MUX9 Configuration for AUXSIG4 of CLB-XBAR
    Uint16 MUX10:2;                     // 21:20 MUX10 Configuration for AUXSIG4 of CLB-XBAR
    Uint16 MUX11:2;                     // 23:22 MUX11 Configuration for AUXSIG4 of CLB-XBAR
    Uint16 MUX12:2;                     // 25:24 MUX12 Configuration for AUXSIG4 of CLB-XBAR
    Uint16 MUX13:2;                     // 27:26 MUX13 Configuration for AUXSIG4 of CLB-XBAR
    Uint16 MUX14:2;                     // 29:28 MUX14 Configuration for AUXSIG4 of CLB-XBAR
    Uint16 MUX15:2;                     // 31:30 MUX15 Configuration for AUXSIG4 of CLB-XBAR
};

union AUXSIG4MUX0TO15CFG_REG {
    Uint32  all;
    struct  AUXSIG4MUX0TO15CFG_BITS  bit;
};

struct AUXSIG4MUX16TO31CFG_BITS {       // bits description
    Uint16 MUX16:2;                     // 1:0 MUX16 Configuration for AUXSIG4 of CLB-XBAR
    Uint16 MUX17:2;                     // 3:2 MUX17 Configuration for AUXSIG4 of CLB-XBAR
    Uint16 MUX18:2;                     // 5:4 MUX18 Configuration for AUXSIG4 of CLB-XBAR
    Uint16 MUX19:2;                     // 7:6 MUX19 Configuration for AUXSIG4 of CLB-XBAR
    Uint16 MUX20:2;                     // 9:8 MUX20 Configuration for AUXSIG4 of CLB-XBAR
    Uint16 MUX21:2;                     // 11:10 MUX21 Configuration for AUXSIG4 of CLB-XBAR
    Uint16 MUX22:2;                     // 13:12 MUX22 Configuration for AUXSIG4 of CLB-XBAR
    Uint16 MUX23:2;                     // 15:14 MUX23 Configuration for AUXSIG4 of CLB-XBAR
    Uint16 MUX24:2;                     // 17:16 MUX24 Configuration for AUXSIG4 of CLB-XBAR
    Uint16 MUX25:2;                     // 19:18 MUX25 Configuration for AUXSIG4 of CLB-XBAR
    Uint16 MUX26:2;                     // 21:20 MUX26 Configuration for AUXSIG4 of CLB-XBAR
    Uint16 MUX27:2;                     // 23:22 MUX27 Configuration for AUXSIG4 of CLB-XBAR
    Uint16 MUX28:2;                     // 25:24 MUX28 Configuration for AUXSIG4 of CLB-XBAR
    Uint16 MUX29:2;                     // 27:26 MUX29 Configuration for AUXSIG4 of CLB-XBAR
    Uint16 MUX30:2;                     // 29:28 MUX30 Configuration for AUXSIG4 of CLB-XBAR
    Uint16 MUX31:2;                     // 31:30 MUX31 Configuration for AUXSIG4 of CLB-XBAR
};

union AUXSIG4MUX16TO31CFG_REG {
    Uint32  all;
    struct  AUXSIG4MUX16TO31CFG_BITS  bit;
};

struct AUXSIG5MUX0TO15CFG_BITS {        // bits description
    Uint16 MUX0:2;                      // 1:0 MUX0 Configuration for AUXSIG5 of CLB-XBAR
    Uint16 MUX1:2;                      // 3:2 MUX1 Configuration for AUXSIG5 of CLB-XBAR
    Uint16 MUX2:2;                      // 5:4 MUX2 Configuration for AUXSIG5 of CLB-XBAR
    Uint16 MUX3:2;                      // 7:6 MUX3 Configuration for AUXSIG5 of CLB-XBAR
    Uint16 MUX4:2;                      // 9:8 MUX4 Configuration for AUXSIG5 of CLB-XBAR
    Uint16 MUX5:2;                      // 11:10 MUX5 Configuration for AUXSIG5 of CLB-XBAR
    Uint16 MUX6:2;                      // 13:12 MUX6 Configuration for AUXSIG5 of CLB-XBAR
    Uint16 MUX7:2;                      // 15:14 MUX7 Configuration for AUXSIG5 of CLB-XBAR
    Uint16 MUX8:2;                      // 17:16 MUX8 Configuration for AUXSIG5 of CLB-XBAR
    Uint16 MUX9:2;                      // 19:18 MUX9 Configuration for AUXSIG5 of CLB-XBAR
    Uint16 MUX10:2;                     // 21:20 MUX10 Configuration for AUXSIG5 of CLB-XBAR
    Uint16 MUX11:2;                     // 23:22 MUX11 Configuration for AUXSIG5 of CLB-XBAR
    Uint16 MUX12:2;                     // 25:24 MUX12 Configuration for AUXSIG5 of CLB-XBAR
    Uint16 MUX13:2;                     // 27:26 MUX13 Configuration for AUXSIG5 of CLB-XBAR
    Uint16 MUX14:2;                     // 29:28 MUX14 Configuration for AUXSIG5 of CLB-XBAR
    Uint16 MUX15:2;                     // 31:30 MUX15 Configuration for AUXSIG5 of CLB-XBAR
};

union AUXSIG5MUX0TO15CFG_REG {
    Uint32  all;
    struct  AUXSIG5MUX0TO15CFG_BITS  bit;
};

struct AUXSIG5MUX16TO31CFG_BITS {       // bits description
    Uint16 MUX16:2;                     // 1:0 MUX16 Configuration for AUXSIG5 of CLB-XBAR
    Uint16 MUX17:2;                     // 3:2 MUX17 Configuration for AUXSIG5 of CLB-XBAR
    Uint16 MUX18:2;                     // 5:4 MUX18 Configuration for AUXSIG5 of CLB-XBAR
    Uint16 MUX19:2;                     // 7:6 MUX19 Configuration for AUXSIG5 of CLB-XBAR
    Uint16 MUX20:2;                     // 9:8 MUX20 Configuration for AUXSIG5 of CLB-XBAR
    Uint16 MUX21:2;                     // 11:10 MUX21 Configuration for AUXSIG5 of CLB-XBAR
    Uint16 MUX22:2;                     // 13:12 MUX22 Configuration for AUXSIG5 of CLB-XBAR
    Uint16 MUX23:2;                     // 15:14 MUX23 Configuration for AUXSIG5 of CLB-XBAR
    Uint16 MUX24:2;                     // 17:16 MUX24 Configuration for AUXSIG5 of CLB-XBAR
    Uint16 MUX25:2;                     // 19:18 MUX25 Configuration for AUXSIG5 of CLB-XBAR
    Uint16 MUX26:2;                     // 21:20 MUX26 Configuration for AUXSIG5 of CLB-XBAR
    Uint16 MUX27:2;                     // 23:22 MUX27 Configuration for AUXSIG5 of CLB-XBAR
    Uint16 MUX28:2;                     // 25:24 MUX28 Configuration for AUXSIG5 of CLB-XBAR
    Uint16 MUX29:2;                     // 27:26 MUX29 Configuration for AUXSIG5 of CLB-XBAR
    Uint16 MUX30:2;                     // 29:28 MUX30 Configuration for AUXSIG5 of CLB-XBAR
    Uint16 MUX31:2;                     // 31:30 MUX31 Configuration for AUXSIG5 of CLB-XBAR
};

union AUXSIG5MUX16TO31CFG_REG {
    Uint32  all;
    struct  AUXSIG5MUX16TO31CFG_BITS  bit;
};

struct AUXSIG6MUX0TO15CFG_BITS {        // bits description
    Uint16 MUX0:2;                      // 1:0 MUX0 Configuration for AUXSIG6 of CLB-XBAR
    Uint16 MUX1:2;                      // 3:2 MUX1 Configuration for AUXSIG6 of CLB-XBAR
    Uint16 MUX2:2;                      // 5:4 MUX2 Configuration for AUXSIG6 of CLB-XBAR
    Uint16 MUX3:2;                      // 7:6 MUX3 Configuration for AUXSIG6 of CLB-XBAR
    Uint16 MUX4:2;                      // 9:8 MUX4 Configuration for AUXSIG6 of CLB-XBAR
    Uint16 MUX5:2;                      // 11:10 MUX5 Configuration for AUXSIG6 of CLB-XBAR
    Uint16 MUX6:2;                      // 13:12 MUX6 Configuration for AUXSIG6 of CLB-XBAR
    Uint16 MUX7:2;                      // 15:14 MUX7 Configuration for AUXSIG6 of CLB-XBAR
    Uint16 MUX8:2;                      // 17:16 MUX8 Configuration for AUXSIG6 of CLB-XBAR
    Uint16 MUX9:2;                      // 19:18 MUX9 Configuration for AUXSIG6 of CLB-XBAR
    Uint16 MUX10:2;                     // 21:20 MUX10 Configuration for AUXSIG6 of CLB-XBAR
    Uint16 MUX11:2;                     // 23:22 MUX11 Configuration for AUXSIG6 of CLB-XBAR
    Uint16 MUX12:2;                     // 25:24 MUX12 Configuration for AUXSIG6 of CLB-XBAR
    Uint16 MUX13:2;                     // 27:26 MUX13 Configuration for AUXSIG6 of CLB-XBAR
    Uint16 MUX14:2;                     // 29:28 MUX14 Configuration for AUXSIG6 of CLB-XBAR
    Uint16 MUX15:2;                     // 31:30 MUX15 Configuration for AUXSIG6 of CLB-XBAR
};

union AUXSIG6MUX0TO15CFG_REG {
    Uint32  all;
    struct  AUXSIG6MUX0TO15CFG_BITS  bit;
};

struct AUXSIG6MUX16TO31CFG_BITS {       // bits description
    Uint16 MUX16:2;                     // 1:0 MUX16 Configuration for AUXSIG6 of CLB-XBAR
    Uint16 MUX17:2;                     // 3:2 MUX17 Configuration for AUXSIG6 of CLB-XBAR
    Uint16 MUX18:2;                     // 5:4 MUX18 Configuration for AUXSIG6 of CLB-XBAR
    Uint16 MUX19:2;                     // 7:6 MUX19 Configuration for AUXSIG6 of CLB-XBAR
    Uint16 MUX20:2;                     // 9:8 MUX20 Configuration for AUXSIG6 of CLB-XBAR
    Uint16 MUX21:2;                     // 11:10 MUX21 Configuration for AUXSIG6 of CLB-XBAR
    Uint16 MUX22:2;                     // 13:12 MUX22 Configuration for AUXSIG6 of CLB-XBAR
    Uint16 MUX23:2;                     // 15:14 MUX23 Configuration for AUXSIG6 of CLB-XBAR
    Uint16 MUX24:2;                     // 17:16 MUX24 Configuration for AUXSIG6 of CLB-XBAR
    Uint16 MUX25:2;                     // 19:18 MUX25 Configuration for AUXSIG6 of CLB-XBAR
    Uint16 MUX26:2;                     // 21:20 MUX26 Configuration for AUXSIG6 of CLB-XBAR
    Uint16 MUX27:2;                     // 23:22 MUX27 Configuration for AUXSIG6 of CLB-XBAR
    Uint16 MUX28:2;                     // 25:24 MUX28 Configuration for AUXSIG6 of CLB-XBAR
    Uint16 MUX29:2;                     // 27:26 MUX29 Configuration for AUXSIG6 of CLB-XBAR
    Uint16 MUX30:2;                     // 29:28 MUX30 Configuration for AUXSIG6 of CLB-XBAR
    Uint16 MUX31:2;                     // 31:30 MUX31 Configuration for AUXSIG6 of CLB-XBAR
};

union AUXSIG6MUX16TO31CFG_REG {
    Uint32  all;
    struct  AUXSIG6MUX16TO31CFG_BITS  bit;
};

struct AUXSIG7MUX0TO15CFG_BITS {        // bits description
    Uint16 MUX0:2;                      // 1:0 MUX0 Configuration for AUXSIG7 of CLB-XBAR
    Uint16 MUX1:2;                      // 3:2 MUX1 Configuration for AUXSIG7 of CLB-XBAR
    Uint16 MUX2:2;                      // 5:4 MUX2 Configuration for AUXSIG7 of CLB-XBAR
    Uint16 MUX3:2;                      // 7:6 MUX3 Configuration for AUXSIG7 of CLB-XBAR
    Uint16 MUX4:2;                      // 9:8 MUX4 Configuration for AUXSIG7 of CLB-XBAR
    Uint16 MUX5:2;                      // 11:10 MUX5 Configuration for AUXSIG7 of CLB-XBAR
    Uint16 MUX6:2;                      // 13:12 MUX6 Configuration for AUXSIG7 of CLB-XBAR
    Uint16 MUX7:2;                      // 15:14 MUX7 Configuration for AUXSIG7 of CLB-XBAR
    Uint16 MUX8:2;                      // 17:16 MUX8 Configuration for AUXSIG7 of CLB-XBAR
    Uint16 MUX9:2;                      // 19:18 MUX9 Configuration for AUXSIG7 of CLB-XBAR
    Uint16 MUX10:2;                     // 21:20 MUX10 Configuration for AUXSIG7 of CLB-XBAR
    Uint16 MUX11:2;                     // 23:22 MUX11 Configuration for AUXSIG7 of CLB-XBAR
    Uint16 MUX12:2;                     // 25:24 MUX12 Configuration for AUXSIG7 of CLB-XBAR
    Uint16 MUX13:2;                     // 27:26 MUX13 Configuration for AUXSIG7 of CLB-XBAR
    Uint16 MUX14:2;                     // 29:28 MUX14 Configuration for AUXSIG7 of CLB-XBAR
    Uint16 MUX15:2;                     // 31:30 MUX15 Configuration for AUXSIG7 of CLB-XBAR
};

union AUXSIG7MUX0TO15CFG_REG {
    Uint32  all;
    struct  AUXSIG7MUX0TO15CFG_BITS  bit;
};

struct AUXSIG7MUX16TO31CFG_BITS {       // bits description
    Uint16 MUX16:2;                     // 1:0 MUX16 Configuration for AUXSIG7 of CLB-XBAR
    Uint16 MUX17:2;                     // 3:2 MUX17 Configuration for AUXSIG7 of CLB-XBAR
    Uint16 MUX18:2;                     // 5:4 MUX18 Configuration for AUXSIG7 of CLB-XBAR
    Uint16 MUX19:2;                     // 7:6 MUX19 Configuration for AUXSIG7 of CLB-XBAR
    Uint16 MUX20:2;                     // 9:8 MUX20 Configuration for AUXSIG7 of CLB-XBAR
    Uint16 MUX21:2;                     // 11:10 MUX21 Configuration for AUXSIG7 of CLB-XBAR
    Uint16 MUX22:2;                     // 13:12 MUX22 Configuration for AUXSIG7 of CLB-XBAR
    Uint16 MUX23:2;                     // 15:14 MUX23 Configuration for AUXSIG7 of CLB-XBAR
    Uint16 MUX24:2;                     // 17:16 MUX24 Configuration for AUXSIG7 of CLB-XBAR
    Uint16 MUX25:2;                     // 19:18 MUX25 Configuration for AUXSIG7 of CLB-XBAR
    Uint16 MUX26:2;                     // 21:20 MUX26 Configuration for AUXSIG7 of CLB-XBAR
    Uint16 MUX27:2;                     // 23:22 MUX27 Configuration for AUXSIG7 of CLB-XBAR
    Uint16 MUX28:2;                     // 25:24 MUX28 Configuration for AUXSIG7 of CLB-XBAR
    Uint16 MUX29:2;                     // 27:26 MUX29 Configuration for AUXSIG7 of CLB-XBAR
    Uint16 MUX30:2;                     // 29:28 MUX30 Configuration for AUXSIG7 of CLB-XBAR
    Uint16 MUX31:2;                     // 31:30 MUX31 Configuration for AUXSIG7 of CLB-XBAR
};

union AUXSIG7MUX16TO31CFG_REG {
    Uint32  all;
    struct  AUXSIG7MUX16TO31CFG_BITS  bit;
};

struct AUXSIG0MUXENABLE_BITS {          // bits description
    Uint16 MUX0:1;                      // 0 mux0 to drive AUXSIG0 of CLB-XBAR
    Uint16 MUX1:1;                      // 1 MUX1 to drive AUXSIG0 of CLB-XBAR
    Uint16 MUX2:1;                      // 2 MUX2 to drive AUXSIG0 of CLB-XBAR
    Uint16 MUX3:1;                      // 3 MUX3 to drive AUXSIG0 of CLB-XBAR
    Uint16 MUX4:1;                      // 4 MUX4 to drive AUXSIG0 of CLB-XBAR
    Uint16 MUX5:1;                      // 5 MUX5 to drive AUXSIG0 of CLB-XBAR
    Uint16 MUX6:1;                      // 6 MUX6 to drive AUXSIG0 of CLB-XBAR
    Uint16 MUX7:1;                      // 7 MUX7 to drive AUXSIG0 of CLB-XBAR
    Uint16 MUX8:1;                      // 8 MUX8 to drive AUXSIG0 of CLB-XBAR
    Uint16 MUX9:1;                      // 9 MUX9 to drive AUXSIG0 of CLB-XBAR
    Uint16 MUX10:1;                     // 10 MUX10 to drive AUXSIG0 of CLB-XBAR
    Uint16 MUX11:1;                     // 11 MUX11 to drive AUXSIG0 of CLB-XBAR
    Uint16 MUX12:1;                     // 12 MUX12 to drive AUXSIG0 of CLB-XBAR
    Uint16 MUX13:1;                     // 13 MUX13 to drive AUXSIG0 of CLB-XBAR
    Uint16 MUX14:1;                     // 14 MUX14 to drive AUXSIG0 of CLB-XBAR
    Uint16 MUX15:1;                     // 15 MUX15 to drive AUXSIG0 of CLB-XBAR
    Uint16 MUX16:1;                     // 16 MUX16 to drive AUXSIG0 of CLB-XBAR
    Uint16 MUX17:1;                     // 17 MUX17 to drive AUXSIG0 of CLB-XBAR
    Uint16 MUX18:1;                     // 18 MUX18 to drive AUXSIG0 of CLB-XBAR
    Uint16 MUX19:1;                     // 19 MUX19 to drive AUXSIG0 of CLB-XBAR
    Uint16 MUX20:1;                     // 20 MUX20 to drive AUXSIG0 of CLB-XBAR
    Uint16 MUX21:1;                     // 21 MUX21 to drive AUXSIG0 of CLB-XBAR
    Uint16 MUX22:1;                     // 22 MUX22 to drive AUXSIG0 of CLB-XBAR
    Uint16 MUX23:1;                     // 23 MUX23 to drive AUXSIG0 of CLB-XBAR
    Uint16 MUX24:1;                     // 24 MUX24 to drive AUXSIG0 of CLB-XBAR
    Uint16 MUX25:1;                     // 25 MUX25 to drive AUXSIG0 of CLB-XBAR
    Uint16 MUX26:1;                     // 26 MUX26 to drive AUXSIG0 of CLB-XBAR
    Uint16 MUX27:1;                     // 27 MUX27 to drive AUXSIG0 of CLB-XBAR
    Uint16 MUX28:1;                     // 28 MUX28 to drive AUXSIG0 of CLB-XBAR
    Uint16 MUX29:1;                     // 29 MUX29 to drive AUXSIG0 of CLB-XBAR
    Uint16 MUX30:1;                     // 30 MUX30 to drive AUXSIG0 of CLB-XBAR
    Uint16 MUX31:1;                     // 31 MUX31 to drive AUXSIG0 of CLB-XBAR
};

union AUXSIG0MUXENABLE_REG {
    Uint32  all;
    struct  AUXSIG0MUXENABLE_BITS  bit;
};

struct AUXSIG1MUXENABLE_BITS {          // bits description
    Uint16 MUX0:1;                      // 0 mux0 to drive AUXSIG1 of CLB-XBAR
    Uint16 MUX1:1;                      // 1 MUX1 to drive AUXSIG1 of CLB-XBAR
    Uint16 MUX2:1;                      // 2 MUX2 to drive AUXSIG1 of CLB-XBAR
    Uint16 MUX3:1;                      // 3 MUX3 to drive AUXSIG1 of CLB-XBAR
    Uint16 MUX4:1;                      // 4 MUX4 to drive AUXSIG1 of CLB-XBAR
    Uint16 MUX5:1;                      // 5 MUX5 to drive AUXSIG1 of CLB-XBAR
    Uint16 MUX6:1;                      // 6 MUX6 to drive AUXSIG1 of CLB-XBAR
    Uint16 MUX7:1;                      // 7 MUX7 to drive AUXSIG1 of CLB-XBAR
    Uint16 MUX8:1;                      // 8 MUX8 to drive AUXSIG1 of CLB-XBAR
    Uint16 MUX9:1;                      // 9 MUX9 to drive AUXSIG1 of CLB-XBAR
    Uint16 MUX10:1;                     // 10 MUX10 to drive AUXSIG1 of CLB-XBAR
    Uint16 MUX11:1;                     // 11 MUX11 to drive AUXSIG1 of CLB-XBAR
    Uint16 MUX12:1;                     // 12 MUX12 to drive AUXSIG1 of CLB-XBAR
    Uint16 MUX13:1;                     // 13 MUX13 to drive AUXSIG1 of CLB-XBAR
    Uint16 MUX14:1;                     // 14 MUX14 to drive AUXSIG1 of CLB-XBAR
    Uint16 MUX15:1;                     // 15 MUX15 to drive AUXSIG1 of CLB-XBAR
    Uint16 MUX16:1;                     // 16 MUX16 to drive AUXSIG1 of CLB-XBAR
    Uint16 MUX17:1;                     // 17 MUX17 to drive AUXSIG1 of CLB-XBAR
    Uint16 MUX18:1;                     // 18 MUX18 to drive AUXSIG1 of CLB-XBAR
    Uint16 MUX19:1;                     // 19 MUX19 to drive AUXSIG1 of CLB-XBAR
    Uint16 MUX20:1;                     // 20 MUX20 to drive AUXSIG1 of CLB-XBAR
    Uint16 MUX21:1;                     // 21 MUX21 to drive AUXSIG1 of CLB-XBAR
    Uint16 MUX22:1;                     // 22 MUX22 to drive AUXSIG1 of CLB-XBAR
    Uint16 MUX23:1;                     // 23 MUX23 to drive AUXSIG1 of CLB-XBAR
    Uint16 MUX24:1;                     // 24 MUX24 to drive AUXSIG1 of CLB-XBAR
    Uint16 MUX25:1;                     // 25 MUX25 to drive AUXSIG1 of CLB-XBAR
    Uint16 MUX26:1;                     // 26 MUX26 to drive AUXSIG1 of CLB-XBAR
    Uint16 MUX27:1;                     // 27 MUX27 to drive AUXSIG1 of CLB-XBAR
    Uint16 MUX28:1;                     // 28 MUX28 to drive AUXSIG1 of CLB-XBAR
    Uint16 MUX29:1;                     // 29 MUX29 to drive AUXSIG1 of CLB-XBAR
    Uint16 MUX30:1;                     // 30 MUX30 to drive AUXSIG1 of CLB-XBAR
    Uint16 MUX31:1;                     // 31 MUX31 to drive AUXSIG1 of CLB-XBAR
};

union AUXSIG1MUXENABLE_REG {
    Uint32  all;
    struct  AUXSIG1MUXENABLE_BITS  bit;
};

struct AUXSIG2MUXENABLE_BITS {          // bits description
    Uint16 MUX0:1;                      // 0 mux0 to drive AUXSIG2 of CLB-XBAR
    Uint16 MUX1:1;                      // 1 MUX1 to drive AUXSIG2 of CLB-XBAR
    Uint16 MUX2:1;                      // 2 MUX2 to drive AUXSIG2 of CLB-XBAR
    Uint16 MUX3:1;                      // 3 MUX3 to drive AUXSIG2 of CLB-XBAR
    Uint16 MUX4:1;                      // 4 MUX4 to drive AUXSIG2 of CLB-XBAR
    Uint16 MUX5:1;                      // 5 MUX5 to drive AUXSIG2 of CLB-XBAR
    Uint16 MUX6:1;                      // 6 MUX6 to drive AUXSIG2 of CLB-XBAR
    Uint16 MUX7:1;                      // 7 MUX7 to drive AUXSIG2 of CLB-XBAR
    Uint16 MUX8:1;                      // 8 MUX8 to drive AUXSIG2 of CLB-XBAR
    Uint16 MUX9:1;                      // 9 MUX9 to drive AUXSIG2 of CLB-XBAR
    Uint16 MUX10:1;                     // 10 MUX10 to drive AUXSIG2 of CLB-XBAR
    Uint16 MUX11:1;                     // 11 MUX11 to drive AUXSIG2 of CLB-XBAR
    Uint16 MUX12:1;                     // 12 MUX12 to drive AUXSIG2 of CLB-XBAR
    Uint16 MUX13:1;                     // 13 MUX13 to drive AUXSIG2 of CLB-XBAR
    Uint16 MUX14:1;                     // 14 MUX14 to drive AUXSIG2 of CLB-XBAR
    Uint16 MUX15:1;                     // 15 MUX15 to drive AUXSIG2 of CLB-XBAR
    Uint16 MUX16:1;                     // 16 MUX16 to drive AUXSIG2 of CLB-XBAR
    Uint16 MUX17:1;                     // 17 MUX17 to drive AUXSIG2 of CLB-XBAR
    Uint16 MUX18:1;                     // 18 MUX18 to drive AUXSIG2 of CLB-XBAR
    Uint16 MUX19:1;                     // 19 MUX19 to drive AUXSIG2 of CLB-XBAR
    Uint16 MUX20:1;                     // 20 MUX20 to drive AUXSIG2 of CLB-XBAR
    Uint16 MUX21:1;                     // 21 MUX21 to drive AUXSIG2 of CLB-XBAR
    Uint16 MUX22:1;                     // 22 MUX22 to drive AUXSIG2 of CLB-XBAR
    Uint16 MUX23:1;                     // 23 MUX23 to drive AUXSIG2 of CLB-XBAR
    Uint16 MUX24:1;                     // 24 MUX24 to drive AUXSIG2 of CLB-XBAR
    Uint16 MUX25:1;                     // 25 MUX25 to drive AUXSIG2 of CLB-XBAR
    Uint16 MUX26:1;                     // 26 MUX26 to drive AUXSIG2 of CLB-XBAR
    Uint16 MUX27:1;                     // 27 MUX27 to drive AUXSIG2 of CLB-XBAR
    Uint16 MUX28:1;                     // 28 MUX28 to drive AUXSIG2 of CLB-XBAR
    Uint16 MUX29:1;                     // 29 MUX29 to drive AUXSIG2 of CLB-XBAR
    Uint16 MUX30:1;                     // 30 MUX30 to drive AUXSIG2 of CLB-XBAR
    Uint16 MUX31:1;                     // 31 MUX31 to drive AUXSIG2 of CLB-XBAR
};

union AUXSIG2MUXENABLE_REG {
    Uint32  all;
    struct  AUXSIG2MUXENABLE_BITS  bit;
};

struct AUXSIG3MUXENABLE_BITS {          // bits description
    Uint16 MUX0:1;                      // 0 mux0 to drive AUXSIG3 of CLB-XBAR
    Uint16 MUX1:1;                      // 1 MUX1 to drive AUXSIG3 of CLB-XBAR
    Uint16 MUX2:1;                      // 2 MUX2 to drive AUXSIG3 of CLB-XBAR
    Uint16 MUX3:1;                      // 3 MUX3 to drive AUXSIG3 of CLB-XBAR
    Uint16 MUX4:1;                      // 4 MUX4 to drive AUXSIG3 of CLB-XBAR
    Uint16 MUX5:1;                      // 5 MUX5 to drive AUXSIG3 of CLB-XBAR
    Uint16 MUX6:1;                      // 6 MUX6 to drive AUXSIG3 of CLB-XBAR
    Uint16 MUX7:1;                      // 7 MUX7 to drive AUXSIG3 of CLB-XBAR
    Uint16 MUX8:1;                      // 8 MUX8 to drive AUXSIG3 of CLB-XBAR
    Uint16 MUX9:1;                      // 9 MUX9 to drive AUXSIG3 of CLB-XBAR
    Uint16 MUX10:1;                     // 10 MUX10 to drive AUXSIG3 of CLB-XBAR
    Uint16 MUX11:1;                     // 11 MUX11 to drive AUXSIG3 of CLB-XBAR
    Uint16 MUX12:1;                     // 12 MUX12 to drive AUXSIG3 of CLB-XBAR
    Uint16 MUX13:1;                     // 13 MUX13 to drive AUXSIG3 of CLB-XBAR
    Uint16 MUX14:1;                     // 14 MUX14 to drive AUXSIG3 of CLB-XBAR
    Uint16 MUX15:1;                     // 15 MUX15 to drive AUXSIG3 of CLB-XBAR
    Uint16 MUX16:1;                     // 16 MUX16 to drive AUXSIG3 of CLB-XBAR
    Uint16 MUX17:1;                     // 17 MUX17 to drive AUXSIG3 of CLB-XBAR
    Uint16 MUX18:1;                     // 18 MUX18 to drive AUXSIG3 of CLB-XBAR
    Uint16 MUX19:1;                     // 19 MUX19 to drive AUXSIG3 of CLB-XBAR
    Uint16 MUX20:1;                     // 20 MUX20 to drive AUXSIG3 of CLB-XBAR
    Uint16 MUX21:1;                     // 21 MUX21 to drive AUXSIG3 of CLB-XBAR
    Uint16 MUX22:1;                     // 22 MUX22 to drive AUXSIG3 of CLB-XBAR
    Uint16 MUX23:1;                     // 23 MUX23 to drive AUXSIG3 of CLB-XBAR
    Uint16 MUX24:1;                     // 24 MUX24 to drive AUXSIG3 of CLB-XBAR
    Uint16 MUX25:1;                     // 25 MUX25 to drive AUXSIG3 of CLB-XBAR
    Uint16 MUX26:1;                     // 26 MUX26 to drive AUXSIG3 of CLB-XBAR
    Uint16 MUX27:1;                     // 27 MUX27 to drive AUXSIG3 of CLB-XBAR
    Uint16 MUX28:1;                     // 28 MUX28 to drive AUXSIG3 of CLB-XBAR
    Uint16 MUX29:1;                     // 29 MUX29 to drive AUXSIG3 of CLB-XBAR
    Uint16 MUX30:1;                     // 30 MUX30 to drive AUXSIG3 of CLB-XBAR
    Uint16 MUX31:1;                     // 31 MUX31 to drive AUXSIG3 of CLB-XBAR
};

union AUXSIG3MUXENABLE_REG {
    Uint32  all;
    struct  AUXSIG3MUXENABLE_BITS  bit;
};

struct AUXSIG4MUXENABLE_BITS {          // bits description
    Uint16 MUX0:1;                      // 0 mux0 to drive AUXSIG4 of CLB-XBAR
    Uint16 MUX1:1;                      // 1 MUX1 to drive AUXSIG4 of CLB-XBAR
    Uint16 MUX2:1;                      // 2 MUX2 to drive AUXSIG4 of CLB-XBAR
    Uint16 MUX3:1;                      // 3 MUX3 to drive AUXSIG4 of CLB-XBAR
    Uint16 MUX4:1;                      // 4 MUX4 to drive AUXSIG4 of CLB-XBAR
    Uint16 MUX5:1;                      // 5 MUX5 to drive AUXSIG4 of CLB-XBAR
    Uint16 MUX6:1;                      // 6 MUX6 to drive AUXSIG4 of CLB-XBAR
    Uint16 MUX7:1;                      // 7 MUX7 to drive AUXSIG4 of CLB-XBAR
    Uint16 MUX8:1;                      // 8 MUX8 to drive AUXSIG4 of CLB-XBAR
    Uint16 MUX9:1;                      // 9 MUX9 to drive AUXSIG4 of CLB-XBAR
    Uint16 MUX10:1;                     // 10 MUX10 to drive AUXSIG4 of CLB-XBAR
    Uint16 MUX11:1;                     // 11 MUX11 to drive AUXSIG4 of CLB-XBAR
    Uint16 MUX12:1;                     // 12 MUX12 to drive AUXSIG4 of CLB-XBAR
    Uint16 MUX13:1;                     // 13 MUX13 to drive AUXSIG4 of CLB-XBAR
    Uint16 MUX14:1;                     // 14 MUX14 to drive AUXSIG4 of CLB-XBAR
    Uint16 MUX15:1;                     // 15 MUX15 to drive AUXSIG4 of CLB-XBAR
    Uint16 MUX16:1;                     // 16 MUX16 to drive AUXSIG4 of CLB-XBAR
    Uint16 MUX17:1;                     // 17 MUX17 to drive AUXSIG4 of CLB-XBAR
    Uint16 MUX18:1;                     // 18 MUX18 to drive AUXSIG4 of CLB-XBAR
    Uint16 MUX19:1;                     // 19 MUX19 to drive AUXSIG4 of CLB-XBAR
    Uint16 MUX20:1;                     // 20 MUX20 to drive AUXSIG4 of CLB-XBAR
    Uint16 MUX21:1;                     // 21 MUX21 to drive AUXSIG4 of CLB-XBAR
    Uint16 MUX22:1;                     // 22 MUX22 to drive AUXSIG4 of CLB-XBAR
    Uint16 MUX23:1;                     // 23 MUX23 to drive AUXSIG4 of CLB-XBAR
    Uint16 MUX24:1;                     // 24 MUX24 to drive AUXSIG4 of CLB-XBAR
    Uint16 MUX25:1;                     // 25 MUX25 to drive AUXSIG4 of CLB-XBAR
    Uint16 MUX26:1;                     // 26 MUX26 to drive AUXSIG4 of CLB-XBAR
    Uint16 MUX27:1;                     // 27 MUX27 to drive AUXSIG4 of CLB-XBAR
    Uint16 MUX28:1;                     // 28 MUX28 to drive AUXSIG4 of CLB-XBAR
    Uint16 MUX29:1;                     // 29 MUX29 to drive AUXSIG4 of CLB-XBAR
    Uint16 MUX30:1;                     // 30 MUX30 to drive AUXSIG4 of CLB-XBAR
    Uint16 MUX31:1;                     // 31 MUX31 to drive AUXSIG4 of CLB-XBAR
};

union AUXSIG4MUXENABLE_REG {
    Uint32  all;
    struct  AUXSIG4MUXENABLE_BITS  bit;
};

struct AUXSIG5MUXENABLE_BITS {          // bits description
    Uint16 MUX0:1;                      // 0 mux0 to drive AUXSIG5 of CLB-XBAR
    Uint16 MUX1:1;                      // 1 MUX1 to drive AUXSIG5 of CLB-XBAR
    Uint16 MUX2:1;                      // 2 MUX2 to drive AUXSIG5 of CLB-XBAR
    Uint16 MUX3:1;                      // 3 MUX3 to drive AUXSIG5 of CLB-XBAR
    Uint16 MUX4:1;                      // 4 MUX4 to drive AUXSIG5 of CLB-XBAR
    Uint16 MUX5:1;                      // 5 MUX5 to drive AUXSIG5 of CLB-XBAR
    Uint16 MUX6:1;                      // 6 MUX6 to drive AUXSIG5 of CLB-XBAR
    Uint16 MUX7:1;                      // 7 MUX7 to drive AUXSIG5 of CLB-XBAR
    Uint16 MUX8:1;                      // 8 MUX8 to drive AUXSIG5 of CLB-XBAR
    Uint16 MUX9:1;                      // 9 MUX9 to drive AUXSIG5 of CLB-XBAR
    Uint16 MUX10:1;                     // 10 MUX10 to drive AUXSIG5 of CLB-XBAR
    Uint16 MUX11:1;                     // 11 MUX11 to drive AUXSIG5 of CLB-XBAR
    Uint16 MUX12:1;                     // 12 MUX12 to drive AUXSIG5 of CLB-XBAR
    Uint16 MUX13:1;                     // 13 MUX13 to drive AUXSIG5 of CLB-XBAR
    Uint16 MUX14:1;                     // 14 MUX14 to drive AUXSIG5 of CLB-XBAR
    Uint16 MUX15:1;                     // 15 MUX15 to drive AUXSIG5 of CLB-XBAR
    Uint16 MUX16:1;                     // 16 MUX16 to drive AUXSIG5 of CLB-XBAR
    Uint16 MUX17:1;                     // 17 MUX17 to drive AUXSIG5 of CLB-XBAR
    Uint16 MUX18:1;                     // 18 MUX18 to drive AUXSIG5 of CLB-XBAR
    Uint16 MUX19:1;                     // 19 MUX19 to drive AUXSIG5 of CLB-XBAR
    Uint16 MUX20:1;                     // 20 MUX20 to drive AUXSIG5 of CLB-XBAR
    Uint16 MUX21:1;                     // 21 MUX21 to drive AUXSIG5 of CLB-XBAR
    Uint16 MUX22:1;                     // 22 MUX22 to drive AUXSIG5 of CLB-XBAR
    Uint16 MUX23:1;                     // 23 MUX23 to drive AUXSIG5 of CLB-XBAR
    Uint16 MUX24:1;                     // 24 MUX24 to drive AUXSIG5 of CLB-XBAR
    Uint16 MUX25:1;                     // 25 MUX25 to drive AUXSIG5 of CLB-XBAR
    Uint16 MUX26:1;                     // 26 MUX26 to drive AUXSIG5 of CLB-XBAR
    Uint16 MUX27:1;                     // 27 MUX27 to drive AUXSIG5 of CLB-XBAR
    Uint16 MUX28:1;                     // 28 MUX28 to drive AUXSIG5 of CLB-XBAR
    Uint16 MUX29:1;                     // 29 MUX29 to drive AUXSIG5 of CLB-XBAR
    Uint16 MUX30:1;                     // 30 MUX30 to drive AUXSIG5 of CLB-XBAR
    Uint16 MUX31:1;                     // 31 MUX31 to drive AUXSIG5 of CLB-XBAR
};

union AUXSIG5MUXENABLE_REG {
    Uint32  all;
    struct  AUXSIG5MUXENABLE_BITS  bit;
};

struct AUXSIG6MUXENABLE_BITS {          // bits description
    Uint16 MUX0:1;                      // 0 mux0 to drive AUXSIG6 of CLB-XBAR
    Uint16 MUX1:1;                      // 1 MUX1 to drive AUXSIG6 of CLB-XBAR
    Uint16 MUX2:1;                      // 2 MUX2 to drive AUXSIG6 of CLB-XBAR
    Uint16 MUX3:1;                      // 3 MUX3 to drive AUXSIG6 of CLB-XBAR
    Uint16 MUX4:1;                      // 4 MUX4 to drive AUXSIG6 of CLB-XBAR
    Uint16 MUX5:1;                      // 5 MUX5 to drive AUXSIG6 of CLB-XBAR
    Uint16 MUX6:1;                      // 6 MUX6 to drive AUXSIG6 of CLB-XBAR
    Uint16 MUX7:1;                      // 7 MUX7 to drive AUXSIG6 of CLB-XBAR
    Uint16 MUX8:1;                      // 8 MUX8 to drive AUXSIG6 of CLB-XBAR
    Uint16 MUX9:1;                      // 9 MUX9 to drive AUXSIG6 of CLB-XBAR
    Uint16 MUX10:1;                     // 10 MUX10 to drive AUXSIG6 of CLB-XBAR
    Uint16 MUX11:1;                     // 11 MUX11 to drive AUXSIG6 of CLB-XBAR
    Uint16 MUX12:1;                     // 12 MUX12 to drive AUXSIG6 of CLB-XBAR
    Uint16 MUX13:1;                     // 13 MUX13 to drive AUXSIG6 of CLB-XBAR
    Uint16 MUX14:1;                     // 14 MUX14 to drive AUXSIG6 of CLB-XBAR
    Uint16 MUX15:1;                     // 15 MUX15 to drive AUXSIG6 of CLB-XBAR
    Uint16 MUX16:1;                     // 16 MUX16 to drive AUXSIG6 of CLB-XBAR
    Uint16 MUX17:1;                     // 17 MUX17 to drive AUXSIG6 of CLB-XBAR
    Uint16 MUX18:1;                     // 18 MUX18 to drive AUXSIG6 of CLB-XBAR
    Uint16 MUX19:1;                     // 19 MUX19 to drive AUXSIG6 of CLB-XBAR
    Uint16 MUX20:1;                     // 20 MUX20 to drive AUXSIG6 of CLB-XBAR
    Uint16 MUX21:1;                     // 21 MUX21 to drive AUXSIG6 of CLB-XBAR
    Uint16 MUX22:1;                     // 22 MUX22 to drive AUXSIG6 of CLB-XBAR
    Uint16 MUX23:1;                     // 23 MUX23 to drive AUXSIG6 of CLB-XBAR
    Uint16 MUX24:1;                     // 24 MUX24 to drive AUXSIG6 of CLB-XBAR
    Uint16 MUX25:1;                     // 25 MUX25 to drive AUXSIG6 of CLB-XBAR
    Uint16 MUX26:1;                     // 26 MUX26 to drive AUXSIG6 of CLB-XBAR
    Uint16 MUX27:1;                     // 27 MUX27 to drive AUXSIG6 of CLB-XBAR
    Uint16 MUX28:1;                     // 28 MUX28 to drive AUXSIG6 of CLB-XBAR
    Uint16 MUX29:1;                     // 29 MUX29 to drive AUXSIG6 of CLB-XBAR
    Uint16 MUX30:1;                     // 30 MUX30 to drive AUXSIG6 of CLB-XBAR
    Uint16 MUX31:1;                     // 31 MUX31 to drive AUXSIG6 of CLB-XBAR
};

union AUXSIG6MUXENABLE_REG {
    Uint32  all;
    struct  AUXSIG6MUXENABLE_BITS  bit;
};

struct AUXSIG7MUXENABLE_BITS {          // bits description
    Uint16 MUX0:1;                      // 0 mux0 to drive AUXSIG7 of CLB-XBAR
    Uint16 MUX1:1;                      // 1 MUX1 to drive AUXSIG7 of CLB-XBAR
    Uint16 MUX2:1;                      // 2 MUX2 to drive AUXSIG7 of CLB-XBAR
    Uint16 MUX3:1;                      // 3 MUX3 to drive AUXSIG7 of CLB-XBAR
    Uint16 MUX4:1;                      // 4 MUX4 to drive AUXSIG7 of CLB-XBAR
    Uint16 MUX5:1;                      // 5 MUX5 to drive AUXSIG7 of CLB-XBAR
    Uint16 MUX6:1;                      // 6 MUX6 to drive AUXSIG7 of CLB-XBAR
    Uint16 MUX7:1;                      // 7 MUX7 to drive AUXSIG7 of CLB-XBAR
    Uint16 MUX8:1;                      // 8 MUX8 to drive AUXSIG7 of CLB-XBAR
    Uint16 MUX9:1;                      // 9 MUX9 to drive AUXSIG7 of CLB-XBAR
    Uint16 MUX10:1;                     // 10 MUX10 to drive AUXSIG7 of CLB-XBAR
    Uint16 MUX11:1;                     // 11 MUX11 to drive AUXSIG7 of CLB-XBAR
    Uint16 MUX12:1;                     // 12 MUX12 to drive AUXSIG7 of CLB-XBAR
    Uint16 MUX13:1;                     // 13 MUX13 to drive AUXSIG7 of CLB-XBAR
    Uint16 MUX14:1;                     // 14 MUX14 to drive AUXSIG7 of CLB-XBAR
    Uint16 MUX15:1;                     // 15 MUX15 to drive AUXSIG7 of CLB-XBAR
    Uint16 MUX16:1;                     // 16 MUX16 to drive AUXSIG7 of CLB-XBAR
    Uint16 MUX17:1;                     // 17 MUX17 to drive AUXSIG7 of CLB-XBAR
    Uint16 MUX18:1;                     // 18 MUX18 to drive AUXSIG7 of CLB-XBAR
    Uint16 MUX19:1;                     // 19 MUX19 to drive AUXSIG7 of CLB-XBAR
    Uint16 MUX20:1;                     // 20 MUX20 to drive AUXSIG7 of CLB-XBAR
    Uint16 MUX21:1;                     // 21 MUX21 to drive AUXSIG7 of CLB-XBAR
    Uint16 MUX22:1;                     // 22 MUX22 to drive AUXSIG7 of CLB-XBAR
    Uint16 MUX23:1;                     // 23 MUX23 to drive AUXSIG7 of CLB-XBAR
    Uint16 MUX24:1;                     // 24 MUX24 to drive AUXSIG7 of CLB-XBAR
    Uint16 MUX25:1;                     // 25 MUX25 to drive AUXSIG7 of CLB-XBAR
    Uint16 MUX26:1;                     // 26 MUX26 to drive AUXSIG7 of CLB-XBAR
    Uint16 MUX27:1;                     // 27 MUX27 to drive AUXSIG7 of CLB-XBAR
    Uint16 MUX28:1;                     // 28 MUX28 to drive AUXSIG7 of CLB-XBAR
    Uint16 MUX29:1;                     // 29 MUX29 to drive AUXSIG7 of CLB-XBAR
    Uint16 MUX30:1;                     // 30 MUX30 to drive AUXSIG7 of CLB-XBAR
    Uint16 MUX31:1;                     // 31 MUX31 to drive AUXSIG7 of CLB-XBAR
};

union AUXSIG7MUXENABLE_REG {
    Uint32  all;
    struct  AUXSIG7MUXENABLE_BITS  bit;
};

struct AUXSIGOUTINV_BITS {              // bits description
    Uint16 OUT0:1;                      // 0 Selects polarity for AUXSIG0 of CLB-XBAR
    Uint16 OUT1:1;                      // 1 Selects polarity for AUXSIG1 of CLB-XBAR
    Uint16 OUT2:1;                      // 2 Selects polarity for AUXSIG2 of CLB-XBAR
    Uint16 OUT3:1;                      // 3 Selects polarity for AUXSIG3 of CLB-XBAR
    Uint16 OUT4:1;                      // 4 Selects polarity for AUXSIG4 of CLB-XBAR
    Uint16 OUT5:1;                      // 5 Selects polarity for AUXSIG5 of CLB-XBAR
    Uint16 OUT6:1;                      // 6 Selects polarity for AUXSIG6 of CLB-XBAR
    Uint16 OUT7:1;                      // 7 Selects polarity for AUXSIG7 of CLB-XBAR
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union AUXSIGOUTINV_REG {
    Uint32  all;
    struct  AUXSIGOUTINV_BITS  bit;
};

struct AUXSIGLOCK_BITS {                // bits description
    Uint16 LOCK:1;                      // 0 Locks the configuration for CLB-XBAR
    Uint16 rsvd1:15;                    // 15:1 Reserved
    Uint16 KEY:16;                      // 31:16 Write Protection KEY
};

union AUXSIGLOCK_REG {
    Uint32  all;
    struct  AUXSIGLOCK_BITS  bit;
};

struct CLB_XBAR_REGS {
    union   AUXSIG0MUX0TO15CFG_REG           AUXSIG0MUX0TO15CFG;           // CLB XBAR Mux Configuration for Output-0
    union   AUXSIG0MUX16TO31CFG_REG          AUXSIG0MUX16TO31CFG;          // CLB XBAR Mux Configuration for Output-0
    union   AUXSIG1MUX0TO15CFG_REG           AUXSIG1MUX0TO15CFG;           // CLB XBAR Mux Configuration for Output-1
    union   AUXSIG1MUX16TO31CFG_REG          AUXSIG1MUX16TO31CFG;          // CLB XBAR Mux Configuration for Output-1
    union   AUXSIG2MUX0TO15CFG_REG           AUXSIG2MUX0TO15CFG;           // CLB XBAR Mux Configuration for Output-2
    union   AUXSIG2MUX16TO31CFG_REG          AUXSIG2MUX16TO31CFG;          // CLB XBAR Mux Configuration for Output-2
    union   AUXSIG3MUX0TO15CFG_REG           AUXSIG3MUX0TO15CFG;           // CLB XBAR Mux Configuration for Output-3
    union   AUXSIG3MUX16TO31CFG_REG          AUXSIG3MUX16TO31CFG;          // CLB XBAR Mux Configuration for Output-3
    union   AUXSIG4MUX0TO15CFG_REG           AUXSIG4MUX0TO15CFG;           // CLB XBAR Mux Configuration for Output-4
    union   AUXSIG4MUX16TO31CFG_REG          AUXSIG4MUX16TO31CFG;          // CLB XBAR Mux Configuration for Output-4
    union   AUXSIG5MUX0TO15CFG_REG           AUXSIG5MUX0TO15CFG;           // CLB XBAR Mux Configuration for Output-5
    union   AUXSIG5MUX16TO31CFG_REG          AUXSIG5MUX16TO31CFG;          // CLB XBAR Mux Configuration for Output-5
    union   AUXSIG6MUX0TO15CFG_REG           AUXSIG6MUX0TO15CFG;           // CLB XBAR Mux Configuration for Output-6
    union   AUXSIG6MUX16TO31CFG_REG          AUXSIG6MUX16TO31CFG;          // CLB XBAR Mux Configuration for Output-6
    union   AUXSIG7MUX0TO15CFG_REG           AUXSIG7MUX0TO15CFG;           // CLB XBAR Mux Configuration for Output-7
    union   AUXSIG7MUX16TO31CFG_REG          AUXSIG7MUX16TO31CFG;          // CLB XBAR Mux Configuration for Output-7
    union   AUXSIG0MUXENABLE_REG             AUXSIG0MUXENABLE;             // CLB XBAR Mux Enable Register for Output-0
    union   AUXSIG1MUXENABLE_REG             AUXSIG1MUXENABLE;             // CLB XBAR Mux Enable Register for Output-1
    union   AUXSIG2MUXENABLE_REG             AUXSIG2MUXENABLE;             // CLB XBAR Mux Enable Register for Output-2
    union   AUXSIG3MUXENABLE_REG             AUXSIG3MUXENABLE;             // CLB XBAR Mux Enable Register for Output-3
    union   AUXSIG4MUXENABLE_REG             AUXSIG4MUXENABLE;             // CLB XBAR Mux Enable Register for Output-4
    union   AUXSIG5MUXENABLE_REG             AUXSIG5MUXENABLE;             // CLB XBAR Mux Enable Register for Output-5
    union   AUXSIG6MUXENABLE_REG             AUXSIG6MUXENABLE;             // CLB XBAR Mux Enable Register for Output-6
    union   AUXSIG7MUXENABLE_REG             AUXSIG7MUXENABLE;             // CLB XBAR Mux Enable Register for Output-7
    Uint16                                   rsvd1[8];                     // Reserved
    union   AUXSIGOUTINV_REG                 AUXSIGOUTINV;                 // CLB XBAR Output Inversion Register
    Uint16                                   rsvd2[4];                     // Reserved
    union   AUXSIGLOCK_REG                   AUXSIGLOCK;                   // ClbXbar Configuration Lock register
};

//---------------------------------------------------------------------------
// CLBXBAR External References & Function Declarations:
//
#ifdef CPU1
extern volatile struct CLB_XBAR_REGS ClbXbarRegs;
#endif
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
