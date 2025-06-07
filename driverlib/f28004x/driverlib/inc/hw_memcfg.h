//###########################################################################
//
// FILE:    hw_memcfg.h
//
// TITLE:   Definitions for the MEMCFG registers.
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

#ifndef HW_MEMCFG_H
#define HW_MEMCFG_H

//*************************************************************************************************
//
// The following are defines for the MEMCFG register offsets
//
//*************************************************************************************************
#define MEMCFG_O_DXLOCK         0x0U    // Dedicated RAM Config Lock Register
#define MEMCFG_O_DXCOMMIT       0x2U    // Dedicated RAM Config Lock Commit Register
#define MEMCFG_O_DXTEST         0x10U   // Dedicated RAM TEST Register
#define MEMCFG_O_DXINIT         0x12U   // Dedicated RAM Init Register
#define MEMCFG_O_DXINITDONE     0x14U   // Dedicated RAM InitDone Status Register
#define MEMCFG_O_LSXLOCK        0x20U   // Local Shared RAM Config Lock Register
#define MEMCFG_O_LSXCOMMIT      0x22U   // Local Shared RAM Config Lock Commit Register
#define MEMCFG_O_LSXMSEL        0x24U   // Local Shared RAM Master Sel Register
#define MEMCFG_O_LSXCLAPGM      0x26U   // Local Shared RAM Prog/Exe control Register
#define MEMCFG_O_LSXACCPROT0    0x28U   // Local Shared RAM Config Register 0
#define MEMCFG_O_LSXACCPROT1    0x2AU   // Local Shared RAM Config Register 1
#define MEMCFG_O_LSXTEST        0x30U   // Local Shared RAM TEST Register
#define MEMCFG_O_LSXINIT        0x32U   // Local Shared RAM Init Register
#define MEMCFG_O_LSXINITDONE    0x34U   // Local Shared RAM InitDone Status Register
#define MEMCFG_O_GSXLOCK        0x40U   // Global Shared RAM Config Lock Register
#define MEMCFG_O_GSXCOMMIT      0x42U   // Global Shared RAM Config Lock Commit Register
#define MEMCFG_O_GSXACCPROT0    0x48U   // Global Shared RAM Config Register 0
#define MEMCFG_O_GSXTEST        0x50U   // Global Shared RAM TEST Register
#define MEMCFG_O_GSXINIT        0x52U   // Global Shared RAM Init Register
#define MEMCFG_O_GSXINITDONE    0x54U   // Global Shared RAM InitDone Status Register
#define MEMCFG_O_MSGXLOCK       0x60U   // Message RAM Config Lock Register
#define MEMCFG_O_MSGXCOMMIT     0x62U   // Message RAM Config Lock Commit Register
#define MEMCFG_O_MSGXTEST       0x70U   // Message RAM TEST Register
#define MEMCFG_O_MSGXINIT       0x72U   // Message RAM Init Register
#define MEMCFG_O_MSGXINITDONE   0x74U   // Message RAM InitDone Status Register

#define MEMCFG_O_NMAVFLG          0x0U    // Non-Master Access Violation Flag Register
#define MEMCFG_O_NMAVSET          0x2U    // Non-Master Access Violation Flag Set Register
#define MEMCFG_O_NMAVCLR          0x4U    // Non-Master Access Violation Flag Clear Register
#define MEMCFG_O_NMAVINTEN        0x6U    // Non-Master Access Violation Interrupt Enable Register
#define MEMCFG_O_NMCPURDAVADDR    0x8U    // Non-Master CPU Read Access Violation Address
#define MEMCFG_O_NMCPUWRAVADDR    0xAU    // Non-Master CPU Write Access Violation Address
#define MEMCFG_O_NMCPUFAVADDR     0xCU    // Non-Master CPU Fetch Access Violation Address
#define MEMCFG_O_NMCLA1RDAVADDR   0x10U   // Non-Master CLA1 Read Access Violation Address
#define MEMCFG_O_NMCLA1WRAVADDR   0x12U   // Non-Master CLA1 Write Access Violation Address
#define MEMCFG_O_NMCLA1FAVADDR    0x14U   // Non-Master CLA1 Fetch Access Violation Address
#define MEMCFG_O_MAVFLG           0x20U   // Master Access Violation Flag Register
#define MEMCFG_O_MAVSET           0x22U   // Master Access Violation Flag Set Register
#define MEMCFG_O_MAVCLR           0x24U   // Master Access Violation Flag Clear Register
#define MEMCFG_O_MAVINTEN         0x26U   // Master Access Violation Interrupt Enable Register
#define MEMCFG_O_MCPUFAVADDR      0x28U   // Master CPU Fetch Access Violation Address
#define MEMCFG_O_MCPUWRAVADDR     0x2AU   // Master CPU Write Access Violation Address
#define MEMCFG_O_MDMAWRAVADDR     0x2CU   // Master  DMA Write Access Violation Address

