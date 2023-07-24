//###########################################################################
//
// FILE:    f28p65x_flash.h
//
// TITLE:   Definitions for the FLASH registers.
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

#ifndef F28P65X_FLASH_H
#define F28P65X_FLASH_H

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// FLASH Individual Register Bit Definitions:

struct FRDCNTL_BITS {                   // bits description
    Uint16 rsvd1:8;                     // 7:0 Reserved
    Uint16 RWAIT:4;                     // 11:8 Random Read Waitstate
    Uint16 rsvd2:4;                     // 15:12 Reserved
    Uint16 rsvd3:8;                     // 23:16 Reserved
    Uint16 rsvd4:4;                     // 27:24 Reserved
    Uint16 rsvd5:4;                     // 31:28 Reserved
};

union FRDCNTL_REG {
    Uint32  all;
    struct  FRDCNTL_BITS  bit;
};

struct FLPROT_BITS {                    // bits description
    Uint16 FLWEPROT:1;                  // 0 Flash write/erase protect bit.
    Uint16 rsvd1:15;                    // 15:1 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union FLPROT_REG {
    Uint32  all;
    struct  FLPROT_BITS  bit;
};

struct FRD_INTF_CTRL_BITS {             // bits description
    Uint16 PREFETCH_EN:1;               // 0 Prefetch Enable
    Uint16 DATA_CACHE_EN:1;             // 1 Data Cache Enable
    Uint16 rsvd1:14;                    // 15:2 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union FRD_INTF_CTRL_REG {
    Uint32  all;
    struct  FRD_INTF_CTRL_BITS  bit;
};

struct FLASH_CTRL_REGS {
    union   FRDCNTL_REG                      FRDCNTL;                      // Flash Read Control Register
    Uint16                                   rsvd1[2];                     // Reserved
    union   FLPROT_REG                       FLPROT;                       // Flash program/erase protect register
    Uint16                                   rsvd2[378];                   // Reserved
    union   FRD_INTF_CTRL_REG                FRD_INTF_CTRL;                // Flash Read Interface Control Register
};

struct ECC_ENABLE_BITS {                // bits description
    Uint16 ENABLE:4;                    // 3:0 Enable ECC
    Uint16 rsvd1:12;                    // 15:4 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union ECC_ENABLE_REG {
    Uint32  all;
    struct  ECC_ENABLE_BITS  bit;
};

struct FECC_CTRL_BITS {                 // bits description
    Uint16 ECC_TEST_EN:2;               // 1:0 Enable ECC Test Logic
    Uint16 rsvd1:14;                    // 15:2 Reserved
    Uint16 rsvd2:16;                    // 31:16 Reserved
};

union FECC_CTRL_REG {
    Uint32  all;
    struct  FECC_CTRL_BITS  bit;
};

struct FLASH_ECC_REGS {
    union   ECC_ENABLE_REG                   ECC_ENABLE;                   // ECC Enable
    Uint16                                   rsvd1[30];                    // Reserved
    union   FECC_CTRL_REG                    FECC_CTRL;                    // ECC Control
};

//---------------------------------------------------------------------------
// FLASH External References & Function Declarations:
//
#ifdef CPU1
extern volatile struct FLASH_CTRL_REGS Flash0CtrlRegs;
extern volatile struct FLASH_ECC_REGS Flash0EccRegs;
#endif
#ifdef CPU2
extern volatile struct FLASH_CTRL_REGS Flash0CtrlRegs;
extern volatile struct FLASH_ECC_REGS Flash0EccRegs;
#endif
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
