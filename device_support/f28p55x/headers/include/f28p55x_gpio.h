//###########################################################################
//
// FILE:    f28p55x_gpio.h
//
// TITLE:   Definitions for the GPIO registers.
//
//###########################################################################
// 
// C2000Ware v5.04.00.00
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

#ifndef F28P55X_GPIO_H
#define F28P55X_GPIO_H

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
    Uint16 GPIO14:2;                    // 29:28 Select input qualification type for GPIO14
    Uint16 GPIO15:2;                    // 31:30 Select input qualification type for GPIO15
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
    Uint16 GPIO25:2;                    // 19:18 Select input qualification type for GPIO25
    Uint16 GPIO26:2;                    // 21:20 Select input qualification type for GPIO26
    Uint16 GPIO27:2;                    // 23:22 Select input qualification type for GPIO27
    Uint16 GPIO28:2;                    // 25:24 Select input qualification type for GPIO28
    Uint16 GPIO29:2;                    // 27:26 Select input qualification type for GPIO29
    Uint16 GPIO30:2;                    // 29:28 Select input qualification type for GPIO30
    Uint16 GPIO31:2;                    // 31:30 Select input qualification type for GPIO31
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
    Uint16 GPIO14:2;                    // 29:28 Defines pin-muxing selection for GPIO14
    Uint16 GPIO15:2;                    // 31:30 Defines pin-muxing selection for GPIO15
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
    Uint16 GPIO25:2;                    // 19:18 Defines pin-muxing selection for GPIO25
    Uint16 GPIO26:2;                    // 21:20 Defines pin-muxing selection for GPIO26
    Uint16 GPIO27:2;                    // 23:22 Defines pin-muxing selection for GPIO27
    Uint16 GPIO28:2;                    // 25:24 Defines pin-muxing selection for GPIO28
    Uint16 GPIO29:2;                    // 27:26 Defines pin-muxing selection for GPIO29
    Uint16 GPIO30:2;                    // 29:28 Defines pin-muxing selection for GPIO30
    Uint16 GPIO31:2;                    // 31:30 Defines pin-muxing selection for GPIO31
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
    Uint16 GPIO14:1;                    // 14 Defines direction for this pin in GPIO mode
    Uint16 GPIO15:1;                    // 15 Defines direction for this pin in GPIO mode
    Uint16 GPIO16:1;                    // 16 Defines direction for this pin in GPIO mode
    Uint16 GPIO17:1;                    // 17 Defines direction for this pin in GPIO mode
    Uint16 GPIO18:1;                    // 18 Defines direction for this pin in GPIO mode
    Uint16 GPIO19:1;                    // 19 Defines direction for this pin in GPIO mode
    Uint16 GPIO20:1;                    // 20 Defines direction for this pin in GPIO mode
    Uint16 GPIO21:1;                    // 21 Defines direction for this pin in GPIO mode
    Uint16 GPIO22:1;                    // 22 Defines direction for this pin in GPIO mode
    Uint16 GPIO23:1;                    // 23 Defines direction for this pin in GPIO mode
    Uint16 GPIO24:1;                    // 24 Defines direction for this pin in GPIO mode
    Uint16 GPIO25:1;                    // 25 Defines direction for this pin in GPIO mode
    Uint16 GPIO26:1;                    // 26 Defines direction for this pin in GPIO mode
    Uint16 GPIO27:1;                    // 27 Defines direction for this pin in GPIO mode
    Uint16 GPIO28:1;                    // 28 Defines direction for this pin in GPIO mode
    Uint16 GPIO29:1;                    // 29 Defines direction for this pin in GPIO mode
    Uint16 GPIO30:1;                    // 30 Defines direction for this pin in GPIO mode
    Uint16 GPIO31:1;                    // 31 Defines direction for this pin in GPIO mode
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
    Uint16 GPIO14:1;                    // 14 Pull-Up Disable control for this pin
    Uint16 GPIO15:1;                    // 15 Pull-Up Disable control for this pin
    Uint16 GPIO16:1;                    // 16 Pull-Up Disable control for this pin
    Uint16 GPIO17:1;                    // 17 Pull-Up Disable control for this pin
    Uint16 GPIO18:1;                    // 18 Pull-Up Disable control for this pin
    Uint16 GPIO19:1;                    // 19 Pull-Up Disable control for this pin
    Uint16 GPIO20:1;                    // 20 Pull-Up Disable control for this pin
    Uint16 GPIO21:1;                    // 21 Pull-Up Disable control for this pin
    Uint16 GPIO22:1;                    // 22 Pull-Up Disable control for this pin
    Uint16 GPIO23:1;                    // 23 Pull-Up Disable control for this pin
    Uint16 GPIO24:1;                    // 24 Pull-Up Disable control for this pin
    Uint16 GPIO25:1;                    // 25 Pull-Up Disable control for this pin
    Uint16 GPIO26:1;                    // 26 Pull-Up Disable control for this pin
    Uint16 GPIO27:1;                    // 27 Pull-Up Disable control for this pin
    Uint16 GPIO28:1;                    // 28 Pull-Up Disable control for this pin
    Uint16 GPIO29:1;                    // 29 Pull-Up Disable control for this pin
    Uint16 GPIO30:1;                    // 30 Pull-Up Disable control for this pin
    Uint16 GPIO31:1;                    // 31 Pull-Up Disable control for this pin
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
    Uint16 GPIO14:1;                    // 14 Input inversion control for this pin
    Uint16 GPIO15:1;                    // 15 Input inversion control for this pin
    Uint16 GPIO16:1;                    // 16 Input inversion control for this pin
    Uint16 GPIO17:1;                    // 17 Input inversion control for this pin
    Uint16 GPIO18:1;                    // 18 Input inversion control for this pin
    Uint16 GPIO19:1;                    // 19 Input inversion control for this pin
    Uint16 GPIO20:1;                    // 20 Input inversion control for this pin
    Uint16 GPIO21:1;                    // 21 Input inversion control for this pin
    Uint16 GPIO22:1;                    // 22 Input inversion control for this pin
    Uint16 GPIO23:1;                    // 23 Input inversion control for this pin
    Uint16 GPIO24:1;                    // 24 Input inversion control for this pin
    Uint16 GPIO25:1;                    // 25 Input inversion control for this pin
    Uint16 GPIO26:1;                    // 26 Input inversion control for this pin
    Uint16 GPIO27:1;                    // 27 Input inversion control for this pin
    Uint16 GPIO28:1;                    // 28 Input inversion control for this pin
    Uint16 GPIO29:1;                    // 29 Input inversion control for this pin
    Uint16 GPIO30:1;                    // 30 Input inversion control for this pin
    Uint16 GPIO31:1;                    // 31 Input inversion control for this pin
};

union GPAINV_REG {
    Uint32  all;
    struct  GPAINV_BITS  bit;
};

struct GPAODR_BITS {                    // bits description
    Uint16 GPIO0:1;                     // 0 Output Open-Drain control for this pin
    Uint16 GPIO1:1;                     // 1 Output Open-Drain control for this pin
    Uint16 GPIO2:1;                     // 2 Output Open-Drain control for this pin
    Uint16 GPIO3:1;                     // 3 Output Open-Drain control for this pin
    Uint16 GPIO4:1;                     // 4 Output Open-Drain control for this pin
    Uint16 GPIO5:1;                     // 5 Output Open-Drain control for this pin
    Uint16 GPIO6:1;                     // 6 Output Open-Drain control for this pin
    Uint16 GPIO7:1;                     // 7 Output Open-Drain control for this pin
    Uint16 GPIO8:1;                     // 8 Output Open-Drain control for this pin
    Uint16 GPIO9:1;                     // 9 Output Open-Drain control for this pin
    Uint16 GPIO10:1;                    // 10 Output Open-Drain control for this pin
    Uint16 GPIO11:1;                    // 11 Output Open-Drain control for this pin
    Uint16 GPIO12:1;                    // 12 Output Open-Drain control for this pin
    Uint16 GPIO13:1;                    // 13 Output Open-Drain control for this pin
    Uint16 GPIO14:1;                    // 14 Output Open-Drain control for this pin
    Uint16 GPIO15:1;                    // 15 Output Open-Drain control for this pin
    Uint16 GPIO16:1;                    // 16 Output Open-Drain control for this pin
    Uint16 GPIO17:1;                    // 17 Output Open-Drain control for this pin
    Uint16 GPIO18:1;                    // 18 Output Open-Drain control for this pin
    Uint16 GPIO19:1;                    // 19 Output Open-Drain control for this pin
    Uint16 GPIO20:1;                    // 20 Output Open-Drain control for this pin
    Uint16 GPIO21:1;                    // 21 Output Open-Drain control for this pin
    Uint16 GPIO22:1;                    // 22 Output Open-Drain control for this pin
    Uint16 GPIO23:1;                    // 23 Output Open-Drain control for this pin
    Uint16 GPIO24:1;                    // 24 Output Open-Drain control for this pin
    Uint16 GPIO25:1;                    // 25 Output Open-Drain control for this pin
    Uint16 GPIO26:1;                    // 26 Output Open-Drain control for this pin
    Uint16 GPIO27:1;                    // 27 Output Open-Drain control for this pin
    Uint16 GPIO28:1;                    // 28 Output Open-Drain control for this pin
    Uint16 GPIO29:1;                    // 29 Output Open-Drain control for this pin
    Uint16 GPIO30:1;                    // 30 Output Open-Drain control for this pin
    Uint16 GPIO31:1;                    // 31 Output Open-Drain control for this pin
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
    Uint16 GPIO11:1;                    // 11 Analog Mode select for this pin
    Uint16 GPIO12:1;                    // 12 Analog Mode select for this pin
    Uint16 GPIO13:1;                    // 13 Analog Mode select for this pin
    Uint16 rsvd12:1;                    // 14 Reserved
    Uint16 rsvd13:1;                    // 15 Reserved
    Uint16 GPIO16:1;                    // 16 Analog Mode select for this pin
    Uint16 GPIO17:1;                    // 17 Analog Mode select for this pin
    Uint16 rsvd14:1;                    // 18 Reserved
    Uint16 rsvd15:1;                    // 19 Reserved
    Uint16 GPIO20:1;                    // 20 Analog Mode select for this pin
    Uint16 GPIO21:1;                    // 21 Analog Mode select for this pin
    Uint16 rsvd16:1;                    // 22 Reserved
    Uint16 GPIO23:1;                    // 23 Analog Mode select for this pin
    Uint16 GPIO24:1;                    // 24 Analog Mode select for this pin
    Uint16 rsvd17:1;                    // 25 Reserved
    Uint16 rsvd18:1;                    // 26 Reserved
    Uint16 rsvd19:1;                    // 27 Reserved
    Uint16 GPIO28:1;                    // 28 Analog Mode select for this pin
    Uint16 rsvd20:1;                    // 29 Reserved
    Uint16 rsvd21:1;                    // 30 Reserved
    Uint16 rsvd22:1;                    // 31 Reserved
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
    Uint16 GPIO14:2;                    // 29:28 Defines pin-muxing selection for GPIO14
    Uint16 GPIO15:2;                    // 31:30 Defines pin-muxing selection for GPIO15
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
    Uint16 GPIO25:2;                    // 19:18 Defines pin-muxing selection for GPIO25
    Uint16 GPIO26:2;                    // 21:20 Defines pin-muxing selection for GPIO26
    Uint16 GPIO27:2;                    // 23:22 Defines pin-muxing selection for GPIO27
    Uint16 GPIO28:2;                    // 25:24 Defines pin-muxing selection for GPIO28
    Uint16 GPIO29:2;                    // 27:26 Defines pin-muxing selection for GPIO29
    Uint16 GPIO30:2;                    // 29:28 Defines pin-muxing selection for GPIO30
    Uint16 GPIO31:2;                    // 31:30 Defines pin-muxing selection for GPIO31
};

union GPAGMUX2_REG {
    Uint32  all;
    struct  GPAGMUX2_BITS  bit;
};

struct GPACSEL1_BITS {                  // bits description
    Uint16 GPIO0:4;                     // 3:0 GPIO0 Controller CPU Select
    Uint16 GPIO1:4;                     // 7:4 GPIO1 Controller CPU Select
    Uint16 GPIO2:4;                     // 11:8 GPIO2 Controller CPU Select
    Uint16 GPIO3:4;                     // 15:12 GPIO3 Controller CPU Select
    Uint16 GPIO4:4;                     // 19:16 GPIO4 Controller CPU Select
    Uint16 GPIO5:4;                     // 23:20 GPIO5 Controller CPU Select
    Uint16 GPIO6:4;                     // 27:24 GPIO6 Controller CPU Select
    Uint16 GPIO7:4;                     // 31:28 GPIO7 Controller CPU Select
};

union GPACSEL1_REG {
    Uint32  all;
    struct  GPACSEL1_BITS  bit;
};

struct GPACSEL2_BITS {                  // bits description
    Uint16 GPIO8:4;                     // 3:0 GPIO8 Controller CPU Select
    Uint16 GPIO9:4;                     // 7:4 GPIO9 Controller CPU Select
    Uint16 GPIO10:4;                    // 11:8 GPIO10 Controller CPU Select
    Uint16 GPIO11:4;                    // 15:12 GPIO11 Controller CPU Select
    Uint16 GPIO12:4;                    // 19:16 GPIO12 Controller CPU Select
    Uint16 GPIO13:4;                    // 23:20 GPIO13 Controller CPU Select
    Uint16 GPIO14:4;                    // 27:24 GPIO14 Controller CPU Select
    Uint16 GPIO15:4;                    // 31:28 GPIO15 Controller CPU Select
};

union GPACSEL2_REG {
    Uint32  all;
    struct  GPACSEL2_BITS  bit;
};

struct GPACSEL3_BITS {                  // bits description
    Uint16 GPIO16:4;                    // 3:0 GPIO16 Controller CPU Select
    Uint16 GPIO17:4;                    // 7:4 GPIO17 Controller CPU Select
    Uint16 GPIO18:4;                    // 11:8 GPIO18 Controller CPU Select
    Uint16 GPIO19:4;                    // 15:12 GPIO19 Controller CPU Select
    Uint16 GPIO20:4;                    // 19:16 GPIO20 Controller CPU Select
    Uint16 GPIO21:4;                    // 23:20 GPIO21 Controller CPU Select
    Uint16 GPIO22:4;                    // 27:24 GPIO22 Controller CPU Select
    Uint16 GPIO23:4;                    // 31:28 GPIO23 Controller CPU Select
};

union GPACSEL3_REG {
    Uint32  all;
    struct  GPACSEL3_BITS  bit;
};

struct GPACSEL4_BITS {                  // bits description
    Uint16 GPIO24:4;                    // 3:0 GPIO24 Controller CPU Select
    Uint16 GPIO25:4;                    // 7:4 GPIO25 Controller CPU Select
    Uint16 GPIO26:4;                    // 11:8 GPIO26 Controller CPU Select
    Uint16 GPIO27:4;                    // 15:12 GPIO27 Controller CPU Select
    Uint16 GPIO28:4;                    // 19:16 GPIO28 Controller CPU Select
    Uint16 GPIO29:4;                    // 23:20 GPIO29 Controller CPU Select
    Uint16 GPIO30:4;                    // 27:24 GPIO30 Controller CPU Select
    Uint16 GPIO31:4;                    // 31:28 GPIO31 Controller CPU Select
};

union GPACSEL4_REG {
    Uint32  all;
    struct  GPACSEL4_BITS  bit;
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
    Uint16 GPIO14:1;                    // 14 Configuration Lock bit for this pin
    Uint16 GPIO15:1;                    // 15 Configuration Lock bit for this pin
    Uint16 GPIO16:1;                    // 16 Configuration Lock bit for this pin
    Uint16 GPIO17:1;                    // 17 Configuration Lock bit for this pin
    Uint16 GPIO18:1;                    // 18 Configuration Lock bit for this pin
    Uint16 GPIO19:1;                    // 19 Configuration Lock bit for this pin
    Uint16 GPIO20:1;                    // 20 Configuration Lock bit for this pin
    Uint16 GPIO21:1;                    // 21 Configuration Lock bit for this pin
    Uint16 GPIO22:1;                    // 22 Configuration Lock bit for this pin
    Uint16 GPIO23:1;                    // 23 Configuration Lock bit for this pin
    Uint16 GPIO24:1;                    // 24 Configuration Lock bit for this pin
    Uint16 GPIO25:1;                    // 25 Configuration Lock bit for this pin
    Uint16 GPIO26:1;                    // 26 Configuration Lock bit for this pin
    Uint16 GPIO27:1;                    // 27 Configuration Lock bit for this pin
    Uint16 GPIO28:1;                    // 28 Configuration Lock bit for this pin
    Uint16 GPIO29:1;                    // 29 Configuration Lock bit for this pin
    Uint16 GPIO30:1;                    // 30 Configuration Lock bit for this pin
    Uint16 GPIO31:1;                    // 31 Configuration Lock bit for this pin
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
    Uint16 GPIO14:1;                    // 14 Configuration lock commit bit for this pin
    Uint16 GPIO15:1;                    // 15 Configuration lock commit bit for this pin
    Uint16 GPIO16:1;                    // 16 Configuration lock commit bit for this pin
    Uint16 GPIO17:1;                    // 17 Configuration lock commit bit for this pin
    Uint16 GPIO18:1;                    // 18 Configuration lock commit bit for this pin
    Uint16 GPIO19:1;                    // 19 Configuration lock commit bit for this pin
    Uint16 GPIO20:1;                    // 20 Configuration lock commit bit for this pin
    Uint16 GPIO21:1;                    // 21 Configuration lock commit bit for this pin
    Uint16 GPIO22:1;                    // 22 Configuration lock commit bit for this pin
    Uint16 GPIO23:1;                    // 23 Configuration lock commit bit for this pin
    Uint16 GPIO24:1;                    // 24 Configuration lock commit bit for this pin
    Uint16 GPIO25:1;                    // 25 Configuration lock commit bit for this pin
    Uint16 GPIO26:1;                    // 26 Configuration lock commit bit for this pin
    Uint16 GPIO27:1;                    // 27 Configuration lock commit bit for this pin
    Uint16 GPIO28:1;                    // 28 Configuration lock commit bit for this pin
    Uint16 GPIO29:1;                    // 29 Configuration lock commit bit for this pin
    Uint16 GPIO30:1;                    // 30 Configuration lock commit bit for this pin
    Uint16 GPIO31:1;                    // 31 Configuration lock commit bit for this pin
};

union GPACR_REG {
    Uint32  all;
    struct  GPACR_BITS  bit;
};

struct GPBCTRL_BITS {                   // bits description
    Uint16 QUALPRD0:8;                  // 7:0 Qualification sampling period for GPIO32 to GPIO39
    Uint16 QUALPRD1:8;                  // 15:8 Qualification sampling period for GPIO40 to GPIO47
    Uint16 QUALPRD2:8;                  // 23:16 Qualification sampling period for GPIO48 to GPIO55
    Uint16 QUALPRD3:8;                  // 31:24 Qualification sampling period for GPIO56 to GPIO63
};

union GPBCTRL_REG {
    Uint32  all;
    struct  GPBCTRL_BITS  bit;
};

struct GPBQSEL1_BITS {                  // bits description
    Uint16 GPIO32:2;                    // 1:0 Select input qualification type for GPIO32
    Uint16 GPIO33:2;                    // 3:2 Select input qualification type for GPIO33
    Uint16 GPIO34:2;                    // 5:4 Select input qualification type for GPIO34
    Uint16 GPIO35:2;                    // 7:6 Select input qualification type for GPIO35
    Uint16 rsvd1:2;                     // 9:8 Reserved
    Uint16 GPIO37:2;                    // 11:10 Select input qualification type for GPIO37
    Uint16 rsvd2:2;                     // 13:12 Reserved
    Uint16 rsvd3:2;                     // 15:14 Reserved
    Uint16 GPIO40:2;                    // 17:16 Select input qualification type for GPIO40
    Uint16 GPIO41:2;                    // 19:18 Select input qualification type for GPIO41
    Uint16 GPIO42:2;                    // 21:20 Select input qualification type for GPIO42
    Uint16 GPIO43:2;                    // 23:22 Select input qualification type for GPIO43
    Uint16 GPIO44:2;                    // 25:24 Select input qualification type for GPIO44
    Uint16 GPIO45:2;                    // 27:26 Select input qualification type for GPIO45
    Uint16 GPIO46:2;                    // 29:28 Select input qualification type for GPIO46
    Uint16 GPIO47:2;                    // 31:30 Select input qualification type for GPIO47
};

union GPBQSEL1_REG {
    Uint32  all;
    struct  GPBQSEL1_BITS  bit;
};

