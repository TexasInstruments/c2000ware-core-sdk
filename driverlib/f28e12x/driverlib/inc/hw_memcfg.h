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
#define MEMCFG_O_DXLOCK            0x0U    // Dedicated RAM config Lock Register
#define MEMCFG_O_DXCOMMIT          0x2U    // Dedicated RAM config Lock Commit Register
#define MEMCFG_O_DXTEST            0x4U    // Dedicated RAM TEST Register
#define MEMCFG_O_DXINIT            0x6U    // Dedicated RAM Init Register
#define MEMCFG_O_DXINITDONE        0x8U    // Dedicated RAM InitDone Status Register
#define MEMCFG_O_DXRAMTEST_LOCK    0xAU    // Dedicated RAM TEST Lock Register
#define MEMCFG_O_GSXLOCK           0x20U   // Global Shared RAM Config Lock Register
#define MEMCFG_O_GSXCOMMIT         0x22U   // Global Shared RAM conffig Lock Commit Register
#define MEMCFG_O_GSXTEST           0x24U   // Global Shared RAM TEST Register
#define MEMCFG_O_GSXINIT           0x26U   // Global Shared RAM Init Register
#define MEMCFG_O_GSXINITDONE       0x28U   // Global Shared RAM InitDone Status Register
#define MEMCFG_O_GSXRAMTEST_LOCK   0x2AU   // Global Shared  RAM TEST Lock Register
#define MEMCFG_O_ROM_LOCK          0x30U   // Rom configuration lock register
#define MEMCFG_O_ROM_TEST          0x32U   // ROM  TEST Register
#define MEMCFG_O_ROM_FORCE_ERROR   0x34U   // ROM Force Error register

#define MEMCFG_O_UCERRFLG        0x0U    // Uncorrectable Error Flag Register
#define MEMCFG_O_UCERRSET        0x2U    // Uncorrectable Error Flag Set Register
#define MEMCFG_O_UCERRCLR        0x4U    // Uncorrectable Error Flag Clear Register
#define MEMCFG_O_UCCPUREADDR     0x6U    // Uncorrectable CPU Error Address
#define MEMCFG_O_UCDMAREADDR     0x8U    // Uncorrectable DMA Error Address
#define MEMCFG_O_FLUCERRSTATUS   0x10U   // Flash read uncorrectable ecc err status
#define MEMCFG_O_FLCERRSTATUS    0x12U   // Flash read correctable ecc err status
#define MEMCFG_O_CERRFLG         0x20U   // Correctable Error Flag Register
#define MEMCFG_O_CERRSET         0x22U   // Correctable Error Flag Set Register
#define MEMCFG_O_CERRCLR         0x24U   // Correctable Error Flag Clear Register
#define MEMCFG_O_CCPUREADDR      0x26U   // Correctable CPU  Error Address
#define MEMCFG_O_CDMAREADDR      0x28U   // Correctable DMA Error Address
#define MEMCFG_O_CERRCNT         0x30U   // Correctable Error Count Register
#define MEMCFG_O_CERRTHRES       0x32U   // Correctable Error Threshold Value Register
#define MEMCFG_O_CEINTFLG        0x34U   // Correctable Error Interrupt Flag Status Register
#define MEMCFG_O_CEINTCLR        0x36U   // Correctable Error Interrupt Flag Clear Register
#define MEMCFG_O_CEINTSET        0x38U   // Correctable Error Interrupt Flag Set Register
#define MEMCFG_O_CEINTEN         0x3AU   // Correctable Error Interrupt Enable Register

#define MEMCFG_O_ROMWAITSTATE   0x0U   // ROM Wait State Configuration Register

#define MEMCFG_O_CPU_RAM_TEST_ERROR_STS       0x0U   // Ram Test: Error Status Register
#define MEMCFG_O_CPU_RAM_TEST_ERROR_STS_CLR   0x2U   // Ram Test: Error Status Clear Register
#define MEMCFG_O_CPU_RAM_TEST_ERROR_ADDR      0x4U   // Ram Test: Error address register


