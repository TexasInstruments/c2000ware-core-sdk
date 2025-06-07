//###########################################################################
//
// FILE:    f280013x_gpio.h
//
// TITLE:   Definitions for the GPIO registers.
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

#ifndef F280013X_GPIO_H
#define F280013X_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// GPIO Individual Register Bit Definitions:

struct GPACTRL_BITS {                   // bits description
    Uint16 QUALPRD0:8;                  // 7:0 Qualification sampling period for GPIO0 to GPIO7
    Uint16 QUALPRD1:8;                  // 15:8 Qualification sampling period for GPIO8 to GPIO15
    Uint16 QUALPRD2:8;                  // 23:16 Qualification sampling period for GPIO16 to GPIO23
    Uint16 QUALPRD3:8;                  // 31:24 Qualification sampling period for GPIO24 to GPIO31
};

union GPACTRL_REG {
    Uint32  all;
    struct  GPACTRL_BITS  bit;
};

struct GPAQSEL1_BITS {                  // bits description
    Uint16 GPIO0:2;                     // 1:0 Select input qualification type for GPIO0
    Uint16 GPIO1:2;                     // 3:2 Select input qualification type for GPIO1
    Uint16 GPIO2:2;                     // 5:4 Select input qualification type for GPIO2
    Uint16 GPIO3:2;                     // 7:6 Select input qualification type for GPIO3
    Uint16 GPIO4:2;                     // 9:8 Select input qualification type for GPIO4
    Uint16 GPIO5:2;                     // 11:10 Select input qualification type for GPIO5
    Uint16 GPIO6:2;                     // 13:12 Select input qualification type for GPIO6
    Uint16 GPIO7:2;                     // 15:14 Select input qualification type for GPIO7
    Uint16 GPIO8:2;                     // 17:16 Select input qualification type for GPIO8
    Uint16 GPIO9:2;                     // 19:18 Select input qualification type for GPIO9
    Uint16 GPIO10:2;                    // 21:20 Select input qualification type for GPIO10
    Uint16 GPIO11:2;                    // 23:22 Select input qualification type for GPIO11
    Uint16 GPIO12:2;                    // 25:24 Select input qualification type for GPIO12
    Uint16 GPIO13:2;                    // 27:26 Select input qualification type for GPIO13
    Uint16 rsvd1:2;                     // 29:28 Reserved
    Uint16 rsvd2:2;                     // 31:30 Reserved
};

union GPAQSEL1_REG {
    Uint32  all;
    struct  GPAQSEL1_BITS  bit;
};

struct GPAQSEL2_BITS {                  // bits description
    Uint16 GPIO16:2;                    // 1:0 Select input qualification type for GPIO16
    Uint16 GPIO17:2;                    // 3:2 Select input qualification type for GPIO17
    Uint16 GPIO18:2;                    // 5:4 Select input qualification type for GPIO18
    Uint16 GPIO19:2;                    // 7:6 Select input qualification type for GPIO19
    Uint16 GPIO20:2;                    // 9:8 Select input qualification type for GPIO20
    Uint16 GPIO21:2;                    // 11:10 Select input qualification type for GPIO21
    Uint16 GPIO22:2;                    // 13:12 Select input qualification type for GPIO22
    Uint16 GPIO23:2;                    // 15:14 Select input qualification type for GPIO23
    Uint16 GPIO24:2;                    // 17:16 Select input qualification type for GPIO24
    Uint16 rsvd1:2;                     // 19:18 Reserved
    Uint16 rsvd2:2;                     // 21:20 Reserved
    Uint16 rsvd3:2;                     // 23:22 Reserved
    Uint16 GPIO28:2;                    // 25:24 Select input qualification type for GPIO28
    Uint16 GPIO29:2;                    // 27:26 Select input qualification type for GPIO29
    Uint16 rsvd4:2;                     // 29:28 Reserved
    Uint16 rsvd5:2;                     // 31:30 Reserved
};

union GPAQSEL2_REG {
    Uint32  all;
    struct  GPAQSEL2_BITS  bit;
};

struct GPAMUX1_BITS {                   // bits description
    Uint16 GPIO0:2;                     // 1:0 Defines pin-muxing selection for GPIO0
    Uint16 GPIO1:2;                     // 3:2 Defines pin-muxing selection for GPIO1
    Uint16 GPIO2:2;                     // 5:4 Defines pin-muxing selection for GPIO2
    Uint16 GPIO3:2;                     // 7:6 Defines pin-muxing selection for GPIO3
    Uint16 GPIO4:2;                     // 9:8 Defines pin-muxing selection for GPIO4
    Uint16 GPIO5:2;                     // 11:10 Defines pin-muxing selection for GPIO5
    Uint16 GPIO6:2;                     // 13:12 Defines pin-muxing selection for GPIO6
    Uint16 GPIO7:2;                     // 15:14 Defines pin-muxing selection for GPIO7
    Uint16 GPIO8:2;                     // 17:16 Defines pin-muxing selection for GPIO8
    Uint16 GPIO9:2;                     // 19:18 Defines pin-muxing selection for GPIO9
    Uint16 GPIO10:2;                    // 21:20 Defines pin-muxing selection for GPIO10
    Uint16 GPIO11:2;                    // 23:22 Defines pin-muxing selection for GPIO11
    Uint16 GPIO12:2;                    // 25:24 Defines pin-muxing selection for GPIO12
    Uint16 GPIO13:2;                    // 27:26 Defines pin-muxing selection for GPIO13
    Uint16 rsvd1:2;                     // 29:28 Reserved
    Uint16 rsvd2:2;                     // 31:30 Reserved
};

union GPAMUX1_REG {
    Uint32  all;
    struct  GPAMUX1_BITS  bit;
};

struct GPAMUX2_BITS {                   // bits description
    Uint16 GPIO16:2;                    // 1:0 Defines pin-muxing selection for GPIO16
    Uint16 GPIO17:2;                    // 3:2 Defines pin-muxing selection for GPIO17
    Uint16 GPIO18:2;                    // 5:4 Defines pin-muxing selection for GPIO18
    Uint16 GPIO19:2;                    // 7:6 Defines pin-muxing selection for GPIO19
    Uint16 GPIO20:2;                    // 9:8 Defines pin-muxing selection for GPIO20
    Uint16 GPIO21:2;                    // 11:10 Defines pin-muxing selection for GPIO21
    Uint16 GPIO22:2;                    // 13:12 Defines pin-muxing selection for GPIO22
    Uint16 GPIO23:2;                    // 15:14 Defines pin-muxing selection for GPIO23
    Uint16 GPIO24:2;                    // 17:16 Defines pin-muxing selection for GPIO24
    Uint16 rsvd1:2;                     // 19:18 Reserved
    Uint16 rsvd2:2;                     // 21:20 Reserved
    Uint16 rsvd3:2;                     // 23:22 Reserved
    Uint16 GPIO28:2;                    // 25:24 Defines pin-muxing selection for GPIO28
    Uint16 GPIO29:2;                    // 27:26 Defines pin-muxing selection for GPIO29
    Uint16 rsvd4:2;                     // 29:28 Reserved
    Uint16 rsvd5:2;                     // 31:30 Reserved
};

union GPAMUX2_REG {
    Uint32  all;
    struct  GPAMUX2_BITS  bit;
};

struct GPADIR_BITS {                    // bits description
    Uint16 GPIO0:1;                     // 0 Defines direction for this pin in GPIO mode
    Uint16 GPIO1:1;                     // 1 Defines direction for this pin in GPIO mode
    Uint16 GPIO2:1;                     // 2 Defines direction for this pin in GPIO mode
    Uint16 GPIO3:1;                     // 3 Defines direction for this pin in GPIO mode
    Uint16 GPIO4:1;                     // 4 Defines direction for this pin in GPIO mode
    Uint16 GPIO5:1;                     // 5 Defines direction for this pin in GPIO mode
    Uint16 GPIO6:1;                     // 6 Defines direction for this pin in GPIO mode
    Uint16 GPIO7:1;                     // 7 Defines direction for this pin in GPIO mode
    Uint16 GPIO8:1;                     // 8 Defines direction for this pin in GPIO mode
    Uint16 GPIO9:1;                     // 9 Defines direction for this pin in GPIO mode
    Uint16 GPIO10:1;                    // 10 Defines direction for this pin in GPIO mode
    Uint16 GPIO11:1;                    // 11 Defines direction for this pin in GPIO mode
    Uint16 GPIO12:1;                    // 12 Defines direction for this pin in GPIO mode
    Uint16 GPIO13:1;                    // 13 Defines direction for this pin in GPIO mode
    Uint16 rsvd1:1;                     // 14 Reserved
    Uint16 rsvd2:1;                     // 15 Reserved
    Uint16 GPIO16:1;                    // 16 Defines direction for this pin in GPIO mode
    Uint16 GPIO17:1;                    // 17 Defines direction for this pin in GPIO mode
    Uint16 GPIO18:1;                    // 18 Defines direction for this pin in GPIO mode
    Uint16 GPIO19:1;                    // 19 Defines direction for this pin in GPIO mode
    Uint16 GPIO20:1;                    // 20 Defines direction for this pin in GPIO mode
    Uint16 GPIO21:1;                    // 21 Defines direction for this pin in GPIO mode
    Uint16 GPIO22:1;                    // 22 Defines direction for this pin in GPIO mode
    Uint16 GPIO23:1;                    // 23 Defines direction for this pin in GPIO mode
    Uint16 GPIO24:1;                    // 24 Defines direction for this pin in GPIO mode
    Uint16 rsvd3:1;                     // 25 Reserved
    Uint16 rsvd4:1;                     // 26 Reserved
    Uint16 rsvd5:1;                     // 27 Reserved
    Uint16 GPIO28:1;                    // 28 Defines direction for this pin in GPIO mode
    Uint16 GPIO29:1;                    // 29 Defines direction for this pin in GPIO mode
    Uint16 rsvd6:1;                     // 30 Reserved
    Uint16 rsvd7:1;                     // 31 Reserved
};

union GPADIR_REG {
    Uint32  all;
    struct  GPADIR_BITS  bit;
};

struct GPAPUD_BITS {                    // bits description
    Uint16 GPIO0:1;                     // 0 Pull-Up Disable control for this pin
    Uint16 GPIO1:1;                     // 1 Pull-Up Disable control for this pin
    Uint16 GPIO2:1;                     // 2 Pull-Up Disable control for this pin
    Uint16 GPIO3:1;                     // 3 Pull-Up Disable control for this pin
    Uint16 GPIO4:1;                     // 4 Pull-Up Disable control for this pin
    Uint16 GPIO5:1;                     // 5 Pull-Up Disable control for this pin
    Uint16 GPIO6:1;                     // 6 Pull-Up Disable control for this pin
    Uint16 GPIO7:1;                     // 7 Pull-Up Disable control for this pin
    Uint16 GPIO8:1;                     // 8 Pull-Up Disable control for this pin
    Uint16 GPIO9:1;                     // 9 Pull-Up Disable control for this pin
    Uint16 GPIO10:1;                    // 10 Pull-Up Disable control for this pin
    Uint16 GPIO11:1;                    // 11 Pull-Up Disable control for this pin
    Uint16 GPIO12:1;                    // 12 Pull-Up Disable control for this pin
    Uint16 GPIO13:1;                    // 13 Pull-Up Disable control for this pin
    Uint16 rsvd1:1;                     // 14 Reserved
    Uint16 rsvd2:1;                     // 15 Reserved
    Uint16 GPIO16:1;                    // 16 Pull-Up Disable control for this pin
    Uint16 GPIO17:1;                    // 17 Pull-Up Disable control for this pin
    Uint16 GPIO18:1;                    // 18 Pull-Up Disable control for this pin
    Uint16 GPIO19:1;                    // 19 Pull-Up Disable control for this pin
    Uint16 GPIO20:1;                    // 20 Pull-Up Disable control for this pin
    Uint16 GPIO21:1;                    // 21 Pull-Up Disable control for this pin
    Uint16 GPIO22:1;                    // 22 Pull-Up Disable control for this pin
    Uint16 GPIO23:1;                    // 23 Pull-Up Disable control for this pin
    Uint16 GPIO24:1;                    // 24 Pull-Up Disable control for this pin
    Uint16 rsvd3:1;                     // 25 Reserved
    Uint16 rsvd4:1;                     // 26 Reserved
    Uint16 rsvd5:1;                     // 27 Reserved
    Uint16 GPIO28:1;                    // 28 Pull-Up Disable control for this pin
    Uint16 GPIO29:1;                    // 29 Pull-Up Disable control for this pin
    Uint16 rsvd6:1;                     // 30 Reserved
    Uint16 rsvd7:1;                     // 31 Reserved
};

union GPAPUD_REG {
    Uint32  all;
    struct  GPAPUD_BITS  bit;
};

