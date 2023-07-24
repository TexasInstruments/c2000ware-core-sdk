//###########################################################################
//
// FILE:    f28p65x_memconfig.h
//
// TITLE:   Definitions for the MEMCONFIG registers.
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

#ifndef F28P65X_MEMCONFIG_H
#define F28P65X_MEMCONFIG_H

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// MEMCONFIG Individual Register Bit Definitions:

struct DxLOCK_BITS {                    // bits description
    Uint16 LOCK_M0:1;                   // 0 M0 RAM Lock bits
    Uint16 LOCK_M1:1;                   // 1 M1 RAM Lock bits
    Uint16 LOCK_D0:1;                   // 2 D0 RAM Lock bits
    Uint16 LOCK_D1:1;                   // 3 D1 RAM Lock bits
    Uint16 LOCK_D2:1;                   // 4 D2 RAM Lock bits
    Uint16 LOCK_D3:1;                   // 5 D3 RAM Lock bits
    Uint16 LOCK_D4:1;                   // 6 D4 RAM Lock bits
    Uint16 LOCK_D5:1;                   // 7 D5 RAM Lock bits
    Uint16 LOCK_PIEVECT:1;              // 8 PIEVECT RAM Lock bits
    Uint16 rsvd1:7;                     // 15:9 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union DxLOCK_REG {
    Uint32  all;
    struct  DxLOCK_BITS  bit;
};

struct DxCOMMIT_BITS {                  // bits description
    Uint16 COMMIT_M0:1;                 // 0 M0 RAM Permanent Lock bits
    Uint16 COMMIT_M1:1;                 // 1 M1 RAM Permanent Lock bits
    Uint16 COMMIT_D0:1;                 // 2 D0 RAM Permanent Lock bits
    Uint16 COMMIT_D1:1;                 // 3 D1 RAM Permanent Lock bits
    Uint16 COMMIT_D2:1;                 // 4 D2 RAM Permanent Lock bits
    Uint16 COMMIT_D3:1;                 // 5 D3 RAM Permanent Lock bits
    Uint16 COMMIT_D4:1;                 // 6 D4 RAM Permanent Lock bits
    Uint16 COMMIT_D5:1;                 // 7 D5 RAM Permanent Lock bits
    Uint16 COMMIT_PIEVECT:1;            // 8 PIEVECT RAM Permanent Lock bits
    Uint16 rsvd1:7;                     // 15:9 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
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
    Uint16 FETCHPROT_D0:1;              // 16 Fetch Protection For D0 RAM
    Uint16 CPUWRPROT_D0:1;              // 17 CPU WR Protection For D0 RAM
    Uint16 rsvd3:6;                     // 23:18 Reserved
    Uint16 FETCHPROT_D1:1;              // 24 Fetch Protection For D1 RAM
    Uint16 CPUWRPROT_D1:1;              // 25 CPU WR Protection For D1 RAM
    Uint16 rsvd4:6;                     // 31:26 Reserved
};

union DxACCPROT0_REG {
    Uint32  all;
    struct  DxACCPROT0_BITS  bit;
};

struct DxACCPROT1_BITS {                // bits description
    Uint16 FETCHPROT_D2:1;              // 0 Fetch Protection For D0 RAM
    Uint16 CPUWRPROT_D2:1;              // 1 CPU WR Protection For D2 RAM
    Uint16 rsvd1:6;                     // 7:2 Reserved
    Uint16 FETCHPROT_D3:1;              // 8 Fetch Protection For D3 RAM
    Uint16 CPUWRPROT_D3:1;              // 9 CPU WR Protection For D3 RAM
    Uint16 rsvd2:6;                     // 15:10 Reserved
    Uint16 FETCHPROT_D4:1;              // 16 Fetch Protection For D4 RAM
    Uint16 CPUWRPROT_D4:1;              // 17 CPU WR Protection For D4 RAM
    Uint16 rsvd3:6;                     // 23:18 Reserved
    Uint16 FETCHPROT_D5:1;              // 24 Fetch Protection For D5 RAM
    Uint16 CPUWRPROT_D5:1;              // 25 CPU WR Protection For D5 RAM
    Uint16 rsvd4:6;                     // 31:26 Reserved
};

union DxACCPROT1_REG {
    Uint32  all;
    struct  DxACCPROT1_BITS  bit;
};

struct DxTEST_BITS {                    // bits description
    Uint16 TEST_M0:2;                   // 1:0 Selects the different modes for M0 RAM
    Uint16 TEST_M1:2;                   // 3:2 Selects the different modes for M1 RAM
    Uint16 TEST_D0:2;                   // 5:4 Selects the different modes for D0 RAM
    Uint16 TEST_D1:2;                   // 7:6 Selects the different modes for D1 RAM
    Uint16 TEST_D2:2;                   // 9:8 Selects the different modes for D2 RAM
    Uint16 TEST_D3:2;                   // 11:10 Selects the different modes for D3 RAM
    Uint16 TEST_D4:2;                   // 13:12 Selects the different modes for D4 RAM
    Uint16 TEST_D5:2;                   // 15:14 Selects the different modes for D5 RAM
    Uint16 rsvd1:2;                     // 17:16 Reserved
    Uint16 rsvd2:14;                    // 31:18 Reserved
};

union DxTEST_REG {
    Uint32  all;
    struct  DxTEST_BITS  bit;
};

struct DxINIT_BITS {                    // bits description
    Uint16 INIT_M0:1;                   // 0 RAM Initialization control for M0 RAM.
    Uint16 INIT_M1:1;                   // 1 RAM Initialization control for M1 RAM.
    Uint16 INIT_D0:1;                   // 2 RAM Initialization control for D0 RAM.
    Uint16 INIT_D1:1;                   // 3 RAM Initialization control for D1 RAM.
    Uint16 INIT_D2:1;                   // 4 RAM Initialization control for D2 RAM.
    Uint16 INIT_D3:1;                   // 5 RAM Initialization control for D3 RAM.
    Uint16 INIT_D4:1;                   // 6 RAM Initialization control for D4 RAM.
    Uint16 INIT_D5:1;                   // 7 RAM Initialization control for D5 RAM.
    Uint16 rsvd1:1;                     // 8 Reserved
    Uint16 rsvd2:7;                     // 15:9 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union DxINIT_REG {
    Uint32  all;
    struct  DxINIT_BITS  bit;
};

struct DxINITDONE_BITS {                // bits description
    Uint16 INITDONE_M0:1;               // 0 RAM Initialization status for M0 RAM.
    Uint16 INITDONE_M1:1;               // 1 RAM Initialization status for M1 RAM.
    Uint16 INITDONE_D0:1;               // 2 RAM Initialization status for D0 RAM.
    Uint16 INITDONE_D1:1;               // 3 RAM Initialization status for D1 RAM.
    Uint16 INITDONE_D2:1;               // 4 RAM Initialization status for D2 RAM.
    Uint16 INITDONE_D3:1;               // 5 RAM Initialization status for D3 RAM.
    Uint16 INITDONE_D4:1;               // 6 RAM Initialization status for D4 RAM.
    Uint16 INITDONE_D5:1;               // 7 RAM Initialization status for D5 RAM.
    Uint16 rsvd1:1;                     // 8 Reserved
    Uint16 rsvd2:7;                     // 15:9 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union DxINITDONE_REG {
    Uint32  all;
    struct  DxINITDONE_BITS  bit;
};

struct DxRAMTEST_LOCK_BITS {            // bits description
    Uint16 M0:1;                        // 0 DxTEST.TEST_M0 LOCK
    Uint16 M1:1;                        // 1 DxTEST.TEST_M1 LOCK
    Uint16 D0:1;                        // 2 DxTEST.TEST_D0 LOCK
    Uint16 D1:1;                        // 3 DxTEST.TEST_D1 LOCK
    Uint16 D2:1;                        // 4 DxTEST.TEST_D2 LOCK
    Uint16 D3:1;                        // 5 DxTEST.TEST_D3 LOCK
    Uint16 D4:1;                        // 6 DxTEST.TEST_D4 LOCK
    Uint16 D5:1;                        // 7 DxTEST.TEST_D5 LOCK
    Uint16 PIEVECT:1;                   // 8 DxTEST.TEST_PIEVECT LOCK
    Uint16 rsvd1:7;                     // 15:9 Reserved
    Uint16 KEY:16;                      // 31:16 Key for writing DxRAMTEST_LOCK
};

union DxRAMTEST_LOCK_REG {
    Uint32  all;
    struct  DxRAMTEST_LOCK_BITS  bit;
};

struct LSxLOCK_BITS {                   // bits description
    Uint16 LOCK_LS0:1;                  // 0 LS0 RAM Lock bits
    Uint16 LOCK_LS1:1;                  // 1 LS1 RAM Lock bits
    Uint16 LOCK_LS2:1;                  // 2 LS2 RAM Lock bits
    Uint16 LOCK_LS3:1;                  // 3 LS3 RAM Lock bits
    Uint16 LOCK_LS4:1;                  // 4 LS4 RAM Lock bits
    Uint16 LOCK_LS5:1;                  // 5 LS5 RAM Lock bits
    Uint16 LOCK_LS6:1;                  // 6 LS6 RAM Lock bits
    Uint16 LOCK_LS7:1;                  // 7 LS7 RAM Lock bits
    Uint16 LOCK_LS8:1;                  // 8 LS8 RAM Lock bits
    Uint16 LOCK_LS9:1;                  // 9 LS9 RAM Lock bits
    Uint16 rsvd1:1;                     // 10 Reserved
    Uint16 rsvd2:1;                     // 11 Reserved
    Uint16 rsvd3:4;                     // 15:12 Reserved
    Uint16 rsvd4:16;                    // 31:16 Reserved
};

