//###########################################################################
//
// FILE:   adc.h
//
// TITLE:  C28x ADC driver.
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
#define ADC_INTSEL_OFFSET_BASE      ADC_O_INTSEL
#define ADC_DMAINTSEL_OFFSET_BASE   ADC_O_DMAINTSEL
#define ADC_PPBxRESULT_OFFSET_BASE  ADC_O_PPB1RESULT

//*****************************************************************************
//
// Define to mask out the bits in the REPxCTL register that aren't associated
// with repeater configuration.
//
//*****************************************************************************
#define REPCTL_MASK                 (ADC_REP1CTL_TRIGGER_M                   |\
                                     ADC_REP1CTL_SYNCINSEL_M)
#define ADC_PPBxPSUM_OFFSET_BASE     ADC_O_PPB1PSUM
#define ADC_PPBxPCOUNT_OFFSET_BASE   ADC_O_PPBP1PCOUNT
#define ADC_PPBxSUM_OFFSET_BASE     ADC_O_PPB1SUM
#define ADC_PPBxCOUNT_OFFSET_BASE   ADC_O_PPB1COUNT
#define ADC_PPBTRIP_MASK            (uint32_t)ADC_PPB1TRIPHI_LIMITHI_M


#define ADC_PPBxCONFIG_STEP         (ADC_O_PPB2CONFIG - ADC_O_PPB1CONFIG)
#define ADC_PPBxTRIPHI_STEP         (ADC_O_PPB2TRIPHI - ADC_O_PPB1TRIPHI)
#define ADC_PPBxTRIPLO_STEP         (ADC_O_PPB2TRIPLO - ADC_O_PPB1TRIPLO)
#define ADC_PPBxOFFCAL_STEP         (ADC_O_PPB2OFFCAL - ADC_O_PPB1OFFCAL)
#define ADC_PPBxOFFREF_STEP         (ADC_O_PPB2OFFREF - ADC_O_PPB1OFFREF)

#define ADC_INT_REF_TSSLOPE         (*(int16_t *)((uintptr_t)0x720C5))
#define ADC_INT_REF_TSOFFSET        (*(int16_t *)((uintptr_t)0x720C6))
#define ADC_EXT_REF_TSSLOPE         (*(int16_t *)((uintptr_t)0x720C3))
#define ADC_EXT_REF_TSOFFSET        (*(int16_t *)((uintptr_t)0x720C4))

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
#define ADC_EVT_NLIMIT              0x0008U //!< Within Trip limit Event
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
                                     ADC_REP1CTL_TRIGGEROVF)


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
//! Values that can be passed to ADC_setupSOC() as the \e trigger
//! parameter to specify the event that will trigger a conversion to start.
//! It is also used with ADC_setBurstModeConfig() and
//! ADC_triggerRepeaterSelect().
//
//*****************************************************************************
typedef enum
{
	ADC_TRIGGER_SW_ONLY		 = 0,	//!Software only
	ADC_TRIGGER_CPU1_TINT0		 = 1,	//!CPU1 Timer 0, TINT0
	ADC_TRIGGER_CPU1_TINT1		 = 2,	//!CPU1 Timer 1, TINT1
	ADC_TRIGGER_CPU1_TINT2		 = 3,	//!CPU1 Timer 2, TINT2
	ADC_TRIGGER_GPIO		 = 4,	//!GPIO, ADCEXTSOC
	ADC_TRIGGER_MCPWM1_SOCA		 = 5,	//!MCPWM1 ADC SOCA
	ADC_TRIGGER_MCPWM1_SOCB		 = 6,	//!MCPWM1 ADC SOCB
	ADC_TRIGGER_MCPWM1_SOCC		 = 7,	//!MCPWM1 ADC SOCC
	ADC_TRIGGER_MCPWM1_SOCD		 = 8,	//!MCPWM1 ADC SOCD
	ADC_TRIGGER_MCPWM3_SOCA		 = 13,	//!MCPWM3 ADC SOCA
	ADC_TRIGGER_MCPWM3_SOCB		 = 14,	//!MCPWM3 ADC SOCB
	ADC_TRIGGER_REPEATER1		 = 21	//!Repeater 1
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
    ADC_CH_ADCIN0  = 0U,          //!< ADCIN0 is converted
    ADC_CH_ADCIN1  = 1U,          //!< ADCIN1 is converted
    ADC_CH_ADCIN2  = 2U,          //!< ADCIN2 is converted
    ADC_CH_ADCIN3  = 3U,          //!< ADCIN3 is converted
    ADC_CH_ADCIN4  = 4U,          //!< ADCIN4 is converted
    ADC_CH_ADCIN5  = 5U,          //!< ADCIN5 is converted
    ADC_CH_ADCIN6  = 6U,          //!< ADCIN6 is converted
    ADC_CH_ADCIN7  = 7U,          //!< ADCIN7 is converted
    ADC_CH_ADCIN8  = 8U,          //!< ADCIN8 is converted
    ADC_CH_ADCIN9  = 9U,          //!< ADCIN9 is converted
    ADC_CH_ADCIN10 = 10U,         //!< ADCIN10 is converted
    ADC_CH_ADCIN11 = 11U,         //!< ADCIN11 is converted
    ADC_CH_ADCIN12 = 12U,         //!< ADCIN12 is converted
    ADC_CH_ADCIN13 = 13U,         //!< ADCIN13 is converted
    ADC_CH_ADCIN14 = 14U,         //!< ADCIN14 is converted
    ADC_CH_ADCIN15 = 15U,         //!< ADCIN15 is converted
    ADC_CH_ADCIN16 = 16U,         //!< ADCIN16 is converted
    ADC_CH_ADCIN17 = 17U,         //!< ADCIN17 is converted
    ADC_CH_ADCIN18 = 18U,         //!< ADCIN18 is converted
    ADC_CH_ADCIN19 = 19U,         //!< ADCIN19 is converted
    ADC_CH_ADCIN20 = 20U,         //!< ADCIN20 is converted
    ADC_CH_ADCIN21 = 21U,         //!< ADCIN21 is converted
    ADC_CH_ADCIN22 = 22U,         //!< ADCIN22 is converted
    ADC_CH_ADCIN23 = 23U,         //!< ADCIN23 is converted
    ADC_CH_ADCIN24 = 24U,         //!< ADCIN24 is converted
    ADC_CH_ADCIN25 = 25U          //!< ADCIN25 is converted
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
    ADC_INT_NUMBER2 = 1U         //!< ADCINT2 Interrupt
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
    ADC_PPB_NUMBER3 = 2U         //!< Post-processing block 3
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
    ADC_INT_SOC_TRIGGER_ADCINT2 = 2U,   //!< ADCINT2 will trigger the SOC
    ADC_INT_SOC_TRIGGER_EOC     = 3U    //!< EOC of previous SOC will trigger
                                        //!< the SOC
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
    ADC_PRI_THRU_SOC2_HIPRI = 3U     //!< SOC 0-2 hi pri, others in round robin
} ADC_PriorityMode;

