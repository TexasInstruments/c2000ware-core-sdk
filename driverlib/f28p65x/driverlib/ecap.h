//###########################################################################
//
// FILE: ecap.h
//
// TITLE: C28x ECAP driver
//
//#############################################################################
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

#ifndef ECAP_H
#define ECAP_H

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
//! \addtogroup ecap_api eCAP
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
// Includes
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ecap.h"
#include "cpu.h"
#include "debug.h"

//*****************************************************************************
//
// Define to mask out the bits in the signal monitoring unit.
//
//*****************************************************************************
#define ECAP_MUNIT_STEP            (ECAP_O_MUNIT_2_CTL - ECAP_O_MUNIT_1_CTL)

//*****************************************************************************
//
// eCAP minimum and maximum values
//
//*****************************************************************************
#define ECAP_MAX_PRESCALER_VALUE       32U  // Maximum Pre-scaler value

//*****************************************************************************
//
// Values that can be passed to ECAP_enableInterrupt(),
// ECAP_disableInterrupt(), ECAP_clearInterrupt() and ECAP_forceInterrupt() as
// the intFlags parameter and returned by ECAP_getInterruptSource().
//
//*****************************************************************************
//! Event 1 ISR source
//!
#define ECAP_ISR_SOURCE_CAPTURE_EVENT_1 0x2U
//! Event 2 ISR source
//!
#define ECAP_ISR_SOURCE_CAPTURE_EVENT_2 0x4U
//! Event 3 ISR source
//!
#define ECAP_ISR_SOURCE_CAPTURE_EVENT_3 0x8U
//! Event 4 ISR source
//!
#define ECAP_ISR_SOURCE_CAPTURE_EVENT_4 0x10U
//! Counter overflow ISR source
//!
#define ECAP_ISR_SOURCE_COUNTER_OVERFLOW 0x20U
//! Counter equals period ISR source
//!
#define ECAP_ISR_SOURCE_COUNTER_PERIOD 0x40U
//! Counter equals compare ISR source
//!
#define ECAP_ISR_SOURCE_COUNTER_COMPARE 0x80U
//! Monitoring unit 1 error event 1 ISR source
//!
#define ECAP_ISR_SOURCE_MUNIT_1_ERROR_EVT1 0x200U
//! Monitoring unit 1 error event 2 ISR source
//!
#define ECAP_ISR_SOURCE_MUNIT_1_ERROR_EVT2 0x400U
//! Monitoring unit 2 error event 1 ISR source
//!
#define ECAP_ISR_SOURCE_MUNIT_2_ERROR_EVT1 0x800U
//! Monitoring unit 2 error event 2 ISR source
//!
#define ECAP_ISR_SOURCE_MUNIT_2_ERROR_EVT2 0x1000U

//*****************************************************************************
//
//! Values that can be passed to ECAP_setEmulationMode() as the
//! \e mode parameter.
//
//*****************************************************************************
typedef enum
{
    //! TSCTR is stopped on emulation suspension
    ECAP_EMULATION_STOP             = 0x0U,
    //! TSCTR runs until 0 before stopping on emulation suspension
    ECAP_EMULATION_RUN_TO_ZERO      = 0x1U,
    //! TSCTR is not affected by emulation suspension
    ECAP_EMULATION_FREE_RUN         = 0x2U
}ECAP_EmulationMode;

//*****************************************************************************
//
//! Values that can be passed to ECAP_setCaptureMode() as the
//! \e mode parameter.
//
//*****************************************************************************
typedef enum
{
    //! eCAP operates in continuous capture mode
    ECAP_CONTINUOUS_CAPTURE_MODE    = 0U,
    //! eCAP operates in one shot capture mode
    ECAP_ONE_SHOT_CAPTURE_MODE      = 1U
}ECAP_CaptureMode;

//*****************************************************************************
//
//! Values that can be passed to ECAP_setEventPolarity(),ECAP_setCaptureMode(),
//! ECAP_enableCounterResetOnEvent(),ECAP_disableCounterResetOnEvent(),
//! ECAP_getEventTimeStamp(),ECAP_setDMASource() as the \e event parameter.
//
//*****************************************************************************
typedef enum
{
    ECAP_EVENT_1 = 0U,   //!< eCAP event 1
    ECAP_EVENT_2 = 1U,   //!< eCAP event 2
    ECAP_EVENT_3 = 2U,   //!< eCAP event 3
    ECAP_EVENT_4 = 3U    //!< eCAP event 4
}ECAP_Events;

//*****************************************************************************
//
//! Values that can be passed to ECAP_setSyncOutMode() as the \e mode
//! parameter.
//
//*****************************************************************************
typedef enum
{
    //! sync out on the sync in signal and software force
    ECAP_SYNC_OUT_SYNCI         = 0x00U,
    //! sync out on counter equals period
    ECAP_SYNC_OUT_COUNTER_PRD   = 0x40U,
    //! Disable sync out signal
    ECAP_SYNC_OUT_DISABLED      = 0x80U
}ECAP_SyncOutMode;

//*****************************************************************************
//
//! Values that can be passed to ECAP_setAPWMPolarity() as the \e polarity
//! parameter.
//
//*****************************************************************************
typedef enum
{
    ECAP_APWM_ACTIVE_HIGH   = 0x000, //!< APWM is active high
    ECAP_APWM_ACTIVE_LOW    = 0x400  //!< APWM is active low
}ECAP_APWMPolarity;

//*****************************************************************************
//
//! Values that can be passed to ECAP_setEventPolarity() as the \e polarity
//! parameter.
//
//*****************************************************************************
typedef enum
{
    ECAP_EVNT_RISING_EDGE   = 0U, //!< Rising edge polarity
    ECAP_EVNT_FALLING_EDGE  = 1U  //!< Falling edge polarity
}ECAP_EventPolarity;