union LSxLOCK_REG {
    Uint32  all;
    struct  LSxLOCK_BITS  bit;
};

struct LSxCOMMIT_BITS {                 // bits description
    Uint16 COMMIT_LS0:1;                // 0 LS0 RAM Permanent Lock bits
    Uint16 COMMIT_LS1:1;                // 1 LS1 RAM Permanent Lock bits
    Uint16 COMMIT_LS2:1;                // 2 LS2 RAM Permanent Lock bits
    Uint16 COMMIT_LS3:1;                // 3 LS3 RAM Permanent Lock bits
    Uint16 COMMIT_LS4:1;                // 4 LS4 RAM Permanent Lock bits
    Uint16 COMMIT_LS5:1;                // 5 LS5 RAM Permanent Lock bits
    Uint16 COMMIT_LS6:1;                // 6 LS6 RAM Permanent Lock bits
    Uint16 COMMIT_LS7:1;                // 7 LS7 RAM Permanent Lock bits
    Uint16 COMMIT_LS8:1;                // 8 LS8 RAM Permanent Lock bits
    Uint16 COMMIT_LS9:1;                // 9 LS9 RAM Permanent Lock bits
    Uint16 rsvd1:1;                     // 10 Reserved
    Uint16 rsvd2:1;                     // 11 Reserved
    Uint16 rsvd3:4;                     // 15:12 Reserved
    Uint16 rsvd4:16;                    // 31:16 Reserved
};

union LSxCOMMIT_REG {
    Uint32  all;
    struct  LSxCOMMIT_BITS  bit;
};

struct LSxMSEL_BITS {                   // bits description
    Uint16 MSEL_LS0:2;                  // 1:0 Controller Select for LS0 RAM
    Uint16 MSEL_LS1:2;                  // 3:2 Controller Select for LS1 RAM
    Uint16 MSEL_LS2:2;                  // 5:4 Controller Select for LS2 RAM
    Uint16 MSEL_LS3:2;                  // 7:6 Controller Select for LS3 RAM
    Uint16 MSEL_LS4:2;                  // 9:8 Controller Select for LS4 RAM
    Uint16 MSEL_LS5:2;                  // 11:10 Controller Select for LS5 RAM
    Uint16 MSEL_LS6:2;                  // 13:12 Controller Select for LS6 RAM
    Uint16 MSEL_LS7:2;                  // 15:14 Controller Select for LS7 RAM
    Uint16 MSEL_LS8:2;                  // 17:16 Controller Select for LS8 RAM
    Uint16 MSEL_LS9:2;                  // 19:18 Controller Select for LS9 RAM
    Uint16 rsvd1:2;                     // 21:20 Reserved
    Uint16 rsvd2:2;                     // 23:22 Reserved
    Uint16 rsvd3:8;                     // 31:24 Reserved
};

union LSxMSEL_REG {
    Uint32  all;
    struct  LSxMSEL_BITS  bit;
};

struct LSxCLAPGM_BITS {                 // bits description
    Uint16 CLAPGM_LS0:1;                // 0 Selects LS0 RAM as program vs data memory for CLA
    Uint16 CLAPGM_LS1:1;                // 1 Selects LS1 RAM as program vs data memory for CLA
    Uint16 CLAPGM_LS2:1;                // 2 Selects LS2 RAM as program vs data memory for CLA
    Uint16 CLAPGM_LS3:1;                // 3 Selects LS3 RAM as program vs data memory for CLA
    Uint16 CLAPGM_LS4:1;                // 4 Selects LS4 RAM as program vs data memory for CLA
    Uint16 CLAPGM_LS5:1;                // 5 Selects LS5 RAM as program vs data memory for CLA
    Uint16 CLAPGM_LS6:1;                // 6 Selects LS6 RAM as program vs data memory for CLA
    Uint16 CLAPGM_LS7:1;                // 7 Selects LS7 RAM as program vs data memory for CLA
    Uint16 rsvd1:1;                     // 8 Reserved
    Uint16 rsvd2:1;                     // 9 Reserved
    Uint16 rsvd3:1;                     // 10 Reserved
    Uint16 rsvd4:1;                     // 11 Reserved
    Uint16 rsvd5:4;                     // 15:12 Reserved
    Uint16 rsvd6:16;                    // 31:16 Reserved
};

union LSxCLAPGM_REG {
    Uint32  all;
    struct  LSxCLAPGM_BITS  bit;
};

struct LSxACCPROT0_BITS {               // bits description
    Uint16 FETCHPROT_LS0:1;             // 0 Fetch Protection For LS0 RAM
    Uint16 CPUWRPROT_LS0:1;             // 1 CPU WR Protection For LS0 RAM
    Uint16 rsvd1:6;                     // 7:2 Reserved
    Uint16 FETCHPROT_LS1:1;             // 8 Fetch Protection For LS1 RAM
    Uint16 CPUWRPROT_LS1:1;             // 9 CPU WR Protection For LS1 RAM
    Uint16 rsvd2:6;                     // 15:10 Reserved
    Uint16 FETCHPROT_LS2:1;             // 16 Fetch Protection For LS2 RAM
    Uint16 CPUWRPROT_LS2:1;             // 17 CPU WR Protection For LS2 RAM
    Uint16 rsvd3:6;                     // 23:18 Reserved
    Uint16 FETCHPROT_LS3:1;             // 24 Fetch Protection For LS3 RAM
    Uint16 CPUWRPROT_LS3:1;             // 25 CPU WR Protection For LS3 RAM
    Uint16 rsvd4:6;                     // 31:26 Reserved
};

union LSxACCPROT0_REG {
    Uint32  all;
    struct  LSxACCPROT0_BITS  bit;
};

struct LSxACCPROT1_BITS {               // bits description
    Uint16 FETCHPROT_LS4:1;             // 0 Fetch Protection For LS4 RAM
    Uint16 CPUWRPROT_LS4:1;             // 1 CPU WR Protection For LS4 RAM
    Uint16 rsvd1:6;                     // 7:2 Reserved
    Uint16 FETCHPROT_LS5:1;             // 8 Fetch Protection For LS5 RAM
    Uint16 CPUWRPROT_LS5:1;             // 9 CPU WR Protection For LS5 RAM
    Uint16 rsvd2:6;                     // 15:10 Reserved
    Uint16 FETCHPROT_LS6:1;             // 16 Fetch Protection For LS6 RAM
    Uint16 CPUWRPROT_LS6:1;             // 17 CPU WR Protection For LS6 RAM
    Uint16 rsvd3:6;                     // 23:18 Reserved
    Uint16 FETCHPROT_LS7:1;             // 24 Fetch Protection For LS7 RAM
    Uint16 CPUWRPROT_LS7:1;             // 25 CPU WR Protection For LS7 RAM
    Uint16 rsvd4:6;                     // 31:26 Reserved
};

union LSxACCPROT1_REG {
    Uint32  all;
    struct  LSxACCPROT1_BITS  bit;
};

struct LSxACCPROT2_BITS {               // bits description
    Uint16 FETCHPROT_LS8:1;             // 0 Fetch Protection For LS8 RAM
    Uint16 CPUWRPROT_LS8:1;             // 1 CPU WR Protection For LS8 RAM
    Uint16 rsvd1:6;                     // 7:2 Reserved
    Uint16 FETCHPROT_LS9:1;             // 8 Fetch Protection For LS9 RAM
    Uint16 CPUWRPROT_LS9:1;             // 9 CPU WR Protection For LS9 RAM
    Uint16 rsvd2:6;                     // 15:10 Reserved
    Uint16 rsvd3:1;                     // 16 Reserved
    Uint16 rsvd4:1;                     // 17 Reserved
    Uint16 rsvd5:6;                     // 23:18 Reserved
    Uint16 rsvd6:1;                     // 24 Reserved
    Uint16 rsvd7:1;                     // 25 Reserved
    Uint16 rsvd8:6;                     // 31:26 Reserved
};

union LSxACCPROT2_REG {
    Uint32  all;
    struct  LSxACCPROT2_BITS  bit;
};

