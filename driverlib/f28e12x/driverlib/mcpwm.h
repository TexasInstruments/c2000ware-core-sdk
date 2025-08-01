//###########################################################################
//
// FILE:   mcpwm.h
//
// TITLE:  C28x MCPWM driver.
//
//###########################################################################
// $Copyright:
// Copyright (C) 2025 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef MCPWM_H
#define MCPWM_H

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
//! \addtogroup mcpwm_api MCPWM
//! @{
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_mcpwm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "cpu.h"
#include "debug.h"


//*****************************************************************************
//
// Defines for the API.
//
//*****************************************************************************

//*****************************************************************************
//
//! Values that can be passed to MCPWM_setTimeBaseCounterMode() as the
//! \e counterMode parameter.
//
//*****************************************************************************
typedef enum
{
    MCPWM_COUNTER_MODE_UP = 0,         //!< Up - count mode
    MCPWM_COUNTER_MODE_UP_DOWN = 1,    //!< Up - down - count mode
    MCPWM_COUNTER_MODE_STOP_FREEZE = 2 //!< Stop - Freeze counter
} MCPWM_TimeBaseCountMode;

//*****************************************************************************
//
// Values that can be returned by the MCPWM_getTimeBaseCounterDirection()
//
//*****************************************************************************
//! Time base counter is counting up
//!
#define MCPWM_TIME_BASE_STATUS_COUNT_UP                1U
//! Time base counter is counting down
//!
#define MCPWM_TIME_BASE_STATUS_COUNT_DOWN              0U

//*****************************************************************************
//
//! Values that can be passed to MCPWM_setClockPrescaler() as the
//! \e prescaler parameter.
//
//*****************************************************************************
typedef enum
{
    MCPWM_CLOCK_DIVIDER_1 = 0,          //!< Divide clock by 1
    MCPWM_CLOCK_DIVIDER_2 = 1,          //!< Divide clock by 2
    MCPWM_CLOCK_DIVIDER_4 = 2,          //!< Divide clock by 4
    MCPWM_CLOCK_DIVIDER_8 = 3,          //!< Divide clock by 8
    MCPWM_CLOCK_DIVIDER_16 = 4,         //!< Divide clock by 16
    MCPWM_CLOCK_DIVIDER_32 = 5,         //!< Divide clock by 32
    MCPWM_CLOCK_DIVIDER_64 = 6,         //!< Divide clock by 64
    MCPWM_CLOCK_DIVIDER_128 = 7,        //!< Divide clock by 128
    MCPWM_CLOCK_DIVIDER_256 = 8,        //!< Divide clock by 256
    MCPWM_CLOCK_DIVIDER_512 = 9,        //!< Divide clock by 512
    MCPWM_CLOCK_DIVIDER_1024 = 10,      //!< Divide clock by 1024
    MCPWM_CLOCK_DIVIDER_2048 = 11,      //!< Divide clock by 2048
    MCPWM_CLOCK_DIVIDER_4096 = 12,      //!< Divide clock by 4096
    MCPWM_CLOCK_DIVIDER_8192 = 13,      //!< Divide clock by 8192
    MCPWM_CLOCK_DIVIDER_16384 = 14,     //!< Divide clock by 16384
    MCPWM_CLOCK_DIVIDER_32768 = 15,     //!< Divide clock by 32768
} MCPWM_ClockDivider;

//*****************************************************************************
//
//! Values that can be passed to MCPWM_setEmulationMode() as the
//! \e emulationMode parameter.
//
//*****************************************************************************
typedef enum
{
   //! Stop after next Time Base counter increment or decrement
   MCPWM_EMULATION_STOP_AFTER_NEXT_TB = 0,
   //! Stop when counter completes whole cycle
   MCPWM_EMULATION_STOP_AFTER_FULL_CYCLE = 1,
   //! Free run
   MCPWM_EMULATION_FREE_RUN = 2
} MCPWM_EmulationMode;

//*****************************************************************************
//
//! Values that can be passed to MCPWM_setPeriodLoadMode()  as the
//! \e loadMode parameter.
//!
//! \note 
//!     1. If the period load mode is set to \b MCPWM_PERIOD_SHADOW_LOAD_ENABLE,
//!         the shadow register will be loaded to active register at TBCTR=0. So,
//!         the value set by MCPWM_setTimebasePeriodActive() will be overwritten by 
//!         the value set by MCPWM_setTimebasePeriodShadow(), if not set, 
//!         the reset default of shadow register, 0.
//!
//!     2. The global load trigger, if enabled, overrides the local load mode.
//
//*****************************************************************************
typedef enum
{
    //! PWM Active Period register loads from Shadow register at TBCTR=0 event
    MCPWM_PERIOD_SHADOW_LOAD_ENABLE = 0,
    //! PWM Period register load from Shadow register is disabled 
    MCPWM_PERIOD_SHADOW_LOAD_DISABLE = 1
} MCPWM_PeriodLoadMode;

//*****************************************************************************
//
//! Values that can be passed to MCPWM_setCountModeAfterSync() as the
//! \e mode parameter.
//
//*****************************************************************************
typedef enum
{
   MCPWM_COUNT_MODE_DOWN_AFTER_SYNC = 0, //!< Count down after sync event
   MCPWM_COUNT_MODE_UP_AFTER_SYNC = 1    //!< Count up after sync event
} MCPWM_SyncCountMode;

//*****************************************************************************
//
//! Values that can be passed to MCPWM_setSyncOutPulseMode() as the \e mode
//! parameter.
//
//*****************************************************************************
typedef enum
{
    //! Sync pulse is generated by software
    MCPWM_SYNC_OUT_PULSE_ON_SOFTWARE  = 0,
    //! Sync pulse is generated when time base counter equals zero
    MCPWM_SYNC_OUT_PULSE_ON_COUNTER_ZERO = 1,
    //! Sync pulse is generated when time base counter equals compare C value
    MCPWM_SYNC_OUT_PULSE_ON_COUNTER_COMPARE_C = 2,
    //! Sync pulse is generated when time base counter equals compare D value
    MCPWM_SYNC_OUT_PULSE_ON_COUNTER_COMPARE_D = 3,
    //! Sync pulse is disabled
    MCPWM_SYNC_OUT_PULSE_DISABLED = 4
} MCPWM_SyncOutPulseMode;

//*****************************************************************************
//
//! Values that can be passed to MCPWM_setSyncPulseSource() as the 
//! \e syncPulseSource parameter.
//
//*****************************************************************************
typedef enum
{
    //! Sync Peripheral Signal Pulse is disabled
    MCPWM_SYNC_PULSE_DISABLED = 0,
    //! Sync Peripheral Signal Pulse is generated when time base counter equals Period
    MCPWM_SYNCPERSEL_SOURCE_PERIOD  = 2,
    //! Sync Peripheral Signal Pulse is generated when time base counter equals zero
    MCPWM_SYNCPERSEL_SOURCE_ZERO = 3,
    //! Sync Peripheral Signal Pulse is generated when time base counter equals compare C value while counting up
    MCPWM_SYNCPERSEL_SOURCE_CMPC_UP = 4,
    //! Sync Peripheral Signal Pulse is generated when time base counter equals compare C value while counting down
    MCPWM_SYNCPERSEL_SOURCE_CMPC_DOWN = 5,
    //! Sync Peripheral Signal Pulse is generated when time base counter equals compare D value while counting up
    MCPWM_SYNCPERSEL_SOURCE_CMPD_UP = 6,
    //! Sync Peripheral Signal Pulse is generated when time base counter equals compare D value while counting down
    MCPWM_SYNCPERSEL_SOURCE_CMPD_DOWN = 7
} MCPWM_SyncPulseSource;

//*****************************************************************************
//
//! Values that can be passed to MCPWM_setSyncInPulseSource() as the \e mode
//! parameter.
//
//*****************************************************************************
typedef enum
{
	MCPWM_SYNC_IN_PULSE_SRC_DISABLE		 = 0x0,	//!Disable Sync-in
	MCPWM_SYNC_IN_PULSE_SRC_INPUTXBAR_OUT5		 = 0x1,	//!Sync-in source is Input XBAR out5 signal
	MCPWM_SYNC_IN_PULSE_SRC_INPUTXBAR_OUT6		 = 0x2,	//!Sync-in source is Input XBAR out6 signal
	MCPWM_SYNC_IN_PULSE_SRC_SYNCOUT_ECAP1		 = 0x3,	//!Sync-in source is ECAP1 sync-out signal
	MCPWM_SYNC_IN_PULSE_SRC_SYNCOUT_MCPWM1		 = 0x5,	//!Sync-in source is MCPWM1 sync-out signal
	MCPWM_SYNC_IN_PULSE_SRC_SYNCOUT_MCPWM3		 = 0x7	//!Sync-in source is MCPWM3 sync-out signal
} MCPWM_SyncInPulseSource;


//
// Counter Compare Module
//
//*****************************************************************************
//
//! Values that can be passed to the MCPWM_setCounterCompareActiveValue(), 
//! MCPWM_setCounterCompareShadowValue(),
//! MCPWM_getCounterCompareActiveValue(), 
//! MCPWM_getCounterCompareShadowValue(), 
//! MCPWM_setCounterCompareShadowLoadMode(),
//! MCPWM_disableCounterCompareShadowLoadMode()
//! as the \e compModule parameter.
//
//*****************************************************************************
typedef enum
{
    MCPWM_COUNTER_COMPARE_1A = 0, //!< Counter compare 1A
    MCPWM_COUNTER_COMPARE_1B = 1, //!< Counter compare 1B
    MCPWM_COUNTER_COMPARE_2A = 2, //!< Counter compare 2A
    MCPWM_COUNTER_COMPARE_2B = 3, //!< Counter compare 2B
    MCPWM_COUNTER_COMPARE_3A = 4, //!< Counter compare 3A
    MCPWM_COUNTER_COMPARE_3B = 5, //!< Counter compare 3B
    MCPWM_COUNTER_COMPARE_C = 6, //!< Counter compare C
    MCPWM_COUNTER_COMPARE_D = 7  //!< Counter compare D
} MCPWM_CounterCompareModule;

//*****************************************************************************
//
//! Values that can be passed to MCPWM_setCounterCompareShadowLoadMode() as the
//! \e loadMode parameter.
//!
//! \note 
//!     1. If the load mode is set to any value other than MCPWM_COMP_LOAD_FREEZE,
//!         the shadow register value set by MCPWM_setCounterCompareShadowValue() 
//!         will be loaded / overwritten to active register, set by 
//!         MCPWM_setCounterCompareActiveValue() when the event is generated.
//!
//!     2. The global load trigger, if enabled, overrides the local load mode.
//
//*****************************************************************************
typedef enum
{
    //! Load when counter equals zero
    MCPWM_COMP_LOAD_ON_CNTR_ZERO = 0,
    //! Load when counter equals period
    MCPWM_COMP_LOAD_ON_CNTR_PERIOD = 1,
    //! Load when counter equals zero or period
    MCPWM_COMP_LOAD_ON_CNTR_ZERO_PERIOD = 2,
    //! Freeze shadow to active load
    MCPWM_COMP_LOAD_FREEZE = 3
} MCPWM_CounterCompareLoadMode;

//*****************************************************************************
//
//! Values that can be passed to MCPWM_setActionQualifierSWOneShotTrigger(),
//! MCPWM_setActionQualifierSWAction(), MCPWM_setActionQualifierActionActive(),
//! MCPWM_setActionQualifierActionShadow(),
//! MCPWM_setActionQualifierContSWForceAction() as the \e MCpwmOutput parameter.
//
//*****************************************************************************
typedef enum
{
    MCPWM_AQ_OUTPUT_1A = 0,  //!< MCPWMx1A output
    MCPWM_AQ_OUTPUT_1B = 1,  //!< MCPWMx1B output
    MCPWM_AQ_OUTPUT_2A = 2,  //!< MCPWMx2A output
    MCPWM_AQ_OUTPUT_2B = 3,  //!< MCPWMx2B output
    MCPWM_AQ_OUTPUT_3A = 4,  //!< MCPWMx3A output
    MCPWM_AQ_OUTPUT_3B = 5   //!< MCPWMx3B output
} MCPWM_ActionQualifierOutputModule;

//*****************************************************************************
//
//! Values that can be passed to MCPWM_setActionQualifierSWAction(),
//! MCPWM_setActionQualifierActionActive(),
//! MCPWM_setActionQualifierActionShadow() as the \e outPut parameter.
//
//*****************************************************************************
typedef enum
{
    MCPWM_AQ_OUTPUT_NO_CHANGE = 0,  //!< No change in the output pins
    MCPWM_AQ_OUTPUT_LOW       = 1,  //!< Set output pins to low
    MCPWM_AQ_OUTPUT_HIGH      = 2,  //!< Set output pins to High
    MCPWM_AQ_OUTPUT_TOGGLE    = 3   //!< Toggle the output pins
} MCPWM_ActionQualifierOutput;

//*****************************************************************************
//
//! Values that can be passed to MCPWM_setActionQualifierSWAction as \e output
//! parameter.
//
//*****************************************************************************
typedef enum
{
    MCPWM_AQ_SW_FORCE_DISABLED   = 0,  //!< SW force Action is disabled
    MCPWM_AQ_SW_CONTINUOUS_LOW   = 1,  //!< Set output pins to continuos low
    MCPWM_AQ_SW_CONTINUOUS_HIGH  = 2,  //!< Set output pins to continuos High
    MCPWM_AQ_SW_ONE_SHOT_LOW     = 5,  //!< Set output to low when one shot is triggered
    MCPWM_AQ_SW_ONE_SHOT_HIGH    = 6,  //!< Set output to high when one shot is triggered
    MCPWM_AQ_SW_ONE_SHOT_TOGGLE  = 7  //!< Toggle output when one shot is triggered
} MCPWM_ActionQualifierSWForceOutput;

//*****************************************************************************
//
//! Values that can be passed to MCPWM_setActionQualifierShadowLoadMode()
//! as the \e aqModule parameter.
//
//*****************************************************************************
typedef enum
{
    MCPWM_ACTION_QUALIFIER_1A = 0, //!< Action Qualifier A
    MCPWM_ACTION_QUALIFIER_1B = 1,  //!< Action Qualifier B
    MCPWM_ACTION_QUALIFIER_2A = 2, //!< Action Qualifier A
    MCPWM_ACTION_QUALIFIER_2B = 3,  //!< Action Qualifier B
    MCPWM_ACTION_QUALIFIER_3A = 4, //!< Action Qualifier A
    MCPWM_ACTION_QUALIFIER_3B = 5  //!< Action Qualifier B
} MCPWM_ActionQualifierModule;

//*****************************************************************************
//
//! Values that can be passed to MCPWM_setActionQualifierShadowLoadMode() as the
//! \e loadMode parameter.
//!
//! \note 
//!     1. If the load mode is set to any value other than MCPWM_AQ_LOAD_FREEZE,
//!         the shadow register value set by 
//!             a. MCPWM_setActionQualifierActionShadow(), or
//!             b. MCPWM_setActionQualifierActionCompleteShadow()
//!         will be loaded / overwritten to active register, set by 
//!             a. MCPWM_setActionQualifierActionActive(), or
//!             b. MCPWM_setActionQualifierActionCompleteActive()
//!         when the event is generated.
//!
//!     2. The global load trigger, if enabled, overrides the local load mode.
//
//*****************************************************************************
typedef enum
{
    //! Load when counter equals zero
    MCPWM_AQ_LOAD_ON_CNTR_ZERO = 0,
    //! Load when counter equals period
    MCPWM_AQ_LOAD_ON_CNTR_PERIOD = 1,
    //! Load when counter equals zero or period
    MCPWM_AQ_LOAD_ON_CNTR_ZERO_PERIOD = 2,
    //! Freeze shadow to active load
    MCPWM_AQ_LOAD_FREEZE = 3
} MCPWM_ActionQualifierLoadMode;

//*****************************************************************************
//
//! Values that can be passed to MCPWM_setActionQualifierActionActive() and
//! MCPWM_setActionQualifierActionShadow() as the \e
//! event parameter.
//
//*****************************************************************************
typedef enum
{
    //! Time base counter equals zero
    MCPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO       = MCPWM_PWM1_AQCTLA_ZRO_S,
    //! Time base counter equals period
    MCPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD     = MCPWM_PWM1_AQCTLA_PRD_S,
    //! Time base counter up equals CMPA
    MCPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA    = MCPWM_PWM1_AQCTLA_CAU_S,
    //! Time base counter down equals CMPA
    MCPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA  = MCPWM_PWM1_AQCTLA_CAD_S,
    //! Time base counter up equals CMPB
    MCPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB    = MCPWM_PWM1_AQCTLA_CBU_S,
    //! Time base counter down equals CMPB
    MCPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB  = MCPWM_PWM1_AQCTLA_CBD_S
} MCPWM_ActionQualifierOutputEvent;

//*****************************************************************************
//
//! Values that can be passed to MCPWM_setActionQualifierActionCompleteActive(),
//! MCPWM_setActionQualifierActionCompleteShadow()
//! as the \e action parameter.
//
//*****************************************************************************
typedef enum
{
    //! Time base counter equals zero and no change in the output pins
    MCPWM_AQ_OUTPUT_NO_CHANGE_ZERO = 0x0,
    //! Time base counter equals zero and set output pins to low
    MCPWM_AQ_OUTPUT_LOW_ZERO = 0x1,
    //! Time base counter equals zero and set output pins to high
    MCPWM_AQ_OUTPUT_HIGH_ZERO = 0x2,
    //! Time base counter equals zero and toggle the output pins
    MCPWM_AQ_OUTPUT_TOGGLE_ZERO = 0x3,
    //! Time base counter equals period and no change in the output pins
    MCPWM_AQ_OUTPUT_NO_CHANGE_PERIOD = 0x0,
    //! Time base counter equals period and set output pins to low
    MCPWM_AQ_OUTPUT_LOW_PERIOD = 0x4,
    //! Time base counter equals period and set output pins to high
    MCPWM_AQ_OUTPUT_HIGH_PERIOD = 0x8,
    //! Time base counter equals period and toggle the output pins
    MCPWM_AQ_OUTPUT_TOGGLE_PERIOD = 0xC,
    //! Time base counter up equals CMPA and no change in the output pins
    MCPWM_AQ_OUTPUT_NO_CHANGE_UP_CMPA = 0x00,
    //! Time base counter up equals CMPA and set output pins to low
    MCPWM_AQ_OUTPUT_LOW_UP_CMPA = 0x10,
    //! Time base counter up equals CMPA and set output pins to high
    MCPWM_AQ_OUTPUT_HIGH_UP_CMPA = 0x20,
    //! Time base counter up equals CMPA and toggle the output pins
    MCPWM_AQ_OUTPUT_TOGGLE_UP_CMPA = 0x30,
    //! Time base counter down equals CMPA and no change in the output pins
    MCPWM_AQ_OUTPUT_NO_CHANGE_DOWN_CMPA = 0x00,
    //! Time base counter down equals CMPA and set output pins to low
    MCPWM_AQ_OUTPUT_LOW_DOWN_CMPA = 0x40,
    //! Time base counter down equals CMPA and set output pins to high
    MCPWM_AQ_OUTPUT_HIGH_DOWN_CMPA = 0x80,
    //! Time base counter down equals CMPA and toggle the output pins
    MCPWM_AQ_OUTPUT_TOGGLE_DOWN_CMPA = 0xC0,
    //! Time base counter up equals CMPB and no change in the output pins
    MCPWM_AQ_OUTPUT_NO_CHANGE_UP_CMPB = 0x000,
    //! Time base counter up equals CMPB and set output pins to low
    MCPWM_AQ_OUTPUT_LOW_UP_CMPB = 0x100,
    //! Time base counter up equals CMPB and set output pins to high
    MCPWM_AQ_OUTPUT_HIGH_UP_CMPB = 0x200,
    //! Time base counter up equals CMPB and toggle the output pins
    MCPWM_AQ_OUTPUT_TOGGLE_UP_CMPB = 0x300,
    //! Time base counter down equals CMPB and no change in the output pins
    MCPWM_AQ_OUTPUT_NO_CHANGE_DOWN_CMPB = 0x000,
    //! Time base counter down equals CMPB and set output pins to low
    MCPWM_AQ_OUTPUT_LOW_DOWN_CMPB = 0x400,
    //! Time base counter down equals CMPB and set output pins to high
    MCPWM_AQ_OUTPUT_HIGH_DOWN_CMPB = 0x800,
    //! Time base counter down equals CMPB and toggle the output pins
    MCPWM_AQ_OUTPUT_TOGGLE_DOWN_CMPB = 0xC00
} MCPWM_ActionQualifierEventAction;

//*****************************************************************************
//
//! Values that can be passed to MCPWM_setGlobalLoadTrigger() as the
//! \e loadTrigger parameter.
//! 
//
//*****************************************************************************
typedef enum
{
    //! Load when counter is equal to zero
    MCPWM_GL_LOAD_PULSE_CNTR_ZERO = 0x0,
    //! Load when counter is equal to period
    MCPWM_GL_LOAD_PULSE_CNTR_PERIOD = 0x1,
    //! Load when counter is equal to zero or period
    MCPWM_GL_LOAD_PULSE_CNTR_ZERO_PERIOD = 0x2,
    //! Load on global force
    MCPWM_GL_LOAD_PULSE_GLOBAL_FORCE = 0xF
} MCPWM_GlobalLoadTrigger;

//*****************************************************************************
//
//! Values that can be passed to MCPWM_setDeadBandOutputSwapMode()
//! as the \e output parameter.
//
//*****************************************************************************
typedef enum
{
    MCPWM_DB_OUTPUT_A = 1, //!< DB output is MCPWMA
    MCPWM_DB_OUTPUT_B = 0  //!< DB output is MCPWMB
} MCPWM_DeadBandOutput;