//*************************************************************************************************
//
// The following are defines for the bit fields in the DxLOCK register
//
//*************************************************************************************************
#define MEMCFG_DXLOCK_LOCK_M0        0x1U   // M0 RAM Lock bits
#define MEMCFG_DXLOCK_LOCK_M1        0x2U   // M1 RAM Lock bits
#define MEMCFG_DXLOCK_LOCK_PIEVECT   0x4U   // PIEVECT RAM Lock bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the DxCOMMIT register
//
//*************************************************************************************************
#define MEMCFG_DXCOMMIT_COMMIT_M0        0x1U   // M0 RAM Permanent Lock bits
#define MEMCFG_DXCOMMIT_COMMIT_M1        0x2U   // M1 RAM Permanent Lock bits
#define MEMCFG_DXCOMMIT_COMMIT_PIEVECT   0x4U   // PIEVECT RAM Permanent Lock bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the DxTEST register
//
//*************************************************************************************************
#define MEMCFG_DXTEST_TEST_M0_S        0U
#define MEMCFG_DXTEST_TEST_M0_M        0x3U    // Selects the different modes for M0 RAM
#define MEMCFG_DXTEST_TEST_M1_S        2U
#define MEMCFG_DXTEST_TEST_M1_M        0xCU    // Selects the different modes for M1 RAM
#define MEMCFG_DXTEST_TEST_PIEVECT_S   4U
#define MEMCFG_DXTEST_TEST_PIEVECT_M   0x30U   // Selects the different modes for PIEVECT RAM

//*************************************************************************************************
//
// The following are defines for the bit fields in the DxINIT register
//
//*************************************************************************************************
#define MEMCFG_DXINIT_INIT_M0        0x1U   // RAM Initialization control for M0 RAM.
#define MEMCFG_DXINIT_INIT_M1        0x2U   // RAM Initialization control for M1 RAM.
#define MEMCFG_DXINIT_INIT_PIEVECT   0x4U   // RAM Initialization control for PIEVECT RAM.

//*************************************************************************************************
//
// The following are defines for the bit fields in the DxINITDONE register
//
//*************************************************************************************************
#define MEMCFG_DXINITDONE_INITDONE_M0        0x1U   // RAM Initialization status for M0 RAM.
#define MEMCFG_DXINITDONE_INITDONE_M1        0x2U   // RAM Initialization status for M1 RAM.
#define MEMCFG_DXINITDONE_INITDONE_PIEVECT   0x4U   // RAM Initialization status for PIEVECT RAM.

//*************************************************************************************************
//
// The following are defines for the bit fields in the DxRAMTEST_LOCK register
//
//*************************************************************************************************
#define MEMCFG_DXRAMTEST_LOCK_M0_TEST        0x1U          // M0_TEST_LOCK
#define MEMCFG_DXRAMTEST_LOCK_M1_TEST        0x2U          // M1_TEST_LOCK
#define MEMCFG_DXRAMTEST_LOCK_PIEVECT_TEST   0x4U          // PIEVECT_TEST_LOCK
#define MEMCFG_DXRAMTEST_LOCK_KEY_S          16U
#define MEMCFG_DXRAMTEST_LOCK_KEY_M          0xFFFF0000U   // Key for writing DxRAMTEST lock

//*************************************************************************************************
//
// The following are defines for the bit fields in the GSxLOCK register
//
//*************************************************************************************************
#define MEMCFG_GSXLOCK_LOCK_GS0   0x1U   // GS0 RAM Lock bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the GSxCOMMIT register
//
//*************************************************************************************************
#define MEMCFG_GSXCOMMIT_COMMIT_GS0   0x1U   // GS0 RAM Permanent Lock bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the GSxTEST register
//
//*************************************************************************************************
#define MEMCFG_GSXTEST_TEST_GS0_S   0U
#define MEMCFG_GSXTEST_TEST_GS0_M   0x3U   // Selects the different modes for GS0 RAM

//*************************************************************************************************
//
// The following are defines for the bit fields in the GSxINIT register
//
//*************************************************************************************************
#define MEMCFG_GSXINIT_INIT_GS0   0x1U   // RAM Initialization control for GS0 RAM.

//*************************************************************************************************
//
// The following are defines for the bit fields in the GSxINITDONE register
//
//*************************************************************************************************
#define MEMCFG_GSXINITDONE_INITDONE_GS0   0x1U   // RAM Initialization status for GS0 RAM.

//*************************************************************************************************
//
// The following are defines for the bit fields in the GSxRAMTEST_LOCK register
//
//*************************************************************************************************
#define MEMCFG_GSXRAMTEST_LOCK_GS0_TEST   0x1U          // GS0_TEST_LOCK
#define MEMCFG_GSXRAMTEST_LOCK_KEY_S      16U
#define MEMCFG_GSXRAMTEST_LOCK_KEY_M      0xFFFF0000U   // Key for writing GSxRAMTEST lock

