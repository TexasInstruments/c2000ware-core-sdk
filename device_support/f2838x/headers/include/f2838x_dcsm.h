//###########################################################################
//
// FILE:    f2838x_dcsm.h
//
// TITLE:   Definitions for the DCSM registers.
//
//###########################################################################
// 
// C2000Ware v6.00.01.00
//
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
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

#ifndef F2838X_DCSM_H
#define F2838X_DCSM_H

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// DCSM Individual Register Bit Definitions:

struct DCSM_Z1_OTP {
    Uint32                                   Z1OTP_LINKPOINTER1;           // Zone 1 Link Pointer1
    Uint32                                   Z1OTP_LINKPOINTER2;           // Zone 1 Link Pointer2
    Uint32                                   Z1OTP_LINKPOINTER3;           // Zone 1 Link Pointer3
    Uint32                                   Z1OTP_JLM_ENABLE;             // Zone 1 JTAGLOCK Enable Register
    Uint32                                   Z1OTP_GPREG1;                 // Zone 1 General Purpose Register 1
    Uint32                                   Z1OTP_GPREG2;                 // Zone 1 General Purpose Register 2
    Uint32                                   Z1OTP_GPREG3;                 // Zone 1 General Purpose Register 3
    Uint32                                   Z1OTP_GPREG4;                 // Zone 1 General Purpose Register 4
    Uint32                                   Z1OTP_PSWDLOCK;               // Secure Password Lock
    Uint32                                   Z1OTP_CRCLOCK;                // Secure CRC Lock
    Uint32                                   Z1OTP_JTAGPSWDH0;             // JTAG Lock Permanent Password 0
    Uint32                                   Z1OTP_JTAGPSWDH1;             // JTAG Lock Permanent Password 1
    Uint32                                   Z1OTP_CMACKEY0;               // Secure Boot CMAC Key 0
    Uint32                                   Z1OTP_CMACKEY1;               // Secure Boot CMAC Key 1
    Uint32                                   Z1OTP_CMACKEY2;               // Secure Boot CMAC Key 2
    Uint32                                   Z1OTP_CMACKEY3;               // Secure Boot CMAC Key 3
};

struct DCSM_Z2_OTP {
    Uint32                                   Z2OTP_LINKPOINTER1;           // Zone 2 Link Pointer1
    Uint32                                   Z2OTP_LINKPOINTER2;           // Zone 2 Link Pointer2
    Uint32                                   Z2OTP_LINKPOINTER3;           // Zone 2 Link Pointer3
    Uint16                                   rsvd1[2];                     // Reserved
    Uint32                                   Z2OTP_GPREG1;                 // Zone 2 General Purpose Register 1
    Uint32                                   Z2OTP_GPREG2;                 // Zone 2 General Purpose Register 2
    Uint32                                   Z2OTP_GPREG3;                 // Zone 2 General Purpose Register 3
    Uint32                                   Z2OTP_GPREG4;                 // Zone 2 General Purpose Register 4
    Uint32                                   Z2OTP_PSWDLOCK;               // Secure Password Lock
    Uint32                                   Z2OTP_CRCLOCK;                // Secure CRC Lock
};

struct Z1_LINKPOINTER_BITS {            // bits description
    Uint16 LINKPOINTER:14;              // 13:0 Zone1 LINK Pointer
    Uint16 rsvd1:2;                     // 15:14 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union Z1_LINKPOINTER_REG {
    Uint32  all;
    struct  Z1_LINKPOINTER_BITS  bit;
};

struct Z1_OTPSECLOCK_BITS {             // bits description
    Uint16 JTAGLOCK:1;                  // 0 JTAG Lock Status
    Uint16 rsvd1:3;                     // 3:1 Reserved
    Uint16 PSWDLOCK:4;                  // 7:4 Zone1 Password Lock.
    Uint16 CRCLOCK:4;                   // 11:8 Zone1 CRC Lock.
    Uint16 rsvd2:4;                     // 15:12 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union Z1_OTPSECLOCK_REG {
    Uint32  all;
    struct  Z1_OTPSECLOCK_BITS  bit;
};

struct Z1_JLM_ENABLE_BITS {             // bits description
    Uint16 Z1_JLM_ENABLE:4;             // 3:0 Zone1 JLM_ENABLE register.
    Uint16 rsvd1:12;                    // 15:4 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union Z1_JLM_ENABLE_REG {
    Uint32  all;
    struct  Z1_JLM_ENABLE_BITS  bit;
};

struct Z1_LINKPOINTERERR_BITS {         // bits description
    Uint16 Z1_LINKPOINTERERR:14;        // 13:0 Error to Resolve Z1 Link pointer from OTP loaded values
    Uint16 rsvd1:2;                     // 15:14 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union Z1_LINKPOINTERERR_REG {
    Uint32  all;
    struct  Z1_LINKPOINTERERR_BITS  bit;
};

struct Z1_CR_BITS {                     // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 rsvd2:1;                     // 1 Reserved
    Uint16 rsvd3:1;                     // 2 Reserved
    Uint16 rsvd4:1;                     // 3 Reserved
    Uint16 rsvd5:12;                    // 15:4 Reserved
    Uint16 rsvd6:3;                     // 18:16 Reserved
    Uint16 ALLZERO:1;                   // 19 CSMPSWD All Zeros
    Uint16 ALLONE:1;                    // 20 CSMPSWD All Ones
    Uint16 UNSECURE:1;                  // 21 CSMPSWD Match CSMKEY
    Uint16 ARMED:1;                     // 22 CSM Passwords Read Status
    Uint16 rsvd7:1;                     // 23 Reserved
    Uint16 rsvd8:7;                     // 30:24 Reserved
    Uint16 FORCESEC:1;                  // 31 Force Secure
};

union Z1_CR_REG {
    Uint32  all;
    struct  Z1_CR_BITS  bit;
};

struct Z1_GRABSECT1R_BITS {             // bits description
    Uint16 GRAB_SECT0:2;                // 1:0 Grab Flash Sector 0 in CPU1 BANK
    Uint16 GRAB_SECT1:2;                // 3:2 Grab Flash Sector 1 in CPU1 BANK
    Uint16 GRAB_SECT2:2;                // 5:4 Grab Flash Sector 2 in CPU1 BANK
    Uint16 GRAB_SECT3:2;                // 7:6 Grab Flash Sector 3 in CPU1 BANK
    Uint16 GRAB_SECT4:2;                // 9:8 Grab Flash Sector 4 in CPU1 BANK
    Uint16 GRAB_SECT5:2;                // 11:10 Grab Flash Sector 5 in CPU1 BANK
    Uint16 GRAB_SECT6:2;                // 13:12 Grab Flash Sector 6 in CPU1 BANK
    Uint16 GRAB_SECT7:2;                // 15:14 Grab Flash Sector 7 in CPU1 BANK
    Uint16 GRAB_SECT8:2;                // 17:16 Grab Flash Sector 8 in CPU1 BANK
    Uint16 GRAB_SECT9:2;                // 19:18 Grab Flash Sector 9 in CPU1 BANK
    Uint16 GRAB_SECT10:2;               // 21:20 Grab Flash Sector 10 in CPU1 BANK
    Uint16 GRAB_SECT11:2;               // 23:22 Grab Flash Sector 11 in CPU1 BANK
    Uint16 GRAB_SECT12:2;               // 25:24 Grab Flash Sector 12 in CPU1 BANK
    Uint16 GRAB_SECT13:2;               // 27:26 Grab Flash Sector 13 in CPU1 BANK
    Uint16 rsvd1:4;                     // 31:28 Reserved
};

union Z1_GRABSECT1R_REG {
    Uint32  all;
    struct  Z1_GRABSECT1R_BITS  bit;
};