//*****************************************************************************
//
//! Values that can be passed to ECAP_selectECAPInput() as the \e input
//! parameter.
//
//*****************************************************************************
typedef enum
{
    //! GPIO Input Crossbar output signal-1
    ECAP_INPUT_INPUTXBAR1 = 0,
    //! GPIO Input Crossbar output signal-2
    ECAP_INPUT_INPUTXBAR2 = 1,
    //! GPIO Input Crossbar output signal-3
    ECAP_INPUT_INPUTXBAR3 = 2,
    //! GPIO Input Crossbar output signal-4
    ECAP_INPUT_INPUTXBAR4 = 3,
    //! GPIO Input Crossbar output signal-5
    ECAP_INPUT_INPUTXBAR5 = 4,
    //! GPIO Input Crossbar output signal-6
    ECAP_INPUT_INPUTXBAR6 = 5,
    //! GPIO Input Crossbar output signal-7
    ECAP_INPUT_INPUTXBAR7 = 6,
    //! GPIO Input Crossbar output signal-8
    ECAP_INPUT_INPUTXBAR8 = 7,
    //! GPIO Input Crossbar output signal-9
    ECAP_INPUT_INPUTXBAR9 = 8,
    //! GPIO Input Crossbar output signal-10
    ECAP_INPUT_INPUTXBAR10 = 9,
    //! GPIO Input Crossbar output signal-11
    ECAP_INPUT_INPUTXBAR11 = 10,
    //! GPIO Input Crossbar output signal-12
    ECAP_INPUT_INPUTXBAR12 = 11,
    //! GPIO Input Crossbar output signal-13
    ECAP_INPUT_INPUTXBAR13 = 12,
    //! GPIO Input Crossbar output signal-14
    ECAP_INPUT_INPUTXBAR14 = 13,
    //! GPIO Input Crossbar output signal-15
    ECAP_INPUT_INPUTXBAR15 = 14,
    //! GPIO Input Crossbar output signal-16
    ECAP_INPUT_INPUTXBAR16 = 15,
    //! CLB1 CLBOUT14 input for ECAP1 instance
    ECAP_INPUT_ECAP1_CLB1_CLBOUT14 = 16,
    //! CLB1 CLBOUT14 input for ECAP2 instance
    ECAP_INPUT_ECAP2_CLB1_CLBOUT14 = 16,
    //! CLB2 CLBOUT14 input for ECAP3 instance
    ECAP_INPUT_ECAP3_CLB2_CLBOUT14 = 16,
    //! CLB2 CLBOUT14 input for ECAP4 instance
    ECAP_INPUT_ECAP4_CLB2_CLBOUT14 = 16,
    //! CLB2 CLBOUT14 input for ECAP5 instance
    ECAP_INPUT_ECAP5_CLB2_CLBOUT14 = 16,
    //! CLB3 CLBOUT14 input for ECAP6 instance
    ECAP_INPUT_ECAP6_CLB3_CLBOUT14 = 16,
    //! CLB3 CLBOUT14 input for ECAP7 instance
    ECAP_INPUT_ECAP7_CLB3_CLBOUT14 = 16,
    //! CLB1 CLBOUT15 input for ECAP1 instance
    ECAP_INPUT_ECAP1_CLB1_CLBOUT15 = 17,
    //! CLB1 CLBOUT15 input for ECAP2 instance
    ECAP_INPUT_ECAP2_CLB1_CLBOUT15 = 17,
    //! CLB2 CLBOUT15 input for ECAP3 instance
    ECAP_INPUT_ECAP3_CLB2_CLBOUT15 = 17,
    //! CLB2 CLBOUT15 input for ECAP4 instance
    ECAP_INPUT_ECAP4_CLB2_CLBOUT15 = 17,
    //! CLB2 CLBOUT15 input for ECAP5 instance
    ECAP_INPUT_ECAP5_CLB2_CLBOUT15 = 17,
    //! CLB3 CLBOUT15 input for ECAP6 instance
    ECAP_INPUT_ECAP6_CLB3_CLBOUT15 = 17,
    //! CLB3 CLBOUT15 input for ECAP7 instance
    ECAP_INPUT_ECAP7_CLB3_CLBOUT15 = 17,
    //! CLB5 CLBOUT14 input for ECAP1 instance
    ECAP_INPUT_ECAP1_CLB5_CLBOUT14 = 18,
    //! CLB5 CLBOUT14 input for ECAP2 instance
    ECAP_INPUT_ECAP2_CLB5_CLBOUT14 = 18,
    //! CLB6 CLBOUT14 input for ECAP3 instance
    ECAP_INPUT_ECAP3_CLB6_CLBOUT14 = 18,
    //! CLB6 CLBOUT14 input for ECAP4 instance
    ECAP_INPUT_ECAP4_CLB6_CLBOUT14 = 18,
    //! CLB6 CLBOUT14 input for ECAP5 instance
    ECAP_INPUT_ECAP5_CLB6_CLBOUT14 = 18,
    //! CLB4 CLBOUT14 input for ECAP6 instance
    ECAP_INPUT_ECAP6_CLB4_CLBOUT14 = 18,
    //! CLB4 CLBOUT14 input for ECAP7 instance
    ECAP_INPUT_ECAP7_CLB4_CLBOUT14 = 18,
    //! CLB5 CLBOUT15 input for ECAP1 instance
    ECAP_INPUT_ECAP1_CLB5_CLBOUT15 = 19,
    //! CLB5 CLBOUT15 input for ECAP2 instance
    ECAP_INPUT_ECAP2_CLB5_CLBOUT15 = 19,
    //! CLB6 CLBOUT15 input for ECAP3 instance
    ECAP_INPUT_ECAP3_CLB6_CLBOUT15 = 19,
    //! CLB6 CLBOUT15 input for ECAP4 instance
    ECAP_INPUT_ECAP4_CLB6_CLBOUT15 = 19,
    //! CLB6 CLBOUT15 input for ECAP5 instance
    ECAP_INPUT_ECAP5_CLB6_CLBOUT15 = 19,
    //! CLB4 CLBOUT15 input for ECAP6 instance
    ECAP_INPUT_ECAP6_CLB4_CLBOUT15 = 19,
    //! CLB4 CLBOUT15 input for ECAP7 instance
    ECAP_INPUT_ECAP7_CLB4_CLBOUT15 = 19,
    //! CANA INT0 Input
    ECAP_INPUT_CANA_INT0 = 20,
    //! Delay clock for measurement
    ECAP_INPUT_ECAP6_DELAY_CLOCK = 23,
    //! Delay clock for measurement
    ECAP_INPUT_ECAP7_DELAY_CLOCK = 23,
    //! Output Xbar Output-1
    ECAP_INPUT_OUTPUTXBAR1 = 24,
    //! Output Xbar Output-2
    ECAP_INPUT_OUTPUTXBAR2 = 25,
    //! Output Xbar Output-3
    ECAP_INPUT_OUTPUTXBAR3 = 26,
    //! Output Xbar Output-4
    ECAP_INPUT_OUTPUTXBAR4 = 27,
    //! Output Xbar Output-5
    ECAP_INPUT_OUTPUTXBAR5 = 28,
    //! Output Xbar Output-6
    ECAP_INPUT_OUTPUTXBAR6 = 29,
    //! Output Xbar Output-7
    ECAP_INPUT_OUTPUTXBAR7 = 30,
    //! Output Xbar Output-8
    ECAP_INPUT_OUTPUTXBAR8 = 31,
    //! ADCC Event4
    ECAP_INPUT_ADC_C_EVENT4 = 36,
    //! ADCC Event3
    ECAP_INPUT_ADC_C_EVENT3 = 37,
    //! ADCC Event2
    ECAP_INPUT_ADC_C_EVENT2 = 38,
    //! ADCC Event1
    ECAP_INPUT_ADC_C_EVENT1 = 39,
    //! ADCB Event4
    ECAP_INPUT_ADC_B_EVENT4 = 40,
    //! ADCB Event3
    ECAP_INPUT_ADC_B_EVENT3 = 41,
    //! ADCB Event2
    ECAP_INPUT_ADC_B_EVENT2 = 42,
    //! ADCB Event1
    ECAP_INPUT_ADC_B_EVENT1 = 43,
    //! ADCA Event4
    ECAP_INPUT_ADC_A_EVENT4 = 44,
    //! ADCA Event3
    ECAP_INPUT_ADC_A_EVENT3 = 45,
    //! ADCA Event2
    ECAP_INPUT_ADC_A_EVENT2 = 46,
    //! ADCA Event1
    ECAP_INPUT_ADC_A_EVENT1 = 47,
    //! FSIA Rx MSR Line
    ECAP_INPUT_FSIA_RX_MSR_LINE = 48,
    //! FSIA Rx MSR Line Rise
    ECAP_INPUT_FSIA_RX_MSR_LINE_RISE = 49,
    //! FSIA Rx MSR Line Fall
    ECAP_INPUT_FSIA_RX_MSR_LINE_FALL = 50,
    //! FSIB Rx MSR Line
    ECAP_INPUT_FSIB_RX_MSR_LINE = 51,
    //! FSIB Rx MSR Line Rise
    ECAP_INPUT_FSIB_RX_MSR_LINE_RISE = 52,
    //! FSIB Rx MSR Line Fall
    ECAP_INPUT_FSIB_RX_MSR_LINE_FALL = 53,
    //! FSIC Rx MSR Line
    ECAP_INPUT_FSIC_RX_MSR_LINE = 54,
    //! FSIC Rx MSR Line Rise
    ECAP_INPUT_FSIC_RX_MSR_LINE_RISE = 55,
    //! FSIC Rx MSR Line Fall
    ECAP_INPUT_FSIC_RX_MSR_LINE_FALL = 56,
    //! FSID Rx MSR Line
    ECAP_INPUT_FSID_RX_MSR_LINE = 57,
    //! FSID Rx MSR Line Rise
    ECAP_INPUT_FSID_RX_MSR_LINE_RISE = 58,
    //! FSID Rx MSR Line Fall
    ECAP_INPUT_FSID_RX_MSR_LINE_FALL = 59,
    //! SDFM-2 Filter-1 Compare Low Trip
    ECAP_INPUT_SDFM2_FLT1_COMPARE_LOW = 60,
    //! SDFM-2 Filter-2 Compare Low Trip
    ECAP_INPUT_SDFM2_FLT2_COMPARE_LOW = 61,
    //! SDFM-2 Filter-3 Compare Low Trip
    ECAP_INPUT_SDFM2_FLT3_COMPARE_LOW = 62,
    //! SDFM-2 Filter-4 Compare Low Trip
    ECAP_INPUT_SDFM2_FLT4_COMPARE_LOW = 63,
    //! SDFM-1 Filter-1 Compare Low Trip
    ECAP_INPUT_SDFM1_FLT1_COMPARE_LOW = 64,
    //! SDFM-1 Filter-2 Compare Low Trip
    ECAP_INPUT_SDFM1_FLT2_COMPARE_LOW = 65,
    //! SDFM-1 Filter-3 Compare Low Trip
    ECAP_INPUT_SDFM1_FLT3_COMPARE_LOW = 66,
    //! SDFM-1 Filter-4 Compare Low Trip
    ECAP_INPUT_SDFM1_FLT4_COMPARE_LOW = 67,
    //! SDFM-2 Filter-1 Compare Z Trip
    ECAP_INPUT_SDFM2_FLT1_COMPARE_Z = 68,
    //! SDFM-2 Filter-2 Compare Low Trip
    ECAP_INPUT_SDFM2_FLT2_COMPARE_Z = 69,
    //! SDFM-2 Filter-3 Compare Low Trip
    ECAP_INPUT_SDFM2_FLT3_COMPARE_Z = 70,
    //! SDFM-2 Filter-4 Compare Low Trip
    ECAP_INPUT_SDFM2_FLT4_COMPARE_Z = 71,
    //! SDFM-1 Filter-1 Compare Z Trip
    ECAP_INPUT_SDFM1_FLT1_COMPARE_Z = 72,
    //! SDFM-1 Filter-2 Compare Low Trip
    ECAP_INPUT_SDFM1_FLT2_COMPARE_Z = 73,
    //! SDFM-1 Filter-3 Compare Low Trip
    ECAP_INPUT_SDFM1_FLT3_COMPARE_Z = 74,
    //! SDFM-1 Filter-4 Compare Low Trip
    ECAP_INPUT_SDFM1_FLT4_COMPARE_Z = 75,
    //! SDFM-2 Filter-1 Compare High Trip
    ECAP_INPUT_SDFM2_FLT1_COMPARE_HIGH = 76,
    //! SDFM-2 Filter-2 Compare High Trip
    ECAP_INPUT_SDFM2_FLT2_COMPARE_HIGH = 77,
    //! SDFM-2 Filter-3 Compare High Trip
    ECAP_INPUT_SDFM2_FLT3_COMPARE_HIGH = 78,
    //! SDFM-2 Filter-4 Compare High Trip
    ECAP_INPUT_SDFM2_FLT4_COMPARE_HIGH = 79,
    //! SDFM-1 Filter-1 Compare High Trip
    ECAP_INPUT_SDFM1_FLT1_COMPARE_HIGH = 80,
    //! SDFM-1 Filter-2 Compare High Trip
    ECAP_INPUT_SDFM1_FLT2_COMPARE_HIGH = 81,
    //! SDFM-1 Filter-3 Compare High Trip
    ECAP_INPUT_SDFM1_FLT3_COMPARE_HIGH = 82,
    //! SDFM-1 Filter-4 Compare High Trip
    ECAP_INPUT_SDFM1_FLT4_COMPARE_HIGH = 83,
    //! SDFM-2 Filter-1 Compare High Trip or Low Trip
    ECAP_INPUT_SDFM2_FLT1_COMPARE_HIGH_OR_LOW = 84,
    //! SDFM-2 Filter-2 Compare High Trip or Low Trip
    ECAP_INPUT_SDFM2_FLT2_COMPARE_HIGH_OR_LOW = 85,
    //! SDFM-2 Filter-3 Compare High Trip or Low Trip
    ECAP_INPUT_SDFM2_FLT3_COMPARE_HIGH_OR_LOW = 86,
    //! SDFM-2 Filter-4 Compare High Trip or Low Trip
    ECAP_INPUT_SDFM2_FLT4_COMPARE_HIGH_OR_LOW = 87,
    //! SDFM-1 Filter-1 Compare High Trip or Low Trip
    ECAP_INPUT_SDFM1_FLT1_COMPARE_HIGH_OR_LOW = 88,
    //! SDFM-1 Filter-2 Compare High Trip or Low Trip
    ECAP_INPUT_SDFM1_FLT2_COMPARE_HIGH_OR_LOW = 89,
    //! SDFM-1 Filter-3 Compare High Trip or Low Trip
    ECAP_INPUT_SDFM1_FLT3_COMPARE_HIGH_OR_LOW = 90,
    //! SDFM-1 Filter-4 Compare High Trip or Low Trip
    ECAP_INPUT_SDFM1_FLT4_COMPARE_HIGH_OR_LOW = 91,
    //! Ethercat Sync0
    ECAP_INPUT_ECATSYNC0 = 94,
    //! Ethercat Sync1
    ECAP_INPUT_ECATSYNC1 = 95,
    //! Compare Subsystem-1 Low Trip
    ECAP_INPUT_CMPSS1_CTRIP_LOW = 96,
    //! Compare Subsystem-2 Low Trip
    ECAP_INPUT_CMPSS2_CTRIP_LOW = 97,
    //! Compare Subsystem-3 Low Trip
    ECAP_INPUT_CMPSS3_CTRIP_LOW = 98,
    //! Compare Subsystem-4 Low Trip
    ECAP_INPUT_CMPSS4_CTRIP_LOW = 99,
    //! Compare Subsystem-5 Low Trip
    ECAP_INPUT_CMPSS5_CTRIP_LOW = 100,
    //! Compare Subsystem-6 Low Trip
    ECAP_INPUT_CMPSS6_CTRIP_LOW = 101,
    //! Compare Subsystem-7 Low Trip
    ECAP_INPUT_CMPSS7_CTRIP_LOW = 102,
    //! Compare Subsystem-8 Low Trip
    ECAP_INPUT_CMPSS8_CTRIP_LOW = 103,
    //! Compare Subsystem-1 High Trip
    ECAP_INPUT_CMPSS1_CTRIP_HIGH = 107,
    //! Compare Subsystem-2 High Trip
    ECAP_INPUT_CMPSS2_CTRIP_HIGH = 108,
    //! Compare Subsystem-3 High Trip
    ECAP_INPUT_CMPSS3_CTRIP_HIGH = 109,
    //! Compare Subsystem-4 High Trip
    ECAP_INPUT_CMPSS4_CTRIP_HIGH = 110,
    //! Compare Subsystem-5 High Trip
    ECAP_INPUT_CMPSS5_CTRIP_HIGH = 111,
    //! Compare Subsystem-6 High Trip
    ECAP_INPUT_CMPSS6_CTRIP_HIGH = 112,
    //! Compare Subsystem-7 High Trip
    ECAP_INPUT_CMPSS7_CTRIP_HIGH = 113,
    //! Compare Subsystem-8 High Trip
    ECAP_INPUT_CMPSS8_CTRIP_HIGH = 114,
    //! GPIO8
    ECAP_INPUT_GPIO8 = 115,
    //! GPIO9
    ECAP_INPUT_GPIO9 = 116,
    //! GPIO22
    ECAP_INPUT_GPIO22 = 117,
    //! GPIO23
    ECAP_INPUT_GPIO23 = 118,
    //! Compare Subsystem-1 High Trip or Low Trip
    ECAP_INPUT_CMPSS1_CTRIP_HIGH_OR_LOW = 119,
    //! Compare Subsystem-1 High Trip or Low Trip
    ECAP_INPUT_CMPSS2_CTRIP_HIGH_OR_LOW = 120,
    //! Compare Subsystem-2 High Trip or Low Trip
    ECAP_INPUT_CMPSS3_CTRIP_HIGH_OR_LOW = 121,
    //! Compare Subsystem-3 High Trip or Low Trip
    ECAP_INPUT_CMPSS4_CTRIP_HIGH_OR_LOW = 122,
    //! Compare Subsystem-4 High Trip or Low Trip
    ECAP_INPUT_CMPSS5_CTRIP_HIGH_OR_LOW = 123,
    //! Compare Subsystem-5 High Trip or Low Trip
    ECAP_INPUT_CMPSS6_CTRIP_HIGH_OR_LOW = 124,
    //! Compare Subsystem-6 High Trip or Low Trip
    ECAP_INPUT_CMPSS7_CTRIP_HIGH_OR_LOW = 125,
    //! Compare Subsystem-7 High Trip or Low Trip
    ECAP_INPUT_CMPSS8_CTRIP_HIGH_OR_LOW = 126,
    //! GPTRIP7 input for instance ECAP1
    ECAP_INPUT_ECAP1_GPTRIP7 = 127,
    //! GPTRIP8 input for instance ECAP2
    ECAP_INPUT_ECAP2_GPTRIP8 = 127,
    //! GPTRIP9 input for instance ECAP3
    ECAP_INPUT_ECAP3_GPTRIP9 = 127,
    //! GPTRIP10 input for instance ECAP4
    ECAP_INPUT_ECAP4_GPTRIP10 = 127,
    //! GPTRIP11 input for instance ECAP5
    ECAP_INPUT_ECAP5_GPTRIP11 = 127,
    //! GPTRIP12 input for instance ECAP6
    ECAP_INPUT_ECAP6_GPTRIP12 = 127,
    //! GPTRIP13 input for instance ECAP7
    ECAP_INPUT_ECAP7_GPTRIP13 = 127,
    //! SDFM-4 Filter-1 Compare Low Trip
    ECAP_INPUT_SDFM4_FLT1_COMPARE_LOW = 128,
    //! SDFM-4 Filter-2 Compare Low Trip
    ECAP_INPUT_SDFM4_FLT2_COMPARE_LOW = 129,
    //! SDFM-4 Filter-3 Compare Low Trip
    ECAP_INPUT_SDFM4_FLT3_COMPARE_LOW = 130,
    //! SDFM-4 Filter-4 Compare Low Trip
    ECAP_INPUT_SDFM4_FLT4_COMPARE_LOW = 131,
    //! SDFM-3 Filter-1 Compare Low Trip
    ECAP_INPUT_SDFM3_FLT1_COMPARE_LOW = 132,
    //! SDFM-3 Filter-2 Compare Low Trip
    ECAP_INPUT_SDFM3_FLT2_COMPARE_LOW = 133,
    //! SDFM-3 Filter-3 Compare Low Trip
    ECAP_INPUT_SDFM3_FLT3_COMPARE_LOW = 134,
    //! SDFM-3 Filter-4 Compare Low Trip
    ECAP_INPUT_SDFM3_FLT4_COMPARE_LOW = 135,
    //! SDFM-4 Filter-1 Compare Z Trip
    ECAP_INPUT_SDFM4_FLT1_COMPARE_Z = 136,
    //! SDFM-4 Filter-2 Compare Low Trip
    ECAP_INPUT_SDFM4_FLT2_COMPARE_Z = 137,
    //! SDFM-4 Filter-3 Compare Low Trip
    ECAP_INPUT_SDFM4_FLT3_COMPARE_Z = 138,
    //! SDFM-4 Filter-4 Compare Low Trip
    ECAP_INPUT_SDFM4_FLT4_COMPARE_Z = 139,
    //! SDFM-3 Filter-1 Compare Z Trip
    ECAP_INPUT_SDFM3_FLT1_COMPARE_Z = 140,
    //! SDFM-3 Filter-2 Compare Low Trip
    ECAP_INPUT_SDFM3_FLT2_COMPARE_Z = 141,
    //! SDFM-3 Filter-3 Compare Low Trip
    ECAP_INPUT_SDFM3_FLT3_COMPARE_Z = 142,
    //! SDFM-3 Filter-4 Compare Low Trip
    ECAP_INPUT_SDFM3_FLT4_COMPARE_Z = 143,
    //! SDFM-4 Filter-1 Compare High Trip
    ECAP_INPUT_SDFM4_FLT1_COMPARE_HIGH = 144,
    //! SDFM-4 Filter-2 Compare High Trip
    ECAP_INPUT_SDFM4_FLT2_COMPARE_HIGH = 145,
    //! SDFM-4 Filter-3 Compare High Trip
    ECAP_INPUT_SDFM4_FLT3_COMPARE_HIGH = 146,
    //! SDFM-4 Filter-4 Compare High Trip
    ECAP_INPUT_SDFM4_FLT4_COMPARE_HIGH = 147,
    //! SDFM-3 Filter-1 Compare High Trip
    ECAP_INPUT_SDFM3_FLT1_COMPARE_HIGH = 148,
    //! SDFM-3 Filter-2 Compare High Trip
    ECAP_INPUT_SDFM3_FLT2_COMPARE_HIGH = 149,
    //! SDFM-3 Filter-3 Compare High Trip
    ECAP_INPUT_SDFM3_FLT3_COMPARE_HIGH = 150,
    //! SDFM-3 Filter-4 Compare High Trip
    ECAP_INPUT_SDFM3_FLT4_COMPARE_HIGH = 151,
    //! SDFM-4 Filter-1 Compare High Trip or Low Trip
    ECAP_INPUT_SDFM4_FLT1_COMPARE_HIGH_OR_LOW = 152,
    //! SDFM-4 Filter-2 Compare High Trip or Low Trip
    ECAP_INPUT_SDFM4_FLT2_COMPARE_HIGH_OR_LOW = 153,
    //! SDFM-4 Filter-3 Compare High Trip or Low Trip
    ECAP_INPUT_SDFM4_FLT3_COMPARE_HIGH_OR_LOW = 154,
    //! SDFM-4 Filter-4 Compare High Trip or Low Trip
    ECAP_INPUT_SDFM4_FLT4_COMPARE_HIGH_OR_LOW = 155,
    //! SDFM-3 Filter-1 Compare High Trip or Low Trip
    ECAP_INPUT_SDFM3_FLT1_COMPARE_HIGH_OR_LOW = 156,
    //! SDFM-3 Filter-2 Compare High Trip or Low Trip
    ECAP_INPUT_SDFM3_FLT2_COMPARE_HIGH_OR_LOW = 157,
    //! SDFM-3 Filter-3 Compare High Trip or Low Trip
    ECAP_INPUT_SDFM3_FLT3_COMPARE_HIGH_OR_LOW = 158,
    //! SDFM-3 Filter-4 Compare High Trip or Low Trip
    ECAP_INPUT_SDFM3_FLT4_COMPARE_HIGH_OR_LOW = 159,
    //! EPWM-18 Diode Emulation Logic Active
    ECAP_INPUT_EPWM18_DEL_ACTIVE = 160,
    //! EPWM-17 Diode Emulation Logic Active
    ECAP_INPUT_EPWM17_DEL_ACTIVE = 161,
    //! EPWM-16 Diode Emulation Logic Active
    ECAP_INPUT_EPWM16_DEL_ACTIVE = 162,
    //! EPWM-15 Diode Emulation Logic Active
    ECAP_INPUT_EPWM15_DEL_ACTIVE = 163,
    //! EPWM-14 Diode Emulation Logic Active
    ECAP_INPUT_EPWM14_DEL_ACTIVE = 164,
    //! EPWM-13 Diode Emulation Logic Active
    ECAP_INPUT_EPWM13_DEL_ACTIVE = 165,
    //! EPWM-12 Diode Emulation Logic Active
    ECAP_INPUT_EPWM12_DEL_ACTIVE = 166,
    //! EPWM-11 Diode Emulation Logic Active
    ECAP_INPUT_EPWM11_DEL_ACTIVE = 167,
    //! EPWM-10 Diode Emulation Logic Active
    ECAP_INPUT_EPWM10_DEL_ACTIVE = 168,
    //! EPWM-9 Diode Emulation Logic Active
    ECAP_INPUT_EPWM9_DEL_ACTIVE = 169,
    //! EPWM-8 Diode Emulation Logic Active
    ECAP_INPUT_EPWM8_DEL_ACTIVE = 170,
    //! EPWM-7 Diode Emulation Logic Active
    ECAP_INPUT_EPWM7_DEL_ACTIVE = 171,
    //! EPWM-6 Diode Emulation Logic Active
    ECAP_INPUT_EPWM6_DEL_ACTIVE = 172,
    //! EPWM-5 Diode Emulation Logic Active
    ECAP_INPUT_EPWM5_DEL_ACTIVE = 173,
    //! EPWM-4 Diode Emulation Logic Active
    ECAP_INPUT_EPWM4_DEL_ACTIVE = 174,
    //! EPWM-3 Diode Emulation Logic Active
    ECAP_INPUT_EPWM3_DEL_ACTIVE = 175,
    //! EPWM-2 Diode Emulation Logic Active
    ECAP_INPUT_EPWM2_DEL_ACTIVE = 176,
    //! EPWM-1 Diode Emulation Logic Active
    ECAP_INPUT_EPWM1_DEL_ACTIVE = 177,
    //! GPIO11
    ECAP_INPUT_GPIO11 = 251,
    //! GPIO12
    ECAP_INPUT_GPIO12 = 252,
    //! GPIO13
    ECAP_INPUT_GPIO13 = 253,
    //! GPIO14
    ECAP_INPUT_GPIO14 = 254,
    //! EPG-1 Data Output-53 Connection
    ECAP_INPUT_ECAP1_EPG1_DATAOUT53 = 255,
    //! EPG-1 Data Output-54 Connection
    ECAP_INPUT_ECAP2_EPG1_DATAOUT54 = 255,
    //! EPG-1 Data Output-55 Connection
    ECAP_INPUT_ECAP3_EPG1_DATAOUT55 = 255,
    //! EPG-1 Data Output-56 Connection
    ECAP_INPUT_ECAP4_EPG1_DATAOUT56 = 255,
    //! EPG-1 Data Output-57 Connection
    ECAP_INPUT_ECAP5_EPG1_DATAOUT57 = 255,
    //! EPG-1 Data Output-58 Connection
    ECAP_INPUT_ECAP6_EPG1_DATAOUT58 = 255,
    //! EPG-1 Data Output-59 Connection
    ECAP_INPUT_ECAP7_EPG1_DATAOUT59 = 255,
}ECAP_InputCaptureSignals;

