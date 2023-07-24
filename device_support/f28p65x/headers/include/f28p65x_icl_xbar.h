//###########################################################################
//
// FILE:    f28p65x_icl_xbar.h
//
// TITLE:   Definitions for the ICL_XBAR registers.
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

#ifndef F28P65X_ICL_XBAR_H
#define F28P65X_ICL_XBAR_H

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// ICL_XBAR Individual Register Bit Definitions:

struct ICLINPUTSELECTLOCK_BITS {        // bits description
    Uint16 ICL1SELECT:1;                // 0 Lock bit for ICL1SELECT Register
    Uint16 ICL2SELECT:1;                // 1 Lock bit for ICL2SELECT Register
    Uint16 ICL3SELECT:1;                // 2 Lock bit for ICL3SELECT Register
    Uint16 ICL4SELECT:1;                // 3 Lock bit for ICL4SELECT Register
    Uint16 ICL5SELECT:1;                // 4 Lock bit for ICL5SELECT Register
    Uint16 ICL6SELECT:1;                // 5 Lock bit for ICL6SELECT Register
    Uint16 ICL7SELECT:1;                // 6 Lock bit for ICL7SELECT Register
    Uint16 ICL8SELECT:1;                // 7 Lock bit for ICL8SELECT Register
    Uint16 ICL9SELECT:1;                // 8 Lock bit for ICL9SELECT Register
    Uint16 ICL10SELECT:1;               // 9 Lock bit for ICL10SELECT Register
    Uint16 ICL11SELECT:1;               // 10 Lock bit for ICL11SELECT Register
    Uint16 ICL12SELECT:1;               // 11 Lock bit for ICL12SELECT Register
    Uint16 ICL13SELECT:1;               // 12 Lock bit for ICL13SELECT Register
    Uint16 ICL14SELECT:1;               // 13 Lock bit for ICL14SELECT Register
    Uint16 ICL15SELECT:1;               // 14 Lock bit for ICL15SELECT Register
    Uint16 ICL16SELECT:1;               // 15 Lock bit for ICL16SELECT Register
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union ICLINPUTSELECTLOCK_REG {
    Uint32  all;
    struct  ICLINPUTSELECTLOCK_BITS  bit;
};

struct ICL_XBAR_REGS {
    Uint16                                   ICL1SELECT;                   // ICL1SELECT Input Select Register
    Uint16                                   ICL2SELECT;                   // ICL2SELECT Input Select Register
    Uint16                                   ICL3SELECT;                   // ICL3SELECT Input Select Register
    Uint16                                   ICL4SELECT;                   // ICL4SELECT Input Select Register
    Uint16                                   ICL5SELECT;                   // ICL5SELECT Input Select Register
    Uint16                                   ICL6SELECT;                   // ICL6SELECT Input Select Register
    Uint16                                   ICL7SELECT;                   // ICL7SELECT Input Select Register
    Uint16                                   ICL8SELECT;                   // ICL8SELECT Input Select Register
    Uint16                                   ICL9SELECT;                   // ICL9SELECT Input Select Register
    Uint16                                   ICL10SELECT;                  // ICL10SELECT Input Select Register
    Uint16                                   ICL11SELECT;                  // ICL11SELECT Input Select Register
    Uint16                                   ICL12SELECT;                  // ICL12SELECT Input Select Register
    Uint16                                   ICL13SELECT;                  // ICL13SELECT Input Select Register
    Uint16                                   ICL14SELECT;                  // ICL14SELECT Input Select Register
    Uint16                                   ICL15SELECT;                  // ICL15SELECT Input Select Register
    Uint16                                   ICL16SELECT;                  // ICL16SELECT Input Select Register
    Uint16                                   rsvd1[14];                    // Reserved
    union   ICLINPUTSELECTLOCK_REG           ICLINPUTSELECTLOCK;           // Input Select Lock Register
};

//---------------------------------------------------------------------------
// ICL_XBAR External References & Function Declarations:
//
#ifdef CPU1
extern volatile struct ICL_XBAR_REGS IclXbarRegs;
#endif
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
