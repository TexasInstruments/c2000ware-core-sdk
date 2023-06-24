//###########################################################################
//
// FILE:    hw_sysctl.h
//
// TITLE:   Definitions for the SYSCTL registers.
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

#ifndef HW_SYSCTL_H
#define HW_SYSCTL_H

//*************************************************************************************************
//
// The following are defines for the SYSCTL register offsets
//
//*************************************************************************************************
#define SYSCTL_O_DEVCFGLOCK1   0x0U     // Lock bit for CPUSELx registers
#define SYSCTL_O_PARTIDL       0x8U     // Lower 32-bit of Device PART Identification Number
#define SYSCTL_O_PARTIDH       0xAU     // Upper 32-bit of Device PART Identification Number
#define SYSCTL_O_REVID         0xCU     // Device Revision Number
#define SYSCTL_O_DC0           0x10U    // Device Capability: Device Information
#define SYSCTL_O_DC1           0x12U    // Device Capability: Processing Block Customization
#define SYSCTL_O_DC2           0x14U    // Device Capability: EMIF Customization
#define SYSCTL_O_DC3           0x16U    // Device Capability: Peripheral Customization
#define SYSCTL_O_DC4           0x18U    // Device Capability: Peripheral Customization
#define SYSCTL_O_DC5           0x1AU    // Device Capability: Peripheral Customization
#define SYSCTL_O_DC6           0x1CU    // Device Capability: Peripheral Customization
#define SYSCTL_O_DC7           0x1EU    // Device Capability: Peripheral Customization
#define SYSCTL_O_DC8           0x20U    // Device Capability: Peripheral Customization
#define SYSCTL_O_DC9           0x22U    // Device Capability: Peripheral Customization
#define SYSCTL_O_DC10          0x24U    // Device Capability: Peripheral Customization
#define SYSCTL_O_DC11          0x26U    // Device Capability: Peripheral Customization
#define SYSCTL_O_DC12          0x28U    // Device Capability: Peripheral Customization
#define SYSCTL_O_DC13          0x2AU    // Device Capability: Peripheral Customization
#define SYSCTL_O_DC14          0x2CU    // Device Capability: Analog Modules Customization
#define SYSCTL_O_DC15          0x2EU    // Device Capability: Analog Modules Customization
#define SYSCTL_O_DC17          0x32U    // Device Capability: Analog Modules Customization
#define SYSCTL_O_DC18          0x34U    // Device Capability: CPU1 Lx SRAM Customization
#define SYSCTL_O_DC19          0x36U    // Device Capability: CPU2 Lx SRAM Customization
#define SYSCTL_O_DC20          0x38U    // Device Capability: GSx SRAM Customization
#define SYSCTL_O_PERCNF1       0x60U    // Peripheral Configuration register
#define SYSCTL_O_FUSEERR       0x74U    // e-Fuse error Status register
#define SYSCTL_O_SOFTPRES0     0x82U    // Processing Block Software Reset register
#define SYSCTL_O_SOFTPRES1     0x84U    // EMIF Software Reset register
#define SYSCTL_O_SOFTPRES2     0x86U    // Peripheral Software Reset register
#define SYSCTL_O_SOFTPRES3     0x88U    // Peripheral Software Reset register
#define SYSCTL_O_SOFTPRES4     0x8AU    // Peripheral Software Reset register
#define SYSCTL_O_SOFTPRES6     0x8EU    // Peripheral Software Reset register
#define SYSCTL_O_SOFTPRES7     0x90U    // Peripheral Software Reset register
#define SYSCTL_O_SOFTPRES8     0x92U    // Peripheral Software Reset register
#define SYSCTL_O_SOFTPRES9     0x94U    // Peripheral Software Reset register
#define SYSCTL_O_SOFTPRES11    0x98U    // Peripheral Software Reset register
#define SYSCTL_O_SOFTPRES13    0x9CU    // Peripheral Software Reset register
#define SYSCTL_O_SOFTPRES14    0x9EU    // Peripheral Software Reset register
#define SYSCTL_O_SOFTPRES16    0xA2U    // Peripheral Software Reset register
#define SYSCTL_O_CPUSEL0       0xD6U    // CPU Select register for common peripherals
#define SYSCTL_O_CPUSEL1       0xD8U    // CPU Select register for common peripherals
#define SYSCTL_O_CPUSEL2       0xDAU    // CPU Select register for common peripherals
#define SYSCTL_O_CPUSEL4       0xDEU    // CPU Select register for common peripherals
#define SYSCTL_O_CPUSEL5       0xE0U    // CPU Select register for common peripherals
#define SYSCTL_O_CPUSEL6       0xE2U    // CPU Select register for common peripherals
#define SYSCTL_O_CPUSEL7       0xE4U    // CPU Select register for common peripherals
#define SYSCTL_O_CPUSEL8       0xE6U    // CPU Select register for common peripherals
#define SYSCTL_O_CPUSEL9       0xE8U    // CPU Select register for common peripherals
#define SYSCTL_O_CPUSEL11      0xECU    // CPU Select register for common peripherals
#define SYSCTL_O_CPUSEL12      0xEEU    // CPU Select register for common peripherals
#define SYSCTL_O_CPUSEL14      0xF2U    // CPU Select register for common peripherals
#define SYSCTL_O_CPU2RESCTL    0x122U   // CPU2 Reset Control Register
#define SYSCTL_O_RSTSTAT       0x124U   // Reset Status register for secondary C28x CPUs
#define SYSCTL_O_LPMSTAT       0x125U   // LPM Status Register for secondary C28x CPUs
#define SYSCTL_O_SYSDBGCTL     0x12CU   // System Debug Control register

#define SYSCTL_O_CLKSEM          0x0U    // Clock Control Semaphore Register
#define SYSCTL_O_CLKCFGLOCK1     0x2U    // Lock bit for CLKCFG registers
#define SYSCTL_O_CLKSRCCTL1      0x8U    // Clock Source Control register-1
#define SYSCTL_O_CLKSRCCTL2      0xAU    // Clock Source Control register-2
#define SYSCTL_O_CLKSRCCTL3      0xCU    // Clock Source Control register-3
#define SYSCTL_O_SYSPLLCTL1      0xEU    // SYSPLL Control register-1
#define SYSCTL_O_SYSPLLMULT      0x14U   // SYSPLL Multiplier register
#define SYSCTL_O_SYSPLLSTS       0x16U   // SYSPLL Status register
#define SYSCTL_O_AUXPLLCTL1      0x18U   // AUXPLL Control register-1
#define SYSCTL_O_AUXPLLMULT      0x1EU   // AUXPLL Multiplier register
#define SYSCTL_O_AUXPLLSTS       0x20U   // AUXPLL Status register
#define SYSCTL_O_SYSCLKDIVSEL    0x22U   // System Clock Divider Select register
#define SYSCTL_O_AUXCLKDIVSEL    0x24U   // Auxillary Clock Divider Select register
#define SYSCTL_O_PERCLKDIVSEL    0x26U   // Peripheral Clock Divider Selet register
#define SYSCTL_O_XCLKOUTDIVSEL   0x28U   // XCLKOUT Divider Select register
#define SYSCTL_O_LOSPCP          0x2CU   // Low Speed Clock Source Prescalar
#define SYSCTL_O_MCDCR           0x2EU   // Missing Clock Detect Control Register
#define SYSCTL_O_X1CNT           0x30U   // 10-bit Counter on X1 Clock

#define SYSCTL_O_CPUSYSLOCK1     0x0U    // Lock bit for CPUSYS registers
#define SYSCTL_O_HIBBOOTMODE     0x6U    // HIB Boot Mode Register
#define SYSCTL_O_IORESTOREADDR   0x8U    // IORestore() routine Address Register
#define SYSCTL_O_PIEVERRADDR     0xAU    // PIE Vector Fetch Error Address register
#define SYSCTL_O_PCLKCR0         0x22U   // Peripheral Clock Gating Registers
#define SYSCTL_O_PCLKCR1         0x24U   // Peripheral Clock Gating Registers
#define SYSCTL_O_PCLKCR2         0x26U   // Peripheral Clock Gating Registers
#define SYSCTL_O_PCLKCR3         0x28U   // Peripheral Clock Gating Registers
#define SYSCTL_O_PCLKCR4         0x2AU   // Peripheral Clock Gating Registers
#define SYSCTL_O_PCLKCR6         0x2EU   // Peripheral Clock Gating Registers
#define SYSCTL_O_PCLKCR7         0x30U   // Peripheral Clock Gating Registers
#define SYSCTL_O_PCLKCR8         0x32U   // Peripheral Clock Gating Registers
#define SYSCTL_O_PCLKCR9         0x34U   // Peripheral Clock Gating Registers
#define SYSCTL_O_PCLKCR10        0x36U   // Peripheral Clock Gating Registers
#define SYSCTL_O_PCLKCR11        0x38U   // Peripheral Clock Gating Registers
#define SYSCTL_O_PCLKCR12        0x3AU   // Peripheral Clock Gating Registers
#define SYSCTL_O_PCLKCR13        0x3CU   // Peripheral Clock Gating Registers
#define SYSCTL_O_PCLKCR14        0x3EU   // Peripheral Clock Gating Registers
#define SYSCTL_O_PCLKCR16        0x42U   // Peripheral Clock Gating Registers
#define SYSCTL_O_SECMSEL         0x74U   // Secondary Master Select register for common
                                         // peripherals: Selects between CLA & DMA
