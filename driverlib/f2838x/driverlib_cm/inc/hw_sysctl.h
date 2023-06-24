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
#define SYSCTL_O_CMPCLKCR0           0x0U     // CM Peripheral clock gating register 0.
#define SYSCTL_O_CMPCLKCR1           0x4U     // CM Peripheral clock gating register 1.
#define SYSCTL_O_CMPCLKCR2           0x8U     // CM Peripheral clock gating register 2.
#define SYSCTL_O_CMSOFTPRESET0       0x20U    // CM Software Peripheral Reset register 0
#define SYSCTL_O_CMSOFTPRESET1       0x24U    // CM Software Peripheral Reset register 1
#define SYSCTL_O_CMSOFTPRESET2       0x28U    // CM Software Peripheral Reset register 2
#define SYSCTL_O_CMCLKSTOPREQ0       0x40U    // Peripheral Clock Stop Request Register 0
#define SYSCTL_O_CMCLKSTOPREQ1       0x44U    // Peripheral Clock Stop Request Register 1
#define SYSCTL_O_CMCLKSTOPREQ2       0x48U    // Peripheral Clock Stop Request Register 2
#define SYSCTL_O_CMCLKSTOPACK1       0x64U    // Peripheral Clock Stop Ackonwledge Register 1
#define SYSCTL_O_MCANWAKESTATUS      0xE0U    // MCAN Wake Status Register
#define SYSCTL_O_MCANWAKESTATUSCLR   0xE4U    // MCAN Wake Status Clear Register
#define SYSCTL_O_PALLOCATESTS        0x1F4U   // Status of PALLOCATE register.
#define SYSCTL_O_CMRESCCLR           0x1F8U   // CM Reset Cause Status Clear Register
#define SYSCTL_O_CMRESC              0x1FCU   // CM Reset Cause Status Register
#define SYSCTL_O_CMSYSCTLLOCK        0x200U   // Locks the configuration registers of CM System
                                              // control


