//###########################################################################
//
// FILE:   f2838x_adc.c
//
// TITLE:  F2838x Adc Support Functions.
//
//###########################################################################
//
//
// 
// C2000Ware v6.00.01.00
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

//
// Included Files
//
#include "f2838x_device.h"
#include "f2838x_examples.h"

//
// AdcSetMode - Set the resolution and signalmode for a given ADC. This will
//              ensure that the correct trim is loaded.
//
// NOTE!!! There is no EALLOW/EDIS in this function! You need to make sure you
// perform the EALLOW before calling this function or else the ADC registers
// will not be configured.
//
void AdcSetMode(Uint16 adc, Uint16 resolution, Uint16 signalmode)
{
    Uint16 adcOffsetTrim;         // temporary ADC offset trim
    Uint16 *adcOffsetTrimOTPLoc;  // pointer to offset trim location in OTP

    //
    // Re-populate INL trim
    //
    CalAdcINL(adc);

    //
    // Calculate offset trim value based on ADC instance and
    // desired resolution
    //
    adcOffsetTrimOTPLoc = GetAdcOffsetTrimOTPLoc(adc, resolution);
    if(TI_OTP_DEV_PRG_KEY_BF == TI_OTP_DEV_KEY_BF)
    {
        adcOffsetTrim = *(Uint16 *)(adcOffsetTrimOTPLoc);

        //
        // Offset trim codes for single-ended and differential modes are
        // bit-packed in one location. Single-ended offset (signalmode=0)
        // is [15:8], differential mode (signalmode=1) is [7:0], hence
        // the code below
        //
        adcOffsetTrim = (signalmode == 0) ?
                                   (adcOffsetTrim >> 8):(adcOffsetTrim & 0xFF);
    }
    else
    {
        adcOffsetTrim = 0;
    }

    //
    // Apply the resolution and signalmode to the specified ADC.
    // Also apply the offset trim and, if needed, linearity trim correction.
    //
    switch(adc)
    {
        case ADC_ADCA:
        {
            AdcaRegs.ADCCTL2.bit.SIGNALMODE = signalmode;
            if(adcOffsetTrim > 0x0)
            {
                AdcaRegs.ADCOFFTRIM.all = adcOffsetTrim;
            }
#ifndef _DUAL_HEADERS
            if(ADC_RESOLUTION_12BIT == resolution)
#else
            if(ADC_BITRESOLUTION_12BIT == resolution)
#endif
            {
                AdcaRegs.ADCCTL2.bit.RESOLUTION = 0;

                //
                // 12-bit linearity trim workaround
                //
                AdcaRegs.ADCINLTRIM1 &= 0xFFFF0000;
                AdcaRegs.ADCINLTRIM2 &= 0xFFFF0000;
                AdcaRegs.ADCINLTRIM4 &= 0xFFFF0000;
                AdcaRegs.ADCINLTRIM5 &= 0xFFFF0000;
            }
            else
            {
                AdcaRegs.ADCCTL2.bit.RESOLUTION = 1;
            }
            break;
        }
        case ADC_ADCB:
        {
            AdcbRegs.ADCCTL2.bit.SIGNALMODE = signalmode;
            if(adcOffsetTrim > 0x0)
            {
                AdcbRegs.ADCOFFTRIM.all = adcOffsetTrim;
            }
#ifndef _DUAL_HEADERS
            if(ADC_RESOLUTION_12BIT == resolution)
#else
            if(ADC_BITRESOLUTION_12BIT == resolution)
#endif
            {
                AdcbRegs.ADCCTL2.bit.RESOLUTION = 0;

                //
                // 12-bit linearity trim workaround
                //
                AdcbRegs.ADCINLTRIM1 &= 0xFFFF0000;
                AdcbRegs.ADCINLTRIM2 &= 0xFFFF0000;
                AdcbRegs.ADCINLTRIM4 &= 0xFFFF0000;
                AdcbRegs.ADCINLTRIM5 &= 0xFFFF0000;
            }
            else
            {
                AdcbRegs.ADCCTL2.bit.RESOLUTION = 1;
            }
            break;
        }
        case ADC_ADCC:
        {
            AdccRegs.ADCCTL2.bit.SIGNALMODE = signalmode;
            if(adcOffsetTrim > 0x0)
            {
                AdccRegs.ADCOFFTRIM.all = adcOffsetTrim;
            }
#ifndef _DUAL_HEADERS
            if(ADC_RESOLUTION_12BIT == resolution)
#else
            if(ADC_BITRESOLUTION_12BIT == resolution)
#endif
            {
                AdccRegs.ADCCTL2.bit.RESOLUTION = 0;

                //
                // 12-bit linearity trim workaround
                //
                AdccRegs.ADCINLTRIM1 &= 0xFFFF0000;
                AdccRegs.ADCINLTRIM2 &= 0xFFFF0000;
                AdccRegs.ADCINLTRIM4 &= 0xFFFF0000;
                AdccRegs.ADCINLTRIM5 &= 0xFFFF0000;
            }
            else
            {
                AdccRegs.ADCCTL2.bit.RESOLUTION = 1;
            }
            break;
        }
        case ADC_ADCD:
        {
            AdcdRegs.ADCCTL2.bit.SIGNALMODE = signalmode;
            if(adcOffsetTrim > 0x0)
            {
                AdcdRegs.ADCOFFTRIM.all = adcOffsetTrim;
            }
#ifndef _DUAL_HEADERS
            if(ADC_RESOLUTION_12BIT == resolution)
#else
            if(ADC_BITRESOLUTION_12BIT == resolution)
#endif
            {
                AdcdRegs.ADCCTL2.bit.RESOLUTION = 0;

                //
                // 12-bit linearity trim workaround
                //
                AdcdRegs.ADCINLTRIM1 &= 0xFFFF0000;
                AdcdRegs.ADCINLTRIM2 &= 0xFFFF0000;
                AdcdRegs.ADCINLTRIM4 &= 0xFFFF0000;
                AdcdRegs.ADCINLTRIM5 &= 0xFFFF0000;
            }
            else
            {
                AdcdRegs.ADCCTL2.bit.RESOLUTION = 1;
            }
            break;
        }
    }
}