#define SYSCTL_O_LPMCR           0x76U   // LPM Control Register
#define SYSCTL_O_GPIOLPMSEL0     0x78U   // GPIO LPM Wakeup select registers
#define SYSCTL_O_GPIOLPMSEL1     0x7AU   // GPIO LPM Wakeup select registers
#define SYSCTL_O_TMR2CLKCTL      0x7CU   // Timer2 Clock Measurement functionality control register
#define SYSCTL_O_RESC            0x80U   // Reset Cause register

#define SYSCTL_O_SCSR     0x22U   // System Control & Status Register
#define SYSCTL_O_WDCNTR   0x23U   // Watchdog Counter Register
#define SYSCTL_O_WDKEY    0x25U   // Watchdog Reset Key Register
#define SYSCTL_O_WDCR     0x29U   // Watchdog Control Register
#define SYSCTL_O_WDWCR    0x2AU   // Watchdog Windowed Control Register

#define SYSCTL_O_CLA1TASKSRCSELLOCK   0x0U    // CLA1 Task Trigger Source Select Lock Register
#define SYSCTL_O_DMACHSRCSELLOCK      0x4U    // DMA Channel Triger Source Select Lock Register
#define SYSCTL_O_CLA1TASKSRCSEL1      0x6U    // CLA1 Task Trigger Source Select Register-1
#define SYSCTL_O_CLA1TASKSRCSEL2      0x8U    // CLA1 Task Trigger Source Select Register-2
#define SYSCTL_O_DMACHSRCSEL1         0x16U   // DMA Channel Trigger Source Select Register-1
#define SYSCTL_O_DMACHSRCSEL2         0x18U   // DMA Channel Trigger Source Select Register-2

#define SYSCTL_O_SYNCSELECT        0x0U   // Sync Input and Output Select Register
#define SYSCTL_O_ADCSOCOUTSELECT   0x2U   // External ADC (Off Chip) SOC Select Register
#define SYSCTL_O_SYNCSOCLOCK       0x4U   // SYNCSEL and EXTADCSOC Select Lock register


//*************************************************************************************************
//
// The following are defines for the bit fields in the DEVCFGLOCK1 register
//
//*************************************************************************************************
#define SYSCTL_DEVCFGLOCK1_CPUSEL0    0x1U      // Lock bit for CPUSEL0 register
#define SYSCTL_DEVCFGLOCK1_CPUSEL1    0x2U      // Lock bit for CPUSEL1 register
#define SYSCTL_DEVCFGLOCK1_CPUSEL2    0x4U      // Lock bit for CPUSEL2 register
#define SYSCTL_DEVCFGLOCK1_CPUSEL3    0x8U      // Lock bit for CPUSEL3 register
#define SYSCTL_DEVCFGLOCK1_CPUSEL4    0x10U     // Lock bit for CPUSEL4 register
#define SYSCTL_DEVCFGLOCK1_CPUSEL5    0x20U     // Lock bit for CPUSEL5 register
#define SYSCTL_DEVCFGLOCK1_CPUSEL6    0x40U     // Lock bit for CPUSEL6 register
#define SYSCTL_DEVCFGLOCK1_CPUSEL7    0x80U     // Lock bit for CPUSEL7 register
#define SYSCTL_DEVCFGLOCK1_CPUSEL8    0x100U    // Lock bit for CPUSEL8 register
#define SYSCTL_DEVCFGLOCK1_CPUSEL9    0x200U    // Lock bit for CPUSEL9 register
#define SYSCTL_DEVCFGLOCK1_CPUSEL10   0x400U    // Lock bit for CPUSEL10 register
#define SYSCTL_DEVCFGLOCK1_CPUSEL11   0x800U    // Lock bit for CPUSEL11 register
#define SYSCTL_DEVCFGLOCK1_CPUSEL12   0x1000U   // Lock bit for CPUSEL12 register
#define SYSCTL_DEVCFGLOCK1_CPUSEL13   0x2000U   // Lock bit for CPUSEL13 register
#define SYSCTL_DEVCFGLOCK1_CPUSEL14   0x4000U   // Lock bit for CPUSEL14 register

//*************************************************************************************************
//
// The following are defines for the bit fields in the PARTIDL register
//
//*************************************************************************************************
#define SYSCTL_PARTIDL_QUAL_S                     6U
#define SYSCTL_PARTIDL_QUAL_M                     0xC0U         // Qualification Status
#define SYSCTL_PARTIDL_PIN_COUNT_S                8U
#define SYSCTL_PARTIDL_PIN_COUNT_M                0x700U        // Device Pin Count
#define SYSCTL_PARTIDL_INSTASPIN_S                13U
#define SYSCTL_PARTIDL_INSTASPIN_M                0x6000U       // Motorware feature set
#define SYSCTL_PARTIDL_FLASH_SIZE_S               16U
#define SYSCTL_PARTIDL_FLASH_SIZE_M               0xFF0000U     // Flash size in KB
#define SYSCTL_PARTIDL_PARTID_FORMAT_REVISION_S   28U
#define SYSCTL_PARTIDL_PARTID_FORMAT_REVISION_M   0xF0000000U   // Revision of the PARTID format

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
// The following are defines for the bit fields in the DC0 register
//
//*************************************************************************************************
#define SYSCTL_DC0_SINGLE_CORE   0x1U   // Single Core vs Dual Core

//*************************************************************************************************
//
// The following are defines for the bit fields in the DC1 register
//
//*************************************************************************************************
#define SYSCTL_DC1_CPU1_FPU_TMU   0x1U     // CPU1's FPU1+TMU1
#define SYSCTL_DC1_CPU2_FPU_TMU   0x2U     // CPU2's FPU2+TMU2
#define SYSCTL_DC1_CPU1_VCU       0x4U     // CPU1's VCU
#define SYSCTL_DC1_CPU2_VCU       0x8U     // CPU2's VCU
#define SYSCTL_DC1_CPU1_CLA1      0x40U    // CPU1.CLA1
#define SYSCTL_DC1_CPU2_CLA1      0x100U   // CPU2.CLA1

//*************************************************************************************************
//
// The following are defines for the bit fields in the DC2 register
//
//*************************************************************************************************
#define SYSCTL_DC2_EMIF1   0x1U   // EMIF1
#define SYSCTL_DC2_EMIF2   0x2U   // EMIF2

//*************************************************************************************************
//
// The following are defines for the bit fields in the DC3 register
//
//*************************************************************************************************
#define SYSCTL_DC3_EPWM1    0x1U     // EPWM1
#define SYSCTL_DC3_EPWM2    0x2U     // EPWM2
#define SYSCTL_DC3_EPWM3    0x4U     // EPWM3
#define SYSCTL_DC3_EPWM4    0x8U     // EPWM4
#define SYSCTL_DC3_EPWM5    0x10U    // EPWM5
#define SYSCTL_DC3_EPWM6    0x20U    // EPWM6
#define SYSCTL_DC3_EPWM7    0x40U    // EPWM7
#define SYSCTL_DC3_EPWM8    0x80U    // EPWM8
#define SYSCTL_DC3_EPWM9    0x100U   // EPWM9
#define SYSCTL_DC3_EPWM10   0x200U   // EPWM10
#define SYSCTL_DC3_EPWM11   0x400U   // EPWM11
#define SYSCTL_DC3_EPWM12   0x800U   // EPWM12

//*************************************************************************************************
//
// The following are defines for the bit fields in the DC4 register
//
//*************************************************************************************************
#define SYSCTL_DC4_ECAP1   0x1U    // ECAP1
#define SYSCTL_DC4_ECAP2   0x2U    // ECAP2
#define SYSCTL_DC4_ECAP3   0x4U    // ECAP3
#define SYSCTL_DC4_ECAP4   0x8U    // ECAP4
#define SYSCTL_DC4_ECAP5   0x10U   // ECAP5
#define SYSCTL_DC4_ECAP6   0x20U   // ECAP6

//*************************************************************************************************
//
// The following are defines for the bit fields in the DC5 register
//
//*************************************************************************************************
#define SYSCTL_DC5_EQEP1   0x1U   // EQEP1
#define SYSCTL_DC5_EQEP2   0x2U   // EQEP2
#define SYSCTL_DC5_EQEP3   0x4U   // EQEP3

