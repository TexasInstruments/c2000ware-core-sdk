//###########################################################################
//
// FILE:    hw_trigxbar.h
//
// TITLE:   Definitions for the XBAR registers.
//
//###########################################################################
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
//###########################################################################

#ifndef HW_TRIGXBAR_H
#define HW_TRIGXBAR_H

//*****************************************************************************
//
// The following are defines for the XBAR register offsets
//
//*****************************************************************************
#define XBAR_O_SYNCSELECT         0x0U         // Sync Input and Output Select
                                               // Register
#define XBAR_O_ADCSOCOUTSELECT    0x2U         // External ADC (Off Chip) SOC
                                               // Select Register
#define XBAR_O_SYNCSOCLOCK        0x4U         // SYNCSEL and EXTADCSOC Select
                                               // Lock register

//*****************************************************************************
//
// The following are defines for the bit fields in the SYNCSELECT register
//
//*****************************************************************************
#define XBAR_SYNCSELECT_EPWM4SYNCIN_S  0U
#define XBAR_SYNCSELECT_EPWM4SYNCIN_M  0x7U         // Selects Sync Input Source for
                                               // EPWM4
#define XBAR_SYNCSELECT_EPWM7SYNCIN_S  3U
#define XBAR_SYNCSELECT_EPWM7SYNCIN_M  0x38U        // Selects Sync Input Source for
                                               // EPWM7
#define XBAR_SYNCSELECT_EPWM10SYNCIN_S  6U
#define XBAR_SYNCSELECT_EPWM10SYNCIN_M  0x1C0U       // Selects Sync Input Source for
                                               // EPWM10
#define XBAR_SYNCSELECT_ECAP1SYNCIN_S  9U
#define XBAR_SYNCSELECT_ECAP1SYNCIN_M  0xE00U       // Selects Sync Input Source for
                                               // ECAP1
#define XBAR_SYNCSELECT_ECAP4SYNCIN_S  12U
#define XBAR_SYNCSELECT_ECAP4SYNCIN_M  0x7000U      // Selects Sync Input Source for
                                               // ECAP4
#define XBAR_SYNCSELECT_ECAP7SYNCIN_S  16U
#define XBAR_SYNCSELECT_ECAP7SYNCIN_M  0xF0000U     // Selects Sync Input Source for
                                               // ECAP7
#define XBAR_SYNCSELECT_EPWM13SYNCIN_S  20U
#define XBAR_SYNCSELECT_EPWM13SYNCIN_M  0xF00000U    // Selects Sync Input Source for
                                               // EPWM13
#define XBAR_SYNCSELECT_SYNCOUT1_S  24U
#define XBAR_SYNCSELECT_SYNCOUT1_M  0x7000000U   // Select Syncout Source
#define XBAR_SYNCSELECT_SYNCOUT_S  27U
#define XBAR_SYNCSELECT_SYNCOUT_M  0x18000000U  // Select Syncout Source
#define XBAR_SYNCSELECT_EPWM1SYNCIN_S  29U
#define XBAR_SYNCSELECT_EPWM1SYNCIN_M  0xE0000000U  // Selects Sync Input Source for
                                               // EPWM1

//*****************************************************************************
//
// The following are defines for the bit fields in the ADCSOCOUTSELECT register
//
//*****************************************************************************
#define XBAR_ADCSOCOUTSELECT_PWM1SOCAEN  0x1U         // PWM1SOCAEN Enable for
                                               // ADCSOCAOn
#define XBAR_ADCSOCOUTSELECT_PWM2SOCAEN  0x2U         // PWM2SOCAEN Enable for
                                               // ADCSOCAOn
#define XBAR_ADCSOCOUTSELECT_PWM3SOCAEN  0x4U         // PWM3SOCAEN Enable for
                                               // ADCSOCAOn
#define XBAR_ADCSOCOUTSELECT_PWM4SOCAEN  0x8U         // PWM4SOCAEN Enable for
                                               // ADCSOCAOn
#define XBAR_ADCSOCOUTSELECT_PWM5SOCAEN  0x10U        // PWM5SOCAEN Enable for
                                               // ADCSOCAOn
#define XBAR_ADCSOCOUTSELECT_PWM6SOCAEN  0x20U        // PWM6SOCAEN Enable for
                                               // ADCSOCAOn
#define XBAR_ADCSOCOUTSELECT_PWM7SOCAEN  0x40U        // PWM7SOCAEN Enable for
                                               // ADCSOCAOn
#define XBAR_ADCSOCOUTSELECT_PWM8SOCAEN  0x80U        // PWM8SOCAEN Enable for
                                               // ADCSOCAOn
