//###########################################################################
//
// FILE:    f28p65x_epwm_xbar.h
//
// TITLE:   Definitions for the EPWM_XBAR registers.
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

#ifndef F28P65X_EPWM_XBAR_H
#define F28P65X_EPWM_XBAR_H

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// EPWM_XBAR Individual Register Bit Definitions:

struct OUT1MUX0TO15CFG_BITS {           // bits description
    Uint16 MUX0:2;                      // 1:0 MUX0 Configuration for OUT1 of EPWM-XBAR
    Uint16 MUX1:2;                      // 3:2 MUX1 Configuration for OUT1 of EPWM-XBAR
    Uint16 MUX2:2;                      // 5:4 MUX2 Configuration for OUT1 of EPWM-XBAR
    Uint16 MUX3:2;                      // 7:6 MUX3 Configuration for OUT1 of EPWM-XBAR
    Uint16 MUX4:2;                      // 9:8 MUX4 Configuration for OUT1 of EPWM-XBAR
    Uint16 MUX5:2;                      // 11:10 MUX5 Configuration for OUT1 of EPWM-XBAR
    Uint16 MUX6:2;                      // 13:12 MUX6 Configuration for OUT1 of EPWM-XBAR
    Uint16 MUX7:2;                      // 15:14 MUX7 Configuration for OUT1 of EPWM-XBAR
    Uint16 MUX8:2;                      // 17:16 MUX8 Configuration for OUT1 of EPWM-XBAR
    Uint16 MUX9:2;                      // 19:18 MUX9 Configuration for OUT1 of EPWM-XBAR
    Uint16 MUX10:2;                     // 21:20 MUX10 Configuration for OUT1 of EPWM-XBAR
    Uint16 MUX11:2;                     // 23:22 MUX11 Configuration for OUT1 of EPWM-XBAR
    Uint16 MUX12:2;                     // 25:24 MUX12 Configuration for OUT1 of EPWM-XBAR
    Uint16 MUX13:2;                     // 27:26 MUX13 Configuration for OUT1 of EPWM-XBAR
    Uint16 MUX14:2;                     // 29:28 MUX14 Configuration for OUT1 of EPWM-XBAR
    Uint16 MUX15:2;                     // 31:30 MUX15 Configuration for OUT1 of EPWM-XBAR
};

union OUT1MUX0TO15CFG_REG {
    Uint32  all;
    struct  OUT1MUX0TO15CFG_BITS  bit;
};

struct OUT1MUX16TO31CFG_BITS {          // bits description
    Uint16 MUX16:2;                     // 1:0 MUX16 Configuration for OUT1 of EPWM-XBAR
    Uint16 MUX17:2;                     // 3:2 MUX17 Configuration for OUT1 of EPWM-XBAR
    Uint16 MUX18:2;                     // 5:4 MUX18 Configuration for OUT1 of EPWM-XBAR
    Uint16 MUX19:2;                     // 7:6 MUX19 Configuration for OUT1 of EPWM-XBAR
    Uint16 MUX20:2;                     // 9:8 MUX20 Configuration for OUT1 of EPWM-XBAR
    Uint16 MUX21:2;                     // 11:10 MUX21 Configuration for OUT1 of EPWM-XBAR
    Uint16 MUX22:2;                     // 13:12 MUX22 Configuration for OUT1 of EPWM-XBAR
    Uint16 MUX23:2;                     // 15:14 MUX23 Configuration for OUT1 of EPWM-XBAR
    Uint16 MUX24:2;                     // 17:16 MUX24 Configuration for OUT1 of EPWM-XBAR
    Uint16 MUX25:2;                     // 19:18 MUX25 Configuration for OUT1 of EPWM-XBAR
    Uint16 MUX26:2;                     // 21:20 MUX26 Configuration for OUT1 of EPWM-XBAR
    Uint16 MUX27:2;                     // 23:22 MUX27 Configuration for OUT1 of EPWM-XBAR
    Uint16 MUX28:2;                     // 25:24 MUX28 Configuration for OUT1 of EPWM-XBAR
    Uint16 MUX29:2;                     // 27:26 MUX29 Configuration for OUT1 of EPWM-XBAR
    Uint16 MUX30:2;                     // 29:28 MUX30 Configuration for OUT1 of EPWM-XBAR
    Uint16 MUX31:2;                     // 31:30 MUX31 Configuration for OUT1 of EPWM-XBAR
};

union OUT1MUX16TO31CFG_REG {
    Uint32  all;
    struct  OUT1MUX16TO31CFG_BITS  bit;
};

struct OUT1MUX32TO47CFG_BITS {          // bits description
    Uint16 MUX32:2;                     // 1:0 MUX32 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX33:2;                     // 3:2 MUX33 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX34:2;                     // 5:4 MUX34 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX35:2;                     // 7:6 MUX35 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX36:2;                     // 9:8 MUX36 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX37:2;                     // 11:10 MUX37 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX38:2;                     // 13:12 MUX38 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX39:2;                     // 15:14 MUX39 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX40:2;                     // 17:16 MUX40 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX41:2;                     // 19:18 MUX41 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX42:2;                     // 21:20 MUX42 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX43:2;                     // 23:22 MUX43 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX44:2;                     // 25:24 MUX44 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX45:2;                     // 27:26 MUX45 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX46:2;                     // 29:28 MUX46 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX47:2;                     // 31:30 MUX47 Configuration for TRIP4 of EPWM-XBAR
};

union OUT1MUX32TO47CFG_REG {
    Uint32  all;
    struct  OUT1MUX32TO47CFG_BITS  bit;
};

struct OUT1MUX48TO63CFG_BITS {          // bits description
    Uint16 MUX48:2;                     // 1:0 MUX48 Configuration for OUT1 of EPWM-XBAR
    Uint16 MUX49:2;                     // 3:2 MUX49 Configuration for OUT1 of EPWM-XBAR
    Uint16 MUX50:2;                     // 5:4 MUX50 Configuration for OUT1 of EPWM-XBAR
    Uint16 MUX51:2;                     // 7:6 MUX51 Configuration for OUT1 of EPWM-XBAR
    Uint16 MUX52:2;                     // 9:8 MUX52 Configuration for OUT1 of EPWM-XBAR
    Uint16 MUX53:2;                     // 11:10 MUX53 Configuration for OUT1 of EPWM-XBAR
    Uint16 MUX54:2;                     // 13:12 MUX54 Configuration for OUT1 of EPWM-XBAR
    Uint16 MUX55:2;                     // 15:14 MUX55 Configuration for OUT1 of EPWM-XBAR
    Uint16 MUX56:2;                     // 17:16 MUX56 Configuration for OUT1 of EPWM-XBAR
    Uint16 MUX57:2;                     // 19:18 MUX57 Configuration for OUT1 of EPWM-XBAR
    Uint16 MUX58:2;                     // 21:20 MUX58 Configuration for OUT1 of EPWM-XBAR
    Uint16 MUX59:2;                     // 23:22 MUX59 Configuration for OUT1 of EPWM-XBAR
    Uint16 MUX60:2;                     // 25:24 MUX60 Configuration for OUT1 of EPWM-XBAR
    Uint16 MUX61:2;                     // 27:26 MUX61 Configuration for OUT1 of EPWM-XBAR
    Uint16 MUX62:2;                     // 29:28 MUX62 Configuration for OUT1 of EPWM-XBAR
    Uint16 MUX63:2;                     // 31:30 MUX63 Configuration for OUT1 of EPWM-XBAR
};

union OUT1MUX48TO63CFG_REG {
    Uint32  all;
    struct  OUT1MUX48TO63CFG_BITS  bit;
};

struct OUT2MUX0TO15CFG_BITS {           // bits description
    Uint16 MUX0:2;                      // 1:0 MUX0 Configuration for OUT2 of EPWM-XBAR
    Uint16 MUX1:2;                      // 3:2 MUX1 Configuration for OUT2 of EPWM-XBAR
    Uint16 MUX2:2;                      // 5:4 MUX2 Configuration for OUT2 of EPWM-XBAR
    Uint16 MUX3:2;                      // 7:6 MUX3 Configuration for OUT2 of EPWM-XBAR
    Uint16 MUX4:2;                      // 9:8 MUX4 Configuration for OUT2 of EPWM-XBAR
    Uint16 MUX5:2;                      // 11:10 MUX5 Configuration for OUT2 of EPWM-XBAR
    Uint16 MUX6:2;                      // 13:12 MUX6 Configuration for OUT2 of EPWM-XBAR
    Uint16 MUX7:2;                      // 15:14 MUX7 Configuration for OUT2 of EPWM-XBAR
    Uint16 MUX8:2;                      // 17:16 MUX8 Configuration for OUT2 of EPWM-XBAR
    Uint16 MUX9:2;                      // 19:18 MUX9 Configuration for OUT2 of EPWM-XBAR
    Uint16 MUX10:2;                     // 21:20 MUX10 Configuration for OUT2 of EPWM-XBAR
    Uint16 MUX11:2;                     // 23:22 MUX11 Configuration for OUT2 of EPWM-XBAR
    Uint16 MUX12:2;                     // 25:24 MUX12 Configuration for OUT2 of EPWM-XBAR
    Uint16 MUX13:2;                     // 27:26 MUX13 Configuration for OUT2 of EPWM-XBAR
    Uint16 MUX14:2;                     // 29:28 MUX14 Configuration for OUT2 of EPWM-XBAR
    Uint16 MUX15:2;                     // 31:30 MUX15 Configuration for OUT2 of EPWM-XBAR
};

union OUT2MUX0TO15CFG_REG {
    Uint32  all;
    struct  OUT2MUX0TO15CFG_BITS  bit;
};

struct OUT2MUX16TO31CFG_BITS {          // bits description
    Uint16 MUX16:2;                     // 1:0 MUX16 Configuration for OUT2 of EPWM-XBAR
    Uint16 MUX17:2;                     // 3:2 MUX17 Configuration for OUT2 of EPWM-XBAR
    Uint16 MUX18:2;                     // 5:4 MUX18 Configuration for OUT2 of EPWM-XBAR
    Uint16 MUX19:2;                     // 7:6 MUX19 Configuration for OUT2 of EPWM-XBAR
    Uint16 MUX20:2;                     // 9:8 MUX20 Configuration for OUT2 of EPWM-XBAR
    Uint16 MUX21:2;                     // 11:10 MUX21 Configuration for OUT2 of EPWM-XBAR
    Uint16 MUX22:2;                     // 13:12 MUX22 Configuration for OUT2 of EPWM-XBAR
    Uint16 MUX23:2;                     // 15:14 MUX23 Configuration for OUT2 of EPWM-XBAR
    Uint16 MUX24:2;                     // 17:16 MUX24 Configuration for OUT2 of EPWM-XBAR
    Uint16 MUX25:2;                     // 19:18 MUX25 Configuration for OUT2 of EPWM-XBAR
    Uint16 MUX26:2;                     // 21:20 MUX26 Configuration for OUT2 of EPWM-XBAR
    Uint16 MUX27:2;                     // 23:22 MUX27 Configuration for OUT2 of EPWM-XBAR
    Uint16 MUX28:2;                     // 25:24 MUX28 Configuration for OUT2 of EPWM-XBAR
    Uint16 MUX29:2;                     // 27:26 MUX29 Configuration for OUT2 of EPWM-XBAR
    Uint16 MUX30:2;                     // 29:28 MUX30 Configuration for OUT2 of EPWM-XBAR
    Uint16 MUX31:2;                     // 31:30 MUX31 Configuration for OUT2 of EPWM-XBAR
};

union OUT2MUX16TO31CFG_REG {
    Uint32  all;
    struct  OUT2MUX16TO31CFG_BITS  bit;
};

struct OUT2MUX32TO47CFG_BITS {          // bits description
    Uint16 MUX32:2;                     // 1:0 MUX32 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX33:2;                     // 3:2 MUX33 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX34:2;                     // 5:4 MUX34 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX35:2;                     // 7:6 MUX35 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX36:2;                     // 9:8 MUX36 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX37:2;                     // 11:10 MUX37 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX38:2;                     // 13:12 MUX38 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX39:2;                     // 15:14 MUX39 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX40:2;                     // 17:16 MUX40 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX41:2;                     // 19:18 MUX41 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX42:2;                     // 21:20 MUX42 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX43:2;                     // 23:22 MUX43 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX44:2;                     // 25:24 MUX44 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX45:2;                     // 27:26 MUX45 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX46:2;                     // 29:28 MUX46 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX47:2;                     // 31:30 MUX47 Configuration for TRIP4 of EPWM-XBAR
};

union OUT2MUX32TO47CFG_REG {
    Uint32  all;
    struct  OUT2MUX32TO47CFG_BITS  bit;
};

struct OUT2MUX48TO63CFG_BITS {          // bits description
    Uint16 MUX48:2;                     // 1:0 MUX48 Configuration for OUT2 of EPWM-XBAR
    Uint16 MUX49:2;                     // 3:2 MUX49 Configuration for OUT2 of EPWM-XBAR
    Uint16 MUX50:2;                     // 5:4 MUX50 Configuration for OUT2 of EPWM-XBAR
    Uint16 MUX51:2;                     // 7:6 MUX51 Configuration for OUT2 of EPWM-XBAR
    Uint16 MUX52:2;                     // 9:8 MUX52 Configuration for OUT2 of EPWM-XBAR
    Uint16 MUX53:2;                     // 11:10 MUX53 Configuration for OUT2 of EPWM-XBAR
    Uint16 MUX54:2;                     // 13:12 MUX54 Configuration for OUT2 of EPWM-XBAR
    Uint16 MUX55:2;                     // 15:14 MUX55 Configuration for OUT2 of EPWM-XBAR
    Uint16 MUX56:2;                     // 17:16 MUX56 Configuration for OUT2 of EPWM-XBAR
    Uint16 MUX57:2;                     // 19:18 MUX57 Configuration for OUT2 of EPWM-XBAR
    Uint16 MUX58:2;                     // 21:20 MUX58 Configuration for OUT2 of EPWM-XBAR
    Uint16 MUX59:2;                     // 23:22 MUX59 Configuration for OUT2 of EPWM-XBAR
    Uint16 MUX60:2;                     // 25:24 MUX60 Configuration for OUT2 of EPWM-XBAR
    Uint16 MUX61:2;                     // 27:26 MUX61 Configuration for OUT2 of EPWM-XBAR
    Uint16 MUX62:2;                     // 29:28 MUX62 Configuration for OUT2 of EPWM-XBAR
    Uint16 MUX63:2;                     // 31:30 MUX63 Configuration for OUT2 of EPWM-XBAR
};

union OUT2MUX48TO63CFG_REG {
    Uint32  all;
    struct  OUT2MUX48TO63CFG_BITS  bit;
};

