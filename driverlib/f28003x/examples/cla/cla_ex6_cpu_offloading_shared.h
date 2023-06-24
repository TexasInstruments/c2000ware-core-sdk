//#############################################################################
//
// FILE:   cla_ex6_cpu_offloading_shared.h
//
// TITLE:  Optimal offloading of control algorithms to CLA
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

#ifndef _CLA_EX6_CPUOFFLOADING_SHARED_H_
#define _CLA_EX6_CPUOFFLOADING_SHARED_H_

#ifdef __cplusplus
extern "C" {
#endif

//
// Included Files
//
#include "driverlib.h"
#include "device.h"

#if run_loop1_cla == 1
#include "DCLCLA.h"
#else
#include "DCLF32.h"
#endif

//
// Structure definitions
//

typedef struct {
    uint16_t loop1;
    uint16_t loop2;
}reference;

typedef struct {
    uint16_t loop1;
    uint16_t loop2;
}sensed;

typedef struct {
    float32_t loop1;
    float32_t loop2;
}control_out;

//
// Defines
//
#define EPWM1_FREQ          1000000UL   // 1 MHz
#define EPWM4_FREQ          200000UL    // 200 KHz
#define EPWM5_FREQ          20000UL     // 20 KHz
#define EPWM1_PERIOD        (uint16_t)(DEVICE_SYSCLK_FREQ / (2 * EPWM1_FREQ))
#define EPWM4_PERIOD        (uint16_t)(DEVICE_SYSCLK_FREQ / EPWM4_FREQ)
#define EPWM5_PERIOD        (uint16_t)(DEVICE_SYSCLK_FREQ / EPWM5_FREQ)

//
// Globals
//
extern volatile reference ref_data;
extern volatile sensed sense_data;
extern volatile control_out control_out_data;
#if run_loop1_cla == 1
extern volatile DCL_PI_CLA pi_loop1;
#else
extern volatile DCL_PI pi_loop1;
#endif
extern volatile float32_t duty, duty_loop1, duty_loop2;

//
// Loop1 control task defined in a shared file so that can be used both
// by CPU and CLA in order avoid code duplication
//
static inline void loop1_task(void)
{
    //
    // Read the oversampled input captured by 4 SOCs and calculate
    // the average
    //
    sense_data.loop1 = (ADC_readResult(ADCARESULT_BASE,ADC_SOC_NUMBER0) +
                        ADC_readResult(ADCARESULT_BASE,ADC_SOC_NUMBER1) +
                         ADC_readResult(ADCARESULT_BASE,ADC_SOC_NUMBER2) +
                          ADC_readResult(ADCARESULT_BASE,ADC_SOC_NUMBER3)) >> 2;

//
// Run the parallel form PI controller
//
#if run_loop1_cla == 1
    control_out_data.loop1 = DCL_runPI_L4(&pi_loop1, (ref_data.loop1 / 4096.0f),
                                          (sense_data.loop1 / 4096.0f));
#else
    control_out_data.loop1 = DCL_runPI_C3(&pi_loop1, __divf32(ref_data.loop1, 4096.0f),
                                          __divf32(sense_data.loop1, 4096.0f));
#endif

    //
    // Calculate the duty contribution based on the controller output with 20% weightage
    //
    duty_loop1 = 0.8f * control_out_data.loop1;

    //
    // Computing final duty value by summing up the contribution of both loops
    //
    duty = duty_loop1 + duty_loop2;

    //
    // Check for upper(0.9) and lower(0.1) saturation values
    //
    duty = (duty > 0.9f) ? 0.9f : duty;
    duty = (duty < 0.1f) ? 0.1f : duty;

    //
    // Write to the COMPA register
    //
    EPWM_setCounterCompareValue(EPWM1_BASE, EPWM_COUNTER_COMPARE_A,
                                (uint16_t)((1.0f - duty) * EPWM1_PERIOD + 0.5f));
}

//CLA C Tasks defined in Cla1Tasks_C.cla
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
#endif //_CLA_EX6_CPUOFFLOADING_SHARED_H_

//
// End of File
//
