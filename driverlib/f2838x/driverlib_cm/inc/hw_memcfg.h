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
#define MEMCFG_O_CXLOCK                  0x0U    // C RAM Config Lock Register
#define MEMCFG_O_CXTEST                  0x4U    // C RAM TEST Register
#define MEMCFG_O_CXINIT                  0x8U    // C RAM Init Register
#define MEMCFG_O_CXINITDONE              0xCU    // C RAM Initialization Status Register
#define MEMCFG_O_CMMSGXLOCK              0x20U   // CM Messae RAM Config Lock Register
#define MEMCFG_O_CMMSGXTEST              0x24U   // CM Messae  RAM TEST Register
#define MEMCFG_O_CMMSGXINIT              0x28U   // CM Messae  RAM Init Register
#define MEMCFG_O_CMMSGXINITDONE          0x2CU   // CM Messae  RAM Initialization Status Register
#define MEMCFG_O_SXGROUP1_LOCK           0x40U   // Group1 S and E RAM Config Lock Register
#define MEMCFG_O_SXGROUP1_TEST           0x44U   // Group1 S and E  RAM TEST Register
#define MEMCFG_O_SXGROUP1_INIT           0x48U   // Group1 S and E  RAM Init Register
#define MEMCFG_O_SXGROUP1_INITDONE       0x4CU   // Group1 S and E  RAM Initialization Status
                                                 // Register
#define MEMCFG_O_ROM_LOCK                0x80U   // ROM Config Lock Register
#define MEMCFG_O_ROM_TEST                0x84U   // ROM  TEST Register
#define MEMCFG_O_ROM_FORCE_ERROR         0x88U   // ROM Force Error register
#define MEMCFG_O_PERI_MEM_TEST_LOCK      0xA0U   // Peripheral Memory Test Lock Register
#define MEMCFG_O_PERI_MEM_TEST_CONTROL   0xA4U   // Peripheral Memory Test control Register

#define MEMCFG_O_UCERRFLG              0x0U    // Uncorrectable Error Flag Register
#define MEMCFG_O_UCERRSET              0x4U    // Uncorrectable Error Flag Set Register
#define MEMCFG_O_UCERRCLR              0x8U    // Uncorrectable Error Flag Clear Register
#define MEMCFG_O_UCM4EADDR             0xCU    // Uncorrectable M4 Error Address
#define MEMCFG_O_UCEMACEADDR           0x10U   // Uncorrectable EMAC Error Address
#define MEMCFG_O_UCUDMAEADDR           0x14U   // Uncorrectable uDMA Error Address
#define MEMCFG_O_UCETHERCATMEMREADDR   0x18U   // Uncorrectable EtherCAT IP RAM Read Error Address
#define MEMCFG_O_UCEMACMEMREADDR       0x1CU   // Uncorrectable EMAC IP RAM Read Error Address
#define MEMCFG_O_BUSFAULTFLG           0x50U   // BusFault Flag register
#define MEMCFG_O_BUSFAULTCLR           0x54U   // BusFault Flag clear register
#define MEMCFG_O_M4BUSFAULTADDR        0x58U   // M4 busfault address
#define MEMCFG_O_UDMABUSFAULTADDR      0x5CU   // uDMA busfault address
#define MEMCFG_O_EMACBUSFAULTADDR      0x60U   // EMAC busfault address
#define MEMCFG_O_CERRFLG               0x80U   // Correctable Error Flag Register
#define MEMCFG_O_CERRSET               0x84U   // Correctable Error Flag Set Register
#define MEMCFG_O_CERRCLR               0x88U   // Correctable Error Flag Clear Register
#define MEMCFG_O_CM4EADDR              0x8CU   // Correctable M4 Error Address
#define MEMCFG_O_CEMACEADDR            0x90U   // Correctable EMAC Error Address
#define MEMCFG_O_CUDMAEADDR            0x94U   // Correctable uDMA Error Address
#define MEMCFG_O_CERRCNT               0xC0U   // Correctable Error Count Register
#define MEMCFG_O_CERRTHRES             0xC4U   // Correctable Error Threshold Value Register
#define MEMCFG_O_CEINTFLG              0xC8U   // Correctable Error Interrupt Flag Status Register
#define MEMCFG_O_CEINTSET              0xCCU   // Correctable Error Interrupt Flag Set Register
#define MEMCFG_O_CEINTCLR              0xD0U   // Correctable Error Interrupt Flag Clear Register
#define MEMCFG_O_CEINTEN               0xD4U   // Correctable Error Interrupt Enable Register