struct GPAINV_BITS {                    // bits description
    Uint16 GPIO0:1;                     // 0 Input inversion control for this pin
    Uint16 GPIO1:1;                     // 1 Input inversion control for this pin
    Uint16 GPIO2:1;                     // 2 Input inversion control for this pin
    Uint16 GPIO3:1;                     // 3 Input inversion control for this pin
    Uint16 GPIO4:1;                     // 4 Input inversion control for this pin
    Uint16 GPIO5:1;                     // 5 Input inversion control for this pin
    Uint16 GPIO6:1;                     // 6 Input inversion control for this pin
    Uint16 GPIO7:1;                     // 7 Input inversion control for this pin
    Uint16 GPIO8:1;                     // 8 Input inversion control for this pin
    Uint16 GPIO9:1;                     // 9 Input inversion control for this pin
    Uint16 GPIO10:1;                    // 10 Input inversion control for this pin
    Uint16 GPIO11:1;                    // 11 Input inversion control for this pin
    Uint16 GPIO12:1;                    // 12 Input inversion control for this pin
    Uint16 GPIO13:1;                    // 13 Input inversion control for this pin
    Uint16 rsvd1:1;                     // 14 Reserved
    Uint16 rsvd2:1;                     // 15 Reserved
    Uint16 GPIO16:1;                    // 16 Input inversion control for this pin
    Uint16 GPIO17:1;                    // 17 Input inversion control for this pin
    Uint16 GPIO18:1;                    // 18 Input inversion control for this pin
    Uint16 GPIO19:1;                    // 19 Input inversion control for this pin
    Uint16 GPIO20:1;                    // 20 Input inversion control for this pin
    Uint16 GPIO21:1;                    // 21 Input inversion control for this pin
    Uint16 GPIO22:1;                    // 22 Input inversion control for this pin
    Uint16 GPIO23:1;                    // 23 Input inversion control for this pin
    Uint16 GPIO24:1;                    // 24 Input inversion control for this pin
    Uint16 rsvd3:1;                     // 25 Reserved
    Uint16 rsvd4:1;                     // 26 Reserved
    Uint16 rsvd5:1;                     // 27 Reserved
    Uint16 GPIO28:1;                    // 28 Input inversion control for this pin
    Uint16 GPIO29:1;                    // 29 Input inversion control for this pin
    Uint16 rsvd6:1;                     // 30 Reserved
    Uint16 rsvd7:1;                     // 31 Reserved
};

union GPAINV_REG {
    Uint32  all;
    struct  GPAINV_BITS  bit;
};

struct GPAODR_BITS {                    // bits description
    Uint16 GPIO0:1;                     // 0 Outpout Open-Drain control for this pin
    Uint16 GPIO1:1;                     // 1 Outpout Open-Drain control for this pin
    Uint16 GPIO2:1;                     // 2 Outpout Open-Drain control for this pin
    Uint16 GPIO3:1;                     // 3 Outpout Open-Drain control for this pin
    Uint16 GPIO4:1;                     // 4 Outpout Open-Drain control for this pin
    Uint16 GPIO5:1;                     // 5 Outpout Open-Drain control for this pin
    Uint16 GPIO6:1;                     // 6 Outpout Open-Drain control for this pin
    Uint16 GPIO7:1;                     // 7 Outpout Open-Drain control for this pin
    Uint16 GPIO8:1;                     // 8 Outpout Open-Drain control for this pin
    Uint16 GPIO9:1;                     // 9 Outpout Open-Drain control for this pin
    Uint16 GPIO10:1;                    // 10 Outpout Open-Drain control for this pin
    Uint16 GPIO11:1;                    // 11 Outpout Open-Drain control for this pin
    Uint16 GPIO12:1;                    // 12 Outpout Open-Drain control for this pin
    Uint16 GPIO13:1;                    // 13 Outpout Open-Drain control for this pin
    Uint16 rsvd1:1;                     // 14 Reserved
    Uint16 rsvd2:1;                     // 15 Reserved
    Uint16 GPIO16:1;                    // 16 Outpout Open-Drain control for this pin
    Uint16 GPIO17:1;                    // 17 Outpout Open-Drain control for this pin
    Uint16 GPIO18:1;                    // 18 Outpout Open-Drain control for this pin
    Uint16 GPIO19:1;                    // 19 Outpout Open-Drain control for this pin
    Uint16 GPIO20:1;                    // 20 Outpout Open-Drain control for this pin
    Uint16 GPIO21:1;                    // 21 Outpout Open-Drain control for this pin
    Uint16 GPIO22:1;                    // 22 Outpout Open-Drain control for this pin
    Uint16 GPIO23:1;                    // 23 Outpout Open-Drain control for this pin
    Uint16 GPIO24:1;                    // 24 Outpout Open-Drain control for this pin
    Uint16 rsvd3:1;                     // 25 Reserved
    Uint16 rsvd4:1;                     // 26 Reserved
    Uint16 rsvd5:1;                     // 27 Reserved
    Uint16 GPIO28:1;                    // 28 Outpout Open-Drain control for this pin
    Uint16 GPIO29:1;                    // 29 Outpout Open-Drain control for this pin
    Uint16 rsvd6:1;                     // 30 Reserved
    Uint16 rsvd7:1;                     // 31 Reserved
};

union GPAODR_REG {
    Uint32  all;
    struct  GPAODR_BITS  bit;
};

struct GPAAMSEL_BITS {                  // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 rsvd2:1;                     // 1 Reserved
    Uint16 rsvd3:1;                     // 2 Reserved
    Uint16 rsvd4:1;                     // 3 Reserved
    Uint16 rsvd5:1;                     // 4 Reserved
    Uint16 rsvd6:1;                     // 5 Reserved
    Uint16 rsvd7:1;                     // 6 Reserved
    Uint16 rsvd8:1;                     // 7 Reserved
    Uint16 rsvd9:1;                     // 8 Reserved
    Uint16 rsvd10:1;                    // 9 Reserved
    Uint16 rsvd11:1;                    // 10 Reserved
    Uint16 rsvd12:1;                    // 11 Reserved
    Uint16 GPIO12:1;                    // 12 Analog Mode select for this pin
    Uint16 GPIO13:1;                    // 13 Analog Mode select for this pin
    Uint16 rsvd13:1;                    // 14 Reserved
    Uint16 rsvd14:1;                    // 15 Reserved
    Uint16 rsvd15:1;                    // 16 Reserved
    Uint16 rsvd16:1;                    // 17 Reserved
    Uint16 rsvd17:1;                    // 18 Reserved
    Uint16 rsvd18:1;                    // 19 Reserved
    Uint16 GPIO20:1;                    // 20 Analog Mode select for this pin
    Uint16 GPIO21:1;                    // 21 Analog Mode select for this pin
    Uint16 rsvd19:1;                    // 22 Reserved
    Uint16 rsvd20:1;                    // 23 Reserved
    Uint16 rsvd21:1;                    // 24 Reserved
    Uint16 rsvd22:1;                    // 25 Reserved
    Uint16 rsvd23:1;                    // 26 Reserved
    Uint16 rsvd24:1;                    // 27 Reserved
    Uint16 GPIO28:1;                    // 28 Analog Mode select for this pin
    Uint16 rsvd25:1;                    // 29 Reserved
    Uint16 rsvd26:1;                    // 30 Reserved
    Uint16 rsvd27:1;                    // 31 Reserved
};

union GPAAMSEL_REG {
    Uint32  all;
    struct  GPAAMSEL_BITS  bit;
};

struct GPAGMUX1_BITS {                  // bits description
    Uint16 GPIO0:2;                     // 1:0 Defines pin-muxing selection for GPIO0
    Uint16 GPIO1:2;                     // 3:2 Defines pin-muxing selection for GPIO1
    Uint16 GPIO2:2;                     // 5:4 Defines pin-muxing selection for GPIO2
    Uint16 GPIO3:2;                     // 7:6 Defines pin-muxing selection for GPIO3
    Uint16 GPIO4:2;                     // 9:8 Defines pin-muxing selection for GPIO4
    Uint16 GPIO5:2;                     // 11:10 Defines pin-muxing selection for GPIO5
    Uint16 GPIO6:2;                     // 13:12 Defines pin-muxing selection for GPIO6
    Uint16 GPIO7:2;                     // 15:14 Defines pin-muxing selection for GPIO7
    Uint16 GPIO8:2;                     // 17:16 Defines pin-muxing selection for GPIO8
    Uint16 GPIO9:2;                     // 19:18 Defines pin-muxing selection for GPIO9
    Uint16 GPIO10:2;                    // 21:20 Defines pin-muxing selection for GPIO10
    Uint16 GPIO11:2;                    // 23:22 Defines pin-muxing selection for GPIO11
    Uint16 GPIO12:2;                    // 25:24 Defines pin-muxing selection for GPIO12
    Uint16 GPIO13:2;                    // 27:26 Defines pin-muxing selection for GPIO13
    Uint16 rsvd1:2;                     // 29:28 Reserved
    Uint16 rsvd2:2;                     // 31:30 Reserved
};

union GPAGMUX1_REG {
    Uint32  all;
    struct  GPAGMUX1_BITS  bit;
};

struct GPAGMUX2_BITS {                  // bits description
    Uint16 GPIO16:2;                    // 1:0 Defines pin-muxing selection for GPIO16
    Uint16 GPIO17:2;                    // 3:2 Defines pin-muxing selection for GPIO17
    Uint16 GPIO18:2;                    // 5:4 Defines pin-muxing selection for GPIO18
    Uint16 GPIO19:2;                    // 7:6 Defines pin-muxing selection for GPIO19
    Uint16 GPIO20:2;                    // 9:8 Defines pin-muxing selection for GPIO20
    Uint16 GPIO21:2;                    // 11:10 Defines pin-muxing selection for GPIO21
    Uint16 GPIO22:2;                    // 13:12 Defines pin-muxing selection for GPIO22
    Uint16 GPIO23:2;                    // 15:14 Defines pin-muxing selection for GPIO23
    Uint16 GPIO24:2;                    // 17:16 Defines pin-muxing selection for GPIO24
    Uint16 rsvd1:2;                     // 19:18 Reserved
    Uint16 rsvd2:2;                     // 21:20 Reserved
    Uint16 rsvd3:2;                     // 23:22 Reserved
    Uint16 GPIO28:2;                    // 25:24 Defines pin-muxing selection for GPIO28
    Uint16 GPIO29:2;                    // 27:26 Defines pin-muxing selection for GPIO29
    Uint16 rsvd4:2;                     // 29:28 Reserved
    Uint16 rsvd5:2;                     // 31:30 Reserved
};

union GPAGMUX2_REG {
    Uint32  all;
    struct  GPAGMUX2_BITS  bit;
};

struct GPALOCK_BITS {                   // bits description
    Uint16 GPIO0:1;                     // 0 Configuration Lock bit for this pin
    Uint16 GPIO1:1;                     // 1 Configuration Lock bit for this pin
    Uint16 GPIO2:1;                     // 2 Configuration Lock bit for this pin
    Uint16 GPIO3:1;                     // 3 Configuration Lock bit for this pin
    Uint16 GPIO4:1;                     // 4 Configuration Lock bit for this pin
    Uint16 GPIO5:1;                     // 5 Configuration Lock bit for this pin
    Uint16 GPIO6:1;                     // 6 Configuration Lock bit for this pin
    Uint16 GPIO7:1;                     // 7 Configuration Lock bit for this pin
    Uint16 GPIO8:1;                     // 8 Configuration Lock bit for this pin
    Uint16 GPIO9:1;                     // 9 Configuration Lock bit for this pin
    Uint16 GPIO10:1;                    // 10 Configuration Lock bit for this pin
    Uint16 GPIO11:1;                    // 11 Configuration Lock bit for this pin
    Uint16 GPIO12:1;                    // 12 Configuration Lock bit for this pin
    Uint16 GPIO13:1;                    // 13 Configuration Lock bit for this pin
    Uint16 rsvd1:1;                     // 14 Reserved
    Uint16 rsvd2:1;                     // 15 Reserved
    Uint16 GPIO16:1;                    // 16 Configuration Lock bit for this pin
    Uint16 GPIO17:1;                    // 17 Configuration Lock bit for this pin
    Uint16 GPIO18:1;                    // 18 Configuration Lock bit for this pin
    Uint16 GPIO19:1;                    // 19 Configuration Lock bit for this pin
    Uint16 GPIO20:1;                    // 20 Configuration Lock bit for this pin
    Uint16 GPIO21:1;                    // 21 Configuration Lock bit for this pin
    Uint16 GPIO22:1;                    // 22 Configuration Lock bit for this pin
    Uint16 GPIO23:1;                    // 23 Configuration Lock bit for this pin
    Uint16 GPIO24:1;                    // 24 Configuration Lock bit for this pin
    Uint16 rsvd3:1;                     // 25 Reserved
    Uint16 rsvd4:1;                     // 26 Reserved
    Uint16 rsvd5:1;                     // 27 Reserved
    Uint16 GPIO28:1;                    // 28 Configuration Lock bit for this pin
    Uint16 GPIO29:1;                    // 29 Configuration Lock bit for this pin
    Uint16 rsvd6:1;                     // 30 Reserved
    Uint16 rsvd7:1;                     // 31 Reserved
};

union GPALOCK_REG {
    Uint32  all;
    struct  GPALOCK_BITS  bit;
};

