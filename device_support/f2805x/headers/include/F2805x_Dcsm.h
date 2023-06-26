//###########################################################################
//
// FILE:   F2805x_Dcsm.h
//
// TITLE:  F2805x Device DCSM Register Definitions.
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:
// Copyright (C) 2012-2023 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef F2805x_DCSM_H
#define F2805x_DCSM_H

#ifdef __cplusplus
extern "C" {
#endif


//
// DCSM Individual Register Bit Definitions:

struct OTPSECLOCK_BITS {                            // bits description
    Uint16  JTAGLOCK:4;                             // 3:0 JTAG Lock Bits
    Uint16  rsvd1:12;                               // 15:4 Reserved
    Uint16  rsvd2:16;                               // 31:16 Reserved
};

union OTPSECLOCK_REG {
    Uint32  all;
    struct  OTPSECLOCK_BITS  bit;
};

struct BOOTMODE_BITS {                              // bits description
    Uint16  OTP_KEY:16;                             // 15:0 OTP Boot Key
    Uint16  OTP_BMODE:16;                           // 31:16 OTP Boot Mode
};

union BOOTMODE_REG {
    Uint32  all;
    struct  BOOTMODE_BITS  bit;
};

struct CR_BITS {                                    // bits description
    Uint16  rsvd1:3;                                // 2:0 Reserved
    Uint16  ALLZERO:1;                              // 3 CSMPSWD All Zeros
    Uint16  ALLONE:1;                               // 4 CSMPSWD All Ones
    Uint16  MATCH:1;                                // 5 CSMPSWD Match CSMKEY
    Uint16  ARMED:1;                                // 6 CSM Armed
    Uint16  rsvd2:1;                                // 7 Reserved
    Uint16  rsvd3:7;                                // 14:8 Reserved
    Uint16  FORCESEC:1;                             // 15 Force Secure
};

union CR_REG {
    Uint16  all;
    struct  CR_BITS  bit;
};

struct GRABSECTR_BITS {                          // bits description
    Uint16  GRAB_SECT0:2;                        // 1:0 Grab Flash Sector 0
    Uint16  GRAB_SECT1:2;                        // 3:2 Grab Flash Sector 1
    Uint16  GRAB_SECT2:2;                        // 5:4 Grab Flash Sector 2
    Uint16  GRAB_SECT3:2;                        // 7:6 Grab Flash Sector 3
    Uint16  GRAB_SECT4:2;                        // 9:8 Grab Flash Sector 4
    Uint16  GRAB_SECT5:2;                        // 11:10 Grab Flash Sector 5
    Uint16  GRAB_SECT6:2;                        // 13:12 Grab Flash Sector 6
    Uint16  GRAB_SECT7:2;                        // 15:14 Grab Flash Sector 7
    Uint16  GRAB_SECT8:2;                        // 17:16 Grab Flash Sector 8
    Uint16  GRAB_SECT9:2;                        // 19:18 Grab Flash Sector 9
    Uint16  rsvd1:12;                            // 31:20 Reserved
};

union GRABSECTR_REG {
    Uint32  all;
    struct  GRABSECTR_BITS  bit;
};

struct GRABRAMR_BITS {                              // bits description
    Uint16  GRAB_RAM0:2;                            // 1:0 Grab RAM L0
    Uint16  GRAB_RAM1:2;                            // 3:2 Grab RAM L1
    Uint16  GRAB_RAM2:2;                            // 5:4 Grab RAM L2
    Uint16  GRAB_RAM3:2;                            // 7:6 Grab RAM L3
    Uint16  rsvd1:8;                                // 15:8 Reserved
    Uint16  rsvd2:16;                               // 31:16 Reserved
};

union GRABRAMR_REG {
    Uint32  all;
    struct  GRABRAMR_BITS  bit;
};

struct EXEONLYSECTR_BITS {                    // bits description
    Uint16  EXEONLY_SECT0:1;                  // 0 Execute-Only Flash Sector 0
    Uint16  EXEONLY_SECT1:1;                  // 1 Execute-Only Flash Sector 1
    Uint16  EXEONLY_SECT2:1;                  // 2 Execute-Only Flash Sector 2
    Uint16  EXEONLY_SECT3:1;                  // 3 Execute-Only Flash Sector 3
    Uint16  EXEONLY_SECT4:1;                  // 4 Execute-Only Flash Sector 4
    Uint16  EXEONLY_SECT5:1;                  // 5 Execute-Only Flash Sector 5
    Uint16  EXEONLY_SECT6:1;                  // 6 Execute-Only Flash Sector 6
    Uint16  EXEONLY_SECT7:1;                  // 7 Execute-Only Flash Sector 7
    Uint16  EXEONLY_SECT8:1;                  // 8 Execute-Only Flash Sector 8
    Uint16  EXEONLY_SECT9:1;                  // 9 Execute-Only Flash Sector 9
    Uint16  rsvd1:6;                          // 15:10 Reserved
    Uint16  rsvd2:16;                         // 31:16 Reserved
};

union EXEONLYSECTR_REG {
    Uint32  all;
    struct  EXEONLYSECTR_BITS  bit;
};

struct EXEONLYRAMR_BITS {                           // bits description
    Uint16  EXEONLY_RAM0:1;                         // 0 Execute-Only RAM L0
    Uint16  EXEONLY_RAM1:1;                         // 1 Execute-Only RAM L1
    Uint16  EXEONLY_RAM2:1;                         // 2 Execute-Only RAM L2
    Uint16  EXEONLY_RAM3:1;                         // 3 Execute-Only RAM L3
    Uint16  rsvd1:12;                               // 15:4 Reserved
    Uint16  rsvd2:16;                               // 31:16 Reserved
};

union EXEONLYRAMR_REG {
    Uint32  all;
    struct  EXEONLYRAMR_BITS  bit;
};

struct FLSEM_BITS {                                 // bits description
    Uint16  SEM:2;                                  // 1:0 Flash Semaphore Bit
    Uint16  rsvd1:6;                                // 7:2 Reserved
    Uint16  KEY:8;                                  // 15:8 Semaphore Key
    Uint16  rsvd2:16;                               // 31:16 Reserved
};

union FLSEM_REG {
    Uint32  all;
    struct  FLSEM_BITS  bit;
};

struct SECTSTAT_BITS {                      // bits description
    Uint16  STATUS_SECT0:2;                 // 1:0 Zone Status Flash Sector 0
    Uint16  STATUS_SECT1:2;                 // 3:2 Zone Status Flash Sector 1
    Uint16  STATUS_SECT2:2;                 // 5:4 Zone Status Flash Sector 2
    Uint16  STATUS_SECT3:2;                 // 7:6 Zone Status Flash Sector 3
    Uint16  STATUS_SECT4:2;                 // 9:8 Zone Status Flash Sector 4
    Uint16  STATUS_SECT5:2;                 // 11:10 Zone Status Flash Sector 5
    Uint16  STATUS_SECT6:2;                 // 13:12 Zone Status Flash Sector 6
    Uint16  STATUS_SECT7:2;                 // 15:14 Zone Status Flash Sector 7
    Uint16  STATUS_SECT8:2;                 // 17:16 Zone Status Flash Sector 8
    Uint16  STATUS_SECT9:2;                 // 19:18 Zone Status Flash Sector 9
    Uint16  rsvd1:12;                       // 31:20 Reserved
};

union SECTSTAT_REG {
    Uint32  all;
    struct  SECTSTAT_BITS  bit;
};

struct RAMSTAT_BITS {                               // bits description
    Uint16  STATUS_RAM0:2;                          // 1:0 Zone Status RAM L0
    Uint16  STATUS_RAM1:2;                          // 3:2 Zone Status RAM L1
    Uint16  STATUS_RAM2:2;                          // 5:4 Zone Status RAM L2
    Uint16  STATUS_RAM3:2;                          // 7:6 Zone Status RAM L3
    Uint16  rsvd1:8;                                // 15:8 Reserved
    Uint16  rsvd2:16;                               // 31:16 Reserved
};

union RAMSTAT_REG {
    Uint32  all;
    struct  RAMSTAT_BITS  bit;
};

struct DCSM_OTP_Z1 {
    Uint32  Z1_LINKPOINTER;                    // Zone 1 Link Pointer in Z1 OTP
    union  OTPSECLOCK_REG  OTPSECLOCK;         // Secure JTAG Lock in Z1 OTP
    union  BOOTMODE_REG  BOOTMODE;             // Boot Mode in Z1 OTP
};

struct DCSM_OTP_Z2 {
    Uint32  Z2_LINKPOINTER;                    // Zone 1 Link Pointer in Z2 OTP
    union  OTPSECLOCK_REG  OTPSECLOCK;         // Secure JTAG Lock in Z2 OTP
    union  BOOTMODE_REG  BOOTMODE;             // Boot Mode in Z2 OTP
};

struct DCSM_REGS_Z1 {
    Uint32                      Z1_LINKPOINTER;  // Zone 1 Link Pointer
    union   OTPSECLOCK_REG      Z1_OTPSECLOCK;   // Zone 1 OTP Secure JTAG lock
    union   BOOTMODE_REG        BOOTMODE;        // Boot Mode
    Uint16                      rsvd1[10];       // Reserved
    Uint32                      Z1_CSMKEY0;      // Zone 1 CSM Key 0
    Uint32                      Z1_CSMKEY1;      // Zone 1 CSM Key 1
    Uint32                      Z1_CSMKEY2;      // Zone 1 CSM Key 2
    Uint32                      Z1_CSMKEY3;      // Zone 1 CSM Key 3
    Uint16                      rsvd2;           // Reserved
    union   CR_REG              Z1_CR;           // Zone 1 CSM Control Reg.
    union   GRABSECTR_REG       Z1_GRABSECTR;    // Zone 1 Grab Flash Sectors
    union   GRABRAMR_REG        Z1_GRABRAMR;     // Zone 1 Grab RAM Blocks
    union   EXEONLYSECTR_REG    Z1_EXEONLYSECTR; // Zone 1 Flash Execute_Only
    union   EXEONLYRAMR_REG     Z1_EXEONLYRAMR;  // Zone 1 RAM Execute_Only
    Uint16                      rsvd3;           // Reserved
};

struct DCSM_REGS_Z2 {
    Uint32                      Z2_LINKPOINTER;  // Zone 2 Link Pointer
    union   OTPSECLOCK_REG      Z2_OTPSECLOCK;   // Zone 2 OTP Secure JTAG lock
    union   BOOTMODE_REG        BOOTMODE;        // Boot Mode
    Uint16                      rsvd1[10];       // Reserved
    Uint32                      Z2_CSMKEY0;      // Zone 2 CSM Key 0
    Uint32                      Z2_CSMKEY1;      // Zone 2 CSM Key 1
    Uint32                      Z2_CSMKEY2;      // Zone 2 CSM Key 2
    Uint32                      Z2_CSMKEY3;      // Zone 2 CSM Key 3
    Uint16                      rsvd2;           // Reserved
    union   CR_REG              Z2_CR;           // Zone 2 CSM Control Reg.
    union   GRABSECTR_REG       Z2_GRABSECTR;    // Zone 2 Grab Flash Sectors
    union   GRABRAMR_REG        Z2_GRABRAMR;     // Zone 2 Grab RAM Blocks
    union   EXEONLYSECTR_REG    Z2_EXEONLYSECTR; // Zone 2 Flash Execute_Only
    union   EXEONLYRAMR_REG     Z2_EXEONLYRAMR;  // Zone 2 RAM Execute_Only
    Uint16                      rsvd3;           // Reserved
};

struct DCSM_REGS_COMMON {
    union   FLSEM_REG           FLSEM;      // Flash Wrapper Semaphore Register
    union   SECTSTAT_REG        SECTSTAT;   // Sectors Status Register
    union   RAMSTAT_REG         RAMSTAT;    // RAM Status Register
    Uint16                      rsvd1;      // Reserved
};

//
// Dcsm External References & Function Declarations:
//
extern volatile struct DCSM_OTP_Z1 DcsmOtpZ1;
extern volatile struct DCSM_OTP_Z2 DcsmOtpZ2;
extern volatile struct DCSM_REGS_Z1 DcsmRegsZ1;
extern volatile struct DCSM_REGS_Z2 DcsmRegsZ2;
extern volatile struct DCSM_REGS_COMMON DcsmRegsCommon;

#ifdef __cplusplus
}
#endif                                 /* extern "C" */


#endif                                 // end of F2805x_DCSM_H definition
//
// End of file
//
