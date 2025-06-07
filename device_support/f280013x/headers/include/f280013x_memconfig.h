//###########################################################################
//
// FILE:    f280013x_memconfig.h
//
// TITLE:   Definitions for the MEMCONFIG registers.
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

#ifndef F280013X_MEMCONFIG_H
#define F280013X_MEMCONFIG_H

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// MEMCONFIG Individual Register Bit Definitions:

struct DxLOCK_BITS {                    // bits description
    Uint16 LOCK_M0:1;                   // 0 M0 RAM Lock bits
    Uint16 LOCK_M1:1;                   // 1 M1 RAM Lock bits
    Uint16 rsvd1:1;                     // 2 Reserved
    Uint16 rsvd2:1;                     // 3 Reserved
    Uint16 LOCK_PIEVECT:1;              // 4 PIEVECT RAM Lock bits
    Uint16 rsvd3:11;                    // 15:5 Reserved
    Uint16 rsvd4:16;                    // 31:16 Reserved
};

union DxLOCK_REG {
    Uint32  all;
    struct  DxLOCK_BITS  bit;
};

struct DxCOMMIT_BITS {                  // bits description
    Uint16 COMMIT_M0:1;                 // 0 M0 RAM Permanent Lock bits
    Uint16 COMMIT_M1:1;                 // 1 M1 RAM Permanent Lock bits
    Uint16 rsvd1:1;                     // 2 Reserved
    Uint16 rsvd2:1;                     // 3 Reserved
    Uint16 COMMIT_PIEVECT:1;            // 4 PIEVECT RAM Permanent Lock bits
    Uint16 rsvd3:11;                    // 15:5 Reserved
    Uint16 rsvd4:16;                    // 31:16 Reserved
};

union DxCOMMIT_REG {
    Uint32  all;
    struct  DxCOMMIT_BITS  bit;
};

struct DxACCPROT0_BITS {                // bits description
    Uint16 FETCHPROT_M0:1;              // 0 Fetch Protection For M0 RAM
    Uint16 CPUWRPROT_M0:1;              // 1 CPU WR Protection For M0 RAM
    Uint16 rsvd1:6;                     // 7:2 Reserved
    Uint16 FETCHPROT_M1:1;              // 8 Fetch Protection For M1 RAM
    Uint16 CPUWRPROT_M1:1;              // 9 CPU WR Protection For M1 RAM
    Uint16 rsvd2:6;                     // 15:10 Reserved
    Uint16 rsvd3:1;                     // 16 Reserved
    Uint16 rsvd4:1;                     // 17 Reserved
    Uint16 rsvd5:6;                     // 23:18 Reserved
    Uint16 rsvd6:1;                     // 24 Reserved
    Uint16 rsvd7:1;                     // 25 Reserved
    Uint16 rsvd8:6;                     // 31:26 Reserved
};

union DxACCPROT0_REG {
    Uint32  all;
    struct  DxACCPROT0_BITS  bit;
};

struct DxACCPROT1_BITS {                // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 CPUWRPROT_PIEVECT:1;         // 1 CPU WR Protection For PIEVECT RAM
    Uint16 rsvd2:14;                    // 15:2 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union DxACCPROT1_REG {
    Uint32  all;
    struct  DxACCPROT1_BITS  bit;
};

struct DxTEST_BITS {                    // bits description
    Uint16 TEST_M0:2;                   // 1:0 Selects the different modes for M0 RAM
    Uint16 TEST_M1:2;                   // 3:2 Selects the different modes for M1 RAM
    Uint16 rsvd1:2;                     // 5:4 Reserved
    Uint16 rsvd2:2;                     // 7:6 Reserved
    Uint16 TEST_PIEVECT:2;              // 9:8 Selects the different modes for PIEVECT RAM
    Uint16 rsvd3:6;                     // 15:10 Reserved
    Uint16 rsvd4:16;                    // 31:16 Reserved
};