struct OUT3MUX0TO15CFG_BITS {           // bits description
    Uint16 MUX0:2;                      // 1:0 MUX0 Configuration for OUT3 of EPWM-XBAR
    Uint16 MUX1:2;                      // 3:2 MUX1 Configuration for OUT3 of EPWM-XBAR
    Uint16 MUX2:2;                      // 5:4 MUX2 Configuration for OUT3 of EPWM-XBAR
    Uint16 MUX3:2;                      // 7:6 MUX3 Configuration for OUT3 of EPWM-XBAR
    Uint16 MUX4:2;                      // 9:8 MUX4 Configuration for OUT3 of EPWM-XBAR
    Uint16 MUX5:2;                      // 11:10 MUX5 Configuration for OUT3 of EPWM-XBAR
    Uint16 MUX6:2;                      // 13:12 MUX6 Configuration for OUT3 of EPWM-XBAR
    Uint16 MUX7:2;                      // 15:14 MUX7 Configuration for OUT3 of EPWM-XBAR
    Uint16 MUX8:2;                      // 17:16 MUX8 Configuration for OUT3 of EPWM-XBAR
    Uint16 MUX9:2;                      // 19:18 MUX9 Configuration for OUT3 of EPWM-XBAR
    Uint16 MUX10:2;                     // 21:20 MUX10 Configuration for OUT3 of EPWM-XBAR
    Uint16 MUX11:2;                     // 23:22 MUX11 Configuration for OUT3 of EPWM-XBAR
    Uint16 MUX12:2;                     // 25:24 MUX12 Configuration for OUT3 of EPWM-XBAR
    Uint16 MUX13:2;                     // 27:26 MUX13 Configuration for OUT3 of EPWM-XBAR
    Uint16 MUX14:2;                     // 29:28 MUX14 Configuration for OUT3 of EPWM-XBAR
    Uint16 MUX15:2;                     // 31:30 MUX15 Configuration for OUT3 of EPWM-XBAR
};

union OUT3MUX0TO15CFG_REG {
    Uint32  all;
    struct  OUT3MUX0TO15CFG_BITS  bit;
};

struct OUT3MUX16TO31CFG_BITS {          // bits description
    Uint16 MUX16:2;                     // 1:0 MUX16 Configuration for OUT3 of EPWM-XBAR
    Uint16 MUX17:2;                     // 3:2 MUX17 Configuration for OUT3 of EPWM-XBAR
    Uint16 MUX18:2;                     // 5:4 MUX18 Configuration for OUT3 of EPWM-XBAR
    Uint16 MUX19:2;                     // 7:6 MUX19 Configuration for OUT3 of EPWM-XBAR
    Uint16 MUX20:2;                     // 9:8 MUX20 Configuration for OUT3 of EPWM-XBAR
    Uint16 MUX21:2;                     // 11:10 MUX21 Configuration for OUT3 of EPWM-XBAR
    Uint16 MUX22:2;                     // 13:12 MUX22 Configuration for OUT3 of EPWM-XBAR
    Uint16 MUX23:2;                     // 15:14 MUX23 Configuration for OUT3 of EPWM-XBAR
    Uint16 MUX24:2;                     // 17:16 MUX24 Configuration for OUT3 of EPWM-XBAR
    Uint16 MUX25:2;                     // 19:18 MUX25 Configuration for OUT3 of EPWM-XBAR
    Uint16 MUX26:2;                     // 21:20 MUX26 Configuration for OUT3 of EPWM-XBAR
    Uint16 MUX27:2;                     // 23:22 MUX27 Configuration for OUT3 of EPWM-XBAR
    Uint16 MUX28:2;                     // 25:24 MUX28 Configuration for OUT3 of EPWM-XBAR
    Uint16 MUX29:2;                     // 27:26 MUX29 Configuration for OUT3 of EPWM-XBAR
    Uint16 MUX30:2;                     // 29:28 MUX30 Configuration for OUT3 of EPWM-XBAR
    Uint16 MUX31:2;                     // 31:30 MUX31 Configuration for OUT3 of EPWM-XBAR
};

union OUT3MUX16TO31CFG_REG {
    Uint32  all;
    struct  OUT3MUX16TO31CFG_BITS  bit;
};

struct OUT3MUX32TO47CFG_BITS {          // bits description
    Uint16 MUX32:2;                     // 1:0 MUX32 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX33:2;                     // 3:2 MUX33 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX34:2;                     // 5:4 MUX34 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX35:2;                     // 7:6 MUX35 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX36:2;                     // 9:8 MUX36 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX37:2;                     // 11:10 MUX37 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX38:2;                     // 13:12 MUX38 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX39:2;                     // 15:14 MUX39 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX40:2;                     // 17:16 MUX40 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX41:2;                     // 19:18 MUX41 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX42:2;                     // 21:20 MUX42 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX43:2;                     // 23:22 MUX43 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX44:2;                     // 25:24 MUX44 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX45:2;                     // 27:26 MUX45 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX46:2;                     // 29:28 MUX46 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX47:2;                     // 31:30 MUX47 Configuration for TRIP4 of EPWM-XBAR
};

union OUT3MUX32TO47CFG_REG {
    Uint32  all;
    struct  OUT3MUX32TO47CFG_BITS  bit;
};

struct OUT3MUX48TO63CFG_BITS {          // bits description
    Uint16 MUX48:2;                     // 1:0 MUX48 Configuration for OUT3 of EPWM-XBAR
    Uint16 MUX49:2;                     // 3:2 MUX49 Configuration for OUT3 of EPWM-XBAR
    Uint16 MUX50:2;                     // 5:4 MUX50 Configuration for OUT3 of EPWM-XBAR
    Uint16 MUX51:2;                     // 7:6 MUX51 Configuration for OUT3 of EPWM-XBAR
    Uint16 MUX52:2;                     // 9:8 MUX52 Configuration for OUT3 of EPWM-XBAR
    Uint16 MUX53:2;                     // 11:10 MUX53 Configuration for OUT3 of EPWM-XBAR
    Uint16 MUX54:2;                     // 13:12 MUX54 Configuration for OUT3 of EPWM-XBAR
    Uint16 MUX55:2;                     // 15:14 MUX55 Configuration for OUT3 of EPWM-XBAR
    Uint16 MUX56:2;                     // 17:16 MUX56 Configuration for OUT3 of EPWM-XBAR
    Uint16 MUX57:2;                     // 19:18 MUX57 Configuration for OUT3 of EPWM-XBAR
    Uint16 MUX58:2;                     // 21:20 MUX58 Configuration for OUT3 of EPWM-XBAR
    Uint16 MUX59:2;                     // 23:22 MUX59 Configuration for OUT3 of EPWM-XBAR
    Uint16 MUX60:2;                     // 25:24 MUX60 Configuration for OUT3 of EPWM-XBAR
    Uint16 MUX61:2;                     // 27:26 MUX61 Configuration for OUT3 of EPWM-XBAR
    Uint16 MUX62:2;                     // 29:28 MUX62 Configuration for OUT3 of EPWM-XBAR
    Uint16 MUX63:2;                     // 31:30 MUX63 Configuration for OUT3 of EPWM-XBAR
};

union OUT3MUX48TO63CFG_REG {
    Uint32  all;
    struct  OUT3MUX48TO63CFG_BITS  bit;
};

struct OUT4MUX0TO15CFG_BITS {           // bits description
    Uint16 MUX0:2;                      // 1:0 MUX0 Configuration for OUT4 of EPWM-XBAR
    Uint16 MUX1:2;                      // 3:2 MUX1 Configuration for OUT4 of EPWM-XBAR
    Uint16 MUX2:2;                      // 5:4 MUX2 Configuration for OUT4 of EPWM-XBAR
    Uint16 MUX3:2;                      // 7:6 MUX3 Configuration for OUT4 of EPWM-XBAR
    Uint16 MUX4:2;                      // 9:8 MUX4 Configuration for OUT4 of EPWM-XBAR
    Uint16 MUX5:2;                      // 11:10 MUX5 Configuration for OUT4 of EPWM-XBAR
    Uint16 MUX6:2;                      // 13:12 MUX6 Configuration for OUT4 of EPWM-XBAR
    Uint16 MUX7:2;                      // 15:14 MUX7 Configuration for OUT4 of EPWM-XBAR
    Uint16 MUX8:2;                      // 17:16 MUX8 Configuration for OUT4 of EPWM-XBAR
    Uint16 MUX9:2;                      // 19:18 MUX9 Configuration for OUT4 of EPWM-XBAR
    Uint16 MUX10:2;                     // 21:20 MUX10 Configuration for OUT4 of EPWM-XBAR
    Uint16 MUX11:2;                     // 23:22 MUX11 Configuration for OUT4 of EPWM-XBAR
    Uint16 MUX12:2;                     // 25:24 MUX12 Configuration for OUT4 of EPWM-XBAR
    Uint16 MUX13:2;                     // 27:26 MUX13 Configuration for OUT4 of EPWM-XBAR
    Uint16 MUX14:2;                     // 29:28 MUX14 Configuration for OUT4 of EPWM-XBAR
    Uint16 MUX15:2;                     // 31:30 MUX15 Configuration for OUT4 of EPWM-XBAR
};

union OUT4MUX0TO15CFG_REG {
    Uint32  all;
    struct  OUT4MUX0TO15CFG_BITS  bit;
};

struct OUT4MUX16TO31CFG_BITS {          // bits description
    Uint16 MUX16:2;                     // 1:0 MUX16 Configuration for OUT4 of EPWM-XBAR
    Uint16 MUX17:2;                     // 3:2 MUX17 Configuration for OUT4 of EPWM-XBAR
    Uint16 MUX18:2;                     // 5:4 MUX18 Configuration for OUT4 of EPWM-XBAR
    Uint16 MUX19:2;                     // 7:6 MUX19 Configuration for OUT4 of EPWM-XBAR
    Uint16 MUX20:2;                     // 9:8 MUX20 Configuration for OUT4 of EPWM-XBAR
    Uint16 MUX21:2;                     // 11:10 MUX21 Configuration for OUT4 of EPWM-XBAR
    Uint16 MUX22:2;                     // 13:12 MUX22 Configuration for OUT4 of EPWM-XBAR
    Uint16 MUX23:2;                     // 15:14 MUX23 Configuration for OUT4 of EPWM-XBAR
    Uint16 MUX24:2;                     // 17:16 MUX24 Configuration for OUT4 of EPWM-XBAR
    Uint16 MUX25:2;                     // 19:18 MUX25 Configuration for OUT4 of EPWM-XBAR
    Uint16 MUX26:2;                     // 21:20 MUX26 Configuration for OUT4 of EPWM-XBAR
    Uint16 MUX27:2;                     // 23:22 MUX27 Configuration for OUT4 of EPWM-XBAR
    Uint16 MUX28:2;                     // 25:24 MUX28 Configuration for OUT4 of EPWM-XBAR
    Uint16 MUX29:2;                     // 27:26 MUX29 Configuration for OUT4 of EPWM-XBAR
    Uint16 MUX30:2;                     // 29:28 MUX30 Configuration for OUT4 of EPWM-XBAR
    Uint16 MUX31:2;                     // 31:30 MUX31 Configuration for OUT4 of EPWM-XBAR
};

union OUT4MUX16TO31CFG_REG {
    Uint32  all;
    struct  OUT4MUX16TO31CFG_BITS  bit;
};

struct OUT4MUX32TO47CFG_BITS {          // bits description
    Uint16 MUX32:2;                     // 1:0 MUX32 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX33:2;                     // 3:2 MUX33 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX34:2;                     // 5:4 MUX34 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX35:2;                     // 7:6 MUX35 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX36:2;                     // 9:8 MUX36 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX37:2;                     // 11:10 MUX37 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX38:2;                     // 13:12 MUX38 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX39:2;                     // 15:14 MUX39 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX40:2;                     // 17:16 MUX40 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX41:2;                     // 19:18 MUX41 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX42:2;                     // 21:20 MUX42 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX43:2;                     // 23:22 MUX43 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX44:2;                     // 25:24 MUX44 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX45:2;                     // 27:26 MUX45 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX46:2;                     // 29:28 MUX46 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX47:2;                     // 31:30 MUX47 Configuration for TRIP4 of EPWM-XBAR
};

union OUT4MUX32TO47CFG_REG {
    Uint32  all;
    struct  OUT4MUX32TO47CFG_BITS  bit;
};

struct OUT4MUX48TO63CFG_BITS {          // bits description
    Uint16 MUX48:2;                     // 1:0 MUX48 Configuration for OUT4 of EPWM-XBAR
    Uint16 MUX49:2;                     // 3:2 MUX49 Configuration for OUT4 of EPWM-XBAR
    Uint16 MUX50:2;                     // 5:4 MUX50 Configuration for OUT4 of EPWM-XBAR
    Uint16 MUX51:2;                     // 7:6 MUX51 Configuration for OUT4 of EPWM-XBAR
    Uint16 MUX52:2;                     // 9:8 MUX52 Configuration for OUT4 of EPWM-XBAR
    Uint16 MUX53:2;                     // 11:10 MUX53 Configuration for OUT4 of EPWM-XBAR
    Uint16 MUX54:2;                     // 13:12 MUX54 Configuration for OUT4 of EPWM-XBAR
    Uint16 MUX55:2;                     // 15:14 MUX55 Configuration for OUT4 of EPWM-XBAR
    Uint16 MUX56:2;                     // 17:16 MUX56 Configuration for OUT4 of EPWM-XBAR
    Uint16 MUX57:2;                     // 19:18 MUX57 Configuration for OUT4 of EPWM-XBAR
    Uint16 MUX58:2;                     // 21:20 MUX58 Configuration for OUT4 of EPWM-XBAR
    Uint16 MUX59:2;                     // 23:22 MUX59 Configuration for OUT4 of EPWM-XBAR
    Uint16 MUX60:2;                     // 25:24 MUX60 Configuration for OUT4 of EPWM-XBAR
    Uint16 MUX61:2;                     // 27:26 MUX61 Configuration for OUT4 of EPWM-XBAR
    Uint16 MUX62:2;                     // 29:28 MUX62 Configuration for OUT4 of EPWM-XBAR
    Uint16 MUX63:2;                     // 31:30 MUX63 Configuration for OUT4 of EPWM-XBAR
};

union OUT4MUX48TO63CFG_REG {
    Uint32  all;
    struct  OUT4MUX48TO63CFG_BITS  bit;
};

struct OUT5MUX0TO15CFG_BITS {           // bits description
    Uint16 MUX0:2;                      // 1:0 MUX0 Configuration for OUT5 of EPWM-XBAR
    Uint16 MUX1:2;                      // 3:2 MUX1 Configuration for OUT5 of EPWM-XBAR
    Uint16 MUX2:2;                      // 5:4 MUX2 Configuration for OUT5 of EPWM-XBAR
    Uint16 MUX3:2;                      // 7:6 MUX3 Configuration for OUT5 of EPWM-XBAR
    Uint16 MUX4:2;                      // 9:8 MUX4 Configuration for OUT5 of EPWM-XBAR
    Uint16 MUX5:2;                      // 11:10 MUX5 Configuration for OUT5 of EPWM-XBAR
    Uint16 MUX6:2;                      // 13:12 MUX6 Configuration for OUT5 of EPWM-XBAR
    Uint16 MUX7:2;                      // 15:14 MUX7 Configuration for OUT5 of EPWM-XBAR
    Uint16 MUX8:2;                      // 17:16 MUX8 Configuration for OUT5 of EPWM-XBAR
    Uint16 MUX9:2;                      // 19:18 MUX9 Configuration for OUT5 of EPWM-XBAR
    Uint16 MUX10:2;                     // 21:20 MUX10 Configuration for OUT5 of EPWM-XBAR
    Uint16 MUX11:2;                     // 23:22 MUX11 Configuration for OUT5 of EPWM-XBAR
    Uint16 MUX12:2;                     // 25:24 MUX12 Configuration for OUT5 of EPWM-XBAR
    Uint16 MUX13:2;                     // 27:26 MUX13 Configuration for OUT5 of EPWM-XBAR
    Uint16 MUX14:2;                     // 29:28 MUX14 Configuration for OUT5 of EPWM-XBAR
    Uint16 MUX15:2;                     // 31:30 MUX15 Configuration for OUT5 of EPWM-XBAR
};