//*****************************************************************************
//
//! Values that can be passed to MCPWM_setDeadBandDelayPolarity(),
//! MCPWM_setDeadBandDelayMode() as the \e delayMode parameter.
//
//*****************************************************************************
typedef enum
{
    MCPWM_DB_RED = 1, //!< DB RED (Rising Edge Delay) mode
    MCPWM_DB_FED = 0  //!< DB FED (Falling Edge Delay) mode
} MCPWM_DeadBandDelayMode;

//*****************************************************************************
//
//! Values that can be passed to MCPWM_setDeadBandDelayPolarity as the
//! \e polarity parameter.
//
//*****************************************************************************
typedef enum
{
    MCPWM_DB_POLARITY_ACTIVE_HIGH = 0, //!< DB polarity is not inverted
    MCPWM_DB_POLARITY_ACTIVE_LOW  = 1  //!< DB polarity is inverted
} MCPWM_DeadBandPolarity;

//*****************************************************************************
//
// Values that can be passed to MCPWM_setRisingEdgeDeadBandDelayInput(),
// MCPWM_setFallingEdgeDeadBandDelayInput() as the input parameter.
//
//*****************************************************************************
//! Input signal is MCPWMA
//!
#define MCPWM_DB_INPUT_MCPWMA       0U
//! Input signal is MCPWMB
//!
#define MCPWM_DB_INPUT_MCPWMB       1U
//! Input signal is the output of Rising Edge delay
//!
#define MCPWM_DB_INPUT_DB_RED      2U

//*****************************************************************************
//
//! Values that can be passed to MCPWM_setRisingEdgeDelayCountShadowLoadMode()
//! as the \e loadMode parameter.
//
//*****************************************************************************
typedef enum
{
    //! Load when counter equals zero
    MCPWM_RED_LOAD_ON_CNTR_ZERO        = 0,
    //! Load when counter equals period
    MCPWM_RED_LOAD_ON_CNTR_PERIOD      = 1,
    //! Load when counter equals zero or period
    MCPWM_RED_LOAD_ON_CNTR_ZERO_PERIOD = 2,
    //! Freeze shadow to active load
    MCPWM_RED_LOAD_FREEZE = 3
} MCPWM_RisingEdgeDelayLoadMode;

//*****************************************************************************
//
//! Values that can be passed to MCPWM_setFallingEdgeDelayCountShadowLoadMode()
//! as the \e loadMode parameter.
//
//*****************************************************************************
typedef enum
{
    //! Load when counter equals zero
    MCPWM_FED_LOAD_ON_CNTR_ZERO        = 0,
    //! Load when counter equals period
    MCPWM_FED_LOAD_ON_CNTR_PERIOD      = 1,
    //! Load when counter equals zero or period
    MCPWM_FED_LOAD_ON_CNTR_ZERO_PERIOD = 2,
    //! Freeze shadow to active load
    MCPWM_FED_LOAD_FREEZE = 3
} MCPWM_FallingEdgeDelayLoadMode;

//*****************************************************************************
//
// Values that can be passed to MCPWM_enableTripZoneSignals() and
// MCPWM_disableTripZoneSignals() as the tzSignal parameter.
//
//*****************************************************************************
//! TZ1 Cycle By Cycle
//!
#define MCPWM_TZ_SIGNAL_CBC1          MCPWM_TZSEL_CBC1
//! TZ2 Cycle By Cycle
//!
#define MCPWM_TZ_SIGNAL_CBC2          MCPWM_TZSEL_CBC2
//! TZ3 Cycle By Cycle
//!
#define MCPWM_TZ_SIGNAL_CBC3          MCPWM_TZSEL_CBC3
//! TZ4 Cycle By Cycle
//!
#define MCPWM_TZ_SIGNAL_CBC4          MCPWM_TZSEL_CBC4
//! TZ5 Cycle By Cycle
//!
#define MCPWM_TZ_SIGNAL_CBC5          MCPWM_TZSEL_CBC5
//! TZ6 Cycle By Cycle
//!
#define MCPWM_TZ_SIGNAL_CBC6          MCPWM_TZSEL_CBC6
//! TZ7 Cycle By Cycle
//!
#define MCPWM_TZ_SIGNAL_CBC7          MCPWM_TZSEL_CBC7
//! TZ8 Cycle By Cycle
//!
#define MCPWM_TZ_SIGNAL_CBC8          MCPWM_TZSEL_CBC8
//! One-shot TZ1
//!
#define MCPWM_TZ_SIGNAL_OSHT1         MCPWM_TZSEL_OST1
//! One-shot TZ2
//!
#define MCPWM_TZ_SIGNAL_OSHT2         MCPWM_TZSEL_OST2
//! One-shot TZ3
//!
#define MCPWM_TZ_SIGNAL_OSHT3         MCPWM_TZSEL_OST3
//! One-shot TZ4
//!
#define MCPWM_TZ_SIGNAL_OSHT4         MCPWM_TZSEL_OST4
//! One-shot TZ5
//!
#define MCPWM_TZ_SIGNAL_OSHT5         MCPWM_TZSEL_OST5
//! One-shot TZ6
//!
#define MCPWM_TZ_SIGNAL_OSHT6         MCPWM_TZSEL_OST6
//! One-shot TZ7
//!
#define MCPWM_TZ_SIGNAL_OSHT7         MCPWM_TZSEL_OST7
//! One-shot TZ8
//!
#define MCPWM_TZ_SIGNAL_OSHT8         MCPWM_TZSEL_OST8

//*****************************************************************************
//
//! Values that can be passed to MCPWM_setTripZoneAction() as the \e tzEvent
//! parameter.
//
//*****************************************************************************
typedef enum
{
    MCPWM_TZ_ACTION_EVENT_TZA = 0,     //!< TZ1 - TZ8
    MCPWM_TZ_ACTION_EVENT_TZB = 1     //!< TZ1 - TZ8
} MCPWM_TripZoneEvent;

//*****************************************************************************
//
//! Values that can be passed to MCPWM_setTripZoneAction() as the
//! \e tzAction parameter.
//
//*****************************************************************************
typedef enum
{
    MCPWM_TZ_ACTION_HIGH_Z  = 0, //!< High impedance output
    MCPWM_TZ_ACTION_HIGH    = 1, //!< High voltage state
    MCPWM_TZ_ACTION_LOW     = 2, //!< Low voltage state
    MCPWM_TZ_ACTION_DISABLE = 3  //!< Disable action
} MCPWM_TripZoneAction;

//*****************************************************************************
//
//! Values that can be passed to MCPWM_selectTripZoneCBCEvent() as
//! the \e clearMode parameter.
//
//*****************************************************************************
typedef enum
{
    //! Disable CBC pulse Clear
    MCPWM_TZ_CBC_PULSE_CLR_NONE = 0,
    //! Clear CBC pulse when counter equals zero
    MCPWM_TZ_CBC_PULSE_CLR_CNTR_ZERO = 1,
    //! Clear CBC pulse when counter equals period
    MCPWM_TZ_CBC_PULSE_CLR_CNTR_PERIOD = 2,
    //! Clear CBC pulse when counter equals zero or period
    MCPWM_TZ_CBC_PULSE_CLR_CNTR_ZERO_PERIOD = 3
} MCPWM_TripZoneCBCMode;

//*****************************************************************************
//
// Values that can be passed to MCPWM_clearTripZoneFlagStatus()
// as the tzCbcFlag parameter and returned by
// MCPWM_getTripZoneFlagStatus().
//
//*****************************************************************************
//! CBC flag 1
//!
#define MCPWM_TZ_FLAG_CBC_TZ1  MCPWM_TZCBCOSTFLAG_CBC1
//! CBC flag 2
//!
#define MCPWM_TZ_FLAG_CBC_TZ2  MCPWM_TZCBCOSTFLAG_CBC2
//! CBC flag 3
//!
#define MCPWM_TZ_FLAG_CBC_TZ3  MCPWM_TZCBCOSTFLAG_CBC3
//! CBC flag 4
//!
#define MCPWM_TZ_FLAG_CBC_TZ4  MCPWM_TZCBCOSTFLAG_CBC4
//! CBC flag 5
//!
#define MCPWM_TZ_FLAG_CBC_TZ5  MCPWM_TZCBCOSTFLAG_CBC5
//! CBC flag 6
//!
#define MCPWM_TZ_FLAG_CBC_TZ6  MCPWM_TZCBCOSTFLAG_CBC6
//! CBC flag 7
//!
#define MCPWM_TZ_FLAG_CBC_TZ7  MCPWM_TZCBCOSTFLAG_CBC7
//! CBC flag 8
//!
#define MCPWM_TZ_FLAG_CBC_TZ8  MCPWM_TZCBCOSTFLAG_CBC8
//! OST flag 1
//!
#define MCPWM_TZ_FLAG_OST_TZ1  MCPWM_TZCBCOSTFLAG_OST1
//! OST flag 2
//!
#define MCPWM_TZ_FLAG_OST_TZ2  MCPWM_TZCBCOSTFLAG_OST2
//! OST flag 3
//!
#define MCPWM_TZ_FLAG_OST_TZ3  MCPWM_TZCBCOSTFLAG_OST3
//! OST flag 4
//!
#define MCPWM_TZ_FLAG_OST_TZ4  MCPWM_TZCBCOSTFLAG_OST4
//! OST flag 5
//!
#define MCPWM_TZ_FLAG_OST_TZ5  MCPWM_TZCBCOSTFLAG_OST5
//! OST flag 6
//!
#define MCPWM_TZ_FLAG_OST_TZ6  MCPWM_TZCBCOSTFLAG_OST6
//! OST flag 7
//!
#define MCPWM_TZ_FLAG_OST_TZ7  MCPWM_TZCBCOSTFLAG_OST7
//! OST flag 8
//!
#define MCPWM_TZ_FLAG_OST_TZ8  MCPWM_TZCBCOSTFLAG_OST8
//! All Trip Zone Flags 
//!
#define MCPWM_TZ_FLAG_ALL   (MCPWM_TZ_FLAG_CBC_TZ1 |\
                            MCPWM_TZ_FLAG_CBC_TZ2 |\
                            MCPWM_TZ_FLAG_CBC_TZ3 |\
                            MCPWM_TZ_FLAG_CBC_TZ4 |\
                            MCPWM_TZ_FLAG_CBC_TZ5 |\
                            MCPWM_TZ_FLAG_CBC_TZ6 |\
                            MCPWM_TZ_FLAG_CBC_TZ7 |\
                            MCPWM_TZ_FLAG_CBC_TZ8 |\
                            MCPWM_TZ_FLAG_OST_TZ1 |\
                            MCPWM_TZ_FLAG_OST_TZ2 |\
                            MCPWM_TZ_FLAG_OST_TZ3 |\
                            MCPWM_TZ_FLAG_OST_TZ4 |\
                            MCPWM_TZ_FLAG_OST_TZ5 |\
                            MCPWM_TZ_FLAG_OST_TZ6 |\
                            MCPWM_TZ_FLAG_OST_TZ7 |\
                            MCPWM_TZ_FLAG_OST_TZ8)


//*****************************************************************************
//! Values that can be passed to MCPWM_enableADCTrigger(),
//! MCPWM_disableADCTrigger(),MCPWM_setADCTriggerSource(),
//! MCPWM_setADCTriggerEventPrescale(),MCPWM_getADCTriggerFlagStatus(),
//! MCPWM_clearADCTriggerFlag(),MCPWM_enableADCTriggerEventCountInit(),
//! MCPWM_disableADCTriggerEventCountInit(),MCPWM_forceADCTriggerEventCountInit(),
//! MCPWM_setADCTriggerEventCountInitValue(),MCPWM_getADCTriggerEventCount(),
//! MCPWM_forceADCTrigger() as the \e adcSOCType parameter
//
//*****************************************************************************
typedef enum
{
    MCPWM_SOC_A = 0,  //!< SOC A
    MCPWM_SOC_B = 1,   //!< SOC B
    MCPWM_SOC_C = 2,   //!< SOC C
    MCPWM_SOC_D = 3   //!< SOC D
} MCPWM_ADCStartOfConversionType;

//*****************************************************************************
//
//! Values that can be passed to MCPWM_setADCTriggerSource() as the
//! \e socSource parameter.
//
//*****************************************************************************
typedef enum
{
    //! Event is Disabled
    MCPWM_SOC_DISABLED = 0,

    //! Time-base counter equal to zero
    MCPWM_SOC_TBCTR_ZERO = 2,
    //! Time-base counter equal to period
    MCPWM_SOC_TBCTR_PERIOD = 3,
    //! Time-base counter equal to zero or period
    MCPWM_SOC_TBCTR_ZERO_PERIOD = 4,

    //! Time-base counter equal to CMPC when the timer is incrementing
    MCPWM_SOC_TBCTR_U_CMPC = 8,
    //! Time-base counter equal to CMPD when the timer is incrementing
    MCPWM_SOC_TBCTR_U_CMPD = 9,

    //! Time-base counter equal to CMP1A when the timer is incrementing
    MCPWM_SOC_TBCTR_U_CMP1A = 10,
    //! Time-base counter equal to CMP1B when the timer is incrementing
    MCPWM_SOC_TBCTR_U_CMP1B = 11,

    //! Time-base counter equal to CMP2A when the timer is incrementing
    MCPWM_SOC_TBCTR_U_CMP2A = 12,
    //! Time-base counter equal to CMP2B when the timer is incrementing
    MCPWM_SOC_TBCTR_U_CMP2B = 13,

    //! Time-base counter equal to CMP3A when the timer is incrementing
    MCPWM_SOC_TBCTR_U_CMP3A = 14,
    //! Time-base counter equal to CMP3B when the timer is incrementing
    MCPWM_SOC_TBCTR_U_CMP3B = 15,

    //! Time-base counter equal to CMPC when the timer is Decrementing
    MCPWM_SOC_TBCTR_D_CMPC = 16,
    //! Time-base counter equal to CMPD when the timer is Decrementing
    MCPWM_SOC_TBCTR_D_CMPD = 17,

    //! Time-base counter equal to CMP1A when the timer is Decrementing
    MCPWM_SOC_TBCTR_D_CMP1A = 18,
    //! Time-base counter equal to CMP1B when the timer is Decrementing
    MCPWM_SOC_TBCTR_D_CMP1B = 19,

    //! Time-base counter equal to CMP2A when the timer is Decrementing
    MCPWM_SOC_TBCTR_D_CMP2A = 20,
    //! Time-base counter equal to CMP2B when the timer is Decrementing
    MCPWM_SOC_TBCTR_D_CMP2B = 21,

    //! Time-base counter equal to CMP3A when the timer is Decrementing
    MCPWM_SOC_TBCTR_D_CMP3A = 22,
    //! Time-base counter equal to CMP3B when the timer is Decrementing
    MCPWM_SOC_TBCTR_D_CMP3B = 23
} MCPWM_ADCStartOfConversionSource;

//*****************************************************************************
//! Values that can be passed to MCPWM_enableADCTrigger(),
//! MCPWM_disableADCTrigger(),MCPWM_setADCTriggerSource(),
//! MCPWM_setADCTriggerEventPrescale(),MCPWM_getADCTriggerFlagStatus(),
//! MCPWM_clearADCTriggerFlag(),MCPWM_enableADCTriggerEventCountInit(),
//! MCPWM_disableADCTriggerEventCountInit(),MCPWM_forceADCTriggerEventCountInit(),
//! MCPWM_setADCTriggerEventCountInitValue(),MCPWM_getADCTriggerEventCount(),
//! MCPWM_forceADCTrigger() as the \e evtTrigType parameter
//
//*****************************************************************************
typedef enum
{
    MCPWM_ET_1 = 0,  //!< EVT 1
    MCPWM_ET_2 = 1   //!< EVT 2
} MCPWM_EventTriggerType;

//*****************************************************************************
//
//! Values that can be passed to MCPWM_setEventTriggerSource() as the
//! \e evtTrigSource parameter.
//
//*****************************************************************************
typedef enum
{
    //! Event is Disabled
    MCPWM_EVT_DISABLED = 0,

    //! Time-base counter equal to zero
    MCPWM_EVT_TBCTR_ZERO = 2,
    //! Time-base counter equal to period
    MCPWM_EVT_TBCTR_PERIOD = 3,
    //! Time-base counter equal to zero or period
    MCPWM_EVT_TBCTR_ZERO_PERIOD = 4,

    //! Time-base counter equal to CMPC when the timer is incrementing
    MCPWM_EVT_TBCTR_U_CMPC = 8,
    //! Time-base counter equal to CMPD when the timer is incrementing
    MCPWM_EVT_TBCTR_U_CMPD = 9,

    //! Time-base counter equal to CMP1A when the timer is incrementing
    MCPWM_EVT_TBCTR_U_CMP1A = 10,
    //! Time-base counter equal to CMP1B when the timer is incrementing
    MCPWM_EVT_TBCTR_U_CMP1B = 11,

    //! Time-base counter equal to CMP2A when the timer is incrementing
    MCPWM_EVT_TBCTR_U_CMP2A = 12,
    //! Time-base counter equal to CMP2B when the timer is incrementing
    MCPWM_EVT_TBCTR_U_CMP2B = 13,

    //! Time-base counter equal to CMP3A when the timer is incrementing
    MCPWM_EVT_TBCTR_U_CMP3A = 14,
    //! Time-base counter equal to CMP3B when the timer is incrementing
    MCPWM_EVT_TBCTR_U_CMP3B = 15,

    //! Time-base counter equal to CMPC when the timer is Decrementing
    MCPWM_EVT_TBCTR_D_CMPC = 16,
    //! Time-base counter equal to CMPD when the timer is Decrementing
    MCPWM_EVT_TBCTR_D_CMPD = 17,

    //! Time-base counter equal to CMP1A when the timer is Decrementing
    MCPWM_EVT_TBCTR_D_CMP1A = 18,
    //! Time-base counter equal to CMP1B when the timer is Decrementing
    MCPWM_EVT_TBCTR_D_CMP1B = 19,

    //! Time-base counter equal to CMP2A when the timer is Decrementing
    MCPWM_EVT_TBCTR_D_CMP2A = 20,
    //! Time-base counter equal to CMP2B when the timer is Decrementing
    MCPWM_EVT_TBCTR_D_CMP2B = 21,

    //! Time-base counter equal to CMP3A when the timer is Decrementing
    MCPWM_EVT_TBCTR_D_CMP3A = 22,
    //! Time-base counter equal to CMP3B when the timer is Decrementing
    MCPWM_EVT_TBCTR_D_CMP3B = 23
} MCPWM_EventTriggerSource;


//*****************************************************************************
//
// Values that can be passed to MCPWM_enableInterrupt() as the
// interruptSource parameter.
//
//*****************************************************************************
//! Interrupt Source is Trip Zone CBC signal
//!
#define MCPWM_INT_TZ_CBC            MCPWM_INTFLAG_CBC    
//! Interrupt Source is Trip Zone OST signal
//!
#define MCPWM_INT_TZ_OST            MCPWM_INTFLAG_OST    
//! Interrupt Source is Event Trigger 1 signal
//!
#define MCPWM_INT_ET_1              MCPWM_INTFLAG_ET1  
//! Interrupt Source is Event Trigger 2 signal
//!
#define MCPWM_INT_ET_2              MCPWM_INTFLAG_ET2  
//! Interrupt Source is Counter Overflow signal
//!
#define MCPWM_INT_TBCTR_OVF         MCPWM_INTFLAG_CNT_OVF 
//! All Interrupt Sources
//! 
#define MCPWM_INT_SOURCE_ALL   (MCPWM_INT_TZ_CBC   |\
                                MCPWM_INT_TZ_OST |\
                                MCPWM_INT_ET_1   |\
                                MCPWM_INT_ET_2   |\
                                MCPWM_INT_TBCTR_OVF)


//*****************************************************************************
//
//! Values that can be passed to MCPWM_configureSignal() as the
//! \e signalParams parameter.
//
//*****************************************************************************
typedef struct
{
    float32_t              freqInHz;    //!< Desired Signal Frequency(in Hz)
    float32_t              dutyVal1A;    //!< Desired MCPWMxA Signal Duty
    float32_t              dutyVal1B;    //!< Desired MCPWMxB Signal Duty
    float32_t              dutyVal2A;    //!< Desired MCPWMxA Signal Duty
    float32_t              dutyVal2B;    //!< Desired MCPWMxB Signal Duty
    float32_t              dutyVal3A;    //!< Desired MCPWMxA Signal Duty
    float32_t              dutyVal3B;    //!< Desired MCPWMxB Signal Duty
    bool                   invertSignal1B; //!< Invert MCPWMxB Signal if TRUE
    bool                   invertSignal2B; //!< Invert MCPWMxB Signal if TRUE
    bool                   invertSignal3B; //!< Invert MCPWMxB Signal if TRUE
    float32_t              sysClkInHz;  //!< SYSCLK Frequency(in Hz)
    MCPWM_TimeBaseCountMode tbCtrMode;   //!< Time Base Counter Mode
    MCPWM_ClockDivider      tbClkDiv;    //!< Time Base Counter Clock Divider
} MCPWM_SignalParams;
//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
//*****************************************************************************
//
//! \internal
//! Checks MCPWM base address.
//!
//! \param base specifies the MCPWM module base address.
//!
//! This function determines if an MCPWM module base address is valid.
//!
//! \return Returns \b TRUE if the base address is valid and \b FALSE
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool
MCPWM_isBaseValid(uint32_t base)
{
    return(
           (base == PWM1_BASE) ||
           (base == PWM3_BASE)
          );
}
#endif

//*****************************************************************************
//
//! Get the MCPWM Revision value
//!
//! \param base is the MCPWM module base address
//!
//! This function gets the MCPWM revision value.
//!
//! \return Returns the MCPWM revision value.
//
//*****************************************************************************
static inline uint16_t
MCPWM_getRevision(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(MCPWM_isBaseValid(base));

    //
    // Get the revision value.
    //
    return(HWREG(base + MCPWM_O_REVISION));
}

