//###########################################################################
//
// FILE:    hw_dcsm.h
//
// TITLE:   Definitions for the DCSM registers.
//
//###########################################################################
// $Copyright:
// Copyright (C) 2023 Texas Instruments Incorporated - http://www.ti.com/
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
#define DCSM_O_B0_Z1OTP_LINKPOINTER1   0x0U    // Zone 1 Link Pointer1 in Z1 OTP for flash BANK0
#define DCSM_O_B0_Z1OTP_LINKPOINTER2   0x4U    // Zone 1 Link Pointer2 in Z1 OTP for flash BANK0
#define DCSM_O_B0_Z1OTP_LINKPOINTER3   0x8U    // Zone 1 Link Pointer3 in Z1 OTP for flash BANK0
#define DCSM_O_Z1OTP_BOOTPIN_CONFIG    0xCU    // Boot Pin Configuration
#define DCSM_O_Z1OTP_GPREG2            0xEU    // Zone-1 General Purpose Register-2 content
#define DCSM_O_Z1OTP_PSWDLOCK          0x10U   // Secure Password Lock in Z1 OTP
#define DCSM_O_Z1OTP_CRCLOCK           0x14U   // Secure CRC Lock in Z1 OTP
#define DCSM_O_Z1OTP_BOOTDEF_LOW       0x1CU   // Boot definition (low 32bit)
#define DCSM_O_Z1OTP_BOOTDEF_HIGH      0x1EU   // Boot definition (high 32bit)

#define DCSM_O_B0_Z2OTP_LINKPOINTER1   0x0U    // Zone 2Link Pointer1 in Z2 OTP for flash BANK0
#define DCSM_O_B0_Z2OTP_LINKPOINTER2   0x4U    // Zone 2 Link Pointer2 in Z2 OTP for flash BANK0
#define DCSM_O_B0_Z2OTP_LINKPOINTER3   0x8U    // Zone 12Link Pointer3 in Z2 OTP for flash BANK0
#define DCSM_O_Z2OTP_BOOTPIN_CONFIG    0xCU    // Boot Pin Configuration
#define DCSM_O_Z2OTP_GPREG2            0xEU    // Zone-2 General Purpose Register-2 content
#define DCSM_O_Z2OTP_PSWDLOCK          0x10U   // Secure Password Lock in Z2 OTP
#define DCSM_O_Z2OTP_CRCLOCK           0x14U   // Secure CRC Lock in Z2 OTP
#define DCSM_O_Z2OTP_BOOTDEF_LOW       0x1CU   // Boot definition (low 32bit)
#define DCSM_O_Z2OTP_BOOTDEF_HIGH      0x1EU   // Boot definition (high 32bit)

#define DCSM_O_B0_Z1_LINKPOINTER      0x0U    // Zone 1 Link Pointer for flash BANK0
#define DCSM_O_Z1_OTPSECLOCK          0x2U    // Zone 1 OTP Secure lock
#define DCSM_O_Z1_BOOTDEF_HIGH        0x4U    // Boot definition (high 32bit)
#define DCSM_O_B0_Z1_LINKPOINTERERR   0x6U    // Link Pointer Error for flash BANK0
#define DCSM_O_Z1_BOOTPIN_CONFIG      0x8U    // Boot Pin Configuration
#define DCSM_O_Z1_GPREG2              0xAU    // Zone1 General Purpose Register-2
#define DCSM_O_Z1_BOOTDEF_LOW         0xCU    // Boot definition (low 32bit)
#define DCSM_O_Z1_CSMKEY0             0x10U   // Zone 1 CSM Key 0
#define DCSM_O_Z1_CSMKEY1             0x12U   // Zone 1 CSM Key 1
#define DCSM_O_Z1_CSMKEY2             0x14U   // Zone 1 CSM Key 2
#define DCSM_O_Z1_CSMKEY3             0x16U   // Zone 1 CSM Key 3
#define DCSM_O_Z1_CR                  0x19U   // Zone 1 CSM Control Register
#define DCSM_O_B0_Z1_GRABSECTR        0x1AU   // Zone 1 Grab Flash BANK0 Sectors Register
#define DCSM_O_Z1_GRABRAMR            0x1CU   // Zone 1 Grab RAM Blocks Register
#define DCSM_O_B0_Z1_EXEONLYSECTR     0x1EU   // Zone 1 Flash BANK0 Execute_Only Sector Register
#define DCSM_O_Z1_EXEONLYRAMR         0x20U   // Zone 1 RAM Execute_Only Block Register