union DxTEST_REG {
    Uint32  all;
    struct  DxTEST_BITS  bit;
};

struct DxINIT_BITS {                    // bits description
    Uint16 INIT_M0:1;                   // 0 RAM Initialization control for M0 RAM.
    Uint16 INIT_M1:1;                   // 1 RAM Initialization control for M1 RAM.
    Uint16 rsvd1:1;                     // 2 Reserved
    Uint16 rsvd2:1;                     // 3 Reserved
    Uint16 INIT_PIEVECT:1;              // 4 RAM Initialization control for PIEVECT RAM.
    Uint16 rsvd3:11;                    // 15:5 Reserved
    Uint16 rsvd4:16;                    // 31:16 Reserved
};

union DxINIT_REG {
    Uint32  all;
    struct  DxINIT_BITS  bit;
};

struct DxINITDONE_BITS {                // bits description
    Uint16 INITDONE_M0:1;               // 0 RAM Initialization status for M0 RAM.
    Uint16 INITDONE_M1:1;               // 1 RAM Initialization status for M1 RAM.
    Uint16 rsvd1:1;                     // 2 Reserved
    Uint16 rsvd2:1;                     // 3 Reserved
    Uint16 INITDONE_PIEVECT:1;          // 4 RAM Initialization status for PIEVECT RAM.
    Uint16 rsvd3:11;                    // 15:5 Reserved
    Uint16 rsvd4:16;                    // 31:16 Reserved
};

union DxINITDONE_REG {
    Uint32  all;
    struct  DxINITDONE_BITS  bit;
};

struct DxRAMTEST_LOCK_BITS {            // bits description
    Uint16 M0:1;                        // 0 DxTEST.TEST_M0 LOCK
    Uint16 M1:1;                        // 1 DxTEST.TEST_M1 LOCK
    Uint16 rsvd1:1;                     // 2 Reserved
    Uint16 rsvd2:1;                     // 3 Reserved
    Uint16 PIEVECT:1;                   // 4 DxTEST.TEST_PIEVECT LOCK
    Uint16 rsvd3:11;                    // 15:5 Reserved
    Uint16 KEY:16;                      // 31:16 Key for writing DxRAMTEST_LOCK
};

union DxRAMTEST_LOCK_REG {
    Uint32  all;
    struct  DxRAMTEST_LOCK_BITS  bit;
};

struct LSxLOCK_BITS {                   // bits description
    Uint16 LOCK_LS0:1;                  // 0 LS0 RAM Lock bits
    Uint16 LOCK_LS1:1;                  // 1 LS1 RAM Lock bits
    Uint16 rsvd1:1;                     // 2 Reserved
    Uint16 rsvd2:1;                     // 3 Reserved
    Uint16 rsvd3:1;                     // 4 Reserved
    Uint16 rsvd4:1;                     // 5 Reserved
    Uint16 rsvd5:1;                     // 6 Reserved
    Uint16 rsvd6:1;                     // 7 Reserved
    Uint16 rsvd7:8;                     // 15:8 Reserved
    Uint16 rsvd8:16;                    // 31:16 Reserved
};

union LSxLOCK_REG {
    Uint32  all;
    struct  LSxLOCK_BITS  bit;
};

struct LSxCOMMIT_BITS {                 // bits description
    Uint16 COMMIT_LS0:1;                // 0 LS0 RAM Permanent Lock bits
    Uint16 COMMIT_LS1:1;                // 1 LS1 RAM Permanent Lock bits
    Uint16 rsvd1:1;                     // 2 Reserved
    Uint16 rsvd2:1;                     // 3 Reserved
    Uint16 rsvd3:1;                     // 4 Reserved
    Uint16 rsvd4:1;                     // 5 Reserved
    Uint16 rsvd5:1;                     // 6 Reserved
    Uint16 rsvd6:1;                     // 7 Reserved
    Uint16 rsvd7:8;                     // 15:8 Reserved
    Uint16 rsvd8:16;                    // 31:16 Reserved
};