//*****************************************************************************
//
//! Sets the phase shift offset counter value.
//!
//! \param base is the base address of the MCPWM module.
//! \param phaseCount is the phase shift count value.
//!
//! This function sets the 16 bit time-base counter phase of the MCPWM relative
//! to the time-base that is supplying the synchronization input signal. Call
//! the MCPWM_enablePhaseShiftLoad() function to enable loading of the
//! phaseCount phase shift value when a sync event occurs.
//!
//! \return None.
//
//*****************************************************************************
static inline void
MCPWM_setPhaseShift(uint32_t base, uint16_t phaseCount)
{
    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));

    //
    // Write to TBPHS bit
    //
    HWREG(base + MCPWM_O_TBPHS) =
                   ((HWREG(base + MCPWM_O_TBPHS) &
                    ~((uint32_t)MCPWM_TBPHS_TBPHS_M)) |
                    ((uint32_t)phaseCount << MCPWM_TBPHS_TBPHS_S));
}

//
// Time Base Sub Module related APIs
//
//*****************************************************************************
//
//! Set the time base count
//!
//! \param base is the base address of the MCPWM module.
//! \param count is the time base count value.
//!
//! This function sets the 16 bit counter value of the time base counter.
//!
//! \return None.
//
//*****************************************************************************
static inline void
MCPWM_setTimeBaseCounter(uint32_t base, uint16_t count)
{
    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));

    //
    // Write to TBCTR register
    //
    HWREG(base + MCPWM_O_TBCTR) = count;
}


//*****************************************************************************
//
//! Returns time base counter value.
//!
//! \param base is the base address of the MCPWM module.
//!
//! This function returns the current value of the time base counter.
//!
//! \return returns time base counter value
//
//*****************************************************************************
static inline uint16_t
MCPWM_getTimeBaseCounterValue(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));

    //
    // Returns TBCTR value
    //
    return((uint16_t)HWREG(base + MCPWM_O_TBCTR));
}

//*****************************************************************************
//
//! Set time base counter mode
//!
//! \param base is the base address of the MCPWM module.
//! \param counterMode is the time base counter mode.
//!
//! This function sets up the time base counter mode.
//! Valid values for counterMode are:
//!  - MCPWM_COUNTER_MODE_UP          - Up - count mode.
//!  - MCPWM_COUNTER_MODE_UP_DOWN     - Up - down - count mode.
//!  - MCPWM_COUNTER_MODE_STOP_FREEZE - Stop - Freeze counter.
//!
//! \return None.
//
//*****************************************************************************
static inline void
MCPWM_setTimeBaseCounterMode(uint32_t base, MCPWM_TimeBaseCountMode counterMode)
{
    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));

    //
    // Write to CTRMODE bit
    //
    HWREG(base + MCPWM_O_TBCTL) =
            ((HWREG(base + MCPWM_O_TBCTL) & ~(MCPWM_TBCTL_CTRMODE_M)) |
             ((uint32_t)counterMode));
}

//*****************************************************************************
//
//! Return time base counter direction.
//!
//! \param base is the base address of the MCPWM module.
//!
//! This function returns the direction of the time base counter.
//!
//! \return returns MCPWM_TIME_BASE_STATUS_COUNT_UP if the counter is counting
//!                 up or MCPWM_TIME_BASE_STATUS_COUNT_DOWN if the counter is
//!                 counting down.
//
//*****************************************************************************
static inline uint32_t
MCPWM_getTimeBaseCounterDirection(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));

    //
    // Return CTRDIR bit
    //
    return(HWREG(base + MCPWM_O_TBSTS) & MCPWM_TBSTS_CTRDIR);
}

//*****************************************************************************
//
//! Set the time base clock and the high speed time base clock count pre-scaler
//!
//! \param base is the base address of the MCPWM module.
//! \param prescaler is the time base count pre scale value.
//!
//! This function sets the pre scaler(divider)value for the time base clock
//! counter and the high speed time base clock counter.
//! Valid values for pre-scaler and highSpeedPrescaler are MCPWM_CLOCK_DIVIDER_X,
//! where X is 1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384 or 32768
//! The actual numerical values for these macros represent values 0,1...15.
//! The equation for the output clock is:
//!   TBCLK = MCPWMCLK/(pre-scaler)
//!
//! \b Note: MCPWMCLK is a scaled version of SYSCLK.
//!
//! \return None.
//
//*****************************************************************************
static inline void
MCPWM_setClockPrescaler(uint32_t base, MCPWM_ClockDivider prescaler)
{
    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));

    //
    // Write to CLKDIV bit
    //
    HWREG(base + MCPWM_O_TBCTL) =
                ((HWREG(base + MCPWM_O_TBCTL)  &
                ~MCPWM_TBCTL_CLKDIV_M) |
                ((uint16_t)prescaler << MCPWM_TBCTL_CLKDIV_S));
}

//*****************************************************************************
//
//! Set PWM period load mode.
//!
//! \param base is the base address of the MCPWM module.
//! \param loadMode is the PWM period load mode.
//!
//! This function sets the load mode for the PWM period. If loadMode is set to
//! MCPWM_PERIOD_SHADOW_LOAD_ENABLE, Shadow register will be loaded to Active
//! register at TBCTR=0. 
//! If loadMode is set to MCPWM_PERIOD_SHADOW_LOAD_DISABLE, load from Shadow
//! register mode  disabled.
//!
//! \return None.
//
//*****************************************************************************
static inline void
MCPWM_setPeriodLoadMode(uint32_t base, MCPWM_PeriodLoadMode loadMode)
{
    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));

    if(loadMode == MCPWM_PERIOD_SHADOW_LOAD_ENABLE)
    {
        //
        // Clear PRDLD
        //
        HWREG(base + MCPWM_O_TBCTL) &= ~MCPWM_TBCTL_PRDLD;
    }
    else
    {
        //
        // Set PRDLD
        //
        HWREG(base + MCPWM_O_TBCTL) |= MCPWM_TBCTL_PRDLD;
    }
}

//*****************************************************************************
//
//! Enable phase shift load
//!
//! \param base is the base address of the MCPWM module.
//!
//! This function enables loading of phase shift when the appropriate sync
//! event occurs.
//!
//! \return None.
//
//*****************************************************************************
static inline void
MCPWM_enablePhaseShiftLoad(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));

    //
    // Set PHSEN bit
    //
    HWREG(base + MCPWM_O_TBCTL) |= MCPWM_TBCTL_PHSEN;
}

//*****************************************************************************
//
//! Disable phase shift load
//!
//! \param base is the base address of the MCPWM module.
//!
//! This function disables loading of phase shift when the appropriate sync
//! event occurs.
//!
//! \return None.
//
//*****************************************************************************
static inline void
MCPWM_disablePhaseShiftLoad(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));

    //
    // Clear PHSEN bit
    //
    HWREG(base + MCPWM_O_TBCTL) &= ~((uint32_t)MCPWM_TBCTL_PHSEN);
}

//*****************************************************************************
//
//! Set count mode after phase shift sync
//!
//! \param base is the base address of the MCPWM module.
//! \param mode is the count mode.
//!
//! This function sets the time base count to count up or down after a new
//! phase value set by the MCPWM_setPhaseShift(). The count direction is
//! determined by the variable mode. Valid inputs for mode are:
//!  - MCPWM_COUNT_MODE_UP_AFTER_SYNC      - Count up after sync
//!  - MCPWM_COUNT_MODE_DOWN_AFTER_SYNC    - Count down after sync
//!
//! \return None.
//
//*****************************************************************************
static inline void
MCPWM_setCountModeAfterSync(uint32_t base, MCPWM_SyncCountMode mode)
{
    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));

    if(mode == MCPWM_COUNT_MODE_UP_AFTER_SYNC)
    {
        //
        // Set PHSDIR bit
        //
        HWREG(base + MCPWM_O_TBCTL) |= MCPWM_TBCTL_PHSDIR;
    }
    else
    {
        //
        // Clear PHSDIR bit
        //
        HWREG(base + MCPWM_O_TBCTL) &= ~MCPWM_TBCTL_PHSDIR;
    }
}

//*****************************************************************************
//
//! Force a software sync pulse
//!
//! \param base is the base address of the MCPWM module.
//!
//! This function causes a single software initiated sync pulse.
//!
//! \return None.
//
//*****************************************************************************
static inline void
MCPWM_forceSyncPulse(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));

    //
    // Set SWFSYNC bit
    //
    HWREG(base + MCPWM_O_TBCTL) |= MCPWM_TBCTL_SWSYNC;
}

//*****************************************************************************
//
//! Set up the sync out pulse event
//!
//! \param base is the base address of the MCPWM module.
//! \param mode is the sync out mode.
//!
//! This function set the sync out pulse mode.
//! Valid values for mode are:
//!  - MCPWM_SYNC_OUT_PULSE_ON_SOFTWARE   - sync pulse is generated by software
//!                                        when MCPWM_forceSyncPulse()
//!                                        function is called or by MCPWMxSYNCI
//!                                        signal.
//!  - MCPWM_SYNC_OUT_PULSE_ON_COUNTER_ZERO - sync pulse is generated when
//!                                          time base counter equals zero.
//!  - MCPWM_SYNC_OUT_PULSE_ON_COUNTER_COMPARE_C - sync pulse is generated when
//!                                           time base counter equals compare
//!                                           C value.
//!  - MCPWM_SYNC_OUT_PULSE_ON_COUNTER_COMPARE_D - sync pulse is generated when
//!                                           time base counter equals compare
//!                                           D value.
//!  - MCPWM_SYNC_OUT_PULSE_DISABLED          - sync pulse is disabled.
//!
//! \return None.
//
//*****************************************************************************
static inline void
MCPWM_setSyncOutPulseMode(uint32_t base, MCPWM_SyncOutPulseMode mode)
{
    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));

    //
    // No extended mode support
    //
    if(mode < MCPWM_SYNC_OUT_PULSE_DISABLED)
    {
        //
        // Write to SYNCOSEL bits
        //
        HWREG(base + MCPWM_O_TBCTL) =
                ((HWREG(base + MCPWM_O_TBCTL) & ~(MCPWM_TBCTL_SYNCOSEL_M)) |
                 ((uint32_t)mode << MCPWM_TBCTL_SYNCOSEL_S));
    }
}

//*****************************************************************************
//
//! Set SYNCPER source. (also known as PWMSYNC in earlier versions)
//!
//! \param base is the base address of the MCPWM module.
//! \param syncPulseSource is the SYNCPERSEL source.
//!
//! This function sets the SYNCPERSEL pulse source.
//! Valid values for syncPulseSource are:
//!  -  MCPWM_SYNCPERSEL_SOURCE_PERIOD      - Counter equals Period.
//!  -  MCPWM_SYNCPERSEL_SOURCE_ZERO        - Counter equals zero.
//!  -  MCPWM_SYNCPERSEL_SOURCE_CMPC_UP    - Counter equals CMPC when
//!                                       counting up.
//!  -  MCPWM_SYNCPERSEL_SOURCE_CMPC_DOWN  - Counter equals CMPC when
//!                                       counting down.
//!  -  MCPWM_SYNCPERSEL_SOURCE_CMPD_UP    - Counter equals CMPD when
//!                                       counting up.
//!  -  MCPWM_SYNCPERSEL_SOURCE_CMPD_DOWN  - Counter equals CMPD when
//!                                       counting down.
//!
//! \return None.
//
//*****************************************************************************
static inline void
MCPWM_setSyncPulseSource(uint32_t base, MCPWM_SyncPulseSource syncPulseSource)
{
    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));

    //
    // Set the SYNCPERSEL source
    //
    HWREG(base + MCPWM_O_TBCTL) =
                ((HWREG(base + MCPWM_O_TBCTL) & ~(MCPWM_TBCTL_SYNCPERSEL_M)) |
                 ((uint32_t)syncPulseSource << MCPWM_TBCTL_SYNCPERSEL_S));

}

//*****************************************************************************
//
//! Set up the source for sync-in pulse.
//!
//! \param base is the base address of the MCPWM module.
//! \param source is the sync-in pulse source.
//!
//! This function set the sync out pulse mode.
//! Valid values for mode are:
//!    MCPWM_SYNC_IN_PULSE_SRC_DISABLE    -    Disable Sync-in
//!    MCPWM_SYNC_IN_PULSE_SRC_INPUTXBAR_OUT5    -    Sync-in source is Input XBAR out5 signal
//!    MCPWM_SYNC_IN_PULSE_SRC_INPUTXBAR_OUT6    -    Sync-in source is Input XBAR out6 signal
//!    MCPWM_SYNC_IN_PULSE_SRC_SYNCOUT_ECAP1    -    Sync-in source is ECAP1 sync-out signal
//!    MCPWM_SYNC_IN_PULSE_SRC_SYNCOUT_MCPWM1    -    Sync-in source is MCPWM1 sync-out signal
//!    MCPWM_SYNC_IN_PULSE_SRC_SYNCOUT_MCPWM3    -    Sync-in source is MCPWM3 sync-out signal
//!
//! \return None.
//
//*****************************************************************************
static inline void
MCPWM_setSyncInPulseSource(uint32_t base, MCPWM_SyncInPulseSource source)
{
    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));

    //
    // Set MCPWM Sync-In Source Mode.
    //
    HWREG(base + MCPWM_O_TBCTL) =
            (HWREG(base + MCPWM_O_TBCTL) & (~MCPWM_TBCTL_SYNCISEL_M)) |
            (((uint32_t)source << MCPWM_TBCTL_SYNCISEL_S));
}

//*****************************************************************************
//
//! Return external sync signal status.
//!
//! \param base is the base address of the MCPWM module.
//!
//! This function returns the external sync signal status.
//!
//! \return Returns TRUE if if an external sync signal event
//!         Returns FALSE if there is no event.
//
//*****************************************************************************
static inline bool
MCPWM_getSyncStatus(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));

    //
    // Return TRUE if SYNCI bit is set, FALSE otherwise
    //
    return(((HWREG(base + MCPWM_O_TBSTS) & MCPWM_TBSTS_SYNCI) ==
            MCPWM_TBSTS_SYNCI) ? TRUE : FALSE);
}

//*****************************************************************************
//
//! Clear external sync signal event.
//!
//! \param base is the base address of the MCPWM module.
//!
//! This function clears the external sync signal latch event.
//!
//! \return None.
//
//*****************************************************************************
static inline void
MCPWM_clearSyncStatus(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));

    //
    // Set SYNCI bit
    //
    HWREGH(base + MCPWM_O_TBSTSCLR) = MCPWM_TBSTS_SYNCI;
}

//*****************************************************************************
//
//! Sets the PWM period count in its Active Register.
//!
//! \param base is the base address of the MCPWM module.
//! \param periodCount is period count value.
//!
//! This function sets the period of the PWM count in its Active period register. 
//! The value of periodCount is the value written to the register. User should 
//! map the desired period or frequency of the waveform into the correct
//! periodCount. 
//! Invoke the function MCPWM_setPeriodLoadMode() with the appropriate
//! parameter to set the load mode of the Period count. periodCount has a
//! maximum valid value of 0xFFFF
//!
//! \return None.
//
//*****************************************************************************
static inline void
MCPWM_setTimeBasePeriodActive(uint32_t base, uint16_t periodCount)
{
    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));

    //
    // Write to TBPRD bit
    //
    HWREG(base + MCPWM_O_TBPRD) = periodCount;
}

//*****************************************************************************
//
//! Sets the PWM period count in shadow register.
//!
//! \param base is the base address of the MCPWM module.
//! \param periodCount is period count value.
//!
//! This function sets the period of the PWM count in its Shadow period register. 
//! The value of periodCount is the value written to the register. User should 
//! map the desired period or frequency of the waveform into the correct
//! periodCount. 
//! Invoke the function MCPWM_setPeriodLoadMode() with the appropriate
//! parameter to set the load mode of the Period count. periodCount has a
//! maximum valid value of 0xFFFF
//!
//! \return None.
//
//*****************************************************************************
static inline void
MCPWM_setTimeBasePeriodShadow(uint32_t base, uint16_t periodCount)
{
    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));

    //
    // Write to TBPRD bit
    //
    HWREG(base + MCPWM_O_TBPRDS) = periodCount;
}

//*****************************************************************************
//
//! Gets the PWM period count.
//!
//! \param base is the base address of the MCPWM module.
//!
//! This function gets the period of the PWM count in its active register.
//!
//! \return The period count value.
//
//*****************************************************************************
static inline uint16_t
MCPWM_getTimeBasePeriodActive(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));

    //
    // Read from TBPRD bit
    //
    return( (uint16_t) HWREG(base + MCPWM_O_TBPRD) & MCPWM_TBPRD_TBPRD_M);
}

//*****************************************************************************
//
//! Gets the PWM period count.
//!
//! \param base is the base address of the MCPWM module.
//!
//! This function gets the period of the PWM count in its shadow register.
//!
//! \return The period count value.
//
//*****************************************************************************
static inline uint16_t
MCPWM_getTimeBasePeriodShadow(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));

    //
    // Read from TBPRD bit
    //
    return( (uint16_t) HWREG(base + MCPWM_O_TBPRDS) & MCPWM_TBPRDS_TBPRDS_M);
}

//*****************************************************************************
//
//! Set counter compare values.
//!
//! \param base is the base address of the MCPWM module.
//! \param compModule is the Counter Compare value module.
//! \param compCount is the counter compare count value.
//!
//! This function sets the active counter compare value for counter compare 
//! registers.
//! The maximum value for compCount is 0xFFFF.
//! Valid values for compModule are:
//!   MCPWM_COUNTER_COMPARE_1A      Counter compare 1A
//!   MCPWM_COUNTER_COMPARE_1B      Counter compare 1B
//!   MCPWM_COUNTER_COMPARE_2A      Counter compare 2A
//!   MCPWM_COUNTER_COMPARE_2B      Counter compare 2B
//!   MCPWM_COUNTER_COMPARE_3A      Counter compare 3A
//!   MCPWM_COUNTER_COMPARE_3B      Counter compare 3B
//!   MCPWM_COUNTER_COMPARE_C       Counter compare C
//!   MCPWM_COUNTER_COMPARE_D       Counter compare D
//!   
//! \return None.
//
//*****************************************************************************
static inline void
MCPWM_setCounterCompareActiveValue(uint32_t base, MCPWM_CounterCompareModule compModule,
                            uint16_t compCount)
{
    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));

    //
    // Write to the counter compare registers.
    //
    switch (compModule)
    {
    case MCPWM_COUNTER_COMPARE_1A:
        HWREGH(base + MCPWM_O_PWM1_CMPA) = compCount; 
        break;
    case MCPWM_COUNTER_COMPARE_1B:
        HWREGH(base + MCPWM_O_PWM1_CMPB) = compCount; 
        break;
    case MCPWM_COUNTER_COMPARE_2A:
        HWREGH(base + MCPWM_O_PWM2_CMPA) = compCount; 
        break;
    case MCPWM_COUNTER_COMPARE_2B:
        HWREGH(base + MCPWM_O_PWM2_CMPB) = compCount; 
        break;
    case MCPWM_COUNTER_COMPARE_3A:
        HWREGH(base + MCPWM_O_PWM3_CMPA) = compCount; 
        break;
    case MCPWM_COUNTER_COMPARE_3B:
        HWREGH(base + MCPWM_O_PWM3_CMPB) = compCount; 
        break;
    case MCPWM_COUNTER_COMPARE_C:
        HWREGH(base + MCPWM_O_CMPC) = compCount; 
        break;
    default:
        HWREGH(base + MCPWM_O_CMPD) = compCount; 
        break;    
    }
}

//*****************************************************************************
//
//! Get counter compare values.
//!
//! \param base is the base address of the MCPWM module.
//! \param compModule is the Counter Compare value module.
//! \param compCount is the counter compare count value.
//!
//! This function gets the value for active counter compare registers.
//! Valid values for compModule are:
//!   MCPWM_COUNTER_COMPARE_1A      Counter compare 1A
//!   MCPWM_COUNTER_COMPARE_1B      Counter compare 1B
//!   MCPWM_COUNTER_COMPARE_2A      Counter compare 2A
//!   MCPWM_COUNTER_COMPARE_2B      Counter compare 2B
//!   MCPWM_COUNTER_COMPARE_3A      Counter compare 3A
//!   MCPWM_COUNTER_COMPARE_3B      Counter compare 3B
//!   MCPWM_COUNTER_COMPARE_C       Counter compare C
//!   MCPWM_COUNTER_COMPARE_D       Counter compare D
//!   
//! \return The counter compare count value.
//
//*****************************************************************************
static inline uint16_t
MCPWM_getCounterCompareActiveValue(uint32_t base, 
                        MCPWM_CounterCompareModule compModule)
{
    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));

    uint16_t retValue = 0;

    //
    // Write to the counter compare registers.
    //
    switch (compModule)
    {
    case MCPWM_COUNTER_COMPARE_1A:
        retValue = (HWREGH(base + MCPWM_O_PWM1_CMPA)); 
        break;
    case MCPWM_COUNTER_COMPARE_1B:
        retValue = (HWREGH(base + MCPWM_O_PWM1_CMPB)); 
        break;
    case MCPWM_COUNTER_COMPARE_2A:
        retValue = (HWREGH(base + MCPWM_O_PWM2_CMPA)); 
        break;
    case MCPWM_COUNTER_COMPARE_2B:
        retValue = (HWREGH(base + MCPWM_O_PWM2_CMPB)); 
        break;
    case MCPWM_COUNTER_COMPARE_3A:
        retValue = (HWREGH(base + MCPWM_O_PWM3_CMPA)); 
        break;
    case MCPWM_COUNTER_COMPARE_3B:
        retValue = (HWREGH(base + MCPWM_O_PWM3_CMPB)); 
        break;
    case MCPWM_COUNTER_COMPARE_C:
        retValue = (HWREGH(base + MCPWM_O_CMPC)); 
        break;
    default:
        retValue = (HWREGH(base + MCPWM_O_CMPD)); 
        break;
    }
        return retValue;
}


