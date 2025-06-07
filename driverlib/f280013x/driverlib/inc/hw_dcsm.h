//###########################################################################
//
// FILE:    hw_dcsm.h
//
// TITLE:   Definitions for the DCSM registers.
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

#ifndef HW_DCSM_H
#define HW_DCSM_H

//*************************************************************************************************
//
// The following are defines for the DCSM register offsets
//
//*************************************************************************************************
#define DCSM_O_Z1OTP_LINKPOINTER1   0x0U    // Zone 1 Link Pointer1
#define DCSM_O_Z1OTP_LINKPOINTER2   0x2U    // Zone 1 Link Pointer2
#define DCSM_O_Z1OTP_LINKPOINTER3   0x4U    // Zone 1 Link Pointer3
#define DCSM_O_Z1OTP_JLM_ENABLE     0x6U    // Zone 1 JTAGLOCK Enable Register
#define DCSM_O_Z1OTP_GPREG1         0x8U    // Zone 1 General Purpose Register 1
#define DCSM_O_Z1OTP_GPREG2         0xAU    // Zone 1 General Purpose Register 2
#define DCSM_O_Z1OTP_GPREG3         0xCU    // Zone 1 General Purpose Register 3
#define DCSM_O_Z1OTP_GPREG4         0xEU    // Zone 1 General Purpose Register 4
#define DCSM_O_Z1OTP_PSWDLOCK       0x10U   // Secure Password Lock
#define DCSM_O_Z1OTP_JTAGPSWDH0     0x14U   // JTAG Lock Permanent Password 0
#define DCSM_O_Z1OTP_JTAGPSWDH1     0x16U   // JTAG Lock Permanent Password 1
#define DCSM_O_Z1OTP_CMACKEY0       0x18U   // Secure Boot CMAC Key 0
#define DCSM_O_Z1OTP_CMACKEY1       0x1AU   // Secure Boot CMAC Key 1
#define DCSM_O_Z1OTP_CMACKEY2       0x1CU   // Secure Boot CMAC Key 2
#define DCSM_O_Z1OTP_CMACKEY3       0x1EU   // Secure Boot CMAC Key 3

#define DCSM_O_Z2OTP_LINKPOINTER1   0x0U    // Zone 2 Link Pointer1
#define DCSM_O_Z2OTP_LINKPOINTER2   0x2U    // Zone 2 Link Pointer2
#define DCSM_O_Z2OTP_LINKPOINTER3   0x4U    // Zone 2 Link Pointer3
#define DCSM_O_Z2OTP_GPREG1         0x8U    // Zone 2 General Purpose Register 1
#define DCSM_O_Z2OTP_GPREG2         0xAU    // Zone 2 General Purpose Register 2
#define DCSM_O_Z2OTP_GPREG3         0xCU    // Zone 2 General Purpose Register 3
#define DCSM_O_Z2OTP_GPREG4         0xEU    // Zone 2 General Purpose Register 4
#define DCSM_O_Z2OTP_PSWDLOCK       0x10U   // Secure Password Lock

#define DCSM_O_Z1_LINKPOINTER      0x0U    // Zone 1 Link Pointer
#define DCSM_O_Z1_OTPSECLOCK       0x2U    // Zone 1 OTP Secure Lock
#define DCSM_O_Z1_JLM_ENABLE       0x4U    // Zone 1 JTAGLOCK Enable Register
#define DCSM_O_Z1_LINKPOINTERERR   0x6U    // Link Pointer Error
#define DCSM_O_Z1_GPREG1           0x8U    // Zone 1 General Purpose Register-1
#define DCSM_O_Z1_GPREG2           0xAU    // Zone 1 General Purpose Register-2
#define DCSM_O_Z1_GPREG3           0xCU    // Zone 1 General Purpose Register-3
#define DCSM_O_Z1_GPREG4           0xEU    // Zone 1 General Purpose Register-4
#define DCSM_O_Z1_CSMKEY0          0x10U   // Zone 1 CSM Key 0
#define DCSM_O_Z1_CSMKEY1          0x12U   // Zone 1 CSM Key 1
#define DCSM_O_Z1_CSMKEY2          0x14U   // Zone 1 CSM Key 2
#define DCSM_O_Z1_CSMKEY3          0x16U   // Zone 1 CSM Key 3
#define DCSM_O_Z1_CR               0x18U   // Zone 1 CSM Control Register
#define DCSM_O_Z1_GRABSECT1R       0x1AU   // Zone 1 Grab Flash Status Register 1
#define DCSM_O_Z1_GRABSECT2R       0x1CU   // Zone 1 Grab Flash Status Register 2
#define DCSM_O_Z1_GRABSECT3R       0x1EU   // Zone 1 Grab Flash Status Register 3
#define DCSM_O_Z1_GRABRAM1R        0x20U   // Zone 1 Grab RAM Status Register 1
#define DCSM_O_Z1_EXEONLYSECT1R    0x26U   // Zone 1 Execute Only Flash Status Register 1
#define DCSM_O_Z1_EXEONLYSECT2R    0x28U   // Zone 1 Execute Only Flash Status Register 2
#define DCSM_O_Z1_EXEONLYRAM1R     0x2AU   // Zone 1 Execute Only RAM Status Register 1
#define DCSM_O_Z1_JTAGKEY0         0x2EU   // JTAG Unlock Key Register 0
#define DCSM_O_Z1_JTAGKEY1         0x30U   // JTAG Unlock Key Register 1
#define DCSM_O_Z1_JTAGKEY2         0x32U   // JTAG Unlock Key Register 2
#define DCSM_O_Z1_JTAGKEY3         0x34U   // JTAG Unlock Key Register 3
#define DCSM_O_Z1_CMACKEY0         0x36U   // Secure Boot CMAC Key Status Register 0
#define DCSM_O_Z1_CMACKEY1         0x38U   // Secure Boot CMAC Key Status Register 1
#define DCSM_O_Z1_CMACKEY2         0x3AU   // Secure Boot CMAC Key Status Register 2
#define DCSM_O_Z1_CMACKEY3         0x3CU   // Secure Boot CMAC Key Status Register 3

#define DCSM_O_Z2_LINKPOINTER      0x0U    // Zone 2 Link Pointer
#define DCSM_O_Z2_OTPSECLOCK       0x2U    // Zone 2 OTP Secure Lock
#define DCSM_O_Z2_LINKPOINTERERR   0x6U    // Link Pointer Error
#define DCSM_O_Z2_GPREG1           0x8U    // Zone 2 General Purpose Register-1
#define DCSM_O_Z2_GPREG2           0xAU    // Zone 2 General Purpose Register-2
#define DCSM_O_Z2_GPREG3           0xCU    // Zone 2 General Purpose Register-3
#define DCSM_O_Z2_GPREG4           0xEU    // Zone 2 General Purpose Register-4
#define DCSM_O_Z2_CSMKEY0          0x10U   // Zone 2 CSM Key 0
#define DCSM_O_Z2_CSMKEY1          0x12U   // Zone 2 CSM Key 1
#define DCSM_O_Z2_CSMKEY2          0x14U   // Zone 2 CSM Key 2
#define DCSM_O_Z2_CSMKEY3          0x16U   // Zone 2 CSM Key 3
#define DCSM_O_Z2_CR               0x18U   // Zone 2 CSM Control Register
#define DCSM_O_Z2_GRABSECT1R       0x1AU   // Zone 2 Grab Flash Status Register 1
#define DCSM_O_Z2_GRABSECT2R       0x1CU   // Zone 2 Grab Flash Status Register 2
#define DCSM_O_Z2_GRABSECT3R       0x1EU   // Zone 2 Grab Flash Status Register 3
#define DCSM_O_Z2_GRABRAM1R        0x20U   // Zone 2 Grab RAM Status Register 1
#define DCSM_O_Z2_EXEONLYSECT1R    0x26U   // Zone 2 Execute Only Flash Status Register 1
#define DCSM_O_Z2_EXEONLYSECT2R    0x28U   // Zone 2 Execute Only Flash Status Register 2
#define DCSM_O_Z2_EXEONLYRAM1R     0x2AU   // Zone 2 Execute Only RAM Status Register 1