//*************************************************************************************************
//
// The following are defines for the bit fields in the DC6 register
//
//*************************************************************************************************
#define SYSCTL_DC6_CLB1   0x1U   // CLB1
#define SYSCTL_DC6_CLB2   0x2U   // CLB2
#define SYSCTL_DC6_CLB3   0x4U   // CLB3
#define SYSCTL_DC6_CLB4   0x8U   // CLB4

//*************************************************************************************************
//
// The following are defines for the bit fields in the DC7 register
//
//*************************************************************************************************
#define SYSCTL_DC7_SD1   0x1U   // SD1
#define SYSCTL_DC7_SD2   0x2U   // SD2

//*************************************************************************************************
//
// The following are defines for the bit fields in the DC8 register
//
//*************************************************************************************************
#define SYSCTL_DC8_SCI_A   0x1U   // SCI_A
#define SYSCTL_DC8_SCI_B   0x2U   // SCI_B
#define SYSCTL_DC8_SCI_C   0x4U   // SCI_C
#define SYSCTL_DC8_SCI_D   0x8U   // SCI_D

//*************************************************************************************************
//
// The following are defines for the bit fields in the DC9 register
//
//*************************************************************************************************
#define SYSCTL_DC9_SPI_A   0x1U   // SPI_A
#define SYSCTL_DC9_SPI_B   0x2U   // SPI_B
#define SYSCTL_DC9_SPI_C   0x4U   // SPI_C

//*************************************************************************************************
//
// The following are defines for the bit fields in the DC10 register
//
//*************************************************************************************************
#define SYSCTL_DC10_I2C_A   0x1U   // I2C_A
#define SYSCTL_DC10_I2C_B   0x2U   // I2C_B

//*************************************************************************************************
//
// The following are defines for the bit fields in the DC11 register
//
//*************************************************************************************************
#define SYSCTL_DC11_CAN_A   0x1U   // CAN_A
#define SYSCTL_DC11_CAN_B   0x2U   // CAN_B

//*************************************************************************************************
//
// The following are defines for the bit fields in the DC12 register
//
//*************************************************************************************************
#define SYSCTL_DC12_MCBSP_A   0x1U       // McBSP_A
#define SYSCTL_DC12_MCBSP_B   0x2U       // McBSP_B
#define SYSCTL_DC12_USB_A_S   16U
#define SYSCTL_DC12_USB_A_M   0x30000U   // Decides the capability of the USB_A Module

//*************************************************************************************************
//
// The following are defines for the bit fields in the DC13 register
//
//*************************************************************************************************
#define SYSCTL_DC13_UPP_A   0x1U   // uPP_A

//*************************************************************************************************
//
// The following are defines for the bit fields in the DC14 register
//
//*************************************************************************************************
#define SYSCTL_DC14_ADC_A   0x1U   // ADC_A
#define SYSCTL_DC14_ADC_B   0x2U   // ADC_B
#define SYSCTL_DC14_ADC_C   0x4U   // ADC_C
#define SYSCTL_DC14_ADC_D   0x8U   // ADC_D

//*************************************************************************************************
//
// The following are defines for the bit fields in the DC15 register
//
//*************************************************************************************************
#define SYSCTL_DC15_CMPSS1   0x1U    // CMPSS1
#define SYSCTL_DC15_CMPSS2   0x2U    // CMPSS2
#define SYSCTL_DC15_CMPSS3   0x4U    // CMPSS3
#define SYSCTL_DC15_CMPSS4   0x8U    // CMPSS4
#define SYSCTL_DC15_CMPSS5   0x10U   // CMPSS5
#define SYSCTL_DC15_CMPSS6   0x20U   // CMPSS6
#define SYSCTL_DC15_CMPSS7   0x40U   // CMPSS7
#define SYSCTL_DC15_CMPSS8   0x80U   // CMPSS8

//*************************************************************************************************
//
// The following are defines for the bit fields in the DC17 register
//
//*************************************************************************************************
#define SYSCTL_DC17_DAC_A   0x10000U   // Buffered-DAC_A
#define SYSCTL_DC17_DAC_B   0x20000U   // Buffered-DAC_B
#define SYSCTL_DC17_DAC_C   0x40000U   // Buffered-DAC_C

//*************************************************************************************************
//
// The following are defines for the bit fields in the DC18 register
//
//*************************************************************************************************
#define SYSCTL_DC18_LS0_1   0x1U    // LS0_1
#define SYSCTL_DC18_LS1_1   0x2U    // LS1_1
#define SYSCTL_DC18_LS2_1   0x4U    // LS2_1
#define SYSCTL_DC18_LS3_1   0x8U    // LS3_1
#define SYSCTL_DC18_LS4_1   0x10U   // LS4_1
#define SYSCTL_DC18_LS5_1   0x20U   // LS5_1

//*************************************************************************************************
//
// The following are defines for the bit fields in the DC19 register
//
//*************************************************************************************************
#define SYSCTL_DC19_LS0_2   0x1U    // LS0_2
#define SYSCTL_DC19_LS1_2   0x2U    // LS1_2
#define SYSCTL_DC19_LS2_2   0x4U    // LS2_2
#define SYSCTL_DC19_LS3_2   0x8U    // LS3_2
#define SYSCTL_DC19_LS4_2   0x10U   // LS4_2
#define SYSCTL_DC19_LS5_2   0x20U   // LS5_2

//*************************************************************************************************
//
// The following are defines for the bit fields in the DC20 register
//
//*************************************************************************************************
#define SYSCTL_DC20_GS0    0x1U      // GS0
#define SYSCTL_DC20_GS1    0x2U      // GS1
#define SYSCTL_DC20_GS2    0x4U      // GS2
#define SYSCTL_DC20_GS3    0x8U      // GS3
#define SYSCTL_DC20_GS4    0x10U     // GS4
#define SYSCTL_DC20_GS5    0x20U     // GS5
#define SYSCTL_DC20_GS6    0x40U     // GS6
#define SYSCTL_DC20_GS7    0x80U     // GS7
#define SYSCTL_DC20_GS8    0x100U    // GS8
#define SYSCTL_DC20_GS9    0x200U    // GS9
#define SYSCTL_DC20_GS10   0x400U    // GS10
#define SYSCTL_DC20_GS11   0x800U    // GS11
#define SYSCTL_DC20_GS12   0x1000U   // GS12
#define SYSCTL_DC20_GS13   0x2000U   // GS13
#define SYSCTL_DC20_GS14   0x4000U   // GS14
#define SYSCTL_DC20_GS15   0x8000U   // GS15

//*************************************************************************************************
//
// The following are defines for the bit fields in the PERCNF1 register
//
//*************************************************************************************************
#define SYSCTL_PERCNF1_ADC_A_MODE   0x1U       // ADC_A mode setting bit
#define SYSCTL_PERCNF1_ADC_B_MODE   0x2U       // ADC_B mode setting bit
#define SYSCTL_PERCNF1_ADC_C_MODE   0x4U       // ADC_C mode setting bit
#define SYSCTL_PERCNF1_ADC_D_MODE   0x8U       // ADC_D mode setting bit
#define SYSCTL_PERCNF1_USB_A_PHY    0x10000U   // USB_A_PHY