//*****************************************************************************
//
//! Set counter compare values.
//!
//! \param base is the base address of the MCPWM module.
//! \param compModule is the Counter Compare value module.
//! \param compCount is the counter compare count value.
//!
//! This function sets the shadow counter compare value for counter compare 
//! registers.
//! The maximum value for compCount is 0xFFFF.
//! Valid values for compModule are:
//!   MCPWM_COUNTER_COMPARE_1A      Counter compare 1A
//!   MCPWM_COUNTER_COMPARE_1B      Counter compare 1B
//!   MCPWM_COUNTER_COMPARE_2A      Counter compare 2A
//!   MCPWM_COUNTER_COMPARE_2B      Counter compare 2B
//!   MCPWM_COUNTER_COMPARE_3A      Counter compare 3A
//!   MCPWM_COUNTER_COMPARE_3B      Counter compare 3B
//!   MCPWM_COUNTER_COMPARE_C       Counter compare C
//!   MCPWM_COUNTER_COMPARE_D       Counter compare D
//!   
//! \return None.
//
//*****************************************************************************
static inline void
MCPWM_setCounterCompareShadowValue(uint32_t base, 
                            MCPWM_CounterCompareModule compModule,
                            uint16_t compCount)
{
    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));

    //
    // Write to the counter compare registers.
    //
    switch (compModule)
    {
    case MCPWM_COUNTER_COMPARE_1A:
        HWREGH(base + MCPWM_O_PWM1_CMPAS) = compCount; 
        break;
    case MCPWM_COUNTER_COMPARE_1B:
        HWREGH(base + MCPWM_O_PWM1_CMPBS) = compCount; 
        break;
    case MCPWM_COUNTER_COMPARE_2A:
        HWREGH(base + MCPWM_O_PWM2_CMPAS) = compCount; 
        break;
    case MCPWM_COUNTER_COMPARE_2B:
        HWREGH(base + MCPWM_O_PWM2_CMPBS) = compCount; 
        break;
    case MCPWM_COUNTER_COMPARE_3A:
        HWREGH(base + MCPWM_O_PWM3_CMPAS) = compCount; 
        break;
    case MCPWM_COUNTER_COMPARE_3B:
        HWREGH(base + MCPWM_O_PWM3_CMPBS) = compCount; 
        break;
    case MCPWM_COUNTER_COMPARE_C:
        HWREGH(base + MCPWM_O_CMPCS) = compCount; 
        break;
    default:
        HWREGH(base + MCPWM_O_CMPDS) = compCount; 
        break;    
    }
}

//*****************************************************************************
//
//! Get counter compare values.
//!
//! \param base is the base address of the MCPWM module.
//! \param compModule is the Counter Compare value module.
//! \param compCount is the counter compare count value.
//!
//! This function gets the value for shadow counter compare registers.
//! Valid values for compModule are:
//!   MCPWM_COUNTER_COMPARE_1A      Counter compare 1A
//!   MCPWM_COUNTER_COMPARE_1B      Counter compare 1B
//!   MCPWM_COUNTER_COMPARE_2A      Counter compare 2A
//!   MCPWM_COUNTER_COMPARE_2B      Counter compare 2B
//!   MCPWM_COUNTER_COMPARE_3A      Counter compare 3A
//!   MCPWM_COUNTER_COMPARE_3B      Counter compare 3B
//!   MCPWM_COUNTER_COMPARE_C       Counter compare C
//!   MCPWM_COUNTER_COMPARE_D       Counter compare D
//!   
//! \return The counter compare count value.
//
//*****************************************************************************
static inline uint16_t
MCPWM_getCounterCompareShadowValue(uint32_t base,
                            MCPWM_CounterCompareModule compModule)
{
    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));
    uint16_t retValue =0;
    //
    // Write to the counter compare registers.
    //
    switch (compModule)
    {
    case MCPWM_COUNTER_COMPARE_1A:
        retValue =  (HWREGH(base + MCPWM_O_PWM1_CMPAS)); 
        break;
    case MCPWM_COUNTER_COMPARE_1B:
        retValue =  (HWREGH(base + MCPWM_O_PWM1_CMPBS)); 
        break;
    case MCPWM_COUNTER_COMPARE_2A:
        retValue =  (HWREGH(base + MCPWM_O_PWM2_CMPAS)); 
        break;
    case MCPWM_COUNTER_COMPARE_2B:
        retValue =  (HWREGH(base + MCPWM_O_PWM2_CMPBS)); 
        break;
    case MCPWM_COUNTER_COMPARE_3A:
        retValue =  (HWREGH(base + MCPWM_O_PWM3_CMPAS)); 
        break;
    case MCPWM_COUNTER_COMPARE_3B:
        retValue =  (HWREGH(base + MCPWM_O_PWM3_CMPBS)); 
        break;
    case MCPWM_COUNTER_COMPARE_C:
        retValue =  (HWREGH(base + MCPWM_O_CMPCS)); 
        break;
    default:
        retValue =  (HWREGH(base + MCPWM_O_CMPDS)); 
        break;    
    }

    return retValue;
}

//*****************************************************************************
//
//! Sets up the Counter Compare shadow load mode
//!
//! \param base is the base address of the MCPWM module.
//! \param compModule is the counter compare module.
//! \param loadMode is the shadow to active load mode.
//!
//! This function enables and sets up the counter compare shadow load mode.
//! Valid values for the variables are:
//!  - compModule
//!        MCPWM_COUNTER_COMPARE_1A      Counter compare 1A
//!        MCPWM_COUNTER_COMPARE_1B      Counter compare 1B
//!        MCPWM_COUNTER_COMPARE_2A      Counter compare 2A
//!        MCPWM_COUNTER_COMPARE_2B      Counter compare 2B
//!        MCPWM_COUNTER_COMPARE_3A      Counter compare 3A
//!        MCPWM_COUNTER_COMPARE_3B      Counter compare 3B
//!        MCPWM_COUNTER_COMPARE_C       Counter compare C
//!        MCPWM_COUNTER_COMPARE_D       Counter compare D
//!  - loadMode
//!        MCPWM_COMP_LOAD_ON_CNTR_ZERO - load when counter equals zero
//!        MCPWM_COMP_LOAD_ON_CNTR_PERIOD - load when counter equals period
//!        MCPWM_COMP_LOAD_ON_CNTR_ZERO_PERIOD - load when counter equals zero or period
//!        MCPWM_COMP_LOAD_FREEZE - freeze/disable Shadow to active load
//!
//! \return None.
//
//*****************************************************************************
static inline void
MCPWM_setCounterCompareShadowLoadMode(uint32_t base,
                                     MCPWM_CounterCompareModule compModule,
                                     MCPWM_CounterCompareLoadMode loadMode)
{

    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));

    //
    // Set the Shadow Load Mode 
    //
    switch (compModule)
    {
    case MCPWM_COUNTER_COMPARE_1A:
        HWREG(base + MCPWM_O_CMPCTL) = ((HWREG(base + MCPWM_O_CMPCTL) & 
                                        ~MCPWM_CMPCTL_PWM1_LOADAMODE_M) |   // clear the current configurations
                                        ((uint32_t)loadMode << MCPWM_CMPCTL_PWM1_LOADAMODE_S)); // update the configuration
        break;
    case MCPWM_COUNTER_COMPARE_1B:
        HWREG(base + MCPWM_O_CMPCTL) = ((HWREG(base + MCPWM_O_CMPCTL) & 
                                        ~MCPWM_CMPCTL_PWM1_LOADBMODE_M) |   // clear the current configurations
                                        ((uint32_t)loadMode << MCPWM_CMPCTL_PWM1_LOADBMODE_S)); // update the configuration
        break;
    case MCPWM_COUNTER_COMPARE_2A:
        HWREG(base + MCPWM_O_CMPCTL) = ((HWREG(base + MCPWM_O_CMPCTL) & 
                                        ~MCPWM_CMPCTL_PWM2_LOADAMODE_M) |   // clear the current configurations
                                        ((uint32_t)loadMode << MCPWM_CMPCTL_PWM2_LOADAMODE_S)); // update the configuration
        break;
    case MCPWM_COUNTER_COMPARE_2B:
        HWREG(base + MCPWM_O_CMPCTL) = ((HWREG(base + MCPWM_O_CMPCTL) & 
                                        ~MCPWM_CMPCTL_PWM2_LOADBMODE_M) |   // clear the current configurations
                                        ((uint32_t)loadMode << MCPWM_CMPCTL_PWM2_LOADBMODE_S)); // update the configuration
        break;
    case MCPWM_COUNTER_COMPARE_3A:
        HWREG(base + MCPWM_O_CMPCTL) = ((HWREG(base + MCPWM_O_CMPCTL) & 
                                        ~MCPWM_CMPCTL_PWM3_LOADAMODE_M) |   // clear the current configurations
                                        ((uint32_t)loadMode << MCPWM_CMPCTL_PWM3_LOADAMODE_S)); // update the configuration
        break;
    case MCPWM_COUNTER_COMPARE_3B:
        HWREG(base + MCPWM_O_CMPCTL) = ((HWREG(base + MCPWM_O_CMPCTL) & 
                                        ~MCPWM_CMPCTL_PWM3_LOADBMODE_M) |   // clear the current configurations
                                        ((uint32_t)loadMode << MCPWM_CMPCTL_PWM3_LOADBMODE_S)); // update the configuration
        break;
    case MCPWM_COUNTER_COMPARE_C:
        HWREG(base + MCPWM_O_CMPCTL) = ((HWREG(base + MCPWM_O_CMPCTL) & 
                                        ~MCPWM_CMPCTL_LOADCMODE_M) |    // clear the current configurations
                                        ((uint32_t)loadMode << MCPWM_CMPCTL_LOADCMODE_S)); // update the configuration
        break;
    default:
        HWREG(base + MCPWM_O_CMPCTL) = ((HWREG(base + MCPWM_O_CMPCTL) & 
                                        ~MCPWM_CMPCTL_LOADDMODE_M) |    // clear the current configurations
                                        ((uint32_t)loadMode << MCPWM_CMPCTL_LOADDMODE_S)); // update the configuration
        break;    
    }
}

//*****************************************************************************
//
//! Set up one time software forced Action qualifier outputs
//!
//! \param base is the base address of the MCPWM module.
//! \param MCpwmOutput is the MCPWM pin type.
//! \param output is the Action Qualifier output.
//!
//! This function sets up the one time software forced Action Qualifier output
//! on MCPWM A or MCPWMB, depending on the value of mcpwmOutput to a value
//! specified by outPut.
//! The following are valid values for the parameters.
//!   - mcpwmOutput
//!       - MCPWM_AQ_OUTPUT_1A - MCPWMx1A output
//!       - MCPWM_AQ_OUTPUT_1B - MCPWMx1B output
//!       - MCPWM_AQ_OUTPUT_2A - MCPWMx2A output
//!       - MCPWM_AQ_OUTPUT_2B - MCPWMx2B output
//!       - MCPWM_AQ_OUTPUT_3A - MCPWMx3A output
//!       - MCPWM_AQ_OUTPUT_3B - MCPWMx3B output
//!   - output
//!       - MCPWM_AQ_SW_FORCE_DISABLED  - SW force Action is disabled
//!       - MCPWM_AQ_SW_CONTINUOUS_LOW  - Set output pins to continuos low
//!       - MCPWM_AQ_SW_CONTINUOUS_HIGH - Set output pins to continuos High
//!       - MCPWM_AQ_SW_ONE_SHOT_LOW    - Set output to low when one shot is triggered
//!       - MCPWM_AQ_SW_ONE_SHOT_HIGH   - Set output to high when one shot is triggered
//!       - MCPWM_AQ_SW_ONE_SHOT_TOGGLE - Toggle output when one shot is triggered
//!
//! \return None.
//
//*****************************************************************************
static inline void
MCPWM_setActionQualifierSWAction(uint32_t base,
                                MCPWM_ActionQualifierOutputModule mcpwmOutput,
                                MCPWM_ActionQualifierSWForceOutput output)
{
    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));

    switch (mcpwmOutput)
    {
    case MCPWM_AQ_OUTPUT_1A :
        HWREG(base + MCPWM_O_PWM1_AQSFRC) = ((HWREG(base + MCPWM_O_PWM1_AQSFRC) & 
                                ~MCPWM_PWM1_AQSFRC_PWMA_M) | 
                                ((uint32_t)output << MCPWM_PWM1_AQSFRC_PWMA_S));
        break;
    case MCPWM_AQ_OUTPUT_1B :
        HWREG(base + MCPWM_O_PWM1_AQSFRC) = ((HWREG(base + MCPWM_O_PWM1_AQSFRC) & 
                                ~MCPWM_PWM1_AQSFRC_PWMB_M) | 
                                ((uint32_t)output << MCPWM_PWM1_AQSFRC_PWMB_S));
        break;
    case MCPWM_AQ_OUTPUT_2A :
        HWREG(base + MCPWM_O_PWM2_AQSFRC) = ((HWREG(base + MCPWM_O_PWM2_AQSFRC) & 
                                ~MCPWM_PWM2_AQSFRC_PWMA_M) | 
                                ((uint32_t)output << MCPWM_PWM2_AQSFRC_PWMA_S));
        break;
    case MCPWM_AQ_OUTPUT_2B :
        HWREG(base + MCPWM_O_PWM2_AQSFRC) = ((HWREG(base + MCPWM_O_PWM2_AQSFRC) & 
                                ~MCPWM_PWM2_AQSFRC_PWMB_M) | 
                                ((uint32_t)output << MCPWM_PWM2_AQSFRC_PWMB_S));
        break;
    case MCPWM_AQ_OUTPUT_3A :
        HWREG(base + MCPWM_O_PWM3_AQSFRC) = ((HWREG(base + MCPWM_O_PWM3_AQSFRC) & 
                                ~MCPWM_PWM3_AQSFRC_PWMA_M) | 
                                ((uint32_t)output << MCPWM_PWM3_AQSFRC_PWMA_S));
        break;
    default : // MCPWM_AQ_OUTPUT_3B
        HWREG(base + MCPWM_O_PWM3_AQSFRC) = ((HWREG(base + MCPWM_O_PWM3_AQSFRC) & 
                                ~MCPWM_PWM3_AQSFRC_PWMB_M) | 
                                ((uint32_t)output << MCPWM_PWM3_AQSFRC_PWMB_S));
        break;
    }
}

//*****************************************************************************
//
//! Triggers a one time software forced event on Action qualifier
//!
//! \param base is the base address of the MCPWM module.
//! \param mcpwmOutput is the MCPWM pin type.
//!
//! This function triggers a one time software forced Action Qualifier event
//! on MCPWM A or B based on the value of mcpwmOutput.
//! Valid values for mcpwmOutput are:
//!       - MCPWM_AQ_OUTPUT_1A - MCPWMx1A output
//!       - MCPWM_AQ_OUTPUT_1B - MCPWMx1B output
//!       - MCPWM_AQ_OUTPUT_2A - MCPWMx2A output
//!       - MCPWM_AQ_OUTPUT_2B - MCPWMx2B output
//!       - MCPWM_AQ_OUTPUT_3A - MCPWMx3A output
//!       - MCPWM_AQ_OUTPUT_3B - MCPWMx3B output
//!
//! \return None.
//
//*****************************************************************************
static inline void
MCPWM_forceActionQualifierSWAction(uint32_t base,
                                  MCPWM_ActionQualifierOutputModule mcpwmOutput)
{
    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));

    //
    // Initiate a software forced event
    //
    switch (mcpwmOutput)
    {
    case MCPWM_AQ_OUTPUT_1A :
        HWREG(base + MCPWM_O_PWM1_AQOTSFRC) = MCPWM_PWM1_AQOTSFRC_PWMA;
        break;
    case MCPWM_AQ_OUTPUT_1B :
        HWREG(base + MCPWM_O_PWM1_AQOTSFRC) = MCPWM_PWM1_AQOTSFRC_PWMB;
        break;
    case MCPWM_AQ_OUTPUT_2A :
        HWREG(base + MCPWM_O_PWM2_AQOTSFRC) = MCPWM_PWM2_AQOTSFRC_PWMA;
        break;
    case MCPWM_AQ_OUTPUT_2B :
        HWREG(base + MCPWM_O_PWM2_AQOTSFRC) = MCPWM_PWM2_AQOTSFRC_PWMB;
        break;
    case MCPWM_AQ_OUTPUT_3A :
        HWREG(base + MCPWM_O_PWM3_AQOTSFRC) = MCPWM_PWM3_AQOTSFRC_PWMA;
        break;
    default : // MCPWM_AQ_OUTPUT_3B
        HWREG(base + MCPWM_O_PWM3_AQOTSFRC) = MCPWM_PWM3_AQOTSFRC_PWMB;
        break;
    }
}

//*****************************************************************************
//
//! Sets the Action Qualifier shadow load mode
//!
//! \param base is the base address of the MCPWM module.
//! \param aqModule is the Action Qualifier module value.
//! \param loadMode is the shadow to active load mode.
//!
//! This function enables and sets the Action Qualifier shadow load mode.
//! Valid values for the variables are:
//!  - aqModule
//!      - MCPWM_ACTION_QUALIFIER_1A - Action Qualifier A for PWM 1.
//!      - MCPWM_ACTION_QUALIFIER_1B - Action Qualifier B for PWM 1.
//!      - MCPWM_ACTION_QUALIFIER_2A - Action Qualifier A for PWM 2.
//!      - MCPWM_ACTION_QUALIFIER_2B - Action Qualifier B for PWM 2.
//!      - MCPWM_ACTION_QUALIFIER_3A - Action Qualifier A for PWM 3.
//!      - MCPWM_ACTION_QUALIFIER_3B - Action Qualifier B for PWM 3.
//!  - loadMode
//!      - MCPWM_AQ_LOAD_ON_CNTR_ZERO - load when counter equals zero
//!      - MCPWM_AQ_LOAD_ON_CNTR_PERIOD - load when counter equals period
//!      - MCPWM_AQ_LOAD_ON_CNTR_ZERO_PERIOD - load when counter equals
//!                                               zero or period
//!      - MCPWM_AQ_LOAD_FREEZE  - Freeze shadow to active load
//!      - MCPWM_AQ_LOAD_ON_SYNC_CNTR_ZERO - load on sync or when counter
//!                                          equals zero
//!      - MCPWM_AQ_LOAD_ON_SYNC_CNTR_PERIOD - load on sync or when counter
//!                                           equals period
//!      - MCPWM_AQ_LOAD_ON_SYNC_CNTR_ZERO_PERIOD - load on sync or when
//!                                               counter equals zero or period
//!      - MCPWM_AQ_LOAD_ON_SYNC_ONLY - load on sync only
//!
//! \return None.
//
//*****************************************************************************
static inline void
MCPWM_setActionQualifierShadowLoadMode(uint32_t base,
                                      MCPWM_ActionQualifierModule aqModule,
                                      MCPWM_ActionQualifierLoadMode loadMode)
{
    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));

    //
    // Set the appropriate sync and load mode bits and also enable shadow
    // load mode. Shadow to active load can also be frozen.
    //
    //
    // Set the Shadow Load Mode 
    //
    switch (aqModule)
    {
    case MCPWM_ACTION_QUALIFIER_1A:
        HWREG(base + MCPWM_O_AQCTL) = ((HWREG(base + MCPWM_O_AQCTL) & 
                                        ~MCPWM_AQCTL_PWM1_LDAQBMODE_M) |   // clear the current configurations
                                        ((uint32_t)loadMode << MCPWM_AQCTL_PWM1_LDAQAMODE_S)); // update the configuration
        break;
    case MCPWM_ACTION_QUALIFIER_1B:
        HWREG(base + MCPWM_O_AQCTL) = ((HWREG(base + MCPWM_O_AQCTL) & 
                                        ~MCPWM_AQCTL_PWM1_LDAQBMODE_M) |   // clear the current configurations
                                        ((uint32_t)loadMode << MCPWM_AQCTL_PWM1_LDAQBMODE_S)); // update the configuration
        break;
    case MCPWM_ACTION_QUALIFIER_2A:
        HWREG(base + MCPWM_O_AQCTL) = ((HWREG(base + MCPWM_O_AQCTL) & 
                                        ~MCPWM_AQCTL_PWM2_LDAQAMODE_M) |   // clear the current configurations
                                        ((uint32_t)loadMode << MCPWM_AQCTL_PWM2_LDAQAMODE_S)); // update the configuration
        break;
    case MCPWM_ACTION_QUALIFIER_2B:
        HWREG(base + MCPWM_O_AQCTL) = ((HWREG(base + MCPWM_O_AQCTL) & 
                                        ~MCPWM_AQCTL_PWM2_LDAQBMODE_M) |   // clear the current configurations
                                        ((uint32_t)loadMode << MCPWM_AQCTL_PWM2_LDAQBMODE_S)); // update the configuration
        break;
    case MCPWM_ACTION_QUALIFIER_3A:
        HWREG(base + MCPWM_O_AQCTL) = ((HWREG(base + MCPWM_O_AQCTL) & 
                                        ~MCPWM_AQCTL_PWM3_LDAQAMODE_M) |   // clear the current configurations
                                        ((uint32_t)loadMode << MCPWM_AQCTL_PWM3_LDAQAMODE_S)); // update the configuration
        break;
    default :  // MCPWM_ACTION_QUALIFIER_3B:
        HWREG(base + MCPWM_O_AQCTL) = ((HWREG(base + MCPWM_O_AQCTL) & 
                                        ~MCPWM_AQCTL_PWM3_LDAQBMODE_M) |   // clear the current configurations
                                        ((uint32_t)loadMode << MCPWM_AQCTL_PWM3_LDAQBMODE_S)); // update the configuration
        break;  
    }
    
}