#define DCSM_O_FLSEM         0x0U    // Flash Wrapper Semaphore Register
#define DCSM_O_SECTSTAT1     0x8U    // Flash Sectors Status Register 1
#define DCSM_O_SECTSTAT2     0xAU    // Flash Sectors Status Register 2
#define DCSM_O_SECTSTAT3     0xCU    // Flash Sectors Status Register 3
#define DCSM_O_RAMSTAT1      0x10U   // RAM Status Register 1
#define DCSM_O_SECERRSTAT    0x18U   // Security Error Status Register
#define DCSM_O_SECERRCLR     0x1AU   // Security Error Clear Register
#define DCSM_O_SECERRFRC     0x1CU   // Security Error Force Register
#define DCSM_O_DENYCODE      0x1EU   // Flash Authorization Denial Code
#define DCSM_O_RAMOPENSTAT   0x20U   // RAM Security Open Status Register
#define DCSM_O_RAMOPENFRC    0x22U   // RAM Security Open Force Register
#define DCSM_O_RAMOPENCLR    0x24U   // RAM Security Open Clear Register
#define DCSM_O_RAMOPENLOCK   0x26U   // RAMOPEN Lock Register




//*************************************************************************************************
//
// The following are defines for the bit fields in the Z1_LINKPOINTER register
//
//*************************************************************************************************
#define DCSM_Z1_LINKPOINTER_LINKPOINTER_S   0U
#define DCSM_Z1_LINKPOINTER_LINKPOINTER_M   0x3FFFU   // Zone1 LINK Pointer

//*************************************************************************************************
//
// The following are defines for the bit fields in the Z1_OTPSECLOCK register
//
//*************************************************************************************************
#define DCSM_Z1_OTPSECLOCK_JTAGLOCK     0x1U    // JTAG Lock Status
#define DCSM_Z1_OTPSECLOCK_PSWDLOCK_S   4U
#define DCSM_Z1_OTPSECLOCK_PSWDLOCK_M   0xF0U   // Zone1 Password Lock.

//*************************************************************************************************
//
// The following are defines for the bit fields in the Z1_JLM_ENABLE register
//
//*************************************************************************************************
#define DCSM_Z1_JLM_ENABLE_Z1_JLM_ENABLE_S   0U
#define DCSM_Z1_JLM_ENABLE_Z1_JLM_ENABLE_M   0xFU   // Zone1 JLM_ENABLE register.

//*************************************************************************************************
//
// The following are defines for the bit fields in the Z1_LINKPOINTERERR register
//
//*************************************************************************************************
#define DCSM_Z1_LINKPOINTERERR_Z1_LINKPOINTERERR_S   0U
#define DCSM_Z1_LINKPOINTERERR_Z1_LINKPOINTERERR_M   0x3FFFU   // Error to Resolve Z1 Link pointer
                                                               // from OTP loaded values

//*************************************************************************************************
//
// The following are defines for the bit fields in the Z1_CR register
//
//*************************************************************************************************
#define DCSM_Z1_CR_ALLZERO    0x80000U      // CSMPSWD All Zeros
#define DCSM_Z1_CR_ALLONE     0x100000U     // CSMPSWD All Ones
#define DCSM_Z1_CR_UNSECURE   0x200000U     // CSMPSWD Match CSMKEY
#define DCSM_Z1_CR_ARMED      0x400000U     // CSM Passwords Read Status
#define DCSM_Z1_CR_FORCESEC   0x80000000U   // Force Secure

//*************************************************************************************************
//
// The following are defines for the bit fields in the Z1_GRABSECT1R register
//
//*************************************************************************************************
#define DCSM_Z1_GRABSECT1R_GRAB_SECT0_S    0U
#define DCSM_Z1_GRABSECT1R_GRAB_SECT0_M    0x3U          // Grab Flash Sector 0
#define DCSM_Z1_GRABSECT1R_GRAB_SECT1_S    2U
#define DCSM_Z1_GRABSECT1R_GRAB_SECT1_M    0xCU          // Grab Flash Sector 1
#define DCSM_Z1_GRABSECT1R_GRAB_SECT2_S    4U
#define DCSM_Z1_GRABSECT1R_GRAB_SECT2_M    0x30U         // Grab Flash Sector 2
#define DCSM_Z1_GRABSECT1R_GRAB_SECT3_S    6U
#define DCSM_Z1_GRABSECT1R_GRAB_SECT3_M    0xC0U         // Grab Flash Sector 3
#define DCSM_Z1_GRABSECT1R_GRAB_SECT4_S    8U
#define DCSM_Z1_GRABSECT1R_GRAB_SECT4_M    0x300U        // Grab Flash Sector 4
#define DCSM_Z1_GRABSECT1R_GRAB_SECT5_S    10U
#define DCSM_Z1_GRABSECT1R_GRAB_SECT5_M    0xC00U        // Grab Flash Sector 5
#define DCSM_Z1_GRABSECT1R_GRAB_SECT6_S    12U
#define DCSM_Z1_GRABSECT1R_GRAB_SECT6_M    0x3000U       // Grab Flash Sector 6
#define DCSM_Z1_GRABSECT1R_GRAB_SECT7_S    14U
#define DCSM_Z1_GRABSECT1R_GRAB_SECT7_M    0xC000U       // Grab Flash Sector 7
#define DCSM_Z1_GRABSECT1R_GRAB_SECT8_S    16U
#define DCSM_Z1_GRABSECT1R_GRAB_SECT8_M    0x30000U      // Grab Flash Sector 8
#define DCSM_Z1_GRABSECT1R_GRAB_SECT9_S    18U
#define DCSM_Z1_GRABSECT1R_GRAB_SECT9_M    0xC0000U      // Grab Flash Sector 9
#define DCSM_Z1_GRABSECT1R_GRAB_SECT10_S   20U
#define DCSM_Z1_GRABSECT1R_GRAB_SECT10_M   0x300000U     // Grab Flash Sector 10
#define DCSM_Z1_GRABSECT1R_GRAB_SECT11_S   22U
#define DCSM_Z1_GRABSECT1R_GRAB_SECT11_M   0xC00000U     // Grab Flash Sector 11
#define DCSM_Z1_GRABSECT1R_GRAB_SECT12_S   24U
#define DCSM_Z1_GRABSECT1R_GRAB_SECT12_M   0x3000000U    // Grab Flash Sector 12
#define DCSM_Z1_GRABSECT1R_GRAB_SECT13_S   26U
#define DCSM_Z1_GRABSECT1R_GRAB_SECT13_M   0xC000000U    // Grab Flash Sector 13
#define DCSM_Z1_GRABSECT1R_GRAB_SECT14_S   28U
#define DCSM_Z1_GRABSECT1R_GRAB_SECT14_M   0x30000000U   // Grab Flash Sector 14
#define DCSM_Z1_GRABSECT1R_GRAB_SECT15_S   30U
#define DCSM_Z1_GRABSECT1R_GRAB_SECT15_M   0xC0000000U   // Grab Flash Sector 15

//*************************************************************************************************
//
// The following are defines for the bit fields in the Z1_GRABSECT2R register
//
//*************************************************************************************************
#define DCSM_Z1_GRABSECT2R_GRAB_SECT16_S   0U
#define DCSM_Z1_GRABSECT2R_GRAB_SECT16_M   0x3U          // Grab Flash Sector 16
#define DCSM_Z1_GRABSECT2R_GRAB_SECT17_S   2U
#define DCSM_Z1_GRABSECT2R_GRAB_SECT17_M   0xCU          // Grab Flash Sector 17
#define DCSM_Z1_GRABSECT2R_GRAB_SECT18_S   4U
#define DCSM_Z1_GRABSECT2R_GRAB_SECT18_M   0x30U         // Grab Flash Sector 18
#define DCSM_Z1_GRABSECT2R_GRAB_SECT19_S   6U
#define DCSM_Z1_GRABSECT2R_GRAB_SECT19_M   0xC0U         // Grab Flash Sector 19
#define DCSM_Z1_GRABSECT2R_GRAB_SECT20_S   8U
#define DCSM_Z1_GRABSECT2R_GRAB_SECT20_M   0x300U        // Grab Flash Sector 20
#define DCSM_Z1_GRABSECT2R_GRAB_SECT21_S   10U
#define DCSM_Z1_GRABSECT2R_GRAB_SECT21_M   0xC00U        // Grab Flash Sector 21
#define DCSM_Z1_GRABSECT2R_GRAB_SECT22_S   12U
#define DCSM_Z1_GRABSECT2R_GRAB_SECT22_M   0x3000U       // Grab Flash Sector 22
#define DCSM_Z1_GRABSECT2R_GRAB_SECT23_S   14U
#define DCSM_Z1_GRABSECT2R_GRAB_SECT23_M   0xC000U       // Grab Flash Sector 23
#define DCSM_Z1_GRABSECT2R_GRAB_SECT24_S   16U
#define DCSM_Z1_GRABSECT2R_GRAB_SECT24_M   0x30000U      // Grab Flash Sector 24
#define DCSM_Z1_GRABSECT2R_GRAB_SECT25_S   18U
#define DCSM_Z1_GRABSECT2R_GRAB_SECT25_M   0xC0000U      // Grab Flash Sector 25
#define DCSM_Z1_GRABSECT2R_GRAB_SECT26_S   20U
#define DCSM_Z1_GRABSECT2R_GRAB_SECT26_M   0x300000U     // Grab Flash Sector 26
#define DCSM_Z1_GRABSECT2R_GRAB_SECT27_S   22U
#define DCSM_Z1_GRABSECT2R_GRAB_SECT27_M   0xC00000U     // Grab Flash Sector 27
#define DCSM_Z1_GRABSECT2R_GRAB_SECT28_S   24U
#define DCSM_Z1_GRABSECT2R_GRAB_SECT28_M   0x3000000U    // Grab Flash Sector 28
#define DCSM_Z1_GRABSECT2R_GRAB_SECT29_S   26U
#define DCSM_Z1_GRABSECT2R_GRAB_SECT29_M   0xC000000U    // Grab Flash Sector 29
#define DCSM_Z1_GRABSECT2R_GRAB_SECT30_S   28U
#define DCSM_Z1_GRABSECT2R_GRAB_SECT30_M   0x30000000U   // Grab Flash Sector 30
#define DCSM_Z1_GRABSECT2R_GRAB_SECT31_S   30U
#define DCSM_Z1_GRABSECT2R_GRAB_SECT31_M   0xC0000000U   // Grab Flash Sector 31