//*************************************************************************************************
//
// The following are defines for the bit fields in the CMPCLKCR0 register
//
//*************************************************************************************************
#define SYSCTL_CMPCLKCR0_UART0   0x1U          // UART0 Clock gating Bit
#define SYSCTL_CMPCLKCR0_SSI0    0x10U         // SSI0 Clock gating Bit
#define SYSCTL_CMPCLKCR0_I2C0    0x100U        // I2C0 Clock gating Bit
#define SYSCTL_CMPCLKCR0_USB     0x1000U       // USB Clock gating Bit
#define SYSCTL_CMPCLKCR0_KEY_S   16U
#define SYSCTL_CMPCLKCR0_KEY_M   0xFFFF0000U   // Key field

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMPCLKCR1 register
//
//*************************************************************************************************
#define SYSCTL_CMPCLKCR1_ETHERNET   0x1U          // ETHERNET Clock gating Bit
#define SYSCTL_CMPCLKCR1_ETHERCAT   0x4U          // ETHERCAT Clock gating Bit
#define SYSCTL_CMPCLKCR1_CAN_A      0x10U         // CAN_A Clock gating Bit
#define SYSCTL_CMPCLKCR1_CAN_B      0x20U         // CAN_B Clock gating Bit
#define SYSCTL_CMPCLKCR1_MCAN_A     0x100U        // MCAN_A Clock gating Bit
#define SYSCTL_CMPCLKCR1_KEY_S      16U
#define SYSCTL_CMPCLKCR1_KEY_M      0xFFFF0000U   // Key field

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMPCLKCR2 register
//
//*************************************************************************************************
#define SYSCTL_CMPCLKCR2_CPUTIMER0   0x1U          // CPUTIMER0 Clock gating Bit
#define SYSCTL_CMPCLKCR2_CPUTIMER1   0x2U          // CPUTIMER1 Clock gating Bit
#define SYSCTL_CMPCLKCR2_CPUTIMER2   0x4U          // CPUTIMER2 Clock gating Bit
#define SYSCTL_CMPCLKCR2_UDMA        0x10U         // UDMA Clock gating Bit
#define SYSCTL_CMPCLKCR2_AESIP       0x40U         // AESIP Clock gating Bit
#define SYSCTL_CMPCLKCR2_GCRC        0x100U        // GCRC Clock gating Bit
#define SYSCTL_CMPCLKCR2_KEY_S       16U
#define SYSCTL_CMPCLKCR2_KEY_M       0xFFFF0000U   // Key field

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMSOFTPRESET0 register
//
//*************************************************************************************************
#define SYSCTL_CMSOFTPRESET0_UART0   0x1U          // UART0 Soft reset bit
#define SYSCTL_CMSOFTPRESET0_SSI0    0x10U         // SSI0 Soft reset bit
#define SYSCTL_CMSOFTPRESET0_I2C0    0x100U        // I2C0 Soft reset bit
#define SYSCTL_CMSOFTPRESET0_USB     0x1000U       // USB Soft reset bit
#define SYSCTL_CMSOFTPRESET0_KEY_S   16U
#define SYSCTL_CMSOFTPRESET0_KEY_M   0xFFFF0000U   // Key field

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMSOFTPRESET1 register
//
//*************************************************************************************************
#define SYSCTL_CMSOFTPRESET1_ETHERNET   0x1U          // ETHERNET Soft reset bit
#define SYSCTL_CMSOFTPRESET1_ETHERCAT   0x4U          // ETHERCAT Soft reset bit
#define SYSCTL_CMSOFTPRESET1_CAN_A      0x10U         // CAN_A Soft reset bit
#define SYSCTL_CMSOFTPRESET1_CAN_B      0x20U         // CAN_B Soft reset bit
#define SYSCTL_CMSOFTPRESET1_MCAN_A     0x100U        // MCAN_A Soft reset bit
#define SYSCTL_CMSOFTPRESET1_KEY_S      16U
#define SYSCTL_CMSOFTPRESET1_KEY_M      0xFFFF0000U   // Key field

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMSOFTPRESET2 register
//
//*************************************************************************************************
#define SYSCTL_CMSOFTPRESET2_AESIP   0x40U         // AESIP Soft reset bit
#define SYSCTL_CMSOFTPRESET2_GCRC    0x100U        // GCRC Soft reset bit
#define SYSCTL_CMSOFTPRESET2_KEY_S   16U
#define SYSCTL_CMSOFTPRESET2_KEY_M   0xFFFF0000U   // Key field

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMCLKSTOPREQ0 register
//
//*************************************************************************************************
#define SYSCTL_CMCLKSTOPREQ0_KEY_S   16U
#define SYSCTL_CMCLKSTOPREQ0_KEY_M   0xFFFF0000U   // Key field

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMCLKSTOPREQ1 register
//
//*************************************************************************************************
#define SYSCTL_CMCLKSTOPREQ1_MCAN_A   0x100U        // MCAN_A Clock Stop Request Bit
#define SYSCTL_CMCLKSTOPREQ1_KEY_S    16U
#define SYSCTL_CMCLKSTOPREQ1_KEY_M    0xFFFF0000U   // Key field

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMCLKSTOPREQ2 register
//
//*************************************************************************************************
#define SYSCTL_CMCLKSTOPREQ2_KEY_S   16U
#define SYSCTL_CMCLKSTOPREQ2_KEY_M   0xFFFF0000U   // Key field

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMCLKSTOPACK1 register
//
//*************************************************************************************************
#define SYSCTL_CMCLKSTOPACK1_MCAN_A   0x100U   // MCAN_A Clock Stop Ack Bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCANWAKESTATUS register
//
//*************************************************************************************************
#define SYSCTL_MCANWAKESTATUS_WAKE   0x1U   // MCAN Wake Status