struct GPBQSEL2_BITS {                  // bits description
    Uint16 GPIO48:2;                    // 1:0 Select input qualification type for GPIO48
    Uint16 GPIO49:2;                    // 3:2 Select input qualification type for GPIO49
    Uint16 GPIO50:2;                    // 5:4 Select input qualification type for GPIO50
    Uint16 GPIO51:2;                    // 7:6 Select input qualification type for GPIO51
    Uint16 GPIO52:2;                    // 9:8 Select input qualification type for GPIO52
    Uint16 GPIO53:2;                    // 11:10 Select input qualification type for GPIO53
    Uint16 GPIO54:2;                    // 13:12 Select input qualification type for GPIO54
    Uint16 GPIO55:2;                    // 15:14 Select input qualification type for GPIO55
    Uint16 GPIO56:2;                    // 17:16 Select input qualification type for GPIO56
    Uint16 GPIO57:2;                    // 19:18 Select input qualification type for GPIO57
    Uint16 GPIO58:2;                    // 21:20 Select input qualification type for GPIO58
    Uint16 GPIO59:2;                    // 23:22 Select input qualification type for GPIO59
    Uint16 GPIO60:2;                    // 25:24 Select input qualification type for GPIO60
    Uint16 GPIO61:2;                    // 27:26 Select input qualification type for GPIO61
    Uint16 GPIO62:2;                    // 29:28 Select input qualification type for GPIO62
    Uint16 GPIO63:2;                    // 31:30 Select input qualification type for GPIO63
};

union GPBQSEL2_REG {
    Uint32  all;
    struct  GPBQSEL2_BITS  bit;
};

struct GPBMUX1_BITS {                   // bits description
    Uint16 GPIO32:2;                    // 1:0 Defines pin-muxing selection for GPIO32
    Uint16 GPIO33:2;                    // 3:2 Defines pin-muxing selection for GPIO33
    Uint16 GPIO34:2;                    // 5:4 Defines pin-muxing selection for GPIO34
    Uint16 GPIO35:2;                    // 7:6 Defines pin-muxing selection for GPIO35
    Uint16 rsvd1:2;                     // 9:8 Reserved
    Uint16 GPIO37:2;                    // 11:10 Defines pin-muxing selection for GPIO37
    Uint16 rsvd2:2;                     // 13:12 Reserved
    Uint16 rsvd3:2;                     // 15:14 Reserved
    Uint16 GPIO40:2;                    // 17:16 Defines pin-muxing selection for GPIO40
    Uint16 GPIO41:2;                    // 19:18 Defines pin-muxing selection for GPIO41
    Uint16 GPIO42:2;                    // 21:20 Defines pin-muxing selection for GPIO42
    Uint16 GPIO43:2;                    // 23:22 Defines pin-muxing selection for GPIO43
    Uint16 GPIO44:2;                    // 25:24 Defines pin-muxing selection for GPIO44
    Uint16 GPIO45:2;                    // 27:26 Defines pin-muxing selection for GPIO45
    Uint16 GPIO46:2;                    // 29:28 Defines pin-muxing selection for GPIO46
    Uint16 GPIO47:2;                    // 31:30 Defines pin-muxing selection for GPIO47
};

union GPBMUX1_REG {
    Uint32  all;
    struct  GPBMUX1_BITS  bit;
};

struct GPBMUX2_BITS {                   // bits description
    Uint16 GPIO48:2;                    // 1:0 Defines pin-muxing selection for GPIO48
    Uint16 GPIO49:2;                    // 3:2 Defines pin-muxing selection for GPIO49
    Uint16 GPIO50:2;                    // 5:4 Defines pin-muxing selection for GPIO50
    Uint16 GPIO51:2;                    // 7:6 Defines pin-muxing selection for GPIO51
    Uint16 GPIO52:2;                    // 9:8 Defines pin-muxing selection for GPIO52
    Uint16 GPIO53:2;                    // 11:10 Defines pin-muxing selection for GPIO53
    Uint16 GPIO54:2;                    // 13:12 Defines pin-muxing selection for GPIO54
    Uint16 GPIO55:2;                    // 15:14 Defines pin-muxing selection for GPIO55
    Uint16 GPIO56:2;                    // 17:16 Defines pin-muxing selection for GPIO56
    Uint16 GPIO57:2;                    // 19:18 Defines pin-muxing selection for GPIO57
    Uint16 GPIO58:2;                    // 21:20 Defines pin-muxing selection for GPIO58
    Uint16 GPIO59:2;                    // 23:22 Defines pin-muxing selection for GPIO59
    Uint16 GPIO60:2;                    // 25:24 Defines pin-muxing selection for GPIO60
    Uint16 GPIO61:2;                    // 27:26 Defines pin-muxing selection for GPIO61
    Uint16 GPIO62:2;                    // 29:28 Defines pin-muxing selection for GPIO62
    Uint16 GPIO63:2;                    // 31:30 Defines pin-muxing selection for GPIO63
};

union GPBMUX2_REG {
    Uint32  all;
    struct  GPBMUX2_BITS  bit;
};

struct GPBDIR_BITS {                    // bits description
    Uint16 GPIO32:1;                    // 0 Defines direction for this pin in GPIO mode
    Uint16 GPIO33:1;                    // 1 Defines direction for this pin in GPIO mode
    Uint16 GPIO34:1;                    // 2 Defines direction for this pin in GPIO mode
    Uint16 GPIO35:1;                    // 3 Defines direction for this pin in GPIO mode
    Uint16 rsvd1:1;                     // 4 Reserved
    Uint16 GPIO37:1;                    // 5 Defines direction for this pin in GPIO mode
    Uint16 rsvd2:1;                     // 6 Reserved
    Uint16 rsvd3:1;                     // 7 Reserved
    Uint16 GPIO40:1;                    // 8 Defines direction for this pin in GPIO mode
    Uint16 GPIO41:1;                    // 9 Defines direction for this pin in GPIO mode
    Uint16 GPIO42:1;                    // 10 Defines direction for this pin in GPIO mode
    Uint16 GPIO43:1;                    // 11 Defines direction for this pin in GPIO mode
    Uint16 GPIO44:1;                    // 12 Defines direction for this pin in GPIO mode
    Uint16 GPIO45:1;                    // 13 Defines direction for this pin in GPIO mode
    Uint16 GPIO46:1;                    // 14 Defines direction for this pin in GPIO mode
    Uint16 GPIO47:1;                    // 15 Defines direction for this pin in GPIO mode
    Uint16 GPIO48:1;                    // 16 Defines direction for this pin in GPIO mode
    Uint16 GPIO49:1;                    // 17 Defines direction for this pin in GPIO mode
    Uint16 GPIO50:1;                    // 18 Defines direction for this pin in GPIO mode
    Uint16 GPIO51:1;                    // 19 Defines direction for this pin in GPIO mode
    Uint16 GPIO52:1;                    // 20 Defines direction for this pin in GPIO mode
    Uint16 GPIO53:1;                    // 21 Defines direction for this pin in GPIO mode
    Uint16 GPIO54:1;                    // 22 Defines direction for this pin in GPIO mode
    Uint16 GPIO55:1;                    // 23 Defines direction for this pin in GPIO mode
    Uint16 GPIO56:1;                    // 24 Defines direction for this pin in GPIO mode
    Uint16 GPIO57:1;                    // 25 Defines direction for this pin in GPIO mode
    Uint16 GPIO58:1;                    // 26 Defines direction for this pin in GPIO mode
    Uint16 GPIO59:1;                    // 27 Defines direction for this pin in GPIO mode
    Uint16 GPIO60:1;                    // 28 Defines direction for this pin in GPIO mode
    Uint16 GPIO61:1;                    // 29 Defines direction for this pin in GPIO mode
    Uint16 GPIO62:1;                    // 30 Defines direction for this pin in GPIO mode
    Uint16 GPIO63:1;                    // 31 Defines direction for this pin in GPIO mode
};

union GPBDIR_REG {
    Uint32  all;
    struct  GPBDIR_BITS  bit;
};

struct GPBPUD_BITS {                    // bits description
    Uint16 GPIO32:1;                    // 0 Pull-Up Disable control for this pin
    Uint16 GPIO33:1;                    // 1 Pull-Up Disable control for this pin
    Uint16 GPIO34:1;                    // 2 Pull-Up Disable control for this pin
    Uint16 GPIO35:1;                    // 3 Pull-Up Disable control for this pin
    Uint16 rsvd1:1;                     // 4 Reserved
    Uint16 GPIO37:1;                    // 5 Pull-Up Disable control for this pin
    Uint16 rsvd2:1;                     // 6 Reserved
    Uint16 rsvd3:1;                     // 7 Reserved
    Uint16 GPIO40:1;                    // 8 Pull-Up Disable control for this pin
    Uint16 GPIO41:1;                    // 9 Pull-Up Disable control for this pin
    Uint16 GPIO42:1;                    // 10 Pull-Up Disable control for this pin
    Uint16 GPIO43:1;                    // 11 Pull-Up Disable control for this pin
    Uint16 GPIO44:1;                    // 12 Pull-Up Disable control for this pin
    Uint16 GPIO45:1;                    // 13 Pull-Up Disable control for this pin
    Uint16 GPIO46:1;                    // 14 Pull-Up Disable control for this pin
    Uint16 GPIO47:1;                    // 15 Pull-Up Disable control for this pin
    Uint16 GPIO48:1;                    // 16 Pull-Up Disable control for this pin
    Uint16 GPIO49:1;                    // 17 Pull-Up Disable control for this pin
    Uint16 GPIO50:1;                    // 18 Pull-Up Disable control for this pin
    Uint16 GPIO51:1;                    // 19 Pull-Up Disable control for this pin
    Uint16 GPIO52:1;                    // 20 Pull-Up Disable control for this pin
    Uint16 GPIO53:1;                    // 21 Pull-Up Disable control for this pin
    Uint16 GPIO54:1;                    // 22 Pull-Up Disable control for this pin
    Uint16 GPIO55:1;                    // 23 Pull-Up Disable control for this pin
    Uint16 GPIO56:1;                    // 24 Pull-Up Disable control for this pin
    Uint16 GPIO57:1;                    // 25 Pull-Up Disable control for this pin
    Uint16 GPIO58:1;                    // 26 Pull-Up Disable control for this pin
    Uint16 GPIO59:1;                    // 27 Pull-Up Disable control for this pin
    Uint16 GPIO60:1;                    // 28 Pull-Up Disable control for this pin
    Uint16 GPIO61:1;                    // 29 Pull-Up Disable control for this pin
    Uint16 GPIO62:1;                    // 30 Pull-Up Disable control for this pin
    Uint16 GPIO63:1;                    // 31 Pull-Up Disable control for this pin
};

union GPBPUD_REG {
    Uint32  all;
    struct  GPBPUD_BITS  bit;
};

struct GPBINV_BITS {                    // bits description
    Uint16 GPIO32:1;                    // 0 Input inversion control for this pin
    Uint16 GPIO33:1;                    // 1 Input inversion control for this pin
    Uint16 GPIO34:1;                    // 2 Input inversion control for this pin
    Uint16 GPIO35:1;                    // 3 Input inversion control for this pin
    Uint16 rsvd1:1;                     // 4 Reserved
    Uint16 GPIO37:1;                    // 5 Input inversion control for this pin
    Uint16 rsvd2:1;                     // 6 Reserved
    Uint16 rsvd3:1;                     // 7 Reserved
    Uint16 GPIO40:1;                    // 8 Input inversion control for this pin
    Uint16 GPIO41:1;                    // 9 Input inversion control for this pin
    Uint16 GPIO42:1;                    // 10 Input inversion control for this pin
    Uint16 GPIO43:1;                    // 11 Input inversion control for this pin
    Uint16 GPIO44:1;                    // 12 Input inversion control for this pin
    Uint16 GPIO45:1;                    // 13 Input inversion control for this pin
    Uint16 GPIO46:1;                    // 14 Input inversion control for this pin
    Uint16 GPIO47:1;                    // 15 Input inversion control for this pin
    Uint16 GPIO48:1;                    // 16 Input inversion control for this pin
    Uint16 GPIO49:1;                    // 17 Input inversion control for this pin
    Uint16 GPIO50:1;                    // 18 Input inversion control for this pin
    Uint16 GPIO51:1;                    // 19 Input inversion control for this pin
    Uint16 GPIO52:1;                    // 20 Input inversion control for this pin
    Uint16 GPIO53:1;                    // 21 Input inversion control for this pin
    Uint16 GPIO54:1;                    // 22 Input inversion control for this pin
    Uint16 GPIO55:1;                    // 23 Input inversion control for this pin
    Uint16 GPIO56:1;                    // 24 Input inversion control for this pin
    Uint16 GPIO57:1;                    // 25 Input inversion control for this pin
    Uint16 GPIO58:1;                    // 26 Input inversion control for this pin
    Uint16 GPIO59:1;                    // 27 Input inversion control for this pin
    Uint16 GPIO60:1;                    // 28 Input inversion control for this pin
    Uint16 GPIO61:1;                    // 29 Input inversion control for this pin
    Uint16 GPIO62:1;                    // 30 Input inversion control for this pin
    Uint16 GPIO63:1;                    // 31 Input inversion control for this pin
};

union GPBINV_REG {
    Uint32  all;
    struct  GPBINV_BITS  bit;
};

struct GPBODR_BITS {                    // bits description
    Uint16 GPIO32:1;                    // 0 Output Open-Drain control for this pin
    Uint16 GPIO33:1;                    // 1 Output Open-Drain control for this pin
    Uint16 GPIO34:1;                    // 2 Output Open-Drain control for this pin
    Uint16 GPIO35:1;                    // 3 Output Open-Drain control for this pin
    Uint16 rsvd1:1;                     // 4 Reserved
    Uint16 GPIO37:1;                    // 5 Output Open-Drain control for this pin
    Uint16 rsvd2:1;                     // 6 Reserved
    Uint16 rsvd3:1;                     // 7 Reserved
    Uint16 GPIO40:1;                    // 8 Output Open-Drain control for this pin
    Uint16 GPIO41:1;                    // 9 Output Open-Drain control for this pin
    Uint16 GPIO42:1;                    // 10 Output Open-Drain control for this pin
    Uint16 GPIO43:1;                    // 11 Output Open-Drain control for this pin
    Uint16 GPIO44:1;                    // 12 Output Open-Drain control for this pin
    Uint16 GPIO45:1;                    // 13 Output Open-Drain control for this pin
    Uint16 GPIO46:1;                    // 14 Output Open-Drain control for this pin
    Uint16 GPIO47:1;                    // 15 Output Open-Drain control for this pin
    Uint16 GPIO48:1;                    // 16 Output Open-Drain control for this pin
    Uint16 GPIO49:1;                    // 17 Output Open-Drain control for this pin
    Uint16 GPIO50:1;                    // 18 Output Open-Drain control for this pin
    Uint16 GPIO51:1;                    // 19 Output Open-Drain control for this pin
    Uint16 GPIO52:1;                    // 20 Output Open-Drain control for this pin
    Uint16 GPIO53:1;                    // 21 Output Open-Drain control for this pin
    Uint16 GPIO54:1;                    // 22 Output Open-Drain control for this pin
    Uint16 GPIO55:1;                    // 23 Output Open-Drain control for this pin
    Uint16 GPIO56:1;                    // 24 Output Open-Drain control for this pin
    Uint16 GPIO57:1;                    // 25 Output Open-Drain control for this pin
    Uint16 GPIO58:1;                    // 26 Output Open-Drain control for this pin
    Uint16 GPIO59:1;                    // 27 Output Open-Drain control for this pin
    Uint16 GPIO60:1;                    // 28 Output Open-Drain control for this pin
    Uint16 GPIO61:1;                    // 29 Output Open-Drain control for this pin
    Uint16 GPIO62:1;                    // 30 Output Open-Drain control for this pin
    Uint16 GPIO63:1;                    // 31 Output Open-Drain control for this pin
};

union GPBODR_REG {
    Uint32  all;
    struct  GPBODR_BITS  bit;
};

struct GPBAMSEL_BITS {                  // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 GPIO33:1;                    // 1 Analog Mode select for this pin
    Uint16 rsvd2:1;                     // 2 Reserved
    Uint16 rsvd3:1;                     // 3 Reserved
    Uint16 rsvd4:1;                     // 4 Reserved
    Uint16 rsvd5:1;                     // 5 Reserved
    Uint16 rsvd6:1;                     // 6 Reserved
    Uint16 rsvd7:1;                     // 7 Reserved
    Uint16 rsvd8:1;                     // 8 Reserved
    Uint16 GPIO41:1;                    // 9 Analog Mode select for this pin
    Uint16 rsvd9:1;                     // 10 Reserved
    Uint16 rsvd10:1;                    // 11 Reserved
    Uint16 rsvd11:1;                    // 12 Reserved
    Uint16 rsvd12:1;                    // 13 Reserved
    Uint16 rsvd13:1;                    // 14 Reserved
    Uint16 rsvd14:1;                    // 15 Reserved
    Uint16 rsvd15:1;                    // 16 Reserved
    Uint16 rsvd16:1;                    // 17 Reserved
    Uint16 rsvd17:1;                    // 18 Reserved
    Uint16 rsvd18:1;                    // 19 Reserved
    Uint16 rsvd19:1;                    // 20 Reserved
    Uint16 rsvd20:1;                    // 21 Reserved
    Uint16 rsvd21:1;                    // 22 Reserved
    Uint16 rsvd22:1;                    // 23 Reserved
    Uint16 rsvd23:1;                    // 24 Reserved
    Uint16 rsvd24:1;                    // 25 Reserved
    Uint16 rsvd25:1;                    // 26 Reserved
    Uint16 rsvd26:1;                    // 27 Reserved
    Uint16 rsvd27:1;                    // 28 Reserved
    Uint16 rsvd28:1;                    // 29 Reserved
    Uint16 rsvd29:1;                    // 30 Reserved
    Uint16 rsvd30:1;                    // 31 Reserved
};

union GPBAMSEL_REG {
    Uint32  all;
    struct  GPBAMSEL_BITS  bit;
};

struct GPBGMUX1_BITS {                  // bits description
    Uint16 GPIO32:2;                    // 1:0 Defines pin-muxing selection for GPIO32
    Uint16 GPIO33:2;                    // 3:2 Defines pin-muxing selection for GPIO33
    Uint16 GPIO34:2;                    // 5:4 Defines pin-muxing selection for GPIO34
    Uint16 GPIO35:2;                    // 7:6 Defines pin-muxing selection for GPIO35
    Uint16 rsvd1:2;                     // 9:8 Reserved
    Uint16 GPIO37:2;                    // 11:10 Defines pin-muxing selection for GPIO37
    Uint16 rsvd2:2;                     // 13:12 Reserved
    Uint16 rsvd3:2;                     // 15:14 Reserved
    Uint16 GPIO40:2;                    // 17:16 Defines pin-muxing selection for GPIO40
    Uint16 GPIO41:2;                    // 19:18 Defines pin-muxing selection for GPIO41
    Uint16 GPIO42:2;                    // 21:20 Defines pin-muxing selection for GPIO42
    Uint16 GPIO43:2;                    // 23:22 Defines pin-muxing selection for GPIO43
    Uint16 GPIO44:2;                    // 25:24 Defines pin-muxing selection for GPIO44
    Uint16 GPIO45:2;                    // 27:26 Defines pin-muxing selection for GPIO45
    Uint16 GPIO46:2;                    // 29:28 Defines pin-muxing selection for GPIO46
    Uint16 GPIO47:2;                    // 31:30 Defines pin-muxing selection for GPIO47
};

union GPBGMUX1_REG {
    Uint32  all;
    struct  GPBGMUX1_BITS  bit;
};

struct GPBGMUX2_BITS {                  // bits description
    Uint16 GPIO48:2;                    // 1:0 Defines pin-muxing selection for GPIO48
    Uint16 GPIO49:2;                    // 3:2 Defines pin-muxing selection for GPIO49
    Uint16 GPIO50:2;                    // 5:4 Defines pin-muxing selection for GPIO50
    Uint16 GPIO51:2;                    // 7:6 Defines pin-muxing selection for GPIO51
    Uint16 GPIO52:2;                    // 9:8 Defines pin-muxing selection for GPIO52
    Uint16 GPIO53:2;                    // 11:10 Defines pin-muxing selection for GPIO53
    Uint16 GPIO54:2;                    // 13:12 Defines pin-muxing selection for GPIO54
    Uint16 GPIO55:2;                    // 15:14 Defines pin-muxing selection for GPIO55
    Uint16 GPIO56:2;                    // 17:16 Defines pin-muxing selection for GPIO56
    Uint16 GPIO57:2;                    // 19:18 Defines pin-muxing selection for GPIO57
    Uint16 GPIO58:2;                    // 21:20 Defines pin-muxing selection for GPIO58
    Uint16 GPIO59:2;                    // 23:22 Defines pin-muxing selection for GPIO59
    Uint16 GPIO60:2;                    // 25:24 Defines pin-muxing selection for GPIO60
    Uint16 GPIO61:2;                    // 27:26 Defines pin-muxing selection for GPIO61
    Uint16 GPIO62:2;                    // 29:28 Defines pin-muxing selection for GPIO62
    Uint16 GPIO63:2;                    // 31:30 Defines pin-muxing selection for GPIO63
};

