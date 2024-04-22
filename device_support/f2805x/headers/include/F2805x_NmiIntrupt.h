//###########################################################################
//
// FILE:   F2805x_Nmiintrupt.h
//
// TITLE:  F2805x Device NmiIntrupt Register Definitions.
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:
// Copyright (C) 2012-2024 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef F2805x_NmiIntrupt_H
#define F2805x_NmiIntrupt_H

#ifdef __cplusplus
extern "C" {
#endif


//
// NmiIntrupt Individual Register Bit Definitions:
//
struct NMICFG_BITS {                       // bits description
    Uint16  rsvd1:1;                       // 0 Reserved
    Uint16  CLOCKFAIL:1;                   // 1 CLOCKFAIL NMI Interrupt Enable
    Uint16  rsvd2:14;                      // 15:2 Reserved
};

union NMICFG_REG {
    Uint16  all;
    struct  NMICFG_BITS  bit;
};

struct NMIFLG_BITS {                       // bits description
    Uint16  NMIINT:1;                      // 0 NMI Interrupt Flag
    Uint16  CLOCKFAIL:1;                   // 1 CLOCKFAIL NMI Flag
    Uint16  rsvd1:14;                      // 15:2 Reserved
};

union NMIFLG_REG {
    Uint16  all;
    struct  NMIFLG_BITS  bit;
};

struct NMIFLGCLR_BITS {                    // bits description
    Uint16  NMIINT:1;                      // 0 NMI Interrupt Flag Clear
    Uint16  CLOCKFAIL:1;                   // 1 CLOCKFAIL NMI Flag Clear
    Uint16  rsvd1:14;                      // 15:2 Reserved
};

union NMIFLGCLR_REG {
    Uint16  all;
    struct  NMIFLGCLR_BITS  bit;
};

struct NMIFLGFRC_BITS {                    // bits description
    Uint16  rsvd1:1;                       // 0 Reserved
    Uint16  CLOCKFAIL:1;                   // 1 CLOCKFAIL NMI Flag Force
    Uint16  rsvd2:14;                      // 15:2 Reserved
};

union NMIFLGFRC_REG {
    Uint16  all;
    struct  NMIFLGFRC_BITS  bit;
};

struct NMI_INTRUPT_REGS {
    union   NMICFG_REG       NMICFG;       // C28 NMI Configuration Register
    union   NMIFLG_REG       NMIFLG;       // C28 NMI Flag Register
    union   NMIFLGCLR_REG    NMIFLGCLR;    // C28 NMI Flag Clear Register
    union   NMIFLGFRC_REG    NMIFLGFRC;    // C28 NMI Flag Force Register
    Uint16                   NMIWDCNT;     // C28 NMI Watchdog Counter Register
    Uint16                   NMIWDPRD;     // C28 NMI Watchdog Period Register
};

//
// Nmiintrupt External References & Function Declarations:
//
extern volatile struct NMI_INTRUPT_REGS NmiIntruptRegs;

#ifdef __cplusplus
}
#endif                            /* extern "C" */


#endif                            // end of F2805x_NmiIntrupt_H definition
//
// End of file
//