struct Z1_GRABSECT2R_BITS {             // bits description
    Uint16 GRAB_SECT0:2;                // 1:0 Grab Flash Sector 0 in CM BANK
    Uint16 GRAB_SECT1:2;                // 3:2 Grab Flash Sector 1 in CM BANK
    Uint16 GRAB_SECT2:2;                // 5:4 Grab Flash Sector 2 in CM BANK
    Uint16 GRAB_SECT3:2;                // 7:6 Grab Flash Sector 3 in CM BANK
    Uint16 GRAB_SECT4:2;                // 9:8 Grab Flash Sector 4 in CM BANK
    Uint16 GRAB_SECT5:2;                // 11:10 Grab Flash Sector 5 in CM BANK
    Uint16 GRAB_SECT6:2;                // 13:12 Grab Flash Sector 6 in CM BANK
    Uint16 GRAB_SECT7:2;                // 15:14 Grab Flash Sector 7 in CM BANK
    Uint16 GRAB_SECT8:2;                // 17:16 Grab Flash Sector 8 in CM BANK
    Uint16 GRAB_SECT9:2;                // 19:18 Grab Flash Sector 9 in CM BANK
    Uint16 GRAB_SECT10:2;               // 21:20 Grab Flash Sector 10 in CM BANK
    Uint16 GRAB_SECT11:2;               // 23:22 Grab Flash Sector 11 in CM BANK
    Uint16 GRAB_SECT12:2;               // 25:24 Grab Flash Sector 12 in CM BANK
    Uint16 GRAB_SECT13:2;               // 27:26 Grab Flash Sector 13 in CM BANK
    Uint16 rsvd1:4;                     // 31:28 Reserved
};

union Z1_GRABSECT2R_REG {
    Uint32  all;
    struct  Z1_GRABSECT2R_BITS  bit;
};

struct Z1_GRABSECT3R_BITS {             // bits description
    Uint16 GRAB_SECT0:2;                // 1:0 Grab Flash Sector 0 in CPU2 BANK
    Uint16 GRAB_SECT1:2;                // 3:2 Grab Flash Sector 1 in CPU2 BANK
    Uint16 GRAB_SECT2:2;                // 5:4 Grab Flash Sector 2 in CPU2 BANK
    Uint16 GRAB_SECT3:2;                // 7:6 Grab Flash Sector 3 in CPU2 BANK
    Uint16 GRAB_SECT4:2;                // 9:8 Grab Flash Sector 4 in CPU2 BANK
    Uint16 GRAB_SECT5:2;                // 11:10 Grab Flash Sector 5 in CPU2 BANK
    Uint16 GRAB_SECT6:2;                // 13:12 Grab Flash Sector 6 in CPU2 BANK
    Uint16 GRAB_SECT7:2;                // 15:14 Grab Flash Sector 7 in CPU2 BANK
    Uint16 GRAB_SECT8:2;                // 17:16 Grab Flash Sector 8 in CPU2 BANK
    Uint16 GRAB_SECT9:2;                // 19:18 Grab Flash Sector 9 in CPU2 BANK
    Uint16 GRAB_SECT10:2;               // 21:20 Grab Flash Sector 10 in CPU2 BANK
    Uint16 GRAB_SECT11:2;               // 23:22 Grab Flash Sector 11 in CPU2 BANK
    Uint16 GRAB_SECT12:2;               // 25:24 Grab Flash Sector 12 in CPU2 BANK
    Uint16 GRAB_SECT13:2;               // 27:26 Grab Flash Sector 13 in CPU2 BANK
    Uint16 rsvd1:4;                     // 31:28 Reserved
};

union Z1_GRABSECT3R_REG {
    Uint32  all;
    struct  Z1_GRABSECT3R_BITS  bit;
};

struct Z1_GRABRAM1R_BITS {              // bits description
    Uint16 GRAB_RAM0:2;                 // 1:0 Grab RAM CPU1.LS0
    Uint16 GRAB_RAM1:2;                 // 3:2 Grab RAM CPU1.LS1
    Uint16 GRAB_RAM2:2;                 // 5:4 Grab RAM CPU1.LS2
    Uint16 GRAB_RAM3:2;                 // 7:6 Grab RAM CPU1.LS3
    Uint16 GRAB_RAM4:2;                 // 9:8 Grab RAM CPU1.LS4
    Uint16 GRAB_RAM5:2;                 // 11:10 Grab RAM CPU1.LS5
    Uint16 GRAB_RAM6:2;                 // 13:12 Grab RAM CPU1.LS6
    Uint16 GRAB_RAM7:2;                 // 15:14 Grab RAM CPU1.LS7
    Uint16 GRAB_RAM8:2;                 // 17:16 Grab RAM CPU1.D0
    Uint16 GRAB_RAM9:2;                 // 19:18 Grab RAM CPU1.D1
    Uint16 rsvd1:12;                    // 31:20 Reserved
};

union Z1_GRABRAM1R_REG {
    Uint32  all;
    struct  Z1_GRABRAM1R_BITS  bit;
};

struct Z1_GRABRAM2R_BITS {              // bits description
    Uint16 GRAB_RAM0:2;                 // 1:0 Grab RAM CM.C0
    Uint16 GRAB_RAM1:2;                 // 3:2 Grab RAM CM.C1
    Uint16 rsvd1:4;                     // 7:4 Reserved
    Uint16 GRAB_RAM4:2;                 // 9:8 Grab RAM CPU1TOCM MSGRAM0_L
    Uint16 GRAB_RAM5:2;                 // 11:10 Grab RAM CPU1TOCM MSGRAM0_H
    Uint16 GRAB_RAM6:2;                 // 13:12 Grab RAM CMTOCPU1 MSGRAM0_L
    Uint16 GRAB_RAM7:2;                 // 15:14 Grab RAM CMTOCPU1 MSGRAM0_H
    Uint16 GRAB_RAM8:2;                 // 17:16 Grab RAM CPU2TOCM MSGRAM0_L
    Uint16 GRAB_RAM9:2;                 // 19:18 Grab RAM CPU2TOCM MSGRAM0_H
    Uint16 GRAB_RAM10:2;                // 21:20 Grab RAM CMTOCPU2 MSGRAM0_L
    Uint16 GRAB_RAM11:2;                // 23:22 Grab RAM CMTOCPU2 MSGRAM0_H
    Uint16 GRAB_RAM12:2;                // 25:24 Grab RAM CPU1TOCPU2 MSGRAM0_L
    Uint16 GRAB_RAM13:2;                // 27:26 Grab RAM CPU1TOCPU2 MSGRAM0_H
    Uint16 GRAB_RAM14:2;                // 29:28 Grab RAM CPU2TOCPU1 MSGRAM0_L
    Uint16 GRAB_RAM15:2;                // 31:30 Grab RAM CPU2TOCPU1 MSGRAM0_H
};

union Z1_GRABRAM2R_REG {
    Uint32  all;
    struct  Z1_GRABRAM2R_BITS  bit;
};

struct Z1_GRABRAM3R_BITS {              // bits description
    Uint16 GRAB_RAM0:2;                 // 1:0 Grab RAM CPU2.LS0
    Uint16 GRAB_RAM1:2;                 // 3:2 Grab RAM CPU2.LS1
    Uint16 GRAB_RAM2:2;                 // 5:4 Grab RAM CPU2.LS2
    Uint16 GRAB_RAM3:2;                 // 7:6 Grab RAM CPU2.LS3
    Uint16 GRAB_RAM4:2;                 // 9:8 Grab RAM CPU2.LS4
    Uint16 GRAB_RAM5:2;                 // 11:10 Grab RAM CPU2.LS5
    Uint16 GRAB_RAM6:2;                 // 13:12 Grab RAM CPU2.LS6
    Uint16 GRAB_RAM7:2;                 // 15:14 Grab RAM CPU2.LS7
    Uint16 GRAB_RAM8:2;                 // 17:16 Grab RAM CPU2.D0
    Uint16 GRAB_RAM9:2;                 // 19:18 Grab RAM CPU2.D1
    Uint16 rsvd1:12;                    // 31:20 Reserved
};

union Z1_GRABRAM3R_REG {
    Uint32  all;
    struct  Z1_GRABRAM3R_BITS  bit;
};

