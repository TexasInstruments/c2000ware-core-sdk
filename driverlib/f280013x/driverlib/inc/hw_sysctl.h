//###########################################################################
//
// FILE:    hw_sysctl.h
//
// TITLE:   Definitions for the SYSCTL registers.
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

#ifndef HW_SYSCTL_H
#define HW_SYSCTL_H

//*************************************************************************************************
//
// The following are defines for the SYSCTL register offsets
//
//*************************************************************************************************
#define SYSCTL_O_PARTIDL      0x8U     // Lower 32-bit of Device PART Identification Number
#define SYSCTL_O_PARTIDH      0xAU     // Upper 32-bit of Device PART Identification Number
#define SYSCTL_O_REVID        0xCU     // Device Revision Number
#define SYSCTL_O_TRIMERRSTS   0x74U    // TRIM Error Status register
#define SYSCTL_O_SOFTPRES2    0x86U    // EPWM Software Reset register
#define SYSCTL_O_SOFTPRES3    0x88U    // ECAP Software Reset register
#define SYSCTL_O_SOFTPRES4    0x8AU    // EQEP Software Reset register
#define SYSCTL_O_SOFTPRES7    0x90U    // SCI Software Reset register
#define SYSCTL_O_SOFTPRES8    0x92U    // SPI Software Reset register
#define SYSCTL_O_SOFTPRES9    0x94U    // I2C Software Reset register
#define SYSCTL_O_SOFTPRES10   0x96U    // CAN Software Reset register
#define SYSCTL_O_SOFTPRES13   0x9CU    // ADC Software Reset register
#define SYSCTL_O_SOFTPRES14   0x9EU    // CMPSS Software Reset register
#define SYSCTL_O_SOFTPRES21   0xACU    // DCC Software Reset register
#define SYSCTL_O_SOFTPRES27   0xB8U    // EPG Software Reset register
#define SYSCTL_O_SOFTPRES28   0xBAU    // Flash Software Reset register
#define SYSCTL_O_SOFTPRES40   0xD2U    // Peripheral Software Reset register
#define SYSCTL_O_TAP_STATUS   0x130U   // Status of JTAG State machine & Debugger Connect
#define SYSCTL_O_ECAPTYPE     0x19BU   // Configures ECAP Type for the device

#define SYSCTL_O_CLKCFGLOCK1     0x2U    // Lock bit for CLKCFG registers
#define SYSCTL_O_CLKSRCCTL1      0x8U    // Clock Source Control register-1
#define SYSCTL_O_CLKSRCCTL2      0xAU    // Clock Source Control register-2
#define SYSCTL_O_CLKSRCCTL3      0xCU    // Clock Source Control register-3
#define SYSCTL_O_SYSPLLCTL1      0xEU    // SYSPLL Control register-1
#define SYSCTL_O_SYSPLLMULT      0x14U   // SYSPLL Multiplier register
#define SYSCTL_O_SYSPLLSTS       0x16U   // SYSPLL Status register
#define SYSCTL_O_SYSCLKDIVSEL    0x22U   // System Clock Divider Select register
#define SYSCTL_O_XCLKOUTDIVSEL   0x28U   // XCLKOUT Divider Select register
#define SYSCTL_O_LOSPCP          0x2CU   // Low Speed Clock Source Prescalar
#define SYSCTL_O_MCDCR           0x2EU   // Missing Clock Detect Control Register
#define SYSCTL_O_X1CNT           0x30U   // 11-bit Counter on X1 Clock
#define SYSCTL_O_XTALCR          0x32U   // XTAL Control Register
#define SYSCTL_O_XTALCR2         0x3AU   // XTAL Control Register for pad init
#define SYSCTL_O_CLKFAILCFG      0x3CU   // Clock Fail cause Configuration

#define SYSCTL_O_CPUSYSLOCK1          0x0U    // Lock bit for CPUSYS registers
#define SYSCTL_O_CPUSYSLOCK2          0x2U    // Lock bit for CPUSYS registers
#define SYSCTL_O_PIEVERRADDR          0xAU    // PIE Vector Fetch Error Address register
#define SYSCTL_O_PCLKCR0              0x22U   // Peripheral Clock Gating Registers
#define SYSCTL_O_PCLKCR2              0x26U   // Peripheral Clock Gating Register - ETPWM
#define SYSCTL_O_PCLKCR3              0x28U   // Peripheral Clock Gating Register - ECAP
#define SYSCTL_O_PCLKCR4              0x2AU   // Peripheral Clock Gating Register - EQEP
#define SYSCTL_O_PCLKCR7              0x30U   // Peripheral Clock Gating Register - SCI
#define SYSCTL_O_PCLKCR8              0x32U   // Peripheral Clock Gating Register - SPI
#define SYSCTL_O_PCLKCR9              0x34U   // Peripheral Clock Gating Register - I2C
#define SYSCTL_O_PCLKCR10             0x36U   // Peripheral Clock Gating Register - CAN
#define SYSCTL_O_PCLKCR13             0x3CU   // Peripheral Clock Gating Register - ADC
#define SYSCTL_O_PCLKCR14             0x3EU   // Peripheral Clock Gating Register - CMPSS
#define SYSCTL_O_PCLKCR21             0x4CU   // Peripheral Clock Gating Register - DCC
#define SYSCTL_O_PCLKCR27             0x58U   // Peripheral Clock Gating Register - EPG
#define SYSCTL_O_SIMRESET             0x70U   // Simulated Reset Register
#define SYSCTL_O_LPMCR                0x76U   // LPM Control Register
#define SYSCTL_O_GPIOLPMSEL0          0x78U   // GPIO LPM Wakeup select registers
#define SYSCTL_O_GPIOLPMSEL1          0x7AU   // GPIO LPM Wakeup select registers
#define SYSCTL_O_TMR2CLKCTL           0x7CU   // Timer2 Clock Measurement functionality control
                                              // register
