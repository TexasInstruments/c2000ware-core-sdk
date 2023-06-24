//###########################################################################
//
// FILE:    hw_dcsm.h
//
// TITLE:   Definitions for the DCSM registers.
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

#ifndef HW_DCSM_H
#define HW_DCSM_H

//*************************************************************************************************
//
// The following are defines for the DCSM register offsets
//
//*************************************************************************************************
#define DCSM_O_Z1OTP_LINKPOINTER1   0x0U    // Zone 1 Link Pointer1 in Z1 OTP
#define DCSM_O_Z1OTP_LINKPOINTER2   0x4U    // Zone 1 Link Pointer2 in Z1 OTP
#define DCSM_O_Z1OTP_LINKPOINTER3   0x8U    // Zone 1 Link Pointer3 in Z1 OTP
#define DCSM_O_Z1OTP_PSWDLOCK       0x10U   // Secure Password Lock in Z1 OTP
#define DCSM_O_Z1OTP_CRCLOCK        0x14U   // Secure CRC Lock in Z1 OTP
#define DCSM_O_Z1OTP_BOOTCTRL       0x1EU   // Boot Mode in Z1 OTP

#define DCSM_O_Z2OTP_LINKPOINTER1   0x0U    // Zone 2 Link Pointer1 in Z2 OTP
#define DCSM_O_Z2OTP_LINKPOINTER2   0x4U    // Zone 2 Link Pointer2 in Z2 OTP
#define DCSM_O_Z2OTP_LINKPOINTER3   0x8U    // Zone 2 Link Pointer3 in Z2 OTP
#define DCSM_O_Z2OTP_PSWDLOCK       0x10U   // Secure Password Lock in Z2 OTP
#define DCSM_O_Z2OTP_CRCLOCK        0x14U   // Secure CRC Lock in Z2 OTP
#define DCSM_O_Z2OTP_BOOTCTRL       0x1EU   // Boot Mode in Z2 OTP

#define DCSM_O_Z1_LINKPOINTER      0x0U    // Zone 1 Link Pointer
#define DCSM_O_Z1_OTPSECLOCK       0x2U    // Zone 1 OTP Secure JTAG lock
#define DCSM_O_Z1_BOOTCTRL         0x4U    // Boot Mode
#define DCSM_O_Z1_LINKPOINTERERR   0x6U    // Link Pointer Error
#define DCSM_O_Z1_CSMKEY0          0x10U   // Zone 1 CSM Key 0
#define DCSM_O_Z1_CSMKEY1          0x12U   // Zone 1 CSM Key 1
#define DCSM_O_Z1_CSMKEY2          0x14U   // Zone 1 CSM Key 2
#define DCSM_O_Z1_CSMKEY3          0x16U   // Zone 1 CSM Key 3
#define DCSM_O_Z1_CR               0x19U   // Zone 1 CSM Control Register
#define DCSM_O_Z1_GRABSECTR        0x1AU   // Zone 1 Grab Flash Sectors Register
#define DCSM_O_Z1_GRABRAMR         0x1CU   // Zone 1 Grab RAM Blocks Register
#define DCSM_O_Z1_EXEONLYSECTR     0x1EU   // Zone 1 Flash Execute_Only Sector Register
#define DCSM_O_Z1_EXEONLYRAMR      0x20U   // Zone 1 RAM Execute_Only Block Register

#define DCSM_O_Z2_LINKPOINTER      0x0U    // Zone 2 Link Pointer
#define DCSM_O_Z2_OTPSECLOCK       0x2U    // Zone 2 OTP Secure JTAG lock
#define DCSM_O_Z2_BOOTCTRL         0x4U    // Boot Mode
#define DCSM_O_Z2_LINKPOINTERERR   0x6U    // Link Pointer Error
#define DCSM_O_Z2_CSMKEY0          0x10U   // Zone 2 CSM Key 0
#define DCSM_O_Z2_CSMKEY1          0x12U   // Zone 2 CSM Key 1
#define DCSM_O_Z2_CSMKEY2          0x14U   // Zone 2 CSM Key 2
#define DCSM_O_Z2_CSMKEY3          0x16U   // Zone 2 CSM Key 3
#define DCSM_O_Z2_CR               0x19U   // Zone 2 CSM Control Register
#define DCSM_O_Z2_GRABSECTR        0x1AU   // Zone 2 Grab Flash Sectors Register
#define DCSM_O_Z2_GRABRAMR         0x1CU   // Zone 2 Grab RAM Blocks Register
#define DCSM_O_Z2_EXEONLYSECTR     0x1EU   // Zone 2 Flash Execute_Only Sector Register
#define DCSM_O_Z2_EXEONLYRAMR      0x20U   // Zone 2 RAM Execute_Only Block Register