//*************************************************************************************************
//
// The following are defines for the bit fields in the Z1_GRABSECT3R register
//
//*************************************************************************************************
#define DCSM_Z1_GRABSECT3R_GRAB_SECT39_32_S     8U
#define DCSM_Z1_GRABSECT3R_GRAB_SECT39_32_M     0x300U        // Grab Flash Sectors 39-32
#define DCSM_Z1_GRABSECT3R_GRAB_SECT47_40_S     10U
#define DCSM_Z1_GRABSECT3R_GRAB_SECT47_40_M     0xC00U        // Grab Flash Sectors 47-40
#define DCSM_Z1_GRABSECT3R_GRAB_SECT55_48_S     12U
#define DCSM_Z1_GRABSECT3R_GRAB_SECT55_48_M     0x3000U       // Grab Flash Sectors 55-48
#define DCSM_Z1_GRABSECT3R_GRAB_SECT63_56_S     14U
#define DCSM_Z1_GRABSECT3R_GRAB_SECT63_56_M     0xC000U       // Grab Flash Sectors 63-56
#define DCSM_Z1_GRABSECT3R_GRAB_SECT71_64_S     16U
#define DCSM_Z1_GRABSECT3R_GRAB_SECT71_64_M     0x30000U      // Grab Flash Sectors 71_64
#define DCSM_Z1_GRABSECT3R_GRAB_SECT79_72_S     18U
#define DCSM_Z1_GRABSECT3R_GRAB_SECT79_72_M     0xC0000U      // Grab Flash Sectors 79-72
#define DCSM_Z1_GRABSECT3R_GRAB_SECT87_80_S     20U
#define DCSM_Z1_GRABSECT3R_GRAB_SECT87_80_M     0x300000U     // Grab Flash Sectors 87-80
#define DCSM_Z1_GRABSECT3R_GRAB_SECT95_88_S     22U
#define DCSM_Z1_GRABSECT3R_GRAB_SECT95_88_M     0xC00000U     // Grab Flash Sectors 95-88
#define DCSM_Z1_GRABSECT3R_GRAB_SECT103_96_S    24U
#define DCSM_Z1_GRABSECT3R_GRAB_SECT103_96_M    0x3000000U    // Grab Flash Sectors 103-96
#define DCSM_Z1_GRABSECT3R_GRAB_SECT111_104_S   26U
#define DCSM_Z1_GRABSECT3R_GRAB_SECT111_104_M   0xC000000U    // Grab Flash Sectors 111_104
#define DCSM_Z1_GRABSECT3R_GRAB_SECT119_112_S   28U
#define DCSM_Z1_GRABSECT3R_GRAB_SECT119_112_M   0x30000000U   // Grab Flash Sectors 119-112
#define DCSM_Z1_GRABSECT3R_GRAB_SECT127_120_S   30U
#define DCSM_Z1_GRABSECT3R_GRAB_SECT127_120_M   0xC0000000U   // Grab Flash Sectors 127-120

//*************************************************************************************************
//
// The following are defines for the bit fields in the Z1_GRABRAM1R register
//
//*************************************************************************************************
#define DCSM_Z1_GRABRAM1R_GRAB_RAM0_S   0U
#define DCSM_Z1_GRABRAM1R_GRAB_RAM0_M   0x3U      // Grab RAM LS0 Section A
#define DCSM_Z1_GRABRAM1R_GRAB_RAM1_S   2U
#define DCSM_Z1_GRABRAM1R_GRAB_RAM1_M   0xCU      // Grab RAM LS0 Section B
#define DCSM_Z1_GRABRAM1R_GRAB_RAM2_S   4U
#define DCSM_Z1_GRABRAM1R_GRAB_RAM2_M   0x30U     // Grab RAM LS0 Section C
#define DCSM_Z1_GRABRAM1R_GRAB_RAM3_S   6U
#define DCSM_Z1_GRABRAM1R_GRAB_RAM3_M   0xC0U     // Grab RAM LS0 Section D
#define DCSM_Z1_GRABRAM1R_GRAB_RAM4_S   8U
#define DCSM_Z1_GRABRAM1R_GRAB_RAM4_M   0x300U    // Grab RAM LS1 Section A
#define DCSM_Z1_GRABRAM1R_GRAB_RAM5_S   10U
#define DCSM_Z1_GRABRAM1R_GRAB_RAM5_M   0xC00U    // Grab RAM LS1 Section B
#define DCSM_Z1_GRABRAM1R_GRAB_RAM6_S   12U
#define DCSM_Z1_GRABRAM1R_GRAB_RAM6_M   0x3000U   // Grab RAM LS1 Section C
#define DCSM_Z1_GRABRAM1R_GRAB_RAM7_S   14U
#define DCSM_Z1_GRABRAM1R_GRAB_RAM7_M   0xC000U   // Grab RAM LS1 Section D

