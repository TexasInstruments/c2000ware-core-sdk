//###########################################################################
//
// FILE:    f28e12x_dcsm.h
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

#ifndef F28E12X_DCSM_H
#define F28E12X_DCSM_H

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
    Uint16 GRAB_B0_SECT0:2;             // 1:0 Grab Flash Bank0 Sector 0
    Uint16 GRAB_B0_SECT1:2;             // 3:2 Grab Flash Bank0 Sector 1
    Uint16 GRAB_B0_SECT2:2;             // 5:4 Grab Flash Bank0 Sector 2
    Uint16 GRAB_B0_SECT3:2;             // 7:6 Grab Flash Bank0 Sector 3
    Uint16 GRAB_B0_SECT31_4:2;          // 9:8 Grab Flash Bank0 Sector 31-4
    Uint16 GRAB_B0_SECT63_32:2;         // 11:10 Grab Flash Bank0 Sector 63-32
    Uint16 rsvd1:4;                     // 15:12 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union Z1_GRABSECT1R_REG {
    Uint32  all;
    struct  Z1_GRABSECT1R_BITS  bit;
};

struct Z1_EXEONLYSECT1R_BITS {          // bits description
    Uint16 EXEONLY_B0_SECT0:1;          // 0 Execute-Only Flash Bank0 Sector 0
    Uint16 EXEONLY_B0_SECT1:1;          // 1 Execute-Only Flash Bank0 Sector 1
    Uint16 EXEONLY_B0_SECT2:1;          // 2 Execute-Only Flash Bank0 Sector 2
    Uint16 EXEONLY_B0_SECT3:1;          // 3 Execute-Only Flash Bank0 Sector 3
    Uint16 EXEONLY_B0_SECT31_4:1;       // 4 Execute-Only Flash Bank0 Sector 31-4
    Uint16 EXEONLY_B0_SECT63_32:1;      // 5 Execute-Only Flash Bank0 Sector 63-32
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union Z1_EXEONLYSECT1R_REG {
    Uint32  all;
    struct  Z1_EXEONLYSECT1R_BITS  bit;
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
    Uint16                                   rsvd1[10];                    // Reserved
    union   Z1_EXEONLYSECT1R_REG             Z1_EXEONLYSECT1R;             // Zone 1 Execute Only Flash Status Register 1
    Uint16                                   rsvd2[6];                     // Reserved
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
    Uint16 GRAB_B0_SECT0:2;             // 1:0 Grab Flash Bank0 Sector 0
    Uint16 GRAB_B0_SECT1:2;             // 3:2 Grab Flash Bank0 Sector 1
    Uint16 GRAB_B0_SECT2:2;             // 5:4 Grab Flash Bank0 Sector 2
    Uint16 GRAB_B0_SECT3:2;             // 7:6 Grab Flash Bank0 Sector 3
    Uint16 GRAB_B0_SECT31_4:2;          // 9:8 Grab Flash Bank0 Sector 31-4
    Uint16 GRAB_B0_SECT63_32:2;         // 11:10 Grab Flash Bank0 Sector 63-32
    Uint16 rsvd1:4;                     // 15:12 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union Z2_GRABSECT1R_REG {
    Uint32  all;
    struct  Z2_GRABSECT1R_BITS  bit;
};

struct Z2_EXEONLYSECT1R_BITS {          // bits description
    Uint16 EXEONLY_B0_SECT0:1;          // 0 Execute-Only Flash Bank0 Sector 0
    Uint16 EXEONLY_B0_SECT1:1;          // 1 Execute-Only Flash Bank0 Sector 1
    Uint16 EXEONLY_B0_SECT2:1;          // 2 Execute-Only Flash Bank0 Sector 2
    Uint16 EXEONLY_B0_SECT3:1;          // 3 Execute-Only Flash Bank0 Sector 3
    Uint16 EXEONLY_B0_SECT31_4:1;       // 4 Execute-Only Flash Bank0 Sector 31-4
    Uint16 EXEONLY_B0_SECT63_32:1;      // 5 Execute-Only Flash Bank0 Sector 63-32
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union Z2_EXEONLYSECT1R_REG {
    Uint32  all;
    struct  Z2_EXEONLYSECT1R_BITS  bit;
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
    Uint16                                   rsvd2[10];                    // Reserved
    union   Z2_EXEONLYSECT1R_REG             Z2_EXEONLYSECT1R;             // Zone 2 Execute Only Flash Status Register 1
};

struct SECTSTAT1_BITS {                 // bits description
    Uint16 STATUS_B0_SECT0:2;           // 1:0 Zone Status Flash Bank0 Sector 0
    Uint16 STATUS_B0_SECT1:2;           // 3:2 Zone Status Flash Bank0 Sector 1
    Uint16 STATUS_B0_SECT2:2;           // 5:4 Zone Status Flash Bank0 Sector 2
    Uint16 STATUS_B0_SECT3:2;           // 7:6 Zone Status Flash Bank0 Sector 3
    Uint16 STATUS_B0_SECT31_4:2;        // 9:8 Zone Status Flash Bank0 Sector 31-4
    Uint16 STATUS_B0_SECT63_32:2;       // 11:10 Zone Status Flash Bank0 Sector 63-32
    Uint16 rsvd1:4;                     // 15:12 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union SECTSTAT1_REG {
    Uint32  all;
    struct  SECTSTAT1_BITS  bit;
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
    Uint16                                   rsvd1[8];                     // Reserved
    union   SECTSTAT1_REG                    SECTSTAT1;                    // Flash Sectors Status Register 1
    Uint16                                   rsvd2[14];                    // Reserved
    union   SECERRSTAT_REG                   SECERRSTAT;                   // Security Error Status Register
    union   SECERRCLR_REG                    SECERRCLR;                    // Security Error Clear Register
    union   SECERRFRC_REG                    SECERRFRC;                    // Security Error Force Register
    union   DENYCODE_REG                     DENYCODE;                     // Flash Authorization Denial Code
    Uint16                                   rsvd3[8];                     // Reserved
    Uint32                                   UID_UNIQUE_31_0;              // Unique Identification Number Low
    Uint32                                   UID_UNIQUE_63_32;             // Unique Identification Number High
    Uint32                                   PARTIDH;                      // Part Identification High Register
    union   PERSEM1_REG                      PERSEM1;                      // Peripheral Semaphore Register
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
