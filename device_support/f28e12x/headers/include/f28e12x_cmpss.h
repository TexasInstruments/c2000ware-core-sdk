//###########################################################################
//
// FILE:    f28e12x_cmpss.h
//
// TITLE:   Definitions for the CMPSS registers.
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

#ifndef F28E12X_CMPSS_H
#define F28E12X_CMPSS_H

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// CMPSS Individual Register Bit Definitions:

struct COMPCTL_BITS {                   // bits description
    Uint16 COMPHSOURCE:1;               // 0 High Comparator Source Select
    Uint16 COMPHINV:1;                  // 1 High Comparator Invert Select
    Uint16 CTRIPHSEL:2;                 // 3:2 High Comparator Trip Select
    Uint16 CTRIPOUTHSEL:2;              // 5:4 High Comparator Trip Output Select
    Uint16 ASYNCHEN:1;                  // 6 High Comparator Asynchronous Path Enable
    Uint16 rsvd1:1;                     // 7 Reserved
    Uint16 COMPLSOURCE:1;               // 8 Low Comparator Source Select
    Uint16 COMPLINV:1;                  // 9 Low Comparator Invert Select
    Uint16 CTRIPLSEL:2;                 // 11:10 Low Comparator Trip Select
    Uint16 CTRIPOUTLSEL:2;              // 13:12 Low Comparator Trip Output Select
    Uint16 ASYNCLEN:1;                  // 14 Low Comparator Asynchronous Path Enable
    Uint16 COMPDACE:1;                  // 15 Comparator/DAC Enable
};

union COMPCTL_REG {
    Uint16  all;
    struct  COMPCTL_BITS  bit;
};

struct COMPHYSCTL_BITS {                // bits description
    Uint16 COMPHYS:4;                   // 3:0 Comparator Hysteresis Trim
    Uint16 rsvd1:12;                    // 15:4 Reserved
};

union COMPHYSCTL_REG {
    Uint16  all;
    struct  COMPHYSCTL_BITS  bit;
};

struct COMPSTS_BITS {                   // bits description
    Uint16 COMPHSTS:1;                  // 0 High Comparator Status
    Uint16 COMPHLATCH:1;                // 1 High Comparator Latched Status
    Uint16 rsvd1:6;                     // 7:2 Reserved
    Uint16 COMPLSTS:1;                  // 8 Low Comparator Status
    Uint16 COMPLLATCH:1;                // 9 Low Comparator Latched Status
    Uint16 rsvd2:6;                     // 15:10 Reserved
};

union COMPSTS_REG {
    Uint16  all;
    struct  COMPSTS_BITS  bit;
};

struct COMPSTSCLR_BITS {                // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 HLATCHCLR:1;                 // 1 High Comparator Latched Status Clear
    Uint16 HSYNCCLREN:1;                // 2 High Comparator EPWMSYNCPER Clear Enable
    Uint16 rsvd2:6;                     // 8:3 Reserved
    Uint16 LLATCHCLR:1;                 // 9 Low Comparator Latched Status Clear
    Uint16 LSYNCCLREN:1;                // 10 Low Comparator EPWMSYNCPER Clear Enable
    Uint16 rsvd3:5;                     // 15:11 Reserved
};

union COMPSTSCLR_REG {
    Uint16  all;
    struct  COMPSTSCLR_BITS  bit;
};

struct COMPDACHCTL_BITS {               // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 RAMPSOURCE:4;                // 4:1 Ramp Generator Source Control
    Uint16 rsvd2:1;                     // 5 Reserved
    Uint16 rsvd3:1;                     // 6 Reserved
    Uint16 SWLOADSEL:1;                 // 7 Software Load Select
    Uint16 rsvd4:4;                     // 11:8 Reserved
    Uint16 rsvd5:1;                     // 12 Reserved
    Uint16 rsvd6:1;                     // 13 Reserved
    Uint16 rsvd7:2;                     // 15:14 Reserved
};

union COMPDACHCTL_REG {
    Uint16  all;
    struct  COMPDACHCTL_BITS  bit;
};

struct DACHVALS_BITS {                  // bits description
    Uint16 DACVAL:12;                   // 11:0 DAC Value Control
    Uint16 rsvd1:4;                     // 15:12 Reserved
};

union DACHVALS_REG {
    Uint16  all;
    struct  DACHVALS_BITS  bit;
};

struct DACHVALA_BITS {                  // bits description
    Uint16 DACVAL:12;                   // 11:0 DAC Value Control
    Uint16 rsvd1:4;                     // 15:12 Reserved
};

union DACHVALA_REG {
    Uint16  all;
    struct  DACHVALA_BITS  bit;
};

struct DACLVALS_BITS {                  // bits description
    Uint16 DACVAL:12;                   // 11:0 DAC Value Control
    Uint16 rsvd1:4;                     // 15:12 Reserved
};

union DACLVALS_REG {
    Uint16  all;
    struct  DACLVALS_BITS  bit;
};

struct DACLVALA_BITS {                  // bits description
    Uint16 DACVAL:12;                   // 11:0 DAC Value Control
    Uint16 rsvd1:4;                     // 15:12 Reserved
};

union DACLVALA_REG {
    Uint16  all;
    struct  DACLVALA_BITS  bit;
};

struct CTRIPLFILCTL_BITS {              // bits description
    Uint16 FILTINSEL:3;                 // 2:0 Filter Input Select
    Uint16 SAMPWIN:6;                   // 8:3 Sample Window
    Uint16 THRESH:6;                    // 14:9 Majority Voting Threshold
    Uint16 FILINIT:1;                   // 15 Filter Initialization Bit
};

