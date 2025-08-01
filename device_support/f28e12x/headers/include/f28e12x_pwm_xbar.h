//###########################################################################
//
// FILE:    f28e12x_pwm_xbar.h
//
// TITLE:   Definitions for the PWM_XBAR registers.
//
//###########################################################################
// $Copyright:
// Copyright (C) 2025 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef F28E12X_PWM_XBAR_H
#define F28E12X_PWM_XBAR_H

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// PWM_XBAR Individual Register Bit Definitions:

struct TRIP1MUX0TO15CFG_BITS {          // bits description
    Uint16 MUX0:2;                      // 1:0 MUX0 Configuration for OUT1 of PWM-XBAR
    Uint16 MUX1:2;                      // 3:2 MUX1 Configuration for OUT1 of PWM-XBAR
    Uint16 MUX2:2;                      // 5:4 MUX2 Configuration for OUT1 of PWM-XBAR
    Uint16 MUX3:2;                      // 7:6 MUX3 Configuration for OUT1 of PWM-XBAR
    Uint16 MUX4:2;                      // 9:8 MUX4 Configuration for OUT1 of PWM-XBAR
    Uint16 MUX5:2;                      // 11:10 MUX5 Configuration for OUT1 of PWM-XBAR
    Uint16 MUX6:2;                      // 13:12 MUX6 Configuration for OUT1 of PWM-XBAR
    Uint16 MUX7:2;                      // 15:14 MUX7 Configuration for OUT1 of PWM-XBAR
    Uint16 MUX8:2;                      // 17:16 MUX8 Configuration for OUT1 of PWM-XBAR
    Uint16 MUX9:2;                      // 19:18 MUX9 Configuration for OUT1 of PWM-XBAR
    Uint16 MUX10:2;                     // 21:20 MUX10 Configuration for OUT1 of PWM-XBAR
    Uint16 MUX11:2;                     // 23:22 MUX11 Configuration for OUT1 of PWM-XBAR
    Uint16 MUX12:2;                     // 25:24 MUX12 Configuration for OUT1 of PWM-XBAR
    Uint16 MUX13:2;                     // 27:26 MUX13 Configuration for OUT1 of PWM-XBAR
    Uint16 MUX14:2;                     // 29:28 MUX14 Configuration for OUT1 of PWM-XBAR
    Uint16 MUX15:2;                     // 31:30 MUX15 Configuration for OUT1 of PWM-XBAR
};

union TRIP1MUX0TO15CFG_REG {
    Uint32  all;
    struct  TRIP1MUX0TO15CFG_BITS  bit;
};

struct TRIP1MUX16TO31CFG_BITS {         // bits description
    Uint16 MUX16:2;                     // 1:0 MUX16 Configuration for OUT1 of PWM-XBAR
    Uint16 MUX17:2;                     // 3:2 MUX17 Configuration for OUT1 of PWM-XBAR
    Uint16 rsvd1:2;                     // 5:4 Reserved
    Uint16 rsvd2:2;                     // 7:6 Reserved
    Uint16 rsvd3:2;                     // 9:8 Reserved
    Uint16 rsvd4:2;                     // 11:10 Reserved
    Uint16 rsvd5:2;                     // 13:12 Reserved
    Uint16 rsvd6:2;                     // 15:14 Reserved
    Uint16 rsvd7:2;                     // 17:16 Reserved
    Uint16 rsvd8:2;                     // 19:18 Reserved
    Uint16 rsvd9:2;                     // 21:20 Reserved
    Uint16 rsvd10:2;                    // 23:22 Reserved
    Uint16 rsvd11:2;                    // 25:24 Reserved
    Uint16 rsvd12:2;                    // 27:26 Reserved
    Uint16 rsvd13:2;                    // 29:28 Reserved
    Uint16 rsvd14:2;                    // 31:30 Reserved
};

union TRIP1MUX16TO31CFG_REG {
    Uint32  all;
    struct  TRIP1MUX16TO31CFG_BITS  bit;
};

struct TRIP2MUX0TO15CFG_BITS {          // bits description
    Uint16 MUX0:2;                      // 1:0 MUX0 Configuration for OUT2 of PWM-XBAR
    Uint16 MUX1:2;                      // 3:2 MUX1 Configuration for OUT2 of PWM-XBAR
    Uint16 MUX2:2;                      // 5:4 MUX2 Configuration for OUT2 of PWM-XBAR
    Uint16 MUX3:2;                      // 7:6 MUX3 Configuration for OUT2 of PWM-XBAR
    Uint16 MUX4:2;                      // 9:8 MUX4 Configuration for OUT2 of PWM-XBAR
    Uint16 MUX5:2;                      // 11:10 MUX5 Configuration for OUT2 of PWM-XBAR
    Uint16 MUX6:2;                      // 13:12 MUX6 Configuration for OUT2 of PWM-XBAR
    Uint16 MUX7:2;                      // 15:14 MUX7 Configuration for OUT2 of PWM-XBAR
    Uint16 MUX8:2;                      // 17:16 MUX8 Configuration for OUT2 of PWM-XBAR
    Uint16 MUX9:2;                      // 19:18 MUX9 Configuration for OUT2 of PWM-XBAR
    Uint16 MUX10:2;                     // 21:20 MUX10 Configuration for OUT2 of PWM-XBAR
    Uint16 MUX11:2;                     // 23:22 MUX11 Configuration for OUT2 of PWM-XBAR
    Uint16 MUX12:2;                     // 25:24 MUX12 Configuration for OUT2 of PWM-XBAR
    Uint16 MUX13:2;                     // 27:26 MUX13 Configuration for OUT2 of PWM-XBAR
    Uint16 MUX14:2;                     // 29:28 MUX14 Configuration for OUT2 of PWM-XBAR
    Uint16 MUX15:2;                     // 31:30 MUX15 Configuration for OUT2 of PWM-XBAR
};

union TRIP2MUX0TO15CFG_REG {
    Uint32  all;
    struct  TRIP2MUX0TO15CFG_BITS  bit;
};

struct TRIP2MUX16TO31CFG_BITS {         // bits description
    Uint16 MUX16:2;                     // 1:0 MUX16 Configuration for OUT2 of PWM-XBAR
    Uint16 MUX17:2;                     // 3:2 MUX17 Configuration for OUT2 of PWM-XBAR
    Uint16 rsvd1:2;                     // 5:4 Reserved
    Uint16 rsvd2:2;                     // 7:6 Reserved
    Uint16 rsvd3:2;                     // 9:8 Reserved
    Uint16 rsvd4:2;                     // 11:10 Reserved
    Uint16 rsvd5:2;                     // 13:12 Reserved
    Uint16 rsvd6:2;                     // 15:14 Reserved
    Uint16 rsvd7:2;                     // 17:16 Reserved
    Uint16 rsvd8:2;                     // 19:18 Reserved
    Uint16 rsvd9:2;                     // 21:20 Reserved
    Uint16 rsvd10:2;                    // 23:22 Reserved
    Uint16 rsvd11:2;                    // 25:24 Reserved
    Uint16 rsvd12:2;                    // 27:26 Reserved
    Uint16 rsvd13:2;                    // 29:28 Reserved
    Uint16 rsvd14:2;                    // 31:30 Reserved
};

