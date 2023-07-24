//###########################################################################
//
// FILE:    hw_aes_ss.h
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

#ifndef HW_AES_SS_H
#define HW_AES_SS_H

//*************************************************************************************************
//
// The following are defines for the AES_SS register offsets
//
//*************************************************************************************************
#define AES_SS_O_AES_GLB_INT_FLG   0x2U   // AES Global Interrupt Flag Register
#define AES_SS_O_AES_GLB_INT_CLR   0x4U   // AES Global Interrupt Clear Register


//*************************************************************************************************
//
// The following are defines for the bit fields in the AES_GLB_INT_FLG register
//
//*************************************************************************************************
#define AES_SS_AES_GLB_INT_FLG_INT_FLG   0x1U   // Global Interrupt Flag for AES Interrupt

//*************************************************************************************************
//
// The following are defines for the bit fields in the AES_GLB_INT_CLR register
//
//*************************************************************************************************
#define AES_SS_AES_GLB_INT_CLR_INT_FLG_CLR   0x1U   // Global Interrupt flag clear for AES
                                                    // Interrupt



#endif