//*************************************************************************************************
//
// The following are defines for the bit fields in the Z1_EXEONLYSECT1R register
//
//*************************************************************************************************
#define DCSM_Z1_EXEONLYSECT1R_EXEONLY_SECT0    0x1U          // Execute-Only Flash Sector 0
#define DCSM_Z1_EXEONLYSECT1R_EXEONLY_SECT1    0x2U          // Execute-Only Flash Sector 1
#define DCSM_Z1_EXEONLYSECT1R_EXEONLY_SECT2    0x4U          // Execute-Only Flash Sector 2
#define DCSM_Z1_EXEONLYSECT1R_EXEONLY_SECT3    0x8U          // Execute-Only Flash Sector 3
#define DCSM_Z1_EXEONLYSECT1R_EXEONLY_SECT4    0x10U         // Execute-Only Flash Sector 4
#define DCSM_Z1_EXEONLYSECT1R_EXEONLY_SECT5    0x20U         // Execute-Only Flash Sector 5
#define DCSM_Z1_EXEONLYSECT1R_EXEONLY_SECT6    0x40U         // Execute-Only Flash Sector 6
#define DCSM_Z1_EXEONLYSECT1R_EXEONLY_SECT7    0x80U         // Execute-Only Flash Sector 7
#define DCSM_Z1_EXEONLYSECT1R_EXEONLY_SECT8    0x100U        // Execute-Only Flash Sector 8
#define DCSM_Z1_EXEONLYSECT1R_EXEONLY_SECT9    0x200U        // Execute-Only Flash Sector 9
#define DCSM_Z1_EXEONLYSECT1R_EXEONLY_SECT10   0x400U        // Execute-Only Flash Sector 10
#define DCSM_Z1_EXEONLYSECT1R_EXEONLY_SECT11   0x800U        // Execute-Only Flash Sector 11
#define DCSM_Z1_EXEONLYSECT1R_EXEONLY_SECT12   0x1000U       // Execute-Only Flash Sector 12
#define DCSM_Z1_EXEONLYSECT1R_EXEONLY_SECT13   0x2000U       // Execute-Only Flash Sector 13
#define DCSM_Z1_EXEONLYSECT1R_EXEONLY_SECT14   0x4000U       // Execute-Only Flash Sector 14
#define DCSM_Z1_EXEONLYSECT1R_EXEONLY_SECT15   0x8000U       // Execute-Only Flash Sector 15
#define DCSM_Z1_EXEONLYSECT1R_EXEONLY_SECT16   0x10000U      // Execute-Only Flash Sector 16
#define DCSM_Z1_EXEONLYSECT1R_EXEONLY_SECT17   0x20000U      // Execute-Only Flash Sector 17
#define DCSM_Z1_EXEONLYSECT1R_EXEONLY_SECT18   0x40000U      // Execute-Only Flash Sector 18
#define DCSM_Z1_EXEONLYSECT1R_EXEONLY_SECT19   0x80000U      // Execute-Only Flash Sector 19
#define DCSM_Z1_EXEONLYSECT1R_EXEONLY_SECT20   0x100000U     // Execute-Only Flash Sector 20
#define DCSM_Z1_EXEONLYSECT1R_EXEONLY_SECT21   0x200000U     // Execute-Only Flash Sector 21
#define DCSM_Z1_EXEONLYSECT1R_EXEONLY_SECT22   0x400000U     // Execute-Only Flash Sector 22
#define DCSM_Z1_EXEONLYSECT1R_EXEONLY_SECT23   0x800000U     // Execute-Only Flash Sector 23
#define DCSM_Z1_EXEONLYSECT1R_EXEONLY_SECT24   0x1000000U    // Execute-Only Flash Sector 24
#define DCSM_Z1_EXEONLYSECT1R_EXEONLY_SECT25   0x2000000U    // Execute-Only Flash Sector 25
#define DCSM_Z1_EXEONLYSECT1R_EXEONLY_SECT26   0x4000000U    // Execute-Only Flash Sector 26
#define DCSM_Z1_EXEONLYSECT1R_EXEONLY_SECT27   0x8000000U    // Execute-Only Flash Sector 27
#define DCSM_Z1_EXEONLYSECT1R_EXEONLY_SECT28   0x10000000U   // Execute-Only Flash Sector 28
#define DCSM_Z1_EXEONLYSECT1R_EXEONLY_SECT29   0x20000000U   // Execute-Only Flash Sector 29
#define DCSM_Z1_EXEONLYSECT1R_EXEONLY_SECT30   0x40000000U   // Execute-Only Flash Sector 30
#define DCSM_Z1_EXEONLYSECT1R_EXEONLY_SECT31   0x80000000U   // Execute-Only Flash Sector 31

//*************************************************************************************************
//
// The following are defines for the bit fields in the Z1_EXEONLYSECT2R register
//
//*************************************************************************************************
#define DCSM_Z1_EXEONLYSECT2R_EXEONLY_SECT39_32     0x10U     // Execute-Only Flash Sectors 39_32
#define DCSM_Z1_EXEONLYSECT2R_EXEONLY_SECT47_40     0x20U     // Execute-Only Flash Sectors 47-40
#define DCSM_Z1_EXEONLYSECT2R_EXEONLY_SECT55_48     0x40U     // Execute-Only Flash Sectors 55-48
#define DCSM_Z1_EXEONLYSECT2R_EXEONLY_SECT63_56     0x80U     // Execute-Only Flash Sectors 63-56
#define DCSM_Z1_EXEONLYSECT2R_EXEONLY_SECT71_64     0x100U    // Execute-Only Flash Sectors 71-64
#define DCSM_Z1_EXEONLYSECT2R_EXEONLY_SECT79_72     0x200U    // Execute-Only Flash Sectors 79-72
#define DCSM_Z1_EXEONLYSECT2R_EXEONLY_SECT87_80     0x400U    // Execute-Only Flash Sectors 87-80
#define DCSM_Z1_EXEONLYSECT2R_EXEONLY_SECT95_88     0x800U    // Execute-Only Flash Sectors 95-88
#define DCSM_Z1_EXEONLYSECT2R_EXEONLY_SECT103_96    0x1000U   // Execute-Only Flash Sectors 103-96
#define DCSM_Z1_EXEONLYSECT2R_EXEONLY_SECT111_104   0x2000U   // Execute-Only Flash Sectors 111-104
#define DCSM_Z1_EXEONLYSECT2R_EXEONLY_SECT119_112   0x4000U   // Execute-Only Flash Sectors 119-112
#define DCSM_Z1_EXEONLYSECT2R_EXEONLY_SECT127_120   0x8000U   // Execute-Only Flash Sectors 127-120

//*************************************************************************************************
//
// The following are defines for the bit fields in the Z1_EXEONLYRAM1R register
//
//*************************************************************************************************
#define DCSM_Z1_EXEONLYRAM1R_EXEONLY_RAM0   0x1U    // Execute-Only RAM LS0 Section A
#define DCSM_Z1_EXEONLYRAM1R_EXEONLY_RAM1   0x2U    // Execute-Only RAM LS0 Section B
#define DCSM_Z1_EXEONLYRAM1R_EXEONLY_RAM2   0x4U    // Execute-Only RAM LS0 Section C
#define DCSM_Z1_EXEONLYRAM1R_EXEONLY_RAM3   0x8U    // Execute-Only RAM LS0 Section D
#define DCSM_Z1_EXEONLYRAM1R_EXEONLY_RAM4   0x10U   // Execute-Only RAM LS1 Section A
#define DCSM_Z1_EXEONLYRAM1R_EXEONLY_RAM5   0x20U   // Execute-Only RAM LS1 Section B
#define DCSM_Z1_EXEONLYRAM1R_EXEONLY_RAM6   0x40U   // Execute-Only RAM LS1 Section C
#define DCSM_Z1_EXEONLYRAM1R_EXEONLY_RAM7   0x80U   // Execute-Only RAM LS1 Section D


//*************************************************************************************************
//
// The following are defines for the bit fields in the Z2_LINKPOINTER register
//
//*************************************************************************************************
#define DCSM_Z2_LINKPOINTER_LINKPOINTER_S   0U
#define DCSM_Z2_LINKPOINTER_LINKPOINTER_M   0x3FFFU   // Zone2 LINK Pointer

//*************************************************************************************************
//
// The following are defines for the bit fields in the Z2_OTPSECLOCK register
//
//*************************************************************************************************
#define DCSM_Z2_OTPSECLOCK_JTAGLOCK     0x1U    // JTAG Lock Status
#define DCSM_Z2_OTPSECLOCK_PSWDLOCK_S   4U
#define DCSM_Z2_OTPSECLOCK_PSWDLOCK_M   0xF0U   // Zone2 Password Lock.

//*************************************************************************************************
//
// The following are defines for the bit fields in the Z2_LINKPOINTERERR register
//
//*************************************************************************************************
#define DCSM_Z2_LINKPOINTERERR_Z2_LINKPOINTERERR_S   0U
#define DCSM_Z2_LINKPOINTERERR_Z2_LINKPOINTERERR_M   0x3FFFU   // Error to Resolve Z2 Link pointer
                                                               // from OTP loaded values

//*************************************************************************************************
//
// The following are defines for the bit fields in the Z2_CR register
//
//*************************************************************************************************
#define DCSM_Z2_CR_ALLZERO    0x80000U      // CSMPSWD All Zeros
#define DCSM_Z2_CR_ALLONE     0x100000U     // CSMPSWD All Ones
#define DCSM_Z2_CR_UNSECURE   0x200000U     // CSMPSWD Match CSMKEY
#define DCSM_Z2_CR_ARMED      0x400000U     // CSM Passwords Read Status
#define DCSM_Z2_CR_FORCESEC   0x80000000U   // Force Secure

