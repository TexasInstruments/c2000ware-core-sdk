//###########################################################################
//
// FILE:   adc.h
//
// TITLE:  C28x ADC driver.
//
//###########################################################################
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
//###########################################################################

#ifndef ADC_H
#define ADC_H

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
//! \addtogroup adc_api ADC
//! @{
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_adc.h"
#include "inc/hw_asysctl.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "cpu.h"
#include "debug.h"
//*****************************************************************************
//
// Useful defines used within the driver functions. Not intended for use by
// application code.
//
//*****************************************************************************
#define ADC_NUM_INTERRUPTS          4U

#define ADC_SOCxCTL_OFFSET_BASE     ADC_O_SOC0CTL
#define ADC_RESULTx_OFFSET_BASE     ADC_O_RESULT0
#define ADC_INTSELxNy_OFFSET_BASE   ADC_O_INTSEL1N2
#define ADC_PPBxRESULT_OFFSET_BASE  ADC_O_PPB1RESULT

//*****************************************************************************
//
// Define to mask out the bits in the REPxCTL register that aren't associated
// with repeater configuration.
//
//*****************************************************************************
#define REPCTL_MASK                 (ADC_REP1CTL_MODE                        |\
                                     ADC_REP1CTL_TRIGGER_M                   |\
                                     ADC_REP1CTL_SYNCINSEL_M)

#define ADC_PPBxPSUM_OFFSET_BASE     ADC_O_PPB1PSUM
#define ADC_PPBxPCOUNT_OFFSET_BASE   ADC_O_PPBP1PCOUNT
#define ADC_PPBxPMAX_OFFSET_BASE     ADC_O_PPB1PMAX
#define ADC_PPBxPMIN_OFFSET_BASE     ADC_O_PPB1PMIN
#define ADC_PPBxPMAXI_OFFSET_BASE    ADC_O_PPB1PMAXI
#define ADC_PPBxPMINI_OFFSET_BASE    ADC_O_PPB1PMINI

#define ADC_PPBxLIMIT_OFFSET_BASE   ADC_O_PPB1LIMIT
#define ADC_PPBxSUM_OFFSET_BASE     ADC_O_PPB1SUM
#define ADC_PPBxCOUNT_OFFSET_BASE   ADC_O_PPB1COUNT
#define ADC_PPBxMAX_OFFSET_BASE     ADC_O_PPB1MAX
#define ADC_PPBxMIN_OFFSET_BASE     ADC_O_PPB1MIN
#define ADC_PPBxMAXI_OFFSET_BASE    ADC_O_PPB1MAXI
#define ADC_PPBxMINI_OFFSET_BASE    ADC_O_PPB1MINI

#define ADC_PPBxLIMIT_STEP          (ADC_O_PPB2LIMIT - ADC_O_PPB1LIMIT)
#define ADC_PPBxCONFIG2_STEP        (ADC_O_PPB2CONFIG2 - ADC_O_PPB1CONFIG2)
#define ADC_REPxCTL_STEP            (ADC_O_REP2CTL - ADC_O_REP1CTL)
#define ADC_REPxN_STEP              (ADC_O_REP2N - ADC_O_REP1N)
#define ADC_REPxPHASE_STEP          (ADC_O_REP2PHASE - ADC_O_REP1PHASE)
#define ADC_REPxSPREAD_STEP         (ADC_O_REP2SPREAD - ADC_O_REP1SPREAD)

#define ADC_PPBTRIP_MASK            (uint32_t)ADC_PPB1TRIPHI_LIMITHI_M
#define ADC_PPBxTRIPLO2_STEP        (ADC_O_PPB2TRIPLO2 - ADC_O_PPB1TRIPLO2)


#define ADC_PPBxCONFIG_STEP         (ADC_O_PPB2CONFIG - ADC_O_PPB1CONFIG)
#define ADC_PPBxTRIPHI_STEP         (ADC_O_PPB2TRIPHI - ADC_O_PPB1TRIPHI)
#define ADC_PPBxTRIPLO_STEP         (ADC_O_PPB2TRIPLO - ADC_O_PPB1TRIPLO)
#define ADC_PPBxSTAMP_STEP          (ADC_O_PPB2STAMP - ADC_O_PPB1STAMP)
#define ADC_PPBxOFFCAL_STEP         (ADC_O_PPB2OFFCAL - ADC_O_PPB1OFFCAL)
#define ADC_PPBxOFFREF_STEP         (ADC_O_PPB2OFFREF - ADC_O_PPB1OFFREF)

#define ADC_INT_REF_TSSLOPE         (*(int16_t *)((uintptr_t)0x720C0))
#define ADC_INT_REF_TSOFFSET        (*(int16_t *)((uintptr_t)0x720C1))
#define ADC_EXT_REF_TSSLOPE         (*(int16_t *)((uintptr_t)0x720BE))
#define ADC_EXT_REF_TSOFFSET        (*(int16_t *)((uintptr_t)0x720BF))

#ifndef DOXYGEN_PDF_IGNORE
//*****************************************************************************
//
// Values that can be passed to ADC_enablePPBEvent(), ADC_disablePPBEvent(),
// ADC_enablePPBEventInterrupt(), ADC_disablePPBEventInterrupt(), and
// ADC_clearPPBEventStatus() as the intFlags and evtFlags parameters. They also
// make up the enumerated bit field returned by ADC_getPPBEventStatus().
//
//*****************************************************************************
#define ADC_EVT_TRIPHI              0x0001U //!< Trip High Event
#define ADC_EVT_TRIPLO              0x0002U //!< Trip Low Event
#define ADC_EVT_ZERO                0x0004U //!< Zero Crossing Event
#endif

//*****************************************************************************
//
// Values that can be passed to ADC_forceMultipleSOC() as socMask parameter.
// These values can be OR'd together to trigger multiple SOCs at a time.
//
//*****************************************************************************
#define ADC_FORCE_SOC0              0x0001U //!< SW trigger ADC SOC 0
#define ADC_FORCE_SOC1              0x0002U //!< SW trigger ADC SOC 1
#define ADC_FORCE_SOC2              0x0004U //!< SW trigger ADC SOC 2
#define ADC_FORCE_SOC3              0x0008U //!< SW trigger ADC SOC 3
#define ADC_FORCE_SOC4              0x0010U //!< SW trigger ADC SOC 4
#define ADC_FORCE_SOC5              0x0020U //!< SW trigger ADC SOC 5
#define ADC_FORCE_SOC6              0x0040U //!< SW trigger ADC SOC 6
#define ADC_FORCE_SOC7              0x0080U //!< SW trigger ADC SOC 7
#define ADC_FORCE_SOC8              0x0100U //!< SW trigger ADC SOC 8
#define ADC_FORCE_SOC9              0x0200U //!< SW trigger ADC SOC 9
#define ADC_FORCE_SOC10             0x0400U //!< SW trigger ADC SOC 10
#define ADC_FORCE_SOC11             0x0800U //!< SW trigger ADC SOC 11
#define ADC_FORCE_SOC12             0x1000U //!< SW trigger ADC SOC 12
#define ADC_FORCE_SOC13             0x2000U //!< SW trigger ADC SOC 13
#define ADC_FORCE_SOC14             0x4000U //!< SW trigger ADC SOC 14
#define ADC_FORCE_SOC15             0x8000U //!< SW trigger ADC SOC 15

//*****************************************************************************
//
// Defines to specify ADC Trigger Repeater block status
//
//*****************************************************************************
#define ADC_REPEATER_MODULE_BUSY      ADC_REP1CTL_MODULEBUSY
#define ADC_REPEATER_PHASE_OVERFLOW   ADC_REP1CTL_PHASEOVF
#define ADC_REPEATER_TRIGGER_OVERFLOW ADC_REP1CTL_TRIGGEROVF

//*****************************************************************************
//
// Defines for the bit fields in the REPxCTL register
//
//*****************************************************************************
#define ADC_REP1CTL_ACTIVEMODE_S      1U
#define ADC_REP1CTL_MODULEBUSY_S      3U

//*****************************************************************************
//
// Define to mask out the bits in the REPSTATUS register that aren't
// associated with trigger repeater block status.
//
//*****************************************************************************
#define ADC_REPSTATUS_MASK          (ADC_REP1CTL_MODULEBUSY                  |\
                                     ADC_REP1CTL_PHASEOVF                    |\
                                     ADC_REP1CTL_TRIGGEROVF)

//*****************************************************************************
//
// Defines to specify ADC Safety Checker result status
//
//*****************************************************************************
#define ADC_SAFECHECK_RESULT1_READY ADC_CHECKSTATUS_RES1READY
#define ADC_SAFECHECK_RESULT2_READY ADC_CHECKSTATUS_RES2READY
#define ADC_SAFECHECK_RESULT_OOT    ADC_CHECKSTATUS_OOT

//*****************************************************************************
//
// Define to mask out the bits in the CHECKSTATUS register that aren't
// associated with safety checker result status.
//
//*****************************************************************************
#define ADC_SAFECHECK_STATUS_MASK   (ADC_SAFECHECK_RESULT1_READY             |\
                                     ADC_SAFECHECK_RESULT2_READY             |\
                                     ADC_SAFECHECK_RESULT_OOT)

//*****************************************************************************
//
//! Values that can be passed to ADC_setPrescaler() as the \e clkPrescale
//! parameter.
//
//*****************************************************************************
typedef enum
{
    ADC_CLK_DIV_1_0 = 0U,            //!< ADCCLK = (input clock) / 1.0
    ADC_CLK_DIV_2_0 = 2U,            //!< ADCCLK = (input clock) / 2.0
    ADC_CLK_DIV_2_5 = 3U,            //!< ADCCLK = (input clock) / 2.5
    ADC_CLK_DIV_3_0 = 4U,            //!< ADCCLK = (input clock) / 3.0
    ADC_CLK_DIV_3_5 = 5U,            //!< ADCCLK = (input clock) / 3.5
    ADC_CLK_DIV_4_0 = 6U,            //!< ADCCLK = (input clock) / 4.0
    ADC_CLK_DIV_4_5 = 7U,            //!< ADCCLK = (input clock) / 4.5
    ADC_CLK_DIV_5_0 = 8U,            //!< ADCCLK = (input clock) / 5.0
    ADC_CLK_DIV_5_5 = 9U,            //!< ADCCLK = (input clock) / 5.5
    ADC_CLK_DIV_6_0 = 10U,           //!< ADCCLK = (input clock) / 6.0
    ADC_CLK_DIV_6_5 = 11U,           //!< ADCCLK = (input clock) / 6.5
    ADC_CLK_DIV_7_0 = 12U,           //!< ADCCLK = (input clock) / 7.0
    ADC_CLK_DIV_7_5 = 13U,           //!< ADCCLK = (input clock) / 7.5
    ADC_CLK_DIV_8_0 = 14U,           //!< ADCCLK = (input clock) / 8.0
    ADC_CLK_DIV_8_5 = 15U            //!< ADCCLK = (input clock) / 8.5
} ADC_ClkPrescale;

//*****************************************************************************
//
//! Values that can be passed to ADC_setMode() as the \e resolution
//! parameter.
//
//*****************************************************************************
typedef enum
{
    ADC_RESOLUTION_12BIT = 0x00U,    //!< 12-bit conversion resolution
    ADC_RESOLUTION_16BIT = 0x40U     //!< 16-bit conversion resolution
} ADC_Resolution;

//*****************************************************************************
//
//! Values that can be passed to ADC_setMode() as the \e signalMode
//! parameter.
//
//*****************************************************************************
typedef enum
{
    ADC_MODE_SINGLE_ENDED = 0x00U,   //!< Sample on single pin with VREFLO
    ADC_MODE_DIFFERENTIAL = 0x80U    //!< Sample on pair of pins
} ADC_SignalMode;

//*****************************************************************************
//
//! Values that can be passed to ADC_setupSOC() as the \e trigger
//! parameter to specify the event that will trigger a conversion to start.
//! It is also used with ADC_setBurstModeConfig() and
//! ADC_triggerRepeaterSelect().
//
//*****************************************************************************
typedef enum
{
    ADC_TRIGGER_SW_ONLY     = 0U,     //!< Software only
    ADC_TRIGGER_CPU1_TINT0  = 1U,     //!< CPU1 Timer 0, TINT0
    ADC_TRIGGER_CPU1_TINT1  = 2U,     //!< CPU1 Timer 1, TINT1
    ADC_TRIGGER_CPU1_TINT2  = 3U,     //!< CPU1 Timer 2, TINT2
    ADC_TRIGGER_GPIO        = 4U,     //!< GPIO, ADCEXTSOC
    ADC_TRIGGER_EPWM1_SOCA  = 5U,     //!< ePWM1, ADCSOCA
    ADC_TRIGGER_EPWM1_SOCB  = 6U,     //!< ePWM1, ADCSOCB
    ADC_TRIGGER_EPWM2_SOCA  = 7U,     //!< ePWM2, ADCSOCA
    ADC_TRIGGER_EPWM2_SOCB  = 8U,     //!< ePWM2, ADCSOCB
    ADC_TRIGGER_EPWM3_SOCA  = 9U,     //!< ePWM3, ADCSOCA
    ADC_TRIGGER_EPWM3_SOCB  = 10U,    //!< ePWM3, ADCSOCB
    ADC_TRIGGER_EPWM4_SOCA  = 11U,    //!< ePWM4, ADCSOCA
    ADC_TRIGGER_EPWM4_SOCB  = 12U,    //!< ePWM4, ADCSOCB
    ADC_TRIGGER_EPWM5_SOCA  = 13U,    //!< ePWM5, ADCSOCA
    ADC_TRIGGER_EPWM5_SOCB  = 14U,    //!< ePWM5, ADCSOCB
    ADC_TRIGGER_EPWM6_SOCA  = 15U,    //!< ePWM6, ADCSOCA
    ADC_TRIGGER_EPWM6_SOCB  = 16U,    //!< ePWM6, ADCSOCB
    ADC_TRIGGER_EPWM7_SOCA  = 17U,    //!< ePWM7, ADCSOCA
    ADC_TRIGGER_EPWM7_SOCB  = 18U,    //!< ePWM7, ADCSOCB
    ADC_TRIGGER_EPWM8_SOCA  = 19U,    //!< ePWM8, ADCSOCA
    ADC_TRIGGER_EPWM8_SOCB  = 20U,    //!< ePWM8, ADCSOCB
    ADC_TRIGGER_EPWM9_SOCA  = 21U,    //!< ePWM9, ADCSOCA
    ADC_TRIGGER_EPWM9_SOCB  = 22U,    //!< ePWM9, ADCSOCB
    ADC_TRIGGER_EPWM10_SOCA = 23U,    //!< ePWM10, ADCSOCA
    ADC_TRIGGER_EPWM10_SOCB = 24U,    //!< ePWM10, ADCSOCB
    ADC_TRIGGER_EPWM11_SOCA = 25U,    //!< ePWM11, ADCSOCA
    ADC_TRIGGER_EPWM11_SOCB = 26U,    //!< ePWM11, ADCSOCB
    ADC_TRIGGER_EPWM12_SOCA = 27U,    //!< ePWM12, ADCSOCA
    ADC_TRIGGER_EPWM12_SOCB = 28U,    //!< ePWM12, ADCSOCB
    ADC_TRIGGER_CPU2_TINT0  = 29U,    //!< CPU2 Timer 0, TINT0
    ADC_TRIGGER_CPU2_TINT1  = 30U,    //!< CPU2 Timer 1, TINT1
    ADC_TRIGGER_CPU2_TINT2  = 31U,    //!< CPU2 Timer 2, TINT2
    ADC_TRIGGER_REPEATER1   = 40U,    //!< Repeater 1
    ADC_TRIGGER_REPEATER2   = 41U,    //!< Repeater 2
    ADC_TRIGGER_ECAP1       = 80U,    //!< eCAP1
    ADC_TRIGGER_ECAP2       = 81U,    //!< eCAP2
    ADC_TRIGGER_ECAP3       = 82U,    //!< eCAP3
    ADC_TRIGGER_ECAP4       = 83U,    //!< eCAP4
    ADC_TRIGGER_ECAP5       = 84U,    //!< eCAP5
    ADC_TRIGGER_ECAP6       = 85U,    //!< eCAP6
    ADC_TRIGGER_ECAP7       = 86U,    //!< eCAP7
    ADC_TRIGGER_EPWM13_SOCA = 88U,    //!< ePWM13, ADCSOCA
    ADC_TRIGGER_EPWM13_SOCB = 89U,    //!< ePWM13, ADCSOCB
    ADC_TRIGGER_EPWM14_SOCA = 90U,    //!< ePWM14, ADCSOCA
    ADC_TRIGGER_EPWM14_SOCB = 91U,    //!< ePWM14, ADCSOCB
    ADC_TRIGGER_EPWM15_SOCA = 92U,    //!< ePWM15, ADCSOCA
    ADC_TRIGGER_EPWM15_SOCB = 93U,    //!< ePWM15, ADCSOCB
    ADC_TRIGGER_EPWM16_SOCA = 94U,    //!< ePWM16, ADCSOCA
    ADC_TRIGGER_EPWM16_SOCB = 95U,    //!< ePWM16, ADCSOCB
    ADC_TRIGGER_EPWM17_SOCA = 96U,    //!< ePWM17, ADCSOCA
    ADC_TRIGGER_EPWM17_SOCB = 97U,    //!< ePWM17, ADCSOCB
    ADC_TRIGGER_EPWM18_SOCA = 98U,    //!< ePWM18, ADCSOCA
    ADC_TRIGGER_EPWM18_SOCB = 99U     //!< ePWM18, ADCSOCB
} ADC_Trigger;

//*****************************************************************************
//
//! Values that can be passed to ADC_setupSOC() as the \e channel
//! parameter. This is the input pin on which the signal to be converted is
//! located.
//
//*****************************************************************************
typedef enum
{
    ADC_CH_ADCIN0  = 0U,          //!< single-ended, ADCIN0
    ADC_CH_ADCIN1  = 1U,          //!< single-ended, ADCIN1
    ADC_CH_ADCIN2  = 2U,          //!< single-ended, ADCIN2
    ADC_CH_ADCIN3  = 3U,          //!< single-ended, ADCIN3
    ADC_CH_ADCIN4  = 4U,          //!< single-ended, ADCIN4
    ADC_CH_ADCIN5  = 5U,          //!< single-ended, ADCIN5
    ADC_CH_ADCIN6  = 6U,          //!< single-ended, ADCIN6
    ADC_CH_ADCIN7  = 7U,          //!< single-ended, ADCIN7
    ADC_CH_ADCIN8  = 8U,          //!< single-ended, ADCIN8
    ADC_CH_ADCIN9  = 9U,          //!< single-ended, ADCIN9
    ADC_CH_ADCIN10 = 10U,         //!< single-ended, ADCIN10
    ADC_CH_ADCIN11 = 11U,         //!< single-ended, ADCIN11
    ADC_CH_ADCIN12 = 12U,         //!< single-ended, ADCIN12
    ADC_CH_ADCIN13 = 13U,         //!< single-ended, ADCIN13
    ADC_CH_ADCIN14 = 14U,         //!< single-ended, ADCIN14
    ADC_CH_ADCIN15 = 15U,         //!< single-ended, ADCIN15
    ADC_CH_ADCIN16 = 16U,         //!< single-ended, ADCIN16
    ADC_CH_ADCIN17 = 17U,         //!< single-ended, ADCIN17
    ADC_CH_ADCIN18 = 18U,         //!< single-ended, ADCIN18
    ADC_CH_ADCIN19 = 19U,         //!< single-ended, ADCIN19
    ADC_CH_ADCIN20 = 20U,         //!< single-ended, ADCIN20
    ADC_CH_ADCIN21 = 21U,         //!< single-ended, ADCIN21
    ADC_CH_ADCIN22 = 22U,         //!< single-ended, ADCIN22
    ADC_CH_ADCIN23 = 23U,         //!< single-ended, ADCIN23
    ADC_CH_ADCIN24 = 24U,         //!< single-ended, ADCIN24
    ADC_CH_ADCIN25 = 25U,         //!< single-ended, ADCIN25
    ADC_CH_ADCIN26 = 26U,         //!< single-ended, ADCIN26
    ADC_CH_ADCIN27 = 27U,         //!< single-ended, ADCIN27
    ADC_CH_ADCIN28 = 28U,         //!< single-ended, ADCIN28
    ADC_CH_ADCIN29 = 29U,         //!< single-ended, ADCIN29
    ADC_CH_ADCIN30 = 30U,         //!< single-ended, ADCIN30
    ADC_CH_ADCIN31 = 31U,         //!< single-ended, ADCIN31
    ADC_CH_ADCIN0_ADCIN1   = 0U,  //!< differential, ADCIN0 and ADCIN1
    ADC_CH_ADCIN2_ADCIN3   = 2U,  //!< differential, ADCIN2 and ADCIN3
    ADC_CH_ADCIN4_ADCIN5   = 4U,  //!< differential, ADCIN4 and ADCIN5
    ADC_CH_ADCIN6_ADCIN7   = 6U,  //!< differential, ADCIN6 and ADCIN7
    ADC_CH_ADCIN8_ADCIN9   = 8U,  //!< differential, ADCIN8 and ADCIN9
    ADC_CH_ADCIN10_ADCIN11 = 10U, //!< differential, ADCIN10 and ADCIN11
    ADC_CH_ADCIN12_ADCIN13 = 12U, //!< differential, ADCIN12 and ADCIN13
    ADC_CH_ADCIN14_ADCIN15 = 14U, //!< differential, ADCIN14 and ADCIN15
    ADC_CH_ADCIN16_ADCIN17 = 16U, //!< differential, ADCIN16 and ADCIN17
    ADC_CH_ADCIN18_ADCIN19 = 18U, //!< differential, ADCIN18 and ADCIN19
    ADC_CH_ADCIN20_ADCIN21 = 20U, //!< differential, ADCIN20 and ADCIN21
    ADC_CH_ADCIN22_ADCIN23 = 22U, //!< differential, ADCIN22 and ADCIN23
    ADC_CH_ADCIN24_ADCIN25 = 24U, //!< differential, ADCIN24 and ADCIN25
    ADC_CH_ADCIN26_ADCIN27 = 26U, //!< differential, ADCIN26 and ADCIN27
    ADC_CH_ADCIN28_ADCIN29 = 28U, //!< differential, ADCIN28 and ADCIN29
    ADC_CH_ADCIN30_ADCIN31 = 30U  //!< differential, ADCIN30 and ADCIN31
} ADC_Channel;