#define DCSM_O_FLSEM      0x0U   // Flash Wrapper Semaphore Register
#define DCSM_O_SECTSTAT   0x2U   // Sectors Status Register
#define DCSM_O_RAMSTAT    0x4U   // RAM Status Register




//*************************************************************************************************
//
// The following are defines for the bit fields in the Z1_LINKPOINTER register
//
//*************************************************************************************************
#define DCSM_Z1_LINKPOINTER_LINKPOINTER_S   0U
#define DCSM_Z1_LINKPOINTER_LINKPOINTER_M   0x1FFFFFFFU   // Zone1 LINK Pointer.

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
// The following are defines for the bit fields in the Z1_BOOTCTRL register
//
//*************************************************************************************************
#define DCSM_Z1_BOOTCTRL_KEY_S        0U
#define DCSM_Z1_BOOTCTRL_KEY_M        0xFFU         // OTP Boot Key
#define DCSM_Z1_BOOTCTRL_BMODE_S      8U
#define DCSM_Z1_BOOTCTRL_BMODE_M      0xFF00U       // OTP Boot Mode
#define DCSM_Z1_BOOTCTRL_BOOTPIN0_S   16U
#define DCSM_Z1_BOOTCTRL_BOOTPIN0_M   0xFF0000U     // OTP Boot Pin 0 Mapping
#define DCSM_Z1_BOOTCTRL_BOOTPIN1_S   24U
#define DCSM_Z1_BOOTCTRL_BOOTPIN1_M   0xFF000000U   // OTP Boot Pin 1 Mapping

//*************************************************************************************************
//
// The following are defines for the bit fields in the Z1_CR register
//
//*************************************************************************************************
#define DCSM_Z1_CR_ALLZERO    0x8U      // CSMPSWD All Zeros
#define DCSM_Z1_CR_ALLONE     0x10U     // CSMPSWD All Ones
#define DCSM_Z1_CR_UNSECURE   0x20U     // CSMPSWD Match CSMKEY
#define DCSM_Z1_CR_ARMED      0x40U     // CSM Armed
#define DCSM_Z1_CR_FORCESEC   0x8000U   // Force Secure

//*************************************************************************************************
//
// The following are defines for the bit fields in the Z1_GRABSECTR register
//
//*************************************************************************************************
#define DCSM_Z1_GRABSECTR_GRAB_SECTA_S   0U
#define DCSM_Z1_GRABSECTR_GRAB_SECTA_M   0x3U         // Grab Flash Sector A
#define DCSM_Z1_GRABSECTR_GRAB_SECTB_S   2U
#define DCSM_Z1_GRABSECTR_GRAB_SECTB_M   0xCU         // Grab Flash Sector B
#define DCSM_Z1_GRABSECTR_GRAB_SECTC_S   4U
#define DCSM_Z1_GRABSECTR_GRAB_SECTC_M   0x30U        // Grab Flash Sector C
#define DCSM_Z1_GRABSECTR_GRAB_SECTD_S   6U
#define DCSM_Z1_GRABSECTR_GRAB_SECTD_M   0xC0U        // Grab Flash Sector D
#define DCSM_Z1_GRABSECTR_GRAB_SECTE_S   8U
#define DCSM_Z1_GRABSECTR_GRAB_SECTE_M   0x300U       // Grab Flash Sector E
#define DCSM_Z1_GRABSECTR_GRAB_SECTF_S   10U
#define DCSM_Z1_GRABSECTR_GRAB_SECTF_M   0xC00U       // Grab Flash Sector F
#define DCSM_Z1_GRABSECTR_GRAB_SECTG_S   12U
#define DCSM_Z1_GRABSECTR_GRAB_SECTG_M   0x3000U      // Grab Flash Sector G
#define DCSM_Z1_GRABSECTR_GRAB_SECTH_S   14U
#define DCSM_Z1_GRABSECTR_GRAB_SECTH_M   0xC000U      // Grab Flash Sector H
#define DCSM_Z1_GRABSECTR_GRAB_SECTI_S   16U
#define DCSM_Z1_GRABSECTR_GRAB_SECTI_M   0x30000U     // Grab Flash Sector I
#define DCSM_Z1_GRABSECTR_GRAB_SECTJ_S   18U
#define DCSM_Z1_GRABSECTR_GRAB_SECTJ_M   0xC0000U     // Grab Flash Sector J
#define DCSM_Z1_GRABSECTR_GRAB_SECTK_S   20U
#define DCSM_Z1_GRABSECTR_GRAB_SECTK_M   0x300000U    // Grab Flash Sector K
#define DCSM_Z1_GRABSECTR_GRAB_SECTL_S   22U
#define DCSM_Z1_GRABSECTR_GRAB_SECTL_M   0xC00000U    // Grab Flash Sector L
#define DCSM_Z1_GRABSECTR_GRAB_SECTM_S   24U
#define DCSM_Z1_GRABSECTR_GRAB_SECTM_M   0x3000000U   // Grab Flash Sector M
#define DCSM_Z1_GRABSECTR_GRAB_SECTN_S   26U
#define DCSM_Z1_GRABSECTR_GRAB_SECTN_M   0xC000000U   // Grab Flash Sector N

