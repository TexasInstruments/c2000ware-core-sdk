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
#define MEMCFG_O_DXLOCK            0x0U    // Dedicated RAM Config Lock Register
#define MEMCFG_O_DXCOMMIT          0x2U    // Dedicated RAM Config Lock Commit Register
#define MEMCFG_O_DXACCPROT0        0x8U    // Dedicated RAM Config Register
#define MEMCFG_O_DXACCPROT1        0xAU    // Dedicated RAM Config Register
#define MEMCFG_O_DXTEST            0x10U   // Dedicated RAM TEST Register
#define MEMCFG_O_DXINIT            0x12U   // Dedicated RAM Init Register
#define MEMCFG_O_DXINITDONE        0x14U   // Dedicated RAM InitDone Status Register
#define MEMCFG_O_DXRAMTEST_LOCK    0x16U   // Lock register to Dx RAM TEST registers
#define MEMCFG_O_LSXLOCK           0x20U   // Local Shared RAM Config Lock Register
#define MEMCFG_O_LSXCOMMIT         0x22U   // Local Shared RAM Config Lock Commit Register
#define MEMCFG_O_LSXACCPROT0       0x28U   // Local Shared RAM Config Register 0
#define MEMCFG_O_LSXTEST           0x30U   // Local Shared RAM TEST Register
#define MEMCFG_O_LSXINIT           0x32U   // Local Shared RAM Init Register
#define MEMCFG_O_LSXINITDONE       0x34U   // Local Shared RAM InitDone Status Register
#define MEMCFG_O_LSXRAMTEST_LOCK   0x36U   // Lock register to LSx RAM TEST registers
#define MEMCFG_O_ROM_LOCK          0xA0U   // ROM Config Lock Register
#define MEMCFG_O_ROM_TEST          0xA2U   // ROM  TEST Register
#define MEMCFG_O_ROM_FORCE_ERROR   0xA4U   // ROM Force Error register

#define MEMCFG_O_MAVFLG         0x20U   // Master Access Violation Flag Register
#define MEMCFG_O_MAVSET         0x22U   // Master Access Violation Flag Set Register
#define MEMCFG_O_MAVCLR         0x24U   // Master Access Violation Flag Clear Register
#define MEMCFG_O_MAVINTEN       0x26U   // Master Access Violation Interrupt Enable Register
#define MEMCFG_O_MCPUFAVADDR    0x28U   // Master CPU Fetch Access Violation Address
#define MEMCFG_O_MCPUWRAVADDR   0x2AU   // Master CPU Write Access Violation Address

#define MEMCFG_O_UCERRFLG        0x0U    // Uncorrectable Error Flag Register
#define MEMCFG_O_UCERRSET        0x2U    // Uncorrectable Error Flag Set Register
#define MEMCFG_O_UCERRCLR        0x4U    // Uncorrectable Error Flag Clear Register
#define MEMCFG_O_UCCPUREADDR     0x6U    // Uncorrectable CPU Read Error Address
#define MEMCFG_O_FLUCERRSTATUS   0x1CU   // Flash read uncorrectable ecc err status
#define MEMCFG_O_FLCERRSTATUS    0x1EU   // Flash read correctable ecc err status
#define MEMCFG_O_CERRFLG         0x20U   // Correctable Error Flag Register
#define MEMCFG_O_CERRSET         0x22U   // Correctable Error Flag Set Register
#define MEMCFG_O_CERRCLR         0x24U   // Correctable Error Flag Clear Register
#define MEMCFG_O_CCPUREADDR      0x26U   // Correctable CPU Read Error Address
#define MEMCFG_O_CERRCNT         0x2EU   // Correctable Error Count Register
#define MEMCFG_O_CERRTHRES       0x30U   // Correctable Error Threshold Value Register
#define MEMCFG_O_CEINTFLG        0x32U   // Correctable Error Interrupt Flag Status Register
#define MEMCFG_O_CEINTCLR        0x34U   // Correctable Error Interrupt Flag Clear Register
#define MEMCFG_O_CEINTSET        0x36U   // Correctable Error Interrupt Flag Set Register
#define MEMCFG_O_CEINTEN         0x38U   // Correctable Error Interrupt Enable Register

