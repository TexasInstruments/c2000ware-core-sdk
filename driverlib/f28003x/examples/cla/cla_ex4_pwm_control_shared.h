//#############################################################################
//
// FILE:   cla_ex4_pwm_control_shared.h
//
// TITLE:  Controlling PWM output using CLA
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

#ifndef _CLA_EX4_PWMCONTROL_SHARED_H_
#define _CLA_EX4_PWMCONTROL_SHARED_H_

#ifdef __cplusplus
extern "C" {
#endif

//
// Included Files
//
#include "driverlib.h"
#include "device.h"

//
// Defines
//
#define EPWM1_FREQ          100000UL   // 100 KHz
#define EPWM4_FREQ          10000UL    // 10 KHz
#define EPWM1_PERIOD        (uint16_t)(DEVICE_SYSCLK_FREQ / (2 * EPWM1_FREQ))
#define EPWM4_PERIOD        (uint16_t)(DEVICE_SYSCLK_FREQ / EPWM4_FREQ)

//
// Globals
//
//Task 1 (C) Variables
extern float duty;

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
__attribute__((interrupt))  void Cla1Task1();
__attribute__((interrupt))  void Cla1Task2();
__attribute__((interrupt))  void Cla1Task3();
__attribute__((interrupt))  void Cla1Task4();
__attribute__((interrupt))  void Cla1Task5();
__attribute__((interrupt))  void Cla1Task6();
__attribute__((interrupt))  void Cla1Task7();
__attribute__((interrupt))  void Cla1Task8();

#ifdef __cplusplus
}
#endif // extern "C"
#endif //_CLA_EX4_PWMCONTROL_SHARED_H_

//
// End of File
//