//*****************************************************************************
//
//! Values that can be passed to ECAP_selectQualPeriod() as the \e mode
//! parameter.
//
//*****************************************************************************
typedef enum
{
    //! Bypass
    ECAP_PULSE_WIDTH_FILTER_BYPASS         = 0x0,
    //! Pulse width less than 1 cycle
    ECAP_PULSE_WIDTH_FILTER_CYCLE1         = 0x1,
    //! Pulse width less than 2 cycles
    ECAP_PULSE_WIDTH_FILTER_CYCLE2         = 0x2,
    //! Pulse width less than 3 cycles
    ECAP_PULSE_WIDTH_FILTER_CYCLE3         = 0x3,
    //! Pulse width less than 4 cycles
    ECAP_PULSE_WIDTH_FILTER_CYCLE4         = 0x4,
    //! Pulse width less than 5 cycles
    ECAP_PULSE_WIDTH_FILTER_CYCLE5         = 0x5,
    //! Pulse width less than 6 cycles
    ECAP_PULSE_WIDTH_FILTER_CYCLE6         = 0x6,
    //! Pulse width less than 7 cycles
    ECAP_PULSE_WIDTH_FILTER_CYCLE7         = 0x7,
    //! Pulse width less than 8 cycles
    ECAP_PULSE_WIDTH_FILTER_CYCLE8         = 0x8,
    //! Pulse width less than 9 cycles
    ECAP_PULSE_WIDTH_FILTER_CYCLE9         = 0x9,
    //! Pulse width less than 10 cycles
    ECAP_PULSE_WIDTH_FILTER_CYCLE10        = 0xA,
    //! Pulse width less than 11 cycles
    ECAP_PULSE_WIDTH_FILTER_CYCLE11        = 0xB,
    //! Pulse width less than 12 cycles
    ECAP_PULSE_WIDTH_FILTER_CYCLE12        = 0xC,
    //! Pulse width less than 13 cycles
    ECAP_PULSE_WIDTH_FILTER_CYCLE13        = 0xD,
    //! Pulse width less than 14 cycles
    ECAP_PULSE_WIDTH_FILTER_CYCLE14        = 0xE,
    //! Pulse width less than 15 cycles
    ECAP_PULSE_WIDTH_FILTER_CYCLE15        = 0xF,
}ECAP_QualPeriodSelect;

//*****************************************************************************
//
//! Values that can be passed to ECAP_setSyncInPulseSource() as the \e mode
//! parameter.
//
//*****************************************************************************
typedef enum
{
    //! Disable Sync-in
    ECAP_SYNC_IN_PULSE_SRC_DISABLE         = 0x0,
    //! Sync-in source is EPWM1 sync-out signal
    ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM1   = 0x1,
    //! Sync-in source is EPWM2 sync-out signal
    ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM2   = 0x2,
    //! Sync-in source is EPWM3 sync-out signal
    ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM3   = 0x3,
    //! Sync-in source is EPWM4 sync-out signal
    ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM4   = 0x4,
    //! Sync-in source is EPWM5 sync-out signal
    ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM5   = 0x5,
    //! Sync-in source is EPWM6 sync-out signal
    ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM6   = 0x6,
    //! Sync-in source is EPWM7 sync-out signal
    ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM7   = 0x7,
    //! Sync-in source is EPWM8 sync-out signal
    ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM8   = 0x8,
    //! Sync-in source is EPWM9 sync-out signal
    ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM9   = 0x9,
    //! Sync-in source is EPWM10 sync-out signal
    ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM10  = 0xA,
    //! Sync-in source is EPWM11 sync-out signal
    ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM11  = 0xB,
    //! Sync-in source is EPWM12 sync-out signal
    ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM12  = 0xC,
    //! Sync-in source is EPWM13 sync-out signal
    ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM13  = 0xD,
    //! Sync-in source is EPWM14 sync-out signal
    ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM14  = 0xE,
    //! Sync-in source is EPWM15 sync-out signal
    ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM15  = 0xF,
    //! Sync-in source is EPWM16 sync-out signal
    ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM16  = 0x10,
    //! Sync-in source is ECAP1 sync-out signal
    ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_ECAP1   = 0x11,
    //! Sync-in source is ECAP2 sync-out signal
    ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_ECAP2   = 0x12,
    //! Sync-in source is ECAP3 sync-out signal
    ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_ECAP3   = 0x13,
    //! Sync-in source is ECAP4 sync-out signal
    ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_ECAP4   = 0x14,
    //! Sync-in source is ECAP5 sync-out signal
    ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_ECAP5   = 0x15,
    //! Sync-in source is ECAP6 sync-out signal
    ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_ECAP6   = 0x16,
    //! Sync-in source is ECAP7 sync-out signal
    ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_ECAP7  = 0x17,
    //! Sync-in source is Input XBAR out5 signal
    ECAP_SYNC_IN_PULSE_SRC_INPUTXBAR_OUT5 = 0x18,
    //! Sync-in source is Input XBAR out6 signal
    ECAP_SYNC_IN_PULSE_SRC_INPUTXBAR_OUT6 = 0x19,
    //! Sync-in source is Ethercat sync0 signal
    ECAP_SYNC_IN_PULSE_SRC_ETHERCAT_SYNC0 = 0x1A,
    //! Sync-in source is Ethercat sync1 signal
    ECAP_SYNC_IN_PULSE_SRC_ETHERCAT_SYNC1 = 0x1B,
    //! Sync-in source is EPWM17 sync-out signal
    ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM17  = 0x1C,
    //! Sync-in source is EPWM18 sync-out signal
    ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM18  = 0x1D,
    //! Sync-in source is FSI RXA RX signal
    ECAP_SYNC_IN_PULSE_SRC_FSIRXA_RX_TRIG1 = 0x1E,
    //! Sync-in source is FSI RXB RX signal
    ECAP_SYNC_IN_PULSE_SRC_FSIRXB_RX_TRIG1 = 0x1F,
    //! Sync-in source is FSI RXC RX signal
    ECAP_SYNC_IN_PULSE_SRC_FSIRXC_RX_TRIG1 = 0x20,
    //! Sync-in source is FSI RXD RX signal
    ECAP_SYNC_IN_PULSE_SRC_FSIRXD_RX_TRIG1 = 0x21,
}ECAP_SyncInPulseSource;

//*****************************************************************************
//
// Values that can be passed to ECAP Signal Monitoring APIs
//
//*****************************************************************************
//! ECAP Monitoring Unit 1
#define ECAP_MONITORING_UNIT_1       0U
//! ECAP Monitoring Unit 2
#define ECAP_MONITORING_UNIT_2       1U

//*****************************************************************************
//
//! Values that can be passed to ECAP_setupEarlyMaxErrorCheck() as the
//! \e checkError parameter.
//
//*****************************************************************************
//! Max error generated when pulse width cross max value
#define ECAP_PULSE_WIDTH_CROSS_MAX_VALUE     0U
//! Max error generated when second event has occured
#define ECAP_SECOND_EVENT_OCCURED            1U

//*****************************************************************************
//
//! Values that can be passed to ECAP_selectShadowLoadMode() as the
//! \e loadMode parameter.
//
//*****************************************************************************
//! Load on next sync event
#define ECAP_ACTIVE_LOAD_SYNC_EVT            0U
//! Load on EPWM GLDLCSTRB event
#define ECAP_ACTIVE_LOAD_GLDLCSTRB_EVT       1U

//*****************************************************************************
//
//! Values that can be passed to ECAP_selectMonitoringType() as the
//! \e monSel parameter.
//
//*****************************************************************************
typedef enum
{
    //! High Pulse Width
    ECAP_MUNIT_HIGH_PULSE_WIDTH = 0U,
    //! Low Pulse Width
    ECAP_MUNIT_LOW_PULSE_WIDTH = 1U,
    //! Period width from rise to rise
    ECAP_MUNIT_PERIOD_WIDTH_RISE_RISE = 2U,
    //! Period width from fall to fall
    ECAP_MUNIT_PERIOD_WIDTH_FALL_FALL = 3U,
    //! Monitor rise edge
    ECAP_MUNIT_MONITOR_RISE_EDGE = 4U,
    //! Monitor fall edge
    ECAP_MUNIT_MONITOR_FALL_EDGE = 5U,
}ECAP_MonitoringTypeSelect;