union OUT5MUX0TO15CFG_REG {
    Uint32  all;
    struct  OUT5MUX0TO15CFG_BITS  bit;
};

struct OUT5MUX16TO31CFG_BITS {          // bits description
    Uint16 MUX16:2;                     // 1:0 MUX16 Configuration for OUT5 of EPWM-XBAR
    Uint16 MUX17:2;                     // 3:2 MUX17 Configuration for OUT5 of EPWM-XBAR
    Uint16 MUX18:2;                     // 5:4 MUX18 Configuration for OUT5 of EPWM-XBAR
    Uint16 MUX19:2;                     // 7:6 MUX19 Configuration for OUT5 of EPWM-XBAR
    Uint16 MUX20:2;                     // 9:8 MUX20 Configuration for OUT5 of EPWM-XBAR
    Uint16 MUX21:2;                     // 11:10 MUX21 Configuration for OUT5 of EPWM-XBAR
    Uint16 MUX22:2;                     // 13:12 MUX22 Configuration for OUT5 of EPWM-XBAR
    Uint16 MUX23:2;                     // 15:14 MUX23 Configuration for OUT5 of EPWM-XBAR
    Uint16 MUX24:2;                     // 17:16 MUX24 Configuration for OUT5 of EPWM-XBAR
    Uint16 MUX25:2;                     // 19:18 MUX25 Configuration for OUT5 of EPWM-XBAR
    Uint16 MUX26:2;                     // 21:20 MUX26 Configuration for OUT5 of EPWM-XBAR
    Uint16 MUX27:2;                     // 23:22 MUX27 Configuration for OUT5 of EPWM-XBAR
    Uint16 MUX28:2;                     // 25:24 MUX28 Configuration for OUT5 of EPWM-XBAR
    Uint16 MUX29:2;                     // 27:26 MUX29 Configuration for OUT5 of EPWM-XBAR
    Uint16 MUX30:2;                     // 29:28 MUX30 Configuration for OUT5 of EPWM-XBAR
    Uint16 MUX31:2;                     // 31:30 MUX31 Configuration for OUT5 of EPWM-XBAR
};

union OUT5MUX16TO31CFG_REG {
    Uint32  all;
    struct  OUT5MUX16TO31CFG_BITS  bit;
};

struct OUT5MUX32TO47CFG_BITS {          // bits description
    Uint16 MUX32:2;                     // 1:0 MUX32 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX33:2;                     // 3:2 MUX33 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX34:2;                     // 5:4 MUX34 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX35:2;                     // 7:6 MUX35 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX36:2;                     // 9:8 MUX36 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX37:2;                     // 11:10 MUX37 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX38:2;                     // 13:12 MUX38 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX39:2;                     // 15:14 MUX39 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX40:2;                     // 17:16 MUX40 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX41:2;                     // 19:18 MUX41 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX42:2;                     // 21:20 MUX42 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX43:2;                     // 23:22 MUX43 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX44:2;                     // 25:24 MUX44 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX45:2;                     // 27:26 MUX45 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX46:2;                     // 29:28 MUX46 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX47:2;                     // 31:30 MUX47 Configuration for TRIP4 of EPWM-XBAR
};

union OUT5MUX32TO47CFG_REG {
    Uint32  all;
    struct  OUT5MUX32TO47CFG_BITS  bit;
};

struct OUT5MUX48TO63CFG_BITS {          // bits description
    Uint16 MUX48:2;                     // 1:0 MUX48 Configuration for OUT5 of EPWM-XBAR
    Uint16 MUX49:2;                     // 3:2 MUX49 Configuration for OUT5 of EPWM-XBAR
    Uint16 MUX50:2;                     // 5:4 MUX50 Configuration for OUT5 of EPWM-XBAR
    Uint16 MUX51:2;                     // 7:6 MUX51 Configuration for OUT5 of EPWM-XBAR
    Uint16 MUX52:2;                     // 9:8 MUX52 Configuration for OUT5 of EPWM-XBAR
    Uint16 MUX53:2;                     // 11:10 MUX53 Configuration for OUT5 of EPWM-XBAR
    Uint16 MUX54:2;                     // 13:12 MUX54 Configuration for OUT5 of EPWM-XBAR
    Uint16 MUX55:2;                     // 15:14 MUX55 Configuration for OUT5 of EPWM-XBAR
    Uint16 MUX56:2;                     // 17:16 MUX56 Configuration for OUT5 of EPWM-XBAR
    Uint16 MUX57:2;                     // 19:18 MUX57 Configuration for OUT5 of EPWM-XBAR
    Uint16 MUX58:2;                     // 21:20 MUX58 Configuration for OUT5 of EPWM-XBAR
    Uint16 MUX59:2;                     // 23:22 MUX59 Configuration for OUT5 of EPWM-XBAR
    Uint16 MUX60:2;                     // 25:24 MUX60 Configuration for OUT5 of EPWM-XBAR
    Uint16 MUX61:2;                     // 27:26 MUX61 Configuration for OUT5 of EPWM-XBAR
    Uint16 MUX62:2;                     // 29:28 MUX62 Configuration for OUT5 of EPWM-XBAR
    Uint16 MUX63:2;                     // 31:30 MUX63 Configuration for OUT5 of EPWM-XBAR
};

union OUT5MUX48TO63CFG_REG {
    Uint32  all;
    struct  OUT5MUX48TO63CFG_BITS  bit;
};

struct OUT6MUX0TO15CFG_BITS {           // bits description
    Uint16 MUX0:2;                      // 1:0 MUX0 Configuration for OUT6 of EPWM-XBAR
    Uint16 MUX1:2;                      // 3:2 MUX1 Configuration for OUT6 of EPWM-XBAR
    Uint16 MUX2:2;                      // 5:4 MUX2 Configuration for OUT6 of EPWM-XBAR
    Uint16 MUX3:2;                      // 7:6 MUX3 Configuration for OUT6 of EPWM-XBAR
    Uint16 MUX4:2;                      // 9:8 MUX4 Configuration for OUT6 of EPWM-XBAR
    Uint16 MUX5:2;                      // 11:10 MUX5 Configuration for OUT6 of EPWM-XBAR
    Uint16 MUX6:2;                      // 13:12 MUX6 Configuration for OUT6 of EPWM-XBAR
    Uint16 MUX7:2;                      // 15:14 MUX7 Configuration for OUT6 of EPWM-XBAR
    Uint16 MUX8:2;                      // 17:16 MUX8 Configuration for OUT6 of EPWM-XBAR
    Uint16 MUX9:2;                      // 19:18 MUX9 Configuration for OUT6 of EPWM-XBAR
    Uint16 MUX10:2;                     // 21:20 MUX10 Configuration for OUT6 of EPWM-XBAR
    Uint16 MUX11:2;                     // 23:22 MUX11 Configuration for OUT6 of EPWM-XBAR
    Uint16 MUX12:2;                     // 25:24 MUX12 Configuration for OUT6 of EPWM-XBAR
    Uint16 MUX13:2;                     // 27:26 MUX13 Configuration for OUT6 of EPWM-XBAR
    Uint16 MUX14:2;                     // 29:28 MUX14 Configuration for OUT6 of EPWM-XBAR
    Uint16 MUX15:2;                     // 31:30 MUX15 Configuration for OUT6 of EPWM-XBAR
};

union OUT6MUX0TO15CFG_REG {
    Uint32  all;
    struct  OUT6MUX0TO15CFG_BITS  bit;
};

struct OUT6MUX16TO31CFG_BITS {          // bits description
    Uint16 MUX16:2;                     // 1:0 MUX16 Configuration for OUT6 of EPWM-XBAR
    Uint16 MUX17:2;                     // 3:2 MUX17 Configuration for OUT6 of EPWM-XBAR
    Uint16 MUX18:2;                     // 5:4 MUX18 Configuration for OUT6 of EPWM-XBAR
    Uint16 MUX19:2;                     // 7:6 MUX19 Configuration for OUT6 of EPWM-XBAR
    Uint16 MUX20:2;                     // 9:8 MUX20 Configuration for OUT6 of EPWM-XBAR
    Uint16 MUX21:2;                     // 11:10 MUX21 Configuration for OUT6 of EPWM-XBAR
    Uint16 MUX22:2;                     // 13:12 MUX22 Configuration for OUT6 of EPWM-XBAR
    Uint16 MUX23:2;                     // 15:14 MUX23 Configuration for OUT6 of EPWM-XBAR
    Uint16 MUX24:2;                     // 17:16 MUX24 Configuration for OUT6 of EPWM-XBAR
    Uint16 MUX25:2;                     // 19:18 MUX25 Configuration for OUT6 of EPWM-XBAR
    Uint16 MUX26:2;                     // 21:20 MUX26 Configuration for OUT6 of EPWM-XBAR
    Uint16 MUX27:2;                     // 23:22 MUX27 Configuration for OUT6 of EPWM-XBAR
    Uint16 MUX28:2;                     // 25:24 MUX28 Configuration for OUT6 of EPWM-XBAR
    Uint16 MUX29:2;                     // 27:26 MUX29 Configuration for OUT6 of EPWM-XBAR
    Uint16 MUX30:2;                     // 29:28 MUX30 Configuration for OUT6 of EPWM-XBAR
    Uint16 MUX31:2;                     // 31:30 MUX31 Configuration for OUT6 of EPWM-XBAR
};

union OUT6MUX16TO31CFG_REG {
    Uint32  all;
    struct  OUT6MUX16TO31CFG_BITS  bit;
};

struct OUT6MUX32TO47CFG_BITS {          // bits description
    Uint16 MUX32:2;                     // 1:0 MUX32 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX33:2;                     // 3:2 MUX33 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX34:2;                     // 5:4 MUX34 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX35:2;                     // 7:6 MUX35 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX36:2;                     // 9:8 MUX36 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX37:2;                     // 11:10 MUX37 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX38:2;                     // 13:12 MUX38 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX39:2;                     // 15:14 MUX39 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX40:2;                     // 17:16 MUX40 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX41:2;                     // 19:18 MUX41 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX42:2;                     // 21:20 MUX42 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX43:2;                     // 23:22 MUX43 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX44:2;                     // 25:24 MUX44 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX45:2;                     // 27:26 MUX45 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX46:2;                     // 29:28 MUX46 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX47:2;                     // 31:30 MUX47 Configuration for TRIP4 of EPWM-XBAR
};

union OUT6MUX32TO47CFG_REG {
    Uint32  all;
    struct  OUT6MUX32TO47CFG_BITS  bit;
};

struct OUT6MUX48TO63CFG_BITS {          // bits description
    Uint16 MUX48:2;                     // 1:0 MUX48 Configuration for OUT6 of EPWM-XBAR
    Uint16 MUX49:2;                     // 3:2 MUX49 Configuration for OUT6 of EPWM-XBAR
    Uint16 MUX50:2;                     // 5:4 MUX50 Configuration for OUT6 of EPWM-XBAR
    Uint16 MUX51:2;                     // 7:6 MUX51 Configuration for OUT6 of EPWM-XBAR
    Uint16 MUX52:2;                     // 9:8 MUX52 Configuration for OUT6 of EPWM-XBAR
    Uint16 MUX53:2;                     // 11:10 MUX53 Configuration for OUT6 of EPWM-XBAR
    Uint16 MUX54:2;                     // 13:12 MUX54 Configuration for OUT6 of EPWM-XBAR
    Uint16 MUX55:2;                     // 15:14 MUX55 Configuration for OUT6 of EPWM-XBAR
    Uint16 MUX56:2;                     // 17:16 MUX56 Configuration for OUT6 of EPWM-XBAR
    Uint16 MUX57:2;                     // 19:18 MUX57 Configuration for OUT6 of EPWM-XBAR
    Uint16 MUX58:2;                     // 21:20 MUX58 Configuration for OUT6 of EPWM-XBAR
    Uint16 MUX59:2;                     // 23:22 MUX59 Configuration for OUT6 of EPWM-XBAR
    Uint16 MUX60:2;                     // 25:24 MUX60 Configuration for OUT6 of EPWM-XBAR
    Uint16 MUX61:2;                     // 27:26 MUX61 Configuration for OUT6 of EPWM-XBAR
    Uint16 MUX62:2;                     // 29:28 MUX62 Configuration for OUT6 of EPWM-XBAR
    Uint16 MUX63:2;                     // 31:30 MUX63 Configuration for OUT6 of EPWM-XBAR
};

union OUT6MUX48TO63CFG_REG {
    Uint32  all;
    struct  OUT6MUX48TO63CFG_BITS  bit;
};

struct OUT7MUX0TO15CFG_BITS {           // bits description
    Uint16 MUX0:2;                      // 1:0 MUX0 Configuration for OUT7 of EPWM-XBAR
    Uint16 MUX1:2;                      // 3:2 MUX1 Configuration for OUT7 of EPWM-XBAR
    Uint16 MUX2:2;                      // 5:4 MUX2 Configuration for OUT7 of EPWM-XBAR
    Uint16 MUX3:2;                      // 7:6 MUX3 Configuration for OUT7 of EPWM-XBAR
    Uint16 MUX4:2;                      // 9:8 MUX4 Configuration for OUT7 of EPWM-XBAR
    Uint16 MUX5:2;                      // 11:10 MUX5 Configuration for OUT7 of EPWM-XBAR
    Uint16 MUX6:2;                      // 13:12 MUX6 Configuration for OUT7 of EPWM-XBAR
    Uint16 MUX7:2;                      // 15:14 MUX7 Configuration for OUT7 of EPWM-XBAR
    Uint16 MUX8:2;                      // 17:16 MUX8 Configuration for OUT7 of EPWM-XBAR
    Uint16 MUX9:2;                      // 19:18 MUX9 Configuration for OUT7 of EPWM-XBAR
    Uint16 MUX10:2;                     // 21:20 MUX10 Configuration for OUT7 of EPWM-XBAR
    Uint16 MUX11:2;                     // 23:22 MUX11 Configuration for OUT7 of EPWM-XBAR
    Uint16 MUX12:2;                     // 25:24 MUX12 Configuration for OUT7 of EPWM-XBAR
    Uint16 MUX13:2;                     // 27:26 MUX13 Configuration for OUT7 of EPWM-XBAR
    Uint16 MUX14:2;                     // 29:28 MUX14 Configuration for OUT7 of EPWM-XBAR
    Uint16 MUX15:2;                     // 31:30 MUX15 Configuration for OUT7 of EPWM-XBAR
};

union OUT7MUX0TO15CFG_REG {
    Uint32  all;
    struct  OUT7MUX0TO15CFG_BITS  bit;
};