//*****************************************************************************
//
//! Set up Action qualifier outputs
//!
//! \param base is the base address of the MCPWM module.
//! \param mcpwmOutput is the MCPWM pin type.
//! \param output is the Active Action Qualifier output.
//! \param event is the event that causes a change in output.
//!
//! This function sets up the Action Qualifier output on MCPWM A or MCPWMB,
//! depending on the value of mcpwmOutput, to a value specified by outPut based
//! on the input events - specified by event.
//! The following are valid values for the parameters.
//!   - mcpwmOutput
//!       - MCPWM_AQ_OUTPUT_1A - MCPWMx1A output
//!       - MCPWM_AQ_OUTPUT_1B - MCPWMx1B output
//!       - MCPWM_AQ_OUTPUT_2A - MCPWMx2A output
//!       - MCPWM_AQ_OUTPUT_2B - MCPWMx2B output
//!       - MCPWM_AQ_OUTPUT_3A - MCPWMx3A output
//!       - MCPWM_AQ_OUTPUT_3B - MCPWMx3B output
//!   - output
//!       - MCPWM_AQ_OUTPUT_NO_CHANGE  - No change in the output pins
//!       - MCPWM_AQ_OUTPUT_LOW        - Set output pins to low
//!       - MCPWM_AQ_OUTPUT_HIGH       - Set output pins to High
//!       - MCPWM_AQ_OUTPUT_TOGGLE     - Toggle the output pins
//!   - event
//!       - MCPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO       - Time base counter equals
//!                                                 zero
//!       - MCPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD     - Time base counter equals
//!                                                 period
//!       - MCPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA    - Time base counter up equals
//!                                                 CMPA
//!       - MCPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA  - Time base counter down
//!                                                 equals CMPA
//!       - MCPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB    - Time base counter up equals
//!                                                 CMPB
//!       - MCPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB  - Time base counter down
//!                                                 equals CMPB
//!
//! \return None.
//
//*****************************************************************************
static inline void
MCPWM_setActionQualifierActionActive(uint32_t base,
                              MCPWM_ActionQualifierOutputModule mcpwmOutput,
                              MCPWM_ActionQualifierOutput output,
                              MCPWM_ActionQualifierOutputEvent event)
{

    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));

    uint32_t mask = ((uint32_t)0x3U << (uint32_t)event);
    uint32_t value = ((uint32_t)output <<  (uint32_t)event);

    //
    // Write to the PWMx_AQCTLy register for the actions on counter equals zero,
    // period, CMPA UP/DOWN, CMPB UP/DOWN
    //
    switch (mcpwmOutput)
    {
    case MCPWM_AQ_OUTPUT_1A :
        HWREG(base + MCPWM_O_PWM1_AQCTLA) = (HWREG(base + MCPWM_O_PWM1_AQCTLA) & ~mask) | value;
        break;
    case MCPWM_AQ_OUTPUT_1B :
        HWREG(base + MCPWM_O_PWM1_AQCTLB) = (HWREG(base + MCPWM_O_PWM1_AQCTLB) & ~mask) | value;
        break;
    case MCPWM_AQ_OUTPUT_2A :
        HWREG(base + MCPWM_O_PWM2_AQCTLA) = (HWREG(base + MCPWM_O_PWM2_AQCTLA) & ~mask) | value;
        break;
    case MCPWM_AQ_OUTPUT_2B :
        HWREG(base + MCPWM_O_PWM2_AQCTLB) = (HWREG(base + MCPWM_O_PWM2_AQCTLB) & ~mask) | value;
        break;
    case MCPWM_AQ_OUTPUT_3A :
        HWREG(base + MCPWM_O_PWM3_AQCTLA) = (HWREG(base + MCPWM_O_PWM3_AQCTLA) & ~mask) | value;
        break;
    default : // MCPWM_AQ_OUTPUT_3B
        HWREG(base + MCPWM_O_PWM3_AQCTLB) = (HWREG(base + MCPWM_O_PWM3_AQCTLB) & ~mask) | value;
        break;
    }
}

//*****************************************************************************
//
//! Set up Action qualifier outputs in Shadow register
//!
//! \param base is the base address of the MCPWM module.
//! \param mcpwmOutput is the MCPWM pin type.
//! \param output is the Shadow Action Qualifier output.
//! \param event is the event that causes a change in output.
//!
//! This function sets up the Action Qualifier output on MCPWM A or MCPWMB,
//! depending on the value of mcpwmOutput, to a value specified by outPut based
//! on the input events - specified by event.
//! The following are valid values for the parameters.
//!   - mcpwmOutput
//!       - MCPWM_AQ_OUTPUT_1A - MCPWMx1A output
//!       - MCPWM_AQ_OUTPUT_1B - MCPWMx1B output
//!       - MCPWM_AQ_OUTPUT_2A - MCPWMx2A output
//!       - MCPWM_AQ_OUTPUT_2B - MCPWMx2B output
//!       - MCPWM_AQ_OUTPUT_3A - MCPWMx3A output
//!       - MCPWM_AQ_OUTPUT_3B - MCPWMx3B output
//!   - output
//!       - MCPWM_AQ_OUTPUT_NO_CHANGE  - No change in the output pins
//!       - MCPWM_AQ_OUTPUT_LOW        - Set output pins to low
//!       - MCPWM_AQ_OUTPUT_HIGH       - Set output pins to High
//!       - MCPWM_AQ_OUTPUT_TOGGLE     - Toggle the output pins
//!   - event
//!       - MCPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO       - Time base counter equals
//!                                                 zero
//!       - MCPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD     - Time base counter equals
//!                                                 period
//!       - MCPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA    - Time base counter up equals
//!                                                 CMPA
//!       - MCPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA  - Time base counter down
//!                                                 equals CMPA
//!       - MCPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB    - Time base counter up equals
//!                                                 CMPB
//!       - MCPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB  - Time base counter down
//!                                                 equals CMPB
//!
//! \return None.
//
//*****************************************************************************
static inline void
MCPWM_setActionQualifierActionShadow(uint32_t base,
                              MCPWM_ActionQualifierOutputModule mcpwmOutput,
                              MCPWM_ActionQualifierOutput output,
                              MCPWM_ActionQualifierOutputEvent event)
{

    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));

    uint32_t mask = ((uint32_t)0x3U << (uint32_t)event);
    uint32_t value = ((uint32_t)output <<  (uint32_t)event);
    
    //
    // Write to the PWMx_AQCTLy register for the actions on counter equals zero,
    // period, CMPA UP/DOWN, CMPB UP/DOWN
    //
    switch (mcpwmOutput)
    {
    case MCPWM_AQ_OUTPUT_1A :
        HWREG(base + MCPWM_O_PWM1_AQCTLAS) = (HWREG(base + MCPWM_O_PWM1_AQCTLAS) &  ~mask) | value;
        break;
    case MCPWM_AQ_OUTPUT_1B :
        HWREG(base + MCPWM_O_PWM1_AQCTLBS) = (HWREG(base + MCPWM_O_PWM1_AQCTLBS) &  ~mask) | value;
        break;
    case MCPWM_AQ_OUTPUT_2A :
        HWREG(base + MCPWM_O_PWM2_AQCTLAS) = (HWREG(base + MCPWM_O_PWM2_AQCTLAS) &  ~mask) | value;
        break;
    case MCPWM_AQ_OUTPUT_2B :
        HWREG(base + MCPWM_O_PWM2_AQCTLBS) = (HWREG(base + MCPWM_O_PWM2_AQCTLBS) &  ~mask) | value;
        break;
    case MCPWM_AQ_OUTPUT_3A :
        HWREG(base + MCPWM_O_PWM3_AQCTLAS) = (HWREG(base + MCPWM_O_PWM3_AQCTLAS) &  ~mask) | value;
        break;
    default : // MCPWM_AQ_OUTPUT_3B
        HWREG(base + MCPWM_O_PWM3_AQCTLBS) = (HWREG(base + MCPWM_O_PWM3_AQCTLBS) &  ~mask) | value;
        break;
    }
}

//*****************************************************************************
//
//! Set up Action qualifier action for all events in one go 
//!
//! \param base is the base address of the MCPWM module.
//! \param mcpwmOutput is the MCPWM pin type.
//! \param action is the desired action when the specified event occurs
//!
//! This function sets up the Action Qualifier output on MCPWMA or MCPWMB,
//! depending on the value of mcpwmOutput, to a value specified by action.
//! Valid action param values from different time base counter scenarios
//! should be OR'd together to configure complete action for a pwm output.
//! The following are valid values for the parameters.
//!   - mcpwmOutput
//!       - MCPWM_AQ_OUTPUT_1A - MCPWMx1A output
//!       - MCPWM_AQ_OUTPUT_1B - MCPWMx1B output
//!       - MCPWM_AQ_OUTPUT_2A - MCPWMx2A output
//!       - MCPWM_AQ_OUTPUT_2B - MCPWMx2B output
//!       - MCPWM_AQ_OUTPUT_3A - MCPWMx3A output
//!       - MCPWM_AQ_OUTPUT_3B - MCPWMx3B output
//!
//!   - action
//!       - When time base counter equals zero
//!         - MCPWM_AQ_OUTPUT_NO_CHANGE_ZERO   - Time base counter equals zero
//!                                             and no change in output pins
//!         - MCPWM_AQ_OUTPUT_LOW_ZERO         - Time base counter equals zero
//!                                             and set output pins to low
//!         - MCPWM_AQ_OUTPUT_HIGH_ZERO        - Time base counter equals zero
//!                                             and set output pins to high
//!         - MCPWM_AQ_OUTPUT_TOGGLE_ZERO      - Time base counter equals zero
//!                                             and toggle the output pins
//!       - When time base counter equals period
//!         - MCPWM_AQ_OUTPUT_NO_CHANGE_PERIOD - Time base counter equals period
//!                                             and no change in output pins
//!         - MCPWM_AQ_OUTPUT_LOW_PERIOD       - Time base counter equals period
//!                                             and set output pins to low
//!         - MCPWM_AQ_OUTPUT_HIGH_PERIOD      - Time base counter equals period
//!                                             and set output pins to high
//!         - MCPWM_AQ_OUTPUT_TOGGLE_PERIOD    - Time base counter equals period
//!                                             and toggle the output pins
//!       - When time base counter equals CMPA during up-count
//!         - MCPWM_AQ_OUTPUT_NO_CHANGE_UP_CMPA  - Time base counter up equals
//!                                               CMPA and no change in the
//!                                               output pins
//!         - MCPWM_AQ_OUTPUT_LOW_UP_CMPA        - Time base counter up equals
//!                                               CMPA and set output pins low
//!         - MCPWM_AQ_OUTPUT_HIGH_UP_CMPA       - Time base counter up equals
//!                                               CMPA and set output pins high
//!         - MCPWM_AQ_OUTPUT_TOGGLE_UP_CMPA     - Time base counter up equals
//!                                               CMPA and toggle output pins
//!       - When time base counter equals CMPA during down-count
//!         - MCPWM_AQ_OUTPUT_NO_CHANGE_DOWN_CMPA - Time base counter down equals
//!                                                CMPA and no change in the
//!                                                output pins
//!         - MCPWM_AQ_OUTPUT_LOW_DOWN_CMPA      - Time base counter down equals
//!                                               CMPA and set output pins low
//!         - MCPWM_AQ_OUTPUT_HIGH_DOWN_CMPA     - Time base counter down equals
//!                                               CMPA and set output pins high
//!         - MCPWM_AQ_OUTPUT_TOGGLE_DOWN_CMPA   - Time base counter down equals
//!                                               CMPA and toggle output pins
//!       - When time base counter equals CMPB during up-count
//!         - MCPWM_AQ_OUTPUT_NO_CHANGE_UP_CMPB  - Time base counter up equals
//!                                               CMPB and no change in the
//!                                               output pins
//!         - MCPWM_AQ_OUTPUT_LOW_UP_CMPB        - Time base counter up equals
//!                                               CMPB and set output pins low
//!         - MCPWM_AQ_OUTPUT_HIGH_UP_CMPB       - Time base counter up equals
//!                                               CMPB and set output pins high
//!         - MCPWM_AQ_OUTPUT_TOGGLE_UP_CMPB     - Time base counter up equals
//!                                               CMPB and toggle output pins
//!       - When time base counter equals CMPB during down-count
//!         - MCPWM_AQ_OUTPUT_NO_CHANGE_DOWN_CMPB- Time base counter down equals
//!                                               CMPB and no change in the
//!                                               output pins
//!         - MCPWM_AQ_OUTPUT_LOW_DOWN_CMPB      - Time base counter down equals
//!                                               CMPB and set output pins low
//!         - MCPWM_AQ_OUTPUT_HIGH_DOWN_CMPB     - Time base counter down equals
//!                                               CMPB and set output pins high
//!         - MCPWM_AQ_OUTPUT_TOGGLE_DOWN_CMPB   - Time base counter down equals
//!                                               CMPB and toggle output pins
//!
//! \b note:  A logical OR of the valid values should be passed as the action
//!           parameter. Single action should be configured for each time base
//!           counter scenario.
//!
//! \return None.
//
//*****************************************************************************
static inline void
MCPWM_setActionQualifierActionCompleteActive(uint32_t base,
                                   MCPWM_ActionQualifierOutputModule mcpwmOutput,
                                   uint16_t action)
{
    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));

    ASSERT(action <= (MCPWM_PWM1_AQCTLA_ZRO_M | \
                        MCPWM_PWM1_AQCTLA_PRD_M | \
                        MCPWM_PWM1_AQCTLA_CAU_M | \
                        MCPWM_PWM1_AQCTLA_CAD_M | \
                        MCPWM_PWM1_AQCTLA_CBU_M | \
                        MCPWM_PWM1_AQCTLA_CBD_M ));

    //
    // Write to ZRO, PRD, CAU, CAD, CBU or CBD bits of AQCTLA register
    //
    switch (mcpwmOutput)
    {
    case MCPWM_AQ_OUTPUT_1A :
        HWREG(base + MCPWM_O_PWM1_AQCTLA) = (uint32_t) action;
        break;
    case MCPWM_AQ_OUTPUT_1B :
        HWREG(base + MCPWM_O_PWM1_AQCTLB) = (uint32_t) action;
        break;
    case MCPWM_AQ_OUTPUT_2A :
        HWREG(base + MCPWM_O_PWM2_AQCTLA) = (uint32_t) action;
        break;
    case MCPWM_AQ_OUTPUT_2B :
        HWREG(base + MCPWM_O_PWM2_AQCTLB) = (uint32_t) action;
        break;
    case MCPWM_AQ_OUTPUT_3A :
        HWREG(base + MCPWM_O_PWM3_AQCTLA) = (uint32_t) action;
        break;
    default : // MCPWM_AQ_OUTPUT_3B
        HWREG(base + MCPWM_O_PWM3_AQCTLB) = (uint32_t) action;
        break;
    }
}


//*****************************************************************************
//
//! Set up Action qualifier action for all events in one go in shadow register
//!
//! \param base is the base address of the MCPWM module.
//! \param mcpwmOutput is the MCPWM pin type.
//! \param action is the desired action when the specified event occurs
//!
//! This function sets up the Action Qualifier output on MCPWMA or MCPWMB,
//! depending on the value of mcpwmOutput, to a value specified by action.
//! Valid action param values from different time base counter scenarios
//! should be OR'd together to configure complete action for a pwm output.
//! The following are valid values for the parameters.
//!   - mcpwmOutput
//!       - MCPWM_AQ_OUTPUT_1A - MCPWMx1A output
//!       - MCPWM_AQ_OUTPUT_1B - MCPWMx1B output
//!       - MCPWM_AQ_OUTPUT_2A - MCPWMx2A output
//!       - MCPWM_AQ_OUTPUT_2B - MCPWMx2B output
//!       - MCPWM_AQ_OUTPUT_3A - MCPWMx3A output
//!       - MCPWM_AQ_OUTPUT_3B - MCPWMx3B output
//!
//!   - action
//!       - When time base counter equals zero
//!         - MCPWM_AQ_OUTPUT_NO_CHANGE_ZERO   - Time base counter equals zero
//!                                             and no change in output pins
//!         - MCPWM_AQ_OUTPUT_LOW_ZERO         - Time base counter equals zero
//!                                             and set output pins to low
//!         - MCPWM_AQ_OUTPUT_HIGH_ZERO        - Time base counter equals zero
//!                                             and set output pins to high
//!         - MCPWM_AQ_OUTPUT_TOGGLE_ZERO      - Time base counter equals zero
//!                                             and toggle the output pins
//!       - When time base counter equals period
//!         - MCPWM_AQ_OUTPUT_NO_CHANGE_PERIOD - Time base counter equals period
//!                                             and no change in output pins
//!         - MCPWM_AQ_OUTPUT_LOW_PERIOD       - Time base counter equals period
//!                                             and set output pins to low
//!         - MCPWM_AQ_OUTPUT_HIGH_PERIOD      - Time base counter equals period
//!                                             and set output pins to high
//!         - MCPWM_AQ_OUTPUT_TOGGLE_PERIOD    - Time base counter equals period
//!                                             and toggle the output pins
//!       - When time base counter equals CMPA during up-count
//!         - MCPWM_AQ_OUTPUT_NO_CHANGE_UP_CMPA  - Time base counter up equals
//!                                               CMPA and no change in the
//!                                               output pins
//!         - MCPWM_AQ_OUTPUT_LOW_UP_CMPA        - Time base counter up equals
//!                                               CMPA and set output pins low
//!         - MCPWM_AQ_OUTPUT_HIGH_UP_CMPA       - Time base counter up equals
//!                                               CMPA and set output pins high
//!         - MCPWM_AQ_OUTPUT_TOGGLE_UP_CMPA     - Time base counter up equals
//!                                               CMPA and toggle output pins
//!       - When time base counter equals CMPA during down-count
//!         - MCPWM_AQ_OUTPUT_NO_CHANGE_DOWN_CMPA - Time base counter down equals
//!                                                CMPA and no change in the
//!                                                output pins
//!         - MCPWM_AQ_OUTPUT_LOW_DOWN_CMPA      - Time base counter down equals
//!                                               CMPA and set output pins low
//!         - MCPWM_AQ_OUTPUT_HIGH_DOWN_CMPA     - Time base counter down equals
//!                                               CMPA and set output pins high
//!         - MCPWM_AQ_OUTPUT_TOGGLE_DOWN_CMPA   - Time base counter down equals
//!                                               CMPA and toggle output pins
//!       - When time base counter equals CMPB during up-count
//!         - MCPWM_AQ_OUTPUT_NO_CHANGE_UP_CMPB  - Time base counter up equals
//!                                               CMPB and no change in the
//!                                               output pins
//!         - MCPWM_AQ_OUTPUT_LOW_UP_CMPB        - Time base counter up equals
//!                                               CMPB and set output pins low
//!         - MCPWM_AQ_OUTPUT_HIGH_UP_CMPB       - Time base counter up equals
//!                                               CMPB and set output pins high
//!         - MCPWM_AQ_OUTPUT_TOGGLE_UP_CMPB     - Time base counter up equals
//!                                               CMPB and toggle output pins
//!       - When time base counter equals CMPB during down-count
//!         - MCPWM_AQ_OUTPUT_NO_CHANGE_DOWN_CMPB- Time base counter down equals
//!                                               CMPB and no change in the
//!                                               output pins
//!         - MCPWM_AQ_OUTPUT_LOW_DOWN_CMPB      - Time base counter down equals
//!                                               CMPB and set output pins low
//!         - MCPWM_AQ_OUTPUT_HIGH_DOWN_CMPB     - Time base counter down equals
//!                                               CMPB and set output pins high
//!         - MCPWM_AQ_OUTPUT_TOGGLE_DOWN_CMPB   - Time base counter down equals
//!                                               CMPB and toggle output pins
//!
//! \b note:  A logical OR of the valid values should be passed as the action
//!           parameter. Single action should be configured for each time base
//!           counter scenario.
//!
//! \return None.
//
//*****************************************************************************
static inline void
MCPWM_setActionQualifierActionCompleteShadow(uint32_t base,
                                   MCPWM_ActionQualifierOutputModule  mcpwmOutput,
                                   uint16_t action)
{
    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));

    ASSERT(action <= (MCPWM_PWM1_AQCTLAS_ZRO_M | \
        MCPWM_PWM1_AQCTLAS_PRD_M | \
        MCPWM_PWM1_AQCTLAS_CAU_M | \
        MCPWM_PWM1_AQCTLAS_CAD_M | \
        MCPWM_PWM1_AQCTLAS_CBU_M | \
        MCPWM_PWM1_AQCTLAS_CBD_M ));
    //
    // Write to ZRO, PRD, CAU, CAD, CBU or CBD bits of AQCTLA register
    //
    switch (mcpwmOutput)
    {
    case MCPWM_AQ_OUTPUT_1A :
        HWREG(base + MCPWM_O_PWM1_AQCTLAS) = action;
        break;
    case MCPWM_AQ_OUTPUT_1B :
        HWREG(base + MCPWM_O_PWM1_AQCTLBS) = action;
        break;
    case MCPWM_AQ_OUTPUT_2A :
        HWREG(base + MCPWM_O_PWM2_AQCTLAS) = action;
        break;
    case MCPWM_AQ_OUTPUT_2B :
        HWREG(base + MCPWM_O_PWM2_AQCTLBS) = action;
        break;
    case MCPWM_AQ_OUTPUT_3A :
        HWREG(base + MCPWM_O_PWM3_AQCTLAS) = action;
        break;
    default : // MCPWM_AQ_OUTPUT_3B
        HWREG(base + MCPWM_O_PWM3_AQCTLBS) = action;
        break;
    }
}

