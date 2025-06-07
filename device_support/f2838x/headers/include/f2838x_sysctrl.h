//###########################################################################
//
// FILE:    f2838x_sysctrl.h
//
// TITLE:   Definitions for the SYSCTRL registers.
//
//###########################################################################
// 
// C2000Ware v5.05.00.00
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

#ifndef F2838X_SYSCTRL_H
#define F2838X_SYSCTRL_H

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// SYSCTRL Individual Register Bit Definitions:

struct CLKSEM_BITS {                    // bits description
    Uint16 SEM:2;                       // 1:0 Semaphore for CLKCFG Ownership by CPU1 or CPU2
    Uint16 rsvd1:14;                    // 15:2 Reserved
    Uint16 KEY:16;                      // 31:16 Key Qualifier for writes to this register
};

union CLKSEM_REG {
    Uint32  all;
    struct  CLKSEM_BITS  bit;
};

struct CLKCFGLOCK1_BITS {               // bits description
    Uint16 CLKSRCCTL1:1;                // 0 Lock bit for CLKSRCCTL1 register
    Uint16 CLKSRCCTL2:1;                // 1 Lock bit for CLKSRCCTL2 register
    Uint16 CLKSRCCTL3:1;                // 2 Lock bit for CLKSRCCTL3 register
    Uint16 SYSPLLCTL1:1;                // 3 Lock bit for SYSPLLCTL1 register
    Uint16 SYSPLLCTL2:1;                // 4 Lock bit for SYSPLLCTL2 register
    Uint16 SYSPLLCTL3:1;                // 5 Lock bit for SYSPLLCTL3 register
    Uint16 SYSPLLMULT:1;                // 6 Lock bit for SYSPLLMULT register
    Uint16 AUXPLLCTL1:1;                // 7 Lock bit for AUXPLLCTL1 register
    Uint16 rsvd1:1;                     // 8 Reserved
    Uint16 rsvd2:1;                     // 9 Reserved
    Uint16 AUXPLLMULT:1;                // 10 Lock bit for AUXPLLMULT register
    Uint16 SYSCLKDIVSEL:1;              // 11 Lock bit for SYSCLKDIVSEL register
    Uint16 AUXCLKDIVSEL:1;              // 12 Lock bit for AUXCLKDIVSEL register
    Uint16 PERCLKDIVSEL:1;              // 13 Lock bit for PERCLKDIVSEL register
    Uint16 CLBCLKCTL:1;                 // 14 Lock bit for CLBCLKCTL register
    Uint16 LOSPCP:1;                    // 15 Lock bit for LOSPCP register
    Uint16 XTALCR:1;                    // 16 Lock bit for XTALCR register
    Uint16 ETHERCATCLKCTL:1;            // 17 Lock bit for ETHERCATCLKCTL register
    Uint16 CMCLKCTL:1;                  // 18 Lock bit for CMCLKCTL register
    Uint16 rsvd3:13;                    // 31:19 Reserved
};

union CLKCFGLOCK1_REG {
    Uint32  all;
    struct  CLKCFGLOCK1_BITS  bit;
};

struct CLKSRCCTL1_BITS {                // bits description
    Uint16 OSCCLKSRCSEL:2;              // 1:0 OSCCLK Source Select Bit
    Uint16 rsvd1:1;                     // 2 Reserved
    Uint16 INTOSC2OFF_NOTSUPPORTED:1;   // 3 Internal Oscillator 2 Off Bit
    Uint16 XTALOFF:1;                   // 4 Crystal (External) Oscillator Off Bit
    Uint16 rsvd2:1;                     // 5 Reserved
    Uint16 rsvd3:10;                    // 15:6 Reserved
    Uint16 rsvd4:16;                    // 31:16 Reserved
};

union CLKSRCCTL1_REG {
    Uint32  all;
    struct  CLKSRCCTL1_BITS  bit;
};

struct CLKSRCCTL2_BITS {                // bits description
    Uint16 AUXOSCCLKSRCSEL:2;           // 1:0 AUXOSCCLK Source Select Bit
    Uint16 CANABCLKSEL:2;               // 3:2 CANA Clock Source Select Bit
    Uint16 CANBBCLKSEL:2;               // 5:4 CANB Clock Source Select Bit
    Uint16 rsvd1:2;                     // 7:6 Reserved
    Uint16 rsvd2:2;                     // 9:8 Reserved
    Uint16 MCANABITCLKSEL:2;            // 11:10 MCAN (global) Bit-Clock Source Select Bit
    Uint16 rsvd3:4;                     // 15:12 Reserved
    Uint16 rsvd4:16;                    // 31:16 Reserved
};

union CLKSRCCTL2_REG {
    Uint32  all;
    struct  CLKSRCCTL2_BITS  bit;
};

struct CLKSRCCTL3_BITS {                // bits description
    Uint16 XCLKOUTSEL:4;                // 3:0 XCLKOUT Source Select Bit
    Uint16 rsvd1:12;                    // 15:4 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union CLKSRCCTL3_REG {
    Uint32  all;
    struct  CLKSRCCTL3_BITS  bit;
};

struct SYSPLLCTL1_BITS {                // bits description
    Uint16 PLLEN:1;                     // 0 SYSPLL enable/disable bit
    Uint16 PLLCLKEN:1;                  // 1 SYSPLL bypassed or included in the PLLSYSCLK path
    Uint16 rsvd1:1;                     // 2 Reserved
    Uint16 rsvd2:1;                     // 3 Reserved
    Uint16 rsvd3:1;                     // 4 Reserved
    Uint16 rsvd4:11;                    // 15:5 Reserved
    Uint16 rsvd5:16;                    // 31:16 Reserved
};

union SYSPLLCTL1_REG {
    Uint32  all;
    struct  SYSPLLCTL1_BITS  bit;
};

struct SYSPLLMULT_BITS {                // bits description
    Uint16 IMULT:8;                     // 7:0 SYSPLL Integer Multiplier
    Uint16 rsvd1:2;                     // 9:8 Reserved
    Uint16 rsvd2:2;                     // 11:10 Reserved
    Uint16 rsvd3:2;                     // 13:12 Reserved
    Uint16 rsvd4:2;                     // 15:14 Reserved
    Uint16 ODIV:5;                      // 20:16 Output Clock Divider
    Uint16 rsvd5:3;                     // 23:21 Reserved
    Uint16 REFDIV:5;                    // 28:24 Reference Clock Divider
    Uint16 rsvd6:3;                     // 31:29 Reserved
};

union SYSPLLMULT_REG {
    Uint32  all;
    struct  SYSPLLMULT_BITS  bit;
};

struct SYSPLLSTS_BITS {                 // bits description
    Uint16 LOCKS:1;                     // 0 SYSPLL Lock Status Bit
    Uint16 SLIPS_NOTSUPPORTED:1;        // 1 SYSPLL Slip Status Bit
    Uint16 rsvd1:1;                     // 2 Reserved
    Uint16 rsvd2:1;                     // 3 Reserved
    Uint16 rsvd3:12;                    // 15:4 Reserved
    Uint16 rsvd4:16;                    // 31:16 Reserved
};

union SYSPLLSTS_REG {
    Uint32  all;
    struct  SYSPLLSTS_BITS  bit;
};

struct AUXPLLCTL1_BITS {                // bits description
    Uint16 PLLEN:1;                     // 0 AUXPLL enable/disable bit
    Uint16 PLLCLKEN:1;                  // 1 AUXPLL bypassed or included in the AUXPLLCLK path
    Uint16 rsvd1:1;                     // 2 Reserved
    Uint16 rsvd2:1;                     // 3 Reserved
    Uint16 rsvd3:1;                     // 4 Reserved
    Uint16 rsvd4:11;                    // 15:5 Reserved
    Uint16 rsvd5:16;                    // 31:16 Reserved
};

union AUXPLLCTL1_REG {
    Uint32  all;
    struct  AUXPLLCTL1_BITS  bit;
};

struct AUXPLLMULT_BITS {                // bits description
    Uint16 IMULT:8;                     // 7:0 AUXPLL Integer Multiplier
    Uint16 rsvd1:2;                     // 9:8 Reserved
    Uint16 rsvd2:2;                     // 11:10 Reserved
    Uint16 rsvd3:2;                     // 13:12 Reserved
    Uint16 rsvd4:2;                     // 15:14 Reserved
    Uint16 ODIV:5;                      // 20:16 Output Clock Divider
    Uint16 rsvd5:3;                     // 23:21 Reserved
    Uint16 REFDIV:5;                    // 28:24 Reference Clock Divider
    Uint16 rsvd6:3;                     // 31:29 Reserved
};

union AUXPLLMULT_REG {
    Uint32  all;
    struct  AUXPLLMULT_BITS  bit;
};

struct AUXPLLSTS_BITS {                 // bits description
    Uint16 LOCKS:1;                     // 0 AUXPLL Lock Status Bit
    Uint16 SLIPS_NOTSUPPORTED:1;        // 1 AUXPLL Slip Status Bit
    Uint16 rsvd1:1;                     // 2 Reserved
    Uint16 rsvd2:1;                     // 3 Reserved
    Uint16 rsvd3:12;                    // 15:4 Reserved
    Uint16 rsvd4:16;                    // 31:16 Reserved
};

union AUXPLLSTS_REG {
    Uint32  all;
    struct  AUXPLLSTS_BITS  bit;
};