#define MEMCFG_O_DIAGERRFLG    0x0U   // Error Flag Register
#define MEMCFG_O_DIAGERRCLR    0x8U   // Error Flag Clear Register
#define MEMCFG_O_DIAGERRADDR   0xCU   // Read Error Address


//*************************************************************************************************
//
// The following are defines for the bit fields in the CxLOCK register
//
//*************************************************************************************************
#define MEMCFG_CXLOCK_LOCK_C0   0x1U   // C0 RAM Lock bits
#define MEMCFG_CXLOCK_LOCK_C1   0x2U   // C1 RAM Lock bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the CxTEST register
//
//*************************************************************************************************
#define MEMCFG_CXTEST_TEST_C0_S   0U
#define MEMCFG_CXTEST_TEST_C0_M   0x3U   // Selects the different modes for C0 RAM
#define MEMCFG_CXTEST_TEST_C1_S   2U
#define MEMCFG_CXTEST_TEST_C1_M   0xCU   // Selects the different modes for C1 RAM

//*************************************************************************************************
//
// The following are defines for the bit fields in the CxINIT register
//
//*************************************************************************************************
#define MEMCFG_CXINIT_INIT_C0   0x1U   // RAM Initialization control for C0 RAM.
#define MEMCFG_CXINIT_INIT_C1   0x2U   // RAM Initialization control for C1 RAM.

//*************************************************************************************************
//
// The following are defines for the bit fields in the CxINITDONE register
//
//*************************************************************************************************
#define MEMCFG_CXINITDONE_INITDONE_C0   0x1U   // RAM Initialization status for C0 RAM.
#define MEMCFG_CXINITDONE_INITDONE_C1   0x2U   // RAM Initialization status for C1 RAM.

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMMSGxLOCK register
//
//*************************************************************************************************
#define MEMCFG_CMMSGXLOCK_LOCK_CMTOCPU1MSGRAM0   0x1U   // Message RAM CMTOCPU1MSGRAM0 Lock bits
#define MEMCFG_CMMSGXLOCK_LOCK_CMTOCPU1MSGRAM1   0x2U   // Message RAM CMTOCPU1MSGRAM1 Lock bits
#define MEMCFG_CMMSGXLOCK_LOCK_CMTOCPU2MSGRAM0   0x4U   // Message RAM CMTOCPU2MSGRAM0 Lock bits
#define MEMCFG_CMMSGXLOCK_LOCK_CMTOCPU2MSGRAM1   0x8U   // Message RAM CMTOCPU2MSGRAM1 Lock bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMMSGxTEST register
//
//*************************************************************************************************
#define MEMCFG_CMMSGXTEST_TEST_CMTOCPU1MSGRAM0_S   0U
#define MEMCFG_CMMSGXTEST_TEST_CMTOCPU1MSGRAM0_M   0x3U    // Selects the different modes for
                                                           // Message RAM CMTOCPU1MSGRAM0
#define MEMCFG_CMMSGXTEST_TEST_CMTOCPU1MSGRAM1_S   2U
#define MEMCFG_CMMSGXTEST_TEST_CMTOCPU1MSGRAM1_M   0xCU    // Selects the different modes for
                                                           // Message RAM CMTOCPU1MSGRAM1
#define MEMCFG_CMMSGXTEST_TEST_CMTOCPU2MSGRAM0_S   4U
#define MEMCFG_CMMSGXTEST_TEST_CMTOCPU2MSGRAM0_M   0x30U   // Selects the different modes for
                                                           // Message RAM CMTOCPU2MSGRAM0