//*************************************************************************************************
//
// The following are defines for the bit fields in the FUSEERR register
//
//*************************************************************************************************
#define SYSCTL_FUSEERR_ALERR_S   0U
#define SYSCTL_FUSEERR_ALERR_M   0x1FU   // Efuse Autoload Error Status
#define SYSCTL_FUSEERR_ERR       0x20U   // Efuse Self Test Error Status

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES0 register
//
//*************************************************************************************************
#define SYSCTL_SOFTPRES0_CPU1_CLA1   0x1U   // CPU1_CLA1 software reset bit
#define SYSCTL_SOFTPRES0_CPU2_CLA1   0x4U   // CPU2_CLA1 software reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES1 register
//
//*************************************************************************************************
#define SYSCTL_SOFTPRES1_EMIF1   0x1U   // EMIF1 software reset bit
#define SYSCTL_SOFTPRES1_EMIF2   0x2U   // EMIF2 software reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES2 register
//
//*************************************************************************************************
#define SYSCTL_SOFTPRES2_EPWM1    0x1U     // EPWM1 software reset bit
#define SYSCTL_SOFTPRES2_EPWM2    0x2U     // EPWM2 software reset bit
#define SYSCTL_SOFTPRES2_EPWM3    0x4U     // EPWM3 software reset bit
#define SYSCTL_SOFTPRES2_EPWM4    0x8U     // EPWM4 software reset bit
#define SYSCTL_SOFTPRES2_EPWM5    0x10U    // EPWM5 software reset bit
#define SYSCTL_SOFTPRES2_EPWM6    0x20U    // EPWM6 software reset bit
#define SYSCTL_SOFTPRES2_EPWM7    0x40U    // EPWM7 software reset bit
#define SYSCTL_SOFTPRES2_EPWM8    0x80U    // EPWM8 software reset bit
#define SYSCTL_SOFTPRES2_EPWM9    0x100U   // EPWM9 software reset bit
#define SYSCTL_SOFTPRES2_EPWM10   0x200U   // EPWM10 software reset bit
#define SYSCTL_SOFTPRES2_EPWM11   0x400U   // EPWM11 software reset bit
#define SYSCTL_SOFTPRES2_EPWM12   0x800U   // EPWM12 software reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES3 register
//
//*************************************************************************************************
#define SYSCTL_SOFTPRES3_ECAP1   0x1U    // ECAP1 software reset bit
#define SYSCTL_SOFTPRES3_ECAP2   0x2U    // ECAP2 software reset bit
#define SYSCTL_SOFTPRES3_ECAP3   0x4U    // ECAP3 software reset bit
#define SYSCTL_SOFTPRES3_ECAP4   0x8U    // ECAP4 software reset bit
#define SYSCTL_SOFTPRES3_ECAP5   0x10U   // ECAP5 software reset bit
#define SYSCTL_SOFTPRES3_ECAP6   0x20U   // ECAP6 software reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES4 register
//
//*************************************************************************************************
#define SYSCTL_SOFTPRES4_EQEP1   0x1U   // EQEP1 software reset bit
#define SYSCTL_SOFTPRES4_EQEP2   0x2U   // EQEP2 software reset bit
#define SYSCTL_SOFTPRES4_EQEP3   0x4U   // EQEP3 software reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES6 register
//
//*************************************************************************************************
#define SYSCTL_SOFTPRES6_SD1   0x1U   // SD1 software reset bit
#define SYSCTL_SOFTPRES6_SD2   0x2U   // SD2 software reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES7 register
//
//*************************************************************************************************
#define SYSCTL_SOFTPRES7_SCI_A   0x1U   // SCI_A software reset bit
#define SYSCTL_SOFTPRES7_SCI_B   0x2U   // SCI_B software reset bit
#define SYSCTL_SOFTPRES7_SCI_C   0x4U   // SCI_C software reset bit
#define SYSCTL_SOFTPRES7_SCI_D   0x8U   // SCI_D software reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES8 register
//
//*************************************************************************************************
#define SYSCTL_SOFTPRES8_SPI_A   0x1U   // SPI_A software reset bit
#define SYSCTL_SOFTPRES8_SPI_B   0x2U   // SPI_B software reset bit
#define SYSCTL_SOFTPRES8_SPI_C   0x4U   // SPI_C software reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES9 register
//
//*************************************************************************************************
#define SYSCTL_SOFTPRES9_I2C_A   0x1U   // I2C_A software reset bit
#define SYSCTL_SOFTPRES9_I2C_B   0x2U   // I2C_B software reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES11 register
//
//*************************************************************************************************
#define SYSCTL_SOFTPRES11_MCBSP_A   0x1U       // McBSP_A software reset bit
#define SYSCTL_SOFTPRES11_MCBSP_B   0x2U       // McBSP_B software reset bit
#define SYSCTL_SOFTPRES11_USB_A     0x10000U   // USB_A software reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES13 register
//
//*************************************************************************************************
#define SYSCTL_SOFTPRES13_ADC_A   0x1U   // ADC_A software reset bit
#define SYSCTL_SOFTPRES13_ADC_B   0x2U   // ADC_B software reset bit
#define SYSCTL_SOFTPRES13_ADC_C   0x4U   // ADC_C software reset bit
#define SYSCTL_SOFTPRES13_ADC_D   0x8U   // ADC_D software reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES14 register
//
//*************************************************************************************************
#define SYSCTL_SOFTPRES14_CMPSS1   0x1U    // CMPSS1 software reset bit
#define SYSCTL_SOFTPRES14_CMPSS2   0x2U    // CMPSS2 software reset bit
#define SYSCTL_SOFTPRES14_CMPSS3   0x4U    // CMPSS3 software reset bit
#define SYSCTL_SOFTPRES14_CMPSS4   0x8U    // CMPSS4 software reset bit
#define SYSCTL_SOFTPRES14_CMPSS5   0x10U   // CMPSS5 software reset bit
#define SYSCTL_SOFTPRES14_CMPSS6   0x20U   // CMPSS6 software reset bit
#define SYSCTL_SOFTPRES14_CMPSS7   0x40U   // CMPSS7 software reset bit
#define SYSCTL_SOFTPRES14_CMPSS8   0x80U   // CMPSS8 software reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES16 register
//
//*************************************************************************************************
#define SYSCTL_SOFTPRES16_DAC_A   0x10000U   // Buffered_DAC_A software reset bit
#define SYSCTL_SOFTPRES16_DAC_B   0x20000U   // Buffered_DAC_B software reset bit
#define SYSCTL_SOFTPRES16_DAC_C   0x40000U   // Buffered_DAC_C software reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the CPUSEL0 register
//
//*************************************************************************************************
#define SYSCTL_CPUSEL0_EPWM1    0x1U     // EPWM1 CPU select bit
#define SYSCTL_CPUSEL0_EPWM2    0x2U     // EPWM2 CPU select bit
#define SYSCTL_CPUSEL0_EPWM3    0x4U     // EPWM3 CPU select bit
#define SYSCTL_CPUSEL0_EPWM4    0x8U     // EPWM4 CPU select bit
#define SYSCTL_CPUSEL0_EPWM5    0x10U    // EPWM5 CPU select bit
#define SYSCTL_CPUSEL0_EPWM6    0x20U    // EPWM6 CPU select bit
#define SYSCTL_CPUSEL0_EPWM7    0x40U    // EPWM7 CPU select bit
#define SYSCTL_CPUSEL0_EPWM8    0x80U    // EPWM8 CPU select bit
#define SYSCTL_CPUSEL0_EPWM9    0x100U   // EPWM9 CPU select bit
#define SYSCTL_CPUSEL0_EPWM10   0x200U   // EPWM10 CPU select bit
#define SYSCTL_CPUSEL0_EPWM11   0x400U   // EPWM11 CPU select bit
#define SYSCTL_CPUSEL0_EPWM12   0x800U   // EPWM12 CPU select bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the CPUSEL1 register
//
//*************************************************************************************************
#define SYSCTL_CPUSEL1_ECAP1   0x1U    // ECAP1 CPU select bit
#define SYSCTL_CPUSEL1_ECAP2   0x2U    // ECAP2 CPU select bit
#define SYSCTL_CPUSEL1_ECAP3   0x4U    // ECAP3 CPU select bit
#define SYSCTL_CPUSEL1_ECAP4   0x8U    // ECAP4 CPU select bit
#define SYSCTL_CPUSEL1_ECAP5   0x10U   // ECAP5 CPU select bit
#define SYSCTL_CPUSEL1_ECAP6   0x20U   // ECAP6 CPU select bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the CPUSEL2 register
//
//*************************************************************************************************
#define SYSCTL_CPUSEL2_EQEP1   0x1U   // EQEP1 CPU select bit
#define SYSCTL_CPUSEL2_EQEP2   0x2U   // EQEP2 CPU select bit
#define SYSCTL_CPUSEL2_EQEP3   0x4U   // EQEP3 CPU select bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the CPUSEL4 register
//
//*************************************************************************************************
#define SYSCTL_CPUSEL4_SD1   0x1U   // SD1 CPU select bit
#define SYSCTL_CPUSEL4_SD2   0x2U   // SD2 CPU select bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the CPUSEL5 register
//
//*************************************************************************************************
#define SYSCTL_CPUSEL5_SCI_A   0x1U   // SCI_A CPU select bit
#define SYSCTL_CPUSEL5_SCI_B   0x2U   // SCI_B CPU select bit
#define SYSCTL_CPUSEL5_SCI_C   0x4U   // SCI_C CPU select bit
#define SYSCTL_CPUSEL5_SCI_D   0x8U   // SCI_D CPU select bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the CPUSEL6 register
//
//*************************************************************************************************
#define SYSCTL_CPUSEL6_SPI_A   0x1U   // SPI_A CPU select bit
#define SYSCTL_CPUSEL6_SPI_B   0x2U   // SPI_B CPU select bit
#define SYSCTL_CPUSEL6_SPI_C   0x4U   // SPI_C CPU select bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the CPUSEL7 register
//
//*************************************************************************************************
#define SYSCTL_CPUSEL7_I2C_A   0x1U   // I2C_A CPU select bit
#define SYSCTL_CPUSEL7_I2C_B   0x2U   // I2C_B CPU select bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the CPUSEL8 register
//
//*************************************************************************************************
#define SYSCTL_CPUSEL8_CAN_A   0x1U   // CAN_A CPU select bit
#define SYSCTL_CPUSEL8_CAN_B   0x2U   // CAN_B CPU select bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the CPUSEL9 register
//
//*************************************************************************************************
#define SYSCTL_CPUSEL9_MCBSP_A   0x1U   // McBSP_A CPU select bit
#define SYSCTL_CPUSEL9_MCBSP_B   0x2U   // McBSP_B CPU select bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the CPUSEL11 register
//
//*************************************************************************************************
#define SYSCTL_CPUSEL11_ADC_A   0x1U   // ADC_A CPU select bit
#define SYSCTL_CPUSEL11_ADC_B   0x2U   // ADC_B CPU select bit
#define SYSCTL_CPUSEL11_ADC_C   0x4U   // ADC_C CPU select bit
#define SYSCTL_CPUSEL11_ADC_D   0x8U   // ADC_D CPU select bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the CPUSEL12 register
//
//*************************************************************************************************
#define SYSCTL_CPUSEL12_CMPSS1   0x1U    // CMPSS1 CPU select bit
#define SYSCTL_CPUSEL12_CMPSS2   0x2U    // CMPSS2 CPU select bit
#define SYSCTL_CPUSEL12_CMPSS3   0x4U    // CMPSS3 CPU select bit
#define SYSCTL_CPUSEL12_CMPSS4   0x8U    // CMPSS4 CPU select bit
#define SYSCTL_CPUSEL12_CMPSS5   0x10U   // CMPSS5 CPU select bit
#define SYSCTL_CPUSEL12_CMPSS6   0x20U   // CMPSS6 CPU select bit
#define SYSCTL_CPUSEL12_CMPSS7   0x40U   // CMPSS7 CPU select bit
#define SYSCTL_CPUSEL12_CMPSS8   0x80U   // CMPSS8 CPU select bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the CPUSEL14 register
//
//*************************************************************************************************
#define SYSCTL_CPUSEL14_DAC_A   0x10000U   // Buffered_DAC_A CPU select bit
#define SYSCTL_CPUSEL14_DAC_B   0x20000U   // Buffered_DAC_B CPU select bit
#define SYSCTL_CPUSEL14_DAC_C   0x40000U   // Buffered_DAC_C CPU select bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the CPU2RESCTL register
//
//*************************************************************************************************
#define SYSCTL_CPU2RESCTL_RESET   0x1U          // CPU2 Reset Control bit
#define SYSCTL_CPU2RESCTL_KEY_S   16U
#define SYSCTL_CPU2RESCTL_KEY_M   0xFFFF0000U   // Key Qualifier for writes to this register

