//###########################################################################
//
// FILE:   F2805x_Gpio.h
//
// TITLE:  F2805x Device GPIO Register Definitions.
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:
// Copyright (C) 2012-2025 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef F2805x_GPIO_H
#define F2805x_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

//
// GPIO Individual Register Bit Definitions:
//
struct GPACTRL_BITS {                        // bits description
    Uint16  QUALPRD0:8;                      // 7:0 GPIO0 to 7 Qual Cycles
    Uint16  QUALPRD1:8;                      // 15:8 GPIO8 to 15 Qual Cycles
    Uint16  QUALPRD2:8;                      // 23:16 GPIO16 to 23 Qual Cycles
    Uint16  QUALPRD3:8;                      // 31:24 GPIO24 to 31 Qual Cycles
};

union GPACTRL_REG {
    Uint32  all;
    struct  GPACTRL_BITS  bit;
};

struct GPBCTRL_BITS {                    // bits description
    Uint16  QUALPRD0:8;                  // 7:0 GPIO32 to 39 Qual Cycles
    Uint16  QUALPRD1:8;                  // 15:8 GPIO40 and GPIO 42 Qual Cycles
    Uint16  rsvd1:16;                    // 31:16 Reserved
};

union GPBCTRL_REG {
    Uint32  all;
    struct  GPBCTRL_BITS  bit;
};

struct GPA1_BITS {                           // bits description
    Uint16  GPIO0:2;                         // 1:0 GPIO0
    Uint16  GPIO1:2;                         // 3:2 GPIO1
    Uint16  GPIO2:2;                         // 5:4 GPIO2
    Uint16  GPIO3:2;                         // 7:6 GPIO3
    Uint16  GPIO4:2;                         // 9:8 GPIO4
    Uint16  GPIO5:2;                         // 11:10 GPIO5
    Uint16  GPIO6:2;                         // 13:12 GPIO6
    Uint16  GPIO7:2;                         // 15:14 GPIO7
    Uint16  GPIO8:2;                         // 17:16 GPIO8
    Uint16  GPIO9:2;                         // 19:18 GPIO9
    Uint16  GPIO10:2;                        // 21:20 GPIO10
    Uint16  GPIO11:2;                        // 23:22 GPIO11
    Uint16  GPIO12:2;                        // 25:24 GPIO12
    Uint16  GPIO13:2;                        // 27:26 GPIO13
    Uint16  GPIO14:2;                        // 29:28 GPIO14
    Uint16  GPIO15:2;                        // 31:30 GPIO15
};

union GPA1_REG {
    Uint32  all;
    struct  GPA1_BITS  bit;
};

struct GPA2_BITS {                           // bits description
    Uint16  GPIO16:2;                        // 1:0 GPIO16
    Uint16  GPIO17:2;                        // 3:2 GPIO17
    Uint16  GPIO18:2;                        // 5:4 GPIO18
    Uint16  GPIO19:2;                        // 7:6 GPIO19
    Uint16  GPIO20:2;                        // 9:8 GPIO20
    Uint16  GPIO21:2;                        // 11:10 GPIO21
    Uint16  GPIO22:2;                        // 13:12 GPIO22
    Uint16  GPIO23:2;                        // 15:14 GPIO23
    Uint16  GPIO24:2;                        // 17:16 GPIO24
    Uint16  GPIO25:2;                        // 19:18 GPIO25
    Uint16  GPIO26:2;                        // 21:20 GPIO26
    Uint16  GPIO27:2;                        // 23:22 GPIO27
    Uint16  GPIO28:2;                        // 25:24 GPIO28
    Uint16  GPIO29:2;                        // 27:26 GPIO29
    Uint16  GPIO30:2;                        // 29:28 GPIO30
    Uint16  GPIO31:2;                        // 31:30 GPIO31
};

union GPA2_REG {
    Uint32  all;
    struct  GPA2_BITS  bit;
};

