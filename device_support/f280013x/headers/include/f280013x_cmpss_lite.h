//###########################################################################
//
// FILE:    f280013x_cmpss_lite.h
//
// TITLE:   Definitions for the CMPSS_LITE registers.
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

#ifndef F280013X_CMPSS_LITE_H
#define F280013X_CMPSS_LITE_H

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// CMPSS_LITE Individual Register Bit Definitions:

struct COMPCTL_LITE_BITS {                   // bits description
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

union COMPCTL_LITE_REG {
    Uint16  all;
    struct  COMPCTL_LITE_BITS  bit;
};

struct COMPHYSCTL_LITE_BITS {                // bits description
    Uint16 COMPHYS:4;                   // 3:0 Comparator Hysteresis Trim
    Uint16 rsvd1:12;                    // 15:4 Reserved
};

union COMPHYSCTL_LITE_REG {
    Uint16  all;
    struct  COMPHYSCTL_LITE_BITS  bit;
};

struct COMPSTS_LITE_BITS {                   // bits description
    Uint16 COMPHSTS:1;                  // 0 High Comparator Status
    Uint16 COMPHLATCH:1;                // 1 High Comparator Latched Status
    Uint16 rsvd1:6;                     // 7:2 Reserved
    Uint16 COMPLSTS:1;                  // 8 Low Comparator Status
    Uint16 COMPLLATCH:1;                // 9 Low Comparator Latched Status
    Uint16 rsvd2:6;                     // 15:10 Reserved
};

union COMPSTS_LITE_REG {
    Uint16  all;
    struct  COMPSTS_LITE_BITS  bit;
};

struct COMPSTSCLR_LITE_BITS {                // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 HLATCHCLR:1;                 // 1 High Comparator Latched Status Clear
    Uint16 HSYNCCLREN:1;                // 2 High Comparator EPWMSYNCPER Clear Enable
    Uint16 rsvd2:6;                     // 8:3 Reserved
    Uint16 LLATCHCLR:1;                 // 9 Low Comparator Latched Status Clear
    Uint16 LSYNCCLREN:1;                // 10 Low Comparator EPWMSYNCPER Clear Enable
    Uint16 rsvd3:5;                     // 15:11 Reserved
};

union COMPSTSCLR_LITE_REG {
    Uint16  all;
    struct  COMPSTSCLR_LITE_BITS  bit;
};

struct COMPDACHCTL_LITE_BITS {               // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 RAMPSOURCE:4;                // 4:1 Ramp Generator Source Control
    Uint16 rsvd2:1;                     // 5 Reserved
    Uint16 rsvd3:1;                     // 6 Reserved
    Uint16 SWLOADSEL:1;                 // 7 Software Load Select
    Uint16 BLANKSOURCE:4;               // 11:8 EPWMBLANK Source Select
    Uint16 BLANKEN:1;                   // 12 EPWMBLANK Enable
    Uint16 rsvd4:1;                     // 13 Reserved
    Uint16 rsvd5:2;                     // 15:14 Reserved
};

union COMPDACHCTL_LITE_REG {
    Uint16  all;
    struct  COMPDACHCTL_LITE_BITS  bit;
};

struct DACHVALS_LITE_BITS {                  // bits description
    Uint16 DACVAL:12;                   // 11:0 DAC Value Control
    Uint16 rsvd1:4;                     // 15:12 Reserved
};

union DACHVALS_LITE_REG {
    Uint16  all;
    struct  DACHVALS_LITE_BITS  bit;
};

struct DACHVALA_LITE_BITS {                  // bits description
    Uint16 DACVAL:12;                   // 11:0 DAC Value Control
    Uint16 rsvd1:4;                     // 15:12 Reserved
};

union DACHVALA_LITE_REG {
    Uint16  all;
    struct  DACHVALA_LITE_BITS  bit;
};

struct DACLVALS_LITE_BITS {                  // bits description
    Uint16 DACVAL:12;                   // 11:0 DAC Value Control
    Uint16 rsvd1:4;                     // 15:12 Reserved
};

union DACLVALS_LITE_REG {
    Uint16  all;
    struct  DACLVALS_LITE_BITS  bit;
};

struct DACLVALA_LITE_BITS {                  // bits description
    Uint16 DACVAL:12;                   // 11:0 DAC Value Control
    Uint16 rsvd1:4;                     // 15:12 Reserved
};

union DACLVALA_LITE_REG {
    Uint16  all;
    struct  DACLVALA_LITE_BITS  bit;
};

struct CTRIPLFILCTL_LITE_BITS {              // bits description
    Uint16 rsvd1:3;                     // 2:0 Reserved
    Uint16 SAMPWIN:5;                   // 7:3 Sample Window
    Uint16 rsvd2:1;                     // 8 Reserved
    Uint16 THRESH:5;                    // 13:9 Majority Voting Threshold
    Uint16 rsvd3:1;                     // 14 Reserved
    Uint16 FILINIT:1;                   // 15 Filter Initialization Bit
};

union CTRIPLFILCTL_LITE_REG {
    Uint16  all;
    struct  CTRIPLFILCTL_LITE_BITS  bit;
};

struct CTRIPHFILCTL_LITE_BITS {              // bits description
    Uint16 rsvd1:3;                     // 2:0 Reserved
    Uint16 SAMPWIN:5;                   // 7:3 Sample Window
    Uint16 rsvd2:1;                     // 8 Reserved
    Uint16 THRESH:5;                    // 13:9 Majority Voting Threshold
    Uint16 rsvd3:1;                     // 14 Reserved
    Uint16 FILINIT:1;                   // 15 Filter Initialization Bit
};

union CTRIPHFILCTL_LITE_REG {
    Uint16  all;
    struct  CTRIPHFILCTL_LITE_BITS  bit;
};

struct COMPLOCK_LITE_BITS {                  // bits description
    Uint16 COMPCTL:1;                   // 0 COMPCTL Lock
    Uint16 COMPHYSCTL:1;                // 1 COMPHYSCTL Lock
    Uint16 DACCTL:1;                    // 2 DACCTL Lock
    Uint16 CTRIP:1;                     // 3 CTRIP Lock
    Uint16 rsvd1:1;                     // 4 Reserved
    Uint16 rsvd2:11;                    // 15:5 Reserved
};

union COMPLOCK_LITE_REG {
    Uint16  all;
    struct  COMPLOCK_LITE_BITS  bit;
};

struct CMPSS_LITE_REGS {
    union   COMPCTL_LITE_REG                 COMPCTL;                      // CMPSS Comparator Control Register
    union   COMPHYSCTL_LITE_REG              COMPHYSCTL;                   // CMPSS Comparator Hysteresis Control Register
    union   COMPSTS_LITE_REG                 COMPSTS;                      // CMPSS Comparator Status Register
    union   COMPSTSCLR_LITE_REG              COMPSTSCLR;                   // CMPSS Comparator Status Clear Register
    union   COMPDACHCTL_LITE_REG             COMPDACHCTL;                  // CMPSS High DAC Control Register
    Uint16                                   rsvd1;                        // Reserved
    union   DACHVALS_LITE_REG                DACHVALS;                     // CMPSS High DAC Value Shadow Register
    union   DACHVALA_LITE_REG                DACHVALA;                     // CMPSS High DAC Value Active Register
    Uint16                                   rsvd2[10];                    // Reserved
    union   DACLVALS_LITE_REG                DACLVALS;                     // CMPSS Low DAC Value Shadow Register
    union   DACLVALA_LITE_REG                DACLVALA;                     // CMPSS Low DAC Value Active Register
    Uint16                                   rsvd3[2];                     // Reserved
    union   CTRIPLFILCTL_LITE_REG            CTRIPLFILCTL;                 // CTRIPL Filter Control Register
    Uint16                                   CTRIPLFILCLKCTL;              // CTRIPL Filter Clock Control Register
    union   CTRIPHFILCTL_LITE_REG            CTRIPHFILCTL;                 // CTRIPH Filter Control Register
    Uint16                                   CTRIPHFILCLKCTL;              // CTRIPH Filter Clock Control Register
    union   COMPLOCK_LITE_REG                COMPLOCK;                     // CMPSS Lock Register
};

//---------------------------------------------------------------------------
// CMPSS_LITE External References & Function Declarations:
//
extern volatile struct CMPSS_LITE_REGS CmpssLite2Regs;
extern volatile struct CMPSS_LITE_REGS CmpssLite3Regs;
extern volatile struct CMPSS_LITE_REGS CmpssLite4Regs;
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
