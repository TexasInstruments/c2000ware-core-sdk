//###########################################################################
//
// FILE:    f28p65x_dcsm.h
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

#ifndef F28P65X_DCSM_H
#define F28P65X_DCSM_H

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
    Uint16 rsvd7:1;                     // 22 Reserved
    Uint16 rsvd8:1;                     // 23 Reserved
    Uint16 rsvd9:7;                     // 30:24 Reserved
    Uint16 FORCESEC:1;                  // 31 Force Secure
};

union Z1_CR_REG {
    Uint32  all;
    struct  Z1_CR_BITS  bit;
};

struct Z1_GRABSECT1R_BITS {             // bits description
    Uint16 GRAB_B0_SECT0:2;             // 1:0 Grab Flash Bank0 Sector 0
    Uint16 GRAB_B0_SECT1:2;             // 3:2 Grab Flash Bank0 Sector 1
    Uint16 GRAB_B0_SECT2:2;             // 5:4 Grab Flash Bank0 Sector 2
    Uint16 GRAB_B0_SECT3:2;             // 7:6 Grab Flash Bank0 Sector 3
    Uint16 GRAB_B0_SECT31_4:2;          // 9:8 Grab Flash Bank0 Sector 31-4
    Uint16 GRAB_B0_SECT63_32:2;         // 11:10 Grab Flash Bank0 Sector 63-32
    Uint16 GRAB_B0_SECT95_64:2;         // 13:12 Grab Flash Bank0 Sector 95-64
    Uint16 GRAB_B0_SECT127_96:2;        // 15:14 Grab Flash Bank1 Sector 127-96
    Uint16 GRAB_B1_SECT0:2;             // 17:16 Grab Flash Bank1 Sector 0
    Uint16 GRAB_B1_SECT1:2;             // 19:18 Grab Flash Bank1 Sector 1
    Uint16 GRAB_B1_SECT2:2;             // 21:20 Grab Flash Bank1 Sector 2
    Uint16 GRAB_B1_SECT3:2;             // 23:22 Grab Flash Bank1 Sector 3
    Uint16 GRAB_B1_SECT31_4:2;          // 25:24 Grab Flash Bank1 Sector 31-4
    Uint16 GRAB_B1_SECT63_32:2;         // 27:26 Grab Flash Bank1 Sector 63-32
    Uint16 GRAB_B1_SECT95_64:2;         // 29:28 Grab Flash Bank1 Sector 95-64
    Uint16 GRAB_B1_SECT127_96:2;        // 31:30 Grab Flash Bank1 Sector 127-96
};

union Z1_GRABSECT1R_REG {
    Uint32  all;
    struct  Z1_GRABSECT1R_BITS  bit;
};

struct Z1_GRABSECT2R_BITS {             // bits description
    Uint16 GRAB_B2_SECT0:2;             // 1:0 Grab Flash Bank2 Sector 0
    Uint16 GRAB_B2_SECT1:2;             // 3:2 Grab Flash Bank2 Sector 1
    Uint16 GRAB_B2_SECT2:2;             // 5:4 Grab Flash Bank2 Sector 2
    Uint16 GRAB_B2_SECT3:2;             // 7:6 Grab Flash Bank2 Sector 3
    Uint16 GRAB_B2_SECT31_4:2;          // 9:8 Grab Flash Bank2 Sector 31-4
    Uint16 GRAB_B2_SECT63_32:2;         // 11:10 Grab Flash Bank2 Sector 63-32
    Uint16 GRAB_B2_SECT95_64:2;         // 13:12 Grab Flash Bank2 Sector 95-64
    Uint16 GRAB_B2_SECT127_96:2;        // 15:14 Grab Flash Bank2 Sector 127-96
    Uint16 GRAB_B3_SECT0:2;             // 17:16 Grab Flash Bank3 Sector 0
    Uint16 GRAB_B3_SECT1:2;             // 19:18 Grab Flash Bank3 Sector 1
    Uint16 GRAB_B3_SECT2:2;             // 21:20 Grab Flash Bank3 Sector 2
    Uint16 GRAB_B3_SECT3:2;             // 23:22 Grab Flash Bank3 Sector 3
    Uint16 GRAB_B3_SECT31_4:2;          // 25:24 Grab Flash Bank3 Sector 31-4
    Uint16 GRAB_B3_SECT63_32:2;         // 27:26 Grab Flash Bank3 Sector 63-32
    Uint16 GRAB_B3_SECT95_64:2;         // 29:28 Grab Flash Bank3 Sector 95-64
    Uint16 GRAB_B3_SECT127_96:2;        // 31:30 Grab Flash Bank3 Sector 127-96
};

