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
#define SYSCTL_O_DEVCFGLOCK2   0x2U     // Lock bit for DEVCFG registers
#define SYSCTL_O_PARTIDL       0x8U     // Lower 32-bit of Device PART Identification Number
#define SYSCTL_O_PARTIDH       0xAU     // Upper 32-bit of Device PART Identification Number
#define SYSCTL_O_REVID         0xCU     // Device Revision Number
#define SYSCTL_O_BANKMUXSEL    0x60U    // Flash Bank allocation to CPU. Internal note : This
                                        // register is accessible (read-only) by CPU2, for devices
                                        // with CPU2
#define SYSCTL_O_MCUCNF0       0x78U    // MCU Configuration register for DC0.DUAL_CORE
#define SYSCTL_O_MCUCNF1       0x7AU    // MCU Configuration register for LockStep Feature on
                                        // device
#define SYSCTL_O_MCUCNF2       0x7CU    // MCU Configuration register for EtherCAT
#define SYSCTL_O_MCUCNF3       0x7EU    // MCU Configuration register for Flash Bank 1
#define SYSCTL_O_MCUCNF4       0x80U    // MCU Configuration register for Flash Bank 2
#define SYSCTL_O_MCUCNF5       0x82U    // MCU Configuration register for Flash Bank 3
#define SYSCTL_O_MCUCNF6       0x84U    // MCU Configuration register for Flash Bank 4
#define SYSCTL_O_MCUCNF7       0x86U    // MCU Configuration register for Flash Bank 5
#define SYSCTL_O_MCUCNFLOCK    0x8CU    // Lock bit for MCUCNFx registers
#define SYSCTL_O_TRIMERRSTS    0x8EU    // TRIM Error Status register
#define SYSCTL_O_SOFTPRES0     0x9CU    // Processing Block Software Reset register
#define SYSCTL_O_SOFTPRES1     0x9EU    // EMIF Software Reset register
#define SYSCTL_O_SOFTPRES2     0xA0U    // EPWM Software Reset register
#define SYSCTL_O_SOFTPRES3     0xA2U    // ECAP Software Reset register
#define SYSCTL_O_SOFTPRES4     0xA4U    // EQEP Software Reset register
#define SYSCTL_O_SOFTPRES6     0xA8U    // Sigma Delta Software Reset register
#define SYSCTL_O_SOFTPRES7     0xAAU    // SCI, UART Software Reset register
#define SYSCTL_O_SOFTPRES8     0xACU    // SPI Software Reset register
#define SYSCTL_O_SOFTPRES9     0xAEU    // I2C Software Reset register
#define SYSCTL_O_SOFTPRES10    0xB0U    // CAN Software Reset register
#define SYSCTL_O_SOFTPRES11    0xB2U    // McBSP/USB Software Reset register
#define SYSCTL_O_SOFTPRES13    0xB6U    // ADC Software Reset register
#define SYSCTL_O_SOFTPRES14    0xB8U    // CMPSS Software Reset register
#define SYSCTL_O_SOFTPRES16    0xBCU    // DAC Software Reset register
#define SYSCTL_O_SOFTPRES17    0xBEU    // CLB Software Reset register
#define SYSCTL_O_SOFTPRES18    0xC0U    // FSI Software Reset register
#define SYSCTL_O_SOFTPRES19    0xC2U    // LIN Software Reset register
#define SYSCTL_O_SOFTPRES21    0xC6U    // DCC Software Reset register
#define SYSCTL_O_SOFTPRES23    0xCAU    // ETHERCAT Software Reset register
#define SYSCTL_O_SOFTPRES26    0xD0U    // AES Software Reset register
#define SYSCTL_O_SOFTPRES27    0xD2U    // EPG Software Reset register
#define SYSCTL_O_SOFTPRES28    0xD4U    // Flash Software Reset register
#define SYSCTL_O_SOFTPRES29    0xD6U    // ADCCHECKER Software Reset register
#define SYSCTL_O_CPUSEL0       0xF0U    // CPU Select register for common peripherals
#define SYSCTL_O_CPUSEL1       0xF2U    // CPU Select register for common peripherals
#define SYSCTL_O_CPUSEL2       0xF4U    // CPU Select register for common peripherals
#define SYSCTL_O_CPUSEL3       0xF6U    // CPU Select register for common peripherals
#define SYSCTL_O_CPUSEL4       0xF8U    // CPU Select register for common peripherals
#define SYSCTL_O_CPUSEL5       0xFAU    // CPU Select register for common peripherals
#define SYSCTL_O_CPUSEL6       0xFCU    // CPU Select register for common peripherals
#define SYSCTL_O_CPUSEL7       0xFEU    // CPU Select register for common peripherals
#define SYSCTL_O_CPUSEL8       0x100U   // CPU Select register for common peripherals
#define SYSCTL_O_CPUSEL9       0x102U   // CPU Select register for common peripherals
#define SYSCTL_O_CPUSEL11      0x106U   // CPU Select register for common peripherals
#define SYSCTL_O_CPUSEL12      0x108U   // CPU Select register for common peripherals
#define SYSCTL_O_CPUSEL13      0x10AU   // CPU select register for DCC
#define SYSCTL_O_CPUSEL14      0x10CU   // CPU Select register for common peripherals
#define SYSCTL_O_CPUSEL15      0x10EU   // CPU select register for CLB tiles
#define SYSCTL_O_CPUSEL16      0x110U   // CPU select register for FSI
#define SYSCTL_O_CPUSEL17      0x112U   // CPU select register for LIN
#define SYSCTL_O_CPUSEL23      0x11EU   // CPU select register for EtherCAT
#define SYSCTL_O_CPUSEL25      0x122U   // CPU select register for HRCAL
#define SYSCTL_O_CPUSEL26      0x124U   // CPU select register for AES
#define SYSCTL_O_CPUSEL27      0x126U   // CPU select register for EPG
#define SYSCTL_O_CPUSEL28      0x128U   // CPU select register for ADCCHECKER tiles
#define SYSCTL_O_CPU2RESCTL    0x13CU   // CPU2 Reset Control Register
#define SYSCTL_O_RSTSTAT       0x13EU   // Reset Status register for secondary C28x CPUs
#define SYSCTL_O_LPMSTAT       0x13FU   // LPM Status Register for secondary C28x CPUs
#define SYSCTL_O_TAP_STATUS    0x14AU   // Status of JTAG State machine & Debugger Connect
#define SYSCTL_O_TAP_CONTROL   0x14CU   // Disable TAP control
#define SYSCTL_O_USBTYPE       0x1D2U   // Configures USB Type for the device
#define SYSCTL_O_ECAPTYPE      0x1D3U   // Configures ECAP Type for the device
#define SYSCTL_O_SDFMTYPE      0x1D4U   // Configures SDFM Type for the device
#define SYSCTL_O_MEMMAPTYPE    0x1D6U   // Configures Memory Map Type for the device

#define SYSCTL_O_CLKSEM           0x0U    // Clock Control Semaphore Register
#define SYSCTL_O_CLKCFGLOCK1      0x2U    // Lock bit for CLKCFG registers
#define SYSCTL_O_CLKSRCCTL1       0x8U    // Clock Source Control register-1
#define SYSCTL_O_CLKSRCCTL2       0xAU    // Clock Source Control register-2
#define SYSCTL_O_CLKSRCCTL3       0xCU    // Clock Source Control register-3
#define SYSCTL_O_SYSPLLCTL1       0xEU    // SYSPLL Control register-1
#define SYSCTL_O_SYSPLLMULT       0x14U   // SYSPLL Multiplier register
#define SYSCTL_O_SYSPLLSTS        0x16U   // SYSPLL Status register
#define SYSCTL_O_AUXPLLCTL1       0x18U   // AUXPLL Control register-1
#define SYSCTL_O_AUXPLLMULT       0x1EU   // AUXPLL Multiplier register
#define SYSCTL_O_AUXPLLSTS        0x20U   // AUXPLL Status register
#define SYSCTL_O_SYSCLKDIVSEL     0x22U   // System Clock Divider Select register
#define SYSCTL_O_AUXCLKDIVSEL     0x24U   // Auxillary Clock Divider Select register
#define SYSCTL_O_PERCLKDIVSEL     0x26U   // Peripheral Clock Divider Select register
#define SYSCTL_O_XCLKOUTDIVSEL    0x28U   // XCLKOUT Divider Select register
#define SYSCTL_O_CLBCLKCTL        0x2AU   // CLB Clocking Control Register
#define SYSCTL_O_LOSPCP           0x2CU   // Low Speed Clock Source Prescalar
#define SYSCTL_O_MCDCR            0x2EU   // Missing Clock Detect Control Register
#define SYSCTL_O_X1CNT            0x30U   // 10-bit Counter on X1 Clock
#define SYSCTL_O_XTALCR           0x32U   // XTAL Control Register
#define SYSCTL_O_XTALCR2          0x3AU   // XTAL Control Register for pad init
#define SYSCTL_O_CLKFAILCFG       0x3CU   // Clock Fail cause Configuration
#define SYSCTL_O_ETHERCATCLKCTL   0x40U   // EtherCAT Clock Control
#define SYSCTL_O_SYNCBUSY         0x42U   // Pulse Transfer Sync Busy Status register

#define SYSCTL_O_CPUSYSLOCK1          0x0U    // Lock bit for CPUSYS registers
#define SYSCTL_O_CPUSYSLOCK2          0x2U    // Lock bit for CPUSYS registers
#define SYSCTL_O_PIEVERRADDR          0xAU    // PIE Vector Fetch Error Address register
#define SYSCTL_O_ETHERCATCTL          0xCU    // ETHERCAT control register.
#define SYSCTL_O_PCLKCR0              0x10U   // Peripheral Clock Gating Registers
#define SYSCTL_O_PCLKCR1              0x12U   // Peripheral Clock Gating Register - EMIF
#define SYSCTL_O_PCLKCR2              0x14U   // Peripheral Clock Gating Register - ETPWM
#define SYSCTL_O_PCLKCR3              0x16U   // Peripheral Clock Gating Register - ECAP
#define SYSCTL_O_PCLKCR4              0x18U   // Peripheral Clock Gating Register - EQEP
#define SYSCTL_O_PCLKCR6              0x1CU   // Peripheral Clock Gating Register - SDFM
#define SYSCTL_O_PCLKCR7              0x1EU   // Peripheral Clock Gating Register - SCI, UART
#define SYSCTL_O_PCLKCR8              0x20U   // Peripheral Clock Gating Register - SPI
#define SYSCTL_O_PCLKCR9              0x22U   // Peripheral Clock Gating Register - I2C, PMBUS
#define SYSCTL_O_PCLKCR10             0x24U   // Peripheral Clock Gating Register - CAN
#define SYSCTL_O_PCLKCR11             0x26U   // Peripheral Clock Gating Register - McBSP_USB
#define SYSCTL_O_PCLKCR13             0x2AU   // Peripheral Clock Gating Register - ADC
#define SYSCTL_O_PCLKCR14             0x2CU   // Peripheral Clock Gating Register - CMPSS
#define SYSCTL_O_PCLKCR16             0x30U   // Peripheral Clock Gating Register Buf_DAC
#define SYSCTL_O_PCLKCR17             0x32U   // Peripheral Clock Gating Register - CLB
#define SYSCTL_O_PCLKCR18             0x34U   // Peripheral Clock Gating Register - FSI
#define SYSCTL_O_PCLKCR19             0x36U   // Peripheral Clock Gating Register - LIN
#define SYSCTL_O_PCLKCR21             0x3AU   // Peripheral Clock Gating Register - DCC
#define SYSCTL_O_PCLKCR23             0x3EU   // Peripheral Clock Gating Register - EtherCAT
#define SYSCTL_O_PCLKCR25             0x42U   // Peripheral Clock Gating Register - HRCAL0,1,2
#define SYSCTL_O_PCLKCR26             0x44U   // Peripheral Clock Gating Register - AES
#define SYSCTL_O_PCLKCR27             0x46U   // Peripheral Clock Gating Register - EPG
#define SYSCTL_O_PCLKCR28             0x48U   // Peripheral Clock Gating Register - ADCCHECKER
#define SYSCTL_O_SIMRESET             0x60U   // Simulated Reset Register
#define SYSCTL_O_LPMCR                0x66U   // LPM Control Register
#define SYSCTL_O_CPUID                0x68U   // Indicates CPU1 or CPU2
#define SYSCTL_O_CMPSSLPMSEL          0x6CU   // CMPSS LPM Wakeup select registers
#define SYSCTL_O_GPIOLPMSEL0          0x6EU   // GPIO LPM Wakeup select registers
#define SYSCTL_O_GPIOLPMSEL1          0x70U   // GPIO LPM Wakeup select registers
#define SYSCTL_O_TMR2CLKCTL           0x72U   // Timer2 Clock Measurement functionality control
                                              // register
#define SYSCTL_O_RESCCLR              0x74U   // Reset Cause Clear Register
#define SYSCTL_O_RESC                 0x76U   // Reset Cause register
#define SYSCTL_O_MCANWAKESTATUS       0x8EU   // MCAN Wake Status Register
#define SYSCTL_O_MCANWAKESTATUSCLR    0x90U   // MCAN Wake Status Clear Register
#define SYSCTL_O_CLKSTOPREQ           0x92U   // Peripheral Clock Stop Request Register
#define SYSCTL_O_CLKSTOPACK           0x94U   // Peripheral Clock Stop Ackonwledge Register
#define SYSCTL_O_USER_REG1_SYSRSN     0x96U   // Software Configurable registers reset by SYSRSn
#define SYSCTL_O_USER_REG2_SYSRSN     0x98U   // Software Configurable registers reset by SYSRSn
#define SYSCTL_O_USER_REG1_XRSN       0x9AU   // Software Configurable registers reset by XRSn
#define SYSCTL_O_USER_REG2_XRSN       0x9CU   // Software Configurable registers reset by XRSn
#define SYSCTL_O_USER_REG1_PORESETN   0x9EU   // Software Configurable registers reset by PORESETn
#define SYSCTL_O_USER_REG2_PORESETN   0xA0U   // Software Configurable registers reset by PORESETn
#define SYSCTL_O_USER_REG3_PORESETN   0xA2U   // Software Configurable registers reset by PORESETn
#define SYSCTL_O_USER_REG4_PORESETN   0xA4U   // Software Configurable registers reset by PORESETn

#define SYSCTL_O_LSEN                 0x6AU   // Lockstep enable configuration

#define SYSCTL_O_SCSR         0x22U   // System Control & Status Register
#define SYSCTL_O_WDCNTR       0x23U   // Watchdog Counter Register
#define SYSCTL_O_WDKEY        0x25U   // Watchdog Reset Key Register
#define SYSCTL_O_SYNCBUSYWD   0x28U   // SYNCBUSY status for Watchdog Register
#define SYSCTL_O_WDCR         0x29U   // Watchdog Control Register
#define SYSCTL_O_WDWCR        0x2AU   // Watchdog Windowed Control Register

#define SYSCTL_O_CLA1TASKSRCSELLOCK   0x0U    // CLA1 Task Trigger Source Select Lock Register
#define SYSCTL_O_DMACHSRCSELLOCK      0x4U    // DMA Channel Triger Source Select Lock Register
#define SYSCTL_O_CLA1TASKSRCSEL1      0x6U    // CLA1 Task Trigger Source Select Register-1
#define SYSCTL_O_CLA1TASKSRCSEL2      0x8U    // CLA1 Task Trigger Source Select Register-2
#define SYSCTL_O_DMACHSRCSEL1         0x16U   // DMA Channel Trigger Source Select Register-1
#define SYSCTL_O_DMACHSRCSEL2         0x18U   // DMA Channel Trigger Source Select Register-2

#define SYSCTL_O_DMACHSRCSELLOCK   0x4U    // DMA Channel Triger Source Select Lock Register
#define SYSCTL_O_DMACHSRCSEL1      0x16U   // DMA Channel Trigger Source Select Register-1
#define SYSCTL_O_DMACHSRCSEL2      0x18U   // DMA Channel Trigger Source Select Register-2