union LSxCOMMIT_REG {
    Uint32  all;
    struct  LSxCOMMIT_BITS  bit;
};

struct LSxACCPROT0_BITS {               // bits description
    Uint16 FETCHPROT_LS0:1;             // 0 Fetch Protection For LS0 RAM
    Uint16 CPUWRPROT_LS0:1;             // 1 CPU WR Protection For LS0 RAM
    Uint16 rsvd1:6;                     // 7:2 Reserved
    Uint16 FETCHPROT_LS1:1;             // 8 Fetch Protection For LS1 RAM
    Uint16 CPUWRPROT_LS1:1;             // 9 CPU WR Protection For LS1 RAM
    Uint16 rsvd2:6;                     // 15:10 Reserved
    Uint16 rsvd3:1;                     // 16 Reserved
    Uint16 rsvd4:1;                     // 17 Reserved
    Uint16 rsvd5:6;                     // 23:18 Reserved
    Uint16 rsvd6:1;                     // 24 Reserved
    Uint16 rsvd7:1;                     // 25 Reserved
    Uint16 rsvd8:6;                     // 31:26 Reserved
};

union LSxACCPROT0_REG {
    Uint32  all;
    struct  LSxACCPROT0_BITS  bit;
};

struct LSxTEST_BITS {                   // bits description
    Uint16 TEST_LS0:2;                  // 1:0 Selects the different modes for LS0 RAM
    Uint16 TEST_LS1:2;                  // 3:2 Selects the different modes for LS1 RAM
    Uint16 rsvd1:2;                     // 5:4 Reserved
    Uint16 rsvd2:2;                     // 7:6 Reserved
    Uint16 rsvd3:2;                     // 9:8 Reserved
    Uint16 rsvd4:2;                     // 11:10 Reserved
    Uint16 rsvd5:2;                     // 13:12 Reserved
    Uint16 rsvd6:2;                     // 15:14 Reserved
    Uint16 rsvd7:16;                    // 31:16 Reserved
};

union LSxTEST_REG {
    Uint32  all;
    struct  LSxTEST_BITS  bit;
};

struct LSxINIT_BITS {                   // bits description
    Uint16 INIT_LS0:1;                  // 0 RAM Initialization control for LS0 RAM.
    Uint16 INIT_LS1:1;                  // 1 RAM Initialization control for LS1 RAM.
    Uint16 rsvd1:1;                     // 2 Reserved
    Uint16 rsvd2:1;                     // 3 Reserved
    Uint16 rsvd3:1;                     // 4 Reserved
    Uint16 rsvd4:1;                     // 5 Reserved
    Uint16 rsvd5:1;                     // 6 Reserved
    Uint16 rsvd6:1;                     // 7 Reserved
    Uint16 rsvd7:8;                     // 15:8 Reserved
    Uint16 rsvd8:16;                    // 31:16 Reserved
};

union LSxINIT_REG {
    Uint32  all;
    struct  LSxINIT_BITS  bit;
};

struct LSxINITDONE_BITS {               // bits description
    Uint16 INITDONE_LS0:1;              // 0 RAM Initialization status for LS0 RAM.
    Uint16 INITDONE_LS1:1;              // 1 RAM Initialization status for LS1 RAM.
    Uint16 rsvd1:1;                     // 2 Reserved
    Uint16 rsvd2:1;                     // 3 Reserved
    Uint16 rsvd3:1;                     // 4 Reserved
    Uint16 rsvd4:1;                     // 5 Reserved
    Uint16 rsvd5:1;                     // 6 Reserved
    Uint16 rsvd6:1;                     // 7 Reserved
    Uint16 rsvd7:8;                     // 15:8 Reserved
    Uint16 rsvd8:16;                    // 31:16 Reserved
};

union LSxINITDONE_REG {
    Uint32  all;
    struct  LSxINITDONE_BITS  bit;
};