//*************************************************************************************************
//
// The following are defines for the bit fields in the RSTSTAT register
//
//*************************************************************************************************
#define SYSCTL_RSTSTAT_CPU2RES          0x1U   // CPU2 Reset Status bit
#define SYSCTL_RSTSTAT_CPU2NMIWDRST     0x2U   // Indicates whether a CPU2.NMIWD reset was issued
                                               // to CPU2
#define SYSCTL_RSTSTAT_CPU2HWBISTRST0   0x4U   // Indicates whether a HWBIST reset was issued to
                                               // CPU2
#define SYSCTL_RSTSTAT_CPU2HWBISTRST1   0x8U   // Indicates whether a HWBIST reset was issued to
                                               // CPU2

//*************************************************************************************************
//
// The following are defines for the bit fields in the LPMSTAT register
//
//*************************************************************************************************
#define SYSCTL_LPMSTAT_CPU2LPMSTAT_S   0U
#define SYSCTL_LPMSTAT_CPU2LPMSTAT_M   0x3U   // CPU2 LPM Status

//*************************************************************************************************
//
// The following are defines for the bit fields in the SYSDBGCTL register
//
//*************************************************************************************************
#define SYSCTL_SYSDBGCTL_BIT_0   0x1U   // Used in PLL startup. Only reset by POR.


//*************************************************************************************************
//
// The following are defines for the bit fields in the CLKSEM register
//
//*************************************************************************************************
#define SYSCTL_CLKSEM_SEM_S   0U
#define SYSCTL_CLKSEM_SEM_M   0x3U          // Semaphore for CLKCFG Ownership by CPU1 or CPU2
#define SYSCTL_CLKSEM_KEY_S   16U
#define SYSCTL_CLKSEM_KEY_M   0xFFFF0000U   // Key Qualifier for writes to this register

//*************************************************************************************************
//
// The following are defines for the bit fields in the CLKCFGLOCK1 register
//
//*************************************************************************************************
#define SYSCTL_CLKCFGLOCK1_CLKSRCCTL1     0x1U      // Lock bit for CLKSRCCTL1 register
#define SYSCTL_CLKCFGLOCK1_CLKSRCCTL2     0x2U      // Lock bit for CLKSRCCTL2 register
#define SYSCTL_CLKCFGLOCK1_CLKSRCCTL3     0x4U      // Lock bit for CLKSRCCTL3 register
#define SYSCTL_CLKCFGLOCK1_SYSPLLCTL1     0x8U      // Lock bit for SYSPLLCTL1 register
#define SYSCTL_CLKCFGLOCK1_SYSPLLCTL2     0x10U     // Lock bit for SYSPLLCTL2 register
#define SYSCTL_CLKCFGLOCK1_SYSPLLCTL3     0x20U     // Lock bit for SYSPLLCTL3 register
#define SYSCTL_CLKCFGLOCK1_SYSPLLMULT     0x40U     // Lock bit for SYSPLLMULT register
#define SYSCTL_CLKCFGLOCK1_AUXPLLCTL1     0x80U     // Lock bit for AUXPLLCTL1 register
#define SYSCTL_CLKCFGLOCK1_AUXPLLMULT     0x400U    // Lock bit for AUXPLLMULT register
#define SYSCTL_CLKCFGLOCK1_SYSCLKDIVSEL   0x800U    // Lock bit for SYSCLKDIVSEL register
#define SYSCTL_CLKCFGLOCK1_AUXCLKDIVSEL   0x1000U   // Lock bit for AUXCLKDIVSEL register
#define SYSCTL_CLKCFGLOCK1_PERCLKDIVSEL   0x2000U   // Lock bit for PERCLKDIVSEL register
#define SYSCTL_CLKCFGLOCK1_LOSPCP         0x8000U   // Lock bit for LOSPCP register

//*************************************************************************************************
//
// The following are defines for the bit fields in the CLKSRCCTL1 register
//
//*************************************************************************************************
#define SYSCTL_CLKSRCCTL1_OSCCLKSRCSEL_S   0U
#define SYSCTL_CLKSRCCTL1_OSCCLKSRCSEL_M   0x3U    // OSCCLK Source Select Bit
#define SYSCTL_CLKSRCCTL1_INTOSC2OFF       0x8U    // Internal Oscillator 2 Off Bit
#define SYSCTL_CLKSRCCTL1_XTALOFF          0x10U   // Crystal (External) Oscillator Off Bit
#define SYSCTL_CLKSRCCTL1_WDHALTI          0x20U   // Watchdog HALT Mode Ignore Bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the CLKSRCCTL2 register
//
//*************************************************************************************************
#define SYSCTL_CLKSRCCTL2_AUXOSCCLKSRCSEL_S   0U
#define SYSCTL_CLKSRCCTL2_AUXOSCCLKSRCSEL_M   0x3U    // AUXOSCCLK Source Select Bit
#define SYSCTL_CLKSRCCTL2_CANABCLKSEL_S       2U
#define SYSCTL_CLKSRCCTL2_CANABCLKSEL_M       0xCU    // CANA Bit Clock Source Select Bit
#define SYSCTL_CLKSRCCTL2_CANBBCLKSEL_S       4U
#define SYSCTL_CLKSRCCTL2_CANBBCLKSEL_M       0x30U   // CANB Bit Clock Source Select Bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the CLKSRCCTL3 register
//
//*************************************************************************************************
#define SYSCTL_CLKSRCCTL3_XCLKOUTSEL_S   0U
#define SYSCTL_CLKSRCCTL3_XCLKOUTSEL_M   0x7U   // XCLKOUT Source Select Bit

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
#define SYSCTL_SYSPLLMULT_IMULT_S   0U
#define SYSCTL_SYSPLLMULT_IMULT_M   0x7FU    // SYSPLL Integer Multiplier
#define SYSCTL_SYSPLLMULT_FMULT_S   8U
#define SYSCTL_SYSPLLMULT_FMULT_M   0x300U   // SYSPLL Fractional Multiplier