//*************************************************************************************************
//
// The following are defines for the bit fields in the Z1_GRABRAMR register
//
//*************************************************************************************************
#define DCSM_Z1_GRABRAMR_GRAB_RAM0_S   0U
#define DCSM_Z1_GRABRAMR_GRAB_RAM0_M   0x3U          // Grab RAM LS0
#define DCSM_Z1_GRABRAMR_GRAB_RAM1_S   2U
#define DCSM_Z1_GRABRAMR_GRAB_RAM1_M   0xCU          // Grab RAM LS1
#define DCSM_Z1_GRABRAMR_GRAB_RAM2_S   4U
#define DCSM_Z1_GRABRAMR_GRAB_RAM2_M   0x30U         // Grab RAM LS2
#define DCSM_Z1_GRABRAMR_GRAB_RAM3_S   6U
#define DCSM_Z1_GRABRAMR_GRAB_RAM3_M   0xC0U         // Grab RAM LS3
#define DCSM_Z1_GRABRAMR_GRAB_RAM4_S   8U
#define DCSM_Z1_GRABRAMR_GRAB_RAM4_M   0x300U        // Grab RAM LS4
#define DCSM_Z1_GRABRAMR_GRAB_RAM5_S   10U
#define DCSM_Z1_GRABRAMR_GRAB_RAM5_M   0xC00U        // Grab RAM LS5
#define DCSM_Z1_GRABRAMR_GRAB_RAM6_S   12U
#define DCSM_Z1_GRABRAMR_GRAB_RAM6_M   0x3000U       // Grab RAM D0
#define DCSM_Z1_GRABRAMR_GRAB_RAM7_S   14U
#define DCSM_Z1_GRABRAMR_GRAB_RAM7_M   0xC000U       // Grab RAM D1
#define DCSM_Z1_GRABRAMR_GRAB_CLA1_S   28U
#define DCSM_Z1_GRABRAMR_GRAB_CLA1_M   0x30000000U   // Grab CLA1

