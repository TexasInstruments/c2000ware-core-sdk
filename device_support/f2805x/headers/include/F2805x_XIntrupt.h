//###########################################################################
//
// FILE:   F2805x_Xintrupt.h
//
// TITLE:  F2805x Device XINTRUPT Register Definitions.
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:
// Copyright (C) 2012-2025 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef F2805x_XINTRUPT_H
#define F2805x_XINTRUPT_H

#ifdef __cplusplus
extern "C" {
#endif

//
// XINTRUPT Individual Register Bit Definitions:
//
struct XINTCR_BITS {                    // bits description
    Uint16  ENABLE:1;                   // 0 XINT1 Enable
    Uint16  rsvd1:1;                    // 1 Reserved
    Uint16  POLARITY:2;                 // 3:2 XINT1 Polarity
    Uint16  rsvd2:12;                   // 15:4 Reserved
};

union XINTCR_REG {
    Uint16  all;
    struct  XINTCR_BITS  bit;
};

struct XINTRUPT_REGS {
    union   XINTCR_REG    XINT1CR;      // XINT1 Configuration Register
    union   XINTCR_REG    XINT2CR;      // XINT2 Configuration Register
    union   XINTCR_REG    XINT3CR;      // XINT3 Configuration Register
    Uint16                rsvd1[5];     // Reserved
    Uint16                XINT1CTR;     // XINT1 Counter Register
    Uint16                XINT2CTR;     // XINT2 Counter Register
    Uint16                XINT3CTR;     // XINT3 Counter Register
};

//
// Xintrupt External References & Function Declarations:
//
extern volatile struct XINTRUPT_REGS XIntruptRegs;

#ifdef __cplusplus
}
#endif                                  /* extern "C" */


#endif                                  // end of F2805x_XINTRUPT_H definition
//
// End of file
//