//*****************************************************************************
//
//! Values that can be passed to ADC_SelectSampleCAPResetValue() as the
//! \e capResetVal parameter.
//
//*****************************************************************************
typedef enum
{
    ADC_CAP_RESET_VREFLO    = 0U,   //! Sample Capacitor reset to Vreflo
    ADC_CAP_RESET_VREFHIBY2 = 1U    //! Sample Capacitor reset to Vrefhi/2
} ADC_SampleCAPResetValue;

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
    ADC_REFERENCE_3_3V      = 0U,
    ADC_REFERENCE_2_5V      = 1U,
    ADC_REFERENCE_VREFHI    = 0U, //!< This value is valid when ADC reference
                                  //!< mode is external
} ADC_ReferenceVoltage;


//*****************************************************************************
//
//! Values that can be passed to ADC_selectPPBSyncInput() and
//! ADC_triggerRepeaterSyncIn() as the \e syncInput parameter.
//
//*****************************************************************************
typedef enum
{
	ADC_SYNCIN_DISABLE		 = 0x0,	//!ADC Syncin is disabled
	ADC_SYNCIN_INPUTXBAROUTPUT5		 = 0x1,	//!ADC Syncin is INPUTXBAROUTPUT5
	ADC_SYNCIN_INPUTXBAROUTPUT6		 = 0x2,	//!ADC Syncin is INPUTXBAROUTPUT6
	ADC_SYNCIN_ECAP1YNCOUT		 = 0x3,	//!ADC Syncin is ECAP1YNCOUT
	ADC_SYNCIN_MCPWM1SYNCPER		 = 0x5,	//!MCPWM1 SYNCPER Signal
	ADC_SYNCIN_MCPWM3SYNCPER		 = 0x7	//!MCPWM3 SYNCPER Signal
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
    ADC_INT_TRIGGER_OSINT1 = 32U        //!< OSINT1
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
    ADC_PPB_COMPSOURCE_SUM    = 0x1U    //!< PPB compare source is SUM
} ADC_PPBCompSource;


//*****************************************************************************
//
//! Values that can be passed to ADC_configureRepeater() as the \e repInstance
//! parameter.
//
//*****************************************************************************
typedef enum
{
    ADC_REPINST1 = 0x0U                 //!< Select ADC repeater instance 1
} ADC_RepInstance;