#define MEMCFG_O_CPU_RAM_TEST_ERROR_STS       0x0U   // Ram Test: Error Status Register
#define MEMCFG_O_CPU_RAM_TEST_ERROR_STS_CLR   0x2U   // Ram Test: Error Status Clear Register
#define MEMCFG_O_CPU_RAM_TEST_ERROR_ADDR      0x4U   // Ram Test: Error address register


//*************************************************************************************************
//
// The following are defines for the bit fields in the DxLOCK register
//
//*************************************************************************************************
#define MEMCFG_DXLOCK_LOCK_M0        0x1U    // M0 RAM Lock bits
#define MEMCFG_DXLOCK_LOCK_M1        0x2U    // M1 RAM Lock bits
#define MEMCFG_DXLOCK_LOCK_PIEVECT   0x10U   // PIEVECT RAM Lock bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the DxCOMMIT register
//
//*************************************************************************************************
#define MEMCFG_DXCOMMIT_COMMIT_M0        0x1U    // M0 RAM Permanent Lock bits
#define MEMCFG_DXCOMMIT_COMMIT_M1        0x2U    // M1 RAM Permanent Lock bits
#define MEMCFG_DXCOMMIT_COMMIT_PIEVECT   0x10U   // PIEVECT RAM Permanent Lock bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the DxACCPROT0 register
//
//*************************************************************************************************
#define MEMCFG_DXACCPROT0_FETCHPROT_M0   0x1U     // Fetch Protection For M0 RAM
#define MEMCFG_DXACCPROT0_CPUWRPROT_M0   0x2U     // CPU WR Protection For M0 RAM
#define MEMCFG_DXACCPROT0_FETCHPROT_M1   0x100U   // Fetch Protection For M1 RAM
#define MEMCFG_DXACCPROT0_CPUWRPROT_M1   0x200U   // CPU WR Protection For M1 RAM

//*************************************************************************************************
//
// The following are defines for the bit fields in the DxACCPROT1 register
//
//*************************************************************************************************
#define MEMCFG_DXACCPROT1_CPUWRPROT_PIEVECT   0x2U   // CPU WR Protection For PIEVECT RAM

//*************************************************************************************************
//
// The following are defines for the bit fields in the DxTEST register
//
//*************************************************************************************************
#define MEMCFG_DXTEST_TEST_M0_S        0U
#define MEMCFG_DXTEST_TEST_M0_M        0x3U     // Selects the different modes for M0 RAM
#define MEMCFG_DXTEST_TEST_M1_S        2U
#define MEMCFG_DXTEST_TEST_M1_M        0xCU     // Selects the different modes for M1 RAM
#define MEMCFG_DXTEST_TEST_PIEVECT_S   8U
#define MEMCFG_DXTEST_TEST_PIEVECT_M   0x300U   // Selects the different modes for PIEVECT RAM

//*************************************************************************************************
//
// The following are defines for the bit fields in the DxINIT register
//
//*************************************************************************************************
#define MEMCFG_DXINIT_INIT_M0        0x1U    // RAM Initialization control for M0 RAM.
#define MEMCFG_DXINIT_INIT_M1        0x2U    // RAM Initialization control for M1 RAM.
#define MEMCFG_DXINIT_INIT_PIEVECT   0x10U   // RAM Initialization control for PIEVECT RAM.

//*************************************************************************************************
//
// The following are defines for the bit fields in the DxINITDONE register
//
//*************************************************************************************************
#define MEMCFG_DXINITDONE_INITDONE_M0        0x1U    // RAM Initialization status for M0 RAM.
#define MEMCFG_DXINITDONE_INITDONE_M1        0x2U    // RAM Initialization status for M1 RAM.
#define MEMCFG_DXINITDONE_INITDONE_PIEVECT   0x10U   // RAM Initialization status for PIEVECT RAM.

