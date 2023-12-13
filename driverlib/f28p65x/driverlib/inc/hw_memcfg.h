//###########################################################################
//
// FILE:    hw_memcfg.h
//
// TITLE:   Definitions for the MEMCFG registers.
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

#ifndef HW_MEMCFG_H
#define HW_MEMCFG_H

//*************************************************************************************************
//
// The following are defines for the MEMCFG register offsets
//
//*************************************************************************************************
#define MEMCFG_O_DXLOCK                  0x0U    // Dedicated RAM Config Lock Register
#define MEMCFG_O_DXCOMMIT                0x2U    // Dedicated RAM Config Lock Commit Register
#define MEMCFG_O_DXACCPROT0              0x8U    // Dedicated RAM Config Register
#define MEMCFG_O_DXACCPROT1              0xAU    // Dedicated RAM Config Register
#define MEMCFG_O_DXTEST                  0x10U   // Dedicated RAM TEST Register
#define MEMCFG_O_DXINIT                  0x12U   // Dedicated RAM Init Register
#define MEMCFG_O_DXINITDONE              0x14U   // Dedicated RAM InitDone Status Register
#define MEMCFG_O_DXRAMTEST_LOCK          0x16U   // Lock register to Dx RAM TEST registers
#define MEMCFG_O_LSXLOCK                 0x20U   // Local Shared RAM Config Lock Register
#define MEMCFG_O_LSXCOMMIT               0x22U   // Local Shared RAM Config Lock Commit Register
#define MEMCFG_O_LSXMSEL                 0x24U   // Local Shared RAM Controller Sel Register
#define MEMCFG_O_LSXCLAPGM               0x26U   // Local Shared RAM Prog/Exe control Register
#define MEMCFG_O_LSXACCPROT0             0x28U   // Local Shared RAM Config Register 0
#define MEMCFG_O_LSXACCPROT1             0x2AU   // Local Shared RAM Config Register 1
#define MEMCFG_O_LSXACCPROT2             0x2CU   // Local Shared RAM Config Register 2
#define MEMCFG_O_LSXTEST                 0x30U   // Local Shared RAM TEST Register
#define MEMCFG_O_LSXINIT                 0x32U   // Local Shared RAM Init Register
#define MEMCFG_O_LSXINITDONE             0x34U   // Local Shared RAM InitDone Status Register
#define MEMCFG_O_LSXRAMTEST_LOCK         0x36U   // Lock register to LSx RAM TEST registers
#define MEMCFG_O_GSXLOCK                 0x40U   // Global Shared RAM Config Lock Register
#define MEMCFG_O_GSXCOMMIT               0x42U   // Global Shared RAM Config Lock Commit Register
#define MEMCFG_O_GSXMSEL                 0x44U   // Global Shared RAM Controller Sel Register
#define MEMCFG_O_GSXACCPROT0             0x48U   // Global Shared RAM Config Register 0
#define MEMCFG_O_GSXACCPROT1             0x4AU   // Global Shared RAM Config Register 1
#define MEMCFG_O_GSXTEST                 0x50U   // Global Shared RAM TEST Register
#define MEMCFG_O_GSXINIT                 0x52U   // Global Shared RAM Init Register
#define MEMCFG_O_GSXINITDONE             0x54U   // Global Shared RAM InitDone Status Register
#define MEMCFG_O_GSXRAMTEST_LOCK         0x56U   // Lock register to GSx RAM TEST registers
#define MEMCFG_O_MSGXLOCK                0x60U   // Message RAM Config Lock Register
#define MEMCFG_O_MSGXCOMMIT              0x62U   // Message RAM Config Lock Commit Register
#define MEMCFG_O_MSGXACCPROT0            0x68U   // Message RAM Access Protection Register 0
#define MEMCFG_O_MSGXTEST                0x70U   // Message RAM TEST Register
#define MEMCFG_O_MSGXINIT                0x72U   // Message RAM Init Register
#define MEMCFG_O_MSGXINITDONE            0x74U   // Message RAM InitDone Status Register
#define MEMCFG_O_MSGXRAMTEST_LOCK        0x76U   // Lock register for MSGx RAM TEST Register
#define MEMCFG_O_ROM_LOCK                0xA0U   // ROM Config Lock Register
#define MEMCFG_O_ROM_TEST                0xA2U   // ROM  TEST Register
#define MEMCFG_O_ROM_FORCE_ERROR         0xA4U   // ROM Force Error register
#define MEMCFG_O_PERI_MEM_TEST_LOCK      0xAAU   // Peripheral Memory Test Lock Register
#define MEMCFG_O_PERI_MEM_TEST_CONTROL   0xACU   // Peripheral Memory Test control Register

#define MEMCFG_O_EMIF1LOCK       0x0U   // EMIF1 Config Lock Register
#define MEMCFG_O_EMIF1COMMIT     0x2U   // EMIF1 Config Lock Commit Register
#define MEMCFG_O_EMIF1MSEL       0x4U   // EMIF1 Controller Sel Register
#define MEMCFG_O_EMIF1ACCPROT0   0x8U   // EMIF1 Config Register 0

#define MEMCFG_O_NMAVFLG          0x0U    // Non-Controller Access Violation Flag Register
#define MEMCFG_O_NMAVSET          0x2U    // Non-Controller Access Violation Flag Set Register
#define MEMCFG_O_NMAVCLR          0x4U    // Non-Controller Access Violation Flag Clear Register
#define MEMCFG_O_NMAVINTEN        0x6U    // Non-Controller Access Violation Interrupt Enable
                                          // Register
#define MEMCFG_O_NMCPURDAVADDR    0x8U    // Non-Controller CPU Read Access Violation Address
#define MEMCFG_O_NMCPUWRAVADDR    0xAU    // Non-Controller CPU Write Access Violation Address
#define MEMCFG_O_NMCPUFAVADDR     0xCU    // Non-Controller CPU Fetch Access Violation Address
#define MEMCFG_O_NMDMAWRAVADDR    0xEU    // Non-Controller DMA Write Access Violation Address
#define MEMCFG_O_NMCLA1RDAVADDR   0x10U   // Non-Controller CLA1 Read Access Violation Address
#define MEMCFG_O_NMCLA1WRAVADDR   0x12U   // Non-Controller CLA1 Write Access Violation Address
#define MEMCFG_O_NMCLA1FAVADDR    0x14U   // Non-Controller CLA1 Fetch Access Violation Address
#define MEMCFG_O_NMDMARDAVADDR    0x1CU   // Non-Controller DMA Read Access Violation Address
#define MEMCFG_O_MAVFLG           0x20U   // Controller Access Violation Flag Register
#define MEMCFG_O_MAVSET           0x22U   // Controller Access Violation Flag Set Register
#define MEMCFG_O_MAVCLR           0x24U   // Controller Access Violation Flag Clear Register
#define MEMCFG_O_MAVINTEN         0x26U   // Controller Access Violation Interrupt Enable Register
#define MEMCFG_O_MCPUFAVADDR      0x28U   // Controller CPU Fetch Access Violation Address
#define MEMCFG_O_MCPUWRAVADDR     0x2AU   // Controller CPU Write Access Violation Address
#define MEMCFG_O_MDMAWRAVADDR     0x2CU   // Controller  DMA Write Access Violation Address