//*****************************************************************************
//
//! Enable Global shadow load mode.
//!
//! \param base is the base address of the MCPWM module.
//!
//! This function enables Global shadow to active load mode of registers.
//! The trigger source for loading shadow to active is determined by
//! MCPWM_setGlobalLoadTrigger() function.
//! 
//! When enabled, the Global Load will overwrite the local load strobes.
//!
//! \return None.
//
//*****************************************************************************
static inline void
MCPWM_enableGlobalLoad(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));

    //
    // Shadow to active load is controlled globally
    //
    EALLOW;
    HWREG(base + MCPWM_O_GLDCTL) |= MCPWM_GLDCTL_GLD;
    EDIS;
}

//*****************************************************************************
//
//! Disable Global shadow load mode.
//!
//! \param base is the base address of the MCPWM module.
//!
//! This function disables Global shadow to active load mode of registers.
//! Loading shadow to active is determined individually.
//!
//! \return None.
//
//*****************************************************************************
static inline void
MCPWM_disableGlobalLoad(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));

    //
    // Shadow to active load is controlled individually
    //
    EALLOW;
    HWREG(base + MCPWM_O_GLDCTL) &= ~MCPWM_GLDCTL_GLD;
    EDIS;
}

//*****************************************************************************
//
//! Set the Global shadow load pulse.
//!
//! \param base is the base address of the MCPWM module.
//! \param loadTrigger is the pulse that causes global shadow load.
//!
//! This function sets the pulse that causes Global shadow to active load. 
//! 
//! 
//! Valid values for the loadTrigger parameter are:
//!
//!   - MCPWM_GL_LOAD_PULSE_CNTR_ZERO              - load when counter is equal
//!                                                 to zero
//!   - MCPWM_GL_LOAD_PULSE_CNTR_PERIOD            - load when counter is equal
//!                                                 to period
//!   - MCPWM_GL_LOAD_PULSE_CNTR_ZERO_PERIOD       - load when counter is equal
//!                                                 to zero or period
//!   - MCPWM_GL_LOAD_PULSE_GLOBAL_FORCE           - load on global force
//!
//! \return None.
//!
//! \note 
//! This selection is only active once the Global shadow load mode is enabled, 
//! i.e, \b MCPWM_enableGlobalLoad() is called. Also, this pulse is called 
//! global load strobe and overwrites any local load strobe, causing active 
//! registers to load from shadow ones. Notice the APIs with Active and Shadow
//! names. 
//
//*****************************************************************************
static inline void
MCPWM_setGlobalLoadTrigger(uint32_t base, MCPWM_GlobalLoadTrigger loadTrigger)
{
    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));

    //
    // Set the Global shadow to active load pulse
    //
    EALLOW;
    HWREG(base + MCPWM_O_GLDCTL) =
               ((HWREG(base + MCPWM_O_GLDCTL) & ~MCPWM_GLDCTL_GLDMODE_M) |
                ((uint32_t)loadTrigger << MCPWM_GLDCTL_GLDMODE_S));
    EDIS;
}

//*****************************************************************************
//
//! Enable One shot global shadow to active load.
//!
//! \param base is the base address of the MCPWM module.
//!
//! This function enables a one time global shadow to active load. Register
//! load happens every time the event set by the
//! MCPWM_setGlobalLoadTrigger() occurs.
//!
//! \return None.
//
//*****************************************************************************
static inline void
MCPWM_enableGlobalLoadOneShotMode(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));

    //
    // Enable global continuous shadow to active load
    //
    EALLOW;
    HWREG(base + MCPWM_O_GLDCTL) |= MCPWM_GLDCTL_OSHTMODE;
    EDIS;
}

//*****************************************************************************
//
//! Enable continuous global shadow to active load.
//!
//! \param base is the base address of the MCPWM module.
//!
//! This function enables global continuous shadow to active load. Register
//! load happens every time the event set by the
//! MCPWM_setGlobalLoadTrigger() occurs.
//!
//! \return None.
//
//*****************************************************************************
static inline void
MCPWM_disableGlobalLoadOneShotMode(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));

    //
    // Enable global continuous shadow to active load
    //
    EALLOW;
    HWREG(base + MCPWM_O_GLDCTL) &= ~MCPWM_GLDCTL_OSHTMODE;
    EDIS;
}

//*****************************************************************************
//
//! Set One shot global shadow to active load pulse.
//!
//! \param base is the base address of the MCPWM module.
//!
//! This function sets a one time global shadow to active load pulse. The pulse
//! propagates to generate a load signal if any of the events set by
//! MCPWM_setGlobalLoadTrigger() occur.
//!
//! \return None.
//
//*****************************************************************************
static inline void
MCPWM_setGlobalLoadOneShotLatch(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));

    //
    // Set a one shot Global shadow load pulse.
    //
    EALLOW;
    HWREG(base + MCPWM_O_GLDOSHTCTL) |= MCPWM_GLDOSHTCTL_OSHTLD;
    EDIS;
}

//*****************************************************************************
//
//! Clears One shot global shadow to active load pulse.
//!
//! \param base is the base address of the MCPWM module.
//!
//! This function sets a one time global shadow to active load pulse. The pulse
//! propagates to generate a load signal if any of the events set by
//! MCPWM_setGlobalLoadTrigger() occur.
//!
//! \return None.
//
//*****************************************************************************
static inline void
MCPWM_clearGlobalLoadOneShotLatch(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));

    //
    // Set a one shot Global shadow load pulse.
    //
    EALLOW;
    HWREG(base + MCPWM_O_GLDOSHTCTL) &= ~MCPWM_GLDOSHTCTL_OSHTLD;
    EDIS;
}

//*****************************************************************************
//
//! Get One shot global shadow to active load pulse Status.
//!
//! \param base is the base address of the MCPWM module.
//!
//!
//! \return One shot global load strobe status.
//
//*****************************************************************************
static inline bool
MCPWM_getGlobalLoadOneShotLatchStatus(uint32_t base)
{   
    bool status;
    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));

    //
    // Set a one shot Global shadow load pulse.
    //
    EALLOW;
    status = ((HWREG(base + MCPWM_O_GLDOSHTSTS) & MCPWM_GLDOSHTSTS_OSHTLATCH) == MCPWM_GLDOSHTSTS_OSHTLATCH);
    EDIS;

    return (status);
}

//*****************************************************************************
//
//! Force a software One shot global shadow to active load pulse.
//!
//! \param base is the base address of the MCPWM module.
//!
//! This function forces a software a one time global shadow to active load
//! pulse.
//!
//! \return None.
//
//*****************************************************************************
static inline void
MCPWM_forceGlobalLoadOneShotEvent(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));

    //
    // Force a Software Global shadow load pulse
    //
    EALLOW;
    HWREGH(base + MCPWM_O_GLDOSHTCTL) |= MCPWM_GLDOSHTCTL_GFRCLD;
    EDIS;
}

//*****************************************************************************
//
//! Sets Dead Band signal output swap mode.
//!
//! \param base is the base address of the MCPWM module.
//! \param output is the MCPWM Dead Band output.
//! \param enableSwapMode is the output swap mode.
//!
//! This function sets up the output signal swap mode. For example if the
//! output variable is set to MCPWM_DB_OUTPUT_A and enableSwapMode is TRUE, then
//! the MCPWM A output gets its signal from the MCPWM B signal path. Valid values
//! for the input variables are:
//!  - output
//!      - MCPWM_DB_OUTPUT_A   - MCPWM output A
//!      - MCPWM_DB_OUTPUT_B   - MCPWM output B
//!  - enableSwapMode
//!      - TRUE     - the output is swapped
//!      - FALSE    - the output and the signal path are the same.
//!
//! \return None.
//
//*****************************************************************************
static inline void
MCPWM_setDeadBandOutputSwapMode(uint32_t base, MCPWM_DeadBandOutput output,
                               bool enableSwapMode)
{
    uint32_t mask;

    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));

    mask = (uint32_t)1U << ((uint32_t)output + MCPWM_DBCTL_OUTSWAP_S);

    if(enableSwapMode)
    {
        //
        // Set the appropriate outswap bit to swap output
        //
        HWREG(base + MCPWM_O_DBCTL) = (HWREG(base + MCPWM_O_DBCTL) | mask);
    }
    else
    {
        //
        // Clear the appropriate outswap bit to disable output swap
        //
        HWREG(base + MCPWM_O_DBCTL) = (HWREG(base + MCPWM_O_DBCTL) & ~mask);
    }
}

//*****************************************************************************
//
//! Sets Dead Band signal output mode.
//!
//! \param base is the base address of the MCPWM module.
//! \param delayMode is the Dead Band delay type.
//! \param enableDelayMode is the dead band delay mode.
//!
//! This function sets up the dead band delay mode. The delayMode variable
//! determines if the applied delay is Rising Edge or Falling Edge. The
//! enableDelayMode determines if a dead band delay should be applied.
//! Valid values for the variables are:
//!  - delayMode
//!      - MCPWM_DB_RED   - Rising Edge delay
//!      - MCPWM_DB_FED   - Falling Edge delay
//!  - enableDelayMode
//!      - TRUE     - Falling edge or Rising edge delay is applied.
//!      - FALSE    - Dead Band delay is bypassed.
//!
//! \return None.
//
//*****************************************************************************
static inline void
MCPWM_setDeadBandDelayMode(uint32_t base, MCPWM_DeadBandDelayMode delayMode,
                          bool enableDelayMode)
{
    uint32_t mask;

    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));

    mask = (uint32_t)1U << ((uint32_t)delayMode + MCPWM_DBCTL_OUT_MODE_S);

    if(enableDelayMode)
    {
         //
         // Set the appropriate outmode bit to enable Dead Band delay
         //
         HWREG(base + MCPWM_O_DBCTL) = (HWREG(base + MCPWM_O_DBCTL) | mask);
    }
    else
    {
        //
        // Clear the appropriate outswap bit to disable output swap
        //
        HWREG(base + MCPWM_O_DBCTL) = (HWREG(base + MCPWM_O_DBCTL) & ~ mask);
    }
}

//*****************************************************************************
//
//! Sets Dead Band delay polarity.
//!
//! \param base is the base address of the MCPWM module.
//! \param delayMode is the Dead Band delay type.
//! \param polarity is the polarity of the delayed signal.
//!
//! This function sets up the polarity as determined by the variable polarity
//! of the Falling Edge or Rising Edge delay depending on the value of
//! delayMode. Valid values for the variables are:
//!   - delayMode
//!       - MCPWM_DB_RED   - Rising Edge delay
//!       - MCPWM_DB_FED   - Falling Edge delay
//!   - polarity
//!       - MCPWM_DB_POLARITY_ACTIVE_HIGH   - polarity is not inverted.
//!       - MCPWM_DB_POLARITY_ACTIVE_LOW    - polarity is inverted.
//!
//! \return None.
//
//*****************************************************************************
static inline void
MCPWM_setDeadBandDelayPolarity(uint32_t base,
                              MCPWM_DeadBandDelayMode delayMode,
                              MCPWM_DeadBandPolarity polarity)
{
    uint16_t shift;

    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));

    shift = (((uint16_t)delayMode ^ 0x1U) + MCPWM_DBCTL_POLSEL_S);

    //
    // Set the appropriate polsel bits for dead band polarity
    //
    HWREG(base + MCPWM_O_DBCTL) =
                       ((HWREG(base + MCPWM_O_DBCTL) & ~(1U << shift)) |
                        ((uint32_t)polarity << shift));
}

//*****************************************************************************
//
//! Sets Rising Edge Dead Band delay input.
//!
//! \param base is the base address of the MCPWM module.
//! \param input is the input signal to the dead band.
//!
//! This function sets up the rising Edge delay input signal.
//! Valid values for input are:
//!     - MCPWM_DB_INPUT_MCPWMA   - Input signal is MCPWMA( Valid for both Falling
//!                                  Edge and Rising Edge)
//!     - MCPWM_DB_INPUT_MCPWMB   - Input signal is MCPWMB( Valid for both Falling
//!                                  Edge and Rising Edge)
//!
//! \return None.
//
//*****************************************************************************
static inline void
MCPWM_setRisingEdgeDeadBandDelayInput(uint32_t base, uint16_t input)
{
    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));
    ASSERT((input == MCPWM_DB_INPUT_MCPWMA) ||
           (input == MCPWM_DB_INPUT_MCPWMB));

    //
    // Set the Rising Edge Delay input
    //
    HWREG(base + MCPWM_O_DBCTL) =
            ((HWREG(base + MCPWM_O_DBCTL) & ~(1U << (MCPWM_DBCTL_IN_MODE_S))) |
             (input << MCPWM_DBCTL_IN_MODE_S));
}

//*****************************************************************************
//
//! Sets Dead Band delay input.
//!
//! \param base is the base address of the MCPWM module.
//! \param input is the input signal to the dead band.
//!
//! This function sets up the rising Edge delay input signal.
//! Valid values for input are:
//!   - MCPWM_DB_INPUT_MCPWMA   - Input signal is MCPWMA(Valid for both Falling
//!                                Edge and Rising Edge)
//!   - MCPWM_DB_INPUT_MCPWMB   - Input signal is MCPWMB(Valid for both Falling
//!                                Edge and Rising Edge)
//!   - MCPWM_DB_INPUT_DB_RED  - Input signal is the output of Rising
//!                                Edge delay.
//!                               (Valid only for Falling Edge delay)
//!
//! \return None.
//
//*****************************************************************************
static inline void
MCPWM_setFallingEdgeDeadBandDelayInput(uint32_t base, uint16_t input)
{
    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));
    ASSERT((input == MCPWM_DB_INPUT_MCPWMA) ||
           (input == MCPWM_DB_INPUT_MCPWMB) ||
           (input == MCPWM_DB_INPUT_DB_RED));

    if(input == MCPWM_DB_INPUT_DB_RED)
    {
        //
        // Set the Falling Edge Delay input
        //
        HWREG(base + MCPWM_O_DBCTL) |= MCPWM_DBCTL_DEDB_MODE;
    }
    else
    {
        //
        // Set the Falling Edge Delay input
        //
        HWREG(base + MCPWM_O_DBCTL) &= ~MCPWM_DBCTL_DEDB_MODE;

        //
        // Set the Rising Edge Delay input
        //
        HWREG(base + MCPWM_O_DBCTL) =
            ((HWREG(base + MCPWM_O_DBCTL) & ~(1U << (MCPWM_DBCTL_IN_MODE_S + 1U))) |
            (input << (MCPWM_DBCTL_IN_MODE_S + 1U)));
    }
}

//*****************************************************************************
//
//! Set the RED (Rising Edge Delay) shadow load mode.
//!
//! \param base is the base address of the MCPWM module.
//! \param loadMode is the shadow to active load event.
//!
//! This function sets the Rising Edge Delay register shadow load mode.
//! Valid values for the \e loadMode parameter are:
//!     - MCPWM_RED_LOAD_ON_CNTR_ZERO        - load when counter equals zero.
//!     - MCPWM_RED_LOAD_ON_CNTR_PERIOD      - load when counter equals period.
//!     - MCPWM_RED_LOAD_ON_CNTR_ZERO_PERIOD - load when counter equals zero or
//!                                            period.
//!     - MCPWM_RED_LOAD_FREEZE              - Freeze shadow to active load.
//!
//! \return None.
//
//*****************************************************************************
static inline void
MCPWM_setRisingEdgeDelayCountShadowLoadMode(uint32_t base,
                                         MCPWM_RisingEdgeDelayLoadMode loadMode)
{
    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));

    //
    // Enable the shadow mode. Set-up the load mode
    //
    HWREG(base + MCPWM_O_DBCTL) = ((HWREG(base + MCPWM_O_DBCTL) & 
                            ~MCPWM_DBCTL_LOADREDMODE_M) |
                            ((uint32_t) loadMode << MCPWM_DBCTL_LOADREDMODE_S));

}

//*****************************************************************************
//
//! Set the FED (Falling Edge Delay) shadow load mode.
//!
//! \param base is the base address of the MCPWM module.
//! \param loadMode is the shadow to active load event.
//!
//! This function enables and sets the Falling Edge Delay register shadow load
//! mode. Valid values for the \e loadMode parameters are:
//!     - MCPWM_FED_LOAD_ON_CNTR_ZERO        - load when counter equals zero.
//!     - MCPWM_FED_LOAD_ON_CNTR_PERIOD      - load when counter equals period.
//!     - MCPWM_FED_LOAD_ON_CNTR_ZERO_PERIOD - load when counter equals zero or
//!                                            period.
//!     - MCPWM_FED_LOAD_FREEZE               - Freeze shadow to active load.
//!
//! \return None.
//
//*****************************************************************************
static inline void
MCPWM_setFallingEdgeDelayCountShadowLoadMode(uint32_t base,
                                        MCPWM_FallingEdgeDelayLoadMode loadMode)
{
    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));

    //
    // Enable the shadow mode. Setup the load mode.
    //
    HWREG(base + MCPWM_O_DBCTL) = ((HWREG(base + MCPWM_O_DBCTL) & 
                            ~MCPWM_DBCTL_LOADFEDMODE_M) |
                            ((uint32_t) loadMode << MCPWM_DBCTL_LOADFEDMODE_S));
}

//*****************************************************************************
//
//! Set MCPWM RED count
//!
//! \param base is the base address of the MCPWM module.
//! \param redCount is the RED(Rising Edge Delay) count.
//!
//! This function sets the RED (Rising Edge Delay) count value, in the active 
//! register.
//! The value of redCount should be less than 0x4000U.
//!
//! \return None.
//
//*****************************************************************************
static inline void
MCPWM_setRisingEdgeDelayCountActive(uint32_t base, uint16_t redCount)
{
    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));
    ASSERT(redCount <= MCPWM_DBRED_DBRED_M);

    //
    // Set the RED (Rising Edge Delay) count
    //
    HWREG(base + MCPWM_O_DBRED) = redCount;
}

//*****************************************************************************
//
//! Set MCPWM RED count in shadow register
//!
//! \param base is the base address of the MCPWM module.
//! \param redCount is the RED(Rising Edge Delay) count.
//!
//! This function sets the RED (Rising Edge Delay) count value, 
//! in the shadow register.
//! The value of redCount should be less than 0x4000U.
//!
//! \return None.
//
//*****************************************************************************
static inline void
MCPWM_setRisingEdgeDelayCountShadow(uint32_t base, uint16_t redCount)
{
    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));
    ASSERT(redCount <= MCPWM_DBREDS_DBREDS_M);

    //
    // Set the RED (Rising Edge Delay) count
    //
    HWREG(base + MCPWM_O_DBREDS) = redCount;
}

//*****************************************************************************
//
//! Set MCPWM FED count
//!
//! \param base is the base address of the MCPWM module.
//! \param fedCount is the FED(Falling Edge Delay) count.
//!
//! This function sets the FED (Falling Edge Delay) count value, in the active
//! register.
//! The value of fedCount should be less than 0x4000U.
//!
//! \return None.
//
//*****************************************************************************
static inline void
MCPWM_setFallingEdgeDelayCountActive(uint32_t base, uint16_t fedCount)
{
    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));
    ASSERT(fedCount < MCPWM_DBFED_DBFED_M);

    //
    // Set the RED (Rising Edge Delay) count
    //
    HWREG(base + MCPWM_O_DBFED) = fedCount;
}

//*****************************************************************************
//
//! Set MCPWM FED count in shadow register
//!
//! \param base is the base address of the MCPWM module.
//! \param fedCount is the FED(Falling Edge Delay) count.
//!
//! This function sets the FED (Falling Edge Delay) count value, 
//! in the shadow register.
//! The value of fedCount should be less than 0x4000U.
//!
//! \return None.
//
//*****************************************************************************
static inline void
MCPWM_setFallingEdgeDelayCountShadow(uint32_t base, uint16_t fedCount)
{
    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));
    ASSERT(fedCount < MCPWM_DBFEDS_DBFEDS_M);

    //
    // Set the RED (Rising Edge Delay) count
    //
    HWREG(base + MCPWM_O_DBFEDS) = fedCount;
}

//*****************************************************************************
//
//! Enables Trip Zone signal.
//!
//! \param base is the base address of the MCPWM module.
//! \param tzSignal is the Trip Zone signal.
//!
//! This function enables the Trip Zone signals specified by tzSignal as a
//! source for the Trip Zone module.
//! Valid values for tzSignal are:
//!   - MCPWM_TZ_SIGNAL_CBC1       - TZ1 Cycle By Cycle
//!   - MCPWM_TZ_SIGNAL_CBC2       - TZ2 Cycle By Cycle
//!   - MCPWM_TZ_SIGNAL_CBC3       - TZ3 Cycle By Cycle
//!   - MCPWM_TZ_SIGNAL_CBC4       - TZ4 Cycle By Cycle
//!   - MCPWM_TZ_SIGNAL_CBC5       - TZ5 Cycle By Cycle
//!   - MCPWM_TZ_SIGNAL_CBC6       - TZ6 Cycle By Cycle
//!   - MCPWM_TZ_SIGNAL_CBC7       - TZ7 Cycle By Cycle
//!   - MCPWM_TZ_SIGNAL_CBC8       - TZ8 Cycle By Cycle
//!   - MCPWM_TZ_SIGNAL_OSHT1      - One-shot TZ1
//!   - MCPWM_TZ_SIGNAL_OSHT2      - One-shot TZ2
//!   - MCPWM_TZ_SIGNAL_OSHT3      - One-shot TZ3
//!   - MCPWM_TZ_SIGNAL_OSHT4      - One-shot TZ4
//!   - MCPWM_TZ_SIGNAL_OSHT5      - One-shot TZ5
//!   - MCPWM_TZ_SIGNAL_OSHT6      - One-shot TZ6
//!   - MCPWM_TZ_SIGNAL_OSHT7      - One-shot TZ7
//!   - MCPWM_TZ_SIGNAL_OSHT8      - One-shot TZ8
//!
//! \b note:  A logical OR of the valid values can be passed as the tzSignal
//!           parameter.
//!
//! \return None.
//
//*****************************************************************************
static inline void
MCPWM_enableTripZoneSignals(uint32_t base, uint32_t tzSignal)
{
    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));

    //
    // Set the trip zone bits
    //
    EALLOW;
    HWREG(base + MCPWM_O_TZSEL) |= tzSignal;
    EDIS;
}