//*************************************************************************************************
//
// The following are defines for the bit fields in the ROM_LOCK register
//
//*************************************************************************************************
#define MEMCFG_ROM_LOCK_LOCK_BOOTROM_SECUREROM   0x1U          //  BOOTROM and SECURE ROM lock bits
#define MEMCFG_ROM_LOCK_KEY_S                    16U
#define MEMCFG_ROM_LOCK_KEY_M                    0xFFFF0000U   // Key for writing ROM LOCK

//*************************************************************************************************
//
// The following are defines for the bit fields in the ROM_TEST register
//
//*************************************************************************************************
#define MEMCFG_ROM_TEST_TEST_BOOTROM_SECUREROM_S   0U
#define MEMCFG_ROM_TEST_TEST_BOOTROM_SECUREROM_M   0x3U   // Selects the different modes for
                                                          // BOOTROM and SECURE ROM

//*************************************************************************************************
//
// The following are defines for the bit fields in the ROM_FORCE_ERROR register
//
//*************************************************************************************************
#define MEMCFG_ROM_FORCE_ERROR_FORCE_BOOTROM_SECUREROM_ERROR   0x1U   // Force Bootrom_SECUREROM
                                                                      // Parity Error


//*************************************************************************************************
//
// The following are defines for the bit fields in the UCERRFLG register
//
//*************************************************************************************************
#define MEMCFG_UCERRFLG_CPU_READ_ERR   0x1U   // CPU  Uncorrectable Read Error Flag
#define MEMCFG_UCERRFLG_DMA_READ_ERR   0x2U   // DMA  Uncorrectable Read Error Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the UCERRSET register
//
//*************************************************************************************************
#define MEMCFG_UCERRSET_CPU_READ_ERR   0x1U   // CPU  Uncorrectable Read Error Flag  set
#define MEMCFG_UCERRSET_DMA_READ_ERR   0x2U   // DMA  Uncorrectable Read Error Flag set

//*************************************************************************************************
//
// The following are defines for the bit fields in the UCERRCLR register
//
//*************************************************************************************************
#define MEMCFG_UCERRCLR_CPU_READ_ERR   0x1U   // CPU  Uncorrectable Read Error Flag  clear
#define MEMCFG_UCERRCLR_DMA_READ_ERR   0x2U   // DMA  Uncorrectable Read Error Flag clear

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
#define MEMCFG_CERRFLG_CPU_READ_ERR   0x1U   // CPU  correctable Read Error Flag
#define MEMCFG_CERRFLG_DMA_READ_ERR   0x2U   // DMA  correctable Read Error Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the CERRSET register
//
//*************************************************************************************************
#define MEMCFG_CERRSET_CPU_READ_ERR_SET   0x1U   // CPU  correctable Read Error Flag  set
#define MEMCFG_CERRSET_DMA_READ_ERR_SET   0x2U   // DMA  correctable Read Error Flag set

//*************************************************************************************************
//
// The following are defines for the bit fields in the CERRCLR register
//
//*************************************************************************************************
#define MEMCFG_CERRCLR_CPU_READ_ERR_CLR   0x1U   // CPU correctable Read Error Flag  clear
#define MEMCFG_CERRCLR_DMA_READ_ERR_CLR   0x2U   // DMA  correctable Read Error Flag clear

//*************************************************************************************************
//
// The following are defines for the bit fields in the CERRTHRES register
//
//*************************************************************************************************
#define MEMCFG_CERRTHRES_CERRTHRES_S   0U
#define MEMCFG_CERRTHRES_CERRTHRES_M   0xFFFFU   // Correctable error threshold

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
#define MEMCFG_CEINTCLR_CEINTCLR   0x1U   // Total corrected error count exceeded flag clear

//*************************************************************************************************
//
// The following are defines for the bit fields in the CEINTSET register
//
//*************************************************************************************************
#define MEMCFG_CEINTSET_CEINTSET   0x1U   // Total corrected error count exceeded flag set

//*************************************************************************************************
//
// The following are defines for the bit fields in the CEINTEN register
//
//*************************************************************************************************
#define MEMCFG_CEINTEN_CEINTEN   0x1U   // Total corrected error count exceeded flag enable


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
#define MEMCFG_CPU_RAM_TEST_ERROR_STS_UNC_ERROR   0x2U   // UNC_ERROR flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the CPU_RAM_TEST_ERROR_STS_CLR register
//
//*************************************************************************************************
#define MEMCFG_CPU_RAM_TEST_ERROR_STS_CLR_UNC_ERROR   0x2U   // UNC_ERROR flag clear bit



#endif
