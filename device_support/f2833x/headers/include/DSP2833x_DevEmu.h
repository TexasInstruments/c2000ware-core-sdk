// TI File $Revision: /main/4 $
// Checkin $Date: April 15, 2009   10:05:17 $
//###########################################################################
//
// FILE:   DSP2833x_DevEmu.h
//
// TITLE:  DSP2833x Device Emulation Register Definitions.
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

#ifndef DSP2833x_DEV_EMU_H
#define DSP2833x_DEV_EMU_H

#ifdef __cplusplus
extern "C" {
#endif

//
// Device Emulation Register Bit Definitions:
//

//
// Device Configuration Register Bit Definitions
//
struct DEVICECNF_BITS  {      // bits  description
    Uint16 rsvd1:3;           // 2:0   reserved
    Uint16 VMAPS:1;           // 3     VMAP Status
    Uint16 rsvd2:1;           // 4     reserved
    Uint16 XRSn:1;            // 5     XRSn Signal Status
    Uint16 rsvd3:10;          // 15:6
    Uint16 rsvd4:3;           // 18:16
    Uint16 ENPROT:1;          // 19    Enable/Disable pipeline protection
    Uint16 rsvd5:7;           // 26:20 reserved
    Uint16 TRSTN:1;           // 27    Status of TRSTn signal
    Uint16 rsvd6:4;           // 31:28 reserved
};

union DEVICECNF_REG {
    Uint32                 all;
    struct DEVICECNF_BITS  bit;
};

//
// CLASSID
//
struct CLASSID_BITS   {   // bits  description
    Uint16 CLASSNO:8;     // 7:0   Class Number
    Uint16 PARTTYPE:8;    // 15:8  Part Type
};

union CLASSID_REG {
    Uint16               all;
    struct CLASSID_BITS  bit;
};

struct DEV_EMU_REGS {
    union DEVICECNF_REG DEVICECNF;  // device configuration
    union CLASSID_REG   CLASSID;    // Class ID
    Uint16              REVID;      // Device ID
    Uint16              PROTSTART;  // Write-Read protection start
    Uint16              PROTRANGE;  // Write-Read protection range
    Uint16              rsvd2[202];
};

//
// PARTID
//
struct PARTID_BITS   {  // bits  description
    Uint16 PARTNO:8;     // 7:0   Part Number
    Uint16 PARTTYPE:8;   // 15:8  Part Type
};

union PARTID_REG {
    Uint16               all;
    struct PARTID_BITS   bit;
};

struct PARTID_REGS {
    union PARTID_REG PARTID; // Part ID
};

//
// Device Emulation Register References & Function Declarations
//
extern volatile struct DEV_EMU_REGS DevEmuRegs;
extern volatile struct PARTID_REGS PartIdRegs;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif  // end of DSP2833x_DEV_EMU_H definition

//
// End of file
//