//*************************************************************************************************
//
// The following are defines for the bit fields in the SYSPLLSTS register
//
//*************************************************************************************************
#define SYSCTL_SYSPLLSTS_LOCKS   0x1U   // SYSPLL Lock Status Bit
#define SYSCTL_SYSPLLSTS_SLIPS   0x2U   // SYSPLL Slip Status Bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the AUXPLLCTL1 register
//
//*************************************************************************************************
#define SYSCTL_AUXPLLCTL1_PLLEN      0x1U   // AUXPLL enable/disable bit
#define SYSCTL_AUXPLLCTL1_PLLCLKEN   0x2U   // AUXPLL bypassed or included in the AUXPLLCLK path

//*************************************************************************************************
//
// The following are defines for the bit fields in the AUXPLLMULT register
//
//*************************************************************************************************
#define SYSCTL_AUXPLLMULT_IMULT_S   0U
#define SYSCTL_AUXPLLMULT_IMULT_M   0x7FU    // AUXPLL Integer Multiplier
#define SYSCTL_AUXPLLMULT_FMULT_S   8U
#define SYSCTL_AUXPLLMULT_FMULT_M   0x300U   // AUXPLL Fractional Multiplier

//*************************************************************************************************
//
// The following are defines for the bit fields in the AUXPLLSTS register
//
//*************************************************************************************************
#define SYSCTL_AUXPLLSTS_LOCKS   0x1U   // AUXPLL Lock Status Bit
#define SYSCTL_AUXPLLSTS_SLIPS   0x2U   // AUXPLL Slip Status Bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SYSCLKDIVSEL register
//
//*************************************************************************************************
#define SYSCTL_SYSCLKDIVSEL_PLLSYSCLKDIV_S   0U
#define SYSCTL_SYSCLKDIVSEL_PLLSYSCLKDIV_M   0x3FU   // PLLSYSCLK Divide Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the AUXCLKDIVSEL register
//
//*************************************************************************************************
#define SYSCTL_AUXCLKDIVSEL_AUXPLLDIV_S   0U
#define SYSCTL_AUXCLKDIVSEL_AUXPLLDIV_M   0x3U   // AUXPLLCLK Divide Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the PERCLKDIVSEL register
//
//*************************************************************************************************
#define SYSCTL_PERCLKDIVSEL_EPWMCLKDIV_S   0U
#define SYSCTL_PERCLKDIVSEL_EPWMCLKDIV_M   0x3U    // EPWM Clock Divide Select
#define SYSCTL_PERCLKDIVSEL_EMIF1CLKDIV    0x10U   // EMIF1  Clock Divide Select
#define SYSCTL_PERCLKDIVSEL_EMIF2CLKDIV    0x40U   // EMIF2 Clock Divide Select

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
#define SYSCTL_MCDCR_MCLKSTS   0x1U   // Missing Clock Status Bit
#define SYSCTL_MCDCR_MCLKCLR   0x2U   // Missing Clock Clear Bit
#define SYSCTL_MCDCR_MCLKOFF   0x4U   // Missing Clock Detect Off Bit
#define SYSCTL_MCDCR_OSCOFF    0x8U   // Oscillator Clock Off Bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the X1CNT register
//
//*************************************************************************************************
#define SYSCTL_X1CNT_X1CNT_S   0U
#define SYSCTL_X1CNT_X1CNT_M   0x3FFU   // X1 Counter


//*************************************************************************************************
//
// The following are defines for the bit fields in the CPUSYSLOCK1 register
//
//*************************************************************************************************
#define SYSCTL_CPUSYSLOCK1_HIBBOOTMODE     0x1U        // Lock bit for HIBBOOTMODE register
#define SYSCTL_CPUSYSLOCK1_IORESTOREADDR   0x2U        // Lock bit for IORESTOREADDR Register
#define SYSCTL_CPUSYSLOCK1_PIEVERRADDR     0x4U        // Lock bit for PIEVERRADDR Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR0         0x8U        // Lock bit for PCLKCR0 Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR1         0x10U       // Lock bit for PCLKCR1 Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR2         0x20U       // Lock bit for PCLKCR2 Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR3         0x40U       // Lock bit for PCLKCR3 Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR4         0x80U       // Lock bit for PCLKCR4 Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR5         0x100U      // Lock bit for PCLKCR5 Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR6         0x200U      // Lock bit for PCLKCR6 Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR7         0x400U      // Lock bit for PCLKCR7 Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR8         0x800U      // Lock bit for PCLKCR8 Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR9         0x1000U     // Lock bit for PCLKCR9 Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR10        0x2000U     // Lock bit for PCLKCR10 Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR11        0x4000U     // Lock bit for PCLKCR11 Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR12        0x8000U     // Lock bit for PCLKCR12 Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR13        0x10000U    // Lock bit for PCLKCR13 Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR14        0x20000U    // Lock bit for PCLKCR14 Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR15        0x40000U    // Lock bit for PCLKCR15 Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR16        0x80000U    // Lock bit for PCLKCR16 Register
#define SYSCTL_CPUSYSLOCK1_SECMSEL         0x100000U   // Lock bit for SECMSEL Register
#define SYSCTL_CPUSYSLOCK1_LPMCR           0x200000U   // Lock bit for LPMCR Register
#define SYSCTL_CPUSYSLOCK1_GPIOLPMSEL0     0x400000U   // Lock bit for GPIOLPMSEL0 Register
#define SYSCTL_CPUSYSLOCK1_GPIOLPMSEL1     0x800000U   // Lock bit for GPIOLPMSEL1 Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the IORESTOREADDR register
//
//*************************************************************************************************
#define SYSCTL_IORESTOREADDR_ADDR_S   0U
#define SYSCTL_IORESTOREADDR_ADDR_M   0x3FFFFFU   // restoreIO() routine address

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
#define SYSCTL_PCLKCR0_CLA1         0x1U       // CLA1 Clock Enable Bit
#define SYSCTL_PCLKCR0_DMA          0x4U       // DMA Clock Enable bit
#define SYSCTL_PCLKCR0_CPUTIMER0    0x8U       // CPUTIMER0 Clock Enable bit
#define SYSCTL_PCLKCR0_CPUTIMER1    0x10U      // CPUTIMER1 Clock Enable bit
#define SYSCTL_PCLKCR0_CPUTIMER2    0x20U      // CPUTIMER2 Clock Enable bit
#define SYSCTL_PCLKCR0_HRPWM        0x10000U   // HRPWM Clock Enable Bit
#define SYSCTL_PCLKCR0_TBCLKSYNC    0x40000U   // EPWM Time Base Clock sync
#define SYSCTL_PCLKCR0_GTBCLKSYNC   0x80000U   // EPWM Time Base Clock Global sync

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCLKCR1 register
//
//*************************************************************************************************
#define SYSCTL_PCLKCR1_EMIF1   0x1U   // EMIF1 Clock Enable bit
#define SYSCTL_PCLKCR1_EMIF2   0x2U   // EMIF2 Clock Enable bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCLKCR2 register
//
//*************************************************************************************************
#define SYSCTL_PCLKCR2_EPWM1    0x1U     // EPWM1 Clock Enable bit
#define SYSCTL_PCLKCR2_EPWM2    0x2U     // EPWM2 Clock Enable bit
#define SYSCTL_PCLKCR2_EPWM3    0x4U     // EPWM3 Clock Enable bit
#define SYSCTL_PCLKCR2_EPWM4    0x8U     // EPWM4 Clock Enable bit
#define SYSCTL_PCLKCR2_EPWM5    0x10U    // EPWM5 Clock Enable bit
#define SYSCTL_PCLKCR2_EPWM6    0x20U    // EPWM6 Clock Enable bit
#define SYSCTL_PCLKCR2_EPWM7    0x40U    // EPWM7 Clock Enable bit
#define SYSCTL_PCLKCR2_EPWM8    0x80U    // EPWM8 Clock Enable bit
#define SYSCTL_PCLKCR2_EPWM9    0x100U   // EPWM9 Clock Enable bit
#define SYSCTL_PCLKCR2_EPWM10   0x200U   // EPWM10 Clock Enable bit
#define SYSCTL_PCLKCR2_EPWM11   0x400U   // EPWM11 Clock Enable bit
#define SYSCTL_PCLKCR2_EPWM12   0x800U   // EPWM12 Clock Enable bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCLKCR3 register
//
//*************************************************************************************************
#define SYSCTL_PCLKCR3_ECAP1   0x1U    // ECAP1 Clock Enable bit
#define SYSCTL_PCLKCR3_ECAP2   0x2U    // ECAP2 Clock Enable bit
#define SYSCTL_PCLKCR3_ECAP3   0x4U    // ECAP3 Clock Enable bit
#define SYSCTL_PCLKCR3_ECAP4   0x8U    // ECAP4 Clock Enable bit
#define SYSCTL_PCLKCR3_ECAP5   0x10U   // ECAP5 Clock Enable bit
#define SYSCTL_PCLKCR3_ECAP6   0x20U   // ECAP6 Clock Enable bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCLKCR4 register
//
//*************************************************************************************************
#define SYSCTL_PCLKCR4_EQEP1   0x1U   // EQEP1 Clock Enable bit
#define SYSCTL_PCLKCR4_EQEP2   0x2U   // EQEP2 Clock Enable bit
#define SYSCTL_PCLKCR4_EQEP3   0x4U   // EQEP3 Clock Enable bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCLKCR6 register
//
//*************************************************************************************************
#define SYSCTL_PCLKCR6_SD1   0x1U   // SD1 Clock Enable bit
#define SYSCTL_PCLKCR6_SD2   0x2U   // SD2 Clock Enable bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCLKCR7 register
//
//*************************************************************************************************
#define SYSCTL_PCLKCR7_SCI_A   0x1U   // SCI_A Clock Enable bit
#define SYSCTL_PCLKCR7_SCI_B   0x2U   // SCI_B Clock Enable bit
#define SYSCTL_PCLKCR7_SCI_C   0x4U   // SCI_C Clock Enable bit
#define SYSCTL_PCLKCR7_SCI_D   0x8U   // SCI_D Clock Enable bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCLKCR8 register
//
//*************************************************************************************************
#define SYSCTL_PCLKCR8_SPI_A   0x1U   // SPI_A Clock Enable bit
#define SYSCTL_PCLKCR8_SPI_B   0x2U   // SPI_B Clock Enable bit
#define SYSCTL_PCLKCR8_SPI_C   0x4U   // SPI_C Clock Enable bit

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
#define SYSCTL_PCLKCR10_CAN_B   0x2U   // CAN_B Clock Enable bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCLKCR11 register
//
//*************************************************************************************************
#define SYSCTL_PCLKCR11_MCBSP_A   0x1U       // McBSP_A Clock Enable bit
#define SYSCTL_PCLKCR11_MCBSP_B   0x2U       // McBSP_B Clock Enable bit
#define SYSCTL_PCLKCR11_USB_A     0x10000U   // USB_A Clock Enable bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCLKCR12 register
//
//*************************************************************************************************
#define SYSCTL_PCLKCR12_UPP_A   0x1U   // uPP_A Clock Enable bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCLKCR13 register
//
//*************************************************************************************************
#define SYSCTL_PCLKCR13_ADC_A   0x1U   // ADC_A Clock Enable bit
#define SYSCTL_PCLKCR13_ADC_B   0x2U   // ADC_B Clock Enable bit
#define SYSCTL_PCLKCR13_ADC_C   0x4U   // ADC_C Clock Enable bit
#define SYSCTL_PCLKCR13_ADC_D   0x8U   // ADC_D Clock Enable bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCLKCR14 register
//
//*************************************************************************************************
#define SYSCTL_PCLKCR14_CMPSS1   0x1U    // CMPSS1 Clock Enable bit
#define SYSCTL_PCLKCR14_CMPSS2   0x2U    // CMPSS2 Clock Enable bit
#define SYSCTL_PCLKCR14_CMPSS3   0x4U    // CMPSS3 Clock Enable bit
#define SYSCTL_PCLKCR14_CMPSS4   0x8U    // CMPSS4 Clock Enable bit
#define SYSCTL_PCLKCR14_CMPSS5   0x10U   // CMPSS5 Clock Enable bit
#define SYSCTL_PCLKCR14_CMPSS6   0x20U   // CMPSS6 Clock Enable bit
#define SYSCTL_PCLKCR14_CMPSS7   0x40U   // CMPSS7 Clock Enable bit
#define SYSCTL_PCLKCR14_CMPSS8   0x80U   // CMPSS8 Clock Enable bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCLKCR16 register
//
//*************************************************************************************************
#define SYSCTL_PCLKCR16_DAC_A   0x10000U   // Buffered_DAC_A Clock Enable Bit
#define SYSCTL_PCLKCR16_DAC_B   0x20000U   // Buffered_DAC_B Clock Enable Bit
#define SYSCTL_PCLKCR16_DAC_C   0x40000U   // Buffered_DAC_C Clock Enable Bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SECMSEL register
//
//*************************************************************************************************
#define SYSCTL_SECMSEL_PF1SEL_S   0U
#define SYSCTL_SECMSEL_PF1SEL_M   0x3U   // Secondary Master Select for VBUS32_1 Bridge
#define SYSCTL_SECMSEL_PF2SEL_S   2U
#define SYSCTL_SECMSEL_PF2SEL_M   0xCU   // Secondary Master Select for VBUS32_2 Bridge