//*************************************************************************************************
//
// The following are defines for the bit fields in the Z1_EXEONLYSECTR register
//
//*************************************************************************************************
#define DCSM_Z1_EXEONLYSECTR_EXEONLY_SECTA   0x1U      // Execute-Only Flash Sector A
#define DCSM_Z1_EXEONLYSECTR_EXEONLY_SECTB   0x2U      // Execute-Only Flash Sector B
#define DCSM_Z1_EXEONLYSECTR_EXEONLY_SECTC   0x4U      // Execute-Only Flash Sector C
#define DCSM_Z1_EXEONLYSECTR_EXEONLY_SECTD   0x8U      // Execute-Only Flash Sector D
#define DCSM_Z1_EXEONLYSECTR_EXEONLY_SECTE   0x10U     // Execute-Only Flash Sector E
#define DCSM_Z1_EXEONLYSECTR_EXEONLY_SECTF   0x20U     // Execute-Only Flash Sector F
#define DCSM_Z1_EXEONLYSECTR_EXEONLY_SECTG   0x40U     // Execute-Only Flash Sector G
#define DCSM_Z1_EXEONLYSECTR_EXEONLY_SECTH   0x80U     // Execute-Only Flash Sector H
#define DCSM_Z1_EXEONLYSECTR_EXEONLY_SECTI   0x100U    // Execute-Only Flash Sector I
#define DCSM_Z1_EXEONLYSECTR_EXEONLY_SECTJ   0x200U    // Execute-Only Flash Sector J
#define DCSM_Z1_EXEONLYSECTR_EXEONLY_SECTK   0x400U    // Execute-Only Flash Sector K
#define DCSM_Z1_EXEONLYSECTR_EXEONLY_SECTL   0x800U    // Execute-Only Flash Sector L
#define DCSM_Z1_EXEONLYSECTR_EXEONLY_SECTM   0x1000U   // Execute-Only Flash Sector M
#define DCSM_Z1_EXEONLYSECTR_EXEONLY_SECTN   0x2000U   // Execute-Only Flash Sector N

//*************************************************************************************************
//
// The following are defines for the bit fields in the Z1_EXEONLYRAMR register
//
//*************************************************************************************************
#define DCSM_Z1_EXEONLYRAMR_EXEONLY_RAM0   0x1U    // Execute-Only RAM LS0
#define DCSM_Z1_EXEONLYRAMR_EXEONLY_RAM1   0x2U    // Execute-Only RAM LS1
#define DCSM_Z1_EXEONLYRAMR_EXEONLY_RAM2   0x4U    // Execute-Only RAM LS2
#define DCSM_Z1_EXEONLYRAMR_EXEONLY_RAM3   0x8U    // Execute-Only RAM LS3
#define DCSM_Z1_EXEONLYRAMR_EXEONLY_RAM4   0x10U   // Execute-Only RAM LS4
#define DCSM_Z1_EXEONLYRAMR_EXEONLY_RAM5   0x20U   // Execute-Only RAM LS5
#define DCSM_Z1_EXEONLYRAMR_EXEONLY_RAM6   0x40U   // Execute-Only RAM D0
#define DCSM_Z1_EXEONLYRAMR_EXEONLY_RAM7   0x80U   // Execute-Only RAM D1


//*************************************************************************************************
//
// The following are defines for the bit fields in the Z2_LINKPOINTER register
//
//*************************************************************************************************
#define DCSM_Z2_LINKPOINTER_LINKPOINTER_S   0U
#define DCSM_Z2_LINKPOINTER_LINKPOINTER_M   0x1FFFFFFFU   // Zone2 LINK Pointer.

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
// The following are defines for the bit fields in the Z2_BOOTCTRL register
//
//*************************************************************************************************
#define DCSM_Z2_BOOTCTRL_KEY_S        0U
#define DCSM_Z2_BOOTCTRL_KEY_M        0xFFU         // OTP Boot Key
#define DCSM_Z2_BOOTCTRL_BMODE_S      8U
#define DCSM_Z2_BOOTCTRL_BMODE_M      0xFF00U       // OTP Boot Mode
#define DCSM_Z2_BOOTCTRL_BOOTPIN0_S   16U
#define DCSM_Z2_BOOTCTRL_BOOTPIN0_M   0xFF0000U     // OTP Boot Pin 0 Mapping
#define DCSM_Z2_BOOTCTRL_BOOTPIN1_S   24U
#define DCSM_Z2_BOOTCTRL_BOOTPIN1_M   0xFF000000U   // OTP Boot Pin 1 Mapping

//*************************************************************************************************
//
// The following are defines for the bit fields in the Z2_CR register
//
//*************************************************************************************************
#define DCSM_Z2_CR_ALLZERO    0x8U      // CSMPSWD All Zeros
#define DCSM_Z2_CR_ALLONE     0x10U     // CSMPSWD All Ones
#define DCSM_Z2_CR_UNSECURE   0x20U     // CSMPSWD Match CSMKEY
#define DCSM_Z2_CR_ARMED      0x40U     // CSM Armed
#define DCSM_Z2_CR_FORCESEC   0x8000U   // Force Secure