//*****************************************************************************
//
//! Values that can be passed to ADC_setInterruptPulseMode() as the
//! \e pulseMode parameter.
//
//*****************************************************************************
typedef enum
{
    //! Occurs at the end of the acquisition window
    ADC_PULSE_END_OF_ACQ_WIN = 0x00U,
    //! Occurs at the end of the conversion
    ADC_PULSE_END_OF_CONV    = 0x04U
} ADC_PulseMode;

//*****************************************************************************
//
//! Values that can be passed to ADC_enableInterrupt(), ADC_disableInterrupt(),
//! and ADC_getInterruptStatus() as the \e adcIntNum parameter.
//
//*****************************************************************************
typedef enum
{
    ADC_INT_NUMBER1 = 0U,        //!< ADCINT1 Interrupt
    ADC_INT_NUMBER2 = 1U,        //!< ADCINT2 Interrupt
    ADC_INT_NUMBER3 = 2U,        //!< ADCINT3 Interrupt
    ADC_INT_NUMBER4 = 3U         //!< ADCINT4 Interrupt
} ADC_IntNumber;

//*****************************************************************************
//
//! Values that can be passed in as the \e ppbNumber parameter for several
//! functions.
//
//*****************************************************************************
typedef enum
{
    ADC_PPB_NUMBER1 = 0U,        //!< Post-processing block 1
    ADC_PPB_NUMBER2 = 1U,        //!< Post-processing block 2
    ADC_PPB_NUMBER3 = 2U,        //!< Post-processing block 3
    ADC_PPB_NUMBER4 = 3U         //!< Post-processing block 4
} ADC_PPBNumber;

//*****************************************************************************
//
//! Values that can be passed in as the \e socNumber parameter for several
//! functions. This value identifies the start-of-conversion (SOC) that a
//! function is configuring or accessing. Note that in some cases (for example,
//! ADC_setInterruptSource()) \e socNumber is used to refer to the
//! corresponding end-of-conversion (EOC).
//
//*****************************************************************************
typedef enum
{
    ADC_SOC_NUMBER0  = 0U,        //!< SOC/EOC number 0
    ADC_SOC_NUMBER1  = 1U,        //!< SOC/EOC number 1
    ADC_SOC_NUMBER2  = 2U,        //!< SOC/EOC number 2
    ADC_SOC_NUMBER3  = 3U,        //!< SOC/EOC number 3
    ADC_SOC_NUMBER4  = 4U,        //!< SOC/EOC number 4
    ADC_SOC_NUMBER5  = 5U,        //!< SOC/EOC number 5
    ADC_SOC_NUMBER6  = 6U,        //!< SOC/EOC number 6
    ADC_SOC_NUMBER7  = 7U,        //!< SOC/EOC number 7
    ADC_SOC_NUMBER8  = 8U,        //!< SOC/EOC number 8
    ADC_SOC_NUMBER9  = 9U,        //!< SOC/EOC number 9
    ADC_SOC_NUMBER10 = 10U,       //!< SOC/EOC number 10
    ADC_SOC_NUMBER11 = 11U,       //!< SOC/EOC number 11
    ADC_SOC_NUMBER12 = 12U,       //!< SOC/EOC number 12
    ADC_SOC_NUMBER13 = 13U,       //!< SOC/EOC number 13
    ADC_SOC_NUMBER14 = 14U,       //!< SOC/EOC number 14
    ADC_SOC_NUMBER15 = 15U        //!< SOC/EOC number 15
} ADC_SOCNumber;

//*****************************************************************************
//
//! Values that can be passed in as the \e trigger parameter for the
//! ADC_setInterruptSOCTrigger() function.
//
//*****************************************************************************
typedef enum
{
    ADC_INT_SOC_TRIGGER_NONE    = 0U,   //!< No ADCINT will trigger the SOC
    ADC_INT_SOC_TRIGGER_ADCINT1 = 1U,   //!< ADCINT1 will trigger the SOC
    ADC_INT_SOC_TRIGGER_ADCINT2 = 2U    //!< ADCINT2 will trigger the SOC
} ADC_IntSOCTrigger;

//*****************************************************************************
//
//! Values that can be passed to ADC_setSOCPriority() as the \e priMode
//! parameter.
//
//*****************************************************************************
typedef enum
{
    ADC_PRI_ALL_ROUND_ROBIN = 0U,    //!< Round robin mode is used for all
    ADC_PRI_SOC0_HIPRI      = 1U,    //!< SOC 0 hi pri, others in round robin
    ADC_PRI_THRU_SOC1_HIPRI = 2U,    //!< SOC 0-1 hi pri, others in round robin
    ADC_PRI_THRU_SOC2_HIPRI = 3U,    //!< SOC 0-2 hi pri, others in round robin
    ADC_PRI_THRU_SOC3_HIPRI = 4U,    //!< SOC 0-3 hi pri, others in round robin
    ADC_PRI_THRU_SOC4_HIPRI = 5U,    //!< SOC 0-4 hi pri, others in round robin
    ADC_PRI_THRU_SOC5_HIPRI = 6U,    //!< SOC 0-5 hi pri, others in round robin
    ADC_PRI_THRU_SOC6_HIPRI = 7U,    //!< SOC 0-6 hi pri, others in round robin
    ADC_PRI_THRU_SOC7_HIPRI = 8U,    //!< SOC 0-7 hi pri, others in round robin
    ADC_PRI_THRU_SOC8_HIPRI = 9U,    //!< SOC 0-8 hi pri, others in round robin
    ADC_PRI_THRU_SOC9_HIPRI = 10U,   //!< SOC 0-9 hi pri, others in round robin
    ADC_PRI_THRU_SOC10_HIPRI = 11U,  //!< SOC 0-10 hi pri, others in round robin
    ADC_PRI_THRU_SOC11_HIPRI = 12U,  //!< SOC 0-11 hi pri, others in round robin
    ADC_PRI_THRU_SOC12_HIPRI = 13U,  //!< SOC 0-12 hi pri, others in round robin
    ADC_PRI_THRU_SOC13_HIPRI = 14U,  //!< SOC 0-13 hi pri, others in round robin
    ADC_PRI_THRU_SOC14_HIPRI = 15U,  //!< SOC 0-14 hi pri, SOC15 in round robin
    ADC_PRI_ALL_HIPRI = 16U          //!< All priorities based on SOC number
} ADC_PriorityMode;

//*****************************************************************************
//
//! Values that can be passed to ADC_getTemperatureC(), ADC_getTemperatureK(),
//! ADC_setVREF() and ADC_setOffsetTrimAll() as the \e refMode parameter.
//
//*****************************************************************************
typedef enum
{
    ADC_REFERENCE_INTERNAL = 0U,
    ADC_REFERENCE_EXTERNAL = 1U
} ADC_ReferenceMode;

//*****************************************************************************
//
//! Values that can be passed to ADC_setVREF() and ADC_setOffsetTrimAll() as the
//! \e refVoltage parameter.
//!
//
//*****************************************************************************
typedef enum
{
    ADC_REFERENCE_3_3V = 0U,
    ADC_REFERENCE_2_5V = 1U
} ADC_ReferenceVoltage;

//*****************************************************************************
//
//! Values that can be passed to ADC_configOSDetectMode() as the \e modeVal
//! parameter.
//
//*****************************************************************************
typedef enum
{
    ADC_OSDETECT_MODE_DISABLED            = 0x0U,//!< Open/Shorts detection cir-
                                                 //!< cuit(O/S DC) is disabled
    ADC_OSDETECT_MODE_VSSA                = 0x1U,//!< O/S DC is enabled at zero
                                                 //!< scale
    ADC_OSDETECT_MODE_VDDA                = 0x2U,//!< O/S DC is enabled at full
                                                 //!< scale
    ADC_OSDETECT_MODE_5BY12_VDDA          = 0x3U,//!< O/S DC is enabled at 5/12
                                                 //!< scale
    ADC_OSDETECT_MODE_7BY12_VDDA          = 0x4U,//!< O/S DC is enabled at 7/12
                                                 //!< scale
    ADC_OSDETECT_MODE_5K_PULLDOWN_TO_VSSA = 0x5U,//!< O/S DC is enabled at 5K
                                                 //!< pulldown to VSSA
    ADC_OSDETECT_MODE_5K_PULLUP_TO_VDDA   = 0x6U,//!< O/S DC is enabled at 5K
                                                 //!< pullup to VDDA
    ADC_OSDETECT_MODE_7K_PULLDOWN_TO_VSSA = 0x7U //!< O/S DC is enabled at 7K
                                                 //!< pulldown to VSSA
} ADC_OSDetectMode;

//*****************************************************************************
//
//! Values that can be passed to ADC_selectOffsetTrimMode() as the
//! \e mode parameter.
//
//*****************************************************************************
typedef enum
{
    ADC_OFFSET_TRIM_COMMON     = 0x0000U, //!< Common Trim register for all
                                          //!< ADC modes
    ADC_OFFSET_TRIM_INDIVIDUAL = 0x0100U  //!< Individual Trim registers for
                                          //!< different ADC modes
} ADC_OffsetTrim;

//*****************************************************************************
//
//! Values that can be passed to ADC_setupSOCRefloChannel() as the
//! \e channelType parameter.
//
//*****************************************************************************
typedef enum
{
    ADC_CHANNEL_ODD     = 0U, //!< ADC Odd Channel
    ADC_CHANNEL_EVEN    = 1U  //!< ADC Even Channel
} ADC_ChannelType;

//*****************************************************************************
//
//! Values that can be passed to ADC_selectPPBSyncInput() and
//! ADC_triggerRepeaterSyncIn() as the \e syncInput parameter.
//
//*****************************************************************************
typedef enum
{
    ADC_SYNCIN_DISABLE          = 0x00U,  //!< ADC Syncin is disabled
    ADC_SYNCIN_EPWM1SYNCOUT     = 0x01U,  //!< ADC Syncin is EPWM1SYNCOUT
    ADC_SYNCIN_EPWM2SYNCOUT     = 0x02U,  //!< ADC Syncin is EPWM2SYNCOUT
    ADC_SYNCIN_EPWM3SYNCOUT     = 0x03U,  //!< ADC Syncin is EPWM3SYNCOUT
    ADC_SYNCIN_EPWM4SYNCOUT     = 0x04U,  //!< ADC Syncin is EPWM4SYNCOUT
    ADC_SYNCIN_EPWM5SYNCOUT     = 0x05U,  //!< ADC Syncin is EPWM5SYNCOUT
    ADC_SYNCIN_EPWM6SYNCOUT     = 0x06U,  //!< ADC Syncin is EPWM6SYNCOUT
    ADC_SYNCIN_EPWM7SYNCOUT     = 0x07U,  //!< ADC Syncin is EPWM7SYNCOUT
    ADC_SYNCIN_EPWM8SYNCOUT     = 0x08U,  //!< ADC Syncin is EPWM8SYNCOUT
    ADC_SYNCIN_EPWM9SYNCOUT     = 0x09U,  //!< ADC Syncin is EPWM9SYNCOUT
    ADC_SYNCIN_EPWM10SYNCOUT    = 0x0AU,  //!< ADC Syncin is EPWM10SYNCOUT
    ADC_SYNCIN_EPWM11SYNCOUT    = 0x0BU,  //!< ADC Syncin is EPWM11SYNCOUT
    ADC_SYNCIN_EPWM12SYNCOUT    = 0x0CU,  //!< ADC Syncin is EPWM12SYNCOUT
    ADC_SYNCIN_EPWM13SYNCOUT    = 0x0DU,  //!< ADC Syncin is EPWM13SYNCOUT
    ADC_SYNCIN_EPWM14SYNCOUT    = 0x0EU,  //!< ADC Syncin is EPWM14SYNCOUT
    ADC_SYNCIN_EPWM15SYNCOUT    = 0x0FU,  //!< ADC Syncin is EPWM15SYNCOUT
    ADC_SYNCIN_EPWM16SYNCOUT    = 0x10U,  //!< ADC Syncin is EPWM16SYNCOUT
    ADC_SYNCIN_EPWM17SYNCOUT    = 0x11U,  //!< ADC Syncin is EPWM17SYNCOUT
    ADC_SYNCIN_EPWM18SYNCOUT    = 0x12U,  //!< ADC Syncin is EPWM18SYNCOUT
    ADC_SYNCIN_ECAP1YNCOUT      = 0x13U,  //!< ADC Syncin is ECAP1YNCOUT
    ADC_SYNCIN_ECAP2SYNCOUT     = 0x14U,  //!< ADC Syncin is ECAP2SYNCOUT
    ADC_SYNCIN_ECAP3SYNCOUT     = 0x15U,  //!< ADC Syncin is ECAP3SYNCOUT
    ADC_SYNCIN_ECAP4SYNCOUT     = 0x16U,  //!< ADC Syncin is ECAP4SYNCOUT
    ADC_SYNCIN_ECAP5SYNCOUT     = 0x17U,  //!< ADC Syncin is ECAP5SYNCOUT
    ADC_SYNCIN_ECAP6SYNCOUT     = 0x18U,  //!< ADC Syncin is ECAP6SYNCOUT
    ADC_SYNCIN_ECAP7SYNCOUT     = 0x19U,  //!< ADC Syncin is ECAP7SYNCOUT
    ADC_SYNCIN_INPUTXBAROUTPUT5 = 0x1AU,  //!< ADC Syncin is INPUTXBAROUTPUT5
    ADC_SYNCIN_INPUTXBAROUTPUT6 = 0x1BU,  //!< ADC Syncin is INPUTXBAROUTPUT6
    ADC_SYNCIN_EtherCATSYNC0    = 0x1CU,  //!< ADC Syncin is EtherCATSYNC0
    ADC_SYNCIN_EtherCATSYNC1    = 0x1DU   //!< ADC Syncin is EtherCATSYNC1
} ADC_SyncInput;

//*****************************************************************************
//
//! Values that can be passed to ADC_selectPPBOSINTSource() as the \e osIntSrc
//! parameter.
//
//*****************************************************************************
typedef enum
{
    ADC_PPB_OS_INT_1 = 0x0U,          //!< PCount generates PPB interrupt
    ADC_PPB_OS_INT_2 = 0x1U,          //!< PCount/Sync generates PPB interrupt
} ADC_PPBIntSrcSelect;

//*****************************************************************************
//
//! Values that can be passed to ADC_selectSOCExtChannel() as the \e extChannel
//! parameter.
//
//*****************************************************************************
typedef enum
{
    ADC_CH_ADCINX_0  = 0x0U,          //!< ADCINX.0 is converted
    ADC_CH_ADCINX_1  = 0x1U,          //!< ADCINX.1 is converted
    ADC_CH_ADCINX_2  = 0x2U,          //!< ADCINX.2 is converted
    ADC_CH_ADCINX_3  = 0x3U,          //!< ADCINX.3 is converted
    ADC_CH_ADCINX_4  = 0x4U,          //!< ADCINX.4 is converted
    ADC_CH_ADCINX_5  = 0x5U,          //!< ADCINX.5 is converted
    ADC_CH_ADCINX_6  = 0x6U,          //!< ADCINX.6 is converted
    ADC_CH_ADCINX_7  = 0x7U,          //!< ADCINX.7 is converted
    ADC_CH_ADCINX_8  = 0x8U,          //!< ADCINX.8 is converted
    ADC_CH_ADCINX_9  = 0x9U,          //!< ADCINX.9 is converted
    ADC_CH_ADCINX_10 = 0xAU,          //!< ADCINX.10 is converted
    ADC_CH_ADCINX_11 = 0xBU,          //!< ADCINX.11 is converted
    ADC_CH_ADCINX_12 = 0xCU,          //!< ADCINX.12 is converted
    ADC_CH_ADCINX_13 = 0xDU,          //!< ADCINX.13 is converted
    ADC_CH_ADCINX_14 = 0xEU,          //!< ADCINX.14 is converted
    ADC_CH_ADCINX_15 = 0xFU           //!< ADCINX.15 is converted
} ADC_ExtChannel;

//*****************************************************************************
//
//! Values that can be passed to ADC_setInterruptSource() as the \e intTrigger
//! parameter.
//
//*****************************************************************************
typedef enum
{
    ADC_INT_TRIGGER_EOC0   = 0U,        //!< SOC/EOC0
    ADC_INT_TRIGGER_EOC1   = 1U,        //!< SOC/EOC1
    ADC_INT_TRIGGER_EOC2   = 2U,        //!< SOC/EOC2
    ADC_INT_TRIGGER_EOC3   = 3U,        //!< SOC/EOC3
    ADC_INT_TRIGGER_EOC4   = 4U,        //!< SOC/EOC4
    ADC_INT_TRIGGER_EOC5   = 5U,        //!< SOC/EOC5
    ADC_INT_TRIGGER_EOC6   = 6U,        //!< SOC/EOC6
    ADC_INT_TRIGGER_EOC7   = 7U,        //!< SOC/EOC7
    ADC_INT_TRIGGER_EOC8   = 8U,        //!< SOC/EOC8
    ADC_INT_TRIGGER_EOC9   = 9U,        //!< SOC/EOC9
    ADC_INT_TRIGGER_EOC10  = 10U,       //!< SOC/EOC10
    ADC_INT_TRIGGER_EOC11  = 11U,       //!< SOC/EOC11
    ADC_INT_TRIGGER_EOC12  = 12U,       //!< SOC/EOC12
    ADC_INT_TRIGGER_EOC13  = 13U,       //!< SOC/EOC13
    ADC_INT_TRIGGER_EOC14  = 14U,       //!< SOC/EOC14
    ADC_INT_TRIGGER_EOC15  = 15U,       //!< SOC/EOC15
    ADC_INT_TRIGGER_OSINT1 = 16U,       //!< OSINT1
    ADC_INT_TRIGGER_OSINT2 = 17U,       //!< OSINT2
    ADC_INT_TRIGGER_OSINT3 = 18U,       //!< OSINT3
    ADC_INT_TRIGGER_OSINT4 = 19U        //!< OSINT4
} ADC_IntTrigger;