#define MEMCFG_O_UCERRFLG        0x0U    // Uncorrectable Error Flag Register
#define MEMCFG_O_UCERRSET        0x2U    // Uncorrectable Error Flag Set Register
#define MEMCFG_O_UCERRCLR        0x4U    // Uncorrectable Error Flag Clear Register
#define MEMCFG_O_UCCPUREADDR     0x6U    // Uncorrectable CPU Read Error Address
#define MEMCFG_O_UCDMAREADDR     0x8U    // Uncorrectable DMA Read Error Address
#define MEMCFG_O_UCCLA1READDR    0xAU    // Uncorrectable CLA1 Read Error Address
#define MEMCFG_O_UCECATRAMADDR   0xEU    // Uncorrectable etherCAT RAM Read Error Address
#define MEMCFG_O_FLUCERRSTATUS   0x1CU   // Flash read uncorrectable ecc err status
#define MEMCFG_O_FLCERRSTATUS    0x1EU   // Flash read correctable ecc err status
#define MEMCFG_O_CERRFLG         0x20U   // Correctable Error Flag Register
#define MEMCFG_O_CERRSET         0x22U   // Correctable Error Flag Set Register
#define MEMCFG_O_CERRCLR         0x24U   // Correctable Error Flag Clear Register
#define MEMCFG_O_CCPUREADDR      0x26U   // Correctable CPU Read Error Address
#define MEMCFG_O_CDMAREADDR      0x28U   // Correctable DMA Read Error Address
#define MEMCFG_O_CCLA1READDR     0x2AU   // Correctable CLA1 Read Error Address
#define MEMCFG_O_CERRCNT         0x2EU   // Correctable Error Count Register
#define MEMCFG_O_CERRTHRES       0x30U   // Correctable Error Threshold Value Register
#define MEMCFG_O_CEINTFLG        0x32U   // Correctable Error Interrupt Flag Status Register
#define MEMCFG_O_CEINTCLR        0x34U   // Correctable Error Interrupt Flag Clear Register
#define MEMCFG_O_CEINTSET        0x36U   // Correctable Error Interrupt Flag Set Register
#define MEMCFG_O_CEINTEN         0x38U   // Correctable Error Interrupt Enable Register

#define MEMCFG_O_ROMWAITSTATE   0x0U   // ROM Wait State Configuration Register

#define MEMCFG_O_CPU_RAM_TEST_ERROR_STS       0x0U   // Ram Test: Error Status Register
#define MEMCFG_O_CPU_RAM_TEST_ERROR_STS_CLR   0x2U   // Ram Test: Error Status Clear Register
#define MEMCFG_O_CPU_RAM_TEST_ERROR_ADDR      0x4U   // Ram Test: Error address register


//*************************************************************************************************
//
// The following are defines for the bit fields in the DxLOCK register
//
//*************************************************************************************************
#define MEMCFG_DXLOCK_LOCK_M0        0x1U     // M0 RAM Lock bits
#define MEMCFG_DXLOCK_LOCK_M1        0x2U     // M1 RAM Lock bits
#define MEMCFG_DXLOCK_LOCK_D0        0x4U     // D0 RAM Lock bits
#define MEMCFG_DXLOCK_LOCK_D1        0x8U     // D1 RAM Lock bits
#define MEMCFG_DXLOCK_LOCK_D2        0x10U    // D2 RAM Lock bits
#define MEMCFG_DXLOCK_LOCK_D3        0x20U    // D3 RAM Lock bits
#define MEMCFG_DXLOCK_LOCK_D4        0x40U    // D4 RAM Lock bits
#define MEMCFG_DXLOCK_LOCK_D5        0x80U    // D5 RAM Lock bits
#define MEMCFG_DXLOCK_LOCK_PIEVECT   0x100U   // PIEVECT RAM Lock bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the DxCOMMIT register
//
//*************************************************************************************************
#define MEMCFG_DXCOMMIT_COMMIT_M0        0x1U     // M0 RAM Permanent Lock bits
#define MEMCFG_DXCOMMIT_COMMIT_M1        0x2U     // M1 RAM Permanent Lock bits
#define MEMCFG_DXCOMMIT_COMMIT_D0        0x4U     // D0 RAM Permanent Lock bits
#define MEMCFG_DXCOMMIT_COMMIT_D1        0x8U     // D1 RAM Permanent Lock bits
#define MEMCFG_DXCOMMIT_COMMIT_D2        0x10U    // D2 RAM Permanent Lock bits
#define MEMCFG_DXCOMMIT_COMMIT_D3        0x20U    // D3 RAM Permanent Lock bits
#define MEMCFG_DXCOMMIT_COMMIT_D4        0x40U    // D4 RAM Permanent Lock bits
#define MEMCFG_DXCOMMIT_COMMIT_D5        0x80U    // D5 RAM Permanent Lock bits
#define MEMCFG_DXCOMMIT_COMMIT_PIEVECT   0x100U   // PIEVECT RAM Permanent Lock bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the DxACCPROT0 register
//
//*************************************************************************************************
#define MEMCFG_DXACCPROT0_FETCHPROT_M0   0x1U         // Fetch Protection For M0 RAM
#define MEMCFG_DXACCPROT0_CPUWRPROT_M0   0x2U         // CPU WR Protection For M0 RAM
#define MEMCFG_DXACCPROT0_FETCHPROT_M1   0x100U       // Fetch Protection For M1 RAM
#define MEMCFG_DXACCPROT0_CPUWRPROT_M1   0x200U       // CPU WR Protection For M1 RAM
#define MEMCFG_DXACCPROT0_FETCHPROT_D0   0x10000U     // Fetch Protection For D0 RAM
#define MEMCFG_DXACCPROT0_CPUWRPROT_D0   0x20000U     // CPU WR Protection For D0 RAM
#define MEMCFG_DXACCPROT0_FETCHPROT_D1   0x1000000U   // Fetch Protection For D1 RAM
#define MEMCFG_DXACCPROT0_CPUWRPROT_D1   0x2000000U   // CPU WR Protection For D1 RAM

//*************************************************************************************************
//
// The following are defines for the bit fields in the DxACCPROT1 register
//
//*************************************************************************************************
#define MEMCFG_DXACCPROT1_FETCHPROT_D2   0x1U         // Fetch Protection For D0 RAM
#define MEMCFG_DXACCPROT1_CPUWRPROT_D2   0x2U         // CPU WR Protection For D2 RAM
#define MEMCFG_DXACCPROT1_FETCHPROT_D3   0x100U       // Fetch Protection For D3 RAM
#define MEMCFG_DXACCPROT1_CPUWRPROT_D3   0x200U       // CPU WR Protection For D3 RAM
#define MEMCFG_DXACCPROT1_FETCHPROT_D4   0x10000U     // Fetch Protection For D4 RAM
#define MEMCFG_DXACCPROT1_CPUWRPROT_D4   0x20000U     // CPU WR Protection For D4 RAM
#define MEMCFG_DXACCPROT1_FETCHPROT_D5   0x1000000U   // Fetch Protection For D5 RAM
#define MEMCFG_DXACCPROT1_CPUWRPROT_D5   0x2000000U   // CPU WR Protection For D5 RAM