#define XBAR_ADCSOCOUTSELECT_PWM9SOCAEN  0x100U       // PWM9SOCAEN Enable for
                                               // ADCSOCAOn
#define XBAR_ADCSOCOUTSELECT_PWM10SOCAEN  0x200U       // PWM10SOCAEN Enable for
                                               // ADCSOCAOn
#define XBAR_ADCSOCOUTSELECT_PWM11SOCAEN  0x400U       // PWM11SOCAEN Enable for
                                               // ADCSOCAOn
#define XBAR_ADCSOCOUTSELECT_PWM12SOCAEN  0x800U       // PWM12SOCAEN Enable for
                                               // ADCSOCAOn
#define XBAR_ADCSOCOUTSELECT_PWM13SOCAEN  0x1000U      // PWM13SOCAEN Enable for
                                               // ADCSOCAOn
#define XBAR_ADCSOCOUTSELECT_PWM14SOCAEN  0x2000U      // PWM14SOCAEN Enable for
                                               // ADCSOCAOn
#define XBAR_ADCSOCOUTSELECT_PWM15SOCAEN  0x4000U      // PWM15SOCAEN Enable for
                                               // ADCSOCAOn
#define XBAR_ADCSOCOUTSELECT_PWM16SOCAEN  0x8000U      // PWM16SOCAEN Enable for
                                               // ADCSOCAOn
#define XBAR_ADCSOCOUTSELECT_PWM1SOCBEN  0x10000U     // PWM1SOCBEN Enable for
                                               // ADCSOCBOn
#define XBAR_ADCSOCOUTSELECT_PWM2SOCBEN  0x20000U     // PWM2SOCBEN Enable for
                                               // ADCSOCBOn
#define XBAR_ADCSOCOUTSELECT_PWM3SOCBEN  0x40000U     // PWM3SOCBEN Enable for
                                               // ADCSOCBOn
#define XBAR_ADCSOCOUTSELECT_PWM4SOCBEN  0x80000U     // PWM4SOCBEN Enable for
                                               // ADCSOCBOn
#define XBAR_ADCSOCOUTSELECT_PWM5SOCBEN  0x100000U    // PWM5SOCBEN Enable for
                                               // ADCSOCBOn
#define XBAR_ADCSOCOUTSELECT_PWM6SOCBEN  0x200000U    // PWM6SOCBEN Enable for
                                               // ADCSOCBOn
#define XBAR_ADCSOCOUTSELECT_PWM7SOCBEN  0x400000U    // PWM7SOCBEN Enable for
                                               // ADCSOCBOn
#define XBAR_ADCSOCOUTSELECT_PWM8SOCBEN  0x800000U    // PWM8SOCBEN Enable for
                                               // ADCSOCBOn
#define XBAR_ADCSOCOUTSELECT_PWM9SOCBEN  0x1000000U   // PWM9SOCBEN Enable for
                                               // ADCSOCBOn
#define XBAR_ADCSOCOUTSELECT_PWM10SOCBEN  0x2000000U   // PWM10SOCBEN Enable for
                                               // ADCSOCBOn
#define XBAR_ADCSOCOUTSELECT_PWM11SOCBEN  0x4000000U   // PWM11SOCBEN Enable for
                                               // ADCSOCBOn
#define XBAR_ADCSOCOUTSELECT_PWM12SOCBEN  0x8000000U   // PWM12SOCBEN Enable for
                                               // ADCSOCBOn
#define XBAR_ADCSOCOUTSELECT_PWM13SOCBEN  0x10000000U  // PWM13SOCBEN Enable for
                                               // ADCSOCBOn
#define XBAR_ADCSOCOUTSELECT_PWM14SOCBEN  0x20000000U  // PWM14SOCBEN Enable for
                                               // ADCSOCBOn
#define XBAR_ADCSOCOUTSELECT_PWM15SOCBEN  0x40000000U  // PWM15SOCBEN Enable for
                                               // ADCSOCBOn
#define XBAR_ADCSOCOUTSELECT_PWM16SOCBEN  0x80000000U  // PWM16SOCBEN Enable for
                                               // ADCSOCBOn

//*****************************************************************************
//
// The following are defines for the bit fields in the SYNCSOCLOCK register
//
//*****************************************************************************
#define XBAR_SYNCSOCLOCK_SYNCSELECT  0x1U         // SYNCSEL Register Lock bit
#define XBAR_SYNCSOCLOCK_EXTADCSOCSELECT  0x2U         // EXTADCSOCSEL Register Lock
                                               // bit
#endif
