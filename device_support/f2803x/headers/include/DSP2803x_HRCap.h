//###########################################################################
//
// FILE:   DSP2803x_HRCap.h
//
// TITLE:  DSP2803x High Resolution Capture Register Definitions
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
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

#ifndef DSP2803x_HRCAP_H
#define DSP2803x_HRCAP_H

#ifdef __cplusplus
extern "C" {
#endif

//
//  High-Resolution Capture Register Bit Definitions
//
struct HCCTL_BITS {            // bit     description
    Uint16   SOFTRESET:1;      // 0       Soft Reset
    Uint16   RISEINTE:1;       // 1       RISE Capture Interrupt Enable Bit
    Uint16   FALLINTE:1;       // 2       FALL Capture Interrupt Enable Bit
    Uint16   OVFINTE:1;        // 3       Counter Overflow Interrupt Enable Bit
    Uint16   rsvd1:4;          // 7:4     reserved
    Uint16   HCCAPCLKSEL:1;    // 8       Capture Clock Select Bit
    Uint16   rsvd2:7; 		   // 15:9	  reserved
};

union HCCTL_REG  {
    Uint16                       all;
    struct HCCTL_BITS            bit;
};

struct HCIFR_BITS {            // bit       description
    Uint16   INT:1;            // 0         Global Interrupt Flag
    Uint16   RISE:1;           // 1         RISE Capture Interrupt Flag
    Uint16   FALL:1;           // 2         FALL Capture Interrupt Flag
    Uint16   COUNTEROVF:1;     // 3         Counter Overflow Interrupt Flag
    Uint16   RISEOVF:1;  	   // 4         RISE Interrupt Overflow Event Flag
    Uint16   rsvd1:11;         // 15:5      reserved
};

union HCIFR_REG  {
    Uint16                       all;
    struct HCIFR_BITS            bit;
};

struct HCICLR_BITS {           // bit description
    Uint16   INT:1;            // 0   Global Interrupt Flag Clear Bit
    Uint16   RISE:1;           // 1   RISE Capture Interrupt Flag Clear Bit
    Uint16   FALL:1;           // 2   FALL Capture Interrupt Flag Clear Bit
    Uint16   COUNTEROVF:1;     // 3   Counter Overflow Interrupt Flag Clear Bit
    Uint16   RISEOVF:1;  	   // 4   RISE Int. Overflow Event Flag Clear Bit
    Uint16   rsvd1:11;         // 15:5 reserved
};

union HCICLR_REG  {
    Uint16                       all;
    struct HCICLR_BITS           bit;
};

struct HCIFRC_BITS {           //bit  description
    Uint16   rsvd1:1;          //0    reserved
    Uint16   RISE:1;           //1    RISE Capture Interrupt Flag Force Bit
    Uint16   FALL:1;           //2    FALL Capture Interrupt Flag Force Bit
    Uint16   COUNTEROVF:1;     //3    Counter Overflow Interrupt Flag Force Bit
    Uint16   RISEOVF:1;  	   //4    RISE Int. Overflow Event Flag Force Bit
    Uint16   rsvd2:11;         //15:5 reserved
};

union HCIFRC_REG  {
    Uint16                       all;
    struct HCIFRC_BITS           bit;
};

struct HRCAP_REGS {
    union  HCCTL_REG           HCCTL;
    union  HCIFR_REG           HCIFR;
    union  HCICLR_REG          HCICLR;
    union  HCIFRC_REG          HCIFRC;
    Uint16                     HCCOUNTER;
    Uint16                     rsvd1[4];
    Uint16                     rsvd2[7];
    Uint16                     HCCAPCNTRISE0;
    Uint16                     rsvd3;
    Uint16                     HCCAPCNTFALL0;
    Uint16                     rsvd4;
    Uint16                     rsvd5;
    Uint16                     rsvd6;
    Uint16                     rsvd7[2];
    Uint16                     HCCAPCNTRISE1;
    Uint16                     rsvd8;
    Uint16                     HCCAPCNTFALL1;
    Uint16                     rsvd9;
    Uint16                     rsvd10;
    Uint16                     rsvd11;
    Uint16                     rsvd12[2];
};

//
//  High Resolution Capture External References and Function Declarations
//
extern volatile struct HRCAP_REGS HRCap1Regs;
extern volatile struct HRCAP_REGS HRCap2Regs;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif  // end of DSP2803x_HRCAP_H definition

//
// End of file
//