struct LSxTEST_BITS {                   // bits description
    Uint16 TEST_LS0:2;                  // 1:0 Selects the different modes for LS0 RAM
    Uint16 TEST_LS1:2;                  // 3:2 Selects the different modes for LS1 RAM
    Uint16 TEST_LS2:2;                  // 5:4 Selects the different modes for LS2 RAM
    Uint16 TEST_LS3:2;                  // 7:6 Selects the different modes for LS3 RAM
    Uint16 TEST_LS4:2;                  // 9:8 Selects the different modes for LS4 RAM
    Uint16 TEST_LS5:2;                  // 11:10 Selects the different modes for LS5 RAM
    Uint16 TEST_LS6:2;                  // 13:12 Selects the different modes for LS6 RAM
    Uint16 TEST_LS7:2;                  // 15:14 Selects the different modes for LS7 RAM
    Uint16 TEST_LS8:2;                  // 17:16 Selects the different modes for LS8 RAM
    Uint16 TEST_LS9:2;                  // 19:18 Selects the different modes for LS9 RAM
    Uint16 rsvd1:2;                     // 21:20 Reserved
    Uint16 rsvd2:2;                     // 23:22 Reserved
    Uint16 rsvd3:8;                     // 31:24 Reserved
};

union LSxTEST_REG {
    Uint32  all;
    struct  LSxTEST_BITS  bit;
};

struct LSxINIT_BITS {                   // bits description
    Uint16 INIT_LS0:1;                  // 0 RAM Initialization control for LS0 RAM.
    Uint16 INIT_LS1:1;                  // 1 RAM Initialization control for LS1 RAM.
    Uint16 INIT_LS2:1;                  // 2 RAM Initialization control for LS2 RAM.
    Uint16 INIT_LS3:1;                  // 3 RAM Initialization control for LS3 RAM.
    Uint16 INIT_LS4:1;                  // 4 RAM Initialization control for LS4 RAM.
    Uint16 INIT_LS5:1;                  // 5 RAM Initialization control for LS5 RAM.
    Uint16 INIT_LS6:1;                  // 6 RAM Initialization control for LS6 RAM.
    Uint16 INIT_LS7:1;                  // 7 RAM Initialization control for LS7 RAM.
    Uint16 INIT_LS8:1;                  // 8 RAM Initialization control for LS8 RAM.
    Uint16 INIT_LS9:1;                  // 9 RAM Initialization control for LS9 RAM.
    Uint16 rsvd1:1;                     // 10 Reserved
    Uint16 rsvd2:1;                     // 11 Reserved
    Uint16 rsvd3:4;                     // 15:12 Reserved
    Uint16 rsvd4:16;                    // 31:16 Reserved
};

union LSxINIT_REG {
    Uint32  all;
    struct  LSxINIT_BITS  bit;
};

struct LSxINITDONE_BITS {               // bits description
    Uint16 INITDONE_LS0:1;              // 0 RAM Initialization status for LS0 RAM.
    Uint16 INITDONE_LS1:1;              // 1 RAM Initialization status for LS1 RAM.
    Uint16 INITDONE_LS2:1;              // 2 RAM Initialization status for LS2 RAM.
    Uint16 INITDONE_LS3:1;              // 3 RAM Initialization status for LS3 RAM.
    Uint16 INITDONE_LS4:1;              // 4 RAM Initialization status for LS4 RAM.
    Uint16 INITDONE_LS5:1;              // 5 RAM Initialization status for LS5 RAM.
    Uint16 INITDONE_LS6:1;              // 6 RAM Initialization status for LS6 RAM.
    Uint16 INITDONE_LS7:1;              // 7 RAM Initialization status for LS7 RAM.
    Uint16 INITDONE_LS8:1;              // 8 RAM Initialization status for LS8 RAM.
    Uint16 INITDONE_LS9:1;              // 9 RAM Initialization status for LS9 RAM.
    Uint16 rsvd1:1;                     // 10 Reserved
    Uint16 rsvd2:1;                     // 11 Reserved
    Uint16 rsvd3:4;                     // 15:12 Reserved
    Uint16 rsvd4:16;                    // 31:16 Reserved
};

union LSxINITDONE_REG {
    Uint32  all;
    struct  LSxINITDONE_BITS  bit;
};

struct LSxRAMTEST_LOCK_BITS {           // bits description
    Uint16 LS0:1;                       // 0 LSxTEST.TEST_LS0 LOCK
    Uint16 LS1:1;                       // 1 LSxTEST.TEST_LS1 LOCK
    Uint16 LS2:1;                       // 2 LSxTEST.TEST_LS2 LOCK
    Uint16 LS3:1;                       // 3 LSxTEST.TEST_LS3 LOCK
    Uint16 LS4:1;                       // 4 LSxTEST.TEST_LS4 LOCK
    Uint16 LS5:1;                       // 5 LSxTEST.TEST_LS5 LOCK
    Uint16 LS6:1;                       // 6 LSxTEST.TEST_LS6 LOCK
    Uint16 LS7:1;                       // 7 LSxTEST.TEST_LS7 LOCK
    Uint16 LS8:1;                       // 8 LSxTEST.TEST_LS8 LOCK
    Uint16 LS9:1;                       // 9 LSxTEST.TEST_LS9 LOCK
    Uint16 rsvd1:1;                     // 10 Reserved
    Uint16 rsvd2:1;                     // 11 Reserved
    Uint16 rsvd3:4;                     // 15:12 Reserved
    Uint16 KEY:16;                      // 31:16 KEY to enable write to lock
};

union LSxRAMTEST_LOCK_REG {
    Uint32  all;
    struct  LSxRAMTEST_LOCK_BITS  bit;
};

struct GSxLOCK_BITS {                   // bits description
    Uint16 LOCK_GS0:1;                  // 0 GS0 RAM Lock bits
    Uint16 LOCK_GS1:1;                  // 1 GS1 RAM Lock bits
    Uint16 LOCK_GS2:1;                  // 2 GS2 RAM Lock bits
    Uint16 LOCK_GS3:1;                  // 3 GS3 RAM Lock bits
    Uint16 LOCK_GS4:1;                  // 4 GS4 RAM Lock bits
    Uint16 rsvd1:1;                     // 5 Reserved
    Uint16 rsvd2:1;                     // 6 Reserved
    Uint16 rsvd3:1;                     // 7 Reserved
    Uint16 rsvd4:1;                     // 8 Reserved
    Uint16 rsvd5:1;                     // 9 Reserved
    Uint16 rsvd6:1;                     // 10 Reserved
    Uint16 rsvd7:1;                     // 11 Reserved
    Uint16 rsvd8:1;                     // 12 Reserved
    Uint16 rsvd9:1;                     // 13 Reserved
    Uint16 rsvd10:1;                    // 14 Reserved
    Uint16 rsvd11:1;                    // 15 Reserved
    Uint16 rsvd12:16;                   // 31:16 Reserved
};

union GSxLOCK_REG {
    Uint32  all;
    struct  GSxLOCK_BITS  bit;
};

struct GSxCOMMIT_BITS {                 // bits description
    Uint16 COMMIT_GS0:1;                // 0 GS0 RAM Permanent Lock bits
    Uint16 COMMIT_GS1:1;                // 1 GS1 RAM Permanent Lock bits
    Uint16 COMMIT_GS2:1;                // 2 GS2 RAM Permanent Lock bits
    Uint16 COMMIT_GS3:1;                // 3 GS3 RAM Permanent Lock bits
    Uint16 COMMIT_GS4:1;                // 4 GS4 RAM Permanent Lock bits
    Uint16 rsvd1:1;                     // 5 Reserved
    Uint16 rsvd2:1;                     // 6 Reserved
    Uint16 rsvd3:1;                     // 7 Reserved
    Uint16 rsvd4:1;                     // 8 Reserved
    Uint16 rsvd5:1;                     // 9 Reserved
    Uint16 rsvd6:1;                     // 10 Reserved
    Uint16 rsvd7:1;                     // 11 Reserved
    Uint16 rsvd8:1;                     // 12 Reserved
    Uint16 rsvd9:1;                     // 13 Reserved
    Uint16 rsvd10:1;                    // 14 Reserved
    Uint16 rsvd11:1;                    // 15 Reserved
    Uint16 rsvd12:16;                   // 31:16 Reserved
};

union GSxCOMMIT_REG {
    Uint32  all;
    struct  GSxCOMMIT_BITS  bit;
};

struct GSxMSEL_BITS {                   // bits description
    Uint16 MSEL_GS0:1;                  // 0 Controller Select for GS0 RAM
    Uint16 MSEL_GS1:1;                  // 1 Controller Select for GS1 RAM
    Uint16 MSEL_GS2:1;                  // 2 Controller Select for GS2 RAM
    Uint16 MSEL_GS3:1;                  // 3 Controller Select for GS3 RAM
    Uint16 MSEL_GS4:1;                  // 4 Controller Select for GS4 RAM
    Uint16 rsvd1:1;                     // 5 Reserved
    Uint16 rsvd2:1;                     // 6 Reserved
    Uint16 rsvd3:1;                     // 7 Reserved
    Uint16 rsvd4:1;                     // 8 Reserved
    Uint16 rsvd5:1;                     // 9 Reserved
    Uint16 rsvd6:1;                     // 10 Reserved
    Uint16 rsvd7:1;                     // 11 Reserved
    Uint16 rsvd8:1;                     // 12 Reserved
    Uint16 rsvd9:1;                     // 13 Reserved
    Uint16 rsvd10:1;                    // 14 Reserved
    Uint16 rsvd11:1;                    // 15 Reserved
    Uint16 rsvd12:16;                   // 31:16 Reserved
};

union GSxMSEL_REG {
    Uint32  all;
    struct  GSxMSEL_BITS  bit;
};

