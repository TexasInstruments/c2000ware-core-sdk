//###########################################################################
//
// FILE:    f2838x_analogsubsys.h
//
// TITLE:   Definitions for the ANALOGSUBSYS registers.
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

#ifndef F2838X_ANALOGSUBSYS_H
#define F2838X_ANALOGSUBSYS_H

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// ANALOGSUBSYS Individual Register Bit Definitions:

struct INTOSC1TRIM_BITS {               // bits description
    Uint16 VALFINETRIM:12;              // 11:0 Oscillator Value Fine Trim Bits
    Uint16 rsvd1:4;                     // 15:12 Reserved
    Uint16 rsvd2:8;                     // 23:16 Reserved
    Uint16 rsvd3:8;                     // 31:24 Reserved
};

union INTOSC1TRIM_REG {
    Uint32  all;
    struct  INTOSC1TRIM_BITS  bit;
};

struct INTOSC2TRIM_BITS {               // bits description
    Uint16 VALFINETRIM:12;              // 11:0 Oscillator Value Fine Trim Bits
    Uint16 rsvd1:4;                     // 15:12 Reserved
    Uint16 rsvd2:8;                     // 23:16 Reserved
    Uint16 rsvd3:8;                     // 31:24 Reserved
};

union INTOSC2TRIM_REG {
    Uint32  all;
    struct  INTOSC2TRIM_BITS  bit;
};

struct TSNSCTL_BITS {                   // bits description
    Uint16 ENABLE:1;                    // 0 Temperature Sensor Enable
    Uint16 rsvd1:15;                    // 15:1 Reserved
};

union TSNSCTL_REG {
    Uint16  all;
    struct  TSNSCTL_BITS  bit;
};

struct LOCK_BITS {                      // bits description
    Uint16 rsvd1:1;                     // 0 Reserved
    Uint16 rsvd2:1;                     // 1 Reserved
    Uint16 rsvd3:1;                     // 2 Reserved
    Uint16 TSNSCTL:1;                   // 3 Temperature Sensor Control Register Lock
    Uint16 rsvd4:1;                     // 4 Reserved
    Uint16 rsvd5:1;                     // 5 Reserved
    Uint16 rsvd6:1;                     // 6 Reserved
    Uint16 rsvd7:9;                     // 15:7 Reserved
    Uint16 rsvd8:3;                     // 18:16 Reserved
    Uint16 rsvd9:1;                     // 19 Reserved
    Uint16 rsvd10:1;                    // 20 Reserved
    Uint16 rsvd11:1;                    // 21 Reserved
    Uint16 rsvd12:1;                    // 22 Reserved
    Uint16 rsvd13:1;                    // 23 Reserved
    Uint16 rsvd14:1;                    // 24 Reserved
    Uint16 rsvd15:1;                    // 25 Reserved
    Uint16 rsvd16:1;                    // 26 Reserved
    Uint16 rsvd17:1;                    // 27 Reserved
    Uint16 rsvd18:1;                    // 28 Reserved
    Uint16 rsvd19:1;                    // 29 Reserved
    Uint16 rsvd20:1;                    // 30 Reserved
    Uint16 rsvd21:1;                    // 31 Reserved
};

union LOCK_REG {
    Uint32  all;
    struct  LOCK_BITS  bit;
};

struct ANAREFTRIMA_BITS {               // bits description
    Uint16 BGVALTRIM:6;                 // 5:0 Bandgap Value Trim
    Uint16 BGSLOPETRIM:5;               // 10:6 Bandgap Slope Trim
    Uint16 IREFTRIM:5;                  // 15:11 Reference Current Trim
    Uint16 rsvd1:8;                     // 23:16 Reserved
    Uint16 rsvd2:8;                     // 31:24 Reserved
};

union ANAREFTRIMA_REG {
    Uint32  all;
    struct  ANAREFTRIMA_BITS  bit;
};

struct ANAREFTRIMB_BITS {               // bits description
    Uint16 BGVALTRIM:6;                 // 5:0 Bandgap Value Trim
    Uint16 BGSLOPETRIM:5;               // 10:6 Bandgap Slope Trim
    Uint16 IREFTRIM:5;                  // 15:11 Reference Current Trim
    Uint16 rsvd1:8;                     // 23:16 Reserved
    Uint16 rsvd2:8;                     // 31:24 Reserved
};

union ANAREFTRIMB_REG {
    Uint32  all;
    struct  ANAREFTRIMB_BITS  bit;
};

struct ANAREFTRIMC_BITS {               // bits description
    Uint16 BGVALTRIM:6;                 // 5:0 Bandgap Value Trim
    Uint16 BGSLOPETRIM:5;               // 10:6 Bandgap Slope Trim
    Uint16 IREFTRIM:5;                  // 15:11 Reference Current Trim
    Uint16 rsvd1:8;                     // 23:16 Reserved
    Uint16 rsvd2:8;                     // 31:24 Reserved
};

union ANAREFTRIMC_REG {
    Uint32  all;
    struct  ANAREFTRIMC_BITS  bit;
};

struct ANAREFTRIMD_BITS {               // bits description
    Uint16 BGVALTRIM:6;                 // 5:0 Bandgap Value Trim
    Uint16 BGSLOPETRIM:5;               // 10:6 Bandgap Slope Trim
    Uint16 IREFTRIM:5;                  // 15:11 Reference Current Trim
    Uint16 rsvd1:8;                     // 23:16 Reserved
    Uint16 rsvd2:8;                     // 31:24 Reserved
};

union ANAREFTRIMD_REG {
    Uint32  all;
    struct  ANAREFTRIMD_BITS  bit;
};

struct ANALOG_SUBSYS_REGS {
    Uint16                                   rsvd1[32];                    // Reserved
    union   INTOSC1TRIM_REG                  INTOSC1TRIM;                  // Internal Oscillator 1 Trim Register
    union   INTOSC2TRIM_REG                  INTOSC2TRIM;                  // Internal Oscillator 2 Trim Register
    Uint16                                   rsvd2[2];                     // Reserved
    union   TSNSCTL_REG                      TSNSCTL;                      // Temperature Sensor Control Register
    Uint16                                   rsvd3[7];                     // Reserved
    union   LOCK_REG                         LOCK;                         // Lock Register
    Uint16                                   rsvd4[6];                     // Reserved
    union   ANAREFTRIMA_REG                  ANAREFTRIMA;                  // Analog Reference Trim A Register
    union   ANAREFTRIMB_REG                  ANAREFTRIMB;                  // Analog Reference Trim B Register
    union   ANAREFTRIMC_REG                  ANAREFTRIMC;                  // Analog Reference Trim C Register
    union   ANAREFTRIMD_REG                  ANAREFTRIMD;                  // Analog Reference Trim D Register
};

//---------------------------------------------------------------------------
// ANALOGSUBSYS External References & Function Declarations:
//
#ifdef CPU1
extern volatile struct ANALOG_SUBSYS_REGS AnalogSubsysRegs;
#endif
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