struct Z1_EXEONLYSECT1R_BITS {          // bits description
    Uint16 EXEONLY_CPU1_SECT0:1;        // 0 Execute-Only Flash Sector 0 in flash CPU1 BANK
    Uint16 EXEONLY_CPU1_SECT1:1;        // 1 Execute-Only Flash Sector 1 in flash CPU1 BANK
    Uint16 EXEONLY_CPU1_SECT2:1;        // 2 Execute-Only Flash Sector 2 in flash CPU1 BANK
    Uint16 EXEONLY_CPU1_SECT3:1;        // 3 Execute-Only Flash Sector 3 in flash CPU1 BANK
    Uint16 EXEONLY_CPU1_SECT4:1;        // 4 Execute-Only Flash Sector 4 in flash CPU1 BANK
    Uint16 EXEONLY_CPU1_SECT5:1;        // 5 Execute-Only Flash Sector 5 in flash CPU1 BANK
    Uint16 EXEONLY_CPU1_SECT6:1;        // 6 Execute-Only Flash Sector 6 in flash CPU1 BANK
    Uint16 EXEONLY_CPU1_SECT7:1;        // 7 Execute-Only Flash Sector 7 in flash CPU1 BANK
    Uint16 EXEONLY_CPU1_SECT8:1;        // 8 Execute-Only Flash Sector 8 in flash CPU1 BANK
    Uint16 EXEONLY_CPU1_SECT9:1;        // 9 Execute-Only Flash Sector 9 in flash CPU1 BANK
    Uint16 EXEONLY_CPU1_SECT10:1;       // 10 Execute-Only Flash Sector 10 in flash CPU1 BANK
    Uint16 EXEONLY_CPU1_SECT11:1;       // 11 Execute-Only Flash Sector 11 in flash CPU1 BANK
    Uint16 EXEONLY_CPU1_SECT12:1;       // 12 Execute-Only Flash Sector 12 in flash CPU1 BANK
    Uint16 EXEONLY_CPU1_SECT13:1;       // 13 Execute-Only Flash Sector 13 in flash CPU1 BANK
    Uint16 rsvd1:2;                     // 15:14 Reserved
    Uint16 EXEONLY_CM_SECT0:1;          // 16 Execute-Only Flash Sector 0 in flash CM BANK
    Uint16 EXEONLY_CM_SECT1:1;          // 17 Execute-Only Flash Sector 1 in flash CM BANK
    Uint16 EXEONLY_CM_SECT2:1;          // 18 Execute-Only Flash Sector 2 in flash CM BANK
    Uint16 EXEONLY_CM_SECT3:1;          // 19 Execute-Only Flash Sector 3 in flash CM BANK
    Uint16 EXEONLY_CM_SECT4:1;          // 20 Execute-Only Flash Sector 4 in flash CM BANK
    Uint16 EXEONLY_CM_SECT5:1;          // 21 Execute-Only Flash Sector 5 in flash CM BANK
    Uint16 EXEONLY_CM_SECT6:1;          // 22 Execute-Only Flash Sector 6 in flash CM BANK
    Uint16 EXEONLY_CM_SECT7:1;          // 23 Execute-Only Flash Sector 7 in flash CM BANK
    Uint16 EXEONLY_CM_SECT8:1;          // 24 Execute-Only Flash Sector 8 in flash CM BANK
    Uint16 EXEONLY_CM_SECT9:1;          // 25 Execute-Only Flash Sector 9 in flash CM BANK
    Uint16 EXEONLY_CM_SECT10:1;         // 26 Execute-Only Flash Sector 10 in flash CM BANK
    Uint16 EXEONLY_CM_SECT11:1;         // 27 Execute-Only Flash Sector 11 in flash CM BANK
    Uint16 EXEONLY_CM_SECT12:1;         // 28 Execute-Only Flash Sector 12 in flash CM BANK
    Uint16 EXEONLY_CM_SECT13:1;         // 29 Execute-Only Flash Sector 13 in flash CM BANK
    Uint16 rsvd2:2;                     // 31:30 Reserved
};

union Z1_EXEONLYSECT1R_REG {
    Uint32  all;
    struct  Z1_EXEONLYSECT1R_BITS  bit;
};

struct Z1_EXEONLYSECT2R_BITS {          // bits description
    Uint16 EXEONLY_CPU2_SECT0:1;        // 0 Execute-Only Flash Sector 0 in flash CPU2 BANK
    Uint16 EXEONLY_CPU2_SECT1:1;        // 1 Execute-Only Flash Sector 1 in flash CPU2 BANK
    Uint16 EXEONLY_CPU2_SECT2:1;        // 2 Execute-Only Flash Sector 2 in flash CPU2 BANK
    Uint16 EXEONLY_CPU2_SECT3:1;        // 3 Execute-Only Flash Sector 3 in flash CPU2 BANK
    Uint16 EXEONLY_CPU2_SECT4:1;        // 4 Execute-Only Flash Sector 4 in flash CPU2 BANK
    Uint16 EXEONLY_CPU2_SECT5:1;        // 5 Execute-Only Flash Sector 5 in flash CPU2 BANK
    Uint16 EXEONLY_CPU2_SECT6:1;        // 6 Execute-Only Flash Sector 6 in flash CPU2 BANK
    Uint16 EXEONLY_CPU2_SECT7:1;        // 7 Execute-Only Flash Sector 7 in flash CPU2 BANK
    Uint16 EXEONLY_CPU2_SECT8:1;        // 8 Execute-Only Flash Sector 8 in flash CPU2 BANK
    Uint16 EXEONLY_CPU2_SECT9:1;        // 9 Execute-Only Flash Sector 9 in flash CPU2 BANK
    Uint16 EXEONLY_CPU2_SECT10:1;       // 10 Execute-Only Flash Sector 10 in flash CPU2 BANK
    Uint16 EXEONLY_CPU2_SECT11:1;       // 11 Execute-Only Flash Sector 11 in flash CPU2 BANK
    Uint16 EXEONLY_CPU2_SECT12:1;       // 12 Execute-Only Flash Sector 12 in flash CPU2 BANK
    Uint16 EXEONLY_CPU2_SECT13:1;       // 13 Execute-Only Flash Sector 13 in flash CPU2 BANK
    Uint16 rsvd1:2;                     // 15:14 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union Z1_EXEONLYSECT2R_REG {
    Uint32  all;
    struct  Z1_EXEONLYSECT2R_BITS  bit;
};

struct Z1_EXEONLYRAM1R_BITS {           // bits description
    Uint16 EXEONLY_RAM0:1;              // 0 Execute-Only RAM CPU1.LS0
    Uint16 EXEONLY_RAM1:1;              // 1 Execute-Only RAM CPU1.LS1
    Uint16 EXEONLY_RAM2:1;              // 2 Execute-Only RAM CPU1.LS2
    Uint16 EXEONLY_RAM3:1;              // 3 Execute-Only RAM CPU1.LS3
    Uint16 EXEONLY_RAM4:1;              // 4 Execute-Only RAM CPU1.LS4
    Uint16 EXEONLY_RAM5:1;              // 5 Execute-Only RAM CPU1.LS5
    Uint16 EXEONLY_RAM6:1;              // 6 Execute-Only RAM CPU1.LS6
    Uint16 EXEONLY_RAM7:1;              // 7 Execute-Only RAM CPU1.LS7
    Uint16 EXEONLY_RAM8:1;              // 8 Execute-Only RAM CPU1.D0
    Uint16 EXEONLY_RAM9:1;              // 9 Execute-Only RAM CPU1.D1
    Uint16 rsvd1:6;                     // 15:10 Reserved
    Uint16 EXEONLY_RAM16:1;             // 16 Execute-Only RAM on CM.C0
    Uint16 EXEONLY_RAM17:1;             // 17 Execute-Only RAM on CM.C1
    Uint16 rsvd2:4;                     // 21:18 Reserved
    Uint16 EXEONLY_RAM22:1;             // 22 Execute-Only RAM CPU2.D1
    Uint16 EXEONLY_RAM23:1;             // 23 Execute-Only RAM CPU2.D0
    Uint16 EXEONLY_RAM24:1;             // 24 Execute-Only RAM CPU2.LS7
    Uint16 EXEONLY_RAM25:1;             // 25 Execute-Only RAM CPU2.LS6
    Uint16 EXEONLY_RAM26:1;             // 26 Execute-Only RAM CPU2.LS5
    Uint16 EXEONLY_RAM27:1;             // 27 Execute-Only RAM CPU2.LS4
    Uint16 EXEONLY_RAM28:1;             // 28 Execute-Only RAM CPU2.LS3
    Uint16 EXEONLY_RAM29:1;             // 29 Execute-Only RAM CPU2.LS2
    Uint16 EXEONLY_RAM30:1;             // 30 Execute-Only RAM CPU2.LS1
    Uint16 EXEONLY_RAM31:1;             // 31 Execute-Only RAM CPU2.LS0
};