struct GSxACCPROT0_BITS {               // bits description
    Uint16 FETCHPROT_GS0:1;             // 0 Fetch Protection For GS0 RAM
    Uint16 CPUWRPROT_GS0:1;             // 1 CPU WR Protection For GS0 RAM
    Uint16 DMAWRPROT_GS0:1;             // 2 DMA WR Protection For GS0 RAM
    Uint16 rsvd1:1;                     // 3 Reserved
    Uint16 rsvd2:4;                     // 7:4 Reserved
    Uint16 FETCHPROT_GS1:1;             // 8 Fetch Protection For GS1 RAM
    Uint16 CPUWRPROT_GS1:1;             // 9 CPU WR Protection For GS1 RAM
    Uint16 DMAWRPROT_GS1:1;             // 10 DMA WR Protection For GS1 RAM
    Uint16 rsvd3:5;                     // 15:11 Reserved
    Uint16 FETCHPROT_GS2:1;             // 16 Fetch Protection For GS2 RAM
    Uint16 CPUWRPROT_GS2:1;             // 17 CPU WR Protection For GS2 RAM
    Uint16 DMAWRPROT_GS2:1;             // 18 DMA WR Protection For GS2 RAM
    Uint16 rsvd4:5;                     // 23:19 Reserved
    Uint16 FETCHPROT_GS3:1;             // 24 Fetch Protection For GS3 RAM
    Uint16 CPUWRPROT_GS3:1;             // 25 CPU WR Protection For GS3 RAM
    Uint16 DMAWRPROT_GS3:1;             // 26 DMA WR Protection For GS3 RAM
    Uint16 rsvd5:5;                     // 31:27 Reserved
};

union GSxACCPROT0_REG {
    Uint32  all;
    struct  GSxACCPROT0_BITS  bit;
};

struct GSxACCPROT1_BITS {               // bits description
    Uint16 FETCHPROT_GS4:1;             // 0 Fetch Protection For GS4 RAM
    Uint16 CPUWRPROT_GS4:1;             // 1 CPU WR Protection For GS4 RAM
    Uint16 DMAWRPROT_GS4:1;             // 2 DMA WR Protection For GS4 RAM
    Uint16 rsvd1:5;                     // 7:3 Reserved
    Uint16 rsvd2:1;                     // 8 Reserved
    Uint16 rsvd3:1;                     // 9 Reserved
    Uint16 rsvd4:1;                     // 10 Reserved
    Uint16 rsvd5:5;                     // 15:11 Reserved
    Uint16 rsvd6:1;                     // 16 Reserved
    Uint16 rsvd7:1;                     // 17 Reserved
    Uint16 rsvd8:1;                     // 18 Reserved
    Uint16 rsvd9:5;                     // 23:19 Reserved
    Uint16 rsvd10:1;                    // 24 Reserved
    Uint16 rsvd11:1;                    // 25 Reserved
    Uint16 rsvd12:1;                    // 26 Reserved
    Uint16 rsvd13:5;                    // 31:27 Reserved
};

union GSxACCPROT1_REG {
    Uint32  all;
    struct  GSxACCPROT1_BITS  bit;
};

struct GSxTEST_BITS {                   // bits description
    Uint16 TEST_GS0:2;                  // 1:0 Selects the different modes for GS0 RAM
    Uint16 TEST_GS1:2;                  // 3:2 Selects the different modes for GS1 RAM
    Uint16 TEST_GS2:2;                  // 5:4 Selects the different modes for GS2 RAM
    Uint16 TEST_GS3:2;                  // 7:6 Selects the different modes for GS3 RAM
    Uint16 TEST_GS4:2;                  // 9:8 Selects the different modes for GS4 RAM
    Uint16 rsvd1:2;                     // 11:10 Reserved
    Uint16 rsvd2:2;                     // 13:12 Reserved
    Uint16 rsvd3:2;                     // 15:14 Reserved
    Uint16 rsvd4:2;                     // 17:16 Reserved
    Uint16 rsvd5:2;                     // 19:18 Reserved
    Uint16 rsvd6:2;                     // 21:20 Reserved
    Uint16 rsvd7:2;                     // 23:22 Reserved
    Uint16 rsvd8:2;                     // 25:24 Reserved
    Uint16 rsvd9:2;                     // 27:26 Reserved
    Uint16 rsvd10:2;                    // 29:28 Reserved
    Uint16 rsvd11:2;                    // 31:30 Reserved
};

union GSxTEST_REG {
    Uint32  all;
    struct  GSxTEST_BITS  bit;
};

struct GSxINIT_BITS {                   // bits description
    Uint16 INIT_GS0:1;                  // 0 RAM Initialization control for GS0 RAM.
    Uint16 INIT_GS1:1;                  // 1 RAM Initialization control for GS1 RAM.
    Uint16 INIT_GS2:1;                  // 2 RAM Initialization control for GS2 RAM.
    Uint16 INIT_GS3:1;                  // 3 RAM Initialization control for GS3 RAM.
    Uint16 INIT_GS4:1;                  // 4 RAM Initialization control for GS4 RAM.
    Uint16 rsvd1:1;                     // 5 Reserved
    Uint16 rsvd2:1;                     // 6 Reserved
    Uint16 rsvd3:1;                     // 7 Reserved
    Uint16 rsvd4:1;                     // 8 Reserved
    Uint16 rsvd5:1;                     // 9 Reserved
    Uint16 rsvd6:1;                     // 10 Reserved
    Uint16 rsvd7:1;                     // 11 Reserved
    Uint16 rsvd8:1;                     // 12 Reserved
    Uint16 rsvd9:1;                     // 13 Reserved
    Uint16 rsvd10:1;                    // 14 Reserved
    Uint16 rsvd11:1;                    // 15 Reserved
    Uint16 rsvd12:16;                   // 31:16 Reserved
};

union GSxINIT_REG {
    Uint32  all;
    struct  GSxINIT_BITS  bit;
};

struct GSxINITDONE_BITS {               // bits description
    Uint16 INITDONE_GS0:1;              // 0 RAM Initialization status for GS0 RAM.
    Uint16 INITDONE_GS1:1;              // 1 RAM Initialization status for GS1 RAM.
    Uint16 INITDONE_GS2:1;              // 2 RAM Initialization status for GS2 RAM.
    Uint16 INITDONE_GS3:1;              // 3 RAM Initialization status for GS3 RAM.
    Uint16 INITDONE_GS4:1;              // 4 RAM Initialization status for GS4 RAM.
    Uint16 rsvd1:1;                     // 5 Reserved
    Uint16 rsvd2:1;                     // 6 Reserved
    Uint16 rsvd3:1;                     // 7 Reserved
    Uint16 rsvd4:1;                     // 8 Reserved
    Uint16 rsvd5:1;                     // 9 Reserved
    Uint16 rsvd6:1;                     // 10 Reserved
    Uint16 rsvd7:1;                     // 11 Reserved
    Uint16 rsvd8:1;                     // 12 Reserved
    Uint16 rsvd9:1;                     // 13 Reserved
    Uint16 rsvd10:1;                    // 14 Reserved
    Uint16 rsvd11:1;                    // 15 Reserved
    Uint16 rsvd12:16;                   // 31:16 Reserved
};

union GSxINITDONE_REG {
    Uint32  all;
    struct  GSxINITDONE_BITS  bit;
};

struct GSxRAMTEST_LOCK_BITS {           // bits description
    Uint16 GS0:1;                       // 0 GSxTEST.TEST_GS0 LOCK
    Uint16 GS1:1;                       // 1 GSxTEST.TEST_GS1 LOCK
    Uint16 GS2:1;                       // 2 GSxTEST.TEST_GS2 LOCK
    Uint16 GS3:1;                       // 3 GSxTEST.TEST_GS3 LOCK
    Uint16 GS4:1;                       // 4 GSxTEST.TEST_GS4 LOCK
    Uint16 rsvd1:1;                     // 5 Reserved
    Uint16 rsvd2:1;                     // 6 Reserved
    Uint16 rsvd3:1;                     // 7 Reserved
    Uint16 rsvd4:1;                     // 8 Reserved
    Uint16 rsvd5:1;                     // 9 Reserved
    Uint16 rsvd6:1;                     // 10 Reserved
    Uint16 rsvd7:1;                     // 11 Reserved
    Uint16 rsvd8:1;                     // 12 Reserved
    Uint16 rsvd9:1;                     // 13 Reserved
    Uint16 rsvd10:1;                    // 14 Reserved
    Uint16 rsvd11:1;                    // 15 Reserved
    Uint16 KEY:16;                      // 31:16 KEY to enable write to lock
};

union GSxRAMTEST_LOCK_REG {
    Uint32  all;
    struct  GSxRAMTEST_LOCK_BITS  bit;
};