struct LSxRAMTEST_LOCK_BITS {           // bits description
    Uint16 LS0:1;                       // 0 LSxTEST.TEST_LS0 LOCK
    Uint16 LS1:1;                       // 1 LSxTEST.TEST_LS1 LOCK
    Uint16 rsvd1:1;                     // 2 Reserved
    Uint16 rsvd2:1;                     // 3 Reserved
    Uint16 rsvd3:1;                     // 4 Reserved
    Uint16 rsvd4:1;                     // 5 Reserved
    Uint16 rsvd5:1;                     // 6 Reserved
    Uint16 rsvd6:1;                     // 7 Reserved
    Uint16 rsvd7:8;                     // 15:8 Reserved
    Uint16 KEY:16;                      // 31:16 KEY to enable write to lock
};

union LSxRAMTEST_LOCK_REG {
    Uint32  all;
    struct  LSxRAMTEST_LOCK_BITS  bit;
};

struct ROM_LOCK_BITS {                  // bits description
    Uint16 LOCK_BOOTROM:1;              // 0 BOOTROM Lock bits
    Uint16 rsvd1:1;                     // 1 Reserved
    Uint16 rsvd2:1;                     // 2 Reserved
    Uint16 rsvd3:1;                     // 3 Reserved
    Uint16 rsvd4:12;                    // 15:4 Reserved
    Uint16 KEY:16;                      // 31:16 Key for writing ROM LOCK
};

union ROM_LOCK_REG {
    Uint32  all;
    struct  ROM_LOCK_BITS  bit;
};

struct ROM_TEST_BITS {                  // bits description
    Uint16 TEST_BOOTROM:2;              // 1:0 Selects the different modes for BOOTROM
    Uint16 rsvd1:2;                     // 3:2 Reserved
    Uint16 rsvd2:2;                     // 5:4 Reserved
    Uint16 rsvd3:2;                     // 7:6 Reserved
    Uint16 rsvd4:8;                     // 15:8 Reserved
    Uint16 rsvd5:16;                    // 31:16 Reserved
};

union ROM_TEST_REG {
    Uint32  all;
    struct  ROM_TEST_BITS  bit;
};

struct ROM_FORCE_ERROR_BITS {           // bits description
    Uint16 FORCE_BOOTROM_ERROR:1;       // 0 Force Bootrom Parity Error
    Uint16 rsvd1:1;                     // 1 Reserved
    Uint16 rsvd2:1;                     // 2 Reserved
    Uint16 rsvd3:1;                     // 3 Reserved
    Uint16 rsvd4:12;                    // 15:4 Reserved
    Uint16 rsvd5:16;                    // 31:16 Reserved
};

union ROM_FORCE_ERROR_REG {
    Uint32  all;
    struct  ROM_FORCE_ERROR_BITS  bit;
};