//*************************************************************************************************
//
// The following are defines for the bit fields in the MCANWAKESTATUSCLR register
//
//*************************************************************************************************
#define SYSCTL_MCANWAKESTATUSCLR_WAKE   0x1U   // Cear bit for MCANWAKESTATUS.WAKE bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the PALLOCATESTS register
//
//*************************************************************************************************
#define SYSCTL_PALLOCATESTS_USB        0x1U    // Status of PALLOCATE.USB bit
#define SYSCTL_PALLOCATESTS_ETHERCAT   0x2U    // Status of PALLOCATE.ETHERCAT bit
#define SYSCTL_PALLOCATESTS_CAN_A      0x4U    // Status of PALLOCATE.CAN_A bit
#define SYSCTL_PALLOCATESTS_CAN_B      0x8U    // Status of PALLOCATE.CAN_B bit
#define SYSCTL_PALLOCATESTS_MCAN_A     0x10U   // Status of PALLOCATE.MCAN_A bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMRESCCLR register
//
//*************************************************************************************************
#define SYSCTL_CMRESCCLR_PORESETN              0x1U       // PORESETn status flag clear
#define SYSCTL_CMRESCCLR_XRSN                  0x2U       // XRSn status flag clear
#define SYSCTL_CMRESCCLR_CPU1WDRSN             0x4U       // CPU1WDRSn status flag clear
#define SYSCTL_CMRESCCLR_CPU1NMIWDRSN          0x8U       // CPU1NMIWDRSn status flag clear
#define SYSCTL_CMRESCCLR_CPU1SYSRSN            0x10U      // CPU1SYSRSN status flag clear
#define SYSCTL_CMRESCCLR_CPU1SCCRESETN         0x20U      // CPU1SCCRESETn status flag clear
#define SYSCTL_CMRESCCLR_ECAT_RESET_OUT        0x40U      // ECAT_RESET_OUT status flag clear
#define SYSCTL_CMRESCCLR_CPU1SIMRESET_CPURSN   0x80U      // CPU1SIMRESET_CPURSn status flag clear
#define SYSCTL_CMRESCCLR_CMRSTCTLRESETREQ      0x100U     // CMRSTCTLRESETREQ status flag clear
#define SYSCTL_CMRESCCLR_CPU1_SIMRESET_XRSN    0x200U     // CPU1_SIMRESET_XRSn status flag clear
#define SYSCTL_CMRESCCLR_CMVECTRESETN          0x10000U   // CMVECTRESETn status flag clear
#define SYSCTL_CMRESCCLR_CMSYSRESETREQ         0x20000U   // CMSYSRESETREQ status flag clear
#define SYSCTL_CMRESCCLR_CMNMIWDRSTN           0x40000U   // CMNMIWDRSTn status flag clear
#define SYSCTL_CMRESCCLR_CMEOLRESETN           0x80000U   // CMEOLRESETn status flag clear

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMRESC register
//
//*************************************************************************************************
#define SYSCTL_CMRESC_PORESETN               0x1U       // PORESETn caused the reset of CM
#define SYSCTL_CMRESC_XRSN                   0x2U       // XRSn caused the reset of CM
#define SYSCTL_CMRESC_CPU1_WDRSN             0x4U       // CPU1_WDRSn caused the reset of CM
#define SYSCTL_CMRESC_CPU1_NMIWDRSN          0x8U       // CPU1_NMIWDRSn caused the reset of CM
#define SYSCTL_CMRESC_CPU1_SYSRSN            0x10U      // CPU1_SYSRSN caused the reset of CM
#define SYSCTL_CMRESC_CPU1_SCCRESETN         0x20U      // CPU1_SCCRESETn caused the reset of CM
#define SYSCTL_CMRESC_ECAT_RESET_OUT         0x40U      // ECAT_RESET_OUT caused the reset of CM
#define SYSCTL_CMRESC_CPU1_SIMRESET_CPURSN   0x80U      // CPU1_SIMRESET_CPURSn caused the reset of
                                                        // CM
#define SYSCTL_CMRESC_CMRSTCTL_RESETREQ      0x100U     // CMRSTCTL_RESETREQ caused the reset of CM
#define SYSCTL_CMRESC_CPU1_SIMRESET_XRSN     0x200U     // CPU1_SIMRESET_XRSn caused the reset of
                                                        // CM
#define SYSCTL_CMRESC_CMVECTRESETN           0x10000U   // CMVECTRESETn caused the reset of CM
#define SYSCTL_CMRESC_CMSYSRESETREQ          0x20000U   // CMSYSRESETREQ caused the reset of CM
#define SYSCTL_CMRESC_CMNMIWDRSTN            0x40000U   // CMNMIWDRSTn caused the reset of CM
#define SYSCTL_CMRESC_CMEOLRESETN            0x80000U   // CMEOLRESETn caused the reset of CM

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMSYSCTLLOCK register
//
//*************************************************************************************************
#define SYSCTL_CMSYSCTLLOCK_LOCK   0x1U   // Locks the configuration registers of CM System Control



#endif