struct GPACR_BITS {                     // bits description
    Uint16 GPIO0:1;                     // 0 Configuration lock commit bit for this pin
    Uint16 GPIO1:1;                     // 1 Configuration lock commit bit for this pin
    Uint16 GPIO2:1;                     // 2 Configuration lock commit bit for this pin
    Uint16 GPIO3:1;                     // 3 Configuration lock commit bit for this pin
    Uint16 GPIO4:1;                     // 4 Configuration lock commit bit for this pin
    Uint16 GPIO5:1;                     // 5 Configuration lock commit bit for this pin
    Uint16 GPIO6:1;                     // 6 Configuration lock commit bit for this pin
    Uint16 GPIO7:1;                     // 7 Configuration lock commit bit for this pin
    Uint16 GPIO8:1;                     // 8 Configuration lock commit bit for this pin
    Uint16 GPIO9:1;                     // 9 Configuration lock commit bit for this pin
    Uint16 GPIO10:1;                    // 10 Configuration lock commit bit for this pin
    Uint16 GPIO11:1;                    // 11 Configuration lock commit bit for this pin
    Uint16 GPIO12:1;                    // 12 Configuration lock commit bit for this pin
    Uint16 GPIO13:1;                    // 13 Configuration lock commit bit for this pin
    Uint16 rsvd1:1;                     // 14 Reserved
    Uint16 rsvd2:1;                     // 15 Reserved
    Uint16 GPIO16:1;                    // 16 Configuration lock commit bit for this pin
    Uint16 GPIO17:1;                    // 17 Configuration lock commit bit for this pin
    Uint16 GPIO18:1;                    // 18 Configuration lock commit bit for this pin
    Uint16 GPIO19:1;                    // 19 Configuration lock commit bit for this pin
    Uint16 GPIO20:1;                    // 20 Configuration lock commit bit for this pin
    Uint16 GPIO21:1;                    // 21 Configuration lock commit bit for this pin
    Uint16 GPIO22:1;                    // 22 Configuration lock commit bit for this pin
    Uint16 GPIO23:1;                    // 23 Configuration lock commit bit for this pin
    Uint16 GPIO24:1;                    // 24 Configuration lock commit bit for this pin
    Uint16 rsvd3:1;                     // 25 Reserved
    Uint16 rsvd4:1;                     // 26 Reserved
    Uint16 rsvd5:1;                     // 27 Reserved
    Uint16 GPIO28:1;                    // 28 Configuration lock commit bit for this pin
    Uint16 GPIO29:1;                    // 29 Configuration lock commit bit for this pin
    Uint16 rsvd6:1;                     // 30 Reserved
    Uint16 rsvd7:1;                     // 31 Reserved
};

union GPACR_REG {
    Uint32  all;
    struct  GPACR_BITS  bit;
};

struct GPBCTRL_BITS {                   // bits description
    Uint16 QUALPRD0:8;                  // 7:0 Qualification sampling period for GPIO32 to GPIO39
    Uint16 QUALPRD1:8;                  // 15:8 Qualification sampling period for GPIO40 to GPIO47
    Uint16 rsvd1:8;                     // 23:16 Reserved
    Uint16 rsvd2:8;                     // 31:24 Reserved
};

union GPBCTRL_REG {
    Uint32  all;
    struct  GPBCTRL_BITS  bit;
};

struct GPBQSEL1_BITS {                  // bits description
    Uint16 GPIO32:2;                    // 1:0 Select input qualification type for GPIO32
    Uint16 GPIO33:2;                    // 3:2 Select input qualification type for GPIO33
    Uint16 rsvd1:2;                     // 5:4 Reserved
    Uint16 GPIO35:2;                    // 7:6 Select input qualification type for GPIO35
    Uint16 rsvd2:2;                     // 9:8 Reserved
    Uint16 GPIO37:2;                    // 11:10 Select input qualification type for GPIO37
    Uint16 rsvd3:2;                     // 13:12 Reserved
    Uint16 GPIO39:2;                    // 15:14 Select input qualification type for GPIO39
    Uint16 GPIO40:2;                    // 17:16 Select input qualification type for GPIO40
    Uint16 GPIO41:2;                    // 19:18 Select input qualification type for GPIO41
    Uint16 rsvd4:2;                     // 21:20 Reserved
    Uint16 rsvd5:2;                     // 23:22 Reserved
    Uint16 rsvd6:2;                     // 25:24 Reserved
    Uint16 rsvd7:2;                     // 27:26 Reserved
    Uint16 rsvd8:2;                     // 29:28 Reserved
    Uint16 rsvd9:2;                     // 31:30 Reserved
};

union GPBQSEL1_REG {
    Uint32  all;
    struct  GPBQSEL1_BITS  bit;
};

struct GPBMUX1_BITS {                   // bits description
    Uint16 GPIO32:2;                    // 1:0 Defines pin-muxing selection for GPIO32
    Uint16 GPIO33:2;                    // 3:2 Defines pin-muxing selection for GPIO33
    Uint16 rsvd1:2;                     // 5:4 Reserved
    Uint16 GPIO35:2;                    // 7:6 Defines pin-muxing selection for GPIO35
    Uint16 rsvd2:2;                     // 9:8 Reserved
    Uint16 GPIO37:2;                    // 11:10 Defines pin-muxing selection for GPIO37
    Uint16 rsvd3:2;                     // 13:12 Reserved
    Uint16 GPIO39:2;                    // 15:14 Defines pin-muxing selection for GPIO39
    Uint16 GPIO40:2;                    // 17:16 Defines pin-muxing selection for GPIO40
    Uint16 GPIO41:2;                    // 19:18 Defines pin-muxing selection for GPIO41
    Uint16 rsvd4:2;                     // 21:20 Reserved
    Uint16 rsvd5:2;                     // 23:22 Reserved
    Uint16 rsvd6:2;                     // 25:24 Reserved
    Uint16 rsvd7:2;                     // 27:26 Reserved
    Uint16 rsvd8:2;                     // 29:28 Reserved
    Uint16 rsvd9:2;                     // 31:30 Reserved
};

union GPBMUX1_REG {
    Uint32  all;
    struct  GPBMUX1_BITS  bit;
};

struct GPBDIR_BITS {                    // bits description
    Uint16 GPIO32:1;                    // 0 Defines direction for this pin in GPIO mode
    Uint16 GPIO33:1;                    // 1 Defines direction for this pin in GPIO mode
    Uint16 rsvd1:1;                     // 2 Reserved
    Uint16 GPIO35:1;                    // 3 Defines direction for this pin in GPIO mode
    Uint16 rsvd2:1;                     // 4 Reserved
    Uint16 GPIO37:1;                    // 5 Defines direction for this pin in GPIO mode
    Uint16 rsvd3:1;                     // 6 Reserved
    Uint16 GPIO39:1;                    // 7 Defines direction for this pin in GPIO mode
    Uint16 GPIO40:1;                    // 8 Defines direction for this pin in GPIO mode
    Uint16 GPIO41:1;                    // 9 Defines direction for this pin in GPIO mode
    Uint16 rsvd4:1;                     // 10 Reserved
    Uint16 rsvd5:1;                     // 11 Reserved
    Uint16 rsvd6:1;                     // 12 Reserved
    Uint16 rsvd7:1;                     // 13 Reserved
    Uint16 rsvd8:1;                     // 14 Reserved
    Uint16 rsvd9:1;                     // 15 Reserved
    Uint16 rsvd10:1;                    // 16 Reserved
    Uint16 rsvd11:1;                    // 17 Reserved
    Uint16 rsvd12:1;                    // 18 Reserved
    Uint16 rsvd13:1;                    // 19 Reserved
    Uint16 rsvd14:1;                    // 20 Reserved
    Uint16 rsvd15:1;                    // 21 Reserved
    Uint16 rsvd16:1;                    // 22 Reserved
    Uint16 rsvd17:1;                    // 23 Reserved
    Uint16 rsvd18:1;                    // 24 Reserved
    Uint16 rsvd19:1;                    // 25 Reserved
    Uint16 rsvd20:1;                    // 26 Reserved
    Uint16 rsvd21:1;                    // 27 Reserved
    Uint16 rsvd22:1;                    // 28 Reserved
    Uint16 rsvd23:1;                    // 29 Reserved
    Uint16 rsvd24:1;                    // 30 Reserved
    Uint16 rsvd25:1;                    // 31 Reserved
};

union GPBDIR_REG {
    Uint32  all;
    struct  GPBDIR_BITS  bit;
};

struct GPBPUD_BITS {                    // bits description
    Uint16 GPIO32:1;                    // 0 Pull-Up Disable control for this pin
    Uint16 GPIO33:1;                    // 1 Pull-Up Disable control for this pin
    Uint16 rsvd1:1;                     // 2 Reserved
    Uint16 GPIO35:1;                    // 3 Pull-Up Disable control for this pin
    Uint16 rsvd2:1;                     // 4 Reserved
    Uint16 GPIO37:1;                    // 5 Pull-Up Disable control for this pin
    Uint16 rsvd3:1;                     // 6 Reserved
    Uint16 GPIO39:1;                    // 7 Pull-Up Disable control for this pin
    Uint16 GPIO40:1;                    // 8 Pull-Up Disable control for this pin
    Uint16 GPIO41:1;                    // 9 Pull-Up Disable control for this pin
    Uint16 rsvd4:1;                     // 10 Reserved
    Uint16 rsvd5:1;                     // 11 Reserved
    Uint16 rsvd6:1;                     // 12 Reserved
    Uint16 rsvd7:1;                     // 13 Reserved
    Uint16 rsvd8:1;                     // 14 Reserved
    Uint16 rsvd9:1;                     // 15 Reserved
    Uint16 rsvd10:1;                    // 16 Reserved
    Uint16 rsvd11:1;                    // 17 Reserved
    Uint16 rsvd12:1;                    // 18 Reserved
    Uint16 rsvd13:1;                    // 19 Reserved
    Uint16 rsvd14:1;                    // 20 Reserved
    Uint16 rsvd15:1;                    // 21 Reserved
    Uint16 rsvd16:1;                    // 22 Reserved
    Uint16 rsvd17:1;                    // 23 Reserved
    Uint16 rsvd18:1;                    // 24 Reserved
    Uint16 rsvd19:1;                    // 25 Reserved
    Uint16 rsvd20:1;                    // 26 Reserved
    Uint16 rsvd21:1;                    // 27 Reserved
    Uint16 rsvd22:1;                    // 28 Reserved
    Uint16 rsvd23:1;                    // 29 Reserved
    Uint16 rsvd24:1;                    // 30 Reserved
    Uint16 rsvd25:1;                    // 31 Reserved
};

union GPBPUD_REG {
    Uint32  all;
    struct  GPBPUD_BITS  bit;
};

struct GPBINV_BITS {                    // bits description
    Uint16 GPIO32:1;                    // 0 Input inversion control for this pin
    Uint16 GPIO33:1;                    // 1 Input inversion control for this pin
    Uint16 rsvd1:1;                     // 2 Reserved
    Uint16 GPIO35:1;                    // 3 Input inversion control for this pin
    Uint16 rsvd2:1;                     // 4 Reserved
    Uint16 GPIO37:1;                    // 5 Input inversion control for this pin
    Uint16 rsvd3:1;                     // 6 Reserved
    Uint16 GPIO39:1;                    // 7 Input inversion control for this pin
    Uint16 GPIO40:1;                    // 8 Input inversion control for this pin
    Uint16 GPIO41:1;                    // 9 Input inversion control for this pin
    Uint16 rsvd4:1;                     // 10 Reserved
    Uint16 rsvd5:1;                     // 11 Reserved
    Uint16 rsvd6:1;                     // 12 Reserved
    Uint16 rsvd7:1;                     // 13 Reserved
    Uint16 rsvd8:1;                     // 14 Reserved
    Uint16 rsvd9:1;                     // 15 Reserved
    Uint16 rsvd10:1;                    // 16 Reserved
    Uint16 rsvd11:1;                    // 17 Reserved
    Uint16 rsvd12:1;                    // 18 Reserved
    Uint16 rsvd13:1;                    // 19 Reserved
    Uint16 rsvd14:1;                    // 20 Reserved
    Uint16 rsvd15:1;                    // 21 Reserved
    Uint16 rsvd16:1;                    // 22 Reserved
    Uint16 rsvd17:1;                    // 23 Reserved
    Uint16 rsvd18:1;                    // 24 Reserved
    Uint16 rsvd19:1;                    // 25 Reserved
    Uint16 rsvd20:1;                    // 26 Reserved
    Uint16 rsvd21:1;                    // 27 Reserved
    Uint16 rsvd22:1;                    // 28 Reserved
    Uint16 rsvd23:1;                    // 29 Reserved
    Uint16 rsvd24:1;                    // 30 Reserved
    Uint16 rsvd25:1;                    // 31 Reserved
};

union GPBINV_REG {
    Uint32  all;
    struct  GPBINV_BITS  bit;
};

struct GPBODR_BITS {                    // bits description
    Uint16 GPIO32:1;                    // 0 Outpout Open-Drain control for this pin
    Uint16 GPIO33:1;                    // 1 Outpout Open-Drain control for this pin
    Uint16 rsvd1:1;                     // 2 Reserved
    Uint16 GPIO35:1;                    // 3 Outpout Open-Drain control for this pin
    Uint16 rsvd2:1;                     // 4 Reserved
    Uint16 GPIO37:1;                    // 5 Outpout Open-Drain control for this pin
    Uint16 rsvd3:1;                     // 6 Reserved
    Uint16 GPIO39:1;                    // 7 Outpout Open-Drain control for this pin
    Uint16 GPIO40:1;                    // 8 Outpout Open-Drain control for this pin
    Uint16 GPIO41:1;                    // 9 Outpout Open-Drain control for this pin
    Uint16 rsvd4:1;                     // 10 Reserved
    Uint16 rsvd5:1;                     // 11 Reserved
    Uint16 rsvd6:1;                     // 12 Reserved
    Uint16 rsvd7:1;                     // 13 Reserved
    Uint16 rsvd8:1;                     // 14 Reserved
    Uint16 rsvd9:1;                     // 15 Reserved
    Uint16 rsvd10:1;                    // 16 Reserved
    Uint16 rsvd11:1;                    // 17 Reserved
    Uint16 rsvd12:1;                    // 18 Reserved
    Uint16 rsvd13:1;                    // 19 Reserved
    Uint16 rsvd14:1;                    // 20 Reserved
    Uint16 rsvd15:1;                    // 21 Reserved
    Uint16 rsvd16:1;                    // 22 Reserved
    Uint16 rsvd17:1;                    // 23 Reserved
    Uint16 rsvd18:1;                    // 24 Reserved
    Uint16 rsvd19:1;                    // 25 Reserved
    Uint16 rsvd20:1;                    // 26 Reserved
    Uint16 rsvd21:1;                    // 27 Reserved
    Uint16 rsvd22:1;                    // 28 Reserved
    Uint16 rsvd23:1;                    // 29 Reserved
    Uint16 rsvd24:1;                    // 30 Reserved
    Uint16 rsvd25:1;                    // 31 Reserved
};

