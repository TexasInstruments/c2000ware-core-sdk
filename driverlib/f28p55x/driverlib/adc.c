//###########################################################################
//
// FILE:   adc.c
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

#include "adc.h"
#include "asysctl.h"

//
// The following macro calculates the INL trim location in OTP memory
// required to calibrate the ADC linearity.  Use this in the
// ADC_setMode() function only.
//
#define ADC_getINLTrimOTPLoc(offset) ((uint32_t *)(0x72070U + (0x6U * offset)))

//
// This macro calculates the ADC offset trim location in OTP memory required
// to calibrate ADC offset. Use this in the ADC_setMode() function only.
//
#define ADC_getOffsetTrimOTPLoc(offset)     ((uint16_t *)(0x72064U + offset))

//
// TI-OTP key value expected to be programmed in trimmed device
//
#define TI_OTP_DEV_KEY                          (0x5A5AU)

//
// Macro to read the key value programmed in the device
//
#define TI_OTP_DEV_PRG_KEY                      (HWREGH(0x72062UL))

//*****************************************************************************
//
// ADC_setINLTrim
//
//*****************************************************************************
void
ADC_setINLTrim(uint32_t base)
{
    uint16_t i;
    uint32_t * inlTrimAddress;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    if(TI_OTP_DEV_PRG_KEY == TI_OTP_DEV_KEY)
    {
        switch(base)
        {
            case ADCA_BASE:
                inlTrimAddress = ADC_getINLTrimOTPLoc(0U);
                break;
            case ADCB_BASE:
                inlTrimAddress = ADC_getINLTrimOTPLoc(1U);
                break;
            case ADCC_BASE:
                inlTrimAddress = ADC_getINLTrimOTPLoc(2U);
                break;
            case ADCD_BASE:
                inlTrimAddress = ADC_getINLTrimOTPLoc(3U);
                break;
            case ADCE_BASE:
                inlTrimAddress = ADC_getINLTrimOTPLoc(4U);
                break;
            default:
                //
                // Invalid base address!
                //
                inlTrimAddress = ADC_getINLTrimOTPLoc(0U);
                break;
        }

        //
        // Update INL trim values to ADC trim registers
        //
        EALLOW;
        for(i = 0U; i < 3U; i++)
        {
            HWREG(base + ADC_O_INLTRIM1 + (i * 2U)) = (*inlTrimAddress++);
        }

        //
        // Apply linearity trim workaround for 12-bit resolution
        //
            HWREG(base + ADC_O_INLTRIM1) &= 0xFFFF0000U;
            HWREG(base + ADC_O_INLTRIM2) &= 0xFFFF0000U;

        EDIS;
    }
}

//*****************************************************************************
//
// ADC_setOffsetTrim
//
//*****************************************************************************
void
ADC_setOffsetTrim(uint32_t base)
{
    uint16_t offsetIndex = 0U, offsetTrim = 0U;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Get the offset index for the ADC base
    //
    switch(base)
    {
        case ADCA_BASE:
            offsetIndex = (uint16_t)(0U);
            break;
        case ADCB_BASE:
            offsetIndex = (uint16_t)(2U);
            break;
        case ADCC_BASE:
            offsetIndex = (uint16_t)(4U);
            break;
        case ADCD_BASE:
            offsetIndex = (uint16_t)(6U);
            break;
        case ADCE_BASE:
            offsetIndex = (uint16_t)(8U);
            break;
        default:
            //
            // Invalid base address!
            //
            offsetIndex = (uint16_t)(0U);
            break;
    }

    if(TI_OTP_DEV_PRG_KEY == TI_OTP_DEV_KEY)
    {
        offsetTrim = (*(uint16_t *)(ADC_getOffsetTrimOTPLoc(offsetIndex)));
        offsetTrim = (offsetTrim & ADC_OFFTRIM_OFFTRIM_M);
    }
    else
    {
        offsetTrim = 0U;
    }

    //
    // Configure the offset trim, offset trim is not updated here in case of
    // untrimmed devices.
    //
    if(offsetTrim > 0x0U)
    {
        EALLOW;
        HWREGH(base + ADC_O_OFFTRIM) = offsetTrim;
        EDIS;
    }
}

