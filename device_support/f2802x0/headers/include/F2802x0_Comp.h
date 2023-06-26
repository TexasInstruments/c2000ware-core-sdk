//###########################################################################
//
// FILE:   F2802x0_Comp.h
//
// TITLE:  F2802x0 Device Comparator Register Definitions
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:
// Copyright (C) 2009-2023 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef F2802x0_COMP_H
#define F2802x0_COMP_H

#ifdef __cplusplus
extern "C" {
#endif

//
//  Comparator Register Bit Definitions
//
struct COMPCTL_BITS
{                                  // bit       description
    uint16_t   COMPDACEN:1;        // 0         Comparator/DAC  Enable
    
    //
    // 1         Source select for comparator inverting input
    //
    uint16_t   COMPSOURCE:1;
    
    uint16_t   CMPINV:1;           // 2         Invert select for Comparator
    
    //
    // 7:03      Qualification Period for synchronized output of the comparator
    //
    uint16_t   QUALSEL:5;          
    
    //
    // 8         Synchronization select for output of the comparator
    //
    uint16_t   SYNCSEL:1;
    
    uint16_t   rsvd1:7;            // 15:09     reserved
};

union COMPCTL_REG
{
    uint16_t                        all;
    struct COMPCTL_BITS             bit;
};

struct COMPSTS_BITS
{                          // bit       description
    uint16_t   COMPSTS:1;  // 0         Logical latched value of the comparator
    uint16_t   rsvd1:15;   // 15:01     reserved
};

union COMPSTS_REG
{
    uint16_t                         all;
    struct COMPSTS_BITS              bit;
};

struct DACCTL_BITS 
{            
                                   // bits      description
    uint16_t   DACSOURCE:1;        // 0         DAC source control bits.
    uint16_t   RAMPSOURCE:4;       // 4:01      Ramp generator source control 
                                   //           bits
    uint16_t   rsvd1:9;            // 13:05     reserved
    uint16_t   FREE_SOFT:2;        // 15:14     Debug Mode Bit
};

union DACCTL_REG  
{
    uint16_t                       all;
    struct DACCTL_BITS             bit;
};

struct DACVAL_BITS
{                                  // bit       description
    uint16_t   DACVAL:10;          // 9:00      DAC Value bit
    uint16_t   rsvd1:6;            // 15:10     reserved
};

union DACVAL_REG
{
    uint16_t                         all;
    struct DACVAL_BITS               bit;
};

//
//  Comparator Register Definitions
//
struct COMP_REGS
{
    union  COMPCTL_REG         COMPCTL;
    uint16_t                   rsvd1;
    union  COMPSTS_REG         COMPSTS;
    uint16_t                   rsvd2;
    union  DACCTL_REG          DACCTL;
    uint16_t                   rsvd3;
    union  DACVAL_REG          DACVAL;
    uint16_t                   rsvd4;
    uint16_t                   RAMPMAXREF_ACTIVE;
    uint16_t                   rsvd5;
    uint16_t                   RAMPMAXREF_SHDW;
    uint16_t                   rsvd6;
    uint16_t                   RAMPDECVAL_ACTIVE;
    uint16_t                   rsvd7;
    uint16_t                   RAMPDECVAL_SHDW;
    uint16_t                   rsvd8;
    uint16_t                   RAMPSTS;
    uint16_t                   rsvd9[15];
};

//
//  Comparator External References and Function Declarations
//
extern volatile struct COMP_REGS Comp1Regs;
extern volatile struct COMP_REGS Comp2Regs;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif  // end of F2802x0_COMP_H definition

//
// End of file
//