union TRIP2MUX16TO31CFG_REG {
    Uint32  all;
    struct  TRIP2MUX16TO31CFG_BITS  bit;
};

struct TRIP3MUX0TO15CFG_BITS {          // bits description
    Uint16 MUX0:2;                      // 1:0 MUX0 Configuration for OUT3 of PWM-XBAR
    Uint16 MUX1:2;                      // 3:2 MUX1 Configuration for OUT3 of PWM-XBAR
    Uint16 MUX2:2;                      // 5:4 MUX2 Configuration for OUT3 of PWM-XBAR
    Uint16 MUX3:2;                      // 7:6 MUX3 Configuration for OUT3 of PWM-XBAR
    Uint16 MUX4:2;                      // 9:8 MUX4 Configuration for OUT3 of PWM-XBAR
    Uint16 MUX5:2;                      // 11:10 MUX5 Configuration for OUT3 of PWM-XBAR
    Uint16 MUX6:2;                      // 13:12 MUX6 Configuration for OUT3 of PWM-XBAR
    Uint16 MUX7:2;                      // 15:14 MUX7 Configuration for OUT3 of PWM-XBAR
    Uint16 MUX8:2;                      // 17:16 MUX8 Configuration for OUT3 of PWM-XBAR
    Uint16 MUX9:2;                      // 19:18 MUX9 Configuration for OUT3 of PWM-XBAR
    Uint16 MUX10:2;                     // 21:20 MUX10 Configuration for OUT3 of PWM-XBAR
    Uint16 MUX11:2;                     // 23:22 MUX11 Configuration for OUT3 of PWM-XBAR
    Uint16 MUX12:2;                     // 25:24 MUX12 Configuration for OUT3 of PWM-XBAR
    Uint16 MUX13:2;                     // 27:26 MUX13 Configuration for OUT3 of PWM-XBAR
    Uint16 MUX14:2;                     // 29:28 MUX14 Configuration for OUT3 of PWM-XBAR
    Uint16 MUX15:2;                     // 31:30 MUX15 Configuration for OUT3 of PWM-XBAR
};

union TRIP3MUX0TO15CFG_REG {
    Uint32  all;
    struct  TRIP3MUX0TO15CFG_BITS  bit;
};

struct TRIP3MUX16TO31CFG_BITS {         // bits description
    Uint16 MUX16:2;                     // 1:0 MUX16 Configuration for OUT3 of PWM-XBAR
    Uint16 MUX17:2;                     // 3:2 MUX17 Configuration for OUT3 of PWM-XBAR
    Uint16 rsvd1:2;                     // 5:4 Reserved
    Uint16 rsvd2:2;                     // 7:6 Reserved
    Uint16 rsvd3:2;                     // 9:8 Reserved
    Uint16 rsvd4:2;                     // 11:10 Reserved
    Uint16 rsvd5:2;                     // 13:12 Reserved
    Uint16 rsvd6:2;                     // 15:14 Reserved
    Uint16 rsvd7:2;                     // 17:16 Reserved
    Uint16 rsvd8:2;                     // 19:18 Reserved
    Uint16 rsvd9:2;                     // 21:20 Reserved
    Uint16 rsvd10:2;                    // 23:22 Reserved
    Uint16 rsvd11:2;                    // 25:24 Reserved
    Uint16 rsvd12:2;                    // 27:26 Reserved
    Uint16 rsvd13:2;                    // 29:28 Reserved
    Uint16 rsvd14:2;                    // 31:30 Reserved
};

union TRIP3MUX16TO31CFG_REG {
    Uint32  all;
    struct  TRIP3MUX16TO31CFG_BITS  bit;
};

struct TRIP4MUX0TO15CFG_BITS {          // bits description
    Uint16 MUX0:2;                      // 1:0 MUX0 Configuration for OUT4 of PWM-XBAR
    Uint16 MUX1:2;                      // 3:2 MUX1 Configuration for OUT4 of PWM-XBAR
    Uint16 MUX2:2;                      // 5:4 MUX2 Configuration for OUT4 of PWM-XBAR
    Uint16 MUX3:2;                      // 7:6 MUX3 Configuration for OUT4 of PWM-XBAR
    Uint16 MUX4:2;                      // 9:8 MUX4 Configuration for OUT4 of PWM-XBAR
    Uint16 MUX5:2;                      // 11:10 MUX5 Configuration for OUT4 of PWM-XBAR
    Uint16 MUX6:2;                      // 13:12 MUX6 Configuration for OUT4 of PWM-XBAR
    Uint16 MUX7:2;                      // 15:14 MUX7 Configuration for OUT4 of PWM-XBAR
    Uint16 MUX8:2;                      // 17:16 MUX8 Configuration for OUT4 of PWM-XBAR
    Uint16 MUX9:2;                      // 19:18 MUX9 Configuration for OUT4 of PWM-XBAR
    Uint16 MUX10:2;                     // 21:20 MUX10 Configuration for OUT4 of PWM-XBAR
    Uint16 MUX11:2;                     // 23:22 MUX11 Configuration for OUT4 of PWM-XBAR
    Uint16 MUX12:2;                     // 25:24 MUX12 Configuration for OUT4 of PWM-XBAR
    Uint16 MUX13:2;                     // 27:26 MUX13 Configuration for OUT4 of PWM-XBAR
    Uint16 MUX14:2;                     // 29:28 MUX14 Configuration for OUT4 of PWM-XBAR
    Uint16 MUX15:2;                     // 31:30 MUX15 Configuration for OUT4 of PWM-XBAR
};

union TRIP4MUX0TO15CFG_REG {
    Uint32  all;
    struct  TRIP4MUX0TO15CFG_BITS  bit;
};

struct TRIP4MUX16TO31CFG_BITS {         // bits description
    Uint16 MUX16:2;                     // 1:0 MUX16 Configuration for OUT4 of PWM-XBAR
    Uint16 MUX17:2;                     // 3:2 MUX17 Configuration for OUT4 of PWM-XBAR
    Uint16 rsvd1:2;                     // 5:4 Reserved
    Uint16 rsvd2:2;                     // 7:6 Reserved
    Uint16 rsvd3:2;                     // 9:8 Reserved
    Uint16 rsvd4:2;                     // 11:10 Reserved
    Uint16 rsvd5:2;                     // 13:12 Reserved
    Uint16 rsvd6:2;                     // 15:14 Reserved
    Uint16 rsvd7:2;                     // 17:16 Reserved
    Uint16 rsvd8:2;                     // 19:18 Reserved
    Uint16 rsvd9:2;                     // 21:20 Reserved
    Uint16 rsvd10:2;                    // 23:22 Reserved
    Uint16 rsvd11:2;                    // 25:24 Reserved
    Uint16 rsvd12:2;                    // 27:26 Reserved
    Uint16 rsvd13:2;                    // 29:28 Reserved
    Uint16 rsvd14:2;                    // 31:30 Reserved
};

union TRIP4MUX16TO31CFG_REG {
    Uint32  all;
    struct  TRIP4MUX16TO31CFG_BITS  bit;
};

