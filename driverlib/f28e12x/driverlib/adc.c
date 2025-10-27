//###########################################################################
//
// FILE:   adc.c
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

#include "adc.h"

//
// The following macro calculates the INL trim location in OTP memory
// required to calibrate the ADC linearity.  Use this in the
// ADC_setMode() function only.
//
#define ADC_getINLTrimOTPLoc(offset) ((uint32_t *)(0x72058U + (0x6U * offset)))

//
// This macro calculates the ADC offset trim location in OTP memory required
// to calibrate ADC offset. Use this in the ADC_setMode() function only.
//
#define ADC_getOffsetTrimOTPLoc(offset)     ((uint16_t *)(0x72066U + offset))

//
// TI-OTP key value expected to be programmed in trimmed device
//
#define TI_OTP_DEV_KEY                          (0x5A5AU)

//
// Macro to read the key value programmed in the device
//
#define TI_OTP_DEV_PRG_KEY                      (HWREGH(0x72064UL))

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
        for(i = 0U; i < 2U; i++)
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
        HWREG(base + ADC_O_OFFTRIM) = (uint32_t)offsetTrim;
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
        HWREG(ANALOGSUBSYS_BASE + ASYSCTL_O_REFCONFIGA) &=
             ~(ASYSCTL_REFCONFIGA_ANAREFSEL);
    }


    else
    {
        HWREG(ANALOGSUBSYS_BASE + ASYSCTL_O_REFCONFIGA) |=
            ASYSCTL_REFCONFIGA_ANAREFSEL;
    }

    //
    // Configure the reference voltage (3.3V or 2.5V).
    //
    if(refVoltage == ADC_REFERENCE_3_3V)
    {
        HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_ANAREFCTL) &=
            ~(ASYSCTL_ANAREFCTL_ANAREF2P5SEL);
    }
    else
    {
        HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_ANAREFCTL) |=
            ASYSCTL_ANAREFCTL_ANAREF2P5SEL;

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

    //
    // Get the offset to the appropriate trip limit registers.
    //
    ppbHiOffset = (ADC_PPBxTRIPHI_STEP * (uint32_t)ppbNumber) +
                  ADC_O_PPB1TRIPHI;
    ppbLoOffset = (ADC_PPBxTRIPLO_STEP * (uint32_t)ppbNumber) +
                  ADC_O_PPB1TRIPLO;

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

    regOffset = base + repInstance;
    EALLOW;
    //
    // Configure repeater mode, trigger and syncin source.
    //
    HWREG(regOffset + ADC_O_REP1CTL) = (HWREG(regOffset + ADC_O_REP1CTL) &
                    ~((uint32_t)REPCTL_MASK))  | 
                    (((uint32_t)config->repTrigger << ADC_REP1CTL_TRIGGER_S) |
                    ((uint32_t)config->repSyncin << ADC_REP1CTL_SYNCINSEL_S));

    //
    // Configure repeater count.
    //
    HWREG(regOffset + ADC_O_REP1N) = (HWREG(regOffset + ADC_O_REP1N) &
                                    ~(ADC_REP1N_NSEL_M)) | config->repCount;

    //
    // Configure repeater spread.
    //
    HWREG(regOffset + ADC_O_REP1SPREAD) =
                                      (HWREG(regOffset + ADC_O_REP1SPREAD) &
                                      ~(ADC_REP1SPREAD_SPREAD_M)) |
                                      config->repSpread;
    EDIS;

}