//*****************************************************************************
//
//! Values that can be passed to ECAP_selectTripSignal() &
//! ECAP_selectGlobalLoadStrobe() as the \e tripSel and \e strobe parameter.
//
//*****************************************************************************
typedef enum
{
    //! Disabled
    ECAP_MUNIT_TRIP_DISABLED = 0U,
    //! MUNIT trip source is PWMXBAR-A output 0
    ECAP_MUNIT_TRIP_EPWM_XBARA_OUT0 = 1U,
    //! MUNIT trip source is PWMXBAR-A output 1
    ECAP_MUNIT_TRIP_EPWM_XBARA_OUT1 = 2U,
    //! MUNIT trip source is PWMXBAR-A output 2
    ECAP_MUNIT_TRIP_EPWM_XBARA_OUT2 = 3U,
    //! MUNIT trip source is PWMXBAR-A output 3
    ECAP_MUNIT_TRIP_EPWM_XBARA_OUT3 = 4U,
    //! MUNIT trip source is PWMXBAR-A output 4
    ECAP_MUNIT_TRIP_EPWM_XBARA_OUT4 = 5U,
    //! MUNIT trip source is PWMXBAR-A output 5
    ECAP_MUNIT_TRIP_EPWM_XBARA_OUT5 = 6U,
    //! MUNIT trip source is PWMXBAR-A output 6
    ECAP_MUNIT_TRIP_EPWM_XBARA_OUT6 = 7U,
    //! MUNIT trip source is PWMXBAR-A output 7
    ECAP_MUNIT_TRIP_EPWM_XBARA_OUT7 = 8U,
    //! MUNIT trip source is PWMXBAR-B output 0
    ECAP_MUNIT_TRIP_EPWM_XBARB_OUT0 = 9U,
    //! MUNIT trip source is PWMXBAR-B output 1
    ECAP_MUNIT_TRIP_EPWM_XBARB_OUT1 = 10U,
    //! MUNIT trip source is PWMXBAR-B output 2
    ECAP_MUNIT_TRIP_EPWM_XBARB_OUT2 = 11U,
    //! MUNIT trip source is PWMXBAR-B output 3
    ECAP_MUNIT_TRIP_EPWM_XBARB_OUT3 = 12U,
    //! MUNIT trip source is PWMXBAR-B output 4
    ECAP_MUNIT_TRIP_EPWM_XBARB_OUT4 = 13U,
    //! MUNIT trip source is PWMXBAR-B output 5
    ECAP_MUNIT_TRIP_EPWM_XBARB_OUT5 = 14U,
    //! MUNIT trip source is PWMXBAR-B output 6
    ECAP_MUNIT_TRIP_EPWM_XBARB_OUT6 = 15U,
    //! MUNIT trip source is PWMXBAR-B output 7
    ECAP_MUNIT_TRIP_EPWM_XBARB_OUT7 = 16U,
    //! MUNIT trip source is EPWM1 trip out signal
    ECAP_MUNIT_TRIP_EPWM1_TRIPOUT = 32U,
    //! MUNIT trip source is EPWM2 trip out signal
    ECAP_MUNIT_TRIP_EPWM2_TRIPOUT = 33U,
    //! MUNIT trip source is EPWM3 trip out signal
    ECAP_MUNIT_TRIP_EPWM3_TRIPOUT = 34U,
    //! MUNIT trip source is EPWM4 trip out signal
    ECAP_MUNIT_TRIP_EPWM4_TRIPOUT = 35U,
    //! MUNIT trip source is EPWM5 trip out signal
    ECAP_MUNIT_TRIP_EPWM5_TRIPOUT = 36U,
    //! MUNIT trip source is EPWM6 trip out signal
    ECAP_MUNIT_TRIP_EPWM6_TRIPOUT = 37U,
    //! MUNIT trip source is EPWM7 trip out signal
    ECAP_MUNIT_TRIP_EPWM7_TRIPOUT = 38U,
    //! MUNIT trip source is EPWM8 trip out signal
    ECAP_MUNIT_TRIP_EPWM8_TRIPOUT = 39U,
    //! MUNIT trip source is EPWM9 trip out signal
    ECAP_MUNIT_TRIP_EPWM9_TRIPOUT = 40U,
    //! MUNIT trip source is EPWM10 trip out signal
    ECAP_MUNIT_TRIP_EPWM10_TRIPOUT = 41U,
    //! MUNIT trip source is EPWM11 trip out signal
    ECAP_MUNIT_TRIP_EPWM11_TRIPOUT = 42U,
    //! MUNIT trip source is EPWM12 trip out signal
    ECAP_MUNIT_TRIP_EPWM12_TRIPOUT = 43U,
    //! MUNIT trip source is EPWM13 trip out signal
    ECAP_MUNIT_TRIP_EPWM13_TRIPOUT = 44U,
    //! MUNIT trip source is EPWM14 trip out signal
    ECAP_MUNIT_TRIP_EPWM14_TRIPOUT = 45U,
    //! MUNIT trip source is EPWM15 trip out signal
    ECAP_MUNIT_TRIP_EPWM15_TRIPOUT = 46U,
    //! MUNIT trip source is EPWM16 trip out signal
    ECAP_MUNIT_TRIP_EPWM16_TRIPOUT = 47U,
    //! MUNIT trip source is EPWM17 trip out signal
    ECAP_MUNIT_TRIP_EPWM17_TRIPOUT = 48U,
    //! MUNIT trip source is EPWM18 trip out signal
    ECAP_MUNIT_TRIP_EPWM18_TRIPOUT = 49U
}ECAP_MunitTripInputSelect;

//*****************************************************************************
//
//! \internal
//! Checks eCAP base address.
//!
//! \param base specifies the eCAP module base address.
//!
//! This function determines if an eCAP module base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool ECAP_isBaseValid(uint32_t base)
{
    return(
           (base == ECAP1_BASE) ||
           (base == ECAP2_BASE) ||
           (base == ECAP3_BASE) ||
           (base == ECAP4_BASE) ||
           (base == ECAP5_BASE) ||
           (base == ECAP6_BASE) ||
           (base == ECAP7_BASE)
          );
}
#endif

//*****************************************************************************
//
//! \internal
//! Checks eCAP Signal Monitoring base address.
//!
//! \param base specifies the eCAP Signal Monitoring module base address.
//!
//! This function determines if an eCAP Signal Monitoring
//! module base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool ECAP_isSignalMonitoringBaseValid(uint32_t base)
{
    return(
           (base == ECAP1SIGNALMONITORING_BASE) ||
           (base == ECAP2SIGNALMONITORING_BASE) ||
           (base == ECAP3SIGNALMONITORING_BASE) ||
           (base == ECAP4SIGNALMONITORING_BASE) ||
           (base == ECAP5SIGNALMONITORING_BASE) ||
           (base == ECAP6SIGNALMONITORING_BASE) ||
           (base == ECAP7SIGNALMONITORING_BASE)
          );
}
#endif

//*****************************************************************************
//
//! Sets the input prescaler.
//!
//! \param base is the base address of the ECAP module.
//! \param preScalerValue is the pre scaler value for ECAP input
//!
//! This function divides the ECAP input scaler. The pre scale value is
//! doubled inside the module. For example a preScalerValue of 5 will divide
//! the scaler by 10. Use a value of 1 to divide the pre scaler by 1.
//! The \e preScalerValue should be less than \b ECAP_MAX_PRESCALER_VALUE.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_setEventPrescaler(uint32_t base,
                                          uint16_t preScalerValue)
{
    ASSERT(ECAP_isBaseValid(base));

    ASSERT(preScalerValue < ECAP_MAX_PRESCALER_VALUE);

    EALLOW;

    //
    // Write to PRESCALE bit
    //
    HWREGH(base + ECAP_O_ECCTL1) =
                 ((HWREGH(base + ECAP_O_ECCTL1) & (~ECAP_ECCTL1_PRESCALE_M)) |
                  (preScalerValue << ECAP_ECCTL1_PRESCALE_S));
    EDIS;
}

//*****************************************************************************
//
//! Sets the Capture event polarity.
//!
//! \param base is the base address of the ECAP module.
//! \param event is the event number.
//! \param polarity is the polarity of the event.
//!
//! This function sets the polarity of a given event. The value of event
//! is between \b ECAP_EVENT_1 and \b ECAP_EVENT_4 inclusive corresponding to
//! the four available events.For each event the polarity value determines the
//! edge on which the capture is activated. For a rising edge use a polarity
//! value of \b ECAP_EVNT_RISING_EDGE and for a falling edge use a polarity of
//! \b ECAP_EVNT_FALLING_EDGE.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_setEventPolarity(uint32_t base,
                                         ECAP_Events event,
                                         ECAP_EventPolarity polarity)
{

    uint16_t shift;

    ASSERT(ECAP_isBaseValid(base));

    shift = ((uint16_t)event) << 1U;

    EALLOW;

    //
    // Write to CAP1POL, CAP2POL, CAP3POL or CAP4POL
    //
    HWREGH(base + ECAP_O_ECCTL1) =
                         (HWREGH(base + ECAP_O_ECCTL1) & ~(1U << shift)) |
                         ((uint16_t)polarity << shift);
    EDIS;
}

//*****************************************************************************
//
//! Sets the capture mode.
//!
//! \param base is the base address of the ECAP module.
//! \param mode is the capture mode.
//! \param event is the event number at which the counter stops or wraps.
//!
//! This function sets the eCAP module to a continuous or one-shot mode.
//! The value of mode should be either \b ECAP_CONTINUOUS_CAPTURE_MODE or
//! \b ECAP_ONE_SHOT_CAPTURE_MODE corresponding to continuous or one-shot mode
//! respectively.
//!
//! The value of event determines the event number at which the counter stops
//! (in one-shot mode) or the counter wraps (in continuous mode). The value of
//! event should be between \b ECAP_EVENT_1 and \b ECAP_EVENT_4 corresponding
//! to the valid event numbers.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_setCaptureMode(uint32_t base,
                                       ECAP_CaptureMode mode,
                                       ECAP_Events event)
{
    ASSERT(ECAP_isBaseValid(base));

    EALLOW;

    //
    // Write to CONT/ONESHT
    //
    HWREGH(base + ECAP_O_ECCTL2) =
               ((HWREGH(base + ECAP_O_ECCTL2) & (~ECAP_ECCTL2_CONT_ONESHT)) |
                (uint16_t)mode);

    //
    // Write to STOP_WRAP
    //
    HWREGH(base + ECAP_O_ECCTL2) =
               ((HWREGH(base + ECAP_O_ECCTL2) & (~ECAP_ECCTL2_STOP_WRAP_M)) |
                (((uint16_t)event) << ECAP_ECCTL2_STOP_WRAP_S ));
    EDIS;
}

//*****************************************************************************
//
//! Re-arms the eCAP module.
//!
//! \param base is the base address of the ECAP module.
//!
//! This function re-arms the eCAP module.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_reArm(uint32_t base)
{
    ASSERT(ECAP_isBaseValid(base));

    EALLOW;

    //
    // Write to RE-ARM bit
    //
    HWREGH(base + ECAP_O_ECCTL2) |= ECAP_ECCTL2_REARM;
    EDIS;
}

//*****************************************************************************
//
//! Enables interrupt source.
//!
//! \param base is the base address of the ECAP module.
//! \param intFlags is the interrupt source to be enabled.
//!
//! This function sets and enables eCAP interrupt source. The following are
//! valid interrupt sources.
//!  - ECAP_ISR_SOURCE_CAPTURE_EVENT_1 - Event 1 generates interrupt
//!  - ECAP_ISR_SOURCE_CAPTURE_EVENT_2 - Event 2 generates interrupt
//!  - ECAP_ISR_SOURCE_CAPTURE_EVENT_3 - Event 3 generates interrupt
//!  - ECAP_ISR_SOURCE_CAPTURE_EVENT_4 - Event 4 generates interrupt
//!  - ECAP_ISR_SOURCE_COUNTER_OVERFLOW - Counter overflow generates interrupt
//!  - ECAP_ISR_SOURCE_COUNTER_PERIOD   - Counter equal period generates
//!                                       interrupt
//!  - ECAP_ISR_SOURCE_COUNTER_COMPARE  - Counter equal compare generates
//!                                       interrupt
//!  - ECAP_ISR_SOURCE_MUNIT_1_ERROR_EVT1 - Monitoring unit 1 error event 1
//!                                         generates interrupt
//!  - ECAP_ISR_SOURCE_MUNIT_1_ERROR_EVT2 - Monitoring unit 1 error event 2
//!                                         generates interrupt
//!  - ECAP_ISR_SOURCE_MUNIT_2_ERROR_EVT1 - Monitoring unit 2 error event 1
//!                                         generates interrupt
//!  - ECAP_ISR_SOURCE_MUNIT_2_ERROR_EVT2 - Monitoring unit 2 error event 2
//!                                         generates interrupt
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_enableInterrupt(uint32_t base,
                                        uint16_t intFlags)
{
    ASSERT(ECAP_isBaseValid(base));
    ASSERT((intFlags & ~(ECAP_ISR_SOURCE_CAPTURE_EVENT_1 |
                         ECAP_ISR_SOURCE_CAPTURE_EVENT_2 |
                         ECAP_ISR_SOURCE_CAPTURE_EVENT_3 |
                         ECAP_ISR_SOURCE_CAPTURE_EVENT_4 |
                         ECAP_ISR_SOURCE_COUNTER_OVERFLOW |
                         ECAP_ISR_SOURCE_COUNTER_PERIOD |
                         ECAP_ISR_SOURCE_MUNIT_1_ERROR_EVT1 |
                         ECAP_ISR_SOURCE_MUNIT_1_ERROR_EVT2 |
                         ECAP_ISR_SOURCE_MUNIT_2_ERROR_EVT1 |
                         ECAP_ISR_SOURCE_MUNIT_2_ERROR_EVT2 |
                         ECAP_ISR_SOURCE_COUNTER_COMPARE)) == 0U);


    EALLOW;

    //
    // Set bits in ECEINT register
    //
    HWREGH(base + ECAP_O_ECEINT) |= intFlags;
    EDIS;
}