struct TRIP5MUX0TO15CFG_BITS {          // bits description
    Uint16 MUX0:2;                      // 1:0 MUX0 Configuration for OUT5 of PWM-XBAR
    Uint16 MUX1:2;                      // 3:2 MUX1 Configuration for OUT5 of PWM-XBAR
    Uint16 MUX2:2;                      // 5:4 MUX2 Configuration for OUT5 of PWM-XBAR
    Uint16 MUX3:2;                      // 7:6 MUX3 Configuration for OUT5 of PWM-XBAR
    Uint16 MUX4:2;                      // 9:8 MUX4 Configuration for OUT5 of PWM-XBAR
    Uint16 MUX5:2;                      // 11:10 MUX5 Configuration for OUT5 of PWM-XBAR
    Uint16 MUX6:2;                      // 13:12 MUX6 Configuration for OUT5 of PWM-XBAR
    Uint16 MUX7:2;                      // 15:14 MUX7 Configuration for OUT5 of PWM-XBAR
    Uint16 MUX8:2;                      // 17:16 MUX8 Configuration for OUT5 of PWM-XBAR
    Uint16 MUX9:2;                      // 19:18 MUX9 Configuration for OUT5 of PWM-XBAR
    Uint16 MUX10:2;                     // 21:20 MUX10 Configuration for OUT5 of PWM-XBAR
    Uint16 MUX11:2;                     // 23:22 MUX11 Configuration for OUT5 of PWM-XBAR
    Uint16 MUX12:2;                     // 25:24 MUX12 Configuration for OUT5 of PWM-XBAR
    Uint16 MUX13:2;                     // 27:26 MUX13 Configuration for OUT5 of PWM-XBAR
    Uint16 MUX14:2;                     // 29:28 MUX14 Configuration for OUT5 of PWM-XBAR
    Uint16 MUX15:2;                     // 31:30 MUX15 Configuration for OUT5 of PWM-XBAR
};

union TRIP5MUX0TO15CFG_REG {
    Uint32  all;
    struct  TRIP5MUX0TO15CFG_BITS  bit;
};

struct TRIP5MUX16TO31CFG_BITS {         // bits description
    Uint16 MUX16:2;                     // 1:0 MUX16 Configuration for OUT5 of PWM-XBAR
    Uint16 MUX17:2;                     // 3:2 MUX17 Configuration for OUT5 of PWM-XBAR
    Uint16 rsvd1:2;                     // 5:4 Reserved
    Uint16 rsvd2:2;                     // 7:6 Reserved
    Uint16 rsvd3:2;                     // 9:8 Reserved
    Uint16 rsvd4:2;                     // 11:10 Reserved
    Uint16 rsvd5:2;                     // 13:12 Reserved
    Uint16 rsvd6:2;                     // 15:14 Reserved
    Uint16 rsvd7:2;                     // 17:16 Reserved
    Uint16 rsvd8:2;                     // 19:18 Reserved
    Uint16 rsvd9:2;                     // 21:20 Reserved
    Uint16 rsvd10:2;                    // 23:22 Reserved
    Uint16 rsvd11:2;                    // 25:24 Reserved
    Uint16 rsvd12:2;                    // 27:26 Reserved
    Uint16 rsvd13:2;                    // 29:28 Reserved
    Uint16 rsvd14:2;                    // 31:30 Reserved
};

union TRIP5MUX16TO31CFG_REG {
    Uint32  all;
    struct  TRIP5MUX16TO31CFG_BITS  bit;
};

struct TRIP6MUX0TO15CFG_BITS {          // bits description
    Uint16 MUX0:2;                      // 1:0 MUX0 Configuration for OUT6 of PWM-XBAR
    Uint16 MUX1:2;                      // 3:2 MUX1 Configuration for OUT6 of PWM-XBAR
    Uint16 MUX2:2;                      // 5:4 MUX2 Configuration for OUT6 of PWM-XBAR
    Uint16 MUX3:2;                      // 7:6 MUX3 Configuration for OUT6 of PWM-XBAR
    Uint16 MUX4:2;                      // 9:8 MUX4 Configuration for OUT6 of PWM-XBAR
    Uint16 MUX5:2;                      // 11:10 MUX5 Configuration for OUT6 of PWM-XBAR
    Uint16 MUX6:2;                      // 13:12 MUX6 Configuration for OUT6 of PWM-XBAR
    Uint16 MUX7:2;                      // 15:14 MUX7 Configuration for OUT6 of PWM-XBAR
    Uint16 MUX8:2;                      // 17:16 MUX8 Configuration for OUT6 of PWM-XBAR
    Uint16 MUX9:2;                      // 19:18 MUX9 Configuration for OUT6 of PWM-XBAR
    Uint16 MUX10:2;                     // 21:20 MUX10 Configuration for OUT6 of PWM-XBAR
    Uint16 MUX11:2;                     // 23:22 MUX11 Configuration for OUT6 of PWM-XBAR
    Uint16 MUX12:2;                     // 25:24 MUX12 Configuration for OUT6 of PWM-XBAR
    Uint16 MUX13:2;                     // 27:26 MUX13 Configuration for OUT6 of PWM-XBAR
    Uint16 MUX14:2;                     // 29:28 MUX14 Configuration for OUT6 of PWM-XBAR
    Uint16 MUX15:2;                     // 31:30 MUX15 Configuration for OUT6 of PWM-XBAR
};

union TRIP6MUX0TO15CFG_REG {
    Uint32  all;
    struct  TRIP6MUX0TO15CFG_BITS  bit;
};

struct TRIP6MUX16TO31CFG_BITS {         // bits description
    Uint16 MUX16:2;                     // 1:0 MUX16 Configuration for OUT6 of PWM-XBAR
    Uint16 MUX17:2;                     // 3:2 MUX17 Configuration for OUT6 of PWM-XBAR
    Uint16 rsvd1:2;                     // 5:4 Reserved
    Uint16 rsvd2:2;                     // 7:6 Reserved
    Uint16 rsvd3:2;                     // 9:8 Reserved
    Uint16 rsvd4:2;                     // 11:10 Reserved
    Uint16 rsvd5:2;                     // 13:12 Reserved
    Uint16 rsvd6:2;                     // 15:14 Reserved
    Uint16 rsvd7:2;                     // 17:16 Reserved
    Uint16 rsvd8:2;                     // 19:18 Reserved
    Uint16 rsvd9:2;                     // 21:20 Reserved
    Uint16 rsvd10:2;                    // 23:22 Reserved
    Uint16 rsvd11:2;                    // 25:24 Reserved
    Uint16 rsvd12:2;                    // 27:26 Reserved
    Uint16 rsvd13:2;                    // 29:28 Reserved
    Uint16 rsvd14:2;                    // 31:30 Reserved
};

union TRIP6MUX16TO31CFG_REG {
    Uint32  all;
    struct  TRIP6MUX16TO31CFG_BITS  bit;
};