struct MEM_CFG_REGS {
    union   DxLOCK_REG                       DxLOCK;                       // Dedicated RAM Config Lock Register
    union   DxCOMMIT_REG                     DxCOMMIT;                     // Dedicated RAM Config Lock Commit Register
    Uint16                                   rsvd1[4];                     // Reserved
    union   DxACCPROT0_REG                   DxACCPROT0;                   // Dedicated RAM Config Register
    union   DxACCPROT1_REG                   DxACCPROT1;                   // Dedicated RAM Config Register
    Uint16                                   rsvd2[4];                     // Reserved
    union   DxTEST_REG                       DxTEST;                       // Dedicated RAM TEST Register
    union   DxINIT_REG                       DxINIT;                       // Dedicated RAM Init Register
    union   DxINITDONE_REG                   DxINITDONE;                   // Dedicated RAM InitDone Status Register
    union   DxRAMTEST_LOCK_REG               DxRAMTEST_LOCK;               // Lock register to Dx RAM TEST registers
    Uint16                                   rsvd3[8];                     // Reserved
    union   LSxLOCK_REG                      LSxLOCK;                      // Local Shared RAM Config Lock Register
    union   LSxCOMMIT_REG                    LSxCOMMIT;                    // Local Shared RAM Config Lock Commit Register
    Uint16                                   rsvd4[4];                     // Reserved
    union   LSxACCPROT0_REG                  LSxACCPROT0;                  // Local Shared RAM Config Register 0
    Uint16                                   rsvd5[6];                     // Reserved
    union   LSxTEST_REG                      LSxTEST;                      // Local Shared RAM TEST Register
    union   LSxINIT_REG                      LSxINIT;                      // Local Shared RAM Init Register
    union   LSxINITDONE_REG                  LSxINITDONE;                  // Local Shared RAM InitDone Status Register
    union   LSxRAMTEST_LOCK_REG              LSxRAMTEST_LOCK;              // Lock register to LSx RAM TEST registers
    Uint16                                   rsvd6[104];                   // Reserved
    union   ROM_LOCK_REG                     ROM_LOCK;                     // ROM Config Lock Register
    union   ROM_TEST_REG                     ROM_TEST;                     // ROM  TEST Register
    union   ROM_FORCE_ERROR_REG              ROM_FORCE_ERROR;              // ROM Force Error register
};

struct MAVFLG_BITS {                    // bits description
    Uint16 CPUFETCH:1;                  // 0 Master CPU Fetch Access Violation Flag
    Uint16 CPUWRITE:1;                  // 1 Master CPU Write Access Violation Flag
    Uint16 rsvd1:1;                     // 2 Reserved
    Uint16 rsvd2:1;                     // 3 Reserved
    Uint16 rsvd3:12;                    // 15:4 Reserved
    Uint16 rsvd4:16;                    // 31:16 Reserved
};

union MAVFLG_REG {
    Uint32  all;
    struct  MAVFLG_BITS  bit;
};

struct MAVSET_BITS {                    // bits description
    Uint16 CPUFETCH:1;                  // 0 Master CPU Fetch Access Violation Flag Set
    Uint16 CPUWRITE:1;                  // 1 Master CPU Write Access Violation Flag Set
    Uint16 rsvd1:1;                     // 2 Reserved
    Uint16 rsvd2:1;                     // 3 Reserved
    Uint16 rsvd3:12;                    // 15:4 Reserved
    Uint16 rsvd4:16;                    // 31:16 Reserved
};

union MAVSET_REG {
    Uint32  all;
    struct  MAVSET_BITS  bit;
};

struct MAVCLR_BITS {                    // bits description
    Uint16 CPUFETCH:1;                  // 0 Master CPU Fetch Access Violation Flag Clear
    Uint16 CPUWRITE:1;                  // 1 Master CPU Write Access Violation Flag Clear
    Uint16 rsvd1:1;                     // 2 Reserved
    Uint16 rsvd2:1;                     // 3 Reserved
    Uint16 rsvd3:12;                    // 15:4 Reserved
    Uint16 rsvd4:16;                    // 31:16 Reserved
};

union MAVCLR_REG {
    Uint32  all;
    struct  MAVCLR_BITS  bit;
};

struct MAVINTEN_BITS {                  // bits description
    Uint16 CPUFETCH:1;                  // 0 Master CPU Fetch Access Violation Interrupt Enable
    Uint16 CPUWRITE:1;                  // 1 Master CPU Write Access Violation Interrupt Enable
    Uint16 rsvd1:1;                     // 2 Reserved
    Uint16 rsvd2:1;                     // 3 Reserved
    Uint16 rsvd3:12;                    // 15:4 Reserved
    Uint16 rsvd4:16;                    // 31:16 Reserved
};

union MAVINTEN_REG {
    Uint32  all;
    struct  MAVINTEN_BITS  bit;
};

