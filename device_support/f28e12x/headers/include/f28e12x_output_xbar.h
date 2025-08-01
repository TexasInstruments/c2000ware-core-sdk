//###########################################################################
//
// FILE:    f28e12x_output_xbar.h
//
// TITLE:   Definitions for the OUTPUT_XBAR registers.
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

#ifndef F28E12X_OUTPUT_XBAR_H
#define F28E12X_OUTPUT_XBAR_H

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// OUTPUT_XBAR Individual Register Bit Definitions:

struct OUTPUT1MUX0TO15CFG_BITS {        // bits description
    Uint16 MUX0:2;                      // 1:0 Mux0 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX1:2;                      // 3:2 Mux1 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX2:2;                      // 5:4 Mux2 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX3:2;                      // 7:6 Mux3 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX4:2;                      // 9:8 Mux4 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX5:2;                      // 11:10 Mux5 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX6:2;                      // 13:12 Mux6 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX7:2;                      // 15:14 Mux7 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX8:2;                      // 17:16 Mux8 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX9:2;                      // 19:18 Mux9 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX10:2;                     // 21:20 Mux10 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX11:2;                     // 23:22 Mux11 Configuration for OUTPUT1 of OUTPUT-XBAR
    Uint16 rsvd1:2;                     // 25:24 Reserved
    Uint16 rsvd2:2;                     // 27:26 Reserved
    Uint16 rsvd3:2;                     // 29:28 Reserved
    Uint16 rsvd4:2;                     // 31:30 Reserved
};

union OUTPUT1MUX0TO15CFG_REG {
    Uint32  all;
    struct  OUTPUT1MUX0TO15CFG_BITS  bit;
};

struct OUTPUT2MUX0TO15CFG_BITS {        // bits description
    Uint16 MUX0:2;                      // 1:0 Mux0 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX1:2;                      // 3:2 Mux1 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX2:2;                      // 5:4 Mux2 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX3:2;                      // 7:6 Mux3 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX4:2;                      // 9:8 Mux4 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX5:2;                      // 11:10 Mux5 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX6:2;                      // 13:12 Mux6 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX7:2;                      // 15:14 Mux7 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX8:2;                      // 17:16 Mux8 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX9:2;                      // 19:18 Mux9 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX10:2;                     // 21:20 Mux10 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX11:2;                     // 23:22 Mux11 Configuration for OUTPUT2 of OUTPUT-XBAR
    Uint16 rsvd1:2;                     // 25:24 Reserved
    Uint16 rsvd2:2;                     // 27:26 Reserved
    Uint16 rsvd3:2;                     // 29:28 Reserved
    Uint16 rsvd4:2;                     // 31:30 Reserved
};

union OUTPUT2MUX0TO15CFG_REG {
    Uint32  all;
    struct  OUTPUT2MUX0TO15CFG_BITS  bit;
};

struct OUTPUT3MUX0TO15CFG_BITS {        // bits description
    Uint16 MUX0:2;                      // 1:0 Mux0 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX1:2;                      // 3:2 Mux1 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX2:2;                      // 5:4 Mux2 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX3:2;                      // 7:6 Mux3 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX4:2;                      // 9:8 Mux4 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX5:2;                      // 11:10 Mux5 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX6:2;                      // 13:12 Mux6 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX7:2;                      // 15:14 Mux7 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX8:2;                      // 17:16 Mux8 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX9:2;                      // 19:18 Mux9 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX10:2;                     // 21:20 Mux10 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX11:2;                     // 23:22 Mux11 Configuration for OUTPUT3 of OUTPUT-XBAR
    Uint16 rsvd1:2;                     // 25:24 Reserved
    Uint16 rsvd2:2;                     // 27:26 Reserved
    Uint16 rsvd3:2;                     // 29:28 Reserved
    Uint16 rsvd4:2;                     // 31:30 Reserved
};

union OUTPUT3MUX0TO15CFG_REG {
    Uint32  all;
    struct  OUTPUT3MUX0TO15CFG_BITS  bit;
};

struct OUTPUT4MUX0TO15CFG_BITS {        // bits description
    Uint16 MUX0:2;                      // 1:0 Mux0 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX1:2;                      // 3:2 Mux1 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX2:2;                      // 5:4 Mux2 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX3:2;                      // 7:6 Mux3 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX4:2;                      // 9:8 Mux4 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX5:2;                      // 11:10 Mux5 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX6:2;                      // 13:12 Mux6 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX7:2;                      // 15:14 Mux7 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX8:2;                      // 17:16 Mux8 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX9:2;                      // 19:18 Mux9 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX10:2;                     // 21:20 Mux10 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX11:2;                     // 23:22 Mux11 Configuration for OUTPUT4 of OUTPUT-XBAR
    Uint16 rsvd1:2;                     // 25:24 Reserved
    Uint16 rsvd2:2;                     // 27:26 Reserved
    Uint16 rsvd3:2;                     // 29:28 Reserved
    Uint16 rsvd4:2;                     // 31:30 Reserved
};