union GPBGMUX2_REG {
    Uint32  all;
    struct  GPBGMUX2_BITS  bit;
};

struct GPBCSEL1_BITS {                  // bits description
    Uint16 GPIO32:4;                    // 3:0 GPIO32 Controller CPU Select
    Uint16 GPIO33:4;                    // 7:4 GPIO33 Controller CPU Select
    Uint16 GPIO34:4;                    // 11:8 GPIO34 Controller CPU Select
    Uint16 GPIO35:4;                    // 15:12 GPIO35 Controller CPU Select
    Uint16 rsvd1:4;                     // 19:16 Reserved
    Uint16 GPIO37:4;                    // 23:20 GPIO37 Controller CPU Select
    Uint16 rsvd2:4;                     // 27:24 Reserved
    Uint16 rsvd3:4;                     // 31:28 Reserved
};

union GPBCSEL1_REG {
    Uint32  all;
    struct  GPBCSEL1_BITS  bit;
};

struct GPBCSEL2_BITS {                  // bits description
    Uint16 GPIO40:4;                    // 3:0 GPIO40 Controller CPU Select
    Uint16 GPIO41:4;                    // 7:4 GPIO41 Controller CPU Select
    Uint16 GPIO42:4;                    // 11:8 GPIO42 Controller CPU Select
    Uint16 GPIO43:4;                    // 15:12 GPIO43 Controller CPU Select
    Uint16 GPIO44:4;                    // 19:16 GPIO44 Controller CPU Select
    Uint16 GPIO45:4;                    // 23:20 GPIO45 Controller CPU Select
    Uint16 GPIO46:4;                    // 27:24 GPIO46 Controller CPU Select
    Uint16 GPIO47:4;                    // 31:28 GPIO47 Controller CPU Select
};

union GPBCSEL2_REG {
    Uint32  all;
    struct  GPBCSEL2_BITS  bit;
};

struct GPBCSEL3_BITS {                  // bits description
    Uint16 GPIO48:4;                    // 3:0 GPIO48 Controller CPU Select
    Uint16 GPIO49:4;                    // 7:4 GPIO49 Controller CPU Select
    Uint16 GPIO50:4;                    // 11:8 GPIO50 Controller CPU Select
    Uint16 GPIO51:4;                    // 15:12 GPIO51 Controller CPU Select
    Uint16 GPIO52:4;                    // 19:16 GPIO52 Controller CPU Select
    Uint16 GPIO53:4;                    // 23:20 GPIO53 Controller CPU Select
    Uint16 GPIO54:4;                    // 27:24 GPIO54 Controller CPU Select
    Uint16 GPIO55:4;                    // 31:28 GPIO55 Controller CPU Select
};

union GPBCSEL3_REG {
    Uint32  all;
    struct  GPBCSEL3_BITS  bit;
};

struct GPBCSEL4_BITS {                  // bits description
    Uint16 GPIO56:4;                    // 3:0 GPIO56 Controller CPU Select
    Uint16 GPIO57:4;                    // 7:4 GPIO57 Controller CPU Select
    Uint16 GPIO58:4;                    // 11:8 GPIO58 Controller CPU Select
    Uint16 GPIO59:4;                    // 15:12 GPIO59 Controller CPU Select
    Uint16 GPIO60:4;                    // 19:16 GPIO60 Controller CPU Select
    Uint16 GPIO61:4;                    // 23:20 GPIO61 Controller CPU Select
    Uint16 GPIO62:4;                    // 27:24 GPIO62 Controller CPU Select
    Uint16 GPIO63:4;                    // 31:28 GPIO63 Controller CPU Select
};

union GPBCSEL4_REG {
    Uint32  all;
    struct  GPBCSEL4_BITS  bit;
};

struct GPBLOCK_BITS {                   // bits description
    Uint16 GPIO32:1;                    // 0 Configuration Lock bit for this pin
    Uint16 GPIO33:1;                    // 1 Configuration Lock bit for this pin
    Uint16 GPIO34:1;                    // 2 Configuration Lock bit for this pin
    Uint16 GPIO35:1;                    // 3 Configuration Lock bit for this pin
    Uint16 rsvd1:1;                     // 4 Reserved
    Uint16 GPIO37:1;                    // 5 Configuration Lock bit for this pin
    Uint16 rsvd2:1;                     // 6 Reserved
    Uint16 rsvd3:1;                     // 7 Reserved
    Uint16 GPIO40:1;                    // 8 Configuration Lock bit for this pin
    Uint16 GPIO41:1;                    // 9 Configuration Lock bit for this pin
    Uint16 GPIO42:1;                    // 10 Configuration Lock bit for this pin
    Uint16 GPIO43:1;                    // 11 Configuration Lock bit for this pin
    Uint16 GPIO44:1;                    // 12 Configuration Lock bit for this pin
    Uint16 GPIO45:1;                    // 13 Configuration Lock bit for this pin
    Uint16 GPIO46:1;                    // 14 Configuration Lock bit for this pin
    Uint16 GPIO47:1;                    // 15 Configuration Lock bit for this pin
    Uint16 GPIO48:1;                    // 16 Configuration Lock bit for this pin
    Uint16 GPIO49:1;                    // 17 Configuration Lock bit for this pin
    Uint16 GPIO50:1;                    // 18 Configuration Lock bit for this pin
    Uint16 GPIO51:1;                    // 19 Configuration Lock bit for this pin
    Uint16 GPIO52:1;                    // 20 Configuration Lock bit for this pin
    Uint16 GPIO53:1;                    // 21 Configuration Lock bit for this pin
    Uint16 GPIO54:1;                    // 22 Configuration Lock bit for this pin
    Uint16 GPIO55:1;                    // 23 Configuration Lock bit for this pin
    Uint16 GPIO56:1;                    // 24 Configuration Lock bit for this pin
    Uint16 GPIO57:1;                    // 25 Configuration Lock bit for this pin
    Uint16 GPIO58:1;                    // 26 Configuration Lock bit for this pin
    Uint16 GPIO59:1;                    // 27 Configuration Lock bit for this pin
    Uint16 GPIO60:1;                    // 28 Configuration Lock bit for this pin
    Uint16 GPIO61:1;                    // 29 Configuration Lock bit for this pin
    Uint16 GPIO62:1;                    // 30 Configuration Lock bit for this pin
    Uint16 GPIO63:1;                    // 31 Configuration Lock bit for this pin
};

union GPBLOCK_REG {
    Uint32  all;
    struct  GPBLOCK_BITS  bit;
};

struct GPBCR_BITS {                     // bits description
    Uint16 GPIO32:1;                    // 0 Configuration lock commit bit for this pin
    Uint16 GPIO33:1;                    // 1 Configuration lock commit bit for this pin
    Uint16 GPIO34:1;                    // 2 Configuration lock commit bit for this pin
    Uint16 GPIO35:1;                    // 3 Configuration lock commit bit for this pin
    Uint16 rsvd1:1;                     // 4 Reserved
    Uint16 GPIO37:1;                    // 5 Configuration lock commit bit for this pin
    Uint16 rsvd2:1;                     // 6 Reserved
    Uint16 rsvd3:1;                     // 7 Reserved
    Uint16 GPIO40:1;                    // 8 Configuration lock commit bit for this pin
    Uint16 GPIO41:1;                    // 9 Configuration lock commit bit for this pin
    Uint16 GPIO42:1;                    // 10 Configuration lock commit bit for this pin
    Uint16 GPIO43:1;                    // 11 Configuration lock commit bit for this pin
    Uint16 GPIO44:1;                    // 12 Configuration lock commit bit for this pin
    Uint16 GPIO45:1;                    // 13 Configuration lock commit bit for this pin
    Uint16 GPIO46:1;                    // 14 Configuration lock commit bit for this pin
    Uint16 GPIO47:1;                    // 15 Configuration lock commit bit for this pin
    Uint16 GPIO48:1;                    // 16 Configuration lock commit bit for this pin
    Uint16 GPIO49:1;                    // 17 Configuration lock commit bit for this pin
    Uint16 GPIO50:1;                    // 18 Configuration lock commit bit for this pin
    Uint16 GPIO51:1;                    // 19 Configuration lock commit bit for this pin
    Uint16 GPIO52:1;                    // 20 Configuration lock commit bit for this pin
    Uint16 GPIO53:1;                    // 21 Configuration lock commit bit for this pin
    Uint16 GPIO54:1;                    // 22 Configuration lock commit bit for this pin
    Uint16 GPIO55:1;                    // 23 Configuration lock commit bit for this pin
    Uint16 GPIO56:1;                    // 24 Configuration lock commit bit for this pin
    Uint16 GPIO57:1;                    // 25 Configuration lock commit bit for this pin
    Uint16 GPIO58:1;                    // 26 Configuration lock commit bit for this pin
    Uint16 GPIO59:1;                    // 27 Configuration lock commit bit for this pin
    Uint16 GPIO60:1;                    // 28 Configuration lock commit bit for this pin
    Uint16 GPIO61:1;                    // 29 Configuration lock commit bit for this pin
    Uint16 GPIO62:1;                    // 30 Configuration lock commit bit for this pin
    Uint16 GPIO63:1;                    // 31 Configuration lock commit bit for this pin
};

union GPBCR_REG {
    Uint32  all;
    struct  GPBCR_BITS  bit;
};

struct GPCCTRL_BITS {                   // bits description
    Uint16 QUALPRD0:8;                  // 7:0 Qualification sampling period for GPIO64 to GPIO71
    Uint16 QUALPRD1:8;                  // 15:8 Qualification sampling period for GPIO72 to GPIO79
    Uint16 QUALPRD2:8;                  // 23:16 Qualification sampling period for GPIO80 to GPIO87
    Uint16 rsvd1:8;                     // 31:24 Reserved
};

union GPCCTRL_REG {
    Uint32  all;
    struct  GPCCTRL_BITS  bit;
};

struct GPCQSEL1_BITS {                  // bits description
    Uint16 GPIO64:2;                    // 1:0 Select input qualification type for GPIO64
    Uint16 GPIO65:2;                    // 3:2 Select input qualification type for GPIO65
    Uint16 GPIO66:2;                    // 5:4 Select input qualification type for GPIO66
    Uint16 GPIO67:2;                    // 7:6 Select input qualification type for GPIO67
    Uint16 GPIO68:2;                    // 9:8 Select input qualification type for GPIO68
    Uint16 GPIO69:2;                    // 11:10 Select input qualification type for GPIO69
    Uint16 GPIO70:2;                    // 13:12 Select input qualification type for GPIO70
    Uint16 GPIO71:2;                    // 15:14 Select input qualification type for GPIO71
    Uint16 GPIO72:2;                    // 17:16 Select input qualification type for GPIO72
    Uint16 GPIO73:2;                    // 19:18 Select input qualification type for GPIO73
    Uint16 GPIO74:2;                    // 21:20 Select input qualification type for GPIO74
    Uint16 GPIO75:2;                    // 23:22 Select input qualification type for GPIO75
    Uint16 GPIO76:2;                    // 25:24 Select input qualification type for GPIO76
    Uint16 GPIO77:2;                    // 27:26 Select input qualification type for GPIO77
    Uint16 GPIO78:2;                    // 29:28 Select input qualification type for GPIO78
    Uint16 GPIO79:2;                    // 31:30 Select input qualification type for GPIO79
};

union GPCQSEL1_REG {
    Uint32  all;
    struct  GPCQSEL1_BITS  bit;
};