//*************************************************************************************************
//
// The following are defines for the bit fields in the DxRAMTEST_LOCK register
//
//*************************************************************************************************
#define MEMCFG_DXRAMTEST_LOCK_M0        0x1U          // DxTEST.TEST_M0 LOCK
#define MEMCFG_DXRAMTEST_LOCK_M1        0x2U          // DxTEST.TEST_M1 LOCK
#define MEMCFG_DXRAMTEST_LOCK_PIEVECT   0x10U         // DxTEST.TEST_PIEVECT LOCK
#define MEMCFG_DXRAMTEST_LOCK_KEY_S     16U
#define MEMCFG_DXRAMTEST_LOCK_KEY_M     0xFFFF0000U   // Key for writing DxRAMTEST_LOCK

//*************************************************************************************************
//
// The following are defines for the bit fields in the LSxLOCK register
//
//*************************************************************************************************
#define MEMCFG_LSXLOCK_LOCK_LS0   0x1U   // LS0 RAM Lock bits
#define MEMCFG_LSXLOCK_LOCK_LS1   0x2U   // LS1 RAM Lock bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the LSxCOMMIT register
//
//*************************************************************************************************
#define MEMCFG_LSXCOMMIT_COMMIT_LS0   0x1U   // LS0 RAM Permanent Lock bits
#define MEMCFG_LSXCOMMIT_COMMIT_LS1   0x2U   // LS1 RAM Permanent Lock bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the LSxACCPROT0 register
//
//*************************************************************************************************
#define MEMCFG_LSXACCPROT0_FETCHPROT_LS0   0x1U     // Fetch Protection For LS0 RAM
#define MEMCFG_LSXACCPROT0_CPUWRPROT_LS0   0x2U     // CPU WR Protection For LS0 RAM
#define MEMCFG_LSXACCPROT0_FETCHPROT_LS1   0x100U   // Fetch Protection For LS1 RAM
#define MEMCFG_LSXACCPROT0_CPUWRPROT_LS1   0x200U   // CPU WR Protection For LS1 RAM

//*************************************************************************************************
//
// The following are defines for the bit fields in the LSxTEST register
//
//*************************************************************************************************
#define MEMCFG_LSXTEST_TEST_LS0_S   0U
#define MEMCFG_LSXTEST_TEST_LS0_M   0x3U   // Selects the different modes for LS0 RAM
#define MEMCFG_LSXTEST_TEST_LS1_S   2U
#define MEMCFG_LSXTEST_TEST_LS1_M   0xCU   // Selects the different modes for LS1 RAM

//*************************************************************************************************
//
// The following are defines for the bit fields in the LSxINIT register
//
//*************************************************************************************************
#define MEMCFG_LSXINIT_INIT_LS0   0x1U   // RAM Initialization control for LS0 RAM.
#define MEMCFG_LSXINIT_INIT_LS1   0x2U   // RAM Initialization control for LS1 RAM.

//*************************************************************************************************
//
// The following are defines for the bit fields in the LSxINITDONE register
//
//*************************************************************************************************
#define MEMCFG_LSXINITDONE_INITDONE_LS0   0x1U   // RAM Initialization status for LS0 RAM.
#define MEMCFG_LSXINITDONE_INITDONE_LS1   0x2U   // RAM Initialization status for LS1 RAM.

//*************************************************************************************************
//
// The following are defines for the bit fields in the LSxRAMTEST_LOCK register
//
//*************************************************************************************************
#define MEMCFG_LSXRAMTEST_LOCK_LS0     0x1U          // LSxTEST.TEST_LS0 LOCK
#define MEMCFG_LSXRAMTEST_LOCK_LS1     0x2U          // LSxTEST.TEST_LS1 LOCK
#define MEMCFG_LSXRAMTEST_LOCK_KEY_S   16U
#define MEMCFG_LSXRAMTEST_LOCK_KEY_M   0xFFFF0000U   // KEY to enable write to lock

