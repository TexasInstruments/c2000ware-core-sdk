// TI File $Revision: /main/4 $
// Checkin $Date: July 27, 2009   13:57:25 $
//###########################################################################
//
// FILE:   DSP2833x_Xintf.h
//
// TITLE:  DSP2833x Device External Interface Register Definitions.
//
//###########################################################################
// $TI Release: 2833x/2823x Header Files V1.32 $
// $Release Date: June 28, 2010 $
// $Copyright:
// Copyright (C) 2009-2024 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef DSP2833x_XINTF_H
#define DSP2833x_XINTF_H

#ifdef __cplusplus
extern "C" {
#endif

//
// XINTF timing register bit definitions
//
struct XTIMING_BITS {     // bits  description
    Uint16 XWRTRAIL:2;    // 1:0   Write access trail timing
    Uint16 XWRACTIVE:3;   // 4:2   Write access active timing
    Uint16 XWRLEAD:2;     // 6:5   Write access lead timing
    Uint16 XRDTRAIL:2;    // 8:7   Read access trail timing
    Uint16 XRDACTIVE:3;   // 11:9  Read access active timing
    Uint16 XRDLEAD:2;     // 13:12 Read access lead timing
    Uint16 USEREADY:1;    // 14    Extend access using HW waitstates
    Uint16 READYMODE:1;   // 15    Ready mode
    Uint16 XSIZE:2;       // 17:16 XINTF bus width - must be written as 11b
    Uint16 rsvd1:4;       // 21:18 reserved
    Uint16 X2TIMING:1;    // 22    Double lead/active/trail timing
    Uint16 rsvd3:9;       // 31:23 reserved
};

union XTIMING_REG {
    Uint32               all;
    struct XTIMING_BITS  bit;
};

//
// XINTF control register bit definitions
//
struct XINTCNF2_BITS {     // bits  description
    Uint16 WRBUFF:2;       // 1:0   Write buffer depth
    Uint16 CLKMODE:1;      // 2     Ratio for XCLKOUT with respect to XTIMCLK
    Uint16 CLKOFF:1;       // 3     Disable XCLKOUT
    Uint16 rsvd1:2;        // 5:4   reserved
    Uint16 WLEVEL:2;       // 7:6   Current level of the write buffer
    Uint16 rsvd2:1;        // 8     reserved
    Uint16 HOLD:1;         // 9     Hold enable/disable
    Uint16 HOLDS:1;        // 10    Current state of HOLDn input
    Uint16 HOLDAS:1;       // 11    Current state of HOLDAn output
    Uint16 rsvd3:4;        // 15:12 reserved
    Uint16 XTIMCLK:3;      // 18:16 Ratio for XTIMCLK
    Uint16 rsvd4:13;       // 31:19 reserved
};

union XINTCNF2_REG {
    Uint32                all;
    struct XINTCNF2_BITS  bit;
};

//
// XINTF bank switching register bit definitions
//
struct XBANK_BITS {       // bits  description
    Uint16  BANK:3;       // 2:0   Zone for which banking is enabled
    Uint16  BCYC:3;       // 5:3   XTIMCLK cycles to add
    Uint16  rsvd:10;      // 15:6  reserved
};  
    
union XBANK_REG {
    Uint16             all;
    struct XBANK_BITS  bit;
};

struct XRESET_BITS {
    Uint16  XHARDRESET:1;
    Uint16  rsvd1:15;
};

union XRESET_REG {
    Uint16            all;
    struct XRESET_BITS bit;
};

//
// XINTF Register File
//
struct XINTF_REGS {
    union XTIMING_REG XTIMING0;
    Uint32  rsvd1[5];
    union XTIMING_REG XTIMING6;
    union XTIMING_REG XTIMING7;
    Uint32  rsvd2[2];
    union XINTCNF2_REG XINTCNF2;
    Uint32  rsvd3;
    union XBANK_REG    XBANK;
    Uint16  rsvd4;
    Uint16  XREVISION;
    Uint16  rsvd5[2];
    union XRESET_REG   XRESET;
};

//
// XINTF External References & Function Declarations
//
extern volatile struct XINTF_REGS XintfRegs;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif  // end of DSP2833x_XINTF_H definition

//
// End of File
//