#define SYSCTL_O_RESCCLR              0x7EU   // Reset Cause Clear Register
#define SYSCTL_O_RESC                 0x80U   // Reset Cause register
#define SYSCTL_O_USER_REG1_SYSRSN     0xA0U   // Software Configurable registers reset by SYSRSn
#define SYSCTL_O_USER_REG2_SYSRSN     0xA2U   // Software Configurable registers reset by SYSRSn
#define SYSCTL_O_USER_REG1_XRSN       0xA4U   // Software Configurable registers reset by XRSn
#define SYSCTL_O_USER_REG2_XRSN       0xA6U   // Software Configurable registers reset by XRSn
#define SYSCTL_O_USER_REG1_PORESETN   0xA8U   // Software Configurable registers reset by PORESETn
#define SYSCTL_O_USER_REG2_PORESETN   0xAAU   // Software Configurable registers reset by PORESETn
#define SYSCTL_O_USER_REG3_PORESETN   0xACU   // Software Configurable registers reset by PORESETn
#define SYSCTL_O_USER_REG4_PORESETN   0xAEU   // Software Configurable registers reset by PORESETn

#define SYSCTL_O_SCSR     0x22U   // System Control & Status Register
#define SYSCTL_O_WDCNTR   0x23U   // Watchdog Counter Register
#define SYSCTL_O_WDKEY    0x25U   // Watchdog Reset Key Register
#define SYSCTL_O_WDCR     0x29U   // Watchdog Control Register
#define SYSCTL_O_WDWCR    0x2AU   // Watchdog Windowed Control Register

#define SYSCTL_O_SYNCSELECT        0x0U   // Sync Input and Output Select Register
#define SYSCTL_O_ADCSOCOUTSELECT   0x2U   // External ADCSOC Select Register
#define SYSCTL_O_SYNCSOCLOCK       0x4U   // SYNCSEL and EXTADCSOC Select Lock register

#define SYSCTL_O_SYS_ERR_INT_FLG   0x10U   // Status of interrupts due to multiple different errors
                                           // in the system.
#define SYSCTL_O_SYS_ERR_INT_CLR   0x12U   // SYS_ERR_INT_FLG clear register
#define SYSCTL_O_SYS_ERR_INT_SET   0x14U   // SYS_ERR_INT_FLG set register
#define SYSCTL_O_SYS_ERR_MASK      0x16U   // SYS_ERR_MASK register


//*************************************************************************************************
//
// The following are defines for the bit fields in the PARTIDL register
//
//*************************************************************************************************
#define SYSCTL_PARTIDL_QUAL_S        6U
#define SYSCTL_PARTIDL_QUAL_M        0xC0U     // Qualification Status
#define SYSCTL_PARTIDL_PIN_COUNT_S   8U
#define SYSCTL_PARTIDL_PIN_COUNT_M   0x700U    // Device Pin Count
#define SYSCTL_PARTIDL_INSTASPIN_S   13U
#define SYSCTL_PARTIDL_INSTASPIN_M   0x6000U   // Instaspin feature set

//*************************************************************************************************
//
// The following are defines for the bit fields in the PARTIDH register
//
//*************************************************************************************************
#define SYSCTL_PARTIDH_FAMILY_S            8U
#define SYSCTL_PARTIDH_FAMILY_M            0xFF00U       // Device family
#define SYSCTL_PARTIDH_PARTNO_S            16U
#define SYSCTL_PARTIDH_PARTNO_M            0xFF0000U     // Device part number
#define SYSCTL_PARTIDH_DEVICE_CLASS_ID_S   24U
#define SYSCTL_PARTIDH_DEVICE_CLASS_ID_M   0xFF000000U   // Device class ID

//*************************************************************************************************
//
// The following are defines for the bit fields in the REVID register
//
//*************************************************************************************************
#define SYSCTL_REVID_REVID_S   0U
#define SYSCTL_REVID_REVID_M   0xFFFFU   // Device Revision ID. This is specific to the Device