//*****************************************************************************
//
//! Values that can be passed to ADC_selectPPBCompareSource() as the \e compSrc
//! parameter.
//
//*****************************************************************************
typedef enum
{
    ADC_PPB_COMPSOURCE_RESULT = 0x0U,   //!< PPB compare source is ADCRESULT
    ADC_PPB_COMPSOURCE_PSUM   = 0x1U,   //!< PPB compare source is PSUM
    ADC_PPB_COMPSOURCE_SUM    = 0x2U    //!< PPB compare source is SUM
} ADC_PPBCompSource;

//*****************************************************************************
//
//! Values that can be passed to ADC_configureSafetyChecker() as the
//! \e adcInst parameter.
//
//*****************************************************************************
typedef enum
{
     ADC_A = 0U,                        //!< Select ADCA instance
     ADC_B = 1U,                        //!< Select ADCB instance
     ADC_C = 2U                         //!< Select ADCC instance
} ADC_Select;

//*****************************************************************************
//
//! Values that can be passed to ADC_configureSafetyChecker() as the
//! \e adcResultInst parameter.
//
//*****************************************************************************
typedef enum
{
    ADC_RESULT0  = 0U,                  //!< Select ADC Result 0
    ADC_RESULT1  = 1U,                  //!< Select ADC Result 1
    ADC_RESULT2  = 2U,                  //!< Select ADC Result 2
    ADC_RESULT3  = 3U,                  //!< Select ADC Result 3
    ADC_RESULT4  = 4U,                  //!< Select ADC Result 4
    ADC_RESULT5  = 5U,                  //!< Select ADC Result 5
    ADC_RESULT6  = 6U,                  //!< Select ADC Result 6
    ADC_RESULT7  = 7U,                  //!< Select ADC Result 7
    ADC_RESULT8  = 8U,                  //!< Select ADC Result 8
    ADC_RESULT9  = 9U,                  //!< Select ADC Result 9
    ADC_RESULT10 = 10U,                 //!< Select ADC Result 10
    ADC_RESULT11 = 11U,                 //!< Select ADC Result 11
    ADC_RESULT12 = 12U,                 //!< Select ADC Result 12
    ADC_RESULT13 = 13U,                 //!< Select ADC Result 13
    ADC_RESULT14 = 14U,                 //!< Select ADC Result 14
    ADC_RESULT15 = 15U                  //!< Select ADC Result 15
} ADC_ResultSelect;

//*****************************************************************************
//
//! Values that can be passed to ADC_configSOCSafetyCheckerInput() as the
//! \e scInput parameter.
//
//*****************************************************************************
typedef enum
{
    ADC_SAFETY_CHECKER_INPUT_DISABLE  = 0x0U, //!< Safety checker i/p disabled
    ADC_SAFETY_CHECKER_INPUT_SOCx     = 0x1U, //!< Safety checker i/p is SOCx
    ADC_SAFETY_CHECKER_INPUT_PPBx     = 0x2U, //!< Safety checker i/p is PPBx
    ADC_SAFETY_CHECKER_INPUT_PPBSUMx  = 0x3U  //!< Safety checker i/p is PPBSUMx
} ADC_SafetyCheckerInput;

//*****************************************************************************
//
//! Values that can be passed to ADC_getSafetyCheckerResult() as
//! \e checkInst parameter.
//
//*****************************************************************************
typedef enum
{
  ADC_SAFETY_CHECK1  = 0x0U,            //!< Safety Check Result 1
  ADC_SAFETY_CHECK2  = 0x2U             //!< Safety Check Result 2
} ADC_SafetyCheckInst;

//*****************************************************************************
//
//! Values that can be passed to ADC_enableSafetyCheckEvt() and
//! ADC_disableSafetyCheckEvt() as \e checkEvent parameter.
//
//*****************************************************************************
typedef enum
{
    ADC_SAFETY_CHECK_EVENT1 = 0U,       //!< Safety Check Event 1
    ADC_SAFETY_CHECK_EVENT2 = 8U,       //!< Safety Check Event 2
    ADC_SAFETY_CHECK_EVENT3 = 16U,      //!< Safety Check Event 3
    ADC_SAFETY_CHECK_EVENT4 = 24U       //!< Safety Check Event 4
} ADC_SafetyCheckEvent;

//*****************************************************************************
//
//! Values that can be passed to ADC_enableSafetyCheckEvt(),
//! ADC_disableSafetyCheckEvt(), ADC_enableSafetyCheckInt() and
//! ADC_disableSafetyCheckInt() as \e checkResult parameter.
//
//*****************************************************************************
typedef enum
{
    ADC_SAFETY_CHECK_RES1OVF = 0U,      //!< Safety Check Result1 Overflow
    ADC_SAFETY_CHECK_RES2OVF = 2U,      //!< Safety Check Result2 Overflow
    ADC_SAFETY_CHECK_OOT     = 4U       //!< Safety Check OOT
} ADC_SafetyCheckResult;

//*****************************************************************************
//
//! Values that can be passed to ADC_enableSafetyCheckEvt(),
//! ADC_disableSafetyCheckEvt(), ADC_enableSafetyCheckInt(),
//! ADC_disableSafetyCheckInt(), ADC_getSafetyCheckStatus(),
//! ADC_clearSafetyCheckStatus(), ADC_getSafetyCheckIntStatus() and
//! ADC_clearSafetyCheckIntStatus() as \e checkerNumber parameter.
//
//*****************************************************************************
typedef enum
{
    ADC_SAFETY_CHECKER1 = 0U,           //!< Safety Checker1
    ADC_SAFETY_CHECKER2 = 1U,           //!< Safety Checker2
    ADC_SAFETY_CHECKER3 = 2U,           //!< Safety Checker3
    ADC_SAFETY_CHECKER4 = 3U,           //!< Safety Checker4
    ADC_SAFETY_CHECKER5 = 4U,           //!< Safety Checker5
    ADC_SAFETY_CHECKER6 = 5U,           //!< Safety Checker6
    ADC_SAFETY_CHECKER7 = 6U,           //!< Safety Checker7
    ADC_SAFETY_CHECKER8 = 7U            //!< Safety Checker8
}ADC_Checker;

//*****************************************************************************
//
//! Values that can be passed to ADC_getSafetyCheckStatus() and
//! ADC_clearSafetyCheckStatus(), as \e checkerFlag parameter.
//
//*****************************************************************************
typedef enum
{
    ADC_SAFETY_CHECK_OOT_FLG     = 0U,  //!< Safety Check Out-of-Tolerance Flag
    ADC_SAFETY_CHECK_RES1OVF_FLG = 4U,  //!< Safety Check Result1 Overflow Flag
    ADC_SAFETY_CHECK_RES2OVF_FLG = 8U   //!< Safety Check Result2 Overflow Flag
}ADC_SafetyCheckFlag;


//*****************************************************************************
//
//! Values that can be passed to ADC_configureRepeater() as the \e repInstance
//! parameter.
//
//*****************************************************************************
typedef enum
{
    ADC_REPINST1 = 0x0U,                //!< Select ADC repeater instance 1
    ADC_REPINST2 = 0x1U                 //!< Select ADC repeater instance 2
} ADC_RepInstance;

//*****************************************************************************
//
//! Values that can be passed to ADC_configureRepeater() as the
//! \e config.repMode and ADC_triggerRepeaterMode() as \e mode parameter.
//
//*****************************************************************************
typedef enum
{
    ADC_REPMODE_OVERSAMPLING   = 0x0U,  //!< ADC repeater mode is oversampling
    ADC_REPMODE_UNDERSAMPLING  = 0x1U   //!< ADC repeater mode is undersampling
} ADC_RepMode;

//*****************************************************************************
//
//! Values that can be passed to ADC_configureRepeater() as the
//! \e config parameter.
//
//*****************************************************************************
typedef struct
{
    ADC_RepMode repMode;     //!< Repeater Mode
    ADC_Trigger repTrigger;  //!< Repeater Trigger
    ADC_SyncInput repSyncin; //!< Repeater Syncin
    uint16_t repCount;       //!< Repeater trigger count
    uint16_t repPhase;       //!< Repeater trigger phase delay in sysclk cycles
    uint16_t repSpread;      //!< Repeater trigger spread in sysclk cycles
} ADC_RepeaterConfig;

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
//*****************************************************************************
//
//! \internal
//! Checks an ADC base address.
//!
//! \param base specifies the ADC module base address.
//!
//! This function determines if a ADC module base address is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool
ADC_isBaseValid(uint32_t base)
{
    return(
           (base == ADCA_BASE) ||
           (base == ADCB_BASE) ||
           (base == ADCC_BASE)
          );
}
#endif

//*****************************************************************************
//
//! Configures the analog-to-digital converter module prescaler.
//!
//! \param base is the base address of the ADC module.
//! \param clkPrescale is the ADC clock prescaler.
//!
//! This function configures the ADC module's ADCCLK.
//!
//! The \e clkPrescale parameter specifies the value by which the input clock
//! is divided to make the ADCCLK.  The clkPrescale value can be specified with
//! any of the following enum values:
//! \b ADC_CLK_DIV_1_0, \b ADC_CLK_DIV_2_0, \b ADC_CLK_DIV_2_5, ...,
//! \b ADC_CLK_DIV_7_5, \b ADC_CLK_DIV_8_0, or \b ADC_CLK_DIV_8_5.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_setPrescaler(uint32_t base, ADC_ClkPrescale clkPrescale)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Set the configuration of the ADC module prescaler.
    //
    EALLOW;
    HWREGH(base + ADC_O_CTL2) = (HWREGH(base + ADC_O_CTL2) &
                                 ~ADC_CTL2_PRESCALE_M) | (uint16_t)clkPrescale;
    EDIS;
}

//*****************************************************************************
//
//! Configures a start-of-conversion (SOC) in the ADC.
//!
//! \param base is the base address of the ADC module.
//! \param socNumber is the number of the start-of-conversion.
//! \param trigger the source that will cause the SOC.
//! \param channel is the number associated with the input signal.
//! \param sampleWindow is the acquisition window duration.
//!
//! This function configures the a start-of-conversion (SOC) in the ADC module.
//!
//! The \e socNumber number is a value \b ADC_SOC_NUMBERX where X is a number
//! from 0 to 15 specifying which SOC is to be configured on the ADC module
//! specified by \e base.
//!
//! The \e trigger specifies the event that causes the SOC such as software, a
//! timer interrupt, an ePWM event, or an ADC interrupt. It should be a value
//! in the format of \b ADC_TRIGGER_XXXX where XXXX is the event such as
//! \b ADC_TRIGGER_SW_ONLY, \b ADC_TRIGGER_CPU1_TINT0, \b ADC_TRIGGER_GPIO,
//! \b ADC_TRIGGER_EPWM1_SOCA, and so on.
//!
//! The \e channel parameter specifies the channel to be converted. In
//! single-ended mode this is a single pin given by \b ADC_CH_ADCINx where x is
//! the number identifying the pin between 0 and 31 inclusive. In differential
//! mode, two pins are used as inputs and are passed in the \e channel
//! parameter as \b ADC_CH_ADCIN0_ADCIN1, \b ADC_CH_ADCIN2_ADCIN3, ..., or
//! \b ADC_CH_ADCIN14_ADCIN15.
//!
//! The \e sampleWindow parameter is the acquisition window duration in SYSCLK
//! cycles. It should be a value between 1 and 512 cycles inclusive. The
//! selected duration must be at least as long as one ADCCLK cycle. Also, the
//! datasheet will specify a minimum window duration requirement in
//! nanoseconds.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_setupSOC(uint32_t base, ADC_SOCNumber socNumber, ADC_Trigger trigger,
             ADC_Channel channel, uint32_t sampleWindow)
{
    uint32_t ctlRegAddr;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));
    ASSERT((sampleWindow >= 1U) && (sampleWindow <= 512U));

    //
    // Calculate address for the SOC control register.
    //
    ctlRegAddr = base + ADC_SOCxCTL_OFFSET_BASE + ((uint32_t)socNumber * 2U);

    //
    // Set the configuration of the specified SOC.
    //
    EALLOW;
    HWREG(ctlRegAddr) = ((uint32_t)channel << ADC_SOC0CTL_CHSEL_S) |
                        ((uint32_t)trigger << ADC_SOC0CTL_TRIGSEL_S) |
                        (sampleWindow - 1U);
    EDIS;
}
//*****************************************************************************
//
//! Disable internal VREFLO connection.
//!
//! This function disables the internal connection of VREFLO for the ADC.
//!
//! \note This function disables the internal connections for VREFLO which is
//! available through CMPSS module. To confiugre the internal connection for
//! VREFLO, please refer ADC_setupSOCRefloChannel().
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_disableIntRefloConnection(void)
{
    EALLOW;
    HWREG(ANALOGSUBSYS_BASE + ASYSCTL_O_INTERNALTESTCTL) = (0xA5A50000UL);
    HWREGH(CMPSS1_BASE + 0x1FU) = 0U;
    EDIS;
}

//*****************************************************************************
//
//! Configures the external channel mux for an ADC SOC.
//!
//! \param base is the base address of the ADC module.
//! \param socNumber is the number of the start-of-conversion.
//! \param extChannel is the desired external channel.
//!
//! This function configures the external channel for an SOC by configuring
//! the external channel mux for an SOC.
//!
//! The \e socNumber number is a value \b ADC_SOC_NUMBERX where X is a number
//! from 0 to 15 specifying which SOC is to be configured on the ADC module
//! specified by \e base.
//!
//! The \e extChannel is the desired external channel. Valid values can be
//! refered from the enum \e ADC_ExtChannel.
//!
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_selectSOCExtChannel(uint32_t base, ADC_SOCNumber socNumber,
                        uint16_t extChannel)
{
    uint32_t ctlRegAddr;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));
    ASSERT(extChannel <= 15U);

    //
    // Calculate address for the SOC control register.
    //
    ctlRegAddr = base + ADC_SOCxCTL_OFFSET_BASE + ((uint32_t)socNumber * 2U);

    //
    // Set the external channel configuration of the specified SOC.
    //
    EALLOW;
    HWREG(ctlRegAddr) =
                   (HWREG(ctlRegAddr) & ~((uint32_t)ADC_SOC0CTL_EXTCHSEL_M)) |
                   (uint32_t)extChannel;
    EDIS;
}


//*****************************************************************************
//
//! Forces software trigger to ADC trigger repeater block
//!
//! \param base is the base address of the ADC module.
//! \param repInstance is the repeater instance to be triggered.
//!
//! This function forces the selected ADC repeater block.
//!
//! Valid values for \e repInstance parameter can be any of the individual
//! ADC_REPEATER_INSTANCEx values defined by enum \e ADC_RepInstance.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_forceRepeaterTrigger(uint32_t base, uint16_t repInstance)
{
  uint32_t regOffset;
  //
  // Check the arguments.
  //
  ASSERT(ADC_isBaseValid(base));

  regOffset = base + (repInstance * (ADC_REPxCTL_STEP));
  EALLOW;
  //
  // Triggers the selected repeater instance
  //
  HWREGH(regOffset + ADC_O_REP1FRC) |= ADC_REP1FRC_SWFRC;
  EDIS;
}

//*****************************************************************************
//
//! Gets the current status for repeater block.
//!
//! \param base is the base address of the ADC module.
//! \param repInstance is the repeater instance
//!
//! This function returns the current status for the repeater block.
//!
//! \return Returns the current event status, enumerated as a bit field of
//! \b ADC_REPEATER_MODULE_BUSY, \b ADC_REPEATER_PHASE_OVERFLOW, and
//! \b ADC_REPEATER_TRIGGER_OVERFLOW.
//
//*****************************************************************************
static inline uint16_t
ADC_getRepeaterStatus(uint32_t base, uint16_t repInstance)
{
    uint32_t regOffset;
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    regOffset = base + (repInstance * (ADC_REPxCTL_STEP));

    //
    // Return the status of repeater.
    //
    return(HWREGH(regOffset + ADC_O_REP1CTL) & ADC_REPSTATUS_MASK);
}

//*****************************************************************************
//
//! Configures the interrupt SOC trigger of an SOC.
//!
//! \param base is the base address of the ADC module.
//! \param socNumber is the number of the start-of-conversion.
//! \param trigger the interrupt source that will cause the SOC.
//!
//! This function configures the interrupt start-of-conversion trigger in
//! the ADC module.
//!
//! The \e socNumber number is a value \b ADC_SOC_NUMBERX where X is a number
//! from 0 to 15 specifying which SOC is to be configured on the ADC module
//! specified by \e base.
//!
//! The \e trigger specifies the interrupt that causes a start of conversion or
//! none. It should be one of the following values.
//!
//! - \b ADC_INT_SOC_TRIGGER_NONE
//! - \b ADC_INT_SOC_TRIGGER_ADCINT1
//! - \b ADC_INT_SOC_TRIGGER_ADCINT2
//!
//! This functionality is useful for creating continuous conversions.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_setInterruptSOCTrigger(uint32_t base, ADC_SOCNumber socNumber,
                           ADC_IntSOCTrigger trigger)
{
    uint16_t shiftVal;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Each SOC has a 2-bit field in this register.
    //
    shiftVal = (uint16_t)socNumber << 1U;

    //
    // Set the configuration of the specified SOC. Not that we're treating
    // ADCINTSOCSEL1 and ADCINTSOCSEL2 as one 32-bit register here.
    //
    EALLOW;
    HWREG(base + ADC_O_INTSOCSEL1) = (HWREG(base + ADC_O_INTSOCSEL1) &
                                      ~((uint32_t)ADC_INTSOCSEL1_SOC0_M <<
                                        shiftVal)) |
                                     ((uint32_t)trigger << shiftVal);
    EDIS;
}

//*****************************************************************************
//
//! Sets the timing of the end-of-conversion pulse
//!
//! \param base is the base address of the ADC module.
//! \param pulseMode is the generation mode of the EOC pulse.
//!
//! This function configures the end-of-conversion (EOC) pulse generated by ADC.
//! This pulse will be generated either at the end of the acquisition window
//! plus a number of SYSCLK cycles configured by ADC_setInterruptCycleOffset()
//! (pass \b ADC_PULSE_END_OF_ACQ_WIN into \e pulseMode) or at the end of the
//! voltage conversion, one cycle prior to the ADC result latching into it's
//! result register (pass \b ADC_PULSE_END_OF_CONV into \e pulseMode).
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_setInterruptPulseMode(uint32_t base, ADC_PulseMode pulseMode)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Set the position of the pulse.
    //
    EALLOW;
    HWREGH(base + ADC_O_CTL1) = (HWREGH(base + ADC_O_CTL1) &
                                 ~ADC_CTL1_INTPULSEPOS) | (uint16_t)pulseMode;
    EDIS;
}

//*****************************************************************************
//
//! Sets the timing of early interrupt generation.
//!
//! \param base is the base address of the ADC module.
//! \param cycleOffset is the cycles from an SOC falling edge to an early
//! interrupt pulse.
//!
//! This function configures cycle offset between the negative edge of a sample
//! pulse and an early interrupt pulse being generated. This number of cycles
//! is specified with the \e cycleOffset parameter.
//!
//! This function only applies when early interrupt generation is enabled. That
//! means the ADC_setInterruptPulseMode() function \e pulseMode parameter is
//! configured as \b ADC_PULSE_END_OF_ACQ_WIN.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_setInterruptCycleOffset(uint32_t base, uint16_t cycleOffset)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Set the position of the pulse.
    //
    EALLOW;
    HWREGH(base + ADC_O_INTCYCLE) = cycleOffset;
    EDIS;
}

//*****************************************************************************
//
//! Enables alternate timings for DMA trigger
//!
//! \param base is the base address of the ADC module.
//!
//! This function enables the alternate timings(tDMA) for DMA trigger. When
//! enabled the DMA is always triggered at tDMA regardless of whether the ADC
//! is in early interrupt mode or late interrupt mode.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_enableAltDMATiming(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Enable the Alternate DMA timings wherein DMA is triggered
    // at tDMA.
    //
    EALLOW;
    HWREGH(base + ADC_O_CTL1) |= ADC_CTL1_TDMAEN;
    EDIS;
}

