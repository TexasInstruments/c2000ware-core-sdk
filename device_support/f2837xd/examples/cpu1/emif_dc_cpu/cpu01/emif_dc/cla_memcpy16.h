//###########################################################################
//
// FILE:   cla_memcpy16.h
//
// TITLE:  CLA and CPU shared variables and constants
//
//###########################################################################
//
// $Release Date: $
// $Copyright:
// Copyright (C) 2013-2024 Texas Instruments Incorporated - http://www.ti.com/
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
#ifndef CLA_MEMCPY16_H
#define CLA_MEMCPY16_H

#include "F28x_Project.h"
#include "F2837xD_Cla_defines.h"

#ifdef __cplusplus
extern "C" {
#endif

//
// Shared message variables between CPU and CLA
//   Cla16bWords: Number of 16b words to copy
//   ClaSrcAddr: Source address for copy
//   ClaDstAddr: Destination address for copy
//
  extern Uint32 Cla16bWords;
  extern Uint16 ClaSrcAddr;
  extern Uint16 ClaDstAddr;

// The following are symbols defined in the CLA assembly code
// Including them in the shared header file makes them 
// .global and the main CPU can make use of them. 

  extern Uint32 Cla1Task1;
  extern Uint32 Cla1Task2;
  extern Uint32 Cla1Task3;
  extern Uint32 Cla1Task4;
  extern Uint32 Cla1Task5;
  extern Uint32 Cla1Task6;
  extern Uint32 Cla1Task7;
  extern Uint32 Cla1Task8;
  extern Uint32 Cla1Prog_Start;
  extern Uint32 Cla1T1End;
  extern Uint32 Cla1T2End;
  extern Uint32 Cla1T3End;
  extern Uint32 Cla1T4End;
  extern Uint32 Cla1T5End;
  extern Uint32 Cla1T6End;
  extern Uint32 Cla1T7End;
  extern Uint32 Cla1T8End;

#ifdef __cplusplus
}
#endif /* extern "C" */


#endif  // end of CLA_SHARED definition
