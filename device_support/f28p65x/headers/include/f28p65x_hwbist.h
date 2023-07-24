//###########################################################################
//
// FILE:    f28p65x_hwbist.h
//
// TITLE:   Definitions for the HWBIST registers.
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

#ifndef F28P65X_HWBIST_H
#define F28P65X_HWBIST_H

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// HWBIST Individual Register Bit Definitions:

struct CSTCGCR3_BITS {                  // bits description
    Uint16 ILS:4;                       // 3:0 Interrupt Logging Start
    Uint16 rsvd1:12;                    // 15:4 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union CSTCGCR3_REG {
    Uint32  all;
    struct  CSTCGCR3_BITS  bit;
};

struct CSTCGCR4_BITS {                  // bits description
    Uint16 BISTGO:4;                    // 3:0 BIST Start
    Uint16 rsvd1:12;                    // 15:4 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union CSTCGCR4_REG {
    Uint32  all;
    struct  CSTCGCR4_BITS  bit;
};

struct CSTCGCR5_BITS {                  // bits description
    Uint16 RESTART:4;                   // 3:0 Restart Enable
    Uint16 rsvd1:12;                    // 15:4 Reserved
    Uint16 rsvd2:15;                    // 30:16 Reserved
    Uint16 SOFT_RESET:1;                // 31 Soft reset to BIST controller
};

union CSTCGCR5_REG {
    Uint32  all;
    struct  CSTCGCR5_BITS  bit;
};

struct CSTCGCR6_BITS {                  // bits description
    Uint16 COV:2;                       // 1:0 COVERAGE
    Uint16 rsvd1:14;                    // 15:2 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union CSTCGCR6_REG {
    Uint32  all;
    struct  CSTCGCR6_BITS  bit;
};

struct CSTCGCR7_BITS {                  // bits description
    Uint16 MCL:8;                       // 7:0 MAX CHAIN LENGTH
    Uint16 DC:4;                        // 11:8 DEAD CYCLES
    Uint16 NP:4;                        // 15:12 NUM  OF PIPELINE STAGES
    Uint16 PST:2;                       // 17:16 PATTERN SET TYPE
    Uint16 SCD:2;                       // 19:18 SHIFT_CLOCK_DIVISION
    Uint16 rsvd1:12;                    // 31:20 Reserved
};

union CSTCGCR7_REG {
    Uint32  all;
    struct  CSTCGCR7_BITS  bit;
};