//*****************************************************************************
//
//! Disables Trip Zone signal.
//!
//! \param base is the base address of the MCPWM module.
//! \param tzSignal is the Trip Zone signal.
//!
//! This function disables the Trip Zone signals specified by tzSignal as a
//! source for the Trip Zone module.
//! Valid values for tzSignal are:
//!   - MCPWM_TZ_SIGNAL_CBC1       - TZ1 Cycle By Cycle
//!   - MCPWM_TZ_SIGNAL_CBC2       - TZ2 Cycle By Cycle
//!   - MCPWM_TZ_SIGNAL_CBC3       - TZ3 Cycle By Cycle
//!   - MCPWM_TZ_SIGNAL_CBC4       - TZ4 Cycle By Cycle
//!   - MCPWM_TZ_SIGNAL_CBC5       - TZ5 Cycle By Cycle
//!   - MCPWM_TZ_SIGNAL_CBC6       - TZ6 Cycle By Cycle
//!   - MCPWM_TZ_SIGNAL_CBC7       - TZ7 Cycle By Cycle
//!   - MCPWM_TZ_SIGNAL_CBC8       - TZ8 Cycle By Cycle
//!   - MCPWM_TZ_SIGNAL_OSHT1      - One-shot TZ1
//!   - MCPWM_TZ_SIGNAL_OSHT2      - One-shot TZ2
//!   - MCPWM_TZ_SIGNAL_OSHT3      - One-shot TZ3
//!   - MCPWM_TZ_SIGNAL_OSHT4      - One-shot TZ4
//!   - MCPWM_TZ_SIGNAL_OSHT5      - One-shot TZ5
//!   - MCPWM_TZ_SIGNAL_OSHT6      - One-shot TZ6
//!   - MCPWM_TZ_SIGNAL_OSHT7      - One-shot TZ7
//!   - MCPWM_TZ_SIGNAL_OSHT8      - One-shot TZ8
//!
//! \b note:  A logical OR of the valid values can be passed as the tzSignal
//!           parameter.
//!
//! \return None.
//
//*****************************************************************************
static inline void
MCPWM_disableTripZoneSignals(uint32_t base, uint32_t tzSignal)
{
    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));

    //
    // Set the trip zone bits
    //
    EALLOW;
    HWREG(base + MCPWM_O_TZSEL) &= ~((uint32_t)tzSignal);
    EDIS;
}

//*****************************************************************************
//
//! Set Trip Zone Action.
//!
//! \param base is the base address of the MCPWM module.
//! \param tzEvent is the Trip Zone event type.
//! \param tzAction is the Trip zone Action.
//!
//! This function sets the Trip Zone Action to be taken when a Trip Zone event
//! occurs.
//! Valid values for the parameters are:
//!  - tzEvent
//!      - MCPWM_TZ_ACTION_EVENT_TZB      - TZ1 - TZ8
//!      - MCPWM_TZ_ACTION_EVENT_TZA      - TZ1 - TZ8
//!  - tzAction
//!      - MCPWM_TZ_ACTION_HIGH_Z         - high impedance output
//!      - MCPWM_TZ_ACTION_HIGH           - high output
//!      - MCPWM_TZ_ACTION_LOW            - low low
//!      - MCPWM_TZ_ACTION_DISABLE        - disable action
//!
//! \note This function operates on both MCPWMxA and MCPWMxB depending on the
//!       tzEvent parameter.
//!
//! \return None.
//
//*****************************************************************************
static inline void
MCPWM_setTripZoneAction(uint32_t base, MCPWM_TripZoneEvent tzEvent,
                       MCPWM_TripZoneAction tzAction)
{   
    uint32_t mask = (tzEvent == MCPWM_TZ_ACTION_EVENT_TZA) ? MCPWM_TZCTL_TZA_M : MCPWM_TZCTL_TZB_M;
    uint32_t shift = (tzEvent == MCPWM_TZ_ACTION_EVENT_TZA) ? MCPWM_TZCTL_TZA_S : MCPWM_TZCTL_TZB_S;
    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));

    //
    // Set the Action for Trip Zone events
    //
    EALLOW;
    HWREG(base + MCPWM_O_TZCTL) = (HWREG(base + MCPWM_O_TZCTL) & 
                                    ~mask) | 
                                    ((uint32_t)tzAction << shift);
    EDIS;
}

//*****************************************************************************
//
//! Set the Trip Zone CBC pulse clear event.
//!
//! \param base is the base address of the MCPWM module.
//! \param clearEvent is the CBC trip zone clear event.
//!
//! This function set the event which automatically clears the
//! CBC (Cycle by Cycle) latch.
//! Valid values for clearEvent are:
//!   - MCPWM_TZ_CBC_PULSE_CLR_NONE              - Disable CBC pulse Clear
//!   - MCPWM_TZ_CBC_PULSE_CLR_CNTR_ZERO         - Clear CBC pulse when counter
//!                                                  equals zero
//!   - MCPWM_TZ_CBC_PULSE_CLR_CNTR_PERIOD       - Clear CBC pulse when counter
//!                                                  equals period
//!   - MCPWM_TZ_CBC_PULSE_CLR_CNTR_ZERO_PERIOD  - Clear CBC pulse when counter
//!                                                  equals zero or period
//!
//!  \return None.
//
//**************************************************************************
static inline void
MCPWM_selectTripZoneCBCEvent(uint32_t base,
                                 MCPWM_TripZoneCBCMode clearEvent)
{
    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));

    //
    // Select the Cycle by Cycle Clear mode
    //
    EALLOW;
    HWREG(base + MCPWM_O_TZCTL) = ((HWREG(base + MCPWM_O_TZCTL) & 
                                ~MCPWM_TZCTL_CBCPULSE_M) | 
                                ((uint32_t)clearEvent << MCPWM_TZCTL_CBCPULSE_S));
    EDIS;
}

//*****************************************************************************
//
//! Gets the Trip Zone flag status
//!
//! \param base is the base address of the MCPWM module.
//!
//! This function returns the specific Trip Zone flag status.
//!
//! \return The function returns the following values.
//!           - MCPWM_TZ_FLAG_CBC_TZ1     - CBC 1 status flag
//!           - MCPWM_TZ_FLAG_CBC_TZ2     - CBC 2 status flag
//!           - MCPWM_TZ_FLAG_CBC_TZ3     - CBC 3 status flag
//!           - MCPWM_TZ_FLAG_CBC_TZ4     - CBC 4 status flag
//!           - MCPWM_TZ_FLAG_CBC_TZ5     - CBC 5 status flag
//!           - MCPWM_TZ_FLAG_CBC_TZ6     - CBC 6 status flag
//!           - MCPWM_TZ_FLAG_CBC_TZ7     - CBC 7 status flag
//!           - MCPWM_TZ_FLAG_CBC_TZ8     - CBC 8 status flag
//!           - MCPWM_TZ_FLAG_OST_TZ1     - OST 1 status flag
//!           - MCPWM_TZ_FLAG_OST_TZ2     - OST 2 status flag
//!           - MCPWM_TZ_FLAG_OST_TZ3     - OST 3 status flag
//!           - MCPWM_TZ_FLAG_OST_TZ4     - OST 4 status flag
//!           - MCPWM_TZ_FLAG_OST_TZ5     - OST 5 status flag
//!           - MCPWM_TZ_FLAG_OST_TZ6     - OST 6 status flag
//!           - MCPWM_TZ_FLAG_OST_TZ7     - OST 7 status flag
//!           - MCPWM_TZ_FLAG_OST_TZ8     - OST 8 status flag
//!           - 
//
//***************************************************************************
static inline uint32_t
MCPWM_getTripZoneFlagStatus(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));

    uint32_t mask = MCPWM_TZSEL_CBC1 |
                    MCPWM_TZSEL_CBC2 |
                    MCPWM_TZSEL_CBC3 |
                    MCPWM_TZSEL_CBC4 |
                    MCPWM_TZSEL_CBC5 |
                    MCPWM_TZSEL_CBC6 |
                    MCPWM_TZSEL_CBC7 |
                    MCPWM_TZSEL_CBC8 |
                    MCPWM_TZSEL_OST1 |
                    MCPWM_TZSEL_OST2 |
                    MCPWM_TZSEL_OST3 |
                    MCPWM_TZSEL_OST4 |
                    MCPWM_TZSEL_OST5 |
                    MCPWM_TZSEL_OST6 |
                    MCPWM_TZSEL_OST7 |
                    MCPWM_TZSEL_OST8;

    //
    // Return the Trip zone flag status for One Shot and Cycle by Cycle flags
    //
    return(HWREG(base + MCPWM_O_TZCBCOSTFLAG) & mask);
}

//*****************************************************************************
//
//! Clear the Trip Zone flag.
//!
//! \param base is the base address of the MCPWM module.
//! \param tzFlags is the CBC flag to be cleared.
//!
//! \note This function only clears the TripZone flags. For OneShot Trips enabled,
//!       use MCPWM_clearInterrupt() API to clear the OneShot Trip.
//! 
//! This function clears the specific Cycle by Cycle Trip Zone flag.
//! The following are valid values for tzFlags.
//!           - MCPWM_TZ_FLAG_CBC_TZ1     - CBC 1 status flag
//!           - MCPWM_TZ_FLAG_CBC_TZ2     - CBC 2 status flag
//!           - MCPWM_TZ_FLAG_CBC_TZ3     - CBC 3 status flag
//!           - MCPWM_TZ_FLAG_CBC_TZ4     - CBC 4 status flag
//!           - MCPWM_TZ_FLAG_CBC_TZ5     - CBC 5 status flag
//!           - MCPWM_TZ_FLAG_CBC_TZ6     - CBC 6 status flag
//!           - MCPWM_TZ_FLAG_CBC_TZ7     - CBC 7 status flag
//!           - MCPWM_TZ_FLAG_CBC_TZ8     - CBC 8 status flag
//!           - MCPWM_TZ_FLAG_OST_TZ1     - OST 1 status flag
//!           - MCPWM_TZ_FLAG_OST_TZ2     - OST 2 status flag
//!           - MCPWM_TZ_FLAG_OST_TZ3     - OST 3 status flag
//!           - MCPWM_TZ_FLAG_OST_TZ4     - OST 4 status flag
//!           - MCPWM_TZ_FLAG_OST_TZ5     - OST 5 status flag
//!           - MCPWM_TZ_FLAG_OST_TZ6     - OST 6 status flag
//!           - MCPWM_TZ_FLAG_OST_TZ7     - OST 7 status flag
//!           - MCPWM_TZ_FLAG_OST_TZ8     - OST 8 status flag
//!           - MCPWM_TZ_FLAG_ALL         - All Trip Zone Flags
//!
//! \return None.
//
//***************************************************************************
static inline void
MCPWM_clearTripZoneFlagStatus(uint32_t base, uint32_t tzFlags)
{
    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));
    ASSERT((tzFlags & ~MCPWM_TZ_FLAG_ALL) == 0U);

    //
    // Clear the Cycle By Cycle Trip zone flag
    //
    EALLOW;
    HWREG(base + MCPWM_O_TZCBCOSTCLR) |= tzFlags;
    EDIS;
}

//*****************************************************************************
//
//! Enable ADC SOC event.
//!
//! \param base is the base address of the MCPWM module.
//! \param adcSOCType is the ADC SOC type.
//!
//! This function enables the MCPWM module to trigger an ADC SOC event.
//! Valid values for adcSOCType are:
//!   - MCPWM_SOC_A  - SOC A
//!   - MCPWM_SOC_B  - SOC B
//!   - MCPWM_SOC_C  - SOC C
//!   - MCPWM_SOC_D  - SOC D
//!
//! \return None.
//
//*****************************************************************************
static inline void
MCPWM_enableADCTrigger(uint32_t base, MCPWM_ADCStartOfConversionType adcSOCType)
{
    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));

    //
    // Enable an SOC
    //
    switch (adcSOCType)
    {
    case MCPWM_SOC_A:
        HWREG(base + MCPWM_O_SOCEN) |= MCPWM_SOCEN_SOCA_ENABLE;
        break;
    case MCPWM_SOC_B:
        HWREG(base + MCPWM_O_SOCEN) |= MCPWM_SOCEN_SOCB_ENABLE;
        break;
    case MCPWM_SOC_C:
        HWREG(base + MCPWM_O_SOCEN) |= MCPWM_SOCEN_SOCC_ENABLE;
        break;
    default:    // MCPWM_SOC_D
        HWREG(base + MCPWM_O_SOCEN) |= MCPWM_SOCEN_SOCD_ENABLE;
        break;
    }
}

//*****************************************************************************
//
//! Disable ADC SOC event.
//!
//! \param base is the base address of the MCPWM module.
//! \param adcSOCType is the ADC SOC type.
//!
//! This function disables the MCPWM module to trigger an ADC SOC event.
//! Valid values for adcSOCType are:
//!   - MCPWM_SOC_A  - SOC A
//!   - MCPWM_SOC_B  - SOC B
//!   - MCPWM_SOC_C  - SOC C
//!   - MCPWM_SOC_D  - SOC D
//!
//! \return None.
//
//*****************************************************************************
static inline void
MCPWM_disableADCTrigger(uint32_t base, MCPWM_ADCStartOfConversionType adcSOCType)
{
    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));

    //
    // Enable an SOC
    //
    switch (adcSOCType)
    {
    case MCPWM_SOC_A:
        HWREG(base + MCPWM_O_SOCEN) &= ~((uint32_t)MCPWM_SOCEN_SOCA_ENABLE);
        break;
    case MCPWM_SOC_B:
        HWREG(base + MCPWM_O_SOCEN) &= ~((uint32_t)MCPWM_SOCEN_SOCB_ENABLE);
        break;
    case MCPWM_SOC_C:
        HWREG(base + MCPWM_O_SOCEN) &= ~((uint32_t)MCPWM_SOCEN_SOCC_ENABLE);
        break;
    default:    // MCPWM_SOC_D
        HWREG(base + MCPWM_O_SOCEN) &= ~((uint32_t)MCPWM_SOCEN_SOCD_ENABLE);
        break;
    }
}

//*****************************************************************************
//
//! Sets the MCPWM SOC source.
//!
//! \param base is the base address of the MCPWM module.
//! \param adcSOCType is the ADC SOC type.
//! \param socSource is the SOC source.
//!
//! This function sets the MCPWM ADC SOC source.
//! Valid values for socSource are:
//!  - adcSOCType
//!     - MCPWM_SOC_A  - SOC A
//!     - MCPWM_SOC_B  - SOC B
//!     - MCPWM_SOC_C  - SOC C
//!     - MCPWM_SOC_D  - SOC D
//!  - socSource
//!     - MCPWM_SOC_DISABLED          Event is Disabled
//!     - MCPWM_SOC_TBCTR_ZERO        Time-base counter equal to zero
//!     - MCPWM_SOC_TBCTR_PERIOD      Time-base counter equal to period
//!     - MCPWM_SOC_TBCTR_ZERO_PERIOD Time-base counter equal to zero or period
//!     - MCPWM_SOC_TBCTR_U_CMPC      Time-base counter equal to CMPC when the timer is incrementing
//!     - MCPWM_SOC_TBCTR_U_CMPD      Time-base counter equal to CMPD when the timer is incrementing
//!     - MCPWM_SOC_TBCTR_U_CMP1A     Time-base counter equal to CMP1A when the timer is incrementing
//!     - MCPWM_SOC_TBCTR_U_CMP1B     Time-base counter equal to CMP1B when the timer is incrementing
//!     - MCPWM_SOC_TBCTR_U_CMP2A     Time-base counter equal to CMP2A when the timer is incrementing
//!     - MCPWM_SOC_TBCTR_U_CMP2B     Time-base counter equal to CMP2B when the timer is incrementing
//!     - MCPWM_SOC_TBCTR_U_CMP3A     Time-base counter equal to CMP3A when the timer is incrementing
//!     - MCPWM_SOC_TBCTR_U_CMP3B     Time-base counter equal to CMP3B when the timer is incrementing
//!     - MCPWM_SOC_TBCTR_D_CMPC      Time-base counter equal to CMPC when the timer is Decrementing
//!     - MCPWM_SOC_TBCTR_D_CMPD      Time-base counter equal to CMPD when the timer is Decrementing
//!     - MCPWM_SOC_TBCTR_D_CMP1A     Time-base counter equal to CMP1A when the timer is Decrementing
//!     - MCPWM_SOC_TBCTR_D_CMP1B     Time-base counter equal to CMP1B when the timer is Decrementing
//!     - MCPWM_SOC_TBCTR_D_CMP2A     Time-base counter equal to CMP2A when the timer is Decrementing
//!     - MCPWM_SOC_TBCTR_D_CMP2B     Time-base counter equal to CMP2B when the timer is Decrementing
//!     - MCPWM_SOC_TBCTR_D_CMP3A     Time-base counter equal to CMP3A when the timer is Decrementing
//!     - MCPWM_SOC_TBCTR_D_CMP3B     Time-base counter equal to CMP3B when the timer is Decrementing
//!
//! \return None.
//
//*****************************************************************************
static inline void
MCPWM_setADCTriggerSource(uint32_t base,
                         MCPWM_ADCStartOfConversionType adcSOCType,
                         MCPWM_ADCStartOfConversionSource socSource)
{
    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));

    //
    // Enable an SOC
    //
    switch (adcSOCType)
    {
    case MCPWM_SOC_A:
        HWREG(base + MCPWM_O_SOCSEL) = (HWREG(base + MCPWM_O_SOCSEL) & 
                            ~MCPWM_SOCSEL_SOCA_SEL_M) | ((uint32_t) socSource << MCPWM_SOCSEL_SOCA_SEL_S);
        break;
    case MCPWM_SOC_B:
        HWREG(base + MCPWM_O_SOCSEL) = (HWREG(base + MCPWM_O_SOCSEL) & 
                            ~MCPWM_SOCSEL_SOCB_SEL_M) | ((uint32_t) socSource << MCPWM_SOCSEL_SOCB_SEL_S);
        break;
    case MCPWM_SOC_C:
        HWREG(base + MCPWM_O_SOCSEL) = (HWREG(base + MCPWM_O_SOCSEL) & 
                            ~MCPWM_SOCSEL_SOCC_SEL_M) | ((uint32_t) socSource << MCPWM_SOCSEL_SOCC_SEL_S);
        break;
    default:    // MCPWM_SOC_D
        HWREG(base + MCPWM_O_SOCSEL) = (HWREG(base + MCPWM_O_SOCSEL) & 
                            ~MCPWM_SOCSEL_SOCD_SEL_M) | ((uint32_t) socSource << MCPWM_SOCSEL_SOCD_SEL_S);
        break;
    }
}

//*****************************************************************************
//
//! Sets the MCPWM SOC event counts.
//!
//! \param base is the base address of the MCPWM module.
//! \param adcSOCType is the ADC SOC type.
//! \param preScaleCount is the event count number.
//!
//! This function sets the SOC event count that determines the number of
//! events that have to occur before an SOC is issued.
//!  Valid values for the parameters are:
//!   - adcSOCType
//!     - MCPWM_SOC_A  - SOC A
//!     - MCPWM_SOC_B  - SOC B
//!     - MCPWM_SOC_C  - SOC C
//!     - MCPWM_SOC_D  - SOC D
//!   - preScaleCount
//!        - [1 - 7]  -  Generate SOC pulse every preScaleCount
//!                       up to 8 events.
//!
//! \note A preScaleCount value of 0 disables the prescale.
//!
//! \return None.
//
//*****************************************************************************
static inline void
MCPWM_setADCTriggerEventPrescale(uint32_t base,
                                MCPWM_ADCStartOfConversionType adcSOCType,
                                uint16_t preScaleCount)
{
    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));
    ASSERT(preScaleCount < 8U);

    //
    // Enable advanced feature of SOC every up to 7 events
    //
    switch (adcSOCType)
    {
    case MCPWM_SOC_A:
        HWREG(base + MCPWM_O_SOCPERIOD) = (HWREG(base + MCPWM_O_SOCPERIOD) & 
                            ~MCPWM_SOCPERIOD_SOCA_PERIOD_M) | ((uint32_t) preScaleCount << MCPWM_SOCPERIOD_SOCA_PERIOD_S);
        break;
    case MCPWM_SOC_B:
        HWREG(base + MCPWM_O_SOCPERIOD) = (HWREG(base + MCPWM_O_SOCPERIOD) & 
                            ~MCPWM_SOCPERIOD_SOCB_PERIOD_M) | ((uint32_t) preScaleCount << MCPWM_SOCPERIOD_SOCB_PERIOD_S);
        break;
    case MCPWM_SOC_C:
        HWREG(base + MCPWM_O_SOCPERIOD) = (HWREG(base + MCPWM_O_SOCPERIOD) & 
                            ~MCPWM_SOCPERIOD_SOCC_PERIOD_M) | ((uint32_t) preScaleCount << MCPWM_SOCPERIOD_SOCC_PERIOD_S);
        break;
    default:    // MCPWM_SOC_D
        HWREG(base + MCPWM_O_SOCPERIOD) = (HWREG(base + MCPWM_O_SOCPERIOD) & 
                            ~MCPWM_SOCPERIOD_SOCD_PERIOD_M) | ((uint32_t) preScaleCount << MCPWM_SOCPERIOD_SOCD_PERIOD_S);
        break;
    }
}