//*****************************************************************************
//
// ADC_setVREF
//
//*****************************************************************************
void
ADC_setVREF(uint32_t base, ADC_ReferenceMode refMode,
            ADC_ReferenceVoltage refVoltage)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    EALLOW;
    //
    // Configure the reference mode (internal or external).
    //
    if(refMode == ADC_REFERENCE_INTERNAL)
    {
        HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_ANAREFPCTL) &=
            ~(ASYSCTL_ANAREF_INTREF_ADCA |
              ASYSCTL_ANAREF_INTREF_ADCB |
              ASYSCTL_ANAREF_INTREF_ADCC |
              ASYSCTL_ANAREF_INTREF_ADCD |
              ASYSCTL_ANAREF_INTREF_ADCE);
        HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_ANAREFNCTL) &=
            ~(ASYSCTL_ANAREF_INTREF_ADCA |
              ASYSCTL_ANAREF_INTREF_ADCB |
              ASYSCTL_ANAREF_INTREF_ADCC |
              ASYSCTL_ANAREF_INTREF_ADCD |
              ASYSCTL_ANAREF_INTREF_ADCE);
    }

    else if(refMode == ADC_REFERENCE_EXTERNAL)
    {
        HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_ANAREFPCTL) =
            (HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_ANAREFPCTL) & ~0x3FFU) |
            (ASYSCTL_ANAREF_VREFHI_ADCA |
             ASYSCTL_ANAREF_VREFHI_ADCB |
             ASYSCTL_ANAREF_VREFHI_ADCC |
             ASYSCTL_ANAREF_VREFHI_ADCD |
             ASYSCTL_ANAREF_VREFHI_ADCE);
        HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_ANAREFNCTL) =
            (HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_ANAREFNCTL) & ~0x3FFU) |
            (ASYSCTL_ANAREF_VREFHI_ADCA |
             ASYSCTL_ANAREF_VREFHI_ADCB |
             ASYSCTL_ANAREF_VREFHI_ADCC |
             ASYSCTL_ANAREF_VREFHI_ADCD |
             ASYSCTL_ANAREF_VREFHI_ADCE);
    }

    else
    {
        HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_ANAREFPCTL) |=
            (ASYSCTL_ANAREF_VDDA_ADCA |
             ASYSCTL_ANAREF_VDDA_ADCB |
             ASYSCTL_ANAREF_VDDA_ADCC |
             ASYSCTL_ANAREF_VDDA_ADCD |
             ASYSCTL_ANAREF_VDDA_ADCE);
        HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_ANAREFPCTL) |=
            (ASYSCTL_ANAREF_VDDA_ADCA |
             ASYSCTL_ANAREF_VDDA_ADCB |
             ASYSCTL_ANAREF_VDDA_ADCC |
             ASYSCTL_ANAREF_VDDA_ADCD |
             ASYSCTL_ANAREF_VDDA_ADCE);
    }

    //
    // Configure the reference voltage (3.3V or 2.5V).
    //
    if(refVoltage == ADC_REFERENCE_3_3V)
    {
        HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_ANAREFPCTL) |=
          ((ASYSCTL_ANAREF_ADCA |
            ASYSCTL_ANAREF_ADCB |
            ASYSCTL_ANAREF_ADCC |
            ASYSCTL_ANAREF_ADCD |
            ASYSCTL_ANAREF_ADCE) << 10);
    }
    else
    {
        HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_ANAREFPCTL) &=
          ~((ASYSCTL_ANAREF_ADCA |
             ASYSCTL_ANAREF_ADCB |
             ASYSCTL_ANAREF_ADCC |
             ASYSCTL_ANAREF_ADCD |
             ASYSCTL_ANAREF_ADCE) << 10);

    }
    EDIS;

}

//*****************************************************************************
//
// ADC_setPPBTripLimits
//
//*****************************************************************************
void
ADC_setPPBTripLimits(uint32_t base, ADC_PPBNumber ppbNumber,
                     int32_t tripHiLimit, int32_t tripLoLimit)
{
    uint32_t ppbHiOffset;
    uint32_t ppbLoOffset;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));
    ASSERT((tripHiLimit <= 8388607) && (tripHiLimit >= -8388607));
    ASSERT((tripLoLimit <= 8388607) && (tripLoLimit >= -8388607));

    //
    // Get the offset to the appropriate trip limit registers.
    //
    ppbHiOffset = (ADC_PPBxTRIPHI_STEP * (uint32_t)ppbNumber) +
                  ADC_O_PPB1TRIPHI;
    //
    // Enable extended low limit
    //
    ADC_enablePPBExtendedLowLimit(base, ppbNumber);
    ppbLoOffset = (ADC_PPBxTRIPLO2_STEP * (uint32_t)ppbNumber) +
                   ADC_O_PPB1TRIPLO2;

    EALLOW;

    //
    // Set the trip high limit.
    //
    HWREG(base + ppbHiOffset) =
        (HWREG(base + ppbHiOffset) & ~ADC_PPBTRIP_MASK) |
        ((uint32_t)tripHiLimit & ADC_PPBTRIP_MASK);

    //
    // Set the trip low limit.
    //
    HWREG(base + ppbLoOffset) =
        (HWREG(base + ppbLoOffset) & ~ADC_PPBTRIP_MASK) |
        ((uint32_t)tripLoLimit & ADC_PPBTRIP_MASK);

    EDIS;
}