union Z1_GRABSECT2R_REG {
    Uint32  all;
    struct  Z1_GRABSECT2R_BITS  bit;
};

struct Z1_GRABSECT3R_BITS {             // bits description
    Uint16 GRAB_B4_SECT0:2;             // 1:0 Grab Flash Bank4 Sector 0
    Uint16 GRAB_B4_SECT1:2;             // 3:2 Grab Flash Bank4 Sector 1
    Uint16 GRAB_B4_SECT2:2;             // 5:4 Grab Flash Bank4 Sector 2
    Uint16 GRAB_B4_SECT3:2;             // 7:6 Grab Flash Bank4 Sector 3
    Uint16 GRAB_B4_SECT31_4:2;          // 9:8 Grab Flash Bank4 Sector 31-4
    Uint16 GRAB_B4_SECT63_32:2;         // 11:10 Grab Flash Bank4 Sector 63-32
    Uint16 GRAB_B4_SECT95_64:2;         // 13:12 Grab Flash Bank4 Sector 95-64
    Uint16 GRAB_B4_SECT127_96:2;        // 15:14 Grab Flash Bank4 Sector 127-96
    Uint16 rsvd1:16;                    // 31:16 Reserved
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
    Uint16 GRAB_RAM8:2;                 // 17:16 Grab RAM CPU1.LS8
    Uint16 GRAB_RAM9:2;                 // 19:18 Grab RAM CPU1.LS9
    Uint16 GRAB_RAM10:2;                // 21:20 Grab RAM D0
    Uint16 GRAB_RAM11:2;                // 23:22 Grab RAM D1
    Uint16 GRAB_RAM12:2;                // 25:24 Grab RAM D2
    Uint16 GRAB_RAM13:2;                // 27:26 Grab RAM D3
    Uint16 GRAB_RAM14:2;                // 29:28 Grab RAM D4
    Uint16 GRAB_RAM15:2;                // 31:30 Grab RAM D5
};

union Z1_GRABRAM1R_REG {
    Uint32  all;
    struct  Z1_GRABRAM1R_BITS  bit;
};