union GPBODR_REG {
    Uint32  all;
    struct  GPBODR_BITS  bit;
};

struct GPBGMUX1_BITS {                  // bits description
    Uint16 GPIO32:2;                    // 1:0 Defines pin-muxing selection for GPIO32
    Uint16 GPIO33:2;                    // 3:2 Defines pin-muxing selection for GPIO33
    Uint16 rsvd1:2;                     // 5:4 Reserved
    Uint16 GPIO35:2;                    // 7:6 Defines pin-muxing selection for GPIO35
    Uint16 rsvd2:2;                     // 9:8 Reserved
    Uint16 GPIO37:2;                    // 11:10 Defines pin-muxing selection for GPIO37
    Uint16 rsvd3:2;                     // 13:12 Reserved
    Uint16 GPIO39:2;                    // 15:14 Defines pin-muxing selection for GPIO39
    Uint16 GPIO40:2;                    // 17:16 Defines pin-muxing selection for GPIO40
    Uint16 GPIO41:2;                    // 19:18 Defines pin-muxing selection for GPIO41
    Uint16 rsvd4:2;                     // 21:20 Reserved
    Uint16 rsvd5:2;                     // 23:22 Reserved
    Uint16 rsvd6:2;                     // 25:24 Reserved
    Uint16 rsvd7:2;                     // 27:26 Reserved
    Uint16 rsvd8:2;                     // 29:28 Reserved
    Uint16 rsvd9:2;                     // 31:30 Reserved
};

union GPBGMUX1_REG {
    Uint32  all;
    struct  GPBGMUX1_BITS  bit;
};

struct GPBLOCK_BITS {                   // bits description
    Uint16 GPIO32:1;                    // 0 Configuration Lock bit for this pin
    Uint16 GPIO33:1;                    // 1 Configuration Lock bit for this pin
    Uint16 rsvd1:1;                     // 2 Reserved
    Uint16 GPIO35:1;                    // 3 Configuration Lock bit for this pin
    Uint16 rsvd2:1;                     // 4 Reserved
    Uint16 GPIO37:1;                    // 5 Configuration Lock bit for this pin
    Uint16 rsvd3:1;                     // 6 Reserved
    Uint16 GPIO39:1;                    // 7 Configuration Lock bit for this pin
    Uint16 GPIO40:1;                    // 8 Configuration Lock bit for this pin
    Uint16 GPIO41:1;                    // 9 Configuration Lock bit for this pin
    Uint16 rsvd4:1;                     // 10 Reserved
    Uint16 rsvd5:1;                     // 11 Reserved
    Uint16 rsvd6:1;                     // 12 Reserved
    Uint16 rsvd7:1;                     // 13 Reserved
    Uint16 rsvd8:1;                     // 14 Reserved
    Uint16 rsvd9:1;                     // 15 Reserved
    Uint16 rsvd10:1;                    // 16 Reserved
    Uint16 rsvd11:1;                    // 17 Reserved
    Uint16 rsvd12:1;                    // 18 Reserved
    Uint16 rsvd13:1;                    // 19 Reserved
    Uint16 rsvd14:1;                    // 20 Reserved
    Uint16 rsvd15:1;                    // 21 Reserved
    Uint16 rsvd16:1;                    // 22 Reserved
    Uint16 rsvd17:1;                    // 23 Reserved
    Uint16 rsvd18:1;                    // 24 Reserved
    Uint16 rsvd19:1;                    // 25 Reserved
    Uint16 rsvd20:1;                    // 26 Reserved
    Uint16 rsvd21:1;                    // 27 Reserved
    Uint16 rsvd22:1;                    // 28 Reserved
    Uint16 rsvd23:1;                    // 29 Reserved
    Uint16 rsvd24:1;                    // 30 Reserved
    Uint16 rsvd25:1;                    // 31 Reserved
};

union GPBLOCK_REG {
    Uint32  all;
    struct  GPBLOCK_BITS  bit;
};

struct GPBCR_BITS {                     // bits description
    Uint16 GPIO32:1;                    // 0 Configuration lock commit bit for this pin
    Uint16 GPIO33:1;                    // 1 Configuration lock commit bit for this pin
    Uint16 rsvd1:1;                     // 2 Reserved
    Uint16 GPIO35:1;                    // 3 Configuration lock commit bit for this pin
    Uint16 rsvd2:1;                     // 4 Reserved
    Uint16 GPIO37:1;                    // 5 Configuration lock commit bit for this pin
    Uint16 rsvd3:1;                     // 6 Reserved
    Uint16 GPIO39:1;                    // 7 Configuration lock commit bit for this pin
    Uint16 GPIO40:1;                    // 8 Configuration lock commit bit for this pin
    Uint16 GPIO41:1;                    // 9 Configuration lock commit bit for this pin
    Uint16 rsvd4:1;                     // 10 Reserved
    Uint16 rsvd5:1;                     // 11 Reserved
    Uint16 rsvd6:1;                     // 12 Reserved
    Uint16 rsvd7:1;                     // 13 Reserved
    Uint16 rsvd8:1;                     // 14 Reserved
    Uint16 rsvd9:1;                     // 15 Reserved
    Uint16 rsvd10:1;                    // 16 Reserved
    Uint16 rsvd11:1;                    // 17 Reserved
    Uint16 rsvd12:1;                    // 18 Reserved
    Uint16 rsvd13:1;                    // 19 Reserved
    Uint16 rsvd14:1;                    // 20 Reserved
    Uint16 rsvd15:1;                    // 21 Reserved
    Uint16 rsvd16:1;                    // 22 Reserved
    Uint16 rsvd17:1;                    // 23 Reserved
    Uint16 rsvd18:1;                    // 24 Reserved
    Uint16 rsvd19:1;                    // 25 Reserved
    Uint16 rsvd20:1;                    // 26 Reserved
    Uint16 rsvd21:1;                    // 27 Reserved
    Uint16 rsvd22:1;                    // 28 Reserved
    Uint16 rsvd23:1;                    // 29 Reserved
    Uint16 rsvd24:1;                    // 30 Reserved
    Uint16 rsvd25:1;                    // 31 Reserved
};

union GPBCR_REG {
    Uint32  all;
    struct  GPBCR_BITS  bit;
};

struct GPHCTRL_BITS {                   // bits description
    Uint16 QUALPRD0:8;                  // 7:0 Qualification sampling period for GPIO224 to GPIO231
    Uint16 QUALPRD1:8;                  // 15:8 Qualification sampling period for GPIO232 to GPIO239
    Uint16 QUALPRD2:8;                  // 23:16 Qualification sampling period for GPIO240 to GPIO247
    Uint16 rsvd1:8;                     // 31:24 Reserved
};

union GPHCTRL_REG {
    Uint32  all;
    struct  GPHCTRL_BITS  bit;
};

struct GPHQSEL1_BITS {                  // bits description
    Uint16 GPIO224:2;                   // 1:0 Select input qualification type for this GPIO Pin
    Uint16 GPIO225:2;                   // 3:2 Select input qualification type for this GPIO Pin
    Uint16 GPIO226:2;                   // 5:4 Select input qualification type for this GPIO Pin
    Uint16 GPIO227:2;                   // 7:6 Select input qualification type for this GPIO Pin
    Uint16 GPIO228:2;                   // 9:8 Select input qualification type for this GPIO Pin
    Uint16 rsvd1:2;                     // 11:10 Reserved
    Uint16 GPIO230:2;                   // 13:12 Select input qualification type for this GPIO Pin
    Uint16 GPIO231:2;                   // 15:14 Select input qualification type for this GPIO Pin
    Uint16 GPIO232:2;                   // 17:16 Select input qualification type for this GPIO Pin
    Uint16 GPIO233:2;                   // 19:18 Select input qualification type for this GPIO Pin
    Uint16 rsvd2:2;                     // 21:20 Reserved
    Uint16 rsvd3:2;                     // 23:22 Reserved
    Uint16 rsvd4:2;                     // 25:24 Reserved
    Uint16 GPIO237:2;                   // 27:26 Select input qualification type for this GPIO Pin
    Uint16 GPIO238:2;                   // 29:28 Select input qualification type for this GPIO Pin
    Uint16 GPIO239:2;                   // 31:30 Select input qualification type for this GPIO Pin
};

union GPHQSEL1_REG {
    Uint32  all;
    struct  GPHQSEL1_BITS  bit;
};

struct GPHQSEL2_BITS {                  // bits description
    Uint16 rsvd1:2;                     // 1:0 Reserved
    Uint16 GPIO241:2;                   // 3:2 Select input qualification type for this GPIO Pin
    Uint16 GPIO242:2;                   // 5:4 Select input qualification type for this GPIO Pin
    Uint16 rsvd2:2;                     // 7:6 Reserved
    Uint16 GPIO244:2;                   // 9:8 Select input qualification type for this GPIO Pin
    Uint16 GPIO245:2;                   // 11:10 Select input qualification type for this GPIO Pin
    Uint16 rsvd3:2;                     // 13:12 Reserved
    Uint16 rsvd4:2;                     // 15:14 Reserved
    Uint16 rsvd5:2;                     // 17:16 Reserved
    Uint16 rsvd6:2;                     // 19:18 Reserved
    Uint16 rsvd7:2;                     // 21:20 Reserved
    Uint16 rsvd8:2;                     // 23:22 Reserved
    Uint16 rsvd9:2;                     // 25:24 Reserved
    Uint16 rsvd10:2;                    // 27:26 Reserved
    Uint16 rsvd11:2;                    // 29:28 Reserved
    Uint16 rsvd12:2;                    // 31:30 Reserved
};

union GPHQSEL2_REG {
    Uint32  all;
    struct  GPHQSEL2_BITS  bit;
};

struct GPHMUX1_BITS {                   // bits description
    Uint16 GPIO224:2;                   // 1:0 Defines pin-muxing selection for GPIO224
    Uint16 rsvd1:2;                     // 3:2 Reserved
    Uint16 GPIO226:2;                   // 5:4 Defines pin-muxing selection for GPIO226
    Uint16 GPIO227:2;                   // 7:6 Defines pin-muxing selection for GPIO227
    Uint16 GPIO228:2;                   // 9:8 Defines pin-muxing selection for GPIO228
    Uint16 rsvd2:2;                     // 11:10 Reserved
    Uint16 GPIO230:2;                   // 13:12 Defines pin-muxing selection for GPIO230
    Uint16 rsvd3:2;                     // 15:14 Reserved
    Uint16 rsvd4:2;                     // 17:16 Reserved
    Uint16 rsvd5:2;                     // 19:18 Reserved
    Uint16 rsvd6:2;                     // 21:20 Reserved
    Uint16 rsvd7:2;                     // 23:22 Reserved
    Uint16 rsvd8:2;                     // 25:24 Reserved
    Uint16 rsvd9:2;                     // 27:26 Reserved
    Uint16 rsvd10:2;                    // 29:28 Reserved
    Uint16 rsvd11:2;                    // 31:30 Reserved
};

union GPHMUX1_REG {
    Uint32  all;
    struct  GPHMUX1_BITS  bit;
};

struct GPHMUX2_BITS {                   // bits description
    Uint16 rsvd1:2;                     // 1:0 Reserved
    Uint16 rsvd2:2;                     // 3:2 Reserved
    Uint16 GPIO242:2;                   // 5:4 Defines pin-muxing selection for GPIO242
    Uint16 rsvd3:2;                     // 7:6 Reserved
    Uint16 rsvd4:2;                     // 9:8 Reserved
    Uint16 rsvd5:2;                     // 11:10 Reserved
    Uint16 rsvd6:2;                     // 13:12 Reserved
    Uint16 rsvd7:2;                     // 15:14 Reserved
    Uint16 rsvd8:2;                     // 17:16 Reserved
    Uint16 rsvd9:2;                     // 19:18 Reserved
    Uint16 rsvd10:2;                    // 21:20 Reserved
    Uint16 rsvd11:2;                    // 23:22 Reserved
    Uint16 rsvd12:2;                    // 25:24 Reserved
    Uint16 rsvd13:2;                    // 27:26 Reserved
    Uint16 rsvd14:2;                    // 29:28 Reserved
    Uint16 rsvd15:2;                    // 31:30 Reserved
};

union GPHMUX2_REG {
    Uint32  all;
    struct  GPHMUX2_BITS  bit;
};

