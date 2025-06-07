//###########################################################################
//
// FILE:    f280013x_otp.h
//
// TITLE:   Definitions for the OTP registers.
//
//###########################################################################
// $Copyright:
// Copyright (C) 2025 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef F280013X_OTP_H
#define F280013X_OTP_H

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// OTP Individual Register Bit Definitions:

struct UID_REGS {
    Uint32                                   UID_PSRAND0;                  // UID Psuedo-random 160 bit number
    Uint32                                   UID_PSRAND1;                  // UID Psuedo-random 160 bit number
    Uint32                                   UID_PSRAND2;                  // UID Psuedo-random 160 bit number
    Uint32                                   UID_PSRAND3;                  // UID Psuedo-random 160 bit number
    Uint32                                   UID_PSRAND4;                  // UID Psuedo-random 160 bit number
    Uint32                                   UID_UNIQUE0;                  // UID Unique 64 bit number
    Uint32                                   UID_UNIQUE1;                  // UID Unique 64 bit number
    Uint32                                   UID_CHECKSUM;                 // UID Checksum
};

//---------------------------------------------------------------------------
// OTP External References & Function Declarations:
//
extern volatile struct UID_REGS UidRegs;
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