//*************************************************************************************************
//
// The following are defines for the bit fields in the TRIMERRSTS register
//
//*************************************************************************************************
#define SYSCTL_TRIMERRSTS_LERR_S   0U
#define SYSCTL_TRIMERRSTS_LERR_M   0xFFFFU   // TRIM Load error status

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES2 register
//
//*************************************************************************************************
#define SYSCTL_SOFTPRES2_EPWM1   0x1U    // EPWM1 software reset bit
#define SYSCTL_SOFTPRES2_EPWM2   0x2U    // EPWM2 software reset bit
#define SYSCTL_SOFTPRES2_EPWM3   0x4U    // EPWM3 software reset bit
#define SYSCTL_SOFTPRES2_EPWM4   0x8U    // EPWM4 software reset bit
#define SYSCTL_SOFTPRES2_EPWM5   0x10U   // EPWM5 software reset bit
#define SYSCTL_SOFTPRES2_EPWM6   0x20U   // EPWM6 software reset bit
#define SYSCTL_SOFTPRES2_EPWM7   0x40U   // EPWM7 software reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES3 register
//
//*************************************************************************************************
#define SYSCTL_SOFTPRES3_ECAP1   0x1U   // ECAP1 software reset bit
#define SYSCTL_SOFTPRES3_ECAP2   0x2U   // ECAP2 software reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES4 register
//
//*************************************************************************************************
#define SYSCTL_SOFTPRES4_EQEP1   0x1U   // EQEP1 software reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES7 register
//
//*************************************************************************************************
#define SYSCTL_SOFTPRES7_SCI_A   0x1U   // SCI_A software reset bit
#define SYSCTL_SOFTPRES7_SCI_B   0x2U   // SCI_B software reset bit
#define SYSCTL_SOFTPRES7_SCI_C   0x4U   // SCI_C software reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES8 register
//
//*************************************************************************************************
#define SYSCTL_SOFTPRES8_SPI_A   0x1U   // SPI_A software reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES9 register
//
//*************************************************************************************************
#define SYSCTL_SOFTPRES9_I2C_A   0x1U   // I2C_A software reset bit
#define SYSCTL_SOFTPRES9_I2C_B   0x2U   // I2C_B software reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES10 register
//
//*************************************************************************************************
#define SYSCTL_SOFTPRES10_CAN_A   0x1U   // CAN_A software reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES13 register
//
//*************************************************************************************************
#define SYSCTL_SOFTPRES13_ADC_A   0x1U   // ADC_A software reset bit
#define SYSCTL_SOFTPRES13_ADC_C   0x4U   // ADC_C software reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES14 register
//
//*************************************************************************************************
#define SYSCTL_SOFTPRES14_CMPSS1   0x1U   // CMPSS1 software reset bit
#define SYSCTL_SOFTPRES14_CMPSS2   0x2U   // CMPSS2 software reset bit
#define SYSCTL_SOFTPRES14_CMPSS3   0x4U   // CMPSS3 software reset bit
#define SYSCTL_SOFTPRES14_CMPSS4   0x8U   // CMPSS4 software reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES21 register
//
//*************************************************************************************************
#define SYSCTL_SOFTPRES21_DCC0   0x1U   // DCC Module reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES27 register
//
//*************************************************************************************************
#define SYSCTL_SOFTPRES27_EPG1   0x1U   // EPG Module Reset Bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES28 register
//
//*************************************************************************************************
#define SYSCTL_SOFTPRES28_FLASHA   0x1U   // Flash Wrapper Module Reset Bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES40 register
//
//*************************************************************************************************
#define SYSCTL_SOFTPRES40_JTAG_NTRST_S       0U
#define SYSCTL_SOFTPRES40_JTAG_NTRST_M       0xFU          // Multi Bit JTAG nTRST
#define SYSCTL_SOFTPRES40_JTAG_NTRST_KEY_S   16U
#define SYSCTL_SOFTPRES40_JTAG_NTRST_KEY_M   0xFFFF0000U   // JTAG nTRST Key

//*************************************************************************************************
//
// The following are defines for the bit fields in the TAP_STATUS register
//
//*************************************************************************************************
#define SYSCTL_TAP_STATUS_TAP_STATE_S   0U
#define SYSCTL_TAP_STATUS_TAP_STATE_M   0xFFFFU       // Present TAP State
#define SYSCTL_TAP_STATUS_DCON          0x80000000U   // Debugger Connect Indication

//*************************************************************************************************
//
// The following are defines for the bit fields in the ECAPTYPE register
//
//*************************************************************************************************
#define SYSCTL_ECAPTYPE_TYPE_S   0U
#define SYSCTL_ECAPTYPE_TYPE_M   0x3U      // Configure ECAP type
#define SYSCTL_ECAPTYPE_LOCK     0x8000U   // Lock bit for the register


//*************************************************************************************************
//
// The following are defines for the bit fields in the CLKCFGLOCK1 register
//
//*************************************************************************************************
#define SYSCTL_CLKCFGLOCK1_CLKSRCCTL1     0x1U       // Lock bit for CLKSRCCTL1 register
#define SYSCTL_CLKCFGLOCK1_CLKSRCCTL2     0x2U       // Lock bit for CLKSRCCTL2 register
#define SYSCTL_CLKCFGLOCK1_CLKSRCCTL3     0x4U       // Lock bit for CLKSRCCTL3 register
#define SYSCTL_CLKCFGLOCK1_SYSPLLCTL1     0x8U       // Lock bit for SYSPLLCTL1 register
#define SYSCTL_CLKCFGLOCK1_SYSPLLMULT     0x40U      // Lock bit for SYSPLLMULT register
#define SYSCTL_CLKCFGLOCK1_SYSCLKDIVSEL   0x800U     // Lock bit for SYSCLKDIVSEL register
#define SYSCTL_CLKCFGLOCK1_LOSPCP         0x8000U    // Lock bit for LOSPCP register
#define SYSCTL_CLKCFGLOCK1_XTALCR         0x10000U   // Lock bit for XTALCR  & XTALCR2 register

//*************************************************************************************************
//
// The following are defines for the bit fields in the CLKSRCCTL1 register
//
//*************************************************************************************************
#define SYSCTL_CLKSRCCTL1_OSCCLKSRCSEL_S   0U
#define SYSCTL_CLKSRCCTL1_OSCCLKSRCSEL_M   0x3U    // OSCCLK Source Select Bit
#define SYSCTL_CLKSRCCTL1_WDHALTI          0x20U   // Watchdog HALT Mode Ignore Bit
#define SYSCTL_CLKSRCCTL1_INTOSC2CLKMODE   0x80U   // Select IntR or ExtR mode for INTOSC2