#define SYSCTL_O_ADCA_AC          0x0U     // ADCA Controller Access Control Register
#define SYSCTL_O_ADCB_AC          0x2U     // ADCB Controller Access Control Register
#define SYSCTL_O_ADCC_AC          0x4U     // ADCC Controller Access Control Register
#define SYSCTL_O_CMPSS1_AC        0x10U    // CMPSS1 Controller Access Control Register
#define SYSCTL_O_CMPSS2_AC        0x12U    // CMPSS2 Controller Access Control Register
#define SYSCTL_O_CMPSS3_AC        0x14U    // CMPSS3 Controller Access Control Register
#define SYSCTL_O_CMPSS4_AC        0x16U    // CMPSS4 Controller Access Control Register
#define SYSCTL_O_CMPSS5_AC        0x18U    // CMPSS5 Controller Access Control Register
#define SYSCTL_O_CMPSS6_AC        0x1AU    // CMPSS6 Controller Access Control Register
#define SYSCTL_O_CMPSS7_AC        0x1CU    // CMPSS7 Controller Access Control Register
#define SYSCTL_O_CMPSS8_AC        0x1EU    // CMPSS8 Controller Access Control Register
#define SYSCTL_O_CMPSS9_AC        0x20U    // CMPSS9 Controller Access Control Register
#define SYSCTL_O_CMPSS10_AC       0x22U    // CMPSS10 Controller Access Control Register
#define SYSCTL_O_CMPSS11_AC       0x24U    // CMPSS11 Controller Access Control Register
#define SYSCTL_O_DACA_AC          0x28U    // DACA Controller Access Control Register
#define SYSCTL_O_DACC_AC          0x2CU    // DACC Controller Access Control Register
#define SYSCTL_O_EPWM1_AC         0x48U    // EPWM1 Controller Access Control Register
#define SYSCTL_O_EPWM2_AC         0x4AU    // EPWM2 Controller Access Control Register
#define SYSCTL_O_EPWM3_AC         0x4CU    // EPWM3 Controller Access Control Register
#define SYSCTL_O_EPWM4_AC         0x4EU    // EPWM4 Controller Access Control Register
#define SYSCTL_O_EPWM5_AC         0x50U    // EPWM5 Controller Access Control Register
#define SYSCTL_O_EPWM6_AC         0x52U    // EPWM6 Controller Access Control Register
#define SYSCTL_O_EPWM7_AC         0x54U    // EPWM7 Controller Access Control Register
#define SYSCTL_O_EPWM8_AC         0x56U    // EPWM8 Controller Access Control Register
#define SYSCTL_O_EPWM9_AC         0x58U    // EPWM9 Controller Access Control Register
#define SYSCTL_O_EPWM10_AC        0x5AU    // EPWM10 Controller Access Control Register
#define SYSCTL_O_EPWM11_AC        0x5CU    // EPWM11 Controller Access Control Register
#define SYSCTL_O_EPWM12_AC        0x5EU    // EPWM12 Controller Access Control Register
#define SYSCTL_O_EPWM13_AC        0x60U    // EPWM13 Controller Access Control Register
#define SYSCTL_O_EPWM14_AC        0x62U    // EPWM14 Controller Access Control Register
#define SYSCTL_O_EPWM15_AC        0x64U    // EPWM15 Controller Access Control Register
#define SYSCTL_O_EPWM16_AC        0x66U    // EPWM16 Controller Access Control Register
#define SYSCTL_O_EPWM17_AC        0x68U    // EPWM17 Controller Access Control Register
#define SYSCTL_O_EPWM18_AC        0x6AU    // EPWM18 Controller Access Control Register
#define SYSCTL_O_EQEP1_AC         0x70U    // EQEP1 Controller Access Control Register
#define SYSCTL_O_EQEP2_AC         0x72U    // EQEP2 Controller Access Control Register
#define SYSCTL_O_EQEP3_AC         0x74U    // EQEP3 Controller Access Control Register
#define SYSCTL_O_EQEP4_AC         0x76U    // EQEP4 Controller Access Control Register
#define SYSCTL_O_EQEP5_AC         0x78U    // EQEP5 Controller Access Control Register
#define SYSCTL_O_EQEP6_AC         0x7AU    // EQEP6 Controller Access Control Register
#define SYSCTL_O_ECAP1_AC         0x80U    // ECAP1 Controller Access Control Register
#define SYSCTL_O_ECAP2_AC         0x82U    // ECAP2 Controller Access Control Register
#define SYSCTL_O_ECAP3_AC         0x84U    // ECAP3 Controller Access Control Register
#define SYSCTL_O_ECAP4_AC         0x86U    // ECAP4 Controller Access Control Register
#define SYSCTL_O_ECAP5_AC         0x88U    // ECAP5 Controller Access Control Register
#define SYSCTL_O_ECAP6_AC         0x8AU    // ECAP6 Controller Access Control Register
#define SYSCTL_O_ECAP7_AC         0x8CU    // ECAP7 Controller Access Control Register
#define SYSCTL_O_SDFM1_AC         0xA8U    // SDFM1 Controller Access Control Register
#define SYSCTL_O_SDFM2_AC         0xAAU    // SDFM2 Controller Access Control Register
#define SYSCTL_O_SDFM3_AC         0xACU    // SDFM3 Controller Access Control Register
#define SYSCTL_O_SDFM4_AC         0xAEU    // SDFM4 Controller Access Control Register
#define SYSCTL_O_CLB1_AC          0xB0U    // CLB1 Controller Access Control Register
#define SYSCTL_O_CLB2_AC          0xB2U    // CLB2 Controller Access Control Register
#define SYSCTL_O_CLB3_AC          0xB4U    // CLB3 Controller Access Control Register
#define SYSCTL_O_CLB4_AC          0xB6U    // CLB4 Controller Access Control Register
#define SYSCTL_O_CLB5_AC          0xB8U    // CLB5 Controller Access Control Register
#define SYSCTL_O_CLB6_AC          0xBAU    // CLB6 Controller Access Control Register
#define SYSCTL_O_SCIA_AC          0x100U   // SCIA Controller Access Control Register
#define SYSCTL_O_SCIB_AC          0x102U   // SCIB Controller Access Control Register
#define SYSCTL_O_SPIA_AC          0x110U   // SPIA Controller Access Control Register
#define SYSCTL_O_SPIB_AC          0x112U   // SPIB Controller Access Control Register
#define SYSCTL_O_SPIC_AC          0x114U   // SPIC Controller Access Control Register
#define SYSCTL_O_SPID_AC          0x116U   // SPID Controller Access Control Register
#define SYSCTL_O_I2CA_AC          0x120U   // I2CA Controller Access Control Register
#define SYSCTL_O_I2CB_AC          0x122U   // I2CB Controller Access Control Register
#define SYSCTL_O_PMBUS_A_AC       0x130U   // PMBUSA Controller Access Control Register
#define SYSCTL_O_LIN_A_AC         0x138U   // LINA Controller Access Control Register
#define SYSCTL_O_LIN_B_AC         0x13AU   // LINB Controller Access Control Register
#define SYSCTL_O_DCANA_AC         0x140U   // DCANA Controller Access Control Register
#define SYSCTL_O_MCANA_AC         0x148U   // MCANA Controller Access Control Register
#define SYSCTL_O_MCANB_AC         0x14AU   // MCANB Controller Access Control Register
#define SYSCTL_O_FSIATX_AC        0x158U   // FSIA Controller Access Control Register
#define SYSCTL_O_FSIARX_AC        0x15AU   // FSIB Controller Access Control Register
#define SYSCTL_O_FSIBTX_AC        0x15CU   // FSIC Controller Access Control Register
#define SYSCTL_O_FSIBRX_AC        0x15EU   // FSID Controller Access Control Register
#define SYSCTL_O_FSICRX_AC        0x162U   // FSIB Controller Access Control Register
#define SYSCTL_O_FSIDRX_AC        0x166U   // FSID Controller Access Control Register
#define SYSCTL_O_USBA_AC          0x18AU   // USBA Controller Access Control Register
#define SYSCTL_O_HRPWM0_AC        0x1B2U   // HRPWM Controller Access Control Register
#define SYSCTL_O_HRPWM1_AC        0x1B4U   // HRPWM Controller Access Control Register
#define SYSCTL_O_HRPWM2_AC        0x1B6U   // HRPWM Controller Access Control Register
#define SYSCTL_O_ETHERCAT_AC      0x1B8U   // ETHERCAT Controller Access Control Register
#define SYSCTL_O_AESA_AC          0x1BCU   // AES Controller Access Control Register
#define SYSCTL_O_UARTA_AC         0x1BEU   // UART Controller Access Control Register
#define SYSCTL_O_UARTB_AC         0x1C0U   // UART Controller Access Control Register
#define SYSCTL_O_PERIPH_AC_LOCK   0x1FEU   // Lock Register to stop Write access to peripheral
                                           // Access register.

#define SYSCTL_O_SYNCSELECT         0x0U   // Sync Input and Output Select Register
#define SYSCTL_O_ADCSOCOUTSELECT    0x2U   // External ADCSOC Select Register (PWM1-16)
#define SYSCTL_O_ADCSOCOUTSELECT1   0x4U   // External ADCSOC Select Register (PWM17-32)
#define SYSCTL_O_SYNCSOCLOCK        0x6U   // SYNCSEL and EXTADCSOC Select Lock register

#define SYSCTL_O_LFUCONFIG            0x0U    // LFU configuration Register
#define SYSCTL_O_LFUSTATUS            0x2U    // LFU Configuration Status Register
#define SYSCTL_O_SWCONFIG1_SYSRSN     0x10U   // Spare registers reset by SYSRSn
#define SYSCTL_O_SWCONFIG2_SYSRSN     0x12U   // Spare registers reset by SYSRSn
#define SYSCTL_O_SWCONFIG1_XRSN       0x14U   // Spare registers reset by XRSn
#define SYSCTL_O_SWCONFIG2_XRSN       0x16U   // Spare registers reset by XRSn
#define SYSCTL_O_SWCONFIG1_PORESETN   0x18U   // Spare registers reset by PORESETn
#define SYSCTL_O_SWCONFIG2_PORESETN   0x1AU   // Spare registers reset by PORESETn
#define SYSCTL_O_LFU_LOCK             0x1CU   // LFU Lock Configuration
#define SYSCTL_O_LFU_COMMIT           0x1EU   // LFU Commit Configuration

#define SYSCTL_O_LFUCONFIG_ALT_       0x0U    // LFU configuration Register
#define SYSCTL_O_LFUSTATUS_ALT_       0x2U    // LFU Configuration Status Register
#define SYSCTL_O_SWCONFIG1_SYSRSN     0x10U   // Spare registers reset by SYSRSn
#define SYSCTL_O_SWCONFIG2_SYSRSN     0x12U   // Spare registers reset by SYSRSn
#define SYSCTL_O_SWCONFIG1_XRSN       0x14U   // Spare registers reset by XRSn
#define SYSCTL_O_SWCONFIG2_XRSN       0x16U   // Spare registers reset by XRSn
#define SYSCTL_O_SWCONFIG1_PORESETN   0x18U   // Spare registers reset by PORESETn
#define SYSCTL_O_SWCONFIG2_PORESETN   0x1AU   // Spare registers reset by PORESETn
#define SYSCTL_O_LFU_LOCK             0x1CU   // LFU Lock Configuration
#define SYSCTL_O_LFU_COMMIT           0x1EU   // LFU Commit Configuration

#define SYSCTL_O_SYS_ERR_INT_FLG   0x10U   // Status of interrupts due to multiple different errors
                                           // in the system.
#define SYSCTL_O_SYS_ERR_INT_CLR   0x12U   // SYS_ERR_INT_FLG clear register
#define SYSCTL_O_SYS_ERR_INT_SET   0x14U   // SYS_ERR_INT_FLG set register
#define SYSCTL_O_SYS_ERR_MASK      0x16U   // SYS_ERR_MASK register
#define SYSCTL_O_LCM_ERR_FLG              0x18U   // Status register indicating lockstep compare
                                                  // error flag
#define SYSCTL_O_LCM_ERR_FLG_CLR          0x1AU   // LCM_ERR_FLG clear register
#define SYSCTL_O_LCM_ERR_FLG_SET          0x1CU   // LCM_ERR_FLG set register
#define SYSCTL_O_LCM_ERR_FLG_MASK         0x1EU   // LCM_ERR_FLG mask register
#define SYSCTL_O_REGPARITY_ERR_FLG        0x20U   // Status register indicating register parity
                                                  // error flag
#define SYSCTL_O_REGPARITY_ERR_FLG_CLR    0x22U   // REGPARITY_ERR_FLG clear register
#define SYSCTL_O_REGPARITY_ERR_FLG_SET    0x24U   // REGPARITY_ERR_FLG set register
#define SYSCTL_O_REGPARITY_ERR_FLG_MASK   0x26U   // REGPARITY_ERR_FLG mask register


//*************************************************************************************************
//
// The following are defines for the bit fields in the DEVCFGLOCK1 register
//
//*************************************************************************************************
#define SYSCTL_DEVCFGLOCK1_CPUSEL0    0x1U          // Lock bit for CPUSEL0 register
#define SYSCTL_DEVCFGLOCK1_CPUSEL1    0x2U          // Lock bit for CPUSEL1 register
#define SYSCTL_DEVCFGLOCK1_CPUSEL2    0x4U          // Lock bit for CPUSEL2 register
#define SYSCTL_DEVCFGLOCK1_CPUSEL3    0x8U          // Lock bit for CPUSEL3 register
#define SYSCTL_DEVCFGLOCK1_CPUSEL4    0x10U         // Lock bit for CPUSEL4 register
#define SYSCTL_DEVCFGLOCK1_CPUSEL5    0x20U         // Lock bit for CPUSEL5 register
#define SYSCTL_DEVCFGLOCK1_CPUSEL6    0x40U         // Lock bit for CPUSEL6 register
#define SYSCTL_DEVCFGLOCK1_CPUSEL7    0x80U         // Lock bit for CPUSEL7 register
#define SYSCTL_DEVCFGLOCK1_CPUSEL8    0x100U        // Lock bit for CPUSEL8 register
#define SYSCTL_DEVCFGLOCK1_CPUSEL9    0x200U        // Lock bit for CPUSEL9 register
#define SYSCTL_DEVCFGLOCK1_CPUSEL11   0x800U        // Lock bit for CPUSEL11 register
#define SYSCTL_DEVCFGLOCK1_CPUSEL12   0x1000U       // Lock bit for CPUSEL12 register
#define SYSCTL_DEVCFGLOCK1_CPUSEL13   0x2000U       // Lock bit for CPUSEL13 register
#define SYSCTL_DEVCFGLOCK1_CPUSEL14   0x4000U       // Lock bit for CPUSEL14 register
#define SYSCTL_DEVCFGLOCK1_CPUSEL15   0x8000U       // Lock bit for CPUSEL15 register
#define SYSCTL_DEVCFGLOCK1_CPUSEL16   0x10000U      // Lock bit for CPUSEL16 register
#define SYSCTL_DEVCFGLOCK1_CPUSEL17   0x20000U      // Lock bit for CPUSEL17 register
#define SYSCTL_DEVCFGLOCK1_CPUSEL23   0x800000U     // Lock bit for CPUSEL23 register
#define SYSCTL_DEVCFGLOCK1_CPUSEL25   0x2000000U    // Lock bit for CPUSEL25 register
#define SYSCTL_DEVCFGLOCK1_CPUSEL26   0x4000000U    // Lock bit for CPUSEL26 register
#define SYSCTL_DEVCFGLOCK1_CPUSEL27   0x8000000U    // Lock bit for CPUSEL27 register
#define SYSCTL_DEVCFGLOCK1_CPUSEL28   0x10000000U   // Lock bit for CPUSEL28 register

//*************************************************************************************************
//
// The following are defines for the bit fields in the DEVCFGLOCK2 register
//
//*************************************************************************************************
#define SYSCTL_DEVCFGLOCK2_BANKMUXSEL   0x4U   // Flash Bank Mux Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the PARTIDL register
//
//*************************************************************************************************
#define SYSCTL_PARTIDL_QUAL_S         6U
#define SYSCTL_PARTIDL_QUAL_M         0xC0U       // Qualification Status
#define SYSCTL_PARTIDL_PIN_COUNT_S    8U
#define SYSCTL_PARTIDL_PIN_COUNT_M    0x700U      // Device Pin Count
#define SYSCTL_PARTIDL_FLASH_SIZE_S   16U
#define SYSCTL_PARTIDL_FLASH_SIZE_M   0xFF0000U   // FLASH_SIZE

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
// The following are defines for the bit fields in the BANKMUXSEL register
//
//*************************************************************************************************
#define SYSCTL_BANKMUXSEL_BANK0_S   0U
#define SYSCTL_BANKMUXSEL_BANK0_M   0x3U     // Select Flash Bank Controller CPU for Read accesses
#define SYSCTL_BANKMUXSEL_BANK1_S   2U
#define SYSCTL_BANKMUXSEL_BANK1_M   0xCU     // Select Flash Bank Controller CPU for Read accesses
#define SYSCTL_BANKMUXSEL_BANK2_S   4U
#define SYSCTL_BANKMUXSEL_BANK2_M   0x30U    // Select Flash Bank Controller CPU for Read accesses
#define SYSCTL_BANKMUXSEL_BANK3_S   6U
#define SYSCTL_BANKMUXSEL_BANK3_M   0xC0U    // Select Flash Bank Controller CPU for Read accesses
#define SYSCTL_BANKMUXSEL_BANK4_S   8U
#define SYSCTL_BANKMUXSEL_BANK4_M   0x300U   // Select Flash Bank Controller CPU for Read accesses

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCUCNF0 register
//
//*************************************************************************************************
#define SYSCTL_MCUCNF0_DUAL_CORE   0x1U   // User Configurable Single Core vs Dual Core

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCUCNF1 register
//
//*************************************************************************************************
#define SYSCTL_MCUCNF1_MSEL_D2   0x4U    // Controller Select for MSEL_D2
#define SYSCTL_MCUCNF1_MSEL_D3   0x8U    // Controller Select for MSEL_D3
#define SYSCTL_MCUCNF1_MSEL_D4   0x10U   // Controller Select for MSEL_D4
#define SYSCTL_MCUCNF1_MSEL_D5   0x20U   // Controller Select for MSEL_D5

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCUCNF2 register
//
//*************************************************************************************************
#define SYSCTL_MCUCNF2_ETHERCAT   0x1U   // ETHERCAT

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCUCNF3 register
//
//*************************************************************************************************
#define SYSCTL_MCUCNF3_SECT15_0      0x1U    // Flash sectors 15_0 present
#define SYSCTL_MCUCNF3_SECT31_16     0x2U    // Flash sectors 31_16 present
#define SYSCTL_MCUCNF3_SECT47_32     0x4U    // Flash sectors 47_32 present
#define SYSCTL_MCUCNF3_SECT63_48     0x8U    // Flash sectors 63_48 present
#define SYSCTL_MCUCNF3_SECT79_64     0x10U   // Flash sectors 79_64 present
#define SYSCTL_MCUCNF3_SECT95_80     0x20U   // Flash sectors 95_80 present
#define SYSCTL_MCUCNF3_SECT111_96    0x40U   // Flash sectors 111_96 present
#define SYSCTL_MCUCNF3_SECT127_112   0x80U   // Flash sectors 127_112 present

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCUCNF4 register
//
//*************************************************************************************************
#define SYSCTL_MCUCNF4_SECT15_0      0x1U    // Flash sectors 15_0 present
#define SYSCTL_MCUCNF4_SECT31_16     0x2U    // Flash sectors 31_16 present
#define SYSCTL_MCUCNF4_SECT47_32     0x4U    // Flash sectors 47_32 present
#define SYSCTL_MCUCNF4_SECT63_48     0x8U    // Flash sectors 63_48 present
#define SYSCTL_MCUCNF4_SECT79_64     0x10U   // Flash sectors 79_64 present
#define SYSCTL_MCUCNF4_SECT95_80     0x20U   // Flash sectors 95_80 present
#define SYSCTL_MCUCNF4_SECT111_96    0x40U   // Flash sectors 111_96 present
#define SYSCTL_MCUCNF4_SECT127_112   0x80U   // Flash sectors 127_112 present

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCUCNF5 register
//
//*************************************************************************************************
#define SYSCTL_MCUCNF5_SECT15_0      0x1U    // Flash sectors 15_0 present
#define SYSCTL_MCUCNF5_SECT31_16     0x2U    // Flash sectors 31_16 present
#define SYSCTL_MCUCNF5_SECT47_32     0x4U    // Flash sectors 47_32 present
#define SYSCTL_MCUCNF5_SECT63_48     0x8U    // Flash sectors 63_48 present
#define SYSCTL_MCUCNF5_SECT79_64     0x10U   // Flash sectors 79_64 present
#define SYSCTL_MCUCNF5_SECT95_80     0x20U   // Flash sectors 95_80 present
#define SYSCTL_MCUCNF5_SECT111_96    0x40U   // Flash sectors 111_96 present
#define SYSCTL_MCUCNF5_SECT127_112   0x80U   // Flash sectors 127_112 present

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCUCNF6 register
//
//*************************************************************************************************
#define SYSCTL_MCUCNF6_SECT15_0      0x1U    // Flash sectors 15_0 present
#define SYSCTL_MCUCNF6_SECT31_16     0x2U    // Flash sectors 31_16 present
#define SYSCTL_MCUCNF6_SECT47_32     0x4U    // Flash sectors 47_32 present
#define SYSCTL_MCUCNF6_SECT63_48     0x8U    // Flash sectors 63_48 present
#define SYSCTL_MCUCNF6_SECT79_64     0x10U   // Flash sectors 79_64 present
#define SYSCTL_MCUCNF6_SECT95_80     0x20U   // Flash sectors 95_80 present
#define SYSCTL_MCUCNF6_SECT111_96    0x40U   // Flash sectors 111_96 present
#define SYSCTL_MCUCNF6_SECT127_112   0x80U   // Flash sectors 127_112 present

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCUCNF7 register
//
//*************************************************************************************************
#define SYSCTL_MCUCNF7_SECT15_0      0x1U    // Flash sectors 15_0 present
#define SYSCTL_MCUCNF7_SECT31_16     0x2U    // Flash sectors 31_16 present
#define SYSCTL_MCUCNF7_SECT47_32     0x4U    // Flash sectors 47_32 present
#define SYSCTL_MCUCNF7_SECT63_48     0x8U    // Flash sectors 63_48 present
#define SYSCTL_MCUCNF7_SECT79_64     0x10U   // Flash sectors 79_64 present
#define SYSCTL_MCUCNF7_SECT95_80     0x20U   // Flash sectors 95_80 present
#define SYSCTL_MCUCNF7_SECT111_96    0x40U   // Flash sectors 111_96 present
#define SYSCTL_MCUCNF7_SECT127_112   0x80U   // Flash sectors 127_112 present

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCUCNFLOCK register
//
//*************************************************************************************************
#define SYSCTL_MCUCNFLOCK_MCUCNF0   0x1U    // Lock bit for MCUCNF0 register
#define SYSCTL_MCUCNFLOCK_MCUCNF1   0x2U    // Lock bit for MCUCNF1 register
#define SYSCTL_MCUCNFLOCK_MCUCNF2   0x4U    // Lock bit for MCUCNF2 register
#define SYSCTL_MCUCNFLOCK_MCUCNF3   0x8U    // Lock bit for MCUCNF3 register
#define SYSCTL_MCUCNFLOCK_MCUCNF4   0x10U   // Lock bit for MCUCNF4 register
#define SYSCTL_MCUCNFLOCK_MCUCNF5   0x20U   // Lock bit for MCUCNF5 register
#define SYSCTL_MCUCNFLOCK_MCUCNF6   0x40U   // Lock bit for MCUCNF6 register
#define SYSCTL_MCUCNFLOCK_MCUCNF7   0x80U   // Lock bit for MCUCNF7 register