struct OUT7MUX16TO31CFG_BITS {          // bits description
    Uint16 MUX16:2;                     // 1:0 MUX16 Configuration for OUT7 of EPWM-XBAR
    Uint16 MUX17:2;                     // 3:2 MUX17 Configuration for OUT7 of EPWM-XBAR
    Uint16 MUX18:2;                     // 5:4 MUX18 Configuration for OUT7 of EPWM-XBAR
    Uint16 MUX19:2;                     // 7:6 MUX19 Configuration for OUT7 of EPWM-XBAR
    Uint16 MUX20:2;                     // 9:8 MUX20 Configuration for OUT7 of EPWM-XBAR
    Uint16 MUX21:2;                     // 11:10 MUX21 Configuration for OUT7 of EPWM-XBAR
    Uint16 MUX22:2;                     // 13:12 MUX22 Configuration for OUT7 of EPWM-XBAR
    Uint16 MUX23:2;                     // 15:14 MUX23 Configuration for OUT7 of EPWM-XBAR
    Uint16 MUX24:2;                     // 17:16 MUX24 Configuration for OUT7 of EPWM-XBAR
    Uint16 MUX25:2;                     // 19:18 MUX25 Configuration for OUT7 of EPWM-XBAR
    Uint16 MUX26:2;                     // 21:20 MUX26 Configuration for OUT7 of EPWM-XBAR
    Uint16 MUX27:2;                     // 23:22 MUX27 Configuration for OUT7 of EPWM-XBAR
    Uint16 MUX28:2;                     // 25:24 MUX28 Configuration for OUT7 of EPWM-XBAR
    Uint16 MUX29:2;                     // 27:26 MUX29 Configuration for OUT7 of EPWM-XBAR
    Uint16 MUX30:2;                     // 29:28 MUX30 Configuration for OUT7 of EPWM-XBAR
    Uint16 MUX31:2;                     // 31:30 MUX31 Configuration for OUT7 of EPWM-XBAR
};

union OUT7MUX16TO31CFG_REG {
    Uint32  all;
    struct  OUT7MUX16TO31CFG_BITS  bit;
};

struct OUT7MUX32TO47CFG_BITS {          // bits description
    Uint16 MUX32:2;                     // 1:0 MUX32 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX33:2;                     // 3:2 MUX33 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX34:2;                     // 5:4 MUX34 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX35:2;                     // 7:6 MUX35 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX36:2;                     // 9:8 MUX36 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX37:2;                     // 11:10 MUX37 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX38:2;                     // 13:12 MUX38 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX39:2;                     // 15:14 MUX39 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX40:2;                     // 17:16 MUX40 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX41:2;                     // 19:18 MUX41 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX42:2;                     // 21:20 MUX42 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX43:2;                     // 23:22 MUX43 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX44:2;                     // 25:24 MUX44 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX45:2;                     // 27:26 MUX45 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX46:2;                     // 29:28 MUX46 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX47:2;                     // 31:30 MUX47 Configuration for TRIP4 of EPWM-XBAR
};

union OUT7MUX32TO47CFG_REG {
    Uint32  all;
    struct  OUT7MUX32TO47CFG_BITS  bit;
};

struct OUT7MUX48TO63CFG_BITS {          // bits description
    Uint16 MUX48:2;                     // 1:0 MUX48 Configuration for OUT7 of EPWM-XBAR
    Uint16 MUX49:2;                     // 3:2 MUX49 Configuration for OUT7 of EPWM-XBAR
    Uint16 MUX50:2;                     // 5:4 MUX50 Configuration for OUT7 of EPWM-XBAR
    Uint16 MUX51:2;                     // 7:6 MUX51 Configuration for OUT7 of EPWM-XBAR
    Uint16 MUX52:2;                     // 9:8 MUX52 Configuration for OUT7 of EPWM-XBAR
    Uint16 MUX53:2;                     // 11:10 MUX53 Configuration for OUT7 of EPWM-XBAR
    Uint16 MUX54:2;                     // 13:12 MUX54 Configuration for OUT7 of EPWM-XBAR
    Uint16 MUX55:2;                     // 15:14 MUX55 Configuration for OUT7 of EPWM-XBAR
    Uint16 MUX56:2;                     // 17:16 MUX56 Configuration for OUT7 of EPWM-XBAR
    Uint16 MUX57:2;                     // 19:18 MUX57 Configuration for OUT7 of EPWM-XBAR
    Uint16 MUX58:2;                     // 21:20 MUX58 Configuration for OUT7 of EPWM-XBAR
    Uint16 MUX59:2;                     // 23:22 MUX59 Configuration for OUT7 of EPWM-XBAR
    Uint16 MUX60:2;                     // 25:24 MUX60 Configuration for OUT7 of EPWM-XBAR
    Uint16 MUX61:2;                     // 27:26 MUX61 Configuration for OUT7 of EPWM-XBAR
    Uint16 MUX62:2;                     // 29:28 MUX62 Configuration for OUT7 of EPWM-XBAR
    Uint16 MUX63:2;                     // 31:30 MUX63 Configuration for OUT7 of EPWM-XBAR
};

union OUT7MUX48TO63CFG_REG {
    Uint32  all;
    struct  OUT7MUX48TO63CFG_BITS  bit;
};

struct OUT8MUX0TO15CFG_BITS {           // bits description
    Uint16 MUX0:2;                      // 1:0 MUX0 Configuration for OUT8 of EPWM-XBAR
    Uint16 MUX1:2;                      // 3:2 MUX1 Configuration for OUT8 of EPWM-XBAR
    Uint16 MUX2:2;                      // 5:4 MUX2 Configuration for OUT8 of EPWM-XBAR
    Uint16 MUX3:2;                      // 7:6 MUX3 Configuration for OUT8 of EPWM-XBAR
    Uint16 MUX4:2;                      // 9:8 MUX4 Configuration for OUT8 of EPWM-XBAR
    Uint16 MUX5:2;                      // 11:10 MUX5 Configuration for OUT8 of EPWM-XBAR
    Uint16 MUX6:2;                      // 13:12 MUX6 Configuration for OUT8 of EPWM-XBAR
    Uint16 MUX7:2;                      // 15:14 MUX7 Configuration for OUT8 of EPWM-XBAR
    Uint16 MUX8:2;                      // 17:16 MUX8 Configuration for OUT8 of EPWM-XBAR
    Uint16 MUX9:2;                      // 19:18 MUX9 Configuration for OUT8 of EPWM-XBAR
    Uint16 MUX10:2;                     // 21:20 MUX10 Configuration for OUT8 of EPWM-XBAR
    Uint16 MUX11:2;                     // 23:22 MUX11 Configuration for OUT8 of EPWM-XBAR
    Uint16 MUX12:2;                     // 25:24 MUX12 Configuration for OUT8 of EPWM-XBAR
    Uint16 MUX13:2;                     // 27:26 MUX13 Configuration for OUT8 of EPWM-XBAR
    Uint16 MUX14:2;                     // 29:28 MUX14 Configuration for OUT8 of EPWM-XBAR
    Uint16 MUX15:2;                     // 31:30 MUX15 Configuration for OUT8 of EPWM-XBAR
};

union OUT8MUX0TO15CFG_REG {
    Uint32  all;
    struct  OUT8MUX0TO15CFG_BITS  bit;
};

struct OUT8MUX16TO31CFG_BITS {          // bits description
    Uint16 MUX16:2;                     // 1:0 MUX16 Configuration for OUT8 of EPWM-XBAR
    Uint16 MUX17:2;                     // 3:2 MUX17 Configuration for OUT8 of EPWM-XBAR
    Uint16 MUX18:2;                     // 5:4 MUX18 Configuration for OUT8 of EPWM-XBAR
    Uint16 MUX19:2;                     // 7:6 MUX19 Configuration for OUT8 of EPWM-XBAR
    Uint16 MUX20:2;                     // 9:8 MUX20 Configuration for OUT8 of EPWM-XBAR
    Uint16 MUX21:2;                     // 11:10 MUX21 Configuration for OUT8 of EPWM-XBAR
    Uint16 MUX22:2;                     // 13:12 MUX22 Configuration for OUT8 of EPWM-XBAR
    Uint16 MUX23:2;                     // 15:14 MUX23 Configuration for OUT8 of EPWM-XBAR
    Uint16 MUX24:2;                     // 17:16 MUX24 Configuration for OUT8 of EPWM-XBAR
    Uint16 MUX25:2;                     // 19:18 MUX25 Configuration for OUT8 of EPWM-XBAR
    Uint16 MUX26:2;                     // 21:20 MUX26 Configuration for OUT8 of EPWM-XBAR
    Uint16 MUX27:2;                     // 23:22 MUX27 Configuration for OUT8 of EPWM-XBAR
    Uint16 MUX28:2;                     // 25:24 MUX28 Configuration for OUT8 of EPWM-XBAR
    Uint16 MUX29:2;                     // 27:26 MUX29 Configuration for OUT8 of EPWM-XBAR
    Uint16 MUX30:2;                     // 29:28 MUX30 Configuration for OUT8 of EPWM-XBAR
    Uint16 MUX31:2;                     // 31:30 MUX31 Configuration for OUT8 of EPWM-XBAR
};

union OUT8MUX16TO31CFG_REG {
    Uint32  all;
    struct  OUT8MUX16TO31CFG_BITS  bit;
};

struct OUT8MUX32TO47CFG_BITS {          // bits description
    Uint16 MUX32:2;                     // 1:0 MUX32 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX33:2;                     // 3:2 MUX33 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX34:2;                     // 5:4 MUX34 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX35:2;                     // 7:6 MUX35 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX36:2;                     // 9:8 MUX36 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX37:2;                     // 11:10 MUX37 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX38:2;                     // 13:12 MUX38 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX39:2;                     // 15:14 MUX39 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX40:2;                     // 17:16 MUX40 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX41:2;                     // 19:18 MUX41 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX42:2;                     // 21:20 MUX42 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX43:2;                     // 23:22 MUX43 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX44:2;                     // 25:24 MUX44 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX45:2;                     // 27:26 MUX45 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX46:2;                     // 29:28 MUX46 Configuration for TRIP4 of EPWM-XBAR
    Uint16 MUX47:2;                     // 31:30 MUX47 Configuration for TRIP4 of EPWM-XBAR
};

union OUT8MUX32TO47CFG_REG {
    Uint32  all;
    struct  OUT8MUX32TO47CFG_BITS  bit;
};

struct OUT8MUX48TO63CFG_BITS {          // bits description
    Uint16 MUX48:2;                     // 1:0 MUX48 Configuration for OUT8 of EPWM-XBAR
    Uint16 MUX49:2;                     // 3:2 MUX49 Configuration for OUT8 of EPWM-XBAR
    Uint16 MUX50:2;                     // 5:4 MUX50 Configuration for OUT8 of EPWM-XBAR
    Uint16 MUX51:2;                     // 7:6 MUX51 Configuration for OUT8 of EPWM-XBAR
    Uint16 MUX52:2;                     // 9:8 MUX52 Configuration for OUT8 of EPWM-XBAR
    Uint16 MUX53:2;                     // 11:10 MUX53 Configuration for OUT8 of EPWM-XBAR
    Uint16 MUX54:2;                     // 13:12 MUX54 Configuration for OUT8 of EPWM-XBAR
    Uint16 MUX55:2;                     // 15:14 MUX55 Configuration for OUT8 of EPWM-XBAR
    Uint16 MUX56:2;                     // 17:16 MUX56 Configuration for OUT8 of EPWM-XBAR
    Uint16 MUX57:2;                     // 19:18 MUX57 Configuration for OUT8 of EPWM-XBAR
    Uint16 MUX58:2;                     // 21:20 MUX58 Configuration for OUT8 of EPWM-XBAR
    Uint16 MUX59:2;                     // 23:22 MUX59 Configuration for OUT8 of EPWM-XBAR
    Uint16 MUX60:2;                     // 25:24 MUX60 Configuration for OUT8 of EPWM-XBAR
    Uint16 MUX61:2;                     // 27:26 MUX61 Configuration for OUT8 of EPWM-XBAR
    Uint16 MUX62:2;                     // 29:28 MUX62 Configuration for OUT8 of EPWM-XBAR
    Uint16 MUX63:2;                     // 31:30 MUX63 Configuration for OUT8 of EPWM-XBAR
};

union OUT8MUX48TO63CFG_REG {
    Uint32  all;
    struct  OUT8MUX48TO63CFG_BITS  bit;
};

struct OUT1MUXENABLE_BITS {             // bits description
    Uint16 MUX0:1;                      // 0 MUX0 to drive OUT1 of EPWM-XBAR
    Uint16 MUX1:1;                      // 1 MUX1 to drive OUT1 of EPWM-XBAR
    Uint16 MUX2:1;                      // 2 MUX2 to drive OUT1 of EPWM-XBAR
    Uint16 MUX3:1;                      // 3 MUX3 to drive OUT1 of EPWM-XBAR
    Uint16 MUX4:1;                      // 4 MUX4 to drive OUT1 of EPWM-XBAR
    Uint16 MUX5:1;                      // 5 MUX5 to drive OUT1 of EPWM-XBAR
    Uint16 MUX6:1;                      // 6 MUX6 to drive OUT1 of EPWM-XBAR
    Uint16 MUX7:1;                      // 7 MUX7 to drive OUT1 of EPWM-XBAR
    Uint16 MUX8:1;                      // 8 MUX8 to drive OUT1 of EPWM-XBAR
    Uint16 MUX9:1;                      // 9 MUX9 to drive OUT1 of EPWM-XBAR
    Uint16 MUX10:1;                     // 10 MUX10 to drive OUT1 of EPWM-XBAR
    Uint16 MUX11:1;                     // 11 MUX11 to drive OUT1 of EPWM-XBAR
    Uint16 MUX12:1;                     // 12 MUX12 to drive OUT1 of EPWM-XBAR
    Uint16 MUX13:1;                     // 13 MUX13 to drive OUT1 of EPWM-XBAR
    Uint16 MUX14:1;                     // 14 MUX14 to drive OUT1 of EPWM-XBAR
    Uint16 MUX15:1;                     // 15 MUX15 to drive OUT1 of EPWM-XBAR
    Uint16 MUX16:1;                     // 16 MUX16 to drive OUT1 of EPWM-XBAR
    Uint16 MUX17:1;                     // 17 MUX17 to drive OUT1 of EPWM-XBAR
    Uint16 MUX18:1;                     // 18 MUX18 to drive OUT1 of EPWM-XBAR
    Uint16 MUX19:1;                     // 19 MUX19 to drive OUT1 of EPWM-XBAR
    Uint16 MUX20:1;                     // 20 MUX20 to drive OUT1 of EPWM-XBAR
    Uint16 MUX21:1;                     // 21 MUX21 to drive OUT1 of EPWM-XBAR
    Uint16 MUX22:1;                     // 22 MUX22 to drive OUT1 of EPWM-XBAR
    Uint16 MUX23:1;                     // 23 MUX23 to drive OUT1 of EPWM-XBAR
    Uint16 MUX24:1;                     // 24 MUX24 to drive OUT1 of EPWM-XBAR
    Uint16 MUX25:1;                     // 25 MUX25 to drive OUT1 of EPWM-XBAR
    Uint16 MUX26:1;                     // 26 MUX26 to drive OUT1 of EPWM-XBAR
    Uint16 MUX27:1;                     // 27 MUX27 to drive OUT1 of EPWM-XBAR
    Uint16 MUX28:1;                     // 28 MUX28 to drive OUT1 of EPWM-XBAR
    Uint16 MUX29:1;                     // 29 MUX29 to drive OUT1 of EPWM-XBAR
    Uint16 MUX30:1;                     // 30 MUX30 to drive OUT1 of EPWM-XBAR
    Uint16 MUX31:1;                     // 31 MUX31 to drive OUT1 of EPWM-XBAR
};

union OUT1MUXENABLE_REG {
    Uint32  all;
    struct  OUT1MUXENABLE_BITS  bit;
};

