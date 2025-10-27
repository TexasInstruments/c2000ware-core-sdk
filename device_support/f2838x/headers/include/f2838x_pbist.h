//###########################################################################
//
// FILE:    f2838x_pbist.h
//
// TITLE:   Definitions for the PBIST registers.
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

#ifndef F2838x_PBIST_H
#define F2838x_PBIST_H

#ifdef __cplusplus 
extern "C" {
#endif 


//---------------------------------------------------------------------------
// PBIST Individual Register Bit Definitions:

struct RAMT_BITS {                      // bits description
    Uint16 rsvd1:16;                    // 15:0 Reserved
    Uint16 RDS:8;                       // 23:16 Return Data Select
    Uint16 RGS:8;                       // 31:24 RAM Group Select
};

union RAMT_REG {
    Uint32  all;
    struct  RAMT_BITS  bit;
};

struct DLRT_BITS {                      // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 rsvd2:1;                     // 1 Reserved
    Uint16 ROM_TEST:1;                  // 2 ROM-based testing
    Uint16 TCK_GATED:1;                 // 3 TCK gated
    Uint16 CONFIG_ACC:1;                // 4 Config Access
    Uint16 rsvd3:1;                     // 5 Reserved
    Uint16 rsvd4:1;                     // 6 Reserved
    Uint16 rsvd5:1;                     // 7 Reserved
    Uint16 rsvd6:1;                     // 8 Reserved
    Uint16 GO_NOGO_TEST:1;              // 9 GO/ NO-GO Testing
    Uint16 rsvd7:1;                     // 10 Reserved
    Uint16 rsvd8:5;                     // 15:11 Reserved
    Uint16 rsvd9:16;                    // 31:16 Reserved
};

union DLRT_REG {
    Uint32  all;
    struct  DLRT_BITS  bit;
};

struct STR_BITS {                       // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 RESUME:1;                    // 1 Resume / Emulation Read
    Uint16 STOP:1;                      // 2 Stops PBIST testing
    Uint16 rsvd2:1;                     // 3 Reserved
    Uint16 rsvd3:1;                     // 4 Reserved
    Uint16 rsvd4:2;                     // 6:5 Reserved
    Uint16 rsvd5:1;                     // 7 Reserved
    Uint16 rsvd6:1;                     // 8 Reserved
    Uint16 rsvd7:7;                     // 15:9 Reserved
    Uint16 rsvd8:16;                    // 31:16 Reserved
};

union STR_REG {
    Uint32  all;
    struct  STR_BITS  bit;
};

struct PACT_BITS {                      // bits description
    Uint16 ENABLE:1;                    // 0 Enable clocks to PBIST
    Uint16 rsvd1:15;                    // 15:1 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union PACT_REG {
    Uint32  all;
    struct  PACT_BITS  bit;
};

struct OVERRIDE_BITS {                  // bits description
    Uint16 RINFO_MEM_OVER:1;            // 0 ROM Memory Information Override
    Uint16 rsvd1:2;                     // 2:1 Reserved
    Uint16 ALGO_OVER:1;                 // 3 ROM Algorithm Override
    Uint16 rsvd2:12;                    // 15:4 Reserved
    Uint16 rsvd3:16;                    // 31:16 Reserved
};

union OVERRIDE_REG {
    Uint32  all;
    struct  OVERRIDE_BITS  bit;
};

struct PBIST_REGS {
    Uint16                                   rsvd1[352];                   // Reserved
    union   RAMT_REG                         RAMT;                         // RAM Configuration Register
    Uint16                                   rsvd2[2];                     // Reserved
    union   DLRT_REG                         DLRT;                         // PBIST Data Logger Register
    Uint16                                   rsvd3[6];                     // Reserved
    union   STR_REG                          STR;                          // Program Control Register
    Uint16                                   rsvd4[18];                    // Reserved
    union   PACT_REG                         PACT;                         // PBIST Activate Register
    Uint16                                   rsvd5[6];                     // Reserved
    union   OVERRIDE_REG                     OVERRIDE;                     // PBIST Override Register
    Uint16                                   rsvd6[6];                     // Reserved
    Uint32                                   FSRF0;                        // Fail Status - Port 0
    Uint16                                   rsvd7[2];                     // Reserved
    Uint32                                   FSRF1;                        // Fail Status - Port 1
    Uint16                                   rsvd8[2];                     // Reserved
    Uint32                                   FSRC0;                        // Fail Status Count - Port 0
    Uint16                                   rsvd9[2];                     // Reserved
    Uint32                                   FSRC1;                        // Fail Status Count - Port 1
    Uint16                                   rsvd10[38];                   // Reserved
    Uint32                                   ALGO;                         // PBIST Algorithm
    Uint16                                   rsvd11[2];                    // Reserved
    Uint32                                   RINFOL;                       // RAM Info Mask Register Lower
    Uint16                                   rsvd12[2];                    // Reserved
    Uint32                                   RINFOU;                       // RAM Info Mask Register Higher
};

//---------------------------------------------------------------------------
// PBIST External References & Function Declarations:
//
#ifdef CPU1
extern volatile struct PBIST_REGS PbistRegs;
#endif
#ifdef CPU2
extern volatile struct PBIST_REGS PbistRegs;
#endif
#ifdef __cplusplus

}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