//*************************************************************************************************
//
// The following are defines for the bit fields in the LPMCR register
//
//*************************************************************************************************
#define SYSCTL_LPMCR_LPM_S         0U
#define SYSCTL_LPMCR_LPM_M         0x3U          // Low Power Mode setting
#define SYSCTL_LPMCR_QUALSTDBY_S   2U
#define SYSCTL_LPMCR_QUALSTDBY_M   0xFCU         // STANDBY Wakeup Pin Qualification Setting
#define SYSCTL_LPMCR_WDINTE        0x8000U       // Enable for WDINT wakeup from STANDBY
#define SYSCTL_LPMCR_M0M1MODE_S    16U
#define SYSCTL_LPMCR_M0M1MODE_M    0x30000U      // Configuration for M0 and M1 mode during HIB
#define SYSCTL_LPMCR_IOISODIS      0x80000000U   // IO Isolation Disable

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
// The following are defines for the bit fields in the RESC register
//
//*************************************************************************************************
#define SYSCTL_RESC_POR                0x1U          // POR Reset Cause Indication Bit
#define SYSCTL_RESC_XRSN               0x2U          // XRSn Reset Cause Indication Bit
#define SYSCTL_RESC_WDRSN              0x4U          // WDRSn Reset Cause Indication Bit
#define SYSCTL_RESC_NMIWDRSN           0x8U          // NMIWDRSn Reset Cause Indication Bit
#define SYSCTL_RESC_HWBISTN            0x20U         // HWBISTn Reset Cause Indication Bit
#define SYSCTL_RESC_HIBRESETN          0x40U         // HIBRESETn Reset Cause Indication Bit
#define SYSCTL_RESC_SCCRESETN          0x100U        // SCCRESETn Reset Cause Indication Bit
#define SYSCTL_RESC_XRSN_PIN_STATUS    0x40000000U   // XRSN Pin Status
#define SYSCTL_RESC_TRSTN_PIN_STATUS   0x80000000U   // TRSTn Status


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
#define SYSCTL_WDKEY_WDKEY_M   0xFFU   // WD KEY

//*************************************************************************************************
//
// The following are defines for the bit fields in the WDCR register
//
//*************************************************************************************************
#define SYSCTL_WDCR_WDPS_S    0U
#define SYSCTL_WDCR_WDPS_M    0x7U    // WD Clock Prescalar
#define SYSCTL_WDCR_WDCHK_S   3U
#define SYSCTL_WDCR_WDCHK_M   0x38U   // WD Check Bits
#define SYSCTL_WDCR_WDDIS     0x40U   // WD Disable

//*************************************************************************************************
//
// The following are defines for the bit fields in the WDWCR register
//
//*************************************************************************************************
#define SYSCTL_WDWCR_MIN_S      0U
#define SYSCTL_WDWCR_MIN_M      0xFFU    // WD Min Threshold setting for Windowed Watchdog
                                         // functionality
#define SYSCTL_WDWCR_FIRSTKEY   0x100U   // First Key Detect Flag


//*************************************************************************************************
//
// The following are defines for the bit fields in the CLA1TASKSRCSELLOCK register
//
//*************************************************************************************************
#define SYSCTL_CLA1TASKSRCSELLOCK_CLA1TASKSRCSEL1   0x1U   // CLA1TASKSRCSEL1 Register Lock bit
#define SYSCTL_CLA1TASKSRCSELLOCK_CLA1TASKSRCSEL2   0x2U   // CLA1TASKSRCSEL2 Register Lock bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the DMACHSRCSELLOCK register
//
//*************************************************************************************************
#define SYSCTL_DMACHSRCSELLOCK_DMACHSRCSEL1   0x1U   // DMACHSRCSEL1 Register Lock bit
#define SYSCTL_DMACHSRCSELLOCK_DMACHSRCSEL2   0x2U   // DMACHSRCSEL2 Register Lock bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the CLA1TASKSRCSEL1 register
//
//*************************************************************************************************
#define SYSCTL_CLA1TASKSRCSEL1_TASK1_S   0U
#define SYSCTL_CLA1TASKSRCSEL1_TASK1_M   0xFFU         // Selects the Trigger Source for TASK1 of
                                                       // CLA1
#define SYSCTL_CLA1TASKSRCSEL1_TASK2_S   8U
#define SYSCTL_CLA1TASKSRCSEL1_TASK2_M   0xFF00U       // Selects the Trigger Source for TASK2 of
                                                       // CLA1
