//###########################################################################
//
// FILE:   adc.c
//
// TITLE:  C28x ADC driver.
//
//###########################################################################
// 
// C2000Ware v5.04.00.00
//
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
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
#define ADC_getINLTrimOTPLoc(offset) ((uint32_t *)(0x72070U + (0xCU * offset)))

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
// ADC_setupSOCRefloChannel
//
//*****************************************************************************
void
ADC_setupSOCRefloChannel(uint32_t base, ADC_SOCNumber socNumber,
        ADC_Trigger trigger, uint32_t sampleWindow, ADC_ChannelType channelType)
{
    switch(base)
    {
        case ADCA_BASE:

            //
            // Configure internal connection for VREFLOB which is available
            // on channel 19
            //
            if(channelType == ADC_CHANNEL_ODD)
            {
                ADC_setupSOC(ADCA_BASE, socNumber, trigger,
                                ADC_CH_ADCIN19, sampleWindow);
            }

            //
            // Configure internal connection for VREFLOC which is available
            // on channel 20
            //
            if(channelType == ADC_CHANNEL_EVEN)
            {
                ADC_setupSOC(ADCA_BASE, socNumber, trigger,
                                ADC_CH_ADCIN20, sampleWindow);
            }

            break;

        case ADCB_BASE:

            //
            // Configure internal connection for VREFLOC which will be available
            // on channel 17
            //
            if(channelType == ADC_CHANNEL_ODD)
            {
                EALLOW;
                HWREG(ANALOGSUBSYS_BASE + ASYSCTL_O_INTERNALTESTCTL) =
                                                                (0xA5A50006UL);
                EDIS;
                ADC_setupSOC(ADCB_BASE, socNumber, trigger,
                                ADC_CH_ADCIN17, sampleWindow);
            }

            //
            // Configure internal connection for VREFLOC which will be available
            // on channel 14 through CMPSS module
            //
            if(channelType == ADC_CHANNEL_EVEN)
            {
                EALLOW;
                HWREG(ANALOGSUBSYS_BASE + ASYSCTL_O_INTERNALTESTCTL) =
                                                                (0xA5A50206UL);
                HWREGH(CMPSS1_BASE + 0x1FU) = 0x8000U;
                EDIS;
                ADC_setupSOC(ADCB_BASE, socNumber, trigger,
                                ADC_CH_ADCIN14, sampleWindow);
            }
            break;

        case ADCC_BASE:

            //
            // Configure internal connection for VREFLOB which is available
            // on channel 19
            //
            if(channelType == ADC_CHANNEL_ODD)
            {
                ADC_setupSOC(ADCC_BASE, socNumber, trigger,
                                ADC_CH_ADCIN19, sampleWindow);
            }

            //
            // Configure internal connection for VREFLOA which is available
            // on channel 18
            //
            if(channelType == ADC_CHANNEL_EVEN)
            {
                ADC_setupSOC(ADCA_BASE, socNumber, trigger,
                                ADC_CH_ADCIN18, sampleWindow);
            }

            break;

        default:
            //
            // Invalid base address! Do nothing!
            //
            break;
    }
}
//*****************************************************************************
//
// ADC_setMode
//
//*****************************************************************************
void
ADC_setMode(uint32_t base, ADC_Resolution resolution,
            ADC_SignalMode signalMode)
{
    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));


    //
    // Apply the resolution and signalMode to the specified ADC.
    //
    EALLOW;
    HWREGH(base + ADC_O_CTL2) = (HWREGH(base + ADC_O_CTL2) &
                                 ~(ADC_CTL2_RESOLUTION | ADC_CTL2_SIGNALMODE)) |
                                ((uint16_t)resolution | (uint16_t)signalMode);
    EDIS;

    //
    // Apply INL and offset trims
    //
    ADC_setINLTrim(base);
    ADC_setOffsetTrim(base);
}

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
    ADC_Resolution resolution;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    resolution = (ADC_Resolution)
                 (HWREGH(base + ADC_O_CTL2) & ADC_CTL2_RESOLUTION);


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
        for(i = 0U; i < 6U; i++)
        {
            HWREG(base + ADC_O_INLTRIM1 + (i * 2U)) = (*inlTrimAddress++);
        }

        //
        // Apply linearity trim workaround for 12-bit resolution
        //
        if(resolution == ADC_RESOLUTION_12BIT)
        {
            //
            // 12-bit linearity trim workaround
            //
            HWREG(base + ADC_O_INLTRIM1) &= 0xFFFF0000U;
            HWREG(base + ADC_O_INLTRIM2) &= 0xFFFF0000U;
            HWREG(base + ADC_O_INLTRIM4) &= 0xFFFF0000U;
            HWREG(base + ADC_O_INLTRIM5) &= 0xFFFF0000U;
        }
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
    //
    // Selecting the individual offset trim mode wherein offset trim will be
    // supplied from individual registers already programmed by device_cal api.
    //
    ADC_selectOffsetTrimMode(base, ADC_OFFSET_TRIM_INDIVIDUAL);
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


    uint16_t moduleShiftVal;

    //
    // Assign a shift amount corresponding to which ADC module is being
    // configured.
    //
    switch(base)
    {
        case ADCA_BASE:
            moduleShiftVal = 0U;
            break;
        case ADCB_BASE:
            moduleShiftVal = 1U;
            break;
        case ADCC_BASE:
            moduleShiftVal = 2U;
            break;
        default:
            //
            // Invalid base address!!
            //
            moduleShiftVal = 0U;
            break;
    }

    EALLOW;
    //
    // Configure the reference mode (internal or external).
    //
    if(refMode == ADC_REFERENCE_INTERNAL)
    {
        HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_ANAREFCTL) &=
            ~(ASYSCTL_ANAREFCTL_ANAREFASEL << moduleShiftVal);
    }


    else
    {
        HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_ANAREFCTL) |=
            ASYSCTL_ANAREFCTL_ANAREFASEL << moduleShiftVal;
    }

    //
    // Configure the reference voltage (3.3V or 2.5V).
    //
    if(refVoltage == ADC_REFERENCE_3_3V)
    {
        HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_ANAREFCTL) &=
            ~(ASYSCTL_ANAREFCTL_ANAREFA2P5SEL << moduleShiftVal);
    }
    else
    {
        HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_ANAREFCTL) |=
            ASYSCTL_ANAREFCTL_ANAREFA2P5SEL << moduleShiftVal;

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