//*****************************************************************************
//
//! Values that can be passed to ADC_configureRepeater() as the
//! \e config parameter.
//
//*****************************************************************************
typedef struct
{
    ADC_Trigger repTrigger;  //!< Repeater Trigger
    ADC_SyncInput repSyncin; //!< Repeater Syncin
    uint16_t repCount;       //!< Repeater trigger count
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
           (base == ADCA_BASE)
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
    HWREG(base + ADC_O_CTL2) = (HWREG(base + ADC_O_CTL2) &
                                 ~ADC_CTL2_PRESCALE_M) | (uint32_t)clkPrescale;
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
//! timer interrupt, an MCPWM event, or an ADC interrupt. It should be a value
//! in the format of \b ADC_TRIGGER_XXXX where XXXX is the event such as
//! \b ADC_TRIGGER_SW_ONLY, \b ADC_TRIGGER_CPU1_TINT0, \b ADC_TRIGGER_GPIO,
//! \b ADC_TRIGGER_MCPWM1_SOCA, and so on.
//!
//! The \e channel parameter specifies the channel to be converted. In
//! single-ended mode this is a single pin given by \b ADC_CH_ADCINx where x is
//! the number identifying the pin between 0 and 15 inclusive.
//!
//! The \e sampleWindow parameter is the acquisition window duration in SYSCLK
//! cycles. The selected duration must be at least as long as one ADCCLK cycle.
//! Also, the datasheet will specify a minimum window duration requirement in
//! nanoseconds. The sample window value is calculated based on the combination
//! of ACQPS[7:6] and ACQPS[5:0], where ACQPS[7:6] determines scale and
//! ACQPS[7:6] determines offset. If ACQPS[7:6] value is:
//! "00" ->  sample window = ACQPS[5:0] + 1 sysclk cycles
//! "01" ->  sample window = 64 + ((ACQPS[5:0] +1) * 2) sysclk cycles
//! "10" ->  sample window = 192 + ((ACQPS[5:0] +1) * 4) sysclk cycles
//! "11" ->  sample window = 448 + ((ACQPS[5:0] +1) * 16) sysclk cycles
//! Based on the \e sampleWindow corresponding ACQPS value will be calculated
//! and configured in ADCSOCxCTL register.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_setupSOC(uint32_t base, ADC_SOCNumber socNumber, ADC_Trigger trigger,
             ADC_Channel channel, uint32_t sampleWindow)
{
    uint32_t ctlRegAddr, mask;
    uint32_t ACQPS;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    mask = (ADC_SOC0CTL_CHSEL_M | ADC_SOC0CTL_TRIGSEL_M | ADC_SOC0CTL_ACQPS_M);

    if (sampleWindow > 448UL){
        ACQPS = (3UL << 6UL) | (((sampleWindow - 448UL) >> 4UL) - 1UL);
    }
    else if (sampleWindow > 192UL){
        ACQPS = (2UL << 6UL) | (((sampleWindow - 192UL) >> 2UL) - 1UL);

    }
    else if (sampleWindow > 64UL){
        ACQPS = (1UL << 6UL) | (((sampleWindow - 64UL) >> 1UL) - 1UL);

    }
    else{
        ACQPS = sampleWindow - 1UL;
    }
    //
    // Calculate address for the SOC control register.
    //
    ctlRegAddr = base + ADC_SOCxCTL_OFFSET_BASE + ((uint32_t)socNumber * 2U);

    //
    // Set the configuration of the specified SOC.
    //
    EALLOW;

    HWREG(ctlRegAddr) = (HWREG(ctlRegAddr) & ~(mask)) |
                        ((uint32_t)channel << ADC_SOC0CTL_CHSEL_S) |
                        ((uint32_t)trigger << ADC_SOC0CTL_TRIGSEL_S) |
                        ACQPS;

    EDIS;
}

//*****************************************************************************
//
//! Enable the sample capacitor reset for an ADC SOC.
//!
//! \param base is the base address of the ADC module.
//! \param socNumber is the number of the start-of-conversion.
//!
//! This function enables the sample capacitor reset after each conversion
//! for a particular SOC.
//!
//! The \e socNumber number is a value \b ADC_SOC_NUMBERX where X is a number
//! from 0 to 15 specifying which SOC is to be configured on the ADC module
//! specified by \e base.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_enableSampleCAPReset(uint32_t base, ADC_SOCNumber socNumber)
{
    uint32_t ctlRegAddr;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Calculate address for the SOC control register.
    //
    ctlRegAddr = base + ADC_SOCxCTL_OFFSET_BASE + ((uint32_t)socNumber * 2UL);

    //
    // Enable the sample capacitor reset after each conversion.
    //
    EALLOW;
    HWREG(ctlRegAddr) &= ~((uint32_t)ADC_SOC0CTL_SAMPCAPRESETDISABLE);
    EDIS;
}

//*****************************************************************************
//
//! Disable the sample capacitor reset for an ADC SOC.
//!
//! \param base is the base address of the ADC module.
//! \param socNumber is the number of the start-of-conversion.
//!
//! This function disables the sample capacitor reset after each conversion
//! for a particular SOC.
//!
//! The \e socNumber number is a value \b ADC_SOC_NUMBERX where X is a number
//! from 0 to 15 specifying which SOC is to be configured on the ADC module
//! specified by \e base.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_disableSampleCAPReset(uint32_t base, ADC_SOCNumber socNumber)
{
    uint32_t ctlRegAddr;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Calculate address for the SOC control register.
    //
    ctlRegAddr = base + ADC_SOCxCTL_OFFSET_BASE + ((uint32_t)socNumber * 2UL);

    //
    // Disable the sample capacitor reset after each conversion.
    //
    EALLOW;
    HWREG(ctlRegAddr) |= ((uint32_t)ADC_SOC0CTL_SAMPCAPRESETDISABLE);
    EDIS;
}