struct MSGxLOCK_BITS {                  // bits description
    Uint16 LOCK_CPUTOCPU_MSGRAM0:1;     // 0 CPUTOCPU RAM Lock bits
    Uint16 LOCK_CPUTOCLA1:1;            // 1 CPUTOCLA1 RAM Lock bits
    Uint16 LOCK_CLA1TOCPU:1;            // 2 CLA1TOCPU RAM Lock bits
    Uint16 rsvd1:1;                     // 3 Reserved
    Uint16 rsvd2:1;                     // 4 Reserved
    Uint16 LOCK_CLA1TODMA:1;            // 5 CLA1TODMA RAM control fields lock bit
    Uint16 LOCK_DMATOCLA1:1;            // 6 DMATOCLA1 RAM control fields lock bit
    Uint16 LOCK_CPUTOCPU_MSGRAM1:1;     // 7 Lock bit of CPU to CPU MSG RAM1 control fields
    Uint16 rsvd3:1;                     // 8 Reserved
    Uint16 rsvd4:1;                     // 9 Reserved
    Uint16 rsvd5:1;                     // 10 Reserved
    Uint16 rsvd6:1;                     // 11 Reserved
    Uint16 rsvd7:4;                     // 15:12 Reserved
    Uint16 rsvd8:16;                    // 31:16 Reserved
};

union MSGxLOCK_REG {
    Uint32  all;
    struct  MSGxLOCK_BITS  bit;
};

struct MSGxCOMMIT_BITS {                // bits description
    Uint16 COMMIT_CPUTOCPU:1;           // 0 CPUTOCPU RAM control fields COMMIT bit
    Uint16 COMMIT_CPUTOCLA1:1;          // 1 CPUTOCLA1 RAM control fields COMMIT bit
    Uint16 COMMIT_CLA1TOCPU:1;          // 2 CLA1TOCPU RAM control fields COMMIT bit
    Uint16 rsvd1:1;                     // 3 Reserved
    Uint16 rsvd2:1;                     // 4 Reserved
    Uint16 COMMIT_CLA1TODMA:1;          // 5 CLA1TODMA RAM control fields COMMIT bit
    Uint16 COMMIT_DMATOCLA1:1;          // 6 DMATOCLA1 RAM control fields COMMIT bit
    Uint16 COMMIT_CPUTOCPU_MSGRAM1:1;   // 7 Commint bit of CPU to CPU MSG RAM1 control fields
    Uint16 rsvd3:1;                     // 8 Reserved
    Uint16 rsvd4:1;                     // 9 Reserved
    Uint16 rsvd5:1;                     // 10 Reserved
    Uint16 rsvd6:1;                     // 11 Reserved
    Uint16 rsvd7:4;                     // 15:12 Reserved
    Uint16 rsvd8:16;                    // 31:16 Reserved
};

union MSGxCOMMIT_REG {
    Uint32  all;
    struct  MSGxCOMMIT_BITS  bit;
};

struct MSGxACCPROT0_BITS {              // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 CPUWRPROT_CPUTOCPU_MSGRAM0:1; // 1 CPU WR Protection For CPUTOCPU_MSGRAM0 RAM
    Uint16 DMAWRPROT_CPUTOCPU_MSGRAM0:1; // 2 DMA WR Protection For CPUTOCPU_MSGRAM0 RAM
    Uint16 rsvd2:5;                     // 7:3 Reserved
    Uint16 rsvd3:1;                     // 8 Reserved
    Uint16 rsvd4:1;                     // 9 Reserved
    Uint16 rsvd5:1;                     // 10 Reserved
    Uint16 rsvd6:5;                     // 15:11 Reserved
    Uint16 rsvd7:1;                     // 16 Reserved
    Uint16 rsvd8:1;                     // 17 Reserved
    Uint16 rsvd9:1;                     // 18 Reserved
    Uint16 rsvd10:5;                    // 23:19 Reserved
    Uint16 rsvd11:1;                    // 24 Reserved
    Uint16 rsvd12:1;                    // 25 Reserved
    Uint16 rsvd13:1;                    // 26 Reserved
    Uint16 rsvd14:5;                    // 31:27 Reserved
};

union MSGxACCPROT0_REG {
    Uint32  all;
    struct  MSGxACCPROT0_BITS  bit;
};

struct MSGxTEST_BITS {                  // bits description
    Uint16 TEST_CPUTOCPU_MSGRAM0:2;     // 1:0 CPU to CPU Mode Select
    Uint16 TEST_CPUTOCLA1:2;            // 3:2 CPU to CLA1 MSG RAM Mode Select
    Uint16 TEST_CLA1TOCPU:2;            // 5:4 CLA1 to CPU MSG RAM Mode Select
    Uint16 rsvd1:2;                     // 7:6 Reserved
    Uint16 rsvd2:2;                     // 9:8 Reserved
    Uint16 TEST_CLA1TODMA:2;            // 11:10 CLA1 to DMA MSG RAM Mode Select
    Uint16 TEST_DMATOCLA1:2;            // 13:12 DMA to CLA1 MSG RAM Mode Select
    Uint16 TEST_CPUTOCPU_MSGRAM1:2;     // 15:14 CPU to CPU Mode Select
    Uint16 rsvd3:2;                     // 17:16 Reserved
    Uint16 rsvd4:2;                     // 19:18 Reserved
    Uint16 rsvd5:2;                     // 21:20 Reserved
    Uint16 rsvd6:2;                     // 23:22 Reserved
    Uint16 rsvd7:8;                     // 31:24 Reserved
};

union MSGxTEST_REG {
    Uint32  all;
    struct  MSGxTEST_BITS  bit;
};

struct MSGxINIT_BITS {                  // bits description
    Uint16 INIT_CPUTOCPU_MSGRAM0:1;     // 0 Initialization control for CPU to CPU MSG RAM
    Uint16 INIT_CPUTOCLA1:1;            // 1 Initialization control for CPUTOCLA1 MSG RAM
    Uint16 INIT_CLA1TOCPU:1;            // 2 Initialization control for CLA1TOCPU MSG RAM
    Uint16 rsvd1:1;                     // 3 Reserved
    Uint16 rsvd2:1;                     // 4 Reserved
    Uint16 INIT_CLA1TODMA:1;            // 5 Initialization control for CLA1 to DMA MSG RAM
    Uint16 INIT_DMATOCLA1:1;            // 6 Initialization control for DMA to CLA1 MSG RAM
    Uint16 INIT_CPUTOCPU_MSGRAM1:1;     // 7 Initialization control for CPU to CPU MSG RAM1
    Uint16 rsvd3:1;                     // 8 Reserved
    Uint16 rsvd4:1;                     // 9 Reserved
    Uint16 rsvd5:1;                     // 10 Reserved
    Uint16 rsvd6:1;                     // 11 Reserved
    Uint16 rsvd7:4;                     // 15:12 Reserved
    Uint16 rsvd8:16;                    // 31:16 Reserved
};

union MSGxINIT_REG {
    Uint32  all;
    struct  MSGxINIT_BITS  bit;
};

struct MSGxINITDONE_BITS {              // bits description
    Uint16 INITDONE_CPUTOCPU:1;         // 0 Initialization status for CPU to CPU MSG RAM
    Uint16 INITDONE_CPUTOCLA1:1;        // 1 Initialization status for CPU to CLA1 MSG RAM
    Uint16 INITDONE_CLA1TOCPU:1;        // 2 Initialization status for CLA1 to CPU MSG RAM
    Uint16 rsvd1:1;                     // 3 Reserved
    Uint16 rsvd2:1;                     // 4 Reserved
    Uint16 INITDONE_CLA1TODMA:1;        // 5 Initialization status for CLA1 to DMA MSG RAM
    Uint16 INITDONE_DMATOCLA1:1;        // 6 Initialization status for DMA to CLA1 MSG RAM
    Uint16 INITDONE_CPUTOCPU_MSGRAM1:1; // 7 Initialization status for CPU to CPU MSG RAM1
    Uint16 rsvd3:1;                     // 8 Reserved
    Uint16 rsvd4:1;                     // 9 Reserved
    Uint16 rsvd5:1;                     // 10 Reserved
    Uint16 rsvd6:1;                     // 11 Reserved
    Uint16 rsvd7:4;                     // 15:12 Reserved
    Uint16 rsvd8:16;                    // 31:16 Reserved
};

union MSGxINITDONE_REG {
    Uint32  all;
    struct  MSGxINITDONE_BITS  bit;
};

struct MSGxRAMTEST_LOCK_BITS {          // bits description
    Uint16 CPUTOCPU:1;                  // 0 MSGxRAMTEST_LOCK.CPUTOCPULock Configuration
    Uint16 CPUTOCLA1:1;                 // 1 MSGxRAMTEST_LOCK.CPUTOCLA1Lock Configuration
    Uint16 CLA1TOCPU:1;                 // 2 MSGxRAMTEST_LOCK.CLA1TOCPULock Configuration
    Uint16 rsvd1:1;                     // 3 Reserved
    Uint16 rsvd2:1;                     // 4 Reserved
    Uint16 CLA1TODMA:1;                 // 5 MSGxRAMTEST_LOCK.CLA1TODMALock Configuration
    Uint16 DMATOCLA1:1;                 // 6 MSGxRAMTEST_LOCK.DMATOCLA1Lock Configuration
    Uint16 CPUTOCPU_MSGRAM1:1;          // 7 MSGxRAMTEST_LOCK.CPUTOCPU_MSGRAM1Lock Configuration
    Uint16 rsvd3:1;                     // 8 Reserved
    Uint16 rsvd4:1;                     // 9 Reserved
    Uint16 rsvd5:1;                     // 10 Reserved
    Uint16 rsvd6:1;                     // 11 Reserved
    Uint16 rsvd7:4;                     // 15:12 Reserved
    Uint16 KEY:16;                      // 31:16 KEY to enable write to lock
};