#define MEMCFG_O_UCERRFLG       0x0U    // Uncorrectable Error Flag Register
#define MEMCFG_O_UCERRSET       0x2U    // Uncorrectable Error Flag Set Register
#define MEMCFG_O_UCERRCLR       0x4U    // Uncorrectable Error Flag Clear Register
#define MEMCFG_O_UCCPUREADDR    0x6U    // Uncorrectable CPU Read Error Address
#define MEMCFG_O_UCDMAREADDR    0x8U    // Uncorrectable DMA Read Error Address
#define MEMCFG_O_UCCLA1READDR   0xAU    // Uncorrectable CLA1 Read Error Address
#define MEMCFG_O_CERRFLG        0x20U   // Correctable Error Flag Register
#define MEMCFG_O_CERRSET        0x22U   // Correctable Error Flag Set Register
#define MEMCFG_O_CERRCLR        0x24U   // Correctable Error Flag Clear Register
#define MEMCFG_O_CCPUREADDR     0x26U   // Correctable CPU Read Error Address
#define MEMCFG_O_CERRCNT        0x2EU   // Correctable Error Count Register
#define MEMCFG_O_CERRTHRES      0x30U   // Correctable Error Threshold Value Register
#define MEMCFG_O_CEINTFLG       0x32U   // Correctable Error Interrupt Flag Status Register
#define MEMCFG_O_CEINTCLR       0x34U   // Correctable Error Interrupt Flag Clear Register
#define MEMCFG_O_CEINTSET       0x36U   // Correctable Error Interrupt Flag Set Register
#define MEMCFG_O_CEINTEN        0x38U   // Correctable Error Interrupt Enable Register


//*************************************************************************************************
//
// The following are defines for the bit fields in the DxLOCK register
//
//*************************************************************************************************
#define MEMCFG_DXLOCK_LOCK_M0   0x1U   // M0 RAM Lock bits
#define MEMCFG_DXLOCK_LOCK_M1   0x2U   // M1 RAM Lock bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the DxCOMMIT register
//
//*************************************************************************************************
#define MEMCFG_DXCOMMIT_COMMIT_M0   0x1U   // M0 RAM Permanent Lock bits
#define MEMCFG_DXCOMMIT_COMMIT_M1   0x2U   // M1 RAM Permanent Lock bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the DxTEST register
//
//*************************************************************************************************
#define MEMCFG_DXTEST_TEST_M0_S   0U
#define MEMCFG_DXTEST_TEST_M0_M   0x3U   // Selects the different modes for M0 RAM
#define MEMCFG_DXTEST_TEST_M1_S   2U
#define MEMCFG_DXTEST_TEST_M1_M   0xCU   // Selects the different modes for M1 RAM

//*************************************************************************************************
//
// The following are defines for the bit fields in the DxINIT register
//
//*************************************************************************************************
#define MEMCFG_DXINIT_INIT_M0   0x1U   // RAM Initialization control for M0 RAM.
#define MEMCFG_DXINIT_INIT_M1   0x2U   // RAM Initialization control for M1 RAM.

//*************************************************************************************************
//
// The following are defines for the bit fields in the DxINITDONE register
//
//*************************************************************************************************
#define MEMCFG_DXINITDONE_INITDONE_M0   0x1U   // RAM Initialization status for M0 RAM.
#define MEMCFG_DXINITDONE_INITDONE_M1   0x2U   // RAM Initialization status for M1 RAM.