struct CSTCGCR8_BITS {                  // bits description
    Uint16 CPC:16;                      // 15:0 COMPARE PATTERN CNT
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union CSTCGCR8_REG {
    Uint32  all;
    struct  CSTCGCR8_BITS  bit;
};

struct CSTCPCNT_BITS {                  // bits description
    Uint16 PCNT_95:16;                  // 15:0 PATTERNS FOR 95% COVERAGE
    Uint16 PCNT_99:16;                  // 31:16 PATTERNS FOR 99% COVERAGE
};

union CSTCPCNT_REG {
    Uint32  all;
    struct  CSTCPCNT_BITS  bit;
};

struct CSTCCONFIG_BITS {                // bits description
    Uint16 CFGDONE:4;                   // 3:0 Configuration done
    Uint16 rsvd1:12;                    // 15:4 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union CSTCCONFIG_REG {
    Uint32  all;
    struct  CSTCCONFIG_BITS  bit;
};

struct CSTCSADDR_BITS {                 // bits description
    Uint16 SAPAT:16;                    // 15:0 PATTERN ROM Start Address
    Uint16 SAMISR:16;                   // 31:16 MISR ROM Start Address
};

union CSTCSADDR_REG {
    Uint32  all;
    struct  CSTCSADDR_BITS  bit;
};

struct CSTCTEST_BITS {                  // bits description
    Uint16 TEST_TO:4;                   // 3:0 Test_ Time_Out
    Uint16 TEST_CMP_FAIL:4;             // 7:4 Test MISR compare fail
    Uint16 TEST_NMI:4;                  // 11:8 Test_NMI
    Uint32 TEST:20;                     // 31:12 TEST Bits
};

union CSTCTEST_REG {
    Uint32  all;
    struct  CSTCTEST_BITS  bit;
};

struct CSTCCRD_BITS {                   // bits description
    Uint16 Restore_Done:4;              // 3:0 Context Restone Done
    Uint16 rsvd1:12;                    // 15:4 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union CSTCCRD_REG {
    Uint32  all;
    struct  CSTCCRD_BITS  bit;
};

struct CSTCGSTAT_BITS {                 // bits description
    Uint16 BISTDONE:1;                  // 0 HW BIST Complete
    Uint16 MACRODONE:1;                 // 1 Macro test slot Complete
    Uint16 NMI:1;                       // 2 Exit due to NMI
    Uint16 BISTFAIL:1;                  // 3 HW BIST Failure
    Uint16 INTCMPF:1;                   // 4 Intermediate Comparison Failure
    Uint16 TOFAIL:1;                    // 5 Time Out Failure
    Uint16 rsvd1:10;                    // 15:6 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union CSTCGSTAT_REG {
    Uint32  all;
    struct  CSTCGSTAT_BITS  bit;
};

struct CSTCCPCR_BITS {                  // bits description
    Uint16 PATCNT:16;                   // 15:0 Current Pattern Count
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union CSTCCPCR_REG {
    Uint32  all;
    struct  CSTCCPCR_BITS  bit;
};

struct CSTCCADDR_BITS {                 // bits description
    Uint16 PATADDR:16;                  // 15:0 Current Pattern ROM Address
    Uint16 MISRADDR:16;                 // 31:16 Current MISR ROM Address
};

union CSTCCADDR_REG {
    Uint32  all;
    struct  CSTCCADDR_BITS  bit;
};

struct HWBIST_REGS {
    Uint16                                   rsvd1[4];                     // Reserved
    Uint32                                   CSTCGCR1;                     // STC Global Control Register1
    Uint16                                   rsvd2[6];                     // Reserved
    union   CSTCGCR3_REG                     CSTCGCR3;                     // STC Global Control Register3
    Uint16                                   rsvd3[2];                     // Reserved
    union   CSTCGCR4_REG                     CSTCGCR4;                     // STC Global Control Register4
    Uint16                                   rsvd4[2];                     // Reserved
    union   CSTCGCR5_REG                     CSTCGCR5;                     // STC Global Control Register5
    Uint16                                   rsvd5[2];                     // Reserved
    union   CSTCGCR6_REG                     CSTCGCR6;                     // STC Global Control Register6
    Uint16                                   rsvd6[2];                     // Reserved
    union   CSTCGCR7_REG                     CSTCGCR7;                     // STC Global Control Register7
    Uint16                                   rsvd7[2];                     // Reserved
    union   CSTCGCR8_REG                     CSTCGCR8;                     // STC Global Control Register8
    Uint16                                   rsvd8[2];                     // Reserved
    union   CSTCPCNT_REG                     CSTCPCNT;                     // STC Pattern Count Register
    Uint16                                   rsvd9[2];                     // Reserved
    union   CSTCCONFIG_REG                   CSTCCONFIG;                   // STC Registers Configuration Status
    Uint16                                   rsvd10[2];                    // Reserved
    union   CSTCSADDR_REG                    CSTCSADDR;                    // STC ROM Start Address
    Uint16                                   rsvd11[2];                    // Reserved
    union   CSTCTEST_REG                     CSTCTEST;                     // C28 HW BIST Test Register
    Uint16                                   rsvd12[2];                    // Reserved
    Uint32                                   CSTCRET;                      // C28 Return PC Address
    Uint16                                   rsvd13[2];                    // Reserved
    union   CSTCCRD_REG                      CSTCCRD;                      // C28 Context Restore Done Register
    Uint16                                   rsvd14[6];                    // Reserved
    union   CSTCGSTAT_REG                    CSTCGSTAT;                    // STC Global Status Register
    Uint16                                   rsvd15[6];                    // Reserved
    union   CSTCCPCR_REG                     CSTCCPCR;                     // STC Current Pattern Count Register
    Uint16                                   rsvd16[2];                    // Reserved
    union   CSTCCADDR_REG                    CSTCCADDR;                    // STC Current ROM Address Register
    Uint16                                   rsvd17[2];                    // Reserved
    Uint32                                   CSTCMISR0;                    // MISR Result Register 0
    Uint16                                   rsvd18[2];                    // Reserved
    Uint32                                   CSTCMISR1;                    // MISR Result Register 1
    Uint16                                   rsvd19[2];                    // Reserved
    Uint32                                   CSTCMISR2;                    // MISR Result Register 2
    Uint16                                   rsvd20[2];                    // Reserved
    Uint32                                   CSTCMISR3;                    // MISR Result Register 3
    Uint16                                   rsvd21[2];                    // Reserved
    Uint32                                   CSTCMISR4;                    // MISR Result Register 4
    Uint16                                   rsvd22[2];                    // Reserved
    Uint32                                   CSTCMISR5;                    // MISR Result Register 5
    Uint16                                   rsvd23[2];                    // Reserved
    Uint32                                   CSTCMISR6;                    // MISR Result Register 6
    Uint16                                   rsvd24[2];                    // Reserved
    Uint32                                   CSTCMISR7;                    // MISR Result Register 7
    Uint16                                   rsvd25[2];                    // Reserved
    Uint32                                   CSTCMISR8;                    // MISR Result Register 8
    Uint16                                   rsvd26[2];                    // Reserved
    Uint32                                   CSTCMISR9;                    // MISR Result Register 9
    Uint16                                   rsvd27[2];                    // Reserved
    Uint32                                   CSTCMISR10;                   // MISR Result Register 10
    Uint16                                   rsvd28[2];                    // Reserved
    Uint32                                   CSTCMISR11;                   // MISR Result Register 11
    Uint16                                   rsvd29[2];                    // Reserved
    Uint32                                   CSTCMISR12;                   // MISR Result Register 12
    Uint16                                   rsvd30[2];                    // Reserved
    Uint32                                   CSTCMISR13;                   // MISR Result Register 13
    Uint16                                   rsvd31[2];                    // Reserved
    Uint32                                   CSTCMISR14;                   // MISR Result Register 14
    Uint16                                   rsvd32[2];                    // Reserved
    Uint32                                   CSTCMISR15;                   // MISR Result Register 15
};

//---------------------------------------------------------------------------
// HWBIST External References & Function Declarations:
//
#ifdef CPU1
extern volatile struct HWBIST_REGS HwbistRegs;
#endif
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