union MSGxRAMTEST_LOCK_REG {
    Uint32  all;
    struct  MSGxRAMTEST_LOCK_BITS  bit;
};

struct ROM_LOCK_BITS {                  // bits description
    Uint16 LOCK_BOOTROM:1;              // 0 BOOTROM Lock bits
    Uint16 LOCK_SECUREROM:1;            // 1 SECUREROM Lock bits
    Uint16 LOCK_CLADATAROM:1;           // 2 CLADATAROM Lock bits
    Uint16 rsvd1:1;                     // 3 Reserved
    Uint16 rsvd2:12;                    // 15:4 Reserved
    Uint16 KEY:16;                      // 31:16 Key for writing ROM LOCK
};

union ROM_LOCK_REG {
    Uint32  all;
    struct  ROM_LOCK_BITS  bit;
};

struct ROM_TEST_BITS {                  // bits description
    Uint16 TEST_BOOTROM:2;              // 1:0 Selects the different modes for BOOTROM
    Uint16 TEST_SECUREROM:2;            // 3:2 Selects the different modes for SECUREROM
    Uint16 TEST_CLADATAROM:2;           // 5:4 Selects the different modes for CLADATAROM
    Uint16 rsvd1:2;                     // 7:6 Reserved
    Uint16 rsvd2:8;                     // 15:8 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union ROM_TEST_REG {
    Uint32  all;
    struct  ROM_TEST_BITS  bit;
};

struct ROM_FORCE_ERROR_BITS {           // bits description
    Uint16 FORCE_BOOTROM_ERROR:1;       // 0 Force Bootrom Parity Error
    Uint16 FORCE_SECUREROM_ERROR:1;     // 1 Force SECUREROM Parity Error
    Uint16 FORCE_CLADATAROM_ERROR:1;    // 2 Force CLADATAROM Parity Error
    Uint16 rsvd1:1;                     // 3 Reserved
    Uint16 rsvd2:12;                    // 15:4 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union ROM_FORCE_ERROR_REG {
    Uint32  all;
    struct  ROM_FORCE_ERROR_BITS  bit;
};

struct PERI_MEM_TEST_LOCK_BITS {        // bits description
    Uint16 LOCK_PERI_MEM_TEST_CONTROL:1; // 0 PERI_MEM_TEST_CONTROL Lock bit
    Uint16 rsvd1:15;                    // 15:1 Reserved
    Uint16 KEY:16;                      // 31:16 KEY to lock Peripheral memory test
};

union PERI_MEM_TEST_LOCK_REG {
    Uint32  all;
    struct  PERI_MEM_TEST_LOCK_BITS  bit;
};

struct PERI_MEM_TEST_CONTROL_BITS {     // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 rsvd2:1;                     // 1 Reserved
    Uint16 rsvd3:1;                     // 2 Reserved
    Uint16 rsvd4:1;                     // 3 Reserved
    Uint16 EtherCAT_TEST_ENABLE:1;      // 4 EtherCAT Test mode enable
    Uint16 EtherCAT_MEM_FORCE_ERROR:1;  // 5 Force Parity Error on EtherCAT RAM
    Uint16 rsvd5:10;                    // 15:6 Reserved
    Uint16 rsvd6:16;                    // 31:16 Reserved
};

union PERI_MEM_TEST_CONTROL_REG {
    Uint32  all;
    struct  PERI_MEM_TEST_CONTROL_BITS  bit;
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
    union   LSxMSEL_REG                      LSxMSEL;                      // Local Shared RAM Controller Sel Register
    union   LSxCLAPGM_REG                    LSxCLAPGM;                    // Local Shared RAM Prog/Exe control Register
    union   LSxACCPROT0_REG                  LSxACCPROT0;                  // Local Shared RAM Config Register 0
    union   LSxACCPROT1_REG                  LSxACCPROT1;                  // Local Shared RAM Config Register 1
    union   LSxACCPROT2_REG                  LSxACCPROT2;                  // Local Shared RAM Config Register 2
    Uint16                                   rsvd4[2];                     // Reserved
    union   LSxTEST_REG                      LSxTEST;                      // Local Shared RAM TEST Register
    union   LSxINIT_REG                      LSxINIT;                      // Local Shared RAM Init Register
    union   LSxINITDONE_REG                  LSxINITDONE;                  // Local Shared RAM InitDone Status Register
    union   LSxRAMTEST_LOCK_REG              LSxRAMTEST_LOCK;              // Lock register to LSx RAM TEST registers
    Uint16                                   rsvd5[8];                     // Reserved
    union   GSxLOCK_REG                      GSxLOCK;                      // Global Shared RAM Config Lock Register
    union   GSxCOMMIT_REG                    GSxCOMMIT;                    // Global Shared RAM Config Lock Commit Register
    union   GSxMSEL_REG                      GSxMSEL;                      // Global Shared RAM Controller Sel Register
    Uint16                                   rsvd6[2];                     // Reserved
    union   GSxACCPROT0_REG                  GSxACCPROT0;                  // Global Shared RAM Config Register 0
    union   GSxACCPROT1_REG                  GSxACCPROT1;                  // Global Shared RAM Config Register 1
    Uint16                                   rsvd7[4];                     // Reserved
    union   GSxTEST_REG                      GSxTEST;                      // Global Shared RAM TEST Register
    union   GSxINIT_REG                      GSxINIT;                      // Global Shared RAM Init Register
    union   GSxINITDONE_REG                  GSxINITDONE;                  // Global Shared RAM InitDone Status Register
    union   GSxRAMTEST_LOCK_REG              GSxRAMTEST_LOCK;              // Lock register to GSx RAM TEST registers
    Uint16                                   rsvd8[8];                     // Reserved
    union   MSGxLOCK_REG                     MSGxLOCK;                     // Message RAM Config Lock Register
    union   MSGxCOMMIT_REG                   MSGxCOMMIT;                   // Message RAM Config Lock Commit Register
    Uint16                                   rsvd9[4];                     // Reserved
    union   MSGxACCPROT0_REG                 MSGxACCPROT0;                 // Message RAM Access Protection Register 0
    Uint16                                   rsvd10[6];                    // Reserved
    union   MSGxTEST_REG                     MSGxTEST;                     // Message RAM TEST Register
    union   MSGxINIT_REG                     MSGxINIT;                     // Message RAM Init Register
    union   MSGxINITDONE_REG                 MSGxINITDONE;                 // Message RAM InitDone Status Register
    union   MSGxRAMTEST_LOCK_REG             MSGxRAMTEST_LOCK;             // Lock register for MSGx RAM TEST Register
    Uint16                                   rsvd11[40];                   // Reserved
    union   ROM_LOCK_REG                     ROM_LOCK;                     // ROM Config Lock Register
    union   ROM_TEST_REG                     ROM_TEST;                     // ROM  TEST Register
    union   ROM_FORCE_ERROR_REG              ROM_FORCE_ERROR;              // ROM Force Error register
    Uint16                                   rsvd12[4];                    // Reserved
    union   PERI_MEM_TEST_LOCK_REG           PERI_MEM_TEST_LOCK;           // Peripheral Memory Test Lock Register
    union   PERI_MEM_TEST_CONTROL_REG        PERI_MEM_TEST_CONTROL;        // Peripheral Memory Test control Register
};

struct EMIF1LOCK_BITS {                 // bits description
    Uint16 LOCK_EMIF1:1;                // 0 EMIF1 access protection and controller fields lock bit
    Uint16 rsvd1:15;                    // 15:1 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union EMIF1LOCK_REG {
    Uint32  all;
    struct  EMIF1LOCK_BITS  bit;
};

struct EMIF1COMMIT_BITS {               // bits description
    Uint16 COMMIT_EMIF1:1;              // 0 EMIF1 access protection and controller select permanent lock
    Uint16 rsvd1:15;                    // 15:1 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union EMIF1COMMIT_REG {
    Uint32  all;
    struct  EMIF1COMMIT_BITS  bit;
};

struct EMIF1MSEL_BITS {                 // bits description
    Uint16 MSEL_EMIF1:2;                // 1:0 Controller Select for EMIF1.
    Uint16 rsvd1:2;                     // 3:2 Reserved
    Uint32 KEY:28;                      // 31:4 KEY to enable the write into MSEL_EMIF1 bits
};

union EMIF1MSEL_REG {
    Uint32  all;
    struct  EMIF1MSEL_BITS  bit;
};

struct EMIF1ACCPROT0_BITS {             // bits description
    Uint16 FETCHPROT_EMIF1:1;           // 0 Fetch Protection For EMIF1
    Uint16 CPUWRPROT_EMIF1:1;           // 1 CPU WR Protection For EMIF1
    Uint16 DMAWRPROT_EMIF1:1;           // 2 DMA WR Protection For EMIF1
    Uint16 rsvd1:13;                    // 15:3 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union EMIF1ACCPROT0_REG {
    Uint32  all;
    struct  EMIF1ACCPROT0_BITS  bit;
};