union OUTPUT4MUX0TO15CFG_REG {
    Uint32  all;
    struct  OUTPUT4MUX0TO15CFG_BITS  bit;
};

struct OUTPUT5MUX0TO15CFG_BITS {        // bits description
    Uint16 MUX0:2;                      // 1:0 Mux0 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX1:2;                      // 3:2 Mux1 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX2:2;                      // 5:4 Mux2 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX3:2;                      // 7:6 Mux3 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX4:2;                      // 9:8 Mux4 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX5:2;                      // 11:10 Mux5 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX6:2;                      // 13:12 Mux6 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX7:2;                      // 15:14 Mux7 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX8:2;                      // 17:16 Mux8 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX9:2;                      // 19:18 Mux9 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX10:2;                     // 21:20 Mux10 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX11:2;                     // 23:22 Mux11 Configuration for OUTPUT5 of OUTPUT-XBAR
    Uint16 rsvd1:2;                     // 25:24 Reserved
    Uint16 rsvd2:2;                     // 27:26 Reserved
    Uint16 rsvd3:2;                     // 29:28 Reserved
    Uint16 rsvd4:2;                     // 31:30 Reserved
};

union OUTPUT5MUX0TO15CFG_REG {
    Uint32  all;
    struct  OUTPUT5MUX0TO15CFG_BITS  bit;
};

struct OUTPUT6MUX0TO15CFG_BITS {        // bits description
    Uint16 MUX0:2;                      // 1:0 Mux0 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX1:2;                      // 3:2 Mux1 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX2:2;                      // 5:4 Mux2 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX3:2;                      // 7:6 Mux3 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX4:2;                      // 9:8 Mux4 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX5:2;                      // 11:10 Mux5 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX6:2;                      // 13:12 Mux6 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX7:2;                      // 15:14 Mux7 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX8:2;                      // 17:16 Mux8 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX9:2;                      // 19:18 Mux9 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX10:2;                     // 21:20 Mux10 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX11:2;                     // 23:22 Mux11 Configuration for OUTPUT6 of OUTPUT-XBAR
    Uint16 rsvd1:2;                     // 25:24 Reserved
    Uint16 rsvd2:2;                     // 27:26 Reserved
    Uint16 rsvd3:2;                     // 29:28 Reserved
    Uint16 rsvd4:2;                     // 31:30 Reserved
};

union OUTPUT6MUX0TO15CFG_REG {
    Uint32  all;
    struct  OUTPUT6MUX0TO15CFG_BITS  bit;
};

struct OUTPUT7MUX0TO15CFG_BITS {        // bits description
    Uint16 MUX0:2;                      // 1:0 Mux0 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX1:2;                      // 3:2 Mux1 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX2:2;                      // 5:4 Mux2 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX3:2;                      // 7:6 Mux3 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX4:2;                      // 9:8 Mux4 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX5:2;                      // 11:10 Mux5 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX6:2;                      // 13:12 Mux6 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX7:2;                      // 15:14 Mux7 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX8:2;                      // 17:16 Mux8 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX9:2;                      // 19:18 Mux9 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX10:2;                     // 21:20 Mux10 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX11:2;                     // 23:22 Mux11 Configuration for OUTPUT7 of OUTPUT-XBAR
    Uint16 rsvd1:2;                     // 25:24 Reserved
    Uint16 rsvd2:2;                     // 27:26 Reserved
    Uint16 rsvd3:2;                     // 29:28 Reserved
    Uint16 rsvd4:2;                     // 31:30 Reserved
};

union OUTPUT7MUX0TO15CFG_REG {
    Uint32  all;
    struct  OUTPUT7MUX0TO15CFG_BITS  bit;
};

struct OUTPUT8MUX0TO15CFG_BITS {        // bits description
    Uint16 MUX0:2;                      // 1:0 Mux0 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX1:2;                      // 3:2 Mux1 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX2:2;                      // 5:4 Mux2 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX3:2;                      // 7:6 Mux3 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX4:2;                      // 9:8 Mux4 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX5:2;                      // 11:10 Mux5 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX6:2;                      // 13:12 Mux6 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX7:2;                      // 15:14 Mux7 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX8:2;                      // 17:16 Mux8 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX9:2;                      // 19:18 Mux9 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX10:2;                     // 21:20 Mux10 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX11:2;                     // 23:22 Mux11 Configuration for OUTPUT8 of OUTPUT-XBAR
    Uint16 rsvd1:2;                     // 25:24 Reserved
    Uint16 rsvd2:2;                     // 27:26 Reserved
    Uint16 rsvd3:2;                     // 29:28 Reserved
    Uint16 rsvd4:2;                     // 31:30 Reserved
};