//*************************************************************************************************
//
// The following are defines for the bit fields in the LSxLOCK register
//
//*************************************************************************************************
#define MEMCFG_LSXLOCK_LOCK_LS0   0x1U    // LS0 RAM Lock bits
#define MEMCFG_LSXLOCK_LOCK_LS1   0x2U    // LS1 RAM Lock bits
#define MEMCFG_LSXLOCK_LOCK_LS2   0x4U    // LS2 RAM Lock bits
#define MEMCFG_LSXLOCK_LOCK_LS3   0x8U    // LS3 RAM Lock bits
#define MEMCFG_LSXLOCK_LOCK_LS4   0x10U   // LS4 RAM Lock bits
#define MEMCFG_LSXLOCK_LOCK_LS5   0x20U   // LS5 RAM Lock bits
#define MEMCFG_LSXLOCK_LOCK_LS6   0x40U   // LS6 RAM Lock bits
#define MEMCFG_LSXLOCK_LOCK_LS7   0x80U   // LS7 RAM Lock bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the LSxCOMMIT register
//
//*************************************************************************************************
#define MEMCFG_LSXCOMMIT_COMMIT_LS0   0x1U    // LS0 RAM Permanent Lock bits
#define MEMCFG_LSXCOMMIT_COMMIT_LS1   0x2U    // LS1 RAM Permanent Lock bits
#define MEMCFG_LSXCOMMIT_COMMIT_LS2   0x4U    // LS2 RAM Permanent Lock bits
#define MEMCFG_LSXCOMMIT_COMMIT_LS3   0x8U    // LS3 RAM Permanent Lock bits
#define MEMCFG_LSXCOMMIT_COMMIT_LS4   0x10U   // LS4 RAM Permanent Lock bits
#define MEMCFG_LSXCOMMIT_COMMIT_LS5   0x20U   // LS5 RAM Permanent Lock bits
#define MEMCFG_LSXCOMMIT_COMMIT_LS6   0x40U   // LS6 RAM Permanent Lock bits
#define MEMCFG_LSXCOMMIT_COMMIT_LS7   0x80U   // LS7 RAM Permanent Lock bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the LSxMSEL register
//
//*************************************************************************************************
#define MEMCFG_LSXMSEL_MSEL_LS0_S   0U
#define MEMCFG_LSXMSEL_MSEL_LS0_M   0x3U      // Master Select for LS0 RAM
#define MEMCFG_LSXMSEL_MSEL_LS1_S   2U
#define MEMCFG_LSXMSEL_MSEL_LS1_M   0xCU      // Master Select for LS1 RAM
#define MEMCFG_LSXMSEL_MSEL_LS2_S   4U
#define MEMCFG_LSXMSEL_MSEL_LS2_M   0x30U     // Master Select for LS2 RAM
#define MEMCFG_LSXMSEL_MSEL_LS3_S   6U
#define MEMCFG_LSXMSEL_MSEL_LS3_M   0xC0U     // Master Select for LS3 RAM
#define MEMCFG_LSXMSEL_MSEL_LS4_S   8U
#define MEMCFG_LSXMSEL_MSEL_LS4_M   0x300U    // Master Select for LS4 RAM
#define MEMCFG_LSXMSEL_MSEL_LS5_S   10U
#define MEMCFG_LSXMSEL_MSEL_LS5_M   0xC00U    // Master Select for LS5 RAM
#define MEMCFG_LSXMSEL_MSEL_LS6_S   12U
#define MEMCFG_LSXMSEL_MSEL_LS6_M   0x3000U   // Master Select for LS6 RAM
#define MEMCFG_LSXMSEL_MSEL_LS7_S   14U
#define MEMCFG_LSXMSEL_MSEL_LS7_M   0xC000U   // Master Select for LS7 RAM

//*************************************************************************************************
//
// The following are defines for the bit fields in the LSxCLAPGM register
//
//*************************************************************************************************
#define MEMCFG_LSXCLAPGM_CLAPGM_LS0   0x1U    // Selects LS0 RAM as program vs data memory for CLA
#define MEMCFG_LSXCLAPGM_CLAPGM_LS1   0x2U    // Selects LS1 RAM as program vs data memory for CLA
#define MEMCFG_LSXCLAPGM_CLAPGM_LS2   0x4U    // Selects LS2 RAM as program vs data memory for CLA
#define MEMCFG_LSXCLAPGM_CLAPGM_LS3   0x8U    // Selects LS3 RAM as program vs data memory for CLA
#define MEMCFG_LSXCLAPGM_CLAPGM_LS4   0x10U   // Selects LS4 RAM as program vs data memory for CLA
#define MEMCFG_LSXCLAPGM_CLAPGM_LS5   0x20U   // Selects LS5 RAM as program vs data memory for CLA
#define MEMCFG_LSXCLAPGM_CLAPGM_LS6   0x40U   // Selects LS6 RAM as program vs data memory for CLA
#define MEMCFG_LSXCLAPGM_CLAPGM_LS7   0x80U   // Selects LS7 RAM as program vs data memory for CLA