#define DCSM_O_B0_Z2_LINKPOINTER      0x0U    // Zone 2 Link Pointer for flash BANK0
#define DCSM_O_Z2_OTPSECLOCK          0x2U    // Zone 2 OTP Secure lock
#define DCSM_O_Z2_BOOTDEF_HIGH        0x4U    // Boot definition (high 32bit)
#define DCSM_O_B0_Z2_LINKPOINTERERR   0x6U    // Link Pointer Error for flash BANK0
#define DCSM_O_Z2_BOOTPIN_CONFIG      0x8U    // Boot Pin Configuration
#define DCSM_O_Z2_GPREG2              0xAU    // Zone2 General Purpose Register-2
#define DCSM_O_Z2_BOOTDEF_LOW         0xCU    // Boot definition (low 32bit)
#define DCSM_O_Z2_CSMKEY0             0x10U   // Zone 2 CSM Key 0
#define DCSM_O_Z2_CSMKEY1             0x12U   // Zone 2 CSM Key 1
#define DCSM_O_Z2_CSMKEY2             0x14U   // Zone 2 CSM Key 2
#define DCSM_O_Z2_CSMKEY3             0x16U   // Zone 2 CSM Key 3
#define DCSM_O_Z2_CR                  0x19U   // Zone 2 CSM Control Register
#define DCSM_O_B0_Z2_GRABSECTR        0x1AU   // Zone 2 Grab Flash BANK0 Sectors Register
#define DCSM_O_Z2_GRABRAMR            0x1CU   // Zone 2 Grab RAM Blocks Register
#define DCSM_O_B0_Z2_EXEONLYSECTR     0x1EU   // Zone 2 Flash BANK0 Execute_Only Sector Register
#define DCSM_O_Z2_EXEONLYRAMR         0x20U   // Zone 2 RAM Execute_Only Block Register

#define DCSM_O_FLSEM         0x0U   // Flash Wrapper Semaphore Register
#define DCSM_O_B0_SECTSTAT   0x2U   // Flash BANK0 Sectors Status Register
#define DCSM_O_RAMSTAT       0x4U   // RAM Status Register
#define DCSM_O_SECERRSTAT    0xAU   // Security Error Status Register
#define DCSM_O_SECERRCLR     0xCU   // Security Error Clear Register
#define DCSM_O_SECERRFRC     0xEU   // Security Error Force Register




//*************************************************************************************************
//
// The following are defines for the bit fields in the B0_Z1_LINKPOINTER register
//
//*************************************************************************************************
#define DCSM_B0_Z1_LINKPOINTER_LINKPOINTER_S   0U
#define DCSM_B0_Z1_LINKPOINTER_LINKPOINTER_M   0x1FFFFFFFU   // Zone1 LINK Pointer for zone Flash
                                                             // BANK0

//*************************************************************************************************
//
// The following are defines for the bit fields in the Z1_OTPSECLOCK register
//
//*************************************************************************************************
#define DCSM_Z1_OTPSECLOCK_PSWDLOCK_S   4U
#define DCSM_Z1_OTPSECLOCK_PSWDLOCK_M   0xF0U    // Zone1 Password Lock.
#define DCSM_Z1_OTPSECLOCK_CRCLOCK_S    8U
#define DCSM_Z1_OTPSECLOCK_CRCLOCK_M    0xF00U   // Zone1 CRC Lock.

//*************************************************************************************************
//
// The following are defines for the bit fields in the B0_Z1_LINKPOINTERERR register
//
//*************************************************************************************************
#define DCSM_B0_Z1_LINKPOINTERERR_Z1_LINKPOINTERERR_S   0U
#define DCSM_B0_Z1_LINKPOINTERERR_Z1_LINKPOINTERERR_M   0x1FFFFFFFU   // Error to Resolve Z1 Link
                                                                      // pointer from OTP loaded values