//*************************************************************************************************
//
// The following are defines for the bit fields in the CLKSRCCTL2 register
//
//*************************************************************************************************
#define SYSCTL_CLKSRCCTL2_CANABCLKSEL_S   2U
#define SYSCTL_CLKSRCCTL2_CANABCLKSEL_M   0xCU   // CANA Bit Clock Source Select Bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the CLKSRCCTL3 register
//
//*************************************************************************************************
#define SYSCTL_CLKSRCCTL3_XCLKOUTSEL_S   0U
#define SYSCTL_CLKSRCCTL3_XCLKOUTSEL_M   0xFU   // XCLKOUT Source Select Bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SYSPLLCTL1 register
//
//*************************************************************************************************
#define SYSCTL_SYSPLLCTL1_PLLEN      0x1U   // SYSPLL enable/disable bit
#define SYSCTL_SYSPLLCTL1_PLLCLKEN   0x2U   // SYSPLL bypassed or included in the PLLSYSCLK path

//*************************************************************************************************
//
// The following are defines for the bit fields in the SYSPLLMULT register
//
//*************************************************************************************************
#define SYSCTL_SYSPLLMULT_IMULT_S    0U
#define SYSCTL_SYSPLLMULT_IMULT_M    0xFFU         // SYSPLL Integer Multiplier
#define SYSCTL_SYSPLLMULT_ODIV_S     16U
#define SYSCTL_SYSPLLMULT_ODIV_M     0x1F0000U     // Output Clock Divider
#define SYSCTL_SYSPLLMULT_REFDIV_S   24U
#define SYSCTL_SYSPLLMULT_REFDIV_M   0x1F000000U   // Reference Clock Divider

//*************************************************************************************************
//
// The following are defines for the bit fields in the SYSPLLSTS register
//
//*************************************************************************************************
#define SYSCTL_SYSPLLSTS_LOCKS                0x1U   // SYSPLL Lock Status Bit
#define SYSCTL_SYSPLLSTS_SLIPS_NOTSUPPORTED   0x2U   // SYSPLL Slip Status Bit
#define SYSCTL_SYSPLLSTS_REF_LOSTS            0x8U   // SYSPLL "Reference  Lost" Status Bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SYSCLKDIVSEL register
//
//*************************************************************************************************
#define SYSCTL_SYSCLKDIVSEL_PLLSYSCLKDIV_S     0U
#define SYSCTL_SYSCLKDIVSEL_PLLSYSCLKDIV_M     0x3FU    // PLLSYSCLK Divide Select
#define SYSCTL_SYSCLKDIVSEL_PLLSYSCLKDIV_LSB   0x100U   // Odd clock divider

//*************************************************************************************************
//
// The following are defines for the bit fields in the XCLKOUTDIVSEL register
//
//*************************************************************************************************
#define SYSCTL_XCLKOUTDIVSEL_XCLKOUTDIV_S   0U
#define SYSCTL_XCLKOUTDIVSEL_XCLKOUTDIV_M   0x3U   // XCLKOUT Divide Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the LOSPCP register
//
//*************************************************************************************************
#define SYSCTL_LOSPCP_LSPCLKDIV_S   0U
#define SYSCTL_LOSPCP_LSPCLKDIV_M   0x7U   // LSPCLK Divide Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCDCR register
//
//*************************************************************************************************
#define SYSCTL_MCDCR_MCLKSTS              0x1U    // Missing Clock Status Bit
#define SYSCTL_MCDCR_MCLKCLR              0x2U    // Missing Clock Clear Bit
#define SYSCTL_MCDCR_MCLKOFF              0x4U    // Missing Clock Detect Off Bit
#define SYSCTL_MCDCR_OSCOFF               0x8U    // Oscillator Clock Off Bit
#define SYSCTL_MCDCR_SYSREF_LOSTS         0x10U   // SYSPLL "Reference  Lost" Status Bit
#define SYSCTL_MCDCR_SYSREF_LOSTSCLR      0x20U   // Clear for Ref clock lost status
#define SYSCTL_MCDCR_SYSREF_LOST_MCD_EN   0x40U   // Enable for PLL REF_CLK_LOST as MCD cause

//*************************************************************************************************
//
// The following are defines for the bit fields in the X1CNT register
//
//*************************************************************************************************
#define SYSCTL_X1CNT_X1CNT_S   0U
#define SYSCTL_X1CNT_X1CNT_M   0x7FFU     // X1 Counter
#define SYSCTL_X1CNT_CLR       0x10000U   // X1 Counter Clear

//*************************************************************************************************
//
// The following are defines for the bit fields in the XTALCR register
//
//*************************************************************************************************
#define SYSCTL_XTALCR_OSCOFF   0x1U   // XTAL Oscillator powered-down
#define SYSCTL_XTALCR_SE       0x2U   // XTAL Oscilator in Single-Ended mode

//*************************************************************************************************
//
// The following are defines for the bit fields in the XTALCR2 register
//
//*************************************************************************************************
#define SYSCTL_XTALCR2_XIF   0x1U   // XI Initial value deposited before XOSC start
#define SYSCTL_XTALCR2_XOF   0x2U   // XO Initial value deposited before XOSC start
#define SYSCTL_XTALCR2_FEN   0x4U   // XOSC pads initialisation enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the CLKFAILCFG register
//
//*************************************************************************************************
#define SYSCTL_CLKFAILCFG_DCC0_ERROR_EN   0x1U   // DCC0 Error causes Clock fail NMI, ERROR