struct OUT1MUXENABLE32TO64_BITS {       // bits description
    Uint16 MUX32:1;                     // 0 MUX32 to drive OUT1 of EPWM-XBAR
    Uint16 MUX33:1;                     // 1 MUX33 to drive OUT1 of EPWM-XBAR
    Uint16 MUX34:1;                     // 2 MUX34 to drive OUT1 of EPWM-XBAR
    Uint16 MUX35:1;                     // 3 MUX35 to drive OUT1 of EPWM-XBAR
    Uint16 MUX36:1;                     // 4 MUX36 to drive OUT1 of EPWM-XBAR
    Uint16 MUX37:1;                     // 5 MUX37 to drive OUT1 of EPWM-XBAR
    Uint16 MUX38:1;                     // 6 MUX38 to drive OUT1 of EPWM-XBAR
    Uint16 MUX39:1;                     // 7 MUX39 to drive OUT1 of EPWM-XBAR
    Uint16 MUX40:1;                     // 8 MUX40 to drive OUT1 of EPWM-XBAR
    Uint16 MUX41:1;                     // 9 MUX41 to drive OUT1 of EPWM-XBAR
    Uint16 MUX42:1;                     // 10 MUX42 to drive OUT1 of EPWM-XBAR
    Uint16 MUX43:1;                     // 11 MUX43 to drive OUT1 of EPWM-XBAR
    Uint16 MUX44:1;                     // 12 MUX44 to drive OUT1 of EPWM-XBAR
    Uint16 MUX45:1;                     // 13 MUX45 to drive OUT1 of EPWM-XBAR
    Uint16 MUX46:1;                     // 14 MUX46 to drive OUT1 of EPWM-XBAR
    Uint16 MUX47:1;                     // 15 MUX47 to drive OUT1 of EPWM-XBAR
    Uint16 MUX48:1;                     // 16 MUX48 to drive OUT1 of EPWM-XBAR
    Uint16 MUX49:1;                     // 17 MUX49 to drive OUT1 of EPWM-XBAR
    Uint16 MUX50:1;                     // 18 MUX50 to drive OUT1 of EPWM-XBAR
    Uint16 MUX51:1;                     // 19 MUX51 to drive OUT1 of EPWM-XBAR
    Uint16 MUX52:1;                     // 20 MUX52 to drive OUT1 of EPWM-XBAR
    Uint16 MUX53:1;                     // 21 MUX53 to drive OUT1 of EPWM-XBAR
    Uint16 MUX54:1;                     // 22 MUX54 to drive OUT1 of EPWM-XBAR
    Uint16 MUX55:1;                     // 23 MUX55 to drive OUT1 of EPWM-XBAR
    Uint16 MUX56:1;                     // 24 MUX56 to drive OUT1 of EPWM-XBAR
    Uint16 MUX57:1;                     // 25 MUX57 to drive OUT1 of EPWM-XBAR
    Uint16 MUX58:1;                     // 26 MUX58 to drive OUT1 of EPWM-XBAR
    Uint16 MUX59:1;                     // 27 MUX59 to drive OUT1 of EPWM-XBAR
    Uint16 MUX60:1;                     // 28 MUX60 to drive OUT1 of EPWM-XBAR
    Uint16 MUX61:1;                     // 29 MUX61 to drive OUT1 of EPWM-XBAR
    Uint16 MUX62:1;                     // 30 MUX62 to drive OUT1 of EPWM-XBAR
    Uint16 MUX63:1;                     // 31 MUX63 to drive OUT1 of EPWM-XBAR
};

union OUT1MUXENABLE32TO64_REG {
    Uint32  all;
    struct  OUT1MUXENABLE32TO64_BITS  bit;
};

struct OUT2MUXENABLE_BITS {             // bits description
    Uint16 MUX0:1;                      // 0 MUX0 to drive OUT2 of EPWM-XBAR
    Uint16 MUX1:1;                      // 1 MUX1 to drive OUT2 of EPWM-XBAR
    Uint16 MUX2:1;                      // 2 MUX2 to drive OUT2 of EPWM-XBAR
    Uint16 MUX3:1;                      // 3 MUX3 to drive OUT2 of EPWM-XBAR
    Uint16 MUX4:1;                      // 4 MUX4 to drive OUT2 of EPWM-XBAR
    Uint16 MUX5:1;                      // 5 MUX5 to drive OUT2 of EPWM-XBAR
    Uint16 MUX6:1;                      // 6 MUX6 to drive OUT2 of EPWM-XBAR
    Uint16 MUX7:1;                      // 7 MUX7 to drive OUT2 of EPWM-XBAR
    Uint16 MUX8:1;                      // 8 MUX8 to drive OUT2 of EPWM-XBAR
    Uint16 MUX9:1;                      // 9 MUX9 to drive OUT2 of EPWM-XBAR
    Uint16 MUX10:1;                     // 10 MUX10 to drive OUT2 of EPWM-XBAR
    Uint16 MUX11:1;                     // 11 MUX11 to drive OUT2 of EPWM-XBAR
    Uint16 MUX12:1;                     // 12 MUX12 to drive OUT2 of EPWM-XBAR
    Uint16 MUX13:1;                     // 13 MUX13 to drive OUT2 of EPWM-XBAR
    Uint16 MUX14:1;                     // 14 MUX14 to drive OUT2 of EPWM-XBAR
    Uint16 MUX15:1;                     // 15 MUX15 to drive OUT2 of EPWM-XBAR
    Uint16 MUX16:1;                     // 16 MUX16 to drive OUT2 of EPWM-XBAR
    Uint16 MUX17:1;                     // 17 MUX17 to drive OUT2 of EPWM-XBAR
    Uint16 MUX18:1;                     // 18 MUX18 to drive OUT2 of EPWM-XBAR
    Uint16 MUX19:1;                     // 19 MUX19 to drive OUT2 of EPWM-XBAR
    Uint16 MUX20:1;                     // 20 MUX20 to drive OUT2 of EPWM-XBAR
    Uint16 MUX21:1;                     // 21 MUX21 to drive OUT2 of EPWM-XBAR
    Uint16 MUX22:1;                     // 22 MUX22 to drive OUT2 of EPWM-XBAR
    Uint16 MUX23:1;                     // 23 MUX23 to drive OUT2 of EPWM-XBAR
    Uint16 MUX24:1;                     // 24 MUX24 to drive OUT2 of EPWM-XBAR
    Uint16 MUX25:1;                     // 25 MUX25 to drive OUT2 of EPWM-XBAR
    Uint16 MUX26:1;                     // 26 MUX26 to drive OUT2 of EPWM-XBAR
    Uint16 MUX27:1;                     // 27 MUX27 to drive OUT2 of EPWM-XBAR
    Uint16 MUX28:1;                     // 28 MUX28 to drive OUT2 of EPWM-XBAR
    Uint16 MUX29:1;                     // 29 MUX29 to drive OUT2 of EPWM-XBAR
    Uint16 MUX30:1;                     // 30 MUX30 to drive OUT2 of EPWM-XBAR
    Uint16 MUX31:1;                     // 31 MUX31 to drive OUT2 of EPWM-XBAR
};

union OUT2MUXENABLE_REG {
    Uint32  all;
    struct  OUT2MUXENABLE_BITS  bit;
};

struct OUT2MUXENABLE32TO64_BITS {       // bits description
    Uint16 MUX32:1;                     // 0 MUX32 to drive OUT2 of EPWM-XBAR
    Uint16 MUX33:1;                     // 1 MUX33 to drive OUT2 of EPWM-XBAR
    Uint16 MUX34:1;                     // 2 MUX34 to drive OUT2 of EPWM-XBAR
    Uint16 MUX35:1;                     // 3 MUX35 to drive OUT2 of EPWM-XBAR
    Uint16 MUX36:1;                     // 4 MUX36 to drive OUT2 of EPWM-XBAR
    Uint16 MUX37:1;                     // 5 MUX37 to drive OUT2 of EPWM-XBAR
    Uint16 MUX38:1;                     // 6 MUX38 to drive OUT2 of EPWM-XBAR
    Uint16 MUX39:1;                     // 7 MUX39 to drive OUT2 of EPWM-XBAR
    Uint16 MUX40:1;                     // 8 MUX40 to drive OUT2 of EPWM-XBAR
    Uint16 MUX41:1;                     // 9 MUX41 to drive OUT2 of EPWM-XBAR
    Uint16 MUX42:1;                     // 10 MUX42 to drive OUT2 of EPWM-XBAR
    Uint16 MUX43:1;                     // 11 MUX43 to drive OUT2 of EPWM-XBAR
    Uint16 MUX44:1;                     // 12 MUX44 to drive OUT2 of EPWM-XBAR
    Uint16 MUX45:1;                     // 13 MUX45 to drive OUT2 of EPWM-XBAR
    Uint16 MUX46:1;                     // 14 MUX46 to drive OUT2 of EPWM-XBAR
    Uint16 MUX47:1;                     // 15 MUX47 to drive OUT2 of EPWM-XBAR
    Uint16 MUX48:1;                     // 16 MUX48 to drive OUT2 of EPWM-XBAR
    Uint16 MUX49:1;                     // 17 MUX49 to drive OUT2 of EPWM-XBAR
    Uint16 MUX50:1;                     // 18 MUX50 to drive OUT2 of EPWM-XBAR
    Uint16 MUX51:1;                     // 19 MUX51 to drive OUT2 of EPWM-XBAR
    Uint16 MUX52:1;                     // 20 MUX52 to drive OUT2 of EPWM-XBAR
    Uint16 MUX53:1;                     // 21 MUX53 to drive OUT2 of EPWM-XBAR
    Uint16 MUX54:1;                     // 22 MUX54 to drive OUT2 of EPWM-XBAR
    Uint16 MUX55:1;                     // 23 MUX55 to drive OUT2 of EPWM-XBAR
    Uint16 MUX56:1;                     // 24 MUX56 to drive OUT2 of EPWM-XBAR
    Uint16 MUX57:1;                     // 25 MUX57 to drive OUT2 of EPWM-XBAR
    Uint16 MUX58:1;                     // 26 MUX58 to drive OUT2 of EPWM-XBAR
    Uint16 MUX59:1;                     // 27 MUX59 to drive OUT2 of EPWM-XBAR
    Uint16 MUX60:1;                     // 28 MUX60 to drive OUT2 of EPWM-XBAR
    Uint16 MUX61:1;                     // 29 MUX61 to drive OUT2 of EPWM-XBAR
    Uint16 MUX62:1;                     // 30 MUX62 to drive OUT2 of EPWM-XBAR
    Uint16 MUX63:1;                     // 31 MUX63 to drive OUT2 of EPWM-XBAR
};

union OUT2MUXENABLE32TO64_REG {
    Uint32  all;
    struct  OUT2MUXENABLE32TO64_BITS  bit;
};

struct OUT3MUXENABLE_BITS {             // bits description
    Uint16 MUX0:1;                      // 0 MUX0 to drive OUT3 of EPWM-XBAR
    Uint16 MUX1:1;                      // 1 MUX1 to drive OUT3 of EPWM-XBAR
    Uint16 MUX2:1;                      // 2 MUX2 to drive OUT3 of EPWM-XBAR
    Uint16 MUX3:1;                      // 3 MUX3 to drive OUT3 of EPWM-XBAR
    Uint16 MUX4:1;                      // 4 MUX4 to drive OUT3 of EPWM-XBAR
    Uint16 MUX5:1;                      // 5 MUX5 to drive OUT3 of EPWM-XBAR
    Uint16 MUX6:1;                      // 6 MUX6 to drive OUT3 of EPWM-XBAR
    Uint16 MUX7:1;                      // 7 MUX7 to drive OUT3 of EPWM-XBAR
    Uint16 MUX8:1;                      // 8 MUX8 to drive OUT3 of EPWM-XBAR
    Uint16 MUX9:1;                      // 9 MUX9 to drive OUT3 of EPWM-XBAR
    Uint16 MUX10:1;                     // 10 MUX10 to drive OUT3 of EPWM-XBAR
    Uint16 MUX11:1;                     // 11 MUX11 to drive OUT3 of EPWM-XBAR
    Uint16 MUX12:1;                     // 12 MUX12 to drive OUT3 of EPWM-XBAR
    Uint16 MUX13:1;                     // 13 MUX13 to drive OUT3 of EPWM-XBAR
    Uint16 MUX14:1;                     // 14 MUX14 to drive OUT3 of EPWM-XBAR
    Uint16 MUX15:1;                     // 15 MUX15 to drive OUT3 of EPWM-XBAR
    Uint16 MUX16:1;                     // 16 MUX16 to drive OUT3 of EPWM-XBAR
    Uint16 MUX17:1;                     // 17 MUX17 to drive OUT3 of EPWM-XBAR
    Uint16 MUX18:1;                     // 18 MUX18 to drive OUT3 of EPWM-XBAR
    Uint16 MUX19:1;                     // 19 MUX19 to drive OUT3 of EPWM-XBAR
    Uint16 MUX20:1;                     // 20 MUX20 to drive OUT3 of EPWM-XBAR
    Uint16 MUX21:1;                     // 21 MUX21 to drive OUT3 of EPWM-XBAR
    Uint16 MUX22:1;                     // 22 MUX22 to drive OUT3 of EPWM-XBAR
    Uint16 MUX23:1;                     // 23 MUX23 to drive OUT3 of EPWM-XBAR
    Uint16 MUX24:1;                     // 24 MUX24 to drive OUT3 of EPWM-XBAR
    Uint16 MUX25:1;                     // 25 MUX25 to drive OUT3 of EPWM-XBAR
    Uint16 MUX26:1;                     // 26 MUX26 to drive OUT3 of EPWM-XBAR
    Uint16 MUX27:1;                     // 27 MUX27 to drive OUT3 of EPWM-XBAR
    Uint16 MUX28:1;                     // 28 MUX28 to drive OUT3 of EPWM-XBAR
    Uint16 MUX29:1;                     // 29 MUX29 to drive OUT3 of EPWM-XBAR
    Uint16 MUX30:1;                     // 30 MUX30 to drive OUT3 of EPWM-XBAR
    Uint16 MUX31:1;                     // 31 MUX31 to drive OUT3 of EPWM-XBAR
};

union OUT3MUXENABLE_REG {
    Uint32  all;
    struct  OUT3MUXENABLE_BITS  bit;
};