//*************************************************************************************************
//
// The following are defines for the bit fields in the Z1_CR register
//
//*************************************************************************************************
#define DCSM_Z1_CR_ALLZERO    0x8U      // CSMPSWD All Zeros
#define DCSM_Z1_CR_ALLONE     0x10U     // CSMPSWD All Ones
#define DCSM_Z1_CR_UNSECURE   0x20U     // CSMPSWD Match CSMKEY
#define DCSM_Z1_CR_ARMED      0x40U     // CSM Passwords Read Status
#define DCSM_Z1_CR_FORCESEC   0x8000U   // Force Secure

//*************************************************************************************************
//
// The following are defines for the bit fields in the B0_Z1_GRABSECTR register
//
//*************************************************************************************************
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT0_S    0U
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT0_M    0x3U          // Grab Flash Sector 0 in BANK0
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT1_S    2U
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT1_M    0xCU          // Grab Flash Sector 1 in BANK0
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT2_S    4U
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT2_M    0x30U         // Grab Flash Sector 2 in BANK0
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT3_S    6U
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT3_M    0xC0U         // Grab Flash Sector 3 in BANK0
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT4_S    8U
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT4_M    0x300U        // Grab Flash Sector 4 in BANK0
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT5_S    10U
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT5_M    0xC00U        // Grab Flash Sector 5 in BANK0
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT6_S    12U
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT6_M    0x3000U       // Grab Flash Sector 6 in BANK0
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT7_S    14U
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT7_M    0xC000U       // Grab Flash Sector 7 in BANK0
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT8_S    16U
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT8_M    0x30000U      // Grab Flash Sector 8 in BANK0
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT9_S    18U
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT9_M    0xC0000U      // Grab Flash Sector 9 in BANK0
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT10_S   20U
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT10_M   0x300000U     // Grab Flash Sector 10 in BANK0
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT11_S   22U
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT11_M   0xC00000U     // Grab Flash Sector 11 in BANK0
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT12_S   24U
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT12_M   0x3000000U    // Grab Flash Sector 12 in BANK0
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT13_S   26U
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT13_M   0xC000000U    // Grab Flash Sector 13 in BANK0
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT14_S   28U
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT14_M   0x30000000U   // Grab Flash Sector 14 in BANK0
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT15_S   30U
#define DCSM_B0_Z1_GRABSECTR_GRAB_SECT15_M   0xC0000000U   // Grab Flash Sector 15 in BANK0

//*************************************************************************************************
//
// The following are defines for the bit fields in the Z1_GRABRAMR register
//
//*************************************************************************************************
#define DCSM_Z1_GRABRAMR_GRAB_RAM4_S   8U
#define DCSM_Z1_GRABRAMR_GRAB_RAM4_M   0x300U    // Grab RAM LS4
#define DCSM_Z1_GRABRAMR_GRAB_RAM5_S   10U
#define DCSM_Z1_GRABRAMR_GRAB_RAM5_M   0xC00U    // Grab RAM LS5
#define DCSM_Z1_GRABRAMR_GRAB_RAM6_S   12U
#define DCSM_Z1_GRABRAMR_GRAB_RAM6_M   0x3000U   // Grab RAM LS6
#define DCSM_Z1_GRABRAMR_GRAB_RAM7_S   14U
#define DCSM_Z1_GRABRAMR_GRAB_RAM7_M   0xC000U   // Grab RAM LS7

//*************************************************************************************************
//
// The following are defines for the bit fields in the B0_Z1_EXEONLYSECTR register
//
//*************************************************************************************************
#define DCSM_B0_Z1_EXEONLYSECTR_EXEONLY_SECT0    0x1U      // Execute-Only Flash Sector 0 in Flash
                                                           // BANK0
#define DCSM_B0_Z1_EXEONLYSECTR_EXEONLY_SECT1    0x2U      // Execute-Only Flash Sector 1 in Flash
                                                           // BANK0
#define DCSM_B0_Z1_EXEONLYSECTR_EXEONLY_SECT2    0x4U      // Execute-Only Flash Sector 2 in Flash
                                                           // BANK0