//*****************************************************************************
//
//! Disables alternate timings for DMA trigger
//!
//! \param base is the base address of the ADC module.
//!
//! This function disables the alternate timings(tDMA) for DMA trigger. When
//! disabled the DMA is triggered at the same time as the CPU interrupt.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_disableAltDMATiming(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Disable the Alternate DMA timings wherein DMA is triggered at the same
    // time as CPU interrupt.
    //
    EALLOW;
    HWREGH(base + ADC_O_CTL1) &= ~ADC_CTL1_TDMAEN;
    EDIS;
}

//*****************************************************************************
//
//! Enables external channel mux preselection
//!
//! \param base is the base address of the ADC module.
//!
//! This function enables the preselection of external mux pins which is at the
//! end of the S+H window of the previous conversion. This preselection allows
//! some of the external mux settling time to be pipelined with previous
//! conversion's conversion time and can be enabled if ADC SOC sequence is
//! deterministic.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_enableExtMuxPreselect(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Enable the external mux selection at the end of S+H window of
    // previous conversion.
    //
    EALLOW;
    HWREGH(base + ADC_O_CTL1) |= ADC_CTL1_EXTMUXPRESELECTEN;
    EDIS;
}

//*****************************************************************************
//
//! Disables external mux preselection
//!
//! \param base is the base address of the ADC module.
//!
//! This function disables the preselection of external mux pins as in
//! ADCEXTMUX pins can only change at the beginning of S+H window of
//! current conversion.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_disableExtMuxPreselect(uint32_t base)
{
    //
    // Check the arguments
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Enable the external mux selection at the beginning of S+H window of
    // current conversion.
    //
    EALLOW;
    HWREGH(base + ADC_O_CTL1) &= ~ADC_CTL1_EXTMUXPRESELECTEN;
    EDIS;
}

//*****************************************************************************
//
//! Selects the offset trim mode
//!
//! \param base is the base address of the ADC module.
//! \param mode is the offset trim mode to be selected.
//!
//! This function configures the offset trim mode for an ADC instance. This
//! means that the offset trim to be used for an ADC mode would be specified
//! by the \e mode parameter. Valid values for \e mode parameter are:
//! - \e ADC_OFFSET_TRIM_COMMON - Offset trim will always be supplied from
//!   ADCOFFTRIM.OFFTRIM register field (Legacy mode)
//! - \e ADC_OFFSET_TRIM_INDIVIDUAL - offset trim will be supplied from
//!   individual registers based on the combination of resolution, signalmode,
//!   and capacitor bank related configurations.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_selectOffsetTrimMode(uint32_t base, ADC_OffsetTrim mode)
{
    //
    // Check the arguments
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Enable the external mux selection at the end of S+H window of
    // previous conversion.
    //
    EALLOW;
    HWREGH(base + ADC_O_CTL2) = (HWREGH(base + ADC_O_CTL2) &
                                 ~(ADC_CTL2_OFFTRIMMODE))  | (uint16_t)mode;
    EDIS;
}

//*****************************************************************************
//
//! Gets the result ready status for ADC interrupt.
//!
//! \param base is the base address of the ADC module.
//! \param adcIntNum is interrupt number within the ADC wrapper.
//!
//! This function returns the result ready status associated with the selected
//! interrupt number within the ADC wrapper.
//!
//! \e adcIntNum takes a one of the values
//! \b ADC_INT_NUMBER1, \b ADC_INT_NUMBER2, \b ADC_INT_NUMBER3
//! or \b ADC_INT_NUMBER4 to get the result ready status for the conversions
//! associated with the given interrupt number.
//!
//! \return \b true if the result is available for the selected interrupt
//! and \b false if it is not.
//
//*****************************************************************************
static inline bool
ADC_getIntResultStatus(uint32_t base, ADC_IntNumber adcIntNum)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Get the specified ADC interrupt result ready status.
    //
    return((HWREGH(base + ADC_O_INTFLG) &
                 (1U << ((uint16_t)adcIntNum + 4U))) != 0U);
}

//*****************************************************************************
//
//! Powers up the analog-to-digital converter core.
//!
//! \param base is the base address of the ADC module.
//!
//! This function powers up the analog circuitry inside the analog core.
//!
//! \note Allow at least a 500us delay before sampling after calling this API.
//! If you enable multiple ADCs, you can delay after they all have begun
//! powering up.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_enableConverter(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Set the bit that powers up the analog circuitry.
    //
    EALLOW;
    HWREGH(base + ADC_O_CTL1) |= ADC_CTL1_ADCPWDNZ;
    EDIS;
}

//*****************************************************************************
//
//! Powers down the analog-to-digital converter module.
//!
//! \param base is the base address of the ADC module.
//!
//! This function powers down the analog circuitry inside the analog core.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_disableConverter(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Clear the bit that powers down the analog circuitry.
    //
    EALLOW;
    HWREGH(base + ADC_O_CTL1) &= ~ADC_CTL1_ADCPWDNZ;
    EDIS;
}

//*****************************************************************************
//
//! Forces a SOC flag to a 1 in the analog-to-digital converter.
//!
//! \param base is the base address of the ADC module.
//! \param socNumber is the number of the start-of-conversion.
//!
//! This function forces the SOC flag associated with the SOC specified by
//! \e socNumber. This initiates a conversion once that SOC is given
//! priority. This software trigger can be used whether or not the SOC has been
//! configured to accept some other specific trigger.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_forceSOC(uint32_t base, ADC_SOCNumber socNumber)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Write to the register that will force a 1 to the corresponding SOC flag
    //
    HWREGH(base + ADC_O_SOCFRC1) = ((uint16_t)1U << (uint16_t)socNumber);
}

//*****************************************************************************
//
//! Forces multiple SOC flags to 1 in the analog-to-digital converter.
//!
//! \param base is the base address of the ADC module.
//! \param socMask is the SOCs to be forced through software
//!
//! This function forces the SOCFRC1 flags associated with the SOCs specified
//! by \e socMask. This initiates a conversion once the desired SOCs are given
//! priority. This software trigger can be used whether or not the SOC has been
//! configured to accept some other specific trigger.
//! Valid values for \e socMask parameter can be any of the individual
//! ADC_FORCE_SOCx values or any of their OR'd combination to trigger multiple
//! SOCs.
//!
//! \note To trigger SOC0, SOC1 and SOC2, value (ADC_FORCE_SOC0 |
//! ADC_FORCE_SOC1 | ADC_FORCE_SOC2) should be passed as socMask.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_forceMultipleSOC(uint32_t base, uint16_t socMask)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Write to the register that will force a 1 to desired SOCs
    //
    HWREGH(base + ADC_O_SOCFRC1) = socMask;
}

//*****************************************************************************
//
//! Gets the current ADC interrupt status.
//!
//! \param base is the base address of the ADC module.
//! \param adcIntNum is interrupt number within the ADC wrapper.
//!
//! This function returns the interrupt status for the analog-to-digital
//! converter.
//!
//! \e adcIntNum takes a one of the values \b ADC_INT_NUMBER1,
//! \b ADC_INT_NUMBER2, \b ADC_INT_NUMBER3 or \b ADC_INT_NUMBER4 to get
//! the interrupt status for the given interrupt number of the ADC module.
//!
//! \return \b true if the interrupt flag for the specified interrupt number is
//! set and \b false if it is not.
//
//*****************************************************************************
static inline bool
ADC_getInterruptStatus(uint32_t base, ADC_IntNumber adcIntNum)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));
    //
    // Get the specified ADC interrupt status.
    //
    return((HWREGH(base + ADC_O_INTFLG) & (1U << (uint16_t)adcIntNum)) != 0U);
}

//*****************************************************************************
//
//! Clears ADC interrupt sources.
//!
//! \param base is the base address of the ADC module.
//! \param adcIntNum is interrupt number within the ADC wrapper.
//!
//! This function clears the specified ADC interrupt sources so that they no
//! longer assert. If not in continuous mode, this function must be called
//! before any further interrupt pulses may occur.
//!
//! \e adcIntNum takes a one of the values \b ADC_INT_NUMBER1,
//! \b ADC_INT_NUMBER2, \b ADC_INT_NUMBER3 or \b ADC_INT_NUMBER4 to express
//! which of the four interrupts of the ADC module should be cleared.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_clearInterruptStatus(uint32_t base, ADC_IntNumber adcIntNum)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Clear the specified interrupt.
    //
    HWREGH(base + ADC_O_INTFLGCLR) = (uint16_t)1U << (uint16_t)adcIntNum;

}

//*****************************************************************************
//
//! Gets the current ADC interrupt overflow status.
//!
//! \param base is the base address of the ADC module.
//! \param adcIntNum is interrupt number within the ADC wrapper.
//!
//! This function returns the interrupt overflow status for the
//! analog-to-digital converter. An overflow condition is generated
//! irrespective of the continuous mode.
//!
//! \e adcIntNum takes a one of the values \b ADC_INT_NUMBER1,
//! \b ADC_INT_NUMBER2, \b ADC_INT_NUMBER3 or \b ADC_INT_NUMBER4 to get
//! the interrupt overflow status for the given interrupt number.
//!
//! \return \b true if the interrupt overflow flag for the specified interrupt
//! number is set and \b false if it is not.
//
//*****************************************************************************
static inline bool
ADC_getInterruptOverflowStatus(uint32_t base, ADC_IntNumber adcIntNum)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Get the specified ADC interrupt status.
    //
    return((HWREGH(base + ADC_O_INTOVF) & (1U << (uint16_t)adcIntNum)) != 0U);
}

//*****************************************************************************
//
//! Clears ADC interrupt overflow sources.
//!
//! \param base is the base address of the ADC module.
//! \param adcIntNum is interrupt number within the ADC wrapper.
//!
//! This function clears the specified ADC interrupt overflow sources so that
//! they no longer assert. If software tries to clear the overflow in the same
//! cycle that hardware tries to set the overflow, then hardware has priority.
//!
//! \e adcIntNum takes a one of the values \b ADC_INT_NUMBER1,
//! \b ADC_INT_NUMBER2, \b ADC_INT_NUMBER3 or \b ADC_INT_NUMBER4 to express
//! which of the four interrupt overflow status of the ADC module
//! should be cleared.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_clearInterruptOverflowStatus(uint32_t base, ADC_IntNumber adcIntNum)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Clear the specified interrupt overflow bit.
    //
    HWREGH(base + ADC_O_INTOVFCLR) = (uint16_t)1U << (uint16_t)adcIntNum;
}

//*****************************************************************************
//
//! Reads the conversion result.
//!
//! \param resultBase is the base address of the ADC results.
//! \param socNumber is the number of the start-of-conversion.
//!
//! This function returns the conversion result that corresponds to the base
//! address passed into \e resultBase and the SOC passed into \e socNumber.
//!
//! The \e socNumber number is a value \b ADC_SOC_NUMBERX where X is a number
//! from 0 to 15 specifying which SOC's result is to be read.
//!
//! \note Take care that you are using a base address for the result registers
//! (ADCxRESULT_BASE) and not a base address for the control registers.
//!
//! \return Returns the conversion result.
//
//*****************************************************************************
static inline uint16_t
ADC_readResult(uint32_t resultBase, ADC_SOCNumber socNumber)
{
    //
    // Check the arguments.
    //
    ASSERT(
           (resultBase == ADCARESULT_BASE) ||
           (resultBase == ADCBRESULT_BASE) ||
           (resultBase == ADCCRESULT_BASE)
          );
    //
    // Return the ADC result for the selected SOC.
    //
    return(HWREGH(resultBase + (uint32_t)ADC_RESULTx_OFFSET_BASE +
                  (uint32_t)socNumber));
}

//*****************************************************************************
//
//! Determines whether the ADC is busy or not.
//!
//! \param base is the base address of the ADC.
//!
//! This function allows the caller to determine whether or not the ADC is
//! busy and can sample another channel.
//!
//! \return Returns \b true if the ADC is sampling or \b false if all
//! samples are complete.
//
//*****************************************************************************
static inline bool
ADC_isBusy(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Determine if the ADC is busy.
    //
    return((HWREGH(base + ADC_O_CTL1) & ADC_CTL1_ADCBSY) != 0U);
}

//*****************************************************************************
//
//! Set SOC burst mode.
//!
//! \param base is the base address of the ADC.
//! \param trigger the source that will cause the burst conversion sequence.
//! \param burstSize is the number of SOCs converted during a burst sequence.
//!
//! This function configures the burst trigger and burstSize of an ADC module.
//! Burst mode allows a single trigger to walk through the round-robin SOCs one
//! or more at a time. When burst mode is enabled, the trigger selected by the
//! ADC_setupSOC() API will no longer have an effect on the SOCs in round-robin
//! mode. Instead, the source specified through the \e trigger parameter will
//! cause a burst of \e burstSize conversions to occur.
//!
//! The \e trigger parameter takes the same values as the ADC_setupSOC() API
//! The \e burstSize parameter should be a value between 1 and 16 inclusive.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_setBurstModeConfig(uint32_t base, ADC_Trigger trigger, uint16_t burstSize)
{
    uint16_t regValue;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));
    ASSERT(((uint16_t)trigger & ~((uint16_t)0x1FU)) == 0U);
    ASSERT((burstSize >= 1U) && (burstSize <= 16U));

    //
    // Write the burst mode configuration to the register.
    //
    EALLOW;

    regValue = (uint16_t)trigger | ((burstSize - 1U) <<
                                    ADC_BURSTCTL_BURSTSIZE_S);

    HWREGH(base + ADC_O_BURSTCTL) = (HWREGH(base + ADC_O_BURSTCTL) &
                                     ~((uint16_t)ADC_BURSTCTL_BURSTTRIGSEL_M |
                                       ADC_BURSTCTL_BURSTSIZE_M)) | regValue;

    EDIS;
}

//*****************************************************************************
//
//! Enables SOC burst mode.
//!
//! \param base is the base address of the ADC.
//!
//! This function enables SOC burst mode operation of the ADC. Burst mode
//! allows a single trigger to walk through the round-robin SOCs one or more at
//! a time. When burst mode is enabled, the trigger selected by the
//! ADC_setupSOC() API will no longer have an effect on the SOCs in round-robin
//! mode. Use ADC_setBurstMode() to configure the burst trigger and size.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_enableBurstMode(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Enable burst mode.
    //
    EALLOW;
    HWREGH(base + ADC_O_BURSTCTL) |= ADC_BURSTCTL_BURSTEN;
    EDIS;
}

//*****************************************************************************
//
//! Disables SOC burst mode.
//!
//! \param base is the base address of the ADC.
//!
//! This function disables SOC burst mode operation of the ADC. SOCs in
//! round-robin mode will be triggered by the trigger configured using the
//! ADC_setupSOC() API.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_disableBurstMode(uint32_t base)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Disable burst mode.
    //
    EALLOW;
    HWREGH(base + ADC_O_BURSTCTL) &= ~ADC_BURSTCTL_BURSTEN;
    EDIS;
}

//*****************************************************************************
//
//! Sets the priority mode of the SOCs.
//!
//! \param base is the base address of the ADC.
//! \param priMode is the priority mode of the SOCs.
//!
//! This function sets the priority mode of the SOCs. There are three main
//! modes that can be passed in the \e priMode parameter
//!
//! - All SOCs are in round-robin mode. This means no SOC has an inherent
//! higher priority over another. This is selected by passing in the value
//! \b ADC_PRI_ALL_ROUND_ROBIN.
//! - All priorities are in high priority mode. This means that the priority of
//! the SOC is determined by its SOC number. This option is selected by passing
//! in the value \b ADC_PRI_ALL_HIPRI.
//! - A range of SOCs are assigned high priority, with all others in round
//! robin mode. High priority mode means that an SOC with high priority will
//! interrupt the round robin wheel and insert itself as the next conversion.
//! Passing in the value \b ADC_PRI_SOC0_HIPRI will make SOC0 highest priority,
//! \b ADC_PRI_THRU_SOC1_HIPRI will put SOC0 and SOC 1 in high priority, and so
//! on up to \b ADC_PRI_THRU_SOC14_HIPRI where SOCs 0 through 14 are in high
//! priority.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_setSOCPriority(uint32_t base, ADC_PriorityMode priMode)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    EALLOW;

    HWREGH(base + ADC_O_SOCPRICTL) = (HWREGH(base + ADC_O_SOCPRICTL) &
                                      ~ADC_SOCPRICTL_SOCPRIORITY_M) |
                                     (uint16_t)priMode;

    EDIS;
}

//*****************************************************************************
//
//! Configures Open/Shorts Detection Circuit Mode.
//!
//! \param base is the base address of the ADC.
//! \param modeVal is the desired open/shorts detection circuit mode.
//!
//! This function configures the open/shorts detection circuit mode of the ADC.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_configOSDetectMode(uint32_t base, ADC_OSDetectMode modeVal)
{
    //
    // Configure open/shorts detection circuit mode.
    //
    EALLOW;
    HWREGH(base + ADC_O_OSDETECT) = ((HWREGH(base + ADC_O_OSDETECT) &
                                     (~ADC_OSDETECT_DETECTCFG_M)) |
                                     (uint16_t)modeVal);
    EDIS;
}

//*****************************************************************************
//
//! Configures a post-processing block (PPB) in the ADC.
//!
//! \param base is the base address of the ADC module.
//! \param ppbNumber is the number of the post-processing block.
//! \param socNumber is the number of the start-of-conversion.
//!
//! This function associates a post-processing block with a SOC.
//!
//! The \e ppbNumber is a value \b ADC_PPB_NUMBERX where X is a value from 1 to
//! 4 inclusive that identifies a PPB to be configured.  The \e socNumber
//! number is a value \b ADC_SOC_NUMBERX where X is a number from 0 to 15
//! specifying which SOC is to be configured on the ADC module specified by
//! \e base.
//!
//! \note You can have more that one PPB associated with the same SOC, but a
//! PPB can only be configured to correspond to one SOC at a time. Also note
//! that when you have multiple PPBs for the same SOC, the calibration offset
//! that actually gets applied will be that of the PPB with the highest number.
//! Since SOC0 is the default for all PPBs, look out for unintentional
//! overwriting of a lower numbered PPB's offset.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_setupPPB(uint32_t base, ADC_PPBNumber ppbNumber, ADC_SOCNumber socNumber)
{
    uint32_t ppbOffset;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Get the offset to the appropriate PPB configuration register.
    //
    ppbOffset = (ADC_PPBxCONFIG_STEP * (uint32_t)ppbNumber) + ADC_O_PPB1CONFIG;

    //
    // Write the configuration to the register.
    //
    EALLOW;
    HWREGH(base + ppbOffset) = (HWREGH(base + ppbOffset) &
                                ~ADC_PPB1CONFIG_CONFIG_M) |
                               ((uint16_t)socNumber & ADC_PPB1CONFIG_CONFIG_M);
    EDIS;
}

//*****************************************************************************
//
//! Enables individual ADC PPB event sources.
//!
//! \param base is the base address of the ADC module.
//! \param ppbNumber is the number of the post-processing block.
//! \param evtFlags is a bit mask of the event sources to be enabled.
//!
//! This function enables the indicated ADC PPB event sources.  This will allow
//! the specified events to propagate through the X-BAR to a pin or to an ePWM
//! module.  The \e evtFlags parameter can be any of the \b ADC_EVT_TRIPHI,
//! \b ADC_EVT_TRIPLO, or \b ADC_EVT_ZERO values.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_enablePPBEvent(uint32_t base, ADC_PPBNumber ppbNumber, uint16_t evtFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));
    ASSERT((evtFlags & ~0x7U) == 0U);

    //
    // Enable the specified event.
    //
    EALLOW;
    HWREGH(base + ADC_O_EVTSEL) |= evtFlags << ((uint16_t)ppbNumber * 4U);
    EDIS;
}