//
// CalAdcINL - Loads INL trim values from OTP into the trim registers of the
//             specified ADC. Use only as part of AdcSetMode function, since
//             linearity trim correction is needed for some modes.
//
void CalAdcINL(Uint16 adc)
{
    volatile Uint32 *inlRegBaseAddr, *inlOTPBaseAddr;
    Uint32 i;

    switch(adc)
    {
        case ADC_ADCA:
            //
            // Pointer to ADCA trim address base
            //
            inlRegBaseAddr = &AdcaRegs.ADCINLTRIM1;
            break;
        case ADC_ADCB:
            //
            // Pointer to ADCB trim address
            //
            inlRegBaseAddr = &AdcbRegs.ADCINLTRIM1;
            break;
        case ADC_ADCC:
            //
            // Pointer to ADCC trim address
            //
            inlRegBaseAddr = &AdccRegs.ADCINLTRIM1;
            break;
        case ADC_ADCD:
            //
            // Pointer to ADCD trim address
            //
            inlRegBaseAddr = &AdcdRegs.ADCINLTRIM1;
            break;
    }

    //
    // OTP trim location for ADC
    //
    inlOTPBaseAddr = GetAdcINLTrimOTPLoc(adc);

    //
    // Populate INL Trim Codes 1 to 6 for respective ADC
    //
    if(TI_OTP_DEV_PRG_KEY_BF == TI_OTP_DEV_KEY_BF)
    {
        for(i = 0; i < 6; i++)
        {
            *inlRegBaseAddr++ = *inlOTPBaseAddr++;
        }
    }
}

//
// End of file
//