#define DCSM_B0_Z1_EXEONLYSECTR_EXEONLY_SECT3    0x8U      // Execute-Only Flash Sector 3 in Flash
                                                           // BANK0
#define DCSM_B0_Z1_EXEONLYSECTR_EXEONLY_SECT4    0x10U     // Execute-Only Flash Sector 4 in Flash
                                                           // BANK0
#define DCSM_B0_Z1_EXEONLYSECTR_EXEONLY_SECT5    0x20U     // Execute-Only Flash Sector 5 in Flash
                                                           // BANK0
#define DCSM_B0_Z1_EXEONLYSECTR_EXEONLY_SECT6    0x40U     // Execute-Only Flash Sector 6 in Flash
                                                           // BANK0
#define DCSM_B0_Z1_EXEONLYSECTR_EXEONLY_SECT7    0x80U     // Execute-Only Flash Sector 7 in Flash
                                                           // BANK0
#define DCSM_B0_Z1_EXEONLYSECTR_EXEONLY_SECT8    0x100U    // Execute-Only Flash Sector 8 in Flash
                                                           // BANK0
#define DCSM_B0_Z1_EXEONLYSECTR_EXEONLY_SECT9    0x200U    // Execute-Only Flash Sector 9 in Flash
                                                           // BANK0
#define DCSM_B0_Z1_EXEONLYSECTR_EXEONLY_SECT10   0x400U    // Execute-Only Flash Sector 10 in Flash
                                                           // BANK0
#define DCSM_B0_Z1_EXEONLYSECTR_EXEONLY_SECT11   0x800U    // Execute-Only Flash Sector 11 in Flash
                                                           // BANK0
#define DCSM_B0_Z1_EXEONLYSECTR_EXEONLY_SECT12   0x1000U   // Execute-Only Flash Sector 12 in Flash
                                                           // BANK0
#define DCSM_B0_Z1_EXEONLYSECTR_EXEONLY_SECT13   0x2000U   // Execute-Only Flash Sector 13 in Flash
                                                           // BANK0
#define DCSM_B0_Z1_EXEONLYSECTR_EXEONLY_SECT14   0x4000U   // Execute-Only Flash Sector 14 in Flash
                                                           // BANK0
#define DCSM_B0_Z1_EXEONLYSECTR_EXEONLY_SECT15   0x8000U   // Execute-Only Flash Sector 15 in Flash
                                                           // BANK0

//*************************************************************************************************
//
// The following are defines for the bit fields in the Z1_EXEONLYRAMR register
//
//*************************************************************************************************
#define DCSM_Z1_EXEONLYRAMR_EXEONLY_RAM4   0x10U   // Execute-Only RAM LS4
#define DCSM_Z1_EXEONLYRAMR_EXEONLY_RAM5   0x20U   // Execute-Only RAM LS5
#define DCSM_Z1_EXEONLYRAMR_EXEONLY_RAM6   0x40U   // Execute-Only RAM LS6
#define DCSM_Z1_EXEONLYRAMR_EXEONLY_RAM7   0x80U   // Execute-Only RAM LS7


//*************************************************************************************************
//
// The following are defines for the bit fields in the B0_Z2_LINKPOINTER register
//
//*************************************************************************************************
#define DCSM_B0_Z2_LINKPOINTER_LINKPOINTER_S   0U
#define DCSM_B0_Z2_LINKPOINTER_LINKPOINTER_M   0x1FFFFFFFU   // Zone2 LINK Pointer in Flash BANK0

//*************************************************************************************************
//
// The following are defines for the bit fields in the Z2_OTPSECLOCK register
//
//*************************************************************************************************
#define DCSM_Z2_OTPSECLOCK_PSWDLOCK_S   4U
#define DCSM_Z2_OTPSECLOCK_PSWDLOCK_M   0xF0U    // Zone2 Password Lock.
#define DCSM_Z2_OTPSECLOCK_CRCLOCK_S    8U
#define DCSM_Z2_OTPSECLOCK_CRCLOCK_M    0xF00U   // Zone2 CRC Lock.