union Z1_EXEONLYRAM1R_REG {
    Uint32  all;
    struct  Z1_EXEONLYRAM1R_BITS  bit;
};

struct DCSM_Z1_REGS {
    union   Z1_LINKPOINTER_REG               Z1_LINKPOINTER;               // Zone 1 Link Pointer
    union   Z1_OTPSECLOCK_REG                Z1_OTPSECLOCK;                // Zone 1 OTP Secure Lock
    union   Z1_JLM_ENABLE_REG                Z1_JLM_ENABLE;                // Zone 1 JTAGLOCK Enable Register
    union   Z1_LINKPOINTERERR_REG            Z1_LINKPOINTERERR;            // Link Pointer Error
    Uint32                                   Z1_GPREG1;                    // Zone 1 General Purpose Register-1
    Uint32                                   Z1_GPREG2;                    // Zone 1 General Purpose Register-2
    Uint32                                   Z1_GPREG3;                    // Zone 1 General Purpose Register-3
    Uint32                                   Z1_GPREG4;                    // Zone 1 General Purpose Register-4
    Uint32                                   Z1_CSMKEY0;                   // Zone 1 CSM Key 0
    Uint32                                   Z1_CSMKEY1;                   // Zone 1 CSM Key 1
    Uint32                                   Z1_CSMKEY2;                   // Zone 1 CSM Key 2
    Uint32                                   Z1_CSMKEY3;                   // Zone 1 CSM Key 3
    union   Z1_CR_REG                        Z1_CR;                        // Zone 1 CSM Control Register
    union   Z1_GRABSECT1R_REG                Z1_GRABSECT1R;                // Zone 1 Grab Flash Status Register 1
    union   Z1_GRABSECT2R_REG                Z1_GRABSECT2R;                // Zone 1 Grab Flash Status Register 2
    union   Z1_GRABSECT3R_REG                Z1_GRABSECT3R;                // Zone 1 Grab Flash Status Register 3
    union   Z1_GRABRAM1R_REG                 Z1_GRABRAM1R;                 // Zone 1 Grab RAM Status Register 1
    union   Z1_GRABRAM2R_REG                 Z1_GRABRAM2R;                 // Zone 1 Grab RAM Status Register 2
    union   Z1_GRABRAM3R_REG                 Z1_GRABRAM3R;                 // Zone 1 Grab RAM Status Register 3
    union   Z1_EXEONLYSECT1R_REG             Z1_EXEONLYSECT1R;             // Zone 1 Execute Only Flash Status Register 1
    union   Z1_EXEONLYSECT2R_REG             Z1_EXEONLYSECT2R;             // Zone 1 Execute Only Flash Status Register 2
    union   Z1_EXEONLYRAM1R_REG              Z1_EXEONLYRAM1R;              // Zone 1 Execute Only RAM Status Register 1
    Uint16                                   rsvd1[2];                     // Reserved
    Uint32                                   Z1_JTAGKEY0;                  // JTAG Unlock Key Register 0
    Uint32                                   Z1_JTAGKEY1;                  // JTAG Unlock Key Register 1
    Uint32                                   Z1_JTAGKEY2;                  // JTAG Unlock Key Register 2
    Uint32                                   Z1_JTAGKEY3;                  // JTAG Unlock Key Register 3
    Uint32                                   Z1_CMACKEY0;                  // Secure Boot CMAC Key Status Register 0
    Uint32                                   Z1_CMACKEY1;                  // Secure Boot CMAC Key Status Register 1
    Uint32                                   Z1_CMACKEY2;                  // Secure Boot CMAC Key Status Register 2
    Uint32                                   Z1_CMACKEY3;                  // Secure Boot CMAC Key Status Register 3
};

struct Z2_LINKPOINTER_BITS {            // bits description
    Uint16 LINKPOINTER:14;              // 13:0 Zone2 LINK Pointer
    Uint16 rsvd1:2;                     // 15:14 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union Z2_LINKPOINTER_REG {
    Uint32  all;
    struct  Z2_LINKPOINTER_BITS  bit;
};

struct Z2_OTPSECLOCK_BITS {             // bits description
    Uint16 JTAGLOCK:1;                  // 0 JTAG Lock Status
    Uint16 rsvd1:3;                     // 3:1 Reserved
    Uint16 PSWDLOCK:4;                  // 7:4 Zone2 Password Lock.
    Uint16 CRCLOCK:4;                   // 11:8 Zone2 CRC Lock.
    Uint16 rsvd2:4;                     // 15:12 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union Z2_OTPSECLOCK_REG {
    Uint32  all;
    struct  Z2_OTPSECLOCK_BITS  bit;
};

struct Z2_LINKPOINTERERR_BITS {         // bits description
    Uint16 Z2_LINKPOINTERERR:14;        // 13:0 Error to Resolve Z2 Link pointer from OTP loaded values
    Uint16 rsvd1:2;                     // 15:14 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union Z2_LINKPOINTERERR_REG {
    Uint32  all;
    struct  Z2_LINKPOINTERERR_BITS  bit;
};

struct Z2_CR_BITS {                     // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 rsvd2:1;                     // 1 Reserved
    Uint16 rsvd3:1;                     // 2 Reserved
    Uint16 rsvd4:1;                     // 3 Reserved
    Uint16 rsvd5:12;                    // 15:4 Reserved
    Uint16 rsvd6:3;                     // 18:16 Reserved
    Uint16 ALLZERO:1;                   // 19 CSMPSWD All Zeros
    Uint16 ALLONE:1;                    // 20 CSMPSWD All Ones
    Uint16 UNSECURE:1;                  // 21 CSMPSWD Match CSMKEY
    Uint16 ARMED:1;                     // 22 CSM Passwords Read Status
    Uint16 rsvd7:1;                     // 23 Reserved
    Uint16 rsvd8:7;                     // 30:24 Reserved
    Uint16 FORCESEC:1;                  // 31 Force Secure
};

union Z2_CR_REG {
    Uint32  all;
    struct  Z2_CR_BITS  bit;
};

struct Z2_GRABSECT1R_BITS {             // bits description
    Uint16 GRAB_SECT0:2;                // 1:0 Grab Flash Sector 0 in CPU1 BANK
    Uint16 GRAB_SECT1:2;                // 3:2 Grab Flash Sector 1 in CPU1 BANK
    Uint16 GRAB_SECT2:2;                // 5:4 Grab Flash Sector 2 in CPU1 BANK
    Uint16 GRAB_SECT3:2;                // 7:6 Grab Flash Sector 3 in CPU1 BANK
    Uint16 GRAB_SECT4:2;                // 9:8 Grab Flash Sector 4 in CPU1 BANK
    Uint16 GRAB_SECT5:2;                // 11:10 Grab Flash Sector 5 in CPU1 BANK
    Uint16 GRAB_SECT6:2;                // 13:12 Grab Flash Sector 6 in CPU1 BANK
    Uint16 GRAB_SECT7:2;                // 15:14 Grab Flash Sector 7 in CPU1 BANK
    Uint16 GRAB_SECT8:2;                // 17:16 Grab Flash Sector 8 in CPU1 BANK
    Uint16 GRAB_SECT9:2;                // 19:18 Grab Flash Sector 9 in CPU1 BANK
    Uint16 GRAB_SECT10:2;               // 21:20 Grab Flash Sector 10 in CPU1 BANK
    Uint16 GRAB_SECT11:2;               // 23:22 Grab Flash Sector 11 in CPU1 BANK
    Uint16 GRAB_SECT12:2;               // 25:24 Grab Flash Sector 12 in CPU1 BANK
    Uint16 GRAB_SECT13:2;               // 27:26 Grab Flash Sector 13 in CPU1 BANK
    Uint16 rsvd1:4;                     // 31:28 Reserved
};

union Z2_GRABSECT1R_REG {
    Uint32  all;
    struct  Z2_GRABSECT1R_BITS  bit;
};