//*****************************************************************************
//
//! Disables individual ADC PPB event sources.
//!
//! \param base is the base address of the ADC module.
//! \param ppbNumber is the number of the post-processing block.
//! \param evtFlags is a bit mask of the event sources to be enabled.
//!
//! This function disables the indicated ADC PPB event sources.  This will stop
//! the specified events from propagating through the X-BAR to other modules.
//! The \e evtFlags parameter can be any of the \b ADC_EVT_TRIPHI,
//! \b ADC_EVT_TRIPLO, or \b ADC_EVT_ZERO values.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_disablePPBEvent(uint32_t base, ADC_PPBNumber ppbNumber, uint16_t evtFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));
    ASSERT((evtFlags & ~0x7U) == 0U);

    //
    // Disable the specified event.
    //
    EALLOW;
    HWREGH(base + ADC_O_EVTSEL) &= ~(evtFlags << ((uint16_t)ppbNumber * 4U));
    EDIS;
}

//*****************************************************************************
//
//! Enables individual ADC PPB event interrupt sources.
//!
//! \param base is the base address of the ADC module.
//! \param ppbNumber is the number of the post-processing block.
//! \param intFlags is a bit mask of the interrupt sources to be enabled.
//!
//! This function enables the indicated ADC PPB interrupt sources.  Only the
//! sources that are enabled can be reflected to the processor interrupt.
//! Disabled sources have no effect on the processor.  The \e intFlags
//! parameter can be any of the \b ADC_EVT_TRIPHI, \b ADC_EVT_TRIPLO, or
//! \b ADC_EVT_ZERO values.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_enablePPBEventInterrupt(uint32_t base, ADC_PPBNumber ppbNumber,
                            uint16_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));
    ASSERT((intFlags & ~0x7U) == 0U);

    //
    // Enable the specified event interrupts.
    //
    EALLOW;
    HWREGH(base + ADC_O_EVTINTSEL) |= intFlags << ((uint16_t)ppbNumber * 4U);
    EDIS;
}

//*****************************************************************************
//
//! Disables individual ADC PPB event interrupt sources.
//!
//! \param base is the base address of the ADC module.
//! \param ppbNumber is the number of the post-processing block.
//! \param intFlags is a bit mask of the interrupt source to be disabled.
//!
//! This function disables the indicated ADC PPB interrupt sources.  Only the
//! sources that are enabled can be reflected to the processor interrupt.
//! Disabled sources have no effect on the processor.  The \e intFlags
//! parameter can be any of the \b ADC_EVT_TRIPHI, \b ADC_EVT_TRIPLO, or
//! \b ADC_EVT_ZERO values.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_disablePPBEventInterrupt(uint32_t base, ADC_PPBNumber ppbNumber,
                             uint16_t intFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));
    ASSERT((intFlags & ~0x7U) == 0U);

    //
    // Disable the specified event interrupts.
    //
    EALLOW;
    HWREGH(base + ADC_O_EVTINTSEL) &= ~(intFlags <<
                                        ((uint16_t)ppbNumber * 4U));
    EDIS;
}

//*****************************************************************************
//
//! Gets the current ADC event status.
//!
//! \param base is the base address of the ADC module.
//! \param ppbNumber is the number of the post-processing block.
//!
//! This function returns the event status for the analog-to-digital converter.
//!
//! \return Returns the current event status, enumerated as a bit field of
//! \b ADC_EVT_TRIPHI, \b ADC_EVT_TRIPLO, and \b ADC_EVT_ZERO.
//
//*****************************************************************************
static inline uint16_t
ADC_getPPBEventStatus(uint32_t base, ADC_PPBNumber ppbNumber)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Get the event status for the specified post-processing block.
    //
    return((HWREGH(base + ADC_O_EVTSTAT) >> ((uint16_t)ppbNumber * 4U)) &
           0x7U);
}

//*****************************************************************************
//
//! Clears ADC event flags.
//!
//! \param base is the base address of the ADC module.
//! \param ppbNumber is the number of the post-processing block.
//! \param evtFlags is a bit mask of the event source to be cleared.
//!
//! This function clears the indicated ADC PPB event flags. After an event
//! occurs this function must be called to allow additional events to be
//! produced. The \e evtFlags parameter can be any of the \b ADC_EVT_TRIPHI,
//! \b ADC_EVT_TRIPLO, or \b ADC_EVT_ZERO values.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_clearPPBEventStatus(uint32_t base, ADC_PPBNumber ppbNumber,
                        uint16_t evtFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));
    ASSERT((evtFlags & ~0x7U) == 0U);

    //
    // Clear the specified event interrupts.
    //
    HWREGH(base + ADC_O_EVTCLR) |= evtFlags << ((uint16_t)ppbNumber * 4U);
}

//*****************************************************************************
//
//! Enables cycle-by-cycle clear of ADC PPB event flags.
//!
//! \param base is the base address of the ADC module.
//! \param ppbNumber is the number of the post-processing block.
//!
//! This function enables the automatic cycle-by-cycle clear of ADC PPB event
//! flags. When enabled, the desired PPB event flags are automatically cleared
//! on the next PPBxRESULT load, unless a set condition is also occurring at
//! the same time, in which case the set takes precedence.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_enablePPBEventCBCClear(uint32_t base, ADC_PPBNumber ppbNumber)
{
    uint32_t ppbOffset;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Get the offset to the appropriate PPB configuration register.
    //
    ppbOffset = (ADC_PPBxCONFIG_STEP * (uint32_t)ppbNumber) + ADC_O_PPB1CONFIG;

    //
    // Set automatic cycle-by-cycle flag clear bit
    //
    EALLOW;
    HWREGH(base + ppbOffset) |= ADC_PPB1CONFIG_CBCEN;
    EDIS;
}

//*****************************************************************************
//
//! Disables cycle-by-cycle clear of ADC PPB event flags.
//!
//! \param base is the base address of the ADC module.
//! \param ppbNumber is the number of the post-processing block.
//!
//! This function disables the cycle-by-cycle clear of ADC PPB event flags. When
//! disabled, the desired PPB event flags are to be cleared explicitly in
//! software inorder to generate next set of interrupts/events.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_disablePPBEventCBCClear(uint32_t base, ADC_PPBNumber ppbNumber)
{
    uint32_t ppbOffset;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Get the offset to the appropriate PPB configuration register.
    //
    ppbOffset = (ADC_PPBxCONFIG_STEP * (uint32_t)ppbNumber) + ADC_O_PPB1CONFIG;

    //
    // Clear automatic cycle-by-cycle flag clear bit
    //
    EALLOW;
    HWREGH(base + ppbOffset) &= ~ADC_PPB1CONFIG_CBCEN;
    EDIS;
}

//*****************************************************************************
//
//! Configures PPB count limit.
//!
//! \param base is the base address of the ADC module.
//! \param ppbNumber is the number of the post-processing block.
//! \param limit is the desired PPB count limit.
//!
//! This function configures the PPB oversampling count limit which defines the
//! number of ADC conversions to accumulate before partial sum is automatically
//! loaded to the sum registes.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_setPPBCountLimit(uint32_t base, ADC_PPBNumber ppbNumber, uint16_t limit)
{
    uint32_t ppbOffset;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));
    ASSERT(limit <= ADC_PPB1LIMIT_LIMIT_M);

    //
    // Get the offset to the appropriate PPB configuration register.
    //
    ppbOffset = (ADC_PPBxLIMIT_STEP * (uint32_t)ppbNumber) + ADC_O_PPB1LIMIT;

    //
    // Enable PPB two's complement.
    //
    EALLOW;
    HWREGH(base + ppbOffset) =
                (HWREGH(base + ppbOffset) & ~(ADC_PPB1LIMIT_LIMIT_M)) |
                (limit << ADC_PPB1LIMIT_LIMIT_S);
    EDIS;

}

//*****************************************************************************
//
//! Returns the PPB count limit.
//!
//! \param base is the base address of the ADC module.
//! \param ppbNumber is the number of the post-processing block.
//!
//! This function returns the PPB oversampling count limit which defines the
//! number of ADC conversions to accumulate before partial sum is automatically
//! loaded to the sum registes.
//!
//! \return Returns the PPB count limit.
//
//*****************************************************************************
static inline uint16_t
ADC_getPPBCountLimit(uint32_t base, ADC_PPBNumber ppbNumber)
{
    uint16_t limit;
    uint32_t ppbOffset;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Get the offset to the appropriate PPB configuration register.
    //
    ppbOffset = (ADC_PPBxLIMIT_STEP * (uint32_t)ppbNumber) + ADC_O_PPB1LIMIT;

    limit = (HWREGH(base + ppbOffset) & ~(ADC_PPB1LIMIT_LIMIT_M)) >>
            ADC_PPB1LIMIT_LIMIT_S;
    return(limit);
}

//*****************************************************************************
//
//! Reads the oversampled partial count from the PPB.
//!
//! \param base is the base address of the ADC module.
//! \param ppbNumber is the number of the post-processing block.
//!
//! This function returns the oversampled partial count that corresponds to
//! the base address passed into \e base and the PPB passed into \e ppbNumber.
//!
//! \return Returns the oversampled partial count value.
//
//*****************************************************************************
static inline uint16_t
ADC_readPPBPCount(uint32_t base, ADC_PPBNumber ppbNumber)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Returns the partial count of the selected PPB.
    //
    return(HWREG(base + (uint32_t)ADC_PPBxPCOUNT_OFFSET_BASE +
            ((uint32_t)ppbNumber * 26UL)));
}

//*****************************************************************************
//
//! Reads the oversampled partial sum from the PPB.
//!
//! \param base is the base address of the ADC module.
//! \param ppbNumber is the number of the post-processing block.
//!
//! This function returns the oversampled partial sum of PPB results that
//! corresponds to the base address passed into \e base and the PPB passed
//! into \e ppbNumber.
//!
//! \return Returns the oversampled partial sum value.
//
//*****************************************************************************
static inline int32_t
ADC_readPPBPSum(uint32_t base, ADC_PPBNumber ppbNumber)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Returns the partial sum result of selected PPB.
    //
    return((int32_t)HWREG(base + (uint32_t)ADC_PPBxPSUM_OFFSET_BASE +
           ((uint32_t)ppbNumber * 26UL)));
}

//*****************************************************************************
//
//! Reads the processed conversion result's partial maximum value from the PPB.
//!
//! \param base is the base address of the ADC module.
//! \param ppbNumber is the number of the post-processing block.
//!
//! This function returns the oversampled partial maximum that corresponds to
//! the base address passed into \e base and the PPB passed into \e ppbNumber.
//!
//! \return Returns the oversampled partial maximum value.
//
//*****************************************************************************
static inline int32_t
ADC_readPPBPMax(uint32_t base, ADC_PPBNumber ppbNumber)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Return the partial maximum value of selected PPB.
    //
    return((int32_t)HWREG(base + (uint32_t)ADC_PPBxPMAX_OFFSET_BASE +
           ((uint32_t)ppbNumber * 26UL)));
}

//*****************************************************************************
//
//! Reads the processed conversion result's partial minimum value from the PPB.
//!
//! \param base is the base address of the ADC module.
//! \param ppbNumber is the number of the post-processing block.
//!
//! This function returns the oversampled partial minimum that corresponds to
//! the base address passed into \e base and the PPB passed into \e ppbNumber.
//!
//! \return Returns the oversampled partial minimum value.
//
//*****************************************************************************
static inline int32_t
ADC_readPPBPMin(uint32_t base, ADC_PPBNumber ppbNumber)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Return the partial minimum value of selected PPB.
    //
    return((int32_t)HWREG(base + (uint32_t)ADC_PPBxPMIN_OFFSET_BASE +
           ((uint32_t)ppbNumber * 26UL)));
}

//*****************************************************************************
//
//! Reads the index of the result with partial maximum value from the PPB.
//!
//! \param base is the base address of the ADC module.
//! \param ppbNumber is the number of the post-processing block.
//!
//! This function returns the index of the oversampled partial maximum value
//! that corresponds to the base address passed into \e base
//! and the PPB passed into \e ppbNumber.
//!
//! \return Returns the index of the oversampled partial maximum value.
//
//*****************************************************************************
static inline uint16_t
ADC_readPPBPMaxIndex(uint32_t base, ADC_PPBNumber ppbNumber)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Returns the index of the partial maximum value of selected PPB.
    //
    return((uint16_t)HWREG(base + (uint32_t)ADC_PPBxPMAXI_OFFSET_BASE +
           ((uint32_t)ppbNumber * 26UL)));
}

//*****************************************************************************
//
//! Reads the index of the result with partial minimum value from the PPB.
//!
//! \param base is the base address of the ADC module.
//! \param ppbNumber is the number of the post-processing block.
//!
//! This function returns the index of the oversampled partial minimum value
//! that corresponds to the base address passed into \e base
//! and the PPB passed into \e ppbNumber.
//!
//! \return Returns the index of the oversampled partial minimum value.
//
//*****************************************************************************
static inline uint16_t
ADC_readPPBPMinIndex(uint32_t base, ADC_PPBNumber ppbNumber)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Returns the index of the partial minimum value of selected PPB.
    //
    return((uint16_t)HWREG(base + (uint32_t)ADC_PPBxPMINI_OFFSET_BASE +
           ((uint32_t)ppbNumber * 26UL)));
}

//*****************************************************************************
//
//! Enables absolute value capability in the PPB.
//!
//! \param base is the base address of the ADC module.
//! \param ppbNumber is the number of the post-processing block.
//!
//! This function enables the absolute value functionality in the post-
//! processing block specified by the \e ppbNumber parameter. When enabled,
//! absolute value calculation would be done on the ADC Result associated
//! with the selected SOC. In other words, the PPB result will calculated as
//! shown below: (ADCPPBxRESULT = abs(ADCRESULTx - ADCPPBxOFFREF))
//!
//! \return None
//
//*****************************************************************************
static inline void
ADC_enablePPBAbsoluteValue(uint32_t base, ADC_PPBNumber ppbNumber)
{
    uint32_t ppbOffset;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Get the offset to the appropriate PPB configuration register.
    //
    ppbOffset = (ADC_PPBxCONFIG_STEP * (uint32_t)ppbNumber) + ADC_O_PPB1CONFIG;

    //
    // Enable PPB absolute value.
    //
    EALLOW;
    HWREGH(base + ppbOffset) |= ADC_PPB1CONFIG_ABSEN;
    EDIS;
}

//*****************************************************************************
//
//! Disables absolute value capability in the PPB.
//!
//! \param base is the base address of the ADC module.
//! \param ppbNumber is the number of the post-processing block.
//!
//! This function disables the absolute value functionality in the post-
//! processing block specified by the \e ppbNumber parameter. When disabled,
//! absolute value calculation would be done on the ADC Result associated
//! with the selected SOC. In other words, the PPB result will calculated as
//! shown below: (ADCPPBxRESULT = ADCRESULTx - ADCPPBxOFFREF)
//!
//! \return None
//
//*****************************************************************************
static inline void
ADC_disablePPBAbsoluteValue(uint32_t base, ADC_PPBNumber ppbNumber)
{
    uint32_t ppbOffset;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Get the offset to the appropriate PPB configuration register.
    //
    ppbOffset = (ADC_PPBxCONFIG_STEP * (uint32_t)ppbNumber) + ADC_O_PPB1CONFIG;

    //
    // Disable PPB abosulte value.
    //
    EALLOW;
    HWREGH(base + ppbOffset) &= ~ADC_PPB1CONFIG_ABSEN;
    EDIS;
}

//*****************************************************************************
//
//! Configures PPB shift value.
//!
//! \param base is the base address of the ADC module.
//! \param ppbNumber is the number of the post-processing block.
//! \param shiftVal is the number of bits to right shift PSUM before loading
//! to final PPB SUM.
//!
//! This function configured the shift value required to right shift the PPB
//! PSUM before loading into the final PPB SUM.
//!
//! \return None
//
//*****************************************************************************
static inline void
ADC_setPPBShiftValue(uint32_t base, ADC_PPBNumber ppbNumber, uint16_t shiftVal)
{
    uint32_t ppbOffset;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));
    ASSERT(shiftVal <= 10U);

    //
    // Get the offset to the appropriate PPB configuration register.
    //
    ppbOffset = (ADC_PPBxCONFIG2_STEP * (uint32_t)ppbNumber) +
                    ADC_O_PPB1CONFIG2;

    //
    // Configure shift value for the PPB.
    //
    HWREGH(base + ppbOffset) =
                 (HWREGH(base + ppbOffset) & ~(ADC_PPB1CONFIG2_SHIFT_M)) |
                 (shiftVal << ADC_PPB1CONFIG2_SHIFT_S);
}

//*****************************************************************************
//
//! Configures PPB sync input.
//!
//! \param base is the base address of the ADC module.
//! \param ppbNumber is the number of the post-processing block.
//! \param syncInput is the desired sync event to transfer partial registers
//! to final registers and reset the partial registers.
//!
//! This function configures desired sync event to transfer partial registers
//! to final registers and reset the partial registers. For valid values of
//! \e syncInput refer to enum \e ADC_SyncInput.
//!
//! \return None
//
//*****************************************************************************
static inline void
ADC_selectPPBSyncInput(uint32_t base, ADC_PPBNumber ppbNumber,
                       uint16_t syncInput)
{
    uint32_t ppbOffset;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));
    ASSERT(syncInput <= 0x1DU);

    //
    // Get the offset to the appropriate PPB configuration register.
    //
    ppbOffset = (ADC_PPBxCONFIG2_STEP * (uint32_t)ppbNumber) +
                    ADC_O_PPB1CONFIG2;

    //
    // Select sync input for the PPB.
    //
    HWREGH(base + ppbOffset) =
                 (HWREGH(base + ppbOffset) & ~(ADC_PPB1CONFIG2_SYNCINSEL_M)) |
                 (syncInput << ADC_PPB1CONFIG2_SYNCINSEL_S);
}

//*****************************************************************************
//
//! Forces PPB software sync.
//!
//! \param base is the base address of the ADC module.
//! \param ppbNumber is the number of the post-processing block.
//!
//! This function forces the software sync for the desired PPB.
//!
//! \return None
//
//*****************************************************************************
static inline void
ADC_forcePPBSync(uint32_t base, ADC_PPBNumber ppbNumber)
{
    uint32_t ppbOffset;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Get the offset to the appropriate PPB configuration register.
    //
    ppbOffset = (ADC_PPBxCONFIG2_STEP * (uint32_t)ppbNumber) +
                    ADC_O_PPB1CONFIG2;

    //
    // Force software sync for the PPB.
    //
    HWREGH(base + ppbOffset) |= ADC_PPB1CONFIG2_SWSYNC;
}

//*****************************************************************************
//
//! Configures PPB interrupt source.
//!
//! \param base is the base address of the ADC module.
//! \param ppbNumber is the number of the post-processing block.
//! \param osIntSrc selects PPB interrupt source.
//!
//! This function sets which oversampling event is the source of
//! a PPB intterupt.
//!
//! For valid values of \e osIntSrc refer to enum \e ADC_PPBIntSrcSelect.
//!
//! \return None
//*****************************************************************************
static inline void
ADC_selectPPBOSINTSource(uint32_t base, ADC_PPBNumber ppbNumber,
                         uint16_t osIntSrc)
{
    uint32_t ppbOffset;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));
    ASSERT(osIntSrc <= 1U);

    //
    // Get the offset to the appropriate PPB configuration register.
    //
    ppbOffset = (ADC_PPBxCONFIG2_STEP * (uint32_t)ppbNumber) +
                    ADC_O_PPB1CONFIG2;

    //
    // Select PPB OSINT source.
    //
    HWREGH(base + ppbOffset) =
                 (HWREGH(base + ppbOffset) & ~(ADC_PPB1CONFIG2_OSINTSEL)) |
                 (osIntSrc << 12U);
}

//*****************************************************************************
//
//! Configures PPB compare source.
//!
//! \param base is the base address of the ADC module.
//! \param ppbNumber is the number of the post-processing block.
//! \param compSrc is the desired source to be used for zero crossing detect
//! logic and threshold compare.
//!
//! This function configures the desired source to be used for zero crossing
//! detect logic and threshold compare. For valid values of \e compSrc refer to
//! enum \e ADC_PPBCompSource.
//!
//! \return None
//
//*****************************************************************************
static inline void
ADC_selectPPBCompareSource(uint32_t base, ADC_PPBNumber ppbNumber,
                           uint16_t compSrc)
{
    uint32_t ppbOffset;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));
    ASSERT(compSrc <= 2U);

    //
    // Get the offset to the appropriate PPB configuration register.
    //
    ppbOffset = (ADC_PPBxCONFIG2_STEP * (uint32_t)ppbNumber) +
                    ADC_O_PPB1CONFIG2;

    //
    // Select PPB compare source..
    //
    HWREGH(base + ppbOffset) =
                 (HWREGH(base + ppbOffset) & ~(ADC_PPB1CONFIG2_COMPSEL_M)) |
                 (compSrc << ADC_PPB1CONFIG2_COMPSEL_S);
}