//*****************************************************************************
//
//! Disables interrupt source.
//!
//! \param base is the base address of the ECAP module.
//! \param intFlags is the interrupt source to be disabled.
//!
//! This function clears and disables eCAP interrupt source. The following are
//! valid interrupt sources.
//!  - ECAP_ISR_SOURCE_CAPTURE_EVENT_1   - Event 1 generates interrupt
//!  - ECAP_ISR_SOURCE_CAPTURE_EVENT_2   - Event 2 generates interrupt
//!  - ECAP_ISR_SOURCE_CAPTURE_EVENT_3   - Event 3 generates interrupt
//!  - ECAP_ISR_SOURCE_CAPTURE_EVENT_4   - Event 4 generates interrupt
//!  - ECAP_ISR_SOURCE_COUNTER_OVERFLOW  - Counter overflow generates interrupt
//!  - ECAP_ISR_SOURCE_COUNTER_PERIOD    - Counter equal period generates
//!                                        interrupt
//!  - ECAP_ISR_SOURCE_COUNTER_COMPARE   - Counter equal compare generates
//!                                        interrupt
//!  - ECAP_ISR_SOURCE_MUNIT_1_ERROR_EVT1 - Monitoring unit 1 error event 1
//!                                         generates interrupt
//!  - ECAP_ISR_SOURCE_MUNIT_1_ERROR_EVT2 - Monitoring unit 1 error event 2
//!                                         generates interrupt
//!  - ECAP_ISR_SOURCE_MUNIT_2_ERROR_EVT1 - Monitoring unit 2 error event 1
//!                                         generates interrupt
//!  - ECAP_ISR_SOURCE_MUNIT_2_ERROR_EVT2 - Monitoring unit 2 error event 2
//!                                         generates interrupt
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_disableInterrupt(uint32_t base,
                                         uint16_t intFlags)
{

    ASSERT(ECAP_isBaseValid(base));
    ASSERT((intFlags & ~(ECAP_ISR_SOURCE_CAPTURE_EVENT_1 |
                         ECAP_ISR_SOURCE_CAPTURE_EVENT_2 |
                         ECAP_ISR_SOURCE_CAPTURE_EVENT_3 |
                         ECAP_ISR_SOURCE_CAPTURE_EVENT_4 |
                         ECAP_ISR_SOURCE_COUNTER_OVERFLOW |
                         ECAP_ISR_SOURCE_COUNTER_PERIOD |
                         ECAP_ISR_SOURCE_MUNIT_1_ERROR_EVT1 |
                         ECAP_ISR_SOURCE_MUNIT_1_ERROR_EVT2 |
                         ECAP_ISR_SOURCE_MUNIT_2_ERROR_EVT1 |
                         ECAP_ISR_SOURCE_MUNIT_2_ERROR_EVT2 |
                         ECAP_ISR_SOURCE_COUNTER_COMPARE)) == 0U);

    EALLOW;

    //
    // Clear bits in ECEINT register
    //
    HWREGH(base + ECAP_O_ECEINT) &= ~intFlags;
    EDIS;
}

//*****************************************************************************
//
//! Returns the interrupt flag.
//!
//! \param base is the base address of the ECAP module.
//!
//! This function returns the eCAP interrupt flag. The following are valid
//! interrupt sources corresponding to the eCAP interrupt flag.
//!
//! \return Returns the eCAP interrupt that has occurred. The following are
//!  valid return values.
//!  - ECAP_ISR_SOURCE_CAPTURE_EVENT_1   - Event 1 generates interrupt
//!  - ECAP_ISR_SOURCE_CAPTURE_EVENT_2   - Event 2 generates interrupt
//!  - ECAP_ISR_SOURCE_CAPTURE_EVENT_3   - Event 3 generates interrupt
//!  - ECAP_ISR_SOURCE_CAPTURE_EVENT_4   - Event 4 generates interrupt
//!  - ECAP_ISR_SOURCE_COUNTER_OVERFLOW  - Counter overflow generates interrupt
//!  - ECAP_ISR_SOURCE_COUNTER_PERIOD    - Counter equal period generates
//!                                        interrupt
//!  - ECAP_ISR_SOURCE_COUNTER_COMPARE   - Counter equal compare generates
//!                                        interrupt
//!  - ECAP_ISR_SOURCE_MUNIT_1_ERROR_EVT1 - Monitoring unit 1 error event 1
//!                                         generates interrupt
//!  - ECAP_ISR_SOURCE_MUNIT_1_ERROR_EVT2 - Monitoring unit 1 error event 2
//!                                         generates interrupt
//!  - ECAP_ISR_SOURCE_MUNIT_2_ERROR_EVT1 - Monitoring unit 2 error event 1
//!                                         generates interrupt
//!  - ECAP_ISR_SOURCE_MUNIT_2_ERROR_EVT2 - Monitoring unit 2 error event 2
//!                                         generates interrupt
//!
//! \note - User can check if a combination of various interrupts have occurred
//!         by ORing the above return values.
//
//*****************************************************************************
static inline uint16_t ECAP_getInterruptSource(uint32_t base)
{
    ASSERT(ECAP_isBaseValid(base));

    //
    // Return contents of ECFLG register
    //
    return(HWREGH(base + ECAP_O_ECFLG) & 0x1EFEU);
}

//*****************************************************************************
//
//! Returns the Global interrupt flag.
//!
//! \param base is the base address of the ECAP module.
//!
//! This function returns the eCAP Global interrupt flag.
//!
//! \return Returns true if there is a global eCAP interrupt, false otherwise.
//
//*****************************************************************************
static inline bool ECAP_getGlobalInterruptStatus(uint32_t base)
{
    ASSERT(ECAP_isBaseValid(base));

    //
    // Return contents of Global interrupt bit
    //
    return((HWREGH(base + ECAP_O_ECFLG) & 0x1U) == 0x1U);
}

//*****************************************************************************
//
//! Clears interrupt flag.
//!
//! \param base is the base address of the ECAP module.
//! \param intFlags is the interrupt source.
//!
//! This function clears eCAP interrupt flags. The following are valid
//! interrupt sources.
//!  - ECAP_ISR_SOURCE_CAPTURE_EVENT_1 - Event 1 generates interrupt
//!  - ECAP_ISR_SOURCE_CAPTURE_EVENT_2 - Event 2 generates interrupt
//!  - ECAP_ISR_SOURCE_CAPTURE_EVENT_3 - Event 3 generates interrupt
//!  - ECAP_ISR_SOURCE_CAPTURE_EVENT_4 - Event 4 generates interrupt
//!  - ECAP_ISR_SOURCE_COUNTER_OVERFLOW - Counter overflow generates interrupt
//!  - ECAP_ISR_SOURCE_COUNTER_PERIOD   - Counter equal period generates
//!                                       interrupt
//!  - ECAP_ISR_SOURCE_COUNTER_COMPARE  - Counter equal compare generates
//!                                       interrupt
//!  - ECAP_ISR_SOURCE_MUNIT_1_ERROR_EVT1 - Monitoring unit 1 error event 1
//!                                         generates interrupt
//!  - ECAP_ISR_SOURCE_MUNIT_1_ERROR_EVT2 - Monitoring unit 1 error event 2
//!                                         generates interrupt
//!  - ECAP_ISR_SOURCE_MUNIT_2_ERROR_EVT1 - Monitoring unit 2 error event 1
//!                                         generates interrupt
//!  - ECAP_ISR_SOURCE_MUNIT_2_ERROR_EVT2 - Monitoring unit 2 error event 2
//!                                         generates interrupt
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_clearInterrupt(uint32_t base,
                                       uint16_t intFlags)
{
    ASSERT(ECAP_isBaseValid(base));
    ASSERT((intFlags & ~(ECAP_ISR_SOURCE_CAPTURE_EVENT_1 |
                         ECAP_ISR_SOURCE_CAPTURE_EVENT_2 |
                         ECAP_ISR_SOURCE_CAPTURE_EVENT_3 |
                         ECAP_ISR_SOURCE_CAPTURE_EVENT_4 |
                         ECAP_ISR_SOURCE_COUNTER_OVERFLOW |
                         ECAP_ISR_SOURCE_COUNTER_PERIOD |
                         ECAP_ISR_SOURCE_MUNIT_1_ERROR_EVT1 |
                         ECAP_ISR_SOURCE_MUNIT_1_ERROR_EVT2 |
                         ECAP_ISR_SOURCE_MUNIT_2_ERROR_EVT1 |
                         ECAP_ISR_SOURCE_MUNIT_2_ERROR_EVT2 |
                         ECAP_ISR_SOURCE_COUNTER_COMPARE)) == 0U);

    //
    // Write to ECCLR register
    //
    HWREGH(base + ECAP_O_ECCLR) = intFlags;
}

//*****************************************************************************
//
//! Clears global interrupt flag
//!
//! \param base is the base address of the ECAP module.
//!
//! This function clears the global interrupt bit.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_clearGlobalInterrupt(uint32_t base)
{
    ASSERT(ECAP_isBaseValid(base));

    //
    // Write to INT bit
    //
    HWREGH(base + ECAP_O_ECCLR) = ECAP_ECCLR_INT;
}

//*****************************************************************************
//
//! Forces interrupt source.
//!
//! \param base is the base address of the ECAP module.
//! \param intFlags is the interrupt source.
//!
//! This function forces and enables eCAP interrupt source. The following are
//! valid interrupt sources.
//!  - ECAP_ISR_SOURCE_CAPTURE_EVENT_1 - Event 1 generates interrupt
//!  - ECAP_ISR_SOURCE_CAPTURE_EVENT_2 - Event 2 generates interrupt
//!  - ECAP_ISR_SOURCE_CAPTURE_EVENT_3 - Event 3 generates interrupt
//!  - ECAP_ISR_SOURCE_CAPTURE_EVENT_4 - Event 4 generates interrupt
//!  - ECAP_ISR_SOURCE_COUNTER_OVERFLOW - Counter overflow generates interrupt
//!  - ECAP_ISR_SOURCE_COUNTER_PERIOD   - Counter equal period generates
//!                                       interrupt
//!  - ECAP_ISR_SOURCE_COUNTER_COMPARE  - Counter equal compare generates
//!                                       interrupt
//!  - ECAP_ISR_SOURCE_MUNIT_1_ERROR_EVT1 - Monitoring unit 1 error event 1
//!                                         generates interrupt
//!  - ECAP_ISR_SOURCE_MUNIT_1_ERROR_EVT2 - Monitoring unit 1 error event 2
//!                                         generates interrupt
//!  - ECAP_ISR_SOURCE_MUNIT_2_ERROR_EVT1 - Monitoring unit 2 error event 1
//!                                         generates interrupt
//!  - ECAP_ISR_SOURCE_MUNIT_2_ERROR_EVT2 - Monitoring unit 2 error event 2
//!                                         generates interrupt
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_forceInterrupt(uint32_t base,
                                       uint16_t intFlags)
{
    ASSERT(ECAP_isBaseValid(base));
    ASSERT((intFlags & ~(ECAP_ISR_SOURCE_CAPTURE_EVENT_1 |
                         ECAP_ISR_SOURCE_CAPTURE_EVENT_2 |
                         ECAP_ISR_SOURCE_CAPTURE_EVENT_3 |
                         ECAP_ISR_SOURCE_CAPTURE_EVENT_4 |
                         ECAP_ISR_SOURCE_COUNTER_OVERFLOW |
                         ECAP_ISR_SOURCE_COUNTER_PERIOD |
                         ECAP_ISR_SOURCE_MUNIT_1_ERROR_EVT1 |
                         ECAP_ISR_SOURCE_MUNIT_1_ERROR_EVT2 |
                         ECAP_ISR_SOURCE_MUNIT_2_ERROR_EVT1 |
                         ECAP_ISR_SOURCE_MUNIT_2_ERROR_EVT2 |
                         ECAP_ISR_SOURCE_COUNTER_COMPARE)) == 0U);

    EALLOW;

    //
    // Write to ECFRC register
    //
    HWREGH(base + ECAP_O_ECFRC) = intFlags;
    EDIS;
}

//*****************************************************************************
//
//! Sets eCAP in Capture mode.
//!
//! \param base is the base address of the ECAP module.
//!
//! This function sets the eCAP module to operate in Capture mode.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_enableCaptureMode(uint32_t base)
{
    ASSERT(ECAP_isBaseValid(base));

    EALLOW;

    //
    // Clear CAP/APWM bit
    //
    HWREGH(base + ECAP_O_ECCTL2) &= ~ECAP_ECCTL2_CAP_APWM;
    EDIS;
}

//*****************************************************************************
//
//! Sets eCAP in APWM mode.
//!
//! \param base is the base address of the ECAP module.
//!
//! This function sets the eCAP module to operate in APWM mode.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_enableAPWMMode(uint32_t base)
{
    ASSERT(ECAP_isBaseValid(base));

    EALLOW;

    //
    // Set CAP/APWM bit
    //
    HWREGH(base + ECAP_O_ECCTL2) |= ECAP_ECCTL2_CAP_APWM;
    EDIS;
}

//*****************************************************************************
//
//! Enables counter reset on an event.
//!
//! \param base is the base address of the ECAP module.
//! \param event is the event number the time base gets reset.
//!
//! This function enables the base timer, TSCTR, to be reset on capture
//! event provided by the variable event. Valid inputs for event are
//! \b ECAP_EVENT_1 to \b ECAP_EVENT_4.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_enableCounterResetOnEvent(uint32_t base,
                                                  ECAP_Events event)
{
    ASSERT(ECAP_isBaseValid(base));

    EALLOW;

    //
    // Set CTRRST1,CTRRST2,CTRRST3 or CTRRST4 bits
    //
    HWREGH(base + ECAP_O_ECCTL1) |= 1U << ((2U * (uint16_t)event) + 1U);
    EDIS;
}

//*****************************************************************************
//
//! Disables counter reset on events.
//!
//! \param base is the base address of the ECAP module.
//! \param event is the event number the time base gets reset.
//!
//! This function disables the base timer, TSCTR, from being reset on capture
//! event provided by the variable event. Valid inputs for event are
//! \b ECAP_EVENT_1 to \b ECAP_EVENT_4.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_disableCounterResetOnEvent(uint32_t base,
                                                   ECAP_Events event)
{
    ASSERT(ECAP_isBaseValid(base));

    EALLOW;

    //
    // Clear CTRRST1,CTRRST2,CTRRST3 or CTRRST4 bits
    //
    HWREGH(base + ECAP_O_ECCTL1) &= ~(1U << ((2U * (uint16_t)event) + 1U));
    EDIS;
}