//*************************************************************************************************
//
// The following are defines for the bit fields in the ROM_LOCK register
//
//*************************************************************************************************
#define MEMCFG_ROM_LOCK_LOCK_BOOTROM   0x1U          // BOOTROM Lock bits
#define MEMCFG_ROM_LOCK_KEY_S          16U
#define MEMCFG_ROM_LOCK_KEY_M          0xFFFF0000U   // Key for writing ROM LOCK

//*************************************************************************************************
//
// The following are defines for the bit fields in the ROM_TEST register
//
//*************************************************************************************************
#define MEMCFG_ROM_TEST_TEST_BOOTROM_S   0U
#define MEMCFG_ROM_TEST_TEST_BOOTROM_M   0x3U   // Selects the different modes for BOOTROM

//*************************************************************************************************
//
// The following are defines for the bit fields in the ROM_FORCE_ERROR register
//
//*************************************************************************************************
#define MEMCFG_ROM_FORCE_ERROR_FORCE_BOOTROM_ERROR   0x1U   // Force Bootrom Parity Error


//*************************************************************************************************
//
// The following are defines for the bit fields in the MAVFLG register
//
//*************************************************************************************************
#define MEMCFG_MAVFLG_CPUFETCH   0x1U   // Master CPU Fetch Access Violation Flag
#define MEMCFG_MAVFLG_CPUWRITE   0x2U   // Master CPU Write Access Violation Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the MAVSET register
//
//*************************************************************************************************
#define MEMCFG_MAVSET_CPUFETCH   0x1U   // Master CPU Fetch Access Violation Flag Set
#define MEMCFG_MAVSET_CPUWRITE   0x2U   // Master CPU Write Access Violation Flag Set

//*************************************************************************************************
//
// The following are defines for the bit fields in the MAVCLR register
//
//*************************************************************************************************
#define MEMCFG_MAVCLR_CPUFETCH   0x1U   // Master CPU Fetch Access Violation Flag Clear
#define MEMCFG_MAVCLR_CPUWRITE   0x2U   // Master CPU Write Access Violation Flag Clear

//*************************************************************************************************
//
// The following are defines for the bit fields in the MAVINTEN register
//
//*************************************************************************************************
#define MEMCFG_MAVINTEN_CPUFETCH   0x1U   // Master CPU Fetch Access Violation Interrupt Enable
#define MEMCFG_MAVINTEN_CPUWRITE   0x2U   // Master CPU Write Access Violation Interrupt Enable


//*************************************************************************************************
//
// The following are defines for the bit fields in the UCERRFLG register
//
//*************************************************************************************************
#define MEMCFG_UCERRFLG_CPURDERR   0x1U   // CPU Uncorrectable Read Error Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the UCERRSET register
//
//*************************************************************************************************
#define MEMCFG_UCERRSET_CPURDERR   0x1U   // CPU Uncorrectable Read Error Flag Set

//*************************************************************************************************
//
// The following are defines for the bit fields in the UCERRCLR register
//
//*************************************************************************************************
#define MEMCFG_UCERRCLR_CPURDERR   0x1U   // CPU Uncorrectable Read Error Flag Clear

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
#define MEMCFG_CERRFLG_CPURDERR   0x1U   // CPU Correctable Read Error Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the CERRSET register
//
//*************************************************************************************************
#define MEMCFG_CERRSET_CPURDERR   0x1U   // CPU Correctable Read Error Flag Set

//*************************************************************************************************
//
// The following are defines for the bit fields in the CERRCLR register
//
//*************************************************************************************************
#define MEMCFG_CERRCLR_CPURDERR   0x1U   // CPU Correctable Read Error Flag Clear

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