//*************************************************************************************************
//
// The following are defines for the bit fields in the TRIMERRSTS register
//
//*************************************************************************************************
#define SYSCTL_TRIMERRSTS_LERR_S   0U
#define SYSCTL_TRIMERRSTS_LERR_M   0xFFFFU   // TRIM Load error status

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES0 register
//
//*************************************************************************************************
#define SYSCTL_SOFTPRES0_CPU1_CLA1        0x1U         // CPU1_CLA1 software reset bit
#define SYSCTL_SOFTPRES0_CPU1_CPUBGCRC    0x2000U      // CPU1 CPUBGCRC Module reset bit
#define SYSCTL_SOFTPRES0_CPU1_CLA1BGCRC   0x4000U      // CPU1 CLA1BGCRC Module reset bit
#define SYSCTL_SOFTPRES0_CPU2_CPUBGCRC    0x10000U     // CPU2 CPUBGCRC Module reset bit
#define SYSCTL_SOFTPRES0_CPU1_ERAD        0x1000000U   // ERAD Module reset bit
#define SYSCTL_SOFTPRES0_CPU2_ERAD        0x2000000U   // ERAD Module reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES1 register
//
//*************************************************************************************************
#define SYSCTL_SOFTPRES1_EMIF1   0x1U   // EMIF1 software reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES2 register
//
//*************************************************************************************************
#define SYSCTL_SOFTPRES2_EPWM1    0x1U       // EPWM1 software reset bit
#define SYSCTL_SOFTPRES2_EPWM2    0x2U       // EPWM2 software reset bit
#define SYSCTL_SOFTPRES2_EPWM3    0x4U       // EPWM3 software reset bit
#define SYSCTL_SOFTPRES2_EPWM4    0x8U       // EPWM4 software reset bit
#define SYSCTL_SOFTPRES2_EPWM5    0x10U      // EPWM5 software reset bit
#define SYSCTL_SOFTPRES2_EPWM6    0x20U      // EPWM6 software reset bit
#define SYSCTL_SOFTPRES2_EPWM7    0x40U      // EPWM7 software reset bit
#define SYSCTL_SOFTPRES2_EPWM8    0x80U      // EPWM8 software reset bit
#define SYSCTL_SOFTPRES2_EPWM9    0x100U     // EPWM9 software reset bit
#define SYSCTL_SOFTPRES2_EPWM10   0x200U     // EPWM10 software reset bit
#define SYSCTL_SOFTPRES2_EPWM11   0x400U     // EPWM11 software reset bit
#define SYSCTL_SOFTPRES2_EPWM12   0x800U     // EPWM12 software reset bit
#define SYSCTL_SOFTPRES2_EPWM13   0x1000U    // EPWM13 software reset bit
#define SYSCTL_SOFTPRES2_EPWM14   0x2000U    // EPWM14 software reset bit
#define SYSCTL_SOFTPRES2_EPWM15   0x4000U    // EPWM15 software reset bit
#define SYSCTL_SOFTPRES2_EPWM16   0x8000U    // EPWM16 software reset bit
#define SYSCTL_SOFTPRES2_EPWM17   0x10000U   // EPWM17 software reset bit
#define SYSCTL_SOFTPRES2_EPWM18   0x20000U   // EPWM18 software reset bit

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
#define SYSCTL_SOFTPRES3_ECAP7   0x40U   // ECAP7 software reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES4 register
//
//*************************************************************************************************
#define SYSCTL_SOFTPRES4_EQEP1   0x1U    // EQEP1 software reset bit
#define SYSCTL_SOFTPRES4_EQEP2   0x2U    // EQEP2 software reset bit
#define SYSCTL_SOFTPRES4_EQEP3   0x4U    // EQEP3 software reset bit
#define SYSCTL_SOFTPRES4_EQEP4   0x8U    // EQEP4 software reset bit
#define SYSCTL_SOFTPRES4_EQEP5   0x10U   // EQEP5 software reset bit
#define SYSCTL_SOFTPRES4_EQEP6   0x20U   // EQEP6 software reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES6 register
//
//*************************************************************************************************
#define SYSCTL_SOFTPRES6_SD1   0x1U   // SD1 software reset bit
#define SYSCTL_SOFTPRES6_SD2   0x2U   // SD2 software reset bit
#define SYSCTL_SOFTPRES6_SD3   0x4U   // SD3 software reset bit
#define SYSCTL_SOFTPRES6_SD4   0x8U   // SD4 software reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES7 register
//
//*************************************************************************************************
#define SYSCTL_SOFTPRES7_SCI_A    0x1U       // SCI_A software reset bit
#define SYSCTL_SOFTPRES7_SCI_B    0x2U       // SCI_B software reset bit
#define SYSCTL_SOFTPRES7_UART_A   0x10000U   // UART_A software reset bit
#define SYSCTL_SOFTPRES7_UART_B   0x20000U   // UART_B software reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES8 register
//
//*************************************************************************************************
#define SYSCTL_SOFTPRES8_SPI_A   0x1U   // SPI_A software reset bit
#define SYSCTL_SOFTPRES8_SPI_B   0x2U   // SPI_B software reset bit
#define SYSCTL_SOFTPRES8_SPI_C   0x4U   // SPI_C software reset bit
#define SYSCTL_SOFTPRES8_SPI_D   0x8U   // SPI_D software reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES9 register
//
//*************************************************************************************************
#define SYSCTL_SOFTPRES9_I2C_A     0x1U       // I2C_A software reset bit
#define SYSCTL_SOFTPRES9_I2C_B     0x2U       // I2C_B software reset bit
#define SYSCTL_SOFTPRES9_PMBUS_A   0x10000U   // PMBUS_A software reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES10 register
//
//*************************************************************************************************
#define SYSCTL_SOFTPRES10_CAN_A    0x1U    // CAN_A software reset bit
#define SYSCTL_SOFTPRES10_MCAN_A   0x10U   // MCAN_A  software reset bit
#define SYSCTL_SOFTPRES10_MCAN_B   0x20U   // MCAN_B  software reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES11 register
//
//*************************************************************************************************
#define SYSCTL_SOFTPRES11_USB_A   0x10000U   // USB_A software reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES13 register
//
//*************************************************************************************************
#define SYSCTL_SOFTPRES13_ADC_A   0x1U   // ADC_A software reset bit
#define SYSCTL_SOFTPRES13_ADC_B   0x2U   // ADC_B software reset bit
#define SYSCTL_SOFTPRES13_ADC_C   0x4U   // ADC_C software reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES14 register
//
//*************************************************************************************************
#define SYSCTL_SOFTPRES14_CMPSS1    0x1U     // CMPSS1 software reset bit
#define SYSCTL_SOFTPRES14_CMPSS2    0x2U     // CMPSS2 software reset bit
#define SYSCTL_SOFTPRES14_CMPSS3    0x4U     // CMPSS3 software reset bit
#define SYSCTL_SOFTPRES14_CMPSS4    0x8U     // CMPSS4 software reset bit
#define SYSCTL_SOFTPRES14_CMPSS5    0x10U    // CMPSS5 software reset bit
#define SYSCTL_SOFTPRES14_CMPSS6    0x20U    // CMPSS6 software reset bit
#define SYSCTL_SOFTPRES14_CMPSS7    0x40U    // CMPSS7 software reset bit
#define SYSCTL_SOFTPRES14_CMPSS8    0x80U    // CMPSS8 software reset bit
#define SYSCTL_SOFTPRES14_CMPSS9    0x100U   // CMPSS9 software reset bit
#define SYSCTL_SOFTPRES14_CMPSS10   0x200U   // CMPSS10 software reset bit
#define SYSCTL_SOFTPRES14_CMPSS11   0x400U   // CMPSS11 software reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES16 register
//
//*************************************************************************************************
#define SYSCTL_SOFTPRES16_DAC_A   0x10000U   // Buffered_DAC_A software reset bit
#define SYSCTL_SOFTPRES16_DAC_C   0x40000U   // Buffered_DAC_C software reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES17 register
//
//*************************************************************************************************
#define SYSCTL_SOFTPRES17_CLB1   0x1U    // CLB1 software reset bit
#define SYSCTL_SOFTPRES17_CLB2   0x2U    // CLB2 software reset bit
#define SYSCTL_SOFTPRES17_CLB3   0x4U    // CLB3 software reset bit
#define SYSCTL_SOFTPRES17_CLB4   0x8U    // CLB4 software reset bit
#define SYSCTL_SOFTPRES17_CLB5   0x10U   // CLB5 software reset bit
#define SYSCTL_SOFTPRES17_CLB6   0x20U   // CLB6 software reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES18 register
//
//*************************************************************************************************
#define SYSCTL_SOFTPRES18_FSITX_A   0x1U       // FSITX_A software reset bit
#define SYSCTL_SOFTPRES18_FSITX_B   0x2U       // FSITX_B software reset bit
#define SYSCTL_SOFTPRES18_FSIRX_A   0x10000U   // FSIRX_A software reset bit
#define SYSCTL_SOFTPRES18_FSIRX_B   0x20000U   // FSIRX_B software reset bit
#define SYSCTL_SOFTPRES18_FSIRX_C   0x40000U   // FSIRX_C software reset bit
#define SYSCTL_SOFTPRES18_FSIRX_D   0x80000U   // FSIRX_D software reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES19 register
//
//*************************************************************************************************
#define SYSCTL_SOFTPRES19_LIN_A   0x1U   // LIN_A software reset bit
#define SYSCTL_SOFTPRES19_LIN_B   0x2U   // LIN_B software reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES21 register
//
//*************************************************************************************************
#define SYSCTL_SOFTPRES21_DCC0   0x1U   // DCC Module reset bit
#define SYSCTL_SOFTPRES21_DCC1   0x2U   // DCC Module reset bit
#define SYSCTL_SOFTPRES21_DCC2   0x4U   // DCC Module reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES23 register
//
//*************************************************************************************************
#define SYSCTL_SOFTPRES23_ETHERCAT   0x1U   // ETHERCAT Module reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SOFTPRES26 register
//
//*************************************************************************************************
#define SYSCTL_SOFTPRES26_AESA   0x1U   // AES Module Reset Bit

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
// The following are defines for the bit fields in the SOFTPRES29 register
//
//*************************************************************************************************
#define SYSCTL_SOFTPRES29_ADCCHECKER1     0x1U       // ADCCHECKER1 software reset bit
#define SYSCTL_SOFTPRES29_ADCCHECKER2     0x2U       // ADCCHECKER2 software reset bit
#define SYSCTL_SOFTPRES29_ADCCHECKER3     0x4U       // ADCCHECKER3 software reset bit
#define SYSCTL_SOFTPRES29_ADCCHECKER4     0x8U       // ADCCHECKER4 software reset bit
#define SYSCTL_SOFTPRES29_ADCCHECKER5     0x10U      // ADCCHECKER5 software reset bit
#define SYSCTL_SOFTPRES29_ADCCHECKER6     0x20U      // ADCCHECKER6 software reset bit
#define SYSCTL_SOFTPRES29_ADCCHECKER7     0x40U      // ADCCHECKER7 software reset bit
#define SYSCTL_SOFTPRES29_ADCCHECKER8     0x80U      // ADCCHECKER8 software reset bit
#define SYSCTL_SOFTPRES29_ADCSEAGGRCPU1   0x10000U   // ADCSEAGGRCPU1 software reset bit
#define SYSCTL_SOFTPRES29_ADCSEAGGRCPU2   0x20000U   // ADCSEAGGRCPU2 software reset bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the CPUSEL0 register
//
//*************************************************************************************************
#define SYSCTL_CPUSEL0_EPWM1    0x1U       // EPWM1 CPU select bit
#define SYSCTL_CPUSEL0_EPWM2    0x2U       // EPWM2 CPU select bit
#define SYSCTL_CPUSEL0_EPWM3    0x4U       // EPWM3 CPU select bit
#define SYSCTL_CPUSEL0_EPWM4    0x8U       // EPWM4 CPU select bit
#define SYSCTL_CPUSEL0_EPWM5    0x10U      // EPWM5 CPU select bit
#define SYSCTL_CPUSEL0_EPWM6    0x20U      // EPWM6 CPU select bit
#define SYSCTL_CPUSEL0_EPWM7    0x40U      // EPWM7 CPU select bit
#define SYSCTL_CPUSEL0_EPWM8    0x80U      // EPWM8 CPU select bit
#define SYSCTL_CPUSEL0_EPWM9    0x100U     // EPWM9 CPU select bit
#define SYSCTL_CPUSEL0_EPWM10   0x200U     // EPWM10 CPU select bit
#define SYSCTL_CPUSEL0_EPWM11   0x400U     // EPWM11 CPU select bit
#define SYSCTL_CPUSEL0_EPWM12   0x800U     // EPWM12 CPU select bit
#define SYSCTL_CPUSEL0_EPWM13   0x1000U    // EPWM13 CPU select bit
#define SYSCTL_CPUSEL0_EPWM14   0x2000U    // EPWM14 CPU select bit
#define SYSCTL_CPUSEL0_EPWM15   0x4000U    // EPWM15 CPU select bit
#define SYSCTL_CPUSEL0_EPWM16   0x8000U    // EPWM16 CPU select bit
#define SYSCTL_CPUSEL0_EPWM17   0x10000U   // EPWM17 CPU select bit
#define SYSCTL_CPUSEL0_EPWM18   0x20000U   // EPWM18 CPU select bit

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
#define SYSCTL_CPUSEL1_ECAP7   0x40U   // ECAP7 CPU select bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the CPUSEL2 register
//
//*************************************************************************************************
#define SYSCTL_CPUSEL2_EQEP1   0x1U    // EQEP1 CPU select bit
#define SYSCTL_CPUSEL2_EQEP2   0x2U    // EQEP2 CPU select bit
#define SYSCTL_CPUSEL2_EQEP3   0x4U    // EQEP3 CPU select bit
#define SYSCTL_CPUSEL2_EQEP4   0x8U    // EQEP4 CPU select bit
#define SYSCTL_CPUSEL2_EQEP5   0x10U   // EQEP5 CPU select bit
#define SYSCTL_CPUSEL2_EQEP6   0x20U   // EQEP6 CPU select bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the CPUSEL3 register
//
//*************************************************************************************************
#define SYSCTL_CPUSEL3_HRCAP6   0x20U   // HRCAP6 CPU select bit
#define SYSCTL_CPUSEL3_HRCAP7   0x40U   // HRCAP7 CPU select bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the CPUSEL4 register
//
//*************************************************************************************************
#define SYSCTL_CPUSEL4_SD1   0x1U   // SD1 CPU select bit
#define SYSCTL_CPUSEL4_SD2   0x2U   // SD2 CPU select bit
#define SYSCTL_CPUSEL4_SD3   0x4U   // SD3 CPU select bit
#define SYSCTL_CPUSEL4_SD4   0x8U   // SD4 CPU select bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the CPUSEL5 register
//
//*************************************************************************************************
#define SYSCTL_CPUSEL5_SCI_A    0x1U       // SCI_A CPU select bit
#define SYSCTL_CPUSEL5_SCI_B    0x2U       // SCI_B CPU select bit
#define SYSCTL_CPUSEL5_UART_A   0x10000U   // UART_A CPU select bit
#define SYSCTL_CPUSEL5_UART_B   0x20000U   // UART_B CPU select bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the CPUSEL6 register
//
//*************************************************************************************************
#define SYSCTL_CPUSEL6_SPI_A   0x1U   // SPI_A CPU select bit
#define SYSCTL_CPUSEL6_SPI_B   0x2U   // SPI_B CPU select bit
#define SYSCTL_CPUSEL6_SPI_C   0x4U   // SPI_C CPU select bit
#define SYSCTL_CPUSEL6_SPI_D   0x8U   // SPI_D CPU select bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the CPUSEL7 register
//
//*************************************************************************************************
#define SYSCTL_CPUSEL7_I2C_A     0x1U       // I2C_A CPU select bit
#define SYSCTL_CPUSEL7_I2C_B     0x2U       // I2C_B CPU select bit
#define SYSCTL_CPUSEL7_PMBUS_A   0x10000U   // PMBUS_A CPU select bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the CPUSEL8 register
//
//*************************************************************************************************
#define SYSCTL_CPUSEL8_CAN_A    0x1U    // CAN_A CPU select bit
#define SYSCTL_CPUSEL8_MCAN_A   0x10U   // MCAN_A CPU select bit
#define SYSCTL_CPUSEL8_MCAN_B   0x20U   // MCAN_B CPU select bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the CPUSEL9 register
//
//*************************************************************************************************
#define SYSCTL_CPUSEL9_USB_A   0x10000U   // USB_A CPU select bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the CPUSEL11 register
//
//*************************************************************************************************
#define SYSCTL_CPUSEL11_ADC_A   0x1U   // ADC_A CPU select bit
#define SYSCTL_CPUSEL11_ADC_B   0x2U   // ADC_B CPU select bit
#define SYSCTL_CPUSEL11_ADC_C   0x4U   // ADC_C CPU select bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the CPUSEL12 register
//
//*************************************************************************************************
#define SYSCTL_CPUSEL12_CMPSS1    0x1U     // CMPSS1 CPU select bit
#define SYSCTL_CPUSEL12_CMPSS2    0x2U     // CMPSS2 CPU select bit
#define SYSCTL_CPUSEL12_CMPSS3    0x4U     // CMPSS3 CPU select bit
#define SYSCTL_CPUSEL12_CMPSS4    0x8U     // CMPSS4 CPU select bit
#define SYSCTL_CPUSEL12_CMPSS5    0x10U    // CMPSS5 CPU select bit
#define SYSCTL_CPUSEL12_CMPSS6    0x20U    // CMPSS6 CPU select bit
#define SYSCTL_CPUSEL12_CMPSS7    0x40U    // CMPSS7 CPU select bit
#define SYSCTL_CPUSEL12_CMPSS8    0x80U    // CMPSS8 CPU select bit
#define SYSCTL_CPUSEL12_CMPSS9    0x100U   // CMPSS9 CPU select bit
#define SYSCTL_CPUSEL12_CMPSS10   0x200U   // CMPSS10 CPU select bit
#define SYSCTL_CPUSEL12_CMPSS11   0x400U   // CMPSS11 CPU select bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the CPUSEL13 register
//
//*************************************************************************************************
#define SYSCTL_CPUSEL13_DCC0   0x1U   // DCC0 CPU select bit
#define SYSCTL_CPUSEL13_DCC1   0x2U   // DCC1 CPU select bit
#define SYSCTL_CPUSEL13_DCC2   0x4U   // DCC2 CPU select bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the CPUSEL14 register
//
//*************************************************************************************************
#define SYSCTL_CPUSEL14_DAC_A   0x10000U   // Buffered_DAC_A CPU select bit
#define SYSCTL_CPUSEL14_DAC_C   0x40000U   // Buffered_DAC_C CPU select bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the CPUSEL15 register
//
//*************************************************************************************************
#define SYSCTL_CPUSEL15_CLB1   0x1U    // CLB1 CPU select bit
#define SYSCTL_CPUSEL15_CLB2   0x2U    // CLB2 CPU select bit
#define SYSCTL_CPUSEL15_CLB3   0x4U    // CLB3 CPU select bit
#define SYSCTL_CPUSEL15_CLB4   0x8U    // CLB4 CPU select bit
#define SYSCTL_CPUSEL15_CLB5   0x10U   // CLB5 CPU select bit
#define SYSCTL_CPUSEL15_CLB6   0x20U   // CLB6 CPU select bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the CPUSEL16 register
//
//*************************************************************************************************
#define SYSCTL_CPUSEL16_FSITX_A   0x1U       // FSITX_A CPU select bit
#define SYSCTL_CPUSEL16_FSITX_B   0x2U       // FSITX_B CPU select bit
#define SYSCTL_CPUSEL16_FSIRX_A   0x10000U   // FSIRX_A CPU select bit
#define SYSCTL_CPUSEL16_FSIRX_B   0x20000U   // FSIRX_B CPU select bit
#define SYSCTL_CPUSEL16_FSIRX_C   0x40000U   // FSIRX_C CPU select bit
#define SYSCTL_CPUSEL16_FSIRX_D   0x80000U   // FSIRX_D CPU select bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the CPUSEL17 register
//
//*************************************************************************************************
#define SYSCTL_CPUSEL17_LIN_A   0x1U   // LIN_A CPU select bit
#define SYSCTL_CPUSEL17_LIN_B   0x2U   // LIN_B CPU select bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the CPUSEL23 register
//
//*************************************************************************************************
#define SYSCTL_CPUSEL23_ETHERCAT   0x1U   // 0 CPU select bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the CPUSEL25 register
//
//*************************************************************************************************
#define SYSCTL_CPUSEL25_HRCAL0   0x1U   // HRCAL0 CPU select bit
#define SYSCTL_CPUSEL25_HRCAL1   0x2U   // HRCAL1 CPU select bit
#define SYSCTL_CPUSEL25_HRCAL2   0x4U   // HRCAL2 CPU select bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the CPUSEL26 register
//
//*************************************************************************************************
#define SYSCTL_CPUSEL26_AESA   0x1U   // AESA CPU select bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the CPUSEL27 register
//
//*************************************************************************************************
#define SYSCTL_CPUSEL27_EPG1   0x1U   // EPG1 CPU select bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the CPUSEL28 register
//
//*************************************************************************************************
#define SYSCTL_CPUSEL28_ADCCHECKER1   0x1U    // ADCCHECKER1 CPU select bit
#define SYSCTL_CPUSEL28_ADCCHECKER2   0x2U    // ADCCHECKER2 CPU select bit
#define SYSCTL_CPUSEL28_ADCCHECKER3   0x4U    // ADCCHECKER3 CPU select bit
#define SYSCTL_CPUSEL28_ADCCHECKER4   0x8U    // ADCCHECKER4 CPU select bit
#define SYSCTL_CPUSEL28_ADCCHECKER5   0x10U   // ADCCHECKER5 CPU select bit
#define SYSCTL_CPUSEL28_ADCCHECKER6   0x20U   // ADCCHECKER6 CPU select bit
#define SYSCTL_CPUSEL28_ADCCHECKER7   0x40U   // ADCCHECKER7 CPU select bit
#define SYSCTL_CPUSEL28_ADCCHECKER8   0x80U   // ADCCHECKER8 CPU select bit

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
#define SYSCTL_RSTSTAT_CPU2RES        0x1U   // CPU2 Reset Status bit
#define SYSCTL_RSTSTAT_CPU2NMIWDRST   0x2U   // Indicates whether a CPU2.NMIWD reset was issued to
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
// The following are defines for the bit fields in the TAP_STATUS register
//
//*************************************************************************************************
#define SYSCTL_TAP_STATUS_TAP_STATE_S   0U
#define SYSCTL_TAP_STATUS_TAP_STATE_M   0xFFFFU       // Present TAP State
#define SYSCTL_TAP_STATUS_DCON          0x80000000U   // Debugger Connect Indication