struct GPCQSEL2_BITS {                  // bits description
    Uint16 GPIO80:2;                    // 1:0 Select input qualification type for GPIO80
    Uint16 GPIO81:2;                    // 3:2 Select input qualification type for GPIO81
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

union GPCQSEL2_REG {
    Uint32  all;
    struct  GPCQSEL2_BITS  bit;
};

struct GPCMUX1_BITS {                   // bits description
    Uint16 GPIO64:2;                    // 1:0 Defines pin-muxing selection for GPIO64
    Uint16 GPIO65:2;                    // 3:2 Defines pin-muxing selection for GPIO65
    Uint16 GPIO66:2;                    // 5:4 Defines pin-muxing selection for GPIO66
    Uint16 GPIO67:2;                    // 7:6 Defines pin-muxing selection for GPIO67
    Uint16 GPIO68:2;                    // 9:8 Defines pin-muxing selection for GPIO68
    Uint16 GPIO69:2;                    // 11:10 Defines pin-muxing selection for GPIO69
    Uint16 GPIO70:2;                    // 13:12 Defines pin-muxing selection for GPIO70
    Uint16 GPIO71:2;                    // 15:14 Defines pin-muxing selection for GPIO71
    Uint16 GPIO72:2;                    // 17:16 Defines pin-muxing selection for GPIO72
    Uint16 GPIO73:2;                    // 19:18 Defines pin-muxing selection for GPIO73
    Uint16 GPIO74:2;                    // 21:20 Defines pin-muxing selection for GPIO74
    Uint16 GPIO75:2;                    // 23:22 Defines pin-muxing selection for GPIO75
    Uint16 GPIO76:2;                    // 25:24 Defines pin-muxing selection for GPIO76
    Uint16 GPIO77:2;                    // 27:26 Defines pin-muxing selection for GPIO77
    Uint16 GPIO78:2;                    // 29:28 Defines pin-muxing selection for GPIO78
    Uint16 GPIO79:2;                    // 31:30 Defines pin-muxing selection for GPIO79
};

union GPCMUX1_REG {
    Uint32  all;
    struct  GPCMUX1_BITS  bit;
};

struct GPCMUX2_BITS {                   // bits description
    Uint16 GPIO80:2;                    // 1:0 Defines pin-muxing selection for GPIO80
    Uint16 GPIO81:2;                    // 3:2 Defines pin-muxing selection for GPIO81
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

union GPCMUX2_REG {
    Uint32  all;
    struct  GPCMUX2_BITS  bit;
};

struct GPCDIR_BITS {                    // bits description
    Uint16 GPIO64:1;                    // 0 Defines direction for this pin in GPIO mode
    Uint16 GPIO65:1;                    // 1 Defines direction for this pin in GPIO mode
    Uint16 GPIO66:1;                    // 2 Defines direction for this pin in GPIO mode
    Uint16 GPIO67:1;                    // 3 Defines direction for this pin in GPIO mode
    Uint16 GPIO68:1;                    // 4 Defines direction for this pin in GPIO mode
    Uint16 GPIO69:1;                    // 5 Defines direction for this pin in GPIO mode
    Uint16 GPIO70:1;                    // 6 Defines direction for this pin in GPIO mode
    Uint16 GPIO71:1;                    // 7 Defines direction for this pin in GPIO mode
    Uint16 GPIO72:1;                    // 8 Defines direction for this pin in GPIO mode
    Uint16 GPIO73:1;                    // 9 Defines direction for this pin in GPIO mode
    Uint16 GPIO74:1;                    // 10 Defines direction for this pin in GPIO mode
    Uint16 GPIO75:1;                    // 11 Defines direction for this pin in GPIO mode
    Uint16 GPIO76:1;                    // 12 Defines direction for this pin in GPIO mode
    Uint16 GPIO77:1;                    // 13 Defines direction for this pin in GPIO mode
    Uint16 GPIO78:1;                    // 14 Defines direction for this pin in GPIO mode
    Uint16 GPIO79:1;                    // 15 Defines direction for this pin in GPIO mode
    Uint16 GPIO80:1;                    // 16 Defines direction for this pin in GPIO mode
    Uint16 GPIO81:1;                    // 17 Defines direction for this pin in GPIO mode
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

union GPCDIR_REG {
    Uint32  all;
    struct  GPCDIR_BITS  bit;
};

struct GPCPUD_BITS {                    // bits description
    Uint16 GPIO64:1;                    // 0 Pull-Up Disable control for this pin
    Uint16 GPIO65:1;                    // 1 Pull-Up Disable control for this pin
    Uint16 GPIO66:1;                    // 2 Pull-Up Disable control for this pin
    Uint16 GPIO67:1;                    // 3 Pull-Up Disable control for this pin
    Uint16 GPIO68:1;                    // 4 Pull-Up Disable control for this pin
    Uint16 GPIO69:1;                    // 5 Pull-Up Disable control for this pin
    Uint16 GPIO70:1;                    // 6 Pull-Up Disable control for this pin
    Uint16 GPIO71:1;                    // 7 Pull-Up Disable control for this pin
    Uint16 GPIO72:1;                    // 8 Pull-Up Disable control for this pin
    Uint16 GPIO73:1;                    // 9 Pull-Up Disable control for this pin
    Uint16 GPIO74:1;                    // 10 Pull-Up Disable control for this pin
    Uint16 GPIO75:1;                    // 11 Pull-Up Disable control for this pin
    Uint16 GPIO76:1;                    // 12 Pull-Up Disable control for this pin
    Uint16 GPIO77:1;                    // 13 Pull-Up Disable control for this pin
    Uint16 GPIO78:1;                    // 14 Pull-Up Disable control for this pin
    Uint16 GPIO79:1;                    // 15 Pull-Up Disable control for this pin
    Uint16 GPIO80:1;                    // 16 Pull-Up Disable control for this pin
    Uint16 GPIO81:1;                    // 17 Pull-Up Disable control for this pin
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

union GPCPUD_REG {
    Uint32  all;
    struct  GPCPUD_BITS  bit;
};

struct GPCINV_BITS {                    // bits description
    Uint16 GPIO64:1;                    // 0 Input inversion control for this pin
    Uint16 GPIO65:1;                    // 1 Input inversion control for this pin
    Uint16 GPIO66:1;                    // 2 Input inversion control for this pin
    Uint16 GPIO67:1;                    // 3 Input inversion control for this pin
    Uint16 GPIO68:1;                    // 4 Input inversion control for this pin
    Uint16 GPIO69:1;                    // 5 Input inversion control for this pin
    Uint16 GPIO70:1;                    // 6 Input inversion control for this pin
    Uint16 GPIO71:1;                    // 7 Input inversion control for this pin
    Uint16 GPIO72:1;                    // 8 Input inversion control for this pin
    Uint16 GPIO73:1;                    // 9 Input inversion control for this pin
    Uint16 GPIO74:1;                    // 10 Input inversion control for this pin
    Uint16 GPIO75:1;                    // 11 Input inversion control for this pin
    Uint16 GPIO76:1;                    // 12 Input inversion control for this pin
    Uint16 GPIO77:1;                    // 13 Input inversion control for this pin
    Uint16 GPIO78:1;                    // 14 Input inversion control for this pin
    Uint16 GPIO79:1;                    // 15 Input inversion control for this pin
    Uint16 GPIO80:1;                    // 16 Input inversion control for this pin
    Uint16 GPIO81:1;                    // 17 Input inversion control for this pin
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

union GPCINV_REG {
    Uint32  all;
    struct  GPCINV_BITS  bit;
};

struct GPCODR_BITS {                    // bits description
    Uint16 GPIO64:1;                    // 0 Output Open-Drain control for this pin
    Uint16 GPIO65:1;                    // 1 Output Open-Drain control for this pin
    Uint16 GPIO66:1;                    // 2 Output Open-Drain control for this pin
    Uint16 GPIO67:1;                    // 3 Output Open-Drain control for this pin
    Uint16 GPIO68:1;                    // 4 Output Open-Drain control for this pin
    Uint16 GPIO69:1;                    // 5 Output Open-Drain control for this pin
    Uint16 GPIO70:1;                    // 6 Output Open-Drain control for this pin
    Uint16 GPIO71:1;                    // 7 Output Open-Drain control for this pin
    Uint16 GPIO72:1;                    // 8 Output Open-Drain control for this pin
    Uint16 GPIO73:1;                    // 9 Output Open-Drain control for this pin
    Uint16 GPIO74:1;                    // 10 Output Open-Drain control for this pin
    Uint16 GPIO75:1;                    // 11 Output Open-Drain control for this pin
    Uint16 GPIO76:1;                    // 12 Output Open-Drain control for this pin
    Uint16 GPIO77:1;                    // 13 Output Open-Drain control for this pin
    Uint16 GPIO78:1;                    // 14 Output Open-Drain control for this pin
    Uint16 GPIO79:1;                    // 15 Output Open-Drain control for this pin
    Uint16 GPIO80:1;                    // 16 Output Open-Drain control for this pin
    Uint16 GPIO81:1;                    // 17 Output Open-Drain control for this pin
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

union GPCODR_REG {
    Uint32  all;
    struct  GPCODR_BITS  bit;
};

struct GPCGMUX1_BITS {                  // bits description
    Uint16 GPIO64:2;                    // 1:0 Defines pin-muxing selection for GPIO64
    Uint16 GPIO65:2;                    // 3:2 Defines pin-muxing selection for GPIO65
    Uint16 GPIO66:2;                    // 5:4 Defines pin-muxing selection for GPIO66
    Uint16 GPIO67:2;                    // 7:6 Defines pin-muxing selection for GPIO67
    Uint16 GPIO68:2;                    // 9:8 Defines pin-muxing selection for GPIO68
    Uint16 GPIO69:2;                    // 11:10 Defines pin-muxing selection for GPIO69
    Uint16 GPIO70:2;                    // 13:12 Defines pin-muxing selection for GPIO70
    Uint16 GPIO71:2;                    // 15:14 Defines pin-muxing selection for GPIO71
    Uint16 GPIO72:2;                    // 17:16 Defines pin-muxing selection for GPIO72
    Uint16 GPIO73:2;                    // 19:18 Defines pin-muxing selection for GPIO73
    Uint16 GPIO74:2;                    // 21:20 Defines pin-muxing selection for GPIO74
    Uint16 GPIO75:2;                    // 23:22 Defines pin-muxing selection for GPIO75
    Uint16 GPIO76:2;                    // 25:24 Defines pin-muxing selection for GPIO76
    Uint16 GPIO77:2;                    // 27:26 Defines pin-muxing selection for GPIO77
    Uint16 GPIO78:2;                    // 29:28 Defines pin-muxing selection for GPIO78
    Uint16 GPIO79:2;                    // 31:30 Defines pin-muxing selection for GPIO79
};

union GPCGMUX1_REG {
    Uint32  all;
    struct  GPCGMUX1_BITS  bit;
};

struct GPCGMUX2_BITS {                  // bits description
    Uint16 GPIO80:2;                    // 1:0 Defines pin-muxing selection for GPIO80
    Uint16 GPIO81:2;                    // 3:2 Defines pin-muxing selection for GPIO81
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

union GPCGMUX2_REG {
    Uint32  all;
    struct  GPCGMUX2_BITS  bit;
};

struct GPCCSEL1_BITS {                  // bits description
    Uint16 GPIO64:4;                    // 3:0 GPIO64 Controller CPU Select
    Uint16 GPIO65:4;                    // 7:4 GPIO65 Controller CPU Select
    Uint16 GPIO66:4;                    // 11:8 GPIO66 Controller CPU Select
    Uint16 GPIO67:4;                    // 15:12 GPIO67 Controller CPU Select
    Uint16 GPIO68:4;                    // 19:16 GPIO68 Controller CPU Select
    Uint16 GPIO69:4;                    // 23:20 GPIO69 Controller CPU Select
    Uint16 GPIO70:4;                    // 27:24 GPIO70 Controller CPU Select
    Uint16 GPIO71:4;                    // 31:28 GPIO71 Controller CPU Select
};

union GPCCSEL1_REG {
    Uint32  all;
    struct  GPCCSEL1_BITS  bit;
};

struct GPCCSEL2_BITS {                  // bits description
    Uint16 GPIO72:4;                    // 3:0 GPIO72 Controller CPU Select
    Uint16 GPIO73:4;                    // 7:4 GPIO73 Controller CPU Select
    Uint16 GPIO74:4;                    // 11:8 GPIO74 Controller CPU Select
    Uint16 GPIO75:4;                    // 15:12 GPIO75 Controller CPU Select
    Uint16 GPIO76:4;                    // 19:16 GPIO76 Controller CPU Select
    Uint16 GPIO77:4;                    // 23:20 GPIO77 Controller CPU Select
    Uint16 GPIO78:4;                    // 27:24 GPIO78 Controller CPU Select
    Uint16 GPIO79:4;                    // 31:28 GPIO79 Controller CPU Select
};

union GPCCSEL2_REG {
    Uint32  all;
    struct  GPCCSEL2_BITS  bit;
};

struct GPCCSEL3_BITS {                  // bits description
    Uint16 GPIO80:4;                    // 3:0 GPIO80 Controller CPU Select
    Uint16 GPIO81:4;                    // 7:4 GPIO81 Controller CPU Select
    Uint16 rsvd1:4;                     // 11:8 Reserved
    Uint16 rsvd2:4;                     // 15:12 Reserved
    Uint16 rsvd3:4;                     // 19:16 Reserved
    Uint16 rsvd4:4;                     // 23:20 Reserved
    Uint16 rsvd5:4;                     // 27:24 Reserved
    Uint16 rsvd6:4;                     // 31:28 Reserved
};

union GPCCSEL3_REG {
    Uint32  all;
    struct  GPCCSEL3_BITS  bit;
};

struct GPCLOCK_BITS {                   // bits description
    Uint16 GPIO64:1;                    // 0 Configuration Lock bit for this pin
    Uint16 GPIO65:1;                    // 1 Configuration Lock bit for this pin
    Uint16 GPIO66:1;                    // 2 Configuration Lock bit for this pin
    Uint16 GPIO67:1;                    // 3 Configuration Lock bit for this pin
    Uint16 GPIO68:1;                    // 4 Configuration Lock bit for this pin
    Uint16 GPIO69:1;                    // 5 Configuration Lock bit for this pin
    Uint16 GPIO70:1;                    // 6 Configuration Lock bit for this pin
    Uint16 GPIO71:1;                    // 7 Configuration Lock bit for this pin
    Uint16 GPIO72:1;                    // 8 Configuration Lock bit for this pin
    Uint16 GPIO73:1;                    // 9 Configuration Lock bit for this pin
    Uint16 GPIO74:1;                    // 10 Configuration Lock bit for this pin
    Uint16 GPIO75:1;                    // 11 Configuration Lock bit for this pin
    Uint16 GPIO76:1;                    // 12 Configuration Lock bit for this pin
    Uint16 GPIO77:1;                    // 13 Configuration Lock bit for this pin
    Uint16 GPIO78:1;                    // 14 Configuration Lock bit for this pin
    Uint16 GPIO79:1;                    // 15 Configuration Lock bit for this pin
    Uint16 GPIO80:1;                    // 16 Configuration Lock bit for this pin
    Uint16 GPIO81:1;                    // 17 Configuration Lock bit for this pin
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

union GPCLOCK_REG {
    Uint32  all;
    struct  GPCLOCK_BITS  bit;
};

struct GPCCR_BITS {                     // bits description
    Uint16 GPIO64:1;                    // 0 Configuration lock commit bit for this pin
    Uint16 GPIO65:1;                    // 1 Configuration lock commit bit for this pin
    Uint16 GPIO66:1;                    // 2 Configuration lock commit bit for this pin
    Uint16 GPIO67:1;                    // 3 Configuration lock commit bit for this pin
    Uint16 GPIO68:1;                    // 4 Configuration lock commit bit for this pin
    Uint16 GPIO69:1;                    // 5 Configuration lock commit bit for this pin
    Uint16 GPIO70:1;                    // 6 Configuration lock commit bit for this pin
    Uint16 GPIO71:1;                    // 7 Configuration lock commit bit for this pin
    Uint16 GPIO72:1;                    // 8 Configuration lock commit bit for this pin
    Uint16 GPIO73:1;                    // 9 Configuration lock commit bit for this pin
    Uint16 GPIO74:1;                    // 10 Configuration lock commit bit for this pin
    Uint16 GPIO75:1;                    // 11 Configuration lock commit bit for this pin
    Uint16 GPIO76:1;                    // 12 Configuration lock commit bit for this pin
    Uint16 GPIO77:1;                    // 13 Configuration lock commit bit for this pin
    Uint16 GPIO78:1;                    // 14 Configuration lock commit bit for this pin
    Uint16 GPIO79:1;                    // 15 Configuration lock commit bit for this pin
    Uint16 GPIO80:1;                    // 16 Configuration lock commit bit for this pin
    Uint16 GPIO81:1;                    // 17 Configuration lock commit bit for this pin
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

union GPCCR_REG {
    Uint32  all;
    struct  GPCCR_BITS  bit;
};

struct GPGCTRL_BITS {                   // bits description
    Uint16 rsvd1:8;                     // 7:0 Reserved
    Uint16 rsvd2:8;                     // 15:8 Reserved
    Uint16 QUALPRD2:8;                  // 23:16 Qualification sampling period for GPIO208 to GPIO215
    Uint16 rsvd3:8;                     // 31:24 Reserved
};

union GPGCTRL_REG {
    Uint32  all;
    struct  GPGCTRL_BITS  bit;
};

struct GPGQSEL2_BITS {                  // bits description
    Uint16 GPIO208:2;                   // 1:0 Select input qualification type for GPIO208
    Uint16 GPIO209:2;                   // 3:2 Select input qualification type for GPIO209
    Uint16 GPIO210:2;                   // 5:4 Select input qualification type for GPIO210
    Uint16 GPIO211:2;                   // 7:6 Select input qualification type for GPIO211
    Uint16 GPIO212:2;                   // 9:8 Select input qualification type for GPIO212
    Uint16 GPIO213:2;                   // 11:10 Select input qualification type for GPIO213
    Uint16 GPIO214:2;                   // 13:12 Select input qualification type for GPIO214
    Uint16 GPIO215:2;                   // 15:14 Select input qualification type for GPIO215
    Uint16 rsvd1:2;                     // 17:16 Reserved
    Uint16 rsvd2:2;                     // 19:18 Reserved
    Uint16 rsvd3:2;                     // 21:20 Reserved
    Uint16 rsvd4:2;                     // 23:22 Reserved
    Uint16 rsvd5:2;                     // 25:24 Reserved
    Uint16 rsvd6:2;                     // 27:26 Reserved
    Uint16 rsvd7:2;                     // 29:28 Reserved
    Uint16 rsvd8:2;                     // 31:30 Reserved
};

union GPGQSEL2_REG {
    Uint32  all;
    struct  GPGQSEL2_BITS  bit;
};

struct GPGMUX2_BITS {                   // bits description
    Uint16 GPIO208:2;                   // 1:0 Defines pin-muxing selection for GPIO208
    Uint16 GPIO209:2;                   // 3:2 Defines pin-muxing selection for GPIO209
    Uint16 GPIO210:2;                   // 5:4 Defines pin-muxing selection for GPIO210
    Uint16 GPIO211:2;                   // 7:6 Defines pin-muxing selection for GPIO211
    Uint16 GPIO212:2;                   // 9:8 Defines pin-muxing selection for GPIO212
    Uint16 GPIO213:2;                   // 11:10 Defines pin-muxing selection for GPIO213
    Uint16 GPIO214:2;                   // 13:12 Defines pin-muxing selection for GPIO214
    Uint16 GPIO215:2;                   // 15:14 Defines pin-muxing selection for GPIO215
    Uint16 rsvd1:2;                     // 17:16 Reserved
    Uint16 rsvd2:2;                     // 19:18 Reserved
    Uint16 rsvd3:2;                     // 21:20 Reserved
    Uint16 rsvd4:2;                     // 23:22 Reserved
    Uint16 rsvd5:2;                     // 25:24 Reserved
    Uint16 rsvd6:2;                     // 27:26 Reserved
    Uint16 rsvd7:2;                     // 29:28 Reserved
    Uint16 rsvd8:2;                     // 31:30 Reserved
};

union GPGMUX2_REG {
    Uint32  all;
    struct  GPGMUX2_BITS  bit;
};

struct GPGDIR_BITS {                    // bits description
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
    Uint16 rsvd13:1;                    // 12 Reserved
    Uint16 rsvd14:1;                    // 13 Reserved
    Uint16 rsvd15:1;                    // 14 Reserved
    Uint16 rsvd16:1;                    // 15 Reserved
    Uint16 GPIO208:1;                   // 16 Defines direction for this pin in GPIO mode
    Uint16 GPIO209:1;                   // 17 Defines direction for this pin in GPIO mode
    Uint16 GPIO210:1;                   // 18 Defines direction for this pin in GPIO mode
    Uint16 GPIO211:1;                   // 19 Defines direction for this pin in GPIO mode
    Uint16 GPIO212:1;                   // 20 Defines direction for this pin in GPIO mode
    Uint16 GPIO213:1;                   // 21 Defines direction for this pin in GPIO mode
    Uint16 GPIO214:1;                   // 22 Defines direction for this pin in GPIO mode
    Uint16 GPIO215:1;                   // 23 Defines direction for this pin in GPIO mode
    Uint16 rsvd17:1;                    // 24 Reserved
    Uint16 rsvd18:1;                    // 25 Reserved
    Uint16 rsvd19:1;                    // 26 Reserved
    Uint16 rsvd20:1;                    // 27 Reserved
    Uint16 rsvd21:1;                    // 28 Reserved
    Uint16 rsvd22:1;                    // 29 Reserved
    Uint16 rsvd23:1;                    // 30 Reserved
    Uint16 rsvd24:1;                    // 31 Reserved
};

union GPGDIR_REG {
    Uint32  all;
    struct  GPGDIR_BITS  bit;
};

struct GPGPUD_BITS {                    // bits description
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
    Uint16 rsvd13:1;                    // 12 Reserved
    Uint16 rsvd14:1;                    // 13 Reserved
    Uint16 rsvd15:1;                    // 14 Reserved
    Uint16 rsvd16:1;                    // 15 Reserved
    Uint16 GPIO208:1;                   // 16 Pull-Up Disable control for this pin
    Uint16 GPIO209:1;                   // 17 Pull-Up Disable control for this pin
    Uint16 GPIO210:1;                   // 18 Pull-Up Disable control for this pin
    Uint16 GPIO211:1;                   // 19 Pull-Up Disable control for this pin
    Uint16 GPIO212:1;                   // 20 Pull-Up Disable control for this pin
    Uint16 GPIO213:1;                   // 21 Pull-Up Disable control for this pin
    Uint16 GPIO214:1;                   // 22 Pull-Up Disable control for this pin
    Uint16 GPIO215:1;                   // 23 Pull-Up Disable control for this pin
    Uint16 rsvd17:1;                    // 24 Reserved
    Uint16 rsvd18:1;                    // 25 Reserved
    Uint16 rsvd19:1;                    // 26 Reserved
    Uint16 rsvd20:1;                    // 27 Reserved
    Uint16 rsvd21:1;                    // 28 Reserved
    Uint16 rsvd22:1;                    // 29 Reserved
    Uint16 rsvd23:1;                    // 30 Reserved
    Uint16 rsvd24:1;                    // 31 Reserved
};

union GPGPUD_REG {
    Uint32  all;
    struct  GPGPUD_BITS  bit;
};

struct GPGINV_BITS {                    // bits description
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
    Uint16 rsvd13:1;                    // 12 Reserved
    Uint16 rsvd14:1;                    // 13 Reserved
    Uint16 rsvd15:1;                    // 14 Reserved
    Uint16 rsvd16:1;                    // 15 Reserved
    Uint16 GPIO208:1;                   // 16 Input inversion control for this pin
    Uint16 GPIO209:1;                   // 17 Input inversion control for this pin
    Uint16 GPIO210:1;                   // 18 Input inversion control for this pin
    Uint16 GPIO211:1;                   // 19 Input inversion control for this pin
    Uint16 GPIO212:1;                   // 20 Input inversion control for this pin
    Uint16 GPIO213:1;                   // 21 Input inversion control for this pin
    Uint16 GPIO214:1;                   // 22 Input inversion control for this pin
    Uint16 GPIO215:1;                   // 23 Input inversion control for this pin
    Uint16 rsvd17:1;                    // 24 Reserved
    Uint16 rsvd18:1;                    // 25 Reserved
    Uint16 rsvd19:1;                    // 26 Reserved
    Uint16 rsvd20:1;                    // 27 Reserved
    Uint16 rsvd21:1;                    // 28 Reserved
    Uint16 rsvd22:1;                    // 29 Reserved
    Uint16 rsvd23:1;                    // 30 Reserved
    Uint16 rsvd24:1;                    // 31 Reserved
};

union GPGINV_REG {
    Uint32  all;
    struct  GPGINV_BITS  bit;
};

struct GPGODR_BITS {                    // bits description
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
    Uint16 rsvd13:1;                    // 12 Reserved
    Uint16 rsvd14:1;                    // 13 Reserved
    Uint16 rsvd15:1;                    // 14 Reserved
    Uint16 rsvd16:1;                    // 15 Reserved
    Uint16 GPIO208:1;                   // 16 Output Open-Drain control for this pin
    Uint16 GPIO209:1;                   // 17 Output Open-Drain control for this pin
    Uint16 GPIO210:1;                   // 18 Output Open-Drain control for this pin
    Uint16 GPIO211:1;                   // 19 Output Open-Drain control for this pin
    Uint16 GPIO212:1;                   // 20 Output Open-Drain control for this pin
    Uint16 GPIO213:1;                   // 21 Output Open-Drain control for this pin
    Uint16 GPIO214:1;                   // 22 Output Open-Drain control for this pin
    Uint16 GPIO215:1;                   // 23 Output Open-Drain control for this pin
    Uint16 rsvd17:1;                    // 24 Reserved
    Uint16 rsvd18:1;                    // 25 Reserved
    Uint16 rsvd19:1;                    // 26 Reserved
    Uint16 rsvd20:1;                    // 27 Reserved
    Uint16 rsvd21:1;                    // 28 Reserved
    Uint16 rsvd22:1;                    // 29 Reserved
    Uint16 rsvd23:1;                    // 30 Reserved
    Uint16 rsvd24:1;                    // 31 Reserved
};

union GPGODR_REG {
    Uint32  all;
    struct  GPGODR_BITS  bit;
};

struct GPGAMSEL_BITS {                  // bits description
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
    Uint16 rsvd13:1;                    // 12 Reserved
    Uint16 rsvd14:1;                    // 13 Reserved
    Uint16 rsvd15:1;                    // 14 Reserved
    Uint16 rsvd16:1;                    // 15 Reserved
    Uint16 GPIO208:1;                   // 16 Analog Mode select for this pin
    Uint16 GPIO209:1;                   // 17 Analog Mode select for this pin
    Uint16 GPIO210:1;                   // 18 Analog Mode select for this pin
    Uint16 GPIO211:1;                   // 19 Analog Mode select for this pin
    Uint16 GPIO212:1;                   // 20 Analog Mode select for this pin
    Uint16 GPIO213:1;                   // 21 Analog Mode select for this pin
    Uint16 GPIO214:1;                   // 22 Analog Mode select for this pin
    Uint16 GPIO215:1;                   // 23 Analog Mode select for this pin
    Uint16 rsvd17:1;                    // 24 Reserved
    Uint16 rsvd18:1;                    // 25 Reserved
    Uint16 rsvd19:1;                    // 26 Reserved
    Uint16 rsvd20:1;                    // 27 Reserved
    Uint16 rsvd21:1;                    // 28 Reserved
    Uint16 rsvd22:1;                    // 29 Reserved
    Uint16 rsvd23:1;                    // 30 Reserved
    Uint16 rsvd24:1;                    // 31 Reserved
};

union GPGAMSEL_REG {
    Uint32  all;
    struct  GPGAMSEL_BITS  bit;
};

struct GPGGMUX2_BITS {                  // bits description
    Uint16 GPIO208:2;                   // 1:0 Defines pin-muxing selection for GPIO208
    Uint16 GPIO209:2;                   // 3:2 Defines pin-muxing selection for GPIO209
    Uint16 GPIO210:2;                   // 5:4 Defines pin-muxing selection for GPIO210
    Uint16 GPIO211:2;                   // 7:6 Defines pin-muxing selection for GPIO211
    Uint16 GPIO212:2;                   // 9:8 Defines pin-muxing selection for GPIO212
    Uint16 GPIO213:2;                   // 11:10 Defines pin-muxing selection for GPIO213
    Uint16 GPIO214:2;                   // 13:12 Defines pin-muxing selection for GPIO214
    Uint16 GPIO215:2;                   // 15:14 Defines pin-muxing selection for GPIO215
    Uint16 rsvd1:2;                     // 17:16 Reserved
    Uint16 rsvd2:2;                     // 19:18 Reserved
    Uint16 rsvd3:2;                     // 21:20 Reserved
    Uint16 rsvd4:2;                     // 23:22 Reserved
    Uint16 rsvd5:2;                     // 25:24 Reserved
    Uint16 rsvd6:2;                     // 27:26 Reserved
    Uint16 rsvd7:2;                     // 29:28 Reserved
    Uint16 rsvd8:2;                     // 31:30 Reserved
};

union GPGGMUX2_REG {
    Uint32  all;
    struct  GPGGMUX2_BITS  bit;
};

struct GPGCSEL3_BITS {                  // bits description
    Uint16 GPIO208:4;                   // 3:0 GPIO208 Controller CPU Select
    Uint16 GPIO209:4;                   // 7:4 GPIO209 Controller CPU Select
    Uint16 GPIO210:4;                   // 11:8 GPIO210 Controller CPU Select
    Uint16 GPIO211:4;                   // 15:12 GPIO211 Controller CPU Select
    Uint16 GPIO212:4;                   // 19:16 GPIO212 Controller CPU Select
    Uint16 GPIO213:4;                   // 23:20 GPIO213 Controller CPU Select
    Uint16 GPIO214:4;                   // 27:24 GPIO214 Controller CPU Select
    Uint16 GPIO215:4;                   // 31:28 GPIO215 Controller CPU Select
};

union GPGCSEL3_REG {
    Uint32  all;
    struct  GPGCSEL3_BITS  bit;
};

struct GPGLOCK_BITS {                   // bits description
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
    Uint16 rsvd13:1;                    // 12 Reserved
    Uint16 rsvd14:1;                    // 13 Reserved
    Uint16 rsvd15:1;                    // 14 Reserved
    Uint16 rsvd16:1;                    // 15 Reserved
    Uint16 GPIO208:1;                   // 16 Configuration Lock bit for this pin
    Uint16 GPIO209:1;                   // 17 Configuration Lock bit for this pin
    Uint16 GPIO210:1;                   // 18 Configuration Lock bit for this pin
    Uint16 GPIO211:1;                   // 19 Configuration Lock bit for this pin
    Uint16 GPIO212:1;                   // 20 Configuration Lock bit for this pin
    Uint16 GPIO213:1;                   // 21 Configuration Lock bit for this pin
    Uint16 GPIO214:1;                   // 22 Configuration Lock bit for this pin
    Uint16 GPIO215:1;                   // 23 Configuration Lock bit for this pin
    Uint16 rsvd17:1;                    // 24 Reserved
    Uint16 rsvd18:1;                    // 25 Reserved
    Uint16 rsvd19:1;                    // 26 Reserved
    Uint16 rsvd20:1;                    // 27 Reserved
    Uint16 rsvd21:1;                    // 28 Reserved
    Uint16 rsvd22:1;                    // 29 Reserved
    Uint16 rsvd23:1;                    // 30 Reserved
    Uint16 rsvd24:1;                    // 31 Reserved
};

union GPGLOCK_REG {
    Uint32  all;
    struct  GPGLOCK_BITS  bit;
};

struct GPGCR_BITS {                     // bits description
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
    Uint16 rsvd13:1;                    // 12 Reserved
    Uint16 rsvd14:1;                    // 13 Reserved
    Uint16 rsvd15:1;                    // 14 Reserved
    Uint16 rsvd16:1;                    // 15 Reserved
    Uint16 GPIO208:1;                   // 16 Configuration lock commit bit for this pin
    Uint16 GPIO209:1;                   // 17 Configuration lock commit bit for this pin
    Uint16 GPIO210:1;                   // 18 Configuration lock commit bit for this pin
    Uint16 GPIO211:1;                   // 19 Configuration lock commit bit for this pin
    Uint16 GPIO212:1;                   // 20 Configuration lock commit bit for this pin
    Uint16 GPIO213:1;                   // 21 Configuration lock commit bit for this pin
    Uint16 GPIO214:1;                   // 22 Configuration lock commit bit for this pin
    Uint16 GPIO215:1;                   // 23 Configuration lock commit bit for this pin
    Uint16 rsvd17:1;                    // 24 Reserved
    Uint16 rsvd18:1;                    // 25 Reserved
    Uint16 rsvd19:1;                    // 26 Reserved
    Uint16 rsvd20:1;                    // 27 Reserved
    Uint16 rsvd21:1;                    // 28 Reserved
    Uint16 rsvd22:1;                    // 29 Reserved
    Uint16 rsvd23:1;                    // 30 Reserved
    Uint16 rsvd24:1;                    // 31 Reserved
};

union GPGCR_REG {
    Uint32  all;
    struct  GPGCR_BITS  bit;
};

struct GPHCTRL_BITS {                   // bits description
    Uint16 QUALPRD0:8;                  // 7:0 Qualification sampling period for GPIO224 to GPIO231
    Uint16 QUALPRD1:8;                  // 15:8 Qualification sampling period for GPIO232 to GPIO239
    Uint16 QUALPRD2:8;                  // 23:16 Qualification sampling period for GPIO240 to GPIO247
    Uint16 QUALPRD3:8;                  // 31:24 Qualification sampling period for GPIO248 to GPIO255
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
    Uint16 GPIO229:2;                   // 11:10 Select input qualification type for this GPIO Pin
    Uint16 GPIO230:2;                   // 13:12 Select input qualification type for this GPIO Pin
    Uint16 GPIO231:2;                   // 15:14 Select input qualification type for this GPIO Pin
    Uint16 GPIO232:2;                   // 17:16 Select input qualification type for this GPIO Pin
    Uint16 GPIO233:2;                   // 19:18 Select input qualification type for this GPIO Pin
    Uint16 GPIO234:2;                   // 21:20 Select input qualification type for this GPIO Pin
    Uint16 GPIO235:2;                   // 23:22 Select input qualification type for this GPIO Pin
    Uint16 GPIO236:2;                   // 25:24 Select input qualification type for this GPIO Pin
    Uint16 GPIO237:2;                   // 27:26 Select input qualification type for this GPIO Pin
    Uint16 GPIO238:2;                   // 29:28 Select input qualification type for this GPIO Pin
    Uint16 GPIO239:2;                   // 31:30 Select input qualification type for this GPIO Pin
};

union GPHQSEL1_REG {
    Uint32  all;
    struct  GPHQSEL1_BITS  bit;
};

struct GPHQSEL2_BITS {                  // bits description
    Uint16 GPIO240:2;                   // 1:0 Select input qualification type for this GPIO Pin
    Uint16 GPIO241:2;                   // 3:2 Select input qualification type for this GPIO Pin
    Uint16 GPIO242:2;                   // 5:4 Select input qualification type for this GPIO Pin
    Uint16 rsvd1:2;                     // 7:6 Reserved
    Uint16 GPIO244:2;                   // 9:8 Select input qualification type for this GPIO Pin
    Uint16 GPIO245:2;                   // 11:10 Select input qualification type for this GPIO Pin
    Uint16 rsvd2:2;                     // 13:12 Reserved
    Uint16 GPIO247:2;                   // 15:14 Select input qualification type for this GPIO Pin
    Uint16 GPIO248:2;                   // 17:16 Select input qualification type for this GPIO Pin
    Uint16 GPIO249:2;                   // 19:18 Select input qualification type for this GPIO Pin
    Uint16 rsvd3:2;                     // 21:20 Reserved
    Uint16 GPIO251:2;                   // 23:22 Select input qualification type for this GPIO Pin
    Uint16 GPIO252:2;                   // 25:24 Select input qualification type for this GPIO Pin
    Uint16 GPIO253:2;                   // 27:26 Select input qualification type for this GPIO Pin
    Uint16 rsvd4:2;                     // 29:28 Reserved
    Uint16 rsvd5:2;                     // 31:30 Reserved
};

union GPHQSEL2_REG {
    Uint32  all;
    struct  GPHQSEL2_BITS  bit;
};

struct GPHMUX1_BITS {                   // bits description
    Uint16 GPIO224:2;                   // 1:0 Defines pin-muxing selection for GPIO224
    Uint16 GPIO225:2;                   // 3:2 Defines pin-muxing selection for GPIO225
    Uint16 GPIO226:2;                   // 5:4 Defines pin-muxing selection for GPIO226
    Uint16 GPIO227:2;                   // 7:6 Defines pin-muxing selection for GPIO227
    Uint16 GPIO228:2;                   // 9:8 Defines pin-muxing selection for GPIO228
    Uint16 GPIO229:2;                   // 11:10 Defines pin-muxing selection for GPIO229
    Uint16 GPIO230:2;                   // 13:12 Defines pin-muxing selection for GPIO230
    Uint16 GPIO231:2;                   // 15:14 Defines pin-muxing selection for GPIO231
    Uint16 GPIO232:2;                   // 17:16 Defines pin-muxing selection for GPIO232
    Uint16 GPIO233:2;                   // 19:18 Defines pin-muxing selection for GPIO233
    Uint16 GPIO234:2;                   // 21:20 Defines pin-muxing selection for GPIO234
    Uint16 GPIO235:2;                   // 23:22 Defines pin-muxing selection for GPIO235
    Uint16 GPIO236:2;                   // 25:24 Defines pin-muxing selection for GPIO236
    Uint16 GPIO237:2;                   // 27:26 Defines pin-muxing selection for GPIO237
    Uint16 GPIO238:2;                   // 29:28 Defines pin-muxing selection for GPIO238
    Uint16 GPIO239:2;                   // 31:30 Defines pin-muxing selection for GPIO239
};

union GPHMUX1_REG {
    Uint32  all;
    struct  GPHMUX1_BITS  bit;
};

struct GPHMUX2_BITS {                   // bits description
    Uint16 GPIO240:2;                   // 1:0 Defines pin-muxing selection for GPIO240
    Uint16 GPIO241:2;                   // 3:2 Defines pin-muxing selection for GPIO241
    Uint16 GPIO242:2;                   // 5:4 Defines pin-muxing selection for GPIO242
    Uint16 rsvd1:2;                     // 7:6 Reserved
    Uint16 GPIO244:2;                   // 9:8 Defines pin-muxing selection for GPIO244
    Uint16 GPIO245:2;                   // 11:10 Defines pin-muxing selection for GPIO245
    Uint16 rsvd2:2;                     // 13:12 Reserved
    Uint16 GPIO247:2;                   // 15:14 Defines pin-muxing selection for GPIO247
    Uint16 GPIO248:2;                   // 17:16 Defines pin-muxing selection for GPIO248
    Uint16 GPIO249:2;                   // 19:18 Defines pin-muxing selection for GPIO249
    Uint16 rsvd3:2;                     // 21:20 Reserved
    Uint16 GPIO251:2;                   // 23:22 Defines pin-muxing selection for GPIO251
    Uint16 GPIO252:2;                   // 25:24 Defines pin-muxing selection for GPIO252
    Uint16 GPIO253:2;                   // 27:26 Defines pin-muxing selection for GPIO253
    Uint16 rsvd4:2;                     // 29:28 Reserved
    Uint16 rsvd5:2;                     // 31:30 Reserved
};

union GPHMUX2_REG {
    Uint32  all;
    struct  GPHMUX2_BITS  bit;
};

struct GPHDIR_BITS {                    // bits description
    Uint16 GPIO224:1;                   // 0 Defines direction for this pin in GPIO mode
    Uint16 GPIO225:1;                   // 1 Defines direction for this pin in GPIO mode
    Uint16 GPIO226:1;                   // 2 Defines direction for this pin in GPIO mode
    Uint16 GPIO227:1;                   // 3 Defines direction for this pin in GPIO mode
    Uint16 GPIO228:1;                   // 4 Defines direction for this pin in GPIO mode
    Uint16 GPIO229:1;                   // 5 Defines direction for this pin in GPIO mode
    Uint16 GPIO230:1;                   // 6 Defines direction for this pin in GPIO mode
    Uint16 GPIO231:1;                   // 7 Defines direction for this pin in GPIO mode
    Uint16 GPIO232:1;                   // 8 Defines direction for this pin in GPIO mode
    Uint16 GPIO233:1;                   // 9 Defines direction for this pin in GPIO mode
    Uint16 GPIO234:1;                   // 10 Defines direction for this pin in GPIO mode
    Uint16 GPIO235:1;                   // 11 Defines direction for this pin in GPIO mode
    Uint16 GPIO236:1;                   // 12 Defines direction for this pin in GPIO mode
    Uint16 GPIO237:1;                   // 13 Defines direction for this pin in GPIO mode
    Uint16 GPIO238:1;                   // 14 Defines direction for this pin in GPIO mode
    Uint16 GPIO239:1;                   // 15 Defines direction for this pin in GPIO mode
    Uint16 GPIO240:1;                   // 16 Defines direction for this pin in GPIO mode
    Uint16 GPIO241:1;                   // 17 Defines direction for this pin in GPIO mode
    Uint16 GPIO242:1;                   // 18 Defines direction for this pin in GPIO mode
    Uint16 rsvd1:1;                     // 19 Reserved
    Uint16 GPIO244:1;                   // 20 Defines direction for this pin in GPIO mode
    Uint16 GPIO245:1;                   // 21 Defines direction for this pin in GPIO mode
    Uint16 rsvd2:1;                     // 22 Reserved
    Uint16 GPIO247:1;                   // 23 Defines direction for this pin in GPIO mode
    Uint16 GPIO248:1;                   // 24 Defines direction for this pin in GPIO mode
    Uint16 GPIO249:1;                   // 25 Defines direction for this pin in GPIO mode
    Uint16 rsvd3:1;                     // 26 Reserved
    Uint16 GPIO251:1;                   // 27 Defines direction for this pin in GPIO mode
    Uint16 GPIO252:1;                   // 28 Defines direction for this pin in GPIO mode
    Uint16 GPIO253:1;                   // 29 Defines direction for this pin in GPIO mode
    Uint16 rsvd4:1;                     // 30 Reserved
    Uint16 rsvd5:1;                     // 31 Reserved
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
    Uint16 GPIO229:1;                   // 5 Pull-Up Disable control for this pin
    Uint16 GPIO230:1;                   // 6 Pull-Up Disable control for this pin
    Uint16 GPIO231:1;                   // 7 Pull-Up Disable control for this pin
    Uint16 GPIO232:1;                   // 8 Pull-Up Disable control for this pin
    Uint16 GPIO233:1;                   // 9 Pull-Up Disable control for this pin
    Uint16 GPIO234:1;                   // 10 Pull-Up Disable control for this pin
    Uint16 GPIO235:1;                   // 11 Pull-Up Disable control for this pin
    Uint16 GPIO236:1;                   // 12 Pull-Up Disable control for this pin
    Uint16 GPIO237:1;                   // 13 Pull-Up Disable control for this pin
    Uint16 GPIO238:1;                   // 14 Pull-Up Disable control for this pin
    Uint16 GPIO239:1;                   // 15 Pull-Up Disable control for this pin
    Uint16 GPIO240:1;                   // 16 Pull-Up Disable control for this pin
    Uint16 GPIO241:1;                   // 17 Pull-Up Disable control for this pin
    Uint16 GPIO242:1;                   // 18 Pull-Up Disable control for this pin
    Uint16 rsvd1:1;                     // 19 Reserved
    Uint16 GPIO244:1;                   // 20 Pull-Up Disable control for this pin
    Uint16 GPIO245:1;                   // 21 Pull-Up Disable control for this pin
    Uint16 rsvd2:1;                     // 22 Reserved
    Uint16 GPIO247:1;                   // 23 Pull-Up Disable control for this pin
    Uint16 GPIO248:1;                   // 24 Pull-Up Disable control for this pin
    Uint16 GPIO249:1;                   // 25 Pull-Up Disable control for this pin
    Uint16 rsvd3:1;                     // 26 Reserved
    Uint16 GPIO251:1;                   // 27 Pull-Up Disable control for this pin
    Uint16 GPIO252:1;                   // 28 Pull-Up Disable control for this pin
    Uint16 GPIO253:1;                   // 29 Pull-Up Disable control for this pin
    Uint16 rsvd4:1;                     // 30 Reserved
    Uint16 rsvd5:1;                     // 31 Reserved
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
    Uint16 GPIO229:1;                   // 5 Input inversion control for this pin
    Uint16 GPIO230:1;                   // 6 Input inversion control for this pin
    Uint16 GPIO231:1;                   // 7 Input inversion control for this pin
    Uint16 GPIO232:1;                   // 8 Input inversion control for this pin
    Uint16 GPIO233:1;                   // 9 Input inversion control for this pin
    Uint16 GPIO234:1;                   // 10 Input inversion control for this pin
    Uint16 GPIO235:1;                   // 11 Input inversion control for this pin
    Uint16 GPIO236:1;                   // 12 Input inversion control for this pin
    Uint16 GPIO237:1;                   // 13 Input inversion control for this pin
    Uint16 GPIO238:1;                   // 14 Input inversion control for this pin
    Uint16 GPIO239:1;                   // 15 Input inversion control for this pin
    Uint16 GPIO240:1;                   // 16 Input inversion control for this pin
    Uint16 GPIO241:1;                   // 17 Input inversion control for this pin
    Uint16 GPIO242:1;                   // 18 Input inversion control for this pin
    Uint16 rsvd1:1;                     // 19 Reserved
    Uint16 GPIO244:1;                   // 20 Input inversion control for this pin
    Uint16 GPIO245:1;                   // 21 Input inversion control for this pin
    Uint16 rsvd2:1;                     // 22 Reserved
    Uint16 GPIO247:1;                   // 23 Input inversion control for this pin
    Uint16 GPIO248:1;                   // 24 Input inversion control for this pin
    Uint16 GPIO249:1;                   // 25 Input inversion control for this pin
    Uint16 rsvd3:1;                     // 26 Reserved
    Uint16 GPIO251:1;                   // 27 Input inversion control for this pin
    Uint16 GPIO252:1;                   // 28 Input inversion control for this pin
    Uint16 GPIO253:1;                   // 29 Input inversion control for this pin
    Uint16 rsvd4:1;                     // 30 Reserved
    Uint16 rsvd5:1;                     // 31 Reserved
};

union GPHINV_REG {
    Uint32  all;
    struct  GPHINV_BITS  bit;
};

struct GPHODR_BITS {                    // bits description
    Uint16 GPIO224:1;                   // 0 Output Open-Drain control for this pin
    Uint16 GPIO225:1;                   // 1 Output Open-Drain control for this pin
    Uint16 GPIO226:1;                   // 2 Output Open-Drain control for this pin
    Uint16 GPIO227:1;                   // 3 Output Open-Drain control for this pin
    Uint16 GPIO228:1;                   // 4 Output Open-Drain control for this pin
    Uint16 GPIO229:1;                   // 5 Output Open-Drain control for this pin
    Uint16 GPIO230:1;                   // 6 Output Open-Drain control for this pin
    Uint16 GPIO231:1;                   // 7 Output Open-Drain control for this pin
    Uint16 GPIO232:1;                   // 8 Output Open-Drain control for this pin
    Uint16 GPIO233:1;                   // 9 Output Open-Drain control for this pin
    Uint16 GPIO234:1;                   // 10 Output Open-Drain control for this pin
    Uint16 GPIO235:1;                   // 11 Output Open-Drain control for this pin
    Uint16 GPIO236:1;                   // 12 Output Open-Drain control for this pin
    Uint16 GPIO237:1;                   // 13 Output Open-Drain control for this pin
    Uint16 GPIO238:1;                   // 14 Output Open-Drain control for this pin
    Uint16 GPIO239:1;                   // 15 Output Open-Drain control for this pin
    Uint16 GPIO240:1;                   // 16 Output Open-Drain control for this pin
    Uint16 GPIO241:1;                   // 17 Output Open-Drain control for this pin
    Uint16 GPIO242:1;                   // 18 Output Open-Drain control for this pin
    Uint16 rsvd1:1;                     // 19 Reserved
    Uint16 GPIO244:1;                   // 20 Output Open-Drain control for this pin
    Uint16 GPIO245:1;                   // 21 Output Open-Drain control for this pin
    Uint16 rsvd2:1;                     // 22 Reserved
    Uint16 GPIO247:1;                   // 23 Output Open-Drain control for this pin
    Uint16 GPIO248:1;                   // 24 Output Open-Drain control for this pin
    Uint16 GPIO249:1;                   // 25 Output Open-Drain control for this pin
    Uint16 rsvd3:1;                     // 26 Reserved
    Uint16 GPIO251:1;                   // 27 Output Open-Drain control for this pin
    Uint16 GPIO252:1;                   // 28 Output Open-Drain control for this pin
    Uint16 GPIO253:1;                   // 29 Output Open-Drain control for this pin
    Uint16 rsvd4:1;                     // 30 Reserved
    Uint16 rsvd5:1;                     // 31 Reserved
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
    Uint16 GPIO229:1;                   // 5 Analog Mode select for this pin
    Uint16 GPIO230:1;                   // 6 Analog Mode select for this pin
    Uint16 GPIO231:1;                   // 7 Analog Mode select for this pin
    Uint16 GPIO232:1;                   // 8 Analog Mode select for this pin
    Uint16 GPIO233:1;                   // 9 Analog Mode select for this pin
    Uint16 GPIO234:1;                   // 10 Analog Mode select for this pin
    Uint16 GPIO235:1;                   // 11 Analog Mode select for this pin
    Uint16 GPIO236:1;                   // 12 Analog Mode select for this pin
    Uint16 GPIO237:1;                   // 13 Analog Mode select for this pin
    Uint16 GPIO238:1;                   // 14 Analog Mode select for this pin
    Uint16 GPIO239:1;                   // 15 Analog Mode select for this pin
    Uint16 GPIO240:1;                   // 16 Analog Mode select for this pin
    Uint16 GPIO241:1;                   // 17 Analog Mode select for this pin
    Uint16 GPIO242:1;                   // 18 Analog Mode select for this pin
    Uint16 rsvd1:1;                     // 19 Reserved
    Uint16 GPIO244:1;                   // 20 Analog Mode select for this pin
    Uint16 GPIO245:1;                   // 21 Analog Mode select for this pin
    Uint16 rsvd2:1;                     // 22 Reserved
    Uint16 GPIO247:1;                   // 23 Analog Mode select for this pin
    Uint16 GPIO248:1;                   // 24 Analog Mode select for this pin
    Uint16 GPIO249:1;                   // 25 Analog Mode select for this pin
    Uint16 rsvd3:1;                     // 26 Reserved
    Uint16 GPIO251:1;                   // 27 Analog Mode select for this pin
    Uint16 GPIO252:1;                   // 28 Analog Mode select for this pin
    Uint16 GPIO253:1;                   // 29 Analog Mode select for this pin
    Uint16 rsvd4:1;                     // 30 Reserved
    Uint16 rsvd5:1;                     // 31 Reserved
};

union GPHAMSEL_REG {
    Uint32  all;
    struct  GPHAMSEL_BITS  bit;
};

struct GPHGMUX1_BITS {                  // bits description
    Uint16 GPIO224:2;                   // 1:0 Defines pin-muxing selection for GPIO224
    Uint16 GPIO225:2;                   // 3:2 Defines pin-muxing selection for GPIO225
    Uint16 GPIO226:2;                   // 5:4 Defines pin-muxing selection for GPIO226
    Uint16 GPIO227:2;                   // 7:6 Defines pin-muxing selection for GPIO227
    Uint16 GPIO228:2;                   // 9:8 Defines pin-muxing selection for GPIO228
    Uint16 GPIO229:2;                   // 11:10 Defines pin-muxing selection for GPIO229
    Uint16 GPIO230:2;                   // 13:12 Defines pin-muxing selection for GPIO230
    Uint16 GPIO231:2;                   // 15:14 Defines pin-muxing selection for GPIO231
    Uint16 GPIO232:2;                   // 17:16 Defines pin-muxing selection for GPIO232
    Uint16 GPIO233:2;                   // 19:18 Defines pin-muxing selection for GPIO233
    Uint16 GPIO234:2;                   // 21:20 Defines pin-muxing selection for GPIO234
    Uint16 GPIO235:2;                   // 23:22 Defines pin-muxing selection for GPIO235
    Uint16 GPIO236:2;                   // 25:24 Defines pin-muxing selection for GPIO236
    Uint16 GPIO237:2;                   // 27:26 Defines pin-muxing selection for GPIO237
    Uint16 GPIO238:2;                   // 29:28 Defines pin-muxing selection for GPIO238
    Uint16 GPIO239:2;                   // 31:30 Defines pin-muxing selection for GPIO239
};

union GPHGMUX1_REG {
    Uint32  all;
    struct  GPHGMUX1_BITS  bit;
};

struct GPHGMUX2_BITS {                  // bits description
    Uint16 GPIO240:2;                   // 1:0 Defines pin-muxing selection for GPIO240
    Uint16 GPIO241:2;                   // 3:2 Defines pin-muxing selection for GPIO241
    Uint16 GPIO242:2;                   // 5:4 Defines pin-muxing selection for GPIO242
    Uint16 rsvd1:2;                     // 7:6 Reserved
    Uint16 GPIO244:2;                   // 9:8 Defines pin-muxing selection for GPIO244
    Uint16 GPIO245:2;                   // 11:10 Defines pin-muxing selection for GPIO245
    Uint16 rsvd2:2;                     // 13:12 Reserved
    Uint16 GPIO247:2;                   // 15:14 Defines pin-muxing selection for GPIO247
    Uint16 GPIO248:2;                   // 17:16 Defines pin-muxing selection for GPIO248
    Uint16 GPIO249:2;                   // 19:18 Defines pin-muxing selection for GPIO249
    Uint16 rsvd3:2;                     // 21:20 Reserved
    Uint16 GPIO251:2;                   // 23:22 Defines pin-muxing selection for GPIO251
    Uint16 GPIO252:2;                   // 25:24 Defines pin-muxing selection for GPIO252
    Uint16 GPIO253:2;                   // 27:26 Defines pin-muxing selection for GPIO253
    Uint16 rsvd4:2;                     // 29:28 Reserved
    Uint16 rsvd5:2;                     // 31:30 Reserved
};

union GPHGMUX2_REG {
    Uint32  all;
    struct  GPHGMUX2_BITS  bit;
};

struct GPHCSEL1_BITS {                  // bits description
    Uint16 GPIO224:4;                   // 3:0 GPIO224 Controller CPU Select
    Uint16 GPIO225:4;                   // 7:4 GPIO225 Controller CPU Select
    Uint16 GPIO226:4;                   // 11:8 GPIO226 Controller CPU Select
    Uint16 GPIO227:4;                   // 15:12 GPIO227 Controller CPU Select
    Uint16 GPIO228:4;                   // 19:16 GPIO228 Controller CPU Select
    Uint16 GPIO229:4;                   // 23:20 GPIO229 Controller CPU Select
    Uint16 GPIO230:4;                   // 27:24 GPIO230 Controller CPU Select
    Uint16 GPIO231:4;                   // 31:28 GPIO231 Controller CPU Select
};

union GPHCSEL1_REG {
    Uint32  all;
    struct  GPHCSEL1_BITS  bit;
};

struct GPHCSEL2_BITS {                  // bits description
    Uint16 GPIO232:4;                   // 3:0 GPIO232 Controller CPU Select
    Uint16 GPIO233:4;                   // 7:4 GPIO233 Controller CPU Select
    Uint16 GPIO234:4;                   // 11:8 GPIO234 Controller CPU Select
    Uint16 GPIO235:4;                   // 15:12 GPIO235 Controller CPU Select
    Uint16 GPIO236:4;                   // 19:16 GPIO236 Controller CPU Select
    Uint16 GPIO237:4;                   // 23:20 GPIO237 Controller CPU Select
    Uint16 GPIO238:4;                   // 27:24 GPIO238 Controller CPU Select
    Uint16 GPIO239:4;                   // 31:28 GPIO239 Controller CPU Select
};

union GPHCSEL2_REG {
    Uint32  all;
    struct  GPHCSEL2_BITS  bit;
};

struct GPHCSEL3_BITS {                  // bits description
    Uint16 GPIO240:4;                   // 3:0 GPIO240 Controller CPU Select
    Uint16 GPIO241:4;                   // 7:4 GPIO241 Controller CPU Select
    Uint16 GPIO242:4;                   // 11:8 GPIO242 Controller CPU Select
    Uint16 rsvd1:4;                     // 15:12 Reserved
    Uint16 GPIO244:4;                   // 19:16 GPIO244 Controller CPU Select
    Uint16 GPIO245:4;                   // 23:20 GPIO245 Controller CPU Select
    Uint16 rsvd2:4;                     // 27:24 Reserved
    Uint16 GPIO247:4;                   // 31:28 GPIO247 Controller CPU Select
};

union GPHCSEL3_REG {
    Uint32  all;
    struct  GPHCSEL3_BITS  bit;
};

struct GPHCSEL4_BITS {                  // bits description
    Uint16 GPIO248:4;                   // 3:0 GPIO248 Controller CPU Select
    Uint16 GPIO249:4;                   // 7:4 GPIO249 Controller CPU Select
    Uint16 rsvd1:4;                     // 11:8 Reserved
    Uint16 GPIO251:4;                   // 15:12 GPIO251 Controller CPU Select
    Uint16 GPIO252:4;                   // 19:16 GPIO252 Controller CPU Select
    Uint16 GPIO253:4;                   // 23:20 GPIO253 Controller CPU Select
    Uint16 rsvd2:4;                     // 27:24 Reserved
    Uint16 rsvd3:4;                     // 31:28 Reserved
};

union GPHCSEL4_REG {
    Uint32  all;
    struct  GPHCSEL4_BITS  bit;
};

struct GPHLOCK_BITS {                   // bits description
    Uint16 GPIO224:1;                   // 0 Configuration Lock bit for this pin
    Uint16 GPIO225:1;                   // 1 Configuration Lock bit for this pin
    Uint16 GPIO226:1;                   // 2 Configuration Lock bit for this pin
    Uint16 GPIO227:1;                   // 3 Configuration Lock bit for this pin
    Uint16 GPIO228:1;                   // 4 Configuration Lock bit for this pin
    Uint16 GPIO229:1;                   // 5 Configuration Lock bit for this pin
    Uint16 GPIO230:1;                   // 6 Configuration Lock bit for this pin
    Uint16 GPIO231:1;                   // 7 Configuration Lock bit for this pin
    Uint16 GPIO232:1;                   // 8 Configuration Lock bit for this pin
    Uint16 GPIO233:1;                   // 9 Configuration Lock bit for this pin
    Uint16 GPIO234:1;                   // 10 Configuration Lock bit for this pin
    Uint16 GPIO235:1;                   // 11 Configuration Lock bit for this pin
    Uint16 GPIO236:1;                   // 12 Configuration Lock bit for this pin
    Uint16 GPIO237:1;                   // 13 Configuration Lock bit for this pin
    Uint16 GPIO238:1;                   // 14 Configuration Lock bit for this pin
    Uint16 GPIO239:1;                   // 15 Configuration Lock bit for this pin
    Uint16 GPIO240:1;                   // 16 Configuration Lock bit for this pin
    Uint16 GPIO241:1;                   // 17 Configuration Lock bit for this pin
    Uint16 GPIO242:1;                   // 18 Configuration Lock bit for this pin
    Uint16 rsvd1:1;                     // 19 Reserved
    Uint16 GPIO244:1;                   // 20 Configuration Lock bit for this pin
    Uint16 GPIO245:1;                   // 21 Configuration Lock bit for this pin
    Uint16 rsvd2:1;                     // 22 Reserved
    Uint16 GPIO247:1;                   // 23 Configuration Lock bit for this pin
    Uint16 GPIO248:1;                   // 24 Configuration Lock bit for this pin
    Uint16 GPIO249:1;                   // 25 Configuration Lock bit for this pin
    Uint16 rsvd3:1;                     // 26 Reserved
    Uint16 GPIO251:1;                   // 27 Configuration Lock bit for this pin
    Uint16 GPIO252:1;                   // 28 Configuration Lock bit for this pin
    Uint16 GPIO253:1;                   // 29 Configuration Lock bit for this pin
    Uint16 rsvd4:1;                     // 30 Reserved
    Uint16 rsvd5:1;                     // 31 Reserved
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
    Uint16 GPIO229:1;                   // 5 Configuration lock commit bit for this pin
    Uint16 GPIO230:1;                   // 6 Configuration lock commit bit for this pin
    Uint16 GPIO231:1;                   // 7 Configuration lock commit bit for this pin
    Uint16 GPIO232:1;                   // 8 Configuration lock commit bit for this pin
    Uint16 GPIO233:1;                   // 9 Configuration lock commit bit for this pin
    Uint16 GPIO234:1;                   // 10 Configuration lock commit bit for this pin
    Uint16 GPIO235:1;                   // 11 Configuration lock commit bit for this pin
    Uint16 GPIO236:1;                   // 12 Configuration lock commit bit for this pin
    Uint16 GPIO237:1;                   // 13 Configuration lock commit bit for this pin
    Uint16 GPIO238:1;                   // 14 Configuration lock commit bit for this pin
    Uint16 GPIO239:1;                   // 15 Configuration lock commit bit for this pin
    Uint16 GPIO240:1;                   // 16 Configuration lock commit bit for this pin
    Uint16 GPIO241:1;                   // 17 Configuration lock commit bit for this pin
    Uint16 GPIO242:1;                   // 18 Configuration lock commit bit for this pin
    Uint16 rsvd1:1;                     // 19 Reserved
    Uint16 GPIO244:1;                   // 20 Configuration lock commit bit for this pin
    Uint16 GPIO245:1;                   // 21 Configuration lock commit bit for this pin
    Uint16 rsvd2:1;                     // 22 Reserved
    Uint16 GPIO247:1;                   // 23 Configuration lock commit bit for this pin
    Uint16 GPIO248:1;                   // 24 Configuration lock commit bit for this pin
    Uint16 GPIO249:1;                   // 25 Configuration lock commit bit for this pin
    Uint16 rsvd3:1;                     // 26 Reserved
    Uint16 GPIO251:1;                   // 27 Configuration lock commit bit for this pin
    Uint16 GPIO252:1;                   // 28 Configuration lock commit bit for this pin
    Uint16 GPIO253:1;                   // 29 Configuration lock commit bit for this pin
    Uint16 rsvd4:1;                     // 30 Reserved
    Uint16 rsvd5:1;                     // 31 Reserved
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
    Uint16                                   rsvd3[4];                     // Reserved
    union   GPACSEL1_REG                     GPACSEL1;                     // GPIO A Core Select Register (GPIO0 to 7)
    union   GPACSEL2_REG                     GPACSEL2;                     // GPIO A Core Select Register (GPIO8 to 15)
    union   GPACSEL3_REG                     GPACSEL3;                     // GPIO A Core Select Register (GPIO16 to 23)
    union   GPACSEL4_REG                     GPACSEL4;                     // GPIO A Core Select Register (GPIO24 to 31)
    Uint16                                   rsvd4[12];                    // Reserved
    union   GPALOCK_REG                      GPALOCK;                      // GPIO A Lock Configuration Register (GPIO0 to 31)
    union   GPACR_REG                        GPACR;                        // GPIO A Lock Commit Register (GPIO0 to 31)
    union   GPBCTRL_REG                      GPBCTRL;                      // GPIO B Qualification Sampling Period Control (GPIO32 to 63)
    union   GPBQSEL1_REG                     GPBQSEL1;                     // GPIO B Qualifier Select 1 Register (GPIO32 to 47)
    union   GPBQSEL2_REG                     GPBQSEL2;                     // GPIO B Qualifier Select 2 Register (GPIO48 to 63)
    union   GPBMUX1_REG                      GPBMUX1;                      // GPIO B Mux 1 Register (GPIO32 to 47)
    union   GPBMUX2_REG                      GPBMUX2;                      // GPIO B Mux 2 Register (GPIO48 to 63)
    union   GPBDIR_REG                       GPBDIR;                       // GPIO B Direction Register (GPIO32 to 63)
    union   GPBPUD_REG                       GPBPUD;                       // GPIO B Pull Up Disable Register (GPIO32 to 63)
    Uint16                                   rsvd5[2];                     // Reserved
    union   GPBINV_REG                       GPBINV;                       // GPIO B Input Polarity Invert Registers (GPIO32 to 63)
    union   GPBODR_REG                       GPBODR;                       // GPIO B Open Drain Output Register (GPIO32 to GPIO63)
    union   GPBAMSEL_REG                     GPBAMSEL;                     // GPIO B Analog Mode Select register (GPIO32 to GPIO63)
    Uint16                                   rsvd6[10];                    // Reserved
    union   GPBGMUX1_REG                     GPBGMUX1;                     // GPIO B Peripheral Group Mux (GPIO32 to 47)
    union   GPBGMUX2_REG                     GPBGMUX2;                     // GPIO B Peripheral Group Mux (GPIO48 to 63)
    Uint16                                   rsvd7[4];                     // Reserved
    union   GPBCSEL1_REG                     GPBCSEL1;                     // GPIO B Core Select Register (GPIO32 to 39)
    union   GPBCSEL2_REG                     GPBCSEL2;                     // GPIO B Core Select Register (GPIO40 to 47)
    union   GPBCSEL3_REG                     GPBCSEL3;                     // GPIO B Core Select Register (GPIO48 to 55)
    union   GPBCSEL4_REG                     GPBCSEL4;                     // GPIO B Core Select Register (GPIO56 to 63)
    Uint16                                   rsvd8[12];                    // Reserved
    union   GPBLOCK_REG                      GPBLOCK;                      // GPIO B Lock Configuration Register (GPIO32 to 63)
    union   GPBCR_REG                        GPBCR;                        // GPIO B Lock Commit Register (GPIO32 to 63)
    union   GPCCTRL_REG                      GPCCTRL;                      // GPIO C Qualification Sampling Period Control (GPIO64 to 95)
    union   GPCQSEL1_REG                     GPCQSEL1;                     // GPIO C Qualifier Select 1 Register (GPIO64 to 79)
    union   GPCQSEL2_REG                     GPCQSEL2;                     // GPIO C Qualifier Select 2 Register (GPIO80  to 95)
    union   GPCMUX1_REG                      GPCMUX1;                      // GPIO C Mux 1 Register (GPIO64 to 79)
    union   GPCMUX2_REG                      GPCMUX2;                      // GPIO C Mux 2 Register (GPIO80  to 95)
    union   GPCDIR_REG                       GPCDIR;                       // GPIO C Direction Register (GPIO64 to 95)
    union   GPCPUD_REG                       GPCPUD;                       // GPIO C Pull Up Disable Register (GPIO64 to 95)
    Uint16                                   rsvd9[2];                     // Reserved
    union   GPCINV_REG                       GPCINV;                       // GPIO C Input Polarity Invert Registers (GPIO64 to 95)
    union   GPCODR_REG                       GPCODR;                       // GPIO C Open Drain Output Register (GPIO64 to GPIO95)
    Uint16                                   rsvd10[12];                   // Reserved
    union   GPCGMUX1_REG                     GPCGMUX1;                     // GPIO C Peripheral Group Mux (GPIO64 to 79)
    union   GPCGMUX2_REG                     GPCGMUX2;                     // GPIO C Peripheral Group Mux (GPIO80  to 95)
    Uint16                                   rsvd11[4];                    // Reserved
    union   GPCCSEL1_REG                     GPCCSEL1;                     // GPIO C Core Select Register (GPIO64 to 71)
    union   GPCCSEL2_REG                     GPCCSEL2;                     // GPIO C Core Select Register (GPIO72 to 79)
    union   GPCCSEL3_REG                     GPCCSEL3;                     // GPIO C Core Select Register (GPIO80  to 87)
    Uint16                                   rsvd12[14];                   // Reserved
    union   GPCLOCK_REG                      GPCLOCK;                      // GPIO C Lock Configuration Register (GPIO64 to 95)
    union   GPCCR_REG                        GPCCR;                        // GPIO C Lock Commit Register (GPIO64 to 95)
    Uint16                                   rsvd13[192];                  // Reserved
    union   GPGCTRL_REG                      GPGCTRL;                      // GPIO G Qualification Sampling Period Control (GPIO192 to 223)
    Uint16                                   rsvd14[2];                    // Reserved
    union   GPGQSEL2_REG                     GPGQSEL2;                     // GPIO G Qualifier Select 2 Register (GPIO208 to 223)
    Uint16                                   rsvd15[2];                    // Reserved
    union   GPGMUX2_REG                      GPGMUX2;                      // GPIO G Mux 2 Register (GPIO208 to 223)
    union   GPGDIR_REG                       GPGDIR;                       // GPIO G Direction Register (GPIO192 to 223)
    union   GPGPUD_REG                       GPGPUD;                       // GPIO G Pull Up Disable Register (GPIO192 to 223)
    Uint16                                   rsvd16[2];                    // Reserved
    union   GPGINV_REG                       GPGINV;                       // GPIO G Input Polarity Invert Registers (GPIO192 to 223)
    union   GPGODR_REG                       GPGODR;                       // GPIO G Open Drain Output Register (GPIO192 to 223)
    union   GPGAMSEL_REG                     GPGAMSEL;                     // GPIO G Analog Mode Select register (GPIO192 to 223)
    Uint16                                   rsvd17[12];                   // Reserved
    union   GPGGMUX2_REG                     GPGGMUX2;                     // GPIO G Peripheral Group Mux (GPIO208 to 223)
    Uint16                                   rsvd18[8];                    // Reserved
    union   GPGCSEL3_REG                     GPGCSEL3;                     // GPIO G Core Select Register (GPIO208 to 215)
    Uint16                                   rsvd19[14];                   // Reserved
    union   GPGLOCK_REG                      GPGLOCK;                      // GPIO G Lock Configuration Register (GPIO192 to 223)
    union   GPGCR_REG                        GPGCR;                        // GPIO G Lock Commit Register (GPIO192 to 223)
    union   GPHCTRL_REG                      GPHCTRL;                      // GPIO H Qualification Sampling Period Control (GPIO224 to 255)
    union   GPHQSEL1_REG                     GPHQSEL1;                     // GPIO H Qualifier Select 1 Register (GPIO224 to 239)
    union   GPHQSEL2_REG                     GPHQSEL2;                     // GPIO H Qualifier Select 2 Register (GPIO240 to 255)
    union   GPHMUX1_REG                      GPHMUX1;                      // GPIO H Mux 1 Register (GPIO224 to 239)
    union   GPHMUX2_REG                      GPHMUX2;                      // GPIO H Mux 2 Register (GPIO240 to 255)
    union   GPHDIR_REG                       GPHDIR;                       // GPIO H Direction Register (GPIO224 to 255)
    union   GPHPUD_REG                       GPHPUD;                       // GPIO H Pull Up Disable Register (GPIO224 to 255)
    Uint16                                   rsvd20[2];                    // Reserved
    union   GPHINV_REG                       GPHINV;                       // GPIO H Input Polarity Invert Registers (GPIO224 to 255)
    union   GPHODR_REG                       GPHODR;                       // GPIO H Open Drain Output Register (GPIO224 to GPIO255)
    union   GPHAMSEL_REG                     GPHAMSEL;                     // GPIO H Analog Mode Select register (GPIO224 to GPIO255)
    Uint16                                   rsvd21[10];                   // Reserved
    union   GPHGMUX1_REG                     GPHGMUX1;                     // GPIO H Peripheral Group Mux (GPIO224 to 239)
    union   GPHGMUX2_REG                     GPHGMUX2;                     // GPIO H Peripheral Group Mux (GPIO240 to 255)
    Uint16                                   rsvd22[4];                    // Reserved
    union   GPHCSEL1_REG                     GPHCSEL1;                     // GPIO H Core Select Register (GPIO224 to 231)
    union   GPHCSEL2_REG                     GPHCSEL2;                     // GPIO H Core Select Register (GPIO232 to 239)
    union   GPHCSEL3_REG                     GPHCSEL3;                     // GPIO H Core Select Register (GPIO240 to 247)
    union   GPHCSEL4_REG                     GPHCSEL4;                     // GPIO H Core Select Register (GPIO248 to 255)
    Uint16                                   rsvd23[12];                   // Reserved
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
    Uint16 GPIO14:1;                    // 14 Data Register for this pin
    Uint16 GPIO15:1;                    // 15 Data Register for this pin
    Uint16 GPIO16:1;                    // 16 Data Register for this pin
    Uint16 GPIO17:1;                    // 17 Data Register for this pin
    Uint16 GPIO18:1;                    // 18 Data Register for this pin
    Uint16 GPIO19:1;                    // 19 Data Register for this pin
    Uint16 GPIO20:1;                    // 20 Data Register for this pin
    Uint16 GPIO21:1;                    // 21 Data Register for this pin
    Uint16 GPIO22:1;                    // 22 Data Register for this pin
    Uint16 GPIO23:1;                    // 23 Data Register for this pin
    Uint16 GPIO24:1;                    // 24 Data Register for this pin
    Uint16 GPIO25:1;                    // 25 Data Register for this pin
    Uint16 GPIO26:1;                    // 26 Data Register for this pin
    Uint16 GPIO27:1;                    // 27 Data Register for this pin
    Uint16 GPIO28:1;                    // 28 Data Register for this pin
    Uint16 GPIO29:1;                    // 29 Data Register for this pin
    Uint16 GPIO30:1;                    // 30 Data Register for this pin
    Uint16 GPIO31:1;                    // 31 Data Register for this pin
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
    Uint16 GPIO14:1;                    // 14 Output Set bit for this pin
    Uint16 GPIO15:1;                    // 15 Output Set bit for this pin
    Uint16 GPIO16:1;                    // 16 Output Set bit for this pin
    Uint16 GPIO17:1;                    // 17 Output Set bit for this pin
    Uint16 GPIO18:1;                    // 18 Output Set bit for this pin
    Uint16 GPIO19:1;                    // 19 Output Set bit for this pin
    Uint16 GPIO20:1;                    // 20 Output Set bit for this pin
    Uint16 GPIO21:1;                    // 21 Output Set bit for this pin
    Uint16 GPIO22:1;                    // 22 Output Set bit for this pin
    Uint16 GPIO23:1;                    // 23 Output Set bit for this pin
    Uint16 GPIO24:1;                    // 24 Output Set bit for this pin
    Uint16 GPIO25:1;                    // 25 Output Set bit for this pin
    Uint16 GPIO26:1;                    // 26 Output Set bit for this pin
    Uint16 GPIO27:1;                    // 27 Output Set bit for this pin
    Uint16 GPIO28:1;                    // 28 Output Set bit for this pin
    Uint16 GPIO29:1;                    // 29 Output Set bit for this pin
    Uint16 GPIO30:1;                    // 30 Output Set bit for this pin
    Uint16 GPIO31:1;                    // 31 Output Set bit for this pin
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
    Uint16 GPIO14:1;                    // 14 Output Clear bit for this pin
    Uint16 GPIO15:1;                    // 15 Output Clear bit for this pin
    Uint16 GPIO16:1;                    // 16 Output Clear bit for this pin
    Uint16 GPIO17:1;                    // 17 Output Clear bit for this pin
    Uint16 GPIO18:1;                    // 18 Output Clear bit for this pin
    Uint16 GPIO19:1;                    // 19 Output Clear bit for this pin
    Uint16 GPIO20:1;                    // 20 Output Clear bit for this pin
    Uint16 GPIO21:1;                    // 21 Output Clear bit for this pin
    Uint16 GPIO22:1;                    // 22 Output Clear bit for this pin
    Uint16 GPIO23:1;                    // 23 Output Clear bit for this pin
    Uint16 GPIO24:1;                    // 24 Output Clear bit for this pin
    Uint16 GPIO25:1;                    // 25 Output Clear bit for this pin
    Uint16 GPIO26:1;                    // 26 Output Clear bit for this pin
    Uint16 GPIO27:1;                    // 27 Output Clear bit for this pin
    Uint16 GPIO28:1;                    // 28 Output Clear bit for this pin
    Uint16 GPIO29:1;                    // 29 Output Clear bit for this pin
    Uint16 GPIO30:1;                    // 30 Output Clear bit for this pin
    Uint16 GPIO31:1;                    // 31 Output Clear bit for this pin
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
    Uint16 GPIO14:1;                    // 14 Output Toggle bit for this pin
    Uint16 GPIO15:1;                    // 15 Output Toggle bit for this pin
    Uint16 GPIO16:1;                    // 16 Output Toggle bit for this pin
    Uint16 GPIO17:1;                    // 17 Output Toggle bit for this pin
    Uint16 GPIO18:1;                    // 18 Output Toggle bit for this pin
    Uint16 GPIO19:1;                    // 19 Output Toggle bit for this pin
    Uint16 GPIO20:1;                    // 20 Output Toggle bit for this pin
    Uint16 GPIO21:1;                    // 21 Output Toggle bit for this pin
    Uint16 GPIO22:1;                    // 22 Output Toggle bit for this pin
    Uint16 GPIO23:1;                    // 23 Output Toggle bit for this pin
    Uint16 GPIO24:1;                    // 24 Output Toggle bit for this pin
    Uint16 GPIO25:1;                    // 25 Output Toggle bit for this pin
    Uint16 GPIO26:1;                    // 26 Output Toggle bit for this pin
    Uint16 GPIO27:1;                    // 27 Output Toggle bit for this pin
    Uint16 GPIO28:1;                    // 28 Output Toggle bit for this pin
    Uint16 GPIO29:1;                    // 29 Output Toggle bit for this pin
    Uint16 GPIO30:1;                    // 30 Output Toggle bit for this pin
    Uint16 GPIO31:1;                    // 31 Output Toggle bit for this pin
};

union GPATOGGLE_REG {
    Uint32  all;
    struct  GPATOGGLE_BITS  bit;
};

struct GPBDAT_BITS {                    // bits description
    Uint16 GPIO32:1;                    // 0 Data Register for this pin
    Uint16 GPIO33:1;                    // 1 Data Register for this pin
    Uint16 GPIO34:1;                    // 2 Data Register for this pin
    Uint16 GPIO35:1;                    // 3 Data Register for this pin
    Uint16 rsvd1:1;                     // 4 Reserved
    Uint16 GPIO37:1;                    // 5 Data Register for this pin
    Uint16 rsvd2:1;                     // 6 Reserved
    Uint16 rsvd3:1;                     // 7 Reserved
    Uint16 GPIO40:1;                    // 8 Data Register for this pin
    Uint16 GPIO41:1;                    // 9 Data Register for this pin
    Uint16 GPIO42:1;                    // 10 Data Register for this pin
    Uint16 GPIO43:1;                    // 11 Data Register for this pin
    Uint16 GPIO44:1;                    // 12 Data Register for this pin
    Uint16 GPIO45:1;                    // 13 Data Register for this pin
    Uint16 GPIO46:1;                    // 14 Data Register for this pin
    Uint16 GPIO47:1;                    // 15 Data Register for this pin
    Uint16 GPIO48:1;                    // 16 Data Register for this pin
    Uint16 GPIO49:1;                    // 17 Data Register for this pin
    Uint16 GPIO50:1;                    // 18 Data Register for this pin
    Uint16 GPIO51:1;                    // 19 Data Register for this pin
    Uint16 GPIO52:1;                    // 20 Data Register for this pin
    Uint16 GPIO53:1;                    // 21 Data Register for this pin
    Uint16 GPIO54:1;                    // 22 Data Register for this pin
    Uint16 GPIO55:1;                    // 23 Data Register for this pin
    Uint16 GPIO56:1;                    // 24 Data Register for this pin
    Uint16 GPIO57:1;                    // 25 Data Register for this pin
    Uint16 GPIO58:1;                    // 26 Data Register for this pin
    Uint16 GPIO59:1;                    // 27 Data Register for this pin
    Uint16 GPIO60:1;                    // 28 Data Register for this pin
    Uint16 GPIO61:1;                    // 29 Data Register for this pin
    Uint16 GPIO62:1;                    // 30 Data Register for this pin
    Uint16 GPIO63:1;                    // 31 Data Register for this pin
};

union GPBDAT_REG {
    Uint32  all;
    struct  GPBDAT_BITS  bit;
};

struct GPBSET_BITS {                    // bits description
    Uint16 GPIO32:1;                    // 0 Output Set bit for this pin
    Uint16 GPIO33:1;                    // 1 Output Set bit for this pin
    Uint16 GPIO34:1;                    // 2 Output Set bit for this pin
    Uint16 GPIO35:1;                    // 3 Output Set bit for this pin
    Uint16 rsvd1:1;                     // 4 Reserved
    Uint16 GPIO37:1;                    // 5 Output Set bit for this pin
    Uint16 rsvd2:1;                     // 6 Reserved
    Uint16 rsvd3:1;                     // 7 Reserved
    Uint16 GPIO40:1;                    // 8 Output Set bit for this pin
    Uint16 GPIO41:1;                    // 9 Output Set bit for this pin
    Uint16 GPIO42:1;                    // 10 Output Set bit for this pin
    Uint16 GPIO43:1;                    // 11 Output Set bit for this pin
    Uint16 GPIO44:1;                    // 12 Output Set bit for this pin
    Uint16 GPIO45:1;                    // 13 Output Set bit for this pin
    Uint16 GPIO46:1;                    // 14 Output Set bit for this pin
    Uint16 GPIO47:1;                    // 15 Output Set bit for this pin
    Uint16 GPIO48:1;                    // 16 Output Set bit for this pin
    Uint16 GPIO49:1;                    // 17 Output Set bit for this pin
    Uint16 GPIO50:1;                    // 18 Output Set bit for this pin
    Uint16 GPIO51:1;                    // 19 Output Set bit for this pin
    Uint16 GPIO52:1;                    // 20 Output Set bit for this pin
    Uint16 GPIO53:1;                    // 21 Output Set bit for this pin
    Uint16 GPIO54:1;                    // 22 Output Set bit for this pin
    Uint16 GPIO55:1;                    // 23 Output Set bit for this pin
    Uint16 GPIO56:1;                    // 24 Output Set bit for this pin
    Uint16 GPIO57:1;                    // 25 Output Set bit for this pin
    Uint16 GPIO58:1;                    // 26 Output Set bit for this pin
    Uint16 GPIO59:1;                    // 27 Output Set bit for this pin
    Uint16 GPIO60:1;                    // 28 Output Set bit for this pin
    Uint16 GPIO61:1;                    // 29 Output Set bit for this pin
    Uint16 GPIO62:1;                    // 30 Output Set bit for this pin
    Uint16 GPIO63:1;                    // 31 Output Set bit for this pin
};

union GPBSET_REG {
    Uint32  all;
    struct  GPBSET_BITS  bit;
};

struct GPBCLEAR_BITS {                  // bits description
    Uint16 GPIO32:1;                    // 0 Output Clear bit for this pin
    Uint16 GPIO33:1;                    // 1 Output Clear bit for this pin
    Uint16 GPIO34:1;                    // 2 Output Clear bit for this pin
    Uint16 GPIO35:1;                    // 3 Output Clear bit for this pin
    Uint16 rsvd1:1;                     // 4 Reserved
    Uint16 GPIO37:1;                    // 5 Output Clear bit for this pin
    Uint16 rsvd2:1;                     // 6 Reserved
    Uint16 rsvd3:1;                     // 7 Reserved
    Uint16 GPIO40:1;                    // 8 Output Clear bit for this pin
    Uint16 GPIO41:1;                    // 9 Output Clear bit for this pin
    Uint16 GPIO42:1;                    // 10 Output Clear bit for this pin
    Uint16 GPIO43:1;                    // 11 Output Clear bit for this pin
    Uint16 GPIO44:1;                    // 12 Output Clear bit for this pin
    Uint16 GPIO45:1;                    // 13 Output Clear bit for this pin
    Uint16 GPIO46:1;                    // 14 Output Clear bit for this pin
    Uint16 GPIO47:1;                    // 15 Output Clear bit for this pin
    Uint16 GPIO48:1;                    // 16 Output Clear bit for this pin
    Uint16 GPIO49:1;                    // 17 Output Clear bit for this pin
    Uint16 GPIO50:1;                    // 18 Output Clear bit for this pin
    Uint16 GPIO51:1;                    // 19 Output Clear bit for this pin
    Uint16 GPIO52:1;                    // 20 Output Clear bit for this pin
    Uint16 GPIO53:1;                    // 21 Output Clear bit for this pin
    Uint16 GPIO54:1;                    // 22 Output Clear bit for this pin
    Uint16 GPIO55:1;                    // 23 Output Clear bit for this pin
    Uint16 GPIO56:1;                    // 24 Output Clear bit for this pin
    Uint16 GPIO57:1;                    // 25 Output Clear bit for this pin
    Uint16 GPIO58:1;                    // 26 Output Clear bit for this pin
    Uint16 GPIO59:1;                    // 27 Output Clear bit for this pin
    Uint16 GPIO60:1;                    // 28 Output Clear bit for this pin
    Uint16 GPIO61:1;                    // 29 Output Clear bit for this pin
    Uint16 GPIO62:1;                    // 30 Output Clear bit for this pin
    Uint16 GPIO63:1;                    // 31 Output Clear bit for this pin
};

union GPBCLEAR_REG {
    Uint32  all;
    struct  GPBCLEAR_BITS  bit;
};

struct GPBTOGGLE_BITS {                 // bits description
    Uint16 GPIO32:1;                    // 0 Output Toggle bit for this pin
    Uint16 GPIO33:1;                    // 1 Output Toggle bit for this pin
    Uint16 GPIO34:1;                    // 2 Output Toggle bit for this pin
    Uint16 GPIO35:1;                    // 3 Output Toggle bit for this pin
    Uint16 rsvd1:1;                     // 4 Reserved
    Uint16 GPIO37:1;                    // 5 Output Toggle bit for this pin
    Uint16 rsvd2:1;                     // 6 Reserved
    Uint16 rsvd3:1;                     // 7 Reserved
    Uint16 GPIO40:1;                    // 8 Output Toggle bit for this pin
    Uint16 GPIO41:1;                    // 9 Output Toggle bit for this pin
    Uint16 GPIO42:1;                    // 10 Output Toggle bit for this pin
    Uint16 GPIO43:1;                    // 11 Output Toggle bit for this pin
    Uint16 GPIO44:1;                    // 12 Output Toggle bit for this pin
    Uint16 GPIO45:1;                    // 13 Output Toggle bit for this pin
    Uint16 GPIO46:1;                    // 14 Output Toggle bit for this pin
    Uint16 GPIO47:1;                    // 15 Output Toggle bit for this pin
    Uint16 GPIO48:1;                    // 16 Output Toggle bit for this pin
    Uint16 GPIO49:1;                    // 17 Output Toggle bit for this pin
    Uint16 GPIO50:1;                    // 18 Output Toggle bit for this pin
    Uint16 GPIO51:1;                    // 19 Output Toggle bit for this pin
    Uint16 GPIO52:1;                    // 20 Output Toggle bit for this pin
    Uint16 GPIO53:1;                    // 21 Output Toggle bit for this pin
    Uint16 GPIO54:1;                    // 22 Output Toggle bit for this pin
    Uint16 GPIO55:1;                    // 23 Output Toggle bit for this pin
    Uint16 GPIO56:1;                    // 24 Output Toggle bit for this pin
    Uint16 GPIO57:1;                    // 25 Output Toggle bit for this pin
    Uint16 GPIO58:1;                    // 26 Output Toggle bit for this pin
    Uint16 GPIO59:1;                    // 27 Output Toggle bit for this pin
    Uint16 GPIO60:1;                    // 28 Output Toggle bit for this pin
    Uint16 GPIO61:1;                    // 29 Output Toggle bit for this pin
    Uint16 GPIO62:1;                    // 30 Output Toggle bit for this pin
    Uint16 GPIO63:1;                    // 31 Output Toggle bit for this pin
};

union GPBTOGGLE_REG {
    Uint32  all;
    struct  GPBTOGGLE_BITS  bit;
};

struct GPCDAT_BITS {                    // bits description
    Uint16 GPIO64:1;                    // 0 Data Register for this pin
    Uint16 GPIO65:1;                    // 1 Data Register for this pin
    Uint16 GPIO66:1;                    // 2 Data Register for this pin
    Uint16 GPIO67:1;                    // 3 Data Register for this pin
    Uint16 GPIO68:1;                    // 4 Data Register for this pin
    Uint16 GPIO69:1;                    // 5 Data Register for this pin
    Uint16 GPIO70:1;                    // 6 Data Register for this pin
    Uint16 GPIO71:1;                    // 7 Data Register for this pin
    Uint16 GPIO72:1;                    // 8 Data Register for this pin
    Uint16 GPIO73:1;                    // 9 Data Register for this pin
    Uint16 GPIO74:1;                    // 10 Data Register for this pin
    Uint16 GPIO75:1;                    // 11 Data Register for this pin
    Uint16 GPIO76:1;                    // 12 Data Register for this pin
    Uint16 GPIO77:1;                    // 13 Data Register for this pin
    Uint16 GPIO78:1;                    // 14 Data Register for this pin
    Uint16 GPIO79:1;                    // 15 Data Register for this pin
    Uint16 GPIO80:1;                    // 16 Data Register for this pin
    Uint16 GPIO81:1;                    // 17 Data Register for this pin
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

union GPCDAT_REG {
    Uint32  all;
    struct  GPCDAT_BITS  bit;
};

struct GPCSET_BITS {                    // bits description
    Uint16 GPIO64:1;                    // 0 Output Set bit for this pin
    Uint16 GPIO65:1;                    // 1 Output Set bit for this pin
    Uint16 GPIO66:1;                    // 2 Output Set bit for this pin
    Uint16 GPIO67:1;                    // 3 Output Set bit for this pin
    Uint16 GPIO68:1;                    // 4 Output Set bit for this pin
    Uint16 GPIO69:1;                    // 5 Output Set bit for this pin
    Uint16 GPIO70:1;                    // 6 Output Set bit for this pin
    Uint16 GPIO71:1;                    // 7 Output Set bit for this pin
    Uint16 GPIO72:1;                    // 8 Output Set bit for this pin
    Uint16 GPIO73:1;                    // 9 Output Set bit for this pin
    Uint16 GPIO74:1;                    // 10 Output Set bit for this pin
    Uint16 GPIO75:1;                    // 11 Output Set bit for this pin
    Uint16 GPIO76:1;                    // 12 Output Set bit for this pin
    Uint16 GPIO77:1;                    // 13 Output Set bit for this pin
    Uint16 GPIO78:1;                    // 14 Output Set bit for this pin
    Uint16 GPIO79:1;                    // 15 Output Set bit for this pin
    Uint16 GPIO80:1;                    // 16 Output Set bit for this pin
    Uint16 GPIO81:1;                    // 17 Output Set bit for this pin
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

union GPCSET_REG {
    Uint32  all;
    struct  GPCSET_BITS  bit;
};

struct GPCCLEAR_BITS {                  // bits description
    Uint16 GPIO64:1;                    // 0 Output Clear bit for this pin
    Uint16 GPIO65:1;                    // 1 Output Clear bit for this pin
    Uint16 GPIO66:1;                    // 2 Output Clear bit for this pin
    Uint16 GPIO67:1;                    // 3 Output Clear bit for this pin
    Uint16 GPIO68:1;                    // 4 Output Clear bit for this pin
    Uint16 GPIO69:1;                    // 5 Output Clear bit for this pin
    Uint16 GPIO70:1;                    // 6 Output Clear bit for this pin
    Uint16 GPIO71:1;                    // 7 Output Clear bit for this pin
    Uint16 GPIO72:1;                    // 8 Output Clear bit for this pin
    Uint16 GPIO73:1;                    // 9 Output Clear bit for this pin
    Uint16 GPIO74:1;                    // 10 Output Clear bit for this pin
    Uint16 GPIO75:1;                    // 11 Output Clear bit for this pin
    Uint16 GPIO76:1;                    // 12 Output Clear bit for this pin
    Uint16 GPIO77:1;                    // 13 Output Clear bit for this pin
    Uint16 GPIO78:1;                    // 14 Output Clear bit for this pin
    Uint16 GPIO79:1;                    // 15 Output Clear bit for this pin
    Uint16 GPIO80:1;                    // 16 Output Clear bit for this pin
    Uint16 GPIO81:1;                    // 17 Output Clear bit for this pin
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

union GPCCLEAR_REG {
    Uint32  all;
    struct  GPCCLEAR_BITS  bit;
};

struct GPCTOGGLE_BITS {                 // bits description
    Uint16 GPIO64:1;                    // 0 Output Toggle bit for this pin
    Uint16 GPIO65:1;                    // 1 Output Toggle bit for this pin
    Uint16 GPIO66:1;                    // 2 Output Toggle bit for this pin
    Uint16 GPIO67:1;                    // 3 Output Toggle bit for this pin
    Uint16 GPIO68:1;                    // 4 Output Toggle bit for this pin
    Uint16 GPIO69:1;                    // 5 Output Toggle bit for this pin
    Uint16 GPIO70:1;                    // 6 Output Toggle bit for this pin
    Uint16 GPIO71:1;                    // 7 Output Toggle bit for this pin
    Uint16 GPIO72:1;                    // 8 Output Toggle bit for this pin
    Uint16 GPIO73:1;                    // 9 Output Toggle bit for this pin
    Uint16 GPIO74:1;                    // 10 Output Toggle bit for this pin
    Uint16 GPIO75:1;                    // 11 Output Toggle bit for this pin
    Uint16 GPIO76:1;                    // 12 Output Toggle bit for this pin
    Uint16 GPIO77:1;                    // 13 Output Toggle bit for this pin
    Uint16 GPIO78:1;                    // 14 Output Toggle bit for this pin
    Uint16 GPIO79:1;                    // 15 Output Toggle bit for this pin
    Uint16 GPIO80:1;                    // 16 Output Toggle bit for this pin
    Uint16 GPIO81:1;                    // 17 Output Toggle bit for this pin
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

union GPCTOGGLE_REG {
    Uint32  all;
    struct  GPCTOGGLE_BITS  bit;
};

struct GPGDAT_BITS {                    // bits description
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
    Uint16 rsvd13:1;                    // 12 Reserved
    Uint16 rsvd14:1;                    // 13 Reserved
    Uint16 rsvd15:1;                    // 14 Reserved
    Uint16 rsvd16:1;                    // 15 Reserved
    Uint16 GPIO208:1;                   // 16 Data Register for this pin
    Uint16 GPIO209:1;                   // 17 Data Register for this pin
    Uint16 GPIO210:1;                   // 18 Data Register for this pin
    Uint16 GPIO211:1;                   // 19 Data Register for this pin
    Uint16 GPIO212:1;                   // 20 Data Register for this pin
    Uint16 GPIO213:1;                   // 21 Data Register for this pin
    Uint16 GPIO214:1;                   // 22 Data Register for this pin
    Uint16 GPIO215:1;                   // 23 Data Register for this pin
    Uint16 rsvd17:1;                    // 24 Reserved
    Uint16 rsvd18:1;                    // 25 Reserved
    Uint16 rsvd19:1;                    // 26 Reserved
    Uint16 rsvd20:1;                    // 27 Reserved
    Uint16 rsvd21:1;                    // 28 Reserved
    Uint16 rsvd22:1;                    // 29 Reserved
    Uint16 rsvd23:1;                    // 30 Reserved
    Uint16 rsvd24:1;                    // 31 Reserved
};

union GPGDAT_REG {
    Uint32  all;
    struct  GPGDAT_BITS  bit;
};

struct GPGSET_BITS {                    // bits description
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
    Uint16 rsvd13:1;                    // 12 Reserved
    Uint16 rsvd14:1;                    // 13 Reserved
    Uint16 rsvd15:1;                    // 14 Reserved
    Uint16 rsvd16:1;                    // 15 Reserved
    Uint16 GPIO208:1;                   // 16 Output Set bit for this pin
    Uint16 GPIO209:1;                   // 17 Output Set bit for this pin
    Uint16 GPIO210:1;                   // 18 Output Set bit for this pin
    Uint16 GPIO211:1;                   // 19 Output Set bit for this pin
    Uint16 GPIO212:1;                   // 20 Output Set bit for this pin
    Uint16 GPIO213:1;                   // 21 Output Set bit for this pin
    Uint16 GPIO214:1;                   // 22 Output Set bit for this pin
    Uint16 GPIO215:1;                   // 23 Output Set bit for this pin
    Uint16 rsvd17:1;                    // 24 Reserved
    Uint16 rsvd18:1;                    // 25 Reserved
    Uint16 rsvd19:1;                    // 26 Reserved
    Uint16 rsvd20:1;                    // 27 Reserved
    Uint16 rsvd21:1;                    // 28 Reserved
    Uint16 rsvd22:1;                    // 29 Reserved
    Uint16 rsvd23:1;                    // 30 Reserved
    Uint16 rsvd24:1;                    // 31 Reserved
};

union GPGSET_REG {
    Uint32  all;
    struct  GPGSET_BITS  bit;
};

struct GPGCLEAR_BITS {                  // bits description
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
    Uint16 rsvd13:1;                    // 12 Reserved
    Uint16 rsvd14:1;                    // 13 Reserved
    Uint16 rsvd15:1;                    // 14 Reserved
    Uint16 rsvd16:1;                    // 15 Reserved
    Uint16 GPIO208:1;                   // 16 Output Clear bit for this pin
    Uint16 GPIO209:1;                   // 17 Output Clear bit for this pin
    Uint16 GPIO210:1;                   // 18 Output Clear bit for this pin
    Uint16 GPIO211:1;                   // 19 Output Clear bit for this pin
    Uint16 GPIO212:1;                   // 20 Output Clear bit for this pin
    Uint16 GPIO213:1;                   // 21 Output Clear bit for this pin
    Uint16 GPIO214:1;                   // 22 Output Clear bit for this pin
    Uint16 GPIO215:1;                   // 23 Output Clear bit for this pin
    Uint16 rsvd17:1;                    // 24 Reserved
    Uint16 rsvd18:1;                    // 25 Reserved
    Uint16 rsvd19:1;                    // 26 Reserved
    Uint16 rsvd20:1;                    // 27 Reserved
    Uint16 rsvd21:1;                    // 28 Reserved
    Uint16 rsvd22:1;                    // 29 Reserved
    Uint16 rsvd23:1;                    // 30 Reserved
    Uint16 rsvd24:1;                    // 31 Reserved
};

union GPGCLEAR_REG {
    Uint32  all;
    struct  GPGCLEAR_BITS  bit;
};

struct GPGTOGGLE_BITS {                 // bits description
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
    Uint16 rsvd13:1;                    // 12 Reserved
    Uint16 rsvd14:1;                    // 13 Reserved
    Uint16 rsvd15:1;                    // 14 Reserved
    Uint16 rsvd16:1;                    // 15 Reserved
    Uint16 GPIO208:1;                   // 16 Output Toggle bit for this pin
    Uint16 GPIO209:1;                   // 17 Output Toggle bit for this pin
    Uint16 GPIO210:1;                   // 18 Output Toggle bit for this pin
    Uint16 GPIO211:1;                   // 19 Output Toggle bit for this pin
    Uint16 GPIO212:1;                   // 20 Output Toggle bit for this pin
    Uint16 GPIO213:1;                   // 21 Output Toggle bit for this pin
    Uint16 GPIO214:1;                   // 22 Output Toggle bit for this pin
    Uint16 GPIO215:1;                   // 23 Output Toggle bit for this pin
    Uint16 rsvd17:1;                    // 24 Reserved
    Uint16 rsvd18:1;                    // 25 Reserved
    Uint16 rsvd19:1;                    // 26 Reserved
    Uint16 rsvd20:1;                    // 27 Reserved
    Uint16 rsvd21:1;                    // 28 Reserved
    Uint16 rsvd22:1;                    // 29 Reserved
    Uint16 rsvd23:1;                    // 30 Reserved
    Uint16 rsvd24:1;                    // 31 Reserved
};

union GPGTOGGLE_REG {
    Uint32  all;
    struct  GPGTOGGLE_BITS  bit;
};

struct GPHDAT_BITS {                    // bits description
    Uint16 GPIO224:1;                   // 0 Data Register for this pin
    Uint16 GPIO225:1;                   // 1 Data Register for this pin
    Uint16 GPIO226:1;                   // 2 Data Register for this pin
    Uint16 GPIO227:1;                   // 3 Data Register for this pin
    Uint16 GPIO228:1;                   // 4 Data Register for this pin
    Uint16 GPIO229:1;                   // 5 Data Register for this pin
    Uint16 GPIO230:1;                   // 6 Data Register for this pin
    Uint16 GPIO231:1;                   // 7 Data Register for this pin
    Uint16 GPIO232:1;                   // 8 Data Register for this pin
    Uint16 GPIO233:1;                   // 9 Data Register for this pin
    Uint16 GPIO234:1;                   // 10 Data Register for this pin
    Uint16 GPIO235:1;                   // 11 Data Register for this pin
    Uint16 GPIO236:1;                   // 12 Data Register for this pin
    Uint16 GPIO237:1;                   // 13 Data Register for this pin
    Uint16 GPIO238:1;                   // 14 Data Register for this pin
    Uint16 GPIO239:1;                   // 15 Data Register for this pin
    Uint16 GPIO240:1;                   // 16 Data Register for this pin
    Uint16 GPIO241:1;                   // 17 Data Register for this pin
    Uint16 GPIO242:1;                   // 18 Data Register for this pin
    Uint16 rsvd1:1;                     // 19 Reserved
    Uint16 GPIO244:1;                   // 20 Data Register for this pin
    Uint16 GPIO245:1;                   // 21 Data Register for this pin
    Uint16 rsvd2:1;                     // 22 Reserved
    Uint16 GPIO247:1;                   // 23 Data Register for this pin
    Uint16 GPIO248:1;                   // 24 Data Register for this pin
    Uint16 GPIO249:1;                   // 25 Data Register for this pin
    Uint16 rsvd3:1;                     // 26 Reserved
    Uint16 GPIO251:1;                   // 27 Data Register for this pin
    Uint16 GPIO252:1;                   // 28 Data Register for this pin
    Uint16 GPIO253:1;                   // 29 Data Register for this pin
    Uint16 rsvd4:1;                     // 30 Reserved
    Uint16 rsvd5:1;                     // 31 Reserved
};

union GPHDAT_REG {
    Uint32  all;
    struct  GPHDAT_BITS  bit;
};

struct GPHSET_BITS {                    // bits description
    Uint16 GPIO224:1;                   // 0 Output Set bit for this pin
    Uint16 GPIO225:1;                   // 1 Output Set bit for this pin
    Uint16 GPIO226:1;                   // 2 Output Set bit for this pin
    Uint16 GPIO227:1;                   // 3 Output Set bit for this pin
    Uint16 GPIO228:1;                   // 4 Output Set bit for this pin
    Uint16 GPIO229:1;                   // 5 Output Set bit for this pin
    Uint16 GPIO230:1;                   // 6 Output Set bit for this pin
    Uint16 GPIO231:1;                   // 7 Output Set bit for this pin
    Uint16 GPIO232:1;                   // 8 Output Set bit for this pin
    Uint16 GPIO233:1;                   // 9 Output Set bit for this pin
    Uint16 GPIO234:1;                   // 10 Output Set bit for this pin
    Uint16 GPIO235:1;                   // 11 Output Set bit for this pin
    Uint16 GPIO236:1;                   // 12 Output Set bit for this pin
    Uint16 GPIO237:1;                   // 13 Output Set bit for this pin
    Uint16 GPIO238:1;                   // 14 Output Set bit for this pin
    Uint16 GPIO239:1;                   // 15 Output Set bit for this pin
    Uint16 GPIO240:1;                   // 16 Output Set bit for this pin
    Uint16 GPIO241:1;                   // 17 Output Set bit for this pin
    Uint16 GPIO242:1;                   // 18 Output Set bit for this pin
    Uint16 rsvd1:1;                     // 19 Reserved
    Uint16 GPIO244:1;                   // 20 Output Set bit for this pin
    Uint16 GPIO245:1;                   // 21 Output Set bit for this pin
    Uint16 rsvd2:1;                     // 22 Reserved
    Uint16 GPIO247:1;                   // 23 Output Set bit for this pin
    Uint16 GPIO248:1;                   // 24 Output Set bit for this pin
    Uint16 GPIO249:1;                   // 25 Output Set bit for this pin
    Uint16 rsvd3:1;                     // 26 Reserved
    Uint16 GPIO251:1;                   // 27 Output Set bit for this pin
    Uint16 GPIO252:1;                   // 28 Output Set bit for this pin
    Uint16 GPIO253:1;                   // 29 Output Set bit for this pin
    Uint16 rsvd4:1;                     // 30 Reserved
    Uint16 rsvd5:1;                     // 31 Reserved
};

union GPHSET_REG {
    Uint32  all;
    struct  GPHSET_BITS  bit;
};

struct GPHCLEAR_BITS {                  // bits description
    Uint16 GPIO224:1;                   // 0 Output Clear bit for this pin
    Uint16 GPIO225:1;                   // 1 Output Clear bit for this pin
    Uint16 GPIO226:1;                   // 2 Output Clear bit for this pin
    Uint16 GPIO227:1;                   // 3 Output Clear bit for this pin
    Uint16 GPIO228:1;                   // 4 Output Clear bit for this pin
    Uint16 GPIO229:1;                   // 5 Output Clear bit for this pin
    Uint16 GPIO230:1;                   // 6 Output Clear bit for this pin
    Uint16 GPIO231:1;                   // 7 Output Clear bit for this pin
    Uint16 GPIO232:1;                   // 8 Output Clear bit for this pin
    Uint16 GPIO233:1;                   // 9 Output Clear bit for this pin
    Uint16 GPIO234:1;                   // 10 Output Clear bit for this pin
    Uint16 GPIO235:1;                   // 11 Output Clear bit for this pin
    Uint16 GPIO236:1;                   // 12 Output Clear bit for this pin
    Uint16 GPIO237:1;                   // 13 Output Clear bit for this pin
    Uint16 GPIO238:1;                   // 14 Output Clear bit for this pin
    Uint16 GPIO239:1;                   // 15 Output Clear bit for this pin
    Uint16 GPIO240:1;                   // 16 Output Clear bit for this pin
    Uint16 GPIO241:1;                   // 17 Output Clear bit for this pin
    Uint16 GPIO242:1;                   // 18 Output Clear bit for this pin
    Uint16 rsvd1:1;                     // 19 Reserved
    Uint16 GPIO244:1;                   // 20 Output Clear bit for this pin
    Uint16 GPIO245:1;                   // 21 Output Clear bit for this pin
    Uint16 rsvd2:1;                     // 22 Reserved
    Uint16 GPIO247:1;                   // 23 Output Clear bit for this pin
    Uint16 GPIO248:1;                   // 24 Output Clear bit for this pin
    Uint16 GPIO249:1;                   // 25 Output Clear bit for this pin
    Uint16 rsvd3:1;                     // 26 Reserved
    Uint16 GPIO251:1;                   // 27 Output Clear bit for this pin
    Uint16 GPIO252:1;                   // 28 Output Clear bit for this pin
    Uint16 GPIO253:1;                   // 29 Output Clear bit for this pin
    Uint16 rsvd4:1;                     // 30 Reserved
    Uint16 rsvd5:1;                     // 31 Reserved
};

union GPHCLEAR_REG {
    Uint32  all;
    struct  GPHCLEAR_BITS  bit;
};

struct GPHTOGGLE_BITS {                 // bits description
    Uint16 GPIO224:1;                   // 0 Output Toggle bit for this pin
    Uint16 GPIO225:1;                   // 1 Output Toggle bit for this pin
    Uint16 GPIO226:1;                   // 2 Output Toggle bit for this pin
    Uint16 GPIO227:1;                   // 3 Output Toggle bit for this pin
    Uint16 GPIO228:1;                   // 4 Output Toggle bit for this pin
    Uint16 GPIO229:1;                   // 5 Output Toggle bit for this pin
    Uint16 GPIO230:1;                   // 6 Output Toggle bit for this pin
    Uint16 GPIO231:1;                   // 7 Output Toggle bit for this pin
    Uint16 GPIO232:1;                   // 8 Output Toggle bit for this pin
    Uint16 GPIO233:1;                   // 9 Output Toggle bit for this pin
    Uint16 GPIO234:1;                   // 10 Output Toggle bit for this pin
    Uint16 GPIO235:1;                   // 11 Output Toggle bit for this pin
    Uint16 GPIO236:1;                   // 12 Output Toggle bit for this pin
    Uint16 GPIO237:1;                   // 13 Output Toggle bit for this pin
    Uint16 GPIO238:1;                   // 14 Output Toggle bit for this pin
    Uint16 GPIO239:1;                   // 15 Output Toggle bit for this pin
    Uint16 GPIO240:1;                   // 16 Output Toggle bit for this pin
    Uint16 GPIO241:1;                   // 17 Output Toggle bit for this pin
    Uint16 GPIO242:1;                   // 18 Output Toggle bit for this pin
    Uint16 rsvd1:1;                     // 19 Reserved
    Uint16 GPIO244:1;                   // 20 Output Toggle bit for this pin
    Uint16 GPIO245:1;                   // 21 Output Toggle bit for this pin
    Uint16 rsvd2:1;                     // 22 Reserved
    Uint16 GPIO247:1;                   // 23 Output Toggle bit for this pin
    Uint16 GPIO248:1;                   // 24 Output Toggle bit for this pin
    Uint16 GPIO249:1;                   // 25 Output Toggle bit for this pin
    Uint16 rsvd3:1;                     // 26 Reserved
    Uint16 GPIO251:1;                   // 27 Output Toggle bit for this pin
    Uint16 GPIO252:1;                   // 28 Output Toggle bit for this pin
    Uint16 GPIO253:1;                   // 29 Output Toggle bit for this pin
    Uint16 rsvd4:1;                     // 30 Reserved
    Uint16 rsvd5:1;                     // 31 Reserved
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
    union   GPCDAT_REG                       GPCDAT;                       // GPIO C Data Register (GPIO64 to 95)
    union   GPCSET_REG                       GPCSET;                       // GPIO C Data Set Register (GPIO64 to 95)
    union   GPCCLEAR_REG                     GPCCLEAR;                     // GPIO C Data Clear Register (GPIO64 to 95)
    union   GPCTOGGLE_REG                    GPCTOGGLE;                    // GPIO C Data Toggle Register (GPIO64 to 95)
    Uint16                                   rsvd1[24];                    // Reserved
    union   GPGDAT_REG                       GPGDAT;                       // GPIO G Data Register (GPIO192 to 223)
    union   GPGSET_REG                       GPGSET;                       // GPIO G Data Set Register (GPIO192 to 223)
    union   GPGCLEAR_REG                     GPGCLEAR;                     // GPIO G Data Clear Register (GPIO192 to 223)
    union   GPGTOGGLE_REG                    GPGTOGGLE;                    // GPIO G Data Toggle Register (GPIO192 to 223)
    union   GPHDAT_REG                       GPHDAT;                       // GPIO H Data Register (GPIO224 to 255)
    union   GPHSET_REG                       GPHSET;                       // GPIO H Data Set Register (GPIO224 to 255)
    union   GPHCLEAR_REG                     GPHCLEAR;                     // GPIO H Data Clear Register (GPIO224 to 255)
    union   GPHTOGGLE_REG                    GPHTOGGLE;                    // GPIO H Data Toggle Register (GPIO224 to 255)
};

struct GPIO_DATA_READ_REGS {
    Uint32                                   GPADAT_R;                     // GPIO A Data Read Register
    Uint32                                   GPBDAT_R;                     // GPIO B Data Read Register
    Uint32                                   GPCDAT_R;                     // GPIO C Data Read Register
    Uint16                                   rsvd1[6];                     // Reserved
    Uint32                                   GPGDAT_R;                     // GPIO G Data Read Register
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
