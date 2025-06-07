//###########################################################################
//
// FILE:    f280013x_dcsm.h
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

#ifndef F280013X_DCSM_H
#define F280013X_DCSM_H

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
    Uint16                                   rsvd1[2];                     // Reserved
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
    Uint16 rsvd2:4;                     // 11:8 Reserved
    Uint16 rsvd3:4;                     // 15:12 Reserved
    Uint16 rsvd4:16;                    // 31:16 Reserved
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
    Uint16 GRAB_SECT0:2;                // 1:0 Grab Flash Sector 0
    Uint16 GRAB_SECT1:2;                // 3:2 Grab Flash Sector 1
    Uint16 GRAB_SECT2:2;                // 5:4 Grab Flash Sector 2
    Uint16 GRAB_SECT3:2;                // 7:6 Grab Flash Sector 3
    Uint16 GRAB_SECT4:2;                // 9:8 Grab Flash Sector 4
    Uint16 GRAB_SECT5:2;                // 11:10 Grab Flash Sector 5
    Uint16 GRAB_SECT6:2;                // 13:12 Grab Flash Sector 6
    Uint16 GRAB_SECT7:2;                // 15:14 Grab Flash Sector 7
    Uint16 GRAB_SECT8:2;                // 17:16 Grab Flash Sector 8
    Uint16 GRAB_SECT9:2;                // 19:18 Grab Flash Sector 9
    Uint16 GRAB_SECT10:2;               // 21:20 Grab Flash Sector 10
    Uint16 GRAB_SECT11:2;               // 23:22 Grab Flash Sector 11
    Uint16 GRAB_SECT12:2;               // 25:24 Grab Flash Sector 12
    Uint16 GRAB_SECT13:2;               // 27:26 Grab Flash Sector 13
    Uint16 GRAB_SECT14:2;               // 29:28 Grab Flash Sector 14
    Uint16 GRAB_SECT15:2;               // 31:30 Grab Flash Sector 15
};

union Z1_GRABSECT1R_REG {
    Uint32  all;
    struct  Z1_GRABSECT1R_BITS  bit;
};

struct Z1_GRABSECT2R_BITS {             // bits description
    Uint16 GRAB_SECT16:2;               // 1:0 Grab Flash Sector 16
    Uint16 GRAB_SECT17:2;               // 3:2 Grab Flash Sector 17
    Uint16 GRAB_SECT18:2;               // 5:4 Grab Flash Sector 18
    Uint16 GRAB_SECT19:2;               // 7:6 Grab Flash Sector 19
    Uint16 GRAB_SECT20:2;               // 9:8 Grab Flash Sector 20
    Uint16 GRAB_SECT21:2;               // 11:10 Grab Flash Sector 21
    Uint16 GRAB_SECT22:2;               // 13:12 Grab Flash Sector 22
    Uint16 GRAB_SECT23:2;               // 15:14 Grab Flash Sector 23
    Uint16 GRAB_SECT24:2;               // 17:16 Grab Flash Sector 24
    Uint16 GRAB_SECT25:2;               // 19:18 Grab Flash Sector 25
    Uint16 GRAB_SECT26:2;               // 21:20 Grab Flash Sector 26
    Uint16 GRAB_SECT27:2;               // 23:22 Grab Flash Sector 27
    Uint16 GRAB_SECT28:2;               // 25:24 Grab Flash Sector 28
    Uint16 GRAB_SECT29:2;               // 27:26 Grab Flash Sector 29
    Uint16 GRAB_SECT30:2;               // 29:28 Grab Flash Sector 30
    Uint16 GRAB_SECT31:2;               // 31:30 Grab Flash Sector 31
};

union Z1_GRABSECT2R_REG {
    Uint32  all;
    struct  Z1_GRABSECT2R_BITS  bit;
};

struct Z1_GRABSECT3R_BITS {             // bits description
    Uint16 rsvd1:2;                     // 1:0 Reserved
    Uint16 rsvd2:2;                     // 3:2 Reserved
    Uint16 rsvd3:2;                     // 5:4 Reserved
    Uint16 rsvd4:2;                     // 7:6 Reserved
    Uint16 GRAB_SECT39_32:2;            // 9:8 Grab Flash Sectors 39-32
    Uint16 GRAB_SECT47_40:2;            // 11:10 Grab Flash Sectors 47-40
    Uint16 GRAB_SECT55_48:2;            // 13:12 Grab Flash Sectors 55-48
    Uint16 GRAB_SECT63_56:2;            // 15:14 Grab Flash Sectors 63-56
    Uint16 GRAB_SECT71_64:2;            // 17:16 Grab Flash Sectors 71_64
    Uint16 GRAB_SECT79_72:2;            // 19:18 Grab Flash Sectors 79-72
    Uint16 GRAB_SECT87_80:2;            // 21:20 Grab Flash Sectors 87-80
    Uint16 GRAB_SECT95_88:2;            // 23:22 Grab Flash Sectors 95-88
    Uint16 GRAB_SECT103_96:2;           // 25:24 Grab Flash Sectors 103-96
    Uint16 GRAB_SECT111_104:2;          // 27:26 Grab Flash Sectors 111_104
    Uint16 GRAB_SECT119_112:2;          // 29:28 Grab Flash Sectors 119-112
    Uint16 GRAB_SECT127_120:2;          // 31:30 Grab Flash Sectors 127-120
};