//*************************************************************************************************
//
// The following are defines for the bit fields in the DxTEST register
//
//*************************************************************************************************
#define MEMCFG_DXTEST_TEST_M0_S   0U
#define MEMCFG_DXTEST_TEST_M0_M   0x3U      // Selects the different modes for M0 RAM
#define MEMCFG_DXTEST_TEST_M1_S   2U
#define MEMCFG_DXTEST_TEST_M1_M   0xCU      // Selects the different modes for M1 RAM
#define MEMCFG_DXTEST_TEST_D0_S   4U
#define MEMCFG_DXTEST_TEST_D0_M   0x30U     // Selects the different modes for D0 RAM
#define MEMCFG_DXTEST_TEST_D1_S   6U
#define MEMCFG_DXTEST_TEST_D1_M   0xC0U     // Selects the different modes for D1 RAM
#define MEMCFG_DXTEST_TEST_D2_S   8U
#define MEMCFG_DXTEST_TEST_D2_M   0x300U    // Selects the different modes for D2 RAM
#define MEMCFG_DXTEST_TEST_D3_S   10U
#define MEMCFG_DXTEST_TEST_D3_M   0xC00U    // Selects the different modes for D3 RAM
#define MEMCFG_DXTEST_TEST_D4_S   12U
#define MEMCFG_DXTEST_TEST_D4_M   0x3000U   // Selects the different modes for D4 RAM
#define MEMCFG_DXTEST_TEST_D5_S   14U
#define MEMCFG_DXTEST_TEST_D5_M   0xC000U   // Selects the different modes for D5 RAM

//*************************************************************************************************
//
// The following are defines for the bit fields in the DxINIT register
//
//*************************************************************************************************
#define MEMCFG_DXINIT_INIT_M0   0x1U    // RAM Initialization control for M0 RAM.
#define MEMCFG_DXINIT_INIT_M1   0x2U    // RAM Initialization control for M1 RAM.
#define MEMCFG_DXINIT_INIT_D0   0x4U    // RAM Initialization control for D0 RAM.
#define MEMCFG_DXINIT_INIT_D1   0x8U    // RAM Initialization control for D1 RAM.
#define MEMCFG_DXINIT_INIT_D2   0x10U   // RAM Initialization control for D2 RAM.
#define MEMCFG_DXINIT_INIT_D3   0x20U   // RAM Initialization control for D3 RAM.
#define MEMCFG_DXINIT_INIT_D4   0x40U   // RAM Initialization control for D4 RAM.
#define MEMCFG_DXINIT_INIT_D5   0x80U   // RAM Initialization control for D5 RAM.

//*************************************************************************************************
//
// The following are defines for the bit fields in the DxINITDONE register
//
//*************************************************************************************************
#define MEMCFG_DXINITDONE_INITDONE_M0   0x1U    // RAM Initialization status for M0 RAM.
#define MEMCFG_DXINITDONE_INITDONE_M1   0x2U    // RAM Initialization status for M1 RAM.
#define MEMCFG_DXINITDONE_INITDONE_D0   0x4U    // RAM Initialization status for D0 RAM.
#define MEMCFG_DXINITDONE_INITDONE_D1   0x8U    // RAM Initialization status for D1 RAM.
#define MEMCFG_DXINITDONE_INITDONE_D2   0x10U   // RAM Initialization status for D2 RAM.
#define MEMCFG_DXINITDONE_INITDONE_D3   0x20U   // RAM Initialization status for D3 RAM.
#define MEMCFG_DXINITDONE_INITDONE_D4   0x40U   // RAM Initialization status for D4 RAM.
#define MEMCFG_DXINITDONE_INITDONE_D5   0x80U   // RAM Initialization status for D5 RAM.

//*************************************************************************************************
//
// The following are defines for the bit fields in the DxRAMTEST_LOCK register
//
//*************************************************************************************************
#define MEMCFG_DXRAMTEST_LOCK_M0        0x1U          // DxTEST.TEST_M0 LOCK
#define MEMCFG_DXRAMTEST_LOCK_M1        0x2U          // DxTEST.TEST_M1 LOCK
#define MEMCFG_DXRAMTEST_LOCK_D0        0x4U          // DxTEST.TEST_D0 LOCK
#define MEMCFG_DXRAMTEST_LOCK_D1        0x8U          // DxTEST.TEST_D1 LOCK
#define MEMCFG_DXRAMTEST_LOCK_D2        0x10U         // DxTEST.TEST_D2 LOCK
#define MEMCFG_DXRAMTEST_LOCK_D3        0x20U         // DxTEST.TEST_D3 LOCK
#define MEMCFG_DXRAMTEST_LOCK_D4        0x40U         // DxTEST.TEST_D4 LOCK
#define MEMCFG_DXRAMTEST_LOCK_D5        0x80U         // DxTEST.TEST_D5 LOCK
#define MEMCFG_DXRAMTEST_LOCK_PIEVECT   0x100U        // DxTEST.TEST_PIEVECT LOCK
#define MEMCFG_DXRAMTEST_LOCK_KEY_S     16U
#define MEMCFG_DXRAMTEST_LOCK_KEY_M     0xFFFF0000U   // Key for writing DxRAMTEST_LOCK

//*************************************************************************************************
//
// The following are defines for the bit fields in the LSxLOCK register
//
//*************************************************************************************************
#define MEMCFG_LSXLOCK_LOCK_LS0   0x1U     // LS0 RAM Lock bits
#define MEMCFG_LSXLOCK_LOCK_LS1   0x2U     // LS1 RAM Lock bits
#define MEMCFG_LSXLOCK_LOCK_LS2   0x4U     // LS2 RAM Lock bits
#define MEMCFG_LSXLOCK_LOCK_LS3   0x8U     // LS3 RAM Lock bits
#define MEMCFG_LSXLOCK_LOCK_LS4   0x10U    // LS4 RAM Lock bits
#define MEMCFG_LSXLOCK_LOCK_LS5   0x20U    // LS5 RAM Lock bits
#define MEMCFG_LSXLOCK_LOCK_LS6   0x40U    // LS6 RAM Lock bits
#define MEMCFG_LSXLOCK_LOCK_LS7   0x80U    // LS7 RAM Lock bits
#define MEMCFG_LSXLOCK_LOCK_LS8   0x100U   // LS8 RAM Lock bits
#define MEMCFG_LSXLOCK_LOCK_LS9   0x200U   // LS9 RAM Lock bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the LSxCOMMIT register
//
//*************************************************************************************************
#define MEMCFG_LSXCOMMIT_COMMIT_LS0   0x1U     // LS0 RAM Permanent Lock bits
#define MEMCFG_LSXCOMMIT_COMMIT_LS1   0x2U     // LS1 RAM Permanent Lock bits
#define MEMCFG_LSXCOMMIT_COMMIT_LS2   0x4U     // LS2 RAM Permanent Lock bits
#define MEMCFG_LSXCOMMIT_COMMIT_LS3   0x8U     // LS3 RAM Permanent Lock bits
#define MEMCFG_LSXCOMMIT_COMMIT_LS4   0x10U    // LS4 RAM Permanent Lock bits
#define MEMCFG_LSXCOMMIT_COMMIT_LS5   0x20U    // LS5 RAM Permanent Lock bits
#define MEMCFG_LSXCOMMIT_COMMIT_LS6   0x40U    // LS6 RAM Permanent Lock bits
#define MEMCFG_LSXCOMMIT_COMMIT_LS7   0x80U    // LS7 RAM Permanent Lock bits
#define MEMCFG_LSXCOMMIT_COMMIT_LS8   0x100U   // LS8 RAM Permanent Lock bits
#define MEMCFG_LSXCOMMIT_COMMIT_LS9   0x200U   // LS9 RAM Permanent Lock bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the LSxMSEL register
//
//*************************************************************************************************
#define MEMCFG_LSXMSEL_MSEL_LS0_S   0U
#define MEMCFG_LSXMSEL_MSEL_LS0_M   0x3U       // Controller Select for LS0 RAM
#define MEMCFG_LSXMSEL_MSEL_LS1_S   2U
#define MEMCFG_LSXMSEL_MSEL_LS1_M   0xCU       // Controller Select for LS1 RAM
#define MEMCFG_LSXMSEL_MSEL_LS2_S   4U
#define MEMCFG_LSXMSEL_MSEL_LS2_M   0x30U      // Controller Select for LS2 RAM
#define MEMCFG_LSXMSEL_MSEL_LS3_S   6U
#define MEMCFG_LSXMSEL_MSEL_LS3_M   0xC0U      // Controller Select for LS3 RAM
#define MEMCFG_LSXMSEL_MSEL_LS4_S   8U
#define MEMCFG_LSXMSEL_MSEL_LS4_M   0x300U     // Controller Select for LS4 RAM
#define MEMCFG_LSXMSEL_MSEL_LS5_S   10U
#define MEMCFG_LSXMSEL_MSEL_LS5_M   0xC00U     // Controller Select for LS5 RAM
#define MEMCFG_LSXMSEL_MSEL_LS6_S   12U
#define MEMCFG_LSXMSEL_MSEL_LS6_M   0x3000U    // Controller Select for LS6 RAM
#define MEMCFG_LSXMSEL_MSEL_LS7_S   14U
#define MEMCFG_LSXMSEL_MSEL_LS7_M   0xC000U    // Controller Select for LS7 RAM
#define MEMCFG_LSXMSEL_MSEL_LS8_S   16U
#define MEMCFG_LSXMSEL_MSEL_LS8_M   0x30000U   // Controller Select for LS8 RAM
#define MEMCFG_LSXMSEL_MSEL_LS9_S   18U
#define MEMCFG_LSXMSEL_MSEL_LS9_M   0xC0000U   // Controller Select for LS9 RAM

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
// The following are defines for the bit fields in the LSxACCPROT2 register
//
//*************************************************************************************************
#define MEMCFG_LSXACCPROT2_FETCHPROT_LS8   0x1U     // Fetch Protection For LS8 RAM
#define MEMCFG_LSXACCPROT2_CPUWRPROT_LS8   0x2U     // CPU WR Protection For LS8 RAM
#define MEMCFG_LSXACCPROT2_FETCHPROT_LS9   0x100U   // Fetch Protection For LS9 RAM
#define MEMCFG_LSXACCPROT2_CPUWRPROT_LS9   0x200U   // CPU WR Protection For LS9 RAM