struct TRIP7MUX0TO15CFG_BITS {          // bits description
    Uint16 MUX0:2;                      // 1:0 MUX0 Configuration for OUT7 of PWM-XBAR
    Uint16 MUX1:2;                      // 3:2 MUX1 Configuration for OUT7 of PWM-XBAR
    Uint16 MUX2:2;                      // 5:4 MUX2 Configuration for OUT7 of PWM-XBAR
    Uint16 MUX3:2;                      // 7:6 MUX3 Configuration for OUT7 of PWM-XBAR
    Uint16 MUX4:2;                      // 9:8 MUX4 Configuration for OUT7 of PWM-XBAR
    Uint16 MUX5:2;                      // 11:10 MUX5 Configuration for OUT7 of PWM-XBAR
    Uint16 MUX6:2;                      // 13:12 MUX6 Configuration for OUT7 of PWM-XBAR
    Uint16 MUX7:2;                      // 15:14 MUX7 Configuration for OUT7 of PWM-XBAR
    Uint16 MUX8:2;                      // 17:16 MUX8 Configuration for OUT7 of PWM-XBAR
    Uint16 MUX9:2;                      // 19:18 MUX9 Configuration for OUT7 of PWM-XBAR
    Uint16 MUX10:2;                     // 21:20 MUX10 Configuration for OUT7 of PWM-XBAR
    Uint16 MUX11:2;                     // 23:22 MUX11 Configuration for OUT7 of PWM-XBAR
    Uint16 MUX12:2;                     // 25:24 MUX12 Configuration for OUT7 of PWM-XBAR
    Uint16 MUX13:2;                     // 27:26 MUX13 Configuration for OUT7 of PWM-XBAR
    Uint16 MUX14:2;                     // 29:28 MUX14 Configuration for OUT7 of PWM-XBAR
    Uint16 MUX15:2;                     // 31:30 MUX15 Configuration for OUT7 of PWM-XBAR
};

union TRIP7MUX0TO15CFG_REG {
    Uint32  all;
    struct  TRIP7MUX0TO15CFG_BITS  bit;
};

struct TRIP7MUX16TO31CFG_BITS {         // bits description
    Uint16 MUX16:2;                     // 1:0 MUX16 Configuration for OUT7 of PWM-XBAR
    Uint16 MUX17:2;                     // 3:2 MUX17 Configuration for OUT7 of PWM-XBAR
    Uint16 rsvd1:2;                     // 5:4 Reserved
    Uint16 rsvd2:2;                     // 7:6 Reserved
    Uint16 rsvd3:2;                     // 9:8 Reserved
    Uint16 rsvd4:2;                     // 11:10 Reserved
    Uint16 rsvd5:2;                     // 13:12 Reserved
    Uint16 rsvd6:2;                     // 15:14 Reserved
    Uint16 rsvd7:2;                     // 17:16 Reserved
    Uint16 rsvd8:2;                     // 19:18 Reserved
    Uint16 rsvd9:2;                     // 21:20 Reserved
    Uint16 rsvd10:2;                    // 23:22 Reserved
    Uint16 rsvd11:2;                    // 25:24 Reserved
    Uint16 rsvd12:2;                    // 27:26 Reserved
    Uint16 rsvd13:2;                    // 29:28 Reserved
    Uint16 rsvd14:2;                    // 31:30 Reserved
};

union TRIP7MUX16TO31CFG_REG {
    Uint32  all;
    struct  TRIP7MUX16TO31CFG_BITS  bit;
};

struct TRIP8MUX0TO15CFG_BITS {          // bits description
    Uint16 MUX0:2;                      // 1:0 MUX0 Configuration for OUT8 of PWM-XBAR
    Uint16 MUX1:2;                      // 3:2 MUX1 Configuration for OUT8 of PWM-XBAR
    Uint16 MUX2:2;                      // 5:4 MUX2 Configuration for OUT8 of PWM-XBAR
    Uint16 MUX3:2;                      // 7:6 MUX3 Configuration for OUT8 of PWM-XBAR
    Uint16 MUX4:2;                      // 9:8 MUX4 Configuration for OUT8 of PWM-XBAR
    Uint16 MUX5:2;                      // 11:10 MUX5 Configuration for OUT8 of PWM-XBAR
    Uint16 MUX6:2;                      // 13:12 MUX6 Configuration for OUT8 of PWM-XBAR
    Uint16 MUX7:2;                      // 15:14 MUX7 Configuration for OUT8 of PWM-XBAR
    Uint16 MUX8:2;                      // 17:16 MUX8 Configuration for OUT8 of PWM-XBAR
    Uint16 MUX9:2;                      // 19:18 MUX9 Configuration for OUT8 of PWM-XBAR
    Uint16 MUX10:2;                     // 21:20 MUX10 Configuration for OUT8 of PWM-XBAR
    Uint16 MUX11:2;                     // 23:22 MUX11 Configuration for OUT8 of PWM-XBAR
    Uint16 MUX12:2;                     // 25:24 MUX12 Configuration for OUT8 of PWM-XBAR
    Uint16 MUX13:2;                     // 27:26 MUX13 Configuration for OUT8 of PWM-XBAR
    Uint16 MUX14:2;                     // 29:28 MUX14 Configuration for OUT8 of PWM-XBAR
    Uint16 MUX15:2;                     // 31:30 MUX15 Configuration for OUT8 of PWM-XBAR
};

union TRIP8MUX0TO15CFG_REG {
    Uint32  all;
    struct  TRIP8MUX0TO15CFG_BITS  bit;
};

struct TRIP8MUX16TO31CFG_BITS {         // bits description
    Uint16 MUX16:2;                     // 1:0 MUX16 Configuration for OUT8 of PWM-XBAR
    Uint16 MUX17:2;                     // 3:2 MUX17 Configuration for OUT8 of PWM-XBAR
    Uint16 rsvd1:2;                     // 5:4 Reserved
    Uint16 rsvd2:2;                     // 7:6 Reserved
    Uint16 rsvd3:2;                     // 9:8 Reserved
    Uint16 rsvd4:2;                     // 11:10 Reserved
    Uint16 rsvd5:2;                     // 13:12 Reserved
    Uint16 rsvd6:2;                     // 15:14 Reserved
    Uint16 rsvd7:2;                     // 17:16 Reserved
    Uint16 rsvd8:2;                     // 19:18 Reserved
    Uint16 rsvd9:2;                     // 21:20 Reserved
    Uint16 rsvd10:2;                    // 23:22 Reserved
    Uint16 rsvd11:2;                    // 25:24 Reserved
    Uint16 rsvd12:2;                    // 27:26 Reserved
    Uint16 rsvd13:2;                    // 29:28 Reserved
    Uint16 rsvd14:2;                    // 31:30 Reserved
};

union TRIP8MUX16TO31CFG_REG {
    Uint32  all;
    struct  TRIP8MUX16TO31CFG_BITS  bit;
};

