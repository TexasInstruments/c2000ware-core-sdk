//#############################################################################
//
// FILE:   sdfm_ex2_filter_sync_claread_shared.h
//
// TITLE:  SDFM filter sync CLA
//
// This header file contains defines, variables and prototypes that are shared
// among the C28x and the CLA
//
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2023 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef _CLA_SDFM_FILTER_SYNCH_SHARED_H_
#define _CLA_SDFM_FILTER_SYNCH_SHARED_H_

#ifdef __cplusplus
extern "C" {
#endif

//
// Defines
//
#define MAX_SAMPLES          1024

//
// Globals
//
extern int16_t  filter1Result[MAX_SAMPLES];
extern int16_t  filter2Result[MAX_SAMPLES];
extern int16_t  filter3Result[MAX_SAMPLES];
extern int16_t  filter4Result[MAX_SAMPLES];

//
// The following are symbols defined in the CLA code
// Including them in the shared header file makes them
// .global and the main CPU can make use of them.
//
//

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
// Linker Defined variables
//
extern uint32_t Cla1ProgRunStart, Cla1ProgLoadStart, Cla1ProgLoadSize;
extern uint32_t Cla1ConstRunStart, Cla1ConstLoadStart, Cla1ConstLoadSize;

#ifdef __cplusplus
}
#endif // extern "C"

#endif //end of _CLA_SDFM_FILTER_SYNCH_SHARED_H_ definition

//
// End of file
//