#define MEMCFG_CMMSGXTEST_TEST_CMTOCPU2MSGRAM1_S   6U
#define MEMCFG_CMMSGXTEST_TEST_CMTOCPU2MSGRAM1_M   0xC0U   // Selects the different modes for
                                                           // Message RAM CMTOCPU2MSGRAM1

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMMSGxINIT register
//
//*************************************************************************************************
#define MEMCFG_CMMSGXINIT_INIT_CMTOCPU1MSGRAM0   0x1U   // RAM Initialization control for Message
                                                        // RAM CMTOCPU1MSGRAM0
#define MEMCFG_CMMSGXINIT_INIT_CMTOCPU1MSGRAM1   0x2U   // RAM Initialization control for Message
                                                        // RAM CMTOCPU1MSGRAM1
#define MEMCFG_CMMSGXINIT_INIT_CMTOCPU2MSGRAM0   0x4U   // RAM Initialization control for Message
                                                        // RAM CMTOCPU2MSGRAM0
#define MEMCFG_CMMSGXINIT_INIT_CMTOCPU2MSGRAM1   0x8U   // RAM Initialization control for Message
                                                        // RAM CMTOCPU2MSGRAM1

//*************************************************************************************************
//
// The following are defines for the bit fields in the CMMSGxINITDONE register
//
//*************************************************************************************************
#define MEMCFG_CMMSGXINITDONE_INITDONE_CMTOCPU1MSGRAM0   0x1U   // RAM Initialization status for
                                                                // Message RAM CMTOCPU1MSGRAM0
#define MEMCFG_CMMSGXINITDONE_INITDONE_CMTOCPU1MSGRAM1   0x2U   // RAM Initialization status for
                                                                // Message RAM CMTOCPU1MSGRAM1
#define MEMCFG_CMMSGXINITDONE_INITDONE_CMTOCPU2MSGRAM0   0x4U   // RAM Initialization status for
                                                                // Message RAM CMTOCPU2MSGRAM0
#define MEMCFG_CMMSGXINITDONE_INITDONE_CMTOCPU2MSGRAM1   0x8U   // RAM Initialization status for
                                                                // Message RAM CMTOCPU2MSGRAM1

//*************************************************************************************************
//
// The following are defines for the bit fields in the SxGROUP1_LOCK register
//
//*************************************************************************************************
#define MEMCFG_SXGROUP1_LOCK_LOCK_S0   0x1U    // S0 RAM Lock bits
#define MEMCFG_SXGROUP1_LOCK_LOCK_S1   0x2U    // S1 RAM Lock bits
#define MEMCFG_SXGROUP1_LOCK_LOCK_S2   0x4U    // S2 RAM Lock bits
#define MEMCFG_SXGROUP1_LOCK_LOCK_S3   0x8U    // S3 RAM Lock bits
#define MEMCFG_SXGROUP1_LOCK_LOCK_E0   0x10U   // E0 RAM Lock bits

//*************************************************************************************************
//
// The following are defines for the bit fields in the SxGROUP1_TEST register
//
//*************************************************************************************************
#define MEMCFG_SXGROUP1_TEST_TEST_S0_S   0U
#define MEMCFG_SXGROUP1_TEST_TEST_S0_M   0x3U     // Selects the different modes for S0 RAM
#define MEMCFG_SXGROUP1_TEST_TEST_S1_S   2U
#define MEMCFG_SXGROUP1_TEST_TEST_S1_M   0xCU     // Selects the different modes for S1 RAM
#define MEMCFG_SXGROUP1_TEST_TEST_S2_S   4U
#define MEMCFG_SXGROUP1_TEST_TEST_S2_M   0x30U    // Selects the different modes for S2 RAM
#define MEMCFG_SXGROUP1_TEST_TEST_S3_S   6U
#define MEMCFG_SXGROUP1_TEST_TEST_S3_M   0xC0U    // Selects the different modes for S3 RAM
#define MEMCFG_SXGROUP1_TEST_TEST_E0_S   8U
#define MEMCFG_SXGROUP1_TEST_TEST_E0_M   0x300U   // Selects the different modes for E0 RAM