//*************************************************************************************************
//
// The following are defines for the bit fields in the LSxACCPROT0 register
//
//*************************************************************************************************
#define MEMCFG_LSXACCPROT0_FETCHPROT_LS0   0x1U         // Fetch Protection For LS0 RAM
#define MEMCFG_LSXACCPROT0_CPUWRPROT_LS0   0x2U         // CPU WR Protection For LS0 RAM
#define MEMCFG_LSXACCPROT0_FETCHPROT_LS1   0x100U       // Fetch Protection For LS1 RAM
#define MEMCFG_LSXACCPROT0_CPUWRPROT_LS1   0x200U       // CPU WR Protection For LS1 RAM
#define MEMCFG_LSXACCPROT0_FETCHPROT_LS2   0x10000U     // Fetch Protection For LS2 RAM
#define MEMCFG_LSXACCPROT0_CPUWRPROT_LS2   0x20000U     // CPU WR Protection For LS2 RAM
#define MEMCFG_LSXACCPROT0_FETCHPROT_LS3   0x1000000U   // Fetch Protection For LS3 RAM
#define MEMCFG_LSXACCPROT0_CPUWRPROT_LS3   0x2000000U   // CPU WR Protection For LS3 RAM

//*************************************************************************************************
//
// The following are defines for the bit fields in the LSxACCPROT1 register
//
//*************************************************************************************************
#define MEMCFG_LSXACCPROT1_FETCHPROT_LS4   0x1U         // Fetch Protection For LS4 RAM
#define MEMCFG_LSXACCPROT1_CPUWRPROT_LS4   0x2U         // CPU WR Protection For LS4 RAM
#define MEMCFG_LSXACCPROT1_FETCHPROT_LS5   0x100U       // Fetch Protection For LS5 RAM
#define MEMCFG_LSXACCPROT1_CPUWRPROT_LS5   0x200U       // CPU WR Protection For LS5 RAM
#define MEMCFG_LSXACCPROT1_FETCHPROT_LS6   0x10000U     // Fetch Protection For LS6 RAM
#define MEMCFG_LSXACCPROT1_CPUWRPROT_LS6   0x20000U     // CPU WR Protection For LS6 RAM
#define MEMCFG_LSXACCPROT1_FETCHPROT_LS7   0x1000000U   // Fetch Protection For LS7 RAM
#define MEMCFG_LSXACCPROT1_CPUWRPROT_LS7   0x2000000U   // CPU WR Protection For LS7 RAM

//*************************************************************************************************
//
// The following are defines for the bit fields in the LSxTEST register
//
//*************************************************************************************************
#define MEMCFG_LSXTEST_TEST_LS0_S   0U
#define MEMCFG_LSXTEST_TEST_LS0_M   0x3U      // Selects the different modes for LS0 RAM
#define MEMCFG_LSXTEST_TEST_LS1_S   2U
#define MEMCFG_LSXTEST_TEST_LS1_M   0xCU      // Selects the different modes for LS1 RAM
#define MEMCFG_LSXTEST_TEST_LS2_S   4U
#define MEMCFG_LSXTEST_TEST_LS2_M   0x30U     // Selects the different modes for LS2 RAM
#define MEMCFG_LSXTEST_TEST_LS3_S   6U
#define MEMCFG_LSXTEST_TEST_LS3_M   0xC0U     // Selects the different modes for LS3 RAM
#define MEMCFG_LSXTEST_TEST_LS4_S   8U
#define MEMCFG_LSXTEST_TEST_LS4_M   0x300U    // Selects the different modes for LS4 RAM
#define MEMCFG_LSXTEST_TEST_LS5_S   10U
#define MEMCFG_LSXTEST_TEST_LS5_M   0xC00U    // Selects the different modes for LS5 RAM
#define MEMCFG_LSXTEST_TEST_LS6_S   12U
#define MEMCFG_LSXTEST_TEST_LS6_M   0x3000U   // Selects the different modes for LS6 RAM
#define MEMCFG_LSXTEST_TEST_LS7_S   14U
#define MEMCFG_LSXTEST_TEST_LS7_M   0xC000U   // Selects the different modes for LS7 RAM

//*************************************************************************************************
//
// The following are defines for the bit fields in the LSxINIT register
//
//*************************************************************************************************
#define MEMCFG_LSXINIT_INIT_LS0   0x1U    // RAM Initialization control for LS0 RAM.
#define MEMCFG_LSXINIT_INIT_LS1   0x2U    // RAM Initialization control for LS1 RAM.
#define MEMCFG_LSXINIT_INIT_LS2   0x4U    // RAM Initialization control for LS2 RAM.
#define MEMCFG_LSXINIT_INIT_LS3   0x8U    // RAM Initialization control for LS3 RAM.
#define MEMCFG_LSXINIT_INIT_LS4   0x10U   // RAM Initialization control for LS4 RAM.
#define MEMCFG_LSXINIT_INIT_LS5   0x20U   // RAM Initialization control for LS5 RAM.
#define MEMCFG_LSXINIT_INIT_LS6   0x40U   // RAM Initialization control for LS6 RAM.
#define MEMCFG_LSXINIT_INIT_LS7   0x80U   // RAM Initialization control for LS7 RAM.