//*****************************************************************************
//
//! Set the sample capacitor to reset to VREFLO
//!
//! \param base is the base address of the ADC module.
//! \param socNumber is the number of the start-of-conversion.
//! \param capResetVal is the desired sample capacitor reset value.
//!
//! This function sets the sample capacitor to reset to either Vrefhi/2 or
//! Vreflo after each conversion.
//!
//! The \e socNumber number is a value \b ADC_SOC_NUMBERX where X is a number
//! from 0 to 15 specifying which SOC is to be configured on the ADC module
//! specified by \e base.
//!
//! The \e capResetVal is the desired sample capacitor reset value. Valid values
//! can be refered from the enum \e ADC_SampleCAPResetValue.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_selectSampleCAPResetValue(uint32_t base, ADC_SOCNumber socNumber,
                                ADC_SampleCAPResetValue capResetVal)
{
    uint32_t ctlRegAddr;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Calculate address for the SOC control register.
    //
    ctlRegAddr = base + ADC_SOCxCTL_OFFSET_BASE + ((uint32_t)socNumber * 2U);

    //
    // Set the sample capacitor to reset to VREFLO.
    //
    EALLOW;
    HWREG(ctlRegAddr) = (HWREG(ctlRegAddr) &
                        ~(ADC_SOC0CTL_SAMPCAPRESETSEL)) | (uint32_t)capResetVal;
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

  regOffset = base + repInstance;
  EALLOW;
  //
  // Triggers the selected repeater instance
  //
  HWREG(regOffset + ADC_O_REP1FRC) |= ADC_REP1FRC_SWFRC;
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
//! \b ADC_REPEATER_MODULE_BUSY, \b ADC_REPEATER_TRIGGER_OVERFLOW
//
//*****************************************************************************
static inline uint32_t
ADC_getRepeaterStatus(uint32_t base, uint16_t repInstance)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Return the status of repeater.
    //
    return(HWREG(base + ADC_O_REP1CTL) & ADC_REPSTATUS_MASK);
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
//! - \b ADC_INT_SOC_TRIGGER_EOC
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
    HWREG(base + ADC_O_CTL1) = (HWREG(base + ADC_O_CTL1) &
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
    HWREG(base + ADC_O_INTCYCLE) = cycleOffset;
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
    return((HWREG(base + ADC_O_INTFLG) &
                 (1UL << ((uint32_t)adcIntNum + 8UL))) != 0UL);
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
    HWREG(base + ADC_O_CTL1) |= ADC_CTL1_ADCPWDNZ;
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
    HWREG(base + ADC_O_CTL1) &= ~ADC_CTL1_ADCPWDNZ;
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
    HWREG(base + ADC_O_SOCFRC1) = (1UL << (uint32_t)socNumber);
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
ADC_forceMultipleSOC(uint32_t base, uint32_t socMask)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Write to the register that will force a 1 to desired SOCs
    //
    HWREG(base + ADC_O_SOCFRC1) = socMask;
}

//*****************************************************************************
//
//! Gets the Raw DMA interrupt status.
//!
//! \param base is the base address of the ADC module.
//! \param adcIntNum is interrupt number for the ADC wrapper.
//!
//! This function returns the Raw DMA interrupt status associated with the
//! selected interrupt number for the ADC wrapper.
//!
//! \e adcIntNum takes a one of the values \b ADC_INT_NUMBER1
//! or \b ADC_INT_NUMBER1 to get the Raw DMA interrupt status for
//! the conversions associated with the given interrupt number. This flag
//! will be set irrespective of corresponding DMAINTE.
//!
//! \return \b true if the result is available for the selected interrupt
//! and \b false if it is not.
//
//*****************************************************************************
static inline bool
ADC_getDMARAWIntStatus(uint32_t base, ADC_IntNumber adcIntNum)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Get the specified Raw DMA interrupt status.
    //
    return((HWREG(base + ADC_O_RAWINTFLG) &
                 (1UL << ((uint32_t)adcIntNum + 16UL))) != 0UL);
}

//*****************************************************************************
//
//! Gets the Raw ADC interrupt status.
//!
//! \param base is the base address of the ADC module.
//! \param adcIntNum is interrupt number within the ADC wrapper.
//!
//! This function returns the raw ADC interrupt status which indicates if the
//! associated interrupt condition occured. This flag will be set irrespective
//! of corresponding INTE.
//!
//! \e adcIntNum takes a one of the values \b ADC_INT_NUMBER1 or
//! \b ADC_INT_NUMBER2 to get the raw ADC interrupt status
//! for the given interrupt number of the ADC module.
//!
//! \return \b true if the interrupt flag for the specified interrupt number is
//! set and \b false if it is not.
//
//*****************************************************************************
static inline bool
ADC_getRAWInterruptStatus(uint32_t base, ADC_IntNumber adcIntNum)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Get the specified raw ADC interrupt status.
    //
    return((HWREG(base + ADC_O_RAWINTFLG) &
                                        (1UL << (uint32_t)adcIntNum)) != 0UL);
}

//*****************************************************************************
//
//! Gets the current ADC DMA interrupt status.
//!
//! \param base is the base address of the ADC module.
//! \param adcIntNum is interrupt number within the ADC wrapper.
//!
//! This function returns the DMA interrupt status for the analog-to-digital
//! converter.
//!
//! \e adcIntNum takes a one of the values \b ADC_INT_NUMBER1 and
//! \b ADC_INT_NUMBER2 to get the DMA interrupt status for the given
//! interrupt number of the ADC module.
//!
//! \return \b true if the DMA interrupt flag for the specified interrupt number
//! is set and \b false if it is not.
//
//*****************************************************************************
static inline bool
ADC_getDMAInterruptStatus(uint32_t base, ADC_IntNumber adcIntNum)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));
    //
    // Get the specified ADC DMA interrupt status.
    //
    return((HWREG(base + ADC_O_INTFLG) &
                 (1UL << ((uint32_t)adcIntNum + 16UL))) != 0UL);
}

//*****************************************************************************
//
//! Clears ADC DMA interrupt sources.
//!
//! \param base is the base address of the ADC module.
//! \param adcIntNum is interrupt number within the ADC wrapper.
//!
//! This function clears the specified ADC DMA interrupt sources so that they no
//! longer assert. If not in continuous mode, this function must be called
//! before any further interrupt pulses may occur.
//!
//! \e adcIntNum takes a one of the values \b ADC_INT_NUMBER1 and
//! \b ADC_INT_NUMBER2 to express which of the two DMA interrupts of the ADC
//! module should be cleared.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_clearDMAInterruptStatus(uint32_t base, ADC_IntNumber adcIntNum)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Clear the specified DMA interrupt.
    //
    HWREG(base + ADC_O_INTFLGCLR) =
                    (uint32_t)ADC_INTFLGCLR_ADCDMAINT1 << (uint32_t)adcIntNum;

}