//*************************************************************************************************
//
// The following are defines for the bit fields in the SxGROUP1_INIT register
//
//*************************************************************************************************
#define MEMCFG_SXGROUP1_INIT_INIT_S0   0x1U    // RAM Initialization control for S0 RAM.
#define MEMCFG_SXGROUP1_INIT_INIT_S1   0x2U    // RAM Initialization control for S1 RAM.
#define MEMCFG_SXGROUP1_INIT_INIT_S2   0x4U    // RAM Initialization control for S2 RAM.
#define MEMCFG_SXGROUP1_INIT_INIT_S3   0x8U    // RAM Initialization control for S3 RAM.
#define MEMCFG_SXGROUP1_INIT_INIT_E0   0x10U   // RAM Initialization control for E0 RAM.

//*************************************************************************************************
//
// The following are defines for the bit fields in the SxGROUP1_INITDONE register
//
//*************************************************************************************************
#define MEMCFG_SXGROUP1_INITDONE_INITDONE_S0   0x1U    // RAM Initialization status for S0 RAM.
#define MEMCFG_SXGROUP1_INITDONE_INITDONE_S1   0x2U    // RAM Initialization status for S1 RAM.
#define MEMCFG_SXGROUP1_INITDONE_INITDONE_S2   0x4U    // RAM Initialization status for S2 RAM.
#define MEMCFG_SXGROUP1_INITDONE_INITDONE_S3   0x8U    // RAM Initialization status for S3 RAM.
#define MEMCFG_SXGROUP1_INITDONE_INITDONE_E0   0x10U   // RAM Initialization status for E0 RAM.

//*************************************************************************************************
//
// The following are defines for the bit fields in the ROM_LOCK register
//
//*************************************************************************************************
#define MEMCFG_ROM_LOCK_LOCK_BOOTROM   0x1U   // BOOTROM Lock bits

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
// The following are defines for the bit fields in the PERI_MEM_TEST_LOCK register
//
//*************************************************************************************************
#define MEMCFG_PERI_MEM_TEST_LOCK_LOCK_PERI_MEM_TEST_CONTROL   0x1U   // PERI_MEM_TEST_CONTROL Lock
                                                                      // bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the PERI_MEM_TEST_CONTROL register
//
//*************************************************************************************************
#define MEMCFG_PERI_MEM_TEST_CONTROL_EMAC_TEST_ENABLE           0x1U    // EMAC Test mode enable
#define MEMCFG_PERI_MEM_TEST_CONTROL_EMAC_MEM_FORCE_ERROR       0x2U    // Force Parity Error on
                                                                        // EMAC RAM
#define MEMCFG_PERI_MEM_TEST_CONTROL_ETHERCAT_TEST_ENABLE       0x10U   // EtherCAT Test mode
                                                                        // enable
#define MEMCFG_PERI_MEM_TEST_CONTROL_ETHERCAT_MEM_FORCE_ERROR   0x20U   // Force Parity Error on
                                                                        // EtherCAT RAM


//*************************************************************************************************
//
// The following are defines for the bit fields in the UCERRFLG register
//
//*************************************************************************************************
#define MEMCFG_UCERRFLG_M4RDERR            0x1U    // M4 Uncorrectable Read Error Flag
#define MEMCFG_UCERRFLG_M4WRERR            0x2U    // M4 Uncorrectable Write Error Flag
#define MEMCFG_UCERRFLG_EMACRDERR          0x4U    // EMAC Uncorrectable Read Error Flag
#define MEMCFG_UCERRFLG_UDMARDERR          0x10U   // uDMA Uncorrectable Read Error Flag
#define MEMCFG_UCERRFLG_UDMAWRERR          0x20U   // uDMA Uncorrectable Write Error Flag
#define MEMCFG_UCERRFLG_ETHERCATMEMRDERR   0x40U   // EtherCAT IP RAM Uncorrectable Read Error Flag
#define MEMCFG_UCERRFLG_EMACMEMRDERR       0x80U   // EMAC IP RAM Uncorrectable Read Error Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the UCERRSET register
//
//*************************************************************************************************
#define MEMCFG_UCERRSET_M4RDERR            0x1U          // M4 Uncorrectable Read Error Flag Set
#define MEMCFG_UCERRSET_M4WRERR            0x2U          // M4 Uncorrectable Write Error Flag Set
#define MEMCFG_UCERRSET_EMACRDERR          0x4U          // EMAC Uncorrectable Read Error Flag Set
#define MEMCFG_UCERRSET_UDMARDERR          0x10U         // uDMA Uncorrectable Read Error Flag Set
#define MEMCFG_UCERRSET_UDMAWRERR          0x20U         // uDMA Uncorrectable Write Error Flag Set
#define MEMCFG_UCERRSET_ETHERCATMEMRDERR   0x40U         // EtherCAT IP RAM Uncorrectable Read
                                                         // Error Flag  set