struct TRIP1MUXENABLE_BITS {            // bits description
    Uint16 MUX0:1;                      // 0 MUX0 to drive OUT1 of PWM-XBAR
    Uint16 MUX1:1;                      // 1 MUX1 to drive OUT1 of PWM-XBAR
    Uint16 MUX2:1;                      // 2 MUX2 to drive OUT1 of PWM-XBAR
    Uint16 MUX3:1;                      // 3 MUX3 to drive OUT1 of PWM-XBAR
    Uint16 MUX4:1;                      // 4 MUX4 to drive OUT1 of PWM-XBAR
    Uint16 MUX5:1;                      // 5 MUX5 to drive OUT1 of PWM-XBAR
    Uint16 MUX6:1;                      // 6 MUX6 to drive OUT1 of PWM-XBAR
    Uint16 MUX7:1;                      // 7 MUX7 to drive OUT1 of PWM-XBAR
    Uint16 MUX8:1;                      // 8 MUX8 to drive OUT1 of PWM-XBAR
    Uint16 MUX9:1;                      // 9 MUX9 to drive OUT1 of PWM-XBAR
    Uint16 MUX10:1;                     // 10 MUX10 to drive OUT1 of PWM-XBAR
    Uint16 MUX11:1;                     // 11 MUX11 to drive OUT1 of PWM-XBAR
    Uint16 MUX12:1;                     // 12 MUX12 to drive OUT1 of PWM-XBAR
    Uint16 MUX13:1;                     // 13 MUX13 to drive OUT1 of PWM-XBAR
    Uint16 MUX14:1;                     // 14 MUX14 to drive OUT1 of PWM-XBAR
    Uint16 MUX15:1;                     // 15 MUX15 to drive OUT1 of PWM-XBAR
    Uint16 MUX16:1;                     // 16 MUX16 to drive OUT1 of PWM-XBAR
    Uint16 MUX17:1;                     // 17 MUX17 to drive OUT1 of PWM-XBAR
    Uint16 rsvd1:1;                     // 18 Reserved
    Uint16 rsvd2:1;                     // 19 Reserved
    Uint16 rsvd3:1;                     // 20 Reserved
    Uint16 rsvd4:1;                     // 21 Reserved
    Uint16 rsvd5:1;                     // 22 Reserved
    Uint16 rsvd6:1;                     // 23 Reserved
    Uint16 rsvd7:1;                     // 24 Reserved
    Uint16 rsvd8:1;                     // 25 Reserved
    Uint16 rsvd9:1;                     // 26 Reserved
    Uint16 rsvd10:1;                    // 27 Reserved
    Uint16 rsvd11:1;                    // 28 Reserved
    Uint16 rsvd12:1;                    // 29 Reserved
    Uint16 rsvd13:1;                    // 30 Reserved
    Uint16 rsvd14:1;                    // 31 Reserved
};

union TRIP1MUXENABLE_REG {
    Uint32  all;
    struct  TRIP1MUXENABLE_BITS  bit;
};

struct TRIP2MUXENABLE_BITS {            // bits description
    Uint16 MUX0:1;                      // 0 MUX0 to drive OUT2 of PWM-XBAR
    Uint16 MUX1:1;                      // 1 MUX1 to drive OUT2 of PWM-XBAR
    Uint16 MUX2:1;                      // 2 MUX2 to drive OUT2 of PWM-XBAR
    Uint16 MUX3:1;                      // 3 MUX3 to drive OUT2 of PWM-XBAR
    Uint16 MUX4:1;                      // 4 MUX4 to drive OUT2 of PWM-XBAR
    Uint16 MUX5:1;                      // 5 MUX5 to drive OUT2 of PWM-XBAR
    Uint16 MUX6:1;                      // 6 MUX6 to drive OUT2 of PWM-XBAR
    Uint16 MUX7:1;                      // 7 MUX7 to drive OUT2 of PWM-XBAR
    Uint16 MUX8:1;                      // 8 MUX8 to drive OUT2 of PWM-XBAR
    Uint16 MUX9:1;                      // 9 MUX9 to drive OUT2 of PWM-XBAR
    Uint16 MUX10:1;                     // 10 MUX10 to drive OUT2 of PWM-XBAR
    Uint16 MUX11:1;                     // 11 MUX11 to drive OUT2 of PWM-XBAR
    Uint16 MUX12:1;                     // 12 MUX12 to drive OUT2 of PWM-XBAR
    Uint16 MUX13:1;                     // 13 MUX13 to drive OUT2 of PWM-XBAR
    Uint16 MUX14:1;                     // 14 MUX14 to drive OUT2 of PWM-XBAR
    Uint16 MUX15:1;                     // 15 MUX15 to drive OUT2 of PWM-XBAR
    Uint16 MUX16:1;                     // 16 MUX16 to drive OUT2 of PWM-XBAR
    Uint16 MUX17:1;                     // 17 MUX17 to drive OUT2 of PWM-XBAR
    Uint16 rsvd1:1;                     // 18 Reserved
    Uint16 rsvd2:1;                     // 19 Reserved
    Uint16 rsvd3:1;                     // 20 Reserved
    Uint16 rsvd4:1;                     // 21 Reserved
    Uint16 rsvd5:1;                     // 22 Reserved
    Uint16 rsvd6:1;                     // 23 Reserved
    Uint16 rsvd7:1;                     // 24 Reserved
    Uint16 rsvd8:1;                     // 25 Reserved
    Uint16 rsvd9:1;                     // 26 Reserved
    Uint16 rsvd10:1;                    // 27 Reserved
    Uint16 rsvd11:1;                    // 28 Reserved
    Uint16 rsvd12:1;                    // 29 Reserved
    Uint16 rsvd13:1;                    // 30 Reserved
    Uint16 rsvd14:1;                    // 31 Reserved
};

union TRIP2MUXENABLE_REG {
    Uint32  all;
    struct  TRIP2MUXENABLE_BITS  bit;
};

struct TRIP3MUXENABLE_BITS {            // bits description
    Uint16 MUX0:1;                      // 0 MUX0 to drive OUT3 of PWM-XBAR
    Uint16 MUX1:1;                      // 1 MUX1 to drive OUT3 of PWM-XBAR
    Uint16 MUX2:1;                      // 2 MUX2 to drive OUT3 of PWM-XBAR
    Uint16 MUX3:1;                      // 3 MUX3 to drive OUT3 of PWM-XBAR
    Uint16 MUX4:1;                      // 4 MUX4 to drive OUT3 of PWM-XBAR
    Uint16 MUX5:1;                      // 5 MUX5 to drive OUT3 of PWM-XBAR
    Uint16 MUX6:1;                      // 6 MUX6 to drive OUT3 of PWM-XBAR
    Uint16 MUX7:1;                      // 7 MUX7 to drive OUT3 of PWM-XBAR
    Uint16 MUX8:1;                      // 8 MUX8 to drive OUT3 of PWM-XBAR
    Uint16 MUX9:1;                      // 9 MUX9 to drive OUT3 of PWM-XBAR
    Uint16 MUX10:1;                     // 10 MUX10 to drive OUT3 of PWM-XBAR
    Uint16 MUX11:1;                     // 11 MUX11 to drive OUT3 of PWM-XBAR
    Uint16 MUX12:1;                     // 12 MUX12 to drive OUT3 of PWM-XBAR
    Uint16 MUX13:1;                     // 13 MUX13 to drive OUT3 of PWM-XBAR
    Uint16 MUX14:1;                     // 14 MUX14 to drive OUT3 of PWM-XBAR
    Uint16 MUX15:1;                     // 15 MUX15 to drive OUT3 of PWM-XBAR
    Uint16 MUX16:1;                     // 16 MUX16 to drive OUT3 of PWM-XBAR
    Uint16 MUX17:1;                     // 17 MUX17 to drive OUT3 of PWM-XBAR
    Uint16 rsvd1:1;                     // 18 Reserved
    Uint16 rsvd2:1;                     // 19 Reserved
    Uint16 rsvd3:1;                     // 20 Reserved
    Uint16 rsvd4:1;                     // 21 Reserved
    Uint16 rsvd5:1;                     // 22 Reserved
    Uint16 rsvd6:1;                     // 23 Reserved
    Uint16 rsvd7:1;                     // 24 Reserved
    Uint16 rsvd8:1;                     // 25 Reserved
    Uint16 rsvd9:1;                     // 26 Reserved
    Uint16 rsvd10:1;                    // 27 Reserved
    Uint16 rsvd11:1;                    // 28 Reserved
    Uint16 rsvd12:1;                    // 29 Reserved
    Uint16 rsvd13:1;                    // 30 Reserved
    Uint16 rsvd14:1;                    // 31 Reserved
};

