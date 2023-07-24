//###########################################################################
//
// FILE:    f28p65x_aes_ss.h
//
// TITLE:   Definitions for the AES_SS registers.
//
//###########################################################################
// $Copyright:
// Copyright (C) 2022 Texas Instruments Incorporated - http://www.ti.com
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

#ifndef F28P65X_AES_SS_H
#define F28P65X_AES_SS_H

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// AES_SS Individual Register Bit Definitions:

struct AES_GLB_INT_FLG_BITS {           // bits description
    Uint16 INT_FLG:1;                   // 0 Global Interrupt Flag for AES Interrupt
    Uint16 rsvd1:15;                    // 15:1 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union AES_GLB_INT_FLG_REG {
    Uint32  all;
    struct  AES_GLB_INT_FLG_BITS  bit;
};

struct AES_GLB_INT_CLR_BITS {           // bits description
    Uint16 INT_FLG_CLR:1;               // 0 Global Interrupt flag clear for AES Interrupt
    Uint16 rsvd1:15;                    // 15:1 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union AES_GLB_INT_CLR_REG {
    Uint32  all;
    struct  AES_GLB_INT_CLR_BITS  bit;
};

struct AES_SS_REGS {
    Uint16                                   rsvd1[2];                     // Reserved
    union   AES_GLB_INT_FLG_REG              AES_GLB_INT_FLG;              // AES Global Interrupt Flag Register
    union   AES_GLB_INT_CLR_REG              AES_GLB_INT_CLR;              // AES Global Interrupt Clear Register
};

//---------------------------------------------------------------------------
// AES_SS External References & Function Declarations:
//
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