struct EMIF1_CONFIG_REGS {
    union   EMIF1LOCK_REG                    EMIF1LOCK;                    // EMIF1 Config Lock Register
    union   EMIF1COMMIT_REG                  EMIF1COMMIT;                  // EMIF1 Config Lock Commit Register
    union   EMIF1MSEL_REG                    EMIF1MSEL;                    // EMIF1 Controller Sel Register
    Uint16                                   rsvd1[2];                     // Reserved
    union   EMIF1ACCPROT0_REG                EMIF1ACCPROT0;                // EMIF1 Config Register 0
};

struct NMAVFLG_BITS {                   // bits description
    Uint16 CPUREAD:1;                   // 0 Non Controller CPU Read Access Violation Flag
    Uint16 CPUWRITE:1;                  // 1 Non Controller CPU Write Access Violation Flag
    Uint16 CPUFETCH:1;                  // 2 Non Controller CPU Fetch Access Violation Flag
    Uint16 DMAWRITE:1;                  // 3 Non Controller DMA Write Access Violation Flag
    Uint16 CLA1READ:1;                  // 4 Non Controller CLA1 Read Access Violation Flag
    Uint16 CLA1WRITE:1;                 // 5 Non Controller CLA1 Write Access Violation Flag
    Uint16 CLA1FETCH:1;                 // 6 Non Controller CLA1 Fetch Access Violation Flag
    Uint16 rsvd1:1;                     // 7 Reserved
    Uint16 rsvd2:1;                     // 8 Reserved
    Uint16 rsvd3:1;                     // 9 Reserved
    Uint16 DMAREAD:1;                   // 10 Non Controller DMA Read Access Violation Flag
    Uint16 rsvd4:1;                     // 11 Reserved
    Uint16 rsvd5:1;                     // 12 Reserved
    Uint16 rsvd6:3;                     // 15:13 Reserved
    Uint16 rsvd7:16;                    // 31:16 Reserved
};

union NMAVFLG_REG {
    Uint32  all;
    struct  NMAVFLG_BITS  bit;
};

struct NMAVSET_BITS {                   // bits description
    Uint16 CPUREAD:1;                   // 0 Non Controller CPU Read Access Violation Flag Set
    Uint16 CPUWRITE:1;                  // 1 Non Controller CPU Write Access Violation Flag Set
    Uint16 CPUFETCH:1;                  // 2 Non Controller CPU Fetch Access Violation Flag Set
    Uint16 DMAWRITE:1;                  // 3 Non Controller DMA Write Access Violation Flag Set
    Uint16 CLA1READ:1;                  // 4 Non Controller CLA1 Read Access Violation Flag Set
    Uint16 CLA1WRITE:1;                 // 5 Non Controller CLA1 Write Access Violation Flag Set
    Uint16 CLA1FETCH:1;                 // 6 Non Controller CLA1 Fetch Access Violation Flag Set
    Uint16 rsvd1:1;                     // 7 Reserved
    Uint16 rsvd2:1;                     // 8 Reserved
    Uint16 rsvd3:1;                     // 9 Reserved
    Uint16 DMAREAD:1;                   // 10 Non Controller DMA Read Access Violation Flag Set
    Uint16 rsvd4:1;                     // 11 Reserved
    Uint16 rsvd5:1;                     // 12 Reserved
    Uint16 rsvd6:3;                     // 15:13 Reserved
    Uint16 rsvd7:16;                    // 31:16 Reserved
};

union NMAVSET_REG {
    Uint32  all;
    struct  NMAVSET_BITS  bit;
};

struct NMAVCLR_BITS {                   // bits description
    Uint16 CPUREAD:1;                   // 0 Non Controller CPU Read Access Violation Flag Clear
    Uint16 CPUWRITE:1;                  // 1 Non Controller CPU Write Access Violation Flag Clear
    Uint16 CPUFETCH:1;                  // 2 Non Controller CPU Fetch Access Violation Flag Clear
    Uint16 DMAWRITE:1;                  // 3 Non Controller DMA Write Access Violation Flag Clear
    Uint16 CLA1READ:1;                  // 4 Non Controller CLA1 Read Access Violation Flag Clear
    Uint16 CLA1WRITE:1;                 // 5 Non Controller CLA1 Write Access Violation Flag Clear
    Uint16 CLA1FETCH:1;                 // 6 Non Controller CLA1 Fetch Access Violation Flag Clear
    Uint16 rsvd1:1;                     // 7 Reserved
    Uint16 rsvd2:1;                     // 8 Reserved
    Uint16 rsvd3:1;                     // 9 Reserved
    Uint16 DMAREAD:1;                   // 10 Non Controller DMA Read Access Violation Flag Clear
    Uint16 rsvd4:1;                     // 11 Reserved
    Uint16 rsvd5:1;                     // 12 Reserved
    Uint16 rsvd6:3;                     // 15:13 Reserved
    Uint16 rsvd7:16;                    // 31:16 Reserved
};

union NMAVCLR_REG {
    Uint32  all;
    struct  NMAVCLR_BITS  bit;
};

struct NMAVINTEN_BITS {                 // bits description
    Uint16 CPUREAD:1;                   // 0 Non Controller CPU Read Access Violation Interrupt Enable
    Uint16 CPUWRITE:1;                  // 1 Non Controller CPU Write Access Violation Interrupt Enable
    Uint16 CPUFETCH:1;                  // 2 Non Controller CPU Fetch Access Violation Interrupt Enable
    Uint16 DMAWRITE:1;                  // 3 Non Controller DMA Write Access Violation Interrupt Enable
    Uint16 CLA1READ:1;                  // 4 Non Controller CLA1 Read Access Violation Interrupt Enable
    Uint16 CLA1WRITE:1;                 // 5 Non Controller CLA1 Write Access Violation Interrupt Enable
    Uint16 CLA1FETCH:1;                 // 6 Non Controller CLA1 Fetch Access Violation Interrupt Enable
    Uint16 rsvd1:1;                     // 7 Reserved
    Uint16 rsvd2:1;                     // 8 Reserved
    Uint16 rsvd3:1;                     // 9 Reserved
    Uint16 DMAREAD:1;                   // 10 Non Controller DMA Read Access Violation Interrupt Enable
    Uint16 rsvd4:1;                     // 11 Reserved
    Uint16 rsvd5:1;                     // 12 Reserved
    Uint16 rsvd6:3;                     // 15:13 Reserved
    Uint16 rsvd7:16;                    // 31:16 Reserved
};

union NMAVINTEN_REG {
    Uint32  all;
    struct  NMAVINTEN_BITS  bit;
};

struct MAVFLG_BITS {                    // bits description
    Uint16 CPUFETCH:1;                  // 0 Controller CPU Fetch Access Violation Flag
    Uint16 CPUWRITE:1;                  // 1 Controller CPU Write Access Violation Flag
    Uint16 DMAWRITE:1;                  // 2 Controller DMA Write Access Violation Flag
    Uint16 rsvd1:1;                     // 3 Reserved
    Uint16 rsvd2:12;                    // 15:4 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union MAVFLG_REG {
    Uint32  all;
    struct  MAVFLG_BITS  bit;
};

struct MAVSET_BITS {                    // bits description
    Uint16 CPUFETCH:1;                  // 0 Controller CPU Fetch Access Violation Flag Set
    Uint16 CPUWRITE:1;                  // 1 Controller CPU Write Access Violation Flag Set
    Uint16 DMAWRITE:1;                  // 2 Controller DMA Write Access Violation Flag Set
    Uint16 rsvd1:1;                     // 3 Reserved
    Uint16 rsvd2:12;                    // 15:4 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union MAVSET_REG {
    Uint32  all;
    struct  MAVSET_BITS  bit;
};

struct MAVCLR_BITS {                    // bits description
    Uint16 CPUFETCH:1;                  // 0 Controller CPU Fetch Access Violation Flag Clear
    Uint16 CPUWRITE:1;                  // 1 Controller CPU Write Access Violation Flag Clear
    Uint16 DMAWRITE:1;                  // 2 Controller DMA Write Access Violation Flag Clear
    Uint16 rsvd1:1;                     // 3 Reserved
    Uint16 rsvd2:12;                    // 15:4 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union MAVCLR_REG {
    Uint32  all;
    struct  MAVCLR_BITS  bit;
};

struct MAVINTEN_BITS {                  // bits description
    Uint16 CPUFETCH:1;                  // 0 Controller CPU Fetch Access Violation Interrupt Enable
    Uint16 CPUWRITE:1;                  // 1 Controller CPU Write Access Violation Interrupt Enable
    Uint16 DMAWRITE:1;                  // 2 Controller DMA Write Access Violation Interrupt Enable
    Uint16 rsvd1:1;                     // 3 Reserved
    Uint16 rsvd2:12;                    // 15:4 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union MAVINTEN_REG {
    Uint32  all;
    struct  MAVINTEN_BITS  bit;
};

