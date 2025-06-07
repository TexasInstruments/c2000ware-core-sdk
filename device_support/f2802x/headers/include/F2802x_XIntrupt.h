//###########################################################################
//
// FILE:  F2802x_XIntrupt.h
//
// TITLE: F2802x Device External Interrupt Register Definitions.
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:
// Copyright (C) 2009-2025 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef F2802x_XINTRUPT_H
#define F2802x_XINTRUPT_H

#ifdef __cplusplus
extern "C" {
#endif

struct XINTCR_BITS 
{
    uint16_t   ENABLE:1;    // 0      enable/disable
    uint16_t   rsvd1:1;     // 1      reserved
    uint16_t   POLARITY:2;  // 3:2    pos/neg, both triggered
    uint16_t   rsvd2:12;    // 15:4   reserved
};

union XINTCR_REG 
{
    uint16_t                all;
    struct XINTCR_BITS      bit;
};

//
// External Interrupt Register File
//
struct XINTRUPT_REGS 
{
    union XINTCR_REG XINT1CR;
    union XINTCR_REG XINT2CR;
    union XINTCR_REG XINT3CR;
    uint16_t           rsvd1[5];
    uint16_t           XINT1CTR;
    uint16_t           XINT2CTR;
    uint16_t           XINT3CTR;
    uint16_t           rsvd[5];
};

//
// External Interrupt References & Function Declarations
//
extern volatile struct XINTRUPT_REGS XIntruptRegs;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif  // end of F2802x_XINTF_H definition

//
// End of file
//