union OUTPUT8MUX0TO15CFG_REG {
    Uint32  all;
    struct  OUTPUT8MUX0TO15CFG_BITS  bit;
};

struct OUTPUT1MUXENABLE_BITS {          // bits description
    Uint16 MUX0:1;                      // 0 Mux0 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX1:1;                      // 1 Mux1 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX2:1;                      // 2 Mux2 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX3:1;                      // 3 Mux3 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX4:1;                      // 4 Mux4 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX5:1;                      // 5 Mux5 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX6:1;                      // 6 Mux6 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX7:1;                      // 7 Mux7 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX8:1;                      // 8 Mux8 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX9:1;                      // 9 Mux9 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX10:1;                     // 10 Mux10 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 MUX11:1;                     // 11 Mux11 to drive OUTPUT1 of OUTPUT-XBAR
    Uint16 rsvd1:1;                     // 12 Reserved
    Uint16 rsvd2:1;                     // 13 Reserved
    Uint16 rsvd3:1;                     // 14 Reserved
    Uint16 rsvd4:1;                     // 15 Reserved
    Uint16 rsvd5:1;                     // 16 Reserved
    Uint16 rsvd6:1;                     // 17 Reserved
    Uint16 rsvd7:1;                     // 18 Reserved
    Uint16 rsvd8:1;                     // 19 Reserved
    Uint16 rsvd9:1;                     // 20 Reserved
    Uint16 rsvd10:1;                    // 21 Reserved
    Uint16 rsvd11:1;                    // 22 Reserved
    Uint16 rsvd12:1;                    // 23 Reserved
    Uint16 rsvd13:1;                    // 24 Reserved
    Uint16 rsvd14:1;                    // 25 Reserved
    Uint16 rsvd15:1;                    // 26 Reserved
    Uint16 rsvd16:1;                    // 27 Reserved
    Uint16 rsvd17:1;                    // 28 Reserved
    Uint16 rsvd18:1;                    // 29 Reserved
    Uint16 rsvd19:1;                    // 30 Reserved
    Uint16 rsvd20:1;                    // 31 Reserved
};

union OUTPUT1MUXENABLE_REG {
    Uint32  all;
    struct  OUTPUT1MUXENABLE_BITS  bit;
};

struct OUTPUT2MUXENABLE_BITS {          // bits description
    Uint16 MUX0:1;                      // 0 Mux0 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX1:1;                      // 1 Mux1 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX2:1;                      // 2 Mux2 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX3:1;                      // 3 Mux3 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX4:1;                      // 4 Mux4 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX5:1;                      // 5 Mux5 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX6:1;                      // 6 Mux6 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX7:1;                      // 7 Mux7 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX8:1;                      // 8 Mux8 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX9:1;                      // 9 Mux9 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX10:1;                     // 10 Mux10 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 MUX11:1;                     // 11 Mux11 to drive OUTPUT2 of OUTPUT-XBAR
    Uint16 rsvd1:1;                     // 12 Reserved
    Uint16 rsvd2:1;                     // 13 Reserved
    Uint16 rsvd3:1;                     // 14 Reserved
    Uint16 rsvd4:1;                     // 15 Reserved
    Uint16 rsvd5:1;                     // 16 Reserved
    Uint16 rsvd6:1;                     // 17 Reserved
    Uint16 rsvd7:1;                     // 18 Reserved
    Uint16 rsvd8:1;                     // 19 Reserved
    Uint16 rsvd9:1;                     // 20 Reserved
    Uint16 rsvd10:1;                    // 21 Reserved
    Uint16 rsvd11:1;                    // 22 Reserved
    Uint16 rsvd12:1;                    // 23 Reserved
    Uint16 rsvd13:1;                    // 24 Reserved
    Uint16 rsvd14:1;                    // 25 Reserved
    Uint16 rsvd15:1;                    // 26 Reserved
    Uint16 rsvd16:1;                    // 27 Reserved
    Uint16 rsvd17:1;                    // 28 Reserved
    Uint16 rsvd18:1;                    // 29 Reserved
    Uint16 rsvd19:1;                    // 30 Reserved
    Uint16 rsvd20:1;                    // 31 Reserved
};