//*************************************************************************************************
//
// The following are defines for the bit fields in the LSxTEST register
//
//*************************************************************************************************
#define MEMCFG_LSXTEST_TEST_LS0_S   0U
#define MEMCFG_LSXTEST_TEST_LS0_M   0x3U       // Selects the different modes for LS0 RAM
#define MEMCFG_LSXTEST_TEST_LS1_S   2U
#define MEMCFG_LSXTEST_TEST_LS1_M   0xCU       // Selects the different modes for LS1 RAM
#define MEMCFG_LSXTEST_TEST_LS2_S   4U
#define MEMCFG_LSXTEST_TEST_LS2_M   0x30U      // Selects the different modes for LS2 RAM
#define MEMCFG_LSXTEST_TEST_LS3_S   6U
#define MEMCFG_LSXTEST_TEST_LS3_M   0xC0U      // Selects the different modes for LS3 RAM
#define MEMCFG_LSXTEST_TEST_LS4_S   8U
#define MEMCFG_LSXTEST_TEST_LS4_M   0x300U     // Selects the different modes for LS4 RAM
#define MEMCFG_LSXTEST_TEST_LS5_S   10U
#define MEMCFG_LSXTEST_TEST_LS5_M   0xC00U     // Selects the different modes for LS5 RAM
#define MEMCFG_LSXTEST_TEST_LS6_S   12U
#define MEMCFG_LSXTEST_TEST_LS6_M   0x3000U    // Selects the different modes for LS6 RAM
#define MEMCFG_LSXTEST_TEST_LS7_S   14U
#define MEMCFG_LSXTEST_TEST_LS7_M   0xC000U    // Selects the different modes for LS7 RAM
#define MEMCFG_LSXTEST_TEST_LS8_S   16U
#define MEMCFG_LSXTEST_TEST_LS8_M   0x30000U   // Selects the different modes for LS8 RAM
#define MEMCFG_LSXTEST_TEST_LS9_S   18U
#define MEMCFG_LSXTEST_TEST_LS9_M   0xC0000U   // Selects the different modes for LS9 RAM

//*************************************************************************************************
//
// The following are defines for the bit fields in the LSxINIT register
//
//*************************************************************************************************
#define MEMCFG_LSXINIT_INIT_LS0   0x1U     // RAM Initialization control for LS0 RAM.
#define MEMCFG_LSXINIT_INIT_LS1   0x2U     // RAM Initialization control for LS1 RAM.
#define MEMCFG_LSXINIT_INIT_LS2   0x4U     // RAM Initialization control for LS2 RAM.
#define MEMCFG_LSXINIT_INIT_LS3   0x8U     // RAM Initialization control for LS3 RAM.
#define MEMCFG_LSXINIT_INIT_LS4   0x10U    // RAM Initialization control for LS4 RAM.
#define MEMCFG_LSXINIT_INIT_LS5   0x20U    // RAM Initialization control for LS5 RAM.
#define MEMCFG_LSXINIT_INIT_LS6   0x40U    // RAM Initialization control for LS6 RAM.
#define MEMCFG_LSXINIT_INIT_LS7   0x80U    // RAM Initialization control for LS7 RAM.
#define MEMCFG_LSXINIT_INIT_LS8   0x100U   // RAM Initialization control for LS8 RAM.
#define MEMCFG_LSXINIT_INIT_LS9   0x200U   // RAM Initialization control for LS9 RAM.

//*************************************************************************************************
//
// The following are defines for the bit fields in the LSxINITDONE register
//
//*************************************************************************************************
#define MEMCFG_LSXINITDONE_INITDONE_LS0   0x1U     // RAM Initialization status for LS0 RAM.
#define MEMCFG_LSXINITDONE_INITDONE_LS1   0x2U     // RAM Initialization status for LS1 RAM.
#define MEMCFG_LSXINITDONE_INITDONE_LS2   0x4U     // RAM Initialization status for LS2 RAM.
#define MEMCFG_LSXINITDONE_INITDONE_LS3   0x8U     // RAM Initialization status for LS3 RAM.
#define MEMCFG_LSXINITDONE_INITDONE_LS4   0x10U    // RAM Initialization status for LS4 RAM.
#define MEMCFG_LSXINITDONE_INITDONE_LS5   0x20U    // RAM Initialization status for LS5 RAM.
#define MEMCFG_LSXINITDONE_INITDONE_LS6   0x40U    // RAM Initialization status for LS6 RAM.
#define MEMCFG_LSXINITDONE_INITDONE_LS7   0x80U    // RAM Initialization status for LS7 RAM.
#define MEMCFG_LSXINITDONE_INITDONE_LS8   0x100U   // RAM Initialization status for LS8 RAM.
#define MEMCFG_LSXINITDONE_INITDONE_LS9   0x200U   // RAM Initialization status for LS9 RAM.