//*****************************************************************************
//
// ADC_configureRepeater
//
//*****************************************************************************
void
ADC_configureRepeater(uint32_t base, uint16_t repInstance,
                      ADC_RepeaterConfig *config)
{
    uint32_t regOffset;
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));
    ASSERT(repInstance <= 2U);
    ASSERT(config->repCount <= 127U);

    regOffset = base + (repInstance * (ADC_REPxCTL_STEP));
    EALLOW;
    //
    // Configure repeater mode, trigger and syncin source.
    //
    HWREG(regOffset + ADC_O_REP1CTL) = (HWREG(regOffset + ADC_O_REP1CTL) &
                     ~((uint32_t)REPCTL_MASK))  | (((uint32_t)config->repMode) |
                      ((uint32_t)config->repTrigger << ADC_REP1CTL_TRIGGER_S) |
                      ((uint32_t)config->repSyncin << ADC_REP1CTL_SYNCINSEL_S));

    //
    // Configure repeater count.
    //
    HWREGH(regOffset + ADC_O_REP1N) = (HWREGH(regOffset + ADC_O_REP1N) &
                                      ~(ADC_REP1N_NSEL_M)) | config->repCount;

    //
    // Configure repeater phase.
    //
    HWREGH(regOffset + ADC_O_REP1PHASE) = (HWREGH(regOffset + ADC_O_REP1PHASE) &
                                          ~(ADC_REP1PHASE_PHASE_M)) |
                                          config->repPhase;
    //
    // Configure repeater spread.
    //
    HWREGH(regOffset + ADC_O_REP1SPREAD) =
                                      (HWREGH(regOffset + ADC_O_REP1SPREAD) &
                                      ~(ADC_REP1SPREAD_SPREAD_M)) |
                                      config->repSpread;
    EDIS;

}

//*****************************************************************************
//
// ADC_configPPBFilter
//
//*****************************************************************************
void
ADC_configPPBFilter(uint32_t base, uint32_t clkPrescale, uint16_t sampleWindow,
                    uint16_t threshold, ADC_PPBNumber ppbNumber)
{
    uint16_t regValue;
    uint32_t ppbOffset;
    uint32_t ppbClkOffset;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));
    ASSERT(clkPrescale <= 65535U);
    ASSERT((sampleWindow >= 1U) && (sampleWindow <= 64U));
    ASSERT((threshold - 1U) >= ((sampleWindow - 1U) / 2U));

    //
    // Shift the sample window and threshold values into the correct positions
    // and write them to the appropriate register.
    //
    ppbOffset = (ADC_PPBTRIPxFILCTL_STEP * (uint32_t)ppbNumber) +
                ADC_O_PPBTRIP1FILCTL;

    ppbClkOffset = (ADC_PPBTRIPxFILCLKCTL_STEP * (uint32_t)ppbNumber) +
                    ADC_O_PPBTRIP1FILCLKCTL;

    regValue = ((sampleWindow - 1U) << ADC_PPBTRIP1FILCTL_SAMPWIN_S) |
               ((threshold - 1U) << ADC_PPBTRIP1FILCTL_THRESH_S);

    EALLOW;

    HWREGH(base + ppbOffset) =
        (HWREGH(base + ppbOffset) &
         ~(ADC_PPBTRIP1FILCTL_SAMPWIN_M | ADC_PPBTRIP1FILCTL_THRESH_M)) |
        regValue;

    //
    // Set the filter sample clock prescale for the high comparator.
    //
    HWREGH(base + ppbClkOffset)  = (uint16_t)clkPrescale;

    EDIS;
}