#define MEMCFG_UCERRSET_EMACMEMRDERR       0x80U         // EMAC IP RAM Uncorrectable Read Error
                                                         // Flag set
#define MEMCFG_UCERRSET_KEY_S              16U
#define MEMCFG_UCERRSET_KEY_M              0xFFFF0000U   // KEY to allow write access

//*************************************************************************************************
//
// The following are defines for the bit fields in the UCERRCLR register
//
//*************************************************************************************************
#define MEMCFG_UCERRCLR_M4RDERR            0x1U          // M4 Uncorrectable Read Error Flag Clear
#define MEMCFG_UCERRCLR_M4WRERR            0x2U          // M4 Uncorrectable Write Error Flag Clear
#define MEMCFG_UCERRCLR_EMACRDERR          0x4U          // EMAC Uncorrectable Read Error Flag
                                                         // Clear
#define MEMCFG_UCERRCLR_UDMARDERR          0x10U         // uDMA Uncorrectable Read Error Flag
                                                         // Clear
#define MEMCFG_UCERRCLR_UDMAWRERR          0x20U         // uDMA Uncorrectable Write Error Flag
                                                         // Clear
#define MEMCFG_UCERRCLR_ETHERCATMEMRDERR   0x40U         // EtherCAT IP RAM Uncorrectable Read
                                                         // Error Flag  Clear
#define MEMCFG_UCERRCLR_EMACMEMRDERR       0x80U         // EMAC IP RAM Uncorrectable Read Error
                                                         // Flag Clear
#define MEMCFG_UCERRCLR_KEY_S              16U
#define MEMCFG_UCERRCLR_KEY_M              0xFFFF0000U   // KEY to allow write access

//*************************************************************************************************
//
// The following are defines for the bit fields in the BUSFAULTFLG register
//
//*************************************************************************************************
#define MEMCFG_BUSFAULTFLG_M4BUSFAULT     0x1U   // M4 busfault Flag
#define MEMCFG_BUSFAULTFLG_UDMABUSFAULT   0x2U   // UDMA busfault Flag
#define MEMCFG_BUSFAULTFLG_EMACBUSFAULT   0x4U   // EMAC busfault Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the BUSFAULTCLR register
//
//*************************************************************************************************
#define MEMCFG_BUSFAULTCLR_M4BUSFAULT     0x1U          // M4 busfault Flag Clear
#define MEMCFG_BUSFAULTCLR_UDMABUSFAULT   0x2U          // UDMA busfault Flag Clear
#define MEMCFG_BUSFAULTCLR_EMACBUSFAULT   0x4U          // EMAC busfault Flag Clear
#define MEMCFG_BUSFAULTCLR_KEY_S          16U
#define MEMCFG_BUSFAULTCLR_KEY_M          0xFFFF0000U   // KEY to allow write access

//*************************************************************************************************
//
// The following are defines for the bit fields in the CERRFLG register
//
//*************************************************************************************************
#define MEMCFG_CERRFLG_M4RDERR     0x1U    // M4 Correctable Read Error Flag
#define MEMCFG_CERRFLG_M4WRERR     0x2U    // M4 Correctable Write Error Flag
#define MEMCFG_CERRFLG_EMACRDERR   0x4U    // EMAC Correctable Read Error Flag
#define MEMCFG_CERRFLG_UDMARDERR   0x10U   // uDMA Correctable Read Error Flag
#define MEMCFG_CERRFLG_UDMAWRERR   0x20U   // uDMA Correctable Write Error Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the CERRSET register
//
//*************************************************************************************************
#define MEMCFG_CERRSET_M4RDERR     0x1U          // M4 Correctable Read Error Flag Set
#define MEMCFG_CERRSET_M4WRERR     0x2U          // M4 Correctable Write Error Flag Set
#define MEMCFG_CERRSET_EMACRDERR   0x4U          // EMAC Correctable Read Error Flag Set
#define MEMCFG_CERRSET_UDMARDERR   0x10U         // uDMA Correctable Read Error Flag Set
#define MEMCFG_CERRSET_UDMAWRERR   0x20U         // uDMA Correctable Write Error Flag Set
#define MEMCFG_CERRSET_KEY_S       16U
#define MEMCFG_CERRSET_KEY_M       0xFFFF0000U   // KEY to allow write access