struct OUT3MUXENABLE32TO64_BITS {       // bits description
    Uint16 MUX32:1;                     // 0 MUX32 to drive OUT3 of EPWM-XBAR
    Uint16 MUX33:1;                     // 1 MUX33 to drive OUT3 of EPWM-XBAR
    Uint16 MUX34:1;                     // 2 MUX34 to drive OUT3 of EPWM-XBAR
    Uint16 MUX35:1;                     // 3 MUX35 to drive OUT3 of EPWM-XBAR
    Uint16 MUX36:1;                     // 4 MUX36 to drive OUT3 of EPWM-XBAR
    Uint16 MUX37:1;                     // 5 MUX37 to drive OUT3 of EPWM-XBAR
    Uint16 MUX38:1;                     // 6 MUX38 to drive OUT3 of EPWM-XBAR
    Uint16 MUX39:1;                     // 7 MUX39 to drive OUT3 of EPWM-XBAR
    Uint16 MUX40:1;                     // 8 MUX40 to drive OUT3 of EPWM-XBAR
    Uint16 MUX41:1;                     // 9 MUX41 to drive OUT3 of EPWM-XBAR
    Uint16 MUX42:1;                     // 10 MUX42 to drive OUT3 of EPWM-XBAR
    Uint16 MUX43:1;                     // 11 MUX43 to drive OUT3 of EPWM-XBAR
    Uint16 MUX44:1;                     // 12 MUX44 to drive OUT3 of EPWM-XBAR
    Uint16 MUX45:1;                     // 13 MUX45 to drive OUT3 of EPWM-XBAR
    Uint16 MUX46:1;                     // 14 MUX46 to drive OUT3 of EPWM-XBAR
    Uint16 MUX47:1;                     // 15 MUX47 to drive OUT3 of EPWM-XBAR
    Uint16 MUX48:1;                     // 16 MUX48 to drive OUT3 of EPWM-XBAR
    Uint16 MUX49:1;                     // 17 MUX49 to drive OUT3 of EPWM-XBAR
    Uint16 MUX50:1;                     // 18 MUX50 to drive OUT3 of EPWM-XBAR
    Uint16 MUX51:1;                     // 19 MUX51 to drive OUT3 of EPWM-XBAR
    Uint16 MUX52:1;                     // 20 MUX52 to drive OUT3 of EPWM-XBAR
    Uint16 MUX53:1;                     // 21 MUX53 to drive OUT3 of EPWM-XBAR
    Uint16 MUX54:1;                     // 22 MUX54 to drive OUT3 of EPWM-XBAR
    Uint16 MUX55:1;                     // 23 MUX55 to drive OUT3 of EPWM-XBAR
    Uint16 MUX56:1;                     // 24 MUX56 to drive OUT3 of EPWM-XBAR
    Uint16 MUX57:1;                     // 25 MUX57 to drive OUT3 of EPWM-XBAR
    Uint16 MUX58:1;                     // 26 MUX58 to drive OUT3 of EPWM-XBAR
    Uint16 MUX59:1;                     // 27 MUX59 to drive OUT3 of EPWM-XBAR
    Uint16 MUX60:1;                     // 28 MUX60 to drive OUT3 of EPWM-XBAR
    Uint16 MUX61:1;                     // 29 MUX61 to drive OUT3 of EPWM-XBAR
    Uint16 MUX62:1;                     // 30 MUX62 to drive OUT3 of EPWM-XBAR
    Uint16 MUX63:1;                     // 31 MUX63 to drive OUT3 of EPWM-XBAR
};

union OUT3MUXENABLE32TO64_REG {
    Uint32  all;
    struct  OUT3MUXENABLE32TO64_BITS  bit;
};

struct OUT4MUXENABLE_BITS {             // bits description
    Uint16 MUX0:1;                      // 0 MUX0 to drive OUT4 of EPWM-XBAR
    Uint16 MUX1:1;                      // 1 MUX1 to drive OUT4 of EPWM-XBAR
    Uint16 MUX2:1;                      // 2 MUX2 to drive OUT4 of EPWM-XBAR
    Uint16 MUX3:1;                      // 3 MUX3 to drive OUT4 of EPWM-XBAR
    Uint16 MUX4:1;                      // 4 MUX4 to drive OUT4 of EPWM-XBAR
    Uint16 MUX5:1;                      // 5 MUX5 to drive OUT4 of EPWM-XBAR
    Uint16 MUX6:1;                      // 6 MUX6 to drive OUT4 of EPWM-XBAR
    Uint16 MUX7:1;                      // 7 MUX7 to drive OUT4 of EPWM-XBAR
    Uint16 MUX8:1;                      // 8 MUX8 to drive OUT4 of EPWM-XBAR
    Uint16 MUX9:1;                      // 9 MUX9 to drive OUT4 of EPWM-XBAR
    Uint16 MUX10:1;                     // 10 MUX10 to drive OUT4 of EPWM-XBAR
    Uint16 MUX11:1;                     // 11 MUX11 to drive OUT4 of EPWM-XBAR
    Uint16 MUX12:1;                     // 12 MUX12 to drive OUT4 of EPWM-XBAR
    Uint16 MUX13:1;                     // 13 MUX13 to drive OUT4 of EPWM-XBAR
    Uint16 MUX14:1;                     // 14 MUX14 to drive OUT4 of EPWM-XBAR
    Uint16 MUX15:1;                     // 15 MUX15 to drive OUT4 of EPWM-XBAR
    Uint16 MUX16:1;                     // 16 MUX16 to drive OUT4 of EPWM-XBAR
    Uint16 MUX17:1;                     // 17 MUX17 to drive OUT4 of EPWM-XBAR
    Uint16 MUX18:1;                     // 18 MUX18 to drive OUT4 of EPWM-XBAR
    Uint16 MUX19:1;                     // 19 MUX19 to drive OUT4 of EPWM-XBAR
    Uint16 MUX20:1;                     // 20 MUX20 to drive OUT4 of EPWM-XBAR
    Uint16 MUX21:1;                     // 21 MUX21 to drive OUT4 of EPWM-XBAR
    Uint16 MUX22:1;                     // 22 MUX22 to drive OUT4 of EPWM-XBAR
    Uint16 MUX23:1;                     // 23 MUX23 to drive OUT4 of EPWM-XBAR
    Uint16 MUX24:1;                     // 24 MUX24 to drive OUT4 of EPWM-XBAR
    Uint16 MUX25:1;                     // 25 MUX25 to drive OUT4 of EPWM-XBAR
    Uint16 MUX26:1;                     // 26 MUX26 to drive OUT4 of EPWM-XBAR
    Uint16 MUX27:1;                     // 27 MUX27 to drive OUT4 of EPWM-XBAR
    Uint16 MUX28:1;                     // 28 MUX28 to drive OUT4 of EPWM-XBAR
    Uint16 MUX29:1;                     // 29 MUX29 to drive OUT4 of EPWM-XBAR
    Uint16 MUX30:1;                     // 30 MUX30 to drive OUT4 of EPWM-XBAR
    Uint16 MUX31:1;                     // 31 MUX31 to drive OUT4 of EPWM-XBAR
};

union OUT4MUXENABLE_REG {
    Uint32  all;
    struct  OUT4MUXENABLE_BITS  bit;
};

struct OUT4MUXENABLE32TO64_BITS {       // bits description
    Uint16 MUX32:1;                     // 0 MUX32 to drive OUT4 of EPWM-XBAR
    Uint16 MUX33:1;                     // 1 MUX33 to drive OUT4 of EPWM-XBAR
    Uint16 MUX34:1;                     // 2 MUX34 to drive OUT4 of EPWM-XBAR
    Uint16 MUX35:1;                     // 3 MUX35 to drive OUT4 of EPWM-XBAR
    Uint16 MUX36:1;                     // 4 MUX36 to drive OUT4 of EPWM-XBAR
    Uint16 MUX37:1;                     // 5 MUX37 to drive OUT4 of EPWM-XBAR
    Uint16 MUX38:1;                     // 6 MUX38 to drive OUT4 of EPWM-XBAR
    Uint16 MUX39:1;                     // 7 MUX39 to drive OUT4 of EPWM-XBAR
    Uint16 MUX40:1;                     // 8 MUX40 to drive OUT4 of EPWM-XBAR
    Uint16 MUX41:1;                     // 9 MUX41 to drive OUT4 of EPWM-XBAR
    Uint16 MUX42:1;                     // 10 MUX42 to drive OUT4 of EPWM-XBAR
    Uint16 MUX43:1;                     // 11 MUX43 to drive OUT4 of EPWM-XBAR
    Uint16 MUX44:1;                     // 12 MUX44 to drive OUT4 of EPWM-XBAR
    Uint16 MUX45:1;                     // 13 MUX45 to drive OUT4 of EPWM-XBAR
    Uint16 MUX46:1;                     // 14 MUX46 to drive OUT4 of EPWM-XBAR
    Uint16 MUX47:1;                     // 15 MUX47 to drive OUT4 of EPWM-XBAR
    Uint16 MUX48:1;                     // 16 MUX48 to drive OUT4 of EPWM-XBAR
    Uint16 MUX49:1;                     // 17 MUX49 to drive OUT4 of EPWM-XBAR
    Uint16 MUX50:1;                     // 18 MUX50 to drive OUT4 of EPWM-XBAR
    Uint16 MUX51:1;                     // 19 MUX51 to drive OUT4 of EPWM-XBAR
    Uint16 MUX52:1;                     // 20 MUX52 to drive OUT4 of EPWM-XBAR
    Uint16 MUX53:1;                     // 21 MUX53 to drive OUT4 of EPWM-XBAR
    Uint16 MUX54:1;                     // 22 MUX54 to drive OUT4 of EPWM-XBAR
    Uint16 MUX55:1;                     // 23 MUX55 to drive OUT4 of EPWM-XBAR
    Uint16 MUX56:1;                     // 24 MUX56 to drive OUT4 of EPWM-XBAR
    Uint16 MUX57:1;                     // 25 MUX57 to drive OUT4 of EPWM-XBAR
    Uint16 MUX58:1;                     // 26 MUX58 to drive OUT4 of EPWM-XBAR
    Uint16 MUX59:1;                     // 27 MUX59 to drive OUT4 of EPWM-XBAR
    Uint16 MUX60:1;                     // 28 MUX60 to drive OUT4 of EPWM-XBAR
    Uint16 MUX61:1;                     // 29 MUX61 to drive OUT4 of EPWM-XBAR
    Uint16 MUX62:1;                     // 30 MUX62 to drive OUT4 of EPWM-XBAR
    Uint16 MUX63:1;                     // 31 MUX63 to drive OUT4 of EPWM-XBAR
};

union OUT4MUXENABLE32TO64_REG {
    Uint32  all;
    struct  OUT4MUXENABLE32TO64_BITS  bit;
};

struct OUT5MUXENABLE_BITS {             // bits description
    Uint16 MUX0:1;                      // 0 MUX0 to drive OUT5 of EPWM-XBAR
    Uint16 MUX1:1;                      // 1 MUX1 to drive OUT5 of EPWM-XBAR
    Uint16 MUX2:1;                      // 2 MUX2 to drive OUT5 of EPWM-XBAR
    Uint16 MUX3:1;                      // 3 MUX3 to drive OUT5 of EPWM-XBAR
    Uint16 MUX4:1;                      // 4 MUX4 to drive OUT5 of EPWM-XBAR
    Uint16 MUX5:1;                      // 5 MUX5 to drive OUT5 of EPWM-XBAR
    Uint16 MUX6:1;                      // 6 MUX6 to drive OUT5 of EPWM-XBAR
    Uint16 MUX7:1;                      // 7 MUX7 to drive OUT5 of EPWM-XBAR
    Uint16 MUX8:1;                      // 8 MUX8 to drive OUT5 of EPWM-XBAR
    Uint16 MUX9:1;                      // 9 MUX9 to drive OUT5 of EPWM-XBAR
    Uint16 MUX10:1;                     // 10 MUX10 to drive OUT5 of EPWM-XBAR
    Uint16 MUX11:1;                     // 11 MUX11 to drive OUT5 of EPWM-XBAR
    Uint16 MUX12:1;                     // 12 MUX12 to drive OUT5 of EPWM-XBAR
    Uint16 MUX13:1;                     // 13 MUX13 to drive OUT5 of EPWM-XBAR
    Uint16 MUX14:1;                     // 14 MUX14 to drive OUT5 of EPWM-XBAR
    Uint16 MUX15:1;                     // 15 MUX15 to drive OUT5 of EPWM-XBAR
    Uint16 MUX16:1;                     // 16 MUX16 to drive OUT5 of EPWM-XBAR
    Uint16 MUX17:1;                     // 17 MUX17 to drive OUT5 of EPWM-XBAR
    Uint16 MUX18:1;                     // 18 MUX18 to drive OUT5 of EPWM-XBAR
    Uint16 MUX19:1;                     // 19 MUX19 to drive OUT5 of EPWM-XBAR
    Uint16 MUX20:1;                     // 20 MUX20 to drive OUT5 of EPWM-XBAR
    Uint16 MUX21:1;                     // 21 MUX21 to drive OUT5 of EPWM-XBAR
    Uint16 MUX22:1;                     // 22 MUX22 to drive OUT5 of EPWM-XBAR
    Uint16 MUX23:1;                     // 23 MUX23 to drive OUT5 of EPWM-XBAR
    Uint16 MUX24:1;                     // 24 MUX24 to drive OUT5 of EPWM-XBAR
    Uint16 MUX25:1;                     // 25 MUX25 to drive OUT5 of EPWM-XBAR
    Uint16 MUX26:1;                     // 26 MUX26 to drive OUT5 of EPWM-XBAR
    Uint16 MUX27:1;                     // 27 MUX27 to drive OUT5 of EPWM-XBAR
    Uint16 MUX28:1;                     // 28 MUX28 to drive OUT5 of EPWM-XBAR
    Uint16 MUX29:1;                     // 29 MUX29 to drive OUT5 of EPWM-XBAR
    Uint16 MUX30:1;                     // 30 MUX30 to drive OUT5 of EPWM-XBAR
    Uint16 MUX31:1;                     // 31 MUX31 to drive OUT5 of EPWM-XBAR
};

union OUT5MUXENABLE_REG {
    Uint32  all;
    struct  OUT5MUXENABLE_BITS  bit;
};

struct OUT5MUXENABLE32TO64_BITS {       // bits description
    Uint16 MUX32:1;                     // 0 MUX32 to drive OUT5 of EPWM-XBAR
    Uint16 MUX33:1;                     // 1 MUX33 to drive OUT5 of EPWM-XBAR
    Uint16 MUX34:1;                     // 2 MUX34 to drive OUT5 of EPWM-XBAR
    Uint16 MUX35:1;                     // 3 MUX35 to drive OUT5 of EPWM-XBAR
    Uint16 MUX36:1;                     // 4 MUX36 to drive OUT5 of EPWM-XBAR
    Uint16 MUX37:1;                     // 5 MUX37 to drive OUT5 of EPWM-XBAR
    Uint16 MUX38:1;                     // 6 MUX38 to drive OUT5 of EPWM-XBAR
    Uint16 MUX39:1;                     // 7 MUX39 to drive OUT5 of EPWM-XBAR
    Uint16 MUX40:1;                     // 8 MUX40 to drive OUT5 of EPWM-XBAR
    Uint16 MUX41:1;                     // 9 MUX41 to drive OUT5 of EPWM-XBAR
    Uint16 MUX42:1;                     // 10 MUX42 to drive OUT5 of EPWM-XBAR
    Uint16 MUX43:1;                     // 11 MUX43 to drive OUT5 of EPWM-XBAR
    Uint16 MUX44:1;                     // 12 MUX44 to drive OUT5 of EPWM-XBAR
    Uint16 MUX45:1;                     // 13 MUX45 to drive OUT5 of EPWM-XBAR
    Uint16 MUX46:1;                     // 14 MUX46 to drive OUT5 of EPWM-XBAR
    Uint16 MUX47:1;                     // 15 MUX47 to drive OUT5 of EPWM-XBAR
    Uint16 MUX48:1;                     // 16 MUX48 to drive OUT5 of EPWM-XBAR
    Uint16 MUX49:1;                     // 17 MUX49 to drive OUT5 of EPWM-XBAR
    Uint16 MUX50:1;                     // 18 MUX50 to drive OUT5 of EPWM-XBAR
    Uint16 MUX51:1;                     // 19 MUX51 to drive OUT5 of EPWM-XBAR
    Uint16 MUX52:1;                     // 20 MUX52 to drive OUT5 of EPWM-XBAR
    Uint16 MUX53:1;                     // 21 MUX53 to drive OUT5 of EPWM-XBAR
    Uint16 MUX54:1;                     // 22 MUX54 to drive OUT5 of EPWM-XBAR
    Uint16 MUX55:1;                     // 23 MUX55 to drive OUT5 of EPWM-XBAR
    Uint16 MUX56:1;                     // 24 MUX56 to drive OUT5 of EPWM-XBAR
    Uint16 MUX57:1;                     // 25 MUX57 to drive OUT5 of EPWM-XBAR
    Uint16 MUX58:1;                     // 26 MUX58 to drive OUT5 of EPWM-XBAR
    Uint16 MUX59:1;                     // 27 MUX59 to drive OUT5 of EPWM-XBAR
    Uint16 MUX60:1;                     // 28 MUX60 to drive OUT5 of EPWM-XBAR
    Uint16 MUX61:1;                     // 29 MUX61 to drive OUT5 of EPWM-XBAR
    Uint16 MUX62:1;                     // 30 MUX62 to drive OUT5 of EPWM-XBAR
    Uint16 MUX63:1;                     // 31 MUX63 to drive OUT5 of EPWM-XBAR
};