//*************************************************************************************************
//
// The following are defines for the bit fields in the Z2_GRABSECTR register
//
//*************************************************************************************************
#define DCSM_Z2_GRABSECTR_GRAB_SECTA_S   0U
#define DCSM_Z2_GRABSECTR_GRAB_SECTA_M   0x3U         // Grab Flash Sector A
#define DCSM_Z2_GRABSECTR_GRAB_SECTB_S   2U
#define DCSM_Z2_GRABSECTR_GRAB_SECTB_M   0xCU         // Grab Flash Sector B
#define DCSM_Z2_GRABSECTR_GRAB_SECTC_S   4U
#define DCSM_Z2_GRABSECTR_GRAB_SECTC_M   0x30U        // Grab Flash Sector C
#define DCSM_Z2_GRABSECTR_GRAB_SECTD_S   6U
#define DCSM_Z2_GRABSECTR_GRAB_SECTD_M   0xC0U        // Grab Flash Sector D
#define DCSM_Z2_GRABSECTR_GRAB_SECTE_S   8U
#define DCSM_Z2_GRABSECTR_GRAB_SECTE_M   0x300U       // Grab Flash Sector E
#define DCSM_Z2_GRABSECTR_GRAB_SECTF_S   10U
#define DCSM_Z2_GRABSECTR_GRAB_SECTF_M   0xC00U       // Grab Flash Sector F
#define DCSM_Z2_GRABSECTR_GRAB_SECTG_S   12U
#define DCSM_Z2_GRABSECTR_GRAB_SECTG_M   0x3000U      // Grab Flash Sector G
#define DCSM_Z2_GRABSECTR_GRAB_SECTH_S   14U
#define DCSM_Z2_GRABSECTR_GRAB_SECTH_M   0xC000U      // Grab Flash Sector H
#define DCSM_Z2_GRABSECTR_GRAB_SECTI_S   16U
#define DCSM_Z2_GRABSECTR_GRAB_SECTI_M   0x30000U     // Grab Flash Sector I
#define DCSM_Z2_GRABSECTR_GRAB_SECTJ_S   18U
#define DCSM_Z2_GRABSECTR_GRAB_SECTJ_M   0xC0000U     // Grab Flash Sector J
#define DCSM_Z2_GRABSECTR_GRAB_SECTK_S   20U
#define DCSM_Z2_GRABSECTR_GRAB_SECTK_M   0x300000U    // Grab Flash Sector K
#define DCSM_Z2_GRABSECTR_GRAB_SECTL_S   22U
#define DCSM_Z2_GRABSECTR_GRAB_SECTL_M   0xC00000U    // Grab Flash Sector L
#define DCSM_Z2_GRABSECTR_GRAB_SECTM_S   24U
#define DCSM_Z2_GRABSECTR_GRAB_SECTM_M   0x3000000U   // Grab Flash Sector M
#define DCSM_Z2_GRABSECTR_GRAB_SECTN_S   26U
#define DCSM_Z2_GRABSECTR_GRAB_SECTN_M   0xC000000U   // Grab Flash Sector N

//*************************************************************************************************
//
// The following are defines for the bit fields in the Z2_GRABRAMR register
//
//*************************************************************************************************
#define DCSM_Z2_GRABRAMR_GRAB_RAM0_S   0U
#define DCSM_Z2_GRABRAMR_GRAB_RAM0_M   0x3U          // Grab RAM LS0
#define DCSM_Z2_GRABRAMR_GRAB_RAM1_S   2U
#define DCSM_Z2_GRABRAMR_GRAB_RAM1_M   0xCU          // Grab RAM LS1
#define DCSM_Z2_GRABRAMR_GRAB_RAM2_S   4U
#define DCSM_Z2_GRABRAMR_GRAB_RAM2_M   0x30U         // Grab RAM LS2
#define DCSM_Z2_GRABRAMR_GRAB_RAM3_S   6U
#define DCSM_Z2_GRABRAMR_GRAB_RAM3_M   0xC0U         // Grab RAM LS3
#define DCSM_Z2_GRABRAMR_GRAB_RAM4_S   8U
#define DCSM_Z2_GRABRAMR_GRAB_RAM4_M   0x300U        // Grab RAM LS4
#define DCSM_Z2_GRABRAMR_GRAB_RAM5_S   10U
#define DCSM_Z2_GRABRAMR_GRAB_RAM5_M   0xC00U        // Grab RAM LS5
#define DCSM_Z2_GRABRAMR_GRAB_RAM6_S   12U
#define DCSM_Z2_GRABRAMR_GRAB_RAM6_M   0x3000U       // Grab RAM D0
#define DCSM_Z2_GRABRAMR_GRAB_RAM7_S   14U
#define DCSM_Z2_GRABRAMR_GRAB_RAM7_M   0xC000U       // Grab RAM D1
#define DCSM_Z2_GRABRAMR_GRAB_CLA1_S   28U
#define DCSM_Z2_GRABRAMR_GRAB_CLA1_M   0x30000000U   // Grab CLA1