//*************************************************************************************************
//
// The following are defines for the bit fields in the LSxINITDONE register
//
//*************************************************************************************************
#define MEMCFG_LSXINITDONE_INITDONE_LS0   0x1U    // RAM Initialization status for LS0 RAM.
#define MEMCFG_LSXINITDONE_INITDONE_LS1   0x2U    // RAM Initialization status for LS1 RAM.
#define MEMCFG_LSXINITDONE_INITDONE_LS2   0x4U    // RAM Initialization status for LS2 RAM.
#define MEMCFG_LSXINITDONE_INITDONE_LS3   0x8U    // RAM Initialization status for LS3 RAM.
#define MEMCFG_LSXINITDONE_INITDONE_LS4   0x10U   // RAM Initialization status for LS4 RAM.
#define MEMCFG_LSXINITDONE_INITDONE_LS5   0x20U   // RAM Initialization status for LS5 RAM.
#define MEMCFG_LSXINITDONE_INITDONE_LS6   0x40U   // RAM Initialization status for LS6 RAM.
#define MEMCFG_LSXINITDONE_INITDONE_LS7   0x80U   // RAM Initialization status for LS7 RAM.

//*************************************************************************************************
//
// The following are defines for the bit fields in the GSxLOCK register
//
//*************************************************************************************************
#define MEMCFG_GSXLOCK_LOCK_GS0   0x1U   // GS0 RAM Lock bits
#define MEMCFG_GSXLOCK_LOCK_GS1   0x2U   // GS1 RAM Lock bits
#define MEMCFG_GSXLOCK_LOCK_GS2   0x4U   // GS2 RAM Lock bits
#define MEMCFG_GSXLOCK_LOCK_GS3   0x8U   // GS3 RAM Lock bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the GSxCOMMIT register
//
//*************************************************************************************************
#define MEMCFG_GSXCOMMIT_COMMIT_GS0   0x1U   // GS0 RAM Permanent Lock bits
#define MEMCFG_GSXCOMMIT_COMMIT_GS1   0x2U   // GS1 RAM Permanent Lock bits
#define MEMCFG_GSXCOMMIT_COMMIT_GS2   0x4U   // GS2 RAM Permanent Lock bits
#define MEMCFG_GSXCOMMIT_COMMIT_GS3   0x8U   // GS3 RAM Permanent Lock bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the GSxACCPROT0 register
//
//*************************************************************************************************
#define MEMCFG_GSXACCPROT0_FETCHPROT_GS0   0x1U         // Fetch Protection For GS0 RAM
#define MEMCFG_GSXACCPROT0_CPUWRPROT_GS0   0x2U         // CPU WR Protection For GS0 RAM
#define MEMCFG_GSXACCPROT0_DMAWRPROT_GS0   0x4U         // DMA WR Protection For GS0 RAM
#define MEMCFG_GSXACCPROT0_FETCHPROT_GS1   0x100U       // Fetch Protection For GS1 RAM
#define MEMCFG_GSXACCPROT0_CPUWRPROT_GS1   0x200U       // CPU WR Protection For GS1 RAM
#define MEMCFG_GSXACCPROT0_DMAWRPROT_GS1   0x400U       // DMA WR Protection For GS1 RAM
#define MEMCFG_GSXACCPROT0_FETCHPROT_GS2   0x10000U     // Fetch Protection For GS2 RAM
#define MEMCFG_GSXACCPROT0_CPUWRPROT_GS2   0x20000U     // CPU WR Protection For GS2 RAM
#define MEMCFG_GSXACCPROT0_DMAWRPROT_GS2   0x40000U     // DMA WR Protection For GS2 RAM
#define MEMCFG_GSXACCPROT0_FETCHPROT_GS3   0x1000000U   // Fetch Protection For GS3 RAM
#define MEMCFG_GSXACCPROT0_CPUWRPROT_GS3   0x2000000U   // CPU WR Protection For GS3 RAM
#define MEMCFG_GSXACCPROT0_DMAWRPROT_GS3   0x4000000U   // DMA WR Protection For GS3 RAM