union OUTPUT2MUXENABLE_REG {
    Uint32  all;
    struct  OUTPUT2MUXENABLE_BITS  bit;
};

struct OUTPUT3MUXENABLE_BITS {          // bits description
    Uint16 MUX0:1;                      // 0 Mux0 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX1:1;                      // 1 Mux1 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX2:1;                      // 2 Mux2 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX3:1;                      // 3 Mux3 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX4:1;                      // 4 Mux4 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX5:1;                      // 5 Mux5 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX6:1;                      // 6 Mux6 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX7:1;                      // 7 Mux7 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX8:1;                      // 8 Mux8 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX9:1;                      // 9 Mux9 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX10:1;                     // 10 Mux10 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 MUX11:1;                     // 11 Mux11 to drive OUTPUT3 of OUTPUT-XBAR
    Uint16 rsvd1:1;                     // 12 Reserved
    Uint16 rsvd2:1;                     // 13 Reserved
    Uint16 rsvd3:1;                     // 14 Reserved
    Uint16 rsvd4:1;                     // 15 Reserved
    Uint16 rsvd5:1;                     // 16 Reserved
    Uint16 rsvd6:1;                     // 17 Reserved
    Uint16 rsvd7:1;                     // 18 Reserved
    Uint16 rsvd8:1;                     // 19 Reserved
    Uint16 rsvd9:1;                     // 20 Reserved
    Uint16 rsvd10:1;                    // 21 Reserved
    Uint16 rsvd11:1;                    // 22 Reserved
    Uint16 rsvd12:1;                    // 23 Reserved
    Uint16 rsvd13:1;                    // 24 Reserved
    Uint16 rsvd14:1;                    // 25 Reserved
    Uint16 rsvd15:1;                    // 26 Reserved
    Uint16 rsvd16:1;                    // 27 Reserved
    Uint16 rsvd17:1;                    // 28 Reserved
    Uint16 rsvd18:1;                    // 29 Reserved
    Uint16 rsvd19:1;                    // 30 Reserved
    Uint16 rsvd20:1;                    // 31 Reserved
};

union OUTPUT3MUXENABLE_REG {
    Uint32  all;
    struct  OUTPUT3MUXENABLE_BITS  bit;
};

struct OUTPUT4MUXENABLE_BITS {          // bits description
    Uint16 MUX0:1;                      // 0 Mux0 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX1:1;                      // 1 Mux1 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX2:1;                      // 2 Mux2 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX3:1;                      // 3 Mux3 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX4:1;                      // 4 Mux4 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX5:1;                      // 5 Mux5 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX6:1;                      // 6 Mux6 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX7:1;                      // 7 Mux7 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX8:1;                      // 8 Mux8 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX9:1;                      // 9 Mux9 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX10:1;                     // 10 Mux10 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 MUX11:1;                     // 11 Mux11 to drive OUTPUT4 of OUTPUT-XBAR
    Uint16 rsvd1:1;                     // 12 Reserved
    Uint16 rsvd2:1;                     // 13 Reserved
    Uint16 rsvd3:1;                     // 14 Reserved
    Uint16 rsvd4:1;                     // 15 Reserved
    Uint16 rsvd5:1;                     // 16 Reserved
    Uint16 rsvd6:1;                     // 17 Reserved
    Uint16 rsvd7:1;                     // 18 Reserved
    Uint16 rsvd8:1;                     // 19 Reserved
    Uint16 rsvd9:1;                     // 20 Reserved
    Uint16 rsvd10:1;                    // 21 Reserved
    Uint16 rsvd11:1;                    // 22 Reserved
    Uint16 rsvd12:1;                    // 23 Reserved
    Uint16 rsvd13:1;                    // 24 Reserved
    Uint16 rsvd14:1;                    // 25 Reserved
    Uint16 rsvd15:1;                    // 26 Reserved
    Uint16 rsvd16:1;                    // 27 Reserved
    Uint16 rsvd17:1;                    // 28 Reserved
    Uint16 rsvd18:1;                    // 29 Reserved
    Uint16 rsvd19:1;                    // 30 Reserved
    Uint16 rsvd20:1;                    // 31 Reserved
};

union OUTPUT4MUXENABLE_REG {
    Uint32  all;
    struct  OUTPUT4MUXENABLE_BITS  bit;
};