struct ACCESS_PROTECTION_REGS {
    union   NMAVFLG_REG                      NMAVFLG;                      // Non-Controller Access Violation Flag Register
    union   NMAVSET_REG                      NMAVSET;                      // Non-Controller Access Violation Flag Set Register
    union   NMAVCLR_REG                      NMAVCLR;                      // Non-Controller Access Violation Flag Clear Register
    union   NMAVINTEN_REG                    NMAVINTEN;                    // Non-Controller Access Violation Interrupt Enable Register
    Uint32                                   NMCPURDAVADDR;                // Non-Controller CPU Read Access Violation Address
    Uint32                                   NMCPUWRAVADDR;                // Non-Controller CPU Write Access Violation Address
    Uint32                                   NMCPUFAVADDR;                 // Non-Controller CPU Fetch Access Violation Address
    Uint32                                   NMDMAWRAVADDR;                // Non-Controller DMA Write Access Violation Address
    Uint32                                   NMCLA1RDAVADDR;               // Non-Controller CLA1 Read Access Violation Address
    Uint32                                   NMCLA1WRAVADDR;               // Non-Controller CLA1 Write Access Violation Address
    Uint32                                   NMCLA1FAVADDR;                // Non-Controller CLA1 Fetch Access Violation Address
    Uint16                                   rsvd1[6];                     // Reserved
    Uint32                                   NMDMARDAVADDR;                // Non-Controller DMA Read Access Violation Address
    Uint16                                   rsvd2[2];                     // Reserved
    union   MAVFLG_REG                       MAVFLG;                       // Controller Access Violation Flag Register
    union   MAVSET_REG                       MAVSET;                       // Controller Access Violation Flag Set Register
    union   MAVCLR_REG                       MAVCLR;                       // Controller Access Violation Flag Clear Register
    union   MAVINTEN_REG                     MAVINTEN;                     // Controller Access Violation Interrupt Enable Register
    Uint32                                   MCPUFAVADDR;                  // Controller CPU Fetch Access Violation Address
    Uint32                                   MCPUWRAVADDR;                 // Controller CPU Write Access Violation Address
    Uint32                                   MDMAWRAVADDR;                 // Controller  DMA Write Access Violation Address
};

struct UCERRFLG_BITS {                  // bits description
    Uint16 CPURDERR:1;                  // 0 CPU Uncorrectable Read Error Flag
    Uint16 DMARDERR:1;                  // 1 DMA Uncorrectable Read Error Flag
    Uint16 CLA1RDERR:1;                 // 2 CLA1 Uncorrectable Read Error Flag
    Uint16 rsvd1:1;                     // 3 Reserved
    Uint16 rsvd2:1;                     // 4 Reserved
    Uint16 rsvd3:1;                     // 5 Reserved
    Uint16 rsvd4:10;                    // 15:6 Reserved
    Uint16 rsvd5:16;                    // 31:16 Reserved
};

union UCERRFLG_REG {
    Uint32  all;
    struct  UCERRFLG_BITS  bit;
};

struct UCERRSET_BITS {                  // bits description
    Uint16 CPURDERR:1;                  // 0 CPU Uncorrectable Read Error Flag Set
    Uint16 DMARDERR:1;                  // 1 DMA Uncorrectable Read Error Flag Set
    Uint16 CLA1RDERR:1;                 // 2 CLA1 Uncorrectable Read Error Flag Set
    Uint16 rsvd1:1;                     // 3 Reserved
    Uint16 rsvd2:1;                     // 4 Reserved
    Uint16 rsvd3:1;                     // 5 Reserved
    Uint16 rsvd4:10;                    // 15:6 Reserved
    Uint16 rsvd5:16;                    // 31:16 Reserved
};

union UCERRSET_REG {
    Uint32  all;
    struct  UCERRSET_BITS  bit;
};

struct UCERRCLR_BITS {                  // bits description
    Uint16 CPURDERR:1;                  // 0 CPU Uncorrectable Read Error Flag Clear
    Uint16 DMARDERR:1;                  // 1 DMA Uncorrectable Read Error Flag Clear
    Uint16 CLA1RDERR:1;                 // 2 CLA1 Uncorrectable Read Error Flag Clear
    Uint16 rsvd1:1;                     // 3 Reserved
    Uint16 rsvd2:1;                     // 4 Reserved
    Uint16 rsvd3:1;                     // 5 Reserved
    Uint16 rsvd4:10;                    // 15:6 Reserved
    Uint16 rsvd5:16;                    // 31:16 Reserved
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
    Uint16 DMARDERR:1;                  // 1 DMA Correctable Read Error Flag
    Uint16 CLA1RDERR:1;                 // 2 CLA1 Correctable Read Error Flag
    Uint16 rsvd1:1;                     // 3 Reserved
    Uint16 rsvd2:12;                    // 15:4 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union CERRFLG_REG {
    Uint32  all;
    struct  CERRFLG_BITS  bit;
};

struct CERRSET_BITS {                   // bits description
    Uint16 CPURDERR:1;                  // 0 CPU Correctable Read Error Flag Set
    Uint16 DMARDERR:1;                  // 1 DMA Correctable Read Error Flag Set
    Uint16 CLA1RDERR:1;                 // 2 CLA1 Correctable Read Error Flag Set
    Uint16 rsvd1:1;                     // 3 Reserved
    Uint16 rsvd2:12;                    // 15:4 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union CERRSET_REG {
    Uint32  all;
    struct  CERRSET_BITS  bit;
};

struct CERRCLR_BITS {                   // bits description
    Uint16 CPURDERR:1;                  // 0 CPU Correctable Read Error Flag Clear
    Uint16 DMARDERR:1;                  // 1 DMA Correctable Read Error Flag Clear
    Uint16 CLA1RDERR:1;                 // 2 CLA1 Correctable Read Error Flag Clear
    Uint16 rsvd1:1;                     // 3 Reserved
    Uint16 rsvd2:12;                    // 15:4 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
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
    Uint32                                   UCDMAREADDR;                  // Uncorrectable DMA Read Error Address
    Uint32                                   UCCLA1READDR;                 // Uncorrectable CLA1 Read Error Address
    Uint16                                   rsvd1[2];                     // Reserved
    Uint32                                   UCECATRAMADDR;                // Uncorrectable etherCAT RAM Read Error Address
    Uint16                                   rsvd2[12];                    // Reserved
    union   FLUCERRSTATUS_REG                FLUCERRSTATUS;                // Flash read uncorrectable ecc err status
    union   FLCERRSTATUS_REG                 FLCERRSTATUS;                 // Flash read correctable ecc err status
    union   CERRFLG_REG                      CERRFLG;                      // Correctable Error Flag Register
    union   CERRSET_REG                      CERRSET;                      // Correctable Error Flag Set Register
    union   CERRCLR_REG                      CERRCLR;                      // Correctable Error Flag Clear Register
    Uint32                                   CCPUREADDR;                   // Correctable CPU Read Error Address
    Uint32                                   CDMAREADDR;                   // Correctable DMA Read Error Address
    Uint32                                   CCLA1READDR;                  // Correctable CLA1 Read Error Address
    Uint16                                   rsvd3[2];                     // Reserved
    Uint32                                   CERRCNT;                      // Correctable Error Count Register
    union   CERRTHRES_REG                    CERRTHRES;                    // Correctable Error Threshold Value Register
    union   CEINTFLG_REG                     CEINTFLG;                     // Correctable Error Interrupt Flag Status Register
    union   CEINTCLR_REG                     CEINTCLR;                     // Correctable Error Interrupt Flag Clear Register
    union   CEINTSET_REG                     CEINTSET;                     // Correctable Error Interrupt Flag Set Register
    union   CEINTEN_REG                      CEINTEN;                      // Correctable Error Interrupt Enable Register
};

struct ROMWAITSTATE_BITS {              // bits description
    Uint16 WSDISABLE:1;                 // 0 ROM Wait State Enable/Disable Control
    Uint16 rsvd1:15;                    // 15:1 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union ROMWAITSTATE_REG {
    Uint32  all;
    struct  ROMWAITSTATE_BITS  bit;
};

struct ROM_WAIT_STATE_REGS {
    union   ROMWAITSTATE_REG                 ROMWAITSTATE;                 // ROM Wait State Configuration Register
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
#ifdef CPU1
extern volatile struct MEM_CFG_REGS MemCfgRegs;
extern volatile struct EMIF1_CONFIG_REGS Emif1ConfigRegs;
extern volatile struct ACCESS_PROTECTION_REGS AccessProtectionRegs;
extern volatile struct MEMORY_ERROR_REGS MemoryErrorRegs;
extern volatile struct ROM_WAIT_STATE_REGS RomWaitStateRegs;
extern volatile struct TEST_ERROR_REGS TestErrorRegs;
#endif
#ifdef CPU2
extern volatile struct MEM_CFG_REGS MemCfgRegs;
extern volatile struct EMIF1_CONFIG_REGS Emif1ConfigRegs;
extern volatile struct ACCESS_PROTECTION_REGS AccessProtectionRegs;
extern volatile struct MEMORY_ERROR_REGS MemoryErrorRegs;
extern volatile struct ROM_WAIT_STATE_REGS RomWaitStateRegs;
extern volatile struct TEST_ERROR_REGS TestErrorRegs;
#endif
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