//*************************************************************************************************
//
// The following are defines for the bit fields in the B0_Z2_LINKPOINTERERR register
//
//*************************************************************************************************
#define DCSM_B0_Z2_LINKPOINTERERR_Z2_LINKPOINTERERR_S   0U
#define DCSM_B0_Z2_LINKPOINTERERR_Z2_LINKPOINTERERR_M   0x1FFFFFFFU   // Error to Resolve Z2 Link
                                                                      // pointer from OTP loaded values

//*************************************************************************************************
//
// The following are defines for the bit fields in the Z2_CR register
//
//*************************************************************************************************
#define DCSM_Z2_CR_ALLZERO    0x8U      // CSMPSWD All Zeros
#define DCSM_Z2_CR_ALLONE     0x10U     // CSMPSWD All Ones
#define DCSM_Z2_CR_UNSECURE   0x20U     // CSMPSWD Match CSMKEY
#define DCSM_Z2_CR_ARMED      0x40U     // CSM Passwords Read Status
#define DCSM_Z2_CR_FORCESEC   0x8000U   // Force Secure

//*************************************************************************************************
//
// The following are defines for the bit fields in the B0_Z2_GRABSECTR register
//
//*************************************************************************************************
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT0_S    0U
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT0_M    0x3U          // Grab Flash Sector 0 in Flash BANK0
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT1_S    2U
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT1_M    0xCU          // Grab Flash Sector 1 in Flash BANK0
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT2_S    4U
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT2_M    0x30U         // Grab Flash Sector 2 in Flash BANK0
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT3_S    6U
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT3_M    0xC0U         // Grab Flash Sector 3 in Flash BANK0
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT4_S    8U
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT4_M    0x300U        // Grab Flash Sector 4 in Flash BANK0
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT5_S    10U
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT5_M    0xC00U        // Grab Flash Sector 5 in Flash BANK0
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT6_S    12U
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT6_M    0x3000U       // Grab Flash Sector 6 in Flash BANK0
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT7_S    14U
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT7_M    0xC000U       // Grab Flash Sector 7 in Flash BANK0
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT8_S    16U
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT8_M    0x30000U      // Grab Flash Sector 8 in Flash BANK0
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT9_S    18U
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT9_M    0xC0000U      // Grab Flash Sector 9 in Flash BANK0
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT10_S   20U
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT10_M   0x300000U     // Grab Flash Sector 10 in Flash BANK0
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT11_S   22U
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT11_M   0xC00000U     // Grab Flash Sector 11 in Flash BANK0
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT12_S   24U
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT12_M   0x3000000U    // Grab Flash Sector 12 in Flash BANK0
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT13_S   26U
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT13_M   0xC000000U    // Grab Flash Sector 13 in Flash BANK0
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT14_S   28U
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT14_M   0x30000000U   // Grab Flash Sector 14 in Flash BANK0
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT15_S   30U
#define DCSM_B0_Z2_GRABSECTR_GRAB_SECT15_M   0xC0000000U   // Grab Flash Sector 15 in Flash BANK0

//*************************************************************************************************
//
// The following are defines for the bit fields in the Z2_GRABRAMR register
//
//*************************************************************************************************
#define DCSM_Z2_GRABRAMR_GRAB_RAM4_S   8U
#define DCSM_Z2_GRABRAMR_GRAB_RAM4_M   0x300U    // Grab RAM LS4
#define DCSM_Z2_GRABRAMR_GRAB_RAM5_S   10U
#define DCSM_Z2_GRABRAMR_GRAB_RAM5_M   0xC00U    // Grab RAM LS5
#define DCSM_Z2_GRABRAMR_GRAB_RAM6_S   12U
#define DCSM_Z2_GRABRAMR_GRAB_RAM6_M   0x3000U   // Grab RAM LS6
#define DCSM_Z2_GRABRAMR_GRAB_RAM7_S   14U
#define DCSM_Z2_GRABRAMR_GRAB_RAM7_M   0xC000U   // Grab RAM LS7

//*************************************************************************************************
//
// The following are defines for the bit fields in the B0_Z2_EXEONLYSECTR register
//
//*************************************************************************************************
#define DCSM_B0_Z2_EXEONLYSECTR_EXEONLY_SECT0    0x1U      // Execute-Only Flash Sector 0 in Flash
                                                           // BANK0
