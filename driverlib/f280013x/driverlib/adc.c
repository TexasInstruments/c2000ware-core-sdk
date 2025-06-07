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

//*****************************************************************************
//
// Defines for locations of ADC calibration functions in OTP for use in
// ADC_setVREF(), ADC_setOffsetTrimAll() and ADC_setOffsetTrim(). Not intended
// for use by application code.
//
//*****************************************************************************
#define ADC_OFFSET_TRIM_KEY_OTP_MP1               0x7103CUL
#define ADC_OFFSET_TRIM_KEY_OTP_MP3               0x71114UL

#define ADC_OFFSET_TRIM_OTP_ADCA_MP1              0x7103EUL
#define ADC_OFFSET_TRIM_OTP_ADCC_MP1              0x7103FUL
#define ADC_OFFSET_TRIM_OTP_ADCA_MP3              0x71116UL
#define ADC_OFFSET_TRIM_OTP_ADCC_MP3              0x71117UL

#define ADC_VOLTAGE_REF_REG_OFFSET              8U
//
// The following macro calculates the INL trim location in OTP memory
// required to calibrate the ADC linearity.
//
#define ADC_getINLTrimOTPLoc(offset) ((uint32_t *)(0x71042U + (0x4U * offset)))

//
// TI-OTP key value expected to be programmed in trimmed device
//
#define TI_OTP_DEV_KEY                          (0x5A5A5A5AUL)

//
// Macro to read the key value programmed in the device
//
#define TI_OTP_DEV_PRG_KEY                      (HWREG(0x71040UL))


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
        HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_ANAREFCTL) &=
            ~(ASYSCTL_ANAREFCTL_ANAREFSEL);
    }


    else
    {
        HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_ANAREFCTL) |=
            ASYSCTL_ANAREFCTL_ANAREFSEL;
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

    //
    // Set ADC offset trim for the all the ADC instances
    //
    ADC_setOffsetTrimAll(refMode, refVoltage);
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
            case ADCC_BASE:
                inlTrimAddress = ADC_getINLTrimOTPLoc(1U);
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
        for(i = 0U; i < 4U; i += 2U)
        {
            //
            // 32-bit writes are performed since the OTP source is word aligned.
            //
            HWREG(base + ADC_O_INLTRIM2 + i) = (*inlTrimAddress++);
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
    uint16_t *offset;
    uint32_t moduleShiftVal;
    uint16_t offsetShiftVal;
    uint16_t analogRefRegVal;
    ADC_ReferenceMode refMode;
    ADC_ReferenceVoltage refVoltage;

    //
    // Check the arguments.
    //
    ASSERT(ADC_isBaseValid(base));

    //
    // Assign a shift amount corresponding to which ADC module is being
    // configured.
    //
    switch(base)
    {
        case ADCA_BASE:
            moduleShiftVal = 0U;
            break;
        case ADCC_BASE:
            moduleShiftVal = 1U;
            break;
        default:
            //
            // Invalid base address!!
            //
            moduleShiftVal = 0U;
            break;
    }

    //
    // Read the Analog Reference Control Register value to determine the
    // ADC reference mode and reference voltage value.
    //
    analogRefRegVal = HWREGH(ANALOGSUBSYS_BASE + ASYSCTL_O_ANAREFCTL);

    //
    // Calculate refMode and refVoltage based on input ADC base
    //
    refMode = (ADC_ReferenceMode)((analogRefRegVal >> moduleShiftVal) & 1U);
    refVoltage = (ADC_ReferenceVoltage)((analogRefRegVal >>
                 (ADC_VOLTAGE_REF_REG_OFFSET + moduleShiftVal)) & 1U);

    //
    // Offset trim for internal VREF 3.3V is unique and stored in upper byte.
    //
    if((refMode == ADC_REFERENCE_INTERNAL) &&
       (refVoltage == ADC_REFERENCE_3_3V))
    {
        offsetShiftVal = 8U;
    }
    else
    {
        offsetShiftVal = 0U;
    }

    //
    // Set up pointer to offset trim in OTP.
    //
    uint32_t *offsetKey;

    offsetKey = (uint32_t *)ADC_OFFSET_TRIM_KEY_OTP_MP3;

    if(*offsetKey == TI_OTP_DEV_KEY)
    {
        offset = (uint16_t *)(ADC_OFFSET_TRIM_OTP_ADCA_MP3 + moduleShiftVal);
    }
    else
    {
        offsetKey = (uint32_t *)ADC_OFFSET_TRIM_KEY_OTP_MP1;
        if(*offsetKey == TI_OTP_DEV_KEY)
        {
            offset = (uint16_t *)(ADC_OFFSET_TRIM_OTP_ADCA_MP1 +
                                    moduleShiftVal);
        }
        else
        {
            offset = 0U;
        }
    }

    //
    // Get offset trim from OTP and write it to the register.
    //
    EALLOW;
    HWREGH(base + ADC_O_OFFTRIM) = (*offset >> offsetShiftVal) & 0xFFU;
    EDIS;
}