//*************************************************************************************************
//
// The following are defines for the bit fields in the CPUSYSLOCK1 register
//
//*************************************************************************************************
#define SYSCTL_CPUSYSLOCK1_PIEVERRADDR   0x4U          // Lock bit for PIEVERRADDR Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR0       0x8U          // Lock bit for PCLKCR0 Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR2       0x20U         // Lock bit for PCLKCR2 Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR3       0x40U         // Lock bit for PCLKCR3 Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR4       0x80U         // Lock bit for PCLKCR4 Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR6       0x200U        // Lock bit for PCLKCR6 Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR7       0x400U        // Lock bit for PCLKCR7 Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR8       0x800U        // Lock bit for PCLKCR8 Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR9       0x1000U       // Lock bit for PCLKCR9 Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR10      0x2000U       // Lock bit for PCLKCR10 Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR13      0x10000U      // Lock bit for PCLKCR13 Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR14      0x20000U      // Lock bit for PCLKCR14 Register
#define SYSCTL_CPUSYSLOCK1_LPMCR         0x200000U     // Lock bit for LPMCR Register
#define SYSCTL_CPUSYSLOCK1_GPIOLPMSEL0   0x400000U     // Lock bit for GPIOLPMSEL0 Register
#define SYSCTL_CPUSYSLOCK1_GPIOLPMSEL1   0x800000U     // Lock bit for GPIOLPMSEL1 Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR20      0x8000000U    // Lock bit for PCLKCR20 Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR21      0x10000000U   // Lock bit for PCLKCR21 Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR22      0x20000000U   // Lock bit for PCLKCR22 Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the CPUSYSLOCK2 register
//
//*************************************************************************************************
#define SYSCTL_CPUSYSLOCK2_PCLKCR27             0x8U          // Lock bit for PCLKCR27 Register
#define SYSCTL_CPUSYSLOCK2_USER_REG1_SYSRSN     0x1000000U    // Lock bit for USER_REG1_SYSRSn
#define SYSCTL_CPUSYSLOCK2_USER_REG2_SYSRSN     0x2000000U    // Lock bit for USER_REG2_SYSRSn
#define SYSCTL_CPUSYSLOCK2_USER_REG1_XRSN       0x4000000U    // Lock bit for USER_REG1_XRSn
#define SYSCTL_CPUSYSLOCK2_USER_REG2_XRSN       0x8000000U    // Lock bit for USER_REG2_XRSn
#define SYSCTL_CPUSYSLOCK2_USER_REG1_PORESETN   0x10000000U   // Lock bit for USER_REG1_PORESETn
#define SYSCTL_CPUSYSLOCK2_USER_REG2_PORESETN   0x20000000U   // Lock bit for USER_REG2_PORESETn
#define SYSCTL_CPUSYSLOCK2_USER_REG3_PORESETN   0x40000000U   // Lock bit for USER_REG3_PORESETn
#define SYSCTL_CPUSYSLOCK2_USER_REG4_PORESETN   0x80000000U   // Lock bit for USER_REG4_PORESETn

//*************************************************************************************************
//
// The following are defines for the bit fields in the PIEVERRADDR register
//
//*************************************************************************************************
#define SYSCTL_PIEVERRADDR_ADDR_S   0U
#define SYSCTL_PIEVERRADDR_ADDR_M   0x3FFFFFU   // PIE Vector Fetch Error Handler Routine Address

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCLKCR0 register
//
//*************************************************************************************************
#define SYSCTL_PCLKCR0_CPUTIMER0   0x8U       // CPUTIMER0 Clock Enable bit
#define SYSCTL_PCLKCR0_CPUTIMER1   0x10U      // CPUTIMER1 Clock Enable bit
#define SYSCTL_PCLKCR0_CPUTIMER2   0x20U      // CPUTIMER2 Clock Enable bit
#define SYSCTL_PCLKCR0_HRCAL       0x10000U   // HRCAL Clock Enable Bit
#define SYSCTL_PCLKCR0_TBCLKSYNC   0x40000U   // EPWM Time Base Clock sync

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCLKCR2 register
//
//*************************************************************************************************
#define SYSCTL_PCLKCR2_EPWM1   0x1U    // EPWM1 Clock Enable bit
#define SYSCTL_PCLKCR2_EPWM2   0x2U    // EPWM2 Clock Enable bit
#define SYSCTL_PCLKCR2_EPWM3   0x4U    // EPWM3 Clock Enable bit
#define SYSCTL_PCLKCR2_EPWM4   0x8U    // EPWM4 Clock Enable bit
#define SYSCTL_PCLKCR2_EPWM5   0x10U   // EPWM5 Clock Enable bit
#define SYSCTL_PCLKCR2_EPWM6   0x20U   // EPWM6 Clock Enable bit
#define SYSCTL_PCLKCR2_EPWM7   0x40U   // EPWM7 Clock Enable bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCLKCR3 register
//
//*************************************************************************************************
#define SYSCTL_PCLKCR3_ECAP1   0x1U   // ECAP1 Clock Enable bit
#define SYSCTL_PCLKCR3_ECAP2   0x2U   // ECAP2 Clock Enable bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCLKCR4 register
//
//*************************************************************************************************
#define SYSCTL_PCLKCR4_EQEP1   0x1U   // EQEP1 Clock Enable bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCLKCR7 register
//
//*************************************************************************************************
#define SYSCTL_PCLKCR7_SCI_A   0x1U   // SCI_A Clock Enable bit
#define SYSCTL_PCLKCR7_SCI_B   0x2U   // SCI_B Clock Enable bit
#define SYSCTL_PCLKCR7_SCI_C   0x4U   // SCI_C Clock Enable bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCLKCR8 register
//
//*************************************************************************************************
#define SYSCTL_PCLKCR8_SPI_A   0x1U   // SPI_A Clock Enable bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCLKCR9 register
//
//*************************************************************************************************
#define SYSCTL_PCLKCR9_I2C_A   0x1U   // I2C_A Clock Enable bit
#define SYSCTL_PCLKCR9_I2C_B   0x2U   // I2C_B Clock Enable bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCLKCR10 register
//
//*************************************************************************************************
#define SYSCTL_PCLKCR10_CAN_A   0x1U   // CAN_A Clock Enable bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCLKCR13 register
//
//*************************************************************************************************
#define SYSCTL_PCLKCR13_ADC_A   0x1U   // ADC_A Clock Enable bit
#define SYSCTL_PCLKCR13_ADC_C   0x4U   // ADC_C Clock Enable bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCLKCR14 register
//
//*************************************************************************************************
#define SYSCTL_PCLKCR14_CMPSS1   0x1U   // CMPSS1 Clock Enable bit
#define SYSCTL_PCLKCR14_CMPSS2   0x2U   // CMPSS2 Clock Enable bit
#define SYSCTL_PCLKCR14_CMPSS3   0x4U   // CMPSS3 Clock Enable bit
#define SYSCTL_PCLKCR14_CMPSS4   0x8U   // CMPSS4 Clock Enable bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCLKCR21 register
//
//*************************************************************************************************
#define SYSCTL_PCLKCR21_DCC0   0x1U   // DCC0 Clock Enable Bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCLKCR27 register
//
//*************************************************************************************************
#define SYSCTL_PCLKCR27_EPG1   0x1U   // EPG1 Clock Enable Bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SIMRESET register
//
//*************************************************************************************************
#define SYSCTL_SIMRESET_CPU1RSN   0x1U          // Generates a reset to CPU
#define SYSCTL_SIMRESET_XRSN      0x2U          // Generates a simulated XRSn
#define SYSCTL_SIMRESET_KEY_S     16U
#define SYSCTL_SIMRESET_KEY_M     0xFFFF0000U   // Key value to enable write

