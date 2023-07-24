//###########################################################################
//
// FILE:    f28p65x_mindb_xbar.h
//
// TITLE:   Definitions for the MINDB_XBAR registers.
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

#ifndef F28P65X_MINDB_XBAR_H
#define F28P65X_MINDB_XBAR_H

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// MINDB_XBAR Individual Register Bit Definitions:

struct MDLINPUTSELECTLOCK_BITS {        // bits description
    Uint16 MDL1SELECT:1;                // 0 Lock bit for MDL1SELECT Register
    Uint16 MDL2SELECT:1;                // 1 Lock bit for MDL2SELECT Register
    Uint16 MDL3SELECT:1;                // 2 Lock bit for MDL3SELECT Register
    Uint16 MDL4SELECT:1;                // 3 Lock bit for MDL4SELECT Register
    Uint16 MDL5SELECT:1;                // 4 Lock bit for MDL5SELECT Register
    Uint16 MDL6SELECT:1;                // 5 Lock bit for MDL6SELECT Register
    Uint16 MDL7SELECT:1;                // 6 Lock bit for MDL7SELECT Register
    Uint16 MDL8SELECT:1;                // 7 Lock bit for MDL8SELECT Register
    Uint16 MDL9SELECT:1;                // 8 Lock bit for MDL9SELECT Register
    Uint16 MDL10SELECT:1;               // 9 Lock bit for MDL10SELECT Register
    Uint16 MDL11SELECT:1;               // 10 Lock bit for MDL11SELECT Register
    Uint16 MDL12SELECT:1;               // 11 Lock bit for MDL12SELECT Register
    Uint16 MDL13SELECT:1;               // 12 Lock bit for MDL13SELECT Register
    Uint16 MDL14SELECT:1;               // 13 Lock bit for MDL14SELECT Register
    Uint16 MDL15SELECT:1;               // 14 Lock bit for MDL15SELECT Register
    Uint16 MDL16SELECT:1;               // 15 Lock bit for MDL16SELECT Register
    Uint16 rsvd1:16;                    // 31:16 Reserved
};

union MDLINPUTSELECTLOCK_REG {
    Uint32  all;
    struct  MDLINPUTSELECTLOCK_BITS  bit;
};

struct MDL_XBAR_REGS {
    Uint16                                   MDL1SELECT;                   // MDL1SELECT Input Select Register
    Uint16                                   MDL2SELECT;                   // MDL2SELECT Input Select Register
    Uint16                                   MDL3SELECT;                   // MDL3SELECT Input Select Register
    Uint16                                   MDL4SELECT;                   // MDL4SELECT Input Select Register
    Uint16                                   MDL5SELECT;                   // MDL5SELECT Input Select Register
    Uint16                                   MDL6SELECT;                   // MDL6SELECT Input Select Register
    Uint16                                   MDL7SELECT;                   // MDL7SELECT Input Select Register
    Uint16                                   MDL8SELECT;                   // MDL8SELECT Input Select Register
    Uint16                                   MDL9SELECT;                   // MDL9SELECT Input Select Register
    Uint16                                   MDL10SELECT;                  // MDL10SELECT Input Select Register
    Uint16                                   MDL11SELECT;                  // MDL11SELECT Input Select Register
    Uint16                                   MDL12SELECT;                  // MDL12SELECT Input Select Register
    Uint16                                   MDL13SELECT;                  // MDL13SELECT Input Select Register
    Uint16                                   MDL14SELECT;                  // MDL14SELECT Input Select Register
    Uint16                                   MDL15SELECT;                  // MDL15SELECT Input Select Register
    Uint16                                   MDL16SELECT;                  // MDL16SELECT Input Select Register
    Uint16                                   rsvd1[14];                    // Reserved
    union   MDLINPUTSELECTLOCK_REG           MDLINPUTSELECTLOCK;           // Input Select Lock Register
};

//---------------------------------------------------------------------------
// MINDB_XBAR External References & Function Declarations:
//
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