#define DCSM_B0_Z2_EXEONLYSECTR_EXEONLY_SECT1    0x2U      // Execute-Only Flash Sector 1 in Flash
                                                           // BANK0
#define DCSM_B0_Z2_EXEONLYSECTR_EXEONLY_SECT2    0x4U      // Execute-Only Flash Sector 2 in Flash
                                                           // BANK0
#define DCSM_B0_Z2_EXEONLYSECTR_EXEONLY_SECT3    0x8U      // Execute-Only Flash Sector 3 in Flash
                                                           // BANK0
#define DCSM_B0_Z2_EXEONLYSECTR_EXEONLY_SECT4    0x10U     // Execute-Only Flash Sector 4 in Flash
                                                           // BANK0
#define DCSM_B0_Z2_EXEONLYSECTR_EXEONLY_SECT5    0x20U     // Execute-Only Flash Sector 5 in Flash
                                                           // BANK0
#define DCSM_B0_Z2_EXEONLYSECTR_EXEONLY_SECT6    0x40U     // Execute-Only Flash Sector 6 in Flash
                                                           // BANK0
#define DCSM_B0_Z2_EXEONLYSECTR_EXEONLY_SECT7    0x80U     // Execute-Only Flash Sector 7 in Flash
                                                           // BANK0
#define DCSM_B0_Z2_EXEONLYSECTR_EXEONLY_SECT8    0x100U    // Execute-Only Flash Sector 8 in Flash
                                                           // BANK0
#define DCSM_B0_Z2_EXEONLYSECTR_EXEONLY_SECT9    0x200U    // Execute-Only Flash Sector 9 in Flash
                                                           // BANK0
#define DCSM_B0_Z2_EXEONLYSECTR_EXEONLY_SECT10   0x400U    // Execute-Only Flash Sector 10 in Flash
                                                           // BANK0
#define DCSM_B0_Z2_EXEONLYSECTR_EXEONLY_SECT11   0x800U    // Execute-Only Flash Sector 11 in Flash
                                                           // BANK0
#define DCSM_B0_Z2_EXEONLYSECTR_EXEONLY_SECT12   0x1000U   // Execute-Only Flash Sector 12 in Flash
                                                           // BANK0
#define DCSM_B0_Z2_EXEONLYSECTR_EXEONLY_SECT13   0x2000U   // Execute-Only Flash Sector 13 in Flash
                                                           // BANK0
#define DCSM_B0_Z2_EXEONLYSECTR_EXEONLY_SECT14   0x4000U   // Execute-Only Flash Sector 14 in Flash
                                                           // BANK0
#define DCSM_B0_Z2_EXEONLYSECTR_EXEONLY_SECT15   0x8000U   // Execute-Only Flash Sector 15 in Flash
                                                           // BANK0