struct GPHDIR_BITS {                    // bits description
    Uint16 GPIO224:1;                   // 0 Defines direction for this pin in GPIO mode
    Uint16 rsvd1:1;                     // 1 Reserved
    Uint16 GPIO226:1;                   // 2 Defines direction for this pin in GPIO mode
    Uint16 GPIO227:1;                   // 3 Defines direction for this pin in GPIO mode
    Uint16 GPIO228:1;                   // 4 Defines direction for this pin in GPIO mode
    Uint16 rsvd2:1;                     // 5 Reserved
    Uint16 GPIO230:1;                   // 6 Defines direction for this pin in GPIO mode
    Uint16 rsvd3:1;                     // 7 Reserved
    Uint16 rsvd4:1;                     // 8 Reserved
    Uint16 rsvd5:1;                     // 9 Reserved
    Uint16 rsvd6:1;                     // 10 Reserved
    Uint16 rsvd7:1;                     // 11 Reserved
    Uint16 rsvd8:1;                     // 12 Reserved
    Uint16 rsvd9:1;                     // 13 Reserved
    Uint16 rsvd10:1;                    // 14 Reserved
    Uint16 rsvd11:1;                    // 15 Reserved
    Uint16 rsvd12:1;                    // 16 Reserved
    Uint16 rsvd13:1;                    // 17 Reserved
    Uint16 GPIO242:1;                   // 18 Defines direction for this pin in GPIO mode
    Uint16 rsvd14:1;                    // 19 Reserved
    Uint16 rsvd15:1;                    // 20 Reserved
    Uint16 rsvd16:1;                    // 21 Reserved
    Uint16 rsvd17:1;                    // 22 Reserved
    Uint16 rsvd18:1;                    // 23 Reserved
    Uint16 rsvd19:1;                    // 24 Reserved
    Uint16 rsvd20:1;                    // 25 Reserved
    Uint16 rsvd21:1;                    // 26 Reserved
    Uint16 rsvd22:1;                    // 27 Reserved
    Uint16 rsvd23:1;                    // 28 Reserved
    Uint16 rsvd24:1;                    // 29 Reserved
    Uint16 rsvd25:1;                    // 30 Reserved
    Uint16 rsvd26:1;                    // 31 Reserved
};

union GPHDIR_REG {
    Uint32  all;
    struct  GPHDIR_BITS  bit;
};

struct GPHPUD_BITS {                    // bits description
    Uint16 GPIO224:1;                   // 0 Pull-Up Disable control for this pin
    Uint16 GPIO225:1;                   // 1 Pull-Up Disable control for this pin
    Uint16 GPIO226:1;                   // 2 Pull-Up Disable control for this pin
    Uint16 GPIO227:1;                   // 3 Pull-Up Disable control for this pin
    Uint16 GPIO228:1;                   // 4 Pull-Up Disable control for this pin
    Uint16 rsvd1:1;                     // 5 Reserved
    Uint16 GPIO230:1;                   // 6 Pull-Up Disable control for this pin
    Uint16 GPIO231:1;                   // 7 Pull-Up Disable control for this pin
    Uint16 GPIO232:1;                   // 8 Pull-Up Disable control for this pin
    Uint16 GPIO233:1;                   // 9 Pull-Up Disable control for this pin
    Uint16 rsvd2:1;                     // 10 Reserved
    Uint16 rsvd3:1;                     // 11 Reserved
    Uint16 rsvd4:1;                     // 12 Reserved
    Uint16 GPIO237:1;                   // 13 Pull-Up Disable control for this pin
    Uint16 GPIO238:1;                   // 14 Pull-Up Disable control for this pin
    Uint16 GPIO239:1;                   // 15 Pull-Up Disable control for this pin
    Uint16 rsvd5:1;                     // 16 Reserved
    Uint16 GPIO241:1;                   // 17 Pull-Up Disable control for this pin
    Uint16 GPIO242:1;                   // 18 Pull-Up Disable control for this pin
    Uint16 rsvd6:1;                     // 19 Reserved
    Uint16 GPIO244:1;                   // 20 Pull-Up Disable control for this pin
    Uint16 GPIO245:1;                   // 21 Pull-Up Disable control for this pin
    Uint16 rsvd7:1;                     // 22 Reserved
    Uint16 rsvd8:1;                     // 23 Reserved
    Uint16 rsvd9:1;                     // 24 Reserved
    Uint16 rsvd10:1;                    // 25 Reserved
    Uint16 rsvd11:1;                    // 26 Reserved
    Uint16 rsvd12:1;                    // 27 Reserved
    Uint16 rsvd13:1;                    // 28 Reserved
    Uint16 rsvd14:1;                    // 29 Reserved
    Uint16 rsvd15:1;                    // 30 Reserved
    Uint16 rsvd16:1;                    // 31 Reserved
};

union GPHPUD_REG {
    Uint32  all;
    struct  GPHPUD_BITS  bit;
};

struct GPHINV_BITS {                    // bits description
    Uint16 GPIO224:1;                   // 0 Input inversion control for this pin
    Uint16 GPIO225:1;                   // 1 Input inversion control for this pin
    Uint16 GPIO226:1;                   // 2 Input inversion control for this pin
    Uint16 GPIO227:1;                   // 3 Input inversion control for this pin
    Uint16 GPIO228:1;                   // 4 Input inversion control for this pin
    Uint16 rsvd1:1;                     // 5 Reserved
    Uint16 GPIO230:1;                   // 6 Input inversion control for this pin
    Uint16 GPIO231:1;                   // 7 Input inversion control for this pin
    Uint16 GPIO232:1;                   // 8 Input inversion control for this pin
    Uint16 GPIO233:1;                   // 9 Input inversion control for this pin
    Uint16 rsvd2:1;                     // 10 Reserved
    Uint16 rsvd3:1;                     // 11 Reserved
    Uint16 rsvd4:1;                     // 12 Reserved
    Uint16 GPIO237:1;                   // 13 Input inversion control for this pin
    Uint16 GPIO238:1;                   // 14 Input inversion control for this pin
    Uint16 GPIO239:1;                   // 15 Input inversion control for this pin
    Uint16 rsvd5:1;                     // 16 Reserved
    Uint16 GPIO241:1;                   // 17 Input inversion control for this pin
    Uint16 GPIO242:1;                   // 18 Input inversion control for this pin
    Uint16 rsvd6:1;                     // 19 Reserved
    Uint16 GPIO244:1;                   // 20 Input inversion control for this pin
    Uint16 GPIO245:1;                   // 21 Input inversion control for this pin
    Uint16 rsvd7:1;                     // 22 Reserved
    Uint16 rsvd8:1;                     // 23 Reserved
    Uint16 rsvd9:1;                     // 24 Reserved
    Uint16 rsvd10:1;                    // 25 Reserved
    Uint16 rsvd11:1;                    // 26 Reserved
    Uint16 rsvd12:1;                    // 27 Reserved
    Uint16 rsvd13:1;                    // 28 Reserved
    Uint16 rsvd14:1;                    // 29 Reserved
    Uint16 rsvd15:1;                    // 30 Reserved
    Uint16 rsvd16:1;                    // 31 Reserved
};

union GPHINV_REG {
    Uint32  all;
    struct  GPHINV_BITS  bit;
};

struct GPHODR_BITS {                    // bits description
    Uint16 GPIO224:1;                   // 0 Outpout Open-Drain control for this pin
    Uint16 rsvd1:1;                     // 1 Reserved
    Uint16 GPIO226:1;                   // 2 Outpout Open-Drain control for this pin
    Uint16 GPIO227:1;                   // 3 Outpout Open-Drain control for this pin
    Uint16 GPIO228:1;                   // 4 Outpout Open-Drain control for this pin
    Uint16 rsvd2:1;                     // 5 Reserved
    Uint16 GPIO230:1;                   // 6 Outpout Open-Drain control for this pin
    Uint16 rsvd3:1;                     // 7 Reserved
    Uint16 rsvd4:1;                     // 8 Reserved
    Uint16 rsvd5:1;                     // 9 Reserved
    Uint16 rsvd6:1;                     // 10 Reserved
    Uint16 rsvd7:1;                     // 11 Reserved
    Uint16 rsvd8:1;                     // 12 Reserved
    Uint16 rsvd9:1;                     // 13 Reserved
    Uint16 rsvd10:1;                    // 14 Reserved
    Uint16 rsvd11:1;                    // 15 Reserved
    Uint16 rsvd12:1;                    // 16 Reserved
    Uint16 rsvd13:1;                    // 17 Reserved
    Uint16 GPIO242:1;                   // 18 Outpout Open-Drain control for this pin
    Uint16 rsvd14:1;                    // 19 Reserved
    Uint16 rsvd15:1;                    // 20 Reserved
    Uint16 rsvd16:1;                    // 21 Reserved
    Uint16 rsvd17:1;                    // 22 Reserved
    Uint16 rsvd18:1;                    // 23 Reserved
    Uint16 rsvd19:1;                    // 24 Reserved
    Uint16 rsvd20:1;                    // 25 Reserved
    Uint16 rsvd21:1;                    // 26 Reserved
    Uint16 rsvd22:1;                    // 27 Reserved
    Uint16 rsvd23:1;                    // 28 Reserved
    Uint16 rsvd24:1;                    // 29 Reserved
    Uint16 rsvd25:1;                    // 30 Reserved
    Uint16 rsvd26:1;                    // 31 Reserved
};

union GPHODR_REG {
    Uint32  all;
    struct  GPHODR_BITS  bit;
};

struct GPHAMSEL_BITS {                  // bits description
    Uint16 GPIO224:1;                   // 0 Analog Mode select for this pin
    Uint16 GPIO225:1;                   // 1 Analog Mode select for this pin
    Uint16 GPIO226:1;                   // 2 Analog Mode select for this pin
    Uint16 GPIO227:1;                   // 3 Analog Mode select for this pin
    Uint16 GPIO228:1;                   // 4 Analog Mode select for this pin
    Uint16 rsvd1:1;                     // 5 Reserved
    Uint16 GPIO230:1;                   // 6 Analog Mode select for this pin
    Uint16 GPIO231:1;                   // 7 Analog Mode select for this pin
    Uint16 GPIO232:1;                   // 8 Analog Mode select for this pin
    Uint16 GPIO233:1;                   // 9 Analog Mode select for this pin
    Uint16 rsvd2:1;                     // 10 Reserved
    Uint16 rsvd3:1;                     // 11 Reserved
    Uint16 rsvd4:1;                     // 12 Reserved
    Uint16 GPIO237:1;                   // 13 Analog Mode select for this pin
    Uint16 GPIO238:1;                   // 14 Analog Mode select for this pin
    Uint16 GPIO239:1;                   // 15 Analog Mode select for this pin
    Uint16 rsvd5:1;                     // 16 Reserved
    Uint16 GPIO241:1;                   // 17 Analog Mode select for this pin
    Uint16 GPIO242:1;                   // 18 Analog Mode select for this pin
    Uint16 rsvd6:1;                     // 19 Reserved
    Uint16 GPIO244:1;                   // 20 Analog Mode select for this pin
    Uint16 GPIO245:1;                   // 21 Analog Mode select for this pin
    Uint16 rsvd7:1;                     // 22 Reserved
    Uint16 rsvd8:1;                     // 23 Reserved
    Uint16 rsvd9:1;                     // 24 Reserved
    Uint16 rsvd10:1;                    // 25 Reserved
    Uint16 rsvd11:1;                    // 26 Reserved
    Uint16 rsvd12:1;                    // 27 Reserved
    Uint16 rsvd13:1;                    // 28 Reserved
    Uint16 rsvd14:1;                    // 29 Reserved
    Uint16 rsvd15:1;                    // 30 Reserved
    Uint16 rsvd16:1;                    // 31 Reserved
};

union GPHAMSEL_REG {
    Uint32  all;
    struct  GPHAMSEL_BITS  bit;
};

struct GPHGMUX1_BITS {                  // bits description
    Uint16 GPIO224:2;                   // 1:0 Defines pin-muxing selection for GPIO224
    Uint16 rsvd1:2;                     // 3:2 Reserved
    Uint16 GPIO226:2;                   // 5:4 Defines pin-muxing selection for GPIO226
    Uint16 GPIO227:2;                   // 7:6 Defines pin-muxing selection for GPIO227
    Uint16 GPIO228:2;                   // 9:8 Defines pin-muxing selection for GPIO228
    Uint16 rsvd2:2;                     // 11:10 Reserved
    Uint16 GPIO230:2;                   // 13:12 Defines pin-muxing selection for GPIO230
    Uint16 rsvd3:2;                     // 15:14 Reserved
    Uint16 rsvd4:2;                     // 17:16 Reserved
    Uint16 rsvd5:2;                     // 19:18 Reserved
    Uint16 rsvd6:2;                     // 21:20 Reserved
    Uint16 rsvd7:2;                     // 23:22 Reserved
    Uint16 rsvd8:2;                     // 25:24 Reserved
    Uint16 rsvd9:2;                     // 27:26 Reserved
    Uint16 rsvd10:2;                    // 29:28 Reserved
    Uint16 rsvd11:2;                    // 31:30 Reserved
};

union GPHGMUX1_REG {
    Uint32  all;
    struct  GPHGMUX1_BITS  bit;
};

struct GPHGMUX2_BITS {                  // bits description
    Uint16 rsvd1:2;                     // 1:0 Reserved
    Uint16 rsvd2:2;                     // 3:2 Reserved
    Uint16 GPIO242:2;                   // 5:4 Defines pin-muxing selection for GPIO242
    Uint16 rsvd3:2;                     // 7:6 Reserved
    Uint16 rsvd4:2;                     // 9:8 Reserved
    Uint16 rsvd5:2;                     // 11:10 Reserved
    Uint16 rsvd6:2;                     // 13:12 Reserved
    Uint16 rsvd7:2;                     // 15:14 Reserved
    Uint16 rsvd8:2;                     // 17:16 Reserved
    Uint16 rsvd9:2;                     // 19:18 Reserved
    Uint16 rsvd10:2;                    // 21:20 Reserved
    Uint16 rsvd11:2;                    // 23:22 Reserved
    Uint16 rsvd12:2;                    // 25:24 Reserved
    Uint16 rsvd13:2;                    // 27:26 Reserved
    Uint16 rsvd14:2;                    // 29:28 Reserved
    Uint16 rsvd15:2;                    // 31:30 Reserved
};

union GPHGMUX2_REG {
    Uint32  all;
    struct  GPHGMUX2_BITS  bit;
};