struct Z2_GRABSECT2R_BITS {             // bits description
    Uint16 GRAB_SECT0:2;                // 1:0 Grab Flash Sector 0 in CM BANK
    Uint16 GRAB_SECT1:2;                // 3:2 Grab Flash Sector 1 in CM BANK
    Uint16 GRAB_SECT2:2;                // 5:4 Grab Flash Sector 2 in CM BANK
    Uint16 GRAB_SECT3:2;                // 7:6 Grab Flash Sector 3 in CM BANK
    Uint16 GRAB_SECT4:2;                // 9:8 Grab Flash Sector 4 in CM BANK
    Uint16 GRAB_SECT5:2;                // 11:10 Grab Flash Sector 5 in CM BANK
    Uint16 GRAB_SECT6:2;                // 13:12 Grab Flash Sector 6 in CM BANK
    Uint16 GRAB_SECT7:2;                // 15:14 Grab Flash Sector 7 in CM BANK
    Uint16 GRAB_SECT8:2;                // 17:16 Grab Flash Sector 8 in CM BANK
    Uint16 GRAB_SECT9:2;                // 19:18 Grab Flash Sector 9 in CM BANK
    Uint16 GRAB_SECT10:2;               // 21:20 Grab Flash Sector 10 in CM BANK
    Uint16 GRAB_SECT11:2;               // 23:22 Grab Flash Sector 11 in CM BANK
    Uint16 GRAB_SECT12:2;               // 25:24 Grab Flash Sector 12 in CM BANK
    Uint16 GRAB_SECT13:2;               // 27:26 Grab Flash Sector 13 in CM BANK
    Uint16 rsvd1:4;                     // 31:28 Reserved
};

union Z2_GRABSECT2R_REG {
    Uint32  all;
    struct  Z2_GRABSECT2R_BITS  bit;
};

struct Z2_GRABSECT3R_BITS {             // bits description
    Uint16 GRAB_SECT0:2;                // 1:0 Grab Flash Sector 0 in CPU2 BANK
    Uint16 GRAB_SECT1:2;                // 3:2 Grab Flash Sector 1 in CPU2 BANK
    Uint16 GRAB_SECT2:2;                // 5:4 Grab Flash Sector 2 in CPU2 BANK
    Uint16 GRAB_SECT3:2;                // 7:6 Grab Flash Sector 3 in CPU2 BANK
    Uint16 GRAB_SECT4:2;                // 9:8 Grab Flash Sector 4 in CPU2 BANK
    Uint16 GRAB_SECT5:2;                // 11:10 Grab Flash Sector 5 in CPU2 BANK
    Uint16 GRAB_SECT6:2;                // 13:12 Grab Flash Sector 6 in CPU2 BANK
    Uint16 GRAB_SECT7:2;                // 15:14 Grab Flash Sector 7 in CPU2 BANK
    Uint16 GRAB_SECT8:2;                // 17:16 Grab Flash Sector 8 in CPU2 BANK
    Uint16 GRAB_SECT9:2;                // 19:18 Grab Flash Sector 9 in CPU2 BANK
    Uint16 GRAB_SECT10:2;               // 21:20 Grab Flash Sector 10 in CPU2 BANK
    Uint16 GRAB_SECT11:2;               // 23:22 Grab Flash Sector 11 in CPU2 BANK
    Uint16 GRAB_SECT12:2;               // 25:24 Grab Flash Sector 12 in CPU2 BANK
    Uint16 GRAB_SECT13:2;               // 27:26 Grab Flash Sector 13 in CPU2 BANK
    Uint16 rsvd1:4;                     // 31:28 Reserved
};

union Z2_GRABSECT3R_REG {
    Uint32  all;
    struct  Z2_GRABSECT3R_BITS  bit;
};

struct Z2_GRABRAM1R_BITS {              // bits description
    Uint16 GRAB_RAM0:2;                 // 1:0 Grab RAM CPU1.LS0
    Uint16 GRAB_RAM1:2;                 // 3:2 Grab RAM CPU1.LS1
    Uint16 GRAB_RAM2:2;                 // 5:4 Grab RAM CPU1.LS2
    Uint16 GRAB_RAM3:2;                 // 7:6 Grab RAM CPU1.LS3
    Uint16 GRAB_RAM4:2;                 // 9:8 Grab RAM CPU1.LS4
    Uint16 GRAB_RAM5:2;                 // 11:10 Grab RAM CPU1.LS5
    Uint16 GRAB_RAM6:2;                 // 13:12 Grab RAM CPU1.LS6
    Uint16 GRAB_RAM7:2;                 // 15:14 Grab RAM CPU1.LS7
    Uint16 GRAB_RAM8:2;                 // 17:16 Grab RAM CPU1.D0
    Uint16 GRAB_RAM9:2;                 // 19:18 Grab RAM CPU1.D1
    Uint16 rsvd1:12;                    // 31:20 Reserved
};

union Z2_GRABRAM1R_REG {
    Uint32  all;
    struct  Z2_GRABRAM1R_BITS  bit;
};

struct Z2_GRABRAM2R_BITS {              // bits description
    Uint16 GRAB_RAM0:2;                 // 1:0 Grab RAM CM.C0
    Uint16 GRAB_RAM1:2;                 // 3:2 Grab RAM CM.C1
    Uint16 rsvd1:4;                     // 7:4 Reserved
    Uint16 GRAB_RAM4:2;                 // 9:8 Grab RAM CPU1TOCM MSGRAM0_L
    Uint16 GRAB_RAM5:2;                 // 11:10 Grab RAM CPU1TOCM MSGRAM0_H
    Uint16 GRAB_RAM6:2;                 // 13:12 Grab RAM CMTOCPU1 MSGRAM0_L
    Uint16 GRAB_RAM7:2;                 // 15:14 Grab RAM CMTOCPU1 MSGRAM0_H
    Uint16 GRAB_RAM8:2;                 // 17:16 Grab RAM CPU2TOCM MSGRAM0_L
    Uint16 GRAB_RAM9:2;                 // 19:18 Grab RAM CPU2TOCM MSGRAM0_H
    Uint16 GRAB_RAM10:2;                // 21:20 Grab RAM CMTOCPU2 MSGRAM0_L
    Uint16 GRAB_RAM11:2;                // 23:22 Grab RAM CMTOCPU2 MSGRAM0_H
    Uint16 GRAB_RAM12:2;                // 25:24 Grab RAM CPU1TOCPU2 MSGRAM0_L
    Uint16 GRAB_RAM13:2;                // 27:26 Grab RAM CPU1TOCPU2 MSGRAM0_H
    Uint16 GRAB_RAM14:2;                // 29:28 Grab RAM CPU2TOCPU1 MSGRAM0_L
    Uint16 GRAB_RAM15:2;                // 31:30 Grab RAM CPU2TOCPU1 MSGRAM0_H
};

union Z2_GRABRAM2R_REG {
    Uint32  all;
    struct  Z2_GRABRAM2R_BITS  bit;
};

struct Z2_GRABRAM3R_BITS {              // bits description
    Uint16 GRAB_RAM0:2;                 // 1:0 Grab RAM CPU2.LS0
    Uint16 GRAB_RAM1:2;                 // 3:2 Grab RAM CPU2.LS1
    Uint16 GRAB_RAM2:2;                 // 5:4 Grab RAM CPU2.LS2
    Uint16 GRAB_RAM3:2;                 // 7:6 Grab RAM CPU2.LS3
    Uint16 GRAB_RAM4:2;                 // 9:8 Grab RAM CPU2.LS4
    Uint16 GRAB_RAM5:2;                 // 11:10 Grab RAM CPU2.LS5
    Uint16 GRAB_RAM6:2;                 // 13:12 Grab RAM CPU2.LS6
    Uint16 GRAB_RAM7:2;                 // 15:14 Grab RAM CPU2.LS7
    Uint16 GRAB_RAM8:2;                 // 17:16 Grab RAM CPU2.D0
    Uint16 GRAB_RAM9:2;                 // 19:18 Grab RAM CPU2.D1
    Uint16 rsvd1:12;                    // 31:20 Reserved
};

union Z2_GRABRAM3R_REG {
    Uint32  all;
    struct  Z2_GRABRAM3R_BITS  bit;
};