//*************************************************************************************************
//
// The following are defines for the bit fields in the Z2_EXEONLYRAMR register
//
//*************************************************************************************************
#define DCSM_Z2_EXEONLYRAMR_EXEONLY_RAM4   0x10U   // Execute-Only RAM LS4
#define DCSM_Z2_EXEONLYRAMR_EXEONLY_RAM5   0x20U   // Execute-Only RAM LS5
#define DCSM_Z2_EXEONLYRAMR_EXEONLY_RAM6   0x40U   // Execute-Only RAM LS6
#define DCSM_Z2_EXEONLYRAMR_EXEONLY_RAM7   0x80U   // Execute-Only RAM LS7


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
// The following are defines for the bit fields in the B0_SECTSTAT register
//
//*************************************************************************************************
#define DCSM_B0_SECTSTAT_STATUS_SECT0_S    0U
#define DCSM_B0_SECTSTAT_STATUS_SECT0_M    0x3U          // Zone Status Flash BANK0 Sector 0
#define DCSM_B0_SECTSTAT_STATUS_SECT1_S    2U
#define DCSM_B0_SECTSTAT_STATUS_SECT1_M    0xCU          // Zone Status Flash BANK0 sector 1
#define DCSM_B0_SECTSTAT_STATUS_SECT2_S    4U
#define DCSM_B0_SECTSTAT_STATUS_SECT2_M    0x30U         // Zone Status Flash BANK0 Sector 2
#define DCSM_B0_SECTSTAT_STATUS_SECT3_S    6U
#define DCSM_B0_SECTSTAT_STATUS_SECT3_M    0xC0U         // Zone Status Flash BANK0 Sector 3
#define DCSM_B0_SECTSTAT_STATUS_SECT4_S    8U
#define DCSM_B0_SECTSTAT_STATUS_SECT4_M    0x300U        // Zone Status Flash BANK0 Sector 4
#define DCSM_B0_SECTSTAT_STATUS_SECT5_S    10U
#define DCSM_B0_SECTSTAT_STATUS_SECT5_M    0xC00U        // Zone Status Flash BANK0 Sector 5
#define DCSM_B0_SECTSTAT_STATUS_SECT6_S    12U
#define DCSM_B0_SECTSTAT_STATUS_SECT6_M    0x3000U       // Zone Status Flash BANK0 Sector 6
#define DCSM_B0_SECTSTAT_STATUS_SECT7_S    14U
#define DCSM_B0_SECTSTAT_STATUS_SECT7_M    0xC000U       // Zone Status Flash BANK0 Sector 7
#define DCSM_B0_SECTSTAT_STATUS_SECT8_S    16U
#define DCSM_B0_SECTSTAT_STATUS_SECT8_M    0x30000U      // Zone Status Flash BANK0 sector 8
#define DCSM_B0_SECTSTAT_STATUS_SECT9_S    18U
#define DCSM_B0_SECTSTAT_STATUS_SECT9_M    0xC0000U      // Zone Status Flash BANK0 Sector 9
#define DCSM_B0_SECTSTAT_STATUS_SECT10_S   20U
#define DCSM_B0_SECTSTAT_STATUS_SECT10_M   0x300000U     // Zone Status Flash BANK0 Sector 10
#define DCSM_B0_SECTSTAT_STATUS_SECT11_S   22U
#define DCSM_B0_SECTSTAT_STATUS_SECT11_M   0xC00000U     // Zone Status Flash BANK0 Sector 11
#define DCSM_B0_SECTSTAT_STATUS_SECT12_S   24U
#define DCSM_B0_SECTSTAT_STATUS_SECT12_M   0x3000000U    // Zone Status Flash BANK0 Sector 12
#define DCSM_B0_SECTSTAT_STATUS_SECT13_S   26U
#define DCSM_B0_SECTSTAT_STATUS_SECT13_M   0xC000000U    // Zone Status Flash BANK0 Sector 13
#define DCSM_B0_SECTSTAT_STATUS_SECT14_S   28U
#define DCSM_B0_SECTSTAT_STATUS_SECT14_M   0x30000000U   // Zone Status Flash BANK0 Sector 14
#define DCSM_B0_SECTSTAT_STATUS_SECT15_S   30U
#define DCSM_B0_SECTSTAT_STATUS_SECT15_M   0xC0000000U   // Zone Status Flash BANK0 Sector 15

//*************************************************************************************************
//
// The following are defines for the bit fields in the RAMSTAT register
//
//*************************************************************************************************
#define DCSM_RAMSTAT_STATUS_RAM4_S   8U
#define DCSM_RAMSTAT_STATUS_RAM4_M   0x300U    // Zone Status RAM LS4
#define DCSM_RAMSTAT_STATUS_RAM5_S   10U
#define DCSM_RAMSTAT_STATUS_RAM5_M   0xC00U    // Zone Status RAM LS5
#define DCSM_RAMSTAT_STATUS_RAM6_S   12U
#define DCSM_RAMSTAT_STATUS_RAM6_M   0x3000U   // Zone Status RAM LS6
#define DCSM_RAMSTAT_STATUS_RAM7_S   14U
#define DCSM_RAMSTAT_STATUS_RAM7_M   0xC000U   // Zone Status RAM LS7

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
#define DCSM_SECERRFRC_ERR   0x1U   // Set Security Configuration Load Error Status Bit



#endif