struct GPHLOCK_BITS {                   // bits description
    Uint16 GPIO224:1;                   // 0 Configuration Lock bit for this pin
    Uint16 GPIO225:1;                   // 1 Configuration Lock bit for this pin
    Uint16 GPIO226:1;                   // 2 Configuration Lock bit for this pin
    Uint16 GPIO227:1;                   // 3 Configuration Lock bit for this pin
    Uint16 GPIO228:1;                   // 4 Configuration Lock bit for this pin
    Uint16 rsvd1:1;                     // 5 Reserved
    Uint16 GPIO230:1;                   // 6 Configuration Lock bit for this pin
    Uint16 GPIO231:1;                   // 7 Configuration Lock bit for this pin
    Uint16 GPIO232:1;                   // 8 Configuration Lock bit for this pin
    Uint16 GPIO233:1;                   // 9 Configuration Lock bit for this pin
    Uint16 rsvd2:1;                     // 10 Reserved
    Uint16 rsvd3:1;                     // 11 Reserved
    Uint16 rsvd4:1;                     // 12 Reserved
    Uint16 GPIO237:1;                   // 13 Configuration Lock bit for this pin
    Uint16 GPIO238:1;                   // 14 Configuration Lock bit for this pin
    Uint16 GPIO239:1;                   // 15 Configuration Lock bit for this pin
    Uint16 rsvd5:1;                     // 16 Reserved
    Uint16 GPIO241:1;                   // 17 Configuration Lock bit for this pin
    Uint16 GPIO242:1;                   // 18 Configuration Lock bit for this pin
    Uint16 rsvd6:1;                     // 19 Reserved
    Uint16 GPIO244:1;                   // 20 Configuration Lock bit for this pin
    Uint16 GPIO245:1;                   // 21 Configuration Lock bit for this pin
    Uint16 rsvd7:1;                     // 22 Reserved
    Uint16 rsvd8:1;                     // 23 Reserved
    Uint16 rsvd9:1;                     // 24 Reserved
    Uint16 rsvd10:1;                    // 25 Reserved
    Uint16 rsvd11:1;                    // 26 Reserved
    Uint16 rsvd12:1;                    // 27 Reserved
    Uint16 rsvd13:1;                    // 28 Reserved
    Uint16 rsvd14:1;                    // 29 Reserved
    Uint16 rsvd15:1;                    // 30 Reserved
    Uint16 rsvd16:1;                    // 31 Reserved
};

union GPHLOCK_REG {
    Uint32  all;
    struct  GPHLOCK_BITS  bit;
};

struct GPHCR_BITS {                     // bits description
    Uint16 GPIO224:1;                   // 0 Configuration lock commit bit for this pin
    Uint16 GPIO225:1;                   // 1 Configuration lock commit bit for this pin
    Uint16 GPIO226:1;                   // 2 Configuration lock commit bit for this pin
    Uint16 GPIO227:1;                   // 3 Configuration lock commit bit for this pin
    Uint16 GPIO228:1;                   // 4 Configuration lock commit bit for this pin
    Uint16 rsvd1:1;                     // 5 Reserved
    Uint16 GPIO230:1;                   // 6 Configuration lock commit bit for this pin
    Uint16 GPIO231:1;                   // 7 Configuration lock commit bit for this pin
    Uint16 GPIO232:1;                   // 8 Configuration lock commit bit for this pin
    Uint16 GPIO233:1;                   // 9 Configuration lock commit bit for this pin
    Uint16 rsvd2:1;                     // 10 Reserved
    Uint16 rsvd3:1;                     // 11 Reserved
    Uint16 rsvd4:1;                     // 12 Reserved
    Uint16 GPIO237:1;                   // 13 Configuration lock commit bit for this pin
    Uint16 GPIO238:1;                   // 14 Configuration lock commit bit for this pin
    Uint16 GPIO239:1;                   // 15 Configuration lock commit bit for this pin
    Uint16 rsvd5:1;                     // 16 Reserved
    Uint16 GPIO241:1;                   // 17 Configuration lock commit bit for this pin
    Uint16 GPIO242:1;                   // 18 Configuration lock commit bit for this pin
    Uint16 rsvd6:1;                     // 19 Reserved
    Uint16 GPIO244:1;                   // 20 Configuration lock commit bit for this pin
    Uint16 GPIO245:1;                   // 21 Configuration lock commit bit for this pin
    Uint16 rsvd7:1;                     // 22 Reserved
    Uint16 rsvd8:1;                     // 23 Reserved
    Uint16 rsvd9:1;                     // 24 Reserved
    Uint16 rsvd10:1;                    // 25 Reserved
    Uint16 rsvd11:1;                    // 26 Reserved
    Uint16 rsvd12:1;                    // 27 Reserved
    Uint16 rsvd13:1;                    // 28 Reserved
    Uint16 rsvd14:1;                    // 29 Reserved
    Uint16 rsvd15:1;                    // 30 Reserved
    Uint16 rsvd16:1;                    // 31 Reserved
};

union GPHCR_REG {
    Uint32  all;
    struct  GPHCR_BITS  bit;
};

struct GPIO_CTRL_REGS {
    union   GPACTRL_REG                      GPACTRL;                      // GPIO A Qualification Sampling Period Control (GPIO0 to 31)
    union   GPAQSEL1_REG                     GPAQSEL1;                     // GPIO A Qualifier Select 1 Register (GPIO0 to 15)
    union   GPAQSEL2_REG                     GPAQSEL2;                     // GPIO A Qualifier Select 2 Register (GPIO16 to 31)
    union   GPAMUX1_REG                      GPAMUX1;                      // GPIO A Mux 1 Register (GPIO0 to 15)
    union   GPAMUX2_REG                      GPAMUX2;                      // GPIO A Mux 2 Register (GPIO16 to 31)
    union   GPADIR_REG                       GPADIR;                       // GPIO A Direction Register (GPIO0 to 31)
    union   GPAPUD_REG                       GPAPUD;                       // GPIO A Pull Up Disable Register (GPIO0 to 31)
    Uint16                                   rsvd1[2];                     // Reserved
    union   GPAINV_REG                       GPAINV;                       // GPIO A Input Polarity Invert Registers (GPIO0 to 31)
    union   GPAODR_REG                       GPAODR;                       // GPIO A Open Drain Output Register (GPIO0 to GPIO31)
    union   GPAAMSEL_REG                     GPAAMSEL;                     // GPIO A Analog Mode Select register (GPIO0 to GPIO31)
    Uint16                                   rsvd2[10];                    // Reserved
    union   GPAGMUX1_REG                     GPAGMUX1;                     // GPIO A Peripheral Group Mux (GPIO0 to 15)
    union   GPAGMUX2_REG                     GPAGMUX2;                     // GPIO A Peripheral Group Mux (GPIO16 to 31)
    Uint16                                   rsvd3[24];                    // Reserved
    union   GPALOCK_REG                      GPALOCK;                      // GPIO A Lock Configuration Register (GPIO0 to 31)
    union   GPACR_REG                        GPACR;                        // GPIO A Lock Commit Register (GPIO0 to 31)
    union   GPBCTRL_REG                      GPBCTRL;                      // GPIO B Qualification Sampling Period Control (GPIO32 to 63)
    union   GPBQSEL1_REG                     GPBQSEL1;                     // GPIO B Qualifier Select 1 Register (GPIO32 to 47)
    Uint16                                   rsvd4[2];                     // Reserved
    union   GPBMUX1_REG                      GPBMUX1;                      // GPIO B Mux 1 Register (GPIO32 to 47)
    Uint16                                   rsvd5[2];                     // Reserved
    union   GPBDIR_REG                       GPBDIR;                       // GPIO B Direction Register (GPIO32 to 63)
    union   GPBPUD_REG                       GPBPUD;                       // GPIO B Pull Up Disable Register (GPIO32 to 63)
    Uint16                                   rsvd6[2];                     // Reserved
    union   GPBINV_REG                       GPBINV;                       // GPIO B Input Polarity Invert Registers (GPIO32 to 63)
    union   GPBODR_REG                       GPBODR;                       // GPIO B Open Drain Output Register (GPIO32 to GPIO63)
    Uint16                                   rsvd7[12];                    // Reserved
    union   GPBGMUX1_REG                     GPBGMUX1;                     // GPIO B Peripheral Group Mux (GPIO32 to 47)
    Uint16                                   rsvd8[26];                    // Reserved
    union   GPBLOCK_REG                      GPBLOCK;                      // GPIO B Lock Configuration Register (GPIO32 to 63)
    union   GPBCR_REG                        GPBCR;                        // GPIO B Lock Commit Register (GPIO32 to 63)
    Uint16                                   rsvd9[320];                   // Reserved
    union   GPHCTRL_REG                      GPHCTRL;                      // GPIO H Qualification Sampling Period Control (GPIO224 to 255)
    union   GPHQSEL1_REG                     GPHQSEL1;                     // GPIO H Qualifier Select 1 Register (GPIO224 to 239)
    union   GPHQSEL2_REG                     GPHQSEL2;                     // GPIO H Qualifier Select 2 Register (GPIO240 to 255)
    union   GPHMUX1_REG                      GPHMUX1;                      // GPIO H Mux 1 Register (GPIO224 to 239)
    union   GPHMUX2_REG                      GPHMUX2;                      // GPIO H Mux 2 Register (GPIO240 to 255)
    union   GPHDIR_REG                       GPHDIR;                       // GPIO H Direction Register (GPIO224 to 255)
    union   GPHPUD_REG                       GPHPUD;                       // GPIO H Pull Up Disable Register (GPIO224 to 255)
    Uint16                                   rsvd10[2];                    // Reserved
    union   GPHINV_REG                       GPHINV;                       // GPIO H Input Polarity Invert Registers (GPIO224 to 255)
    union   GPHODR_REG                       GPHODR;                       // GPIO H Open Drain Output Register (GPIO224 to GPIO255)
    union   GPHAMSEL_REG                     GPHAMSEL;                     // GPIO H Analog Mode Select register (GPIO224 to GPIO255)
    Uint16                                   rsvd11[10];                   // Reserved
    union   GPHGMUX1_REG                     GPHGMUX1;                     // GPIO H Peripheral Group Mux (GPIO224 to 239)
    union   GPHGMUX2_REG                     GPHGMUX2;                     // GPIO H Peripheral Group Mux (GPIO240 to 255)
    Uint16                                   rsvd12[24];                   // Reserved
    union   GPHLOCK_REG                      GPHLOCK;                      // GPIO H Lock Configuration Register (GPIO224 to 255)
    union   GPHCR_REG                        GPHCR;                        // GPIO H Lock Commit Register (GPIO224 to 255)
};

struct GPADAT_BITS {                    // bits description
    Uint16 GPIO0:1;                     // 0 Data Register for this pin
    Uint16 GPIO1:1;                     // 1 Data Register for this pin
    Uint16 GPIO2:1;                     // 2 Data Register for this pin
    Uint16 GPIO3:1;                     // 3 Data Register for this pin
    Uint16 GPIO4:1;                     // 4 Data Register for this pin
    Uint16 GPIO5:1;                     // 5 Data Register for this pin
    Uint16 GPIO6:1;                     // 6 Data Register for this pin
    Uint16 GPIO7:1;                     // 7 Data Register for this pin
    Uint16 GPIO8:1;                     // 8 Data Register for this pin
    Uint16 GPIO9:1;                     // 9 Data Register for this pin
    Uint16 GPIO10:1;                    // 10 Data Register for this pin
    Uint16 GPIO11:1;                    // 11 Data Register for this pin
    Uint16 GPIO12:1;                    // 12 Data Register for this pin
    Uint16 GPIO13:1;                    // 13 Data Register for this pin
    Uint16 rsvd1:1;                     // 14 Reserved
    Uint16 rsvd2:1;                     // 15 Reserved
    Uint16 GPIO16:1;                    // 16 Data Register for this pin
    Uint16 GPIO17:1;                    // 17 Data Register for this pin
    Uint16 GPIO18:1;                    // 18 Data Register for this pin
    Uint16 GPIO19:1;                    // 19 Data Register for this pin
    Uint16 GPIO20:1;                    // 20 Data Register for this pin
    Uint16 GPIO21:1;                    // 21 Data Register for this pin
    Uint16 GPIO22:1;                    // 22 Data Register for this pin
    Uint16 GPIO23:1;                    // 23 Data Register for this pin
    Uint16 GPIO24:1;                    // 24 Data Register for this pin
    Uint16 rsvd3:1;                     // 25 Reserved
    Uint16 rsvd4:1;                     // 26 Reserved
    Uint16 rsvd5:1;                     // 27 Reserved
    Uint16 GPIO28:1;                    // 28 Data Register for this pin
    Uint16 GPIO29:1;                    // 29 Data Register for this pin
    Uint16 rsvd6:1;                     // 30 Reserved
    Uint16 rsvd7:1;                     // 31 Reserved
};

union GPADAT_REG {
    Uint32  all;
    struct  GPADAT_BITS  bit;
};