//*************************************************************************************************
//
// The following are defines for the bit fields in the TAP_CONTROL register
//
//*************************************************************************************************
#define SYSCTL_TAP_CONTROL_BSCAN_DIS   0x1U          // Disable BSCAN TAP control
#define SYSCTL_TAP_CONTROL_KEY_S       16U
#define SYSCTL_TAP_CONTROL_KEY_M       0xFFFF0000U   // Key value to enable write

//*************************************************************************************************
//
// The following are defines for the bit fields in the USBTYPE register
//
//*************************************************************************************************
#define SYSCTL_USBTYPE_TYPE_S   0U
#define SYSCTL_USBTYPE_TYPE_M   0x3U      // Configure USB type
#define SYSCTL_USBTYPE_LOCK     0x8000U   // Lock bit

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
// The following are defines for the bit fields in the SDFMTYPE register
//
//*************************************************************************************************
#define SYSCTL_SDFMTYPE_TYPE_S   0U
#define SYSCTL_SDFMTYPE_TYPE_M   0x3U      // Configure SDFM type
#define SYSCTL_SDFMTYPE_LOCK     0x8000U   // Lock bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the MEMMAPTYPE register
//
//*************************************************************************************************
#define SYSCTL_MEMMAPTYPE_TYPE_S   0U
#define SYSCTL_MEMMAPTYPE_TYPE_M   0x3U      // Configures system specific features related to
                                             // memory map.
#define SYSCTL_MEMMAPTYPE_LOCK     0x8000U   // Lock bit


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
#define SYSCTL_CLKCFGLOCK1_CLKSRCCTL1       0x1U       // Lock bit for CLKSRCCTL1 register
#define SYSCTL_CLKCFGLOCK1_CLKSRCCTL2       0x2U       // Lock bit for CLKSRCCTL2 register
#define SYSCTL_CLKCFGLOCK1_CLKSRCCTL3       0x4U       // Lock bit for CLKSRCCTL3 register
#define SYSCTL_CLKCFGLOCK1_SYSPLLCTL1       0x8U       // Lock bit for SYSPLLCTL1 register
#define SYSCTL_CLKCFGLOCK1_SYSPLLMULT       0x40U      // Lock bit for SYSPLLMULT register
#define SYSCTL_CLKCFGLOCK1_AUXPLLCTL1       0x80U      // Lock bit for AUXPLLCTL1 register
#define SYSCTL_CLKCFGLOCK1_AUXPLLMULT       0x400U     // Lock bit for AUXPLLMULT register
#define SYSCTL_CLKCFGLOCK1_SYSCLKDIVSEL     0x800U     // Lock bit for SYSCLKDIVSEL register
#define SYSCTL_CLKCFGLOCK1_AUXCLKDIVSEL     0x1000U    // Lock bit for AUXCLKDIVSEL register
#define SYSCTL_CLKCFGLOCK1_PERCLKDIVSEL     0x2000U    // Lock bit for PERCLKDIVSEL register
#define SYSCTL_CLKCFGLOCK1_CLBCLKCTL        0x4000U    // Lock bit for CLBCLKCTL register
#define SYSCTL_CLKCFGLOCK1_LOSPCP           0x8000U    // Lock bit for LOSPCP register
#define SYSCTL_CLKCFGLOCK1_XTALCR           0x10000U   // Lock bit for XTALCR  & XTALCR2 register
#define SYSCTL_CLKCFGLOCK1_EXTRFLTDET       0x20000U   // Lockbit for EXTRFLTDET register
#define SYSCTL_CLKCFGLOCK1_ETHERCATCLKCTL   0x40000U   // Lockbit for ETHERCATCLKCTL register

//*************************************************************************************************
//
// The following are defines for the bit fields in the CLKSRCCTL1 register
//
//*************************************************************************************************
#define SYSCTL_CLKSRCCTL1_OSCCLKSRCSEL_S   0U
#define SYSCTL_CLKSRCCTL1_OSCCLKSRCSEL_M   0x3U    // OSCCLK Source Select Bit
#define SYSCTL_CLKSRCCTL1_WDHALTI          0x20U   // Watchdog HALT Mode Ignore Bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the CLKSRCCTL2 register
//
//*************************************************************************************************
#define SYSCTL_CLKSRCCTL2_AUXOSCCLKSRCSEL_S   0U
#define SYSCTL_CLKSRCCTL2_AUXOSCCLKSRCSEL_M   0x3U      // AUXOSCCLK Source Select Bit
#define SYSCTL_CLKSRCCTL2_CANABCLKSEL_S       2U
#define SYSCTL_CLKSRCCTL2_CANABCLKSEL_M       0xCU      // CANA Bit Clock Source Select Bit
#define SYSCTL_CLKSRCCTL2_MCANABCLKSEL_S      10U
#define SYSCTL_CLKSRCCTL2_MCANABCLKSEL_M      0xC00U    // MCANA Bit Clock Source Select Bit
#define SYSCTL_CLKSRCCTL2_MCANBBCLKSEL_S      12U
#define SYSCTL_CLKSRCCTL2_MCANBBCLKSEL_M      0x3000U   // MCANB Bit Clock Source Select Bit

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
#define SYSCTL_AUXPLLMULT_IMULT_S    0U
#define SYSCTL_AUXPLLMULT_IMULT_M    0xFFU         // AUXPLL Integer Multiplier
#define SYSCTL_AUXPLLMULT_ODIV_S     16U
#define SYSCTL_AUXPLLMULT_ODIV_M     0x1F0000U     // Output Clock Divider
#define SYSCTL_AUXPLLMULT_REFDIV_S   24U
#define SYSCTL_AUXPLLMULT_REFDIV_M   0x1F000000U   // Reference Clock Divider

//*************************************************************************************************
//
// The following are defines for the bit fields in the AUXPLLSTS register
//
//*************************************************************************************************
#define SYSCTL_AUXPLLSTS_LOCKS                0x1U   // AUXPLL Lock Status Bit
#define SYSCTL_AUXPLLSTS_SLIPS_NOTSUPPORTED   0x2U   // AUXPLL Slip Status Bit
#define SYSCTL_AUXPLLSTS_REF_LOSTS            0x8U   // AUXPLL "Reference  Lost" Status Bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SYSCLKDIVSEL register
//
//*************************************************************************************************
#define SYSCTL_SYSCLKDIVSEL_PLLSYSCLKDIV_S     0U
#define SYSCTL_SYSCLKDIVSEL_PLLSYSCLKDIV_M     0x3FU    // PLLSYSCLK Divide Select
#define SYSCTL_SYSCLKDIVSEL_PLLSYSCLKDIV_LSB   0x100U   // PLLSYSCLKDIV_LSB Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the AUXCLKDIVSEL register
//
//*************************************************************************************************
#define SYSCTL_AUXCLKDIVSEL_AUXPLLDIV_S     0U
#define SYSCTL_AUXCLKDIVSEL_AUXPLLDIV_M     0x7U       // AUXPLLCLK Divide Select
#define SYSCTL_AUXCLKDIVSEL_MCANACLKDIV_S   8U
#define SYSCTL_AUXCLKDIVSEL_MCANACLKDIV_M   0x1F00U    // Divider CANFD Bit CLK for MCANA
#define SYSCTL_AUXCLKDIVSEL_MCANBCLKDIV_S   13U
#define SYSCTL_AUXCLKDIVSEL_MCANBCLKDIV_M   0x3E000U   // Divider CANFD Bit CLK for MCANB

//*************************************************************************************************
//
// The following are defines for the bit fields in the PERCLKDIVSEL register
//
//*************************************************************************************************
#define SYSCTL_PERCLKDIVSEL_EPWMCLKDIV_S   0U
#define SYSCTL_PERCLKDIVSEL_EPWMCLKDIV_M   0x3U      // EPWM Clock Divide Select
#define SYSCTL_PERCLKDIVSEL_EMIF1CLKDIV    0x10U     // EMIF1  Clock Divide Select
#define SYSCTL_PERCLKDIVSEL_LINACLKDIV_S   8U
#define SYSCTL_PERCLKDIVSEL_LINACLKDIV_M   0x300U    // LINA Clock Divide Select
#define SYSCTL_PERCLKDIVSEL_LINBCLKDIV_S   11U
#define SYSCTL_PERCLKDIVSEL_LINBCLKDIV_M   0x1800U   // LINB Clock Divide Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the XCLKOUTDIVSEL register
//
//*************************************************************************************************
#define SYSCTL_XCLKOUTDIVSEL_XCLKOUTDIV_S   0U
#define SYSCTL_XCLKOUTDIVSEL_XCLKOUTDIV_M   0x3U   // XCLKOUT Divide Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the CLBCLKCTL register
//
//*************************************************************************************************
#define SYSCTL_CLBCLKCTL_CLKMODECLB1   0x10000U    // Clock mode of CLB1
#define SYSCTL_CLBCLKCTL_CLKMODECLB2   0x20000U    // Clock mode of CLB2
#define SYSCTL_CLBCLKCTL_CLKMODECLB3   0x40000U    // Clock mode of CLB3
#define SYSCTL_CLBCLKCTL_CLKMODECLB4   0x80000U    // Clock mode of CLB4
#define SYSCTL_CLBCLKCTL_CLKMODECLB5   0x100000U   // Clock mode of CLB5
#define SYSCTL_CLBCLKCTL_CLKMODECLB6   0x200000U   // Clock mode of CLB6

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
#define SYSCTL_MCDCR_MCLKSTS              0x1U      // Missing Clock Status Bit
#define SYSCTL_MCDCR_MCLKCLR              0x2U      // Missing Clock Clear Bit
#define SYSCTL_MCDCR_MCLKOFF              0x4U      // Missing Clock Detect Off Bit
#define SYSCTL_MCDCR_OSCOFF               0x8U      // Oscillator Clock Off Bit
#define SYSCTL_MCDCR_SYSREF_LOSTS         0x10U     // SYSPLL "Reference  Lost" Status Bit
#define SYSCTL_MCDCR_SYSREF_LOSTSCLR      0x20U     // Clear for Ref clock lost status
#define SYSCTL_MCDCR_SYSREF_LOST_MCD_EN   0x40U     // Enable for PLL REF_CLK_LOST as MCD cause
#define SYSCTL_MCDCR_AUXREF_LOSTS         0x80U     // AUXPLL "Reference  Lost" Status Bit
#define SYSCTL_MCDCR_AUXREF_LOSTSCLR      0x100U    // Clear for Ref clock lost status
#define SYSCTL_MCDCR_AUXREF_LOST_MCD_EN   0x200U    // Enable for PLL REF_CLK_LOST as MCD cause
#define SYSCTL_MCDCR_EXTR_FAULTS          0x400U    // External Resistor fault indication
#define SYSCTL_MCDCR_EXTR_FAULTSCLR       0x800U    // External Resistor fault status clear
#define SYSCTL_MCDCR_EXTR_FAULT_MCD_EN    0x1000U   // Configuration to enable EXTR_FAULTS as MCD
                                                    // cause

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
#define SYSCTL_CLKFAILCFG_DCC1_ERROR_EN   0x2U   // DCC1 Error causes Clock fail NMI, ERROR
#define SYSCTL_CLKFAILCFG_DCC2_ERROR_EN   0x4U   // DCC2 Error causes Clock fail NMI, ERROR

//*************************************************************************************************
//
// The following are defines for the bit fields in the ETHERCATCLKCTL register
//
//*************************************************************************************************
#define SYSCTL_ETHERCATCLKCTL_DIVSRCSEL   0x1U     // Clock source select for the etherCAT clock
                                                   // divider.
#define SYSCTL_ETHERCATCLKCTL_ECATDIV_S   1U
#define SYSCTL_ETHERCATCLKCTL_ECATDIV_M   0xEU     // etherCAT clock divider configuration.
#define SYSCTL_ETHERCATCLKCTL_PHYCLKEN    0x100U   // etherCAT PHY clock enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the SYNCBUSY register
//
//*************************************************************************************************
#define SYSCTL_SYNCBUSY_BUSY             0x1U          // Status bit indicating synchronization in
                                                       // progress
#define SYSCTL_SYNCBUSY_AUXCLKDIVSEL     0x10000U      // BUSY status bit for AUXCLKDIVSEL
#define SYSCTL_SYNCBUSY_AUXPLLMULT       0x20000U      // BUSY status bit for AUXPLLMULT
#define SYSCTL_SYNCBUSY_CLBCLKCTL        0x40000U      // BUSY status bit for CLBCLKCTL
#define SYSCTL_SYNCBUSY_ETHERCATCLKCTL   0x80000U      // BUSY status bit for ETHERCATCLKCTL
#define SYSCTL_SYNCBUSY_PERCLKDIVSEL     0x100000U     // BUSY status bit for PERCLKDIVSEL
#define SYSCTL_SYNCBUSY_SYSCLKDIVSEL     0x200000U     // BUSY status bit for SYSCLKDIVSEL
#define SYSCTL_SYNCBUSY_SYSPLLCTL1       0x400000U     // BUSY status bit for SYSPLLCTL1
#define SYSCTL_SYNCBUSY_SYSPLLMULT       0x800000U     // BUSY status bit for SYSPLLMULT
#define SYSCTL_SYNCBUSY_XCLKOUTDIVSEL    0x2000000U    // BUSY status bit for XCLKOUTDIVSEL
#define SYSCTL_SYNCBUSY_XTALCR           0x4000000U    // BUSY status bit for XTALCR
#define SYSCTL_SYNCBUSY_CLKSRCCTL1       0x8000000U    // BUSY status bit for CLKSRCCTL1
#define SYSCTL_SYNCBUSY_CLKSRCCTL2       0x10000000U   // BUSY status bit for CLKSRCCTL2
#define SYSCTL_SYNCBUSY_CLKSRCCTL3       0x20000000U   // BUSY status bit for CLKSRCCTL3
#define SYSCTL_SYNCBUSY_CPU1TMR2CTL      0x40000000U   // BUSY status bit for CPU1TMR2CTL
#define SYSCTL_SYNCBUSY_CPU2TMR2CTL      0x80000000U   // BUSY status bit for CPU2TMR2CTL