union TRIP3MUXENABLE_REG {
    Uint32  all;
    struct  TRIP3MUXENABLE_BITS  bit;
};

struct TRIP4MUXENABLE_BITS {            // bits description
    Uint16 MUX0:1;                      // 0 MUX0 to drive OUT4 of PWM-XBAR
    Uint16 MUX1:1;                      // 1 MUX1 to drive OUT4 of PWM-XBAR
    Uint16 MUX2:1;                      // 2 MUX2 to drive OUT4 of PWM-XBAR
    Uint16 MUX3:1;                      // 3 MUX3 to drive OUT4 of PWM-XBAR
    Uint16 MUX4:1;                      // 4 MUX4 to drive OUT4 of PWM-XBAR
    Uint16 MUX5:1;                      // 5 MUX5 to drive OUT4 of PWM-XBAR
    Uint16 MUX6:1;                      // 6 MUX6 to drive OUT4 of PWM-XBAR
    Uint16 MUX7:1;                      // 7 MUX7 to drive OUT4 of PWM-XBAR
    Uint16 MUX8:1;                      // 8 MUX8 to drive OUT4 of PWM-XBAR
    Uint16 MUX9:1;                      // 9 MUX9 to drive OUT4 of PWM-XBAR
    Uint16 MUX10:1;                     // 10 MUX10 to drive OUT4 of PWM-XBAR
    Uint16 MUX11:1;                     // 11 MUX11 to drive OUT4 of PWM-XBAR
    Uint16 MUX12:1;                     // 12 MUX12 to drive OUT4 of PWM-XBAR
    Uint16 MUX13:1;                     // 13 MUX13 to drive OUT4 of PWM-XBAR
    Uint16 MUX14:1;                     // 14 MUX14 to drive OUT4 of PWM-XBAR
    Uint16 MUX15:1;                     // 15 MUX15 to drive OUT4 of PWM-XBAR
    Uint16 MUX16:1;                     // 16 MUX16 to drive OUT4 of PWM-XBAR
    Uint16 MUX17:1;                     // 17 MUX17 to drive OUT4 of PWM-XBAR
    Uint16 rsvd1:1;                     // 18 Reserved
    Uint16 rsvd2:1;                     // 19 Reserved
    Uint16 rsvd3:1;                     // 20 Reserved
    Uint16 rsvd4:1;                     // 21 Reserved
    Uint16 rsvd5:1;                     // 22 Reserved
    Uint16 rsvd6:1;                     // 23 Reserved
    Uint16 rsvd7:1;                     // 24 Reserved
    Uint16 rsvd8:1;                     // 25 Reserved
    Uint16 rsvd9:1;                     // 26 Reserved
    Uint16 rsvd10:1;                    // 27 Reserved
    Uint16 rsvd11:1;                    // 28 Reserved
    Uint16 rsvd12:1;                    // 29 Reserved
    Uint16 rsvd13:1;                    // 30 Reserved
    Uint16 rsvd14:1;                    // 31 Reserved
};

union TRIP4MUXENABLE_REG {
    Uint32  all;
    struct  TRIP4MUXENABLE_BITS  bit;
};

struct TRIP5MUXENABLE_BITS {            // bits description
    Uint16 MUX0:1;                      // 0 MUX0 to drive OUT5 of PWM-XBAR
    Uint16 MUX1:1;                      // 1 MUX1 to drive OUT5 of PWM-XBAR
    Uint16 MUX2:1;                      // 2 MUX2 to drive OUT5 of PWM-XBAR
    Uint16 MUX3:1;                      // 3 MUX3 to drive OUT5 of PWM-XBAR
    Uint16 MUX4:1;                      // 4 MUX4 to drive OUT5 of PWM-XBAR
    Uint16 MUX5:1;                      // 5 MUX5 to drive OUT5 of PWM-XBAR
    Uint16 MUX6:1;                      // 6 MUX6 to drive OUT5 of PWM-XBAR
    Uint16 MUX7:1;                      // 7 MUX7 to drive OUT5 of PWM-XBAR
    Uint16 MUX8:1;                      // 8 MUX8 to drive OUT5 of PWM-XBAR
    Uint16 MUX9:1;                      // 9 MUX9 to drive OUT5 of PWM-XBAR
    Uint16 MUX10:1;                     // 10 MUX10 to drive OUT5 of PWM-XBAR
    Uint16 MUX11:1;                     // 11 MUX11 to drive OUT5 of PWM-XBAR
    Uint16 MUX12:1;                     // 12 MUX12 to drive OUT5 of PWM-XBAR
    Uint16 MUX13:1;                     // 13 MUX13 to drive OUT5 of PWM-XBAR
    Uint16 MUX14:1;                     // 14 MUX14 to drive OUT5 of PWM-XBAR
    Uint16 MUX15:1;                     // 15 MUX15 to drive OUT5 of PWM-XBAR
    Uint16 MUX16:1;                     // 16 MUX16 to drive OUT5 of PWM-XBAR
    Uint16 MUX17:1;                     // 17 MUX17 to drive OUT5 of PWM-XBAR
    Uint16 rsvd1:1;                     // 18 Reserved
    Uint16 rsvd2:1;                     // 19 Reserved
    Uint16 rsvd3:1;                     // 20 Reserved
    Uint16 rsvd4:1;                     // 21 Reserved
    Uint16 rsvd5:1;                     // 22 Reserved
    Uint16 rsvd6:1;                     // 23 Reserved
    Uint16 rsvd7:1;                     // 24 Reserved
    Uint16 rsvd8:1;                     // 25 Reserved
    Uint16 rsvd9:1;                     // 26 Reserved
    Uint16 rsvd10:1;                    // 27 Reserved
    Uint16 rsvd11:1;                    // 28 Reserved
    Uint16 rsvd12:1;                    // 29 Reserved
    Uint16 rsvd13:1;                    // 30 Reserved
    Uint16 rsvd14:1;                    // 31 Reserved
};

union TRIP5MUXENABLE_REG {
    Uint32  all;
    struct  TRIP5MUXENABLE_BITS  bit;
};