union Z1_GRABSECT3R_REG {
    Uint32  all;
    struct  Z1_GRABSECT3R_BITS  bit;
};

struct Z1_GRABRAM1R_BITS {              // bits description
    Uint16 GRAB_RAM0:2;                 // 1:0 Grab RAM LS0 Section A
    Uint16 GRAB_RAM1:2;                 // 3:2 Grab RAM LS0 Section B
    Uint16 GRAB_RAM2:2;                 // 5:4 Grab RAM LS0 Section C
    Uint16 GRAB_RAM3:2;                 // 7:6 Grab RAM LS0 Section D
    Uint16 GRAB_RAM4:2;                 // 9:8 Grab RAM LS1 Section A
    Uint16 GRAB_RAM5:2;                 // 11:10 Grab RAM LS1 Section B
    Uint16 GRAB_RAM6:2;                 // 13:12 Grab RAM LS1 Section C
    Uint16 GRAB_RAM7:2;                 // 15:14 Grab RAM LS1 Section D
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union Z1_GRABRAM1R_REG {
    Uint32  all;
    struct  Z1_GRABRAM1R_BITS  bit;
};

struct Z1_EXEONLYSECT1R_BITS {          // bits description
    Uint16 EXEONLY_SECT0:1;             // 0 Execute-Only Flash Sector 0
    Uint16 EXEONLY_SECT1:1;             // 1 Execute-Only Flash Sector 1
    Uint16 EXEONLY_SECT2:1;             // 2 Execute-Only Flash Sector 2
    Uint16 EXEONLY_SECT3:1;             // 3 Execute-Only Flash Sector 3
    Uint16 EXEONLY_SECT4:1;             // 4 Execute-Only Flash Sector 4
    Uint16 EXEONLY_SECT5:1;             // 5 Execute-Only Flash Sector 5
    Uint16 EXEONLY_SECT6:1;             // 6 Execute-Only Flash Sector 6
    Uint16 EXEONLY_SECT7:1;             // 7 Execute-Only Flash Sector 7
    Uint16 EXEONLY_SECT8:1;             // 8 Execute-Only Flash Sector 8
    Uint16 EXEONLY_SECT9:1;             // 9 Execute-Only Flash Sector 9
    Uint16 EXEONLY_SECT10:1;            // 10 Execute-Only Flash Sector 10
    Uint16 EXEONLY_SECT11:1;            // 11 Execute-Only Flash Sector 11
    Uint16 EXEONLY_SECT12:1;            // 12 Execute-Only Flash Sector 12
    Uint16 EXEONLY_SECT13:1;            // 13 Execute-Only Flash Sector 13
    Uint16 EXEONLY_SECT14:1;            // 14 Execute-Only Flash Sector 14
    Uint16 EXEONLY_SECT15:1;            // 15 Execute-Only Flash Sector 15
    Uint16 EXEONLY_SECT16:1;            // 16 Execute-Only Flash Sector 16
    Uint16 EXEONLY_SECT17:1;            // 17 Execute-Only Flash Sector 17
    Uint16 EXEONLY_SECT18:1;            // 18 Execute-Only Flash Sector 18
    Uint16 EXEONLY_SECT19:1;            // 19 Execute-Only Flash Sector 19
    Uint16 EXEONLY_SECT20:1;            // 20 Execute-Only Flash Sector 20
    Uint16 EXEONLY_SECT21:1;            // 21 Execute-Only Flash Sector 21
    Uint16 EXEONLY_SECT22:1;            // 22 Execute-Only Flash Sector 22
    Uint16 EXEONLY_SECT23:1;            // 23 Execute-Only Flash Sector 23
    Uint16 EXEONLY_SECT24:1;            // 24 Execute-Only Flash Sector 24
    Uint16 EXEONLY_SECT25:1;            // 25 Execute-Only Flash Sector 25
    Uint16 EXEONLY_SECT26:1;            // 26 Execute-Only Flash Sector 26
    Uint16 EXEONLY_SECT27:1;            // 27 Execute-Only Flash Sector 27
    Uint16 EXEONLY_SECT28:1;            // 28 Execute-Only Flash Sector 28
    Uint16 EXEONLY_SECT29:1;            // 29 Execute-Only Flash Sector 29
    Uint16 EXEONLY_SECT30:1;            // 30 Execute-Only Flash Sector 30
    Uint16 EXEONLY_SECT31:1;            // 31 Execute-Only Flash Sector 31
};

union Z1_EXEONLYSECT1R_REG {
    Uint32  all;
    struct  Z1_EXEONLYSECT1R_BITS  bit;
};

struct Z1_EXEONLYSECT2R_BITS {          // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 rsvd2:1;                     // 1 Reserved
    Uint16 rsvd3:1;                     // 2 Reserved
    Uint16 rsvd4:1;                     // 3 Reserved
    Uint16 EXEONLY_SECT39_32:1;         // 4 Execute-Only Flash Sectors 39_32
    Uint16 EXEONLY_SECT47_40:1;         // 5 Execute-Only Flash Sectors 47-40
    Uint16 EXEONLY_SECT55_48:1;         // 6 Execute-Only Flash Sectors 55-48
    Uint16 EXEONLY_SECT63_56:1;         // 7 Execute-Only Flash Sectors 63-56
    Uint16 EXEONLY_SECT71_64:1;         // 8 Execute-Only Flash Sectors 71-64
    Uint16 EXEONLY_SECT79_72:1;         // 9 Execute-Only Flash Sectors 79-72
    Uint16 EXEONLY_SECT87_80:1;         // 10 Execute-Only Flash Sectors 87-80
    Uint16 EXEONLY_SECT95_88:1;         // 11 Execute-Only Flash Sectors 95-88
    Uint16 EXEONLY_SECT103_96:1;        // 12 Execute-Only Flash Sectors 103-96
    Uint16 EXEONLY_SECT111_104:1;       // 13 Execute-Only Flash Sectors 111-104
    Uint16 EXEONLY_SECT119_112:1;       // 14 Execute-Only Flash Sectors 119-112
    Uint16 EXEONLY_SECT127_120:1;       // 15 Execute-Only Flash Sectors 127-120
    Uint16 rsvd5:16;                    // 31:16 Reserved
};

union Z1_EXEONLYSECT2R_REG {
    Uint32  all;
    struct  Z1_EXEONLYSECT2R_BITS  bit;
};

struct Z1_EXEONLYRAM1R_BITS {           // bits description
    Uint16 EXEONLY_RAM0:1;              // 0 Execute-Only RAM LS0 Section A
    Uint16 EXEONLY_RAM1:1;              // 1 Execute-Only RAM LS0 Section B
    Uint16 EXEONLY_RAM2:1;              // 2 Execute-Only RAM LS0 Section C
    Uint16 EXEONLY_RAM3:1;              // 3 Execute-Only RAM LS0 Section D
    Uint16 EXEONLY_RAM4:1;              // 4 Execute-Only RAM LS1 Section A
    Uint16 EXEONLY_RAM5:1;              // 5 Execute-Only RAM LS1 Section B
    Uint16 EXEONLY_RAM6:1;              // 6 Execute-Only RAM LS1 Section C
    Uint16 EXEONLY_RAM7:1;              // 7 Execute-Only RAM LS1 Section D
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
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
    Uint16                                   rsvd1[4];                     // Reserved
    union   Z1_EXEONLYSECT1R_REG             Z1_EXEONLYSECT1R;             // Zone 1 Execute Only Flash Status Register 1
    union   Z1_EXEONLYSECT2R_REG             Z1_EXEONLYSECT2R;             // Zone 1 Execute Only Flash Status Register 2
    union   Z1_EXEONLYRAM1R_REG              Z1_EXEONLYRAM1R;              // Zone 1 Execute Only RAM Status Register 1
    Uint16                                   rsvd2[2];                     // Reserved
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
    Uint16 rsvd2:4;                     // 11:8 Reserved
    Uint16 rsvd3:4;                     // 15:12 Reserved
    Uint16 rsvd4:16;                    // 31:16 Reserved
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
    Uint16 GRAB_SECT0:2;                // 1:0 Grab Flash Sector 0
    Uint16 GRAB_SECT1:2;                // 3:2 Grab Flash Sector 1
    Uint16 GRAB_SECT2:2;                // 5:4 Grab Flash Sector 2
    Uint16 GRAB_SECT3:2;                // 7:6 Grab Flash Sector 3
    Uint16 GRAB_SECT4:2;                // 9:8 Grab Flash Sector 4
    Uint16 GRAB_SECT5:2;                // 11:10 Grab Flash Sector 5
    Uint16 GRAB_SECT6:2;                // 13:12 Grab Flash Sector 6
    Uint16 GRAB_SECT7:2;                // 15:14 Grab Flash Sector 7
    Uint16 GRAB_SECT8:2;                // 17:16 Grab Flash Sector 8
    Uint16 GRAB_SECT9:2;                // 19:18 Grab Flash Sector 9
    Uint16 GRAB_SECT10:2;               // 21:20 Grab Flash Sector 10
    Uint16 GRAB_SECT11:2;               // 23:22 Grab Flash Sector 11
    Uint16 GRAB_SECT12:2;               // 25:24 Grab Flash Sector 12
    Uint16 GRAB_SECT13:2;               // 27:26 Grab Flash Sector 13
    Uint16 GRAB_SECT14:2;               // 29:28 Grab Flash Sector 14
    Uint16 GRAB_SECT15:2;               // 31:30 Grab Flash Sector 15
};

union Z2_GRABSECT1R_REG {
    Uint32  all;
    struct  Z2_GRABSECT1R_BITS  bit;
};

struct Z2_GRABSECT2R_BITS {             // bits description
    Uint16 GRAB_SECT16:2;               // 1:0 Grab Flash Sector 16
    Uint16 GRAB_SECT17:2;               // 3:2 Grab Flash Sector 17
    Uint16 GRAB_SECT18:2;               // 5:4 Grab Flash Sector 18
    Uint16 GRAB_SECT19:2;               // 7:6 Grab Flash Sector 19
    Uint16 GRAB_SECT20:2;               // 9:8 Grab Flash Sector 20
    Uint16 GRAB_SECT21:2;               // 11:10 Grab Flash Sector 21
    Uint16 GRAB_SECT22:2;               // 13:12 Grab Flash Sector 22
    Uint16 GRAB_SECT23:2;               // 15:14 Grab Flash Sector 23
    Uint16 GRAB_SECT24:2;               // 17:16 Grab Flash Sector 24
    Uint16 GRAB_SECT25:2;               // 19:18 Grab Flash Sector 25
    Uint16 GRAB_SECT26:2;               // 21:20 Grab Flash Sector 26
    Uint16 GRAB_SECT27:2;               // 23:22 Grab Flash Sector 27
    Uint16 GRAB_SECT28:2;               // 25:24 Grab Flash Sector 28
    Uint16 GRAB_SECT29:2;               // 27:26 Grab Flash Sector 29
    Uint16 GRAB_SECT30:2;               // 29:28 Grab Flash Sector 30
    Uint16 GRAB_SECT31:2;               // 31:30 Grab Flash Sector 31
};

union Z2_GRABSECT2R_REG {
    Uint32  all;
    struct  Z2_GRABSECT2R_BITS  bit;
};

struct Z2_GRABSECT3R_BITS {             // bits description
    Uint16 rsvd1:2;                     // 1:0 Reserved
    Uint16 rsvd2:2;                     // 3:2 Reserved
    Uint16 rsvd3:2;                     // 5:4 Reserved
    Uint16 rsvd4:2;                     // 7:6 Reserved
    Uint16 GRAB_SECT39_32:2;            // 9:8 Grab Flash Sectors 39-32
    Uint16 GRAB_SECT47_40:2;            // 11:10 Grab Flash Sectors 47-40
    Uint16 GRAB_SECT55_48:2;            // 13:12 Grab Flash Sectors 55-48
    Uint16 GRAB_SECT63_56:2;            // 15:14 Grab Flash Sectors 63-56
    Uint16 GRAB_SECT71_64:2;            // 17:16 Grab Flash Sectors 71_64
    Uint16 GRAB_SECT79_72:2;            // 19:18 Grab Flash Sectors 79-72
    Uint16 GRAB_SECT87_80:2;            // 21:20 Grab Flash Sectors 87-80
    Uint16 GRAB_SECT95_88:2;            // 23:22 Grab Flash Sectors 95-88
    Uint16 GRAB_SECT103_96:2;           // 25:24 Grab Flash Sectors 103-96
    Uint16 GRAB_SECT111_104:2;          // 27:26 Grab Flash Sectors 111_104
    Uint16 GRAB_SECT119_112:2;          // 29:28 Grab Flash Sectors 119-112
    Uint16 GRAB_SECT127_120:2;          // 31:30 Grab Flash Sectors 127-120
};

union Z2_GRABSECT3R_REG {
    Uint32  all;
    struct  Z2_GRABSECT3R_BITS  bit;
};

struct Z2_GRABRAM1R_BITS {              // bits description
    Uint16 GRAB_RAM0:2;                 // 1:0 Grab RAM LS0 Section A
    Uint16 GRAB_RAM1:2;                 // 3:2 Grab RAM LS0 Section B
    Uint16 GRAB_RAM2:2;                 // 5:4 Grab RAM LS0 Section C
    Uint16 GRAB_RAM3:2;                 // 7:6 Grab RAM LS0 Section D
    Uint16 GRAB_RAM4:2;                 // 9:8 Grab RAM LS1 Section A
    Uint16 GRAB_RAM5:2;                 // 11:10 Grab RAM LS1 Section B
    Uint16 GRAB_RAM6:2;                 // 13:12 Grab RAM LS1 Section C
    Uint16 GRAB_RAM7:2;                 // 15:14 Grab RAM LS1 Section D
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union Z2_GRABRAM1R_REG {
    Uint32  all;
    struct  Z2_GRABRAM1R_BITS  bit;
};

struct Z2_EXEONLYSECT1R_BITS {          // bits description
    Uint16 EXEONLY_SECT0:1;             // 0 Execute-Only Flash Sector 0
    Uint16 EXEONLY_SECT1:1;             // 1 Execute-Only Flash Sector 1
    Uint16 EXEONLY_SECT2:1;             // 2 Execute-Only Flash Sector 2
    Uint16 EXEONLY_SECT3:1;             // 3 Execute-Only Flash Sector 3
    Uint16 EXEONLY_SECT4:1;             // 4 Execute-Only Flash Sector 4
    Uint16 EXEONLY_SECT5:1;             // 5 Execute-Only Flash Sector 5
    Uint16 EXEONLY_SECT6:1;             // 6 Execute-Only Flash Sector 6
    Uint16 EXEONLY_SECT7:1;             // 7 Execute-Only Flash Sector 7
    Uint16 EXEONLY_SECT8:1;             // 8 Execute-Only Flash Sector 8
    Uint16 EXEONLY_SECT9:1;             // 9 Execute-Only Flash Sector 9
    Uint16 EXEONLY_SECT10:1;            // 10 Execute-Only Flash Sector 10
    Uint16 EXEONLY_SECT11:1;            // 11 Execute-Only Flash Sector 11
    Uint16 EXEONLY_SECT12:1;            // 12 Execute-Only Flash Sector 12
    Uint16 EXEONLY_SECT13:1;            // 13 Execute-Only Flash Sector 13
    Uint16 EXEONLY_SECT14:1;            // 14 Execute-Only Flash Sector 14
    Uint16 EXEONLY_SECT15:1;            // 15 Execute-Only Flash Sector 15
    Uint16 EXEONLY_SECT16:1;            // 16 Execute-Only Flash Sector 16
    Uint16 EXEONLY_SECT17:1;            // 17 Execute-Only Flash Sector 17
    Uint16 EXEONLY_SECT18:1;            // 18 Execute-Only Flash Sector 18
    Uint16 EXEONLY_SECT19:1;            // 19 Execute-Only Flash Sector 19
    Uint16 EXEONLY_SECT20:1;            // 20 Execute-Only Flash Sector 20
    Uint16 EXEONLY_SECT21:1;            // 21 Execute-Only Flash Sector 21
    Uint16 EXEONLY_SECT22:1;            // 22 Execute-Only Flash Sector 22
    Uint16 EXEONLY_SECT23:1;            // 23 Execute-Only Flash Sector 23
    Uint16 EXEONLY_SECT24:1;            // 24 Execute-Only Flash Sector 24
    Uint16 EXEONLY_SECT25:1;            // 25 Execute-Only Flash Sector 25
    Uint16 EXEONLY_SECT26:1;            // 26 Execute-Only Flash Sector 26
    Uint16 EXEONLY_SECT27:1;            // 27 Execute-Only Flash Sector 27
    Uint16 EXEONLY_SECT28:1;            // 28 Execute-Only Flash Sector 28
    Uint16 EXEONLY_SECT29:1;            // 29 Execute-Only Flash Sector 29
    Uint16 EXEONLY_SECT30:1;            // 30 Execute-Only Flash Sector 30
    Uint16 EXEONLY_SECT31:1;            // 31 Execute-Only Flash Sector 31
};

union Z2_EXEONLYSECT1R_REG {
    Uint32  all;
    struct  Z2_EXEONLYSECT1R_BITS  bit;
};

struct Z2_EXEONLYSECT2R_BITS {          // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 rsvd2:1;                     // 1 Reserved
    Uint16 rsvd3:1;                     // 2 Reserved
    Uint16 rsvd4:1;                     // 3 Reserved
    Uint16 EXEONLY_SECT39_32:1;         // 4 Execute-Only Flash Sectors 39-32
    Uint16 EXEONLY_SECT47_40:1;         // 5 Execute-Only Flash Sectors 47-40
    Uint16 EXEONLY_SECT55_48:1;         // 6 Execute-Only Flash Sectors 55-48
    Uint16 EXEONLY_SECT63_56:1;         // 7 Execute-Only Flash Sectors 63-56
    Uint16 EXEONLY_SECT71_64:1;         // 8 Execute-Only Flash Sectors 71-64
    Uint16 EXEONLY_SECT79_72:1;         // 9 Execute-Only Flash Sectors 79-72
    Uint16 EXEONLY_SECT87_80:1;         // 10 Execute-Only Flash Sectors 87-80
    Uint16 EXEONLY_SECT95_88:1;         // 11 Execute-Only Flash Sectors 95-88
    Uint16 EXEONLY_SECT103_96:1;        // 12 Execute-Only Flash Sectors 103-96
    Uint16 EXEONLY_SECT111_104:1;       // 13 Execute-Only Flash Sectors 111-104
    Uint16 EXEONLY_SECT119_112:1;       // 14 Execute-Only Flash Sectors 119-112
    Uint16 EXEONLY_SECT127_120:1;       // 15 Execute-Only Flash Sectors 127-120
    Uint16 rsvd5:16;                    // 31:16 Reserved
};

union Z2_EXEONLYSECT2R_REG {
    Uint32  all;
    struct  Z2_EXEONLYSECT2R_BITS  bit;
};

struct Z2_EXEONLYRAM1R_BITS {           // bits description
    Uint16 EXEONLY_RAM0:1;              // 0 Execute-Only RAM LS0 Section A
    Uint16 EXEONLY_RAM1:1;              // 1 Execute-Only RAM LS0 Section B
    Uint16 EXEONLY_RAM2:1;              // 2 Execute-Only RAM LS0 Section C
    Uint16 EXEONLY_RAM3:1;              // 3 Execute-Only RAM LS0 Section D
    Uint16 EXEONLY_RAM4:1;              // 4 Execute-Only RAM LS1 Section A
    Uint16 EXEONLY_RAM5:1;              // 5 Execute-Only RAM LS1 Section B
    Uint16 EXEONLY_RAM6:1;              // 6 Execute-Only RAM LS1 Section C
    Uint16 EXEONLY_RAM7:1;              // 7 Execute-Only RAM LS1 Section D
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
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
    Uint16                                   rsvd2[4];                     // Reserved
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
    Uint16 STATUS_SECT0:2;              // 1:0 Zone Status Flash Bank 0 Sector 0
    Uint16 STATUS_SECT1:2;              // 3:2 Zone Status Flash Bank 0 Sector 1
    Uint16 STATUS_SECT2:2;              // 5:4 Zone Status Flash Bank 0 Sector 2
    Uint16 STATUS_SECT3:2;              // 7:6 Zone Status Flash Bank 0 Sector 3
    Uint16 STATUS_SECT4:2;              // 9:8 Zone Status Flash Bank 0 Sector 4
    Uint16 STATUS_SECT5:2;              // 11:10 Zone Status Flash Bank 0 Sector 5
    Uint16 STATUS_SECT6:2;              // 13:12 Zone Status Flash Bank 0 Sector 6
    Uint16 STATUS_SECT7:2;              // 15:14 Zone Status Flash Bank 0 Sector 7
    Uint16 STATUS_SECT8:2;              // 17:16 Zone Status Flash Bank 0 Sector 8
    Uint16 STATUS_SECT9:2;              // 19:18 Zone Status Flash Bank 0 Sector 9
    Uint16 STATUS_SECT10:2;             // 21:20 Zone Status Flash Bank 0 Sector 10
    Uint16 STATUS_SECT11:2;             // 23:22 Zone Status Flash Bank 0 Sector 11
    Uint16 STATUS_SECT12:2;             // 25:24 Zone Status Flash Bank 0 Sector 12
    Uint16 STATUS_SECT13:2;             // 27:26 Zone Status Flash Bank 0 Sector 13
    Uint16 STATUS_SECT14:2;             // 29:28 Zone Status Flash Bank 0 Sector 14
    Uint16 STATUS_SECT15:2;             // 31:30 Zone Status Flash Bank 0 Sector 15
};

union SECTSTAT1_REG {
    Uint32  all;
    struct  SECTSTAT1_BITS  bit;
};

struct SECTSTAT2_BITS {                 // bits description
    Uint16 STATUS_SECT16:2;             // 1:0 Zone Status Flash Bank 0 Sector 16
    Uint16 STATUS_SECT17:2;             // 3:2 Zone Status Flash Bank 0 Sector 17
    Uint16 STATUS_SECT18:2;             // 5:4 Zone Status Flash Bank 0 Sector 18
    Uint16 STATUS_SECT19:2;             // 7:6 Zone Status Flash Bank 0 Sector 19
    Uint16 STATUS_SECT20:2;             // 9:8 Zone Status Flash Bank 0 Sector 20
    Uint16 STATUS_SECT21:2;             // 11:10 Zone Status Flash Bank 0 Sector 21
    Uint16 STATUS_SECT22:2;             // 13:12 Zone Status Flash Bank 0 Sector 22
    Uint16 STATUS_SECT23:2;             // 15:14 Zone Status Flash Bank 0 Sector 23
    Uint16 STATUS_SECT24:2;             // 17:16 Zone Status Flash Bank 0 Sector 24
    Uint16 STATUS_SECT25:2;             // 19:18 Zone Status Flash Bank 0 Sector 25
    Uint16 STATUS_SECT26:2;             // 21:20 Zone Status Flash Bank 0 Sector 26
    Uint16 STATUS_SECT27:2;             // 23:22 Zone Status Flash Bank 0 Sector 27
    Uint16 STATUS_SECT28:2;             // 25:24 Zone Status Flash Bank 0 Sector 28
    Uint16 STATUS_SECT29:2;             // 27:26 Zone Status Flash Bank 0 Sector 29
    Uint16 STATUS_SECT30:2;             // 29:28 Zone Status Flash Bank 0 Sector 30
    Uint16 STATUS_SECT31:2;             // 31:30 Zone Status Flash Bank 0 Sector 31
};

union SECTSTAT2_REG {
    Uint32  all;
    struct  SECTSTAT2_BITS  bit;
};

struct SECTSTAT3_BITS {                 // bits description
    Uint16 rsvd1:2;                     // 1:0 Reserved
    Uint16 rsvd2:2;                     // 3:2 Reserved
    Uint16 rsvd3:2;                     // 5:4 Reserved
    Uint16 rsvd4:2;                     // 7:6 Reserved
    Uint16 STATUS_SECT39_32:2;          // 9:8 Zone Status flash Bank 0 Sectors 39-32
    Uint16 STATUS_SECT47_40:2;          // 11:10 Zone Status flash Bank 0 Sectors 47-40
    Uint16 STATUS_SECT55_48:2;          // 13:12 Zone Status flash Bank 0 Sectors 55-48
    Uint16 STATUS_SECT63_56:2;          // 15:14 Zone Status flash Bank 0 Sectors 63-56
    Uint16 STATUS_SECT71_64:2;          // 17:16 Zone Status flash Bank 0 Sectors 71-64
    Uint16 STATUS_SECT79_72:2;          // 19:18 Zone Status flash Bank 0 Sectors 79-72
    Uint16 STATUS_SECT87_80:2;          // 21:20 Zone Status flash Bank 0 Sectors 87-80
    Uint16 STATUS_SECT95_88:2;          // 23:22 Zone Status flash Bank 0 Sectors 95-88
    Uint16 STATUS_SECT103_96:2;         // 25:24 Zone Status flash Bank 0 Sectors 103-96
    Uint16 STATUS_SECT111_104:2;        // 27:26 Zone Status flash Bank 0 Sectors 111-104
    Uint16 STATUS_SECT119_112:2;        // 29:28 Zone Status flash Bank 0 Sectors 119-112
    Uint16 STATUS_SECT127_120:2;        // 31:30 Zone Status flash Bank 0 Sectors 127-120
};

union SECTSTAT3_REG {
    Uint32  all;
    struct  SECTSTAT3_BITS  bit;
};

struct RAMSTAT1_BITS {                  // bits description
    Uint16 STATUS_RAM0:2;               // 1:0 Zone Status RAM LS0 Section A
    Uint16 STATUS_RAM1:2;               // 3:2 Zone Status RAM LS0 Section B
    Uint16 STATUS_RAM2:2;               // 5:4 Zone Status RAM LS0 Section C
    Uint16 STATUS_RAM3:2;               // 7:6 Zone Status RAM LS0 Section D
    Uint16 STATUS_RAM4:2;               // 9:8 Zone Status RAM LS1 Section A
    Uint16 STATUS_RAM5:2;               // 11:10 Zone Status RAM LS1 Section B
    Uint16 STATUS_RAM6:2;               // 13:12 Zone Status RAM LS1 Section C
    Uint16 STATUS_RAM7:2;               // 15:14 Zone Status RAM LS1 Section D
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union RAMSTAT1_REG {
    Uint32  all;
    struct  RAMSTAT1_BITS  bit;
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

struct DENYCODE_BITS {                  // bits description
    Uint16 BLOCKED:1;                   // 0 Blocked Code
    Uint16 ILLADDR:1;                   // 1 Illegal Address Code
    Uint16 ILLPROG:1;                   // 2 Illegal Program Address
    Uint16 ILLERASE:1;                  // 3 Illegal Erase Address
    Uint16 ILLRDVER:1;                  // 4 Illegal Read Verify Address
    Uint16 ILLMODECH:1;                 // 5 Illegal Mode Change
    Uint16 ILLCMD:1;                    // 6 Illegal Command
    Uint16 ILLSIZE:1;                   // 7 Illegal Command Size
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union DENYCODE_REG {
    Uint32  all;
    struct  DENYCODE_BITS  bit;
};

struct RAMOPENSTAT_BITS {               // bits description
    Uint16 RAMOPEN:1;                   // 0 RAM Security Open
    Uint16 rsvd1:15;                    // 15:1 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union RAMOPENSTAT_REG {
    Uint32  all;
    struct  RAMOPENSTAT_BITS  bit;
};

struct RAMOPENFRC_BITS {                // bits description
    Uint16 SET:1;                       // 0 Set RAM Open request
    Uint16 rsvd1:15;                    // 15:1 Reserved
    Uint16 KEY:16;                      // 31:16 Valid Write KEY
};

union RAMOPENFRC_REG {
    Uint32  all;
    struct  RAMOPENFRC_BITS  bit;
};

struct RAMOPENCLR_BITS {                // bits description
    Uint16 CLEAR:1;                     // 0 Clear RAM Open request
    Uint16 rsvd1:15;                    // 15:1 Reserved
    Uint16 KEY:16;                      // 31:16 Valid Write KEY
};

union RAMOPENCLR_REG {
    Uint32  all;
    struct  RAMOPENCLR_BITS  bit;
};

struct RAMOPENLOCK_BITS {               // bits description
    Uint16 LOCK:1;                      // 0 RAMOPEN Lock
    Uint16 rsvd1:15;                    // 15:1 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union RAMOPENLOCK_REG {
    Uint32  all;
    struct  RAMOPENLOCK_BITS  bit;
};

struct DCSM_COMMON_REGS {
    union   FLSEM_REG                        FLSEM;                        // Flash Wrapper Semaphore Register
    Uint16                                   rsvd1[6];                     // Reserved
    union   SECTSTAT1_REG                    SECTSTAT1;                    // Flash Sectors Status Register 1
    union   SECTSTAT2_REG                    SECTSTAT2;                    // Flash Sectors Status Register 2
    union   SECTSTAT3_REG                    SECTSTAT3;                    // Flash Sectors Status Register 3
    Uint16                                   rsvd2[2];                     // Reserved
    union   RAMSTAT1_REG                     RAMSTAT1;                     // RAM Status Register 1
    Uint16                                   rsvd3[6];                     // Reserved
    union   SECERRSTAT_REG                   SECERRSTAT;                   // Security Error Status Register
    union   SECERRCLR_REG                    SECERRCLR;                    // Security Error Clear Register
    union   SECERRFRC_REG                    SECERRFRC;                    // Security Error Force Register
    union   DENYCODE_REG                     DENYCODE;                     // Flash Authorization Denial Code
    union   RAMOPENSTAT_REG                  RAMOPENSTAT;                  // RAM Security Open Status Register
    union   RAMOPENFRC_REG                   RAMOPENFRC;                   // RAM Security Open Force Register
    union   RAMOPENCLR_REG                   RAMOPENCLR;                   // RAM Security Open Clear Register
    union   RAMOPENLOCK_REG                  RAMOPENLOCK;                  // RAMOPEN Lock Register
};

//---------------------------------------------------------------------------
// DCSM External References & Function Declarations:
//
extern volatile struct DCSM_Z1_REGS DcsmZ1Regs;
extern volatile struct DCSM_Z2_REGS DcsmZ2Regs;
extern volatile struct DCSM_COMMON_REGS DcsmCommonRegs;
extern volatile struct DCSM_Z1_OTP DcsmZ1OtpRegs;
extern volatile struct DCSM_Z2_OTP DcsmZ2OtpRegs;
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