//*****************************************************************************
//
//! Enables time stamp capture.
//!
//! \param base is the base address of the ECAP module.
//!
//! This function enables time stamp count to be captured
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_enableTimeStampCapture(uint32_t base)
{
    ASSERT(ECAP_isBaseValid(base));

    EALLOW;

    //
    // Set CAPLDEN bit
    //
    HWREGH(base + ECAP_O_ECCTL1) |= ECAP_ECCTL1_CAPLDEN;
    EDIS;
}

//*****************************************************************************
//
//! Disables time stamp capture.
//!
//! \param base is the base address of the ECAP module.
//!
//! This function disables time stamp count to be captured
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_disableTimeStampCapture(uint32_t base)
{
    ASSERT(ECAP_isBaseValid(base));

    EALLOW;

    //
    // Clear CAPLDEN bit
    //
    HWREGH(base + ECAP_O_ECCTL1) &= ~ECAP_ECCTL1_CAPLDEN;
    EDIS;
}

//*****************************************************************************
//
//! Sets a phase shift value count.
//!
//! \param base is the base address of the ECAP module.
//! \param shiftCount is the phase shift value.
//!
//! This function writes a phase shift value to be loaded into the main time
//! stamp counter.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_setPhaseShiftCount(uint32_t base, uint32_t shiftCount)
{
    ASSERT(ECAP_isBaseValid(base));

    //
    // Write to CTRPHS
    //
    HWREG(base + ECAP_O_CTRPHS) = shiftCount;
}

//*****************************************************************************
//
//! Set up the source for sync-in pulse.
//!
//! \param base is the base address of the ECAP module.
//! \param source is the sync-in pulse source.
//!
//! This function set the sync out pulse mode.
//! Valid values for mode are:
//!  - ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWMx - sync-in pulse source can be
//!                                           any of the EPWMx sync-out
//!                                           signal
//!  - ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_ECAPx - sync-in pulse source can be
//!                                           selected as any of the ECAPx
//!                                           sync-out signal
//!  - ECAP_SYNC_IN_PULSE_SRC_INPUTXBAR_OUT5-6 - sync-in pulse source can be
//!                                              selected as any of the Input
//!                                              xbar out5-6 signal
//!  - ECAP_SYNC_IN_PULSE_SRC_ETHERCAT_SYNC0-1 - sync-in pulse source can be
//!                                              selected as any of the
//!                                              Ethercat sync0-1 signal
//!  - ECAP_SYNC_IN_PULSE_SRC_FSI_RXn_RX_TRIG1 - sync-in pulse source can be
//!                                              selected as any of the
//!                                              FSI RXn RX trig signal
//!  - ECAP_SYNC_IN_PULSE_SRC_DISABLE - sync-in pulse is disabled for the
//!                                     ECAP module
//!
//! \return None.
//
//*****************************************************************************
static inline void
ECAP_setSyncInPulseSource(uint32_t base, ECAP_SyncInPulseSource source)
{
    ASSERT(ECAP_isBaseValid(base));

    EALLOW;

    //
    // Set ECAP Sync-In Source Mode.
    //
    HWREGH(base + ECAP_O_SYNCINSEL) =
            (HWREGH(base + ECAP_O_SYNCINSEL) & (~ECAP_SYNCINSEL_SEL_M)) |
            ((uint16_t)source & ECAP_SYNCINSEL_SEL_M);

    EDIS;
}

//*****************************************************************************
//
//! Enable counter loading with phase shift value.
//!
//! \param base is the base address of the ECAP module.
//!
//! This function enables loading of the counter with the value present in the
//! phase shift counter as defined by the ECAP_setPhaseShiftCount() function.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_enableLoadCounter(uint32_t base)
{

    ASSERT(ECAP_isBaseValid(base));

    EALLOW;

    //
    // Write to SYNCI_EN
    //
    HWREGH(base + ECAP_O_ECCTL2) |= ECAP_ECCTL2_SYNCI_EN;
    EDIS;
}

//*****************************************************************************
//
//! Disable counter loading with phase shift value.
//!
//! \param base is the base address of the ECAP module.
//!
//! This function disables loading of the counter with the value present in the
//! phase shift counter as defined by the ECAP_setPhaseShiftCount() function.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_disableLoadCounter(uint32_t base)
{

    ASSERT(ECAP_isBaseValid(base));

    EALLOW;

    //
    // Write to SYNCI_EN
    //
    HWREGH(base + ECAP_O_ECCTL2) &= ~ECAP_ECCTL2_SYNCI_EN;
    EDIS;
}

//*****************************************************************************
//
//! Load time stamp counter
//!
//! \param base is the base address of the ECAP module.
//!
//! This function forces the value in the phase shift counter register to be
//! loaded into Time stamp counter register.
//! Make sure to enable loading of Time stamp counter by calling
//! ECAP_enableLoadCounter() function before calling this function.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_loadCounter(uint32_t base)
{
    ASSERT(ECAP_isBaseValid(base));

    EALLOW;

    //
    // Write to SWSYNC
    //
    HWREGH(base + ECAP_O_ECCTL2) |= ECAP_ECCTL2_SWSYNC;
    EDIS;
}

//*****************************************************************************
//
//! Configures Sync out signal mode.
//!
//! \param base is the base address of the ECAP module.
//! \param mode is the sync out mode.
//!
//! This function sets the sync out mode. Valid parameters for mode are:
//! - ECAP_SYNC_OUT_SYNCI - Trigger sync out on sync-in event.
//! - ECAP_SYNC_OUT_COUNTER_PRD - Trigger sync out when counter equals period.
//! - ECAP_SYNC_OUT_DISABLED - Disable sync out.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_setSyncOutMode(uint32_t base,
                                       ECAP_SyncOutMode mode)
{
    ASSERT(ECAP_isBaseValid(base));

    EALLOW;

    //
    // Write to SYNCO_SEL
    //
     HWREGH(base + ECAP_O_ECCTL2) =
                ((HWREGH(base + ECAP_O_ECCTL2) & (~ECAP_ECCTL2_SYNCO_SEL_M)) |
                 (uint16_t)mode);
    EDIS;
}

//*****************************************************************************
//
//! Stops Time stamp counter.
//!
//! \param base is the base address of the ECAP module.
//!
//! This function stops the time stamp counter.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_stopCounter(uint32_t base)
{
    ASSERT(ECAP_isBaseValid(base));

    EALLOW;

    //
    // Clear TSCTR
    //
    HWREGH(base + ECAP_O_ECCTL2) &= ~ECAP_ECCTL2_TSCTRSTOP;
    EDIS;
}

//*****************************************************************************
//
//! Starts Time stamp counter.
//!
//! \param base is the base address of the ECAP module.
//!
//! This function starts the time stamp counter.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_startCounter(uint32_t base)
{
    ASSERT(ECAP_isBaseValid(base));

    EALLOW;

    //
    // Set TSCTR
    //
    HWREGH(base + ECAP_O_ECCTL2) |= ECAP_ECCTL2_TSCTRSTOP;
    EDIS;
}

//*****************************************************************************
//
//! Set eCAP APWM polarity.
//!
//! \param base is the base address of the ECAP module.
//! \param polarity is the polarity of APWM
//!
//! This function sets the polarity of the eCAP in APWM mode. Valid inputs for
//! polarity are:
//!  - ECAP_APWM_ACTIVE_HIGH - For active high.
//!  - ECAP_APWM_ACTIVE_LOW - For active low.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_setAPWMPolarity(uint32_t base,
                                        ECAP_APWMPolarity polarity)
{
    ASSERT(ECAP_isBaseValid(base));

    EALLOW;
    HWREGH(base + ECAP_O_ECCTL2) =
               ((HWREGH(base + ECAP_O_ECCTL2) & ~ECAP_ECCTL2_APWMPOL) |
                (uint16_t)polarity);
    EDIS;
}

//*****************************************************************************
//
//! Set eCAP APWM period.
//!
//! \param base is the base address of the ECAP module.
//! \param periodCount is the period count for APWM.
//!
//! This function sets the period count of the APWM waveform.
//! periodCount takes the actual count which is written to the register. The
//! user is responsible for converting the desired frequency or time into
//! the period count.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_setAPWMPeriod(uint32_t base, uint32_t periodCount)
{
    ASSERT(ECAP_isBaseValid(base));

    //
    // Write to CAP1
    //
    HWREG(base + ECAP_O_CAP1) = periodCount;
}

//*****************************************************************************
//
//! Set eCAP APWM on or off time count.
//!
//! \param base is the base address of the ECAP module.
//! \param compareCount is the on or off count for APWM.
//!
//! This function sets the on or off time count of the APWM waveform depending
//! on the polarity of the output. If the output , as set by
//! ECAP_setAPWMPolarity(), is active high then compareCount determines the on
//! time. If the output is active low then compareCount determines the off
//! time. compareCount takes the actual count which is written to the register.
//! The user is responsible for converting the desired frequency or time into
//! the appropriate count value.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_setAPWMCompare(uint32_t base, uint32_t compareCount)
{
    ASSERT(ECAP_isBaseValid(base));

    //
    // Write to CAP2
    //
    HWREG(base + ECAP_O_CAP2) = compareCount;
}

//*****************************************************************************
//
//! Load eCAP APWM shadow period.
//!
//! \param base is the base address of the ECAP module.
//! \param periodCount is the shadow period count for APWM.
//!
//! This function sets the shadow period count of the APWM waveform.
//! periodCount takes the actual count which is written to the register. The
//! user is responsible for converting the desired frequency or time into
//! the period count.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_setAPWMShadowPeriod(uint32_t base,
                                            uint32_t periodCount)
{
    ASSERT(ECAP_isBaseValid(base));

    //
    // Write to CAP3
    //
    HWREG(base + ECAP_O_CAP3) = periodCount;
}

//*****************************************************************************
//
//! Set eCAP APWM shadow on or off time count.
//!
//! \param base is the base address of the ECAP module.
//! \param compareCount is the on or off count for APWM.
//!
//! This function sets the shadow on or off time count of the APWM waveform
//! depending on the polarity of the output. If the output , as set by
//! ECAP_setAPWMPolarity() , is active high then compareCount determines the
//! on time. If the output is active low then compareCount determines the off
//! time. compareCount takes the actual count which is written to the register.
//! The user is responsible for converting the desired frequency or time into
//! the appropriate count value.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_setAPWMShadowCompare(uint32_t base,
                                             uint32_t compareCount)
{
    ASSERT(ECAP_isBaseValid(base));

    //
    // Write to CAP4
    //
    HWREG(base + ECAP_O_CAP4) = compareCount;
}

//*****************************************************************************
//
//! Returns the time base counter value.
//!
//! \param base is the base address of the ECAP module.
//!
//! This function returns the time base counter value.
//!
//! \return Returns the time base counter value.
//
//*****************************************************************************
static inline uint32_t ECAP_getTimeBaseCounter(uint32_t base)
{
    ASSERT(ECAP_isBaseValid(base));

    //
    // Read the Time base counter value
    //
    return(HWREG(base + ECAP_O_TSCTR));
}

//*****************************************************************************
//
//! Returns event time stamp.
//!
//! \param base is the base address of the ECAP module.
//! \param event is the event number.
//!
//! This function returns the current time stamp count of the given event.
//! Valid values for event are \b ECAP_EVENT_1 to \b ECAP_EVENT_4.
//!
//! \return Event time stamp value or 0 if \e event is invalid.
//
//*****************************************************************************
static inline uint32_t ECAP_getEventTimeStamp(uint32_t base, ECAP_Events event)
{
    uint32_t count;

    ASSERT(ECAP_isBaseValid(base));


    switch(event)
    {
        case ECAP_EVENT_1:

            //
            // Read CAP1 register
            //
            count = HWREG(base + ECAP_O_CAP1);
        break;

        case ECAP_EVENT_2:
            //
            // Read CAP2 register
            //
            count = HWREG(base + ECAP_O_CAP2);
        break;

        case ECAP_EVENT_3:

            //
            // Read CAP3 register
            //
            count = HWREG(base + ECAP_O_CAP3);
        break;

        case ECAP_EVENT_4:

            //
            // Read CAP4 register
            //
            count = HWREG(base + ECAP_O_CAP4);
        break;

        default:

            //
            // Invalid event parameter
            //
            count = 0U;
        break;
    }

    return(count);
}

//*****************************************************************************
//
//! Select eCAP input.
//!
//! \param base is the base address of the ECAP module.
//! \param input is the eCAP input signal.
//!
//! This function selects the eCAP input signal.
//!
//! Please refer to the ::ECAP_InputCaptureSignals Enum for the valid values
//! to be passed to \e input parameter.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_selectECAPInput(uint32_t base,
                                        ECAP_InputCaptureSignals input)
{
    ASSERT(ECAP_isBaseValid(base));

    EALLOW;

    //
    // Write to ECCTL0
    //
    HWREGH(base + ECAP_O_ECCTL0) =
                ((HWREGH(base + ECAP_O_ECCTL0) & ~ECAP_ECCTL0_INPUTSEL_M) |
                 (uint16_t)input);
    EDIS;
}

//*****************************************************************************
//
//! Select qualification period to filter out noise
//!
//! \param base is the base address of the ECAP module.
//! \param width is the pulse width below which the pulse
//!              will be filtered out.
//!
//! This function selects the qualification period to filter out pulses with
//! width less than the mentioned number of cycles.
//!
//! Please refer to the ::ECAP_QualPeriodSelect Enum for the valid values
//! to be passed to \e width parameter.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_selectQualPeriod(uint32_t base,
                                         ECAP_QualPeriodSelect width)
{
    ASSERT(ECAP_isBaseValid(base));

    EALLOW;

    //
    // Write to ECCTL0 - Qualification Period
    //
    HWREGH(base + ECAP_O_ECCTL0) =
               ((HWREGH(base + ECAP_O_ECCTL0) & ~ECAP_ECCTL0_QUALPRD_M) |
                ((uint32_t)width << ECAP_ECCTL0_QUALPRD_S));
    EDIS;
}