//*************************************************************************************************
//
// The following are defines for the bit fields in the LSxRAMTEST_LOCK register
//
//*************************************************************************************************
#define MEMCFG_LSXRAMTEST_LOCK_LS0     0x1U          // LSxTEST.TEST_LS0 LOCK
#define MEMCFG_LSXRAMTEST_LOCK_LS1     0x2U          // LSxTEST.TEST_LS1 LOCK
#define MEMCFG_LSXRAMTEST_LOCK_LS2     0x4U          // LSxTEST.TEST_LS2 LOCK
#define MEMCFG_LSXRAMTEST_LOCK_LS3     0x8U          // LSxTEST.TEST_LS3 LOCK
#define MEMCFG_LSXRAMTEST_LOCK_LS4     0x10U         // LSxTEST.TEST_LS4 LOCK
#define MEMCFG_LSXRAMTEST_LOCK_LS5     0x20U         // LSxTEST.TEST_LS5 LOCK
#define MEMCFG_LSXRAMTEST_LOCK_LS6     0x40U         // LSxTEST.TEST_LS6 LOCK
#define MEMCFG_LSXRAMTEST_LOCK_LS7     0x80U         // LSxTEST.TEST_LS7 LOCK
#define MEMCFG_LSXRAMTEST_LOCK_LS8     0x100U        // LSxTEST.TEST_LS8 LOCK
#define MEMCFG_LSXRAMTEST_LOCK_LS9     0x200U        // LSxTEST.TEST_LS9 LOCK
#define MEMCFG_LSXRAMTEST_LOCK_KEY_S   16U
#define MEMCFG_LSXRAMTEST_LOCK_KEY_M   0xFFFF0000U   // KEY to enable write to lock

//*************************************************************************************************
//
// The following are defines for the bit fields in the GSxLOCK register
//
//*************************************************************************************************
#define MEMCFG_GSXLOCK_LOCK_GS0   0x1U    // GS0 RAM Lock bits
#define MEMCFG_GSXLOCK_LOCK_GS1   0x2U    // GS1 RAM Lock bits
#define MEMCFG_GSXLOCK_LOCK_GS2   0x4U    // GS2 RAM Lock bits
#define MEMCFG_GSXLOCK_LOCK_GS3   0x8U    // GS3 RAM Lock bits
#define MEMCFG_GSXLOCK_LOCK_GS4   0x10U   // GS4 RAM Lock bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the GSxCOMMIT register
//
//*************************************************************************************************
#define MEMCFG_GSXCOMMIT_COMMIT_GS0   0x1U    // GS0 RAM Permanent Lock bits
#define MEMCFG_GSXCOMMIT_COMMIT_GS1   0x2U    // GS1 RAM Permanent Lock bits
#define MEMCFG_GSXCOMMIT_COMMIT_GS2   0x4U    // GS2 RAM Permanent Lock bits
#define MEMCFG_GSXCOMMIT_COMMIT_GS3   0x8U    // GS3 RAM Permanent Lock bits
#define MEMCFG_GSXCOMMIT_COMMIT_GS4   0x10U   // GS4 RAM Permanent Lock bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the GSxMSEL register
//
//*************************************************************************************************
#define MEMCFG_GSXMSEL_MSEL_GS0   0x1U    // Controller Select for GS0 RAM
#define MEMCFG_GSXMSEL_MSEL_GS1   0x2U    // Controller Select for GS1 RAM
#define MEMCFG_GSXMSEL_MSEL_GS2   0x4U    // Controller Select for GS2 RAM
#define MEMCFG_GSXMSEL_MSEL_GS3   0x8U    // Controller Select for GS3 RAM
#define MEMCFG_GSXMSEL_MSEL_GS4   0x10U   // Controller Select for GS4 RAM

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
// The following are defines for the bit fields in the GSxACCPROT1 register
//
//*************************************************************************************************
#define MEMCFG_GSXACCPROT1_FETCHPROT_GS4   0x1U   // Fetch Protection For GS4 RAM
#define MEMCFG_GSXACCPROT1_CPUWRPROT_GS4   0x2U   // CPU WR Protection For GS4 RAM
#define MEMCFG_GSXACCPROT1_DMAWRPROT_GS4   0x4U   // DMA WR Protection For GS4 RAM

//*************************************************************************************************
//
// The following are defines for the bit fields in the GSxTEST register
//
//*************************************************************************************************
#define MEMCFG_GSXTEST_TEST_GS0_S   0U
#define MEMCFG_GSXTEST_TEST_GS0_M   0x3U     // Selects the different modes for GS0 RAM
#define MEMCFG_GSXTEST_TEST_GS1_S   2U
#define MEMCFG_GSXTEST_TEST_GS1_M   0xCU     // Selects the different modes for GS1 RAM
#define MEMCFG_GSXTEST_TEST_GS2_S   4U
#define MEMCFG_GSXTEST_TEST_GS2_M   0x30U    // Selects the different modes for GS2 RAM
#define MEMCFG_GSXTEST_TEST_GS3_S   6U
#define MEMCFG_GSXTEST_TEST_GS3_M   0xC0U    // Selects the different modes for GS3 RAM
#define MEMCFG_GSXTEST_TEST_GS4_S   8U
#define MEMCFG_GSXTEST_TEST_GS4_M   0x300U   // Selects the different modes for GS4 RAM

//*************************************************************************************************
//
// The following are defines for the bit fields in the GSxINIT register
//
//*************************************************************************************************
#define MEMCFG_GSXINIT_INIT_GS0   0x1U    // RAM Initialization control for GS0 RAM.
#define MEMCFG_GSXINIT_INIT_GS1   0x2U    // RAM Initialization control for GS1 RAM.
#define MEMCFG_GSXINIT_INIT_GS2   0x4U    // RAM Initialization control for GS2 RAM.
#define MEMCFG_GSXINIT_INIT_GS3   0x8U    // RAM Initialization control for GS3 RAM.
#define MEMCFG_GSXINIT_INIT_GS4   0x10U   // RAM Initialization control for GS4 RAM.

//*************************************************************************************************
//
// The following are defines for the bit fields in the GSxINITDONE register
//
//*************************************************************************************************
#define MEMCFG_GSXINITDONE_INITDONE_GS0   0x1U    // RAM Initialization status for GS0 RAM.
#define MEMCFG_GSXINITDONE_INITDONE_GS1   0x2U    // RAM Initialization status for GS1 RAM.
#define MEMCFG_GSXINITDONE_INITDONE_GS2   0x4U    // RAM Initialization status for GS2 RAM.
#define MEMCFG_GSXINITDONE_INITDONE_GS3   0x8U    // RAM Initialization status for GS3 RAM.
#define MEMCFG_GSXINITDONE_INITDONE_GS4   0x10U   // RAM Initialization status for GS4 RAM.

//*************************************************************************************************
//
// The following are defines for the bit fields in the GSxRAMTEST_LOCK register
//
//*************************************************************************************************
#define MEMCFG_GSXRAMTEST_LOCK_GS0     0x1U          // GSxTEST.TEST_GS0 LOCK
#define MEMCFG_GSXRAMTEST_LOCK_GS1     0x2U          // GSxTEST.TEST_GS1 LOCK
#define MEMCFG_GSXRAMTEST_LOCK_GS2     0x4U          // GSxTEST.TEST_GS2 LOCK
#define MEMCFG_GSXRAMTEST_LOCK_GS3     0x8U          // GSxTEST.TEST_GS3 LOCK
#define MEMCFG_GSXRAMTEST_LOCK_GS4     0x10U         // GSxTEST.TEST_GS4 LOCK
#define MEMCFG_GSXRAMTEST_LOCK_KEY_S   16U
#define MEMCFG_GSXRAMTEST_LOCK_KEY_M   0xFFFF0000U   // KEY to enable write to lock