//*************************************************************************************************
//
// The following are defines for the bit fields in the Z2_GRABSECT1R register
//
//*************************************************************************************************
#define DCSM_Z2_GRABSECT1R_GRAB_SECT0_S    0U
#define DCSM_Z2_GRABSECT1R_GRAB_SECT0_M    0x3U          // Grab Flash Sector 0
#define DCSM_Z2_GRABSECT1R_GRAB_SECT1_S    2U
#define DCSM_Z2_GRABSECT1R_GRAB_SECT1_M    0xCU          // Grab Flash Sector 1
#define DCSM_Z2_GRABSECT1R_GRAB_SECT2_S    4U
#define DCSM_Z2_GRABSECT1R_GRAB_SECT2_M    0x30U         // Grab Flash Sector 2
#define DCSM_Z2_GRABSECT1R_GRAB_SECT3_S    6U
#define DCSM_Z2_GRABSECT1R_GRAB_SECT3_M    0xC0U         // Grab Flash Sector 3
#define DCSM_Z2_GRABSECT1R_GRAB_SECT4_S    8U
#define DCSM_Z2_GRABSECT1R_GRAB_SECT4_M    0x300U        // Grab Flash Sector 4
#define DCSM_Z2_GRABSECT1R_GRAB_SECT5_S    10U
#define DCSM_Z2_GRABSECT1R_GRAB_SECT5_M    0xC00U        // Grab Flash Sector 5
#define DCSM_Z2_GRABSECT1R_GRAB_SECT6_S    12U
#define DCSM_Z2_GRABSECT1R_GRAB_SECT6_M    0x3000U       // Grab Flash Sector 6
#define DCSM_Z2_GRABSECT1R_GRAB_SECT7_S    14U
#define DCSM_Z2_GRABSECT1R_GRAB_SECT7_M    0xC000U       // Grab Flash Sector 7
#define DCSM_Z2_GRABSECT1R_GRAB_SECT8_S    16U
#define DCSM_Z2_GRABSECT1R_GRAB_SECT8_M    0x30000U      // Grab Flash Sector 8
#define DCSM_Z2_GRABSECT1R_GRAB_SECT9_S    18U
#define DCSM_Z2_GRABSECT1R_GRAB_SECT9_M    0xC0000U      // Grab Flash Sector 9
#define DCSM_Z2_GRABSECT1R_GRAB_SECT10_S   20U
#define DCSM_Z2_GRABSECT1R_GRAB_SECT10_M   0x300000U     // Grab Flash Sector 10
#define DCSM_Z2_GRABSECT1R_GRAB_SECT11_S   22U
#define DCSM_Z2_GRABSECT1R_GRAB_SECT11_M   0xC00000U     // Grab Flash Sector 11
#define DCSM_Z2_GRABSECT1R_GRAB_SECT12_S   24U
#define DCSM_Z2_GRABSECT1R_GRAB_SECT12_M   0x3000000U    // Grab Flash Sector 12
#define DCSM_Z2_GRABSECT1R_GRAB_SECT13_S   26U
#define DCSM_Z2_GRABSECT1R_GRAB_SECT13_M   0xC000000U    // Grab Flash Sector 13
#define DCSM_Z2_GRABSECT1R_GRAB_SECT14_S   28U
#define DCSM_Z2_GRABSECT1R_GRAB_SECT14_M   0x30000000U   // Grab Flash Sector 14
#define DCSM_Z2_GRABSECT1R_GRAB_SECT15_S   30U
#define DCSM_Z2_GRABSECT1R_GRAB_SECT15_M   0xC0000000U   // Grab Flash Sector 15

//*************************************************************************************************
//
// The following are defines for the bit fields in the Z2_GRABSECT2R register
//
//*************************************************************************************************
#define DCSM_Z2_GRABSECT2R_GRAB_SECT16_S   0U
#define DCSM_Z2_GRABSECT2R_GRAB_SECT16_M   0x3U          // Grab Flash Sector 16
#define DCSM_Z2_GRABSECT2R_GRAB_SECT17_S   2U
#define DCSM_Z2_GRABSECT2R_GRAB_SECT17_M   0xCU          // Grab Flash Sector 17
#define DCSM_Z2_GRABSECT2R_GRAB_SECT18_S   4U
#define DCSM_Z2_GRABSECT2R_GRAB_SECT18_M   0x30U         // Grab Flash Sector 18
#define DCSM_Z2_GRABSECT2R_GRAB_SECT19_S   6U
#define DCSM_Z2_GRABSECT2R_GRAB_SECT19_M   0xC0U         // Grab Flash Sector 19
#define DCSM_Z2_GRABSECT2R_GRAB_SECT20_S   8U
#define DCSM_Z2_GRABSECT2R_GRAB_SECT20_M   0x300U        // Grab Flash Sector 20
#define DCSM_Z2_GRABSECT2R_GRAB_SECT21_S   10U
#define DCSM_Z2_GRABSECT2R_GRAB_SECT21_M   0xC00U        // Grab Flash Sector 21
#define DCSM_Z2_GRABSECT2R_GRAB_SECT22_S   12U
#define DCSM_Z2_GRABSECT2R_GRAB_SECT22_M   0x3000U       // Grab Flash Sector 22
#define DCSM_Z2_GRABSECT2R_GRAB_SECT23_S   14U
#define DCSM_Z2_GRABSECT2R_GRAB_SECT23_M   0xC000U       // Grab Flash Sector 23
#define DCSM_Z2_GRABSECT2R_GRAB_SECT24_S   16U
#define DCSM_Z2_GRABSECT2R_GRAB_SECT24_M   0x30000U      // Grab Flash Sector 24
#define DCSM_Z2_GRABSECT2R_GRAB_SECT25_S   18U
#define DCSM_Z2_GRABSECT2R_GRAB_SECT25_M   0xC0000U      // Grab Flash Sector 25
#define DCSM_Z2_GRABSECT2R_GRAB_SECT26_S   20U
#define DCSM_Z2_GRABSECT2R_GRAB_SECT26_M   0x300000U     // Grab Flash Sector 26
#define DCSM_Z2_GRABSECT2R_GRAB_SECT27_S   22U
#define DCSM_Z2_GRABSECT2R_GRAB_SECT27_M   0xC00000U     // Grab Flash Sector 27
#define DCSM_Z2_GRABSECT2R_GRAB_SECT28_S   24U
#define DCSM_Z2_GRABSECT2R_GRAB_SECT28_M   0x3000000U    // Grab Flash Sector 28
#define DCSM_Z2_GRABSECT2R_GRAB_SECT29_S   26U
#define DCSM_Z2_GRABSECT2R_GRAB_SECT29_M   0xC000000U    // Grab Flash Sector 29
#define DCSM_Z2_GRABSECT2R_GRAB_SECT30_S   28U
#define DCSM_Z2_GRABSECT2R_GRAB_SECT30_M   0x30000000U   // Grab Flash Sector 30
#define DCSM_Z2_GRABSECT2R_GRAB_SECT31_S   30U
#define DCSM_Z2_GRABSECT2R_GRAB_SECT31_M   0xC0000000U   // Grab Flash Sector 31

//*************************************************************************************************
//
// The following are defines for the bit fields in the Z2_GRABSECT3R register
//
//*************************************************************************************************
#define DCSM_Z2_GRABSECT3R_GRAB_SECT39_32_S     8U
#define DCSM_Z2_GRABSECT3R_GRAB_SECT39_32_M     0x300U        // Grab Flash Sectors 39-32
#define DCSM_Z2_GRABSECT3R_GRAB_SECT47_40_S     10U
#define DCSM_Z2_GRABSECT3R_GRAB_SECT47_40_M     0xC00U        // Grab Flash Sectors 47-40
#define DCSM_Z2_GRABSECT3R_GRAB_SECT55_48_S     12U
#define DCSM_Z2_GRABSECT3R_GRAB_SECT55_48_M     0x3000U       // Grab Flash Sectors 55-48
#define DCSM_Z2_GRABSECT3R_GRAB_SECT63_56_S     14U
#define DCSM_Z2_GRABSECT3R_GRAB_SECT63_56_M     0xC000U       // Grab Flash Sectors 63-56
#define DCSM_Z2_GRABSECT3R_GRAB_SECT71_64_S     16U
#define DCSM_Z2_GRABSECT3R_GRAB_SECT71_64_M     0x30000U      // Grab Flash Sectors 71_64
#define DCSM_Z2_GRABSECT3R_GRAB_SECT79_72_S     18U
#define DCSM_Z2_GRABSECT3R_GRAB_SECT79_72_M     0xC0000U      // Grab Flash Sectors 79-72
#define DCSM_Z2_GRABSECT3R_GRAB_SECT87_80_S     20U
#define DCSM_Z2_GRABSECT3R_GRAB_SECT87_80_M     0x300000U     // Grab Flash Sectors 87-80
#define DCSM_Z2_GRABSECT3R_GRAB_SECT95_88_S     22U
#define DCSM_Z2_GRABSECT3R_GRAB_SECT95_88_M     0xC00000U     // Grab Flash Sectors 95-88
#define DCSM_Z2_GRABSECT3R_GRAB_SECT103_96_S    24U
#define DCSM_Z2_GRABSECT3R_GRAB_SECT103_96_M    0x3000000U    // Grab Flash Sectors 103-96
#define DCSM_Z2_GRABSECT3R_GRAB_SECT111_104_S   26U
#define DCSM_Z2_GRABSECT3R_GRAB_SECT111_104_M   0xC000000U    // Grab Flash Sectors 111_104
#define DCSM_Z2_GRABSECT3R_GRAB_SECT119_112_S   28U
#define DCSM_Z2_GRABSECT3R_GRAB_SECT119_112_M   0x30000000U   // Grab Flash Sectors 119-112
#define DCSM_Z2_GRABSECT3R_GRAB_SECT127_120_S   30U
#define DCSM_Z2_GRABSECT3R_GRAB_SECT127_120_M   0xC0000000U   // Grab Flash Sectors 127-120