struct ACCESS_PROTECTION_REGS {
    Uint16                                   rsvd1[32];                    // Reserved
    union   MAVFLG_REG                       MAVFLG;                       // Master Access Violation Flag Register
    union   MAVSET_REG                       MAVSET;                       // Master Access Violation Flag Set Register
    union   MAVCLR_REG                       MAVCLR;                       // Master Access Violation Flag Clear Register
    union   MAVINTEN_REG                     MAVINTEN;                     // Master Access Violation Interrupt Enable Register
    Uint32                                   MCPUFAVADDR;                  // Master CPU Fetch Access Violation Address
    Uint32                                   MCPUWRAVADDR;                 // Master CPU Write Access Violation Address
};

struct UCERRFLG_BITS {                  // bits description
    Uint16 CPURDERR:1;                  // 0 CPU Uncorrectable Read Error Flag
    Uint16 rsvd1:1;                     // 1 Reserved
    Uint16 rsvd2:1;                     // 2 Reserved
    Uint16 rsvd3:1;                     // 3 Reserved
    Uint16 rsvd4:1;                     // 4 Reserved
    Uint16 rsvd5:1;                     // 5 Reserved
    Uint16 rsvd6:10;                    // 15:6 Reserved
    Uint16 rsvd7:16;                    // 31:16 Reserved
};

union UCERRFLG_REG {
    Uint32  all;
    struct  UCERRFLG_BITS  bit;
};

struct UCERRSET_BITS {                  // bits description
    Uint16 CPURDERR:1;                  // 0 CPU Uncorrectable Read Error Flag Set
    Uint16 rsvd1:1;                     // 1 Reserved
    Uint16 rsvd2:1;                     // 2 Reserved
    Uint16 rsvd3:1;                     // 3 Reserved
    Uint16 rsvd4:1;                     // 4 Reserved
    Uint16 rsvd5:1;                     // 5 Reserved
    Uint16 rsvd6:10;                    // 15:6 Reserved
    Uint16 rsvd7:16;                    // 31:16 Reserved
};

union UCERRSET_REG {
    Uint32  all;
    struct  UCERRSET_BITS  bit;
};

struct UCERRCLR_BITS {                  // bits description
    Uint16 CPURDERR:1;                  // 0 CPU Uncorrectable Read Error Flag Clear
    Uint16 rsvd1:1;                     // 1 Reserved
    Uint16 rsvd2:1;                     // 2 Reserved
    Uint16 rsvd3:1;                     // 3 Reserved
    Uint16 rsvd4:1;                     // 4 Reserved
    Uint16 rsvd5:1;                     // 5 Reserved
    Uint16 rsvd6:10;                    // 15:6 Reserved
    Uint16 rsvd7:16;                    // 31:16 Reserved
};

union UCERRCLR_REG {
    Uint32  all;
    struct  UCERRCLR_BITS  bit;
};

struct FLUCERRSTATUS_BITS {             // bits description
    Uint16 UNC_ERR_L:1;                 // 0 Lower 64 bits Uncorrectable error occurred
    Uint16 DIAG_L_FAIL:1;               // 1 Diagnostics of ECC on lower 64 bits.
    Uint16 rsvd1:6;                     // 7:2 Reserved
    Uint16 UNC_ERR_H:1;                 // 8 Upper 64 bits Uncorrectable error occurred
    Uint16 DIAG_H_FAIL:1;               // 9 Diagnostics of ECC on upper 64 bits.
    Uint16 rsvd2:6;                     // 15:10 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union FLUCERRSTATUS_REG {
    Uint32  all;
    struct  FLUCERRSTATUS_BITS  bit;
};