//*****************************************************************************
//
//! Reads the oversampled final sum from the PPB.
//!
//! \param resultBase is the base address of the ADC results.
//! \param ppbNumber is the number of the post-processing block.
//!
//! This function returns the processed sum of results that corresponds to
//! the base address passed into \e resultBase and the PPB passed into
//! \e ppbNumber.
//!
//! \note Take care that you are using a base address for the result registers
//! (ADCxRESULT_BASE) and not a base address for the control registers.
//!
//! \return Returns the oversampled final sum value.
//
//*****************************************************************************
static inline int32_t
ADC_readPPBSum(uint32_t resultBase, ADC_PPBNumber ppbNumber)
{
    //
    // Check the arguments.
    //
    ASSERT(
           (resultBase == ADCARESULT_BASE) ||
           (resultBase == ADCBRESULT_BASE) ||
           (resultBase == ADCCRESULT_BASE)
          );
    //
    // Return the result of selected PPB.
    //
    return((int32_t)HWREG(resultBase + (uint32_t)ADC_PPBxSUM_OFFSET_BASE +
           ((uint32_t)ppbNumber * 4UL)));
}

//*****************************************************************************
//
//! Reads the oversampled final count from the PPB.
//!
//! \param resultBase is the base address of the ADC results.
//! \param ppbNumber is the number of the post-processing block.
//!
//! This function returns the oversampled final count that
//! corresponds to the base address passed into \e resultBase and the
//! PPB passed into \e ppbNumber.
//!
//! \note Take care that you are using a base address for the result registers
//! (ADCxRESULT_BASE) and not a base address for the control registers.
//!
//! \return Returns the oversampled final count value.
//
//*****************************************************************************
static inline uint32_t
ADC_readPPBCount(uint32_t resultBase, ADC_PPBNumber ppbNumber)
{
    //
    // Check the arguments.
    //
    ASSERT(
           (resultBase == ADCARESULT_BASE) ||
           (resultBase == ADCBRESULT_BASE) ||
           (resultBase == ADCCRESULT_BASE)
          );
    //
    // Return the final count of selected PPB.
    //
    return((uint32_t)HWREG(resultBase + (uint32_t)ADC_PPBxCOUNT_OFFSET_BASE +
           ((uint32_t)ppbNumber * 4UL)));
}

//*****************************************************************************
//
//! Reads the processed conversion result's maximum value from the PPB.
//!
//! \param resultBase is the base address of the ADC results.
//! \param ppbNumber is the number of the post-processing block.
//!
//! This function returns the oversampled final maximum that corresponds to
//! the base address passed into \e resultBase and the PPB passed into
//! \e ppbNumber.
//!
//! \note Take care that you are using a base address for the result registers
//! (ADCxRESULT_BASE) and not a base address for the control registers.
//!
//! \return Returns the oversampled final maximum value.
//
//*****************************************************************************
static inline int32_t
ADC_readPPBMax(uint32_t resultBase, ADC_PPBNumber ppbNumber)
{
    //
    // Check the arguments.
    //
    ASSERT(
           (resultBase == ADCARESULT_BASE) ||
           (resultBase == ADCBRESULT_BASE) ||
           (resultBase == ADCCRESULT_BASE)
          );
    //
    // Return the final maximum value of selected PPB.
    //
    return((int32_t)HWREG(resultBase + (uint32_t)ADC_PPBxMAX_OFFSET_BASE +
           ((uint32_t)ppbNumber * 8UL)));
}

//*****************************************************************************
//
//! Reads the processed conversion result's minimum value from the PPB.
//!
//! \param resultBase is the base address of the ADC results.
//! \param ppbNumber is the number of the post-processing block.
//!
//! This function returns the processed conversion result that corresponds to
//! the base address passed into \e resultBase and the PPB passed into
//! \e ppbNumber.
//!
//! \note Take care that you are using a base address for the result registers
//! (ADCxRESULT_BASE) and not a base address for the control registers.
//!
//! \return Returns the signed 32-bit conversion result.
//
//*****************************************************************************
static inline int32_t
ADC_readPPBMin(uint32_t resultBase, ADC_PPBNumber ppbNumber)
{
    //
    // Check the arguments.
    //
    ASSERT(
           (resultBase == ADCARESULT_BASE) ||
           (resultBase == ADCBRESULT_BASE) ||
           (resultBase == ADCCRESULT_BASE)
          );
    //
    // Return the final minimum value of selected PPB.
    //
    return((int32_t)HWREG(resultBase + (uint32_t)ADC_PPBxMIN_OFFSET_BASE +
           ((uint32_t)ppbNumber * 8UL)));
}

//*****************************************************************************
//
//! Reads the index of the result with maximum value from the PPB.
//!
//! \param resultBase is the base address of the ADC results.
//! \param ppbNumber is the number of the post-processing block.
//!
//! This function returns the index of the processed conversion's maximum value
//! that corresponds to the base address passed into \e resultBase and
//! the PPB passed into \e ppbNumber.
//!
//! \note Take care that you are using a base address for the result registers
//! (ADCxRESULT_BASE) and not a base address for the control registers.
//!
//! \return Returns the index of the result with maximum value.
//
//*****************************************************************************
static inline uint16_t
ADC_readPPBMaxIndex(uint32_t resultBase, ADC_PPBNumber ppbNumber)
{
    //
    // Check the arguments.
    //
    ASSERT(
           (resultBase == ADCARESULT_BASE) ||
           (resultBase == ADCBRESULT_BASE) ||
           (resultBase == ADCCRESULT_BASE)
          );

    //
    // Returns the index of the final maximum value of selected PPB.
    //
    return(HWREG(resultBase + (uint32_t)ADC_PPBxMAXI_OFFSET_BASE +
           ((uint32_t)ppbNumber * 8UL)));
}

//*****************************************************************************
//
//! Reads the index of the result with minimum value from the PPB.
//!
//! \param resultBase is the base address of the ADC results.
//! \param ppbNumber is the number of the post-processing block.
//!
//! This function returns the index of the processed conversion's minimum value
//! that corresponds to the base address passed into \e resultBase and
//! the PPB passed into \e ppbNumber.
//!
//! \note Take care that you are using a base address for the result registers
//! (ADCxRESULT_BASE) and not a base address for the control registers.
//!
//! \return Returns the index of the result with final minimum value.
//
//*****************************************************************************
static inline uint16_t
ADC_readPPBMinIndex(uint32_t resultBase, ADC_PPBNumber ppbNumber)
{
    //
    // Check the arguments.
    //
    ASSERT(
           (resultBase == ADCARESULT_BASE) ||
           (resultBase == ADCBRESULT_BASE) ||
           (resultBase == ADCCRESULT_BASE)
    );

    //
    // Returns the index of the final minimum value of the selected PPB.
    //
    return(HWREG(resultBase + (uint32_t)ADC_PPBxMINI_OFFSET_BASE +
            ((uint32_t)ppbNumber * 8UL)));
}


//*****************************************************************************
//
//! Reads the processed conversion result from the PPB.
//!
//! \param resultBase is the base address of the ADC results.
//! \param ppbNumber is the number of the post-processing block.
//!
//! This function returns the processed conversion result that corresponds to
//! the base address passed into \e resultBase and the PPB passed into
//! \e ppbNumber.
//!
//! \note Take care that you are using a base address for the result registers
//! (ADCxRESULT_BASE) and not a base address for the control registers.
//!
//! \return Returns the signed 32-bit conversion result.
//
//*****************************************************************************
static inline int32_t
ADC_readPPBResult(uint32_t resultBase, ADC_PPBNumber ppbNumber)
{
    //
    // Check the arguments.
    //
    ASSERT(
           (resultBase == ADCARESULT_BASE) ||
           (resultBase == ADCBRESULT_BASE) ||
           (resultBase == ADCCRESULT_BASE)
          );
    //
    // Return the result of selected PPB.
    //
    return((int32_t)HWREG(resultBase + (uint32_t)ADC_PPBxRESULT_OFFSET_BASE +
           ((uint32_t)ppbNumber * 2UL)));
}

//*****************************************************************************
//
//! Reads sample delay time stamp from a PPB.
//!
//! \param base is the base address of the ADC module.
//! \param ppbNumber is the number of the post-processing block.
//!
//! This function returns the sample delay time stamp. This delay is the number
//! of system clock cycles between the SOC being triggered and when it began
//! converting.
//!
//! \return Returns the delay time stamp.
//
//*****************************************************************************
static inline uint16_t
ADC_getPPBDelayTimeStamp(uint32_t base, ADC_PPBNumber ppbNumber)
{
    uint32_t ppbOffset;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Get the offset to the appropriate delay.
    //
    ppbOffset = (ADC_PPBxSTAMP_STEP * (uint32_t)ppbNumber) + ADC_O_PPB1STAMP;

    //
    // Return the delay time stamp.
    //
    return(HWREGH(base + ppbOffset) & ADC_PPB2STAMP_DLYSTAMP_M);
}

//*****************************************************************************
//
//! Sets the post processing block offset correction.
//!
//! \param base is the base address of the ADC module.
//! \param ppbNumber is the number of the post-processing block.
//! \param offset is the 10-bit signed value subtracted from ADC the output.
//!
//! This function sets the PPB offset correction value.  This value can be used
//! to digitally remove any system-level offset inherent in the ADCIN circuit
//! before it is stored in the appropriate result register. The \e offset
//! parameter is \b subtracted from the ADC output and is a signed value from
//! -512 to 511 inclusive. For example, when \e offset = 1, ADCRESULT = ADC
//! output - 1. When \e offset = -512, ADCRESULT = ADC output - (-512) or ADC
//! output + 512.
//!
//! Passing a zero in to the \e offset parameter will effectively disable the
//! calculation, allowing the raw ADC result to be passed unchanged into the
//! result register.
//!
//! \note If multiple PPBs are applied to the same SOC, the offset that will be
//! applied will be that of the PPB with the highest number.
//!
//! \return None
//
//*****************************************************************************
static inline void
ADC_setPPBCalibrationOffset(uint32_t base, ADC_PPBNumber ppbNumber,
                            int16_t offset)
{
    uint32_t ppbOffset;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Get the offset to the appropriate offset register.
    //
    ppbOffset = (ADC_PPBxOFFCAL_STEP * (uint32_t)ppbNumber) + ADC_O_PPB1OFFCAL;

    //
    // Write the offset amount.
    //
    EALLOW;
    HWREGH(base + ppbOffset) = (HWREGH(base + ppbOffset) &
                                ~ADC_PPB1OFFCAL_OFFCAL_M) |
                               ((uint16_t)offset & ADC_PPB1OFFCAL_OFFCAL_M);
    EDIS;
}

//*****************************************************************************
//
//! Sets the post processing block reference offset.
//!
//! \param base is the base address of the ADC module.
//! \param ppbNumber is the number of the post-processing block.
//! \param offset is the 16-bit unsigned value subtracted from ADC the output.
//!
//! This function sets the PPB reference offset value. This can be used to
//! either calculate the feedback error or convert a unipolar signal to bipolar
//! by subtracting a reference value. The result will be stored in the
//! appropriate PPB result register which can be read using ADC_readPPBResult().
//!
//! Passing a zero in to the \e offset parameter will effectively disable the
//! calculation and will pass the ADC result to the PPB result register
//! unchanged.
//!
//! \note If in 12-bit mode, you may only pass a 12-bit value into the \e offset
//! parameter.
//!
//! \return None
//
//*****************************************************************************
static inline void
ADC_setPPBReferenceOffset(uint32_t base, ADC_PPBNumber ppbNumber,
                          uint16_t offset)
{
    uint32_t ppbOffset;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Get the offset to the appropriate offset register.
    //
    ppbOffset = (ADC_PPBxOFFREF_STEP * (uint32_t)ppbNumber) + ADC_O_PPB1OFFREF;

    //
    // Write the offset amount.
    //
    HWREGH(base + ppbOffset) = offset;
}

//*****************************************************************************
//
//! Enables two's complement capability in the PPB.
//!
//! \param base is the base address of the ADC module.
//! \param ppbNumber is the number of the post-processing block.
//!
//! This function enables two's complement in the post-processing block
//! specified by the \e ppbNumber parameter. When enabled, a two's complement
//! will be performed on the output of the offset subtraction before it is
//! stored in the appropriate PPB result register. In other words, the PPB
//! result will be the reference offset value minus the the ADC result value
//! (ADCPPBxRESULT = ADCSOCxOFFREF - ADCRESULTx).
//!
//! \return None
//
//*****************************************************************************
static inline void
ADC_enablePPBTwosComplement(uint32_t base, ADC_PPBNumber ppbNumber)
{
    uint32_t ppbOffset;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Get the offset to the appropriate PPB configuration register.
    //
    ppbOffset = (ADC_PPBxCONFIG_STEP * (uint32_t)ppbNumber) + ADC_O_PPB1CONFIG;

    //
    // Enable PPB two's complement.
    //
    EALLOW;
    HWREGH(base + ppbOffset) |= ADC_PPB1CONFIG_TWOSCOMPEN;
    EDIS;
}

//*****************************************************************************
//
//! Disables two's complement capability in the PPB.
//!
//! \param base is the base address of the ADC module.
//! \param ppbNumber is the number of the post-processing block.
//!
//! This function disables two's complement in the post-processing block
//! specified by the \e ppbNumber parameter. When disabled, a two's complement
//! will \b NOT be performed on the output of the offset subtraction before it
//! is stored in the appropriate PPB result register. In other words, the PPB
//! result will be the ADC result value minus the reference offset value
//! (ADCPPBxRESULT = ADCRESULTx - ADCSOCxOFFREF).
//!
//! \return None
//
//*****************************************************************************
static inline void
ADC_disablePPBTwosComplement(uint32_t base, ADC_PPBNumber ppbNumber)
{
    uint32_t ppbOffset;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Get the offset to the appropriate PPB configuration register.
    //
    ppbOffset = (ADC_PPBxCONFIG_STEP * (uint32_t)ppbNumber) + ADC_O_PPB1CONFIG;

    //
    // Disable PPB two's complement.
    //
    EALLOW;
    HWREGH(base + ppbOffset) &= ~ADC_PPB1CONFIG_TWOSCOMPEN;
    EDIS;
}

//*****************************************************************************
//
//! Enables the extended low limit in the PPB.
//!
//! \param base is the base address of the ADC module.
//! \param ppbNumber is the number of the post-processing block.
//!
//! This function enables the low limit for PPB by allowing the PPB low
//! limit to be set by ADCPPBxTRIPLO2 register.
//!
//! \return None
//
//*****************************************************************************
static inline void
ADC_enablePPBExtendedLowLimit(uint32_t base, ADC_PPBNumber ppbNumber)
{
    uint32_t ppbLoOffset;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Get the offset to the appropriate trip limit registers.
    //
    ppbLoOffset = (ADC_PPBxTRIPLO_STEP * (uint32_t)ppbNumber) +
                  ADC_O_PPB1TRIPLO;

    //
    // Enable PPB extended low limit.
    //
    EALLOW;
    HWREG(base + ppbLoOffset) |= ADC_PPB1TRIPLO_LIMITLO2EN;
    EDIS;
}

//*****************************************************************************
//
//! Disables extended low limit capability in the PPB.
//!
//! \param base is the base address of the ADC module.
//! \param ppbNumber is the number of the post-processing block.
//!
//! This function disables the low limit for PPB by allowing the PPB low
//! limit to be set by ADCPPBxTRIPLO register.
//!
//! \return None
//
//*****************************************************************************
static inline void
ADC_disablePPBExtendedLowLimit(uint32_t base, ADC_PPBNumber ppbNumber)
{
    uint32_t ppbOffset;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Get the offset to the appropriate PPB configuration register.
    //
    ppbOffset = (ADC_PPBxCONFIG_STEP * (uint32_t)ppbNumber) + ADC_O_PPB1CONFIG;

    //
    // Disable PPB extended low limit.
    //
    EALLOW;
    HWREG(base + ppbOffset) &= ~ADC_PPB1TRIPLO_LIMITLO2EN;
    EDIS;
}

//*****************************************************************************
//
//! Enables an ADC interrupt source.
//!
//! \param base is the base address of the ADC module.
//! \param adcIntNum is interrupt number within the ADC wrapper.
//!
//! This function enables the indicated ADC interrupt source.  Only the
//! sources that are enabled can be reflected to the processor interrupt.
//! Disabled sources have no effect on the processor.
//!
//! \e adcIntNum can take the value \b ADC_INT_NUMBER1,
//! \b ADC_INT_NUMBER2, \b ADC_INT_NUMBER3 or \b ADC_INT_NUMBER4 to express
//! which of the four interrupts of the ADC module should be enabled.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_enableInterrupt(uint32_t base, ADC_IntNumber adcIntNum)
{
    uint32_t intRegAddr;
    uint16_t shiftVal;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Each INTSEL register manages two interrupts. If the interrupt number is
    // even, we'll be accessing the upper byte and will need to shift.
    //
    intRegAddr = base + ADC_INTSELxNy_OFFSET_BASE + ((uint32_t)adcIntNum >> 1);
    shiftVal = ((uint16_t)adcIntNum & 0x1U) << 3U;

    //
    // Enable the specified ADC interrupt.
    //
    EALLOW;

    HWREGH(intRegAddr) |= ADC_INTSEL1N2_INT1E << shiftVal;

    EDIS;
}

//*****************************************************************************
//
//! Disables an ADC interrupt source.
//!
//! \param base is the base address of the ADC module.
//! \param adcIntNum is interrupt number within the ADC wrapper.
//!
//! This function disables the indicated ADC interrupt source.
//! Only the sources that are enabled can be reflected to the processor
//! interrupt. Disabled sources have no effect on the processor.
//!
//! \e adcIntNum can take the value \b ADC_INT_NUMBER1,
//! \b ADC_INT_NUMBER2, \b ADC_INT_NUMBER3 or \b ADC_INT_NUMBER4 to express
//! which of the four interrupts of the ADC module should be disabled.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_disableInterrupt(uint32_t base, ADC_IntNumber adcIntNum)
{
    uint32_t intRegAddr;
    uint16_t shiftVal;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Each INTSEL register manages two interrupts. If the interrupt number is
    // even, we'll be accessing the upper byte and will need to shift.
    //
    intRegAddr = base + ADC_INTSELxNy_OFFSET_BASE + ((uint32_t)adcIntNum >> 1);
    shiftVal = ((uint16_t)adcIntNum & 0x1U) << 3U;

    //
    // Disable the specified ADC interrupt.
    //
    EALLOW;

    HWREGH(intRegAddr) &= ~(ADC_INTSEL1N2_INT1E << shiftVal);

    EDIS;
}

//*****************************************************************************
//
//! Sets the source EOC for an analog-to-digital converter interrupt.
//!
//! \param base is the base address of the ADC module.
//! \param adcIntNum is interrupt number within the ADC wrapper.
//! \param socNumber is the number of the start-of-conversion.
//!
//! This function sets which conversion is the source of an ADC interrupt.
//!
//! The \e intTrigger number is a value \b ADC_INT_TRIGGER_X where X specifies
//! the interrupt trigger to be configured for the ADC module specified by
//! \e base. Refer \b ADC_IntTrigger enum for valid values for this input.
//!
//! \e adcIntNum can take the value \b ADC_INT_NUMBER1,
//! \b ADC_INT_NUMBER2, \b ADC_INT_NUMBER3 or \b ADC_INT_NUMBER4 to express
//! which of the four interrupts of the ADC module is being configured.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_setInterruptSource(uint32_t base, ADC_IntNumber adcIntNum,
                       uint16_t intTrigger)
{
    uint32_t intRegAddr;
    uint16_t shiftVal;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));
    ASSERT(intTrigger < 20U);

    //
    // Each INTSEL register manages two interrupts. If the interrupt number is
    // even, we'll be accessing the upper byte and will need to shift.
    //
    intRegAddr = base + ADC_INTSELxNy_OFFSET_BASE + ((uint32_t)adcIntNum >> 1);
    shiftVal = ((uint16_t)adcIntNum & 0x1U) << 3U;

    //
    // Set the specified ADC interrupt source.
    //
    EALLOW;

    HWREGH(intRegAddr) =
        (HWREGH(intRegAddr) & ~(ADC_INTSEL1N2_INT1SEL_M << shiftVal)) |
        ((uint16_t)intTrigger << shiftVal);

    EDIS;
}

