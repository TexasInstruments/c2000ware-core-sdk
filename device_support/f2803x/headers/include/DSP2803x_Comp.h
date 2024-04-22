//###########################################################################
//
// FILE:   DSP2803x_Comp.h
//
// TITLE:  DSP2803x Device Comparator Register Definitions
//
//###########################################################################
// $TI Release: $
// $Release Date: $
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

#ifndef DSP2803x_COMP_H
#define DSP2803x_COMP_H

#ifdef __cplusplus
extern "C" {
#endif

//
//  Comparator Register Bit Definitions
//
struct COMPCTL_BITS {            // bit       description
    Uint16   COMPDACEN:1;        // 0         Comparator/DAC  Enable
    
    //
    // 1         Source select for comparator inverting input
    //
    Uint16   COMPSOURCE:1;       
    
    Uint16   CMPINV:1;           // 2         Invert select for Comparator
    
    //
    // 7:03      Qualification Period for synchronized output of the comparator
    //
    Uint16   QUALSEL:5;          
    
    //
    // 8         Synchronization select for output of the comparator
    //
    Uint16   SYNCSEL:1;          
    
    Uint16   rsvd1:7;            // 15:09     reserved
};

union COMPCTL_REG  {
    Uint16                         all;
    struct COMPCTL_BITS            bit;
};

struct COMPSTS_BITS {            // bit   description
    Uint16   COMPSTS:1;          // 0     Logical latched value of comparator
    Uint16   rsvd1:15;           // 15:01 reserved
};

union COMPSTS_REG  {
    Uint16                         all;
    struct COMPSTS_BITS            bit;
};

struct DACCTL_BITS {            // bits      description
    Uint16   DACSOURCE:1;       // 0         DAC source control bits.
    Uint16   RAMPSOURCE:4;      // 4:01      Ramp generator source control bits
    Uint16   rsvd1:9;           // 13:05     reserved
    Uint16   FREE_SOFT:2;       // 15:14     Debug Mode Bit
};

union DACCTL_REG  {
    Uint16                         all;
    struct DACCTL_BITS             bit;
};

struct DACVAL_BITS {            // bit       description
    Uint16   DACVAL:10;         // 9:00      DAC Value bit
    Uint16   rsvd1:6;           // 15:10     reserved
};

union DACVAL_REG  {
    Uint16                         all;
    struct DACVAL_BITS             bit;
};

//
//  Comparator Register Definitions
//
struct COMP_REGS {
    union  COMPCTL_REG         COMPCTL;
    Uint16                     rsvd1;
    union  COMPSTS_REG         COMPSTS;
    Uint16                     rsvd2;
    union  DACCTL_REG          DACCTL;
    Uint16                     rsvd3;
    union  DACVAL_REG          DACVAL;
    Uint16                     rsvd4;
    Uint16                     RAMPMAXREF_ACTIVE;
    Uint16                     rsvd5;
    Uint16                     RAMPMAXREF_SHDW;
    Uint16                     rsvd6;
    Uint16                     RAMPDECVAL_ACTIVE;
    Uint16                     rsvd7;
    Uint16                     RAMPDECVAL_SHDW;
    Uint16                     rsvd8;
    Uint16                     RAMPSTS;
    Uint16                     rsvd9[3];
};

//
//  Comparator External References and Function Declarations
//
extern volatile struct COMP_REGS Comp1Regs;
extern volatile struct COMP_REGS Comp2Regs;
extern volatile struct COMP_REGS Comp3Regs;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif  // end of DSP2803x_COMP_H definition

//
// End of file
//