//*****************************************************************************
//
//! Gets the current ADC DMA interrupt overflow status.
//!
//! \param base is the base address of the ADC module.
//! \param adcIntNum is interrupt number within the ADC wrapper.
//!
//! This function returns the DMA interrupt overflow status for the
//! analog-to-digital converter. An overflow condition is generated
//! irrespective of the continuous mode.
//!
//! \e adcIntNum takes a one of the values \b ADC_INT_NUMBER1 and
//! \b ADC_INT_NUMBER2 to get the DMA interrupt overflow status for
//! the given interrupt number.
//!
//! \return \b true if the DMA interrupt overflow flag for the specified
//! interrupt number is set and \b false if it is not.
//
//*****************************************************************************
static inline bool
ADC_getDMAInterruptOverflowStatus(uint32_t base, ADC_IntNumber adcIntNum)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Get the specified ADC DMA interrupt overflow status.
    //
    return((HWREG(base + ADC_O_INTOVF) &
                (1UL << (uint32_t)adcIntNum + 16UL)) != 0UL);
}

//*****************************************************************************
//
//! Clears ADC DMA interrupt overflow sources.
//!
//! \param base is the base address of the ADC module.
//! \param adcIntNum is interrupt number within the ADC wrapper.
//!
//! This function clears the specified ADC DMA interrupt overflow sources so
//! that they no longer assert. If software tries to clear the overflow in same
//! cycle that hardware tries to set the overflow, then hardware has priority.
//!
//! \e adcIntNum takes a one of the values \b ADC_INT_NUMBER1 and
//! \b ADC_INT_NUMBER2 to express which of the DMA interrupt overflow status
//! of the ADC module should be cleared.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_clearDMAInterruptOverflowStatus(uint32_t base, ADC_IntNumber adcIntNum)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Clear the specified DMA interrupt overflow bit.
    //
    HWREG(base + ADC_O_INTOVFCLR) =
                (uint32_t)ADC_INTOVFCLR_ADCDMAINT1OVF << (uint32_t)adcIntNum;
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
    return((HWREG(base + ADC_O_INTFLG) & (1UL << (uint32_t)adcIntNum)) != 0UL);
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
    HWREG(base + ADC_O_INTFLGCLR) = 1UL << (uint32_t)adcIntNum;

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
    return((HWREG(base + ADC_O_INTOVF) & (1UL << (uint32_t)adcIntNum)) != 0U);
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
    HWREG(base + ADC_O_INTOVFCLR) = 1UL << (uint32_t)adcIntNum;
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
           (resultBase == ADCARESULT_BASE)
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
    return((HWREG(base + ADC_O_CTL1) & ADC_CTL1_ADCBSY) != 0U);
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
//! on up to \b ADC_PRI_THRU_SOC2_HIPRI where SOCs 0 through 2 are in high
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

    HWREG(base + ADC_O_SOCPRICTL) = (HWREG(base + ADC_O_SOCPRICTL) &
                                      ~ADC_SOCPRICTL_SOCPRIORITY_M) |
                                     (uint32_t)priMode;

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
//! 3 inclusive that identifies a PPB to be configured.  The \e socNumber
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
    HWREG(base + ppbOffset) = (HWREG(base + ppbOffset) &
                                ~ADC_PPB1CONFIG_CONFIG_M) |
                               ((uint32_t)socNumber & ADC_PPB1CONFIG_CONFIG_M);
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
//! the specified events to propagate through the X-BAR to a pin or to an PWM
//! module.  The \e evtFlags parameter can be any of the \b ADC_EVT_TRIPHI,
//! \b ADC_EVT_TRIPLO, \b ADC_EVT_ZERO or \b ADC_EVT_NLIMIT values.
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
    ASSERT((evtFlags & ~0xFU) == 0U);

    //
    // Enable the specified event.
    //
    EALLOW;
    HWREG(base + ADC_O_EVTSEL) |= evtFlags << ((uint32_t)ppbNumber * 4UL);
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
//! \b ADC_EVT_TRIPLO, \b ADC_EVT_ZERO or \b ADC_EVT_NLIMIT values.
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
    ASSERT((evtFlags & ~0xFU) == 0U);

    //
    // Disable the specified event.
    //
    EALLOW;
    HWREG(base + ADC_O_EVTSEL) &= ~(evtFlags << ((uint32_t)ppbNumber * 4UL));
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
//! parameter can be any of the \b ADC_EVT_TRIPHI, \b ADC_EVT_TRIPLO,
//! \b ADC_EVT_ZERO or \b ADC_EVT_NLIMIT values.
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
    ASSERT((intFlags & ~0xFU) == 0U);

    //
    // Enable the specified event interrupts.
    //
    EALLOW;
    HWREG(base + ADC_O_EVTINTSEL) |= intFlags << ((uint32_t)ppbNumber * 4UL);
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
//! parameter can be any of the \b ADC_EVT_TRIPHI, \b ADC_EVT_TRIPLO,
//! \b ADC_EVT_ZERO or \b ADC_EVT_NLIMIT values.
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
    ASSERT((intFlags & ~0xFU) == 0U);

    //
    // Disable the specified event interrupts.
    //
    EALLOW;
    HWREG(base + ADC_O_EVTINTSEL) &= ~(intFlags <<
                                        ((uint32_t)ppbNumber * 4UL));
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
//! \b ADC_EVT_TRIPHI, \b ADC_EVT_TRIPLO, \b ADC_EVT_ZERO and \b ADC_EVT_NLIMIT.
//
//*****************************************************************************
static inline uint32_t
ADC_getPPBEventStatus(uint32_t base, ADC_PPBNumber ppbNumber)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Get the event status for the specified post-processing block.
    //
    return((HWREG(base + ADC_O_EVTSTAT) >> ((uint32_t)ppbNumber * 4U)) &
           0xFU);
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
//! \b ADC_EVT_TRIPLO, \b ADC_EVT_ZERO or \b ADC_EVT_NLIMIT.
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
    ASSERT((evtFlags & ~0xFU) == 0U);

    //
    // Clear the specified event interrupts.
    //
    HWREG(base + ADC_O_EVTCLR) |= evtFlags << ((uint32_t)ppbNumber * 4UL);
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
    HWREG(base + ppbOffset)  |= ADC_PPB1CONFIG_CBCEN;
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
    HWREG(base + ppbOffset)  &= ~ADC_PPB1CONFIG_CBCEN;
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
//! \note Only ADC_PPB_NUMBER1 supports this feature.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_setPPBCountLimit(uint32_t base, ADC_PPBNumber ppbNumber, uint16_t limit)
{

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));
    ASSERT(limit <= ADC_PPB1LIMIT_LIMIT_M);

    //
    // Get the offset to the appropriate PPB configuration register.
    //
    EALLOW;
    HWREG(base + ADC_O_PPB1LIMIT) =
                (HWREG(base + ADC_O_PPB1LIMIT) & ~(ADC_PPB1LIMIT_LIMIT_M)) |
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
//! \note Only ADC_PPB_NUMBER1 supports this feature.
//!
//! \return Returns the PPB count limit.
//
//*****************************************************************************
static inline uint32_t
ADC_getPPBCountLimit(uint32_t base, ADC_PPBNumber ppbNumber)
{
    uint32_t limit;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Get the offset to the appropriate PPB configuration register.
    //

    limit = (HWREG(base + ADC_O_PPB1LIMIT) & ~(ADC_PPB1LIMIT_LIMIT_M)) >>
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
//! \note Only ADC_PPB_NUMBER1 supports this feature.
//!
//! \return Returns the oversampled partial count value.
//
//*****************************************************************************
static inline uint32_t
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
//! \note Only ADC_PPB_NUMBER1 supports this feature.
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
//! \note Only ADC_PPB_NUMBER1 supports this feature.
//!
//! \return None
//
//*****************************************************************************
static inline void
ADC_setPPBShiftValue(uint32_t base, ADC_PPBNumber ppbNumber, uint16_t shiftVal)
{

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));
    ASSERT(shiftVal <= 7U);

    //
    // Get the offset to the appropriate PPB configuration register.
    //
    //
    // Configure shift value for the PPB.
    //
    HWREG(base + ADC_O_PPB1CONFIG2) =
                (HWREG(base + ADC_O_PPB1CONFIG2) & ~(ADC_PPB1CONFIG2_SHIFT_M)) |
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
//! \note Only ADC_PPB_NUMBER1 supports this feature.
//!
//! \return None
//
//*****************************************************************************
static inline void
ADC_selectPPBSyncInput(uint32_t base, ADC_PPBNumber ppbNumber,
                       uint16_t syncInput)
{

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));
    ASSERT(syncInput <= 7U);

    HWREG(base + ADC_O_PPB1CONFIG2) =
            (HWREG(base + ADC_O_PPB1CONFIG2) & ~(ADC_PPB1CONFIG2_SYNCINSEL_M)) |
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
//! \note Only ADC_PPB_NUMBER1 supports this feature.
//!
//! \return None
//
//*****************************************************************************
static inline void
ADC_forcePPBSync(uint32_t base, ADC_PPBNumber ppbNumber)
{

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    HWREG(base + ADC_O_PPB1CONFIG2) |= ADC_PPB1CONFIG2_SWSYNC;
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
//! \note Only ADC_PPB_NUMBER1 supports this feature.
//!
//! \return None
//*****************************************************************************
static inline void
ADC_selectPPBOSINTSource(uint32_t base, ADC_PPBNumber ppbNumber,
                         uint16_t osIntSrc)
{

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));
    ASSERT(osIntSrc <= 1U);

    HWREG(base + ADC_O_PPB1CONFIG2) =
               (HWREG(base + ADC_O_PPB1CONFIG2) & ~(ADC_PPB1CONFIG2_OSINTSEL)) |
               (osIntSrc << 12UL);
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
//! \note Only ADC_PPB_NUMBER1 supports this feature.
//!
//! \return None
//
//*****************************************************************************
static inline void
ADC_selectPPBCompareSource(uint32_t base, ADC_PPBNumber ppbNumber,
                           uint16_t compSrc)
{

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));
    ASSERT(compSrc <= 1U);

    HWREG(base + ADC_O_PPB1CONFIG2) =
            (HWREG(base + ADC_O_PPB1CONFIG2) & ~(ADC_PPB1CONFIG2_COMPSEL)) |
            (compSrc << 15UL);
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
//! \note Only ADC_PPB_NUMBER1 supports this feature.
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
           (resultBase == ADCARESULT_BASE)
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
//! \note Only ADC_PPB_NUMBER1 supports this feature.
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
           (resultBase == ADCARESULT_BASE)
          );
    //
    // Return the final count of selected PPB.
    //
    return((uint32_t)HWREG(resultBase + (uint32_t)ADC_PPBxCOUNT_OFFSET_BASE +
           ((uint32_t)ppbNumber * 4UL)));
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
           (resultBase == ADCARESULT_BASE)
          );
    //
    // Return the result of selected PPB.
    //
    return((int32_t)HWREG(resultBase + (uint32_t)ADC_PPBxRESULT_OFFSET_BASE +
           ((uint32_t)ppbNumber * 2UL)));
}