//*****************************************************************************
//
//! Enables continuous mode for an ADC interrupt.
//!
//! \param base is the base address of the ADC.
//! \param adcIntNum is interrupt number within the ADC wrapper.
//!
//! This function enables continuous mode for the ADC interrupt passed into
//! \e adcIntNum. This means that pulses will be generated for the specified
//! ADC interrupt whenever an EOC pulse is generated irrespective of whether or
//! not the flag bit is set.
//!
//! \e adcIntNum can take the value \b ADC_INT_NUMBER1,
//! \b ADC_INT_NUMBER2, \b ADC_INT_NUMBER3 or \b ADC_INT_NUMBER4 to express
//! which of the four interrupts of the ADC module is being configured.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_enableContinuousMode(uint32_t base, ADC_IntNumber adcIntNum)
{
    uint32_t intRegAddr;
    uint16_t shiftVal;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Each INTSEL register manages two interrupts. If the interrupt number is
    // even, we'll be accessing the upper byte and will need to shift.
    //
    intRegAddr = base + ADC_INTSELxNy_OFFSET_BASE + ((uint32_t)adcIntNum >> 1);
    shiftVal = ((uint16_t)adcIntNum & 0x1U) << 3U;

    //
    // Enable continuous mode for the specified ADC interrupt.
    //
    EALLOW;

    HWREGH(intRegAddr) |= ADC_INTSEL1N2_INT1CONT << shiftVal;

    EDIS;
}

//*****************************************************************************
//
//! Disables continuous mode for an ADC interrupt.
//!
//! \param base is the base address of the ADC.
//! \param adcIntNum is interrupt number within the ADC wrapper.
//!
//! This function disables continuous mode for the ADC interrupt passed into
//! \e adcIntNum. This means that pulses will not be generated for the
//! specified ADC interrupt until the corresponding interrupt flag for the
//! previous interrupt occurrence has been cleared using
//! ADC_clearInterruptStatus().
//!
//! \e adcIntNum can take the value \b ADC_INT_NUMBER1,
//! \b ADC_INT_NUMBER2, \b ADC_INT_NUMBER3 or \b ADC_INT_NUMBER4 to express
//! which of the four interrupts of the ADC module is being configured.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_disableContinuousMode(uint32_t base, ADC_IntNumber adcIntNum)
{
    uint32_t intRegAddr;
    uint16_t shiftVal;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Each INTSEL register manages two interrupts. If the interrupt number is
    // even, we'll be accessing the upper byte and will need to shift.
    //
    intRegAddr = base + ADC_INTSELxNy_OFFSET_BASE + ((uint32_t)adcIntNum >> 1);
    shiftVal = ((uint16_t)adcIntNum & 0x1U) << 3U;

    //
    // Disable continuous mode for the specified ADC interrupt.
    //
    EALLOW;

    HWREGH(intRegAddr) &= ~(ADC_INTSEL1N2_INT1CONT << shiftVal);

    EDIS;
}

//*****************************************************************************
//
//! Converts temperature from sensor reading to degrees C
//!
//! \param tempResult is the raw ADC A conversion result from the temp sensor.
//! \param vref is the reference voltage being used (for example 3.3 for 3.3V).
//! \param refMode is the reference mode being used (\b ADC_REFERENCE_INTERNAL
//!        or \b ADC_REFERENCE_EXTERNAL).
//!
//! This function converts temperature from temp sensor reading to degrees C.
//! Temp sensor values in production test are derived with 2.5V reference.
//! The \b vref argument in the function is used to scale the temp sensor
//! reading accordingly if temp sensor value is read at a different VREF
//! setting.
//!
//! \return Returns the temperature sensor reading converted to degrees C.
//
//*****************************************************************************
static inline int16_t
ADC_getTemperatureC(uint16_t tempResult, ADC_ReferenceMode refMode,
                        float32_t vref)
{
    float32_t temp;

    //
    // Read temp sensor slope and offset locations from OTP and convert
    //
    temp = (float32_t)tempResult * (vref / 2.5F);
    if(refMode == ADC_REFERENCE_INTERNAL)
    {
        return((int16_t)((((int32_t)temp - ADC_INT_REF_TSOFFSET) * 4096) /
                         ADC_INT_REF_TSSLOPE));
    }
    else
    {
        return((int16_t)((((int32_t)temp - ADC_EXT_REF_TSOFFSET) * 4096) /
                         ADC_EXT_REF_TSSLOPE));
    }
}

//*****************************************************************************
//
//! Converts temperature from sensor reading to degrees K
//!
//! \param tempResult is the raw ADC A conversion result from the temp sensor.
//! \param vref is the reference voltage being used (for example 3.3 for 3.3V).
//! \param refMode is the reference mode being used (\b ADC_REFERENCE_INTERNAL
//!        or \b ADC_REFERENCE_EXTERNAL).
//!
//! This function converts temperature from temp sensor reading to degrees K.
//! Temp sensor values in production test are derived with 2.5V reference.
//! The \b vref argument in the function is used to scale the temp sensor
//! reading accordingly if temp sensor value is read at a different VREF
//! setting.
//!
//! \return Returns the temperature sensor reading converted to degrees K.
//
//*****************************************************************************
static inline int16_t
ADC_getTemperatureK(uint16_t tempResult, ADC_ReferenceMode refMode,
                        float32_t vref)
{
    float32_t temp;

    //
    // Read temp sensor slope and offset locations from OTP and convert
    //
    temp = (float32_t)tempResult * (vref / 2.5F);
    if(refMode == ADC_REFERENCE_INTERNAL)
    {
        return((int16_t)(((((int32_t)temp - ADC_INT_REF_TSOFFSET) * 4096) /
                         ADC_INT_REF_TSSLOPE) + 273));
    }
    else
    {
        return((int16_t)(((((int32_t)temp - ADC_EXT_REF_TSOFFSET) * 4096) /
                         ADC_EXT_REF_TSSLOPE) + 273));
    }
}
//*****************************************************************************
//
//! Configures the safety checker result for a selected SOC.
//!
//! \param base is the base address of the ADC module.
//! \param socNumber is the number of the start-of-conversion.
//! \param scInput is the desired input configuration.
//!
//! This function configures the safety checker input for the desired SOC.
//!
//! The \e socNumber number is a value \b ADC_SOC_NUMBERX where X is a number
//! from 0 to 15 specifying which SOC is to be configured on the ADC module
//! specified by \e base.
//!
//! The \e scInput is the desired safety checker input configuration.
//! Valid values can be refered from the enum \e ADC_SafetyCheckerInput.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_configSOCSafetyCheckerInput(uint32_t base, ADC_SOCNumber socNumber,
                                ADC_SafetyCheckerInput scInput)
{
    uint32_t socShift;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Calculate the SOC shift.
    //
    socShift = ((uint32_t)socNumber * 2U);

    //
    // Configure the Safety Checker Result mode.
    //
    HWREG(base + ADC_O_SAFECHECKRESEN) =
                          (HWREG(base + ADC_O_SAFECHECKRESEN)             &
                           ~(ADC_SAFECHECKRESEN_SOC0CHKEN_M << socShift)) |
                          ((uint32_t)scInput << socShift);
}

//
// ADC_SAFECHECK_REGS
//*****************************************************************************
//
//! \internal
//! Checks the Safety Checker base address.
//!
//! \param base specifies the ADC Safety Checker module base address.
//!
//! This function determines if a ADC Safety Checker module base address is
//! valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool
ADC_isSafetyCheckerBaseValid(uint32_t base)
{
    return(
           (base == ADCSAFETYCHK1_BASE) ||
           (base == ADCSAFETYCHK2_BASE) ||
           (base == ADCSAFETYCHK3_BASE) ||
           (base == ADCSAFETYCHK4_BASE) ||
           (base == ADCSAFETYCHK5_BASE) ||
           (base == ADCSAFETYCHK6_BASE) ||
           (base == ADCSAFETYCHK7_BASE) ||
           (base == ADCSAFETYCHK8_BASE)
          );
}
#endif

//*****************************************************************************
//
//! Enables the ADC result safety checker module.
//!
//! \param scBase is the base address of the ADC Safety Checker module.
//!
//! This function enables the ADC result safety checker module.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_enableSafetyChecker(uint32_t scBase)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isSafetyCheckerBaseValid(scBase));

    //
    // Enable the Saftey Checker module
    //
    HWREGH(scBase + ADC_O_CHECKCONFIG) |= ADC_CHECKCONFIG_CHKEN;
}

//*****************************************************************************
//
//! Disables the ADC result safety checker module.
//!
//! \param scBase is the base address of the ADC Safety Checker module.
//!
//! This function disables the ADC result safety checker module.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_disableSafetyChecker(uint32_t scBase)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isSafetyCheckerBaseValid(scBase));

    //
    // Disable the Saftey Checker module.
    //
    HWREGH(scBase + ADC_O_CHECKCONFIG) &= ~ADC_CHECKCONFIG_CHKEN;
}

//*****************************************************************************
//
//! Forces the software sync for the safety checker module
//!
//! \param scBase is the base address of the safety checker module.
//!
//! This function forces the software sync for the safety checker module.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_forceSafetyCheckerSync(uint32_t scBase)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isSafetyCheckerBaseValid(scBase));

    //
    // Force software sync for the safety checker module.
    //
    HWREGH(scBase + ADC_O_CHECKCONFIG) |= ADC_CHECKCONFIG_SWSYNC;
}

//*****************************************************************************
//
//! Returns the status of the safey checker module.
//!
//! \param scBase is the base address of the ADC safety checker module.
//!
//! This function configures the external channel for an SOC by configuring
//! the external channel mux for an SOC.
//!
//! \return Returns the status of the safety checker module. Valid values
//! are any of the follwing values or any of their OR'd combination:
//! - \e ADC_SAFECHECK_RESULT1_READY
//! - \e ADC_SAFECHECK_RESULT2_READY
//! - \e ADC_SAFECHECK_RESULT1_OOT
//
//*****************************************************************************
static inline uint16_t
ADC_getSafetyCheckerStatus(uint32_t scBase)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isSafetyCheckerBaseValid(scBase));

    //
    // Returns Safety Checker module status
    //
    return(HWREGH(scBase + ADC_O_CHECKSTATUS) & ADC_SAFECHECK_STATUS_MASK);
}

//*****************************************************************************
//
//! Configures the safety checker module.
//!
//! \param scBase is the base address of the ADC safety checker module.
//! \param scInst is the safety checker instance to be configured.
//! \param adcInst is the desired ADC instance.
//! \param adcResultInst is the desired ADC result instance.
//!
//! This function configures the selected checker instance of a safety checker
//! instance.
//!
//! The \e checkInst parameter can take values defined by enum
//! \b ADC_SafetyCheckInst. The \e adcInst parameter can take values defined
//! by enum \b ADC_Select. The \e adcResultInst parameter can take values
//! defined by enum \b ADC_ResultSelect.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_configureSafetyChecker(uint32_t scBase, ADC_SafetyCheckInst checkInst,
                           ADC_Select adcInst, ADC_ResultSelect adcResultInst)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isSafetyCheckerBaseValid(scBase));

    //
    // Configure safety checker instance
    //
    HWREGH(scBase + ADC_O_RESSEL1 + (uint16_t)checkInst) =
                        (HWREGH(scBase + ADC_O_RESSEL1 + (uint16_t)checkInst) &
                        (ADC_RESSEL1_ADCSEL_M | ADC_RESSEL1_ADCRESULTSEL_M)) |
                        (((uint16_t)adcInst << ADC_RESSEL1_ADCSEL_S) |
                         ((uint16_t)adcResultInst << ADC_RESSEL1_ADCRESULTSEL_S));
}

//*****************************************************************************
//
//! Configures the tolerance allowed between safety check results.
//!
//! \param scBase is the base address of the ADC module.
//! \param tolerance is the number of the start-of-conversion.
//!
//! This function configures the tolerance for the difference between
//! check result instances of the selected safety checker instance.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_setSafetyCheckerTolerance(uint32_t scBase, uint32_t tolerance)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isSafetyCheckerBaseValid(scBase));
    ASSERT(tolerance <= ADC_TOLERANCE_TOLERANCE_M);

    //
    // Set safety checker tolerance
    //
    HWREGH(scBase + ADC_O_TOLERANCE) = (tolerance & ADC_TOLERANCE_TOLERANCE_M);
}

//*****************************************************************************
//
//! Returns the safety check result for the selected instance.
//!
//! \param scBase is the base address of the ADC module.
//! \param checkInst is the number of the start-of-conversion.
//!
//! This function returns the safety check result for the selected instance.
//!
//! The \e checkInst number is a value \b ADC_SAFETY_CHECKx where x is a number
//! from 1 to 2 specifying the safety result check instances available in the
//! safety checker instance specified by \e scBase.
//!
//!
//! \return Returns the safety checker result for the desired instance.
//
//*****************************************************************************
static inline uint32_t
ADC_getSafetyCheckerResult(uint32_t scBase, ADC_SafetyCheckInst checkInst)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isSafetyCheckerBaseValid(scBase));

    //
    // Returns the safety check result for the selected instance
    //
    return(HWREG(scBase + ADC_O_CHECKRESULT1 + (uint16_t)checkInst) &
           ADC_CHECKRESULT1_RESULT_M);
}

//
// ADC_SAFECHECK_INTEVT_REGS
//*****************************************************************************
//
//! \internal
//! Checks the Safety Checker INTEVT base address.
//!
//! \param base specifies the ADC Safety Checker INTEVT module base address.
//!
//! This function determines if a ADC Safety Checker INTEVT module base address
//! is valid.
//!
//! \return Returns \b true if the base address is valid and \b false
//! otherwise.
//
//*****************************************************************************
#ifdef DEBUG
static inline bool
ADC_isSafeCheckINTEVTBaseValid(uint32_t base)
{
    return(
            (base == ADCSAFETYINTEVTAGG1_BASE) ||
            (base == ADCSAFETYINTEVTAGG2_BASE)
          );
}
#endif

//*****************************************************************************
//
//! Enables the safety checker event sources for selected instance.
//!
//! \param scIntEvtBase is the base address of ADC Safe Check INTEVT module.
//! \param checkResult is the desired ADC Safety Checker result.
//! \param checkEvent is the desired event number.
//! \param checkerNumber is the number of the checker tile.
//!
//! This function enables the indicated safety checker event sources.
//!
//! The \e checkResult specifies the result of the OOT or OVF events. It should
//! be one of the following values.
//!
//! - \b ADC_SAFETY_CHECK_RESULT1
//! - \b ADC_SAFETY_CHECK_RESULT2
//! - \b ADC_SAFETY_CHECK_OOT
//!
//! The \e checkEvent is a value \b ADC_SAFETY_CHECK_EVENTx where x is
//! a number from 1 to 4 specifying the safety check events available in
//! the safety checker specified by \e scIntEvtBase.
//!
//! The \e checkerNumber number is a value \b ADC_SAFETY_CHECKERx where x is
//! a number from 1 to 8 specifying which Checker Tile is to be selected in
//! the ADC module.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_enableSafetyCheckEvt(uint32_t scIntEvtBase, ADC_Checker checkerNumber,
            ADC_SafetyCheckEvent checkEvent, ADC_SafetyCheckResult checkResult)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isSafeCheckINTEVTBaseValid(scIntEvtBase));

    //
    // Enables the safety checker event source.
    //
    HWREG(scIntEvtBase + ADC_O_CHECKEVT1SEL1 + (uint32_t)checkEvent +
                    (uint32_t)checkResult) |= (1UL << (uint32_t)checkerNumber);
}

//*****************************************************************************
//
//! Disables the safety checker event sources for selected instance.
//!
//! \param scIntEvtBase is the base address of ADC Safe Check INTEVT module.
//! \param checkResult is the desired ADC Safety Checker result.
//! \param checkEvent is the desired event number.
//! \param checkerNumber is the number of the checker tile.
//!
//! This function disables the indicated safety checker event sources.
//!
//! The \e checkResult specifies the result of the OOT or OVF events. It should
//! be one of the following values.
//!
//! - \b ADC_SAFETY_CHECK_RESULT1
//! - \b ADC_SAFETY_CHECK_RESULT2
//! - \b ADC_SAFETY_CHECK_OOT
//!
//! The \e checkEvent is a value \b ADC_SAFETY_CHECK_EVENTx where x is
//! a number from 1 to 4 specifying the safety check events available in
//! the safety checker specified by \e scIntEvtBase.
//!
//! The \e checkerNumber number is a value \b ADC_CHECKER_NUMBERx where x is
//! a number from 1 to 8 specifying which Checker Tile is to be selected in
//! the ADC module.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_disableSafetyCheckEvt(uint32_t scIntEvtBase, ADC_Checker checkerNumber,
            ADC_SafetyCheckEvent checkEvent, ADC_SafetyCheckResult checkResult)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isSafeCheckINTEVTBaseValid(scIntEvtBase));

    //
    // Disables the safety checker event source.
    //
    HWREG(scIntEvtBase + ADC_O_CHECKEVT1SEL1 + (uint32_t)checkEvent +
                   (uint32_t)checkResult) &= ~(1UL << (uint32_t)checkerNumber);
}

//*****************************************************************************
//
//! Enables the safety checker interrupt sources for selected instance.
//!
//! \param scIntEvtBase is the base address of ADC Safe Check INTEVT module.
//! \param checkResult is the desired ADC Safety Checker interrupt result.
//! \param checkerNumber is the number of the checker tile.
//!
//! This function enables the indicated safety checker interrupt sources.
//!
//! The \e checkResult specifies the result of the OOT or OVF events. It should
//! be one of the following values.
//!
//! - \b ADC_SAFETY_CHECK_RESULT1
//! - \b ADC_SAFETY_CHECK_RESULT2
//! - \b ADC_SAFETY_CHECK_OOT
//!
//! The \e checkerNumber number is a value \b ADC_CHECKER_NUMBERx where x is
//! a number from 1 to 8 specifying which Checker Tile is to be selected in
//! the ADC module.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_enableSafetyCheckInt(uint32_t scIntEvtBase, ADC_Checker checkerNumber,
                         ADC_SafetyCheckResult checkResult)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isSafeCheckINTEVTBaseValid(scIntEvtBase));

    //
    // Enables the safety checker interrupt source.
    //
    HWREG(scIntEvtBase + ADC_O_CHECKINTSEL1 + (uint32_t)checkResult) |=
                                              (1UL << (uint32_t)checkerNumber);
}

//*****************************************************************************
//
//! Disables the safety checker interrupt sources for selected instance.
//!
//! \param scIntEvtBase is the base address of ADC Safe Check INTEVT module.
//! \param checkResult is the desired ADC Safety Checker interrupt result.
//! \param checkerNumber is the number of the checker tile.
//!
//! This function disables the indicated safety checker interrupt sources.
//!
//! The \e checkResult specifies the result of the OOT or OVF events. It should
//! be one of the following values.
//!
//! - \b ADC_SAFETY_CHECK_RESULT1
//! - \b ADC_SAFETY_CHECK_RESULT2
//! - \b ADC_SAFETY_CHECK_OOT
//!
//! The \e checkerNumber number is a value \b ADC_CHECKER_NUMBERx where x is
//! a number from 1 to 8 specifying which Checker Tile is to be selected in
//! the ADC module.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_disableSafetyCheckInt(uint32_t scIntEvtBase, ADC_Checker checkerNumber,
                          ADC_SafetyCheckResult checkResult)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isSafeCheckINTEVTBaseValid(scIntEvtBase));

    //
    // Enables the safety checker interrupt source.
    //
    HWREG(scIntEvtBase + ADC_O_CHECKINTSEL1 + (uint32_t)checkResult) &=
                                             ~(1UL << (uint32_t)checkerNumber);
}