struct GPB1_BITS {                           // bits description
    Uint16  GPIO32:2;                        // 1:0 GPIO32
    Uint16  GPIO33:2;                        // 3:2 GPIO33
    Uint16  GPIO34:2;                        // 5:4 GPIO34
    Uint16  GPIO35:2;                        // 7:6 GPIO35
    Uint16  GPIO36:2;                        // 9:8 GPIO36
    Uint16  GPIO37:2;                        // 11:10 GPIO37
    Uint16  GPIO38:2;                        // 13:12 GPIO38
    Uint16  GPIO39:2;                        // 15:14 GPIO39
    Uint16  GPIO40:2;                        // 17:16 GPIO40
    Uint16  rsvd1:2;                         // 19:18 Reserved
    Uint16  GPIO42:2;                        // 21:20 GPIO42
    Uint16  rsvd2:10;                         // 31:22 Reserved
};

union GPB1_REG {
    Uint32  all;
    struct  GPB1_BITS  bit;
};

struct GPADAT_BITS {                         // bits description
    Uint16  GPIO0:1;                         // 0 GPIO0 Data
    Uint16  GPIO1:1;                         // 1 GPIO1 Data
    Uint16  GPIO2:1;                         // 2 GPIO2 Data
    Uint16  GPIO3:1;                         // 3 GPIO3 Data
    Uint16  GPIO4:1;                         // 4 GPIO4 Data
    Uint16  GPIO5:1;                         // 5 GPIO5 Data
    Uint16  GPIO6:1;                         // 6 GPIO6 Data
    Uint16  GPIO7:1;                         // 7 GPIO7 Data
    Uint16  GPIO8:1;                         // 8 GPIO8 Data
    Uint16  GPIO9:1;                         // 9 GPIO9 Data
    Uint16  GPIO10:1;                        // 10 GPIO10 Data
    Uint16  GPIO11:1;                        // 11 GPIO11 Data
    Uint16  GPIO12:1;                        // 12 GPIO12 Data
    Uint16  GPIO13:1;                        // 13 GPIO13 Data
    Uint16  GPIO14:1;                        // 14 GPIO14 Data
    Uint16  GPIO15:1;                        // 15 GPIO15 Data
    Uint16  GPIO16:1;                        // 16 GPIO16 Data
    Uint16  GPIO17:1;                        // 17 GPIO17 Data
    Uint16  GPIO18:1;                        // 18 GPIO18 Data
    Uint16  GPIO19:1;                        // 19 GPIO19 Data
    Uint16  GPIO20:1;                        // 20 GPIO20 Data
    Uint16  GPIO21:1;                        // 21 GPIO21 Data
    Uint16  GPIO22:1;                        // 22 GPIO22 Data
    Uint16  GPIO23:1;                        // 23 GPIO23 Data
    Uint16  GPIO24:1;                        // 24 GPIO24 Data
    Uint16  GPIO25:1;                        // 25 GPIO25 Data
    Uint16  GPIO26:1;                        // 26 GPIO26 Data
    Uint16  GPIO27:1;                        // 27 GPIO27 Data
    Uint16  GPIO28:1;                        // 28 GPIO28 Data
    Uint16  GPIO29:1;                        // 29 GPIO29 Data
    Uint16  GPIO30:1;                        // 30 GPIO30 Data
    Uint16  GPIO31:1;                        // 31 GPIO31 Data
};

union GPADAT_REG {
    Uint32  all;
    struct  GPADAT_BITS  bit;
};

struct GPBDAT_BITS {                         // bits description
    Uint16  GPIO32:1;                        // 0 GPIO32 Data
    Uint16  GPIO33:1;                        // 1 GPIO33 Data
    Uint16  GPIO34:1;                        // 2 GPIO34 Data
    Uint16  GPIO35:1;                        // 3 GPIO35 Data
    Uint16  GPIO36:1;                        // 4 GPIO36 Data
    Uint16  GPIO37:1;                        // 5 GPIO37 Data
    Uint16  GPIO38:1;                        // 6 GPIO38 Data
    Uint16  GPIO39:1;                        // 7 GPIO39 Data
    Uint16  GPIO40:1;                        // 8 GPIO40 Data
    Uint16  rsvd1:1;                         // 9 Reserved
    Uint16  GPIO42:1;                        // 10 GPIO42 Data
    Uint16  rsvd2:5;                         // 15:11 Reserved
    Uint16  rsvd3:16;                        // 31:16 Reserved
};