struct FLCERRSTATUS_BITS {              // bits description
    Uint16 FAIL_0_L:1;                  // 0 Lower 64bits Single Bit Error Corrected Value 0
    Uint16 FAIL_1_L:1;                  // 1 Lower 64bits Single Bit Error Corrected Value 1
    Uint16 rsvd1:1;                     // 2 Reserved
    Uint16 FAIL_0_H:1;                  // 3 Upper 64bits Single Bit Error Corrected Value 0
    Uint16 FAIL_1_H:1;                  // 4 Upper 64bits Single Bit Error Corrected Value 1
    Uint16 rsvd2:1;                     // 5 Reserved
    Uint16 rsvd3:10;                    // 15:6 Reserved
    Uint16 ERR_POS_L:6;                 // 21:16 Bit Position of Single bit Error in lower 64 bits
    Uint16 ERR_TYPE_L:1;                // 22 Error Type in lower 64 bits
    Uint16 ERR_POS_H:6;                 // 28:23 Bit Position of Single bit Error in upper 64 bits
    Uint16 ERR_TYPE_H:1;                // 29 Error Type in upper 64 bits
    Uint16 rsvd4:2;                     // 31:30 Reserved
};

union FLCERRSTATUS_REG {
    Uint32  all;
    struct  FLCERRSTATUS_BITS  bit;
};

struct CERRFLG_BITS {                   // bits description
    Uint16 CPURDERR:1;                  // 0 CPU Correctable Read Error Flag
    Uint16 rsvd1:1;                     // 1 Reserved
    Uint16 rsvd2:1;                     // 2 Reserved
    Uint16 rsvd3:1;                     // 3 Reserved
    Uint16 rsvd4:12;                    // 15:4 Reserved
    Uint16 rsvd5:16;                    // 31:16 Reserved
};

union CERRFLG_REG {
    Uint32  all;
    struct  CERRFLG_BITS  bit;
};

struct CERRSET_BITS {                   // bits description
    Uint16 CPURDERR:1;                  // 0 CPU Correctable Read Error Flag Set
    Uint16 rsvd1:1;                     // 1 Reserved
    Uint16 rsvd2:1;                     // 2 Reserved
    Uint16 rsvd3:1;                     // 3 Reserved
    Uint16 rsvd4:12;                    // 15:4 Reserved
    Uint16 rsvd5:16;                    // 31:16 Reserved
};

union CERRSET_REG {
    Uint32  all;
    struct  CERRSET_BITS  bit;
};

struct CERRCLR_BITS {                   // bits description
    Uint16 CPURDERR:1;                  // 0 CPU Correctable Read Error Flag Clear
    Uint16 rsvd1:1;                     // 1 Reserved
    Uint16 rsvd2:1;                     // 2 Reserved
    Uint16 rsvd3:1;                     // 3 Reserved
    Uint16 rsvd4:12;                    // 15:4 Reserved
    Uint16 rsvd5:16;                    // 31:16 Reserved
};

union CERRCLR_REG {
    Uint32  all;
    struct  CERRCLR_BITS  bit;
};

