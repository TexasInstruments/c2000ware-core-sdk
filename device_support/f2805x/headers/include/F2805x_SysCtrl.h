//###########################################################################
//
// FILE:   F2805x_Sysctrl.h
//
// TITLE:  F2805x Device SYSCTRL Register Definitions.
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:
// Copyright (C) 2012-2024 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef F2805x_SYSCTRL_H
#define F2805x_SYSCTRL_H

#ifdef __cplusplus
extern "C" {
#endif

//
// SYSCTRL Individual Register Bit Definitions:
//
struct XCLK_BITS {             // bits description
    Uint16  XCLKOUTDIV:2;      // 1:0 XCLKOUT Divide Ratio
    Uint16  rsvd1:4;           // 5:2 Reserved
    Uint16  XCLKINSEL:1;       // 6 XCLKIN Source Select
    Uint16  rsvd2:9;           // 15:7 Reserved
};

union XCLK_REG {
    Uint16  all;
    struct  XCLK_BITS  bit;
};

struct PLLSTS_BITS {           // bits description
    Uint16  PLLLOCKS:1;        // 0 PLL lock status
    Uint16  rsvd1:1;           // 1 Reserved
    Uint16  PLLOFF:1;          // 2 PLL off bit
    Uint16  MCLKSTS:1;         // 3 Missing clock status bit
    Uint16  MCLKCLR:1;         // 4 Missing clock clear bit
    Uint16  OSCOFF:1;          // 5 Oscillator clock off
    Uint16  MCLKOFF:1;         // 6 Missing clock detect
    Uint16  DIVSEL:2;          // 8:7 Divide select (/4 default)
    Uint16  rsvd2:6;           // 14:9 Reserved
    Uint16  NORMRDYE:1;        // 15 VREG NORMRDY enable bit
};

union PLLSTS_REG {
    Uint16  all;
    struct  PLLSTS_BITS  bit;
};

struct CLKCTL_BITS {          // bits description
    Uint16  OSCCLKSRCSEL:1;   // 0 Oscillator clock source select bit
    Uint16  OSCCLKSRC2SEL:1;  // 1 Oscillator 2 clock source select bit
    Uint16  WDCLKSRCSEL:1;    // 2 Watchdog clock source select bit
    Uint16  TMR2CLKSRCSEL:2;  // 4:3 CPU timer 2 clock source select bit
    Uint16  TMR2CLKPRESCALE:3;// 7:5 CPU timer 2 clock pre-scale value
    Uint16  INTOSC1OFF:1;     // 8 Internal oscillator off bit
    Uint16  INTOSC1HALTI:1;   // 9 Internal oscillator 1 halt mode ignore bit
    Uint16  INTOSC2OFF:1;     // 10 Internal oscillator 2 off bit
    Uint16  INTOSC2HALTI:1;   // 11 Internal oscillator 2 halt mode ignore bit
    Uint16  WDHALTI:1;        // 12 Watchdog halt mode ignore bit
    Uint16  XCLKINOFF:1;      // 13 XCLKIN off bit
    Uint16  XTALOSCOFF:1;     // 14 Crystal (External) oscillator off bit
    Uint16  NMIRESETSEL:1;    // 15 NMI reset select bit
};

union CLKCTL_REG {
    Uint16  all;
    struct  CLKCTL_BITS  bit;
};

struct INTOSC1TRIM_BITS {      // bits description
    Uint16  COARSETRIM:8;      // 7:0 8-bit coarse trim value
    Uint16  rsvd1:1;           // 8 Reserved
    Uint16  FINETRIM:6;        // 14:9 6-bit fine trim value
    Uint16  rsvd2:1;           // 15 Reserved
};

union INTOSC1TRIM_REG {
    Uint16  all;
    struct  INTOSC1TRIM_BITS  bit;
};

struct INTOSC2TRIM_BITS {      // bits description
    Uint16  COARSETRIM:8;      // 7:0 8-bit coarse trim value
    Uint16  rsvd1:1;           // 8 Reserved
    Uint16  FINETRIM:6;        // 14:9 6-bit fine trim value
    Uint16  rsvd2:1;           // 15 Reserved
};

union INTOSC2TRIM_REG {
    Uint16  all;
    struct  INTOSC2TRIM_BITS  bit;
};

struct LOSPCP_BITS {           // bits description
    Uint16  LSPCLK:3;          // 2:0 Rate relative to SYSCLKOUT
    Uint16  rsvd1:13;          // 15:3 Reserved
};

union LOSPCP_REG {
    Uint16  all;
    struct  LOSPCP_BITS  bit;
};

struct PCLKCR0_BITS {          // bits description
    Uint16  rsvd1:1;           // 0 Reserved
    Uint16  rsvd2:1;           // 1 Reserved
    Uint16  TBCLKSYNC:1;       // 2 ETWPM Module TBCLK enable/sync
    Uint16  ADCENCLK:1;        // 3 Enable high speed clk to ADC
    Uint16  I2CAENCLK:1;       // 4 I2C Clock Enable
    Uint16  SCICENCLK:1;       // 5 SCI C Clock Enable
    Uint16  rsvd3:2;           // 7:6 Reserved
    Uint16  SPIAENCLK:1;       // 8 SPI A Clock Enable
    Uint16  rsvd4:1;           // 9 Reserved
    Uint16  SCIAENCLK:1;       // 10 SCI A Clock Enable
    Uint16  SCIBENCLK:1;       // 11 SCI B Clock Enable
    Uint16  rsvd5:2;           // 13:12 Reserved
    Uint16  ECANAENCLK:1;      // 14 CAN A Clock Enable
    Uint16  rsvd6:1;           // 15 Reserved
};

union PCLKCR0_REG {
    Uint16  all;
    struct  PCLKCR0_BITS  bit;
};

struct PCLKCR1_BITS {          // bits description
    Uint16  EPWM1ENCLK:1;      // 0 EPWM1 Clock Enable
    Uint16  EPWM2ENCLK:1;      // 1 EPWM2 Clock Enable
    Uint16  EPWM3ENCLK:1;      // 2 EPWM3 Clock Enable
    Uint16  EPWM4ENCLK:1;      // 3 EPWM4 Clock Enable
    Uint16  EPWM5ENCLK:1;      // 4 EPWM5 Clock Enable
    Uint16  EPWM6ENCLK:1;      // 5 EPWM6 Clock Enable
    Uint16  EPWM7ENCLK:1;      // 6 EPWM7 Clock Enable
    Uint16  rsvd1:1;           // 7 Reserved
    Uint16  ECAP1ENCLK:1;      // 8 ECAP1 Clock Enable
    Uint16  rsvd2:5;           // 13:9 Reserved
    Uint16  EQEP1ENCLK:1;      // 14 EQEP1 Clock Enable
    Uint16  rsvd3:1;           // 15 Reserved
};

union PCLKCR1_REG {
    Uint16  all;
    struct  PCLKCR1_BITS  bit;
};

struct PCLKCR3_BITS {          // bits description
    Uint16  rsvd1:8;           // 7:0 Reserved
    Uint16  CPUTIMER0ENCLK:1;  // 8 Enable SYSCLKOUT to CPUTIMER0
    Uint16  CPUTIMER1ENCLK:1;  // 9 Enable SYSCLKOUT to CPUTIMER1
    Uint16  CPUTIMER2ENCLK:1;  // 10 Enable SYSCLKOUT to CPUTIMER2
    Uint16  rsvd2:3;           // 13:11 Reserved
    Uint16  CLA1ENCLK:1;       // 14 CLA Clock Enable
    Uint16  rsvd3:1;           // 15 Reserved
};

union PCLKCR3_REG {
    Uint16  all;
    struct  PCLKCR3_BITS  bit;
};
//
// Digital Filter & Comparator Trip Clock Enable
//
struct PCLKCR4_BITS {
    Uint16  CTRIPA1ENCLK:1;
    Uint16  CTRIPA3ENCLK:1;
    Uint16  CTRIPB1ENCLK:1;
    Uint16  CTRIPA6ENCLK:1;
    Uint16  CTRIPB4ENCLK:1;
    Uint16  CTRIPB6ENCLK:1;
    Uint16  CTRIPPFCENCLK:1;
    Uint16  rsvd1:9;           // 15:7 Reserved
};

union PCLKCR4_REG {
    Uint16  all;
    struct  PCLKCR4_BITS  bit;
};

struct PLLCR_BITS {            // bits description
    Uint16  DIV:4;             // 3:0 Set Clock ratio for the PLL
    Uint16  rsvd1:12;          // 15:4 Reserved
};

union PLLCR_REG {
    Uint16  all;
    struct  PLLCR_BITS  bit;
};

struct LPMCR0_BITS {           // bits description
    Uint16  LPM:2;             // 1:0 Set the low power mode
    Uint16  QUALSTDBY:6;       // 7:2 Qualification
    Uint16  rsvd1:7;           // 14:8 Reserved
    Uint16  WDINTE:1;          // 15 Enables WD to wake the device from STANDBY
};

union LPMCR0_REG {
    Uint16  all;
    struct  LPMCR0_BITS  bit;
};

struct JTAGDEBUG_BITS {        // bits description
    Uint16  JTAGDIS:1;         // 0 JTAG Port Disable Bit
    Uint16  rsvd1:15;          // 15:1 Reserved
};

union JTAGDEBUG_REG {
    Uint16  all;
    struct  JTAGDEBUG_BITS  bit;
};

//Flash Registers
#define FLASH_SLEEP   0x0000;
#define FLASH_STANDBY 0x0001;
#define FLASH_ACTIVE  0x0003;

struct FOPT_BITS {             // bits description
    Uint16  ENPIPE:1;          // 0 Enable Pipeline Mode
    Uint16  rsvd1:15;          // 15:1 Reserved
};

union FOPT_REG {
    Uint16  all;
    struct  FOPT_BITS  bit;
};

struct FPWR_BITS {             // bits description
    Uint16  PWR:2;             // 1:0 Power Mode Bits
    Uint16  rsvd1:14;          // 15:2 Reserved
};

union FPWR_REG {
    Uint16  all;
    struct  FPWR_BITS  bit;
};

struct FSTATUS_BITS {          // bits description
    Uint16  PWRS:2;            // 1:0 Power Mode Status Bits
    Uint16  STDBYWAITS:1;      // 2 Bank/Pump Sleep to Standby Wait Counter
    Uint16  ACTIVEWAITS:1;     // 3 Bank/Pump Standby to Active Wait Counter
    Uint16  rsvd1:4;           // 7:4 Reserved
    Uint16  V3STAT:1;          // 8 VDD3V Status Latch Bit
    Uint16  rsvd2:7;           // 15:9 Reserved
};

union FSTATUS_REG {
    Uint16  all;
    struct  FSTATUS_BITS  bit;
};

struct FSTDBYWAIT_BITS {      // bits description
    Uint16  STDBYWAIT:9;      // 8:0 Bank/Pump Sleep to Standby Wait Count Bits
    Uint16  rsvd1:7;          // 15:9 Reserved
};

union FSTDBYWAIT_REG {
    Uint16  all;
    struct  FSTDBYWAIT_BITS  bit;
};

struct FACTIVEWAIT_BITS {    // bits description
    Uint16  ACTIVEWAIT:9;    // 8:0 Bank/Pump Standby to Active Wait Count Bits
    Uint16  rsvd1:7;         // 15:9 Reserved
};

union FACTIVEWAIT_REG {
    Uint16  all;
    struct  FACTIVEWAIT_BITS  bit;
};

struct FBANKWAIT_BITS {        // bits description
    Uint16  RANDWAIT:4;        // 3:0 Flash Random Read Wait State Bits
    Uint16  rsvd1:4;           // 7:4 Reserved
    Uint16  PAGEWAIT:4;        // 11:8 Flash Paged Read Wait State Bits
    Uint16  rsvd2:4;           // 15:12 Reserved
};

union FBANKWAIT_REG {
    Uint16  all;
    struct  FBANKWAIT_BITS  bit;
};

struct FOTPWAIT_BITS {         // bits description
    Uint16  OTPWAIT:5;         // 4:0 OTP Read Wait State Bits
    Uint16  rsvd1:11;          // 15:5 Reserved
};

union FOTPWAIT_REG {
    Uint16  all;
    struct  FOTPWAIT_BITS  bit;
};

struct BORCFG_BITS {           // bits description
    Uint16  BORENZ:1;          // 0 BOR Enable Active Low Bit
    Uint16  rsvd1:1;           // 1 Reserved
    Uint16  rsvd2:1;           // 2 Reserved
    Uint16  rsvd3:13;          // 15:3 Reserved
};

union BORCFG_REG {
    Uint16  all;
    struct  BORCFG_BITS  bit;
};

struct SYS_CTRL_REGS {
    union   XCLK_REG           XCLK;        // XCLKOUT Control
    union   PLLSTS_REG         PLLSTS;      // PLL Status Register
    union   CLKCTL_REG         CLKCTL;      // Clock Control Register
    Uint16                     PLLLOCKPRD;  // PLL Lock Period Register
    union   INTOSC1TRIM_REG    INTOSC1TRIM; // Internal Oscillator 1 Trim Reg
    Uint16                     rsvd1;       // Reserved
    union   INTOSC2TRIM_REG    INTOSC2TRIM; // Int 32KHz Oscillator 2 Trim Reg
    Uint16                     rsvd2[4];    // Reserved
    union   LOSPCP_REG         LOSPCP;   // Low-Speed Peripheral Clk Pre-Scaler
    union   PCLKCR0_REG        PCLKCR0;  // Peripheral Clock Control Reg 0
    union   PCLKCR1_REG        PCLKCR1;  // Peripheral Clock Control Reg 1
    union   LPMCR0_REG         LPMCR0;   // Low Power Mode Control Reg 0
    Uint16                     rsvd3;    // Reserved
    union   PCLKCR3_REG        PCLKCR3;  // Peripheral Clock Control Reg 3
    union   PLLCR_REG          PLLCR;    // PLL Control Register
    Uint16                     SCSR;     // System Control and Status Reg
    Uint16                     WDCNTR;   // Watchdog Counter Register
    union   PCLKCR4_REG        PCLKCR4;  // Peripheral Clock Control Reg 4
    Uint16                     WDKEY;    // Watchdog Reset Key Register
    Uint16                     rsvd4[3]; // Reserved
    Uint16                     WDCR;     // Watchdog Control Register
    union   JTAGDEBUG_REG      JTAGDEBUG;// JTAG Port Debug Register
    Uint16                     rsvd5[5]; // Reserved
};

struct SYS_PWR_CTRL_REGS {
    union   BORCFG_REG         BORCFG;      // BOR Configuration Register
    Uint16                     rsvd1;       // Reserved
    Uint16                     rsvd2;       // Reserved
};

struct FLASH_REGS {
    union FOPT_REG        FOPT;        //Option Register
    Uint16                rsvd1;       //Reserved
    union FPWR_REG        FPWR;        //Power Modes Register
    union FSTATUS_REG     FSTATUS;     //Status Register
    union FSTDBYWAIT_REG  FSTDBYWAIT;  //Pump/Bank Sleep to Standby Wait State
    union FACTIVEWAIT_REG FACTIVEWAIT; //Pump/Bank Standby to Active Wait State
    union FBANKWAIT_REG   FBANKWAIT;   //Bank Read Access Wait State Reg
    union FOTPWAIT_REG    FOTPWAIT;    //OTP Read Access Wait State Reg
};

//
// Sysctrl External References & Function Declarations:
//
extern volatile struct SYS_CTRL_REGS SysCtrlRegs;
extern volatile struct SYS_PWR_CTRL_REGS SysPwrCtrlRegs;
extern volatile struct FLASH_REGS FlashRegs;

#ifdef __cplusplus
}
#endif                                 /* extern "C" */


#endif                    // end of F2805x_SYSCTRL_H definition
//
// End of file
//