struct OUTPUT5MUXENABLE_BITS {          // bits description
    Uint16 MUX0:1;                      // 0 Mux0 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX1:1;                      // 1 Mux1 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX2:1;                      // 2 Mux2 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX3:1;                      // 3 Mux3 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX4:1;                      // 4 Mux4 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX5:1;                      // 5 Mux5 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX6:1;                      // 6 Mux6 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX7:1;                      // 7 Mux7 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX8:1;                      // 8 Mux8 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX9:1;                      // 9 Mux9 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX10:1;                     // 10 Mux10 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 MUX11:1;                     // 11 Mux11 to drive OUTPUT5 of OUTPUT-XBAR
    Uint16 rsvd1:1;                     // 12 Reserved
    Uint16 rsvd2:1;                     // 13 Reserved
    Uint16 rsvd3:1;                     // 14 Reserved
    Uint16 rsvd4:1;                     // 15 Reserved
    Uint16 rsvd5:1;                     // 16 Reserved
    Uint16 rsvd6:1;                     // 17 Reserved
    Uint16 rsvd7:1;                     // 18 Reserved
    Uint16 rsvd8:1;                     // 19 Reserved
    Uint16 rsvd9:1;                     // 20 Reserved
    Uint16 rsvd10:1;                    // 21 Reserved
    Uint16 rsvd11:1;                    // 22 Reserved
    Uint16 rsvd12:1;                    // 23 Reserved
    Uint16 rsvd13:1;                    // 24 Reserved
    Uint16 rsvd14:1;                    // 25 Reserved
    Uint16 rsvd15:1;                    // 26 Reserved
    Uint16 rsvd16:1;                    // 27 Reserved
    Uint16 rsvd17:1;                    // 28 Reserved
    Uint16 rsvd18:1;                    // 29 Reserved
    Uint16 rsvd19:1;                    // 30 Reserved
    Uint16 rsvd20:1;                    // 31 Reserved
};

union OUTPUT5MUXENABLE_REG {
    Uint32  all;
    struct  OUTPUT5MUXENABLE_BITS  bit;
};

struct OUTPUT6MUXENABLE_BITS {          // bits description
    Uint16 MUX0:1;                      // 0 Mux0 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX1:1;                      // 1 Mux1 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX2:1;                      // 2 Mux2 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX3:1;                      // 3 Mux3 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX4:1;                      // 4 Mux4 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX5:1;                      // 5 Mux5 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX6:1;                      // 6 Mux6 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX7:1;                      // 7 Mux7 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX8:1;                      // 8 Mux8 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX9:1;                      // 9 Mux9 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX10:1;                     // 10 Mux10 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 MUX11:1;                     // 11 Mux11 to drive OUTPUT6 of OUTPUT-XBAR
    Uint16 rsvd1:1;                     // 12 Reserved
    Uint16 rsvd2:1;                     // 13 Reserved
    Uint16 rsvd3:1;                     // 14 Reserved
    Uint16 rsvd4:1;                     // 15 Reserved
    Uint16 rsvd5:1;                     // 16 Reserved
    Uint16 rsvd6:1;                     // 17 Reserved
    Uint16 rsvd7:1;                     // 18 Reserved
    Uint16 rsvd8:1;                     // 19 Reserved
    Uint16 rsvd9:1;                     // 20 Reserved
    Uint16 rsvd10:1;                    // 21 Reserved
    Uint16 rsvd11:1;                    // 22 Reserved
    Uint16 rsvd12:1;                    // 23 Reserved
    Uint16 rsvd13:1;                    // 24 Reserved
    Uint16 rsvd14:1;                    // 25 Reserved
    Uint16 rsvd15:1;                    // 26 Reserved
    Uint16 rsvd16:1;                    // 27 Reserved
    Uint16 rsvd17:1;                    // 28 Reserved
    Uint16 rsvd18:1;                    // 29 Reserved
    Uint16 rsvd19:1;                    // 30 Reserved
    Uint16 rsvd20:1;                    // 31 Reserved
};

union OUTPUT6MUXENABLE_REG {
    Uint32  all;
    struct  OUTPUT6MUXENABLE_BITS  bit;
};