struct CERRTHRES_BITS {                 // bits description
    Uint16 CERRTHRES:16;                // 15:0 Correctable error threshold.
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union CERRTHRES_REG {
    Uint32  all;
    struct  CERRTHRES_BITS  bit;
};

struct CEINTFLG_BITS {                  // bits description
    Uint16 CEINTFLAG:1;                 // 0 Total corrected error count exceeded threshold flag.
    Uint16 rsvd1:15;                    // 15:1 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union CEINTFLG_REG {
    Uint32  all;
    struct  CEINTFLG_BITS  bit;
};

struct CEINTCLR_BITS {                  // bits description
    Uint16 CEINTCLR:1;                  // 0 CPU Corrected Error Threshold Exceeded Error Clear.
    Uint16 rsvd1:15;                    // 15:1 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union CEINTCLR_REG {
    Uint32  all;
    struct  CEINTCLR_BITS  bit;
};

struct CEINTSET_BITS {                  // bits description
    Uint16 CEINTSET:1;                  // 0 Total corrected error count exceeded flag set.
    Uint16 rsvd1:15;                    // 15:1 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union CEINTSET_REG {
    Uint32  all;
    struct  CEINTSET_BITS  bit;
};

struct CEINTEN_BITS {                   // bits description
    Uint16 CEINTEN:1;                   // 0 CPU/DMA Correctable Error Interrupt Enable.
    Uint16 rsvd1:15;                    // 15:1 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union CEINTEN_REG {
    Uint32  all;
    struct  CEINTEN_BITS  bit;
};

struct MEMORY_ERROR_REGS {
    union   UCERRFLG_REG                     UCERRFLG;                     // Uncorrectable Error Flag Register
    union   UCERRSET_REG                     UCERRSET;                     // Uncorrectable Error Flag Set Register
    union   UCERRCLR_REG                     UCERRCLR;                     // Uncorrectable Error Flag Clear Register
    Uint32                                   UCCPUREADDR;                  // Uncorrectable CPU Read Error Address
    Uint16                                   rsvd1[20];                    // Reserved
    union   FLUCERRSTATUS_REG                FLUCERRSTATUS;                // Flash read uncorrectable ecc err status
    union   FLCERRSTATUS_REG                 FLCERRSTATUS;                 // Flash read correctable ecc err status
    union   CERRFLG_REG                      CERRFLG;                      // Correctable Error Flag Register
    union   CERRSET_REG                      CERRSET;                      // Correctable Error Flag Set Register
    union   CERRCLR_REG                      CERRCLR;                      // Correctable Error Flag Clear Register
    Uint32                                   CCPUREADDR;                   // Correctable CPU Read Error Address
    Uint16                                   rsvd2[6];                     // Reserved
    Uint32                                   CERRCNT;                      // Correctable Error Count Register
    union   CERRTHRES_REG                    CERRTHRES;                    // Correctable Error Threshold Value Register
    union   CEINTFLG_REG                     CEINTFLG;                     // Correctable Error Interrupt Flag Status Register
    union   CEINTCLR_REG                     CEINTCLR;                     // Correctable Error Interrupt Flag Clear Register
    union   CEINTSET_REG                     CEINTSET;                     // Correctable Error Interrupt Flag Set Register
    union   CEINTEN_REG                      CEINTEN;                      // Correctable Error Interrupt Enable Register
};

struct CPU_RAM_TEST_ERROR_STS_BITS {    // bits description
    Uint16 COR_ERROR:1;                 // 0 COR_ERROR flag
    Uint16 UNC_ERROR:1;                 // 1 UNC_ERROR flag
    Uint16 rsvd1:14;                    // 15:2 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union CPU_RAM_TEST_ERROR_STS_REG {
    Uint32  all;
    struct  CPU_RAM_TEST_ERROR_STS_BITS  bit;
};

struct CPU_RAM_TEST_ERROR_STS_CLR_BITS {// bits description
    Uint16 COR_ERROR:1;                 // 0 COR_ERROR flag clear bit
    Uint16 UNC_ERROR:1;                 // 1 UNC_ERROR flag clear bit
    Uint16 rsvd1:14;                    // 15:2 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union CPU_RAM_TEST_ERROR_STS_CLR_REG {
    Uint32  all;
    struct  CPU_RAM_TEST_ERROR_STS_CLR_BITS  bit;
};

struct TEST_ERROR_REGS {
    union   CPU_RAM_TEST_ERROR_STS_REG       CPU_RAM_TEST_ERROR_STS;       // Ram Test: Error Status Register
    union   CPU_RAM_TEST_ERROR_STS_CLR_REG   CPU_RAM_TEST_ERROR_STS_CLR;   // Ram Test: Error Status Clear Register
    Uint32                                   CPU_RAM_TEST_ERROR_ADDR;      // Ram Test: Error address register
};

//---------------------------------------------------------------------------
// MEMCONFIG External References & Function Declarations:
//
extern volatile struct MEM_CFG_REGS MemCfgRegs;
extern volatile struct ACCESS_PROTECTION_REGS AccessProtectionRegs;
extern volatile struct MEMORY_ERROR_REGS MemoryErrorRegs;
extern volatile struct TEST_ERROR_REGS TestErrorRegs;
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