struct Z2_EXEONLYSECT1R_BITS {          // bits description
    Uint16 EXEONLY_CPU1_SECT0:1;        // 0 Execute-Only Flash Sector 0 in flash CPU1 BANK
    Uint16 EXEONLY_CPU1_SECT1:1;        // 1 Execute-Only Flash Sector 1 in flash CPU1 BANK
    Uint16 EXEONLY_CPU1_SECT2:1;        // 2 Execute-Only Flash Sector 2 in flash CPU1 BANK
    Uint16 EXEONLY_CPU1_SECT3:1;        // 3 Execute-Only Flash Sector 3 in flash CPU1 BANK
    Uint16 EXEONLY_CPU1_SECT4:1;        // 4 Execute-Only Flash Sector 4 in flash CPU1 BANK
    Uint16 EXEONLY_CPU1_SECT5:1;        // 5 Execute-Only Flash Sector 5 in flash CPU1 BANK
    Uint16 EXEONLY_CPU1_SECT6:1;        // 6 Execute-Only Flash Sector 6 in flash CPU1 BANK
    Uint16 EXEONLY_CPU1_SECT7:1;        // 7 Execute-Only Flash Sector 7 in flash CPU1 BANK
    Uint16 EXEONLY_CPU1_SECT8:1;        // 8 Execute-Only Flash Sector 8 in flash CPU1 BANK
    Uint16 EXEONLY_CPU1_SECT9:1;        // 9 Execute-Only Flash Sector 9 in flash CPU1 BANK
    Uint16 EXEONLY_CPU1_SECT10:1;       // 10 Execute-Only Flash Sector 10 in flash CPU1 BANK
    Uint16 EXEONLY_CPU1_SECT11:1;       // 11 Execute-Only Flash Sector 11 in flash CPU1 BANK
    Uint16 EXEONLY_CPU1_SECT12:1;       // 12 Execute-Only Flash Sector 12 in flash CPU1 BANK
    Uint16 EXEONLY_CPU1_SECT13:1;       // 13 Execute-Only Flash Sector 13 in flash CPU1 BANK
    Uint16 rsvd1:2;                     // 15:14 Reserved
    Uint16 EXEONLY_CM_SECT0:1;          // 16 Execute-Only Flash Sector 0 in flash CM BANK
    Uint16 EXEONLY_CM_SECT1:1;          // 17 Execute-Only Flash Sector 1 in flash CM BANK
    Uint16 EXEONLY_CM_SECT2:1;          // 18 Execute-Only Flash Sector 2 in flash CM BANK
    Uint16 EXEONLY_CM_SECT3:1;          // 19 Execute-Only Flash Sector 3 in flash CM BANK
    Uint16 EXEONLY_CM_SECT4:1;          // 20 Execute-Only Flash Sector 4 in flash CM BANK
    Uint16 EXEONLY_CM_SECT5:1;          // 21 Execute-Only Flash Sector 5 in flash CM BANK
    Uint16 EXEONLY_CM_SECT6:1;          // 22 Execute-Only Flash Sector 6 in flash CM BANK
    Uint16 EXEONLY_CM_SECT7:1;          // 23 Execute-Only Flash Sector 7 in flash CM BANK
    Uint16 EXEONLY_CM_SECT8:1;          // 24 Execute-Only Flash Sector 8 in flash CM BANK
    Uint16 EXEONLY_CM_SECT9:1;          // 25 Execute-Only Flash Sector 9 in flash CM BANK
    Uint16 EXEONLY_CM_SECT10:1;         // 26 Execute-Only Flash Sector 10 in flash CM BANK
    Uint16 EXEONLY_CM_SECT11:1;         // 27 Execute-Only Flash Sector 11 in flash CM BANK
    Uint16 EXEONLY_CM_SECT12:1;         // 28 Execute-Only Flash Sector 12 in flash CM BANK
    Uint16 EXEONLY_CM_SECT13:1;         // 29 Execute-Only Flash Sector 13 in flash CM BANK
    Uint16 rsvd2:2;                     // 31:30 Reserved
};

union Z2_EXEONLYSECT1R_REG {
    Uint32  all;
    struct  Z2_EXEONLYSECT1R_BITS  bit;
};

struct Z2_EXEONLYSECT2R_BITS {          // bits description
    Uint16 EXEONLY_CPU2_SECT0:1;        // 0 Execute-Only Flash Sector 0 in flash CPU2 BANK
    Uint16 EXEONLY_CPU2_SECT1:1;        // 1 Execute-Only Flash Sector 1 in flash CPU2 BANK
    Uint16 EXEONLY_CPU2_SECT2:1;        // 2 Execute-Only Flash Sector 2 in flash CPU2 BANK
    Uint16 EXEONLY_CPU2_SECT3:1;        // 3 Execute-Only Flash Sector 3 in flash CPU2 BANK
    Uint16 EXEONLY_CPU2_SECT4:1;        // 4 Execute-Only Flash Sector 4 in flash CPU2 BANK
    Uint16 EXEONLY_CPU2_SECT5:1;        // 5 Execute-Only Flash Sector 5 in flash CPU2 BANK
    Uint16 EXEONLY_CPU2_SECT6:1;        // 6 Execute-Only Flash Sector 6 in flash CPU2 BANK
    Uint16 EXEONLY_CPU2_SECT7:1;        // 7 Execute-Only Flash Sector 7 in flash CPU2 BANK
    Uint16 EXEONLY_CPU2_SECT8:1;        // 8 Execute-Only Flash Sector 8 in flash CPU2 BANK
    Uint16 EXEONLY_CPU2_SECT9:1;        // 9 Execute-Only Flash Sector 9 in flash CPU2 BANK
    Uint16 EXEONLY_CPU2_SECT10:1;       // 10 Execute-Only Flash Sector 10 in flash CPU2 BANK
    Uint16 EXEONLY_CPU2_SECT11:1;       // 11 Execute-Only Flash Sector 11 in flash CPU2 BANK
    Uint16 EXEONLY_CPU2_SECT12:1;       // 12 Execute-Only Flash Sector 12 in flash CPU2 BANK
    Uint16 EXEONLY_CPU2_SECT13:1;       // 13 Execute-Only Flash Sector 13 in flash CPU2 BANK
    Uint16 rsvd1:2;                     // 15:14 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union Z2_EXEONLYSECT2R_REG {
    Uint32  all;
    struct  Z2_EXEONLYSECT2R_BITS  bit;
};

struct Z2_EXEONLYRAM1R_BITS {           // bits description
    Uint16 EXEONLY_RAM0:1;              // 0 Execute-Only RAM CPU1.LS0
    Uint16 EXEONLY_RAM1:1;              // 1 Execute-Only RAM CPU1.LS1
    Uint16 EXEONLY_RAM2:1;              // 2 Execute-Only RAM CPU1.LS2
    Uint16 EXEONLY_RAM3:1;              // 3 Execute-Only RAM CPU1.LS3
    Uint16 EXEONLY_RAM4:1;              // 4 Execute-Only RAM CPU1.LS4
    Uint16 EXEONLY_RAM5:1;              // 5 Execute-Only RAM CPU1.LS5
    Uint16 EXEONLY_RAM6:1;              // 6 Execute-Only RAM CPU1.LS6
    Uint16 EXEONLY_RAM7:1;              // 7 Execute-Only RAM CPU1.LS7
    Uint16 EXEONLY_RAM8:1;              // 8 Execute-Only RAM CPU1.D0
    Uint16 EXEONLY_RAM9:1;              // 9 Execute-Only RAM CPU1.D1
    Uint16 rsvd1:6;                     // 15:10 Reserved
    Uint16 EXEONLY_RAM16:1;             // 16 Execute-Only RAM on CM.C0
    Uint16 EXEONLY_RAM17:1;             // 17 Execute-Only RAM on CM.C1
    Uint16 rsvd2:4;                     // 21:18 Reserved
    Uint16 EXEONLY_RAM22:1;             // 22 Execute-Only RAM CPU2.D1
    Uint16 EXEONLY_RAM23:1;             // 23 Execute-Only RAM CPU2.D0
    Uint16 EXEONLY_RAM24:1;             // 24 Execute-Only RAM CPU2.LS7
    Uint16 EXEONLY_RAM25:1;             // 25 Execute-Only RAM CPU2.LS6
    Uint16 EXEONLY_RAM26:1;             // 26 Execute-Only RAM CPU2.LS5
    Uint16 EXEONLY_RAM27:1;             // 27 Execute-Only RAM CPU2.LS4
    Uint16 EXEONLY_RAM28:1;             // 28 Execute-Only RAM CPU2.LS3
    Uint16 EXEONLY_RAM29:1;             // 29 Execute-Only RAM CPU2.LS2
    Uint16 EXEONLY_RAM30:1;             // 30 Execute-Only RAM CPU2.LS1
    Uint16 EXEONLY_RAM31:1;             // 31 Execute-Only RAM CPU2.LS0
};