//*****************************************************************************
//
//! Sets the eCAP SOC trigger source.
//!
//! \param base is the base address of the ECAP module.
//! \param event is the eCAP event for the SOC trigger
//!
//! This function sets the eCAP event source in capture mode and APWM mode
//! for the SOC trigger trigger.
//! Valid values for \e event are \b ECAP_EVENT_1 to \b ECAP_EVENT_4.
//!
//! In capture mode of operation -
//! \b ECAP_EVENT_1 - SOC trigger interrupt source is CEVT1
//! \b ECAP_EVENT_2 - SOC trigger interrupt source is CEVT2
//! \b ECAP_EVENT_3 - SOC trigger interrupt source is CEVT3
//! \b ECAP_EVENT_4 - SOC trigger interrupt source is CEVT4
//!
//! In APWM mode of operation -
//! \b ECAP_EVENT_1 - SOC trigger interrupt source is period match
//! \b ECAP_EVENT_2 - SOC trigger interrupt source is compare match
//! \b ECAP_EVENT_3 - SOC trigger interrupt source is period or compare match
//! \b ECAP_EVENT_4 - disabled
//! This function sets the eCAP event source for the SOC trigger trigger.
//! Valid values for \e event are \b ECAP_EVENT_1 to \b ECAP_EVENT_4.
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_setSOCTriggerSource(uint32_t base, ECAP_Events event)
{
    ASSERT(ECAP_isBaseValid(base));

    EALLOW;
    //
    // Write to ECCTL0 - SOC event selection
    //
    HWREG(base + ECAP_O_ECCTL0) =
               ((HWREG(base + ECAP_O_ECCTL0) & ~ECAP_ECCTL0_SOCEVTSEL_M) |
                ((uint32_t)event << ECAP_ECCTL0_SOCEVTSEL_S));
    EDIS;
}
//*****************************************************************************
//
//! Resets eCAP counters and flags.
//!
//! \param base is the base address of the ECAP module.
//!
//! This function resets the main counter (TSCTR register), event filter,
//! modulo counter, capture events and counter overflow flags
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_resetCounters(uint32_t base)
{
    ASSERT(ECAP_isBaseValid(base));

    EALLOW;

    //
    // Write to ECCTL2
    //
    HWREGH(base + ECAP_O_ECCTL2) |= ECAP_ECCTL2_CTRFILTRESET;
    EDIS;
}

//*****************************************************************************
//
//! Sets the eCAP DMA source.
//!
//! \param base is the base address of the ECAP module.
//! \param event is the eCAP event for the DMA
//!
//! This function sets the eCAP event source in capture mode and APWM mode
//! for the DMA trigger.
//! Valid values for \e event are \b ECAP_EVENT_1 to \b ECAP_EVENT_4.
//!
//! In capture mode of operation -
//! \b ECAP_EVENT_1 - DMA interrupt source is CEVT1
//! \b ECAP_EVENT_2 - DMA interrupt source is CEVT2
//! \b ECAP_EVENT_3 - DMA interrupt source is CEVT3
//! \b ECAP_EVENT_4 - DMA interrupt source is CEVT4
//!
//! In APWM mode of operation -
//! \b ECAP_EVENT_1 - DMA interrupt source is period match
//! \b ECAP_EVENT_2 - DMA interrupt source is compare match
//! \b ECAP_EVENT_3 - DMA interrupt source is period or compare match
//! \b ECAP_EVENT_4 - disabled
//!
//! \return None.
//
//*****************************************************************************
static inline void ECAP_setDMASource(uint32_t base, ECAP_Events event)
{
    ASSERT(ECAP_isBaseValid(base));

    EALLOW;

    //
    // Write to ECCTL2
    //
    HWREGH(base + ECAP_O_ECCTL2) =
               ((HWREGH(base + ECAP_O_ECCTL2) & ~ECAP_ECCTL2_DMAEVTSEL_M) |
                ((uint16_t)event << ECAP_ECCTL2_DMAEVTSEL_S));
    EDIS;
}

//*****************************************************************************
//
//! Return the Modulo counter status.
//!
//! \param base is the base address of the ECAP module.
//!
//! This function returns the modulo counter status, indicating which register
//! gets loaded on the next capture event.
//!
//! \return Returns an \b ECAP_EVENT_n value indicating that CAPn is the
//! register to be loaded on the next event.
//
//*****************************************************************************
static inline ECAP_Events ECAP_getModuloCounterStatus(uint32_t base)
{
    uint16_t counterStatusValue;

    ASSERT(ECAP_isBaseValid(base));

    counterStatusValue = (((HWREGH(base + ECAP_O_ECCTL2) &
                            ECAP_ECCTL2_MODCNTRSTS_M) >>
                            ECAP_ECCTL2_MODCNTRSTS_S));

    //
    // Read MODCNTRSTS bit
    //
    return((ECAP_Events)(counterStatusValue));
}

//
// Signal Monitoring related APIs
//
//*****************************************************************************
//
//! Enable eCAP monitoring unit.
//!
//! \param base is the base address of the ECAP signal monitoring module.
//! \param munit is the monitoring unit, either 1 or 2.
//!
//! This function enables the eCAP signal monitoring unit.
//! Valid values for the input variables are:
//! - munit:
//!    - ECAP_MONITORING_UNIT_1 - ECAP Monitoring Unit 1
//!    - ECAP_MONITORING_UNIT_2 - ECAP Monitoring Unit 2
//!
//! \return None.
//
//*****************************************************************************
static inline void
ECAP_enableSignalMonitoringUnit(uint32_t base, uint32_t munit)
{
    uint32_t munitOffset;
    //
    // Check the arguments
    //
    ASSERT(ECAP_isSignalMonitoringBaseValid(base));

    //
    // Get the offset to the appropriate MUNIT configuration register.
    //
    munitOffset = (ECAP_MUNIT_STEP * munit) + ECAP_O_MUNIT_1_CTL;

    //
    // Enable MUNIT
    //
    HWREG(base + munitOffset) |= ECAP_MUNIT_1_CTL_EN;
}

//*****************************************************************************
//
//! Disable eCAP monitoring unit.
//!
//! \param base is the base address of the ECAP signal monitoring module.
//! \param munit is the monitoring unit, either 1 or 2.
//!
//! This function disables the eCAP signal monitoring unit.
//! Valid values for the input variables are:
//! - munit:
//!    - ECAP_MONITORING_UNIT_1 - ECAP Monitoring Unit 1
//!    - ECAP_MONITORING_UNIT_2 - ECAP Monitoring Unit 2
//!
//! \return None.
//
//*****************************************************************************
static inline void
ECAP_disableSignalMonitoringUnit(uint32_t base, uint32_t munit)
{
    uint32_t munitOffset;
    //
    // Check the arguments
    //
    ASSERT(ECAP_isSignalMonitoringBaseValid(base));

    //
    // Get the offset to the appropriate MUNIT configuration register.
    //
    munitOffset = (ECAP_MUNIT_STEP * munit) + ECAP_O_MUNIT_1_CTL;

    //
    // Disable MUNIT
    //
    HWREG(base + munitOffset) &= ~ECAP_MUNIT_1_CTL_EN;
}

//*****************************************************************************
//
//! Enables debug mode to capture range from min to max
//!
//! \param base is the base address of the ECAP signal monitoring module.
//! \param munit is the monitoring unit, either 1 or 2.
//!
//! This function enables the eCAP debug mode for signal monitoring.
//! Range is captured in DEBUG_RANGE_MAX and DEBUG_RANGE_MIN registers.
//!
//! Valid values for the input variables are:
//! - munit:
//!    - ECAP_MONITORING_UNIT_1 - ECAP Monitoring Unit 1
//!    - ECAP_MONITORING_UNIT_2 - ECAP Monitoring Unit 2
//!
//! \return None.
//
//*****************************************************************************
static inline void
ECAP_enableDebugRange(uint32_t base, uint32_t munit)
{
    uint32_t munitOffset;
    //
    // Check the arguments
    //
    ASSERT(ECAP_isSignalMonitoringBaseValid(base));

    //
    // Get the offset to the appropriate MUNIT configuration register.
    //
    munitOffset = (ECAP_MUNIT_STEP * munit) + ECAP_O_MUNIT_1_CTL;

    //
    // Enable debug mode for MUNIT 1
    //
    HWREG(base + munitOffset) |= ECAP_MUNIT_1_CTL_DEBUG_RANGE_EN;
}

//*****************************************************************************
//
//! Disables debug mode to capture range from min to max
//!
//! \param base is the base address of the ECAP signal monitoring module.
//! \param munit is the monitoring unit, either 1 or 2.
//!
//! This function disables the eCAP debug mode for signal monitoring.
//!
//! Valid values for the input variables are:
//! - munit:
//!    - ECAP_MONITORING_UNIT_1 - ECAP Monitoring Unit 1
//!    - ECAP_MONITORING_UNIT_2 - ECAP Monitoring Unit 2
//!
//! \return None.
//
//*****************************************************************************
static inline void
ECAP_disableDebugRange(uint32_t base, uint32_t munit)
{
    uint32_t munitOffset;
    //
    // Check the arguments
    //
    ASSERT(ECAP_isSignalMonitoringBaseValid(base));

    //
    // Get the offset to the appropriate MUNIT configuration register.
    //
    munitOffset = (ECAP_MUNIT_STEP * munit) + ECAP_O_MUNIT_1_CTL;

    //
    // Disable debug mode for MUNIT
    //
    HWREG(base + munitOffset) &= ~ECAP_MUNIT_1_CTL_DEBUG_RANGE_EN;
}

//*****************************************************************************
//
//! Setup the early max error check
//!
//! \param base is the base address of the ECAP signal monitoring module.
//! \param munit is the monitoring unit, either 1 or 2.
//! \param errorCheck is the functionality for early max error check
//!        to be enabled.
//!
//! Valid values for the input variables are:
//! - munit:
//!    - ECAP_MONITORING_UNIT_1 - ECAP Monitoring Unit 1
//!    - ECAP_MONITORING_UNIT_2 - ECAP Monitoring Unit 2
//! - errorCheck:
//!    - ECAP_PULSE_WIDTH_CROSS_MAX_VALUE - Max error generated as soon as
//!                                         pulse width crosses max value
//!    - ECAP_SECOND_EVENT_OCCURED        - Max error generated when second
//!                                         event has occured
//!
//! \return None.
//
//*****************************************************************************
static inline void
ECAP_setupEarlyMaxErrorCheck(uint32_t base, uint32_t munit,
                             uint32_t errorCheck)
{
    uint32_t munitOffset;
    //
    // Check the arguments
    //
    ASSERT(ECAP_isSignalMonitoringBaseValid(base));

    //
    // Get the offset to the appropriate MUNIT configuration register.
    //
    munitOffset = (ECAP_MUNIT_STEP * munit) + ECAP_O_MUNIT_1_CTL;

    //
    // Setup early max error check
    //
    HWREG(base + munitOffset) =
            ((HWREG(base + munitOffset) &
              ~ECAP_MUNIT_1_CTL_DISABLE_EARLY_MAX_ERR) | (errorCheck << 2U));
}

//*****************************************************************************
//
//! Selects the type of monitoring
//!
//! \param base is the base address of the ECAP signal monitoring module.
//! \param munit is the monitoring unit, either 1 or 2.
//! \param monSel is the type of monitoring to be selected.
//!
//! Valid values for the input variables are:
//! - munit:
//!    - ECAP_MONITORING_UNIT_1 - ECAP Monitoring Unit 1
//!    - ECAP_MONITORING_UNIT_2 - ECAP Monitoring Unit 2
//! - monSel:
//!    - ECAP_MUNIT_HIGH_PULSE_WIDTH       - High Pulse Width
//!    - ECAP_MUNIT_LOW_PULSE_WIDTH        - Low Pulse Width
//!    - ECAP_MUNIT_PERIOD_WIDTH_RISE_RISE - Period width from rise to rise
//!    - ECAP_MUNIT_PERIOD_WIDTH_FALL_FALL - Period width from fall to fall
//!    - ECAP_MUNIT_MONITOR_RISE_EDGE      - Monitor rise edge
//!    - ECAP_MUNIT_MONITOR_FALL_EDGE      - Monitor fall edge
//!
//! \return None.
//
//*****************************************************************************
static inline void
ECAP_selectMonitoringType(uint32_t base, uint32_t munit,
                          ECAP_MonitoringTypeSelect monSel)
{
    uint32_t munitOffset;
    //
    // Check the arguments
    //
    ASSERT(ECAP_isSignalMonitoringBaseValid(base));

    //
    // Get the offset to the appropriate MUNIT configuration register.
    //
    munitOffset = (ECAP_MUNIT_STEP * munit) + ECAP_O_MUNIT_1_CTL;

    //
    // Select Monitoring Type for MUNIT
    //
    HWREG(base + munitOffset) =
            (HWREG(base + munitOffset) &
            ~ECAP_MUNIT_1_CTL_MON_SEL_M) |
            ((uint32_t)monSel << ECAP_MUNIT_1_CTL_MON_SEL_S);
}

//*****************************************************************************
//
//! Selects the trip signal to disable and enable monitoring automatically.
//!
//! \param base is the base address of the ECAP signal monitoring module.
//! \param tripSel is the trip signal.
//!
//! Valid values for the input variables are:
//! - tripSel:
//!     - DISABLED
//!     - ECAP_MUNIT_TRIP_EPWM_XBARy_OUTn - y is A/B, n is 0-7
//!     - ECAP_MUNIT_TRIP_EPWMn_TRIPOUT - n is 1-18
//!
//! \return None.
//
//*****************************************************************************
static inline void
ECAP_selectTripSignal(uint32_t base, ECAP_MunitTripInputSelect tripSel)
{
    //
    // Check the arguments
    //
    ASSERT(ECAP_isSignalMonitoringBaseValid(base));

    //
    // Select Monitoring Type
    //
    HWREG(base + ECAP_O_MUNIT_COMMON_CTL) =
            (HWREG(base + ECAP_O_MUNIT_COMMON_CTL) &
             ~ECAP_MUNIT_COMMON_CTL_TRIPSEL_M) |
            ((uint32_t)tripSel << ECAP_MUNIT_COMMON_CTL_TRIPSEL_S);
}

