#ifndef _CLA_SDFM_FILTER_SYNCH_SHARED_H_
#define _CLA_SDFM_FILTER_SYNCH_SHARED_H_
//#############################################################################
//
// FILE:   sdfm_ex1_filter_cla_sync_shared_cpu2.h
//
// TITLE:  SDFM filter sync CLA
//
//  Group:            C2000
//  Target Family:    f2838x
//
//#############################################################################
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
//#############################################################################

//
// Included Files
//
#include "f28x_project.h"
#include "f2838x_cla_defines.h"
#include "f2838x_cla_typedefs.h"
#include "f2838x_sdfm.h"

#ifdef __cplusplus
extern "C" {
#endif

//
// Defines
//
#define FLT_MAX              1.1754944e+38
#define FLT_MIN              1.1754944e-38
#define NUM_DATA             8
#define TO_CPU1              0
#define TO_CPU2              1
#define CONNECT_TO_CLA1      0
#define CONNECT_TO_DMA       1
#define CONNECT_TO_CLA2      2
#define ENABLE               1
#define DISABLE              0
#define MAX_SAMPLES          1024
#define SDFM_INT_MASK        0x8000F000U

#define CONNECT_SD1(x)    EALLOW; DevCfgRegs.CPUSEL4.bit.SD1 = x; EDIS
#define CONNECT_SD2(x)    EALLOW; DevCfgRegs.CPUSEL4.bit.SD2 = x; EDIS

//
// Globals
//
extern short  Filter1_Result_CPU2[MAX_SAMPLES];
extern short  Filter2_Result_CPU2[MAX_SAMPLES];
extern short  Filter3_Result_CPU2[MAX_SAMPLES];
extern short  Filter4_Result_CPU2[MAX_SAMPLES];

// The following are symbols defined in the CLA code
// Including them in the shared header file makes them
// .global and the main CPU can make use of them.

//
// CLA C Tasks
//
__interrupt void Cla1Task1();
__interrupt void Cla1Task2();
__interrupt void Cla1Task3();
__interrupt void Cla1Task4();
__interrupt void Cla1Task5();
__interrupt void Cla1Task6();
__interrupt void Cla1Task7();
__interrupt void Cla1Task8();

__interrupt void cla1Isr1();
__interrupt void cla1Isr2();
__interrupt void cla1Isr3();
__interrupt void cla1Isr4();
__interrupt void cla1Isr5();
__interrupt void cla1Isr6();
__interrupt void cla1Isr7();
__interrupt void cla1Isr8();

//
// Linker command variables
//
extern Uint32 Cla1funcsLoadStart;
extern Uint32 Cla1funcsLoadEnd;
extern Uint32 Cla1funcsRunStart;
extern Uint32 Cla1funcsLoadSize;
extern uint32_t Cla1ConstLoadStart;
extern uint32_t Cla1ConstLoadEnd;
extern uint32_t Cla1ConstRunStart;
extern uint32_t Cla1ConstLoadSize;

#ifdef __cplusplus
}
#endif // extern "C"

#endif //end of _CLA_SDFM_FILTER_SYNCH_SHARED_H_ definition

//
// End of file
//