//*****************************************************************************
//
// ADC_setOffsetTrimAll
//
//*****************************************************************************
void
ADC_setOffsetTrimAll(ADC_ReferenceMode refMode, ADC_ReferenceVoltage refVoltage)
{
    uint16_t *offset;
    uint16_t offsetShiftVal;

    //
    // Offset trim for internal VREF 3.3V is unique and stored in upper byte.
    //
    if((refMode == ADC_REFERENCE_INTERNAL) &&
       (refVoltage == ADC_REFERENCE_3_3V))
    {
        offsetShiftVal = 8U;
    }
    else
    {
        offsetShiftVal = 0U;
    }

    //
    // Set up pointer to offset trim in OTP for ADCA.
    //
    uint32_t *offsetKey;
    offsetKey = (uint32_t *)ADC_OFFSET_TRIM_KEY_OTP_MP3;
    if(*offsetKey == TI_OTP_DEV_KEY)
    {
    offset = (uint16_t *)ADC_OFFSET_TRIM_OTP_ADCA_MP3;
    }
    else
    {
        offsetKey = (uint32_t *)ADC_OFFSET_TRIM_KEY_OTP_MP1;
        if(*offsetKey == TI_OTP_DEV_KEY)
        {
            offset = (uint16_t *)ADC_OFFSET_TRIM_OTP_ADCA_MP1;
        }
        else
        {
            offset = 0U;
        }
    }

    //
    // Get offset trim from OTP and write it to the register for ADCA.
    //
    EALLOW;
    HWREGH(ADCA_BASE + ADC_O_OFFTRIM) = (*offset >> offsetShiftVal) & 0xFFU;

    //
    // Set up pointer to offset trim in OTP for ADCC.
    //
    offsetKey = (uint32_t *)ADC_OFFSET_TRIM_KEY_OTP_MP3;
    if(*offsetKey == TI_OTP_DEV_KEY)
    {
        offset = (uint16_t *)ADC_OFFSET_TRIM_OTP_ADCC_MP3;
    }
    else
    {
        offsetKey = (uint32_t *)ADC_OFFSET_TRIM_KEY_OTP_MP1;
        if(*offsetKey == TI_OTP_DEV_KEY)
        {
            offset = (uint16_t *)ADC_OFFSET_TRIM_OTP_ADCC_MP1;
        }
        else
        {
            offset = 0U;
        }
    }

    //
    // Get offset trim from OTP and write it to the register for ADCC.
    //
    HWREGH(ADCC_BASE + ADC_O_OFFTRIM) = (*offset >> offsetShiftVal) & 0xFFU;
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
    ASSERT((tripHiLimit <= 65535) && (tripHiLimit >= -65536));
    ASSERT((tripLoLimit <= 65535) && (tripLoLimit >= -65536));

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