//*************************************************************************************************
//
// The following are defines for the bit fields in the GSxTEST register
//
//*************************************************************************************************
#define MEMCFG_GSXTEST_TEST_GS0_S   0U
#define MEMCFG_GSXTEST_TEST_GS0_M   0x3U    // Selects the different modes for GS0 RAM
#define MEMCFG_GSXTEST_TEST_GS1_S   2U
#define MEMCFG_GSXTEST_TEST_GS1_M   0xCU    // Selects the different modes for GS1 RAM
#define MEMCFG_GSXTEST_TEST_GS2_S   4U
#define MEMCFG_GSXTEST_TEST_GS2_M   0x30U   // Selects the different modes for GS2 RAM
#define MEMCFG_GSXTEST_TEST_GS3_S   6U
#define MEMCFG_GSXTEST_TEST_GS3_M   0xC0U   // Selects the different modes for GS3 RAM

//*************************************************************************************************
//
// The following are defines for the bit fields in the GSxINIT register
//
//*************************************************************************************************
#define MEMCFG_GSXINIT_INIT_GS0   0x1U   // RAM Initialization control for GS0 RAM.
#define MEMCFG_GSXINIT_INIT_GS1   0x2U   // RAM Initialization control for GS1 RAM.
#define MEMCFG_GSXINIT_INIT_GS2   0x4U   // RAM Initialization control for GS2 RAM.
#define MEMCFG_GSXINIT_INIT_GS3   0x8U   // RAM Initialization control for GS3 RAM.

//*************************************************************************************************
//
// The following are defines for the bit fields in the GSxINITDONE register
//
//*************************************************************************************************
#define MEMCFG_GSXINITDONE_INITDONE_GS0   0x1U   // RAM Initialization status for GS0 RAM.
#define MEMCFG_GSXINITDONE_INITDONE_GS1   0x2U   // RAM Initialization status for GS1 RAM.
#define MEMCFG_GSXINITDONE_INITDONE_GS2   0x4U   // RAM Initialization status for GS2 RAM.
#define MEMCFG_GSXINITDONE_INITDONE_GS3   0x8U   // RAM Initialization status for GS3 RAM.

//*************************************************************************************************
//
// The following are defines for the bit fields in the MSGxLOCK register
//
//*************************************************************************************************
#define MEMCFG_MSGXLOCK_LOCK_CPUTOCLA1   0x2U   // CPUTOCLA1 RAM Lock bits
#define MEMCFG_MSGXLOCK_LOCK_CLA1TOCPU   0x4U   // CLA1TOCPU RAM Lock bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the MSGxCOMMIT register
//
//*************************************************************************************************
#define MEMCFG_MSGXCOMMIT_COMMIT_CPUTOCLA1   0x2U   // CPUTOCLA1 RAM control fields COMMIT bit
#define MEMCFG_MSGXCOMMIT_COMMIT_CLA1TOCPU   0x4U   // CLA1TOCPU RAM control fields COMMIT bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the MSGxTEST register
//
//*************************************************************************************************
#define MEMCFG_MSGXTEST_TEST_CPUTOCLA1_S   2U
#define MEMCFG_MSGXTEST_TEST_CPUTOCLA1_M   0xCU    // CPU to CLA1 MSG RAM Mode Select
#define MEMCFG_MSGXTEST_TEST_CLA1TOCPU_S   4U
#define MEMCFG_MSGXTEST_TEST_CLA1TOCPU_M   0x30U   // CLA1 to CPU MSG RAM Mode Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the MSGxINIT register
//
//*************************************************************************************************
#define MEMCFG_MSGXINIT_INIT_CPUTOCLA1   0x2U   // Initialization control for CPUTOCLA1 MSG RAM
#define MEMCFG_MSGXINIT_INIT_CLA1TOCPU   0x4U   // Initialization control for CLA1TOCPU MSG RAM

//*************************************************************************************************
//
// The following are defines for the bit fields in the MSGxINITDONE register
//
//*************************************************************************************************
#define MEMCFG_MSGXINITDONE_INITDONE_CPUTOCLA1   0x2U   // Initialization status for CPU to CLA1
                                                        // MSG RAM
#define MEMCFG_MSGXINITDONE_INITDONE_CLA1TOCPU   0x4U   // Initialization status for CLA1 to CPU
                                                        // MSG RAM