struct OUTPUT7MUXENABLE_BITS {          // bits description
    Uint16 MUX0:1;                      // 0 Mux0 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX1:1;                      // 1 Mux1 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX2:1;                      // 2 Mux2 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX3:1;                      // 3 Mux3 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX4:1;                      // 4 Mux4 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX5:1;                      // 5 Mux5 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX6:1;                      // 6 Mux6 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX7:1;                      // 7 Mux7 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX8:1;                      // 8 Mux8 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX9:1;                      // 9 Mux9 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX10:1;                     // 10 Mux10 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 MUX11:1;                     // 11 Mux11 to drive OUTPUT7 of OUTPUT-XBAR
    Uint16 rsvd1:1;                     // 12 Reserved
    Uint16 rsvd2:1;                     // 13 Reserved
    Uint16 rsvd3:1;                     // 14 Reserved
    Uint16 rsvd4:1;                     // 15 Reserved
    Uint16 rsvd5:1;                     // 16 Reserved
    Uint16 rsvd6:1;                     // 17 Reserved
    Uint16 rsvd7:1;                     // 18 Reserved
    Uint16 rsvd8:1;                     // 19 Reserved
    Uint16 rsvd9:1;                     // 20 Reserved
    Uint16 rsvd10:1;                    // 21 Reserved
    Uint16 rsvd11:1;                    // 22 Reserved
    Uint16 rsvd12:1;                    // 23 Reserved
    Uint16 rsvd13:1;                    // 24 Reserved
    Uint16 rsvd14:1;                    // 25 Reserved
    Uint16 rsvd15:1;                    // 26 Reserved
    Uint16 rsvd16:1;                    // 27 Reserved
    Uint16 rsvd17:1;                    // 28 Reserved
    Uint16 rsvd18:1;                    // 29 Reserved
    Uint16 rsvd19:1;                    // 30 Reserved
    Uint16 rsvd20:1;                    // 31 Reserved
};

union OUTPUT7MUXENABLE_REG {
    Uint32  all;
    struct  OUTPUT7MUXENABLE_BITS  bit;
};

struct OUTPUT8MUXENABLE_BITS {          // bits description
    Uint16 MUX0:1;                      // 0 Mux0 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX1:1;                      // 1 Mux1 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX2:1;                      // 2 Mux2 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX3:1;                      // 3 Mux3 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX4:1;                      // 4 Mux4 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX5:1;                      // 5 Mux5 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX6:1;                      // 6 Mux6 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX7:1;                      // 7 Mux7 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX8:1;                      // 8 Mux8 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX9:1;                      // 9 Mux9 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX10:1;                     // 10 Mux10 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 MUX11:1;                     // 11 Mux11 to drive OUTPUT8 of OUTPUT-XBAR
    Uint16 rsvd1:1;                     // 12 Reserved
    Uint16 rsvd2:1;                     // 13 Reserved
    Uint16 rsvd3:1;                     // 14 Reserved
    Uint16 rsvd4:1;                     // 15 Reserved
    Uint16 rsvd5:1;                     // 16 Reserved
    Uint16 rsvd6:1;                     // 17 Reserved
    Uint16 rsvd7:1;                     // 18 Reserved
    Uint16 rsvd8:1;                     // 19 Reserved
    Uint16 rsvd9:1;                     // 20 Reserved
    Uint16 rsvd10:1;                    // 21 Reserved
    Uint16 rsvd11:1;                    // 22 Reserved
    Uint16 rsvd12:1;                    // 23 Reserved
    Uint16 rsvd13:1;                    // 24 Reserved
    Uint16 rsvd14:1;                    // 25 Reserved
    Uint16 rsvd15:1;                    // 26 Reserved
    Uint16 rsvd16:1;                    // 27 Reserved
    Uint16 rsvd17:1;                    // 28 Reserved
    Uint16 rsvd18:1;                    // 29 Reserved
    Uint16 rsvd19:1;                    // 30 Reserved
    Uint16 rsvd20:1;                    // 31 Reserved
};

union OUTPUT8MUXENABLE_REG {
    Uint32  all;
    struct  OUTPUT8MUXENABLE_BITS  bit;
};