//*************************************************************************************************
//
// The following are defines for the bit fields in the Z2_GRABRAM1R register
//
//*************************************************************************************************
#define DCSM_Z2_GRABRAM1R_GRAB_RAM0_S   0U
#define DCSM_Z2_GRABRAM1R_GRAB_RAM0_M   0x3U      // Grab RAM LS0 Section A
#define DCSM_Z2_GRABRAM1R_GRAB_RAM1_S   2U
#define DCSM_Z2_GRABRAM1R_GRAB_RAM1_M   0xCU      // Grab RAM LS0 Section B
#define DCSM_Z2_GRABRAM1R_GRAB_RAM2_S   4U
#define DCSM_Z2_GRABRAM1R_GRAB_RAM2_M   0x30U     // Grab RAM LS0 Section C
#define DCSM_Z2_GRABRAM1R_GRAB_RAM3_S   6U
#define DCSM_Z2_GRABRAM1R_GRAB_RAM3_M   0xC0U     // Grab RAM LS0 Section D
#define DCSM_Z2_GRABRAM1R_GRAB_RAM4_S   8U
#define DCSM_Z2_GRABRAM1R_GRAB_RAM4_M   0x300U    // Grab RAM LS1 Section A
#define DCSM_Z2_GRABRAM1R_GRAB_RAM5_S   10U
#define DCSM_Z2_GRABRAM1R_GRAB_RAM5_M   0xC00U    // Grab RAM LS1 Section B
#define DCSM_Z2_GRABRAM1R_GRAB_RAM6_S   12U
#define DCSM_Z2_GRABRAM1R_GRAB_RAM6_M   0x3000U   // Grab RAM LS1 Section C
#define DCSM_Z2_GRABRAM1R_GRAB_RAM7_S   14U
#define DCSM_Z2_GRABRAM1R_GRAB_RAM7_M   0xC000U   // Grab RAM LS1 Section D

//*************************************************************************************************
//
// The following are defines for the bit fields in the Z2_EXEONLYSECT1R register
//
//*************************************************************************************************
#define DCSM_Z2_EXEONLYSECT1R_EXEONLY_SECT0    0x1U          // Execute-Only Flash Sector 0
#define DCSM_Z2_EXEONLYSECT1R_EXEONLY_SECT1    0x2U          // Execute-Only Flash Sector 1
#define DCSM_Z2_EXEONLYSECT1R_EXEONLY_SECT2    0x4U          // Execute-Only Flash Sector 2
#define DCSM_Z2_EXEONLYSECT1R_EXEONLY_SECT3    0x8U          // Execute-Only Flash Sector 3
#define DCSM_Z2_EXEONLYSECT1R_EXEONLY_SECT4    0x10U         // Execute-Only Flash Sector 4
#define DCSM_Z2_EXEONLYSECT1R_EXEONLY_SECT5    0x20U         // Execute-Only Flash Sector 5
#define DCSM_Z2_EXEONLYSECT1R_EXEONLY_SECT6    0x40U         // Execute-Only Flash Sector 6
#define DCSM_Z2_EXEONLYSECT1R_EXEONLY_SECT7    0x80U         // Execute-Only Flash Sector 7
#define DCSM_Z2_EXEONLYSECT1R_EXEONLY_SECT8    0x100U        // Execute-Only Flash Sector 8
#define DCSM_Z2_EXEONLYSECT1R_EXEONLY_SECT9    0x200U        // Execute-Only Flash Sector 9
#define DCSM_Z2_EXEONLYSECT1R_EXEONLY_SECT10   0x400U        // Execute-Only Flash Sector 10
#define DCSM_Z2_EXEONLYSECT1R_EXEONLY_SECT11   0x800U        // Execute-Only Flash Sector 11
#define DCSM_Z2_EXEONLYSECT1R_EXEONLY_SECT12   0x1000U       // Execute-Only Flash Sector 12
#define DCSM_Z2_EXEONLYSECT1R_EXEONLY_SECT13   0x2000U       // Execute-Only Flash Sector 13
#define DCSM_Z2_EXEONLYSECT1R_EXEONLY_SECT14   0x4000U       // Execute-Only Flash Sector 14
#define DCSM_Z2_EXEONLYSECT1R_EXEONLY_SECT15   0x8000U       // Execute-Only Flash Sector 15
#define DCSM_Z2_EXEONLYSECT1R_EXEONLY_SECT16   0x10000U      // Execute-Only Flash Sector 16
#define DCSM_Z2_EXEONLYSECT1R_EXEONLY_SECT17   0x20000U      // Execute-Only Flash Sector 17
#define DCSM_Z2_EXEONLYSECT1R_EXEONLY_SECT18   0x40000U      // Execute-Only Flash Sector 18
#define DCSM_Z2_EXEONLYSECT1R_EXEONLY_SECT19   0x80000U      // Execute-Only Flash Sector 19
#define DCSM_Z2_EXEONLYSECT1R_EXEONLY_SECT20   0x100000U     // Execute-Only Flash Sector 20
#define DCSM_Z2_EXEONLYSECT1R_EXEONLY_SECT21   0x200000U     // Execute-Only Flash Sector 21
#define DCSM_Z2_EXEONLYSECT1R_EXEONLY_SECT22   0x400000U     // Execute-Only Flash Sector 22
#define DCSM_Z2_EXEONLYSECT1R_EXEONLY_SECT23   0x800000U     // Execute-Only Flash Sector 23
#define DCSM_Z2_EXEONLYSECT1R_EXEONLY_SECT24   0x1000000U    // Execute-Only Flash Sector 24
#define DCSM_Z2_EXEONLYSECT1R_EXEONLY_SECT25   0x2000000U    // Execute-Only Flash Sector 25
#define DCSM_Z2_EXEONLYSECT1R_EXEONLY_SECT26   0x4000000U    // Execute-Only Flash Sector 26
#define DCSM_Z2_EXEONLYSECT1R_EXEONLY_SECT27   0x8000000U    // Execute-Only Flash Sector 27
#define DCSM_Z2_EXEONLYSECT1R_EXEONLY_SECT28   0x10000000U   // Execute-Only Flash Sector 28
#define DCSM_Z2_EXEONLYSECT1R_EXEONLY_SECT29   0x20000000U   // Execute-Only Flash Sector 29
#define DCSM_Z2_EXEONLYSECT1R_EXEONLY_SECT30   0x40000000U   // Execute-Only Flash Sector 30
#define DCSM_Z2_EXEONLYSECT1R_EXEONLY_SECT31   0x80000000U   // Execute-Only Flash Sector 31

//*************************************************************************************************
//
// The following are defines for the bit fields in the Z2_EXEONLYSECT2R register
//
//*************************************************************************************************
#define DCSM_Z2_EXEONLYSECT2R_EXEONLY_SECT39_32     0x10U     // Execute-Only Flash Sectors 39-32
#define DCSM_Z2_EXEONLYSECT2R_EXEONLY_SECT47_40     0x20U     // Execute-Only Flash Sectors 47-40
#define DCSM_Z2_EXEONLYSECT2R_EXEONLY_SECT55_48     0x40U     // Execute-Only Flash Sectors 55-48
#define DCSM_Z2_EXEONLYSECT2R_EXEONLY_SECT63_56     0x80U     // Execute-Only Flash Sectors 63-56
#define DCSM_Z2_EXEONLYSECT2R_EXEONLY_SECT71_64     0x100U    // Execute-Only Flash Sectors 71-64
#define DCSM_Z2_EXEONLYSECT2R_EXEONLY_SECT79_72     0x200U    // Execute-Only Flash Sectors 79-72
#define DCSM_Z2_EXEONLYSECT2R_EXEONLY_SECT87_80     0x400U    // Execute-Only Flash Sectors 87-80
#define DCSM_Z2_EXEONLYSECT2R_EXEONLY_SECT95_88     0x800U    // Execute-Only Flash Sectors 95-88
#define DCSM_Z2_EXEONLYSECT2R_EXEONLY_SECT103_96    0x1000U   // Execute-Only Flash Sectors 103-96
#define DCSM_Z2_EXEONLYSECT2R_EXEONLY_SECT111_104   0x2000U   // Execute-Only Flash Sectors 111-104
#define DCSM_Z2_EXEONLYSECT2R_EXEONLY_SECT119_112   0x4000U   // Execute-Only Flash Sectors 119-112
#define DCSM_Z2_EXEONLYSECT2R_EXEONLY_SECT127_120   0x8000U   // Execute-Only Flash Sectors 127-120