//*************************************************************************************************
//
// The following are defines for the bit fields in the CPUSYSLOCK1 register
//
//*************************************************************************************************
#define SYSCTL_CPUSYSLOCK1_PIEVERRADDR   0x4U          // Lock bit for PIEVERRADDR Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR0       0x8U          // Lock bit for PCLKCR0 Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR1       0x10U         // Lock bit for PCLKCR1 Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR2       0x20U         // Lock bit for PCLKCR2 Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR3       0x40U         // Lock bit for PCLKCR3 Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR4       0x80U         // Lock bit for PCLKCR4 Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR6       0x200U        // Lock bit for PCLKCR6 Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR7       0x400U        // Lock bit for PCLKCR7 Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR8       0x800U        // Lock bit for PCLKCR8 Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR9       0x1000U       // Lock bit for PCLKCR9 Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR10      0x2000U       // Lock bit for PCLKCR10 Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR11      0x4000U       // Lock bit for PCLKCR11 Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR13      0x10000U      // Lock bit for PCLKCR13 Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR14      0x20000U      // Lock bit for PCLKCR14 Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR16      0x80000U      // Lock bit for PCLKCR16 Register
#define SYSCTL_CPUSYSLOCK1_LPMCR         0x200000U     // Lock bit for LPMCR Register
#define SYSCTL_CPUSYSLOCK1_GPIOLPMSEL0   0x400000U     // Lock bit for GPIOLPMSEL0 Register
#define SYSCTL_CPUSYSLOCK1_GPIOLPMSEL1   0x800000U     // Lock bit for GPIOLPMSEL1 Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR17      0x1000000U    // Lock bit for PCLKCR17 Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR18      0x2000000U    // Lock bit for PCLKCR18 Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR19      0x4000000U    // Lock bit for PCLKCR19 Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR21      0x10000000U   // Lock bit for PCLKCR21 Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR22      0x20000000U   // Lock bit for PCLKCR22 Register
#define SYSCTL_CPUSYSLOCK1_PCLKCR23      0x40000000U   // Lock bit for PCLKCR23 Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the CPUSYSLOCK2 register
//
//*************************************************************************************************
#define SYSCTL_CPUSYSLOCK2_ETHERCATCTL          0x1U          // Lock bit for ETHERCATCTL register
#define SYSCTL_CPUSYSLOCK2_PCLKCR25             0x2U          // Lock bit for PCLKCR25 Register
#define SYSCTL_CPUSYSLOCK2_PCLKCR26             0x4U          // Lock bit for PCLKCR26 Register
#define SYSCTL_CPUSYSLOCK2_PCLKCR27             0x8U          // Lock bit for PCLKCR27 Register
#define SYSCTL_CPUSYSLOCK2_LSEN                 0x10U         // Lock bit for LSEN Register
#define SYSCTL_CPUSYSLOCK2_CMPSSLPMSEL          0x20U         // Lock bit for CMPSSLPMSEL register
#define SYSCTL_CPUSYSLOCK2_PCLKCR28             0x40U         // Lock bit for PCLKCR28 Register
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
// The following are defines for the bit fields in the ETHERCATCTL register
//
//*************************************************************************************************
#define SYSCTL_ETHERCATCTL_I2CLOOPBACK   0x1U   // Loopback I2C port of etherCAT IP to I2C_A.

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCLKCR0 register
//
//*************************************************************************************************
#define SYSCTL_PCLKCR0_CLA1         0x1U         // CLA1 Clock Enable Bit
#define SYSCTL_PCLKCR0_DMA          0x4U         // DMA Clock Enable bit
#define SYSCTL_PCLKCR0_CPUTIMER0    0x8U         // CPUTIMER0 Clock Enable bit
#define SYSCTL_PCLKCR0_CPUTIMER1    0x10U        // CPUTIMER1 Clock Enable bit
#define SYSCTL_PCLKCR0_CPUTIMER2    0x20U        // CPUTIMER2 Clock Enable bit
#define SYSCTL_PCLKCR0_CPUBGCRC     0x2000U      // CPUBGCRC Clock Enable Bit
#define SYSCTL_PCLKCR0_CLA1BGCRC    0x4000U      // CLA1BGCRC Clock Enable Bit
#define SYSCTL_PCLKCR0_TBCLKSYNC    0x40000U     // EPWM Time Base Clock sync
#define SYSCTL_PCLKCR0_GTBCLKSYNC   0x80000U     // EPWM Time Base Clock Global sync
#define SYSCTL_PCLKCR0_ERAD         0x1000000U   // ERAD module clock enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCLKCR1 register
//
//*************************************************************************************************
#define SYSCTL_PCLKCR1_EMIF1   0x1U   // EMIF1 Clock Enable bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCLKCR2 register
//
//*************************************************************************************************
#define SYSCTL_PCLKCR2_EPWM1    0x1U       // EPWM1 Clock Enable bit
#define SYSCTL_PCLKCR2_EPWM2    0x2U       // EPWM2 Clock Enable bit
#define SYSCTL_PCLKCR2_EPWM3    0x4U       // EPWM3 Clock Enable bit
#define SYSCTL_PCLKCR2_EPWM4    0x8U       // EPWM4 Clock Enable bit
#define SYSCTL_PCLKCR2_EPWM5    0x10U      // EPWM5 Clock Enable bit
#define SYSCTL_PCLKCR2_EPWM6    0x20U      // EPWM6 Clock Enable bit
#define SYSCTL_PCLKCR2_EPWM7    0x40U      // EPWM7 Clock Enable bit
#define SYSCTL_PCLKCR2_EPWM8    0x80U      // EPWM8 Clock Enable bit
#define SYSCTL_PCLKCR2_EPWM9    0x100U     // EPWM9 Clock Enable bit
#define SYSCTL_PCLKCR2_EPWM10   0x200U     // EPWM10 Clock Enable bit
#define SYSCTL_PCLKCR2_EPWM11   0x400U     // EPWM11 Clock Enable bit
#define SYSCTL_PCLKCR2_EPWM12   0x800U     // EPWM12 Clock Enable bit
#define SYSCTL_PCLKCR2_EPWM13   0x1000U    // EPWM13 Clock Enable bit
#define SYSCTL_PCLKCR2_EPWM14   0x2000U    // EPWM14 Clock Enable bit
#define SYSCTL_PCLKCR2_EPWM15   0x4000U    // EPWM15 Clock Enable bit
#define SYSCTL_PCLKCR2_EPWM16   0x8000U    // EPWM16 Clock Enable bit
#define SYSCTL_PCLKCR2_EPWM17   0x10000U   // EPWM17 Clock Enable bit
#define SYSCTL_PCLKCR2_EPWM18   0x20000U   // EPWM18 Clock Enable bit

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
#define SYSCTL_PCLKCR3_ECAP7   0x40U   // ECAP7 Clock Enable bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCLKCR4 register
//
//*************************************************************************************************
#define SYSCTL_PCLKCR4_EQEP1   0x1U    // EQEP1 Clock Enable bit
#define SYSCTL_PCLKCR4_EQEP2   0x2U    // EQEP2 Clock Enable bit
#define SYSCTL_PCLKCR4_EQEP3   0x4U    // EQEP3 Clock Enable bit
#define SYSCTL_PCLKCR4_EQEP4   0x8U    // EQEP4 Clock Enable bit
#define SYSCTL_PCLKCR4_EQEP5   0x10U   // EQEP5 Clock Enable bit
#define SYSCTL_PCLKCR4_EQEP6   0x20U   // EQEP6 Clock Enable bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCLKCR6 register
//
//*************************************************************************************************
#define SYSCTL_PCLKCR6_SD1   0x1U   // SD1 Clock Enable bit
#define SYSCTL_PCLKCR6_SD2   0x2U   // SD2 Clock Enable bit
#define SYSCTL_PCLKCR6_SD3   0x4U   // SD3 Clock Enable bit
#define SYSCTL_PCLKCR6_SD4   0x8U   // SD4 Clock Enable bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCLKCR7 register
//
//*************************************************************************************************
#define SYSCTL_PCLKCR7_SCI_A    0x1U       // SCI_A Clock Enable bit
#define SYSCTL_PCLKCR7_SCI_B    0x2U       // SCI_B Clock Enable bit
#define SYSCTL_PCLKCR7_UART_A   0x10000U   // UART_A Clock Enable bit
#define SYSCTL_PCLKCR7_UART_B   0x20000U   // UART_B Clock Enable bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCLKCR8 register
//
//*************************************************************************************************
#define SYSCTL_PCLKCR8_SPI_A   0x1U   // SPI_A Clock Enable bit
#define SYSCTL_PCLKCR8_SPI_B   0x2U   // SPI_B Clock Enable bit
#define SYSCTL_PCLKCR8_SPI_C   0x4U   // SPI_C Clock Enable bit
#define SYSCTL_PCLKCR8_SPI_D   0x8U   // SPI_D Clock Enable bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCLKCR9 register
//
//*************************************************************************************************
#define SYSCTL_PCLKCR9_I2C_A     0x1U       // I2C_A Clock Enable bit
#define SYSCTL_PCLKCR9_I2C_B     0x2U       // I2C_B Clock Enable bit
#define SYSCTL_PCLKCR9_PMBUS_A   0x10000U   // PMBUS_A Clock Enable bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCLKCR10 register
//
//*************************************************************************************************
#define SYSCTL_PCLKCR10_CAN_A    0x1U    // CAN_A Clock Enable bit
#define SYSCTL_PCLKCR10_MCAN_A   0x10U   // MCAN_A Clock Enable bit
#define SYSCTL_PCLKCR10_MCAN_B   0x20U   // MCAN_B Clock Enable bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCLKCR11 register
//
//*************************************************************************************************
#define SYSCTL_PCLKCR11_USB_A   0x10000U   // USB_A Clock Enable bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCLKCR13 register
//
//*************************************************************************************************
#define SYSCTL_PCLKCR13_ADC_A   0x1U   // ADC_A Clock Enable bit
#define SYSCTL_PCLKCR13_ADC_B   0x2U   // ADC_B Clock Enable bit
#define SYSCTL_PCLKCR13_ADC_C   0x4U   // ADC_C Clock Enable bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCLKCR14 register
//
//*************************************************************************************************
#define SYSCTL_PCLKCR14_CMPSS1    0x1U     // CMPSS1 Clock Enable bit
#define SYSCTL_PCLKCR14_CMPSS2    0x2U     // CMPSS2 Clock Enable bit
#define SYSCTL_PCLKCR14_CMPSS3    0x4U     // CMPSS3 Clock Enable bit
#define SYSCTL_PCLKCR14_CMPSS4    0x8U     // CMPSS4 Clock Enable bit
#define SYSCTL_PCLKCR14_CMPSS5    0x10U    // CMPSS5 Clock Enable bit
#define SYSCTL_PCLKCR14_CMPSS6    0x20U    // CMPSS6 Clock Enable bit
#define SYSCTL_PCLKCR14_CMPSS7    0x40U    // CMPSS7 Clock Enable bit
#define SYSCTL_PCLKCR14_CMPSS8    0x80U    // CMPSS8 Clock Enable bit
#define SYSCTL_PCLKCR14_CMPSS9    0x100U   // CMPSS9 Clock Enable bit
#define SYSCTL_PCLKCR14_CMPSS10   0x200U   // CMPSS10 Clock Enable bit
#define SYSCTL_PCLKCR14_CMPSS11   0x400U   // CMPSS11 Clock Enable bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCLKCR16 register
//
//*************************************************************************************************
#define SYSCTL_PCLKCR16_DAC_A   0x10000U   // Buffered_DAC_A Clock Enable Bit
#define SYSCTL_PCLKCR16_DAC_C   0x40000U   // Buffered_DAC_C Clock Enable Bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCLKCR17 register
//
//*************************************************************************************************
#define SYSCTL_PCLKCR17_CLB1   0x1U    // CLB1 Clock Enable bit
#define SYSCTL_PCLKCR17_CLB2   0x2U    // CLB2 Clock Enable bit
#define SYSCTL_PCLKCR17_CLB3   0x4U    // CLB3 Clock Enable bit
#define SYSCTL_PCLKCR17_CLB4   0x8U    // CLB4 Clock Enable bit
#define SYSCTL_PCLKCR17_CLB5   0x10U   // CLB5 Clock Enable bit
#define SYSCTL_PCLKCR17_CLB6   0x20U   // CLB6 Clock Enable bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCLKCR18 register
//
//*************************************************************************************************
#define SYSCTL_PCLKCR18_FSITX_A   0x1U       // FSITX_A Clock Enable bit
#define SYSCTL_PCLKCR18_FSITX_B   0x2U       // FSIRX_A Clock Enable bit
#define SYSCTL_PCLKCR18_FSIRX_A   0x10000U   // FSITX_B Clock Enable bit
#define SYSCTL_PCLKCR18_FSIRX_B   0x20000U   // FSIRX_B Clock Enable bit
#define SYSCTL_PCLKCR18_FSIRX_C   0x40000U   // FSITX_C Clock Enable bit
#define SYSCTL_PCLKCR18_FSIRX_D   0x80000U   // FSIRX_C Clock Enable bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCLKCR19 register
//
//*************************************************************************************************
#define SYSCTL_PCLKCR19_LIN_A   0x1U   // LIN_A Clock Enable bit
#define SYSCTL_PCLKCR19_LIN_B   0x2U   // LIN_B Clock Enable bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCLKCR21 register
//
//*************************************************************************************************
#define SYSCTL_PCLKCR21_DCC0   0x1U   // DCC0 Clock Enable Bit
#define SYSCTL_PCLKCR21_DCC1   0x2U   // DCC1 Clock Enable Bit
#define SYSCTL_PCLKCR21_DCC2   0x4U   // DCC2 Clock Enable Bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCLKCR23 register
//
//*************************************************************************************************
#define SYSCTL_PCLKCR23_ETHERCAT   0x1U   // ETHERCAT Clock Enable Bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCLKCR25 register
//
//*************************************************************************************************
#define SYSCTL_PCLKCR25_HRCAL0   0x1U   // HRCAL0 Clock Enable Bit
#define SYSCTL_PCLKCR25_HRCAL1   0x2U   // HRCAL1 Clock Enable Bit
#define SYSCTL_PCLKCR25_HRCAL2   0x4U   // HRCAL2 Clock Enable Bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCLKCR26 register
//
//*************************************************************************************************
#define SYSCTL_PCLKCR26_AESA   0x1U   // AESA Clock Enable Bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCLKCR27 register
//
//*************************************************************************************************
#define SYSCTL_PCLKCR27_EPG1   0x1U   // EPG1 Clock Enable Bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the PCLKCR28 register
//
//*************************************************************************************************
#define SYSCTL_PCLKCR28_ADCCHECKER1     0x1U       // ADCCHECKER1 Clock Enable bit
#define SYSCTL_PCLKCR28_ADCCHECKER2     0x2U       // ADCCHECKER2 Clock Enable bit
#define SYSCTL_PCLKCR28_ADCCHECKER3     0x4U       // ADCCHECKER3 Clock Enable bit
#define SYSCTL_PCLKCR28_ADCCHECKER4     0x8U       // ADCCHECKER4 Clock Enable bit
#define SYSCTL_PCLKCR28_ADCCHECKER5     0x10U      // ADCCHECKER5 Clock Enable bit
#define SYSCTL_PCLKCR28_ADCCHECKER6     0x20U      // ADCCHECKER6 Clock Enable bit
#define SYSCTL_PCLKCR28_ADCCHECKER7     0x40U      // ADCCHECKER7 Clock Enable bit
#define SYSCTL_PCLKCR28_ADCCHECKER8     0x80U      // ADCCHECKER8 Clock Enable bit
#define SYSCTL_PCLKCR28_ADCSEAGGRCPU1   0x10000U   // ADCSEAGGRCPU1 Clock Enable bit

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
// The following are defines for the bit fields in the CPUID register
//
//*************************************************************************************************
#define SYSCTL_CPUID_CPUID_S   0U
#define SYSCTL_CPUID_CPUID_M   0x3U   // Indicates CPU1 or CPU2

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMPSSLPMSEL register
//
//*************************************************************************************************
#define SYSCTL_CMPSSLPMSEL_CMPSS1H    0x1U        // CMPSS1H Enable for LPM Wakeup
#define SYSCTL_CMPSSLPMSEL_CMPSS1L    0x2U        // CMPSS1L Enable for LPM Wakeup
#define SYSCTL_CMPSSLPMSEL_CMPSS2H    0x4U        // CMPSS2H Enable for LPM Wakeup
#define SYSCTL_CMPSSLPMSEL_CMPSS2L    0x8U        // CMPSS2L Enable for LPM Wakeup
#define SYSCTL_CMPSSLPMSEL_CMPSS3H    0x10U       // CMPSS3H Enable for LPM Wakeup
#define SYSCTL_CMPSSLPMSEL_CMPSS3L    0x20U       // CMPSS3L Enable for LPM Wakeup
#define SYSCTL_CMPSSLPMSEL_CMPSS4H    0x40U       // CMPSS4H Enable for LPM Wakeup
#define SYSCTL_CMPSSLPMSEL_CMPSS4L    0x80U       // CMPSS4L Enable for LPM Wakeup
#define SYSCTL_CMPSSLPMSEL_CMPSS5H    0x100U      // CMPSS5H Enable for LPM Wakeup
#define SYSCTL_CMPSSLPMSEL_CMPSS5L    0x200U      // CMPSS5L Enable for LPM Wakeup
#define SYSCTL_CMPSSLPMSEL_CMPSS6H    0x400U      // CMPSS6H Enable for LPM Wakeup
#define SYSCTL_CMPSSLPMSEL_CMPSS6L    0x800U      // CMPSS6L Enable for LPM Wakeup
#define SYSCTL_CMPSSLPMSEL_CMPSS7H    0x1000U     // CMPSS7H Enable for LPM Wakeup
#define SYSCTL_CMPSSLPMSEL_CMPSS7L    0x2000U     // CMPSS7L Enable for LPM Wakeup
#define SYSCTL_CMPSSLPMSEL_CMPSS8H    0x4000U     // CMPSS8H Enable for LPM Wakeup
#define SYSCTL_CMPSSLPMSEL_CMPSS8L    0x8000U     // CMPSS8L Enable for LPM Wakeup
#define SYSCTL_CMPSSLPMSEL_CMPSS9H    0x10000U    // CMPSS9H Enable for LPM Wakeup
#define SYSCTL_CMPSSLPMSEL_CMPSS9L    0x20000U    // CMPSS9L Enable for LPM Wakeup
#define SYSCTL_CMPSSLPMSEL_CMPSS10H   0x40000U    // CMPSS10H Enable for LPM Wakeup
#define SYSCTL_CMPSSLPMSEL_CMPSS10L   0x80000U    // CMPSS10L Enable for LPM Wakeup
#define SYSCTL_CMPSSLPMSEL_CMPSS11H   0x100000U   // CMPSS11H Enable for LPM Wakeup
#define SYSCTL_CMPSSLPMSEL_CMPSS11L   0x200000U   // CMPSS11L Enable for LPM Wakeup

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
#define SYSCTL_RESCCLR_HWBISTN            0x20U    // HWBISTn Reset Cause Indication Bit
#define SYSCTL_RESCCLR_SCCRESETN          0x100U   // SCCRESETn Reset Cause Indication Bit
#define SYSCTL_RESCCLR_ECAT_RESET_OUT     0x200U   // ECAT_RESET_OUT Reset Cause Indication Bit
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
#define SYSCTL_RESC_HWBISTN            0x20U         // HWBISTn Reset Cause Indication Bit
#define SYSCTL_RESC_SCCRESETN          0x100U        // SCCRESETn Reset Cause Indication Bit
#define SYSCTL_RESC_ECAT_RESET_OUT     0x200U        // ECAT_RESET_OUT Reset Cause Indication Bit
#define SYSCTL_RESC_SIMRESET_CPU1RSN   0x400U        // SIMRESET_CPU1RSn Reset Cause Indication Bit
#define SYSCTL_RESC_SIMRESET_XRSN      0x800U        // SIMRESET_XRSn Reset Cause Indication Bit
#define SYSCTL_RESC_XRSN_PIN_STATUS    0x40000000U   // XRSN Pin Status
#define SYSCTL_RESC_DCON               0x80000000U   // Debugger conntion status to C28x

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCANWAKESTATUS register
//
//*************************************************************************************************
#define SYSCTL_MCANWAKESTATUS_WAKE_MCANA   0x1U   // MCANA Wake Status
#define SYSCTL_MCANWAKESTATUS_WAKE_MCANB   0x2U   // MCANB Wake Status

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCANWAKESTATUSCLR register
//
//*************************************************************************************************
#define SYSCTL_MCANWAKESTATUSCLR_WAKE_MCANA   0x1U   // Cear bit for MCANWAKESTATUS.WAKE_MCANA bit
#define SYSCTL_MCANWAKESTATUSCLR_WAKE_MCANB   0x2U   // Cear bit for MCANWAKESTATUS.WAKE_MCANB bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the CLKSTOPREQ register
//
//*************************************************************************************************
#define SYSCTL_CLKSTOPREQ_CAN_A    0x10U         // CAN_A Clock Stop Request Bit
#define SYSCTL_CLKSTOPREQ_MCAN_A   0x100U        // MCAN_A Clock Stop Request Bit
#define SYSCTL_CLKSTOPREQ_MCAN_B   0x200U        // MCAN_B Clock Stop Request Bit
#define SYSCTL_CLKSTOPREQ_KEY_S    16U
#define SYSCTL_CLKSTOPREQ_KEY_M    0xFFFF0000U   // Key for register write