//*************************************************************************************************
//
// The following are defines for the bit fields in the MSGxLOCK register
//
//*************************************************************************************************
#define MEMCFG_MSGXLOCK_LOCK_CPUTOCPU_MSGRAM0   0x1U    // CPUTOCPU RAM Lock bits
#define MEMCFG_MSGXLOCK_LOCK_CPUTOCLA1          0x2U    // CPUTOCLA1 RAM Lock bits
#define MEMCFG_MSGXLOCK_LOCK_CLA1TOCPU          0x4U    // CLA1TOCPU RAM Lock bits
#define MEMCFG_MSGXLOCK_LOCK_CLA1TODMA          0x20U   // CLA1TODMA RAM control fields lock bit
#define MEMCFG_MSGXLOCK_LOCK_DMATOCLA1          0x40U   // DMATOCLA1 RAM control fields lock bit
#define MEMCFG_MSGXLOCK_LOCK_CPUTOCPU_MSGRAM1   0x80U   // Lock bit of CPU to CPU MSG RAM1 control
                                                        // fields

//*************************************************************************************************
//
// The following are defines for the bit fields in the MSGxCOMMIT register
//
//*************************************************************************************************
#define MEMCFG_MSGXCOMMIT_COMMIT_CPUTOCPU           0x1U    // CPUTOCPU RAM control fields COMMIT
                                                            // bit
#define MEMCFG_MSGXCOMMIT_COMMIT_CPUTOCLA1          0x2U    // CPUTOCLA1 RAM control fields COMMIT
                                                            // bit
#define MEMCFG_MSGXCOMMIT_COMMIT_CLA1TOCPU          0x4U    // CLA1TOCPU RAM control fields COMMIT
                                                            // bit
#define MEMCFG_MSGXCOMMIT_COMMIT_CLA1TODMA          0x20U   // CLA1TODMA RAM control fields COMMIT
                                                            // bit
#define MEMCFG_MSGXCOMMIT_COMMIT_DMATOCLA1          0x40U   // DMATOCLA1 RAM control fields COMMIT
                                                            // bit
#define MEMCFG_MSGXCOMMIT_COMMIT_CPUTOCPU_MSGRAM1   0x80U   // Commint bit of CPU to CPU MSG RAM1
                                                            // control fields

//*************************************************************************************************
//
// The following are defines for the bit fields in the MSGxACCPROT0 register
//
//*************************************************************************************************
#define MEMCFG_MSGXACCPROT0_CPUWRPROT_CPUTOCPU_MSGRAM0   0x2U   // CPU WR Protection For
                                                                // CPUTOCPU_MSGRAM0 RAM
#define MEMCFG_MSGXACCPROT0_DMAWRPROT_CPUTOCPU_MSGRAM0   0x4U   // DMA WR Protection For
                                                                // CPUTOCPU_MSGRAM0 RAM

//*************************************************************************************************
//
// The following are defines for the bit fields in the MSGxTEST register
//
//*************************************************************************************************
#define MEMCFG_MSGXTEST_TEST_CPUTOCPU_MSGRAM0_S   0U
#define MEMCFG_MSGXTEST_TEST_CPUTOCPU_MSGRAM0_M   0x3U      // CPU to CPU Mode Select
#define MEMCFG_MSGXTEST_TEST_CPUTOCLA1_S          2U
#define MEMCFG_MSGXTEST_TEST_CPUTOCLA1_M          0xCU      // CPU to CLA1 MSG RAM Mode Select
#define MEMCFG_MSGXTEST_TEST_CLA1TOCPU_S          4U
#define MEMCFG_MSGXTEST_TEST_CLA1TOCPU_M          0x30U     // CLA1 to CPU MSG RAM Mode Select
#define MEMCFG_MSGXTEST_TEST_CLA1TODMA_S          10U
#define MEMCFG_MSGXTEST_TEST_CLA1TODMA_M          0xC00U    // CLA1 to DMA MSG RAM Mode Select
#define MEMCFG_MSGXTEST_TEST_DMATOCLA1_S          12U
#define MEMCFG_MSGXTEST_TEST_DMATOCLA1_M          0x3000U   // DMA to CLA1 MSG RAM Mode Select
#define MEMCFG_MSGXTEST_TEST_CPUTOCPU_MSGRAM1_S   14U
#define MEMCFG_MSGXTEST_TEST_CPUTOCPU_MSGRAM1_M   0xC000U   // CPU to CPU Mode Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the MSGxINIT register
//
//*************************************************************************************************
#define MEMCFG_MSGXINIT_INIT_CPUTOCPU_MSGRAM0   0x1U    // Initialization control for CPU to CPU
                                                        // MSG RAM
#define MEMCFG_MSGXINIT_INIT_CPUTOCLA1          0x2U    // Initialization control for CPUTOCLA1 MSG
                                                        // RAM
#define MEMCFG_MSGXINIT_INIT_CLA1TOCPU          0x4U    // Initialization control for CLA1TOCPU MSG
                                                        // RAM
#define MEMCFG_MSGXINIT_INIT_CLA1TODMA          0x20U   // Initialization control for CLA1 to DMA
                                                        // MSG RAM
#define MEMCFG_MSGXINIT_INIT_DMATOCLA1          0x40U   // Initialization control for DMA to CLA1
                                                        // MSG RAM
#define MEMCFG_MSGXINIT_INIT_CPUTOCPU_MSGRAM1   0x80U   // Initialization control for CPU to CPU
                                                        // MSG RAM1

//*************************************************************************************************
//
// The following are defines for the bit fields in the MSGxINITDONE register
//
//*************************************************************************************************
#define MEMCFG_MSGXINITDONE_INITDONE_CPUTOCPU           0x1U    // Initialization status for CPU to
                                                                // CPU MSG RAM
#define MEMCFG_MSGXINITDONE_INITDONE_CPUTOCLA1          0x2U    // Initialization status for CPU to
                                                                // CLA1 MSG RAM
#define MEMCFG_MSGXINITDONE_INITDONE_CLA1TOCPU          0x4U    // Initialization status for CLA1
                                                                // to CPU MSG RAM
#define MEMCFG_MSGXINITDONE_INITDONE_CLA1TODMA          0x20U   // Initialization status for CLA1
                                                                // to DMA MSG RAM
#define MEMCFG_MSGXINITDONE_INITDONE_DMATOCLA1          0x40U   // Initialization status for DMA to
                                                                // CLA1 MSG RAM
#define MEMCFG_MSGXINITDONE_INITDONE_CPUTOCPU_MSGRAM1   0x80U   // Initialization status for CPU to
                                                                // CPU MSG RAM1

//*************************************************************************************************
//
// The following are defines for the bit fields in the MSGxRAMTEST_LOCK register
//
//*************************************************************************************************
#define MEMCFG_MSGXRAMTEST_LOCK_CPUTOCPU           0x1U          // MSGxRAMTEST_LOCK.CPUTOCPULock
                                                                 // Configuration
#define MEMCFG_MSGXRAMTEST_LOCK_CPUTOCLA1          0x2U          // MSGxRAMTEST_LOCK.CPUTOCLA1Lock
                                                                 // Configuration
#define MEMCFG_MSGXRAMTEST_LOCK_CLA1TOCPU          0x4U          // MSGxRAMTEST_LOCK.CLA1TOCPULock
                                                                 // Configuration
#define MEMCFG_MSGXRAMTEST_LOCK_CLA1TODMA          0x20U         // MSGxRAMTEST_LOCK.CLA1TODMALock
                                                                 // Configuration
#define MEMCFG_MSGXRAMTEST_LOCK_DMATOCLA1          0x40U         // MSGxRAMTEST_LOCK.DMATOCLA1Lock
                                                                 // Configuration
#define MEMCFG_MSGXRAMTEST_LOCK_CPUTOCPU_MSGRAM1   0x80U         //
                                                                 // MSGxRAMTEST_LOCK.CPUTOCPU_MSGRAM1Lock
                                                                 // Configuration