union Z2_EXEONLYRAM1R_REG {
    Uint32  all;
    struct  Z2_EXEONLYRAM1R_BITS  bit;
};

struct DCSM_Z2_REGS {
    union   Z2_LINKPOINTER_REG               Z2_LINKPOINTER;               // Zone 2 Link Pointer
    union   Z2_OTPSECLOCK_REG                Z2_OTPSECLOCK;                // Zone 2 OTP Secure Lock
    Uint16                                   rsvd1[2];                     // Reserved
    union   Z2_LINKPOINTERERR_REG            Z2_LINKPOINTERERR;            // Link Pointer Error
    Uint32                                   Z2_GPREG1;                    // Zone 2 General Purpose Register-1
    Uint32                                   Z2_GPREG2;                    // Zone 2 General Purpose Register-2
    Uint32                                   Z2_GPREG3;                    // Zone 2 General Purpose Register-3
    Uint32                                   Z2_GPREG4;                    // Zone 2 General Purpose Register-4
    Uint32                                   Z2_CSMKEY0;                   // Zone 2 CSM Key 0
    Uint32                                   Z2_CSMKEY1;                   // Zone 2 CSM Key 1
    Uint32                                   Z2_CSMKEY2;                   // Zone 2 CSM Key 2
    Uint32                                   Z2_CSMKEY3;                   // Zone 2 CSM Key 3
    union   Z2_CR_REG                        Z2_CR;                        // Zone 2 CSM Control Register
    union   Z2_GRABSECT1R_REG                Z2_GRABSECT1R;                // Zone 2 Grab Flash Status Register 1
    union   Z2_GRABSECT2R_REG                Z2_GRABSECT2R;                // Zone 2 Grab Flash Status Register 2
    union   Z2_GRABSECT3R_REG                Z2_GRABSECT3R;                // Zone 2 Grab Flash Status Register 3
    union   Z2_GRABRAM1R_REG                 Z2_GRABRAM1R;                 // Zone 2 Grab RAM Status Register 1
    union   Z2_GRABRAM2R_REG                 Z2_GRABRAM2R;                 // Zone 2 Grab RAM Status Register 2
    union   Z2_GRABRAM3R_REG                 Z2_GRABRAM3R;                 // Zone 2 Grab RAM Status Register 3
    union   Z2_EXEONLYSECT1R_REG             Z2_EXEONLYSECT1R;             // Zone 2 Execute Only Flash Status Register 1
    union   Z2_EXEONLYSECT2R_REG             Z2_EXEONLYSECT2R;             // Zone 2 Execute Only Flash Status Register 2
    union   Z2_EXEONLYRAM1R_REG              Z2_EXEONLYRAM1R;              // Zone 2 Execute Only RAM Status Register 1
};

