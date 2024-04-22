// TI File $Revision: /main/1 $
// Checkin $Date: August 18, 2006   13:52:39 $
//###########################################################################
//
// FILE:  DSP2833x_XIntrupt.h
//
// TITLE: DSP2833x Device External Interrupt Register Definitions.
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

#ifndef DSP2833x_XINTRUPT_H
#define DSP2833x_XINTRUPT_H


#ifdef __cplusplus
extern "C" {
#endif

struct XINTCR_BITS {
    Uint16   ENABLE:1;    // 0      enable/disable
    Uint16   rsvd1:1;     // 1      reserved
    Uint16   POLARITY:2;  // 3:2    pos/neg, both triggered
    Uint16   rsvd2:12;    //15:4    reserved
};

union XINTCR_REG {
    Uint16               all;
    struct XINTCR_BITS   bit;
};  

struct XNMICR_BITS {
    Uint16   ENABLE:1;    // 0      enable/disable
    Uint16   SELECT:1;    // 1      Timer 1 or XNMI connected to int13
    Uint16   POLARITY:2;  // 3:2    pos/neg, or both triggered
    Uint16   rsvd2:12;    // 15:4   reserved
};

union XNMICR_REG {
    Uint16               all;
    struct XNMICR_BITS   bit;
};  

//
// External Interrupt Register File
//
struct XINTRUPT_REGS {
    union XINTCR_REG XINT1CR;
    union XINTCR_REG XINT2CR;
    union XINTCR_REG XINT3CR;
    union XINTCR_REG XINT4CR;
    union XINTCR_REG XINT5CR;
    union XINTCR_REG XINT6CR;
    union XINTCR_REG XINT7CR;
    union XNMICR_REG XNMICR;
    Uint16           XINT1CTR;
    Uint16           XINT2CTR;
    Uint16           rsvd[5];
    Uint16           XNMICTR;
};

//
// External Interrupt References & Function Declarations
//
extern volatile struct XINTRUPT_REGS XIntruptRegs;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif  // end of DSP2833x_XINTF_H definition

//
// End of file
//