//*************************************************************************************************
//
// The following are defines for the bit fields in the Z2_EXEONLYSECTR register
//
//*************************************************************************************************
#define DCSM_Z2_EXEONLYSECTR_EXEONLY_SECTA   0x1U      // Execute-Only Flash Sector A
#define DCSM_Z2_EXEONLYSECTR_EXEONLY_SECTB   0x2U      // Execute-Only Flash Sector B
#define DCSM_Z2_EXEONLYSECTR_EXEONLY_SECTC   0x4U      // Execute-Only Flash Sector C
#define DCSM_Z2_EXEONLYSECTR_EXEONLY_SECTD   0x8U      // Execute-Only Flash Sector D
#define DCSM_Z2_EXEONLYSECTR_EXEONLY_SECTE   0x10U     // Execute-Only Flash Sector E
#define DCSM_Z2_EXEONLYSECTR_EXEONLY_SECTF   0x20U     // Execute-Only Flash Sector F
#define DCSM_Z2_EXEONLYSECTR_EXEONLY_SECTG   0x40U     // Execute-Only Flash Sector G
#define DCSM_Z2_EXEONLYSECTR_EXEONLY_SECTH   0x80U     // Execute-Only Flash Sector H
#define DCSM_Z2_EXEONLYSECTR_EXEONLY_SECTI   0x100U    // Execute-Only Flash Sector I
#define DCSM_Z2_EXEONLYSECTR_EXEONLY_SECTJ   0x200U    // Execute-Only Flash Sector J
#define DCSM_Z2_EXEONLYSECTR_EXEONLY_SECTK   0x400U    // Execute-Only Flash Sector K
#define DCSM_Z2_EXEONLYSECTR_EXEONLY_SECTL   0x800U    // Execute-Only Flash Sector L
#define DCSM_Z2_EXEONLYSECTR_EXEONLY_SECTM   0x1000U   // Execute-Only Flash Sector M
#define DCSM_Z2_EXEONLYSECTR_EXEONLY_SECTN   0x2000U   // Execute-Only Flash Sector N