//*****************************************************************************
//
//! Get the ADC safety checker OOT and OVF event status.
//!
//! \param scIntEvtBase is the base address of ADC Safe Check INTEVT module.
//! \param checkerFlag is the desired ADC Safety Checker event status.
//! \param checkerNumber is the number of the checker tile.
//!
//! This function returns the event status for the OOT or OVF event.
//!
//! The \e checkerFlag specifies the ADC safety checker event status of
//! OOT or OVF events. It should be one of the following values.
//!
//! - \b ADC_SAFETY_CHECK_OOT_FLG
//! - \b ADC_SAFETY_CHECK_RES1OVF_FLG
//! - \b ADC_SAFETY_CHECK_RES2OVF_FLG
//!
//! The \e checkerNumber number is a value \b ADC_SAFETY_CHECKERx where x is
//! a number from 1 to 8 specifying which Checker Tile is to be selected in
//! the ADC module specified by \e scIntEvtBase.
//!
//! \return Returns the status of the safety checker event module for
//! the selected instance.
//
//*****************************************************************************
static inline bool
ADC_getSafetyCheckStatus(uint32_t scIntEvtBase, ADC_Checker checkerNumber,
                            ADC_SafetyCheckFlag checkerFlag)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isSafeCheckINTEVTBaseValid(scIntEvtBase));

    //
    // Get the specified safety checker event status.
    //
    return(HWREG(scIntEvtBase + ADC_O_OOTFLG + (uint32_t)checkerFlag) &
                                              (1U << (uint32_t)checkerNumber));
}

//*****************************************************************************
//
//! Clears the ADC safety checker OOT and OVF event status.
//!
//! \param scIntEvtBase is the base address of ADC Safe Check INTEVT module.
//! \param checkerFlag is the desired ADC Safety Checker event status.
//! \param checkerNumber is the number of the checker tile.
//!
//! This funtion clears the specified ADC Safety Checker event status so that
//! they no longer assert.
//!
//! \e checkerFlag takes one of the values \b ADC_SAFETY_CHECK_OOT_FLG,
//! \b ADC_SAFETY_CHECK_RES1OVF_FLG or \b ADC_SAFETY_CHECK_RES2OVF_FLG
//! to express which of the three event status of the ADC Safety Checker should
//! be cleared.
//!
//! The \e checkerNumber number is a value \b ADC_SAFETY_CHECKERx where x is
//! a number from 1 to 8 specifying which Checker Tile is to be selected in
//! the ADC module specified by \e scIntEvtBase.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_clearSafetyCheckStatus(uint32_t scIntEvtBase, ADC_Checker checkerNumber,
                            ADC_SafetyCheckFlag checkerFlag)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isSafeCheckINTEVTBaseValid(scIntEvtBase));

    //
    // Clear the specified safety checker event status.
    //
    HWREG(scIntEvtBase + ADC_O_OOTFLGCLR + (uint32_t)checkerFlag) =
                                                1UL << (uint32_t)checkerNumber;
}

//*****************************************************************************
//
//! Get the ADC safety checker interrupt status.
//!
//! \param scIntEvtBase is the base address of ADC Safe Check INTEVT module.
//!
//! This function returns the interrupt status for the OOT or OVF event.
//!
//! \return Returns the status of the safety checker interrupt for
//! the selected instance.
//
//*****************************************************************************
static inline uint32_t
ADC_getSafetyCheckIntStatus(uint32_t scIntEvtBase)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isSafeCheckINTEVTBaseValid(scIntEvtBase));
    //
    // Get the specified safety checker interrupt status.
    //
    return(HWREG(scIntEvtBase + ADC_O_CHECKINTFLG));

}

//*****************************************************************************
//
//! Clears the ADC safety checker interrupt status.
//!
//! \param scIntEvtBase is the base address of ADC Safe Check INTEVT module.
//! \param checkerNumber is the number of the checker tile.
//!
//! This funtion clears the specified ADC Safety Checker interrupt status
//! so that they no longer assert.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_clearSafetyCheckIntStatus(uint32_t scIntEvtBase)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isSafeCheckINTEVTBaseValid(scIntEvtBase));
    //
    // Clear the specified safety checker interrupt status.
    //
    HWREG(scIntEvtBase + ADC_O_CHECKINTFLGCLR) = 1U;
}

//*****************************************************************************
//
//! Configures the trigger repeater mode select.
//!
//! \param base is the base address of the ADC module.
//! \param repInstance is the repeater instance.
//! \param mode is the repeater mode.
//!
//! This function configures desired ADC trigger repeater mode that corresponds
//! to \e mode to select either oversampling or undersampling mode.
//!
//! The \e repInstance is the repeater instance to be configured. Valid values
//! for this parameter can be referred from the enum \e ADC_RepInstance.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_triggerRepeaterMode(uint32_t base, uint32_t repInstance, ADC_RepMode mode)
{
    uint32_t regOffset;
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    regOffset = base + (repInstance * (ADC_REPxCTL_STEP));

    //
    // Set the specified repeater trigger source to modify.
    //
    EALLOW;
    HWREG(regOffset + ADC_O_REP1CTL) = (HWREG(regOffset + ADC_O_REP1CTL) &
                                        ~(ADC_REP1CTL_MODE)) | (uint32_t)mode;
    EDIS;
}

//*****************************************************************************
//
//! Get the trigger repeater active mode status.
//!
//! \param base is the base address of the ADC module.
//! \param repInstance is the repeater instance.
//!
//! This function returns the status of the ADC trigger repeater mode for
//! the selected repeater instance.
//!
//! The \e repInstance is the repeater instance to be configured. Valid values
//! for this parameter can be referred from the enum \e ADC_RepInstance.
//!
//! \return Returns the status of the trigger repeater active mode.
//
//*****************************************************************************
static inline bool
ADC_triggerRepeaterActiveMode(uint32_t base, uint32_t repInstance)
{
    uint32_t regOffset;
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    regOffset = base + (repInstance * (ADC_REPxCTL_STEP));

    //
    // get the specified repeater trigger active mode status.
    //
    return(HWREG(regOffset + ADC_O_REP1CTL) &
                (1U << ADC_REP1CTL_ACTIVEMODE_S));
}

//*****************************************************************************
//
//! Get the trigger repeater module busy indication.
//!
//! \param base is the base address of the ADC module.
//! \param repInstance is the repeater instance.
//!
//! This function returns the status of the ADC trigger repeater module for
//! the selected repeater instance.
//!
//! The \e repInstance is the repeater instance to be configured. Valid values
//! for this parameter can be referred from the enum \e ADC_RepInstance.
//!
//! \return Returns the staus of the trigger repeater module busy.
//
//*****************************************************************************
static inline bool
ADC_triggerRepeaterModuleBusy(uint32_t base, uint32_t repInstance)
{
    uint32_t regOffset;
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    regOffset = base + (repInstance * (ADC_REPxCTL_STEP));

    //
    // get the specified repeater trigger active mode status.
    //
    return(HWREG(regOffset + ADC_O_REP1CTL) &
                (1U << ADC_REP1CTL_MODULEBUSY_S));
}

//*****************************************************************************
//
//! Configures the trigger source of the trigger repeater.
//!
//! \param base is the base address of the ADC module.
//! \param repInstance is the repeater instance.
//! \param trigger the source to modify via oversampling or undersampling.
//!
//! This function configures ADC trigger repeater by selecting the trigger
//! source passed into \e trigger to modify via oversampling or undersampling.
//!
//! The \e repInstance is the repeater instance to be configured. Valid values
//! for this parameter can be referred from the enum \e ADC_RepInstance.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_triggerRepeaterSelect(uint32_t base, uint16_t repInstance,
                          ADC_Trigger trigger)
{
    uint32_t regOffset;
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    regOffset = base + (repInstance * (ADC_REPxCTL_STEP));

    //
    // Set the specified repeater trigger source to modify.
    //
    EALLOW;
    HWREG(regOffset + ADC_O_REP1CTL) = (HWREG(regOffset + ADC_O_REP1CTL) &
                        ~((uint32_t)ADC_REP1CTL_TRIGGER_M)) |
                        ((uint32_t)trigger << ADC_REP1CTL_TRIGGER_S);
    EDIS;
}

//*****************************************************************************
//
//! Configures the trigger repeater syncin source.
//!
//! \param base is the base address of the ADC module.
//! \param repInstance is the repeater instance.
//! \param syncInput is the desired sync event to reset all counters.
//!
//! This function configures desired ADC trigger repeater sync event that
//! corresponds to \e syncInput to reset all counters and
//! any pending repeated triggers are discarded.
//!
//! The \e repInstance is the repeater instance to be configured. Valid values
//! for this parameter can be referred from the enum \e ADC_RepInstance.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_triggerRepeaterSyncIn(uint32_t base, uint16_t repInstance,
                          ADC_SyncInput syncInput)
{
    uint32_t regOffset;
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    regOffset = base + (repInstance * (ADC_REPxCTL_STEP));

    //
    // Set the specified trigger sync input.
    //
    EALLOW;
    HWREG(regOffset + ADC_O_REP1CTL) = (HWREG(regOffset + ADC_O_REP1CTL) &
                        ~((uint32_t)ADC_REP1CTL_SYNCINSEL_M)) |
                        ((uint32_t)syncInput << ADC_REP1CTL_SYNCINSEL_S);
    EDIS;
}

//*****************************************************************************
//
//!
//! Forces software sync for the trigger repeater block.
//!
//! \param base is the base address of the ADC module.
//! \param repInstance is the repeater instance.
//!
//! This function forces the software sync for the trigger repeater block.
//!
//! The \e repInstance is the repeater instance to be configured. Valid values
//! for this parameter can be referred from the enum \e ADC_RepInstance.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_forceRepeaterTriggerSync(uint32_t base, uint16_t repInstance)
{
    uint32_t regOffset;
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    regOffset = base + (repInstance * (ADC_REPxCTL_STEP));

    //
    // Force software sync for the trigger repeater block.
    //
    EALLOW;
    HWREG(regOffset + ADC_O_REP1CTL) |= ADC_REP1CTL_SWSYNC;
    EDIS;
}

//*****************************************************************************
//
//! Configures the trigger repeater count.
//!
//! \param base is the base address of the ADC module.
//! \param repInstance is the repeater instance.
//! \param repCount is the desired trigger count to be selected.
//!
//! This function indicates the number of repeated triggers passed into
//! \e repCount and remaining triggers to be generated/supressed.
//! In oversampling mode, the \e repCount parameter is the number of desired
//! repeated triggers to be generated. It should be a value between 0 to 127
//! where (repCount + 1) triggers will be generated. For example, when
//! \e repCount = 2, 3 triggers will be generated on receiving corresponding
//! REPxCTL.TRIGSEL. In unversampling mode, the \e repCount parameter is
//! the number of desired triggers to be supressed. It should be a value between
//! 0 to 127 where 1 out of (repCount + 1) triggers received will be passed
//! through. For Example, when \e repCount = 2, 1 out of 3 triggers will be
//! generated.
//!
//! The \e repInstance is the repeater instance to be configured. Valid values
//! for this parameter can be referred from the enum \e ADC_RepInstance.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_triggerRepeaterCount(uint32_t base, uint16_t repInstance,
                          uint16_t repCount)
{
    uint32_t regOffset;
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));
    ASSERT(repCount <= 127U);

    regOffset = base + (repInstance * (ADC_REPxN_STEP));

    //
    // Configure repeater count.
    //
    EALLOW;
    HWREG(regOffset + ADC_O_REP1N) = (HWREG(regOffset + ADC_O_REP1N) &
                                      ~(ADC_REP1N_NSEL_M)) | repCount;
    EDIS;
}

//*****************************************************************************
//
//! Configures the trigger repeater phase.
//!
//! \param base is the base address of the ADC module.
//! \param repInstance is the repeater instance.
//! \param repPhase indicates the repeater trigger phase delay
//! in sysclk cycles.
//!
//! This function configures the phase delay that corresponds to \e repPhase
//! by defining the number of sysclk to delay the selected trigger.
//! The \e repPhase parameter should be a value between 0 and 65535 inclusive.
//! For example, passing a 2 to the \e offset parameter will delay the trigger
//! by 2 sysclks and passing 0 will pass through the trigger without delay.
//!
//! The \e repInstance is the repeater instance to be configured. Valid values
//! for this parameter can be referred from the enum \e ADC_RepInstance.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_triggerRepeaterPhase(uint32_t base, uint16_t repInstance,
                          uint16_t repPhase)
{
    uint32_t regOffset;
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    regOffset = base + (repInstance * (ADC_REPxPHASE_STEP));

    //
    // Configure repeater phase.
    //
    EALLOW;
    HWREG(regOffset + ADC_O_REP1PHASE) = (HWREG(regOffset + ADC_O_REP1PHASE) &
                                          ~(ADC_REP1PHASE_PHASE_M)) | repPhase;
    EDIS;
}

//*****************************************************************************
//
//! Configures the trigger repeater spread.
//!
//! \param base is the base address of the ADC module.
//! \param repInstance is the repeater instance.
//! \param repSpread is the desired trigger spread in sysclk cycle.
//!
//! This function configures the spread time by setting \e repSpread
//! to number of sysclk desired between triggers. In oversampling mode,
//! the \e repSpread parameter is the minimum number of sysclks to wait before
//! creating the next repeated trigger to the ADC. It should be a value between
//! 0 and 65535 inclusive. For example, passing a 2 to the \e offset parameter
//! will create at least 2 sysclk time between repeated triggers.
//!
//! The \e repInstance is the repeater instance to be configured. Valid values
//! for this parameter can be referred from the enum \e ADC_RepInstance.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_triggerRepeaterSpread(uint32_t base, uint16_t repInstance,
                          uint16_t repSpread)
{
    uint32_t regOffset;
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    regOffset = base + (repInstance * (ADC_REPxSPREAD_STEP));

    //
    // Configure repeater spread.
    //
    EALLOW;
    HWREG(regOffset + ADC_O_REP1SPREAD) =
                                      (HWREG(regOffset + ADC_O_REP1SPREAD) &
                                      ~(ADC_REP1SPREAD_SPREAD_M)) | repSpread;
    EDIS;
}
//*****************************************************************************
//
//! Configures the trigger repeater.
//!
//! \param base is the base address of the ADC module.
//! \param repInstance is the repeater instance.
//! \param config is the desired repeater configuration.
//!
//! This function configures ADC trigger repeater for repeater mode, trigger
//! and sync along with count, phase delay and spread of triggers.
//!
//! The \e repInstance is the repeater instance to be configured. Valid values
//! for this parameter can be referred from the enum \e ADC_RepInstance.
//!
//! The \e config is the desired trigger repeater configuration which is
//! of type \e ADC_RepeaterConfig.
//!
//! \return None.
//
//*****************************************************************************
extern void
ADC_configureRepeater(uint32_t base, uint16_t repInstance,
                      ADC_RepeaterConfig *config);

//*****************************************************************************
//
//! Cofigure the internal connection to route VREFLO to ADC module.
//!
//! \param base is the base address of the ADC module.
//! \param socNumber is the number of the start-of-conversion.
//! \param trigger the source that will cause the SOC.
//! \param sampleWindow is the acquisition window duration.
//! \param channelType specifies the type of the ADC channel.
//!
//! This function configures the internal connection to route VREFLO to the ADC
//! module as all the modules do not have direct connection to internal VREFLO.
//!
//! The \e socNumber number is a value \b ADC_SOC_NUMBERX where X is a number
//! from 0 to 15 specifying which SOC is to be configured on the ADC module
//! specified by \e base.
//!
//! The \e trigger parameter takes the same values as the ADC_setupSOC() API and
//! the \e sampleWindow parameter is the acquisition window duration in SYSCLK
//! cycles. It should be a value between 1 and 512 cycles inclusive.
//!
//! The \e channelType parameter must be one of the following:
//! \b ADC_CHANNEL_ODD or \b ADC_CHANNEL_EVEN based on the channel selection.
//!
//! \return None.
//!
//*****************************************************************************
extern void
ADC_setupSOCRefloChannel(uint32_t base, ADC_SOCNumber socNumber,
       ADC_Trigger trigger, uint32_t sampleWindow, ADC_ChannelType channelType);

//*****************************************************************************
//
//! Configures the analog-to-digital converter resolution and signal mode.
//!
//! \param base is the base address of the ADC module.
//! \param resolution is the resolution of the converter (12 or 16 bits).
//! \param signalMode is the input signal mode of the converter.
//!
//! This function configures the ADC module's conversion resolution and input
//! signal mode and ensures that the corresponding trims are loaded.
//!
//! The \e resolution parameter specifies the resolution of the conversion.
//! It can be 12-bit or 16-bit specified by \b ADC_RESOLUTION_12BIT
//! or \b ADC_RESOLUTION_16BIT.
//!
//! The \e signalMode parameter specifies the signal mode. In single-ended
//! mode, which is indicated by \b ADC_MODE_SINGLE_ENDED, the input voltage is
//! sampled on a single pin referenced to VREFLO. In differential mode, which
//! is indicated by \b ADC_MODE_DIFFERENTIAL, the input voltage to the
//! converter is sampled on a pair of input pins, a positive and a negative.
//!
//!
//! \return None.
//
//*****************************************************************************
extern void
ADC_setMode(uint32_t base, ADC_Resolution resolution,
            ADC_SignalMode signalMode);

//*****************************************************************************
//
//! Configures the ADC module's reference mode and offset trim
//!
//! \param base is the base address of the ADC module.
//! \param refMode is the reference mode being used (\b ADC_REFERENCE_INTERNAL
//!        or \b ADC_REFERENCE_EXTERNAL).
//! \param refVoltage is the reference voltage being used
//!        (\b ADC_REFERENCE_2_5V or \b ADC_REFERENCE_3_3V). This is ignored
//!        when the reference mode is external.
//!
//! This function configures the ADC module's reference mode and loads the
//! corresponding offset trims.
//!
//! \note In this device, the bandgaps are common for all the ADC instances,
//! hence common Vref configuration needs to be done for all the ADCs. This
//! API configures same Vref configuration for all the supported ADCs in the
//! device.
//!
//! \note When the \e refMode parameter is \b ADC_REFERENCE_EXTERNAL, the value
//! of the \e refVoltage parameter has no effect on the operation of the ADC.
//!
//! \return None.
//
//*****************************************************************************
extern void
ADC_setVREF(uint32_t base, ADC_ReferenceMode refMode,
            ADC_ReferenceVoltage refVoltage);


//*****************************************************************************
//
//! Configures the offset trim for the desired ADC instance
//!
//! \param base is the base address of the ADC module.
//!
//! This function loads the offset trims for the desired ADC instance.
//!
//! \return None.
//
//*****************************************************************************
extern void
ADC_setOffsetTrim(uint32_t base);

//*****************************************************************************
//
//! Configures the INL trim for the desired ADC instance
//!
//! \param base is the base address of the ADC module.
//!
//! This function loads the INL trims for the desired ADC instance.
//!
//! \return None.
//
//*****************************************************************************
extern void
ADC_setINLTrim(uint32_t base);

//*****************************************************************************
//
//! Sets the windowed trip limits for a PPB.
//!
//! \param base is the base address of the ADC module.
//! \param ppbNumber is the number of the post-processing block.
//! \param tripHiLimit is the value is the digital comparator trip high limit.
//! \param tripLoLimit is the value is the digital comparator trip low limit.
//!
//! This function sets the windowed trip limits for a PPB. These values set
//! the digital comparator so that when one of the values is exceeded, either a
//! high or low trip event will occur.
//!
//! The \e ppbNumber is a value \b ADC_PPB_NUMBERX where X is a value from 1 to
//! 4 inclusive that identifies a PPB to be configured.
//!
//!
//! \return None.
//
//*****************************************************************************
extern void
ADC_setPPBTripLimits(uint32_t base, ADC_PPBNumber ppbNumber,
                     int32_t tripHiLimit, int32_t tripLoLimit);


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

#endif // ADC_H
