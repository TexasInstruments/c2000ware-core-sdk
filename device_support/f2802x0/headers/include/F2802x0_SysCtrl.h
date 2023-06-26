//###########################################################################
//
// FILE:   F2802x0_SysCtrl.h
//
// TITLE:  F2802x0 Device System Control Register Definitions.
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:
// Copyright (C) 2009-2023 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef F2802x0_SYS_CTRL_H
#define F2802x0_SYS_CTRL_H

#ifdef __cplusplus
extern "C" {
#endif

//
// System Control Individual Register Bit Definitions:
//

//
// XCLKOUT Control
//
struct XCLK_BITS
{                           // bits  description
    uint16_t XCLKOUTDIV:2;  // 1:0   XCLKOUT Divide Ratio
    uint16_t rsvd1:3;       // 4:2   reserved
    uint16_t rsvd2:1;       // 5     reserved
    uint16_t XCLKINSEL:1;   // 6     XCLKIN Source Select bit
    uint16_t rsvd3:9;       // 15:7   reserved
};

union XCLK_REG 
{
    uint16_t                     all;
    struct XCLK_BITS           bit;
};

//
// PLL Status Register
//
struct PLLSTS_BITS
{                            // bits  description
    uint16_t PLLLOCKS:1;     // 0     PLL lock status
    uint16_t rsvd1:1;        // 1     reserved
    uint16_t PLLOFF:1;       // 2     PLL off bit
    uint16_t MCLKSTS:1;      // 3     Missing clock status bit
    uint16_t MCLKCLR:1;      // 4     Missing clock clear bit
    uint16_t OSCOFF:1;       // 5     Oscillator clock off
    uint16_t MCLKOFF:1;      // 6     Missing clock detect
    uint16_t DIVSEL:2;       // 8:7   Divide select (/4 default)
    uint16_t rsvd2:6;        // 14:9  reserved
    uint16_t NORMRDYE:1;     // 15    VREG NORMRDY enable bit
};

union PLLSTS_REG 
{
    uint16_t                     all;
    struct PLLSTS_BITS         bit;
};

//
// Clock Control Register
//
struct CLKCTL_BITS 
{                                // bits  description
    uint16_t OSCCLKSRCSEL:1;     // 0     Oscillator clock source select bit
    uint16_t OSCCLKSRC2SEL:1;    // 1     Oscillator 2 clock source select bit
    uint16_t WDCLKSRCSEL:1;      // 2     Watchdog clock source select bit
    uint16_t TMR2CLKSRCSEL:2;    // 4:3   CPU timer 2 clock source select bit
    uint16_t TMR2CLKPRESCALE:3;  // 7:5   CPU timer 2 clock pre-scale value
    uint16_t INTOSC1OFF:1;       // 8     Internal oscillator off bit
    
    //
    // 9     Internal oscillator 1 halt mode ignore bit
    //
    uint16_t INTOSC1HALTI:1;
    
    uint16_t INTOSC2OFF:1;       // 10    Internal oscillator 2 off bit
    
    //
    // 11    Internal oscillator 2 halt mode ignore bit
    //
    uint16_t INTOSC2HALTI:1;
    
    uint16_t WDHALTI:1;          // 12    Watchdog halt mode ignore bit
    uint16_t XCLKINOFF:1;        // 13    XCLKIN off bit
    uint16_t XTALOSCOFF:1;       // 14    Crystal (External) oscillator off bit
    uint16_t NMIRESETSEL:1;      // 15    NMI reset select bit
    };

union CLKCTL_REG 
{
    uint16_t                   all;
    struct CLKCTL_BITS         bit;
};

//
// Internal Oscillator 1 Trim
//
struct INTOSC1TRIM_BITS
{                                 // bits  description
    uint16_t COARSETRIM:8;        // 7:0   8-bit coarse trim value
    uint16_t rsvd1:1;             // 8     reserved
    uint16_t FINETRIM:6;          // 9:14  6-bit fine trim value
    uint16_t rsvd2:1;             // 15    reserved
};

union INTOSC1TRIM_REG 
{
    uint16_t                   all;
    struct INTOSC1TRIM_BITS    bit;
};

//
// Internal Oscillator 2 Trim
//
struct INTOSC2TRIM_BITS   
{                                 // bits  description
    uint16_t COARSETRIM:8;        // 7:0   8-bit coarse trim value
    uint16_t rsvd1:1;             // 8     reserved
    uint16_t FINETRIM:6;          // 9:14  6-bit fine trim value
    uint16_t rsvd2:1;             // 15    reserved
};

union INTOSC2TRIM_REG 
{
    uint16_t                     all;
    struct INTOSC2TRIM_BITS    bit;
};

//
// Low speed peripheral clock register bit definitions
//
struct LOSPCP_BITS  
{                          // bits  description
    uint16_t LSPCLK:3;     // 2:0   Rate relative to SYSCLKOUT
    uint16_t rsvd1:13;     // 15:3  reserved
};

union LOSPCP_REG 
{
    uint16_t                   all;
    struct LOSPCP_BITS         bit;
};

//
// Peripheral clock control register 0 bit definitions
//
struct PCLKCR0_BITS  
{                          // bits  description
    uint16_t rsvd1:2;      // 1:0     reserved
    uint16_t TBCLKSYNC:1;  // 2     ETWPM Module TBCLK enable/sync
    uint16_t ADCENCLK:1;   // 3     Enable high speed clk to ADC
    uint16_t I2CAENCLK:1;  // 4     Enable SYSCLKOUT to I2C-A
    uint16_t rsvd2:3;      // 7:5   reserved
    uint16_t SPIAENCLK:1;  // 8     Enable low speed clk to SPI-A
    uint16_t rsvd3:1;      // 9     reserved
    uint16_t SCIAENCLK:1;  // 10    Enable low speed clk to SCI-A
    uint16_t rsvd4:5;      // 15:11 reserved
};

union PCLKCR0_REG 
{
    uint16_t                   all;
    struct PCLKCR0_BITS        bit;
};

//
// Peripheral clock control register 1 bit definitions
//
struct PCLKCR1_BITS
{                            // bits  description
    uint16_t EPWM1ENCLK:1;   // 0     Enable SYSCLKOUT to EPWM1
    uint16_t EPWM2ENCLK:1;   // 1     Enable SYSCLKOUT to EPWM2
    uint16_t EPWM3ENCLK:1;   // 2     Enable SYSCLKOUT to EPWM3
    uint16_t EPWM4ENCLK:1;   // 3     Enable SYSCLKOUT to EPWM4
    uint16_t rsvd1:4;        // 7:4   reserved
    uint16_t ECAP1ENCLK:1;   // 8     Enable SYSCLKOUT to ECAP1
    uint16_t rsvd2:7;        // 15:9  reserved
};

union PCLKCR1_REG 
{
    uint16_t                   all;
    struct PCLKCR1_BITS        bit;
};

//
// Peripheral clock control register 3 bit definitions
//
struct PCLKCR3_BITS  
{                               // bits  description
    uint16_t COMP1ENCLK:1;      // 0     Enable SYSCLKOUT to COMP1
    uint16_t COMP2ENCLK:1;      // 1     Enable SYSCLKOUT to COMP2
    uint16_t rsvd1:1;           // 2     reserved
    uint16_t rsvd2:5;           // 7:3   reserved
    uint16_t CPUTIMER0ENCLK:1;  // 8     Enable SYSCLKOUT to CPUTIMER0
    uint16_t CPUTIMER1ENCLK:1;  // 9     Enable SYSCLKOUT to CPUTIMER1
    uint16_t CPUTIMER2ENCLK:1;  // 10    Enable SYSCLKOUT to CPUTIMER2
    uint16_t rsvd3:2;           // 12:11 reserved
    uint16_t GPIOINENCLK:1;     // 13    Enable SYSCLKOUT to GPIO
    uint16_t rsvd4:2;           // 15:14
};

union PCLKCR3_REG 
{
    uint16_t                all;
    struct PCLKCR3_BITS     bit;
};

//
// PLL control register bit definitions
//
struct PLLCR_BITS 
{                           // bits  description
    uint16_t DIV:4;         // 3:0   Set clock ratio for the PLL
    uint16_t rsvd1:12;      // 15:4  reserved
};

union PLLCR_REG {
    uint16_t             all;
    struct PLLCR_BITS    bit;
};

//
// Low Power Mode 0 control register bit definitions
//
struct LPMCR0_BITS 
{                           // bits  description
    uint16_t LPM:2;         // 1:0   Set the low power mode
    uint16_t QUALSTDBY:6;   // 7:2   Qualification
    uint16_t rsvd1:7;       // 14:8  reserved
    uint16_t WDINTE:1;      // 15    Enables WD to wake the device from STANDBY
};

union LPMCR0_REG 
{
    uint16_t              all;
    struct LPMCR0_BITS  bit;
};

//
// System Control Register File
//
struct SYS_CTRL_REGS 
{
    union   XCLK_REG        XCLK;        // 0: XCLKOUT Control
    union   PLLSTS_REG      PLLSTS;      // 1: PLL Status Register
    union   CLKCTL_REG      CLKCTL;      // 2: Clock Control Register
    uint16_t                PLLLOCKPRD;  // 3: PLL Lock Period Register
    union   INTOSC1TRIM_REG INTOSC1TRIM; // 4: Internal Oscillator 1 Trim
    uint16_t                rsvd1;       // 5: reserved
    union   INTOSC2TRIM_REG INTOSC2TRIM; // 6: Internal Oscillator 2 Trim
    uint16_t                rsvd2[4];    // 7-10
    
    //
    // 11: Low-speed peripheral clock pre-scaler
    //
    union   LOSPCP_REG      LOSPCP;
    
    union   PCLKCR0_REG     PCLKCR0;   // 12: Peripheral clock control register
    union   PCLKCR1_REG     PCLKCR1;   // 13: Peripheral clock control register
    
    //
    // 14: Low-power mode control register 0
    //
    union   LPMCR0_REG      LPMCR0;
    
    uint16_t                rsvd3;       // 15: reserved
    union   PCLKCR3_REG     PCLKCR3;     // 16: Peripheral clock register
    union   PLLCR_REG       PLLCR;       // 17: PLL control register
    
    //
    // No bit definitions are defined for SCSR because
    // a read-modify-write instruction can clear the WDOVERRIDE bit
    //
    
    //
    // 18: System control and status register
    //
    uint16_t                SCSR;
    
    uint16_t                WDCNTR;      // 19: WD counter register
    uint16_t                rsvd4;       // 20
    uint16_t                WDKEY;       // 21: WD reset key register
    uint16_t                rsvd5[3];    // 22-24
    
    //
    // No bit definitions are defined for WDCR because
    // the proper value must be written to the WDCHK field
    // whenever writing to this register.
    //
    uint16_t                  WDCR;        // 25: WD timer control register
    uint16_t                  rsvd6[5];    // 26-28
};

//
// System Power Control Registers
//

//
// BOR configuration register bit definitions
//
struct BORCFG_BITS 
{                           // bits  description
    uint16_t BORENZ:1;      // 0     BOR enable active low bit
    uint16_t rsvd1:15;      // 15:1  reserved
};

union BORCFG_REG 
{
    uint16_t            all;
    struct BORCFG_BITS  bit;
};

struct SYS_PWR_CTRL_REGS 
{
    union    BORCFG_REG   BORCFG;       // 0: BOR Configuration Register
    uint16_t   rsvd1[2];                  // 1-2
};

//
// CSM Registers
//

//
// CSM Status & Control register bit definitions
//
struct  CSMSCR_BITS 
{                               // bit   description
    uint16_t     SECURE:1;      // 0     Secure flag
    uint16_t     rsvd1:14;      // 14-1  reserved
    uint16_t     FORCESEC:1;    // 15    Force Secure control bit
};

//
// Allow access to the bit fields or entire register
//
union CSMSCR_REG 
{
    uint16_t             all;
    struct CSMSCR_BITS bit;
};

//
// CSM Register File
//
struct  CSM_REGS 
{
    uint16_t           KEY0;    // KEY reg bits 15-0
    uint16_t           KEY1;    // KEY reg bits 31-16
    uint16_t           KEY2;    // KEY reg bits 47-32
    uint16_t           KEY3;    // KEY reg bits 63-48
    uint16_t           KEY4;    // KEY reg bits 79-64
    uint16_t           KEY5;    // KEY reg bits 95-80
    uint16_t           KEY6;    // KEY reg bits 111-96
    uint16_t           KEY7;    // KEY reg bits 127-112
    uint16_t           rsvd1;   // reserved
    uint16_t           rsvd2;   // reserved
    uint16_t           rsvd3;   // reserved
    uint16_t           rsvd4;   // reserved
    uint16_t           rsvd5;   // reserved
    uint16_t           rsvd6;   // reserved
    uint16_t           rsvd7;   // reserved
    union CSMSCR_REG CSMSCR;  // CSM Status & Control register
};

//
// Password locations
//
struct  CSM_PWL 
{
    uint16_t   PSWD0;  // PSWD bits 15-0
    uint16_t   PSWD1;  // PSWD bits 31-16
    uint16_t   PSWD2;  // PSWD bits 47-32
    uint16_t   PSWD3;  // PSWD bits 63-48
    uint16_t   PSWD4;  // PSWD bits 79-64
    uint16_t   PSWD5;  // PSWD bits 95-80
    uint16_t   PSWD6;  // PSWD bits 111-96
    uint16_t   PSWD7;  // PSWD bits 127-112
};

//
// Flash Registers Defines
//
#define FLASH_SLEEP   0x0000;
#define FLASH_STANDBY 0x0001;
#define FLASH_ACTIVE  0x0003;

//
// Flash Option Register bit definitions
//
struct  FOPT_BITS 
{                                // bit   description
    uint16_t     ENPIPE:1;       // 0     Enable Pipeline Mode
    uint16_t     rsvd:15;        // 1-15  reserved
};

//
// Allow access to the bit fields or entire register
//
union FOPT_REG 
{
    uint16_t           all;
    struct FOPT_BITS bit;
};

//
// Flash Power Modes Register bit definitions
//
struct  FPWR_BITS 
{                               // bit   description
    uint16_t     PWR:2;         // 0-1   Power Mode bits
    uint16_t     rsvd:14;       // 2-15  reserved
};

//
// Allow access to the bit fields or entire register
//
union FPWR_REG 
{
    uint16_t           all;
    struct FPWR_BITS bit;
};

//
// Flash Status Register bit definitions
//
struct  FSTATUS_BITS 
{                               // bit   description
    uint16_t     PWRS:2;        // 0-1   Power Mode Status bits
    
    //
    // 2     Bank/Pump Sleep to Standby Wait Counter Status bits
    //
    uint16_t     STDBYWAITS:1;
    
    //
    // 3     Bank/Pump Standby to Active Wait Counter Status bits
    //
    uint16_t     ACTIVEWAITS:1;
    
    uint16_t     rsvd1:4;       // 4-7   reserved
    uint16_t     V3STAT:1;      // 8     VDD3V Status Latch bit
    uint16_t     rsvd2:7;       // 9-15  reserved
};

//
// Allow access to the bit fields or entire register
//
union FSTATUS_REG 
{
    uint16_t                    all;
    struct FSTATUS_BITS         bit;
};

//
// Flash Sleep to Standby Wait Counter Register bit definitions
//
struct  FSTDBYWAIT_BITS 
{                               // bit   description
    //
    // 0-8   Bank/Pump Sleep to Standby Wait Count bits
    //
    uint16_t     STDBYWAIT:9;
    
    uint16_t     rsvd:7;        // 9-15  reserved
};

//
// Allow access to the bit fields or entire register
//
union FSTDBYWAIT_REG 
{
    uint16_t                    all;
    struct FSTDBYWAIT_BITS      bit;
};

//
// Flash Standby to Active Wait Counter Register bit definitions
//
struct  FACTIVEWAIT_BITS 
{                               // bit   description
    //
    // 0-8   Bank/Pump Standby to Active Wait Count bits
    //
    uint16_t     ACTIVEWAIT:9;
    uint16_t     rsvd:7;        // 9-15  reserved
};

//
// Allow access to the bit fields or entire register
//
union FACTIVEWAIT_REG 
{
    uint16_t                    all;
    struct FACTIVEWAIT_BITS     bit;
};

//
// Bank Read Access Wait State Register bit definitions
//
struct  FBANKWAIT_BITS 
{                               // bit   description
    uint16_t     RANDWAIT:4;    // 0-3   Flash Random Read Wait State bits
    uint16_t     rsvd1:4;       // 4-7   reserved
    uint16_t     PAGEWAIT:4;    // 8-11  Flash Paged Read Wait State bits
    uint16_t     rsvd2:4;       // 12-15 reserved
};

//
// Allow access to the bit fields or entire register
//
union FBANKWAIT_REG 
{
    uint16_t                    all;
    struct FBANKWAIT_BITS       bit;
};

//
// OTP Read Access Wait State Register bit definitions
//
struct  FOTPWAIT_BITS 
{                               // bit   description
    uint16_t     OTPWAIT:5;     // 0-4   OTP Read Wait State bits
    uint16_t     rsvd:11;       // 5-15  reserved
};

//
// Allow access to the bit fields or entire register
//
union FOTPWAIT_REG 
{
    uint16_t                    all;
    struct FOTPWAIT_BITS        bit;
};

struct FLASH_REGS 
{
    union FOPT_REG        FOPT;        // Option Register
    uint16_t              rsvd1;       // reserved
    union FPWR_REG        FPWR;        // Power Modes Register
    union FSTATUS_REG     FSTATUS;     // Status Register
    
    //
    // Pump/Bank Sleep to Standby Wait State Register
    //
    union FSTDBYWAIT_REG  FSTDBYWAIT;
    
    //
    // Pump/Bank Standby to Active Wait State Register
    //
    union FACTIVEWAIT_REG FACTIVEWAIT;
    
    union FBANKWAIT_REG   FBANKWAIT;   // Bank Read Access Wait State Register
    union FOTPWAIT_REG    FOTPWAIT;    // OTP Read Access Wait State Register
};

//
// System Control External References & Function Declarations:
//
extern volatile struct SYS_CTRL_REGS SysCtrlRegs;
extern volatile struct SYS_PWR_CTRL_REGS SysPwrCtrlRegs;
extern volatile struct CSM_REGS CsmRegs;
extern volatile struct CSM_PWL CsmPwl;
extern volatile struct FLASH_REGS FlashRegs;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif  // end of F2802x0_SYS_CTRL_H definition

//
// End of file
//

