//#############################################################################
//
// FILE:   fsi_ex2_loopback_clacontrol_cla_shared.h
//
// TITLE:  CLA code to control FSI data frame transfers
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

#ifndef _FSI_EX2_LOOPBACK_CLACONTROL_CLA_SHARED_H_
#define _FSI_EX2_LOOPBACK_CLACONTROL_CLA_SHARED_H_

#ifdef __cplusplus
extern "C" {
#endif
//
// Included Files
//

//
// Defines
//

//
// Globals, User can modify these parameters as per usecase
//

//
// Globals, these are not config parameters, user are not required to edit them
//

extern volatile uint32_t fsiTxInt1Received;
extern volatile uint32_t fsiRxInt1Received;
extern uint32_t txTimeOutCntr, rxTimeOutCntr;

//
// Function Prototypes
//

//
// Globals
//
//Task 1 (C) Variables

//Task 2 (C) Variables

//Task 3 (C) Variables

//Task 4 (C) Variables

//Task 5 (C) Variables

//Task 6 (C) Variables

//Task 7 (C) Variables

//Task 8 (C) Variables

//Common (C) Variables

//
// Function Prototypes
//
//CLA C Tasks defined in fsi_ex2_loopback_clacontrol_cla.cla
__attribute__((interrupt))  void Cla1Task1();
__attribute__((interrupt))  void Cla1Task2();
__attribute__((interrupt))  void Cla1Task3();
__attribute__((interrupt))  void Cla1Task4();
__attribute__((interrupt))  void Cla1Task5();
__attribute__((interrupt))  void Cla1Task6();
__attribute__((interrupt))  void Cla1Task7();
__attribute__((interrupt))  void Cla1Task8();
#if defined(__TMS320C28XX__)
__attribute__((interrupt))  void Cla1Task8();
#else
__attribute__((interrupt("background")))  void Cla1Task8();
#endif

#ifdef __cplusplus
}
#endif // extern "C"
#endif //_FSI_EX2_LOOPBACK_CLACONTROL_CLA_SHARED_H_

//
// End of File
//
