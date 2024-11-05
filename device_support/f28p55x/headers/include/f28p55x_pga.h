//###########################################################################
//
// FILE:    f28p55x_pga.h
//
// TITLE:   Definitions for the PGA registers.
//
//###########################################################################
// 
// C2000Ware v5.04.00.00
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

#ifndef F28P55X_PGA_H
#define F28P55X_PGA_H

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// PGA Individual Register Bit Definitions:

struct PGACTL_BITS {                    // bits description
    Uint16 PGAEN:1;                     // 0 PGA Enable
    Uint16 FILT_RES_SEL:3;              // 3:1 Filter Resistor Select
    Uint16 rsvd1:1;                     // 4 Reserved
    Uint16 GAIN:3;                      // 7:5 PGA gain setting
    Uint16 PGA_OUTENABLE:1;             // 8 PGA Output Enable
    Uint16 PGA_OUTEN_INTGAIN:1;         // 9 PGA Internal Gain Output Enable
    Uint16 rsvd2:5;                     // 14:10 Reserved
    Uint16 CHOP_EXTCTRL:1;              // 15 External Chop Signal Control
};

union PGACTL_REG {
    Uint16  all;
    struct  PGACTL_BITS  bit;
};

struct MUXSEL_BITS {                    // bits description
    Uint16 PMUXSEL:2;                   // 1:0 Positive Input Mux Select
    Uint16 rsvd1:2;                     // 3:2 Reserved
    Uint16 NMUXSEL:2;                   // 5:4 Negative Input Mux Select
    Uint16 rsvd2:2;                     // 7:6 Reserved
    Uint16 MMUXSEL:2;                   // 9:8 M Mux Select
    Uint16 rsvd3:2;                     // 11:10 Reserved
    Uint16 PGA_FBONPIN:1;               // 12 Connect PGAOUT to PGA_INM
    Uint16 PGA_CHOP:2;                  // 14:13 Chopper Mode Control
    Uint16 rsvd4:1;                     // 15 Reserved
};

union MUXSEL_REG {
    Uint16  all;
    struct  MUXSEL_BITS  bit;
};

struct OFFSETTRIM_BITS {                // bits description
    Uint16 PGA_OFFSETTRIMN:8;           // 7:0 OFFSET TRIM value for i/p NMOS pair
    Uint16 rsvd1:8;                     // 15:8 Reserved
    Uint16 PGA_OFFSETTRIMP:8;           // 23:16 OFFSET TRIM value for i/p PMOS pair
    Uint16 rsvd2:8;                     // 31:24 Reserved
};

union OFFSETTRIM_REG {
    Uint32  all;
    struct  OFFSETTRIM_BITS  bit;
};

struct PGATYPE_BITS {                   // bits description
    Uint16 REV:8;                       // 7:0 PGA Revision Field
    Uint16 TYPE:8;                      // 15:8 PGA Type Field
};

union PGATYPE_REG {
    Uint16  all;
    struct  PGATYPE_BITS  bit;
};

struct PGALOCK_BITS {                   // bits description
    Uint16 PGACTL:1;                    // 0 Lock bit for PGACTL.
    Uint16 MUXSEL:1;                    // 1 Lock bit for MUXSEL
    Uint16 OFFSETTRIM:1;                // 2 Lock bit for OFFSET TRIM
    Uint16 PGATMCTL:1;                  // 3 Lock but for PGATMCTL
    Uint16 rsvd1:1;                     // 4 Reserved
    Uint16 rsvd2:1;                     // 5 Reserved
    Uint16 rsvd3:1;                     // 6 Reserved
    Uint16 rsvd4:1;                     // 7 Reserved
    Uint16 rsvd5:8;                     // 15:8 Reserved
};

union PGALOCK_REG {
    Uint16  all;
    struct  PGALOCK_BITS  bit;
};

struct PGA_REGS {
    union   PGACTL_REG                       PGACTL;                       // PGA Control Register
    union   MUXSEL_REG                       MUXSEL;                       // Mux Selection Register
    union   OFFSETTRIM_REG                   OFFSETTRIM;                   // Offset Trim Register
    Uint16                                   rsvd1;                        // Reserved
    union   PGATYPE_REG                      PGATYPE;                      // PGA Type Register
    union   PGALOCK_REG                      PGALOCK;                      // PGA Lock Register
};

//---------------------------------------------------------------------------
// PGA External References & Function Declarations:
//
extern volatile struct PGA_REGS Pga1Regs;
extern volatile struct PGA_REGS Pga2Regs;
extern volatile struct PGA_REGS Pga3Regs;
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