//*****************************************************************************
//
//! Selects the global load strobe to enable shadow to active loading
//!
//! \param base is the base address of the ECAP signal monitoring module.
//! \param strobe is the type of monitoring to be selected.
//!
//! Valid values for the input variables are:
//! - strobe:
//!     - DISABLED
//!     - ECAP_MUNIT_TRIP_EPWM_XBARy_OUTn - y is A/B, n is 0-7
//!     - ECAP_MUNIT_TRIP_EPWMn_TRIPOUT - n is 1-18
//!
//! \return None.
//
//*****************************************************************************
static inline void
ECAP_selectGlobalLoadStrobe(uint32_t base, ECAP_MunitTripInputSelect strobe)
{
    //
    // Check the arguments
    //
    ASSERT(ECAP_isSignalMonitoringBaseValid(base));

    //
    // Select the global load strobe
    //
    HWREG(base + ECAP_O_MUNIT_COMMON_CTL) =
            (HWREG(base + ECAP_O_MUNIT_COMMON_CTL) &
             ~ECAP_MUNIT_COMMON_CTL_GLDSTRBSEL_M) |
            ((uint32_t)strobe << ECAP_MUNIT_COMMON_CTL_GLDSTRBSEL_S);
}

//*****************************************************************************
//
//! Enables shadowing for min and max registers
//!
//! \param base is the base address of the ECAP signal monitoring module.
//! \param munit is the monitoring unit, either 1 or 2.
//!
//! This function enables the shadowing feature for min and max registers.
//!
//! Valid values for the input variable:
//! - munit:
//!    - ECAP_MONITORING_UNIT_1 - ECAP Monitoring Unit 1
//!    - ECAP_MONITORING_UNIT_2 - ECAP Monitoring Unit 2
//!
//! \return None.
//
//*****************************************************************************
static inline void
ECAP_enableShadowMinMaxRegisters(uint32_t base, uint32_t munit)
{
    uint32_t munitOffset;
    //
    // Check the arguments
    //
    ASSERT(ECAP_isSignalMonitoringBaseValid(base));

    //
    // Get the offset to the appropriate MUNIT configuration register.
    //
    munitOffset = (ECAP_MUNIT_STEP * munit) + ECAP_O_MUNIT_1_SHADOW_CTL;

    //
    // Enable shadowing for MUNIT 1
    //
    HWREG(base + munitOffset) |= ECAP_MUNIT_1_SHADOW_CTL_SYNCI_EN;
}

//*****************************************************************************
//
//! Disables shadowing for min and max registers
//!
//! \param base is the base address of the ECAP signal monitoring module.
//! \param munit is the monitoring unit, either 1 or 2.
//!
//! This function disables the shadowing feature for min and max registers.
//!
//! Valid values for the input variable:
//! - munit:
//!    - ECAP_MONITORING_UNIT_1 - ECAP Monitoring Unit 1
//!    - ECAP_MONITORING_UNIT_2 - ECAP Monitoring Unit 2
//!
//! \return None.
//
//*****************************************************************************
static inline void
ECAP_disableShadowMinMaxRegisters(uint32_t base, uint32_t munit)
{
    uint32_t munitOffset;
    //
    // Check the arguments
    //
    ASSERT(ECAP_isSignalMonitoringBaseValid(base));

    //
    // Get the offset to the appropriate MUNIT configuration register.
    //
    munitOffset = (ECAP_MUNIT_STEP * munit) + ECAP_O_MUNIT_1_SHADOW_CTL;

    //
    // Disable shadowing for MUNIT 1
    //
    HWREG(base + munitOffset) &= ~ECAP_MUNIT_1_SHADOW_CTL_SYNCI_EN;
}

//*****************************************************************************
//
//! Enables software sync operation
//!
//! \param base is the base address of the ECAP signal monitoring module.
//! \param munit is the monitoring unit, either 1 or 2.
//!
//! This function enables the SW Sync to copy min and max values from
//! shadow to active registers immediately is shadowing is enabled.
//!
//! Valid values for the input variable:
//! - munit:
//!    - ECAP_MONITORING_UNIT_1 - ECAP Monitoring Unit 1
//!    - ECAP_MONITORING_UNIT_2 - ECAP Monitoring Unit 2
//!
//! \return None.
//
//*****************************************************************************
static inline void
ECAP_enableSoftwareSync(uint32_t base, uint32_t munit)
{
    uint32_t munitOffset;
    //
    // Check the arguments
    //
    ASSERT(ECAP_isSignalMonitoringBaseValid(base));

    //
    // Get the offset to the appropriate MUNIT configuration register.
    //
    munitOffset = (ECAP_MUNIT_STEP * munit) + ECAP_O_MUNIT_1_SHADOW_CTL;

    //
    // Generates SW Sync for MUNIT
    //
    HWREG(base + munitOffset) |= ECAP_MUNIT_1_SHADOW_CTL_SWSYNC;
}

//*****************************************************************************
//
//! Selects the shadow to active load mode
//!
//! \param base is the base address of the ECAP signal monitoring module.
//! \param munit is the monitoring unit, either 1 or 2.
//! \param loadMode is the shadow to active mode to be selected.
//!
//! Valid values for the input variables are:
//! - munit:
//!    - ECAP_MONITORING_UNIT_1 - ECAP Monitoring Unit 1
//!    - ECAP_MONITORING_UNIT_2 - ECAP Monitoring Unit 2
//! - loadMode:
//!    - ECAP_ACTIVE_LOAD_SYNC_EVT       - Active loaded with shadow on
//!                                        next sync event
//!    - ECAP_ACTIVE_LOAD_GLDLCSTRB_EVT  - Active loaded with shadow on
//!                                        EPWM GLDLCSTRB event
//!
//! \return None.
//
//*****************************************************************************
static inline void
ECAP_selectShadowLoadMode(uint32_t base, uint32_t munit,
                          uint32_t loadMode)
{
    uint32_t munitOffset;
    //
    // Check the arguments
    //
    ASSERT(ECAP_isSignalMonitoringBaseValid(base));

    //
    // Get the offset to the appropriate MUNIT configuration register.
    //
    munitOffset = (ECAP_MUNIT_STEP * munit) + ECAP_O_MUNIT_1_SHADOW_CTL;

    //
    // Select shadow to active load mode for MUNIT
    //
    HWREG(base + munitOffset) =
            (HWREG(base + munitOffset) &
             ~ECAP_MUNIT_1_SHADOW_CTL_LOADMODE) |
            (loadMode << 2U);
}

//*****************************************************************************
//
//! Configure minimum value for monitoring
//!
//! \param base is the base address of the ECAP signal monitoring module.
//! \param munit is the monitoring unit, either 1 or 2.
//! \param minValue is the minimum value for monitoring.
//! Valid values for the input variables are:
//! - munit:
//!    - ECAP_MONITORING_UNIT_1 - ECAP Monitoring Unit 1
//!    - ECAP_MONITORING_UNIT_2 - ECAP Monitoring Unit 2
//! - minValue:
//!    - Range from 0x0 to 0xFFFFFFFF
//!
//! \return None.
//
//*****************************************************************************
static inline void
ECAP_configureMinValue(uint32_t base, uint32_t munit,
                       uint32_t minValue)
{
    uint32_t munitOffset;
    //
    // Check the arguments
    //
    ASSERT(ECAP_isSignalMonitoringBaseValid(base));

    //
    // Get the offset to the appropriate MUNIT configuration register.
    //
    munitOffset = (ECAP_MUNIT_STEP * munit) + ECAP_O_MUNIT_1_MIN;

    //
    // Load minimum value for monitoring
    //
    HWREG(base + munitOffset) = minValue;
}

//*****************************************************************************
//
//! Configure maximum value for monitoring
//!
//! \param base is the base address of the ECAP signal monitoring module.
//! \param munit is the monitoring unit, either 1 or 2.
//! \param maxValue is the maximum value for monitoring.
//!
//! Valid values for the input variables are:
//! - munit:
//!    - ECAP_MONITORING_UNIT_1 - ECAP Monitoring Unit 1
//!    - ECAP_MONITORING_UNIT_2 - ECAP Monitoring Unit 2
//! - maxValue:
//!    - Range from 0x0 to 0xFFFFFFFF
//!
//! \return None.
//
//*****************************************************************************
static inline void
ECAP_configureMaxValue(uint32_t base, uint32_t munit,
                       uint32_t maxValue)
{
    uint32_t munitOffset;
    //
    // Check the arguments
    //
    ASSERT(ECAP_isSignalMonitoringBaseValid(base));

    //
    // Get the offset to the appropriate MUNIT configuration register.
    //
    munitOffset = (ECAP_MUNIT_STEP * munit) + ECAP_O_MUNIT_1_MAX;

    //
    // Load maximum value for monitoring
    //
    HWREG(base + munitOffset) = maxValue;
}

//*****************************************************************************
//
//! Configure minimum value for shadow register
//!
//! \param base is the base address of the ECAP signal monitoring module.
//! \param munit is the monitoring unit, either 1 or 2.
//! \param minValue is the minimum value for monitoring.
//! Valid values for the input variables are:
//! - munit:
//!    - ECAP_MONITORING_UNIT_1 - ECAP Monitoring Unit 1
//!    - ECAP_MONITORING_UNIT_2 - ECAP Monitoring Unit 2
//! - minValue:
//!    - Range from 0x0 to 0xFFFFFFFF
//!
//! \return None.
//
//*****************************************************************************
static inline void
ECAP_configureShadowMinValue(uint32_t base, uint32_t munit,
                             uint32_t minValue)
{
    uint32_t munitOffset;
    //
    // Check the arguments
    //
    ASSERT(ECAP_isSignalMonitoringBaseValid(base));

    //
    // Get the offset to the appropriate MUNIT configuration register.
    //
    munitOffset = (ECAP_MUNIT_STEP * munit) + ECAP_O_MUNIT_1_MIN_SHADOW;

    //
    // Load minimum value for monitoring
    //
    HWREG(base + munitOffset) = minValue;
}

//*****************************************************************************
//
//! Configure maximum value for shadow register
//!
//! \param base is the base address of the ECAP signal monitoring module.
//! \param munit is the monitoring unit, either 1 or 2.
//! \param maxValue is the maximum value for monitoring.
//!
//! Valid values for the input variables are:
//! - munit:
//!    - ECAP_MONITORING_UNIT_1 - ECAP Monitoring Unit 1
//!    - ECAP_MONITORING_UNIT_2 - ECAP Monitoring Unit 2
//! - maxValue:
//!    - Range from 0x0 to 0xFFFFFFFF
//!
//! \return None.
//
//*****************************************************************************
static inline void
ECAP_configureShadowMaxValue(uint32_t base, uint32_t munit,
                             uint32_t maxValue)
{
    uint32_t munitOffset;
    //
    // Check the arguments
    //
    ASSERT(ECAP_isSignalMonitoringBaseValid(base));

    //
    // Get the offset to the appropriate MUNIT configuration register.
    //
    munitOffset = (ECAP_MUNIT_STEP * munit) + ECAP_O_MUNIT_1_MAX_SHADOW;

    //
    // Load maximum value for monitoring
    //
    HWREG(base + munitOffset) = maxValue;
}

//*****************************************************************************
//
//! Returns observed minimum value
//!
//! \param base is the base address of the ECAP signal monitoring module.
//! \param munit is the monitoring unit, either 1 or 2.
//!
//! This function returns the observed minimum value when the DEBUG_RANGE_EN
//! bit is set to 1.
//!
//! Valid values for the input variables are:
//! - munit:
//!    - ECAP_MONITORING_UNIT_1 - ECAP Monitoring Unit 1
//!    - ECAP_MONITORING_UNIT_2 - ECAP Monitoring Unit 2
//!
//! \return returns the observed minimum value.
//
//*****************************************************************************
static inline uint32_t
ECAP_observedMinValue(uint32_t base, uint32_t munit)
{
    uint32_t munitOffset;
    //
    // Check the arguments
    //
    ASSERT(ECAP_isSignalMonitoringBaseValid(base));

    //
    // Get the offset to the appropriate MUNIT configuration register.
    //
    munitOffset = (ECAP_MUNIT_STEP * munit) + ECAP_O_MUNIT_1_DEBUG_RANGE_MIN;

    //
    // Returns minimum value
    //
    return(HWREG(base + munitOffset));
}

//*****************************************************************************
//
//! Returns observed maximum value
//!
//! \param base is the base address of the ECAP signal monitoring module.
//! \param munit is the monitoring unit, either 1 or 2.
//!
//! This function returns the observed maximum value when the DEBUG_RANGE_EN
//! bit is set to 1.
//!
//! Valid values for the input variables are:
//! - munit:
//!    - ECAP_MONITORING_UNIT_1 - ECAP Monitoring Unit 1
//!    - ECAP_MONITORING_UNIT_2 - ECAP Monitoring Unit 2
//!
//! \return returns the observed maximum value.
//
//*****************************************************************************
static inline uint32_t
ECAP_observedMaxValue(uint32_t base, uint32_t munit)
{
    uint32_t munitOffset;
    //
    // Check the arguments
    //
    ASSERT(ECAP_isSignalMonitoringBaseValid(base));

    //
    // Get the offset to the appropriate MUNIT configuration register.
    //
    munitOffset = (ECAP_MUNIT_STEP * munit) + ECAP_O_MUNIT_1_DEBUG_RANGE_MAX;

    //
    // Returns maximum value
    //
    return(HWREG(base + munitOffset));
}
//*****************************************************************************
//
//! Configures emulation mode.
//!
//! \param base is the base address of the ECAP module.
//! \param mode is the emulation mode.
//!
//! This function configures the eCAP counter, TSCTR,  to the desired emulation
//! mode when emulation suspension occurs. Valid inputs for mode are:
//! - ECAP_EMULATION_STOP  - Counter is stopped immediately.
//! - ECAP_EMULATION_RUN_TO_ZERO - Counter runs till it reaches 0.
//! - ECAP_EMULATION_FREE_RUN - Counter is not affected.
//!
//! \return None.
//
//*****************************************************************************
extern void ECAP_setEmulationMode(uint32_t base, ECAP_EmulationMode mode);

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // ECAP_H