//*************************************************************************************************
//
// The following are defines for the bit fields in the LPMCR register
//
//*************************************************************************************************
#define SYSCTL_LPMCR_LPM_S         0U
#define SYSCTL_LPMCR_LPM_M         0x3U      // Low Power Mode setting
#define SYSCTL_LPMCR_QUALSTDBY_S   2U
#define SYSCTL_LPMCR_QUALSTDBY_M   0xFCU     // STANDBY Wakeup Pin Qualification Setting
#define SYSCTL_LPMCR_WDINTE        0x8000U   // Enable for WDINT wakeup from STANDBY

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPIOLPMSEL0 register
//
//*************************************************************************************************
#define SYSCTL_GPIOLPMSEL0_GPIO0    0x1U          // GPIO0 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO1    0x2U          // GPIO1 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO2    0x4U          // GPIO2 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO3    0x8U          // GPIO3 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO4    0x10U         // GPIO4 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO5    0x20U         // GPIO5 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO6    0x40U         // GPIO6 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO7    0x80U         // GPIO7 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO8    0x100U        // GPIO8 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO9    0x200U        // GPIO9 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO10   0x400U        // GPIO10 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO11   0x800U        // GPIO11 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO12   0x1000U       // GPIO12 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO13   0x2000U       // GPIO13 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO14   0x4000U       // GPIO14 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO15   0x8000U       // GPIO15 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO16   0x10000U      // GPIO16 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO17   0x20000U      // GPIO17 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO18   0x40000U      // GPIO18 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO19   0x80000U      // GPIO19 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO20   0x100000U     // GPIO20 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO21   0x200000U     // GPIO21 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO22   0x400000U     // GPIO22 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO23   0x800000U     // GPIO23 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO24   0x1000000U    // GPIO24 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO25   0x2000000U    // GPIO25 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO26   0x4000000U    // GPIO26 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO27   0x8000000U    // GPIO27 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO28   0x10000000U   // GPIO28 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO29   0x20000000U   // GPIO29 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO30   0x40000000U   // GPIO30 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL0_GPIO31   0x80000000U   // GPIO31 Enable for LPM Wakeup

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPIOLPMSEL1 register
//
//*************************************************************************************************
#define SYSCTL_GPIOLPMSEL1_GPIO32   0x1U          // GPIO32 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO33   0x2U          // GPIO33 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO34   0x4U          // GPIO34 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO35   0x8U          // GPIO35 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO36   0x10U         // GPIO36 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO37   0x20U         // GPIO37 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO38   0x40U         // GPIO38 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO39   0x80U         // GPIO39 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO40   0x100U        // GPIO40 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO41   0x200U        // GPIO41 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO42   0x400U        // GPIO42 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO43   0x800U        // GPIO43 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO44   0x1000U       // GPIO44 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO45   0x2000U       // GPIO45 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO46   0x4000U       // GPIO46 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO47   0x8000U       // GPIO47 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO48   0x10000U      // GPIO48 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO49   0x20000U      // GPIO49 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO50   0x40000U      // GPIO50 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO51   0x80000U      // GPIO51 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO52   0x100000U     // GPIO52 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO53   0x200000U     // GPIO53 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO54   0x400000U     // GPIO54 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO55   0x800000U     // GPIO55 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO56   0x1000000U    // GPIO56 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO57   0x2000000U    // GPIO57 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO58   0x4000000U    // GPIO58 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO59   0x8000000U    // GPIO59 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO60   0x10000000U   // GPIO60 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO61   0x20000000U   // GPIO61 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO62   0x40000000U   // GPIO62 Enable for LPM Wakeup
#define SYSCTL_GPIOLPMSEL1_GPIO63   0x80000000U   // GPIO63 Enable for LPM Wakeup

//*************************************************************************************************
//
// The following are defines for the bit fields in the TMR2CLKCTL register
//
//*************************************************************************************************
#define SYSCTL_TMR2CLKCTL_TMR2CLKSRCSEL_S     0U
#define SYSCTL_TMR2CLKCTL_TMR2CLKSRCSEL_M     0x7U    // CPU Timer 2 Clock Source Select Bit
#define SYSCTL_TMR2CLKCTL_TMR2CLKPRESCALE_S   3U
#define SYSCTL_TMR2CLKCTL_TMR2CLKPRESCALE_M   0x38U   // CPU Timer 2 Clock Pre-Scale Value