//*************************************************************************************************
//
// The following are defines for the bit fields in the NMAVFLG register
//
//*************************************************************************************************
#define MEMCFG_NMAVFLG_CPUREAD     0x1U    // Non Master CPU Read Access Violation Flag
#define MEMCFG_NMAVFLG_CPUWRITE    0x2U    // Non Master CPU Write Access Violation Flag
#define MEMCFG_NMAVFLG_CPUFETCH    0x4U    // Non Master CPU Fetch Access Violation Flag
#define MEMCFG_NMAVFLG_DMAWRITE    0x8U    // Non Master DMA Write Access Violation Flag
#define MEMCFG_NMAVFLG_CLA1READ    0x10U   // Non Master CLA1 Read Access Violation Flag
#define MEMCFG_NMAVFLG_CLA1WRITE   0x20U   // Non Master CLA1 Write Access Violation Flag
#define MEMCFG_NMAVFLG_CLA1FETCH   0x40U   // Non Master CLA1 Fetch Access Violation Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the NMAVSET register
//
//*************************************************************************************************
#define MEMCFG_NMAVSET_CPUREAD     0x1U    // Non Master CPU Read Access Violation Flag Set
#define MEMCFG_NMAVSET_CPUWRITE    0x2U    // Non Master CPU Write Access Violation Flag Set
#define MEMCFG_NMAVSET_CPUFETCH    0x4U    // Non Master CPU Fetch Access Violation Flag Set
#define MEMCFG_NMAVSET_DMAWRITE    0x8U    // Non Master DMA Write Access Violation Flag Set
#define MEMCFG_NMAVSET_CLA1READ    0x10U   // Non Master CLA1 Read Access Violation Flag Set
#define MEMCFG_NMAVSET_CLA1WRITE   0x20U   // Non Master CLA1 Write Access Violation Flag Set
#define MEMCFG_NMAVSET_CLA1FETCH   0x40U   // Non Master CLA1 Fetch Access Violation Flag Set

//*************************************************************************************************
//
// The following are defines for the bit fields in the NMAVCLR register
//
//*************************************************************************************************
#define MEMCFG_NMAVCLR_CPUREAD     0x1U    // Non Master CPU Read Access Violation Flag Clear
#define MEMCFG_NMAVCLR_CPUWRITE    0x2U    // Non Master CPU Write Access Violation Flag Clear
#define MEMCFG_NMAVCLR_CPUFETCH    0x4U    // Non Master CPU Fetch Access Violation Flag Clear
#define MEMCFG_NMAVCLR_DMAWRITE    0x8U    // Non Master DMA Write Access Violation Flag Clear
#define MEMCFG_NMAVCLR_CLA1READ    0x10U   // Non Master CLA1 Read Access Violation Flag Clear
#define MEMCFG_NMAVCLR_CLA1WRITE   0x20U   // Non Master CLA1 Write Access Violation Flag Clear
#define MEMCFG_NMAVCLR_CLA1FETCH   0x40U   // Non Master CLA1 Fetch Access Violation Flag Clear

//*************************************************************************************************
//
// The following are defines for the bit fields in the NMAVINTEN register
//
//*************************************************************************************************
#define MEMCFG_NMAVINTEN_CPUREAD     0x1U    // Non Master CPU Read Access Violation Interrupt
                                             // Enable
#define MEMCFG_NMAVINTEN_CPUWRITE    0x2U    // Non Master CPU Write Access Violation Interrupt
                                             // Enable
#define MEMCFG_NMAVINTEN_CPUFETCH    0x4U    // Non Master CPU Fetch Access Violation Interrupt
                                             // Enable
#define MEMCFG_NMAVINTEN_CLA1READ    0x10U   // Non Master CLA1 Read Access Violation Interrupt
                                             // Enable
#define MEMCFG_NMAVINTEN_CLA1WRITE   0x20U   // Non Master CLA1 Write Access Violation Interrupt
                                             // Enable
#define MEMCFG_NMAVINTEN_CLA1FETCH   0x40U   // Non Master CLA1 Fetch Access Violation Interrupt
                                             // Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the MAVFLG register
//
//*************************************************************************************************
#define MEMCFG_MAVFLG_CPUFETCH   0x1U   // Master CPU Fetch Access Violation Flag
#define MEMCFG_MAVFLG_CPUWRITE   0x2U   // Master CPU Write Access Violation Flag
#define MEMCFG_MAVFLG_DMAWRITE   0x4U   // Master DMA Write Access Violation Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the MAVSET register
//
//*************************************************************************************************
#define MEMCFG_MAVSET_CPUFETCH   0x1U   // Master CPU Fetch Access Violation Flag Set
#define MEMCFG_MAVSET_CPUWRITE   0x2U   // Master CPU Write Access Violation Flag Set
#define MEMCFG_MAVSET_DMAWRITE   0x4U   // Master DMA Write Access Violation Flag Set