#define MEMCFG_MSGXRAMTEST_LOCK_KEY_S              16U
#define MEMCFG_MSGXRAMTEST_LOCK_KEY_M              0xFFFF0000U   // KEY to enable write to lock

//*************************************************************************************************
//
// The following are defines for the bit fields in the ROM_LOCK register
//
//*************************************************************************************************
#define MEMCFG_ROM_LOCK_LOCK_BOOTROM      0x1U          // BOOTROM Lock bits
#define MEMCFG_ROM_LOCK_LOCK_SECUREROM    0x2U          // SECUREROM Lock bits
#define MEMCFG_ROM_LOCK_LOCK_CLADATAROM   0x4U          // CLADATAROM Lock bits
#define MEMCFG_ROM_LOCK_KEY_S             16U
#define MEMCFG_ROM_LOCK_KEY_M             0xFFFF0000U   // Key for writing ROM LOCK

//*************************************************************************************************
//
// The following are defines for the bit fields in the ROM_TEST register
//
//*************************************************************************************************
#define MEMCFG_ROM_TEST_TEST_BOOTROM_S      0U
#define MEMCFG_ROM_TEST_TEST_BOOTROM_M      0x3U    // Selects the different modes for BOOTROM
#define MEMCFG_ROM_TEST_TEST_SECUREROM_S    2U
#define MEMCFG_ROM_TEST_TEST_SECUREROM_M    0xCU    // Selects the different modes for SECUREROM
#define MEMCFG_ROM_TEST_TEST_CLADATAROM_S   4U
#define MEMCFG_ROM_TEST_TEST_CLADATAROM_M   0x30U   // Selects the different modes for CLADATAROM

//*************************************************************************************************
//
// The following are defines for the bit fields in the ROM_FORCE_ERROR register
//
//*************************************************************************************************
#define MEMCFG_ROM_FORCE_ERROR_FORCE_BOOTROM_ERROR      0x1U   // Force Bootrom Parity Error
#define MEMCFG_ROM_FORCE_ERROR_FORCE_SECUREROM_ERROR    0x2U   // Force SECUREROM Parity Error
#define MEMCFG_ROM_FORCE_ERROR_FORCE_CLADATAROM_ERROR   0x4U   // Force CLADATAROM Parity Error

//*************************************************************************************************
//
// The following are defines for the bit fields in the PERI_MEM_TEST_LOCK register
//
//*************************************************************************************************
#define MEMCFG_PERI_MEM_TEST_LOCK_LOCK_PERI_MEM_TEST_CONTROL   0x1U          //
                                                                             // PERI_MEM_TEST_CONTROL Lock bit
#define MEMCFG_PERI_MEM_TEST_LOCK_KEY_S                        16U
#define MEMCFG_PERI_MEM_TEST_LOCK_KEY_M                        0xFFFF0000U   // KEY to lock
                                                                             // Peripheral memory test

//*************************************************************************************************
//
// The following are defines for the bit fields in the PERI_MEM_TEST_CONTROL register
//
//*************************************************************************************************
#define MEMCFG_PERI_MEM_TEST_CONTROL_ETHERCAT_TEST_ENABLE       0x10U   // EtherCAT Test mode
                                                                        // enable
#define MEMCFG_PERI_MEM_TEST_CONTROL_ETHERCAT_MEM_FORCE_ERROR   0x20U   // Force Parity Error on
                                                                        // EtherCAT RAM


//*************************************************************************************************
//
// The following are defines for the bit fields in the EMIF1LOCK register
//
//*************************************************************************************************
#define MEMCFG_EMIF1LOCK_LOCK_EMIF1   0x1U   // EMIF1 access protection and controller fields lock
                                             // bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the EMIF1COMMIT register
//
//*************************************************************************************************
#define MEMCFG_EMIF1COMMIT_COMMIT_EMIF1   0x1U   // EMIF1 access protection and controller select
                                                 // permanent lock

//*************************************************************************************************
//
// The following are defines for the bit fields in the EMIF1MSEL register
//
//*************************************************************************************************
#define MEMCFG_EMIF1MSEL_MSEL_EMIF1_S   0U
#define MEMCFG_EMIF1MSEL_MSEL_EMIF1_M   0x3U          // Controller Select for EMIF1.
#define MEMCFG_EMIF1MSEL_KEY_S          4U
#define MEMCFG_EMIF1MSEL_KEY_M          0xFFFFFFF0U   // KEY to enable the write into MSEL_EMIF1
                                                      // bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the EMIF1ACCPROT0 register
//
//*************************************************************************************************
#define MEMCFG_EMIF1ACCPROT0_FETCHPROT_EMIF1   0x1U   // Fetch Protection For EMIF1
#define MEMCFG_EMIF1ACCPROT0_CPUWRPROT_EMIF1   0x2U   // CPU WR Protection For EMIF1
#define MEMCFG_EMIF1ACCPROT0_DMAWRPROT_EMIF1   0x4U   // DMA WR Protection For EMIF1


//*************************************************************************************************
//
// The following are defines for the bit fields in the NMAVFLG register
//
//*************************************************************************************************
#define MEMCFG_NMAVFLG_CPUREAD     0x1U     // Non Controller CPU Read Access Violation Flag
#define MEMCFG_NMAVFLG_CPUWRITE    0x2U     // Non Controller CPU Write Access Violation Flag
#define MEMCFG_NMAVFLG_CPUFETCH    0x4U     // Non Controller CPU Fetch Access Violation Flag
#define MEMCFG_NMAVFLG_DMAWRITE    0x8U     // Non Controller DMA Write Access Violation Flag
#define MEMCFG_NMAVFLG_CLA1READ    0x10U    // Non Controller CLA1 Read Access Violation Flag
#define MEMCFG_NMAVFLG_CLA1WRITE   0x20U    // Non Controller CLA1 Write Access Violation Flag
#define MEMCFG_NMAVFLG_CLA1FETCH   0x40U    // Non Controller CLA1 Fetch Access Violation Flag
#define MEMCFG_NMAVFLG_DMAREAD     0x400U   // Non Controller DMA Read Access Violation Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the NMAVSET register
//
//*************************************************************************************************
#define MEMCFG_NMAVSET_CPUREAD     0x1U     // Non Controller CPU Read Access Violation Flag Set
#define MEMCFG_NMAVSET_CPUWRITE    0x2U     // Non Controller CPU Write Access Violation Flag Set
#define MEMCFG_NMAVSET_CPUFETCH    0x4U     // Non Controller CPU Fetch Access Violation Flag Set
#define MEMCFG_NMAVSET_DMAWRITE    0x8U     // Non Controller DMA Write Access Violation Flag Set
#define MEMCFG_NMAVSET_CLA1READ    0x10U    // Non Controller CLA1 Read Access Violation Flag Set
#define MEMCFG_NMAVSET_CLA1WRITE   0x20U    // Non Controller CLA1 Write Access Violation Flag Set
#define MEMCFG_NMAVSET_CLA1FETCH   0x40U    // Non Controller CLA1 Fetch Access Violation Flag Set
#define MEMCFG_NMAVSET_DMAREAD     0x400U   // Non Controller DMA Read Access Violation Flag Set