union OUT5MUXENABLE32TO64_REG {
    Uint32  all;
    struct  OUT5MUXENABLE32TO64_BITS  bit;
};

struct OUT6MUXENABLE_BITS {             // bits description
    Uint16 MUX0:1;                      // 0 MUX0 to drive OUT6 of EPWM-XBAR
    Uint16 MUX1:1;                      // 1 MUX1 to drive OUT6 of EPWM-XBAR
    Uint16 MUX2:1;                      // 2 MUX2 to drive OUT6 of EPWM-XBAR
    Uint16 MUX3:1;                      // 3 MUX3 to drive OUT6 of EPWM-XBAR
    Uint16 MUX4:1;                      // 4 MUX4 to drive OUT6 of EPWM-XBAR
    Uint16 MUX5:1;                      // 5 MUX5 to drive OUT6 of EPWM-XBAR
    Uint16 MUX6:1;                      // 6 MUX6 to drive OUT6 of EPWM-XBAR
    Uint16 MUX7:1;                      // 7 MUX7 to drive OUT6 of EPWM-XBAR
    Uint16 MUX8:1;                      // 8 MUX8 to drive OUT6 of EPWM-XBAR
    Uint16 MUX9:1;                      // 9 MUX9 to drive OUT6 of EPWM-XBAR
    Uint16 MUX10:1;                     // 10 MUX10 to drive OUT6 of EPWM-XBAR
    Uint16 MUX11:1;                     // 11 MUX11 to drive OUT6 of EPWM-XBAR
    Uint16 MUX12:1;                     // 12 MUX12 to drive OUT6 of EPWM-XBAR
    Uint16 MUX13:1;                     // 13 MUX13 to drive OUT6 of EPWM-XBAR
    Uint16 MUX14:1;                     // 14 MUX14 to drive OUT6 of EPWM-XBAR
    Uint16 MUX15:1;                     // 15 MUX15 to drive OUT6 of EPWM-XBAR
    Uint16 MUX16:1;                     // 16 MUX16 to drive OUT6 of EPWM-XBAR
    Uint16 MUX17:1;                     // 17 MUX17 to drive OUT6 of EPWM-XBAR
    Uint16 MUX18:1;                     // 18 MUX18 to drive OUT6 of EPWM-XBAR
    Uint16 MUX19:1;                     // 19 MUX19 to drive OUT6 of EPWM-XBAR
    Uint16 MUX20:1;                     // 20 MUX20 to drive OUT6 of EPWM-XBAR
    Uint16 MUX21:1;                     // 21 MUX21 to drive OUT6 of EPWM-XBAR
    Uint16 MUX22:1;                     // 22 MUX22 to drive OUT6 of EPWM-XBAR
    Uint16 MUX23:1;                     // 23 MUX23 to drive OUT6 of EPWM-XBAR
    Uint16 MUX24:1;                     // 24 MUX24 to drive OUT6 of EPWM-XBAR
    Uint16 MUX25:1;                     // 25 MUX25 to drive OUT6 of EPWM-XBAR
    Uint16 MUX26:1;                     // 26 MUX26 to drive OUT6 of EPWM-XBAR
    Uint16 MUX27:1;                     // 27 MUX27 to drive OUT6 of EPWM-XBAR
    Uint16 MUX28:1;                     // 28 MUX28 to drive OUT6 of EPWM-XBAR
    Uint16 MUX29:1;                     // 29 MUX29 to drive OUT6 of EPWM-XBAR
    Uint16 MUX30:1;                     // 30 MUX30 to drive OUT6 of EPWM-XBAR
    Uint16 MUX31:1;                     // 31 MUX31 to drive OUT6 of EPWM-XBAR
};

union OUT6MUXENABLE_REG {
    Uint32  all;
    struct  OUT6MUXENABLE_BITS  bit;
};

struct OUT6MUXENABLE32TO64_BITS {       // bits description
    Uint16 MUX32:1;                     // 0 MUX32 to drive OUT6 of EPWM-XBAR
    Uint16 MUX33:1;                     // 1 MUX33 to drive OUT6 of EPWM-XBAR
    Uint16 MUX34:1;                     // 2 MUX34 to drive OUT6 of EPWM-XBAR
    Uint16 MUX35:1;                     // 3 MUX35 to drive OUT6 of EPWM-XBAR
    Uint16 MUX36:1;                     // 4 MUX36 to drive OUT6 of EPWM-XBAR
    Uint16 MUX37:1;                     // 5 MUX37 to drive OUT6 of EPWM-XBAR
    Uint16 MUX38:1;                     // 6 MUX38 to drive OUT6 of EPWM-XBAR
    Uint16 MUX39:1;                     // 7 MUX39 to drive OUT6 of EPWM-XBAR
    Uint16 MUX40:1;                     // 8 MUX40 to drive OUT6 of EPWM-XBAR
    Uint16 MUX41:1;                     // 9 MUX41 to drive OUT6 of EPWM-XBAR
    Uint16 MUX42:1;                     // 10 MUX42 to drive OUT6 of EPWM-XBAR
    Uint16 MUX43:1;                     // 11 MUX43 to drive OUT6 of EPWM-XBAR
    Uint16 MUX44:1;                     // 12 MUX44 to drive OUT6 of EPWM-XBAR
    Uint16 MUX45:1;                     // 13 MUX45 to drive OUT6 of EPWM-XBAR
    Uint16 MUX46:1;                     // 14 MUX46 to drive OUT6 of EPWM-XBAR
    Uint16 MUX47:1;                     // 15 MUX47 to drive OUT6 of EPWM-XBAR
    Uint16 MUX48:1;                     // 16 MUX48 to drive OUT6 of EPWM-XBAR
    Uint16 MUX49:1;                     // 17 MUX49 to drive OUT6 of EPWM-XBAR
    Uint16 MUX50:1;                     // 18 MUX50 to drive OUT6 of EPWM-XBAR
    Uint16 MUX51:1;                     // 19 MUX51 to drive OUT6 of EPWM-XBAR
    Uint16 MUX52:1;                     // 20 MUX52 to drive OUT6 of EPWM-XBAR
    Uint16 MUX53:1;                     // 21 MUX53 to drive OUT6 of EPWM-XBAR
    Uint16 MUX54:1;                     // 22 MUX54 to drive OUT6 of EPWM-XBAR
    Uint16 MUX55:1;                     // 23 MUX55 to drive OUT6 of EPWM-XBAR
    Uint16 MUX56:1;                     // 24 MUX56 to drive OUT6 of EPWM-XBAR
    Uint16 MUX57:1;                     // 25 MUX57 to drive OUT6 of EPWM-XBAR
    Uint16 MUX58:1;                     // 26 MUX58 to drive OUT6 of EPWM-XBAR
    Uint16 MUX59:1;                     // 27 MUX59 to drive OUT6 of EPWM-XBAR
    Uint16 MUX60:1;                     // 28 MUX60 to drive OUT6 of EPWM-XBAR
    Uint16 MUX61:1;                     // 29 MUX61 to drive OUT6 of EPWM-XBAR
    Uint16 MUX62:1;                     // 30 MUX62 to drive OUT6 of EPWM-XBAR
    Uint16 MUX63:1;                     // 31 MUX63 to drive OUT6 of EPWM-XBAR
};

union OUT6MUXENABLE32TO64_REG {
    Uint32  all;
    struct  OUT6MUXENABLE32TO64_BITS  bit;
};

struct OUT7MUXENABLE_BITS {             // bits description
    Uint16 MUX0:1;                      // 0 MUX0 to drive OUT7 of EPWM-XBAR
    Uint16 MUX1:1;                      // 1 MUX1 to drive OUT7 of EPWM-XBAR
    Uint16 MUX2:1;                      // 2 MUX2 to drive OUT7 of EPWM-XBAR
    Uint16 MUX3:1;                      // 3 MUX3 to drive OUT7 of EPWM-XBAR
    Uint16 MUX4:1;                      // 4 MUX4 to drive OUT7 of EPWM-XBAR
    Uint16 MUX5:1;                      // 5 MUX5 to drive OUT7 of EPWM-XBAR
    Uint16 MUX6:1;                      // 6 MUX6 to drive OUT7 of EPWM-XBAR
    Uint16 MUX7:1;                      // 7 MUX7 to drive OUT7 of EPWM-XBAR
    Uint16 MUX8:1;                      // 8 MUX8 to drive OUT7 of EPWM-XBAR
    Uint16 MUX9:1;                      // 9 MUX9 to drive OUT7 of EPWM-XBAR
    Uint16 MUX10:1;                     // 10 MUX10 to drive OUT7 of EPWM-XBAR
    Uint16 MUX11:1;                     // 11 MUX11 to drive OUT7 of EPWM-XBAR
    Uint16 MUX12:1;                     // 12 MUX12 to drive OUT7 of EPWM-XBAR
    Uint16 MUX13:1;                     // 13 MUX13 to drive OUT7 of EPWM-XBAR
    Uint16 MUX14:1;                     // 14 MUX14 to drive OUT7 of EPWM-XBAR
    Uint16 MUX15:1;                     // 15 MUX15 to drive OUT7 of EPWM-XBAR
    Uint16 MUX16:1;                     // 16 MUX16 to drive OUT7 of EPWM-XBAR
    Uint16 MUX17:1;                     // 17 MUX17 to drive OUT7 of EPWM-XBAR
    Uint16 MUX18:1;                     // 18 MUX18 to drive OUT7 of EPWM-XBAR
    Uint16 MUX19:1;                     // 19 MUX19 to drive OUT7 of EPWM-XBAR
    Uint16 MUX20:1;                     // 20 MUX20 to drive OUT7 of EPWM-XBAR
    Uint16 MUX21:1;                     // 21 MUX21 to drive OUT7 of EPWM-XBAR
    Uint16 MUX22:1;                     // 22 MUX22 to drive OUT7 of EPWM-XBAR
    Uint16 MUX23:1;                     // 23 MUX23 to drive OUT7 of EPWM-XBAR
    Uint16 MUX24:1;                     // 24 MUX24 to drive OUT7 of EPWM-XBAR
    Uint16 MUX25:1;                     // 25 MUX25 to drive OUT7 of EPWM-XBAR
    Uint16 MUX26:1;                     // 26 MUX26 to drive OUT7 of EPWM-XBAR
    Uint16 MUX27:1;                     // 27 MUX27 to drive OUT7 of EPWM-XBAR
    Uint16 MUX28:1;                     // 28 MUX28 to drive OUT7 of EPWM-XBAR
    Uint16 MUX29:1;                     // 29 MUX29 to drive OUT7 of EPWM-XBAR
    Uint16 MUX30:1;                     // 30 MUX30 to drive OUT7 of EPWM-XBAR
    Uint16 MUX31:1;                     // 31 MUX31 to drive OUT7 of EPWM-XBAR
};

union OUT7MUXENABLE_REG {
    Uint32  all;
    struct  OUT7MUXENABLE_BITS  bit;
};

struct OUT7MUXENABLE32TO64_BITS {       // bits description
    Uint16 MUX32:1;                     // 0 MUX32 to drive OUT7 of EPWM-XBAR
    Uint16 MUX33:1;                     // 1 MUX33 to drive OUT7 of EPWM-XBAR
    Uint16 MUX34:1;                     // 2 MUX34 to drive OUT7 of EPWM-XBAR
    Uint16 MUX35:1;                     // 3 MUX35 to drive OUT7 of EPWM-XBAR
    Uint16 MUX36:1;                     // 4 MUX36 to drive OUT7 of EPWM-XBAR
    Uint16 MUX37:1;                     // 5 MUX37 to drive OUT7 of EPWM-XBAR
    Uint16 MUX38:1;                     // 6 MUX38 to drive OUT7 of EPWM-XBAR
    Uint16 MUX39:1;                     // 7 MUX39 to drive OUT7 of EPWM-XBAR
    Uint16 MUX40:1;                     // 8 MUX40 to drive OUT7 of EPWM-XBAR
    Uint16 MUX41:1;                     // 9 MUX41 to drive OUT7 of EPWM-XBAR
    Uint16 MUX42:1;                     // 10 MUX42 to drive OUT7 of EPWM-XBAR
    Uint16 MUX43:1;                     // 11 MUX43 to drive OUT7 of EPWM-XBAR
    Uint16 MUX44:1;                     // 12 MUX44 to drive OUT7 of EPWM-XBAR
    Uint16 MUX45:1;                     // 13 MUX45 to drive OUT7 of EPWM-XBAR
    Uint16 MUX46:1;                     // 14 MUX46 to drive OUT7 of EPWM-XBAR
    Uint16 MUX47:1;                     // 15 MUX47 to drive OUT7 of EPWM-XBAR
    Uint16 MUX48:1;                     // 16 MUX48 to drive OUT7 of EPWM-XBAR
    Uint16 MUX49:1;                     // 17 MUX49 to drive OUT7 of EPWM-XBAR
    Uint16 MUX50:1;                     // 18 MUX50 to drive OUT7 of EPWM-XBAR
    Uint16 MUX51:1;                     // 19 MUX51 to drive OUT7 of EPWM-XBAR
    Uint16 MUX52:1;                     // 20 MUX52 to drive OUT7 of EPWM-XBAR
    Uint16 MUX53:1;                     // 21 MUX53 to drive OUT7 of EPWM-XBAR
    Uint16 MUX54:1;                     // 22 MUX54 to drive OUT7 of EPWM-XBAR
    Uint16 MUX55:1;                     // 23 MUX55 to drive OUT7 of EPWM-XBAR
    Uint16 MUX56:1;                     // 24 MUX56 to drive OUT7 of EPWM-XBAR
    Uint16 MUX57:1;                     // 25 MUX57 to drive OUT7 of EPWM-XBAR
    Uint16 MUX58:1;                     // 26 MUX58 to drive OUT7 of EPWM-XBAR
    Uint16 MUX59:1;                     // 27 MUX59 to drive OUT7 of EPWM-XBAR
    Uint16 MUX60:1;                     // 28 MUX60 to drive OUT7 of EPWM-XBAR
    Uint16 MUX61:1;                     // 29 MUX61 to drive OUT7 of EPWM-XBAR
    Uint16 MUX62:1;                     // 30 MUX62 to drive OUT7 of EPWM-XBAR
    Uint16 MUX63:1;                     // 31 MUX63 to drive OUT7 of EPWM-XBAR
};

union OUT7MUXENABLE32TO64_REG {
    Uint32  all;
    struct  OUT7MUXENABLE32TO64_BITS  bit;
};