//*************************************************************************************************
//
// The following are defines for the bit fields in the MAVCLR register
//
//*************************************************************************************************
#define MEMCFG_MAVCLR_CPUFETCH   0x1U   // Master CPU Fetch Access Violation Flag Clear
#define MEMCFG_MAVCLR_CPUWRITE   0x2U   // Master CPU Write Access Violation Flag Clear
#define MEMCFG_MAVCLR_DMAWRITE   0x4U   // Master DMA Write Access Violation Flag Clear

//*************************************************************************************************
//
// The following are defines for the bit fields in the MAVINTEN register
//
//*************************************************************************************************
#define MEMCFG_MAVINTEN_CPUFETCH   0x1U   // Master CPU Fetch Access Violation Interrupt Enable
#define MEMCFG_MAVINTEN_CPUWRITE   0x2U   // Master CPU Write Access Violation Interrupt Enable
#define MEMCFG_MAVINTEN_DMAWRITE   0x4U   // Master DMA Write Access Violation Interrupt Enable


//*************************************************************************************************
//
// The following are defines for the bit fields in the UCERRFLG register
//
//*************************************************************************************************
#define MEMCFG_UCERRFLG_CPURDERR    0x1U   // CPU Uncorrectable Read Error Flag
#define MEMCFG_UCERRFLG_DMARDERR    0x2U   // DMA Uncorrectable Read Error Flag
#define MEMCFG_UCERRFLG_CLA1RDERR   0x4U   // CLA1 Uncorrectable Read Error Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the UCERRSET register
//
//*************************************************************************************************
#define MEMCFG_UCERRSET_CPURDERR    0x1U   // CPU Uncorrectable Read Error Flag Set
#define MEMCFG_UCERRSET_DMARDERR    0x2U   // DMA Uncorrectable Read Error Flag Set
#define MEMCFG_UCERRSET_CLA1RDERR   0x4U   // CLA1 Uncorrectable Read Error Flag Set

//*************************************************************************************************
//
// The following are defines for the bit fields in the UCERRCLR register
//
//*************************************************************************************************
#define MEMCFG_UCERRCLR_CPURDERR    0x1U   // CPU Uncorrectable Read Error Flag Clear
#define MEMCFG_UCERRCLR_DMARDERR    0x2U   // DMA Uncorrectable Read Error Flag Clear
#define MEMCFG_UCERRCLR_CLA1RDERR   0x4U   // CLA1 Uncorrectable Read Error Flag Clear

//*************************************************************************************************
//
// The following are defines for the bit fields in the CERRFLG register
//
//*************************************************************************************************
#define MEMCFG_CERRFLG_CPURDERR    0x1U   // CPU Correctable Read Error Flag
#define MEMCFG_CERRFLG_DMARDERR    0x2U   // DMA Correctable Read Error Flag
#define MEMCFG_CERRFLG_CLA1RDERR   0x4U   // CLA1 Correctable Read Error Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the CERRSET register
//
//*************************************************************************************************
#define MEMCFG_CERRSET_CPURDERR    0x1U   // CPU Correctable Read Error Flag Set
#define MEMCFG_CERRSET_DMARDERR    0x2U   // DMA Correctable Read Error Flag Set
#define MEMCFG_CERRSET_CLA1RDERR   0x4U   // CLA1 Correctable Read Error Flag Set

//*************************************************************************************************
//
// The following are defines for the bit fields in the CERRCLR register
//
//*************************************************************************************************
#define MEMCFG_CERRCLR_CPURDERR    0x1U   // CPU Correctable Read Error Flag Clear
#define MEMCFG_CERRCLR_DMARDERR    0x2U   // DMA Correctable Read Error Flag Clear
#define MEMCFG_CERRCLR_CLA1RDERR   0x4U   // CLA1 Correctable Read Error Flag Clear

//*************************************************************************************************
//
// The following are defines for the bit fields in the CEINTFLG register
//
//*************************************************************************************************
#define MEMCFG_CEINTFLG_CEINTFLAG   0x1U   // Total corrected error count exceeded threshold flag.

//*************************************************************************************************
//
// The following are defines for the bit fields in the CEINTCLR register
//
//*************************************************************************************************
#define MEMCFG_CEINTCLR_CEINTCLR   0x1U   // CPU Corrected Error Threshold Exceeded Error Clear.

//*************************************************************************************************
//
// The following are defines for the bit fields in the CEINTSET register
//
//*************************************************************************************************
#define MEMCFG_CEINTSET_CEINTSET   0x1U   // Total corrected error count exceeded flag set.

//*************************************************************************************************
//
// The following are defines for the bit fields in the CEINTEN register
//
//*************************************************************************************************
#define MEMCFG_CEINTEN_CEINTEN   0x1U   // CPU/DMA Correctable Error Interrupt Enable.



#endif