struct GPASET_BITS {                    // bits description
    Uint16 GPIO0:1;                     // 0 Output Set bit for this pin
    Uint16 GPIO1:1;                     // 1 Output Set bit for this pin
    Uint16 GPIO2:1;                     // 2 Output Set bit for this pin
    Uint16 GPIO3:1;                     // 3 Output Set bit for this pin
    Uint16 GPIO4:1;                     // 4 Output Set bit for this pin
    Uint16 GPIO5:1;                     // 5 Output Set bit for this pin
    Uint16 GPIO6:1;                     // 6 Output Set bit for this pin
    Uint16 GPIO7:1;                     // 7 Output Set bit for this pin
    Uint16 GPIO8:1;                     // 8 Output Set bit for this pin
    Uint16 GPIO9:1;                     // 9 Output Set bit for this pin
    Uint16 GPIO10:1;                    // 10 Output Set bit for this pin
    Uint16 GPIO11:1;                    // 11 Output Set bit for this pin
    Uint16 GPIO12:1;                    // 12 Output Set bit for this pin
    Uint16 GPIO13:1;                    // 13 Output Set bit for this pin
    Uint16 rsvd1:1;                     // 14 Reserved
    Uint16 rsvd2:1;                     // 15 Reserved
    Uint16 GPIO16:1;                    // 16 Output Set bit for this pin
    Uint16 GPIO17:1;                    // 17 Output Set bit for this pin
    Uint16 GPIO18:1;                    // 18 Output Set bit for this pin
    Uint16 GPIO19:1;                    // 19 Output Set bit for this pin
    Uint16 GPIO20:1;                    // 20 Output Set bit for this pin
    Uint16 GPIO21:1;                    // 21 Output Set bit for this pin
    Uint16 GPIO22:1;                    // 22 Output Set bit for this pin
    Uint16 GPIO23:1;                    // 23 Output Set bit for this pin
    Uint16 GPIO24:1;                    // 24 Output Set bit for this pin
    Uint16 rsvd3:1;                     // 25 Reserved
    Uint16 rsvd4:1;                     // 26 Reserved
    Uint16 rsvd5:1;                     // 27 Reserved
    Uint16 GPIO28:1;                    // 28 Output Set bit for this pin
    Uint16 GPIO29:1;                    // 29 Output Set bit for this pin
    Uint16 rsvd6:1;                     // 30 Reserved
    Uint16 rsvd7:1;                     // 31 Reserved
};

union GPASET_REG {
    Uint32  all;
    struct  GPASET_BITS  bit;
};

struct GPACLEAR_BITS {                  // bits description
    Uint16 GPIO0:1;                     // 0 Output Clear bit for this pin
    Uint16 GPIO1:1;                     // 1 Output Clear bit for this pin
    Uint16 GPIO2:1;                     // 2 Output Clear bit for this pin
    Uint16 GPIO3:1;                     // 3 Output Clear bit for this pin
    Uint16 GPIO4:1;                     // 4 Output Clear bit for this pin
    Uint16 GPIO5:1;                     // 5 Output Clear bit for this pin
    Uint16 GPIO6:1;                     // 6 Output Clear bit for this pin
    Uint16 GPIO7:1;                     // 7 Output Clear bit for this pin
    Uint16 GPIO8:1;                     // 8 Output Clear bit for this pin
    Uint16 GPIO9:1;                     // 9 Output Clear bit for this pin
    Uint16 GPIO10:1;                    // 10 Output Clear bit for this pin
    Uint16 GPIO11:1;                    // 11 Output Clear bit for this pin
    Uint16 GPIO12:1;                    // 12 Output Clear bit for this pin
    Uint16 GPIO13:1;                    // 13 Output Clear bit for this pin
    Uint16 rsvd1:1;                     // 14 Reserved
    Uint16 rsvd2:1;                     // 15 Reserved
    Uint16 GPIO16:1;                    // 16 Output Clear bit for this pin
    Uint16 GPIO17:1;                    // 17 Output Clear bit for this pin
    Uint16 GPIO18:1;                    // 18 Output Clear bit for this pin
    Uint16 GPIO19:1;                    // 19 Output Clear bit for this pin
    Uint16 GPIO20:1;                    // 20 Output Clear bit for this pin
    Uint16 GPIO21:1;                    // 21 Output Clear bit for this pin
    Uint16 GPIO22:1;                    // 22 Output Clear bit for this pin
    Uint16 GPIO23:1;                    // 23 Output Clear bit for this pin
    Uint16 GPIO24:1;                    // 24 Output Clear bit for this pin
    Uint16 rsvd3:1;                     // 25 Reserved
    Uint16 rsvd4:1;                     // 26 Reserved
    Uint16 rsvd5:1;                     // 27 Reserved
    Uint16 GPIO28:1;                    // 28 Output Clear bit for this pin
    Uint16 GPIO29:1;                    // 29 Output Clear bit for this pin
    Uint16 rsvd6:1;                     // 30 Reserved
    Uint16 rsvd7:1;                     // 31 Reserved
};

union GPACLEAR_REG {
    Uint32  all;
    struct  GPACLEAR_BITS  bit;
};

struct GPATOGGLE_BITS {                 // bits description
    Uint16 GPIO0:1;                     // 0 Output Toggle bit for this pin
    Uint16 GPIO1:1;                     // 1 Output Toggle bit for this pin
    Uint16 GPIO2:1;                     // 2 Output Toggle bit for this pin
    Uint16 GPIO3:1;                     // 3 Output Toggle bit for this pin
    Uint16 GPIO4:1;                     // 4 Output Toggle bit for this pin
    Uint16 GPIO5:1;                     // 5 Output Toggle bit for this pin
    Uint16 GPIO6:1;                     // 6 Output Toggle bit for this pin
    Uint16 GPIO7:1;                     // 7 Output Toggle bit for this pin
    Uint16 GPIO8:1;                     // 8 Output Toggle bit for this pin
    Uint16 GPIO9:1;                     // 9 Output Toggle bit for this pin
    Uint16 GPIO10:1;                    // 10 Output Toggle bit for this pin
    Uint16 GPIO11:1;                    // 11 Output Toggle bit for this pin
    Uint16 GPIO12:1;                    // 12 Output Toggle bit for this pin
    Uint16 GPIO13:1;                    // 13 Output Toggle bit for this pin
    Uint16 rsvd1:1;                     // 14 Reserved
    Uint16 rsvd2:1;                     // 15 Reserved
    Uint16 GPIO16:1;                    // 16 Output Toggle bit for this pin
    Uint16 GPIO17:1;                    // 17 Output Toggle bit for this pin
    Uint16 GPIO18:1;                    // 18 Output Toggle bit for this pin
    Uint16 GPIO19:1;                    // 19 Output Toggle bit for this pin
    Uint16 GPIO20:1;                    // 20 Output Toggle bit for this pin
    Uint16 GPIO21:1;                    // 21 Output Toggle bit for this pin
    Uint16 GPIO22:1;                    // 22 Output Toggle bit for this pin
    Uint16 GPIO23:1;                    // 23 Output Toggle bit for this pin
    Uint16 GPIO24:1;                    // 24 Output Toggle bit for this pin
    Uint16 rsvd3:1;                     // 25 Reserved
    Uint16 rsvd4:1;                     // 26 Reserved
    Uint16 rsvd5:1;                     // 27 Reserved
    Uint16 GPIO28:1;                    // 28 Output Toggle bit for this pin
    Uint16 GPIO29:1;                    // 29 Output Toggle bit for this pin
    Uint16 rsvd6:1;                     // 30 Reserved
    Uint16 rsvd7:1;                     // 31 Reserved
};

union GPATOGGLE_REG {
    Uint32  all;
    struct  GPATOGGLE_BITS  bit;
};

struct GPBDAT_BITS {                    // bits description
    Uint16 GPIO32:1;                    // 0 Data Register for this pin
    Uint16 GPIO33:1;                    // 1 Data Register for this pin
    Uint16 rsvd1:1;                     // 2 Reserved
    Uint16 GPIO35:1;                    // 3 Data Register for this pin
    Uint16 rsvd2:1;                     // 4 Reserved
    Uint16 GPIO37:1;                    // 5 Data Register for this pin
    Uint16 rsvd3:1;                     // 6 Reserved
    Uint16 GPIO39:1;                    // 7 Data Register for this pin
    Uint16 GPIO40:1;                    // 8 Data Register for this pin
    Uint16 GPIO41:1;                    // 9 Data Register for this pin
    Uint16 rsvd4:1;                     // 10 Reserved
    Uint16 rsvd5:1;                     // 11 Reserved
    Uint16 rsvd6:1;                     // 12 Reserved
    Uint16 rsvd7:1;                     // 13 Reserved
    Uint16 rsvd8:1;                     // 14 Reserved
    Uint16 rsvd9:1;                     // 15 Reserved
    Uint16 rsvd10:1;                    // 16 Reserved
    Uint16 rsvd11:1;                    // 17 Reserved
    Uint16 rsvd12:1;                    // 18 Reserved
    Uint16 rsvd13:1;                    // 19 Reserved
    Uint16 rsvd14:1;                    // 20 Reserved
    Uint16 rsvd15:1;                    // 21 Reserved
    Uint16 rsvd16:1;                    // 22 Reserved
    Uint16 rsvd17:1;                    // 23 Reserved
    Uint16 rsvd18:1;                    // 24 Reserved
    Uint16 rsvd19:1;                    // 25 Reserved
    Uint16 rsvd20:1;                    // 26 Reserved
    Uint16 rsvd21:1;                    // 27 Reserved
    Uint16 rsvd22:1;                    // 28 Reserved
    Uint16 rsvd23:1;                    // 29 Reserved
    Uint16 rsvd24:1;                    // 30 Reserved
    Uint16 rsvd25:1;                    // 31 Reserved
};

union GPBDAT_REG {
    Uint32  all;
    struct  GPBDAT_BITS  bit;
};

struct GPBSET_BITS {                    // bits description
    Uint16 GPIO32:1;                    // 0 Output Set bit for this pin
    Uint16 GPIO33:1;                    // 1 Output Set bit for this pin
    Uint16 rsvd1:1;                     // 2 Reserved
    Uint16 GPIO35:1;                    // 3 Output Set bit for this pin
    Uint16 rsvd2:1;                     // 4 Reserved
    Uint16 GPIO37:1;                    // 5 Output Set bit for this pin
    Uint16 rsvd3:1;                     // 6 Reserved
    Uint16 GPIO39:1;                    // 7 Output Set bit for this pin
    Uint16 GPIO40:1;                    // 8 Output Set bit for this pin
    Uint16 GPIO41:1;                    // 9 Output Set bit for this pin
    Uint16 rsvd4:1;                     // 10 Reserved
    Uint16 rsvd5:1;                     // 11 Reserved
    Uint16 rsvd6:1;                     // 12 Reserved
    Uint16 rsvd7:1;                     // 13 Reserved
    Uint16 rsvd8:1;                     // 14 Reserved
    Uint16 rsvd9:1;                     // 15 Reserved
    Uint16 rsvd10:1;                    // 16 Reserved
    Uint16 rsvd11:1;                    // 17 Reserved
    Uint16 rsvd12:1;                    // 18 Reserved
    Uint16 rsvd13:1;                    // 19 Reserved
    Uint16 rsvd14:1;                    // 20 Reserved
    Uint16 rsvd15:1;                    // 21 Reserved
    Uint16 rsvd16:1;                    // 22 Reserved
    Uint16 rsvd17:1;                    // 23 Reserved
    Uint16 rsvd18:1;                    // 24 Reserved
    Uint16 rsvd19:1;                    // 25 Reserved
    Uint16 rsvd20:1;                    // 26 Reserved
    Uint16 rsvd21:1;                    // 27 Reserved
    Uint16 rsvd22:1;                    // 28 Reserved
    Uint16 rsvd23:1;                    // 29 Reserved
    Uint16 rsvd24:1;                    // 30 Reserved
    Uint16 rsvd25:1;                    // 31 Reserved
};

union GPBSET_REG {
    Uint32  all;
    struct  GPBSET_BITS  bit;
};

struct GPBCLEAR_BITS {                  // bits description
    Uint16 GPIO32:1;                    // 0 Output Clear bit for this pin
    Uint16 GPIO33:1;                    // 1 Output Clear bit for this pin
    Uint16 rsvd1:1;                     // 2 Reserved
    Uint16 GPIO35:1;                    // 3 Output Clear bit for this pin
    Uint16 rsvd2:1;                     // 4 Reserved
    Uint16 GPIO37:1;                    // 5 Output Clear bit for this pin
    Uint16 rsvd3:1;                     // 6 Reserved
    Uint16 GPIO39:1;                    // 7 Output Clear bit for this pin
    Uint16 GPIO40:1;                    // 8 Output Clear bit for this pin
    Uint16 GPIO41:1;                    // 9 Output Clear bit for this pin
    Uint16 rsvd4:1;                     // 10 Reserved
    Uint16 rsvd5:1;                     // 11 Reserved
    Uint16 rsvd6:1;                     // 12 Reserved
    Uint16 rsvd7:1;                     // 13 Reserved
    Uint16 rsvd8:1;                     // 14 Reserved
    Uint16 rsvd9:1;                     // 15 Reserved
    Uint16 rsvd10:1;                    // 16 Reserved
    Uint16 rsvd11:1;                    // 17 Reserved
    Uint16 rsvd12:1;                    // 18 Reserved
    Uint16 rsvd13:1;                    // 19 Reserved
    Uint16 rsvd14:1;                    // 20 Reserved
    Uint16 rsvd15:1;                    // 21 Reserved
    Uint16 rsvd16:1;                    // 22 Reserved
    Uint16 rsvd17:1;                    // 23 Reserved
    Uint16 rsvd18:1;                    // 24 Reserved
    Uint16 rsvd19:1;                    // 25 Reserved
    Uint16 rsvd20:1;                    // 26 Reserved
    Uint16 rsvd21:1;                    // 27 Reserved
    Uint16 rsvd22:1;                    // 28 Reserved
    Uint16 rsvd23:1;                    // 29 Reserved
    Uint16 rsvd24:1;                    // 30 Reserved
    Uint16 rsvd25:1;                    // 31 Reserved
};