union GPBDAT_REG {
    Uint32  all;
    struct  GPBDAT_BITS  bit;
};

struct GPIOXINT_BITS {           // bits description
    Uint16  GPIOSEL:5;           // 4:0 Select XGPIO pin as __interrupt source
    Uint16  rsvd1:11;            // 15:5 Reserved
};

union GPIOXINT_REG {
    Uint16  all;
    struct  GPIOXINT_BITS  bit;
};

struct GPIO_CTRL_REGS {
    union   GPACTRL_REG     GPACTRL;   // GPIO A Control Register (GPIO0-31)
    union   GPA1_REG        GPAQSEL1;  // GPIO A Qual. Sel. 1 Reg. (GPIO0-15)
    union   GPA2_REG        GPAQSEL2;  // GPIO A Qual. Sel. 2 Reg. (GPIO16-31)
    union   GPA1_REG        GPAMUX1;   // GPIO A Mux 1 Register (GPIO0-15)
    union   GPA2_REG        GPAMUX2;   // GPIO A Mux 2 Register (GPIO16-31)
    union   GPADAT_REG      GPADIR;    // GPIO A Direction Reg. (GPIO0 to 31)
    union   GPADAT_REG      GPAPUD;    // GPIO A Pull-Up Disable Register
    Uint16                  rsvd1[2];  // Reserved
    union   GPBCTRL_REG     GPBCTRL;   // GPIO B Control Reg. (GPIO32-40, 42)
    union   GPB1_REG        GPBQSEL1;  // GPIO B Qual. Sel. 1 Reg GPIO32-40, 42
    Uint16                  rsvd2[2];  // Reserved
    union   GPB1_REG        GPBMUX1;   // GPIO B Mux 1 Register (GPIO32-40, 42)
    Uint16                  rsvd3[2];  // Reserved
    union   GPBDAT_REG      GPBDIR;    // GPIO B Direction Reg. (GPIO32-40, 42)
    union   GPBDAT_REG      GPBPUD;    // GPIO B Pull-Up Disable Register
    Uint16                  rsvd4[34]; // Reserved
};

struct GPIO_DATA_REGS {
    union   GPADAT_REG      GPADAT;      // GPIO A Data Register GPIO0-31
    union   GPADAT_REG      GPASET;      // GPIO A Data Set Reg. GPIO0-31
    union   GPADAT_REG      GPACLEAR;    // GPIO A Data Clear Reg. GPIO0-31
    union   GPADAT_REG      GPATOGGLE;   // GPIO A Data Toggle Reg. GPIO031
    union   GPBDAT_REG      GPBDAT;      // GPIO B Data Register GPIO32-40, 42
    union   GPBDAT_REG      GPBSET;      // GPIO B Data Set Reg GPIO32-40, 42
    union   GPBDAT_REG      GPBCLEAR;    // GPIO B Data Clr Reg. GPIO32-40, 42
    union   GPBDAT_REG      GPBTOGGLE;   // GPIO B Data Toggle Reg GPIO32-40,42
    Uint16                  rsvd1[16];   // Reserved
};

struct GPIO_INT_REGS {
    union   GPIOXINT_REG    GPIOXINT1SEL; // XINT1 GPIO Input Sel. Reg GPIO0-31
    union   GPIOXINT_REG    GPIOXINT2SEL; // XINT2 GPIO Input Sel. Reg GPIO0-31
    union   GPIOXINT_REG    GPIOXINT3SEL; // XINT3 GPIO Input Sel. Reg GPIO0-31
    Uint16                  rsvd1[5];    // Reserved
    union   GPADAT_REG      GPIOLPMSEL;  // LPM GPIO Select Reg GPIO0-31
    Uint16                  rsvd2[22];   // Reserved
};

//
// Gpio External References & Function Declarations:
//
extern volatile struct GPIO_CTRL_REGS GpioCtrlRegs;
extern volatile struct GPIO_DATA_REGS GpioDataRegs;
extern volatile struct GPIO_INT_REGS GpioIntRegs;

#ifdef __cplusplus
}
#endif                                       /* extern "C" */

#endif                                       // end of F2805x_GPIO_H definition
//
// End of file
//