//*************************************************************************************************
//
// The following are defines for the bit fields in the RESCCLR register
//
//*************************************************************************************************
#define SYSCTL_RESCCLR_POR                0x1U     // POR Reset Cause Indication Bit
#define SYSCTL_RESCCLR_XRSN               0x2U     // XRSn Reset Cause Indication Bit
#define SYSCTL_RESCCLR_WDRSN              0x4U     // WDRSn Reset Cause Indication Bit
#define SYSCTL_RESCCLR_NMIWDRSN           0x8U     // NMIWDRSn Reset Cause Indication Bit
#define SYSCTL_RESCCLR_SCCRESETN          0x100U   // SCCRESETn Reset Cause Indication Bit
#define SYSCTL_RESCCLR_SIMRESET_CPU1RSN   0x400U   // SIMRESET_CPU1RSn Reset Cause Indication Bit
#define SYSCTL_RESCCLR_SIMRESET_XRSN      0x800U   // SIMRESET_XRSn Reset Cause Indication Bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the RESC register
//
//*************************************************************************************************
#define SYSCTL_RESC_POR                0x1U          // POR Reset Cause Indication Bit
#define SYSCTL_RESC_XRSN               0x2U          // XRSn Reset Cause Indication Bit
#define SYSCTL_RESC_WDRSN              0x4U          // WDRSn Reset Cause Indication Bit
#define SYSCTL_RESC_NMIWDRSN           0x8U          // NMIWDRSn Reset Cause Indication Bit
#define SYSCTL_RESC_SCCRESETN          0x100U        // SCCRESETn Reset Cause Indication Bit
#define SYSCTL_RESC_SIMRESET_CPU1RSN   0x400U        // SIMRESET_CPU1RSn Reset Cause Indication Bit
#define SYSCTL_RESC_SIMRESET_XRSN      0x800U        // SIMRESET_XRSn Reset Cause Indication Bit
#define SYSCTL_RESC_XRSN_PIN_STATUS    0x40000000U   // XRSN Pin Status
#define SYSCTL_RESC_DCON               0x80000000U   // Debugger conntion status to C28x


//*************************************************************************************************
//
// The following are defines for the bit fields in the SCSR register
//
//*************************************************************************************************
#define SYSCTL_SCSR_WDOVERRIDE   0x1U   // WD Override for WDDIS bit
#define SYSCTL_SCSR_WDENINT      0x2U   // WD Interrupt Enable
#define SYSCTL_SCSR_WDINTS       0x4U   // WD Interrupt Status

//*************************************************************************************************
//
// The following are defines for the bit fields in the WDCNTR register
//
//*************************************************************************************************
#define SYSCTL_WDCNTR_WDCNTR_S   0U
#define SYSCTL_WDCNTR_WDCNTR_M   0xFFU   // WD Counter

//*************************************************************************************************
//
// The following are defines for the bit fields in the WDKEY register
//
//*************************************************************************************************
#define SYSCTL_WDKEY_WDKEY_S   0U
#define SYSCTL_WDKEY_WDKEY_M   0xFFU   // Key to pet the watchdog timer.

//*************************************************************************************************
//
// The following are defines for the bit fields in the WDCR register
//
//*************************************************************************************************
#define SYSCTL_WDCR_WDPS_S          0U
#define SYSCTL_WDCR_WDPS_M          0x7U     // WD Clock Prescalar
#define SYSCTL_WDCR_WDCHK_S         3U
#define SYSCTL_WDCR_WDCHK_M         0x38U    // WD Check Bits
#define SYSCTL_WDCR_WDDIS           0x40U    // WD Disable
#define SYSCTL_WDCR_WDPRECLKDIV_S   8U
#define SYSCTL_WDCR_WDPRECLKDIV_M   0xF00U   // WD Pre Clock Divider

//*************************************************************************************************
//
// The following are defines for the bit fields in the WDWCR register
//
//*************************************************************************************************
#define SYSCTL_WDWCR_MIN_S   0U
#define SYSCTL_WDWCR_MIN_M   0xFFU   // WD Min Threshold setting for Windowed Watchdog
                                     // functionality


//*************************************************************************************************
//
// The following are defines for the bit fields in the SYNCSELECT register
//
//*************************************************************************************************
#define SYSCTL_SYNCSELECT_SYNCOUT_S   24U
#define SYSCTL_SYNCSELECT_SYNCOUT_M   0x1F000000U   // Select Syncout Source

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOCOUTSELECT register
//
//*************************************************************************************************
#define SYSCTL_ADCSOCOUTSELECT_PWM1SOCAEN   0x1U        // PWM1SOCAEN Enable for ADCSOCAOn
#define SYSCTL_ADCSOCOUTSELECT_PWM2SOCAEN   0x2U        // PWM2SOCAEN Enable for ADCSOCAOn
#define SYSCTL_ADCSOCOUTSELECT_PWM3SOCAEN   0x4U        // PWM3SOCAEN Enable for ADCSOCAOn
#define SYSCTL_ADCSOCOUTSELECT_PWM4SOCAEN   0x8U        // PWM4SOCAEN Enable for ADCSOCAOn
#define SYSCTL_ADCSOCOUTSELECT_PWM5SOCAEN   0x10U       // PWM5SOCAEN Enable for ADCSOCAOn
#define SYSCTL_ADCSOCOUTSELECT_PWM6SOCAEN   0x20U       // PWM6SOCAEN Enable for ADCSOCAOn
#define SYSCTL_ADCSOCOUTSELECT_PWM7SOCAEN   0x40U       // PWM7SOCAEN Enable for ADCSOCAOn
#define SYSCTL_ADCSOCOUTSELECT_PWM1SOCBEN   0x10000U    // PWM1SOCBEN Enable for ADCSOCBOn
#define SYSCTL_ADCSOCOUTSELECT_PWM2SOCBEN   0x20000U    // PWM2SOCBEN Enable for ADCSOCBOn
#define SYSCTL_ADCSOCOUTSELECT_PWM3SOCBEN   0x40000U    // PWM3SOCBEN Enable for ADCSOCBOn
#define SYSCTL_ADCSOCOUTSELECT_PWM4SOCBEN   0x80000U    // PWM4SOCBEN Enable for ADCSOCBOn
#define SYSCTL_ADCSOCOUTSELECT_PWM5SOCBEN   0x100000U   // PWM5SOCBEN Enable for ADCSOCBOn
#define SYSCTL_ADCSOCOUTSELECT_PWM6SOCBEN   0x200000U   // PWM6SOCBEN Enable for ADCSOCBOn
#define SYSCTL_ADCSOCOUTSELECT_PWM7SOCBEN   0x400000U   // PWM7SOCBEN Enable for ADCSOCBOn