//*************************************************************************************************
//
// The following are defines for the bit fields in the CLKSTOPACK register
//
//*************************************************************************************************
#define SYSCTL_CLKSTOPACK_CAN_A    0x10U    // CAN_A Clock Stop Ack Bit
#define SYSCTL_CLKSTOPACK_MCAN_A   0x100U   // MCAN_A Clock Stop Ack Bit
#define SYSCTL_CLKSTOPACK_MCAN_B   0x200U   // MCAN_B Clock Stop Ack Bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the LSEN register
//
//*************************************************************************************************
#define SYSCTL_LSEN_ENABLE      0x1U          // Lockstep Enable
#define SYSCTL_LSEN_RSERVED_S   1U
#define SYSCTL_LSEN_RSERVED_M   0xFFFFFFFEU   // Reserved

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
// The following are defines for the bit fields in the SYNCBUSYWD register
//
//*************************************************************************************************
#define SYSCTL_SYNCBUSYWD_BUSY   0x1U   // Status bit indicating synchronization in progress
#define SYSCTL_SYNCBUSYWD_WDCR   0x2U   // BUSY status bit for WDCR

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
// The following are defines for the bit fields in the DMACHSRCSELLOCK register
//
//*************************************************************************************************
#define SYSCTL_DMACHSRCSELLOCK_DMACHSRCSEL1   0x1U   // DMACHSRCSEL1 Register Lock bit
#define SYSCTL_DMACHSRCSELLOCK_DMACHSRCSEL2   0x2U   // DMACHSRCSEL2 Register Lock bit

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
// The following are defines for the bit fields in the ADCA_AC register
//
//*************************************************************************************************
#define SYSCTL_ADCA_AC_CPUX_ACC_S   0U
#define SYSCTL_ADCA_AC_CPUX_ACC_M   0x3U   // CPUx Access conditions to peripheral
#define SYSCTL_ADCA_AC_CLA1_ACC_S   2U
#define SYSCTL_ADCA_AC_CLA1_ACC_M   0xCU   // CLA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCB_AC register
//
//*************************************************************************************************
#define SYSCTL_ADCB_AC_CPUX_ACC_S   0U
#define SYSCTL_ADCB_AC_CPUX_ACC_M   0x3U   // CPUx Access conditions to peripheral
#define SYSCTL_ADCB_AC_CLA1_ACC_S   2U
#define SYSCTL_ADCB_AC_CLA1_ACC_M   0xCU   // CLA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCC_AC register
//
//*************************************************************************************************
#define SYSCTL_ADCC_AC_CPUX_ACC_S   0U
#define SYSCTL_ADCC_AC_CPUX_ACC_M   0x3U   // CPUx Access conditions to peripheral
#define SYSCTL_ADCC_AC_CLA1_ACC_S   2U
#define SYSCTL_ADCC_AC_CLA1_ACC_M   0xCU   // CLA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMPSS1_AC register
//
//*************************************************************************************************
#define SYSCTL_CMPSS1_AC_CPUX_ACC_S   0U
#define SYSCTL_CMPSS1_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_CMPSS1_AC_CLA1_ACC_S   2U
#define SYSCTL_CMPSS1_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_CMPSS1_AC_DMA1_ACC_S   4U
#define SYSCTL_CMPSS1_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMPSS2_AC register
//
//*************************************************************************************************
#define SYSCTL_CMPSS2_AC_CPUX_ACC_S   0U
#define SYSCTL_CMPSS2_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_CMPSS2_AC_CLA1_ACC_S   2U
#define SYSCTL_CMPSS2_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_CMPSS2_AC_DMA1_ACC_S   4U
#define SYSCTL_CMPSS2_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMPSS3_AC register
//
//*************************************************************************************************
#define SYSCTL_CMPSS3_AC_CPUX_ACC_S   0U
#define SYSCTL_CMPSS3_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_CMPSS3_AC_CLA1_ACC_S   2U
#define SYSCTL_CMPSS3_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_CMPSS3_AC_DMA1_ACC_S   4U
#define SYSCTL_CMPSS3_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMPSS4_AC register
//
//*************************************************************************************************
#define SYSCTL_CMPSS4_AC_CPUX_ACC_S   0U
#define SYSCTL_CMPSS4_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_CMPSS4_AC_CLA1_ACC_S   2U
#define SYSCTL_CMPSS4_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_CMPSS4_AC_DMA1_ACC_S   4U
#define SYSCTL_CMPSS4_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMPSS5_AC register
//
//*************************************************************************************************
#define SYSCTL_CMPSS5_AC_CPUX_ACC_S   0U
#define SYSCTL_CMPSS5_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_CMPSS5_AC_CLA1_ACC_S   2U
#define SYSCTL_CMPSS5_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_CMPSS5_AC_DMA1_ACC_S   4U
#define SYSCTL_CMPSS5_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMPSS6_AC register
//
//*************************************************************************************************
#define SYSCTL_CMPSS6_AC_CPUX_ACC_S   0U
#define SYSCTL_CMPSS6_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_CMPSS6_AC_CLA1_ACC_S   2U
#define SYSCTL_CMPSS6_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_CMPSS6_AC_DMA1_ACC_S   4U
#define SYSCTL_CMPSS6_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMPSS7_AC register
//
//*************************************************************************************************
#define SYSCTL_CMPSS7_AC_CPUX_ACC_S   0U
#define SYSCTL_CMPSS7_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_CMPSS7_AC_CLA1_ACC_S   2U
#define SYSCTL_CMPSS7_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_CMPSS7_AC_DMA1_ACC_S   4U
#define SYSCTL_CMPSS7_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMPSS8_AC register
//
//*************************************************************************************************
#define SYSCTL_CMPSS8_AC_CPUX_ACC_S   0U
#define SYSCTL_CMPSS8_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_CMPSS8_AC_CLA1_ACC_S   2U
#define SYSCTL_CMPSS8_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_CMPSS8_AC_DMA1_ACC_S   4U
#define SYSCTL_CMPSS8_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMPSS9_AC register
//
//*************************************************************************************************
#define SYSCTL_CMPSS9_AC_CPUX_ACC_S   0U
#define SYSCTL_CMPSS9_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_CMPSS9_AC_CLA1_ACC_S   2U
#define SYSCTL_CMPSS9_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_CMPSS9_AC_DMA1_ACC_S   4U
#define SYSCTL_CMPSS9_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMPSS10_AC register
//
//*************************************************************************************************
#define SYSCTL_CMPSS10_AC_CPUX_ACC_S   0U
#define SYSCTL_CMPSS10_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_CMPSS10_AC_CLA1_ACC_S   2U
#define SYSCTL_CMPSS10_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_CMPSS10_AC_DMA1_ACC_S   4U
#define SYSCTL_CMPSS10_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMPSS11_AC register
//
//*************************************************************************************************
#define SYSCTL_CMPSS11_AC_CPUX_ACC_S   0U
#define SYSCTL_CMPSS11_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_CMPSS11_AC_CLA1_ACC_S   2U
#define SYSCTL_CMPSS11_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_CMPSS11_AC_DMA1_ACC_S   4U
#define SYSCTL_CMPSS11_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the DACA_AC register
//
//*************************************************************************************************
#define SYSCTL_DACA_AC_CPUX_ACC_S   0U
#define SYSCTL_DACA_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_DACA_AC_CLA1_ACC_S   2U
#define SYSCTL_DACA_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_DACA_AC_DMA1_ACC_S   4U
#define SYSCTL_DACA_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the DACC_AC register
//
//*************************************************************************************************
#define SYSCTL_DACC_AC_CPUX_ACC_S   0U
#define SYSCTL_DACC_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_DACC_AC_CLA1_ACC_S   2U
#define SYSCTL_DACC_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_DACC_AC_DMA1_ACC_S   4U
#define SYSCTL_DACC_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the EPWM1_AC register
//
//*************************************************************************************************
#define SYSCTL_EPWM1_AC_CPUX_ACC_S   0U
#define SYSCTL_EPWM1_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_EPWM1_AC_CLA1_ACC_S   2U
#define SYSCTL_EPWM1_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_EPWM1_AC_DMA1_ACC_S   4U
#define SYSCTL_EPWM1_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the EPWM2_AC register
//
//*************************************************************************************************
#define SYSCTL_EPWM2_AC_CPUX_ACC_S   0U
#define SYSCTL_EPWM2_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_EPWM2_AC_CLA1_ACC_S   2U
#define SYSCTL_EPWM2_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_EPWM2_AC_DMA1_ACC_S   4U
#define SYSCTL_EPWM2_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the EPWM3_AC register
//
//*************************************************************************************************
#define SYSCTL_EPWM3_AC_CPUX_ACC_S   0U
#define SYSCTL_EPWM3_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_EPWM3_AC_CLA1_ACC_S   2U
#define SYSCTL_EPWM3_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_EPWM3_AC_DMA1_ACC_S   4U
#define SYSCTL_EPWM3_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the EPWM4_AC register
//
//*************************************************************************************************
#define SYSCTL_EPWM4_AC_CPUX_ACC_S   0U
#define SYSCTL_EPWM4_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_EPWM4_AC_CLA1_ACC_S   2U
#define SYSCTL_EPWM4_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_EPWM4_AC_DMA1_ACC_S   4U
#define SYSCTL_EPWM4_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the EPWM5_AC register
//
//*************************************************************************************************
#define SYSCTL_EPWM5_AC_CPUX_ACC_S   0U
#define SYSCTL_EPWM5_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_EPWM5_AC_CLA1_ACC_S   2U
#define SYSCTL_EPWM5_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_EPWM5_AC_DMA1_ACC_S   4U
#define SYSCTL_EPWM5_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the EPWM6_AC register
//
//*************************************************************************************************
#define SYSCTL_EPWM6_AC_CPUX_ACC_S   0U
#define SYSCTL_EPWM6_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_EPWM6_AC_CLA1_ACC_S   2U
#define SYSCTL_EPWM6_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_EPWM6_AC_DMA1_ACC_S   4U
#define SYSCTL_EPWM6_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the EPWM7_AC register
//
//*************************************************************************************************
#define SYSCTL_EPWM7_AC_CPUX_ACC_S   0U
#define SYSCTL_EPWM7_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_EPWM7_AC_CLA1_ACC_S   2U
#define SYSCTL_EPWM7_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_EPWM7_AC_DMA1_ACC_S   4U
#define SYSCTL_EPWM7_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the EPWM8_AC register
//
//*************************************************************************************************
#define SYSCTL_EPWM8_AC_CPUX_ACC_S   0U
#define SYSCTL_EPWM8_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_EPWM8_AC_CLA1_ACC_S   2U
#define SYSCTL_EPWM8_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_EPWM8_AC_DMA1_ACC_S   4U
#define SYSCTL_EPWM8_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the EPWM9_AC register
//
//*************************************************************************************************
#define SYSCTL_EPWM9_AC_CPUX_ACC_S   0U
#define SYSCTL_EPWM9_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_EPWM9_AC_CLA1_ACC_S   2U
#define SYSCTL_EPWM9_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_EPWM9_AC_DMA1_ACC_S   4U
#define SYSCTL_EPWM9_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the EPWM10_AC register
//
//*************************************************************************************************
#define SYSCTL_EPWM10_AC_CPUX_ACC_S   0U
#define SYSCTL_EPWM10_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_EPWM10_AC_CLA1_ACC_S   2U
#define SYSCTL_EPWM10_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_EPWM10_AC_DMA1_ACC_S   4U
#define SYSCTL_EPWM10_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the EPWM11_AC register
//
//*************************************************************************************************
#define SYSCTL_EPWM11_AC_CPUX_ACC_S   0U
#define SYSCTL_EPWM11_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_EPWM11_AC_CLA1_ACC_S   2U
#define SYSCTL_EPWM11_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_EPWM11_AC_DMA1_ACC_S   4U
#define SYSCTL_EPWM11_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the EPWM12_AC register
//
//*************************************************************************************************
#define SYSCTL_EPWM12_AC_CPUX_ACC_S   0U
#define SYSCTL_EPWM12_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_EPWM12_AC_CLA1_ACC_S   2U
#define SYSCTL_EPWM12_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_EPWM12_AC_DMA1_ACC_S   4U
#define SYSCTL_EPWM12_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the EPWM13_AC register
//
//*************************************************************************************************
#define SYSCTL_EPWM13_AC_CPUX_ACC_S   0U
#define SYSCTL_EPWM13_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_EPWM13_AC_CLA1_ACC_S   2U
#define SYSCTL_EPWM13_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_EPWM13_AC_DMA1_ACC_S   4U
#define SYSCTL_EPWM13_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the EPWM14_AC register
//
//*************************************************************************************************
#define SYSCTL_EPWM14_AC_CPUX_ACC_S   0U
#define SYSCTL_EPWM14_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_EPWM14_AC_CLA1_ACC_S   2U
#define SYSCTL_EPWM14_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_EPWM14_AC_DMA1_ACC_S   4U
#define SYSCTL_EPWM14_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the EPWM15_AC register
//
//*************************************************************************************************
#define SYSCTL_EPWM15_AC_CPUX_ACC_S   0U
#define SYSCTL_EPWM15_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_EPWM15_AC_CLA1_ACC_S   2U
#define SYSCTL_EPWM15_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_EPWM15_AC_DMA1_ACC_S   4U
#define SYSCTL_EPWM15_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the EPWM16_AC register
//
//*************************************************************************************************
#define SYSCTL_EPWM16_AC_CPUX_ACC_S   0U
#define SYSCTL_EPWM16_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_EPWM16_AC_CLA1_ACC_S   2U
#define SYSCTL_EPWM16_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_EPWM16_AC_DMA1_ACC_S   4U
#define SYSCTL_EPWM16_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the EPWM17_AC register
//
//*************************************************************************************************
#define SYSCTL_EPWM17_AC_CPUX_ACC_S   0U
#define SYSCTL_EPWM17_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_EPWM17_AC_CLA1_ACC_S   2U
#define SYSCTL_EPWM17_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_EPWM17_AC_DMA1_ACC_S   4U
#define SYSCTL_EPWM17_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the EPWM18_AC register
//
//*************************************************************************************************
#define SYSCTL_EPWM18_AC_CPUX_ACC_S   0U
#define SYSCTL_EPWM18_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_EPWM18_AC_CLA1_ACC_S   2U
#define SYSCTL_EPWM18_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_EPWM18_AC_DMA1_ACC_S   4U
#define SYSCTL_EPWM18_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the EQEP1_AC register
//
//*************************************************************************************************
#define SYSCTL_EQEP1_AC_CPUX_ACC_S   0U
#define SYSCTL_EQEP1_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_EQEP1_AC_CLA1_ACC_S   2U
#define SYSCTL_EQEP1_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_EQEP1_AC_DMA1_ACC_S   4U
#define SYSCTL_EQEP1_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the EQEP2_AC register
//
//*************************************************************************************************
#define SYSCTL_EQEP2_AC_CPUX_ACC_S   0U
#define SYSCTL_EQEP2_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_EQEP2_AC_CLA1_ACC_S   2U
#define SYSCTL_EQEP2_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_EQEP2_AC_DMA1_ACC_S   4U
#define SYSCTL_EQEP2_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the EQEP3_AC register
//
//*************************************************************************************************
#define SYSCTL_EQEP3_AC_CPUX_ACC_S   0U
#define SYSCTL_EQEP3_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_EQEP3_AC_CLA1_ACC_S   2U
#define SYSCTL_EQEP3_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_EQEP3_AC_DMA1_ACC_S   4U
#define SYSCTL_EQEP3_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the EQEP4_AC register
//
//*************************************************************************************************
#define SYSCTL_EQEP4_AC_CPUX_ACC_S   0U
#define SYSCTL_EQEP4_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_EQEP4_AC_CLA1_ACC_S   2U
#define SYSCTL_EQEP4_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_EQEP4_AC_DMA1_ACC_S   4U
#define SYSCTL_EQEP4_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the EQEP5_AC register
//
//*************************************************************************************************
#define SYSCTL_EQEP5_AC_CPUX_ACC_S   0U
#define SYSCTL_EQEP5_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_EQEP5_AC_CLA1_ACC_S   2U
#define SYSCTL_EQEP5_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_EQEP5_AC_DMA1_ACC_S   4U
#define SYSCTL_EQEP5_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the EQEP6_AC register
//
//*************************************************************************************************
#define SYSCTL_EQEP6_AC_CPUX_ACC_S   0U
#define SYSCTL_EQEP6_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_EQEP6_AC_CLA1_ACC_S   2U
#define SYSCTL_EQEP6_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_EQEP6_AC_DMA1_ACC_S   4U
#define SYSCTL_EQEP6_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the ECAP1_AC register
//
//*************************************************************************************************
#define SYSCTL_ECAP1_AC_CPUX_ACC_S   0U
#define SYSCTL_ECAP1_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_ECAP1_AC_CLA1_ACC_S   2U
#define SYSCTL_ECAP1_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_ECAP1_AC_DMA1_ACC_S   4U
#define SYSCTL_ECAP1_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the ECAP2_AC register
//
//*************************************************************************************************
#define SYSCTL_ECAP2_AC_CPUX_ACC_S   0U
#define SYSCTL_ECAP2_AC_CPUX_ACC_M   0x3U    // CPUx Access c+D2593onditions to peripheral
#define SYSCTL_ECAP2_AC_CLA1_ACC_S   2U
#define SYSCTL_ECAP2_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_ECAP2_AC_DMA1_ACC_S   4U
#define SYSCTL_ECAP2_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the ECAP3_AC register
//
//*************************************************************************************************
#define SYSCTL_ECAP3_AC_CPUX_ACC_S   0U
#define SYSCTL_ECAP3_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_ECAP3_AC_CLA1_ACC_S   2U
#define SYSCTL_ECAP3_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_ECAP3_AC_DMA1_ACC_S   4U
#define SYSCTL_ECAP3_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the ECAP4_AC register
//
//*************************************************************************************************
#define SYSCTL_ECAP4_AC_CPUX_ACC_S   0U
#define SYSCTL_ECAP4_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_ECAP4_AC_CLA1_ACC_S   2U
#define SYSCTL_ECAP4_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_ECAP4_AC_DMA1_ACC_S   4U
#define SYSCTL_ECAP4_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the ECAP5_AC register
//
//*************************************************************************************************
#define SYSCTL_ECAP5_AC_CPUX_ACC_S   0U
#define SYSCTL_ECAP5_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_ECAP5_AC_CLA1_ACC_S   2U
#define SYSCTL_ECAP5_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_ECAP5_AC_DMA1_ACC_S   4U
#define SYSCTL_ECAP5_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the ECAP6_AC register
//
//*************************************************************************************************
#define SYSCTL_ECAP6_AC_CPUX_ACC_S   0U
#define SYSCTL_ECAP6_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_ECAP6_AC_CLA1_ACC_S   2U
#define SYSCTL_ECAP6_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_ECAP6_AC_DMA1_ACC_S   4U
#define SYSCTL_ECAP6_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the ECAP7_AC register
//
//*************************************************************************************************
#define SYSCTL_ECAP7_AC_CPUX_ACC_S   0U
#define SYSCTL_ECAP7_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_ECAP7_AC_CLA1_ACC_S   2U
#define SYSCTL_ECAP7_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_ECAP7_AC_DMA1_ACC_S   4U
#define SYSCTL_ECAP7_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the SDFM1_AC register
//
//*************************************************************************************************
#define SYSCTL_SDFM1_AC_CPUX_ACC_S   0U
#define SYSCTL_SDFM1_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_SDFM1_AC_CLA1_ACC_S   2U
#define SYSCTL_SDFM1_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_SDFM1_AC_DMA1_ACC_S   4U
#define SYSCTL_SDFM1_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the SDFM2_AC register
//
//*************************************************************************************************
#define SYSCTL_SDFM2_AC_CPUX_ACC_S   0U
#define SYSCTL_SDFM2_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_SDFM2_AC_CLA1_ACC_S   2U
#define SYSCTL_SDFM2_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_SDFM2_AC_DMA1_ACC_S   4U
#define SYSCTL_SDFM2_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the SDFM3_AC register
//
//*************************************************************************************************
#define SYSCTL_SDFM3_AC_CPUX_ACC_S   0U
#define SYSCTL_SDFM3_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_SDFM3_AC_CLA1_ACC_S   2U
#define SYSCTL_SDFM3_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_SDFM3_AC_DMA1_ACC_S   4U
#define SYSCTL_SDFM3_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the SDFM4_AC register
//
//*************************************************************************************************
#define SYSCTL_SDFM4_AC_CPUX_ACC_S   0U
#define SYSCTL_SDFM4_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_SDFM4_AC_CLA1_ACC_S   2U
#define SYSCTL_SDFM4_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_SDFM4_AC_DMA1_ACC_S   4U
#define SYSCTL_SDFM4_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the CLB1_AC register
//
//*************************************************************************************************
#define SYSCTL_CLB1_AC_CPUX_ACC_S   0U
#define SYSCTL_CLB1_AC_CPUX_ACC_M   0x3U   // CPUx Access conditions to peripheral
#define SYSCTL_CLB1_AC_CLA1_ACC_S   2U
#define SYSCTL_CLB1_AC_CLA1_ACC_M   0xCU   // CLA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the CLB2_AC register
//
//*************************************************************************************************
#define SYSCTL_CLB2_AC_CPUX_ACC_S   0U
#define SYSCTL_CLB2_AC_CPUX_ACC_M   0x3U   // CPUx Access conditions to peripheral
#define SYSCTL_CLB2_AC_CLA1_ACC_S   2U
#define SYSCTL_CLB2_AC_CLA1_ACC_M   0xCU   // CLA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the CLB3_AC register
//
//*************************************************************************************************
#define SYSCTL_CLB3_AC_CPUX_ACC_S   0U
#define SYSCTL_CLB3_AC_CPUX_ACC_M   0x3U   // CPUx Access conditions to peripheral
#define SYSCTL_CLB3_AC_CLA1_ACC_S   2U
#define SYSCTL_CLB3_AC_CLA1_ACC_M   0xCU   // CLA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the CLB4_AC register
//
//*************************************************************************************************
#define SYSCTL_CLB4_AC_CPUX_ACC_S   0U
#define SYSCTL_CLB4_AC_CPUX_ACC_M   0x3U   // CPUx Access conditions to peripheral
#define SYSCTL_CLB4_AC_CLA1_ACC_S   2U
#define SYSCTL_CLB4_AC_CLA1_ACC_M   0xCU   // CLA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the CLB5_AC register
//
//*************************************************************************************************
#define SYSCTL_CLB5_AC_CPUX_ACC_S   0U
#define SYSCTL_CLB5_AC_CPUX_ACC_M   0x3U   // CPUx Access conditions to peripheral
#define SYSCTL_CLB5_AC_CLA1_ACC_S   2U
#define SYSCTL_CLB5_AC_CLA1_ACC_M   0xCU   // CLA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the CLB6_AC register
//
//*************************************************************************************************
#define SYSCTL_CLB6_AC_CPUX_ACC_S   0U
#define SYSCTL_CLB6_AC_CPUX_ACC_M   0x3U   // CPUx Access conditions to peripheral
#define SYSCTL_CLB6_AC_CLA1_ACC_S   2U
#define SYSCTL_CLB6_AC_CLA1_ACC_M   0xCU   // CLA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the SCIA_AC register
//
//*************************************************************************************************
#define SYSCTL_SCIA_AC_CPUX_ACC_S   0U
#define SYSCTL_SCIA_AC_CPUX_ACC_M   0x3U   // CPUx Access conditions to peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the SCIB_AC register
//
//*************************************************************************************************
#define SYSCTL_SCIB_AC_CPUX_ACC_S   0U
#define SYSCTL_SCIB_AC_CPUX_ACC_M   0x3U   // CPUx Access conditions to peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the SPIA_AC register
//
//*************************************************************************************************
#define SYSCTL_SPIA_AC_CPUX_ACC_S   0U
#define SYSCTL_SPIA_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_SPIA_AC_CLA1_ACC_S   2U
#define SYSCTL_SPIA_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_SPIA_AC_DMA1_ACC_S   4U
#define SYSCTL_SPIA_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the SPIB_AC register
//
//*************************************************************************************************
#define SYSCTL_SPIB_AC_CPUX_ACC_S   0U
#define SYSCTL_SPIB_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_SPIB_AC_CLA1_ACC_S   2U
#define SYSCTL_SPIB_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_SPIB_AC_DMA1_ACC_S   4U
#define SYSCTL_SPIB_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the SPIC_AC register
//
//*************************************************************************************************
#define SYSCTL_SPIC_AC_CPUX_ACC_S   0U
#define SYSCTL_SPIC_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_SPIC_AC_CLA1_ACC_S   2U
#define SYSCTL_SPIC_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_SPIC_AC_DMA1_ACC_S   4U
#define SYSCTL_SPIC_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the SPID_AC register
//
//*************************************************************************************************
#define SYSCTL_SPID_AC_CPUX_ACC_S   0U
#define SYSCTL_SPID_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_SPID_AC_CLA1_ACC_S   2U
#define SYSCTL_SPID_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_SPID_AC_DMA1_ACC_S   4U
#define SYSCTL_SPID_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the I2CA_AC register
//
//*************************************************************************************************
#define SYSCTL_I2CA_AC_CPUX_ACC_S   0U
#define SYSCTL_I2CA_AC_CPUX_ACC_M   0x3U   // CPUx Access conditions to peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the I2CB_AC register
//
//*************************************************************************************************
#define SYSCTL_I2CB_AC_CPUX_ACC_S   0U
#define SYSCTL_I2CB_AC_CPUX_ACC_M   0x3U   // CPUx Access conditions to peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the PMBUS_A_AC register
//
//*************************************************************************************************
#define SYSCTL_PMBUS_A_AC_CPUX_ACC_S   0U
#define SYSCTL_PMBUS_A_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_PMBUS_A_AC_CLA1_ACC_S   2U
#define SYSCTL_PMBUS_A_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_PMBUS_A_AC_DMA1_ACC_S   4U
#define SYSCTL_PMBUS_A_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the LIN_A_AC register
//
//*************************************************************************************************
#define SYSCTL_LIN_A_AC_CPUX_ACC_S   0U
#define SYSCTL_LIN_A_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_LIN_A_AC_CLA1_ACC_S   2U
#define SYSCTL_LIN_A_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_LIN_A_AC_DMA1_ACC_S   4U
#define SYSCTL_LIN_A_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the LIN_B_AC register
//
//*************************************************************************************************
#define SYSCTL_LIN_B_AC_CPUX_ACC_S   0U
#define SYSCTL_LIN_B_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_LIN_B_AC_CLA1_ACC_S   2U
#define SYSCTL_LIN_B_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_LIN_B_AC_DMA1_ACC_S   4U
#define SYSCTL_LIN_B_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the DCANA_AC register
//
//*************************************************************************************************
#define SYSCTL_DCANA_AC_CPUX_ACC_S   0U
#define SYSCTL_DCANA_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_DCANA_AC_DMA1_ACC_S   4U
#define SYSCTL_DCANA_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCANA_AC register
//
//*************************************************************************************************
#define SYSCTL_MCANA_AC_CPUX_ACC_S   0U
#define SYSCTL_MCANA_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_MCANA_AC_DMA1_ACC_S   4U
#define SYSCTL_MCANA_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCANB_AC register
//
//*************************************************************************************************
#define SYSCTL_MCANB_AC_CPUX_ACC_S   0U
#define SYSCTL_MCANB_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_MCANB_AC_DMA1_ACC_S   4U
#define SYSCTL_MCANB_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the FSIATX_AC register
//
//*************************************************************************************************
#define SYSCTL_FSIATX_AC_CPUX_ACC_S   0U
#define SYSCTL_FSIATX_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_FSIATX_AC_CLA1_ACC_S   2U
#define SYSCTL_FSIATX_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_FSIATX_AC_DMA1_ACC_S   4U
#define SYSCTL_FSIATX_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the FSIARX_AC register
//
//*************************************************************************************************
#define SYSCTL_FSIARX_AC_CPUX_ACC_S   0U
#define SYSCTL_FSIARX_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_FSIARX_AC_CLA1_ACC_S   2U
#define SYSCTL_FSIARX_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_FSIARX_AC_DMA1_ACC_S   4U
#define SYSCTL_FSIARX_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the FSIBTX_AC register
//
//*************************************************************************************************
#define SYSCTL_FSIBTX_AC_CPUX_ACC_S   0U
#define SYSCTL_FSIBTX_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_FSIBTX_AC_CLA1_ACC_S   2U
#define SYSCTL_FSIBTX_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_FSIBTX_AC_DMA1_ACC_S   4U
#define SYSCTL_FSIBTX_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the FSIBRX_AC register
//
//*************************************************************************************************
#define SYSCTL_FSIBRX_AC_CPUX_ACC_S   0U
#define SYSCTL_FSIBRX_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_FSIBRX_AC_CLA1_ACC_S   2U
#define SYSCTL_FSIBRX_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_FSIBRX_AC_DMA1_ACC_S   4U
#define SYSCTL_FSIBRX_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the FSICRX_AC register
//
//*************************************************************************************************
#define SYSCTL_FSICRX_AC_CPUX_ACC_S   0U
#define SYSCTL_FSICRX_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_FSICRX_AC_CLA1_ACC_S   2U
#define SYSCTL_FSICRX_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_FSICRX_AC_DMA1_ACC_S   4U
#define SYSCTL_FSICRX_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the FSIDRX_AC register
//
//*************************************************************************************************
#define SYSCTL_FSIDRX_AC_CPUX_ACC_S   0U
#define SYSCTL_FSIDRX_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_FSIDRX_AC_CLA1_ACC_S   2U
#define SYSCTL_FSIDRX_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_FSIDRX_AC_DMA1_ACC_S   4U
#define SYSCTL_FSIDRX_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the USBA_AC register
//
//*************************************************************************************************
#define SYSCTL_USBA_AC_CPUX_ACC_S   0U
#define SYSCTL_USBA_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_USBA_AC_DMA1_ACC_S   4U
#define SYSCTL_USBA_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the HRPWM0_AC register
//
//*************************************************************************************************
#define SYSCTL_HRPWM0_AC_CPU1_ACC_S   0U
#define SYSCTL_HRPWM0_AC_CPU1_ACC_M   0x3U    // CPU1 Access conditions to peripheral
#define SYSCTL_HRPWM0_AC_CLA1_ACC_S   2U
#define SYSCTL_HRPWM0_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_HRPWM0_AC_DMA1_ACC_S   4U
#define SYSCTL_HRPWM0_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the HRPWM1_AC register
//
//*************************************************************************************************
#define SYSCTL_HRPWM1_AC_CPU1_ACC_S   0U
#define SYSCTL_HRPWM1_AC_CPU1_ACC_M   0x3U    // CPU1 Access conditions to peripheral
#define SYSCTL_HRPWM1_AC_CLA1_ACC_S   2U
#define SYSCTL_HRPWM1_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_HRPWM1_AC_DMA1_ACC_S   4U
#define SYSCTL_HRPWM1_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the HRPWM2_AC register
//
//*************************************************************************************************
#define SYSCTL_HRPWM2_AC_CPU1_ACC_S   0U
#define SYSCTL_HRPWM2_AC_CPU1_ACC_M   0x3U    // CPU1 Access conditions to peripheral
#define SYSCTL_HRPWM2_AC_CLA1_ACC_S   2U
#define SYSCTL_HRPWM2_AC_CLA1_ACC_M   0xCU    // CLA1 Access Conditions to Peripheral
#define SYSCTL_HRPWM2_AC_DMA1_ACC_S   4U
#define SYSCTL_HRPWM2_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the ETHERCAT_AC register
//
//*************************************************************************************************
#define SYSCTL_ETHERCAT_AC_CPU1_ACC_S   0U
#define SYSCTL_ETHERCAT_AC_CPU1_ACC_M   0x3U    // CPU1 Access conditions to peripheral
#define SYSCTL_ETHERCAT_AC_DMA1_ACC_S   4U
#define SYSCTL_ETHERCAT_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the AESA_AC register
//
//*************************************************************************************************
#define SYSCTL_AESA_AC_CPUX_ACC_S   0U
#define SYSCTL_AESA_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_AESA_AC_DMA1_ACC_S   4U
#define SYSCTL_AESA_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the UARTA_AC register
//
//*************************************************************************************************
#define SYSCTL_UARTA_AC_CPUX_ACC_S   0U
#define SYSCTL_UARTA_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_UARTA_AC_DMA1_ACC_S   4U
#define SYSCTL_UARTA_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the UARTB_AC register
//
//*************************************************************************************************
#define SYSCTL_UARTB_AC_CPUX_ACC_S   0U
#define SYSCTL_UARTB_AC_CPUX_ACC_M   0x3U    // CPUx Access conditions to peripheral
#define SYSCTL_UARTB_AC_DMA1_ACC_S   4U
#define SYSCTL_UARTB_AC_DMA1_ACC_M   0x30U   // DMA1 Access Conditions to Peripheral