struct OUT8MUXENABLE_BITS {             // bits description
    Uint16 MUX0:1;                      // 0 MUX0 to drive OUT8 of EPWM-XBAR
    Uint16 MUX1:1;                      // 1 MUX1 to drive OUT8 of EPWM-XBAR
    Uint16 MUX2:1;                      // 2 MUX2 to drive OUT8 of EPWM-XBAR
    Uint16 MUX3:1;                      // 3 MUX3 to drive OUT8 of EPWM-XBAR
    Uint16 MUX4:1;                      // 4 MUX4 to drive OUT8 of EPWM-XBAR
    Uint16 MUX5:1;                      // 5 MUX5 to drive OUT8 of EPWM-XBAR
    Uint16 MUX6:1;                      // 6 MUX6 to drive OUT8 of EPWM-XBAR
    Uint16 MUX7:1;                      // 7 MUX7 to drive OUT8 of EPWM-XBAR
    Uint16 MUX8:1;                      // 8 MUX8 to drive OUT8 of EPWM-XBAR
    Uint16 MUX9:1;                      // 9 MUX9 to drive OUT8 of EPWM-XBAR
    Uint16 MUX10:1;                     // 10 MUX10 to drive OUT8 of EPWM-XBAR
    Uint16 MUX11:1;                     // 11 MUX11 to drive OUT8 of EPWM-XBAR
    Uint16 MUX12:1;                     // 12 MUX12 to drive OUT8 of EPWM-XBAR
    Uint16 MUX13:1;                     // 13 MUX13 to drive OUT8 of EPWM-XBAR
    Uint16 MUX14:1;                     // 14 MUX14 to drive OUT8 of EPWM-XBAR
    Uint16 MUX15:1;                     // 15 MUX15 to drive OUT8 of EPWM-XBAR
    Uint16 MUX16:1;                     // 16 MUX16 to drive OUT8 of EPWM-XBAR
    Uint16 MUX17:1;                     // 17 MUX17 to drive OUT8 of EPWM-XBAR
    Uint16 MUX18:1;                     // 18 MUX18 to drive OUT8 of EPWM-XBAR
    Uint16 MUX19:1;                     // 19 MUX19 to drive OUT8 of EPWM-XBAR
    Uint16 MUX20:1;                     // 20 MUX20 to drive OUT8 of EPWM-XBAR
    Uint16 MUX21:1;                     // 21 MUX21 to drive OUT8 of EPWM-XBAR
    Uint16 MUX22:1;                     // 22 MUX22 to drive OUT8 of EPWM-XBAR
    Uint16 MUX23:1;                     // 23 MUX23 to drive OUT8 of EPWM-XBAR
    Uint16 MUX24:1;                     // 24 MUX24 to drive OUT8 of EPWM-XBAR
    Uint16 MUX25:1;                     // 25 MUX25 to drive OUT8 of EPWM-XBAR
    Uint16 MUX26:1;                     // 26 MUX26 to drive OUT8 of EPWM-XBAR
    Uint16 MUX27:1;                     // 27 MUX27 to drive OUT8 of EPWM-XBAR
    Uint16 MUX28:1;                     // 28 MUX28 to drive OUT8 of EPWM-XBAR
    Uint16 MUX29:1;                     // 29 MUX29 to drive OUT8 of EPWM-XBAR
    Uint16 MUX30:1;                     // 30 MUX30 to drive OUT8 of EPWM-XBAR
    Uint16 MUX31:1;                     // 31 MUX31 to drive OUT8 of EPWM-XBAR
};

union OUT8MUXENABLE_REG {
    Uint32  all;
    struct  OUT8MUXENABLE_BITS  bit;
};

struct OUT8MUXENABLE32TO64_BITS {       // bits description
    Uint16 MUX32:1;                     // 0 MUX32 to drive OUT8 of EPWM-XBAR
    Uint16 MUX33:1;                     // 1 MUX33 to drive OUT8 of EPWM-XBAR
    Uint16 MUX34:1;                     // 2 MUX34 to drive OUT8 of EPWM-XBAR
    Uint16 MUX35:1;                     // 3 MUX35 to drive OUT8 of EPWM-XBAR
    Uint16 MUX36:1;                     // 4 MUX36 to drive OUT8 of EPWM-XBAR
    Uint16 MUX37:1;                     // 5 MUX37 to drive OUT8 of EPWM-XBAR
    Uint16 MUX38:1;                     // 6 MUX38 to drive OUT8 of EPWM-XBAR
    Uint16 MUX39:1;                     // 7 MUX39 to drive OUT8 of EPWM-XBAR
    Uint16 MUX40:1;                     // 8 MUX40 to drive OUT8 of EPWM-XBAR
    Uint16 MUX41:1;                     // 9 MUX41 to drive OUT8 of EPWM-XBAR
    Uint16 MUX42:1;                     // 10 MUX42 to drive OUT8 of EPWM-XBAR
    Uint16 MUX43:1;                     // 11 MUX43 to drive OUT8 of EPWM-XBAR
    Uint16 MUX44:1;                     // 12 MUX44 to drive OUT8 of EPWM-XBAR
    Uint16 MUX45:1;                     // 13 MUX45 to drive OUT8 of EPWM-XBAR
    Uint16 MUX46:1;                     // 14 MUX46 to drive OUT8 of EPWM-XBAR
    Uint16 MUX47:1;                     // 15 MUX47 to drive OUT8 of EPWM-XBAR
    Uint16 MUX48:1;                     // 16 MUX48 to drive OUT8 of EPWM-XBAR
    Uint16 MUX49:1;                     // 17 MUX49 to drive OUT8 of EPWM-XBAR
    Uint16 MUX50:1;                     // 18 MUX50 to drive OUT8 of EPWM-XBAR
    Uint16 MUX51:1;                     // 19 MUX51 to drive OUT8 of EPWM-XBAR
    Uint16 MUX52:1;                     // 20 MUX52 to drive OUT8 of EPWM-XBAR
    Uint16 MUX53:1;                     // 21 MUX53 to drive OUT8 of EPWM-XBAR
    Uint16 MUX54:1;                     // 22 MUX54 to drive OUT8 of EPWM-XBAR
    Uint16 MUX55:1;                     // 23 MUX55 to drive OUT8 of EPWM-XBAR
    Uint16 MUX56:1;                     // 24 MUX56 to drive OUT8 of EPWM-XBAR
    Uint16 MUX57:1;                     // 25 MUX57 to drive OUT8 of EPWM-XBAR
    Uint16 MUX58:1;                     // 26 MUX58 to drive OUT8 of EPWM-XBAR
    Uint16 MUX59:1;                     // 27 MUX59 to drive OUT8 of EPWM-XBAR
    Uint16 MUX60:1;                     // 28 MUX60 to drive OUT8 of EPWM-XBAR
    Uint16 MUX61:1;                     // 29 MUX61 to drive OUT8 of EPWM-XBAR
    Uint16 MUX62:1;                     // 30 MUX62 to drive OUT8 of EPWM-XBAR
    Uint16 MUX63:1;                     // 31 MUX63 to drive OUT8 of EPWM-XBAR
};

union OUT8MUXENABLE32TO64_REG {
    Uint32  all;
    struct  OUT8MUXENABLE32TO64_BITS  bit;
};

struct TRIPOUTINV_BITS {                // bits description
    Uint16 OUT0:1;                      // 0 Selects polarity for OUT0 of EPWM-XBAR
    Uint16 OUT1:1;                      // 1 Selects polarity for OUT1 of EPWM-XBAR
    Uint16 OUT2:1;                      // 2 Selects polarity for OUT2 of EPWM-XBAR
    Uint16 OUT3:1;                      // 3 Selects polarity for OUT3 of EPWM-XBAR
    Uint16 OUT4:1;                      // 4 Selects polarity for OUT4 of EPWM-XBAR
    Uint16 OUT5:1;                      // 5 Selects polarity for OUT5 of EPWM-XBAR
    Uint16 OUT6:1;                      // 6 Selects polarity for OUT6 of EPWM-XBAR
    Uint16 OUT7:1;                      // 7 Selects polarity for OUT7 of EPWM-XBAR
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union TRIPOUTINV_REG {
    Uint32  all;
    struct  TRIPOUTINV_BITS  bit;
};

struct TRIPLOCK_BITS {                  // bits description
    Uint16 LOCK:1;                      // 0 Locks the configuration for EPWM-XBAR
    Uint16 rsvd1:15;                    // 15:1 Reserved
    Uint16 KEY:16;                      // 31:16 Write protection KEY
};

union TRIPLOCK_REG {
    Uint32  all;
    struct  TRIPLOCK_BITS  bit;
};

struct EPWM_XBAR_REGS {
    union   OUT1MUX0TO15CFG_REG              OUT1MUX0TO15CFG;              // ePWM XBAR Mux Configuration for Output1
    union   OUT1MUX16TO31CFG_REG             OUT1MUX16TO31CFG;             // ePWM XBAR Mux Configuration for Output1
    union   OUT1MUX32TO47CFG_REG             OUT1MUX32TO47CFG;             // ePWM XBAR Mux Configuration for Output1
    union   OUT1MUX48TO63CFG_REG             OUT1MUX48TO63CFG;             // ePWM XBAR Mux Configuration for Output1
    union   OUT2MUX0TO15CFG_REG              OUT2MUX0TO15CFG;              // ePWM XBAR Mux Configuration for Output2
    union   OUT2MUX16TO31CFG_REG             OUT2MUX16TO31CFG;             // ePWM XBAR Mux Configuration for Output2
    union   OUT2MUX32TO47CFG_REG             OUT2MUX32TO47CFG;             // ePWM XBAR Mux Configuration for Output2
    union   OUT2MUX48TO63CFG_REG             OUT2MUX48TO63CFG;             // ePWM XBAR Mux Configuration for Output2
    union   OUT3MUX0TO15CFG_REG              OUT3MUX0TO15CFG;              // ePWM XBAR Mux Configuration for Output3
    union   OUT3MUX16TO31CFG_REG             OUT3MUX16TO31CFG;             // ePWM XBAR Mux Configuration for Output3
    union   OUT3MUX32TO47CFG_REG             OUT3MUX32TO47CFG;             // ePWM XBAR Mux Configuration for Output3
    union   OUT3MUX48TO63CFG_REG             OUT3MUX48TO63CFG;             // ePWM XBAR Mux Configuration for Output3
    union   OUT4MUX0TO15CFG_REG              OUT4MUX0TO15CFG;              // ePWM XBAR Mux Configuration for Output4
    union   OUT4MUX16TO31CFG_REG             OUT4MUX16TO31CFG;             // ePWM XBAR Mux Configuration for Output4
    union   OUT4MUX32TO47CFG_REG             OUT4MUX32TO47CFG;             // ePWM XBAR Mux Configuration for Output4
    union   OUT4MUX48TO63CFG_REG             OUT4MUX48TO63CFG;             // ePWM XBAR Mux Configuration for Output4
    union   OUT5MUX0TO15CFG_REG              OUT5MUX0TO15CFG;              // ePWM XBAR Mux Configuration for Output5
    union   OUT5MUX16TO31CFG_REG             OUT5MUX16TO31CFG;             // ePWM XBAR Mux Configuration for Output5
    union   OUT5MUX32TO47CFG_REG             OUT5MUX32TO47CFG;             // ePWM XBAR Mux Configuration for Output5
    union   OUT5MUX48TO63CFG_REG             OUT5MUX48TO63CFG;             // ePWM XBAR Mux Configuration for Output5
    union   OUT6MUX0TO15CFG_REG              OUT6MUX0TO15CFG;              // ePWM XBAR Mux Configuration for Output6
    union   OUT6MUX16TO31CFG_REG             OUT6MUX16TO31CFG;             // ePWM XBAR Mux Configuration for Output6
    union   OUT6MUX32TO47CFG_REG             OUT6MUX32TO47CFG;             // ePWM XBAR Mux Configuration for Output6
    union   OUT6MUX48TO63CFG_REG             OUT6MUX48TO63CFG;             // ePWM XBAR Mux Configuration for Output6
    union   OUT7MUX0TO15CFG_REG              OUT7MUX0TO15CFG;              // ePWM XBAR Mux Configuration for Output7
    union   OUT7MUX16TO31CFG_REG             OUT7MUX16TO31CFG;             // ePWM XBAR Mux Configuration for Output7
    union   OUT7MUX32TO47CFG_REG             OUT7MUX32TO47CFG;             // ePWM XBAR Mux Configuration for Output7
    union   OUT7MUX48TO63CFG_REG             OUT7MUX48TO63CFG;             // ePWM XBAR Mux Configuration for Output7
    union   OUT8MUX0TO15CFG_REG              OUT8MUX0TO15CFG;              // ePWM XBAR Mux Configuration for Output8
    union   OUT8MUX16TO31CFG_REG             OUT8MUX16TO31CFG;             // ePWM XBAR Mux Configuration for Output8
    union   OUT8MUX32TO47CFG_REG             OUT8MUX32TO47CFG;             // ePWM XBAR Mux Configuration for Output8
    union   OUT8MUX48TO63CFG_REG             OUT8MUX48TO63CFG;             // ePWM XBAR Mux Configuration for Output8
    union   OUT1MUXENABLE_REG                OUT1MUXENABLE;                // ePWM XBAR Mux Enable for Output1
    union   OUT1MUXENABLE32TO64_REG          OUT1MUXENABLE32TO64;          // ePWM XBAR Mux Enable for Output1
    union   OUT2MUXENABLE_REG                OUT2MUXENABLE;                // ePWM XBAR Mux Enable for Output2
    union   OUT2MUXENABLE32TO64_REG          OUT2MUXENABLE32TO64;          // ePWM XBAR Mux Enable for Output2
    union   OUT3MUXENABLE_REG                OUT3MUXENABLE;                // ePWM XBAR Mux Enable for Output3
    union   OUT3MUXENABLE32TO64_REG          OUT3MUXENABLE32TO64;          // ePWM XBAR Mux Enable for Output3
    union   OUT4MUXENABLE_REG                OUT4MUXENABLE;                // ePWM XBAR Mux Enable for Output4
    union   OUT4MUXENABLE32TO64_REG          OUT4MUXENABLE32TO64;          // ePWM XBAR Mux Enable for Output4
    union   OUT5MUXENABLE_REG                OUT5MUXENABLE;                // ePWM XBAR Mux Enable for Output5
    union   OUT5MUXENABLE32TO64_REG          OUT5MUXENABLE32TO64;          // ePWM XBAR Mux Enable for Output5
    union   OUT6MUXENABLE_REG                OUT6MUXENABLE;                // ePWM XBAR Mux Enable for Output6
    union   OUT6MUXENABLE32TO64_REG          OUT6MUXENABLE32TO64;          // ePWM XBAR Mux Enable for Output6
    union   OUT7MUXENABLE_REG                OUT7MUXENABLE;                // ePWM XBAR Mux Enable for Output7
    union   OUT7MUXENABLE32TO64_REG          OUT7MUXENABLE32TO64;          // ePWM XBAR Mux Enable for Output7
    union   OUT8MUXENABLE_REG                OUT8MUXENABLE;                // ePWM XBAR Mux Enable for Output8
    union   OUT8MUXENABLE32TO64_REG          OUT8MUXENABLE32TO64;          // ePWM XBAR Mux Enable for Output8
    Uint16                                   rsvd1[8];                     // Reserved
    union   TRIPOUTINV_REG                   TRIPOUTINV;                   // ePWM XBAR Output Inversion Register
    Uint16                                   rsvd2[4];                     // Reserved
    union   TRIPLOCK_REG                     TRIPLOCK;                     // ePWM XBAR Configuration Lock register
};

//---------------------------------------------------------------------------
// EPWM_XBAR External References & Function Declarations:
//
extern volatile struct EPWM_XBAR_REGS EPwmXbarBRegs;
extern volatile struct EPWM_XBAR_REGS EPwmXbarARegs;
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