//*****************************************************************************
//
//! Sets the post processing block offset correction.
//!
//! \param base is the base address of the ADC module.
//! \param ppbNumber is the number of the post-processing block.
//! \param offset is the 6-bit signed value subtracted from ADC the output.
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
    HWREG(base + ppbOffset) = (HWREG(base + ppbOffset) &
                                ~ADC_PPB1OFFCAL_OFFCAL_M) |
                               ((uint32_t)offset & ADC_PPB1OFFCAL_OFFCAL_M);
    EDIS;
}

//*****************************************************************************
//
//! Sets the post processing block reference offset.
//!
//! \param base is the base address of the ADC module.
//! \param ppbNumber is the number of the post-processing block.
//! \param offset is the 12-bit unsigned value subtracted from ADC the output.
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
    HWREG(base + ppbOffset) = offset;
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
    HWREG(base + ppbOffset) |= ADC_PPB1CONFIG_TWOSCOMPEN;
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
    HWREG(base + ppbOffset) &= ~ADC_PPB1CONFIG_TWOSCOMPEN;
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
    uint32_t shiftVal;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Each INTSEL register manages two interrupts. If the interrupt number is
    // even, we'll be accessing the upper byte and will need to shift.
    //
    intRegAddr = base + ADC_INTSEL_OFFSET_BASE;
    shiftVal = (uint32_t)adcIntNum << 3UL;

    //
    // Enable the specified ADC interrupt.
    //
    EALLOW;

    HWREG(intRegAddr) |= ADC_INTSEL_INT1E << shiftVal;

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
    uint32_t shiftVal;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Each INTSEL register manages two interrupts. If the interrupt number is
    // even, we'll be accessing the upper byte and will need to shift.
    //
    intRegAddr = base + ADC_INTSEL_OFFSET_BASE;
    shiftVal = (uint32_t)adcIntNum << 3UL;

    //
    // Disable the specified ADC interrupt.
    //
    EALLOW;

    HWREG(intRegAddr) &= ~(ADC_INTSEL_INT1E << shiftVal);

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
    uint32_t shiftVal;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));
    ASSERT(intTrigger < 33U);

    //
    // Each INTSEL register manages two interrupts. If the interrupt number is
    // even, we'll be accessing the upper byte and will need to shift.
    //
    intRegAddr = base + ADC_INTSEL_OFFSET_BASE;
    shiftVal = (uint32_t)adcIntNum << 3U;

    //
    // Set the specified ADC interrupt source.
    //
    EALLOW;

    HWREG(intRegAddr) =
        (HWREG(intRegAddr) & ~(ADC_INTSEL_INT1SEL_M << shiftVal)) |
        ((uint32_t)intTrigger << shiftVal);

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
    uint32_t shiftVal;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Each INTSEL register manages two interrupts. If the interrupt number is
    // even, we'll be accessing the upper byte and will need to shift.
    //
    intRegAddr = base + ADC_INTSEL_OFFSET_BASE;
    shiftVal = (uint32_t)adcIntNum << 3UL;

    //
    // Enable continuous mode for the specified ADC interrupt.
    //
    EALLOW;

    HWREG(intRegAddr) |= ADC_INTSEL_INT1CONT << shiftVal;

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
    uint32_t shiftVal;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Each INTSEL register manages two interrupts. If the interrupt number is
    // even, we'll be accessing the upper byte and will need to shift.
    //
    intRegAddr = base + ADC_INTSEL_OFFSET_BASE;
    shiftVal = (uint32_t)adcIntNum << 3UL;

    //
    // Disable continuous mode for the specified ADC interrupt.
    //
    EALLOW;

    HWREG(intRegAddr) &= ~(ADC_INTSEL_INT1CONT << shiftVal);

    EDIS;
}
//*****************************************************************************
//
//! Enables a ADC interrupt for DMA.
//!
//! \param base is the base address of the ADC module.
//! \param adcIntNum is interrupt number within the ADC wrapper.
//!
//! This function enables the indicated ADC interrupt for DMA. Only the
//! sources that are enabled can be reflected to the processor interrupt.
//! Disabled sources have no effect on the processor.
//!
//! \e adcIntNum can take the value \b ADC_INT_NUMBER1 and \b ADC_INT_NUMBER2
//! to express which of the interrupts of the ADC module should be enabled.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_enableDMAInterrupt(uint32_t base, ADC_IntNumber adcIntNum)
{
    uint32_t shiftVal;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    shiftVal = (uint32_t)adcIntNum << 3UL;

    //
    // Enable the ADC interrupt for DMA.
    //
    EALLOW;

    HWREG(base + ADC_O_DMAINTSEL) |= ADC_DMAINTSEL_DMAINT1E << shiftVal;

    EDIS;
}