union GPBCLEAR_REG {
    Uint32  all;
    struct  GPBCLEAR_BITS  bit;
};

struct GPBTOGGLE_BITS {                 // bits description
    Uint16 GPIO32:1;                    // 0 Output Toggle bit for this pin
    Uint16 GPIO33:1;                    // 1 Output Toggle bit for this pin
    Uint16 rsvd1:1;                     // 2 Reserved
    Uint16 GPIO35:1;                    // 3 Output Toggle bit for this pin
    Uint16 rsvd2:1;                     // 4 Reserved
    Uint16 GPIO37:1;                    // 5 Output Toggle bit for this pin
    Uint16 rsvd3:1;                     // 6 Reserved
    Uint16 GPIO39:1;                    // 7 Output Toggle bit for this pin
    Uint16 GPIO40:1;                    // 8 Output Toggle bit for this pin
    Uint16 GPIO41:1;                    // 9 Output Toggle bit for this pin
    Uint16 rsvd4:1;                     // 10 Reserved
    Uint16 rsvd5:1;                     // 11 Reserved
    Uint16 rsvd6:1;                     // 12 Reserved
    Uint16 rsvd7:1;                     // 13 Reserved
    Uint16 rsvd8:1;                     // 14 Reserved
    Uint16 rsvd9:1;                     // 15 Reserved
    Uint16 rsvd10:1;                    // 16 Reserved
    Uint16 rsvd11:1;                    // 17 Reserved
    Uint16 rsvd12:1;                    // 18 Reserved
    Uint16 rsvd13:1;                    // 19 Reserved
    Uint16 rsvd14:1;                    // 20 Reserved
    Uint16 rsvd15:1;                    // 21 Reserved
    Uint16 rsvd16:1;                    // 22 Reserved
    Uint16 rsvd17:1;                    // 23 Reserved
    Uint16 rsvd18:1;                    // 24 Reserved
    Uint16 rsvd19:1;                    // 25 Reserved
    Uint16 rsvd20:1;                    // 26 Reserved
    Uint16 rsvd21:1;                    // 27 Reserved
    Uint16 rsvd22:1;                    // 28 Reserved
    Uint16 rsvd23:1;                    // 29 Reserved
    Uint16 rsvd24:1;                    // 30 Reserved
    Uint16 rsvd25:1;                    // 31 Reserved
};

union GPBTOGGLE_REG {
    Uint32  all;
    struct  GPBTOGGLE_BITS  bit;
};

struct GPHDAT_BITS {                    // bits description
    Uint16 GPIO224:1;                   // 0 Data Register for this pin
    Uint16 GPIO225:1;                   // 1 Data Register for this pin
    Uint16 GPIO226:1;                   // 2 Data Register for this pin
    Uint16 GPIO227:1;                   // 3 Data Register for this pin
    Uint16 GPIO228:1;                   // 4 Data Register for this pin
    Uint16 rsvd1:1;                     // 5 Reserved
    Uint16 GPIO230:1;                   // 6 Data Register for this pin
    Uint16 GPIO231:1;                   // 7 Data Register for this pin
    Uint16 GPIO232:1;                   // 8 Data Register for this pin
    Uint16 GPIO233:1;                   // 9 Data Register for this pin
    Uint16 rsvd2:1;                     // 10 Reserved
    Uint16 rsvd3:1;                     // 11 Reserved
    Uint16 rsvd4:1;                     // 12 Reserved
    Uint16 GPIO237:1;                   // 13 Data Register for this pin
    Uint16 GPIO238:1;                   // 14 Data Register for this pin
    Uint16 GPIO239:1;                   // 15 Data Register for this pin
    Uint16 rsvd5:1;                     // 16 Reserved
    Uint16 GPIO241:1;                   // 17 Data Register for this pin
    Uint16 GPIO242:1;                   // 18 Data Register for this pin
    Uint16 rsvd6:1;                     // 19 Reserved
    Uint16 GPIO244:1;                   // 20 Data Register for this pin
    Uint16 GPIO245:1;                   // 21 Data Register for this pin
    Uint16 rsvd7:1;                     // 22 Reserved
    Uint16 rsvd8:1;                     // 23 Reserved
    Uint16 rsvd9:1;                     // 24 Reserved
    Uint16 rsvd10:1;                    // 25 Reserved
    Uint16 rsvd11:1;                    // 26 Reserved
    Uint16 rsvd12:1;                    // 27 Reserved
    Uint16 rsvd13:1;                    // 28 Reserved
    Uint16 rsvd14:1;                    // 29 Reserved
    Uint16 rsvd15:1;                    // 30 Reserved
    Uint16 rsvd16:1;                    // 31 Reserved
};

union GPHDAT_REG {
    Uint32  all;
    struct  GPHDAT_BITS  bit;
};

struct GPHSET_BITS {                    // bits description
    Uint16 GPIO224:1;                   // 0 Output Set bit for this pin
    Uint16 rsvd1:1;                     // 1 Reserved
    Uint16 GPIO226:1;                   // 2 Output Set bit for this pin
    Uint16 GPIO227:1;                   // 3 Output Set bit for this pin
    Uint16 GPIO228:1;                   // 4 Output Set bit for this pin
    Uint16 rsvd2:1;                     // 5 Reserved
    Uint16 GPIO230:1;                   // 6 Output Set bit for this pin
    Uint16 rsvd3:1;                     // 7 Reserved
    Uint16 rsvd4:1;                     // 8 Reserved
    Uint16 rsvd5:1;                     // 9 Reserved
    Uint16 rsvd6:1;                     // 10 Reserved
    Uint16 rsvd7:1;                     // 11 Reserved
    Uint16 rsvd8:1;                     // 12 Reserved
    Uint16 rsvd9:1;                     // 13 Reserved
    Uint16 rsvd10:1;                    // 14 Reserved
    Uint16 rsvd11:1;                    // 15 Reserved
    Uint16 rsvd12:1;                    // 16 Reserved
    Uint16 rsvd13:1;                    // 17 Reserved
    Uint16 GPIO242:1;                   // 18 Output Set bit for this pin
    Uint16 rsvd14:1;                    // 19 Reserved
    Uint16 rsvd15:1;                    // 20 Reserved
    Uint16 rsvd16:1;                    // 21 Reserved
    Uint16 rsvd17:1;                    // 22 Reserved
    Uint16 rsvd18:1;                    // 23 Reserved
    Uint16 rsvd19:1;                    // 24 Reserved
    Uint16 rsvd20:1;                    // 25 Reserved
    Uint16 rsvd21:1;                    // 26 Reserved
    Uint16 rsvd22:1;                    // 27 Reserved
    Uint16 rsvd23:1;                    // 28 Reserved
    Uint16 rsvd24:1;                    // 29 Reserved
    Uint16 rsvd25:1;                    // 30 Reserved
    Uint16 rsvd26:1;                    // 31 Reserved
};

union GPHSET_REG {
    Uint32  all;
    struct  GPHSET_BITS  bit;
};

struct GPHCLEAR_BITS {                  // bits description
    Uint16 GPIO224:1;                   // 0 Output Clear bit for this pin
    Uint16 rsvd1:1;                     // 1 Reserved
    Uint16 GPIO226:1;                   // 2 Output Clear bit for this pin
    Uint16 GPIO227:1;                   // 3 Output Clear bit for this pin
    Uint16 GPIO228:1;                   // 4 Output Clear bit for this pin
    Uint16 rsvd2:1;                     // 5 Reserved
    Uint16 GPIO230:1;                   // 6 Output Clear bit for this pin
    Uint16 rsvd3:1;                     // 7 Reserved
    Uint16 rsvd4:1;                     // 8 Reserved
    Uint16 rsvd5:1;                     // 9 Reserved
    Uint16 rsvd6:1;                     // 10 Reserved
    Uint16 rsvd7:1;                     // 11 Reserved
    Uint16 rsvd8:1;                     // 12 Reserved
    Uint16 rsvd9:1;                     // 13 Reserved
    Uint16 rsvd10:1;                    // 14 Reserved
    Uint16 rsvd11:1;                    // 15 Reserved
    Uint16 rsvd12:1;                    // 16 Reserved
    Uint16 rsvd13:1;                    // 17 Reserved
    Uint16 GPIO242:1;                   // 18 Output Clear bit for this pin
    Uint16 rsvd14:1;                    // 19 Reserved
    Uint16 rsvd15:1;                    // 20 Reserved
    Uint16 rsvd16:1;                    // 21 Reserved
    Uint16 rsvd17:1;                    // 22 Reserved
    Uint16 rsvd18:1;                    // 23 Reserved
    Uint16 rsvd19:1;                    // 24 Reserved
    Uint16 rsvd20:1;                    // 25 Reserved
    Uint16 rsvd21:1;                    // 26 Reserved
    Uint16 rsvd22:1;                    // 27 Reserved
    Uint16 rsvd23:1;                    // 28 Reserved
    Uint16 rsvd24:1;                    // 29 Reserved
    Uint16 rsvd25:1;                    // 30 Reserved
    Uint16 rsvd26:1;                    // 31 Reserved
};

union GPHCLEAR_REG {
    Uint32  all;
    struct  GPHCLEAR_BITS  bit;
};

struct GPHTOGGLE_BITS {                 // bits description
    Uint16 GPIO224:1;                   // 0 Output Toggle bit for this pin
    Uint16 rsvd1:1;                     // 1 Reserved
    Uint16 GPIO226:1;                   // 2 Output Toggle bit for this pin
    Uint16 GPIO227:1;                   // 3 Output Toggle bit for this pin
    Uint16 GPIO228:1;                   // 4 Output Toggle bit for this pin
    Uint16 rsvd2:1;                     // 5 Reserved
    Uint16 GPIO230:1;                   // 6 Output Toggle bit for this pin
    Uint16 rsvd3:1;                     // 7 Reserved
    Uint16 rsvd4:1;                     // 8 Reserved
    Uint16 rsvd5:1;                     // 9 Reserved
    Uint16 rsvd6:1;                     // 10 Reserved
    Uint16 rsvd7:1;                     // 11 Reserved
    Uint16 rsvd8:1;                     // 12 Reserved
    Uint16 rsvd9:1;                     // 13 Reserved
    Uint16 rsvd10:1;                    // 14 Reserved
    Uint16 rsvd11:1;                    // 15 Reserved
    Uint16 rsvd12:1;                    // 16 Reserved
    Uint16 rsvd13:1;                    // 17 Reserved
    Uint16 GPIO242:1;                   // 18 Output Toggle bit for this pin
    Uint16 rsvd14:1;                    // 19 Reserved
    Uint16 rsvd15:1;                    // 20 Reserved
    Uint16 rsvd16:1;                    // 21 Reserved
    Uint16 rsvd17:1;                    // 22 Reserved
    Uint16 rsvd18:1;                    // 23 Reserved
    Uint16 rsvd19:1;                    // 24 Reserved
    Uint16 rsvd20:1;                    // 25 Reserved
    Uint16 rsvd21:1;                    // 26 Reserved
    Uint16 rsvd22:1;                    // 27 Reserved
    Uint16 rsvd23:1;                    // 28 Reserved
    Uint16 rsvd24:1;                    // 29 Reserved
    Uint16 rsvd25:1;                    // 30 Reserved
    Uint16 rsvd26:1;                    // 31 Reserved
};

union GPHTOGGLE_REG {
    Uint32  all;
    struct  GPHTOGGLE_BITS  bit;
};

struct GPIO_DATA_REGS {
    union   GPADAT_REG                       GPADAT;                       // GPIO A Data Register (GPIO0 to 31)
    union   GPASET_REG                       GPASET;                       // GPIO A Data Set Register (GPIO0 to 31)
    union   GPACLEAR_REG                     GPACLEAR;                     // GPIO A Data Clear Register (GPIO0 to 31)
    union   GPATOGGLE_REG                    GPATOGGLE;                    // GPIO A Data Toggle Register (GPIO0 to 31)
    union   GPBDAT_REG                       GPBDAT;                       // GPIO B Data Register (GPIO32 to 63)
    union   GPBSET_REG                       GPBSET;                       // GPIO B Data Set Register (GPIO32 to 63)
    union   GPBCLEAR_REG                     GPBCLEAR;                     // GPIO B Data Clear Register (GPIO32 to 63)
    union   GPBTOGGLE_REG                    GPBTOGGLE;                    // GPIO B Data Toggle Register (GPIO32 to 63)
    Uint16                                   rsvd1[40];                    // Reserved
    union   GPHDAT_REG                       GPHDAT;                       // GPIO H Data Register (GPIO224 to 255)
    union   GPHSET_REG                       GPHSET;                       // GPIO H Data Set Register (GPIO224 to 255)
    union   GPHCLEAR_REG                     GPHCLEAR;                     // GPIO H Data Clear Register (GPIO224 to 255)
    union   GPHTOGGLE_REG                    GPHTOGGLE;                    // GPIO H Data Toggle Register (GPIO224 to 255)
};

struct GPIO_DATA_READ_REGS {
    Uint32                                   GPADAT_R;                     // GPIO A Data Read Register
    Uint32                                   GPBDAT_R;                     // GPIO B Data Read Register
    Uint16                                   rsvd1[10];                    // Reserved
    Uint32                                   GPHDAT_R;                     // GPIO H Data Read Register
};

//---------------------------------------------------------------------------
// GPIO External References & Function Declarations:
//
extern volatile struct GPIO_CTRL_REGS GpioCtrlRegs;
extern volatile struct GPIO_DATA_REGS GpioDataRegs;
extern volatile struct GPIO_DATA_READ_REGS GpioDataReadRegs;
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