//*************************************************************************************************
//
// The following are defines for the bit fields in the PERIPH_AC_LOCK register
//
//*************************************************************************************************
#define SYSCTL_PERIPH_AC_LOCK_LOCK_AC_WR   0x1U   // Lock control for Access control registers
                                                  // write.


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
#define SYSCTL_ADCSOCOUTSELECT_PWM1SOCAEN    0x1U          // PWM1SOCAEN Enable for ADCSOCAOn
#define SYSCTL_ADCSOCOUTSELECT_PWM2SOCAEN    0x2U          // PWM2SOCAEN Enable for ADCSOCAOn
#define SYSCTL_ADCSOCOUTSELECT_PWM3SOCAEN    0x4U          // PWM3SOCAEN Enable for ADCSOCAOn
#define SYSCTL_ADCSOCOUTSELECT_PWM4SOCAEN    0x8U          // PWM4SOCAEN Enable for ADCSOCAOn
#define SYSCTL_ADCSOCOUTSELECT_PWM5SOCAEN    0x10U         // PWM5SOCAEN Enable for ADCSOCAOn
#define SYSCTL_ADCSOCOUTSELECT_PWM6SOCAEN    0x20U         // PWM6SOCAEN Enable for ADCSOCAOn
#define SYSCTL_ADCSOCOUTSELECT_PWM7SOCAEN    0x40U         // PWM7SOCAEN Enable for ADCSOCAOn
#define SYSCTL_ADCSOCOUTSELECT_PWM8SOCAEN    0x80U         // PWM8SOCAEN Enable for ADCSOCAOn
#define SYSCTL_ADCSOCOUTSELECT_PWM9SOCAEN    0x100U        // PWM9SOCAEN Enable for ADCSOCAOn
#define SYSCTL_ADCSOCOUTSELECT_PWM10SOCAEN   0x200U        // PWM10SOCAEN Enable for ADCSOCAOn
#define SYSCTL_ADCSOCOUTSELECT_PWM11SOCAEN   0x400U        // PWM11SOCAEN Enable for ADCSOCAOn
#define SYSCTL_ADCSOCOUTSELECT_PWM12SOCAEN   0x800U        // PWM12SOCAEN Enable for ADCSOCAOn
#define SYSCTL_ADCSOCOUTSELECT_PWM13SOCAEN   0x1000U       // PWM13SOCAEN Enable for ADCSOCAOn
#define SYSCTL_ADCSOCOUTSELECT_PWM14SOCAEN   0x2000U       // PWM14SOCAEN Enable for ADCSOCAOn
#define SYSCTL_ADCSOCOUTSELECT_PWM15SOCAEN   0x4000U       // PWM15SOCAEN Enable for ADCSOCAOn
#define SYSCTL_ADCSOCOUTSELECT_PWM16SOCAEN   0x8000U       // PWM16SOCAEN Enable for ADCSOCAOn
#define SYSCTL_ADCSOCOUTSELECT_PWM1SOCBEN    0x10000U      // PWM1SOCBEN Enable for ADCSOCBOn
#define SYSCTL_ADCSOCOUTSELECT_PWM2SOCBEN    0x20000U      // PWM2SOCBEN Enable for ADCSOCBOn
#define SYSCTL_ADCSOCOUTSELECT_PWM3SOCBEN    0x40000U      // PWM3SOCBEN Enable for ADCSOCBOn
#define SYSCTL_ADCSOCOUTSELECT_PWM4SOCBEN    0x80000U      // PWM4SOCBEN Enable for ADCSOCBOn
#define SYSCTL_ADCSOCOUTSELECT_PWM5SOCBEN    0x100000U     // PWM5SOCBEN Enable for ADCSOCBOn
#define SYSCTL_ADCSOCOUTSELECT_PWM6SOCBEN    0x200000U     // PWM6SOCBEN Enable for ADCSOCBOn
#define SYSCTL_ADCSOCOUTSELECT_PWM7SOCBEN    0x400000U     // PWM7SOCBEN Enable for ADCSOCBOn
#define SYSCTL_ADCSOCOUTSELECT_PWM8SOCBEN    0x800000U     // PWM8SOCBEN Enable for ADCSOCBOn
#define SYSCTL_ADCSOCOUTSELECT_PWM9SOCBEN    0x1000000U    // PWM9SOCBEN Enable for ADCSOCBOn
#define SYSCTL_ADCSOCOUTSELECT_PWM10SOBAEN   0x2000000U    // PWM10SOBAEN Enable for ADCSOCBOn
#define SYSCTL_ADCSOCOUTSELECT_PWM11SOBAEN   0x4000000U    // PWM11SOBAEN Enable for ADCSOCBOn
#define SYSCTL_ADCSOCOUTSELECT_PWM12SOBAEN   0x8000000U    // PWM12SOBAEN Enable for ADCSOCBOn
#define SYSCTL_ADCSOCOUTSELECT_PWM13SOCBEN   0x10000000U   // PWM13SOCBEN Enable for ADCSOCBOn
#define SYSCTL_ADCSOCOUTSELECT_PWM14SOBAEN   0x20000000U   // PWM14SOBAEN Enable for ADCSOCBOn
#define SYSCTL_ADCSOCOUTSELECT_PWM15SOBAEN   0x40000000U   // PWM15SOBAEN Enable for ADCSOCBOn
#define SYSCTL_ADCSOCOUTSELECT_PWM16SOBAEN   0x80000000U   // PWM16SOBAEN Enable for ADCSOCBOn