struct SYSCLKDIVSEL_BITS {              // bits description
    Uint16 PLLSYSCLKDIV:6;              // 5:0 PLLSYSCLK Divide Select
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union SYSCLKDIVSEL_REG {
    Uint32  all;
    struct  SYSCLKDIVSEL_BITS  bit;
};

struct AUXCLKDIVSEL_BITS {              // bits description
    Uint16 AUXPLLDIV:3;                 // 2:0 AUXPLLCLK Divide Select
    Uint16 rsvd1:5;                     // 7:3 Reserved
    Uint16 MCANCLKDIV:5;                // 12:8 Divider between CANFD Source Clock and CANFD Bit CLK
    Uint16 rsvd2:3;                     // 15:13 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union AUXCLKDIVSEL_REG {
    Uint32  all;
    struct  AUXCLKDIVSEL_BITS  bit;
};

struct PERCLKDIVSEL_BITS {              // bits description
    Uint16 EPWMCLKDIV:2;                // 1:0 EPWM Clock Divide Select
    Uint16 rsvd1:2;                     // 3:2 Reserved
    Uint16 EMIF1CLKDIV:1;               // 4 EMIF1  Clock Divide Select
    Uint16 rsvd2:1;                     // 5 Reserved
    Uint16 EMIF2CLKDIV:1;               // 6 EMIF2 Clock Divide Select
    Uint16 rsvd3:9;                     // 15:7 Reserved
    Uint16 rsvd4:16;                    // 31:16 Reserved
};

union PERCLKDIVSEL_REG {
    Uint32  all;
    struct  PERCLKDIVSEL_BITS  bit;
};

struct XCLKOUTDIVSEL_BITS {             // bits description
    Uint16 XCLKOUTDIV:2;                // 1:0 XCLKOUT Divide Select
    Uint16 rsvd1:14;                    // 15:2 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union XCLKOUTDIVSEL_REG {
    Uint32  all;
    struct  XCLKOUTDIVSEL_BITS  bit;
};

struct CLBCLKCTL_BITS {                 // bits description
    Uint16 CLBCLKDIV:3;                 // 2:0 CLB clock divider configuration.
    Uint16 rsvd1:1;                     // 3 Reserved
    Uint16 TILECLKDIV:1;                // 4 CLB Tile clock divider configuration.
    Uint16 rsvd2:11;                    // 15:5 Reserved
    Uint16 CLKMODECLB1:1;               // 16 Clock mode of CLB1
    Uint16 CLKMODECLB2:1;               // 17 Clock mode of CLB2
    Uint16 CLKMODECLB3:1;               // 18 Clock mode of CLB3
    Uint16 CLKMODECLB4:1;               // 19 Clock mode of CLB4
    Uint16 CLKMODECLB5:1;               // 20 Clock mode of CLB5
    Uint16 CLKMODECLB6:1;               // 21 Clock mode of CLB6
    Uint16 CLKMODECLB7:1;               // 22 Clock mode of CLB7
    Uint16 CLKMODECLB8:1;               // 23 Clock mode of CLB8
    Uint16 rsvd3:8;                     // 31:24 Reserved
};

union CLBCLKCTL_REG {
    Uint32  all;
    struct  CLBCLKCTL_BITS  bit;
};

struct LOSPCP_BITS {                    // bits description
    Uint16 LSPCLKDIV:3;                 // 2:0 LSPCLK Divide Select
    Uint16 rsvd1:13;                    // 15:3 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union LOSPCP_REG {
    Uint32  all;
    struct  LOSPCP_BITS  bit;
};

struct MCDCR_BITS {                     // bits description
    Uint16 MCLKSTS:1;                   // 0 Missing Clock Status Bit
    Uint16 MCLKCLR:1;                   // 1 Missing Clock Clear Bit
    Uint16 MCLKOFF:1;                   // 2 Missing Clock Detect Off Bit
    Uint16 OSCOFF:1;                    // 3 Oscillator Clock Off Bit
    Uint16 rsvd1:12;                    // 15:4 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union MCDCR_REG {
    Uint32  all;
    struct  MCDCR_BITS  bit;
};

struct X1CNT_BITS {                     // bits description
    Uint16 X1CNT:10;                    // 9:0 X1 Counter
    Uint16 rsvd1:6;                     // 15:10 Reserved
    Uint16 CLR:1;                       // 16 X1 Counter Clear
    Uint16 rsvd2:15;                    // 31:17 Reserved
};

union X1CNT_REG {
    Uint32  all;
    struct  X1CNT_BITS  bit;
};

struct XTALCR_BITS {                    // bits description
    Uint16 OSCOFF:1;                    // 0 XTAL Oscillator powered-down
    Uint16 SE:1;                        // 1 XTAL Oscilator in Single-Ended mode
    Uint16 rsvd1:1;                     // 2 Reserved
    Uint16 rsvd2:13;                    // 15:3 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union XTALCR_REG {
    Uint32  all;
    struct  XTALCR_BITS  bit;
};

struct ETHERCATCLKCTL_BITS {            // bits description
    Uint16 DIVSRCSEL:1;                 // 0 Clock source select for the etherCAT clock divider.
    Uint16 ECATDIV:3;                   // 3:1 etherCAT clock divider configuration.
    Uint16 rsvd1:4;                     // 7:4 Reserved
    Uint16 PHYCLKEN:1;                  // 8 etherCAT PHY clock enable
    Uint16 rsvd2:7;                     // 15:9 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union ETHERCATCLKCTL_REG {
    Uint32  all;
    struct  ETHERCATCLKCTL_BITS  bit;
};

struct CMCLKCTL_BITS {                  // bits description
    Uint16 CMDIVSRCSEL:1;               // 0 Clock source select for the CM clock divider.
    Uint16 CMCLKDIV:3;                  // 3:1 CM clock divider configuration.
    Uint16 ETHDIVSRCSEL:1;              // 4 Clock source select for the etherNET clock divider.
    Uint16 ETHDIV:3;                    // 7:5 Ethernet clock divider configuration
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union CMCLKCTL_REG {
    Uint32  all;
    struct  CMCLKCTL_BITS  bit;
};

struct CLK_CFG_REGS {
    union   CLKSEM_REG                       CLKSEM;                       // Clock Control Semaphore Register
    union   CLKCFGLOCK1_REG                  CLKCFGLOCK1;                  // Lock bit for CLKCFG registers
    Uint16                                   rsvd1[4];                     // Reserved
    union   CLKSRCCTL1_REG                   CLKSRCCTL1;                   // Clock Source Control register-1
    union   CLKSRCCTL2_REG                   CLKSRCCTL2;                   // Clock Source Control register-2
    union   CLKSRCCTL3_REG                   CLKSRCCTL3;                   // Clock Source Control register-3
    union   SYSPLLCTL1_REG                   SYSPLLCTL1;                   // SYSPLL Control register-1
    Uint16                                   rsvd2[4];                     // Reserved
    union   SYSPLLMULT_REG                   SYSPLLMULT;                   // SYSPLL Multiplier register
    union   SYSPLLSTS_REG                    SYSPLLSTS;                    // SYSPLL Status register
    union   AUXPLLCTL1_REG                   AUXPLLCTL1;                   // AUXPLL Control register-1
    Uint16                                   rsvd3[4];                     // Reserved
    union   AUXPLLMULT_REG                   AUXPLLMULT;                   // AUXPLL Multiplier register
    union   AUXPLLSTS_REG                    AUXPLLSTS;                    // AUXPLL Status register
    union   SYSCLKDIVSEL_REG                 SYSCLKDIVSEL;                 // System Clock Divider Select register
    union   AUXCLKDIVSEL_REG                 AUXCLKDIVSEL;                 // Auxillary Clock Divider Select register
    union   PERCLKDIVSEL_REG                 PERCLKDIVSEL;                 // Peripheral Clock Divider Selet register
    union   XCLKOUTDIVSEL_REG                XCLKOUTDIVSEL;                // XCLKOUT Divider Select register
    union   CLBCLKCTL_REG                    CLBCLKCTL;                    // CLB Clocking Control Register
    union   LOSPCP_REG                       LOSPCP;                       // Low Speed Clock Source Prescalar
    union   MCDCR_REG                        MCDCR;                        // Missing Clock Detect Control Register
    union   X1CNT_REG                        X1CNT;                        // 10-bit Counter on X1 Clock
    union   XTALCR_REG                       XTALCR;                       // XTAL Control Register
    Uint16                                   rsvd4[2];                     // Reserved
    union   ETHERCATCLKCTL_REG               ETHERCATCLKCTL;               // ETHERCATCLKCTL
    union   CMCLKCTL_REG                     CMCLKCTL;                     // CMCLKCTL
};

struct CPUSYSLOCK1_BITS {               // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 rsvd2:1;                     // 1 Reserved
    Uint16 PIEVERRADDR:1;               // 2 Lock bit for PIEVERRADDR Register
    Uint16 PCLKCR0:1;                   // 3 Lock bit for PCLKCR0 Register
    Uint16 PCLKCR1:1;                   // 4 Lock bit for PCLKCR1 Register
    Uint16 PCLKCR2:1;                   // 5 Lock bit for PCLKCR2 Register
    Uint16 PCLKCR3:1;                   // 6 Lock bit for PCLKCR3 Register
    Uint16 PCLKCR4:1;                   // 7 Lock bit for PCLKCR4 Register
    Uint16 rsvd3:1;                     // 8 Reserved
    Uint16 PCLKCR6:1;                   // 9 Lock bit for PCLKCR6 Register
    Uint16 PCLKCR7:1;                   // 10 Lock bit for PCLKCR7 Register
    Uint16 PCLKCR8:1;                   // 11 Lock bit for PCLKCR8 Register
    Uint16 PCLKCR9:1;                   // 12 Lock bit for PCLKCR9 Register
    Uint16 PCLKCR10:1;                  // 13 Lock bit for PCLKCR10 Register
    Uint16 PCLKCR11:1;                  // 14 Lock bit for PCLKCR11 Register
    Uint16 rsvd4:1;                     // 15 Reserved
    Uint16 PCLKCR13:1;                  // 16 Lock bit for PCLKCR13 Register
    Uint16 PCLKCR14:1;                  // 17 Lock bit for PCLKCR14 Register
    Uint16 rsvd5:1;                     // 18 Reserved
    Uint16 PCLKCR16:1;                  // 19 Lock bit for PCLKCR16 Register
    Uint16 rsvd6:1;                     // 20 Reserved
    Uint16 LPMCR:1;                     // 21 Lock bit for LPMCR Register
    Uint16 GPIOLPMSEL0:1;               // 22 Lock bit for GPIOLPMSEL0 Register
    Uint16 GPIOLPMSEL1:1;               // 23 Lock bit for GPIOLPMSEL1 Register
    Uint16 PCLKCR17:1;                  // 24 Lock bit for PCLKCR17 Register
    Uint16 PCLKCR18:1;                  // 25 Lock bit for PCLKCR18 Register
    Uint16 rsvd7:1;                     // 26 Reserved
    Uint16 PCLKCR20:1;                  // 27 Lock bit for PCLKCR20 Register
    Uint16 PCLKCR21:1;                  // 28 Lock bit for PCLKCR21 Register
    Uint16 PCLKCR22:1;                  // 29 Lock bit for PCLKCR22 Register
    Uint16 PCLKCR23:1;                  // 30 Lock bit for PCLKCR23 Register
    Uint16 rsvd8:1;                     // 31 Reserved
};

union CPUSYSLOCK1_REG {
    Uint32  all;
    struct  CPUSYSLOCK1_BITS  bit;
};

struct CPUSYSLOCK2_BITS {               // bits description
    Uint16 ETHERCATCTL:1;               // 0 Lock bit for ETHERCATCTL register
    Uint16 rsvd1:15;                    // 15:1 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union CPUSYSLOCK2_REG {
    Uint32  all;
    struct  CPUSYSLOCK2_BITS  bit;
};

struct PIEVERRADDR_BITS {               // bits description
    Uint32 ADDR:22;                     // 21:0 PIE Vector Fetch Error Handler Routine Address
    Uint16 rsvd1:10;                    // 31:22 Reserved
};

union PIEVERRADDR_REG {
    Uint32  all;
    struct  PIEVERRADDR_BITS  bit;
};

struct PCLKCR0_BITS {                   // bits description
    Uint16 CLA1:1;                      // 0 CLA1 Clock Enable Bit
    Uint16 rsvd1:1;                     // 1 Reserved
    Uint16 DMA:1;                       // 2 DMA Clock Enable bit
    Uint16 CPUTIMER0:1;                 // 3 CPUTIMER0 Clock Enable bit
    Uint16 CPUTIMER1:1;                 // 4 CPUTIMER1 Clock Enable bit
    Uint16 CPUTIMER2:1;                 // 5 CPUTIMER2 Clock Enable bit
    Uint16 rsvd2:7;                     // 12:6 Reserved
    Uint16 CPUBGCRC:1;                  // 13 CPUBGCRC Clock Enable Bit
    Uint16 CLA1BGCRC:1;                 // 14 CLA1BGCRC Clock Enable Bit
    Uint16 rsvd3:1;                     // 15 Reserved
    Uint16 HRCAL:1;                     // 16 HRCAL Clock Enable Bit
    Uint16 rsvd4:1;                     // 17 Reserved
    Uint16 TBCLKSYNC:1;                 // 18 EPWM Time Base Clock sync
    Uint16 GTBCLKSYNC:1;                // 19 EPWM Time Base Clock Global sync
    Uint16 rsvd5:4;                     // 23:20 Reserved
    Uint16 ERAD:1;                      // 24 ERAD module clock enable
    Uint16 rsvd6:7;                     // 31:25 Reserved
};

union PCLKCR0_REG {
    Uint32  all;
    struct  PCLKCR0_BITS  bit;
};

struct PCLKCR1_BITS {                   // bits description
    Uint16 EMIF1:1;                     // 0 EMIF1 Clock Enable bit
    Uint16 EMIF2:1;                     // 1 EMIF2 Clock Enable bit
    Uint16 rsvd1:14;                    // 15:2 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union PCLKCR1_REG {
    Uint32  all;
    struct  PCLKCR1_BITS  bit;
};

struct PCLKCR2_BITS {                   // bits description
    Uint16 EPWM1:1;                     // 0 EPWM1 Clock Enable bit
    Uint16 EPWM2:1;                     // 1 EPWM2 Clock Enable bit
    Uint16 EPWM3:1;                     // 2 EPWM3 Clock Enable bit
    Uint16 EPWM4:1;                     // 3 EPWM4 Clock Enable bit
    Uint16 EPWM5:1;                     // 4 EPWM5 Clock Enable bit
    Uint16 EPWM6:1;                     // 5 EPWM6 Clock Enable bit
    Uint16 EPWM7:1;                     // 6 EPWM7 Clock Enable bit
    Uint16 EPWM8:1;                     // 7 EPWM8 Clock Enable bit
    Uint16 EPWM9:1;                     // 8 EPWM9 Clock Enable bit
    Uint16 EPWM10:1;                    // 9 EPWM10 Clock Enable bit
    Uint16 EPWM11:1;                    // 10 EPWM11 Clock Enable bit
    Uint16 EPWM12:1;                    // 11 EPWM12 Clock Enable bit
    Uint16 EPWM13:1;                    // 12 EPWM13 Clock Enable bit
    Uint16 EPWM14:1;                    // 13 EPWM14 Clock Enable bit
    Uint16 EPWM15:1;                    // 14 EPWM15 Clock Enable bit
    Uint16 EPWM16:1;                    // 15 EPWM16 Clock Enable bit
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union PCLKCR2_REG {
    Uint32  all;
    struct  PCLKCR2_BITS  bit;
};

struct PCLKCR3_BITS {                   // bits description
    Uint16 ECAP1:1;                     // 0 ECAP1 Clock Enable bit
    Uint16 ECAP2:1;                     // 1 ECAP2 Clock Enable bit
    Uint16 ECAP3:1;                     // 2 ECAP3 Clock Enable bit
    Uint16 ECAP4:1;                     // 3 ECAP4 Clock Enable bit
    Uint16 ECAP5:1;                     // 4 ECAP5 Clock Enable bit
    Uint16 ECAP6:1;                     // 5 ECAP6 Clock Enable bit
    Uint16 ECAP7:1;                     // 6 ECAP7 Clock Enable bit
    Uint16 rsvd1:1;                     // 7 Reserved
    Uint16 rsvd2:8;                     // 15:8 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union PCLKCR3_REG {
    Uint32  all;
    struct  PCLKCR3_BITS  bit;
};

struct PCLKCR4_BITS {                   // bits description
    Uint16 EQEP1:1;                     // 0 EQEP1 Clock Enable bit
    Uint16 EQEP2:1;                     // 1 EQEP2 Clock Enable bit
    Uint16 EQEP3:1;                     // 2 EQEP3 Clock Enable bit
    Uint16 rsvd1:1;                     // 3 Reserved
    Uint16 rsvd2:12;                    // 15:4 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union PCLKCR4_REG {
    Uint32  all;
    struct  PCLKCR4_BITS  bit;
};

struct PCLKCR6_BITS {                   // bits description
    Uint16 SD1:1;                       // 0 SD1 Clock Enable bit
    Uint16 SD2:1;                       // 1 SD2 Clock Enable bit
    Uint16 rsvd1:1;                     // 2 Reserved
    Uint16 rsvd2:1;                     // 3 Reserved
    Uint16 rsvd3:1;                     // 4 Reserved
    Uint16 rsvd4:1;                     // 5 Reserved
    Uint16 rsvd5:1;                     // 6 Reserved
    Uint16 rsvd6:1;                     // 7 Reserved
    Uint16 rsvd7:8;                     // 15:8 Reserved
    Uint16 rsvd8:16;                    // 31:16 Reserved
};

union PCLKCR6_REG {
    Uint32  all;
    struct  PCLKCR6_BITS  bit;
};

struct PCLKCR7_BITS {                   // bits description
    Uint16 SCI_A:1;                     // 0 SCI_A Clock Enable bit
    Uint16 SCI_B:1;                     // 1 SCI_B Clock Enable bit
    Uint16 SCI_C:1;                     // 2 SCI_C Clock Enable bit
    Uint16 SCI_D:1;                     // 3 SCI_D Clock Enable bit
    Uint16 rsvd1:12;                    // 15:4 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union PCLKCR7_REG {
    Uint32  all;
    struct  PCLKCR7_BITS  bit;
};

struct PCLKCR8_BITS {                   // bits description
    Uint16 SPI_A:1;                     // 0 SPI_A Clock Enable bit
    Uint16 SPI_B:1;                     // 1 SPI_B Clock Enable bit
    Uint16 SPI_C:1;                     // 2 SPI_C Clock Enable bit
    Uint16 SPI_D:1;                     // 3 SPI_D Clock Enable bit
    Uint16 rsvd1:12;                    // 15:4 Reserved
    Uint16 rsvd2:1;                     // 16 Reserved
    Uint16 rsvd3:1;                     // 17 Reserved
    Uint16 rsvd4:14;                    // 31:18 Reserved
};

union PCLKCR8_REG {
    Uint32  all;
    struct  PCLKCR8_BITS  bit;
};

struct PCLKCR9_BITS {                   // bits description
    Uint16 I2C_A:1;                     // 0 I2C_A Clock Enable bit
    Uint16 I2C_B:1;                     // 1 I2C_B Clock Enable bit
    Uint16 rsvd1:14;                    // 15:2 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union PCLKCR9_REG {
    Uint32  all;
    struct  PCLKCR9_BITS  bit;
};

struct PCLKCR10_BITS {                  // bits description
    Uint16 CAN_A:1;                     // 0 CAN_A Clock Enable bit
    Uint16 CAN_B:1;                     // 1 CAN_B Clock Enable bit
    Uint16 rsvd1:1;                     // 2 Reserved
    Uint16 rsvd2:1;                     // 3 Reserved
    Uint16 MCAN_A:1;                    // 4 MCAN_A Clock Enable bit
    Uint16 rsvd3:1;                     // 5 Reserved
    Uint16 rsvd4:1;                     // 6 Reserved
    Uint16 rsvd5:1;                     // 7 Reserved
    Uint16 rsvd6:8;                     // 15:8 Reserved
    Uint16 rsvd7:16;                    // 31:16 Reserved
};

union PCLKCR10_REG {
    Uint32  all;
    struct  PCLKCR10_BITS  bit;
};

struct PCLKCR11_BITS {                  // bits description
    Uint16 McBSP_A:1;                   // 0 McBSP_A Clock Enable bit
    Uint16 McBSP_B:1;                   // 1 McBSP_B Clock Enable bit
    Uint16 rsvd1:14;                    // 15:2 Reserved
    Uint16 USB_A:1;                     // 16 USB_A Clock Enable bit
    Uint16 rsvd2:1;                     // 17 Reserved
    Uint16 rsvd3:14;                    // 31:18 Reserved
};

union PCLKCR11_REG {
    Uint32  all;
    struct  PCLKCR11_BITS  bit;
};

struct PCLKCR13_BITS {                  // bits description
    Uint16 ADC_A:1;                     // 0 ADC_A Clock Enable bit
    Uint16 ADC_B:1;                     // 1 ADC_B Clock Enable bit
    Uint16 ADC_C:1;                     // 2 ADC_C Clock Enable bit
    Uint16 ADC_D:1;                     // 3 ADC_D Clock Enable bit
    Uint16 rsvd1:12;                    // 15:4 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union PCLKCR13_REG {
    Uint32  all;
    struct  PCLKCR13_BITS  bit;
};

struct PCLKCR14_BITS {                  // bits description
    Uint16 CMPSS1:1;                    // 0 CMPSS1 Clock Enable bit
    Uint16 CMPSS2:1;                    // 1 CMPSS2 Clock Enable bit
    Uint16 CMPSS3:1;                    // 2 CMPSS3 Clock Enable bit
    Uint16 CMPSS4:1;                    // 3 CMPSS4 Clock Enable bit
    Uint16 CMPSS5:1;                    // 4 CMPSS5 Clock Enable bit
    Uint16 CMPSS6:1;                    // 5 CMPSS6 Clock Enable bit
    Uint16 CMPSS7:1;                    // 6 CMPSS7 Clock Enable bit
    Uint16 CMPSS8:1;                    // 7 CMPSS8 Clock Enable bit
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union PCLKCR14_REG {
    Uint32  all;
    struct  PCLKCR14_BITS  bit;
};

struct PCLKCR16_BITS {                  // bits description
    Uint16 rsvd1:16;                    // 15:0 Reserved
    Uint16 DAC_A:1;                     // 16 Buffered_DAC12_1 Clock Enable Bit
    Uint16 DAC_B:1;                     // 17 Buffered_DAC12_2 Clock Enable Bit
    Uint16 DAC_C:1;                     // 18 Buffered_DAC12_3 Clock Enable Bit
    Uint16 rsvd2:1;                     // 19 Reserved
    Uint16 rsvd3:12;                    // 31:20 Reserved
};

union PCLKCR16_REG {
    Uint32  all;
    struct  PCLKCR16_BITS  bit;
};

struct PCLKCR17_BITS {                  // bits description
    Uint16 CLB1:1;                      // 0 CLB1 Clock Enable bit
    Uint16 CLB2:1;                      // 1 CLB2 Clock Enable bit
    Uint16 CLB3:1;                      // 2 CLB3 Clock Enable bit
    Uint16 CLB4:1;                      // 3 CLB4 Clock Enable bit
    Uint16 CLB5:1;                      // 4 CLB5 Clock Enable bit
    Uint16 CLB6:1;                      // 5 CLB6 Clock Enable bit
    Uint16 CLB7:1;                      // 6 CLB7 Clock Enable bit
    Uint16 CLB8:1;                      // 7 CLB8 Clock Enable bit
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union PCLKCR17_REG {
    Uint32  all;
    struct  PCLKCR17_BITS  bit;
};

struct PCLKCR18_BITS {                  // bits description
    Uint16 FSITX_A:1;                   // 0 FSITX_A Clock Enable bit
    Uint16 FSITX_B:1;                   // 1 FSITX_B Clock Enable bit
    Uint16 rsvd1:1;                     // 2 Reserved
    Uint16 rsvd2:1;                     // 3 Reserved
    Uint16 rsvd3:1;                     // 4 Reserved
    Uint16 rsvd4:1;                     // 5 Reserved
    Uint16 rsvd5:1;                     // 6 Reserved
    Uint16 rsvd6:1;                     // 7 Reserved
    Uint16 rsvd7:8;                     // 15:8 Reserved
    Uint16 FSIRX_A:1;                   // 16 FSIRX_A Clock Enable bit
    Uint16 FSIRX_B:1;                   // 17 FSIRX_B Clock Enable bit
    Uint16 FSIRX_C:1;                   // 18 FSIRX_C Clock Enable bit
    Uint16 FSIRX_D:1;                   // 19 FSIRX_D Clock Enable bit
    Uint16 FSIRX_E:1;                   // 20 FSIRX_E Clock Enable bit
    Uint16 FSIRX_F:1;                   // 21 FSIRX_F Clock Enable bit
    Uint16 FSIRX_G:1;                   // 22 FSIRX_G Clock Enable bit
    Uint16 FSIRX_H:1;                   // 23 FSIRX_H Clock Enable bit
    Uint16 rsvd8:8;                     // 31:24 Reserved
};

union PCLKCR18_REG {
    Uint32  all;
    struct  PCLKCR18_BITS  bit;
};

struct PCLKCR20_BITS {                  // bits description
    Uint16 PMBUS_A:1;                   // 0 PMBUS_A Clock Enable bit
    Uint16 rsvd1:1;                     // 1 Reserved
    Uint16 rsvd2:14;                    // 15:2 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union PCLKCR20_REG {
    Uint32  all;
    struct  PCLKCR20_BITS  bit;
};

struct PCLKCR21_BITS {                  // bits description
    Uint16 DCC0:1;                      // 0 DCC0 Clock Enable Bit
    Uint16 DCC1:1;                      // 1 DCC1 Clock Enable Bit
    Uint16 DCC2:1;                      // 2 DCC2 Clock Enable Bit
    Uint16 rsvd1:13;                    // 15:3 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union PCLKCR21_REG {
    Uint32  all;
    struct  PCLKCR21_BITS  bit;
};

struct PCLKCR22_BITS {                  // bits description
    Uint16 MPOSTCLK:1;                  // 0 MPOSTCLK Clock Enable Bit
    Uint16 rsvd1:15;                    // 15:1 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union PCLKCR22_REG {
    Uint32  all;
    struct  PCLKCR22_BITS  bit;
};

struct PCLKCR23_BITS {                  // bits description
    Uint16 ETHERCAT:1;                  // 0 ETHERCAT Clock Enable Bit
    Uint16 rsvd1:15;                    // 15:1 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union PCLKCR23_REG {
    Uint32  all;
    struct  PCLKCR23_BITS  bit;
};

struct SIMRESET_BITS {                  // bits description
    Uint16 CPU1RSn:1;                   // 0 Generates a reset to CPU
    Uint16 XRSn:1;                      // 1 Generates a simulated XRSn
    Uint16 rsvd1:14;                    // 15:2 Reserved
    Uint16 KEY:16;                      // 31:16 Key value
};

union SIMRESET_REG {
    Uint32  all;
    struct  SIMRESET_BITS  bit;
};

struct LPMCR_BITS {                     // bits description
    Uint16 LPM:2;                       // 1:0 Low Power Mode setting
    Uint16 QUALSTDBY:6;                 // 7:2 STANDBY Wakeup Pin Qualification Setting
    Uint16 rsvd1:7;                     // 14:8 Reserved
    Uint16 WDINTE:1;                    // 15 Enable for WDINT wakeup from STANDBY
    Uint16 rsvd2:2;                     // 17:16 Reserved
    Uint16 rsvd3:13;                    // 30:18 Reserved
    Uint16 rsvd4:1;                     // 31 Reserved
};

union LPMCR_REG {
    Uint32  all;
    struct  LPMCR_BITS  bit;
};

struct GPIOLPMSEL0_BITS {               // bits description
    Uint16 GPIO0:1;                     // 0 GPIO0 Enable for LPM Wakeup
    Uint16 GPIO1:1;                     // 1 GPIO1 Enable for LPM Wakeup
    Uint16 GPIO2:1;                     // 2 GPIO2 Enable for LPM Wakeup
    Uint16 GPIO3:1;                     // 3 GPIO3 Enable for LPM Wakeup
    Uint16 GPIO4:1;                     // 4 GPIO4 Enable for LPM Wakeup
    Uint16 GPIO5:1;                     // 5 GPIO5 Enable for LPM Wakeup
    Uint16 GPIO6:1;                     // 6 GPIO6 Enable for LPM Wakeup
    Uint16 GPIO7:1;                     // 7 GPIO7 Enable for LPM Wakeup
    Uint16 GPIO8:1;                     // 8 GPIO8 Enable for LPM Wakeup
    Uint16 GPIO9:1;                     // 9 GPIO9 Enable for LPM Wakeup
    Uint16 GPIO10:1;                    // 10 GPIO10 Enable for LPM Wakeup
    Uint16 GPIO11:1;                    // 11 GPIO11 Enable for LPM Wakeup
    Uint16 GPIO12:1;                    // 12 GPIO12 Enable for LPM Wakeup
    Uint16 GPIO13:1;                    // 13 GPIO13 Enable for LPM Wakeup
    Uint16 GPIO14:1;                    // 14 GPIO14 Enable for LPM Wakeup
    Uint16 GPIO15:1;                    // 15 GPIO15 Enable for LPM Wakeup
    Uint16 GPIO16:1;                    // 16 GPIO16 Enable for LPM Wakeup
    Uint16 GPIO17:1;                    // 17 GPIO17 Enable for LPM Wakeup
    Uint16 GPIO18:1;                    // 18 GPIO18 Enable for LPM Wakeup
    Uint16 GPIO19:1;                    // 19 GPIO19 Enable for LPM Wakeup
    Uint16 GPIO20:1;                    // 20 GPIO20 Enable for LPM Wakeup
    Uint16 GPIO21:1;                    // 21 GPIO21 Enable for LPM Wakeup
    Uint16 GPIO22:1;                    // 22 GPIO22 Enable for LPM Wakeup
    Uint16 GPIO23:1;                    // 23 GPIO23 Enable for LPM Wakeup
    Uint16 GPIO24:1;                    // 24 GPIO24 Enable for LPM Wakeup
    Uint16 GPIO25:1;                    // 25 GPIO25 Enable for LPM Wakeup
    Uint16 GPIO26:1;                    // 26 GPIO26 Enable for LPM Wakeup
    Uint16 GPIO27:1;                    // 27 GPIO27 Enable for LPM Wakeup
    Uint16 GPIO28:1;                    // 28 GPIO28 Enable for LPM Wakeup
    Uint16 GPIO29:1;                    // 29 GPIO29 Enable for LPM Wakeup
    Uint16 GPIO30:1;                    // 30 GPIO30 Enable for LPM Wakeup
    Uint16 GPIO31:1;                    // 31 GPIO31 Enable for LPM Wakeup
};

union GPIOLPMSEL0_REG {
    Uint32  all;
    struct  GPIOLPMSEL0_BITS  bit;
};

struct GPIOLPMSEL1_BITS {               // bits description
    Uint16 GPIO32:1;                    // 0 GPIO32 Enable for LPM Wakeup
    Uint16 GPIO33:1;                    // 1 GPIO33 Enable for LPM Wakeup
    Uint16 GPIO34:1;                    // 2 GPIO34 Enable for LPM Wakeup
    Uint16 GPIO35:1;                    // 3 GPIO35 Enable for LPM Wakeup
    Uint16 GPIO36:1;                    // 4 GPIO36 Enable for LPM Wakeup
    Uint16 GPIO37:1;                    // 5 GPIO37 Enable for LPM Wakeup
    Uint16 GPIO38:1;                    // 6 GPIO38 Enable for LPM Wakeup
    Uint16 GPIO39:1;                    // 7 GPIO39 Enable for LPM Wakeup
    Uint16 GPIO40:1;                    // 8 GPIO40 Enable for LPM Wakeup
    Uint16 GPIO41:1;                    // 9 GPIO41 Enable for LPM Wakeup
    Uint16 GPIO42:1;                    // 10 GPIO42 Enable for LPM Wakeup
    Uint16 GPIO43:1;                    // 11 GPIO43 Enable for LPM Wakeup
    Uint16 GPIO44:1;                    // 12 GPIO44 Enable for LPM Wakeup
    Uint16 GPIO45:1;                    // 13 GPIO45 Enable for LPM Wakeup
    Uint16 GPIO46:1;                    // 14 GPIO46 Enable for LPM Wakeup
    Uint16 GPIO47:1;                    // 15 GPIO47 Enable for LPM Wakeup
    Uint16 GPIO48:1;                    // 16 GPIO48 Enable for LPM Wakeup
    Uint16 GPIO49:1;                    // 17 GPIO49 Enable for LPM Wakeup
    Uint16 GPIO50:1;                    // 18 GPIO50 Enable for LPM Wakeup
    Uint16 GPIO51:1;                    // 19 GPIO51 Enable for LPM Wakeup
    Uint16 GPIO52:1;                    // 20 GPIO52 Enable for LPM Wakeup
    Uint16 GPIO53:1;                    // 21 GPIO53 Enable for LPM Wakeup
    Uint16 GPIO54:1;                    // 22 GPIO54 Enable for LPM Wakeup
    Uint16 GPIO55:1;                    // 23 GPIO55 Enable for LPM Wakeup
    Uint16 GPIO56:1;                    // 24 GPIO56 Enable for LPM Wakeup
    Uint16 GPIO57:1;                    // 25 GPIO57 Enable for LPM Wakeup
    Uint16 GPIO58:1;                    // 26 GPIO58 Enable for LPM Wakeup
    Uint16 GPIO59:1;                    // 27 GPIO59 Enable for LPM Wakeup
    Uint16 GPIO60:1;                    // 28 GPIO60 Enable for LPM Wakeup
    Uint16 GPIO61:1;                    // 29 GPIO61 Enable for LPM Wakeup
    Uint16 GPIO62:1;                    // 30 GPIO62 Enable for LPM Wakeup
    Uint16 GPIO63:1;                    // 31 GPIO63 Enable for LPM Wakeup
};

union GPIOLPMSEL1_REG {
    Uint32  all;
    struct  GPIOLPMSEL1_BITS  bit;
};

struct TMR2CLKCTL_BITS {                // bits description
    Uint16 TMR2CLKSRCSEL:3;             // 2:0 CPU Timer 2 Clock Source Select Bit
    Uint16 TMR2CLKPRESCALE:3;           // 5:3 CPU Timer 2 Clock Pre-Scale Value
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union TMR2CLKCTL_REG {
    Uint32  all;
    struct  TMR2CLKCTL_BITS  bit;
};

struct RESCCLR_BITS {                   // bits description
    Uint16 POR:1;                       // 0 POR Reset Cause Indication Bit
    Uint16 XRSn:1;                      // 1 XRSn Reset Cause Indication Bit
    Uint16 WDRSn:1;                     // 2 WDRSn Reset Cause Indication Bit
    Uint16 NMIWDRSn:1;                  // 3 NMIWDRSn Reset Cause Indication Bit
    Uint16 rsvd1:1;                     // 4 Reserved
    Uint16 HWBISTn:1;                   // 5 HWBISTn Reset Cause Indication Bit
    Uint16 rsvd2:1;                     // 6 Reserved
    Uint16 rsvd3:1;                     // 7 Reserved
    Uint16 SCCRESETn:1;                 // 8 SCCRESETn Reset Cause Indication Bit
    Uint16 ECAT_RESET_OUT:1;            // 9 ECAT_RESET_OUT Reset Cause Indication Bit
    Uint16 SIMRESET_CPU1RSn:1;          // 10 SIMRESET_CPU1RSn Reset Cause Indication Bit
    Uint16 SIMRESET_XRSn:1;             // 11 SIMRESET_XRSn Reset Cause Indication Bit
    Uint16 rsvd4:4;                     // 15:12 Reserved
    Uint16 rsvd5:16;                    // 31:16 Reserved
};

union RESCCLR_REG {
    Uint32  all;
    struct  RESCCLR_BITS  bit;
};

struct RESC_BITS {                      // bits description
    Uint16 POR:1;                       // 0 POR Reset Cause Indication Bit
    Uint16 XRSn:1;                      // 1 XRSn Reset Cause Indication Bit
    Uint16 WDRSn:1;                     // 2 WDRSn Reset Cause Indication Bit
    Uint16 NMIWDRSn:1;                  // 3 NMIWDRSn Reset Cause Indication Bit
    Uint16 rsvd1:1;                     // 4 Reserved
    Uint16 HWBISTn:1;                   // 5 HWBISTn Reset Cause Indication Bit
    Uint16 rsvd2:1;                     // 6 Reserved
    Uint16 rsvd3:1;                     // 7 Reserved
    Uint16 SCCRESETn:1;                 // 8 SCCRESETn Reset Cause Indication Bit
    Uint16 ECAT_RESET_OUT:1;            // 9 ECAT_RESET_OUT Reset Cause Indication Bit
    Uint16 SIMRESET_CPU1RSn:1;          // 10 SIMRESET_CPU1RSn Reset Cause Indication Bit
    Uint16 SIMRESET_XRSn:1;             // 11 SIMRESET_XRSn Reset Cause Indication Bit
    Uint16 rsvd4:4;                     // 15:12 Reserved
    Uint16 rsvd5:14;                    // 29:16 Reserved
    Uint16 XRSn_pin_status:1;           // 30 XRSN Pin Status
    Uint16 TRSTn_pin_status:1;          // 31 TRSTn Status
};

union RESC_REG {
    Uint32  all;
    struct  RESC_BITS  bit;
};

struct MCANWAKESTATUS_BITS {            // bits description
    Uint16 WAKE:1;                      // 0 MCAN Wake Status
    Uint16 rsvd1:15;                    // 15:1 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union MCANWAKESTATUS_REG {
    Uint32  all;
    struct  MCANWAKESTATUS_BITS  bit;
};

struct MCANWAKESTATUSCLR_BITS {         // bits description
    Uint16 WAKE:1;                      // 0 Cear bit for MCANWAKESTATUS.WAKE bit
    Uint16 rsvd1:15;                    // 15:1 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union MCANWAKESTATUSCLR_REG {
    Uint32  all;
    struct  MCANWAKESTATUSCLR_BITS  bit;
};

struct CPU_SYS_REGS {
    union   CPUSYSLOCK1_REG                  CPUSYSLOCK1;                  // Lock bit for CPUSYS registers
    union   CPUSYSLOCK2_REG                  CPUSYSLOCK2;                  // Lock bit for CPUSYS registers
    Uint16                                   rsvd1[6];                     // Reserved
    union   PIEVERRADDR_REG                  PIEVERRADDR;                  // PIE Vector Fetch Error Address register
    Uint16                                   rsvd2[22];                    // Reserved
    union   PCLKCR0_REG                      PCLKCR0;                      // Peripheral Clock Gating Registers
    union   PCLKCR1_REG                      PCLKCR1;                      // Peripheral Clock Gating Registers
    union   PCLKCR2_REG                      PCLKCR2;                      // Peripheral Clock Gating Registers
    union   PCLKCR3_REG                      PCLKCR3;                      // Peripheral Clock Gating Registers
    union   PCLKCR4_REG                      PCLKCR4;                      // Peripheral Clock Gating Registers
    Uint16                                   rsvd3[2];                     // Reserved
    union   PCLKCR6_REG                      PCLKCR6;                      // Peripheral Clock Gating Registers
    union   PCLKCR7_REG                      PCLKCR7;                      // Peripheral Clock Gating Registers
    union   PCLKCR8_REG                      PCLKCR8;                      // Peripheral Clock Gating Registers
    union   PCLKCR9_REG                      PCLKCR9;                      // Peripheral Clock Gating Registers
    union   PCLKCR10_REG                     PCLKCR10;                     // Peripheral Clock Gating Registers
    union   PCLKCR11_REG                     PCLKCR11;                     // Peripheral Clock Gating Registers
    Uint16                                   rsvd4[2];                     // Reserved
    union   PCLKCR13_REG                     PCLKCR13;                     // Peripheral Clock Gating Registers
    union   PCLKCR14_REG                     PCLKCR14;                     // Peripheral Clock Gating Registers
    Uint16                                   rsvd5[2];                     // Reserved
    union   PCLKCR16_REG                     PCLKCR16;                     // Peripheral Clock Gating Registers
    union   PCLKCR17_REG                     PCLKCR17;                     // Peripheral Clock Gating Registers
    union   PCLKCR18_REG                     PCLKCR18;                     // Peripheral Clock Gating Registers
    Uint16                                   rsvd6[2];                     // Reserved
    union   PCLKCR20_REG                     PCLKCR20;                     // Peripheral Clock Gating Registers
    union   PCLKCR21_REG                     PCLKCR21;                     // Peripheral Clock Gating Registers
    union   PCLKCR22_REG                     PCLKCR22;                     // Peripheral Clock Gating Registers
    union   PCLKCR23_REG                     PCLKCR23;                     // Peripheral Clock Gating Registers
    Uint16                                   rsvd7[30];                    // Reserved
    union   SIMRESET_REG                     SIMRESET;                     // Simulated Reset Register
    Uint16                                   rsvd8[4];                     // Reserved
    union   LPMCR_REG                        LPMCR;                        // LPM Control Register
    union   GPIOLPMSEL0_REG                  GPIOLPMSEL0;                  // GPIO LPM Wakeup select registers
    union   GPIOLPMSEL1_REG                  GPIOLPMSEL1;                  // GPIO LPM Wakeup select registers
    union   TMR2CLKCTL_REG                   TMR2CLKCTL;                   // Timer2 Clock Measurement functionality control register
    union   RESCCLR_REG                      RESCCLR;                      // Reset Cause Clear Register
    union   RESC_REG                         RESC;                         // Reset Cause register
    Uint16                                   rsvd9[22];                    // Reserved
    union   MCANWAKESTATUS_REG               MCANWAKESTATUS;               // MCAN Wake Status Register
    union   MCANWAKESTATUSCLR_REG            MCANWAKESTATUSCLR;            // MCAN Wake Status Clear Register
};

struct CLA1TASKSRCSELLOCK_BITS {        // bits description
    Uint16 CLA1TASKSRCSEL1:1;           // 0 CLA1TASKSRCSEL1 Register Lock bit
    Uint16 CLA1TASKSRCSEL2:1;           // 1 CLA1TASKSRCSEL2 Register Lock bit
    Uint16 rsvd1:14;                    // 15:2 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union CLA1TASKSRCSELLOCK_REG {
    Uint32  all;
    struct  CLA1TASKSRCSELLOCK_BITS  bit;
};

struct DMACHSRCSELLOCK_BITS {           // bits description
    Uint16 DMACHSRCSEL1:1;              // 0 DMACHSRCSEL1 Register Lock bit
    Uint16 DMACHSRCSEL2:1;              // 1 DMACHSRCSEL2 Register Lock bit
    Uint16 rsvd1:14;                    // 15:2 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union DMACHSRCSELLOCK_REG {
    Uint32  all;
    struct  DMACHSRCSELLOCK_BITS  bit;
};

struct CLA1TASKSRCSEL1_BITS {           // bits description
    Uint16 TASK1:8;                     // 7:0 Selects the Trigger Source for TASK1 of CLA1
    Uint16 TASK2:8;                     // 15:8 Selects the Trigger Source for TASK2 of CLA1
    Uint16 TASK3:8;                     // 23:16 Selects the Trigger Source for TASK3 of CLA1
    Uint16 TASK4:8;                     // 31:24 Selects the Trigger Source for TASK4 of CLA1
};

union CLA1TASKSRCSEL1_REG {
    Uint32  all;
    struct  CLA1TASKSRCSEL1_BITS  bit;
};

struct CLA1TASKSRCSEL2_BITS {           // bits description
    Uint16 TASK5:8;                     // 7:0 Selects the Trigger Source for TASK5 of CLA1
    Uint16 TASK6:8;                     // 15:8 Selects the Trigger Source for TASK6 of CLA1
    Uint16 TASK7:8;                     // 23:16 Selects the Trigger Source for TASK7 of CLA1
    Uint16 TASK8:8;                     // 31:24 Selects the Trigger Source for TASK8 of CLA1
};

union CLA1TASKSRCSEL2_REG {
    Uint32  all;
    struct  CLA1TASKSRCSEL2_BITS  bit;
};

struct DMACHSRCSEL1_BITS {              // bits description
    Uint16 CH1:8;                       // 7:0 Selects the Trigger and Sync Source CH1 of DMA
    Uint16 CH2:8;                       // 15:8 Selects the Trigger and Sync Source CH2 of DMA
    Uint16 CH3:8;                       // 23:16 Selects the Trigger and Sync Source CH3 of DMA
    Uint16 CH4:8;                       // 31:24 Selects the Trigger and Sync Source CH4 of DMA
};

union DMACHSRCSEL1_REG {
    Uint32  all;
    struct  DMACHSRCSEL1_BITS  bit;
};

struct DMACHSRCSEL2_BITS {              // bits description
    Uint16 CH5:8;                       // 7:0 Selects the Trigger and Sync Source CH5 of DMA
    Uint16 CH6:8;                       // 15:8 Selects the Trigger and Sync Source CH6 of DMA
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union DMACHSRCSEL2_REG {
    Uint32  all;
    struct  DMACHSRCSEL2_BITS  bit;
};

struct DMA_CLA_SRC_SEL_REGS {
    union   CLA1TASKSRCSELLOCK_REG           CLA1TASKSRCSELLOCK;           // CLA1 Task Trigger Source Select Lock Register
    Uint16                                   rsvd1[2];                     // Reserved
    union   DMACHSRCSELLOCK_REG              DMACHSRCSELLOCK;              // DMA Channel Triger Source Select Lock Register
    union   CLA1TASKSRCSEL1_REG              CLA1TASKSRCSEL1;              // CLA1 Task Trigger Source Select Register-1
    union   CLA1TASKSRCSEL2_REG              CLA1TASKSRCSEL2;              // CLA1 Task Trigger Source Select Register-2
    Uint16                                   rsvd2[12];                    // Reserved
    union   DMACHSRCSEL1_REG                 DMACHSRCSEL1;                 // DMA Channel Trigger Source Select Register-1
    union   DMACHSRCSEL2_REG                 DMACHSRCSEL2;                 // DMA Channel Trigger Source Select Register-2
};

struct DEVCFGLOCK1_BITS {               // bits description
    Uint16 CPUSEL0:1;                   // 0 Lock bit for CPUSEL0 register
    Uint16 CPUSEL1:1;                   // 1 Lock bit for CPUSEL1 register
    Uint16 CPUSEL2:1;                   // 2 Lock bit for CPUSEL2 register
    Uint16 rsvd1:1;                     // 3 Reserved
    Uint16 CPUSEL4:1;                   // 4 Lock bit for CPUSEL4 register
    Uint16 CPUSEL5:1;                   // 5 Lock bit for CPUSEL5 register
    Uint16 CPUSEL6:1;                   // 6 Lock bit for CPUSEL6 register
    Uint16 CPUSEL7:1;                   // 7 Lock bit for CPUSEL7 register
    Uint16 CPUSEL8:1;                   // 8 Lock bit for CPUSEL8 register
    Uint16 CPUSEL9:1;                   // 9 Lock bit for CPUSEL9 register
    Uint16 rsvd2:1;                     // 10 Reserved
    Uint16 CPUSEL11:1;                  // 11 Lock bit for CPUSEL11 register
    Uint16 CPUSEL12:1;                  // 12 Lock bit for CPUSEL12 register
    Uint16 rsvd3:1;                     // 13 Reserved
    Uint16 CPUSEL14:1;                  // 14 Lock bit for CPUSEL14 register
    Uint16 CPUSEL15:1;                  // 15 Lock bit for CPUSEL15 register
    Uint16 CPUSEL16:1;                  // 16 Lock bit for CPUSEL16 register
    Uint16 rsvd4:1;                     // 17 Reserved
    Uint16 CPUSEL18:1;                  // 18 Lock bit for CPUSEL18 register
    Uint16 rsvd5:6;                     // 24:19 Reserved
    Uint16 CPUSEL25:1;                  // 25 Lock bit for CPUSEL25 register
    Uint16 rsvd6:6;                     // 31:26 Reserved
};

union DEVCFGLOCK1_REG {
    Uint32  all;
    struct  DEVCFGLOCK1_BITS  bit;
};

struct PARTIDL_BITS {                   // bits description
    Uint16 rsvd1:3;                     // 2:0 Reserved
    Uint16 rsvd2:2;                     // 4:3 Reserved
    Uint16 rsvd3:1;                     // 5 Reserved
    Uint16 QUAL:2;                      // 7:6 Qualification Status
    Uint16 PIN_COUNT:3;                 // 10:8 Device Pin Count
    Uint16 rsvd4:1;                     // 11 Reserved
    Uint16 rsvd5:1;                     // 12 Reserved
    Uint16 INSTASPIN:2;                 // 14:13 Motorware feature set
    Uint16 rsvd6:1;                     // 15 Reserved
    Uint16 FLASH_SIZE:8;                // 23:16 Flash size in KB per CPU
    Uint16 rsvd7:4;                     // 27:24 Reserved
    Uint16 PARTID_FORMAT_REVISION:4;    // 31:28 Revision of the PARTID format
};

union PARTIDL_REG {
    Uint32  all;
    struct  PARTIDL_BITS  bit;
};

struct PARTIDH_BITS {                   // bits description
    Uint16 rsvd1:4;                     // 3:0 Reserved
    Uint16 rsvd2:4;                     // 7:4 Reserved
    Uint16 FAMILY:8;                    // 15:8 Device family
    Uint16 PARTNO:8;                    // 23:16 Device part number
    Uint16 DEVICE_CLASS_ID:8;           // 31:24 Device class ID
};

union PARTIDH_REG {
    Uint32  all;
    struct  PARTIDH_BITS  bit;
};

struct REVID_BITS {                     // bits description
    Uint16 REVID:16;                    // 15:0 Device Revision ID. This is specific to the Device
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union REVID_REG {
    Uint32  all;
    struct  REVID_BITS  bit;
};

struct PERCNF1_BITS {                   // bits description
    Uint16 ADC_A_MODE:1;                // 0 ADC Wrapper-1 mode setting bit
    Uint16 ADC_B_MODE:1;                // 1 ADC Wrapper-2 mode setting bit
    Uint16 ADC_C_MODE:1;                // 2 ADC Wrapper-3 mode setting bit
    Uint16 ADC_D_MODE:1;                // 3 ADC Wrapper-4 mode setting bit
    Uint16 rsvd1:12;                    // 15:4 Reserved
    Uint16 USB_A_PHY:1;                 // 16 USB_A_PHY enable/disable bit
    Uint16 rsvd2:1;                     // 17 Reserved
    Uint16 rsvd3:14;                    // 31:18 Reserved
};

union PERCNF1_REG {
    Uint32  all;
    struct  PERCNF1_BITS  bit;
};

struct FUSEERR_BITS {                   // bits description
    Uint16 ALERR:5;                     // 4:0 Efuse Autoload Error Status
    Uint16 ERR:1;                       // 5 Efuse Self Test Error Status
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union FUSEERR_REG {
    Uint32  all;
    struct  FUSEERR_BITS  bit;
};

struct SOFTPRES0_BITS {                 // bits description
    Uint16 CPU1_CLA1:1;                 // 0 CPU1_CLA1 software reset bit
    Uint16 rsvd1:1;                     // 1 Reserved
    Uint16 CPU2_CLA1:1;                 // 2 CPU2_CLA1 software reset bit
    Uint16 rsvd2:1;                     // 3 Reserved
    Uint16 rsvd3:9;                     // 12:4 Reserved
    Uint16 CPU1_CPUBGCRC:1;             // 13 CPUBGCRC Module reset bit
    Uint16 CPU1_CLA1BGCRC:1;            // 14 CLA1BGCRC Module reset bit
    Uint16 rsvd4:1;                     // 15 Reserved
    Uint16 CPU2_CPUBGCRC:1;             // 16 CPUBGCRC Module reset bit
    Uint16 CPU2_CLA1BGCRC:1;            // 17 CLA1BGCRC Module reset bit
    Uint16 rsvd5:1;                     // 18 Reserved
    Uint16 rsvd6:5;                     // 23:19 Reserved
    Uint16 CPU1_ERAD:1;                 // 24 ERAD Module reset bit
    Uint16 CPU2_ERAD:1;                 // 25 ERAD Module reset bit
    Uint16 rsvd7:6;                     // 31:26 Reserved
};

union SOFTPRES0_REG {
    Uint32  all;
    struct  SOFTPRES0_BITS  bit;
};

struct SOFTPRES1_BITS {                 // bits description
    Uint16 EMIF1:1;                     // 0 EMIF1 software reset bit
    Uint16 EMIF2:1;                     // 1 EMIF2 software reset bit
    Uint16 rsvd1:14;                    // 15:2 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union SOFTPRES1_REG {
    Uint32  all;
    struct  SOFTPRES1_BITS  bit;
};

struct SOFTPRES2_BITS {                 // bits description
    Uint16 EPWM1:1;                     // 0 EPWM1 software reset bit
    Uint16 EPWM2:1;                     // 1 EPWM2 software reset bit
    Uint16 EPWM3:1;                     // 2 EPWM3 software reset bit
    Uint16 EPWM4:1;                     // 3 EPWM4 software reset bit
    Uint16 EPWM5:1;                     // 4 EPWM5 software reset bit
    Uint16 EPWM6:1;                     // 5 EPWM6 software reset bit
    Uint16 EPWM7:1;                     // 6 EPWM7 software reset bit
    Uint16 EPWM8:1;                     // 7 EPWM8 software reset bit
    Uint16 EPWM9:1;                     // 8 EPWM9 software reset bit
    Uint16 EPWM10:1;                    // 9 EPWM10 software reset bit
    Uint16 EPWM11:1;                    // 10 EPWM11 software reset bit
    Uint16 EPWM12:1;                    // 11 EPWM12 software reset bit
    Uint16 EPWM13:1;                    // 12 EPWM13 software reset bit
    Uint16 EPWM14:1;                    // 13 EPWM14 software reset bit
    Uint16 EPWM15:1;                    // 14 EPWM15 software reset bit
    Uint16 EPWM16:1;                    // 15 EPWM16 software reset bit
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union SOFTPRES2_REG {
    Uint32  all;
    struct  SOFTPRES2_BITS  bit;
};

struct SOFTPRES3_BITS {                 // bits description
    Uint16 ECAP1:1;                     // 0 ECAP1 software reset bit
    Uint16 ECAP2:1;                     // 1 ECAP2 software reset bit
    Uint16 ECAP3:1;                     // 2 ECAP3 software reset bit
    Uint16 ECAP4:1;                     // 3 ECAP4 software reset bit
    Uint16 ECAP5:1;                     // 4 ECAP5 software reset bit
    Uint16 ECAP6:1;                     // 5 ECAP6 software reset bit
    Uint16 ECAP7:1;                     // 6 ECAP7 software reset bit
    Uint16 rsvd1:1;                     // 7 Reserved
    Uint16 rsvd2:8;                     // 15:8 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union SOFTPRES3_REG {
    Uint32  all;
    struct  SOFTPRES3_BITS  bit;
};

struct SOFTPRES4_BITS {                 // bits description
    Uint16 EQEP1:1;                     // 0 EQEP1 software reset bit
    Uint16 EQEP2:1;                     // 1 EQEP2 software reset bit
    Uint16 EQEP3:1;                     // 2 EQEP3 software reset bit
    Uint16 rsvd1:1;                     // 3 Reserved
    Uint16 rsvd2:12;                    // 15:4 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union SOFTPRES4_REG {
    Uint32  all;
    struct  SOFTPRES4_BITS  bit;
};

struct SOFTPRES6_BITS {                 // bits description
    Uint16 SD1:1;                       // 0 SD1 software reset bit
    Uint16 SD2:1;                       // 1 SD2 software reset bit
    Uint16 rsvd1:1;                     // 2 Reserved
    Uint16 rsvd2:1;                     // 3 Reserved
    Uint16 rsvd3:1;                     // 4 Reserved
    Uint16 rsvd4:1;                     // 5 Reserved
    Uint16 rsvd5:1;                     // 6 Reserved
    Uint16 rsvd6:1;                     // 7 Reserved
    Uint16 rsvd7:8;                     // 15:8 Reserved
    Uint16 rsvd8:16;                    // 31:16 Reserved
};

union SOFTPRES6_REG {
    Uint32  all;
    struct  SOFTPRES6_BITS  bit;
};

struct SOFTPRES7_BITS {                 // bits description
    Uint16 SCI_A:1;                     // 0 SCI_A software reset bit
    Uint16 SCI_B:1;                     // 1 SCI_B software reset bit
    Uint16 SCI_C:1;                     // 2 SCI_C software reset bit
    Uint16 SCI_D:1;                     // 3 SCI_D software reset bit
    Uint16 rsvd1:12;                    // 15:4 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union SOFTPRES7_REG {
    Uint32  all;
    struct  SOFTPRES7_BITS  bit;
};

struct SOFTPRES8_BITS {                 // bits description
    Uint16 SPI_A:1;                     // 0 SPI_A software reset bit
    Uint16 SPI_B:1;                     // 1 SPI_B software reset bit
    Uint16 SPI_C:1;                     // 2 SPI_C software reset bit
    Uint16 SPI_D:1;                     // 3 SPI_D software reset bit
    Uint16 rsvd1:12;                    // 15:4 Reserved
    Uint16 rsvd2:1;                     // 16 Reserved
    Uint16 rsvd3:1;                     // 17 Reserved
    Uint16 rsvd4:14;                    // 31:18 Reserved
};

union SOFTPRES8_REG {
    Uint32  all;
    struct  SOFTPRES8_BITS  bit;
};

struct SOFTPRES9_BITS {                 // bits description
    Uint16 I2C_A:1;                     // 0 I2C_A software reset bit
    Uint16 I2C_B:1;                     // 1 I2C_B software reset bit
    Uint16 rsvd1:14;                    // 15:2 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union SOFTPRES9_REG {
    Uint32  all;
    struct  SOFTPRES9_BITS  bit;
};

struct SOFTPRES10_BITS {                // bits description
    Uint16 CAN_A:1;                     // 0 CAN_A software reset bit
    Uint16 CAN_B:1;                     // 1 CAN_B software reset bit
    Uint16 rsvd1:1;                     // 2 Reserved
    Uint16 rsvd2:1;                     // 3 Reserved
    Uint16 MCAN_A:1;                    // 4 MCAN_A software reset bit
    Uint16 rsvd3:11;                    // 15:5 Reserved
    Uint16 rsvd4:16;                    // 31:16 Reserved
};

union SOFTPRES10_REG {
    Uint32  all;
    struct  SOFTPRES10_BITS  bit;
};

struct SOFTPRES11_BITS {                // bits description
    Uint16 McBSP_A:1;                   // 0 McBSP_A software reset bit
    Uint16 McBSP_B:1;                   // 1 McBSP_B software reset bit
    Uint16 rsvd1:14;                    // 15:2 Reserved
    Uint16 USB_A:1;                     // 16 USB_A software reset bit
    Uint16 rsvd2:1;                     // 17 Reserved
    Uint16 rsvd3:14;                    // 31:18 Reserved
};

union SOFTPRES11_REG {
    Uint32  all;
    struct  SOFTPRES11_BITS  bit;
};

struct SOFTPRES13_BITS {                // bits description
    Uint16 ADC_A:1;                     // 0 ADC_A software reset bit
    Uint16 ADC_B:1;                     // 1 ADC_B software reset bit
    Uint16 ADC_C:1;                     // 2 ADC_C software reset bit
    Uint16 ADC_D:1;                     // 3 ADC_D software reset bit
    Uint16 rsvd1:12;                    // 15:4 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union SOFTPRES13_REG {
    Uint32  all;
    struct  SOFTPRES13_BITS  bit;
};

struct SOFTPRES14_BITS {                // bits description
    Uint16 CMPSS1:1;                    // 0 CMPSS1 software reset bit
    Uint16 CMPSS2:1;                    // 1 CMPSS2 software reset bit
    Uint16 CMPSS3:1;                    // 2 CMPSS3 software reset bit
    Uint16 CMPSS4:1;                    // 3 CMPSS4 software reset bit
    Uint16 CMPSS5:1;                    // 4 CMPSS5 software reset bit
    Uint16 CMPSS6:1;                    // 5 CMPSS6 software reset bit
    Uint16 CMPSS7:1;                    // 6 CMPSS7 software reset bit
    Uint16 CMPSS8:1;                    // 7 CMPSS8 software reset bit
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union SOFTPRES14_REG {
    Uint32  all;
    struct  SOFTPRES14_BITS  bit;
};

struct SOFTPRES16_BITS {                // bits description
    Uint16 rsvd1:16;                    // 15:0 Reserved
    Uint16 DAC_A:1;                     // 16 Buffered_DAC12_1 software reset bit
    Uint16 DAC_B:1;                     // 17 Buffered_DAC12_2 software reset bit
    Uint16 DAC_C:1;                     // 18 Buffered_DAC12_3 software reset bit
    Uint16 rsvd2:1;                     // 19 Reserved
    Uint16 rsvd3:12;                    // 31:20 Reserved
};

union SOFTPRES16_REG {
    Uint32  all;
    struct  SOFTPRES16_BITS  bit;
};

struct SOFTPRES17_BITS {                // bits description
    Uint16 CLB1:1;                      // 0 CLB1 software reset bit
    Uint16 CLB2:1;                      // 1 CLB2 software reset bit
    Uint16 CLB3:1;                      // 2 CLB3 software reset bit
    Uint16 CLB4:1;                      // 3 CLB4 software reset bit
    Uint16 CLB5:1;                      // 4 CLB5 software reset bit
    Uint16 CLB6:1;                      // 5 CLB6 software reset bit
    Uint16 CLB7:1;                      // 6 CLB7 software reset bit
    Uint16 CLB8:1;                      // 7 CLB8 software reset bit
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union SOFTPRES17_REG {
    Uint32  all;
    struct  SOFTPRES17_BITS  bit;
};

struct SOFTPRES18_BITS {                // bits description
    Uint16 FSITX_A:1;                   // 0 FSITX_A software reset bit
    Uint16 FSITX_B:1;                   // 1 FSITX_B software reset bit
    Uint16 rsvd1:1;                     // 2 Reserved
    Uint16 rsvd2:1;                     // 3 Reserved
    Uint16 rsvd3:1;                     // 4 Reserved
    Uint16 rsvd4:1;                     // 5 Reserved
    Uint16 rsvd5:1;                     // 6 Reserved
    Uint16 rsvd6:1;                     // 7 Reserved
    Uint16 rsvd7:8;                     // 15:8 Reserved
    Uint16 FSIRX_A:1;                   // 16 FSIRX_A software reset bit
    Uint16 FSIRX_B:1;                   // 17 FSIRX_B software reset bit
    Uint16 FSIRX_C:1;                   // 18 FSIRX_C software reset bit
    Uint16 FSIRX_D:1;                   // 19 FSIRX_D software reset bit
    Uint16 FSIRX_E:1;                   // 20 FSIRX_E software reset bit
    Uint16 FSIRX_F:1;                   // 21 FSIRX_F software reset bit
    Uint16 FSIRX_G:1;                   // 22 FSIRX_G software reset bit
    Uint16 FSIRX_H:1;                   // 23 FSIRX_H software reset bit
    Uint16 rsvd8:8;                     // 31:24 Reserved
};

union SOFTPRES18_REG {
    Uint32  all;
    struct  SOFTPRES18_BITS  bit;
};

struct SOFTPRES20_BITS {                // bits description
    Uint16 PMBUS_A:1;                   // 0 PMBUS_A software reset bit
    Uint16 rsvd1:1;                     // 1 Reserved
    Uint16 rsvd2:14;                    // 15:2 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union SOFTPRES20_REG {
    Uint32  all;
    struct  SOFTPRES20_BITS  bit;
};

struct SOFTPRES21_BITS {                // bits description
    Uint16 DCC0:1;                      // 0 DCC0 Module reset bit
    Uint16 DCC1:1;                      // 1 DCC1 Module reset bit
    Uint16 DCC2:1;                      // 2 DCC2 Module reset bit
    Uint16 rsvd1:13;                    // 15:3 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union SOFTPRES21_REG {
    Uint32  all;
    struct  SOFTPRES21_BITS  bit;
};

struct SOFTPRES23_BITS {                // bits description
    Uint16 ETHERCAT:1;                  // 0 ETHERCAT Module reset bit
    Uint16 rsvd1:15;                    // 15:1 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union SOFTPRES23_REG {
    Uint32  all;
    struct  SOFTPRES23_BITS  bit;
};

struct CPUSEL0_BITS {                   // bits description
    Uint16 EPWM1:1;                     // 0 EPWM1 CPU select bit
    Uint16 EPWM2:1;                     // 1 EPWM2 CPU select bit
    Uint16 EPWM3:1;                     // 2 EPWM3 CPU select bit
    Uint16 EPWM4:1;                     // 3 EPWM4 CPU select bit
    Uint16 EPWM5:1;                     // 4 EPWM5 CPU select bit
    Uint16 EPWM6:1;                     // 5 EPWM6 CPU select bit
    Uint16 EPWM7:1;                     // 6 EPWM7 CPU select bit
    Uint16 EPWM8:1;                     // 7 EPWM8 CPU select bit
    Uint16 EPWM9:1;                     // 8 EPWM9 CPU select bit
    Uint16 EPWM10:1;                    // 9 EPWM10 CPU select bit
    Uint16 EPWM11:1;                    // 10 EPWM11 CPU select bit
    Uint16 EPWM12:1;                    // 11 EPWM12 CPU select bit
    Uint16 EPWM13:1;                    // 12 EPWM13 CPU select bit
    Uint16 EPWM14:1;                    // 13 EPWM14 CPU select bit
    Uint16 EPWM15:1;                    // 14 EPWM15 CPU select bit
    Uint16 EPWM16:1;                    // 15 EPWM16 CPU select bit
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union CPUSEL0_REG {
    Uint32  all;
    struct  CPUSEL0_BITS  bit;
};

struct CPUSEL1_BITS {                   // bits description
    Uint16 ECAP1:1;                     // 0 ECAP1 CPU select bit
    Uint16 ECAP2:1;                     // 1 ECAP2 CPU select bit
    Uint16 ECAP3:1;                     // 2 ECAP3 CPU select bit
    Uint16 ECAP4:1;                     // 3 ECAP4 CPU select bit
    Uint16 ECAP5:1;                     // 4 ECAP5 CPU select bit
    Uint16 ECAP6:1;                     // 5 ECAP6 CPU select bit
    Uint16 ECAP7:1;                     // 6 ECAP7 CPU select bit
    Uint16 rsvd1:1;                     // 7 Reserved
    Uint16 rsvd2:8;                     // 15:8 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union CPUSEL1_REG {
    Uint32  all;
    struct  CPUSEL1_BITS  bit;
};

struct CPUSEL2_BITS {                   // bits description
    Uint16 EQEP1:1;                     // 0 EQEP1 CPU select bit
    Uint16 EQEP2:1;                     // 1 EQEP2 CPU select bit
    Uint16 EQEP3:1;                     // 2 EQEP3 CPU select bit
    Uint16 rsvd1:1;                     // 3 Reserved
    Uint16 rsvd2:12;                    // 15:4 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union CPUSEL2_REG {
    Uint32  all;
    struct  CPUSEL2_BITS  bit;
};

struct CPUSEL4_BITS {                   // bits description
    Uint16 SD1:1;                       // 0 SD1 CPU select bit
    Uint16 SD2:1;                       // 1 SD2 CPU select bit
    Uint16 rsvd1:1;                     // 2 Reserved
    Uint16 rsvd2:1;                     // 3 Reserved
    Uint16 rsvd3:1;                     // 4 Reserved
    Uint16 rsvd4:1;                     // 5 Reserved
    Uint16 rsvd5:1;                     // 6 Reserved
    Uint16 rsvd6:1;                     // 7 Reserved
    Uint16 rsvd7:8;                     // 15:8 Reserved
    Uint16 rsvd8:16;                    // 31:16 Reserved
};

union CPUSEL4_REG {
    Uint32  all;
    struct  CPUSEL4_BITS  bit;
};

struct CPUSEL5_BITS {                   // bits description
    Uint16 SCI_A:1;                     // 0 SCI_A CPU select bit
    Uint16 SCI_B:1;                     // 1 SCI_B CPU select bit
    Uint16 SCI_C:1;                     // 2 SCI_C CPU select bit
    Uint16 SCI_D:1;                     // 3 SCI_D CPU select bit
    Uint16 rsvd1:12;                    // 15:4 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union CPUSEL5_REG {
    Uint32  all;
    struct  CPUSEL5_BITS  bit;
};

struct CPUSEL6_BITS {                   // bits description
    Uint16 SPI_A:1;                     // 0 SPI_A CPU select bit
    Uint16 SPI_B:1;                     // 1 SPI_B CPU select bit
    Uint16 SPI_C:1;                     // 2 SPI_C CPU select bit
    Uint16 SPI_D:1;                     // 3 SPI_D CPU select bit
    Uint16 rsvd1:12;                    // 15:4 Reserved
    Uint16 rsvd2:1;                     // 16 Reserved
    Uint16 rsvd3:1;                     // 17 Reserved
    Uint16 rsvd4:14;                    // 31:18 Reserved
};

union CPUSEL6_REG {
    Uint32  all;
    struct  CPUSEL6_BITS  bit;
};

struct CPUSEL7_BITS {                   // bits description
    Uint16 I2C_A:1;                     // 0 I2C_A CPU select bit
    Uint16 I2C_B:1;                     // 1 I2C_B CPU select bit
    Uint16 rsvd1:14;                    // 15:2 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union CPUSEL7_REG {
    Uint32  all;
    struct  CPUSEL7_BITS  bit;
};

struct CPUSEL8_BITS {                   // bits description
    Uint16 CAN_A:1;                     // 0 CAN_A CPU select bit
    Uint16 CAN_B:1;                     // 1 CAN_B CPU select bit
    Uint16 rsvd1:1;                     // 2 Reserved
    Uint16 rsvd2:1;                     // 3 Reserved
    Uint16 MCAN_A:1;                    // 4 MCAN_A CPU select bit
    Uint16 rsvd3:11;                    // 15:5 Reserved
    Uint16 rsvd4:16;                    // 31:16 Reserved
};

union CPUSEL8_REG {
    Uint32  all;
    struct  CPUSEL8_BITS  bit;
};

struct CPUSEL9_BITS {                   // bits description
    Uint16 McBSP_A:1;                   // 0 McBSP_A CPU select bit
    Uint16 McBSP_B:1;                   // 1 McBSP_B CPU select bit
    Uint16 rsvd1:14;                    // 15:2 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union CPUSEL9_REG {
    Uint32  all;
    struct  CPUSEL9_BITS  bit;
};

struct CPUSEL11_BITS {                  // bits description
    Uint16 ADC_A:1;                     // 0 ADC_A CPU select bit
    Uint16 ADC_B:1;                     // 1 ADC_B CPU select bit
    Uint16 ADC_C:1;                     // 2 ADC_C CPU select bit
    Uint16 ADC_D:1;                     // 3 ADC_D CPU select bit
    Uint16 rsvd1:12;                    // 15:4 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union CPUSEL11_REG {
    Uint32  all;
    struct  CPUSEL11_BITS  bit;
};

struct CPUSEL12_BITS {                  // bits description
    Uint16 CMPSS1:1;                    // 0 CMPSS1 CPU select bit
    Uint16 CMPSS2:1;                    // 1 CMPSS2 CPU select bit
    Uint16 CMPSS3:1;                    // 2 CMPSS3 CPU select bit
    Uint16 CMPSS4:1;                    // 3 CMPSS4 CPU select bit
    Uint16 CMPSS5:1;                    // 4 CMPSS5 CPU select bit
    Uint16 CMPSS6:1;                    // 5 CMPSS6 CPU select bit
    Uint16 CMPSS7:1;                    // 6 CMPSS7 CPU select bit
    Uint16 CMPSS8:1;                    // 7 CMPSS8 CPU select bit
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union CPUSEL12_REG {
    Uint32  all;
    struct  CPUSEL12_BITS  bit;
};

struct CPUSEL14_BITS {                  // bits description
    Uint16 rsvd1:16;                    // 15:0 Reserved
    Uint16 DAC_A:1;                     // 16 Buffered_DAC12_1 CPU select bit
    Uint16 DAC_B:1;                     // 17 Buffered_DAC12_2 CPU select bit
    Uint16 DAC_C:1;                     // 18 Buffered_DAC12_3 CPU select bit
    Uint16 rsvd2:1;                     // 19 Reserved
    Uint16 rsvd3:12;                    // 31:20 Reserved
};

union CPUSEL14_REG {
    Uint32  all;
    struct  CPUSEL14_BITS  bit;
};

struct CPUSEL15_BITS {                  // bits description
    Uint16 CLB1:1;                      // 0 CLB1 CPU select bit
    Uint16 CLB2:1;                      // 1 CLB2 CPU select bit
    Uint16 CLB3:1;                      // 2 CLB3 CPU select bit
    Uint16 CLB4:1;                      // 3 CLB4 CPU select bit
    Uint16 CLB5:1;                      // 4 CLB5 CPU select bit
    Uint16 CLB6:1;                      // 5 CLB6 CPU select bit
    Uint16 CLB7:1;                      // 6 CLB7 CPU select bit
    Uint16 CLB8:1;                      // 7 CLB8 CPU select bit
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union CPUSEL15_REG {
    Uint32  all;
    struct  CPUSEL15_BITS  bit;
};

struct CPUSEL16_BITS {                  // bits description
    Uint16 FSITX_A:1;                   // 0 FSITX_A CPU select bit
    Uint16 FSITX_B:1;                   // 1 FSITX_B CPU select bit
    Uint16 rsvd1:1;                     // 2 Reserved
    Uint16 rsvd2:1;                     // 3 Reserved
    Uint16 rsvd3:1;                     // 4 Reserved
    Uint16 rsvd4:1;                     // 5 Reserved
    Uint16 rsvd5:1;                     // 6 Reserved
    Uint16 rsvd6:1;                     // 7 Reserved
    Uint16 rsvd7:8;                     // 15:8 Reserved
    Uint16 FSIRX_A:1;                   // 16 FSIRX_A CPU select bit
    Uint16 FSIRX_B:1;                   // 17 FSIRX_B CPU select bit
    Uint16 FSIRX_C:1;                   // 18 FSIRX_C CPU select bit
    Uint16 FSIRX_D:1;                   // 19 FSIRX_D CPU select bit
    Uint16 FSIRX_E:1;                   // 20 FSIRX_E CPU select bit
    Uint16 FSIRX_F:1;                   // 21 FSIRX_F CPU select bit
    Uint16 FSIRX_G:1;                   // 22 FSIRX_G CPU select bit
    Uint16 FSIRX_H:1;                   // 23 FSIRX_H CPU select bit
    Uint16 rsvd8:8;                     // 31:24 Reserved
};

union CPUSEL16_REG {
    Uint32  all;
    struct  CPUSEL16_BITS  bit;
};

struct CPUSEL18_BITS {                  // bits description
    Uint16 PMBUS_A:1;                   // 0 PMBUS_A CPU select bit
    Uint16 rsvd1:1;                     // 1 Reserved
    Uint16 rsvd2:14;                    // 15:2 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union CPUSEL18_REG {
    Uint32  all;
    struct  CPUSEL18_BITS  bit;
};

struct CPUSEL25_BITS {                  // bits description
    Uint16 HRCAL_A:1;                   // 0 HRCAL CPU select bit
    Uint16 rsvd1:15;                    // 15:1 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union CPUSEL25_REG {
    Uint32  all;
    struct  CPUSEL25_BITS  bit;
};

struct CPU2RESCTL_BITS {                // bits description
    Uint16 RESET:1;                     // 0 CPU2 Reset Control bit
    Uint16 rsvd1:15;                    // 15:1 Reserved
    Uint16 KEY:16;                      // 31:16 Key Qualifier for writes to this register
};

union CPU2RESCTL_REG {
    Uint32  all;
    struct  CPU2RESCTL_BITS  bit;
};

struct RSTSTAT_BITS {                   // bits description
    Uint16 CPU2RES:1;                   // 0 CPU2 Reset Status bit
    Uint16 CPU2NMIWDRST:1;              // 1 Tells whether a CPU2.NMIWD reset was issued to CPU2 or not
    Uint16 CPU2HWBISTRST:2;             // 3:2 Tells whether a HWBIST reset was issued to CPU2 or not
    Uint16 rsvd1:12;                    // 15:4 Reserved
};

union RSTSTAT_REG {
    Uint16  all;
    struct  RSTSTAT_BITS  bit;
};

struct LPMSTAT_BITS {                   // bits description
    Uint16 CPU2LPMSTAT:2;               // 1:0 CPU2 LPM Status
    Uint16 rsvd1:14;                    // 15:2 Reserved
};

union LPMSTAT_REG {
    Uint16  all;
    struct  LPMSTAT_BITS  bit;
};

struct USBTYPE_BITS {                   // bits description
    Uint16 TYPE:2;                      // 1:0 Configure USB type
    Uint16 rsvd1:13;                    // 14:2 Reserved
    Uint16 LOCK:1;                      // 15 Lock bit
};

union USBTYPE_REG {
    Uint16  all;
    struct  USBTYPE_BITS  bit;
};

struct ECAPTYPE_BITS {                  // bits description
    Uint16 TYPE:2;                      // 1:0 Configure ECAP type
    Uint16 rsvd1:13;                    // 14:2 Reserved
    Uint16 LOCK:1;                      // 15 Lock bit
};

union ECAPTYPE_REG {
    Uint16  all;
    struct  ECAPTYPE_BITS  bit;
};

struct SDFMTYPE_BITS {                  // bits description
    Uint16 TYPE:2;                      // 1:0 Configure SDFM type
    Uint16 rsvd1:13;                    // 14:2 Reserved
    Uint16 LOCK:1;                      // 15 Lock bit
};

union SDFMTYPE_REG {
    Uint16  all;
    struct  SDFMTYPE_BITS  bit;
};

struct MEMMAPTYPE_BITS {                // bits description
    Uint16 TYPE:2;                      // 1:0 Configures system specific features related to memory map.
    Uint16 rsvd1:13;                    // 14:2 Reserved
    Uint16 LOCK:1;                      // 15 Lock bit
};

union MEMMAPTYPE_REG {
    Uint16  all;
    struct  MEMMAPTYPE_BITS  bit;
};

struct DEV_CFG_REGS {
    union   DEVCFGLOCK1_REG                  DEVCFGLOCK1;                  // Lock bit for DEVCFG registers
    Uint16                                   rsvd1[6];                     // Reserved
    union   PARTIDL_REG                      PARTIDL;                      // Lower 32-bit of Device PART Identification Number
    union   PARTIDH_REG                      PARTIDH;                      // Upper 32-bit of Device PART Identification Number
    union   REVID_REG                        REVID;                        // Device Revision Number
    Uint16                                   rsvd2[82];                    // Reserved
    union   PERCNF1_REG                      PERCNF1;                      // Peripheral Configuration register
    Uint16                                   rsvd3[18];                    // Reserved
    union   FUSEERR_REG                      FUSEERR;                      // e-Fuse error Status register
    Uint16                                   rsvd4[12];                    // Reserved
    union   SOFTPRES0_REG                    SOFTPRES0;                    // Processing Block Software Reset register
    union   SOFTPRES1_REG                    SOFTPRES1;                    // EMIF Software Reset register
    union   SOFTPRES2_REG                    SOFTPRES2;                    // Peripheral Software Reset register
    union   SOFTPRES3_REG                    SOFTPRES3;                    // Peripheral Software Reset register
    union   SOFTPRES4_REG                    SOFTPRES4;                    // Peripheral Software Reset register
    Uint16                                   rsvd5[2];                     // Reserved
    union   SOFTPRES6_REG                    SOFTPRES6;                    // Peripheral Software Reset register
    union   SOFTPRES7_REG                    SOFTPRES7;                    // Peripheral Software Reset register
    union   SOFTPRES8_REG                    SOFTPRES8;                    // Peripheral Software Reset register
    union   SOFTPRES9_REG                    SOFTPRES9;                    // Peripheral Software Reset register
    union   SOFTPRES10_REG                   SOFTPRES10;                   // Peripheral Software Reset register
    union   SOFTPRES11_REG                   SOFTPRES11;                   // Peripheral Software Reset register
    Uint16                                   rsvd6[2];                     // Reserved
    union   SOFTPRES13_REG                   SOFTPRES13;                   // Peripheral Software Reset register
    union   SOFTPRES14_REG                   SOFTPRES14;                   // Peripheral Software Reset register
    Uint16                                   rsvd7[2];                     // Reserved
    union   SOFTPRES16_REG                   SOFTPRES16;                   // Peripheral Software Reset register
    union   SOFTPRES17_REG                   SOFTPRES17;                   // Reserved Peripheral Software Reset register
    union   SOFTPRES18_REG                   SOFTPRES18;                   // Reserved Peripheral Software Reset register
    Uint16                                   rsvd8[2];                     // Reserved
    union   SOFTPRES20_REG                   SOFTPRES20;                   // Peripheral Software Reset register
    union   SOFTPRES21_REG                   SOFTPRES21;                   // Peripheral Software Reset register
    Uint16                                   rsvd9[2];                     // Reserved
    union   SOFTPRES23_REG                   SOFTPRES23;                   // Peripheral Software Reset register
    Uint16                                   rsvd10[36];                   // Reserved
    union   CPUSEL0_REG                      CPUSEL0;                      // CPU Select register for common peripherals
    union   CPUSEL1_REG                      CPUSEL1;                      // CPU Select register for common peripherals
    union   CPUSEL2_REG                      CPUSEL2;                      // CPU Select register for common peripherals
    Uint16                                   rsvd11[2];                    // Reserved
    union   CPUSEL4_REG                      CPUSEL4;                      // CPU Select register for common peripherals
    union   CPUSEL5_REG                      CPUSEL5;                      // CPU Select register for common peripherals
    union   CPUSEL6_REG                      CPUSEL6;                      // CPU Select register for common peripherals
    union   CPUSEL7_REG                      CPUSEL7;                      // CPU Select register for common peripherals
    union   CPUSEL8_REG                      CPUSEL8;                      // CPU Select register for common peripherals
    union   CPUSEL9_REG                      CPUSEL9;                      // CPU Select register for common peripherals
    Uint16                                   rsvd12[2];                    // Reserved
    union   CPUSEL11_REG                     CPUSEL11;                     // CPU Select register for common peripherals
    union   CPUSEL12_REG                     CPUSEL12;                     // CPU Select register for common peripherals
    Uint16                                   rsvd13[2];                    // Reserved
    union   CPUSEL14_REG                     CPUSEL14;                     // CPU Select register for common peripherals
    union   CPUSEL15_REG                     CPUSEL15;                     // CPU Select register for common peripherals
    union   CPUSEL16_REG                     CPUSEL16;                     // CPU Select register for common peripherals
    Uint16                                   rsvd14[2];                    // Reserved
    union   CPUSEL18_REG                     CPUSEL18;                     // CPU Select register for common peripherals
    Uint16                                   rsvd15[12];                   // Reserved
    union   CPUSEL25_REG                     CPUSEL25;                     // CPU Select register for common peripherals
    Uint16                                   rsvd16[24];                   // Reserved
    union   CPU2RESCTL_REG                   CPU2RESCTL;                   // CPU2 Reset Control Register
    union   RSTSTAT_REG                      RSTSTAT;                      // Reset Status register for secondary C28x CPUs
    union   LPMSTAT_REG                      LPMSTAT;                      // LPM Status Register for secondary C28x CPUs
    Uint16                                   rsvd17[116];                  // Reserved
    union   USBTYPE_REG                      USBTYPE;                      // Configures USB Type for the device
    union   ECAPTYPE_REG                     ECAPTYPE;                     // Configures ECAP Type for the device
    union   SDFMTYPE_REG                     SDFMTYPE;                     // Configures SDFM Type for the device
    Uint16                                   rsvd18;                       // Reserved
    union   MEMMAPTYPE_REG                   MEMMAPTYPE;                   // Configures Memory Map Type for the device
};

struct ADCA_AC_BITS {                   // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPU1 Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union ADCA_AC_REG {
    Uint32  all;
    struct  ADCA_AC_BITS  bit;
};

struct ADCB_AC_BITS {                   // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union ADCB_AC_REG {
    Uint32  all;
    struct  ADCB_AC_BITS  bit;
};

struct ADCC_AC_BITS {                   // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union ADCC_AC_REG {
    Uint32  all;
    struct  ADCC_AC_BITS  bit;
};

struct ADCD_AC_BITS {                   // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union ADCD_AC_REG {
    Uint32  all;
    struct  ADCD_AC_BITS  bit;
};

struct CMPSS1_AC_BITS {                 // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union CMPSS1_AC_REG {
    Uint32  all;
    struct  CMPSS1_AC_BITS  bit;
};

struct CMPSS2_AC_BITS {                 // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union CMPSS2_AC_REG {
    Uint32  all;
    struct  CMPSS2_AC_BITS  bit;
};

struct CMPSS3_AC_BITS {                 // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union CMPSS3_AC_REG {
    Uint32  all;
    struct  CMPSS3_AC_BITS  bit;
};

struct CMPSS4_AC_BITS {                 // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union CMPSS4_AC_REG {
    Uint32  all;
    struct  CMPSS4_AC_BITS  bit;
};

struct CMPSS5_AC_BITS {                 // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union CMPSS5_AC_REG {
    Uint32  all;
    struct  CMPSS5_AC_BITS  bit;
};

struct CMPSS6_AC_BITS {                 // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union CMPSS6_AC_REG {
    Uint32  all;
    struct  CMPSS6_AC_BITS  bit;
};

struct CMPSS7_AC_BITS {                 // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union CMPSS7_AC_REG {
    Uint32  all;
    struct  CMPSS7_AC_BITS  bit;
};

struct CMPSS8_AC_BITS {                 // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union CMPSS8_AC_REG {
    Uint32  all;
    struct  CMPSS8_AC_BITS  bit;
};

struct DACA_AC_BITS {                   // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union DACA_AC_REG {
    Uint32  all;
    struct  DACA_AC_BITS  bit;
};

struct DACB_AC_BITS {                   // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union DACB_AC_REG {
    Uint32  all;
    struct  DACB_AC_BITS  bit;
};

struct DACC_AC_BITS {                   // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union DACC_AC_REG {
    Uint32  all;
    struct  DACC_AC_BITS  bit;
};

struct EPWM1_AC_BITS {                  // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union EPWM1_AC_REG {
    Uint32  all;
    struct  EPWM1_AC_BITS  bit;
};

struct EPWM2_AC_BITS {                  // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union EPWM2_AC_REG {
    Uint32  all;
    struct  EPWM2_AC_BITS  bit;
};

struct EPWM3_AC_BITS {                  // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union EPWM3_AC_REG {
    Uint32  all;
    struct  EPWM3_AC_BITS  bit;
};

struct EPWM4_AC_BITS {                  // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union EPWM4_AC_REG {
    Uint32  all;
    struct  EPWM4_AC_BITS  bit;
};

struct EPWM5_AC_BITS {                  // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union EPWM5_AC_REG {
    Uint32  all;
    struct  EPWM5_AC_BITS  bit;
};

struct EPWM6_AC_BITS {                  // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union EPWM6_AC_REG {
    Uint32  all;
    struct  EPWM6_AC_BITS  bit;
};

struct EPWM7_AC_BITS {                  // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union EPWM7_AC_REG {
    Uint32  all;
    struct  EPWM7_AC_BITS  bit;
};

struct EPWM8_AC_BITS {                  // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union EPWM8_AC_REG {
    Uint32  all;
    struct  EPWM8_AC_BITS  bit;
};

struct EPWM9_AC_BITS {                  // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union EPWM9_AC_REG {
    Uint32  all;
    struct  EPWM9_AC_BITS  bit;
};

struct EPWM10_AC_BITS {                 // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union EPWM10_AC_REG {
    Uint32  all;
    struct  EPWM10_AC_BITS  bit;
};

struct EPWM11_AC_BITS {                 // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union EPWM11_AC_REG {
    Uint32  all;
    struct  EPWM11_AC_BITS  bit;
};

struct EPWM12_AC_BITS {                 // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union EPWM12_AC_REG {
    Uint32  all;
    struct  EPWM12_AC_BITS  bit;
};

struct EPWM13_AC_BITS {                 // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union EPWM13_AC_REG {
    Uint32  all;
    struct  EPWM13_AC_BITS  bit;
};

struct EPWM14_AC_BITS {                 // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union EPWM14_AC_REG {
    Uint32  all;
    struct  EPWM14_AC_BITS  bit;
};

struct EPWM15_AC_BITS {                 // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union EPWM15_AC_REG {
    Uint32  all;
    struct  EPWM15_AC_BITS  bit;
};

struct EPWM16_AC_BITS {                 // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union EPWM16_AC_REG {
    Uint32  all;
    struct  EPWM16_AC_BITS  bit;
};

struct EQEP1_AC_BITS {                  // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union EQEP1_AC_REG {
    Uint32  all;
    struct  EQEP1_AC_BITS  bit;
};

struct EQEP2_AC_BITS {                  // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union EQEP2_AC_REG {
    Uint32  all;
    struct  EQEP2_AC_BITS  bit;
};

struct EQEP3_AC_BITS {                  // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union EQEP3_AC_REG {
    Uint32  all;
    struct  EQEP3_AC_BITS  bit;
};

struct ECAP1_AC_BITS {                  // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union ECAP1_AC_REG {
    Uint32  all;
    struct  ECAP1_AC_BITS  bit;
};

struct ECAP2_AC_BITS {                  // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union ECAP2_AC_REG {
    Uint32  all;
    struct  ECAP2_AC_BITS  bit;
};

struct ECAP3_AC_BITS {                  // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union ECAP3_AC_REG {
    Uint32  all;
    struct  ECAP3_AC_BITS  bit;
};

struct ECAP4_AC_BITS {                  // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union ECAP4_AC_REG {
    Uint32  all;
    struct  ECAP4_AC_BITS  bit;
};

struct ECAP5_AC_BITS {                  // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union ECAP5_AC_REG {
    Uint32  all;
    struct  ECAP5_AC_BITS  bit;
};

struct ECAP6_AC_BITS {                  // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union ECAP6_AC_REG {
    Uint32  all;
    struct  ECAP6_AC_BITS  bit;
};

struct ECAP7_AC_BITS {                  // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union ECAP7_AC_REG {
    Uint32  all;
    struct  ECAP7_AC_BITS  bit;
};

struct SDFM1_AC_BITS {                  // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union SDFM1_AC_REG {
    Uint32  all;
    struct  SDFM1_AC_BITS  bit;
};

struct SDFM2_AC_BITS {                  // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union SDFM2_AC_REG {
    Uint32  all;
    struct  SDFM2_AC_BITS  bit;
};

struct CLB1_AC_BITS {                   // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 rsvd1:2;                     // 5:4 Reserved
    Uint16 rsvd2:10;                    // 15:6 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union CLB1_AC_REG {
    Uint32  all;
    struct  CLB1_AC_BITS  bit;
};

struct CLB2_AC_BITS {                   // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 rsvd1:2;                     // 5:4 Reserved
    Uint16 rsvd2:10;                    // 15:6 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union CLB2_AC_REG {
    Uint32  all;
    struct  CLB2_AC_BITS  bit;
};

struct CLB3_AC_BITS {                   // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 rsvd1:2;                     // 5:4 Reserved
    Uint16 rsvd2:10;                    // 15:6 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union CLB3_AC_REG {
    Uint32  all;
    struct  CLB3_AC_BITS  bit;
};

struct CLB4_AC_BITS {                   // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 rsvd1:2;                     // 5:4 Reserved
    Uint16 rsvd2:10;                    // 15:6 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union CLB4_AC_REG {
    Uint32  all;
    struct  CLB4_AC_BITS  bit;
};

struct CLB5_AC_BITS {                   // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 rsvd1:2;                     // 5:4 Reserved
    Uint16 rsvd2:10;                    // 15:6 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union CLB5_AC_REG {
    Uint32  all;
    struct  CLB5_AC_BITS  bit;
};

struct CLB6_AC_BITS {                   // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 rsvd1:2;                     // 5:4 Reserved
    Uint16 rsvd2:10;                    // 15:6 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union CLB6_AC_REG {
    Uint32  all;
    struct  CLB6_AC_BITS  bit;
};

struct CLB7_AC_BITS {                   // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 rsvd1:2;                     // 5:4 Reserved
    Uint16 rsvd2:10;                    // 15:6 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union CLB7_AC_REG {
    Uint32  all;
    struct  CLB7_AC_BITS  bit;
};

struct CLB8_AC_BITS {                   // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 rsvd1:2;                     // 5:4 Reserved
    Uint16 rsvd2:10;                    // 15:6 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union CLB8_AC_REG {
    Uint32  all;
    struct  CLB8_AC_BITS  bit;
};

struct SPIA_AC_BITS {                   // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union SPIA_AC_REG {
    Uint32  all;
    struct  SPIA_AC_BITS  bit;
};

struct SPIB_AC_BITS {                   // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union SPIB_AC_REG {
    Uint32  all;
    struct  SPIB_AC_BITS  bit;
};

struct SPIC_AC_BITS {                   // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union SPIC_AC_REG {
    Uint32  all;
    struct  SPIC_AC_BITS  bit;
};

struct SPID_AC_BITS {                   // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union SPID_AC_REG {
    Uint32  all;
    struct  SPID_AC_BITS  bit;
};

struct PMBUS_A_AC_BITS {                // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union PMBUS_A_AC_REG {
    Uint32  all;
    struct  PMBUS_A_AC_BITS  bit;
};

struct CAN_A_AC_BITS {                  // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 rsvd1:2;                     // 3:2 Reserved
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd2:10;                    // 15:6 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union CAN_A_AC_REG {
    Uint32  all;
    struct  CAN_A_AC_BITS  bit;
};

struct CAN_B_AC_BITS {                  // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 rsvd1:2;                     // 3:2 Reserved
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd2:10;                    // 15:6 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union CAN_B_AC_REG {
    Uint32  all;
    struct  CAN_B_AC_BITS  bit;
};

struct MCBSPA_AC_BITS {                 // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union MCBSPA_AC_REG {
    Uint32  all;
    struct  MCBSPA_AC_BITS  bit;
};

struct MCBSPB_AC_BITS {                 // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union MCBSPB_AC_REG {
    Uint32  all;
    struct  MCBSPB_AC_BITS  bit;
};

struct USBA_AC_BITS {                   // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 rsvd1:2;                     // 3:2 Reserved
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd2:10;                    // 15:6 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union USBA_AC_REG {
    Uint32  all;
    struct  USBA_AC_BITS  bit;
};

struct HRPWM_AC_BITS {                  // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union HRPWM_AC_REG {
    Uint32  all;
    struct  HRPWM_AC_BITS  bit;
};

struct ETHERCAT_AC_BITS {               // bits description
    Uint16 CPU1_ACC:2;                  // 1:0 CPU1 Access conditions to peripheral
    Uint16 rsvd1:2;                     // 3:2 Reserved
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd2:10;                    // 15:6 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union ETHERCAT_AC_REG {
    Uint32  all;
    struct  ETHERCAT_AC_BITS  bit;
};

struct FSIATX_AC_BITS {                 // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union FSIATX_AC_REG {
    Uint32  all;
    struct  FSIATX_AC_BITS  bit;
};

struct FSIARX_AC_BITS {                 // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union FSIARX_AC_REG {
    Uint32  all;
    struct  FSIARX_AC_BITS  bit;
};

struct FSIBTX_AC_BITS {                 // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union FSIBTX_AC_REG {
    Uint32  all;
    struct  FSIBTX_AC_BITS  bit;
};

struct FSIBRX_AC_BITS {                 // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union FSIBRX_AC_REG {
    Uint32  all;
    struct  FSIBRX_AC_BITS  bit;
};

struct FSICRX_AC_BITS {                 // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union FSICRX_AC_REG {
    Uint32  all;
    struct  FSICRX_AC_BITS  bit;
};

struct FSIDRX_AC_BITS {                 // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union FSIDRX_AC_REG {
    Uint32  all;
    struct  FSIDRX_AC_BITS  bit;
};

struct FSIERX_AC_BITS {                 // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union FSIERX_AC_REG {
    Uint32  all;
    struct  FSIERX_AC_BITS  bit;
};

struct FSIFRX_AC_BITS {                 // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union FSIFRX_AC_REG {
    Uint32  all;
    struct  FSIFRX_AC_BITS  bit;
};

struct FSIGRX_AC_BITS {                 // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union FSIGRX_AC_REG {
    Uint32  all;
    struct  FSIGRX_AC_BITS  bit;
};

struct FSIHRX_AC_BITS {                 // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 CLA1_ACC:2;                  // 3:2 CLA1 Access Conditions to Peripheral
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union FSIHRX_AC_REG {
    Uint32  all;
    struct  FSIHRX_AC_BITS  bit;
};

struct MCANA_AC_BITS {                  // bits description
    Uint16 CPUx_ACC:2;                  // 1:0 CPUx Access conditions to peripheral
    Uint16 rsvd1:2;                     // 3:2 Reserved
    Uint16 DMA1_ACC:2;                  // 5:4 DMA1 Access Conditions to Peripheral
    Uint16 rsvd2:10;                    // 15:6 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union MCANA_AC_REG {
    Uint32  all;
    struct  MCANA_AC_BITS  bit;
};

struct PERIPH_AC_LOCK_BITS {            // bits description
    Uint16 LOCK_AC_WR:1;                // 0  Lock control for Access control registers write.
    Uint16 rsvd1:15;                    // 15:1 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union PERIPH_AC_LOCK_REG {
    Uint32  all;
    struct  PERIPH_AC_LOCK_BITS  bit;
};

struct CPU1_PERIPH_AC_REGS {
    union   ADCA_AC_REG                      ADCA_AC;                      // ADCA Master Access Control Register
    union   ADCB_AC_REG                      ADCB_AC;                      // ADCB Master Access Control Register
    union   ADCC_AC_REG                      ADCC_AC;                      // ADCC Master Access Control Register
    union   ADCD_AC_REG                      ADCD_AC;                      // ADCD Master Access Control Register
    Uint16                                   rsvd1[8];                     // Reserved
    union   CMPSS1_AC_REG                    CMPSS1_AC;                    // CMPSS1 Master Access Control Register
    union   CMPSS2_AC_REG                    CMPSS2_AC;                    // CMPSS2 Master Access Control Register
    union   CMPSS3_AC_REG                    CMPSS3_AC;                    // CMPSS3 Master Access Control Register
    union   CMPSS4_AC_REG                    CMPSS4_AC;                    // CMPSS4 Master Access Control Register
    union   CMPSS5_AC_REG                    CMPSS5_AC;                    // CMPSS5 Master Access Control Register
    union   CMPSS6_AC_REG                    CMPSS6_AC;                    // CMPSS6 Master Access Control Register
    union   CMPSS7_AC_REG                    CMPSS7_AC;                    // CMPSS7 Master Access Control Register
    union   CMPSS8_AC_REG                    CMPSS8_AC;                    // CMPSS8 Master Access Control Register
    Uint16                                   rsvd2[8];                     // Reserved
    union   DACA_AC_REG                      DACA_AC;                      // DACA Master Access Control Register
    union   DACB_AC_REG                      DACB_AC;                      // DACB Master Access Control Register
    union   DACC_AC_REG                      DACC_AC;                      // DACC Master Access Control Register
    Uint16                                   rsvd3[26];                    // Reserved
    union   EPWM1_AC_REG                     EPWM1_AC;                     // EPWM1 Master Access Control Register
    union   EPWM2_AC_REG                     EPWM2_AC;                     // EPWM2 Master Access Control Register
    union   EPWM3_AC_REG                     EPWM3_AC;                     // EPWM3 Master Access Control Register
    union   EPWM4_AC_REG                     EPWM4_AC;                     // EPWM4 Master Access Control Register
    union   EPWM5_AC_REG                     EPWM5_AC;                     // EPWM5 Master Access Control Register
    union   EPWM6_AC_REG                     EPWM6_AC;                     // EPWM6 Master Access Control Register
    union   EPWM7_AC_REG                     EPWM7_AC;                     // EPWM7 Master Access Control Register
    union   EPWM8_AC_REG                     EPWM8_AC;                     // EPWM8 Master Access Control Register
    union   EPWM9_AC_REG                     EPWM9_AC;                     // EPWM9 Master Access Control Register
    union   EPWM10_AC_REG                    EPWM10_AC;                    // EPWM10 Master Access Control Register
    union   EPWM11_AC_REG                    EPWM11_AC;                    // EPWM11 Master Access Control Register
    union   EPWM12_AC_REG                    EPWM12_AC;                    // EPWM12 Master Access Control Register
    union   EPWM13_AC_REG                    EPWM13_AC;                    // EPWM13 Master Access Control Register
    union   EPWM14_AC_REG                    EPWM14_AC;                    // EPWM14 Master Access Control Register
    union   EPWM15_AC_REG                    EPWM15_AC;                    // EPWM15 Master Access Control Register
    union   EPWM16_AC_REG                    EPWM16_AC;                    // EPWM16 Master Access Control Register
    Uint16                                   rsvd4[8];                     // Reserved
    union   EQEP1_AC_REG                     EQEP1_AC;                     // EQEP1 Master Access Control Register
    union   EQEP2_AC_REG                     EQEP2_AC;                     // EQEP2 Master Access Control Register
    union   EQEP3_AC_REG                     EQEP3_AC;                     // EQEP3 Master Access Control Register
    Uint16                                   rsvd5[10];                    // Reserved
    union   ECAP1_AC_REG                     ECAP1_AC;                     // ECAP1 Master Access Control Register
    union   ECAP2_AC_REG                     ECAP2_AC;                     // ECAP2 Master Access Control Register
    union   ECAP3_AC_REG                     ECAP3_AC;                     // ECAP3 Master Access Control Register
    union   ECAP4_AC_REG                     ECAP4_AC;                     // ECAP4 Master Access Control Register
    union   ECAP5_AC_REG                     ECAP5_AC;                     // ECAP5 Master Access Control Register
    union   ECAP6_AC_REG                     ECAP6_AC;                     // ECAP6 Master Access Control Register
    union   ECAP7_AC_REG                     ECAP7_AC;                     // ECAP7 Master Access Control Register
    Uint16                                   rsvd6[26];                    // Reserved
    union   SDFM1_AC_REG                     SDFM1_AC;                     // SDFM1 Master Access Control Register
    union   SDFM2_AC_REG                     SDFM2_AC;                     // SDFM2 Master Access Control Register
    Uint16                                   rsvd7[4];                     // Reserved
    union   CLB1_AC_REG                      CLB1_AC;                      // CLB1 Master Access Control Register
    union   CLB2_AC_REG                      CLB2_AC;                      // CLB2 Master Access Control Register
    union   CLB3_AC_REG                      CLB3_AC;                      // CLB3 Master Access Control Register
    union   CLB4_AC_REG                      CLB4_AC;                      // CLB4 Master Access Control Register
    union   CLB5_AC_REG                      CLB5_AC;                      // CLB5 Master Access Control Register
    union   CLB6_AC_REG                      CLB6_AC;                      // CLB6 Master Access Control Register
    union   CLB7_AC_REG                      CLB7_AC;                      // CLB7 Master Access Control Register
    union   CLB8_AC_REG                      CLB8_AC;                      // CLB8 Master Access Control Register
    Uint16                                   rsvd8[80];                    // Reserved
    union   SPIA_AC_REG                      SPIA_AC;                      // SPIA Master Access Control Register
    union   SPIB_AC_REG                      SPIB_AC;                      // SPIB Master Access Control Register
    union   SPIC_AC_REG                      SPIC_AC;                      // SPIC Master Access Control Register
    union   SPID_AC_REG                      SPID_AC;                      // SPID Master Access Control Register
    Uint16                                   rsvd9[24];                    // Reserved
    union   PMBUS_A_AC_REG                   PMBUS_A_AC;                   // PMBUSA Master Access Control Register
    Uint16                                   rsvd10[14];                   // Reserved
    union   CAN_A_AC_REG                     CAN_A_AC;                     // CAN_A Master Access Control Register
    union   CAN_B_AC_REG                     CAN_B_AC;                     // CAN_B Master Access Control Register
    Uint16                                   rsvd11[12];                   // Reserved
    union   MCBSPA_AC_REG                    MCBSPA_AC;                    // MCBSPA Master Access Control Register
    union   MCBSPB_AC_REG                    MCBSPB_AC;                    // MCBSPB Master Access Control Register
    Uint16                                   rsvd12[44];                   // Reserved
    union   USBA_AC_REG                      USBA_AC;                      // USBA Master Access Control Register
    Uint16                                   rsvd13[38];                   // Reserved
    union   HRPWM_AC_REG                     HRPWM_AC;                     // HRPWM Master Access Control Register
    union   ETHERCAT_AC_REG                  ETHERCAT_AC;                  // ETHERCAT Master Access Control Register
    Uint16                                   rsvd14[4];                    // Reserved
    union   FSIATX_AC_REG                    FSIATX_AC;                    // FSIATX Master Access Control Register
    union   FSIARX_AC_REG                    FSIARX_AC;                    // FSIARX Master Access Control Register
    union   FSIBTX_AC_REG                    FSIBTX_AC;                    // FSIBTX Master Access Control Register
    union   FSIBRX_AC_REG                    FSIBRX_AC;                    // FSIBRX Master Access Control Register
    Uint16                                   rsvd15[2];                    // Reserved
    union   FSICRX_AC_REG                    FSICRX_AC;                    // FSICRX Master Access Control Register
    Uint16                                   rsvd16[2];                    // Reserved
    union   FSIDRX_AC_REG                    FSIDRX_AC;                    // FSIDRX Master Access Control Register
    Uint16                                   rsvd17[2];                    // Reserved
    union   FSIERX_AC_REG                    FSIERX_AC;                    // FSIERX Master Access Control Register
    Uint16                                   rsvd18[2];                    // Reserved
    union   FSIFRX_AC_REG                    FSIFRX_AC;                    // FSIFRX Master Access Control Register
    Uint16                                   rsvd19[2];                    // Reserved
    union   FSIGRX_AC_REG                    FSIGRX_AC;                    // FSIGRX Master Access Control Register
    Uint16                                   rsvd20[2];                    // Reserved
    union   FSIHRX_AC_REG                    FSIHRX_AC;                    // FSIHRX Master Access Control Register
    union   MCANA_AC_REG                     MCANA_AC;                     // MCANA Master Access Control Register
    Uint16                                   rsvd21[44];                   // Reserved
    union   PERIPH_AC_LOCK_REG               PERIPH_AC_LOCK;               // Lock Register to stop Write access to peripheral Access register.
};

struct CPU2_PERIPH_AC_REGS {
    union   ADCA_AC_REG                      ADCA_AC;                      // ADCA Master Access Control Register
    union   ADCB_AC_REG                      ADCB_AC;                      // ADCB Master Access Control Register
    union   ADCC_AC_REG                      ADCC_AC;                      // ADCC Master Access Control Register
    union   ADCD_AC_REG                      ADCD_AC;                      // ADCD Master Access Control Register
    Uint16                                   rsvd1[8];                     // Reserved
    union   CMPSS1_AC_REG                    CMPSS1_AC;                    // CMPSS1 Master Access Control Register
    union   CMPSS2_AC_REG                    CMPSS2_AC;                    // CMPSS2 Master Access Control Register
    union   CMPSS3_AC_REG                    CMPSS3_AC;                    // CMPSS3 Master Access Control Register
    union   CMPSS4_AC_REG                    CMPSS4_AC;                    // CMPSS4 Master Access Control Register
    union   CMPSS5_AC_REG                    CMPSS5_AC;                    // CMPSS5 Master Access Control Register
    union   CMPSS6_AC_REG                    CMPSS6_AC;                    // CMPSS6 Master Access Control Register
    union   CMPSS7_AC_REG                    CMPSS7_AC;                    // CMPSS7 Master Access Control Register
    union   CMPSS8_AC_REG                    CMPSS8_AC;                    // CMPSS8 Master Access Control Register
    Uint16                                   rsvd2[8];                     // Reserved
    union   DACA_AC_REG                      DACA_AC;                      // DACA Master Access Control Register
    union   DACB_AC_REG                      DACB_AC;                      // DACB Master Access Control Register
    union   DACC_AC_REG                      DACC_AC;                      // DACC Master Access Control Register
    Uint16                                   rsvd3[26];                    // Reserved
    union   EPWM1_AC_REG                     EPWM1_AC;                     // EPWM1 Master Access Control Register
    union   EPWM2_AC_REG                     EPWM2_AC;                     // EPWM2 Master Access Control Register
    union   EPWM3_AC_REG                     EPWM3_AC;                     // EPWM3 Master Access Control Register
    union   EPWM4_AC_REG                     EPWM4_AC;                     // EPWM4 Master Access Control Register
    union   EPWM5_AC_REG                     EPWM5_AC;                     // EPWM5 Master Access Control Register
    union   EPWM6_AC_REG                     EPWM6_AC;                     // EPWM6 Master Access Control Register
    union   EPWM7_AC_REG                     EPWM7_AC;                     // EPWM7 Master Access Control Register
    union   EPWM8_AC_REG                     EPWM8_AC;                     // EPWM8 Master Access Control Register
    union   EPWM9_AC_REG                     EPWM9_AC;                     // EPWM9 Master Access Control Register
    union   EPWM10_AC_REG                    EPWM10_AC;                    // EPWM10 Master Access Control Register
    union   EPWM11_AC_REG                    EPWM11_AC;                    // EPWM11 Master Access Control Register
    union   EPWM12_AC_REG                    EPWM12_AC;                    // EPWM12 Master Access Control Register
    union   EPWM13_AC_REG                    EPWM13_AC;                    // EPWM13 Master Access Control Register
    union   EPWM14_AC_REG                    EPWM14_AC;                    // EPWM14 Master Access Control Register
    union   EPWM15_AC_REG                    EPWM15_AC;                    // EPWM15 Master Access Control Register
    union   EPWM16_AC_REG                    EPWM16_AC;                    // EPWM16 Master Access Control Register
    Uint16                                   rsvd4[8];                     // Reserved
    union   EQEP1_AC_REG                     EQEP1_AC;                     // EQEP1 Master Access Control Register
    union   EQEP2_AC_REG                     EQEP2_AC;                     // EQEP2 Master Access Control Register
    union   EQEP3_AC_REG                     EQEP3_AC;                     // EQEP3 Master Access Control Register
    Uint16                                   rsvd5[10];                    // Reserved
    union   ECAP1_AC_REG                     ECAP1_AC;                     // ECAP1 Master Access Control Register
    union   ECAP2_AC_REG                     ECAP2_AC;                     // ECAP2 Master Access Control Register
    union   ECAP3_AC_REG                     ECAP3_AC;                     // ECAP3 Master Access Control Register
    union   ECAP4_AC_REG                     ECAP4_AC;                     // ECAP4 Master Access Control Register
    union   ECAP5_AC_REG                     ECAP5_AC;                     // ECAP5 Master Access Control Register
    union   ECAP6_AC_REG                     ECAP6_AC;                     // ECAP6 Master Access Control Register
    union   ECAP7_AC_REG                     ECAP7_AC;                     // ECAP7 Master Access Control Register
    Uint16                                   rsvd6[26];                    // Reserved
    union   SDFM1_AC_REG                     SDFM1_AC;                     // SDFM1 Master Access Control Register
    union   SDFM2_AC_REG                     SDFM2_AC;                     // SDFM2 Master Access Control Register
    Uint16                                   rsvd7[4];                     // Reserved
    union   CLB1_AC_REG                      CLB1_AC;                      // CLB1 Master Access Control Register
    union   CLB2_AC_REG                      CLB2_AC;                      // CLB2 Master Access Control Register
    union   CLB3_AC_REG                      CLB3_AC;                      // CLB3 Master Access Control Register
    union   CLB4_AC_REG                      CLB4_AC;                      // CLB4 Master Access Control Register
    union   CLB5_AC_REG                      CLB5_AC;                      // CLB5 Master Access Control Register
    union   CLB6_AC_REG                      CLB6_AC;                      // CLB6 Master Access Control Register
    union   CLB7_AC_REG                      CLB7_AC;                      // CLB7 Master Access Control Register
    union   CLB8_AC_REG                      CLB8_AC;                      // CLB8 Master Access Control Register
    Uint16                                   rsvd8[80];                    // Reserved
    union   SPIA_AC_REG                      SPIA_AC;                      // SPIA Master Access Control Register
    union   SPIB_AC_REG                      SPIB_AC;                      // SPIB Master Access Control Register
    union   SPIC_AC_REG                      SPIC_AC;                      // SPIC Master Access Control Register
    union   SPID_AC_REG                      SPID_AC;                      // SPID Master Access Control Register
    Uint16                                   rsvd9[24];                    // Reserved
    union   PMBUS_A_AC_REG                   PMBUS_A_AC;                   // PMBUSA Master Access Control Register
    Uint16                                   rsvd10[14];                   // Reserved
    union   CAN_A_AC_REG                     CAN_A_AC;                     // CAN_A Master Access Control Register
    union   CAN_B_AC_REG                     CAN_B_AC;                     // CAN_B Master Access Control Register
    Uint16                                   rsvd11[12];                   // Reserved
    union   MCBSPA_AC_REG                    MCBSPA_AC;                    // MCBSPA Master Access Control Register
    union   MCBSPB_AC_REG                    MCBSPB_AC;                    // MCBSPB Master Access Control Register
    Uint16                                   rsvd12[44];                   // Reserved
    union   USBA_AC_REG                      USBA_AC;                      // USBA Master Access Control Register
    Uint16                                   rsvd13[38];                   // Reserved
    union   HRPWM_AC_REG                     HRPWM_AC;                     // HRPWM Master Access Control Register
    Uint16                                   rsvd14[6];                    // Reserved
    union   FSIATX_AC_REG                    FSIATX_AC;                    // FSIATX Master Access Control Register
    union   FSIARX_AC_REG                    FSIARX_AC;                    // FSIARX Master Access Control Register
    union   FSIBTX_AC_REG                    FSIBTX_AC;                    // FSIBTX Master Access Control Register
    union   FSIBRX_AC_REG                    FSIBRX_AC;                    // FSIBRX Master Access Control Register
    Uint16                                   rsvd15[2];                    // Reserved
    union   FSICRX_AC_REG                    FSICRX_AC;                    // FSICRX Master Access Control Register
    Uint16                                   rsvd16[2];                    // Reserved
    union   FSIDRX_AC_REG                    FSIDRX_AC;                    // FSIDRX Master Access Control Register
    Uint16                                   rsvd17[2];                    // Reserved
    union   FSIERX_AC_REG                    FSIERX_AC;                    // FSIERX Master Access Control Register
    Uint16                                   rsvd18[2];                    // Reserved
    union   FSIFRX_AC_REG                    FSIFRX_AC;                    // FSIFRX Master Access Control Register
    Uint16                                   rsvd19[2];                    // Reserved
    union   FSIGRX_AC_REG                    FSIGRX_AC;                    // FSIGRX Master Access Control Register
    Uint16                                   rsvd20[2];                    // Reserved
    union   FSIHRX_AC_REG                    FSIHRX_AC;                    // FSIHRX Master Access Control Register
    union   MCANA_AC_REG                     MCANA_AC;                     // MCANA Master Access Control Register
    Uint16                                   rsvd21[44];                   // Reserved
    union   PERIPH_AC_LOCK_REG               PERIPH_AC_LOCK;               // Lock Register to stop Write access to peripheral Access register.
};

struct CMRESCTL_BITS {                  // bits description
    Uint16 RESET:1;                     // 0 Software reset to CM
    Uint16 RESETSTS:1;                  // 1 CM Reset status
    Uint16 rsvd1:14;                    // 15:2 Reserved
    Uint16 KEY:16;                      // 31:16 Key value
};

union CMRESCTL_REG {
    Uint32  all;
    struct  CMRESCTL_BITS  bit;
};

struct CMTOCPU1NMICTL_BITS {            // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 rsvd2:1;                     // 1 Reserved
    Uint16 CMNMIWDRST:1;                // 2 CMNMIWDRST NMI enable bit, enables nmi generation to C28x
    Uint16 rsvd3:13;                    // 15:3 Reserved
    Uint16 rsvd4:16;                    // 31:16 Reserved
};

union CMTOCPU1NMICTL_REG {
    Uint32  all;
    struct  CMTOCPU1NMICTL_BITS  bit;
};

struct CMTOCPU1INTCTL_BITS {            // bits description
    Uint16 VECTRESET:1;                 // 0 VECTRESET Interrupt enable bit, enables interrupt to C28x
    Uint16 SYSRESETREQ:1;               // 1 SYSRESETREQ Interrupt enable bit, enables interrupt to C28x
    Uint16 CMNMIWDRST:1;                // 2 CMNMIWDRST Interrupt enable bit, enables interrupt to C28x
    Uint16 rsvd1:13;                    // 15:3 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union CMTOCPU1INTCTL_REG {
    Uint32  all;
    struct  CMTOCPU1INTCTL_BITS  bit;
};

struct PALLOCATE0_BITS {                // bits description
    Uint16 USB_A:1;                     // 0 Allocate USB_A to CM
    Uint16 ETHERCAT:1;                  // 1 Allocate ETHERCAT to CM
    Uint16 CAN_A:1;                     // 2 Allocate CANA to CM
    Uint16 CAN_B:1;                     // 3 Allocate CANB to CM
    Uint16 MCAN_A:1;                    // 4 Allocate MCANA to CM
    Uint16 rsvd1:11;                    // 15:5 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union PALLOCATE0_REG {
    Uint32  all;
    struct  PALLOCATE0_BITS  bit;
};

struct CM_CONF_REGS_LOCK_BITS {         // bits description
    Uint16 LOCK:1;                      // 0 Lock one time CM configuration registers.
    Uint16 rsvd1:15;                    // 15:1 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union CM_CONF_REGS_LOCK_REG {
    Uint32  all;
    struct  CM_CONF_REGS_LOCK_BITS  bit;
};

struct CM_CONF_REGS {
    union   CMRESCTL_REG                     CMRESCTL;                     // CM Reset Control Register
    union   CMTOCPU1NMICTL_REG               CMTOCPU1NMICTL;               // CM To CPU1 NMI Control register
    union   CMTOCPU1INTCTL_REG               CMTOCPU1INTCTL;               // CM To CPU1 interrupt Control register
    Uint16                                   rsvd1[26];                    // Reserved
    union   PALLOCATE0_REG                   PALLOCATE0;                   // CM Peripheral Allocation Register.
    Uint16                                   rsvd2[988];                   // Reserved
    union   CM_CONF_REGS_LOCK_REG            CM_CONF_REGS_LOCK;            // CM Configuration Registers Lock
};

struct CM_STATUS_INT_FLG_BITS {         // bits description
    Uint16 GINT:1;                      // 0 Global Interrupt flag
    Uint16 CMNMIWDRST:1;                // 1 CMNMIWDRST caused a reset of CM
    Uint16 CMSYSRESETREQ:1;             // 2 CMSYSRESETREQ caused a reset of CM
    Uint16 CMVECTRESET:1;               // 3 CMVECTRESET caused a reset of CM
    Uint16 rsvd1:12;                    // 15:4 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union CM_STATUS_INT_FLG_REG {
    Uint32  all;
    struct  CM_STATUS_INT_FLG_BITS  bit;
};

struct CM_STATUS_INT_CLR_BITS {         // bits description
    Uint16 GINT:1;                      // 0 Global Interrupt flag Clear bit
    Uint16 CMNMIWDRST:1;                // 1 CMNMIWDRST interrupt flag clear bit
    Uint16 CMSYSRESETREQ:1;             // 2 CMSYSRESETREQ interrupt flag clear bit
    Uint16 CMVECTRESET:1;               // 3 CMVECTRESET interrupt flag clear bit
    Uint16 rsvd1:12;                    // 15:4 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union CM_STATUS_INT_CLR_REG {
    Uint32  all;
    struct  CM_STATUS_INT_CLR_BITS  bit;
};

struct CM_STATUS_INT_SET_BITS {         // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 CMNMIWDRST:1;                // 1 CMNMIWDRST interrupt flag set bit
    Uint16 CMSYSRESETREQ:1;             // 2 CMSYSRESETREQ interrupt flag set bit
    Uint16 CMVECTRESET:1;               // 3 CMVECTRESET interrupt flag set bit
    Uint16 rsvd2:12;                    // 15:4 Reserved
    Uint16 KEY:16;                      // 31:16 KEY field
};

union CM_STATUS_INT_SET_REG {
    Uint32  all;
    struct  CM_STATUS_INT_SET_BITS  bit;
};

struct CM_STATUS_MASK_BITS {            // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 CMNMIWDRST:1;                // 1 CMNMIWDRST flag mask bit
    Uint16 CMSYSRESETREQ:1;             // 2 CMSYSRESETREQ interrupt flag set bit
    Uint16 CMVECTRESET:1;               // 3 CMVECTRESET interrupt flag set bit
    Uint16 rsvd2:12;                    // 15:4 Reserved
    Uint16 KEY:16;                      // 31:16 KEY field
};

union CM_STATUS_MASK_REG {
    Uint32  all;
    struct  CM_STATUS_MASK_BITS  bit;
};

struct SYS_ERR_INT_FLG_BITS {           // bits description
    Uint16 GINT:1;                      // 0 Global Interrupt flag
    Uint16 EMIF_ERR:1;                  // 1 EMIF error event flag
    Uint16 RAM_CORRECTABLE_ERR:1;       // 2 RAM correctable error flag
    Uint16 FLASH_CORRECTABLE_ERR:1;     // 3 FLASH correctable error flag
    Uint16 RAM_ACC_VIOL:1;              // 4 RAM access vioation flag.
    Uint16 SYS_PLL_SLIP_NOTSUPPORTED:1; // 5 System PLL Slip event flag.
    Uint16 AUX_PLL_SLIP_NOTSUPPORTED:1; // 6 Auxillary PLL Slip event flag.
    Uint16 DCC0:1;                      // 7 DCC0 Interrupt flag.
    Uint16 DCC1:1;                      // 8 DCC1 Interrupt flag.
    Uint16 DCC2:1;                      // 9 DCC2 Interrupt flag.
    Uint16 rsvd1:6;                     // 15:10 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union SYS_ERR_INT_FLG_REG {
    Uint32  all;
    struct  SYS_ERR_INT_FLG_BITS  bit;
};

struct SYS_ERR_INT_CLR_BITS {           // bits description
    Uint16 GINT:1;                      // 0 Global Interrupt flag Clear bit
    Uint16 EMIF_ERR:1;                  // 1 EMIF_ERR interrupt flag clear bit
    Uint16 RAM_CORRECTABLE_ERR:1;       // 2 RAM_CORRECTABLE_ERR interrupt flag clear bit
    Uint16 FLASH_CORRECTABLE_ERR:1;     // 3 FLASH_CORRECTABLE_ERR interrupt flag clear bit
    Uint16 RAM_ACC_VIOL:1;              // 4 RAM_ACC_VIOL interrupt flag clear bit
    Uint16 SYS_PLL_SLIP_NOTSUPPORTED:1; // 5 SYS_PLL_SLIP interrupt flag clear bit
    Uint16 AUX_PLL_SLIP_NOTSUPPORTED:1; // 6 AUX_PLL_SLIP interrupt flag clear bit
    Uint16 DCC0:1;                      // 7 DCC0 interrupt flag clear bit
    Uint16 DCC1:1;                      // 8 DCC1 interrupt flag clear bit
    Uint16 DCC2:1;                      // 9 DCC2 interrupt flag clear bit
    Uint16 rsvd1:6;                     // 15:10 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union SYS_ERR_INT_CLR_REG {
    Uint32  all;
    struct  SYS_ERR_INT_CLR_BITS  bit;
};

struct SYS_ERR_INT_SET_BITS {           // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 EMIF_ERR:1;                  // 1 Reserved
    Uint16 RAM_CORRECTABLE_ERR:1;       // 2 RAM_CORRECTABLE_ERR interrupt flag set bit
    Uint16 FLASH_CORRECTABLE_ERR:1;     // 3 FLASH_CORRECTABLE_ERR interrupt flag set bit
    Uint16 RAM_ACC_VIOL:1;              // 4 RAM_ACC_VIOL interrupt flag set bit
    Uint16 SYS_PLL_SLIP_NOTSUPPORTED:1; // 5 SYS_PLL_SLIP interrupt flag set bit
    Uint16 AUX_PLL_SLIP_NOTSUPPORTED:1; // 6 AUX_PLL_SLIP interrupt flag set bit
    Uint16 DCC0:1;                      // 7 DCC0 interrupt flag set bit
    Uint16 DCC1:1;                      // 8 DCC1 interrupt flag set bit
    Uint16 DCC2:1;                      // 9 DCC2 interrupt flag set bit
    Uint16 rsvd2:6;                     // 15:10 Reserved
    Uint16 KEY:16;                      // 31:16 KEY field
};

union SYS_ERR_INT_SET_REG {
    Uint32  all;
    struct  SYS_ERR_INT_SET_BITS  bit;
};

struct SYS_ERR_MASK_BITS {              // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 EMIF_ERR:1;                  // 1 Reserved
    Uint16 RAM_CORRECTABLE_ERR:1;       // 2 RAM_CORRECTABLE_ERR flag mask bit
    Uint16 FLASH_CORRECTABLE_ERR:1;     // 3 FLASH_CORRECTABLE_ERR flag mask bit
    Uint16 RAM_ACC_VIOL:1;              // 4 RAM_ACC_VIOL flag mask bit
    Uint16 SYS_PLL_SLIP:1;              // 5 SYS_PLL_SLIP flag mask bit
    Uint16 AUX_PLL_SLIP:1;              // 6 AUX_PLL_SLIP flag mask bit
    Uint16 DCC0:1;                      // 7 DCC0 flag mask bit
    Uint16 DCC1:1;                      // 8 DCC1 flag mask bit
    Uint16 DCC2:1;                      // 9 DCC2 flag mask bit
    Uint16 rsvd2:6;                     // 15:10 Reserved
    Uint16 KEY:16;                      // 31:16 KEY field
};

union SYS_ERR_MASK_REG {
    Uint32  all;
    struct  SYS_ERR_MASK_BITS  bit;
};

struct SYS_STATUS_REGS {
    union   CM_STATUS_INT_FLG_REG            CM_STATUS_INT_FLG;            // Status of interrupts due to multiple sources of Cortex-M4 reset.
    union   CM_STATUS_INT_CLR_REG            CM_STATUS_INT_CLR;            // CM_STATUS_INT_FLG clear register
    union   CM_STATUS_INT_SET_REG            CM_STATUS_INT_SET;            // CM_STATUS_INT_FLG set register
    union   CM_STATUS_MASK_REG               CM_STATUS_MASK;               // CM_STATUS_MASK register
    Uint16                                   rsvd1[8];                     // Reserved
    union   SYS_ERR_INT_FLG_REG              SYS_ERR_INT_FLG;              // Status of interrupts due to multiple different errors in the system.
    union   SYS_ERR_INT_CLR_REG              SYS_ERR_INT_CLR;              // SYS_ERR_INT_FLG clear register
    union   SYS_ERR_INT_SET_REG              SYS_ERR_INT_SET;              // SYS_ERR_INT_FLG set register
    union   SYS_ERR_MASK_REG                 SYS_ERR_MASK;                 // SYS_ERR_MASK register
};

struct SYNCSELECT_BITS {                // bits description
    Uint16 rsvd1:3;                     // 2:0 Reserved
    Uint16 rsvd2:3;                     // 5:3 Reserved
    Uint16 rsvd3:3;                     // 8:6 Reserved
    Uint16 rsvd4:3;                     // 11:9 Reserved
    Uint16 rsvd5:3;                     // 14:12 Reserved
    Uint16 rsvd6:1;                     // 15 Reserved
    Uint16 rsvd7:4;                     // 19:16 Reserved
    Uint16 rsvd8:4;                     // 23:20 Reserved
    Uint16 SYNCOUT:5;                   // 28:24 Select Syncout Source
    Uint16 rsvd9:3;                     // 31:29 Reserved
};

union SYNCSELECT_REG {
    Uint32  all;
    struct  SYNCSELECT_BITS  bit;
};

struct ADCSOCOUTSELECT_BITS {           // bits description
    Uint16 PWM1SOCAEN:1;                // 0 PWM1SOCAEN Enable for ADCSOCAOn
    Uint16 PWM2SOCAEN:1;                // 1 PWM2SOCAEN Enable for ADCSOCAOn
    Uint16 PWM3SOCAEN:1;                // 2 PWM3SOCAEN Enable for ADCSOCAOn
    Uint16 PWM4SOCAEN:1;                // 3 PWM4SOCAEN Enable for ADCSOCAOn
    Uint16 PWM5SOCAEN:1;                // 4 PWM5SOCAEN Enable for ADCSOCAOn
    Uint16 PWM6SOCAEN:1;                // 5 PWM6SOCAEN Enable for ADCSOCAOn
    Uint16 PWM7SOCAEN:1;                // 6 PWM7SOCAEN Enable for ADCSOCAOn
    Uint16 PWM8SOCAEN:1;                // 7 PWM8SOCAEN Enable for ADCSOCAOn
    Uint16 PWM9SOCAEN:1;                // 8 PWM9SOCAEN Enable for ADCSOCAOn
    Uint16 PWM10SOCAEN:1;               // 9 PWM10SOCAEN Enable for ADCSOCAOn
    Uint16 PWM11SOCAEN:1;               // 10 PWM11SOCAEN Enable for ADCSOCAOn
    Uint16 PWM12SOCAEN:1;               // 11 PWM12SOCAEN Enable for ADCSOCAOn
    Uint16 PWM13SOCAEN:1;               // 12 PWM13SOCAEN Enable for ADCSOCAOn
    Uint16 PWM14SOCAEN:1;               // 13 PWM14SOCAEN Enable for ADCSOCAOn
    Uint16 PWM15SOCAEN:1;               // 14 PWM15SOCAEN Enable for ADCSOCAOn
    Uint16 PWM16SOCAEN:1;               // 15 PWM16SOCAEN Enable for ADCSOCAOn
    Uint16 PWM1SOCBEN:1;                // 16 PWM1SOCBEN Enable for ADCSOCBOn
    Uint16 PWM2SOCBEN:1;                // 17 PWM2SOCBEN Enable for ADCSOCBOn
    Uint16 PWM3SOCBEN:1;                // 18 PWM3SOCBEN Enable for ADCSOCBOn
    Uint16 PWM4SOCBEN:1;                // 19 PWM4SOCBEN Enable for ADCSOCBOn
    Uint16 PWM5SOCBEN:1;                // 20 PWM5SOCBEN Enable for ADCSOCBOn
    Uint16 PWM6SOCBEN:1;                // 21 PWM6SOCBEN Enable for ADCSOCBOn
    Uint16 PWM7SOCBEN:1;                // 22 PWM7SOCBEN Enable for ADCSOCBOn
    Uint16 PWM8SOCBEN:1;                // 23 PWM8SOCBEN Enable for ADCSOCBOn
    Uint16 PWM9SOCBEN:1;                // 24 PWM9SOCBEN Enable for ADCSOCBOn
    Uint16 PWM10SOCBEN:1;               // 25 PWM10SOCBEN Enable for ADCSOCBOn
    Uint16 PWM11SOCBEN:1;               // 26 PWM11SOCBEN Enable for ADCSOCBOn
    Uint16 PWM12SOCBEN:1;               // 27 PWM12SOCBEN Enable for ADCSOCBOn
    Uint16 PWM13SOCBEN:1;               // 28 PWM13SOCBEN Enable for ADCSOCBOn
    Uint16 PWM14SOCBEN:1;               // 29 PWM14SOCBEN Enable for ADCSOCBOn
    Uint16 PWM15SOCBEN:1;               // 30 PWM15SOCBEN Enable for ADCSOCBOn
    Uint16 PWM16SOCBEN:1;               // 31 PWM16SOCBEN Enable for ADCSOCBOn
};

union ADCSOCOUTSELECT_REG {
    Uint32  all;
    struct  ADCSOCOUTSELECT_BITS  bit;
};

struct SYNCSOCLOCK_BITS {               // bits description
    Uint16 SYNCSELECT:1;                // 0 SYNCSEL Register Lock bit
    Uint16 ADCSOCOUTSELECT:1;           // 1 ADCSOCOUTSELECT Register Lock bit
    Uint16 rsvd1:14;                    // 15:2 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union SYNCSOCLOCK_REG {
    Uint32  all;
    struct  SYNCSOCLOCK_BITS  bit;
};

struct SYNC_SOC_REGS {
    union   SYNCSELECT_REG                   SYNCSELECT;                   // Sync Input and Output Select Register
    union   ADCSOCOUTSELECT_REG              ADCSOCOUTSELECT;              // External ADC (Off Chip) SOC Select Register
    union   SYNCSOCLOCK_REG                  SYNCSOCLOCK;                  // SYNCSEL and EXTADCSOC Select Lock register
};

//---------------------------------------------------------------------------
// SYSCTRL External References & Function Declarations:
//
#ifdef CPU1
extern volatile struct DMA_CLA_SRC_SEL_REGS DmaClaSrcSelRegs;
extern volatile struct CLK_CFG_REGS ClkCfgRegs;
extern volatile struct CPU_SYS_REGS CpuSysRegs;
extern volatile struct DEV_CFG_REGS DevCfgRegs;
extern volatile struct CPU1_PERIPH_AC_REGS SysPeriphAcRegs;
extern volatile struct CM_CONF_REGS CmConfRegs;
extern volatile struct SYS_STATUS_REGS SysStatusRegs;
extern volatile struct SYNC_SOC_REGS SyncSocRegs;
#endif
#ifdef CPU2
extern volatile struct DMA_CLA_SRC_SEL_REGS DmaClaSrcSelRegs;
extern volatile struct CLK_CFG_REGS ClkCfgRegs;
extern volatile struct CPU_SYS_REGS CpuSysRegs;
extern volatile struct CPU2_PERIPH_AC_REGS SysPeriphAcRegs;
extern volatile struct SYS_STATUS_REGS SysStatusRegs;
#endif
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