union CTRIPLFILCTL_REG {
    Uint16  all;
    struct  CTRIPLFILCTL_BITS  bit;
};

struct CTRIPHFILCTL_BITS {              // bits description
    Uint16 FILTINSEL:3;                 // 2:0 Filter Input Select
    Uint16 SAMPWIN:6;                   // 8:3 Sample Window
    Uint16 THRESH:6;                    // 14:9 Majority Voting Threshold
    Uint16 FILINIT:1;                   // 15 Filter Initialization Bit
};

union CTRIPHFILCTL_REG {
    Uint16  all;
    struct  CTRIPHFILCTL_BITS  bit;
};

struct COMPLOCK_BITS {                  // bits description
    Uint16 COMPCTL:1;                   // 0 COMPCTL Lock
    Uint16 COMPHYSCTL:1;                // 1 COMPHYSCTL Lock
    Uint16 DACCTL:1;                    // 2 DACCTL Lock
    Uint16 CTRIP:1;                     // 3 CTRIP Lock
    Uint16 rsvd1:1;                     // 4 Reserved
    Uint16 rsvd2:11;                    // 15:5 Reserved
};

union COMPLOCK_REG {
    Uint16  all;
    struct  COMPLOCK_BITS  bit;
};

struct COMPDACLCTL_BITS {               // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 RAMPSOURCE:4;                // 4:1 Ramp Generator Source Control
    Uint16 rsvd2:1;                     // 5 Reserved
    Uint16 rsvd3:1;                     // 6 Reserved
    Uint16 rsvd4:1;                     // 7 Reserved
    Uint16 rsvd5:4;                     // 11:8 Reserved
    Uint16 rsvd6:1;                     // 12 Reserved
    Uint16 rsvd7:1;                     // 13 Reserved
    Uint16 rsvd8:2;                     // 15:14 Reserved
};

union COMPDACLCTL_REG {
    Uint16  all;
    struct  COMPDACLCTL_BITS  bit;
};

struct CTRIPLFILCLKCTL2_BITS {          // bits description
    Uint16 CLKPRESCALEU:8;              // 7:0 Sample Clock Prescale Upper Bits
    Uint16 rsvd1:8;                     // 15:8 Reserved
};

union CTRIPLFILCLKCTL2_REG {
    Uint16  all;
    struct  CTRIPLFILCLKCTL2_BITS  bit;
};

struct CTRIPHFILCLKCTL2_BITS {          // bits description
    Uint16 CLKPRESCALEU:8;              // 7:0 Sample Clock Prescale Upper Bits
    Uint16 rsvd1:8;                     // 15:8 Reserved
};

union CTRIPHFILCLKCTL2_REG {
    Uint16  all;
    struct  CTRIPHFILCLKCTL2_BITS  bit;
};

struct CMPSS_LITE_REGS {
    union   COMPCTL_REG                      COMPCTL;                      // CMPSS Comparator Control Register
    union   COMPHYSCTL_REG                   COMPHYSCTL;                   // CMPSS Comparator Hysteresis Control Register
    union   COMPSTS_REG                      COMPSTS;                      // CMPSS Comparator Status Register
    union   COMPSTSCLR_REG                   COMPSTSCLR;                   // CMPSS Comparator Status Clear Register
    union   COMPDACHCTL_REG                  COMPDACHCTL;                  // CMPSS High DAC Control Register
    Uint16                                   rsvd1;                        // Reserved
    union   DACHVALS_REG                     DACHVALS;                     // CMPSS High DAC Value Shadow Register
    union   DACHVALA_REG                     DACHVALA;                     // CMPSS High DAC Value Active Register
    Uint16                                   rsvd2[10];                    // Reserved
    union   DACLVALS_REG                     DACLVALS;                     // CMPSS Low DAC Value Shadow Register
    union   DACLVALA_REG                     DACLVALA;                     // CMPSS Low DAC Value Active Register
    Uint16                                   rsvd3[2];                     // Reserved
    union   CTRIPLFILCTL_REG                 CTRIPLFILCTL;                 // CTRIPL Filter Control Register
    Uint16                                   CTRIPLFILCLKCTL;              // CTRIPL Filter Clock Control Register
    union   CTRIPHFILCTL_REG                 CTRIPHFILCTL;                 // CTRIPH Filter Control Register
    Uint16                                   CTRIPHFILCLKCTL;              // CTRIPH Filter Clock Control Register
    union   COMPLOCK_REG                     COMPLOCK;                     // CMPSS Lock Register
    Uint16                                   rsvd4[9];                     // Reserved
    union   COMPDACLCTL_REG                  COMPDACLCTL;                  // CMPSS Low DAC Control Register
    Uint16                                   rsvd5[18];                    // Reserved
    union   CTRIPLFILCLKCTL2_REG             CTRIPLFILCLKCTL2;             // CTRIPL Filter Clock Control Register 2
    Uint16                                   rsvd6;                        // Reserved
    union   CTRIPHFILCLKCTL2_REG             CTRIPHFILCLKCTL2;             // CTRIPH Filter Clock Control Register 2
};

//---------------------------------------------------------------------------
// CMPSS External References & Function Declarations:
//
extern volatile struct CMPSS_LITE_REGS CmpssLite1Regs;
extern volatile struct CMPSS_LITE_REGS CmpssLite2Regs;
extern volatile struct CMPSS_LITE_REGS CmpssLite3Regs;
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
