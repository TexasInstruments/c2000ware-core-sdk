//###########################################################################
//
// FILE:    f2838x_memconfig.h
//
// TITLE:   Definitions for the MEMCONFIG registers.
//
//###########################################################################
// 
// C2000Ware v5.05.00.00
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

#ifndef F2838X_MEMCONFIG_H
#define F2838X_MEMCONFIG_H

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
    Uint16 rsvd1:12;                    // 15:4 Reserved
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
    Uint16 rsvd1:12;                    // 15:4 Reserved
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

struct DxTEST_BITS {                    // bits description
    Uint16 TEST_M0:2;                   // 1:0 Selects the different modes for M0 RAM
    Uint16 TEST_M1:2;                   // 3:2 Selects the different modes for M1 RAM
    Uint16 TEST_D0:2;                   // 5:4 Selects the different modes for D0 RAM
    Uint16 TEST_D1:2;                   // 7:6 Selects the different modes for D1 RAM
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
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
    Uint16 rsvd1:12;                    // 15:4 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
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
    Uint16 rsvd1:12;                    // 15:4 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
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
    Uint16 rsvd1:12;                    // 15:4 Reserved
    Uint16 KEY:16;                      // 31:16 KEY field
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
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
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
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union LSxCOMMIT_REG {
    Uint32  all;
    struct  LSxCOMMIT_BITS  bit;
};

struct LSxMSEL_BITS {                   // bits description
    Uint16 MSEL_LS0:2;                  // 1:0 Master Select for LS0 RAM
    Uint16 MSEL_LS1:2;                  // 3:2 Master Select for LS1 RAM
    Uint16 MSEL_LS2:2;                  // 5:4 Master Select for LS2 RAM
    Uint16 MSEL_LS3:2;                  // 7:6 Master Select for LS3 RAM
    Uint16 MSEL_LS4:2;                  // 9:8 Master Select for LS4 RAM
    Uint16 MSEL_LS5:2;                  // 11:10 Master Select for LS5 RAM
    Uint16 MSEL_LS6:2;                  // 13:12 Master Select for LS6 RAM
    Uint16 MSEL_LS7:2;                  // 15:14 Master Select for LS7 RAM
    Uint16 rsvd1:16;                    // 31:16 Reserved
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
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
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

struct LSxTEST_BITS {                   // bits description
    Uint16 TEST_LS0:2;                  // 1:0 Selects the different modes for LS0 RAM
    Uint16 TEST_LS1:2;                  // 3:2 Selects the different modes for LS1 RAM
    Uint16 TEST_LS2:2;                  // 5:4 Selects the different modes for LS2 RAM
    Uint16 TEST_LS3:2;                  // 7:6 Selects the different modes for LS3 RAM
    Uint16 TEST_LS4:2;                  // 9:8 Selects the different modes for LS4 RAM
    Uint16 TEST_LS5:2;                  // 11:10 Selects the different modes for LS5 RAM
    Uint16 TEST_LS6:2;                  // 13:12 Selects the different modes for LS6 RAM
    Uint16 TEST_LS7:2;                  // 15:14 Selects the different modes for LS7 RAM
    Uint16 rsvd1:16;                    // 31:16 Reserved
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
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
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
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
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
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 KEY:16;                      // 31:16 KEY field
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
    Uint16 LOCK_GS5:1;                  // 5 GS5 RAM Lock bits
    Uint16 LOCK_GS6:1;                  // 6 GS6 RAM Lock bits
    Uint16 LOCK_GS7:1;                  // 7 GS7 RAM Lock bits
    Uint16 LOCK_GS8:1;                  // 8 GS8 RAM Lock bits
    Uint16 LOCK_GS9:1;                  // 9 GS9 RAM Lock bits
    Uint16 LOCK_GS10:1;                 // 10 GS10 RAM Lock bits
    Uint16 LOCK_GS11:1;                 // 11 GS11 RAM Lock bits
    Uint16 LOCK_GS12:1;                 // 12 GS12 RAM Lock bits
    Uint16 LOCK_GS13:1;                 // 13 GS13 RAM Lock bits
    Uint16 LOCK_GS14:1;                 // 14 GS14 RAM Lock bits
    Uint16 LOCK_GS15:1;                 // 15 GS15 RAM Lock bits
    Uint16 rsvd1:16;                    // 31:16 Reserved
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
    Uint16 COMMIT_GS5:1;                // 5 GS5 RAM Permanent Lock bits
    Uint16 COMMIT_GS6:1;                // 6 GS6 RAM Permanent Lock bits
    Uint16 COMMIT_GS7:1;                // 7 GS7 RAM Permanent Lock bits
    Uint16 COMMIT_GS8:1;                // 8 GS8 RAM Permanent Lock bits
    Uint16 COMMIT_GS9:1;                // 9 GS9 RAM Permanent Lock bits
    Uint16 COMMIT_GS10:1;               // 10 GS10 RAM Permanent Lock bits
    Uint16 COMMIT_GS11:1;               // 11 GS11 RAM Permanent Lock bits
    Uint16 COMMIT_GS12:1;               // 12 GS12 RAM Permanent Lock bits
    Uint16 COMMIT_GS13:1;               // 13 GS13 RAM Permanent Lock bits
    Uint16 COMMIT_GS14:1;               // 14 GS14 RAM Permanent Lock bits
    Uint16 COMMIT_GS15:1;               // 15 GS15 RAM Permanent Lock bits
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union GSxCOMMIT_REG {
    Uint32  all;
    struct  GSxCOMMIT_BITS  bit;
};

struct GSxMSEL_BITS {                   // bits description
    Uint16 MSEL_GS0:1;                  // 0 Master Select for GS0 RAM
    Uint16 MSEL_GS1:1;                  // 1 Master Select for GS1 RAM
    Uint16 MSEL_GS2:1;                  // 2 Master Select for GS2 RAM
    Uint16 MSEL_GS3:1;                  // 3 Master Select for GS3 RAM
    Uint16 MSEL_GS4:1;                  // 4 Master Select for GS4 RAM
    Uint16 MSEL_GS5:1;                  // 5 Master Select for GS5 RAM
    Uint16 MSEL_GS6:1;                  // 6 Master Select for GS6 RAM
    Uint16 MSEL_GS7:1;                  // 7 Master Select for GS7 RAM
    Uint16 MSEL_GS8:1;                  // 8 Master Select for GS8 RAM
    Uint16 MSEL_GS9:1;                  // 9 Master Select for GS9 RAM
    Uint16 MSEL_GS10:1;                 // 10 Master Select for GS10 RAM
    Uint16 MSEL_GS11:1;                 // 11 Master Select for GS11 RAM
    Uint16 MSEL_GS12:1;                 // 12 Master Select for GS12 RAM
    Uint16 MSEL_GS13:1;                 // 13 Master Select for GS13 RAM
    Uint16 MSEL_GS14:1;                 // 14 Master Select for GS14 RAM
    Uint16 MSEL_GS15:1;                 // 15 Master Select for GS15 RAM
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union GSxMSEL_REG {
    Uint32  all;
    struct  GSxMSEL_BITS  bit;
};

struct GSxACCPROT0_BITS {               // bits description
    Uint16 FETCHPROT_GS0:1;             // 0 Fetch Protection For GS0 RAM
    Uint16 CPUWRPROT_GS0:1;             // 1 CPU WR Protection For GS0 RAM
    Uint16 DMAWRPROT_GS0:1;             // 2 DMA WR Protection For GS0 RAM
    Uint16 rsvd1:5;                     // 7:3 Reserved
    Uint16 FETCHPROT_GS1:1;             // 8 Fetch Protection For GS1 RAM
    Uint16 CPUWRPROT_GS1:1;             // 9 CPU WR Protection For GS1 RAM
    Uint16 DMAWRPROT_GS1:1;             // 10 DMA WR Protection For GS1 RAM
    Uint16 rsvd2:5;                     // 15:11 Reserved
    Uint16 FETCHPROT_GS2:1;             // 16 Fetch Protection For GS2 RAM
    Uint16 CPUWRPROT_GS2:1;             // 17 CPU WR Protection For GS2 RAM
    Uint16 DMAWRPROT_GS2:1;             // 18 DMA WR Protection For GS2 RAM
    Uint16 rsvd3:5;                     // 23:19 Reserved
    Uint16 FETCHPROT_GS3:1;             // 24 Fetch Protection For GS3 RAM
    Uint16 CPUWRPROT_GS3:1;             // 25 CPU WR Protection For GS3 RAM
    Uint16 DMAWRPROT_GS3:1;             // 26 DMA WR Protection For GS3 RAM
    Uint16 rsvd4:5;                     // 31:27 Reserved
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
    Uint16 FETCHPROT_GS5:1;             // 8 Fetch Protection For GS5 RAM
    Uint16 CPUWRPROT_GS5:1;             // 9 CPU WR Protection For GS5 RAM
    Uint16 DMAWRPROT_GS5:1;             // 10 DMA WR Protection For GS5RAM
    Uint16 rsvd2:5;                     // 15:11 Reserved
    Uint16 FETCHPROT_GS6:1;             // 16 Fetch Protection For GS6 RAM
    Uint16 CPUWRPROT_GS6:1;             // 17 CPU WR Protection For GS6 RAM
    Uint16 DMAWRPROT_GS6:1;             // 18 DMA WR Protection For GS6RAM
    Uint16 rsvd3:5;                     // 23:19 Reserved
    Uint16 FETCHPROT_GS7:1;             // 24 Fetch Protection For GS7 RAM
    Uint16 CPUWRPROT_GS7:1;             // 25 CPU WR Protection For GS7 RAM
    Uint16 DMAWRPROT_GS7:1;             // 26 DMA WR Protection For GS7RAM
    Uint16 rsvd4:5;                     // 31:27 Reserved
};

union GSxACCPROT1_REG {
    Uint32  all;
    struct  GSxACCPROT1_BITS  bit;
};

struct GSxACCPROT2_BITS {               // bits description
    Uint16 FETCHPROT_GS8:1;             // 0 Fetch Protection For GS8 RAM
    Uint16 CPUWRPROT_GS8:1;             // 1 CPU WR Protection For GS8 RAM
    Uint16 DMAWRPROT_GS8:1;             // 2 DMA WR Protection For GS8 RAM
    Uint16 rsvd1:5;                     // 7:3 Reserved
    Uint16 FETCHPROT_GS9:1;             // 8 Fetch Protection For GS9 RAM
    Uint16 CPUWRPROT_GS9:1;             // 9 CPU WR Protection For GS9 RAM
    Uint16 DMAWRPROT_GS9:1;             // 10 DMA WR Protection For GS9RAM
    Uint16 rsvd2:5;                     // 15:11 Reserved
    Uint16 FETCHPROT_GS10:1;            // 16 Fetch Protection For GS10 RAM
    Uint16 CPUWRPROT_GS10:1;            // 17 CPU WR Protection For GS10 RAM
    Uint16 DMAWRPROT_GS10:1;            // 18 DMA WR Protection For GS10RAM
    Uint16 rsvd3:5;                     // 23:19 Reserved
    Uint16 FETCHPROT_GS11:1;            // 24 Fetch Protection For GS11 RAM
    Uint16 CPUWRPROT_GS11:1;            // 25 CPU WR Protection For GS11 RAM
    Uint16 DMAWRPROT_GS11:1;            // 26 DMA WR Protection For GS11RAM
    Uint16 rsvd4:5;                     // 31:27 Reserved
};

union GSxACCPROT2_REG {
    Uint32  all;
    struct  GSxACCPROT2_BITS  bit;
};

struct GSxACCPROT3_BITS {               // bits description
    Uint16 FETCHPROT_GS12:1;            // 0 Fetch Protection For GS12 RAM
    Uint16 CPUWRPROT_GS12:1;            // 1 CPU WR Protection For GS12 RAM
    Uint16 DMAWRPROT_GS12:1;            // 2 DMA WR Protection For GS12 RAM
    Uint16 rsvd1:5;                     // 7:3 Reserved
    Uint16 FETCHPROT_GS13:1;            // 8 Fetch Protection For GS13 RAM
    Uint16 CPUWRPROT_GS13:1;            // 9 CPU WR Protection For GS13 RAM
    Uint16 DMAWRPROT_GS13:1;            // 10 DMA WR Protection For GS13RAM
    Uint16 rsvd2:5;                     // 15:11 Reserved
    Uint16 FETCHPROT_GS14:1;            // 16 Fetch Protection For GS14 RAM
    Uint16 CPUWRPROT_GS14:1;            // 17 CPU WR Protection For GS14 RAM
    Uint16 DMAWRPROT_GS14:1;            // 18 DMA WR Protection For GS14RAM
    Uint16 rsvd3:5;                     // 23:19 Reserved
    Uint16 FETCHPROT_GS15:1;            // 24 Fetch Protection For GS15 RAM
    Uint16 CPUWRPROT_GS15:1;            // 25 CPU WR Protection For GS15 RAM
    Uint16 DMAWRPROT_GS15:1;            // 26 DMA WR Protection For GS15RAM
    Uint16 rsvd4:5;                     // 31:27 Reserved
};

union GSxACCPROT3_REG {
    Uint32  all;
    struct  GSxACCPROT3_BITS  bit;
};

struct GSxTEST_BITS {                   // bits description
    Uint16 TEST_GS0:2;                  // 1:0 Selects the different modes for GS0 RAM
    Uint16 TEST_GS1:2;                  // 3:2 Selects the different modes for GS1 RAM
    Uint16 TEST_GS2:2;                  // 5:4 Selects the different modes for GS2 RAM
    Uint16 TEST_GS3:2;                  // 7:6 Selects the different modes for GS3 RAM
    Uint16 TEST_GS4:2;                  // 9:8 Selects the different modes for GS4 RAM
    Uint16 TEST_GS5:2;                  // 11:10 Selects the different modes for GS5 RAM
    Uint16 TEST_GS6:2;                  // 13:12 Selects the different modes for GS6 RAM
    Uint16 TEST_GS7:2;                  // 15:14 Selects the different modes for GS7 RAM
    Uint16 TEST_GS8:2;                  // 17:16 Selects the different modes for GS8 RAM
    Uint16 TEST_GS9:2;                  // 19:18 Selects the different modes for GS9 RAM
    Uint16 TEST_GS10:2;                 // 21:20 Selects the different modes for GS10 RAM
    Uint16 TEST_GS11:2;                 // 23:22 Selects the different modes for GS11 RAM
    Uint16 TEST_GS12:2;                 // 25:24 Selects the different modes for GS12 RAM
    Uint16 TEST_GS13:2;                 // 27:26 Selects the different modes for GS13 RAM
    Uint16 TEST_GS14:2;                 // 29:28 Selects the different modes for GS14 RAM
    Uint16 TEST_GS15:2;                 // 31:30 Selects the different modes for GS15 RAM
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
    Uint16 INIT_GS5:1;                  // 5 RAM Initialization control for GS5 RAM.
    Uint16 INIT_GS6:1;                  // 6 RAM Initialization control for GS6 RAM.
    Uint16 INIT_GS7:1;                  // 7 RAM Initialization control for GS7 RAM.
    Uint16 INIT_GS8:1;                  // 8 RAM Initialization control for GS8 RAM.
    Uint16 INIT_GS9:1;                  // 9 RAM Initialization control for GS9 RAM.
    Uint16 INIT_GS10:1;                 // 10 RAM Initialization control for GS10 RAM.
    Uint16 INIT_GS11:1;                 // 11 RAM Initialization control for GS11 RAM.
    Uint16 INIT_GS12:1;                 // 12 RAM Initialization control for GS12 RAM.
    Uint16 INIT_GS13:1;                 // 13 RAM Initialization control for GS13 RAM.
    Uint16 INIT_GS14:1;                 // 14 RAM Initialization control for GS14 RAM.
    Uint16 INIT_GS15:1;                 // 15 RAM Initialization control for GS15 RAM.
    Uint16 rsvd1:16;                    // 31:16 Reserved
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
    Uint16 INITDONE_GS5:1;              // 5 RAM Initialization status for GS5 RAM.
    Uint16 INITDONE_GS6:1;              // 6 RAM Initialization status for GS6 RAM.
    Uint16 INITDONE_GS7:1;              // 7 RAM Initialization status for GS7 RAM.
    Uint16 INITDONE_GS8:1;              // 8 RAM Initialization status for GS8 RAM.
    Uint16 INITDONE_GS9:1;              // 9 RAM Initialization status for GS9 RAM.
    Uint16 INITDONE_GS10:1;             // 10 RAM Initialization status for GS10 RAM.
    Uint16 INITDONE_GS11:1;             // 11 RAM Initialization status for GS11 RAM.
    Uint16 INITDONE_GS12:1;             // 12 RAM Initialization status for GS12 RAM.
    Uint16 INITDONE_GS13:1;             // 13 RAM Initialization status for GS13 RAM.
    Uint16 INITDONE_GS14:1;             // 14 RAM Initialization status for GS14 RAM.
    Uint16 INITDONE_GS15:1;             // 15 RAM Initialization status for GS15 RAM.
    Uint16 rsvd1:16;                    // 31:16 Reserved
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
    Uint16 GS5:1;                       // 5 GSxTEST.TEST_GS5 LOCK
    Uint16 GS6:1;                       // 6 GSxTEST.TEST_GS6 LOCK
    Uint16 GS7:1;                       // 7 GSxTEST.TEST_GS7 LOCK
    Uint16 GS8:1;                       // 8 GSxTEST.TEST_GS8 LOCK
    Uint16 GS9:1;                       // 9 GSxTEST.TEST_GS9 LOCK
    Uint16 GS10:1;                      // 10 GSxTEST.TEST_GS10 LOCK
    Uint16 GS11:1;                      // 11 GSxTEST.TEST_GS11 LOCK
    Uint16 GS12:1;                      // 12 GSxTEST.TEST_GS12 LOCK
    Uint16 GS13:1;                      // 13 GSxTEST.TEST_GS13 LOCK
    Uint16 GS14:1;                      // 14 GSxTEST.TEST_GS14 LOCK
    Uint16 GS15:1;                      // 15 GSxTEST.TEST_GS15 LOCK
    Uint16 KEY:16;                      // 31:16 KEY field
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
    Uint16 LOCK_CPUTOCM_MSGRAM0:1;      // 8 Lock bit of CPU to CM MSG RAM0 control fields
    Uint16 LOCK_CPUTOCM_MSGRAM1:1;      // 9 Lock bit of CPU to CM MSG RAM1 control fields
    Uint16 LOCK_CLA2TODMA:1;            // 10 Lock bit of CLA to DMA MSG RAM control fields
    Uint16 LOCK_DMATOCLA2:1;            // 11 Lock bit of DMA to CLA MSG RAM control fields
    Uint16 rsvd3:4;                     // 15:12 Reserved
    Uint16 rsvd4:16;                    // 31:16 Reserved
};

union MSGxLOCK_REG {
    Uint32  all;
    struct  MSGxLOCK_BITS  bit;
};

struct MSGxCOMMIT_BITS {                // bits description
    Uint16 COMMIT_CPUTOCPU_MSGRAM0:1;   // 0 CPUTOCPU RAM control fields COMMIT bit
    Uint16 COMMIT_CPUTOCLA1:1;          // 1 CPUTOCLA1 RAM control fields COMMIT bit
    Uint16 COMMIT_CLA1TOCPU:1;          // 2 CLA1TOCPU RAM control fields COMMIT bit
    Uint16 rsvd1:1;                     // 3 Reserved
    Uint16 rsvd2:1;                     // 4 Reserved
    Uint16 COMMIT_CLA1TODMA:1;          // 5 CLA1TODMA RAM control fields COMMIT bit
    Uint16 COMMIT_DMATOCLA1:1;          // 6 DMATOCLA1 RAM control fields COMMIT bit
    Uint16 COMMIT_CPUTOCPU_MSGRAM1:1;   // 7 Commint bit of CPU to CPU MSG RAM1 control fields
    Uint16 COMMIT_CPUTOCM_MSGRAM0:1;    // 8 Commint bit of CPU to CM MSG RAM0 control fields
    Uint16 COMMIT_CPUTOCM_MSGRAM1:1;    // 9 Commint bit of CPU to CM MSG RAM1 control fields
    Uint16 COMMIT_CLATODMA_MSGRAM0:1;   // 10 Commint bit of CLA to DMA MSG RAM control fields
    Uint16 COMMIT_DMATOCLA_MSGRAM1:1;   // 11 Commint bit of DMA to CLA MSG RAM control fields
    Uint16 rsvd3:4;                     // 15:12 Reserved
    Uint16 rsvd4:16;                    // 31:16 Reserved
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

struct MSGxACCPROT1_BITS {              // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 rsvd2:1;                     // 1 Reserved
    Uint16 rsvd3:1;                     // 2 Reserved
    Uint16 rsvd4:5;                     // 7:3 Reserved
    Uint16 rsvd5:1;                     // 8 Reserved
    Uint16 rsvd6:1;                     // 9 Reserved
    Uint16 rsvd7:1;                     // 10 Reserved
    Uint16 rsvd8:5;                     // 15:11 Reserved
    Uint16 rsvd9:1;                     // 16 Reserved
    Uint16 rsvd10:1;                    // 17 Reserved
    Uint16 rsvd11:1;                    // 18 Reserved
    Uint16 rsvd12:5;                    // 23:19 Reserved
    Uint16 rsvd13:1;                    // 24 Reserved
    Uint16 CPUWRPROT_CPUTOCPU_MSGRAM1:1; // 25 CPU WR Protection For CPUTOCPU_MSGRAM1 RAM
    Uint16 DMAWRPROT_CPUTOCPU_MSGRAM1:1; // 26 DMA WR Protection For CPUTOCPU_MSGRAM1RAM
    Uint16 rsvd14:5;                    // 31:27 Reserved
};

union MSGxACCPROT1_REG {
    Uint32  all;
    struct  MSGxACCPROT1_BITS  bit;
};

struct MSGxACCPROT2_BITS {              // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 CPUWRPROT_CPUTOCM_MSGRAM0:1; // 1 CPU WR Protection For CPUTOCM_MSGRAM0 RAM
    Uint16 DMAWRPROT_CPUTOCM_MSGRAM0:1; // 2 DMA WR Protection For CPUTOCM_MSGRAM0 RAM
    Uint16 rsvd2:5;                     // 7:3 Reserved
    Uint16 rsvd3:1;                     // 8 Reserved
    Uint16 CPUWRPROT_CPUTOCM_MSGRAM1:1; // 9 CPU WR Protection For CPUTOCM_MSGRAM1 RAM
    Uint16 DMAWRPROT_CPUTOCM_MSGRAM1:1; // 10 DMA WR Protection For CPUTOCM_MSGRAM1RAM
    Uint16 rsvd4:5;                     // 15:11 Reserved
    Uint16 rsvd5:1;                     // 16 Reserved
    Uint16 rsvd6:1;                     // 17 Reserved
    Uint16 rsvd7:1;                     // 18 Reserved
    Uint16 rsvd8:5;                     // 23:19 Reserved
    Uint16 rsvd9:1;                     // 24 Reserved
    Uint16 rsvd10:1;                    // 25 Reserved
    Uint16 rsvd11:1;                    // 26 Reserved
    Uint16 rsvd12:5;                    // 31:27 Reserved
};

union MSGxACCPROT2_REG {
    Uint32  all;
    struct  MSGxACCPROT2_BITS  bit;
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
    Uint16 TEST_CPUTOCM_MSGRAM0:2;      // 17:16 CPU to CM Mode Select
    Uint16 TEST_CPUTOCM_MSGRAM1:2;      // 19:18 CPU to CM Mode Select
    Uint16 rsvd3:2;                     // 21:20 Reserved
    Uint16 rsvd4:2;                     // 23:22 Reserved
    Uint16 rsvd5:8;                     // 31:24 Reserved
};

union MSGxTEST_REG {
    Uint32  all;
    struct  MSGxTEST_BITS  bit;
};

struct MSGxINIT_BITS {                  // bits description
    Uint16 INIT_CPUTOCPU_MSGRAM0:1;     // 0 Initialization control for CPU to CPU MSG RAM0
    Uint16 INIT_CPUTOCLA1:1;            // 1 Initialization control for CPUTOCLA1 MSG RAM
    Uint16 INIT_CLA1TOCPU:1;            // 2 Initialization control for CLA1TOCPU MSG RAM
    Uint16 rsvd1:1;                     // 3 Reserved
    Uint16 rsvd2:1;                     // 4 Reserved
    Uint16 INIT_CLA1TODMA:1;            // 5 Initialization control for CLA1 to DMA MSG RAM
    Uint16 INIT_DMATOCLA1:1;            // 6 Initialization control for DMA to CLA1 MSG RAM
    Uint16 INIT_CPUTOCPU_MSGRAM1:1;     // 7 Initialization control for CPU to CPU MSG RAM1
    Uint16 INIT_CPUTOCM_MSGRAM0:1;      // 8 Initialization control for CPU to CM MSG RAM0
    Uint16 INIT_CPUTOCM_MSGRAM1:1;      // 9 Initialization control for CPU to CM MSG RAM1
    Uint16 rsvd3:1;                     // 10 Reserved
    Uint16 rsvd4:1;                     // 11 Reserved
    Uint16 rsvd5:4;                     // 15:12 Reserved
    Uint16 rsvd6:16;                    // 31:16 Reserved
};

union MSGxINIT_REG {
    Uint32  all;
    struct  MSGxINIT_BITS  bit;
};

struct MSGxINITDONE_BITS {              // bits description
    Uint16 INITDONE_CPUTOCPU_MSGRAM0:1; // 0 Initialization status for CPU to CPU MSG RAM
    Uint16 INITDONE_CPUTOCLA1:1;        // 1 Initialization status for CPU to CLA1 MSG RAM
    Uint16 INITDONE_CLA1TOCPU:1;        // 2 Initialization status for CLA1 to CPU MSG RAM
    Uint16 rsvd1:1;                     // 3 Reserved
    Uint16 rsvd2:1;                     // 4 Reserved
    Uint16 INITDONE_CLA1TODMA:1;        // 5 Initialization status for CLA1 to DMA MSG RAM
    Uint16 INITDONE_DMATOCLA1:1;        // 6 Initialization status for DMA to CLA1 MSG RAM
    Uint16 INITDONE_CPUTOCPU_MSGRAM1:1; // 7 Initialization status for CPU to CPU MSG RAM1
    Uint16 INITDONE_CPUTOCM_MSGRAM0:1;  // 8 Initialization status for CPU to CM MSG RAM0
    Uint16 INITDONE_CPUTOCM_MSGRAM1:1;  // 9 Initialization status for CPU to CM MSG RAM1
    Uint16 rsvd3:1;                     // 10 Reserved
    Uint16 rsvd4:1;                     // 11 Reserved
    Uint16 rsvd5:4;                     // 15:12 Reserved
    Uint16 rsvd6:16;                    // 31:16 Reserved
};

union MSGxINITDONE_REG {
    Uint32  all;
    struct  MSGxINITDONE_BITS  bit;
};

struct MSGxRAMTEST_LOCK_BITS {          // bits description
    Uint16 CPUTOCPU_MSGRAM0:1;          // 0 MSGxTEST.TEST_CPUTOCPU_MSGRAM0 LOCK
    Uint16 CPUTOCLA1:1;                 // 1 MSGxTEST.TEST_CPUTOCLA1 LOCK
    Uint16 CLA1TOCPU:1;                 // 2 MSGxTEST.TEST_CLA1TOCPU LOCK
    Uint16 CPUTOCLA2:1;                 // 3 MSGxTEST.TEST_CPUTOCLA2 LOCK
    Uint16 CLA2TOCPU:1;                 // 4 MSGxTEST.TEST_CLA2TOCPU LOCK
    Uint16 CLA1TODMA:1;                 // 5 MSGxTEST.TEST_CLA1TODMA LOCK
    Uint16 DMATOCLA1:1;                 // 6 MSGxTEST.TEST_DMATOCLA1 LOCK
    Uint16 CPUTOCPU_MSGRAM1:1;          // 7 MSGxTEST.TEST_CPUTOCPU_MSGRAM1 LOCK
    Uint16 CPUTOCM_MSGRAM0:1;           // 8 MSGxTEST.TEST_CPUTOCM_MSGRAM0 LOCK
    Uint16 CPUTOCM_MSGRAM1:1;           // 9 MSGxTEST.TEST_CPUTOCM_MSGRAM1 LOCK
    Uint16 CLA2TODMA:1;                 // 10 MSGxTEST.TEST_CLA2TODMA LOCK
    Uint16 DMATOCLA2:1;                 // 11 MSGxTEST.TEST_DMATOCLA2 LOCK
    Uint16 rsvd1:4;                     // 15:12 Reserved
    Uint16 KEY:16;                      // 31:16 KEY field
};

union MSGxRAMTEST_LOCK_REG {
    Uint32  all;
    struct  MSGxRAMTEST_LOCK_BITS  bit;
};

struct ROM_LOCK_BITS {                  // bits description
    Uint16 LOCK_BOOTROM:1;              // 0 BOOTROM Lock bits
    Uint16 LOCK_SECUREROM:1;            // 1 SECUREROM Lock bits
    Uint16 LOCK_CLADATAROM:1;           // 2 CLADATAROM Lock bits
    Uint16 rsvd1:13;                    // 15:3 Reserved
    Uint16 KEY:16;                      // 31:16 KEY field
};

union ROM_LOCK_REG {
    Uint32  all;
    struct  ROM_LOCK_BITS  bit;
};

struct ROM_TEST_BITS {                  // bits description
    Uint16 TEST_BOOTROM:2;              // 1:0 Selects the different modes for BOOTROM
    Uint16 TEST_SECUREROM:2;            // 3:2 Selects the different modes for SECUREROM
    Uint16 TEST_CLADATAROM:2;           // 5:4 Selects the different modes for CLADATAROM
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union ROM_TEST_REG {
    Uint32  all;
    struct  ROM_TEST_BITS  bit;
};

struct ROM_FORCE_ERROR_BITS {           // bits description
    Uint16 FORCE_BOOTROM_ERROR:1;       // 0 Force Bootrom Parity Error
    Uint16 FORCE_SECUREROM_ERROR:1;     // 1 Force SECUREROM Parity Error
    Uint16 FORCE_CLADATAROM_ERROR:1;    // 2 Force CLADATAROM Parity Error
    Uint16 rsvd1:13;                    // 15:3 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union ROM_FORCE_ERROR_REG {
    Uint32  all;
    struct  ROM_FORCE_ERROR_BITS  bit;
};

struct PERI_MEM_TEST_LOCK_BITS {        // bits description
    Uint16 LOCK_PERI_MEM_TEST_CONTROL:1; // 0 PERI_MEM_TEST_CONTROL Lock bit
    Uint16 rsvd1:15;                    // 15:1 Reserved
    Uint16 KEY:16;                      // 31:16 KEY field
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
    Uint16                                   rsvd2[6];                     // Reserved
    union   DxTEST_REG                       DxTEST;                       // Dedicated RAM TEST Register
    union   DxINIT_REG                       DxINIT;                       // Dedicated RAM Init Register
    union   DxINITDONE_REG                   DxINITDONE;                   // Dedicated RAM InitDone Status Register
    union   DxRAMTEST_LOCK_REG               DxRAMTEST_LOCK;               // Lock register to Dx RAM TEST registers
    Uint16                                   rsvd3[8];                     // Reserved
    union   LSxLOCK_REG                      LSxLOCK;                      // Local Shared RAM Config Lock Register
    union   LSxCOMMIT_REG                    LSxCOMMIT;                    // Local Shared RAM Config Lock Commit Register
    union   LSxMSEL_REG                      LSxMSEL;                      // Local Shared RAM Master Sel Register
    union   LSxCLAPGM_REG                    LSxCLAPGM;                    // Local Shared RAM Prog/Exe control Register
    union   LSxACCPROT0_REG                  LSxACCPROT0;                  // Local Shared RAM Config Register 0
    union   LSxACCPROT1_REG                  LSxACCPROT1;                  // Local Shared RAM Config Register 1
    Uint16                                   rsvd4[4];                     // Reserved
    union   LSxTEST_REG                      LSxTEST;                      // Local Shared RAM TEST Register
    union   LSxINIT_REG                      LSxINIT;                      // Local Shared RAM Init Register
    union   LSxINITDONE_REG                  LSxINITDONE;                  // Local Shared RAM InitDone Status Register
    union   LSxRAMTEST_LOCK_REG              LSxRAMTEST_LOCK;              // Lock register to LSx RAM TEST registers
    Uint16                                   rsvd5[8];                     // Reserved
    union   GSxLOCK_REG                      GSxLOCK;                      // Global Shared RAM Config Lock Register
    union   GSxCOMMIT_REG                    GSxCOMMIT;                    // Global Shared RAM Config Lock Commit Register
    union   GSxMSEL_REG                      GSxMSEL;                      // Global Shared RAM Master Sel Register
    Uint16                                   rsvd6[2];                     // Reserved
    union   GSxACCPROT0_REG                  GSxACCPROT0;                  // Global Shared RAM Access Protection Register 0
    union   GSxACCPROT1_REG                  GSxACCPROT1;                  // Global Shared RAM Access Protection Register 1
    union   GSxACCPROT2_REG                  GSxACCPROT2;                  // Global Shared RAM Access Protection Register 2
    union   GSxACCPROT3_REG                  GSxACCPROT3;                  // Global Shared RAM Access Protection Register 3
    union   GSxTEST_REG                      GSxTEST;                      // Global Shared RAM TEST Register
    union   GSxINIT_REG                      GSxINIT;                      // Global Shared RAM Init Register
    union   GSxINITDONE_REG                  GSxINITDONE;                  // Global Shared RAM InitDone Status Register
    union   GSxRAMTEST_LOCK_REG              GSxRAMTEST_LOCK;              // Lock register to GSx RAM TEST registers
    Uint16                                   rsvd7[8];                     // Reserved
    union   MSGxLOCK_REG                     MSGxLOCK;                     // Message RAM Config Lock Register
    union   MSGxCOMMIT_REG                   MSGxCOMMIT;                   // Message RAM Config Lock Commit Register
    Uint16                                   rsvd8[4];                     // Reserved
    union   MSGxACCPROT0_REG                 MSGxACCPROT0;                 // Message RAM Access Protection Register 0
    union   MSGxACCPROT1_REG                 MSGxACCPROT1;                 // Message RAM Access Protection Register 1
    union   MSGxACCPROT2_REG                 MSGxACCPROT2;                 // Message RAM Access Protection Register 2
    Uint16                                   rsvd9[2];                     // Reserved
    union   MSGxTEST_REG                     MSGxTEST;                     // Message RAM TEST Register
    union   MSGxINIT_REG                     MSGxINIT;                     // Message RAM Init Register
    union   MSGxINITDONE_REG                 MSGxINITDONE;                 // Message RAM InitDone Status Register
    union   MSGxRAMTEST_LOCK_REG             MSGxRAMTEST_LOCK;             // Lock register to MSGx RAM TEST registers
    Uint16                                   rsvd10[40];                   // Reserved
    union   ROM_LOCK_REG                     ROM_LOCK;                     // ROM Config Lock Register
    union   ROM_TEST_REG                     ROM_TEST;                     // ROM  TEST Register
    union   ROM_FORCE_ERROR_REG              ROM_FORCE_ERROR;              // ROM Force Error register
    Uint16                                   rsvd11[4];                    // Reserved
    union   PERI_MEM_TEST_LOCK_REG           PERI_MEM_TEST_LOCK;           // Peripheral Memory Test Lock Register
    union   PERI_MEM_TEST_CONTROL_REG        PERI_MEM_TEST_CONTROL;        // Peripheral Memory Test control Register
};

struct EMIF1LOCK_BITS {                 // bits description
    Uint16 LOCK_EMIF1:1;                // 0 EMIF1 access protection and master select fields lock bit
    Uint16 rsvd1:15;                    // 15:1 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union EMIF1LOCK_REG {
    Uint32  all;
    struct  EMIF1LOCK_BITS  bit;
};

struct EMIF1COMMIT_BITS {               // bits description
    Uint16 COMMIT_EMIF1:1;              // 0 EMIF1 access protection and master select permanent lock
    Uint16 rsvd1:15;                    // 15:1 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union EMIF1COMMIT_REG {
    Uint32  all;
    struct  EMIF1COMMIT_BITS  bit;
};

struct EMIF1MSEL_BITS {                 // bits description
    Uint16 MSEL_EMIF1:2;                // 1:0 Master Select for EMIF1.
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
    union   EMIF1MSEL_REG                    EMIF1MSEL;                    // EMIF1 Master Sel Register
    Uint16                                   rsvd1[2];                     // Reserved
    union   EMIF1ACCPROT0_REG                EMIF1ACCPROT0;                // EMIF1 Config Register 0
};

struct EMIF2LOCK_BITS {                 // bits description
    Uint16 LOCK_EMIF2:1;                // 0 EMIF2 access protection and master select permanent lock
    Uint16 rsvd1:15;                    // 15:1 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union EMIF2LOCK_REG {
    Uint32  all;
    struct  EMIF2LOCK_BITS  bit;
};

struct EMIF2COMMIT_BITS {               // bits description
    Uint16 COMMIT_EMIF2:1;              // 0 EMIF2 access protection and master select permanent lock
    Uint16 rsvd1:15;                    // 15:1 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union EMIF2COMMIT_REG {
    Uint32  all;
    struct  EMIF2COMMIT_BITS  bit;
};

struct EMIF2ACCPROT0_BITS {             // bits description
    Uint16 FETCHPROT_EMIF2:1;           // 0 Fetch Protection For EMIF2
    Uint16 CPUWRPROT_EMIF2:1;           // 1 CPU WR Protection For EMIF2
    Uint16 rsvd1:14;                    // 15:2 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union EMIF2ACCPROT0_REG {
    Uint32  all;
    struct  EMIF2ACCPROT0_BITS  bit;
};

struct EMIF2_CONFIG_REGS {
    union   EMIF2LOCK_REG                    EMIF2LOCK;                    // EMIF2 Config Lock Register
    union   EMIF2COMMIT_REG                  EMIF2COMMIT;                  // EMIF2 Config Lock Commit Register
    Uint16                                   rsvd1[4];                     // Reserved
    union   EMIF2ACCPROT0_REG                EMIF2ACCPROT0;                // EMIF2 Config Register 0
};

struct NMAVFLG_BITS {                   // bits description
    Uint16 CPUREAD:1;                   // 0 Non Master CPU Read Access Violation Flag
    Uint16 CPUWRITE:1;                  // 1 Non Master CPU Write Access Violation Flag
    Uint16 CPUFETCH:1;                  // 2 Non Master CPU Fetch Access Violation Flag
    Uint16 DMAWRITE:1;                  // 3 Non Master DMA Write Access Violation Flag
    Uint16 CLA1READ:1;                  // 4 Non Master CLA1 Read Access Violation Flag
    Uint16 CLA1WRITE:1;                 // 5 Non Master CLA1 Write Access Violation Flag
    Uint16 CLA1FETCH:1;                 // 6 Non Master CLA1 Fetch Access Violation Flag
    Uint16 rsvd1:1;                     // 7 Reserved
    Uint16 rsvd2:1;                     // 8 Reserved
    Uint16 rsvd3:1;                     // 9 Reserved
    Uint16 DMAREAD:1;                   // 10 Non Master DMA read Access Violation Flag
    Uint16 rsvd4:5;                     // 15:11 Reserved
    Uint16 rsvd5:16;                    // 31:16 Reserved
};

union NMAVFLG_REG {
    Uint32  all;
    struct  NMAVFLG_BITS  bit;
};

struct NMAVSET_BITS {                   // bits description
    Uint16 CPUREAD:1;                   // 0 Non Master CPU Read Access Violation Flag Set
    Uint16 CPUWRITE:1;                  // 1 Non Master CPU Write Access Violation Flag Set
    Uint16 CPUFETCH:1;                  // 2 Non Master CPU Fetch Access Violation Flag Set
    Uint16 DMAWRITE:1;                  // 3 Non Master DMA Write Access Violation Flag Set
    Uint16 CLA1READ:1;                  // 4 Non Master CLA1 Read Access Violation Flag Set
    Uint16 CLA1WRITE:1;                 // 5 Non Master CLA1 Write Access Violation Flag Set
    Uint16 CLA1FETCH:1;                 // 6 Non Master CLA1 Fetch Access Violation Flag Set
    Uint16 rsvd1:1;                     // 7 Reserved
    Uint16 rsvd2:1;                     // 8 Reserved
    Uint16 rsvd3:1;                     // 9 Reserved
    Uint16 DMAREAD:1;                   // 10 Non Master DMA read Access Violation Flag Set
    Uint16 rsvd4:5;                     // 15:11 Reserved
    Uint16 rsvd5:16;                    // 31:16 Reserved
};

union NMAVSET_REG {
    Uint32  all;
    struct  NMAVSET_BITS  bit;
};

struct NMAVCLR_BITS {                   // bits description
    Uint16 CPUREAD:1;                   // 0 Non Master CPU Read Access Violation Flag Clear
    Uint16 CPUWRITE:1;                  // 1 Non Master CPU Write Access Violation Flag Clear
    Uint16 CPUFETCH:1;                  // 2 Non Master CPU Fetch Access Violation Flag Clear
    Uint16 DMAWRITE:1;                  // 3 Non Master DMA Write Access Violation Flag Clear
    Uint16 CLA1READ:1;                  // 4 Non Master CLA1 Read Access Violation Flag Clear
    Uint16 CLA1WRITE:1;                 // 5 Non Master CLA1 Write Access Violation Flag Clear
    Uint16 CLA1FETCH:1;                 // 6 Non Master CLA1 Fetch Access Violation Flag Clear
    Uint16 rsvd1:1;                     // 7 Reserved
    Uint16 rsvd2:1;                     // 8 Reserved
    Uint16 rsvd3:1;                     // 9 Reserved
    Uint16 DMAREAD:1;                   // 10 Non Master DMA read Access Violation Flag Clear
    Uint16 rsvd4:5;                     // 15:11 Reserved
    Uint16 rsvd5:16;                    // 31:16 Reserved
};

union NMAVCLR_REG {
    Uint32  all;
    struct  NMAVCLR_BITS  bit;
};

struct NMAVINTEN_BITS {                 // bits description
    Uint16 CPUREAD:1;                   // 0 Non Master CPU Read Access Violation Interrupt Enable
    Uint16 CPUWRITE:1;                  // 1 Non Master CPU Write Access Violation Interrupt Enable
    Uint16 CPUFETCH:1;                  // 2 Non Master CPU Fetch Access Violation Interrupt Enable
    Uint16 DMAWRITE:1;                  // 3 Non Master DMA Write Access Violation Interrupt Enable
    Uint16 CLA1READ:1;                  // 4 Non Master CLA1 Read Access Violation Interrupt Enable
    Uint16 CLA1WRITE:1;                 // 5 Non Master CLA1 Write Access Violation Interrupt Enable
    Uint16 CLA1FETCH:1;                 // 6 Non Master CLA1 Fetch Access Violation Interrupt Enable
    Uint16 rsvd1:1;                     // 7 Reserved
    Uint16 rsvd2:1;                     // 8 Reserved
    Uint16 rsvd3:1;                     // 9 Reserved
    Uint16 DMAREAD:1;                   // 10 Non Master DMA Read Access Violation Interrupt Enable
    Uint16 rsvd4:5;                     // 15:11 Reserved
    Uint16 rsvd5:16;                    // 31:16 Reserved
};

union NMAVINTEN_REG {
    Uint32  all;
    struct  NMAVINTEN_BITS  bit;
};

struct MAVFLG_BITS {                    // bits description
    Uint16 CPUFETCH:1;                  // 0 Master CPU Fetch Access Violation Flag
    Uint16 CPUWRITE:1;                  // 1 Master CPU Write Access Violation Flag
    Uint16 DMAWRITE:1;                  // 2 Master DMA Write Access Violation Flag
    Uint16 rsvd1:13;                    // 15:3 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union MAVFLG_REG {
    Uint32  all;
    struct  MAVFLG_BITS  bit;
};

struct MAVSET_BITS {                    // bits description
    Uint16 CPUFETCH:1;                  // 0 Master CPU Fetch Access Violation Flag Set
    Uint16 CPUWRITE:1;                  // 1 Master CPU Write Access Violation Flag Set
    Uint16 DMAWRITE:1;                  // 2 Master DMA Write Access Violation Flag Set
    Uint16 rsvd1:13;                    // 15:3 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union MAVSET_REG {
    Uint32  all;
    struct  MAVSET_BITS  bit;
};

struct MAVCLR_BITS {                    // bits description
    Uint16 CPUFETCH:1;                  // 0 Master CPU Fetch Access Violation Flag Clear
    Uint16 CPUWRITE:1;                  // 1 Master CPU Write Access Violation Flag Clear
    Uint16 DMAWRITE:1;                  // 2 Master DMA Write Access Violation Flag Clear
    Uint16 rsvd1:13;                    // 15:3 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union MAVCLR_REG {
    Uint32  all;
    struct  MAVCLR_BITS  bit;
};

struct MAVINTEN_BITS {                  // bits description
    Uint16 CPUFETCH:1;                  // 0 Master CPU Fetch Access Violation Interrupt Enable
    Uint16 CPUWRITE:1;                  // 1 Master CPU Write Access Violation Interrupt Enable
    Uint16 DMAWRITE:1;                  // 2 Master DMA Write Access Violation Interrupt Enable
    Uint16 rsvd1:13;                    // 15:3 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union MAVINTEN_REG {
    Uint32  all;
    struct  MAVINTEN_BITS  bit;
};

struct ACCESS_PROTECTION_REGS {
    union   NMAVFLG_REG                      NMAVFLG;                      // Non-Master Access Violation Flag Register
    union   NMAVSET_REG                      NMAVSET;                      // Non-Master Access Violation Flag Set Register
    union   NMAVCLR_REG                      NMAVCLR;                      // Non-Master Access Violation Flag Clear Register
    union   NMAVINTEN_REG                    NMAVINTEN;                    // Non-Master Access Violation Interrupt Enable Register
    Uint32                                   NMCPURDAVADDR;                // Non-Master CPU Read Access Violation Address
    Uint32                                   NMCPUWRAVADDR;                // Non-Master CPU Write Access Violation Address
    Uint32                                   NMCPUFAVADDR;                 // Non-Master CPU Fetch Access Violation Address
    Uint32                                   NMDMAWRAVADDR;                // Non-Master DMA Write Access Violation Address
    Uint32                                   NMCLA1RDAVADDR;               // Non-Master CLA1 Read Access Violation Address
    Uint32                                   NMCLA1WRAVADDR;               // Non-Master CLA1 Write Access Violation Address
    Uint32                                   NMCLA1FAVADDR;                // Non-Master CLA1 Fetch Access Violation Address
    Uint16                                   rsvd1[6];                     // Reserved
    Uint32                                   NMDMARDAVADDR;                // Non-Master DMA Read Access Violation Address
    Uint16                                   rsvd2[2];                     // Reserved
    union   MAVFLG_REG                       MAVFLG;                       // Master Access Violation Flag Register
    union   MAVSET_REG                       MAVSET;                       // Master Access Violation Flag Set Register
    union   MAVCLR_REG                       MAVCLR;                       // Master Access Violation Flag Clear Register
    union   MAVINTEN_REG                     MAVINTEN;                     // Master Access Violation Interrupt Enable Register
    Uint32                                   MCPUFAVADDR;                  // Master CPU Fetch Access Violation Address
    Uint32                                   MCPUWRAVADDR;                 // Master CPU Write Access Violation Address
    Uint32                                   MDMAWRAVADDR;                 // Master  DMA Write Access Violation Address
};

struct UCERRFLG_BITS {                  // bits description
    Uint16 CPURDERR:1;                  // 0 CPU Uncorrectable Read Error Flag
    Uint16 DMARDERR:1;                  // 1 DMA Uncorrectable Read Error Flag
    Uint16 CLA1RDERR:1;                 // 2 CLA1 Uncorrectable Read Error Flag
    Uint16 rsvd1:1;                     // 3 Reserved
    Uint16 ECATRAMRDERR:1;              // 4 ECAT RAM Read Error Flag
    Uint16 rsvd2:11;                    // 15:5 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
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
    Uint16 ECATRAMRDERR:1;              // 4 ECAT RAM Read Error Flag Set
    Uint16 rsvd2:11;                    // 15:5 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
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
    Uint16 ECATRAMRDERR:1;              // 4 ECAT RAM Read Error Flag Clear
    Uint16 rsvd2:11;                    // 15:5 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union UCERRCLR_REG {
    Uint32  all;
    struct  UCERRCLR_BITS  bit;
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

struct CERRCNT_BITS {                   // bits description
    Uint16 CERRCNT:16;                  // 15:0 Correctable error count.
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union CERRCNT_REG {
    Uint32  all;
    struct  CERRCNT_BITS  bit;
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
    Uint16 CEINTEN:1;                   // 0 CPU/DMA/CLA Correctable Error Interrupt Enable.
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
    Uint16                                   rsvd2[16];                    // Reserved
    union   CERRFLG_REG                      CERRFLG;                      // Correctable Error Flag Register
    union   CERRSET_REG                      CERRSET;                      // Correctable Error Flag Set Register
    union   CERRCLR_REG                      CERRCLR;                      // Correctable Error Flag Clear Register
    Uint32                                   CCPUREADDR;                   // Correctable CPU Read Error Address
    Uint16                                   rsvd3[2];                     // Reserved
    Uint32                                   CCLA1READDR;                  // Correctable CLA1 Read Error Address
    Uint16                                   rsvd4[2];                     // Reserved
    union   CERRCNT_REG                      CERRCNT;                      // Correctable Error Count Register
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

struct ROMPREFETCH_BITS {               // bits description
    Uint16 PFENABLE:1;                  // 0 ROM Prefetch Enable/Disable Control
    Uint16 rsvd1:15;                    // 15:1 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union ROMPREFETCH_REG {
    Uint32  all;
    struct  ROMPREFETCH_BITS  bit;
};

struct ROM_PREFETCH_REGS {
    union   ROMPREFETCH_REG                  ROMPREFETCH;                  // ROM Prefetch Configuration Register
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
extern volatile struct ACCESS_PROTECTION_REGS AccessProtectionRegs;
extern volatile struct MEMORY_ERROR_REGS MemoryErrorRegs;
extern volatile struct ROM_WAIT_STATE_REGS RomWaitStateRegs;
extern volatile struct ROM_PREFETCH_REGS RomPrefetchRegs;
extern volatile struct TEST_ERROR_REGS TestErrorRegs;
extern volatile struct EMIF1_CONFIG_REGS Emif1ConfigRegs;
extern volatile struct EMIF2_CONFIG_REGS Emif2ConfigRegs;
#endif
#ifdef CPU2
extern volatile struct MEM_CFG_REGS MemCfgRegs;
extern volatile struct ACCESS_PROTECTION_REGS AccessProtectionRegs;
extern volatile struct MEMORY_ERROR_REGS MemoryErrorRegs;
extern volatile struct ROM_WAIT_STATE_REGS RomWaitStateRegs;
extern volatile struct ROM_PREFETCH_REGS RomPrefetchRegs;
extern volatile struct TEST_ERROR_REGS TestErrorRegs;
extern volatile struct EMIF1_CONFIG_REGS Emif1ConfigRegs;
#endif
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
