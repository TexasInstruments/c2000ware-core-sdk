//###########################################################################
//
// FILE:   f28p65x_sdfm_defines.h
//
// TITLE:  #defines used in sdfm examples
//
//###########################################################################
//
//
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

#ifndef F28P65x_SDFM_DEFINES_H
#define F28P65x_SDFM_DEFINES_H

#ifdef __cplusplus
extern "C" {
#endif

//
// Defines for backward compatibility
// The registers in f28p65x have been renamed from prior devices to make these
// more intuitive & easy to use. Following macros are being added for
// maintaining backward compatibility as a result code ported from prior
// devices can execute as-is.
//
#define IFH1  FLT1_FLG_CEVT1
#define IFH2  FLT2_FLG_CEVT1
#define IFH3  FLT3_FLG_CEVT1
#define IFH4  FLT4_FLG_CEVT1

#define IFL1  FLT1_FLG_CEVT2
#define IFL2  FLT2_FLG_CEVT2
#define IFL3  FLT3_FLG_CEVT2
#define IFL4  FLT4_FLG_CEVT2

#define IEH   EN_CEVT1
#define IEL   EN_CEVT2

#define SDCMPH1 SDFLT1CMPH1
#define SDCMPH2 SDFLT2CMPH1
#define SDCMPH3 SDFLT3CMPH1
#define SDCMPH4 SDFLT4CMPH1

#define SDCMPL1 SDFLT1CMPL1
#define SDCMPL2 SDFLT2CMPL1
#define SDCMPL3 SDFLT3CMPL1
#define SDCMPL4 SDFLT4CMPL1

#define SDCMPHZ1  SDFLT1CMPHZ
#define SDCMPHZ2  SDFLT2CMPHZ
#define SDCMPHZ3  SDFLT3CMPHZ
#define SDCMPHZ4  SDFLT4CMPHZ

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif   // - end of F28P65x_SDFM_DEFINES_H

//
// End of file
//