struct Z1_GRABRAM2R_BITS {              // bits description
    Uint16 GRAB_RAM12:2;                // 1:0 Grab RAM CPU1TOCPU2 MSGRAM0_L
    Uint16 GRAB_RAM13:2;                // 3:2 Grab RAM CPU1TOCPU2 MSGRAM0_H
    Uint16 GRAB_RAM14:2;                // 5:4 Grab RAM CPU2TOCPU1 MSGRAM0_L
    Uint16 GRAB_RAM15:2;                // 7:6 Grab RAM CPU2TOCPU1 MSGRAM0_H
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union Z1_GRABRAM2R_REG {
    Uint32  all;
    struct  Z1_GRABRAM2R_BITS  bit;
};

struct Z1_EXEONLYSECT1R_BITS {          // bits description
    Uint16 EXEONLY_B0_SECT0:1;          // 0 Execute-Only Flash Bank0 Sector 0
    Uint16 EXEONLY_B0_SECT1:1;          // 1 Execute-Only Flash Bank0 Sector 1
    Uint16 EXEONLY_B0_SECT2:1;          // 2 Execute-Only Flash Bank0 Sector 2
    Uint16 EXEONLY_B0_SECT3:1;          // 3 Execute-Only Flash Bank0 Sector 3
    Uint16 EXEONLY_B0_SECT31_4:1;       // 4 Execute-Only Flash Bank0 Sector 31-4
    Uint16 EXEONLY_B0_SECT63_32:1;      // 5 Execute-Only Flash Bank0 Sector 63-32
    Uint16 EXEONLY_B0_SECT95_64:1;      // 6 Execute-Only Flash Bank0 Sector 95-64
    Uint16 EXEONLY_B0_SECT127_96:1;     // 7 Execute-Only Flash Bank0 Sector 127-96
    Uint16 EXEONLY_B1_SECT0:1;          // 8 Execute-Only Flash Bank1 Sector 0
    Uint16 EXEONLY_B1_SECT1:1;          // 9 Execute-Only Flash Bank1 Sector 1
    Uint16 EXEONLY_B1_SECT2:1;          // 10 Execute-Only Flash Bank1 Sector 2
    Uint16 EXEONLY_B1_SECT3:1;          // 11 Execute-Only Flash Bank1 Sector 3
    Uint16 EXEONLY_B1_SECT31_4:1;       // 12 Execute-Only Flash Bank1 Sector 31-4
    Uint16 EXEONLY_B1_SECT63_32:1;      // 13 Execute-Only Flash Bank1 Sector 63-32
    Uint16 EXEONLY_B1_SECT95_64:1;      // 14 Execute-Only Flash Bank1 Sector 95-64
    Uint16 EXEONLY_B1_SECT127_96:1;     // 15 Execute-Only Flash Bank1 Sector 127-96
    Uint16 EXEONLY_B2_SECT0:1;          // 16 Execute-Only Flash Bank2 Sector 0
    Uint16 EXEONLY_B2_SECT1:1;          // 17 Execute-Only Flash Bank2 Sector 1
    Uint16 EXEONLY_B2_SECT2:1;          // 18 Execute-Only Flash Bank2 Sector 2
    Uint16 EXEONLY_B2_SECT3:1;          // 19 Execute-Only Flash Bank2 Sector 3
    Uint16 EXEONLY_B2_SECT31_4:1;       // 20 Execute-Only Flash Bank2 Sector 31-4
    Uint16 EXEONLY_B2_SECT63_32:1;      // 21 Execute-Only Flash Bank2 Sector 63-32
    Uint16 EXEONLY_B2_SECT95_64:1;      // 22 Execute-Only Flash Bank2 Sector 95-64
    Uint16 EXEONLY_B2_SECT127_96:1;     // 23 Execute-Only Flash Bank2 Sector 127-96
    Uint16 EXEONLY_B3_SECT0:1;          // 24 Execute-Only Flash Bank3 Sector 0
    Uint16 EXEONLY_B3_SECT1:1;          // 25 Execute-Only Flash Bank3 Sector 1
    Uint16 EXEONLY_B3_SECT2:1;          // 26 Execute-Only Flash Bank3 Sector 2
    Uint16 EXEONLY_B3_SECT3:1;          // 27 Execute-Only Flash Bank3 Sector 3
    Uint16 EXEONLY_B3_SECT31_4:1;       // 28 Execute-Only Flash Bank3 Sector 31-4
    Uint16 EXEONLY_B3_SECT63_32:1;      // 29 Execute-Only Flash Bank3 Sector 63-32
    Uint16 EXEONLY_B3_SECT95_64:1;      // 30 Execute-Only Flash Bank3 Sector 95-64
    Uint16 EXEONLY_B3_SECT127_96:1;     // 31 Execute-Only Flash Bank3 Sector 127-96
};

union Z1_EXEONLYSECT1R_REG {
    Uint32  all;
    struct  Z1_EXEONLYSECT1R_BITS  bit;
};

struct Z1_EXEONLYSECT2R_BITS {          // bits description
    Uint16 EXEONLY_B4_SECT0:1;          // 0 Execute-Only Flash Bank4 Sector 0
    Uint16 EXEONLY_B4_SECT1:1;          // 1 Execute-Only Flash Bank4 Sector 1
    Uint16 EXEONLY_B4_SECT2:1;          // 2 Execute-Only Flash Bank4 Sector 2
    Uint16 EXEONLY_B4_SECT3:1;          // 3 Execute-Only Flash Bank4 Sector 3
    Uint16 EXEONLY_B4_SECT31_4:1;       // 4 Execute-Only Flash Bank4 Sector 31-4
    Uint16 EXEONLY_B4_SECT63_32:1;      // 5 Execute-Only Flash Bank4 Sector 63-32
    Uint16 EXEONLY_B4_SECT95_64:1;      // 6 Execute-Only Flash Bank4 Sector 95-64
    Uint16 EXEONLY_B4_SECT127_96:1;     // 7 Execute-Only Flash Bank4 Sector 127-96
    Uint16 rsvd1:8;                     // 15:8 Reserved
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
    Uint16 EXEONLY_RAM8:1;              // 8 Execute-Only RAM CPU1.LS8
    Uint16 EXEONLY_RAM9:1;              // 9 Execute-Only RAM CPU1.LS9
    Uint16 EXEONLY_RAM10:1;             // 10 Execute-Only RAM D0
    Uint16 EXEONLY_RAM11:1;             // 11 Execute-Only RAM D1
    Uint16 EXEONLY_RAM12:1;             // 12 Execute-Only RAM D2
    Uint16 EXEONLY_RAM13:1;             // 13 Execute-Only RAM D3
    Uint16 EXEONLY_RAM14:1;             // 14 Execute-Only RAM D4
    Uint16 EXEONLY_RAM15:1;             // 15 Execute-Only RAM D5
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union Z1_EXEONLYRAM1R_REG {
    Uint32  all;
    struct  Z1_EXEONLYRAM1R_BITS  bit;
};

struct Z1_DIAG_BITS {                   // bits description
    Uint16 rsvd1:2;                     // 1:0 Reserved
    Uint16 rsvd2:2;                     // 3:2 Reserved
    Uint16 MPOST_EN:2;                  // 5:4 MPOST Enable
    Uint16 rsvd3:10;                    // 15:6 Reserved
    Uint16 rsvd4:16;                    // 31:16 Reserved
};

union Z1_DIAG_REG {
    Uint32  all;
    struct  Z1_DIAG_BITS  bit;
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
    Uint16                                   rsvd1[2];                     // Reserved
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
    union   Z1_DIAG_REG                      Z1_DIAG;                      // Diagnostics Configuration Register
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
    Uint16 rsvd7:1;                     // 22 Reserved
    Uint16 rsvd8:1;                     // 23 Reserved
    Uint16 rsvd9:7;                     // 30:24 Reserved
    Uint16 FORCESEC:1;                  // 31 Force Secure
};

union Z2_CR_REG {
    Uint32  all;
    struct  Z2_CR_BITS  bit;
};

struct Z2_GRABSECT1R_BITS {             // bits description
    Uint16 GRAB_B0_SECT0:2;             // 1:0 Grab Flash Bank0 Sector 0
    Uint16 GRAB_B0_SECT1:2;             // 3:2 Grab Flash Bank0 Sector 1
    Uint16 GRAB_B0_SECT2:2;             // 5:4 Grab Flash Bank0 Sector 2
    Uint16 GRAB_B0_SECT3:2;             // 7:6 Grab Flash Bank0 Sector 3
    Uint16 GRAB_B0_SECT31_4:2;          // 9:8 Grab Flash Bank0 Sector 31-4
    Uint16 GRAB_B0_SECT63_32:2;         // 11:10 Grab Flash Bank0 Sector 63-32
    Uint16 GRAB_B0_SECT95_64:2;         // 13:12 Grab Flash Bank0 Sector 95-64
    Uint16 GRAB_B0_SECT127_96:2;        // 15:14 Grab Flash Bank1 Sector 127-96
    Uint16 GRAB_B1_SECT0:2;             // 17:16 Grab Flash Bank1 Sector 0
    Uint16 GRAB_B1_SECT1:2;             // 19:18 Grab Flash Bank1 Sector 1
    Uint16 GRAB_B1_SECT2:2;             // 21:20 Grab Flash Bank1 Sector 2
    Uint16 GRAB_B1_SECT3:2;             // 23:22 Grab Flash Bank1 Sector 3
    Uint16 GRAB_B1_SECT31_4:2;          // 25:24 Grab Flash Bank1 Sector 31-4
    Uint16 GRAB_B1_SECT63_32:2;         // 27:26 Grab Flash Bank1 Sector 63-32
    Uint16 GRAB_B1_SECT95_64:2;         // 29:28 Grab Flash Bank1 Sector 95-64
    Uint16 GRAB_B1_SECT127_96:2;        // 31:30 Grab Flash Bank1 Sector 127-96
};

union Z2_GRABSECT1R_REG {
    Uint32  all;
    struct  Z2_GRABSECT1R_BITS  bit;
};

struct Z2_GRABSECT2R_BITS {             // bits description
    Uint16 GRAB_B2_SECT0:2;             // 1:0 Grab Flash Bank2 Sector 0
    Uint16 GRAB_B2_SECT1:2;             // 3:2 Grab Flash Bank2 Sector 1
    Uint16 GRAB_B2_SECT2:2;             // 5:4 Grab Flash Bank2 Sector 2
    Uint16 GRAB_B2_SECT3:2;             // 7:6 Grab Flash Bank2 Sector 3
    Uint16 GRAB_B2_SECT31_4:2;          // 9:8 Grab Flash Bank2 Sector 31-4
    Uint16 GRAB_B2_SECT63_32:2;         // 11:10 Grab Flash Bank2 Sector 63-32
    Uint16 GRAB_B2_SECT95_64:2;         // 13:12 Grab Flash Bank2 Sector 95-64
    Uint16 GRAB_B2_SECT127_96:2;        // 15:14 Grab Flash Bank2 Sector 127-96
    Uint16 GRAB_B3_SECT0:2;             // 17:16 Grab Flash Bank3 Sector 0
    Uint16 GRAB_B3_SECT1:2;             // 19:18 Grab Flash Bank3 Sector 1
    Uint16 GRAB_B3_SECT2:2;             // 21:20 Grab Flash Bank3 Sector 2
    Uint16 GRAB_B3_SECT3:2;             // 23:22 Grab Flash Bank3 Sector 3
    Uint16 GRAB_B3_SECT31_4:2;          // 25:24 Grab Flash Bank3 Sector 31-4
    Uint16 GRAB_B3_SECT63_32:2;         // 27:26 Grab Flash Bank3 Sector 63-32
    Uint16 GRAB_B3_SECT95_64:2;         // 29:28 Grab Flash Bank3 Sector 95-64
    Uint16 GRAB_B3_SECT127_96:2;        // 31:30 Grab Flash Bank3 Sector 127-96
};

union Z2_GRABSECT2R_REG {
    Uint32  all;
    struct  Z2_GRABSECT2R_BITS  bit;
};

struct Z2_GRABSECT3R_BITS {             // bits description
    Uint16 GRAB_B4_SECT0:2;             // 1:0 Grab Flash Bank4 Sector 0
    Uint16 GRAB_B4_SECT1:2;             // 3:2 Grab Flash Bank4 Sector 1
    Uint16 GRAB_B4_SECT2:2;             // 5:4 Grab Flash Bank4 Sector 2
    Uint16 GRAB_B4_SECT3:2;             // 7:6 Grab Flash Bank4 Sector 3
    Uint16 GRAB_B4_SECT31_4:2;          // 9:8 Grab Flash Bank4 Sector 31-4
    Uint16 GRAB_B4_SECT63_32:2;         // 11:10 Grab Flash Bank4 Sector 63-32
    Uint16 GRAB_B4_SECT95_64:2;         // 13:12 Grab Flash Bank4 Sector 95-64
    Uint16 GRAB_B4_SECT127_96:2;        // 15:14 Grab Flash Bank4 Sector 127-96
    Uint16 rsvd1:16;                    // 31:16 Reserved
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
    Uint16 GRAB_RAM8:2;                 // 17:16 Grab RAM CPU1.LS8
    Uint16 GRAB_RAM9:2;                 // 19:18 Grab RAM CPU1.LS9
    Uint16 GRAB_RAM10:2;                // 21:20 Grab RAM D0
    Uint16 GRAB_RAM11:2;                // 23:22 Grab RAM D1
    Uint16 GRAB_RAM12:2;                // 25:24 Grab RAM D2
    Uint16 GRAB_RAM13:2;                // 27:26 Grab RAM D3
    Uint16 GRAB_RAM14:2;                // 29:28 Grab RAM D4
    Uint16 GRAB_RAM15:2;                // 31:30 Grab RAM D5
};

union Z2_GRABRAM1R_REG {
    Uint32  all;
    struct  Z2_GRABRAM1R_BITS  bit;
};

struct Z2_GRABRAM2R_BITS {              // bits description
    Uint16 GRAB_RAM12:2;                // 1:0 Grab RAM CPU1TOCPU2 MSGRAM0_L
    Uint16 GRAB_RAM13:2;                // 3:2 Grab RAM CPU1TOCPU2 MSGRAM0_H
    Uint16 GRAB_RAM14:2;                // 5:4 Grab RAM CPU2TOCPU1 MSGRAM0_L
    Uint16 GRAB_RAM15:2;                // 7:6 Grab RAM CPU2TOCPU1 MSGRAM0_H
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union Z2_GRABRAM2R_REG {
    Uint32  all;
    struct  Z2_GRABRAM2R_BITS  bit;
};

struct Z2_EXEONLYSECT1R_BITS {          // bits description
    Uint16 EXEONLY_B0_SECT0:1;          // 0 Execute-Only Flash Bank0 Sector 0
    Uint16 EXEONLY_B0_SECT1:1;          // 1 Execute-Only Flash Bank0 Sector 1
    Uint16 EXEONLY_B0_SECT2:1;          // 2 Execute-Only Flash Bank0 Sector 2
    Uint16 EXEONLY_B0_SECT3:1;          // 3 Execute-Only Flash Bank0 Sector 3
    Uint16 EXEONLY_B0_SECT31_4:1;       // 4 Execute-Only Flash Bank0 Sector 31-4
    Uint16 EXEONLY_B0_SECT63_32:1;      // 5 Execute-Only Flash Bank0 Sector 63-32
    Uint16 EXEONLY_B0_SECT95_64:1;      // 6 Execute-Only Flash Bank0 Sector 95-64
    Uint16 EXEONLY_B0_SECT127_96:1;     // 7 Execute-Only Flash Bank0 Sector 127-96
    Uint16 EXEONLY_B1_SECT0:1;          // 8 Execute-Only Flash Bank1 Sector 0
    Uint16 EXEONLY_B1_SECT1:1;          // 9 Execute-Only Flash Bank1 Sector 1
    Uint16 EXEONLY_B1_SECT2:1;          // 10 Execute-Only Flash Bank1 Sector 2
    Uint16 EXEONLY_B1_SECT3:1;          // 11 Execute-Only Flash Bank1 Sector 3
    Uint16 EXEONLY_B1_SECT31_4:1;       // 12 Execute-Only Flash Bank1 Sector 31-4
    Uint16 EXEONLY_B1_SECT63_32:1;      // 13 Execute-Only Flash Bank1 Sector 63-32
    Uint16 EXEONLY_B1_SECT95_64:1;      // 14 Execute-Only Flash Bank1 Sector 95-64
    Uint16 EXEONLY_B1_SECT127_96:1;     // 15 Execute-Only Flash Bank1 Sector 127-96
    Uint16 EXEONLY_B2_SECT0:1;          // 16 Execute-Only Flash Bank2 Sector 0
    Uint16 EXEONLY_B2_SECT1:1;          // 17 Execute-Only Flash Bank2 Sector 1
    Uint16 EXEONLY_B2_SECT2:1;          // 18 Execute-Only Flash Bank2 Sector 2
    Uint16 EXEONLY_B2_SECT3:1;          // 19 Execute-Only Flash Bank2 Sector 3
    Uint16 EXEONLY_B2_SECT31_4:1;       // 20 Execute-Only Flash Bank2 Sector 31-4
    Uint16 EXEONLY_B2_SECT63_32:1;      // 21 Execute-Only Flash Bank2 Sector 63-32
    Uint16 EXEONLY_B2_SECT95_64:1;      // 22 Execute-Only Flash Bank2 Sector 95-64
    Uint16 EXEONLY_B2_SECT127_96:1;     // 23 Execute-Only Flash Bank2 Sector 127-96
    Uint16 EXEONLY_B3_SECT0:1;          // 24 Execute-Only Flash Bank3 Sector 0
    Uint16 EXEONLY_B3_SECT1:1;          // 25 Execute-Only Flash Bank3 Sector 1
    Uint16 EXEONLY_B3_SECT2:1;          // 26 Execute-Only Flash Bank3 Sector 2
    Uint16 EXEONLY_B3_SECT3:1;          // 27 Execute-Only Flash Bank3 Sector 3
    Uint16 EXEONLY_B3_SECT31_4:1;       // 28 Execute-Only Flash Bank3 Sector 31-4
    Uint16 EXEONLY_B3_SECT63_32:1;      // 29 Execute-Only Flash Bank3 Sector 63-32
    Uint16 EXEONLY_B3_SECT95_64:1;      // 30 Execute-Only Flash Bank3 Sector 95-64
    Uint16 EXEONLY_B3_SECT127_96:1;     // 31 Execute-Only Flash Bank3 Sector 127-96
};

union Z2_EXEONLYSECT1R_REG {
    Uint32  all;
    struct  Z2_EXEONLYSECT1R_BITS  bit;
};

struct Z2_EXEONLYSECT2R_BITS {          // bits description
    Uint16 EXEONLY_B4_SECT0:1;          // 0 Execute-Only Flash Bank4 Sector 0
    Uint16 EXEONLY_B4_SECT1:1;          // 1 Execute-Only Flash Bank4 Sector 1
    Uint16 EXEONLY_B4_SECT2:1;          // 2 Execute-Only Flash Bank4 Sector 2
    Uint16 EXEONLY_B4_SECT3:1;          // 3 Execute-Only Flash Bank4 Sector 3
    Uint16 EXEONLY_B4_SECT31_4:1;       // 4 Execute-Only Flash Bank4 Sector 31-4
    Uint16 EXEONLY_B4_SECT63_32:1;      // 5 Execute-Only Flash Bank4 Sector 63-32
    Uint16 EXEONLY_B4_SECT95_64:1;      // 6 Execute-Only Flash Bank4 Sector 95-64
    Uint16 EXEONLY_B4_SECT127_96:1;     // 7 Execute-Only Flash Bank4 Sector 127-96
    Uint16 rsvd1:8;                     // 15:8 Reserved
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
    Uint16 EXEONLY_RAM8:1;              // 8 Execute-Only RAM CPU1.LS8
    Uint16 EXEONLY_RAM9:1;              // 9 Execute-Only RAM CPU1.LS9
    Uint16 EXEONLY_RAM10:1;             // 10 Execute-Only RAM D0
    Uint16 EXEONLY_RAM11:1;             // 11 Execute-Only RAM D1
    Uint16 EXEONLY_RAM12:1;             // 12 Execute-Only RAM D2
    Uint16 EXEONLY_RAM13:1;             // 13 Execute-Only RAM D3
    Uint16 EXEONLY_RAM14:1;             // 14 Execute-Only RAM D4
    Uint16 EXEONLY_RAM15:1;             // 15 Execute-Only RAM D5
    Uint16 rsvd1:16;                    // 31:16 Reserved
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
    Uint16                                   rsvd2[2];                     // Reserved
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
    Uint16 STATUS_B0_SECT0:2;           // 1:0 Zone Status Flash Bank0 Sector 0
    Uint16 STATUS_B0_SECT1:2;           // 3:2 Zone Status Flash Bank0 Sector 1
    Uint16 STATUS_B0_SECT2:2;           // 5:4 Zone Status Flash Bank0 Sector 2
    Uint16 STATUS_B0_SECT3:2;           // 7:6 Zone Status Flash Bank0 Sector 3
    Uint16 STATUS_B0_SECT31_4:2;        // 9:8 Zone Status Flash Bank0 Sector 31-4
    Uint16 STATUS_B0_SECT63_32:2;       // 11:10 Zone Status Flash Bank0 Sector 63-32
    Uint16 STATUS_B0_SECT95_64:2;       // 13:12 Zone Status Flash Bank0 Sector 95-64
    Uint16 STATUS_B0_SECT127_96:2;      // 15:14 Zone Status Flash Bank0 Sector 127-96
    Uint16 STATUS_B1_SECT0:2;           // 17:16 Zone Status Flash Bank1 Sector 0
    Uint16 STATUS_B1_SECT1:2;           // 19:18 Zone Status Flash Bank1 Sector 1
    Uint16 STATUS_B1_SECT2:2;           // 21:20 Zone Status Flash Bank1 Sector 2
    Uint16 STATUS_B1_SECT3:2;           // 23:22 Zone Status Flash Bank1 Sector 3
    Uint16 STATUS_B1_SECT31_4:2;        // 25:24 Zone Status Flash Bank1 Sector 31-4
    Uint16 STATUS_B1_SECT63_32:2;       // 27:26 Zone Status Flash Bank1 Sector 63-32
    Uint16 STATUS_B1_SECT95_64:2;       // 29:28 Zone Status Flash Bank1 Sector 95-64
    Uint16 STATUS_B1_SECT127_96:2;      // 31:30 Zone Status Flash Bank1 Sector 127-96
};

union SECTSTAT1_REG {
    Uint32  all;
    struct  SECTSTAT1_BITS  bit;
};

struct SECTSTAT2_BITS {                 // bits description
    Uint16 STATUS_B2_SECT0:2;           // 1:0 Zone Status Flash Bank2 Sector 0
    Uint16 STATUS_B2_SECT1:2;           // 3:2 Zone Status Flash Bank2 Sector 1
    Uint16 STATUS_B2_SECT2:2;           // 5:4 Zone Status Flash Bank2 Sector 2
    Uint16 STATUS_B2_SECT3:2;           // 7:6 Zone Status Flash Bank2 Sector 3
    Uint16 STATUS_B2_SECT31_4:2;        // 9:8 Zone Status Flash Bank2 Sector 31-4
    Uint16 STATUS_B2_SECT63_32:2;       // 11:10 Zone Status Flash Bank2 Sector 63-32
    Uint16 STATUS_B2_SECT95_64:2;       // 13:12 Zone Status Flash Bank2 Sector 95-64
    Uint16 STATUS_B2_SECT127_96:2;      // 15:14 Zone Status Flash Bank2 Sector 127-96
    Uint16 STATUS_B3_SECT0:2;           // 17:16 Zone Status Flash Bank3 Sector 0
    Uint16 STATUS_B3_SECT1:2;           // 19:18 Zone Status Flash Bank3 Sector 1
    Uint16 STATUS_B3_SECT2:2;           // 21:20 Zone Status Flash Bank3 Sector 2
    Uint16 STATUS_B3_SECT3:2;           // 23:22 Zone Status Flash Bank3 Sector 3
    Uint16 STATUS_B3_SECT31_4:2;        // 25:24 Zone Status Flash Bank3 Sector 31-4
    Uint16 STATUS_B3_SECT63_32:2;       // 27:26 Zone Status Flash Bank3 Sector 63-32
    Uint16 STATUS_B3_SECT95_64:2;       // 29:28 Zone Status Flash Bank3 Sector 95-64
    Uint16 STATUS_B3_SECT127_96:2;      // 31:30 Zone Status Flash Bank3 Sector 127-96
};

union SECTSTAT2_REG {
    Uint32  all;
    struct  SECTSTAT2_BITS  bit;
};

struct SECTSTAT3_BITS {                 // bits description
    Uint16 STATUS_B4_SECT0:2;           // 1:0 Zone Status Flash Bank4 Sector 0
    Uint16 STATUS_B4_SECT1:2;           // 3:2 Zone Status Flash Bank4 Sector 1
    Uint16 STATUS_B4_SECT2:2;           // 5:4 Zone Status Flash Bank4 Sector 2
    Uint16 STATUS_B4_SECT3:2;           // 7:6 Zone Status Flash Bank4 Sector 3
    Uint16 STATUS_B4_SECT31_4:2;        // 9:8 Zone Status Flash Bank4 Sector 31-4
    Uint16 STATUS_B4_SECT63_32:2;       // 11:10 Zone Status Flash Bank4 Sector 63-32
    Uint16 STATUS_B4_SECT95_64:2;       // 13:12 Zone Status Flash Bank4 Sector 95-64
    Uint16 STATUS_B4_SECT127_96:2;      // 15:14 Zone Status Flash Bank4 Sector 127-96
    Uint16 rsvd1:16;                    // 31:16 Reserved
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
    Uint16 STATUS_RAM8:2;               // 17:16 Zone Status RAM CPU1.LS8
    Uint16 STATUS_RAM9:2;               // 19:18 Zone Status RAM CPU1.LS9
    Uint16 STATUS_RAM10:2;              // 21:20 Zone Status RAM D0
    Uint16 STATUS_RAM11:2;              // 23:22 Zone Status RAM D1
    Uint16 STATUS_RAM12:2;              // 25:24 Zone Status RAM D2
    Uint16 STATUS_RAM13:2;              // 27:26 Zone Status RAM D3
    Uint16 STATUS_RAM14:2;              // 29:28 Zone Status RAM D4
    Uint16 STATUS_RAM15:2;              // 31:30 Zone Status RAM D5
};

union RAMSTAT1_REG {
    Uint32  all;
    struct  RAMSTAT1_BITS  bit;
};

struct RAMSTAT2_BITS {                  // bits description
    Uint16 STATUS_RAM12:2;              // 1:0 Zone Status RAM CPU1TOCPU2 MSGRAM0_L
    Uint16 STATUS_RAM13:2;              // 3:2 Zone Status RAM CPU1TOCPU2 MSGRAM0_H
    Uint16 STATUS_RAM14:2;              // 5:4 Zone Status RAM CPU2TOCPU1 MSGRAM0_L
    Uint16 STATUS_RAM15:2;              // 7:6 Zone Status RAM CPU2TOCPU1 MSGRAM0_H
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union RAMSTAT2_REG {
    Uint32  all;
    struct  RAMSTAT2_BITS  bit;
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

struct PERSEM1_BITS {                   // bits description
    Uint16 GRABWD:2;                    // 1:0 Grab Watchdog module
    Uint16 GRABNMIWD:2;                 // 3:2 GRAB NMIWD module
    Uint16 GRABTIMER1:2;                // 5:4 Grab TIMER1 module
    Uint16 GRABCLKCTL:2;                // 7:6 Grab Clock Configuration
    Uint16 GRABRSTCTL:2;                // 9:8 Grab Reset Configuration
    Uint16 rsvd1:6;                     // 15:10 Reserved
    Uint16 rsvd2:8;                     // 23:16 Reserved
    Uint16 KEY:8;                       // 31:24 Semaphore Key
};

union PERSEM1_REG {
    Uint32  all;
    struct  PERSEM1_BITS  bit;
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
    Uint16                                   rsvd3[4];                     // Reserved
    union   SECERRSTAT_REG                   SECERRSTAT;                   // Security Error Status Register
    union   SECERRCLR_REG                    SECERRCLR;                    // Security Error Clear Register
    union   SECERRFRC_REG                    SECERRFRC;                    // Security Error Force Register
    union   DENYCODE_REG                     DENYCODE;                     // Flash Authorization Denial Code
    Uint16                                   rsvd4[8];                     // Reserved
    Uint32                                   UID_UNIQUE_31_0;              // Unique Identification Number
    Uint32                                   UID_UNIQUE_63_32;             // Part Identification High Register
    Uint32                                   PARTIDH;                      // Part Identification High Register
    union   PERSEM1_REG                      PERSEM1;                      // Peripheral Semaphore Register
};

//---------------------------------------------------------------------------
// DCSM External References & Function Declarations:
//
#ifdef CPU1
extern volatile struct DCSM_Z1_REGS DcsmZ1Regs;
extern volatile struct DCSM_Z2_REGS DcsmZ2Regs;
extern volatile struct DCSM_COMMON_REGS DcsmCommonRegs;
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