//*************************************************************************************************
//
// The following are defines for the bit fields in the CERRCLR register
//
//*************************************************************************************************
#define MEMCFG_CERRCLR_M4RDERR     0x1U          // M4 Correctable Read Error Flag Clear
#define MEMCFG_CERRCLR_M4WRERR     0x2U          // M4 Correctable Write Error Flag Clear
#define MEMCFG_CERRCLR_EMACRDERR   0x4U          // EMAC Correctable Read Error Flag Clear
#define MEMCFG_CERRCLR_UDMARDERR   0x10U         // uDMA Correctable Read Error Flag Clear
#define MEMCFG_CERRCLR_UDMAWRERR   0x20U         // uDMA Correctable Write Error Flag Clear
#define MEMCFG_CERRCLR_KEY_S       16U
#define MEMCFG_CERRCLR_KEY_M       0xFFFF0000U   // KEY to allow write access

//*************************************************************************************************
//
// The following are defines for the bit fields in the CEINTFLG register
//
//*************************************************************************************************
#define MEMCFG_CEINTFLG_CEINTFLAG   0x1U   // Total corrected error count exceeded threshold flag.

//*************************************************************************************************
//
// The following are defines for the bit fields in the CEINTSET register
//
//*************************************************************************************************
#define MEMCFG_CEINTSET_CEINTSET   0x1U          // Total corrected error count exceeded flag set.
#define MEMCFG_CEINTSET_KEY_S      16U
#define MEMCFG_CEINTSET_KEY_M      0xFFFF0000U   // KEY to allow write access

//*************************************************************************************************
//
// The following are defines for the bit fields in the CEINTCLR register
//
//*************************************************************************************************
#define MEMCFG_CEINTCLR_CEINTCLR   0x1U          // M4 Corrected Error Threshold Exceeded Error
                                                 // Clear.
#define MEMCFG_CEINTCLR_KEY_S      16U
#define MEMCFG_CEINTCLR_KEY_M      0xFFFF0000U   // KEY to allow write access

//*************************************************************************************************
//
// The following are defines for the bit fields in the CEINTEN register
//
//*************************************************************************************************
#define MEMCFG_CEINTEN_CEINTEN   0x1U          // M4 Correctable Error Interrupt Enable.
#define MEMCFG_CEINTEN_KEY_S     16U
#define MEMCFG_CEINTEN_KEY_M     0xFFFF0000U   // KEY to allow write access


//*************************************************************************************************
//
// The following are defines for the bit fields in the DIAGERRFLG register
//
//*************************************************************************************************
#define MEMCFG_DIAGERRFLG_UCRDERROR   0x1U   // Diagnostics Uncorrectable Read Error Flag
#define MEMCFG_DIAGERRFLG_UCWRERROR   0x2U   // Diagnostics Uncorrectable Write Error Flag
#define MEMCFG_DIAGERRFLG_CRDERROR    0x4U   // Diagnostics Correctable Read Error Flag
#define MEMCFG_DIAGERRFLG_CWRERROR    0x8U   // Diagnostics Correctable Write Error Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the DIAGERRCLR register
//
//*************************************************************************************************
#define MEMCFG_DIAGERRCLR_UCRDERROR   0x1U   // Clear diagnostics uncorrectable Read Error Flag
#define MEMCFG_DIAGERRCLR_UCWRERROR   0x2U   // Clear diagnostics uncorrectable Write Error Flag
#define MEMCFG_DIAGERRCLR_CRDERROR    0x4U   // Clear diagnostics correctable Read Error Flag
#define MEMCFG_DIAGERRCLR_CWRERROR    0x8U   // Clear diagnostics correctable Write Error Flag



#endif