#define SYSCTL_CLA1TASKSRCSEL1_TASK3_S   16U
#define SYSCTL_CLA1TASKSRCSEL1_TASK3_M   0xFF0000U     // Selects the Trigger Source for TASK3 of
                                                       // CLA1
#define SYSCTL_CLA1TASKSRCSEL1_TASK4_S   24U
#define SYSCTL_CLA1TASKSRCSEL1_TASK4_M   0xFF000000U   // Selects the Trigger Source for TASK4 of
                                                       // CLA1

//*************************************************************************************************
//
// The following are defines for the bit fields in the CLA1TASKSRCSEL2 register
//
//*************************************************************************************************
#define SYSCTL_CLA1TASKSRCSEL2_TASK5_S   0U
#define SYSCTL_CLA1TASKSRCSEL2_TASK5_M   0xFFU         // Selects the Trigger Source for TASK5 of
                                                       // CLA1
#define SYSCTL_CLA1TASKSRCSEL2_TASK6_S   8U
#define SYSCTL_CLA1TASKSRCSEL2_TASK6_M   0xFF00U       // Selects the Trigger Source for TASK6 of
                                                       // CLA1
#define SYSCTL_CLA1TASKSRCSEL2_TASK7_S   16U
#define SYSCTL_CLA1TASKSRCSEL2_TASK7_M   0xFF0000U     // Selects the Trigger Source for TASK7 of
                                                       // CLA1
#define SYSCTL_CLA1TASKSRCSEL2_TASK8_S   24U
#define SYSCTL_CLA1TASKSRCSEL2_TASK8_M   0xFF000000U   // Selects the Trigger Source for TASK8 of
                                                       // CLA1

//*************************************************************************************************
//
// The following are defines for the bit fields in the DMACHSRCSEL1 register
//
//*************************************************************************************************
#define SYSCTL_DMACHSRCSEL1_CH1_S   0U
#define SYSCTL_DMACHSRCSEL1_CH1_M   0xFFU         // Selects the Trigger and Sync Source CH1 of DMA
#define SYSCTL_DMACHSRCSEL1_CH2_S   8U
#define SYSCTL_DMACHSRCSEL1_CH2_M   0xFF00U       // Selects the Trigger and Sync Source CH2 of DMA
#define SYSCTL_DMACHSRCSEL1_CH3_S   16U
#define SYSCTL_DMACHSRCSEL1_CH3_M   0xFF0000U     // Selects the Trigger and Sync Source CH3 of DMA
#define SYSCTL_DMACHSRCSEL1_CH4_S   24U
#define SYSCTL_DMACHSRCSEL1_CH4_M   0xFF000000U   // Selects the Trigger and Sync Source CH4 of DMA

//*************************************************************************************************
//
// The following are defines for the bit fields in the DMACHSRCSEL2 register
//
//*************************************************************************************************
#define SYSCTL_DMACHSRCSEL2_CH5_S   0U
#define SYSCTL_DMACHSRCSEL2_CH5_M   0xFFU     // Selects the Trigger and Sync Source CH5 of DMA
#define SYSCTL_DMACHSRCSEL2_CH6_S   8U
#define SYSCTL_DMACHSRCSEL2_CH6_M   0xFF00U   // Selects the Trigger and Sync Source CH6 of DMA


//*************************************************************************************************
//
// The following are defines for the bit fields in the SYNCSELECT register
//
//*************************************************************************************************
#define SYSCTL_SYNCSELECT_EPWM4SYNCIN_S    0U
#define SYSCTL_SYNCSELECT_EPWM4SYNCIN_M    0x7U          // Selects Sync Input Source for EPWM4
#define SYSCTL_SYNCSELECT_EPWM7SYNCIN_S    3U
#define SYSCTL_SYNCSELECT_EPWM7SYNCIN_M    0x38U         // Selects Sync Input Source for EPWM7
#define SYSCTL_SYNCSELECT_EPWM10SYNCIN_S   6U
#define SYSCTL_SYNCSELECT_EPWM10SYNCIN_M   0x1C0U        // Selects Sync Input Source for EPWM10
#define SYSCTL_SYNCSELECT_ECAP1SYNCIN_S    9U
#define SYSCTL_SYNCSELECT_ECAP1SYNCIN_M    0xE00U        // Selects Sync Input Source for ECAP1
#define SYSCTL_SYNCSELECT_ECAP4SYNCIN_S    12U
#define SYSCTL_SYNCSELECT_ECAP4SYNCIN_M    0x7000U       // Selects Sync Input Source for ECAP4
#define SYSCTL_SYNCSELECT_SYNCOUT_S        27U
#define SYSCTL_SYNCSELECT_SYNCOUT_M        0x18000000U   // Select Syncout Source

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOCOUTSELECT register
//
//*************************************************************************************************
#define SYSCTL_ADCSOCOUTSELECT_PWM1SOCAEN    0x1U         // PWM1SOCAEN Enable for ADCSOCAO
#define SYSCTL_ADCSOCOUTSELECT_PWM2SOCAEN    0x2U         // PWM2SOCAEN Enable for ADCSOCAO
#define SYSCTL_ADCSOCOUTSELECT_PWM3SOCAEN    0x4U         // PWM3SOCAEN Enable for ADCSOCAO
#define SYSCTL_ADCSOCOUTSELECT_PWM4SOCAEN    0x8U         // PWM4SOCAEN Enable for ADCSOCAO
#define SYSCTL_ADCSOCOUTSELECT_PWM5SOCAEN    0x10U        // PWM5SOCAEN Enable for ADCSOCAO
#define SYSCTL_ADCSOCOUTSELECT_PWM6SOCAEN    0x20U        // PWM6SOCAEN Enable for ADCSOCAO
#define SYSCTL_ADCSOCOUTSELECT_PWM7SOCAEN    0x40U        // PWM7SOCAEN Enable for ADCSOCAO
#define SYSCTL_ADCSOCOUTSELECT_PWM8SOCAEN    0x80U        // PWM8SOCAEN Enable for ADCSOCAO
#define SYSCTL_ADCSOCOUTSELECT_PWM9SOCAEN    0x100U       // PWM9SOCAEN Enable for ADCSOCAO
#define SYSCTL_ADCSOCOUTSELECT_PWM10SOCAEN   0x200U       // PWM10SOCAEN Enable for ADCSOCAO
#define SYSCTL_ADCSOCOUTSELECT_PWM11SOCAEN   0x400U       // PWM11SOCAEN Enable for ADCSOCAO
#define SYSCTL_ADCSOCOUTSELECT_PWM12SOCAEN   0x800U       // PWM12SOCAEN Enable for ADCSOCAO
#define SYSCTL_ADCSOCOUTSELECT_PWM1SOCBEN    0x10000U     // PWM1SOCBEN Enable for ADCSOCBO
#define SYSCTL_ADCSOCOUTSELECT_PWM2SOCBEN    0x20000U     // PWM2SOCBEN Enable for ADCSOCBO
#define SYSCTL_ADCSOCOUTSELECT_PWM3SOCBEN    0x40000U     // PWM3SOCBEN Enable for ADCSOCBO
#define SYSCTL_ADCSOCOUTSELECT_PWM4SOCBEN    0x80000U     // PWM4SOCBEN Enable for ADCSOCBO
#define SYSCTL_ADCSOCOUTSELECT_PWM5SOCBEN    0x100000U    // PWM5SOCBEN Enable for ADCSOCBO
#define SYSCTL_ADCSOCOUTSELECT_PWM6SOCBEN    0x200000U    // PWM6SOCBEN Enable for ADCSOCBO
#define SYSCTL_ADCSOCOUTSELECT_PWM7SOCBEN    0x400000U    // PWM7SOCBEN Enable for ADCSOCBO
#define SYSCTL_ADCSOCOUTSELECT_PWM8SOCBEN    0x800000U    // PWM8SOCBEN Enable for ADCSOCBO
#define SYSCTL_ADCSOCOUTSELECT_PWM9SOCBEN    0x1000000U   // PWM9SOCBEN Enable for ADCSOCBO
#define SYSCTL_ADCSOCOUTSELECT_PWM10SOCBEN   0x2000000U   // PWM10SOCBEN Enable for ADCSOCBO
#define SYSCTL_ADCSOCOUTSELECT_PWM11SOCBEN   0x4000000U   // PWM11SOCBEN Enable for ADCSOCBO
#define SYSCTL_ADCSOCOUTSELECT_PWM12SOCBEN   0x8000000U   // PWM12SOCBEN Enable for ADCSOCBO

//*************************************************************************************************
//
// The following are defines for the bit fields in the SYNCSOCLOCK register
//
//*************************************************************************************************
#define SYSCTL_SYNCSOCLOCK_SYNCSELECT        0x1U   // SYNCSEL Register Lock bit
#define SYSCTL_SYNCSOCLOCK_ADCSOCOUTSELECT   0x2U   // ADCSOCOUTSELECT Register Lock bit



#endif