//*****************************************************************************
//
//! Disables an ADC interrupt for DMA.
//!
//! \param base is the base address of the ADC module.
//! \param adcIntNum is interrupt number within the ADC wrapper.
//!
//! This function disables the indicated ADC interrupt for DMA.
//! Only the sources that are enabled can be reflected to the processor
//! interrupt. Disabled sources have no effect on the processor.
//!
//! \e adcIntNum can take the value \b ADC_INT_NUMBER1 or \b ADC_INT_NUMBER2
//! to express which of the interrupts of the ADC module should be disabled.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_disableDMAInterrupt(uint32_t base, ADC_IntNumber adcIntNum)
{
    uint32_t shiftVal;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    shiftVal = (uint32_t)adcIntNum << 3UL;

    //
    // Disable the ADC interrupt for DMA.
    //
    EALLOW;

    HWREG(base + ADC_O_DMAINTSEL) &= ~(ADC_DMAINTSEL_DMAINT1E << shiftVal);

    EDIS;
}

//*****************************************************************************
//
//! Select the EOC source for an ADC interrupt for DMA.
//!
//! \param base is the base address of the ADC module.
//! \param adcIntNum is interrupt number within the ADC wrapper.
//! \param socNumber is the number of the start-of-conversion.
//!
//! This function sets which conversion is the source of an ADC interrupt for DMA.
//!
//! The \e intTrigger number is a value \b ADC_INT_TRIGGER_X where X specifies
//! the interrupt trigger to be configured for the ADC module specified by
//! \e base. Refer \b ADC_IntTrigger enum for valid values for this input.
//!
//! \e adcIntNum can take the value \b ADC_INT_NUMBER1 or \b ADC_INT_NUMBER2
//! to express which of the interrupts of the ADC module is being configured.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_setDMAInterruptSource(uint32_t base, ADC_IntNumber adcIntNum,
                       uint32_t intTrigger)
{
    uint32_t shiftVal;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));
    ASSERT(intTrigger < 33U);

    shiftVal = (uint32_t)adcIntNum << 3UL;

    //
    // Set the specified ADC interrupt source for DMA.
    //
    EALLOW;

    HWREG(base + ADC_O_DMAINTSEL) = (HWREG(base + ADC_O_DMAINTSEL) &
                                    ~(ADC_DMAINTSEL_DMAINT1SEL_M << shiftVal)) |
                                    ((uint32_t)intTrigger << shiftVal);

    EDIS;
}