//*************************************************************************************************
//
// The following are defines for the bit fields in the ADCSOCOUTSELECT1 register
//
//*************************************************************************************************
#define SYSCTL_ADCSOCOUTSELECT1_PWM17SOCAEN   0x1U       // PWM17SOCAEN Enable for ADCSOCAOn
#define SYSCTL_ADCSOCOUTSELECT1_PWM18SOCAEN   0x2U       // PWM18SOCAEN Enable for ADCSOCAOn
#define SYSCTL_ADCSOCOUTSELECT1_PWM17SOCBEN   0x10000U   // PWM17SOCBEN Enable for ADCSOCBOn
#define SYSCTL_ADCSOCOUTSELECT1_PWM18SOCBEN   0x20000U   // PWM18SOCBEN Enable for ADCSOCBOn

//*************************************************************************************************
//
// The following are defines for the bit fields in the SYNCSOCLOCK register
//
//*************************************************************************************************
#define SYSCTL_SYNCSOCLOCK_SYNCSELECT         0x1U   // SYNCSEL Register Lock bit
#define SYSCTL_SYNCSOCLOCK_ADCSOCOUTSELECT    0x2U   // ADCSOCOUTSELECT Register Lock bit
#define SYSCTL_SYNCSOCLOCK_ADCSOCOUTSELECT1   0x4U   // ADCSOCOUTSELECT1 Register Lock bit


//*************************************************************************************************
//
// The following are defines for the bit fields in the LFUConfig register
//
//*************************************************************************************************
#define SYSCTL_LFUCONFIG_LFU_CPU         0x1U        // SW configuration to implement LFU
#define SYSCTL_LFUCONFIG_LFU_CLA1        0x10U       // SW configuration to implement LFU
#define SYSCTL_LFUCONFIG_PIEVECTORSWAP   0x1000U     // Swap of pie vector table
#define SYSCTL_LFUCONFIG_LS01SWAP        0x100000U   // Swap LS0 and LS1 memory

//*************************************************************************************************
//
// The following are defines for the bit fields in the LFUStatus register
//
//*************************************************************************************************
#define SYSCTL_LFUSTATUS_PIEVECTORSWAP   0x1000U     // Indicate the status of PieVectorSwap
#define SYSCTL_LFUSTATUS_LS01SWAP        0x100000U   // Indicate the status of LS0/LS1 memory swap

//*************************************************************************************************
//
// The following are defines for the bit fields in the LFU_LOCK register
//
//*************************************************************************************************
#define SYSCTL_LFU_LOCK_LFUCONFIG            0x1U      // Register lock configuration
#define SYSCTL_LFU_LOCK_SWCONFIG1_SYSRSN     0x100U    // Register lock configuration
#define SYSCTL_LFU_LOCK_SWCONFIG2_SYSRSN     0x200U    // Register lock configuration
#define SYSCTL_LFU_LOCK_SWCONFIG1_XRSN       0x400U    // Register lock configuration
#define SYSCTL_LFU_LOCK_SWCONFIG2_XRSN       0x800U    // Register lock configuration
#define SYSCTL_LFU_LOCK_SWCONFIG1_PORESETN   0x1000U   // Register lock configuration
#define SYSCTL_LFU_LOCK_SWCONFIG2_PORESETN   0x2000U   // Register lock configuration

//*************************************************************************************************
//
// The following are defines for the bit fields in the LFU_COMMIT register
//
//*************************************************************************************************
#define SYSCTL_LFU_COMMIT_LFUCONFIG            0x1U      // Register commit configuration
#define SYSCTL_LFU_COMMIT_SWCONFIG1_SYSRSN     0x100U    // Register commit configuration
#define SYSCTL_LFU_COMMIT_SWCONFIG2_SYSRSN     0x200U    // Register commit configuration
#define SYSCTL_LFU_COMMIT_SWCONFIG1_XRSN       0x400U    // Register commit configuration
#define SYSCTL_LFU_COMMIT_SWCONFIG2_XRSN       0x800U    // Register commit configuration
#define SYSCTL_LFU_COMMIT_SWCONFIG1_PORESETN   0x1000U   // Register commit configuration
#define SYSCTL_LFU_COMMIT_SWCONFIG2_PORESETN   0x2000U   // Register commit configuration


//*************************************************************************************************
//
// The following are defines for the bit fields in the LFUConfig_ALT_ register
//
//*************************************************************************************************
#define SYSCTL_LFUCONFIG_ALT__LFU_CPU         0x1U        // SW configuration to implement LFU
#define SYSCTL_LFUCONFIG_ALT__PIEVECTORSWAP   0x1000U     // Swap of pie vector table
#define SYSCTL_LFUCONFIG_ALT__D23SWAP         0x100000U   // Swap D2 and D3 memory

//*************************************************************************************************
//
// The following are defines for the bit fields in the LFUStatus_ALT_ register
//
//*************************************************************************************************
#define SYSCTL_LFUSTATUS_ALT__PIEVECTORSWAP   0x1000U     // Indicate the status of PieVectorSwap
#define SYSCTL_LFUSTATUS_ALT__D23SWAP         0x100000U   // Indicate the status of D2/3 memory
                                                          // swap

//*************************************************************************************************
//
// The following are defines for the bit fields in the LFU_LOCK register
//
//*************************************************************************************************
#define SYSCTL_LFU_LOCK_LFUCONFIG            0x1U      // Register lock configuration
#define SYSCTL_LFU_LOCK_SWCONFIG1_SYSRSN     0x100U    // Register lock configuration
#define SYSCTL_LFU_LOCK_SWCONFIG2_SYSRSN     0x200U    // Register lock configuration
#define SYSCTL_LFU_LOCK_SWCONFIG1_XRSN       0x400U    // Register lock configuration
#define SYSCTL_LFU_LOCK_SWCONFIG2_XRSN       0x800U    // Register lock configuration
#define SYSCTL_LFU_LOCK_SWCONFIG1_PORESETN   0x1000U   // Register lock configuration
#define SYSCTL_LFU_LOCK_SWCONFIG2_PORESETN   0x2000U   // Register lock configuration

//*************************************************************************************************
//
// The following are defines for the bit fields in the LFU_COMMIT register
//
//*************************************************************************************************
#define SYSCTL_LFU_COMMIT_LFUCONFIG            0x1U      // Register commit configuration
#define SYSCTL_LFU_COMMIT_SWCONFIG1_SYSRSN     0x100U    // Register commit configuration
#define SYSCTL_LFU_COMMIT_SWCONFIG2_SYSRSN     0x200U    // Register commit configuration
#define SYSCTL_LFU_COMMIT_SWCONFIG1_XRSN       0x400U    // Register commit configuration
#define SYSCTL_LFU_COMMIT_SWCONFIG2_XRSN       0x800U    // Register commit configuration
#define SYSCTL_LFU_COMMIT_SWCONFIG1_PORESETN   0x1000U   // Register commit configuration
#define SYSCTL_LFU_COMMIT_SWCONFIG2_PORESETN   0x2000U   // Register commit configuration


//*************************************************************************************************
//
// The following are defines for the bit fields in the SYS_ERR_INT_FLG register
//
//*************************************************************************************************
#define SYSCTL_SYS_ERR_INT_FLG_GINT              0x1U     // Global Interrupt flag
#define SYSCTL_SYS_ERR_INT_FLG_EMIF_ERR          0x2U     // EMIF error event flag
#define SYSCTL_SYS_ERR_INT_FLG_CORRECTABLE_ERR   0x4U     // RAM/Flash correctable error flag
#define SYSCTL_SYS_ERR_INT_FLG_RAM_ACC_VIOL      0x10U    // A RAM access vioation flag.
#define SYSCTL_SYS_ERR_INT_FLG_SYS_PLL_SLIP      0x20U    // System PLL Slip event flag.
#define SYSCTL_SYS_ERR_INT_FLG_AUX_PLL_SLIP      0x40U    // Auxillary PLL Slip event flag.
#define SYSCTL_SYS_ERR_INT_FLG_DCC0              0x80U    // DCC0 Interrupt flag.
#define SYSCTL_SYS_ERR_INT_FLG_DCC1              0x100U   // DCC1 Interrupt flag.
#define SYSCTL_SYS_ERR_INT_FLG_DCC2              0x200U   // DCC2 Interrupt flag.
#define SYSCTL_SYS_ERR_INT_FLG_AES_BUS_ERROR     0x400U   // AES_BUS_ERROR Interrupt flag.
#define SYSCTL_SYS_ERR_INT_FLG_EPG1_INT          0x800U   // EPG1_INT Interrupt flag.

//*************************************************************************************************
//
// The following are defines for the bit fields in the SYS_ERR_INT_CLR register
//
//*************************************************************************************************
#define SYSCTL_SYS_ERR_INT_CLR_GINT              0x1U     // Global Interrupt flag Clear bit
#define SYSCTL_SYS_ERR_INT_CLR_EMIF_ERR          0x2U     // EMIF_ERR interrupt flag clear bit
#define SYSCTL_SYS_ERR_INT_CLR_CORRECTABLE_ERR   0x4U     // CORRECTABLE_ERR interrupt flag clear
                                                          // bit
#define SYSCTL_SYS_ERR_INT_CLR_RAM_ACC_VIOL      0x10U    // RAM_ACC_VIOL interrupt flag clear bit
#define SYSCTL_SYS_ERR_INT_CLR_SYS_PLL_SLIP      0x20U    // SYS_PLL_SLIP interrupt flag clear bit
#define SYSCTL_SYS_ERR_INT_CLR_AUX_PLL_SLIP      0x40U    // AUX_PLL_SLIP interrupt flag clear bit
#define SYSCTL_SYS_ERR_INT_CLR_DCC0              0x80U    // DCC0 interrupt flag clear bit
#define SYSCTL_SYS_ERR_INT_CLR_DCC1              0x100U   // DCC1 interrupt flag clear bit
#define SYSCTL_SYS_ERR_INT_CLR_DCC2              0x200U   // DCC2 interrupt flag clear bit
#define SYSCTL_SYS_ERR_INT_CLR_AES_BUS_ERROR     0x400U   // AES_BUS_ERROR interrupt flag clear bit
#define SYSCTL_SYS_ERR_INT_CLR_EPG1_INT          0x800U   // EPG1_INT interrupt flag clear bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SYS_ERR_INT_SET register
//
//*************************************************************************************************
#define SYSCTL_SYS_ERR_INT_SET_EMIF_ERR          0x2U          // EMIF_ERR interrupt flag set bit
#define SYSCTL_SYS_ERR_INT_SET_CORRECTABLE_ERR   0x4U          // CORRECTABLE_ERR interrupt flag
                                                               // set bit
#define SYSCTL_SYS_ERR_INT_SET_RAM_ACC_VIOL      0x10U         // RAM_ACC_VIOL interrupt flag set
                                                               // bit
#define SYSCTL_SYS_ERR_INT_SET_SYS_PLL_SLIP      0x20U         // SYS_PLL_SLIP interrupt flag set
                                                               // bit
#define SYSCTL_SYS_ERR_INT_SET_AUX_PLL_SLIP      0x40U         // AUX_PLL_SLIP interrupt flag set
                                                               // bit
#define SYSCTL_SYS_ERR_INT_SET_DCC0              0x80U         // DCC0 interrupt flag set bit
#define SYSCTL_SYS_ERR_INT_SET_DCC1              0x100U        // DCC1 interrupt flag set bit
#define SYSCTL_SYS_ERR_INT_SET_DCC2              0x200U        // DCC2 interrupt flag set bit
#define SYSCTL_SYS_ERR_INT_SET_AES_BUS_ERROR     0x400U        // AES_BUS_ERROR interrupt flag set
                                                               // bit
#define SYSCTL_SYS_ERR_INT_SET_EPG1_INT          0x800U        // EPG1_INT interrupt flag set bit
#define SYSCTL_SYS_ERR_INT_SET_KEY_S             24U
#define SYSCTL_SYS_ERR_INT_SET_KEY_M             0xFF000000U   // KEY field

//*************************************************************************************************
//
// The following are defines for the bit fields in the SYS_ERR_MASK register
//
//*************************************************************************************************
#define SYSCTL_SYS_ERR_MASK_EMIF_ERR          0x2U          // EMIF_ERR flag mask bit
#define SYSCTL_SYS_ERR_MASK_CORRECTABLE_ERR   0x4U          // CORRECTABLE_ERR flag mask bit
#define SYSCTL_SYS_ERR_MASK_RAM_ACC_VIOL      0x10U         // RAM_ACC_VIOL flag mask bit
#define SYSCTL_SYS_ERR_MASK_SYS_PLL_SLIP      0x20U         // SYS_PLL_SLIP flag mask bit
#define SYSCTL_SYS_ERR_MASK_AUX_PLL_SLIP      0x40U         // AUX_PLL_SLIP flag mask bit
#define SYSCTL_SYS_ERR_MASK_DCC0              0x80U         // DCC0 flag mask bit
#define SYSCTL_SYS_ERR_MASK_DCC1              0x100U        // DCC1 flag mask bit
#define SYSCTL_SYS_ERR_MASK_DCC2              0x200U        // DCC2 flag mask bit
#define SYSCTL_SYS_ERR_MASK_AES_BUS_ERROR     0x400U        // AES_BUS_ERROR flag mask bit
#define SYSCTL_SYS_ERR_MASK_EPG1_INT          0x800U        // EPG1_INT flag mask bit
#define SYSCTL_SYS_ERR_MASK_KEY_S             24U
#define SYSCTL_SYS_ERR_MASK_KEY_M             0xFF000000U   // KEY field




//*************************************************************************************************
//
// The following are defines for the bit fields in the LCM_ERR_FLG register
//
//*************************************************************************************************
#define SYSCTL_LCM_ERR_FLG_GERR   0x1U   // Global Error event flag
#define SYSCTL_LCM_ERR_FLG_CPU    0x2U   // CPU Lokstep Miscompare flag
#define SYSCTL_LCM_ERR_FLG_DMA    0x4U   // DMA Lokstep Miscompare flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the LCM_ERR_FLG_CLR register
//
//*************************************************************************************************
#define SYSCTL_LCM_ERR_FLG_CLR_GERR   0x1U   // Global Error event flag
#define SYSCTL_LCM_ERR_FLG_CLR_CPU    0x2U   // CPU Lokstep Miscompare flag
#define SYSCTL_LCM_ERR_FLG_CLR_DMA    0x4U   // DMA Lokstep Miscompare flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the LCM_ERR_FLG_SET register
//
//*************************************************************************************************
#define SYSCTL_LCM_ERR_FLG_SET_CPU     0x2U          // CPU Lokstep Miscompare flag set
#define SYSCTL_LCM_ERR_FLG_SET_DMA     0x4U          // DMA Lokstep Miscompare flag set
#define SYSCTL_LCM_ERR_FLG_SET_KEY_S   24U
#define SYSCTL_LCM_ERR_FLG_SET_KEY_M   0xFF000000U   // KEY field

//*************************************************************************************************
//
// The following are defines for the bit fields in the LCM_ERR_FLG_MASK register
//
//*************************************************************************************************
#define SYSCTL_LCM_ERR_FLG_MASK_CPU     0x2U          // CPU Lokstep Miscompare flag mask
#define SYSCTL_LCM_ERR_FLG_MASK_DMA     0x4U          // DMA Lokstep Miscompare flag mask
#define SYSCTL_LCM_ERR_FLG_MASK_KEY_S   24U
#define SYSCTL_LCM_ERR_FLG_MASK_KEY_M   0xFF000000U   // KEY field

//*************************************************************************************************
//
// The following are defines for the bit fields in the REGPARITY_ERR_FLG register
//
//*************************************************************************************************
#define SYSCTL_REGPARITY_ERR_FLG_GERR   0x1U   // Global Error event flag
#define SYSCTL_REGPARITY_ERR_FLG_CPU    0x2U   // Register parity error from lockstep compare
                                               // module
#define SYSCTL_REGPARITY_ERR_FLG_DMA    0x4U   // Register parity error from lockstep compare
                                               // module

//*************************************************************************************************
//
// The following are defines for the bit fields in the REGPARITY_ERR_FLG_CLR register
//
//*************************************************************************************************
#define SYSCTL_REGPARITY_ERR_FLG_CLR_GERR   0x1U   // Global Error event flag clear
#define SYSCTL_REGPARITY_ERR_FLG_CLR_CPU    0x2U   // Register parity error from lockstep compare
                                                   // module clear
#define SYSCTL_REGPARITY_ERR_FLG_CLR_DMA    0x4U   // Register parity error from lockstep compare
                                                   // module clear

//*************************************************************************************************
//
// The following are defines for the bit fields in the REGPARITY_ERR_FLG_SET register
//
//*************************************************************************************************
#define SYSCTL_REGPARITY_ERR_FLG_SET_CPU     0x2U          // Register parity error from lockstep
                                                           // compare module set
#define SYSCTL_REGPARITY_ERR_FLG_SET_DMA     0x4U          // Register parity error from lockstep
                                                           // compare module set
#define SYSCTL_REGPARITY_ERR_FLG_SET_KEY_S   24U
#define SYSCTL_REGPARITY_ERR_FLG_SET_KEY_M   0xFF000000U   // KEY field

//*************************************************************************************************
//
// The following are defines for the bit fields in the REGPARITY_ERR_FLG_MASK register
//
//*************************************************************************************************
#define SYSCTL_REGPARITY_ERR_FLG_MASK_CPU     0x2U          // Register parity error from lockstep
                                                            // compare module mask
#define SYSCTL_REGPARITY_ERR_FLG_MASK_DMA     0x4U          // Register parity error from lockstep
                                                            // compare module mask
#define SYSCTL_REGPARITY_ERR_FLG_MASK_KEY_S   24U
#define SYSCTL_REGPARITY_ERR_FLG_MASK_KEY_M   0xFF000000U   // KEY field



#endif