//*************************************************************************************************
//
// The following are defines for the bit fields in the Z2_EXEONLYRAMR register
//
//*************************************************************************************************
#define DCSM_Z2_EXEONLYRAMR_EXEONLY_RAM0   0x1U    // Execute-Only RAM LS0
#define DCSM_Z2_EXEONLYRAMR_EXEONLY_RAM1   0x2U    // Execute-Only RAM LS1
#define DCSM_Z2_EXEONLYRAMR_EXEONLY_RAM2   0x4U    // Execute-Only RAM LS2
#define DCSM_Z2_EXEONLYRAMR_EXEONLY_RAM3   0x8U    // Execute-Only RAM LS3
#define DCSM_Z2_EXEONLYRAMR_EXEONLY_RAM4   0x10U   // Execute-Only RAM LS4
#define DCSM_Z2_EXEONLYRAMR_EXEONLY_RAM5   0x20U   // Execute-Only RAM LS5
#define DCSM_Z2_EXEONLYRAMR_EXEONLY_RAM6   0x40U   // Execute-Only RAM D0
#define DCSM_Z2_EXEONLYRAMR_EXEONLY_RAM7   0x80U   // Execute-Only RAM D1


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
// The following are defines for the bit fields in the SECTSTAT register
//
//*************************************************************************************************
#define DCSM_SECTSTAT_STATUS_SECTA_S   0U
#define DCSM_SECTSTAT_STATUS_SECTA_M   0x3U         // Zone Status Flash Sector A
#define DCSM_SECTSTAT_STATUS_SECTB_S   2U
#define DCSM_SECTSTAT_STATUS_SECTB_M   0xCU         // Zone Status Flash Sector B
#define DCSM_SECTSTAT_STATUS_SECTC_S   4U
#define DCSM_SECTSTAT_STATUS_SECTC_M   0x30U        // Zone Status Flash Sector C
#define DCSM_SECTSTAT_STATUS_SECTD_S   6U
#define DCSM_SECTSTAT_STATUS_SECTD_M   0xC0U        // Zone Status Flash Sector D
#define DCSM_SECTSTAT_STATUS_SECTE_S   8U
#define DCSM_SECTSTAT_STATUS_SECTE_M   0x300U       // Zone Status Flash Sector E
#define DCSM_SECTSTAT_STATUS_SECTF_S   10U
#define DCSM_SECTSTAT_STATUS_SECTF_M   0xC00U       // Zone Status Flash Sector F
#define DCSM_SECTSTAT_STATUS_SECTG_S   12U
#define DCSM_SECTSTAT_STATUS_SECTG_M   0x3000U      // Zone Status Flash Sector G
#define DCSM_SECTSTAT_STATUS_SECTH_S   14U
#define DCSM_SECTSTAT_STATUS_SECTH_M   0xC000U      // Zone Status Flash Sector H
#define DCSM_SECTSTAT_STATUS_SECTI_S   16U
#define DCSM_SECTSTAT_STATUS_SECTI_M   0x30000U     // Zone Status Flash Sector I
#define DCSM_SECTSTAT_STATUS_SECTJ_S   18U
#define DCSM_SECTSTAT_STATUS_SECTJ_M   0xC0000U     // Zone Status Flash Sector J
#define DCSM_SECTSTAT_STATUS_SECTK_S   20U
#define DCSM_SECTSTAT_STATUS_SECTK_M   0x300000U    // Zone Status Flash Sector K
#define DCSM_SECTSTAT_STATUS_SECTL_S   22U
#define DCSM_SECTSTAT_STATUS_SECTL_M   0xC00000U    // Zone Status Flash Sector L
#define DCSM_SECTSTAT_STATUS_SECTM_S   24U
#define DCSM_SECTSTAT_STATUS_SECTM_M   0x3000000U   // Zone Status Flash Sector M
#define DCSM_SECTSTAT_STATUS_SECTN_S   26U
#define DCSM_SECTSTAT_STATUS_SECTN_M   0xC000000U   // Zone Status Flash Sector N

//*************************************************************************************************
//
// The following are defines for the bit fields in the RAMSTAT register
//
//*************************************************************************************************
#define DCSM_RAMSTAT_STATUS_RAM0_S   0U
#define DCSM_RAMSTAT_STATUS_RAM0_M   0x3U          // Zone Status RAM LS0
#define DCSM_RAMSTAT_STATUS_RAM1_S   2U
#define DCSM_RAMSTAT_STATUS_RAM1_M   0xCU          // Zone Status RAM LS1
#define DCSM_RAMSTAT_STATUS_RAM2_S   4U
#define DCSM_RAMSTAT_STATUS_RAM2_M   0x30U         // Zone Status RAM LS2
#define DCSM_RAMSTAT_STATUS_RAM3_S   6U
#define DCSM_RAMSTAT_STATUS_RAM3_M   0xC0U         // Zone Status RAM LS3
#define DCSM_RAMSTAT_STATUS_RAM4_S   8U
#define DCSM_RAMSTAT_STATUS_RAM4_M   0x300U        // Zone Status RAM LS4
#define DCSM_RAMSTAT_STATUS_RAM5_S   10U
#define DCSM_RAMSTAT_STATUS_RAM5_M   0xC00U        // Zone Status RAM LS5
#define DCSM_RAMSTAT_STATUS_RAM6_S   12U
#define DCSM_RAMSTAT_STATUS_RAM6_M   0x3000U       // Zone Status RAM D0
#define DCSM_RAMSTAT_STATUS_RAM7_S   14U
#define DCSM_RAMSTAT_STATUS_RAM7_M   0xC000U       // Zone Status RAM D1
#define DCSM_RAMSTAT_STATUS_CLA1_S   28U
#define DCSM_RAMSTAT_STATUS_CLA1_M   0x30000000U   // Zone Status CLA1



#endif