//*************************************************************************************************
//
// The following are defines for the bit fields in the SYNCSOCLOCK register
//
//*************************************************************************************************
#define SYSCTL_SYNCSOCLOCK_SYNCSELECT        0x1U   // SYNCSEL Register Lock bit
#define SYSCTL_SYNCSOCLOCK_ADCSOCOUTSELECT   0x2U   // ADCSOCOUTSELECT Register Lock bit


//*************************************************************************************************
//
// The following are defines for the bit fields in the SYS_ERR_INT_FLG register
//
//*************************************************************************************************
#define SYSCTL_SYS_ERR_INT_FLG_GINT              0x1U       // Global Interrupt flag
#define SYSCTL_SYS_ERR_INT_FLG_CORRECTABLE_ERR   0x4U       // RAM/Flash correctable error flag
#define SYSCTL_SYS_ERR_INT_FLG_RAM_ACC_VIOL      0x10U      // A RAM access vioation flag.
#define SYSCTL_SYS_ERR_INT_FLG_EPG1_INT          0x800U     // EPG1_INT Interrupt flag.
#define SYSCTL_SYS_ERR_INT_FLG_FPU_UFLOW         0x10000U   // FPU_UFLOW Interrupt flag.
#define SYSCTL_SYS_ERR_INT_FLG_FPU_OFLOW         0x20000U   // FPU_OFLOW Interrupt flag.

//*************************************************************************************************
//
// The following are defines for the bit fields in the SYS_ERR_INT_CLR register
//
//*************************************************************************************************
#define SYSCTL_SYS_ERR_INT_CLR_GINT              0x1U       // Global Interrupt flag Clear bit
#define SYSCTL_SYS_ERR_INT_CLR_CORRECTABLE_ERR   0x4U       // CORRECTABLE_ERR interrupt flag clear
                                                            // bit
#define SYSCTL_SYS_ERR_INT_CLR_RAM_ACC_VIOL      0x10U      // RAM_ACC_VIOL interrupt flag clear
                                                            // bit
#define SYSCTL_SYS_ERR_INT_CLR_EPG1_INT          0x800U     // EPG1_INT interrupt flag clear bit
#define SYSCTL_SYS_ERR_INT_CLR_FPU_UFLOW         0x10000U   // FPU_UFLOW interrupt flag clear bit
#define SYSCTL_SYS_ERR_INT_CLR_FPU_OFLOW         0x20000U   // FPU_OFLOW interrupt flag clear bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SYS_ERR_INT_SET register
//
//*************************************************************************************************
#define SYSCTL_SYS_ERR_INT_SET_CORRECTABLE_ERR   0x4U          // CORRECTABLE_ERR interrupt flag
                                                               // set bit
#define SYSCTL_SYS_ERR_INT_SET_RAM_ACC_VIOL      0x10U         // RAM_ACC_VIOL interrupt flag set
                                                               // bit
#define SYSCTL_SYS_ERR_INT_SET_EPG1_INT          0x800U        // EPG1_INT interrupt flag set bit
#define SYSCTL_SYS_ERR_INT_SET_FPU_UFLOW         0x10000U      // FPU_UFLOW interrupt flag set bit
#define SYSCTL_SYS_ERR_INT_SET_FPU_OFLOW         0x20000U      // FPU_OFLOW interrupt flag set bit
#define SYSCTL_SYS_ERR_INT_SET_KEY_S             24U
#define SYSCTL_SYS_ERR_INT_SET_KEY_M             0xFF000000U   // KEY field

//*************************************************************************************************
//
// The following are defines for the bit fields in the SYS_ERR_MASK register
//
//*************************************************************************************************
#define SYSCTL_SYS_ERR_MASK_CORRECTABLE_ERR   0x4U          // CORRECTABLE_ERR flag mask bit
#define SYSCTL_SYS_ERR_MASK_RAM_ACC_VIOL      0x10U         // RAM_ACC_VIOL flag mask bit
#define SYSCTL_SYS_ERR_MASK_EPG1_INT          0x800U        // EPG1_INT flag mask bit
#define SYSCTL_SYS_ERR_MASK_FPU_UFLOW         0x10000U      // FPU_UFLOW flag mask bit
#define SYSCTL_SYS_ERR_MASK_FPU_OFLOW         0x20000U      // FPU_OFLOW flag mask bit
#define SYSCTL_SYS_ERR_MASK_KEY_S             24U
#define SYSCTL_SYS_ERR_MASK_KEY_M             0xFF000000U   // KEY field



#endif