struct TRIP6MUXENABLE_BITS {            // bits description
    Uint16 MUX0:1;                      // 0 MUX0 to drive OUT6 of PWM-XBAR
    Uint16 MUX1:1;                      // 1 MUX1 to drive OUT6 of PWM-XBAR
    Uint16 MUX2:1;                      // 2 MUX2 to drive OUT6 of PWM-XBAR
    Uint16 MUX3:1;                      // 3 MUX3 to drive OUT6 of PWM-XBAR
    Uint16 MUX4:1;                      // 4 MUX4 to drive OUT6 of PWM-XBAR
    Uint16 MUX5:1;                      // 5 MUX5 to drive OUT6 of PWM-XBAR
    Uint16 MUX6:1;                      // 6 MUX6 to drive OUT6 of PWM-XBAR
    Uint16 MUX7:1;                      // 7 MUX7 to drive OUT6 of PWM-XBAR
    Uint16 MUX8:1;                      // 8 MUX8 to drive OUT6 of PWM-XBAR
    Uint16 MUX9:1;                      // 9 MUX9 to drive OUT6 of PWM-XBAR
    Uint16 MUX10:1;                     // 10 MUX10 to drive OUT6 of PWM-XBAR
    Uint16 MUX11:1;                     // 11 MUX11 to drive OUT6 of PWM-XBAR
    Uint16 MUX12:1;                     // 12 MUX12 to drive OUT6 of PWM-XBAR
    Uint16 MUX13:1;                     // 13 MUX13 to drive OUT6 of PWM-XBAR
    Uint16 MUX14:1;                     // 14 MUX14 to drive OUT6 of PWM-XBAR
    Uint16 MUX15:1;                     // 15 MUX15 to drive OUT6 of PWM-XBAR
    Uint16 MUX16:1;                     // 16 MUX16 to drive OUT6 of PWM-XBAR
    Uint16 MUX17:1;                     // 17 MUX17 to drive OUT6 of PWM-XBAR
    Uint16 rsvd1:1;                     // 18 Reserved
    Uint16 rsvd2:1;                     // 19 Reserved
    Uint16 rsvd3:1;                     // 20 Reserved
    Uint16 rsvd4:1;                     // 21 Reserved
    Uint16 rsvd5:1;                     // 22 Reserved
    Uint16 rsvd6:1;                     // 23 Reserved
    Uint16 rsvd7:1;                     // 24 Reserved
    Uint16 rsvd8:1;                     // 25 Reserved
    Uint16 rsvd9:1;                     // 26 Reserved
    Uint16 rsvd10:1;                    // 27 Reserved
    Uint16 rsvd11:1;                    // 28 Reserved
    Uint16 rsvd12:1;                    // 29 Reserved
    Uint16 rsvd13:1;                    // 30 Reserved
    Uint16 rsvd14:1;                    // 31 Reserved
};

union TRIP6MUXENABLE_REG {
    Uint32  all;
    struct  TRIP6MUXENABLE_BITS  bit;
};

struct TRIP7MUXENABLE_BITS {            // bits description
    Uint16 MUX0:1;                      // 0 MUX0 to drive OUT7 of PWM-XBAR
    Uint16 MUX1:1;                      // 1 MUX1 to drive OUT7 of PWM-XBAR
    Uint16 MUX2:1;                      // 2 MUX2 to drive OUT7 of PWM-XBAR
    Uint16 MUX3:1;                      // 3 MUX3 to drive OUT7 of PWM-XBAR
    Uint16 MUX4:1;                      // 4 MUX4 to drive OUT7 of PWM-XBAR
    Uint16 MUX5:1;                      // 5 MUX5 to drive OUT7 of PWM-XBAR
    Uint16 MUX6:1;                      // 6 MUX6 to drive OUT7 of PWM-XBAR
    Uint16 MUX7:1;                      // 7 MUX7 to drive OUT7 of PWM-XBAR
    Uint16 MUX8:1;                      // 8 MUX8 to drive OUT7 of PWM-XBAR
    Uint16 MUX9:1;                      // 9 MUX9 to drive OUT7 of PWM-XBAR
    Uint16 MUX10:1;                     // 10 MUX10 to drive OUT7 of PWM-XBAR
    Uint16 MUX11:1;                     // 11 MUX11 to drive OUT7 of PWM-XBAR
    Uint16 MUX12:1;                     // 12 MUX12 to drive OUT7 of PWM-XBAR
    Uint16 MUX13:1;                     // 13 MUX13 to drive OUT7 of PWM-XBAR
    Uint16 MUX14:1;                     // 14 MUX14 to drive OUT7 of PWM-XBAR
    Uint16 MUX15:1;                     // 15 MUX15 to drive OUT7 of PWM-XBAR
    Uint16 MUX16:1;                     // 16 MUX16 to drive OUT7 of PWM-XBAR
    Uint16 MUX17:1;                     // 17 MUX17 to drive OUT7 of PWM-XBAR
    Uint16 rsvd1:1;                     // 18 Reserved
    Uint16 rsvd2:1;                     // 19 Reserved
    Uint16 rsvd3:1;                     // 20 Reserved
    Uint16 rsvd4:1;                     // 21 Reserved
    Uint16 rsvd5:1;                     // 22 Reserved
    Uint16 rsvd6:1;                     // 23 Reserved
    Uint16 rsvd7:1;                     // 24 Reserved
    Uint16 rsvd8:1;                     // 25 Reserved
    Uint16 rsvd9:1;                     // 26 Reserved
    Uint16 rsvd10:1;                    // 27 Reserved
    Uint16 rsvd11:1;                    // 28 Reserved
    Uint16 rsvd12:1;                    // 29 Reserved
    Uint16 rsvd13:1;                    // 30 Reserved
    Uint16 rsvd14:1;                    // 31 Reserved
};

union TRIP7MUXENABLE_REG {
    Uint32  all;
    struct  TRIP7MUXENABLE_BITS  bit;
};