//*****************************************************************************
//
//! Get the SOC event count.
//!
//! \param base is the base address of the MCPWM module.
//! \param adcSOCType is the ADC SOC type.
//!
//! This function returns the MCPWM SOC event count.
//! Valid values for adcSOCType are:
//!     - MCPWM_SOC_A  - SOC A
//!     - MCPWM_SOC_B  - SOC B
//!     - MCPWM_SOC_C  - SOC C
//!     - MCPWM_SOC_D  - SOC D
//!
//! \return The SOC event counts that have occurred.
//
//*****************************************************************************
static inline uint16_t
MCPWM_getADCTriggerEventCount(uint32_t base,
                             MCPWM_ADCStartOfConversionType adcSOCType)
{

    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));
    uint16_t retValue = 0;
    //
    // Return the SOC event count
    //
    switch (adcSOCType)
    {
    case MCPWM_SOC_A:
        retValue = (uint16_t)((HWREG(base + MCPWM_O_SOCCNT) & MCPWM_SOCCNT_SOCA_CNT_M) >> MCPWM_SOCCNT_SOCA_CNT_S);
        break;
    case MCPWM_SOC_B:
        retValue = (uint16_t)((HWREG(base + MCPWM_O_SOCCNT) & MCPWM_SOCCNT_SOCB_CNT_M) >> MCPWM_SOCCNT_SOCB_CNT_S);
        break;
    case MCPWM_SOC_C:
        retValue = (uint16_t)((HWREG(base + MCPWM_O_SOCCNT) & MCPWM_SOCCNT_SOCC_CNT_M) >> MCPWM_SOCCNT_SOCC_CNT_S);
        break;
    default:    // MCPWM_SOC_D
        retValue = (uint16_t)((HWREG(base + MCPWM_O_SOCCNT) & MCPWM_SOCCNT_SOCD_CNT_M) >> MCPWM_SOCCNT_SOCD_CNT_S);
        break;
    }

    return retValue;
}

//*****************************************************************************
//
//! Return the SOC event status.
//!
//! \param base is the base address of the MCPWM module.
//! \param adcSOCType is the ADC SOC type.
//!
//! This function returns the MCPWM SOC status.
//! Valid values for adcSOCType are:
//!     - MCPWM_SOC_A  - SOC A
//!     - MCPWM_SOC_B  - SOC B
//!     - MCPWM_SOC_C  - SOC C
//!     - MCPWM_SOC_D  - SOC D
//!
//! \return Returns TRUE if the selected adcSOCType SOC was generated.
//!         Returns FALSE if the selected adcSOCType SOC was not generated.
//
//*****************************************************************************
static inline bool
MCPWM_getADCTriggerFlagStatus(uint32_t base,
                             MCPWM_ADCStartOfConversionType adcSOCType)
{
    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));
    bool retValue = FALSE;
    //
    // Return the SOC A/B/C/D status
    //
    switch (adcSOCType)
    {
    case MCPWM_SOC_A:
        retValue = (((HWREG(base + MCPWM_O_SOCFLAG) & MCPWM_SOCFLAG_SOCA) == MCPWM_SOCFLAG_SOCA) ? TRUE : FALSE);
        break;
    case MCPWM_SOC_B:
        retValue = (((HWREG(base + MCPWM_O_SOCFLAG) & MCPWM_SOCFLAG_SOCB) == MCPWM_SOCFLAG_SOCB) ? TRUE : FALSE);
        break;
    case MCPWM_SOC_C:
        retValue = (((HWREG(base + MCPWM_O_SOCFLAG) & MCPWM_SOCFLAG_SOCC) == MCPWM_SOCFLAG_SOCC) ? TRUE : FALSE);
        break;
    default:    // MCPWM_SOC_D
        retValue = (((HWREG(base + MCPWM_O_SOCFLAG) & MCPWM_SOCFLAG_SOCD) == MCPWM_SOCFLAG_SOCD) ? TRUE : FALSE);
        break;
    }

    return retValue;
}

//*****************************************************************************
//
//! Clear SOC flag.
//!
//! \param base is the base address of the MCPWM module.
//! \param adcSOCType is the ADC SOC type.
//!
//! This function clears the MCPWM SOC flag.
//! Valid values for adcSOCType are:
//!     - MCPWM_SOC_A  - SOC A
//!     - MCPWM_SOC_B  - SOC B
//!     - MCPWM_SOC_C  - SOC C
//!     - MCPWM_SOC_D  - SOC D
//!
//! \return None
//
//*****************************************************************************
static inline void
MCPWM_clearADCTriggerFlag(uint32_t base,
                         MCPWM_ADCStartOfConversionType adcSOCType)
{
    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));

    //
    // Clear SOC A/B/C/D bit of ETCLR register
    //
   switch (adcSOCType)
    {
    case MCPWM_SOC_A:
        HWREG(base + MCPWM_O_SOCCLR) |= MCPWM_SOCCLR_SOCA;
        break;
    case MCPWM_SOC_B:
        HWREG(base + MCPWM_O_SOCCLR) |= MCPWM_SOCCLR_SOCB;
        break;
    case MCPWM_SOC_C:
        HWREG(base + MCPWM_O_SOCCLR) |= MCPWM_SOCCLR_SOCC;
        break;
    default:    // MCPWM_SOC_D
        HWREG(base + MCPWM_O_SOCCLR) |= MCPWM_SOCCLR_SOCD;
        break;
    }
}

//*****************************************************************************
//
//! Sets the MCPWM Event Trigger source.
//!
//! \param base is the base address of the MCPWM module.
//! \param evtTrigType is the Event Trigger type.
//! \param evtTrigSource is the EVT source.
//!
//! This function sets the MCPWM Event Trigger source.
//! Valid values for evtSource are:
//!  - evtTrigType
//!     - MCPWM_ET_1  - EVT 1
//!     - MCPWM_ET_2  - EVT 2
//!  - evtTrigSource
//!     - MCPWM_EVT_DISABLED          Event is Disabled
//!     - MCPWM_EVT_TBCTR_ZERO        Time-base counter equal to zero
//!     - MCPWM_EVT_TBCTR_PERIOD      Time-base counter equal to period
//!     - MCPWM_EVT_TBCTR_ZERO_PERIOD Time-base counter equal to zero or period
//!     - MCPWM_EVT_TBCTR_U_CMPC      Time-base counter equal to CMPC when the timer is incrementing
//!     - MCPWM_EVT_TBCTR_U_CMPD      Time-base counter equal to CMPD when the timer is incrementing
//!     - MCPWM_EVT_TBCTR_U_CMP1A     Time-base counter equal to CMP1A when the timer is incrementing
//!     - MCPWM_EVT_TBCTR_U_CMP1B     Time-base counter equal to CMP1B when the timer is incrementing
//!     - MCPWM_EVT_TBCTR_U_CMP2A     Time-base counter equal to CMP2A when the timer is incrementing
//!     - MCPWM_EVT_TBCTR_U_CMP2B     Time-base counter equal to CMP2B when the timer is incrementing
//!     - MCPWM_EVT_TBCTR_U_CMP3A     Time-base counter equal to CMP3A when the timer is incrementing
//!     - MCPWM_EVT_TBCTR_U_CMP3B     Time-base counter equal to CMP3B when the timer is incrementing
//!     - MCPWM_EVT_TBCTR_D_CMPC      Time-base counter equal to CMPC when the timer is Decrementing
//!     - MCPWM_EVT_TBCTR_D_CMPD      Time-base counter equal to CMPD when the timer is Decrementing
//!     - MCPWM_EVT_TBCTR_D_CMP1A     Time-base counter equal to CMP1A when the timer is Decrementing
//!     - MCPWM_EVT_TBCTR_D_CMP1B     Time-base counter equal to CMP1B when the timer is Decrementing
//!     - MCPWM_EVT_TBCTR_D_CMP2A     Time-base counter equal to CMP2A when the timer is Decrementing
//!     - MCPWM_EVT_TBCTR_D_CMP2B     Time-base counter equal to CMP2B when the timer is Decrementing
//!     - MCPWM_EVT_TBCTR_D_CMP3A     Time-base counter equal to CMP3A when the timer is Decrementing
//!     - MCPWM_EVT_TBCTR_D_CMP3B     Time-base counter equal to CMP3B when the timer is Decrementing
//!
//! \return None.
//
//*****************************************************************************
static inline void
MCPWM_setEventTriggerSource(uint32_t base,
                         MCPWM_EventTriggerType evtTrigType,
                         MCPWM_EventTriggerSource evtTrigSource)
{
    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));

    //
    // Enable an event trigger source
    //
    switch (evtTrigType)
    {
    case MCPWM_ET_1:
        HWREG(base + MCPWM_O_ETSEL) = (HWREG(base + MCPWM_O_ETSEL) & 
                            ~MCPWM_ETSEL_ET1_SEL_M) | ((uint32_t) evtTrigSource << MCPWM_ETSEL_ET1_SEL_S);
        break;
    default:    // MCPWM_ET_2
        HWREG(base + MCPWM_O_ETSEL) = (HWREG(base + MCPWM_O_ETSEL) & 
                            ~MCPWM_ETSEL_ET2_SEL_M) | ((uint32_t) evtTrigSource << MCPWM_ETSEL_ET2_SEL_S);
        break;
    }
}

//*****************************************************************************
//
//! Sets the MCPWM Event Trigger event counts.
//!
//! \param base is the base address of the MCPWM module.
//! \param evtTrigType is the Event Trigger type.
//! \param preScaleCount is the event count number.
//!
//! This function sets the event trigger count that determines the number of
//! events that have to occur before an event trigger is issued.
//!  Valid values for the parameters are:
//!  - evtTrigType
//!     - MCPWM_ET_1  - EVT 1
//!     - MCPWM_ET_2  - EVT 2
//!   - preScaleCount
//!        - [1 - 7]  -  Generate Event Trigger pulse every preScaleCount
//!                       up to 8 events.
//!
//! \note A preScaleCount value of 0 disables the prescale.
//!
//! \return None.
//
//*****************************************************************************
static inline void
MCPWM_setEventTriggerEventPrescale(uint32_t base,
                                MCPWM_EventTriggerType evtTrigType,
                                uint16_t preScaleCount)
{
    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));
    ASSERT(preScaleCount < 8U);

    //
    // Enable advanced feature of Event trigger event every up to 7 events
    //
    switch (evtTrigType)
    {
    case MCPWM_ET_1:
        HWREG(base + MCPWM_O_ETPERIOD) = (HWREG(base + MCPWM_O_ETPERIOD) & 
                            ~MCPWM_ETPERIOD_ET1_PERIOD_M) | ((uint32_t) preScaleCount << MCPWM_ETPERIOD_ET1_PERIOD_S);
        break;
    default:    // MCPWM_ET_2
        HWREG(base + MCPWM_O_ETPERIOD) = (HWREG(base + MCPWM_O_ETPERIOD) & 
                            ~MCPWM_ETPERIOD_ET2_PERIOD_M) | ((uint32_t) preScaleCount << MCPWM_ETPERIOD_ET2_PERIOD_S);
        break;
    }
}

//*****************************************************************************
//
//! Get the Event Trigger event count.
//!
//! \param base is the base address of the MCPWM module.
//! \param evtTrigType is the Event Trigger type.
//!
//! This function returns the MCPWM Event trigger event count.
//! Valid values for evtTrigType are:
//!  - evtTrigType
//!     - MCPWM_ET_1  - EVT 1
//!     - MCPWM_ET_2  - EVT 2
//!
//! \return The Event Trigger event counts that have occurred.
//
//*****************************************************************************
static inline uint16_t
MCPWM_getEventTriggerEventCount(uint32_t base,
                             MCPWM_EventTriggerType evtTrigType)
{

    //
    // Check the arguments
    //
    ASSERT(MCPWM_isBaseValid(base));
    uint16_t retValue = 0;
    //
    // Return the Event Trigger event count
    //
    switch (evtTrigType)
    {
    case MCPWM_ET_1:
        retValue = (uint16_t)((HWREG(base + MCPWM_O_ETCNT) & MCPWM_ETCNT_ET1_CNT_M) >> MCPWM_ETCNT_ET1_CNT_S);
        break;
    default:    // MCPWM_ET_2
        retValue = (uint16_t)((HWREG(base + MCPWM_O_ETCNT) & MCPWM_ETCNT_ET2_CNT_M) >> MCPWM_ETCNT_ET2_CNT_S);
        break;
    }

    return retValue;
}

//*****************************************************************************
//
//! Enables interrupt source.
//!
//! \param base is the base address of the MCPWM module.
//! \param intFlags is the interrupt source to be enabled.
//!
//! This function sets and enables MCPWM interrupt source. The following are
//! valid interrupt sources.
//!  - MCPWM_INT_TZ_CBC - Interrupt Source is Trip Zone CBC signal
//!  - MCPWM_INT_TZ_OST - Interrupt Source is Trip Zone OST signal
//!  - MCPWM_INT_ET_1   - Interrupt Source is Event Trigger 1 signal
//!  - MCPWM_INT_ET_2   - Interrupt Source is Event Trigger 2 signal
//!  - MCPWM_INT_TBCTR_OVF - Counter overflow generates interrupt
//!  - MCPWM_INT_SOURCE_ALL - All Interrupt Sources
//!
//! \return None.
//
//*****************************************************************************
static inline void MCPWM_enableInterrupt(uint32_t base,
                                        uint16_t intFlags)
{
    ASSERT(MCPWM_isBaseValid(base));
    ASSERT((intFlags & ~(MCPWM_INT_SOURCE_ALL)) == 0U);

    //
    // Set bits in ECEINT register
    //
    EALLOW;
    HWREG(base + MCPWM_O_INTEN) |= intFlags;
    EDIS;
}

//*****************************************************************************
//
//! Disables interrupt source.
//!
//! \param base is the base address of the MCPWM module.
//! \param intFlags is the interrupt source to be disabled.
//!
//! This function clears and disables MCPWM interrupt source. The following are
//! valid interrupt sources.
//!  - MCPWM_INT_TZ_CBC   - Interrupt Source is Trip Zone CBC signal
//!  - MCPWM_INT_TZ_OST   - Interrupt Source is Trip Zone OST signal
//!  - MCPWM_INT_ET_1   - Interrupt Source is Event Trigger 1 signal
//!  - MCPWM_INT_ET_2   - Interrupt Source is Event Trigger 2 signal
//!  - MCPWM_INT_TBCTR_OVF  - Counter overflow generates interrupt
//!  - MCPWM_INT_SOURCE_ALL - All Interrupt Sources
//!
//! \return None.
//
//*****************************************************************************
static inline void MCPWM_disableInterrupt(uint32_t base,
                                         uint16_t intFlags)
{

    ASSERT(MCPWM_isBaseValid(base));
    ASSERT((intFlags & ~(MCPWM_INT_SOURCE_ALL)) == 0U);

    //
    // Clear bits in ECEINT register
    //
    EALLOW;
    HWREG(base + MCPWM_O_INTEN) &= ~intFlags;
    EDIS;
}

//*****************************************************************************
//
//! Returns the interrupt flag.
//!
//! \param base is the base address of the MCPWM module.
//!
//! This function returns the MCPWM interrupt flag. The following are valid
//! interrupt sources corresponding to the MCPWM interrupt flag.
//!
//! \return Returns the MCPWM interrupt that has occurred. The following are
//!  valid return values.
//!  - MCPWM_INT_TZ_CBC   - Interrupt Source is Trip Zone CBC signal
//!  - MCPWM_INT_TZ_OST   - Interrupt Source is Trip Zone OST signal
//!  - MCPWM_INT_ET_1     - Interrupt Source is Event Trigger 1 signal
//!  - MCPWM_INT_ET_2     - Interrupt Source is Event Trigger 2 signal
//!  - MCPWM_INT_TBCTR_OVF  - Counter overflow generates interrupt
//!  - MCPWM_INT_SOURCE_ALL - All Interrupt Sources
//!
//! \note - User can check if a combination of various interrupts have occurred
//!         by ORing the above return values.
//
//*****************************************************************************
static inline uint16_t MCPWM_getInterruptSource(uint32_t base)
{
    ASSERT(MCPWM_isBaseValid(base));

    //
    // Return contents of ECFLG register
    //
    return(HWREG(base + MCPWM_O_INTFLAG) & MCPWM_INT_SOURCE_ALL);
}

//*****************************************************************************
//
//! Returns the Global interrupt flag.
//!
//! \param base is the base address of the MCPWM module.
//!
//! This function returns the MCPWM Global interrupt flag.
//!
//! \return Returns TRUE if there is a global MCPWM interrupt, FALSE otherwise.
//
//*****************************************************************************
static inline bool MCPWM_getGlobalInterruptStatus(uint32_t base)
{
    ASSERT(MCPWM_isBaseValid(base));

    //
    // Return contents of Global interrupt bit
    //
    return((HWREG(base + MCPWM_O_INTFLAG) & MCPWM_INTFLAG_INT) == MCPWM_INTFLAG_INT);
}

//*****************************************************************************
//
//! Clears interrupt flag.
//!
//! \param base is the base address of the MCPWM module.
//! \param intFlags is the interrupt source.
//!
//! This function clears MCPWM interrupt flags. The following are valid
//! interrupt sources.
//!  - MCPWM_INT_TZ_CBC - Interrupt Source is Trip Zone CBC signal
//!  - MCPWM_INT_TZ_OST - Interrupt Source is Trip Zone OST signal
//!  - MCPWM_INT_ET_1   - Interrupt Source is Event Trigger 1 signal
//!  - MCPWM_INT_ET_2   - Interrupt Source is Event Trigger 2 signal
//!  - MCPWM_INT_TBCTR_OVF - Counter overflow generates interrupt
//!  - MCPWM_INT_SOURCE_ALL   - All Interrupt Sources- 
//!
//! \note MCPWM_INT_TZ_OST this flag has to be passed into the MCPWM_clearInterrupt
//! API for the Trip Zone One Shot to be cleared and the MCPWMs to return to 
//! normal state. 
//!
//! \return None.
//
//*****************************************************************************
static inline void MCPWM_clearInterrupt(uint32_t base,
                                       uint16_t intFlags)
{
    ASSERT(MCPWM_isBaseValid(base));
    ASSERT((intFlags & ~(MCPWM_INT_SOURCE_ALL)) == 0U);

    //
    // Write to ECCLR register
    //
    EALLOW;
    HWREGH(base + MCPWM_O_INTCLR) = intFlags;
    EDIS;
}

//*****************************************************************************
//
//! Clears global interrupt flag
//!
//! \param base is the base address of the MCPWM module.
//!
//! This function clears the global interrupt bit.
//!
//! \return None.
//
//*****************************************************************************
static inline void MCPWM_clearGlobalInterrupt(uint32_t base)
{
    ASSERT(MCPWM_isBaseValid(base));

    //
    // Write to INT bit
    //
    EALLOW;
    HWREG(base + MCPWM_O_INTCLR) = MCPWM_INTFLAG_INT;
    EDIS;
}

//*****************************************************************************
//
//! Forces interrupt source.
//!
//! \param base is the base address of the MCPWM module.
//! \param intFlags is the interrupt source.
//!
//! This function forces and enables MCPWM interrupt source. The following are
//! valid interrupt sources.
//!  - MCPWM_INT_TZ_CBC - Interrupt Source is Trip Zone CBC signal
//!  - MCPWM_INT_TZ_OST - Interrupt Source is Trip Zone OST signal
//!  - MCPWM_INT_ET_1   - Interrupt Source is Event Trigger 1 signal
//!  - MCPWM_INT_ET_2   - Interrupt Source is Event Trigger 2 signal
//!  - MCPWM_INT_TBCTR_OVF - Counter overflow generates interrupt
//!  - MCPWM_INT_SOURCE_ALL   - All Interrupt Sources- 
//!
//! \note MCPWM_INT_TZ_OST this flag can be passed into the MCPWM_forceInterrupt
//! API for the Trip Zone One Shot to be forced and the MCPWMs to be to set to 
//! tripped state, as configured in MCPWM_setTripZoneAction() API. 
//! \return None.
//
//*****************************************************************************
static inline void MCPWM_forceInterrupt(uint32_t base,
                                       uint16_t intFlags)
{
    ASSERT(MCPWM_isBaseValid(base));
    ASSERT((intFlags & ~(MCPWM_INT_SOURCE_ALL)) == 0U);


    //
    // Write to ECFRC register
    //
    EALLOW;
    HWREG(base + MCPWM_O_INTFRC) = intFlags;
    EDIS;
}
/* 
 DONE TILL HERE!!!
 */
//*****************************************************************************
//
//! Set emulation mode
//!
//! \param base is the base address of the MCPWM module.
//! \param emulationMode is the emulation mode.
//!
//! This function sets the emulation behaviours of the time base counter. Valid
//! values for emulationMode are:
//! - MCPWM_EMULATION_STOP_AFTER_NEXT_TB    - Stop after next Time Base counter
//!                                           increment or decrement.
//! - MCPWM_EMULATION_STOP_AFTER_FULL_CYCLE - Stop when counter completes whole
//!                                           cycle.
//! - MCPWM_EMULATION_FREE_RUN               - Free run.
//!
//! \return None.
//
//*****************************************************************************
extern void
MCPWM_setEmulationMode(uint32_t base, MCPWM_EmulationMode emulationMode);

//*****************************************************************************
//
//! Configures MCPWM signal with desired frequency & duty
//!
//! \param base is the base address of the MCPWM module.
//! \param signalParams is the desired signal parameters.
//!
//! This function configures the MCPWM module to generate a signal with
//! desired frequency & duty.
//!
//! \return None.
//
//*****************************************************************************
extern void
MCPWM_configureSignal(uint32_t base, const MCPWM_SignalParams *signalParams);


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

#endif // MCPWM_H