//*****************************************************************************
//
//! Enables continuous mode of an ADC interrupt for DMA.
//!
//! \param base is the base address of the ADC.
//! \param adcIntNum is interrupt number within the ADC wrapper.
//!
//! This function enables continuous mode for the ADC interrupt passed into
//! \e adcIntNum. This means that pulses will be generated for the specified
//! ADC interrupt for DMA whenever an EOC pulse is generated irrespective of
//! whether or not the flag bit is set.
//!
//! \e adcIntNum can take the value \b ADC_INT_NUMBER1 or \b ADC_INT_NUMBER2
//! to express which of the interrupts of the ADC module is being configured.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_enableDMAContinuousMode(uint32_t base, ADC_IntNumber adcIntNum)
{
    uint32_t shiftVal;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    shiftVal = (uint32_t)adcIntNum << 3UL;

    //
    // Enable continuous mode for the specified ADC interrupt for DMA.
    //
    EALLOW;

    HWREG(base + ADC_O_DMAINTSEL) |= ADC_DMAINTSEL_DMAINT1CONT << shiftVal;

    EDIS;
}

//*****************************************************************************
//
//! Disables continuous mode of an ADC interrupt for DMA.
//!
//! \param base is the base address of the ADC.
//! \param adcIntNum is interrupt number within the ADC wrapper.
//!
//! This function disables continuous mode for the ADC interrupt passed into
//! \e adcIntNum. This means that pulses will not be generated for DMA for the
//! specified ADC interrupt until the corresponding interrupt flag for the
//! previous interrupt occurrence has been cleared using
//! ADC_clearInterruptStatus().
//!
//! \e adcIntNum can take the value \b ADC_INT_NUMBER1 or \b ADC_INT_NUMBER2
//! to express which of the interrupts of the ADC module is being configured.
//!
//! \return None.
//
//*****************************************************************************
static inline void
ADC_disableDMAContinuousMode(uint32_t base, ADC_IntNumber adcIntNum)
{
    uint32_t shiftVal;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    shiftVal = (uint32_t)adcIntNum << 3UL;

    //
    // Disable continuous mode for the specified ADC interrupt for DMA.
    //
    EALLOW;

    HWREG(base + ADC_O_DMAINTSEL) &= ~(ADC_DMAINTSEL_DMAINT1CONT << shiftVal);

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

    regOffset = base + repInstance;

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
//! source passed into \e trigger to modify via oversampling
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

    regOffset = base + repInstance;

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

    regOffset = base + repInstance;

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

    regOffset = base + repInstance;

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
//! In oversampling mode, the \e repCount parameter is to generate 2^repCount
//! triggers. It should be a value between 0 to 3. For example,
//! when \e repCount = 1, 2 triggers will be generated, when \e repCount = 2,
//! 4 triggers will be generated, and so on.
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
    ASSERT(repCount <= 3U);

    regOffset = base + repInstance;

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

    regOffset = base + repInstance;

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
//! This function configures ADC trigger repeater for trigger
//! and sync along with count and spread of triggers.
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