struct FLSEM_BITS {                     // bits description
    Uint16 SEM:2;                       // 1:0 Flash Semaphore Bit
    Uint16 rsvd1:6;                     // 7:2 Reserved
    Uint16 KEY:8;                       // 15:8 Semaphore Key
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union FLSEM_REG {
    Uint32  all;
    struct  FLSEM_BITS  bit;
};

struct SECTSTAT1_BITS {                 // bits description
    Uint16 STATUS_SECT0:2;              // 1:0 Zone Status flash CPU1 BANK Sector 0
    Uint16 STATUS_SECT1:2;              // 3:2 Zone Status flash CPU1 BANK sector 1
    Uint16 STATUS_SECT2:2;              // 5:4 Zone Status flash CPU1 BANK Sector 2
    Uint16 STATUS_SECT3:2;              // 7:6 Zone Status flash CPU1 BANK Sector 3
    Uint16 STATUS_SECT4:2;              // 9:8 Zone Status flash CPU1 BANK Sector 4
    Uint16 STATUS_SECT5:2;              // 11:10 Zone Status flash CPU1 BANK Sector 5
    Uint16 STATUS_SECT6:2;              // 13:12 Zone Status flash CPU1 BANK Sector 6
    Uint16 STATUS_SECT7:2;              // 15:14 Zone Status flash CPU1 BANK Sector 7
    Uint16 STATUS_SECT8:2;              // 17:16 Zone Status flash CPU1 BANK sector 8
    Uint16 STATUS_SECT9:2;              // 19:18 Zone Status flash CPU1 BANK Sector 9
    Uint16 STATUS_SECT10:2;             // 21:20 Zone Status flash CPU1 BANK Sector 10
    Uint16 STATUS_SECT11:2;             // 23:22 Zone Status flash CPU1 BANK Sector 11
    Uint16 STATUS_SECT12:2;             // 25:24 Zone Status flash CPU1 BANK Sector 12
    Uint16 STATUS_SECT13:2;             // 27:26 Zone Status flash CPU1 BANK Sector 13
    Uint16 rsvd1:4;                     // 31:28 Reserved
};

union SECTSTAT1_REG {
    Uint32  all;
    struct  SECTSTAT1_BITS  bit;
};

struct SECTSTAT2_BITS {                 // bits description
    Uint16 STATUS_SECT0:2;              // 1:0 Zone Status flash CM BANK Sector 0
    Uint16 STATUS_SECT1:2;              // 3:2 Zone Status flash CM BANK sector 1
    Uint16 STATUS_SECT2:2;              // 5:4 Zone Status flash CM BANK Sector 2
    Uint16 STATUS_SECT3:2;              // 7:6 Zone Status flash CM BANK Sector 3
    Uint16 STATUS_SECT4:2;              // 9:8 Zone Status flash CM BANK Sector 4
    Uint16 STATUS_SECT5:2;              // 11:10 Zone Status flash CM BANK Sector 5
    Uint16 STATUS_SECT6:2;              // 13:12 Zone Status flash CM BANK Sector 6
    Uint16 STATUS_SECT7:2;              // 15:14 Zone Status flash CM BANK Sector 7
    Uint16 STATUS_SECT8:2;              // 17:16 Zone Status flash CM BANK sector 8
    Uint16 STATUS_SECT9:2;              // 19:18 Zone Status flash CM BANK Sector 9
    Uint16 STATUS_SECT10:2;             // 21:20 Zone Status flash CM BANK Sector 10
    Uint16 STATUS_SECT11:2;             // 23:22 Zone Status flash CM BANK Sector 11
    Uint16 STATUS_SECT12:2;             // 25:24 Zone Status flash CM BANK Sector 12
    Uint16 STATUS_SECT13:2;             // 27:26 Zone Status flash CM BANK Sector 13
    Uint16 rsvd1:4;                     // 31:28 Reserved
};

union SECTSTAT2_REG {
    Uint32  all;
    struct  SECTSTAT2_BITS  bit;
};

struct SECTSTAT3_BITS {                 // bits description
    Uint16 STATUS_SECT0:2;              // 1:0 Zone Status flash CPU2 BANK Sector 0
    Uint16 STATUS_SECT1:2;              // 3:2 Zone Status flash CPU2 BANK sector 1
    Uint16 STATUS_SECT2:2;              // 5:4 Zone Status flash CPU2 BANK Sector 2
    Uint16 STATUS_SECT3:2;              // 7:6 Zone Status flash CPU2 BANK Sector 3
    Uint16 STATUS_SECT4:2;              // 9:8 Zone Status flash CPU2 BANK Sector 4
    Uint16 STATUS_SECT5:2;              // 11:10 Zone Status flash CPU2 BANK Sector 5
    Uint16 STATUS_SECT6:2;              // 13:12 Zone Status flash CPU2 BANK Sector 6
    Uint16 STATUS_SECT7:2;              // 15:14 Zone Status flash CPU2 BANK Sector 7
    Uint16 STATUS_SECT8:2;              // 17:16 Zone Status flash CPU2 BANK sector 8
    Uint16 STATUS_SECT9:2;              // 19:18 Zone Status flash CPU2 BANK Sector 9
    Uint16 STATUS_SECT10:2;             // 21:20 Zone Status flash CPU2 BANK Sector 10
    Uint16 STATUS_SECT11:2;             // 23:22 Zone Status flash CPU2 BANK Sector 11
    Uint16 STATUS_SECT12:2;             // 25:24 Zone Status flash CPU2 BANK Sector 12
    Uint16 STATUS_SECT13:2;             // 27:26 Zone Status flash CPU2 BANK Sector 13
    Uint16 rsvd1:4;                     // 31:28 Reserved
};

union SECTSTAT3_REG {
    Uint32  all;
    struct  SECTSTAT3_BITS  bit;
};

struct RAMSTAT1_BITS {                  // bits description
    Uint16 STATUS_RAM0:2;               // 1:0 Zone Status RAM CPU1.LS0
    Uint16 STATUS_RAM1:2;               // 3:2 Zone Status RAM CPU1.LS1
    Uint16 STATUS_RAM2:2;               // 5:4 Zone Status RAM CPU1.LS2
    Uint16 STATUS_RAM3:2;               // 7:6 Zone Status RAM CPU1.LS3
    Uint16 STATUS_RAM4:2;               // 9:8 Zone Status RAM CPU1.LS4
    Uint16 STATUS_RAM5:2;               // 11:10 Zone Status RAM CPU1.LS5
    Uint16 STATUS_RAM6:2;               // 13:12 Zone Status RAM CPU1.LS6
    Uint16 STATUS_RAM7:2;               // 15:14 Zone Status RAM CPU1.LS7
    Uint16 STATUS_RAM8:2;               // 17:16 Zone Status RAM CPU1.D0
    Uint16 STATUS_RAM9:2;               // 19:18 Zone Status RAM CPU1.D1
    Uint16 rsvd1:12;                    // 31:20 Reserved
};

union RAMSTAT1_REG {
    Uint32  all;
    struct  RAMSTAT1_BITS  bit;
};

struct RAMSTAT2_BITS {                  // bits description
    Uint16 STATUS_RAM0:2;               // 1:0 Zone Status RAM CM.C0
    Uint16 STATUS_RAM1:2;               // 3:2 Zone Status RAM CM.C1
    Uint16 rsvd1:4;                     // 7:4 Reserved
    Uint16 STATUS_RAM4:2;               // 9:8 Zone Status RAM CPU1 to CM MSG RAM 1
    Uint16 STATUS_RAM5:2;               // 11:10 Zone Status RAM CPU1 to CM MSG RAM 2
    Uint16 STATUS_RAM6:2;               // 13:12 Zone Status RAM CM to CPU1 MSG RAM 1
    Uint16 STATUS_RAM7:2;               // 15:14 Zone Status RAM CM to CPU1 MSG RAM 2
    Uint16 STATUS_RAM8:2;               // 17:16 Zone Status RAM CPU2 to CM MSG RAM 1
    Uint16 STATUS_RAM9:2;               // 19:18 Zone Status RAM CPU2 to CM MSG RAM 2
    Uint16 STATUS_RAM10:2;              // 21:20 Zone Status RAM CM to CPU2 MSG RAM 1
    Uint16 STATUS_RAM11:2;              // 23:22 Zone Status RAM CM to CPU2 MSG RAM 2
    Uint16 STATUS_RAM12:2;              // 25:24 Zone Status RAM CPU1 to CPU2 MSG RAM 1
    Uint16 STATUS_RAM13:2;              // 27:26 Zone Status RAM CPU1 to CPU2 MSG RAM 2
    Uint16 STATUS_RAM14:2;              // 29:28 Zone Status RAM CPU2 to CPU1 MSG RAM 1
    Uint16 STATUS_RAM15:2;              // 31:30 Zone Status RAM CPU2 to CPU1 MSG RAM 2
};

union RAMSTAT2_REG {
    Uint32  all;
    struct  RAMSTAT2_BITS  bit;
};

struct RAMSTAT3_BITS {                  // bits description
    Uint16 STATUS_RAM0:2;               // 1:0 Zone Status RAM CPU2.LS0
    Uint16 STATUS_RAM1:2;               // 3:2 Zone Status RAM CPU2.LS1
    Uint16 STATUS_RAM2:2;               // 5:4 Zone Status RAM CPU2.LS2
    Uint16 STATUS_RAM3:2;               // 7:6 Zone Status RAM CPU2.LS3
    Uint16 STATUS_RAM4:2;               // 9:8 Zone Status RAM CPU2.LS4
    Uint16 STATUS_RAM5:2;               // 11:10 Zone Status RAM CPU2.LS5
    Uint16 STATUS_RAM6:2;               // 13:12 Zone Status RAM CPU2.LS6
    Uint16 STATUS_RAM7:2;               // 15:14 Zone Status RAM CPU2.LS7
    Uint16 STATUS_RAM8:2;               // 17:16 Zone Status RAM CPU2.D0
    Uint16 STATUS_RAM9:2;               // 19:18 Zone Status RAM CPU2.D1
    Uint16 rsvd1:12;                    // 31:20 Reserved
};

union RAMSTAT3_REG {
    Uint32  all;
    struct  RAMSTAT3_BITS  bit;
};

struct SECERRSTAT_BITS {                // bits description
    Uint16 ERR:1;                       // 0 Security Configuration load Error Status
    Uint16 rsvd1:15;                    // 15:1 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union SECERRSTAT_REG {
    Uint32  all;
    struct  SECERRSTAT_BITS  bit;
};

struct SECERRCLR_BITS {                 // bits description
    Uint16 ERR:1;                       // 0 Clear Security Configuration Load Error Status Bit
    Uint16 rsvd1:15;                    // 15:1 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union SECERRCLR_REG {
    Uint32  all;
    struct  SECERRCLR_BITS  bit;
};

struct SECERRFRC_BITS {                 // bits description
    Uint16 ERR:1;                       // 0 Set Security Configuration Load Error Status Bit
    Uint16 rsvd1:15;                    // 15:1 Reserved
    Uint16 KEY:16;                      // 31:16 Valid Register Write Key
};

union SECERRFRC_REG {
    Uint32  all;
    struct  SECERRFRC_BITS  bit;
};

struct DCSM_COMMON_REGS {
    union   FLSEM_REG                        FLSEM;                        // Flash Wrapper Semaphore Register
    Uint16                                   rsvd1[6];                     // Reserved
    union   SECTSTAT1_REG                    SECTSTAT1;                    // Flash Sectors Status Register 1
    union   SECTSTAT2_REG                    SECTSTAT2;                    // Flash Sectors Status Register 2
    union   SECTSTAT3_REG                    SECTSTAT3;                    // Flash Sectors Status Register 3
    Uint16                                   rsvd2[2];                     // Reserved
    union   RAMSTAT1_REG                     RAMSTAT1;                     // RAM Status Register 1
    union   RAMSTAT2_REG                     RAMSTAT2;                     // RAM Status Register 2
    union   RAMSTAT3_REG                     RAMSTAT3;                     // RAM Status Register 3
    Uint16                                   rsvd3[2];                     // Reserved
    union   SECERRSTAT_REG                   SECERRSTAT;                   // Security Error Status Register
    union   SECERRCLR_REG                    SECERRCLR;                    // Security Error Clear Register
    union   SECERRFRC_REG                    SECERRFRC;                    // Security Error Force Register
};

//---------------------------------------------------------------------------
// DCSM External References & Function Declarations:
//
#ifdef CPU1
extern volatile struct DCSM_Z1_REGS DcsmZ1Regs;
extern volatile struct DCSM_Z2_REGS DcsmZ2Regs;
extern volatile struct DCSM_COMMON_REGS DcsmCommonRegs;
extern volatile struct DCSM_Z1_OTP DcsmZ1OtpRegs;
extern volatile struct DCSM_Z2_OTP DcsmZ2OtpRegs;
#endif
#ifdef CPU2
extern volatile struct DCSM_Z1_REGS DcsmZ1Regs;
extern volatile struct DCSM_Z2_REGS DcsmZ2Regs;
extern volatile struct DCSM_COMMON_REGS DcsmCommonRegs;
#endif
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