//*************************************************************************************************
//
// The following are defines for the bit fields in the NMAVCLR register
//
//*************************************************************************************************
#define MEMCFG_NMAVCLR_CPUREAD     0x1U     // Non Controller CPU Read Access Violation Flag Clear
#define MEMCFG_NMAVCLR_CPUWRITE    0x2U     // Non Controller CPU Write Access Violation Flag Clear
#define MEMCFG_NMAVCLR_CPUFETCH    0x4U     // Non Controller CPU Fetch Access Violation Flag Clear
#define MEMCFG_NMAVCLR_DMAWRITE    0x8U     // Non Controller DMA Write Access Violation Flag Clear
#define MEMCFG_NMAVCLR_CLA1READ    0x10U    // Non Controller CLA1 Read Access Violation Flag Clear
#define MEMCFG_NMAVCLR_CLA1WRITE   0x20U    // Non Controller CLA1 Write Access Violation Flag
                                            // Clear
#define MEMCFG_NMAVCLR_CLA1FETCH   0x40U    // Non Controller CLA1 Fetch Access Violation Flag
                                            // Clear
#define MEMCFG_NMAVCLR_DMAREAD     0x400U   // Non Controller DMA Read Access Violation Flag Clear

//*************************************************************************************************
//
// The following are defines for the bit fields in the NMAVINTEN register
//
//*************************************************************************************************
#define MEMCFG_NMAVINTEN_CPUREAD     0x1U     // Non Controller CPU Read Access Violation Interrupt
                                              // Enable
#define MEMCFG_NMAVINTEN_CPUWRITE    0x2U     // Non Controller CPU Write Access Violation
                                              // Interrupt Enable
#define MEMCFG_NMAVINTEN_CPUFETCH    0x4U     // Non Controller CPU Fetch Access Violation
                                              // Interrupt Enable
#define MEMCFG_NMAVINTEN_DMAWRITE    0x8U     // Non Controller DMA Write Access Violation
                                              // Interrupt Enable
#define MEMCFG_NMAVINTEN_CLA1READ    0x10U    // Non Controller CLA1 Read Access Violation
                                              // Interrupt Enable
#define MEMCFG_NMAVINTEN_CLA1WRITE   0x20U    // Non Controller CLA1 Write Access Violation
                                              // Interrupt Enable
#define MEMCFG_NMAVINTEN_CLA1FETCH   0x40U    // Non Controller CLA1 Fetch Access Violation
                                              // Interrupt Enable
#define MEMCFG_NMAVINTEN_DMAREAD     0x400U   // Non Controller DMA Read Access Violation Interrupt
                                              // Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the MAVFLG register
//
//*************************************************************************************************
#define MEMCFG_MAVFLG_CPUFETCH   0x1U   // Controller CPU Fetch Access Violation Flag
#define MEMCFG_MAVFLG_CPUWRITE   0x2U   // Controller CPU Write Access Violation Flag
#define MEMCFG_MAVFLG_DMAWRITE   0x4U   // Controller DMA Write Access Violation Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the MAVSET register
//
//*************************************************************************************************
#define MEMCFG_MAVSET_CPUFETCH   0x1U   // Controller CPU Fetch Access Violation Flag Set
#define MEMCFG_MAVSET_CPUWRITE   0x2U   // Controller CPU Write Access Violation Flag Set
#define MEMCFG_MAVSET_DMAWRITE   0x4U   // Controller DMA Write Access Violation Flag Set

//*************************************************************************************************
//
// The following are defines for the bit fields in the MAVCLR register
//
//*************************************************************************************************
#define MEMCFG_MAVCLR_CPUFETCH   0x1U   // Controller CPU Fetch Access Violation Flag Clear
#define MEMCFG_MAVCLR_CPUWRITE   0x2U   // Controller CPU Write Access Violation Flag Clear
#define MEMCFG_MAVCLR_DMAWRITE   0x4U   // Controller DMA Write Access Violation Flag Clear

//*************************************************************************************************
//
// The following are defines for the bit fields in the MAVINTEN register
//
//*************************************************************************************************
#define MEMCFG_MAVINTEN_CPUFETCH   0x1U   // Controller CPU Fetch Access Violation Interrupt Enable
#define MEMCFG_MAVINTEN_CPUWRITE   0x2U   // Controller CPU Write Access Violation Interrupt Enable
#define MEMCFG_MAVINTEN_DMAWRITE   0x4U   // Controller DMA Write Access Violation Interrupt Enable


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
// The following are defines for the bit fields in the FLUCERRSTATUS register
//
//*************************************************************************************************
#define MEMCFG_FLUCERRSTATUS_UNC_ERR_L     0x1U     // Lower 64 bits Uncorrectable error occurred
#define MEMCFG_FLUCERRSTATUS_DIAG_L_FAIL   0x2U     // Diagnostics of ECC on lower 64 bits.
#define MEMCFG_FLUCERRSTATUS_UNC_ERR_H     0x100U   // Upper 64 bits Uncorrectable error occurred
#define MEMCFG_FLUCERRSTATUS_DIAG_H_FAIL   0x200U   // Diagnostics of ECC on upper 64 bits.

//*************************************************************************************************
//
// The following are defines for the bit fields in the FLCERRSTATUS register
//
//*************************************************************************************************
#define MEMCFG_FLCERRSTATUS_FAIL_0_L      0x1U          // Lower 64bits Single Bit Error Corrected
                                                        // Value 0
#define MEMCFG_FLCERRSTATUS_FAIL_1_L      0x2U          // Lower 64bits Single Bit Error Corrected
                                                        // Value 1
#define MEMCFG_FLCERRSTATUS_FAIL_0_H      0x8U          // Upper 64bits Single Bit Error Corrected
                                                        // Value 0
#define MEMCFG_FLCERRSTATUS_FAIL_1_H      0x10U         // Upper 64bits Single Bit Error Corrected
                                                        // Value 1
#define MEMCFG_FLCERRSTATUS_ERR_POS_L_S   16U
#define MEMCFG_FLCERRSTATUS_ERR_POS_L_M   0x3F0000U     // Bit Position of Single bit Error in
                                                        // lower 64 bits
#define MEMCFG_FLCERRSTATUS_ERR_TYPE_L    0x400000U     // Error Type in lower 64 bits
#define MEMCFG_FLCERRSTATUS_ERR_POS_H_S   23U
#define MEMCFG_FLCERRSTATUS_ERR_POS_H_M   0x1F800000U   // Bit Position of Single bit Error in
                                                        // upper 64 bits
#define MEMCFG_FLCERRSTATUS_ERR_TYPE_H    0x20000000U   // Error Type in upper 64 bits

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
// The following are defines for the bit fields in the CERRTHRES register
//
//*************************************************************************************************
#define MEMCFG_CERRTHRES_CERRTHRES_S   0U
#define MEMCFG_CERRTHRES_CERRTHRES_M   0xFFFFU   // Correctable error threshold.

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


//*************************************************************************************************
//
// The following are defines for the bit fields in the ROMWAITSTATE register
//
//*************************************************************************************************
#define MEMCFG_ROMWAITSTATE_WSDISABLE   0x1U   // ROM Wait State Enable/Disable Control


//*************************************************************************************************
//
// The following are defines for the bit fields in the CPU_RAM_TEST_ERROR_STS register
//
//*************************************************************************************************
#define MEMCFG_CPU_RAM_TEST_ERROR_STS_COR_ERROR   0x1U   // COR_ERROR flag
#define MEMCFG_CPU_RAM_TEST_ERROR_STS_UNC_ERROR   0x2U   // UNC_ERROR flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the CPU_RAM_TEST_ERROR_STS_CLR register
//
//*************************************************************************************************
#define MEMCFG_CPU_RAM_TEST_ERROR_STS_CLR_COR_ERROR   0x1U   // COR_ERROR flag clear bit
#define MEMCFG_CPU_RAM_TEST_ERROR_STS_CLR_UNC_ERROR   0x2U   // UNC_ERROR flag clear bit



#endif