//*************************************************************************************************
//
// The following are defines for the bit fields in the Z2_EXEONLYRAM1R register
//
//*************************************************************************************************
#define DCSM_Z2_EXEONLYRAM1R_EXEONLY_RAM0   0x1U    // Execute-Only RAM LS0 Section A
#define DCSM_Z2_EXEONLYRAM1R_EXEONLY_RAM1   0x2U    // Execute-Only RAM LS0 Section B
#define DCSM_Z2_EXEONLYRAM1R_EXEONLY_RAM2   0x4U    // Execute-Only RAM LS0 Section C
#define DCSM_Z2_EXEONLYRAM1R_EXEONLY_RAM3   0x8U    // Execute-Only RAM LS0 Section D
#define DCSM_Z2_EXEONLYRAM1R_EXEONLY_RAM4   0x10U   // Execute-Only RAM LS1 Section A
#define DCSM_Z2_EXEONLYRAM1R_EXEONLY_RAM5   0x20U   // Execute-Only RAM LS1 Section B
#define DCSM_Z2_EXEONLYRAM1R_EXEONLY_RAM6   0x40U   // Execute-Only RAM LS1 Section C
#define DCSM_Z2_EXEONLYRAM1R_EXEONLY_RAM7   0x80U   // Execute-Only RAM LS1 Section D


//*************************************************************************************************
//
// The following are defines for the bit fields in the FLSEM register
//
//*************************************************************************************************
#define DCSM_FLSEM_SEM_S   0U
#define DCSM_FLSEM_SEM_M   0x3U      // Flash Semaphore Bit
#define DCSM_FLSEM_KEY_S   8U
#define DCSM_FLSEM_KEY_M   0xFF00U   // Semaphore Key

//*************************************************************************************************
//
// The following are defines for the bit fields in the SECTSTAT1 register
//
//*************************************************************************************************
#define DCSM_SECTSTAT1_STATUS_SECT0_S    0U
#define DCSM_SECTSTAT1_STATUS_SECT0_M    0x3U          // Zone Status Flash Bank 0 Sector 0
#define DCSM_SECTSTAT1_STATUS_SECT1_S    2U
#define DCSM_SECTSTAT1_STATUS_SECT1_M    0xCU          // Zone Status Flash Bank 0 Sector 1
#define DCSM_SECTSTAT1_STATUS_SECT2_S    4U
#define DCSM_SECTSTAT1_STATUS_SECT2_M    0x30U         // Zone Status Flash Bank 0 Sector 2
#define DCSM_SECTSTAT1_STATUS_SECT3_S    6U
#define DCSM_SECTSTAT1_STATUS_SECT3_M    0xC0U         // Zone Status Flash Bank 0 Sector 3
#define DCSM_SECTSTAT1_STATUS_SECT4_S    8U
#define DCSM_SECTSTAT1_STATUS_SECT4_M    0x300U        // Zone Status Flash Bank 0 Sector 4
#define DCSM_SECTSTAT1_STATUS_SECT5_S    10U
#define DCSM_SECTSTAT1_STATUS_SECT5_M    0xC00U        // Zone Status Flash Bank 0 Sector 5
#define DCSM_SECTSTAT1_STATUS_SECT6_S    12U
#define DCSM_SECTSTAT1_STATUS_SECT6_M    0x3000U       // Zone Status Flash Bank 0 Sector 6
#define DCSM_SECTSTAT1_STATUS_SECT7_S    14U
#define DCSM_SECTSTAT1_STATUS_SECT7_M    0xC000U       // Zone Status Flash Bank 0 Sector 7
#define DCSM_SECTSTAT1_STATUS_SECT8_S    16U
#define DCSM_SECTSTAT1_STATUS_SECT8_M    0x30000U      // Zone Status Flash Bank 0 Sector 8
#define DCSM_SECTSTAT1_STATUS_SECT9_S    18U
#define DCSM_SECTSTAT1_STATUS_SECT9_M    0xC0000U      // Zone Status Flash Bank 0 Sector 9
#define DCSM_SECTSTAT1_STATUS_SECT10_S   20U
#define DCSM_SECTSTAT1_STATUS_SECT10_M   0x300000U     // Zone Status Flash Bank 0 Sector 10
#define DCSM_SECTSTAT1_STATUS_SECT11_S   22U
#define DCSM_SECTSTAT1_STATUS_SECT11_M   0xC00000U     // Zone Status Flash Bank 0 Sector 11
#define DCSM_SECTSTAT1_STATUS_SECT12_S   24U
#define DCSM_SECTSTAT1_STATUS_SECT12_M   0x3000000U    // Zone Status Flash Bank 0 Sector 12
#define DCSM_SECTSTAT1_STATUS_SECT13_S   26U
#define DCSM_SECTSTAT1_STATUS_SECT13_M   0xC000000U    // Zone Status Flash Bank 0 Sector 13
#define DCSM_SECTSTAT1_STATUS_SECT14_S   28U
#define DCSM_SECTSTAT1_STATUS_SECT14_M   0x30000000U   // Zone Status Flash Bank 0 Sector 14
#define DCSM_SECTSTAT1_STATUS_SECT15_S   30U
#define DCSM_SECTSTAT1_STATUS_SECT15_M   0xC0000000U   // Zone Status Flash Bank 0 Sector 15

//*************************************************************************************************
//
// The following are defines for the bit fields in the SECTSTAT2 register
//
//*************************************************************************************************
#define DCSM_SECTSTAT2_STATUS_SECT16_S   0U
#define DCSM_SECTSTAT2_STATUS_SECT16_M   0x3U          // Zone Status Flash Bank 0 Sector 16
#define DCSM_SECTSTAT2_STATUS_SECT17_S   2U
#define DCSM_SECTSTAT2_STATUS_SECT17_M   0xCU          // Zone Status Flash Bank 0 Sector 17
#define DCSM_SECTSTAT2_STATUS_SECT18_S   4U
#define DCSM_SECTSTAT2_STATUS_SECT18_M   0x30U         // Zone Status Flash Bank 0 Sector 18
#define DCSM_SECTSTAT2_STATUS_SECT19_S   6U
#define DCSM_SECTSTAT2_STATUS_SECT19_M   0xC0U         // Zone Status Flash Bank 0 Sector 19
#define DCSM_SECTSTAT2_STATUS_SECT20_S   8U
#define DCSM_SECTSTAT2_STATUS_SECT20_M   0x300U        // Zone Status Flash Bank 0 Sector 20
#define DCSM_SECTSTAT2_STATUS_SECT21_S   10U
#define DCSM_SECTSTAT2_STATUS_SECT21_M   0xC00U        // Zone Status Flash Bank 0 Sector 21
#define DCSM_SECTSTAT2_STATUS_SECT22_S   12U
#define DCSM_SECTSTAT2_STATUS_SECT22_M   0x3000U       // Zone Status Flash Bank 0 Sector 22
#define DCSM_SECTSTAT2_STATUS_SECT23_S   14U
#define DCSM_SECTSTAT2_STATUS_SECT23_M   0xC000U       // Zone Status Flash Bank 0 Sector 23
#define DCSM_SECTSTAT2_STATUS_SECT24_S   16U
#define DCSM_SECTSTAT2_STATUS_SECT24_M   0x30000U      // Zone Status Flash Bank 0 Sector 24
#define DCSM_SECTSTAT2_STATUS_SECT25_S   18U
#define DCSM_SECTSTAT2_STATUS_SECT25_M   0xC0000U      // Zone Status Flash Bank 0 Sector 25
#define DCSM_SECTSTAT2_STATUS_SECT26_S   20U
#define DCSM_SECTSTAT2_STATUS_SECT26_M   0x300000U     // Zone Status Flash Bank 0 Sector 26
#define DCSM_SECTSTAT2_STATUS_SECT27_S   22U
#define DCSM_SECTSTAT2_STATUS_SECT27_M   0xC00000U     // Zone Status Flash Bank 0 Sector 27
#define DCSM_SECTSTAT2_STATUS_SECT28_S   24U
#define DCSM_SECTSTAT2_STATUS_SECT28_M   0x3000000U    // Zone Status Flash Bank 0 Sector 28
#define DCSM_SECTSTAT2_STATUS_SECT29_S   26U
#define DCSM_SECTSTAT2_STATUS_SECT29_M   0xC000000U    // Zone Status Flash Bank 0 Sector 29
#define DCSM_SECTSTAT2_STATUS_SECT30_S   28U
#define DCSM_SECTSTAT2_STATUS_SECT30_M   0x30000000U   // Zone Status Flash Bank 0 Sector 30
#define DCSM_SECTSTAT2_STATUS_SECT31_S   30U
#define DCSM_SECTSTAT2_STATUS_SECT31_M   0xC0000000U   // Zone Status Flash Bank 0 Sector 31

