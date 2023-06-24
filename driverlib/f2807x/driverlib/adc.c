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