struct TRIP8MUXENABLE_BITS {            // bits description
    Uint16 MUX0:1;                      // 0 MUX0 to drive OUT8 of PWM-XBAR
    Uint16 MUX1:1;                      // 1 MUX1 to drive OUT8 of PWM-XBAR
    Uint16 MUX2:1;                      // 2 MUX2 to drive OUT8 of PWM-XBAR
    Uint16 MUX3:1;                      // 3 MUX3 to drive OUT8 of PWM-XBAR
    Uint16 MUX4:1;                      // 4 MUX4 to drive OUT8 of PWM-XBAR
    Uint16 MUX5:1;                      // 5 MUX5 to drive OUT8 of PWM-XBAR
    Uint16 MUX6:1;                      // 6 MUX6 to drive OUT8 of PWM-XBAR
    Uint16 MUX7:1;                      // 7 MUX7 to drive OUT8 of PWM-XBAR
    Uint16 MUX8:1;                      // 8 MUX8 to drive OUT8 of PWM-XBAR
    Uint16 MUX9:1;                      // 9 MUX9 to drive OUT8 of PWM-XBAR
    Uint16 MUX10:1;                     // 10 MUX10 to drive OUT8 of PWM-XBAR
    Uint16 MUX11:1;                     // 11 MUX11 to drive OUT8 of PWM-XBAR
    Uint16 MUX12:1;                     // 12 MUX12 to drive OUT8 of PWM-XBAR
    Uint16 MUX13:1;                     // 13 MUX13 to drive OUT8 of PWM-XBAR
    Uint16 MUX14:1;                     // 14 MUX14 to drive OUT8 of PWM-XBAR
    Uint16 MUX15:1;                     // 15 MUX15 to drive OUT8 of PWM-XBAR
    Uint16 MUX16:1;                     // 16 MUX16 to drive OUT8 of PWM-XBAR
    Uint16 MUX17:1;                     // 17 MUX17 to drive OUT8 of PWM-XBAR
    Uint16 rsvd1:1;                     // 18 Reserved
    Uint16 rsvd2:1;                     // 19 Reserved
    Uint16 rsvd3:1;                     // 20 Reserved
    Uint16 rsvd4:1;                     // 21 Reserved
    Uint16 rsvd5:1;                     // 22 Reserved
    Uint16 rsvd6:1;                     // 23 Reserved
    Uint16 rsvd7:1;                     // 24 Reserved
    Uint16 rsvd8:1;                     // 25 Reserved
    Uint16 rsvd9:1;                     // 26 Reserved
    Uint16 rsvd10:1;                    // 27 Reserved
    Uint16 rsvd11:1;                    // 28 Reserved
    Uint16 rsvd12:1;                    // 29 Reserved
    Uint16 rsvd13:1;                    // 30 Reserved
    Uint16 rsvd14:1;                    // 31 Reserved
};

union TRIP8MUXENABLE_REG {
    Uint32  all;
    struct  TRIP8MUXENABLE_BITS  bit;
};

struct TRIPOUTINV_BITS {                // bits description
    Uint16 OUT1:1;                      // 0 Selects polarity for OUT1 of PWM-XBAR
    Uint16 OUT2:1;                      // 1 Selects polarity for OUT2 of PWM-XBAR
    Uint16 OUT3:1;                      // 2 Selects polarity for OUT3 of PWM-XBAR
    Uint16 OUT4:1;                      // 3 Selects polarity for OUT4 of PWM-XBAR
    Uint16 OUT5:1;                      // 4 Selects polarity for OUT5 of PWM-XBAR
    Uint16 OUT6:1;                      // 5 Selects polarity for OUT6 of PWM-XBAR
    Uint16 OUT7:1;                      // 6 Selects polarity for OUT7 of PWM-XBAR
    Uint16 OUT8:1;                      // 7 Selects polarity for OUT8 of PWM-XBAR
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union TRIPOUTINV_REG {
    Uint32  all;
    struct  TRIPOUTINV_BITS  bit;
};

struct TRIPLOCK_BITS {                  // bits description
    Uint16 LOCK:1;                      // 0 Locks the configuration for PWM-XBAR
    Uint16 rsvd1:15;                    // 15:1 Reserved
    Uint16 KEY:16;                      // 31:16 Write protection KEY
};

union TRIPLOCK_REG {
    Uint32  all;
    struct  TRIPLOCK_BITS  bit;
};

struct PWM_XBAR_REGS {
    union   TRIP1MUX0TO15CFG_REG             TRIP1MUX0TO15CFG;             // PWM XBAR Mux Configuration for Output1
    union   TRIP1MUX16TO31CFG_REG            TRIP1MUX16TO31CFG;            // PWM XBAR Mux Configuration for Output1
    union   TRIP2MUX0TO15CFG_REG             TRIP2MUX0TO15CFG;             // PWM XBAR Mux Configuration for Output2
    union   TRIP2MUX16TO31CFG_REG            TRIP2MUX16TO31CFG;            // PWM XBAR Mux Configuration for Output2
    union   TRIP3MUX0TO15CFG_REG             TRIP3MUX0TO15CFG;             // PWM XBAR Mux Configuration for Output3
    union   TRIP3MUX16TO31CFG_REG            TRIP3MUX16TO31CFG;            // PWM XBAR Mux Configuration for Output3
    union   TRIP4MUX0TO15CFG_REG             TRIP4MUX0TO15CFG;             // PWM XBAR Mux Configuration for Output4
    union   TRIP4MUX16TO31CFG_REG            TRIP4MUX16TO31CFG;            // PWM XBAR Mux Configuration for Output4
    union   TRIP5MUX0TO15CFG_REG             TRIP5MUX0TO15CFG;             // PWM XBAR Mux Configuration for Output5
    union   TRIP5MUX16TO31CFG_REG            TRIP5MUX16TO31CFG;            // PWM XBAR Mux Configuration for Output5
    union   TRIP6MUX0TO15CFG_REG             TRIP6MUX0TO15CFG;             // PWM XBAR Mux Configuration for Output6
    union   TRIP6MUX16TO31CFG_REG            TRIP6MUX16TO31CFG;            // PWM XBAR Mux Configuration for Output6
    union   TRIP7MUX0TO15CFG_REG             TRIP7MUX0TO15CFG;             // PWM XBAR Mux Configuration for Output7
    union   TRIP7MUX16TO31CFG_REG            TRIP7MUX16TO31CFG;            // PWM XBAR Mux Configuration for Output7
    union   TRIP8MUX0TO15CFG_REG             TRIP8MUX0TO15CFG;             // PWM XBAR Mux Configuration for Output8
    union   TRIP8MUX16TO31CFG_REG            TRIP8MUX16TO31CFG;            // PWM XBAR Mux Configuration for Output8
    union   TRIP1MUXENABLE_REG               TRIP1MUXENABLE;               // PWM XBAR Mux Enable for Output1
    union   TRIP2MUXENABLE_REG               TRIP2MUXENABLE;               // PWM XBAR Mux Enable for Output2
    union   TRIP3MUXENABLE_REG               TRIP3MUXENABLE;               // PWM XBAR Mux Enable for Output3
    union   TRIP4MUXENABLE_REG               TRIP4MUXENABLE;               // PWM XBAR Mux Enable for Output4
    union   TRIP5MUXENABLE_REG               TRIP5MUXENABLE;               // PWM XBAR Mux Enable for Output5
    union   TRIP6MUXENABLE_REG               TRIP6MUXENABLE;               // PWM XBAR Mux Enable for Output6
    union   TRIP7MUXENABLE_REG               TRIP7MUXENABLE;               // PWM XBAR Mux Enable for Output7
    union   TRIP8MUXENABLE_REG               TRIP8MUXENABLE;               // PWM XBAR Mux Enable for Output8
    Uint16                                   rsvd1[8];                     // Reserved
    union   TRIPOUTINV_REG                   TRIPOUTINV;                   // PWM XBAR Output Inversion Register
    Uint16                                   rsvd2[4];                     // Reserved
    union   TRIPLOCK_REG                     TRIPLOCK;                     // PWM XBAR Configuration Lock register
};

//---------------------------------------------------------------------------
// PWM_XBAR External References & Function Declarations:
//
extern volatile struct PWM_XBAR_REGS PwmXbarRegs;
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