//*************************************************************************************************
//
// The following are defines for the bit fields in the SECTSTAT3 register
//
//*************************************************************************************************
#define DCSM_SECTSTAT3_STATUS_SECT39_32_S     8U
#define DCSM_SECTSTAT3_STATUS_SECT39_32_M     0x300U        // Zone Status flash Bank 0 Sectors
                                                            // 39-32
#define DCSM_SECTSTAT3_STATUS_SECT47_40_S     10U
#define DCSM_SECTSTAT3_STATUS_SECT47_40_M     0xC00U        // Zone Status flash Bank 0 Sectors
                                                            // 47-40
#define DCSM_SECTSTAT3_STATUS_SECT55_48_S     12U
#define DCSM_SECTSTAT3_STATUS_SECT55_48_M     0x3000U       // Zone Status flash Bank 0 Sectors
                                                            // 55-48
#define DCSM_SECTSTAT3_STATUS_SECT63_56_S     14U
#define DCSM_SECTSTAT3_STATUS_SECT63_56_M     0xC000U       // Zone Status flash Bank 0 Sectors
                                                            // 63-56
#define DCSM_SECTSTAT3_STATUS_SECT71_64_S     16U
#define DCSM_SECTSTAT3_STATUS_SECT71_64_M     0x30000U      // Zone Status flash Bank 0 Sectors
                                                            // 71-64
#define DCSM_SECTSTAT3_STATUS_SECT79_72_S     18U
#define DCSM_SECTSTAT3_STATUS_SECT79_72_M     0xC0000U      // Zone Status flash Bank 0 Sectors
                                                            // 79-72
#define DCSM_SECTSTAT3_STATUS_SECT87_80_S     20U
#define DCSM_SECTSTAT3_STATUS_SECT87_80_M     0x300000U     // Zone Status flash Bank 0 Sectors
                                                            // 87-80
#define DCSM_SECTSTAT3_STATUS_SECT95_88_S     22U
#define DCSM_SECTSTAT3_STATUS_SECT95_88_M     0xC00000U     // Zone Status flash Bank 0 Sectors
                                                            // 95-88
#define DCSM_SECTSTAT3_STATUS_SECT103_96_S    24U
#define DCSM_SECTSTAT3_STATUS_SECT103_96_M    0x3000000U    // Zone Status flash Bank 0 Sectors
                                                            // 103-96
#define DCSM_SECTSTAT3_STATUS_SECT111_104_S   26U
#define DCSM_SECTSTAT3_STATUS_SECT111_104_M   0xC000000U    // Zone Status flash Bank 0 Sectors
                                                            // 111-104
#define DCSM_SECTSTAT3_STATUS_SECT119_112_S   28U
#define DCSM_SECTSTAT3_STATUS_SECT119_112_M   0x30000000U   // Zone Status flash Bank 0 Sectors
                                                            // 119-112
#define DCSM_SECTSTAT3_STATUS_SECT127_120_S   30U
#define DCSM_SECTSTAT3_STATUS_SECT127_120_M   0xC0000000U   // Zone Status flash Bank 0 Sectors
                                                            // 127-120

//*************************************************************************************************
//
// The following are defines for the bit fields in the RAMSTAT1 register
//
//*************************************************************************************************
#define DCSM_RAMSTAT1_STATUS_RAM0_S   0U
#define DCSM_RAMSTAT1_STATUS_RAM0_M   0x3U      // Zone Status RAM LS0 Section A
#define DCSM_RAMSTAT1_STATUS_RAM1_S   2U
#define DCSM_RAMSTAT1_STATUS_RAM1_M   0xCU      // Zone Status RAM LS0 Section B
#define DCSM_RAMSTAT1_STATUS_RAM2_S   4U
#define DCSM_RAMSTAT1_STATUS_RAM2_M   0x30U     // Zone Status RAM LS0 Section C
#define DCSM_RAMSTAT1_STATUS_RAM3_S   6U
#define DCSM_RAMSTAT1_STATUS_RAM3_M   0xC0U     // Zone Status RAM LS0 Section D
#define DCSM_RAMSTAT1_STATUS_RAM4_S   8U
#define DCSM_RAMSTAT1_STATUS_RAM4_M   0x300U    // Zone Status RAM LS1 Section A
#define DCSM_RAMSTAT1_STATUS_RAM5_S   10U
#define DCSM_RAMSTAT1_STATUS_RAM5_M   0xC00U    // Zone Status RAM LS1 Section B
#define DCSM_RAMSTAT1_STATUS_RAM6_S   12U
#define DCSM_RAMSTAT1_STATUS_RAM6_M   0x3000U   // Zone Status RAM LS1 Section C
#define DCSM_RAMSTAT1_STATUS_RAM7_S   14U
#define DCSM_RAMSTAT1_STATUS_RAM7_M   0xC000U   // Zone Status RAM LS1 Section D

//*************************************************************************************************
//
// The following are defines for the bit fields in the SECERRSTAT register
//
//*************************************************************************************************
#define DCSM_SECERRSTAT_ERR   0x1U   // Security Configuration load Error Status

//*************************************************************************************************
//
// The following are defines for the bit fields in the SECERRCLR register
//
//*************************************************************************************************
#define DCSM_SECERRCLR_ERR   0x1U   // Clear Security Configuration Load Error Status Bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the SECERRFRC register
//
//*************************************************************************************************
#define DCSM_SECERRFRC_ERR     0x1U          // Set Security Configuration Load Error Status Bit
#define DCSM_SECERRFRC_KEY_S   16U
#define DCSM_SECERRFRC_KEY_M   0xFFFF0000U   // Valid Register Write Key

//*************************************************************************************************
//
// The following are defines for the bit fields in the DENYCODE register
//
//*************************************************************************************************
#define DCSM_DENYCODE_BLOCKED     0x1U    // Blocked Code
#define DCSM_DENYCODE_ILLADDR     0x2U    // Illegal Address Code
#define DCSM_DENYCODE_ILLPROG     0x4U    // Illegal Program Address
#define DCSM_DENYCODE_ILLERASE    0x8U    // Illegal Erase Address
#define DCSM_DENYCODE_ILLRDVER    0x10U   // Illegal Read Verify Address
#define DCSM_DENYCODE_ILLMODECH   0x20U   // Illegal Mode Change
#define DCSM_DENYCODE_ILLCMD      0x40U   // Illegal Command
#define DCSM_DENYCODE_ILLSIZE     0x80U   // Illegal Command Size

//*************************************************************************************************
//
// The following are defines for the bit fields in the RAMOPENSTAT register
//
//*************************************************************************************************
#define DCSM_RAMOPENSTAT_RAMOPEN   0x1U   // RAM Security Open

//*************************************************************************************************
//
// The following are defines for the bit fields in the RAMOPENFRC register
//
//*************************************************************************************************
#define DCSM_RAMOPENFRC_SET     0x1U          // Set RAM Open request
#define DCSM_RAMOPENFRC_KEY_S   16U
#define DCSM_RAMOPENFRC_KEY_M   0xFFFF0000U   // Valid Write KEY

//*************************************************************************************************
//
// The following are defines for the bit fields in the RAMOPENCLR register
//
//*************************************************************************************************
#define DCSM_RAMOPENCLR_CLEAR   0x1U          // Clear RAM Open request
#define DCSM_RAMOPENCLR_KEY_S   16U
#define DCSM_RAMOPENCLR_KEY_M   0xFFFF0000U   // Valid Write KEY

//*************************************************************************************************
//
// The following are defines for the bit fields in the RAMOPENLOCK register
//
//*************************************************************************************************
#define DCSM_RAMOPENLOCK_LOCK   0x1U   // RAMOPEN Lock



#endif