struct OUTPUTLATCH_BITS {               // bits description
    Uint16 OUTPUT1:1;                   // 0 Records the OUTPUT1 of OUTPUT-XBAR
    Uint16 OUTPUT2:1;                   // 1 Records the OUTPUT2 of OUTPUT-XBAR
    Uint16 OUTPUT3:1;                   // 2 Records the OUTPUT3 of OUTPUT-XBAR
    Uint16 OUTPUT4:1;                   // 3 Records the OUTPUT4 of OUTPUT-XBAR
    Uint16 OUTPUT5:1;                   // 4 Records the OUTPUT5 of OUTPUT-XBAR
    Uint16 OUTPUT6:1;                   // 5 Records the OUTPUT6 of OUTPUT-XBAR
    Uint16 OUTPUT7:1;                   // 6 Records the OUTPUT7 of OUTPUT-XBAR
    Uint16 OUTPUT8:1;                   // 7 Records the OUTPUT8 of OUTPUT-XBAR
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union OUTPUTLATCH_REG {
    Uint32  all;
    struct  OUTPUTLATCH_BITS  bit;
};

struct OUTPUTLATCHCLR_BITS {            // bits description
    Uint16 OUTPUT1:1;                   // 0 Clears the Output-Latch for OUTPUT1 of OUTPUT-XBAR
    Uint16 OUTPUT2:1;                   // 1 Clears the Output-Latch for OUTPUT2 of OUTPUT-XBAR
    Uint16 OUTPUT3:1;                   // 2 Clears the Output-Latch for OUTPUT3 of OUTPUT-XBAR
    Uint16 OUTPUT4:1;                   // 3 Clears the Output-Latch for OUTPUT4 of OUTPUT-XBAR
    Uint16 OUTPUT5:1;                   // 4 Clears the Output-Latch for OUTPUT5 of OUTPUT-XBAR
    Uint16 OUTPUT6:1;                   // 5 Clears the Output-Latch for OUTPUT6 of OUTPUT-XBAR
    Uint16 OUTPUT7:1;                   // 6 Clears the Output-Latch for OUTPUT7 of OUTPUT-XBAR
    Uint16 OUTPUT8:1;                   // 7 Clears the Output-Latch for OUTPUT8 of OUTPUT-XBAR
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union OUTPUTLATCHCLR_REG {
    Uint32  all;
    struct  OUTPUTLATCHCLR_BITS  bit;
};

struct OUTPUTLATCHFRC_BITS {            // bits description
    Uint16 OUTPUT1:1;                   // 0 Sets the Output-Latch for OUTPUT1 of OUTPUT-XBAR
    Uint16 OUTPUT2:1;                   // 1 Sets the Output-Latch for OUTPUT2 of OUTPUT-XBAR
    Uint16 OUTPUT3:1;                   // 2 Sets the Output-Latch for OUTPUT3 of OUTPUT-XBAR
    Uint16 OUTPUT4:1;                   // 3 Sets the Output-Latch for OUTPUT4 of OUTPUT-XBAR
    Uint16 OUTPUT5:1;                   // 4 Sets the Output-Latch for OUTPUT5 of OUTPUT-XBAR
    Uint16 OUTPUT6:1;                   // 5 Sets the Output-Latch for OUTPUT6 of OUTPUT-XBAR
    Uint16 OUTPUT7:1;                   // 6 Sets the Output-Latch for OUTPUT7 of OUTPUT-XBAR
    Uint16 OUTPUT8:1;                   // 7 Sets the Output-Latch for OUTPUT8 of OUTPUT-XBAR
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union OUTPUTLATCHFRC_REG {
    Uint32  all;
    struct  OUTPUTLATCHFRC_BITS  bit;
};

struct OUTPUTLATCHENABLE_BITS {         // bits description
    Uint16 OUTPUT1:1;                   // 0 Selects the output latch to drive OUTPUT1 for OUTPUT-XBAR
    Uint16 OUTPUT2:1;                   // 1 Selects the output latch to drive OUTPUT2 for OUTPUT-XBAR
    Uint16 OUTPUT3:1;                   // 2 Selects the output latch to drive OUTPUT3 for OUTPUT-XBAR
    Uint16 OUTPUT4:1;                   // 3 Selects the output latch to drive OUTPUT4 for OUTPUT-XBAR
    Uint16 OUTPUT5:1;                   // 4 Selects the output latch to drive OUTPUT5 for OUTPUT-XBAR
    Uint16 OUTPUT6:1;                   // 5 Selects the output latch to drive OUTPUT6 for OUTPUT-XBAR
    Uint16 OUTPUT7:1;                   // 6 Selects the output latch to drive OUTPUT7 for OUTPUT-XBAR
    Uint16 OUTPUT8:1;                   // 7 Selects the output latch to drive OUTPUT8 for OUTPUT-XBAR
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union OUTPUTLATCHENABLE_REG {
    Uint32  all;
    struct  OUTPUTLATCHENABLE_BITS  bit;
};

struct OUTPUTINV_BITS {                 // bits description
    Uint16 OUTPUT1:1;                   // 0 Selects polarity for OUTPUT1 of OUTPUT-XBAR
    Uint16 OUTPUT2:1;                   // 1 Selects polarity for OUTPUT2 of OUTPUT-XBAR
    Uint16 OUTPUT3:1;                   // 2 Selects polarity for OUTPUT3 of OUTPUT-XBAR
    Uint16 OUTPUT4:1;                   // 3 Selects polarity for OUTPUT4 of OUTPUT-XBAR
    Uint16 OUTPUT5:1;                   // 4 Selects polarity for OUTPUT5 of OUTPUT-XBAR
    Uint16 OUTPUT6:1;                   // 5 Selects polarity for OUTPUT6 of OUTPUT-XBAR
    Uint16 OUTPUT7:1;                   // 6 Selects polarity for OUTPUT7 of OUTPUT-XBAR
    Uint16 OUTPUT8:1;                   // 7 Selects polarity for OUTPUT8 of OUTPUT-XBAR
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union OUTPUTINV_REG {
    Uint32  all;
    struct  OUTPUTINV_BITS  bit;
};

struct OUTPUTLOCK_BITS {                // bits description
    Uint16 LOCK:1;                      // 0 Locks the configuration for OUTPUT-XBAR
    Uint16 rsvd1:15;                    // 15:1 Reserved
    Uint16 KEY:16;                      // 31:16 Write Protection KEY
};

union OUTPUTLOCK_REG {
    Uint32  all;
    struct  OUTPUTLOCK_BITS  bit;
};

struct OUTPUT_XBAR_REGS {
    union   OUTPUT1MUX0TO15CFG_REG           OUTPUT1MUX0TO15CFG;           // Output X-BAR Mux Configuration for Output 1
    Uint16                                   rsvd1[2];                     // Reserved
    union   OUTPUT2MUX0TO15CFG_REG           OUTPUT2MUX0TO15CFG;           // Output X-BAR Mux Configuration for Output 2
    Uint16                                   rsvd2[2];                     // Reserved
    union   OUTPUT3MUX0TO15CFG_REG           OUTPUT3MUX0TO15CFG;           // Output X-BAR Mux Configuration for Output 3
    Uint16                                   rsvd3[2];                     // Reserved
    union   OUTPUT4MUX0TO15CFG_REG           OUTPUT4MUX0TO15CFG;           // Output X-BAR Mux Configuration for Output 4
    Uint16                                   rsvd4[2];                     // Reserved
    union   OUTPUT5MUX0TO15CFG_REG           OUTPUT5MUX0TO15CFG;           // Output X-BAR Mux Configuration for Output 5
    Uint16                                   rsvd5[2];                     // Reserved
    union   OUTPUT6MUX0TO15CFG_REG           OUTPUT6MUX0TO15CFG;           // Output X-BAR Mux Configuration for Output 6
    Uint16                                   rsvd6[2];                     // Reserved
    union   OUTPUT7MUX0TO15CFG_REG           OUTPUT7MUX0TO15CFG;           // Output X-BAR Mux Configuration for Output 7
    Uint16                                   rsvd7[2];                     // Reserved
    union   OUTPUT8MUX0TO15CFG_REG           OUTPUT8MUX0TO15CFG;           // Output X-BAR Mux Configuration for Output 8
    Uint16                                   rsvd8[2];                     // Reserved
    union   OUTPUT1MUXENABLE_REG             OUTPUT1MUXENABLE;             // Output X-BAR Mux Enable  for Output 1
    union   OUTPUT2MUXENABLE_REG             OUTPUT2MUXENABLE;             // Output X-BAR Mux Enable  for Output 2
    union   OUTPUT3MUXENABLE_REG             OUTPUT3MUXENABLE;             // Output X-BAR Mux Enable  for Output 3
    union   OUTPUT4MUXENABLE_REG             OUTPUT4MUXENABLE;             // Output X-BAR Mux Enable  for Output 4
    union   OUTPUT5MUXENABLE_REG             OUTPUT5MUXENABLE;             // Output X-BAR Mux Enable  for Output 5
    union   OUTPUT6MUXENABLE_REG             OUTPUT6MUXENABLE;             // Output X-BAR Mux Enable  for Output 6
    union   OUTPUT7MUXENABLE_REG             OUTPUT7MUXENABLE;             // Output X-BAR Mux Enable  for Output 7
    union   OUTPUT8MUXENABLE_REG             OUTPUT8MUXENABLE;             // Output X-BAR Mux Enable  for Output 8
    union   OUTPUTLATCH_REG                  OUTPUTLATCH;                  // Output X-BAR Output Latch
    union   OUTPUTLATCHCLR_REG               OUTPUTLATCHCLR;               // Output X-BAR Output Latch Clear
    union   OUTPUTLATCHFRC_REG               OUTPUTLATCHFRC;               // Output X-BAR Output Latch Clear
    union   OUTPUTLATCHENABLE_REG            OUTPUTLATCHENABLE;            // Output X-BAR Output Latch Enable
    union   OUTPUTINV_REG                    OUTPUTINV;                    // Output X-BAR Output Inversion
    Uint16                                   rsvd9[4];                     // Reserved
    union   OUTPUTLOCK_REG                   OUTPUTLOCK;                   // Output X-BAR Configuration Lock register
};

//---------------------------------------------------------------------------
// OUTPUT_XBAR External References & Function Declarations:
//
extern volatile struct OUTPUT_XBAR_REGS OutputXbarRegs;
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
